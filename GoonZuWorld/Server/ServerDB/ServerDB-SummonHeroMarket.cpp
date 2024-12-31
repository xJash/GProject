#include "..\Common\CommonHeader.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Letter\Letter.h"
#include "Char\CharManager\CharManager.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-SummonHeroMarket.h"
#include "Statistics\Statistics.h"

//------------------------------------
// CommonLogic
//-----------------------------------
#include "Msg\MsgType-SummonHeroMarket.h"
#include "MsgType-Person.h"
#include "MsgRval-Define.h"

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_GETMANYORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_SummonHeroMarketGetManyOrder* pclMsg = (sDBResponse_SummonHeroMarketGetManyOrder*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->usCount > GET_MANY_SUMMONHEROMARKET_ORDER_NUM )		pclMsg->usCount = GET_MANY_SUMMONHEROMARKET_ORDER_NUM;
	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for( i = 0; i < pclMsg->usCount; ++i )
	{
		pclSummonHeroMarketManager->AddOrder( &pclMsg->clOrder[ i ] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_SummonHeroMarketGetManyOrder"));
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_ORDERSELL(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_SummonHeroMarketOrderSell *pclMsg = (sDBResponse_SummonHeroMarketOrderSell *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_SUMMONHEROMARKET_FAIL_SELL;

	switch( pclMsg->siResult ) {
	case 1:
		{			
			pclSummonHeroMarketManager->AddOrder( &pclMsg->clOrder );
			
			// ��ȯ�� ���� 

			//---------------------------------------------
			// ��ȯ���� �����Ǿ��ִٸ� �����Ѵ�
			//---------------------------------------------
			SI32 siSummonID = pclCM->CR[id]->GetSummonID();
			if(pclCM->IsValidID(siSummonID)  == TRUE )
			{
				if(pclCM->CR[siSummonID]->GetSummonIndex() == pclMsg->clOrder.clSummon.siSummonID)
				{
					//---------------------------------------------
					// ���ӿ��� ��ȯ���� �����. 
					//---------------------------------------------
					pclCM->CR[siSummonID]->DeleteInCell();
					pclCM->DeleteChar(siSummonID);
					//==========================================
					// ������ ���� �ִ� ��ȯ���� ������ �����Ѵ�.
					//==========================================
					pclCM->CR[id]->siChildCharUnique  = 0;
					pclCM->CR[id]->siSummonIndex	  = 0;

					// �������׵� ������ ���Ž�Ų��.
					cltGameMsgResponse_ChangeSummonStatus clInfo(id, pclCM->CR[id]->siChildCharUnique, pclCM->CR[id]->siSummonIndex);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESUMMONSTATUS, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}


			pclCM->CR[ id ]->pclCI->clSummonInfo.SummonInit( pclMsg->clOrder.clSummon.siSummonID );

			// ���� ���� ������Ʈ 
			pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

			// �����ڱ� ������Ʈ 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONHEROMARKET ); 
			if( pStrInfo ) {
				pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clSummonMarketMoney );
			}

			if(pclMsg->clOrder.siSelectPersonID != 0 )
			{
				if( pclMsg->siPos >= 0 && pclMsg->siPos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siPos ].Set( &pclMsg->clitem );

					cltGameMsgResponse_PersonItemInfo clinfo1( pclMsg->siPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clitem, 0);
					cltMsg clMsg1(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo1), (BYTE*)&clinfo1);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
				}
			}

			// Ŭ���̾�Ʈ�� �뺸 
			cltGameMsgResponse_SummonHeroMarketSell sendMsg;
			sendMsg.clSummonOrder.Set( &pclMsg->clOrder );

			cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONHEROMARKET_SELL, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

			returnval = SRVAL_SUMMONHEROMARKET_SUCCESS_SELL;
		

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// TEMP LEEKH -------------------------------------------------------------------
				// [�α��߰� : Ȳ���� 2007. 10. 18] // ��ȯ ���� �ֹ�.(�����ʿ�)
				// param1 == ��ġ. param2 == �ŷ��� �����ڱ�.
				/*TCHAR str[256];
				ZeroMemory(str, sizeof(str));
				StringCchPrintf(str, sizeof(str), TEXT("%d Year %d Month %d Day %d Hour %d Minute"),	
														pclMsg->clOrder.clDate.uiYear, 
														pclMsg->clOrder.clDate.uiMonth, 
														pclMsg->clOrder.clDate.uiDay, 
														pclMsg->clOrder.clDate.uiHour, 
														pclMsg->clOrder.clDate.uiMinute);

			
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_HERO_MARKET, LOGCOMMAND_INDEX_SUMMON_HERO_MARKET_SELL_ORDER, 
												0, (cltCharServer*)pclCM->CR[id], &pclMsg->clOrder.clSummon, pclMsg->clOrder.siSelectPersonID, 
												pclMsg->siTax, pclMsg->siPersonMoney, &pclMsg->clitem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siPos, pclMsg->clSummonMarketMoney.itMoney, 0, 0, 0, str, NULL);*/
				// TEMP LEEKH -------------------------------------------------------------------
			}
		}
		break;

	case 2:
		{
			returnval = SRVAL_SUMMONHEROMARKET_FAIL_SELL_NOTENOUGHMONEY;
		}
		break;

	case 5:
		{
			returnval = SRVAL_SUMMONHEROMARKET_FAIL_SELECTSELL_WRONGNAME;
		}

	}

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_SUMMONHEROMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_MYORDER(sPacketHeader* pPacket)
{

	sDBResponse_SummonHeroMarketMyOrder *pclMsg = (sDBResponse_SummonHeroMarketMyOrder *)pPacket;
	
	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	if( pclMsg->siResult == 1 ) {

		cltGameMsgResponse_SummonHeroMarketMyOrder sendMsg;

		if( pclMsg->usCount > MAX_SUMMONHEROMARKET_ORDER_PER_PERSON )		pclMsg->usCount = MAX_SUMMONHEROMARKET_ORDER_PER_PERSON;
		for( int i = 0; i < pclMsg->usCount; ++i ) {

			sendMsg.clMyOrder[ i ].Set( &pclMsg->clMyOrder[ i ] );
		}

		sendMsg.usCount = pclMsg->usCount;

		cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONHEROMARKET_MYORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

	} 

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER(sPacketHeader* pPacket)
{
	sDBResponse_SummonHeroMarketCancelOrder *pclMsg = (sDBResponse_SummonHeroMarketCancelOrder *)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE ) return;

	SI32 returnval = SRVAL_SUMMONHEROMARKET_FAIL_CANCELORDER;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclSummonHeroMarketManager->DelOrder( pclMsg->siOrderIndex );

			// ��ȯ�� ����
			pclCM->CR[ id ]->pclCI->clSummonInfo.SetSummon( pclMsg->clSummon.siSummonID, &pclMsg->clSummon );

			cltGameMsgResponse_SummonHeroMarketCancelOrder sendMsg( pclMsg->siOrderIndex, &pclMsg->clSummon );
			cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONHEROMARKET_CANCELORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

			returnval = SRVAL_SUMMONHEROMARKET_SUCCESS_CANCELORDER;
			
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			{
				// [�α��߰� : Ȳ���� 2007. 10. 11] // ���� ��ȯ�� ��ϵ� �Ǹ� ���� ���.
				// param1 == ��ϵ� �Ǹ� ��ȣ.
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_HERO_MARKET, LOGCOMMAND_INDEX_SUMMON_HERO_MARKET_SELL_ORDER_CANCEL, 
												0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
												pclMsg->siOrderIndex, 0, 0, 0, 0, NULL, NULL);
			}
		}
		break;

	case 2:
		{
			// ��ȯ���� ���̻� ������ �� ���� 
			returnval = SRVAL_SUMMONHEROMARKET_FAIL_CANCELORDER_NOMORE;
		}
		break;

	} 

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_SUMMONHEROMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_BUY(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_SummonHeroMarketBuy *pclMsg = (sDBResponse_SummonHeroMarketBuy *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_SUMMONHEROMARKET_FAIL_BUY;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclSummonHeroMarketManager->DelOrder( pclMsg->siOrderIndex );

			// �忹�� �ڱ� 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONHEROMARKET );


			if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)	
			{

				//--------------------------------
				// ��ȯ�� ���� ������Ʈ
				//--------------------------------
				pclCM->CR[ id ]->pclCI->clSummonInfo.SetSummon( pclMsg->clSummon.siSummonID, &pclMsg->clSummon );


				//--------------------------------
				// ���� ���� ������ ������Ʈ �Ѵ�. 
				//--------------------------------
				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siMoney );
				pclCM->CR[id]->SetUpdateSwitch( UPDATE_IP, true, 0 );

				//--------------------------------
				// Ŭ���̾�Ʈ�� ���� ��Ŷ ����
				//--------------------------------
				cltGameMsgResponse_SummonHeroMarketBuy sendMsg( pclMsg->siOrderIndex, &pclMsg->clSummon );
				cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONHEROMARKET_BUY, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ȯ���� ����.
					// param1 == ������ ��ȯ������ �ֹ� ��ȣ.
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_HERO_MARKET, LOGCOMMAND_INDEX_SUMMON_HERO_MARKET_BUY, 
													0, (cltCharServer*)pclCM->CR[id], &pclMsg->clSummon, pclMsg->siSellerPersonID, 
													pclMsg->siTradePrice, pclMsg->siMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
													pclMsg->siOrderIndex, 0, 0, 0, 0, NULL, NULL);
				}
			}


			//-----------------------------------------
			// ������ ����(���� �ܾ�, �ֹ� ���� )�� ������Ʈ �Ѵ�. 
			//-----------------------------------------
			SI32 sellerid = pclCM->GetIDFromPersonID( pclMsg->siSellerPersonID );
			GMONEY price	= pclMsg->siTradePrice;

			//---------------------------------------------
			// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
			//--------------------------------------------
			// �����Ḧ Ȯ���Ѵ�. 
			cltStrInfo* pclstrinfo = pclSummonHeroMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			if(pclstrinfo == NULL)return ;

			GMONEY fee = pclstrinfo->clSummonMarketStrInfo.clFee.CalcFee( price );

			if(fee)
			{
				cltMoney clmoney;
				clmoney.itMoney = fee;
				sDBRequest_PayFee clinfo(sellerid, pclMsg->siSellerPersonID, pclMsg->siVillageUnique, RANKTYPE_SUMMONHEROMARKET, FEETYPE_MARKET_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}

			// ������ ������. 
			cltLetterMsg_SummonHeroMarketTrade clletter1( pclMsg->clSummon.siKind, pclMsg->clSummon.szName, price, fee );
			SendLetterMsg(pclMsg->siSellerPersonID, (cltLetterHeader*)&clletter1);


			// ��ȯ�� �ŷ� �Ǽ�. 
			pclStatisticsManager->clDailyStatistics.siSummonMarketTradeNumber++;
 
			// ��ȯ�� �ŷ� �ݾ� ���� 
			pclStatisticsManager->clDailyStatistics.siSummonMarketTradeMoney += price;

			if(pclCM->IsValidID(sellerid))
			{
/*
				//---------------------------------
				// ���� �ܾ� 
				//---------------------------------
				pclCM->CR[sellerid]->pclCI->clBank.SetMoney( pclMsg->clSellerBankMoney.itMoney );
				
				pclCM->CR[sellerid]->SetUpdateSwitch( UPDATE_BANK, true );
*/
			}

			returnval = SRVAL_SUMMONHEROMARKET_SUCCESS_BUY;
		}
		break;

	case 2:
		{
			returnval = SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTENOUGHMONEY;
		}
		break;

	case 3:
	case 4:
		{
			// �ֹ� ���� 
			pclSummonHeroMarketManager->DelOrder( pclMsg->siOrderIndex );

			returnval = SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTVALID;
		}
		break;
	case 6:
		{
			returnval = SRVAL_SUMMONHEROMARKET_FAIL_BUY_NOTSELECTPERSON;
		}
		break;

	} 

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_SUMMONHEROMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONHEROMARKET_SETFEE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;	

	sDBResponse_SummonHeroMarketSetFee *pclMsg = (sDBResponse_SummonHeroMarketSetFee *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if( pclCM->IsValidID(id) == FALSE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID ) return;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONHEROMARKET );

	if( pStrInfo ) {
		pStrInfo->clSummonMarketStrInfo.clFee.Set( &pclMsg->clFee );
	
		SendServerResponseMsg( RANKTYPE_SUMMONHEROMARKET, SRVAL_SUMMONHEROMARKET_SUCCESS_SETFEE, 0, 0, pclCM->CR[id]->GetCharUnique() );

	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_REDUCESUMMONHEROORDERPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ReduceSummonHeroOrderPrice* pclMsg = (sDBResponse_ReduceSummonHeroOrderPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	pclSummonHeroMarketManager->UpdatePrice( pclMsg->arrayindex, &pclMsg->clOrder );

	// ���� �ֹ��ڰ� �ִٸ� ���ŵ� ������ �뺸�Ѵ�. 

	// ������ ������. 
	cltLetterMsg_SummonHeroMarketPriceDown clletter( pclMsg->clOrder.clSummon.siKind,
		pclMsg->clOrder.clSummon.szName, 
		pclMsg->clOrder.siPrice );
	SendLetterMsg( pclMsg->clOrder.siPersonID, (cltLetterHeader*)&clletter );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ȯ���� �ֹ� ������ ����.
		// param1 == ��ȯ������ �ֹ� ��ȣ. param2 == �϶��� �ݾ�. pszParam1 == ��ȯ�� �̸�.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_HERO_MARKET, LOGCOMMAND_INDEX_SUMMON_HERO_MARKET_PRICE_REDUCE, 
										0, NULL, NULL, pclMsg->clOrder.siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->arrayindex, pclMsg->clOrder.siPrice, 0, 0, 0, pclMsg->clOrder.clSummon.szName, NULL);
	}

}