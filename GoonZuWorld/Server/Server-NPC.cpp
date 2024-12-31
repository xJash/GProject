//---------------------------------
// 2003/8/19 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Common\SystemNPC\ForeignMerchantNPC\ForeignMerchantNPC.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

#include "../CommonLogic/MsgRval-Define.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Market.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMSG-ForeignMerchantNPC.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../../DBManager/GameDBManager_World/dbMsg-Person.h"

#include "..\Client\Interface\NPC1\NPCTradeBaseInfo.h"
//#include "..\Client\Interface\ForeignMerchant\ForeignMerchantBaseInfo.h"
#include "..\CommonLogic\Msg\MsgType-NPC.h"
#include "..\CommonLogic\MsgType-Item.h"

#include "Statistics/Statistics.h"

#include "../Common/SystemNpc/SystemNPC.h"

#include "../common/VoteMgr/VoteMgr.h"

#include "../Server/ServerReward/ServerReward.h"
#include "../../Common/GameMaster/GameMaster.h"


// NPC���� ������ �Ǹ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SELLNPC(cltMsg* pclMsg, SI32 id)
{
	stNPCTradeData* pclinfo	=  (stNPCTradeData*)pclMsg->cData;

	SI32 NPCCharUnique = pclinfo->siNPCCharUnique;
	if ( NPCCharUnique < 1 )
	{
		return;
	}

	SI32 NPCID = pclCM->GetIDFromCharUnique( NPCCharUnique );

	if ( NPCID < 1 )
	{
		return;
	}
	
	if ( pclCM->IsValidID( NPCID ) == false )
	{
		return;
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

	if(pclinfo->si32lParam < 0 || pclinfo->si32lParam >= MAX_ITEM_PER_PERSON)return ;

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->si32lParam	)
			{
				// ���� �������� ������ �����ϴ��� üũ 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}

			// �ͼ����� ���λ���
			if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->si32lParam	)
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

	cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->si32lParam];

	//cyj źȯ�� �������� NPC���� �ȼ� ����
	if ( pclfromitem->IsBulletItem() )
	{
		// �ŷ� ���и� �˷��ش�. 
		cltMsg clMsg( GAMEMSG_RESPONSE_SELLNPC, SYSTEMNPC_FAIL_SELL_BULLETITEM );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		return;
	}

	//���� 
	if ( pclItemManager->IsItemInfoAtb( pclfromitem->siUnique, ITEMINFOATB_TYPE_QUESTITEM) &&
		 pclchar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		// �ŷ� ���и� �˷��ش�. 
		cltMsg clMsg( GAMEMSG_RESPONSE_SELLNPC, SYSTEMNPC_FAIL_SELL_QUESTITEM );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return ;
	}

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� �Ǹ��� �� ����.
	//------------------------------------------------------
	if( pclfromitem->clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )	
	{
		return;
	}

	// ITEMINFOATB_NOTSELL�� NPC���� �� �Ǵ�
	if( pclItemManager->IsItemInfoAtb( pclfromitem->siUnique, ITEMINFOATB_NOTSELL ) )
	{
		// �ŷ� ���и� �˷��ش�. 
		cltMsg clMsg( GAMEMSG_RESPONSE_SELLNPC, SYSTEMNPC_FAIL_SELL_ITEMMALLITEM );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return ;
	}

	//---------------------------------------------------------------------------------
	// Ŭ���̾�Ʈ�� ������ �����۰� �������� �˰� �ִ� �������� ���� ������ Ȯ���Ѵ�. 
	//---------------------------------------------------------------------------------
	cltItem clitem1;
	clitem1.Set(pclfromitem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(&pclinfo->clItem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)
	{
		return ;
	}

	//------------------------------------------------
	// �������� NPC���� �Ǹ��ϴ� ������ ���Ѵ�. 
	//------------------------------------------------
	GMONEY price = pclItemManager->pclItemPrice->GetPriceSellToNPC(pclItemManager, pclinfo->clItem.siUnique);

	// �Ƿι��� �ý��� ����
	price = ((cltCharServer*)pclCM->CR[id])->CalcTiredPoint( price );

	SI32 VillageUnique = pclCM->CR[NPCID]->GetCurrentVillageUnique();
	sDBRequest_SellNPC clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->si32lParam, &pclinfo->clItem, price, VillageUnique, pclCM->CR[NPCID]->GetKind());
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			
	// �Ǹ� �ݾ��� �����Ѵ�. 
	cltMoney clmoney;
	clmoney.Set(pclinfo->clItem.siItemNum * price);
	clCurrencyInfo.clInputMoney_NPC.Increase(&clmoney);

	pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_SELLNPC, price);
}

// NPC���Լ� ������ ����. 
void cltServer::DoMsg_GAMEMSG_REQUEST_BUYNPC(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	stNPCTradeData* pclinfo	=  (stNPCTradeData*)pclMsg->cData;

	if(pclinfo->si32lParam < 0 || pclinfo->si32lParam >= MAX_NPC_ITEM_NUMBER)return ;
	
	if ( pclinfo->siNPCCharUnique < 1 )
	{
		return;
	}

	SI32 NPCID = pclCM->GetIDFromCharUnique( pclinfo->siNPCCharUnique );
	if ( NPCID < 1 || pclCM->IsValidID(NPCID) == FALSE )
	{
		return;
	}

	SI32 NPCKind = pclCM->CR[NPCID]->GetKind();

	cltNPCMerchantInfo *pNPCMerchantInfo = NULL;

	for ( SI16 k = 0; k < MAX_NPC_MERCHANT_NUMBER; ++k )
	{
		if ( pclNPCItemInfo->clNPCMerchantInfo[ k ].siNPCKind == NPCKind )
		{
			pNPCMerchantInfo = &pclNPCItemInfo->clNPCMerchantInfo[ k ];
			break;
		}
	}

	if ( pNPCMerchantInfo == NULL )
	{
		return;
	}

	cltItem* pclfromitem = &pNPCMerchantInfo->clItemInfo[pclinfo->si32lParam].clItem;

	// ������ ��ȿ�ϸ� ����. 
	if(pclinfo->clItem.siItemNum <= 0)return ;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// ���ſ� ������� �����Ⱓ���ȸ� �Ǹ��Ѵ�
	if ( pclfromitem->siUnique == ITEMUNIQUE(24080) )
	{
		if ( false == bVoteCampaign )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_DONOTBUY_ELECTIONSTUMPITEM, 0, 0, id );
			return;
		}
	}

	// Ŭ���̾�Ʈ�� ������ �����۰� �������� �˰� �ִ� �������� ���� ������ Ȯ���Ѵ�. 
	cltItem clitem1;
	clitem1.Set(pclfromitem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(&pclinfo->clItem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)
	{
		return ;
	}

	// ��ø�� �ȵǴ� �������� ��쿡�� �������� �ֹ��� ���͵� �Ѱ��� ������ �� �ִ�. 
	if(pclfromitem->CanPile(pclItemManager) == false)
	{
		pclinfo->clItem.SetItemNum(1);
	}
	

	//cyj �������� 1000������ ��� �ֵ��� ����
	SI32 MAX_BUY_NUMBER = 300;
	if (pNPCMerchantInfo->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_WAITINGWOMAN")) )
	{
		MAX_BUY_NUMBER = 1000;
	}
	// [����] �߷�Ÿ�� ���� �̺�Ʈ - �Ǹ��� �� ���
	else if(pNPCMerchantInfo->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHOCOLATE")) )
	{
		pclinfo->clItem.SetItemNum(1);
	}
	
	// 300 �� ������ ���� ����( ���� ���� �ʰ� ������... )
	if ( pclinfo->clItem.siItemNum > MAX_BUY_NUMBER )
	{
		return;
	}

	// ������ ���ؿ´�. 
	GMONEY price = pNPCMerchantInfo->clItemInfo[pclinfo->si32lParam].siPrice;
	
	// ������ ����
	if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < price * pclinfo->clItem.siItemNum )
	{
		// �ŷ� ���и� �˷��ش�. 
		cltMsg clMsg( GAMEMSG_RESPONSE_BUYNPC, SYSTEMNPC_FAIL_BUY_REASPON_MONEY_INSUFFICIENTY );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		return;
	}

	// [����] �븸���� 1�ֳ� ��� ������ �к��� Ǯ���� ���´�
	if ( ITEMUNIQUE(7615) == pclinfo->clItem.siUnique )
	{
		if ( false == pclinfo->clItem.CancellationSealingUp(sTime) )
		{
			return;
		}
	}

	SI16 itempos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclinfo->clItem, &itempos, &cltoitem, &rtnvalue) == TRUE)
	{
		// [����] �߷�Ÿ�� ���� �̺�Ʈ - �Ǹ��� �� ���
		if(pNPCMerchantInfo->siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHOCOLATE")) )
		{
			CValentineEventServerMgr* pclValentineEventServerMgr = (CValentineEventServerMgr*)m_pclValentineEventMgr;
			if( NULL == pclValentineEventServerMgr)
			{
				return;
			}
			else
			{
				if(pclValentineEventServerMgr->IsHolding())
				{
					if(!pclValentineEventServerMgr->BuyPresentToStore(pclinfo->siNPCCharUnique, pclinfo->clItem.siUnique))
					{
						cltMsg clMsg( GAMEMSG_RESPONSE_BUYNPC, SYSTEMNPC_FAIL_BUY_SOLDOUT );
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

						return;
					}
				}
			}
		}

		sDBRequest_BuyNPC clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), &pclinfo->clItem, pclinfo->clItem.CanPile(pclItemManager), price, itempos, NPCKind);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		// ���� �ݾ��� �����Ѵ�. 
		cltMoney clmoney;
		clmoney.Set(pclinfo->clItem.siItemNum * price);
		clCurrencyInfo.clOutputMoney_NPC.Increase(&clmoney);

        pclDelMoneyStatistics->Add(DELMONEY_BUYNPC, pclinfo->clItem.siItemNum * price);
	}
	else
	{
		if(pclchar)
		{
			SendServerResponseMsg(0, SRVAL_NPC_MARKET_SELL_FAIL,  0, 0, pclchar->GetCharUnique());
		}
		
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NPCSELLITEMINFO(cltMsg* pclMsg, SI32 id)
{
	if ( pclItemManager->clItemStatistic.siNPCPriceRate == 0 )
	{
		return;
	}
	
	cltGameMsgRequest_NPCSellItemInfo* pclinfo = (cltGameMsgRequest_NPCSellItemInfo*)pclMsg->cData;

	if ( pclinfo->siNPCKind < 1 )
	{
		return;
	}
	
	cltNPCMerchantInfo *pNPCMerchantInfo = NULL;

	for ( SI16 k = 0; k < MAX_NPC_MERCHANT_NUMBER; ++k )
	{
		if ( pclNPCItemInfo->clNPCMerchantInfo[ k ].siNPCKind == pclinfo->siNPCKind )
		{
			pNPCMerchantInfo = &pclNPCItemInfo->clNPCMerchantInfo[ k ];
			break;
		}
	}

	if ( pNPCMerchantInfo == NULL )
	{
		return;
	}

	cltGameMsgResponse_NPCSellItemInfo clNPCSellItemInfo( pclinfo->siNPCKind, &pNPCMerchantInfo->clItemInfo[0] );
		
	cltMsg clMsg( GAMEMSG_RESPONSE_NPCSELLITEMINFO, sizeof( clNPCSellItemInfo ), (BYTE*)&clNPCSellItemInfo );

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SellToForeignMerchant* pclinfo = (cltGameMsgRequest_SellToForeignMerchant*)pclMsg->cData;
	
	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	SI32 NPCCharUnique = pclinfo->siNPCCharUnique;
	if ( NPCCharUnique < 1 )
	{
		return;
	}

	SI32 NPCID = pclCM->GetIDFromCharUnique( NPCCharUnique );

	if ( NPCID < 1 )
	{
		return;
	}
	
	if ( pclCM->IsValidID( NPCID ) == false )
	{
		return;
	}

	if ( pclinfo->siSellItemUnique < 1 )
	{
		return;
	}

	// �ŷ��� �������� ������ ��ȿ���� Ȯ��. 
	if ( pclinfo->uiSellItemNum < 1 )
	{
		return;
	}

	// 1000 �� ���� ����
	if ( pclinfo->uiSellItemNum > 1000 )
	{
		return;
	}
	
	// ����, NPC �߿� �ִ� NPC ���� üũ.
	if( pclinfo->siForeignMerchantKind < FOREIGNMERCHANT_HELMET || pclinfo->siForeignMerchantKind >= FOREIGNMERCHANT_END )
	{
		return;
	}

	//  �κ��丮 ���� �ִ� ������ ��ġ���� Ȯ��
	if( pclinfo->uiSelectedIndex < PERSONITEM_INV0 || pclinfo->uiSelectedIndex >= MAX_ITEM_PER_PERSON )
	{
		return ;
	}

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->uiSelectedIndex	)
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
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->uiSelectedIndex	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}

	// ���� NPC�� �����ϴ� ������ Ŭ���̾�Ʈ���� �� ������ �մ��ϴ��� Ȯ��. 
	// ���� �������� NPC �� ������ ���õ� ������ �޾ƿ´�.
	stForeignMerchantNPCInfo* pclForeignMerchantNPCInfo = pclForeignMerchantNPCMgr->GetForeignMerchantNPCInfo( pclinfo->siForeignMerchantKind );
	
	if ( pclForeignMerchantNPCInfo == NULL )
	{
		return;
	}

	CForeignMerchantNPC *pclForeignMerchantNPC = pclForeignMerchantNPCMgr->GetForeignMerchantNPC( pclinfo->siForeignMerchantKind );

	if ( pclForeignMerchantNPC == NULL )
	{
		return;
	}	

	// ������ ������� �κ��� �ش�  ��ǰ�� �ִ��� Ȯ��(������ Ȯ��.)
	cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->uiSelectedIndex ];

	if( pclfromitem == NULL )
	{
		return;
	}

	// ������ ����ũ �� ��
	// ���� ������ �κ��丮�� �ִ� ������ ������ Ŭ���̾�Ʈ���� ������ ������ ������ ������ ��
	// �Ǹ��ҷ��� ������ 1���� ������ ������... �� ���� �� ���� ������... Ȥ�ó�...
	if( pclfromitem->siUnique != pclinfo->siSellItemUnique ) 
	{
		return;
	}
	
	// ������ �ȷ��� ������ ���� Ȯ��
	if ( pclfromitem->siItemNum < pclinfo->uiSellItemNum )
	{
		return;
	}

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� �Ǹ��� �� ����.
	//------------------------------------------------------
	if( pclfromitem->clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )	return;

	SI32 remainDay = 0;
	
	BOOL rVal = GetItemUseAbleDay( pclfromitem, &remainDay );
	
	if (remainDay < 0 && rVal == TRUE)
		return;

	// ������ ��� ��ǰ�߿� �ִ� ������ �װ��� ������ �Ĵ� ���ǰ� ���� ������ Ȯ��
	SI32 siBuyItemIndex = -1;
	for ( SI32 i = 0; i < pclForeignMerchantNPCInfo->siBuyItemListCount; ++i )
	{
		if ( pclForeignMerchantNPCInfo->siBuyItemUniqueList[ i ] == pclinfo->siSellItemUnique )
		{
			siBuyItemIndex = i;
			break;
		}
	}

	// �����ϴ� ��ǰ�� ��ġ���� ����.
	if ( siBuyItemIndex == -1)
	{
		return;
	}

	// ��ø�� �ȵǴ� �������� ��쿡�� �������� �ֹ��� ���͵� �Ѱ��� ������
	if(pclfromitem->CanPile(pclItemManager) == false)
	{
		pclinfo->uiSellItemNum = 1;
	}
	
	pclForeignMerchantNPC->RefreshPrice();

	//-------------------------------
	// �ü��� ������Ʈ �Ѵ�. 
	//------------------------------
	GMONEY price = 0;

	// ��ǰ, ȣǰ, �ű� �϶��� �������� ���� �ü��� ����´�
	if ( (pclinfo->uiRareInfo == RARELEVEL_2) || (pclinfo->uiRareInfo == RARELEVEL_1) || (pclinfo->uiRareInfo == RARELEVEL_5) )
	{
		price = (pclItemManager->GetCurrentPrice( pclinfo->siSellItemUnique ))->siPrice ;
	}
	// �Ϲ� �������� ��� �ü��� 50%~75��ŭ�� ������ ����´�
	else
	{
		price = pclForeignMerchantNPCInfo->siBuyItemPriceList[ siBuyItemIndex ];
	}
	
	
	if ( pclinfo->uiRareInfo == RARELEVEL_2 )
	{
		price *=  10;			// ������ �ü��� 10��( ��ǰ )
	}
	else if ( pclinfo->uiRareInfo == RARELEVEL_1 )
	{
		price *=  5;			// ������ �ü��� 3��( ȣǰ )
	}
	//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
	else if ( pclinfo->uiRareInfo == RARELEVEL_5 )
	{
		price *= 2;			// ������ �ü��� 2��( �ű� )
	}

	// �۷ι��� �ƴϸ� ������ ������ �Ǹ� ���ݷ� ����.
	if(!pclClient->IsCountrySwitch(Switch_SellToForeignMerchant))
	{	
		if ( pclinfo->uiRareInfo == RARELEVEL_1 )
		{
			price /= 5;			// ������ �ü��� 5�踦 Ǯ�� 3��( ȣǰ )
			price *= 3;
		}
		//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
		else if ( pclinfo->uiRareInfo == RARELEVEL_5 )
		{
			price /= 2;			// ������ �ü��� 2�踦 Ǭ��.( �ű� )
		}
	}

	// DB�� ��ǰ�� �ȶ�� ��û..
	cltItem clItem;
	clItem.Set(pclfromitem);
	clItem.SetItemNum(pclinfo->uiSellItemNum);
	if (pclfromitem->IsSealingUp(pclItemManager) == false)
	{
		if( rVal == TRUE) // �Ⱓ�� �������̶��
		{
			switch (remainDay)
			{
			case 2 :
				price = price * 5 / 10;
				break;
			case 1 :
				price = price * 3 / 10;
				break;
			case 0 :
				{
					if(clItem.uiDateUseDay != 0)
						price = price * 1 / 10;
				}
				break;
			}
		}
	}

	// ������ ���� 
	SI16 siDurabilityPenalty = 0;

	if ( IsCountrySwitch(Switch_NewDurability) )
	{
		REAL32 fGetDurabilityPenalty = pclfromitem->GetDurabilityPenlty( pclItemManager );

		price				= (GMONEY)((REAL64)price * (REAL64)fGetDurabilityPenalty);
		siDurabilityPenalty	= (SI16)(fGetDurabilityPenalty * 100.0f);
	}

	//KHY - 0530 ���� ���� ��������.
	if(gForeignMerchantBuyLimit > 0) // ���������� �����Ǿ� �ִٸ�.
	{
		// �Ϸ� 6�� ���������� �Ѵ�. ���� �� �ܰ谡 �ִµ� ������ 60���̸� 1ȸ���� 10��, 2ȸ���� 20�� ���ѱݾ��� ����Ǵ� 
		// ����̴�. �׸��� �Ǹ��ϴ� �������� �ݾ��� ���ѱݾ��� �ʰ��ϴ� ���� 1 ~ 5ȸ������ ���ѵȴ�.
		// ������ ���� ȸ���� ������ �ֱ� �����̴�. ������ ���Ŵ����ݾ��� �ʱ�ȭ�ϱ� ���� 6ȸ���� ��쿣 �������� ���ݿ� ���� 
		// ������ ���� �ǸŰ� �ǵ��� �ߴ�.
		SI32 siDay	  = pclTime->clDate.GetDay();
		SI32 siSeason = 1;
			 if(  1 <= siDay &&  5 >= siDay ) siSeason = 1;	
		else if(  6 <= siDay && 10 >= siDay ) siSeason = 2;
		else if( 11 <= siDay && 15 >= siDay ) siSeason = 3;
		else if( 16 <= siDay && 20 >= siDay ) siSeason = 4;
		else if( 21 <= siDay && 25 >= siDay ) siSeason = 5;
		else if( 26 <= siDay && 30 >= siDay ) siSeason = 6;

		if((gForeignMerchantBuyLimit / 6) * siSeason <= gForeignMerchantNowMoney + ((6 == siSeason) ? 0 : price) )
		{
			SendServerResponseMsg(0, SRVAL_CANNOTBUYITEM_FOREIGNMERCHANT, 0, 0, id );
			return ;
		}
		else
		{
			// ������ �׼��� �����Ѵ�.
			gForeignMerchantNowMoney = gForeignMerchantNowMoney + price;

			if ( gForeignMerchantNowMoney > gForeignMerchantBuyLimit ) 
			{
				gForeignMerchantNowMoney = gForeignMerchantBuyLimit ;
			}
			//sDBRequest_SetForeignMerchantNowMoney clMsg(pclinfo->siForeignMerchantKind, gForeignMerchantNowMoney);
			sDBRequest_SetForeignMerchantNowMoney clMsg( gForeignMerchantNowMoney);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);		
		}
	}

	if(price > 0)
	{
		pclItemManager->SetCurrentPrice(pclfromitem->siUnique, price, pclinfo->uiSellItemNum);
		
		cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(pclfromitem->siUnique);
		
		if(pclprice)
		{
			const TCHAR* pszItemName = pclClient->pclItemManager->GetName(pclprice->siUnique);
			sDBRequest_SetItemPrice clMsg(pclprice->siUnique, pclprice->siPrice, pclprice->fPrice, pclprice->siItemNum, pszItemName);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 4] // ������ ����.
			//	// param1 == ������ ����ũ. param2 == ����, param3 == ����, param4 == ����, pszParam1 == ������ �̸�.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MARKET, LOGCOMMAND_INDEX_MARKET_ITEMPRICESET, 
			//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									pclprice->siUnique, pclprice->siPrice, pclprice->fPrice, pclprice->siItemNum, 0, (TCHAR*)pszItemName, NULL);
			//}
		}
	}


	// �Ƿι��� �ý��� ����
	price = pclchar->CalcTiredPoint( price );

	SI32 VillageUnique = pclCM->CR[NPCID]->GetCurrentVillageUnique();
	sDBRequest_SellNPC clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->uiSelectedIndex, &clItem, price, VillageUnique, pclCM->CR[NPCID]->GetKind());
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_NPCBUYITEM, price);
	
	// �Ǹ� �ݾ��� �����Ѵ�. 
	cltMoney clmoney;
	clmoney.Set(clItem.siItemNum * price);
	clCurrencyInfo.clInputMoney_NPC.Increase(&clmoney);
	
	pclStatisticsManager->clDailyStatistics.siForeignMerchantBuyGameItemMoney += clmoney.itMoney;

	pclItemManager->AddForeignMerchantItemNum( clItem.siUnique, clItem.siItemNum );

	// ���ο� ��� - ���� ���ο� ���� ��鿩�� ��ǰ�� ��踦 ����.
	NStatistics_Add("Item", clItem.siUnique ,"ForeignMerchant", clItem.siItemNum);
	NStatistics_Add("Item", clItem.siUnique ,"ForeignMerchantPrice", clmoney.itMoney);
	NStatistics_Set("Item", clItem.siUnique, "Name", pclItemManager->GetName(clItem.siUnique));

	// ����Ʈ ������ ������Ʈ �Ѵ�.
	((cltCharServer*)(pclCM->CR[id]))->IncQuestPara(QUEST_CLEAR_COND_SELLTRADER, clItem.siUnique  , clItem.siItemNum );

	//[�߰��� : Ȳ���� 2007. 11. 19 ���� ������ ���� ���� ����.]

	UI16  RareLevelType;
	switch(pclinfo->uiRareInfo)
	{
		case RARELEVEL_1: 	// ȣǰ
		case RARELEVEL_2: 	// ��ǰ	
		case RARELEVEL_3: 	
		case RARELEVEL_4: 	
		case RARELEVEL_5: RareLevelType = pclinfo->uiRareInfo;	break;	// ���ǰ.
		case RARELEVEL_6:								// ��ǰ.(�Ϲݰ� ����.)
		default:		  RareLevelType = 6;	break;  // �Ϲ�ǰ.
	}
	
	// �迭�� ��ȣ. (-1)
	SI32 Index = RareLevelType - 1;
	
	clItemInfo[Index].m_sTime    = sTime;				// ���� �ð�.
	clItemInfo[Index].m_siMoney += clmoney.itMoney;		// �ŷ� �ݾ� ����.
	clItemInfo[Index].m_siCnt++;						// Ƚ�� ����.
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 11. 19 ���� ���ΰ��� �ŷ�����. ��踦 ����...]
		/*
			RareLevelType => 

		
		*/
		// param1 == ���� ������ ������ �ݾ�.
		// param2 == ���� �ŷ� Ƚ��.
		// param3 == ������.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SELL_TO_FOREIGN_MERCHANT, RareLevelType, 
							 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &clItem, 0, 0, 0, 0, 0, 0, 
							 clmoney.itMoney, clItemInfo[Index].m_siCnt, clItemInfo[Index].m_siMoney, 0, 0, 
							 NULL, NULL);
		
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRESELLTOFOREIGNMERCHANT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SellToForeignMerchant* pclinfo = (cltGameMsgRequest_SellToForeignMerchant*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// ������ ������� �κ��� �ش�  ��ǰ�� �ִ��� Ȯ��(������ Ȯ��.)
	cltItem* pclfromitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->uiSelectedIndex ];

    if( pclfromitem == NULL )
	{
		return;
	}

	// ���λ��� �������̸� ���λ����� ��ǰ�� �������̶�� �ȼ� ����.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->uiSelectedIndex	)
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
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->uiSelectedIndex	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}

	stForeignMerchantNPCInfo* pclForeignMerchantNPCInfo = pclForeignMerchantNPCMgr->GetForeignMerchantNPCInfo( pclinfo->siForeignMerchantKind );

	if ( pclForeignMerchantNPCInfo == NULL )
	{
		return;
	}

	CForeignMerchantNPC *pclForeignMerchantNPC = pclForeignMerchantNPCMgr->GetForeignMerchantNPC( pclinfo->siForeignMerchantKind );

	if ( pclForeignMerchantNPC == NULL )
	{
		return;
	}	

	pclForeignMerchantNPC->RefreshPrice();

	// ������ ��� ��ǰ�߿� �ִ� ������ �װ��� ������ �Ĵ� ���ǰ� ���� ������ Ȯ��
	SI32 siBuyItemIndex = -1;
	for ( SI32 i = 0; i < pclForeignMerchantNPCInfo->siBuyItemListCount; ++i )
	{
		if ( pclForeignMerchantNPCInfo->siBuyItemUniqueList[ i ] == pclinfo->siSellItemUnique )
		{
			siBuyItemIndex = i;
			break;
		}
	}

	// �����ϴ� ��ǰ�� ��ġ���� ����.
	if ( siBuyItemIndex == -1)
	{
		return;
	}

	GMONEY price = 0;

	// ��ǰ, ȣǰ, �ű� �϶��� �������� ���� �ü��� ����´�
	if ( (pclinfo->uiRareInfo == RARELEVEL_2) || (pclinfo->uiRareInfo == RARELEVEL_1) || (pclinfo->uiRareInfo == RARELEVEL_5) )
	{
		price = (pclItemManager->GetCurrentPrice( pclinfo->siSellItemUnique ))->siPrice ;
	}
	// �Ϲ� �������� ��� �ü��� 50%~75��ŭ�� ������ ����´�
	else
	{
		price = pclForeignMerchantNPCInfo->siBuyItemPriceList[ siBuyItemIndex ];
	}
		
	
	if (  pclfromitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_2 )
	{
		price *=  10;			// ������ �ü��� 10��( ��ǰ )
	}
	else if (  pclfromitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_1 )
	{
		price *=  5;			// ������ �ü��� 3��( ȣǰ )
	}
	//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
	else if ( pclfromitem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
	{
		price *= 2;			// ������ �ü��� 2��( �ű� )
	}
	
	// �۷ι��� �ƴϸ� ������ ������ �Ǹ� ���ݷ� ����.
	if(!pclClient->IsCountrySwitch(Switch_SellToForeignMerchant))
	{	
		if ( pclinfo->uiRareInfo == RARELEVEL_1 )
		{
			price /= 5;			// ������ �ü��� 5�踦 Ǯ�� 3��( ȣǰ )
			price *= 3;
		}
		//[�߰� : Ȳ���� 2007. 12. 5 �ű⹰ǰ�� �ü��� 2��.]
		else if ( pclinfo->uiRareInfo == RARELEVEL_5 )
		{
			price /= 2;			// ������ �ü��� 2�踦 Ǭ��.( �ű� )
		}
	}
	
	SI32 remainDay = 0;
	BOOL rVal = GetItemUseAbleDay( pclfromitem , &remainDay );
	SI16 percent = 0;

	if (pclfromitem->IsSealingUp(pclItemManager) == false)
	{
		if( rVal == TRUE && remainDay == 0 ) //�Ϲ�ǰ�̴�.
		{
			percent = 100;
		}
		else if( rVal == TRUE && remainDay >0 )
		{

			switch (remainDay)
			{
			case 2 :
				percent = 50;
				price = price * 5 / 10;
				break;
			case 1 :
				percent = 30;
				price = price * 3 / 10;
				break;
			case 0 :
				percent = 10;
				price = price * 1 / 10;
				break;
			default:
				percent = 100;
				break;
			}			
		}
		else if(remainDay < 0)
		{
			percent = 0;
			price = 0;
		}
	}

	// ������ ���� 
	SI16 siDurabilityPenalty = 0;

	if ( IsCountrySwitch(Switch_NewDurability) )
	{
		REAL32 fGetDurabilityPenalty = pclfromitem->GetDurabilityPenlty( pclItemManager );

		price				= (GMONEY)((REAL64)price * (REAL64)fGetDurabilityPenalty);
		siDurabilityPenalty	= (SI16)(fGetDurabilityPenalty * 100.0f);
	}

	cltGameMsgResponse_PreSellToForeignMerchant clPreSellInfo(remainDay, percent, price, pclfromitem->clItemCommon.clCommonInfo.uiRareInfo, siDurabilityPenalty);

	cltMsg clMsg( GAMEMSG_RESPONSE_PRESELLTOFOREIGNMERCHANT, sizeof( clPreSellInfo ), (BYTE*)&clPreSellInfo );

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTNPCBUYINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ForeignMerchantNPCBuyInfo* pclinfo = (cltGameMsgRequest_ForeignMerchantNPCBuyInfo*)pclMsg->cData;

	// ����, ������ ������ üũ
	if( pclinfo->siForeignMerchantKind < FOREIGNMERCHANT_HELMET || pclinfo->siForeignMerchantKind >= FOREIGNMERCHANT_END )
	{
		return;
	}
	
	CForeignMerchantNPC *pForeignMerchantNPC = pclForeignMerchantNPCMgr->GetForeignMerchantNPC( pclinfo->siForeignMerchantKind );

	if ( pForeignMerchantNPC == NULL )
	{
		return;
	}

	if ( ! pForeignMerchantNPC->IsAvailable() )
	{
		return;
	}

	// ���� �������� NPC �� ������ ���õ� ������ �޾ƿ´�.
	stForeignMerchantNPCInfo* pclForeignMerchantNPCInfo = pForeignMerchantNPC->GetForeignMerchantNPCInfo();

	// ������ �̻��� ���...
	if ( pclForeignMerchantNPCInfo == NULL )
	{
		return;
	}
	
	cltGameMsgResponse_ForeignMerchantNPCBuyInfo clBuyInfo;
	
	clBuyInfo.Set
		(
		pclForeignMerchantNPCInfo->siForeignMerchantKind,
		pclForeignMerchantNPCInfo->siBuyItemType,
		&pclForeignMerchantNPCInfo->siBuyItemUniqueList[0],
		&pclForeignMerchantNPCInfo->siBuyItemPriceList[0],
		pclForeignMerchantNPCInfo->siBuyItemListCount
		);
	
	cltMsg clMsg( GAMEMSG_RESPONSE_FOREIGNMERCHANTNPCBUYINFO, sizeof( clBuyInfo ), (BYTE*)&clBuyInfo );

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

// ������ ���� ���� NPC �� ���� ���� ĳ�� �������� �������� ��û( �������� )
void cltServer::DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEMINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ForeignMerchantBuyCashItemInfo * pclinfo = (cltGameMsgRequest_ForeignMerchantBuyCashItemInfo*)pclMsg->cData;

	if ( pclinfo->siItemType < 1 || pclinfo->siItemType >= MAX_ITEMTYPE_NUMBER )
	{
		return;
	}

	SI16 ItemUniqueList[ MAX_AVAILABLE_CASHITEMNUM ];
	UI16 ItemPriceList[ MAX_AVAILABLE_CASHITEMNUM ];
	
	SI16 Counter = pclForeignMerchantNPCBuyCashItem->GetItemUniqueAndPriceListFromItemType( pclinfo->siItemType, ItemUniqueList, ItemPriceList );

	if ( Counter < 1 )
	{
		return;
	}

	cltGameMsgResponse_ForeignMerchantBuyCashItemInfo clGameMsgResponse_ForeignMerchantBuyCashItemInfo;
	clGameMsgResponse_ForeignMerchantBuyCashItemInfo.Set( pclinfo->siItemType, ItemUniqueList, ItemPriceList, Counter );
	cltMsg clMsg( GAMEMSG_RESPONSE_FOREIGNMERCHANTBUYCASHITEMINFO, clGameMsgResponse_ForeignMerchantBuyCashItemInfo.GetTotalSize(), (BYTE*)&clGameMsgResponse_ForeignMerchantBuyCashItemInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	
}

// ������ ���� ���ο��� ĳ�� ������ �Ǹ�
void cltServer::DoMsg_GAMEMSG_REQUEST_FOREIGNMERCHANTBUYCASHITEM(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	// 1�ʿ� �ѹ��� �̿��� �����ϴ�.
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}
	
	/*
	// SBS ȸ���� �Ǹ� �Ұ�
	if ( pclCM->CR[id]->IsSBS() )
	{
		SendServerResponseMsg(0, SRVAL_FOREIGNMERCHANT_NOTBUYCASHITEM_SBS,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	*/

	cltGameMsgRequest_ForeignMerchantBuyCashItem * pclinfo = (cltGameMsgRequest_ForeignMerchantBuyCashItem*)pclMsg->cData;

	if ( pclinfo->siItemPos < PERSONITEM_INV0 || pclinfo->siItemPos >= PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique < 1 ||	
		pclinfo->clSellItem.siItemNum < 1 ||
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique != pclinfo->clSellItem.siUnique ||
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siItemNum < pclinfo->clSellItem.siItemNum
		)
	{
		return;
	}

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� �Ǹ��� �� ����.
	//------------------------------------------------------
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )
		return;


	// �������� ���������� Ȯ��
	UI16 ItemOnePrice = 0;
	if ( ! pclForeignMerchantNPCBuyCashItem->GetItemPrice( pclinfo->clSellItem.siUnique, &ItemOnePrice ) )
	{
		return;
	}

	if ( ItemOnePrice < 1 || ItemOnePrice > 60000 )
	{
		SendServerResponseMsg(0, SRVAL_FOREIGNMERCHANT_NOTBUYCASHITEM_PRICE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		
		return;
	}

	// ������ ���� * �Ǹ� ����
	UI32 ItemPrice = ItemOnePrice * pclinfo->clSellItem.siItemNum;

	if ( ItemPrice < 1 || ItemPrice > 60000 )
	{
		SendServerResponseMsg(0, SRVAL_FOREIGNMERCHANT_NOTBUYCASHITEM_PRICE,  0, 0, pclCM->CR[id]->GetCharUnique() );

		return;
	}

	//cyj �����۸����� �� �����۸� �� �ȵ��� ����
	//if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].uiDateUseDay > 0)
	if ( pclItemManager->IsItemInfoAtb( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos ].siUnique, ITEMINFOATB_NOTTRADE) )
	{
		return ;
	}
	

	sDBRequest_ForeignMerchantBuyCashItem clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), pclCM->CR[id]->pclCI->clBI.szAccountID, 0, 0, 0, pclinfo->siItemPos, &pclinfo->clSellItem, ItemPrice );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclStatisticsManager->clDailyStatistics.siForeignMerchantBuyCashItemMoney += ItemPrice;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETRECOMMANDPOINT(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}


	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )	return ;
	

	sDBRequest_GetRecommendPoint clMsg( id, pclCM->CR[id]->pclCI->GetPersonID() );
	pclGameDBProcess->SendMsg( (sPacketHeader*)&clMsg);

}



// ��õ ����Ʈ�� �������� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_BUYRECOMMANDPRODUCT(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_BuyRecommandProduct * pclinfo = (cltGameMsgRequest_BuyRecommandProduct*)pclMsg->cData;
    
	/////////////////////////////////////////////////////////////
	SI32 ProductIndex = pclinfo->siRecommandProductIndex;
	
	if( ProductIndex < 0 || ProductIndex >= MAX_RECOMMAND_PRODUCT )
		return;

	// ������ Ŭ���̾�Ʈ�� ��ǰ ������ �ٸ��� ����
	stRecommandProduct* sRecommandProduct = &pclClient->pclRPMerchantNPCMgr->m_RecommandProduct[ProductIndex];

	if(sRecommandProduct->ItemUnique <= 0) 
		return;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( sRecommandProduct->ItemUnique );
	
	if( ref <= 0) 
		return;

	cltItem clItem	= pclClient->pclItemManager->pclItemInfo[ref]->clItem;

	clItem.SetItemNum( sRecommandProduct->ItemNum  );
	clItem.uiDateUseDay = sRecommandProduct->ItemUseDate;

	if( clItem.IsSame(&pclinfo->sRecommandProduct,true) == false )
		return;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// �ʿ� ����Ʈ�� ���ؿ´�. 
	SI32 NeedPoint = sRecommandProduct->NeedPoint;

	if(NeedPoint <= 0 ) 
		return;
	
	SI16 itempos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclinfo->sRecommandProduct, &itempos, &cltoitem, &rtnvalue) == TRUE)
	{
		sDBRequest_BuyRecommendProduct clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), &pclinfo->sRecommandProduct, pclinfo->sRecommandProduct.CanPile(pclItemManager), NeedPoint, itempos);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		if(pclchar)
		{
			//SendServerResponseMsg(0, SRVAL_NPC_MARKET_SELL_FAIL,  0, 0, pclchar->GetCharUnique());
		}
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_RECOMMANDPOINTLIST(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgRequest_RecommandPointList * pclinfo = (cltGameMsgRequest_RecommandPointList*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	sDBRequest_RecommendPointList clMsg(id, pclCM->CR[id]->pclCI->GetPersonID()  , pclinfo->siCurrentPage);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_MANUFACTURENPC( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_ManufactureNPC* pclinfo = (cltGameMsgRequest_ManufactureNPC*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )
		return;

	if( pclCM->IsAlive( id ) == false )
		return;

	if( pclCM->CR[id]->CheckLastMsgClock(1000) == true )
		return;

	// TODO : �����ᰡ �ִ��� Ȯ���Ѵ�.
	// 1. ������ ��� �������� �ü��� �̿�
	// 2. �����ݰ� ��

	cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice(pclinfo->siItemUnique);
	
	GMONEY fee = pclprice->siPrice / 10;

	if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < fee  )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_MANUFATURENPC_NOMONEY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

		cltGameMsgRequest_MakeItemInv clinfo( pclinfo->siItemUnique, 1, 0,0,PSHOP_MODE_NONE, 0, true );	// NPC�� ����� 
	MakeItemProcess( id, &clinfo );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RECEIVEBEGINNERITEM(cltMsg* pclMsg, SI32 id )
{
	// TODO 
	// �̹� �ʺ��� �������� �޾Ҵ��� üũ �ϰ�!
	// ������ �־��ش�!

	if( pclCM->IsValidID( id ) == false )
		return;

	if( pclCM->IsAlive( id ) == false )
		return;

	if( pclCM->CR[id]->CheckLastMsgClock(1000) == true )
		return;

	cltGameMsgRequest_RecieveBeginnerItem* pclinfo = 
		(cltGameMsgRequest_RecieveBeginnerItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if ( pclchar->pclCI->clBI.bReceiveBeginnerWeapon )
	{
		SendServerResponseMsg(0, SRVAL_FAIL_ALEADYRECEIVE_BEGINNERWEAPON,  0, 0, id);
		return;
	}

	pclchar->GiveItem( pclinfo->siItemUnique, 1, INPUTITEMPERSON_OPTION_BEGINNERWEAPON, 0 );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROMOTER_INFO_TOTAL_GET(cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_Promoter_Info_Total_Get* pclinfo = (cltGameRequest_Promoter_Info_Total_Get*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if( NULL == pclChar ) return;

	clPromoterInfo PromoterInfo( id, clPromoterInfo::GET_PROMOTER_INFO_TOTAL );
	pclPromoterManager->Push( PromoterInfo );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROMOTER_INFO_GET(cltMsg* pclMsg, SI32 id )
{
	/*cltGameRequest_Promoter_Info_Get* pclinfo = (cltGameRequest_Promoter_Info_Get*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if( NULL == pclChar ) return;

	clPromoterInfo PromoterInfo( id, clPromoterInfo::GET_PROMOTER_INFO );
	pclPromoterManager->Push( PromoterInfo );*/
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROMOTER_URL_GET(cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_Promoter_URL_Get* pclinfo = (cltGameRequest_Promoter_URL_Get*)pclMsg->cData;
	
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if( NULL == pclChar ) return;

	clPromoterInfo PromoterInfo( id, clPromoterInfo::GET_PROMOTER_URL );
	pclPromoterManager->Push( PromoterInfo );
}


void cltServer::DoMsg_GAMEMSG_REQUEST_PROMOTERNPC_GIVE_ITEM_GET(cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_PromoterNPC_Give_Item_Get* pclinfo = (cltGameRequest_PromoterNPC_Give_Item_Get*)pclMsg->cData;
	
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if( NULL == pclChar ) return;

	// ȹ���Ҽ� �ִ� ������ ���� �ֱ�
	cltRewardItem**	pcltRewardItemList = pclRewardMgr->GetRecommendRewardItemList();
	if( NULL == pcltRewardItemList ) return;

	cltGameResponse_PromoterNPC_Give_Item_Get clInfo;

	for( SI32 siCount = 0; siCount < Const_Max_RecommandReward_Item; ++siCount )
	{
		if( NULL == pcltRewardItemList[siCount] ) continue;

		clInfo.ItemUnique[siCount]	= pcltRewardItemList[siCount]->GetItemUnique();
		clInfo.ItemNum[siCount]		= pcltRewardItemList[siCount]->GetItemNum();
	}

	cltMsg clMsg2(GAMEMSG_RESPONSE_PROMOTERNPC_GIVE_ITEM_GET, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MONSTERCREATE(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_MonsterCreate* pclinfo = (cltGameRequest_MonsterCreate*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if(pclchar == NULL)	return;

	SI32 ref = pclGMManager->FindUniqueFromOrder(TEXT("cmt"));
	SI32 gamemasterlevel = pclchar->GetGameMasterLevel();

	if(ref < 1 || ref >= MAX_GMINFO_NUMBER)	return;

	// ��� ������ ������ ���� ���Ѵ�.
	if(gamemasterlevel < pclGMManager->pclGMInfo[ref]->siNeedGMLevel)	return;

	SI32 siMonsterkind = pclinfo->m_siMonsterKind;
	SI32 siMonCreateNum = pclinfo->m_siMonCreateNum;
	SI32 siMonLevel = pclinfo->m_siMonLevel;

	if(siMonsterkind == 0)	return;

	SI32 CreatedMonsterNum = 0;
	SI32 count = 0;

	cltGMCommandKindInfo* pclGMCommandKI;
	pclGMCommandKI = pclKindInfoSet->pclGMCommandKindInfo[siMonsterkind];

	cltKindInfo* pclki = NULL;
	pclki = pclKindInfoSet->pclKI[siMonsterkind];
	
	pclGMCommandKI->siAggressive = pclinfo->m_siAggro;
	pclGMCommandKI->clDefaultWeaponInfo.Set(pclki->clDefaultWeaponInfo.GetAttackType(), pclki->clDefaultWeaponInfo.GetAttackRange(), pclinfo->m_siMinDmg, pclinfo->m_siMaxDmg, pclinfo->m_siMonAC);
	pclGMCommandKI->clBA.SetStr(pclinfo->m_siMonStr);
	pclGMCommandKI->clBA.SetDex(pclinfo->m_siMonDex);
	pclGMCommandKI->clBA.SetVit(pclinfo->m_siMonVit);
	pclGMCommandKI->clBA.SetMag(pclinfo->m_siMonIntl);
	pclGMCommandKI->clBA.SetHnd(pclinfo->m_siMonHnd);
	pclGMCommandKI->clBA.SetLuk(pclinfo->m_siMonLuk);
	pclGMCommandKI->clBA.SetWis(pclinfo->m_siMonWis);
	pclGMCommandKI->siCriticalRate = pclinfo->m_siCriRate;
	pclGMCommandKI->dwAttackInterval = pclinfo->m_siAttInter;
	pclGMCommandKI->clCharElemental.Set(pclinfo->m_siFire, pclinfo->m_siWater, pclinfo->m_siLand, pclinfo->m_siWind, pclinfo->m_siNature, 
		pclki->pclCharElemental.GetFireA(), pclki->pclCharElemental.GetWaterA(), pclki->pclCharElemental.GetLandA(), pclki->pclCharElemental.GetWindA());

	// ��ڸ�ɾ� �α׿� �����. (������ ������ �̸�, �������� ǥ���ϰ� ������ ������ �׳� ������� �����͸� ��´�.
	// ������ ���� : �ּҵ�����, �ִ뵥����, ����, ��, ��ø, �����, ����, ������, ���, ����, �����׷�, �����׷�, �����׷�, �ٶ����׷�, �������׷�
	pclLog->FilePrint(TEXT("Config\\GameMaster.log"), TEXT("User:[%s] Use cmt : MonsterName : [%s], MonsterNum : [%d], [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] "), 
		pclCM->CR[id]->GetName(), pclki->GetName(), pclinfo->m_siMonCreateNum, pclinfo->m_siMinDmg, pclinfo->m_siMaxDmg, pclinfo->m_siMonAC, pclinfo->m_siMonStr, pclinfo->m_siMonDex, pclinfo->m_siMonVit, pclinfo->m_siMonIntl,
		pclinfo->m_siMonHnd, pclinfo->m_siMonLuk, pclinfo->m_siMonWis, pclinfo->m_siFire, pclinfo->m_siWater, pclinfo->m_siLand, pclinfo->m_siWind, pclinfo->m_siNature);

	for(SI32 i = 0; i < siMonCreateNum; i++)
	{
		SI32 x, y;
		if(pclchar->pclMap->FindEmptyAreaForCharLocate(siMonsterkind, pclchar->GetX(), pclchar->GetY(), 20, &x, &y, true) == false)
		{
			continue;
		}

		pclchar->SetInitProtectSwitch();

		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

		SI32 siSummonID = SetNPCChar(siMonsterkind, VILLAGE_NONE, NULL, siMonLevel, 0, x, y, pclchar->GetMapIndex(), NPCITEMMODE_GM, &clinnerstatus, NULL, pclGMCommandKI);

		if(siSummonID > 0)
		{
			SendServerResponseMsg( 0, SRVAL_RETURN_MONCREATE_DLG_SUCCESS, 0, 0, id );
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_ITEM_PACKING(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineDay_Item_Packing* pclinfo = (cltGameRequest_ValentineDay_Item_Packing*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if(pclchar == NULL)	return;

	if( 0 >= pclinfo->m_clPackingItem.siItemNum )																		  return;
	if( pclinfo->m_clPackingItem.siItemNum > pclchar->pclCI->clCharItem.GetItemNum( pclinfo->m_clPackingItem.siUnique ) ) return;

	bool bResult = false;
	// �κ��� �α��� ����� ������ ��� ���.
	if( true == pclchar->IsBlankInv( 2, INVMODE_ALL ) )
	{
		bResult = true;
	}
	// �κ��� �� �������� ���� �������� �κ��� �ִ��� Ȯ���ؼ� �ΰ� �� ������ �������� �ش�.
	else
	{
		SI32 siPackItemUnique1 = ITEMUNIQUE(13661);
		SI32 siPackItemUnique2 = ITEMUNIQUE(13373);

		SI32 Pos1 = pclchar->pclCI->clCharItem.GetItemPos( siPackItemUnique1 );
		SI32 Pos2 = pclchar->pclCI->clCharItem.GetItemPos( siPackItemUnique2 );
		
		// �ΰ� �� �κ��� �������� �ִٸ�
		if( 0 < Pos1 && 0 < Pos2 )
		{
			bResult = true;
		}
		// ���� �ϳ��� �ְ�
		else if( 0 < Pos1 || 0 < Pos2 )
		{
			// �κ� �ϳ��� ����ִٸ�.
			if( true == pclchar->IsBlankInv( 1, INVMODE_ALL ) )
			{
				bResult = true;
			}
		}
	}

	if( false == bResult ) 
	{
		SendServerResponseMsg( 0, SRVAL_CANNOTINPUTTOINV, 0, 0, pclchar->GetID() );
		return;
	}
		
	pclchar->GiveItem( ITEMUNIQUE(13661), pclinfo->m_clPackingItem.siItemNum, INPUTITEMPERSON_OPTION_VALENTINEDAY_PAKING, 0 );
	pclchar->GiveItem( ITEMUNIQUE(13373), pclinfo->m_clPackingItem.siItemNum, INPUTITEMPERSON_OPTION_VALENTINEDAY_PAKING, 0 );

	// ������ ���.
	SI32 siInvenPos = pclchar->pclCI->clCharItem.GetItemPos( pclinfo->m_clPackingItem.siUnique );
	if( 0 > siInvenPos ) return;

	cltItem clUseItem;
	clUseItem.Set( &pclchar->pclCI->clCharItem.clItem[siInvenPos] );
	clUseItem.siItemNum = pclinfo->m_clPackingItem.siItemNum;

	sDBRequest_UseItem useitem(	pclchar->GetID(),
								pclchar->pclCI->GetPersonID(),
								siInvenPos,
								&clUseItem, 
								USEITEM_REASON_CONTRIBUTION_ITEM_INPUT	);

	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

	

	cltItem	clResultItem[2];
	clResultItem[0].siUnique  = ITEMUNIQUE(13661);
	clResultItem[0].siItemNum = pclinfo->m_clPackingItem.siItemNum;
	clResultItem[1].siUnique  = ITEMUNIQUE(13373);
	clResultItem[1].siItemNum = pclinfo->m_clPackingItem.siItemNum;
	
	cltGameResponse_ValentineDay_Item_Packing clInfo( clResultItem );
	cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINEDAY_ITEM_PACKING, PACKET(clInfo) );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_BUY_ITEM(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineDay_Buy_Item* pclinfo = (cltGameRequest_ValentineDay_Buy_Item*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if(pclchar == NULL)	return;

	if( pclinfo->m_UseMoney > pclchar->pclCI->clIP.GetMoney() ) return;

	const SI32 siNPCKind = pclClient->GetUniqueFromHash( TEXT("KIND_GIFTRACCOON") );
	
	// �ش� NPC�� �Ǹ��ϴ� �������� ���� ���.
	cltNPCMerchantInfo* pNPCMerchantInfo	= NULL;
	for( SI16 siCount = 0; siCount < MAX_NPC_MERCHANT_NUMBER; ++siCount )
	{
		if( siNPCKind == pclNPCItemInfo->clNPCMerchantInfo[siCount].siNPCKind )
		{
			pNPCMerchantInfo = &pclNPCItemInfo->clNPCMerchantInfo[siCount];
			break;
		}
	}

	if( NULL == pNPCMerchantInfo ) return;

	// ���� �����ϴ� �������� NPC�� �Ǹ��ϴ� ������ ��Ͽ� �ִ��� Ȯ��.
	bool bNPCSellItem = false;
	for ( SI32 i = 0; i < MAX_NPC_ITEM_NUMBER; ++i )
	{
		if( pclinfo->m_clBuyItem.siUnique == pNPCMerchantInfo->clItemInfo[i].clItem.siUnique )
		{
			bNPCSellItem = true;
			break;
		}
	}

	if( false == bNPCSellItem ) return;

	if( GIVEITEM_RESULT_SUCCESS == pclchar->GiveItem( pclinfo->m_clBuyItem.siUnique, pclinfo->m_clBuyItem.siItemNum, INPUTITEMPERSON_OPTION_VALENTINEDAY_BUY, 0 ) )
	{
		sDBRequest_ChangeMoney clMsg( id, pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_VALENTINEDAY_BUY_ITEM, -pclinfo->m_UseMoney );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


		cltGameResponse_ValentineDay_Buy_Item clInfo( &pclinfo->m_clBuyItem );
		cltMsg clMsg2( GAMEMSG_RESPONSE_VALENTINEDAY_BUY_ITEM, PACKET(clInfo) );
		pclchar->SendNetMsg((sPacketHeader*)&clMsg2 );
	}
	else
	{
		SendServerResponseMsg( 0, SRVAL_CANNOTINPUTTOINV, 0, 0, pclchar->GetID() ); 
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_QUESTION(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineDay_Confession_Question* pclinfo = (cltGameRequest_ValentineDay_Confession_Question*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( NULL == pclchar )		return;

	// ����� �޴� ���.
	SI32 siTargetPersonID = pclCM->GetPersonIDFromName( pclinfo->m_szTargetName );
	if( 0 >= siTargetPersonID )	
	{
		SendServerResponseMsg( 0, SRVAL_VALENITNEDAY_NOT_USER, 0, 0, pclchar->GetID() ); 
		return; 
	}

	// �ڽ����� ��� �� �� ����.
	if( siTargetPersonID == pclchar->pclCI->GetPersonID() ) 
	{
		SendServerResponseMsg( 0, SRVAL_VALENITNEDAY_NOT_MYSELF, 0, 0, pclchar->GetID() ); 
		return; 
	}
	
	cltCharServer* pclTargetChar = pclCM->GetCharServer( pclCM->GetIDFromPersonID( siTargetPersonID ) );
	if( NULL == pclTargetChar ) 
	{
		SendServerResponseMsg( 0, SRVAL_VALENITNEDAY_NOT_USER, 0, 0, pclchar->GetID() ); 
		return; 
	}

	if(    pclchar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_VALENTINEDAY ) 
		|| pclTargetChar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_VALENTINEDAY ) )
	{
		SendServerResponseMsg( 0, SRVAL_VALENITNEDAY_ALREADY_BUF, 0, 0, pclchar->GetID() ); 
		return;
	}
	
	
	cltGameResponse_ValentineDay_Confession_Question clInfo( pclchar->pclCI->GetPersonID(), (TCHAR*)pclchar->GetName(), pclinfo->m_szMsg );
	cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_QUESTION, PACKET(clInfo) );
	pclTargetChar->SendNetMsg((sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEDAY_CONFESSION_ANSWER(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineDay_Confession_Answer* pclinfo = (cltGameRequest_ValentineDay_Confession_Answer*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if(pclchar == NULL)	return;

	// ����� �ѻ��.
	cltCharServer* pclTargetChar = pclCM->GetCharServer( pclCM->GetIDFromPersonID( pclinfo->m_siTargetPersonID ) );
	if( NULL == pclTargetChar ) return;

	if( pclinfo->m_bResult )
	{
		// ������ ����.
		SI32 siInvenPos = pclTargetChar->pclCI->clCharItem.GetItemPos( 13661 );
		if( 0 > siInvenPos ) return;

		SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.				

		SI16 index = pclchar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_VALENTINEDAY, false );
		if( index > -1 )
		{
			stBuf addBuf( BUF_VALENTINEDAY, 0, usetime );
			pclchar->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0 );
		}

		index = pclTargetChar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_VALENTINEDAY, false );
		if( index > -1 )
		{
			stBuf addBuf( BUF_VALENTINEDAY, 0, usetime );
			pclTargetChar->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0 );
		}

		// ������ ���.
		cltItem clUseItem;
		clUseItem.Set( &pclTargetChar->pclCI->clCharItem.clItem[siInvenPos] );
		clUseItem.siItemNum = 1;

		sDBRequest_UseItem useitem(	pclTargetChar->GetID(),
									pclTargetChar->pclCI->GetPersonID(),
									siInvenPos,
									&clUseItem, 
									USEITEM_REASON_VALENTINEDAY	);

		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
	}
	
	cltGameResponse_ValentineDay_Confession_Answer clInfo( pclinfo->m_bResult, (TCHAR*)pclchar->GetName() );
	cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINEDAY_CONFESSION_ANSWER, PACKET(clInfo) );
	pclTargetChar->SendNetMsg((sPacketHeader*)&clMsg );
}


