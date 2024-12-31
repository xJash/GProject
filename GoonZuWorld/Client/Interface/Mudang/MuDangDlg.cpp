
#include "../ErrorMsgDlg/ErrorMsgDlg.h"

#include "Char/CharCommon/Char-Common.h"
#include "Char/CharManager/CharManager.h"


#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Summon.h"
#include "../../../lib/WebHTML/WebHTML.h"
#include "../../Client/Client.h"
#include "../../Client/Music/Music.h"
#include "Char/KindInfo/KindInfo.h"
#include "MuDangDlg.h"

#include "../../../../DBManager/GameDBManager/DBMsg-Summon.h"

extern cltCommonLogic* pclClient;

// TIMER
CMuDangDlg::CMuDangDlg()
{
	m_hDlg			= NULL;
	m_hEditBrush	= NULL;
	m_bRect			= false;

	m_CurrentStatusPage	 = 0;
	for(SI32 i = 0; i< MAX_MUDANG_PAGE_NUMBER;i++)
	{
		m_TabDlg[i]	= NULL;
	}

	m_hPortraitBitmap = NULL;
	m_bChangedScrollPercent = FALSE;
	m_siActiveScrollIndex = 0;
	m_LastSendSummonTime  = 0;

	m_siSelectEvolveDlg = 0 ;
}

CMuDangDlg::~CMuDangDlg()
{
}

void CMuDangDlg::Create( HINSTANCE hInst, HWND hWnd )
{
	m_hInst = hInst;
	m_hWnd  = hWnd;
}

void CMuDangDlg::Set()
{
	if ( !IsWindow(m_hDlg) )
	{
		m_hDlg = CreateDialog( m_hInst, MAKEINTRESOURCE( IDD_DIALOG_MUDANG), m_hWnd, StaticMuDangDlgProc);

		if ( m_bRect ) 
		{
			MoveWindow(m_hDlg, m_DlgRect.left, m_DlgRect.top, m_DlgRect.right - m_DlgRect.left, m_DlgRect.bottom - m_DlgRect.top, FALSE);
		}

		ShowWindow( m_hDlg, SW_SHOW );
	}
	else
	{
		DestroyWindow(m_hDlg);
	}

}


BOOL CMuDangDlg::CreateTabDlg(HWND hDlg, SI32 page, SI32 dlg, DLGPROC proc)
{
	RECT rect;
	SI32 tabindex = 0;

	// ������ ����� ���ư���.
	if(page < 0 || page >= MAX_MUDANG_PAGE_NUMBER) return FALSE;
	
	tabindex = page;

	// �̹� �����찡 ������� ��Ȳ�̸� �ܼ��� ȭ�鿡 �����ֱ⸸ �Ѵ�. 
	if(m_TabDlg[tabindex])
	{
		ShowWindow(m_TabDlg[tabindex], SW_SHOW) ;
	}
	else
	{
		HWND hwnd = GetDlgItem(hDlg, IDC_TAB_MUDANG_TASK);
		m_TabDlg[tabindex] = CreateDialog(pclClient->GetInstance(), MAKEINTRESOURCE(dlg), hwnd, proc);
		
		GetClientRect(hwnd, &rect);
		TabCtrl_AdjustRect(hwnd, FALSE, &rect);
		
		MoveWindow(m_TabDlg[tabindex], rect.left, rect.top, rect.right-rect. left, rect.bottom- rect.top, TRUE);
		
		ShowWindow(m_TabDlg[tabindex], SW_SHOW) ;
	}

	return TRUE;
}


BOOL CALLBACK CMuDangDlg::StaticMuDangDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	cltClient *pclclient = (cltClient*)pclClient;
	return pclclient->m_pMuDangDlg->MuDangDlgProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CMuDangDlg::MuDangReviveStaticProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	cltClient *pclclient = (cltClient*)pclClient;
	return pclclient->m_pMuDangDlg->MuDangDlgReviveProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CMuDangDlg::MuDangScrollStaticProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	cltClient *pclclient = (cltClient*)pclClient;
	return pclclient->m_pMuDangDlg->MuDangDlgScrollProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CMuDangDlg::MuDangEvolveStaticProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	cltClient *pclclient = (cltClient*)pclClient;
	return pclclient->m_pMuDangDlg->MuDangDlgEvolveProc( hDlg, iMsg, wParam, lParam );
}



BOOL CALLBACK CMuDangDlg::MuDangDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwnd = NULL;
	
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{
			m_hDlg = hDlg;

			// EditBrush 
			m_hEditBrush = CreateSolidBrush( COLOR_DIALOG_WHITEBLUE);

			
			//==========================================
			// ������ �⺻ ��Ʈ 
			//==========================================
			char buffer[512]="";
			if(pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel()< LIMIT_LEVEL_HATCH_DOLL)
			{
				char* pText = GetTxtFromMgr(2270);
				sprintf(buffer, pText, LIMIT_LEVEL_HATCH_DOLL);
			}
			else
			{
				char* pText = GetTxtFromMgr(2271);
				strcpy(buffer, pText);
			}

			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_MUDANG), buffer);
			
			//==========================================
			// �ʻ�ȭ 
			//==========================================
			char* pText = GetTxtFromMgr(2272);
			SI32 siNCPKind = pclClient->pclKindInfoSet->FindKindFromName( pText );
			if(pclClient->pclKindInfoSet->pclKI[ siNCPKind ])
			{
				char strFileName[ 128 ] = "";
				sprintf( strFileName, "Interface/Portrait/%s.bmp",	pclClient->pclKindInfoSet->pclKI[ siNCPKind ]->szCode );
				m_hPortraitBitmap = (HBITMAP)LoadImage( m_hInst, strFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			}
			if ( m_hPortraitBitmap != NULL )
			{
				SendDlgItemMessage( hDlg, IDC_STATIC_PORTRAIT_MUDANG, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hPortraitBitmap );
			}

			//==========================================
			// TAB WINDOW
			//==========================================
			hwnd = GetDlgItem(hDlg, IDC_TAB_MUDANG_TASK);
			TC_ITEM item;
			item.mask= TCIF_TEXT; 
			item.iImage		= -1;
			pText = GetTxtFromMgr(2273);
			item.pszText	= pText;
			TabCtrl_InsertItem(hwnd, 0,  &item);

			pText = GetTxtFromMgr(2274);
			item.pszText	= pText;
			TabCtrl_InsertItem(hwnd, 1, &item);

			pText = GetTxtFromMgr(2275);
			item.pszText	= pText;
			TabCtrl_InsertItem(hwnd, 2, &item);

			m_CurrentStatusPage	= 0;
			switch(m_CurrentStatusPage)
			{
			case 0:
				CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_REVIVE, MuDangReviveStaticProc);
				break;
			case 1:
				CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_SCROLL, MuDangScrollStaticProc);
				break;
			case 2:
				CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_EVOLVE, MuDangEvolveStaticProc);
				break;
			}

		}
		return TRUE;
	case WM_TIMER:
		{			
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_MUDANG ) == (HWND)lParam ||
				 GetDlgItem( hDlg, IDC_EDIT_MESSAGE) == (HWND)lParam )
			{
				HDC hdc = (HDC)wParam;
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITEBLUE);
				return (BOOL)m_hEditBrush;
			}
		}
		break;

	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDOK:	
				{
					DestroyWindow(m_hDlg);
				}
				break;
			}
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR FAR *tem=(NMHDR FAR *)lParam;
			
			if (tem->code== TCN_SELCHANGE)
			{
				hwnd = GetDlgItem(hDlg, IDC_TAB_MUDANG_TASK);
				
				// ���� ȭ�鿡 ���̴� �������� �����. 
				if(m_TabDlg[m_CurrentStatusPage])	ShowWindow(m_TabDlg[m_CurrentStatusPage], SW_HIDE) ;
				
				m_CurrentStatusPage = TabCtrl_GetCurSel(tem->hwndFrom);
				
				switch(m_CurrentStatusPage )
				{
				case 0:
					CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_REVIVE, MuDangReviveStaticProc);
					break;
				case 1:
					CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_SCROLL, MuDangScrollStaticProc);
					break;
				case 2:
					CreateTabDlg(hDlg, m_CurrentStatusPage, IDD_DIALOG_MUDANG_EVOLVE, MuDangEvolveStaticProc);
					break;
				}
			}
		}
		return TRUE;	
	case WM_CLOSE:
		{
			DestroyWindow(m_hDlg);
		}
		break;
	case WM_DESTROY:
		{
			if ( m_hEditBrush )
			{
				DeleteObject( m_hEditBrush );
				m_hEditBrush= NULL;
			}

			if ( m_hPortraitBitmap )
			{
				DeleteObject( m_hPortraitBitmap );
				m_hPortraitBitmap = NULL;
			}
			
			for(SI32 i = 0;i < MAX_MUDANG_PAGE_NUMBER;i++)
			{
				if(m_TabDlg[i])
				{
					DestroyWindow( m_TabDlg[i] );
					m_TabDlg[i] = NULL;
				}
			}

			
			// �������� ��ġ�� ����Ѵ�. 
			GetWindowRect(m_hDlg, &m_DlgRect);
			m_bRect = true;
			

			m_hDlg = NULL;

		}
		break;
	}

	return FALSE;
}

BOOL CALLBACK CMuDangDlg::MuDangDlgReviveProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwnd = NULL;
	
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{
			SetTimer( hDlg, 1, 2000, NULL );

			UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, FALSE);
			UpdateReviveMent(hDlg);
		}
		break;
	case WM_CLOSE:
		{
			
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_SUMMON_REVIVE_EXPLAIN ) == (HWND)lParam)
			{
				HDC hdc = (HDC)wParam;
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITEBLUE);
				return (BOOL)m_hEditBrush;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDC_BUTTON_SUMMON_REVIVE:
				SendSummonReviveMessageToServer(hDlg, 1);	
				break;

			}
		}
		break;
	case WM_TIMER:
		{
			UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, FALSE);
			UpdateReviveMent(hDlg);
		}
		break;
	case WM_DESTROY:
		{
			KillTimer( hDlg, 1 );
		}
		break;
	}
			
	return FALSE;
}


BOOL CALLBACK CMuDangDlg::MuDangDlgScrollProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwnd = NULL;
	
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{
			SetTimer( hDlg, 10, 1000, NULL );

			//================================================
			// INIT SCROLL
			//================================================
			hwnd = GetDlgItem( hDlg, IDC_RADIO_HAVE_SCROLL_1 );
			if(hwnd)	SetWindowText(hwnd, "");
			hwnd = GetDlgItem( hDlg, IDC_RADIO_HAVE_SCROLL_2 );
			if(hwnd)	SetWindowText(hwnd, "");
			hwnd = GetDlgItem( hDlg, IDC_STATIC_SCROLL_PERCENT_1 );
			if(hwnd)	SetWindowText(hwnd, "");
			hwnd = GetDlgItem( hDlg, IDC_STATIC_SCROLL_PERCENT_2 );
			if(hwnd)	SetWindowText(hwnd, "");
			CheckRadioButton( hDlg, IDC_RADIO_HAVE_SCROLL_1, IDC_RADIO_HAVE_SCROLL_2, IDC_RADIO_HAVE_SCROLL_1 );
			m_siActiveScrollIndex   = 0;
			m_bChangedScrollPercent = TRUE;
			//================================================
			
			

			UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
			UpdateScrollSummonInfo(hDlg);

			UpdateScrollMent(hDlg);
			
			//============================================
			// ��ȭ %
			//============================================
			hwnd = GetDlgItem( hDlg, IDC_STATIC_SCROLL );
			char textbuffer[256] = "";
			char* pText = GetTxtFromMgr(2276);
			sprintf(textbuffer, pText, (float)(LIMIT_SUMMON_ADD_SCROLL_PERCENT/10.0));
			if(hwnd)	SetWindowText(hwnd, textbuffer);
		}
		break;
	case WM_CLOSE:
		{
			
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_SUMMON_SCROLL_EXPLAIN ) == (HWND)lParam)
			{
				HDC hdc = (HDC)wParam;
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITEBLUE);
				return (BOOL)m_hEditBrush;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDC_BUTTON_SUMMON_SCROLL:
				SendSummonScrollMessageToServer(hDlg, 1);
				break;
			case IDC_RADIO_HAVE_SCROLL_1:
				m_siActiveScrollIndex = 0;
				break;
			case IDC_RADIO_HAVE_SCROLL_2:
				m_siActiveScrollIndex = 1;
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
			UpdateScrollSummonInfo(hDlg);
			UpdateScrollMent(hDlg);
		}
		break;
	case WM_DESTROY:
		{
			KillTimer( hDlg, 10 );
		}
		break;
	}
	return FALSE;
}

BOOL CALLBACK CMuDangDlg::MuDangDlgEvolveProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwnd = NULL;
	
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{
			SetTimer( hDlg, 10, 1000, NULL );

			UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
			UpdateEvolveSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);

			UpdateEvolveMent(hDlg);

			m_siSelectEvolveDlg = 0 ;

			CheckRadioButton(hDlg,IDC_RADIO_EVOLVE,IDC_RADIO_TRANSFORM,IDC_RADIO_EVOLVE);
		}
		break;
	case WM_CLOSE:
		{
		}
		break;
	case WM_CTLCOLORSTATIC:
		{
			if ( GetDlgItem( hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN ) == (HWND)lParam)
			{
				HDC hdc = (HDC)wParam;
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITEBLUE);
				return (BOOL)m_hEditBrush;
			}
		}
		break;
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDC_BUTTON_SUMMON_EVOLVE:
				{
					switch(m_siSelectEvolveDlg)
					{
					case SUMMONEVOLVE_EVOLVE:
						SendSummonEvolveMessageToServer(hDlg, 1);
						break;
					case SUMMONEVOLVE_DEVOLUTION:
						SendSummonDevolutionMessageToServer(hDlg, 1);
						break;
					case SUMMONEVOLVE_TRANSFORM:
						SendSummonTransformMessageToServer(hDlg, 1);
						break;
					default:
						break;
					}
				}
				break;
			case IDC_RADIO_EVOLVE:
				{
					m_siSelectEvolveDlg = SUMMONEVOLVE_EVOLVE ;
					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateEvolveSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);

					SetWindowText(GetDlgItem(hDlg,IDC_BUTTON_SUMMON_EVOLVE),"��ȭ");
				}
				break;
			case IDC_RADIO_DEVOLUTION:
				{
					m_siSelectEvolveDlg = SUMMONEVOLVE_DEVOLUTION ;

					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateDevolutionSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);

					SetWindowText(GetDlgItem(hDlg,IDC_BUTTON_SUMMON_EVOLVE),"��ȭ");
				}
				break;
			case IDC_RADIO_TRANSFORM:
				{
					m_siSelectEvolveDlg = SUMMONEVOLVE_TRANSFORM ;

					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateTransformSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);

					SetWindowText(GetDlgItem(hDlg,IDC_BUTTON_SUMMON_EVOLVE),"��ȯ");
				}
				break;
			}
		}
		break;
	case WM_TIMER:
		{
			switch(m_siSelectEvolveDlg)
			{
			case SUMMONEVOLVE_EVOLVE:
				{
					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateEvolveSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);
					UpdateEvolveMent(hDlg);
				}
				break;
			case SUMMONEVOLVE_DEVOLUTION:
				{
					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateDevolutionSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);
					UpdateEvolveMent(hDlg);
				}
				break;
			case SUMMONEVOLVE_TRANSFORM:
				{
					UpdateCurrentSummonInfo(hDlg, IDC_COMBO_NOW_SUMMON, TRUE);
					UpdateTransformSummonInfo(hDlg, IDC_LIST_NEW_SUMMON);
					UpdateEvolveMent(hDlg);
				}
				break;
			default:
				break;
			}
		}
		break;
	case WM_DESTROY:
		{
			KillTimer( hDlg, 10 );
		}
		break;
	}
	return FALSE;
}


//===================================================================
//
//===================================================================
BOOL CMuDangDlg::GetComboSummonNameIndex(HWND hDlg, char *CurrSummonName, SI32 *siSummonIndex)
{
	char TempSummonName[60] = "";
	char TempSummonIndex[60] = "";
	ComboGetString(hDlg, IDC_COMBO_NOW_SUMMON, (LPARAM)TempSummonName);
	
	if(strlen(TempSummonName) >4)
	{
		strcpy(CurrSummonName,  &TempSummonName[3]);
		strncpy(TempSummonIndex, TempSummonName, 1);
		SI32 siIndex = atoi(TempSummonIndex);
		siIndex--;
		
		*siSummonIndex = siIndex;
		return TRUE;
	}
	return FALSE;
}

//===================================================================
// ���� �����ϰ� �ִ� ��ȯ���� ����� Update�Ѵ�.
// 1�� �� ���� �ϰ��ִ� ��Ȳ������ �� �ƹ��� �
//=================================================================== 
void CMuDangDlg::UpdateCurrentSummonInfo(HWND hDlg, SI32 Item, BOOL bALive)
{
	SI32 siCurIndex = SendDlgItemMessage(hDlg, Item, CB_GETCURSEL, 0, 0);	
	ComboDelete(hDlg, Item);	

	//===================================================================
	// bAlive ������ ����ִ� ��ȯ���� �׾� �ִ� ��ȯ����ϸ� �����Ѵ�.
	//===================================================================
	// ��ȯ���� Kind �̸��� ���´�.
	//===================================================================
	SI32 id = 1;
	char szName[128]="";
	SI32 siSummonCount = 0;
	for(SI32 i = 0 ; i < MAX_SUMMON_OWN; ++i)
	{
		cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(i);
		if(pclSummon == NULL) return;
		//===================================================================
		// ���� �˻� 
		//===================================================================
		SI32 siKind = pclSummon->siKind;
		if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)		continue;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
		if(pclki == NULL)									continue;
		//===================================================================
		
		if(bALive)	// ����ִ� ��ȯ���� ü�µ� �ְ� TAKEOUT�Ǿ� �־���Ѵ�.
		{
			if(pclSummon->clIP.GetLife() <= 0)				continue;
			if(pclSummon->siStatus != SUMMON_STATUS_TAKEOUT)continue;
		}
		if(!bALive)	// �׾��ִ� ��ȯ���� ü���� 0 �̰� DEAD�����̾���Ѵ�.
		{
			//if(pclSummon->clIP.GetLife() >  0)				continue;
			if(pclSummon->siStatus != SUMMON_STATUS_DEAD)	continue;
		}
		
		sprintf(szName, "%d: %s", i+1, pclClient->pclKindInfoSet->pclKI[siKind]->GetName());
		// ��������� �����ϴ� ��ȯ���� �߰��Ѵ�.
		ComboAddString(hDlg, Item, (LPARAM)szName);
		siSummonCount++;
	}
	
	// ���� �����ΰ��� ��� ���ٸ� ��ó���� ����Ű���� �Ѵ�.
	if(siCurIndex == LB_ERR)		 siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;
	SendDlgItemMessage(hDlg, Item, CB_SETCURSEL, siCurIndex, 0);	
}


//===================================================================
// �������� ��ȭ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank���� 1�� ���⸸ �ϸ� �ȴ�.
//===================================================================
void CMuDangDlg::UpdateEvolveSummonInfo(HWND hDlg, SI32 Item)
{
	SI32 siCurIndex = SendDlgItemMessage(hDlg, Item, LB_GETCURSEL, 0, 0);	

	ListDelete(hDlg, Item);	

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	SI32 siCurrentRank = pclki->siSummonRank;
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( pclClient->pclKindInfoSet->pclKI[i] &&
		    pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank+1 &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			ListAddString(hDlg, Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;
		
	SendDlgItemMessage(hDlg, Item, LB_SETCURSEL, siCurIndex, 0);	
}

//===================================================================
// �������� ��ȭ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank���� 1�� ���⸸ �ϸ� �ȴ�.
//===================================================================
void CMuDangDlg::UpdateDevolutionSummonInfo(HWND hDlg, SI32 Item)
{
	SI32 siCurIndex = SendDlgItemMessage(hDlg, Item, LB_GETCURSEL, 0, 0);	

	ListDelete(hDlg, Item);	

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 1)					return;
	SI32 siCurrentRank = pclki->siSummonRank;
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( pclClient->pclKindInfoSet->pclKI[i] &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank-1 &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			ListAddString(hDlg, Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;

	SendDlgItemMessage(hDlg, Item, LB_SETCURSEL, siCurIndex, 0);	
}

//===================================================================
// ���� ������� ��ȯ�� ��ȯ�� ����� ǥ���Ѵ�. 
// ������ Kind�� Rank�� ���� �ڱ�� ���� kind�� �ƴϸ� �ȴ�.
//===================================================================
void CMuDangDlg::UpdateTransformSummonInfo(HWND hDlg, SI32 Item)
{
	SI32 siCurIndex = SendDlgItemMessage(hDlg, Item, LB_GETCURSEL, 0, 0);	

	ListDelete(hDlg, Item);	

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE) return;

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	SI32 siCurrentRank = pclki->siSummonRank;
	//===================================================================

	SI32 siSummonCount = 0;
	// MONSTER �����߿��� ���� ��ȯ������ 1�ܰ� ���� ��ȭ����� ã�´�.
	for ( SI32 i = 1; i < MAX_KIND_NUMBER; ++i )
	{
		if( i != siKind && pclClient->pclKindInfoSet->pclKI[i] &&
		    pclClient->pclKindInfoSet->pclKI[i]->siSummonRank == siCurrentRank &&
			pclClient->pclKindInfoSet->pclKI[i]->siSummonRank <= LIMIT_SUMMON_RANK_EVOLVE &&
			pclClient->pclKindInfoSet->pclKI[i]->bSummonMall != TRUE)   // �̺κ� �� ����� ��ȯ�������� ��ȭ �ȴ�.
		{
			ListAddString(hDlg, Item, (LPARAM)pclClient->pclKindInfoSet->pclKI[i]->GetName());
			siSummonCount++;
		}
	}

	if(siCurIndex == LB_ERR)		siCurIndex = 0;
	if(siCurIndex >= siSummonCount)  siCurIndex = 0;
		
	SendDlgItemMessage(hDlg, Item, LB_SETCURSEL, siCurIndex, 0);	
}


//===================================================================
//
//===================================================================
void CMuDangDlg::UpdateScrollSummonInfo(HWND hDlg)
{

	//if(m_bChangedScrollPercent== FALSE) return;

	SI32 id = 1;
	//===================================================================
	// ������ SUMMON�� ���´�.
	//===================================================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		SetWindowText(GetDlgItem(hDlg, IDC_RADIO_HAVE_SCROLL_1),	""); 
		SetWindowText(GetDlgItem(hDlg, IDC_STATIC_SCROLL_PERCENT_1),""); 
		SetWindowText(GetDlgItem(hDlg, IDC_RADIO_HAVE_SCROLL_2),	""); 
		SetWindowText(GetDlgItem(hDlg, IDC_STATIC_SCROLL_PERCENT_2),""); 

		CheckRadioButton( hDlg, IDC_RADIO_HAVE_SCROLL_1, IDC_RADIO_HAVE_SCROLL_2, IDC_RADIO_HAVE_SCROLL_1 );
		m_siActiveScrollIndex   = 0;
		return;
	}

	cltSummon *pclSummon = pclClient->pclCM->CR[id]->pclCI->clSummonInfo.GetSummon(siSummonIndex);
	if(pclSummon == NULL) return;
	//===================================================================
	// ���� �˻� 
	//===================================================================
	SI32 siKind = pclSummon ->siKind;
	if(siKind <= 0 || siKind >= MAX_KIND_NUMBER)	return;
	cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siKind];
	if(pclki == NULL)								return;
	if(pclki->siSummonRank <= 0)					return;
	//===================================================================
	// ���� ������ �ɷ��� �����ش�.
	SI32 siUnique  = 0;
	SI32 siPercent = 0;
	char ScrollName[60] = "";
	char PercentString[30] = "";
	for(SI32 i = 0; i < MAX_SCROLL_SUMMON_PER_KIND; ++i)
	{
		siUnique  = pclSummon->clScroll.siUnique[i];
		siPercent = pclSummon->clScroll.siPercent[i];

		if(siUnique && pclClient->pclItemManager->GetName(siUnique))	
		{
			strcpy(ScrollName, pclClient->pclItemManager->GetName(siUnique));
			sprintf(PercentString, "%0.1f%%", (float)(siPercent/10.0)); 
		}
		else
		{
			strcpy(ScrollName, "");	
			strcpy(PercentString, ""); 
		}
	
		switch(i)
		{
		case 0:	SetWindowText(GetDlgItem(hDlg, IDC_RADIO_HAVE_SCROLL_1),	ScrollName); 
				SetWindowText(GetDlgItem(hDlg, IDC_STATIC_SCROLL_PERCENT_1),PercentString); 
			break;
		case 1:	SetWindowText(GetDlgItem(hDlg, IDC_RADIO_HAVE_SCROLL_2),	ScrollName); 
				SetWindowText(GetDlgItem(hDlg, IDC_STATIC_SCROLL_PERCENT_2),PercentString); 
			break;
		}
	}

	m_bChangedScrollPercent = FALSE;
}

//--------------------------------
// ��Ȱ �޽����� �����Ѵ�.
//--------------------------------
BOOL CMuDangDlg::SendSummonReviveMessageToServer(HWND hDlg, SI32 id)
{

	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;


	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	char buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE )
		{
			char* pText = GetTxtFromMgr(2277);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			char* pText = GetTxtFromMgr(2278);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];	
	if( pclSummon &&
		//pclSummon->clIP.GetLife() <= 0 &&
		pclSummon->siStatus == SUMMON_STATUS_DEAD)
	{
		//--------------------------------
		// ��Ȱ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = pclSummon->siKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;
		
		//--------------------------------
		// ��Ȱ��Ű������ �غ� ����
		//--------------------------------
		SI32 siSuccess = 1;
		SI32 siDollPos = 0;
		SI32 siDollUnique = pclClient->pclItemManager->GetItemDollUnique(kind);
		SI32 siDollNum   =  pclSummon->clIP.GetLevel();
		if(siDollUnique <= 0 || siDollNum	<= 0)	return FALSE;
		
		siDollPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siDollUnique);
		if( siDollPos >= PERSONITEM_INV0 && siDollPos < PERSONITEM_SUMMON1EQUIP0 )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siDollPos].siItemNum >= siDollNum)
			{
				cltGameMsgRequest_SummonRevive clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, SUMMON_REVIVE_DOLL);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONREVIVE, sizeof(clInfo), (char*)&clInfo);
				pclClient->SendMsgToServer((char*)&clMsg);

				DisplayMessage(-1, "");
				return TRUE;
			}
		}
		{
			char buffer[256];
			char* pText = GetTxtFromMgr(2279);
			sprintf(buffer, pText,  
				pclClient->pclItemManager->GetName(siDollUnique) , siDollNum );
			DisplayMessage(FALSE, buffer);
		}
		
	}
	else
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2280);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
	}

	return FALSE;
}



BOOL CMuDangDlg::SendSummonEvolveMessageToServer(HWND hDlg, SI32 id)
{

	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;
	
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	char buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2281);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			char* pText = GetTxtFromMgr(2282);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;
	
	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	char NewSummonName[256] = "";
	ListGetString(hDlg, IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	if(strlen(NewSummonName)<=0)
	{
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			char* pText = GetTxtFromMgr(2283);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			char* pText = GetTxtFromMgr(2284);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}


	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//============================================
		// ��ȭ LEVEL���� ���� 
		//============================================
		if(pclSummon->clIP.GetLevel() < pclki->siEvolveLevel)
		{
			char* pText = GetTxtFromMgr(2285);
			sprintf(buffer, pText, pclki->siEvolveLevel);
			DisplayMessage(FALSE,  buffer);
			return FALSE;
		}

		//--------------------------------
		// ��ȭ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank+1)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.
		if(pclnewki->siSummonRank > LIMIT_SUMMON_RANK_EVOLVE)	
		{
			char* pText = GetTxtFromMgr(2283);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		
		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = 14050;		// ��ȭ�̿�� 
		SI32 siTicketNum    = GetSummonTicketNum(pclki->siSummonRank);
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;

		SI32 itemnum = GetSummonTicketNum(pclki->siSummonRank) ;
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTION;

		if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
		{
			siTicketNum -= 1 ;
		}

		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if ( siTicketNum )
		{
			if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < PERSONITEM_SUMMON1EQUIP0 )	
			{
				if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
				{
					cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
						pclSummon->siUnique, newkind,SUMMONEVOLVE_EVOLVE);
					cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (char*)&clInfo);
					pclClient->SendMsgToServer((char*)&clMsg);

					DisplayMessage(-1, "");
					return TRUE;
				}
			}
		}
		else
		{
			cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
				pclSummon->siUnique, newkind,SUMMONEVOLVE_EVOLVE);
			cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (char*)&clInfo);
			pclClient->SendMsgToServer((char*)&clMsg);

			DisplayMessage(-1, "");
			return TRUE;
		}
		
		{
			char buffer[256];
			char* pText = GetTxtFromMgr(2286);
			sprintf(buffer, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2287);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CMuDangDlg::SendSummonDevolutionMessageToServer(HWND hDlg, SI32 id)
{

	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	char buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2281);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			char* pText = GetTxtFromMgr(2282);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;

	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	char NewSummonName[256] = "";
	ListGetString(hDlg, IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	if(strlen(NewSummonName)<=0)
	{
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			char* pText = GetTxtFromMgr(2283);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			char* pText = GetTxtFromMgr(2284);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}


	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȭ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank-1)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.
		if(pclnewki->siSummonRank <= 0 ) return FALSE ;

		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = 14050;		// ��ȭ�̿�� 
		SI32 siTicketNum    = 1 ;
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;

		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < PERSONITEM_SUMMON1EQUIP0 )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
			{
				cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
					pclSummon->siUnique, newkind,SUMMONEVOLVE_DEVOLUTION);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (char*)&clInfo);
				pclClient->SendMsgToServer((char*)&clMsg);

				DisplayMessage(-1, "");
				return TRUE;
			}
		}

		{
			char buffer[256];
			char* pText = GetTxtFromMgr(2286);
			sprintf(buffer, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2287);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CMuDangDlg::SendSummonTransformMessageToServer(HWND hDlg, SI32 id)
{

	// 1000 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 1000) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	char buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2281);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			char* pText = GetTxtFromMgr(2282);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;

	//============================================
	// LIST BOX���� ���� ��ȭ�� SUMMON�� ���´�.
	//============================================
	char NewSummonName[256] = "";
	ListGetString(hDlg, IDC_LIST_NEW_SUMMON, (LPARAM)NewSummonName);
	if(strlen(NewSummonName)<=0)
	{
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[siCurrSummonKind];
		if(pclki != NULL && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE)
		{
			char* pText = GetTxtFromMgr(2283);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		else
		{
			char* pText = GetTxtFromMgr(2284);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
		}
		return FALSE;
	}


	SI32 siNewSummonKind = pclClient->pclKindInfoSet->FindKindFromName( NewSummonName );
	if(siNewSummonKind <= 0 || siNewSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	if(pclClient->pclKindInfoSet->pclKI[siNewSummonKind] == NULL)	return FALSE;

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT)
	{
		//--------------------------------
		// ��ȯ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȯ�Ǿ��� ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 newkind = siNewSummonKind;
		if(newkind <= 0 || newkind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclnewki = pclClient->pclKindInfoSet->pclKI[newkind];
		if(pclnewki == NULL)									return FALSE;
		if(pclnewki->siSummonRank != pclki->siSummonRank)		return FALSE;
		if(pclnewki->bSummonMall == TRUE ) return FALSE; // ��ȯ�������δ� �ȵȴ�.

		//--------------------------------
		// ��ȯ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siTicketPos	= 0;
		SI32 siTicketUnique = 14050;		// ��ȭ�̿�� 
		SI32 siTicketNum    = 1 ;
		if(siTicketUnique <= 0 || siTicketNum	<= 0)	return FALSE;

		siTicketPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siTicketUnique);

		if( siTicketPos >= PERSONITEM_INV0 && siTicketPos < PERSONITEM_SUMMON1EQUIP0 )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siTicketPos].siItemNum >= siTicketNum)
			{
				cltGameMsgRequest_SummonEvolve clInfo(pclClient->pclCM->CR[id]->GetCharUnique(),
					pclSummon->siUnique, newkind,SUMMONEVOLVE_TRANSFORM);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONEVOLVE, sizeof(clInfo), (char*)&clInfo);
				pclClient->SendMsgToServer((char*)&clMsg);

				DisplayMessage(-1, "");
				return TRUE;
			}
		}

		{
			char buffer[256];
			char* pText = GetTxtFromMgr(2286);
			sprintf(buffer, pText,  
				pclClient->pclItemManager->GetName(siTicketUnique) , siTicketNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2287);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CMuDangDlg::SendSummonScrollMessageToServer(HWND hDlg, SI32 id)
{
	// 500 ms ���Ͽ����� ��� �޽����� ���� ���� ���ϰ� �Ѵ�.
	if(TABS(pclClient->CurrentClock - m_LastSendSummonTime) < 500) return FALSE;
	m_LastSendSummonTime = pclClient->CurrentClock ;

	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return FALSE;

	char buffer[256];
	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE )
		{
			char* pText = GetTxtFromMgr(2288);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return FALSE;
		}
		else
		{
			char* pText = GetTxtFromMgr(2289);
			sprintf(buffer, pText);
			DisplayMessage(FALSE, buffer);
			return TRUE;
		}
	}
	//============================================
	// 
	//============================================
	cltSummon *pclSummon= pclSummonInfo->GetSummon(siSummonIndex);
	if(pclSummon == NULL) return FALSE;

	//============================================
	// KIND �� 
	//============================================
	SI32 siCurrSummonKind = pclClient->pclKindInfoSet->FindKindFromName( CurrSummonName );
	if(siCurrSummonKind <= 0 || siCurrSummonKind >= MAX_KIND_NUMBER)	return FALSE;
	// ���� �ϳ� �ۿ� ���� ��ȯ���� KIND�� �ٸ��� ���ư���.
	if(pclSummon->siKind !=siCurrSummonKind) return FALSE;
	
	//============================================
	// LISTVIEW���� ���� ��ȭ��ų �ɷ��� ���´�.
	//============================================
	SI32 siCurrentCheckedIndex = -1;
	if(SendDlgItemMessage(hDlg, IDC_RADIO_HAVE_SCROLL_1, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		siCurrentCheckedIndex = 0;
	}
	else if(SendDlgItemMessage(hDlg, IDC_RADIO_HAVE_SCROLL_2, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		siCurrentCheckedIndex = 1;
	}
	
	if(		(m_siActiveScrollIndex<0 || m_siActiveScrollIndex>=MAX_SCROLL_SUMMON_PER_KIND)
		||	(siCurrentCheckedIndex != m_siActiveScrollIndex))
	{
		char* pText = GetTxtFromMgr(2290);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}
	//============================================
	// UNIQUE ���� 
	//============================================
	SI32 siScrollUnique = pclSummon->clScroll.siUnique[m_siActiveScrollIndex] ;
	SI32 siScrollPercent= pclSummon->clScroll.siPercent[m_siActiveScrollIndex];
	
	if(siScrollUnique == 0)
	{
		char* pText = GetTxtFromMgr(2290);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
		return FALSE;
	}

	// �������� �������� Ȯ���Ѵ�. 
	SI32 atb = pclClient->pclItemManager->GetItemAtb(siScrollUnique);
	if((atb & ITEMATB_SCROLL) ==0)		return FALSE;

	// ������ ������ Ȯ���Ѵ�. 
	cltItemInfo* pclscrollinfo = pclClient->pclItemManager->FindItemInfo(siScrollUnique);
	if(pclscrollinfo == NULL)			return FALSE;

	// ������ ����� Ȯ���Ѵ�. 
	SI32 function	= pclscrollinfo->siScrollFunction;
	if(function <= 0)					return FALSE;

	// ������ ���� �ɷ��� ���Ѵ�.
	SI32 ability	= pclscrollinfo->siScrollAbility;
	if(ability <= 0)					return FALSE;

	//============================================
	// ���� ��ȭ % ���� 
	//============================================
	SI32 siMaxSrollPercent = min(LIMIT_SUMMON_ADD_SCROLL_PERCENT, pclSummon->clIP.GetLevel()*10/2 );
	if(siScrollPercent >= siMaxSrollPercent)
	{
		char* pText = GetTxtFromMgr(2291);
		sprintf(buffer, pText, LIMIT_SUMMON_ADD_SCROLL_PERCENT);
		DisplayMessage(FALSE,  buffer);
		return FALSE;
	}

	//============================================
	//
	//============================================
	cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[id];
	if( pclSummon->siKind &&
		pclSummon->clIP.GetLife() > 0 &&
		pclSummon->siStatus == SUMMON_STATUS_TAKEOUT )
	{
		//--------------------------------
		// ��ȭ��ų ��ȯ���� Kind�� �����Ѵ�.
		//--------------------------------
		SI32 kind = siCurrSummonKind;
		if(kind <= 0 || kind >= MAX_KIND_NUMBER)	return FALSE;
		cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[kind];
		if(pclki == NULL)							return FALSE;
		if(pclki->siSummonRank <= 0)				return FALSE;

		//--------------------------------
		// ��ȭ ��Ű������ �غ� ���� 
		//--------------------------------
		SI32 siSuccess		= 1;
		SI32 siScrollPos	= 0;
		SI32 siScrollNum    = 1;					// ���� ���� 
		if(siScrollUnique <= 0 || siScrollNum	<= 0)	return FALSE;
		
		siScrollPos = pclClient->pclCM->CR[id]->pclCI->clCharItem.GetItemPos(siScrollUnique);
		if( siScrollPos >= PERSONITEM_INV0 && siScrollPos < PERSONITEM_SUMMON1EQUIP0 )	
		{
			if(pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[siScrollPos].siItemNum >= siScrollNum)
			{
				cltGameMsgRequest_SummonScroll clInfo(pclClient->pclCM->CR[id]->GetCharUnique(), pclSummon->siUnique, siScrollUnique);
				cltMsg clMsg(GAMEMSG_REQUEST_SUMMONSCROLL, sizeof(clInfo), (char*)&clInfo);
				pclClient->SendMsgToServer((char*)&clMsg);
				DisplayMessage(-1, "");
				return TRUE;
			}
		}
		
		{
			char buffer[256];
			char* pText = GetTxtFromMgr(2286);
			sprintf(buffer, pText,  
				pclClient->pclItemManager->GetName(siScrollUnique) , siScrollNum );
			DisplayMessage(FALSE, buffer);
		}
	}
	else
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2292);
		sprintf(buffer, pText);
		DisplayMessage(FALSE, buffer);
	}


	return FALSE;
}

BOOL CMuDangDlg::DisplayMessage(BOOL bSuccess, char *pStr)
{
	if(m_hDlg)
	{
		if(bSuccess == TRUE)		pclClient->PushEffect(EFFECT_SUCCESS, 0, 0);
		else if(bSuccess == FALSE)	pclClient->PushEffect(EFFECT_FAILURE, 0, 0);	
		
		SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_MESSAGE ), pStr);
	}

	return TRUE;
}

void CMuDangDlg::UpdateReviveMent(HWND hDlg)
{
	char buffer[512];
	
	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2277);
			sprintf(buffer, pText);
		}
		else
		{
			char* pText = GetTxtFromMgr(2293);
			sprintf(buffer, pText);
		}
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_REVIVE_EXPLAIN), buffer);
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			if(pclki && pclSummon->clIP.GetLife()<=0)
			{
				if(pclSummon->siStatus == SUMMON_STATUS_DEAD)
				{
					char* pText = GetTxtFromMgr(2294);
					char num[128]= " " ;
					sprintf(num,"%d",pclSummon->clIP.GetLevel());
					Nsprintf(buffer,pText,"monster",    pclki->GetName(),"num", num   ,NULL);


					//sprintf(buffer, pText,
					//	pclki->GetName(),
					//	pclSummon->clIP.GetLevel()
					//	);
				}
				else
				{
					char* pText = GetTxtFromMgr(2295);
					sprintf(buffer, pText);
				}
				
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_REVIVE_EXPLAIN), buffer);
			}
		}
	}

}

void CMuDangDlg::UpdateEvolveMent(HWND hDlg)
{
	char buffer[512]="";
	cltClient *pclclient = (cltClient*)pclClient;

	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2277);
			sprintf(buffer, pText);
		}
		else
		{
			char* pText = GetTxtFromMgr(2282);
			sprintf(buffer, pText);
		}
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_REVIVE_EXPLAIN), buffer);
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			cltKindInfo* pclki	 = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			if(pclki && pclki->siSummonRank >= LIMIT_SUMMON_RANK_EVOLVE && m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE)
			{
				char* pText = GetTxtFromMgr(2296);
				sprintf(buffer, pText);
				
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN), buffer);
			}
			else if(pclki && pclSummon->clIP.GetLevel() >= pclki->siEvolveLevel && m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE)
			{
				SI32 itemnum = GetSummonTicketNum(pclki->siSummonRank) ;
				SI16 questtype, questunique, para1, para2;
				SI16 questclearcond =  QUEST_CLEAR_COND_SUMMONEVOLUTION;

				if(pclclient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
				{
					itemnum -= 1 ;
				}

				char* pText = NULL ;
				if ( itemnum )
				{
					pText = GetTxtFromMgr(2297);
					char num[128]= " " ;
					sprintf(num,"%d",itemnum);
					Nsprintf(buffer,pText,"monster",  pclClient->pclItemManager->GetName(14050)  ,"num", num   ,NULL);
					//sprintf(buffer,pText,pclClient->pclItemManager->GetName(14050),itemnum);
				}
				else
				{
					pText = GetTxtFromMgr(3194);
					sprintf(buffer,pText,pclClient->pclItemManager->GetName(14050));
				}

				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN), buffer);
			}
			else if ( m_siSelectEvolveDlg == SUMMONEVOLVE_EVOLVE )
			{
				char* pText = GetTxtFromMgr(2298);
				sprintf(buffer,
					pText, pclki->siEvolveLevel);
				
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN), buffer);
			}
			else if ( m_siSelectEvolveDlg == SUMMONEVOLVE_DEVOLUTION )
			{
				char* pText = GetTxtFromMgr(3284);
				char num[128]= " " ;
				
				sprintf(num,"%d",1);
				Nsprintf(buffer,pText,"item", pclClient->pclItemManager->GetName(14050)   ,"num",  num  ,NULL);


				//sprintf(buffer,pText,pclClient->pclItemManager->GetName(14050),1);

				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN), buffer);
			}
			else if ( m_siSelectEvolveDlg == SUMMONEVOLVE_TRANSFORM )
			{
				char* pText = GetTxtFromMgr(3285);
				char num[128]= " " ;
				
				sprintf(num,"%d",1);
				Nsprintf(buffer,pText,"item", pclClient->pclItemManager->GetName(14050)   ,"num",  num  ,NULL);

				//sprintf(buffer,pText,pclClient->pclItemManager->GetName(14050),1);

				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_EVOLVE_EXPLAIN), buffer);
			}
		}
	}
}


void CMuDangDlg::UpdateScrollMent(HWND hDlg)
{
	char buffer[512]="";
	
	SI32 id = 1;
	cltSummonInfo *pclSummonInfo = &pclClient->pclCM->CR[id]->pclCI->clSummonInfo;
	if(pclSummonInfo == NULL) return;

	//============================================
	// ������ SUMMON�� ���´�.
	//============================================
	char CurrSummonName[60] = "";
	SI32 siSummonIndex = 0;
	if(GetComboSummonNameIndex(hDlg, CurrSummonName, &siSummonIndex) == FALSE)
	{
		if(pclSummonInfo->HaveSummon() == FALSE)
		{
			char* pText = GetTxtFromMgr(2277);
			sprintf(buffer, pText);
		}
		else
		{
			char* pText = GetTxtFromMgr(2289);
			sprintf(buffer, pText);
		}
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_REVIVE_EXPLAIN), buffer);
	}
	else
	{
		cltSummon *pclSummon = pclSummonInfo->GetSummon(siSummonIndex);
		if(pclSummon)
		{
			cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
			if(pclki)
			{
				char* pText = GetTxtFromMgr(2299);
				sprintf(buffer, pText);
				
				SetWindowText(GetDlgItem(hDlg, IDC_EDIT_SUMMON_SCROLL_EXPLAIN), buffer);
			}
		}
	}
	

}