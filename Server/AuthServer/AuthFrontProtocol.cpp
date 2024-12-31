#include <windows.h>
/*#include "Wininet.h"

#include <comutil.h>
#include <tchar.h>
#include <atlcomcli.h>

#include "C:\Program Files\MSSOAP\Inc\mssoap30.h"
#pragma comment(lib, "C:\\Program Files\\MSSOAP\\Lib\\mssoap30.lib") 
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "comsupp.lib")
*/

#include "AuthUserList.h"
#include "AuthFrontProtocol.h"
#include "AccountDBProcess.h"

#include "../FrontServer/Log.h"

#include "NUtil.h"

#ifdef USE_HANAUTH
	// - NHN ASM -
	#include "./HanAuth/HanAuthForSvr.h"
	// - NHN ASM -
#endif //USE_HANAUTH

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	#include "./Porte/PorteAuthForSvr.h"	
	using namespace Porte::PorteAuthSystem;
#endif // USE_PORTEAUTH

//KHY - 0218 - �߱� NHN �Ƿε� ��� ���� - ��������� ����Ǿ�߸� �Ѵ�.
#ifdef USE_HANANTITOXIC
	#include "./HanAntiToxic/HanAntiToxic.h"

	extern TCHAR g_HanSID[MAX_SID_BUF];
	extern BOOL g_Tired;
#endif


extern CLogPrint			g_CLogPrint;
extern BOOL					g_bRun;

#include "./JapanAuth/JapanAuth.h"

int CALLBACK JapanAuthCallBackFunc(AuthInfo info, int nRet);

AuthFrontProtocol::AuthFrontProtocol()
{

}

AuthFrontProtocol::~AuthFrontProtocol()
{
	JapanAuthShutdown();
}

void AuthFrontProtocol::Init(UI16 usFrontServerListenPort)
{
	m_SF.CreateFactory( GetSessionManager(), 1, 20 * 1000 * 1000, 20 * 1000 * 1000 );

	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), usFrontServerListenPort );

	SetFPS( 200 );

	JapanAuthInit(20, JapanAuthCallBackFunc);
}


void AuthFrontProtocol::LogOut( ITZSession *pSession )
{

}

void AuthFrontProtocol::SessionProc( ITZSession *pSession )
{

	int count = pSession->GetRecvBuffer()->GetPacketCount();

	for( int i = 0; i < count; ++i ) {

		// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
		sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );
																								
		if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������
		
		// ��Ŷ Ŀ�ǵ忡 ���� ó��
		switch( pPacket->usCmd ) {

		case AUTHMSG_REQUEST_FRONTAUTH:
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_FrontAuth	*pRecvMsg = (sRequest_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;
				
				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );

			}
			break;

		case AUTHMSG_REQUEST_KOREA_FRONTAUTH:		// [��ȣ_NHN->NDOORS] Korea ����
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_FrontAuth	*pRecvMsg = (sRequest_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );

			}
			break;
//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�.
		case AUTHMSG_REQUEST_HANGAMEJP_FRONTAUTH:
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_HANGAMEJP_FrontAuth	*pRecvMsg = (sRequest_HANGAMEJP_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;
				
				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );

			}
			break;
		case AUTHMSG_REQUEST_GAMANIAJP_FRONTAUTH:
			{
				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_GAMANIAJP_FrontAuth	*pRecvMsg = (sRequest_GAMANIAJP_FrontAuth *)pPacket;

				// -  �����Ͼƴ� ������ ������, @GA�� ���� ������. 
				TCHAR	GA_userid[ 20 ] = {'0',};

				// @�ۺ��� �� ���� �Լ�.
				DeltPublisherID(pRecvMsg->userid ,GA_userid);
				
				//int ret  = HttpsPostAuth(GA_userid , pRecvMsg->userpw); 
				AuthInfo info;
				info.Set(GA_userid, pRecvMsg->userpw, pRecvMsg->userIP, pRecvMsg->macaddress);
				info.m_usPacketUnique	= pRecvMsg->usPacketUnique;
				info.m_usFrontCharID	= pRecvMsg->usFrontCharID;

				int ret = JapanAuth_GamaniaAuth(info);	// �����Ͼƴ� ��ü ������ �ʿ��ϴ�.

				if( ret == 0)	// ���� ��⿡�� ����!
				{
					// FrontServer�� ���� ���� ����
					sResponse_FrontAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_FRONTAUTH;

					// GAMANIAJP ��������
					sendMsg.usResult = 14;

					sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

					sendMsg.siAuthKey = 0;

					sendMsg.siGameMasterLevel = 0;

					sendMsg.siBlockMode = 0;
					sendMsg.siBlockYear = 0;
					sendMsg.siBlockMonth = 0;
					sendMsg.siBlockDay = 0;
					sendMsg.siBlockHour = 0;
					sendMsg.siBlockMin = 0;

					sendMsg.szBlockReason[ 0 ] = NULL;
					sendMsg.bAlreadyMakeCharSwitch = 0;
					sendMsg.szServerName[ 0 ] = NULL;

					sendMsg.siAccountStatus = 0;

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED) 
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

					// �α� ���
					g_CLogPrint.WriteFileLog("GAMANIAJP_Error.txt", __FILE__, __LINE__, "[FRONTAUTH] GAMANIAJPAuthForServer() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);

				}

			}
			break;

		case AUTHMSG_REQUEST_GAMEPOTJP_FRONTAUTH:
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_GAMEPOTJP_FrontAuth	*pRecvMsg = (sRequest_GAMEPOTJP_FrontAuth *)pPacket;

				//int ret = SoapAuth(pRecvMsg->userid , pRecvMsg->userpw ,pRecvMsg->userIP ); 
				AuthInfo info;
				info.Set(pRecvMsg->userid, pRecvMsg->userpw, pRecvMsg->userIP, pRecvMsg->macaddress);
				info.m_usPacketUnique	= pRecvMsg->usPacketUnique;
				info.m_usFrontCharID	= pRecvMsg->usFrontCharID;

				int ret = JapanAuth_GamepotAuth(info);

				if(ret == 0) // ������⿡�� ���� ����!!// �������� ��ü ������ �ʿ��ϴ�.
				{
					// FrontServer�� ���� ���� ����
					sResponse_FrontAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_FRONTAUTH;

					// GamePot ��������
					sendMsg.usResult = 15;

					sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

					sendMsg.siAuthKey = 0;

					sendMsg.siGameMasterLevel = 0;

					sendMsg.siBlockMode = 0;
					sendMsg.siBlockYear = 0;
					sendMsg.siBlockMonth = 0;
					sendMsg.siBlockDay = 0;
					sendMsg.siBlockHour = 0;
					sendMsg.siBlockMin = 0;

					sendMsg.szBlockReason[ 0 ] = NULL;
					sendMsg.bAlreadyMakeCharSwitch = 0;
					sendMsg.szServerName[ 0 ] = NULL;

					sendMsg.siAccountStatus = 0;

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED) 
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

					// �α� ���
					g_CLogPrint.WriteFileLog("GAMANIAJP_Error.txt", __FILE__, __LINE__, "[FRONTAUTH] GAMEPOTJPAuthForServer() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);

				}
			}
			break;

		case AUTHMSG_REQUEST_NDEJP_FRONTAUTH:
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_NDEJP_FrontAuth	*pRecvMsg = (sRequest_NDEJP_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;
				
				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );

			}
			break;
		case AUTHMSG_REQUEST_NEXONJP_FRONTAUTH:  // �ؽ� �� ���� �� �� ����.
			{

				printf( "Request user auth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_NEXONJP_FrontAuth	*pRecvMsg = (sRequest_NEXONJP_FrontAuth *)pPacket;


				// AccountDBManager�� ���� ��û -
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;


				// �ؽ���  ID�� ����ִ� ������ ���� �Ľ��� �ʿ��ϴ�.
				NexonjpIDDataDivision(pRecvMsg, &sendMsg);

				//memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				//sendMsg.userid[ 19 ] = NULL;
				//memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				//sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;
				
				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "[%s] [%s] [%s] [%s] [%s] \n",sendMsg.userid,sendMsg.requestTime,sendMsg.mkey1,sendMsg.mkey2,sendMsg.key);


				//printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );

			}
			break;

//---------------------------------------------------------
		case AUTHMSG_REQUEST_HANAUTH_FRONTAUTH:
			{
#ifdef USE_HANAUTH
				// ȭ�鿡 �α� ���
				printf( "[HANAUTH] Request user HanAuth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_HanAuth_FrontAuth	*pRecvMsg = (sRequest_HanAuth_FrontAuth *)pPacket;
				// HanAuth ���������� ��ģ��.
				char szOutBuf[ SIZE_OUTBUFFER ] = {0x00};
				int ret = HanAuthForSvr( pRecvMsg->userid, pRecvMsg->authstring, szOutBuf, SIZE_OUTBUFFER, pRecvMsg->userIP );

				// �α� ���
				g_CLogPrint.WriteFileLog("HanAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], OutBuf : [%s]", pRecvMsg->userid, szOutBuf);

				if( ret == 0 )
				{
					TCHAR szSSN[24] = { '\0', };

					SI32 siAge = HanAuthGetUserAge(szOutBuf);
					SI32 siSex = HanAuthGetUserSex(szOutBuf);

					switch(siSex)
					{
					case HAN_AUTHSVR_USER_IS_MALE:		siSex = 0;		break;
					case HAN_AUTHSVR_USER_IS_FEMALE:	siSex = 1;		break;
					default:							siSex = -1;		break;
					}
					if(siSex >= 0 && siAge > 0 && siAge < 200)
                        SSNCreate(siAge, siSex, szSSN, sizeof(szSSN));

					// AccountDBManager�� ���� ��û
					sDBRequest_IDNumGet	sendMsg;

					sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
					sendMsg.packetHeader.usSize = sizeof( sendMsg );

					sendMsg.usPacketUnique	= pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID	= pRecvMsg->usFrontCharID;

					memcpy( sendMsg.userid, 	pRecvMsg->userid, 		20 );	sendMsg.userid[ 19 ] = NULL;
					memcpy( sendMsg.userpw, 	pRecvMsg->userpw, 		20 );	sendMsg.userpw[ 19 ] = NULL;
					memcpy( sendMsg.userIP, 	pRecvMsg->userIP, 		20 );	sendMsg.userIP[ 19 ] = NULL;
					memcpy( sendMsg.macaddress, pRecvMsg->macaddress,	20 );	sendMsg.macaddress[ 19 ] = NULL;
					memcpy( sendMsg.jumin,		szSSN,					20 );	sendMsg.jumin[ 19 ] = NULL;

					g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

					// ȭ�鿡 �α� ���
					printf( "[HANAUTH] ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
				}
				// HanAuth ���� �Լ� ����
				else
				{
					// FrontServer�� ���� ���� ����
					sResponse_FrontAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_FRONTAUTH;

					// �Ѱ��� ��������
					sendMsg.usResult = 12;

					sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

					sendMsg.siAuthKey = 0;

					sendMsg.siGameMasterLevel = 0;

					sendMsg.siBlockMode = 0;
					sendMsg.siBlockYear = 0;
					sendMsg.siBlockMonth = 0;
					sendMsg.siBlockDay = 0;
					sendMsg.siBlockHour = 0;
					sendMsg.siBlockMin = 0;

					sendMsg.szBlockReason[ 0 ] = NULL;
					sendMsg.bAlreadyMakeCharSwitch = 0;
					sendMsg.szServerName[ 0 ] = NULL;

					sendMsg.siAccountStatus = 0;

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED) 
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

					// �α� ���
					g_CLogPrint.WriteFileLog("HanAuth_Error.txt", __FILE__, __LINE__, "[FRONTAUTH] HanAuthForServer() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);

					// ���α׷� ���� ����
					if( ret == HAN_AUTHSVR_DLL_UNEXPECTED)
					{
						g_bRun = FALSE;
						break;
					}
				}
#endif // USE_HANAUTH
			}
			break;

//---------------------------------------------------------
		case AUTHMSG_REQUEST_PORTEAUTH_FRONTAUTH:
			{
//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH

				// ȭ�鿡 �α� ���
				printf( "[PORTEAUTH] Request user PorteAuth from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_PorteAuth_FrontAuth	*pRecvMsg = (sRequest_PorteAuth_FrontAuth *)pPacket;
				// HanAuth ���������� ��ģ��.
				char szOutBuf[ SIZE_USERINFORMATION ] = {0x00};
				int ret = PubCheckAuth( pRecvMsg->userid, pRecvMsg->authstring, pRecvMsg->userIP, szOutBuf, sizeof(szOutBuf) );

				// �α� ���
				g_CLogPrint.WriteFileLog("PorteAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], OutBuf : [%s]", pRecvMsg->userid, szOutBuf);

				if( ret == 0 )
				{
					TCHAR szSex[8] = { '\0', };
					TCHAR szAge[8] = { '\0', };
					TCHAR szSIDval[MAX_SID_BUF] = { '\0', };
					TCHAR szTIREDval[8] = { '\0', };

					SI32 siSex = 0; 
					SI32 siAge = 0; 

					int GetValueret  = PubGetValue(szOutBuf,"SEX",szSex, sizeof(szSex));
					if(GetValueret ==0)
					{
						g_CLogPrint.WriteFileLog("PorteAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], Sex : [%s]", pRecvMsg->userid, szSex);
					}

					GetValueret  = PubGetValue(szOutBuf,"AGE",szAge, sizeof(szAge));
					if(GetValueret ==0)
					{
						g_CLogPrint.WriteFileLog("PorteAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], AGE : [%s]", pRecvMsg->userid, szAge);
					}

//KHY - 0218 - �߱� NHN �Ƿε� ��� ����
#ifdef USE_HANANTITOXIC
					// �ߵ����� ����, SID ( �ź��� ��ȣ)�� �޴´�. 
					GetValueret  = PubGetValue(szOutBuf,"SID",szSIDval, sizeof(szSIDval));
					if(GetValueret ==0)
					{						
						memcpy( g_HanSID, 	szSIDval, 	MAX_SID_BUF );
						g_CLogPrint.WriteFileLog("PorteAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], SID : [%s]", pRecvMsg->userid, szSIDval);
					}

					// �ߵ����� ����, TIRED ���� ���θ� �Ǵ��Ѵ�.
					g_Tired = FALSE;	

					GetValueret  = PubGetValue(szOutBuf,"TIRED",szTIREDval, sizeof(szTIREDval));
					if(GetValueret ==0)
					{	
						if(strcmp("Y", &szTIREDval[0]) ==0)
							 g_Tired = TRUE;							
						else
							 g_Tired = FALSE;						
						
						g_CLogPrint.WriteFileLog("PorteAuth.txt", __FILE__, __LINE__, "[FRONTAUTH] UserID : [%s], szTIREDval : [%c]", pRecvMsg->userid, szTIREDval[0]);
					}
#endif
					// AccountDBManager�� ���� ��û
					sDBRequest_IDNumGet	sendMsg;

					sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
					sendMsg.packetHeader.usSize = sizeof( sendMsg );

					sendMsg.usPacketUnique	= pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID	= pRecvMsg->usFrontCharID;

					memcpy( sendMsg.userid, 	pRecvMsg->userid, 		20 );	sendMsg.userid[ 19 ] = NULL;
					memcpy( sendMsg.userpw, 	pRecvMsg->userpw, 		20 );	sendMsg.userpw[ 19 ] = NULL;
					memcpy( sendMsg.userIP, 	pRecvMsg->userIP, 		20 );	sendMsg.userIP[ 19 ] = NULL;
					memcpy( sendMsg.macaddress, pRecvMsg->macaddress,	20 );	sendMsg.macaddress[ 19 ] = NULL;

					g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

					// ȭ�鿡 �α� ���
					printf( "[PORTEAUTH] ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
				}
				// HanAuth ���� �Լ� ����
				else
				{
					// FrontServer�� ���� ���� ����
					sResponse_FrontAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_FRONTAUTH;

					// �Ѱ��� ��������
					sendMsg.usResult = 20;

					sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

					sendMsg.siAuthKey = 0;

					sendMsg.siGameMasterLevel = 0;

					sendMsg.siBlockMode = 0;
					sendMsg.siBlockYear = 0;
					sendMsg.siBlockMonth = 0;
					sendMsg.siBlockDay = 0;
					sendMsg.siBlockHour = 0;
					sendMsg.siBlockMin = 0;

					sendMsg.szBlockReason[ 0 ] = NULL;
					sendMsg.bAlreadyMakeCharSwitch = 0;
					sendMsg.szServerName[ 0 ] = NULL;

					sendMsg.siAccountStatus = 0;

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED) 
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

					// �α� ���
					g_CLogPrint.WriteFileLog("PorteAuth_Error.txt", __FILE__, __LINE__, "[FRONTAUTH] AUTHMSG_REQUEST_PORTEAUTH_FRONTAUTH() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);

					// ���α׷� ���� ����
					/*if( ret == HAN_AUTHSVR_DLL_UNEXPECTED)
					{
						g_bRun = FALSE;
						break;
					}*/
				}
#endif // USE_PORTEAUTH
			}
			break;
			
		case AUTHMSG_REQUEST_TAIWAN_FRONTAUTH:
			{
#ifdef _TAIWAN
				printf( "Request user auth (TAIWAN) from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_Taiwan_FrontAuth	*pRecvMsg = (sRequest_Taiwan_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->gameaccount, sizeof(sendMsg.userid) );
				sendMsg.userid[ sizeof(sendMsg.userid) - 1 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->onetimepassword, sizeof(sendMsg.userpw) );
				sendMsg.userpw[ sizeof(sendMsg.userpw) - 1 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, sizeof(sendMsg.userIP) );
				sendMsg.userIP[ sizeof(sendMsg.userIP) - 1 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, sizeof(sendMsg.macaddress) );
				sendMsg.macaddress[ sizeof(sendMsg.macaddress) - 1 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
#endif
			}
			break;
			
		// PCK : IOVATION ���� ��û (2009.02.03)
		case AUTHMSG_REQUEST_ENGLISH_FRONTAUTH:
			{
				printf( "Request user auth (IOVATION) from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_English_FrontAuth	*pRecvMsg = (sRequest_English_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_English_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_ENGLISH_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;
				sendMsg.accountstatus = 200;	// 200 => �۷ι����� ������ AccountDBManager�� �˸�.
				
				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;

				memcpy( sendMsg.Blackbox, pRecvMsg->Blackbox, 2048 );
				sendMsg.macaddress[ 2047 ] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s\n, PW:%s\n, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
			}
			break;
		case AUTHMSG_REQUEST_USA_FRONTAUTH:
			{
				printf( "Request user auth (USA) from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_USA_FrontAuth	*pRecvMsg = (sRequest_USA_FrontAuth*)pPacket;

				AuthInfo info;
				info.Init();
				
				info.SetUSAAuthString( pRecvMsg->authstring );
				info.m_usPacketUnique	= pRecvMsg->usPacketUnique;
				info.m_usFrontCharID	= pRecvMsg->usFrontCharID;

				int ret = USAAuth_NHNAuth( info );	

				// ���� ��⿡�� ����!
				if( ret == 0 )	
				{
					// FrontServer�� ���� ���� ����
					sResponse_FrontAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd  = AUTHMSG_RESPONSE_FRONTAUTH;

					// USA ��������
					sendMsg.usResult		  		= 30;
					sendMsg.usPacketUnique    		= pRecvMsg->usPacketUnique;
					sendMsg.usFrontCharID     		= pRecvMsg->usFrontCharID;
					sendMsg.siAuthKey		  		= 0;
					sendMsg.siGameMasterLevel 		= 0;
					sendMsg.siBlockMode  			= 0;
					sendMsg.siBlockYear  			= 0;
					sendMsg.siBlockMonth 			= 0;
					sendMsg.siBlockDay   			= 0;
					sendMsg.siBlockHour  			= 0;
					sendMsg.siBlockMin   			= 0;
					sendMsg.szBlockReason[ 0 ]		= NULL;
					sendMsg.bAlreadyMakeCharSwitch	= 0;
					sendMsg.szServerName[ 0 ]		= NULL;
					sendMsg.siAccountStatus			= 0;

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED) 
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	

					// �α� ���
					g_CLogPrint.WriteFileLog("USA_Error.txt", __FILE__, __LINE__, "[FRONTAUTH] USAAuthForServer() Error - Auth String : [%s], ErrorCode : [%d]", pRecvMsg->authstring, ret);
				}
			}
			break;

		case AUTHMSG_REQUEST_EUROPE_FRONTAUTH:
			{
				printf( "Request user auth(Europe) from FrontServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_EUROPE_FrontAuth *pRecvMsg = (sRequest_EUROPE_FrontAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_IDNumGet	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				memcpy( sendMsg.userIP, pRecvMsg->userIP, 20 );
				sendMsg.userIP[ 19 ] = NULL;

				memcpy( sendMsg.macaddress, pRecvMsg->macaddress, 20 );
				sendMsg.macaddress[ 19 ] = NULL;

				sendMsg.jumin[ 0 ] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );


			}
			break;

		case AUTHMSG_REQUEST_FRONTJOINGAME:
			{
				sRequest_FrontJoinGame	*pRecvMsg = (sRequest_FrontJoinGame *)pPacket;
			
				sDBRequest_JoinGame sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_JOINGAME;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usPacketUnique = pRecvMsg->usPacketUnique;
				sendMsg.usFrontCharID = pRecvMsg->usFrontCharID;

				// id
				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				// pw
				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				// cookie
				memcpy( sendMsg.cookie, pRecvMsg->cookie, 20 );
				sendMsg.cookie[ 19 ] = NULL;

				// ip
				memcpy( sendMsg.szIP, pRecvMsg->szIP, 20 );
				sendMsg.szIP[ 19 ] = NULL;

				// jumin
				sendMsg.jumin[0] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

			}
			break;
		}

		pSession->GetRecvBuffer()->RemoveFirstPacket();
	}
}

void AuthFrontProtocol::Update()
{

}

// ���� ���̵��� �Ľ��ϴ� �Լ�.
void DeltPublisherID(TCHAR * Input_userid ,TCHAR * Output_userid)
{
	SI16 idSize = strlen(Input_userid);

	for(SI16 i =0;i < idSize; i++)
	{
		// "@" ���� ������ ���ڸ��� �����Ѵ�.
		if(Input_userid[i] == '@')
		{
			strncpy(Output_userid,Input_userid, i );
			break;
		}
	}	
}

int CALLBACK JapanAuthCallBackFunc(AuthInfo info, int nRet)
{
	switch(info.m_nAuthType)
	{
	case AUTH_TYPE_GAMEPOT:
		{
			if( 0 != nRet ) return 0;

			// AccountDBManager�� ���� ��û
			sDBRequest_IDNumGet	sendMsg;

			sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
			sendMsg.packetHeader.usSize = sizeof( sendMsg );

			sendMsg.usPacketUnique	= info.m_usPacketUnique;
			sendMsg.usFrontCharID	= info.m_usFrontCharID;

			memcpy( sendMsg.userid, info.m_szID, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, info.m_szPW, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, info.m_szIP, 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, info.m_szMAC, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			sendMsg.jumin[ 0 ] = NULL;

			g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

			printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
		}
		break;
	case AUTH_TYPE_GAMANIA:
		{
			if( 0 != nRet ) return 0;

			// AccountDBManager�� ���� ��û
			sDBRequest_IDNumGet	sendMsg;

			sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
			sendMsg.packetHeader.usSize = sizeof( sendMsg );

			sendMsg.usPacketUnique	= info.m_usPacketUnique;
			sendMsg.usFrontCharID	= info.m_usFrontCharID;

			memcpy( sendMsg.userid, info.m_szID, 20 );
			if( strlen(sendMsg.userid) <= 16 )	{		strcat(sendMsg.userid, "@GA");		}
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userpw, info.m_szPW, 20 );
			sendMsg.userpw[ 19 ] = NULL;

			memcpy( sendMsg.userIP, info.m_szIP, 20 );
			sendMsg.userIP[ 19 ] = NULL;

			memcpy( sendMsg.macaddress, info.m_szMAC, 20 );
			sendMsg.macaddress[ 19 ] = NULL;

			sendMsg.jumin[ 0 ] = NULL;

			g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

			printf( "ID:%s, PW:%s, IP:%s\n", sendMsg.userid, sendMsg.userpw, sendMsg.userIP );
		}
		break;
	case AUTH_TYPE_USA:
		{
			// AccountDBManager�� ���� ��û
			sDBRequest_IDNumGet	sendMsg;

			sendMsg.packetHeader.usCmd = DBMSG_REQUEST_IDNUMGET;
			sendMsg.packetHeader.usSize = sizeof( sendMsg );

			sendMsg.usPacketUnique	= info.m_usPacketUnique;
			sendMsg.usFrontCharID	= info.m_usFrontCharID;
			sendMsg.accountstatus   = 100;							// 100 => USA ���� ������ AccountDBManager�� �˸�.
		
			printf( "USA AUTH STRING:%s\n", info.m_Authstring );	

			memcpy( sendMsg.userid, info.m_szID, 20 );
			sendMsg.userid[ 19 ] = NULL;

			memcpy( sendMsg.userIP, info.m_szIP, 20 );
			sendMsg.userIP[ 19 ] = NULL;

			sendMsg.jumin[ 0 ]	= NULL;

			g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

			printf( "ID:%s, IP:%s\n", sendMsg.userid, sendMsg.userIP );
		}
		break;
	}

	return 0;
}


//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�. - �����Ͼƿ� ���� �Լ�.
/*int HttpsPostAuth(TCHAR *pszID, TCHAR *pszPW)	// For �����Ͼ�
{
	if(pszID == NULL || pszPW == NULL)			return -1;

	int bResult = -1;

	HINTERNET	hSession = NULL;
	hSession = ::InternetOpen("AuthTest", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	char szPostData[1024] = { '\0', };
	BOOL bRet = FALSE;

	wsprintf(szPostData, "id=%s&pw=%s", pszID, pszPW);

	if(hSession)
	{
		HINTERNET hConnect = ::InternetConnect(hSession,
												"gash.gamania.co.jp",
												INTERNET_DEFAULT_HTTPS_PORT,
												"",
												"",
												INTERNET_SERVICE_HTTP,//urlcomponent.nScheme,
												0,
												0);

		if(hConnect)
		{
			// connected server..
			HINTERNET hObject = ::HttpOpenRequest( hConnect,
													"POST",
													"/acxauth/b2b.auth/authkunshu.ashx",
													HTTP_VERSION,
													"",
													NULL,
													INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID,
													0);

			if(hObject)
			{
				// post header
				char szLen[MAX_PATH] = { '\0', };
				char aHeader[1024] = { '\0', };

				wsprintf(szLen, "%d", strlen(szPostData));
				strcat(aHeader, "Accept: text/*\r\n");
				strcat(aHeader, "User-Agent: Mozilla/4.0 (compatible; MSIE 5.0;* Windows NT)\r\n");
				strcat(aHeader, "Content-type: application/x-www-form-urlencoded\r\n");
				strcat(aHeader, "Content-length: ");
				strcat(aHeader, szLen);
				strcat(aHeader, "\r\n\n");

				bRet = ::HttpAddRequestHeaders(hObject,(LPCTSTR)aHeader,-1L,HTTP_ADDREQ_FLAG_ADD);
				bRet = ::HttpSendRequest(hObject, NULL, 0, (LPVOID)szPostData, (DWORD)strlen(szPostData));

				// open object
				char szBuffer[1024] = { '\0', };
				DWORD dwRead = 0;
				char szResult[2048] = { '\0', };

				while (::InternetReadFile(hObject, szBuffer, 1023, &dwRead) && dwRead > 0)
				{
					szBuffer[dwRead] = 0;
					strcat(szResult, szBuffer);
					Sleep(1);
				}

				if(strcmp(szBuffer, "00") == 0)		bResult = 0;
				else if(strcmp(szBuffer, "01") == 0)		bResult = 1;
				else if(strcmp(szBuffer, "10") == 0)		bResult = 10;
				else if(strcmp(szBuffer, "11") == 0)		bResult = 11;
				else if(strcmp(szBuffer, "99") == 0)		bResult = 99;				

				::InternetCloseHandle(hObject);
			}

			::InternetCloseHandle(hConnect);
		}
		::InternetCloseHandle(hSession);
	}

	return bResult;
}

BOOL HTTPHangameRTA(int Count)	// For HangameJP
{
	BOOL bResult = FALSE;

	HINTERNET	hSession = NULL;
	hSession = ::InternetOpen("HTTPHangameRTA", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	char szPostData[128] = { '\0', };
	char szObject[1024] = { '\0', };
	BOOL bRet = FALSE;

	sprintf(szObject, "publish/common/rta.asp?gameid=pubkunshu&cnt=%d", Count);

	if(hSession)
	{
		HINTERNET hConnect = ::InternetConnect(hSession,
			"ssl.hangame.co.jp",
			INTERNET_DEFAULT_HTTP_PORT,
			"",
			"",
			INTERNET_SERVICE_HTTP,
			0,
			0);

		if(hConnect)
		{
			// connected server..
			HINTERNET hObject = ::HttpOpenRequest( hConnect,
				"GET",
				szObject,
				HTTP_VERSION,
				"",
				NULL,
				NULL,
				0);

			if(hObject)
			{
				// post header
				char szLen[MAX_PATH] = { '\0', };
				char aHeader[1024] = { '\0', };

				sprintf(szLen, "%d", strlen(szPostData));
				strcat(aHeader, "Accept: text/*\r\n");
				strcat(aHeader, "User-Agent: Mozilla/4.0 (compatible; MSIE 5.0;* Windows NT)\r\n");
				strcat(aHeader, "Content-type: application/x-www-form-urlencoded\r\n");
				strcat(aHeader, "Content-length: ");
				strcat(aHeader, szLen);
				strcat(aHeader, "\r\n\n");

				bRet = ::HttpAddRequestHeaders(hObject,(LPCTSTR)aHeader,-1L,HTTP_ADDREQ_FLAG_ADD);
				bRet = ::HttpSendRequest(hObject, NULL, 0, (LPVOID)NULL, (DWORD)0);

				// open object
				char szBuffer[1024] = { '\0', };
				DWORD dwRead = 0;
				DWORD dwTotalRead = 0;
				char szResult[2048] = { '\0', };

				while (::InternetReadFile(hObject, szBuffer, 1023, &dwRead) && dwRead > 0)
				{
					szBuffer[dwRead] = 0;
					dwTotalRead += dwRead;
					if( strlen(szResult) + dwRead >= sizeof(szResult) )
						break;
					strcat(szResult, szBuffer);
					Sleep(1);
				}

				::InternetCloseHandle(hObject);
			}

			::InternetCloseHandle(hConnect);
		}
		::InternetCloseHandle(hSession);
	}

	return bResult;
}

//KHY - 0617 - �Ϻ� ä�θ� �߰�. - �����̿� ���� �Լ�.
int SoapAuth(TCHAR *pszID, TCHAR *pszPW ,  TCHAR *puserIP)	// For GamePot
{
	HRESULT	hr;

	hr = CoInitialize(NULL);

	//bool ret = GamePotAuth("channeling001@GP", "1CE2BD159ED941D1", "127.0.0.1");
	SI16 ret = GamePotAuth(pszID, pszPW, puserIP);

	CoUninitialize();

	return ret;
}


int GamePotAuth(char* pszID, char* pszPW, char* pszIP)
{
	if(pszID == NULL || pszPW == NULL || pszIP == NULL)		return -1;

	int				bRet = -1; // ���� 
	HRESULT			hr;
	TCHAR			szMethodName[] = "GameLogin";
	LPOLESTR		fszMemberFunc = new OLECHAR[strlen(szMethodName) + 1];

	_bstr_t			bstrWSDLFile = (_T("https://kunshu.postar.jp/api/channeling.asmx?wsdl"));

	DISPPARAMS		dispparams;
	EXCEPINFO		excepinfo;
	VARIANT			returnval;
	unsigned int		uArgErr = 0;

	CComPtr<ISoapClient>	pSoapClient;

	if(fszMemberFunc)		ZeroMemory(fszMemberFunc, sizeof(OLECHAR) * (strlen(szMethodName) + 1));
	::MultiByteToWideChar(CP_ACP, 0, szMethodName, (int)strlen(szMethodName), fszMemberFunc, (int)strlen(szMethodName));

	dispparams.rgvarg = NULL;

	hr = pSoapClient.CoCreateInstance(__uuidof(SoapClient30));
	if( hr == S_OK )
	{
		_bstr_t			empty(_T(""));
		DISPID			dispid;

		hr = pSoapClient->MSSoapInit(bstrWSDLFile, empty, empty, empty);		
		hr = pSoapClient->GetIDsOfNames(IID_NULL, &fszMemberFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

		BSTR		bstrParam_ID;
		BSTR		bstrParam_PW;
		BSTR		bstrParam_IP;
		BSTR		bstrParam_ERRNO;
		BSTR		bstrParam_ERRMSG;

		OLECHAR		oleBuf[1024];

		ZeroMemory(oleBuf, sizeof(OLECHAR) * 1024);
		::MultiByteToWideChar(CP_ACP, 0, pszID, (int)strlen(pszID), oleBuf, (int)strlen(pszID));
		bstrParam_ID = SysAllocString(oleBuf);

		ZeroMemory(oleBuf, sizeof(OLECHAR) * 1024);
		::MultiByteToWideChar(CP_ACP, 0, pszPW, (int)strlen(pszPW), oleBuf, (int)strlen(pszPW));
		bstrParam_PW = SysAllocString(oleBuf);

		ZeroMemory(oleBuf, sizeof(OLECHAR) * 1024);
		::MultiByteToWideChar(CP_ACP, 0, pszIP, (int)strlen(pszIP), oleBuf, (int)strlen(pszIP));
		bstrParam_IP = SysAllocString(oleBuf);

		ZeroMemory(oleBuf, sizeof(OLECHAR) * 1024);
		bstrParam_ERRNO = SysAllocStringLen(oleBuf, 1024);

		ZeroMemory(oleBuf, sizeof(OLECHAR) * 1024);
		bstrParam_ERRMSG = SysAllocStringLen(oleBuf, 1024);

		dispparams.rgvarg				= new VARIANTARG[5];
		dispparams.cArgs				= 5;
		dispparams.cNamedArgs			= 0;
		dispparams.rgdispidNamedArgs	= NULL;

		dispparams.rgvarg[0].vt			= VT_BYREF | VT_BSTR;
		dispparams.rgvarg[0].pbstrVal	= &bstrParam_ERRMSG;

		dispparams.rgvarg[1].vt			= VT_BYREF | VT_BSTR;
		dispparams.rgvarg[1].pbstrVal	= &bstrParam_ERRNO;

		dispparams.rgvarg[2].vt			= VT_BYREF | VT_BSTR;
		dispparams.rgvarg[2].pbstrVal	= &bstrParam_IP;

		dispparams.rgvarg[3].vt			= VT_BYREF | VT_BSTR;
		dispparams.rgvarg[3].pbstrVal	= &bstrParam_PW;

		dispparams.rgvarg[4].vt			= VT_BYREF | VT_BSTR;
		dispparams.rgvarg[4].pbstrVal	= &bstrParam_ID;

		VariantInit(&returnval);

		excepinfo.wCode					= 0;
		excepinfo.bstrSource			= NULL;
		excepinfo.bstrDescription		= NULL;
		excepinfo.bstrHelpFile			= NULL;

		hr = pSoapClient->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, &returnval, &excepinfo, &uArgErr);

		if( hr == S_OK )
		{
			if( returnval.vt == VT_BOOL )
			{
				if( returnval.boolVal == VARIANT_TRUE )
				{
					// ���� ����
					if( wcscmp(bstrParam_ERRNO, L"0") == 0 )
					{
						bRet = 0; //���� 
					}
				}
				else
				{
					// ���� ����
					if( wcscmp(bstrParam_ERRNO, L"1") == 0 )
					{
						bRet = 1;  					
					}
					else if( wcscmp(bstrParam_ERRNO, L"100") == 0 )
					{
						bRet = 100;  
					}
					else if( wcscmp(bstrParam_ERRNO, L"254") == 0 )
					{
						bRet = 254;  					
					}
					else if( wcscmp(bstrParam_ERRNO, L"255") == 0 )
					{
						bRet = 255;  					
					}
					else
					{
						bRet = -1;
					}
					
				}
			}
		}

		SysFreeString(bstrParam_ID);
		SysFreeString(bstrParam_PW);
		SysFreeString(bstrParam_IP);
		SysFreeString(bstrParam_ERRNO);
		SysFreeString(bstrParam_ERRMSG);
	}

	if(pSoapClient)				pSoapClient.Release();
	if(dispparams.rgvarg)		delete[] dispparams.rgvarg;

	return bRet;
}

bool GamePotReport(int nCount)
{
	bool			bRet = false;
	HRESULT			hr;
	TCHAR			szMethodName[] = "GameReport";
	LPOLESTR		fszMemberFunc = new OLECHAR[strlen(szMethodName) + 1];

	_bstr_t			bstrWSDLFile = (_T("https://kunshu.postar.jp/api/channeling.asmx?wsdl"));

	DISPPARAMS		dispparams;
	EXCEPINFO		excepinfo;
	VARIANT			returnval;
	unsigned int	uArgErr = 0;

	CComPtr<ISoapClient>	pSoapClient;

	if(fszMemberFunc)		ZeroMemory(fszMemberFunc, sizeof(OLECHAR) * (strlen(szMethodName) + 1));
	::MultiByteToWideChar(CP_ACP, 0, szMethodName, (int)strlen(szMethodName), fszMemberFunc, (int)strlen(szMethodName));

	dispparams.rgvarg = NULL;

	hr = pSoapClient.CoCreateInstance(__uuidof(SoapClient30));
	if( hr == S_OK )
	{
		_bstr_t			empty(_T(""));
		DISPID			dispid;

		hr = pSoapClient->MSSoapInit(bstrWSDLFile, empty, empty, empty);		
		hr = pSoapClient->GetIDsOfNames(IID_NULL, &fszMemberFunc, 1, LOCALE_SYSTEM_DEFAULT, &dispid);

		dispparams.rgvarg				= new VARIANTARG[2];
		dispparams.cArgs				= 2;
		dispparams.cNamedArgs			= 0;
		dispparams.rgdispidNamedArgs	= NULL;

		dispparams.rgvarg[0].vt			= VT_DATE;
		SYSTEMTIME	curTime;
		GetLocalTime(&curTime);
		SystemTimeToVariantTime(&curTime, &dispparams.rgvarg[0].date);

		dispparams.rgvarg[1].vt			= VT_INT;
		dispparams.rgvarg[1].intVal		= nCount;

		VariantInit(&returnval);

		excepinfo.wCode					= 0;
		excepinfo.bstrSource			= NULL;
		excepinfo.bstrDescription		= NULL;
		excepinfo.bstrHelpFile			= NULL;

		hr = pSoapClient->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &dispparams, &returnval, &excepinfo, &uArgErr);

		if( hr == S_OK )
		{
			if( returnval.vt == VT_BOOL )
			{
				if( returnval.boolVal == VARIANT_TRUE )
				{
					bRet = true;
				}
				else
				{
				}
			}
		}
	}

	if(pSoapClient)				pSoapClient.Release();
	if(dispparams.rgvarg)		delete[] dispparams.rgvarg;

	return bRet;
}
*/

// �ֹε�Ϲ�ȣ (SSN)�� ������ �Է��� ���̿� ������ �̿��ؼ� �����Ѵ�.
// siAge     [input]  : ����
// siSex     [input]  : 0(����), 1(����)
// pszRet    [output] : �ֹι�ȣ
// uiRetSize [input]  : pszRet�� ����
bool SSNCreate(SI08 siAge, SI08 siSex, TCHAR* pszRet, UI32 uiRetSize)
{
	SI16 siBirthYear;
	TCHAR szSSN[16] = {'\0',};
	TCHAR szBirthYear[8] = { '\0',};

	if(pszRet == NULL)			return false;

	// ������ �⵵�� ���Ѵ�. (�ϴ� �׽�Ʈ�� ���ؼ� 2008�� ���Ƿ� ����ִ´�.)
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	SI16 siCurrentYear = stTime.wYear;

	// ����⵵�� ���ϱ� ���ؼ� ���� �⵵���� �ڱ⳪�̸� ���Ŀ� 1�� ���Ѵ�.
	// �ѱ��� ��� �¾�ڸ��� 1��� ����ϱ� ������ �������� 1�� ���ؾ� �Ѵ�.
	siBirthYear = siCurrentYear - siAge + 1;

	// ����⵵�� ���ڿ��� ��ȯ�Ѵ�.
	StringCchPrintf(szBirthYear, sizeof(szBirthYear), "%d", siBirthYear);

	// ����⵵�� ���� 2�ڸ��� �ֹε�Ϲ�ȣ�� ����ִ´�.
	_tcsncpy(szSSN, &szBirthYear[2], 2);

	// ������ ��, ���� '0101'�� ä���ִ´�.
	_tcscat(szSSN, TEXT("0101"));

	// ���� ù��° �ڸ��� ������������ ä���ִ´�.
	if(siBirthYear >= 1900 && siBirthYear <= 1999)	// 1900���� �̸�
	{
		if	   (siSex == 0)		   {	_tcscat(szSSN, TEXT("1"));	}		// ���ڸ� 1
		else if(siSex == 1)		   {	_tcscat(szSSN, TEXT("2"));	}		// ���ڸ� 2
	}
	else if(siBirthYear >= 2000)	// 2000���� �̸�
	{
		if	   (siSex == 0)		   {	_tcscat(szSSN, TEXT("3"));	}		// ���ڸ� 3
		else if(siSex == 1)		   {	_tcscat(szSSN, TEXT("4"));	}		// ���ڸ� 4
	}
	else if(siBirthYear <= 1899)	// 1800��� ������ �̸�
	{
		if	   (siSex == 0)		   {	_tcscat(szSSN, TEXT("9"));	}		// ���ڸ� 9
		else if(siSex == 1)		   {	_tcscat(szSSN, TEXT("0"));	}		// ���ڸ� 0
	}

	// ������ 6�ڸ��� '000000'�� ä���ִ´�.
	_tcscat(szSSN, TEXT("000000"));

	_tcsncpy(pszRet, szSSN, uiRetSize);

	return true;
}

// �Ϻ� �ؽ� �� �Ľ� �Լ�.
void NexonjpIDDataDivision(sRequest_NEXONJP_FrontAuth *FfrontAuth , sDBRequest_IDNumGet *FsendMsg)
{
	char temTotalChar[512] = { '\0', };

	char	szDivider1[] = {'&'};
	char	szDivider2[] = {'='};

	char temuserid[50] = { '\0', };
	char temrequestTime[60] = { '\0', };
	char temmkey1[50] = { '\0', };
	char temmkey2[50] = { '\0', };
	char temmkey[262] = { '\0', };

	char tem2userid[40] = { '\0', };
	char tem2requestTime[24] = { '\0', };
	char tem2mkey1[37] = { '\0', };
	char tem2mkey2[37] = { '\0', };
	char tem2mkey[261] = { '\0', };

	char imsiChar[300] = { '\0', };
	
	memcpy(temTotalChar, FfrontAuth->userid , 512);

	//printf( " 0 -FfrontAuth->userid: %s\n", FfrontAuth->userid);
	//printf( " 0 -1 temTotalChar: %s\n", temTotalChar);


	// 1�� "&"������ ���´�. 
	HQDivideBy2(szDivider1,temTotalChar,"%s %s %s %s %s",temuserid,temrequestTime,temmkey1,temmkey2,temmkey);

	//printf( " 1- [%s] [%s] [%s] [%s] [%s] \n",temuserid,temrequestTime,temmkey1,temmkey2,temmkey);

	// 2�� ���� "=" ������ ��� ����.
	HQDivideBy2(szDivider2,temuserid,"%s %s",imsiChar,tem2userid);
	HQDivideBy2(szDivider2,temrequestTime,"%s %s",imsiChar,tem2requestTime);	
	HQDivideBy2(szDivider2,temmkey1,"%s %s",imsiChar,tem2mkey1);
	HQDivideBy2(szDivider2,temmkey2,"%s %s",imsiChar,tem2mkey2);
	HQDivideBy2(szDivider2,temmkey,"%s %s",imsiChar,tem2mkey);

	//printf( " 2- [%s] [%s] [%s] [%s] [%s] \n",tem2userid,tem2requestTime,tem2mkey1,tem2mkey2,tem2mkey);

	// �Ľ̵� ���� �����Ѵ�.
	memcpy(FsendMsg->userid,tem2userid,sizeof(tem2userid));
	memcpy(FsendMsg->requestTime,tem2requestTime,sizeof(tem2requestTime));
	memcpy(FsendMsg->mkey1,tem2mkey1,sizeof(tem2mkey1));
	memcpy(FsendMsg->mkey2,tem2mkey2,sizeof(tem2mkey2));
	memcpy(FsendMsg->key,tem2mkey,sizeof(tem2mkey));

	//printf( "3- [%s] [%s] [%s] [%s] [%s] \n",FsendMsg->userid,FsendMsg->requestTime,FsendMsg->mkey1,FsendMsg->mkey2,FsendMsg->key);
}
