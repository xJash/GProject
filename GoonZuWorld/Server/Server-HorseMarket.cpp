#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-HorseMarket.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\Msg\MsgType-HorseMarket.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_MYACCOUNT(cltMsg* pclMsg, SI32 id )
{

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_HorseMarketMyAccount sendMsg( id, personid );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_OUTHORSE(cltMsg* pclMsg, SI32 id )
{

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;
	
	// �纹�÷κ��� ���� ������. 
	SI16 index = pclCM->CR[id]->pclCI->clHorseInfo.FindEmptyHorseIndex();
	if(index < 0)return ;	// ���� ������ ������ ����. 

	// ���� ���� ���� DB�� ��û�Ѵ�. 
	sDBRequest_HorseMarketOutHorse sendMsg( id, personid, index );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_ORDERLIST(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_HorseMarketOrderList *pclinfo = (cltGameMsgRequest_HorseMarketOrderList *)pclMsg->cData;

	cltGameMsgResponse_HorseMarketOrderList sendMsg;

	cltHorseOrder *pclOrder;
	int count = 0;

	sendMsg.usCount = 0;

	for( int i = 0; i < MAX_HORSEMARKET_ORDER_NUMBER; ++i ) {

		pclOrder = &pclHorseMarketManager->pclHorseOrder[ i ];
		
		if( pclOrder->siPersonID != 0 ) {
			++count; 

			// ��û�� ���� ǰ���� ���ٸ�, 
			if( pclOrder->clHorse.siHorseUnique == pclinfo->siHorseUnique ) {

				switch( pclinfo->siPriceType ) {
				case 0:
					{
						if( pclOrder->siPrice < 200000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}
					}
					break;
				
				case 1:
					{
						if( pclOrder->siPrice >= 200000 && pclOrder->siPrice < 500000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}
					}
					break;
				case 2:
					{
						if( pclOrder->siPrice >= 500000 && pclOrder->siPrice < 1000000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}	
					}
					break;
				case 3:
					{
						if( pclOrder->siPrice >= 1000000 && pclOrder->siPrice < 2000000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}	

					}
					break;
					
				case 4:
					{
						if( pclOrder->siPrice >= 2000000 && pclOrder->siPrice < 5000000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}	

					}
					break;

				case 5:
					{
						if( pclOrder->siPrice >= 5000000 && pclOrder->siPrice < 10000000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}	

					}
					break;

				case 6:
					{
						if( pclOrder->siPrice >= 10000000 ) {						
							sendMsg.clHorseOrder[ sendMsg.usCount ].Set( pclOrder );
							++sendMsg.usCount;
						}	
					}
					break;
				}
				
			}
		}

		if( sendMsg.usCount >= MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER ) break;

		if( count >= pclHorseMarketManager->siTotalOrderNumber ) break;
	}

	if( sendMsg.usCount > 0 ) {

		cltMsg clMsg( GAMEMSG_RESPONSE_HORSEMARKET_ORDERLIST, sendMsg.GetTotalSize(), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}


}



void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_SELLHORSE(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_HorseMarketSellHorse *pclinfo = (cltGameMsgRequest_HorseMarketSellHorse *)pclMsg->cData;

	GMONEY price = pclinfo->siPrice;
	GMONEY tax = price * 1 / 100 ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;


	cltHorse *pclHorse = pclCM->CR[ id ]->pclCI->clHorseInfo.GetHorse(pclinfo->siHorseIndex);

	// ���� �ֳ� ����
	if( pclHorse == NULL || pclHorse->siHorseUnique == 0 ) {
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_SELL_NOTHAVE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	// �ŷ��� ������ ���ΰ� //KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.   //KHY - 0911 - ȣ���� �߰�.
	// PCK : ��Ÿ�߰� (08.03.06)
	// PCK : �̺�Ʈ�� ȣ���� �߰� (08.04.01)
	// PCK : �ڳ��� �߰� (08.06.12)
	// PCK : ��ȣ �߰� (08.08.14)
	// PCK : ������� �߰� (08.09.02)
	// PCK : ����ġ �߰� (08.12.10)
	// ü��� �鸶 : �ռ���-2009.03.17
	// PCK : ������Ʈ �߰�(09.07.30)
	switch ( pclHorse->siHorseUnique )
	{
		case HORSEUNIQUE_WOLF:
		case HORSEUNIQUE_FOAL:
		case HORSEUNIQUE_TIGER:
		case HORSEUNIQUE_CAMEL:
		case HORSEUNIQUE_TIGER2:
		case HORSEUNIQUE_ELEPHANT:
		case HORSEUNIQUE_WHITETIGER:
		case HORSEUNIQUE_MOTORCYCLE:
		case HORSEUNIQUE_FIREHATCH:
		case HORSEUNIQUE_WHITE_TEST:
		case HORSEUNIQUE_BAPHOMET:
		case HORSEUNIQUE_GRAYWOLF:
		case HORSEUNIQUE_SASURI:
			{
				SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_SELL_NOTHAVE,  0, 0, pclCM->CR[id]->GetCharUnique());
				return;        
			}
			break;

	}	// switch ( pclHorse->siHorseUnique )  ����

	// �κ��丮�� ����� �ֳ� 
	if( pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() == TRUE ) {
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_SELL_NOTEMPTYINVEN,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}


	pclCM->CR[ id ]->UnrideHorse();
	((cltCharServer*)pclCM->CR[ id ])->SendNeighbourMyHorseStatus( pclCM->CR[ id ]->pclCI->clHorseInfo.siCurrentShowHorse);

	
	cltHorseOrder clOrder;

	clOrder.siPersonID = personid;
	clOrder.siPrice = price;
	clOrder.clDate.Set( &pclTime->clDate );
	clOrder.clHorse.Set( pclHorse );

	sDBRequest_HorseMarketOrderSell sendMsg( id, villageunique, pclinfo->siHorseIndex, &clOrder, tax );
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	pclDelMoneyStatistics->Add(DELMONEY_TAX, tax);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_BUYHORSE(cltMsg* pclMsg, SI32 id )
{
	
	cltGameMsgRequest_HorseMarketBuyHorse *pclinfo = (cltGameMsgRequest_HorseMarketBuyHorse *)pclMsg->cData;

	GMONEY price = 0;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// Person�� ��ġ�� ������ VillageUnique�� Ȯ���Ѵ�
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;


	if( pclCM->CR[ id ]->pclCI->clIP.GetLevel() < MIN_LEVEL_FOR_HORSE ) return;

	// ���� ������ ���� �ִ°� 
	//if( pclHorse->siHorseUnique != 0 ) {
	SI16 index = pclCM->CR[id]->pclCI->clHorseInfo.FindEmptyHorseIndex();

	if(index < 0 ) {// ���� ������ ������ ����. 
		SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_BUY_HAVEANOTHER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}


	int count = 0;
	for( int i = 0; i < MAX_HORSEMARKET_ORDER_NUMBER; ++i ) {
		if( pclHorseMarketManager->pclHorseOrder[ i ].clHorse.siHorseUnique ) {
			++count;

			if( pclHorseMarketManager->pclHorseOrder[ i ].siIndex == pclinfo->siOrderIndex ) {

				if( pclHorseMarketManager->pclHorseOrder[ i ].siPersonID == personid ) {
					SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_BUY_NOTSELF,  0, 0, pclCM->CR[id]->GetCharUnique());
					return;
				}

				if( pclHorseMarketManager->pclHorseOrder[ i ].siPersonID != pclinfo->siSellerPersonID ) {
					SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_BUY,  0, 0, pclCM->CR[id]->GetCharUnique());
					return;
				}

				price = pclHorseMarketManager->pclHorseOrder[ i ].siPrice;

				sDBRequest_HorseMarketBuyHorse sendMsg( id, personid, index, villageunique, pclinfo->siOrderIndex, price );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
				return;
			}
		}

		if( count >= pclHorseMarketManager->siTotalOrderNumber ) break;
	}

	SendServerResponseMsg( RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_BUY,  0, 0, pclCM->CR[id]->GetCharUnique());
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEMARKET_SETFEE(cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_HorseMarketSetFee *pclinfo = (cltGameMsgRequest_HorseMarketSetFee *)pclMsg->cData;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;
	
	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = &pclinfo->clFee;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;
	
	//----------------------------------
	// ��û�ڰ� �纹��������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_HORSEMARKET, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_HORSEMARKET, SRVAL_HORSEMARKET_FAIL_SETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	sDBRequest_HorseMarketSetFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

