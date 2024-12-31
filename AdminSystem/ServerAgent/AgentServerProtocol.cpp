#include "AgentMasterProtocol.h"
#include "AgentServerProtocol.h"
#include "SessionList.h"

#include "ServerAgent.h"

#include "../MasterServer/MasterMsg.h"

AgentServerProtocol::AgentServerProtocol()
{

}

AgentServerProtocol::~AgentServerProtocol()
{

}

void AgentServerProtocol::Init()
{

	m_SF.CreateFactory( GetSessionManager(), 20, 200000, 200000 );
	
	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), 6400 );

}

void AgentServerProtocol::Update()
{
	
}

void AgentServerProtocol::SessionProc( ITZSession *pSession )
{

	cServer *pServer = (cServer *)(pSession->GetPerson());


	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );
																							
	if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������

	// �����ͼ����� �ٷ� ���� �ؾ��� �޽����̸�,
	if( pPacket->usCmd >= 10000 ) {

		if(pPacket->usCmd >= 13000)
		{
			int a = 0;
		}
		if(pPacket->usCmd >= 13000)
		{
			int a = 0;
		}
		if( pServer->m_pMaster != NULL ) {

			if( pServer->m_pMaster->GetSession()->GetState() == SESSION_STATE_ESTABLISHED ) {

				pServer->m_pMaster->GetSession()->GetSendBuffer()->Write( (BYTE *)pPacket );
			}
		}

	} else {	

	// ��Ŷ Ŀ�ǵ忡 ���� ó��
	switch( pPacket->usCmd ) {

	case AGENTMSG_REPORT_FILEPATH:
		{
			sReportToAgent_FilePath *pRecvMsg = (sReportToAgent_FilePath *)pPacket;

			pServer->SetFilePath( pRecvMsg->szFilePath );

			g_sessionList.Wait();

			// ������ ����Ʈ���� ���������ϸ��� ���� ���� ã�Ƽ� �����ش�
			for( int i = 0; i < g_amp.m_SF.m_siMaxSize; ++i ) {
				
				cMaster *pMaster = (cMaster *)(g_amp.GetSessionManager()->GetSession( i )->GetPerson() );

				if( pMaster->IsEqualFilePath( pRecvMsg->szFilePath ) == TRUE ) {

					pMaster->SetServer( pServer );

					pServer->SetMaster( pMaster );
					pServer->SetServerID( pMaster->GetServerID() );

					printf( "ok!!! %s\n", pServer->m_szFilePath );

				}
			}

			g_sessionList.AddServerSession( pServer, pRecvMsg->szMessage );

			g_sessionList.Release();

		}
		break;
	} // switch
	} // if

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}

