#include "NNewMarketDlg.h"

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

#include "../../CommonLogic/Market/Market.h"
//#include "../../CommonLogic/TradeOrder/TradeOrder.h"

extern cltCommonLogic*	pclClient;
extern CJYLibFunction	g_JYLibFunction;

NNewMarketUserSellDlg::NNewMarketUserSellDlg()
{
	m_pMyInventory	= new NStrInventory;
	m_pStgItem		= new NStrInventory;

	m_fFeeRate	= 0.f; 
	m_siItemNum = 0;
	m_Tax		= 0;
	m_Price		= 0; 

	ZeroMemory( &m_clNewMarketAccount, sizeof(m_clNewMarketAccount) );
}

NNewMarketUserSellDlg::~NNewMarketUserSellDlg()
{
	NDelete( m_pMyInventory );
	NDelete( m_pStgItem		);
}

void NNewMarketUserSellDlg::InitDlg()
{
 	SetControlMap( LISTVIEW_MYINVENTORY,	TEXT("listview_myinventory") );
 	SetControlMap( LISTVIEW_MARKETSTORAGE,	TEXT("listview_marketstorage") );
	SetControlMap( EDIT_AMOUNT,				TEXT("editbox_amount") );
	SetControlMap( EDIT_PRICE,				TEXT("editbox_price") );
	SetControlMap( EDIT_FEERATE,			TEXT("editbox_feerate") );
	SetControlMap( EDIT_FEE,				TEXT("editbox_fee") );
	SetControlMap( EDIT_MONEY_UNIT,			TEXT("editbox_money_unit") );
	SetControlMap( BUTTON_SELL,				TEXT("button_sell") );
	SetControlMap( BUTTON_CANCEL_ORDER,		TEXT("button_cancel_order") );
	SetControlMap( EDIT_ITEMPRICE1,			TEXT("editbox_NONAME1") );
	SetControlMap( EDIT_ITEMPRICE2,			TEXT("editbox_NONAME2") );
	SetControlMap( EDIT_ITEMPRICE3,			TEXT("editbox_NONAME3") );
	SetControlMap( EDIT_ITEMPRICE4,			TEXT("editbox_NONAME4") );	
	SetControlMap( BUTTON_SEARCHPRICE,		TEXT("button_SearchPrice") );
	SetControlMap( STATIC_TOTALNUM,			TEXT("statictext_totalnum") );
	SetControlMap( STATIC_MONEYUNIT,		TEXT("statictext_MoneyUnit") );
	
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE2 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE3 ])->ShowScrollBar(false);
	((CEdit*)m_pControlMap[ EDIT_ITEMPRICE4 ])->ShowScrollBar(false);

	((CEdit*)m_pControlMap[ EDIT_AMOUNT ])->SetNumberMode(true);
	((CEdit*)m_pControlMap[ EDIT_PRICE ])->SetMaxEditTextLength(20);

	NTCHARString128	kText(GetTxtFromMgr(8783));
	if(m_pControlMap[ STATIC_MONEYUNIT ])
	{
		((CStatic*)m_pControlMap[ STATIC_MONEYUNIT ])->SetTextPrintOption(DT_TOP | DT_RIGHT);
		((CStatic*)m_pControlMap[ STATIC_MONEYUNIT ])->SetText(kText);
	}

	SetMyInventory();
	SetStrInventory();

	SetActionTimer( 3000 );
	SetTimerOnOff( true );

	// ���� ���ֿ� ���� �ø� Ǯ�� ���� ��û
	cltMsg clMsg(GAMEMSG_REQUEST_NEWMARKETACCOUNT, 0, NULL);
	pclClient->pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);
}

void NNewMarketUserSellDlg::Action()
{
	// ���������� �ֱ�������. (ó�� ������ �ȵɶ��� �ִ�.)
	ShowFeeRate();
}

void NNewMarketUserSellDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	cltClient *pclclient = (cltClient*)pclClient;

	CASE_CONTROL( LISTVIEW_MYINVENTORY )
	{
		switch( nEvent )
		{
			case EVENT_LISTVIEW_LBUTTONDOWN:
			{
				m_pStgItem->m_pListView->SetFocus(FALSE);
				m_pStgItem->m_siSelectedIndex = -1;
				m_pStgItem->m_pListView->ClearSelectedItem();

				m_pMyInventory->SelectAction();
				
				TCHAR szBuffer[ 256 ];
				StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%d"), m_pMyInventory->m_clSelectedItem.GetItemNum() );
				SetEditText( EDIT_AMOUNT, szBuffer );

				
				SetEditText( EDIT_PRICE, "0" );									// ������ ���� ����.		
				ShowFee( m_pMyInventory->m_clSelectedItem.GetItemNum(), 0 );	// ������ ����.
				SetEditText( EDIT_MONEY_UNIT, "0", 0 );							// �� ���� ����.
			}
			break;
		}
	}

	else CASE_CONTROL( EDIT_AMOUNT )
	{
		switch( nEvent )
		{
			case EVENT_EDITBOX_CHANGE:
				{
					RefreshSellInfo();
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
					RefreshSellInfo();
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
				pclclient->CreateInterface( NNEWMARKET_SUB_DLG );
							
				if( pclclient->m_pDialog[NNEWMARKET_DLG]->GetX() + pclclient->m_pDialog[NNEWMARKET_DLG]->GetWidth() < 800 )
				{
					pclclient->m_pDialog[NNEWMARKET_SUB_DLG]->MovePos( pclclient->m_pDialog[NNEWMARKET_DLG]->GetX() + pclclient->m_pDialog[NNEWMARKET_DLG]->GetWidth(), pclclient->m_pDialog[NNEWMARKET_DLG]->GetY() );			
				}
				else
				{
					pclclient->m_pDialog[NNEWMARKET_SUB_DLG]->MovePos( pclclient->m_pDialog[NNEWMARKET_DLG]->GetX() - pclclient->m_pDialog[NNEWMARKET_SUB_DLG]->GetWidth(), pclclient->m_pDialog[NNEWMARKET_DLG]->GetY() );			
				}

				if( pclclient->m_pDialog[NNEWMARKET_SUB_DLG] )
				{
					((NNewMarketUserBuyDlgSub*)pclclient->m_pDialog[NNEWMARKET_SUB_DLG])->SetProductListFromUnique( m_pMyInventory->m_clSelectedItem.siUnique );
				}
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
					m_pMyInventory->m_pListView->SetFocus(FALSE);
					m_pMyInventory->m_siSelectedIndex = -1;
					m_pMyInventory->m_pListView->ClearSelectedItem();

					m_pStgItem->SelectAction();

					TCHAR szBuffer[64] = "";
					StringCchPrintf( szBuffer, sizeof(szBuffer), TEXT("%d"), m_pStgItem->m_clSelectedItem.GetItemNum() );
					SetEditText( EDIT_AMOUNT, szBuffer );
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
		if( false == IsSell() ) return;
		
		TCHAR		szBuffer[256]	= "";
		TCHAR		szPrice[64]		= { '\0', };
		g_JYLibFunction.SetNumUnit( m_Price * m_siItemNum, szPrice, sizeof(szPrice) );
		StringCchPrintf(szBuffer, sizeof(szBuffer), GetTxtFromMgr(1675), m_fFeeRate, '%', szPrice);

		stMsgBox MsgBox;
		MsgBox.Set( this, GetTxtFromMgr(1676), szBuffer, MSGBOX_TYPE_YESNO, SELL_MSGBOX );
		pclclient->SetMsgBox( &MsgBox, NULL, 0 );
	}
	else CASE_CONTROL( BUTTON_CANCEL_ORDER )
	{
		CancelOrder();
	}

}

void NNewMarketUserSellDlg::SetMyInventory( void )
{
	m_pMyInventory->CreateInventory( MAX_ITEM_PER_PERSON, (CListView*)m_pControlMap[ LISTVIEW_MYINVENTORY ] );
	m_pMyInventory->m_pListView->SetBKColorUse( true );
	m_pMyInventory->m_pListView->SetBorder( true );
	m_pMyInventory->LoadMyInventory();
}

void NNewMarketUserSellDlg::ShowFeeRate( void )
{
	cltNewMarketManager* pMarketManager = ((cltNewMarketManager*)m_pStrManager);

	TCHAR szBuffer[16];
	float feerate = (float)pMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf(szBuffer, sizeof(szBuffer), TEXT("%3.1f%%"), feerate);
	SetEditText( EDIT_FEERATE, szBuffer );
}

void NNewMarketUserSellDlg::ShowFee( SI32 _siItemNum, GMONEY _Price )
{
	cltNewMarketManager* pMarketManager = ((cltNewMarketManager*)m_pStrManager);

	GMONEY Totalmoney = _siItemNum * _Price;

	TCHAR	szFeeMoney[64];
	g_JYLibFunction.SetNumUnit(	pMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.CalcFee(Totalmoney), 
								szFeeMoney, sizeof(szFeeMoney));
	
	SetEditText( EDIT_FEE, szFeeMoney );
}

bool NNewMarketUserSellDlg::IsSell( bool _bEditBoxClear )
{
	if( false == pclClient->pclItemManager->IsNewMarketTrade( m_pMyInventory->m_clSelectedItem.siUnique ) )
	{
		SetMainExplain(GetTxtFromMgr(9858));
		return false;
	}

	SI32 ItemNum = 0;
	for( SI32 i = 0; i < MAX_NEWMARKET_ORDER_PER_PERSON; i++ )
	{
		if( m_clNewMarketAccount.clItem[i].siUnique > 0)
		{
			++ItemNum;
		}
	}

	if( pclClient->pclCM->CR[1]->pclCI->clBI.bNewMarketPremiumService )
	{
		if( ItemNum >= MAX_PERSON_NEWMARKET_ORDER_NUM )	return false;
	}
	else
	{
		if( ItemNum >= 6 )	return false;
	}

	cltClient* pclclient = (cltClient*)pclClient;

	cltCharClient* pclChar = pclClient->pclCM->GetCharClient(1);
	//	���°� �ִ��� Ȯ���Ѵ�. 
	BOOL bBankCheck = pclClient->pclVillageManager->IsThereStructure( pclChar->GetCurrentVillageUnique(), RANKTYPE_BANK );
	if( 0 == pclChar->pclCI->clBank.clAccountNum.siVillageUnique && TRUE == bBankCheck )
	{
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
		SetMainExplain( GetTxtFromMgr( 1669 ) );

		CControllerMgr *pParent = NULL;
		pParent = this->GetParentDialog();
		if(pParent == NULL ) return false;
		
		stMsgBox MsgBox;
		MsgBox.Set( pParent, GetTxtFromMgr(3942), GetTxtFromMgr(5589), MSGBOX_TYPE_YESNO, CREATE_BANK_MSGBOX );
		pclclient->SetMsgBox( &MsgBox, NULL, 0 );
		return false;
	}
	if( pclChar->pclCI->clBank.clAccountNum.siVillageUnique == 0 )
	{
		pclclient->m_pDialog[ NOTIFYMSG_DLG ]->SetText(GetTxtFromMgr(3942), GetTxtFromMgr(5590));
		return false;
	}

	// ���õ� �������� �ִ��� üũ.
	if( FALSE == m_pMyInventory->CheckCurrentSelect() ) return false;

	// ������ Ȯ���Ѵ�. 
	SI32 siSellItemNum = _tstoi( GetEditText( EDIT_AMOUNT ) );
	if(siSellItemNum <= 0)
	{
		pclClient->PushEffect( pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0 );
		SetMainExplain( GetTxtFromMgr( 1671 ) );
		return false;
	}
	else if( siSellItemNum > MAX_ITEM_PILE_NUMBER )
	{
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
		SetMainExplain( GetTxtFromMgr(1672) );
		return false;
	}


	//---------------------------
	// �ܰ��� Ȯ���Ѵ�. 
	//---------------------------
	NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
	kRawPrice.ReplaceAll(",", "");	// , ����
	GMONEY Price = _tstoi64(kRawPrice);

	if( Price <= 0 )
	{
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);
		SetMainExplain(GetTxtFromMgr(1673));
		return false;
	}
	else if( Price * siSellItemNum > MAX_PRICE_IN_MARKET)
	{
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_FAILURE")), 0, 0);

		TCHAR szMoney[128] = { '\0', };
		g_JYLibFunction.SetNumUnit( MAX_PRICE_IN_MARKET, szMoney, sizeof(szMoney) );

		NTCHARString512 strMessage( GetTxtFromMgr(1674) );
		strMessage.Replace( TEXT("#money#"), szMoney );

		SetMainExplain( strMessage );
		return false;
	}
	
	// ���ݾ��� ����Ѵ�. 
	cltNewMarketManager* pNewMarketManager = ((cltNewMarketManager*)m_pStrManager);
	float feerate = (float)pNewMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.GetFeeRate() / 10;
	if( feerate < MIN_FEE_RATE_NEWMARKET )
		feerate = MIN_FEE_RATE_NEWMARKET;	 //  5%
	else if( feerate > MAX_FEE_RATE_NEWMARKET ) 
		feerate = MAX_FEE_RATE_NEWMARKET;	 // 15%
	
	GMONEY Totalmoney = Price * siSellItemNum;
	GMONEY Tax = pNewMarketManager->clClientStrInfo.clNewMarketStrInfo.clFee.CalcFee( Totalmoney );

	// �����̾��� �����ᰡ ��¥.
	if( true == pclChar->pclCI->clBI.bNewMarketPremiumService )
	{
		Tax = 0;
	}
	else 
	{
		// ������ ������ ���� ������ �Ǹ� ����� ���� ���Ѵ�.
		if( pclChar->pclCI->clIP.GetMoney() < Tax )	
		{
            return false;
		}
	}

	// ���� ����Ʈ �ڽ��� �ʱ�ȭ �Ѵ�.
	if( _bEditBoxClear ) 
	{
		// ������ �ܰ��� �Է��� ���� �����. (PCK - 07.11.27)
		((CEdit*)m_pControlMap[ EDIT_AMOUNT ])->Clear();
		((CEdit*)m_pControlMap[ EDIT_PRICE ])->Clear();
		((CEdit*)m_pControlMap[ EDIT_FEE ])->Clear();
		((CEdit*)m_pControlMap[ EDIT_MONEY_UNIT ])->Clear();
	}	

	m_pStgItem->m_pListView->SetScrollTrackPos( 0 );

   	m_fFeeRate	= feerate; 
	m_siItemNum	= siSellItemNum;
	m_Tax		= Tax;
	m_Price		= Price; 

	return true;
}



void NNewMarketUserSellDlg::RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen )
{
	cltClient* pclclient = (cltClient*)pclClient;
	switch( MsgIndex )
	{
	case CREATE_BANK_MSGBOX:	
		{
			if( false == RetValue )			return;

			cltGameMsgRequest_CreateBankAccount clinfo( pclCM->CR[1]->GetCurrentVillageUnique() );

			// ���� ���� ��û 
			cltMsg clMsg( GAMEMSG_REQUEST_CREATEBANKACCOUNT, sizeof(clinfo), (BYTE*)&clinfo);			
			pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);	

		}
		break;
	case SELL_MSGBOX:
		{
			if( false == RetValue )	return;
			if( false == IsSell() )	return;

			cltCharClient* pclChar = pclClient->pclCM->GetCharClient(1);
			if( NULL == pclChar ) return; 

			NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
			kRawPrice.ReplaceAll(",", "");	// , ����
			GMONEY siPrice = _tstoi64(kRawPrice);
			
			cltNewTradeOrder clOrder(  &m_pMyInventory->m_clSelectedItem, 
										false, 
										0, 
										0, 
										0, 
										_tstoi(GetEditText( EDIT_AMOUNT )), 
										0, 
										siPrice );

			if(		m_pMyInventory->m_siSelectedIndex < PERSONITEM_INV0 
				||	m_pMyInventory->m_siSelectedIndex > MAX_ITEM_PER_PERSON)
				return;
			
			cltGameMsgRequest_NewSellItem clSellItemInfo(&clOrder, m_pMyInventory->m_siSelectedIndex);

			cltMsg clMsg(GAMEMSG_REQUEST_NEWSELLITEM, sizeof(cltGameMsgRequest_NewSellItem), (BYTE*)&clSellItemInfo);

			pclChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
		break;
	case RECALL_MSGBOX:
		{
			if( false == RetValue )			return;

			cltCharClient* pclChar = pclClient->pclCM->GetCharClient(1);
			if( NULL == pclChar ) return;

			cltMsg clMsg(GAMEMSG_RESPONSE_RECALL_NEWMARKET, 0, (BYTE*)NULL);				
			pclChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
		break;
	}
}

void NNewMarketUserSellDlg::SetStgItemPrice( void )
{
	SI16 num = 0;
	for( SI32 i = 0; i < 4; ++i )
	{
		((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 + i ])->Clear();
	}

	for( i = 0; i < MAX_NEWMARKET_ORDER_PER_PERSON; i++ )
	{
		if( m_clNewMarketAccount.clItem[i].siUnique > 0)
		{
			if(m_clNewMarketAccount.clMoney[i].itMoney > 0)
			{
				TCHAR* pText = GetTxtFromMgr(611);
				TCHAR moneybuf[256] ;

				// ����S�� ��� ���� ������ ���� �ʴ´�..(UIâ�� ũ���Ѱ�� ���ؼ�..) (PCK - 07.11.27)
				// ���� ©�� ���� ����, ������ â �ϴܿ� �ѹ��� ǥ���Ѵ�. - by LEEKH 2008-08-26
				g_JYLibFunction.SetNumUnit( m_clNewMarketAccount.clMoney[i].itMoney, moneybuf, 256);

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
	if( pclClient->pclCM->CR[1]->pclCI->clBI.bNewMarketPremiumService )
	{
		maxNumber = MAX_NEWMARKET_ORDER_PER_PERSON;
		if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetFontColor( RGB(255, 0, 0) );
	}
	else 
	{
		maxNumber = 6;
		if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetFontColor( RGB(0, 0, 0) );
	}

	StringCchPrintf( buffer, 64, "%d/%d", num, maxNumber );
	if(m_pControlMap[STATIC_TOTALNUM])	((CStatic*)m_pControlMap[STATIC_TOTALNUM])->SetText(buffer);
}

void NNewMarketUserSellDlg::SetStrInventory( void )
{
	m_pStgItem->CreateInventory( MAX_NEWMARKET_ORDER_PER_PERSON, (CListView*)m_pControlMap[ LISTVIEW_MARKETSTORAGE ], NULL, NStrInventory::SELECT_NEWMARKETACCOUNT );
	m_pStgItem->LoadInventory2( &m_clNewMarketAccount, TRUE );
}


void NNewMarketUserSellDlg::SetNewMarketAccount(cltGameMsgResponse_NewMarketAccount* pNewMarketAccount)
{
	memcpy( &m_clNewMarketAccount, &pNewMarketAccount->clMarketAccount, sizeof(m_clNewMarketAccount) );
	
	SetStgItemPrice();
    SetMyInventory();
	SetStrInventory();
}
void NNewMarketUserSellDlg::RefreshSellInfo( void )
{
	// ���ڰ� �ٲ�� �ٽ� , �� �����Ѵ�.
	NTCHARString512	kRawPrice(GetEditText( EDIT_PRICE ));
	kRawPrice.ReplaceAll(",", "");	// , ����

	TCHAR		szPrice[64] = { '\0', };
	GMONEY		siPrice		= _tstoi64(kRawPrice); 

	// ���ѱݾ��� ������ ���� �ݾ����� ���� 
	if( siPrice > pclClient->GetGlobalValue("GV_MarketMoneyLimit") + 1)
		siPrice = pclClient->GetGlobalValue("GV_MarketMoneyLimit") + 1;

	if( kRawPrice.Length() > 0 )
		g_JYLibFunction.SetNumUnit(siPrice, szPrice, sizeof(szPrice));

	SetEditText( EDIT_PRICE, szPrice );

	ShowFee( _tstoi(GetEditText( EDIT_AMOUNT )), siPrice );	// ������ ���̱�.

	// ���� * ���� (���Ǹž�) ǥ��
	TCHAR szbuffer[64] = "";
	g_JYLibFunction.SetNumUnit( siPrice * _tstoi(GetEditText( EDIT_AMOUNT )), szbuffer, sizeof(szbuffer), GetTxtFromMgr(611)); 
	SetEditText( EDIT_MONEY_UNIT, szbuffer, ((cltClient*)pclClient)->GetColorByPrice(siPrice * m_pMyInventory->m_clSelectedItem.GetItemNum()) );
}


// [����] ��ũ�ѵɶ� ������ ǥ�õǴ� �κ��� ó���ϴ� �Լ� - 2008.02.13
void NNewMarketUserSellDlg::SetScrollStgItemPrice()
{
	SI32 siTrackPos	= m_pStgItem->m_pListView->GetScrollTrackPos(); // �������� �ֻ��� ������ ��ȣ
	SI32 siRealPos	= 0;
	SI16 siEditNum	= 0;	// ����Ʈ ��Ʈ�ѿ� �� ��ȣ


	// ����Ʈ ��Ʈ�ѿ� �ؽ�Ʈ�� ��� Ŭ����
	for ( SI32 siIndex = 0; siIndex < 4; siIndex++ )
	{
		((CEdit*)m_pControlMap[ EDIT_ITEMPRICE1 + siIndex ])->Clear();
	}

	// �������� �ֻ��� ������ ��ȣ���� �ִ� ��ȣ���� �ݺ���
	for ( SI32 siCount=0; siCount<MAX_NEWMARKET_ORDER_PER_PERSON; siCount++ )
	{
		if ( ( m_clNewMarketAccount.clItem[siCount].siUnique > 0 )
			&& ( m_clNewMarketAccount.clMoney[siCount].itMoney > 0 )
			)
		{
			if ( siRealPos >= siTrackPos )
			{
				TCHAR*	pszMoney = GetTxtFromMgr(611);
				TCHAR	szMoneyBuf[256];

				// ����S�� ��� ���� ������ �ȳ������� �Ѵ�.(UIâ�� ũ���Ѱ�� ���ؼ�..) (PCK - 07.11.27)
				if(pclClient->siServiceArea == ConstServiceArea_Korea)
				{
					g_JYLibFunction.SetNumUnit( m_clNewMarketAccount.clMoney[siCount].itMoney, szMoneyBuf, 256);
				}
				else
				{	
					g_JYLibFunction.SetNumUnit( m_clNewMarketAccount.clMoney[siCount].itMoney, szMoneyBuf, 256, pszMoney );
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

void NNewMarketUserSellDlg::CancelOrder( void )
{
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
		char* pText = GetTxtFromMgr(1668);
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

	cltGetItemFromNewMarketInfo clInfo( m_pStgItem->GetSelectOrderIndex(), 
										clItem.CanPile(pclClient->pclItemManager), 
										&clItem, 
										-1, 
										NULL	);

	cltMsg clMsg(GAMEMSG_REQUEST_GETFROMNEWMARKET, sizeof(clInfo), (BYTE*)&clInfo);
	pclClient->pclCM->GetCharClient(1)->SendNetMsg((sPacketHeader*)&clMsg);

}

