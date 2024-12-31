#include "UserInventoryDlg.h"
#include "ItemInventory.h"

#include "ItemInventoryBuffer.h"
#include "..\..\CommonLogic\CommonLogic.h"
//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "..\Common\CommonHeader.h"
#include "Char\CharManager\CharManager.h"

#include "..\Client\Client.h"
extern cltCommonLogic* pclClient;

CUserInventoryDlg::CUserInventoryDlg()
{
	m_siSelectedIndex = -1;
	m_siUpgradeSelectedIndex = -1;
	m_siRingflag=false;
	m_bShow = false;
	m_hDlg = NULL;
}

CUserInventoryDlg::~CUserInventoryDlg()
{
	m_siRingflag = false;
	/*
	if( m_hDlg )
	{
		DestroyWindow( m_hDlg );
		m_hDlg = NULL;
	}
	*/
}

void CUserInventoryDlg::Create( HWND hWnd, HINSTANCE hInst, cltPItemInfo *pPersonItemInfo, CItemInventoryBuffer *pBuffer, HWND hParentDlg )
{
	m_pBuffer = pBuffer;
	m_pPersonItemInfo = pPersonItemInfo;

	m_hParentDlg = hParentDlg;
	m_hDlg = CreateDialog( hInst, MAKEINTRESOURCE(IDD_DIALOG_USER_INVENTORY ), hWnd, StaticUserInventoryDlgProc );	

	Hide();

	return;
}

void CUserInventoryDlg::Initialize()
{
}

void CUserInventoryDlg::Destroy()
{
}

BOOL CALLBACK CUserInventoryDlg::StaticUserInventoryDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient *pclclient = ( cltClient *)pclClient;
	return pclclient->m_pItemInventoryDlg->m_pUserInventoryDlg->UserInventoryDlgProc( hDlg, iMsg, wParam, lParam );
}

LVBKIMAGE lv1;		// �� ���� ��� ��� �־�� �ǳ�... ������ ����Ʈ�� ��浵 �������Ѱ�... �Ѥ�
BOOL CALLBACK CUserInventoryDlg::UserInventoryDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch( iMsg )
	{
	case WM_INITDIALOG:
		{
			m_hDlg = hDlg;
			m_siRingflag=false;

			m_hUserInventory = GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY );
			
			g_FontManager.SetFont( hDlg, IDC_LIST_USER_INVENTORY, 12 );
			ListView_SetExtendedListViewStyle( m_hUserInventory, LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_INFOTIP );
						
			char strInventoryImagePath[ _MAX_PATH ];
			char strDirectoryPath[ _MAX_PATH ];

			memset( strInventoryImagePath, 0, _MAX_PATH );
			strcpy ( strInventoryImagePath, "file://");			
			memset( strDirectoryPath, 0, _MAX_PATH );
			GetCurrentDirectory( _MAX_PATH, strDirectoryPath );			
			strcat( strInventoryImagePath, strDirectoryPath );
			strcat( strInventoryImagePath, "\\Interface\\Inventory\\Inventory1.bmp");
			lv1.ulFlags = LVBKIF_SOURCE_URL | LVBKIF_STYLE_NORMAL;			
			lv1.pszImage = strInventoryImagePath;
			::SendMessage(m_hUserInventory, LVM_SETBKIMAGE, 0, (LPARAM)&lv1);
			SendMessage( m_hUserInventory, LVM_SETTEXTBKCOLOR, 0, 0xffffffff );

			cltClient *pclclient = (cltClient *)pclClient;
			pclclient->pclImageList->ConnectToListView( GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ), LVSIL_NORMAL );

			// Show �Ҷ� SetTimer ���� �ʰ�, ���⼭ �ϴ� ������ ����Ű ��� ����.
			// ����Ű�� �κ��丮 â�� ���� ���� ���¿����� �� �� �������� ... �׶� ����Ҽ� �ֵ��� �ϱ� ���ؼ���.
			SetTimer( m_hDlg, 0, INVENTORY_SETTIMER_VALUE, NULL );
		}
		return TRUE;

	case WM_TIMER:				// ���������� �� �κ��丮 �����۵��� �ٲ������ Ȯ���ؾ� �ϹǷ�...
		{
			if ( IsInventoryChanged() )
			{
				LoadInventoryData();
			}
		}
		return TRUE;

	case WM_MOUSEMOVE:
		{
			if ( m_siSelectedIndex > -1 )
			{
				POINT pt;
				GetCursorPos( &pt );
				ImageList_DragMove( pt.x, pt.y );

				return TRUE;
			}
		}
		break;
	
		/*
	case WM_LBUTTONDBLCLK:
		{
			m_siSelectedIndex = 0;
		}
		break;
		
*/

	case WM_LBUTTONDOWN:
		{
		
			if ( m_siSelectedIndex > -1 )
			{
				MouseReleaseOperation();
			}
	
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
						

			if ( hdr->hwndFrom == GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ) )
			{
				switch( hdr->code )
				{
				case NM_CLICK:
					{
						if ( nia->iItem >= 0 )
						{
							m_siSelectedIndex = nia->iItem + PERSONITEM_INV0;
							InventorySelect( m_siSelectedIndex, hDlg );
						}
					}
					break;
				case NM_RCLICK:
					{
						if ( nia->iItem >= 0 )
						{
							m_siSelectedIndex = nia->iItem + PERSONITEM_INV0;

							if ( m_clItem[ m_siSelectedIndex ].CanRepair(pclClient->pclItemManager ) )
							{
								RepairItem( m_siSelectedIndex );
							}
							else
							{
								UseItem( m_siSelectedIndex );
							}
						}
					}
					break;
				case LVN_GETINFOTIP:
					{
						if ( ngt->iItem >= 0 )
						{
							pclClient->pclItemManager->GetExplain( &m_clItem[ ngt->iItem + PERSONITEM_INV0 ], ngt->pszText );
						}
					}
					break;

				case NM_RELEASEDCAPTURE:
					{
						if ( m_siSelectedIndex > -1 || m_siUpgradeSelectedIndex > -1 )
						{
							ImageList_DragLeave( NULL );
							ImageList_EndDrag();
							ReleaseCapture();
						}
					}
					break;
				}				
			}
		}
		break;

	case WM_DESTROY:
		{
			KillTimer( m_hDlg, 0 );

			Hide();

			/*
			if ( m_hDlg )
			{
				DestroyWindow( m_hDlg );
				m_hDlg = NULL;
			}
			*/
		}
		break;
	}

	return FALSE;
}

bool CUserInventoryDlg::IsShow()
{
	return m_bShow;
}

void CUserInventoryDlg::Show()
{
	if ( m_bShow )
	{
		return;
	}

	m_bShow = true;

	LoadInventoryData();
	
	ShowWindow( m_hDlg, SW_SHOW );

	

	return;
}

void CUserInventoryDlg::Hide()
{
	if ( ! m_bShow )
	{
		return;
	}

	m_bShow = false;

	ShowWindow( m_hDlg, SW_HIDE );

	return;
}

void CUserInventoryDlg::LoadInventoryData()
{
	if ( m_siSelectedIndex > -1 || m_siUpgradeSelectedIndex > -1 )
	{
		ImageList_DragLeave( NULL );
		ImageList_EndDrag();
		ReleaseCapture();
	}	

	m_siSelectedIndex = -1;
	m_siUpgradeSelectedIndex = -1;

	for ( SI32 i = PERSONITEM_INV0; i < MAX_ITEM_PER_PERSON; ++i )		// ����â�� üũ�� �ʿ� �����Ƿ�, 10 ���� ��.
	{
		m_clItem[ i ] = m_pPersonItemInfo->clItem[ i ];
	}

	SetInventoryInListView1( pclClient->pclItemManager, m_hDlg, IDC_LIST_USER_INVENTORY, NULL, m_pPersonItemInfo );
	
	return;
}

bool CUserInventoryDlg::IsInventoryChanged()
{
	for ( int j = PERSONITEM_INV0; j < MAX_ITEM_PER_PERSON; ++j )		// ����â�� üũ�� �ʿ� �����Ƿ�, 10 ���� ��.
	{
		SI32 size = sizeof(cltItem);

		char* src = (char*)&m_clItem[ j ];
		char* dst = (char*)&m_pPersonItemInfo->clItem[ j];

		for(int i = 0;i < size; i++)
		{
			if(src[i] != dst[i])
			{
				return true;
			}
		}
	}
	return false;
}

void CUserInventoryDlg::MouseReleaseOperation()
{
	if ( m_siSelectedIndex > -1 )
	{
		MoveInventoryItem( m_hDlg );

		ImageList_DragLeave( NULL );
		ImageList_EndDrag();
		ReleaseCapture();

		m_siSelectedIndex = -1;
		m_siUpgradeSelectedIndex = -1;
	}

	return;
}

void CUserInventoryDlg::ChangeItem( HWND hDlg, SI32 siDestination )
{
	SI32 siMoveInfo = MAKELONG( m_siSelectedIndex, siDestination );

	if ( m_clItem[ siDestination ].siUnique != 0 )
	{
		if ( m_clItem[ siDestination ].CanPile( pclClient->pclItemManager ) == false )
		{
			return;
		}
	}


	pclClient->pclItemManager->PlaySound(m_clItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );	
	m_pBuffer->Push( (SI16)INV_CHANGE_ITEM, siMoveInfo, &m_clItem[ m_siSelectedIndex ] );

	return;
	

}

void CUserInventoryDlg::MoveItem( HWND hDlg, SI32 siDestination )
{
	/*
	if ( m_pPersonItemInfo->clItem[ siDestination ].siUnique != 0 )
	{
		m_siSelectedIndex = -1;
		return;
	}
	*/

	SI32 siMoveInfo = MAKELONG( m_siSelectedIndex, siDestination );

	if ( m_clItem[ siDestination ].siUnique != 0 )
	{
		if ( m_clItem[ siDestination ].CanPile( pclClient->pclItemManager ) == false )
		{
			return;
		}
	}


	pclClient->pclItemManager->PlaySound(m_clItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
	
	m_pBuffer->Push( (SI16)INV_MOVE_ITEM, siMoveInfo, &m_clItem[ m_siSelectedIndex ] );

	return;
}

/*
void CUserInventoryDlg::MoveInventoryItem( HWND hDlg )
{
	POINT pt;
	GetCursorPos( &pt );

	HWND hFindWnd = WindowFromPoint( pt );
	
	SI16 StartPos = 0;
	cltClient *pclclient = (cltClient *)pclClient;
	if ( pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex() != -1 )
	{
		StartPos = PERSONITEM_SUMMON1EQUIP0 + MAX_SHAPE_ITEM * pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex();
	}

	if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_HELMET ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_HELMET + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_HELMET + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_HELMET + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_HELMET + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_ARMOR ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_ARMOUR + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_ARMOUR + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_ARMOUR + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_ARMOUR + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WEAPON1 ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_WEAPON1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON1 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_WEAPON1 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_WEAPON1 + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WEAPON2 ) )
	{

		// JAYCEE WEAPON2

		if ( m_pPersonItemInfo->clItem[ PERSONITEM_WEAPON2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON2 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_WEAPON2 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_WEAPON2 + StartPos );
		}

	}	
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_NECKWEAR ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_NECK + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_NECK + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_NECK + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_NECK + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_RING1 ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_RING1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING1 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_RING1 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_RING1 + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_RING2 ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_RING2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING2 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_RING2 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_RING2 + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WAISTBAND ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_BELT + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_BELT + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_BELT + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_BELT + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_SHOE ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_SHOES + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_SHOES + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_SHOES + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_SHOES + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MANTLE ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_MANTLE + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_MANTLE + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_MANTLE + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_MANTLE + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_BAG ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_BAG + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_BAG + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_BAG + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_BAG + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_HAT ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_HAT + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_HAT + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_HAT + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_HAT + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_DRESS ) )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_DRESS + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_DRESS + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_DRESS + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_DRESS + StartPos );
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MOVEITEM_HORSE ) )
	{
		if ( pclClient->pclCM->CR[1]->HaveHorse() )
		{
			SI16 pos;
			cltItem cltoitem;
			SI32 rtnvalue;

			if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_HORSE, 
				&m_clItem[ m_siSelectedIndex ],
				NULL, 
				&pos, 
				&cltoitem,
				&rtnvalue) == true)
			{
				MoveItem( m_hDlg, pos );
			}
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MOVEITEM_BAG ) )
	{
		if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0  )
		{
			SI16 pos;
			cltItem cltoitem;
			SI32 rtnvalue;

			if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG, 
				&m_clItem[ m_siSelectedIndex ],
				NULL, 
				&pos, 
				&cltoitem,
				&rtnvalue) == true)
			{
				MoveItem( m_hDlg, pos );
			}
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hDlg, IDC_LIST_USER_INVENTORY ) )
	{
		// ����Ʈ�信�� ����Ʈ��� �ű涧�� ���� ���׷��̵��Ҷ���...
		if ( m_siSelectedIndex >= PERSONITEM_INV0 )
		{
			ScreenToClient( GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ), &pt );

			LVHITTESTINFO HitTestInfo;
			HitTestInfo.pt = pt;
			HitTestInfo.flags = LVHT_ONITEMICON | LVHT_NOWHERE;
			int temp =  ListView_HitTest( GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ), &HitTestInfo );

			if ( temp != -1 )
			{
				if ( temp + PERSONITEM_INV0 != m_siSelectedIndex )
				{
					m_siUpgradeSelectedIndex = temp + PERSONITEM_INV0;

					if ( m_clItem[ m_siSelectedIndex ].GetType( pclClient->pclItemManager ) == ITEMTYPE_SCROLL &&  m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ].siUnique != 0 )
					{
						m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
					}
					else
					{
						MoveItem( hDlg, m_siUpgradeSelectedIndex );
					}
				}
			}

			return;
		}
	}
	else if ( hFindWnd == pclClient->GetHwnd() )
	{
		if ( m_siSelectedIndex >= PERSONITEM_INV0 )		// ����Ʈ�信 �ִ� �͸� �ٴڿ� ���� �� �����Ƿ�...
		{
			DropItem( m_siSelectedIndex );
			return;
		}
	}
	
	return;
}
*/



SI32 CUserInventoryDlg::GetInventoryType(SI32 siItemType)
{
	SI32 StartPos =0;
	cltClient *pclclient = (cltClient *)pclClient;
	if ( pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex() != -1 )
	{
		StartPos = PERSONITEM_SUMMON1EQUIP0 + MAX_SHAPE_ITEM * pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex();
	}
	SI32 siItemUinque =m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique;

	if (siItemType == ITEMTYPE_HELMET )
		return PERSONITEM_HELMET;

	else if  (siItemType == ITEMTYPE_ARMOUR  )
		return PERSONITEM_ARMOUR;

	else if(( siItemType == ITEMTYPE_CANNON || siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == 10100 ||siItemUinque == 10090) && ( m_pPersonItemInfo->clItem[ PERSONITEM_WEAPON1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON1 + StartPos ))
		return PERSONITEM_WEAPON2;

	else if ( siItemType == ITEMTYPE_CANNON || siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == 10100 ||siItemUinque == 10090)
		return PERSONITEM_WEAPON1;

	else if ( siItemType == ITEMTYPE_NECK )
		return PERSONITEM_NECK;

	else if (( siItemType == ITEMTYPE_RING )
		&&( m_pPersonItemInfo->clItem[ PERSONITEM_RING2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING2 + StartPos ))
		return PERSONITEM_RING1;

	else if ( siItemType == ITEMTYPE_RING )
		return PERSONITEM_RING2;

	else if ( siItemType == ITEMTYPE_BELT )
		return PERSONITEM_BELT;

	else if ( siItemType == ITEMTYPE_SHOES )
		return PERSONITEM_SHOES;

	else if ( siItemType ==ITEMTYPE_MANTLE )
		return PERSONITEM_MANTLE;

	else if ( siItemType == ITEMTYPE_BAG )
		return PERSONITEM_BAG;

	else if ( siItemType == ITEMTYPE_HAT )
		return PERSONITEM_HAT;

	else if ( siItemType == ITEMTYPE_DRESS )
		return PERSONITEM_DRESS;
	else
	{
		return PERSONITEM_NONE;
	}


}
SI32 CUserInventoryDlg::CheckIsInventory()
{
	POINT pt;
	GetCursorPos( &pt );

	HWND hFindWnd = WindowFromPoint( pt );
	if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_HELMET ) )
		return PERSONITEM_HELMET;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_ARMOR ) )
		return PERSONITEM_ARMOUR;
    else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WEAPON1 ) )
		return PERSONITEM_WEAPON1;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WEAPON2 ) )
		return PERSONITEM_WEAPON2;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_NECKWEAR ) )
		return PERSONITEM_NECK;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_RING1 ) )
		return PERSONITEM_RING1;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_RING2 ) )
		return PERSONITEM_RING2;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_WAISTBAND ) )
		return PERSONITEM_BELT;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_SHOE ) )
		return PERSONITEM_SHOES;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MANTLE ) )
		return PERSONITEM_MANTLE;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_BAG ) )
		return PERSONITEM_BAG;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_HAT ) )
		return PERSONITEM_HAT;
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_DRESS ) )
		return PERSONITEM_DRESS;

	else
	{
		return PERSONITEM_NONE;
	}
}

void CUserInventoryDlg::MoveInventoryItem( HWND hDlg )
{
	POINT pt;
	GetCursorPos( &pt );

	HWND hFindWnd = WindowFromPoint( pt );

	SI16 StartPos = 0;
	cltClient *pclclient = (cltClient *)pclClient;
	if ( pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex() != -1 )
	{
		StartPos = PERSONITEM_SUMMON1EQUIP0 + MAX_SHAPE_ITEM * pclclient->m_pItemInventoryDlg->GetCurrentSummonIndex();
	}


	if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MOVEITEM_HORSE ) )
	{
		if ( pclClient->pclCM->CR[1]->HaveHorse() )
		{
			SI16 pos;
			cltItem cltoitem;
			SI32 rtnvalue;

			if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_HORSE, 
				&m_clItem[ m_siSelectedIndex ],
				NULL, 
				&pos, 
				&cltoitem,
				&rtnvalue) == true)
			{
				MoveItem( m_hDlg, pos );
			}
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hParentDlg, IDC_LIST_MOVEITEM_BAG ) )
	{
		if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0  )
		{
			SI16 pos;
			cltItem cltoitem;
			SI32 rtnvalue;

			if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG, 
				&m_clItem[ m_siSelectedIndex ],
				NULL, 
				&pos, 
				&cltoitem,
				&rtnvalue) == true)
			{
				MoveItem( m_hDlg, pos );
			}
		}
	}
	else if ( hFindWnd == GetDlgItem( m_hDlg, IDC_LIST_USER_INVENTORY ) )
	{
		// ����Ʈ�信�� ����Ʈ��� �ű涧�� ���� ���׷��̵��Ҷ���...
		if ( m_siSelectedIndex >= PERSONITEM_INV0 )
		{
			ScreenToClient( GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ), &pt );

			LVHITTESTINFO HitTestInfo;
			HitTestInfo.pt = pt;
			HitTestInfo.flags = LVHT_ONITEMICON | LVHT_NOWHERE;
			int temp =  ListView_HitTest( GetDlgItem( hDlg, IDC_LIST_USER_INVENTORY ), &HitTestInfo );

			if ( temp != -1 )
			{
				if ( temp + PERSONITEM_INV0 != m_siSelectedIndex )
				{
					m_siUpgradeSelectedIndex = temp + PERSONITEM_INV0;

					if ( m_clItem[ m_siSelectedIndex ].GetType( pclClient->pclItemManager ) == ITEMTYPE_SCROLL &&  m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ].siUnique != 0 )
					{
						m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
					}
					else
					{
						MoveItem( hDlg, m_siUpgradeSelectedIndex );
					}
				}
			}

			return;
		}
	}
	else if ( hFindWnd == pclClient->GetHwnd() )
	{
		if ( m_siSelectedIndex >= PERSONITEM_INV0 )		// ����Ʈ�信 �ִ� �͸� �ٴڿ� ���� �� �����Ƿ�...
		{
			DropItem( m_siSelectedIndex );
			return;
		}
	}

	//���⼭ ���� �۾� ..�Ф�
	SI32 siCheckInven = CheckIsInventory();	

	if(siCheckInven==PERSONITEM_NONE && StartPos!=75)
	{
		return;
	}
	
	SI32 siItemUinque =m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique;
    SI32 ItemType= pclclient->pclItemManager->GetItemType(siItemUinque);
	SI32 siItemType = GetInventoryType(ItemType);

	if(siCheckInven==PERSONITEM_WEAPON2 || siCheckInven==PERSONITEM_WEAPON1)
	{
		if(ItemType >=ITEMTYPE_SWORD && ItemType <=ITEMTYPE_GUN)
		{
			siItemType = siCheckInven;
		}
	}	

	if(siCheckInven==PERSONITEM_RING1 || siCheckInven==PERSONITEM_RING2)
	{
		if(ItemType ==ITEMTYPE_RING)
		{
			siItemType = siCheckInven;
		}
	}	
	
	if(ItemType == ITEMTYPE_SCROLL)
	{
		siItemType = siCheckInven;
	}
	

	if(siItemType >= PERSONITEM_HELMET && siItemType<=PERSONITEM_DRESS)
	{
		if ( m_pPersonItemInfo->clItem[ siItemType + StartPos ].siUnique != 0 && m_siSelectedIndex != siItemType + StartPos && ItemType == ITEMTYPE_SCROLL)
		{
			m_siUpgradeSelectedIndex = siItemType + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}		
		else if ( m_pPersonItemInfo->clItem[ siItemType + StartPos ].siUnique != 0 && m_siSelectedIndex != siItemType + StartPos) 
		{
			ChangeItem( m_hParentDlg, siItemType + StartPos );
		}		
		else
		{
			MoveItem( m_hParentDlg, siItemType + StartPos );
		}
	}

	
	/*
	
	if (siItemType == PERSONITEM_HELMET )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_HELMET + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_HELMET + StartPos && ItemType == ITEMTYPE_SCROLL)
		{
			m_siUpgradeSelectedIndex = PERSONITEM_HELMET + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}		
		else if ( m_pPersonItemInfo->clItem[ PERSONITEM_HELMET + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_HELMET + StartPos) 
		{
            ChangeItem( m_hParentDlg, PERSONITEM_HELMET + StartPos );
		}		
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_HELMET + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_ARMOUR )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_ARMOUR + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_ARMOUR + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_ARMOUR + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_ARMOUR + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_WEAPON1 )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_WEAPON1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON1 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_WEAPON1 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_WEAPON1 + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_WEAPON2 )
	{

		// JAYCEE WEAPON2

		if ( m_pPersonItemInfo->clItem[ PERSONITEM_WEAPON2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON2 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_WEAPON2 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_WEAPON2 + StartPos );
		}

	}	
	else if ( siItemType == PERSONITEM_NECK )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_NECK + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_NECK + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_NECK + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_NECK + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_RING1 )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_RING1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING1 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_RING1 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_RING1 + StartPos );
		}
	}
	else if ( siItemType ==PERSONITEM_RING2 )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_RING2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING2 + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_RING2 + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_RING2 + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_BELT )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_BELT + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_BELT + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_BELT + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_BELT + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_SHOES )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_SHOES + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_SHOES + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_SHOES + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_SHOES + StartPos );
		}
	}
	else if ( siItemType ==PERSONITEM_MANTLE )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_MANTLE + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_MANTLE + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_MANTLE + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_MANTLE + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_BAG )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_BAG + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_BAG + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_BAG + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_BAG + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_HAT )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_HAT + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_HAT + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_HAT + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_HAT + StartPos );
		}
	}
	else if ( siItemType == PERSONITEM_DRESS )
	{
		if ( m_pPersonItemInfo->clItem[ PERSONITEM_DRESS + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_DRESS + StartPos )
		{
			m_siUpgradeSelectedIndex = PERSONITEM_DRESS + StartPos;
			m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, m_siUpgradeSelectedIndex, m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique , &m_pPersonItemInfo->clItem[ m_siUpgradeSelectedIndex ] );
		}
		else
		{
			MoveItem( m_hParentDlg, PERSONITEM_DRESS + StartPos );
		}
	}
	*/

	return;
}

void CUserInventoryDlg::RepairItem( SI32 siSelectedInventoryItemIndex )
{
	if ( m_clItem[ m_siSelectedIndex ].CanRepair( pclClient->pclItemManager ) )
	{
		char* pTitle = GetTxtFromMgr(1141);
		char* pText = GetTxtFromMgr(1140);
		

		if (  MessageBox(NULL,  pText,pTitle, MB_ICONQUESTION | MB_YESNO) == IDYES ) 
		{
			m_pBuffer->Push( INV_REPAIR_ITEM, m_siSelectedIndex, &m_clItem[ m_siSelectedIndex ] );
		}
		
		return;
	}

	return;
}

void CUserInventoryDlg::InventorySelect( SI32 siSelectedInventoryItemIndex, HWND hDlg )
{
	// siSelectedInventoryItemIndex �� ����Ʈ���� index���� ���� �������� index �� �ƴϴ�.
	// ���� ���� �������� index �� ������ ������ �־�� �Ѵ�.

	if ( m_clItem[ siSelectedInventoryItemIndex ].siUnique == 0 )
	{
		return;
	}
	
	pclClient->pclItemManager->PlaySound( m_clItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );

	m_siSelectedIndex = siSelectedInventoryItemIndex;	
	
	
	POINT pt;
	GetCursorPos( &pt );

	cltClient *pclclient = (cltClient *)pclClient;
	ImageList_BeginDrag( pclclient->pclImageList->hImageList, m_clItem[ m_siSelectedIndex ].GetImage( pclClient->pclItemManager ), ITEM_IMAGE_WIDTH / 2, ITEM_IMAGE_WIDTH / 2 );
	ImageList_DragEnter( NULL, pt.x, pt.y );
	SetCapture( hDlg );

	return;
}

void CUserInventoryDlg::UseItem( SI16 si16Pos )
{
	if ( m_clItem[ si16Pos ].siUnique == 0 )
	{
		return;
	}

	if ( m_clItem[ si16Pos ].GetType( pclClient->pclItemManager ) == ITEMTYPE_BOOK )
	{
		char* pTitle = GetTxtFromMgr(1142);
		char* pText = GetTxtFromMgr(1143);
		

		if (  MessageBox(NULL, pTitle, pText, MB_ICONQUESTION | MB_YESNO) == IDYES )
		{
			m_pBuffer->Push( INV_USE_ITEM, si16Pos, &m_clItem[ si16Pos ] );
		}
	}
	else
	{
		m_pBuffer->Push( INV_USE_ITEM, si16Pos, &m_clItem[ si16Pos ] );
	}

	m_siSelectedIndex = -1;
	
	return;
}

void CUserInventoryDlg::DropItem( SI16 si16Pos )
{
	char* pTitle = GetTxtFromMgr(5261);
	char* pText = GetTxtFromMgr(5262);

	if (  MessageBox(NULL,  pText,pTitle, MB_ICONQUESTION | MB_YESNO) == IDNO ) 
	{
		return;
	}

	if ( m_clItem[ si16Pos ].siUnique == 0 )
	{
		return;
	}

	m_pBuffer->Push( INV_DROP_ITEM, si16Pos, &m_clItem[ si16Pos ] );

	m_siSelectedIndex = -1;
}

void CUserInventoryDlg::MountItem( SI16 si16Pos )
{
	if ( m_clItem[ si16Pos ].siUnique == 0 )
	{
		return;
	}

	m_pBuffer->Push( INV_MOUNT_ITEM, si16Pos, &m_clItem[ si16Pos ] );

	m_siSelectedIndex = -1;
}

HWND CUserInventoryDlg::GetHwnd()
{
	return m_hDlg;
}

SI32 CUserInventoryDlg::GetSelectedIndex()
{
	return m_siSelectedIndex;
}

cltItem	*CUserInventoryDlg::GetItemIndex( SI32 siIndex )
{
	return &m_clItem[ siIndex ];
}