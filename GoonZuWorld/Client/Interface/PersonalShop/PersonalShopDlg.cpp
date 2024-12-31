#include "..\..\..\Common\SMLib\LibList\LibList.h"
#include "..\..\..\Common\PrivateTradeOrderMgr\PrivateTradeOrderObj.h"

#include "..\PrivateChatDlg\PrivateChatDlgMgr.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../Client/Interface/ErrorMsgDlg/ErrorMsgDlg.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"

#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Personalshop.h"
#include "../../../lib/WebHTML/WebHTML.h"
#include "../../Client/Client.h"
#include "PersonalShopDlg.h"
#include "..\..\Client\Music\Music.h"


extern cltCommonLogic* pclClient;

CPersonalShopDlg g_PersonalShopDlg;


CPersonalShopDlg::CPersonalShopDlg()
{
	m_hDlg = NULL;
	m_bShow = false;
	m_bTimer= false;

	m_hUserInventory	= NULL;
	m_hUserShopShowcase = NULL;
	m_hEditBrush		= NULL;

	m_bSelf		 = false;
	m_siShopMode = 0;
	m_bShopStarted = false;

	m_bShopDataChanged = false;
	m_bShopMoneyCheck = false;

	memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
	m_clShopData.Init();

	m_pPersonItemInfo	= NULL;
	m_siShopperCharUnique = 0;		// MINI HOMEPAGE�� ���� ���� 
	m_siShopperPersonID	  = 0;
	memset(m_szAccountID, 0, sizeof(m_szAccountID));
	memset(m_szCharName,  0, sizeof(m_szCharName));
	
	m_siUserInventorySelectedRealItemIndex  = -1;
	m_siUserInventorySelectedIndex			= -1;
	m_siShopShowCaseSelectedRealItemIndex	= -1;
	m_siShopShowCaseSelectedIndex			= -1;

	Initialize();
}

CPersonalShopDlg::~CPersonalShopDlg()
{
}

void CPersonalShopDlg::Initialize()
{
	return;
}

void CPersonalShopDlg::Destroy()
{

	return;
}

void CPersonalShopDlg::Create( HINSTANCE hInst, HWND hWnd )
{
	m_pPersonItemInfo = &pclClient->pclCM->CR[1]->pclCI->clCharItem;

	m_hDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG_PERSONAL_SHOP), hWnd, StaticPersonalShopDlgProc );
	m_bShow = false;
	Hide();
	

	return;
}


BOOL CALLBACK CPersonalShopDlg::StaticPersonalShopDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	return g_PersonalShopDlg.PersonalShopDlgProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CPersonalShopDlg::PersonalShopDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	HWND hwnd = NULL;
	cltClient *pclclient = (cltClient*)pclClient;
	
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{

			if(pclClient->siServiceArea == ConstServiceArea_Netmarble)
			{
				HWND hTemp = GetDlgItem(hDlg, IDC_BUTTON_MINIHOME);
				ShowWindow(hTemp, SW_HIDE);
			}

			m_hDlg = hDlg;
			m_hUserInventory = GetDlgItem( hDlg, IDC_LIST_SHOP_USER_INVENTORY );
			m_hUserShopShowcase = GetDlgItem( hDlg, IDC_LIST_SHOP_SHOWCASE );
			
			pclclient->pclImageList->ConnectToListView( m_hUserInventory, LVSIL_NORMAL );
			pclclient->pclImageList->ConnectToListView( m_hUserShopShowcase, LVSIL_NORMAL );

			if(m_hUserInventory)
			{
				ListView_SetExtendedListViewStyle( m_hUserInventory, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT | LVS_EX_INFOTIP );
			}
			
			if(m_hUserShopShowcase )
			{
				ListView_SetExtendedListViewStyle( m_hUserShopShowcase, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_INFOTIP);
				char* pText = GetTxtFromMgr(1227);
				ListViewInsertColumn( m_hUserShopShowcase,  90, pText, 0, 0);
				pText = GetTxtFromMgr(1678);
				ListViewInsertColumn( m_hUserShopShowcase,  80, pText,   1, 1);
				pText = GetTxtFromMgr(1679);
				ListViewInsertColumn( m_hUserShopShowcase,  55, pText,   2, 1);
				pText = GetTxtFromMgr(2191);
				ListViewInsertColumn( m_hUserShopShowcase,  80, pText, 3, 1);
			}

			// ������ ������ �����ش�. 
			cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
			pclitemmanager->SetItemTypeInComboPersonalShop(hDlg, IDC_COMBO_ITEMINFO_TYPE, false);
		

			//---------------------------------
			// INIT CONTROLS		   --------
			//ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
			SendMessage(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_LIMITTEXT, MAX_PERSONAL_SHOP_TEXT_SIZE-1, 0);

			char Tempbuffer[128];
			itoa(MAX_ITEM_PILE_NUMBER, Tempbuffer, 10);
			SendMessage(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT),EM_LIMITTEXT, strlen(Tempbuffer), 0);
			
			itoa(MAX_PRICE_IN_MARKET, Tempbuffer, 10);
			SendMessage(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),EM_LIMITTEXT, strlen(Tempbuffer), 0);
			
			// EditBrush 
			m_hEditBrush = CreateSolidBrush( COLOR_DIALOG_WHITEBLUE);
			//---------------------------------
				
			LoadUserInventory();
			LoadShopShwocase();
			//---------------------------------
			// HTML �� �ʱ�ȭ�Ѵ�.
			//---------------------------------
			//==================================
			hwnd = GetDlgItem(hDlg, IDC_STATIC_SHOP_PROFILE);
			if (hwnd)
			{
				EmbedBrowserObject(hwnd);
			}
			//===============================
			MoveWindow( GetDlgItem( hDlg, IDC_STATIC_SHOP_PROFILE ), 1, 4, 73, 73, TRUE );
		}
		return TRUE;
	case WM_SIZE:
	{
		
		//============================
		// HTML Resize �� �Ѵ�.
		//============================
		//==================================
		hwnd = GetDlgItem(hDlg, IDC_STATIC_SHOP_PROFILE);
		if(hwnd)
		{
			ResizeBrowser(hwnd, LOWORD(lParam), HIWORD(lParam));		
		}
		return(0);
	}
	case WM_CTLCOLORSTATIC:
		{
			if (GetDlgItem( hDlg, IDC_EDIT_ITEM_EXPLAIN ) == (HWND)lParam ||
				GetDlgItem( hDlg, IDC_EDIT_MESSAGE ) == (HWND)lParam )
			{
				HDC hdc = (HDC)wParam;
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITEBLUE);
				return (BOOL)m_hEditBrush;
			}
		}
		break;

	case WM_TIMER:
		{		
			// ���� ���ڶ�� ���� �����Ų��
		/*	if(m_siShopMode == PSHOP_MODE_BUY && m_bShopMoneyCheck == TRUE &&
				pclclient->pclCM->CR[1]->pclCI->GetPersonID() == m_siShopperPersonID )
			{
				SI64 siTotalPrice = 0;
				SI32 i;
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{
					if(m_clShopData.m_clItem[i].siUnique > 0)
						siTotalPrice += (m_clShopData.m_clItem[i].siItemNum * (SI64)m_clShopData.m_siPrice[i]);
				}

				// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
 				SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

				if ( BuyerMoney  < siTotalPrice )
				{
					char* pTitle = GetTxtFromMgr(5118);
					char* pText = GetTxtFromMgr(5119);

					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					StopPersonalShop();
					return FALSE;
				}
			}
		*/
			if ( IsUserInventoryChanged() )
			{
				LoadUserInventory();
			}
			
			if ( IsShopShowCaseChanged() )
			{
				LoadShopShwocase();
			}

			ShowMoneyText();
			//==================================
			// �������� �Ѱ��� �������� �ʾҴµ� ���� �Ҽ� ����.
			//==================================
			// �ڽ��� ������ ���� ������ ��� �������� �ϳ��� ���ٸ� HIDE
			if(m_bSelf == TRUE && m_bShopStarted == FALSE)
			{
				BOOL bHasItem = FALSE;
				for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{
					if ( m_clShopData.m_clItem[ i ].siUnique != 0 )
					{
						bHasItem = TRUE;
						break;
					}
				}
				if(bHasItem == TRUE)	EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	TRUE);
				else					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	FALSE);
			}
			//==================================
			//---------------------------------
			// ���۰����� ������ ����� �����Ѵ�.
			//---------------------------------
			//SetMakeableItemList(IDC_COMBO_MAKEITEM_NAME); ���ž���.

		}
		break;

	case WM_NOTIFY:
		{
			LPNMHDR						hdr;
			LPNMITEMACTIVATE			nia;
			LPNMLVGETINFOTIP			ngt;
			LPNMLISTVIEW				nlv;
			hdr = ( LPNMHDR )			lParam;
			ngt = ( LPNMLVGETINFOTIP )	lParam;
			nlv = ( LPNMLISTVIEW )		lParam;
			nia = (LPNMITEMACTIVATE)	lParam;
			
			if ( hdr->hwndFrom == m_hUserInventory )
			{
				switch( hdr->code )
				{
				case LVN_ITEMCHANGED:
					{
						if(nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
						{
							m_siUserInventorySelectedRealItemIndex = nlv->lParam;
							m_siUserInventorySelectedIndex = nia->iItem;

							SI32 siListViewIndex = 0;
							
							for ( int i = PERSONITEM_INV0; i < PERSONITEM_SUMMON1EQUIP0; ++i )
							{
								if ( m_clUserItem[ i ].siUnique != 0 )
								{
									if ( m_siUserInventorySelectedIndex == siListViewIndex )
									{
										if((m_bSelf == TRUE  && m_siShopMode == PSHOP_MODE_SELL) ||
										   (m_bSelf == FALSE && m_siShopMode == PSHOP_MODE_BUY))
										{
											SetDlgItemInt( hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, m_clUserItem[ i ].GetItemNum(), FALSE );
										}
										break;
									}
									else
									{
										++siListViewIndex;
									}
								}
							}
						}
					}
					break;
				case LVN_GETINFOTIP:
					{
						if ( ngt->iItem >= 0 )
						{
							SI32 siListViewIndex = 0;
							
							for ( int i = PERSONITEM_INV0; i < PERSONITEM_SUMMON1EQUIP0; ++i )
							{
								if ( m_clUserItem[ i ].siUnique != 0 )
								{
									if ( ngt->iItem == siListViewIndex )
									{
										pclClient->pclItemManager->GetExplain( &m_clUserItem[ i ], ngt->pszText );
										break;
									}
									else
									{
										++siListViewIndex;
									}
								}
							}							
						}
					}
					break;
				}
			}
			else if ( hdr->hwndFrom == m_hUserShopShowcase )
			{
				switch( hdr->code )
				{
				case LVN_ITEMCHANGED:
					{
						if(nlv->uChanged == LVIF_STATE && nlv->uNewState == (LVIS_SELECTED | LVIS_FOCUSED))
						{
							m_siShopShowCaseSelectedRealItemIndex = nlv->lParam;
							m_siShopShowCaseSelectedIndex = nia->iItem;
							
							SI32 siListViewIndex = 0;
							
							for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
							{
								if ( m_clShopData.m_clItem[ i ].siUnique != 0 )
								{
									if ( m_siShopShowCaseSelectedIndex == siListViewIndex )
									{
										if((m_bSelf == FALSE  && m_siShopMode == PSHOP_MODE_SELL) ||
										   (m_bSelf == TRUE   && m_siShopMode == PSHOP_MODE_BUY))
										{
											SetDlgItemInt( hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, m_clShopData.m_clItem[ i ].GetItemNum(), FALSE );
										}

										char ItemExplain[ 512 ] = "";
										cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
										if(m_siShopMode == PSHOP_MODE_SELL) // ������ �ȶ��� ��Ȯ�� ������ �����ֳ�.
											pclitemmanager->GetExplain( &m_clShopData.m_clItem[ i ], ItemExplain );
										else								// ������ �춧�� �ش� ��ǰ�� ���.
											pclitemmanager->GetExplain( m_clShopData.m_clItem[ i ].siUnique, ItemExplain );

										SI32 silen = strlen(ItemExplain);
										if( silen > 2 && ItemExplain[silen-1] =='\n') {	ItemExplain[silen-1] = 0;	}
										if( silen > 2 && ItemExplain[silen-2] =='\r') {	ItemExplain[silen-2] = 0;	}
										SetWindowText( GetDlgItem(hDlg, IDC_EDIT_ITEM_EXPLAIN) , ItemExplain );
										break;
									}
									else
									{
										++siListViewIndex;
									}
								}
							}	
						}
						break;
					}
				case LVN_GETINFOTIP:
					{
						if ( ngt->iItem >= 0 )
						{
							SI32 siListViewIndex = 0;
							
							for ( int i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
							{
								if ( m_clShopData.m_clItem[ i ].siUnique != 0 )
								{
									if ( ngt->iItem == siListViewIndex )
									{
										cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;

										if(m_siShopMode == PSHOP_MODE_SELL) // ������ �ȶ��� ��Ȯ�� ������ �����ֳ�.
											pclitemmanager->GetExplain( &m_clShopData.m_clItem[ i ],          ngt->pszText );
										else								// ������ �춧�� �ش� ��ǰ�� ���.
											pclitemmanager->GetExplain( m_clShopData.m_clItem[ i ].siUnique,  ngt->pszText );
										
										break;
									}
									else
									{
										++siListViewIndex;
									}
								}
							}							
						}
					}
					break;
				}
			}
		}
		break;

	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDC_COMBO_ITEMINFO_TYPE:
				{
					switch(HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						{
							char szSelText[128];
							ComboGetString(hDlg, IDC_COMBO_ITEMINFO_TYPE, (LPARAM)szSelText);
							
							SI32 itemtypeunique = pclClient->pclItemManager->FindItemTypeUniqueFromTypeName(szSelText);
							if(itemtypeunique >=0)
							{
								// itemtypeunique�� �ش��ϴ� ������ ����Ʈ�� �����ش�. 
								cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
								pclitemmanager->ShowItemListInCombo(hDlg, IDC_COMBO_ITEMINFO_NAME, itemtypeunique, true);
							}
						}
						break;
					}
				}
				break;
			case IDOK:	
				{
					Hide();	
				}
				break;
			case IDC_RADIO_SHOP_TYPE_SELL:
				{
					if(m_siShopMode!=PSHOP_MODE_SELL)
					{
						m_clShopData.InitData();
						memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
						ShopInit(TRUE, PSHOP_MODE_SELL);
					}
				}
				break;
			case IDC_RADIO_SHOP_TYPE_BUY:
				{
					if(m_siShopMode!=PSHOP_MODE_BUY)
					{
						m_clShopData.InitData();
						memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
						ShopInit(TRUE, PSHOP_MODE_BUY);
					}
				}
				break;
			case IDC_RADIO_SHOP_TYPE_MAKEITEM:
				{
					if(m_siShopMode!=PSHOP_MODE_MAKEITEM)
					{
						m_clShopData.InitData();
						memset(	m_szShopBanner, 0 , sizeof(m_szShopBanner));
						ShopInit(TRUE, PSHOP_MODE_MAKEITEM);
					}
				}
				break;
			
			case IDC_BUTTON_MINIHOME:
				{
					if ( m_siShopperCharUnique > 0 )
					{
						cltGameMsgRequest_Userid clUserid( m_siShopperCharUnique );
						cltMsg clMsg( GAMEMSG_REQUEST_USERID, sizeof( clUserid ), (char*)&clUserid );
						cltClient *pclclient = ( cltClient * )pclClient;
						pclclient->SendMsgToServer((char*)&clMsg);
					}
				}
				break;
			case IDC_BUTTON_REG_BUY_SELL:
				{
					Do_Button_reg_buy_sell();
				}
				break;
			case IDC_BUTTON_ITEM_CANCEL:
				{
					// �ڽ��� ������ �������� �ʾ������� ��Ҹ� �Ҽ� �ִ�.
					if(m_bSelf==TRUE && m_bShopStarted==FALSE)
					{
						if(DropShopItem(m_siShopShowCaseSelectedIndex)==true)
						{
							m_bShopDataChanged = true;
						}
					}
				}
				break;
			case IDC_BUTTON_SHOP_START:
				{
					StartPersonalShop();
				}
				break;
			case IDC_BUTTON_SHOP_STOP:
				{
					StopPersonalShop();
				}
				break;
			}
		}
		break;
		
	case WM_CLOSE:
		{
			Hide();
		}
		break;

	case WM_DESTROY:
		{
	
			if ( m_hEditBrush )
			{
				DeleteObject( m_hEditBrush );
				m_hEditBrush= NULL;
			}

			//---------------------------------
			// HTML �� �����Ѵ�.
			//---------------------------------
			//==================================
			hwnd = GetDlgItem(hDlg, IDC_STATIC_SHOP_PROFILE);
			if(hwnd)
			{
				DoPageAction(hwnd, WEBPAGE_STOP);
				UnEmbedBrowserObject(hwnd);
			}
			//==================================
			
			if(m_bTimer==true) KillTimer( hDlg, 0 );			
			m_bTimer = false;
			m_hDlg = NULL;
		}
		break;
	}

	return FALSE;
}

bool CPersonalShopDlg::IsShow()
{
	return m_bShow;
}

void CPersonalShopDlg::Show( SI32 siCharUnique, SI32 siPersonID, SI16 ShopMode, char *Name, char *AccountID,
							BOOL bShopStarted)
{
	
	if(m_hDlg == NULL)	 return;

	if(m_bShow == false)
		ShowWindow( m_hDlg, SW_SHOWNOACTIVATE );

	m_bShow = true;
	

	if(m_bTimer == false) 
		SetTimer( m_hDlg, 0, PERSONALSHOPDLG_SETTIMER_TIME, NULL );
	m_bTimer = true;

	
	if(AccountID && strlen(AccountID))	strcpy(m_szAccountID, AccountID);
	if(Name&& strlen(Name))				strcpy(m_szCharName,  Name);
	
	m_siShopperCharUnique = siCharUnique;
	m_siShopperPersonID   = siPersonID;
	m_bShopStarted		  = bShopStarted;
	

/*	HWND hwnd = GetDlgItem(m_hDlg, IDC_STATIC_SHOP_PROFILE);
	if(hwnd)
	{
		char ProfileURL[MAX_PATH]; // = "" ;
		pclClient->GetCZProfileUrl( ProfileURL, m_szAccountID);
		DisplayHTMLPage(hwnd, ProfileURL);
	}*/

	//---------------------------------
	// ���۰����� ������ ����� �����Ѵ�.
	//---------------------------------
	SetMakeableItemList(IDC_COMBO_MAKEITEM_NAME);

	// �ڱ��ڽ��ϰ�� 
	BOOL bSelf = (siCharUnique == pclClient->pclCM->CR[1]->GetCharUnique());
	ShopInit(bSelf, ShopMode);
	
	SetForegroundWindow( m_hDlg );
	
	return;
}

void CPersonalShopDlg::ShopInit(BOOL bSelf, SI16 shopmode)
{

	// DialogBox ���� 
	char buffer[256];
	switch(shopmode)
	{
	case PSHOP_MODE_BUY:	
		{
			char* pText = GetTxtFromMgr(2192);
			sprintf(buffer, pText,	  m_szCharName);
		}
		break;	
	case PSHOP_MODE_SELL:
		{
			char* pText = GetTxtFromMgr(2193);
			sprintf(buffer, pText,	  m_szCharName);	
		}
		break;
	case PSHOP_MODE_MAKEITEM:
		{
			char* pText = GetTxtFromMgr(2194);
			sprintf(buffer, pText, m_szCharName);	
		}
		break;
	}
	SetWindowText(m_hDlg, buffer);

	switch(shopmode)
	{
	case PSHOP_MODE_BUY:
		{
			char* pText = GetTxtFromMgr(1678);
			ListViewSetColumn( m_hUserShopShowcase,  80, pText,		1, 1);
		}
		break;	
	case PSHOP_MODE_SELL:
		{
			char* pText = GetTxtFromMgr(1678);
			ListViewSetColumn( m_hUserShopShowcase,  80, pText,		1, 1);
		}
		break;
	case PSHOP_MODE_MAKEITEM:
		{
			char* pText = GetTxtFromMgr(2195);
			ListViewSetColumn( m_hUserShopShowcase,  80, pText, 1, 1);
		}
		break;
	}
		

	m_bSelf		 = bSelf;
	m_siShopMode = shopmode;

	m_clShopData.m_siShopMode = m_siShopMode;

	// ��������� �����.
	cltShopBannerData clShopBanner;
	clShopBanner.SetData(&m_clShopData);
	clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);


	// MESSAGE EDIT�ʱ�ȭ 
	DisplayMessage(TRUE, "");
	SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		"");
	SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),	"");

	// �ڱ��ڽ��� ���� ���� 
	if(bSelf == TRUE)
	{
		switch(shopmode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ ��� ���  	
			{
				ListView_DeleteAllItems( m_hUserShopShowcase );

				//EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),				TRUE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, FALSE, 0);
				
				char* pText = GetTxtFromMgr(2196);
				sprintf(buffer, pText, MAX_SHOP_ITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);

				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),			TRUE);
				
				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_BUY ),       BM_SETCHECK, BST_CHECKED,   0);
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_SELL ),      BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_MAKEITEM),   BM_SETCHECK, BST_UNCHECKED, 0);
								
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_ITEM_TYPE),			TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_ITEM_NAME),			TRUE);
			
				// MAKEITEM HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SKILLPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		FALSE);
				
				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

				
				EnableWindow(GetDlgItem( m_hDlg, IDC_LIST_SHOP_USER_INVENTORY),	TRUE);

				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_UNIT_MONEY),		TRUE);

				//"���Թ�ǰ ���/���"
				pText = GetTxtFromMgr(2197);
				SetWindowText(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2198);
				SetWindowText(GetDlgItem( m_hDlg, IDC_BUTTON_REG_BUY_SELL),			pText);

				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), "");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  "");
				
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),	TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),	FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_REG_BUY_SELL),	FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),		TRUE);
					
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),  FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),  FALSE);

				}
				else
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),	TRUE);
					EnableWindow(GetDlgItem(m_hDlg, IDC_BUTTON_REG_BUY_SELL),	TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),		FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  TRUE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),  TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),  TRUE);
				}
				
				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_TYPE, CB_SETCURSEL,   (WPARAM)-1, 0);
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_NAME, CB_RESETCONTENT, 0, 0);
			}
			
			break;
		case PSHOP_MODE_SELL:	// ���� ������ �Ǵ� ��� 
			{
				ListView_DeleteAllItems( m_hUserShopShowcase );

				//EnableWindow(GetDlgItem( m_hDlg,	IDC_EDIT_EXPLAIN),				TRUE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, FALSE, 0);

				char* pText = GetTxtFromMgr(2199);
				sprintf(buffer, pText, MAX_SHOP_ITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),				TRUE);

				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,	    IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,	    IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);
				
				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_BUY ),      BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),     BM_SETCHECK, BST_CHECKED,   0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),  BM_SETCHECK, BST_UNCHECKED, 0);

				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_TYPE),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_TYPE),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_NAME),			FALSE);

				// MAKEITEM HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SKILLPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		FALSE);

				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

				EnableWindow(GetDlgItem( m_hDlg,	IDC_LIST_SHOP_USER_INVENTORY),	TRUE);

				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_UNIT_MONEY),	TRUE);
	
				pText = GetTxtFromMgr(2197);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2200);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_BUTTON_REG_BUY_SELL),	pText);
				
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), "");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  "");

				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_START),			TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_STOP),			TRUE);
				
				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_REG_BUY_SELL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),			TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);
				}
				else
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),		TRUE);
					EnableWindow(GetDlgItem(m_hDlg, IDC_BUTTON_REG_BUY_SELL),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),			FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  TRUE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);
				}

			}

			break;

		case PSHOP_MODE_MAKEITEM:	// ���� ������ ������ �Ƿ��Ѵ�.
			{
				ListView_DeleteAllItems( m_hUserShopShowcase );

				//EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),				TRUE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, FALSE, 0);
				
				char* pText = GetTxtFromMgr(2201);
				sprintf(buffer, pText, MAX_SHOP_MAKEITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);

				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),			TRUE);
				
				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_SELL ),    BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_BUY ),     BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,  IDC_RADIO_SHOP_TYPE_MAKEITEM), BM_SETCHECK, BST_CHECKED,   0);
								
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_ITEM_TYPE),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_ITEM_NAME),			FALSE);

				// MAKEITEM SHOW
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_MAKEITEM_NAME),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_HANDPOINT),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SKILLPOINT),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

				
				EnableWindow(GetDlgItem( m_hDlg, IDC_LIST_SHOP_USER_INVENTORY),	TRUE);

				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_UNIT_MONEY),		TRUE);

				//"���Թ�ǰ ���/���"
				pText = GetTxtFromMgr(2202);
				SetWindowText(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2203);
				SetWindowText(GetDlgItem( m_hDlg, IDC_BUTTON_REG_BUY_SELL),			pText);

				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), "");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  "");
				
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),	TRUE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),	TRUE);

				// ������ �̹� ������ �Ǿ����� 
				if(m_bShopStarted)
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_REG_BUY_SELL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),			TRUE);
					
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),		FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		FALSE);

				}
				else
				{
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),		TRUE);
					EnableWindow(GetDlgItem(m_hDlg,  IDC_BUTTON_REG_BUY_SELL),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_START),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_BUTTON_SHOP_STOP),			FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT), TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),  TRUE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_SELL),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_TYPE),		FALSE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_ITEMINFO_NAME),		FALSE);

					EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
					EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);
				}
				
				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_TYPE, CB_SETCURSEL,   (WPARAM)-1, 0);
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_NAME, CB_RESETCONTENT, 0, 0);
			}
			
			break;
		}
	}
	else
	{
		switch(shopmode)
		{
		case PSHOP_MODE_BUY:
			{
				//EnableWindow(GetDlgItem( m_hDlg,	IDC_EDIT_EXPLAIN),				FALSE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, TRUE, 0);

	
				char* pText = GetTxtFromMgr(2196);
				sprintf(buffer, pText, MAX_SHOP_ITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);

				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),				FALSE);
				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);
		
				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_BUY ),      BM_SETCHECK, BST_CHECKED,   0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),     BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),  BM_SETCHECK, BST_UNCHECKED, 0);
				
				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_TYPE),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_TYPE),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_NAME),			FALSE);

				// MAKEITEM HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SKILLPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		FALSE);

				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

			
				EnableWindow(GetDlgItem( m_hDlg,	IDC_LIST_SHOP_USER_INVENTORY),	TRUE);
				
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_UNIT_MONEY),	FALSE);

				pText = GetTxtFromMgr(2197);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2205);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_BUTTON_REG_BUY_SELL),		pText);
				
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT),	"");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),	"");
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),		TRUE);

				EnableWindow(GetDlgItem(m_hDlg,     IDC_BUTTON_REG_BUY_SELL),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_START),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_STOP),			FALSE);

				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);
				

				//=========================================
				// COMBO LIST CLEAR
				//=========================================
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_TYPE, CB_SETCURSEL,   (WPARAM)-1, 0);
				SendDlgItemMessage( m_hDlg, IDC_COMBO_ITEMINFO_NAME, CB_RESETCONTENT, 0, 0);
			}
			
			break;
		case PSHOP_MODE_SELL:
			{
				//EnableWindow(GetDlgItem( m_hDlg,	IDC_EDIT_EXPLAIN),				FALSE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, TRUE, 0);

				char* pText = GetTxtFromMgr(2206);

				sprintf(buffer, pText, MAX_SHOP_ITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);
				
				ShowWindow(GetDlgItem( m_hDlg, IDC_BUTTON_ITEM_CANCEL),				FALSE);
				
				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,	    IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_BUY ),      BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),     BM_SETCHECK, BST_CHECKED,   0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),  BM_SETCHECK, BST_UNCHECKED, 0);

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_TYPE),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_TYPE),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_NAME),			FALSE);

				// MAKEITEM HIDE
				ShowWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_STATIC_SHOP_SKILLPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		FALSE);

				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);

				
				EnableWindow(GetDlgItem( m_hDlg,	IDC_LIST_SHOP_USER_INVENTORY),	TRUE);
				
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_UNIT_MONEY),	FALSE);

				pText = GetTxtFromMgr(2197);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2207);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_BUTTON_REG_BUY_SELL),		pText);

				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT),	"");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),	"");
				EnableWindow(GetDlgItem( m_hDlg,   IDC_EDIT_SHOP_SELLBUY_AMOUNT),	TRUE);
				EnableWindow(GetDlgItem( m_hDlg,   IDC_EDIT_SHOP_SELLBUY_PRICE),	TRUE);


				EnableWindow(GetDlgItem(m_hDlg,     IDC_BUTTON_REG_BUY_SELL),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_START),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_STOP),			FALSE);

				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);

			}
	
			break;

		case PSHOP_MODE_MAKEITEM:
			{
				//EnableWindow(GetDlgItem( m_hDlg,	IDC_EDIT_EXPLAIN),				FALSE);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
				//SendMessage( GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),EM_SETREADONLY, TRUE, 0);

				char* pText = GetTxtFromMgr(2201);
				sprintf(buffer, pText, MAX_SHOP_MAKEITEM_NUMBER);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_ITEM_TAG),		buffer);
				
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_ITEM_CANCEL),		FALSE);
				
				// ���� ���� HIDE
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SETTING),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,	    IDC_RADIO_SHOP_TYPE_BUY),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,	    IDC_RADIO_SHOP_TYPE_MAKEITEM),	TRUE);

				// Default Gray
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_BUY ),      BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_SELL ),     BM_SETCHECK, BST_CHECKED,   0);
				SendMessage(GetDlgItem( m_hDlg,		IDC_RADIO_SHOP_TYPE_MAKEITEM),  BM_SETCHECK, BST_UNCHECKED, 0);

				// COMBOBOX�� �ڽ��� BUY�� ���ϴ� �����ϋ��� �Ѵ�.
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_TYPE),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_TYPE),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_ITEMINFO_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_ITEM_NAME),			FALSE);

				// MAKEITEM HIDE
				ShowWindow(GetDlgItem( m_hDlg,		IDC_COMBO_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_MAKEITEM_NAME),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SKILLPOINT),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_HANDPOINT),		FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_SKILLPOINT),		FALSE);

				EnableWindow(GetDlgItem( m_hDlg, IDC_COMBO_MAKEITEM_NAME),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_HANDPOINT),		TRUE);
				EnableWindow(GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT),		TRUE);
				
				EnableWindow(GetDlgItem( m_hDlg,	IDC_LIST_SHOP_USER_INVENTORY),	TRUE);
				
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_EDIT_SHOP_SELLBUY_PRICE),	FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_STATIC_SHOP_UNIT_MONEY),	FALSE);

				pText = GetTxtFromMgr(2202);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_STATIC_SHOP_SELLBUY_PRICE),	pText);
				pText = GetTxtFromMgr(2208);
				SetWindowText(GetDlgItem( m_hDlg,	IDC_BUTTON_REG_BUY_SELL),	  pText);

				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT),	"");
				SetWindowText( GetDlgItem( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE),	"");
				EnableWindow(GetDlgItem( m_hDlg,   IDC_EDIT_SHOP_SELLBUY_AMOUNT),	TRUE);
				EnableWindow(GetDlgItem( m_hDlg,   IDC_EDIT_SHOP_SELLBUY_PRICE),	TRUE);


				EnableWindow(GetDlgItem(m_hDlg,     IDC_BUTTON_REG_BUY_SELL),		TRUE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_START),			FALSE);
				ShowWindow(GetDlgItem( m_hDlg,		IDC_BUTTON_SHOP_STOP),			FALSE);

				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_BUY),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_SELL),		FALSE);
				EnableWindow(GetDlgItem( m_hDlg,	IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);
			}
	
			break;
		}
	}

	//========================================
	// PATCH�� Ǯ����´�.
	//========================================
	//EnableWindow(GetDlgItem( m_hDlg, IDC_RADIO_SHOP_TYPE_MAKEITEM),	FALSE);
	//========================================


}

void CPersonalShopDlg::Hide()
{
	if(m_hDlg == NULL)	 return;

	if(m_bShow==true)	ShowWindow( m_hDlg, SW_HIDE);
	m_bShow = false;

	if(m_bTimer==true) KillTimer( m_hDlg, 0 );			
	m_bTimer = false;
/*
	cltGameMsgRequest_PersonalShopData clinfo(pclClient->pclCM->CR[1]->GetCharUnique(),false);
	cltMsg clMsg(GAMEMSG_REQUEST_PERSONALSHOPDATA, sizeof(clinfo), (char*)&clinfo);

	pclClient->SendMsgToServer((char*)&clMsg);
*/
}



bool CPersonalShopDlg::IsUserInventoryChanged()
{
	for ( int j = PERSONITEM_INV0; j < PERSONITEM_SUMMON1EQUIP0; ++j )
	{
		SI32 size = sizeof(cltItem);

		char* src = (char*)&m_clUserItem[ j ];
		char* dst = (char*)&m_pPersonItemInfo->clItem[ j ];

		for( int i = 0; i < size; ++i )
		{
			if( src[i] != dst[i] )
			{
				return true;
			}
		}
	}

	return false;
}


bool CPersonalShopDlg::IsShopShowCaseChanged()
{
	if(m_bShopDataChanged) return true;

	return false;
}

void CPersonalShopDlg::LoadUserInventory()
{	
	if ( m_hDlg == NULL )	{	return;		}

	m_siUserInventorySelectedIndex = -1;

	for ( int i = PERSONITEM_INV0; i < PERSONITEM_SUMMON1EQUIP0; ++i )
	{
		m_clUserItem[ i ] = m_pPersonItemInfo->clItem[ i ];
	}

	SetInventoryInListView( pclClient->pclItemManager, m_hDlg, IDC_LIST_SHOP_USER_INVENTORY, NULL, m_pPersonItemInfo );
	
	return;
}

void CPersonalShopDlg::LoadShopShwocase()
{
	if ( m_hDlg == NULL )	{	return;		}

	m_siShopShowCaseSelectedIndex = -1;

	int i = 0;
	
	m_bShopDataChanged = false;

	char itemname[128];
	char itembuffer[128];
	ListView_DeleteAllItems( m_hUserShopShowcase );

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_clItem[i].siUnique)
		{
			if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname) == true)
			{
				ListViewInsertItem(m_hUserShopShowcase, -1 , i, 0, itemname,   i);

				 char* pText = GetTxtFromMgr(611);
				g_JYLibFunction.SetNumUnit(m_clShopData.m_siPrice[i], itembuffer, pText);
				ListViewInsertItem(m_hUserShopShowcase, -1 , i, 1, itembuffer, -1);

				pText = GetTxtFromMgr(2209);
				sprintf(itembuffer, pText, m_clShopData.m_clItem[ i ].siItemNum);
				ListViewInsertItem(m_hUserShopShowcase, -1 , i, 2, itembuffer, -1);

				if(m_clShopData.m_siCurrentPrice[i])
				{
					g_JYLibFunction.SetNumUnit(m_clShopData.m_siCurrentPrice[i], itembuffer,"��");
					ListViewInsertItem(m_hUserShopShowcase, -1 , i, 3, itembuffer, -1);
				}
			}
		}
	}
	
	SetWindowText( GetDlgItem(m_hDlg, IDC_EDIT_ITEM_EXPLAIN) , "" );	
	return;
}


void CPersonalShopDlg::Do_Button_reg_buy_sell()
{
	if(m_bSelf)
	{
		switch(m_siShopMode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ �ڵ��� �� �� �ֵ��� ���� 
			{
				if(AddShopBuyItem() == true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		case PSHOP_MODE_SELL:	// ���� ������ �ڵ����� �� �� �ֵ��� ���� 
			{

				// ���� ������ Item�� ������ �����Ѵ�.
				if(AddShopSellItem(m_siUserInventorySelectedRealItemIndex)==true)
				{
					m_bShopDataChanged = true;
				}

			}
		case PSHOP_MODE_MAKEITEM:
			{
				if(AddShopMakeItem() == true)
				{
					m_bShopDataChanged = true;
				}
			}
			break;
		}
	}
	else
	{
		switch(m_siShopMode)
		{
		case PSHOP_MODE_BUY:	// ���� ������ϴ°��� ������ ���� �Ǵ�.
			{
				// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ �� ������ �Ǵ�.
				SellShopItem(m_siUserInventorySelectedRealItemIndex);
			}
			break;
		case PSHOP_MODE_SELL:	// ���� ���� �Ȱ� �ִ� ������ ���.
			{
				BuyShopItem();
			}
			break;
		case PSHOP_MODE_MAKEITEM:
			{
				MakeShopItem();
			}
			break;
		}
	}
	
	
}

bool CPersonalShopDlg::AddShopBuyItem()
{
	char szSelText[128];
	// ��ǰ ��Ͽ��� ������ ������ ���������� ������ showcase�� �����Ѵ�. 
	if(GetWindowText(GetDlgItem(m_hDlg, IDC_COMBO_ITEMINFO_NAME), szSelText, 100))
	{
		SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName(szSelText);
		if(itemunique)
		{
			//----------------------------------------
			// �������� ��Ÿ ������ ǥ���Ѵ� 
			//----------------------------------------
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
			if(ref > 0)
			{
				//DisplayMessage(TRUE,(char*) pclClient->pclItemManager->pclItemInfo[ref]->GetName());
				SI32 i = 0;
				SI32 siAmountSuccess= 0, siPriceSuccess = 0;
				char AmountBuffer[256]="", PriceBuffer[256]="";
				siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer,  128 );
				siPriceSuccess  = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE,  PriceBuffer,  128 );
				
				if(siAmountSuccess <= 0 || siPriceSuccess <= 0 )
				{
					char* pText = GetTxtFromMgr(2210);
					DisplayMessage(FALSE, pText);
					return false;
				}

				SI64 siAmountValue = 0, siPriceValue = 0;
				
				// AMOUNT
				siAmountValue = _atoi64(AmountBuffer);
				if(siAmountValue <=0 )
				{
					char* pText = GetTxtFromMgr(1688);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siAmountValue > MAX_ITEM_PILE_NUMBER)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2211);
					sprintf(buffer, pText, MAX_ITEM_PILE_NUMBER);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// PRICE 
				siPriceValue  = _atoi64(PriceBuffer);
				if(siPriceValue <= 0)
				{
					char* pText = GetTxtFromMgr(2212);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siPriceValue > MAX_PRICE_IN_MARKET)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2213);
					sprintf(buffer, pText, 
						MAX_PRICE_IN_MARKET);
					DisplayMessage(FALSE, buffer);
					return false;
				}
				
				// ���� �������� ������ �߰��Ҽ� ����.
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == itemunique)
					{
						char* pText = GetTxtFromMgr(2214);
						DisplayMessage(FALSE, pText);
						return false;
					}
				}
				
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == 0)
					{
						m_clShopData.m_clItem[i].siUnique		= itemunique;
						m_clShopData.m_clItem[i].siItemNum		= (SI32)siAmountValue;
						m_clShopData.m_siPrice[i]				= (SI32)siPriceValue;
						m_clShopData.m_siSelectedInventoryPos[i]= 0;
						
						char itemname[128];
						if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname) == true)			
						{
							char buffer[512];
							char* pText = GetTxtFromMgr(2215);
							char num[128]= " " ;
							char money[128]= " " ;
							sprintf(num,"%d",(SI32)siAmountValue);
							sprintf(money,"%d",(SI32)siPriceValue);
							Nsprintf(buffer,pText,"item", itemname   ,"num",  num  ,"money", money   ,NULL);

							//sprintf(buffer, pText,
							//				itemname, (SI32)siAmountValue, (SI32)siPriceValue);
							DisplayMessage(TRUE, buffer);
							

							// EDIT�� ��������� ǥ���Ѵ�.
							cltShopBannerData clShopBanner;
							clShopBanner.SetData(&m_clShopData);
							clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
							SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
						}
						
						return true;
					}
				}
				char* pText = GetTxtFromMgr(2216);
				DisplayMessage(FALSE, pText);
				return false;
			}
		}
	}

	DisplayMessage(FALSE, "");
	return false;
}

bool CPersonalShopDlg::AddShopSellItem(SI32 siUserInventoryRealIndex)
{
	if(siUserInventoryRealIndex < PERSONITEM_INV0 ||  siUserInventoryRealIndex >= PERSONITEM_SUMMON1EQUIP0)
		return false;

	SI32 i = 0;
	SI32 siAmountSuccess= 0, siPriceSuccess = 0;
	char AmountBuffer[256], PriceBuffer[256];
	siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer,  128 );
	siPriceSuccess  = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE,  PriceBuffer,  128 );

	if(siAmountSuccess <= 0 || siAmountSuccess <= 0 ) return false;
	SI64 siAmountValue = 0, siPriceValue = 0;
	
	// AMOUNT
	siAmountValue = _atoi64(AmountBuffer);
	if(siAmountValue <=0 )
	{
		char* pText = GetTxtFromMgr(1668);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if(siAmountValue > m_clUserItem[siUserInventoryRealIndex].siItemNum )
	{
		char* pText = GetTxtFromMgr(2217);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if(siAmountValue > MAX_ITEM_PILE_NUMBER)
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2211);
		sprintf(buffer, pText, MAX_ITEM_PILE_NUMBER);
		DisplayMessage(FALSE, buffer);
		return false;
	}

	// PRICE 
	siPriceValue  = _atoi64(PriceBuffer);
	if(siPriceValue <= 0)
	{
		char* pText = GetTxtFromMgr(2212);
		DisplayMessage(FALSE, pText);
		return false;
	}
	if(siPriceValue > MAX_PRICE_IN_MARKET)
	{
		char buffer[256];
		char* pText = GetTxtFromMgr(2213);
		sprintf(buffer, pText, 
			MAX_PRICE_IN_MARKET);
		DisplayMessage(FALSE, buffer);
		return false;
	}


	// ���� �������� ������ �߰��Ҽ� ����.
	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_siSelectedInventoryPos[i] == siUserInventoryRealIndex)
		{
			char* pText = GetTxtFromMgr(2214);
			DisplayMessage(FALSE, pText);
			return false;
		}
	}

	for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_clItem[i].siUnique == 0)
		{
			m_clShopData.m_clItem[ i ].Set(&m_clUserItem[siUserInventoryRealIndex]);

			// �缳�� 
			m_clShopData.m_clItem[ i ].siItemNum		= (SI32)siAmountValue;
			m_clShopData.m_siPrice[ i ]					= (SI32)siPriceValue;
			m_clShopData.m_siSelectedInventoryPos[ i ]	= siUserInventoryRealIndex;

			char itemname[128];
			if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname) == true)			
			{
				char buffer[512];
				char* pText = GetTxtFromMgr(2218);
				char num[128]= " " ;
				char money[128]= " " ;
				sprintf(num,"%d",(SI32)siAmountValue);
				sprintf(money,"%d",(SI32)siPriceValue);
				Nsprintf(buffer,pText,"item", itemname   ,"num",  num  ,"money", money   ,NULL);

//				sprintf(buffer, pText, itemname, (SI32)siAmountValue, (SI32)siPriceValue);

				// EDIT�� ��������� ǥ���Ѵ�.
				cltShopBannerData clShopBanner;
				clShopBanner.SetData(&m_clShopData);
				clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
				SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);

				DisplayMessage(TRUE, buffer);
			}
			
			return true;
		}
	}
	
	char* pText = GetTxtFromMgr(2216);
	DisplayMessage(FALSE, pText);
	return false;
}


bool CPersonalShopDlg::AddShopMakeItem()
{
	char szSelText[128];


	// ���۸�Ͽ��� ������ ������ ���������� ������ showcase�� �����Ѵ�. 
	if(GetWindowText(GetDlgItem(m_hDlg, IDC_COMBO_MAKEITEM_NAME), szSelText, 100))
	{
		char *pTemp1 = strstr(szSelText, "-");	
		char* pText = GetTxtFromMgr(2219);
		char *pTemp2 = strstr(szSelText, pText);	
		if(pTemp1 == NULL || pTemp2 == NULL) return false;

		*pTemp1 = '\0';	pTemp1++;
		*pTemp2 = '\0';

		SI64 siMaxMakeItem = _atoi64(pTemp1);
		if(siMaxMakeItem <= 0)				{ return false;   }

		SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName(szSelText);
		if(itemunique)
		{
			//----------------------------------------
			// �������� ��Ÿ ������ ǥ���Ѵ� 
			//----------------------------------------
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
			if(ref > 0)
			{
				SI32 i = 0;
				SI32 siAmountSuccess= 0, siPriceSuccess = 0;
				SI32 siHandSuccess= 0,   siSkillSuccess = 0;
				char AmountBuffer[256]="", PriceBuffer[256]="";
				char HandBuffer[256]="",   SkillBuffer[256]="";
				siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer, 128 );
				siPriceSuccess  = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE,  PriceBuffer,  128 );
				siHandSuccess   = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_HANDPOINT,		HandBuffer,   128 );
				siSkillSuccess  = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SKILLPOINT,		SkillBuffer,  128 );

			
				if(siAmountSuccess <= 0 || siPriceSuccess <= 0 || siHandSuccess<=0 || siSkillSuccess <=0)
				{
					char* pText = GetTxtFromMgr(2220);
					DisplayMessage(FALSE, pText);
					return false;
				}

				SI64 siAmountValue = 0, siPriceValue = 0;
				SI64 siHandValue = 0,   siSkillValue = 0;
				
				// AMOUNT
				siAmountValue = _atoi64(AmountBuffer);
				if(siAmountValue <=0 )
				{
					char* pText = GetTxtFromMgr(1668);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siAmountValue > siMaxMakeItem )
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2221);
					sprintf(buffer, pText, siMaxMakeItem);
					DisplayMessage(FALSE, buffer);
					return false;
				}
				if(siAmountValue > MAX_ITEM_PILE_NUMBER)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2211);
					sprintf(buffer, pText, MAX_ITEM_PILE_NUMBER);
					DisplayMessage(FALSE, buffer);
					return false;
				}
				
				// PRICE 
				siPriceValue  = _atoi64(PriceBuffer);
				if(siPriceValue < 0)
				{
					char* pText = GetTxtFromMgr(2222);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siPriceValue > MAX_PRICE_IN_MARKET)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2223);
					sprintf(buffer, pText, 
						MAX_PRICE_IN_MARKET);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// ������ 
				siHandValue  = _atoi64(HandBuffer);
				if(siHandValue < 0)
				{
					char* pText = GetTxtFromMgr(2224);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siHandValue > 2000)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2225);
					sprintf(buffer, pText, 
						2000);
					DisplayMessage(FALSE, buffer);
					return false;
				}

				// ��ų���� 
				siSkillValue  = _atoi64(SkillBuffer);
				if(siSkillValue < 0)
				{
					char* pText = GetTxtFromMgr(2226);
					DisplayMessage(FALSE, pText);
					return false;
				}
				if(siSkillValue > MAX_SKILL_LEVEL+30)
				{
					char buffer[256];
					char* pText = GetTxtFromMgr(2227);
					sprintf(buffer, pText, 
						MAX_SKILL_LEVEL+30);
					DisplayMessage(FALSE, buffer);
					return false;
				}
				

				// ���� �������� ������ �߰��Ҽ� ����.
				for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == itemunique)
					{
						char* pText = GetTxtFromMgr(2214);
						DisplayMessage(FALSE, pText);
						return false;
					}
				}
				
				// 1���� �����Ҽ��ֵ��� �Ѵ�.
				for ( i = 0; i < MAX_SHOP_MAKEITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique == 0)
					{
						m_clShopData.m_clItem[i].siUnique		= itemunique;
						m_clShopData.m_clItem[i].siItemNum		= (SI32)siAmountValue;
						m_clShopData.m_siPrice[i]				= (SI32)siPriceValue;
						m_clShopData.m_siSelectedInventoryPos[i]= 0;
						m_clShopData.m_siHandPoint				= siHandValue;
						m_clShopData.m_siSkillLevel				= siSkillValue;

						
						char itemname[128];
						if(m_clShopData.m_clItem[ i ].GetFullName(pclClient->pclItemManager, itemname) == true)			
						{
							char buffer[512];
							char* pText = GetTxtFromMgr(2228);
							char num[128]= " " ;
							char money[128]= " " ;
							char hand[128]= " " ;
							char skill[128]= " " ;

							sprintf(num,"%d", (SI32)siAmountValue);
							sprintf(money,"%d",(SI32)siPriceValue);
							sprintf(hand,"%d",(SI32)siHandValue);
							sprintf(skill,"%d", (SI32)siSkillValue);

							Nsprintf(buffer,pText,"item", itemname   ,"num",  num  ,"money", money   ,"hand", hand   ,"skill",  skill  ,NULL);
							//sprintf(buffer, pText,
							//				itemname, (SI32)siAmountValue, (SI32)siPriceValue,
							//				(SI32)siHandValue, (SI32)siSkillValue
							//				);
							DisplayMessage(TRUE, buffer);
							

							// EDIT�� ��������� ǥ���Ѵ�.
							cltShopBannerData clShopBanner;
							clShopBanner.SetData(&m_clShopData);
							clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
							SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
						}
						
						return true;
					}
				}
				char* pText = GetTxtFromMgr(2216);
				DisplayMessage(FALSE, pText);
				return false;
			}
		}
	}

	DisplayMessage(FALSE, "");
	return false;
}

bool CPersonalShopDlg::DropShopItem(SI32 siShopShowCaseSelectedIndex)
{
	if(siShopShowCaseSelectedIndex<0 || siShopShowCaseSelectedIndex>=MAX_SHOP_ITEM_NUMBER)
	{
		char* pText = GetTxtFromMgr(2229);
		DisplayMessage(FALSE, pText);
		return false;
	}

	m_clShopData.m_clItem[siShopShowCaseSelectedIndex].Init();
	m_clShopData.m_siSelectedInventoryPos[siShopShowCaseSelectedIndex]	= 0;
	m_clShopData.m_siPrice[siShopShowCaseSelectedIndex]					= 0;

	cltShopTradeData	TempShopData;
	memcpy(&TempShopData, &m_clShopData, sizeof(cltShopTradeData));
	memset(&m_clShopData, 0, sizeof( cltShopTradeData ) );		// �޸𸮸� Clear ��Ų��.

	// ������ ���� �����Ѵ�. 
	m_clShopData.m_siShopMode =  TempShopData.m_siShopMode;
	m_clShopData.m_siPersonID =  TempShopData.m_siPersonID; 
	strcpy(m_clShopData.m_szAccountID, TempShopData.m_szAccountID);

	SI32 siIndex = 0;
	for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(TempShopData.m_clItem[i].siUnique>0)
		{
			m_clShopData.m_clItem[siIndex].Set(&TempShopData.m_clItem[i]);
			m_clShopData.m_siSelectedInventoryPos[siIndex]  = TempShopData.m_siSelectedInventoryPos[i]; 
			m_clShopData.m_siPrice[siIndex]					= TempShopData.m_siPrice[i];
			siIndex++;
		}
	}	
	
	// EDIT�� ��������� ǥ���Ѵ�.
	cltShopBannerData clShopBanner;
	clShopBanner.SetData(&m_clShopData);
	clShopBanner.MakeBannerText(pclClient->pclItemManager, m_szShopBanner);
	SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN), m_szShopBanner);
	

	char* pText = GetTxtFromMgr(2230);
	DisplayMessage(TRUE, pText);
	
	return true;
}

bool CPersonalShopDlg::SellShopItem(SI32 siUserInventoryRealIndex)
{
	if(siUserInventoryRealIndex < PERSONITEM_INV0 ||  siUserInventoryRealIndex >= PERSONITEM_SUMMON1EQUIP0)
	{	
		char* pText = GetTxtFromMgr(2231);
		DisplayMessage(FALSE, pText); 
		return false;
	}

	SI32 siFoundShowCaseIndex = -1;
	for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
	{	
		if(m_clShopData.m_clItem[i].siUnique>0)
		{
			if(m_clUserItem[siUserInventoryRealIndex].siUnique == m_clShopData.m_clItem[i].siUnique)
			{
				siFoundShowCaseIndex = i;
				break;
			}
		}
	}

	// ������ �߰��ߴٸ� (���� unique�� �ø��� �����Ƿ� �����ϴ�.)
	if(siFoundShowCaseIndex>= 0 && siFoundShowCaseIndex<MAX_SHOP_ITEM_NUMBER)
	{
		// ������ ���ǰ����� �����ؾ��Ѵ�.
		if(m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum>0 && m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum <= MAX_ITEM_PILE_NUMBER)
		{
			char AmountBuffer[256];
			SI32  siPrice		    = 0;
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;
			siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer,  128 );
			if(siAmountSuccess>0)	siAmountValue = _atoi64(AmountBuffer);
			// �Ǹſ䱸���� ������ ���� ���� �̳�����Ѵ�.
			if(siAmountValue > 0 )
			{
				// ������ ������ Showcase�������� ũ�� �ִ� Showcase������ �����Ѵ�.
				if(siAmountValue >= m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum ) 
					siAmountValue = m_clShopData.m_clItem[ siFoundShowCaseIndex ].siItemNum;

				// ������ ������ �����ؾ��Ѵ�.
				if(m_clShopData.m_siPrice[siFoundShowCaseIndex] > 0 && m_clShopData.m_siPrice[siFoundShowCaseIndex] <= MAX_PRICE_IN_MARKET)
				{
					cltClient *pclclient = ( cltClient * )pclClient;
					cltItem clitem;
					clitem.Set(&m_clShopData.m_clItem[ siFoundShowCaseIndex ]);	// �ٸ� ��� ������ ������ 
					clitem.siItemNum  = (SI32)siAmountValue;					// ������ �ٸ���.
					siPrice			  = m_clShopData.m_siPrice[ siFoundShowCaseIndex ];
					cltGameMsgRequest_SellPersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, siFoundShowCaseIndex, siUserInventoryRealIndex);
					cltMsg clMsg( GAMEMSG_REQUEST_SELLPERSONALSHOP, sizeof(clInfo), (char*)&clInfo );
					pclclient->SendMsgToServer((char*)&clMsg);
					
					DisplayMessage(TRUE, "");
					return true;
				}
				else {
					char* pText = GetTxtFromMgr(2232);
					DisplayMessage(FALSE, pText);  }
			}
			else { 
				char* pText = GetTxtFromMgr(2233);
				DisplayMessage(FALSE, pText);  }
		}
		else { 
			char* pText = GetTxtFromMgr(2234);
			DisplayMessage(FALSE, pText);	}
	}
	else	{  
		char* pText = GetTxtFromMgr(2235);
		DisplayMessage(FALSE, pText);	}
	

	return false;

}

bool CPersonalShopDlg::BuyShopItem()
{
	// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ ������ ���.
	if(m_siShopShowCaseSelectedIndex>= 0 && m_siShopShowCaseSelectedIndex< MAX_SHOP_ITEM_NUMBER)
	{
		if(m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ].siItemNum>0)
		{
			char AmountBuffer[256];
			SI32  siPrice		    = 0;
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;
			siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer,  128 );
			if(siAmountSuccess>0)	siAmountValue = _atoi64(AmountBuffer);
			if(siAmountValue > 0)
			{
				// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
				SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();
				SI64 siTotalPrice = (SI64)m_clShopData.m_siPrice[m_siShopShowCaseSelectedIndex] * siAmountValue ;
				if ( BuyerMoney  >= siTotalPrice )
				{
					cltClient *pclclient = ( cltClient * )pclClient;
					cltItem clitem;
					clitem.Set(&m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ]);	// �ٸ� ��� ������ ������ 
					clitem.siItemNum  = (SI32)siAmountValue;								// ������ �ٸ���.
					siPrice			  = m_clShopData.m_siPrice[ m_siShopShowCaseSelectedIndex ];
					cltGameMsgRequest_BuyPersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, m_siShopShowCaseSelectedIndex);
					cltMsg clMsg( GAMEMSG_REQUEST_BUYPERSONALSHOP, sizeof(clInfo), (char*)&clInfo );
					pclclient->SendMsgToServer((char*)&clMsg);
					
					DisplayMessage(TRUE, "");
					return true;
				}
				else {
					char* pText = GetTxtFromMgr(2236);
					DisplayMessage(FALSE, pText);	}
			}
			else {
				char* pText = GetTxtFromMgr(2237);
				DisplayMessage(FALSE, pText); }
		}
		else { 
			char* pText = GetTxtFromMgr(2238);
			DisplayMessage(FALSE, pText);	}
	}
	else { char* pText = GetTxtFromMgr(2239);
	DisplayMessage(FALSE, pText); }

	return false;
}
bool CPersonalShopDlg::MakeShopItem()
{
	// showcase�� �ִ� ��ǰ�� ���� ���� ������ŭ ������ �����.
	if(m_siShopShowCaseSelectedIndex>= 0 && m_siShopShowCaseSelectedIndex< MAX_SHOP_MAKEITEM_NUMBER)
	{
		if(m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ].siItemNum>0)
		{
			char AmountBuffer[256];
			SI32  siAmountSuccess	= 0;
			SI64  siAmountValue     = 0;
			siAmountSuccess = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_AMOUNT, AmountBuffer,  128 );
			if(siAmountSuccess>0)	siAmountValue = _atoi64(AmountBuffer);
			if(siAmountValue > 0)
			{
				cltClient *pclclient = ( cltClient * )pclClient;
				cltItem clitem;
				clitem.Set(&m_clShopData.m_clItem[ m_siShopShowCaseSelectedIndex ]);	// �ٸ� ��� ������ ������ 
				clitem.siItemNum  = (SI32)siAmountValue;								// ������ �ٸ���.

				SI32  siPrice	    = 0;
				SI32  siHandpoint   = 0;
				SI32  siSkillLevel  = 0;
				siPrice			  = m_clShopData.m_siPrice[ m_siShopShowCaseSelectedIndex ];
				siHandpoint		  = m_clShopData.m_siHandPoint;
				siSkillLevel	  = m_clShopData.m_siSkillLevel;
				cltGameMsgRequest_MakePersonalShop clInfo(m_siShopperCharUnique, m_siShopMode, m_siShopperPersonID, &clitem, siPrice, siHandpoint, siSkillLevel,m_siShopShowCaseSelectedIndex);
				cltMsg clMsg( GAMEMSG_REQUEST_MAKEPERSONALSHOP, sizeof(clInfo), (char*)&clInfo );
				pclclient->SendMsgToServer((char*)&clMsg);
				
				DisplayMessage(TRUE, "");
				return true;
			}
			else { 
				char* pText = GetTxtFromMgr(2240);
				DisplayMessage(FALSE, pText); }
		}
		else { 
			char* pText = GetTxtFromMgr(2241);
			DisplayMessage(FALSE, pText);	}
	}
	else { 
		char* pText = GetTxtFromMgr(2242);
		DisplayMessage(FALSE, pText); }

	return false;
}
void CPersonalShopDlg::DisplayMessage(SI32 siSuccess, char *pBuffer)
{
	if(siSuccess<=0)	pclClient->PushEffect(EFFECT_FAILURE, 0, 0);
	if(pBuffer)		SetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_MESSAGE), pBuffer);
}


void CPersonalShopDlg::StartPersonalShop()
{
	cltClient *pclclient = ( cltClient * )pclClient;

	if(m_siShopMode == PSHOP_MODE_BUY)
	{
		SI64 siTotalPrice = 0;
		SI32 i;
		for ( i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
		{
			if(m_clShopData.m_clItem[i].siUnique > 0)
				siTotalPrice += (m_clShopData.m_clItem[i].siItemNum * (SI64)m_clShopData.m_siPrice[i]);
		}

		// ���� ���� �ִµ��� ������ ������ ���ݰ� ���Ѵ�.
		SI64 BuyerMoney   = (SI64)pclClient->pclCM->CR[1]->pclCI->clIP.GetMoney();

		if ( BuyerMoney  < siTotalPrice )
		{
			char* pTitle = GetTxtFromMgr(5120);
			char* pText = GetTxtFromMgr(5121);


			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;
		}
	}

	SI32 siTicketNum = (m_siShopMode==PSHOP_MODE_MAKEITEM) ? 1: 1;//2: 1;
	// 14040 : ���λ��� �̿�� 
	if ( pclclient->pclCM->CR[1]->pclCI->clCharItem.GetItemNum(14040) >= siTicketNum )
	{
		char buffer[256] = "" ;
		char* pText = GetTxtFromMgr(2243);
		sprintf(buffer, pText, siTicketNum);
		pText = GetTxtFromMgr(2244);
		if (  MessageBox(NULL, buffer, pText, MB_ICONQUESTION | MB_YESNO | MB_TOPMOST) == IDYES )
		{
			char szText[MAX_PERSONAL_SHOP_TEXT_SIZE]="";
			GetWindowText(GetDlgItem( m_hDlg, IDC_EDIT_EXPLAIN),	szText, MAX_PERSONAL_SHOP_TEXT_SIZE);
			
			// ���� �ٲ�� �־ �������ش�.
			m_clShopData.m_siShopMode   = m_siShopMode;
			// ������϶��� üũ�Ѵ�
			if(m_clShopData.m_siShopMode == PSHOP_MODE_BUY)
			{
				cltCharClient* pclChar = (cltCharClient*)pclClient->pclCM->CR[1];
				pclChar->bMyShopStart = TRUE;

				for ( SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i )
				{	
					if(m_clShopData.m_clItem[i].siUnique>0)
					{
						pclChar->clMyShopData.m_clItem[i].Set(&m_clShopData.m_clItem[i]);
						pclChar->clMyShopData.m_siPrice[i] = m_clShopData.m_siPrice[i];
					}
				}	
			}

			cltGameMsgRequest_StartPersonalShop clshopdata( m_siShopperCharUnique,  &m_clShopData);
			cltMsg clMsgDt( GAMEMSG_REQUEST_STARTPERSONALSHOP, sizeof( clshopdata ), (char*)&clshopdata );
			pclclient->SendMsgToServer((char*)&clMsgDt);
			Hide();
		}
	}
	else	
	{
		char buffer[256] = "" ;
		char* pText = GetTxtFromMgr(2245);
		sprintf(buffer, pText, siTicketNum);
		DisplayMessage(FALSE, buffer);
	}
}
void CPersonalShopDlg::StopPersonalShop()
{
//	m_bShopMoneyCheck = FALSE;

	cltGameMsgRequest_StopPersonalShop clshopdata( m_siShopperCharUnique);
	cltMsg clMsg( GAMEMSG_REQUEST_STOPPERSONALSHOP, sizeof( clshopdata ), (char*)&clshopdata );
	cltClient *pclclient = ( cltClient * )pclClient;
	pclclient->SendMsgToServer((char*)&clMsg);
	
	Hide();
}


void CPersonalShopDlg::ShowMoneyText()
{
	SI32 siPriceSuccess = 0;
	char PriceBuffer[256]="";
	siPriceSuccess  = GetDlgItemText( m_hDlg, IDC_EDIT_SHOP_SELLBUY_PRICE,  PriceBuffer,  128 );
	if(siPriceSuccess <= 0)
	{
		SetWindowText( GetDlgItem( m_hDlg, IDC_STATIC_MONEY_TEXT),  "");
	}
	else
	{
		SI64 siPriceValue = 0;
		siPriceValue  = _atoi64(PriceBuffer);
		if(siPriceValue <= 0)
		{
			SetWindowText( GetDlgItem( m_hDlg, IDC_STATIC_MONEY_TEXT),  "");
		}
		else
		{
			char szMoney[128];
			char* pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumTxt(siPriceValue , szMoney,pText);
			SetWindowText( GetDlgItem( m_hDlg, IDC_STATIC_MONEY_TEXT),  szMoney);
		}
	}
}


void CPersonalShopDlg::SetMakeableItemList(SI32 DlgItem)
{
	HWND hCombobox = GetDlgItem(m_hDlg, DlgItem);
	if(hCombobox == NULL) return;

	// �޺� �ڽ��� �����.
	ComboDelete(m_hDlg, DlgItem);

	SI32 m_siMakeableItemNum = 0;
	SI32 *m_pMakeableItemList = NULL;
	SI32 id = 1;
	
	// ������ ������ �����ش�. 
	cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
	if(pclitemmanager->FindMakeableItem(
		NULL, 
		&pclClient->pclCM->CR[id]->pclCI->clCharItem,
		NULL,
		MAX_INVITEM_PER_PERSON,
		&pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_INV0],
		&m_siMakeableItemNum,
		&m_pMakeableItemList,
		true) == true)
	{
		char buffer[256];
		for(SI32 i = 0; i < m_siMakeableItemNum; ++i)
		{
			char* pText = GetTxtFromMgr(2246);
			sprintf(buffer, pText, pclitemmanager->GetName(m_pMakeableItemList[i*2]), m_pMakeableItemList[i*2 + 1]);

			SendMessage( hCombobox, CB_ADDSTRING, 0, (LPARAM)buffer );
		}

	}

	if(m_pMakeableItemList)
	{
		delete []m_pMakeableItemList;
		m_pMakeableItemList = NULL;
	}
}
