#include "FrontServer.h"
#include "AuthProcess.h"
#include "FrontClientProtocol.h"

#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

#include "Log.h"

AuthProcess::AuthProcess()
{
	m_pAuthSession = NULL;
	m_szIP[ 0 ] = NULL;

}

AuthProcess::~AuthProcess()
{

}

void AuthProcess::Init( char *szIP, UI16 usPort )
{
	strcpy( m_szIP, szIP );
	m_usPort = usPort;

	m_sf.CreateFactory( &m_sm, 1, 20 * 1000 * 1000, 20 * 1000 * 1000 );

	ITZSession *pSession = m_sm.GetSession( 0 );

	InterlockedExchange( (LPLONG)&m_pAuthSession, (LONG)pSession );

	m_iocp.CreateIOCP( &m_sm, 1 );

	g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "AuthProcess::Init();IP=%s;Port=%d", szIP, usPort);
}

void AuthProcess::Run()
{
	
	int i;

	m_sm.Update();

	if( m_pAuthSession->GetState() == SESSION_STATE_NONE ) 
	{
		if( m_sm.Connect( 0, m_szIP, m_usPort ) == m_pAuthSession ) 
		{
		} 
		else 
		{
		}
	}

	if( m_pAuthSession->GetState() == SESSION_STATE_ESTABLISHED ) 
	{		

		sPacketHeader *pPacket;
		SI32 count = m_pAuthSession->GetRecvBuffer()->GetPacketCount();

		for( i = 0; i < count; ++i ) 
		{
			// ���ۿ��� ��Ŷ�� �ϳ� �����´�
			pPacket = (sPacketHeader *)m_pAuthSession->GetRecvBuffer()->GetFirstPacket();		
			
			if( pPacket != NULL ) {										
				// ��Ŷ�� ������,

				switch( pPacket->usCmd ) {

				case AUTHMSG_RESPONSE_FRONTAUTH:
					{
						g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Msg=Recv AUTHMSG_RESPONSE_FRONTAUTH");

//						printf( "���������� ���� ���� ��Ŷ ����!\n" );
						sResponse_FrontAuth *pRecvMsg = (sResponse_FrontAuth *)pPacket;
						if(pRecvMsg->packetHeader.usSize != sizeof(sResponse_FrontAuth))
						{
							g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sResponse_FrontAuth PacketSize Error",
											pRecvMsg->packetHeader.usSize, sizeof(sResponse_FrontAuth));
							break;
						}
						
						printf( "UserId = %s , %d , %d \n", pRecvMsg->userid,pRecvMsg->usFrontCharID, pRecvMsg->siAuthKey );

						sResponse_LogIn sendMsg;

						sendMsg.packetHeader.usSize = sizeof( sendMsg );
						sendMsg.packetHeader.usCmd	= FRONTMSG_RESPONSE_LOGIN;

						sendMsg.usResult	= pRecvMsg->usResult;
						sendMsg.siAuthKey	= pRecvMsg->siAuthKey;

						// �ؽ� ä�θ��� ���� IDüũ -�ؽ��� DB���� ID�� ��ȯ�Ǿ� ���;� �Ѵ�.
						memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
						sendMsg.szBlockReason[ 19 ] = NULL;
						
						sendMsg.siGameMasterLevel	= pRecvMsg->siGameMasterLevel;
						sendMsg.siAccountStatus		= pRecvMsg->siAccountStatus;

						sendMsg.siBlockMode		= pRecvMsg->siBlockMode;
						sendMsg.siBlockYear		= pRecvMsg->siBlockYear;
						sendMsg.siBlockMonth	= pRecvMsg->siBlockMonth;
						sendMsg.siBlockDay		= pRecvMsg->siBlockDay;
						sendMsg.siBlockHour		= pRecvMsg->siBlockHour;
						sendMsg.siBlockMinute	= pRecvMsg->siBlockMin;
						
						memcpy( sendMsg.szBlockReason, pRecvMsg->szBlockReason, 30 );
						sendMsg.szBlockReason[ 29 ] = NULL;

						sendMsg.bAlreadyMakeCharSwitch = pRecvMsg->bAlreadyMakeCharSwitch;

						memcpy( sendMsg.szServerName, pRecvMsg->szServerName, 20 );
						sendMsg.szServerName[ 19 ] = NULL;

						sendMsg.m_uiRealAge		= pRecvMsg->m_uiRealAge;

						cClient *pClient = g_fcp.m_SF.GetPerson( pRecvMsg->usFrontCharID );

						if( pClient == NULL )													break;
						if( pClient->GetSession() == NULL )										break;
						if( pClient->GetSession()->GetState() != SESSION_STATE_ESTABLISHED )	break;

						UI16 usUnique = 0;

						EnterCriticalSection( &pClient->m_cs );

						usUnique = pClient->m_siUnique;

						LeaveCriticalSection( &pClient->m_cs );

						if( usUnique != pRecvMsg->usPacketUnique )								break;

						pClient->GetSendBuffer()->Write( (BYTE *)&sendMsg );
//						printf( "Ŭ���̾�Ʈ�� �α��� ���� ��Ŷ ����\n" );

						g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Msg=Send FRONTMSG_RESPONSE_LOGIN");
					}
					break;

				case AUTHMSG_RESPONSE_FRONTJOINGAME:
					{
						g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Msg=Recv AUTHMSG_RESPONSE_FRONTJOINGAME");

//						printf( "���������� ���� ���Ӱ��� ��Ŷ ����\n" );
						sResponse_FrontJoinGame *pRecvMsg = (sResponse_FrontJoinGame *)pPacket;

						if(pRecvMsg->packetHeader.usSize != sizeof(sResponse_FrontJoinGame))
						{
							g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sResponse_FrontJoinGame PacketSize Error",
								pRecvMsg->packetHeader.usSize, sizeof(sResponse_FrontJoinGame));
							break;
						}

						sResponse_JoinGame sendMsg;

						sendMsg.packetHeader.usCmd = FRONTMSG_RESPONSE_JOINGAME;
						sendMsg.packetHeader.usSize = sizeof( sendMsg );

						sendMsg.siResult = pRecvMsg->siResult;

						cClient *pClient = g_fcp.m_SF.GetPerson( pRecvMsg->usFrontCharID );

						if( pClient == NULL )													break;
						if( pClient->GetSession() == NULL )										break;
						if( pClient->GetSession()->GetState() != SESSION_STATE_ESTABLISHED )	break;

						UI16 usUnique = 0;

						LeaveCriticalSection( &pClient->m_cs );

						usUnique = pClient->m_siUnique;

						LeaveCriticalSection( &pClient->m_cs );

						if( usUnique != pRecvMsg->usPacketUnique ) break;

						pClient->GetSendBuffer()->Write( (BYTE *)&sendMsg );

						g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Msg=Send FRONTMSG_RESPONSE_JOINGAME");

					}
					break;

				}

				// ó�� �� ��Ŷ�� ���ۿ��� �����
				m_pAuthSession->GetRecvBuffer()->RemoveFirstPacket();
			}
		}
	}
}
