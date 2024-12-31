#include "NFeastDlg.h"

#include "../../InterfaceMgr/Interface/List.h"
#include "../StrBaseDlg/StrInventory.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-Feast.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"

#include "../../InterfaceMgr/InterfaceMgr.h"

#include "../../FeastEffect/FeastEffectManager.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NPartyHallPresentDlg::NPartyHallPresentDlg()
{
	m_pMyInventory = new NStrInventory;
	
	m_siPresentItemInvenPos = 0;
}

NPartyHallPresentDlg::~NPartyHallPresentDlg()
{
	NDelete( m_pMyInventory );	
}

void NPartyHallPresentDlg::InitDlg()
{
	SetControlMap( LISTVIEW_INVENTORY,		TEXT("listview_inventory") );
	SetControlMap( LISTVIEW_PRESENT_LIST,	TEXT("listview_present_list") );
	SetControlMap( BUTTON_INPUT_PRESENT,	TEXT("button_input_present") );
	SetControlMap( EDIT_ITEM_NAME,			TEXT("editbox_item_name") );
	SetControlMap( EDIT_ITEM_NUM,			TEXT("editbox_item_num") );
	SetControlMap( EDIT_EXPLAIN,			TEXT("editbox_NONAME1") );
	
	CEdit* pEdit = (CEdit*)m_pControlMap[ EDIT_EXPLAIN ];		
	pEdit->SetText(GetTxtFromMgr(8141));

	m_pMyInventory->CreateInventory( MAX_ITEM_PER_PERSON, (CListView*)m_pControlMap[ LISTVIEW_INVENTORY ] );

	SetMyInventory();
	SetPresentItem();
}

void NPartyHallPresentDlg::SetMyInventory( void )
{
	// MyInventory
	m_pMyInventory->m_pListView->SetBKColorUse( true );
	m_pMyInventory->m_pListView->SetBorder( true );
	m_pMyInventory->LoadMyInventory( true );

}

void NPartyHallPresentDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltFeastManager *pFeastManager = (cltFeastManager *)m_pStrManager;

	
	CASE_CONTROL( EDIT_ITEM_NUM )
	{
		CEdit* pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NUM ];		
		
		// editbox�� �ִ� �Է� ������ ���� ������ش�.
		EditCountRange( pEdit, 10000 );    
		
	}
	else CASE_CONTROL( LISTVIEW_INVENTORY )
	{
		CListView* pListView = (CListView*)m_pControlMap[ LISTVIEW_INVENTORY ];		

		SI32 TempUserInventorySelectedIndex = pListView->GetSelectedItemIndex();

		if(TempUserInventorySelectedIndex < 0)
			return;

		m_siPresentItemInvenPos	= TempUserInventorySelectedIndex;
		
		cltItem* pSelectItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siPresentItemInvenPos];

		TCHAR buffer[8] = "";
		itoa(pSelectItem->siItemNum, buffer, 10);

		CEdit* pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NUM ];	
		pEdit->SetText(buffer);

		TCHAR* ItemName = (TCHAR*)pclClient->pclItemManager->GetName( pSelectItem->siUnique );
		pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NAME ];	
		pEdit->SetText(ItemName);

	}
	else CASE_CONTROL( BUTTON_INPUT_PRESENT )
	{
		CEdit* pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NUM ];	
		SI32 ItemNum = atoi(pEdit->GetText());

		// ���� ������ ������ �ø����� �������� ������ ���.
		cltItem* pSelectItem = &pclClient->pclCM->CR[1]->pclCI->clCharItem.clItem[m_siPresentItemInvenPos];

		// ������ ������ ������ ���ų� ������ �����ʴ� ������ ����� ����.
		if( 0 >= ItemNum || pSelectItem->siItemNum < ItemNum )
			return;

		
		cltPatyHallResvInfo* pPatyHallResvInfo     = NULL;
		cltPatyHallResvInfo* pPatyHallResvInfoList = (cltPatyHallResvInfo*)&pclClient->pclFeastManager->clPartyHallResvInfo[0];

		SI32 PsersonID = pclClient->pclCM->CR[1]->pclCI->GetPersonID(); 
		// ��Ƽ�� ��ġ.
		for( SI32 PartyHallCount = 0; PartyHallCount < MAX_PARTYHALL_MAP; ++PartyHallCount)
		{
			pPatyHallResvInfo = &pPatyHallResvInfoList[PartyHallCount*MAX_PARTYHALL_RESERVATION_INFO_LIST];
			for( SI32 ReservationCount = 0; ReservationCount < MAX_PARTYHALL_RESERVATION_INFO_LIST; ++ReservationCount)
			{
				// ����� ��ġ.
				if( PsersonID == pPatyHallResvInfo[ReservationCount].m_siPersonID)
				{
					// ������ ��ġ.
					for( SI32 ItemIndex = 0; ItemIndex < RESERVATIO_PRESENT_ITEM; ++ItemIndex)
					{
						// �̹� ��ϵ� �������̸�.
						if( pSelectItem->siUnique == pPatyHallResvInfo[ReservationCount].m_PresentItem[ItemIndex].m_siItemUnique )
						{
							return;
						}
						
						// �������� ���� ��ġ. (�������� ���°���.)
						if( 0 >= pPatyHallResvInfo[ReservationCount].m_PresentItem[ItemIndex].m_siItemUnique )
						{
							cltGameMsgRequest_PartyHall_Add_Present sendmsg( pSelectItem->siUnique, ItemNum, PartyHallCount, m_siPresentItemInvenPos, ItemIndex );
							cltMsg clMsg(GAMEMSG_REQUEST_PARTYHALL_ADD_PRESENT, sizeof(sendmsg), (BYTE*)&sendmsg);
							pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
							
							
							m_siPresentItemInvenPos = 0;
							
							CEdit* pEdit = NULL;
							pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NUM ];	
							pEdit->SetText("");

							pEdit = (CEdit*)m_pControlMap[ EDIT_ITEM_NAME ];	
							pEdit->SetText("");
							return;
						}
					}
				}
			}
		}
	}
}

void NPartyHallPresentDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	
}



BOOL NPartyHallPresentDlg::ShowItemListInCombo( CComboBox *pCombo, SI32 itemtypeunique, bool btradeinterface )
{
	cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;

	SI32 i;
	// �޺� �ڽ��� �����.
	pCombo->Clear();

	stComboBoxItemData itemdata;

	// �޺� �ڽ��� �������� ������ �����Ѵ�. 
	for( i = 0;i < MAX_ITEMINFO_NUMBER;i++ )
	{	
		cltItemInfo* pinfo = pclitemmanager->pclItemInfo[i];

		if(pinfo == NULL)continue;
		if(pinfo->siType != itemtypeunique)continue;

		// �־��� Ÿ�԰� ���� �����۸� �����Ѵ�. 
		// ����ڿ��� �������� �������� ��쿡��. 
		bool bshow = false; 

		if(pinfo->IsItemInfoAtb(ITEMINFOATB_NOTTRADE))
		{
			continue;
		}

		if(pinfo->IsItemInfoAtb(ITEMINFOATB_SHOWLIST))
		{
			if(btradeinterface == true)
			{
				//	if(pinfo->IsItemInfoAtb(ITEMINFOATB_TRADELIST)  == true)
				{
					bshow = true;
				}
			}
			else
			{
				bshow = true;
			}

			if(bshow)
			{
				itemdata.Init();
				itemdata.Set( (TCHAR *)pinfo->GetName() );
				pCombo->AddItem( &itemdata );
			}
		}
	}

	return TRUE;
}
void NPartyHallPresentDlg::EditCountRange( CEdit* _pEdit, SI32 _MaxCount )
{
	SI32   ItemCount = atoi( _pEdit->GetText() );

	if( _MaxCount < ItemCount )
	{
		TCHAR szBuffer[64] = "";
		itoa( _MaxCount, szBuffer, 10 );
		_pEdit->SetText( szBuffer );
	}
	else if( 0 >= ItemCount )
	{
		_pEdit->SetText("");
	}
	else
	{
		TCHAR szCount[16] = "";
		itoa(ItemCount, szCount, 10);
		_pEdit->SetText(szCount);
	}
}


void NPartyHallPresentDlg::SetPresentItem( void )
{
	cltClient* pclclient = (cltClient*)pclClient;

	cltFeastManager*	 pFeastManager			 = (cltFeastManager *)m_pStrManager;
	cltPatyHallResvInfo* pclPatyHallResvInfoList = (cltPatyHallResvInfo*)&pFeastManager->clPartyHallResvInfo[0];

	cltPatyHallResvInfo* pclPatyHallResvInfo = NULL;

	
	SI32 PsersonID = pclClient->pclCM->CR[1]->pclCI->GetPersonID(); 
	// ��Ƽ�� ��ġ.
	for( SI32 PartyHallCount = 0; PartyHallCount < MAX_PARTYHALL_MAP; ++PartyHallCount)
	{
		pclPatyHallResvInfo = &pclPatyHallResvInfoList[PartyHallCount*MAX_PARTYHALL_RESERVATION_INFO_LIST];
		for( SI32 ReservationCount = 0; ReservationCount < MAX_PARTYHALL_RESERVATION_INFO_LIST; ++ReservationCount)
		{
			// ����� ��ġ.
			if( PsersonID == pclPatyHallResvInfo[ReservationCount].m_siPersonID)
			{
				pclPatyHallResvInfo	= &pclPatyHallResvInfo[ReservationCount];
				
				//�ݺ��� ���Ḧ ���ؼ�...
				PartyHallCount = MAX_PARTYHALL_MAP;
				break;
			}
		}
	}

	if(NULL == pclPatyHallResvInfo)
		return;	

	CListView* pListView = (CListView*)m_pControlMap[ LISTVIEW_PRESENT_LIST ];
	if( NULL == pListView )
		return;

	pListView->DeleteAllItems();

	stListViewItemData itemdata;
	SI32 GlobalImageIndex	= -1;
	SI32 GlobalImageFont	= -1;
	SI32 StartPos			=  0;
	SI32 id					=  1;

	TCHAR* pItemName = NULL;
	for( SI32 Count = 0; Count < RESERVATIO_PRESENT_ITEM; ++Count ) 
	{
		pItemName = (TCHAR *)pclClient->pclItemManager->GetName( pclPatyHallResvInfo->m_PresentItem[Count].m_siItemUnique );

		if( pItemName ) 
		{
			if ( pclClient->pclItemManager->GetItemGImageFileIndexAndFont( 
				pclPatyHallResvInfo->m_PresentItem[Count].m_siItemUnique, 
				&GlobalImageIndex, &GlobalImageFont ) )
			{

				//	TCHAR* pText = GetTxtFromMgr(676);
				//	sprintf(buffer, pText, ItemName, m_pclItem[i].GetItemNum() );
				TCHAR ToolTipMsg[ MAX_TOOLTIP_MSG_SIZE ] = TEXT("");

				cltItem TempItem;
				TempItem.Init();
				TempItem.siUnique  = pclPatyHallResvInfo->m_PresentItem[Count].m_siItemUnique;
				TempItem.siItemNum = pclPatyHallResvInfo->m_PresentItem[Count].m_siItemNum;

				pclClient->pclItemManager->GetExplain( &TempItem, ToolTipMsg );

				stListViewItemData ListViewItemData;
				ListViewItemData.Set( GlobalImageIndex, GlobalImageFont, Count - StartPos ,pclPatyHallResvInfo->m_PresentItem[Count].m_siItemNum, pItemName, ToolTipMsg );
				pListView->InsertItem( &ListViewItemData );
			}
		}
	}

	pListView->SetBKColorUse( true );
	pListView->SetBorder( true );
}

void NPartyHallPresentDlg::SetItemMaterialInfo(TCHAR* pItemName)
{
	
} 

void NPartyHallPresentDlg::SetMakeItemNumEnable( void )
{

	
}