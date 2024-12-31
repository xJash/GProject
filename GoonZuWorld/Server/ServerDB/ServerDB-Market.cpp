//---------------------------------
// 2003/8/9 ���°�
//---------------------------------

#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"

#include "..\..\Common\Map\Map.h"

#include "..\../../Server/AuthServer/AuthMsg.h"

#include "..\Minister\Minister-Goonzu.h"
#include "..\Minister\MinisterMgr.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Market.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

#include "MsgRval-Define.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../CommonLogic/Bank/Bank-Manager.h"

signed short UserMoneyCapsule(__int64 Money)
{
	signed short tMoney = (signed short)((Money % 7796) ^ 7796);

	return tMoney;
}

// �ֹ� ���� ���� ��û ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_REDUCEORDERPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ReduceOrderPrice* pclMsg = (sDBResponse_ReduceOrderPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if(pclMarketManager->pclOrderManager->SetOrder(ORDERMODE_SELL, &pclMsg->clOrder) == true)
	{
		pclMarketManager->SetItemTypeOrder(&pclMsg->clOrder, 200);
	}

	// ���� �ֹ��ڰ� �ִٸ� ���ŵ� ������ �뺸�Ѵ�. 
	
	// ������ ������. 
	cltItem clitem;
	clitem.Set(&pclMsg->clOrder.clItemData);

	cltLetterMsg_MarketPriceDown clletter(clitem.siUnique, clitem.siItemNum, pclMsg->clOrder.siPrice);
	SI32 id = SendLetterMsg(pclMsg->clOrder.siPersonID, (cltLetterHeader*)&clletter);
	if(pclCM->IsValidID(id))
	{
		// ĳ������ ���� ������ ������Ʈ �Ѵ�. 
		pclCM->CR[id]->pclCI->clMarket.clInfo.UpdateMarketOrder(pclMsg->siMarketIndex, &pclMsg->clOrder);

		pclCM->CR[id]->SetUpdateSwitch(UPDATE_MARKET, true, 0);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 4] // ����� �ֹ� ����(��������). 
			// param1 == ���� ��ȣ, 
			// param2 == ��ǰ ����ũ, 
			// param3 == ���ϵǱ� �� �ݾ�, 
			// param4 == ���ϵ� �ݾ�, 
			// param5 == �ֹ���ȣ
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_REDUCEORDERPRICE, 
											0, NULL, NULL, pclMsg->clOrder.siPersonID, 0, 0, &clitem, clitem.siItemNum, 0, 0, 0, 0, 0, 
											pclMsg->siMarketIndex, clitem.siUnique, pclMsg->siPrice, pclMsg->clOrder.siPrice, pclMsg->clOrder.siIndex, 
											NULL, NULL);
		}
	}
}

// ���� ���� ���� ��û��  ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MARKETACCOUNT(sPacketHeader* pPacket)
{
	sDBResponse_MarketAccount* pclMsg = (sDBResponse_MarketAccount*)pPacket;

	if(pclMsg->siResult == 0)
	{

		return ;
	}

	if(pclMsg->siPersonID <= 0)
	{

		return ;
	}
	
	// Ŭ���̾�Ʈ�� ��ȿ�� �����, 
	// ������ ĳ���͸� ã�ƾ� �Ѵ�. 
	SI32 id = pclMsg->usCharID;
	if(id == 0 || pclCM->IsValidID(id)== false )
	{
		//PersonID�� �ٰŷ� ID�� ã�´�. 
		// ���� �ֹ��� �÷� ���� ����� ������ �ȷ��� �� ���ڰ� �����߿� �ִٸ� �� �ȸ� ������ ������ ���ؼ���. 
		id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
		if(id == 0 || pclCM->IsValidID(id)== false)
		{
			return ;
		}
	}


	if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)	
	{
		pclCM->CR[id]->pclCI->clMarket.clInfo.Set(&pclMsg->clMarketAccount);
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_MARKET, true, 0);
	}
}

// ���� �ֹ��� DB�� ��û�� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETMANYMARKETORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_GetManyMarketOrder* pclMsg = (sDBResponse_GetManyMarketOrder*)pPacket;

	// id�� 0�ΰ�쵵 �����ϴ�. 

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for(i = 0;i < GET_MANY_MARKET_ORDER_NUM;i++)
	{
		// �ֹ��� ������ 0 �̸� ��ȿ�� �ֹ��̹Ƿ�(�ֹ��� ���� ����) �������� �ʴ´�. 
		if(pclMsg->clTradeOrder[i].siPrice)
		{
			if(pclMarketManager->pclOrderManager->SetOrder(pclMsg->siOrderMode, &pclMsg->clTradeOrder[i]) == true)
			{
				pclMarketManager->SetItemTypeOrder(&pclMsg->clTradeOrder[i], 300);
			}
		}
		
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetManyMarketOrder"));

}

// �ֹ� ������ DB�� �߰��϶�� ��û�� ���� ������ ó���Ѵ�.
void cltServer::DoMsg_DBMSG_RESPONSE_ORDERMARKET(sPacketHeader* pPacket)
{
	sDBResponse_OrderMarket* pclMsg = (sDBResponse_OrderMarket*)pPacket;

	if(pclMsg->clOrder.siType != TRADEORDER_TYPE_OBJECT)return ;

	SI32 id = pclMsg->usCharID;

	SI32 returnval = 0;

	switch(pclMsg->siResult )
	{
	case 0:		
		break;
	case 1:		
		{
			// ������ �ֹ� ���ۿ� DB�κ��� ���� �ֹ� ������ �߰��Ѵ�. 
			if(pclMarketManager->pclOrderManager->SetOrder(pclMsg->siOrderMode, &pclMsg->clOrder) == true)
			{
				pclMarketManager->SetItemTypeOrder(&pclMsg->clOrder, 400);
			}

			// Ŭ���̾�Ʈ�� ��ȿ�� �����, 
			// Ŭ���̾�Ʈ�� �� �ֹ� ������ ������. 
			if(pclCM->IsValidID(id)== false) return ;
		
			if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->clOrder.siPersonID)	
			{
				
				//---------------------------------
				// �κ��丮 ������ ������Ʈ �Ѵ�.
				//---------------------------------
				if( pclMsg->siItemFromPos >= 0 && pclMsg->siItemFromPos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemFromPos].Set(&pclMsg->clFromItem);

					// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
					cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemFromPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ǰ ��� ����. 
					// param1	 == �ֹ���ȣ. 
					// param2	 == �ֹ� ���� ����. 
					// param3    == ����.
					// pszParam1 == �Ǹ� �ֹ��� �������� �κ� ��ġ, �Ĵ� ������ ����ũ, �ֹ��ϰ� ���� �������� ����.
					TCHAR str[50];
					StringCchPrintf(str, sizeof(str), "Pos: %d, Unique: %d, Num: %d",
														pclMsg->siItemFromPos, 
														pclMsg->clOrderItem.siUnique, 
														pclMsg->clOrderItem.siItemNum);
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_ORDERMARKET, 
										 0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clOrderItem, pclMsg->clFromItem.GetItemNum(), 0, 0, pclMsg->clOrder.siVillageUnique, 0, 0, 
										 pclMsg->clOrder.siIndex, pclMsg->clOrder.siPrice, pclMsg->siTax, 0, 0, str, NULL);
				}

				//-------------------------------
				// ������ �����Ѵ�. 
				//-------------------------------
				if( false == pclCM->CR[id]->pclCI->clBI.bMarKetPremiumService )
				{
					if(pclMsg->siTax > 0)
					{
						if(pclCM->CR[id]->pclCI->clIP.GetMoney() >= pclMsg->siTax)
						{
							sDBRequest_ChangeMoney clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_USEMARKET, -pclMsg->siTax);
							pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);


							// ������ �����Ѵ�. 
							//clCurrencyInfo.clReservedBudget.itMoney += pclMsg->siTax;

							CMinisterGoonzu *pclminister = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
							pclminister->AddTempFinances( pclMsg->siTax );

							// ��ȭ�� ���� 
							cltMoney clmoney;
							clmoney.Set(pclMsg->siTax);
							clCurrencyInfo.clOutputMoney_clMarketTax.Increase(&clmoney);

                            pclDelMoneyStatistics->Add(DELMONEY_MARKETSERVICECHARGE, pclMsg->siTax);
						}
					}
				}
			}

			returnval	= SRVAL_MARKET_SUCCESS_ORDERSELL; 

			pclCM->CR[id]->DoQuestCheckAndAction( QUEST_CLEAR_COND_ORDERTOMARKET );
		}
		break;

	default:
		MsgBox(TEXT("DoMsg_DBMSG_RESPONSE_ORDERMARKET()"), TEXT("result:%d"), pclMsg->siResult);
		break;
	}
		
		
	if(pclCM->IsValidID(id) == false)return ;

	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	if(returnval)
	{
		SendServerResponseMsg(RANKTYPE_MARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// ���� �ŷ� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_TRADEMARKET(sPacketHeader* pPacket)
{
	sDBResponse_TradeMarket* pclMsg = (sDBResponse_TradeMarket* )pPacket;

	SI32 villageunique = pclMsg->siVillageUnique;

	// Ŭ���̾�Ʈ�� ��ȿ�� �����, 
	// Ŭ���̾�Ʈ�� �� �ֹ� ������ ������. 
	SI32 id = pclMsg->usCharID;
	
	SI32 returnval	= 0;
	SI32 rtnpara1	= 0;
		
	switch(pclMsg->siResult )
	{
	case -1:	returnval	= SRVAL_MARKET_SELL_FAIL;	rtnpara1 = 900; break;  // �κ��丮�� ���ڸ��� ��� �������� �ű� �� ����. 
	case -2:	returnval	= SRVAL_MARKET_SELL_FAIL;	rtnpara1 = 1000; break;	// ���� ���� ���� - ��� �ֹ��� ��� �ֹ���(�����δ� ������ ����.) 
	case -3:	returnval	= SRVAL_MARKET_SELL_FAIL;	rtnpara1 = 700; break;	// ���� ���� ���� - ���� ����. 
	case -4:	returnval	= SRVAL_MARKET_SELL_FAIL;	rtnpara1 = 1200; break;	// ���� ���� ���� - �Ǹ��ڰ� ������ ����. 
	case -5:	returnval	= SRVAL_MARKET_SELL_FAIL;	rtnpara1 = 800; break;	// ���� ���� ���� - ���� �ִ� ������ �ʰ�. 
	case -6:																	// ���� ���� ���� - ������ ������ ������ ���� �Աݽ�ų �� ����. 
		{
			returnval	= SRVAL_MARKET_SELL_FAIL;
			rtnpara1	= 1400;

			SI32 index	= pclMsg->clDstOrder.siIndex;
			if(index < 0 || index >= MAX_MARKET_ORDER_NUMBER)
			{
				pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("fd3fdee index:%d"), index);
				return ;
			}
			pclMarketManager->pclOrderManager->pclOrderSell[index]->bBankError = true ;
		}
		break;
	case 0:		break;
	case 1:		
		{
			// �����ֹ��� ������Ʈ �Ѵ�. 
			//���� �ֹ����� ã�´�. 
			SI32 index				= pclMsg->clDstOrder.siIndex;
			if(index < 0 || index >= MAX_MARKET_ORDER_NUMBER)
			{
				pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("fd3fdff index:%d"), index);
				return ;
			}
			SI32 orderitemunique	= pclMarketManager->pclOrderManager->pclOrderSell[index]->clItemData.siUnique;

			if(pclMarketManager->pclOrderManager->SetOrder(ORDERMODE_SELL, &pclMsg->clDstOrder) == true)
			{
				cltTradeOrder clorder;
				clorder.Set(&pclMsg->clDstOrder);
				clorder.clItemData.siUnique	= orderitemunique;
				
				pclMarketManager->SetItemTypeOrder(&clorder, 500);
			}
			
			
			//---------------------------------
			// �ŷ��� ������ �����Ѵ�.
			//---------------------------------
			if(pclMsg->clItem.siUnique && pclMsg->siTradePrice)
			{
				pclItemManager->SetCurrentPrice(pclMsg->clItem.siUnique, pclMsg->siTradePrice, pclMsg->siTradeItemNum);

				cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(pclMsg->clItem.siUnique);
				if(pclprice)
				{
					const TCHAR* pszItemName = pclClient->pclItemManager->GetName(pclprice->siUnique);
					sDBRequest_SetItemPrice clMsg(pclprice->siUnique, pclprice->siPrice, pclprice->fPrice, pclprice->siItemNum, pszItemName);
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
				}
			}
			
			if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)	
			{
				//--------------------------------
				// ���� ���� ������ ������Ʈ �Ѵ�. 
				//--------------------------------
				pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siMoney);
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);


				//---------------------------------
				// �κ��丮 ������ ������Ʈ �Ѵ�.
				//---------------------------------
				if(pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON)
				{
					pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
					
					// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
					cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					
					((cltCharServer*)pclCM->CR[id])->IncQuestPara( QUEST_CLEAR_COND_BUYMARKET, pclMsg->clItem.siUnique, pclMsg->siTradeItemNum );

				}
			}

			//-----------------------------------------
			// ������ ����(���� �ܾ�, �ֹ� ���� )�� ������Ʈ �Ѵ�. 
			//-----------------------------------------
			SI32 sellerid = pclCM->GetIDFromPersonID(pclMsg->siSellerPersonID);
			// ������ �ŷ��� �̷���� ������ Ȯ���Ѵ�. 
			SI32	itemunique = pclMsg->clItem.siUnique;
			SI32	itemnum	   = pclMsg->siTradeItemNum;
			GMONEY	price	   = pclMsg->siTradePrice;

			if(itemunique)
			{
				//---------------------------------------------
				// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
				//--------------------------------------------
				// �����Ḧ Ȯ���Ѵ�. 
				cltStrInfo* pclstrinfo = pclMarketManager->GetStrInfo(villageunique);
				if ( NULL != pclstrinfo )
				{
					GMONEY fee = pclstrinfo->clMarketStrInfo.clFee.CalcFee(itemnum * price);

					if(fee)
					{
						cltMoney clmoney;
						clmoney.itMoney = fee;
						sDBRequest_PayFee clinfo(sellerid, pclMsg->siSellerPersonID, villageunique, RANKTYPE_MARKET, FEETYPE_MARKET_SELL, &clmoney);
						pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

						pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
					}


					// ������ ������.
					cltLetterMsg_MarketTrade clletter1(itemunique, itemnum, price*itemnum, fee);
					SendLetterMsg(pclMsg->siSellerPersonID, (cltLetterHeader*)&clletter1);
				}
			}

			if(pclCM->IsValidID(sellerid))
			{
				//---------------------------------
				// ���� �ܾ� 
				//---------------------------------
				pclCM->CR[sellerid]->pclCI->clBank.SetMoney(pclMsg->siSellerBankMoney);
				
				pclCM->CR[sellerid]->SetUpdateSwitch(UPDATE_BANK, true, 0);
			}


			returnval = SRVAL_MARKET_SUCCESS_TRADE;	
		}	
		break;

	default:
		MsgBox(TEXT("DoMsg_DBMSG_RESPONSE_TRADEMARKET()"), TEXT("result:%d"), pclMsg->siResult);
		break;
	}


	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	if(returnval)
	{
		if(pclCM->IsValidID(id))
		{
			if(returnval == SRVAL_MARKET_SUCCESS_TRADE)
			{
				SendServerResponseMsg(RANKTYPE_MARKET, returnval,  rtnpara1, 0, pclCM->CR[id]->GetCharUnique());
			}
			else
			{
				SendServerResponseMsg(0, returnval,  rtnpara1, 0, pclCM->CR[id]->GetCharUnique());
			}
			
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				SI32 sellerid = pclCM->GetIDFromPersonID(pclMsg->siSellerPersonID);

				TCHAR pszCharParam1[50] = {'\0', };
				
				cltItemData*  ItemData = &pclMsg->clDstOrder.clItemData;

				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "Unique: %d, Num: %d",
																		ItemData->siUnique, 
																		ItemData->siItemNum);

				// ��ü �ŷ��ݾ�.
				SI32 siTotalTradeMoney = pclMsg->siTradePrice * pclMsg->clTradeItem.siItemNum;

				// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ǰ �Ǹ� ����. 
				// param1 == �ֹ���ȣ,
				// param2 == ������ �ϳ��� ����.
				// pszCharParam1 == �ֹ� ������ ������ ����.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_SELL, 
									 pclMsg->siReason, (cltCharServer*)(pclCM->CR[sellerid]), NULL, pclMsg->siPersonID, 
									 siTotalTradeMoney, pclMsg->siSellerBankMoney, &pclMsg->clTradeItem, pclMsg->siTradeItemNum, 
									 0, 0, pclMsg->siVillageUnique, 0, 0, 
									 pclMsg->clDstOrder.siIndex, pclMsg->siTradePrice, 0, 0, 0, 
									 pszCharParam1, NULL);

				// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ǰ ���� ����. 
				// param1 == �ֹ���ȣ.
				// param2 == ������ �ϳ��� ����.
				// pszCharParam1 == ���� �κ��� ������ ����.
				ZeroMemory(pszCharParam1, sizeof(pszCharParam1));
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "Pos: %d, Unique: %d, Num: %d",
																		pclMsg->siItemPos, 
																		pclMsg->clItem.siUnique, 
																		pclMsg->clItem.siItemNum);


				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_BUY, 
									pclMsg->siReason, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->siSellerPersonID, 
									siTotalTradeMoney, pclMsg->siMoney, &pclMsg->clTradeItem,  pclMsg->siTradeItemNum, 
									0, 0, pclMsg->siVillageUnique, 0, 0, 
									pclMsg->clDstOrder.siIndex, pclMsg->siTradePrice, siTotalTradeMoney, 0, 0,
									pszCharParam1, NULL);
		
			}
		}
		
		// �ý����� �����ϸ�.
		if(0 == id)
		{
			TCHAR pszCharParam1[50] = {'\0', };

			cltItemData*  ItemData = &pclMsg->clDstOrder.clItemData;

			StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "Unique: %d, Num: %d",
																	ItemData->siUnique, 
																	ItemData->siItemNum);

			// ��ü �ŷ��ݾ�.
			SI32 siTotalTradeMoney = pclMsg->siTradePrice * pclMsg->clTradeItem.siItemNum;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // �ý��ۿ��� ��ǰ ���� ����. 
				// param1		 == �ֹ���ȣ.
				// param2		 == ������ �ϳ��� ����.
				// param3		 == ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0) 
				// pszCharParam1 == ���� �κ��� ������ ����.
				ZeroMemory(pszCharParam1, sizeof(pszCharParam1));
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "Pos: %d, Unique: %d, Num: %d",
																		pclMsg->siItemPos, 
																		pclMsg->clItem.siUnique, 
																		pclMsg->clItem.siItemNum);


				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SYSTEM, LOGCOMMAND_INDEX_SYSTEM_USER_ITEM_BUY, 
									pclMsg->siReason, NULL, NULL, pclMsg->siSellerPersonID, 0, 0, &pclMsg->clTradeItem,  pclMsg->siTradeItemNum, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									pclMsg->clDstOrder.siIndex, pclMsg->siTradePrice, siTotalTradeMoney, 0, 0,
									pszCharParam1, NULL);
			}

			// �ý����� ������ ���忡 �ø� �������� ������ ������ ���Ϸ� ��������� ����.
			clSystemBuyItem.m_sTime    = sTime;				// ���� �ð�.
			clSystemBuyItem.m_siCnt++;						// ���� Ƚ��.
			clSystemBuyItem.m_siMoney += siTotalTradeMoney;	// �׼�.
		}
	}
}


// ���� â���� �������� ��������� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETITEMFROMMARKET(sPacketHeader* pPacket)
{
	sDBResponse_GetItemFromMarket* pclMsg = (sDBResponse_GetItemFromMarket*)pPacket;

	SI32 id = pclMsg->usCharID;

	SI32 returnval = 0;

	switch(pclMsg->siResult )
	{
	case 0:
		break;
	case 1:		
		{
			if(pclCM->IsValidID(id)== false) return;
			
			// ����� â���� ���뿡 ���� �ֹ��� �����Ѵ�.
			SI32 index				= pclMsg->clOrder.siIndex;
			if( index < 0 || index >= MAX_MARKET_ORDER_NUMBER)		return;
			SI32 orderitemunique	= pclMarketManager->pclOrderManager->pclOrderSell[index]->clItemData.siUnique;

			if(pclMarketManager->pclOrderManager->SetOrder(ORDERMODE_SELL, &pclMsg->clOrder) == true)
			{
				cltTradeOrder clorder;
				clorder.Set(&pclMsg->clOrder);
				clorder.clItemData.siUnique = orderitemunique;
				pclMarketManager->SetItemTypeOrder(&clorder, 600);
			}

			if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)	
			{
				if( pclMsg->siFromPos >= 0	&& pclMsg->siFromPos < MAX_MARKET_ORDER_PER_PERSON &&
					pclMsg->siToPos >= 0	&& pclMsg->siToPos < MAX_ITEM_PER_PERSON )
				{
					// Ŭ���̾�Ʈ���� ���� â���� �ֽ� ������ �����ش�.
					pclCM->CR[id]->pclCI->clMarket.clInfo.clItem[pclMsg->siFromPos].Set(&pclMsg->clFromItem);
					pclCM->CR[id]->SetUpdateSwitch(UPDATE_MARKET, true, 0);

					// Ŭ���̾�Ʈ���� ������Ʈ�� �κ��� ������ �����ش�. 
					pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToPos].Set(&pclMsg->clToItem);

					cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siToPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}

			returnval	= SRVAL_MARKET_SUCCESS_GETFROMMARKET; 
		}
		break;

	default:
		MsgBox(TEXT("DoMsg_DBMSG_RESPONSE_GETITEMFROMMARKET()"), TEXT("result:%d"), pclMsg->siResult);
		break;
	}
		
	if(pclCM->IsValidID(id)== false) return;

	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	if(returnval)
	{
		SendServerResponseMsg(RANKTYPE_MARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ǰ ȸ�� ����. 
			// param1 == �ֹ���ȣ. 
			// param2 == �����ġ.
			// param3 == ȸ�� ������ ����ũ.
			// param4 == ȸ�� ������ ����.
			// pszParam1 == ȸ���� �������� �κ� ��ġ, ȸ�� ������ ����ũ, ȸ���ϰ� �κ��� ���� �������� ����.
			TCHAR str[50] = {'\0', };
			StringCchPrintf(str, sizeof(str), "Pos: %d, Unique: %d, Num: %d",
											  pclMsg->siToPos, 
											  pclMsg->clToItem.siUnique, 
										  	  pclMsg->clToItem.siItemNum);

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_GETITEMFROMMARKET, 
								 0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clGetItem, pclMsg->clToItem.GetItemNum(), 0, 0, pclMsg->clOrder.siVillageUnique, 0, 0, 
								 pclMsg->clOrder.siIndex, pclMsg->siFromPos, pclMsg->clGetItem.siUnique, pclMsg->clGetItem.siItemNum, 0, str, NULL);
		}
	}
}

// ������ ���� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYITEMPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ManyItemPrice* pclMsg = (sDBResponse_ManyItemPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 i;
	// ������ ������ ���´�
	for(i = 0;i < MANYITEM_PRICE_NUMBER;i++)
	{
		if(pclMsg->siItemUnique[i])
		{
			SI32 index = pclItemManager->FindItemRefFromUnique(pclMsg->siItemUnique[i]);

			if(index > 0 && index < MAX_ITEMINFO_NUMBER) 
			{
				pclItemManager->pclItemPrice->clUnit[index].siPrice		= (SI64) pclMsg->fPrice[i];
				pclItemManager->pclItemPrice->clUnit[index].fPrice		= pclMsg->fPrice[i];
				pclItemManager->pclItemPrice->clUnit[index].siItemNum	= pclMsg->siItemNum[i];
			}
		}
	}

	// ������ �޽���
	if( -1 == pclMsg->siResult )
	{
		// ������ �ü��� ���°�� �⺻������ �����Ѵ�.	- By KKM 2007 / 08 / 22
		SI32 siItemCount = pclItemManager->siItemNum;
		if( siItemCount > MAX_ITEMINFO_NUMBER )		siItemCount = MAX_ITEMINFO_NUMBER;
		for( SI32 i=1; i<= siItemCount; ++i)
		{
			// ���߿� �ϳ��� ���������̸� �⺻���� �־��ش�.
			if(	pclItemManager->pclItemPrice->clUnit[i].siPrice <= 0 || 
				pclItemManager->pclItemPrice->clUnit[i].fPrice <= 0.001f )
			{
				pclItemManager->pclItemPrice->clUnit[i].siPrice		= BASIC_ITEMPRICE_DEFAULT;
				pclItemManager->pclItemPrice->clUnit[i].fPrice		= (float)BASIC_ITEMPRICE_DEFAULT;
			}
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_ManyItemPrice"));
}

// ������ ���� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_SETITEMPRICE(sPacketHeader* pPacket)
{

}

// ���� �ŷ� ������ ������ �����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETMARKETFEE(sPacketHeader* pPacket)
{
	
	sDBResponse_SetMarketFee* pclMsg = (sDBResponse_SetMarketFee*)pPacket;

	// ����� Ȯ���Ѵ�. 
	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case 1:	// ������ ���� ����. 
		{

			// ������ �ش� ������ ������ ������Ʈ �Ѵ�. 
			cltStrInfo* pclinfo = pclMarketManager->GetStrInfo(pclMsg->siVillageUnique);
			pclinfo->clMarketStrInfo.clFee.Set(&pclMsg->clFee);

			returnval	= SRVAL_MARKET_SUCCESSSETFEE;
		}
		break;
	default:
		MsgBox(TEXT("vc984j"), TEXT("fdd:%d"), pclMsg->siResult);
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_MARKET, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_GET_SYSTEMBUYITEMNOWMONEY(sPacketHeader* pPacket)
{
	sDBResponse_GetSystemBuyItemNowMoney* pclMsg = (sDBResponse_GetSystemBuyItemNowMoney*)pPacket;

	if(pclMsg->siResult == 1) //����
		siMarketMoneyItemMaxpriceNow = pclMsg->gPrice;
	else
		siMarketMoneyItemMaxpriceNow = 0;
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKETACCOUNT(sPacketHeader* pPacket)
{
	sDBResponse_NewMarketAccount* pclMsg = (sDBResponse_NewMarketAccount*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return ;
	}

	SI32 id  = pclMsg->usCharID;
	if( false == pclCM->IsValidID(id) )
		return;

	if( pclMsg->siPersonID != pclCM->CR[id]->pclCI->GetPersonID() )
		return;

	if( pclMsg->siServerUnique != siServerUnique )
		return;

	cltGameMsgResponse_NewMarketAccount clNewMarketAccount( &pclMsg->clMarketAccount );
	cltMsg clMsg(GAMEMSG_RESPONSE_NEWMARKETACCOUNT, sizeof(cltGameMsgResponse_NewMarketAccount), (BYTE*)&clNewMarketAccount);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKETITEMLIST(sPacketHeader* pPacket)
{
	sDBResponse_NewMarketItemList* pclMsg = (sDBResponse_NewMarketItemList*)pPacket;

	SI32 id = pclMsg->usCharID;
	if( false == pclCM->IsValidID(id) )
		return;

	SI64 currentPrice = 0;

	if( 0 < pclMsg->siItemUnique )
	{
		SI32 index = pclItemManager->FindItemRefFromUnique(pclMsg->siItemUnique);
		if(index >= 0)
		{
			currentPrice = pclItemManager->pclItemNewPrice->clUnit[index].siPrice;
		}
	}

	if(pclMsg->siResult != 1)
	{
		if( -1 == pclMsg->siResult )
		{
			cltGameMsgResponse_NewMarketItemList clNewMarketItemList( pclMsg->uiType, 1, currentPrice, pclMsg->clNewTradeOrder );
			cltMsg clMsg(GAMEMSG_RESPONSE_NEWMARKETITEMLIST, sizeof(cltGameMsgResponse_NewMarketItemList), (BYTE*)&clNewMarketItemList);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		return ;
	}

	cltGameMsgResponse_NewMarketItemList clNewMarketItemList( pclMsg->uiType, pclMsg->siMaxPage, currentPrice, pclMsg->clNewTradeOrder );
	cltMsg clMsg(GAMEMSG_RESPONSE_NEWMARKETITEMLIST, sizeof(cltGameMsgResponse_NewMarketItemList), (BYTE*)&clNewMarketItemList);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETFROMNEWMARKET(sPacketHeader* pPacket)
{
	sDBResponse_GetItemFromNewMarket* pclMsg = (sDBResponse_GetItemFromNewMarket*)pPacket;

	SI32 id = pclMsg->usCharID;
	if( false == pclCM->IsValidID(id) )
		return;

	if(pclMsg->siResult != 1)
	{
		SendServerResponseMsg( 0, SRVAL_GET_SAVEUSERITEM_FAIL,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	if( pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID )
		return;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ǰ ȸ�� ����. 
		// pszParam1 == ���� �κ��� ������ ����.
		TCHAR str[50] = {'\0', };
		StringCchPrintf(str, sizeof(str), "Pos: %d, Unique: %d, Num: %d",
										pclMsg->siToPos, 
										pclMsg->clToItem.siUnique, 
										pclMsg->clToItem.siItemNum);

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_GETITEMFROMMARKET, 
			0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clGetItem, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, str, NULL);
	}	

	//---------------------------------
	// �κ��丮 ������ ������Ʈ �Ѵ�.
	//---------------------------------
	pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siToPos].Set(&pclMsg->clToItem);

	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siToPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clToItem, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	sDBRequest_NewMarketAccount	clMsg2( id, siServerUnique, pclCM->CR[id]->pclCI->GetPersonID() );
	pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg2);

	SendServerResponseMsg( RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_SUCCESS_GETFROMMARKET,  0, 0, pclCM->CR[id]->GetCharUnique());
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETNEWMARKETFEE(sPacketHeader* pPacket)
{
	sDBResponse_SetNewMarketFee* pclMsg = (sDBResponse_SetNewMarketFee*)pPacket;

	if(pclMsg->siResult != 1)	return;

	// ������ �ش� ������ ������ ������Ʈ �Ѵ�. 
	cltStrInfo* pclStrInfo = pclNewMarketManager->GetStrInfo(pclMsg->siVillageUnique);
	if( NULL != pclStrInfo	)
	{
		pclStrInfo->clNewMarketStrInfo.clFee.Set(&pclMsg->clFee);
		pclNewMarketManager->m_bSetFee = false;
	}

	SI32 returnval	= SRVAL_NEWMARKET_SUCCESSSETFEE;

	cltCharServer* pclChar = pclCM->GetCharServer( pclMsg->siCharID );
	if( NULL == pclChar ) return;
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_NEWMARKET, returnval,  pclStrInfo->clNewMarketStrInfo.clFee.GetFeeRate(), 0, pclChar->GetCharUnique());
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWTRADEMARKET(sPacketHeader* pPacket)
{
	sDBResponse_NewTradeMarket* pclMsg = (sDBResponse_NewTradeMarket*)pPacket;

	SI32 id = pclMsg->usCharID;
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if( NULL == pclChar )	return;

	if(pclMsg->siResult != 1)
	{
		SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  500, 0, pclChar->GetCharUnique());
		return ;
	}

	// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ǰ ���� ����. 
	// param1 == ���� ����ũ.
	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NEWMARKET, LOGCOMMAND_INDEX_NEWMARKET_BUY, 
							0,	pclChar, NULL, pclMsg->siSellerPersonID, pclMsg->siTradePrice, pclMsg->siMoney, &pclMsg->clTradeItem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							pclMsg->siSellerServerUnique, 0, 0, 0, 0, NULL, NULL	);
	
	if( pclChar->pclCI->GetPersonID() != pclMsg->siBuyerPersonID )
		return;

	//---------------------------------
	// �ŷ��� ������ �����Ѵ�.
	//---------------------------------
	if( pclMsg->clItem.siUnique && 0 < pclMsg->siTradePrice )
	{
		SI32 index = pclItemManager->FindItemRefFromUnique(pclMsg->clItem.siUnique);
		if( 0 < index )
		{
			// �ü�
			if( 0 >= pclItemManager->pclItemNewPrice->clUnit[index].siPrice )
			{
				cltItemPriceUnit* pclprice = pclItemManager->GetCurrentNewPrice( pclMsg->clItem.siUnique );
				if( pclprice )
				{
					sDBRequest_SetItemNewPrice clMsg( pclprice->siUnique, MIN_ITEM_PRICE, (float)MIN_ITEM_PRICE, pclprice->siItemNum );
					pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg );
				}
			}

			pclItemManager->pclItemNewPrice->clUnit[index].siPrice		= pclMsg->fPrice;

			// ���� 0�� ���ų� �۾Ƽ��� �ȵȴ�
			if(pclItemManager->pclItemNewPrice->clUnit[index].siPrice <= 0)
			{
				pclItemManager->pclItemNewPrice->clUnit[index].siPrice	= MIN_ITEM_PRICE;
			}
			if(pclItemManager->pclItemNewPrice->clUnit[index].fPrice <= 0.001f)
			{
				pclItemManager->pclItemNewPrice->clUnit[index].fPrice	= (float)MIN_ITEM_PRICE;
			}

			pclItemManager->SetCurrentNewPrice( pclMsg->clItem.siUnique, pclMsg->siTradePrice, pclMsg->siTradeItemNum );
		}
		
		//--------------------------------
		// ���� ���� ������ ������Ʈ �Ѵ�. 
		//--------------------------------
		pclChar->pclCI->clIP.SetMoney(pclMsg->siMoney);
		pclChar->SetUpdateSwitch(UPDATE_IP, true, 0);

		//---------------------------------
		// �κ��丮 ������ ������Ʈ �Ѵ�.
		//---------------------------------
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_BUYFROMNEWMARKET, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclChar->SendNetMsg((sPacketHeader*)&clMsg);

			// Ȥ�� OBJECT�� �ƴϸ鼭 �Ⱓ�� ������ �������̸� ����������.
			SI32 atb = pclItemManager->GetItemAtb(pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].siUnique);
			if ( ( atb & ITEMATB_OBJECT ) == 0 )
			{
				if ( pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateYear   > 0 ||
					 pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateMonth  > 0 ||
					 pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateDay    > 0 ||
					 pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateUseDay > 0	)
				{
					pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateYear   = 0;
					pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateMonth  = 0;
					pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateDay    = 0;
					pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos].uiDateUseDay = 0;

					// ������Ʈ�� �ƴ� ���� �����̹Ƿ� �Ⱓ�� ���ֹ�����
					sDBRequest_WasteDurability clMsg(	id, 
														pclChar->pclCI->GetPersonID(), 
														pclMsg->siItemPos,
														&pclChar->pclCI->clCharItem.clItem[pclMsg->siItemPos]	);
					
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}

			SendServerResponseMsg( RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_SUCCESS_TRADE,  0, 0, pclChar->GetCharUnique() );
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWORDERMARKET(sPacketHeader* pPacket)
{
	sDBResponse_NewOrderMarket* pclMsg = (sDBResponse_NewOrderMarket*)pPacket;

	SI32 id = pclMsg->usCharID;

	SI32 returnval = 0;
	// Ŭ���̾�Ʈ�� ��ȿ�� �����, 
	if(pclCM->IsValidID(id)== FALSE) return ;

	switch(pclMsg->siResult )
	{
	case 0:	
		break;
	case -1:
		{
			SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_ORDERSELL_OVERFLOW,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		break;
	case -5:
		{
			SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_ORDERSELL_ALREADY_ORDERED,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		break;
	case 1:		
		{
			if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->clOrder.siPersonID)	
			{
				//---------------------------------
				// �κ��丮 ������ ������Ʈ �Ѵ�.
				//---------------------------------
				pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemFromPos].Set(&pclMsg->clFromItem);

				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemFromPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clFromItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				//-------------------------------
				// ������ �����Ѵ�. 
				//-------------------------------
				if( 0 < pclMsg->siTax )
				{
					if(pclCM->CR[id]->pclCI->clIP.GetMoney() >= pclMsg->siTax)
					{
						pclCM->CR[id]->pclCI->clIP.SetMoney( pclCM->CR[id]->pclCI->clIP.GetMoney() - pclMsg->siTax );
						SI64 tempUserMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();
						SI16 modUserMoney  = UserMoneyCapsule(tempUserMoney);

						sDBRequest_ChangeMoney clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_USENEWMARKET, -pclMsg->siTax );
						pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

						CMinisterGoonzu *pclminister = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
						pclminister->AddTempFinances( pclMsg->siTax / 2); // �����ῡ 50% �� �������� ������� 50%�� ����ݰ� �ִ´�.

						// ��ȭ�� ���� 
						cltMoney clmoney;
						clmoney.Set(pclMsg->siTax / 2);
						clCurrencyInfo.clOutputMoney_clNewMarketTax.Increase(&clmoney); 
					}
				}

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					cltItem clOrderItem;
					clOrderItem.Set(&pclMsg->clOrder.clItemData);
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ǰ ��� ����. 
					// param1	 == �ֹ���ȣ. 
					// param2	 == �ֹ� ���� ����. 
					// param3    == ����.
					// pszParam1 == �Ǹ� �ֹ��� �������� �κ� ��ġ, �Ĵ� ������ ����ũ, �ֹ��ϰ� ���� �������� ����.
					TCHAR str[50];
					StringCchPrintf(str, sizeof(str), "Pos: %d, Unique: %d, Num: %d",
									pclMsg->siItemFromPos, 
									clOrderItem.siUnique, 
									clOrderItem.siItemNum);
					SendLog_WriteLogToDB( LOGCOMMAND_TYPE_NEWMARKET, LOGCOMMAND_INDEX_NEWMARKET_ORDER, 
											0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &clOrderItem, pclMsg->clFromItem.GetItemNum(), 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->clOrder.siOrderIndex, pclMsg->clOrder.siPrice, pclMsg->siTax, 0, 0, str, NULL);
				}
			}

			SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_SUCCESS_ORDERSELL,  0, 0, pclCM->CR[id]->GetCharUnique());			
		}
		break;
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKETRESULT(sPacketHeader* pPacket)
{
	sDBResponse_NewMarketResult* pclMsg = (sDBResponse_NewMarketResult*)pPacket;

	if( 1 != pclMsg->siResult )
	{
		return;
	}

	for( SI16 i = 0; i < MAX_NEWMARKET_RESULTLIST; ++i )
	{
		SI32 personID = pclMsg->stSellerInfo[i].siSellerPersonID;
		if( 0 < personID )
		{
			SI32 id = pclCM->GetIDFromPersonID( personID );
			SI16 itemUnique		= pclMsg->stSellerInfo[i].siSellItemUnique;
			SI32 itemNum		= pclMsg->stSellerInfo[i].siSellItemNum;
			SI64 price			= pclMsg->stSellerInfo[i].siSellPrice;
			SI32 villageUnique	= pclMsg->stSellerInfo[i].siVillageUnique;

			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ǰ �Ǹ� ����. 
			// pszCharParam1 == ������ȣ, ������ ����ũ, ����.
			TCHAR pszStrParam1[50] = {'\0', };
			StringCchPrintf(pszStrParam1, sizeof(pszStrParam1), "Server : %d, Unique: %d, Num: %d",
																pclMsg->siServerUnique,
																itemUnique, 
																itemNum		);
			
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NEWMARKET, LOGCOMMAND_INDEX_NEWMARKET_SELL, 
									0,	0, 	NULL, personID, price, 0, NULL, 0, 0, 0, villageUnique, 0, 0, 
									0, 0, 0, 0, 0, pszStrParam1, NULL	);

			if( false == pclCM->IsValidID(id) )
			{
				if( 0 < itemUnique )
				{
					if( 0 < price)
					{
						sDBRequest_NewMarket_IncreaseBankMoney clMsg( 0, personID, price );
						pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
					}

					//---------------------------------------------
					// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
					//--------------------------------------------
					cltStrInfo* pclstrinfo = pclNewMarketManager->GetStrInfo(villageUnique);
					if(pclstrinfo == NULL)
						return;

					SI64 fee = pclstrinfo->clNewMarketStrInfo.clFee.CalcFee( price ); 
 
					if( 0 < fee )
					{
						cltMoney clmoney;
						clmoney.itMoney = fee; // ���ո����� ������ �����Ѵ�.
						sDBRequest_PayFee clinfo( 0, personID, villageUnique, RANKTYPE_NEWMARKET, FEETYPE_NEWMARKET_SELL, &clmoney);
						pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);
					}

					// ������ ������.
					cltLetterMsg_MarketTrade clletter( itemUnique, itemNum, price, fee, cltLetterMsg_MarketTrade::TYPE_NEWMARKET );
					SendLetterMsg( personID, (cltLetterHeader*)&clletter );
				}
			}
			else
			{
				if( 0 < itemUnique )
				{
					if( 0 < price)
					{
						sDBRequest_NewMarket_IncreaseBankMoney clMsg( id, personID, price );
						pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
					}

					//---------------------------------------------
					// ���� �� ����� ���¿��� �����Ḧ �����Ѵ�. 
					//--------------------------------------------
					cltStrInfo* pclstrinfo = pclNewMarketManager->GetStrInfo(villageUnique);
					if(pclstrinfo == NULL)
						return;

					SI64 fee = pclstrinfo->clNewMarketStrInfo.clFee.CalcFee( price);

					if( 0 < fee )
					{
						cltMoney clmoney;
						clmoney.itMoney = fee;
						sDBRequest_PayFee clinfo( id, personID, villageUnique, RANKTYPE_NEWMARKET, FEETYPE_NEWMARKET_SELL, &clmoney);
						pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);
					}

					// ������ ������.
					cltLetterMsg_MarketTrade clletter( itemUnique, itemNum, price, fee, cltLetterMsg_MarketTrade::TYPE_NEWMARKET );
					SendLetterMsg( personID, (cltLetterHeader*)&clletter );
				}
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKET_SETITEMPRICE(sPacketHeader* pPacket)
{
	//sDBResponse_NewMarketResult* pclMsg = (sDBResponse_NewMarketResult*)pPacket;

	//if( 1 != pclMsg->siResult )
	//{
	//	return;
	//}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKET_INCREASEBANKMONEY(sPacketHeader* pPacket)
{
	sDBResponse_NewMarket_IncreaseBankMoney* pclMsg = (sDBResponse_NewMarket_IncreaseBankMoney*)pPacket;

	if( 1 != pclMsg->siResult )
	{
		return;
	}

	//-------------------------------
	// ToBank ������Ʈ. 
	//-------------------------------
	SI32 villageUnique = pclMsg->siVillageUnique;
	if( 0 < villageUnique )
	{
		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageUnique);
		if(pclinfo)
		{
			pclinfo->clBankStrInfo.clTotalInputMoney.Set(&pclMsg->clTotalInputMoney);
			pclinfo->clCommonInfo.clMoney.Set(&pclMsg->clCurrentLeftMoney);
		}
	}

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if( false == pclCM->IsValidID(id) )
	{
		return;
	}

	pclCM->CR[id]->pclCI->clBank.SetMoney( pclMsg->clTotalMoney.itMoney );
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);
}

// ������ ���� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYITEMNEWPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ManyItemNewPrice* pclMsg = (sDBResponse_ManyItemNewPrice*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return ;
	}

	SI32 i;

	// ������ ������ ���´�
	for(i = 0;i < MANYITEM_PRICE_NUMBER;i++)
	{
		if( 0 < pclMsg->siItemUnique[i] )
		{
			SI32 index = pclItemManager->FindItemRefFromUnique(pclMsg->siItemUnique[i]);
			if( 0 < index )
			{
				pclItemManager->pclItemNewPrice->clUnit[index].siPrice		= pclMsg->fPrice[i];
				pclItemManager->pclItemNewPrice->clUnit[index].fPrice		= pclMsg->fPrice[i];
				pclItemManager->pclItemNewPrice->clUnit[index].siItemNum	= pclMsg->siItemNum[i];

				// ���� 0�� ���ų� �۾Ƽ��� �ȵȴ�
				if(pclItemManager->pclItemNewPrice->clUnit[index].siPrice <= 0)
				{
					pclItemManager->pclItemNewPrice->clUnit[index].siPrice	= MIN_ITEM_PRICE;
				}
				if(pclItemManager->pclItemNewPrice->clUnit[index].fPrice <= 0.001f)
				{
					pclItemManager->pclItemNewPrice->clUnit[index].fPrice	= (float)MIN_ITEM_PRICE;
				}
			}
		}
	}

}

// ������ ���� ��û�� ���� ���� �Ϸ�
void cltServer::DoMsg_DBMSG_RESPONSE_MANYITEMNEWPRICE_COMPLETED(sPacketHeader* pPacket)
{
	sDBResponse_ManyItemNewPrice_Completed* pclMsg = (sDBResponse_ManyItemNewPrice_Completed*)pPacket;

	if(pclMsg->siResult != 1)
	{
		return ;
	}

	for(SI32 i = 0; i < MAX_ITEMINFO_NUMBER; ++i)
	{
#ifdef _DEBUG
		pclLog->FilePrint( "newitemprice.txt", "%d	%I64d %d", pclItemManager->pclItemNewPrice->clUnit[i].siUnique,
			pclItemManager->pclItemNewPrice->clUnit[i].siPrice, pclItemManager->pclItemNewPrice->clUnit[i].siItemNum );
#endif
		if(pclItemManager->pclItemNewPrice->clUnit[i].siUnique <= 0)	continue;
		if(pclItemManager->pclItemNewPrice->clUnit[i].siPrice > 0)		continue;

		pclItemManager->pclItemNewPrice->clUnit[i].siPrice	= MIN_ITEM_PRICE;
		pclItemManager->pclItemNewPrice->clUnit[i].fPrice	= (float)MIN_ITEM_PRICE;
	}

	pclNewMarketManager->bUpdateItemPrice = true;
}

// ������ ���� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_SETITEMNEWPRICE(sPacketHeader* pPacket)
{

}

// ������ ���� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_NEWMARKETREDUCEPRICENOTICE(sPacketHeader* pPacket)
{
	sDBResponse_NewMarketReducePriceNotice* pclMsg = (sDBResponse_NewMarketReducePriceNotice*)pPacket;

	if( 1 !=  pclMsg->siResult )
		return;

	for( SI16 i = 0 ; i < MAX_REDUCEPRICE_USERLIST; ++i )
	{		
		if( 0 < pclMsg->stData[ i ].siPersonID )
		{
			cltLetterMsg_MarketPriceDown clletter( pclMsg->stData[ i ].siItemUnique, pclMsg->stData[ i ].siItemQty, pclMsg->stData[ i ].clPrice.itMoney, cltLetterMsg_MarketPriceDown::TYPE_NEWMARKET );
			SendLetterMsg( pclMsg->stData[ i ].siPersonID, (cltLetterHeader*)&clletter);
		}
	}
}



