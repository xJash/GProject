#include "stdafx.h"
#include "Patch.h"
#include "PatchDlg.h"


#include "FrontProcess.h"
#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

#include "ITZEncrypt.h"

#include "../../Server/FrontServer/FrontMsg.h"


FrontProcess::FrontProcess()
{
	m_pFrontSession = NULL;
	m_szIP1[ 0 ] = NULL;
	m_szIP2[ 0 ] = NULL;

	m_bReqVersionInfo = FALSE;
	m_bVersion = FALSE;

	m_pPatchDlg = NULL;

	m_bSecretKey = FALSE;

	m_usTryConnectCount = 0;

}


FrontProcess::~FrontProcess()
{

}

void FrontProcess::Init( char *szIP1, char *szIP2, UI16 usPort, CPatchDlg *pDlg )
{
	strcpy( m_szIP1, szIP1 );
	strcpy( m_szIP2, szIP2 );

	m_usPort = usPort;

	m_sf.CreateFactory( &m_sm, 1, 50 * 1000, 50 * 1000 );

	ITZSession *pSession = m_sm.GetSession( 0 );
	
	InterlockedExchange( (LPLONG)&m_pFrontSession, (LONG)pSession );

	overlapped.CreateOverlapped( &m_sm );	

	m_bReqVersionInfo = FALSE;
	m_bVersion = FALSE;

	m_pPatchDlg = pDlg;

}

void FrontProcess::	Run()
{
	m_sm.Update();

	if( m_pFrontSession == NULL ) return;


	// ����Ʈ ������ ���� ���� �ƴϰ�, ���� ������ ���� ���°� �ƴ϶��, ���� �õ��Ѵ�
	if( m_pFrontSession->GetState() == SESSION_STATE_NONE &&
		m_bVersion == FALSE ) 
	{
		m_usTryConnectCount++;

		if ( m_usTryConnectCount < 100 )
		{
			if( m_sm.Connect( 0, m_szIP1, m_usPort ) == m_pFrontSession )
			{
				m_bSecretKey = FALSE;
			}
			else 
			{
			}
		}
		else
		{
			if( m_sm.Connect( 0, m_szIP2, m_usPort ) == m_pFrontSession ) 
			{
				m_bSecretKey = FALSE;
			}
			else 
			{
			}
		}
	}

	// ����Ʈ ������ ���������� ����� �����̸�, 
	else if( m_pFrontSession->GetState() == SESSION_STATE_ESTABLISHED ) 
	{
		// ���� ������ ��û ���� �ʾ����� ��û�Ѵ�
		if( m_bReqVersionInfo == FALSE && m_bSecretKey == TRUE ) 
		{

			sRequest_PatchInfo sendMsg;

			sendMsg.packetHeader.usCmd = FRONTMSG_REQUEST_PATCHINFO;
			sendMsg.packetHeader.usSize = sizeof( sendMsg );

			sendMsg.uiCurrentVersion = m_pPatchDlg->m_uiCurrentVersion;

			m_pFrontSession->GetEncrypt()->Encode( (UI08 *)&sendMsg, m_encrBuf );

			m_pFrontSession->GetSendBuffer()->Write( (BYTE *)m_encrBuf );

			m_bReqVersionInfo = TRUE;
		}


		// ���ۿ��� ��Ŷ�� �ϳ� �����´�
		sPacketHeader *pPacket = (sPacketHeader *)m_pFrontSession->GetRecvBuffer()->GetFirstPacket();		
		
		if( pPacket != NULL ) 
		{										
			// ��Ŷ�� ������,
			
			char packet[ PACKET_MAX_SIZE ];
			memcpy( packet, pPacket, pPacket->usSize );
			m_pFrontSession->GetRecvBuffer()->RemoveFirstPacket();

			m_pPatchDlg->FrontMsgProcess( (sPacketHeader *)packet );
			
		}
	}
}
