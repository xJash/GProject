#include "Client.h"

#include "..\..\NetworkLib\ITZNetLib\ITZNetworkThread.h"
#include "..\..\NetworkLib\ITZNetLib\ITZSessionFactory.h"
#include "..\..\NetworkLib\ITZNetLib\ITZSessionManager.h"
#include "..\..\NetworkLib\ITZNetLib\ITZSession.h"
#include "..\..\NetworkLib\ITZNetLib\ITZNetOverlapped.h"
#include "..\..\NetworkLib\ITZNetLib\ITZPerson.h"

#include "..\..\NetworkLib\ITZNetLib\ITZRecvBuffer.h"
#include "..\..\NetworkLib\ITZNetLib\ITZSendBuffer.h"

#include "..\Server\Gameprotocol\GameProtocol.h"

#include "ITZEncrypt.h"
#include "Interface\LoginClient\LoginClient.h"
#include "GameContract\GameContract.h"
#include "Char\CharManager\CharManager.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "Interface/HtmlDlg/HtmlDlg.h"
#include "Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include <wininet.h>

#include "../Client/NInterface/NLogin/NLogin.h"
#include "../Client/NInterface/NNoticeAdminDlg/NNoticeAdminDlg.h"
#include "../Client/NInterface/nselectworldlistdlg/SelectWorldListDlg.h"

#include "NUtil.h"
#include "NDataLoader.h"
#include "NFile.h"
#include "NUtil.h"

#include "../Apex/gamecode.h"

// LZF ����
#include "../../NetworkLib/ITZNetLib/NLZF.h"

// ����S�� FRONTSERVER PORT �� 11000 �̴�.
#ifdef _KOREA
	#ifdef _DEBUG
		#define FRONTSERVER_PORT	5700
	#else
		#define FRONTSERVER_PORT	11000
	#endif
//KHY - 0204 -  �߱� PurpleAuth ���� ���
#elif USE_PORTEAUTH
	#define FRONTSERVER_PORT	11000
#else
	#define FRONTSERVER_PORT	5700
#endif

#ifdef USE_GAME_GUARD_CLIENT

	extern CNPGameLib * pNpgl;

#endif

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	extern char g_szServerIP[20];
	extern char g_szServerPORTE[20];
#endif

extern SI16 g_siChannelingCode;
extern char g_nm_id[ 1024 ];
extern char g_nm_pw[ 1024 ];

void cltClient::InitNetwork()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);

	if(err != 0)
	{
		MsgBox(TEXT("void cltClient::InitNetwork()"), TEXT("f8j3:%d"), err);
		return ;
	}

	if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return ;
	}

	sf.CreateFactory(&sm, 2, 300000, 300000); // ���� ��ü���� �����ϰ� SessionManager�� ������ �ش�.
	

}

void cltClient::WinSockConnect()
{
	pGameSession	= sm.GetSession(0);			// ���� �޴����κ��� �ϳ��� Ŭ���̾�Ʈ�� ������ ��´�. 
	pFrontSession	= sm.GetSession(1);


	overlapped.CreateOverlapped(&sm);		//Overlapped IO�� �����Ѵ�. 
}

void cltClient::WinSockAction()
{

	// ĳ���Ͱ����ڰ� �����ɶ������� ��Ʈ��ũ �޽����� ó���ؼ��� �ȵȴ�.
	//��Ʈ��ũ�� ����� �� ĳ���Ͱ� �ڵ����� �����Ǳ� �����̴�. 
	if(pclCM == NULL)return ;

	sm.Update();

	if(clUserState.GetState() <= USERSTATE_GAME_CONNECTED)
	{
		FrontServerAction();
	}
	if(clUserState.GetState() >= USERSTATE_GAME_CONNECTING)
	{
		GameServerAction();
	}

}


// ����ĳ���͸� pclCM�� �����Ѵ�. 
void  cltClient::SetSessionChar()
{
	pclCM->CR[1] = (cltCharCommon*)sf.GetPerson(1);
	pclCM->CR[1]->SetpclCM(pclCM);

	pclCM->CR[2] = (cltCharCommon*)sf.GetPerson(2);
	pclCM->CR[2]->SetpclCM(pclCM);

}

// ����Ʈ ������ �޽����� ������. 
BOOL cltClient::SendFrontServerMsg(sPacketHeader* psendmsg)
{
	if(bFrontServerSecretKeySwitch == false)return FALSE;

	ITZEncrypt *pEncrypt = pFrontSession->GetEncrypt();

	// �޽����� ��ȣȣ�Ѵ�. 
	pEncrypt->Encode( (UI08*)psendmsg, cSecretBuffer );
	pFrontSession->GetSendBuffer()->Write((BYTE*)cSecretBuffer );
	
	return TRUE;
}



// �޽����� ������ ������. 
BOOL cltClient::SendMsgToServer(sPacketHeader* pmsg)
{
#ifdef _CHINA
	// APEX-
	EnterCriticalSection( &m_CSSendToGameServer );
	// -APEX

	if(bGameServerSecretKeySwitch == false) 
	{
		// APEX-
		LeaveCriticalSection( &m_CSSendToGameServer );
		// -APEX

		return FALSE;
	}
#else
	if(bGameServerSecretKeySwitch == false)return FALSE;
#endif

	ITZEncrypt *pEncrypt = pGameSession->GetEncrypt();

	UI32 siCompSize = 0;

	if( pmsg->usSize >= 200 )		// 200����Ʈ���� �����Ѵ�.
	{
		BYTE* pMsg = (BYTE*)pmsg;
		memcpy(m_bufCompress, pMsg, sizeof(sPacketHeader));
		siCompSize = NLZF::Compress( &pMsg[sizeof(sPacketHeader)],			pmsg->usSize - sizeof(sPacketHeader),
									 &m_bufCompress[sizeof(sPacketHeader)], sizeof(m_bufCompress) - sizeof(sPacketHeader) );
	}

	if( siCompSize != 0 && siCompSize < pmsg->usSize - sizeof(sPacketHeader) )
	{
		sPacketHeader* pCompMsg = (sPacketHeader*)m_bufCompress;
		pCompMsg->usSize = sizeof(sPacketHeader) + siCompSize;

		// ��Ŷ ����� �ֻ��� ��Ʈ�� ��Ʈ�ϸ�, ��Ŷ�� ����� ���̴�.
		pCompMsg->usCmd |= 0x8000;

		// �޽����� ��ȣȭ�Ѵ�. 
		pEncrypt->Encode( m_bufCompress, cSecretBuffer );
	}
	else
	{
		// �޽����� ��ȣȭ�Ѵ�. 
		pEncrypt->Encode( (UI08*)pmsg, cSecretBuffer );
	}

	pGameSession->GetSendBuffer()->Write((BYTE*)cSecretBuffer);

	// APEX-
#ifdef _CHINA
	LeaveCriticalSection( &m_CSSendToGameServer );
#endif
	// -APEX
	return TRUE;
}

void cltClient::FrontServerOperation(sPacketHeader *pPacket)
{
#ifdef _DEBUG
	pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "sRequest_NetmarbleJP_LogIn  %d" ,
		pPacket->usCmd);
#endif

	switch(pPacket->usCmd)
	{
	case FRONTMSG_RESPONSE_SECRETKEY:
		{
			sResponse_SecretKey* pRecvMsg = (sResponse_SecretKey*)pPacket;

			ITZEncrypt* pencrypt = pFrontSession->GetEncrypt();

			pencrypt->SetKey(pRecvMsg->ucKey1, pRecvMsg->ucKey2);

#ifdef _CHINA // dhm-
			m_pClientDiffHellMan->create_a0();
			m_pClientDiffHellMan->encrypt_a0_with_PublicKey_Key0();

			sRequest_DiffHellManKey sendMsg;
			sendMsg.packetHeader.usSize	= sizeof(sendMsg);
			sendMsg.packetHeader.usCmd = FRONTMSG_REQUEST_DIFFHELLMAN_KEY;

			memcpy( sendMsg.tempKey, m_pClientDiffHellMan->m_pstPacket, m_pClientDiffHellMan->m_pstPacket->sPacketSize );
			
			ITZEncrypt *pEncrypt = pFrontSession->GetEncrypt();
			// �޽����� ��ȣȣ�Ѵ�. 
			pEncrypt->Encode( ((UI08*)((sPacketHeader*)&sendMsg)), cSecretBuffer );
			pFrontSession->GetSendBuffer()->Write((BYTE*)cSecretBuffer );
//			bFrontServerSecretKeySwitch	= true;
#else
			// ��ȣȭŰ�� ����Ʈ �����κ��� �޾����� Ȯ���Ѵ�. 
			bFrontServerSecretKeySwitch	= true;
#endif
		}
		break;
	case FRONTMSG_RESPONSE_JOINGAME:
		{
			sResponse_JoinGame* pclMsg = (sResponse_JoinGame*)pPacket;

			TCHAR* pText = GetTxtFromMgr(925);
		
			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
		}
		break;

	case FRONTMSG_RESPONSE_NETMARBLEJP_LOGIN:
		{
			sResponse_NetmarbleJP_LogIn *pRecvMsg = (sResponse_NetmarbleJP_LogIn *)pPacket;

			MStrCpy( szID, pRecvMsg->userid, 20 );
			MStrCpy( szPassword, pRecvMsg->userpw, 20 );

#ifdef _DEBUG
			pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "sRequest_NetmarbleJP_LogIn  %s %s" ,
				pRecvMsg->userid , pRecvMsg->userpw);
#endif

			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( szID );
			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( szPassword );
			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();

		}
		break;


	case FRONTMSG_RESPONSE_LOGIN:
		{
			sResponse_LogIn* pRecvMsg = (sResponse_LogIn*)pPacket;

			if (pRecvMsg->siAccountStatus == -1)
			{
				TCHAR *pTitle = GetTxtFromMgr(836);
				TCHAR *pText = GetTxtFromMgr(6264);

				if (pTitle != NULL && pText != NULL)
				{
					m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				}

				break;
			}

//			WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "sResponse_LogIn-Result=%d", pRecvMsg->usResult);

#ifdef USE_HANAUTH
			if(pRecvMsg->usResult != 0)
			{
				m_siHanAuth_TryCount++;
//				WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "m_siHanAuth_TryCount=%d", m_siHanAuth_TryCount);
			}
#endif // USE_HANAUTH

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
			if(pRecvMsg->usResult != 0)
			{
				m_siPorteAuth_TryCount++;
			}
#endif // USE_PORTEAUTH

#ifdef _JAPAN
			// �Ϻ��� ���α��� ���н� ī��Ʈ�� �Ѵ�.
			if( pRecvMsg->usResult != 0 )
			{
				if( g_siChannelingCode == CHANNELINGCODE_GAMEPOTJP ||
					g_siChannelingCode == CHANNELINGCODE_HANGAMEJP ||
					g_siChannelingCode == CHANNELINGCODE_GAMANIAJP ||
					g_siChannelingCode == CHANNELINGCODE_NEXONJP )
				{
					m_siHanAuth_TryCount++;
				}
			}
#endif


#ifdef _EUROPE
			if ( 0 != pRecvMsg->usResult )
			{
				// ���н� ���̵�/��� �����
				ZeroMemory( szID, sizeof(szID) );
				ZeroMemory( szPassword, sizeof(szPassword) );
			}
#endif

#ifdef _KOREA
			if ( 0 != pRecvMsg->usResult )
			{
				// ���н� ���̵�/��� �����
				ZeroMemory( szID, sizeof(szID) );
				ZeroMemory( szPassword, sizeof(szPassword) );
			}
#endif
			switch(pRecvMsg->usResult)
			{
			case 0:	
				{	// �α��� ����. 
					clUserState.SetState(USERSTATE_FRONT_AUTHOK);
					// ����Ű Ȯ�� 
					siAuthKey = pRecvMsg->siAuthKey;

					// ���̸� �����Ѵ�
					siServiceAge = pRecvMsg->m_uiRealAge;

					// �Ѱ��� ���뺸��
					if(pclClient->siServiceArea == ConstServiceArea_NHNChina)
					{
						HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(clSelectedWorldInfo.baseinfo.siServerID ,m_szPorteAuth_UserID, HANREPORT_CLIENT_LOGINOK);
					}
					else
					{
						HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_LOGINOK);
					}

#ifdef USE_GAME_GUARD_CLIENT
					// ���Ӱ��忡 ������ �������� ����
					pNpgl->Send( szID );

#endif
					// �ؽ� ä�θ��� ���� IDüũ -�ؽ��� DB���� ID�� ��ȯ�Ǿ� ���;� �Ѵ�.
					memcpy( szID, pRecvMsg->userid, 20 );

					TCHAR* pText = NULL;
					pText = GetTxtFromMgr(926);
					
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
	
					if(pRecvMsg->siGameMasterLevel >= BASIC_PLAYERMASTER_LEVEL)
					{
						bLoginWhileServerDownSwitch = true;		// ��ڴ� �����߿��� ������ �α��� �� �� �־�� �Ѵ�. 
					}
					else
					{
						bLoginWhileServerDownSwitch = false;
					}

					if ( pRecvMsg->szServerName[0] != NULL )
					{
						MStrCpy(szLastConnectServerName, pRecvMsg->szServerName,20);
					}
				}
				break;

			case 1:	// �α��� ����. (�߸��� ���̵�. ) 
				{
					TCHAR* pText = GetTxtFromMgr(928);
					
					/*cyj �α��ν����ص� �������� �ȶߵ��� ����
					if(siServiceArea ==  ConstServiceArea_English) 
					{
						ShellExecute( NULL, NULL, TEXT("http://kunshu.jp"), NULL, NULL, SW_SHOWNORMAL );
					}						
					else
					{						
						ShellExecute( NULL, NULL, TEXT("http://kunshu.jp"), NULL, NULL, SW_SHOWNORMAL );
					}
					*/
					
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
				}
				break;
			case 2:	// �α��� ���� (�߸��� �н�����)
				{
					TCHAR* pText = GetTxtFromMgr(929);
					
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
				}
				break;
			case 3:
				{
					//	TCHAR buffer[256] = TEXT("�������Դϴ�. ���� Ȩ�������� �����ϼ���.");	
					TCHAR* pText = GetTxtFromMgr(930);

					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
				}
				break;
			case 4:
				{
					TCHAR buffer[512];
					TCHAR temp[256];
					TCHAR* pText = GetTxtFromMgr(931);
					

					StringCchPrintf(buffer, 512, pText);

					switch(pRecvMsg->siBlockMode)
					{
					case 1:	// �Ϲݺ� 
						pText = GetTxtFromMgr(932);
						

						StringCchPrintf(temp, 256, pText, 
							pRecvMsg->siBlockYear,
							pRecvMsg->siBlockMonth,
							pRecvMsg->siBlockDay,
							pRecvMsg->siBlockHour,
							pRecvMsg->siBlockMinute);

						StringCchCat(buffer, 512, temp);

						pText = GetTxtFromMgr(933);
						

						StringCchPrintf(temp, 256, pText, pRecvMsg->szBlockReason);
						StringCchCat(buffer, 512, temp);


						break;
					case 2:	// ������ 
						{
							pText = GetTxtFromMgr(934);
							

							StringCchPrintf(temp, 256, pText);
							StringCchCat(buffer, 512, temp);

							pText = GetTxtFromMgr(933);
							
							StringCchPrintf(temp, 256, pText, pRecvMsg->szBlockReason);
							StringCchCat(buffer, 512, temp);
						}
						break;
					default:
						MsgBox(TEXT("fdf2jdsf"), TEXT("fdf93jf:%d"), pRecvMsg->siBlockMode);
					}

					pText = GetTxtFromMgr(935);
					

					StringCchPrintf(temp, 256, pText);
					StringCchCat(buffer, 512, temp);

					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
				}
				break;
			case 5:
				{
					TCHAR* pText = GetTxtFromMgr(936);
					
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );

					//ShellExecute( NULL, NULL, TEXT("http://goonzu.ndoors.com"), NULL, NULL, SW_SHOWNORMAL );
				}
				break;
			case 6:
				{
					if ( m_pDialog[NNOTICEADMIN_DLG] == NULL )
						CreateInterface ( NNOTICEADMIN_DLG ) ;

					TCHAR notice[512] = TEXT("") ;

					if ( siServiceArea == ConstServiceArea_English )
					{
						StringCchPrintf(notice, 512, TEXT("At the current moment you haven��t registered for the E-Mail verification system.")
							TEXT("You can only access and use the Game and Homepage services only if you register your e-mail verification.")
							TEXT("Please get your e-mail verification at your account info section."));
					}
					else
					{
						StringCchPrintf(notice, 512, TEXT(""));
					}

					((cltNNoticeAdminDlg*)m_pDialog[ NNOTICEADMIN_DLG ])->SetData(notice);
				}
				break;
			case 11:
				{
					TCHAR*  pText = GetTxtFromMgr( 6080 );
                                        
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
					break;

				}

				// �Ѱ��� ���� ����
			case 12:
				{
					//m_siHanAuth_TryCount++;
				}
				break;
				//---------------------------------------------------------
				//KHY - 0617 - �Ϻ� ä�θ� �߰�.
			case 13: // HANGAMEJP ��������
				{

				}
				break;
			case 14:  // GAMANIAJP ��������
				{

				}
				break;
			case 15:  // GAMEPOTJP ��������
				{

				}
				break;
			case 16:  // NDEJP ��������
				{

				}
				break;
			case 17:  // NEXONJP ��������
				{

				}
				break;
			case 18:  // IOVATION ���� ����
				{

				}
				break;
			case 30:  // USA ���ο� ���� ����
				{

				}
				break;

			default:
				{
					TCHAR buffer[256];
					TCHAR* pText = GetTxtFromMgr(937);
					

					StringCchPrintf(buffer, 256, pText, pRecvMsg->usResult);

					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );
				}
				break;

			}

			if( pRecvMsg->usResult ) {
				bLoginRequest = FALSE;
			}
		}
		break;

	case FRONTMSG_RESPONSE_NOTICE:
		{
			sResponse_Notice recvMsg;

			memcpy(&recvMsg, pPacket, pPacket->usSize);

			// ������ ȭ�鿡 ǥ���Ѵ�. 

			clUserState.SetState(USERSTATE_FRONT_NOTICEOK);
		}
		break;

	case FRONTMSG_RESPONSE_WORLDLIST:
		{
			clWorldList.SetWorldList((sResponse_WorldList*)pPacket);

			clUserState.SetState(USERSTATE_FRONT_SERVERSELECTING);
		}
		break;


	case FRONTMSG_NOTIFY_WORLDREFRESHALL:
		{
			if( clUserState.GetState() == USERSTATE_FRONT_SERVERSELECTING ) 
			{
				clWorldList.SetWorldRefreshInfo( (sNotify_WorldRefreshAll *)pPacket );
			}
		}
		break;

	case FRONTMSG_RESPONSE_DIFFHELLMAN_KEY:
		{
#ifdef _CHINA // dhm-
			sResponse_DiffHellManKey* pRecvMsg = (sResponse_DiffHellManKey*)pPacket;

			memcpy( m_pClientDiffHellMan->m_client_buf, pRecvMsg->tempKey, Net_Packet_Max_Size );
			m_pClientDiffHellMan->decrypt_c0_with_PublicKey_Key0();
			m_pClientDiffHellMan->create_PrivateKey_Key1_with_c0();

			// ��ȣȭŰ�� ����Ʈ �����κ��� �޾����� Ȯ���Ѵ�. 
			bFrontServerSecretKeySwitch	= true;
#endif
		}
		break;

	case FRONTMSG_RESPONSE_PROMOTER_INFO:
		{
			sResponse_Promoter_Info* pRecvMsg = (sResponse_Promoter_Info*)pPacket;

			// ���� ���θ��Ϳ� �ڽ��� ĳ���� ������� ���� �����϶��� �� â�� ������. 
			// �� ĳ���� �����ϱ� �� 1ȸ �������.
			if( 0 == pRecvMsg->m_ret )
			{
				if( m_pDialog[ NSELECTWORLDLIST_DLG ] )
					((CNSelectWorldListDlg*)m_pDialog[ NSELECTWORLDLIST_DLG ])->SetPromoterText( pRecvMsg->m_szPromoterName, pRecvMsg->m_siServerID );
			}
		}
		break;

	default:
		{
			MsgBox(TEXT("fds974jjkfd"), TEXT("fdoi7jh3:%d"), pPacket->usCmd);
		}
	}

}

bool cltClient::FrontServerAction()
{
	static DWORD frontserverconnecttryclock;
	static DWORD dwTryClock = CurrentClock;
	static DWORD errorClock = CurrentClock;

	static TCHAR domain1[ 128 ];
	static TCHAR domain2[ 128 ];

	if(clUserState.GetState() == USERSTATE_FRONT_SERVERSELECTING)
	{
		
	}

	// ����Ʈ ������ Disconnected�����϶�. 
	if(pFrontSession->GetState() == SESSION_STATE_NONE)
	{
		// ���� ���� ���¿����� Front Session�� Connect�Ǿ� �־�� �ϴ� �����ε� 
		// �׷��� �����Ƿ� ���� ���¸� USERSTATE_DISCONNECTED�� �����Ѵ�. 
		if(    clUserState.GetState() > USERSTATE_FRONT_CONNECTING 
			&& clUserState.GetState() < USERSTATE_GAME_CONNECTED	)
		{
			clUserState.SetState(USERSTATE_DISCONNECTED);
		}

		// ���� ���°� ���� �õ����̸�, 
		if(clUserState.GetState() == USERSTATE_FRONT_CONNECTING)
		{
			//----------------------------------
			// 1�ʿ� �ѹ����� ������ �õ��Ѵ�. 
			//----------------------------------
			if(TABS(CurrentClock - frontserverconnecttryclock) > 1000)
			{
				frontserverconnecttryclock = CurrentClock;

				TCHAR domain1[128];
				TCHAR domain2[128];

				TCHAR* pdomain = NULL;
//KHY - 0204 -  �߱� PurpleAuth ���� ��� - �߱��� ��������(front)IP�� ���� H1���� �о�´�.
#ifdef USE_PORTEAUTH
				memcpy( domain1, g_szServerIP, 20 );
				pdomain = domain1;

				if(pdomain != NULL)
#else
				if(GetServeIPInFile(domain1, 128, domain2, 128) == true)
#endif
				{
					TCHAR* pdomain;

					if(TABS(CurrentClock - dwTryClock) < 10000 )
					{
						pdomain = domain1;
					}
					else
					{
						pdomain = domain1;

						if(TABS(CurrentClock - dwTryClock) > 20000 )
						{
							dwTryClock = CurrentClock;
						}
					}

#ifdef USE_HANAUTH
					pdomain = domain1;
					if (m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
						pdomain = domain2;
					else if (m_siHanAuth_ServiceTypeCode == SERVICE_REAL)
						pdomain = domain1;

					if(sm.Connect(1, pdomain, 11000) == pFrontSession)
//KHY - 0204 -  �߱� PurpleAuth ���� ���
#elif USE_PORTEAUTH
//g_szServerPORTE
					if(sm.Connect(1, pdomain, atoi(g_szServerPORTE)) == pFrontSession)
#else
					if(sm.Connect(1, pdomain, 5700) == pFrontSession)
#endif
					{
						((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( GetTxtFromMgr(926) );

						TCHAR ip[ 32 ];

						SOCKADDR_IN addr;
						int len = sizeof( addr );

						getsockname( sm.GetSession(1)->GetSocket(), (SOCKADDR *)&addr, &len );

						memcpy( ip, inet_ntoa( addr.sin_addr ), 20 );
						ip[ 19 ] = NULL;

						memcpy( sm.GetSession(1)->m_szIP, ip, 20 );

						clUserState.SetState(USERSTATE_FRONT_CONNECTED);

						// ����Ʈ �����κ��� ��ȣȭŰ�� ���� ���� �ʾ���. 
						bFrontServerSecretKeySwitch	= false;
					}
					else
					{
						((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( GetTxtFromMgr(938) );
					}
				}
				else
				{
					((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( GetTxtFromMgr(939) );
				}
			}
		}
	}
	// Front Session�� ����Ǿ� �ִ� �����̸�, 
	else if(pFrontSession->GetState() == SESSION_STATE_ESTABLISHED)
	{
		sPacketHeader* pPacket = (sPacketHeader*)pFrontSession->GetRecvBuffer()->GetFirstPacket();

		if(pPacket != NULL)
		{
			FrontServerOperation(pPacket);

			pFrontSession->GetRecvBuffer()->RemoveFirstPacket();
		}

		if(clUserState.GetState() >= USERSTATE_GAME_CONNECTED)
		{
			pFrontSession->CloseSocket();
		}
	}

	return true;
}


bool cltClient::GameServerAction()
{

	// ������ ������� ���� �����̸� ���� �õ��Ѵ�. 
	if(pGameSession->GetState() == SESSION_STATE_NONE)
	{
		if(clUserState.GetState() == USERSTATE_GAME_CONNECTING)
		{
			// ���Ӽ��� ���� ����. 
			if(sm.Connect(0, clSelectedWorldInfo.baseinfo.gameserverip, 
				clSelectedWorldInfo.baseinfo.gameserverport) == pGameSession)
			{


				TCHAR ip[ 32 ];

				SOCKADDR_IN addr;
				int len = sizeof( addr );

				getsockname( sm.GetSession(0)->GetSocket(), (SOCKADDR *)&addr, &len );

				memcpy( ip, inet_ntoa( addr.sin_addr ), 20 );
				ip[ 19 ] = NULL;

				memcpy( sm.GetSession(0)->m_szIP, ip, 20 );

				clUserState.SetState(USERSTATE_GAME_CONNECTED);

				// ���Ӽ����κ��� ��ȣȭŰ�� ���� ���� �ʾ���. 
				bGameServerSecretKeySwitch	= false;
			}
			else
			{
			}
		}
	}

	//cyj �������� ������ ����� ���� �޼��� �ڽ� ǥ�� �� ����
	if (pGameSession->GetState() == SESSION_STATE_NONE && clUserState.GetState() >= USERSTATE_GAME_AUTHOK
		&& bServerNotConnectSwitch == false 
		&& GetGameStatus() != GS_CONNECTFRONTSERVER )
	{
		TCHAR *pTitle = GetTxtFromMgr(5727);
		TCHAR *pText = GetTxtFromMgr(5728);
		g_ErrorMsg.Set(true, pTitle, pText);

		CreateInterface( NEXITCONFIRM_DLG );
		bServerNotConnectSwitch = true;
	}

	// ������ ���������� ����� �����̸� ������ ��Ŷ ó���� �Ѵ�. 
	if( pGameSession->IsActive() && pGameSession->GetState() == SESSION_STATE_ESTABLISHED)
	{

		int count = pGameSession->GetRecvBuffer()->GetPacketCount();
		//------------------------------------
		/*		SI32 orgnum = count;
		if(count >= 20)count = 20;

		TCHAR buffer[256];
		sprintf(buffer, TEXT("msgnum:%d(org:%d)"), count, orgnum);
		pclMessage->SetMsg(buffer);
		*/
		//------------------------------

		BYTE* pTempMsg;
		cltMsg* pclMsg;

		for( int i = 0; i < count; ++i )
		{
			pTempMsg = pGameSession->GetRecvBuffer()->GetFirstPacket();


			if(pTempMsg != NULL)
			{
				// ��ȣȭ ���� 
				if( pGameSession->GetEncrypt2()->Decode( pTempMsg, m_encRecvBuf ) == false )
				{
#ifdef _DEBUG
					//----------------------------------------------------------
					// �ӽ� �α� �߰� ����
					//----------------------------------------------------------
					UI16 uiCmd	= ((sPacketHeader*)pTempMsg)->usCmd;
					UI16 uiSize	= ((sPacketHeader*)pTempMsg)->usSize;
					UI08 uiKey1	= pGameSession->GetEncrypt2()->GetKey1();
					UI08 uiKey2	= pGameSession->GetEncrypt2()->GetKey2();

					// ���� �α� ����� �߰�
					pclClient->pclLog->FilePrint( TEXT("config\\PacketMessage.log"), TEXT("---ERROR CMD:%d\tSIZE:%d\tKEY1:%d\tKEY2:%d"), uiCmd, uiSize, uiKey1, uiKey2 );
					//----------------------------------------------------------
					// �ӽ� �α� �߰� ��
					//----------------------------------------------------------
#endif
					return false;
				}

				pclMsg = (cltMsg*)m_encRecvBuf;

				// Ŀ�ǵ��� �ֻ��� ��Ʈ�� ���࿩�η� ����Ѵ�.
				BYTE bufDecomp[MAX_CLTMSG_DATA_SIZE + 5000];
				if( pclMsg->clHead.usCmd & 0x8000 )
				{
					memcpy(bufDecomp, m_encRecvBuf, sizeof(sPacketHeader));
					UI32 uiSize = pclMsg->clHead.usSize - sizeof(sPacketHeader);

					TCHAR szMsg[1024];
					sprintf(szMsg, "recvCmd:%d, recvSize:%d\n", pclMsg->clHead.usCmd - 0x8000, uiSize + sizeof(sPacketHeader));
					OutputDebugString( szMsg );

					UI32 uiDecompSize = NLZF::Decompress( &m_encRecvBuf[sizeof(sPacketHeader)], uiSize,
														  &bufDecomp[sizeof(sPacketHeader)],	sizeof(bufDecomp) - sizeof(sPacketHeader) );
					if( uiDecompSize == 0 )		return false;

					pclMsg = (cltMsg*)bufDecomp;
					pclMsg->clHead.usSize = sizeof(sPacketHeader) + uiDecompSize;
					pclMsg->clHead.usCmd -= 0x8000;
				}

				InBufferMessageOperation(pclMsg, 1);

				pGameSession->GetRecvBuffer()->RemoveFirstPacket();
			}
		}
	}

	return true;
}


void cltClient::NetworkOperation()
{
	WinSockAction();
}

// ���Ͽ��� Server�� IP�ּҸ� ���´�.
bool cltClient::GetServeIPInFile(TCHAR* ip1, SI16 ip1txtSize, TCHAR*ip2, SI16 ip2txtSize)
{
	TCHAR abuffer[1024];
	NFile file; 
	if(file.LoadFile( TEXT("ServerIP.dat") ) == false)
	{
		return FALSE;
	}

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{
		NLoadCryptFile( TEXT("ServerIP.dat"),  (BYTE*)abuffer );
		abuffer[ pHeader->dwDataSize ] = NULL;
	}

//#ifdef _KOREA
#ifdef USE_HANAUTH

	char buf1[ 256 ] = {'\0'};
	char buf2[ 256 ] = {'\0'};
	_stscanf( abuffer, "%s %s", buf1, buf2 );

	strcpy( ip1, buf1 );
	strcpy( ip2, buf2 );

#else

	char buf[ 256 ] = {'\0'};
	_stscanf( abuffer, "%s", buf );

	char serverip1[ 256 ] = {'\0'};
	char serverip2[ 256 ] = {'\0'};

	strcpy( ip1, buf );
	strcpy( ip2, buf );

#endif

	return true;
}

