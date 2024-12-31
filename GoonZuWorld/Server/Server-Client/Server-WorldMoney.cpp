//----------------------------
// SJY 2005/12/06
//----------------------------
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"

#include "MsgRval-Define.h"

#include "../CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"
#include "../CommonLogic/Msg/MsgType-WorldMoney.h"
#include "../CommonLogic/WorldTraderMgr/WorldTraderManager.h"
#include "../CommonLogic/WorldPassport/WorldPassport.h"

#include "..\Server\Minister\MinisterBase.h"
#include "..\Server\Minister\Minister-Izo.h"
#include "..\Server\Minister\MinisterMgr.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_DISTRIBUTION_WORLDMONEY( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Distrubution_WorldMoney* pclinfo = (cltGameMsgRequest_Distrubution_WorldMoney*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI64 totalmoney = pclinfo->siWorldMoney * pclinfo->siWorldMoneyPrice ;
	if ( pclDistributionWorldMoney->IsCorrectDistribution(pclinfo->siWorldMoney,pclinfo->siWorldMoneyPrice) == FALSE ||
		pclchar->pclCI->clIP.GetMoney() < totalmoney || pclchar->pclCI->clIP.GetLevel() < FATHER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_DIS_WORLDMONEY,  0, 0, id);
		return ;
	}

	sDBRequest_Distribution_WorldMoney clMsg((UI16)pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),totalmoney,pclinfo->siWorldMoney,INPUTREASON_WORLDMONEY_DISTRIBUTION);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return ;
}


void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDMONEY_TRADELIST(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if( id <= 0 )
		//&& pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	for ( SI32 i = 0 ; i < ( MAX_WORLDMONEY_TRADELIST_NUM / MAX_WORLDMONEY_TRADELIST_PER_SEND ) ; i ++ )
	{
#ifdef _SAFE_MEMORY
		NSafeTArray<cltWorldMoneyTradeList, MAX_WORLDMONEY_TRADELIST_PER_SEND>	clList;
#else
		cltWorldMoneyTradeList clList[MAX_WORLDMONEY_TRADELIST_PER_SEND];
#endif

		for ( SI32 j = 0 ; j < MAX_WORLDMONEY_TRADELIST_PER_SEND ; j ++ )
		{
			if( (i*MAX_WORLDMONEY_TRADELIST_PER_SEND+j) >= 0 && (i*MAX_WORLDMONEY_TRADELIST_PER_SEND+j) < MAX_WORLDMONEY_TRADELIST_NUM )
				clList[j].Set(&pclDistributionWorldMoney->clTradeList[i*MAX_WORLDMONEY_TRADELIST_PER_SEND+j]);
		}

		bool bEnd = false ;
		if ( i == ( MAX_WORLDMONEY_TRADELIST_NUM / MAX_WORLDMONEY_TRADELIST_PER_SEND ) - 1 )
			bEnd = true ;

		//cltGameMsgResponse_WorldMoney_TradeList clinfo(clList,i,bEnd);
#ifdef _SAFE_MEMORY
		cltGameMsgResponse_WorldMoney_TradeList clinfo(&clList[0],i,bEnd,pclDistributionWorldMoney->siAverageWorldMoneyPrice);
#else
		cltGameMsgResponse_WorldMoney_TradeList clinfo(clList,i,bEnd,pclDistributionWorldMoney->siAverageWorldMoneyPrice);
#endif

		cltMsg clMsg(GAMEMSG_RESPONSE_WORLDMONEY_TRADELIST, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDMONEY_SELLORDER(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	cltGameMsgRequest_WorldMoney_SellOrder* pclinfo = (cltGameMsgRequest_WorldMoney_SellOrder*)pclMsg->cData;

	// �̹� �ø� ��ť�� �ִ�
	if ( pclchar->pclCI->clWorldMoney.siTradeWorldMoney != 0 &&
		pclchar->pclCI->clWorldMoney.siTradeWorldMoneyPrice != 0 )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_SELLORDER,  0, 0, id);
		return ;
	}

	// �ø����� �� ��ť���� ���� ������ �ִ�.
	if ( pclinfo->siWorldMoney > pclchar->pclCI->clWorldMoney.siWorldMoney )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_SELLORDER,  0, 0, id);
		return ;
	}

	// �����ᰡ �ֳ�?
	SI64 fee = pclinfo->siWorldMoney * pclinfo->siPrice / 100 ; // ������ 1%
	if ( pclchar->pclCI->clIP.GetMoney() < fee )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_SELLORDER,  0, 0, id);
		return ;
	}

	if ( pclinfo->siPrice <= 0 || pclinfo->siWorldMoney <= 0 )
		return ;

	SI32 gamedate = pclTime->clDate.GetDateVary();

	sDBRequest_WorldMoney_SellOrder clMsg((UI16)pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),pclinfo->siPrice,pclinfo->siWorldMoney,fee,gamedate);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_TAX, fee);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDMONEY_BUYORDER(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	cltGameMsgRequest_WorldMoney_BuyOrder* pclinfo = (cltGameMsgRequest_WorldMoney_BuyOrder*)pclMsg->cData;

	if ( pclinfo->siIndex < 0 || pclinfo->siIndex >= MAX_WORLDMONEY_TRADELIST_NUM )
		return ;

	// ������ �ִ� �ֹ��̳�?
	if ( pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPersonID <= 0 ||
		pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siWorldMoney <= 0 ||
		pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPrice <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_BUYORDER,  0, 0, id);
		return ;
	}

	if ( pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPersonID == pclchar->pclCI->GetPersonID())
	{
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_BUYORDER_MYSELF, 0, 0, id);
		return;
	}

	SI64 realBuyWorldMoney = pclinfo->siWorldMoney ;
	if ( pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siWorldMoney < pclinfo->siWorldMoney )
		realBuyWorldMoney = pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siWorldMoney ;

	// ���� �ֳ�?
	SI64 totalMoney = realBuyWorldMoney * pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPrice ;
	if ( pclchar->pclCI->clIP.GetMoney() < totalMoney )
	{
		//SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_BUYORDER,  0, 0, id);
		SendServerResponseMsg(0, SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY,  0, 0, id);

		return ;
	}

	// 100�� ��ť�� �Ѿ �ȵȴ�.
	if ( pclchar->pclCI->clWorldMoney.GetWorldMoney() + realBuyWorldMoney > 10000000000 )
		return ;

	sDBRequest_WorldMoney_BuyOrder clMsg((UI16)pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),pclinfo->siIndex,
		realBuyWorldMoney,pclDistributionWorldMoney->clTradeList[pclinfo->siIndex].siPrice);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDMONEY_CANCELORDER(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	// ���� �ø� �ֹ��� �ֳ�?
	if ( pclchar->pclCI->clWorldMoney.siTradeWorldMoney <= 0 ||
		pclchar->pclCI->clWorldMoney.siTradeWorldMoneyPrice <= 0 )
		return ;

	sDBRequest_WorldMoney_CancelOrder clMsg((UI16)pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID());
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// TradeServer
// �ȱ� �ֹ� ���
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_SET_SELLORDER(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_TradeServer_Set_SellOrder* pclinfo = (cltGameMsgRequest_TradeServer_Set_SellOrder*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if ( bTradeServer == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_GM,0,0,pclchar->GetCharUnique());
		return ;
	}

	// ���� ���� �ŷ����̸� �ȵȴ�!
	if ( pclchar->bTradeServerUsing == true )
	{
		return ;
	}

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->siPos	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}

		// �ͼ����� ���λ���
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->siPos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}


	// �ٸ������� Ư��ǰ�ϰ�� ���ȼ� ����
	if ( pclClient->siServiceArea == ConstServiceArea_English )
	{
		if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_KOREA) ||
			pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_JAPAN) )
		{
			if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_GLOBAL) == false )
			{
				return;
			}
		}
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_KOREA) ||
			pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_GLOBAL) )
		{
			if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_JAPAN) == false )
			{
				return;
			}
		}
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_NHNChina )
	{
		if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_KOREA) ||
			pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_JAPAN) )
		{
			if ( pclItemManager->IsItemInfoAtb( pclinfo->clitem.siUnique, ITEMINFOATB_SPECIAL_GLOBAL) == false )
			{
				return;
			}
		}
	}

	// �ð�����
	if ( sTime.wHour < siTradeServerStartTime || sTime.wHour > siTradeServerEndTime )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_LIMITTIME,siTradeServerStartTime,siTradeServerEndTime,pclchar->GetCharUnique());
		return ;
	}

	// Ʈ���̵� ������ ����Ǿ� �ֳ�?
	if ( pclNTradeServerProcess == NULL || pclNTradeServerProcess->GetTradeServerServersSession()->GetState() != SESSION_STATE_ESTABLISHED )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_SESSION,0,0,pclchar->GetCharUnique());
		return ;
	}

	cltTradeServerOrder clOrder;
	clOrder.Init();
	clOrder.clitem.siUnique = pclinfo->clitem.siUnique;
	clOrder.clitem.siItemNum = pclinfo->clitem.siItemNum;
	clOrder.clitem.siPrice = pclinfo->siPrice ;
	clOrder.clitem.siType = pclinfo->clitem.Element.siType;
	clOrder.clitem.siPower = pclinfo->clitem.Element.siPower;
	clOrder.clitem.siRareType = pclinfo->clitem.clItemCommon.clCommonInfo.uiRareInfo ;
	memcpy(clOrder.clitem.szItemData,pclinfo->clitem.cData8,MAX_ITEM_UNION_BYTE);

	clOrder.siIndex = 0 ;
	clOrder.siPersonID = pclchar->pclCI->GetPersonID();
	MStrCpy(clOrder.szAccountID,pclchar->pclCI->clBI.szAccountID,MAX_PLAYER_NAME);
	//MStrCpy(clOrder.szServerName,szServerName,20);
	MStrCpy(clOrder.szCharName,pclchar->GetName(),20);

	clOrder.siCharNation = GetTradeServer_CharNation( pclClient->pclCM->GetCharServer(id) );//pclClient->pclCM->CR[id]->pclCI->clBI.siCountryID;
	if( clOrder.siCharNation == -1 )		return;

	NTCHARString<4> kServerNation;
	kServerNation = GetTradeServer_ServerNation( pclClient->siServiceArea );
	if( kServerNation.Length() <= 0 )		return;

	MStrCpy(clOrder.szServerNation, kServerNation, 4);

	/*
#ifdef _DEBUG
	MStrCpy(clOrder.szServerNation,"tst",4);
#else
	if (pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		clOrder.siCharNation = 1;
		MStrCpy(clOrder.szServerNation,"jpn",4);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		if( clOrder.siCharNation == -1  ) clOrder.siCharNation = 2;
		MStrCpy(clOrder.szServerNation,"eng",4);
	}
#endif
	*/

	clOrder.siServerIndex = siServerUnique ;


	// �ŷ������� �������̳�? ���ڴ� �³�?
	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clitem.siUnique);
	if ( ref <= 0 || ref >= MAX_ITEMINFO_NUMBER ) return ;
	if ( pclItemManager->pclItemInfo[ref]->siTradeServerMinNum <= 0 ) return ;
	if ( pclItemManager->pclItemInfo[ref]->siTradeServerMinNum > pclinfo->clitem.siItemNum ) return ;

	// ������� ������ ��ť�� ������ �ֳ�?
	SI64 fee = clOrder.clitem.siPrice / 100 ;
	if ( pclchar->pclCI->clWorldMoney.siWorldMoney < fee )
		return;

	if ( pclinfo->siPos < PERSONITEM_INV0 || pclinfo->siPos >= MAX_ITEM_PER_PERSON )
		return ;

	// �̹� �̵����� ���� �ȵȴ�!
	if ( pclchar->GetNoMoveItemSwitch(pclinfo->siPos) != 0 )
		return ;

	if ( pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].siUnique != pclinfo->clitem.siUnique )
		return ;

	// ������ ������ �ֳ�?
	if ( pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].siItemNum < pclinfo->clitem.siItemNum )
		return ;

	clOrder.clitem.siRank = 0 ;
	SI32 itemtype = pclItemManager->pclItemInfo[ref]->siType ;
	if( itemtype < 0 || itemtype >= MAX_ITEMTYPE_NUMBER )	return;

	// OBJECT �����̸�
	if ( pclItemManager->pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_OBJECT) )
	{
		if ( clOrder.clitem.siItemNum != 1 )
			return ;
		// ������ ���� �����ΰ�?
		if ( pclchar->pclCI->clCharItem.clItem[pclinfo->siPos].IsSame(&pclinfo->clitem,true) )
		{
			clOrder.clitem.siRank = pclItemManager->GetTradeServerObjectRank(&pclinfo->clitem);

			if ( clOrder.clitem.siRank < 0 || clOrder.clitem.siRank >= MAX_TRADESERVER_OBJECT_RANK )
				return ;
		}
		else return ;
	}

	// Ʈ���̵����� ���̴� ������ �̵��� �����!
	pclchar->SetNoMoveItemSwitch(pclinfo->siPos,true);

	// Ʈ���̵� ������ �ȱ� �ֹ� ��û����.

	if ( true == IsCountrySwitch( Switch_Trade_Renewal ) )
	{
		// ������ ������ �Ǹ� ��û�� ���Ѵ�
		if ( false == pclchar->pclCI->clWorldPassport.IsHavePassport() )
		{
			return;
		}
		
		// ������ �ȾƵ� ��ť�� ���������� ����ǵ��� �Ѵ�
		NTradeServerRequest_Set_SellOrder_HoldAcu clMsg( pclchar->GetCharUnique(), pclinfo->siPos, &clOrder, true );
		pclNTradeServerProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		NTradeServerRequest_Set_SellOrder clMsg(pclchar->GetCharUnique(),pclinfo->siPos,&clOrder);
		pclNTradeServerProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	
	// ���� ���� ������ ��Ŷ ���´ٰ� �˷��ش�.
	pclchar->bTradeServerUsing = true ;
}

// �ֹ� ���
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_CANCEL_SELLORDER(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if ( bTradeServer == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_GM,0,0,pclchar->GetCharUnique());
		return ;
	}

	// ���� ���� �ŷ����̸� �ȵȴ�!
	if ( pclchar->bTradeServerUsing == true )
	{
		return ;
	}

	// �ð�����
	if ( sTime.wHour < siTradeServerStartTime || sTime.wHour > siTradeServerEndTime )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_LIMITTIME,siTradeServerStartTime,siTradeServerEndTime,pclchar->GetCharUnique());
		return ;
	}

	// Ʈ���̵� ������ ����Ǿ� �ֳ�?
	if ( pclNTradeServerProcess == NULL || pclNTradeServerProcess->GetTradeServerServersSession()->GetState() != SESSION_STATE_ESTABLISHED )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_SESSION,0,0,pclchar->GetCharUnique());
		return ;
	}

	cltGameMsgRequest_TradeServer_Cancel_SellOrder* pclinfo = (cltGameMsgRequest_TradeServer_Cancel_SellOrder*)pclMsg->cData ;

	if ( pclinfo->siIndex < 0 || pclinfo->siIndex >= MAX_TRADESERVER_ORDER_LIST )
	{
		pclLog->FilePrint("TRADESERVER_CANCEL_SELLORDER_ERROR.txt", "pclinfo->siIndex Error");
		return ;
	}

	if ( pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siUnique != pclinfo->siItemUnique )
	{
		pclLog->FilePrint("TRADESERVER_CANCEL_SELLORDER_ERROR.txt", "%d %d %d clitem.siUnique Error", pclinfo->siIndex,
			pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siUnique,pclinfo->siItemUnique );

		return ;
	}
	if ( pclWorldTraderManager->clOrder[pclinfo->siIndex].siPersonID != pclchar->pclCI->GetPersonID() )
	{
		pclLog->FilePrint("TRADESERVER_CANCEL_SELLORDER_ERROR.txt", "%d %d siPersonID Error", pclWorldTraderManager->clOrder[pclinfo->siIndex].siPersonID,
			pclchar->pclCI->GetPersonID() );
		return ;
	}

	cltItem clitem;
	clitem.Init();

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->siItemUnique);
	if ( ref )
	{
		SI32 itemtype = pclItemManager->pclItemInfo[ref]->siType ;
		// ������Ʈ �����̳�?
		if ( pclItemManager->pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_OBJECT) )
		{
			if ( pclItemManager->MakeTradeServerObjectForRank(&clitem,pclinfo->siItemUnique,pclinfo->siItemNum,
				pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siRank,
				pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siRareType,
				pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siType,
				pclWorldTraderManager->clOrder[pclinfo->siIndex].clitem.siPower) == FALSE )
				return ;
		}
		else
		{
			clitem.siUnique = pclinfo->siItemUnique ;
			clitem.siItemNum = pclinfo->siItemNum ;
		}
	}
	else return ;

	cltItem cltoitem;
	cltoitem.Init();
	SI16 pos = 0 ;
	SI32 returnvalue = 0 ;

	if ( pclchar->CanAddInv(INVMODE_ALL,&clitem,&pos,&cltoitem,&returnvalue) == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_BUY_FULLINV,0,0,pclchar->GetCharUnique());
		return ;
	}

	//NTradeServerRequest_Cancel_SellOrder clMsg(pclchar->GetCharUnique(),&pclWorldTraderManager->clOrder[pclinfo->siIndex]);

	// �� �ڸ��� �����Ѵ�.
	pclchar->SetInputItemReserve(pos,CurrentClock);

	NTradeServerRequest_Cancel_SellOrder clMsg(pclchar->GetCharUnique(),&pclWorldTraderManager->clOrder[pclinfo->siIndex],pos);
	pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);

	// ���� ���� ������ ��Ŷ ���´ٰ� �˷��ش�.
	pclchar->bTradeServerUsing = true ;
}

// ��� �ֹ�
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_SET_BUYORDER(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// ����� ���������� ������ �� �־�� �Ѵ�
	if ( true == IsCountrySwitch(Switch_Trade_Renewal) )
	{
		if ( false == pclchar->pclCI->clWorldPassport.IsHavePassport() )
		{
			return;
		}
	}

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if ( bTradeServer == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_GM,0,0,pclchar->GetCharUnique());
		return ;
	}

	// �ð�����
	if ( sTime.wHour < siTradeServerStartTime || sTime.wHour > siTradeServerEndTime )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_LIMITTIME,siTradeServerStartTime,siTradeServerEndTime,pclchar->GetCharUnique());
		return ;
	}

	// ���� ���� �ŷ����̸� �ȵȴ�!
	if ( pclchar->bTradeServerUsing == true )
	{
		return ;
	}

	// Ʈ���̵� ������ ����Ǿ� �ֳ�?
	if ( pclNTradeServerProcess == NULL || pclNTradeServerProcess->GetTradeServerServersSession()->GetState() != SESSION_STATE_ESTABLISHED )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_SESSION,0,0,pclchar->GetCharUnique());
		return ;
	}

	cltGameMsgRequest_TradeServer_Set_BuyOrder* pclinfo = (cltGameMsgRequest_TradeServer_Set_BuyOrder*)pclMsg->cData ;
	if( pclinfo->clOrder.siIndex < 0 || pclinfo->clOrder.siIndex >= MAX_TRADESERVER_ORDER_LIST )	return;

	if ( pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex].IsSame(&pclinfo->clOrder) == false )
		return ;

	SI64 price = pclinfo->clOrder.clitem.siPrice ;
	if ( pclchar->pclCI->clWorldMoney.siWorldMoney < price )
		return ;

	cltItem clitem;
	clitem.Init();

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->clOrder.clitem.siUnique);
	if ( ref )
	{
		SI32 itemtype = pclItemManager->pclItemInfo[ref]->siType ;
		if( itemtype < 0 || itemtype >= MAX_ITEMTYPE_NUMBER )		return;

		// ������Ʈ �����̳�?
		if ( pclItemManager->pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_OBJECT) )
		{
			if ( pclItemManager->MakeTradeServerObjectForRank(&clitem,pclinfo->clOrder.clitem.siUnique,
				pclinfo->clOrder.clitem.siItemNum,pclinfo->clOrder.clitem.siRank,
				pclinfo->clOrder.clitem.siRareType,pclinfo->clOrder.clitem.siType,
				pclinfo->clOrder.clitem.siPower) == FALSE )
				return ;
		}
		else
		{
			clitem.siUnique = pclinfo->clOrder.clitem.siUnique ;
			clitem.siItemNum = pclinfo->clOrder.clitem.siItemNum ;
		}
	}
	else
	{
		return ;
	}

	//--------------------------------------------------------------------------------------
	// ���� �˻�
	//--------------------------------------------------------------------------------------
	bool bIsFeeCheck = false;

	// ������ �ΰ��Ѵ�.
	CMinisterIzo *pclminister = (CMinisterIzo *)pclMinisterMgr->GetMinister(MINISTER_IZO);
	if ( (pclminister) && (pclminister->GetIsWorldTradeTax()) )
	{
		bIsFeeCheck = true;
	}

	// �ٸ� ���� Ư��ǰ�� ��� ������ �ΰ����� �ʴ´�
	if ( pclClient->siServiceArea == ConstServiceArea_English )
	{
		if ( pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_KOREA) ||
			pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_JAPAN) )
		{
			if(pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_GLOBAL) == false )
			{
				bIsFeeCheck = false;
			}
		}
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		if ( pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_KOREA) ||
			pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_GLOBAL) )
		{
			if(pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SPECIAL_JAPAN) == false )
			{		
				bIsFeeCheck = false;
			}
		}
	}

	if ( true == bIsFeeCheck )
	{
		SI64 siPrice				= pclinfo->clOrder.clitem.siPrice;
		SI16 siItemNum				= pclinfo->clOrder.clitem.siItemNum;
		SI64 siAverageWorldMoney	= pclDistributionWorldMoney->siAverageWorldMoneyPrice;

		// �ֹ��� �÷��� �������� �Ѱ��� ����
		GMONEY siOrderPrice = 0;
		if ( 0 < siItemNum )
		{
			siOrderPrice = ( siPrice * siAverageWorldMoney ) / siItemNum ;
		}

		// �������� �ü�
		cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(pclinfo->clOrder.clitem.siUnique);
		if ( pclprice == NULL )
		{
			return ;
		}

		SI64 itemprice	= pclprice->siPrice ;

		SI32 siRatio	= 0;

		if ( 0 != itemprice )
		{
			siRatio = (SI32)(siOrderPrice * 100 / itemprice);
		}
		else

		{
			return;
		}

		// ���� ����� ������ ���Ѵ�.
		SI32 siTotalSpecialTaxRate = 0;

		if ( (pclminister) && (siRatio < pclminister->GetSpecialTaxRange()) )
		{
			siTotalSpecialTaxRate = pclminister->GetSpecialTaxRate() + ( pclminister->GetSpecialTaxRange() - siRatio );
		}
		else
		{
			siTotalSpecialTaxRate = 1;
		}

		GMONEY siTax = ( siPrice * siAverageWorldMoney ) * siTotalSpecialTaxRate / 100;
		if ( (0 < siTax) && (pclchar->pclCI->clIP.GetMoney() < siTax ) )
		{
			return;
		}

	}


	cltItem cltoitem;
	cltoitem.Init();
	SI16 pos = 0 ;
	SI32 returnvalue = 0 ;

	if ( pclchar->CanAddInv(INVMODE_ALL,&clitem,&pos,&cltoitem,&returnvalue) == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_BUY_FULLINV,0,0,pclchar->GetCharUnique());
		return ;
	}

	SI16 serverindex = siServerUnique;

	// �� �ڸ��� �����Ѵ�.
	pclchar->SetInputItemReserve(pos,CurrentClock);

	NTCHARString<4>	kServerNation;
	kServerNation = GetTradeServer_ServerNation( pclClient->siServiceArea );

	NTradeServerRequest_Set_BuyOrder clMsg( pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),
		(char*)pclchar->GetName(),pclchar->pclCI->clBI.szAccountID,
		kServerNation ,serverindex,0,
		&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex],pos);
	pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);

/*
#ifdef _DEBUG
	NTradeServerRequest_Set_BuyOrder clMsg( pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),
		(char*)pclchar->GetName(),pclchar->pclCI->clBI.szAccountID,
		"tst",serverindex,0,
		&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex],pos);
	pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);
#else
	if (pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		NTradeServerRequest_Set_BuyOrder clMsg( pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),
			(char*)pclchar->GetName(),pclchar->pclCI->clBI.szAccountID,
			"jpn",serverindex,0,
			//&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex]);
			&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex],pos);

		pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		NTradeServerRequest_Set_BuyOrder clMsg( pclchar->GetCharUnique(),pclchar->pclCI->GetPersonID(),
			(char*)pclchar->GetName(),pclchar->pclCI->clBI.szAccountID,
			"eng",serverindex,0,
			//&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex]);
			&pclWorldTraderManager->clOrder[pclinfo->clOrder.siIndex],pos);

		pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);
	}
#endif*/

	// ���� ���� ������ ��Ŷ ���´ٰ� �˷��ش�.
	pclchar->bTradeServerUsing = true ;
}

// ����Ʈ ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_LISTINFO(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if ( bTradeServer == false )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_GM,0,0,pclchar->GetCharUnique());
		return ;
	}

	// �ð�����
	if ( sTime.wHour < siTradeServerStartTime || sTime.wHour > siTradeServerEndTime )
	{
		SendServerResponseMsg(0,SRVAL_FAIL_TRADESERVER_LIMITTIME,siTradeServerStartTime,siTradeServerEndTime,pclchar->GetCharUnique());
		return ;
	}

	cltGameMsgRequest_TradeServer_Get_ListInfo* pclinfo = (cltGameMsgRequest_TradeServer_Get_ListInfo*)pclMsg->cData;

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclinfo->siIndex);
	if ( ref <= 0 || ref >= MAX_ITEMINFO_NUMBER )
		return ;
	if ( pclItemManager->pclItemInfo[ref]->siTradeServerMinNum <= 0 )
		return ;

	SI32 itemunique = pclinfo->siIndex ;

	SI32 index = 0 , listnum = 0 ;
	cltTradeServerOrder clorder[MAX_TRADESERVER_GET_LIST];
	for ( SI32 j = 0 ; j < MAX_TRADESERVER_GET_LIST ; j ++ )
		clorder[j].Init();

	SI64 averageworldmoneyprice = pclDistributionWorldMoney->siAverageWorldMoneyPrice ;
	cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(itemunique);
	if ( pclprice == NULL )
		return ;
	SI64 itemprice = pclprice->siPrice ;

	bool bIsItem = false ;

	for ( SI32 i = 0 ; i < MAX_TRADESERVER_ORDER_LIST ; i ++ )
	{
/*		bool bDiffNation = false;

		if (siServiceArea == ConstServiceArea_English)
		{
			if (_tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("eng")) != 0 && 
				pclWorldTraderManager->clOrder[i].szServerNation[0] != NULL	)
			{
				bDiffNation  = true;
			}
		}
		else if (siServiceArea == ConstServiceArea_Japan)
		{
			if (_tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("jpn")) != 0 &&
				pclWorldTraderManager->clOrder[i].szServerNation[0] != NULL	)
			{
				bDiffNation  = true;
			}
		}
		/*
		else if (siServiceArea == ConstServiceArea_NHNChina)
		{
			if (_tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("NHNChi")) != 0 && 
				pclWorldTraderManager->clOrder[i].szServerNation[0] != NULL	)
			{
				bDiffNation  = true;
			}
		}
		*/

		// ���� ������?
		bool bCanAdd = true;

		if( pclWorldTraderManager->clOrder[i].clitem.siUnique != itemunique )				bCanAdd = false;

#ifndef _DEBUG
		// ����� ������ �ƴϸ�, ���� �׽�Ʈ ������ ������ �ʴ´�.
		if( _tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("tst")) == 0 )	bCanAdd = false;
		if( _tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("tgl")) == 0 )	bCanAdd = false;
#endif

		// ���� �ؿܼ��񽺴� �ѱ� ���� �ݸ��� ���񽺿��� �ø� �������� ������ �ʴ´�.
		if( _tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("net")) == 0 )	bCanAdd = false;

		// ���� ���� ���� ������ ������ ������ �ʴ´�.
		NTCHARString<4> kNation;
		kNation = GetTradeServer_ServerNation( siServiceArea );

		if( _tcslen(pclWorldTraderManager->clOrder[i].szServerNation) <= 0 )				bCanAdd = false;
		if( _tcscmp(kNation, pclWorldTraderManager->clOrder[i].szServerNation) == 0 &&
			siServerUnique == pclWorldTraderManager->clOrder[i].siServerIndex)
		{
			bCanAdd = false;
		}

		if( bCanAdd )
		{
			if( index >= 0 && index < MAX_TRADESERVER_GET_LIST )
			{
				clorder[index].Set(&pclWorldTraderManager->clOrder[i]);
				index ++ ;
			}
			bIsItem = true ;
		}
/*		if ( (siServerUnique != pclWorldTraderManager->clOrder[i].siServerIndex && 
			pclWorldTraderManager->clOrder[i].clitem.siUnique == itemunique 
			&& bDiffNation == false) 
			|| ( bDiffNation &&  pclWorldTraderManager->clOrder[i].clitem.siUnique == itemunique    )
			)
		{

			//========================================================
			// �۷ι������϶��� �ݸ����� ��ǰ�� �Ⱥ��̵���
			//========================================================
			if ((siServiceArea == ConstServiceArea_English &&_tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("net")) != 0	) ||
				// �Ϻ������϶��� �ݸ����� ��ǰ�� �Ⱥ��̵���
				(siServiceArea == ConstServiceArea_Japan &&_tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("net")) != 0	) ||
				// NHNCHINA
				(siServiceArea == ConstServiceArea_NHNChina && _tcscmp(pclWorldTraderManager->clOrder[i].szServerNation, TEXT("net")) != 0	))
			{
				if( index >= 0 && index < MAX_TRADESERVER_GET_LIST )
				{
					clorder[index].Set(&pclWorldTraderManager->clOrder[i]);
					index ++ ;
				}
				bIsItem = true ;
			}
			//========================================================
		}*/

		CMinisterIzo* pclminister = (CMinisterIzo*)pclMinisterMgr->GetMinister(MINISTER_IZO);

		bool isworldtradetax = pclminister->GetIsWorldTradeTax();
		SI32 spcialtaxrange = pclminister->GetSpecialTaxRange();
		SI32 spcialtaxrate = pclminister->GetSpecialTaxRate();

		if ( i == MAX_TRADESERVER_ORDER_LIST - 1 )
		{
			cltGameMsgResponse_TradeServer_Get_ListInfo clinfo(clorder, listnum, true, itemprice,
				averageworldmoneyprice, bIsItem, isworldtradetax, spcialtaxrange, spcialtaxrate);
			cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_GET_LISTINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else if ( index == MAX_TRADESERVER_GET_LIST )
		{
			cltGameMsgResponse_TradeServer_Get_ListInfo clinfo(clorder, listnum, false, 0, 0, bIsItem,
                isworldtradetax, spcialtaxrange, spcialtaxrate);
			cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_GET_LISTINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			index = 0 ;
			listnum ++ ;
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_MYINFO(cltMsg*pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	for ( SI32 i = 0 ; i < MAX_TRADESERVER_ORDER_LIST ; i ++ )
	{
		// ���� ����ũ�� ��ġ�ϴ��� Ȯ���Ѵ�.
		if( pclWorldTraderManager->clOrder[i].siServerIndex != pclClient->siServerUnique ) 
			continue;

#ifdef _DEBUG
		// ������϶��� ������ üũ���� �ʴ´�
		if( _tcscmp( pclWorldTraderManager->clOrder[i].szServerNation , TEXT("tst") ) != 0)
		{
			continue;
		}
#else
		if(	pclClient->siServiceArea == ConstServiceArea_Japan )
		{
			if( _tcscmp( pclWorldTraderManager->clOrder[i].szServerNation , TEXT("jpn") ) != 0)
			{
				continue;
			}
		}
		else if( pclClient->siServiceArea == ConstServiceArea_English )
		{
			if( _tcscmp( pclWorldTraderManager->clOrder[i].szServerNation , TEXT("eng") ) != 0)
			{
				continue;
			}
		}
		/*(�̰� �o�� �Ѥ�;)
		else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )
		{
			if( _tcscmp( pclWorldTraderManager->clOrder[i].szServerNation , TEXT("NHNChi") ) != 0)
				continue;
		}
		*/
		else
		{
			// �Ϻ� , �۷ι��� ������ �����Ѵ�.
			continue;
		}
#endif

		if ( pclWorldTraderManager->clOrder[i].siPersonID == pclchar->pclCI->GetPersonID() )
		{
			cltGameMsgResponse_TradeServer_Get_MyInfo clinfo(&pclWorldTraderManager->clOrder[i]);
			cltMsg clMsg(GAMEMSG_RESPONSE_TRADESERVER_GET_MYINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			break;
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU(cltMsg*pclMsg,SI32 id)
{
	cltGameMsgRequest_TradeServer_Get_Withdraw_Acu* pclInfo = (cltGameMsgRequest_TradeServer_Get_Withdraw_Acu*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	// �������� ��ť�� ���ٸ�
	if ( 0 >= pclInfo->m_siWithdrawAcu )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( true == pclchar->CheckLastMsgClock(1000) )
	{
		return;
	}

	// �̹� ���� �̿����̶�� �ȵȴ�
	if ( true == pclchar->bTradeServerUsing )
	{
		return;
	}
	
	// Ʈ���̵� ������ ����Ǿ� �ֳ�?
	if ( (NULL == pclNTradeServerProcess) || (FALSE == pclNTradeServerProcess->IsEstablished()) )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_TRADESERVER_SESSION, 0, 0, pclchar->GetCharUnique() );
		return;
	}

	char szNationCode[4] = { '\0', };
	if ( false == GetNationCode(szNationCode, sizeof(szNationCode)) )
	{
		return;
	}
	SI32 siPersonID = pclchar->pclCI->GetPersonID();

	NTradeServerRequest_Withdraw_Acu clMsg( id, siPersonID, szNationCode, siServerUnique, pclInfo->m_siWithdrawAcu );
	pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);

	// �������� ������̶�� �س��´�
	pclchar->bTradeServerUsing = true;
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRADESERVER_GET_SAVEDACU_LIST(cltMsg*pclMsg,SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( true == pclchar->CheckLastMsgClock(1000) )
	{
		return;
	}

	// Ʈ���̵� ������ ����Ǿ� �ֳ�?
	if ( (NULL == pclNTradeServerProcess) || (FALSE == pclNTradeServerProcess->IsEstablished()) )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_TRADESERVER_SESSION, 0, 0, pclchar->GetCharUnique() );
		return;
	}

	char szNationCode[4] = { '\0', };
	if ( false == GetNationCode(szNationCode, sizeof(szNationCode)) )
	{
		return;
	}
		
	NTradeServerRequest_Get_SavedACU_List clMsg( pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), szNationCode, siServerUnique );
	pclNTradeServerProcess->SendMsg((sPacketHeader*)&clMsg);

}

// WorldPassport( ���� ���� )
void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDPASSPORT_SET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_WorldPassport_Set* pclInfo = (cltGameMsgRequest_WorldPassport_Set*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// �̹� ������ �ִµ� �߱޽�û�� �Ѵٸ�
	if ( true == pclchar->pclCI->clWorldPassport.IsHavePassport() )
	{
		return;
	}

	// �߱� ��� ��ť üũ
	if ( Const_Passport_Issue_Cost_Acu > pclchar->pclCI->clWorldMoney.GetWorldMoney() )
	{
		return;
	}

	// ��ȿ�� Passport Name���� üũ
	if ( false == pclchar->pclCI->clWorldPassport.IsCorrectPassportName(pclInfo->m_szPassportName) )
	{
		return;
	}

	// �μ��� ���� ������ 
	SI32 siPersonID	= pclchar->pclCI->GetPersonID();
	SI32 siCharID	= pclchar->GetCharID();

	// �߱����� ���� �ð�
	cltDate clIssueDate;
	clIssueDate.Set( &pclTime->clDate );

	// �������� ���� �ð��� 5���� ���Ѵ�
	cltDate clExpireDate;
	clExpireDate.Set( &clIssueDate );
	clExpireDate.uiYear += 5;


	sDBRequest_WorldPassport_Set clPassport_Set( 
		siPersonID,		
		siCharID, 
		pclInfo->m_szPassportName, 
		clIssueDate.GetDateVary(),
		clExpireDate.GetDateVary(),
		Const_Passport_Issue_Cost_Acu
	);
	pclGameDBProcess->SendMsg( (sPacketHeader*)&clPassport_Set );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_WORLDPASSPORT_EXTEND(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// ���ǵ� ���µ� ���� ��û�� �ߴٸ�
	if ( false == pclchar->pclCI->clWorldPassport.IsHavePassport() )
	{
		return;
	}

	// ���� ��� ��ť üũ
	if ( Const_Passport_Extend_Cost_Acu > pclchar->pclCI->clWorldMoney.GetWorldMoney() )
	{
		return;
	}

	// �μ��� ���� ������ 
	SI32 siPersonID	= pclchar->pclCI->GetPersonID();
	SI32 siCharID	= pclchar->GetCharID();

	// ������ ����
	cltDate clExpireDate;
	clExpireDate.MakeFullDateFromDateVary( pclchar->pclCI->clWorldPassport.GetExpireDateVary() );

	// ���� ����ð��� ���� �ð����� �����ð��̸� �⺻�������� ����ð����� �Ѵ�
	if ( pclTime->clDate.GetDateVary() > clExpireDate.GetDateVary() )
	{
		clExpireDate.Set( &pclTime->clDate );
	}
	// ���� �Ⱓ�� 5���̴�
	clExpireDate.uiYear += 5;


	sDBRequest_WorldPassport_Extend clPassport_Extend( siPersonID, siCharID, clExpireDate.GetDateVary(), Const_Passport_Extend_Cost_Acu );
	pclGameDBProcess->SendMsg( (sPacketHeader*)&clPassport_Extend );

}

