#include "NMarketDlg.h"

#include "../../InterfaceMgr/Interface/ListView.h"
#include "../StrBaseDlg/StrInventory.h"

#include "Char\CharManager\CharManager.h"
#include "..\..\Server\Rank\Rank.h"

#include "../../CommonLogic/MsgType.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/MsgType-Bank.h"

#include "../Lib/JYLibFunction.h"
#include "..\..\Client\Music\Music.h"

#include "../../Client/InterfaceMgr/InterfaceMgr.h"

extern cltCommonLogic* pclClient;
extern CJYLibFunction g_JYLibFunction;

NMarketUserSellDlg::NMarketUserSellDlg()
{
	m_pMyInventory = new NStrInventory;
	m_pStgItem = new NStrInventory;
}

NMarketUserSellDlg::~NMarketUserSellDlg()
{
	NDelete( m_pMyInventory );
	NDelete( m_pStgItem );
}

void NMarketUserSellDlg::InitDlg()
{

	//SetControlMap( EDIT_BACKGROUND, TEXT("editbox_BackGround") );

 	SetControlMap( LISTVIEW_MYINVENTORY, TEXT("listview_myinventory") );
 	SetControlMap( LISTVIEW_MARKETSTORAGE, TEXT("listview_marketstorage") );

	SetControlMap( EDIT_AMOUNT, TEXT("editbox_amount") );
	SetControlMap( EDIT_PRICE, TEXT("editbox_price") );
	
	SetControlMap( EDIT_FEERATE, TEXT("editbox_feerate") );
	SetControlMap( EDIT_FEE, TEXT("editbox_fee") );

	SetControlMap( EDIT_MONEY_UNIT, TEXT("editbox_money_unit") );

	SetControlMap( BUTTON_SELL, TEXT("button_sell") );
	SetControlMap( BUTTON_CANCEL_ORDER, TEXT("button_cancel_order") );

	SetControlMap( EDIT_ITEMPRICE1, TEXT("editbox_NONAME1") );
	SetControlMap( EDIT_ITEMPRICE2, TEXT("editbox_NONAME2") );
	SetControlMap( EDIT_ITEMPRICE3, TEXT("editbox_NONAME3") );
	SetControlMap( EDIT_ITEMPRICE4, TEXT("editbox_NONAME4") );	

	SetControlMap( BUTTON_SEARCHPRICE, TEXT("button_SearchPrice") );

	SetControlMap( STATIC_TOTALNUM, TEXT("statictext_totalnum") );

	SetControlMap( STATIC_MONEYUNIT, TEXT("statictext_MoneyUnit") );
	
//	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 ])->SetTextPrintOption( DT_RIGHT | DT_VCENTER | DT_SINGLELINE );
//	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE2 ])->SetTextPrintOption( DT_RIGHT | DT_VCENTER | DT_SINGLELINE );
//	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE3 ])->SetTextPrintOption( DT_RIGHT | DT_VCENTER | DT_SINGLELINE );
//	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE4 ])->SetTextPrintOption( DT_RIGHT | DT_VCENTER | DT_SINGLELINE );

	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE2 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE3 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE4 ])->ShowScrollBar(false);

	((CEdit*)m_pControlMap[ EDIT_AMOUNT ])->SetNumberMode(true);
	//((CEdit*)m_pControlMap[ EDIT_PRICE ])->SetNumberMode(true);
	((CEdit*)m_pControlMap[ EDIT_PRICE ])->SetMaxEditTextLength(20);

	// MyInventory
	m_pMyInventory->CreateInventory( MAX_ITEM_PER_PERSON, (CListView*)m_pControlMap[ LISTVIEW_MYINVENTORY ] );

	m_pMyInventory->m_pListView->SetBKColorUse( true );
	m_pMyInventory->m_pListView->SetBorder( true );

 	m_pMyInventory->LoadMyInventory();

	// Stg Item
	m_pStgItem->CreateInventory(  MAX_MARKET_ORDER_PER_PERSON, (CListView*)m_pControlMap[ LISTVIEW_MARKETSTORAGE ],
								&pclCM->CR[1]->pclCI->clMarket.clInfo.clItem[0] );
	
	//m_pStgItem->m_pListView->SetBKColorUse( false );
	//m_pStgItem->m_pListView->SetBorder( true );

	m_pStgItem->LoadInventory( NULL, TRUE );
	// ���Ͽ� ��ϵ� �������� ������ ����Ʈ �ڽ��� ǥ������
	SetStgItemPrice(&pclCM->CR[1]->pclCI->clMarket.clInfo);


	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	// ����� �Ǵ� ĳ������ ���̵� ���Ѵ�. 
	SI32 id = 1;

	pMarketManager->clOldPersonItemInfo.Init();
	pMarketManager->clOldAccount.Init();

/*
	// ���� ��ư�� ��Ȱ��ȭ ��Ų��. (������) 
	EnableSellButton(hDlg, IDC_BUTTON_MARKETSELL, FALSE, TRUE);
	// ���� ȸ�� ��ư�� ��Ȱ��ȭ ��Ų��. (������) 
	EnableGetFromMarketButton(hDlg, IDC_BUTTON_GETFROMMARKETSTORAGE, FALSE, TRUE);
*/

	NTCHARString128	kText(GetTxtFromMgr(8783));
	if(m_pControlMap[ STATIC_MONEYUNIT ])
	{
		((CStatic*)m_pControlMap[ STATIC_MONEYUNIT ])->SetTextPrintOption(DT_TOP | DT_RIGHT);
		((CStatic*)m_pControlMap[ STATIC_MONEYUNIT ])->SetText(kText);
	}

	// ������ ������ ǥ���Ѵ�. 
	ShowFeeRate();

	m_bMyInven = FALSE;

}

void NMarketUserSellDlg::Action()
{
	TCHAR buffer[ 256 ];

	if( m_pMyInventory->IsMyInventoryChanged() ) {
		m_pMyInventory->LoadMyInventory();
	}

	if( m_pStgItem->IsInventoryChanged() ) {
		m_pStgItem->LoadInventory( NULL, TRUE );
		SetStgItemPrice(&pclCM->CR[1]->pclCI->clMarket.clInfo);
	}

	// ������ ������ ǥ���Ѵ�. 
	ShowFeeRate();

	// EDIT BOX ���� ������ ����
	MStrCpy( buffer, GetEditText( EDIT_AMOUNT ), 9 );
	int itemnum = _tstoi( buffer );
	
	// 2007.06.14 - �����
	// ������ǰ �Ǵ� �ȷ��� ������ ������ ������ ������ �ʰ��ؼ� �Է��ϸ� ������ ������ ������ ��ȯ�Ѵ�..

	if (m_bMyInven == TRUE)		// ������ǰ�� ������ ���
	{
		if (itemnum > m_pMyInventory->m_clSelectedItem.GetItemNum())
		{
			TCHAR buf[ 256 ];
			itemnum = m_pMyInventory->m_clSelectedItem.GetItemNum();
			StringCchPrintf( buf, 256, TEXT("%d"), itemnum );
			SetEditText( EDIT_AMOUNT, buf );
		}
	}
	else
	{
		if (itemnum > m_pStgItem->m_clSelectedItem.GetItemNum())
		{
			TCHAR buf[ 256 ];
			itemnum = m_pStgItem->m_clSelectedItem.GetItemNum();
			StringCchPrintf( buf, 256, TEXT("%d"), itemnum );
			SetEditText( EDIT_AMOUNT, buf );
		}
	}

	NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
	kRawPrice.ReplaceAll(",", "");	// , ����
//	MStrCpy( buffer, GetEditText( EDIT_PRICE ), 15 );
	SI64 price = _tstoi64( kRawPrice );

	if( m_bMyInven )
		ShowFee( itemnum, price );
	else 
		ShowFee( 0, 0 );
	

	TCHAR *pText = GetTxtFromMgr(611);
	

	//���� * ���� (���Ǹž�) ǥ��
	g_JYLibFunction.SetNumUnit( price * itemnum ,buffer, 256, pText); //[�����մ�]
		
	SetEditText( EDIT_MONEY_UNIT, buffer , ((cltClient*)pclClient)->GetColorByPrice(price*itemnum) );

/*
	// ���õ� �������� ������ �����۰� �ٸ��ٸ� ������ ����Ѵ�. 
	if(pclCurrentInvItem && pclCurrentInvItem->IsSame(&clCurrentInvItem, true) == FALSE)
	{
		pclCurrentInvItem  = NULL;
	}

	if(pclCurrentStgItem && pclCurrentStgItem->IsSame(&clCurrentStgItem, true) == FALSE)
	{
		pclCurrentStgItem  = NULL;
		CurrentStgItemIndex	= -1;
	}

	//-------------------------------------------------------
	// ���� ��ư�� Ȱ��ȭ ���Ѿ� �ϴ��� ���θ� �����Ѵ�. 
	//-------------------------------------------------------
	if(pclCurrentInvItem)
	{
		GetDlgItemText(hDlg, IDC_EDIT_MARKETSELLAMOUNT, buffer, 64);
		SI32 itemnum = _tstoi(buffer);
		if(itemnum > 0 )
		{
			GetDlgItemText(hDlg, IDC_EDITMARKETSELLPRICE, buffer, 64);
			SI32 price = _tstoi(buffer);
			if(price > 0)
			{
				//wsprintf(buffer, TEXT("%d %d"), itemnum, price);
				//pclClient->pclMessage->SetMsg(buffer);
				
				// ���� ��ư�� Ȱ��ȭ ��Ų��. 
				EnableSellButton(hDlg, IDC_BUTTON_MARKETSELL, TRUE);
				
				// �����ؾ� �� �����Ḧ �����ش�. 
				ShowRealFee(hDlg, itemnum, price);
				
			}
			else
			{
				// ���� ��ư�� ��Ȱ��ȭ ��Ų��. 
				EnableSellButton(hDlg, IDC_BUTTON_MARKETSELL, FALSE);
			}
		}
		else
		{
			// ���� ��ư�� ��Ȱ��ȭ ��Ų��. 
			EnableSellButton(hDlg, IDC_BUTTON_MARKETSELL, FALSE);
		}
	}
	else
	{
		// ���� ��ư�� ��Ȱ��ȭ ��Ų��. 
		EnableSellButton(hDlg, IDC_BUTTON_MARKETSELL, FALSE);
	}

	//------------------------------------------------------
	// ���� ȸ�� ��ư�� Ȱ��ȭ ���Ѿ� �ϴ��� ���θ� �����Ѵ�. 
	//------------------------------------------------------
	if(pclCurrentStgItem)
	{
		EnableGetFromMarketButton(hDlg, IDC_BUTTON_GETFROMMARKETSTORAGE, TRUE);
	}
	else
	{
		EnableGetFromMarketButton(hDlg, IDC_BUTTON_GETFROMMARKETSTORAGE, FALSE);
	}
*/

}
void NMarketUserSellDlg::ShowFeeRate()
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	TCHAR buffer[256];
	float feerate = (float)pMarketManager->clClientStrInfo.clMarketStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf(buffer, 256, TEXT("%3.1f%%"), feerate);
	SetEditText( EDIT_FEERATE, buffer );

}

void NMarketUserSellDlg::ShowFee( SI32 itemnum, GMONEY price )
{
	cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);

	//TCHAR buffer[256];

	GMONEY totalmoney = itemnum * price;

	// ���� 3�ڸ��� ��� ǥ��
//	StringCchPrintf( buffer, 256, TEXT("%I64d"), pMarketManager->clClientStrInfo.clMarketStrInfo.clFee.CalcFee(totalmoney) );
	TCHAR	szFeeMoney[64];
	g_JYLibFunction.SetNumUnit(	pMarketManager->clClientStrInfo.clMarketStrInfo.clFee.CalcFee(totalmoney), 
								szFeeMoney, sizeof(szFeeMoney));
	SetEditText( EDIT_FEE, szFeeMoney );
}


void NMarketUserSellDlg::SetStgItemPrice(cltMarketAccount * pclMarketAccount)
{
	if( pclMarketAccount == NULL  ) return;

	SI16 num = 0;

	for( SI32 i = 0; i < 4; ++i )
	{
		((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 + i ])->Clear();
	}

	for( i = 0; i < MAX_MARKET_ORDER_PER_PERSON; i++ )
	{
		if( pclMarketAccount->clItem[i].siUnique > 0)
		{
			if(pclMarketAccount->clMoney[i].itMoney > 0)
			{
				TCHAR* pText = GetTxtFromMgr(611);
				TCHAR moneybuf[256] ;

				// ����S�� ��� ���� ������ ���� �ʴ´�..(UIâ�� ũ���Ѱ�� ���ؼ�..) (PCK - 07.11.27)
				// ���� ©�� ���� ����, ������ â �ϴܿ� �ѹ��� ǥ���Ѵ�. - by LEEKH 2008-08-26
					g_JYLibFunction.SetNumUnit( pclMarketAccount->clMoney[i].itMoney, moneybuf, 256);
	
				if( num < 4 )
				{
					((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 + num ])->SetText( moneybuf );
				}
				num++;
			}
		}
	}

	TCHAR	buffer[64]	= {'\0'};
	SI32	maxNumber	= 0;
	if( pclClient->pclCM->CR[1]->pclCI->clBI.bMarKetPremiumService )
	{
		maxNumber = MAX_MARKET_ORDER_PER_PERSON;
		if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetFontColor( RGB(255, 0, 0) );
	}
	else 
	{
		maxNumber = 4;
		if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetFontColor( RGB(0, 0, 0) );
	}

	StringCchPrintf( buffer, 64, "%d/%d", num, maxNumber );
	if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetText(buffer);
}



void NMarketUserSellDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;

	TCHAR buffer[ 256 ];

	CASE_CONTROL( LISTVIEW_MYINVENTORY )
	{
		switch( nEvent )
		{
			case EVENT_LISTVIEW_LBUTTONDOWN:
			{
				m_bMyInven = TRUE;
				m_pStgItem->m_pListView->SetFocus(FALSE);
				m_pStgItem->m_siSelectedIndex = -1;
				m_pStgItem->m_pListView->ClearSelectedItem();

				m_pMyInventory->SelectAction();

				StringCchPrintf( buffer, 256, TEXT("%d"), m_pMyInventory->m_clSelectedItem.GetItemNum() );
				SetEditText( EDIT_AMOUNT, buffer );
			}
			break;
		}
	}
	else CASE_CONTROL( EDIT_PRICE )
	{
		switch( nEvent )
		{
		case EVENT_EDITBOX_CHANGE:
			{
				// ���ڰ� �ٲ�� �ٽ� , �� �����Ѵ�.
				NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
				kRawPrice.ReplaceAll(",", "");	// , ����
				TCHAR		szPrice[64] = { '\0', };
				GMONEY		siPrice = _tstoi64(kRawPrice);
				// ���ѱݾ��� ������ ���� �ݾ����� ���� 
				if( siPrice > pclClient->GetGlobalValue("GV_MarketMoneyLimit") + 1)
					siPrice = pclClient->GetGlobalValue("GV_MarketMoneyLimit") + 1;
				if( kRawPrice.Length() > 0 )
					g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));
				SetEditText( EDIT_PRICE, szPrice );
			}
			break;
		}
	}
	else CASE_CONTROL(BUTTON_SEARCHPRICE)
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				
			 
				pclclient->CreateInterface(NMARKET_SUB_DLG);
				
				
				if( pclclient->m_pDialog[NMARKET_DLG]->GetX() + pclclient->m_pDialog[NMARKET_DLG]->GetWidth() < 800 )
				{
					pclclient->m_pDialog[NMARKET_SUB_DLG]->MovePos( 
						pclclient->m_pDialog[NMARKET_DLG]->GetX() + pclclient->m_pDialog[NMARKET_DLG]->GetWidth(), pclclient->m_pDialog[NMARKET_DLG]->GetY() );			
				}
				else
				{
					pclclient->m_pDialog[NMARKET_SUB_DLG]->MovePos( 
						pclclient->m_pDialog[NMARKET_DLG]->GetX() - pclclient->m_pDialog[NMARKET_SUB_DLG]->GetWidth(), pclclient->m_pDialog[NMARKET_DLG]->GetY() );			

				}


				((NMarketUserBuyDlgSub*) pclclient->m_pDialog[NMARKET_SUB_DLG])->SetProductListFromUnique( m_pMyInventory->m_clSelectedItem.siUnique  );
			}
			break;
		}
	}
	else if( nControlID == COMMON_SCROLL )
	{
		switch( nEvent )
		{
		case EVENT_SCROLL_UPBUTTONCLICKED:
		case EVENT_SCROLL_DOWNBUTTONCLICKED:
		case EVENT_SCROLL_MOUSEMOVE:
			{
				SetScrollStgItemPrice();
			}
			break;
		}
	}

	else CASE_CONTROL( LISTVIEW_MARKETSTORAGE )
	{
		switch( nEvent )
		{
			case EVENT_LISTVIEW_LBUTTONDOWN:
				{
					m_bMyInven = FALSE;
					m_pMyInventory->m_pListView->SetFocus(FALSE);
					m_pMyInventory->m_siSelectedIndex = -1;
					m_pMyInventory->m_pListView->ClearSelectedItem();

					m_pStgItem->SelectAction();

					StringCchPrintf( buffer, 256, TEXT("%d"),m_pStgItem->m_clSelectedItem.GetItemNum() );
					SetEditText( EDIT_AMOUNT, buffer );
				}
				break;

			case EVENT_SCROLL_MOUSEMOVE:
				{
					SetScrollStgItemPrice();
				}
				break;
		}
	}

	else CASE_CONTROL( BUTTON_SELL )
	{

		SI32 id = 1;

		//-------------------------------------
		// ���ѵ� �ֹ� �Ǽ� �̻��� �� �� ����. 
		//-------------------------------------
		
		//------------------------------
		//	���忡 ���°� �ִ��� Ȯ���Ѵ�. 
		//------------------------------

		SI32 siBankCheck = pclClient->pclVillageManager->IsThereStructure(pclCM->CR[id]->GetCurrentVillageUnique(),RANKTYPE_BANK);
		if(pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0 && siBankCheck==1)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1669);
			SetMainExplain(pText);

			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			TCHAR* pTitle = GetTxtFromMgr(3942);
			pText = GetTxtFromMgr(5589);
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;
			MsgBox.Set( pParent, pTitle, pText, MSGBOX_TYPE_YESNO, 1 );
			BYTE TempBuffer[ 128 ];
		
			SI16 Size = sizeof( id );
			memcpy( TempBuffer, &id, sizeof( id ) );			
			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
			return;
		}
		if(pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0)
		{
			TCHAR* pTitle = GetTxtFromMgr(3942);
			TCHAR* pText = GetTxtFromMgr(5590);
			pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);
			return;

		}
		/*
		if(pclCM->CR[id]->pclCI->clBank.clAccountNum.siVillageUnique == 0)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1669);
			SetMainExplain(pText);
			return;
		}
		*/
		//-----------------------------
		// ������ Ȯ���Ѵ�. 
		//------------------------------
		
		if( m_pMyInventory->CheckCurrentSelect() == FALSE ) return;
		
		//------------------------------------
		// ���� ������ �ߺ��ؼ� �ø� �� ����. 
		//------------------------------------
		if(pclCM->CR[id]->pclCI->clMarket.IsInMarketOrder( m_pMyInventory->m_clSelectedItem.siUnique ) == true )
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1670);
			SetMainExplain(pText);
			return;
		}

		//----------------------------
		// ������ Ȯ���Ѵ�. 
		//----------------------------
		SI32 amount = _tstoi( GetEditText( EDIT_AMOUNT ) );

		if(amount <= 0)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1671);
			SetMainExplain(pText);
			return;
		}
		if(amount > 10000)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1672);
			SetMainExplain(pText);
			return;
		}

		//---------------------------
		// �ܰ��� Ȯ���Ѵ�. 
		//---------------------------
		//GMONEY price = _tstoi64( GetEditText( EDIT_PRICE ) );
		NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
		kRawPrice.ReplaceAll(",", "");	// , ����
		GMONEY price = _tstoi64(kRawPrice);

		if(price <= 0)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			TCHAR* pText = GetTxtFromMgr(1673);
			SetMainExplain(pText);
			return;
		}
		if( (INT64)price * amount > MAX_PRICE_IN_MARKET)
		{
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
			
			TCHAR szMoney[128] = { '\0', };
			g_JYLibFunction.SetNumUnit( MAX_PRICE_IN_MARKET, szMoney, sizeof(szMoney) );

			NTCHARString512 strMessage( GetTxtFromMgr(1674) );
			strMessage.Replace( TEXT("#money#"), szMoney );

			SetMainExplain(strMessage);
			return;
		}

		//--------------------------
		// ���ݾ��� ����Ѵ�. (1.0%) - �׶� �׶� �ٸ���. ��������..^^;;
		//--------------------------
		cltMarketManager *pMarketManager = ((cltMarketManager *)m_pStrManager);
		float feerate = (float)pMarketManager->clClientStrInfo.clMarketStrInfo.clFee.GetFeeRate() / 10;

		if( feerate <=0 )
		{
			feerate = 1;	// 1%
		}
		else if( feerate * 10 > MAX_FEE_RATE ) 
		{
			feerate = MAX_FEE_RATE / 10;	// 10%
		}

		//SI64 tax = ( (SI64)price * (SI64)amount ) / 100;
		SI64 totalmoney = (SI64)price * (SI64)amount;
		SI64 tax = pMarketManager->clClientStrInfo.clMarketStrInfo.clFee.CalcFee(totalmoney);

		if( tax > MIN_FEE && false == pclClient->pclCM->CR[1]->pclCI->clBI.bMarKetPremiumService )
		{
			if( pclclient->pclItemManager->IsItemInfoAtb(m_pMyInventory->m_clSelectedItem.siUnique, ITEMINFOATB_NOTTRADE) || 
				//===============================================================
				//cyj �ͼӾ������̸� ���Ͽ� �� �ø�����
				//===============================================================
				(m_pMyInventory->m_clSelectedItem.IsBelonging(pclclient->pclItemManager)) )
			{
				TCHAR *pText = GetTxtFromMgr(267, true);
				SetMainExplain(pText);
				return;
			}

			TCHAR* pText = GetTxtFromMgr(1675);

			TCHAR		szPrice[64] = { '\0', };
			GMONEY		siPrice = tax ;
			g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));


			StringCchPrintf(buffer, 256, pText, feerate, '%', szPrice);

			pText = GetTxtFromMgr(1676);

			stMsgBox MsgBox;
			// ���� dialog�� �� â ���� Child Dialog�϶�
			CControllerMgr *pParent = NULL;
			pParent = this->GetParentDialog();
			if(pParent == NULL ) return;
			MsgBox.Set( pParent, pText, buffer, MSGBOX_TYPE_YESNO, 0 );
			BYTE TempBuffer[ 128 ];
			SI16 Size = sizeof( id ) + sizeof( price ) + sizeof(amount) + sizeof( tax );
			memcpy( TempBuffer, &id, sizeof( id ) );
			memcpy( &TempBuffer[ sizeof(id) ], &price, sizeof( price ) );
			memcpy( &TempBuffer[ sizeof( id ) + sizeof( price ) ], &amount, sizeof( amount ) );
			memcpy( &TempBuffer[ sizeof( id ) + sizeof( price ) + sizeof(amount) ], &tax, sizeof( tax ) );
			pclclient->SetMsgBox( &MsgBox, TempBuffer, Size );
		}
		else
		{
			//---------------------------------------
			// ������ ��ǰ�� �ŵ��϶�� ��û�� �뺸�Ѵ�. 
			//---------------------------------------
			if(id)
			{
					//PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
				cltTradeOrder clOrder(TRADEORDER_TYPE_OBJECT, 0, price, amount, 0, &m_pMyInventory->m_clSelectedItem );				
				cltMsg clMsg(GAMEMSG_REQUEST_SELLITEM, sizeof(cltTradeOrder), (BYTE*)&clOrder);				
				pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		// ������ �ܰ��� �Է��� ���� �����. (PCK - 07.11.27)
		((CEdit*)m_pControlMap[ EDIT_AMOUNT ])->Clear();
		((CEdit*)m_pControlMap[ EDIT_PRICE ])->Clear();

		m_pStgItem->m_pListView->SetScrollTrackPos( 0 );
	}

	else CASE_CONTROL( BUTTON_CANCEL_ORDER )
	{

		SI32 id = 1;

		//-----------------------------
		// ������ Ȯ���Ѵ�. 
		//------------------------------

		if( m_pStgItem->CheckCurrentSelect() == FALSE ) return;

		//----------------------------------
		// �Űܾ� �ϴ� ������ Ȯ���Ѵ�. 
		//----------------------------------
		SI32 amount = _tstoi( GetEditText( EDIT_AMOUNT ) );

		if(amount < 0)
		{
			TCHAR* pText = GetTxtFromMgr(1668);
			SetMainExplain(pText);
			return;
		}

		//---------------------------------------
		// ������ ��ǰ�� ȸ���϶�� ��û�� �뺸�Ѵ�. 
		//---------------------------------------
		//PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.

		// Item�� ������ �����ϰ� �����Ѵ�. 
		cltItem clItem;
		clItem.Set( &m_pStgItem->m_clSelectedItem );
		clItem.SetItemNum( amount );

		cltGetItemFromMarketInfo clInfo(0, 
			m_pStgItem->m_siSelectedIndex, 
			clItem.CanPile(pclClient->pclItemManager), 
			&clItem, 
			-1, NULL);

		cltMsg clMsg(GAMEMSG_REQUEST_GETFROMMARKET, sizeof(clInfo), (BYTE*)&clInfo);
		
		pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		
		m_pStgItem->m_pListView->SetScrollTrackPos( 0 );
	}

}



void NMarketUserSellDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient *pclclient = (cltClient*)pclClient;
	switch( MsgIndex )
	{
	case 0:	// ���� ����
		{
			if ( pData == NULL || DataLen < 1 )
			{
				return;
			}

			if ( RetValue )
			{
				SI32 id = *((SI32*)pData);
				GMONEY price = *((GMONEY*)(pData + 4));
				SI32 amount = *((SI32*)(pData + 12 ));
				GMONEY tax =  *((GMONEY*)(pData + 16 ));
				TCHAR buffer[ 256 ];

				// ���� ������ ���� �ִ��� Ȯ���Ѵ�. 
				if( false == pclClient->pclCM->CR[1]->pclCI->clBI.bMarKetPremiumService )
				{
					if(pclClient->pclCM->CR[id]->pclCI->clIP.GetMoney() < tax)
					{
						pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
						TCHAR* pText = GetTxtFromMgr(1677);
						StringCchPrintf(buffer, 256, pText);
						SetMainExplain(buffer);
						return;
					}
				}
				
				//---------------------------------------
				// ������ ��ǰ�� �ŵ��϶�� ��û�� �뺸�Ѵ�. 
				//---------------------------------------
				if(id)
				{
						//PersonID�� 0���� ������ �������� ������ ������ �����Ѵ�.
					cltTradeOrder clOrder(TRADEORDER_TYPE_OBJECT, 0, price, amount, 0, &m_pMyInventory->m_clSelectedItem );
					
					cltMsg clMsg(GAMEMSG_REQUEST_SELLITEM, sizeof(cltTradeOrder), (BYTE*)&clOrder);
					
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
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
				SI32 id = *((SI32*)pData);

				if(id)
				{
					cltGameMsgRequest_CreateBankAccount clinfo( pclCM->CR[id]->GetCurrentVillageUnique() );

					// ���� ���� ��û 
					cltMsg clMsg( GAMEMSG_REQUEST_CREATEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);			
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
				}
				// �������� ���� �������� 0 �̸� ������ ���� �����Ƿ� ������ �����޽����� ����� �ʴ´�.
				/*TCHAR* pTitle = GetTxtFromMgr(5591);
				TCHAR* pText  = GetTxtFromMgr(5592);
				pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(pTitle, pText);*/
			}
			
		}
		break;
	}
}

// [����] ��ũ�ѵɶ� ������ ǥ�õǴ� �κ��� ó���ϴ� �Լ� - 2008.02.13
void NMarketUserSellDlg::SetScrollStgItemPrice()
{
	SI32 siTrackPos	= m_pStgItem->m_pListView->GetScrollTrackPos(); // �������� �ֻ��� ������ ��ȣ
	SI32 siRealPos	= 0;
	SI16 siEditNum	= 0;	// ����Ʈ ��Ʈ�ѿ� �� ��ȣ
	

	// ����Ʈ ��Ʈ�ѿ� �ؽ�Ʈ�� ��� Ŭ����
	for ( SI32 siIndex=0; siIndex<4; siIndex++ )
	{
		((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 + siIndex ])->Clear();
	}

	// �������� �ֻ��� ������ ��ȣ���� �ִ� ��ȣ���� �ݺ���
	for ( SI32 siCount=0; siCount<MAX_MARKET_ORDER_PER_PERSON; siCount++ )
	{
		if ( ( pclCM->CR[1]->pclCI->clMarket.clInfo.clItem[siCount].siUnique > 0 )
			&& ( pclCM->CR[1]->pclCI->clMarket.clInfo.clMoney[siCount].itMoney > 0 )
		)
		{
			if ( siRealPos >= siTrackPos )
			{
				TCHAR*	pszMoney = GetTxtFromMgr(611);
				TCHAR	szMoneyBuf[256];

				// ����S�� ��� ���� ������ �ȳ������� �Ѵ�.(UIâ�� ũ���Ѱ�� ���ؼ�..) (PCK - 07.11.27)
				if(pclClient->siServiceArea == ConstServiceArea_Korea)
				{
					g_JYLibFunction.SetNumUnit( pclCM->CR[1]->pclCI->clMarket.clInfo.clMoney[siCount].itMoney, szMoneyBuf, 256);
				}
				else
				{	
					g_JYLibFunction.SetNumUnit( pclCM->CR[1]->pclCI->clMarket.clInfo.clMoney[siCount].itMoney, szMoneyBuf, 256, pszMoney );
				}

				SetEditText(EDIT_ITEMPRICE1 + siEditNum, szMoneyBuf);
				siEditNum++;
			}

			siRealPos++;
		}

		// �ѹ��� ǥ�õ� �� �ִ� �ؽ�Ʈ�� 4���̱� ������ 4���� ǥ���ϸ� �ݺ��� ����
		if ( siEditNum >= 4 )
		{
			break;
		}
	}
}
