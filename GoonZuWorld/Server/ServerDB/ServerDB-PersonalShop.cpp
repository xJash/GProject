//---------------------------------
// 2004/8/17 ������
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"


#include "..\..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

#include "..\../../Server/AuthServer/AuthMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-PersonalShop.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "Skill\Skill-Manager.h"

#include "MsgType-Person.h"
#include "MsgType-Item.h"
#include "Msg/MsgType-Personalshop.h"


void cltServer::DOMSG_DBMSG_RESPONSE_STARTPERSONALSHOP(sPacketHeader* pPacket)
{
	sDBResponse_StartPersonalShop* pclMsg = (sDBResponse_StartPersonalShop*)pPacket;

	// �ش� Item�� ����.
	if(pclMsg->siResult == 0)			return;

	SI32 id = pclMsg->siCharID;
	if(pclCM->IsValidID(id) == false)	return;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	//================================================ 
	// Client�� ������ �κ��丮 Update�Ѵ�.
	if(pclchar->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	//================================================ 
	
	//================================================ 
	// �������� Ticket�� ����ϸ� ������ 5000���� �߰��Ѵ�.
	if(pclMsg->siVillageUnique>0 && pclMsg->siVillageUnique < MAX_VILLAGE_NUMBER)
	{
		sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, pclMsg->siVillageUnique, VILLAGE_PROFIT_FOR_PERSONALSHOP );
		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
	}
	//================================================ 

	//============= ���λ����� �����Ѵ�. ============= 
	// ĳ������ ���λ����� �����Ѵ�. 
	pclchar->SetHeadChat(false, NULL);				// �Ӹ����� �����. 
	pclchar->SetPersonalShopData(true, NULL);		// ������ ������ �����Ѵ�.
	//================================================ 
	//================================================ 
	// ���� ������ �����Ѵ�.
	{
		cltGameMsgResponse_StartPersonalShop clinfo(pclchar->GetCharUnique(), 1, pclchar->bPremiumPersonalShop,pclMsg->m_siShopMode );
		cltMsg clMsg(GAMEMSG_RESPONSE_STARTPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			SI32 siCommandType = 0;
			SI32 siCommandIndex = 0;
			SI32 siReason = 0;
			if( pclMsg->m_siShopMode == PSHOP_MODE_MAKEITEM || 
				pclMsg->m_siShopMode == PSHOP_MODE_MAKEITEM_WANT)
			{
				siCommandType = LOGCOMMAND_TYPE_COMMISSION;
				siCommandIndex = LOGCOMMAND_INDEX_COMMISSION_START;
				siReason = USEITEM_REASON_COMMISSION;
			}
			else
			{
				siCommandType = LOGCOMMAND_TYPE_PRIVATETRADE;
				siCommandIndex = LOGCOMMAND_INDEX_PRIVATETRADE_START;
				siReason = USEITEM_REASON_PERSONSHOP;
			}

			// PCK : ������ ���α� ��� ����.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
				siReason, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem_Log, 0, 
				0, 0, 0, 0, 0, pclMsg->siItemPos, 0, 0, 0, 0, NULL, NULL);

			// [�α��߰� : Ȳ���� 2007. 10. 16] // ���λ��� ���� ����. 
			// param1 == �����̾� ����. param2 == ������ ����ũ
			SendLog_WriteLogToDB(siCommandType, siCommandIndex, 
				0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
				pclchar->bPremiumPersonalShop, pclMsg->clItem.siUnique, 0, 0, 0, NULL, NULL);
		}

	}
	//================================================ 
	//================================================ 
	// �̿��鿡�� ���λ��� ���ʸ� ������.
	{
		cltGameMsgResponse_PersonalShopBanner clinfo(pclchar->GetCharUnique(), pclchar->bPersonalShopSwitch, &pclchar->clShopBanner);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONALSHOPBANNER, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	//================================================ 

	//���λ��� ���� ����Ʈ�� ���������� Ȯ���Ѵ�. 
	((cltCharServer*)pclCM->CR[id])->DoQuestCheckAndAction(QUEST_CLEAR_COND_OPENPBSTORE);
}


void cltServer::DOMSG_DBMSG_RESPONSE_PERSONALSHOPBUYITEM(sPacketHeader* pPacket)
{
	sDBResponse_PersonalShopBuyItem * pclMsg = (sDBResponse_PersonalShopBuyItem *)pPacket;
	SI32 buyercharid	= pclMsg->siCharID;
	SI32 buyerpersonid	= pclMsg->siBuyerPersonID;
	SI32 buyerinvpos	= pclMsg->siBuyerInvPos;

	SI32 shoppercharid	= pclMsg->siShopperCharID;
	SI32 shopperpersonid= pclMsg->siShopperPersonID;
	SI32 shopperinvpos	= pclMsg->siShopperInvPos;
	GMONEY itemcoast = pclMsg->siItemCost;
	SI32 itemnum = pclMsg->siBuyItemNum;
	SI32 itemunique = pclMsg->clBuyerInvItem.siUnique;

	// ���������� �������� �ʴ´ٸ� ����â�� �ݵ��� �Ѵ�.
	cltShopTradeData	clShopData;
	clShopData.Init();
	clShopData.m_siShopMode = PSHOP_MODE_NONE;
	clShopData.m_siPersonID = shopperpersonid;


	if ( pclMsg->siResult < 1 )	
	{	
		// ���ŵ� ���������� ������ ���۹޴´�.
		if(pclCM->IsValidID(shoppercharid) == TRUE && pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
		{
			cltCharServer* pclcharshopper = ((cltCharServer*)pclCM->CR[shoppercharid]);

			if( pclMsg->siShowCaseIndex >= 0 && pclMsg->siShowCaseIndex < MAX_ITEM_PER_PERSON )
			{
				pclcharshopper->clShopData.m_clItem[pclMsg->siShowCaseIndex].siItemNum += pclMsg->siBuyItemNum;
			}

			// ������ �������� �ʰ� �ִٸ� ������ �ݵ��� �Ѵ�.
			if(pclcharshopper->bPersonalShopSwitch == false)	
				pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
		
			clShopData.Set(&pclcharshopper->clShopData);
		}

		if(pclCM->IsValidID(buyercharid) == TRUE)
		{
			if(pclCM->CR[buyercharid]->pclCI->GetPersonID() == buyerpersonid)
			{
				// Client���� siSuccess ���������� �����Ѵ�.
				cltGameMsgResponse_BuyPersonalShop clInfo(buyercharid, BUYPERSONALSHOP_FAIL_UNKNOWN, pclMsg->clBuyerInvItem.siUnique,  pclMsg->siBuyItemNum);
				cltMsg clMsg(GAMEMSG_RESPONSE_BUYPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
				pclCM->CR[buyercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				
				//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				//{
				//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����.
				//	// param1 == ��� , param2 == �� ������ �κ���ġ. param3 == ������ ����ũ, param4 == ������ ���� �ش� ������ ��������
				//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_BUY, 
				//						0, (cltCharServer*)(pclCM->CR[buyercharid]), NULL, pclMsg->siShopperPersonID, 0, 0, &pclMsg->clBuyItem, 0, 0, 0, 0, 0, 0, 
				//						BUYPERSONALSHOP_FAIL_UNKNOWN, pclMsg->siBuyerInvPos, pclMsg->clBuyerInvItem.siUnique, pclMsg->clBuyerInvItem.siItemNum, 0, NULL, NULL);	
				//}

				// ���λ��� ���������� ������.
				{
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[buyercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				
			}
		}
	}
	else // ������ 
	{
		BOOL bShopSoldOut = TRUE;
		//===========================================================
		// ���������� ������ �����ϰ� ���ŵ� ������ �����ϵ��� �Ѵ�.
		//===========================================================
		if(pclCM->IsValidID(shoppercharid) == TRUE && pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
		{
			// �ǸſϷῡ ����
			cltCharServer* pclcharshopper = ((cltCharServer*)pclCM->CR[shoppercharid]);
			
			// ������ �������� �ʰ� �ִٸ� ������ �ݵ��� �Ѵ�.
			if(pclcharshopper->bPersonalShopSwitch == false)	
				pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
			
			
			for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
			{
				if(pclcharshopper->clShopData.m_clItem[i].siItemNum > 0 )
				{
					bShopSoldOut = FALSE;
					break;
				}
			}
			// ���������� ���� ������ٸ� ������� ����
			if(bShopSoldOut == TRUE)	pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
			clShopData.Set(&pclcharshopper->clShopData);

			// ���� ������ ��������� Update �Ѵ�. 
			pclcharshopper->SetPersonalShopBanner(&pclcharshopper->clShopData);


			//���λ��� �Ǹ� ����Ʈ�� ���������� Ȯ���Ѵ�. 
			pclcharshopper->DoQuestCheckAndAction(QUEST_CLEAR_COND_SELLFROMPBSTORE);
		}
		
		

		
		// ������ 
		if(pclCM->IsValidID(buyercharid) == TRUE)
		{
			if(pclCM->CR[buyercharid]->pclCI->GetPersonID() == buyerpersonid)
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( buyerinvpos >= 0 || buyerinvpos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[buyercharid]->pclCI->clCharItem.clItem[buyerinvpos].Set(&pclMsg->clBuyerInvItem);

					cltGameMsgResponse_PersonItemInfo clinfo(buyerinvpos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clBuyerInvItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[buyercharid]->SendNetMsg((sPacketHeader*)&clMsg);
					
				}
				// ���� �ڱ��� ������Ʈ �Ѵ�. 
				pclCM->CR[buyercharid]->pclCI->clIP.SetMoney(pclMsg->siBuyerMoney);
				pclCM->CR[buyercharid]->SetUpdateSwitch(UPDATE_IP, true, 0);
				
				// Client���� ���������� �����ش�.			
				{
					cltGameMsgResponse_BuyPersonalShop clInfo(buyercharid, BUYPERSONALSHOP_SUCCESS_BUY, pclMsg->clBuyerInvItem.siUnique);
					cltMsg clMsg(GAMEMSG_RESPONSE_BUYPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[buyercharid]->SendNetMsg((sPacketHeader*)&clMsg);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� �Ǹ� ����.
						// param1 == �Ǹ� ������ �κ���ġ. 
						// param2 == ������ ����ũ, 
						// param3 == ������ ���� �ش� ������ ��������
						//SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_SELL, 
						//					0, (cltCharServer*)(pclCM->CR[pclMsg->siShopperCharID]), NULL, pclMsg->siBuyerPersonID, 0, 0, &pclMsg->clBuyItem, 0, 0, 0, 0, 0, 0, 
						//					pclMsg->siShopperInvPos, pclMsg->clShopperInvItem.siUnique, pclMsg->clShopperInvItem.siItemNum, 0, 0, NULL, NULL);	
					
						// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����.
						// param1 == �� ������ �κ���ġ. 
						// param2 == ������ ����ũ, 
						// param3 == ������ ���� �ش� ������ ��������
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_BUY, 
											0, (cltCharServer*)(pclCM->CR[buyercharid]), NULL, pclMsg->siShopperPersonID,  pclMsg->siItemCost, pclMsg->siBuyerMoney, &pclMsg->clBuyItem, 0, 0, 0, 0, 0, 0, 
											pclMsg->siBuyerInvPos, pclMsg->clBuyerInvItem.siUnique, pclMsg->clBuyerInvItem.siItemNum, 0, 0, NULL, NULL);	
					}

					

				}
				
				// ���λ��� ���������� ������.
				{
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData,itemunique , itemnum, itemcoast, TRUE);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[buyercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				
				//���λ��� ���� ����Ʈ�� ���������� Ȯ���Ѵ�. 
				((cltCharServer*)pclCM->CR[buyercharid])->DoQuestCheckAndAction(QUEST_CLEAR_COND_BUYFROMPBSTORE);
				
			}
		}


		//===========================================================
		// �������� 
		//===========================================================

		if(pclCM->IsValidID(shoppercharid) == TRUE)
		{
			if(pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( shopperinvpos >= 0 && shopperinvpos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[shoppercharid]->pclCI->clCharItem.clItem[shopperinvpos].Set(&pclMsg->clShopperInvItem);

					cltGameMsgResponse_PersonItemInfo clinfo(shopperinvpos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clShopperInvItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[shoppercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}

				// ���� �ڱ��� ������Ʈ �Ѵ�. 
				pclCM->CR[shoppercharid]->pclCI->clIP.SetMoney(pclMsg->siShopperMoney);
				pclCM->CR[shoppercharid]->SetUpdateSwitch(UPDATE_IP, true, 0);

				//[����] �ͼ����� �̿�� �Ҹ�. ����� �������� �ŷ��� �Ǹ� �ϳ��� ���ش�. ��? ������ ��ϱ�.���� => 2008-4-21
				cltCharServer* pclchar = (cltCharServer* )pclCM->CR[shoppercharid];
				if(0 < pclchar->clShopData.m_clSpacialItem.siUnique)
				{
					sDBRequest_UseItem useitem(shoppercharid, 
												pclchar->pclCI->GetPersonID(), 
												pclchar->clShopData.m_siSelectedSpacialInventoryPos, 
												&pclchar->clShopData.m_clSpacialItem, 
												USEITEM_REASON_NONE);
					pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
				}
				
				
				// ������ ���� �ȸ��� Stop��Ű���� �Ѵ�.
				//else
				{

					// ���λ��� ���������� ������.
					// TODO : �ȸ� ������ ����, �Լ��� �ݾ� ǥ��
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData,itemunique , itemnum, itemcoast,FALSE );
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[shoppercharid]->SendNetMsg((sPacketHeader*)&clMsg);

					if(bShopSoldOut == TRUE)
					{
						// ĳ������ ���λ����� �����Ѵ�. 
						((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopBanner(NULL);
						((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopData(false, NULL);

						// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
						cltGameMsgResponse_StopPersonalShop clinfo(pclCM->CR[shoppercharid]->GetCharUnique(), pclCM->CR[shoppercharid]->pclCI->GetPersonID(), 2);
						cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
						((cltCharServer*)pclCM->CR[shoppercharid])->SendNeighbourMsg(&clMsg, true);

						if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
						{
							// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����. 
							// param1 == ���.
							SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_END, 
												0, (cltCharServer*)(pclCM->CR[shoppercharid]), NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
												2, 0, 0, 0, 0, NULL, NULL);
						}
					}
				}
			}
		}
	}

	return;
}

void cltServer::DOMSG_DBMSG_RESPONSE_PERSONALSHOPSELLITEM(sPacketHeader* pPacket)
{
	sDBResponse_PersonalShopSellItem * pclMsg = (sDBResponse_PersonalShopSellItem *)pPacket;
	SI32 sellercharid	= pclMsg->siCharID;
	SI32 sellerpersonid	= pclMsg->siSellerPersonID;
	SI32 sellerinvpos	= pclMsg->siSellerInvPos;

	SI32 shoppercharid	= pclMsg->siShopperCharID;
	SI32 shopperpersonid= pclMsg->siShopperPersonID;
	SI32 shopperinvpos	= pclMsg->siShopperInvPos;
	SI32 itemnum   = pclMsg->siSellItemNum;
	GMONEY itemcoast = pclMsg->siItemCost;
	SI32 itemunique = pclMsg->clShopperInvItem.siUnique;

	// ���������� �������� �ʴ´ٸ� ����â�� �ݵ��� �Ѵ�.
	cltShopTradeData	clShopData;
	clShopData.Init();
	clShopData.m_siShopMode = PSHOP_MODE_NONE;
	clShopData.m_siPersonID = shopperpersonid;

	if ( pclMsg->siResult < 1 )	
	{	
		// ���ŵ� ���������� ������ ���۹޴´�.
		if(pclCM->IsValidID(shoppercharid) == TRUE && pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
		{
			cltCharServer* pclcharshopper = ((cltCharServer*)pclCM->CR[shoppercharid]);

			if( pclMsg->siShowCaseIndex >= 0 && pclMsg->siShowCaseIndex < MAX_ITEM_PER_PERSON)
			{
				pclcharshopper->clShopData.m_clItem[pclMsg->siShowCaseIndex].siItemNum += pclMsg->siSellItemNum;
			}

			// ������ �������� �ʰ� �ִٸ� ������ �ݵ��� �Ѵ�.
			if(pclcharshopper->bPersonalShopSwitch == false)	
				pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
		
			clShopData.Set(&pclcharshopper->clShopData);
		}

		if(pclCM->IsValidID(sellercharid) == TRUE)
		{
			if(pclCM->CR[sellercharid]->pclCI->GetPersonID() == sellerpersonid)
			{
				// Client���� siSuccess ���������� �����Ѵ�.
				cltGameMsgResponse_SellPersonalShop clInfo(sellercharid, SELLPERSONALSHOP_FAIL_UNKNOWN, pclMsg->clSellerInvItem.siUnique,  pclMsg->siSellItemNum);
				cltMsg clMsg(GAMEMSG_RESPONSE_SELLPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
				pclCM->CR[sellercharid]->SendNetMsg((sPacketHeader*)&clMsg);

				//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				//{
				//	// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� �Ǹ� ����. 
				//	// param1 == ��������, param2 == ������ ����ũ.
				//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_SELL, 
				//						0, (cltCharServer*)(pclCM->CR[shoppercharid]), NULL, 0, 0, 0, NULL, pclMsg->siSellItemNum, 0, 0, 0, 0, 0,
				//						SELLPERSONALSHOP_FAIL_UNKNOWN, pclMsg->clShopperInvItem.siUnique,  0, 0, 0, NULL, NULL);
				//}

				
				// ���λ��� ���������� ������.
				{
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[sellercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				
			}
		}
	}
	else // ������ 
	{
		
		BOOL bShopSoldOut = TRUE;
		//===========================================================
		// ���������� ������ �����ϰ� ���ŵ� ������ �����ϵ��� �Ѵ�.
		//===========================================================
		if(pclCM->IsValidID(shoppercharid) == TRUE && pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
		{
			// �ǸſϷῡ ����
			cltCharServer* pclcharshopper = ((cltCharServer*)pclCM->CR[shoppercharid]);
			
			// ������ �������� �ʰ� �ִٸ� ������ �ݵ��� �Ѵ�.
			if(pclcharshopper->bPersonalShopSwitch == false)	
				pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
	
			
			for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
			{
				if(pclcharshopper->clShopData.m_clItem[i].siItemNum > 0 )
				{
					bShopSoldOut = FALSE;
					break;
				}
			}
			if(bShopSoldOut == TRUE)	pclcharshopper->clShopData.m_siShopMode = PSHOP_MODE_NONE;
			clShopData.Set(&pclcharshopper->clShopData);
			
			// ���� ������ ��������� Update �Ѵ�.
			pclcharshopper->SetPersonalShopBanner(&pclcharshopper->clShopData);

			//���ΰŷ� ����Ʈ�� ���������� Ȯ���Ѵ�. 
			pclcharshopper->DoQuestCheckAndAction(QUEST_CLEAR_COND_BUYTOPBSTORE);
		}
		

		// �Ǹ���  
		if(pclCM->IsValidID(sellercharid) == TRUE)
		{
			if(pclCM->CR[sellercharid]->pclCI->GetPersonID() == sellerpersonid)
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( sellerinvpos >= 0 && sellerinvpos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[sellercharid]->pclCI->clCharItem.clItem[sellerinvpos].Set(&pclMsg->clSellerInvItem);

					cltGameMsgResponse_PersonItemInfo clinfo(sellerinvpos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clSellerInvItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[sellercharid]->SendNetMsg((sPacketHeader*)&clMsg);

				}
				// ���� �ڱ��� ������Ʈ �Ѵ�. 
				pclCM->CR[sellercharid]->pclCI->clIP.SetMoney(pclMsg->siSellerMoney);
				pclCM->CR[sellercharid]->SetUpdateSwitch(UPDATE_IP, true, 0);

				// Client���� ���������� �����ش�.			
				{
					cltGameMsgResponse_SellPersonalShop clInfo(sellercharid, SELLPERSONALSHOP_SUCCESS_SELL, pclMsg->clShopperInvItem.siUnique,  pclMsg->siSellItemNum);
					cltMsg clMsg(GAMEMSG_RESPONSE_SELLPERSONALSHOP, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[sellercharid]->SendNetMsg((sPacketHeader*)&clMsg);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� �Ǹ� ����. 
						// param1 == seller�� ������ ��ġ, param2 == seller�� ������ ����ũ.
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_SELL, 
											0, (cltCharServer*)(pclCM->CR[sellercharid]), NULL, shopperpersonid, itemcoast, pclMsg->siSellerMoney, &pclMsg->clSellerInvItem_Log, pclMsg->siSellItemNum, 0, 0, 0, 0, 0,
											sellerinvpos, pclMsg->clSellerInvItem_Log.siUnique,  0, 0, 0, NULL, NULL);
					}

				}

				// ���λ��� ���������� ������.
				{
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData,itemunique, itemnum,itemcoast,FALSE);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[sellercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}

			}
		}
		//===========================================================
		// �������� 
		//===========================================================
		if(pclCM->IsValidID(shoppercharid) == TRUE)
		{
			if(pclCM->CR[shoppercharid]->pclCI->GetPersonID() == shopperpersonid)
			{
				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( shopperinvpos >= 0 && shopperinvpos < MAX_ITEM_PER_PERSON )
				{
					pclCM->CR[shoppercharid]->pclCI->clCharItem.clItem[shopperinvpos].Set(&pclMsg->clShopperInvItem);

					cltGameMsgResponse_PersonItemInfo clinfo(shopperinvpos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clShopperInvItem, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[shoppercharid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				
				// ���� �ڱ��� ������Ʈ �Ѵ�. 
				pclCM->CR[shoppercharid]->pclCI->clIP.SetMoney(pclMsg->siShopperMoney);
				pclCM->CR[shoppercharid]->SetUpdateSwitch(UPDATE_IP, true, 0);
				
				// ������ ���� �ȸ��� Stop��Ű���� �Ѵ�.
				/*
				if(bShopSoldOut == TRUE)
				{
					// ĳ������ ���λ����� �����Ѵ�. 
					((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopBanner(NULL);
					((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopData(false, NULL);
					
					// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
					cltGameMsgResponse_StopPersonalShop clinfo(pclCM->CR[shoppercharid]->GetCharUnique(), pclCM->CR[shoppercharid]->pclCI->GetPersonID(), 2);
					cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
					((cltCharServer*)pclCM->CR[shoppercharid])->SendNeighbourMsg(&clMsg, true);
				}
				else*/
				{
					// ���λ��� ���������� ������.
					cltGameMsgResponse_UpdatePersonalShopData clinfo(shoppercharid, &clShopData,itemunique ,itemnum, itemcoast,TRUE);
					cltMsg clMsg(GAMEMSG_RESPONSE_UPDATEPERSONALSHOPDATA, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[shoppercharid]->SendNetMsg((sPacketHeader*)&clMsg);

					if(bShopSoldOut == TRUE)
					{
						// ĳ������ ���λ����� �����Ѵ�. 
						((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopBanner(NULL);
						((cltCharServer* )pclCM->CR[shoppercharid])->SetPersonalShopData(false, NULL);

						// �̿��鿡�� ���ᰡ �Ǿ����� �˷��ش�.
						cltGameMsgResponse_StopPersonalShop clinfo(pclCM->CR[shoppercharid]->GetCharUnique(), pclCM->CR[shoppercharid]->pclCI->GetPersonID(), 2);
						cltMsg clMsg(GAMEMSG_RESPONSE_STOPPERSONALSHOP, sizeof(clinfo), (BYTE*)&clinfo);
						((cltCharServer*)pclCM->CR[shoppercharid])->SendNeighbourMsg(&clMsg, true);

						if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
						{
							// [�α��߰� : Ȳ���� 2007. 10. 9] // ���λ��� ���� ����.
							// param1 == ���.
							SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRIVATETRADE, LOGCOMMAND_INDEX_PRIVATETRADE_END, 
												0, (cltCharServer*)(pclCM->CR[shoppercharid]), NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
												2, 0, 0, 0, 0, NULL, NULL);
						}
					}	
				}
			}
		}	
	}
}