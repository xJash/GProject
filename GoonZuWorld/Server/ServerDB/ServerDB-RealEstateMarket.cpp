#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Letter\Letter.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-RealEstateMarket.h"


#include "Msg\MsgType-RealEstateMarket.h"
#include "MsgRval-Define.h"
#include "Statistics\Statistics.h"
#include "House/House.h"

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_GETMANYORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_RealEstateMarketGetManyOrder* pclMsg = (sDBResponse_RealEstateMarketGetManyOrder*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->usCount > GET_MANY_REALESTATEMARKET_ORDER_NUM )		pclMsg->usCount = GET_MANY_REALESTATEMARKET_ORDER_NUM;
	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for( i = 0; i < pclMsg->usCount; ++i )
	{
		pclRealEstateMarketManager->AddOrder( &pclMsg->clOrder[ i ] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_RealEstateMarketGetManyOrder"));
}


void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_ORDERSELL(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_RealEstateMarketOrderSell *pclMsg = (sDBResponse_RealEstateMarketOrderSell *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_REALESTATEMARKET_FAIL_SELL;

	switch( pclMsg->siResult ) {
	case 1:
		{			
			pclRealEstateMarketManager->AddOrder( &pclMsg->clOrder );

			// ���� ���� ������Ʈ 
			pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

			// �����ڱ� ������Ʈ 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_REALESTATEMARKET );
			if( pStrInfo ) {
				pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clRealEstateMarketMoney );
			}

			// Ŭ���̾�Ʈ�� �뺸 
			cltGameMsgResponse_RealEstateMarketSell sendMsg;
			sendMsg.clRealEstateOrder.Set( &pclMsg->clOrder );

			cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_SELL, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

			returnval = SRVAL_REALESTATEMARKET_SUCCESS_SELL;

		

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// TEMP LEEKH --------------------------------------------------------------
				// [�α��߰� : Ȳ���� 2007. 10. 11] // �ε��� �Ǹ� ���.
				// param2 == �ֹ���ȣ.
				// param3 == ����.
				// param4 == �Ǹ� �ϴ� �ε����� �ִ� ���� ����ũ.
				// param5 == �ǹ� �ε���.
				// pszParam1 ==  �ð�.
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
																			pclMsg->clOrder.clDate.uiYear,
																			pclMsg->clOrder.clDate.uiMonth,
																			pclMsg->clOrder.clDate.uiDay,
																			pclMsg->clOrder.clDate.uiHour,
																			pclMsg->clOrder.clDate.uiMinute );


				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_SELL_ORDER, 
												0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->siTax, pclMsg->siPersonMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												0, 
												pclMsg->clOrder.siIndex,  
												pclMsg->clOrder.siPrice, 
												pclMsg->clOrder.siVillageUnique, 
												pclMsg->clOrder.siHouseIndex, 
												pszCharParam1, NULL);
				// TEMP LEEKH --------------------------------------------------------------
			}
		}
		break;

	case 2:
		{
			returnval = SRVAL_REALESTATEMARKET_FAIL_SELL_NOTENOUGHMONEY;
		}
		break;
	}

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_MYORDER(sPacketHeader* pPacket)
{

	sDBResponse_RealEstateMarketMyOrder *pclMsg = (sDBResponse_RealEstateMarketMyOrder *)pPacket;
	
	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	if( pclMsg->siResult == 1 ) {

		cltGameMsgResponse_RealEstateMarketMyOrder sendMsg;

		if( pclMsg->usCount > MAX_REAL_ESTATE_NUMBER_PER_PERSON )	pclMsg->usCount = MAX_REAL_ESTATE_NUMBER_PER_PERSON;
		for( int i = 0; i < pclMsg->usCount; ++i ) {

			sendMsg.clMyOrder[ i ].Set( &pclMsg->clMyOrder[ i ] );
		}

		sendMsg.usCount = pclMsg->usCount;

		cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_MYORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

	} 

}

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_CANCELORDER(sPacketHeader* pPacket)
{

	SI32 returnval = 0;

	sDBResponse_RealEstateMarketCancelOrder *pclMsg = (sDBResponse_RealEstateMarketCancelOrder *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_REALESTATEMARKET_FAIL_CANCELORDER;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclRealEstateMarketManager->DelOrder( pclMsg->siOrderIndex );

			cltGameMsgResponse_RealEstateMarketCancelOrder sendMsg( pclMsg->siOrderIndex, pclMsg->siVillageUnique, pclMsg->siHouseIndex );
			cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_CANCELORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

			returnval = SRVAL_REALESTATEMARKET_SUCCESS_CANCELORDER;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 11] // �ε��� �Ǹ� ���.
				// param1 == ������ �ֹ� ��ȣ. 
				// param2 == �ε��� ��ȣ. 
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_SELL_ORDER_CANCEL, 
												0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siOrderIndex, pclMsg->siHouseIndex, 0, 0, 0,
												NULL, NULL);
			}			
		}
		break;

	} 

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_BUY(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_RealEstateMarketBuy *pclMsg = (sDBResponse_RealEstateMarketBuy *)pPacket;

	if( pclMsg->siHouseVillage < 0 || pclMsg->siHouseVillage >= MAX_VILLAGE_NUMBER )		return;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_REALESTATEMARKET_FAIL_BUY;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclRealEstateMarketManager->DelOrder( pclMsg->siOrderIndex );

			// �ε��� ���� ������Ʈ

			cltHouse *pclHouse = (cltHouse *)pclHouseManager->pclStruct[ pclMsg->siHouseVillage ];

			if( pclHouse == NULL ) break;

			cltHouseUnit *pclHouseUnit = pclHouse->GetHouseUnit( pclMsg->siHouseIndex );

			if( pclHouseUnit == NULL ) break;

			pclMsg->szPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

			pclHouseUnit->clPerson.Set( pclMsg->siPersonID, pclMsg->szPersonName );

			// �Ű� �ڱ� 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_REALESTATEMARKET );


			if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)	
			{

				//--------------------------------
				// �ε��� ���� ������Ʈ 
				//--------------------------------
				pclCM->CR[id]->pclCI->clRealEstate.Add( REALESTATE_TYPE_HOUSE,
					pclMsg->siHouseVillage, pclMsg->siHouseIndex, &pclHouseUnit->clContract );


				//--------------------------------
				// ���� ���� ������ ������Ʈ �Ѵ�. 
				//--------------------------------
				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siMoney );
				pclCM->CR[id]->SetUpdateSwitch( UPDATE_IP, true, 0 );

				//--------------------------------
				// Ŭ���̾�Ʈ�� ���� ��Ŷ ����
				//--------------------------------
				cltGameMsgResponse_RealEstateMarketBuy sendMsg( pclMsg->siOrderIndex, pclMsg->siHouseVillage, pclMsg->siHouseIndex, &pclHouseUnit->clContract );
				cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATEMARKET_BUY, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );
				
				
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// TEMP LEEKH --------------------------------------------------------------
					// [�α��߰� : Ȳ���� 2007. 10. 11] // �ε��� ���� ����.
					// param1		 == �ŷ� �ε��� ���� ��ȣ, 
					// param2		 == �� �Ӵ��.
					// param3		 == �Ӵ�Ⱓ.
					// pszCharparam1 == ���Խð�.
					TCHAR pszCharParam1[50] = {'\0', };					
					StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d"),	
																				sendMsg.clContract.clDate.uiYear,
																				sendMsg.clContract.clDate.uiMonth,
																				sendMsg.clContract.clDate.uiDay,
																				sendMsg.clContract.clDate.uiHour,
																				sendMsg.clContract.clDate.uiMinute );

					
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_BUY, 
													0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siSellerPersonID, pclMsg->siTradePrice, pclMsg->siMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
													pclMsg->siHouseIndex, sendMsg.clContract.siRentFee, sendMsg.clContract.siRentPeriod, 0, 0, 
													pszCharParam1, NULL);
					// TEMP LEEKH --------------------------------------------------------------
				}
			}


			//-----------------------------------------
			// ������ ����(���� �ܾ�, �ֹ� ���� )�� ������Ʈ �Ѵ�. 
			//-----------------------------------------
			SI32 sellerid = pclCM->GetIDFromPersonID( pclMsg->siSellerPersonID );
			GMONEY price	= pclMsg->siTradePrice;

			// �ε��� �ŷ� �Ǽ�. 
			pclStatisticsManager->clDailyStatistics.siRealEstateTradeNum++;
 
			// �ε��� �ŷ� �ݾ� ���� 
			pclStatisticsManager->clDailyStatistics.siRealEstateTradeMoney += price;


			//---------------------------------------------
			// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
			//--------------------------------------------
			// �����Ḧ Ȯ���Ѵ�. 
			cltStrInfo* pclstrinfo = pclRealEstateMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			if(pclstrinfo == NULL)return ;

			GMONEY fee = pclstrinfo->clRealEstateMarketStrInfo.clFee.CalcFee( price );

			if(fee)
			{
				cltMoney clmoney;
				clmoney.itMoney = fee;
				sDBRequest_PayFee clinfo(sellerid, pclMsg->siSellerPersonID, pclMsg->siVillageUnique, RANKTYPE_REALESTATEMARKET, FEETYPE_MARKET_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}

			// ������ ������. 
			cltLetterMsg_RealEstateMarketTrade clletter1( pclMsg->siHouseVillage, pclMsg->siHouseIndex, price, fee );
			SendLetterMsg(pclMsg->siSellerPersonID, (cltLetterHeader*)&clletter1);

			if(pclCM->IsValidID(sellerid))
			{

				pclCM->CR[sellerid]->pclCI->clRealEstate.Delete( REALESTATE_TYPE_HOUSE, pclMsg->siHouseVillage, pclMsg->siHouseIndex );
			
				cltMsg clMsg( GAMEMSG_RESPONSE_REALESTATE, sizeof( cltCharRealEstate ), (BYTE*)&pclCM->CR[sellerid]->pclCI->clRealEstate );
				pclCM->CR[sellerid]->SendNetMsg( (sPacketHeader*)&clMsg );

/*
				//---------------------------------
				// ���� �ܾ� 
				//---------------------------------
				pclCM->CR[sellerid]->pclCI->clBank.SetMoney( pclMsg->clSellerBankMoney.itMoney );
				
				pclCM->CR[sellerid]->SetUpdateSwitch( UPDATE_BANK, true );
*/
			}

			returnval = SRVAL_REALESTATEMARKET_SUCCESS_BUY;
		}
		break;

	case 2:
		{
			returnval = SRVAL_REALESTATEMARKET_FAIL_BUY_NOTENOUGHMONEY;
		}
		break;

	case 4:
		{
			// �ֹ� ���� 
			pclRealEstateMarketManager->DelOrder( pclMsg->siOrderIndex );

			returnval = SRVAL_REALESTATEMARKET_FAIL_BUY_NOTVALID;
		}
		break;

	} 

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_SETFEE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;	

	sDBResponse_RealEstateMarketSetFee *pclMsg = (sDBResponse_RealEstateMarketSetFee *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if( pclCM->IsValidID(id) == FALSE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID ) return;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_REALESTATEMARKET );

	if( pStrInfo ) {
		pStrInfo->clHorseMarketStrInfo.clFee.Set( &pclMsg->clFee );
	
		SendServerResponseMsg( RANKTYPE_REALESTATEMARKET, SRVAL_REALESTATEMARKET_SUCCESS_SETFEE, 0, 0, pclCM->CR[id]->GetCharUnique() );

	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // �ε��� �ŷ� �����Ḧ  ����
		// param1 == ������ ����. 
		// param2 == ���� ������, 
		// param3 == �ִ� ������. 
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_SELL_SET_FEE, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->clFee.GetFeeRate(), pclMsg->clFee.GetMinFee(), pclMsg->clFee.GetMaxFee(), 0, 0, 
										NULL, NULL);

	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_REDUCEREALESTATEORDERPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ReduceRealEstateOrderPrice* pclMsg = (sDBResponse_ReduceRealEstateOrderPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	pclRealEstateMarketManager->UpdatePrice( pclMsg->arrayindex, &pclMsg->clOrder );

	// ���� �ֹ��ڰ� �ִٸ� ���ŵ� ������ �뺸�Ѵ�. 

	// ������ ������. 
	cltLetterMsg_RealEstateMarketPriceDown clletter( pclMsg->clOrder.siVillageUnique, 
		pclMsg->clOrder.siHouseIndex, pclMsg->clOrder.siPrice );
	SendLetterMsg( pclMsg->clOrder.siPersonID, (cltLetterHeader*)&clletter );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// TEMP LEEKH --------------------------------------------------------------
		// [�α��߰� : Ȳ���� 2007. 10. 18] // �ε��� �ֹ� ���� ����. ������ �ٿ�ȴ�.
		// param1		== �ε���. 
		// param2		== �ֹ���ȣ.
		// param3		== ����.
		// param4		== �ε��� ��ȣ.
		// pszParam1	== �ð�.
		TCHAR pszCharParam1[50] = {'\0', };
		StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d"),	
																	pclMsg->clOrder.clDate.uiYear,
																	pclMsg->clOrder.clDate.uiMonth,
																	pclMsg->clOrder.clDate.uiDay,
																	pclMsg->clOrder.clDate.uiHour,
																	pclMsg->clOrder.clDate.uiMinute );
		

		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_PRICE_REDUCE, 
										0, NULL, NULL, pclMsg->clOrder.siPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->clOrder.siVillageUnique, 0, 0, 
										pclMsg->arrayindex, 
										pclMsg->clOrder.siIndex, 
										pclMsg->clOrder.siPrice,  
										pclMsg->clOrder.siHouseIndex, 
										0, 
										pszCharParam1, NULL);
		// TEMP LEEKH --------------------------------------------------------------
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_REALESTATEMARKET_DELORDER(sPacketHeader* pPacket)
{
	sDBResponse_RealEstateMarketDelOrder* pclMsg = (sDBResponse_RealEstateMarketDelOrder*)pPacket;

	if( pclMsg->siResult == 1 ) {
		pclRealEstateMarketManager->DelOrder( pclMsg->siOrderIndex );
	}


	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 11] // �ε��� �ֹ��� ��ȿ ���� ���� ��� ����.
		// param1 == �ֹ���ȣ. 
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_REALESTATE, LOGCOMMAND_INDEX_REALESTATE_SELL_ORDER_DELETE, 
										0, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->siOrderIndex, 0, 0, 0, 0, NULL, NULL);
	}
}