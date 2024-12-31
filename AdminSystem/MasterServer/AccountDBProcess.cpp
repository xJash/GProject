#include "MasterServer.h"
#include "AccountDBProcess.h"
#include "MasterClientProtocol.h"

#include "ITZRecvBuffer.h"
#include "ITZSendBuffer.h"

#include "../../DBManager/AccountDBManager/AccountDBMsg.h"
#include "MasterMsg.h"

#include "../../DBManager/LogDBManager/LogDBMsg.h"
#include "ToolsLog.h"

AccountDBProcess::AccountDBProcess()
{
	m_pAccountDBSession = NULL;

	m_accountDBManagerIP[ 0 ] = NULL;
}

AccountDBProcess::~AccountDBProcess()
{

}

void AccountDBProcess::Init( char *ip, UI16 usPort )
{
	m_sf.CreateFactory( &m_sm, 2, 1000 * 1000, 1000 * 1000 );

	m_pAccountDBSession = m_sm.GetSession( 0 );

	m_iocp.CreateIOCP( &m_sm, 1 );

	strcpy( m_accountDBManagerIP, ip );
	m_accountDBManagerPort = usPort;
}

void AccountDBProcess::Run()
{
	m_sm.Update();

	FILE*	fp = NULL;

	// ������ ������� ���� �����̸�,
	if( m_pAccountDBSession->GetState() == SESSION_STATE_NONE )
	{
		if( m_sm.Connect( 0, m_accountDBManagerIP, m_accountDBManagerPort ) == m_pAccountDBSession ) {
			printf( "Connect to AccontDBManager [SUCCESS]\n" );
		} else {
			printf( "Trying to connect to AccontDBManager..\n" );
		}		
	} 
	// ������ ���������� ����� �����̸�,
	else if( m_pAccountDBSession->GetState() == SESSION_STATE_ESTABLISHED )
	{

		// ���ۿ��� ��Ŷ�� �ϳ� �����´�
		sPacketHeader *pPacket = (sPacketHeader *)m_pAccountDBSession->GetRecvBuffer()->GetFirstPacket();
			
		if( pPacket != NULL ) {										
			// ��Ŷ�� ������,

			switch( pPacket->usCmd ) {
			case DBMSG_RESPONSE_ADMINLOGIN:
				{
					sDBResponse_AdminLogin *pRecvMsg = (sDBResponse_AdminLogin *)pPacket;
				
					fp = fopen("adminlogin.log", "a");
					if(fp)		{	fprintf(fp, "recv sDBResponse_AdminLogin : pRecvMsg->usMasterCharID:%d, pRecvMsg->usResult:%d, pRecvMsg->userid:%s\n"
							, pRecvMsg->usMasterCharID, pRecvMsg->usResult, pRecvMsg->userid);	fclose(fp);		}
					
					cClient *pClient = g_mcp.m_SF.GetPerson( pRecvMsg->usMasterCharID );
					
					fp = fopen("adminlogin.log", "a");
					if(fp)		{	fprintf(fp, "pClient = %x\n", pClient);	fclose(fp);		}

					if( pClient ) 
					{
						fp = fopen("adminlogin.log", "a");
						if(fp)		{	fprintf(fp, "pClient->CharID = %d\n", pClient->GetCharID());	fclose(fp);		}

						sResponse_GMCLogin sendMsg;

						sendMsg.usResult = pRecvMsg->usResult;

						if( pRecvMsg->usResult > 0 )
						{
							InterlockedExchange( (LPLONG)&pClient->m_bLoginOK, TRUE );
							pClient->m_nMasterLevel = pRecvMsg->usResult;
#ifdef _CHINA
							sDBRequest_ToolsLog clSendMsg( "NULL", "GMTool LogIn", pRecvMsg->userid, "", "GMTool LogIn" );
							g_ToolsLog.SendMsg( (sPacketHeader *)&clSendMsg );
#endif
						}
						else
						{
							//	������ ���� �ȴٸ� �ӽ������ ���̵� ����
							ZeroMemory(pClient->m_szID,ConstIDSize * sizeof(TCHAR));
						}

						pClient->GetSendBuffer()->Write( (BYTE *)&sendMsg );

						fp = fopen("adminlogin.log", "a");
						if(fp)		{	fprintf(fp, "send sResponse_GMCLogin\n");	fclose(fp);		}
					}

				}
				break;

			case DBMSG_RESPONSE_NEWCHARNUM:
				{
					sDBResponse_NewCharNum *pRecvMsg = (sDBResponse_NewCharNum *)pPacket;

					g_serverinfo.Wait();
			
					for( int i = 0; i < pRecvMsg->siCount; ++i ) {
						g_serverinfo.m_siNewCharNum[ i ] = pRecvMsg->siNewCharNum[ i ];
						g_serverinfo.m_siDelCharNum[ i ] = pRecvMsg->siDelCharNum[ i ];
					}

					g_serverinfo.Release();
				}
				break;
			}

			// ó�� �� ��Ŷ�� ���ۿ��� �����
			m_pAccountDBSession->GetRecvBuffer()->RemoveFirstPacket();
		}

	}

}