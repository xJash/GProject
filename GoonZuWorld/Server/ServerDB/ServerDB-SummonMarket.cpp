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

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-SummonMarket.h"
#include "Statistics\Statistics.h"

//------------------------------------
// CommonLogic
//-----------------------------------
#include "Msg\MsgType-SummonMarket.h"
#include "MsgType-Person.h"
#include "MsgRval-Define.h"


void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_GETMANYORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_SummonMarketGetManyOrder* pclMsg = (sDBResponse_SummonMarketGetManyOrder*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->usCount > GET_MANY_SUMMONMARKET_ORDER_NUM )		pclMsg->usCount = GET_MANY_SUMMONMARKET_ORDER_NUM;
	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for( i = 0; i < pclMsg->usCount; ++i )
	{
		pclSummonMarketManager->AddOrder( &pclMsg->clOrder[ i ] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_SummonMarketGetManyOrder"));
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_ORDERSELL(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_SummonMarketOrderSell *pclMsg = (sDBResponse_SummonMarketOrderSell *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	returnval = SRVAL_SUMMONMARKET_FAIL_SELL;

	switch( pclMsg->siResult ) 
	{
		case 1:
			{			
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					//VillageUnique, OrderIndex, Price, SummonIndex, Kind, Name, Status, AttackType, Identity, Str/Dex/Vit/Mag, Life/Mana, Exp/Level/Bonus, Scroll1, Scroll2, ItemPos, LeftItemNum, TradeType
					
					// TEMP LEEKH -------------------------------------------------------------------
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ȯ�� �Ǹ� ���.
					// param1 == �κ��丮 ��ġ,  pszParam1 == ��ȯ�� �ǸŰ��� ����.
					/*TCHAR	str[256];
					ZeroMemory(str, sizeof(str));
					StringCchPrintf(str, sizeof(str), TEXT("Index : %d, PersonID : %d, Price : %d, %d Year, %d Month, %d Day, %d Hour, %d Minute"),	
															pclMsg->clOrder.siIndex,
															pclMsg->clOrder.siPersonID,
															pclMsg->clOrder.siPrice,
															pclMsg->clOrder.clDate.uiYear,
															pclMsg->clOrder.clDate.uiMonth,
															pclMsg->clOrder.clDate.uiDay,
															pclMsg->clOrder.clDate.uiHour,
															pclMsg->clOrder.clDate.uiMinute);
					
				
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_MARKET, LOGCOMMAND_INDEX_SUMMON_MARKET_SELL_ORDER, 
													0,(cltCharServer* )pclCM->CR[id], &pclMsg->clOrder.clSummon, 0, pclMsg->siTax, pclMsg->siPersonMoney, &pclMsg->clitem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
													pclMsg->siPos, 0, 0, 0, 0, str, NULL);*/
					// TEMP LEEKH -------------------------------------------------------------------
				}

				pclSummonMarketManager->AddOrder( &pclMsg->clOrder );
				
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

				//[����] ��ȯ�� �ŷ��� ������ �α� ����� ���� �߰� => 2008-7-23
				GMONEY Tax = pclCM->CR[id]->pclCI->clIP.GetMoney() - pclMsg->siPersonMoney;

				// ���� ���� ������Ʈ 
				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

				// �����ڱ� ������Ʈ 
				cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONMARKET );
				if( pStrInfo ) 
				{
					pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clSummonMarketMoney );
				}

				// ���� �ŷ��� ���
				if( pclMsg->clOrder.siSelectPersonID != 0 ) 
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
				cltGameMsgResponse_SummonMarketSell sendMsg;
				sendMsg.clSummonOrder.Set( &pclMsg->clOrder );

				cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_SELL, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

				returnval = SRVAL_SUMMONMARKET_SUCCESS_SELL;


				//[����] ��ȯ�� �ŷ���. �Ǹ� ��� ���� �α�. => 2008-7-23
				//���� ����ũ, personID, ��ȯ�� ����ũ, ����, �����ŷ� ����. 
				pclClient->pclLog->FilePrint(	TEXT("Config\\SummonMarket.log"), "[SUMMON_SELL] VillageUnique = %d, PersonID = %d, SummonKind  = %s, Price = %I64d, Tax = %I64d, SelectPersonID = %d",
																					pclMsg->siVillageUnique,
																					pclMsg->clOrder.siPersonID,
																					pclClient->pclKindInfoSet->pclKI[ pclMsg->clOrder.clSummon.siKind ],
																					pclMsg->clOrder.siPrice,
																					Tax,
																					pclMsg->clOrder.siSelectPersonID);
			}
			break;

		case 2:
			{
				returnval = SRVAL_SUMMONMARKET_FAIL_SELL_NOTENOUGHMONEY;
			}
			break;

		case 5:
			{
				returnval = SRVAL_SUMMONMARKET_FAIL_SELECTSELL_WRONGNAME;
			}
	}

	if( returnval ) 
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_MYORDER(sPacketHeader* pPacket)
{

	sDBResponse_SummonMarketMyOrder *pclMsg = (sDBResponse_SummonMarketMyOrder *)pPacket;
	
	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) return;

	if( pclMsg->siResult == 1 ) 
	{
		cltGameMsgResponse_SummonMarketMyOrder sendMsg;

		if( pclMsg->usCount > MAX_SUMMONMARKET_ORDER_PER_PERSON )		pclMsg->usCount = MAX_SUMMONMARKET_ORDER_PER_PERSON;
		for( int i = 0; i < pclMsg->usCount; ++i ) {

			sendMsg.clMyOrder[ i ].Set( &pclMsg->clMyOrder[ i ] );
		}

		sendMsg.usCount = pclMsg->usCount;

		cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_MYORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

	} 
	else
	{
		cltGameMsgResponse_SummonMarketMyOrder sendMsg;
		ZeroMemory(&sendMsg, sizeof(sendMsg));
		
		cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_MYORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_CANCELORDER(sPacketHeader* pPacket)
{
	sDBResponse_SummonMarketCancelOrder *pclMsg = (sDBResponse_SummonMarketCancelOrder *)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE )
		return;

	SI32 returnval = SRVAL_SUMMONMARKET_FAIL_CANCELORDER;

	switch( pclMsg->siResult ) 
	{
		case 1:
			{
				// �ֹ� ���� 
				pclSummonMarketManager->DelOrder( pclMsg->siOrderIndex );

				// ��ȯ�� ����
				pclCM->CR[ id ]->pclCI->clSummonInfo.SetSummon( pclMsg->clSummon.siSummonID, &pclMsg->clSummon );

				cltGameMsgResponse_SummonMarketCancelOrder sendMsg( pclMsg->siOrderIndex, &pclMsg->clSummon );
				cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_CANCELORDER, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

				returnval = SRVAL_SUMMONMARKET_SUCCESS_CANCELORDER;

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ȯ�� �Ǹ� ��� ���.
					// param1 == �ֹ���ȣ.
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_MARKET, LOGCOMMAND_INDEX_SUMMON_MARKET_SELL_ORDER_CANCEL, 
													0,(cltCharServer* )pclCM->CR[id], &pclMsg->clSummon, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
													pclMsg->siOrderIndex, 0, 0, 0, 0, NULL, NULL);
				}			
			}
			break;

		case 2:
			{
				// ��ȯ���� ���̻� ������ �� ���� 
				returnval = SRVAL_SUMMONMARKET_FAIL_CANCELORDER_NOMORE;
			}
			break;
	} 

	if( returnval ) 
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_BUY(sPacketHeader* pPacket)
{
	SI32 returnval = 0;

	sDBResponse_SummonMarketBuy *pclMsg = (sDBResponse_SummonMarketBuy *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if(pclCM->IsValidID(id) == FALSE) 
		return;

	returnval = SRVAL_SUMMONMARKET_FAIL_BUY;

	switch( pclMsg->siResult ) 
	{
	case 1:
		{
			// �ֹ� ���� 
			pclSummonMarketManager->DelOrder( pclMsg->siOrderIndex );

			// �忹�� �ڱ� 
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONMARKET );


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
				cltGameMsgResponse_SummonMarketBuy sendMsg( pclMsg->siOrderIndex, &pclMsg->clSummon );
				cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_BUY, sizeof( sendMsg ), (BYTE*)&sendMsg );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{					
					// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ȯ�� ����.
					// param1 == �ֹ���ȣ. param2 == ��ȯ�� ����, pszParam1 == ��ȯ�� �̸�. 
					cltServer * pclServer = (cltServer*)pclClient;
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_MARKET, LOGCOMMAND_INDEX_SUMMON_MARKET_BUY, 
													0,(cltCharServer* )pclCM->CR[id], &pclMsg->clSummon, pclMsg->siSellerPersonID, 
													pclMsg->siTradePrice, pclMsg->siMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
													pclMsg->siOrderIndex, pclMsg->clSummon.siKind, 0, 0, 0, pclMsg->clSummon.szName, NULL);
				}
			}


			//-----------------------------------------
			// ������ ����(���� �ܾ�, �ֹ� ���� )�� ������Ʈ �Ѵ�. 
			//-----------------------------------------
			SI32	sellerid = pclCM->GetIDFromPersonID( pclMsg->siSellerPersonID );
			GMONEY	price	 = pclMsg->siTradePrice;

			//---------------------------------------------
			// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
			//--------------------------------------------
			// �����Ḧ Ȯ���Ѵ�. 
			cltStrInfo* pclstrinfo = pclSummonMarketManager->GetStrInfo( pclMsg->siVillageUnique );
			if(pclstrinfo == NULL)
				return ;

			GMONEY fee = pclstrinfo->clSummonMarketStrInfo.clFee.CalcFee( price );

			if(fee)
			{
				cltMoney clmoney;
				clmoney.itMoney = fee;
				sDBRequest_PayFee clinfo(sellerid, pclMsg->siSellerPersonID, pclMsg->siVillageUnique, RANKTYPE_SUMMONMARKET, FEETYPE_MARKET_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}

			// ������ ������. 
			cltLetterMsg_SummonMarketTrade clletter1( pclMsg->clSummon.siKind, pclMsg->clSummon.szName, price, fee );
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

			returnval = SRVAL_SUMMONMARKET_SUCCESS_BUY;

			//[����] ��ȯ�� �ŷ���. ���� ���� �α�. => 2008-7-23
			//���� ����ũ, �Ǹ��� personID, ������ personID, ��ȯ�� ����, �ŷ�����, ������
			pclClient->pclLog->FilePrint(	TEXT("Config\\SummonMarket.log"), "[SUMMON_BUY] VillageUnique = %d, BuyerPersonID = %d, SellerPersonID = %d, SummonKind  = %s, Price = %I64d, Fee = %I64d",
																				pclMsg->siVillageUnique,
																				pclMsg->siPersonID,
																				pclMsg->siSellerPersonID,
																				pclClient->pclKindInfoSet->pclKI[ pclMsg->clSummon.siKind ],
																				pclMsg->siTradePrice,
																				fee
																				);
		}  
		break;

	case 2:
		{
			returnval = SRVAL_SUMMONMARKET_FAIL_BUY_NOTENOUGHMONEY;
		}
		break;

	case 3:
	case 4:
		{
			// �ֹ� ���� 
			//pclSummonMarketManager->DelOrder( pclMsg->siOrderIndex );

			returnval = SRVAL_SUMMONMARKET_FAIL_BUY_NOTVALID;
		}
		break;


	case 6:
		{
			returnval = SRVAL_SUMMONMARKET_FAIL_BUY_NOTSELECTPERSON;
		} 
		break;
	} 

	if( returnval ) 
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_SUMMONMARKET_SETFEE(sPacketHeader* pPacket)
{
	SI32 returnval = 0;	

	sDBResponse_SummonMarketSetFee *pclMsg = (sDBResponse_SummonMarketSetFee *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if( pclCM->IsValidID(id) == FALSE || pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID ) return;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_SUMMONMARKET );

	if( pStrInfo ) {
		pStrInfo->clSummonMarketStrInfo.clFee.Set( &pclMsg->clFee );
	
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_SUCCESS_SETFEE, 0, 0, pclCM->CR[id]->GetCharUnique() );

	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_REDUCESUMMONORDERPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ReduceSummonOrderPrice* pclMsg = (sDBResponse_ReduceSummonOrderPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	pclSummonMarketManager->UpdatePrice( pclMsg->arrayindex, &pclMsg->clOrder );

	// ���� �ֹ��ڰ� �ִٸ� ���ŵ� ������ �뺸�Ѵ�. 

	// ������ ������. 
	cltLetterMsg_SummonMarketPriceDown clletter( pclMsg->clOrder.clSummon.siKind,
		pclMsg->clOrder.clSummon.szName, 
		pclMsg->clOrder.siPrice );
	SendLetterMsg( pclMsg->clOrder.siPersonID, (cltLetterHeader*)&clletter );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// TEMP LEEKH -------------------------------------------------------------------
		// [�α��߰� : Ȳ���� 2007. 10. 11] // ��ϵ� ��ȯ�� ���� ����.
		// param1		 == �ֹ���ȣ. 
		// param2		 == ���ϵ� �ݾ�. 
		// pszCharParam1 == ��ȯ�� �̸�.
		// pszcharParam2 == �ð�.
		TCHAR	str[50];
		ZeroMemory(str, sizeof(str));
		StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d, %d:%d"),	
												pclMsg->clOrder.clDate.uiYear,
												pclMsg->clOrder.clDate.uiMonth,
												pclMsg->clOrder.clDate.uiDay,
												pclMsg->clOrder.clDate.uiHour,
												pclMsg->clOrder.clDate.uiMinute );


		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SUMMON_MARKET, LOGCOMMAND_INDEX_SUMMON_MARKET_PRICE_REDUCE, 
										0, NULL, &pclMsg->clOrder.clSummon, pclMsg->clOrder.siPersonID, 
										0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->clOrder.siIndex, pclMsg->clOrder.siPrice, 0, 0, 0, pclMsg->clOrder.clSummon.szName, str);

	}
}