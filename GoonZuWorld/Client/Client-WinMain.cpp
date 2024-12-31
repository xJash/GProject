//---------------------------------
// 2003/10/2 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "Client.h"

#include "..\Common\Map\Map.h"
#include "..\resource.h"
#include "..\Server\Candidate\Candidate.h"
#include "Music\Music.h"
#include "../Client/DrawLogo/DrawLogo.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"
#include "../Client/Interface/LoginClient/LoginClient.h"
#include "../Client/StatusBar/ChatStatusBar/ChatStatusBar.h"
#include "../Client/NInterface/NLogin/NLogin.h"
#include "../Client/MiniHomeUpdates/PopupCheck.h"

#include "../common/Char/CharManager/CharManager.h"

extern bool bDrawSkipSwitch;
extern bool g_bHanAuth;
extern bool g_bUSA_Auth;
extern DWORD dwQuitTimer;

#ifdef USE_GAME_GUARD_CLIENT
	extern CNPGameLib * pNpgl;
#endif

// WInMain�ȿ����� Ŭ���̾�Ʈ ���. 
void cltClient::ClientWinMain()
{
	
	// �����찡 Ȱ��ȭ �Ǿ� ���������� ȿ������ ����. 
	//if(bActive == TRUE)
	{
		// ȿ������ �����Ѵ�. 
		PopEffect();

	}
	
	switch(GetGameStatus())
	{
		//---------------------------
		// Front Server���� ����. 
		//---------------------------
	case GS_INITCONNECTFRONTSERVER:	GsInitConnectFrontServer();		break;
		
	case GS_CONNECTFRONTSERVER:		GsConnectFrontServer();			break;

		//---------------------------
		// ���ɰ��� ȭ�� ǥ��
		//---------------------------
	case GS_SHOWGOVERNMENT:			GsShowGovernment();				break;
		
		//--------------------------
		// World List ���� 
		//--------------------------
	case GS_INITSELECTWORLDLIST:	GsInitSelectWorldList();		break;
		
	case GS_SELECTWORLDLIST:		GsSelectWorldList();			break;
		
		//---------------------------
		// Game Server ���� ����. 
		//---------------------------
	case GS_INITCONNECTGAMESERVER:	GsInitConnectGameServer();		break;
		
	case GS_CONNECTGAMESERVER:		GsConnectGameServer();			break;
		
		//--------------------------
		// Person List ����.
		//--------------------------
	case GS_INITCHARLIST:			GsInitCharList();				break;
		
	case GS_CHARLIST:				GsCharList();					break;
		
		//--------------------------
		// ���� 
		//-------------------------
	case GS_GAME:					GsGame();						break;

	case GS_GAMEDESTROY:			DestroyWindow( GetHwnd() );		return;
	}

//	// USA �������� ȣ�� ���
//	if( IsCountrySwitch(Switch_PopupCheck) )
//	{
//		// �ʱ� �ѹ� ȣ��
//#ifdef USE_HANAUTH
//
//		if( m_kUpdateTimer_PopupCheck.IsActivated() == false &&
//			GetGameStatus() >= GS_INITSELECTWORLDLIST )
//		{
//			// Ÿ�̸� �ѱ�
//			m_kUpdateTimer_PopupCheck.SetActive(true, ::GetTickCount());
//
//			TCHAR FullURL[100] = {'\0', };
//			if(m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
//			{
//				StringCchPrintf(FullURL, sizeof(FullURL),
//					"http://alpha-services.ijji.com/service/api/popupCheck?id=%s&gameid=U_GOONZU&type=0", m_szHanAuth_UserID);
//			}
//			else
//			{
//				StringCchPrintf(FullURL, sizeof(FullURL),
//					"http://services.ijji.com/service/api/popupCheck?id=%s&gameid=U_GOONZU&type=0", m_szHanAuth_UserID);
//			}
//
//			m_pPopupCheck->Request_PopupCheck(FullURL);
//		}
//#else
//		if( m_kUpdateTimer_PopupCheck.IsActivated() == false &&
//			_tcslen(pclClient->pclCM->CR[1]->pclCI->clBI.szAccountID) > 0 )
//		{
//			// Ÿ�̸� �ѱ�
//			m_kUpdateTimer_PopupCheck.SetActive(true, ::GetTickCount());
//
//			TCHAR FullURL[100] = {'\0', };
//			StringCchPrintf(FullURL, sizeof(FullURL),
//				"http://services.ijji.com/service/api/popupCheck?id=%s&gameid=U_GOONZU&type=0", pclClient->pclCM->CR[1]->pclCI->clBI.szAccountID);
//
//			// �����׽�Ʈ.
//			StringCchPrintf( FullURL, sizeof(FullURL),
//				"http://alpha-services.ijji.com/service/api/popupCheck?id=searer1&gameid=U_GOONZU&type=0");
//
//			m_pPopupCheck->Request_PopupCheck(FullURL);
//		}
//
//#endif // USE_HANRTA
//	}

	// ���ǥ�� �׸���
	if (IsWhereServiceArea(ConstServiceArea_Korea) && GetGameStatus() == GS_GAME && m_kTimer_ShowRank_Interval.IsTimed(GetTickCount()) == true)
	{
		DrawGovernMentRankMark(1);
	}

#ifdef USE_GAME_GUARD_CLIENT

	if(m_kTimer_Check_GameGuard_Interval.IsTimed(GetTickCount()) == true)
	{
		if( pNpgl->Check() != NPGAMEMON_SUCCESS ) dwQuitTimer = 1;
	}

#endif

#ifdef USE_HANAUTH

	// �����ð� �������� ������ ����� �� �ִ� �������� üũ�Ѵ�.
/*	if( GetGameStatus() >= GS_GAME &&
		kHanAuth_UpdateTimer_GameRunAuth.IsTimed(::GetTickCount(), true))
	{
		// �ѱ� NHN������ �����߿� ���̸� üũ�Ѵ�.
		if(IsWhereServiceArea(ConstServiceArea_Korea))
		{
			// ������Ʈ�� ���
			SI32 siHanAuthRet = GetAuthString(m_szHanAuth_AuthString, SIZE_AUTHSTRING);
			if(siHanAuthRet != 0)		{		m_szHanAuth_GameString[0] = '\0';		}

			cltHanAuth_GameRunAuth clRunAuth;
			MStrCpy(clRunAuth.authstring,	m_szHanAuth_AuthString,	2048 );
			MStrCpy(clRunAuth.userid,		m_szHanAuth_UserID,		MAX_PLAYER_NAME );

			cltMsg clMsg(GAMEMSG_REQUEST_HANAUTH_GAMERUNAUTH, sizeof(cltHanAuth_GameRunAuth), (BYTE*)&clRunAuth);

			SendMsgToServer((sPacketHeader*)&clMsg);
		}
	}
*/
#endif

	if ( GetGameStatus() >= GS_INITCONNECTFRONTSERVER && GetGameStatus() < GS_GAME )
	{
		if ( lpBackScreen && GP.LockSurface( lpBackScreen ) == TRUE )
		{
			GP.UnlockSurface( lpBackScreen );
		}
		else
		{
			return;
		}

		GP.ClearSurface( lpBackScreen );
		
/*
// ������ ���
		if( m_DrawLogo ) //��� ����
			m_DrawLogo->PlayMovie(TEXT("Movie/Logo.mpg"));
// �����ְ� ������
		if ( m_DrawLogo )
		{
			delete m_DrawLogo;
			m_DrawLogo = NULL;
		}
*/
		if ( m_pLoadingImg )
		{
			m_pLoadingImg->Draw( lpBackScreen, GetScreenRX(), GetScreenRY() );
		}

		GameDrawUpdateScreen();
	}

}

void cltClient::GsGame()
{

#ifndef JEWAN_FRAME_SKIP

	if(bDrawSkipSwitch == false)
	{
		GameDraw();	
	}

#endif

	GameProcess();
}


void cltClient::GsInitConnectFrontServer()
{
	//DrawGovernMentRankMark(0);

	// ����Ʈ ������ �����ϵ��� �����. 
	if(InitConnectToFrontServer() == true)
	{
		SetGameStatus(GS_CONNECTFRONTSERVER);
	}
	else
	{
		SetGameStatus( GS_GAMEDESTROY );
		//DestroyWindow(GetHwnd());
	}
}

void cltClient::GsConnectFrontServer()
{
	// Ŭ���̾�Ʈ �� ��� ������ ������ �õ��Ѵ�. 
	SI32 returnval = ConnectToFrontServer();

	if(returnval == 1)
	{
		SetGameStatus(GS_SHOWGOVERNMENT);

		if ( IsWhereServiceArea(ConstServiceArea_Korea) )
		{
			m_kTimer_WaitGameLogin.SetActive( true, GetTickCount() );
		}
		else
		{
			m_kTimer_WaitGameLogin.SetActive( true, 1 );
		}
	}
	else if(returnval == -1)
	{
		SetGameStatus( GS_GAMEDESTROY );
		//DestroyWindow(GetHwnd());
	}
}

void cltClient::GsInitConnectGameServer()
{

	// ����  ������ �����ϵ��� �����. 
	if(InitConnectToGameServer() == true)
	{
		SetGameStatus(GS_CONNECTGAMESERVER);
	}
	else
	{
	}


}

void cltClient::GsConnectGameServer()
{
	// Ŭ���̾�Ʈ �� ��� ������ ������ �õ��Ѵ�. 
	SI32 returnval = ConnectToGameServer();

	if(returnval == 1)
	{
		SetGameStatus(GS_INITCHARLIST);

	}
	else if(returnval == -1)
	{
		DestroyWindow(GetHwnd());

		// �Ѱ��� ���뺸��
		//HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_SELECTSERVER);
	}
}


void cltClient::GsInitCharList()
{
	// ĳ���� ����Ʈ�� �غ�Ǿ� �ִٸ�, 
	if(IsReadyCharList() == TRUE)
	{
		SetGameStatus(GS_CHARLIST);
		clSelectedWorldInfo.baseinfo.worldId;
		
		// �Ѱ��� ���뺸��
		if(siServiceArea == ConstServiceArea_NHNChina)
		{
			HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(clSelectedWorldInfo.baseinfo.siServerID ,m_szPorteAuth_UserID, HANREPORT_CLIENT_SELECTCHAR);
		}
		else
		{
			HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_SELECTCHAR);
		}
	}
	else
	{
	}
}


void cltClient::GsCharList()
{
	if(SelectChar() == FALSE)
	{	
		SetGameStatus(GS_GAME);

		// �Ѱ��� ���뺸��
		if(siServiceArea == ConstServiceArea_NHNChina)
		{
			HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(clSelectedWorldInfo.baseinfo.siServerID ,m_szPorteAuth_UserID, HANREPORT_CLIENT_LOGINTOGAMESERVER);
		}
		else
		{
			HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_LOGINTOGAMESERVER);
		}


		//cyj Toolbar, Statusbar ���� ���Ŀ� ����
		if ( g_SoundOnOffDlg.m_bFullScreenMode )
		{
			/*if ( m_pDialog[ NCHAT_DLG ] )
			{
				if ( ! m_pDialog[ NCHAT_DLG ]->IsShow() )
				{
					m_pDialog[ NCHAT_DLG ]->Show( true );
				}
			}*/
			if ( m_pDialog[ STATUSBAR_DLG ] )
			{
				if ( ! m_pDialog[ STATUSBAR_DLG ]->IsShow() )
				{
					m_pDialog[ STATUSBAR_DLG ]->Show( true );
				}
			}
			if ( m_pDialog[ NCHARMENUBAR_DLG ] )
			{
				if ( ! m_pDialog[ NCHARMENUBAR_DLG ]->IsShow() )
				{
					m_pDialog[ NCHARMENUBAR_DLG]->Show( true );
				}
			}				
			if ( m_pDialog[ NSYSMENUBAR_DLG ] )
			{
				if ( ! m_pDialog[ NSYSMENUBAR_DLG ]->IsShow() )
				{
					m_pDialog[ NSYSMENUBAR_DLG ]->Show( true );
				}
			}
			if ( m_pDialog[ NCHATBAR_DLG ] )
			{
				if ( ! m_pDialog[ NCHATBAR_DLG ]->IsShow() )
				{
					m_pDialog[ NCHATBAR_DLG ]->Show( true );
				}
			}

			if ( m_pDialog[ NMINIMAP_DLG ] )
			{
				if( ! m_pDialog[ NMINIMAP_DLG ]->IsShow() )
				{
					m_pDialog[ NMINIMAP_DLG ]->Show( true );
				}
			}

			if ( m_pDialog[ NPREMIUMSTATUS_DLG ] )
			{
				if( ! m_pDialog[ NPREMIUMSTATUS_DLG ]->IsShow() )
				{
					m_pDialog[ NPREMIUMSTATUS_DLG ]->Show( true );
				}
			}

			if ( m_pDialog[ NBUFFSTATUS_DLG ] )//�����߰�.[2007.07.12 ����]
			{
				if( ! m_pDialog[ NBUFFSTATUS_DLG ]->IsShow() )
				{
					m_pDialog[ NBUFFSTATUS_DLG ]->Show( true );
				}
			}
			
			if ( m_pDialog[ NDORMANCYPOINT_DLG ] )//�޸� ����Ʈ ���̾�α� [2009.09.15 ����]
			{
				if( ! m_pDialog[ NDORMANCYPOINT_DLG ]->IsShow() )
				{
					m_pDialog[ NDORMANCYPOINT_DLG ]->Show( true );
				}
			}
		}

	}
}

void cltClient::GsQuit()
{
	DestroyWindow(GetHwnd());
}


void cltClient::GsInitSelectWorldList()
{

	if(CreateSelectWorldListDlg(true) == true)
	{
		// �Ѱ��� ���뺸��
		if(siServiceArea == ConstServiceArea_NHNChina)
		{
			HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(clSelectedWorldInfo.baseinfo.siServerID ,m_szPorteAuth_UserID, HANREPORT_CLIENT_SELECTSERVER);
		}
		else
		{
			HanAuth_Lib_HanReportSendPosLog_Client(m_szHanAuth_UserID, HANREPORT_CLIENT_SELECTSERVER);
		}


		SetGameStatus(GS_SELECTWORLDLIST);
	}
}

void cltClient::GsSelectWorldList()
{

	if(SelectWorldList() == true)
	{
		SetGameStatus(GS_INITCONNECTGAMESERVER);
	}
}

void cltClient::GsShowGovernment()
{
	if ( m_kTimer_WaitGameLogin.IsTimed(GetTickCount()) )
	{
		SetGameStatus( GS_INITSELECTWORLDLIST );
	}
}
