#include "Char\CharManager\CharManager.h"

#include "..\Common\SystemNPC\TradeMerchantNPC\TradeMerchantNPC.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Map\Map.h"
#include "../Common/Char/KindInfo/kindinfo.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-TradeMerchant.h"

#include "../../CommonLogic/Msg/MsgType-TradeMerchant.h"
#include "../../CommonLogic/MsgRval-Define.h"

#include "../Minister/MinisterBase.h"
#include "../Minister/Minister-Izo.h"
#include "../Minister/MinisterMgr.h"


// ���� ������ ���� �����ϴ� ������ ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYINFO(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuyInfo* pclinfo = (cltGameMsgRequest_TradeMerchantBuyInfo*)pclMsg->cData;

	if ( pclinfo->siNPCCharUnique < 1 || pclinfo->siNPCKind < 1 )
	{
		return;
	}

	SI32 NPCID = pclCM->GetIDFromCharUnique( pclinfo->siNPCCharUnique );

	if ( NPCID < 1 || pclCM->IsValidID( NPCID ) == FALSE )
	{
		return;
	}

	if ( pclCM->CR[NPCID]->GetKind() != pclinfo->siNPCKind )
	{
		return;
	}

	CTradeMerchantNPC *pTradeMerchantNPC = pclTradeMerchantNPCMgr->GetTradeMerchantNPCPtr( pclinfo->siNPCKind );
	
	if ( pTradeMerchantNPC == NULL )
	{
		return;
	}

	GetLocalTime(&sTime);
	if ( sTime.wHour < TRADEMERCHATNPC_BUY_START_TIME || sTime.wHour >= TRADEMERCHATNPC_BUY_END_TIME )
	{
		SendServerResponseMsg(0, SRVAL_TRADEMERCHANT_NOT_BUY_TIME,  0, 0, pclCM->CR[id]->GetCharUnique());
		// ���� �ð��� �ƴ�
		return;
	}

	// ���� �غ���� �ʾ���
	if ( ! pTradeMerchantNPC->m_bTradeMerchantSet )
	{
		SendServerResponseMsg(0, SRVAL_TRADEMERCHANT_PREPARE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	cltGameMsgResponse_TradeMerchantBuyInfo clGameMsgResponseTradeMerchantBuyInfo( pTradeMerchantNPC );
	cltMsg clMsg( GAMEMSG_RESPONSE_TRADEMERCHANTBUYINFO,  sizeof( clGameMsgResponseTradeMerchantBuyInfo ), (BYTE*)&clGameMsgResponseTradeMerchantBuyInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���� ���ο��� ������ ��ǰ�� �Ǹ�
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMFROMPERSON(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}
	
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuyItemFromPerson* pclinfo = (cltGameMsgRequest_TradeMerchantBuyItemFromPerson*)pclMsg->cData;

	if( pclinfo->siNPCKind < 1 )
	{
		return;
	}

	CTradeMerchantNPC *pTradeMerchantNPC = pclTradeMerchantNPCMgr->GetTradeMerchantNPCPtr( pclinfo->siNPCKind );

	// �Ƿι��� �ý��� ����
	pTradeMerchantNPC->m_siBuyItemPrice = ((cltCharServer*)pclCM->CR[id])->CalcTiredPoint( pTradeMerchantNPC->m_siBuyItemPrice );
	
	if ( pTradeMerchantNPC == NULL )
	{
		return;
	}

	GetLocalTime(&sTime);
	if ( sTime.wHour < TRADEMERCHATNPC_BUY_START_TIME || sTime.wHour >= TRADEMERCHATNPC_BUY_END_TIME )
	{
		// ���� �ð��� �ƴ�
		return;
	}

	// ���� �غ���� �ʾ���
	if ( ! pTradeMerchantNPC->m_bTradeMerchantSet )
	{
		return;
	}

	// NPC �� �������� ������ ������ ���� �Ǵ���..
	if ( pTradeMerchantNPC->m_siBuyTotalMoney < pTradeMerchantNPC->m_siBuyItemPrice )
	{
		SendServerResponseMsg(0, SRVAL_TRADEMERCHANT_MONEY_INSUFFICIENTY,  0, 0, pclCM->CR[id]->GetCharUnique());
		
		return;
	}


	// ������ ��ġ Ȯ��
	if ( pclinfo->siItemPos < PERSONITEM_INV0 || pclinfo->siItemPos >= MAX_ITEM_PER_PERSON )
	{
		return;
	}

	// ������ ��ġ Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique < 1 )
	{
		return;
	}

	// ������ ��ġ Ȯ��
	if ( ! pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].IsSame( &pclinfo->clItem, true ) )
	{
		return;
	}

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� �Ǹ��� �� ����.
	//------------------------------------------------------
	if( pclinfo->clItem.clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
		return;

	// NPC �� �������� �������� �´��� Ȯ��
	if ( pTradeMerchantNPC->m_siBuyItemUnique != pclinfo->clItem.siUnique )
	{
		return;
	}

	// ��ø ������ Ȯ�� - ��ø �������� �ȵ�
	if ( pclinfo->clItem.CanPile( pclItemManager ) )
	{
		return;
	}
	
	CMinisterIzo* pclMinister = (CMinisterIzo*)pclMinisterMgr->GetMinister( MINISTER_IZO );
	if ( pclMinister == NULL )
	{
		return;
	}

	GMONEY tradetax = ( pTradeMerchantNPC->m_siBuyItemPrice / 100 ) * pclMinister->m_siTradeTax ;
	GMONEY buyitemprice = pTradeMerchantNPC->m_siBuyItemPrice - tradetax ;

	sDBRequest_TradeMerchantBuyItemFromPerson clMsg( id, PersonID, pclinfo->siNPCKind, pclinfo->siItemPos, &pclinfo->clItem, buyitemprice,tradetax);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_NPCBUYITEM, buyitemprice);
}

// ������ ���� �����ϴ� ���� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTHORSEBUYINFO(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}
	
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantHorseBuyInfo * pclinfo = (cltGameMsgRequest_TradeMerchantHorseBuyInfo *)pclMsg->cData;

	// ������ �� �������� Ȯ��
	if( pclinfo->siMerchantKind != GetUniqueFromHash(TEXT("KIND_MERCHANTHORSE")) )
	{
		return;
	}

	// �� ���� Ȯ��
	if ( ! pclCM->CR[id]->HaveHorse() )
	{
		return;
	}

	cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();

	if( pclHorse == NULL ||	pclHorse->siHorseUnique <= 0)
		return;

	// �� Ÿ�� �ִ��� Ȯ��
	if ( pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true )
	{
		return;
	}

	// �ŷ� ������ ������ ���� üũ
	SI32 CurTotalStat = pclHorse->siMoveSpeed +
						pclHorse->siStr +
						pclHorse->siDex +
						pclHorse->siMag +
						pclHorse->siStatusBonus;

	// Total Stat �� 9000 �̻� ����
	if ( CurTotalStat < 9000 )
	{
		return;
	}

	SI32 datevary = pclTime->clDate.GetDateVary();

	//SI32 FullLife	= pclHorseManager->GetFullLife(pclCM->CR[id]->pclCI->clHorseInfo.clHorse.siHorseUnique);
	//SI32 Life		= pclHorseManager->GetLife(&pclCM->CR[id]->pclCI->clHorseInfo.clHorse,  datevary );
	// �������� ���� ��. 
	//SI32 leftage	= max(0, (FullLife - Life) / 360);
	
	// ���� ������ ���� ���� �ʾ���.
	if ( siHorseCurrentPrice < 1 )
	{
		return;
	}

	GMONEY HorsePrice = 0;
	switch ( pclHorse->siHorseUnique )
	{
	case 1:
		//HorsePrice = siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage;
		HorsePrice = siHorseCurrentPrice;
		break;
	case 2:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.25;
		HorsePrice = siHorseCurrentPrice * 13 / 10;
		break;
	case 3:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.50;
		HorsePrice = siHorseCurrentPrice * 16 / 10;
		break;
	case 4:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 5:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 6:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 7:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 8:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 9:
		//HorsePrice = ( siHorseCurrentPrice - siHorseCurrentPrice * 0.05 * leftage ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 22 / 10;
		break;
	default:
		return;
	}

	cltGameMsgResponse_TradeMerchantHorseBuyInfo clGameMsgResponse_TradeMerchantHorseBuyInfo( pclHorse->siHorseUnique, HorsePrice );
	cltMsg clMsg( GAMEMSG_RESPONSE_TRADEMERCHANTHORSEBUYINFO,  sizeof( clGameMsgResponse_TradeMerchantHorseBuyInfo ), (BYTE*)&clGameMsgResponse_TradeMerchantHorseBuyInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

// ������ ���� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYHORSEFROMPERSON(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}
	
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuyHorseFromPerson * pclinfo = (cltGameMsgRequest_TradeMerchantBuyHorseFromPerson*)pclMsg->cData;

	// �� ���� Ȯ��
	if ( ! pclCM->CR[id]->HaveHorse() )
	{
		return;
	}

	// �� Ÿ�� �ִ��� Ȯ��
	if ( pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true )
	{
		return;
	}

	// ���� ������ �����ϰ� ����.
	if ( pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() )
	{
		return;
	}

	cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
	
	if( pclHorse == NULL ||	pclHorse->siHorseUnique <= 0)
		return;

	// �ŷ� ������ ������ ���� üũ
	SI32 CurTotalStat = pclHorse->siMoveSpeed +
						pclHorse->siStr +
						pclHorse->siDex +
						pclHorse->siMag +
						pclHorse->siStatusBonus;

	// Total Stat �� 9000 �̻� ���� ( 90.00 )
	if ( CurTotalStat < 9000 )
	{
		return;
	}

	SI32 datevary = pclTime->clDate.GetDateVary();

	//SI32 Life = pclHorseManager->GetLife( &pclCM->CR[id]->pclCI->clHorseInfo.clHorse, datevary );
	
	// ���� ������ ���� ���� �ʾ���.
	if ( siHorseCurrentPrice < 1 )
	{
		return;
	}

	GMONEY HorsePrice = 0;
	switch ( pclHorse->siHorseUnique )
	{
	case 1:
		//HorsePrice = siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365;
		HorsePrice = siHorseCurrentPrice;
		break;
	case 2:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.25;
		HorsePrice = siHorseCurrentPrice * 13 / 10;
		break;
	case 3:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.50;
		HorsePrice = siHorseCurrentPrice * 16 / 10;
		break;
	case 4:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 5:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 6:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 7:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 8:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 19 / 10;
		break;
	case 9:
		//HorsePrice = ( siHorseCurrentPrice + siHorseCurrentPrice * 0.05 * ( Life - MAX_HORSE_LIFE ) / 365 ) * 1.75;
		HorsePrice = siHorseCurrentPrice * 22 / 10;
		break;
	default:
		return;
	}

	sDBRequest_TradeMerchantBuyHorseFromPerson clMsg( id, PersonID, GetUniqueFromHash(TEXT("KIND_MERCHANTHORSE")), pclCM->CR[id]->pclCI->clHorseInfo.siCurrentShowHorse, HorsePrice );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

// ������ ������ �����ϴ� ������ ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEMINFO(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}
	
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuyItemInfo * pclinfo = (cltGameMsgRequest_TradeMerchantBuyItemInfo*)pclMsg->cData;

	if ( pclinfo->siItemPos < 1 || pclinfo->siItemPos>= MAX_ITEM_PER_PERSON )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique < 1 )
	{
		return;
	}

	// ��ǰ �Ǵ� ȣǰ���� Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 ||
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
	}
	else
	{
		return;
	}

	// �������� �ü��� ���Ѵ�. 
	cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice( pclItemManager, pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique );
	
	if ( pclprice == NULL )
	{
		return;
	}
	
	GMONEY Price	= 0;
	
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 )
	{
		Price = pclprice->siPrice * 10;			// ������ �ü��� 10��( ��ǰ )
	}
	else if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
		Price = pclprice->siPrice * 5;			// ������ �ü��� 5��( ȣǰ )
	}
	else if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
		Price = pclprice->siPrice * 2;			// ������ �ü��� 2��( ȣǰ )
	}

	cltGameMsgResponse_TradeMerchantBuyItemInfo clGameMsgResponse_TradeMerchantBuyItemInfo( GetUniqueFromHash(TEXT("KIND_MERCHANTPOTTER")), pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique, Price );
	cltMsg clMsg( GAMEMSG_RESPONSE_TRADEMERCHANTBUYITEMINFO,  sizeof( clGameMsgResponse_TradeMerchantBuyItemInfo ), (BYTE*)&clGameMsgResponse_TradeMerchantBuyItemInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
	return;
}

// ������ ������ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_TRADEMERCHANTBUYITEM(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}
	
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )
	{
		return;
	}

	cltGameMsgRequest_TradeMerchantBuyItem* pclinfo = (cltGameMsgRequest_TradeMerchantBuyItem*)pclMsg->cData;

	if ( pclinfo->siItemPos < 1 || pclinfo->siItemPos>= MAX_ITEM_PER_PERSON )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique < 1 )
	{
		return;
	}

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� �Ǹ��� �� ����.
	//------------------------------------------------------
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
		return;
	
	// ��ǰ �Ǵ� ȣǰ���� Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 ||
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
	}
	else
	{
		return;
	}
	
	// �������� �ü��� ���Ѵ�. 
	cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice( pclItemManager, pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique );
	
	if ( pclprice == NULL )
	{
		return;
	}
	
	GMONEY Price	= 0;
	
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 )
	{
		Price = pclprice->siPrice * 10;			// ������ �ü��� 10��( ��ǰ )
	}
	else if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
		Price = pclprice->siPrice * 5;			// ������ �ü��� 3��( ȣǰ )
	}
	//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
	else if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
	{
		Price = pclprice->siPrice * 2;			// ������ �ü��� 2��( �ű� )
	}

	// �۷ι��� �ƴϸ� ���� ������ �Ǹ� �׼��� ����.
	if(!pclClient->IsCountrySwitch(Switch_SellToForeignMerchant))
	{	
		if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1  )
		{
			Price /= 5;			// ������ �ü��� 5�踦 Ǯ�� 3��( ȣǰ )
			Price *= 3;
		}
		//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
		else if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5  )
		{
			Price /= 2;			// ������ �ü��� 2�踦 Ǭ��.( �ű� )
		}
	}
	
	sDBRequest_TradeMerchantBuyItem clMsg( id, PersonID, pclinfo->siMerchantKind, pclinfo->siItemPos, &pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ], Price );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
	pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_NPCBUYITEM, Price);
	return;
}

