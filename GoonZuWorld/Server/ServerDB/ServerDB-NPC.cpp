//---------------------------------
// 2003/8/19 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"
#include "../CommonLogic/Msg/MsgType-NPC.h"

#include "../../Server/AuthServer/AuthMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-ForeignMerchantNPC.h"
#include "../../DBManager/GameDBManager_World/DBMsg-IPGClient.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Market.h"


#include "SystemNPC\SystemNPC.h"
#include "SystemNPC\ForeignMerchantNPC\ForeignMerchantNPC.h"

#include "../../CommonLogic/MsgType-Person.h"

// NPC���� �Ǹ��� ���� ��û�ϴ� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_SELLNPC(sPacketHeader* pPacket)
{
	sDBResponse_SellNPC* pclMsg = (sDBResponse_SellNPC*)pPacket;

	if(pclMsg->siResult != 1 )
	{
		return ;
	}

	SI32 id = pclMsg->usCharID;

	GMONEY BMoney = 0;
	if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		if( pclMsg->siItemPos >= 0 || pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			// �κ��丮�� ������Ʈ �Ѵ�. 
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		
		BMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();
		
		// ���� �ڱ��� ������Ʈ �Ѵ�. 
		pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siMoney);

		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);
		
		// �ŷ� ������ �˷��ش�. 
		cltMsg clMsg(GAMEMSG_RESPONSE_SELLNPC, SYSTEMNPC_SUCCESS_SELL);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		
		// NPC �ŷ� �ݾ��� �Ϻθ� ������ ���Ѵ�.
		GMONEY incmoney = pclMsg->siChangedMoney;

		// ���� �κи� ������ ���ͱ����� 
		incmoney = incmoney * VILLAGE_PROFIT_RATE_FOR_MERCHANT / 100;
		if(incmoney)
		{
			// villageunique�� �ڱ� ����
			SI32 villageunique = pclMsg->siVillageUnique;

			if(villageunique > 0)
			{	
				//sDBRequest_ChangeStrMoney sendMsg(CHANGESTRMONEY_SELLNPC, 0, villageunique, RANKTYPE_CITYHALL, incmoney);
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, villageunique, incmoney );
				
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // NPC���� �Ǹ�.
			// param1 == �������� ��ġ, param2 == ������ ����ũ.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_SELL_ITEM, 
								 0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->siSellMoney * pclMsg->clSellItem.siItemNum, pclMsg->siMoney, 
								 &pclMsg->clSellItem, pclMsg->clItem.siItemNum, 0, pclMsg->siNPCKind, pclMsg->siVillageUnique, 0, 0, 
								 pclMsg->siItemPos, 0, 0, 0, 0, NULL, NULL);
		}
	}

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	// [�α��߰� : Ȳ���� 2007. 10. 9] // NPC �Ǹ�.
	//SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NPCTRADE, LOGCOMMAND_INDEX_NPCTRADE_SELL, 
	//					 0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
	//					 0, 0, 0, 0, 0, NULL, NULL);
	//}

	// ������ �Ǹ� �ܰ��� �����̻��� �Ǹ� �α׿� ����.
	// ĳ���͸�, ����������ũ, �Ǹŵ� �����۰���, �ȱ����� ĳ������ ������, ������ ĳ������ �������� ���.
	if(pclMsg->siItemNum > 0 && (pclMsg->siChangedMoney / pclMsg->siItemNum) >= 10000)
	{
		pclLog->FilePrint(TEXT("Config\\SellItemLog.log"), TEXT("Name:%s	ItemUnique:%d	ItemNum:%d	Before Money:%I64d	After Money:%I64d"),
			    pclCM->CR[id]->GetName(), pclMsg->siIitemUnique, pclMsg->siItemNum, BMoney, pclMsg->siMoney);
	}	
}


// NPC���Լ� ������ ���� ��û�ϴ� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_BUYNPC(sPacketHeader* pPacket)
{
	sDBResponse_BuyNPC* pclMsg = (sDBResponse_BuyNPC*)pPacket;

	if( pclMsg->siResult != 1 )
	{
		return ;
	}


	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			// �κ��丮�� ������Ʈ �Ѵ�. 
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		// ���� �ڱ��� ������Ʈ �Ѵ�. 
		pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siMoney);

		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);


		SI32 itemUnique = pclMsg->clItem.siUnique;
		SI32 type = pclClient->pclItemManager->GetItemType(itemUnique);
		SI32 rtnMsg;				// ������ �޼���

		//������ Ÿ�Կ� �ٸ� ȿ������ ���� ���ؼ� 

		if( itemUnique == ITEMUNIQUE(7850)  || itemUnique == ITEMUNIQUE(13600))		rtnMsg = SYSTEMNPC_SUCCESS_BUY_ARROW;	//ȭ��
		else if( itemUnique == ITEMUNIQUE(7855) || itemUnique == ITEMUNIQUE(13601))	rtnMsg = SYSTEMNPC_SUCCESS_BUY_BULLET;	//�Ѿ�
		
		else
		{
			switch( type)
			{
			case ITEMTYPE_FOOD:		//����
				rtnMsg = SYSTEMNPC_SUCCESS_BUY_FOOD;	
				break;
			case ITEMTYPE_HEAL:		//��
				rtnMsg = SYSTEMNPC_SUCCESS_BUY_HEAL;	
				break;
			default:				//�⺻
				rtnMsg = SYSTEMNPC_SUCCESS_BUY;
				break;
			}
		}
		// �ŷ� ������ �˷��ش�. 
		cltMsg clMsg(GAMEMSG_RESPONSE_BUYNPC, rtnMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // NPC���� ����.
			// param1 == ������ ��ġ.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_BUY_ITEM, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->siBuyMoney*pclMsg->clBuyItem.siItemNum, pclMsg->siMoney, &pclMsg->clBuyItem, pclMsg->clItem.siItemNum, 0, pclMsg->siNPCkind, 0, 0, 0, 
											pclMsg->siItemPos, 0, 0, 0, 0, NULL, NULL);
		}

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // NPC ����.
		//// param1 == �ŷ���������.
		//SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NPCTRADE, LOGCOMMAND_INDEX_NPCTRADE_BUY, 
		//	0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
		//	rtnMsg, 0, 0, 0, 0, NULL, NULL);
		//}
	}
}


// ���� ���� NPC �� ������ DB�� �����Ѵ�.
void cltServer::DoMsg_DBMSG_RESPONSE_SETFOREIGNMERCHANTNPCINFO( sPacketHeader* pPacket )
{
	sDBResponse_SetForeignMerchantNPCInfo* pclMsg = (sDBResponse_SetForeignMerchantNPCInfo*)pPacket;

	if( pclMsg->siResult != 1 )
	{
		return ;
	}

	return;
}

// ���� ���� NPC �� ������ DB�� ���� �޾ƿ´�.
void cltServer::DoMsg_DBMSG_RESPONSE_GETFOREIGNMERCHANTNPCINFO( sPacketHeader* pPacket )
{
	/*
	sDBResponse_GetForeignMerchantNPCInfo* pclMsg = (sDBResponse_GetForeignMerchantNPCInfo*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if ( pclMsg->siResult == -1 )				// ���� �����Ͱ� ����.
	{
		pclForeignMerchantNPCMgr->SetReady( true );
		return ;
	}


	pclForeignMerchantNPCMgr->Set
		(
		pclMsg->siForeignMerchantKind,
		pclMsg->siItemUnique,
		pclMsg->siPrice,
		pclMsg->siRestNum,
		pclMsg->clDate 
		);


	pclForeignMerchantNPCMgr->SetReady( true );

	*/
	return;
}

// ���� ���� NPC �� ĳ�� ������ ����
void cltServer::DoMsg_DBMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM( sPacketHeader* pPacket )
{
	sDBResponse_ForeignMerchantBuyCashItem* pclMsg = (sDBResponse_ForeignMerchantBuyCashItem*)pPacket;

	if( pclMsg->siResult != 1 )
	{
		return ;
	}

	SI32 id = pclMsg->siCharID;
	
	PushCash( id, pclMsg->siPersonID, pclMsg->szAccountID, pclMsg->uiEventMoney, PUSHCASH_FOREIGNMERCHANTBUY );	

	if( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemPos ].Set( &pclMsg->clLeftItem );

			cltGameMsgResponse_ForeignMerchantBuyCashItem clGameMsgResponse_ForeignMerchantBuyCashItem( pclMsg->siItemPos, &pclMsg->clLeftItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEM, sizeof(clGameMsgResponse_ForeignMerchantBuyCashItem), (BYTE*)&clGameMsgResponse_ForeignMerchantBuyCashItem);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ������ ĳ�������� �ǸŽ� ���.
			// param1 == siForeignMerchantCharID,
			// param2 == siForeignMerchantCharUnique,
			// param3 == ��������ġ
			// param4 == �̺�Ʈ ���
			// pszparam1 == ����
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_NPC, LOGCOMMAND_INDEX_NPC_TRADE_MERCHANT_BUY_CASHITEM, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clLeftItem, 0, 0, pclMsg->siForeignMerchantKind, 0, 0, 0, 
											pclMsg->siForeignMerchantCharID, 
											pclMsg->siForeignMerchantCharUnique, 
											pclMsg->siItemPos, 
											pclMsg->uiEventMoney, 
											0,
											pclMsg->szAccountID, 
											NULL);
		}

	}	

	return;
}

// NPC���Լ� ��õ����Ʈ�� ��ǰ�� ������ ���� ��û�ϴ� �Ϳ� ���� ����.  
void cltServer::DoMsg_DBMSG_RESPONSE_BUYRECOMMANDPRODUCT(sPacketHeader* pPacket)
{
	sDBResonse_BuyRecommendProduct* pclMsg = (sDBResonse_BuyRecommendProduct*)pPacket;
	
	if( pclMsg->siResult != 1 )
	{
		return ;
	}

	SI32 id = pclMsg->usCharID;
	if( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			// �κ��丮�� ������Ʈ �Ѵ�. 
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

		// �������� �ŷ� ����� �˷��ش�. 
		cltGameMsgResponse_BuyRecommandProduct clinfo( pclMsg->siUsedPoint , pclMsg->siRecommendPoint, &pclMsg->clItem );
		cltMsg clMsg(GAMEMSG_RESPONSE_BUYRECOMMANDPRODUCT, sizeof(clinfo), (BYTE*)&clinfo  );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ��õ ����Ʈ�� �������� ����.
			// param1 == ������ ��ġ,
			// param2 == ��� ����Ʈ, 
			// param3 == ���� ����Ʈ.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_BUY_RECOMMEND_PRODUCT, 
								 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem_Log, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
								 pclMsg->siItemPos, pclMsg->siUsedPoint, pclMsg->siRecommendPoint, 0, 0, 
								 NULL, NULL);
		}
	}
}


// NPC���Լ� �ڽ��� ��õ������ ����� ������� ����� ���´�.
void cltServer::DoMsg_DBMSG_RESPONSE_RECOMMANDPOINTLIST(sPacketHeader* pPacket)
{
	sDBResponse_RecommendPointList* pclMsg = (sDBResponse_RecommendPointList*)pPacket;
	/*
	if( pclMsg->siResult != 1 )
	{

		//todo:



		return ;
	}*/

	SI32 id = pclMsg->uiCharID;
	if(pclCM->IsValidID(id) == false) return;

    if( pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID) return;



	cltGameMsgResponse_RecommandPointList clinfo(pclMsg->siCurrentPage,pclMsg->siMaxPage,pclMsg->sRPListData);
	cltMsg clMsg( GAMEMSG_RESPONSE_RECOMMANDPOINTLIST, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

//KHY - 0530 ���� ���� ��������.
void cltServer::DoMsg_DBMSG_RESPONSE_GET_FOREIGNMERCHANTBUYLIMIT(sPacketHeader* pPacket)
{
	sDBResponse_GetForeignMerchantBuyLimit* pclMsg = (sDBResponse_GetForeignMerchantBuyLimit*)pPacket;

	if(pclMsg->siResult == 1) //����
	{
		gForeignMerchantBuyLimit = pclMsg->gPrice;
		fForeignMerchantPercentUP = pclMsg->fUpPercent;
		fForeignMerchantPercentDOWN = pclMsg->fDownPercent;
	}
	else
	{
		gForeignMerchantBuyLimit = 0	;
		fForeignMerchantPercentUP = 0	;
		fForeignMerchantPercentDOWN = 0	;
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_GET_FOREIGNMERCHANTNOWMONEY(sPacketHeader* pPacket)
{
	sDBResponse_GetForeignMerchantNowMoney* pclMsg = (sDBResponse_GetForeignMerchantNowMoney*)pPacket;

	if(pclMsg->siResult == 1) //����
		gForeignMerchantNowMoney = pclMsg->gPrice;
	else
		gForeignMerchantNowMoney = 0;
}

