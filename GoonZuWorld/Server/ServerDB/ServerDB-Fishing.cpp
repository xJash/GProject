#include "..\Common\CommonHeader.h"

#include "..\Common\Order\Order.h"
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\CommonLogic\Msg\MsgType-Fishing.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Fishing.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"

void cltServer::DoMsg_DBMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY(sPacketHeader* pPacket)
{
	sDBResponse_FishingDecreaseToolDurability *pclMsg = (sDBResponse_FishingDecreaseToolDurability*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( id > 0 && pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// ������ �Ҹ� ��Ŵ.
		for ( SI16 i = 0; i < MAX_FISHING_TOOL_NUMBER; ++i )
		{
			if ( pclMsg->clFishingTool[ i ].siPos > 0 )
			{
				if( pclMsg->clFishingTool[ i ].siPos < 0 || pclMsg->clFishingTool[ i ].siPos >= MAX_ITEM_PER_PERSON )
					pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->clFishingTool[ i ].siPos ].Set( &pclMsg->clFishingTool[ i ].clItem );
			}
		}

		cltGameMsgResponse_FishingDecreaseToolDurability clGameMsgResponse_FishingDecreaseToolDurability( pclMsg->clFishingTool );
		cltMsg clMsg( GAMEMSG_RESPONSE_FISHINGDECREASETOOLDURABILITY, sizeof( clGameMsgResponse_FishingDecreaseToolDurability ), (BYTE*)&clGameMsgResponse_FishingDecreaseToolDurability );
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ���ô� ���� ���� ����.(�����ʿ� : �������� �迭 10���� ��� �ϳ�?)
		//	//  
		//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_FISHING_TOOL_DUR_DECREASE, 
		//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		//									0, 0, 0, 0, 0, NULL, NULL);
		//}
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_FISHINGGETMARINEPRODUCTS(sPacketHeader* pPacket)
{
	sDBResponse_FishingGetMarineProducts *pclMsg = (sDBResponse_FishingGetMarineProducts *)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;
	
	// ��ȹ���� ȹ���Ѱ� ��迡 �߰�
	if ( pclMsg->clLeftItem.siUnique > 0 )
	{
		//cyj ����ǰ ��� �߰�
		pclItemManager->AddProductionItemNum( pclMsg->clLeftItem.siUnique, pclMsg->siAddedItemNum );

		// ���ο� ��� - ������� ���� ���� ��ǰ�� ��踦 ����.
		NStatistics_Add("Item", pclMsg->clLeftItem.siUnique, "ProductionNum", pclMsg->siAddedItemNum);
		NStatistics_Set("Item", pclMsg->clLeftItem.siUnique, "Name", pclItemManager->GetName(pclMsg->clLeftItem.siUnique));
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// ������ Update
		if ( pclMsg->siAcquireMarineInvPos > 0 )
		{
			if( pclMsg->siAcquireMarineInvPos >= 0 && pclMsg->siAcquireMarineInvPos < MAX_ITEM_PER_PERSON )
				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siAcquireMarineInvPos ].Set( &pclMsg->clLeftItem );
		}

		cltGameMsgResponse_FishingGetMarineProducts clGameMsgResponse_FishingGetMarineProducts
			(
			FISHING_SUCCESS,
			pclMsg->clLeftItem.siUnique,				
			pclMsg->siAcquireMarineInvPos, 
			&pclMsg->clLeftItem,				
			pclMsg->siKind
			);
		cltMsg clMsg( GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTS, sizeof( clGameMsgResponse_FishingGetMarineProducts ), (BYTE*)&clGameMsgResponse_FishingGetMarineProducts );		
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ���÷� ��� ���� ������ ���.
			// Item = ���� ���깰
			// NPCKind = ���� ĳ������ KIND
			// param1 == ���깰�� �� ��ġ,  
			// param2 == ���� ����ġ
			// param3 == ��������ġ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_FISHING, 
								FISHING_SUCCESS, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clAcquireMarineProductItem, pclMsg->clLeftItem.siItemNum, 0, pclMsg->siKind, 0, 0, 0, 
								pclMsg->siAcquireMarineInvPos, pclMsg->siIncSkillUnique, pclMsg->siSkillTotalExp, 0, 0, 
								NULL, NULL);
		}
		
		cltGameMsgResponse_FishingGetMarineProductsNotify clGameMsgResponse_FishingGetMarineProductsNotify
			(
			FISHING_SUCCESS,
			pclMsg->clLeftItem.siUnique,
			pclMsg->siAddedItemNum,
			pclMsg->siCharUnique,
			pclMsg->siKind
			);
		cltMsg clMsg1( GAMEMSG_RESPONSE_FISHINGGETMARINEPRODUCTSNOTIFY, sizeof( clGameMsgResponse_FishingGetMarineProductsNotify ), (BYTE*)&clGameMsgResponse_FishingGetMarineProductsNotify );
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg( &clMsg1, true);

		//[����] - 2010�ų��̺�Ʈ : ������ 3% Ȯ���� 1���� ������Ű ���� ȹ��
		((cltCharServer*)(pclCM->CR[id]))->GiveFortuneCookiePiece( 30, 1 );
	}

	return;
}