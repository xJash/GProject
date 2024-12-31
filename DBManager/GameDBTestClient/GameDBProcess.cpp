#include "GameDBProcess.h"
#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"
#include "../GameDBManager/DBMsg.h"

GameDBProcess::GameDBProcess()
{
	m_pGameDBSession = NULL;

	m_gameDBManagerIP[ 0 ] = NULL;
}

GameDBProcess::~GameDBProcess()
{

}

void GameDBProcess::Init( char *ip, UI16 usPort )
{
	m_sf.CreateFactory( &m_sm, 1, 1000 * 1000, 1000 * 1000 );

	m_pGameDBSession = m_sm.GetSession( 0 );

	m_iocp.CreateIOCP( &m_sm, 1 );

	strcpy( m_gameDBManagerIP, ip );
	m_gameDBManagerPort = usPort;
}

void GameDBProcess::Run()
{
	m_sm.Update();

	// ������ ������� ���� �����̸�,
	if( m_pGameDBSession->GetState() == SESSION_STATE_NONE )
	{
		if( m_sm.Connect( 0, m_gameDBManagerIP, m_gameDBManagerPort ) == m_pGameDBSession ) {
		} else {
		}
		
	} 
	// ������ ���������� ����� �����̸�,
	else if( m_pGameDBSession->GetState() == SESSION_STATE_ESTABLISHED )
	{

		// ���ۿ��� ��Ŷ�� �ϳ� �����´�
		sPacketHeader *pPacket = (sPacketHeader *)m_pGameDBSession->GetRecvBuffer()->GetFirstPacket();
			
		if( pPacket != NULL ) {										
			// ��Ŷ�� ������,

			switch( pPacket->usCmd ) {

			case DBMSG_RESPONSE_PERSONLISTINFOGET:
				{
					printf( "DBMSG_RESPONSE_PERSONLISTINFOGET\n" );
					sDBResponse_PersonListInfoGet *pRecvMsg =  (sDBResponse_PersonListInfoGet *)pPacket;

					for( int i = 0; i < 3; ++i ) {
						printf( "[%d] kind:%d, name:%s, mapindex:%d, x:%d, y:%d\n",
							i, pRecvMsg->personInfo[ i ].kind,
							pRecvMsg->personInfo[ i ].name,
							pRecvMsg->personInfo[ i ].mapindex,
							pRecvMsg->personInfo[ i ].x,
							pRecvMsg->personInfo[ i ].y );
					}
					
				}
				break;

			}

			// ó�� �� ��Ŷ�� ���ۿ��� �����
			m_pGameDBSession->GetRecvBuffer()->RemoveFirstPacket();
		}

	}

}