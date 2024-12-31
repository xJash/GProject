#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-RealEstateMarket.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\Msg\MsgType-RealEstateMarket.h"
#include "../CommonLogic/House/House.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_MYORDER(cltMsg* pclMsg, SI32 id )
{

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_RealEstateMarketMyOrder sendMsg( id, personid );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);	

}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_RealEstateMarketCancelOrder *pclinfo = (cltGameMsgRequest_RealEstateMarketCancelOrder *)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	sDBRequest_RealEstateMarketCancelOrder sendMsg( id, personid, pclinfo->siVillageUnique, pclinfo->siHouseIndex );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgResponse_RealEstateMarketOrderList sendMsg;

	cltRealEstateOrder *pclOrder;
	int count = 0;

	sendMsg.usCount = 0;

	for( int i = 0; i < MAX_REALESTATEMARKET_ORDER_NUMBER; ++i ) {

		pclOrder = &pclRealEstateMarketManager->pclRealEstateOrder[ i ];
		
		if( pclOrder->siPersonID ) {
			++count; 

			sendMsg.clOrder[ sendMsg.usCount ].Set( pclOrder );
			++sendMsg.usCount;
		}

		if( sendMsg.usCount == MAX_REALESTATEMARKET_RESPONSE_ORDER_NUMBER ) break;

		if( count >= pclRealEstateMarketManager->siTotalOrderNumber ) break;
	}

	if( sendMsg.usCount > 0 ) {

		cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_ORDERLIST, sendMsg.GetTotalSize(), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_SELL(cltMsg* pclMsg, SI32 id )
{
	
	cltGameMsgRequest_RealEstateMarketSell *pclinfo = (cltGameMsgRequest_RealEstateMarketSell *)pclMsg->cData;

	GMONEY price = pclinfo->siPrice;
	SI32 tax = (SI32)(price * 0.01);

	if (pclCM->IsValidID(id) == false)
	{
		return;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	// ������ �������� �ش� ������ �����ϰ� �ִ°�?
	if( pclHouseManager->IsHouseHost( personid, pclinfo->siVillageUnique, pclinfo->siHouseIndex ) == FALSE ) {
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_SELL_NOTVALID,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	bool bHaveNotTradeItem = false;

	for (SI32 i = 0; i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; i++)
	{
		cltItem* pclitem = pclHouseManager->GetStgItemPointer(pclinfo->siVillageUnique, pclinfo->siHouseIndex, i);
		if(pclitem == NULL) continue;

		cltItemInfo* pcliteminfo = pclItemManager->FindItemInfo( pclitem->siUnique );
		if (pcliteminfo == NULL) continue;

		if ( pcliteminfo->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) || pclitem->IsBelonging(pclItemManager) )
		{
			bHaveNotTradeItem = true;
		}

	}
	if (bHaveNotTradeItem)
	{
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_SELL_HAVENOTRADE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	// �ŷ� �Ұ����� ���� �ִ��� üũ
	cltHouseUnitStorageInfo * pclHouseUnit = pclHouseManager->GetStgPointer(pclinfo->siVillageUnique , pclinfo->siHouseIndex);
	
	if( pclHouseUnit == NULL ) return;

	i = 0;
	for( i = 0; i < MAX_HOUSEUNIT_HORSENUMBER ; i ++ )
	{
		//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
		// PCK : ��Ÿ�߰� (08.03.06)
		// PCK : �̺�Ʈ�� ȣ���� �߰� (08.04.01)
		// PCK : �ڳ��� �߰� (08.06.12)
		// PCK : ��ȣ �߰� (08.08.14)
		// PCK : ������� �߰� (08.09.02)
		// PCK : ����ġ �߰� (08.12.10)
		// ü��� �鸶 : �ռ���-2009.03.17
		// PCK : ������Ʈ �߰� (09.07.30)
		switch ( pclHouseUnit->clHorse[i].siHorseUnique )
		{
			case HORSEUNIQUE_WOLF:
			case HORSEUNIQUE_FOAL:
			case HORSEUNIQUE_TIGER:
			case HORSEUNIQUE_CAMEL:
			case HORSEUNIQUE_TIGER2:
			case HORSEUNIQUE_ELEPHANT:
			case HORSEUNIQUE_WHITETIGER:
			case HORSEUNIQUE_MOTORCYCLE:
			case HORSEUNIQUE_FIREHATCH:
			case HORSEUNIQUE_WHITE_TEST:
			case HORSEUNIQUE_BAPHOMET:
			case HORSEUNIQUE_GRAYWOLF:
			case HORSEUNIQUE_SASURI:
				{
					SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_SELL_HAVENOTRADEHORSE,  0, 0, pclCM->CR[id]->GetCharUnique());
					return;
				}
				break;
		}	// switch ( pclHouseUnit->clHorse[i].siHorseUnique ) ����
	}
	



	if (pclCM->CR[id]->pclCI->clBank.clAccountNum.IsValid() == false)
	{
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_SELL,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	cltRealEstateOrder clOrder;

	clOrder.siPersonID = personid;
	clOrder.siPrice = price;
	clOrder.clDate.Set( &pclTime->clDate );

	clOrder.siVillageUnique = pclinfo->siVillageUnique;
	clOrder.siHouseIndex = pclinfo->siHouseIndex;

	sDBRequest_RealEstateMarketOrderSell sendMsg( id, villageunique, &clOrder, tax );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	pclDelMoneyStatistics->Add(DELMONEY_TAX, tax);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_BUY(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_RealEstateMarketBuy *pclinfo = (cltGameMsgRequest_RealEstateMarketBuy *)pclMsg->cData;

	GMONEY price = 0;
	SI32 orderindex = 0;
	SI32 housevillage = 0;
	SI32 houseindex = 0;
	

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	if( pclCM->CR[ id ]->pclCI->clIP.GetLevel() < MIN_LEVEL_FOR_HORSE ) return;

	// ������ �� ������ �� �ִ°� 3�� �̻� ������ �� ����
	if( pclCM->CR[ id ]->pclCI->clRealEstate.GetRealEstateNum() == 3 ) {
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_BUY_NOMORE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	int count = 0;
	for( int i = 0; i < MAX_REALESTATEMARKET_ORDER_NUMBER; ++i ) {
		if( pclRealEstateMarketManager->pclRealEstateOrder[ i ].siPersonID != 0 ) {
			++count;

			if( pclRealEstateMarketManager->pclRealEstateOrder[ i ].siIndex == 
				pclinfo->siOrderIndex ) {

				if( pclRealEstateMarketManager->pclRealEstateOrder[ i ].siPersonID == personid ) {
					SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_BUY_NOTSELF,  0, 0, pclCM->CR[id]->GetCharUnique());
					return;
				}

				orderindex = pclRealEstateMarketManager->pclRealEstateOrder[ i ].siIndex;
				housevillage = pclRealEstateMarketManager->pclRealEstateOrder[ i ].siVillageUnique;
				houseindex = pclRealEstateMarketManager->pclRealEstateOrder[ i ].siHouseIndex;
				price = pclRealEstateMarketManager->pclRealEstateOrder[ i ].siPrice;

				sDBRequest_RealEstateMarketBuy sendMsg( id, personid, villageunique, orderindex, housevillage, houseindex, price );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
				
				return;
			}
		}

		if( count >= pclRealEstateMarketManager->siTotalOrderNumber ) break;
	}

	SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_BUY_NOTVALID,  0, 0, pclCM->CR[id]->GetCharUnique());
}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_SETFEE(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_RealEstateMarketSetFee *pclinfo = (cltGameMsgRequest_RealEstateMarketSetFee *)pclMsg->cData;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;
	
	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = &pclinfo->clFee;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;
	
	//----------------------------------
	// ��û�ڰ� �Ű�������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_REALESTATEMARKET, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_FAIL_SETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	sDBRequest_RealEstateMarketSetFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_REALESTATEMARKET_DETAILINFO(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_RealEstateMarketDetailInfo *pclinfo = (cltGameMsgRequest_RealEstateMarketDetailInfo *)pclMsg->cData;

	if( pclinfo->siVillageUnique < 0 || pclinfo->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	cltGameMsgResponse_RealEstateMarketDetailInfo sendMsg;

	cltHouse *pclHouse = (cltHouse *)pclHouseManager->pclStruct[ pclinfo->siVillageUnique ];
	if( pclHouse == NULL ) return;
	
	cltHouseUnit *pclHouseUnit = pclHouse->GetHouseUnit( pclinfo->siHouseIndex );
	if( pclHouseUnit == NULL ) return;
	
	sendMsg.siVillageUnique = pclinfo->siVillageUnique;
	sendMsg.siHouseIndex = pclinfo->siHouseIndex;

	cltStrInfo *pStrInfo = GetStrInfo( pclinfo->siVillageUnique, RANKTYPE_HOUSE );
	if( pStrInfo == NULL ) return;

	sendMsg.siCurrentRentFee = pStrInfo->clHouseStrInfo.clRentContract.siRentFee;
	sendMsg.siRentFee = pclHouseUnit->clContract.siRentFee;			// ���Ӵ��
	sendMsg.siRentPeriod = pclHouseUnit->clContract.siRentPeriod;	// �Ӵ�Ⱓ
	sendMsg.clContractDate.Set( &pclHouseUnit->clContract.clDate );	// ����Ͻ�

	sendMsg.siItemNum = pclHouseUnit->GetItemNum();
	sendMsg.siStableNum = pclHouseUnit->GetStableNum();
	if( sendMsg.siStableNum == 0 ) {
		sendMsg.siHorseNum = 0;
	}
	else {
		sendMsg.siHorseNum = pclHouseUnit->GetHorseNum();
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_DETAILINFO, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}
