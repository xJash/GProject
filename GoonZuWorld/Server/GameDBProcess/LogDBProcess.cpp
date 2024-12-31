#include "..\Server.h"

#include "LogDBProcess.h"

#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

#include "..\..\..\DBManager\GameDBManager_World\DBGameLogMsg.h"

extern cltCommonLogic* pclClient;

LogDBProcess::LogDBProcess()
{
	m_pGameDBSession = NULL;

	m_gameDBManagerIP[ 0 ] = NULL;
}

LogDBProcess::~LogDBProcess()
{

}

void LogDBProcess::Init( TCHAR *ip, UI16 usPort )
{
	m_sf.CreateFactory( &m_sm, 1, 5000 * 1000, 5000 * 1000 );

	m_pGameDBSession = m_sm.GetSession( 0 );

	m_iocp.CreateIOCP( &m_sm, 1 );

	StringCchCopy( m_gameDBManagerIP, 20, ip );
	m_gameDBManagerPort = usPort;
}

void LogDBProcess::Run()
{
	if(m_pGameDBSession == NULL)return ;

	m_sm.Update();	

	// ������ ������� ���� �����̸�,
	if( m_pGameDBSession->GetState() == SESSION_STATE_NONE )
	{
	//tsoi 	printf(  TEXT("DB Manager ���� �õ�\n") );
		if( m_sm.Connect( 0, m_gameDBManagerIP, m_gameDBManagerPort ) == m_pGameDBSession ) {
		} else {
		}
		
	} 
	// ������ ���������� ����� �����̸�,
	else if( m_pGameDBSession->GetState() == SESSION_STATE_ESTABLISHED )
	{

		int count = m_pGameDBSession->GetRecvBuffer()->GetPacketCount();

		for( int i = 0; i < count; ++i ) {

			// ���ۿ��� ��Ŷ�� �ϳ� �����´�
			sPacketHeader *pPacket = (sPacketHeader *)m_pGameDBSession->GetRecvBuffer()->GetFirstPacket();
				
			if( pPacket != NULL ) {										
				// ��Ŷ�� ������,

				((cltServer *)pclClient)->DoLogMsg(pPacket);

				// ó�� �� ��Ŷ�� ���ۿ��� �����
				m_pGameDBSession->GetRecvBuffer()->RemoveFirstPacket();
				

			}
		
		}


	}

}

bool LogDBProcess::SendMsg(sPacketHeader *pPacket)
{
	if(m_pGameDBSession == NULL) return false;
	if(m_pGameDBSession->GetSendBuffer() == NULL) return false;

	if(m_pGameDBSession->GetState() != SESSION_STATE_ESTABLISHED) return false;

	m_pGameDBSession->GetSendBuffer()->Write( (BYTE *)pPacket);
	return true;
}



