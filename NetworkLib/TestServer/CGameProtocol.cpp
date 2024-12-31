#include "CGameProtocol.h"
#include "msgType.h"

CGameProtocol::CGameProtocol()
{

	m_SF.CreateFactory( GetSessionManager(), 1000, 30000, 30000 );
	
	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), 4010 );

}

CGameProtocol::~CGameProtocol()
{

}

void CGameProtocol::LogOut( ITZSession *pSession )
{
	MessageBox( 0, "�α׾ƿ�!", "", 0 );
}


void CGameProtocol::SessionProc( ITZSession *pSession )
{

	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );		
																							
	if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������

	
	// ��Ŷ Ŀ�ǵ忡 ���� ó��
	switch( pPacket->usCmd ) {

	case MSG_REQUEST_TEST1:
		{

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_Test1	*pRecvMsg = (sRequest_Test1 *)pPacket;

			// ó��
			MessageBox( 0, "MSG_REQUEST_TEST1 ����!", "", 0 );

			// ���� ������

			sResponse_Test1	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = MSG_RESPONSE_TEST1;

			pSession->GetSendBuffer()->Write( (char *)&sendMsg );
		}
		break;

	case MSG_REQUEST_TEST2:
		{

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_Test2	*pRecvMsg = (sRequest_Test2 *)pPacket;

			// ó��
			MessageBox( 0, "MSG_REQUEST_TEST2 ����!", "", 0 );

			// ���� ������
			sResponse_Test2	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = MSG_RESPONSE_TEST2;

			pSession->GetSendBuffer()->Write( (char *)&sendMsg );
		}

		break;
	}

	pSession->GetRecvBuffer()->RemoveFirstPacket();						// ó�� �� ��Ŷ�� ���ۿ��� �����

}