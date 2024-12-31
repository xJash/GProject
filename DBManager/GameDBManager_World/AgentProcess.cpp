#include "AgentProcess.h"
#include "GameDB.h"

#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

#include "../../AdminSystem/MasterServer/MasterMsg.h"
#include "../../NLib/NMap.h"

extern AgentProcess			g_agent;

AgentProcess::AgentProcess()
{
	m_pAgentSession = NULL;
	m_szIP[ 0 ] = NULL;

	m_bInitReady = FALSE;
}

AgentProcess::~AgentProcess()
{

}

void AgentProcess::Init( char *szIP, UI16 usPort )
{

	strcpy( m_szIP, szIP );
	m_usPort = usPort;

	m_sf.CreateFactory( &m_sm, 1, 50000, 50000 );

	ITZSession *pSession = m_sm.GetSession( 0 );

	InterlockedExchange( (LPLONG)&m_pAgentSession, (LONG)pSession );

	m_iocp.CreateIOCP( &m_sm, 1 );


}

void AgentProcess::Run()
{

	m_sm.Update();

	DWORD		currentTick;

	if( m_pAgentSession == NULL ) return;

	if( m_pAgentSession->GetState() == SESSION_STATE_NONE ) {

		if( m_sm.Connect( 0, m_szIP, m_usPort ) == m_pAgentSession ) {
			
			m_dwLastTick = GetTickCount() - AGENT_HEARTBEAT_INTERVAL;

			m_bSendFilePath = FALSE;

		} else {
		}
	} else 

	// ������Ʈ������ ���������� ����� �����̸�,
	if( m_pAgentSession->GetState() == SESSION_STATE_ESTABLISHED )
	{

		if( m_bSendFilePath == FALSE ) {

			sReportToAgent_FilePath		sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AGENTMSG_REPORT_FILEPATH;

			strcpy( sendMsg.szMessage, "GameDBManager" );

			GetModuleFileName( 0, sendMsg.szFilePath, 127 );

			m_pAgentSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			m_bSendFilePath = TRUE;
		}

		// heartbeat ������
		currentTick = GetTickCount();
		if( currentTick >= m_dwLastTick + AGENT_HEARTBEAT_INTERVAL ) {
			m_dwLastTick = currentTick;

			// �ʱ�ȭ ������ ���� �����̸� �����ͷ� �ʱ�ȭ ������ ��û�Ѵ�
			if( m_bInitReady == FALSE ) {
				
				//sRequest_GameDBManagerInitInfo		sendMsg;
				sRequest_GameDBManagerInitInfo_String		sendMsg;

				m_pAgentSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );
				
				// �ʱ�ȭ ���� ��û

				printf( "- Master Server�� �ʱ�ȭ ���� ��û\n" );

			} else {

				sReport_GameDBManagerHeartbeat		sendMsg;

				sendMsg.packetHeader.usCmd = MASTERMSG_REPORT_GAMEDBMANAGER_HEARTBEAT;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.dwProcessId = GetCurrentProcessId();
				sendMsg.refreshInfo.usStatus = 0;

				m_pAgentSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );				
				
			}

		}


		// ���ۿ��� ��Ŷ�� �ϳ� �����´�
		sPacketHeader *pPacket = (sPacketHeader *)m_pAgentSession->GetRecvBuffer()->GetFirstPacket();		
		
		if( pPacket != NULL ) {										
			// ��Ŷ�� ������,

			switch( pPacket->usCmd ) {

			case MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO:

				printf( "- Master Server�� ���� �ʱ�ȭ ���� ����\n" );

				if( m_bInitReady == FALSE ) {

					sResponse_GameDBManagerInitInfo *pRecvMsg = (sResponse_GameDBManagerInitInfo *)pPacket;
					
					
					InitServer( pRecvMsg->usGameServerListenPort,
								pRecvMsg->szGameDBIP,
								pRecvMsg->szDatabaseName,
								pRecvMsg->szUserID,
								pRecvMsg->szUserPW,
								pRecvMsg->szLogDBIP,
								pRecvMsg->szLogDatabaseName,
								pRecvMsg->szLogUserID,
								pRecvMsg->szLogUserPW,
								pRecvMsg->szLogProcedure);

					m_bInitReady = TRUE;
					
				}

				break;

			case MASTERMSG_RESPONSE_GAMEDBMANAGERINITINFO_STRING:
				{
					printf( "- Master Server�� ���� �ʱ�ȭ ���� ����\n" );

					if( m_bInitReady == FALSE ) {

						sResponse_GameDBManagerInitInfo_String *pRecvMsg = (sResponse_GameDBManagerInitInfo_String *)pPacket;

						NMapString<40, 128>		KGameDBMgrInfo;
						KGameDBMgrInfo.CreateMap( 30 );
						KGameDBMgrInfo.Parse( pRecvMsg->szMapString );

						StringCchCopy( g_szServiceArea, sizeof(g_szServiceArea), KGameDBMgrInfo["ServiceArea"] );
						StringCchCopy( g_szServiceMode, sizeof(g_szServiceMode), KGameDBMgrInfo["ServiceMode"] );

						StringCchCopy( g_BillingServerIP, sizeof(g_BillingServerIP), KGameDBMgrInfo["BillingServerIP"]);
						g_BillingServerPort = _ttoi(KGameDBMgrInfo["BillingServerPort"]);
						g_BillingTimeOut	= _ttoi(KGameDBMgrInfo["BillingTimeOut"]);

						//// �ѱ� NHN
						//if( _tcscmp( g_szServiceArea, "KOREA" ) == 0 )
						//{
						//	if( KGameDBMgrInfo["BillingMode"] == "HANGAME_BILLINGMODE_SOCKET" )
						//	{
						//		g_BillingMode	= HANGAME_BILLINGMODE_SOCKET;
						//	}
						//	else if( KGameDBMgrInfo["BillingMode"] == "HANGAME_BILLINGMODE_NEVERBILL" )
						//	{
						//		g_BillingMode	= HANGAME_BILLINGMODE_NEVERBILL;
						//	}
						//}
						//// �̱� NHN
						//else if( _tcscmp( g_szServiceArea, "KOREA" ) == 0 )
						//{
						//}

						InitServer( _ttoi(KGameDBMgrInfo["GameServerListenPort"]),
									KGameDBMgrInfo["GameDBIP"],
									KGameDBMgrInfo["DatabaseName"],
									KGameDBMgrInfo["UserID"],
									KGameDBMgrInfo["UserPW"],
									KGameDBMgrInfo["LogDBIP"],
									KGameDBMgrInfo["LogDatabaseName"],
									KGameDBMgrInfo["LogUserID"],
									KGameDBMgrInfo["LogUserPW"],
									KGameDBMgrInfo["LogProcedure"]);

						m_bInitReady = TRUE;

					}
				}
				break;

			case MASTERMSG_COMMAND_GAMEDBMANAGER_OFF:
				{
					g_bRun = FALSE;
				}
				break;
			}

			m_pAgentSession->GetRecvBuffer()->RemoveFirstPacket();

		}

	}

}

void RichODBC_ErroyQuery(const char* pszErrorQuery)
{
	ITZSession* pAgentSession = g_agent.GetAgentSession();
	if( pAgentSession == NULL )										return;
	if( pAgentSession->GetState() != SESSION_STATE_ESTABLISHED )	return;

	NTCHARString128		kErrorQuery(pszErrorQuery);

	NMapString<32, 128>	kMap;
	kMap.CreateMap( 20 );

	kMap["DatabaseName"] = g_dbname;
	kMap["ErrorQuery"] = kErrorQuery;

	NTCHARString1024	kMsg;
	kMap.ToString(kMsg);
    
	sRequest_GameDBMgr_ErroyQuery_String clMsg( kMsg );
	pAgentSession->GetSendBuffer()->Write( (BYTE*)&clMsg );
}