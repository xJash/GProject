#include "../Common/CommonHeader.h"
#include "../Server/Server.h"
#include "../Common/Letter/Letter.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-HorseMarket.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "Statistics/Statistics.h"
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char/CharManager/CharManager.h"

#include "Msg/MsgType-HorseMarket.h"
#include "MsgRval-Define.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_GETMANYORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_HorseMarketGetManyOrder* pclMsg = (sDBResponse_HorseMarketGetManyOrder*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->usCount > GET_MANY_HORSEMARKET_ORDER_NUM )		pclMsg->usCount = GET_MANY_HORSEMARKET_ORDER_NUM;
	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for( i = 0; i < pclMsg->usCount; ++i )
	{
		pclHorseMarketManager->AddOrder( &pclMsg->clHorseOrder[ i ] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_HorseMarketGetManyOrder"));

}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_ORDERSELL(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_HorseMarketOrderSell *pclMsg = (sDBResponse_HorseMarketOrderSell *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_HORSEMARKET_FAIL_SELL;

	switch( pclMsg->siResult ) {
	case 1:
		{			
			// �� ����
			pclCM->CR[ id ]->pclCI->clHorseInfo.Init( pclMsg->siHorseIndex );

			pclHorseMarketManager->AddOrder( &pclMsg->clHorseOrder );

			// ���� ���� ������Ʈ 
			pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

			// �纹�� �����ڱ� ������Ʈ 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_HORSEMARKET );
			if( pStrInfo ) {
				pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clHorseMarketMoney );
			}

			//KHY - 1001 - ��µ��� 5���� ���� ����.
			// Ŭ���̾�Ʈ�� �뺸 
			cltGameMsgResponse_HorseMarketSellHorse sendMsg( pclMsg->siHorseIndex, &pclMsg->clHorseOrder );;

			cltMsg clMsg( GAMEMSG_RESPONSE_HORSEMARKET_SELLHORSE, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

			returnval = SRVAL_HORSEMARKET_SUCCESS_SELLHORSE;
			
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				TCHAR str[50] = {'\0', };
				StringCchPrintf(str, sizeof(str), "Str: %d, Dex: %d, Mag: %d, Speed: %d",
													pclMsg->clHorseOrder.clHorse.siStr,
													pclMsg->clHorseOrder.clHorse.siDex,
													pclMsg->clHorseOrder.clHorse.siMag,
													pclMsg->clHorseOrder.clHorse.siMoveSpeed );


				// [�α��߰� : Ȳ���� 2007. 10. 10] // Ż�� �Ǹ� ��� �α׾���. 
				// param2	 == �纹�� �����ڱ�, 
				// param3	 == �ֹ���ȣ,
				// param4    == �ֹ�����,
				// param5	 == �� ����ũ.
				// pszParam1 == �� �̸�,
				// pszParam2 == �� ����,
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_ORDERSELL, 
									0, (cltCharServer*)(pclCM->CR[ id ]), NULL, 0, pclMsg->siTax, pclMsg->siPersonMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									0, pclMsg->clHorseMarketMoney.itMoney, pclMsg->clHorseOrder.siIndex, 
									pclMsg->clHorseOrder.siPrice, pclMsg->clHorseOrder.clHorse.siHorseUnique, 
									pclMsg->clHorseOrder.clHorse.szName, str);
			}
		}
		break;

	case 2:
		{
			returnval = SRVAL_HORSEMARKET_FAIL_SELL_NOTENOUGHMONEY;
		}
		break;
	}

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_MYACCOUNT(sPacketHeader* pPacket)
{
	sDBResponse_HorseMarketMyAccount *pclMsg = (sDBResponse_HorseMarketMyAccount *)pPacket;
	
	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	if( pclMsg->siResult == 1 ) {

		cltGameMsgResponse_HorseMarketMyAccount sendMsg( &pclMsg->clHorseOrder );
		cltMsg clMsg( GAMEMSG_RESPONSE_HORSEMARKET_MYACCOUNT, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

	} 



}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_OUTHORSE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_HorseMarketOutHorse *pclMsg = (sDBResponse_HorseMarketOutHorse *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_HORSEMARKET_FAIL_GETBACK;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				TCHAR str[50] = {'\0', };
				StringCchPrintf(str, sizeof(str), "Str: %d, Dex: %d, Mag: %d, Speed: %d",
													pclMsg->clHorse.siStr,
													pclMsg->clHorse.siDex,
													pclMsg->clHorse.siMag,
													pclMsg->clHorse.siMoveSpeed);

				if( pclMsg->siOrderIndex >= 0 && pclMsg->siOrderIndex < MAX_HORSEMARKET_ORDER_NUMBER )
				{
					cltHorseOrder* HorseOrder = &pclHorseMarketManager->pclHorseOrder[pclMsg->siOrderIndex];
					// [�α��߰� : Ȳ���� 2007. 10. 16] // Ż�� �Ǹ� ��� ��� �α׾���.
					// param3 == �ֹ���ȣ. 
					// param4 == �ֹ�����.
					// param5 == �� ����ũ.
					// pszParam1 == �� �̸�.
					// pszParam2 == �� ����.
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_SELLCANCEL, 
						0, (cltCharServer*)(pclCM->CR[ id ]), NULL, 0, 0, 0, NULL, 0, 0, 0, pclHorseMarketManager->siVillageUnique, 0, 0, 
						0, 0, HorseOrder->siIndex, HorseOrder->siPrice, HorseOrder->clHorse.siHorseUnique, 
						pclMsg->clHorse.szName, str);
				}
			}

			// �ֹ� ���� 
			pclHorseMarketManager->DelOrder( pclMsg->siOrderIndex );

			// �� ������Ʈ
			pclCM->CR[ id ]->pclCI->clHorseInfo.SetHorse( pclMsg->siHorseIndex, &pclMsg->clHorse );


			cltGameMsgResponse_HorseMarketOutHorse sendMsg( pclMsg->siHorseIndex, &pclMsg->clHorse );
			cltMsg clMsg( GAMEMSG_RESPONSE_HORSEMARKET_OUTHORSE, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

			returnval = SRVAL_HORSEMARKET_SUCCESS_GETBACK;
		}
		break;

	} 

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_BUYHORSE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_HorseMarketBuyHorse *pclMsg = (sDBResponse_HorseMarketBuyHorse *)pPacket;

	SI32 id = pclMsg->usCharID;

	returnval = SRVAL_HORSEMARKET_FAIL_BUY;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclHorseMarketManager->DelOrder( pclMsg->siOrderIndex );

			if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID ) {
				
				// �� ������Ʈ
				pclCM->CR[ id ]->pclCI->clHorseInfo.SetHorse( pclMsg->siHorseIndex, &pclMsg->clHorse );

				//--------------------------------
				// ���� ���� ������ ������Ʈ �Ѵ�. 
				//--------------------------------
				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siMoney );
				pclCM->CR[id]->SetUpdateSwitch( UPDATE_IP, true, 0 );

				cltGameMsgResponse_HorseMarketBuyHorse sendMsg( pclMsg->siHorseIndex, &pclMsg->clHorse, pclMsg->siOrderIndex );
				cltMsg clMsg( GAMEMSG_RESPONSE_HORSEMARKET_BUYHORSE, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

				// ������ ������ ������Ʈ���ش�.
				{
					sDBRequest_PersonItemInfoGet clMsg(id, pclCM->CR[id]->pclCI->GetPersonID());
					pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
				}
			}

			// �纹�� �ڱ� 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_HORSEMARKET );

			//-----------------------------------------
			// ������ ����(���� �ܾ�, �ֹ� ���� )�� ������Ʈ �Ѵ�. 
			//-----------------------------------------
			SI32 sellerid = pclCM->GetIDFromPersonID( pclMsg->siSellerPersonID );
			GMONEY price		= pclMsg->siTradePrice;

			//---------------------------------------------
			// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
			//--------------------------------------------
			// �����Ḧ Ȯ���Ѵ�. 
			cltStrInfo* pclstrinfo = pclHorseMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			if(pclstrinfo == NULL)return ;

			GMONEY fee = pclstrinfo->clHorseMarketStrInfo.clFee.CalcFee( price );

			if(fee)
			{
				cltMoney clmoney;
				clmoney.itMoney = fee;
				sDBRequest_PayFee clinfo(sellerid, pclMsg->siSellerPersonID, pclMsg->siVillageUnique, RANKTYPE_HORSEMARKET, FEETYPE_MARKET_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}

			// ������ ������. 
			cltLetterMsg_HorseMarketTrade clletter1( price, fee);
			SendLetterMsg(pclMsg->siSellerPersonID, (cltLetterHeader*)&clletter1);

/*
			if(pclCM->IsValidID(sellerid))
			{
				//---------------------------------
				// ���� �ܾ� 
				//---------------------------------
				pclCM->CR[sellerid]->pclCI->clBank.SetMoney( pclMsg->clSellerBankMoney.itMoney );
				
				pclCM->CR[sellerid]->SetUpdateSwitch( UPDATE_BANK, true );
			}
*/

			// �� �ŷ� �Ǽ�. 
			 pclStatisticsManager->clDailyStatistics.siHorseMarketTradeNumber++;

			// �� �ŷ� �ݾ� ���� 
			pclStatisticsManager->clDailyStatistics.siHorseMarketTradeMoney += price;


			returnval = SRVAL_HORSEMARKET_SUCCESS_BUYHORSE;
		}
		break;

	case 2:
		{
			returnval = SRVAL_HORSEMARKET_FAIL_BUY_NOTENOUGHMONEY;
		}
		break;

	case 3:
	case 4:
		{
			// �ֹ� ���� 
			pclHorseMarketManager->DelOrder( pclMsg->siOrderIndex );

			returnval = SRVAL_HORSEMARKET_FAIL_BUY_NOTVALID;
		}
		break;

	} 

	if(pclCM->IsValidID(id) == FALSE) return;

	if( returnval ) 
	{
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			SI32 sellerid = pclCM->GetIDFromPersonID( pclMsg->siSellerPersonID );

			TCHAR str[50] = {'\0', };
			StringCchPrintf(str, sizeof(str), "Str: %d, Dex: %d, Mag: %d, Speed: %d",
												pclMsg->clHorse.siStr,
												pclMsg->clHorse.siDex,
												pclMsg->clHorse.siMag,
												pclMsg->clHorse.siMoveSpeed );

			// [�α��߰� : Ȳ���� 2007. 10. 10] // Ż�� �Ǹ� �α׾���. 
			// param1		 == �ֹ���ȣ.
			// param2		 == �� ���� ��ȣ.
            // pszCharParam1 == �� �̸�,  
			// pszCharParam2 == �� ����.
			cltCharServer* pclcharseller = NULL;
			if( pclCM->IsValidID(sellerid) )		pclcharseller = (cltCharServer*)(pclCM->CR[sellerid]);
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_SELL, 
								0, pclcharseller, NULL, pclMsg->siPersonID, 
								pclMsg->siTradePrice, pclMsg->clSellerBankMoney.itMoney, 0, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								pclMsg->siOrderIndex, pclMsg->siHorseIndex, 0, 0, 0, pclMsg->clHorse.szName, str);
		
			// [�α��߰� : Ȳ���� 2007. 10. 10] // Ż�� ���� �α׾���.
			// param1		 == �ֹ���ȣ.
			// param2		 == �� ���� ��ȣ.
			// pszCharParam1 == �� �̸�.
			// pszCharParam2 == �� ����.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_BUY, 
								0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->siSellerPersonID, 
								pclMsg->siTradePrice, pclMsg->siMoney, 0, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								pclMsg->siOrderIndex, pclMsg->siHorseIndex, 0, 0, 0, pclMsg->clHorse.szName, str);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSEMARKET_SETFEE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;	

	sDBResponse_HorseMarketSetFee *pclMsg = (sDBResponse_HorseMarketSetFee *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if( pclCM->IsValidID(id) == FALSE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID ) return;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_HORSEMARKET );

	if( pStrInfo ) {
		pStrInfo->clHorseMarketStrInfo.clFee.Set( &pclMsg->clFee );
	
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_SUCCESS_SETFEE, 0, 0, pclCM->CR[id]->GetCharUnique() );

	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_REDUCEHORSEORDERPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ReduceHorseOrderPrice* pclMsg = (sDBResponse_ReduceHorseOrderPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	pclHorseMarketManager->UpdatePrice( pclMsg->arrayindex, &pclMsg->clOrder );


	// �ֹ� ���� 
	if (pclMsg->clOrder.siPrice == 0)
	{
		pclHorseMarketManager->DelOrder( pclMsg->clOrder.siIndex );
	}

	// ���� �ֹ��ڰ� �ִٸ� ���ŵ� ������ �뺸�Ѵ�. 
	// ������ ������. 
	cltLetterMsg_HorseMarketPriceDown clletter( pclMsg->clOrder.clHorse.szName, pclMsg->clOrder.siPrice );
	SendLetterMsg( pclMsg->clOrder.siPersonID, (cltLetterHeader*)&clletter );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		TCHAR str[50] = {'\0', };
		StringCchPrintf(str, sizeof(str), "Str: %d, Dex: %d, Mag: %d, Speed: %d",
											pclMsg->clOrder.clHorse.siStr,
											pclMsg->clOrder.clHorse.siDex,
											pclMsg->clOrder.clHorse.siMag,
											pclMsg->clOrder.clHorse.siMoveSpeed );

		// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� ���� �϶�.
		// param1		 == �ֹ� ������ �ĺ���(�ε���), 
		// param2		 == ����, 
		// pszCharParam1 == �� �̸�,  
		// pszCharParam2 == �� ����.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_REDUCEHORSEORDERPRICE, 
							0, NULL, NULL, pclMsg->clOrder.siPersonID, 
							0, 0, 0, 0, 0, 0, 0, 0, 0, 
							pclMsg->clOrder.siIndex, pclMsg->clOrder.siPrice, 0, 0, 0, pclMsg->clOrder.clHorse.szName, str);
	}
}
