#include "NStockDlg.h"

#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/InterfaceMgr.h"


#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType-Stock.h"
#include "../../CommonLogic/MsgType-Structure.h"

#include "../Lib/JYLibFunction.h"

#include "../CommonLogic/Bank/Bank-Manager.h"

#include <tchar.h>

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;


NStockUserDlg::NStockUserDlg()
{

}

NStockUserDlg::~NStockUserDlg()
{

}

void NStockUserDlg::InitDlg()
{
	SetControlMap( BUTTON_BUY, TEXT("button_buy") );
	SetControlMap( BUTTON_SELL, TEXT("button_sell") );
	SetControlMap( BUTTON_CANCEL_ORDER, TEXT("button_cancel_order") );

	//SetControlMap( COMBO_BUY_KIND, TEXT("combobox_buy_kind") );
	SetControlMap( COMBO_SELL_KIND, TEXT("combobox_sell_kind") );

	//SetControlMap( EDIT_BUY_AMOUNT, TEXT("editbox_buy_amount") );
	//SetControlMap( EDIT_BUY_PRICE, TEXT("editbox_buy_price") );
	SetControlMap( EDIT_SELL_AMOUNT, TEXT("editbox_sell_amount") );
	SetControlMap( EDIT_SELL_PRICE, TEXT("editbox_sell_price") );

	SetControlMap( EDIT_FEERATE, TEXT("editbox_feerate") );

	SetControlMap( LIST_HAVESTOCK, TEXT("listbox_havestock") );
	SetControlMap( LIST_ORDERSTOCK, TEXT("listbox_orderstock") );
	SetControlMap( LIST_MOST_ORDER_SELL, TEXT("listbox_most_order_sell") );
	SetControlMap( LIST_MOST_ORDER_BUY, TEXT("listbox_most_order_buy") );
	
	SetControlMap( EDIT_AVERAGE_BUY, TEXT("editbox_average_Buy") );
	SetControlMap( EDIT_AVERAGE_SELL, TEXT("editbox_average_Sell") );

	//[�迵�� �߰�:2007.11.21 - �ֽĽ��忡�� ������ ���ݿ� ���� �̿ܿ� ���� �Է� ���ϵ��� ����]
	((CEdit*)m_pControlMap[ EDIT_SELL_AMOUNT ])->SetNumberMode(true);
	//((CEdit*)m_pControlMap[ EDIT_SELL_PRICE ])->SetNumberMode(true);

	CList *pList;
	
	// ���� �ֽ� ��Ȳ
	pList = (CList *)m_pControlMap[ LIST_HAVESTOCK ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	TCHAR* pText = GetTxtFromMgr(3452);
	pList->SetColumn( 0, pList->GetWidth(), pText);
	pList->Refresh();

	// �� �ֹ� ���� 
	pList = (CList *)m_pControlMap[ LIST_ORDERSTOCK ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	pText = GetTxtFromMgr(3453);
	pList->SetColumn( 0, pList->GetWidth(), pText );
	pList->Refresh();

	// ���� �ֹ�
	pList = (CList *)m_pControlMap[ LIST_MOST_ORDER_SELL ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	pText = GetTxtFromMgr(6723);
	pList->SetColumn( 0, pList->GetWidth(), pText );
	pList->Refresh();


	pList = (CList *)m_pControlMap[ LIST_MOST_ORDER_BUY ];

	pList->SetBorder(true);
	pList->SetBKColorUse(true);

	pText = GetTxtFromMgr(6724);
	pList->SetColumn( 0, pList->GetWidth(), pText );
	pList->Refresh();

	// By LEEKH - 2007.10.17 - �Է�����
	CEdit* pEdit_Sell_Amount = (CEdit*)m_pControlMap[ EDIT_SELL_AMOUNT ];
	pEdit_Sell_Amount->SetMaxEditTextLength( 5 );

	//// By LEEKH - 2007.10.17 - �Է�����
	//CEdit* pEdit_Sell_Price = (CEdit*)m_pControlMap[ EDIT_SELL_PRICE ];
	//pEdit_Sell_Price->SetMaxEditTextLength( 11 );

	cltStockManager *pStockManager = ((cltStockManager *)m_pStrManager);
		
	//pStockManager->clMostOrder.Init();

	memset( &pStockManager->clSellMostOrder[0], 0, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
	memset( &pStockManager->clBuyMostOrder[0], 0, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );

	pStockManager->siAverageSellMoney = 0;
	pStockManager->siAverageBuyMoney = 0;

	pStockManager->clOldStockInfo.Init();
	
	// ���� �ֽ��� ����Ʈ �ڽ��� �߰��Ѵ�. 
	SetHaveStock();

	// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
	SetStockOrderList();

	// �ż� ������ �޺��ڽ��� �߰��Ѵ�. 
//	SetComboBuyKind();

	// �ŵ� ������ �޺��ڽ��� �߰��Ѵ�.
	SetComboSellKind();

}

void NStockUserDlg::Action()
{
	if( m_pBaseDlg->m_dwActionCount % 3 ) return;

	TCHAR buffer[ 256 ];

	// ���� �ֽ��� ����Ʈ �ڽ��� �߰��Ѵ�. 
	SetHaveStock();

	// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
	SetStockOrderList();

	// ������ ������ �����ش�
	ShowFeeInfo();

	// ���� �ֹ� ������ �����ش�. 
	cltStockManager *pStockManager = ((cltStockManager *)m_pStrManager);

	CList *pSellList, *pBuyList;
	pSellList = (CList *)m_pControlMap[ LIST_MOST_ORDER_SELL ];
	pBuyList = (CList *)m_pControlMap[ LIST_MOST_ORDER_BUY ];

	pSellList->Clear();
	pBuyList->Clear();

	stListBoxItemData itemdata;

	TCHAR temp[256];

	TCHAR* name  = NULL;
	TCHAR* pText = GetTxtFromMgr(1486);
	/*
	
	StringCchPrintf(temp, 256, pText);

	itemdata.Init();
	itemdata.Set( 0, temp );
	pSellList->AddItem( &itemdata );

	pText = GetTxtFromMgr(1487);
	StringCchPrintf(temp, 256, pText);

	itemdata.Init();
	itemdata.Set( 0, temp );
	pBuyList->AddItem( &itemdata );
*/
	TCHAR* pTextMoney = GetTxtFromMgr(611); //�� ������ �������� ����.

	StringCchPrintf(temp,256,TEXT("%I64d%s"),pStockManager->siAverageSellMoney, pTextMoney);
	((CEdit *)m_pControlMap[ EDIT_AVERAGE_SELL ])->SetText(temp);
	
	StringCchPrintf(temp,256,TEXT("%I64d%s"),pStockManager->siAverageBuyMoney, pTextMoney);
	((CEdit *)m_pControlMap[ EDIT_AVERAGE_BUY ])->SetText(temp);

	pText = GetTxtFromMgr(1488);

	for( SI32 i = 0; i < MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM ; i ++ )
	{
		name = pclClient->pclVillageManager->GetName( pStockManager->clSellMostOrder[i].siVillageUnique );
		if( name )
		{
			StringCchPrintf(buffer, 256, pText, 
							TEXT(""), 
							name, 
							pStockManager->clSellMostOrder[i].siPrice, 
							pStockManager->clSellMostOrder[i].siAmount);

			itemdata.Init();
			itemdata.Set( 0, buffer );
			pSellList->AddItem( &itemdata );
		}

		name = pclClient->pclVillageManager->GetName( pStockManager->clBuyMostOrder[i].siVillageUnique );
		if( name )
		{
			StringCchPrintf(buffer, 256, pText, 
							TEXT(""), 
							name, 
							pStockManager->clBuyMostOrder[i].siPrice, 
							pStockManager->clBuyMostOrder[i].siAmount);

			itemdata.Init();
			itemdata.Set( 0, buffer );
			pBuyList->AddItem( &itemdata );
		}
	}

	pBuyList->Refresh();
	pSellList->Refresh();	

}

void NStockUserDlg::ShowFeeInfo()
{
	TCHAR buffer[256];

	REAL64 feerate = (REAL64)m_pStrManager->clClientStrInfo.clStockStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf( buffer, 256, TEXT("%3.1f%%"), feerate);

	SetEditText( EDIT_FEERATE, buffer );
}


// ���� �ֽ��� ǥ���Ѵ�. 
void NStockUserDlg::SetHaveStock()
{
	cltStockManager *pStockManager = ((cltStockManager *)m_pStrManager);
	CList *pList;
	
	// ���� �ֽ� ��Ȳ
	pList = (CList *)m_pControlMap[ LIST_HAVESTOCK ];

	SI32 i;
	TCHAR buffer[256];

	SI32 id = 1;
	if(id==0)return ;

	// ������ ���ŵ� ���¿����� ������Ʈ �Ѵ�. 
	if( pclCM->CR[id]->pclCI->clStock.clInfo.IsSame(&pStockManager->clOldStockInfo) == true)return ;
	pStockManager->clOldStockInfo.Set(&pclCM->CR[id]->pclCI->clStock.clInfo);


	// ����Ʈ �ڽ��� �ʱ�ȭ�Ѵ�. 
	pList->Clear();

	stListBoxItemData itemdata;

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		SI32 villageunique	= pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siVillageUnique;
		SI32 amount			= pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siAmount;
	
		if(villageunique)
		{
			if(villageunique >=0)
			{
				TCHAR* pText = GetTxtFromMgr(1500);
				StringCchPrintf(buffer, 256, pText, pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName, amount);
				itemdata.Init();
				itemdata.Set( 0, buffer );
				pList->AddItem( &itemdata );
			}
			else
			{
				MsgBox(TEXT("fds09f82j"), TEXT("fdo9873:%d"), villageunique);
			}
		}
	}

	NListSort( pList );

	//<= pList->Refresh();
}

// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
void NStockUserDlg::SetStockOrderList()
{
	cltStockManager *pStockManager = ((cltStockManager *)m_pStrManager);
	CList *pList;

	// �� �ֹ� ���� 
	pList = (CList *)m_pControlMap[ LIST_ORDERSTOCK ];

	SI32 i;

	// ����Ʈ �ڽ��� �ʱ�ȭ�Ѵ�. 
	pList->Clear();

	SI32 id = 1;
	if(id <= 0)return ;

	stListBoxItemData itemdata;

	for(i = 0;i < MAX_ORDER_PER_PERSON;i++)
	{
		cltTradeOrder* pclStockOrder = &pclCM->CR[id]->pclCI->clStock.clOrderInfo.clOrderUnit[i].clOrder;
		SI32 villageunique	= pclStockOrder->GetVillageUnique();
		SI32 amount			= pclStockOrder->siAmount;
		GMONEY price			= pclStockOrder->siPrice;
		SI32 ordermode		= pclCM->CR[id]->pclCI->clStock.clOrderInfo.clOrderUnit[i].siOrderMode;

	
		if(villageunique)
		{
			if(villageunique >=0)
			{
				NTCHARString128 strMessage( TEXT("") );
				
				if(ordermode == ORDERMODE_SELL)
				{
					strMessage = GetTxtFromMgr(1501);
				}
				else
				{
					strMessage = GetTxtFromMgr(1502);
				}

				TCHAR szMoney[128]= { '\0', };
				g_JYLibFunction.SetNumUnit( price, szMoney, sizeof(szMoney) );

				strMessage.Replace( TEXT("#village#"), pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName );
				strMessage.Replace( TEXT("#amount#"), SI32ToString(amount) );
				strMessage.Replace( TEXT("#money#"), szMoney );

				
				itemdata.Init();
				itemdata.Set( 0, strMessage );
				pList->AddItem( &itemdata );
			}
			else
			{
				MsgBox(TEXT("fds2309f82j"), TEXT("fdfdo9873:%d"), villageunique);
			}
		}
	}

	NListSort( pList );

	//<= pList->Refresh();

}


// �ŵ� ������ �޺� �ڽ��� �߰��Ѵ�. 
void NStockUserDlg::SetComboSellKind()
{

	CComboBox *pCombo;
	pCombo = (CComboBox *)m_pControlMap[ COMBO_SELL_KIND ];	
	
	stComboBoxItemData itemdata;
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		// [����] �ʺ��� ���� : �ʺ��� ���� �ֽ��� �ֽ� �ŷ� ����Ʈ�� �ȳ�Ÿ���� �Ѵ�
		if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
		{
			if ( Const_Beginner_Village == i )
			{
				continue;
			}
		}

		if(pclClient->pclVillageManager->pclVillageInfo[i])
		{
			itemdata.Init();
			itemdata.Set( pclClient->pclVillageManager->pclVillageInfo[i]->szName );			
			pCombo->AddItem( &itemdata );
		}
	}

	NComboBoxSort( pCombo );
}


void NStockUserDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	TCHAR buffer[ 512 ];
	cltClient* pclclient = (cltClient*)pclClient;

	CComboBox *pComboBuyKind = (CComboBox *)m_pControlMap[ COMBO_SELL_KIND ];
	CComboBox *pComboSellKind = (CComboBox *)m_pControlMap[ COMBO_SELL_KIND ];

	
	CASE_CONTROL( EDIT_SELL_PRICE )
	{
		switch(nEvent) {
		case EVENT_EDITBOX_CHANGE :
			NTCHARString512	kRawPrice( GetEditText( EDIT_SELL_PRICE ));
			kRawPrice.ReplaceAll(",", "");	// , ����
			TCHAR		szPrice[64] = { '\0', };
			GMONEY		siPrice = _tstoi64(kRawPrice);
			if( siPrice > pclClient->GetGlobalValue("GV_StockTradeMoneyLimit"))
				siPrice = pclClient->GetGlobalValue("GV_StockTradeMoneyLimit");
			
			TCHAR buf[128] = "";
			g_JYLibFunction.SetNumUnit( siPrice, buf, sizeof(buf) );
			SetEditText( EDIT_SELL_PRICE, buf ); 
		}
	}

	CASE_CONTROL( COMBO_BUY_KIND )
	{
		
		switch( nEvent )
		{
		case EVENT_COMBOBOX_SELECTION_CHANGED:
			{
				// ����� ��ȿ�� �˻�. 
				SI32 id = 1;
				if(id <= 0)break;

				// ������ ������ �̸��� Ȯ���Ѵ�. 
				TCHAR *szSelText = pComboBuyKind->GetText( pComboBuyKind->GetSelectedIndex() );

				// ������ ����ũ�� Ȯ���Ѵ�. 
				SI32 villageunique = pclClient->pclVillageManager->FindVillageUniqueFromName(szSelText);
				if(villageunique <= 0)break;
					
				// ���Ӽ����� �������� �ֹ��� �Ƿ��Ѵ�. 
				cltGameMsgRequest_StockOrderInfo clInfo(villageunique);
				cltMsg clMsg(GAMEMSG_REQUEST_STOCKORDERINFO, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
			break;
		}
	}

	else CASE_CONTROL( COMBO_SELL_KIND )
	{
		switch( nEvent )
		{
		case EVENT_COMBOBOX_SELECTION_CHANGED: 
			{
				// ����� ��ȿ�� �˻�. 
				SI32 id = 1;
				if(id <= 0)break;

				TCHAR *szSelText = pComboSellKind->GetText( pComboSellKind->GetSelectedIndex() );

				// ������ ����ũ�� Ȯ���Ѵ�. 
				SI32 villageunique = pclClient->pclVillageManager->FindVillageUniqueFromName(szSelText);
				if(villageunique <= 0)break;
					
				// ���Ӽ����� �ְ���� �ֹ��� �Ƿ��Ѵ�. 
				cltGameMsgRequest_StockOrderInfo clInfo(villageunique);
				cltMsg clMsg(GAMEMSG_REQUEST_STOCKORDERINFO, sizeof(clInfo), (BYTE*)&clInfo);
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
			break;
		}

	}

	else CASE_CONTROL( BUTTON_CANCEL_ORDER )
	{
		SI32 id = 1;
		if(id)
		{
			cltMsg clMsg(GAMEMSG_REQUEST_CANCELSTOCKORDER, 0, NULL);
			
			pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	else CASE_CONTROL( BUTTON_BUY )
	{
		SI32 id = 1;

		//-------------------------------------
		// ���ѵ� �ֹ� �Ǽ� �̻��� �� �� ����. 
		//-------------------------------------
		SI32 stockordernum = pclCM->CR[id]->GetStockOrderNumber();
		if(stockordernum >= MAX_ORDER_PER_PERSON)
		{
			TCHAR* pText = GetTxtFromMgr(1489);
			SetMainExplain(pText);
			return;
		}

		//------------------------------
		//	���忡 ���°� �ִ��� Ȯ���Ѵ�. 
		//------------------------------

		//���忡 ���°� ���ٸ� ���ٴ� �޼����� ����ϰ� 0���� ��� 0���̶�� �޼����� 
		//����Ѵ�.[���� 2007.06.26]

		
		BOOL bAccount = pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid();

		if (bAccount==FALSE) {
			TCHAR* pText = GetTxtFromMgr(1490);
			SetMainExplain(pText);
			return;
		}
		
		else if(pclCM->CR[id]->GetBankMoney() == 0)
		{
			TCHAR* pText = GetTxtFromMgr(7113);
			SetMainExplain(pText);
			return;
		}	

		//-----------------------------
		// ������ Ȯ���Ѵ�. (����ũ��) 
		//------------------------------
		TCHAR *pControlText;
		pControlText = pComboBuyKind->GetText( pComboBuyKind->GetSelectedIndex() );

		SI32 ref = pclClient->pclVillageManager->FindVillageUniqueFromName( pControlText );
		if(ref < 0)
		{
			TCHAR* pText = GetTxtFromMgr(1491);
			SetMainExplain(pText);
			return;
		}
		SI32 villageunique = pclClient->pclVillageManager->pclVillageInfo[ref]->siVillageUnique;

		//----------------------------
		// ������ Ȯ���Ѵ�. 
		//----------------------------
		pControlText = GetEditText( EDIT_SELL_AMOUNT );

		SI32 amount = _tstoi( pControlText );

		if(amount <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1492);
			SetMainExplain(pText);
			return;
		}
		if(amount > MAX_AMOUNT_PER_DEAL)
		{
			TCHAR* pText = GetTxtFromMgr(1493);
			StringCchPrintf(buffer, 512, pText, MAX_AMOUNT_PER_DEAL);
			SetMainExplain(buffer);
			return;
		}

		//---------------------------
		// �ܰ��� Ȯ���Ѵ�. 
		//---------------------------
		//pControlText = GetEditText( EDIT_SELL_PRICE );

		//// by LEEKH 2007.10.17 ���� ���õ� ��ġ�� ������ SI64�� ó���Ѵ�.
		////SI32 price = _tstoi( pControlText );
		//SI64 price = _tstoi64( pControlText );
		NTCHARString512	kRawPrice( GetEditText( EDIT_SELL_PRICE ));
		kRawPrice.ReplaceAll(",", "");	// , ����
		GMONEY		price = _tstoi64(kRawPrice);
		if( price > pclClient->GetGlobalValue("GV_StockTradeMoneyLimit"))
			price = pclClient->GetGlobalValue("GV_StockTradeMoneyLimit");

		if(price <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1494);
			SetMainExplain(pText);
			return;
		}

		//------------------------------------------
		// �հ� �ݾ��� �ܰ� ���� �ִ��� Ȯ���Ѵ�. 
		//------------------------------------------
		SI64 totalmoney = (SI64)price * (SI64)amount;

		/*if( price > 2100000000)
		{
			TCHAR* pText = GetTxtFromMgr(5484);
			StringCchPrintf(buffer, 512, pText);

			SetMainExplain(buffer);
			return;
		}*/

		GMONEY diff		= totalmoney - pclCM->CR[id]->GetBankMoney();

		if(diff > 0)
		{
			TCHAR* pText = GetTxtFromMgr(1495);
			StringCchPrintf(buffer, 512, pText, diff );

			SetMainExplain(buffer);
			return;
		}

		TCHAR		szPrice[64] = { '\0', };
		g_JYLibFunction.SetNumUnit(price, szPrice, sizeof(szPrice));

		TCHAR*			pTitle = GetTxtFromMgr(850);
		NTCHARString512 strText( GetTxtFromMgr(5399) );

		strText.Replace( TEXT("#village#"), pclClient->pclVillageManager->GetName(villageunique) );
		strText.Replace( TEXT("#amount#"), SI32ToString(amount) );
		strText.Replace( TEXT("#price#"), szPrice );


		stMsgBox MsgBox;
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent, pTitle, strText, MSGBOX_TYPE_YESNO, 0 );
		BYTE TempBuffer[ 512 ] = "";
		SI16 Size = sizeof( id ) + sizeof( price ) + sizeof(amount) + sizeof(villageunique) ;
		memcpy( TempBuffer, &id, sizeof( id ) );
		memcpy( &TempBuffer[ sizeof(id) ], &price, sizeof( price ) );
		memcpy( &TempBuffer[ sizeof( id ) + sizeof( price ) ], &amount, sizeof( amount ) );
		memcpy( &TempBuffer[ sizeof( id ) + sizeof( price ) + sizeof(amount)], &villageunique, sizeof( villageunique ) );
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );

		////---------------------------------------
		//// ������ �ֽ��� �ż��϶�� ��û�� �뺸�Ѵ�. 
		////---------------------------------------
		//if(id)
		//{
		//	// PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
		//	cltTradeOrder clStockOrder(0, price, amount, 0, villageunique);
		//	
		//	cltMsg clMsg(GAMEMSG_REQUEST_BUYSTOCK,  
		//		sizeof(cltTradeOrder), (TCHAR*)&clStockOrder);
		//	
		//	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//}


	}

	else CASE_CONTROL( BUTTON_SELL )
	{
		SI32 id = 1;
        BOOL bStockAccount = pclCM->CR[id]->pclCI->clStock.clInfo.HaveStock();
		//-------------------------------------
		// �ֽ��� ������ ���ٰ� �Ѵ�. [2007.08.10 �ռ���]
		//-------------------------------------
		if (bStockAccount==FALSE) {
			TCHAR* pText = GetTxtFromMgr(1497);
			SetMainExplain(pText);
			return;
		}
		//-------------------------------------
		// ���ѵ� �ֹ� �Ǽ� �̻��� �� �� ����. 
		//-------------------------------------
		SI32 stockordernum = pclCM->CR[id]->GetStockOrderNumber();
		if(stockordernum >= MAX_ORDER_PER_PERSON)
		{
			TCHAR* pText = GetTxtFromMgr(1496);
			SetMainExplain(pText);
			return;
		}

		//------------------------------
		//	���忡 ���°� �ִ��� Ȯ���Ѵ�. 
		//------------------------------
		BOOL bAccount = pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid();

		if (bAccount==FALSE) {
			TCHAR* pText = GetTxtFromMgr(1490);
			SetMainExplain(pText);
			return;
		}

		//if(pclCM->CR[id]->GetBankMoney() == 0)
		//{
		//	TCHAR* pText = GetTxtFromMgr(1490);
		//	SetMainExplain(pText);
		//	return;
		//}

		//-----------------------------
		// ������ Ȯ���Ѵ�. (����ũ��) 
		//------------------------------

		TCHAR *pControlText;
		pControlText = pComboSellKind->GetText( pComboSellKind->GetSelectedIndex() );
		
		SI32 ref = pclClient->pclVillageManager->FindVillageUniqueFromName( pControlText );
		if(ref < 0)
		{
			TCHAR* pText = GetTxtFromMgr(1491);
			SetMainExplain(pText);
			return;
		}
		SI32 villageunique = pclClient->pclVillageManager->pclVillageInfo[ref]->siVillageUnique;

		// �ش� villageunique�� �����ϰ� �ִ��� Ȯ���Ѵ�. 
		SI32 maxsellamount = pclCM->CR[id]->pclCI->clStock.clInfo.GetStockAmount(villageunique);
		if(maxsellamount == 0)
		{
			TCHAR* pText = GetTxtFromMgr(1497);
			SetMainExplain(pText);
			return;
		}

		//----------------------------
		// ������ Ȯ���Ѵ�. 
		//----------------------------
		pControlText = GetEditText( EDIT_SELL_AMOUNT );		
		SI32 amount = _tstoi( pControlText );

		if(amount <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1492);
			SetMainExplain(pText);
			return;
		}
		else if(amount > maxsellamount)
		{
			TCHAR* pText = GetTxtFromMgr(1498);
			SetMainExplain(pText);
			return;
		}
		else if(amount > MAX_AMOUNT_PER_DEAL)
		{
			TCHAR* pText = GetTxtFromMgr(1493);
			StringCchPrintf(buffer, 512, pText, MAX_AMOUNT_PER_DEAL);
			SetMainExplain(buffer);
			return;
		}

		//---------------------------
		// �ܰ��� Ȯ���Ѵ�. 
		//---------------------------
		NTCHARString512	kRawPrice( GetEditText( EDIT_SELL_PRICE ));
		kRawPrice.ReplaceAll(",", "");	// , ����
		TCHAR		szPrice[64] = { '\0', };
		GMONEY		siPrice = _tstoi64(kRawPrice);
		if( siPrice > pclClient->GetGlobalValue("GV_StockTradeMoneyLimit"))
			siPrice = pclClient->GetGlobalValue("GV_StockTradeMoneyLimit");

		//pControlText = GetEditText( EDIT_SELL_PRICE );		
		//SI64 price = _tstoi64(pControlText);
		if(siPrice <= 0)
		{
			TCHAR* pText = GetTxtFromMgr(1494);
			SetMainExplain(pText);
			return;
		}

		//TCHAR		szPrice[64] = { '\0', };
		g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));

		TCHAR*			pTitle = GetTxtFromMgr(5401);
		NTCHARString512 strText( GetTxtFromMgr(5400) );

		strText.Replace( TEXT("#village#"), pclClient->pclVillageManager->GetName(villageunique) );
		strText.Replace( TEXT("#amount#"), SI32ToString(amount) );
		strText.Replace( TEXT("#price#"), szPrice );

		
		stMsgBox MsgBox;
		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return;
		MsgBox.Set( pParent, pTitle, strText, MSGBOX_TYPE_YESNO, 1 );
		BYTE TempBuffer[ 512 ];
		SI16 Size = sizeof( id ) + sizeof( siPrice ) + sizeof(amount) + sizeof(villageunique) ;
		memcpy( TempBuffer, &id, sizeof( id ) );
		memcpy( &TempBuffer[ sizeof(id) ], &siPrice, sizeof( siPrice ) );
		memcpy( &TempBuffer[ sizeof( id ) + sizeof( siPrice ) ], &amount, sizeof( amount ) );
		memcpy( &TempBuffer[ sizeof( id ) + sizeof( siPrice ) + sizeof(amount)], &villageunique, sizeof( villageunique ) );
		pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );


		////---------------------------------------
		//// ������ �ֽ��� �ŵ��϶�� ��û�� �뺸�Ѵ�. 
		////---------------------------------------
		//if(id)
		//{
		//	// PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
		//	cltTradeOrder clStockOrder(0, price, amount, 0, villageunique);
		//	
		//	cltMsg clMsg(GAMEMSG_REQUEST_SELLSTOCK, 
		//		sizeof(cltTradeOrder), (TCHAR*)&clStockOrder);
		//	
		//	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//}

	}

}

void NStockUserDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	switch( MsgIndex )
	{
	case 0: // �ֽ� ���
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 siPos			= 0;
				SI32 id				= *((SI32*)(pData + siPos));	siPos += sizeof(id);
				SI64 price			= *((SI64*)(pData + siPos));	siPos += sizeof(price);
				SI32 amount			= *((SI32*)(pData + siPos));	siPos += sizeof(amount);
				SI32 villageunique	= *((SI32*)(pData + siPos));	siPos += sizeof(villageunique);

				//---------------------------------------
				// ������ �ֽ��� �ż��϶�� ��û�� �뺸�Ѵ�. 
				//---------------------------------------
				if(id)
				{
					// PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
					cltTradeOrder clStockOrder(0, price, amount, 0, villageunique);
					
					cltMsg clMsg(GAMEMSG_REQUEST_BUYSTOCK,  
						sizeof(cltTradeOrder), (BYTE*)&clStockOrder);
					
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				}

			}
		}
		break;
	case 1:	// �ֽ� �ȱ�
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 siPos			= 0;
				SI32 id				= *((SI32*)(pData + siPos));	siPos += sizeof(id);
				SI64 price			= *((SI64*)(pData + siPos));	siPos += sizeof(price);
				SI32 amount			= *((SI32*)(pData + siPos));	siPos += sizeof(amount);
				SI32 villageunique	= *((SI32*)(pData + siPos));	siPos += sizeof(villageunique);

				//---------------------------------------
				// ������ �ֽ��� �ŵ��϶�� ��û�� �뺸�Ѵ�. 
				//---------------------------------------
				if(id)
				{
					// PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
					cltTradeOrder clStockOrder(0, price, amount, 0, villageunique);
					
					cltMsg clMsg(GAMEMSG_REQUEST_SELLSTOCK, sizeof(cltTradeOrder), (BYTE*)&clStockOrder);
					
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
		break;
	}
}
