//---------------------------------
// 2003/6/21 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Market.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"

#include "MsgRval-Define.h"
#include "MsgType-System.h"
#include "MsgType-Person.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_SETMARKETFEE(cltMsg* pclMsg, SI32 id)
{

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;
	
	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = (cltFee*)pclMsg->cData;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;
	
	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_MARKET, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAILSETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	//-----------------------------------
	// DB�� ���� ������ ������. 
	//-----------------------------------
	// DB �� ������.

	sDBRequest_SetMarketFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}


void cltServer::DoMsg_GAMEMSG_REQUEST_SELLITEM(cltMsg* pclMsg, SI32 id)
{
	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;
	

	cltTradeOrder* pclOrder = (cltTradeOrder*)pclMsg->cData;
	
	// Person�� ��ġ�� dy������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	// ���ο� ������ �ý��ۿ��� �к��� üũ���� �ʴ´�.
	bool bIsBelonging = false;
	if( IsCountrySwitch( Switch_NewDurability) )
	{
		SI32 siForeverDurability	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
		SI32 siForeverDurability2	= (SI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability2") );
		SI32 siGetMaxDurability		= pclOrder->clItemData.clItemCommon.clCommonInfo.uiMaxDurability;
		
		// ���� ������ ��ǰ�� �ƴϸ� ������ �ͼӵ��� ����
		if ( (siForeverDurability != siGetMaxDurability) && (siForeverDurability2 != siGetMaxDurability) )
		{
			bIsBelonging = false;
		}
		else
		{
			bIsBelonging = (pclOrder->clItemData.uiDateDay > 0 && pclOrder->clItemData.uiDateMonth > 0 && pclOrder->clItemData.uiDateDay > 0);
		}
	}
	else
	{
		bIsBelonging = (pclOrder->clItemData.uiDateDay > 0 && pclOrder->clItemData.uiDateMonth > 0 && pclOrder->clItemData.uiDateDay > 0);
	}

	//---------------------------------------------
	// �ŷ� ���� ǰ������ Ȯ���Ѵ�. 
	//---------------------------------------------
	if( pclItemManager->IsItemInfoAtb(pclOrder->clItemData.siUnique, ITEMINFOATB_NOTTRADE) || 
		//===============================================================
		//cyj �ͼӾ������̸� ���Ͽ� �� �ø�����
		//===============================================================
		bIsBelonging ||
		 //===============================================================
		pclOrder->clItemData.siUnique == 8150 || pclOrder->clItemData.siUnique == 14300 ||
		pclOrder->clItemData.siUnique == 14400 || pclOrder->clItemData.siUnique == 14500 )
	{
		SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------------------
	// ��ƼȦ���� ���� �������� �ŷ� �� �� ����.
	//---------------------------------------------
	if( pclOrder->clItemData.clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
		return;
	
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	
	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	if(pclClient->IsCountrySwitch(Switch_FourLeaf))
	{
		//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
		if( ITEMUNIQUE(2755) == pclOrder->clItemData.siUnique || ITEMUNIQUE(2754) == pclOrder->clItemData.siUnique )	
		{	
			if( pclOrder->clItemData.siUnique != siFourLeafUnique )	
			{
				SendServerResponseMsg( 0, SRVAL_RETURN_NOT_USE_FOURLEAF, 0, 0, pclchar->GetID() );
				return;	
			}
		}
	}

	// ������ ���� ���������� Ȯ���Ѵ�. 
	if(pclOrder->siPrice <= 0 || pclOrder->siPrice > MAX_PRICE_IN_MARKET)
		return ;

	// ������ �� ���� �ִ��� Ȯ���Ѵ�. 
	cltStrInfo* pclinfo = GetStrInfo( villageunique, RANKTYPE_MARKET );
	if(pclinfo == NULL)return ;

	SI64 totalmoney = (SI64)pclOrder->siPrice * (SI64)pclOrder->siAmount;
	// ���� �ŷ� ���ѱ�
	if( totalmoney > pclClient->GetGlobalValue("GV_MarketMoneyLimit")+1) return ;
	
	SI64 tax = pclinfo->clMarketStrInfo.clFee.CalcFee(totalmoney);

	//SI64 tax = ( (SI64)pclOrder->siPrice * (SI64)pclOrder->siAmount ) / 100;
	// ���� �����̾��� ���� tax�� 0 �Ⱦ��� �������̶� ����üũ
	if( false == pclClient->pclCM->CR[id]->pclCI->clBI.bMarKetPremiumService )
	{
		if(tax > MIN_FEE)
		{
			if(pclCM->CR[id]->pclCI->clIP.GetMoney() < tax)return ;
		}
		else
		{
			tax = 0;
		}
	}
	else
		tax = 0;

	// PersonID�� ������Ʈ �Ѵ�.
	pclOrder->siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// �ֹ� ��¥�� Ȯ���Ѵ�. 
	pclOrder->siDate = pclTime->clDate.GetDateVary();

	// ���� �ֹ��� �������� ������ Ȯ���Ѵ�. 
	cltItem clItem;
	clItem.Set(&pclOrder->clItemData);

	// Person�� �ֹ� ������ �������� Ȯ���Ѵ�. 
	if( false == pclCM->CR[id]->pclCI->clBI.bMarKetPremiumService )
	{
		// ���� �����̾��� ���ٸ� �Ǹ� ������ ������ 4��
		if( pclCM->CR[id]->GetMarketOrderNumber() >= 4 )
		{
			SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAIL_ORDERSELL_OVERFLOW,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}
	else
	{
		// ���� �����̾��� �ִٸ� �Ǹ� ������ ������ 8��
		if( pclCM->CR[id]->GetMarketOrderNumber() >= MAX_MARKET_ORDER_PER_PERSON )
		{
			SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAIL_ORDERSELL_OVERFLOW,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}

	// �̹� �÷��� ��ǰ���� Ȯ���Ѵ�. 
	if( pclCM->CR[id]->pclCI->clMarket.IsInMarketOrder(clItem.siUnique) == true)
	{
		return ;
	}
	
	// �ż� �ֹ��� �ִ´�. 
	SI32 orderref = -1;
	SI32 retval = 0;
	
	// DB�� ���� �ֹ� ���ۿ� ������ ���� ���� ��û�Ѵ�. 
	SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(&clItem, true);
	
	SI32 itemunique = clItem.siUnique;

	if(itempos >= 0 && itemunique > 0 )
	{
		// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
		if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode == PSHOP_MODE_SELL)
		{
			for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
			{
				if( pclchar->clShopData.m_siSelectedInventoryPos[i] == itempos	)
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
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == itempos	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}
	}

	//�Ⱓ�� �������� ��� ���� ���Ⱓ�� �ִ��� Ȯ���Ѵ�.
	if ( itemunique > 0 )
	{
		if ( clItem.IsHaveUseDay() )  //[����] ���� ���Ⱓ ���� �˸�
		{
			SI32 useableDay = 0;
			BOOL rVal = GetItemUseAbleDay(&clItem,&useableDay);
			if(rVal == FALSE) return;

			if( useableDay < 0)		// ���Ⱓ�� ���� �������� �ŷ��� �� ����.
			{
				SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
				return;
			}
		}
	}

	if(itempos >= 0)
	{
		// ������ �ŷ� ��踦 ����. 
		pclItemManager->AddTradeNum(pclOrder->GetItemUnique(), pclOrder->siAmount);

		// ���ο� ��� - ������ �ŷ� (�޸���Ÿ��Ʋ, �ش����������ũ, �޸�������÷��̸�, �߰��Ǵ� ��)
		NStatistics_Add("Item", pclOrder->GetItemUnique(),"TradeNum", pclOrder->siAmount);
		NStatistics_Set("Item", pclOrder->GetItemUnique(), "Name", pclItemManager->GetName(pclOrder->GetItemUnique()));
		
		// ����Ʈ ������ ������Ʈ �Ѵ�.
		((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_UPITEMTOMARKET, clItem.siUnique  , pclOrder->siAmount);


		sDBRequest_OrderMarket	clMsg(id, ORDERMODE_SELL, villageunique, pclOrder, itempos, clItem.CanPile(pclItemManager), tax);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
}

// ���ֿ��� ��ǰ ���Կ� ���� ó���� �Ѵ�. 
void cltServer::MarketBuyAction(SI16 id, SI16 villageunique, cltTradeOrder* pclOrder, SI16 siReason)
{

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// ���� �ֹ��� Ȯ���Ѵ�. 
	SI32 orderref = -1;
	SI32 retval = 0;
	
	// �ֹ� ����Ʈ���� �ε����� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* pclorder = pclMarketManager->pclOrderManager->GetOrder(ORDERMODE_SELL, pclOrder->siIndex);
	if(pclorder == NULL)
	{
		if(pclchar)
		{
			SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  500, 0, pclchar->GetCharUnique());
			return ;
		}
	}
	
	// ������ Ʋ���� ����. 
	if(pclorder->siPrice != pclOrder->siPrice)
	{
		if(pclchar)
		{
		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  550, 0, pclchar->GetCharUnique());
		return ;
		}
	}
	
	// ���� ��ǰ�� �� ������ Ʋ���� ����. 
	if(pclMarketManager->pclOrderManager->IsSameKind(pclorder, pclOrder) == false)
	{
		if(pclchar)
		{

		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  600, 0, pclchar->GetCharUnique());
		return ;
		}
	}
	
	// �ŷ� ����. (�� �ֹ���  ��� ����) 
	GMONEY tradeprice		= pclorder->siPrice;
	
	cltItem clItem;
	clItem.Set(&pclOrder->clItemData);
	
	// �� �ŷ����. 
	GMONEY totaltrademoney = tradeprice * pclOrder->siAmount;

	if(pclchar)
	{
		
		// �� �ŷ� ����� ���� ���� �ѵ��� �ʰ��ϸ� �ֹ� ����. 
		if(totaltrademoney > pclCM->CR[id]->pclCI->clIP.GetMoney())
		{
			SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  700, 0, pclchar->GetCharUnique());
			return ;
		}
	}
	
	//---------------------------------------------
	// ������ ������ �ִ� ��� ������ �ʰ��ϸ� ���� 
	//---------------------------------------------
/*	cltItem cltoitem;
	if(pclchar)
	{
		if(pclchar->pclCI->clCharItem.GetItemNum(clItem.siUnique) +  pclOrder->siAmount > MAX_ITEM_PILE_NUMBER)
		{
			SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  800, 0, pclchar->GetCharUnique());
			return ;
		}
	}
*/	
	//--------------------------------------------
	// ������ ��ǰ�� ��ġ�� �ڸ��� Ȯ���Ѵ�. 
	//--------------------------------------------
	SI16 EmptyPos	= 0;
	SI32 rtnvalue	= 0;
	cltItem clToItem;
	cltItem clitem;
	
	clitem.Set(&pclOrder->clItemData);
	
	// �������� ���� �� �ִ��� üũ
	if(pclchar)
	{
		if ( ! pclchar->CanAddInv(INVMODE_ALL, &clitem, &EmptyPos, &clToItem , &rtnvalue) )
		{
			SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  900, 0, pclchar->GetCharUnique());
			return ;
		}
	}
	
	sDBRequest_TradeMarket clMsg(id, villageunique, clItem.CanPile(pclItemManager), pclOrder, pclorder->siIndex, tradeprice, EmptyPos, MARKETTRADE_REASON_NORMAL);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_BUYITEM(cltMsg* pclMsg, SI32 id)
{
	cltTradeOrder* pclOrder = (cltTradeOrder*)pclMsg->cData;

	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)
	{
		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  100, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}


	if(pclOrder->siType != TRADEORDER_TYPE_OBJECT)
	{

		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  200, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//------------------------------------------
	// ���� �ֹ��ڿ� �ڽ��� ������ ������ �� �� ����. 
	//---------------------------------------------
	if(pclOrder->siPersonID == pclCM->CR[id]->pclCI->GetPersonID())
	{
		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  300, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
	{
		SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  400, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	
	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	if(pclClient->IsCountrySwitch(Switch_FourLeaf))
	{
		//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
		if( ITEMUNIQUE(2755) == pclOrder->clItemData.siUnique || ITEMUNIQUE(2754) == pclOrder->clItemData.siUnique )	
		{	
			if( pclOrder->clItemData.siUnique != siFourLeafUnique )	
			{
				SendServerResponseMsg( 0, SRVAL_RETURN_NOT_USE_FOURLEAF, 0, 0, pclchar->GetID() );
				return;	
			}
		}
	}



	// PersonID�� ������Ʈ �Ѵ�.
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	pclOrder->siPersonID = personid;
	
	MarketBuyAction( id, villageunique, pclOrder, MARKETTRADE_REASON_NORMAL );

}

// ������ �ֹ� ����Ʈ�� ��û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_MARKETORDER(cltMsg* pclMsg, SI32 id)
{
	SI32 i, j;

	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(800) == true)
	{
		return ;
	}

	cltGameMsgRequest_MarketOrder* pclinfo = (cltGameMsgRequest_MarketOrder*)pclMsg->cData;	
	
	// �䱸�Ǵ� �������� Ȯ���Ѵ�. 
	SI32 itemunique = pclinfo->siItemUnique;
	if(itemunique <= 0)return ;
	if(itemunique >= MAX_ITEM_UNIQUE)return ;

	GMONEY pricecond = pclinfo->siPriceCondition;
	if(pricecond < 0)pricecond = 0;

	// �������� Ÿ���� ���Ѵ�. 
	SI32 itemtype = pclItemManager->GetItemType(itemunique);
	if(itemtype <= 0)return ;


	// ���� �ֹ����� �䱸�Ǵ� �������� �͵��� ã�Ƽ� Ŭ���̾�Ʈ�� ������.
	SI32 searchnum			= pclMarketManager->siItemTypeOrderIndex[itemtype];
	cltTradeOrder** porder	= pclMarketManager->pclOrderManager->pclOrderSell;

	//-------------------------------------------
	// ���� �ü��� ������. 
	//-------------------------------------------
	{
		cltItemPriceUnit clunit;
		
		clunit.siUnique = itemunique;
		
		cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(itemunique);
		if(pclprice)
		{
			clunit.siPrice	= pclprice->siPrice;
			
			// Ŭ���̾�Ʈ�� ������ ������.
			cltGameMsgResponse_ProductPrice clinfo(itemunique, clunit.siPrice);
			cltMsg clMsg(GAMEMSG_RESPONSE_PRODUCTPRICE, sizeof(clinfo), (BYTE*)&clinfo);
			
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}


	//-------------------------------------------------
	// ������ ���� �ֹ��� Ȯ���ؼ� ������. 
	//------------------------------------------------
	SI32 sendnum	=	0;
	cltTradeOrder	clorder[MARKET_ORDER_SEND_UNIT];
	SI32 index		= 0;
	SI32 ref		= 0;

	if (searchnum > MAX_MARKET_ORDER_NUMBER)		searchnum = MAX_MARKET_ORDER_NUMBER;
	for(i = 0;i < searchnum;i++)
	{
		ref = pclMarketManager->pclItemTypeOrder[itemtype][i];

		if( ref < 0 || ref >= MAX_MARKET_ORDER_NUMBER)	continue;
		if( porder[ref] == NULL)						continue;

		// ���� ����ũ ���� ���´ٸ�, 
		if(porder[ref]->clItemData.siUnique != itemunique)	continue;
		if(sendnum >= MAX_RESPONSE_ORDER_NUMBER)			continue;
		if(pricecond && pricecond < porder[ref]->siPrice)	continue;	// ���� ���� ���ǿ� �ɸ����� Ȯ��. 

		sendnum++;
		
		clorder[index].Set(porder[ref]);
		index++;
		
		// �� á���� ������. 
		if(index == MARKET_ORDER_SEND_UNIT)
		{
			// ������. 
			// Ŭ���̾�Ʈ�� ������ ������. 
			cltMsg clMsg(GAMEMSG_RESPONSE_MARKETORDER, sizeof(cltTradeOrder) * MARKET_ORDER_SEND_UNIT, (BYTE*)clorder);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			
			// �ٽ� �ʱ�ȭ�Ѵ�. 
			index	= 0;
			for(j  = 0;j < MARKET_ORDER_SEND_UNIT;j++)
			{
				clorder[j].Init();
			}
		}
		
	}

	// ���� ���� ������. 
	if(index)
	{
		// Ŭ���̾�Ʈ�� ������ ������. 
		cltMsg clMsg(GAMEMSG_RESPONSE_MARKETORDER, sizeof(cltTradeOrder) * MARKET_ORDER_SEND_UNIT, (BYTE*)clorder);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	if(sendnum == 0)
	{
		for(j  = 0;j < MARKET_ORDER_SEND_UNIT;j++)
		{
			clorder[j].Init();
		}

		// Ŭ���̾�Ʈ�� ������ ������. 
		cltMsg clMsg(GAMEMSG_RESPONSE_MARKETORDER, sizeof(cltTradeOrder) * MARKET_ORDER_SEND_UNIT, (BYTE*)clorder);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// ��ǰ ȸ��. 
void cltServer::DoMsg_GAMEMSG_REQUEST_GETFROMMARKET(cltMsg* pclMsg, SI32 id)
{	
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}


	cltGetItemFromMarketInfo* pclInfo = (cltGetItemFromMarketInfo*)pclMsg->cData;
	
	// PersonID�� ������Ʈ �Ѵ�.
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();
	
	// �ش� person�� �κ����� �������� �Űܳ��� ������ ��ġ�� ã�´�. 
	SI16 sitopos;
	cltItem clto;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclInfo->clFromItem, &sitopos, &clto, &rtnvalue) == true)
	{
		// Ŭ���̾�Ʈ���� ��ϵ��� ���� ������ �������� ����Ѵ�. (���Ȼ��� ����. ) 
		pclInfo->siPersonID	= personid;
		pclInfo->siToPos	= sitopos;
		pclInfo->clToItem.Set(&clto);
		
		// DB�޴������� �������� �Űܳ��� ���� ��û�Ѵ�.
		sDBRequest_GetItemFromMarket clMsg(id, pclInfo);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		
	}
	// ������ ��ġ�� ã�� �� ���ٸ� ����. 
	else
	{
		SendServerResponseMsg(RANKTYPE_MARKET, SRVAL_MARKET_FAIL_GETFROMMARKET,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}	
}
void cltServer::DoMsg_GAMEMSG_REQUEST_PRODUCTPRICE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_ProductPrice* pclInfo = (cltGameMsgRequest_ProductPrice*)pclMsg->cData;

	cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(pclInfo->siItemUnique);
	if(pclprice)
	{
		// Ŭ���̾�Ʈ�� ������ ������.
		cltGameMsgResponse_ProductPrice clinfo(pclInfo->siItemUnique, pclprice->siPrice, pclInfo->siDialogID );
		cltMsg clMsg(GAMEMSG_RESPONSE_PRODUCTPRICE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWMARKETACCOUNT(cltMsg* pclMsg, SI32 id)
{
	if( sTime.wHour == 5 && ( sTime.wMinute >= 50 && sTime.wMinute <= 59 ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	if( false == pclCM->IsValidID(id) )
		return;

	//--------------------------------------------
	// ������ ���� ������ ���� 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;

	SI32 personID = pclCM->CR[id]->pclCI->GetPersonID();
	if( 0 < personID )
	{
		sDBRequest_NewMarketAccount	clMsg( id, siServerUnique, personID );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWMARKETITEMLIST(cltMsg* pclMsg, SI32 id)
{
	if( sTime.wHour == 5 && ( sTime.wMinute >= 50 && sTime.wMinute <= 59 ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	if( false == pclCM->IsValidID(id) )
		return;

	//--------------------------------------------
	// ������ ���� ������ ���� 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;

	cltGameMsgRequest_NewMarketItemList* pclinfo = (cltGameMsgRequest_NewMarketItemList*)pclMsg->cData;

	SI32 itemunique = pclinfo->siItemUnique;
	if(itemunique <= 0)return ;
	if(itemunique >= MAX_ITEM_UNIQUE)return ;

	if( 0 < pclinfo->siRequestPage )
	{
		sDBRequest_NewMarketItemList	clMsg( id, pclinfo->uiType, itemunique, pclinfo->siRequestPage );
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_NEWSELLITEM(cltMsg* pclMsg, SI32 id)
{
	if( sTime.wHour == 5 && ( sTime.wMinute >= 50 && sTime.wMinute <= 59 ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	//--------------------------------------------
	// ������ ���� ������ ���� 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;

	cltGameMsgRequest_NewSellItem * pclmsg = (cltGameMsgRequest_NewSellItem*)pclMsg->cData ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->GetCharServer( id );
	if( NULL == pclchar ) return;

	pclchar->ItemUseReserveAction();	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	pclchar->BulletUseReserveAction();	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 

	if(false == IsUseFourLeaf(0, pclchar)) return;


	cltNewTradeOrder pclOrder ;
	pclOrder.Init();
	pclOrder.siServerUnique = siServerUnique;
	pclOrder.siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	pclOrder.siAmount = pclmsg->clTradeOrder.siAmount;
	pclOrder.siDate = pclmsg->clTradeOrder.siDate;
	pclOrder.siPrice = pclmsg->clTradeOrder.siPrice;
	pclOrder.clItemData.Set(&pclmsg->clTradeOrder.clItemData);

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	//---------------------------------------------
	// �ŷ� ���� ǰ������ Ȯ���Ѵ�. 
	//---------------------------------------------
	if( false == pclItemManager->IsNewMarketTrade( pclOrder.clItemData.siUnique ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	if(	true == pclItemManager->IsItemInfoAtb(pclOrder.clItemData.siUnique, ITEMINFOATB_NOTTRADE) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclOrder.clItemData.siUnique);
	if ( ref )
	{
		SI32 itemtype = pclItemManager->pclItemInfo[ref]->siType ;
		// ������Ʈ �����̳�?
		if ( pclItemManager->pclItemTypeInfo[itemtype]->IsAtb(ITEMATB_OBJECT) )
		{
			if(false == pclOrder.clItemData.IsSealingUp(pclClient->pclItemManager))	
			{
				SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
				return;
			}
		}
	}

	SI32 itemRef = pclItemManager->FindItemRefFromUnique(pclOrder.clItemData.siUnique);

	if( itemRef <= 0 || itemRef >= MAX_ITEMINFO_NUMBER ) return;
	if( pclItemManager->pclItemInfo[ itemRef ]->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) == true )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	// ������ ���� ���������� Ȯ���Ѵ�. 
	if(pclOrder.siPrice <= 0 || pclOrder.siPrice > MAX_PRICE_IN_MARKET)return ;

	// ������ �� ���� �ִ��� Ȯ���Ѵ�. 

	cltStrInfo* pclinfo = GetStrInfo( villageunique, RANKTYPE_NEWMARKET );
	if(pclinfo == NULL)return ;

	GMONEY totalmoney = (SI64)pclOrder.siPrice * (SI64)pclOrder.siAmount;

	GMONEY tax = pclinfo->clNewMarketStrInfo.clFee.CalcFee(totalmoney);
	if(pclCM->CR[id]->pclCI->clIP.GetMoney() < tax)	
		return;
		
	// PersonID�� ������Ʈ �Ѵ�.
	pclOrder.siPersonID = pclCM->CR[id]->pclCI->GetPersonID();

	// �ֹ� ��¥�� Ȯ���Ѵ�. 
	pclOrder.siDate = pclTime->clDate.GetDateVary();

	// ���� �ֹ��� �������� ������ Ȯ���Ѵ�. 
	cltItem clItem;
	clItem.Set(&pclOrder.clItemData);

	SI32 itempos = pclmsg->siPos;
	if(itempos >= 0)
	{
		if ( pclCM->CR[id]->pclCI->clCharItem.clItem[itempos].IsSame(&clItem,true) )
		{
			sDBRequest_NewOrderMarket	clMsg(id,  villageunique, &pclOrder, itempos, clItem.CanPile(pclItemManager), tax, 0);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETFROMNEWMARKET(cltMsg* pclMsg, SI32 id)
{
	if( sTime.wHour == 5 && ( sTime.wMinute >= 50 && sTime.wMinute <= 59 ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)
	{
		return ;
	}

	// ��ǰ ã��� ���ֲ� �״�� ����
	cltGetItemFromNewMarketInfo* pclInfo = (cltGetItemFromNewMarketInfo*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->GetCharServer( id );
	if( NULL == pclchar ) return;

	pclchar->ItemUseReserveAction();	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	pclchar->BulletUseReserveAction();	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 

	if(false == IsUseFourLeaf(0, pclchar)) return;

	// PersonID�� ������Ʈ �Ѵ�.
	SI32 personid = pclchar->pclCI->GetPersonID();

	if( 0 > personid )
		return;

	if( 0 > pclInfo->siOrderIndex )
		return;

	// �ش� person�� �κ����� �������� �Űܳ��� ������ ��ġ�� ã�´�. 
	SI16	sitopos;
	cltItem clto;
	SI32	rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclInfo->clFromItem, &sitopos, &clto, &rtnvalue) == true)
	{
		// Ŭ���̾�Ʈ���� ��ϵ��� ���� ������ �������� ����Ѵ�. (���Ȼ��� ����. ) 
		sDBRequest_GetItemFromNewMarket clMsg( id, siServerUnique, personid,  pclInfo->siOrderIndex, pclInfo->bPileSwitch, &pclInfo->clFromItem, sitopos);
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
	}
	// ������ ��ġ�� ã�� �� ���ٸ� ����. 
	else
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_GETFROMMARKET,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NEWBUYITEM(cltMsg* pclMsg, SI32 id)
{
	if( sTime.wHour == 5 && ( sTime.wMinute >= 50 && sTime.wMinute <= 59 ) )
	{
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAIL_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;		
	}

	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)
	{
		SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  100, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	cltNewTradeOrder* pclOrder = (cltNewTradeOrder*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->GetCharServer( id );
	if( NULL == pclchar ) return;

	pclchar->ItemUseReserveAction();	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	pclchar->BulletUseReserveAction();	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 

	if(false == IsUseFourLeaf(0, pclchar)) return;


	//------------------------------------------
	// ���� �ֹ��ڿ� �ڽ��� ������ ������ �� �� ����. 
	//---------------------------------------------
	if( pclOrder->siPersonID == pclCM->CR[id]->pclCI->GetPersonID() &&
		pclOrder->siServerUnique == siServerUnique ) 
	{
		SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  300, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
	{
		SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  400, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// PersonID�� ������Ʈ �Ѵ�.
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// �ŷ� ����. 
	SI64 tradeprice	= pclOrder->siPrice;

	cltItem clItem;
	clItem.Set(&pclOrder->clItemData);

	// �Ⱓ�� �̻��� ��� �͵� �� �����Ѵ�.
	SI16 date = (SI16)clItem.uiDateUseDay ;
	if ( date < 0 )
	{
		if ( pclchar )
		{
			SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  600, 0, pclchar->GetCharUnique());
		}
		return ;
	}

	// �� �ŷ����. 
	SI64 totaltrademoney = tradeprice * pclOrder->siAmount;

	if(pclchar)
	{
		// �� �ŷ� ����� ���� ���� �ѵ��� �ʰ��ϸ� �ֹ� ����. 
		if(totaltrademoney > pclCM->CR[id]->pclCI->clIP.GetMoney())
		{
			SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  700, 0, pclchar->GetCharUnique());
			return ;
		}
	}

	//---------------------------------------------
	// ������ ������ �ִ� ��� ������ �ʰ��ϸ� ���� 
	//---------------------------------------------
	cltItem cltoitem;
	if(pclchar)
	{
		if(pclchar->pclCI->clCharItem.GetItemNum(clItem.siUnique) +  pclOrder->siAmount > 100000 )
		{
			SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  800, 0, pclchar->GetCharUnique());
			return ;
		}
	}

	//--------------------------------------------
	// ������ ��ǰ�� ��ġ�� �ڸ��� Ȯ���Ѵ�. 
	//--------------------------------------------
	SI16 EmptyPos	= 0;
	SI32 rtnvalue	= 0;
	cltItem clToItem;
	cltItem clitem;

	clitem.Set(&pclOrder->clItemData);

	// �������� ���� �� �ִ��� üũ
	if(pclchar)
	{
		if ( ! pclchar->CanAddInv(INVMODE_ALL, &clitem, &EmptyPos, &clToItem , &rtnvalue) )
		{
			SendServerResponseMsg(0, SRVAL_NEWMARKET_BUY_FAIL,  900, 0, pclchar->GetCharUnique());
			return ;
		}
	}

	sDBRequest_NewTradeMarket clMsg(id, siServerUnique, villageunique, personid, pclOrder, tradeprice,  EmptyPos, clItem.CanPile(pclItemManager), clItem.IsCreateSID(pclItemManager), &sTime );
	pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETNEWMARKETFEE(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = (cltCharServer*)pclCM->GetCharServer( id );
	if( NULL == pclchar ) return;

	// �Ϸ翡 �ѹ��� ������ ������ �����ϰ�.
	if( false == pclNewMarketManager->m_bSetFee ) 
	{ 
		SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_NEWMARKET_FAILSETFEE,  0, 0, pclchar->GetCharUnique());
		return;
	}

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageUnique = pclchar->GetCurrentVillageUnique();
	if( 0 < villageUnique && MAX_VILLAGE_NUMBER >= villageUnique )
	{
		// ������ ������ Ȯ���Ѵ�. 
		cltFee* pclfee = (cltFee*)pclMsg->cData;
		
		// ���ո��� ������� 5% ~ 15%
		if( MIN_FEE_RATE_NEWMARKET*10 <= pclfee->GetFeeRate() && MAX_FEE_RATE_NEWMARKET*10 >= pclfee->GetFeeRate() )
		{
			//----------------------------------
			// ��û�ڰ� ����������� Ȯ���Ѵ�. 
			//----------------------------------
			cltSimpleRank clrank(RANKTYPE_NEWMARKET, villageUnique);
			if( FALSE == pclRankManager->IsRank(pclchar->pclCI->GetPersonID(), &clrank) )
			{
				// ������ ������ ����. 
				SendServerResponseMsg(RANKTYPE_NEWMARKET, SRVAL_MARKET_FAILSETFEE,  0, 0, pclchar->GetCharUnique());
				return ;
			}

			// DB �� ������.
			sDBRequest_SetNewMarketFee clMsg(id, pclchar->pclCI->GetPersonID(), villageUnique, pclfee);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
		}
	}
}




