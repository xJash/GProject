//---------------------------------
// 2003/6/3 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "..\../../Server/AuthServer/AuthMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Stock.h"
#include "MsgType-Stock.h"
#include "MsgRval-Define.h"

#include "..\Common\StockDistributionMgr\StockDistributionMgr.h"
#include "..\Common\StockDistributionMgr\StockDistributionObj.h"

#include "..\CommonLogic\Cityhall\Cityhall.h"
#include "../Client/NStructureDlg/Cityhall/NCityhallDlg.h"

#include "MsgType-Structure.h"	// ���� �Ļ� ���� �޼��� ó��

// ������ ������ ��� �ֹ��� ��û�Ѵ�. (Ŭ���̾�Ʈ ����ڰ� ������ �� �ְ�. ) 
void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKORDERINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StockOrderInfo* pclInfo = (cltGameMsgRequest_StockOrderInfo*)pclMsg->cData;

	// �޽����� ��ȿ�� �˻�. 
	if(pclInfo->siVillageUnique <= 0 || pclInfo->siVillageUnique >= MAX_VILLAGE_NUMBER)return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0) return ;

	// ������ �ֹ��� ã�´�. 
	GMONEY price =0; 
	
	cltTradeOrder clOrder(personid, price, 1, 0, pclInfo->siVillageUnique);
	
	cltTradeOrder clSellMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];
	cltTradeOrder clBuyMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];

	GMONEY	siAverageSell = 0;
	GMONEY	siAverageBuy = 0;

	pclStockManager->pclOrderManager->GetMostSellBuyOrder(&clOrder, clSellMostOrderList, clBuyMostOrderList, &siAverageSell, &siAverageBuy);
	

	// ã�� �ֹ��� Ŭ���̾�Ʈ�� ������. 
	cltGameMsgResponse_StockOrderInfo clInfo( clSellMostOrderList, clBuyMostOrderList , siAverageSell , siAverageBuy );
	cltMsg clMsg(GAMEMSG_RESPONSE_STOCKORDERINFO, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELSTOCKORDER(cltMsg* pclMsg, SI32 id)
{
	// PersonID�� ���Ѵ�. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// �ֹ��� ����϶�� ��û�� DB�� ������.
	sDBRequest_CancelStockOrder clMsg(id, personid);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
}

// ���� �ֹ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_BUYSTOCK(cltMsg* pclMsg, SI32 id)
{
	cltTradeOrder* pclStockOrder = (cltTradeOrder*)pclMsg->cData;

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	// [����] �ʺ��� ���� : �ʺ��� ������ �ֽ��� �������
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == pclStockOrder->siVillageUnique )
		{
			return;
		}
	}
	// �ѹ��� �ֹ��� �� �ִ� ������ �ʰ��ϸ� ����. 
	if(pclStockOrder->siAmount > MAX_AMOUNT_PER_DEAL)return ;

	// PersonID�� ������Ʈ �Ѵ�.
	pclStockOrder->siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	// �ֹ� ��¥�� Ȯ���Ѵ�. 
	pclStockOrder->siDate = pclTime->clDate.GetDateVary();


	// Person�� �ֹ� ������ �������� Ȯ���Ѵ�. 
	if( pclCM->CR[id]->GetStockOrderNumber() >= MAX_ORDER_PER_PERSON)return ;

	//#if defined(_CITYHALL_BANKRUPTCY)
	// �ش� ������ �Ļ� ������ ���� �ֽ� ���� �ֹ��� �ø� �� ����.
	SI32 targetVillage = pclStockOrder->siVillageUnique;
	cltStrInfo *pTargetStrInfo = GetStrInfo( targetVillage, RANKTYPE_CITYHALL );
	if(pTargetStrInfo == NULL)return ;

	if( pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT )
	{
		// �ֽ� ���� ��� ������ �Ļ�����Դϴ�.. => ���� �ֹ� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( targetVillage,  pTargetStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}
	//#endif

	// �ֽ� �ż� �ֹ��� �ִ´�. 
	SI32 retval	= 0;
	cltTradeOrder* pclorder = pclStockManager->pclOrderManager->FindOpositeOrder(ORDERMODE_BUY, pclStockOrder);
	if(pclorder)
	{
		// ������ �ݴ� �ֹ��� ã�Ҵ�. 
		// �ŷ� ������ ���� ���� �����Ŀ� DB�� �뺸�Ѵ�. 

		// �ŷ� ����. (�� �ֹ���  ��� ����) 
		//GMONEY tradeprice		= (pclStockOrder->siPrice + pclorder->siPrice) / 2;


		//KHY - 1114 - '����' �ֹ��� �������� ����. - �۰ų� ���� �ֹ����� FindOpositeOrder �� ã��.
		//'�ż�'�ֹ��϶�, �ش� ������ '�ŵ��ֹ�����'�� '�ż��ֹ�����'���� ���� �ֽ��� �ִٸ� �� �ֽ��� '�ŵ��ֹ�����'���� ����Ѵ�.
		
		GMONEY tradeprice		= pclorder->siPrice;
		
		sDBRequest_TradeStock clMsg(id, ORDERMODE_BUY, villageunique, pclStockOrder, pclorder->siIndex, tradeprice);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	}
	else
	{
		// DB�� �ֹ� ���ۿ� ������ ���� ���� ��û�Ѵ�. 
		sDBRequest_OrderStock	clMsg(id, ORDERMODE_BUY, pclStockOrder);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SELLSTOCK(cltMsg* pclMsg, SI32 id)
{
	cltTradeOrder* pclStockOrder = (cltTradeOrder*)pclMsg->cData;

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	// [����] �ʺ��� ���� : �ʺ��� ������ �ֽ��� ������ �� ����
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == pclStockOrder->siVillageUnique )
		{
			return;
		}
	}

	// PersonID�� ������Ʈ �Ѵ�.
	pclStockOrder->siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	// �ֹ� ��¥�� Ȯ���Ѵ�. 
	pclStockOrder->siDate = pclTime->clDate.GetDateVary();

	// Person�� �ֹ� ������ �������� Ȯ���Ѵ�. 
	if( pclCM->CR[id]->GetStockOrderNumber() >= MAX_ORDER_PER_PERSON || pclStockOrder->siAmount <= 0 ) 
		return ;

	//[����] �ֽĸŵ��� �̹� �ŵ��� �ֽĿ��� �ŵ��� ������ �ֽĺ��� ���� �ֽ��� �ŵ���ϰ����� ���� ����. 2008-5-8
	//�ŵ� �ֽ��� ���� ���Ѵ�.
	SI32 OrderStockAmount = 0;
	for(SI32 Count = 0; Count < MAX_MARKET_ORDER_PER_PERSON; ++Count)
	{
		if(pclCM->CR[id]->pclCI->clStock.clOrderInfo.clOrderUnit[Count].clOrder.GetVillageUnique() == pclStockOrder->siVillageUnique)
		{
			OrderStockAmount += pclCM->CR[id]->pclCI->clStock.clOrderInfo.clOrderUnit[Count].clOrder.siAmount;
		}
	}

	//[����] �ŵ��� �ֽļ��� ��ü �ֽļ����� ���� �ŵ������� �ֽļ��� ����ϰ� �Ѵ�.
	if(pclStockOrder->siAmount > pclCM->CR[id]->pclCI->clStock.clInfo.GetStockAmount(pclStockOrder->siVillageUnique) - OrderStockAmount)
	{
		SendServerResponseMsg( 0, SRVAL_OVER_STOCK_ORDER, 0, 0, id );
		return;
	}
	
	// �ֹ� �ݾ��� �͹��� ������ ����. 21�� ���ϱ���
	if(pclStockOrder->siPrice <= 0 || pclStockOrder->siPrice > pclClient->GetGlobalValue("GV_StockTradeMoneyLimit") )
	{
		return ;
	}

	//#if defined(_CITYHALL_BANKRUPTCY)
	// �ش� ������ �Ļ� ������ ���� �ֽ� ���� �ֹ��� �ø� �� ����.
	SI32 targetVillage = pclStockOrder->siVillageUnique;
	cltStrInfo *pTargetStrInfo = GetStrInfo( targetVillage, RANKTYPE_CITYHALL );
	if(pTargetStrInfo == NULL)return ;

	if( pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT )
	{
		// �ֽ� ���� ��� ������ �Ļ�����Դϴ�.. => ���� �ֹ� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( targetVillage,  pTargetStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_STOCK_TRADE );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}
	//#endif

	// �ֽ� �ŵ� �ֹ��� �ִ´�. 
	SI32 orderref = -1;
	SI32 retval = 0;
	cltTradeOrder* pclorder = pclStockManager->pclOrderManager->FindOpositeOrder(ORDERMODE_SELL, pclStockOrder);
	if(pclorder)
	{
		// �ŷ� ������ ���� ���� �����Ŀ� DB�� �뺸�Ѵ�. 

		// �ŷ� ����. (�� �ֹ���  ��� ����) 
		//GMONEY tradeprice		= (pclStockOrder->siPrice + pclorder->siPrice) / 2;

		//KHY - 1114 - '����' �ֹ��� �������� ����. - ���ų� ���� �ֹ����� FindOpositeOrder �� ã��.
		//'�ŵ�'�ֹ��϶�, �ش� ������ '�ż��ֹ�����'�� '�ŵ��ֹ�����'���� ���� �ֽ��� �ִٸ� �� �ֽ��� '�ż��ֹ�����'���� ����Ѵ�. 
		GMONEY tradeprice		= pclorder->siPrice;

		sDBRequest_TradeStock clMsg(id, ORDERMODE_SELL, villageunique, pclStockOrder, pclorder->siIndex, tradeprice);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		// DB�� �ֹ� ���ۿ� ������ ���� ���� ��û�Ѵ�. 
		sDBRequest_OrderStock	clMsg(id, ORDERMODE_SELL, pclStockOrder);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETSTOCKFEE(cltMsg* pclMsg, SI32 id)
{

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = (cltFee*)pclMsg->cData;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;

	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_STOCK, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAILSETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	//-----------------------------------
	// DB�� ���� ������ ������. 
	//-----------------------------------
	// DB �� ������.

	sDBRequest_SetStockFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}


void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKBIDVILLAGELIST(cltMsg* pclMsg, SI32 id)
{

	int count = 0;

	cltGameMsgResponse_StockBidVillageList sendMsg;

	for( int i = 0; i < MAX_VILLAGE_NUMBER; ++i ) {

		//if( pclStockManager->clStockBidVillageInfo[ i ].siVillageUnique != 0 ) {
		if( pclStockManager->clStockBidVillageInfo[ i ].siVillageUnique_ != 0 ) {

			if( count >= 0 && count < MAX_VILLAGE_NUMBER)
			{
				sendMsg.clStockBidVillageInfo[ count ].Set( &pclStockManager->clStockBidVillageInfo[ i ] );
				count++;
			}
		}

	}

	if( count > 0 ) {

		sendMsg.usCount = count;

		// ���� ���� ����Ʈ�� �����Ѵ�
		cltMsg clMsg( GAMEMSG_RESPONSE_STOCKBIDVILLAGELIST, sendMsg.GetTotalSize(), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}


}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKBIDDERLIST(cltMsg* pclMsg, SI32 id)
{

	SI32 villageUnique = pclMsg->siData32[ 0 ];
	if( villageUnique < 0 || villageUnique >= MAX_VILLAGE_NUMBER )		return;

	cltGameMsgResponse_StockBidder sendMsg;

	UI16 count = 0;

	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {

		if( pclStockManager->clStockBidderManager[ villageUnique ].clStockBidder[ i ].clPerson.GetPersonID() ) {

			if( count >= 0 && count < MAX_STOCKBIDDER_INVILLAGE)
			{
				sendMsg.clStockBidder[ count ].Set( 
					&pclStockManager->clStockBidderManager[ villageUnique ].clStockBidder[ i ] );

				count++;
			}
		}
	}

	sendMsg.usCount = count;

	// ���� ���� ����Ʈ�� �����Ѵ�
	cltMsg clMsg( GAMEMSG_RESPONSE_STOCKBIDDERLIST, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BIDSTOCK(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgRequest_BidStock* pclInfo = (cltGameMsgRequest_BidStock*)pclMsg->cData;

	if( pclInfo->siVillageUnique == 0 ) return;

	if( pclInfo->siStockMoney < LIMIT_STOCKMONEY )
		return;

	cltStrInfo *pStrInfo = pclCityHallManager->GetStrInfo( pclInfo->siVillageUnique );

	if( pStrInfo == NULL ) return;

	cltStrInfo *pclStrInfo = pStrInfo;

	if( pclStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT )	
	{
		// ������ �Ļ�� �Դϴ�.. => ���� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( pclInfo->siVillageUnique,  pclStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_BIDSTOCK);
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	// DB��û
	sDBRequest_BidStock clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), pclInfo->siVillageUnique, pclInfo->siStockMoney, &pclTime->clDate );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
	// �����ֽļ��� ���� ������ �� 
	//	if( pclInfo->siAmount > pclStockManager->clStockBidVillageInfo[ pclInfo->siVillageUnique ].siStockAmount ) {
	//		return;
	//	}


	//	// ���۰� ���� ������ �� 
	//	if( pclInfo->clPrice.itMoney < pStrInfo->clCityhallStrInfo.siBeginningPrice ) {
	//		return;
	//	}

	//	// ���� �������� ���� �ݾ׺��� 10%�̻����� ��
	//	if( pclStockManager->clStockBidderManager[ pclInfo->siVillageUnique ].clStockBidder[0].clPerson.siPersonID )
	//	{
	//		if( pclInfo->clPrice.itMoney < pclStockManager->clStockBidderManager[ pclInfo->siVillageUnique ].clStockBidder[0].siPrice * 1.1 )
	//		{
	//			SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BIDDING_WRONGVALUE10,  0, 0, pclCM->CR[id]->GetCharUnique());
	//			return;
	//		}
	//	}



	/*	//------------------------------------------
	// �����Ḧ �����Ѵ�. 
	//------------------------------------------		
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	SI64 fee = 0;

	SI64 money = (SI64)(pclInfo->siAmount * pclInfo->clPrice.itMoney);

	cltStrInfo* pclinfo = pclStockManager->GetStrInfo( villageunique );

	if( pclinfo ) 
	{
	// DB��û
	sDBRequest_BidStock clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &pclTime->clDate );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	*/

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELBIDSTOCK(cltMsg* pclMsg, SI32 id)
{



}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKBIDDATE(cltMsg* pclMsg, SI32 id)
{
	SI32 villageUnique = pclMsg->siData32[ 0 ];

	if( villageUnique <= 0 || villageUnique >= MAX_VILLAGE_NUMBER) return;

	//cltGameMsgResponse_StockBidDate sendMsg( villageUnique, &pclStockManager->clStockBidVillageInfo[ villageUnique ].clBiddingDate );
	cltGameMsgResponse_StockBidDate sendMsg( villageUnique, &pclStockManager->clStockBidVillageInfo[ villageUnique ].clBiddingDate_ );
	cltMsg clMsg( GAMEMSG_RESPONSE_STOCKBIDDATE, sizeof( cltGameMsgResponse_StockBidDate ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKDISTRIBUTIONORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StockDistributionOrder *pclinfo = (cltGameMsgRequest_StockDistributionOrder*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)return ;

	// ���� 20 �̸��� ��� ���� �Ұ�
	if ( pclCM->CR[id]->pclCI->clIP.GetLevel() <  FATHER_LEVEL)
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1) return ;

	if ( pclinfo->siVillageUnique < 1 )
	{
		return;
	}

	CStockDistributionObj *pObj = pclStockDistributionMgr->GetStockDistributionObj( pclinfo->siVillageUnique, pclinfo->bVillageWarStockDistribution );

	if ( pObj == NULL )
	{
		// ���� ���� ���������� ����.
		SendServerResponseMsg(0, SRVAL_STOCK_FAIL_DISTRIBUTIONSTOP,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	if ( pclinfo->siAmount < 1 || pclinfo->siAmount > pObj->GetDistributionStockUnit() )
	{
		return;
	}

	// ���Ե� ��� �� �� ����. ( 20 �ֶ�� �������� �� 20�ָ� ��� �ȴ�. 19�ֵ� �� �� ���� ���� ������. )
	if ( pclinfo->siAmount != pObj->GetDistributionStockUnit() )
	{
		return;
	}

	if ( pObj->GetLeftDistributionStockNum() < 1 )
	{
		return;
	}

	if ( pclinfo->siAmount > pObj->GetLeftDistributionStockNum() )
	{
		pclinfo->siAmount = pObj->GetLeftDistributionStockNum();
	}

	GMONEY siStockPrice = pObj->GetDistributionStockPrice();
	if ( siStockPrice < 1 )
	{
		return;
	}
	GMONEY siBuyingPrice = pclinfo->siAmount * siStockPrice;

	// �� ����
	if ( pclCM->CR[id]->pclCI->clIP.GetMoney()  < siBuyingPrice )
	{
		return;
	}

	sDBRequest_StockDistributionOrder clMsg( 
		pclinfo->siVillageUnique,
		PersonID, 
		id, 
		pclinfo->siAmount,
		pObj->GetDistributionStockPrice(),
		pObj->IsVillageWarStockDistribution()
		);

	pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	
	pclDelMoneyStatistics->Add(DELMONEY_STOCK, siBuyingPrice);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BUYBIDSTOCK(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsAlive(id) == false)
		return ;

	cltGameMsgRequest_BuyBidStock *pclinfo = (cltGameMsgRequest_BuyBidStock*)pclMsg->cData;

	if( pclinfo == NULL )
		return;

	// ���� ����ũ üũ
	if( pclinfo->siVillageUnique_ <= 0 || pclinfo->siVillageUnique_ >= MAX_VILLAGE_NUMBER )
		return;

	if( pclinfo->siType_ < 0 || pclinfo->siType_ > 1 )
		return;

	if( pclinfo->siType_ == 0 )
	{
		cltDate clEndDate;

		clEndDate.Set( &pclStockManager->clStockBidVillageInfo[ pclinfo->siVillageUnique_ ].clBiddingDate_ );
		clEndDate.AddMonth( 3 );

		// ���� ���� �ð��� ����ϸ�,
		if( clEndDate.GetHourVary() - pclTime->clDate.GetHourVary() <= 0 ) 
			return;
	}
	else if( pclinfo->siType_ == 1 )
	{
		cltDate clEndDate;

		clEndDate.Set( &pclStockManager->clStockBidVillageInfo[ pclinfo->siVillageUnique_ ].clBiddingDate_ );
		clEndDate.AddMonth( 6 );

		// ���� ���� �ð��� ����ϸ�,
		if( clEndDate.GetHourVary() - pclTime->clDate.GetHourVary() <= 0 ) 
			return;
	}

	// ���� üũ
	if( pclinfo->siAmount_ <=0 )
	{
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BUY_BIDSTOCK_EXCEEDAMOUNT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	SI64 Price = 0; // ���� ����
	SI64 TotalPrice = 0;
	bool bBuySwitch = false;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();

	// �����϶�
	if( pclinfo->siType_ == 0 )
	{
		SI32 FindIndex = 0;

		for(SI32 i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
		{
			// ���ϴ� ������ ã����, 
			if(pclinfo->siVillageUnique_ == pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siVillageUnique)
			{
				FindIndex = i;
				break;
			}
		}

		if( pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[FindIndex].bBuySwitch == true )
		{
			SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BUY_BIDSTOCK_ALREADY,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}

		if( pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[FindIndex].siLimitBuyBidStockAmount < pclinfo->siAmount_ )
			return;

		Price = pclinfo->clPrice_.itMoney;// * 8 / 10;
		TotalPrice = Price * pclinfo->siAmount_ * 8 / 10;
		bBuySwitch = true;
	}
	else if( pclinfo->siType_ == 1)
	{
		Price = pclinfo->clPrice_.itMoney;
		TotalPrice = Price * pclinfo->siAmount_;
	}

	// ����� �� �ֽİ��� �� �����ݺ��� ������ üũ
	if( TotalPrice > pclCM->CR[id]->pclCI->clIP.GetMoney() )
	{
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BUY_BIDSTOCK_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	SI64 fee = TotalPrice / 10;

	sDBRequest_BuyBidStock clMsg(id, PersonID, pclinfo->siType_, pclinfo->siVillageUnique_, pclinfo->siAmount_, Price, TotalPrice, bBuySwitch, fee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_STOCK, TotalPrice);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MYSTOCKINFO(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsAlive(id) == false)
		return ;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();

	if( PersonID < 0 )
		return;

	sDBRequest_MyStockInfo clMsg(id, PersonID );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKOFFERINGINFO(cltMsg* pclMsg, SI32 id )
{
	
	cltGameMsgResponse_StockOfferingInfo sendMsg;

	for( int i = 0; i < MAX_VILLAGE_NUMBER; ++i )
	{
		sendMsg.clStockOfferingInfo[ i ].siVillageUnique = pclStockOfferingManager->clStockInfo[ i ].siVillageUnique;
		sendMsg.clStockOfferingInfo[ i ].siTotalOffering = pclStockOfferingManager->clStockInfo[ i ].siTotalOffering;
		sendMsg.clStockOfferingInfo[ i ].siStockAmount = pclStockOfferingManager->clStockInfo[ i ].siStockAmount;
		sendMsg.clStockOfferingInfo[ i ].siPrice = pclStockOfferingManager->clStockInfo[ i ].siPrice;
		sendMsg.clStockOfferingInfo[ i ].siStatus = pclStockOfferingManager->clStockInfo[ i ].siStatus;
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_STOCKOFFERINGINFO, sizeof( cltGameMsgResponse_StockOfferingInfo ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_STOCKOFFERINGORDER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StockOfferingOrder* pclinfo = (cltGameMsgRequest_StockOfferingOrder*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)
		return ;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();

	if( PersonID < 0 )
		return;

	cltCharServer* pclCharSever = (cltCharServer*)pclCM->CR[id];
	if(pclCharSever == NULL)			return;

	//SI32 villageunique = pclMsg->siData32[ 0 ];
	SI32 villageunique = pclinfo->siVillageUnique;

	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER ) {
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDER,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	if(pclStockOfferingManager->clStockInfo[ villageunique ].siStatus != 1 ) {
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	if(pclCM->CR[id]->pclCI->clIP.GetLevel() < 20)
	{
		SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDERLIMIT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	sDBRequest_StockOfferingOrder clMsg( id, villageunique, PersonID,
		pclStockOfferingManager->clStockInfo[ villageunique ].siStockAmount,
		pclStockOfferingManager->clStockInfo[ villageunique ].siPrice,
		pclCharSever->GetSession()->GetIP(),
		pclinfo->szPrivateIP, pclinfo->szMacAddress);

	
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EXCHANGESTOCK(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsAlive(id) == false)
		return ;

	cltGameMsgRequest_ExchangeStock *pclinfo = (cltGameMsgRequest_ExchangeStock*)pclMsg->cData;

    SI32 villageUnique = pclinfo->siVillageUnique;
	SI32 personID = pclCM->CR[id]->pclCI->GetPersonID();
	SI32 sellAmount = pclinfo->siSellAmount;
	SI32 bankType = pclinfo->siBankType;
	SI32 myStockAmount = 0;

	if( 0 >= villageUnique )
	{
		/// �������� �� �� �� ���� ����
		return;
	}

	bool haveStock = false;
	for( SI32 i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
	{
		if( villageUnique == pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siVillageUnique )
		{
			myStockAmount = pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[i].siAmount;
			haveStock = true;
			break;
		}
	}
	
	/// �ȷ��� �ϴ� �ֽ��� �ֽİ��� �� 2���� ������ �ǸŰ� �����ϴ�.

	if( false == haveStock )
	{
		/// �ֽ��� ����
		return;
	}

	if( sellAmount < 100 || ( 0 != sellAmount % 100 ) )
	{
		/// 100���Ϸδ� �� �� ����.
		return;
	}

	if( sellAmount > myStockAmount )
	{
		/// ������ �ִ� �ֽĺ��� ���� �� �� ����.
		return;
	}

	sDBRequest_ExchangeFromStock clMsg( id, personID, pclinfo->szSecondPassWord, villageUnique,
		                                              sellAmount, bankType, pclinfo->szBankAccount );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETBEGINNERVILLAGESTOCK( cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}

	SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( siPersonID < 0 )
	{
		return;
	}

	// �ʺ��� ������ �ֽ��� ���� �� �ִ� �����̾�� �Ѵ�
	if ( pclChar->pclCI->clIP.GetLevel() >= Const_BV_StockDividend_Level )
	{
		return;
	}

	// �ʺ��� ���� �ֹ��̾�� �Ѵ�.
	if ( pclChar->pclCI->clBI.siHomeVillage != Const_Beginner_Village )
	{
		return;
	}

	// �ʺ��� ������ �ֽ��� ������ �ȵȴ�
	for ( SI32 siCount=0; siCount<MAX_STOCK_KIND_IN_ACOUNT; siCount++)
	{
		SI32 siFindVillageUnique	= pclChar->pclCI->clStock.clInfo.clUnit[siCount].siVillageUnique;
		SI32 siFindStockAmount		= pclChar->pclCI->clStock.clInfo.clUnit[siCount].siAmount;

		if ( Const_Beginner_Village == siFindVillageUnique )
		{
			if ( siFindStockAmount > 0 )
			{
				return;
			}
			break;
		}
	}

	sDBRequest_GiveStock clMsg( id, siPersonID, Const_Beginner_Village, 10 );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}
