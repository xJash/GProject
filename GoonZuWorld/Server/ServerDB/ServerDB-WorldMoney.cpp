//---------------------------------
// SJY 2005/12/06
//---------------------------------

#include "Char/CharManager/CharManager.h"
#include "Letter/Letter.h"

#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"

#include "../../CommonLogic/Msg/MsgType-WorldMoney.h"

#include "../../CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"
#include "../../CommonLogic/WorldTraderMgr/WorldTraderManager.h"

#include "../../CommonLogic/MsgRval-Define.h"
#include "../../CommonLogic/Msg/MsgType-Quest.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"


void cltServer::DoMsg_DBMSG_RESPONSE_DISTRIBUTION_WORLDMONEY( sPacketHeader* pPacket )
{
	sDBResponse_Distribution_WorldMoney* pclinfo = (sDBResponse_Distribution_WorldMoney*)pPacket;

	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return ;

	pclchar->pclCI->clIP.SetMoney(pclinfo->siLeftMoney);
	pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

	cltGameMsgResponse_Distrubution_WorldMoney clinfo(pclinfo->siWorldMoney,pclinfo->siLeftWorldMoney,pclinfo->siMoney,pclinfo->siLeftMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_DISTRIBUTION_WORLDMONEY, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť ����.
		// param1 == ��� ��ť�� ��, param2 == �� ���� ��ť�� ��
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_DISTRIBUTION, 
							0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, pclinfo->siMoney, pclinfo->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0, 
							pclinfo->siWorldMoney, pclinfo->siLeftWorldMoney, 0, 0, 0, NULL, NULL);
	}
	return ;
}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_TRADELIST( sPacketHeader* pPacket )
{
	sDBResponse_WorldMoney_TradeList* pclinfo = (sDBResponse_WorldMoney_TradeList*)pPacket;

	if ( pclinfo->siResult != 1 )
		return ;

	if ( pclinfo->siPage < 0 || pclinfo->siPage >= MAX_WORLDMONEY_TRADELIST_NUM )
		return ;

	for ( SI32 i = pclinfo->siPage ; i < pclinfo->siPage + MAX_WORLDMONEY_TRADELIST_PER_SEND ; i ++ )
	{
		// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
		if (i < 0 || i >= MAX_WORLDMONEY_TRADELIST_NUM)		continue;
		if ( (i-pclinfo->siPage) < 0 || (i-pclinfo->siPage) >= MAX_WORLDMONEY_TRADELIST_PER_SEND )	continue;

		pclDistributionWorldMoney->clTradeList[i].Set(pclinfo->siWorldMoney[i-pclinfo->siPage],
			pclinfo->siPrice[i-pclinfo->siPage],
			pclinfo->siPersonID[i-pclinfo->siPage],
			pclinfo->siDate[i-pclinfo->siPage]);
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_WorldMoney_TradeList"));

}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_SELLORDER( sPacketHeader* pPacket )
{
	sDBResponse_WorldMoney_SellOrder* pclinfo = (sDBResponse_WorldMoney_SellOrder*)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if (pclinfo->siListIndex < 0 || pclinfo->siListIndex >= MAX_WORLDMONEY_TRADELIST_NUM )
		return;

	SI32 id = pclinfo->usCharId ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return ;

	// ����Ʈ�� ����Ѵ�.
	pclDistributionWorldMoney->clTradeList[pclinfo->siListIndex].Set(pclinfo->siWorldMoney,pclinfo->siPrice,
		pclinfo->siPersonID,pclinfo->siDate) ;

	// �Ǹ����� ������ �����Ѵ�.
	pclchar->pclCI->clIP.SetMoney(pclinfo->siLeftMoney); // ���� ��ť
	pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney); // ���� ��
	pclchar->pclCI->clWorldMoney.siTradeWorldMoney = pclinfo->siWorldMoney ; // �ø� ��ť
	pclchar->pclCI->clWorldMoney.siTradeWorldMoneyPrice = pclinfo->siPrice ; // �ø� ����

	cltGameMsgResponse_WorldMoney_SellOrder clinfo(pclinfo->siResult,pclinfo->siWorldMoney,pclinfo->siLeftWorldMoney,pclinfo->siPrice,pclinfo->siLeftMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_WORLDMONEY_SELLORDER, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť �Ǹ� ���.
		// param1 == ��� ��ť�� ��, param2 == �� ���� ��ť�� ��, param3 == �� ��ť�� ���� 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_SELL_ORDER, 
							0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, pclinfo->siFee, pclinfo->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0, 
							pclinfo->siWorldMoney, pclinfo->siLeftWorldMoney, pclinfo->siPrice, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_BUYORDER( sPacketHeader* pPacket )
{
	sDBResponse_WorldMoney_BuyOrder* pclinfo = (sDBResponse_WorldMoney_BuyOrder*)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if ( pclinfo->siListIndex < 0 || pclinfo->siListIndex >= MAX_WORLDMONEY_TRADELIST_NUM )
		return ;

	SI32 id = pclinfo->usCharId ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return ;

	// ����Ʈ�� �����Ѵ�.
	pclDistributionWorldMoney->clTradeList[pclinfo->siListIndex].Set(pclinfo->siLeftListWorldMoney,pclinfo->siPrice,
		pclinfo->siSellerPersonID,
		pclDistributionWorldMoney->clTradeList[pclinfo->siListIndex].siDate);

	if ( pclinfo->siLeftListWorldMoney == 0 ) // �� �ȸ� �ǰ�?
	{
		pclDistributionWorldMoney->clTradeList[pclinfo->siListIndex].Set(0,0,0,0);
	}

	// �������� ������ �����Ѵ�.
	pclchar->pclCI->clIP.SetMoney(pclinfo->siLeftMoney);
	pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

	// PCK : ��ť�� �� ���� ����
	SI32 siWorldMoneySum = pclinfo->siWorldMoney * pclinfo->siPrice;

	// �Ǹ����� ������ �����Ѵ�.
	if ( pclinfo->siSellerPersonID > 0 )
	{
		SI32 sellerID = pclCM->GetIDFromPersonID(pclinfo->siSellerPersonID);
		if ( IsPC(sellerID) )
		{
			pclCM->CR[sellerID]->pclCI->clBank.SetMoney(pclinfo->siSellerBankMoney);

			pclCM->CR[sellerID]->pclCI->clWorldMoney.siTradeWorldMoney = pclinfo->siLeftListWorldMoney ;
			if ( pclinfo->siLeftListWorldMoney == 0 )
			{
				pclCM->CR[sellerID]->pclCI->clWorldMoney.siTradeWorldMoneyPrice = 0 ;
			}

			pclCM->CR[sellerID]->SetUpdateSwitch(UPDATE_BANK,true,0);
			pclCM->CR[sellerID]->SetUpdateSwitch(UPDATE_WORLDMONEY,true,0);
		}

		cltLetterMsg_WorldMoneyTradeResult clletter(pclinfo->siWorldMoney,pclinfo->siWorldMoney*pclinfo->siPrice);
		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
		SendLetterMsg(pclinfo->siSellerPersonID, (cltLetterHeader*)&clletter);
	}

	cltGameMsgResponse_WorldMoney_BuyOrder clinfo(pclinfo->siResult,pclinfo->siWorldMoney,pclinfo->siLeftWorldMoney,pclinfo->siLeftMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_WORLDMONEY_BUYORDER, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť ����.
		// param1 == �� ��ť. param2 == �� ���� �� ��ť
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_BUY, 
							0, (cltCharServer*)(pclCM->CR[id]), NULL, pclinfo->siSellerPersonID, siWorldMoneySum, pclinfo->siLeftMoney, NULL, 0, 0, 0, 0, 0, 0, 
							pclinfo->siWorldMoney, pclinfo->siLeftWorldMoney, 0, 0, 0, NULL, NULL);
	}
	
	SI64 averageprice = pclDistributionWorldMoney->SetAverageWorldMoney(pclinfo->siWorldMoney,pclinfo->siPrice);

	sDBRequest_WorldMoney_SetAveragePrice clMsg2(averageprice);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg2);

	// ����Ʈ�� �����Ѵ�.
	//pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_TRYTOBUYACU);

}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_CANCELORDER( sPacketHeader* pPacket )
{
	sDBResponse_WorldMoney_CancelOrder* pclinfo = (sDBResponse_WorldMoney_CancelOrder*)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if ( pclinfo->siListIndex < 0 || pclinfo->siListIndex >= MAX_WORLDMONEY_TRADELIST_NUM )
		return ;

	SI32 id = pclinfo->usCharId ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )
		return ;

	// ����Ʈ�� �����Ѵ�.
	pclDistributionWorldMoney->clTradeList[pclinfo->siListIndex].Set(0,0,0,0);

	// ������� ������ �����Ѵ�.
	pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
	pclchar->pclCI->clWorldMoney.siTradeWorldMoney = 0 ;
	pclchar->pclCI->clWorldMoney.siTradeWorldMoneyPrice = 0 ;

	cltGameMsgResponse_WorldMoney_CancelOrder clinfo(pclinfo->siResult,pclinfo->siLeftWorldMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_WORLDMONEY_CANCELORDER, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť �Ǹ� ��� ���.
		// param1 == ����Ʈ������ �ε���, param2 == ����ϰ� ���� ���� ��ť��.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_CANCEL_ORDER, 
							0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
							pclinfo->siListIndex, pclinfo->siLeftWorldMoney, 0, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_SETAVERAGEPRICE(sPacketHeader*pPacket)
{
	sDBResponse_WorldMoney_SetAveragePrice* pclinfo = (sDBResponse_WorldMoney_SetAveragePrice*)pPacket;

	if ( pclinfo->siResult == 1 )
	{
		pclDistributionWorldMoney->siAverageWorldMoneyPrice = pclinfo->siAverageWorldMoneyPrice ;

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť ��� ����.
			// param1 == ��� ��ť ����.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_AVERAGE_PRICE, 
								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								pclinfo->siAverageWorldMoneyPrice, 0, 0, 0, 0, NULL, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_REDUCEPRICE(sPacketHeader*pPacket)
{
	sDBResponse_WorldMoney_ReducePrice * pclinfo = (sDBResponse_WorldMoney_ReducePrice*)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if ( pclinfo->siIndex < 0 || pclinfo->siIndex >= MAX_WORLDMONEY_TRADELIST_NUM )
		return ;

	if ( pclinfo->siResult == 1 )
	{
		pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siDate = pclinfo->siDate ;
		pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPrice = pclinfo->siPrice ;

		cltLetterMsg_WorldMoneyReducePrice clletter(pclinfo->siPrice,pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siWorldMoney,
			pclinfo->siDate);
		// ������ DB�� Ŭ���̾�Ʈ���� ������. 
		SendLetterMsg(pclinfo->siPersonID, (cltLetterHeader*)&clletter);

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [�α��߰� : Ȳ���� 2007. 10. 18] // ��ť�� ������ ������.
		//	// param1 == �����, param2 == ����� �ֹ��� �ε���, param3 == ����� ����, param4 == ��ť. param5 == �ð�.
		//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_REDUCE_PRICE, 
		//						0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		//						pclinfo->siResult, 
		//						pclinfo->siIndex,
		//						pclinfo->siPrice, 
		//						pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siWorldMoney,
		//						pclinfo->siDate, NULL, NULL);
		//}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDMONEY_SET_CHAR(sPacketHeader*pPacket)
{
	sDBResponse_WorldMoney_Set_Char * pclinfo = (sDBResponse_WorldMoney_Set_Char*)pPacket;

	SI32 id = pclinfo->siCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult == 1 )
	{
		pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);
		pclchar->SetUpdateSwitch(UPDATE_WORLDMONEY,true,0);

		TCHAR* name = (TCHAR*)pclchar->GetName();

		cltGameMsgResponse_WorldMoney_Set_Char clinfo(name, pclinfo->siWorldMoney,pclinfo->siLeftWorldMoney);
		cltMsg clMsg(GAMEMSG_RESPONSE_WORLDMONEY_SET_CHAR, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��ť �߰�. 
			// param1 == ��ť, param2 == ���� ��ť. pszParam1 == �̸�. 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_MONEY, LOGCOMMAND_INDEX_WORLD_MONEY_ADD, 
								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								pclinfo->siWorldMoney, pclinfo->siLeftWorldMoney, 0, 0, 0, name, NULL);
		}
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_TRADESERVER_SETORDER( sPacketHeader* pPacket )
{
	sDBResponse_TradeServer_SetOrder* pclinfo = (sDBResponse_TradeServer_SetOrder*)pPacket;

	if ( pclinfo->siResult == 1 )
	{
		SI32 siID = pclinfo->siCharID ;
		if ( pclCM->IsValidID(siID) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
			if( pclchar == NULL )													return;
			if( pclinfo->siPos < 0 || pclinfo->siPos >= MAX_ITEM_PER_PERSON )		return;

			// ���� �������̶� ��ť�� �����Ѵ�.
			pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
			pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

			cltGameMsgResponse_TradeServer_Set_SellOrder clinfo(pclinfo->siResult,&pclinfo->clOrder,pclinfo->siPos,&pclinfo->clLeftItem,
				pclinfo->siLeftWorldMoney);
			cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_SET_SELLORDER, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			// Ʈ���̵����̶�� ��� ���� Ǯ������!
			pclchar->SetNoMoveItemSwitch(pclinfo->siPos,false);

			// ���� ���� �������� �ŷ��� ������
			pclchar->bTradeServerUsing = false ;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 11] // ���� ���� �������� �Ǹ� ���.
				// param1 == ������ ����ũ, 
				// param2 == ������ ��ġ,
				// param3 == ������ ����
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TRADE_SERVER, LOGCOMMAND_INDEX_TRADE_SERVER_SELL_ORDER, 
												0, (cltCharServer*)pclchar, NULL, 0, pclinfo->siWorldMoneyFee, pclinfo->siLeftWorldMoney, NULL, 0, 0, 0, 0, 0, 0, 
												pclinfo->clOrder.clitem.siUnique, pclinfo->siPos, pclinfo->clOrder.clitem.siItemNum, 0, 0, 
												NULL, NULL);
			}
		}
	}
	else
	{
		SI32 siID = pclinfo->siCharID ;
		if ( pclCM->IsValidID(siID) )
		{
			cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
			if ( pclchar == NULL )													return;
			if( pclinfo->siPos < 0 || pclinfo->siPos >= MAX_ITEM_PER_PERSON )		return;

			if ( pclchar->pclCI->GetPersonID() == pclinfo->siPersonID )
			{
				// Ʈ���̵����̶�� ��� ���� Ǯ������!
				pclchar->SetNoMoveItemSwitch(pclinfo->siPos,false);

				// ���� ���� �������� �ŷ��� ������
				pclchar->bTradeServerUsing = false ;
			}
		}

	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_TRADESERVER_CANCELORDER( sPacketHeader* pPacket )
{
	sDBResponse_TradeServer_CancelOrder* pclinfo = (sDBResponse_TradeServer_CancelOrder*)pPacket;

	SI32 siID = pclinfo->siCharID ;
	if ( pclCM->IsValidID(siID) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if( pclchar == NULL )													return;
	if( pclinfo->siPos < 0 || pclinfo->siPos >= MAX_ITEM_PER_PERSON )		return;

	// ����Ǿ� �ִ� �ڸ��� �����Ѵ�.
	pclchar->SetInputItemReserve(pclinfo->siPos,0);

	// ���� ���� �������� �ŷ��� ������
	pclchar->bTradeServerUsing = false ;

	if ( pclinfo->siResult == 1 )
	{
		//SI32 siID = pclinfo->siCharID ;
		//if ( pclCM->IsValidID(siID) )
		//{
		//	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
		//	if ( pclchar == NULL )
		//		return ;

		//	// ���� �������� �����Ѵ�.
		//	pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);

		//	// ����Ʈ�� �����Ѵ�.
		//	//pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].Set(&pclinfo->clOrder);
		//	pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].Init();

		//	cltGameMsgResponse_TradeServer_Cancel_SellOrder clinfo(pclinfo->siResult,&pclinfo->clOrder,pclinfo->siPos,&pclinfo->clLeftItem);
		//	cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_CANCEL_SELLORDER,sizeof(clinfo),(BYTE*)&clinfo);
		//	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		//}

		// ���� �������� �����Ѵ�.
		pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);

		cltGameMsgResponse_TradeServer_Cancel_SellOrder clinfo(pclinfo->siResult,&pclinfo->clOrder,pclinfo->siPos,&pclinfo->clLeftItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_CANCEL_SELLORDER,sizeof(clinfo),(BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		
		
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ���� ���� �������� �Ǹ� ���.				
			// param1 == ������ ����ũ
			// param2 == ��ġ
			// param3 == �ֹ���ȣ
			// param4 == ĳ���� ������ȣ
			// param5 == ���� ��ȣ
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TRADE_SERVER, LOGCOMMAND_INDEX_TRADE_SERVER_CANCEL_SELL, 
											0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclinfo->clOrder.clitem.siUnique, pclinfo->siPos, pclinfo->clOrder.siIndex, pclinfo->clOrder.siCharNation, pclinfo->clOrder.siServerIndex, NULL, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_TRADESERVER_BUYITEM( sPacketHeader* pPacket )
{
	sDBResponse_TradeServer_BuyItem* pclinfo = (sDBResponse_TradeServer_BuyItem*)pPacket;

	SI32 siID = pclinfo->siCharID ;
	if ( pclCM->IsValidID(siID) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( pclchar == NULL )													return;
	if( pclinfo->siPos < 0 || pclinfo->siPos >= MAX_ITEM_PER_PERSON )		return;

	// ����Ǿ� �ִ� �ڸ��� �����Ѵ�.
	pclchar->SetInputItemReserve(pclinfo->siPos,0);

	// ���� ���� �������� �ŷ��� ������
	pclchar->bTradeServerUsing = false ;

	if ( pclinfo->siResult == 1 )
	{
		//SI32 siID = pclinfo->siCharID ;
		//if ( pclCM->IsValidID(siID) )
		//{
		//	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
		//	if ( pclchar == NULL )
		//		return ;

		//	pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
		//	pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

		//	cltGameMsgResponse_TradeServer_Set_BuyOrder clinfo( pclinfo->siResult,&pclinfo->clOrder,pclinfo->siPos,
		//		&pclinfo->clLeftItem,pclinfo->siLeftWorldMoney);
		//	cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_SET_BUYORDER,sizeof(clinfo),(BYTE*)&clinfo);
		//	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		//}

		pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].Set(&pclinfo->clLeftItem);
		pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

		cltGameMsgResponse_TradeServer_Set_BuyOrder clinfo( pclinfo->siResult,&pclinfo->clOrder,pclinfo->siPos,
			&pclinfo->clLeftItem,pclinfo->siLeftWorldMoney);
		cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_SET_BUYORDER,sizeof(clinfo),(BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		//�������� ���Թ�ǰ ��� �߰�
		pclItemManager->AddWorldTradeIncomeItemNum(pclinfo->clLeftItem.siUnique, pclinfo->clLeftItem.siItemNum);

		// ���ο� ��� - ���������� ���� ���Թ�ǰ�� ��踦 ����.
		NStatistics_Add("Item", pclinfo->clLeftItem.siUnique, "TradeIncome", pclinfo->clLeftItem.siItemNum);
		NStatistics_Set("Item", pclinfo->clLeftItem.siUnique, "Name", (const char*)pclItemManager->GetName(pclinfo->clLeftItem.siUnique));

		// ����Ʈ�� �����Ѵ�.
		//pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_TRYTOBUYIMPORTS);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11]  // ���� ���� �������� ����.				
			// param1	 == ������ ����ũ,  param2 == ������ ��ġ, param3 == ������ ����
			// pszParam1 ==  �ֹ�ǰ ��ġ
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TRADE_SERVER, LOGCOMMAND_INDEX_TRADE_SERVER_BUY, 
											0, (cltCharServer*)pclchar, NULL, 0, 0, pclinfo->siLeftWorldMoney, NULL, 0, 0, 0, 0, 0, 0, 
											pclinfo->clOrder.clitem.siUnique, pclinfo->siPos, pclinfo->clOrder.clitem.siPrice, 0, 0, 0, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_TRADESERVER_SET_SELLINFO( sPacketHeader* pPacket )
{
	sDBResponse_TradeServer_Set_SellInfo* pclinfo = ( sDBResponse_TradeServer_Set_SellInfo*)pPacket;

	if ( pclinfo->siResult == 1 )
	{
		if ( pclinfo->clOrder.siPersonID > 0 )
		{
			SI32 siID = 0;
			siID = pclCM->GetIDFromPersonID(pclinfo->clOrder.siPersonID);

			// ���� ������ �����Ѵٸ�
			if ( IsPC(siID) && pclCM->IsValidID(siID) && pclCM->CR[siID]->pclCI->GetPersonID() == pclinfo->clOrder.siPersonID )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
				if ( pclchar == NULL )
					return ;

				pclchar->pclCI->clWorldMoney.SetWorldMoney(pclinfo->siLeftWorldMoney);

				cltGameMsgResponse_TradeServer_Get_SellInfo clinfo(&pclinfo->clOrder,pclinfo->siLeftWorldMoney);
				cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_GET_SELLINFO,sizeof(clinfo),(BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}

			if ( pclinfo->clOrder.siIndex >= 0 )//&& pclinfo->clOrder.siIndex < MAX_TRADESERVER_ORDER_LIST )
			{
				//	pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].Init() ;

				//if ( pclNTradeServerProcess )
				if ( pclNTradeServerProcess && pclNTradeServerProcess->GetTradeServerServersSession()->GetState() == SESSION_STATE_ESTABLISHED )
				{
					NTradeServerRequest_Del_SellInfo clMsg(&pclinfo->clOrder);
					pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);
				}
				else
				{
					TCHAR* itemname = (TCHAR*)pclItemManager->GetName(pclinfo->clOrder.clitem.siUnique);
					if ( itemname )
					{
						pclLog->FilePrint("Config\\TradeServerSellError.log","Session NULL : ID[%d] Item[%s] Num[%d] Price[%I64d]",
							pclinfo->clOrder.siPersonID,itemname,pclinfo->clOrder.clitem.siItemNum,pclinfo->clOrder.clitem.siPrice);
					}
				}
			}
			else
			{
				TCHAR* itemname = (TCHAR*)pclItemManager->GetName(pclinfo->clOrder.clitem.siUnique);
				if ( itemname )
				{
					pclLog->FilePrint("Config\\TradeServerSellIndexError.log","List Error : Index[%d] ID[%d] Item[%s] Num[%d] Price[%I64d]",
						pclinfo->clOrder.siIndex,pclinfo->clOrder.siPersonID,itemname,pclinfo->clOrder.clitem.siItemNum,
						pclinfo->clOrder.clitem.siPrice);
				}
			}

			cltLetterMsg_TradeServerSell clletter(pclinfo->clOrder.clitem.siUnique,pclinfo->clOrder.clitem.siItemNum,
				pclinfo->clOrder.clitem.siPrice,
				pclinfo->szBuyerServer,pclinfo->szBuyerName);
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclinfo->clOrder.siPersonID, (cltLetterHeader*)&clletter);


			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 11] // �����ŷ�.
				// param1	 == ������ ����ũ, 
				// param2	 == ������ ����, 
				// pszParam1 == �� ����� �ִ� ����, 
				// pszParam1 == �� ����� �̸�.  
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TRADE_SERVER, LOGCOMMAND_INDEX_TRADE_SERVER_SELLED, 
												0, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
												pclinfo->clOrder.clitem.siUnique, pclinfo->clOrder.clitem.siItemNum, 
												pclinfo->clOrder.clitem.siPrice, 0, 0, 
												pclinfo->szBuyerServer, pclinfo->szBuyerName);
			}

			//�������� ���⹰ǰ ��� �߰�
			pclItemManager->AddWorldTradeExportItemNum(pclinfo->clOrder.clitem.siUnique,pclinfo->clOrder.clitem.siItemNum);

			// ���ο� ��� - ���������� ���� ���⹰ǰ�� ��踦 ����.
			NStatistics_Add("Item", pclinfo->clOrder.clitem.siUnique, "TradeExport", pclinfo->clOrder.clitem.siItemNum);
			NStatistics_Set("Item", pclinfo->clOrder.clitem.siUnique, "Name", pclItemManager->GetName(pclinfo->clOrder.clitem.siUnique));
		}
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU( sPacketHeader* pPacket )
{
	sDBResponse_TradeServer_Get_Withdraw_Acu* pclInfo = (sDBResponse_TradeServer_Get_Withdraw_Acu*)pPacket;
	if ( NULL == pclInfo )
	{
		return;
	}

	if ( 1 != pclInfo->m_siResult )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( pclInfo->m_siCharID );
	if ( NULL == pclchar )
	{
		return;
	}
	
	// ��û�� ����� �ٸ� ����̶��
	if ( pclchar->pclCI->GetPersonID() != pclInfo->m_siPersonID )
	{
		return;
	}

	//------------------------------------------
	// �������� ����
	//------------------------------------------

	// �� ����� ��ť�� ����
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclInfo->m_siLeftAcu );

	//------------------------------------------
	// ���������� ���������� �޾Ҵٴ� �޽��� ����
	//------------------------------------------
	SI64 siTradeServerConnect = 0;	// �� ������ �α׸� ���涧 ���������� ����� ���´��� �Ⱥ��´����� Ȯ���ϴ� ����

	if ( (pclNTradeServerProcess) && (TRUE == pclNTradeServerProcess->IsEstablished()) )
	{
		siTradeServerConnect = 1;

		NTradeServerRequest_Withdraw_Acu_Success clTSMsg( pclInfo->m_siReservedNum );
		pclNTradeServerProcess->SendMsg((sPacketHeader*)&clTSMsg);
	}

	//------------------------------------------
	// Ŭ���̾�Ʈ�� ���� ����
	//------------------------------------------
	cltGameMsgResponse_TradeServer_Get_Withdraw_Acu clInfo( pclInfo->m_siLeftAcu, pclInfo->m_siLeftSavedAcu );
	cltMsg clMsg( GAMEMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU, sizeof(clInfo), (BYTE*)&clInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	//------------------------------------------
	// �α� ����
	//------------------------------------------
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// Param1	: ���� ���� ���� �ִ� ��ť
		// Param2	: ���������� ����Ǿ��ִ� ��ť
		// Param3	: ������������ ���� ��ť
		// Param4	: ���������� �޾Ҵٴ� ����� ���´��� ����(0=DisConnect/1=Connect)
		
		cltServer* pclserver = (cltServer*)pclClient;
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_TRADE_SERVER, LOGCOMMAND_INDEX_TRADE_WITHDRAW_ACU, 
			0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			pclInfo->m_siLeftAcu, pclInfo->m_siLeftSavedAcu, pclInfo->m_siWithdrawAcu, siTradeServerConnect, 0,
			NULL, NULL
			);
	}

	// ���� ��������� �����Ѵ�
	pclchar->bTradeServerUsing = false;

}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDPASSPORT_SET(sPacketHeader*pPacket)
{
	sDBResponse_WorldPassport_Set* pclinfo = (sDBResponse_WorldPassport_Set*)pPacket;
	if ( NULL == pclinfo )
	{
		return;
	}

	SI32 siCharID = pclCM->GetIDFromPersonID( pclinfo->m_siPersonID );
	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( 1 > pclinfo->m_siResult )
	{
		// �ߺ��� �̸��� �̹� ������
		if ( -1 == pclinfo->m_siResult )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_WORLDPASSPORT_OVERLAPPING, 0, 0, siCharID );
		}
		return;
	}

	//------------------------------------------
	// �������� ����
	//------------------------------------------

	// �ɸ��Ϳ� ���ǰ��� ���� ����
	pclchar->pclCI->clWorldPassport.Set( pclinfo->m_szPassportName, pclinfo->m_siIssueDateVary, pclinfo->m_siExpireDateVary );

	// �߱޺���� �����ϰ� �� ��ť
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclinfo->m_siLeftAcu );


	//------------------------------------------
	// Ŭ���̾�Ʈ�� ���� ����
	//------------------------------------------
	cltGameMsgResponse_WorldPassport_Set clinfo( pclinfo->m_szPassportName, pclinfo->m_siIssueDateVary, pclinfo->m_siExpireDateVary, pclinfo->m_siLeftAcu );
	cltMsg clMsg(GAMEMSG_RESPONSE_WORLDPASSPORT_SET,sizeof(clinfo),(BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);


	//------------------------------------------
	// �α� ����
	//------------------------------------------
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// Param1	: ���� ������
		// Param2	: ���� ������
		// Param3	: ���� ���� ���(��ť)
		// Param4	: �߱޺���� ������ ���� ��ť
		// szParam1	: �����̸�
		cltServer* pclserver = (cltServer*)pclClient;
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_PASSPORT, LOGCOMMAND_INDEX_WORLD_PASSPORT_SET, 
			0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			pclinfo->m_siIssueDateVary, pclinfo->m_siExpireDateVary, pclinfo->m_siPaidAcu, pclinfo->m_siLeftAcu, 0,
			pclinfo->m_szPassportName, NULL
		);
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_WORLDPASSPORT_EXTEND(sPacketHeader*pPacket)
{
	sDBResponse_WorldPassport_Extend* pclinfo = ( sDBResponse_WorldPassport_Extend*)pPacket;
	if ( NULL == pclinfo )
	{
		return;
	}

	SI32 siCharID = pclCM->GetIDFromPersonID( pclinfo->m_siPersonID );
	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( 1 > pclinfo->m_siResult )
	{
		return;
	}

	//------------------------------------------
	// �������� ����
	//------------------------------------------
	// �ɸ��Ϳ� ���� ������ ����
	pclchar->pclCI->clWorldPassport.SetExpireDateVary( pclinfo->m_siExpireDateVary );

	// �������� �����ϰ� �� ��ť
	pclchar->pclCI->clWorldMoney.SetWorldMoney( pclinfo->m_siLeftAcu );


	//------------------------------------------
	// Ŭ���̾�Ʈ�� ���� ����
	//------------------------------------------
	cltGameMsgResponse_WorldPassport_Extend clinfo( pclinfo->m_siExpireDateVary, pclinfo->m_siLeftAcu );
	cltMsg clMsg(GAMEMSG_RESPONSE_WORLDPASSPORT_EXTEND,sizeof(clinfo),(BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);


	//------------------------------------------
	// �α� ����
	//------------------------------------------
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// Param1	: ���� ������
		// Param2	: ���� ���� ���(��ť)
		// Param3	: �������� ������ ���� ��ť
		cltServer* pclserver = (cltServer*)pclClient;
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_WORLD_PASSPORT, LOGCOMMAND_INDEX_WORLD_PASSPORT_EXTEND, 
			0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			pclinfo->m_siExpireDateVary, pclinfo->m_siPaidAcu, pclinfo->m_siLeftAcu, 0, 0,
			NULL, NULL
		);
	}


}