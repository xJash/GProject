//---------------------------------
// 2003/8/5 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"
//-----------------------------------------
// Server
//-----------------------------------------
#include "../Server/Statistics/Statistics.h"


#include "..\..\..\DBManager\GameDBManager_World\DBMsg-CityHall.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Stock.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Bank.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"

#include "..\Common\StockDistributionMgr\StockDistributionMgr.h"

#include "..\CommonLogic\MsgType-Person.h"


#include "MsgRval-Define.h"

#include "..\..\CommonLogic\CityHall\Cityhall.h"

#include "..\CommonLogic\MsgType-Stock.h"


// �ֽ� �ֹ��� ����϶�� ��û�� ���� ����
void cltServer::DoMsg_DBMSG_RESPONSE_CANCELSTOCKORDER(sPacketHeader* pPacket)
{
	sDBResponse_CancelStockOrder* pclMsg = (sDBResponse_CancelStockOrder*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// �ֽ� �ֹ� �����ڿ��� PersonID������ �ֹ��� ��� ����ϰ� �Ѵ�.
	pclStockManager->pclOrderManager->CancelOrder(pclMsg->siPersonID);

	// Ŭ���̾�Ʈ���� ��ҵ� ������ ������. 
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) && pclCM->CR[id]->IsValidConnection())
	{
		// Person�� �˰� �ִ� �ڽ��� �ֹ� ������ �ʱ�ȭ�Ѵ�. 
		pclCM->CR[id]->pclCI->clStock.clOrderInfo.Init();
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCKORDER, true, 0);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ��ֹ��� ����� ���� ��û.
			// 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_ORDER_CANCEL, 
								 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								 0, 0, 0, 0, 0, NULL, NULL);
		}
	}
}

// �ֽ� �ֹ��� DB�� ��û�� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETMANYSTOCKORDER(sPacketHeader* pPacket)
{
	SI32 i;

	sDBResponse_GetManyStockOrder* pclMsg = (sDBResponse_GetManyStockOrder*)pPacket;

	// id�� 0�ΰ�쵵 �����ϴ�. 

	if( pclMsg->siOrderMode == ORDERMODE_SELL ) {
		pclStockManager->bInitSellOrder = TRUE;
		//�ʹ� ���� ������ ����
		//pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetManyStockOrder : ORDERMODE_SELL"));
	} else {
		pclStockManager->bInitBuyOrder = TRUE;
		//�ʹ� ���� ������ ����
		//pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetManyStockOrder : ORDERMODE_BUY"));
	}

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// ������ �ֹ� ���ۿ� DB���� ������ �ֹ� ����Ʈ�� �ִ´�. 
	for(i = 0;i < GET_MANY_STOCK_ORDER_NUM;i++)
	{
		pclStockManager->pclOrderManager->SetOrder(pclMsg->siOrderMode, &pclMsg->clTradeOrder[i]);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("pclStockManager->pclOrderManager->SetOrder(pclMsg->siOrderMode, &pclMsg->clTradeOrder[i])"));
	}
	

}

// �ֽ� �ŷ��� ����� ���� ���� ó���Ѵ�. 
void cltServer::DoMsg_DBMSG_RESPONSE_TRADESTOCK(sPacketHeader* pPacket)
{
	sDBResponse_TradeStock* pclMsg = (sDBResponse_TradeStock*)pPacket;

	SI32 returnval = 0;

	if (pclMsg->siOrderMode == ORDERMODE_BUY ||	pclMsg->siResult == 1) 
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{			
			// �ֽ� ���� ���� �α�[2007.9.4 �ռ���]
			// ���� : PCK
			SI32 charID			= pclMsg->usCharID;
			SI32 villageunique	= pclMsg->siVillageUnique;		
			GMONEY price		= pclMsg->siTradePrice;
			SI16 stockamount	= pclMsg->siTradeAmount;
						
			// ���� �ŷ��� �� �׼�
			GMONEY TotalPrice	= price * stockamount;
			
			// [�α��߰� : Ȳ���� 2007. 11. 1 �ֽ� ����.]
			// param1 == �ŷ��� �ֽļ�
			// param2 == �ϳ� �ŷ��� ����
			// param3 == ���� �ŷ��� �� �׼�
			// param4 == ���� �ֽ� ��
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(charID))		pclchar = (cltCharServer*)pclCM->CR[charID];
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK,LOGCOMMAND_INDEX_STOCKBUY,
								0,pclchar, NULL, pclMsg->clDstOrder.siPersonID, 0, pclMsg->siBankMoney, NULL, 0, 0, 0, villageunique, 0, 0,
								stockamount, price, TotalPrice, pclMsg->siLeftAmount, 0, NULL, NULL);
		
							
			// [�α��߰� : Ȳ���� 2007. 11. 1 �ֽ� �Ǹ�.]
			// param1 == �ŷ��� �ֽļ�
			// param2 == �ϳ� �ŷ��� ����
			// param3 == ���� �ŷ��� �� �׼�
			// param4 == ���� �ֽ� ��
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK,LOGCOMMAND_INDEX_STOCKSELL,0,
								NULL, NULL, pclMsg->clOrgOrder.siPersonID, 0, pclMsg->siDstBankMoney, NULL, 0, 0, 0, villageunique, 0, 0,
								stockamount, price, TotalPrice, pclMsg->siDstLeftAmount, 0, NULL, NULL);
		}
	}

	switch(pclMsg->siResult)
	{
	case 0:
		return;
	case 1:	// �ŷ� ����. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_SUCCESSTRADE;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_SUCCESSTRADE;
		}
		break;
	case -1:// ������ ���� ���°� ����. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_FAILNOACCOUNT;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_FAILNOACCOUNT;
		}
		break;
	case -2:	// ������ ���� ���¿� �ܾ��� ������� �ʴ�. �ֹ��� ��ҵȴ�. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_FAILNOTENOUGHMONEY;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_FAILNOTENOUGHMONEY;
		}
		break;

	case -3:	// ���ѵ� ���� �̻��� �ֽ��� �� �� ����. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_FAILLIMITSTOCKKIND;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_FAILLIMITSTOCKKIND;
		}
		break;
	case -4:	// �ֹ��� �Ϻδ� ó���ǰ� �Ϻδ� ó������ �ʾҴ�. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_HALFSUCCESS;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_HALFSUCCESS;
		}
		break;
	case -5:	// ��� �ֹ��� �㱸���� ���ֵ� �ŷ��� ü����� �ʾҴ�. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_FAILLIAR;
		}
		else
		{
			returnval	= SRVAL_STOCK_BUY_FAILLIAR;
		}
		break;
	case -6:	// ������ ���°� ��ȿ���� �ʾƼ� �ŷ��� ü����� ����. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_DSTSELLERNOACCOUNT;  // ���� ����� �ϴµ� ������ ���°� ����. 
		}
		else
		{
			returnval	= SRVAL_STOCK_DSTBUYERNOACCOUNT;	// ���� �ȷ��� �ϴµ� ������ ���°� ����. 
		}
		break;


	default:
		MsgBox( TEXT("fd9jfd"), TEXT("11fld9j:%d"), pclMsg->siResult);
		return ;
	}

	//----------------------------------------------------------
	// DB�� ���� ���� �ֹ� �ݴ� ������ ������ ������Ʈ �Ѵ�. 
	//----------------------------------------------------------
	SI32 mode = 0;
	if(pclMsg->siOrderMode == ORDERMODE_SELL)
	{
		mode = ORDERMODE_BUY;
	}
	else
	{
		mode = ORDERMODE_SELL;
	}

	// �ݴ��ֹ� ������ 0�̸� �� �ֹ��� �����Ǿ�� �� �ֹ��� �ȴ�. ���� VillageUnique�� 0���� ����. 
	// �ŷ��Ǵ� ������ ������ Ȯ���Ѵ�.
	SI32 tradevillageunique	= pclMsg->clDstOrder.siVillageUnique;

	if(pclMsg->clDstOrder.siAmount == 0)
	{
		pclMsg->clDstOrder.siPrice			= 0;
		pclMsg->clDstOrder.siVillageUnique	= 0;
	}

	pclStockManager->pclOrderManager->SetOrder(mode, &pclMsg->clDstOrder);

	// �ֹ��ڰ� ������ �ִٸ�, ����� �ֹ� ������ �뺸���ش�. 
	SI32 tempid = pclCM->GetIDFromPersonID(pclMsg->clDstOrder.siPersonID);
	if(pclCM->IsValidID(tempid))
	{
		pclCM->CR[tempid]->pclCI->clStock.clOrderInfo.Set(mode, &pclMsg->clDstOrder);
		pclCM->CR[tempid]->SetUpdateSwitch(UPDATE_STOCKORDER, true, 0);
	}


	//------------------------------------------------------
	// Ŭ���̾�Ʈ�κ��� ���� �ֹ��� ���� ������ Ȯ���Ѵ�. 
	//------------------------------------------------------

	// ��� ó���� ����Ǿ���.
	if(pclMsg->clOrgOrder.siAmount == 0)
	{
		// ������ �ŷ��� �ֽ��� �ִٸ�, 
		if(pclMsg->siTradeAmount)
		{
			// �ŷ��� ������ ������Ʈ �Ѵ�. 
			if(pclMsg->siTradePrice)
			{
				pclVillageManager->SetCurrentStockPrice(pclMsg->clOrgOrder.siVillageUnique, pclMsg->siTradePrice);
			}
		}
	}
	// ó���� �Ϸ���� �ʾҴٸ� �ٽ� ������ �ֹ� ������ Ȯ���Ѵ�. 
	else
	{
		cltTradeOrder* pclorder = pclStockManager->pclOrderManager->FindOpositeOrder(pclMsg->siOrderMode, &pclMsg->clOrgOrder);
		// ������ �ֹ� ���ۿ��� ������ �ݴ� �ֹ��� ã�� ���̶��, 
		if(pclorder)
		{
			// �ŷ� ������ ���� ���� �����Ŀ� DB�� �뺸�Ѵ�. 

			// �ŷ� ����. (�� �ֹ���  ��� ����) 
			GMONEY tradeprice		= (pclMsg->clOrgOrder.siPrice + pclorder->siPrice) / 2;

			sDBRequest_TradeStock clMsg(pclMsg->usCharID, pclMsg->siOrderMode, pclMsg->siVillageUnique, &pclMsg->clOrgOrder, pclorder->siIndex, tradeprice);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		}
		// ������ �ݴ� �ֹ��� ã�� ���ߴٸ�, 
		else
		{
			// DB�� �ֹ� ���ۿ� ������ ���� ���� ��û�Ѵ�. 
			sDBRequest_OrderStock	clMsg(pclMsg->usCharID, pclMsg->siOrderMode, &pclMsg->clOrgOrder);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
	}


	// �����Ḧ Ȯ���Ѵ�. 
	cltStrInfo* pclstrinfo = pclStockManager->GetStrInfo(pclMsg->siVillageUnique);
	if(pclstrinfo == NULL)return ;

	GMONEY fee = pclstrinfo->clMarketStrInfo.clFee.CalcFee(pclMsg->siTradeAmount * pclMsg->siTradePrice);

	//---------------------------------------
	// �ŷ� ������ ���� ������ �����. 
	//---------------------------------------
	SI32 dstordermode;
	if(pclMsg->siOrderMode == ORDERMODE_SELL)
	{
		dstordermode = ORDERMODE_BUY;
	}
	else
	{
		dstordermode = ORDERMODE_SELL;
	}
	// �ŷ��� �ֽ��� �ִٸ� ������ ������. (Org)
	if(pclMsg->siTradeAmount)
	{
		//----------------------------------------
		// �ֽ� �ŷ� ��踦 �����Ѵ�. 
		//----------------------------------------
		pclStatisticsManager->clDailyStatistics.siStockTradeNumber += pclMsg->siTradeAmount;
 
		// Org�� ������ ������. 
		cltLetterMsg_StockTrade clletter1(tradevillageunique, pclMsg->siOrderMode, pclMsg->siTradeAmount, pclMsg->siLeftAmount, pclMsg->siTradePrice*pclMsg->siTradeAmount, fee);
		SI32 orgid = SendLetterMsg(pclMsg->clOrgOrder.siPersonID, (cltLetterHeader*)&clletter1);
		if(pclCM->IsValidID(orgid))
		{
			//-------------------------------------
			// �ŷ� ��û���� ������ ������Ʈ �Ѵ�. 
			//-------------------------------------

			// �ܿ� �ֽļ�. 
			pclCM->CR[orgid]->pclCI->clStock.clInfo.Set(tradevillageunique, pclMsg->siLeftAmount);
			pclCM->CR[orgid]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

			// ���� �ܱ�. 
			pclCM->CR[orgid]->pclCI->clBank.SetMoney(pclMsg->siBankMoney);
			pclCM->CR[orgid]->SetUpdateSwitch(UPDATE_BANK, true, 0);

		}

		// Dst�� ������ ������. 
		cltLetterMsg_StockTrade clletter2(tradevillageunique, dstordermode, pclMsg->siTradeAmount, pclMsg->siDstLeftAmount, pclMsg->siTradePrice*pclMsg->siTradeAmount, fee);
		SI32 dstid = SendLetterMsg(pclMsg->clDstOrder.siPersonID, (cltLetterHeader*)&clletter2);
		if(pclCM->IsValidID(dstid))
		{
			//------------------------------------
			// �ŷ� ������� ������ ������Ʈ �Ѵ�. 
			//-------------------------------------

			// �ܿ� �ֽļ�. 
			pclCM->CR[dstid]->pclCI->clStock.clInfo.Set(tradevillageunique, pclMsg->siDstLeftAmount);
			pclCM->CR[dstid]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

			// ���� �ܱ�. 
			pclCM->CR[dstid]->pclCI->clBank.SetMoney(pclMsg->siDstBankMoney);
			pclCM->CR[dstid]->SetUpdateSwitch(UPDATE_BANK, true, 0);
		}

		//-----------------------------------
		// �Ǹ��ڴ� �����Ḧ �����Ѵ�. 
		//-----------------------------------
		// �����ؾ� �� �����ᰡ ������, 
		if(fee)
		{
			cltMoney clmoney;
			clmoney.itMoney = fee;

			if(pclMsg->siOrderMode == ORDERMODE_SELL)
			{
				sDBRequest_PayFee clinfo(orgid, pclMsg->clOrgOrder.siPersonID, pclMsg->siVillageUnique, RANKTYPE_STOCK, FEETYPE_STOCK_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}
			else
			{
				sDBRequest_PayFee clinfo(dstid, pclMsg->clDstOrder.siPersonID, pclMsg->siVillageUnique, RANKTYPE_STOCK, FEETYPE_STOCK_SELL, &clmoney);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clinfo);

				pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
			}

		}

	}


	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;


	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_STOCK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

// �ֹ� ������ DB�� �߰��϶�� ��û�� ���� ������ ó���Ѵ�.
void cltServer::DoMsg_DBMSG_RESPONSE_ORDERSTOCK(sPacketHeader* pPacket)
{
	sDBResponse_OrderStock* pclMsg = (sDBResponse_OrderStock*)pPacket;
	
	SI32 id = pclMsg->usCharID;

	SI32 returnval = 0;
	switch(pclMsg->siResult)
	{
	case 0:
		return;
	case 1:	// �ŷ� ����. 
		if(pclMsg->siOrderMode == ORDERMODE_BUY)
		{
			returnval	= SRVAL_STOCK_BUY_SUCCESSORDER;
		}
		else
		{
			returnval	= SRVAL_STOCK_SELL_SUCCESSORDER;
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 11. 1] // �ֽĸŵ�, �ż� ����.
			// param1 == ������� �ֹ��ΰ�? �ֽ�, ������, Ȥ�� ����ֽ�.
			// param2 == �ֹ� ������ �ĺ���(�ε���) (0~�� 16000).
			// param3 == �ֹ� ����. 
			// param4 == �ֹ� ���� ����. 
			// param5 == �ð� ����.

			cltCharServer* pclchar = NULL;
			if( pclCM->IsValidID(id) )		pclchar = (cltCharServer*)pclCM->CR[id];
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_ORDER, 
				returnval, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clOrder.siVillageUnique, 0, 0, 
				pclMsg->clOrder.siType,
				pclMsg->clOrder.siIndex,
				pclMsg->clOrder.siAmount,
				pclMsg->clOrder.siPrice,
				pclMsg->clOrder.siDate,
				NULL, NULL);
		}

		break;
	}

	// ������ �ֹ� ���ۿ� DB�κ��� ���� �ֹ� ������ �߰��Ѵ�. 
	pclStockManager->pclOrderManager->SetOrder(pclMsg->siOrderMode, &pclMsg->clOrder);


	// Ŭ���̾�Ʈ�� ��ȿ�� �����, 
	// Ŭ���̾�Ʈ�� �� �ֹ� ������ ������. 
	if(pclCM->IsValidID(id) && pclCM->CR[id]->IsValidConnection())
	{
		pclCM->CR[id]->pclCI->clStock.clOrderInfo.Set(pclMsg->siOrderMode, &pclMsg->clOrder);
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCKORDER, true, 0);

		if(returnval)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_STOCK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
	}
}

// �ֽ� ���� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYSTOCKPRICE(sPacketHeader* pPacket)
{
	sDBResponse_ManyStockPrice* pclMsg = (sDBResponse_ManyStockPrice*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 i;

	// �ְ��� ���´�
	for(i = 0;i < MAX_VILLAGE_NUMBER;i++)
	{
		pclVillageManager->SetCurrentStockPrice(i, pclMsg->siCurrentStockPrice[i]);
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_ManyStockPrice"));
}

// �ֽ� �ŷ� ������ ������ �����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETSTOCKFEE(sPacketHeader* pPacket)
{
	sDBResponse_SetStockFee* pclMsg = (sDBResponse_SetStockFee*)pPacket;

	// ����� Ȯ���Ѵ�. 
	SI32 returnval = 0;
	switch(pclMsg->siResult)
	{
	case 0:
		return ;
	case 1:	// ������ ���� ����. 
		returnval	= SRVAL_STOCK_SUCCESSSETFEE;
		break;
	default:
		MsgBox( TEXT("vc984j"), TEXT("fdd:%d"), pclMsg->siResult);
	}

	// ������ �ش� ������ ������ ������Ʈ �Ѵ�. 
	cltStrInfo* pclinfo = pclStockManager->GetStrInfo(pclMsg->siVillageUnique);
	pclinfo->clStockStrInfo.clFee.Set(&pclMsg->clFee);

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_STOCK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	//KHY - 0727 - �ֽ� ������ ���� ���� ����. ���� ������ �ִ� ��� ���� client�� �ǹ� ������ ������Ʈ�Ѵ�.
	cltMsg clNormalMsg(GAMEMSG_RESPONSE_STRINFO, 	pclinfo->GetTotalSize(), 	(BYTE*)pclinfo);
//	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);

	SI32 index = 0;
	while(id = pclCM->GetCharOrder(index))
	{
		index++;

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if(pclchar->GetSession())
		{
			if(pclchar->GetCurrentVillageUnique() == pclMsg->siVillageUnique)
			{
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
			}
			
		}
	}

	////////////////////////////////////////////////////////////////	
}

// ���� ���� ���� ����� ���´� 
void cltServer::DoMsg_DBMSG_RESPONSE_GETSTOCKBIDVILLAGELIST(sPacketHeader* pPacket)
{
	sDBResponse_GetStockBidVillageList *pclMsg = (sDBResponse_GetStockBidVillageList *)pPacket;

	cltStockBidVillageInfo *pStockBidVillageInfo;

	//SI32 beginningPrice;

	if( pclMsg->usCount > MAX_VILLAGE_NUMBER )		pclMsg->usCount = MAX_VILLAGE_NUMBER;

	for( int i = 0; i < pclMsg->usCount; ++i ) {

		//pStockBidVillageInfo = &pclMsg->clStockBidVillageInfo[ i ];

		//beginningPrice = pStockBidVillageInfo->siBeginningPrice;
		//if( beginningPrice < 5000 ) beginningPrice = 5000;
		//
		//pclStockManager->SetStockBidVillage(
		//	pStockBidVillageInfo->siVillageUnique,
		//	&pStockBidVillageInfo->clBiddingDate,
		//	pStockBidVillageInfo->siStockAmount,
		//	beginningPrice );
		pStockBidVillageInfo = &pclMsg->clStockBidVillageInfo[ i ];

		pclStockManager->SetStockBidVillage( pStockBidVillageInfo->siVillageUnique_,
			pStockBidVillageInfo->siTotalStockAmount_,
			pStockBidVillageInfo->siTottalIncreaseStockAmount_,
			pStockBidVillageInfo->siLeftIncreaseStockAmount_,
			pStockBidVillageInfo->siCurrentStockPrice_,
			&pStockBidVillageInfo->clBiddingDate_
			);

	}


	if( pclMsg->usCount > 0 ) pclStockManager->bBidding = TRUE;
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStockBidVillageList"));
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETSTOCKBIDDERLIST(sPacketHeader* pPacket)
{
	sDBResponse_GetStockBidderList *pclMsg = (sDBResponse_GetStockBidderList *)pPacket;
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	int count = pclMsg->usCount;
	if( count > MAX_STOCKBIDDER_INVILLAGE )		count = MAX_STOCKBIDDER_INVILLAGE;

	pclStockManager->InitStockBidder( pclMsg->siVillageUnique );

	if( count == 0 ) return;

	for( int i = 0; i < count; ++i ) {

		pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ i ].Set(
			&pclMsg->clStockBidder[ i ] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStockBidderList"));

}


void cltServer::DoMsg_DBMSG_RESPONSE_SETSTOCKBIDVILLAGE(sPacketHeader* pPacket)
{
	//sDBResponse_SetStockBidVillage *pclMsg = (sDBResponse_SetStockBidVillage *)pPacket;

	//if( pclMsg->siResult == 1 ) {
	//	pclStockManager->SetStockBidVillage( pclMsg->siVillageUnique, &pclMsg->clDate, pclMsg->siStockAmount, pclMsg->siBeginningPrice );
	//}
}

//void cltServer::DoMsg_DBMSG_RESPONSE_BIDSTOCK(sPacketHeader* pPacket)
//{
//	sDBResponse_BidStock *pclMsg = (sDBResponse_BidStock *)pPacket;
//
//	SI32 id	= pclMsg->usCharID;
//	if(pclCM->IsValidID(id) == FALSE)return ;
//
//	// ����� Ȯ���Ѵ�. 
//	SI32 returnval = 0;
//
//	if( pclMsg->siResult != 1 )
//	{
//		returnval	= SRVAL_STOCK_FAIL_BIDDING;
//		if(returnval)
//		{
//			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
//			SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
//		}
//		return;
//	}
//	else
//	{
//		returnval = SRVAL_STOCK_SUCCESS_BIDDING;
//
//		pclStockManager->SetStockBidVillage( pclMsg->clStockBidVillageInfo.siVillageUnique_,
//			pclMsg->clStockBidVillageInfo.siTotalStockAmount_,
//			pclMsg->clStockBidVillageInfo.siTottalIncreaseStockAmount_,
//			pclMsg->clStockBidVillageInfo.siLeftIncreaseStockAmount_,
//			pclMsg->clStockBidVillageInfo.siCurrentStockPrice_,
//			&pclMsg->clStockBidVillageInfo.clBiddingDate_ );
//		pclStockManager->bBidding = TRUE;
//
//		if(returnval)
//		{
//			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
//			SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
//		}
//	}
//	
//}

void cltServer::DoMsg_DBMSG_RESPONSE_BIDSTOCK(sPacketHeader* pPacket)
{
	sDBResponse_BidStock *pclMsg = (sDBResponse_BidStock *)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	// ����� Ȯ���Ѵ�. 
	SI32 returnval = 0;

	if( pclMsg->siResult != 1 )
	{
		returnval	= SRVAL_STOCK_FAIL_BIDDING;
		if(returnval)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
			
			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� �������.
			//	// param2 == ���� Ÿ��, 
			//	// param2 == ���.
			//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_BID, 
			//						 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//						 RANKTYPE_CITYHALL, returnval, 0, 0, 0, NULL, NULL);
			//}
		}
		return;
	}
	else
	{
		returnval = SRVAL_STOCK_SUCCESS_BIDDING;

		pclStockManager->SetStockBidVillage( pclMsg->clStockBidVillageInfo.siVillageUnique_,
			pclMsg->clStockBidVillageInfo.siTotalStockAmount_,
			pclMsg->clStockBidVillageInfo.siTottalIncreaseStockAmount_,
			pclMsg->clStockBidVillageInfo.siLeftIncreaseStockAmount_,
			pclMsg->clStockBidVillageInfo.siCurrentStockPrice_,
			&pclMsg->clStockBidVillageInfo.clBiddingDate_ );
		pclStockManager->bBidding = TRUE;

		if(returnval)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� �������.
				// param2 == ���� Ÿ��, 
				// param2 == ���.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_BID, 
									 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									 RANKTYPE_CITYHALL, returnval, 0, 0, 0, NULL, NULL);
			}
		}
	}
}

//void cltServer::DoMsg_DBMSG_RESPONSE_COMPLETESTOCKBIDVILLAGE(sPacketHeader* pPacket)
//{
//	sDBResponse_CompleteStockBidVillage *pclMsg = (sDBResponse_CompleteStockBidVillage *)pPacket;
//
//	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );
//
//	if( pclMsg->siResult == 1 ) {
//		// ���� �����̸�, 	
//
//		// ��� �����ڱ� ����
//		pclinfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );
//
//		// ��� �� �����ֽļ� ����
//		pclinfo->clCityhallStrInfo.siTotalStockAmount +=
//			pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siStockAmount;
//
//
//		// ��� ����� ������ �߰��Ѵ�			
//		{
//			cltMoney clMoney;
//
//			clMoney.itMoney = pclMsg->clTotalMoney.itMoney - pclMsg->clTaxMoney.itMoney;
//
//			pclinfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
//				INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );
//
//			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
//				INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );
//
//			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
//			
//
//			// ���ӿ��� ���� ������ ���� 
//			clCurrencyInfo.clOutputMoney_clStockBidTax.Increase( &pclMsg->clTaxMoney );
//		}
//
//		// ���۰� ���� 
//		SI32 amount = 0;
//		SI32 beginningPrice;
//
//
//		// �����ڵ鿡�� ��� ���� ������
//
//		for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {
//
//			if( pclMsg->clResultStockBidder[ i ].siPersonID == 0 ) continue;
//
//			cltLetterMsg_ResultBidStock clLetter( 
//				pclMsg->clResultStockBidder[ i ].bSuccessfulBid,
//				pclMsg->siVillageUnique,
//				pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siStockAmount,
//				&pclMsg->clResultStockBidder[ i ].clBidMoney,
//				pclMsg->clResultStockBidder[ i ].bExceedLimit );
//
//			SendLetterMsg( pclMsg->clResultStockBidder[ i ].siPersonID, (cltLetterHeader*)&clLetter);
//
//		}
//
////		beginningPrice = (int)( pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ i ].siPrice * 0.0097 ) * 100;
//
//		beginningPrice = (int)( pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ 0 ].siPrice * 0.007 ) * 100;
//		pclinfo->clCityhallStrInfo.siBeginningPrice = beginningPrice;
//
//		sDBRequest_SetBeginningPrice sendMsg( pclMsg->siVillageUnique, beginningPrice );
//		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
//
//	} else {
//		// ���� �����̸�
//
//		// ���۰� ���� ���� 
//		SI32 beginningPrice = (int)(pclinfo->clCityhallStrInfo.siBeginningPrice * 0.009) * 100;
//
//		if( beginningPrice < 5000 ) beginningPrice = 5000;
//
//		pclinfo->clCityhallStrInfo.siBeginningPrice = beginningPrice;
//
//		sDBRequest_SetBeginningPrice sendMsg( pclMsg->siVillageUnique, beginningPrice );
//		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
//
//	}
//
//	pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siVillageUnique = 0;
//
//	pclStockManager->InitStockBidder( pclMsg->siVillageUnique );
//}

void cltServer::DoMsg_DBMSG_RESPONSE_COMPLETESTOCKBIDVILLAGE(sPacketHeader* pPacket)
{
	sDBResponse_CompleteStockBidVillage *pclMsg = (sDBResponse_CompleteStockBidVillage *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if( pclMsg->siResult != 1 ) 
		return;

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclinfo == NULL )
		return ;
	if ( pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique] == NULL )
		return ;
	if ( pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique]->siVillageUnique <= 0 ||
		pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique]->siVillageUnique >= MAX_VILLAGE_NUMBER )
		return ;

	cltDate tempDate;
	tempDate.Set( 0, 0, 0, 0, 0 );
	pclStockManager->SetStockBidVillage( pclMsg->siVillageUnique, 0, 0, 0, 0, &tempDate);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// TEMP LEEKH --------------------------------------------------------------
		// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� �Ϸ�.
		// pszParam1 == �ð�.
		TCHAR str[50] = {'\0', };
		StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d, %d:%d"),	
												tempDate.uiYear,
												tempDate.uiMonth,
												tempDate.uiDay,
												tempDate.uiHour,
												tempDate.uiMinute );

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_BID_COMPLETE, 
							 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							 pclMsg->clTaxMoney.itMoney, pclMsg->clTotalMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, str, NULL);
		// TEMP LEEKH --------------------------------------------------------------
	}

	/*	sDBResponse_CompleteStockBidVillage *pclMsg = (sDBResponse_CompleteStockBidVillage *)pPacket;

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclinfo == NULL )
	return ;
	if ( pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique] == NULL )
	return ;
	if ( pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique]->siVillageUnique <= 0 ||
	pclVillageManager->pclVillageInfo[pclMsg->siVillageUnique]->siVillageUnique >= MAX_VILLAGE_NUMBER )
	return ;

	if( pclMsg->siResult == 1 ) {
	// ���� �����̸�, 	

	// ��� �����ڱ� ����
	pclinfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );

	// ��� �� �����ֽļ� ����
	pclinfo->clCityhallStrInfo.siTotalStockAmount +=
	pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siStockAmount;


	// ��� ����� ������ �߰��Ѵ�			
	{
	cltMoney clMoney;

	clMoney.itMoney = pclMsg->clTotalMoney.itMoney - pclMsg->clTaxMoney.itMoney;

	pclinfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
	INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
	INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );


	// ���ӿ��� ���� ������ ���� 
	clCurrencyInfo.clOutputMoney_clStockBidTax.Increase( &pclMsg->clTaxMoney );
	}

	// ���۰� ���� 
	SI32 amount = 0;
	SI64 beginningPrice;


	// �����ڵ鿡�� ��� ���� ������

	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {

	if( pclMsg->clResultStockBidder[ i ].siPersonID == 0 ) continue;

	cltLetterMsg_ResultBidStock clLetter( 
	pclMsg->clResultStockBidder[ i ].bSuccessfulBid,
	pclMsg->siVillageUnique,
	pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siStockAmount,
	&pclMsg->clResultStockBidder[ i ].clBidMoney,
	pclMsg->clResultStockBidder[ i ].bExceedLimit );

	SendLetterMsg( pclMsg->clResultStockBidder[ i ].siPersonID, (cltLetterHeader*)&clLetter);

	}

	//		beginningPrice = (int)( pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ i ].siPrice * 0.0097 ) * 100;

	beginningPrice = (int)( pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ 0 ].siPrice * 0.007 ) * 100;
	pclinfo->clCityhallStrInfo.siBeginningPrice = beginningPrice;

	sDBRequest_SetBeginningPrice sendMsg( pclMsg->siVillageUnique, beginningPrice );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	} else {
	// ���� �����̸�

	// ���۰� ���� ���� 
	SI64 beginningPrice = (SI64)(pclinfo->clCityhallStrInfo.siBeginningPrice * 0.009) * 100;

	if( beginningPrice < 5000 ) beginningPrice = 5000;

	pclinfo->clCityhallStrInfo.siBeginningPrice = beginningPrice;

	sDBRequest_SetBeginningPrice sendMsg( pclMsg->siVillageUnique, beginningPrice );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	}

	pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siVillageUnique = 0;

	pclStockManager->InitStockBidder( pclMsg->siVillageUnique );*/
}


void cltServer::DoMsg_DBMSG_RESPONSE_STOCKDISTRIBUTIONORDER(sPacketHeader* pPacket)
{
	sDBResponse_StockDistributionOrder *pclMsg = (sDBResponse_StockDistributionOrder*)pPacket;

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	switch( pclMsg->siResult)
	{	
	case 1:
		break;
	case -2:		// 10���� �̻� ����.
		SendServerResponseMsg(0, SRVAL_STOCKGIVEFAIL_FULL,  MAX_STOCK_KIND_IN_ACOUNT, 0, pclCM->CR[id]->GetCharUnique());
		return;
	case -3:		
		SendServerResponseMsg(0, SRVAL_STOCK_FAIL_DISTRIBUTIONSTOP,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	default:
		return;
	}

	if ( pclMsg->siVillageUnique < 1 )
	{
		return;
	}

	// �迭 �ε��� üũ
	if ( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if ( ! pclMsg->bVillageWarStockDistribution )
	{
		cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

		if(pclinfo != NULL)
		{
			pclinfo->clCityhallStrInfo.siTotalStockAmount += pclMsg->siStockDistributionNum;
		}
	}

	// �ֽ� ���� ������ ������Ʈ
	// DB �� ���� ������ �ʰ� �ͼ� ���� �����ٸ� IncreaseDistributionStockNum �� �Լ������� �ƹ��͵� ���� �ʰ� �׳� return �ϰ� �Ǿ� �ִ�.
	pclStockDistributionMgr->IncreaseDistributionStockNum( pclMsg->siVillageUnique, pclMsg->siStockDistributionNum );

	// ĳ���� ID üũ
	if(pclCM->IsValidID(id) == false)		return;

	// �ֽ��� ������Ʈ �Ѵ�. 
	pclCM->CR[id]->pclCI->clStock.clInfo.Add(pclMsg->siVillageUnique, pclMsg->siStockDistributionNum);

	//������Ʈ �� ������ Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

	// �� ������Ʈ
	pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->clPersonMoney.itMoney );

	// �ֽ� ���Կ� �� ���������� �˸�
	cltGameMsgResponse_ChangeMoney clinfo(pclCM->CR[id]->pclCI->clIP.GetMoney(), 0, CHANGE_MONEY_REASON_NOTDEFINED);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// �ֽ� �굷 �˸�
	cltGameMsgResponse_StockDistributionOrder clinfo1( pclMsg->siVillageUnique, pclMsg->siStockDistributionNum, pclMsg->siStockPrice );
	cltMsg clMsg1(GAMEMSG_RESPONSE_STOCKDISTRIBUTIONORDER, sizeof(clinfo1), (BYTE*)&clinfo1);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	SI32 siTotalMoney = pclMsg->siStockDistributionNum * pclMsg->siStockPrice;	// PCK : �ֽı��Կ� ������ ��

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // �ֽ� ���� ����.
		// param1 == �ֽ� ��. 
		// param2 == �ֹ� ���� ����. 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_DISTRIBUTION, 
							 0, (cltCharServer*)pclCM->CR[id], NULL, 0, siTotalMoney, pclMsg->clPersonMoney.itMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							 pclMsg->siStockDistributionNum, pclMsg->siStockPrice, 0, 0, 0, NULL, NULL);
	}

	cltMoney clMoney;
	clMoney.Set( pclMsg->siStockDistributionNum * pclMsg->siStockPrice );
	clCurrencyInfo.clOutputMoney_Stock.Increase( &clMoney );

	//�ֽ� ���� ��� �α� ���� [2007.08.04 �ռ���]
	//�ֽ� ���� ���� ���� �ϰ� ���� �α׿� �����.
	GMONEY price		= pclMsg->siStockPrice;
	SI32 villageunique	= pclMsg->siVillageUnique;
	SI16 stockamount	= pclMsg->siStockDistributionNum;
	
	// [�α��߰� : Ȳ���� 2007. 11. 1] // �ֽ� ����.
	// param1 == �ֹ� ���� ����. 
	// param2 == �ֽ� ��. 
	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCKRESPONSE, 
						 0 ,(cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, pclMsg->clPersonMoney.itMoney, NULL, 0, 0, 0, villageunique, 0, 0,
						 price, stockamount, 0, 0, 0, NULL, NULL);
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_MAXSTOCKDISTRIBUTIONNUM(sPacketHeader* pPacket)
{
	sDBResponse_MaxStockDistributionNum *pclMsg = (sDBResponse_MaxStockDistributionNum*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( ! pclMsg->bVillageWarStockDistribution )
	{
		if ( pclMsg->uiRememberVillageUnique )
		{
			clServerStartInfo.siStockDistributionVillageUnique = pclMsg->siVillageUnique;
		}
		else
		{
			clServerStartInfo.siStockDistributionVillageUnique = 0;
		}
	}

	pclStockDistributionMgr->Set( pclMsg->siVillageUnique, pclMsg->siMaxStockDistributionNum, pclMsg->siStockDistributionNum, pclMsg->siStockPrice, pclMsg->bVillageWarStockDistribution, pclMsg->siVillageWarWinVillageUnique );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // �ִ� �ֽ� ����.
		// param1 == �ֽ� ����.
		// param2 == �����鿡�� �ִ� �ִ� �ֽļ�, 
		// param3 == �� �����鿡�� �ټ� �ִ� �ֽļ�, 
		// param4 == ������ ���� �ֽ� �������� ���� ���� ���� ��,  
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_MAX_DISTRIBUTION_SET, 
							 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							 pclMsg->siStockPrice, pclMsg->siMaxStockDistributionNum, pclMsg->siStockDistributionNum, pclMsg->bVillageWarStockDistribution, 0, 
							 NULL, NULL);
	}
	return;
}

//#if defined(_CITYHALL_BANKRUPTCY)
void cltServer::DoMsg_DBMSG_RESPONSE_RETURNSTOCKBIDVILLAGE(sPacketHeader* pPacket)
{
	//sDBResponse_ReturnStockBidVillage *pclMsg = (sDBResponse_ReturnStockBidVillage *)pPacket;

	//cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

	//if( pclMsg->siResult == 1 ) {
	//	// ���� ���� ���� �����̸�, 	

	//	// ��� �����ڱ� ����

	//	// ��� �� �����ֽļ� ����

	//	// ��� ����� ������ �߰��Ѵ�			


	//	// �����ڵ鿡�� ��� ���� ������

	//	for( int i = 0; i < MAX_STOCKBIDDER_INVILLAGE; ++i ) {

	//		if( pclMsg->clResultStockBidder[ i ].siPersonID == 0 ) continue;

	//		// ���� �ð����� �Ļ��Ͽ� ���� ���� �ֽ� ���� ������ ����
	//		cltLetterMsg_VillageNameAndDate clletter( pclMsg->siVillageUnique, &(pclTime->clDate), cltLetterMsg_VillageNameAndDate::LETTERTYPE_RETURNSTOCKBIDVILLAGE );
	//		SendLetterMsg(pclMsg->clResultStockBidder[ i ].siPersonID, (cltLetterHeader*)&clletter );

	//		//---------------------------------
	//		// Ŭ���̾�Ʈ���� ���κ� ���� �ܾ� ����
	//		//---------------------------------
	//		SI32 id = pclCM->GetIDFromPersonID(pclMsg->clResultStockBidder[ i ].siPersonID);

	//		// ���ӿ� �������̸� Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
	//		if(id)
	//		{
	//			pclCM->CR[id]->pclCI->clBank.SetMoney((SI32)(pclMsg->clResultStockBidder[i].clPersonBankMoney.itMoney));

	//			pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);
	//		}
	//	}

	//	// ���۰� ���� �ʿ� ����
	//	//SI32 amount = 0;
	//	//SI32 beginningPrice;
	//	//beginningPrice = (int)( pclStockManager->clStockBidderManager[ pclMsg->siVillageUnique ].clStockBidder[ 0 ].siPrice * 0.007 ) * 100;
	//	//pclinfo->clCityhallStrInfo.siBeginningPrice = beginningPrice;

	//	//sDBRequest_SetBeginningPrice sendMsg( pclMsg->siVillageUnique, beginningPrice );
	//	//pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);


	//} else {
	//	// ���� ���� ���� ���и�, 	

	//	// ���۰� ���� ���� 

	//}

	//pclStockManager->clStockBidVillageInfo[ pclMsg->siVillageUnique ].siVillageUnique = 0;

	//pclStockManager->InitStockBidder( pclMsg->siVillageUnique );
}

void cltServer::DoMsg_DBMSG_RESPONSE_BUYBIDSTOCK(sPacketHeader* pPacket)
{
	sDBResponse_BuyBidStock *pclMsg = (sDBResponse_BuyBidStock *)pPacket;

	if( pclMsg == NULL )
		return;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == false )
		return;

	if( pclMsg->siResult != 1 )
	{
		if( pclMsg->siResult == -100 )
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BUY_BIDSTOCK_NOTBUYER,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		else
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_FAIL_BUY_BIDSTOCK,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		return;
	}

	SI32 tempVillageUnique = pclMsg->clStockBidVillageInfo.siVillageUnique_;

	if( tempVillageUnique <=0 )
		return;

	// �迭 �ε��� üũ
	if( tempVillageUnique < 0 || tempVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if( pclMsg->siAmount <= 0 )
		return;

	if( pclMsg->clStockBidVillageInfo.siCurrentStockPrice_ <=0 )
		return;

	SI64 tempTotalStockPrice = pclMsg->siTotalPrice;

	if( tempTotalStockPrice <= 0)
		return;

	// �����ݾ׿��� üũ����~
	if( tempTotalStockPrice > pclCM->CR[id]->pclCI->clIP.GetMoney() )
		return;

	// �����ݾ� ����
	pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siBuyStockLeftMoney );

	// �� �ֽ��� ������Ʈ �Ѵ�. 
	pclCM->CR[id]->pclCI->clStock.clInfo.Add(pclMsg->clStockBidVillageInfo.siVillageUnique_, pclMsg->siAmount );
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

	// �ֽ� ���Կ� �� ���������� �˸�
	cltGameMsgResponse_ChangeMoney clinfo(pclCM->CR[id]->pclCI->clIP.GetMoney(), 0, CHANGE_MONEY_REASON_BUYBIDSTOCK);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// �ֽ� �굷 �˸�
	GMONEY tempStockMoney = 0;
	if( pclMsg->siBuyMode == 0 )
		tempStockMoney = pclMsg->clStockBidVillageInfo.siCurrentStockPrice_ * 8 / 10;
	
	else if( pclMsg->siBuyMode == 1 )
		tempStockMoney = pclMsg->clStockBidVillageInfo.siCurrentStockPrice_;
	
	cltGameMsgResponse_StockDistributionOrder clinfo1( tempVillageUnique, pclMsg->siAmount, tempStockMoney );
	cltMsg clMsg1(GAMEMSG_RESPONSE_STOCKDISTRIBUTIONORDER, sizeof(clinfo1), (BYTE*)&clinfo1);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 9] // �ֽ� ���� ����.
	//	// param1 == �ֽ� ��. 
	//	// param2 == �ֹ� ���� ����. 
	//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_DISTRIBUTION, 
	//						 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, tempVillageUnique, 0, 0, 
	//						 pclMsg->siAmount, tempStockMoney, 0, 0, 0, NULL, NULL);
	//}

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( tempVillageUnique );

	if ( pclinfo == NULL )
		return ;
	if ( pclVillageManager->pclVillageInfo[tempVillageUnique] == NULL )
		return ;
	if ( pclVillageManager->pclVillageInfo[tempVillageUnique]->siVillageUnique <= 0 ||
		pclVillageManager->pclVillageInfo[tempVillageUnique]->siVillageUnique >= MAX_VILLAGE_NUMBER )
		return ;

	// ���� �����̸�, 	
	// ��� ���ͱ��� �����Ѵ�.
	pclinfo->clCityhallStrInfo.clProfitMoney.Set( &pclMsg->clCityhallMoney );

	// ��� �� �����ֽļ� ����
	pclinfo->clCityhallStrInfo.siTotalStockAmount += pclMsg->siAmount;


	// ��� ����� ������ �߰��Ѵ�			
	{
		cltMoney clMoney;

		clMoney.itMoney = pclMsg->siTotalPrice - pclMsg->siFee;

		pclinfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg( tempVillageUnique, RANKTYPE_CITYHALL, 
			INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH --------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 9. 20] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, tempVillageUnique, 0, 0, 
		//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, pszCharParam1, NULL);
		//	// TEMP LEEKH --------------------------------------------------------------
		//}

		// ���ӿ��� ���� ������ ����
		clMoney.itMoney = pclMsg->siFee;
		clCurrencyInfo.clOutputMoney_clStockBidTax.Increase( &clMoney );
	}

	pclStockManager->SetStockBidVillage( pclMsg->clStockBidVillageInfo.siVillageUnique_,
		pclMsg->clStockBidVillageInfo.siTotalStockAmount_,
		pclMsg->clStockBidVillageInfo.siTottalIncreaseStockAmount_,
		pclMsg->clStockBidVillageInfo.siLeftIncreaseStockAmount_,
		pclMsg->clStockBidVillageInfo.siCurrentStockPrice_,
		&pclMsg->clStockBidVillageInfo.clBiddingDate_ );

	int count = 0;

	cltGameMsgResponse_StockBidVillageList sendMsg;

	for( int i = 0; i < MAX_VILLAGE_NUMBER; ++i ) {

		if( pclStockManager->clStockBidVillageInfo[ i ].siVillageUnique_ != 0 ) {

			if( count >= MAX_VILLAGE_NUMBER )		continue;
			sendMsg.clStockBidVillageInfo[ count ].Set( &pclStockManager->clStockBidVillageInfo[ i ] );
			count++;
		}

	}

	if( count > 0 )
	{

		sendMsg.usCount = count;

		// ���� ���� ����Ʈ�� �����Ѵ�
		cltMsg clMsg( GAMEMSG_RESPONSE_STOCKBIDVILLAGELIST, sendMsg.GetTotalSize(), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	sDBRequest_InvestList clMsgInvest(tempVillageUnique);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsgInvest);

	// ������ ������ ���Ѵ�. 
	cltVillageInvestInfo* pMayorInfo = &pclVillageManager->pclVillageInfo[tempVillageUnique]->clVillageVary.clInvestInfo;

	// � ������ ���������� ������Ʈ �Ѵ�. 
	pMayorInfo->siVillageUnique = tempVillageUnique;

	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg2(GAMEMSG_RESPONSE_INVESTLIST, sizeof(cltVillageInvestInfo), (BYTE*)pMayorInfo);

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

	/*	if( pclMsg->clStockBidVillageInfo.siLeftIncreaseStockAmount_ == 0 )
	{
	sDBRequest_CompleteStockBidVillage	clMsg( tempVillageUnique );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}
	*/
	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	SendServerResponseMsg(RANKTYPE_STOCK, SRVAL_STOCK_SUCCESS_BUY_BIDSTOCK,  0, 0, pclCM->CR[id]->GetCharUnique());

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 8] // �����ֽ� ���
		// param1 == �ֹ�����.
		// param2 == ������.
		// param3 == �� �ŷ� �ݾ�.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_BID_BUY, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->siAmount, pclMsg->siFee, pclMsg->siTotalPrice, 0, 0, 
										NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_MYSTOCKINFO(sPacketHeader* pPacket)
{
	sDBResponse_MyStockInfo *pclMsg = (sDBResponse_MyStockInfo *)pPacket;

	if( pclMsg == NULL )
		return;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == false )
		return;

	if( pclMsg->siResult != 1 )
	{
		return;
	}

	// �� �ֽ��� ������Ʈ �Ѵ�. 
	pclCM->CR[id]->pclCI->clStock.clInfo.Set( &pclMsg->clInfo ); 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCK, true, 0);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETSTOCKOFFERINGINFO( sPacketHeader* pPacket )
{
	sDBResponse_GetStockOfferingInfo *pclMsg = (sDBResponse_GetStockOfferingInfo *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siVillageUnique = pclMsg->siVillageUnique;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siTotalOffering = pclMsg->siTotalOffering;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStockAmount = pclMsg->siStockAmount;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siPrice = pclMsg->siPrice;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStatus = pclMsg->siStatus;
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStockOfferingInfo"));

}

void cltServer::DoMsg_DBMSG_RESPONSE_SETSTOCKOFFERING( sPacketHeader* pPacket )
{
	sDBResponse_SetStockOffering *pclMsg = (sDBResponse_SetStockOffering *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siVillageUnique = pclMsg->siVillageUnique;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siTotalOffering = pclMsg->siTotalOffering;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStockAmount = pclMsg->siStockAmount;
	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siPrice = pclMsg->siPrice;

	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStatus = 1;
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� ���� ���� (���� û�� ����)
		// param1 == �� ���� �ֽ� ����, param2 == 1�δ� ��� �ֽ� ��, param3 == 1�δ� ��� �ֽ� ����
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_SET, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->siTotalOffering, pclMsg->siStockAmount, pclMsg->siPrice, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_ENDSTOCKOFFERING( sPacketHeader* pPacket )
{
	sDBResponse_EndStockOffering *pclMsg = (sDBResponse_EndStockOffering *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStatus = 2;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� û�� ����. 
		// 
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_END, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										0, 0, 0, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_STOCKOFFERINGORDER( sPacketHeader* pPacket )
{
	sDBResponse_StockOfferingOrder *pclMsg = (sDBResponse_StockOfferingOrder *)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id) == false ) return;

	switch( pclMsg->siResult )
	{
	case 1:
		{
			// �� ������Ʈ
			pclCM->CR[id]->pclCI->clIP.DecreaseMoney( pclMsg->siMoney );
			//pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );

			// �ֽ� ���Կ� �� ���������� �˸�
			cltGameMsgResponse_ChangeMoney clinfo(pclCM->CR[id]->pclCI->clIP.GetMoney(), 0, CHANGE_MONEY_REASON_NOTDEFINED);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			pclDelMoneyStatistics->Add(DELMONEY_STOCK, pclMsg->siMoney);
			
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� ���� û�� �ֹ�.
				// param1 == �ֽļ�.
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_ORDER, 
												0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->siMoney, pclMsg->siPersonMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siStockAmount, 0, 0, 0, 0, NULL, NULL);
			}

			SendServerResponseMsg( RANKTYPE_STOCK, SRVAL_STOCKOFFERING_SUCCESS_ORDER,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		break;

	case 2:	// ������ ����
		SendServerResponseMsg( RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;

	case 3: // 10�� �̻� �ֽ� ����
		SendServerResponseMsg( RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;

	case 4: // �ش� ���� �ֽ� ���� �̹� ��û ����
		SendServerResponseMsg( RANKTYPE_STOCK, SRVAL_STOCKOFFERING_FAIL_ORDERALREADY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETSTOCKOFFERINGORDERLIST( sPacketHeader* pPacket )
{
	sDBResponse_GetStockOfferingOrderList *pclMsg = (sDBResponse_GetStockOfferingOrderList *)pPacket;


	// �������� ���� ����Ʈ�� �޴ٰ�, ������ �������̸�( villageunique == -1 )
	if( pclMsg->siVillageUnique == -1 )
	{
		pclClient->pclLog->FilePrint(TEXT("Config\\StockLog.log"), TEXT("ORDERLIST..(last) %d"), pclStockOfferingManager->siCount );

		int i;
		SI32 villageunique = pclStockOfferingManager->siVillageUnique;
		if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER )		return;

		// ���´�.
		if( IsCountrySwitch( Switch_LotteryStockRandom ) )
		{
			if( pclStockOfferingManager->siCount >= 2)
			{
				for ( i=0; i<pclStockOfferingManager->siCount; i++)
				{
					SI32 siChoose = rand() % pclStockOfferingManager->siCount;
					SI32 siDistance = (rand() % pclStockOfferingManager->siCount) + 1;

					SI32 siPos1 = siChoose;
					SI32 siPos2 = (siChoose + siDistance) % pclStockOfferingManager->siCount;

					if( siPos1 < 0 || siPos1 >= 2000 )		continue;
					if( siPos2 < 0 || siPos2 >= 2000 )		continue;

					cltStockOfferingOrderInfo temp;

					if(siPos1 != siPos2)
					{
						temp.Set(&pclStockOfferingManager->clStockOrder[siPos1]);
						pclStockOfferingManager->clStockOrder[siPos1].Set(&pclStockOfferingManager->clStockOrder[siPos2]);
						pclStockOfferingManager->clStockOrder[siPos2].Set(&temp);
					}
				}
			}
		}

		// �տ��� ���� ��÷ ��Ų��. (������ �������Ƿ� �ᱹ�� �����̴�.)
		SI32 totalAmount = pclStockOfferingManager->clStockInfo[ villageunique ].siTotalOffering;
		SI32 offerAmount = 0;

		for( i = 0; i < pclStockOfferingManager->siCount; ++i )
		{
			if( i >= 2000 )		continue;

			cltStockOfferingOrderInfo *pOrder = &pclStockOfferingManager->clStockOrder[ i ];

			SI32 id = pclCM->GetIDFromPersonID( pOrder->siPersonID );
			
			bool bWinning = false;
			
			// ���ӿ� �������̰�, ��� ������ �ֽ��� �����ִٸ�,
			if( id && offerAmount < totalAmount )
				bWinning = true;

			// ������ ��÷�� IP, MACADDRESS�� ������ ��÷���� �ʴ´�. - �ߺ� ��밳���� ������ �� �ִ�.
			if( IsCountrySwitch( Switch_LotteryStockRandom ) )
			{
				// ��÷�Ǵ� ��쿡�� üũ�Ѵ�. - ���ʿ��� CPU���� ����
				if( bWinning == true)
				{
					if( pclStockOfferingManager->CheckStockOfferingOrderDuplicate(pOrder->szIP, pOrder->szPrivateIP, pOrder->szMacAddress) )
						bWinning = false;
				}
			}
			
			//if( id && offerAmount < totalAmount )
			if( bWinning )
			{				
				offerAmount += pOrder->siStockAmount;

				sDBRequest_ExecuteStockOfferingOrder clMsg( 
					id,
					1, 
					villageunique, 
					pOrder->siPersonID,
					pOrder->siStockAmount,
					pOrder->siMoney,
					pOrder->szIP,
					pOrder->szPrivateIP,
					pOrder->szMacAddress );

				pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );		
			}
			else
			{
				sDBRequest_ExecuteStockOfferingOrder clMsg( 
					id,
					2, 
					villageunique, 
					pOrder->siPersonID,
					pOrder->siStockAmount,
					pOrder->siMoney,
					pOrder->szIP,
					pOrder->szPrivateIP,
					pOrder->szMacAddress);

				pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
			}
		}

		// ��÷ �Ϸ�..
		pclStockOfferingManager->bLottery = FALSE;
		pclStockOfferingManager->siCount = 0;

		pclStockOfferingManager->siVillageUnique = 0;
		pclStockOfferingManager->siDuplicateCount = 0;

		sDBRequest_ResetStockOfferingOrderList clMsg( villageunique );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

		sDBRequest_GetStrInfo clMsg2(0, villageunique, RANKTYPE_CITYHALL );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg2);			

		cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
		cltMoney clMoney;

		clMoney.itMoney = offerAmount * pclStockOfferingManager->clStockInfo[ villageunique ].siPrice;

		pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pStrInfo->clCityhallStrInfo.clProfitMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg( villageunique, RANKTYPE_CITYHALL, 
			INOUTCODE_STOCK, &pclTime->clDate, &clMoney, &pStrInfo->clCityhallStrInfo.clProfitMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH --------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 9. 20] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);
		//
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, villageunique, 0, 0, 
		//									clMoney.itMoney, pStrInfo->clCityhallStrInfo.clProfitMoney.itMoney, 0, 0, 0, 
		//									pszCharParam1, NULL);
		//	// TEMP LEEKH --------------------------------------------------------------
		//}
	}
	else
	{
		int i = pclStockOfferingManager->siCount;

		if( i < 2000 ) {
		
			pclStockOfferingManager->clStockOrder[ i ].siVillageUnique = pclMsg->siVillageUnique;
			pclStockOfferingManager->clStockOrder[ i ].siPersonID = pclMsg->siPersonID;
			pclStockOfferingManager->clStockOrder[ i ].siStockAmount = pclMsg->siStockAmount;
			pclStockOfferingManager->clStockOrder[ i ].siMoney = pclMsg->siMoney;
			StringCchCopy(pclStockOfferingManager->clStockOrder[ i ].szIP,			sizeof(pclStockOfferingManager->clStockOrder[ i ].szIP),		 pclMsg->szIP);
			StringCchCopy(pclStockOfferingManager->clStockOrder[ i ].szPrivateIP,	sizeof(pclStockOfferingManager->clStockOrder[ i ].szPrivateIP),  pclMsg->szPrivateIP);
			StringCchCopy(pclStockOfferingManager->clStockOrder[ i ].szMacAddress,	sizeof(pclStockOfferingManager->clStockOrder[ i ].szMacAddress), pclMsg->szMacAddress);
			
			pclStockOfferingManager->siCount = i + 1;

			pclClient->pclLog->FilePrint(TEXT("Config\\StockLog.log"), TEXT("ORDERLIST..(make) %d, IP:%s(%s), MAC:%s"), pclMsg->siPersonID, pclMsg->szIP, pclMsg->szPrivateIP, pclMsg->szMacAddress );
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_EXECUTESTOCKOFFERINGORDER( sPacketHeader* pPacket )
{
	sDBResponse_ExecuteStockOfferingOrder *pclMsg = (sDBResponse_ExecuteStockOfferingOrder *)pPacket;

	pclClient->pclLog->FilePrint(TEXT("Config\\StockLog.log"), TEXT("excute result %d, type %d, personid %d, IP:%s(%s), MAC:%s"), pclMsg->siResult, pclMsg->siType, pclMsg->siPersonID, pclMsg->szIP, pclMsg->szPrivateIP, pclMsg->szMacAddress );

	if( pclMsg->siResult == 1 )
	{
		if( pclMsg->siType == 1)  // ��÷
		{
			SI32 id = pclMsg->usCharID;

			if(pclCM->IsValidID(id) )
			{		
				//�ֽ��� ������Ʈ �Ѵ�
				pclCM->CR[id]->pclCI->clStock.clInfo.Add(pclMsg->siVillageUnique, pclMsg->siStockAmount);

				//������Ʈ �� ������ Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

				//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				//{
				//	// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� û�� �ֹ� ����.
				//	// param1 == Ÿ��. 
				//	// param2 == ����.
				//	cltServer * pclServer = (cltServer*)pclClient;
				//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_ORDER_EXECUTE, 
				//									0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siMoney, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				//									pclMsg->siType, pclMsg->siStockAmount, 0, 0, 0, NULL, NULL);
				//}
			}

			cltLetterMsg_StockOfferingResult clletter( pclMsg->siType, pclMsg->siVillageUnique, pclMsg->siStockAmount, pclMsg->siMoney );
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclMsg->siPersonID, (cltLetterHeader*)&clletter);

		} 
		else
		{				  // �̴�÷

			SI32 id = pclMsg->usCharID;

			if(pclCM->IsValidID(id) )
			{		
				//------------------------------
				// ���� ���� ������Ʈ. 
				//------------------------------
				// ���� ������ Ȯ���Ѵ�. 
				pclCM->CR[id]->pclCI->clBank.IncreaseMoney(pclMsg->siMoney);

				// Ŭ���̾�Ʈ�� ������ ������. 
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);
			}

			cltLetterMsg_StockOfferingResult clletter( pclMsg->siType, pclMsg->siVillageUnique, pclMsg->siStockAmount, pclMsg->siMoney );
			// ������ DB�� Ŭ���̾�Ʈ���� ������. 
			SendLetterMsg(pclMsg->siPersonID, (cltLetterHeader*)&clletter);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� û�� �ֹ� ����.
			//	// param1 == Ÿ��. param2 == ����.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	cltCharServer* pclchar = NULL;
			//	if( pclCM->IsValidID(id) )		pclchar = (cltCharServer*)pclCM->CR[id];
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_ORDER_EXECUTE, 
			//									0, pclchar, NULL, 0, pclMsg->siMoney, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
			//									pclMsg->siType, pclMsg->siStockAmount, 0, 0, 0, NULL, NULL);
			//}
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� û�� �ֹ� ����.
			// param2 == ����.
			cltServer * pclServer = (cltServer*)pclClient;
			cltCharServer* pclchar = NULL;
			SI32 id = pclMsg->usCharID;
			if( pclCM->IsValidID(id) )		pclchar = (cltCharServer*)pclCM->CR[id];
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_ORDER_EXECUTE, 
				pclMsg->siType, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siMoney, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				0, pclMsg->siStockAmount, 0, 0, 0, NULL, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_RESETSTOCKOFFERINGORDERLIST( sPacketHeader* pPacket )
{
	sDBResponse_ResetStockOfferingOrderList *pclMsg = (sDBResponse_ResetStockOfferingOrderList *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	pclStockOfferingManager->clStockInfo[ pclMsg->siVillageUnique ].siStatus = 0;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 8] // �ֽ� û�� �ֹ� ����.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_OFFERING_ORDER_RESET, 
							 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							 0, 0, 0, 0, 0, NULL, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_EXCHANGESTOCK( sPacketHeader* pPacket )
{
	sDBResponse_ExchangeFromStock *pclMsg = (sDBResponse_ExchangeFromStock *)pPacket;

	SI32 id = pclMsg->siCharID;
	if( 1 != pclMsg->siResult )
	{
		/// ������ �ƴϹǷ� ����
		if( -1 == pclMsg->siResult )
		{
			if( pclCM->IsValidID(id) ) 
			{
				cltGameMsgResponse_ExchangeStock clExchangeStock( false, 0, 0, 0 );
				cltMsg clMsg( GAMEMSG_RESPONSE_EXCHANGESTOCK, sizeof(clExchangeStock), (BYTE*)&clExchangeStock);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
			}
		}
		return;
	}

	SI32 villageUnique = pclMsg->siStockUnique;
	SI32 sellAmount = pclMsg->siSellAmount;
	SI32 leftAmount = pclMsg->siLeftStockAmount;
	SI32 totalStockAmount = pclMsg->siTotalStockAmount;
	
	if( pclCM->IsValidID(id) ) 
	{
		// �ֽ��� ������Ʈ ���ش�.
		pclCM->CR[id]->pclCI->clStock.clInfo.Set( villageUnique, leftAmount );
		pclCM->CR[id]->SetUpdateSwitch( UPDATE_STOCK, true, 0 );

		cltGameMsgResponse_ExchangeStock clExchangeStock( true, villageUnique, sellAmount, leftAmount );
		cltMsg clMsg( GAMEMSG_RESPONSE_EXCHANGESTOCK, sizeof(clExchangeStock), (BYTE*)&clExchangeStock);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	/// �ش� ������ �� �ֽļ� ������Ʈ
	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( villageUnique );

	if(pclinfo != NULL)
	{
		pclinfo->clCityhallStrInfo.siTotalStockAmount = totalStockAmount;
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GIVESTOCK( sPacketHeader* pPacket )
{
	sDBResponse_GiveStock *pclMsg = (sDBResponse_GiveStock*)pPacket;
	if ( pclMsg == NULL )
	{
		return;
	}

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 siCharID = pclMsg->siCharID;
	if ( pclCM->IsValidID(siCharID) == NULL )
	{
		return;
	}

	SI32 siVillageUnique	= pclMsg->siVillageUnique;
	SI32 siAmount			= pclMsg->siStockAmount;

	// �ֽ��� ������Ʈ ���ش�.
	pclCM->CR[siCharID]->pclCI->clStock.clInfo.Set( siVillageUnique, siAmount );
	pclCM->CR[siCharID]->SetUpdateSwitch( UPDATE_STOCK, true, 0 );

}
