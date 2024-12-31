#include "FrontClientProtocol.h"
#include "AuthProcess.h"
#include "Log.h"
#include "../../GoonZuWorld/Apex/gamecode.h"

FrontClientProtocol::FrontClientProtocol()
{

}


FrontClientProtocol::~FrontClientProtocol()
{

}	


void FrontClientProtocol::Init(UI16 siListenPort)
{

	m_SF.CreateFactory( GetSessionManager(), MAX_USER_CONNECTION, 200 * 1000, 200 * 1000 );

	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), siListenPort );

	SetFPS( 200 );

	m_usUniqueCount = 1;

	g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "FrontClientProtocol::Init(%d)", siListenPort );

	// m_szLogFileName[ 0 ] = NULL;
}

void FrontClientProtocol::LogOut( ITZSession *pSession )
{

}

void FrontClientProtocol::SessionProc( ITZSession *pSession )
{

	if( GetTickCount() - ((cClient *)pSession->GetPerson())->m_dwRefreshTick >= 3000 ) {

		EnterCriticalSection( &g_cs );

		((cClient *)pSession->GetPerson())->m_dwRefreshTick = GetTickCount();

		// �������� ��Ŷ ������

		sNotify_WorldRefreshAll *pSendMsg;
		pSendMsg = (sNotify_WorldRefreshAll *)m_buf;
		g_worldlist.MakeWorldRefreshAllPacket( pSendMsg );

		LeaveCriticalSection( &g_cs );

		pSession->GetSendBuffer()->Write( (BYTE *)pSendMsg );

	}

	if( GetTickCount() - ((cClient *)pSession->GetPerson())->m_dwLastTick >= 3 * 60 * 1000 ) {

		g_CLogPrint.WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Msg=Close Client;CharID=%d", pSession->GetPerson()->GetCharID());

		pSession->CloseSocket();
		return;
	}

	// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
	sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );

	if( pPacket == NULL ) 
		return;										// ��Ŷ�� ������ ������

	// ���׽�Ʈ�� �׳� ������.
	if( FRONTMSG_REQUEST_PINGTEST == pPacket->usCmd )
	{
		((cClient *)pSession->GetPerson())->m_dwLastTick = GetTickCount();

		//	pPacket = (sPacketHeader *)m_encrBuf;
	}
	else
	{
		if( pSession->GetEncrypt()->Decode( (UI08*)pPacket, m_encrBuf ) == FALSE ) 
		{
			g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Msg=Msg Decode Error;CharID=%d", pSession->GetPerson()->GetCharID());

			// �߸��� ��Ŷ�̸�, ��ȣȭ ���� 
			pSession->CloseSocket();
			return;
		}

		((cClient *)pSession->GetPerson())->m_dwLastTick = GetTickCount();

		pPacket = (sPacketHeader *)m_encrBuf;
	}

	// ��Ŷ Ŀ�ǵ忡 ���� ó��
	switch( pPacket->usCmd ) 
	{
	case FRONTMSG_REQUEST_PATCHINFO:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_PATCHINFO" );

			EnterCriticalSection( &g_cs );

			sRequest_PatchInfo	*pRecvMsg = (sRequest_PatchInfo	*)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_PatchInfo))
			{
				LeaveCriticalSection( &g_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_PatchInfo PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_PatchInfo));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

            sResponse_PatchInfo	sendMsg;

			ZeroMemory( &sendMsg, sizeof( sResponse_PatchInfo ) );

			sendMsg.packetHeader.usCmd = FRONTMSG_RESPONSE_PATCHINFO;
			sendMsg.packetHeader.usSize = sizeof( sendMsg );

			sendMsg.uiCount = 0;
			for( UI32 i = 0; i < g_versionCount; ++i )
			{
				if( pRecvMsg->uiCurrentVersion < g_versionList[ i ] ) {

					sendMsg.uiVersionHistory[ sendMsg.uiCount++ ] = g_versionList[ i ];

					// ��ġ���α׷� ������Ʈ
					if( g_versionList[ i ] == g_patchInfo.versionChangeUp ) {
						break;
					}

					if( sendMsg.uiCount >= 99 ) break;
				}

			}

			g_patchselect = 1 - g_patchselect;

			//dns
			strcpy( sendMsg.szAddr, g_patchInfo.addr[ 0 ] );
			strcpy( sendMsg.szPath, g_patchInfo.dir[ 0 ] );
			strcpy( sendMsg.szID, g_patchInfo.id[ 0 ] );
			strcpy( sendMsg.szPW, g_patchInfo.pw[ 0 ] );
			sendMsg.usPort = 21;

			//dns �ȵɶ��� ���� IP
			strcpy( sendMsg.szAddr_2, g_patchInfo.addr[ 1 ] );
			strcpy( sendMsg.szPath_2, g_patchInfo.dir[ 1 ] );
			strcpy( sendMsg.szID_2, g_patchInfo.id[ 1 ] );
			strcpy( sendMsg.szPW_2, g_patchInfo.pw[ 1 ] );
			sendMsg.usPort_2 = 21;

			LeaveCriticalSection( &g_cs );

			pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send FRONTMSG_RESPONSE_PATCHINFO" );

		}

		break;
		
	case FRONTMSG_REQUEST_KOREA_LOGIN:	//	[��ȣ_NHN->NDOORS] �̰� ���� ����S ���� ��������
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_KOREA_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_LogIn	*pRecvMsg = (sRequest_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=FRONTMSG_REQUEST_KOREA_LOGIN PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_KOREA_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_KOREA_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );
			//#endif
		}
		break;


	case FRONTMSG_REQUEST_LOGIN:
		{
/*#ifdef _CHINA
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_LogIn	*pRecvMsg = (sRequest_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// ���� ������ ���� ��û �ϱ�
			sRequest_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			TCHAR	userID[Net_Packet_Max_Size] = {'\0'};
			memset( pClient->m_GameServer.m_server_buf, 0, Net_Packet_Max_Size );
			memcpy( pClient->m_GameServer.m_server_buf, pRecvMsg->userid, Net_Packet_Max_Size );
			
			pClient->m_GameServer.decrypt_data_with_PrivateKey_Key1( userID, Net_Packet_Max_Size );

			TCHAR	userPassWord[Net_Packet_Max_Size] = {'\0'};
			memset( pClient->m_GameServer.m_server_buf, 0, Net_Packet_Max_Size );
			memcpy( pClient->m_GameServer.m_server_buf, pRecvMsg->userpw, Net_Packet_Max_Size );
			pClient->m_GameServer.decrypt_data_with_PrivateKey_Key1( userPassWord, Net_Packet_Max_Size );

			StringCchCopy( sendMsg.userid, 20, userID );
			sendMsg.userid[ 19 ] = NULL;
			StringCchCopy( sendMsg.userpw, 20, userPassWord );
			sendMsg.userpw[ 19 ] = NULL;

			bool isCorrect = true;

			for ( int i=0; i<strlen(sendMsg.userid) ; ++i )
			{
				if( ( ( sendMsg.userid[ i ] >= '0' && sendMsg.userid[ i ] <= '9' ) || 
					( sendMsg.userid[ i ] >= 'a' && sendMsg.userid[ i ] <= 'z' ) ||
					( sendMsg.userid[ i ] >= 'A' && sendMsg.userid[ i ] <= 'Z' ) ||
					sendMsg.userid[ i ] == '_' 
					) == false ) 
				{
					LeaveCriticalSection( &pClient->m_cs );
					g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "ID Error " );
					// �߸��� ���̵��� ��� ���� ����/
					pSession->CloseSocket();
					isCorrect = false;
					break;
				}
			}

			for ( int i=0; i<strlen(sendMsg.userpw) ; ++i )
			{
				if( ( ( sendMsg.userpw[ i ] >= '0' && sendMsg.userpw[ i ] <= '9' ) || 
					( sendMsg.userpw[ i ] >= 'a' && sendMsg.userpw[ i ] <= 'z' ) ||
					( sendMsg.userpw[ i ] >= 'A' && sendMsg.userpw[ i ] <= 'Z' ) ||
					sendMsg.userid[ i ] == '_'
					) == false ) 
				{
					LeaveCriticalSection( &pClient->m_cs );
					g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "PW Errors ");
					// �߸��� ���̵��� ��� ���� ����/
					pSession->CloseSocket();
					isCorrect = false;
					break;
				}
			}

			if ( !isCorrect )
			{
				break;
			}
			
			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_FRONTAUTH" );
#else*/
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_LogIn	*pRecvMsg = (sRequest_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );
//#endif
		}
		break;
//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�.
	case FRONTMSG_REQUEST_HANGAMEJP_LOGIN:
		{
			// �Ϻ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "JAPAN" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_HANGAMEJP_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_HANGAMEJP_LogIn	*pRecvMsg = (sRequest_HANGAMEJP_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_HANGAMEJP_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_HANGAMEJP_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_HANGAMEJP_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_HANGAMEJP_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_HANGAMEJP_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_HANGAMEJP_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );
		}
		 break;
	case FRONTMSG_REQUEST_GAMANIAJP_LOGIN:
		{
			// �Ϻ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "JAPAN" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_GAMANIAJP_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_GAMANIAJP_LogIn	*pRecvMsg = (sRequest_GAMANIAJP_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_GAMANIAJP_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_GAMANIAJP_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_GAMANIAJP_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_GAMANIAJP_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GAMANIAJP_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_GAMANIAJP_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );
		}
		 break;
	case FRONTMSG_REQUEST_GAMEPOTJP_LOGIN:
		{
			// �Ϻ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "JAPAN" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_GAMEPOTJP_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_GAMEPOTJP_LogIn	*pRecvMsg = (sRequest_GAMEPOTJP_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_GAMEPOTJP_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_GAMEPOTJP_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_GAMEPOTJP_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_GAMEPOTJP_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GAMEPOTJP_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_GAMEPOTJP_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );

		}
		 break;
	case FRONTMSG_REQUEST_NDEJP_LOGIN:
		{
			// �Ϻ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceMode, "REAL") == 0 && strcmp( g_szServiceArea, "JAPAN" ) )		break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_NDEJP_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_NDEJP_LogIn	*pRecvMsg = (sRequest_NDEJP_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_NDEJP_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_NDEJP_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_NDEJP_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_NDEJP_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_NDEJP_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_NDEJP_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );

		}
		 break;
	case FRONTMSG_REQUEST_NEXONJP_LOGIN:
		{
			// �Ϻ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "JAPAN" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_NEXONJP_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_NEXONJP_LogIn	*pRecvMsg = (sRequest_NEXONJP_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_NEXONJP_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_NEXONJP_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_NEXONJP_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_NEXONJP_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_NEXONJP_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 512 );
			sendMsg.userid[ 511] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_NEXONJP_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );

		}
		 break;		 
//---------------------------------------------------------
	case FRONTMSG_REQUEST_JOINGAME:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_JOINGAME" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			sRequest_JoinGame	*pRecvMsg = (sRequest_JoinGame *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_JoinGame))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_JoinGame PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_JoinGame));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			

			// ���� ������ ���� ��û �ϱ� 
			sRequest_FrontJoinGame	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_FRONTJOINGAME;


			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			// ip
			memcpy( sendMsg.szIP, pSession->GetIP(), 20 );
			sendMsg.szIP[ 19 ] = NULL;

			// cookie
			memcpy( sendMsg.cookie, pRecvMsg->cookie, 20 );
			sendMsg.cookie[ 19 ] = NULL;

			// id
			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			// pw
			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_FRONTJOINGAME" );

		}
		break;

	case FRONTMSG_REQUEST_NOTICE:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_NOTICE" );

			EnterCriticalSection( &g_cs );

			// ���� ������
			sResponse_Notice sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sPacketHeader ) + 16;
			sendMsg.packetHeader.usCmd = FRONTMSG_RESPONSE_NOTICE;

			sendMsg.text[ 0 ] = NULL;

			LeaveCriticalSection( &g_cs );

			pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send FRONTMSG_RESPONSE_NOTICE" );

		}
		break;

	case FRONTMSG_REQUEST_WORLDLIST:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_WORLDLIST" );

			EnterCriticalSection( &g_cs );

			sResponse_WorldList *pSendMsg;

			pSendMsg = (sResponse_WorldList *)m_buf;

			g_worldlist.MakeWorldListPacket( pSendMsg );

			LeaveCriticalSection( &g_cs );

			pSession->GetSendBuffer()->Write( (BYTE *)pSendMsg );	

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send sResponse_WorldList" );

#ifdef USE_PROMOTOR_FRONT_SERVER
			sRequest_WorldList* pRecvMsg = (sRequest_WorldList*)pPacket;

			clPromoterInfo PromoterInfo;
			PromoterInfo.SetOperatorType(clPromoterInfo::GET_PROMOTER_INFO);
			PromoterInfo.SetSession( pSession );
			PromoterInfo.SetName( pRecvMsg->szAccountID );
			g_clPromoterManager.Push( PromoterInfo );
#endif
		}
		break;

	case FRONTMSG_HEARTBEAT:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "FRONTMSG_HEARTBEAT" );
		}
		break;

	case FRONTMSG_REQUEST_HANAUTH_LOGIN:
		{
			// �ѱ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "KOREA" ) != 0 )		break;

			//// �̱��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			//if( strcmp( g_szServiceArea, "USA" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_HANAUTH_LOGIN" );

/*#if defined(_KOREA)
			// KOREA�� HANAUTH�� ����Ѵ�.
#elif defined(_USA)
			// USA��   HANAUTH�� ����Ѵ�.
#else
			//g_CLogPrint.FilePrint( "FrontCMDError.txt", "%d", pPacket->usCmd );
			g_CLogPrint.WriteFileLog( "ErrorLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_HANAUTH_LOGIN is now returned" );

			return;
#endif*/
			printf( "HanAuth Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();
			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_HanAuth_LogIn	*pRecvMsg = (sRequest_HanAuth_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_HanAuth_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_HanAuth_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_HanAuth_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_HanAuth_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_HANAUTH_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.authstring, pRecvMsg->authstring, 2048 );
			sendMsg.userid[ 2047 ] = NULL;

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_HANAUTH_FRONTAUTH" );
		}
		break;

	//KHY - 0204 -  �߱� PurpleAuth ���� ���
	case FRONTMSG_REQUEST_PORTEAUTH_LOGIN:
		{
			// �ѱ��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "NHNCHINA" ) != 0 )		break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_PORTEAUTH_LOGIN" );

			printf( "PorteAuth Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();
			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_PorteAuth_LogIn	*pRecvMsg = (sRequest_PorteAuth_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_PorteAuth_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_PorteAuth_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_HanAuth_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_PorteAuth_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_PORTEAUTH_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.authstring, pRecvMsg->authstring, 2048 );
			sendMsg.userid[ 2047 ] = NULL;

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send FRONTMSG_REQUEST_PORTEAUTH_LOGIN" );
		}
		break;
	case FRONTMSG_REQUEST_TAIWAN_LOGIN:
		{
			// �븸�� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "TAIWAN" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_TAIWAN_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_Taiwan_LogIn	*pRecvMsg = (sRequest_Taiwan_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_Taiwan_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
											pRecvMsg->packetHeader.usSize, sizeof(sRequest_Taiwan_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_Taiwan_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_TAIWAN_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.gameaccount, pRecvMsg->szGameAccount, sizeof(sendMsg.gameaccount) );
			sendMsg.gameaccount[ sizeof(sendMsg.gameaccount) - 1 ] = NULL;

			memcpy( sendMsg.onetimepassword, pRecvMsg->szOneTimePassword, sizeof(sendMsg.onetimepassword) );
			sendMsg.onetimepassword[ sizeof(sendMsg.onetimepassword) - 1 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), sizeof(sendMsg.userIP) );
			sendMsg.userIP[ sizeof(sendMsg.userIP) - 1 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, sizeof(sendMsg.macaddress) );
			sendMsg.macaddress[ sizeof(sendMsg.macaddress) - 1 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_TAIWAN_FRONTAUTH %s %s", sendMsg.gameaccount , sendMsg.onetimepassword  );
//#endif
		}
		break;

	// PCK : IOVATION ���� ��û�ϱ� (2009.02.03)
	case FRONTMSG_REQUEST_ENGLISH_LOGIN:
		{
			// �۷ι��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "ENGLISH" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_ENGLISH_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_English_LogIn	*pRecvMsg = (sRequest_English_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_English_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
											pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_English_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_ENGLISH_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			memcpy( sendMsg.Blackbox, pRecvMsg->Blackbox, 2048 );
			sendMsg.macaddress[ 2047 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_ENGLISH_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw );
		}
		break;
	case FRONTMSG_REQUEST_USA_LOGIN:
		{
			// USA�� �۷ι��� �̰��Ǿ���. �۷ι��� �ƴϸ� ó������ �ʴ´�. - �����ڵ�
			if( strcmp( g_szServiceArea, "ENGLISH" ) != 0 )			break;

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_USA_LOGIN" );

			printf( "Request Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_USA_LogIn *pRecvMsg = (sRequest_USA_LogIn*)pPacket;

			if( pRecvMsg->packetHeader.usSize != sizeof(sRequest_USA_LogIn) )
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
											pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_USA_FrontAuth sendMsg;

			sendMsg.packetHeader.usSize = sizeof( sendMsg );
			sendMsg.packetHeader.usCmd  = AUTHMSG_REQUEST_USA_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID  = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.authstring, pRecvMsg->authstring, sizeof(sendMsg.authstring) );

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send FRONTMSG_REQUEST_USA_LOGIN %s", sendMsg.authstring );
		}
		break;

	case FRONTMSG_REQUEST_EUROPE_LOGIN:
		{
			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Recv FRONTMSG_REQUEST_EUROPE_LOGIN" );

			printf( "Request Europe Login\n" );

			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			pClient->m_siUnique = m_usUniqueCount;
			m_usUniqueCount += 2;

			// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
			sRequest_EUROPE_LogIn	*pRecvMsg = (sRequest_EUROPE_LogIn *)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_LogIn))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_LogIn PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_LogIn));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������ ���� ��û �ϱ�
			sRequest_EUROPE_FrontAuth	sendMsg;

			sendMsg.packetHeader.usSize	= sizeof( sendMsg );
			sendMsg.packetHeader.usCmd	= AUTHMSG_REQUEST_EUROPE_FRONTAUTH;

			sendMsg.usPacketUnique = pClient->m_siUnique;
			sendMsg.usFrontCharID = (UI16)pSession->GetPerson()->GetCharID();

			memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, pSession->GetIP(), 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			LeaveCriticalSection( &pClient->m_cs );

			g_auth.m_pAuthSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );

			g_CLogPrint.WriteFileLog( "ProcessLog.txt", __FILE__, __LINE__, "Send AUTHMSG_REQUEST_EUROPE_FRONTAUTH %s %s", sendMsg.userid , sendMsg.userpw  );
		}
		break;

	case FRONTMSG_REQUEST_PINGTEST:
		{
			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			sRequest_PingTest	*pRecvMsg = (sRequest_PingTest*)pPacket;
			
			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_PingTest))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_PingTest PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_PingTest));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������
			sResponse_PingTest sendMsg;

			ZeroMemory( &sendMsg, sizeof( sResponse_PingTest ) );

			sendMsg.packetHeader.usSize = sizeof( sResponse_PingTest );
			sendMsg.packetHeader.usCmd = FRONTMSG_RESPONSE_PINGTEST;

			sendMsg.m_uiIDCType = pRecvMsg->m_uiIDCType;
			sendMsg.m_siFrontServerIndex = pRecvMsg->m_siFrontServerIndex;

			LeaveCriticalSection( &pClient->m_cs );

			pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	
		}
		break;
	case FRONTMSG_REQUEST_DIFFHELLMAN_KEY:
		{
			cClient *pClient = (cClient *)pSession->GetPerson();

			if( pClient == NULL ) break;

			EnterCriticalSection( &pClient->m_cs );

			sRequest_DiffHellManKey	*pRecvMsg = (sRequest_DiffHellManKey*)pPacket;

			if(pRecvMsg->packetHeader.usSize != sizeof(sRequest_DiffHellManKey))
			{
				LeaveCriticalSection( &pClient->m_cs );
				g_CLogPrint.WriteFileLog("ErrorLog.txt", __FILE__, __LINE__, "Recv=%d;Want=%d;Msg=sRequest_DiffHellManKey PacketSize Error",
					pRecvMsg->packetHeader.usSize, sizeof(sRequest_DiffHellManKey));
				// �߸��� �������̸� Ŭ���̾�Ʈ ���� ����
				pSession->CloseSocket();
				break;
			}

			// ���� ������
			sResponse_DiffHellManKey sendMsg;

			ZeroMemory( &sendMsg, sizeof( sResponse_DiffHellManKey ) );

			sendMsg.packetHeader.usSize = sizeof( sResponse_DiffHellManKey );
			sendMsg.packetHeader.usCmd = FRONTMSG_RESPONSE_DIFFHELLMAN_KEY;

			pClient->m_GameServer.create_c0();

			memcpy( pClient->m_GameServer.m_server_buf, pRecvMsg->tempKey, Net_Packet_Max_Size );
			pClient->m_GameServer.decrypt_a0_with_PublicKey_Key0();
			pClient->m_GameServer.create_PrivateKey_Key1_with_a0();
			pClient->m_GameServer.encrypt_c0_with_PublicKey_Key0();
			memcpy( sendMsg.tempKey, pClient->m_GameServer.m_pstPacket, pClient->m_GameServer.m_pstPacket->sPacketSize );
			//	g_CLogPrint.FilePrint( "sPacketSize.txt", "%d", m_GameServer.m_pstPacket->sPacketSize );

			LeaveCriticalSection( &pClient->m_cs );

			pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );
		}
		break;
	default:
		{
//			g_CLogPrint.FilePrint( "FrontCMDError.txt", "%d", pPacket->usCmd );
		}
		break;
	}

	pSession->GetRecvBuffer()->RemoveFirstPacket();
}

void FrontClientProtocol::Update()
{
	DWORD tick = GetTickCount();

	InterlockedExchange( (LPLONG)&g_dwClientProtocolTick, tick );
}

