#include "NEquipWindow.h"

#include "../../Inventory/ItemInventoryBuffer.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../InterfaceMgr/Interface/Edit.h"

#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../../Client.h"
#include "../CommonLogic/TextMgr/TextMgr.h"

#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "Msg/MsgType-ItemMall.h"
#include "Msg/MsgType-Postoffice.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"
#include "../common/Item/ItemCommon/cltItem.h"

#include "../../Client/NInterface/NNewInventory/NNewInventory.h"  //NInventoryDlg/NInventory.h"

extern cltCommonLogic* pclClient;
extern SI32 gsiResolution;
 
CNEquipWindow::CNEquipWindow() : CDialogController()
{
	SI32 i;

	for( i = 0; i < EWV_MAX_ALLBUTTON_NUM; ++i )
	{
		m_pButton[i] = NULL;
	}

	for( i = 0; i < EWV_REAL_EQUIPITEM_NUM; ++i )
	{
		m_pListView[i] = NULL;
	}

	m_pclEquipItem			= NULL;
	m_pclInventoryItem		= NULL;

	m_pBuffer				= new CItemInventoryBuffer();

	m_pSummonInfo			= new cltSummonInfo();
	m_pSummonInfo->Init();

	m_siSelectedIndex		= -1;
	m_siCurrentSummonIndex	= SELECTED_HUMAN;
	LastSelectedIndex		= -1;
	m_siEquipSelectedIndex	= -1;
}

CNEquipWindow::~CNEquipWindow()
{
	SetTimerOnOff(false);

	SI32 i;

	GP.FreeSpr(		m_SprEquipItem		);
	GP.FreeSpr(		m_SprBack			);

	SAFE_DELETE(	m_pSummonInfo		);

	SAFE_DELETE(	m_pBuffer			);

	SAFE_DELETE_A(	m_pclInventoryItem	);

	SAFE_DELETE_A(	m_pclEquipItem		);

	for( i=0; i<EWV_MAX_ALLBUTTON_NUM; ++i )
	{
		SAFE_DELETE( m_pButton[i] );
	}

	for( i=0; i<EWV_REAL_EQUIPITEM_NUM; ++i )
	{
		SAFE_DELETE( m_pListView[i] );
	}
}

void CNEquipWindow::Create()
{
	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/NCharStatusDlg/DLG_NCharStatus_Child_NEquip.ddf"));
	file.CreatePopupDialog( this, NNEWEQUIPWINDOW_DLG, TEXT("dialog_Equip"), StaticCallBackDialogNEquipWindow );

	// if(gsiResolution == 2) // 1024 X 768
	//	MovePos(80 + 300, 135 );

	// ����
	SI32 i;

	for( i = 0; i < EWV_MAX_ALLBUTTON_NUM; ++i )
	{
		NEWCBUTTON( m_pButton[i] );
	}

	for( i = 0; i < 14; ++i )
	{
		NEWCLISTVIEW( m_pListView[i] );
	}

	// ��ư ���� ����
	SelectButtonChangeState( EWV_HUMAN_SELECTBUTTON, true );


	TCHAR tempBuffer[50] = TEXT("");
	for( i = 0; i < EWV_MAX_ALLBUTTON_NUM; ++i )
	{		
		StringCchPrintf(tempBuffer, 50, TEXT("button_NONAME%d"), i + 1 );
		file.CreateControl( m_pButton[i], NNEWEQUIPWINDOW_DLG_BUTTON1 + i, tempBuffer );
	}

	// [�߰� : Ȳ���� 2007. 12. 31 => ���Ź�ư�� ������� ����.]
	if(false == pclClient->IsCountrySwitch(Switch_Transform))
	{
		m_pButton[6]->Show(false);
	}
	
	for( i = 0; i < 14; ++i )
	{		
		StringCchPrintf(tempBuffer, 50, TEXT("listview_NONAME%d"), i + 1 );
		file.CreateControl( m_pListView[i], NNEWEQUIPWINDOW_DLG_LISTVIEW1 + i, tempBuffer );
	}

	GP.LoadSprFromFile(TEXT("NInterface/Interface/INTERFACE_300X264_00_000.SPR"), &m_SprBack);

	m_pclEquipItem = new cltItem[ MAX_SHAPE_ITEM ];
	memset( m_pclEquipItem, 0, sizeof( cltItem ) * MAX_SHAPE_ITEM );

	m_pclInventoryItem = new cltItem[ MAX_ITEM_PER_PERSON ];
	memset( m_pclInventoryItem, 0, sizeof( cltItem ) * MAX_ITEM_PER_PERSON );

	GP.LoadSprFromFile(TEXT("NInterface/Image/Image_40x40_00_000.SPR"), &m_SprEquipItem);

	TCHAR* pText = GetTxtFromMgr(5678);

	SetTitle(pText);

	SetTimerOnOff(true);

	Hide();
}


void CALLBACK CNEquipWindow::StaticCallBackDialogNEquipWindow( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
	CNEquipWindow *pThis = (CNEquipWindow *)pControllerMgr;
	pThis->CallBackDialogNEquipWindow( nEvent, nControlID, pControl );
}

void CALLBACK CNEquipWindow::CallBackDialogNEquipWindow( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;

	if( pclClient->IsCountrySwitch(Switch_ClickAndDrop))
	{
		switch ( nControlID )
		{
		case NNEWEQUIPWINDOW_DLG_LISTVIEW1:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW2:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW3:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW4:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW5:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW6:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW7:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW8:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW9:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW10:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW11:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW12:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW13:
		case NNEWEQUIPWINDOW_DLG_LISTVIEW14:
			{
				switch( nEvent )
				{
				case EVENT_LISTVIEW_LBUTTONUP:
					{
						CListView* pListView = (CListView*)GetControl( nControlID );
						if(pListView)
						{
							SI16 SelectedIndex = pListView->GetSelectedItemIndex();

							cltItem* pclSelectedItem = NULL;
							if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
							{
								pclSelectedItem = &m_pclInventoryItem[ SelectedIndex ];
							}
							else
							{
								pclSelectedItem = &m_pclEquipItem[ SelectedIndex ];
							}	

							if ( (SelectedIndex >= 0) && (pclSelectedItem != NULL) && (pclSelectedItem->siUnique > 0) )
							{
								pclclient->m_pInterfaceMgr->BeginClickAndDrop_Item(pclSelectedItem, GetDialogControllerID(), nControlID, SelectedIndex);
							}

						}
					}
					break;
				}				
				return;
			}
			break;
		}
	}	

	switch ( nControlID )
	{
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			Hide();
		}
		break;

	case NNEWEQUIPWINDOW_DLG_LISTVIEW1:
		{
			EquipmentListViewMsgProc( m_pListView[ 0 ], PERSONITEM_HELMET, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW2:
		{
			EquipmentListViewMsgProc( m_pListView[ 1 ], PERSONITEM_ARMOUR, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW3:
		{
			EquipmentListViewMsgProc( m_pListView[ 2 ], PERSONITEM_WEAPON1, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW4:
		{
			EquipmentListViewMsgProc( m_pListView[ 3 ], PERSONITEM_NECK, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW5:
		{
			EquipmentListViewMsgProc( m_pListView[ 4 ], PERSONITEM_RING1, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW6:
		{
			EquipmentListViewMsgProc( m_pListView[ 5 ], PERSONITEM_RING2, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW7:
		{
			EquipmentListViewMsgProc( m_pListView[ 6 ], PERSONITEM_BELT, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW8:
		{
			EquipmentListViewMsgProc( m_pListView[ 7 ], PERSONITEM_SHOES, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW9:
		{
			EquipmentListViewMsgProc( m_pListView[ 8 ], PERSONITEM_WEAPON2, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW10:
		{
			EquipmentListViewMsgProc( m_pListView[ 9 ], PERSONITEM_MANTLE, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW11:
		{
			EquipmentListViewMsgProc( m_pListView[ 10 ], PERSONITEM_BAG, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW12:
		{
			EquipmentListViewMsgProc( m_pListView[ 11 ], PERSONITEM_HAT, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW13:
		{
			EquipmentListViewMsgProc( m_pListView[ 12 ], PERSONITEM_DRESS, nEvent );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW14:
		{
			EquipmentListViewMsgProc( m_pListView[ 13 ], PERSONITEM_BAG_SUB, nEvent );
		}
		break;

		// ����â ����( ���, ��ȯ��1, ��ȯ��2, ��ȯ��3 )
	case NNEWEQUIPWINDOW_DLG_BUTTON1:
		{
			m_siCurrentSummonIndex = SELECTED_HUMAN;
			
			LoadItemData();

			SelectButtonChangeState( EWV_HUMAN_SELECTBUTTON );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_BUTTON2:
		{
			OnButtonSummonSelect( EWV_SUMMON_1_SELECTBUTTON );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_BUTTON3:
		{
			OnButtonSummonSelect( EWV_SUMMON_2_SELECTBUTTON );
		}
		break;
		
	case NNEWEQUIPWINDOW_DLG_BUTTON4:
		{
			OnButtonSummonSelect( EWV_SUMMON_3_SELECTBUTTON );
		}
		break;

		// ���� ����
	case NNEWEQUIPWINDOW_DLG_BUTTON5:
		{
			// [�߰� : Ȳ���� 2008. 1. 4 => ���Ż��¿����� ���� ��ü �Ұ���.]
			if(true == pclclient->pclCM->CR[1]->clTransFormInfo.bTransFormMode)
			{
				break;
			}

			ExchangeWeapon();
		}
		break;
	case NNEWEQUIPWINDOW_DLG_BUTTON6:
		{			
			ExchangeClothes();
		}
		break;
	case NNEWEQUIPWINDOW_DLG_BUTTON7:
		{
			// ���� ���� â�� ����.
			pclclient->CreateInterface(CHARTRANSFORMINFO_DLG);

			m_pButton[6]->SetFocus(false);
		}
		break;
	}
}

void CNEquipWindow::Hide()
{
	CControllerMgr::Show( false );

	m_siCurrentSummonIndex = SELECTED_HUMAN;
}

void CNEquipWindow::Show()
{

	CControllerMgr::Show( true );

	m_siCurrentSummonIndex = SELECTED_HUMAN;

	SelectButtonChangeState( EWV_HUMAN_SELECTBUTTON );

	LoadSummonData();
	LoadItemData();

	m_bRideHorse = pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE;
}

void CNEquipWindow::Action()
{
	if ( IsSummonDataChanged() )
	{
		m_siCurrentSummonIndex = SELECTED_HUMAN;
		SelectButtonChangeState( EWV_HUMAN_SELECTBUTTON );

		LoadSummonData();
		LoadItemData();
	}
	else if ( IsItemDataChanged() )
	{
		LoadItemData();
	}
	else if ( IsSummonItemDataChanged() )
	{
		LoadItemData();
	}
	else if ( m_bRideHorse != pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE)
	{
		LoadItemData();
		m_bRideHorse = pclClient->pclCM->CR[1]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE;
	}
}

bool CNEquipWindow::IsSummonDataChanged()
{
	SI32 id = 1;
	for ( SI16 i = 0; i < MAX_SUMMON_OWN; ++i )
	{
		if ( m_pSummonInfo->clSummon[ i ].siKind != pclClient->pclCM->CR[id]->pclCI->clSummonInfo.clSummon[ i ].siKind )
		{
			return true;
		}
	}

	return false;
}

bool CNEquipWindow::IsItemDataChanged()
{
	SI32 id = 1;

	for ( int j = 0; j < MAX_ITEM_PER_PERSON; ++j )
	{
		SI32 size = sizeof(cltItem);

		BYTE* src = (BYTE*)&m_pclInventoryItem[ j ];
		BYTE* dst = (BYTE*)&pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[ j ];

		for( int i = 0;i < size; ++i )
		{
			if( src[ i ] != dst[ i ] )
			{
				return true;
			}
		}
	}

	return false;
}

bool CNEquipWindow::IsSummonItemDataChanged()
{
	SI32 siID = 1;

	if ( (0 > m_siCurrentSummonIndex) && (MAX_SUMMON_OWN <= m_siCurrentSummonIndex) )
	{
		return false;
	}
	cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[ siID ];
	if ( NULL == pclchar )
	{
		return false;
	}
	
	cltItem *pclSrcItem = NULL;
	cltItem *pclDstItem = NULL;


	for ( SI32 siIndex=0; siIndex<MAX_SHAPE_ITEM; siIndex++ )
	{	
		pclSrcItem = &m_pclEquipItem[siIndex];
		pclDstItem = pclchar->pclCI->clSummonInfo.GetSummonEquipItem( m_siCurrentSummonIndex, siIndex );

		if ( (NULL == pclSrcItem) || (NULL == pclDstItem) )
		{
			continue;
		}

		if ( (pclSrcItem->siUnique != pclDstItem->siUnique) || (pclSrcItem->siItemNum != pclDstItem->siItemNum) )
		{
			return true;
		}
	}

	return false;
}

void CNEquipWindow::DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY )
{
	GP.PutSpr( &m_SprBack , ScreenRX + GetX() + 5 , ScreenRY + GetY() + 52 );

	//	m_SprBack.PutSprT( ScreenRX + GetX() + 5, ScreenRY + GetY() + 52, 0);

	SI32 id = 1;
	// ��� ���� ��쿡�� ���� ���� ���� �̹��� ���������..
	if ( m_siCurrentSummonIndex == SELECTED_HUMAN )
	{
		if ( pclClient->pclCM->CR[id]->ActiveWeapon > 0 && m_pclInventoryItem[ pclClient->pclCM->CR[id]->ActiveWeapon ].siUnique > 0 )
		{
			if ( pclClient->pclCM->CR[id]->ActiveWeapon == PERSONITEM_WEAPON1 )
			{
				GP.PutSpr( &m_SprEquipItem , ScreenRX + GetX() + m_pListView[2]->GetX() , ScreenRY + GetY() + m_pListView[2]->GetY(),14 );
				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[2]->GetX(), ScreenRY + GetY() + m_pListView[2]->GetY(), 14 );
			}
			else if( pclClient->pclCM->CR[id]->ActiveWeapon == PERSONITEM_WEAPON2 )
			{
				GP.PutSpr( &m_SprEquipItem ,  ScreenRX + GetX() + m_pListView[8]->GetX() , ScreenRY + GetY() + m_pListView[8]->GetY(),14 );
				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[8]->GetX(), ScreenRY + GetY() + m_pListView[8]->GetY(), 14 );
			}
		}

		if ( pclClient->pclCM->CR[id]->ActiveClothes > 0 && m_pclInventoryItem[ pclClient->pclCM->CR[id]->ActiveClothes ].siUnique > 0 &&
			pclClient->pclCM->CR[id]->ActiveHat >= 0 && m_pclInventoryItem[ pclClient->pclCM->CR[id]->ActiveHat ].siUnique > 0
			)
		{
			if ( pclClient->pclCM->CR[id]->ActiveClothes == PERSONITEM_DRESS )
			{
				GP.PutSpr( &m_SprEquipItem ,  ScreenRX + GetX() + m_pListView[11]->GetX() , ScreenRY + GetY() + m_pListView[11]->GetY(),14 );
				GP.PutSpr( &m_SprEquipItem ,  ScreenRX + GetX() + m_pListView[12]->GetX() , ScreenRY + GetY() + m_pListView[12]->GetY(),14 );

				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[11]->GetX(), ScreenRY + GetY() + m_pListView[11]->GetY(), 14 );
				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[12]->GetX(), ScreenRY + GetY() + m_pListView[12]->GetY(), 14 );

				// �� �ٲٱ�
				TCHAR* pText = GetTxtFromMgr(5344 );
				m_pButton[4]->SetUseToolTip(pText);

				// ���� �ٲٱ�
				pText = GetTxtFromMgr(5345);
				m_pButton[3]->SetUseToolTip(pText);
			}
			else if( pclClient->pclCM->CR[id]->ActiveClothes == PERSONITEM_ARMOUR )
			{
				GP.PutSpr( &m_SprEquipItem ,  ScreenRX + GetX() + m_pListView[0]->GetX() , ScreenRY + GetY() + m_pListView[0]->GetY() ,14);
				GP.PutSpr( &m_SprEquipItem ,  ScreenRX + GetX() + m_pListView[1]->GetX() , ScreenRY + GetY() + m_pListView[1]->GetY() ,14);

				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[0]->GetX(), ScreenRY + GetY() + m_pListView[0]->GetY(), 14 );
				//m_SprEquipItem.PutSprT( ScreenRX + GetX() + m_pListView[1]->GetX(), ScreenRY + GetY() + m_pListView[1]->GetY(), 14 );

				//	m_pListView[ PERSONITEM_DRESS ]->SetFontIndex( 1 );
				//	m_pListView[ PERSONITEM_ARMOUR ]->SetFontIndex( 19 );

				//	m_pListView[ PERSONITEM_HAT ]->SetFontIndex( 0 );
				//	m_pListView[ PERSONITEM_HELMET ]->SetFontIndex( 18 );

				// �� �ٲٱ�
				TCHAR* pText = GetTxtFromMgr(5344);
				m_pButton[4]->SetUseToolTip(pText);

				// ���� �ٲٱ�
				pText = GetTxtFromMgr(5343);
				m_pButton[3]->SetUseToolTip(pText);

			}
		}
	}
}

void CNEquipWindow::LoadItemData()
{
	/*
	SI16 StartPos = 0;

	// ��ȯ�� Tab�� ���.
	if ( m_siCurrentSummonIndex != -1 )
	{
		StartPos = PERSONITEM_SUMMON1EQUIP0 + MAX_SHAPE_ITEM * m_siCurrentSummonIndex;
	}
	*/

	// ����â�� ������ ������ �о�ͼ� �V���� �ش�.
	SI16 i	= 0;
	SI32 id	= 1;

	cltCharCommon* pclchar = (cltCharCommon*)pclClient->pclCM->CR[id];
	if ( NULL == pclchar )
	{
		return;
	}

	// �κ��丮 ������ ������ �����´�
	for ( i=0; i<MAX_ITEM_PER_PERSON; ++i )
	{
		m_pclInventoryItem[ i ].Set( &pclchar->pclCI->clCharItem.clItem[ i ] );
	}

	// ��� ����â ������ ��� �����
	for ( i=0; i<EWV_REAL_EQUIPITEM_NUM; ++i )
	{
		if ( m_pListView[ i ] )
		{
			m_pListView[ i ]->DeleteAllItems();
		}
	}
	
	// ������ �̹��� ���� ����
	SI32		GlobalImageIndex	= -1;	
	SI32		GlobalImageFont		= -1;
	
	cltItem		clNowItem;
	SI16		siItemUnique		= 0;
	
	

	for ( i=0; i<EWV_REAL_EQUIPITEM_NUM; ++i )
	{
		// ����� ��� ����� �κ� �������� �־��ش�
		if ( SELECTED_HUMAN == m_siCurrentSummonIndex  )
		{
			m_pclEquipItem[ i ].Set( &pclchar->pclCI->clCharItem.clItem[ i ] );
		}
		// ��ȯ���� ��� ��ȯ���� �κ� �������� �־��ش�
		else
		{
			m_pclEquipItem[ i ].Set( &pclchar->pclCI->clSummonInfo.clItemInfo[m_siCurrentSummonIndex].clEquipItem[ i ] );
		}

		clNowItem.Init();
		clNowItem.Set( &m_pclEquipItem[ i ] );

		siItemUnique = clNowItem.siUnique;
		
		// ��ȿ�� ����ũ�� �ƴ϶��
		if ( 0 >= siItemUnique )
		{
			continue;
		}

		// ������ �̹��� ���� ����
		if ( false == pclClient->pclItemManager->GetItemGImageFileIndexAndFont( siItemUnique, &GlobalImageIndex, &GlobalImageFont ) )
		{
			continue;
		}

		// ������ �̸� ������
		TCHAR *szItemName = (TCHAR*)pclClient->pclItemManager->GetName( siItemUnique );
		if ( NULL == szItemName )
		{
			continue;
		}

		TCHAR	szToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
		SI32	siItemStatus	= 0;
		SI32	siItemnum		= clNowItem.siItemNum;

		pclClient->pclItemManager->GetExplain( &clNowItem, szToolTipMsg, true, false, true );

		//cyj �����ִ� �������� ���Ǿ��������� ������ ���� ���̵���
		stListViewItemData ListViewItemData;
		ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, 0, siItemnum, szItemName, szToolTipMsg );

		if ( !pclClient->IsCountrySwitch(Switch_StatusBug) && (SELECTED_HUMAN == m_siCurrentSummonIndex) )
		{
			SI32 retval = 0;
			if(pclClient->pclItemManager->CheckCondition( siItemUnique, pclchar, &retval ) == false)
			{
				ListViewItemData.SetCanNotEquip( true );
			}
		}
        
		if ( m_pListView[i] )
		{
			m_pListView[ i ]->SetStartItemPos( i );
			m_pListView[ i ]->InsertItem( &ListViewItemData );

			if ( m_pclEquipItem[ i ].CanPile(pclClient->pclItemManager) )
			{
				m_pListView[ i ]->SetItemNumShow(true);
			}
			else
			{
				m_pListView[ i ]->SetItemNumShow(false);
			}

		}

	}	// for ( i=0; i<=EWV_REAL_EQUIPITEM_NUM; ++i ) ����
}

void CNEquipWindow::LoadSummonData()
{
	SI32	siMyId	= 1;

	// ��ȯ�� ������ ������
	m_pSummonInfo->Set( &pclClient->pclCM->CR[siMyId]->pclCI->clSummonInfo );

	// ���
	TCHAR*	pName	= (TCHAR*)pclClient->pclCM->CR[siMyId]->GetName();
	if ( pName == NULL )
	{
		pName = GetTxtFromMgr(1159);
	}
	m_pButton[0]->SetText( pName, DT_CENTER | DT_VCENTER | DT_SINGLELINE );


	for ( SI16 i = 0; i < MAX_SUMMON_OWN; ++i )
	{
		SI32			siSummonKind	= m_pSummonInfo->clSummon[ i ].siKind;
		// ��� ������� ��ư Ȱ��ȭ
		SI32			siSummonEquip	= 0;
		cltKindInfo*	pclki			= NULL;

		// ��ȯ�� KIND ������ �����
		if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
		{
			pclki = pclClient->pclKindInfoSet->pclSummonKI[ siSummonKind ];
		}
		else
		{
			pclki = pclClient->pclKindInfoSet->pclKI[ siSummonKind ];
		}

		// ����Դٸ� ����� �������� ���θ� ����
		if ( pclki )
		{
			siSummonEquip = pclki->siSummonEquip;
		}

		if ( (siSummonKind > 0) && (m_pSummonInfo->clSummon[ i ].szName != NULL) )
		{
			m_pButton[i+1]->SetText( m_pSummonInfo->clSummon[ i ].szName, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
			
			// ��� ���������Ҷ��� Ȱ��ȭ �ȴ�.
			if ( siSummonEquip )
			{
				m_pButton[i+1]->Enable( true );
			}
			else
			{
				m_pButton[i+1]->Enable( false );
			}
		}
		else
		{
			m_pButton[i+1]->SetText( TEXT("") );
			m_pButton[i+1]->Enable( false );
		}
		//else
		//{
			// ��ȯ����
		//	pText = GetTxtFromMgr(848);

		//	m_pButton[i+1]->SetText( pText, DT_CENTER | DT_VCENTER | DT_SINGLELINE );
		//}
	}	// for ( SI16 i = 0; i < MAX_SUMMON_OWN; ++i ) ����

	return;
}

bool CNEquipWindow::Pop( stMoveData * pMoveData )
{
	return m_pBuffer->Pop( pMoveData );	
}

bool CNEquipWindow::Pop( BYTE* pMoveData )
{
	return m_pBuffer->Pop( pMoveData );
}

SI32 CNEquipWindow::GetInventoryType(SI32 siItemType)
{
	SI32 StartPos =0;
	SI32 siItemUinque =m_pclInventoryItem[m_siSelectedIndex].siUnique;

	if (siItemType == ITEMTYPE_HELMET )
		return PERSONITEM_HELMET;

	else if  (siItemType == ITEMTYPE_ARMOUR  )
		return PERSONITEM_ARMOUR;

	else if(( siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == ITEMUNIQUE(10100) ||siItemUinque == ITEMUNIQUE(10090)) && (m_pclInventoryItem[ PERSONITEM_WEAPON1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON1 + StartPos ))
		return PERSONITEM_WEAPON2;

	else if ( siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == ITEMUNIQUE(10100) ||siItemUinque == ITEMUNIQUE(10090))
		return PERSONITEM_WEAPON1;

	else if ( siItemType == ITEMTYPE_NECK || siItemType == ITEMTYPE_AVATAR_NECK) // �ƹ�Ÿ �����
		return PERSONITEM_NECK;

	else if (( siItemType == ITEMTYPE_RING || siItemType == ITEMTYPE_AVATAR_RING ) // �ƹ�Ÿ ����
		&&( m_pclInventoryItem[ PERSONITEM_RING2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING2 + StartPos ))
		return PERSONITEM_RING1;

	else if ( siItemType == ITEMTYPE_RING )
		return PERSONITEM_RING2;

	else if ( siItemType == ITEMTYPE_BELT )
		return PERSONITEM_BELT;

	else if ( siItemType == ITEMTYPE_SHOES )
		return PERSONITEM_SHOES;

	else if ( siItemType ==ITEMTYPE_MANTLE || siItemType == ITEMTYPE_AVATAR_MANTLE ) // �ƹ�Ÿ ����
		return PERSONITEM_MANTLE;
	
	else if ( (siItemType == ITEMTYPE_BAG) &&
		( m_pclInventoryItem[ PERSONITEM_BAG_SUB + StartPos ].siUnique != 0	&& 
		m_siSelectedIndex != PERSONITEM_BAG_SUB + StartPos ) )
		return PERSONITEM_BAG;

	else if ( siItemType == ITEMTYPE_BAG )
		return PERSONITEM_BAG_SUB;

	else if ( siItemType == ITEMTYPE_HAT || siItemType == ITEMTYPE_AVATAR_HAT) // �ƹ�Ÿ ����
		return PERSONITEM_HAT;

	else if ( siItemType == ITEMTYPE_DRESS || siItemType == ITEMTYPE_AVATAR_DRESS ) // �ƹ�Ÿ �Ǻ�
		return PERSONITEM_DRESS;
	else
	{
		return PERSONITEM_NONE;
	}
}

void CNEquipWindow::EquipmentListViewMsgProc( CListView* pListView, SI16 ItemPos, UINT nEvent )
{
	if ( pListView == NULL )
	{
		return;
	}

	cltClient *pclclient = (cltClient *)pclClient;

	// �����̵� ����̶� ������ ������� �ִ�!!
	//CListView* m_pInventoryListView = ((CNNewInventory*) pclclient->m_pDialog[ NNEWINVENTORY_DLG])->m_pInventoryListView;
	//CListView* m_pInventoryHorseListView = ((CNNewInventory*) pclclient->m_pDialog[ NNEWINVENTORY_HORSE_DLG])->m_pInventoryListView;

	SI16 m_siCurrentInventoryIndex =((CNNewInventory*) pclclient->m_pDialog[ NNEWINVENTORY_DLG])->m_siCurrentInventoryIndex;


	//	if( m_pInventoryListView == NULL )
	//		return;

	static TempCounter =0 ;

	switch( nEvent )
	{
	case EVENT_LISTVIEW_LBUTTONDOWN:
		{	
			if ( ++TempCounter % 2 == 0 )
			{
				int tesdfsdf = 0;
				tesdfsdf++;
			}

			SI16 SelectedIndex = pListView->GetSelectedItemIndex();
			POINT Point;
			GetCursorPos( &Point );
			ScreenToClient( pclclient->GetHwnd(), &Point );
			Point.x += MAP_TILE_XSIZE;
			Point.y += MAP_TILE_YSIZE;

			SI16 LastSelectedIndex = -1;

			CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];
			CNNewInventory* horseinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_HORSE_DLG];
			CNNewInventory* bag0inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG0_DLG];
			CNNewInventory* bag1inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG1_DLG];


			CControllerMgr *pDialog = NULL;
			CControllerObj *pControllerObj = NULL;

			if ( pclclient->m_pInterfaceMgr->GetControllerAtPoint( &pDialog, &pControllerObj ) == true )
			{
				SI16 DialogID = pDialog->GetDialogControllerID();
				switch ( DialogID )
				{
				case NNEWINVENTORY_DLG:
					LastSelectedIndex = personinventory->m_pInventoryListView->GetItemIndexFromPoint( Point, true );
					break;
				case NNEWINVENTORY_HORSE_DLG:
					LastSelectedIndex = horseinventory->m_pInventoryListView->GetItemIndexFromPoint( Point, true );
					break;
				case NNEWINVENTORY_BAG0_DLG:
					LastSelectedIndex = bag0inventory->m_pInventoryListView->GetItemIndexFromPoint( Point, true );
					break;						
				case NNEWINVENTORY_BAG1_DLG:
					LastSelectedIndex = bag1inventory->m_pInventoryListView->GetItemIndexFromPoint( Point, true );
					break;						}
			}
			if ( m_siSelectedIndex >= 0 )
			{
				if ( pclclient->m_pInterfaceMgr->IsItemDragMoveStatus() )
				{
					CControllerMgr *pDialog = NULL;
					CControllerObj *pControllerObj = NULL;

					if ( pclclient->m_pInterfaceMgr->GetControllerAtPoint( &pDialog, &pControllerObj ) == false )
					{
						if ( GetFocus() == pclclient->GetHwnd() )
						{
							//	DropItem( m_siSelectedIndex );

							pListView->ClearSelectedItem();
							m_siSelectedIndex = -1;
						}
					}
					else
					{
						//	LastSelectedIndex = ((CNNewInventory*) pclclient->m_pDialog[ NNEWINVENTORY_DLG])->m_pInventoryListView->GetLastSelectedItemIndex();

						if ( pControllerObj )
						{
							SI16 SelectPos = -1;
							/*
							SI16 StartPos = 0;
							if ( m_siCurrentSummonIndex != -1 )
							{
								StartPos = PERSONITEM_SUMMON1EQUIP0 + MAX_SHAPE_ITEM * m_siCurrentSummonIndex;
							}
							*/

							switch( pControllerObj->GetControllerID() )
							{
							case NNEWEQUIPWINDOW_DLG_LISTVIEW1:
								SelectPos = PERSONITEM_HELMET;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW2:
								SelectPos = PERSONITEM_ARMOUR;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW3:
								SelectPos = PERSONITEM_WEAPON1;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW4:
								SelectPos = PERSONITEM_NECK;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW5:
								SelectPos = PERSONITEM_RING1;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW6:
								SelectPos = PERSONITEM_RING2;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW7:
								SelectPos = PERSONITEM_BELT;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW8:
								SelectPos = PERSONITEM_SHOES;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW9:
								SelectPos = PERSONITEM_WEAPON2;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW10:
								SelectPos = PERSONITEM_MANTLE;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW11:
								SelectPos = PERSONITEM_BAG;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW12:
								SelectPos = PERSONITEM_HAT;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW13:
								SelectPos = PERSONITEM_DRESS;// + StartPos;
								break;
							case NNEWEQUIPWINDOW_DLG_LISTVIEW14:
								SelectPos = PERSONITEM_BAG_SUB;// + StartPos;
								break;
							case NNEWINVENTORY_DIALOG_MOVEITEMTOHORSE_LISTVIEW:
								{	
									if ( pclClient->pclCM->CR[1]->HaveHorse() )
									{
										SI16 pos;
										cltItem cltoitem;
										SI32 rtnvalue;

										if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_HORSE, 
											&m_pclInventoryItem[ m_siSelectedIndex ],
											NULL, 
											&pos, 
											&cltoitem,
											&rtnvalue) == true)
										{
											SelectPos = pos;
										}
										else
										{
											SelectPos = -1;
										}
									}
								}
								break;
							case NNEWINVENTORY_DIALOG_MOVEITEMTOBAG0_LISTVIEW:
								{	
									if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0  )
									{
										SI16 pos;
										cltItem cltoitem;
										SI32 rtnvalue;

										if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG, 
											&m_pclInventoryItem[ m_siSelectedIndex ],
											NULL, 
											&pos, 
											&cltoitem,
											&rtnvalue) == true)
										{
											SelectPos = pos;
										}
										else
										{
											SelectPos = -1;
										}
									}								}
								break;
							case NNEWINVENTORY_DIALOG_MOVEITEMTOBAG1_LISTVIEW:
								{	
									if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0  )
									{
										SI16 pos;
										cltItem cltoitem;
										SI32 rtnvalue;

										if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG_SUB, 
											&m_pclInventoryItem[ m_siSelectedIndex ],
											NULL, 
											&pos, 
											&cltoitem,
											&rtnvalue) == true)
										{
											SelectPos = pos;
										}
										else
										{
											SelectPos = -1;
										}
									}								}
								break;
							case NNEWINVENTORY_DIALOG_INVENTORY_LISTVIEW:
								{
									SelectPos = LastSelectedIndex;
								}
								break;
							default:
								break;
							}

							if ( SelectPos > -1 )
							{

								if ( (m_siSelectedIndex != SelectPos) && ((m_pclInventoryItem[ SelectPos ].siUnique == 0 || m_pclInventoryItem[ SelectPos ].IsBulletItem())) )
								{
									MoveItem( SelectPos );
								}
								else if ( SelectPos != m_siSelectedIndex )
								{
									m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, SelectPos, m_pclInventoryItem[ m_siSelectedIndex ].siUnique, &m_pclInventoryItem[ SelectPos ] );
								}
							}
						}
					}

					pListView->ClearSelectedItem();
					m_siSelectedIndex = -1;

					pclclient->m_pInterfaceMgr->ItemEndDrag();
				}
				else
				{
					//m_siPreItemDragIndex = -1;
				}
			}
			else
			{
				m_siSelectedIndex = SelectedIndex;
				//m_siPreItemDragIndex = -1;
			}
		}
		break;
	case EVENT_LISTVIEW_LBUTTONUP:
		{
			OnButtonUpListView( pListView );
		}
		break;
	case EVENT_LISTVIEW_RBUTTONUP:
		{

		}
		break;
	}

	return;
}

void CNEquipWindow::MoveItem( SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( m_siSelectedIndex == PERSONITEM_BAG )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG0 && Destination < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}

	if ( m_siSelectedIndex == PERSONITEM_BAG_SUB )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG1 && Destination < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}

	SI32 MoveInfo = MAKELONG( m_siSelectedIndex, Destination );

	if ( m_pclInventoryItem[ Destination ].siUnique != 0 )
	{
		if ( m_pclInventoryItem[ Destination ].CanPile( pclClient->pclItemManager ) == false )
		{
			return;
		}
	}

	if((Destination >= 0  && Destination <= 14 ) || Destination == 82 || Destination == 97 )
	{
		if(m_pclInventoryItem[ m_siSelectedIndex ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR *pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(m_pclInventoryItem[ m_siSelectedIndex ].siUnique);

		if (ref > 0)
		{
			bool bCanEquip = true;
			SI32 siKind = pclClient->pclCM->CR[1]->GetKind();

			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST) == true)
			{
				if (siKind != 0 && siKind != KIND_HERO3 && siKind != KIND_HEROINE3)
					bCanEquip = false;
			}

			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_WEST) == true)
			{
				if (siKind != 0 && siKind != KIND_HERO4 && siKind != KIND_HEROINE4)
					bCanEquip = false;
			}

			if (bCanEquip == false)
			{
				TCHAR*pTitle = GetTxtFromMgr(6023);
				TCHAR *pText = GetTxtFromMgr(6024);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				return;		
			}

		}

	}

	// ����϶�
	if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
	{
		pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
		m_pBuffer->Push( INV_MOVE_ITEM, MoveInfo, &m_pclInventoryItem[ m_siSelectedIndex ] );
	}
	// ��ȯ���ϰ��
	else
	{
		pclClient->pclItemManager->PlaySound( m_pclEquipItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
		m_pBuffer->Push( INV_MOVE_ITEM, MoveInfo, &m_pclEquipItem[ m_siSelectedIndex ] );
	}

	return;
}

void CNEquipWindow::ChangeItem( SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( m_siSelectedIndex == PERSONITEM_BAG )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG0 && Destination < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}
	if ( m_siSelectedIndex == PERSONITEM_BAG_SUB )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG1 && Destination < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}


	SI32 MoveInfo = MAKELONG( m_siSelectedIndex, Destination );

	if((Destination >= 0  && Destination <= 14 ) || Destination == 82 || Destination == 97 )
	{
		if(m_pclInventoryItem[ m_siSelectedIndex ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR*pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}
	}

	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_CHANGE_ITEM, MoveInfo, &m_pclInventoryItem[ m_siSelectedIndex ] );


	return;
}

// WEAPON1 �� WEAPON2�� ��ġ�� ��ȯ�Ѵ�.
void CNEquipWindow::ExchangeWeapon()
{
	if ( m_pclInventoryItem[ PERSONITEM_WEAPON1 ].siUnique == 0 && 
		m_pclInventoryItem[ PERSONITEM_WEAPON2 ].siUnique == 0 )
	{
		return;
	}

	cltMsg clMsg(GAMEMSG_REQUEST_EXCHANGEWEAPON, 0, NULL);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

	((cltClient*)pclClient)->pclCM->CR[1]->SetCurrentOrder(ORDER_STOP);
	((cltClient*)pclClient)->SetSiSelectedOrder(ORDER_STOP);

	m_siSelectedIndex = -1;

	return;
}

void CNEquipWindow::MoveItem( SI32 siSource, SI32 Destination )
{
	cltClient*	pclclient	= (cltClient *)pclClient;

	cltItem*	pclSrcItem	= NULL;
	cltItem*	pclDestItem	= NULL;
	
	
	// ���� ��ġ�� ���â�̶��
	if ( (PERSONITEM_HELMET <= siSource) && (MAX_SHAPE_ITEM > siSource)  && (SELECTED_HUMAN != m_siCurrentSummonIndex) )
	{
		pclSrcItem = &m_pclEquipItem[ siSource ];
	}
	else
	{
		pclSrcItem = &m_pclInventoryItem[ siSource ];
	}

	// ���� ��ġ�� ���â�̶��
	if ( (PERSONITEM_HELMET <= Destination) && (MAX_SHAPE_ITEM > Destination)  && (SELECTED_HUMAN != m_siCurrentSummonIndex) )
	{
		pclDestItem = &m_pclEquipItem[ Destination ];
	}
	else
	{
		pclDestItem = &m_pclInventoryItem[ Destination ];
	}

	if ( (NULL == pclSrcItem) || (NULL == pclDestItem) )
	{
		return;
	}

	if ( siSource == PERSONITEM_BAG )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG0 && Destination < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}

	if ( siSource == PERSONITEM_BAG_SUB )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG1 && Destination < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}

	SI32 MoveInfo = MAKELONG( siSource, Destination );

	if ( pclDestItem->siUnique != 0 )
	{
		if ( pclDestItem->CanPile( pclClient->pclItemManager ) == false )
		{
			return;
		}
	}

	if ( (Destination >= 0)  && (Destination <= 14) )
	{
		if(pclSrcItem->IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR *pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclSrcItem->siUnique);

		if (ref > 0)
		{
			bool bCanEquip = true;
			SI32 siKind = pclClient->pclCM->CR[1]->GetKind();

			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST) == true)
			{
				if (siKind != 0 && siKind != KIND_HERO3 && siKind != KIND_HEROINE3)
					bCanEquip = false;
			}

			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_WEST) == true)
			{
				if (siKind != 0 && siKind != KIND_HERO4 && siKind != KIND_HEROINE4)
					bCanEquip = false;
			}

			if (bCanEquip == false)
			{
				TCHAR*pTitle = GetTxtFromMgr(6023);
				TCHAR *pText = GetTxtFromMgr(6024);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				return;		
			}

		}

	}

	pclClient->pclItemManager->PlaySound( pclSrcItem->siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_MOVE_ITEM, MoveInfo, pclSrcItem );

	return;
}

void CNEquipWindow::ChangeItem( SI32 siSource, SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( siSource == PERSONITEM_BAG )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG0 && Destination < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG0; t < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}
	if ( siSource == PERSONITEM_BAG_SUB )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG1 && Destination < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG )
		{
			TCHAR* pTitle = GetTxtFromMgr(1167);
			TCHAR* pText = GetTxtFromMgr(1168);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return;
		}

		// ���濡 ������ �ִٸ� �ű�� �Ұ�
		for ( SI16 t = PERSONITEM_BAG1; t < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG; ++t )
		{
			if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
			{
				TCHAR* pTitle = GetTxtFromMgr(1165);
				TCHAR* pText = GetTxtFromMgr(1166);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
				return;
			}
		}
	}


	SI32 MoveInfo = MAKELONG( siSource, Destination );

	if((Destination >= 0  && Destination <= 14 ) || Destination == 82 || Destination == 97 )
	{
		if(m_pclInventoryItem[ siSource ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR*pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}
	}

	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ siSource ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_CHANGE_ITEM, MoveInfo, &m_pclInventoryItem[ siSource ] );

	return;
}

void CNEquipWindow::ExchangeClothes()
{


	if ( m_pclInventoryItem[ PERSONITEM_DRESS ].siUnique == 0 ||
		m_pclInventoryItem[ PERSONITEM_ARMOUR ].siUnique == 0 || 

		m_pclInventoryItem[ PERSONITEM_HELMET ].siUnique == 0 || 
		m_pclInventoryItem[ PERSONITEM_HAT ].siUnique == 0  ||

		m_pclInventoryItem[ PERSONITEM_DRESS ].siUnique == ITEMUNIQUE(23150) ||
		m_pclInventoryItem[ PERSONITEM_DRESS ].siUnique == ITEMUNIQUE(9280) ||
		m_pclInventoryItem[ PERSONITEM_DRESS ].siUnique == ITEMUNIQUE(9290) ||
		m_pclInventoryItem[ PERSONITEM_HAT ].siUnique == ITEMUNIQUE(13270) ||
		m_pclInventoryItem[ PERSONITEM_HAT ].siUnique == ITEMUNIQUE(13280) ||
		m_pclInventoryItem[ PERSONITEM_HAT ].siUnique == ITEMUNIQUE(13290) 

		)
	{
		return;
	}

	cltMsg clMsg(GAMEMSG_REQUEST_EXCHANGECLOTHES, 0, NULL);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

	m_siSelectedIndex = -1;


	return;
}


bool CNEquipWindow::EndClickAndDrop( cltClickAndDrop* pclClickAndDrop )
{
	cltClient* pclclient = (cltClient*)pclClient;

	if(pclClickAndDrop == NULL)										return false;
	if(pclClickAndDrop->IsType(CLICKANDDROP_TYPE_ITEM) == false)	return false;

	cltClickAndDrop_Item* pclClickAndDrop_Item = (cltClickAndDrop_Item*)pclClickAndDrop;

	SI32 siDestination = -1;

	// �κ��丮���� �κ��丮�� �̵��ϴ� ���
	switch(pclClickAndDrop_Item->m_siSrcDialogID)
	{
	case NNEWINVENTORY_DLG:
	case NNEWINVENTORY_HORSE_DLG:
	case NNEWINVENTORY_BAG0_DLG:
	case NNEWINVENTORY_BAG1_DLG:
		{
			switch( pclClickAndDrop_Item->m_siDstControlID )
			{
			case NNEWEQUIPWINDOW_DLG_LISTVIEW1:		{		siDestination = PERSONITEM_HELMET;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW2:		{		siDestination = PERSONITEM_ARMOUR;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW3:		{		siDestination = PERSONITEM_WEAPON1;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW4:		{		siDestination = PERSONITEM_NECK;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW5:		{		siDestination = PERSONITEM_RING1;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW6:		{		siDestination = PERSONITEM_RING2;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW7:		{		siDestination = PERSONITEM_BELT;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW8:		{		siDestination = PERSONITEM_SHOES;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW9:		{		siDestination = PERSONITEM_WEAPON2;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW10:	{		siDestination = PERSONITEM_MANTLE;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW11:	{		siDestination = PERSONITEM_BAG;			}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW12:	{		siDestination = PERSONITEM_HAT;			}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW13:	{		siDestination = PERSONITEM_DRESS;		}	break;
			case NNEWEQUIPWINDOW_DLG_LISTVIEW14:	{		siDestination = PERSONITEM_BAG_SUB;		}	break;
			}

			if( siDestination >= PERSONITEM_HELMET &&
				siDestination <= PERSONITEM_RESERVED1 )	
			{
				if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
				{
					if( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[siDestination].siUnique <= 0)
						MoveItem(pclClickAndDrop_Item->m_siPara1, siDestination);
					else
						ChangeItem(pclClickAndDrop_Item->m_siPara1, siDestination);
					return true;
				}
				else
				{
					MoveItem(pclClickAndDrop_Item->m_siPara1, siDestination);
					return true;
				}
			}
		}
		break;
	}

	return false;
}

void CNEquipWindow::SelectButtonChangeState( SI32 siSelectIndex, bool bOtherButtonFalse/* =false  */)
{
	if ( (0 > siSelectIndex) || (EWV_MAX_SELECTBUTTON_NUM <= siSelectIndex) )
	{
		return;
	}

	for ( SI32 siIndex=0; siIndex<EWV_MAX_SELECTBUTTON_NUM; siIndex++ )
	{
		// ���õǾ��� ��ư
		if ( siSelectIndex == siIndex )
		{
			m_pButton[ siIndex ]->SetFontColor(CONTROLLER_BUTTONTEXT_COLOR);
			m_pButton[ siIndex ]->SetFontWeight(FW_BOLD);
			m_pButton[ siIndex ]->Refresh();
		}
		// �׿��� ��ư��
		else
		{
			m_pButton[ siIndex ]->SetFontColor(CONTROLLER_BACK_BUTTONTEXT_COLOR);
			m_pButton[ siIndex ]->SetFontWeight( FW_NORMAL );
			// ��ư�� ��� ���ϰ� �ؾ� �Ѵٸ�
			if ( true == bOtherButtonFalse )
			{
				m_pButton[ siIndex ]->Enable( false );
			}

			m_pButton[ siIndex ]->Refresh();
		}
	}
	
}

void CNEquipWindow::OnButtonSummonSelect( SI32 siSelectIndex )
{
	if ( (EWV_SUMMON_1_SELECTBUTTON > siSelectIndex) || (EWV_SUMMON_3_SELECTBUTTON < siSelectIndex) )
	{
		return;
	}

	// ��ư�� Ȱ��ȭ�� �Ǿ ��ȯ���� ��¥ �ִ��� �˻�
	SI16			siSummonIndex	= (siSelectIndex - 1); // ��ȯ���� 0���� ����
	cltCharCommon*	pclChar			= pclClient->pclCM->CR[1];
	if ( NULL == pclChar )
	{
		return;
	}

	cltSummon*		pclSummon		= pclChar->pclCI->clSummonInfo.GetSummon( siSummonIndex );
	if ( NULL == pclSummon )
	{
		return;
	}

	if( pclSummon->siKind <= 0 || pclSummon->siKind > MAX_KIND_NUMBER )
	{
		return;
	}

	m_siCurrentSummonIndex = siSummonIndex;

	LoadItemData();

	SelectButtonChangeState( siSelectIndex );
}

void CNEquipWindow::OnButtonUpListView( CListView* pListView )
{
	if ( pListView == NULL )
	{
		return;
	}

	cltClient* pclclient	= (cltClient*)pclClient;
	if ( NULL == pclclient )
	{
		return;
	}

	SI16 siSelectedIndex	= pListView->GetSelectedItemIndex();
	SI16 siSelectItemUnique	= 0;

	// ����κ�
	if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
	{
		if ( (0 > siSelectedIndex) || ( MAX_PERSON_NUMBER <= siSelectedIndex) )
		{
			return;
		}
		siSelectItemUnique = m_pclInventoryItem[ siSelectedIndex ].siUnique;
	}
	// ��ȯ�� �κ�
	else
	{
		if ( (0 > siSelectedIndex) || ( MAX_SHAPE_ITEM <= siSelectedIndex) )
		{
			return;
		}
		siSelectItemUnique = m_pclEquipItem[ siSelectedIndex ].siUnique;
	}


	if ( siSelectedIndex >= 0 && siSelectedIndex == m_siSelectedIndex && siSelectItemUnique > 0 )
	{	
		m_siSelectedIndex = siSelectedIndex;

		SI32 GlobalImageIndex;
		SI32 GlobalImageFont;
		if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( siSelectItemUnique, &GlobalImageIndex, &GlobalImageFont ) )
		{
			pclClient->pclItemManager->PlaySound( siSelectItemUnique, ITEMSOUND_SELECT );
			pclclient->m_pInterfaceMgr->ItemBeginDrag( GlobalImageIndex, GlobalImageFont );
		}
	}
	else
	{
		m_siSelectedIndex = -1;
	}

}