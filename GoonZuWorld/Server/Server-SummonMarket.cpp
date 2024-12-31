#include "Char\CharManager\CharManager.h"
#include "../Server/Minister/MinisterBase.h"
#include "../Server/Minister/MinisterMgr.h"
#include "../Server/Minister/Minister-Izo.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-SummonMarket.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\Msg\MsgType-SummonMarket.h"	

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_MYORDER(cltMsg* pclMsg, SI32 id )
{
 	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_SummonMarketMyOrder sendMsg( id, personid );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_CANCELORDER(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SummonMarketCancelOrder *pclinfo = (cltGameMsgRequest_SummonMarketCancelOrder *)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)
		return ;

	if(FALSE == pclCM->CR[id]->pclCI->clSummonInfo.CanHaveSummon())
	{
		// ��ȯ���� ���̻� ������ �� ���� 
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_CANCELORDER_NOMORE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	sDBRequest_SummonMarketCancelOrder sendMsg( id, personid, pclinfo->siOrderIndex );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SummonMarketOrderList *pclinfo = (cltGameMsgRequest_SummonMarketOrderList *)pclMsg->cData;

	cltGameMsgResponse_SummonMarketOrderList sendMsg;

	cltSummonOrder *pclOrder;
	int count = 0;
	int i;

	sendMsg.usCount		  = 0;
	SI32 TotalSummonCount = 0;

	if( pclinfo->siSelectList == 1 ) 
	{
		SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

		for( i = 0; i < MAX_SUMMONMARKET_ORDER_NUMBER; ++i ) 
		{
			pclOrder = &pclSummonMarketManager->pclSummonOrder[ i ];
		
			if( pclOrder->siPersonID &&	pclOrder->siSelectPersonID == personid ) 
			{
				++count; 

				sendMsg.clOrder[ sendMsg.usCount ].Set( pclOrder );
				++sendMsg.usCount;
			}

			if( sendMsg.usCount == MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER ) 
				break;

			if( count >= pclSummonMarketManager->siTotalOrderNumber ) 
				break;
		}
	}
	else 
	{
		SI32 siOrderListStart = pclinfo->siStartPos * MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER;	// �ֹ� ������ ������ ó�� �迭.
		for(i = 0; i < MAX_SUMMONMARKET_ORDER_NUMBER; ++i ) 
		{
			pclOrder = &pclSummonMarketManager->pclSummonOrder[ i ];

			//test++++++++++++++++++++++++++++++++++++++++++++
			// �ֹ� ���� ä��� �׽�Ʈ.
			/*if(i < MAX_SUMMONMARKET_ORDER_NUMBER)
			{
				memcpy(&pclSummonMarketManager->pclSummonOrder[i], &pclSummonMarketManager->pclSummonOrder[0], sizeof(pclSummonMarketManager->pclSummonOrder[0]));
				pclSummonMarketManager->pclSummonOrder[i].siPrice += i;
			} */
			//test++++++++++++++++++++++++++++++++++++++++++++

			if(	pclOrder->siPersonID &&	pclOrder->clSummon.siKind == pclinfo->siKind)
			{		
				TotalSummonCount++;
			}

			if(		pclOrder->siPersonID 	
				&&  pclOrder->clSummon.siKind == pclinfo->siKind 
				&&  i >= siOrderListStart
				&&  sendMsg.usCount < MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER)
			{
				++count; 

				sendMsg.clOrder[ sendMsg.usCount ].Set( pclOrder );
				++sendMsg.usCount;
			}

			//if( sendMsg.usCount == MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER ) ;
				//break;

			//if( count >= pclSummonMarketManager->siTotalOrderNumber ) ;
				//break;
		}
	}

	// ���� �ŷ��� ���������� ������ �ϳ�.
	if( pclinfo->siSelectList == 1 ) 
	{
		sendMsg.siCurrentPage  = 0;
		sendMsg.usTotalPage	   = 0;	//[����] ��ü ������ ��.
	}
	else
	{
		sendMsg.siCurrentPage  = pclinfo->siStartPos;
		sendMsg.usTotalPage	   = TotalSummonCount / MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER;	//[����] ��ü ������ ��.
	}	

	cltMsg clMsg( GAMEMSG_RESPONSE_SUMMONMARKET_ORDERLIST, sendMsg.GetTotalSize(), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_SELL(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_SummonMarketSell *pclinfo = (cltGameMsgRequest_SummonMarketSell *)pclMsg->cData;

	GMONEY price = pclinfo->siPrice;
	GMONEY tax = (GMONEY)(price * 0.01);

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	// ������ �����ִ� ��ȯ���� ������ ���ο��� update ��Ų��.
	((cltCharServer *)pclCM->CR[ id ])->UpdateTakeOutSummon();

	// ������ �������� ��ȯ���� �����ϰ� �ִ°�?
	cltSummon *pclSummon = pclCM->CR[ id ]->pclCI->clSummonInfo.GetSummon( pclinfo->siSummonIndex );
	if( pclSummon == NULL ) return;

	//[����] ��ȯ�� ��� ���� �˻�.
	if( pclCM->CR[ id ]->pclCI->clSummonInfo.IsHaveEquipItem(pclinfo->siSummonIndex) )
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELL_HAVEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	//[����] ���� ��ȯ�� ��� ���� �˻�.
	/*if( pclCM->CR[ id ]->IsSummonHaveItem( pclinfo->siSummonIndex ) ) 
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELL_HAVEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}*/

	if( pclClient->pclKindInfoSet->IsValidKind(pclSummon->siKind) == false ) 
	{ 
		//SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELL_NOTVALID,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	cltKindInfo* pclKI	= NULL;
	//[����] ��ȯ�� ���̺� �и�. => 2008-6-18
	if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
	{
		pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];
	}
	else
	{
		pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];
	}
	if(NULL == pclKI)
		return;
	
	// �ŷ� �Ұ� ��ȯ�� Ȯ��.
	if(false == pclKI->bSummonTrade)
		return;

	if( pclSummon->siStatus == SUMMON_STATUS_DEAD || pclSummon->clIP.GetLife() <= 0 ) 
	{
		return;
	}

	//[����] ���� ��ȯ�� ��� ���� �˻�.
	/*if( pclCM->CR[ id ]->IsSummonHaveItem( pclinfo->siSummonIndex ) ) 
	{
		return;
	}*/

	cltSummonOrder clOrder;

	clOrder.siPersonID = personid;
	clOrder.siPrice = price;
	clOrder.clDate.Set( &pclTime->clDate );
	
	clOrder.clSummon.Set( pclSummon );
	clOrder.clSummon.siStatus = SUMMON_STATUS_TAKEIN; // ��ȯ���� �������� �ʴ� ���·� �����.


	SI16 pos = 0;
	cltItem clitem;

	clitem.Init();

//#if defined(_LEON_ADD_SELECTSELL_CODE)
	// ���� �ŷ� ����ڰ� ���µ� �ŷ� ������ �Ϲ� �ŷ��� �ƴϰų�
	// ���� �ŷ� ����ڰ� �ִµ� �ŷ� ������ ���� �ŷ��� �ƴϸ�
	// => �߸��� �ŷ���
	if(     (pclinfo->szSelectPersonName[ 0 ] == NULL && pclinfo->uiTradeType != cltGameMsgRequest_SummonMarketSell::TRADE_TYPE_NORMAL) 
		||  (pclinfo->szSelectPersonName[ 0 ] != NULL && pclinfo->uiTradeType != cltGameMsgRequest_SummonMarketSell::TRADE_TYPE_SELECTIVE ) )
	{
        // ��ȯ�� ���� �ֹ��� �����Ͽ����ϴ�.			
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELL, 0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
//#endif

	// ���� �ŷ��� ���,
	if( _tcslen(pclinfo->szSelectPersonName) > 0 ) 
	{
		SI16 itemunique = ITEMUNIQUE(24055) ; // �����ŷ��̿��

		if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum( itemunique ) <= 0 ) 
		{
			// ���� �ŷ� �̿�� ���� 
			SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELECTSELL_NOTHAVETICKET,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}

		pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( itemunique );
		if( pos < 0 ) 
		{
			// ���� �ŷ� �̿�� ���� 
			SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELECTSELL_NOTHAVETICKET,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}

		CMinisterIzo* pclminister = (CMinisterIzo*)pclMinisterMgr->GetMinister(MINISTER_IZO);
		
		if( pclminister->m_siTradeLimitMoney > pclinfo->siPrice ) 
		{
			SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SELECTSELL_WRONGPRICE,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}


		clitem.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[pos] );
		clitem.SetItemNum( 1 );

	}

//#if defined(_LEON_ADD_SELECTSELL_CODE)
	sDBRequest_SummonMarketOrderSell sendMsg( id, villageunique, &clOrder, tax, pclinfo->szSelectPersonName, pos, &clitem, pclinfo->uiTradeType );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, tax);
//#endif

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_BUY(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SummonMarketBuy *pclinfo = (cltGameMsgRequest_SummonMarketBuy *)pclMsg->cData;

	GMONEY	price		 = 0;
	SI32	orderindex	 = 0;
	SI32	housevillage = 0;
	SI32	houseindex	 = 0;
	
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
		return ;

	if( pclCM->CR[ id ]->pclCI->clIP.GetLevel() < LIMIT_LEVEL_HATCH_DOLL ) 
		return;

	// ��ȯ���� �� ������ �� �ִ°�
	if( pclCM->CR[ id ]->pclCI->clSummonInfo.CanHaveSummon() == FALSE ) 
	{
		SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_BUY_NOMORE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	int count = 0;
	for( int i = 0; i < MAX_SUMMONMARKET_ORDER_NUMBER; ++i ) 
	{
		if( pclSummonMarketManager->pclSummonOrder[ i ].siPersonID != 0 ) 
		{
			++count;

			if( pclSummonMarketManager->pclSummonOrder[ i ].siIndex == pclinfo->siOrderIndex ) 
			{

				if( pclSummonMarketManager->pclSummonOrder[ i ].siPersonID == personid ) 
				{
					SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_BUY_NOTSELF,  0, 0, pclCM->CR[id]->GetCharUnique());
					return;
				}


				orderindex = pclSummonMarketManager->pclSummonOrder[ i ].siIndex;
				price	   = pclSummonMarketManager->pclSummonOrder[ i ].siPrice;

				sDBRequest_SummonMarketBuy sendMsg( id, personid, villageunique, orderindex, price );
				pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				return;
			}
		}

		if( count >= pclSummonMarketManager->siTotalOrderNumber ) 
			break;
	}

	SendServerResponseMsg( RANKTYPE_SUMMONMARKET, SRVAL_REALESTATEMARKET_FAIL_BUY_NOTVALID,  0, 0, pclCM->CR[id]->GetCharUnique());
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SUMMONMARKET_SETFEE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SummonMarketSetFee *pclinfo = (cltGameMsgRequest_SummonMarketSetFee *)pclMsg->cData;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;
	
	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = &pclinfo->clFee;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;
	
	//----------------------------------
	// ��û�ڰ� �忹��������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_SUMMONMARKET, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_SUMMONMARKET, SRVAL_SUMMONMARKET_FAIL_SETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	sDBRequest_SummonMarketSetFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}
