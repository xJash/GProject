//---------------------------------
// 2003/6/3 ���°�
//---------------------------------
#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"

//-----------------------------
// Common
//-----------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "Stock.h"


#include "MsgType-Stock.h"

#include "..\..\Resource.h"

#include "../../CommonLogic/MsgType-Structure.h"

#include "../CityHall/TaxpaymentListDlg.h"
#include "../Server/Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Stock.h"
#include "..\..\Client\Music\Music.h"

extern cltCommonLogic* pclClient;


cltStockManager::cltStockManager(cltCharManager* pclcm, SI32 gamemode, SI32 ranktype, TCHAR *strFileName ) 
: cltStructureMngBasic(MAX_STOCK_TAB_NUMBER, pclcm, ranktype, strFileName )
{

	bInitBuyOrder = FALSE;
	bInitSellOrder = FALSE;

	bBidding = FALSE;

	UpdateStockBidVillageSwitch = FALSE;
    UpdateStockBidderSwitch = FALSE;
	UpdateInvestSwitch = FALSE;

	UpdateStockOfferingInfoSwitch = FALSE;
	ZeroMemory( &clStockOfferingInfo, sizeof(clStockOfferingInfo) );


	// ���� ���� ����Ʈ�� �ʱ�ȭ �Ѵ� 
	InitStockBidVillage();

	// ���� �������� ������ ����Ʈ�� �ʱ�ȭ �Ѵ� 
	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {
		InitStockBidder( i );
	}

	tickTemp = GetTickCount();

	// ����, ���� �ֹ��� �ʱ�ȭ�Ѵ�. 
	pclOrderManager = NULL;

	if(gamemode == GAMEMODE_SERVER)
	{
		pclOrderManager	= new cltStockOrderManager;
		//pclAcountManager	= new cltStockAcountManager;
	}

	//siMostOrderMode	= ORDERMODE_SELL;
	//clMostOrder.Init();

	memset( &clSellMostOrder[0], 0, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
	memset( &clBuyMostOrder[0], 0, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );

}


cltStockManager::~cltStockManager()
{

/*	if(pclAcountManager)
	{
		delete pclAcountManager;
		pclAcountManager = NULL;
	}
*/

	if(pclOrderManager)
	{
		delete pclOrderManager;
		pclOrderManager = NULL;
	}


}

// ���� ȯ�� �λ縻ǥ��..
void cltStockManager::GreetingMsg(HWND hDlg)
{
	TCHAR* pText = GetTxtFromMgr(1499);
	SetMainExplain(hDlg, pText);
}

void cltStockManager::Do_WM_INITDIALOG(SI32 charunique)
{
	cltStructureMngBasic::Do_WM_INITDIALOG(charunique);
	
}


// ������ �ż��Ѵ�.
SI32 cltStockManager::CreateStock(SI32 siunique)
{
	if(pclStruct[siunique] == NULL)
	{
		pclStruct[siunique] = new cltStockMarket(siunique);
		return siunique;
	}
	
	return 0;
}

// ���� �ֽ��� ǥ���Ѵ�. 
void cltStockManager::SetHaveStock(HWND hDlg)
{
	SI32 i;
	TCHAR buffer[256];

	SI32 id = 1;
	if(id==0)return ;

	// ������ ���ŵ� ���¿����� ������Ʈ �Ѵ�. 
	if(pclCM->CR[id]->pclCI->clStock.clInfo.IsSame(&clOldStockInfo) == true)return ;
	clOldStockInfo.Set(&pclCM->CR[id]->pclCI->clStock.clInfo);

	
	// ����Ʈ �ڽ��� �ʱ�ȭ�Ѵ�. 
	SendDlgItemMessage(hDlg, IDC_LIST_HAVESTOCK, LB_RESETCONTENT, 0, 0);

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		SI32 villageunique	= pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siVillageUnique;
		SI32 amount			= pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siAmount;
	
		if(villageunique)
		{
			if(villageunique >=0)
			{
				TCHAR* pText = GetTxtFromMgr(1500);
				StringCchPrintf(buffer, 256, pText,pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName, amount); 
				SendDlgItemMessage(hDlg, IDC_LIST_HAVESTOCK, LB_ADDSTRING, 0, (LPARAM)buffer);
			}
			else
			{
				MsgBox(TEXT("fds09f82j"), TEXT("fdo9873:%d"), villageunique);
			}
		}
	}

}

// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
void cltStockManager::SetStockOrderList(HWND hDlg)
{
	SI32 i;
	TCHAR buffer[256];

	// ����Ʈ �ڽ��� �ʱ�ȭ�Ѵ�. 
	SendDlgItemMessage(hDlg, IDC_LIST_STOCKORDERINFO, LB_RESETCONTENT, 0, 0);

	SI32 id = 1;
	if(id <= 0)return ;

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
				if(ordermode == ORDERMODE_SELL)
				{
					TCHAR* pText = GetTxtFromMgr(1501);
					StringCchPrintf(buffer, 256, pText,pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName, amount, price); 
				}
				else
				{
					TCHAR* pText = GetTxtFromMgr(1502);
					StringCchPrintf(buffer, 256, pText,pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName, amount, price); 
				}
				
				SendDlgItemMessage(hDlg, IDC_LIST_STOCKORDERINFO, LB_ADDSTRING, 0, (LPARAM)buffer);
			}
			else
			{
				MsgBox(TEXT("fds2309f82j"), TEXT("fdfdo9873:%d"), villageunique);
			}
		}
	}

}

void cltStockManager::SetComboBuyKind(HWND hDlg)
{
	SI32 i;

	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclClient->pclVillageManager->pclVillageInfo[i])
		{
			SendDlgItemMessage(hDlg, IDC_COMBO_BUYSTOCK_KIND, CB_ADDSTRING, 0, (LPARAM)pclClient->pclVillageManager->pclVillageInfo[i]->szName);
		}
	}

}

// �ŵ� ������ �޺� �ڽ��� �߰��Ѵ�. 
void cltStockManager::SetComboSellKind(HWND hDlg)
{
	SI32 i;

	SI32 id = 1;
	if(id == 0)return ;

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		SI32 villageunique = pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siVillageUnique;
		if(villageunique)
		{
			if(villageunique >= 0)
			{
				SendDlgItemMessage(hDlg, IDC_COMBO_SELLSTOCK_KIND, CB_ADDSTRING, 0, (LPARAM)pclClient->pclVillageManager->pclVillageInfo[villageunique]->szName);
			}
		}
	}

}

// ������ �ֽ� ���� ���� ���� �ֹ��� �����Ѵ�.
void cltStockManager::SetMostOrder(cltTradeOrder* pclSellOrder, cltTradeOrder* pclBuyOrder, GMONEY AverageSell , GMONEY AverageBuy )
{
#ifdef _SAFE_MEMORY
    clSellMostOrder.MemCpy(pclSellOrder);
	clBuyMostOrder.MemCpy(pclBuyOrder);
#else
	memcpy( clSellMostOrder, pclSellOrder, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
	memcpy( clBuyMostOrder, pclBuyOrder, sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
#endif	
	siAverageSellMoney = AverageSell;
	siAverageBuyMoney = AverageBuy;
}

void cltStockManager::ShowFeeInfo( HWND hDlg )
{
	TCHAR buffer[256];

	float feerate = (float)clClientStrInfo.clStockStrInfo.clFee.GetFeeRate() / 10;

	StringCchPrintf( buffer, 256, TEXT("%3.1f%%"), feerate);

	SetDlgItemText( hDlg, IDC_EDIT_STOCKFEERATE, buffer );
}


// �ֽ� ��ſ� ���� ó���� �ֱ������� �Ѵ�
void cltStockManager::Action(cltTime* pcltime)
{
	if(pcltime == NULL) return ;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( ((cltServer *)pclClient)->bCompleteDBInitAll == FALSE ) return;

	if( bInitBuyOrder == FALSE || bInitSellOrder == FALSE ) return;

	//----------------------------------------
	// 
	//----------------------------------------
	cltServer *pclServer = (cltServer *)pclClient;

	if( pclServer->GetFrame() % ( 40 * 60 ) == 0 ) 
	{
		SetBidItem();
	}

	
	if( pclServer->GetFrame() % ( 40 * 3 ) == 0 )
	{
		int i, j = 0;

		// ��� ���� ó��
		for( i = 1; i < MAX_VILLAGE_NUMBER; ++i )
		{
			if( clStockBidVillageInfo[ i ].siTottalIncreaseStockAmount_ > 0 )
			{
				cltDate clEndDate;


				clEndDate.Set( &clStockBidVillageInfo[ i ].clBiddingDate_ );
				clEndDate.AddMonth( 6 );

				// ���� ���� �ð��� ����ϸ�,
				if( clEndDate.GetHourVary() - ((cltServer *)pclClient)->pclTime->clDate.GetHourVary() <= 0 ) 
				{
					CompletionStockBidVillage( i );
				}
			}
		}
	}
}

void cltStockManager::SetBidItem()
{

	int i, j = 0;
	int orderamount[ MAX_VILLAGE_NUMBER ];
	BOOL bSoldOut[ MAX_VILLAGE_NUMBER ];

	for( i = 0; i < MAX_VILLAGE_NUMBER; ++i ) {

		orderamount[ i ] = 0;
		bSoldOut[ i ] = TRUE;
	}

	for( i = 0; i < pclOrderManager->siMaxOrderNum; ++i )
	{
		// ���� �ֹ��� ��ȿ �ϴٸ�, ���� �� �ֹ������� ���� 
		if( pclOrderManager->pclOrderBuy[ i ]->IsValid() ) {

			orderamount[ pclOrderManager->pclOrderBuy[ i ]->GetVillageUnique() ] += 
				pclOrderManager->pclOrderBuy[ i ]->siAmount;
		}

		// �ý��� �ֹ��� ���� �ִ��� ���� 
		if( pclOrderManager->pclOrderSell[ i ]->IsValid() ) {


			if( pclOrderManager->pclOrderSell[ i ]->siPersonID == 0 ) {
				
				bSoldOut[ pclOrderManager->pclOrderSell[ i ]->GetVillageUnique() ] = FALSE;
			}
			
		}

	}

	//cltDate clDate;

	for( i = 1; i < MAX_VILLAGE_NUMBER; ++i ) {

		// ��ȿ�� ������ �ƴϸ�, skip
		if( pclClient->pclVillageManager->pclVillageInfo[i] == NULL ) continue;

		// ���� ���� �����̸�, skip
		if( clStockBidVillageInfo[i].siVillageUnique_ != NULL ) continue;

		if( bSoldOut[ i ] == TRUE /*&& orderamount[ i ] >= 10*/ ) {

			// ���� �ֽ� �� ���� 
			cltVillageInvestInfo* pInvestInfo = &pclClient->pclVillageManager->pclVillageInfo[i]->clVillageVary.clInvestInfo;		

			SI32 stockAmount = pInvestInfo->clInvestInfo[ 0 ].siStockNum;

			if( stockAmount == 0 ) continue;
			
			stockAmount = SI32 (stockAmount * 0.05);

			if( stockAmount < 20 ) stockAmount = 20;

			if( stockAmount > 500 ) stockAmount = 500;
			
/*			
			clDate.Set( &((cltServer *)pclClient)->pclTime->clDate );
			clDate.AddMonth( 3 );

			// �ֽ� ��� ���� 3���� ������ �Ҿ�����, �ٽ� ���� �� �� ����
			if( clStockBidderManager[ i ].clBiddingDate.IsLaterMonthThan( &clDate ) == FALSE ) continue;
*/
			cltStrInfo *pStrInfo = pclClient->pclCityHallManager->GetStrInfo( i );
			if(pStrInfo == NULL)continue;

			if( pStrInfo->clCityhallStrInfo.siBeginningPrice < 5000 ) pStrInfo->clCityhallStrInfo.siBeginningPrice = 5000;

			sDBRequest_SetStockBidVillage clMsg( i, stockAmount, &((cltServer *)pclClient)->pclTime->clDate, pStrInfo->clCityhallStrInfo.siBeginningPrice );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			bBidding = TRUE;
		}		

	}

}

void cltStockManager::InitStockBidVillage()
{
	for( int i = 0; i < MAX_VILLAGE_NUMBER; ++i ) {

		clStockBidVillageInfo[ i ].siVillageUnique_ = 0;
	}

	bBidding = FALSE;
}

void cltStockManager::InitStockBidder( SI32 villageUnique )
{
	if( villageUnique <= 0 || villageUnique >= MAX_VILLAGE_NUMBER ) return;

	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {

		clStockBidderManager[ villageUnique ].clStockBidder[ i ].clPerson.Init();
	}
}

void cltStockManager::InitClientStockBidder()
{
	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {

		clClientStockBidder[ i ].clPerson.Init();
	}
}

//void cltStockManager::SetStockBidVillage( SI32 villageUnique, cltDate *pclDate, SI32 stockAmount, SI32 beginningPrice )
//{
//	clStockBidVillageInfo[ villageUnique ].siVillageUnique_ = villageUnique;
//	clStockBidVillageInfo[ villageUnique ].clBiddingDate.Set( pclDate );
//	clStockBidVillageInfo[ villageUnique ].siStockAmount = stockAmount;
//	clStockBidVillageInfo[ villageUnique ].siBeginningPrice = beginningPrice;
//}
void cltStockManager::SetStockBidVillage( SI32 VillageUnique, SI32 TotalStockAmount, SI32 TottalIncreaseStockAmount, SI32 LeftIncreaseStockAmount, SI64 CurrentStockPrice, cltDate *pclDate )
{
	if( VillageUnique < 0 || VillageUnique >= MAX_VILLAGE_NUMBER )	return;

	clStockBidVillageInfo[ VillageUnique ].siVillageUnique_ = VillageUnique;
	clStockBidVillageInfo[ VillageUnique ].siTotalStockAmount_ = TotalStockAmount;
	clStockBidVillageInfo[ VillageUnique ].siTottalIncreaseStockAmount_ = TottalIncreaseStockAmount;
	clStockBidVillageInfo[ VillageUnique ].siLeftIncreaseStockAmount_ = LeftIncreaseStockAmount;
	clStockBidVillageInfo[ VillageUnique ].siCurrentStockPrice_ = CurrentStockPrice;
	clStockBidVillageInfo[ VillageUnique ].clBiddingDate_.Set( pclDate );
}


void cltStockManager::CompletionStockBidVillage( SI32 villageUnique )
{
	
	sDBRequest_CompleteStockBidVillage	clMsg( villageUnique );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	
}

// ������ �ֹ��� �����ϴµ� �׼��� ���Ѵ�. 
void cltStockManager::Action(bool bdaychangedswitch)
{
	SI32 i = 0;
	static SI32 stockorderindex	= 0;

	//----------------------------------------
	// ���� �ֹ� ������ �����Ѵ�.
	//----------------------------------------
/*	if(bdaychangedswitch)
	{
		// ��ü �ֹ��� �˻��Ͽ� ��¥�� ���� �ð� �̻� ����� �ֹ��� �����Ѵ�. 
		cltServer* pclserver = (cltServer* )pclClient;
		if(pclserver->pclTime)
		{
			
			SI32 curdate = pclserver->pclTime->clDate.GetDateVary();
			
			for(i = 0;i < pclOrderManager->siMaxOrderNum;i++)
			{
				cltTradeOrder clorder;
				clorder.Set(pclOrderManager->pclOrderBuy[i]);

				if(clorder.siPersonID <= 0)continue;

				if(clorder.siDate + 210 < curdate)	// 210�Ͽ� �ѹ��� 
				{
				
					// ����� �ֹ� ������ DB�� ������. 
					// ������ �� �̻� �������� ������, �����Ѵ�.
//					sDBRequest_ReduceOrderPrice clMsg(&clorder);
//					pclserver->SendDBMsg((sPacketHeader *)&clMsg);
				}
			}
		}
	}
	*/
}

