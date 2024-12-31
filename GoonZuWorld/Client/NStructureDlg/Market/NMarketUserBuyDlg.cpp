#include "NMarketDlg.h"


#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/Edit.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/CheckBox.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"

#include "../../../common/Item/ItemCommon\cltItem.h"
#include "../../../common/skill/skill-manager.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;


//////////////////////////////////////////////////
// ������ ������ ���������� �ʴ´�. NMarketUserBuySubDlg �� ����Ѵ�.
//////////////////////////////////////////////////

NMarketUserBuyDlg::NMarketUserBuyDlg()
{
	bSelectedSwitch = false;
	bMakerSwitch = false;	

	m_siImageIndex = -1;
	m_siImageType = -1;
}

NMarketUserBuyDlg::~NMarketUserBuyDlg()
{
}

void NMarketUserBuyDlg::InitDlg()
{

	m_siImageIndex = -1;
	m_siImageType = -1;

 	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	SetControlMap( STATIC_PRICECOND, TEXT("statictext_pricecond") );
	SetControlMap( CHECK_PRICECOND, TEXT("checkbox_pricecond") );

	SetControlMap( COMBO_ITEMTYPE, TEXT("combobox_itemtype") );
	SetControlMap( COMBO_ITEM, TEXT("combobox_item") );

	SetControlMap( BUTTON_REFRESH, TEXT("button_refresh") );
	SetControlMap( BUTTON_BUY, TEXT("button_buy") );
	SetControlMap( BUTTON_ITEMMALL, TEXT("button_itemmall") );

	SetControlMap( EDIT_AMOUNT, TEXT("editbox_amount") );
	SetControlMap( EDIT_PRICECOND, TEXT("editbox_pricecond") );
	SetControlMap( EDIT_ITEMPRICE, TEXT("editbox_itemprice") );
	SetControlMap( EDIT_EXPLAIN, TEXT("editbox_explain") );

	SetControlMap( LIST_ORDERLIST, TEXT("listbox_orderlist") );
	SetControlMap( IMAGESTATIC_ITEMBACK, TEXT("imagestatic_NONAME1") );

	SetControlMap( EDIT_EXPLAINCHAR, TEXT("editbox_NONAME1")  );
	SetControlMap( STATIC_ITEMNAME, TEXT("statictext_itemname") );
	SetControlMap( STATIC_ITEMTYPE, TEXT("statictext_itemtype") );
	SetControlMap( STATIC_ITEMINFO, TEXT("statictext_imteinfo") );
	SetControlMap( STATIC_CHARINFO, TEXT("statictext_charinfo") );

	m_pControlMap[ EDIT_PRICECOND ]->Show( false );
	m_pControlMap[ STATIC_PRICECOND ]->Show( false );

	((CEdit*)m_pControlMap[ EDIT_AMOUNT ])->SetNumberMode( true );

	// �ֹ� ����Ʈ 
	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

 	TCHAR* pText = GetTxtFromMgr(1227);
	pList->SetColumn( 0, 100, pText );
	pText = GetTxtFromMgr(1678);
	pList->SetColumn( 1, 88, pText );
	pText = GetTxtFromMgr(1679);
	pList->SetColumn( 2, 67, pText );

	pList->Refresh();

	pMarketManager->m_siSelectedBuyList = -1;

	// ������ ������ �����ش�. 
	{
		CComboBox *pComboItemType = (CComboBox*)m_pControlMap[ COMBO_ITEMTYPE ];
		stComboBoxItemData itemdata;

		cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;
		int i;
		// �޺� �ڽ��� �����.
		pComboItemType->Clear();

		// �޺� �ڽ��� �������� ������ �����Ѵ�. 
		for( i = 0; i < MAX_ITEMTYPE_NUMBER; i++ )
		{	
			cltItemTypeInfo* pinfo = pclitemmanager->pclItemTypeInfo[i];
			if(pinfo == NULL)continue;

			if(pinfo->IsAtb(ITEMATB_NOTRADE))continue;

			// �޺�����Ʈ���� ����� �Ӽ��� �ִٸ�
			if( pinfo->IsAtb(ITEMATB_HIDECOMBOLIST) ) continue;


			itemdata.Init();
			itemdata.Set( (TCHAR*)pinfo->GetName() );
			pComboItemType->AddItem( &itemdata );
		}

		pComboItemType->SetCursel(0);

	}



	pMarketManager->ShowResponseOrderSiwtch			= FALSE;
	pMarketManager->bResponseEmptyOrder				= FALSE;
	pMarketManager->CurrentSelectedBuyItemUnique	= 0;
	bSelectedSwitch									= false;
	bMakerSwitch									= false;

	bRequest = FALSE;

	// �����۸� ��ư
	m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );

	((CEdit*)m_pControlMap[EDIT_EXPLAINCHAR])->SetChangeTextDrawMode(true);

}

void NMarketUserBuyDlg::Action()
{
	return;
//--------------------------------------------------------------
// ���̻� ������ �ʴ� â�̹Ƿ� ���� ��. �ٸ� ���� ������ ��ħ
/*
	if( m_pBaseDlg->m_dwActionCount % 5 ) return;

	TCHAR strText[ 1024 ];
	TCHAR tmpText[ 1024 ];
	memset(strText, 0 , sizeof(strText));
	memset(tmpText, 0, sizeof(tmpText));

	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	// �����κ��� ���� �ֹ� ������ �����ش�.
	ShowResponseOrder();

	// ��ǰ�� �ü��� �����ش�. 
	ShowPrice();

	if(bSelectedSwitch == true )
	{
		bSelectedSwitch = false;
		bRequest = TRUE;
		dwRequestTick = GetTickCount();

		// ������ ��������  �Ǹ� �ֹ� ����Ʈ�� ��û�Ѵ�. 
		RequestMarketOrderList( pMarketManager->CurrentSelectedBuyItemUnique );

		cltItemManagerClient *pclItemMgr = ( cltItemManagerClient * )pclClient->pclItemManager;

		SI32 ref = pclItemMgr->FindItemRefFromUnique(pMarketManager->CurrentSelectedBuyItemUnique);
		if(ref <= 0)return ;

		if(pclItemMgr->GetExplain( &pclItemMgr->pclItemInfo[ref]->clItem, strText, false,true,false,0,false ) == FALSE) return;
		
		NTCHARString512	kTmp;
		NTCHARString512	kExplain;

		NTCHARString512	kName;
		NTCHARString512 kType;

		kTmp = strText;


		SI32 siFind1, siFind2;
		// ù���� ������ �̸����� ��������
		siFind1 = kTmp.Find("\r");
		kName = kTmp.SubStr(0, siFind1);
		// ��°���� ������ Ÿ��
		siFind2 = kTmp.Find("\r", siFind1 + 1);
		kType = kTmp.SubStr(siFind1 + 2, siFind2 - siFind1 - 1);

		kExplain = kTmp.SubStr(siFind2 + 1);

//		StringCchPrintf( tmp, 1024, TEXT("%s"), &strText[j+1] );
		
		((CStatic*)m_pControlMap[STATIC_ITEMNAME])->SetText(kName,DT_CENTER);
		((CStatic*)m_pControlMap[STATIC_ITEMNAME])->Refresh();
		((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->SetText(kType,DT_CENTER);
		((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->Refresh();


		SetEditText( EDIT_EXPLAIN, kExplain );

		ShowMyCharInfo(	pMarketManager->CurrentSelectedBuyItemUnique );

		if(pclClient->pclItemManager->GetItemGImageFileIndexAndFont( pMarketManager->CurrentSelectedBuyItemUnique, &m_siImageType, &m_siImageIndex ) )
		{
		}
		else
		{
			m_siImageIndex = -1;
			m_siImageType  = -1;
		}


		// �����۸� ��ǰ���� Ȯ���Ѵ�. 
		if(pclClient->pclItemManager->IsItemInfoAtb( pMarketManager->CurrentSelectedBuyItemUnique, ITEMINFOATB_ITEMMALL))
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( true );
		}
		else
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );
		}

	}

	if (bMakerSwitch == true)
	{
		bMakerSwitch = false;

		CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];
		int index = pList->GetSelectedIndex();

		if( index < 0 ) return;

		index = pMarketManager->m_siSelectedBuyIndex[ index ];
		if( index < 0 ) return;

		pMarketManager->m_siSelectedBuyList = index;

		cltItem clitem;
		clitem.Set(&pMarketManager->clResponseOrder[index].clItemData);

		// �ش� ������ ������ ǥ���Ѵ�. 
		cltItemManagerClient *pclItemMgr = ( cltItemManagerClient * )pclClient->pclItemManager;
		pclItemMgr->GetExplain(&clitem, strText, false );

		NTCHARString512	kTmp;
		NTCHARString512	kExplain;

		NTCHARString512	kName;
		NTCHARString512 kType;

		kTmp = strText;

		SI32 siFind1, siFind2;
		// ù���� ������ �̸����� ��������
		siFind1 = kTmp.Find("\r");
		kName = kTmp.SubStr(0, siFind1);
		// ��°���� ������ Ÿ��
		siFind2 = kTmp.Find("\r", siFind1 + 1);
		kType = kTmp.SubStr(siFind1 + 2, siFind2 - siFind1 - 1);

		kExplain = kTmp.SubStr(siFind2 + 1);

//		StringCchPrintf( tmp, 1024, TEXT("%s"), &strText[j+1] );

		((CStatic*)m_pControlMap[STATIC_ITEMNAME])->SetText(kName,DT_CENTER);
		((CStatic*)m_pControlMap[STATIC_ITEMNAME])->Refresh();
		((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->SetText(kType,DT_CENTER);
		((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->Refresh();


		SetEditText( EDIT_EXPLAIN, kExplain );


		if(pclClient->pclItemManager->GetItemGImageFileIndexAndFont( clitem.siUnique, &m_siImageType, &m_siImageIndex ) )
		{
		}
		else
		{
			m_siImageIndex = -1;
			m_siImageType  = -1;
		}


		// �����۸� ��ǰ���� Ȯ���Ѵ�. 
		if(pclClient->pclItemManager->IsItemInfoAtb( pMarketManager->CurrentSelectedBuyItemUnique, ITEMINFOATB_ITEMMALL))
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( true );
		}
		else
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );
		}
	}
*/
//-----------------------------------------------------------------
}

void NMarketUserBuyDlg::ShowPrice()
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	if( pMarketManager->CurrentSelectedBuyItemUnique == 0)return;

	TCHAR buffer[256];

	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(pMarketManager->CurrentSelectedBuyItemUnique);
	if(pclprice)
	{
		TCHAR pricestring[128] = TEXT("") ;
		TCHAR* pText = GetTxtFromMgr(611);
		g_JYLibFunction.SetNumUnit(pclprice->siPrice, pricestring, 128, pText);
		StringCchPrintf(buffer, 256, TEXT("%s"),pricestring);

		SetEditText( EDIT_ITEMPRICE, buffer, ((cltClient*)pclClient)->GetColorByPrice(pclprice->siPrice) );

	}
}


BOOL NMarketUserBuyDlg::ShowResponseOrder()
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	// �ֹ� ����Ʈ 
	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];
	stListBoxItemData itemdata;


	if( bRequest ) {
		if( GetTickCount() - dwRequestTick >= 5000 ) {
			bRequest = FALSE;

			itemdata.Init();
			TCHAR* pText = GetTxtFromMgr(3456);

			itemdata.Set( 0, pText);


			pList->Clear();
			pList->AddItem( &itemdata );
			pList->Refresh();		

			// itemmall�� ��� ǥ��
			if(pclClient->pclItemManager->IsItemInfoAtb( pMarketManager->CurrentSelectedBuyItemUnique, ITEMINFOATB_ITEMMALL))
			{
				m_pControlMap[ BUTTON_ITEMMALL ]->Show( true );
			}
			else
			{
				m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );
			}

			//m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );
		}
	}

	SI32 i;

	if( pMarketManager->bResponseEmptyOrder == TRUE )
	{
		pMarketManager->ShowResponseOrderSiwtch = FALSE;
		pMarketManager->bResponseEmptyOrder = FALSE;
		bRequest = FALSE;

		itemdata.Init();
		TCHAR* pText = GetTxtFromMgr(3456);
		itemdata.Set( 0, pText);

		pList->Clear();
		pList->AddItem( &itemdata );
		pList->Refresh();		

		if(pclClient->pclItemManager->IsItemInfoAtb( pMarketManager->CurrentSelectedBuyItemUnique, ITEMINFOATB_ITEMMALL))
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( true );
		}
		else
		{
			m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );
		}

		//m_pControlMap[ BUTTON_ITEMMALL ]->Show( false );

		return FALSE;
	}

	if( pMarketManager->ShowResponseOrderSiwtch == TRUE)
	{
		pMarketManager->ShowResponseOrderSiwtch = FALSE;
		bRequest = FALSE;
	}
	else 
	{
		return FALSE;
	}

	// ������ ����Ʈ�� �����Ѵ�. 
	pList->Clear();

	bool bcheck[ MAX_RESPONSE_ORDER_NUMBER ];
	for(i = 0;i < MAX_RESPONSE_ORDER_NUMBER; i++ )
	{
		bcheck[i] = false;
	}

	SI32 addnum = 0 ;
	while( addnum < pMarketManager->siResponseOrderIndex )
	{
		GMONEY minprice	= 2100000000;
		SI32 minindex	= -1;

		for(i = 0;i < pMarketManager->siResponseOrderIndex;i++)
		{
			if( bcheck[i] == false && pMarketManager->clResponseOrder[i].siPrice <= minprice)
			{
				minprice = pMarketManager->clResponseOrder[i].siPrice;
				minindex = i;
			}
		}

		if(minindex >= 0)
		{
			bcheck[minindex] = true;

			cltItem clitem;
			clitem.Set(&pMarketManager->clResponseOrder[minindex].clItemData);

			TCHAR itemname[128] = TEXT("") ;

			if( clitem.GetFullName(pclClient->pclItemManager, itemname, 128) == true)
			{
				TCHAR pricestring[128] = TEXT("") ;
				TCHAR amount[128] = TEXT("") ;
				TCHAR* pText = GetTxtFromMgr(611);

				g_JYLibFunction.SetNumUnit(pMarketManager->clResponseOrder[minindex].siPrice, pricestring, 128, pText);
				StringCchPrintf(amount, 128, TEXT("%d"),pMarketManager->clResponseOrder[minindex].siAmount);

				itemdata.Init();
				itemdata.Set( 0, itemname );
				itemdata.Set( 1, pricestring, ((cltClient*)pclClient)->GetColorByPrice(pMarketManager->clResponseOrder[minindex].siPrice) );
				itemdata.Set( 2, amount );

				pList->AddItem( &itemdata );

				pMarketManager->m_siSelectedBuyIndex[addnum] = minindex ;
				addnum++;
			}
		}
	}

	pList->Refresh();

	pMarketManager->m_siSelectedBuyList = -1;

	return TRUE;

}

void NMarketUserBuyDlg::RefreshOrder()
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	CComboBox *pCombo = (CComboBox *)m_pControlMap[ COMBO_ITEM ];

	int index = pCombo->GetSelectedIndex();

	if( index < 0 ) return;

	SI32 itemunique = pclClient->pclItemManager->FindUniqueFromName( pCombo->GetText( index ) );

	if(itemunique)
	{
		// ���Ÿ� �������� ������ �������� �����Ѵ�. 
		pMarketManager->CurrentSelectedBuyItemUnique = itemunique;

		bSelectedSwitch = true;		
	}

	ShowRequestMsg();
	/*
	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];

	pList->Clear();
	pList->Refresh();
	*/
}

BOOL NMarketUserBuyDlg::ShowItemListInCombo( CComboBox *pCombo, SI32 itemtypeunique, bool btradeinterface )
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

void NMarketUserBuyDlg::RequestMarketOrderList( SI32 itemunique )
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	// �ֹ� ����Ʈ 
	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];

	if(itemunique <= 0)return ;

	SI32 id = 1;
	if(id == 0)return;

	// ������ ����Ʈ�� �����Ѵ�. 
	pList->Clear();
	pList->Refresh();
	pMarketManager->siResponseOrderIndex = 0;

	// ���� ������ Ȯ���Ѵ�. 
	SI32 pricecond	= 0;

	CCheckBox *pCheckBox = (CCheckBox *)m_pControlMap[ CHECK_PRICECOND ];

	if( pCheckBox->IsCheck() )
	{
		pricecond = _tstoi( GetEditText( EDIT_PRICECOND ) );
	}


	// ������ Ư�� ������(unique)�� �ֹ�����Ʈ�� ���� ���� �䱸�Ѵ�.
	cltGameMsgRequest_MarketOrder clinfo( itemunique, pricecond );
	cltMsg clMsg(GAMEMSG_REQUEST_MARKETORDER, sizeof(clinfo), (BYTE*)&clinfo);

	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void NMarketUserBuyDlg::ShowRequestMsg()
{
	// �ֹ� ����Ʈ 
	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];
	stListBoxItemData itemdata;

	itemdata.Init();
	TCHAR* pText = GetTxtFromMgr(5614);
	itemdata.Set( 0,pText);

	pList->Clear();
	pList->AddItem( &itemdata );
	pList->Refresh();
}


void NMarketUserBuyDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);
	cltClient *pclclient = (cltClient*)pclClient;

	CList *pList = (CList*)m_pControlMap[ LIST_ORDERLIST ];
//	stListBoxItemData *pitemdata;

	CComboBox *pComboItemType = (CComboBox *)m_pControlMap[ COMBO_ITEMTYPE ];
	CComboBox *pComboItem = (CComboBox *)m_pControlMap[ COMBO_ITEM ];

	CCheckBox *pCheckPrice = (CCheckBox *)m_pControlMap[ CHECK_PRICECOND ];

	CASE_CONTROL( LIST_ORDERLIST )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
			{

				TCHAR buf[ 1024 ];
				TCHAR tmpText[ 1024 ];
				memset(buf, 0 , sizeof(buf));
				memset(tmpText, 0, sizeof(tmpText));

				pMarketManager->m_siSelectedBuyList = -1;

				int index = pList->GetSelectedIndex();

				if( index < 0 ) return;

				index = pMarketManager->m_siSelectedBuyIndex[ index ];
				if( index < 0 ) return;

				pMarketManager->m_siSelectedBuyList = index;

				cltItem clitem;
				clitem.Set(&pMarketManager->clResponseOrder[index].clItemData);

				// �ش� ������ ������ ǥ���Ѵ�. 
				cltItemManagerClient *pclItemMgr = ( cltItemManagerClient * )pclClient->pclItemManager;
				pclItemMgr->GetExplain(&clitem, buf, true );

				NTCHARString512	kTmp;
				NTCHARString512	kExplain;

				NTCHARString512	kName;
				NTCHARString512 kType;

				kTmp = buf;

/*				TCHAR name [512];
				TCHAR type [512];
				TCHAR tmp [1024];
				memset(name, 0, sizeof(name));
				memset(type, 0, sizeof(type));
				memset(tmp, 0, sizeof(tmp));

				// ù���� ������ �̸����� ��������
				SI16 i = 0, j = 0;
				SI16 bufSize = (SI16)(_tcslen(buf));
 				for(  i = 0; i < bufSize;i++  )
				{
					if( buf[i] == TEXT('\0') )
					{
						break;
					}

					if( buf[i] == TEXT('\r') )
					{
						StringCchCopyN(name,512,buf,i);	
						break;				
					}
				}
				// ��°���� ������ Ÿ������ ��������
				for( j = i+1; j < bufSize;j++ )
				{
					if( buf[j] == TEXT('\0') )
					{
						break;
					}

					if( buf[j] == TEXT('\r') )
					{
						StringCchCopyN(type,512,&buf[i+2],j-i);
						break;
					}
				}*/

				SI32 siFind1, siFind2;
				// ù���� ������ �̸����� ��������
				siFind1 = kTmp.Find("\r");
				kName = kTmp.SubStr(0, siFind1);
				// ��°���� ������ Ÿ��
				siFind2 = kTmp.Find("\r", siFind1 + 1);
				kType = kTmp.SubStr(siFind1 + 2, siFind2 - siFind1 - 1);

				kExplain = kTmp.SubStr(siFind2 + 1);

// 				StringCchPrintf( tmp, 1024, TEXT("%s"), &buf[j+1] );


/*				((CStatic*)m_pControlMap[STATIC_ITEMNAME])->SetText(name,DT_CENTER);
				((CStatic*)m_pControlMap[STATIC_ITEMNAME])->Refresh();
				((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->SetText(type,DT_CENTER);
				((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->Refresh();


				SetEditText( EDIT_EXPLAIN, tmp );*/

				((CStatic*)m_pControlMap[STATIC_ITEMNAME])->SetText(kName,DT_CENTER);
				((CStatic*)m_pControlMap[STATIC_ITEMNAME])->Refresh();
				((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->SetText(kType,DT_CENTER);
				((CStatic*)m_pControlMap[STATIC_ITEMTYPE])->Refresh();


				SetEditText( EDIT_EXPLAIN, kExplain );

				CEdit *pEdit = (CEdit*)m_pControlMap[ EDIT_AMOUNT ];
				SI32 sivalue =_tstoi(pEdit->GetText());
				if(sivalue==0)
				{
					pEdit->SetText(TEXT("1"));
				}			

			}
			break;
		}
	}

	else CASE_CONTROL( CHECK_PRICECOND )
	{
		if( pCheckPrice->IsCheck() ) {

			m_pControlMap[ EDIT_PRICECOND ]->Show( true );
			m_pControlMap[ STATIC_PRICECOND ]->Show( true );
		} else {
			m_pControlMap[ EDIT_PRICECOND ]->Show( false );
			m_pControlMap[ STATIC_PRICECOND ]->Show( false );
		}
	}

	else CASE_CONTROL( COMBO_ITEMTYPE )
	{
		switch( nEvent )
		{
		case EVENT_COMBOBOX_SELECTION_CHANGED:
			{
				int index = pComboItemType->GetSelectedIndex();
				if( index < 0 ) return;

				TCHAR *szSelText = pComboItemType->GetText( index );

				SI32 itemtypeunique = pclClient->pclItemManager->FindItemTypeUniqueFromTypeName(szSelText);
				if(itemtypeunique >=0)
				{
					ShowItemListInCombo( pComboItem, itemtypeunique, false );
					pComboItem->SetCursel( 0 );
					RefreshOrder();
				}
			}
			break;
		}

	}

	else CASE_CONTROL( COMBO_ITEM )
	{
		switch( nEvent )
		{
		case EVENT_COMBOBOX_SELECTION_CHANGED:
			{
				RefreshOrder();
			}
			break;
		}
	}

	else CASE_CONTROL( BUTTON_REFRESH )
	{
		RefreshOrder();
	}

	else CASE_CONTROL( BUTTON_BUY )
	{
		SI32 id = 1;
		if(id == 0) return;

		//-----------------------------------
		// �������� ������ �ľ��Ѵ�. 
		//-----------------------------------
		if( pMarketManager->m_siSelectedBuyList < 0) return;

		cltTradeOrder* pclorder = &pMarketManager->clResponseOrder[pMarketManager->m_siSelectedBuyList];

		//-----------------------------------
		// �����ϰ��� �ϴ� ������ �ľ��Ѵ�.
		//-----------------------------------
		SI32 buynum = _tstoi( GetEditText( EDIT_AMOUNT ) );
		if(buynum <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1680);
			SetMainExplain(pText);
			return;
		}
		if(buynum > pclorder->siAmount)
		{
			buynum = pclorder->siAmount;
		}

		//-----------------------------------
		// �ֹ��� �ִ´�. 
		//-----------------------------------
		//PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
		cltTradeOrder clOrder;
		clOrder.Set(pclorder);
		clOrder.siAmount = buynum;	// ������  �����Ѵ�. 

		cltMsg clMsg(GAMEMSG_REQUEST_BUYITEM, sizeof(cltTradeOrder), (BYTE*)&clOrder);

		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//pMarketManager->m_siSelectedBuyList = -1;

	}

	else CASE_CONTROL( BUTTON_ITEMMALL )
	{
		if( pclClient->pclItemManager->IsItemInfoAtb(pMarketManager->CurrentSelectedBuyItemUnique, ITEMINFOATB_ITEMMALL))
		{
			//			pclClient->pclItemMallManager->CreateItemMallDlg(pclClient->GetHwnd(),pclClient->GetInstance(),
			//				0,pMarketManager->CurrentSelectedBuyItemUnique,true);
		}
	}
}

void NMarketUserBuyDlg::DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY )
{
	/*
	if(m_siImageIndex < 0)   
		return;
	cltClient *pclclient = ( cltClient * )pclClient;
	TSpr *pSpr = pclclient->pclGImg->GetGlobalSpr( m_siImageType );

	if ( pSpr )
	{
		GP.PutSpr(pSpr, ScreenRX + GetParentDialog()->GetX() +  GetX() + 290, ScreenRY + GetParentDialog()->GetY() + GetY() + 70, m_siImageIndex );
	}*/

}

void NMarketUserBuyDlg::VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY )
{
	if ( ! IsShow() )
		return;
	
	if(m_siImageIndex < 0)   
		return;

	cltClient *pclclient = ( cltClient * )pclClient;
	TSpr *pSpr = pclclient->pclGImg->GetGlobalSpr( m_siImageType );

	if ( pSpr )
	{

		GP.PutSpr( pSpr ,ScreenRX + GetParentDialog()->GetX() +  GetX() + 290,ScreenRY + GetParentDialog()->GetY() + GetY() + 70, m_siImageIndex);

	}
}

void NMarketUserBuyDlg::ShowMyCharInfo(SI32 itemunique)
{
	// �������� ���� ���ǰ� �ڽ��� �ɷ�ġ�� ���Ͽ� ǥ���� �ش�.

 	TCHAR strText[1024] = {'\0',};
	TCHAR strBuf[256] = {'\0',};
	
	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(itemunique);
	if(ref <= 0)return ;

	cltPersonInfo * pclCI =	pclClient->pclCM->CR[1]->pclCI;
	cltParametaBox * pclPB = &pclClient->pclCM->CR[1]->clPB;
	

	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel)
	{
		TCHAR*	pText = GetTxtFromMgr(649);

		// ���� ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����

		StringCchPrintf(strBuf, 256, pText, pclCI->clIP.GetLevel() );
		
		
		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel > pclCI->clIP.GetLevel())
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
 			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}

	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siStr)
	{
		TCHAR*	pText = GetTxtFromMgr(655);

		// �� ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����
		StringCchPrintf(strBuf,256,pText, pclPB->clTotalBA.GetStr() );


		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siStr > pclPB->clTotalBA.GetStr() )
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}

	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siDex)
	{
		TCHAR*	pText = GetTxtFromMgr(6301);

		// ��ø ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����
		StringCchPrintf(strBuf,256,pText, pclPB->clTotalBA.GetDex() );


		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siDex > pclPB->clTotalBA.GetDex())
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}
	
	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siMag )
	{
		TCHAR*	pText = GetTxtFromMgr(653);

		// ���� ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����
		StringCchPrintf(strBuf,256,pText, pclPB->clTotalBA.GetMag());


		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siMag > pclPB->clTotalBA.GetMag() )
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}

	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siVit )
	{
		TCHAR*	pText = GetTxtFromMgr(6302);

		// ü�� ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����
		StringCchPrintf(strBuf,256,pText, pclPB->clTotalBA.GetVit() );


		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel > pclPB->clTotalBA.GetVit() )
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}

	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siHnd )
	{
		SI32	siHndOrLuk	= 0;
		TCHAR*	pText		= NULL;

		if ( pclClient->IsCountrySwitch(Switch_ManufactureInfluenceLuck) )
		{
			siHndOrLuk	= pclPB->clTotalBA.GetLuk();
			pText		= GetTxtFromMgr(6065);
		}
		else
		{
			siHndOrLuk	= pclPB->clTotalBA.GetHnd();
			pText		= GetTxtFromMgr(6303);
		}

		// ������ ���� ���ǿ� ���� �ʴ´ٸ� ���� ���ڵ带 ����
		StringCchPrintf( strBuf, 256, pText, siHndOrLuk );


		if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siHnd > siHndOrLuk )
		{
			//StringCchPrintf( strBuf,256,TEXT("<C08>%s</C>\r"),pText );
			StringCchCat(strText,1024,TEXT("<C08>"));
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("</C>\r\n"));
		}
		else
		{
			StringCchCat(strText,1024,strBuf);
			StringCchCat(strText,1024,TEXT("\r\n"));
		}
	}

	// ��ų ���ǿ� ���� ��ų���� ǥ��
	
	SI32 skill = 0;
	
	switch(pclClient->pclItemManager->pclItemInfo[ref]->siType)
	{
		case ITEMTYPE_BOW:	skill = SKILL_USEBOW1;		break;
		case ITEMTYPE_GUN:	skill = SKILL_USEGUN1;		break;
		case ITEMTYPE_AXE:	skill = SKILL_USEAXE1;		break;
		case ITEMTYPE_STAFF:skill = SKILL_USESTAFF1;	break;
		case ITEMTYPE_SPEAR:skill = SKILL_USESPEAR1;	break;
		case ITEMTYPE_SWORD:skill = SKILL_USESWORD1;	break;		
	}

	if( skill )
	{
		TCHAR SkillName[256] = {'\0',};
		if(pclClient->pclSkillManager->GetSkillName( skill, SkillName ) ==  false)return;
		
		if(skill == pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siSkillKind)
		{
			SI32 totalskilllevel = pclCI->clCharSkill.GetTotalSkillLevel(skill,0,0,&pclCI->clCharItem.clItem[0]); 

			// ��ų ����
			if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siSkillPoint > totalskilllevel)
			{
				StringCchPrintf(strBuf, 256,TEXT("<C08>%s: %d</C>\r\n") , SkillName, totalskilllevel );
			}
			else
			{
				StringCchPrintf(strBuf, 256,TEXT("%s: %d\r\n") , SkillName, totalskilllevel );
			}
		}

		StringCchCat( strText , 1024, strBuf );
	}
    

	// �����, ����� üũ
	
 	if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST | CANUSEITEM_TYPE_WEST ) )
	{
		TCHAR *  pText = GetTxtFromMgr(6304);
		
		if(pclClient->pclCM->CR[1]->GetKind() == KIND_HERO3 
			|| pclClient->pclCM->CR[1]->GetKind() == KIND_HEROINE3)
		{
			TCHAR * pText = GetTxtFromMgr(6304);

			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_WEST)  )
			{
				StringCchPrintf( strBuf , 256, TEXT("<C08>%s</C>\r\n"), pText );
			}
			else
			{
				StringCchPrintf( strBuf , 256, TEXT("%s\r\n"), pText );
			}

			StringCchCat(strText, 1024,strBuf );

		}		
		else if(pclClient->pclCM->CR[1]->GetKind() == KIND_HERO4 
			|| pclClient->pclCM->CR[1]->GetKind() == KIND_HEROINE4)
		{
			TCHAR *  pText = GetTxtFromMgr(6305);
			if(pclClient->pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(CANUSEITEM_TYPE_EAST)  )
			{
				StringCchPrintf( strBuf , 256, TEXT("<C08>%s</C>\r\n"), pText );
			}
			else
			{
				StringCchPrintf( strBuf , 256, TEXT("%s\r\n"), pText );
			}

			StringCchCat(strText, 1024,strBuf );
		}

	}


	
	
	// ��, �� üũ

	((CEdit*)m_pControlMap[EDIT_EXPLAINCHAR])->SetText(strText);

	/*
	if(pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLuk )
	{


	}*/




}

