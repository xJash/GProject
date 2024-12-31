//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Client.h"
#include "..\..\resource.h"
#include "..\Interface\LoginClient\LoginClient.h"
#include "../Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"
#include "../NInterface/NLogin/NLogin.h"
#include "../../Apex/gamecode.h"

#include <Wininet.h>

#include "StmOCX.tlh"
#include <comutil.h>
#include <tchar.h>
#include <atlcomcli.h>
#include <stdio.h>

extern cltCommonLogic* pclClient;

// ���̵�, ��ȣ �Է� ���� Ȯ��. 
bool bIDPassswordInputSwitch	= false;
bool loginswitch				= false;
bool noticeswitch				= false;
bool worldlistswitch			= false;


extern SI16 g_siChannelingCode;
extern char g_nm_id[ 1024 ];
extern char g_nm_pw[ 1024 ];

// WEB LOGIN SERVICE
extern char g_szWeb_id[ 1024 ];
extern char g_szWeb_pw[ 1024 ];
extern bool g_bWebLoginService;

extern bool g_bHanAuth;
extern bool g_bUSA_Auth;
extern bool g_bWebLoginService;
extern DWORD dwQuitTimer;

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
extern bool g_bPorteAuth;
#endif

extern bool g_bIovationAuth;

// PCK : IOVATION ���� - blackbox
typedef HRESULT (*RegProto)();

// Ŭ���̾�Ʈ�� �Ͽ��� FrontServer�� �����ϰ� �����. 
bool cltClient::InitConnectToFrontServer()
{

	//-------------------------------
	// �α��� ��ȭ���ڸ� �غ��Ѵ�. 
	//-------------------------------
	bLoginRequest = FALSE;

	((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show();

	// ���̵�� ��ȣ�� �Է� ���� �ʾҴ�. 
	bIDPassswordInputSwitch = false;

	TCHAR buffer[256] = TEXT("") ;
	TCHAR* pText = GetTxtFromMgr(1036);
	
	StringCchPrintf(buffer, 256, pText);

	((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( buffer );

	return true;
}

// Ŭ���̾�Ʈ�� ��� ������ ������ �õ��Ѵ�. 
// 1: ���� ����. 
// -1:���� 
// 0: ��� 

SI32 cltClient::ConnectToFrontServer()
{
	// Ŭ���̾�Ʈ�� ��쿡�� ó���Ѵ�.(�ʿ����Ϳ����� ������� �ʴ´�. ) 
	if(GameMode != GAMEMODE_CLIENT) return 1;
	SI32 returnval = 0;
	
	if( bLoginRequest == FALSE && g_siChannelingCode > 0 ) 
	{
		returnval = LOGIN_OK;
	} 
	else if  (bLoginRequest == FALSE && g_bHanAuth)
	{
		returnval = LOGIN_OK;
	}
#ifdef _USA_NEW_AUTH_
	else if( bLoginRequest == FALSE && g_bUSA_Auth )
	{
		returnval = LOGIN_OK;
	}
#endif
//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	else if  (bLoginRequest == FALSE && g_bPorteAuth)
	{
		returnval = LOGIN_OK;
	}
#endif // USE_PORTEAUTH
	else if (bLoginRequest == FALSE && g_bWebLoginService)
	{
		returnval = LOGIN_OK;
	}
	// �ڵ� �α��� - ������ ���̵�� �н����带 �Է��� ���� �ִٸ�, �ڵ����� �α��� �ȴ�.
	else if ( bLoginRequest == FALSE && _tcslen(szID) > 0 && _tcslen(szPassword) > 0 )
	{
		returnval = LOGIN_OK;
	}
	else 
	{
		returnval = ((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->GetStatus();
	}

	switch(returnval)
	{
	case LOGIN_READY:
		break;

	case LOGIN_OK:
		{
			if( bLoginRequest == TRUE && GetTickCount() - dwLastLoginTick < 10000 ) {

				TCHAR buf[256];

				TCHAR* pText = GetTxtFromMgr(1037);
				

				StringCchPrintf( buf, 256, pText, 
					( GetTickCount() - dwLastLoginTick ) / 1000 );


				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( buf );

				
				return 0;
			}

			bLoginRequest = TRUE;
			dwLastLoginTick = GetTickCount();

			if( clUserState.GetState() == USERSTATE_FRONT_CONNECTING ||
				clUserState.GetState() == USERSTATE_FRONT_CONNECTED )  {

				pFrontSession->CloseSocket();

				Sleep( 200 );
			}

			stLoginData sdata;
			
			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->GetLoginData(&sdata);
			
			// �ݸ��� ������̸�,
			if( g_siChannelingCode == CHANNELINGCODE_NETMARBLEJP )
			{	
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "NetmarbleJP" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
			//---------------------------------------------------------------------------
			//KHY - 0617 - �Ϻ� ä�θ� �߰�.
			//---------------------------------------------------------------------------
#ifdef _JAPAN			
			// �Ѱ��� ������̸�,
			if( g_siChannelingCode == CHANNELINGCODE_HANGAMEJP )
			{	
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "HangameJP" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
			// �����Ͼƻ�����̸�,
			if( g_siChannelingCode == CHANNELINGCODE_GAMANIAJP )
			{	
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "GamaniaJP" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
			// ������ ������̸�,
			if( g_siChannelingCode == CHANNELINGCODE_GAMEPOTJP )
			{	
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "GamePotJP" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
			// �ؽ� ������̸�,
			if( g_siChannelingCode == CHANNELINGCODE_NEXONJP )
			{	
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "NexonJP" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
			// NDE ������̸�,
			if( g_siChannelingCode == 0 )
			{	
//				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "NdeJP" );
//				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();
//
//				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
//				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
#endif
			//---------------------------------------------------------------------------

			// [����] USA ���ο� ����.
			if( g_bUSA_Auth )
			{
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "USAHangame" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}

			// NHN - HanAuth ���
			if (g_bHanAuth)
			{
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "HanGame" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}

			//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
			if (g_bPorteAuth)
			{
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "PorteHanGame" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}
#endif // USE_PORTEAUTH

			// ���α��� ���
			if (g_bWebLoginService)
			{
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->SetText( "WebLogin" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[0]->Refresh();

				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->SetText( "password" );
				((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->m_pEdit[1]->Refresh();
			}

			// ���̵� ���´�. 
			MStrCpy( szID, sdata.m_strUserID, MAX_PLAYER_NAME);
			
			// ��ȣ�� ���´�.
			MStrCpy( szPassword, sdata.m_strUserPassword, MAX_PLAYER_NAME );

			// ���̵�� ��ȣ�� �Է� �Ǿ���. 
			bIDPassswordInputSwitch = true;
			loginswitch				= false;
			noticeswitch			= false;
			worldlistswitch			= false;

			// ���� ���·� �����Ѵ�. 
			clUserState.SetState(USERSTATE_FRONT_CONNECTING);
//#ifdef _DEBUG
			pclClient->pclLog->FilePrint("Config\\ErrorLog.log"," clUserState.SetState(USERSTATE_FRONT_CONNECTING) ");
//#endif

		}
		return 0;

	case LOGIN_CANCEL:
		return -1;		// ������ �����Ѵ�. 
		break;

	case LOGIN_ID_REGIST:
		if ( ! ((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->IsShow() )
		{
			TCHAR* pText = GetTxtFromMgr(1038);

			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show(pText);
		}

		break;
	}

	// ���̵�� ��ȣ�� ���� �Էµ��� �ʾҴٸ� , 
	if(bIDPassswordInputSwitch == false)return 0;

	//-----------------------------------------------------
	// FrontServer�� ���̵�� ��ȣ�� ������ �α��� ��Ų��. 
	//-----------------------------------------------------
	if(loginswitch == false && clUserState.GetState() == USERSTATE_FRONT_CONNECTED)
	{
		// ��ȣȭŰ�� �ޱ� ������ ����Ʈ ������ �޽����� �������� �ȵȴ�.!!!!!!!!!
		if(bFrontServerSecretKeySwitch == true)
		{
			loginswitch = true;
			
			// �ݸ��� ������� ���
			if( g_siChannelingCode == CHANNELINGCODE_NETMARBLEJP ) 
			{

				sRequest_NetmarbleJP_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_NETMARBLEJP_LOGIN;

				MStrCpy( sendmsg.userid, g_nm_id, 100 );
				MStrCpy( sendmsg.userpw, g_nm_pw, 100 );

				GetMacAddress( sendmsg.macaddress , 20);
//#ifdef _DEBUG
				pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "sRequest_NetmarbleJP_LogIn  %s %s %s" ,
						sendmsg.userid , sendmsg.userpw , sendmsg.macaddress );
//#endif

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);
			} 			
			//---------------------------------------------------------
			//KHY - 0617 - �Ϻ� ä�θ� �߰�.
			//---------------------------------------------------------
#ifdef _JAPAN
			// �Ѱ���.
			else if( g_siChannelingCode == CHANNELINGCODE_HANGAMEJP ) 
			{
				if(m_siHanAuth_TryCount > 1)
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);	TCHAR* pText  = GetTxtFromMgr(7503);
					MsgBox( pTitle, pText);					dwQuitTimer = 1;
				}
				else
				{
					sRequest_HANGAMEJP_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_HANGAMEJP_LOGIN;

					MStrCpy( sendmsg.userid, g_nm_id, sizeof(sendmsg.userid));
					MStrCpy( sendmsg.userpw, g_nm_pw, sizeof(sendmsg.userpw) );

					MStrCpy( szID, g_nm_id , MAX_PLAYER_NAME );
					MStrCpy( szPassword, g_nm_pw , MAX_PLAYER_NAME );

					GetMacAddress( sendmsg.macaddress , 20);

					pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "Hangame Request Login  %s %s" ,
						sendmsg.userid , sendmsg.macaddress );

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);
				}
			} 
			// �����Ͼ�
			else if( g_siChannelingCode == CHANNELINGCODE_GAMANIAJP ) 
			{
				if(m_siHanAuth_TryCount > 1)
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);	TCHAR* pText  = GetTxtFromMgr(7503);
					MsgBox( pTitle, pText);					dwQuitTimer = 1;
				}
				else
				{
					sRequest_GAMANIAJP_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_GAMANIAJP_LOGIN;

					MStrCpy( sendmsg.userid, g_nm_id, sizeof(sendmsg.userid));
					MStrCpy( sendmsg.userpw, g_nm_pw, sizeof(sendmsg.userpw) );

					MStrCpy( szID, g_nm_id , MAX_PLAYER_NAME );
					MStrCpy( szPassword, g_nm_pw , MAX_PLAYER_NAME );

					GetMacAddress( sendmsg.macaddress , 20);

					pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "Gamania Request Login  %s %s" ,
						sendmsg.userid , sendmsg.macaddress );

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);
				}
			} 
			// ������
			else if( g_siChannelingCode == CHANNELINGCODE_GAMEPOTJP ) 
			{
				if(m_siHanAuth_TryCount > 1)
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);	TCHAR* pText  = GetTxtFromMgr(7503);
					MsgBox( pTitle, pText);					dwQuitTimer = 1;
				}
				else
				{
					sRequest_GAMEPOTJP_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_GAMEPOTJP_LOGIN;

					MStrCpy( sendmsg.userid, g_nm_id,  sizeof(sendmsg.userid) );
					MStrCpy( sendmsg.userpw, g_nm_pw, sizeof(sendmsg.userpw) );

					MStrCpy( szID, g_nm_id , MAX_PLAYER_NAME );
					MStrCpy( szPassword, g_nm_pw , MAX_PLAYER_NAME );

					GetMacAddress( sendmsg.macaddress , 20);

					pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "Gamepot Request Login  %s %s" ,
						sendmsg.userid ,  sendmsg.macaddress );

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);
				}
			} 
			// �ؽ�
			else if( g_siChannelingCode == CHANNELINGCODE_NEXONJP ) 
			{
				if(m_siHanAuth_TryCount > 1)
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);	TCHAR* pText  = GetTxtFromMgr(7503);
					MsgBox( pTitle, pText);					dwQuitTimer = 1;
				}
				else
				{
					sRequest_NEXONJP_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_NEXONJP_LOGIN;

					MStrCpy( sendmsg.userid, g_nm_id,  512); // �ؽ��� ID�ȿ� ��Ÿ������ ��� ���´�.
					MStrCpy( sendmsg.userpw, g_nm_pw, sizeof(sendmsg.userpw) );

					// ID�� ���߿� AC���� ���ƿ;� �� �� �ִ�.
					//MStrCpy( szID, g_nm_id , MAX_PLAYER_NAME );
					//MStrCpy( szPassword, g_nm_pw , MAX_PLAYER_NAME );

					GetMacAddress( sendmsg.macaddress , 20);

					pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "Nexon Request Login  %s %s" ,
						sendmsg.userid ,  sendmsg.macaddress );

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);
				}
			} 
#endif
			//---------------------------------------------------------
			else if ( g_bWebLoginService )
			{
#ifdef _TAIWAN
				sRequest_Taiwan_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_TAIWAN_LOGIN;

				MStrCpy( sendmsg.szGameAccount,		g_szWeb_id, sizeof(sendmsg.szGameAccount) );
				MStrCpy( sendmsg.szOneTimePassword, g_szWeb_pw, sizeof(sendmsg.szOneTimePassword) );

				GetMacAddress( sendmsg.macaddress , 20);

//#ifdef _DEBUG
				pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "sRequest_Taiwan_LogIn  %s %s" ,
					sendmsg.szGameAccount , sendmsg.szOneTimePassword);
//#endif

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);
#endif
			}
#ifdef _USA_NEW_AUTH_
			// [����]  USA ���ο� ����.
			else if ( g_bUSA_Auth )
			{
				//MessageBox(NULL, "USA �����Ϸ��� ���⿡ �Դ�.", "USA ����", 0 );
								
				sRequest_USA_LogIn sendMsg;

				sendMsg.packetHeader.usSize	= sizeof(sendMsg);
				sendMsg.packetHeader.usCmd	= FRONTMSG_REQUEST_USA_LOGIN;

				memcpy( sendMsg.authstring, m_szUSAAuth_String, sizeof(sendMsg.authstring) );

				pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "sRequest_USA_LogIn  %s", sendMsg.authstring );
							
				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendMsg);

				//MessageBox(NULL, sendMsg.authstring, "USA ����", 0 );
			}
#endif

#ifdef USE_HANAUTH
			else if ( g_bHanAuth )
			{
				if(m_siHanAuth_TryCount > 3)
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);
					TCHAR* pText  = GetTxtFromMgr(7503);

					MsgBox( pTitle, pText);
					dwQuitTimer = 1;
				}
				else
				{
					sRequest_HanAuth_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_HANAUTH_LOGIN;

					// ������Ʈ�� ���
					SI32 siHanAuthRet = GetAuthString(m_szHanAuth_AuthString, SIZE_AUTHSTRING);
					if(siHanAuthRet != 0)		{		m_szHanAuth_GameString[0] = '\0';		}

					if(strlen(m_szHanAuth_GameString) <= 0)
					{
						// ���� ���� Ŭ���̾�Ʈ ���� ����
						TCHAR* pTitle = GetTxtFromMgr(3168);
						TCHAR* pText  = GetTxtFromMgr(7503);

						MsgBox( pTitle, pText);
						dwQuitTimer = 1;
					}

					MStrCpy( sendmsg.authstring, m_szHanAuth_AuthString, SIZE_AUTHSTRING );
					MStrCpy( sendmsg.userid,	 m_szHanAuth_UserID,	MAX_PLAYER_NAME );
					sendmsg.userpw[0] = '\0';

					GetMacAddress( sendmsg.macaddress , 20);

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);

	//				WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Send sRequest_HanAuth_LogIn");
				}
			}
#endif // USE_HANAUTH

			//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
#ifndef _SERVER //������ ���ǵǾ� ���� �ʴٸ�.
			else if ( g_bPorteAuth )
			{
				if(m_siPorteAuth_TryCount > 3) // 3�� �õ�.
				{
					// ���� ���� Ŭ���̾�Ʈ ���� ����
					TCHAR* pTitle = GetTxtFromMgr(3168);
					TCHAR* pText  = GetTxtFromMgr(7503);

					MsgBox( pTitle, pText);
					dwQuitTimer = 1;
				}
				else
				{
					sRequest_PorteAuth_LogIn sendmsg;

					sendmsg.packetHeader.usSize	= sizeof(sendmsg);
					sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_PORTEAUTH_LOGIN;

					// ID �޾ƿ���.
					SI32 siPorteAuthRet = PubGetUserID(m_szPorteAuth_UserID, sizeof(m_szPorteAuth_UserID));
					if(siPorteAuthRet != 0)		{		m_szPorteAuth_UserID[0] = '\0';		}

					// Auth Ƽ�� �޾� ����.
					siPorteAuthRet = PubGetAuthTicket(m_szPorteAuth_szAuthTICKET, sizeof(m_szPorteAuth_szAuthTICKET));
					if(siPorteAuthRet != 0)		{		m_szPorteAuth_szAuthTICKET[0] = '\0';		}

					if(strlen(m_szPorteAuth_szAuthTICKET) <= 0)
					{
						// ���� ���� Ŭ���̾�Ʈ ���� ����
						TCHAR* pTitle = GetTxtFromMgr(3168);
						TCHAR* pText  = GetTxtFromMgr(7503);

						MsgBox( pTitle, pText);
						dwQuitTimer = 1;
					}

					MStrCpy( sendmsg.authstring, m_szPorteAuth_szAuthTICKET, sizeof(m_szPorteAuth_szAuthTICKET) );
					MStrCpy( sendmsg.userid,	 m_szPorteAuth_UserID,	MAX_PLAYER_NAME );
					sendmsg.userpw[0] = '\0';

					MStrCpy( szID, m_szPorteAuth_UserID , MAX_PLAYER_NAME );
					GetMacAddress( sendmsg.macaddress , 20);

					// ����Ʈ ������ �޽����� ������. 
					SendFrontServerMsg((sPacketHeader*)&sendmsg);

					//				WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Send sRequest_HanAuth_LogIn");
				}
			}
#endif
#endif // USE_PORTEAUTH

#ifdef _IOVATION
			// PCK : IOVATION������ ���� ���ο� ��Ŷ �ۼ� (2009.02.03)
			else if( g_bIovationAuth )
			{
				sRequest_English_LogIn sendmsg;

				// BlackBox ���
				Registeriovation();

				HRESULT hr;
				CComPtr<IStm>	clIStm;

				char	szBlackBox[2048] = { '\0', };

				hr = clIStm.CoCreateInstance( CLSID_Stm );
				if( SUCCEEDED(hr) )
				{
					//BSTR	bstrVersion;
					//bstrVersion = clIStm->ioVersion();

					BSTR	bstrBlackbox;
					bstrBlackbox = clIStm->ioBegin();

					int len = ::WideCharToMultiByte(CP_ACP, 0, bstrBlackbox, wcslen(bstrBlackbox), szBlackBox, 2048, NULL, NULL);
					printf("BlackBox String -----\n%s\n", szBlackBox);

					if(clIStm)		clIStm.Release();
				}

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_ENGLISH_LOGIN;

				MStrCpy(sendmsg.userid, szID,		MAX_PLAYER_NAME );
				MStrCpy(sendmsg.userpw, szPassword, MAX_PLAYER_NAME );
				
				GetMacAddress( sendmsg.macaddress , 20);
				
				MStrCpy(sendmsg.Blackbox, szBlackBox, 2048);

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);
			}
#endif
			else
			{
#ifdef _CHINA // dhm-
				sRequest_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_LOGIN;

				m_pClientDiffHellMan->encrypt_data_with_PrivateKey_Key1( (const char*)szID, Net_Packet_Max_Size );
				memcpy(sendmsg.userid, m_pClientDiffHellMan->m_client_buf,	Net_Packet_Max_Size );
				m_pClientDiffHellMan->encrypt_data_with_PrivateKey_Key1( (const char*)szPassword, Net_Packet_Max_Size );
				memcpy(sendmsg.userpw, m_pClientDiffHellMan->m_client_buf, Net_Packet_Max_Size );

				GetMacAddress( sendmsg.macaddress , 20);

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);

#elif _JAPAN
				//---------------------------------------------------------
				//KHY - 0617 - �Ϻ� ä�θ� �߰�.

				// NDE
				sRequest_NDEJP_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_NDEJP_LOGIN;

	#ifndef _DEBUG // ����� ��尡 �ƴҶ���.
				//  NDE �� ���, Ŭ���̾�Ʈ �α����� ������ �������� �ٿ��ش�. ���α��ν�, ���� ��û��, �����ʿ�. 
				strcat( szID, "@ND"); 
	#endif				
				MStrCpy(sendmsg.userid, szID,		MAX_PLAYER_NAME );
				MStrCpy(sendmsg.userpw, szPassword, MAX_PLAYER_NAME );

				GetMacAddress( sendmsg.macaddress , 20);

				pclClient->pclLog->FilePrint("Config\\ErrorLog.log", "NDE Request Login  %s %s" ,
									sendmsg.userid ,  sendmsg.macaddress );
				
				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);

#elif _EUROPE
				sRequest_EUROPE_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_EUROPE_LOGIN;

				MStrCpy(sendmsg.userid, szID,		MAX_PLAYER_NAME );
				MStrCpy(sendmsg.userpw, szPassword, MAX_PLAYER_NAME );

				GetMacAddress( sendmsg.macaddress , 20);

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);

#elif _KOREA	//////////////////////////////////////////////////
				//	[��ȣ_NHN->NDOORS] �̰� ���� ����S �÷ξ� �߰�
				sRequest_LogIn sendmsg;

				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_KOREA_LOGIN;

				MStrCpy(sendmsg.userid, szID,		MAX_PLAYER_NAME );
				MStrCpy(sendmsg.userpw, szPassword, MAX_PLAYER_NAME );

				GetMacAddress( sendmsg.macaddress , 20);

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);
#else	// _KOREA

				//---------------------------------------------------------
				sRequest_LogIn sendmsg;

//#ifdef _ENGLISH
//#ifndef _DEBUG	//	����� ��尡 �ƴҶ���
//				// �۷ι��� ��� Ŭ���̾�Ʈ �α����̱� ������ �������� �ڿ� "@GB"�� �ٿ��ش�. (09.03.18)
//				strcat( szID, "@GB"); 
//#endif
//#endif
				sendmsg.packetHeader.usSize	= sizeof(sendmsg);
				sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_LOGIN;

				MStrCpy(sendmsg.userid, szID,		MAX_PLAYER_NAME );
				MStrCpy(sendmsg.userpw, szPassword, MAX_PLAYER_NAME );

				GetMacAddress( sendmsg.macaddress , 20);

				// ����Ʈ ������ �޽����� ������. 
				SendFrontServerMsg((sPacketHeader*)&sendmsg);
#endif

			}

			TCHAR* pText = GetTxtFromMgr(1039);

			((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );

		}

	}

	//--------------------------------------------------
	// FrontServer�� ���������� ��û�Ѵ�. 
	//--------------------------------------------------
	if(noticeswitch == false && clUserState.GetState() == USERSTATE_FRONT_AUTHOK)
	{
		noticeswitch = true;

		sRequest_Notice sendmsg;

		sendmsg.packetHeader.usSize	= sizeof(sendmsg);
		sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_NOTICE;

		SendFrontServerMsg((sPacketHeader*)&sendmsg);

		TCHAR* pText = GetTxtFromMgr(1040);

		((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Show( pText );


	}
	//--------------------------------------------------
	// FrontServer�� ���� ����� ��û�Ѵ�.
	//--------------------------------------------------
	if(worldlistswitch == false && clUserState.GetState() == USERSTATE_FRONT_NOTICEOK)
	{
		worldlistswitch = true;

		sRequest_WorldList sendmsg;

		sendmsg.packetHeader.usSize	= sizeof(sendmsg);
		sendmsg.packetHeader.usCmd	= FRONTMSG_REQUEST_WORLDLIST;
		
		StringCchCopy( sendmsg.szAccountID, sizeof(sendmsg.szAccountID), szID );

		SendFrontServerMsg((sPacketHeader*)&sendmsg);

		// �α��� ��ȭ���ڸ� �����. 

		((CNLoginDlg*)m_pDialog[ NLOGIN_DLG ])->Hide();

		return 1;
	}

	return 0;
}

// ����Ʈ ������ ���� DB����ڸ� ��DB�� �����϶�� ��û�Ѵ�. 
void cltClient::RequestJoinGame()
{
	sRequest_JoinGame clMsg;
				
	clMsg.packetHeader.usSize	= sizeof(clMsg);
	clMsg.packetHeader.usCmd	= FRONTMSG_REQUEST_JOINGAME;
	
	DWORD Size = 256;
	TCHAR Buffer[ 256 ];
	
	if ( InternetGetCookie( TEXT("http://kunshu.jp"), TEXT("gzbanner"), Buffer, &Size ) == FALSE )
	{
		StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
	}
	else
	{
		/*
		if ( Size > 8 )
		{	
			if ( _tcsncmp( &Buffer[0], TEXT("gzbanner"), 8 ) == 0 || _tcsncmp( &Buffer[0], TEXT("GZBANNER"), 8 ) == 0 )
			{
				memcpy( clMsg.cookie, &Buffer[9], 20 );
				clMsg.cookie[ 19 ] = NULL;
			}
			else
			{
				_tcscpy( clMsg.cookie, TEXT("GAME") );
			}
		}
		else
		{
			_tcscpy( clMsg.cookie, TEXT("GAME") );
		}
		*/
		if ( Size > 8 && Size < 255 )
		{
			Buffer[ Size ] = NULL;

			TCHAR *pDest = _tcsstr( Buffer ,TEXT("gzbanner") );
			if ( pDest == NULL )
			{
				StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
			}
			else
			{
				SI16 Counter = 0;
				SI16 EqualPos = 0;
				bool bEqual = false;
				bool bFoundSeminicolon = false;
				
				while( pDest[ Counter ] != NULL )
				{
					if ( pDest[ Counter ] == TEXT('=') )
					{
						if ( bEqual == true )
						{
							bEqual = false;
							EqualPos = 0;
							break;
						}

						bEqual = true;
						EqualPos = Counter;
					}
					else if ( pDest[ Counter ] == TEXT(';') )
					{
						bFoundSeminicolon = true;
						break;
					}
					++Counter;
				}

				if ( bEqual == false )
				{
					StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
				}
				else
				{
					if ( bFoundSeminicolon )
					{
						if ( Counter - EqualPos < 2 )
						{
							StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
						}
						else
						{
							if ( Counter - EqualPos - 1 >= 20 )
							{
								StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
							}
							else
							{
								memcpy( clMsg.cookie, &pDest[9], Counter - EqualPos - 1 );
								clMsg.cookie[ Counter - EqualPos - 1 ] = NULL;
							}

							
						}
					}
					else
					{
						if ( Counter - EqualPos < 2 )
						{
							StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
						}
						else
						{
							if ( Counter - EqualPos - 1 >= 20 )
							{
								StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
							}
							else
							{
								memcpy( clMsg.cookie, &pDest[9], Counter - EqualPos - 1 );
								clMsg.cookie[ Counter - EqualPos - 1 ] = NULL;
							}
						}
					}
				}
				
			}
		}
		else
		{
			StringCchCopy( clMsg.cookie, 20, TEXT("GAME") );
		}
		
	}
	
	// SBS �� ��쿡�� ��ȣ�� �����Ѵ�.
	memcpy ( clMsg.userpw, szPassword, 20 );
	clMsg.userpw[ 19 ] = NULL;

	/*
	if ( RegistrationNumber > 0 )
	{
		TCHAR Buffer[256 ] = TEXT("");
		sprintf( Buffer, TEXT("%d"), RegistrationNumber );
		memcpy( clMsg.jumincode, Buffer, 7 );
		clMsg.jumincode[ 7 ] = NULL;
	}
	else
	{
		clMsg.jumincode[ 0 ] = NULL;
	}
	*/
				
	MStrCpy( clMsg.userid, szID,		MAX_PLAYER_NAME );
				
	// ����Ʈ ������ �޽����� ������. 
	SendFrontServerMsg((sPacketHeader*)&clMsg);
}

// Ŭ���̾�Ʈ�� �Ͽ��� GameServer�� �����ϰ� �����. 
bool cltClient::InitConnectToGameServer()
{
	// Ŭ���̾�Ʈ�� ��쿡�� ó���Ѵ�.(�ʿ����Ϳ����� ������� �ʴ´�. ) 
	if(GameMode != GAMEMODE_CLIENT) return true;

	// ���Ӽ����� ���ӽõ����·� �����Ѵ�. 
	// �̷��� �ϸ� ����Ʈ �������� ������ ����� �ȴ�. 
	clUserState.SetState(USERSTATE_GAME_CONNECTING);

	// �ʱ���Ӽ��� ���ӽÿ� �̴ϸ��� �������� �Ⱥ��������� �����Ѵ� (��� ,JAYCEE)
	bSmallMapSwitch = g_SoundOnOffDlg.m_bMiniMapShow;

	// Ÿ�̸� �ʱ�ȭ
	//m_kTimer_WaitGameLogin.SetActive(true, GetTickCount());
	
	return true;
}

SI32 cltClient::ConnectToGameServer()
{
	UI08 uiGamemode = 0;

	// Ŭ���̾�Ʈ�� ��쿡�� ó���Ѵ�.(�ʿ����Ϳ����� ������� �ʴ´�. ) 
	if(GameMode != GAMEMODE_CLIENT) return 1;

	// ������� CharUnique���� ���� �������� �ʾҴٸ� ��ٸ���. 
	if(MyCharUnique == 0)return 0;
	// ��ȣȭŰ�� ���� ���� ���ߴٸ� ��ٸ���. 
	if(bGameServerSecretKeySwitch	== false)return 0;

	// GameServer�� ������ ����ߴ�.
	clUserState.SetState(USERSTATE_GAME_AUTHOK);

	if( !g_SoundOnOffDlg.m_bFullScreenMode )
	{
		uiGamemode = 0;	// ������ ���
	} 
	else
	{
		// if( ����â + ���������̽� ��� )
		uiGamemode = 1;	// ����â + ���������̽� ���
		// else // ��üȭ�� + ���������̽� ���
		// uiGameMode = 2;
	}


	//----------------------------------------
	// ������ �����ϸ� GAMEMSG_REQUEST_LOGIN 
	// �޽����� ������ �α��� ������ ��û�Ѵ�.
	//----------------------------------------

	{
		if(g_bHanAuth)		
		{
#ifdef USE_HANAUTH
			// ������Ʈ�� ���
			SI32 siHanAuthRet = GetAuthString(m_szHanAuth_AuthString, SIZE_AUTHSTRING);
			if(siHanAuthRet != 0)		{		m_szHanAuth_GameString[0] = '\0';		}

//			WriteFileLog("ProcessLog.txt", __FILE__, __LINE__, "Send cltLogIn_HanAuthInfo;siAuthKey = %d", siAuthKey);

			cltLogIn_HanAuthInfo cllogin(siAuthKey, m_szHanAuth_AuthString, m_szHanAuth_UserID, uiGamemode);
			cltMsg clMsg(GAMEMSG_REQUEST_HANAUTH_LOGIN, sizeof(cltLogIn_HanAuthInfo), (BYTE*)&cllogin);

			SendMsgToServer((sPacketHeader*)&clMsg);
#endif // USE_HANAUTH
		}
		else if(g_bWebLoginService)
		{
#ifdef _TAIWAN // -- �븸 �α��� --
			cltLogIn_TaiwanInfo cllogin( siAuthKey, g_szWeb_id, g_szWeb_pw, uiGamemode );
			cltMsg clMsg(GAMEMSG_REQUEST_TAIWAN_LOGIN, sizeof(cltLogIn_TaiwanInfo), (BYTE*)&cllogin);

			SendMsgToServer((sPacketHeader*)&clMsg);
#endif
		}
		else
		{
			cltLogInInfo cllogin( siAuthKey, szID, szPassword, uiGamemode );
			cltMsg clMsg(GAMEMSG_REQUEST_LOGIN, sizeof(cltLogInInfo), (BYTE*)&cllogin);

			SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}

	return 1;
}

bool cltClient::Registeriovation()
{
	bool bRet = false;
	HRESULT hr;

	// register the ActiveX dll
	HMODULE hDLL = LoadLibrary( "StmOCX.dll" );
	if ( hDLL )
	{
		RegProto regFn = (RegProto) GetProcAddress( hDLL, "DllRegisterServer" );
		if ( regFn )
		{
			hr = regFn();
			if( SUCCEEDED(hr) )		bRet = true;
		}

		FreeLibrary( hDLL );
	}

	return bRet;
}