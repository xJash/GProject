#include "RightMouseMenu.h"

#include "..\PrivateChatDlg\PrivateChatDlgMgr.h"
#include "..\PrivateTradeDlg\PrivateTradeDlg.h"
#include "..\PartyDlg\PartyDlg.h"
#include "..\ErrorMsgDlg\ErrorMsgDlg.h"
#include "..\NotifyMsgDlg\NotifyMsgDlg.h"

#include "../../Common/Char/CharCommon/Char-Common.h"
#include "../../Common/PrivateTradeOrderMgr/PrivateTradeOrderBaseInfo.h"
#include "Char\CharManager\CharManager.h"

#include "../../CommonLogic/Msg/MsgType-PrivateTrade.h"
#include "../../CommonLogic/Msg/MsgType-Party.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/Msg/MsgType-Quest.h"
#include "../../CommonLogic/Msg/MsgType-PersonalShop.h"

#include "../Client/NInterface/NPartyDlg/NPartyDlg.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

#include "../../Client/client.h"
extern cltCommonLogic* pclClient;

CRightMouseMenu g_RightMouseMenu;

CRightMouseMenu::CRightMouseMenu()
{
	m_hDlg = NULL;
	m_bShow = false;
	m_siUnderMouseID = 0;
	m_siCharUnique = 0;
	m_bPersonalShopSwitch = false ;

	m_hRightMouseMenu = NULL ;
	m_hRightMouseMenu0 = NULL ;
	m_hRightMouseMenu1 = NULL ;
}

CRightMouseMenu::~CRightMouseMenu()
{
	if ( m_hDlg )
	{
		DestroyWindow( m_hDlg );
	}
}

void CRightMouseMenu::Create( HINSTANCE hInst, HWND hWnd )
{
	m_hDlg = ::CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG_RIGHTMOUSE_MENU), hWnd, StaticRightMouseMenuDlgProc );
	Hide();
	m_bShow = false;
	m_bPersonalShopSwitch = false ;

	return;
}

BOOL CALLBACK CRightMouseMenu::StaticRightMouseMenuDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	return g_RightMouseMenu.RightMouseMenuDlgProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CRightMouseMenu::RightMouseMenuDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
	TRACKMOUSEEVENT tme;
	HBITMAP hOldBitmap = NULL;
	cltClient *pclclient = ( cltClient * )pclClient;

	switch ( iMsg )
	{
	case WM_INITDIALOG:
		{
			m_hDlg = hDlg;

			m_hRightMouseMenu0 = (HBITMAP)LoadImage( pclClient->GetInstance(), "Interface/RightMouseMenu/RightMouseMenu0.bmp",IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
			m_hRightMouseMenu1 = (HBITMAP)LoadImage( pclClient->GetInstance(), "Interface/RightMouseMenu/RightMouseMenu1.bmp",IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		}
		return TRUE;

	case WM_NCHITTEST:
		{
			int nHit = DefWindowProc( hDlg, iMsg, wParam, lParam );
			
			if ( nHit == HTCLIENT )
			{
				POINT point;
				point.x = LOWORD( lParam );
				point.y = HIWORD( lParam );

				ScreenToClient( hDlg, &point );

				SI32 buttonnumber ;
				if ( m_bPersonalShopSwitch )
					buttonnumber = MENU_BUTTON_NUM + 1 ;
				else buttonnumber = MENU_BUTTON_NUM ;

				if ( point.y < 6 + MENU_BUTTON_HEIGHT )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( point.y < 6 + MENU_BUTTON_HEIGHT * 2 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 2,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( point.y < 6 + MENU_BUTTON_HEIGHT * 3 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 3,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( point.y < 6 + MENU_BUTTON_HEIGHT * 4 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 4,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( point.y < 6 + MENU_BUTTON_HEIGHT * 5 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 5,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( point.y < 6 + MENU_BUTTON_HEIGHT * 6 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 6,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
				else if ( m_bPersonalShopSwitch &&
					point.y < 6 + MENU_BUTTON_HEIGHT * 7 )
				{
					HDC hDC = GetDC( hDlg );
					HDC mdc;
					mdc = CreateCompatibleDC( hDC );
					
					hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
					BitBlt( 
						hDC,         // destination DC 
						0, // x upper left 
						0,  // y upper left 
						MENU_BUTTON_WIDTH,
						19 + MENU_BUTTON_HEIGHT * buttonnumber ,
						mdc,    // source device context 
						MENU_BUTTON_WIDTH * 7,
						0,      // x and y upper left 								
						SRCCOPY);  // raster operation
					
					SelectObject( mdc, hOldBitmap );
					DeleteDC( mdc ); 
					ReleaseDC( hDlg, hDC );
				}
			}		
		}
		break;
		
	case WM_PAINT:
		{
			HDC hDC = GetDC( hDlg );
			HDC mdc;
			mdc = CreateCompatibleDC( hDC );

			SI32 buttonnumber ;
			if ( m_bPersonalShopSwitch )
				buttonnumber = MENU_BUTTON_NUM + 1 ;
			else buttonnumber = MENU_BUTTON_NUM ;

			hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
			BitBlt(
				hDC,         // destination DC 
				0, // x upper left 
				0,  // y upper left 
				MENU_BUTTON_WIDTH,
				19 + MENU_BUTTON_HEIGHT * buttonnumber ,
				mdc,    // source device context 
				0,
				0,      // x and y upper left 								
				SRCCOPY);  // raster operation

			SelectObject( mdc, hOldBitmap );
			DeleteDC( mdc ); 
			ReleaseDC( hDlg, hDC );
		}
		break;
	case WM_MOUSELEAVE:
		{
			HDC hDC = GetDC( hDlg );
			HDC mdc;
			mdc = CreateCompatibleDC( hDC );

			SI32 buttonnumber ;
			if ( m_bPersonalShopSwitch )
				buttonnumber = MENU_BUTTON_NUM + 1 ;
			else buttonnumber = MENU_BUTTON_NUM ;

			hOldBitmap = (HBITMAP)SelectObject( mdc, m_hRightMouseMenu );
			BitBlt(
				hDC,         // destination DC 
				0, // x upper left 
				0,  // y upper left 
				MENU_BUTTON_WIDTH,
				19 + MENU_BUTTON_HEIGHT * buttonnumber ,
				mdc,    // source device context 
				0,
				0,      // x and y upper left 								
				SRCCOPY);  // raster operation

			SelectObject( mdc, hOldBitmap );
			DeleteDC( mdc ); 
			ReleaseDC( hDlg, hDC );
		}
		break;
		
	case WM_MOUSEMOVE:
		{
			tme.cbSize = sizeof( TRACKMOUSEEVENT );
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hDlg;
			tme.dwHoverTime = 500;
			_TrackMouseEvent( &tme );
		}
		break;
	
	case WM_LBUTTONUP:
		{
			SI32 siYPos = HIWORD( lParam );
			
			if ( siYPos < 6 + MENU_BUTTON_HEIGHT )
			{				
				// ĳ���� �迭�� ��ġ��, ĳ���� ����ũ ���� ��ġ�Ұ�쿡�� �� ������ ���õǾ��ٰ� ���� ���� ( �ƴ� ���� ����. �޴��� ����� �����ð� ������ٰ� �����ϸ�, �쿬�� ���� �迭�� ���� unique ��ȣ�� �����Ҽ� �����Ƿ�... )
				if( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
				{
					// �ӼӸ�â ȣ��
					cltClient *pclclient = (cltClient *)pclClient;
					//pclclient->pclPrivateChatDlgMgr->Push(pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique(), (char*)pclClient->pclCM->CR[m_siUnderMouseID]->GetName(), "");
					pclclient->RequestSecretChatByCharUnique(pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique());
				}
			}
			else if ( siYPos < 6 + MENU_BUTTON_HEIGHT * 2 )
			{
				if ( ! pclClient->pclCM->IsValidID(m_siUnderMouseID) )
				{
					Hide();
				}
				else if ( m_siCharUnique < 1 )
				{
					Hide();
				}
				else if ( pclClient->pclCM->CR[m_siUnderMouseID]->pclCI->clIP.GetLevel() < 3 || pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < 3 )
				{
					char* pTitle = GetTxtFromMgr(2037);
					char* pText = GetTxtFromMgr(2361);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					Hide();
				}
				// ĳ���� �迭�� ��ġ��, ĳ���� ����ũ ���� ��ġ�Ұ�쿡�� �� ������ ���õǾ��ٰ� ���� ���� ( �ƴ� ���� ����. �޴��� ����� �����ð� ������ٰ� �����ϸ�, �쿬�� ���� �迭�� ���� unique ��ȣ�� �����Ҽ� �����Ƿ�... )
				else if( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
				{
					// �ŷ�â�� �������ؼ� �ŷ��ϱ� ������ ������ ��û�� ��.
					SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
					cltGameMsgRequest_PrivateTrade clPrivateTrade( siCharUnique, PRIVATETRADE_TRADE_MODE );
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE,
						sizeof(clPrivateTrade), (char*)&clPrivateTrade);

					cltClient *pclclient = ( cltClient * )pclClient;
					pclclient->SendMsgToServer((char*)&clMsg);
				}
			}
			else if ( siYPos < 6 + MENU_BUTTON_HEIGHT * 3 )
			{				
				// �̴� Ȩ������ ���� ��û
				if( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
				{
					SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
					cltGameMsgRequest_Userid clUserid( siCharUnique );
					cltMsg clMsg( GAMEMSG_REQUEST_USERID, sizeof( clUserid ), (char*)&clUserid );
					cltClient *pclclient = ( cltClient * )pclClient;
					pclclient->SendMsgToServer((char*)&clMsg);
					
					//-----------------------------------------------------------
					// ���� ���� ����Ʈ�� �������̾��ٸ�, 
					// ���� ������ ����Ʈ�� �Ϸ�Ǿ����� �˷��ش�.
					//-----------------------------------------------------------
					SI16 questtype, questunique, para1, para2;
					SI16 questclearcond =  QUEST_CLEAR_COND_OTHERMINIHOME;
					if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true)
					{
						cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
						cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (char*)&clinfo);
						pclclient->SendMsgToServer((char*)&clMsg);
					}
					
				}			
			}
			else if ( siYPos < 6 + MENU_BUTTON_HEIGHT * 4 )
			{	
				// ��Ƽ �ʴ� ( ��Ƽ������ �׸��� ��Ƽ������ üũ )
				if ( g_PartyDlg.IsPartyStatus() )
				{
					if ( g_PartyDlg.IsPartyLeader() )
					{
						if ( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
						{
							SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
								cltGameMsgRequest_Party_Invite clPartyInvite( siCharUnique, g_PartyDlg.GetPartyIndex() );
							cltMsg clMsg( GAMEMSG_REQUEST_PARTY_INVITE, sizeof( clPartyInvite ), (char*)&clPartyInvite );
							cltClient *pclclient = ( cltClient * )pclClient;
							pclclient->SendMsgToServer((char*)&clMsg);
						}
					}
				}
				else		// ��Ƽ ���� �ƴ϶�� ��Ƽ ������ �ʴ븦 ���ÿ� �ؾ� ��.
				{
					if ( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
					{
						SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
						cltGameMsgRequest_Party_CreateInvite clPartyCreateInvite( siCharUnique );
						cltMsg clMsg( GAMEMSG_REQUEST_PARTY_CREATEINVITE, sizeof( clPartyCreateInvite ), (char*)&clPartyCreateInvite );
						cltClient *pclclient = ( cltClient * )pclClient;
						pclclient->SendMsgToServer((char*)&clMsg);
					}
				}
/*			// ��Ƽ �ʴ� ( ��Ƽ������ �׸��� ��Ƽ������ üũ )
				if ( g_PartyDlg.IsPartyStatus() )
				{
					if ( g_PartyDlg.IsPartyLeader() )
					{
						if ( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
						{
							SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
							
							cltGameMsgRequest_Party_Invite clPartyInvite( siCharUnique, g_PartyDlg.GetPartyIndex() );
							cltMsg clMsg( GAMEMSG_REQUEST_PARTY_INVITE, sizeof( clPartyInvite ), (char*)&clPartyInvite );
							cltClient *pclclient = ( cltClient * )pclClient;
							pclclient->SendMsgToServer((char*)&clMsg);
						}
					}
				}
				else		// ��Ƽ ���� �ƴ϶�� ��Ƽ ������ �ʴ븦 ���ÿ� �ؾ� ��.
				{
					if ( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
					{
						SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
						cltGameMsgRequest_Party_CreateInvite clPartyCreateInvite( siCharUnique );
						cltMsg clMsg( GAMEMSG_REQUEST_PARTY_CREATEINVITE, sizeof( clPartyCreateInvite ), (char*)&clPartyCreateInvite );
						cltClient *pclclient = ( cltClient * )pclClient;
						pclclient->SendMsgToServer((char*)&clMsg);
					}
				}*/
			}
			else if ( siYPos < 6 + MENU_BUTTON_HEIGHT * 5 )
			{
				// ���� ��û
				if ( ! pclClient->pclCM->IsValidID(m_siUnderMouseID) )
				{
					Hide();
				}
				else if ( m_siCharUnique < 1 )
				{
					Hide();
				}
				else if ( pclClient->pclCM->CR[m_siUnderMouseID]->pclCI->clIP.GetLevel() < 3 || pclClient->pclCM->CR[1]->pclCI->clIP.GetLevel() < 3 )
				{
					char* pTitle = GetTxtFromMgr(2037);
					char* pText = GetTxtFromMgr(2361);
					pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					Hide();
				}
				// ĳ���� �迭�� ��ġ��, ĳ���� ����ũ ���� ��ġ�Ұ�쿡�� �� ������ ���õǾ��ٰ� ���� ���� ( �ƴ� ���� ����. �޴��� ����� �����ð� ������ٰ� �����ϸ�, �쿬�� ���� �迭�� ���� unique ��ȣ�� �����Ҽ� �����Ƿ�... )
				else if( pclClient->pclCM->IsValidID(m_siUnderMouseID) && m_siCharUnique == pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique() )
				{
					// �ŷ�â�� �������ؼ� �ŷ��ϱ� ������ ������ ��û�� ��.
					SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
					cltGameMsgRequest_PrivateTrade clPrivateTrade( siCharUnique, PRIVATETRADE_REPAIR_MODE );
					cltMsg clMsg(GAMEMSG_REQUEST_PRIVATETRADE,
						sizeof(clPrivateTrade), (char*)&clPrivateTrade);

					cltClient *pclclient = ( cltClient * )pclClient;
					pclclient->SendMsgToServer((char*)&clMsg);
				}
			}
			else if ( siYPos < 6 + MENU_BUTTON_HEIGHT * 6 )
			{
				SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
				cltGameMsgRequest_PersonPrivateInfo clinfo(siCharUnique);
				cltMsg clMsg(GAMEMSG_REQUEST_PERSONPRIVATEINFO, sizeof(clinfo), (char*)&clinfo);
				pclClient->SendMsgToServer((char*)&clMsg);
			}
			else if ( m_bPersonalShopSwitch && siYPos < 7 + MENU_BUTTON_HEIGHT * 7 )
			{
				SI32 siCharUnique = pclClient->pclCM->CR[m_siUnderMouseID]->GetCharUnique();
				cltGameMsgRequest_PersonalShopData	clinfo(siCharUnique);
				cltMsg clMsg(GAMEMSG_REQUEST_PERSONALSHOPDATA, sizeof(clinfo), (char*)&clinfo);
				pclClient->SendMsgToServer((char*)&clMsg);

			}

			Hide();
		}
		break;

	case WM_KILLFOCUS:
		{
			Hide();
		}
		break;

	case WM_DESTROY:
		{
			if ( m_hRightMouseMenu1 )
			{
				DeleteObject( m_hRightMouseMenu1 );
				m_hRightMouseMenu1 = NULL;
			}
			if ( m_hRightMouseMenu0 )
			{
				DeleteObject( m_hRightMouseMenu0 );
				m_hRightMouseMenu0 = NULL;
			}

			m_hDlg = NULL;
		}
		break;
	}

	return FALSE;
}

bool CRightMouseMenu::IsShow()
{
	return m_bShow;
}

void CRightMouseMenu::Show( SI32 siUnderMouseID, SI32 siCharUnique, SI32 siMouseXPos, SI32 siMouseYPos ,bool bPersonalShop)
{
	m_siCharUnique = siCharUnique;
	m_siUnderMouseID = siUnderMouseID;
	SetWindowPos( m_hDlg, HWND_TOP, siMouseXPos, siMouseYPos, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW );
	
	m_bShow = true;
	m_bPersonalShopSwitch = bPersonalShop ;
	SI32 buttonnumber ;

	if ( m_bPersonalShopSwitch )
	{
		buttonnumber = MENU_BUTTON_NUM+1 ;
		m_hRightMouseMenu = m_hRightMouseMenu1 ;
		MoveWindow(m_hDlg,siMouseXPos,siMouseYPos,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT*buttonnumber,true);
		HRGN hWndRgn = g_JYLibFunction.DIBToRgn(m_hRightMouseMenu,RGB(240,0,255),false);
		MoveWindow(m_hDlg,siMouseXPos,siMouseYPos,MENU_BUTTON_WIDTH , 19 + MENU_BUTTON_HEIGHT * buttonnumber ,true);
		SetWindowRgn(m_hDlg,hWndRgn,TRUE);
	}
	else
	{
		buttonnumber = MENU_BUTTON_NUM ;
		m_hRightMouseMenu = m_hRightMouseMenu0 ;
		HRGN hWndRgn = g_JYLibFunction.DIBToRgn(m_hRightMouseMenu,RGB(240,0,255),false);
		MoveWindow(m_hDlg,siMouseXPos,siMouseYPos,MENU_BUTTON_WIDTH , 19 + MENU_BUTTON_HEIGHT * buttonnumber ,true);
		SetWindowRgn(m_hDlg,hWndRgn,TRUE);
	}
}

void CRightMouseMenu::Hide()
{
	ShowWindow( m_hDlg, SW_HIDE );

	m_bShow = false;
}