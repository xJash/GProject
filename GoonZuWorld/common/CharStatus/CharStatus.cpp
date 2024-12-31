//---------------------------------
// 2003/5/17 ���°�
//--------------------------------
#include "../Client/Client.h"
#include "CharStatus.h"
#include "../Father/Father.h"

#include "../resource.h"
#include "../Server/Rank/Rank.h"
#include "../../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../../Client/NInterface/NSelecWarpTicket/NSelectNoLimitWarpTicket.h"

#include "Msg/MsgType-Horse.h"
#include "Msg/MsgType-Summon.h"
#include "../JWLib/IsCorrectID/IsCorrectID.h"
#include "../../lib/WebHTML/WebHTML.h"
#include "../../Client/Music/Music.h"
#include "../Ship/Ship.h"
#include "NInterface/NHintDlg/NHintDlg.h"
//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "HintDlg/HintDlg.h"
#include "Char/CharManager/CharManager.h"

//-----------------------------
// CommonLogic
//-----------------------------
#include "../CommonLogic/msgType-Person.h"
#include "Msg/MsgType-ItemMall.h"

extern cltCommonLogic* pclClient;

cltCharStatus::cltCharStatus(cltCharManager* pclcm)
{
	SI32 i;

	m_hDlg	= NULL;
	CurrentStatusPage = 0;
	m_hHorsePortraitBitmap  = NULL;
	m_hSummonPortraitBitmap = NULL;
	
	for(i = 0; i< MAX_CHARSTATUS_PAGE_NUMBER;i++)
	{
		TabDlg[i]	= NULL;
	}

	DlgRectInitSwitch = FALSE;

	CharUnique = 0;
	bBonusButtonEnableSwitch	= false;
	bBonusButton2EnableSwitch	= false;
	BonusSummonButtonEnableSwitch = FALSE;
	BonusHorseButtonEnableSwitch = FALSE;

	pclCM	= pclcm;
	//pclCharStatusExplain	= new cltCharStatusExplain;
	//pclHorseBreedExplain	= new cltHorseBreedExplain;
	//pclSummonBreedExplain	= new cltSummonBreedExplain;
	pclHorseTypeChange		= new cltHorseTypeChange;
	pclCharNameChange		= new cltCharNameChange;
	pclCharKindChange		= new cltCharKindChange;

	m_hStatusHintHitBitmap = NULL;
	m_hHorseHintHitBitmap  = NULL;
	m_hSummonHintHitBitmap = NULL;
	m_hSummonReviveBitmap  = NULL;	 
	m_hStatusInitHitBitmap = NULL;
	m_hHorseAddStatusHitBitmap = NULL ;
	m_hHorseInitHitBitmap  = NULL;
	m_hHorseTypeHitBitmap  = NULL;
	m_hStatusChangeNameBitmap = NULL ;
	m_hStatusChangeKindBitmap = NULL ;
	m_hSummonStatusInitBitmap = NULL ;
	m_hNoLimitWarpTicketBitmap = NULL ;

	m_hDlgBrush = NULL;
	m_hEditBrush= NULL;
	m_hStaticBrush= NULL;
	
	m_hDlgBrush    = CreateSolidBrush( COLOR_DIALOG_DLG_BLUE );
	m_hEditBrush   = CreateSolidBrush( COLOR_DIALOG_WHITE);
	m_hStaticBrush = CreateSolidBrush( COLOR_DIALOG_STATIC_BLUE);
	
	memset( strHorseName, 0, MAX_HORSE_NAME );
	memset( strSummonName, 0, MAX_SUMMON_NAME );

	m_LastTakeInOutTime = 0;
	m_bChangedInitSummonStatus = TRUE;
	m_siLastSummonComboList    = 0;
	m_siPortraitSummonKind	   = 0;	
}

cltCharStatus::~cltCharStatus()
{

/*	if(pclCharStatusExplain)	
	{
		delete pclCharStatusExplain;
		pclCharStatusExplain = NULL;
	}*/

	if(pclCharKindChange)
	{
		delete pclCharKindChange;
		pclCharKindChange = NULL ;
	}
	if(pclCharNameChange)
	{
		delete pclCharNameChange;
		pclCharNameChange = NULL ;
	}
	if(pclHorseTypeChange)
	{
		delete pclHorseTypeChange;
		pclHorseTypeChange = NULL ;
	}
/*	if(pclHorseBreedExplain)	
	{
		delete pclHorseBreedExplain;
		pclHorseBreedExplain = NULL;
	}*/
/*	if(pclSummonBreedExplain)
	{
		delete pclSummonBreedExplain;
		pclSummonBreedExplain = NULL;
	}*/

	if ( m_hStaticBrush )
	{
		DeleteObject( m_hStaticBrush );
		m_hStaticBrush = NULL;
	}
	if ( m_hDlgBrush )
	{
		DeleteObject( m_hDlgBrush );
		m_hDlgBrush = NULL;
	}
	if(m_hEditBrush)
	{
		DeleteObject( m_hEditBrush );
		m_hEditBrush = NULL;
	}
}


BOOL CALLBACK cltCharStatus::CharStatusDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 i;
	HWND hwnd ;

	cltClient* pclclient = (cltClient*)pclClient;

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{

			SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
			if(id == 0)
			{
				DestroyWindow(m_hDlg);
				return TRUE;
			}

			hwnd = GetDlgItem(hDlg, IDC_TAB_STATUS);
			TC_ITEM item;
			// to use an image set this to TCIF_IMAGE  
			item.mask= TCIF_TEXT; 
			// index into tabs image list, set to -1 when not in use
			item.iImage		= -1;
			// ����� 
			item.pszText	= (char*)pclCM->CR[id]->GetName();
			TabCtrl_InsertItem(hwnd,0,&item);

			// �� 
			char* pText = GetTxtFromMgr(372);
			item.pszText	= pText;
			TabCtrl_InsertItem(hwnd, 1, &item);

			// ��ȯ��
			pText = GetTxtFromMgr(449);
			item.pszText	=	pText;
			TabCtrl_InsertItem(hwnd, 2, &item);

			// �ڻ�  
			pText = GetTxtFromMgr(600);
			item.pszText	=	pText;
			TabCtrl_InsertItem(hwnd, 3, &item);

			// ����Ʈ  
			pText = GetTxtFromMgr(601);
			item.pszText	=	pText;
			TabCtrl_InsertItem(hwnd, 4, &item);


			CurrentStatusPage	= 0;


			switch(CurrentStatusPage)
			{
			case 0:
				CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_PERSON, CharStatusBattleStaticProc);
				break;
			case 1:
				CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_HORSE, CharStatusHorseStaticProc);
				break;
			case 2:
				CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_SUMMON, CharStatusSummonStaticProc);
				break;
			case 3:
				CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_ESSET, CharStatusEssetStaticProc);
				break;
			case 4:
				CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_QUEST, CharStatusQuestStaticProc);
				break;
			}
		}
		return TRUE;
	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor( hdc, COLOR_DIALOG_BLACK);
			SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE );
			
			return (BOOL)m_hDlgBrush;
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR FAR *tem=(NMHDR FAR *)lParam;

			if (tem->code== TCN_SELCHANGE)
			{
				hwnd = GetDlgItem(hDlg, IDC_TAB_STATUS);

				// ���� ȭ�鿡 ���̴� �������� �����. 
				if(TabDlg[CurrentStatusPage])
				{
					ShowWindow(TabDlg[CurrentStatusPage], SW_HIDE) ;
				}

				CurrentStatusPage = TabCtrl_GetCurSel(tem->hwndFrom);

				switch(CurrentStatusPage)
				{
				case 0:
					CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_PERSON, CharStatusBattleStaticProc);
					break;
				case 1:
					CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_HORSE, CharStatusHorseStaticProc);
					break;
				case 2:
					CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_SUMMON, CharStatusSummonStaticProc);
					break;
				case 3:
					{
						CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_ESSET, CharStatusEssetStaticProc);
						// ��� ������ ��û��
						cltMsg clMsg(GAMEMSG_REQUEST_MYGUILDINFO, 0, NULL );
						pclclient->SendMsgToServer((char*)&clMsg );
					}
					break;
				case 4:
					CreateTabDlg(hDlg, CurrentStatusPage, IDD_DIALOG_STATUS_QUEST, CharStatusQuestStaticProc);
					break;
				}
			}
		}
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_DESTROY:

		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hHorseAddStatusHitBitmap)
		{
			DeleteObject(m_hHorseAddStatusHitBitmap);
			m_hHorseAddStatusHitBitmap = NULL ;
		}
		if(m_hHorsePortraitBitmap)
		{
			DeleteObject(m_hHorsePortraitBitmap);
			m_hHorsePortraitBitmap= NULL;
		}
		if(m_hSummonPortraitBitmap)
		{
			DeleteObject(m_hSummonPortraitBitmap);
			m_hSummonPortraitBitmap= NULL;
		}
		if(m_hStatusHintHitBitmap)
		{
			DeleteObject(m_hStatusHintHitBitmap);
			m_hStatusHintHitBitmap = NULL;
		}
		if(m_hHorseHintHitBitmap)
		{
			DeleteObject(m_hHorseHintHitBitmap);
			m_hHorseHintHitBitmap = NULL;
		}
		if(m_hSummonHintHitBitmap)
		{
			DeleteObject(m_hSummonHintHitBitmap);
			m_hSummonHintHitBitmap = NULL;
		}
		if(m_hSummonReviveBitmap)
		{
			DeleteObject(m_hSummonReviveBitmap);
			m_hSummonReviveBitmap = NULL;
		}
		if(m_hStatusInitHitBitmap)
		{
			DeleteObject(m_hStatusInitHitBitmap);
			m_hStatusInitHitBitmap = NULL;
		}
		if(m_hHorseInitHitBitmap)
		{
			DeleteObject(m_hHorseInitHitBitmap);
			m_hHorseInitHitBitmap = NULL;
		}
		if(m_hHorseTypeHitBitmap)
		{
			DeleteObject(m_hHorseTypeHitBitmap);
			m_hHorseTypeHitBitmap = NULL ;
		}
		if(m_hStatusChangeNameBitmap)
		{
			DeleteObject(m_hStatusChangeNameBitmap);
			m_hStatusChangeNameBitmap = NULL ;
		}
		if(m_hStatusChangeKindBitmap)
		{
			DeleteObject(m_hStatusChangeKindBitmap);
			m_hStatusChangeKindBitmap = NULL ;
		}
		if(m_hSummonStatusInitBitmap)
		{
			DeleteObject(m_hSummonStatusInitBitmap);
			m_hSummonStatusInitBitmap = NULL;
		}
		if(m_hNoLimitWarpTicketBitmap)
		{
			DeleteObject(m_hNoLimitWarpTicketBitmap);
			m_hNoLimitWarpTicketBitmap = NULL;
		}

		for(i = 0;i < MAX_CHARSTATUS_PAGE_NUMBER;i++)
		{
			if(TabDlg[i])
			{
				DestroyWindow( TabDlg[i] );
				TabDlg[i] = NULL;
			}
		}

		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(m_hDlg, &DlgRect);

		DlgRectInitSwitch = TRUE;

		m_hDlg = NULL;
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			DestroyWindow(m_hDlg);
			return TRUE;

		case IDC_BUTTON_WARP:	// 10������ ���� �����ֱ�
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if(id == 0)
					return TRUE;

				if(pclCM->CR[id]->pclCI->clIP.GetLevel() > 10)
				{
					char* pTitle = GetTxtFromMgr(1413);
					char* pText  = GetTxtFromMgr(5602);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					return TRUE;
				}
				
				// ���� ����
				if(pclCM->CR[id]->pclCI->clBI.GetKind() == 1 || pclCM->CR[id]->pclCI->clBI.GetKind() == 2)
				{
					if( pclCM->CR[id]->GetMapIndex() == 158)
					{
						char* pTitle = GetTxtFromMgr(1413);
						char* pText  = GetTxtFromMgr(5603);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return TRUE;
					}
					//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
					cltGameMsgRequest_HuntMapWarp pclInfo(158,0,false);
					cltMsg clMsg( GAMEMSG_REQUEST_WARJOIN, sizeof( pclInfo ), (char*)&pclInfo );
					pclClient->SendMsgToServer((char*)&clMsg);
				}
				else if(pclCM->CR[id]->pclCI->clBI.GetKind() == 3)
				{
					if( pclCM->CR[id]->GetMapIndex() == 176)
					{
						char* pTitle = GetTxtFromMgr(1413);
						char* pText  = GetTxtFromMgr(5603);

							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							return TRUE;
					}
					//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
					cltGameMsgRequest_HuntMapWarp pclInfo(176,0,false);
					cltMsg clMsg( GAMEMSG_REQUEST_WARJOIN, sizeof( pclInfo ), (char*)&pclInfo );
					pclClient->SendMsgToServer((char*)&clMsg);
				}
			}
			return TRUE;

		case IDCANCEL:
			DestroyWindow(m_hDlg);
			return TRUE;
			
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK cltCharStatus::CharStatusBattleStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;
	return pclclient->pclCharStatus->CharStatusBattleProc(hDlg, iMsg, wParam, lParam);
}


BOOL CALLBACK cltCharStatus::CharStatusBattleProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient *pclclient = (cltClient*)pclClient;

	//SI32 i;
	HWND hwnd = NULL;

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 1000, NULL);
			
			bBonusButtonEnableSwitch		= false;
			bBonusButton2EnableSwitch		= false;

			//////JAYCEE
			m_hStatusHintHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "StatusHint/StatusExplainHint.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			
			if ( m_hStatusHintHitBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_STATUS_EXPLAIN, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hStatusHintHitBitmap);
			}

			m_hStatusInitHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/StatusInit.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

			if ( m_hStatusInitHitBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_STATUS_INIT, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hStatusInitHitBitmap);
			}

			m_hStatusChangeNameBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/changename.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

			if ( m_hStatusChangeNameBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_STATUS_CHANGE_NAME, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hStatusChangeNameBitmap);
			}

			m_hStatusChangeKindBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/changecharkind.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

			if ( m_hStatusChangeKindBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_STATUS_CHANGE_CHARKIND, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hStatusChangeKindBitmap);
			}

			m_hNoLimitWarpTicketBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "interface/HitButton/NoLimitWarp.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

			if ( m_hNoLimitWarpTicketBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_STATUS_NOLIMITWARP, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hNoLimitWarpTicketBitmap);
			}

			//------------------------------
			// ĳ������ �ʻ�ȭ�� �����ش�. 
			//------------------------------
			//---------------------------------
			// HTML �� �ʱ�ȭ�Ѵ�.
			//---------------------------------
			HWND hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
			if ( hwnd )
			{
				EmbedBrowserObject(hwnd);
			}

			SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
/*			if(id)
			{
				cltClient* pclclient = (cltClient *)pclClient;
				char GomziURL[MAX_PATH] = "" ;

				pclClient->GetCZProfileUrl( GomziURL, pclclient->szID );

				// PROFILE
				hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
				DisplayHTMLPage(hwnd, GomziURL);
			}*/
			UpdateCharStatusInfo(hDlg);
		}
		return TRUE;

	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			SetTextColor( hdc, COLOR_DIALOG_BLACK);
			SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE );
								
			return (BOOL)m_hDlgBrush;
		}
		break;
		
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_STR ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_DEX ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_INT ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_VIT ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_HND ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_BATTLEBONUS ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_TOTALSPEED ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_TOTALDAMAGE ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_ARMOURCLASS ) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_EDIT_STATUS_HEALTH_EXPLAIN) == (HWND)lParam
				)
			{
				HDC hdc = (HDC)wParam;
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);				
				SetTextColor( hdc, COLOR_DIALOG_BLACK );

				return (BOOL)m_hStaticBrush;
			}
			else
			{
				HDC hdc = (HDC)wParam;
				SetBkMode(hdc,TRANSPARENT);
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				return (BOOL)m_hDlgBrush;
			}
			
		}
		break;

	case WM_SIZE:
		//============================
		// HTML Resize �� �Ѵ�.
		//==================================
		hwnd = GetDlgItem(hDlg, IDC_STATIC_CHARSTATUS_PORT);
		if( hwnd )
		{
			ResizeBrowser(hwnd, LOWORD(lParam), HIWORD(lParam));		
		}
		return TRUE;

	case WM_TIMER:
		UpdateCharStatusInfo(hDlg);
		return TRUE;

	case WM_DESTROY:
		//---------------------------------
		// HTML �� �����Ѵ�.
		//---------------------------------
		//==================================
		hwnd = GetDlgItem( hDlg, IDC_STATIC_CHARSTATUS_PORT );
		if( hwnd )
		{
			UnEmbedBrowserObject(hwnd);
		}			
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_COMMAND:
		cltClient *pclclient = (cltClient *)pclClient;
		switch(wParam)
		{
		case IDC_BUTTON_GREETING:
			{
				if( pclclient->m_pDialog[ CLTNCHARGREETINGCHANGE_DLG ] == NULL )
					pclclient->CreateInterface( CLTNCHARGREETINGCHANGE_DLG);
			}
			return TRUE;
		case IDC_BUTTON_STATUS_NOLIMITWARP:
			{
				pclclient->CreateInterface(NSELECTNOLIMITWARPTICKET_DLG);
			}
			return TRUE;
		case IDC_BUTTON_STR:SendUseBonusMessageToServer(0, 1);	return TRUE;
		case IDC_BUTTON_DEX:SendUseBonusMessageToServer(1, 1);	return TRUE;
		case IDC_BUTTON_INT:SendUseBonusMessageToServer(2, 1);	return TRUE;
		case IDC_BUTTON_VIT:SendUseBonusMessageToServer(3, 1);	return TRUE;
		case IDC_BUTTON_HND:
			{
				SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
				if(id)
				{
					// �����ִ� ���� * 2 ������ ����Ѵ�.
					if(pclCM->CR[id]->pclCI->clIP.GetHnd() >= pclCM->CR[id]->pclCI->clIP.GetLevel()*2)
					{
						char* pTitle = GetTxtFromMgr(602);
						char* pText = GetTxtFromMgr(603);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						return TRUE;
					}
					
					SendUseBonusMessageToServer(4, 1);	
				}
			}
			return TRUE;
		case IDC_BUTTON_STR2:
		case IDC_BUTTON_DEX2:
		case IDC_BUTTON_MAG2:
		case IDC_BUTTON_VIT2:
		case IDC_BUTTON_HND2:
			{
				char buffer[256] = "" ;
				SI32 itemunique = 14095 ;  // ���ºκ��ʱ�ȭ�̿��
				if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(605);
					char* pText = GetTxtFromMgr(604);

					sprintf(buffer,
						pText);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);

					return TRUE;
				}

				char* pTitle = GetTxtFromMgr(607);
				char* pText = GetTxtFromMgr(606);

				strcpy(buffer, pText);
				if (  MessageBox(NULL, buffer,pTitle,
					MB_ICONQUESTION | MB_YESNO) == IDNO )
				{
					return TRUE;
				}
				
				SendUseBonusMessageToServer(wParam, -1);	
			}
			return TRUE;
		case IDC_BUTTON_STATUS_EXPLAIN:
			{
				//pclCharStatusExplain->CreateDlg(pclClient->GetInstance(), pclClient->GetHwnd());
				//pclclient->m_pHintDlg->Show("charstatus");
				
				if((pclclient->m_pDialog[ NHINT_DLG ])==NULL)
				{
					pclclient->CreateInterface( NHINT_DLG );
				}
					((NHintDlgExplain*)pclclient->m_pDialog[ NHINT_DLG])->Show("charstatus");
			}
			return TRUE;
		case IDC_BUTTON_STATUS_INIT:
			{
				char buffer[256] = "" ;

				SI32 itemunique = 14090 ;  // �����ʱ�ȭ�̿��
				if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(605);
					char* pText = GetTxtFromMgr(608);

					sprintf(buffer,pText);
					
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
					return TRUE;
				}

				char* pTitle = GetTxtFromMgr(605);
				char* pText = GetTxtFromMgr(609);

				strcpy(buffer,pText);
				if (  MessageBox(NULL, buffer,pTitle,
					MB_ICONQUESTION | MB_YESNO) == IDNO )
				{
					return TRUE;
				}

				cltMsg clMsg(GAMEMSG_REQUEST_INITSTATUS,0);
				pclclient->SendMsgToServer((char*)&clMsg);
			}
			return TRUE;
		case IDC_BUTTON_STATUS_CHANGE_NAME:
			{
				if ( !pclCharNameChange->CreateDlg(pclClient->GetInstance(), pclClient->GetHwnd()) )
					pclCharNameChange->Close();
			}
			return TRUE;
		case IDC_BUTTON_STATUS_CHANGE_CHARKIND:
			{
				if ( pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() <= 0 ||
					pclclient->pclCM->CR[1]->pclCI->clBI.GetKind() >= KIND_SYSTEM )
					return TRUE ;

				if ( !pclCharKindChange->CreateDlg(pclClient->GetInstance(),pclClient->GetHwnd()) )
					pclCharKindChange->Close();
			}
			return TRUE;
		case IDOK:
			return TRUE;
		case IDCANCEL:
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK cltCharStatus::CharStatusSummonStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;

	return pclclient->pclCharStatus->CharStatusSummonProc(hDlg, iMsg, wParam, lParam);
}

// ��ȯ�� 
BOOL CALLBACK cltCharStatus::CharStatusSummonProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 1000, NULL);
			BonusSummonButtonEnableSwitch = FALSE;
			// ���ڼ��� �����Ѵ�.
			SendDlgItemMessage( hDlg, IDC_EDIT_STATUS_SUMMONNAME, EM_LIMITTEXT, MAX_SUMMON_NAME-1, 0 );
		
			// SummonStatus �������� ó�� �ʱ�ȭ �����Ѵ�.
			m_bChangedInitSummonStatus = TRUE;
			m_siLastSummonComboList = 0;

			InitSummonStatusInfo(hDlg);
			UpdateSummonStatusInfo(hDlg);
			UpdateSummonPortrait(hDlg);

			//====================================
			// HINT
			//====================================
			m_hSummonHintHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "StatusHint\\summonshint.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			
			if ( m_hSummonHintHitBitmap  != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_SUMMON_EXPLAIN, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hSummonHintHitBitmap );
			}		

			//====================================
			// BUTTOM
			//====================================
			m_hSummonReviveBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "StatusHint\\SummonRevive.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			
			if ( m_hSummonReviveBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_SUMMON_REVIVE, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hSummonReviveBitmap );
			}

			//====================================
			// SummonStatusInit
			//====================================
			m_hSummonStatusInitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), "StatusHint\\SummonStatusInit.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

			if ( m_hSummonStatusInitBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_BUTTON_SUMMON_STATUSINIT, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hSummonStatusInitBitmap );
			}

		}

		return TRUE;
		
	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			SetTextColor( hdc, COLOR_DIALOG_BLACK);
			SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE );
								
			return (BOOL)m_hDlgBrush;
		}
		break;
	case WM_CTLCOLOREDIT:
		{
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ) == (HWND)lParam)
			{
				HDC hdc = (HDC)wParam;
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);				
				SetTextColor( hdc, COLOR_DIALOG_BLACK );

				return (BOOL)m_hStaticBrush;
			}
			else
			{
				HDC hdc = (HDC)wParam;
				SetBkMode(hdc,TRANSPARENT);
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				return (BOOL)m_hDlgBrush;
			}
		}
		break;
	case WM_TIMER:
		InitSummonStatusInfo(hDlg);
		UpdateSummonStatusInfo(hDlg);
		UpdateSummonPortrait(hDlg);
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);
		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hSummonPortraitBitmap)
		{
			DeleteObject(m_hSummonPortraitBitmap);
			m_hSummonPortraitBitmap = NULL;
		}
		m_siPortraitSummonKind	   = 0;	
		m_siLastSummonComboList	   = 0;

		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_CHECK_SUMMON_AUTOHEAL:
			{
				HWND hcheck = GetDlgItem( hDlg, IDC_CHECK_SUMMON_AUTOHEAL);
				bool bautoheal  = false ;

				if(SendMessage(hcheck , BM_GETCHECK, 0, 0 ) == BST_UNCHECKED )
				{
					bautoheal = false;
				}
				else
				{
					bautoheal = true;
				}

				SI16 selectautoheal = pclclient->pclCM->CR[1]->pclCI->clSummonInfo.siSelectAutoHeal ;
				SendSummonAutoHealMessageToServer(hDlg,selectautoheal,bautoheal) ;
				InvalidateRect(hDlg, NULL, TRUE);
			}
			break;
		case IDC_RADIO_SUMMON_AUTOHEAL30:
			{
				SendSummonAutoHealMessageToServer(hDlg,0,true) ;
				InvalidateRect(hDlg, NULL, TRUE);
			}
			break;
		case IDC_RADIO_SUMMON_AUTOHEAL50:
			{
				SendSummonAutoHealMessageToServer(hDlg,1,true) ;
				InvalidateRect(hDlg, NULL, TRUE);
			}
			break;
		case IDC_RADIO_SUMMON_AUTOHEAL70:
			{
				SendSummonAutoHealMessageToServer(hDlg,2,true) ;
				InvalidateRect(hDlg, NULL, TRUE);
			}
			break;
		case IDC_BUTTON_STR_INIT:
		case IDC_BUTTON_DEX_INIT:
		case IDC_BUTTON_INT_INIT:
		case IDC_BUTTON_VIT_INIT:
			{
				char buffer[256] = "" ;
				SI32 itemunique = 14095 ;  // ���ºκ��ʱ�ȭ�̿��
				if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(2835);
					char* pText = GetTxtFromMgr(604);

					sprintf(buffer, pText);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, buffer);

					return TRUE;
				}

				char* pTitle = GetTxtFromMgr(2835);
				char* pText = GetTxtFromMgr(2836);

				strcpy(buffer, pText);
				if (  MessageBox(NULL, buffer,pTitle,
					MB_ICONQUESTION | MB_YESNO) == IDNO )
				{
					return TRUE;
				}

				SendUseSummonBonusMessageToServer(hDlg, wParam,true);
			}
			break;
		case IDC_BUTTON_SUMMON_STATUSINIT:
			{
				SendSummonStatusInitMessageToServer(hDlg);
			}
			break;
		case IDC_BUTTON_STR:SendUseSummonBonusMessageToServer(hDlg, 0);	return TRUE;
		case IDC_BUTTON_DEX:SendUseSummonBonusMessageToServer(hDlg, 1);	return TRUE;
		case IDC_BUTTON_INT:SendUseSummonBonusMessageToServer(hDlg, 2);	return TRUE;
		case IDC_BUTTON_VIT:SendUseSummonBonusMessageToServer(hDlg, 3);	return TRUE;
		case IDC_RADIO_SUMMON_ACTIVE:
			{
				SendSummonAttackTypeMessageToServer(hDlg, SUMMON_ATTACKTYPE_ACTIVE);
			}
			break;
		case IDC_RADIO_SUMMON_AVOID:
			{
				SendSummonAttackTypeMessageToServer(hDlg, SUMMON_ATTACKTYPE_AVOID);
			}
			break;
		case IDC_BUTTON_STATUS_CHANGENAME:
			{
	
				SendSummonChangeNameMessageToServer(hDlg);
			}
			break;

		case IDC_BUTTON_SUMMON_TAKEINOUT:		// �ϴ� ��Ȱ��Ű�µ� ����Ѵ�.
			{
				SendSummonTakeInOutMessageToServer(hDlg);
		
			}
			break;
		case IDC_BUTTON_SUMMON_FREE:
			{
				SendSummonFreeMessageToServer(hDlg);
			}
			break;
		case IDC_BUTTON_SUMMON_REVIVE:
			{
				SendSummonReviveMessageToServer(hDlg);
			}
			break;
		case IDC_BUTTON_SUMMON_EXPLAIN:
			{
				//pclclient->m_pHintDlg->Show("summonbreed");
				if((pclclient->m_pDialog[ NHINT_DLG ])==NULL)
				{
					pclclient->CreateInterface( NHINT_DLG );
				}
					((NHintDlgExplain*)pclclient->m_pDialog[ NHINT_DLG])->Show("summonbreed");
			}
			return TRUE;
		case IDC_COMBO_SUMMON_LIST:
			{
				switch(HIWORD(wParam))
				{
				case CBN_SELCHANGE:
					{
						m_siLastSummonComboList = SendDlgItemMessage( hDlg, IDC_COMBO_SUMMON_LIST, CB_GETCURSEL, 0, 0 );

						UpdateSummonStatusInfo(hDlg);
						UpdateSummonPortrait(hDlg);

						//=======================================================
						// ��ȯ�� �̸� �� ���� 
						//=======================================================
						char SummonName[256]="";
						SI32 SummonIndex = 0;
						if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex))
						{
							SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME ), SummonName );
						}
						//=======================================================

					}
					break;
				}
			}
			break;
		case IDOK:
			return TRUE;
		case IDCANCEL:
			return TRUE;
			
		}
		return TRUE;
	}
	return FALSE;

}


BOOL CALLBACK cltCharStatus::CharStatusEssetStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;

	return pclclient->pclCharStatus->CharStatusEssetProc(hDlg, iMsg, wParam, lParam);
}


BOOL CALLBACK cltCharStatus::CharStatusEssetProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 i;
	char buffer[256];
	char string[128];
	static cltStockAccount clOldStockInfo;
	static cltGuildStockAccount clOldGuildStockInfo;	// ��� �ֽ� ����
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetTimer(hDlg, 1, 1000, NULL);

		clOldStockInfo.Init();
		clOldGuildStockInfo.Init();

		return TRUE;

	case WM_CTLCOLORDLG:
		{
			HDC hdc = (HDC)wParam;
			SetTextColor( hdc, COLOR_DIALOG_BLACK);
			SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE );
								
			return (BOOL)m_hDlgBrush;
		}
		break;

	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_WEALTHRANK ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_TOTALWEALTH ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_STATUS_BANKMONEY ) == (HWND)lParam || 
				GetDlgItem( hDlg, IDC_EDIT_STATUS_BANKVILLAGE ) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_LIST_STATUS_STOCK) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_LIST_STATUS_HOUSE) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_LIST_STATUS_SHIP) == (HWND)lParam  ||

				GetDlgItem( hDlg, IDC_STATIC_BATTLEZONEWIN) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_STATIC_BATTLEZONETOTALKILL) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_STATIC_BATTLEZONETIMEKILL) == (HWND)lParam ||

				GetDlgItem( hDlg, IDC_EDIT_STATUS_GUILDPOS) == (HWND)lParam  ||
				GetDlgItem( hDlg, IDC_EDIT_STATUS_GUILDNAME) == (HWND)lParam  ||
				GetDlgItem( hDlg, IDC_EDIT_STATUS_GUILDRANK) == (HWND)lParam  ||
				GetDlgItem( hDlg, IDC_LIST_STATUS_GUILDSTOCK) == (HWND)lParam 

				)
			{
				HDC hdc = (HDC)wParam;
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);				
				SetTextColor( hdc, COLOR_DIALOG_BLACK );

				return (BOOL)m_hStaticBrush;
			}
			else
			{
				HDC hdc = (HDC)wParam;
				SetBkMode(hdc,TRANSPARENT);
				SetBkColor( hdc, COLOR_DIALOG_STATIC_BLUE);
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				return (BOOL)m_hDlgBrush;
			}
			
		}
		break;
	case WM_TIMER:
		{
			cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];

			//----------------------
			// ����� ���� ǥ��. 
			//-----------------------
			
			// ����. 
			if(pclchar->pclCI->clBI.siWealthRank && pclchar->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
			{
				sprintf(buffer, "%d", pclchar->pclCI->clBI.siWealthRank);
			}
			else
			{
				char* pText = GetTxtFromMgr(610);
				sprintf(buffer, pText);
			}
			SetDlgItemText(hDlg, IDC_EDIT_WEALTHRANK, buffer);

			// ������. 
			char* pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumUnit(pclchar->pclCI->clBI.clTotalWealthMoney.itMoney, string, pText);

			sprintf(buffer, "%s", string);
			SetDlgItemText(hDlg, IDC_EDIT_TOTALWEALTH, buffer);


			// ���� ������Ʈ ��¥. 
			cltDate cldate;
			cldate.MakeFullDateFromDateVary(pclchar->pclCI->clBI.siWealthCalcDay);
			if(cldate.GetDateText(string) == TRUE)
			{
				pText = GetTxtFromMgr(612);
				sprintf(buffer, pText, string);
				SetDlgItemText(hDlg, IDC_STATIC_WEALTHUPDATE_DATE, buffer);
			}


			// ���� �ܾ� ǥ��. 
			pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumUnit(pclchar->pclCI->clBank.GetMoney(), string, pText);
			sprintf(buffer, "%s", string);
			SetDlgItemText(hDlg, IDC_EDIT_STATUS_BANKMONEY, buffer);

			// ���� ���� ǥ��. 
			char* pbankname = pclClient->pclVillageManager->GetName(pclchar->pclCI->clBank.clAccountNum.siVillageUnique);
			if(pbankname)
			{
				sprintf(buffer, "%s", pbankname);
			}
			else
			{
				pText = GetTxtFromMgr(613);
				sprintf(buffer, "%s", pText);
			}
			SetDlgItemText(hDlg, IDC_EDIT_STATUS_BANKVILLAGE, buffer);

			// �ֽ� 
			if(pclchar->pclCI->clStock.clInfo.IsSame(&clOldStockInfo) == false)
			{
				// ������ ������Ʈ �Ѵ�. 
				clOldStockInfo.Set(&pclchar->pclCI->clStock.clInfo);

				// ������ ����Ʈ�� �����Ѵ�. 
				ListDelete(hDlg, IDC_LIST_STATUS_STOCK);
				for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
				{
					SI32 villageunique  = pclchar->pclCI->clStock.clInfo.clUnit[i].siVillageUnique;
					SI32 num			= pclchar->pclCI->clStock.clInfo.clUnit[i].siAmount;
					
					if(villageunique)
					{
						pText = GetTxtFromMgr(614);
						sprintf(buffer, pText, pclClient->pclVillageManager->GetName(villageunique), num);
						ListAddString(hDlg, IDC_LIST_STATUS_STOCK, (LPARAM)buffer);
					}
				}
			}

			//_LEON_GUILD_STOCK
			// ��� �ֽ�
			if(pclchar->pclCI->clGuildStock.clInfo.IsSame(&clOldGuildStockInfo) == false)
			{
				clOldGuildStockInfo.Set(&pclchar->pclCI->clGuildStock.clInfo);

				ListDelete(hDlg, IDC_LIST_STATUS_GUILDSTOCK);

				for(i=0; i<MAX_GUILD_STOCK_KIND_IN_ACOUNT;i++)
				{
					SI32 villageunique = pclchar->pclCI->clGuildStock.clInfo.clUnit[i].siVillageUnique;
					UI08 unitslot	   = pclchar->pclCI->clGuildStock.clInfo.clUnit[i].uiUnitSlot;
					SI32 num		   = pclchar->pclCI->clGuildStock.clInfo.clUnit[i].siAmount;

					if(villageunique > 0 && villageunique < MAX_VILLAGE_NUMBER )
					{
						if(unitslot >=0 && unitslot < MAX_GUILDUNIT_NUMBER )
						{
                            pText = GetTxtFromMgr(5427);
							sprintf(buffer, pText, pclClient->pclVillageManager->GetName(villageunique), unitslot+1, num );
							ListAddString(hDlg, IDC_LIST_STATUS_GUILDSTOCK, (LPARAM)buffer);
						}
					}
				}
			}

			// ���� 
			ListDelete(hDlg, IDC_LIST_STATUS_HOUSE);
			for(i = 0;i < MAX_REAL_ESTATE_NUMBER_PER_PERSON;i++)
			{
				SI32 villageunique	= pclchar->pclCI->clRealEstate.clRealEstate[i].siVillageUnique;
				SI32 realestatetype	= pclchar->pclCI->clRealEstate.clRealEstate[i].siType;
				SI32 address		= pclchar->pclCI->clRealEstate.clRealEstate[i].siIndex;


				if(realestatetype == REALESTATE_TYPE_HOUSE)
				{
					pText = GetTxtFromMgr(615);
					sprintf(buffer, pText, pclClient->pclVillageManager->GetName(villageunique), address + 1);
					ListAddString(hDlg, IDC_LIST_STATUS_HOUSE, (LPARAM)buffer);
				}

				if(realestatetype == REALESTATE_TYPE_LAND)
				{
					pText = GetTxtFromMgr(616);
					sprintf(buffer, pText, pclClient->pclVillageManager->GetName(villageunique), address + 1);
					ListAddString(hDlg, IDC_LIST_STATUS_HOUSE, (LPARAM)buffer);
				}

				if(realestatetype == REALESTATE_TYPE_MINE)
				{
					pText = GetTxtFromMgr(3239);
					sprintf(buffer, pText, pclClient->pclVillageManager->GetName(villageunique), address + 1);
					ListAddString(hDlg, IDC_LIST_STATUS_HOUSE, (LPARAM)buffer);
				}
			}

			// �� 
			ListDelete(hDlg, IDC_LIST_STATUS_SHIP);			
			for( i = 0; i < MAX_SHIP_PER_PERSON; ++i )
			{
				if ( pclchar->pclCI->clShipInfo.clShip[ i ].siShipID > 0 )
				{
					strcpy( buffer, "" );

					if ( pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos == ShipPos_HouseUnit )
					{
						pText = GetTxtFromMgr(617);
						sprintf( buffer, pText, pclClient->pclShipManager->GetShipKindName( pclchar->pclCI->clShipInfo.clShip[i].siKind ) );
					}
					else if ( pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos >= ShipPos_Port && pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos <= CUR_VILLAGE_LIMIT )
					{
						pText = GetTxtFromMgr(618);
						sprintf( buffer, pText, pclClient->pclShipManager->GetShipKindName( pclchar->pclCI->clShipInfo.clShip[i].siKind ), pclClient->pclVillageManager->GetName( pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos ) );
					}
					else if ( pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos == ShipPos_Field || pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos > CUR_VILLAGE_LIMIT )
					{
						sprintf( buffer, "[%s] %s %d,%d", pclClient->pclMapManager->GetMapName( pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos ), pclClient->pclShipManager->GetShipKindName( pclchar->pclCI->clShipInfo.clShip[i].siKind ), pclchar->pclCI->clShipInfo.clShip[i].clPos.GetX(), pclchar->pclCI->clShipInfo.clShip[i].clPos.GetY() );
					}
					else
					{
						pclClient->pclLog->FilePrint( "Config/Ship.txt", "pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos = %d", pclchar->pclCI->clShipInfo.clShip[ i ].siShipPos );
					}
					
					ListAddString(hDlg, IDC_LIST_STATUS_SHIP, (LPARAM)buffer);
				}
			}

			HWND hWnd = NULL ;
			char strBuf[256] = "" ;
			memset(strBuf,0,256);
			pText = GetTxtFromMgr(5498);
			wsprintf(strBuf,pText,pclchar->pclCI->clBI.siBattleZoneWin,pclchar->pclCI->clBI.siBattleWinRank);
			hWnd = GetDlgItem( hDlg, IDC_STATIC_BATTLEZONEWIN );
			SetWindowText( hWnd, strBuf );

			memset(strBuf,0,256);
			pText = GetTxtFromMgr(5499);
			wsprintf(strBuf,pText,pclchar->pclCI->clBI.siBattleZoneTotalKill,pclchar->pclCI->clBI.siBattleKillRank);
			hWnd = GetDlgItem( hDlg, IDC_STATIC_BATTLEZONETOTALKILL );
			SetWindowText( hWnd, strBuf );

			memset(strBuf,0,256);
			wsprintf(strBuf,"%d",pclchar->pclCI->clBI.siBattleZoneTimeKill);
			hWnd = GetDlgItem( hDlg, IDC_STATIC_BATTLEZONETIMEKILL );
			SetWindowText( hWnd, strBuf );

		}
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);
		return TRUE;

	case WM_NOTIFY:
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			return TRUE;

		case IDCANCEL:
			return TRUE;
			
		}
		return TRUE;
	}
	return FALSE;

}

// ���� ������ ��� ������ ǥ���Ѵ�.
void cltCharStatus::ShowMyGuildInfo( SI32 villageunique, char* guildname, char* guildrankname )
{
	//if(villageunique <=0 || villageunique >=MAX_VILLAGE_NUMBER ) return;
    if(guildname == NULL ) 
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDNAME), "");
	else		
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDNAME), guildname );

	if(guildrankname == NULL )
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDRANK), "" );
	else
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDRANK), guildrankname );

	char* pVillName = NULL;
	pVillName = pclClient->pclVillageManager->GetName( villageunique );

	if( pVillName == NULL )
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDPOS), "" );
	else
		SetWindowText( GetDlgItem(TabDlg[3], IDC_EDIT_STATUS_GUILDPOS), pVillName );
}


BOOL cltCharStatus::CreateTabDlg(HWND hDlg, SI32 page, SI32 dlg, DLGPROC proc)
{
	RECT rect;
	SI32 tabindex = 0;

	tabindex = page;

	// �̹� �����찡 ������� ��Ȳ�̸� �ܼ��� ȭ�鿡 �����ֱ⸸ �Ѵ�. 
	if(TabDlg[tabindex])
	{
		ShowWindow(TabDlg[tabindex], SW_SHOW) ;
	}
	else
	{
		HWND hwnd = GetDlgItem(hDlg, IDC_TAB_STATUS);
		TabDlg[tabindex] = CreateDialog(pclClient->GetInstance(), MAKEINTRESOURCE(dlg), hwnd, proc);
		
		
		GetClientRect(hwnd, &rect);
		TabCtrl_AdjustRect(hwnd, FALSE, &rect);
		
		MoveWindow(TabDlg[tabindex], rect.left, rect.top, rect.right-rect. left,
			rect.bottom- rect.top, TRUE);
		
		ShowWindow(TabDlg[tabindex], SW_SHOW) ;
	}

	return TRUE;
}

void cltCharStatus::UpdateSummonStatusInfo(HWND hDlg)
{
	HWND hwnd;
	char buffer[256];
	BOOL bSummonExist= FALSE;
	

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)	{return ;}

	//==============================================
	// ��ȯ���� ������ ���ư���.
	//==============================================
	cltClient*   pclclient = (cltClient*)pclClient;
	// ��ȯ���������� �����Ѵ�.
	cltSummonInfo *pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	hwnd = GetDlgItem(hDlg,IDC_CHECK_SUMMON_AUTOHEAL);
	if ( pclSummonInfo->bAutoHeal )
	{
		if(SendMessage(hwnd , BM_GETCHECK, 0, 0 ) == BST_UNCHECKED )
		{
			SendMessage( hwnd, BM_SETCHECK, BST_CHECKED, 0 );
		}
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL30),TRUE);
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL50),TRUE);
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL70),TRUE);
	}
	else
	{
		if(SendMessage(hwnd , BM_GETCHECK, 0, 0 ) == BST_CHECKED )
		{
			SendMessage( hwnd, BM_SETCHECK, BST_UNCHECKED, 0 );
		}
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL30),FALSE);
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL50),FALSE);
		EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SUMMON_AUTOHEAL70),FALSE);
	}

	switch(pclSummonInfo->siSelectAutoHeal)
	{
	case 0 : CheckRadioButton(hDlg,IDC_RADIO_SUMMON_AUTOHEAL30,IDC_RADIO_SUMMON_AUTOHEAL70,IDC_RADIO_SUMMON_AUTOHEAL30); break;
	case 1 : CheckRadioButton(hDlg,IDC_RADIO_SUMMON_AUTOHEAL30,IDC_RADIO_SUMMON_AUTOHEAL70,IDC_RADIO_SUMMON_AUTOHEAL50); break;
	case 2 : CheckRadioButton(hDlg,IDC_RADIO_SUMMON_AUTOHEAL30,IDC_RADIO_SUMMON_AUTOHEAL70,IDC_RADIO_SUMMON_AUTOHEAL70); break;
	}

	if(pclSummonInfo->HaveSummon())
	{
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex))
		{
			cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
			switch(pclSummon->siStatus)
			{
			case SUMMON_STATUS_DEAD:
				{
					// ���� �����̴�. 
					hwnd = GetDlgItem(hDlg, IDC_STATIC_SUMMON_STATUS); 
					char* pText = GetTxtFromMgr(619);
					SetWindowText(hwnd, pText);

				}
				break;
			case SUMMON_STATUS_TAKEOUT:
				{
					if(pclSummon->clIP.GetLife() <= 0) 
					{
						// ���� �����̴�. 
						hwnd = GetDlgItem(hDlg, IDC_STATIC_SUMMON_STATUS); 
						char* pText = GetTxtFromMgr(620);
						SetWindowText(hwnd, pText);
					}
					else
					{
						hwnd = GetDlgItem(hDlg, IDC_STATIC_SUMMON_STATUS); 
						char* pText = GetTxtFromMgr(621);
						SetWindowText(hwnd, pText);
					}
				}
				break;
			case SUMMON_STATUS_TAKEIN:
				{
					hwnd = GetDlgItem(hDlg, IDC_STATIC_SUMMON_STATUS); 
					char* pText = GetTxtFromMgr(622);
					SetWindowText(hwnd, pText);
				}
				break;
			}
			
			bSummonExist = TRUE;
		}
	}
	else
	{
		hwnd = GetDlgItem(hDlg, IDC_STATIC_SUMMON_STATUS); 
		char* pText = GetTxtFromMgr(623);
		SetWindowText(hwnd, pText);
	}

	SI32 ButtonDlg[] = {IDC_BUTTON_STR, IDC_BUTTON_DEX,IDC_BUTTON_INT,IDC_BUTTON_VIT,-1};
	//==============================================
	// ��ȯ���� �����ϸ� 
	//==============================================
	if(bSummonExist)
	{
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;

		cltParametaBox clPB;	
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
		
		cltPIPInfo			clipinfo2;
		clipinfo2.Set(&pclSummon->clIP);
		clPB.Init(pclClient->pclItemManager, &clipinfo2, NULL, pclki);
	
		bool bmosterhero = false;
		// �����۸����� �Ǹ��ϴ� ��ȯ�����̰� ���Ϳ��� ��ȭ�� ���̶��, 
		if(pclki->bSummonMall && pclSummon->siIdentity == 0)	
		{
			bmosterhero = true;
		}

		//--------------------------------------
		// ��ȯ���� ��� Ȯ���Ѵ�. 
		//--------------------------------------
		SI32 equipset = EQUIPSET_PERSON;
		switch(SummonIndex)
		{
		case 0:			equipset = EQUIPSET_SUMMON1;	break;
		case 1:			equipset = EQUIPSET_SUMMON2;	break;
		default:		MsgBox("vd3fdf", "Ve3sdf:%d", SummonIndex);
		}
		
		cltItem* pclitemlist = pclCM->CR[id]->pclCI->clCharItem.GetEquipSet(equipset);
		
		clPB.Action(NULL, 0, PERSONITEM_WEAPON1, pclitemlist, NULL, NULL, NULL, NULL, &pclSummon->clScroll, NULL, GAMEMODE_CLIENT, true, bmosterhero);
		
		/*
		//==============================================
		// 
		//==============================================
		// �̸� 
		// ��ȯ�� ������ ó�� ���� ���
		if ( strSummonName != NULL && strlen ( strSummonName) == 0 )
		{
			strcpy( strSummonName, pclSummon->szName );
			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME ), pclSummon->szName );

			//==============================================
			// COMBO LIST�� ��ȯ�� �̸��� �����Ѵ�.
			//==============================================
			SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_RESETCONTENT, 0, 0);	
			ComboAddString(hDlg, IDC_COMBO_SUMMON_LIST, (LPARAM)pclSummon->szName);
			SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_SETCURSEL, 0, 0);	
		}
		
		// �����κ��� �̸��� �ٲ���ٰ� �뺸�� �� ���
		if ( strSummonName != NULL && strlen ( strSummonName ) > 0 && strcmp( strSummonName, pclSummon->szName ) != 0 )
		{
			strcpy( strSummonName, pclSummon->szName );
			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME ), pclSummon->szName );

			//==============================================
			// COMBO LIST�� ��ȯ�� �̸��� �����Ѵ�.
			//==============================================
			SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_RESETCONTENT, 0, 0);	
			ComboAddString(hDlg, IDC_COMBO_SUMMON_LIST, (LPARAM)pclSummon->szName);
			SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_SETCURSEL, 0, 0);	
		}
		*/
		
		// ����
		hwnd = GetDlgItem(hDlg, IDC_STATIC_LEVEL); 
		char* pText = GetTxtFromMgr(624);
		sprintf(buffer, pText, pclSummon->clIP.GetLevel(), MAX_LEVEL, pclki->siEvolveLevel);
		SetWindowText(hwnd, buffer);
		
		// ����ġ
		hwnd = GetDlgItem(hDlg, IDC_STATIC_EXP); 
		sprintf(buffer, "%d / %d", pclSummon->clIP.GetCurExp(), clPB.GetNextExp());
		SetWindowText(hwnd, buffer);
		
		// ü��
		hwnd = GetDlgItem(hDlg, IDC_STATIC_LIFE); 
		sprintf(buffer, "%d / %d", pclSummon->clIP.GetLife(), clPB.GetMaxLife());
		SetWindowText(hwnd, buffer);
		
		// ������ 
		hwnd = GetDlgItem(hDlg, IDC_STATIC_MANA); 
		sprintf(buffer, "%d / %d", pclSummon->clIP.GetMana(), clPB.GetMaxMana());
		SetWindowText(hwnd, buffer);

		//==============================================
		// 
		//==============================================
		// �ٷ�
		hwnd = GetDlgItem(hDlg, IDC_EDIT_STR); 
		sprintf(buffer, "%d", clPB.clTotalBA.GetStr() );
		SetWindowText(hwnd, buffer);
		
		// �ٷ·� �� ������ �����Ѵ�. 
		ShowDetailStrInfo(hDlg, &clPB);
		
		//  ���߷�
		hwnd = GetDlgItem(hDlg, IDC_EDIT_DEX); 
		sprintf(buffer, "%d", clPB.clTotalBA.GetDex() );
		SetWindowText(hwnd, buffer);
		
		// ���߷� �� ������ �����Ѵ�. 
		ShowDetailDexInfo(hDlg, &clPB);
		
		// ����
		hwnd = GetDlgItem(hDlg, IDC_EDIT_INT); 
		sprintf(buffer, "%d", clPB.clTotalBA.GetMag() );
		SetWindowText(hwnd, buffer);
		
		// ���� �� ������ �����Ѵ�. 
		ShowDetailMagInfo(hDlg, &clPB);
		
		// ����� 
		hwnd = GetDlgItem(hDlg, IDC_EDIT_VIT); 
		sprintf(buffer, "%d", clPB.clTotalBA.GetVit() );
		SetWindowText(hwnd, buffer);
		
		// ����� �� ������ �����Ѵ�. 
		ShowDetailVitInfo(hDlg, &clPB);
		
		// �������ʽ�  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_BATTLEBONUS); 
		sprintf(buffer, "%d", pclSummon->clIP.GetBonus() );
		SetWindowText(hwnd, buffer);
		
		
		//==============================================
		// �̵��ӵ� 
		//==============================================
		/*
		hwnd = GetDlgItem(hDlg, IDC_EDIT_TOTALSPEED); 
		sprintf(buffer, "%d", clPB.TotalMoveSpeed);
		SetWindowText(hwnd, buffer);
		
		  // �̵��ӵ� �� ������ �����Ѵ�. 
		  ShowDetailSpeedInfo(hDlg, &clPB, NULL);
		*/
		
		// ���ݷ�  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_TOTALDAMAGE); 
		sprintf(buffer, "%d - %d", clPB.GetTotalMinDamage(),  clPB.GetTotalMaxDamage());
		SetWindowText(hwnd, buffer);
		
		// ���ݷ� �� ������ �����Ѵ�. 
		ShowDetailDamageInfo(hDlg, &clPB, pclitemlist, PERSONITEM_WEAPON1);
		
		// ����  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_ARMOURCLASS); 
		sprintf(buffer, "%d", clPB.GetTotalAC());
		SetWindowText(hwnd, buffer);
		
		// ���� �� ������ �����Ѵ�. 
		ShowDetailArmourInfo(hDlg, &clPB);
		
		//==============================================
		// ���ʽ� ��ư 
		//==============================================
		SI32 index = 0;
		// ���ʽ� ��ġ ������ ��ư�� �����Ѵ�. 
		if(pclSummon->clIP.GetBonus())
		{
			if(BonusSummonButtonEnableSwitch == FALSE)
			{
				BonusSummonButtonEnableSwitch = TRUE;
				index = 0;
				while(ButtonDlg[index] >0)
				{
					hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
					EnableWindow(hwnd, TRUE);
					index++;
				}
			}
		}
		else
		{
			if(BonusSummonButtonEnableSwitch == TRUE)
			{
				BonusSummonButtonEnableSwitch = FALSE;
				index = 0;
				while(ButtonDlg[index] >0)
				{
					hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
					EnableWindow(hwnd, FALSE);
					index++;
				}
			}
		}
		
		//==============================================
		// 
		//==============================================
		// ����
		hwnd = GetDlgItem(hDlg, IDC_BUTTON_SUMMON_TAKEINOUT); 
		switch(pclSummon->siStatus)
		{
		case SUMMON_STATUS_TAKEIN:
			{
				switch(pclSummon->siUnique)
				{
				case 0: 
					{
						char* pText = GetTxtFromMgr(625);
						strcpy(buffer, pText);		
					}
					break;
				case 1:
					{
						char* pText = GetTxtFromMgr(626);
						strcpy(buffer, pText);		
					}
					break;
				default:
					{
						char* pText = GetTxtFromMgr(627);
						strcpy(buffer,pText);
					}break;
				}
			}
			break;
		case SUMMON_STATUS_TAKEOUT:	
			{
				if(pclSummon->clIP.GetLife() > 0) 
				{
					switch(pclSummon->siUnique)
					{
					case 0:
						{
							char* pText = GetTxtFromMgr(628);
							strcpy(buffer, pText);		
						}
						break;
					case 1:
						{
							char* pText = GetTxtFromMgr(629);
							strcpy(buffer, pText);
						}
						break;
					default:
						{
							char* pText = GetTxtFromMgr(630);
							strcpy(buffer, pText);
						}
						break;
					}
				}
				else
				{
					char* pText = GetTxtFromMgr(631);
					strcpy(buffer, pText);
				}
			}
			break;
		case SUMMON_STATUS_DEAD:	//strcpy(buffer, "��Ȱ");		break;
		default:	
			{
				char* pText = GetTxtFromMgr(631);
				strcpy(buffer, pText);	
			}break;
		}
		
		SetWindowText(hwnd, buffer);
		
		EnableWindow(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_ACTIVE ),      TRUE);
		EnableWindow(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_AVOID ),       TRUE);
		
		switch(pclSummon->siAttackType)
		{
		case SUMMON_ATTACKTYPE_ACTIVE:
			{
				SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_ACTIVE ),      BM_SETCHECK, BST_CHECKED,	0);
				SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_AVOID ),       BM_SETCHECK, BST_UNCHECKED,  0);
			}
			break;
		case SUMMON_ATTACKTYPE_AVOID:	
			{
				SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_ACTIVE ),      BM_SETCHECK, BST_UNCHECKED,	0);
				SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_AVOID ),       BM_SETCHECK, BST_CHECKED,    0);
			}
			break;
		}

		ShowDetailScrollInfo(hDlg, &pclSummon->clScroll);

	}
	else
	{
		strcpy(buffer, "");
		// �̸� 
		hwnd = GetDlgItem(hDlg, IDC_EDIT_STATUS_SUMMONNAME); 
		SetWindowText(hwnd, buffer);
		strcpy(strSummonName, "");
		
		SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_RESETCONTENT, 0, 0);	

		// ����
		hwnd = GetDlgItem(hDlg, IDC_STATIC_LEVEL); 
		SetWindowText(hwnd, buffer);
		// ����ġ
		hwnd = GetDlgItem(hDlg, IDC_STATIC_EXP); 
		SetWindowText(hwnd, buffer);
		// ü��
		hwnd = GetDlgItem(hDlg, IDC_STATIC_LIFE); 
		SetWindowText(hwnd, buffer);
		// ������ 
		hwnd = GetDlgItem(hDlg, IDC_STATIC_MANA); 
		SetWindowText(hwnd, buffer);
		// �ٷ�
		hwnd = GetDlgItem(hDlg, IDC_EDIT_STR);
		SetWindowText(hwnd, buffer);						
		//  ���߷�
		hwnd = GetDlgItem(hDlg, IDC_EDIT_DEX); 
		SetWindowText(hwnd, buffer);		
		// ����
		hwnd = GetDlgItem(hDlg, IDC_EDIT_INT); 
		SetWindowText(hwnd, buffer);				
		// ����� 
		hwnd = GetDlgItem(hDlg, IDC_EDIT_VIT); 
		SetWindowText(hwnd, buffer);				
		// �������ʽ�  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_BATTLEBONUS); 
		SetWindowText(hwnd, buffer);				
		// ���ݷ�  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_TOTALDAMAGE); 
		SetWindowText(hwnd, buffer);				
		// ����  
		hwnd = GetDlgItem(hDlg, IDC_EDIT_ARMOURCLASS); 
		SetWindowText(hwnd, buffer);				
		
		SI32 index = 0;
		if(BonusSummonButtonEnableSwitch == TRUE)
		{
			BonusSummonButtonEnableSwitch = FALSE;
			index = 0;
			while(ButtonDlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
				EnableWindow(hwnd, FALSE);
				index++;
			}
		}
		char* pText = GetTxtFromMgr(631);
		strcpy(buffer, pText);
		hwnd = GetDlgItem(hDlg, IDC_BUTTON_SUMMON_TAKEINOUT); 
		SetWindowText(hwnd, buffer);

		SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_ACTIVE ),      BM_SETCHECK, BST_UNCHECKED,	0);
		SendMessage(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_AVOID ),       BM_SETCHECK, BST_UNCHECKED,  0);
		
		EnableWindow(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_ACTIVE ),      FALSE);
		EnableWindow(GetDlgItem( hDlg,  IDC_RADIO_SUMMON_AVOID ),       FALSE);

	}


}


void cltCharStatus::SendSummonAttackTypeMessageToServer(HWND hDlg, SI32 siAttackType)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltClient* pclclient = (cltClient*)pclClient;
		SI32 id = 1;
		if(pclCM->IsAlive(id) == false)	return;

		cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
		if(pclSummonInfo == NULL) return;

		// ��ȯ���� ������ ����. 
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
			char* pText = GetTxtFromMgr(632);
			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
			return;
		}
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;
		//=======================================

		if(pclSummon)
		{
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(633);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return;
			}
			
			if(pclSummon->clIP.GetLife() <= 0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(634);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return;
			}
	
			//-----------------------------------
			// ���� �Ӽ������� ��û�Ѵ�.
			//-----------------------------------
			if( siAttackType == SUMMON_ATTACKTYPE_ACTIVE ||
				siAttackType == SUMMON_ATTACKTYPE_AVOID)
			{
				cltGameMsgRequest_SummonAttackChange clinfo(pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, siAttackType);
				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONATTACKCHANGE, sizeof(clinfo), (char*)&clinfo);
				pclclient->SendMsgToServer((char*)&clMsg);
				
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), "");
			}
		}
	}
	
}


void cltCharStatus::SendUseSummonBonusMessageToServer(HWND hDlg, SI16 data,bool bInit )
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltClient* pclclient = (cltClient*)pclClient;
		SI32 id = 1;
		if(pclCM->IsAlive(id) == false)	return;

		cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
		if(pclSummonInfo == NULL) return;

		// ��ȯ���� ������ ����. 
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
			char* pText = GetTxtFromMgr(632);
			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
			return;
		}
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;
		//=======================================
		if(pclSummon)
		{
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(633);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return;
			}
				
			if(pclSummon->clIP.GetLife() <= 0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(634);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return;
			}

			if ( bInit == false && pclSummon->clIP.GetBonus() <= 0 ) return ;

			cltGameMsgRequest_SummonUseBonusPoint clinfo(pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, data,bInit);
			cltMsg clMsg( GAMEMSG_REQUEST_USESUMMONBONUS, sizeof(clinfo), (char*)&clinfo);
			pclclient->SendMsgToServer((char*)&clMsg);

			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), "");
		}
	}
}


void cltCharStatus::SendSummonTakeInOutMessageToServer(HWND hDlg, SI32 siSummonUnique)
{
	//=====================================================
	// 300 ms ���Ͽ����� ��� �˻��� ���� ���ϰ� �Ѵ�.
	//=====================================================
	if(TABS(pclClient->CurrentClock - m_LastTakeInOutTime) < 300) return;
	m_LastTakeInOutTime = pclClient->CurrentClock ;
	//=====================================================

	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;
	if(pclclient->pclCM->IsAlive(id) == false)	return;
	
	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;
	// ��ȯ���� ������ ����. 
	if(pclSummonInfo->HaveSummon() == FALSE)
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(632);
		if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return;
	}

	cltSummon *pclSummon = NULL ;
	cltSummon *pclSummonOut = NULL ; // ������ ���� ���� ����
	//=======================================	
	// ����� VK_F6,VK_F7 �߰��� VK_F8
	//=======================================	
	if(hDlg == NULL)
	{
		// ���� Ű�� �����ϴ� ��ȯ���� �ۿ� ������ ������ ���� �ִ´�.
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID) == TRUE && pclCM->CR[id]->siSummonIndex == siSummonUnique )
		{
			pclSummon = pclSummonInfo->GetSummon(pclCM->CR[id]->siSummonIndex);
		}

		if(pclSummon == NULL)
		{
			// ���� Ű�� �����ϴ� ��ȯ���� �ȿ� ������ ������ ����.
			pclSummon = pclSummonInfo->GetSummon(siSummonUnique);
			if(pclSummon==NULL) return;

			// ������ ����Ѵ�.
			// TAKE IN OUT ��ų ��ȯ���� ������ ���ٸ� ��ü�� ã�´�.
			/*if(pclSummon->siKind == 0)
			{
				for(SI32 i = 0 ; i < MAX_SUMMON_OWN; ++i)
				{
					pclSummon = pclSummonInfo->GetSummon(i);
					if(pclSummon && pclSummon->siKind)	break;
				}
			}*/
		}
		if(pclSummon==NULL) return;
	}
	else
	{
		SI32 siSummonID = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(siSummonID) == TRUE && pclCM->CR[id]->siSummonIndex == siSummonUnique )
		{
			// ���� ��ȯ���� ���� ������ �����ִ� ���� �ϴ� ���� �ִ´�.
			pclSummon = pclSummonInfo->GetSummon(pclCM->CR[id]->siSummonIndex);
		}
		if(pclSummon == NULL)
		{
			//=======================================
			// ���� ComboList�� ��ȯ���� ���´�.
			//=======================================
			char SummonName[256]="";
			SI32 SummonIndex = 0;
			if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
			pclSummon = pclSummonInfo->GetSummon(SummonIndex);
			//=======================================
		}
		if(pclSummon==NULL) return;
	}

	if(pclSummon)
	{
		switch(pclSummon->siStatus)
		{
		case SUMMON_STATUS_TAKEIN:	//strcpy(buffer, "��ȯ");		break;
			{
				if( pclSummon->siKind &&
					pclSummon->clIP.GetLife() > 0 &&
					pclSummon->siStatus == SUMMON_STATUS_TAKEIN )//&&
					//pclCM->CR[id]->siChildCharUnique == 0)
				{
					cltGameMsgRequest_SummonTakeInOut  clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique,  SUMMON_STATUS_TAKEOUT);
					cltMsg clMsg( GAMEMSG_REQUEST_TAKEINOUT, sizeof(clinfo), (char*)&clinfo);
					pclclient->SendMsgToServer((char*)&clMsg);
				}
				else
				{
					/*if(pclCM->CR[id]->siChildCharUnique != 0)
					{
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						switch(pclSummon->siUnique)
						{
						case 0:	if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
										"��ȯ�� ��ȯ���� ���� ȸ���Ͽ��� �մϴ�. \r\n"
										"����Ű(F6)�� ����Ͻø� ���մϴ�." );	break;
						case 1: if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
										"��ȯ�� ��ȯ���� ���� ȸ���Ͽ��� �մϴ�. \r\n"
										"����Ű(F7)�� ����Ͻø� ���մϴ�." );	break;
						}
					}
					else*/ if(pclSummon->clIP.GetLife() <= 0)
					{
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						char* pText = GetTxtFromMgr(634);
						if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
                            					pText);
					}
					else
					{
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						char* pText = GetTxtFromMgr(637);
						if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
							pText);
					}
				}
			}
			break;
		case SUMMON_STATUS_TAKEOUT:	//strcpy(buffer, "ȸ��");		break;
			{
				if( pclSummon->siKind &&
					pclSummon->clIP.GetLife() > 0 &&
					pclSummon->siStatus == SUMMON_STATUS_TAKEOUT &&
					pclCM->CR[id]->siChildCharUnique != 0)
				{
					cltGameMsgRequest_SummonTakeInOut  clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique,  SUMMON_STATUS_TAKEIN);
					cltMsg clMsg( GAMEMSG_REQUEST_TAKEINOUT, sizeof(clinfo), (char*)&clinfo);
					pclclient->SendMsgToServer((char*)&clMsg);
				}
				else
				{
					if(pclSummon->clIP.GetLife() <= 0)
					{
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						char* pText = GetTxtFromMgr(638);
						if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
							pText);
					}
					else
					{
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						char* pText = GetTxtFromMgr(637);
						if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
							pText);
					}
				}
			}
			break;
		case SUMMON_STATUS_DEAD:    
			{
				if( pclSummon->siKind )
				{
/*					pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
					if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), 
						"��ȯ���� ����Ͽ����ϴ�.\r\n"
						"[������]�� ã�ư� ��Ȱ���Ѿ� �մϴ�.\r\n"
						"�ٷ� ��Ȱ ��Ű���� [��ȯ����Ȱ�̿��]�� �ʿ��մϴ�."
						);
					
					return;*/
					SI32 itemunique = 14060;  // ��ȯ����Ȱ�̿��
					if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
					{
						char buffer[256] = "" ;
						pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
						char* pText = GetTxtFromMgr(2837);
						sprintf(buffer, pText);

						pText = GetTxtFromMgr(619);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pText,buffer);
						return ;
					}

					char* pTitle = GetTxtFromMgr(578);
					char* pText = GetTxtFromMgr(2838);
					if(MessageBox(NULL, pText, pTitle,
						MB_TOPMOST|MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
					{
						cltGameMsgRequest_SummonRevive clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, SUMMON_REVIVE_TICKET);
						cltMsg clMsg( GAMEMSG_REQUEST_SUMMONREVIVE, sizeof(clinfo), (char*)&clinfo);
						pclclient->SendMsgToServer((char*)&clMsg);
					}
				}
				else
				{
					pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
					char* pText = GetTxtFromMgr(632);
					if(hDlg) SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
					return;
				}
			}
			break;
		}
	}
}

void cltCharStatus::SendSummonChangeNameMessageToServer(HWND hDlg)
{
	cltClient* pclclient = (cltClient*)pclClient;
	char ChangeSummonName[ MAX_SUMMON_NAME ] = "";
	SI32 id = 1;
	if(pclCM->IsAlive(id) == false)	return ;
	
	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;

	if(pclSummonInfo->HaveSummon() == FALSE)
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(632);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME), "");
		strcpy(strSummonName, "");
		
		return ;
	}
	
	//-----------------------------------
	// ��ȯ�� �̸��� ���´�.
	//-----------------------------------
	if ( GetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME ), ChangeSummonName, MAX_SUMMON_NAME ) == 0 )
	{
		return ;			
	}
	
	//-----------------------------------
	// ��ȯ���� �̸��� �˻��Ѵ�.
	//-----------------------------------
	//=======================================
	// ���� ComboList�� ��ȯ���� ���´�.
	//=======================================
	char SummonName[256]="";
	SI32 SummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
	cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
	if(pclSummon==NULL) return;

	char *pName = pclSummon->szName;
	if ( pName != NULL && strlen( pName ) > 0 && strcmp( pName, ChangeSummonName ) == 0 )
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(639);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return ;
	}
	
	if ( IsCorrectID( ChangeSummonName ) == FALSE )
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(640);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return ;
	}
	
	//-----------------------------------
	// �̸� ���� ��û�� �Ѵ�.
	//-----------------------------------
	cltGameMsgRequest_SummonNameChange  clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, ChangeSummonName );
	cltMsg clMsg( GAMEMSG_REQUEST_SUMMONNAMECHANGE, sizeof(clinfo), (char*)&clinfo);
	pclclient->SendMsgToServer((char*)&clMsg);
				
}


void cltCharStatus::SendSummonFreeMessageToServer(HWND hDlg)
{
	
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;
	if(pclclient->pclCM->IsAlive(id) == false)return ;
	
	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;

	// ��ȯ���� ������ ����. 
	if(pclSummonInfo->HaveSummon() == FALSE)
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(632);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return ;
	}
	else
	{
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;

		if(pclSummon)
		{
			if(pclSummon->siKind == 0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(641);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return ;
			}
			else if(pclSummon->siStatus == SUMMON_STATUS_DEAD)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(642);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return ;
			}

			char* pTitle = GetTxtFromMgr(578);
			char* pText = GetTxtFromMgr(643);
			if(MessageBox(hDlg, pText, pTitle, MB_TOPMOST|MB_YESNO|MB_ICONEXCLAMATION|MB_DEFBUTTON2) == IDYES)
			{
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), "");

				cltGameMsgRequest_SummonFree  clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique);
				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONFREE, sizeof(clinfo), (char*)&clinfo);
				pclclient->SendMsgToServer((char*)&clMsg);
			}
		}
	}
}


void cltCharStatus::SendSummonReviveMessageToServer(HWND hDlg)
{
	
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;
	if(pclclient->pclCM->IsAlive(id) == false)return ;
	
	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;

	// ��ȯ���� ������ ����. 
	if(pclSummonInfo->HaveSummon() == FALSE)
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(632);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return ;
	}
	else
	{
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;
		
		if(pclSummon)
		{
			if(pclSummon->siKind == 0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(633);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN), pText);
				return ;
			}
			
			if(pclSummon->siStatus != SUMMON_STATUS_DEAD)
			{
				if(pclSummon->clIP.GetLife()<=0)
				{
					pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
					char* pText = GetTxtFromMgr(644);
					SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
					return ;
				}
				else
				{
					pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
					char* pText = GetTxtFromMgr(645);
					SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
					return ;
				}
			}
			
			if(pclSummon->siStatus == SUMMON_STATUS_DEAD )//&& pclSummon->clIP.GetLife()<=0)
			{
				
				SI32 itemunique = 14060;  // ��ȯ����Ȱ�̿��
				if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				{
					char* pTitle = GetTxtFromMgr(647);
					char* pText = GetTxtFromMgr(646);
					MessageBox(hDlg, pText, pTitle, 
						MB_TOPMOST|MB_OK|MB_ICONEXCLAMATION);
					return ;
				}
				
				char* pTitle = GetTxtFromMgr(578);
				char* pText = GetTxtFromMgr(648);
				if(MessageBox(hDlg, pText, pTitle, MB_TOPMOST|MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
				{
					SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), "");
					
					cltGameMsgRequest_SummonRevive clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, SUMMON_REVIVE_TICKET);
					cltMsg clMsg( GAMEMSG_REQUEST_SUMMONREVIVE, sizeof(clinfo), (char*)&clinfo);
					pclclient->SendMsgToServer((char*)&clMsg);
				}
			}
		}
	}
}



void cltCharStatus::UpdateCharStatusInfo(HWND hDlg)
{
	HWND hwnd;
	char buffer[256];
	SI32 index = 0;

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		return ;
	}

	cltCharClient* pclchar = (cltCharClient*)pclCM->CR[id];
	
	// ĳ���� �ź�
	hwnd = GetDlgItem(hDlg, IDC_STATIC_RANK); 

	cltSimpleRank* pclrank = &pclCM->CR[id]->pclCI->clCharRank;
	UI08 grank = pclCM->CR[id]->pclCI->clBI.uiGRank;	

	if(GetRankName(pclrank, buffer,grank) == TRUE)
	{
		char FameLevelName[256] = "";
		if ( ((cltClient *)pclClient)->GetFameLevelName( pclCM->CR[id]->pclCI->clIP.siFameLevel, FameLevelName ) )
		{
			strcat( buffer, "-" );
			strcat( buffer, FameLevelName );
		}

		SetWindowText(hwnd, buffer);
	}

	// ����
	hwnd = GetDlgItem(hDlg, IDC_STATIC_LEVEL); 
	sprintf(buffer, "%d / %d", pclCM->CR[id]->pclCI->clIP.GetLevel(), MAX_LEVEL);
	SetWindowText(hwnd, buffer);
	
	// ����ġ
	hwnd = GetDlgItem(hDlg, IDC_STATIC_EXP); 
	sprintf(buffer, "%d / %d", pclCM->CR[id]->pclCI->clIP.GetCurExp(), pclCM->CR[id]->clPB.GetNextExp());
	SetWindowText(hwnd, buffer);
	
	// ü��
	hwnd = GetDlgItem(hDlg, IDC_STATIC_LIFE); 
	sprintf(buffer, "%d / %d", pclCM->CR[id]->GetLife(), pclCM->CR[id]->clPB.GetMaxLife());
	SetWindowText(hwnd, buffer);

	// ������ 
	hwnd = GetDlgItem(hDlg, IDC_STATIC_MANA); 
	sprintf(buffer, "%d / %d", pclCM->CR[id]->GetMana(), pclCM->CR[id]->clPB.GetMaxMana());
	SetWindowText(hwnd, buffer);
	
	// �ǰ� 
	hwnd = GetDlgItem(hDlg, IDC_STATIC_HEALTH); 
	SI32 healthpoint = pclCM->CR[id]->pclCI->clHealthInfo.uiHealthPoint;
	sprintf(buffer, "%d", healthpoint);
	SetWindowText(hwnd, buffer);


	// �������ʽ�  
	hwnd = GetDlgItem(hDlg, IDC_EDIT_BATTLEBONUS); 
	sprintf(buffer, "%d", pclCM->CR[id]->pclCI->clIP.GetBonus() );
	SetWindowText(hwnd, buffer);

	// �����
	hwnd = GetDlgItem(hDlg, IDC_STATIC_FAME); 
	sprintf(buffer, "%d/%d(%d / %d)", pclCM->CR[id]->pclCI->clIP.siFameLevel, MAX_FAME_LEVEL, 
		pclCM->CR[id]->pclCI->clIP.siFameExp, 
		GetRequiredFameExpForLevel(pclCM->CR[id]->pclCI->clIP.siFameLevel + 1));
	SetWindowText(hwnd, buffer);

	// �ٷ�
	hwnd = GetDlgItem(hDlg, IDC_EDIT_STR); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.clTotalBA.GetStr() );
	SetWindowText(hwnd, buffer);

	// �ٷ·� �� ������ �����Ѵ�. 
	ShowDetailStrInfo(hDlg, &pclchar->clPB);
	
	//  ���߷�
	hwnd = GetDlgItem(hDlg, IDC_EDIT_DEX); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.clTotalBA.GetDex() );
	SetWindowText(hwnd, buffer);

	// ���߷� �� ������ �����Ѵ�. 
	ShowDetailDexInfo(hDlg, &pclchar->clPB);
	
	// ����
	hwnd = GetDlgItem(hDlg, IDC_EDIT_INT); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.clTotalBA.GetMag() );
	SetWindowText(hwnd, buffer);

	// ���� �� ������ �����Ѵ�. 
	ShowDetailMagInfo(hDlg, &pclchar->clPB);
	
	// ����� 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_VIT); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.clTotalBA.GetVit() );
	SetWindowText(hwnd, buffer);

	// ����� �� ������ �����Ѵ�. 
	ShowDetailVitInfo(hDlg, &pclchar->clPB);
	
	// ������ 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_HND); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.clTotalBA.GetHnd() );
	SetWindowText(hwnd, buffer);

	// ������ �� ������ �����Ѵ�. 
	ShowDetailHndInfo(hDlg, &pclchar->clPB);
	
	// �̵��ӵ� 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_TOTALSPEED); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.TotalMoveSpeed);
	SetWindowText(hwnd, buffer);

	// �̵��ӵ� �� ������ �����Ѵ�. 
	ShowDetailSpeedInfo(hDlg, &pclchar->clPB, pclchar);

	// ���ݷ�  
	hwnd = GetDlgItem(hDlg, IDC_EDIT_TOTALDAMAGE); 
	sprintf(buffer, "%d - %d", pclCM->CR[id]->clPB.GetTotalMinDamage(),  pclCM->CR[id]->clPB.GetTotalMaxDamage());
	SetWindowText(hwnd, buffer);

	// ���ݷ� �� ������ �����Ѵ�. 
	ShowDetailDamageInfo(hDlg, &pclchar->clPB, pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON), pclchar->ActiveWeapon);

	// ����  
	hwnd = GetDlgItem(hDlg, IDC_EDIT_ARMOURCLASS); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.GetTotalAC());
	SetWindowText(hwnd, buffer);

	// ���� �� ������ �����Ѵ�. 
	ShowDetailArmourInfo(hDlg, &pclchar->clPB);
	
	/*
	// �������׷�. 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_DAMAGERESIST); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.GetTotalDamageResist());
	SetWindowText(hwnd, buffer);
	
	// ���� ���׷�. 
	hwnd = GetDlgItem(hDlg, IDC_EDIT_MAGICRESIST); 
	sprintf(buffer, "%d", pclCM->CR[id]->clPB.GetTotalMagicResist());
	SetWindowText(hwnd, buffer);
	*/
	
	SI32 ButtonDlg[] = {
		IDC_BUTTON_STR, 
		IDC_BUTTON_DEX,
		IDC_BUTTON_INT,
		IDC_BUTTON_VIT,
		IDC_BUTTON_HND,
		-1
	};

	// ���ʽ� ��ġ ������ ��ư�� �����Ѵ�. 
	if(pclCM->CR[id]->pclCI->clIP.GetBonus())
	{
		if(bBonusButtonEnableSwitch == false)
		{
			bBonusButtonEnableSwitch = true;

			index = 0;
			while(ButtonDlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
				EnableWindow(hwnd, TRUE);

				index++;
			}
		}
	}
	else
	{
		if(bBonusButtonEnableSwitch == true)
		{
			bBonusButtonEnableSwitch = false;

			index = 0;
			while(ButtonDlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, ButtonDlg[index]); 
				EnableWindow(hwnd, FALSE);

				index++;
			}
		}
	}

/*	SI32 Button2Dlg[] = {
		IDC_BUTTON_STR2, 
		IDC_BUTTON_DEX2,
		IDC_BUTTON_MAG2,
		IDC_BUTTON_VIT2,
		IDC_BUTTON_HND2,
		-1
	};

	// ���ºκ��ʱ�ȭ�̿���� ������ ��ġ ������ ��ư�� �����Ѵ�. 
	if(pclCM->CR[id]->pclCI->clCharItem.GetItemNum(14095) > 0)
	{
		if(bBonusButton2EnableSwitch == FALSE)
		{
			bBonusButton2EnableSwitch = TRUE;

			index = 0;
			while(Button2Dlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, Button2Dlg[index]); 
				EnableWindow(hwnd, TRUE);

				index++;
			}
		}
	}
	else
	{
		if(bBonusButton2EnableSwitch == TRUE)
		{
			bBonusButton2EnableSwitch = FALSE;

			index = 0;
			while(Button2Dlg[index] >0)
			{
				hwnd = GetDlgItem(hDlg, Button2Dlg[index]); 
				EnableWindow(hwnd, FALSE);

				index++;
			}
		}
	}
*/
	
	// �ǰ� ���� 
	char healthtext[2048];
	if(pclCM->CR[id]->clPB.clHealth.GetHealthText(pclCM->CR[id]->pclCI->clIP.GetLevel(), healthtext) == true)
	{
		SetDlgItemText(hDlg, IDC_EDIT_STATUS_HEALTH_EXPLAIN, healthtext);
	}

}


void cltCharStatus::SendUseBonusMessageToServer(SI32 pos, SI32 amount)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltGameMsgResponse_UseBonus clinfo(pos, amount);
		cltMsg clMsg(GAMEMSG_REQUEST_USEBONUS, sizeof(clinfo), (char*)&clinfo);
		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->SendMsgToServer((char*)&clMsg);
	}
}

void cltCharStatus::SendUseHorseBonusMessageToServer(char data)
{
	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id)
	{
		cltMsg clMsg(GAMEMSG_REQUEST_USEHORSE_BONUS, 1, &data);
		cltClient* pclclient = (cltClient*)pclClient;
		pclclient->SendMsgToServer((char*)&clMsg);
	}
}

// ���ݷ� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailDamageInfo(HWND hDlg, cltParametaBox* pclPB, cltItem* pclitemlist, SI32 activesweapon)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_APOWERNAME);

	// ������ ���� ���ݷ�. 
	char* pText = GetTxtFromMgr(649);
	sprintf(buffer, pText, pclPB->siLevelDamage);
	ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);

	if(pclitemlist && pclClient->pclItemManager->GetWeaponMinDamage(pclitemlist, activesweapon) )
	{
		pText = GetTxtFromMgr(650);
		if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND )
			sprintf(buffer, pText, pclPB->TotalEquipMinDamage*2, pclPB->TotalEquipMaxDamage*2);
		else
			sprintf(buffer, pText, pclPB->TotalEquipMinDamage, pclPB->TotalEquipMaxDamage);
	}
	else
	{
		pText = GetTxtFromMgr(651);
		sprintf(buffer, pText, pclPB->TotalEquipMinDamage, pclPB->TotalEquipMaxDamage);
	}

	ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);

	// ��ȭ 
	if(pclPB->siEvolveDamage)
	{
		pText = GetTxtFromMgr(652);
		sprintf(buffer, pText, pclPB->siEvolveDamage );
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);
	}

	if(pclPB->siAttackType == ATTACKTYPE_STAFF1 || pclPB->siAttackType == ATTACKTYPE_STAFF2 || pclPB->siAttackType == ATTACKTYPE_NEW_STAFF2)
	{
		// ���¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(653);
		sprintf(buffer, pText, pclPB->GetAddMagicDamage());
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);

		// �����̼��� ���� ���ݷ�. 
		pText = GetTxtFromMgr(654);
		sprintf(buffer, pText, pclPB->siStaffSkillDamage);
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);
	}
	else if ( pclPB->siAttackType == ATTACKTYPE_STAFFWIND ) // ������� ���
	{
		// ���¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(653);
		sprintf(buffer, pText, pclPB->GetAddMagicDamage());
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);
	}
	else
	{
		// �ٷ¿� ���� ���ݷ�. 
		pText = GetTxtFromMgr(655);
		sprintf(buffer, pText, pclPB->siStrDamage);
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);

	}

	// ��Ʈ �����ۿ� ���� ���ݷ�
	if ( ((cltCharClient*)pclClient->pclCM->CR[1])->m_siSetItemIndex > 0 )
	{
		pText = GetTxtFromMgr(5416);
		sprintf(buffer, pText, 30, '%');
		ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);
	}
	
	// ����ȿ��
	pText = GetTxtFromMgr(656);
	sprintf(buffer, pText, pclPB->siGeneralDamage, '%');
	ComboAddString(hDlg, IDC_COMBO_APOWERNAME, (LPARAM)buffer);


}


// �ٷ� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailStrInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_STR);

	// �⺻ �ٷ� 
	char* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetStr());
	ComboAddString(hDlg, IDC_COMBO_STR, (LPARAM)buffer);

	// ��� ���� �ٷ�
	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetStr());
	ComboAddString(hDlg, IDC_COMBO_STR, (LPARAM)buffer);
	
	// ���� ���� �ٷ� 
	pText = GetTxtFromMgr(659);
	sprintf(buffer, pText, pclPB->siHorseStr);
	ComboAddString(hDlg, IDC_COMBO_STR, (LPARAM)buffer);

	// �ǰ��� ���� �ٷ� 
	pText = GetTxtFromMgr(660);
	sprintf(buffer, pText, pclPB->siHealthStrRate, '%');
	ComboAddString(hDlg, IDC_COMBO_STR, (LPARAM)buffer);
	
	

}

// ���߷� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailDexInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_DEX);

	// �⺻ �ٷ� 
	char* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetDex());
	ComboAddString(hDlg, IDC_COMBO_DEX, (LPARAM)buffer);

	// ��� ���� �ٷ� 
	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetDex());
	ComboAddString(hDlg, IDC_COMBO_DEX, (LPARAM)buffer);

	// ���� ���� �ٷ� 
	pText = GetTxtFromMgr(659);
	sprintf(buffer, pText, pclPB->siHorseDex);
	ComboAddString(hDlg, IDC_COMBO_DEX, (LPARAM)buffer);

	// �ǰ��� ���� ���߷� 
	pText = GetTxtFromMgr(660);
	sprintf(buffer, pText, pclPB->siHealthDexRate, '%');
	ComboAddString(hDlg, IDC_COMBO_DEX, (LPARAM)buffer);
	
}

// ���� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailMagInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_MAG);

	// �⺻ �ٷ� 
	char* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetMag());
	ComboAddString(hDlg, IDC_COMBO_MAG, (LPARAM)buffer);

	// ��� ���� ���� 
	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetMag());
	ComboAddString(hDlg, IDC_COMBO_MAG, (LPARAM)buffer);
	
	// ���� ���� ���� 
	pText = GetTxtFromMgr(659);
	sprintf(buffer, pText, pclPB->siHorseMag);
	ComboAddString(hDlg, IDC_COMBO_MAG, (LPARAM)buffer);
	
	// �ǰ��� ���� ���� 
	pText = GetTxtFromMgr(660);
	sprintf(buffer, pText, pclPB->siHealthMagRate, '%');
	ComboAddString(hDlg, IDC_COMBO_MAG, (LPARAM)buffer);


}

// ����� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailVitInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_VIT);

	// �⺻ �ٷ� 
	char* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetVit());
	ComboAddString(hDlg, IDC_COMBO_VIT, (LPARAM)buffer);

	// ��� ���� �ٷ� 
	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetVit());
	ComboAddString(hDlg, IDC_COMBO_VIT, (LPARAM)buffer);

}

// ������ �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailHndInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_HND);

	// �⺻ �ٷ� 
	char* pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->pclIP->GetHnd());
	ComboAddString(hDlg, IDC_COMBO_HND, (LPARAM)buffer);

	// ��� ���� �ٷ� 
	pText = GetTxtFromMgr(658);
	sprintf(buffer, pText, pclPB->clEquipBA.GetHnd());
	ComboAddString(hDlg, IDC_COMBO_HND, (LPARAM)buffer);

}



// ���� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailArmourInfo(HWND hDlg, cltParametaBox* pclPB)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_DPOWERNAME);

	// ������ ���� ����. 
	char* pText = GetTxtFromMgr(649);
	sprintf(buffer, pText, pclPB->siLevelAC);
	ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);
	
	// �⺻ ���� 
	pText = GetTxtFromMgr(657);
	sprintf(buffer, pText, pclPB->siDefaultAC );
	ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);

	// ��ȭ 
	if(pclPB->siEvolveAC)
	{
		pText = GetTxtFromMgr(652);
		sprintf(buffer, pText, pclPB->siEvolveAC );
		ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);
	}

	// ���� ���� 
	pText = GetTxtFromMgr(809);
	sprintf(buffer, pText, pclPB->siEquipAC);
	ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);
	
	// ��Ʈ �����ۿ� ���� ���ݷ�
	if ( ((cltCharClient*)pclClient->pclCM->CR[1])->m_siSetItemIndex > 0 )
	{
		pText = GetTxtFromMgr(5416);
		sprintf(buffer, pText, 20, '%');
		ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);
	}
	
	// ����ȿ��
	pText = GetTxtFromMgr(656);
	sprintf(buffer, pText, pclPB->siGeneralAC, '%');
	ComboAddString(hDlg, IDC_COMBO_DPOWERNAME, (LPARAM)buffer);

}


// �̵��ӵ� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailSpeedInfo(HWND hDlg, cltParametaBox* pclPB, cltCharClient* pclchar)
{
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_DETAIL_SPEED);

	//KHY - 1001 - ��µ��� 5���� ���� ����.
	// ���� Ÿ�� �ִ� ���, 
	if(pclchar && pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		// ���� �̵��ӵ�. 
		char* pText = GetTxtFromMgr(659);
		sprintf(buffer, pText, pclPB->TotalMoveSpeed);
		ComboAddString(hDlg, IDC_COMBO_DETAIL_SPEED, (LPARAM)buffer);
	}
	// ���� Ÿ�� ���� ���� ���, 
	else
	{
		// �⺻ �̵��ӵ� 
		char* pText = GetTxtFromMgr(657);
		sprintf(buffer, pText, pclPB->BasicMoveSpeed);
		ComboAddString(hDlg, IDC_COMBO_DETAIL_SPEED, (LPARAM)buffer);
		
		// �Ź� �̵��ӵ�.  
		pText = GetTxtFromMgr(661);
		sprintf(buffer, pText, pclPB->ShoesMoveSpeed);
		ComboAddString(hDlg, IDC_COMBO_DETAIL_SPEED, (LPARAM)buffer);
	}

}


// �̵��ӵ� �� ������ �����Ѵ�. 
void cltCharStatus::ShowDetailScrollInfo(HWND hDlg, cltSummonScroll *pScroll )
{
	/*
	char buffer[256];

	// ��� �׸��� �����Ѵ�. 
	ComboDelete(hDlg, IDC_COMBO_SUMMON_SCROLL);
	
	if(pScroll)
	{
		for(SI32 i = 0 ; i<MAX_SCROLL_SUMMON_PER_KIND; ++i )
		{
			if(pScroll->siUnique[i])
			{
				sprintf(buffer, "%s:%0.1f%%", 
					pclClient->pclItemManager->GetName(pScroll->siUnique[i]),
					(float)(pScroll->siPercent[i] / 10.0));
				
				ComboAddString(hDlg, IDC_COMBO_SUMMON_SCROLL, (LPARAM)buffer);
			}
		}
	}
	*/
	char szScrollExplain[512];
	if(pScroll)
	{
		strcpy(szScrollExplain, "");
		for(SI32 i = 0 ; i<MAX_SCROLL_SUMMON_PER_KIND; ++i )
		{
			if(pScroll->siUnique[i])
			{
				char buffer[256] = "";
				sprintf(buffer, "%s:%0.1f%%\r\n", 
					pclClient->pclItemManager->GetName(pScroll->siUnique[i]),
					(float)(pScroll->siPercent[i] / 10.0));

				strcat(szScrollExplain, buffer);
			}
		}
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), szScrollExplain);
	}
}

//===================================================================
//
//===================================================================
BOOL cltCharStatus::GetComboSummonNameIndex(HWND hDlg, char *CurrSummonName, SI32 *siSummonIndex)
{
	// NULL �� ������ VK_F8 ���� ��û 
	if(hDlg == NULL)	return FALSE;

	// IDC_EDIT_STATUS_SUMMONNAME
	char TempSummonName[60] = "";
	char TempSummonIndex[60] = "";

	SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_GETLBTEXT, m_siLastSummonComboList, (LPARAM)TempSummonName);
	
	if(strlen(TempSummonName) >4)
	{
		strncpy(TempSummonIndex, TempSummonName, 1);
		SI32 siIndex = atoi(TempSummonIndex);
		siIndex--;
		if(siIndex<0 || siIndex>= MAX_SUMMON_OWN) return FALSE;

		strcpy(CurrSummonName,  pclCM->CR[1]->pclCI->clSummonInfo.clSummon[siIndex].szName);

		*siSummonIndex = siIndex;
		return TRUE;
	}
	return FALSE;
}

void cltCharStatus::InitSummonStatusInfo(HWND hDlg)
{
	if(m_bChangedInitSummonStatus)
	{
		//==============================================
		// COMBO LIST�� ��ȯ�� �̸��� �����Ѵ�.
		//==============================================
		SI32 siIndex = SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_GETCURSEL, 0, 0);	
		SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_RESETCONTENT, 0, 0);				
		SI32 siSummonCount = 0;
		char SummonName[256]="";
		for(SI32 i=0; i < MAX_SUMMON_OWN; ++i)
		{
			cltSummon *pclSummon = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon(i);
			if(pclSummon && pclSummon->siKind )
			{
				cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
				if(pclki)
				{
					sprintf(SummonName, "%d: %s", i+1, pclki->GetName());
					ComboAddString(hDlg, IDC_COMBO_SUMMON_LIST, (LPARAM)SummonName);
					siSummonCount++;
				}
			}
		}
		if(siIndex == CB_ERR)			siIndex = 0;
		if(siIndex >= siSummonCount)	siIndex = 0;
		SendDlgItemMessage(hDlg, IDC_COMBO_SUMMON_LIST, CB_SETCURSEL, siIndex, 0);	
		m_siLastSummonComboList = siIndex;


		// Combo List���� ���õ� ��ȯ���� �̸��� �����Ѵ�.
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex))
		{
			cltSummon *pclSummon = pclCM->CR[1]->pclCI->clSummonInfo.GetSummon(SummonIndex);
			if(pclSummon)
			{
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMONNAME ), pclSummon->szName );
			}
		}
		
		
	}
	//==============================================
	m_bChangedInitSummonStatus = FALSE;
}

void cltCharStatus::UpdateSummonPortrait(HWND hDlg)
{
	//==========================================
	// �ʻ�ȭ 
	//==========================================
	SI32 siSummonKind = 0;
	HBITMAP Portrait = m_hSummonPortraitBitmap;
	if(pclCM->CR[1]->pclCI->clSummonInfo.HaveSummon())
	{
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex))
		{
			siSummonKind = pclCM->CR[1]->pclCI->clSummonInfo.clSummon[SummonIndex].siKind;
			if((m_hSummonPortraitBitmap == NULL) || (siSummonKind && m_siPortraitSummonKind != siSummonKind ))			
			{
				char strFileName[ MAX_PATH ] = "";
				sprintf( strFileName, "Interface/Portrait/%s.bmp",	pclClient->pclKindInfoSet->pclKI[ siSummonKind ]->szCode );
				Portrait = (HBITMAP)LoadImage( pclClient->GetInstance(), strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

				m_siPortraitSummonKind = siSummonKind;
			}
		}
	}

	if( m_hSummonPortraitBitmap != Portrait )
	{
		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hSummonPortraitBitmap)
		{	
			DeleteObject(m_hSummonPortraitBitmap);	
			m_hSummonPortraitBitmap = NULL;	
		}
		if(Portrait)
		{
			m_hSummonPortraitBitmap = Portrait;
			SendDlgItemMessage( hDlg, IDC_STATIC_SUMMON_PORTRAIT, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hSummonPortraitBitmap);
		}
	}
}

void cltCharStatus::SendSummonStatusInitMessageToServer(HWND hDlg)
{
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;
	if(pclclient->pclCM->IsAlive(id) == false)return ;

	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;

	// ��ȯ���� ������ ����. 
	if(pclSummonInfo->HaveSummon() == FALSE)
	{
		pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
		char* pText = GetTxtFromMgr(632);
		SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
		return ;
	}
	else
	{
		//=======================================
		// ���� ComboList�� ��ȯ���� ���´�.
		//=======================================
		char SummonName[256]="";
		SI32 SummonIndex = 0;
		if(GetComboSummonNameIndex(hDlg, SummonName, &SummonIndex) == FALSE) return;
		cltSummon *pclSummon = pclSummonInfo->GetSummon(SummonIndex);
		if(pclSummon==NULL) return;

		if(pclSummon)
		{
			if(pclSummon->siKind == 0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(641);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return ;
			}

			if(pclSummon->siStatus == SUMMON_STATUS_DEAD || pclSummon->clIP.GetLife()<=0)
			{
				pclclient->PushEffect(EFFECT_FAILURE, 0, 0);
				char* pText = GetTxtFromMgr(2839);
				SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), pText);
				return ;
			}

			char buffer[256] = "" ;

			SI32 itemunique = 14090 ;  // �����ʱ�ȭ�̿��
			if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
			{
				char* pText = GetTxtFromMgr(608);
				sprintf(buffer, pText);

				char* pTitle = GetTxtFromMgr(605);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,buffer);
				return ;
			}

			char* pText = GetTxtFromMgr(2840);
			strcpy(buffer, pText);
			char* pTitle = GetTxtFromMgr(605);
			if (  MessageBox(NULL, buffer,pTitle,
				MB_ICONQUESTION | MB_YESNO) == IDNO )
			{
				return ;
			}

			SetWindowText( GetDlgItem( hDlg, IDC_EDIT_STATUS_SUMMON_EXPLAIN ), "");

			cltGameMsgRequest_Summon_StatusInit clinfo( pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique);
			cltMsg clMsg( GAMEMSG_REQUEST_SUMMON_STATUSINIT, sizeof(clinfo), (char*)&clinfo);
			pclclient->SendMsgToServer((char*)&clMsg);
		}
	}
}

void cltCharStatus::SendSummonAutoHealMessageToServer(HWND hDlg,SI16 data,bool autoheal)
{
	cltClient* pclclient = (cltClient*)pclClient;
	SI32 id = 1;
	if(pclclient->pclCM->IsAlive(id) == false)return ;

	cltSummonInfo* pclSummonInfo = &pclCM->CR[id]->pclCI->clSummonInfo;		
	if(pclSummonInfo == NULL) return;

	cltGameMsgRequest_Summon_SetAutoHeal clinfo( pclCM->CR[id]->GetCharUnique(), data,autoheal);
	cltMsg clMsg( GAMEMSG_REQUEST_SUMMON_SETAUTOHEAL, sizeof(clinfo), (char*)&clinfo);
	pclclient->SendMsgToServer((char*)&clMsg);
}