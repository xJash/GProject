#include "AuthGameProtocol.h"
#include "AuthUserList.h"
#include "AccountDBProcess.h"
#include "UserManager.h"
#include "../FrontServer/Log.h"

#ifdef USE_HANAUTH
	// - NHN ASM -
	#include "./HanAuth/HanAuthForSvr.h"
	// - NHN ASM -
#endif //USE_HANAUTH

#ifdef _CHINA
	// �߱� ������
	#include <comutil.h>
	#include "../../NLib/md5.h"
	#include "TiredSystem.h"
	AEService::CAEService			    g_UserTiredSystem;
	CLogPrint							g_Log;
#endif

extern CLogPrint			g_CLogPrint;
extern BOOL					g_bRun;

//extern bool GamePotReport(int nCount);
//extern BOOL HTTPHangameRTA(int Count);

#include "./JapanAuth/JapanAuth.h"

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	#include "./Porte/PorteAuthForSvr.h"	
	using namespace Porte::PorteAuthSystem;
#endif // USE_PORTEAUTH

	//KHY - 0218 - �߱� NHN �Ƿε� ��� ���� - ��������� ����Ǿ�߸� �Ѵ�.
#ifdef USE_HANANTITOXIC
	#include "./HanAntiToxic/HanAntiToxic.h"
#endif


AuthGameProtocol::AuthGameProtocol()
{
//	m_kUpdateTimer_GamepotJP.Init(60 * 1000);
//	m_kUpdateTimer_HangameJP.Init(10 * 60 * 1000);
}

AuthGameProtocol::~AuthGameProtocol()
{
	
}

void AuthGameProtocol::Init(UI16 usGameServerListenPort)
{
	m_SF.CreateFactory( GetSessionManager(), 30, 5 * 1000 * 1000, 5 * 1000 * 1000 );
	
	GetNetIOCP()->CreateIOCP( GetSessionManager(), 1 );

	GetListen()->CreateListen( GetSessionManager(), usGameServerListenPort );
	
	SetFPS( 200 );

//	m_kUpdateTimer_GamepotJP.SetActive(true, ::GetTickCount());
//	m_kUpdateTimer_HangameJP.SetActive(true, ::GetTickCount());
}


void AuthGameProtocol::LogOut( ITZSession *pSession )
{
	
}

void AuthGameProtocol::SessionProc( ITZSession *pSession )
{

	int count = pSession->GetRecvBuffer()->GetPacketCount();

	for( int i = 0; i < count; ++i ) {

		// ���ۿ��� ��Ŷ�� �ϳ� �����´� 
		sPacketHeader *pPacket = (sPacketHeader *)( pSession->GetRecvBuffer()->GetFirstPacket() );
																								
		if( pPacket == NULL ) return;										// ��Ŷ�� ������ ������
		
		// ��Ŷ Ŀ�ǵ忡 ���� ó��
		switch( pPacket->usCmd ) {

		case AUTHMSG_REPORT_GAMEHEARTBEAT:
			{
			}
			break;

		case AUTHMSG_REQUEST_GAMEAUTH:
			{
#ifdef _CHINA
				// webservice-
				CoInitialize(NULL);

				printf( "Request user auth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_GameAuth	*pRecvMsg = (sRequest_GameAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_GameAuth	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_GAMEAUTH;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usGameServerID = pSession->m_usIndex;
				sendMsg.usCharID = pRecvMsg->usCharID;

				sendMsg.idnum = pRecvMsg->siAuthKey;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				_bstr_t serverID = pRecvMsg->userServerID;
				_bstr_t id = pRecvMsg->userid;
				_bstr_t pw = pRecvMsg->userpw;
				_bstr_t ip = pRecvMsg->userIP;

				_bstr_t resultstr = "Tired Login";

				const size_t newsize = 100;
				char nstring[newsize];
				strncpy(nstring, (char *)resultstr, 100 );
				printf( "%s\n", nstring );

				BSTR  bstr = resultstr.copy();  

		//		g_Log.FilePrint( "TiredSystem.txt", "Tired Login" );

				SI32 result = -1;
				SI32 tryTiredSystem = 0;
				g_UserTiredSystem.HLJZLogIn( serverID, id, ip, &result, &bstr ) ;

				resultstr.Assign( bstr );
				strncpy(nstring, (char *)resultstr, 100 );

				if( strcmp(nstring, "Tired Login") == 0 )
				{
					tryTiredSystem = 1;
					g_UserTiredSystem.HLJZLogIn( serverID, id, ip, &result, &bstr ) ;
				}

				resultstr.Assign( bstr );
				strncpy(nstring, (char *)resultstr, 100 );

				printf( "Tired Login Result = %d %s %d %s \n" , tryTiredSystem, pRecvMsg->userServerID, result, nstring);
		//		g_Log.FilePrint( "TiredSystem.txt", "Tired Login Result Time[Try : %d][ServerID : %s][Result : %d][Message : %s]", tryTiredSystem, pRecvMsg->userServerID, result, nstring );

				SysFreeString ( bstr );

				sendMsg.siPlayingTime = result;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "IDNUM:%d, ID:%s, PW:%s\n", sendMsg.idnum, sendMsg.userid, sendMsg.userpw );

#else
				printf( "Request user auth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_GameAuth	*pRecvMsg = (sRequest_GameAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_GameAuth	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_GAMEAUTH;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usGameServerID = pSession->m_usIndex;
				sendMsg.usCharID = pRecvMsg->usCharID;

				sendMsg.idnum = pRecvMsg->siAuthKey;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				sendMsg.siPlayingTime = -1;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "IDNUM:%d, ID:%s, PW:%s\n", sendMsg.idnum, sendMsg.userid, sendMsg.userpw );
#endif
			}
			break;

		case AUTHMSG_REQUEST_HANAUTH_GAMEAUTH:
			{
#ifdef USE_HANAUTH
				// ȭ�鿡 �α� ���
				printf( "[HANAUTH] Request user HanAuth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_HanAuth_GameAuth	*pRecvMsg = (sRequest_HanAuth_GameAuth *)pPacket;

				// HanAuth ���������� ��ģ��.
				char szOutBuf[ SIZE_OUTBUFFER ] = {0x00};
				//int ret = HanAuthForSvr( pRecvMsg->userid, pRecvMsg->authstring, szOutBuf, SIZE_OUTBUFFER );
				if ( pRecvMsg->userid == NULL)	break	;
				if ( pRecvMsg->authstring == NULL)	break	;
				int ret = HanAuthForSvr( pRecvMsg->userid, pRecvMsg->authstring, szOutBuf, sizeof( szOutBuf ) );
				// �α� ���
				g_CLogPrint.WriteFileLog("HanAuth.txt", __FILE__, __LINE__, "[GAMEAUTH] UserID : [%s], OutBuf : [%s]", pRecvMsg->userid, szOutBuf);

				if( ret == 0 )
				{
					// AccountDBManager�� ������ ���� ���̸� ���� üũ�Ѵ�.
					char szTempOutBuf[ SIZE_OUTBUFFER ] = {0x00};

					// �Ѱ��� ������ ����
					strcpy(szTempOutBuf, szOutBuf);
					char* pRet = NULL;
					char* pID = NULL;
					char* pAge = NULL;
					char* pIDNo = NULL;

					char szAge[32] = {0, };		// ���� - for KOREA
					char szIDNo[32] = {0, };	// IDNO - for USA

					SI32 siAge = 0;
					UI32 uiIDNo = 0;

					pRet = strtok(szTempOutBuf, "|");
					if(pRet != NULL)		pID   = strtok(NULL, "|");
					if(pID  != NULL)		pAge  = strtok(NULL, "|");	// ���� - for KOREA
					if(pAge != NULL)		pIDNo = strtok(NULL, "|");	// IDNO - for USA

					if(pAge != NULL)		strncpy(szAge, pAge, sizeof(szAge));
					if(strlen(szAge))		siAge = atoi(szAge);		// ���� - for KOREA

					if(pIDNo != NULL)		strncpy(szIDNo, pIDNo, sizeof(szIDNo));
					if(strlen(szIDNo))		uiIDNo = (UI32)atoi(szIDNo);		// IDNO - for USA

					if(!(pRecvMsg->usServerAge <= siAge))
					{
						// ���̰� �ȵǼ� ������ ���� �� �� ����.
						sResponse_GameAuth	sendMsg;

						sendMsg.packetHeader.usSize = sizeof( sendMsg );
						sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_GAMEAUTH;

						sendMsg.usCharID = pRecvMsg->usCharID;

						sendMsg.uiIDNum = pRecvMsg->siAuthKey;

						sendMsg.siSex = 0;

						sendMsg.siGameMasterLevel = 0;
						sendMsg.siAccountStatus = -1000;

						sendMsg.siBlockMode = 0;
						sendMsg.siBlockYear = 0;
						sendMsg.siBlockMonth = 0;
						sendMsg.siBlockDay = 0;
						sendMsg.siBlockHour = 0;
						sendMsg.siBlockMin = 0;

						sendMsg.szBlockReason[ 0 ] = NULL;
						sendMsg.siPlayingTime = -1;

						sendMsg.uiIDNo = 0;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

						// ȭ�鿡 �α� ���
						printf( "[HANAUTH] IDNUM:%d, ServerAge:%d, UserAge:%d, AccountStatus:%d\n", sendMsg.uiIDNum, pRecvMsg->usServerAge, siAge, sendMsg.siAccountStatus);

						// �α� ���
						g_CLogPrint.WriteFileLog("HanAuth_Error.txt", __FILE__, __LINE__, "[GAMEAUTH] refuse to enter server - UserID : [%s], ServerAge : [%d], UserAge : [%d]", pRecvMsg->userid, pRecvMsg->usServerAge, siAge);

						if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED )					
						{
							pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );
						}

						break;
					}

					// AccountDBManager�� ���� ��û
					sDBRequest_GameAuth	sendMsg;

					sendMsg.packetHeader.usCmd = DBMSG_REQUEST_GAMEAUTH;
					sendMsg.packetHeader.usSize = sizeof( sendMsg );

					sendMsg.usGameServerID	= pSession->m_usIndex;
					sendMsg.usCharID		= pRecvMsg->usCharID;
					sendMsg.idnum			= pRecvMsg->siAuthKey;

					memcpy( sendMsg.userid, pRecvMsg->userid, 20 );			sendMsg.userid[ 19 ] = NULL;
					sendMsg.userpw[ 0 ]		= NULL;

					sendMsg.uiIDNo = uiIDNo;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

					g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

					// ȭ�鿡 �α� ���
					printf( "[HANAUTH] IDNUM:%d, ID:%s, PW:%s IDNO: %d \n", sendMsg.idnum, sendMsg.userid, sendMsg.userpw, sendMsg.uiIDNo );

					// �α� ���
					g_CLogPrint.WriteFileLog("HanAuth.txt", __FILE__, __LINE__, "[GAMEAUTH] allow to enter server - UserID : [%s], ServerAge : [%d], UserAge : [%d]", pRecvMsg->userid, pRecvMsg->usServerAge, siAge);
				}
				else
				{
					//------------------------------------------------------------
					// �Ѱ��� ���� �Լ� ����
					sResponse_GameAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_GAMEAUTH;

					sendMsg.usCharID			= pRecvMsg->usCharID;
					sendMsg.uiIDNum				= pRecvMsg->siAuthKey;
					sendMsg.siSex				= 0;

					sendMsg.siGameMasterLevel	= 0;
					sendMsg.siAccountStatus		= -1100;

					sendMsg.siBlockMode			= 0;
					sendMsg.siBlockYear			= 0;
					sendMsg.siBlockMonth		= 0;
					sendMsg.siBlockDay			= 0;
					sendMsg.siBlockHour			= 0;
					sendMsg.siBlockMin			= 0;

					sendMsg.szBlockReason[ 0 ]	= NULL;
					sendMsg.siPlayingTime		= -1;

					sendMsg.uiIDNo				= 0;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED )
					{
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	
					}

					// �α� ���
					g_CLogPrint.WriteFileLog("HanAuth_Error.txt", __FILE__, __LINE__, "[GAMEAUTH] HanAuthForServer() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);

					// ���α׷� ���� ����
					if( ret == HAN_AUTHSVR_DLL_UNEXPECTED)
					{
						g_bRun = FALSE;
						break;
					}
				}
#endif //USE_HANAUTH
			}
			break;

		case AUTHMSG_REQUEST_TAIWAN_GAMEAUTH:
			{
#ifdef _TAIWAN
				printf( "[TAIWAN] Request user auth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_Taiwan_GameAuth	*pRecvMsg = (sRequest_Taiwan_GameAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_GameAuth	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_GAMEAUTH;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usGameServerID = pSession->m_usIndex;
				sendMsg.usCharID = pRecvMsg->usCharID;

				sendMsg.idnum = pRecvMsg->siAuthKey;

				memcpy( sendMsg.userid, pRecvMsg->gameaccount, sizeof(sendMsg.userid) );
				sendMsg.userid[ sizeof(sendMsg.userid) - 1 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->onetinepassword, sizeof(sendMsg.userpw) );
				sendMsg.userpw[ sizeof(sendMsg.userpw) - 1 ] = NULL;

				sendMsg.siPlayingTime = -1;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "[TAIWAN] IDNUM:%d, ID:%s, PW:%s\n", sendMsg.idnum, sendMsg.userid, sendMsg.userpw );
#endif
			}

		case AUTHMSG_REQUEST_GAMELOGOUT:
			{
#ifdef _CHINA
				// webservice-
				CoInitialize(NULL);

				printf( "Request user logout from GameServer\n" );

				sRequest_GameLogout	*pRecvMsg = (sRequest_GameLogout *)pPacket;

				_bstr_t serverID = pRecvMsg->userServerID;
				_bstr_t id = pRecvMsg->szAccountID;
				_bstr_t playingCharName = pRecvMsg->szPlayingCharNmae;

				_bstr_t resultstr = "Tired LogOut";

				const size_t newsize = 100;
				char nstring[newsize];
				strncpy(nstring, (char *)resultstr, 100 );
				printf( "%s\n", nstring );

				BSTR  bstr = resultstr.copy();  

		//		g_Log.FilePrint( "TiredSystem.txt", "Tired LogOut" );

				SI32 result = -1;
				SI32 tryTiredSystem = 0;
				g_UserTiredSystem.HLJZLogOut( serverID, id, playingCharName, pRecvMsg->siLevel, &result, &bstr ) ;

				resultstr.Assign( bstr );
				strncpy(nstring, (char *)resultstr, 100 );

				if( -1 == result && strcmp( nstring, "Tired LogOut" ) == 0 )
				{
					tryTiredSystem = 1;
					g_UserTiredSystem.HLJZLogOut( serverID, id, playingCharName, pRecvMsg->siLevel, &result, &bstr ) ;

					if( -1 == result && strcmp( nstring, "error" ) == 0 )
					{
						g_UserTiredSystem.HLJZLogOut( serverID, id, playingCharName, pRecvMsg->siLevel, &result, &bstr ) ;
					}

					resultstr.Assign( bstr );
					strncpy(nstring, (char *)resultstr, 100 );
				}

				if( -1 == result && strcmp( nstring, "Tired LogOut" ) == 0 )
				{
					tryTiredSystem = 2;
					g_UserTiredSystem.HLJZLogOut( serverID, id, playingCharName, pRecvMsg->siLevel, &result, &bstr ) ;

					if( -1 == result && strcmp( nstring, "error" ) == 0 )
					{
						g_UserTiredSystem.HLJZLogOut( serverID, id, playingCharName, pRecvMsg->siLevel, &result, &bstr ) ;
					}

					resultstr.Assign( bstr );
					strncpy(nstring, (char *)resultstr, 100 );
				}

		//		g_Log.FilePrint( "TiredSystem.txt", "Tired LogOut Result Time[Try : %d][ServerID : %s][Result : %d][Message : %s]", tryTiredSystem, pRecvMsg->userServerID, result, nstring );

				printf( "Tired LogOut Result = %d %s %d %s\n" , tryTiredSystem, pRecvMsg->userServerID, result, nstring );

				SysFreeString ( bstr ); 
				
				g_usermanager.GameLogOut( pRecvMsg->uiIDNum );
#else
				printf( "Request user logout from GameServer\n" );
				
				sRequest_GameLogout	*pRecvMsg = (sRequest_GameLogout *)pPacket;

//KHY - 0218 - �߱� NHN �Ƿε� ��� ���� - �÷��� Ÿ�� ����.
#ifdef USE_HANANTITOXIC							
				SI32	siHanAntiToxicSetRet = 0;

				printf( "AUTHMSG_REQUEST_GAMELOGOUT - szAccountID = %s,  siPlayTimeMinute =%d  \n", pRecvMsg->szAccountID, pRecvMsg->siPlayTimeMinute );
							
				if(pRecvMsg->siPlayTimeMinute > 0) // 0���� �۴ٸ�, �Ƿε� �������� �ƴϾ���.
				{
					siHanAntiToxicSetRet = HanSetAntiToxic("N",pRecvMsg->szAccountID,pRecvMsg->siPlayTimeMinute);
					if(siHanAntiToxicSetRet < 0)		
					{	
						SI32 HanAntiToxicReTryCount = 0;

						while(siHanAntiToxicSetRet < 0) //�� ���� �ؾ� �Ѵ�.
						{
							HanAntiToxicReTryCount++;

							g_CLogPrint.WriteFileLog("AuthserverProcessLog_HanAntiToxicRet.txt", __FILE__, __LINE__, "HanAntiToxicReTryCount = %d, HanSetAntiToxic Ret=%d, szAccountID = %s,  siPlayTimeMinute =%d", HanAntiToxicReTryCount , siHanAntiToxicSetRet , pRecvMsg->szAccountID , pRecvMsg->siPlayTimeMinute);	

							if(HanAntiToxicReTryCount < 10) // 10���� ����.
							{
								SI32	siHanAntiToxicInitRet = 0;

								siHanAntiToxicInitRet = HanAntiToxicInit("C_GZ");
								if(siHanAntiToxicInitRet < 0)		
								{	
									printf( "DBMSG_RESPONSE_GAMEAUTH - siHanAntiToxicInitRet =%d \n", siHanAntiToxicInitRet );
								}
								else
								{
									//��õ�.
									siHanAntiToxicSetRet = HanSetAntiToxic("N",pRecvMsg->szAccountID,pRecvMsg->siPlayTimeMinute);
								}
							}
							else
							{
								siHanAntiToxicSetRet = 100; // ����������.
							}
						}								

					}
				}
#endif //USE_HANANTITOXIC

				SI32 siAccountStatus = 0;

				if( _tcsstr(pRecvMsg->szAccountID, TEXT("@HG")) != NULL )
					siAccountStatus = 4;
				else if( _tcsstr(pRecvMsg->szAccountID, TEXT("@GP")) != NULL )
					siAccountStatus = 8;

				// ������ ����
				switch(siAccountStatus)
				{
				case 2:		g_usermanager.m_GamaniaJPCount--;	break;
				case 4:		g_usermanager.m_HanGameJPCount--;	break;
				case 8:		g_usermanager.m_GamepotJPCount--;	break;
				case 10:	g_usermanager.m_NEXONJPCount--;	break;
				case 0:		g_usermanager.m_NDEJPCount--;	break;
				}

				g_usermanager.GameLogOut( pRecvMsg->uiIDNum );
#endif
			}
			break;
			
		case AUTHMSG_REQUEST_HANAUTH_GAMERUNAUTH:
			{
#ifdef USE_HANAUTH
#ifdef _KOREA  // -- �ǽð� ����üũ�� �ѱ� NHN�� �����Ѵ�.
				// �ǽð� ����üũ ����
/*				printf( "Request user HanAuth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_HanAuth_GameRunAuth	*pRecvMsg = (sRequest_HanAuth_GameRunAuth *)pPacket;

				// HanAuth ���������� ��ģ��.

				char szOutBuf[ SIZE_OUTBUFFER ] = {0x00};

				int ret = HanAuthForSvr( pRecvMsg->userid, pRecvMsg->authstring, szOutBuf, SIZE_OUTBUFFER );

				if( ret == 0 )
				{
					// AccountDBManager�� ������ ���� ���̸� ���� üũ�Ѵ�.
					char szTempOutBuf[ SIZE_OUTBUFFER ] = {0x00};

					// ���� ������ ����
					strcpy(szTempOutBuf, szOutBuf);
					char* pToken = NULL;
					char szAge[32];
					pToken = strtok(szTempOutBuf, "|");
					if(pToken != NULL)		pToken = strtok(NULL, "|");
					if(pToken != NULL)		pToken = strtok(NULL, "|");

					strncpy(szAge, pToken, sizeof(szAge));
					SI32 siAge = atoi(szAge);

					// ������ ���̿� ��
					if(!(pRecvMsg->usServerAge <= siAge))
					{
						// ���̰� �ȵǼ� ������ ���� �� �� ����.
						sResponse_GameRunAuth	sendMsg;

						sendMsg.packetHeader.usSize = sizeof( sendMsg );
						sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH;

						sendMsg.usCharID = pRecvMsg->usCharID;

						sendMsg.siResult = 0;	// ������ ����
						printf( "CharID:%s, ServerAge:%d, UserAge:%d\n", sendMsg.usCharID, pRecvMsg->usServerAge, siAge);

						// �α� ���
						g_CLogPrint.WriteFileLog("HanAuth_Error.txt", __FILE__, __LINE__, "[GAMERUNAUTH] refuse to use server - UserID : [%s], ServerAge : [%d], UserAge : [%d]", pRecvMsg->userid, pRecvMsg->usServerAge, siAge);

						if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED ) 
						{
							pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	
						}
						break;
					}

					sResponse_GameRunAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH;

					sendMsg.usCharID = pRecvMsg->usCharID;

					sendMsg.siResult = 1;	// ������ ����

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED )
					{
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	
					}

					// �α� ���
					//g_CLogPrint.WriteFileLog("HanAuth.txt", __FILE__, __LINE__, "[GAMERUNAUTH] allow to use server - UserID : [%s], ServerAge : [%d], UserAge : [%d]", pRecvMsg->userid, pRecvMsg->usServerAge, siAge);

				}
				else
				{
					sResponse_GameRunAuth	sendMsg;

					sendMsg.packetHeader.usSize = sizeof( sendMsg );
					sendMsg.packetHeader.usCmd = AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH;

					sendMsg.usCharID = pRecvMsg->usCharID;

					sendMsg.siResult = 1;	// ������ ����

					if( pSession && pSession->GetState() == SESSION_STATE_ESTABLISHED )
					{
						pSession->GetSendBuffer()->Write( (BYTE *)&sendMsg );	
					}

					// �α� ���
					//g_CLogPrint.WriteFileLog("HanAuth_Error.txt", __FILE__, __LINE__, "[GAMERUNAUTH] HanAuthForServer() Error - UserID : [%s], ErrorCode : [%d]", pRecvMsg->userid, ret);
				}*/
#endif
#endif //USE_HANAUTH
			}
			break;

		case AUTHMSG_REQUEST_GMTOOLAUTH:
			{
				printf( "Request GMTOOL auth from GameServer\n" );

				// Ŀ�ǵ忡 ���� �޽��� ����ü ĳ����
				sRequest_GMToolAuth*	pRecvMsg = (sRequest_GMToolAuth *)pPacket;

				// AccountDBManager�� ���� ��û
				sDBRequest_GMTOOLLogin	sendMsg;

				sendMsg.packetHeader.usCmd = DBMSG_REQUEST_GMTOOLLOGIN;
				sendMsg.packetHeader.usSize = sizeof( sendMsg );

				sendMsg.usGameServerID = pSession->m_usIndex;
				sendMsg.usCharID = pRecvMsg->usCharID;

				memcpy( sendMsg.userid, pRecvMsg->userid, 20 );
				sendMsg.userid[ 19 ] = NULL;

				memcpy( sendMsg.userpw, pRecvMsg->userpw, 20 );
				sendMsg.userpw[ 19 ] = NULL;

				g_accountDB.SendMsg( (sPacketHeader *)&sendMsg );

				printf( "ID:%s, PW:%s, CharID:%d \n", sendMsg.userid, sendMsg.userpw, sendMsg.usCharID );
			}
			break;
		}

		pSession->GetRecvBuffer()->RemoveFirstPacket();
	}
}

void AuthGameProtocol::Update()
{
/*	if( m_kUpdateTimer_GamepotJP.IsTimed(::GetTickCount()) == true )
	{
		GamePotReport(g_usermanager.m_GamepotJPCount);
	}

	if( m_kUpdateTimer_HangameJP.IsTimed(::GetTickCount()) == true )
	{
		HTTPHangameRTA(g_usermanager.m_HanGameJPCount);
	}*/
}
