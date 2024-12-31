//#include <CommonLogic.h>
#include "..\..\Server\Server.h"
//
//#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"
//#include "..\..\Common\Util\Control\Control.h"
//
//#include "..\..\Resource.h"
//
//#include "SummonMarket.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Market.h"
//
#include "MsgRval-Define.h"
#include "../../CommonLogic/MsgType-Structure.h"
#include "../../CommonLogic/Msg/MsgType-SummonMarket.h"
//
//#include "../CityHall/TaxpaymentListDlg.h"

#include "NSummonMarketDlg.h"

#include <tchar.h>
#include "../../InterfaceMgr/Interface/List.h"
#include "../../InterfaceMgr/Interface/ComboBox.h"
#include "../../InterfaceMgr/Interface/ImageStatic.h"

//#include "../../../CommonLogic/MsgType-Person.h"
#include "../../../CommonLogic/MsgType-Structure.h"

#include "../../../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

extern cltCommonLogic* pclClient;

NSummonMarketBuyDlg::NSummonMarketBuyDlg()
{
}

NSummonMarketBuyDlg::~NSummonMarketBuyDlg()
{
}

void NSummonMarketBuyDlg::InitDlg()
{
	SetControlMap(	IMAGESTATIC_PORTRAIT,   	TEXT("imagestatic_portrait") );
	SetControlMap(	BUTTON_BUY,					TEXT("button_buy"));
	SetControlMap(	BUTTON_FIRST,				TEXT("button_first"));
	SetControlMap(	BUTTON_NEXT	,				TEXT("button_next"));
	SetControlMap(	BUTTON_SELECTORDER,			TEXT("button_selectorder"));
	SetControlMap(	BUTTON_REFRESH,				TEXT("button_refresh"));
	SetControlMap(	LISTBOX_SUMMON,				TEXT("listbox_summon"));
	SetControlMap(	LISTBOX_EXPLAIN,			TEXT("listbox_base_info"));
	SetControlMap(	LISTBOX_ABILITY_INFO,		TEXT("listbox_ability_ifo"));
	SetControlMap(	COMBOBOX_KIND,				TEXT("combobox_kind"));
	SetControlMap(	RADIOBUTTON_SUMMON,			TEXT("radiobutton_summon"));
	SetControlMap(	RADIOBUTTON_SUMMON_PET,		TEXT("radiobutton_summon_pet"));
	SetControlMap(	RADIOBUTTON_SUMMON_BOSS,	TEXT("radiobutton_summon_boss"));
	SetControlMap(	STATICTEXT_PAGE,			TEXT("statictext_page"));
	
	// [����] �����ŷ� ��ư ����.
	((CButton*)m_pControlMap[ BUTTON_SELECTORDER ])->Show(false);

	CRadioButton* pRadioButton_summon		= (CRadioButton*)m_pControlMap[ RADIOBUTTON_SUMMON ];
	pRadioButton_summon->SetCheck(true);

	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	pSummonManager->m_siKind		= -1;
	pSummonManager->m_siCurrentPage	=  0;
	pSummonManager->siSelectedIndex = -1;

	int i;

	pSummonManager->bShowResponseOrderSwitch = FALSE;
	
	// ����Ʈ ���
	CList *pList_summon  = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CList *pList_ability = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	if( pList_summon == NULL || pList_explain == NULL ) 
		return; 

	{
		int width[]		= { 120, 118, 0 };

		TCHAR* pText[3];

		pText[0] = GetTxtFromMgr(449);
		pText[1] = GetTxtFromMgr(1678);
		pText[2] = NULL;

		for( i = 0; i < 3; ++i ) 
		{ 
			pList_summon->SetColumn( i, width[i], pText[i] );
		}

        pList_summon->SetTextPrintOption( DT_LEFT | DT_VCENTER | DT_SINGLELINE );
		pList_summon->SetBorder( true );
		pList_summon->SetBKColorUse( true );
		pList_summon->Refresh();
	}

	{ 
		int width[]  = { 75, 113 };   
		int width2[] = { 75,  73 };   

		TCHAR* pText[2];

		pText[0] = GetTxtFromMgr(1780);
		pText[1] = GetTxtFromMgr(1565);

		for( i = 0; i < 2; ++i ) 
		{   
			pList_explain->SetColumn( i, width[i], pText[i] );
			pList_ability->SetColumn( i, width2[i], pText[i] );
		}

		pList_explain->SetBorder( true );
		pList_explain->SetBKColorUse( true );
		pList_explain->Refresh();

		pList_ability->SetBorder( true );
		pList_ability->SetBKColorUse( true );
		pList_ability->Refresh();

		SI32 id = 1;

		//cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_ORDERLIST, 0 );
		//pclClient->pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

		AddSummonKind();
	}		
}

void NSummonMarketBuyDlg::Action()
{
	SI32 id = 1;
	
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	// ����Ʈ ���
	CList *pList_summon  = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CList *pList_ability = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	if( pList_summon == NULL || pList_explain == NULL  || pList_ability == NULL ) 
		return; 

	if(pSummonManager->bShowResponseOrderSwitch == TRUE )
	{
		pSummonManager->bShowResponseOrderSwitch = FALSE;

		ShowResponseOrder();
		
		CStatic *pStaticText_page  = (CStatic*)m_pControlMap[ STATICTEXT_PAGE ];
		TCHAR szPage[16] = "";
		StringCchPrintf(szPage, sizeof(szPage), "%d / %d", pSummonManager->m_siCurrentPage + 1, 
														   pSummonManager->m_siTotalPageNum + 1	);
		pStaticText_page->SetText(szPage);
	}

	if(pSummonManager->bSelectedSwitch == TRUE)
	{
		ShowResponseExplain();

		pSummonManager->bSelectedSwitch = FALSE;

		pSummonManager->siTotalResponseOrderNumber = 0;

		pList_summon->Clear();
		pList_summon->Refresh();
		
		cltGameMsgRequest_SummonMarketOrderList sendMsg( pSummonManager->m_siCurrentPage, pSummonManager->m_siKind, pSummonManager->m_siSelectList );

		if( pSummonManager->m_siKind > 0 || pSummonManager->m_siSelectList == 1 ) 
		{
			cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_ORDERLIST, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclClient->pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );
		}

		pSummonManager->m_siSelectList = 0;
	}	
}

void NSummonMarketBuyDlg::NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl )
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;
	// ����Ʈ ���
	CList *pList_summon = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CComboBox *pComboBox_kind = (CComboBox*)m_pControlMap[ COMBOBOX_KIND ];
	if( pList_summon == NULL || pList_explain == NULL || pComboBox_kind == NULL ) return; 

	SI32 id = 1;

	CASE_CONTROL( LISTBOX_SUMMON )
	{
		switch( nEvent )
		{
		case EVENT_LISTBOX_SELECTION:
		{
			TCHAR *pchTmp = NULL;
			SI16 siRow = -1, siCol = -1;
			
			pList_summon->GetSelectedIndex( &siRow, &siCol );
			if( siRow == -1 || siCol == -1 ) return;
			stListBoxItemData *pstListBoxItemData = NULL;
			pstListBoxItemData = pList_summon->GetItemData( siRow, 0 );
			if( pstListBoxItemData == NULL ) return;
			pSummonManager->siSelectedIndex = pstListBoxItemData->siParam[0];	

			if( pSummonManager->siSelectedIndex >= 0 )
				ShowResponseExplain( );
		}
		break;
		default :
			{
				/*pSummonManager->siSelectedIndex = -1;
				pList_explain->Clear();
				pList_explain->Refresh();*/
			}
			break;
		}
	}
	//else CASE_CONTROL( LISTBOX_EXPLAIN )
	//{
	//	switch( nEvent )
	//	{
	//		case EVENT_LISTBOX_SELECTION:
	//		{
	//		}
	//		break;
	//	}
	//}
	else CASE_CONTROL( BUTTON_SELECTORDER )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				pSummonManager->m_siSelectList  =    1;
				pSummonManager->m_siCurrentPage    =    0;
				pSummonManager->bSelectedSwitch = true; 
				pSummonManager->siSelectedIndex =   -1;
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_FIRST )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				if(0 < pSummonManager->m_siCurrentPage)
				{
					pSummonManager->m_siSelectList  =    0;
					pSummonManager->bSelectedSwitch = true;
					pSummonManager->siSelectedIndex =   -1;
					pSummonManager->m_siCurrentPage--;
				}
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_NEXT )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				if(pSummonManager->m_siCurrentPage < pSummonManager->m_siTotalPageNum)
				{
					pSummonManager->m_siSelectList  =    0;
					pSummonManager->bSelectedSwitch = true;
					pSummonManager->siSelectedIndex =   -1;
					pSummonManager->m_siCurrentPage++;
				}
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_BUY )
	{
		switch( nEvent )
		{
		case EVENT_BUTTON_CLICKED:
			{
				TCHAR buf[ 256 ];

				if( pclClient->pclCM->CR[ id ]->pclCI->clIP.GetLevel() < LIMIT_LEVEL_HATCH_DOLL ) 
				{
					TCHAR* pText = GetTxtFromMgr(1753);
					StringCchPrintf( buf, 256, pText, LIMIT_LEVEL_HATCH_DOLL );
					SetMainExplain( buf );
					break;
				}

				if( pSummonManager->siSelectedIndex < 0 )
					break;

				if( pSummonManager->clResponseOrder[ pSummonManager->siSelectedIndex ].siPersonID == 0 )
					break;

				cltGameMsgRequest_SummonMarketBuy sendMsg( pSummonManager->clResponseOrder[ pSummonManager->siSelectedIndex ].siIndex );

				cltMsg clMsg( GAMEMSG_REQUEST_SUMMONMARKET_BUY, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclClient->pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

				//// ����!!
				//pSummonManager->bSelectedSwitch = true;
			}
			break;
		}
	}
	else CASE_CONTROL( BUTTON_REFRESH )
	{
		switch( nEvent )
		{
			case EVENT_BUTTON_CLICKED:
				{	
					pSummonManager->m_siSelectList  =    0;
					pSummonManager->m_siCurrentPage =    0;
					pSummonManager->bSelectedSwitch = true;
					pSummonManager->siSelectedIndex =   -1;
				}
				break;
		}
	}
	else CASE_CONTROL( RADIOBUTTON_SUMMON )
	{
		AddSummonKind();
	}
	else CASE_CONTROL( RADIOBUTTON_SUMMON_PET )
	{
		AddSummonKind();		
	}
	else CASE_CONTROL( RADIOBUTTON_SUMMON_BOSS )
	{
		AddSummonKind();		
	}
	else CASE_CONTROL( COMBOBOX_KIND )
	{
		switch( nEvent )
		{
		case EVENT_COMBOBOX_SELECTION_CHANGED:
			{
				SI32 index = pComboBox_kind->GetSelectedIndex();

				if ( index > -1 )
				{
					TCHAR strMonsterName[ 128 ] = TEXT("");
					TCHAR* pchTmp = NULL;
					pchTmp = pComboBox_kind->GetText( index );
					if(pchTmp == NULL ) return;
					if( _tcslen( pchTmp ) >= 128 ) return;
					_tcscpy( strMonsterName, pchTmp );

					pSummonManager->m_siKind = pclClient->pclKindInfoSet->FindKindFromName( strMonsterName );

					pSummonManager->m_siSelectList  = 0;
					pSummonManager->m_siCurrentPage    = 0;
					pSummonManager->bSelectedSwitch = true;

					// �޺� �ڽ��� ��ȯ���� ���õǸ� �ʻ�ȭ ��ƨ.
					TCHAR szPortrait[256];
					SI32 siPortraitFont;  
					pclClient->pclKindInfoSet->GetNPCImageFileAndFont(pSummonManager->m_siKind, szPortrait, sizeof(szPortrait), &siPortraitFont);
					
					CImageStatic* pImageStatic_portrait = (CImageStatic*)m_pControlMap[ IMAGESTATIC_PORTRAIT ];
					if(NULL == pImageStatic_portrait)
						return;

					pImageStatic_portrait->SetFileName( szPortrait );
					pImageStatic_portrait->SetFontIndex( siPortraitFont );
				}
			}
			break;
		}
	}

}

void NSummonMarketBuyDlg::ShowResponseOrder( )
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL )
		return;
	// ����Ʈ ���
	CList *pList_summon		  = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain	  = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CComboBox *pComboBox_kind = (CComboBox*)m_pControlMap[ COMBOBOX_KIND ];
	if( pList_summon == NULL || pList_explain == NULL || pComboBox_kind == NULL ) return; 

	int i;
	TCHAR buffer[256 ];
	TCHAR pricestring[64];

	// ������ ����Ʈ�� �����Ѵ�. 
	pList_summon->Clear();
	pList_summon->Refresh();


	bool bcheck[MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER];
	for( i = 0; i < MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER; i++ )
	{
		bcheck[i] = false;
	}

	SI32 addnum = 0 ;
	while(addnum < pSummonManager->siTotalResponseOrderNumber)
	{
		GMONEY	minprice = MAX_TRADE_MONEY;
		SI32	minindex = -1;	

		for( i = 0; i < pSummonManager->siTotalResponseOrderNumber; i++ )
		{
			if( bcheck[i] == false && pSummonManager->clResponseOrder[i].siPrice <= minprice)
			{
				minprice	= pSummonManager->clResponseOrder[i].siPrice;
				minindex	= i;
			}
		}
		
		if(minindex >= 0)
		{
			bcheck[minindex] = true;

			int len = _tcslen( pSummonManager->clResponseOrder[minindex].clSummon.szName );
			
			cltKindInfo* pclki = NULL;
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[pSummonManager->clResponseOrder[minindex].clSummon.siKind];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[pSummonManager->clResponseOrder[minindex].clSummon.siKind ];
			}

			if( len > 0 ) 
			{
				StringCchPrintf( buffer, 256, TEXT("[%s]%s"), 
					(TCHAR*)pclki->GetName(),
					pSummonManager->clResponseOrder[minindex].clSummon.szName );
			} 
			else 
			{
				TCHAR* pText = GetTxtFromMgr(1781);
				StringCchPrintf( buffer, 256, pText,
					(TCHAR*)pclki->GetName() );
			}

			// ��ȯ��
			stListBoxItemData stTmpListBoxItemData;
			stTmpListBoxItemData.Init();
			stTmpListBoxItemData.Set( 0, buffer );
			stTmpListBoxItemData.siParam[0] = minindex;
			// ���� 
			TCHAR* pText = GetTxtFromMgr(611);
			g_JYLibFunction.SetNumUnit(pSummonManager->clResponseOrder[minindex].siPrice, pricestring, 64, pText);

			//stTmpListBoxItemData.Init();
			stTmpListBoxItemData.Set( 1, pricestring );
			pList_summon->AddItem( &stTmpListBoxItemData );

			addnum++;
		}
	}
	
	pList_summon->Refresh();
	pSummonManager->siSelectedIndex = -1;
}

void NSummonMarketBuyDlg::ShowResponseExplain()
{

	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;
	// ����Ʈ ���
	CList *pList_summon		  = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain	  = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CList *pList_ability	  = (CList*)m_pControlMap[ LISTBOX_ABILITY_INFO ];
	CComboBox *pComboBox_kind = (CComboBox*)m_pControlMap[ COMBOBOX_KIND ];
	if( pList_summon   == NULL || pList_explain == NULL || 
		pComboBox_kind == NULL || pList_ability == NULL		) 
		return; 

	TCHAR buffer[256];

	pList_explain->Clear();
	pList_explain->Refresh();
	pList_ability->Clear();
	pList_ability->Refresh();

	TCHAR* pText[16];

	pText[0]  = GetTxtFromMgr(1782);
	pText[1]  = GetTxtFromMgr(1556);
	pText[2]  = GetTxtFromMgr(1506);
	pText[3]  = GetTxtFromMgr(1319);
	pText[4]  = GetTxtFromMgr(1783);
	pText[5]  = GetTxtFromMgr(1784);
	pText[6]  = GetTxtFromMgr(1785);
	pText[7]  = GetTxtFromMgr(1786);
	pText[8]  = GetTxtFromMgr(1787);
	pText[9]  = GetTxtFromMgr(1788);
	pText[10] = GetTxtFromMgr(1789);
	pText[11] = GetTxtFromMgr(1790);
	pText[12] = GetTxtFromMgr(1791);
	pText[13] = GetTxtFromMgr(8594);
	pText[14] = GetTxtFromMgr(8607);
	pText[15] = GetTxtFromMgr(8608);

	if( pSummonManager->siSelectedIndex < 0 ) 
		return;

	cltSummon *pclSummon = &(pSummonManager->clResponseOrder[ pSummonManager->siSelectedIndex ].clSummon);

	stListBoxItemData stTmpListBoxItemData;
	// ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 0 ] );
	
	cltKindInfo* pclki = NULL;
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclki = pclClient->pclKindInfoSet->pclSummonKI[pclSummon->siKind];
	}
	else
	{
		pclki = pclClient->pclKindInfoSet->pclKI[pclSummon->siKind];
	}

	stTmpListBoxItemData.Set( 1, (TCHAR*)pclki->GetName() );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// �̸�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 1 ] );
	stTmpListBoxItemData.Set( 1, pclSummon->szName );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// ����
	_itot( pclSummon->clIP.GetLevel(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 2 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// ����ġ
	
	_i64tot( pclSummon->clIP.GetCurExp(), buffer, 10 );// SI32->SI64 ����ġ �����÷ο춧���� ����
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 3 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// ü��
	
	_itot( pclSummon->clIP.GetLife(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[4  ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// ������

	_itot( pclSummon->clIP.GetMana(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 5 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// ���׹̳�
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 13 ] );

	// [����] : ATB_SUMMONSTAMINASTATIC�� ������ �⺻ ��ȯ�� ���¹̳ʰ��ҷ��� �����Ų��. (08.07.18)
	SI32 amt = 0;
	if (pclki->IsAtb(ATB_SUMMONSTAMINASTATIC) == TRUE )
	{
		amt = SUMMON_DECREASESTAMINA_AMT;
	}
	else
	{
		// �Ҹ�Ǵ� ���¹̳��� ���� ���Ѵ�.
		amt =  SUMMON_DECREASESTAMINA_AMT - (pclki->siSummonRank / 5) ;

		// �Ҹ�Ǵ� ���¹̳��� ���� 0���� �۾� ���� 1�� ������Ų��.
		if(amt <= 0) { amt = 1; }
	}

	StringCchPrintf(buffer, sizeof(buffer), GetTxtFromMgr(1252), pclSummon->clIP.GetLuk() / amt);  
	stTmpListBoxItemData.Set( 1, buffer );
	pList_explain->AddItem( &stTmpListBoxItemData );

	// �ٷ�
	_itot( pclSummon->clIP.GetStr(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 6 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// ���߷�

	_itot( pclSummon->clIP.GetDex(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 7 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// ����

	_itot( pclSummon->clIP.GetMag(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 8 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// �����
	_itot( pclSummon->clIP.GetVit(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 9] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// ���ʽ�
	_itot( pclSummon->clIP.GetBonus(), buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 10 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siAttackWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 14 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	// ���뼮
	_itot( pclSummon->siDefenseWearStoneNum, buffer, 10 );
	stTmpListBoxItemData.Init();
	stTmpListBoxItemData.Set( 0, pText[ 15 ] );
	stTmpListBoxItemData.Set( 1, buffer );
	pList_ability->AddItem( &stTmpListBoxItemData );

	SI32 i = 0;
	// ����
	/*for( i = 0; i < 2; ++i )
	{
		stTmpListBoxItemData.Init();
		stTmpListBoxItemData.Set( 0, pText[ 11 + i ] );
		if( pclSummon->clScroll.siUnique[i] )
		{
			stTmpListBoxItemData.Set( 0, (TCHAR *)pclClient->pclItemManager->GetName( pclSummon->clScroll.siUnique[i] ) );

			StringCchPrintf( buffer, 256, TEXT("%0.1f%%"), (float)(pclSummon->clScroll.siPercent[i] / 10.0));
			stTmpListBoxItemData.Set( 1, buffer );
		}
		else
		{
			stTmpListBoxItemData.Set( 0, TEXT("") );
			stTmpListBoxItemData.Set( 1, TEXT("") );
		}

		pList_explain->AddItem( &stTmpListBoxItemData );
	}*/

	pList_explain->Refresh();
	pList_ability->Refresh();

	DrawSummonPortrait();
}

void NSummonMarketBuyDlg::DrawSummonPortrait()
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	// ����Ʈ ���
	CList *pList_summon					= (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList *pList_explain				= (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CComboBox *pComboBox_kind			= (CComboBox*)m_pControlMap[ COMBOBOX_KIND ];
	CImageStatic *pImageStatic_portrait = (CImageStatic*)m_pControlMap[ IMAGESTATIC_PORTRAIT ];

	if( pList_summon == NULL || pList_explain == NULL || pImageStatic_portrait == NULL ) 
		return; 

	if( pSummonManager->siSelectedIndex < 0 ) 
		return;

	cltSummon *pclSummon = &(pSummonManager->clResponseOrder[ pSummonManager->siSelectedIndex ].clSummon);

	SI32 siSummonKind = pclSummon->siKind;

	if( siSummonKind == 0 ) 
		return;

	if( pSummonManager->m_siPortraitSummonKind != siSummonKind ) 
	{
		TCHAR strFileName[ MAX_PATH ] = TEXT("");

		SI16 tmpSelectedIndex = siSummonKind;

		TCHAR szPortrait[256];
		SI32 siPortraitFont;
		pclClient->pclKindInfoSet->GetNPCImageFileAndFont(tmpSelectedIndex, szPortrait, sizeof(szPortrait), &siPortraitFont);
		pImageStatic_portrait->SetFileName( szPortrait );
		pImageStatic_portrait->SetFontIndex( siPortraitFont );

		pSummonManager->m_siPortraitSummonKind = siSummonKind;
	}
}

void NSummonMarketBuyDlg::AddSummonKind() 
{
	// �忹�� �Ŵ���
	cltSummonMarketManager *pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) return;
	// ����Ʈ ���
	CList*			pList_summon		  = (CList*)m_pControlMap[ LISTBOX_SUMMON ];
	CList*			pList_explain		  = (CList*)m_pControlMap[ LISTBOX_EXPLAIN ];
	CComboBox*		pComboBox_kind		  = (CComboBox*)m_pControlMap[ COMBOBOX_KIND ];
	CImageStatic*	pImageStatic_portrait = (CImageStatic*)m_pControlMap[ IMAGESTATIC_PORTRAIT ];
	if( pList_summon == NULL || pList_explain == NULL || pImageStatic_portrait == NULL ) 
		return; 

	pComboBox_kind->Clear();

	cltKindInfo* pclki = NULL;

	for ( SI32 j = 1 ; j < MAX_KIND_NUMBER ; j ++ )
	{
		for ( SI32 i = 10; i < MAX_KIND_NUMBER ; ++i )
		{
			if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
			{
				pclki = pclClient->pclKindInfoSet->pclSummonKI[i];
			}
			else
			{
				pclki = pclClient->pclKindInfoSet->pclKI[i];
			}

			CRadioButton* pList_summon		= (CRadioButton*)m_pControlMap[ RADIOBUTTON_SUMMON ];
			CRadioButton* pList_summon_pet	= (CRadioButton*)m_pControlMap[ RADIOBUTTON_SUMMON_PET ];
			CRadioButton* pList_summon_boss	= (CRadioButton*)m_pControlMap[ RADIOBUTTON_SUMMON_BOSS ];
			if(NULL == pList_summon)
				return;
			if(true == pList_summon->IsCheck())
			{
				// ��ȯ�� ����Ʈ �߰� �������� ��.
				if( pclki == NULL || pclki->siSummonRank == 0 ) 
					continue;

				if(pclki->bSummonMall == TRUE)
					continue;

				if(99 <= pclki->siEvolveLevel)
					continue;
			}
			if(true == pList_summon_pet->IsCheck())
			{
				// ��ȯ�� ����Ʈ �߰� �������� ��.
				if( pclki == NULL || pclki->siSummonRank == 0 ) 
					continue;
				
				if(99 > pclki->siEvolveLevel || 99 < pclki->siEvolveLevel)
					continue;
			}
			if(true == pList_summon_boss->IsCheck())
			{
				if( pclki == NULL || pclki->siSummonRank == 0 ) 
					continue;

				if(100 > pclki->siEvolveLevel)
					continue;
			}
			

			if ( pclki->siSortLevel <= 0 || pclki->siSortLevel >= MAX_SORT_LEVEL )
				continue;

			if ( pclki->siSortLevel == j )
			{
				TCHAR* pname = (TCHAR*)pclki->GetName();
				stComboBoxItemData stTmpComboBoxItemData;
				stTmpComboBoxItemData.Init();
				stTmpComboBoxItemData.Set( pname );
				pComboBox_kind->AddItem( &stTmpComboBoxItemData );
				break ;
			}
		}
	}

	pComboBox_kind->Refresh();

	return;
}

void NSummonMarketBuyDlg::Refresh(void) 
{
	cltSummonMarketManager* pSummonManager = ((cltSummonMarketManager *)m_pStrManager);
	if( pSummonManager == NULL ) 
		return;

	pSummonManager->m_siSelectList  =    0;
	pSummonManager->m_siCurrentPage   =    0;
	pSummonManager->bSelectedSwitch = true;
	pSummonManager->siSelectedIndex =   -1;
}