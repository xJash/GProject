#include "NNewInventory.h"

#include "../../ninterface/nnewmakeitem/NNewMakeItemDlg.h"
#include "../../ninterface/NSelectItemCountDlg/NSelectItemCountDlg.h"
#include "../../ninterface/ngachadlg/NGachaDlg.h"

#include "../../Inventory/ItemInventoryBuffer.h"

#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../InterfaceMgr/Interface/Static.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/ListView.h"
#include "../../InterfaceMgr/Interface/Button.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"
#include "../../InterfaceMgr/Interface/ChatTabButton.h"

#include "../../InterfaceMgr/ControllerSurfaceObj.h"

#include "../../InterfaceMgr/InterfaceMgr.h"
#include "../../InterfaceMgr/InterfaceImgMgr/InterfaceImgMgr.h"

#include "../../InterfaceMgr/InterfaceFile.h"

#include "../../Client/Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../../Client/NInterface/NCharStatus/NCharStatus.h"
#include "../../Client/NInterface/NCharStatus/NEquipWindow.h"
#include "../../Client/ninterface/NTreasureBoxDlg/NTreasureBoxDlg.h"
#include "../../Client/ninterface/NOpenBigItemBoxDlg/NOpenBigItemBoxDlg.h"
#include "../../Client/ninterface/NMySummonDlg/NMySummonDlg.h"

#include "../../../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"

//#include "../../Client/NInterface/NCharStatus/NCharEquipWindow.h"

//#include "../Client/NInterface/NTutorialDlg/NTutorialDlg.h"
#include "../Client/ninterface/NArtifactDlg/NArtifactBaseDlg.h"
#include "../Client/ninterface/NElixirDlg/NElixirUseDlg.h"
#include "../Client/ninterface/NNewSelectBoxDlg/NNewSelectBoxDlg.h"

#include "../Client/ninterface/nnpcrepairdlg/NNewNPCRepair.h"
#include "../Client/ninterface/nnewmakeitem/NItemRepair.h"
#include "../Client/ninterface/nnewmakeitem/NNewMakeItemDlg.h"

#include "../Client/Interface/NHalloweenSpiritBox/NHalloweenSpiritBox.h"

#include "../CommonLogic/Msg/MsgType-Quest.h"
#include "../CommonLogic/MsgType-Item.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/Msg/MsgType-ItemMall.h"
#include "../CommonLogic/BoxItemMgr/BoxItemMgr.h"
//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"
#include "../Server/GachaManager/GachaManager.h"
#include "../Server/Gacha2Manager/Gacha2Manager.h"

#include "../../Client/Client.h"	
extern cltCommonLogic* pclClient;

// �� ����� ����Ʈ�� ��� �̹��� ���� ���� ���� �ȵ�����, ��Ʈ(=index)�� ����Ǿ�� ������...
#define INVENTORY_TAB_IMAGE_FONT_INDEX_PERSON	15
#define INVENTORY_TAB_IMAGE_FONT_INDEX_HORSE	13
#define INVENTORY_TAB_IMAGE_FONT_INDEX_BAG		17

// �ٸ� �κ��丮�� ������ �̵��� ������ ���ð��� ��𿡼� �Դ��� �˱� ����..
#define INVEN_FROM_PERSON					0
#define INVEN_FROM_HORSE					1
#define INVEN_FROM_BAG0						2
#define INVEN_FROM_BAG1						3

SI16 CNNewInventory::m_siSelectedIndex = -1;
bool CNNewInventory::m_bMax = false;
bool CNNewInventory::m_bMini = false;
cltMakeItemContainer CNNewInventory::clMakeItemContainer;

CNNewInventory::CNNewInventory() : CDialogController()
{
	m_bMakeButton = false;
	//m_siSelectedIndex = -1;
	m_siCurrentSummonIndex = SELECTED_HUMAN;
	m_siCurrentInventoryIndex = TAB_SELECTED_PERSON;
	m_siComboBoxSelectedIndex = -1;
	m_siLastSelectInventoryIndex = -1;

	m_pMakeableItemList = NULL;
	m_siMakeableItemNum = 0;

	m_bHorseHave = false;
	m_bBagHave = false;
	m_bClickChangeItem = false;
	m_bStatusChanged = false;
	m_pclInventoryItem = NULL;
	m_pBuffer = new CItemInventoryBuffer();

	m_pMakeItemBtn = NULL;
	m_pEnchantItemBtn = NULL;
	m_pButtonSpaceBox = NULL;
	//m_pMakeItemComboBox = NULL;
	//m_pMakeItemStatic = NULL;
	m_pWeightStatic	= NULL;
	//m_pMakeItemInputEdit = NULL;

	m_pInventoryListView = NULL;
	m_pMoveItemToHorseListView = NULL;
	m_pMoveItemToBag0ListView = NULL;
	m_pMoveItemToBag1ListView = NULL;

	m_pButtonMini = NULL;
	m_pButtonMax = NULL;
	//m_pButtonManInventory = NULL;
	//m_pButtonHorseInventory = NULL;
	//m_pButtonBagInventory = NULL;



	m_pStatic[0] = NULL;
	m_pStatic[1] = NULL;
	m_pStatic[2] = NULL;

	SetActionTimer( 1000 );
}

CNNewInventory::~CNNewInventory()
{
	if ( m_pBuffer )
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}

	if ( m_pclInventoryItem )
	{
		delete [] m_pclInventoryItem;
		m_pclInventoryItem = NULL;
	}

	if ( m_pWeightStatic )
	{
		delete m_pWeightStatic;
		m_pWeightStatic = NULL;

	}

	if ( m_pMakeItemBtn )
	{
		delete m_pMakeItemBtn;
		m_pMakeItemBtn = NULL;
	}

	if ( m_pEnchantItemBtn )
	{
		delete	m_pEnchantItemBtn;
		m_pEnchantItemBtn = NULL;
	}


	if ( m_pInventoryListView )
	{
		delete m_pInventoryListView;
		m_pInventoryListView = NULL;
	}

	SAFE_DELETE( m_pItemmallListBtn );
	SAFE_DELETE( m_pButtonSpaceBox );

	SAFE_DELETE( m_pMoveItemToHorseListView );
	SAFE_DELETE( m_pMoveItemToBag0ListView );
	SAFE_DELETE( m_pMoveItemToBag1ListView );

	if ( m_pMakeableItemList )
	{
		delete [] m_pMakeableItemList;
		m_pMakeableItemList = NULL;
	}


	SAFE_DELETE( m_pButtonMini );
	SAFE_DELETE( m_pButtonMax );
	//SAFE_DELETE(m_pButtonManInventory );
	//SAFE_DELETE(m_pButtonHorseInventory );
	//SAFE_DELETE(m_pButtonBagInventory );

	SAFE_DELETE(m_pStatic[0]);
	SAFE_DELETE(m_pStatic[1]);
	SAFE_DELETE(m_pStatic[2]);

}

void CNNewInventory::Create()
{
	
	if ( IsCreate() )
		return;

	CInterfaceFile file;

	file.LoadFile(TEXT("NInterface/Data/NNewInventoryDlg/DLG_NewInventory.ddf"));
	file.CreatePopupDialog( this, NNEWINVENTORY_DLG, TEXT("dialog_NewInventory"), StaticCallBackDialogNNewInventory );

	cltClient *pclclient = (cltClient *)pclClient;

	MovePos( pclclient->GetScreenXSize() - 218, 250 );


	int i = 0;

	m_pclInventoryItem = new cltItem[ MAX_ITEM_PER_PERSON ];
	memset( m_pclInventoryItem, 0, sizeof( cltItem ) * MAX_ITEM_PER_PERSON );



	NEWCBUTTON(m_pMakeItemBtn);
	NEWCBUTTON(m_pEnchantItemBtn);
	NEWCBUTTON(m_pItemmallListBtn);
	NEWCBUTTON(m_pButtonSpaceBox);			//[�߰� : Ȳ���� 2008. 1. 29 => ���� ����. ��ư �޸� Ȯ��]
	NEWCSTATIC(m_pWeightStatic);

	NEWCLISTVIEW(m_pInventoryListView);
	NEWCLISTVIEW(m_pMoveItemToHorseListView);
	NEWCLISTVIEW(m_pMoveItemToBag0ListView);
	NEWCLISTVIEW(m_pMoveItemToBag1ListView);

	NEWCBUTTON(m_pButtonMini);
	NEWCBUTTON(m_pButtonMax);

	//m_pButtonManInventory = new CChatTabButton(this);
	//m_pButtonHorseInventory = new CChatTabButton(this);
	//m_pButtonBagInventory = new CChatTabButton(this);

	NEWCSTATIC(m_pStatic[0]);
	NEWCSTATIC(m_pStatic[1]);
	NEWCSTATIC(m_pStatic[2]);


	file.CreateControl( m_pItemmallListBtn, NNEWINVENTORY_DIALOG_ITEMMALL_BUTTON, TEXT("button_NONAME3"));
	file.CreateControl( m_pEnchantItemBtn, NNEWINVENTORY_DIALOG_ENCHANTITEM_BUTTON, TEXT("button_NONAME4")); 
	file.CreateControl( m_pMakeItemBtn, NNEWINVENTORY_DIALOG_MAKEITEM_BUTTON, TEXT("button_NONAME5")); 
	
	file.CreateControl( m_pWeightStatic, NNEWINVENTORY_DIALOG_WEIGHT_STATIC, TEXT("statictext_weight"));

	file.CreateControl( m_pInventoryListView, NNEWINVENTORY_DIALOG_INVENTORY_LISTVIEW, TEXT("listview_NONAME1")); 
	file.CreateControl( m_pMoveItemToHorseListView, NNEWINVENTORY_DIALOG_MOVEITEMTOHORSE_LISTVIEW, TEXT("listview_NONAME2")); 
	file.CreateControl( m_pMoveItemToBag1ListView, NNEWINVENTORY_DIALOG_MOVEITEMTOBAG1_LISTVIEW, TEXT("listview_NONAME3")); 
	file.CreateControl( m_pMoveItemToBag0ListView, NNEWINVENTORY_DIALOG_MOVEITEMTOBAG0_LISTVIEW, TEXT("listview_NONAME4")); 

	file.CreateControl( m_pButtonMini, NNEWINVENTORY_DIALOG_BUTTON1, TEXT("button_NONAME1"));
	file.CreateControl( m_pButtonMax, NNEWINVENTORY_DIALOG_BUTTON2, TEXT("button_NONAME2")); 

	// [�߰� : Ȳ���� 2008. 1. 29 => ���� ����.  ��ư���� .]
	file.CreateControl( m_pButtonSpaceBox, NNEWINVENTORY_DIALOG_BUTTON_SPACE_BOX, TEXT("button_space_box")); 
	
	//file.CreateControl( m_pButtonManInventory, NNEWINVENTORY_DIALOG_BUTTON2, TEXT("button_NONAME2")); 
	//file.CreateControl( m_pButtonHorseInventory, NNEWINVENTORY_DIALOG_BUTTON3, TEXT("button_NONAME3")); 
	//file.CreateControl( m_pButtonBagInventory, NNEWINVENTORY_DIALOG_BUTTON4, TEXT("button_NONAME4")); 

	file.CreateControl( m_pStatic[0], NNEWINVENTORY_DIALOG_STATIC1, TEXT("statictext_NONAME1")); 
	file.CreateControl( m_pStatic[1], NNEWINVENTORY_DIALOG_STATIC2, TEXT("statictext_NONAME2")); 
	file.CreateControl( m_pStatic[2], NNEWINVENTORY_DIALOG_STATIC3, TEXT("statictext_NONAME3"));

	m_pStatic[0]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_HORSE );
	m_pStatic[1]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_BAG );
	m_pStatic[2]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_BAG );


	// [�߰� : Ȳ���� 2008. 1. 29 => ���� ����. �κ����� ��ư�� ��ġ ������ ����.]
	if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
	{
		m_pButtonMini->SetFileName("NInterface/Button/BUTTON_Min_Max_24X38_00_000.SPR");
		m_pButtonMini->SetX( m_pButtonMini->GetX() - 3);
		m_pButtonMax->Show( false );	// �ִ�ȭ ��ư�� ������� �����Ƿ� �Ⱥ��̰�.
		
		SI16 Space = 44; 
		m_pMakeItemBtn->SetY( m_pButtonMax->GetY() );
		m_pEnchantItemBtn->SetY( m_pMakeItemBtn->GetY()	    + Space );
		m_pItemmallListBtn->SetY( m_pEnchantItemBtn->GetY() + Space );
		m_pButtonSpaceBox->SetY(m_pItemmallListBtn->GetY()	+ Space );
	}
	else
	{
		m_pButtonSpaceBox->Show( false );
	}
	//[����]�������ϰ�� ��Ʈũ�� �ø� - �ѱ��߰� By LEEKH
	if( pclClient->IsWhereServiceArea(ConstServiceArea_English 
									| ConstServiceArea_Korea 
									| ConstServiceArea_USA 
									| ConstServiceArea_NHNChina 
									| ConstServiceArea_EUROPE) 
	)
	{
		m_pWeightStatic->SetFontSize(11);
	}
	else
	{
		m_pWeightStatic->SetFontSize(10); 
	}

	TCHAR* pText = GetTxtFromMgr(5067); //  "����ǰ( alt+i)"
	SetTitle(pText,CONTROLLER_TITLE_COLOR,11);

	if ( GetDialogControllerID() != NNEWINVENTORY_DLG  )
	{
        m_pWeightStatic->Show( false );
	}

	if ( pclclient->siServiceArea == ConstServiceArea_China )
	{
		ShowSlotNum();
	}
	else
	{
		ShowInvenWeight();
	}


	m_pCloseButton->SetFileName(TEXT("NInterface/common/Common_12x12_00_000.SPR"));

	SetTimerOnOff( true );

	CDialogController::Show( false );

	return;
}

void CALLBACK CNNewInventory::StaticCallBackDialogNNewInventory( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl )
{
 	CNNewInventory *pThis = (CNNewInventory *)pControllerMgr;
	pThis->CallBackDialogNNewInventory( nEvent, nControlID, pControl );
}

void CALLBACK CNNewInventory::CallBackDialogNNewInventory( UINT nEvent, int nControlID, CControllerObj* pControl )
{
	cltClient *pclclient = (cltClient *)pclClient;
	
	CControllerMgr *pDialog = NULL;
	CControllerObj *pControllerObj = NULL;

	if ( pclclient->m_pInterfaceMgr->GetControllerAtPoint( &pDialog, &pControllerObj ) == true )
	{
		if ( pDialog->GetDialogControllerID() != GetDialogControllerID()  && pControllerObj != NULL)
		{
			((CNNewInventory*)pDialog)->CallBackDialogNNewInventory( nEvent, pControllerObj->GetControllerID(), pControllerObj );
		}
	}


	switch ( nControlID )
	{
	// [�߰� : Ȳ���� 2008. 1. 29 => ���� ���� â Ŭ������ ����.]
	case NNEWINVENTORY_DIALOG_BUTTON_SPACE_BOX:
		{
			pclclient->CreateInterface( NSPACE_BOX );
		}
		break;
	case NNEWEQUIPWINDOW_DLG_LISTVIEW1:
		{
			switch( nEvent )
			{
			case EVENT_LISTVIEW_LBUTTONDOWN:
				{
					int a = 0;
				}
				break;
			}
		}
		break;
	case COMMON_DIALOG_CLOSEBUTTON:
		{
			Hide();
		}
		break;

		// ����� ��ư
	case NNEWINVENTORY_DIALOG_MAKEITEM_BUTTON:
		{
			// ����â�� ���� ����Ʈ ������ ���
			SI16 questtype, questunique, para1, para2;
			SI16 questclearcond = QUEST_CLEAR_COND_OPENMAKEITEM;
			if(	pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
				&& para1 == clMakeItemContainer.clMatEnchantItem.siUnique )
			{
				cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
				cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
				cltClient* pclclient = (cltClient* )pclClient;
				pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
			}

			if(pclclient->m_pDialog[ NNEWITEMMAKE_DLG ] == NULL)
			{
				pclclient->CreateInterface(NNEWITEMMAKE_DLG);
				pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MENU_CLICK")), 0, 0);

				if( ( pclclient->pclCM->CR[1]->HaveHorse() || 
					pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique > 0 )
					&& m_bMax )
				{
					(pclclient->m_pDialog[ NNEWITEMMAKE_DLG ])->MovePos( 450, 205 );
				}
			}
		}
		break;
		// ��þƮ ��ư
	case NNEWINVENTORY_DIALOG_ENCHANTITEM_BUTTON:
		{
			if(pclclient->m_pDialog[ NNEWITEMMAKE_DLG ] == NULL)
			{
				pclclient->CreateInterface(NNEWITEMMAKE_DLG);
				pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MENU_CLICK")), 0, 0);

				((CNewMakeItemDlg*)pclclient->m_pDialog[ NNEWITEMMAKE_DLG ])->ShowEnchantTab();

				if( ( pclclient->pclCM->CR[1]->HaveHorse() || 
					pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique > 0 )
					&& m_bMax )
				{
					(pclclient->m_pDialog[ NNEWITEMMAKE_DLG ])->MovePos( 450, 205 );
				}
			}
		}
		break;
 
	case NNEWINVENTORY_DIALOG_ITEMMALL_BUTTON:
		{
			if(pclClient->IsCountrySwitch(Switch_PeriodItem))		//	090326 [��ȣ]	�Ⱓ����ư ������ ���� �ɸ� ������ �Ⱓ�� ǥ���ϴ��� �ƴϸ� ���� ���� �������� ITEMMALL && �Ⱓ �� �������� ǥ���ϴ���
			{
				if(pclclient->m_pDialog[ NPERIODITEMLIST_DLG ] == NULL )
				{
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MENU_CLICK")), 0, 0);
					pclclient->CreateInterface(NPERIODITEMLIST_DLG);
					pclclient->m_pDialog[ NPERIODITEMLIST_DLG ]->MovePos( 303, 205 );
				}
			}
			else
			{
				if(pclclient->m_pDialog[ NITEMMALLPRODUCT_DLG ] == NULL )
				{
					pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_MENU_CLICK")), 0, 0);
					pclclient->CreateInterface(NITEMMALLPRODUCT_DLG);
					pclclient->m_pDialog[ NITEMMALLPRODUCT_DLG ]->MovePos( 303, 205 );
				}

			}
		}


	case NNEWINVENTORY_DIALOG_INVENTORY_LISTVIEW:
		{
			switch( nEvent )
			{
			case EVENT_LISTVIEW_DBLCLK:
				{

					pclclient->m_pInterfaceMgr->ItemEndDrag();

					SI16 SelectedIndex = m_pInventoryListView->GetSelectedItemIndex();
					// SI16 LastSelectedIndex = m_pInventoryListView->GetLastSelectedItemIndex();
					EquipItem( SelectedIndex );


				}
				break;
			case EVENT_LISTVIEW_LBUTTONDOWN:
				{
					if ( (true == pclClient->pclCM->CR[1]->bPersonalShopSwitch) || 
						 (true == pclClient->pclCM->CR[1]->bPremiumPersonalShop) )
					{
						cltCharClient* pChar = pclClient->pclCM->GetCharClient(1)	;

						if(pChar != NULL )
						{
							if( pclClient->IsCountrySwitch( Switch_Change_manufacture_request_interface ) )
							{
								if(pChar->siShopMode == PSHOP_MODE_MAKEITEM || pChar->siShopMode == PSHOP_MODE_MAKEITEM_WANT)
								{
									TCHAR* pTitle = GetTxtFromMgr(1891);
									TCHAR* pText = GetTxtFromMgr(20099);	//����/���� �Ƿ� �߿��� �������� �̵��� �Ұ��� �մϴ�.
									pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
									break ;
								}
							}							
						}
						else
						{
							TCHAR* pTitle = GetTxtFromMgr(1891);
							TCHAR* pText = GetTxtFromMgr(10038);
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
							break ;
						}
					}
					
					// ���ο� Ŭ���� ��������� �ƹ� ó���� ���� �ʴ´�.
					if( pclClient->IsCountrySwitch(Switch_ClickAndDrop))
					{
						break;	// case Ż��
					}
					

					if( pclclient->m_pDialog[NSELECTITEMCOUNT_DLG] != NULL )
					{
						(pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->DeleteDialog();
					}

					SI16 SelectedIndex = m_pInventoryListView->GetSelectedItemIndex();
					SI16 LastSelectedIndex = m_pInventoryListView->GetLastSelectedItemIndex();

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
							LastSelectedIndex = personinventory->m_pInventoryListView->GetLastSelectedItemIndex();
							break;
						case NNEWINVENTORY_HORSE_DLG:
							LastSelectedIndex = horseinventory->m_pInventoryListView->GetLastSelectedItemIndex();
							break;
						case NNEWINVENTORY_BAG0_DLG:
							LastSelectedIndex = bag0inventory->m_pInventoryListView->GetLastSelectedItemIndex();
							break;						
						case NNEWINVENTORY_BAG1_DLG:
							LastSelectedIndex = bag1inventory->m_pInventoryListView->GetLastSelectedItemIndex();
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
								POINT pt;
								GetCursorPos( &pt );

								HWND hFindWnd = WindowFromPoint( pt );
								if ( hFindWnd != NULL && hFindWnd == pclclient->GetHwnd() )
								{
									if( ( pclclient->pclItemManager->GetItemAtb( m_pclInventoryItem[ m_siSelectedIndex ].siUnique ) & ITEMATB_OBJECT) == false )
									{
										if ( pclClient->IsCountrySwitch(Switch_DestroyDropItem) )
										{
											/*bool bTemp1 = pclclient->pclItemManager->IsCanDestroyDropItem( m_pclInventoryItem[ m_siSelectedIndex ].siUnique)	;
											bool bTemp2 = m_pclInventoryItem->IsBelonging( pclClient->pclItemManager ) ;*/
											if ( m_pclInventoryItem[ m_siSelectedIndex ].GetItemNum() > 1)
											{
												if ( ((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG]) == NULL )
												{
													pclclient->CreateInterface( NSELECTITEMCOUNT_DLG );
												}
												((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetCountMode( COUNT_MODE_DROPITEM );
												
											}
											else
											{
												DropItem( m_siSelectedIndex );
												
											}
										}
										else{
											if ( ((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG]) == NULL )
											{
												pclclient->CreateInterface( NSELECTITEMCOUNT_DLG );
											}
											((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetCountMode( COUNT_MODE_DROPITEM );
										}
										
									}
									else
									{
										DropItem( m_siSelectedIndex );
									}
									m_pInventoryListView->ClearSelectedItem();
									m_siSelectedIndex = -1;

								}
							}
							else
							{
								if ( pControllerObj )
								{
									SI16 SelectPos				= -1;
									SI16 MakeItemPos			= -1;
									m_siCurrentSummonIndex		= SELECTED_HUMAN;
									

									GetPositionFromControllerID( pControllerObj->GetControllerID(), LastSelectedIndex ,&SelectPos, &MakeItemPos );
									

									// ��� ����â������ �̵��̰� ��� �������� �����ִٸ�
									if ( ((0 <= SelectPos) && (MAX_SHAPE_ITEM > SelectPos)) && (pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ]) )
									{
										// �׶��� ������� ��ȯ������ �Ǵ��غ���
										m_siCurrentSummonIndex = ((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->m_siCurrentSummonIndex;
									}

									

									if ( SelectPos > -1 )
									{

										SI32 siItemUinque =m_pclInventoryItem[m_siSelectedIndex].siUnique; //m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique;
										SI32 ItemType= pclclient->pclItemManager->GetItemType(siItemUinque);
										SI32 siItemType = GetInventoryType(ItemType);

										if(SelectPos==PERSONITEM_WEAPON2 || SelectPos==PERSONITEM_WEAPON1)
										{
											if(ItemType >=ITEMTYPE_SWORD && ItemType <=ITEMTYPE_GUN)
											{
												siItemType = SelectPos;
											}
										}

										if(SelectPos==PERSONITEM_RING1 || SelectPos==PERSONITEM_RING2)
										{
											if(ItemType == ITEMTYPE_RING)
											{
												siItemType = SelectPos;
											}
										}

										if(ItemType == ITEMTYPE_SCROLL || SelectPos>14 )
										{
											siItemType = SelectPos;
										}

										// ����϶�
										if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
										{
											if ( m_pclInventoryItem[ siItemType ].siUnique == 0 )
											{											
												MoveItem( siItemType );
											}
											else if(m_pclInventoryItem[ siItemType ].siUnique != 0 && ItemType != ITEMTYPE_SCROLL)
											{											
												ChangeItem( siItemType );										
											}
											else if ( SelectPos != m_siSelectedIndex )
											{
												m_pInventoryListView->SetFocus(false);
												m_pBuffer->Push( INV_ADD_ITEM, m_siSelectedIndex, siItemType, m_pclInventoryItem[ m_siSelectedIndex ].siUnique, &m_pclInventoryItem[ siItemType ] );
											}

										}
										// ��ȯ�� �϶�
										else
										{
											//if ( pclClient->pclCM->CR[1]->pclCI->clSummonInfo.clItemInfo[ m_siCurrentSummonIndex ].clEquipItem[ SelectPos ].siUnique == 0 )
											{
												MoveItem( SelectPos );
											}
										}

									}
									if( MakeItemPos > 0) //����  in ����
									{
										SI32 siItemUinque =m_pclInventoryItem[m_siSelectedIndex].siUnique; //m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique;
										SI32 ItemType= pclclient->pclItemManager->GetItemType(siItemUinque);									

										if ( m_pclInventoryItem[m_siSelectedIndex].siUnique != 0 ) //ShowItem
										{	
											TCHAR * pTitleText = GetTxtFromMgr(5927); // ���պҰ� ��� �˸�â Ÿ��Ʋ�� �̸� �����صд�.
											TCHAR * pExplain  = NULL;

											if(MakeItemPos ==NEWMAKE_MATERIALFOR_MAKEITEM)
												ShowMaterials(m_siSelectedIndex);
											else if(MakeItemPos ==NEWMAKE_TOOLSFOR_MAKEITEM)
											{
												if ( m_pclInventoryItem[m_siSelectedIndex].IsSealingUp(pclclient->pclItemManager) == true )
												{
													pTitleText = GetTxtFromMgr(5662);
													pExplain = GetTxtFromMgr(5663);	// �к��� �������� ����ϼ���
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText , pExplain);				
												}
												else
													ShowTools(m_siSelectedIndex);
											}

											else if(MakeItemPos ==NEWMAKE_ORIGINALFOR_ENCHANT)
											{
												if (CheckCanPutonItem(m_pclInventoryItem[m_siSelectedIndex].siUnique ) == false)
												{
													pExplain = GetTxtFromMgr(5928);	// ���� ���� ���հ����մϴ�
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText , pExplain);
												}												
												else
													ShowEnchantOrg(m_siSelectedIndex);
											}
											else if(MakeItemPos ==NEWMAKE_MATFOR_ENCHANT)
											{
												SI32 org = pclclient->pclCM->CR[1]->siOrgInvEnchantInx;

												if(org ==0)
												{ 
													pExplain = GetTxtFromMgr(5929);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}
												else if(m_siSelectedIndex == org)
												{
													pExplain = GetTxtFromMgr(5930);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}
												else if (CheckCanPutonItem(m_pclInventoryItem[m_siSelectedIndex].siUnique ) == false)
												{									
													pExplain = GetTxtFromMgr(5928);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}
												else if (m_pclInventoryItem[org].siUnique != m_pclInventoryItem[m_siSelectedIndex].siUnique )
												{
													pExplain = GetTxtFromMgr(5931);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}
												else
													ShowEnchantMat(m_siSelectedIndex);
											}
											else if(MakeItemPos ==NEWMAKE_ELEFOR_ENCHANT)
											{
												// ��� �������� �����Ǿ� ���� �ʴ�
												if( pclclient->pclCM->CR[1]->siOrgInvEnchantInx <= 0)
												{
													pExplain = GetTxtFromMgr(5929);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}
												// ��þƮ �Ӽ� ���� �������� ���λ��¶��
												else if ( (m_pclInventoryItem[m_siSelectedIndex].siUnique == ENCHANT_CHANGE_ELEMENT_ITEMUNIQUE)
													&& (pclClient->pclCM->CR[1]->siOrgInvEnchantInx > 0)
													&& (m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].siUnique > 0)
													&& (m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].GetEnchantType(pclClient->pclItemManager) > 0)
												)
												{
													pTitleText	= GetTxtFromMgr(7940);
													pExplain	= GetTxtFromMgr(7949);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);


													if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
													{
														SI32				siEncnantType	= m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].GetEnchantType(pclClient->pclItemManager);
														CNewMakeItemDlg*	tools			= (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];

														(tools->NewEnchantTab)->SetChangeEnchanteButton(siEncnantType);
													}

													ShowEnchantElem(m_siSelectedIndex);
													
												}

												// �Ӽ��� ���� ��þƮ ��� �������� �����Ǿ��ִ�.
												else if(  pclClient->pclCM->CR[1]->siOrgInvEnchantInx > 0 
													&& m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].siUnique > 0  
													//&& m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].GetEnchantType(pclClient->pclItemManager) > 0  
													)
												{

													SI32 EnchantType = m_pclInventoryItem[pclClient->pclCM->CR[1]->siOrgInvEnchantInx].GetEnchantType(pclClient->pclItemManager);
													if(EnchantType == ENCHANT_TYPE_FIRE_A || EnchantType == ENCHANT_TYPE_FIRE_D) // �ҼӼ� �����
													{
														if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5350) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
														{// �ƴϸ� �߸��� �ƴ����Դϴ� ��� �˷��ش�
															pExplain = GetTxtFromMgr(5932);
															pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
														}
														else
														{
															ShowEnchantElem(m_siSelectedIndex);
														}
													}
													else if(EnchantType == ENCHANT_TYPE_WATER_A || EnchantType == ENCHANT_TYPE_WATER_D) // �ҼӼ� �����
													{
														// ���� ���������� Ȯ���Ѵ�.
														if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5355) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370)  && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
														{// �ƴϸ� �߸��� �ƴ����Դϴ� ��� �˷��ش�
															pExplain = GetTxtFromMgr(5932);
															pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
														}
														else
														{
															ShowEnchantElem(m_siSelectedIndex);
														}
													}
													else if(EnchantType == ENCHANT_TYPE_WIND_A || EnchantType == ENCHANT_TYPE_WIND_D) // �ҼӼ� �����
													{
														// �ٶ� ���������� Ȯ���Ѵ�.
														if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5360) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370)  && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
														{// �ƴϸ� �߸��� �ƴ����Դϴ� ��� �˷��ش�
															pExplain = GetTxtFromMgr(5932);
															pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
														}
														else
														{
															ShowEnchantElem(m_siSelectedIndex);
														}
													}
													else if(EnchantType == ENCHANT_TYPE_GROUND_A || EnchantType == ENCHANT_TYPE_GROUND_D) // �ҼӼ� �����
													{
														// ���� ���������� Ȯ���Ѵ�.
														if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5365) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370)  
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607)
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
														{// �ƴϸ� �߸��� �ƴ����Դϴ� ��� �˷��ش�
															pExplain = GetTxtFromMgr(5932);
															pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
														}
														else
														{
															ShowEnchantElem(m_siSelectedIndex);
														}
													}
													else	
													{
														// �Ӽ��� ���� �������̶�� ������ �߰��� �ȵȴ�.
														if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370)  && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606) 
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607) 
															&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
														{
															pExplain = GetTxtFromMgr(5932);
															pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
														}
														else
														{
															ShowEnchantElem(m_siSelectedIndex);
														}
													}
												}

												else if( m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5350) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5355) 
													&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5360) && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5365)
													&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(5370)  && m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13606)
													&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ITEMUNIQUE(13607) 
													&& m_pclInventoryItem[m_siSelectedIndex].siUnique != ENCHANT_USEDAYPLUS_ITEMUNIQUE )
												{
													pExplain = GetTxtFromMgr(5932);
													pclclient->m_pDialog[NOTIFYMSG_DLG ]->SetText(pTitleText, pExplain);
												}

												else
													ShowEnchantElem(m_siSelectedIndex);
											}	

										}
									}
								}
							}

							m_pInventoryListView->ClearSelectedItem();
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
					//	if( true == m_bClickChangeItem )
					//		break;

					// ���� �������̶�� ������ �̵� �Ұ�

					if ( (true == pclClient->pclCM->CR[1]->bPersonalShopSwitch) || 
						(true == pclClient->pclCM->CR[1]->bPremiumPersonalShop) )
					{
						break ;
					}

					SI16 SelectedIndex = m_pInventoryListView->GetSelectedItemIndex();

					// ���ο� Ŭ�� �� ���
					if(pclClient->IsCountrySwitch(Switch_ClickAndDrop))
					{
						bool bIsSplitMode = false;
						if( GetKeyState(VK_CONTROL) < 0 )
						{
							if( ( pclclient->pclItemManager->GetItemAtb(m_pclInventoryItem[ SelectedIndex ].siUnique) & ITEMATB_OBJECT) == false )
							{
								if ( ((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG]) == NULL )
								{
									pclclient->CreateInterface( NSELECTITEMCOUNT_DLG );
								}
								((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetSelectedItemIndex( SelectedIndex );
								((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetCountMode( COUNT_MODE_SPLITITEM );
								bIsSplitMode = true;
							}
						}
						else if ( SelectedIndex >= 0 && m_pclInventoryItem[ SelectedIndex ].siUnique > 0 )
						{
							// Ŭ�� �� ����� �����ϱ� ���� ������������ üũ�ϰ� �����Ѵ�.
							if ( IsItemDataChanged() )	{			LoadItemData();				}
							pclclient->m_pInterfaceMgr->BeginClickAndDrop_Item(&m_pclInventoryItem[ SelectedIndex ], GetDialogControllerID(), nControlID, SelectedIndex);
						}
					}
					else
					{
						if ( SelectedIndex >= 0 && SelectedIndex == m_siSelectedIndex && m_pclInventoryItem[ SelectedIndex ].siUnique > 0 )
						{	
							m_siSelectedIndex = SelectedIndex;

							bool bIsSplitMode = false;
							if( GetKeyState(VK_CONTROL) < 0 )
							{
								if( ( pclclient->pclItemManager->GetItemAtb(m_pclInventoryItem[ SelectedIndex ].siUnique) & ITEMATB_OBJECT) == false )
								{
									if ( ((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG]) == NULL )
									{
										pclclient->CreateInterface( NSELECTITEMCOUNT_DLG );
									}									
									((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetCountMode( COUNT_MODE_SPLITITEM );
									bIsSplitMode = true;
								}
							}

							if( !bIsSplitMode )
							{
								SI32 GlobalImageIndex;
								SI32 GlobalImageFont;
								if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( m_pclInventoryItem[ SelectedIndex ].siUnique, &GlobalImageIndex, &GlobalImageFont ) )
								{
									pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ SelectedIndex ].siUnique, ITEMSOUND_SELECT );
									pclclient->m_pInterfaceMgr->ItemBeginDrag( GlobalImageIndex, GlobalImageFont );
								}
							}
						}
						else
						{
							m_siSelectedIndex = -1;
						}
					}
				}
				break;
			case EVENT_LISTVIEW_RBUTTONUP:
				{
					SI16 SelectedIndex = m_pInventoryListView->GetSelectedItemIndex();
					if ( SelectedIndex >= 0 && m_pclInventoryItem[ SelectedIndex ].siUnique > 0 )
					{
						/*
						if ( m_pclInventoryItem[ SelectedIndex ].CanRepair( pclClient->pclItemManager ) )
						{
						//		RepairItem( SelectedIndex );
						}
						else*/

						if ( m_pclInventoryItem[SelectedIndex].IsSealingUp(pclClient->pclItemManager) )
						{
							CancellationSealingUp(SelectedIndex);
						}
						else
						{
							UseItem( SelectedIndex );
						}
					}
				}
				break;
			case EVENT_LISTVIEW_RBUTTONDOWN:
				{
					if ( m_siSelectedIndex >= 0 )
					{
						if ( pclclient->m_pInterfaceMgr->IsItemDragMoveStatus() )
						{
							m_pInventoryListView->ClearSelectedItem();
							m_siSelectedIndex = -1;

							pclclient->m_pInterfaceMgr->ItemEndDrag();
						}
					}
				}
				break;
			}
		}
		break;
	case NNEWINVENTORY_DIALOG_BUTTON1:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					// [�߰� : Ȳ���� 2008. 1. 29 => ���� ����. ��ư �ϳ��� �κ� �ִ�, �ּ�ȭ �ǰ�]
					if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
					{
						// �⺻ �����϶� �ִ�ȭ.
						if( false == m_bMax && false == m_bMini )
						{
							// �ִ�ȭ�� �ϴ´� �����̳� ���� ��� �ִ�ȭ �Ұ��� ���ٸ� �ּ�ȭ ��Ų��.
							bool bSet = true;
							if( ( pclclient->pclCM->CR[1]->HaveHorse() == false )  &&
								( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique < 1) && 
								( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique < 1) )
							{
								bSet = false;
							}

							if( bSet ) //�ִ�ȭ
							{
								m_bMax = true;
								ChangeMaxMode( m_bMax );
							}
							else //�ּ�ȭ.
							{
								m_bMax  = false;
								m_bMini = true;
								IsMinimi( m_bMini );  
							}
						}
						// �ּ�ȭ ������ �� �⺻����
						else if( false == m_bMax && true == m_bMini )
						{
							m_bMini = false;
							IsMinimi( m_bMini );
						}
						// �ִ�ȭ ������ �� �ּ� ���·�
						else if( true == m_bMax && false == m_bMini )
						{
							m_bMax  = false;
							m_bMini = true;
							IsMinimi( m_bMini );  
						}
					}
					else
					{
						m_bMini = !m_bMini;
						IsMinimi( m_bMini );
					}
				}
				break;
			}
		}
		break;
	case NNEWINVENTORY_DIALOG_BUTTON2:
		{
			switch( nEvent )
			{
			case EVENT_BUTTON_CLICKED:
				{
					m_bMax = !m_bMax;
					ChangeMaxMode( m_bMax );
				}
				break;
			}
		}
		break;
	}

	return;
}


void CNNewInventory::ShowTools( SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 i = 0;

	//�к������� ������ �ø��� ����.
	//�νĵ� ������ �ø��� ����.e

	SI32 siItemType =pclClient->pclItemManager->GetItemType(m_pclInventoryItem[ Destination ].siUnique);
	if(siItemType != ITEMTYPE_IRON  && siItemType != ITEMTYPE_DISH && siItemType != ITEMTYPE_PAPER) //paper �� �� �� ����
		return;
	cltItem* pclitem = &pclclient->pclCM->CR[1]->pclCI->clCharItem.clItem[ Destination ];
	if(pclitem->IsSealingUp(pclClient->pclItemManager))	return;//�к������� ������ �ø��� ���ϵ��� �Ѵ�.
    	
	for(i = 0; i < 4; i++) //������ �������θ� �ö󰣴�.
	{
		if(clMakeItemContainer.cltools[i].siUnique!=0 && clMakeItemContainer.cltools[i].siUnique == m_pclInventoryItem[ Destination ].siUnique )
		{
			return;
		}
	}

	for(i = 0; i < 4; i++) //�ڸ��� ����� ĭ�� ������ �ø���.
	{
		if(clMakeItemContainer.cltools[i].siUnique == 0 )
		{
			memcpy(&(clMakeItemContainer.cltools[i]), &m_pclInventoryItem[ Destination ], sizeof(cltItem));
			clMakeItemContainer.m_sitools[i] = Destination;
			pclClient->pclCM->CR[1]->siInvMakeItemIndex[i+25] =Destination;

			cltGameMsgRequest_MakeItem_SelectedIndex clGameMsgRequest_MakeItem_SelectedIndex(i+25,Destination);
			cltMsg clMsg(GAMEMSG_REQUEST_MAKEITEMINVINDEX, sizeof(clGameMsgRequest_MakeItem_SelectedIndex), (BYTE*)&clGameMsgRequest_MakeItem_SelectedIndex);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);					
			break;
		}
	}

	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		CNewMakeItemDlg* tools  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
		(tools->NewMakeTab)->ShowTools(clMakeItemContainer.cltools);
	}

	m_pInventoryListView->SetItemDrawAlphaOption(Destination);

	return;
}


void CNNewInventory::ShowMaterials( SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;
	SI32 i = 0;

	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];

	for(i = 0; i < 25; i++)
	{
		SI32 siItemType =pclClient->pclItemManager->GetItemType(m_pclInventoryItem[ Destination ].siUnique);
		if(siItemType == ITEMTYPE_IRON || siItemType == ITEMTYPE_DISH || siItemType == ITEMTYPE_PAPER)
			return;

		if(clMakeItemContainer.clMaterials[i].siUnique!=0 && 
			clMakeItemContainer.clMaterials[i].siUnique == m_pclInventoryItem[ Destination ].siUnique )//�ڵ����� �������� �κ��� ó������ �˻� �ϱ� ������ ����â���� ����
			//�׷��� ����â ��ŭ �ε��� �ں��� �˻� �ؾ� �Ѵ�.,
		{
			return;
		}
	}

	//��Ḧ ������ ���� â�� �÷����� ��ġ�� �̿��ؼ� �����ϴ�. ����ũ�� ��� ���� �ʴ´�

	for(i = 0; i < 25; i++) //�ڸ��� ����� ĭ�� ��Ḧ �ø���.
	{
		if( clMakeItemContainer.clMaterials[i].siUnique == 0 )
		{
			memcpy( &(clMakeItemContainer.clMaterials[i]), &m_pclInventoryItem[ Destination ], sizeof(cltItem));
			clMakeItemContainer.m_siMaterials[i] = Destination;
			pclClient->pclCM->CR[1]->siInvMakeItemIndex[i] =Destination;

			//�ε�����  ���� ����ũ�� ��� ��..
			cltGameMsgRequest_MakeItem_SelectedIndex clGameMsgRequest_MakeItem_SelectedIndex(i,Destination);//(i = ����â �ε���, Destination = �� ������ �κ��ε���)
			cltMsg clMsg(GAMEMSG_REQUEST_MAKEITEMINVINDEX, sizeof(clGameMsgRequest_MakeItem_SelectedIndex), (BYTE*)&clGameMsgRequest_MakeItem_SelectedIndex);
			pclClient->SendMsgToServer((sPacketHeader*)&clMsg);	
			break;
		}
	}

	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
		(NewMakeItem->NewMakeTab)->ShowMaterials(clMakeItemContainer.clMaterials);
	}

	m_pInventoryListView->SetItemDrawAlphaOption(Destination);

	return;
}


void CNNewInventory::ShowEnchantOrg(SI32 Destination) //��æƮâ�� ��æƮ��ų������ �����ֱ�
{
	cltClient *pclclient = (cltClient *)pclClient;

	pclclient->pclCM->CR[1]->siOrgInvEnchantInx = Destination;
	SI32 OrgIndex = pclclient->pclCM->CR[1]->siOrgInvEnchantInx;
	SI32 MatIndex = pclclient->pclCM->CR[1]->siMatInvEnchantInx;


	if( MatIndex == Destination) return;

	//�к������� ������ �ø��� ����.
	//�νĵ� ������ �ø��� ����.

	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];

	//if(clOrgEnchantItem.siUnique == 0 )
	{
		clMakeItemContainer.clOrgEnchantItem.Set( &m_pclInventoryItem[ Destination] );			
		pclClient->pclCM->CR[1]->siOrgInvEnchantInx =Destination;		
	}
	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		CNewMakeItemDlg* tools  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
		(tools->NewEnchantTab)->ShowOrgEnchantItem(clMakeItemContainer.clOrgEnchantItem);
	}

	m_pInventoryListView->SetItemDrawAlphaOption(Destination);

	return;
}
void CNNewInventory::ShowEnchantMat(SI32 Destination) //��æƮâ�� ����������� �����ֱ�
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 OrgIndex = pclclient->pclCM->CR[1]->siOrgInvEnchantInx;
	SI32 MatIndex = pclclient->pclCM->CR[1]->siMatInvEnchantInx;


	if( OrgIndex == Destination) return;



	//�к������� ������ �ø��� ����.
	//�νĵ� ������ �ø��� ����.

	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];


	//if(clMatEnchantItem.siUnique == 0 )
	{
		memcpy(&(clMakeItemContainer.clMatEnchantItem), &m_pclInventoryItem[ Destination ], sizeof(cltItem));		
		pclclient->pclCM->CR[1]->siMatInvEnchantInx = Destination;	
	}


	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		CNewMakeItemDlg* tools  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
		(tools->NewEnchantTab)->ShowMatEnchantItem(clMakeItemContainer.clMatEnchantItem);
	}

	m_pInventoryListView->SetItemDrawAlphaOption(Destination);

	//��þƮ �������� �����ϴ� ����Ʈ�� �������̶��

	SI16 questtype, questunique, para1, para2;
	SI16 questclearcond =  QUEST_CLEAR_COND_SETENCHANTITEM;
	if(pclClient->pclCM->CR[1]->pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
		&& para1 == clMakeItemContainer.clMatEnchantItem.siUnique )
	{
		cltGameMsgRequest_QuestStatus clinfo(questtype, questunique, questclearcond, para1, para2  );
		cltMsg clMsg(GAMEMSG_REQUEST_QUESTSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
		cltClient* pclclient = (cltClient* )pclClient;
		pclclient->SendMsgToServer((sPacketHeader*)&clMsg);
	}


	return;
}

void CNNewInventory::ShowEnchantElem(SI32 Destination) //��æƮâ�� �Ӽ������� �����ֱ�
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 i = 0;

	//�к������� ������ �ø��� ����.
	//�νĵ� ������ �ø��� ����.


	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];

	for(i = 0; i < NOW_ENCHANT_NUMBER; i++) //�������θ� �ö󰣴�.
	{		
		if(clMakeItemContainer.clEleEnchantItem[i].siUnique!=0 && 
			clMakeItemContainer.clEleEnchantItem[i].siUnique == m_pclInventoryItem[ Destination ].siUnique )
		{
			return;
		}
	}


	for(i = 0; i < NOW_ENCHANT_NUMBER; i++) //�ڸ��� ����� ĭ�� ������ �ø���.
	{
		if(clMakeItemContainer.clEleEnchantItem[i].siUnique == 0 )
		{
			memcpy(&(clMakeItemContainer.clEleEnchantItem[i]), &m_pclInventoryItem[ Destination ], sizeof(cltItem));
			//clEleEnchantItem[i] = Destination;
			pclClient->pclCM->CR[1]->siElementEnchantInx[i] =Destination;					
			break;
		}
	}

	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		CNewMakeItemDlg* tools  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
		(tools->NewEnchantTab)->ShowEleEnchantItem(clMakeItemContainer.clEleEnchantItem);
	}

	m_pInventoryListView->SetItemDrawAlphaOption(Destination);

	return;
}

bool CNNewInventory::CheckBag( SI32 siSource, SI32 siDestination )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if(pclclient == NULL)			return false;

	SI32 siBagStart = -1;

	switch(siSource)
	{
	case PERSONITEM_BAG:		siBagStart = PERSONITEM_BAG0;		break;
	case PERSONITEM_BAG_SUB:	siBagStart = PERSONITEM_BAG1;		break;
	default:
		return true;
	}

	if(siBagStart < 0)			return false;

	// �����ϰ� �ִ� ������ ���� �� ��������� ������ ����.
	if( siDestination >= siBagStart && siDestination < siBagStart + MAX_ITEM_PER_BAG )
	{
		TCHAR* pTitle = GetTxtFromMgr(1167);
		TCHAR* pText = GetTxtFromMgr(1168);

		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
		return false;
	}

	// ���濡 ������ �ִٸ� �ű�� �Ұ�
	for ( SI16 t = siBagStart; t < siBagStart + MAX_ITEM_PER_BAG; ++t )
	{
		if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ t ].siUnique > 0 )
		{
			TCHAR* pTitle = GetTxtFromMgr(1165);
			TCHAR* pText = GetTxtFromMgr(1166);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText );
			return false;
		}
	}

	return true;
}


bool CNNewInventory::MoveItem( SI32 siSource, SI32 siDestination )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if(pclclient == NULL)					return false;

	// ���� üũ
	if(CheckBag(siSource, siDestination) == false)			return false;

	// ��ĥ �� ���� �������̸� �ű� �� ����.
	if ( m_pclInventoryItem[ siDestination ].siUnique > 0 )
	{
		if ( m_pclInventoryItem[ siDestination ].CanPile( pclClient->pclItemManager ) == false )
		{
			return false;
		}
	}

	// ����â�� ���� ��� ���� �������� Ȯ�� �Ѵ�.
	if( (siDestination >= PERSONITEM_HELMET  && siDestination <= PERSONITEM_RESERVED1) //|| // ĳ���� ����â
		//(siDestination >= PERSONITEM_SUMMON1EQUIP0 + PERSONITEM_HELMET  && siDestination <= PERSONITEM_SUMMON1EQUIP0 + PERSONITEM_RESERVED1) || // ��ȯ�� ����â
		//(siDestination >= PERSONITEM_SUMMON2EQUIP0 + PERSONITEM_HELMET  && siDestination <= PERSONITEM_SUMMON2EQUIP0 + PERSONITEM_RESERVED1) // ��ȯ�� ����â
		)
	{
		// �к��� �������� ������ �� ����.
		if(m_pclInventoryItem[ siSource ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR*pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return false;		
		}

		// ���� ������ �˻��Ѵ�.
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(m_pclInventoryItem[ siSource ].siUnique);
		if (ref > 0)
		{
			bool bCanEquip = true;
			SI32 siKind = pclClient->pclCM->CR[1]->GetKind();

			bCanEquip = m_pclInventoryItem[ siSource ].IsCorrectPrivateEquip(pclClient->pclItemManager, siKind);
			if (bCanEquip == false)
			{
				TCHAR*pTitle = GetTxtFromMgr(6023);
				TCHAR *pText = GetTxtFromMgr(6024);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				return false;
			}
		}
	}


	SI32 MoveInfo = MAKELONG( siSource, siDestination );
	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ siSource ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_MOVE_ITEM, MoveInfo, &m_pclInventoryItem[ siSource ] );

	return true;
}

bool CNNewInventory::ChangeItem( SI32 siSource, SI32 siDestination )
{
	cltClient *pclclient = (cltClient *)pclClient;
	if(pclclient == NULL)					return false;

	// ���� üũ
	if(CheckBag(siSource, siDestination) == false)			return false;

	SI32 MoveInfo = MAKELONG( siSource, siDestination );

	// ����â�� ���� ��� ���� �������� Ȯ�� �Ѵ�.
	if( (siDestination >= PERSONITEM_HELMET  && siSource <= PERSONITEM_RESERVED1) //|| // ĳ���� ����â
		//(siDestination >= PERSONITEM_SUMMON1EQUIP0 + PERSONITEM_HELMET  && siSource <= PERSONITEM_SUMMON1EQUIP0 + PERSONITEM_RESERVED1) || // ��ȯ�� ����â
		//(siDestination >= PERSONITEM_SUMMON2EQUIP0 + PERSONITEM_HELMET  && siSource <= PERSONITEM_SUMMON2EQUIP0 + PERSONITEM_RESERVED1)  // ��ȯ�� ����â
	)
	{
		if(m_pclInventoryItem[ siDestination ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR *pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return false;		
		}
	}

	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ siSource ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_CHANGE_ITEM, MoveInfo, &m_pclInventoryItem[ siSource ] );

	return false;
}

void CNNewInventory::MoveItem( SI32 Destination )
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

	cltItem clToItem;

	// ����϶�
	if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
	{
		clToItem.Set( &m_pclInventoryItem[ Destination ] );
	}
	// ��ȯ�� �϶�
	else
	{
		clToItem.Set( &pclClient->pclCM->CR[1]->pclCI->clSummonInfo.clItemInfo[m_siCurrentSummonIndex].clEquipItem[Destination] );
	}

	SI32 MoveInfo = MAKELONG( m_siSelectedIndex, Destination );

	if ( clToItem.siUnique != 0 )
	{
		if ( clToItem.CanPile( pclClient->pclItemManager ) == false )
		{
			return;
		}
	}

	if((Destination >= 0  && Destination <= 14 ) || Destination == 82 || Destination == 97 )
	{
		if(m_pclInventoryItem[ m_siSelectedIndex ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR*pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(m_pclInventoryItem[ m_siSelectedIndex ].siUnique);

		if (ref > 0)
		{
			bool bCanEquip = true;
			SI32 siKind = pclClient->pclCM->CR[1]->GetKind();

			bCanEquip = m_pclInventoryItem[ m_siSelectedIndex ].IsCorrectPrivateEquip(pclClient->pclItemManager, siKind);

			if (bCanEquip == false)
			{
				TCHAR*pTitle = GetTxtFromMgr(6023);
				TCHAR *pText = GetTxtFromMgr(6024);

				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
				return;		
			}

		}

	}

	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_MOVE_ITEM, MoveInfo, &m_pclInventoryItem[ m_siSelectedIndex ] );

	return;
}

void CNNewInventory::RepairItem( SI32 SelectedInventoryItemIndex )
{
	if ( m_pclInventoryItem[ SelectedInventoryItemIndex ].CanRepair( pclClient->pclItemManager ) )
	{
		TCHAR* pTitle = GetTxtFromMgr(1141);
		TCHAR* pText = GetTxtFromMgr(1140);


		cltClient *pclclient = ( cltClient * )pclClient;

		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 0 );
		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( SelectedInventoryItemIndex ) + sizeof( cltItem );
		memcpy( TempBuffer, &SelectedInventoryItemIndex, sizeof( SelectedInventoryItemIndex ) );
		memcpy( &TempBuffer[ sizeof( SelectedInventoryItemIndex ) ], &m_pclInventoryItem[ SelectedInventoryItemIndex ], sizeof( cltItem ) );

		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

		return;
	}
}

void CNNewInventory::CancellationSealingUp(SI32 siIndex)
{
	if ( m_pclInventoryItem[ siIndex ].IsSealingUp( pclClient->pclItemManager ) )
	{
		TCHAR* pTitle = GetTxtFromMgr(5661);
		TCHAR* pText = GetTxtFromMgr(5660);

		cltClient *pclclient = ( cltClient * )pclClient;

		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 3 );
		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( siIndex ) + sizeof( cltItem );
		memcpy( TempBuffer, &siIndex, sizeof( siIndex ) );
		memcpy( &TempBuffer[ sizeof( siIndex ) ], &m_pclInventoryItem[ siIndex ], sizeof( cltItem ) );

		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

		return;
	}
}

void CNNewInventory::UseNolimitTicket(SI32 ItemUnique, SI32 Type)
{
	cltDate MaxWarpDate;//���� Ƽ�� ���� ���� �Ѥ�;�̷��� ���ϴ� �����������.
	MaxWarpDate.uiYear = 255;
	MaxWarpDate.uiMonth = 12;
	MaxWarpDate.uiDay = 30;
	SI32 MAX_GAME_DATE = MaxWarpDate.GetDateVary();
	
	//�ʿ� ���� �������� ������ ����	
	//���� �Ⱓ�� ���� Ƽ���� ������� ���¿��� ���ѿ���Ƽ���� ����Ϸ� ������
	if (pclClient->pclCM->CR[1]->pclCI->clBI.bUseNoLimitTicketWarp == true &&
		ItemUnique == ITEMUNIQUE(24102)) {
			//���� Ƽ���� ����ϴ� �Ⱓ ���߿��� ���� ���� Ƽ�� ���Ұ��� �޼����� ������ ���� ��Ų��.
			cltClient *pclclient = ( cltClient * )pclClient;
			TCHAR * pTitle = GetTxtFromMgr(7863);
			TCHAR * pText = GetTxtFromMgr(7864);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText , MSGBOX_TYPE_OK, 5 );
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( ItemUnique );
			memcpy( TempBuffer, &ItemUnique, sizeof( ItemUnique ) );	

			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
	}
	//���ѿ��� Ƽ���� ����Ͽ��� �� �ٽ� ����ϰ� �������
	else if (Type ==NOLIMIT_TICKET &&
		pclClient->pclCM->CR[1]->pclCI->clBI.bUseNoLimitTicketWarp == true &&
		pclClient->pclCM->CR[1]->pclCI->clBI.siNoLimitTicketWarpDateVary == MAX_GAME_DATE){
			cltClient *pclclient = ( cltClient * )pclClient;
			TCHAR * pTitle = GetTxtFromMgr(7863);
			TCHAR * pText = GetTxtFromMgr(7865);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText , MSGBOX_TYPE_OK, 5 );
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( ItemUnique );
			memcpy( TempBuffer, &ItemUnique, sizeof( ItemUnique ) );	

			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
	}
	//�̹� �ٸ� �Ⱓ�� ���� Ƽ���� ����ϰ� �ְ� ���ѿ��� Ƽ���� ����ϰ� ���� ���
	/*
	else if (Type ==NOLIMIT_TICKET &&
		pclClient->pclCM->CR[1]->pclCI->clBI.bUseNoLimitTicketWarp == true&&
		pclClient->pclCM->CR[1]->pclCI->clBI.siNoLimitTicketWarpDateVary < MAX_GAME_DATE){
			cltClient *pclclient = ( cltClient * )pclClient;
			TCHAR * pTitle = GetTxtFromMgr(7863);
			TCHAR * pText = GetTxtFromMgr(7864);
			stMsgBox MsgBox;
			MsgBox.Set( this, pTitle, pText , MSGBOX_TYPE_OK, 5 );
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( ItemUnique );
			memcpy( TempBuffer, &ItemUnique, sizeof( ItemUnique ) );	

			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
		}
	*/
	// �׿��� ��쿡 ���� Ƽ���� ����Ѵ�.(��¥�� �ߺ� �ǹǷ�)
	else{
		TCHAR* pTitle = NULL;
		switch( Type ) {
		case NOLIMIT_TICKET :{
				pTitle = GetTxtFromMgr(4381);
			}break;
		case MARKET_TICKET :{
				pTitle = GetTxtFromMgr(10157);
			}break;
		case SPACEBOX_TICKET:{/// ���� â�� �ڽ�
				pTitle = GetTxtFromMgr(7914);
			}break;
		case SUMMON_SPACE_TICKET:
			{
				// ��ȯ�� ���� ���� Ȯ��
				pTitle = GetTxtFromMgr(8785);
			}break;
		}		
		TCHAR* pText = GetTxtFromMgr(6919);
		TCHAR szBuffer[256];
		szBuffer[0] = 0;
		cltClient *pclclient = ( cltClient * )pclClient;

		const TCHAR* pItemName = pclclient->pclItemManager->GetName(ItemUnique);

		if( pItemName == NULL ) return;

		StringCchPrintf(szBuffer , 256 , pText , pItemName );

		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle, szBuffer , MSGBOX_TYPE_YESNO, 4 );
		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( ItemUnique );
		memcpy( TempBuffer, &ItemUnique, sizeof( ItemUnique ) );	

		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
	}
}


void CNNewInventory::UseWarpTargetWorld(SI32 siItemUnique )
{
	cltClient *pclclient = ( cltClient * )pclClient;

	const TCHAR* pItemName = pclclient->pclItemManager->GetName(siItemUnique);	if( pItemName == NULL ) return;

	TCHAR* pTitle =GetTxtFromMgr(40379);
	NTCHARString256 szExplain(GetTxtFromMgr(40380));	// Ƽ���� ��� �Ͻðڽ��ϱ�? 

	switch( siItemUnique ) 
	{
	case ITEMUNIQUE(24128):
		{			
			szExplain.Replace( "#itemname#" , pItemName )	;
		}
		break;
	}
	stMsgBox MsgBox;
	MsgBox.Set( this, pTitle, szExplain , MSGBOX_TYPE_YESNO, 6 );
	
	BYTE TempBuffer[ 128 ];
	SI16 Size = sizeof( siItemUnique );
	memcpy( TempBuffer, &siItemUnique, sizeof( siItemUnique ) );	

	pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
}
// [����] ���� ���� ���ڿ��� �������� �ش� 
void CNNewInventory::UseLevelLimitBoxOpen(SI32 siItemUnique )
{
	if ( pclClient->IsCountrySwitch(Switch_LevelLimitBox) == false)		return	;
	cltClient *pclclient = ( cltClient * )pclClient;

	const TCHAR* pItemName = pclclient->pclItemManager->GetName(siItemUnique);	if( pItemName == NULL ) return;

	TCHAR* pTitle =GetTxtFromMgr(40379);
	NTCHARString256 szExplain(GetTxtFromMgr(40380));
	szExplain.Replace( "#itemname#" , pItemName )	;

	stMsgBox MsgBox;
	MsgBox.Set( this, pTitle, szExplain , MSGBOX_TYPE_YESNO, 7 );

	BYTE TempBuffer[ 128 ];
	SI16 Size = sizeof( siItemUnique );
	memcpy( TempBuffer, &siItemUnique, sizeof( siItemUnique ) );	

	pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
}
void CNNewInventory::UseItem( SI16 Pos )
{

	cltClient* pclclient = (cltClient*)pclClient;
	if ( m_pclInventoryItem[ Pos ].siUnique == 0 )
	{
		return;
	}

	TCHAR*		pTitle	= GetTxtFromMgr(1143);
	TCHAR*		pText	= NULL;
	
	if ( m_pclInventoryItem[ Pos ].GetType( pclClient->pclItemManager ) == ITEMTYPE_BOOK )
	{
		if( pclClient->pclItemManager->IsItemInfoAtb( m_pclInventoryItem[ Pos ].siUnique, ITEMINFOATB_SKILLBOOK ) )
		{
			if( false == pclClient->IsCountrySwitch( Switch_SkillBook ) )	return;

			// ��ų�� ���� ����å.
			if( pclclient->pclItemManager->pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( m_pclInventoryItem[ Pos ].siUnique ) )
			{
				pText = GetTxtFromMgr(30530);
			}
			// ��ų�� ����å.
			else
			{
				pText = GetTxtFromMgr(30517);
			}
		}
		else
		{
			pText = GetTxtFromMgr(1142); 
		}

		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( Pos ) + sizeof( cltItem );
		memcpy( TempBuffer, &Pos, sizeof( Pos ) );
		memcpy( &TempBuffer[ sizeof( Pos ) ], &m_pclInventoryItem[ Pos ], sizeof( cltItem ) );
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
	}
	// �ڽ� �������� ��� ���⿡�� üũ �� ��밡������ �Ǵ�
	else if ( (pclClient->m_pclBoxItemMgr) && (TRUE == pclClient->m_pclBoxItemMgr->IsNormalBoxItem(m_pclInventoryItem[ Pos ].siUnique)) )
	{
		if ( !pclclient->m_pDialog[ NTREASUREBOX_DLG ] )
		{
			pclclient->CreateInterface(NTREASUREBOX_DLG);
		}

		if( ((CNTreasureBoxDlg*)pclclient->m_pDialog[NTREASUREBOX_DLG])->CanDraw() )
		{
			((CNTreasureBoxDlg*)pclclient->m_pDialog[NTREASUREBOX_DLG])->SetTreasureBox( Pos, &m_pclInventoryItem[ Pos ], m_pBuffer );
		}
	}
// [����] ���� ���� ���ڿ��� �������� �ش� 
	else if( pclClient->IsCountrySwitch(Switch_LevelLimitBox) 
		&& pclClient->pclItemManager->pclRewardItemLimitLevelForChina != NULL 
		&& pclClient->pclItemManager->pclRewardItemLimitLevelForChina->IsRewardBox_Unique( m_pclInventoryItem[ Pos ].siUnique ) ) 
	{
		UseLevelLimitBoxOpen(m_pclInventoryItem[ Pos ].siUnique)	;
	}
	else
	{	
		// [����] ������ ��� if -> switch�� ����
		switch ( m_pclInventoryItem[ Pos ].siUnique )
		{
			//----------------------------------------------------------------------------------------------------
			// Ʈ���� �ڽ�
			case ITEMUNIQUE(7975):	// �߱�å����
			case ITEMUNIQUE(13002):	// �縻
			case ITEMUNIQUE(13005):	// Ȳ�ݾ�
			case ITEMUNIQUE(13015):	// �������
			case ITEMUNIQUE(13021):	// ������
			case ITEMUNIQUE(13028):	// �����
			case ITEMUNIQUE(13300):	// ��������
			case ITEMUNIQUE(13301):	// ƾƾ����
			case ITEMUNIQUE(13302):	// Ű�޶� ����
			case ITEMUNIQUE(13303):	// ����� ����
			case ITEMUNIQUE(13304):	// å����
			case ITEMUNIQUE(13305):	// �Ŀ��� ����
			case ITEMUNIQUE(13306):	// ���̵����
			case ITEMUNIQUE(13307):	// �ٷ¹���
			case ITEMUNIQUE(13308):	// ���߷¹���
			case ITEMUNIQUE(13309):	// ����¹���
			case ITEMUNIQUE(13310):	// ���¹���
			case ITEMUNIQUE(13311):	// �����ֹ���
			case ITEMUNIQUE(13312):	// ������
			case ITEMUNIQUE(13313):	// �׸���������
			case ITEMUNIQUE(13314):	// ��������
			case ITEMUNIQUE(13315):	// ������
			case ITEMUNIQUE(13316):	// �ų�������
			//case ITEMUNIQUE(13317):	// ���� ����
			case ITEMUNIQUE(13318):	// ���ڻ���
			case ITEMUNIQUE(13319):	// ĵ�����
			case ITEMUNIQUE(13320):	// ��������
			case ITEMUNIQUE(13321):	// �ݺ�����
			case ITEMUNIQUE(13322):	// ������ ����
			case ITEMUNIQUE(13323):	// �絹������
			case ITEMUNIQUE(13324):	// �븸����
			case ITEMUNIQUE(13326):	// ��λ���
			case ITEMUNIQUE(13327):	// ���λ���
			case ITEMUNIQUE(13328):	// ���
			case ITEMUNIQUE(13329):	// �ų����(��Ű����)
			//case ITEMUNIQUE(13330):	// ����� ���� ����  (��í)
			case ITEMUNIQUE(13331):	// // [����] 2�����ָӴ� 2008.06.30 ( ��í)
			case ITEMUNIQUE(13333):	// ���� ���� ����.
			case ITEMUNIQUE(13332):	// ȣ���Ǻ�����
			case ITEMUNIQUE(13335):	// [����] ��̳ʸ�(USA) 1�ֳ� ��� ���� ����  => 2008-9-25
			case ITEMUNIQUE(13336):	// �̺� ����.
			case ITEMUNIQUE(13337):	// ���� ���� ����.
			//case ITEMUNIQUE(13338):	// Christmas Spirit BOX
			case ITEMUNIQUE(13342):	// ���ֻ���
			case ITEMUNIQUE(13341):	// ������ �Ǻ� ����
			//case ITEMUNIQUE(13343): // ���� ���Ǹ� ���� (�˻罺�Ǹ�,�ųʽ��Ǹ�)
			case ITEMUNIQUE(13344): // �ƹ�Ÿ ����
			case ITEMUNIQUE(13346):	// ��ȥ���� ����
			case ITEMUNIQUE(13347):	// ���� �蹶ġ
			case ITEMUNIQUE(13348): // ��ȥ�� ���� ����
			case ITEMUNIQUE(13350): // ���ڴ� �Ŀ��� ����
			case ITEMUNIQUE(13351): // �߱� pc�� ����
			//case ITEMUNIQUE(13352):	// ���� ���Ǹ� ����
			case ITEMUNIQUE(13349):	// �߱� ��õ�� ����	
			//case ITEMUNIQUE(13357):	// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
			case ITEMUNIQUE(13358):	// 2010�ų��̺�Ʈ - ���� ���� �� �ִ� ����.
			case ITEMUNIQUE(13063):	// 2010�ų��̺�Ʈ - ������Ű
			case ITEMUNIQUE(13359):	// [���] 3�� ���ָӴ� (2009.11.26)
			case ITEMUNIQUE(13360):	// EVENT ITEM ���� ����
			case ITEMUNIQUE(13361):	// ����å����
			case ITEMUNIQUE(13362):	// ���å����
			case ITEMUNIQUE(13363):	// ����å����
			case ITEMUNIQUE(13364):	// �Ǹ� �Ǻ� ����.
				{
					if ( !pclclient->m_pDialog[ NTREASUREBOX_DLG ] )
					{
						pclclient->CreateInterface(NTREASUREBOX_DLG);
					}

					if( ((CNTreasureBoxDlg*)pclclient->m_pDialog[NTREASUREBOX_DLG])->CanDraw() )
					{
						((CNTreasureBoxDlg*)pclclient->m_pDialog[NTREASUREBOX_DLG])->SetTreasureBox( Pos, &m_pclInventoryItem[ Pos ], m_pBuffer );
					}
				}
				break;

			//----------------------------------------------------------------------------------------------------
			// ��ڻ���
			case ITEMUNIQUE(13325):
				{
					if ( !pclclient->m_pDialog[ NOPENBIGITEMBOX_DLG ] )
					{
						pclclient->CreateInterface(NOPENBIGITEMBOX_DLG);
					}
					((CNOpenBigItemBoxDlg*)pclclient->m_pDialog[NOPENBIGITEMBOX_DLG])->SetBigItemBox( Pos, &m_pclInventoryItem[ Pos ] );
				}
				break;

			//----------------------------------------------------------------------------------------------------
			// �ų����
			case ITEMUNIQUE(13340):
				{
					// â�� ���� ������ �ݴ´�
					if ( pclclient->m_pDialog[NEWSELECTBOX_DLG] )
					{
						pclclient->DestroyInterface( pclclient->m_pDialog[NEWSELECTBOX_DLG] );
					}

					pclclient->CreateInterface(NEWSELECTBOX_DLG);

					((CNNewSelectBoxDlg*)pclclient->m_pDialog[NEWSELECTBOX_DLG])->OpenNewSelectBox( m_pclInventoryItem[ Pos ].siUnique );
					
				}
				break;

			//----------------------------------------------------------------------------------------------------
			case ITEMUNIQUE(24114):
				{
					if ( !pclclient->m_pDialog[ CLTNCHARNAMECHANGE_DLG ] )
					{
						pclclient->CreateInterface(CLTNCHARNAMECHANGE_DLG);
					}
				}
				break;

			//----------------------------------------------------------------------------------------------------
			// ����Ƽ��
			case ITEMUNIQUE(24094):
			case ITEMUNIQUE(24096):
			case ITEMUNIQUE(24097):
			case ITEMUNIQUE(24098):
			case ITEMUNIQUE(24102):	// ���� ���� Ƽ��
			case ITEMUNIQUE(24126):	// �����̵������7��(EVENT)
			case ITEMUNIQUE(24129): // Goonzu Enent Item - Item Unique 24094�� ���� ���.
				{
					UseNolimitTicket(m_pclInventoryItem[ Pos ].siUnique, NOLIMIT_TICKET );
				}
				break;

			//----------------------------------------------------------------------------------------------------
			case ITEMUNIQUE(24099):
				{
					UseNolimitTicket(m_pclInventoryItem[ Pos ].siUnique, MARKET_TICKET );
				}
				break;

			//----------------------------------------------------------------------------------------------------
			// ��������
			case ITEMUNIQUE(24111):	// 1�� ���� ���ڻ��Ƽ��
			case ITEMUNIQUE(24112):	// 7�� ���� ���ڻ��Ƽ��
			case ITEMUNIQUE(24113):	// 30�� ���� ���ڻ��Ƽ��
			case ITEMUNIQUE(24127):	// 30�� ���� ���ڻ��Ƽ��(EVENT)
			case ITEMUNIQUE(24131):	// 1�� ���� ���� ���Ƽ�� GE
				{
					UseNolimitTicket(m_pclInventoryItem[ Pos ].siUnique, SPACEBOX_TICKET );
				}
				break;
			case ITEMUNIQUE(24128):	// �������� �̵�
				{
					//�����̸� ���Ұ���
					if ( pclclient->pclCM->CR[1]->clInnerStatus.IsStatus(INNERSTATUS_PRISON))
					{
						TCHAR* pTitle = GetTxtFromMgr(836);
						TCHAR* pText = GetTxtFromMgr(6033);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,pText);
						return ;
					}
					else if( pclclient->pclCM->CR[1]->bPersonalShopSwitch == true || 
						pclclient->pclCM->CR[1]->bPremiumPersonalShop == true )
					{
						TCHAR* pTitle = GetTxtFromMgr(836);
						TCHAR* pText = GetTxtFromMgr(8283);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle,pText);
						return ;
					}
					UseWarpTargetWorld(m_pclInventoryItem[ Pos ].siUnique)	;

				}break	;

			//----------------------------------------------------------------------------------------------------
			// ����
			case GACHA_GOLDKEY_ITEMUNIQUE:
			case GACHA_SILVERKEY_ITEMUNIQUE:
			case GACHA_BRONZEKEY_ITEMUNIQUE:
			case GACHA_BRONZEKEY_EVENT_ITEMUNIQUE:
			case GACHA_KEYPIECE_ITEMUNIQUE:
				{
					if ( pclClient->IsCountrySwitch(Switch_CarryOverGacha) )
					{
						cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
						if ( (NULL == pclchar) || (false == pclchar->IsBlankInv(1, INVMODE_ALL)) )
						{
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6634) );
							return; 
						}

						pclclient->CreateInterface( NCARRYOVERGACHA_DLG );
					}
					else if( pclClient->IsCountrySwitch(Switch_Gacha_Reform) )
					{
						//[����] �κ��丮�� �� �������� ���� â�� ���� �ʴ´�.
						cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
						if(false == pclchar->IsBlankInv(1, INVMODE_ALL) )
						{
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6634) );
							return; 
						}
						else
						{
							pclclient->CreateInterface(NGACHANEW_DLG);
						}
					}
					else
					{
						pclclient->CreateInterface(NGACHA_DLG);
					}
				}
				break;

			// [����] �̿� ��í ���ɿ���
			case CARRYOVER_GOLDKEY_ITEMUNIQUE:
			case CARRYOVER_SILVERKEY_ITEMUNIQUE:
			case CARRYOVER_BRONZEKEY_ITEMUNIQUE:
				{
					if ( pclClient->IsCountrySwitch(Switch_CarryOverGacha) )
					{
						cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
						if ( (NULL == pclchar) || (false == pclchar->IsBlankInv(1, INVMODE_ALL)) )
						{
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6634) );
							return; 
						}

						pclclient->CreateInterface( NCARRYOVERGACHA_DLG );
					}
				}
				break;

			//----------------------------------------------------------------------------------------------------
			//KHY - 1104 -  ����2 -���� ���� ����. 
			case GACHA2_RACCOONKEY_ITEMUNIQUE:
				{
						//[����] �κ��丮�� �� �������� ���� â�� ���� �ʴ´�.
						cltCharClient* pclchar = pclClient->pclCM->GetCharClient(1);
						if(false == pclchar->IsBlankInv(1, INVMODE_ALL) )
						{
							pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(6634) );
							return; 
						}
						else
						{
							pclclient->CreateInterface(NGACHA2_DLG);
						}
				}
				break;

			//----------------------------------------------------------------------------------------------------
			// ���Žý��� : ����â ����			
			case ITEMUNIQUE(24080):
				{
					if ( false == pclclient->bVoteCampaign )
					{
						TCHAR	*pTitle	= GetTxtFromMgr(5614);
						TCHAR	*pText	= GetTxtFromMgr(8797);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					else
					{
						pclclient->CreateInterface( ELECTIONSTUMP_DLG );
					}
				}
				break;
			
			//----------------------------------------------------------------------------------------------------
			case ITEMUNIQUE(24117):	// ��ȯ�� ���� ���� �߰�.
				{
					if( pclclient->pclCM->CR[1]->pclCI->clBI.siSummonExtraSlotDate > 0 )
					{
						TCHAR	*pTitle	= GetTxtFromMgr(512);
						TCHAR	*pText	= GetTxtFromMgr(8769);
						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
						break;
					}
					else
					{
						UseNolimitTicket(m_pclInventoryItem[ Pos ].siUnique, SUMMON_SPACE_TICKET );
					}

					
				}
				break;
			//[����] ������ ��� â.
			case ITEMUNIQUE(13634):
				{
					if( pclClient->IsCountrySwitch( Switch_Elixir ) )
					{
						cltCharClient* pclChar = pclClient->pclCM->GetCharClient(1);
						//if(	pclChar && false == pclChar->pcltElixir->IsElixir() )
						{
							pclclient->CreateInterface( NELIXIR_USE_DLG );

							((NElixirUseDlg*)pclclient->m_pDialog[NELIXIR_USE_DLG])->SetItemUnique( ITEMUNIQUE(13634) );
						}
						//else
						{
							//pclclient->m_pDialog[NOTIFYMSG_DLG]->SetText( GetTxtFromMgr(5614), GetTxtFromMgr(9759) ); 
						}
					}
				}
				break;

			case ITEMUNIQUE(8123):
				{
					if( pclClient->IsCountrySwitch( Switch_NewDurability) )
					{
						pclclient->CreateInterface( NNEWITEMMAKE_DLG );
						CNewMakeItemDlg* pclNewMakeItemDlg = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
						NItemRepairDlg* pclItemRepairDlg = NULL;
						if( pclNewMakeItemDlg )		pclItemRepairDlg = pclNewMakeItemDlg->NewItemRepair;

						if( pclItemRepairDlg )
						{
							pclItemRepairDlg->SetMode( 1 );
						}
						pclNewMakeItemDlg->ShowRepairTab();
					}
				}
				break;

			case ITEMUNIQUE(13356):
			case ITEMUNIQUE(13357):
			case ITEMUNIQUE(13338):
			case ITEMUNIQUE(13343):
			case ITEMUNIQUE(13352):
			case ITEMUNIQUE(13317):
			case ITEMUNIQUE(13330):
				{
					// �ҷ��� ���Ǹ� ���� dlg
					cltClient* pClient = (cltClient*)pclClient;
					if(pClient != NULL)
					{
						if(pClient->m_pDialog[NHALLOWEENSPIRITBOX_DLG] == NULL)
						{
							pClient->CreateInterface(NHALLOWEENSPIRITBOX_DLG);

							((NHalloweenSpiritBoxDlg*)pclclient->m_pDialog[NHALLOWEENSPIRITBOX_DLG])->SetSpritItmeUnique( m_pclInventoryItem[ Pos ].siUnique );
						}
						else
						{
							// ������� ������ �׳� ��
							((NHalloweenSpiritBoxDlg*)pclclient->m_pDialog[NHALLOWEENSPIRITBOX_DLG])->SetSpritItmeUnique( m_pclInventoryItem[ Pos ].siUnique );
						}
					}
				}
				break;
			//[����] �߷�Ÿ�ε���. ������ ���ݸ�
			case ITEMUNIQUE(13661):
				{
					pclclient->CreateInterface( VALENTINEDAY_CONFESSION_QUESTION_DLG );
				}
				break;
			//----------------------------------------------------------------------------------------------------
			default:
				{
					m_pBuffer->Push( INV_USE_ITEM, Pos, &m_pclInventoryItem[ Pos ] );
				}
		}
	}
	m_siSelectedIndex = -1;

	return;
}

void CNNewInventory::DropItem( SI16 Pos )
{
	if ( m_pclInventoryItem[ Pos ].siUnique == 0 )
	{
		return;
	}
	if ( pclClient->IsCountrySwitch(Switch_DestroyDropItem) ){
		SI16 siItemnum = m_pclInventoryItem[ Pos ].GetItemNum();// ������ ����
		if ( siItemnum <= 0 ) return;
		SI32 siItemUnique = m_pclInventoryItem[ Pos ].siUnique;// ������ ����ũ
		if ( siItemUnique <= 0 ) return;
		TCHAR* tcItemname = ( TCHAR* )pclClient->pclItemManager->GetName( siItemUnique);// ������ �̸�
		if ( tcItemname == NULL ) return;

		TCHAR* pTitle = GetTxtFromMgr(5261);
		NTCHARString256	kText(GetTxtFromMgr(8571));
		kText.Replace(TEXT("#itemname#"),tcItemname );
		kText.Replace(TEXT("#num#"),SI16ToString(siItemnum) );
		
		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle,kText, MSGBOX_TYPE_YESNO, 2 );
		BYTE TempBuffer[ 256 ];
		SI16 Size = sizeof( Pos ) + sizeof( cltItem );
		memcpy( TempBuffer, &Pos, sizeof( Pos ) );
		memcpy( &TempBuffer[ sizeof( Pos ) ], &m_pclInventoryItem[ Pos ], sizeof( cltItem ) );
		cltClient *pclclient = (cltClient *)pclClient;
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
		m_siSelectedIndex = -1;		
	}
	else{
		TCHAR* pTitle = GetTxtFromMgr(5261);
		TCHAR* pText;
		//cyj �ͼ� �������϶��� �ı��ϵ��� �޼��� ����
		if (m_pclInventoryItem[ Pos ].IsBelonging(pclClient->pclItemManager))
		{
			pText = GetTxtFromMgr(5899);
		}
		else
		{
			pText = GetTxtFromMgr(5262);
		}
		stMsgBox MsgBox;
		MsgBox.Set( this, pTitle, pText, MSGBOX_TYPE_YESNO, 2 );

		BYTE TempBuffer[ 128 ];
		SI16 Size = sizeof( Pos ) + sizeof( cltItem );
		memcpy( TempBuffer, &Pos, sizeof( Pos ) );
		memcpy( &TempBuffer[ sizeof( Pos ) ], &m_pclInventoryItem[ Pos ], sizeof( cltItem ) );

		cltClient *pclclient = (cltClient *)pclClient;
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

		m_siSelectedIndex = -1;
	}	
}

void CNNewInventory::DropItem_New( cltItem* pclItem, SI16 Pos )
{
	cltClient* pclclient = (cltClient*)pclClient;

	// ��û�� �����۰� ���� �������� ���ؼ� Ʋ���� �ƹ��͵� ���Ѵ�.
	if( pclItem->IsSame(&m_pclInventoryItem[ Pos ], true) == false )			return;

	/*if ( pclClient->IsCountrySwitch(Switch_DestroyDropItem) ){
		DropItem( Pos );
	}
	else{*/
		if( ( pclclient->pclItemManager->GetItemAtb(m_pclInventoryItem[ Pos ].siUnique) & ITEMATB_OBJECT) == false )
		{
			if ( ((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG]) == NULL )
			{
				pclclient->CreateInterface( NSELECTITEMCOUNT_DLG );
			}
			((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetSelectedItemIndex( Pos );
			((CNSelectItemCountDlg*)pclclient->m_pDialog[NSELECTITEMCOUNT_DLG])->SetCountMode( COUNT_MODE_DROPITEM );
		}
		else
		{
			DropItem( Pos );
		}
	//}
}

// WEAPON1 �� WEAPON2�� ��ġ�� ��ȯ�Ѵ�.
void CNNewInventory::ExchangeWeapon()
{
}

void CNNewInventory::ExchangeClothes()
{
}

void CNNewInventory::Show()
{	
	cltClient *pclclient = (cltClient *)pclClient;

	CDialogController::Show( true );
	m_bMax = false;
	ChangeMaxMode( m_bMax );

	CheckWrongSelectedInven();
	LoadItemData();

	return;
}

void CNNewInventory::Hide()
{
	cltClient* pclclient = (cltClient*)pclClient;

	// ��� �κ��� ���ܶ�!!
	((CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG])->CDialogController::Show( false );
	((CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_HORSE_DLG])->CDialogController::Show( false );
	((CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG0_DLG])->CDialogController::Show( false );
	((CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG1_DLG])->CDialogController::Show( false );

	return;
}

void CNNewInventory::Action()
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI16 dialogID = GetDialogControllerID();

	if(IsShow())
	{
		// ������ ����Ʈ ����� ����â�� �����־ Ŭ���� �ܰ�� �Ѿ��. by LEEKH 2008.08.10
		// ���� ������ ���� ������������ �����Ѵ�.
		static SI32 siUpdateTime = 0;
		if(GetTickCount() - siUpdateTime > 500)
		{
			siUpdateTime = GetTickCount();
		}

		if ( pclclient->siServiceArea == ConstServiceArea_China )
		{
			ShowSlotNum();
		}
		else
		{
			ShowInvenWeight();
		}
	}

	if ( IsItemDataChanged()  )
	{
		LoadItemData();
		if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
		{
			UpdateMakeItemData();
		}
	}

	CheckCharStatusChanged();
	

	return;
}


void CNNewInventory::UpdateMakeItemData()
{
	cltClient *pclclient = (cltClient *)pclClient;

	for(SI32 i =0; i <25 ; i++)
	{	

		SI32 index = clMakeItemContainer.m_siMaterials[i];
		//�������� �ڸ��� �̵��� ���
		if( m_pclInventoryItem[index].siUnique  !=  clMakeItemContainer.clMaterials[i].siUnique )
		{
			clMakeItemContainer.clMaterials[i].Init();
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
				(NewMakeItem->NewMakeTab)->ShowMaterials(clMakeItemContainer.clMaterials);
			}
		}
		//�����Ǿ� ������ ������ �پ���� 
		else if( m_pclInventoryItem[index].siItemNum !=  clMakeItemContainer.clMaterials[i].siItemNum  && m_pclInventoryItem[index].siUnique  ==  clMakeItemContainer.clMaterials[i].siUnique)
		{
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];				
				clMakeItemContainer.clMaterials[i].siItemNum= m_pclInventoryItem[index].siItemNum;
				(NewMakeItem->NewMakeTab)->ShowMaterials(clMakeItemContainer.clMaterials);
			}
		}			
	}


	for(SI32 i =0; i <4  ; i++)
	{
		SI32 index = clMakeItemContainer.m_sitools[i];
		if( m_pclInventoryItem[index].siUnique  != clMakeItemContainer.cltools[i].siUnique )
		{
			clMakeItemContainer.cltools[i].Init();
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
				(NewMakeItem->NewMakeTab)->ShowTools(clMakeItemContainer.cltools);
			}

		}
		else if( m_pclInventoryItem[index].siItemNum ==  clMakeItemContainer.cltools[i].siItemNum  && m_pclInventoryItem[index].siUnique  ==  clMakeItemContainer.cltools[i].siUnique)
		{
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];				
				clMakeItemContainer.cltools[i].siItemNum= m_pclInventoryItem[index].siItemNum;
				(NewMakeItem->NewMakeTab)->ShowTools(clMakeItemContainer.cltools);
			}
		}		
	}

	for(SI32 i =0; i <NOW_ENCHANT_NUMBER ; i++) //��æƮ ����
	{
		SI32 index = pclclient->pclCM->CR[1]->siElementEnchantInx[i];
		if( m_pclInventoryItem[index].siUnique  !=  clMakeItemContainer.clEleEnchantItem[i].siUnique )
		{
			clMakeItemContainer.clEleEnchantItem[i].Init();
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
				clMakeItemContainer.clEleEnchantItem[i].siItemNum = m_pclInventoryItem[index].siItemNum;
				(NewMakeItem->NewEnchantTab)->ShowEleEnchantItem(clMakeItemContainer.clEleEnchantItem);
			}

		}
		else if( m_pclInventoryItem[index].siItemNum !=  clMakeItemContainer.clEleEnchantItem[i].siItemNum  && m_pclInventoryItem[index].siUnique  ==  clMakeItemContainer.clEleEnchantItem[i].siUnique)
		{
			if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
			{
				CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];				
				clMakeItemContainer.clEleEnchantItem[i].siItemNum= m_pclInventoryItem[index].siItemNum;
				(NewMakeItem->NewEnchantTab)->ShowEleEnchantItem(clMakeItemContainer.clEleEnchantItem);
			}
		}		
	}



	SI32 index = pclclient->pclCM->CR[1]->siOrgInvEnchantInx;
	if( index!=0 && m_pclInventoryItem[index].siUnique  !=  clMakeItemContainer.clOrgEnchantItem.siUnique )
	{
		clMakeItemContainer.clOrgEnchantItem.Init();
		if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
		{
			CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
			(NewMakeItem->NewEnchantTab)->ShowOrgEnchantItem( m_pclInventoryItem[index]);
		}

	}
	else if(index!=0 && m_pclInventoryItem[index].siItemNum ==  clMakeItemContainer.clOrgEnchantItem.siItemNum  && m_pclInventoryItem[index].siUnique  ==  clMakeItemContainer.clOrgEnchantItem.siUnique)
	{
		if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
		{
			CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];				
			clMakeItemContainer.clOrgEnchantItem.siItemNum= m_pclInventoryItem[index].siItemNum;
			(NewMakeItem->NewEnchantTab)->ShowOrgEnchantItem( m_pclInventoryItem[index]);
		}
	}



	index = pclclient->pclCM->CR[1]->siMatInvEnchantInx;
	if( m_pclInventoryItem[index].siUnique  !=  clMakeItemContainer.clMatEnchantItem.siUnique )
	{
		clMakeItemContainer.clMatEnchantItem.Init();
		if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
		{
			CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
			(NewMakeItem->NewEnchantTab)->ShowMatEnchantItem(clMakeItemContainer.clMatEnchantItem);
		}

	}
	else if( m_pclInventoryItem[index].siItemNum ==  clMakeItemContainer.clMatEnchantItem.siItemNum  && m_pclInventoryItem[index].siUnique  ==  clMakeItemContainer.clMatEnchantItem.siUnique)
	{
		if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
		{
			CNewMakeItemDlg* NewMakeItem  = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];				
			clMakeItemContainer.clMatEnchantItem.siItemNum= m_pclInventoryItem[index].siItemNum;
			(NewMakeItem->NewEnchantTab)->ShowMatEnchantItem(clMakeItemContainer.clMatEnchantItem);
		}
	}	

	return;
}

bool CNNewInventory::IsItemDataChanged()
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

void CNNewInventory::LoadItemData()
{
	SI16 StartPos = 0;
	SI32 i = 0;
	SI32 id = 1;
	SI32 GlobalImageIndex = -1;
	SI32 GlobalImageFont = -1;
	cltClient* pclclient = (cltClient*)pclClient;

	// � �κ�����..
	SI16 contollerid = GetDialogControllerID();
	switch( contollerid )
	{
	case NNEWINVENTORY_DLG : 
		StartPos = PERSONITEM_INV0;
		break;
	case NNEWINVENTORY_HORSE_DLG : 
		StartPos = PERSONITEM_HORSE0;
		break;
	case NNEWINVENTORY_BAG0_DLG : 
		StartPos = PERSONITEM_BAG0;
		break;
	case NNEWINVENTORY_BAG1_DLG : 
		StartPos = PERSONITEM_BAG1;
		break;
	}

	//	StartPos = PERSONITEM_INV0 + ( m_siCurrentInventoryIndex * MAX_ITEM_PER_INVENTORY );
	m_pInventoryListView->DeleteAllItems();

	m_pInventoryListView->SetStartItemPos( StartPos );

	for ( i = 0; i < MAX_ITEM_PER_PERSON; ++i )
	{
		m_pclInventoryItem[ i ].Set( &pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[ i ] );

		if ( m_pclInventoryItem[ i ].siUnique > 0 )
		{
			if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( m_pclInventoryItem[ i ].siUnique, &GlobalImageIndex, &GlobalImageFont ) )
			{
				TCHAR *ItemName = (TCHAR*)pclClient->pclItemManager->GetName( m_pclInventoryItem[ i ].siUnique );

				if ( ItemName )
				{
					TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");
					//SI32 siItemStatus = 0 ;					

					pclClient->pclItemManager->GetExplain( &m_pclInventoryItem[ i ], ToolTipMsg,true,false,true, pclClient->pclCM->CR[1]->GetKind() );//,&siItemStatus);
					SI32 size = sizeof(ToolTipMsg);
					SI32 ddd = _tcslen(ToolTipMsg);
					bool bIsSealed = m_pclInventoryItem[ i ].IsSealingUp(pclClient->pclItemManager);

					if ( i >= StartPos && i < StartPos + MAX_ITEM_PER_INVENTORY )
					{
						// ������ ��쿡�� ���濡 ������ �ִ� ������ ���� ��ŭ��..
						if( i >= StartPos + MAX_ITEM_PER_BAG && (  GetDialogControllerID() == NNEWINVENTORY_BAG0_DLG  || GetDialogControllerID() == NNEWINVENTORY_BAG1_DLG ) )
							continue;

						// ����â�� ���ְ� �� �ȿ� ���Ե� �������̶��, ��ο� �ɼ��� ���������� ��������

						stListViewItemData ListViewItemData;

						//KHY - 0723 - �Ⱓ������ �ı� ����. Ȥ�� ����.
						if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
						{	
							SI32		useableDay	= 0;
							BOOL bRet = pclclient->GetItemUseAbleDay( &(m_pclInventoryItem[ i ]), &useableDay);

							if(bRet == TRUE && useableDay < 0)		ListViewItemData.SetExpired(true);
//							if(bRet == TRUE )				
//								ListViewItemData.UpViewSet(&(pclClient->sUpViewEffect));
						}
						ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, i - StartPos, m_pclInventoryItem[ i ].siItemNum, ItemName, ToolTipMsg, false, bIsSealed ); // ������ ������ ���� ���� ColorSwitch = true
						m_pInventoryListView->InsertItem( &ListViewItemData );
					}
				}
			}
		}
	}

	// ����â�� �������� ���������� ��� ���,  �� Ž���Ͽ� ��ο� �ɼ��� ����������~ ����
	if(pclclient->m_pDialog[NNEWITEMMAKE_DLG])
	{
		for( i = 0; i < 25; i++)
		{
			if(clMakeItemContainer.m_siMaterials[ i ] > 0)
			{
				m_pInventoryListView->SetItemDrawAlphaOption(clMakeItemContainer.m_siMaterials[ i ],true);
			}
		}
		for(i = 0; i < 4; i++)
		{
			if(clMakeItemContainer.m_sitools[i] > 0)
			{
				m_pInventoryListView->SetItemDrawAlphaOption(clMakeItemContainer.m_sitools[ i ],true);
			}
		}

		if(pclclient->pclCM->CR[1]->siOrgInvEnchantInx > 0)
		{
			m_pInventoryListView->SetItemDrawAlphaOption(pclclient->pclCM->CR[1]->siOrgInvEnchantInx, true);
		}

		if(pclclient->pclCM->CR[1]->siMatInvEnchantInx > 0)
		{
			m_pInventoryListView->SetItemDrawAlphaOption(pclclient->pclCM->CR[1]->siMatInvEnchantInx, true);
		}

		for(i = 0; i < NOW_ENCHANT_NUMBER; i++)
		{
			if(pclclient->pclCM->CR[1]->siElementEnchantInx[i] > 0)
			{
				m_pInventoryListView->SetItemDrawAlphaOption(pclclient->pclCM->CR[1]->siElementEnchantInx[i], true);
			}
		}
	}

	if( pclclient->m_pDialog[NNEWNPCREPAIR_DLG] && pclclient->m_pDialog[NNEWNPCREPAIR_DLG]->IsShow() )
	{
		NNewNPCRepairDlg* pkNewNPCRepairDlg = (NNewNPCRepairDlg*)pclclient->m_pDialog[NNEWNPCREPAIR_DLG];

		SI32 siRepairItemPos = pkNewNPCRepairDlg->GetRepairItemPos();
		m_pInventoryListView->SetItemDrawAlphaOption( siRepairItemPos, true );

		for( SI32 i=0; i<pkNewNPCRepairDlg->GetMaterialItemCount(); i++ )
		{
			SI32 siMaterialItemPos = pkNewNPCRepairDlg->GetMaterialItemPos( i );
			m_pInventoryListView->SetItemDrawAlphaOption( siMaterialItemPos, true );
		}
	}

	CNewMakeItemDlg* pclNewMakeItemDlg = (CNewMakeItemDlg*)pclclient->m_pDialog[NNEWITEMMAKE_DLG];
	NItemRepairDlg* pclItemRepairDlg = NULL;
	if( pclNewMakeItemDlg )		pclItemRepairDlg = pclNewMakeItemDlg->NewItemRepair;

	if( pclItemRepairDlg && pclItemRepairDlg->IsShow() )
	{
		SI32 siRepairItemPos = pclItemRepairDlg->GetRepairItemPos();
		m_pInventoryListView->SetItemDrawAlphaOption( siRepairItemPos, true );

		for( SI32 i=0; i<pclItemRepairDlg->GetMaterialItemCount(); i++ )
		{
			SI32 siMaterialItemPos = pclItemRepairDlg->GetMaterialItemPos( i );
			m_pInventoryListView->SetItemDrawAlphaOption( siMaterialItemPos, true );
		}
	}

	// �־��� ��Ḧ �ٰŷ� ���� ������ �������� ����Ʈ�� �ۼ��ؼ� �����Ѵ�. 
	// ���� ����Ʈ�� ����� ������ �־�� �Ѵ�. 
	SI32 siMakeableItemNum = 0;	

	if ( m_pMakeableItemList )
	{
		delete [] m_pMakeableItemList;
		m_pMakeableItemList = NULL;
	}	

	m_pMakeableItemList = NULL;

	//m_pMakeItemComboBox->Clear();

	if( pclClient->pclItemManager->FindMakeableItem(
		&pclClient->pclCM->CR[id]->pclCI->clCharSkill,
		&pclClient->pclCM->CR[id]->pclCI->clCharItem,
		&pclClient->pclCM->CR[id]->clPB.clTotalBA, 
		MAX_INVITEM_PER_PERSON, 
		&pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[PERSONITEM_INV0], 
		&m_siMakeableItemNum, &m_pMakeableItemList,
		false) == true)
	{

		// �޺� �ڽ��� �������� ���갡���� ����� ǥ���Ѵ�. 
		for( i = 0; i < m_siMakeableItemNum; ++i )
		{
			SI32 unique		= m_pMakeableItemList[ i * 2 ];
			SI32 itemnum	= m_pMakeableItemList[ i * 2 +1];

			if ( unique !=  0 )
			{
				TCHAR buffer[256];
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( unique );

				if(ref > 0)
				{	
					TCHAR* pText = GetTxtFromMgr(676);

					//sprintf( buffer, pText, pclClient->pclItemManager->pclItemInfo[ref]->GetName(), itemnum );
					StringCchPrintf(buffer,256, pText, pclClient->pclItemManager->pclItemInfo[ref]->GetName(), itemnum );

				}
			}
		}
	}
	if ( m_bMax && IsShow() )
	{

		ChangeMaxMode( m_bMax );
	}
	return;
}


void CNNewInventory::LoadSummonData()
{
}

void CNNewInventory::LoadInventoryTabData()
{
	//SI32 id = 1;

	//SI16 Counter = 0;

	//m_bHorseHave = pclClient->pclCM->CR[id]->HaveHorse();

	//if ( m_bHorseHave )
	//{
	//	m_pButtonHorseInventory->Enable( true );
	//}
	//else
	//{	
	//	m_pButtonHorseInventory->Enable( false );
	//}


	//if ( pclClient->pclCM->CR[id]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0 )
	//{
	//	m_bBagHave = true;
	//	m_pButtonBagInventory->Enable( true );
	//}
	//else
	//{
	//	m_bBagHave = false;
	//	m_pButtonBagInventory->Enable( false );
	//}

	return;
}


void CNNewInventory::DrawDialogFirst( SI32 ScreenRX, SI32 ScreenRY  )
{

}


void CNNewInventory::DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  )
{
	cltClient *pclclient = (cltClient *)pclClient;

	//// ��� ���� ��쿡�� ����Ű ��� �׸��� ���� ���� ���� �̹��� �����ִ� �͵� ����( tab ��ư���� �ٲٴ� �� )
	//if ( m_siCurrentInventoryIndex == TAB_SELECTED_PERSON )
	//{
	if( GetDialogControllerID() == NNEWINVENTORY_DLG )
	{
		SI16 i = 0;
		TSpr *pAcceleratorImg = pclclient->m_pInterfaceMgr->GetInterfaceImgrMgr()->LoadInterfaceImg( LISTVIEW_ACCELERATOR_FILENAME );

		if ( pAcceleratorImg )
		{
			if( m_bMax && pclClient->pclCM->CR[1]->HaveHorse() )
			{
				for ( i = 0; i < 5; ++i )
				{
					// ���� : 9, 298    OffSet : 57
					GP.PutSpr(pAcceleratorImg, ScreenRX + GetX() + 7, ScreenRY + GetY() + 20 + (i * 44), LISTVIEW_ACCELERATOR_FONTINDEX  + i  ); //*1�� F0 ���� ���������� 
				}
			}
			else
			{
				for ( i = 0; i < 5; ++i )
				{
					// ���� : 9, 298    OffSet : 57
					GP.PutSpr(pAcceleratorImg, ScreenRX + GetX() + 43, ScreenRY + GetY() + 20 + (i * 44), LISTVIEW_ACCELERATOR_FONTINDEX  + i  ); //*1�� F0 ���� ���������� 
				}
			}
		}
	}
	return;
}

bool CNNewInventory::Pop( stMoveData * pMoveData )
{
	return m_pBuffer->Pop( pMoveData );	
}

bool CNNewInventory::Pop( BYTE* pMoveData )
{
	return m_pBuffer->Pop( pMoveData );
}

void CNNewInventory::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 0:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				SI32 *SelectedInventoryItemIndex = (SI32 *)pData;
				cltItem *pclItem = (cltItem *)&pData[4];

				if ( m_pclInventoryItem[ *SelectedInventoryItemIndex ].siUnique == 0 )
				{
					return;
				}

				m_pBuffer->Push( INV_REPAIR_ITEM, *SelectedInventoryItemIndex, pclItem );
			}
		}
		break;
	case 1:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				SI16 *Pos = (SI16 *)pData;
				cltItem *pclItem = (cltItem *)&pData[2];

				if ( m_pclInventoryItem[ *Pos ].siUnique == 0 )
				{
					return;
				}

				m_pBuffer->Push( INV_USE_ITEM, *Pos, pclItem );
			}
		}
		break;
	case 2:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI16 *Pos = (SI16 *)pData;
				cltItem *pclItem = (cltItem *)&pData[2];

				if ( m_pclInventoryItem[ *Pos ].siUnique == 0 )
				{
					return;
				}

				m_pBuffer->Push( INV_DROP_ITEM, *Pos, pclItem );

				m_siSelectedIndex = -1;
			}
		}
		break;
	case 3:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				SI32 *SelectedInventoryItemIndex = (SI32 *)pData;
				cltItem *pclItem = (cltItem *)&pData[4];

				if ( m_pclInventoryItem[ *SelectedInventoryItemIndex ].siUnique == 0 )
				{
					return;
				}

				m_pBuffer->Push( INV_CANCELLATIONSEALINGUP_ITEM, *SelectedInventoryItemIndex, pclItem );
			}
		}
		break;
	case 4:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				SI32 *ItemUnique = (SI32 *)pData;				

				if ( *ItemUnique <= 0 )
				{
					return;
				}
				cltGameMsgRequest_NolimitTicket_Warp clInfo(*ItemUnique);
				cltMsg clMsg( GAMEMSG_REQUEST_NOLIMITTICKET_WARP , sizeof(clInfo) , (BYTE*)&clInfo );
				pclClient->SendMsgToServer( (sPacketHeader*) &clMsg );
			}
		}
		break;
	case 5:
		{
			//���� ���� ����ȵǸ� �Ϸ� ��������
			//�׳� ƨ�� ����.���� ����.
			return;
		}break	;

	case 6:	// �ش� ��ġ�� ���󰣴�.
		{
			if ( RetValue )
			{
				SI32 *ItemUnique = (SI32 *)pData;				

				if ( *ItemUnique <= 0 )
				{
					return;
				}
				cltGameMsgRequest_WarpTargetWorld clInfo(*ItemUnique);
				cltMsg clMsg( GAMEMSG_REQUEST_WARP_TARGETWORLD , sizeof(clInfo) , (BYTE*)&clInfo );
				pclClient->SendMsgToServer( (sPacketHeader*) &clMsg );
			}
		}break	;
// [����] ���� ���� ���ڿ��� �������� �ش� 
	case 7:
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}
			if ( RetValue )
			{
				if ( pclClient->IsCountrySwitch(Switch_LevelLimitBox) == false)		return	;
				SI32 *ItemUnique = (SI32 *)pData;				

				if ( *ItemUnique <= 0 )
				{
					return;
				}
				cltGameMsgRequest_UseLimitLevleBox clInfo(*ItemUnique);
				cltMsg clMsg( GAMEMSG_REQUEST_OPEN_LEVEL_LIMIT_BOX , sizeof(clInfo) , (BYTE*)&clInfo );
				pclClient->SendMsgToServer( (sPacketHeader*) &clMsg );
			}
		}
		break;
	}	
	return;
}


SI32 CNNewInventory::GetInventoryType(SI32 siItemType)
{
	SI32 StartPos =0;
	SI32 siItemUinque =m_pclInventoryItem[m_siSelectedIndex].siUnique;

	if (siItemType == ITEMTYPE_HELMET )
		return PERSONITEM_HELMET;

	else if  (siItemType == ITEMTYPE_ARMOUR  )
		return PERSONITEM_ARMOUR;

	//cyj ȭ�� �� źȯ ���� �����ϵ��� ����
	else if(( siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == ITEMUNIQUE(10100) ||siItemUinque == ITEMUNIQUE(10090) || m_pclInventoryItem[m_siSelectedIndex].IsBulletItem()) 
		&& (m_pclInventoryItem[ PERSONITEM_WEAPON1 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_WEAPON1 + StartPos ))
		return PERSONITEM_WEAPON2;

	//cyj ȭ�� �� źȯ ���� �����ϵ��� ����
	else if ( siItemType == ITEMTYPE_GUN || siItemType == ITEMTYPE_BOW ||siItemType == ITEMTYPE_AXE ||siItemType == ITEMTYPE_STAFF ||siItemType == ITEMTYPE_SPEAR 
		||siItemType == ITEMTYPE_SWORD || siItemType == ITEMTYPE_FISHINGROD || siItemUinque == ITEMUNIQUE(10100) ||siItemUinque == ITEMUNIQUE(10090) || m_pclInventoryItem[m_siSelectedIndex].IsBulletItem())
		return PERSONITEM_WEAPON1;

	else if ( siItemType == ITEMTYPE_NECK || siItemType == ITEMTYPE_AVATAR_NECK ) // �ƹ�Ÿ �����
		return PERSONITEM_NECK;

	else if (( siItemType == ITEMTYPE_RING || siItemType == ITEMTYPE_AVATAR_RING ) // �ƹ�Ÿ ����
		&&( m_pclInventoryItem[ PERSONITEM_RING2 + StartPos ].siUnique != 0 && m_siSelectedIndex != PERSONITEM_RING2 + StartPos ))
		return PERSONITEM_RING1;

	else if ( siItemType == ITEMTYPE_RING || siItemType == ITEMTYPE_AVATAR_RING )
		return PERSONITEM_RING2;

	else if ( siItemType == ITEMTYPE_BELT )
		return PERSONITEM_BELT;

	else if ( siItemType == ITEMTYPE_SHOES )
		return PERSONITEM_SHOES;

	else if ( siItemType ==ITEMTYPE_MANTLE || siItemType == ITEMTYPE_AVATAR_MANTLE) // �ƹ�Ÿ ����
		return PERSONITEM_MANTLE;

	else if (( siItemType == ITEMTYPE_BAG )
		&&( m_pclInventoryItem[ PERSONITEM_BAG + StartPos ].siUnique == 0 ) )
		return PERSONITEM_BAG;

	else if ( siItemType == ITEMTYPE_BAG )
		return PERSONITEM_BAG_SUB;

	else if ( siItemType == ITEMTYPE_HAT || siItemType == ITEMTYPE_AVATAR_HAT ) // �ƹ�Ÿ ����
		return PERSONITEM_HAT;

	else if ( siItemType == ITEMTYPE_DRESS || siItemType == ITEMTYPE_AVATAR_DRESS ) // �ƹ�Ÿ �Ǻ�
		return PERSONITEM_DRESS;
	else
	{
		return PERSONITEM_NONE;
	}
}

SI32 CNNewInventory::GetInventoryTypeForSummon( SI32 siItemType )
{
	switch ( siItemType )
	{
		case ITEMTYPE_HELMET:
			return PERSONITEM_HELMET;

		case ITEMTYPE_ARMOUR:
			return PERSONITEM_ARMOUR;
		
		case ITEMTYPE_GUN:
		case ITEMTYPE_BOW:
		case ITEMTYPE_AXE:
		case ITEMTYPE_STAFF:
		case ITEMTYPE_SPEAR:
		case ITEMTYPE_SWORD:
			return PERSONITEM_WEAPON1;

		case ITEMTYPE_BELT:
			return PERSONITEM_BELT;

		case ITEMTYPE_SHOES:
			return PERSONITEM_SHOES;
		
		case ITEMTYPE_MANTLE:
			return PERSONITEM_MANTLE;
	}

	if ( TRUE == m_pclInventoryItem[m_siSelectedIndex].IsBulletItem() )
	{
		return PERSONITEM_WEAPON2;
	}

	return PERSONITEM_NONE;

}


void CNNewInventory::ChangeItem( SI32 Destination )
{
	cltClient *pclclient = (cltClient *)pclClient;

	if ( m_siSelectedIndex == PERSONITEM_BAG )
	{	
		// ���� ���� ���� �ű�� �Ұ�
		if( Destination >= PERSONITEM_BAG0 && Destination < PERSONITEM_BAG0 + MAX_ITEM_PER_INVENTORY )
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
	/*
	if ( m_pclInventoryItem[ Destination ].siUnique != 0 )
	{
	if ( m_pclInventoryItem[ Destination ].CanPile( pclClient->pclItemManager ) == false )
	{
	return;
	}
	}
	*/  
	if((Destination >= 0  && Destination <= 14 ) || Destination == 82 || Destination == 97 )
	{
		if(m_pclInventoryItem[ m_siSelectedIndex ].IsSealingUp(pclClient->pclItemManager))
		{
			TCHAR *pTitle = GetTxtFromMgr(5662);
			TCHAR *pText = GetTxtFromMgr(5663);

			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
			return;		
		}
	}

	pclClient->pclItemManager->PlaySound( m_pclInventoryItem[ m_siSelectedIndex ].siUnique, ITEMSOUND_SELECT );
	m_pBuffer->Push( INV_CHANGE_ITEM, MoveInfo, &m_pclInventoryItem[ m_siSelectedIndex ] );


	return;
}

void CNNewInventory::IsMinimi(bool bSet)
{
	cltClient *pclclient = (cltClient *)pclClient;

	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];
	CNNewInventory* horseinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_HORSE_DLG];
	CNNewInventory* bag0inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG0_DLG];
	CNNewInventory* bag1inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG1_DLG];

	if( bSet ) // �ּ�ȭ
	{
		m_bMax = false;
		horseinventory->CDialogController::Show( false );
		bag0inventory->CDialogController::Show( false );
		bag1inventory->CDialogController::Show( false );
		m_siCurrentInventoryIndex = TAB_SELECTED_PERSON;
		personinventory->LoadItemData();


		personinventory->SetFileName( TEXT("NInterface/interface/INTERFACE_84x240_00_000.SPR") );

		// SetDialogPos -> SetTitle ������ ����!
		// SetDialogPos �� ���ڴ������� ũ�⵵ ���ϰ� �ȴ�.

		personinventory->SetDialogPos( pclclient->GetScreenXSize() - 84, 250, 68, 240 );
		personinventory->SetTitle(NULL);
		personinventory->m_pInventoryListView->MoveController(40, 17);

		personinventory->SetMoveable( false );

		if ( pclclient->IsCountrySwitch( Switch_AutoMakeItem ) == true ){
			personinventory->m_pMakeItemBtn->Show( true );//�ּ�ȭ �϶��� ���� ��ư�� Ȱ��ȭ.
		}
		else{
			personinventory->m_pMakeItemBtn->Show( false );//�ּ�ȭ �϶��� ���� ��ư�� Ȱ��ȭ.
		}
		
		personinventory->m_pEnchantItemBtn->Show( false );
		personinventory->m_pItemmallListBtn->Show( false );
	
		//		m_pMakeItemComboBox->Show( false );
		//		m_pMakeItemStatic->Show( false );
		//	m_pMakeItemInputEdit->Show( false );

		personinventory->m_pInventoryListView->Show( true );
		personinventory->m_pMoveItemToHorseListView->Show( false );
		personinventory->m_pMoveItemToBag0ListView->Show( false );
		personinventory->m_pMoveItemToBag1ListView->Show( false );


		personinventory->m_pButtonMini->Show( true );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			personinventory->m_pButtonSpaceBox->Show( false );
		}
		else
		{
			personinventory->m_pButtonMax->Show( true );
		}

		//m_pButtonManInventory->Show( false );
		//m_pButtonHorseInventory->Show( false );
		//m_pButtonBagInventory->Show( false );

		personinventory->m_pStatic[0]->Show( false );
		personinventory->m_pStatic[1]->Show( false );
		personinventory->m_pStatic[2]->Show( false );
		if ( pclclient->siServiceArea == ConstServiceArea_China )
		{
			personinventory->m_pWeightStatic->MoveController( -25, 3 );
		}
		else
		{
			personinventory->m_pWeightStatic->Show( false );
		}
	}
	else
	{
		m_bMax = false;
		ChangeMaxMode( m_bMax );
		//TCHAR* pText = GetTxtFromMgr(5067);

		//SetFileName( TEXT("NInterface/interface/INTERFACE_202x325_00_000.SPR") );

		//SetDialogPos( pclclient->GetScreenXSize() - 202, 250, 202, 325 );
		//SetTitle(pText,CONTROLLER_TITLE_COLOR,11);		

		//SetMoveable( true );

		//m_pMakeItemBtn->Show( true );
		////m_pMakeItemComboBox->Show( true );
		////		m_pMakeItemStatic->Show( true );
		////	m_pMakeItemInputEdit->Show( true );

		//m_pInventoryListView->Show( true );
		//m_pMoveItemToHorseListView->Show( true );
		//m_pMoveItemToBagListView->Show( true );

		//m_pButtonMini->Show( true );
		////m_pButtonManInventory->Show( true );
		////m_pButtonHorseInventory->Show( true );
		////m_pButtonBagInventory->Show( true );

		//m_pStatic[0]->Show( true );
		//m_pStatic[1]->Show( true );
	}
}

void CNNewInventory::ChangeMaxMode(bool bSet)//�ռ���
{
	m_bMini = false;

	cltClient*	pclclient = (cltClient*)pclClient;
	CNNewInventory* personinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_DLG];
	CNNewInventory* horseinventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_HORSE_DLG];
	CNNewInventory* bag0inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG0_DLG];
	CNNewInventory* bag1inventory = (CNNewInventory*)pclclient->m_pDialog[NNEWINVENTORY_BAG1_DLG];

	//if (HORSEACTION_DIE) {//���� ������ �������� �и��� ���� ���װ� �߻��Ͽ� �׾������ ó��.[2008.08.02 �ռ���]
	//	horseinventory->CDialogController::Show( false );
	//	bag0inventory->CDialogController::Show( false );
	//	bag1inventory->CDialogController::Show( false );
	//	personinventory->SetFileName( TEXT("NInterface/interface/INTERFACE_218x280_00_000.SPR") );
	//	personinventory->SetDialogPos( pclclient->GetScreenXSize() - 218 , 250 , 218, 280 );
	//	TCHAR* pText = GetTxtFromMgr(5067); //  "����ǰ( alt+i)"
	//	personinventory->SetTitle(pText,CONTROLLER_TITLE_COLOR,11);
	//	personinventory->m_pInventoryListView->MoveController( 40, 17 );
	//	personinventory->m_pWeightStatic->MoveController( 96, 3 );
	//	//KHY - 0618 - ����.�׻� false. 		
	//	personinventory->m_pMoveItemToHorseListView->Show( false );
	//	personinventory->m_pMoveItemToBag0ListView->Show( false );
	//	personinventory->m_pMoveItemToBag1ListView->Show( false );
	//	//////////////////////
	//	personinventory->m_pMakeItemBtn->Show( true );
	//	personinventory->m_pEnchantItemBtn->Show( true );
	//	personinventory->m_pItemmallListBtn->Show( true );
	//	personinventory->m_pButtonMini->Show( true );
	//	personinventory->m_pButtonMax->Show( true );
	//	personinventory->SetMoveable( true );	
	//	//KHY - 0618 - ����.�׻� false. 
	//	personinventory->m_pStatic[0]->Show( false );
	//	personinventory->m_pStatic[1]->Show( false );
	//	personinventory->m_pStatic[2]->Show( false);
	//	//////////////////////
	//	personinventory->m_pCloseButton->Show(true);
	//	personinventory->m_pCloseButton->MoveController(GetWidth() - 16, 3);
	//	//personinventory->m_pMakeItemBtn->MoveController( 23, 280 );
	//	//personinventory->m_pItemmallListBtn->MoveController( 23, 300 );
	//}

	if ( ( pclclient->pclCM->CR[1]->HaveHorse() == false )  &&
		( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique < 1) && 
		( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique < 1) )
	{
		m_bMax = false;
		bSet = false;
	}

	personinventory->m_pWeightStatic->Show( true );

	if(bSet)
	{
		personinventory->SetFileName( TEXT("NInterface/interface/INTERFACE_218x239_00_000.SPR") );
		personinventory->SetDialogPos( pclclient->GetScreenXSize() - 218 , 250 , 218, 239 );
		TCHAR* pText = GetTxtFromMgr(5067); //  "����ǰ( alt+i)"
		personinventory->SetTitle(pText,CONTROLLER_TITLE_COLOR,11);
		personinventory->m_pMoveItemToHorseListView->Show( false );
		personinventory->m_pMoveItemToBag0ListView->Show( false );
		personinventory->m_pMoveItemToBag1ListView->Show( false );
		personinventory->SetMoveable( false );
		personinventory->m_pStatic[0]->Show( false );
		personinventory->m_pStatic[1]->Show( false );
		personinventory->m_pStatic[2]->Show( false );
		personinventory->m_pButtonMini->Show( true );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			personinventory->m_pButtonSpaceBox->Show( true );
		}		
		else
		{
			personinventory->m_pButtonMax->Show( true );
		}
		
		personinventory->m_pMakeItemBtn->Show( true );
		personinventory->m_pEnchantItemBtn->Show( true );
		personinventory->m_pItemmallListBtn->Show( true );

		if ( pclclient->pclCM->CR[1]->HaveHorse() )//���κ��丮.
		{
			horseinventory->CDialogController::Show( true );
			horseinventory->m_pMakeItemBtn->Show( true );
			horseinventory->m_pEnchantItemBtn->Show( true );
			horseinventory->m_pItemmallListBtn->Show( true );
			personinventory->SetFileName( TEXT("NInterface/interface/INTERFACE_182x239_00_000.SPR") );
			personinventory->SetDialogPos( pclclient->GetScreenXSize() - 182 , 250 , 182, 239 );
			TCHAR* pText = GetTxtFromMgr(4661); //  "����ǰ( alt+i)"<<07.0608�ڿ� (alt+i)������ ���� �ؽ�Ʈ��ü

			personinventory->SetTitle(pText,CONTROLLER_TITLE_COLOR,11);
			personinventory->m_pInventoryListView->MoveController( 3, 17 );
			personinventory->m_pWeightStatic->MoveController( 60, 3 );
			personinventory->m_pButtonMini->Show( false );
			
			if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
			{
				personinventory->m_pButtonSpaceBox->Show( false );
			}
			else
			{
				personinventory->m_pButtonMax->Show( false );
			}

			personinventory->m_pMakeItemBtn->Show( false );
			personinventory->m_pEnchantItemBtn->Show( false );
			personinventory->m_pItemmallListBtn->Show( false );
			personinventory->m_pCloseButton->Show(true);
			personinventory->m_pCloseButton->MoveController(GetWidth() - 16, 3);

		}
		if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG ].siUnique > 0 )
		{
			bag0inventory->CDialogController::Show( true );
			//personinventory->m_pMakeItemBtn->Show( false );
			//personinventory->m_pItemmallListBtn->Show( false );
			//bag0inventory->m_pMakeItemBtn->MoveController( 23, 151 );
			//bag0inventory->m_pMakeItemBtn->Show( true );
			//bag0inventory->m_pItemmallListBtn->MoveController( 23, 171 );
			//bag0inventory->m_pItemmallListBtn->Show( true );
		}
		//else
		//{
		//	personinventory->m_pMakeItemBtn->MoveController( 23, 238 );
		//	personinventory->m_pItemmallListBtn->MoveController( 23, 258 );
		//}
		if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique > 0 )
		{
			bag1inventory->CDialogController::Show( true );
		}

		personinventory->m_pCloseButton->Show(true);
		personinventory->m_pCloseButton->MoveController(personinventory->GetWidth() - 16, 3);
	}
	else
	{
		horseinventory->CDialogController::Show( false );
		bag0inventory->CDialogController::Show( false );
		bag1inventory->CDialogController::Show( false );
		personinventory->SetFileName( TEXT("NInterface/interface/INTERFACE_218x280_00_000.SPR") );
		personinventory->SetDialogPos( pclclient->GetScreenXSize() - 218 , 250 , 218, 280 );
		TCHAR* pText = GetTxtFromMgr(5067); //  "����ǰ( alt+i)"
		personinventory->SetTitle(pText,CONTROLLER_TITLE_COLOR,11);
		personinventory->m_pInventoryListView->MoveController( 40, 17 );
		personinventory->m_pWeightStatic->MoveController( 96, 3 );
//KHY - 0618 - ����.�׻� false. 		
		personinventory->m_pMoveItemToHorseListView->Show( true );
		personinventory->m_pMoveItemToBag0ListView->Show( true );
		personinventory->m_pMoveItemToBag1ListView->Show( true );
//////////////////////
		personinventory->m_pMakeItemBtn->Show( true );
		personinventory->m_pEnchantItemBtn->Show( true );
		personinventory->m_pItemmallListBtn->Show( true );
		personinventory->m_pButtonMini->Show( true );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			personinventory->m_pButtonSpaceBox->Show( true );
		}
		else
		{
			personinventory->m_pButtonMax->Show( true );
		}

		personinventory->SetMoveable( true );	
//KHY - 0618 - ����.�׻� false. 
		personinventory->m_pStatic[0]->Show( true );
		personinventory->m_pStatic[1]->Show( true );
		personinventory->m_pStatic[2]->Show( true );
//////////////////////
		personinventory->m_pCloseButton->Show(true);
		personinventory->m_pCloseButton->MoveController(GetWidth() - 16, 3);
		//personinventory->m_pMakeItemBtn->MoveController( 23, 280 );
		//personinventory->m_pItemmallListBtn->MoveController( 23, 300 );
	}
}

void CNNewInventory::CheckWrongSelectedInven()//�߸����κ�
{

	if(m_bHorseHave == false)
	{
		if(m_siCurrentInventoryIndex == TAB_SELECTED_HORSE)
		{
			SelectInven(TAB_SELECTED_PERSON);
		}
	}

	if(m_bBagHave == false)
	{
		if(m_siCurrentInventoryIndex == TAB_SELECTED_BAG)
		{
			SelectInven(TAB_SELECTED_PERSON);
		}
	}
}

void CNNewInventory::SelectInven(SI16 SelectInventoryIndex)//�ּ�ó�� �ƾ��� �κ��̴�,.
{
	//m_siCurrentInventoryIndex = SelectInventoryIndex;

	//if(m_siCurrentInventoryIndex == TAB_SELECTED_PERSON)
	//{
//		m_pStatic[0]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_HORSE );
//		m_pStatic[1]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_BAG );
//
//		m_pButtonManInventory->SetSelect(TRUE);
//		m_pButtonHorseInventory->SetSelect(FALSE);
//		m_pButtonBagInventory->SetSelect(FALSE);
//	}
//	else if( m_siCurrentInventoryIndex == TAB_SELECTED_HORSE)
//	{
//		m_pStatic[0]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_PERSON );
//		m_pStatic[1]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_BAG );	
//
//		m_pButtonManInventory->SetSelect(FALSE);
//		m_pButtonHorseInventory->SetSelect(TRUE);
//		m_pButtonBagInventory->SetSelect(FALSE);
//	}
//	else if( m_siCurrentInventoryIndex == TAB_SELECTED_BAG)
//	{
//		m_pStatic[0]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_PERSON );
//		m_pStatic[1]->SetFontIndex( INVENTORY_TAB_IMAGE_FONT_INDEX_HORSE );
//
//		m_pButtonManInventory->SetSelect(FALSE);
//		m_pButtonHorseInventory->SetSelect(FALSE);
//		m_pButtonBagInventory->SetSelect(TRUE);
//	}
}

void CNNewInventory::ShowInvenWeight()
{
	if ( GetDialogControllerID() != NNEWINVENTORY_DLG || m_bMini )
		return;

	SI32 siTotalWeight = pclClient->pclCM->CR[1]->GetTotalWeight();		// ���� �κ��丮�� �ѹ���
	SI32 siMaxWeight = pclClient->pclCM->CR[1]->GetMaxWeight();	

	// ������ ���Կ� ���� ������ ����
	static SI32	oldsiTotalWeight = 0;
	static SI32	oldsiMaxWeight = 0;

	if( oldsiTotalWeight == siTotalWeight && oldsiMaxWeight == siMaxWeight) return;

	oldsiTotalWeight = siTotalWeight;
	oldsiMaxWeight = siMaxWeight;


	// 20.0/30.0   ��� ����ǥ�� ���ڿ�
	TCHAR strWeightBuffer[ 128 ] = TEXT("");
	// ��� �ִ� �ִ� ����
	TCHAR* pText = GetTxtFromMgr(1158);
	StringCchPrintf( strWeightBuffer, 128, pText, (float)siTotalWeight/10.0, (float)siMaxWeight/10.0);



	m_pWeightStatic->SetText(strWeightBuffer,DT_LEFT | DT_VCENTER | DT_SINGLELINE );

	if( siTotalWeight > siMaxWeight  )     
	{ 
		m_pWeightStatic->SetFontColor( RGB(225,50,50) );
	}
	else 
	{
		m_pWeightStatic->SetFontColor( CONTROLLER_TITLE_COLOR );
	}


	m_pWeightStatic->Refresh();
}

void CNNewInventory::ShowSlotNum()
{
	if ( GetDialogControllerID() != NNEWINVENTORY_DLG )
	{
		m_pWeightStatic->SetText(TEXT(""),DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		return;
	}

	cltClient* pclclient = (cltClient*)pclClient;

	cltCharClient* pclchar = (cltCharClient*)pclClient->pclCM->CR[1];

	SI32 maxSlotNum = MAX_ITEM_PER_INVENTORY;
	SI32 curSlotNum = 0;

	for ( SI32 i = PERSONITEM_INV0 ; i < PERSONITEM_INV0 + MAX_ITEM_PER_INVENTORY ; i++ )
	{
		if ( pclchar->pclCI->clCharItem.clItem[i].siUnique > 0 )
		{
			++curSlotNum;
		}
	}

	if( pclchar->HaveHorse() )
	{
		maxSlotNum += MAX_ITEM_PER_INVENTORY;

		for ( SI32 i = PERSONITEM_HORSE0 ; i < PERSONITEM_HORSE0 + MAX_ITEM_PER_INVENTORY ; i++ )
		{
			if ( pclchar->pclCI->clCharItem.clItem[i].siUnique > 0 )
			{
				++curSlotNum;
			}
		}
	}

	if( pclchar->pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique != 0 )
	{
		maxSlotNum += MAX_ITEM_PER_BAG;

		for ( SI32 i = PERSONITEM_BAG0 ; i < PERSONITEM_BAG0 + MAX_ITEM_PER_BAG ; i++ )
		{
			if ( pclchar->pclCI->clCharItem.clItem[i].siUnique > 0 )
			{
				++curSlotNum;
			}
		}
	}

	if( pclchar->pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique != 0 )
	{
		maxSlotNum += MAX_ITEM_PER_BAG;

		for ( SI32 i = PERSONITEM_BAG1 ; i < PERSONITEM_BAG1 + MAX_ITEM_PER_BAG ; i++ )
		{
			if ( pclchar->pclCI->clCharItem.clItem[i].siUnique > 0 )
			{
				++curSlotNum;
			}
		}
	}

	TCHAR buf[64];
	StringCchPrintf( buf, 64, TEXT("%d/%d"), curSlotNum, maxSlotNum );
	m_pWeightStatic->SetText(buf,DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
}

bool CNNewInventory::CheckCanEnchintItem(SI32 siUnique)
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 sitype = pclclient->pclItemManager->GetItemType(siUnique);
	switch(sitype)
	{
	case  ITEMTYPE_SWORD:
	case  ITEMTYPE_SPEAR:
	case  ITEMTYPE_STAFF:
	case  ITEMTYPE_AXE:
	case  ITEMTYPE_BOW:
	case  ITEMTYPE_GUN:
	case  ITEMTYPE_CANNON:
	case  ITEMTYPE_ARMOUR:
	case  ITEMTYPE_BELT:
	case  ITEMTYPE_SHOES:
	case  ITEMTYPE_HELMET:
		return true;						 	

	}				
	return false;
}				

bool CNNewInventory::CheckCanPutonItem(SI32 siUnique)
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 sitype = pclclient->pclItemManager->GetItemType(siUnique);
	switch(sitype)
	{
	case  ITEMTYPE_SWORD:
	case  ITEMTYPE_SPEAR:
	case  ITEMTYPE_STAFF:
	case  ITEMTYPE_AXE:
	case  ITEMTYPE_BOW:
	case  ITEMTYPE_GUN:
	case  ITEMTYPE_CANNON:
	case  ITEMTYPE_ARMOUR:
	case  ITEMTYPE_BELT:
	case  ITEMTYPE_SHOES:
	case  ITEMTYPE_HELMET:
	case  ITEMTYPE_AVATAR_MANTLE:
	case  ITEMTYPE_AVATAR_DRESS:
	case  ITEMTYPE_AVATAR_HAT:
	case  ITEMTYPE_AVATAR_NECK:
	case  ITEMTYPE_AVATAR_RING:
		return true;						 	

	}				
	return false;
}				


bool CNNewInventory::CheckCanEquipItem(SI32 siUnique)
{
	cltClient *pclclient = (cltClient *)pclClient;

	SI32 sitype = pclclient->pclItemManager->GetItemType(siUnique);

	cltItem clItem(siUnique);


	// �ҷ��������϶� ��������
	if (clItem.IsBulletItem())
		return true;

/*	//���� �Ѿ� ���밡��[����]
	if (siUnique == ITEMUNIQUE(7857)||ITEMUNIQUE(7856)) {
		return true;
	}*/

	// ��, ���, ���ô� �϶��� ��������
	if (siUnique == ITEMUNIQUE(10090) || siUnique == ITEMUNIQUE(10100) ||siUnique == ITEMUNIQUE(17100)
		|| siUnique == ITEMUNIQUE(17150))
		return true;

	switch(sitype)
	{
	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HAT:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_NECK:
	case ITEMTYPE_AVATAR_MANTLE:
	case ITEMTYPE_AVATAR_DRESS:
	case ITEMTYPE_AVATAR_HAT:		
	case ITEMTYPE_AVATAR_NECK:	
	case ITEMTYPE_AVATAR_RING:
	case ITEMTYPE_MANTLE:
		{
			return true;
		}
		break;
	}

	return false;
}				

void CNNewInventory::MakeSetEnchant(bool bMakeButton)
{
	m_pMakeItemBtn->Enable(bMakeButton);    
	m_bMakeButton = bMakeButton;
}


void CNNewInventory::CheckCharStatusChanged()
{	
	cltCharCommon* pclchar = pclClient->pclCM->CR[1];		
	static SI32 oldLevel = pclchar->pclCI->clIP.GetLevel();
	static SI32 oldStr = pclchar->clPB.clTotalBA.GetStr();
	static SI32 oldDex = pclchar->clPB.clTotalBA.GetDex();
	static SI32 oldMag = pclchar->clPB.clTotalBA.GetMag();
	static SI32 oldVit = pclchar->clPB.clTotalBA.GetVit();
	static SI32	oldHnd = pclchar->clPB.clTotalBA.GetHnd();
	static SI32	oldFame = pclchar->pclCI->clIP.siFameLevel;

	//static cltPSkillInfo oldSkilinfo =	pclchar->pclCI->clCharSkill;


	if( pclchar->pclCI->clIP.GetLevel() !=  oldLevel) m_bStatusChanged = TRUE;
	if( pclchar->clPB.clTotalBA.GetStr() !=  oldStr) m_bStatusChanged = TRUE;
	if( pclchar->clPB.clTotalBA.GetDex() !=  oldDex) m_bStatusChanged = TRUE;
	if( pclchar->clPB.clTotalBA.GetMag() !=  oldMag) m_bStatusChanged = TRUE;
	if( pclchar->clPB.clTotalBA.GetVit() !=  oldVit) m_bStatusChanged = TRUE;
	if( pclchar->clPB.clTotalBA.GetHnd() !=  oldHnd) m_bStatusChanged = TRUE;
	if( pclchar->pclCI->clIP.siFameLevel !=  oldFame) m_bStatusChanged = TRUE;


	if(m_bStatusChanged == TRUE)
	{	
		LoadItemData();

		m_bStatusChanged = FALSE;
		oldLevel = pclchar->pclCI->clIP.GetLevel();
		oldStr = pclchar->clPB.clTotalBA.GetStr();
		oldDex = pclchar->clPB.clTotalBA.GetDex();
		oldMag = pclchar->clPB.clTotalBA.GetMag();
		oldVit = pclchar->clPB.clTotalBA.GetVit();
		oldHnd = pclchar->clPB.clTotalBA.GetHnd();
		oldFame = pclchar->pclCI->clIP.siFameLevel;

	}
}

void CNNewInventory::EquipItem( SI16 Pos )
{
	cltClient	*pclclient		= (cltClient *)pclClient;
	SI16		SelectedIndex	= Pos;
	m_siSelectedIndex			= Pos;
	m_siCurrentSummonIndex		= SELECTED_HUMAN; 

	// â�� Ȥ�� �ȿ��� �������� �����Ƿ�
	if ( pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ] )
	{
		m_siCurrentSummonIndex = ((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->m_siCurrentSummonIndex;
	}
	

	if ( m_siSelectedIndex >= 0 )
	{
		m_bClickChangeItem = true;

		SI16 SelectPos	= -1;
		SI16 StartPos	= 0;

		SelectPos = m_siSelectedIndex;

		if ( SelectPos > -1 )
		{
			SI32 siItemUinque	= m_pclInventoryItem[m_siSelectedIndex].siUnique; //m_pPersonItemInfo->clItem[ m_siSelectedIndex ].siUnique;
			SI32 ItemType		= pclclient->pclItemManager->GetItemType(siItemUinque);
			SI32 siItemType		= GetInventoryType(ItemType);

			if( PERSONITEM_NONE == siItemType)
			{
				m_pInventoryListView->ClearSelectedItem();
				m_siSelectedIndex = -1;
				m_bClickChangeItem = false;
				return;
			}

			//KHY - 1023 - �Ѿ� ȭ�� ���ѻ�� ����.
			if( !(pclclient->m_pDialog[ NPERSONALSHOP_DLG ]) )
			{
				if ( SELECTED_HUMAN ==  m_siCurrentSummonIndex )
				{
					if ( m_pclInventoryItem[ siItemType ].siUnique == 0 )
					{											
						MoveItem( siItemType );
					}
					else if(m_pclInventoryItem[ siItemType ].siUnique != 0 && ItemType != ITEMTYPE_SCROLL)
					{											
						ChangeItem( siItemType );										
					}

				}
				else
				{
					SI32 siSummonInventoryType = GetInventoryTypeForSummon(ItemType);
					if ( PERSONITEM_NONE == siSummonInventoryType )
					{
						TCHAR* pTitle	= GetTxtFromMgr(1074);
						TCHAR* pText	= GetTxtFromMgr(1075);

						pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText( pTitle, pText);
					}
					else
					{
						MoveItem( GetInventoryTypeForSummon(ItemType) );
					}
				}
			}
		}

		m_pInventoryListView->ClearSelectedItem();
		m_siSelectedIndex = -1;
		m_bClickChangeItem = false;
	}
	else
	{
		m_siSelectedIndex = SelectedIndex;
		//m_siPreItemDragIndex = -1;
	}
}
void CNNewInventory::SetInventoryMode(SI16 DialogId)
{
	cltClient* pclclient = (cltClient*)pclClient;

	SetDialogControllerID( DialogId );
	CNNewInventory* inventory = (CNNewInventory*)pclclient->m_pDialog[DialogId];

	TCHAR* pszText = NULL;

	switch( DialogId )
	{
	case NNEWINVENTORY_HORSE_DLG:
		inventory->SetFileName( TEXT("NInterface/interface/INTERFACE_218x239_00_000.SPR") );
		inventory->SetDialogPos( pclclient->GetScreenXSize() - 399 , 250 , 218, 239 );
		pszText = GetTxtFromMgr(6349);
		inventory->SetTitle(pszText ,CONTROLLER_TITLE_COLOR,11);
		inventory->m_pMoveItemToHorseListView->Show( false );
		inventory->m_pMoveItemToBag0ListView->Show( false );
		inventory->m_pMoveItemToBag1ListView->Show( false );
		inventory->m_pMakeItemBtn->Show( false );
		inventory->m_pEnchantItemBtn->Show( false );
		inventory->m_pItemmallListBtn->Show( false );
		inventory->m_pButtonMini->Show( true );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			inventory->m_pButtonSpaceBox->Show( true );
		}
		else
		{
			inventory->m_pButtonMax->Show( true );
		}

		inventory->SetMoveable( false );
		inventory->m_pCloseButton->Show( false );
		inventory->m_pStatic[0]->Show( false );
		inventory->m_pStatic[1]->Show( false );
		inventory->m_pStatic[2]->Show( false );
		break;
	case NNEWINVENTORY_BAG0_DLG:
		inventory->SetFileName(TEXT("NInterface/interface/INTERFACE_182x151_00_000.SPR") );
		inventory->SetDialogPos( pclclient->GetScreenXSize() - 182 , 488 , 182, 151 );
//		inventory->m_pInventoryListView->MoveController(3, 17);
		inventory->m_pInventoryListView->SetControllerPos( 3, 17, 180, 134, 180, 134 );
		pszText = GetTxtFromMgr(6350);
		inventory->SetTitle(pszText,CONTROLLER_TITLE_COLOR,11);
		inventory->m_pMoveItemToHorseListView->Show( false );
		inventory->m_pMoveItemToBag0ListView->Show( false );
		inventory->m_pMoveItemToBag1ListView->Show( false );
		inventory->m_pMakeItemBtn->Show( false );
		inventory->m_pEnchantItemBtn->Show( false );
		inventory->m_pItemmallListBtn->Show( false );
		inventory->m_pButtonMini->Show( false );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			inventory->m_pButtonSpaceBox->Show( false );				
		}
		else
		{
			inventory->m_pButtonMax->Show( false );
		}

		inventory->SetMoveable( false );
		inventory->m_pCloseButton->Show( false );
		inventory->m_pStatic[0]->Show( false );
		inventory->m_pStatic[1]->Show( false );
		inventory->m_pStatic[2]->Show( false );
		break;
	case NNEWINVENTORY_BAG1_DLG:
		inventory->SetFileName(TEXT("NInterface/interface/INTERFACE_182x151_00_000.SPR") );
		inventory->SetDialogPos( pclclient->GetScreenXSize() - 363 , 488 , 182, 151 );
//		inventory->m_pInventoryListView->MoveController(3, 17);
		inventory->m_pInventoryListView->SetControllerPos( 3, 17, 180, 134, 180, 134 );
		pszText = GetTxtFromMgr(6351);
		inventory->SetTitle(pszText,CONTROLLER_TITLE_COLOR,11);
		inventory->m_pMoveItemToHorseListView->Show( false );
		inventory->m_pMoveItemToBag0ListView->Show( false );
		inventory->m_pMoveItemToBag1ListView->Show( false );
		inventory->m_pMakeItemBtn->Show( false );
		inventory->m_pEnchantItemBtn->Show( false );
		inventory->m_pItemmallListBtn->Show( false );
		inventory->m_pButtonMini->Show( false );
		
		if( pclclient->IsCountrySwitch( Switch_SpaceBox ) )
		{
			inventory->m_pButtonSpaceBox->Show( false );
		}	
		else
		{
			inventory->m_pButtonMax->Show( false );
		}

		inventory->SetMoveable( false );
		inventory->m_pCloseButton->Show( false );
		inventory->m_pStatic[0]->Show( false );
		inventory->m_pStatic[1]->Show( false );
		inventory->m_pStatic[2]->Show( false );
		break;
	}
}


bool CNNewInventory::EndClickAndDrop( cltClickAndDrop* pclClickAndDrop )
{
	cltClient* pclclient = (cltClient*)pclClient;

	if(pclClickAndDrop == NULL)										return false;
	if(pclClickAndDrop->IsType(CLICKANDDROP_TYPE_ITEM) == false)	return false;

	cltClickAndDrop_Item* pclClickAndDrop_Item = (cltClickAndDrop_Item*)pclClickAndDrop;

	switch(pclClickAndDrop_Item->m_siSrcDialogID)
	{
	// �κ��丮���� �κ��丮�� �̵��ϴ� ���
	case NNEWINVENTORY_DLG:
	case NNEWINVENTORY_HORSE_DLG:
	case NNEWINVENTORY_BAG0_DLG:
	case NNEWINVENTORY_BAG1_DLG:
		{
			SI32 siSelectedIndex = m_pInventoryListView->GetLastSelectedItemIndex();
			
			// ���� ��ġ�� ������ �̹Ƿ� ����.��
			if( siSelectedIndex == pclClickAndDrop_Item->m_siPara1 )
			{
				return true;
			}

			if( m_pclInventoryItem[ siSelectedIndex ].siUnique <= 0 )
			{
				MoveItem(pclClickAndDrop_Item->m_siPara1, siSelectedIndex);
			}
			else
			{
				ChangeItem(pclClickAndDrop_Item->m_siPara1, siSelectedIndex);
			}
		
            return true;
		}
		break;

	// �������â���� �κ��丮�� �̵��Ǿ���.
	case NNEWEQUIPWINDOW_DLG:
		{
			SI32 siSelectedIndex = m_pInventoryListView->GetLastSelectedItemIndex();
			if( pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ] )
			{
				m_siCurrentSummonIndex = ((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->m_siCurrentSummonIndex;

				if ( SELECTED_HUMAN == m_siCurrentSummonIndex )
				{
					if( m_pclInventoryItem[ siSelectedIndex ].siUnique <= 0 )
					{
						((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->MoveItem(pclClickAndDrop_Item->m_siPara1, siSelectedIndex);
					}
					else
					{
						((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->ChangeItem(siSelectedIndex, pclClickAndDrop_Item->m_siPara1);
					}
				}
				else
				{
					((CNEquipWindow*)pclclient->m_pDialog[ NNEWEQUIPWINDOW_DLG ])->MoveItem(pclClickAndDrop_Item->m_siPara1, siSelectedIndex);
				}
			}

			return true;
		}
		break;
	}

	return false;
}

void CNNewInventory::GetPositionFromControllerID( IN SI16 siControllerID, IN SI16 siLastSelectedIndex, OUT SI16* psiSelectPos, OUT SI16* psiMakeItemPos )
{
	if ( (NULL == psiSelectPos) || (NULL == psiMakeItemPos) )
	{
		return;
	}

	SI16 siSelectPos	= -1;
	SI16 siMakeItemPos	= -1;


	switch( siControllerID )
	{
		case NNEWEQUIPWINDOW_DLG_LISTVIEW1:
			siSelectPos = PERSONITEM_HELMET;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW2:
			siSelectPos = PERSONITEM_ARMOUR;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW3:
			siSelectPos = PERSONITEM_WEAPON1;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW4:
			siSelectPos = PERSONITEM_NECK;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW5:
			siSelectPos = PERSONITEM_RING1;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW6:
			siSelectPos = PERSONITEM_RING2;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW7:
			siSelectPos = PERSONITEM_BELT;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW8:
			siSelectPos = PERSONITEM_SHOES;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW9:
			siSelectPos = PERSONITEM_WEAPON2;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW10:
			siSelectPos = PERSONITEM_MANTLE;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW11:
			siSelectPos = PERSONITEM_BAG;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW12:
			siSelectPos = PERSONITEM_HAT;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW13:
			siSelectPos = PERSONITEM_DRESS;
			break;
		case NNEWEQUIPWINDOW_DLG_LISTVIEW14:
			siSelectPos = PERSONITEM_BAG_SUB;
			break;

		case NNEWINVENTORY_DIALOG_MOVEITEMTOHORSE_LISTVIEW:
			{	
				if ( pclClient->pclCM->CR[1]->HaveHorse() )
				{
					SI16		pos;
					cltItem		cltoitem;
					SI32		rtnvalue;

					if(pclClient->pclCM->CR[1]->pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_HORSE, 
						&m_pclInventoryItem[ m_siSelectedIndex ],
						NULL, 
						&pos, 
						&cltoitem,
						&rtnvalue) == true)
					{
						siSelectPos = pos;
					}
					else
					{
						siSelectPos = -1;
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
						siSelectPos = pos;
					}
					else
					{
						siSelectPos = -1;
					}
				}
			}
			break;
		case NNEWINVENTORY_DIALOG_MOVEITEMTOBAG1_LISTVIEW:
			{
				if ( pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[ PERSONITEM_BAG_SUB ].siUnique > 0  )
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
						siSelectPos = pos;
					}
					else
					{
						siSelectPos = -1;
					}
				}
			}
			break;
		case NNEWINVENTORY_DIALOG_INVENTORY_LISTVIEW:
			siSelectPos = siLastSelectedIndex;
			break;
		case NEWMAKE_LISTVIEW2: //��
			siMakeItemPos  = NEWMAKE_TOOLSFOR_MAKEITEM;
			break;
		case NEWMAKE_LISTVIEW1: //���
			siMakeItemPos  = NEWMAKE_MATERIALFOR_MAKEITEM;
			break;		
		case NEWMAKE_LISTVIEW_ORIGINALITEM:
			siMakeItemPos  = NEWMAKE_ORIGINALFOR_ENCHANT;
			break;
		case NEWMAKE_LISTVIEW_MATERIALITEM:
			siMakeItemPos  = NEWMAKE_MATFOR_ENCHANT;
			break;
		case NEWMAKE_LISTVIEW_ELEMENTITEM:
			siMakeItemPos  = NEWMAKE_ELEFOR_ENCHANT;
			break;
	}

	*psiSelectPos	= siSelectPos;
	*psiMakeItemPos	= siMakeItemPos;
}
