//---------------------------------
// 2004/2/18 ���°�
//---------------------------------
#include "Char\CharManager\CharManager.h"
#include "..\Server\Server.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "../Server/Statistics/Statistics.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Hunt.h"

#include "..\Common\Order\Order.h"
#include "..\CommonLogic\Hunt\Hunt.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-Hunt.h"


// �����忡 ����. 
void cltServer::DoMsg_GAMEMSG_REQUEST_ENTERHUNT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_EnterHunt* pclinfo = (cltGameMsgRequest_EnterHunt*)pclMsg->cData;
	
	if(pclCM->IsAlive(id) == false)return ;
	if(pclinfo->siVillageUnique != pclCM->CR[id]->GetCurrentVillageUnique())return ;
	if(pclinfo->siVillageUnique < 0 || pclinfo->siVillageUnique >= MAX_VILLAGE_NUMBER)		return;

	SI32 returnvalpara1 = 0;

	cltHunt* pclhunt = (cltHunt*)pclHuntManager->pclStruct[pclinfo->siVillageUnique];
	if(pclhunt == NULL)return ;
		
	// ���Ͱ� �����ص� ���� �Ұ�. 
	if(pclHuntManager->IsHuntLineUpMonsterReady(pclinfo->siVillageUnique) == false)
	{
		SendServerResponseMsg(0, SRVAL_HUNT_NOTENOUGHMON,  0, 0, id);
		return ;
	}

	
	// ���� �ε����� ���Ѵ�. 
	SI32 mapindex = pclinfo->siVillageUnique + 200;
	if( mapindex < 0 || pclinfo->siVillageUnique >= MAX_MAP_NUMBER )		return;


	// �����忡 ������ ������ ��� ��. 
	SI32 enternum = 0;

	pclStatisticsManager->clDailyStatistics.siHuntUserNumber++;		// ��踦 ���� �� ���尴 �ľ� 
	pclhunt->siLeftUserNum++;	// ���尴 ���. 
				
	pclhunt->clStrInfo.clHuntStrInfo.siUserNum++;	// ���尴 �� ����. 	
				
	// ���������� �̵��Ѵ�.
	OrderStop(id, BY_COMPUTER);

	if(pclMapManager->pclMapArray[mapindex])
	{
		SI32 huntmaptype = pclMapManager->pclMapArray[mapindex]->siMapUnique;
		if(huntmaptype <= 0 || huntmaptype >= MAX_MAPTYPE_NUMBER)	return;

		SI32 huntcenterx = pclMapManager->pclMapTypeManager->pclMapTypeInfo[huntmaptype]->siCenterX;
		SI32 huntcentery = pclMapManager->pclMapTypeManager->pclMapTypeInfo[huntmaptype]->siCenterY;

		cltWarpInfo clWarpInfo(1, mapindex, false, false, huntcenterx, huntcentery, -1, -1);
		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, 1800);
	}
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTADD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HuntMonsterFieldListAdd* pclinfo = (cltGameMsgRequest_HuntMonsterFieldListAdd*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)return ;
	if(pclinfo->siVillageUnique != pclCM->CR[id]->GetCurrentVillageUnique())return ;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ ����� �ƴϴ�.
	if ( RANKTYPE_HUNT != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
	{
		return;
	}

	// ������ ���� �ʴ�.
	if ( pclinfo->siVillageUnique != pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique() )
	{
		return;
	}	

	if ( pclinfo->siMonsterNum < 0 || pclinfo->siMonsterNum > MAX_HUNT_LINEUP_EACH_MONSTER_NUM )
	{
		return;
	}

	if ( pclinfo->siMonsterLevel < 1 || pclinfo->siMonsterLevel > MAX_CHARACTER_LEVEL )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclinfo->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	SI32 i = 0;
	SI32 Ref = 0;
	SI32 MonKind = 0; //pclClient->pclItemManager->pclItemInfo[ref]->siMakeKind;
	for ( ; i < MAX_HUNT_STG_NUMBER; ++i )
	{
		if ( pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemUnique != 0 )
		{
			Ref = pclItemManager->FindItemRefFromUnique( pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemUnique );
			
			if ( Ref > 0 && pclItemManager->pclItemInfo[Ref]->siMakeKind == pclinfo->siMonsterKind )
			{
				break;
			}
		}
	}

	// â�� ���� ���͸� ������� �ؼ���...
	if ( i >= MAX_HUNT_STG_NUMBER )
	{
		return;
	}

	if ( pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemNum < pclinfo->siMonsterNum )
	{
		return;
	}

	SI16 CurrentLineUpMonsterTotalNum = 0;
	SI16 AddListIndex = -1;	

	for ( i = 0; i < MAX_HUNT_LINEUP_NUMBER; ++i )
	{
		if ( pclStrInfo->clHuntStrInfo.clHuntLineUp[i].siLineUpKind > 0 )
		{
			if( pclStrInfo->clHuntStrInfo.clHuntLineUp[i].siLineUpKind != pclinfo->siMonsterKind )
			{
				CurrentLineUpMonsterTotalNum += pclStrInfo->clHuntStrInfo.clHuntLineUp[i].siLineUpKindNum;
			}

			if ( pclStrInfo->clHuntStrInfo.clHuntLineUp[i].siLineUpKind == pclinfo->siMonsterKind )
			{
				AddListIndex = i;
			}
		}
		else
		{
			if ( AddListIndex < 0 )
			{
				AddListIndex = i;
			}
		}
	}

	if ( pclinfo->siMonsterNum + CurrentLineUpMonsterTotalNum > MAX_HUNT_MONSTER_NUM || 
		AddListIndex == -1
		)
	{
		return;
	}

	sDBRequest_HuntMonsterFieldListAdd clMsg( 
		FromPersonID, 
		id, 
		pclinfo->siVillageUnique, 
		AddListIndex, 
		pclinfo->siMonsterKind,
		pclinfo->siMonsterNum,
		pclinfo->siMonsterLevel
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HUNTMONSTERFIELDLISTDEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HuntMonsterFieldListDel *pclinfo = (cltGameMsgRequest_HuntMonsterFieldListDel *)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)
		return;
	if(pclinfo->siVillageUnique != pclCM->CR[id]->GetCurrentVillageUnique())
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ ����� �ƴϴ�.
	if ( RANKTYPE_HUNT != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
	{
		return;
	}

	// ������ ���� �ʴ�.
	if ( pclinfo->siVillageUnique != pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique() )
	{
		return;
	}

	if ( pclinfo->siDelListIndex < 0 || pclinfo->siDelListIndex >= MAX_HUNT_LINEUP_NUMBER )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclinfo->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	if ( pclStrInfo->clHuntStrInfo.clHuntLineUp[pclinfo->siDelListIndex].siLineUpKind > 0 )
	{
		sDBRequest_HuntMonsterFieldListDel clMsg( 
			FromPersonID, 
			id, 
			pclinfo->siVillageUnique,
			pclinfo->siDelListIndex
			);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HUNTMONSTERIN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HuntMonsterIn* pclinfo = (cltGameMsgRequest_HuntMonsterIn*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)
		return;
	if(pclinfo->siVillageUnique != pclCM->CR[id]->GetCurrentVillageUnique())
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ ����� �ƴϴ�.
	if ( RANKTYPE_HUNT != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
	{
		return;
	}

	// ������ ���� �ʴ�.
	if ( pclinfo->siVillageUnique != pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique() )
	{
		return;
	}

	if ( pclinfo->siFromPersonInventoryItemIndex < PERSONITEM_INV0 || pclinfo->siFromPersonInventoryItemIndex > MAX_ITEM_PER_PERSON )
	{
		return;
	}

	if( pclinfo->siItemUnique < 1 )
	{
		return;
	}

	// ������ Ÿ���� ������ �ƴ��� üũ
	if ( ( pclItemManager->GetItemAtb( pclinfo->siItemUnique ) & ITEMATB_DOLL ) == 0 )
	{
		return;
	}

	if ( pclinfo->siItemNum < 1 || pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}
	
	// ������ unique Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siFromPersonInventoryItemIndex ].siUnique != pclinfo->siItemUnique )
	{
		return;
	}

	// ������ ������ �������� Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siFromPersonInventoryItemIndex ].siItemNum < pclinfo->siItemNum )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclinfo->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	SI16 EmptyIndex = -1;

	SI32 i = 0;
	for ( ; i < MAX_HUNT_STG_NUMBER; ++i )
	{
		if ( pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemUnique == pclinfo->siItemUnique )
		{
			break;
		}
		else
		{
			if ( pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemUnique ==0 && EmptyIndex < 0 )
			{
				EmptyIndex = i;
			}
		}
	}

	// ItemUnique ���� ���� �������� â�� �����ϴ� ���
	// i ���� ���� �������� �����ϴ� â�� ������ ��ġ
	if ( i < MAX_HUNT_STG_NUMBER )
	{
		// ������ ������ �ߺ� ������ �ʰ��� �ÿ��� ���� ���� ( �ִ� ������ �°� )
		if ( pclinfo->siItemNum + pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemNum > MAX_ITEM_PILE_NUMBER )
		{
			pclinfo->siItemNum = MAX_ITEM_PILE_NUMBER - pclStrInfo->clHuntStrInfo.clHuntStg[ i ].siItemNum;

			if ( pclinfo->siItemNum < 1 )
			{
				return;
			}
		}

		sDBRequest_HuntStorageMonsterIn clMsg ( FromPersonID, id, pclinfo->siFromPersonInventoryItemIndex, i, pclinfo->siVillageUnique, pclinfo->siItemUnique, pclinfo->siItemNum );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	// ���� �������� â�� ����, ���� �� ������ ����.
	// EmptyIndex ���� â�� �� ���� ��ġ.
	else if ( EmptyIndex > -1 )		
	{
		sDBRequest_HuntStorageMonsterIn clMsg ( FromPersonID, id, pclinfo->siFromPersonInventoryItemIndex, EmptyIndex, pclinfo->siVillageUnique, pclinfo->siItemUnique, pclinfo->siItemNum );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else							// ���� �������� â�� ����, ���� �� ������ ���� ���
	{
		return;
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HUNTMONSTEROUT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HuntMonsterOut* pclinfo = (cltGameMsgRequest_HuntMonsterOut*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)
		return;
	if(pclinfo->siVillageUnique != pclCM->CR[id]->GetCurrentVillageUnique())
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// ������ ����� �ƴϴ�.
	if ( RANKTYPE_HUNT != pclCM->CR[id]->pclCI->clCharRank.GetRankType() )
	{
		return;
	}

	// ������ ���� �ʴ�.
	if ( pclinfo->siVillageUnique != pclCM->CR[id]->pclCI->clCharRank.GetVillageUnique() )
	{
		return;
	}

	if ( pclinfo->siFromHuntStorageItemIndex < 0 || pclinfo->siFromHuntStorageItemIndex >= MAX_HUNT_STG_NUMBER )
	{
		return;
	}
	
	if( pclinfo->siItemUnique < 1 )
	{
		return;
	}

	// ������ Ÿ���� ������ �ƴ��� üũ
	if ( ( pclItemManager->GetItemAtb( pclinfo->siItemUnique ) & ITEMATB_DOLL ) == 0 )
	{
		return;
	}

	if ( pclinfo->siItemNum < 1 || pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}

	cltStrInfo *pclStrInfo = pclHuntManager->GetStrInfo( pclinfo->siVillageUnique );

	if ( pclStrInfo == NULL )
	{
		return;
	}

	 
	// ������ unique Ȯ��
	if ( pclStrInfo->clHuntStrInfo.clHuntStg[ pclinfo->siFromHuntStorageItemIndex ].siItemUnique != pclinfo->siItemUnique )
	{
		return;
	}

	// ������ ������ �������� Ȯ��
	if ( pclStrInfo->clHuntStrInfo.clHuntStg[ pclinfo->siFromHuntStorageItemIndex ].siItemNum < pclinfo->siItemNum )
	{
		return;
	}

	SI16 EmptyIndex = -1;
	cltItem clItem;
	clItem.Init();
	clItem.siUnique = pclinfo->siItemUnique;
	clItem.siItemNum = pclinfo->siItemNum;

	cltItem clTempItem;
	clTempItem.Init();


	SI32 RetrunValue;

	if ( ! pclchar->CanAddInv(INVMODE_PERSON, &clItem, &EmptyIndex, &clTempItem, &RetrunValue ) )
	{
		return;
	}
	
	sDBRequest_HuntStorageMonsterOut clMsg ( FromPersonID, id, pclinfo->siFromHuntStorageItemIndex, EmptyIndex, pclinfo->siVillageUnique, pclinfo->siItemUnique, pclinfo->siItemNum );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	/*
	SI32 i = PERSONITEM_INV0;
	for ( ; i < MAX_ITEM_PER_PERSON; ++i )
	{
		if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ i ].siUnique == pclinfo->siItemUnique )
		{
			break;
		}
		else
		{
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ i ].siUnique == 0 && EmptyIndex < 0 )
			{
				EmptyIndex = i;
			}
		}
	}


	// ItemUnique ���� ���� �������� â�� �����ϴ� ���
	// i ���� ���� �������� �����ϴ� â�� ������ ��ġ
	if ( i < MAX_ITEM_PER_PERSON )
	{
		// ������ ������ �ߺ� ������ �ʰ��� �ÿ��� ���� ���� ( �ִ� ������ �°� )
		if ( pclinfo->siItemNum + pclCM->CR[id]->pclCI->clCharItem.clItem[ i ].siItemNum > MAX_ITEM_PILE_NUMBER )
		{
			pclinfo->siItemNum = MAX_ITEM_PILE_NUMBER - pclCM->CR[id]->pclCI->clCharItem.clItem[ i ].siItemNum;

			if ( pclinfo->siItemNum < 1 )
			{
				return;
			}
		}
		
		sDBRequest_HuntStorageMonsterOut clMsg ( FromPersonID, id, pclinfo->siFromHuntStorageItemIndex, i, pclinfo->siVillageUnique, pclinfo->siItemUnique, pclinfo->siItemNum );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	// ���� �������� â�� ����, ���� �� ������ ����.
	// EmptyIndex ���� â�� �� ���� ��ġ.
	else if ( EmptyIndex > -1 )		
	{
		sDBRequest_HuntStorageMonsterOut clMsg ( FromPersonID, id, pclinfo->siFromHuntStorageItemIndex, EmptyIndex, pclinfo->siVillageUnique, pclinfo->siItemUnique, pclinfo->siItemNum );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else							// ���� �������� â�� ����, ���� �� ������ ���� ���
	{
		return;
	}
	*/

	return;
}
//���� ���� ����Ʈ
void cltServer::DoMsg_GAMEMSG_REQUEST_HOFLIST(cltMsg* pclMsg, SI32 id){

	cltGameMsgRequest_HOFList *pclInfo = (cltGameMsgRequest_HOFList*)pclMsg->cData;

	cltCharCommon* pclchar = pclClient->pclCM->CR[id];
	if( pclchar == NULL )			return;

	sDBRequest_HOFList clMsg( pclchar->GetCharID(), INSTANCEMAPPOINT_TYPE_GUILD, pclInfo->siRequestPage );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

//��ŷ ����Ʈ
void cltServer::DoMsg_GAMEMSG_REQUEST_RAKINGLIST(cltMsg* pclMsg, SI32 id){//��ŷ����Ʈ������ ���� �ش� ������ ���� �����ָ� �ȴ�.
	//�׷��� ��񿡼� ����Ǿ� �ִ� �ش翬���� ������ �����ش�.������ �� ����.
	cltGameMsgRequest_RankingList *pclInfo = (cltGameMsgRequest_RankingList*)pclMsg->cData;
	
	cltCharCommon* pclchar = pclClient->pclCM->CR[id];
	if( pclchar == NULL )			return;

	sDBRequest_YearRanking clMsg( pclCM->CR[id]->GetCharID(), INSTANCEMAPPOINT_TYPE_GUILD, pclInfo->uiYear, false,pclInfo->siPageNum );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}


// [�߰� : Ȳ���� 2008. 1. 9 => �ν���Ʈ���� ���� ���� ����.]
void cltServer::DoMsg_GAMEMSG_REQUEST_INSTANTSDUNGEON_STATUS(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_InstantsDungeonStatus* pclinfo = (cltGameMsgRequest_InstantsDungeonStatus*)pclMsg->cData;

	cltGameMsgResponse_InstantsDungeonStatus GuildInfo;

	SI32 siCount = 0;
	SI32 siMapIndex = MAPINDEX_MOFUMOFU_AGIT;
	cltMapCommon* pclMap = pclMapManager->GetMapPointer(siMapIndex);
	if( pclMap == NULL)			return;

	SI32 siGuildUnique = pclMap->m_siInstanceMapData;

	cltGuildInfo* pclGuildInfo = pclGuildManager->GetGuildInfo(siGuildUnique);
	if(pclGuildInfo)
	{
		StringCchCopy(GuildInfo.clGuildInfo[siCount].szGuildName, sizeof(GuildInfo.clGuildInfo[siCount].szGuildName), pclGuildInfo->GetName());
		GuildInfo.clGuildInfo[siCount].siRemainTime = (pclMap->m_dwInstanceMapStartTime + 30 * 60 * 1000) - pclClient->CurrentClock;
		GuildInfo.clGuildInfo[siCount].siScore = pclMap->m_siInstanceMapScore;
		GuildInfo.clGuildInfo[siCount].siGuildMarkIndex = pclGuildInfo->clGPoint.siMarkIndex;
		siCount++;
	}

	SI32		  cloneindex	= 0;
	SI32		  dstMap		= 0;
	cltMapCommon* pcldstMap		= NULL;
	if( pclMapManager->HaveCloneMap( siMapIndex ) )
	{
		cloneindex = pclMapManager->clUnitMapInfo[siMapIndex].siCloneIndex;

		for ( SI32 i=0; i < CLONEMAP_NUM ; ++i )
		{
			dstMap = pclMapManager->clCloneMapInfo[cloneindex].siDstMapIndex[i];
			if ( dstMap <= 0 ) continue;

			pcldstMap = pclMapManager->GetMapPointer(dstMap);
			if( pcldstMap == NULL)			continue;

			siGuildUnique = pcldstMap->m_siInstanceMapData;

			if( siCount >= MAX_INSTANCEDUNGEON_STATUS )		continue;

			pclGuildInfo = pclGuildManager->GetGuildInfo(siGuildUnique);
			if(pclGuildInfo)
			{
				StringCchCopy(GuildInfo.clGuildInfo[siCount].szGuildName, sizeof(GuildInfo.clGuildInfo[siCount].szGuildName), pclGuildInfo->GetName());
				GuildInfo.clGuildInfo[siCount].siRemainTime = ( pcldstMap->m_dwInstanceMapStartTime + 30 * 60 * 1000 ) - pclClient->CurrentClock;
				GuildInfo.clGuildInfo[siCount].siScore = pcldstMap->m_siInstanceMapScore;
				GuildInfo.clGuildInfo[siCount].siGuildMarkIndex = pclGuildInfo->clGPoint.siMarkIndex;
				siCount++;
			}
		}
	}
    
	cltGameMsgResponse_InstantsDungeonStatus clInfo(GuildInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_STATUS, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

