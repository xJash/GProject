#include "..\Client\Client.h"
#include "Char\CharServer\Char-Server.h"

#include "Map\Map.h"
//-----------------------------
// Common
//-----------------------------
#include "..\Common\NPCManager\NPC.h"

#include "../common/Char/MonsterGroupManager/MonsterGroupManager.h"

#include "..\..\Order\Order.h"
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"

#include "../../../Server/Server.h"
#include "../../CommonLogic/CityHall/CityHall.h"

extern cltCommonLogic* pclClient;

// ��ó�� ���� ã�´�. 
bool cltCharServer::SearchEnemy(SI32 range)
{
	SI32 i, j;
	SI32 id;

	for(i = -range;i <= range;i++)
		for(j = -range;j <= range;j++)
		{
			id = pclMap->GetIDMap(GetX()+j, GetY()+i);


			if(IsEnemy(id) && CanAttack(id) )
			{
				cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

				if (clIdentity.siIdentity == IDENTITY_RACOONDODGE_EVENT ) // ���� �̺�Ʈ ���͸� ������ ���� 
				{
					cltCharServer* pclcharTarget = (cltCharServer*)pclCM->CR[id];
					SI32 siCharInMAp = pclcharTarget->GetMapIndex() ;

					if ( siCharInMAp = MAPINDEX_FESTIVAL) 
					{
						cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer( siCharInMAp )	;	// ��������
						if(pclmap != NULL)
						{
							SI32 siColl = pclmap->CalcCollInfo( pclcharTarget->GetX(), pclcharTarget->GetY())	;
							if( siColl & BLOCK_EVENT1 || siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ
							{
								OrderAttack(siID, id, BY_PLAYER);
								return true;
							}
							else
							{
								return false;
							}
						}
					}

				}
				else if (clIdentity.siIdentity == IDENTITY_BATTLEROYAL_MONSTER )
				{
					cltCharServer* pclTargetChar = (cltCharServer*)pclCM->GetCharServer(id);
					if( NULL == pclTargetChar)
						continue;
					SI32 siMapIndex = pclTargetChar->GetMapIndex();

					if( siMapIndex == MAPINDEX_BATTLEROYAL_MABRIUM || siMapIndex == MAPINDEX_BATTLEROYAL_GRANDMABRIUM)
					{
						OrderAttack(siID, id, BY_PLAYER);
						return true;
					}

				}
				else
				{
					if( pclKI->IsAtb(ATB_WEAKENEMYNOATTACK) || siCharMode == CHARMODE_BLACKWAR )// ���� ���� �������� �ʴ� �Ӽ��̸�, 
					{
						if(IsPC(pclchar->GetCharUnique()) && (pclchar->pclCI->clIP.GetLevel() < 20) )
						{
							continue;
						}	
					}

					// ����, ���, ä������ ĳ���ʹ� �������� �� �Ѵ�.
					if( ORDER_FISH == pclchar->GetCurrentOrder() ||
						ORDER_FARM == pclchar->GetCurrentOrder() ||
						ORDER_MINE == pclchar->GetCurrentOrder() )
					{
						continue;
					}

					//[�߰� : Ȳ���� 2008. 2. 18 ����������. ���� ����.]
					if( pclchar->pclCI->clBI.siHomeVillage > 0 )
					{
						cltServer*  pclserver = (cltServer*)pclClient;
						cltStrInfo* pclinfo   = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );
						if ( pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))) == TRUE )
						{	
							continue;
						}				
					}
				
					// ���� ������ �Ǿ� �ִ� ĳ���ʹ� �����Ѵ�. 
					if(pclchar->bNoFirstAttackSwitch == true)continue;
					if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK)) continue;

					if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI)) continue;
					
					if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_EVENT_EGGMOONCAKE )) continue;
					
					if(pclchar->pclCI->clBI.clBufInfo.IsHaveBufExecptGetType(BUF_TRANSFORM,BUF_GET_TYPE_NIGHTMARKET)) continue;
					
					// �����, ������ �漮 ���� ���� ���.
					if( (pclchar->GetCurrentOrder() == ORDER_SITDOWN )&&( pclchar->IsHaveCushionItem() > 0)  )	continue;

					//KHY - 1113 - ũ�������� �̺�Ʈ - ��������.
					if( pclchar && pclchar->m_siSetItemType == XMAS_SETITEM )	continue;

					// ���Ǳ��� ����� ĳ������ ��� - �Ϲ� ���λ��� ĳ���͵� �������� �ʴ´�.
					if( siCharMode == CHARMODE_BLACKWAR )
					{
						if(pclchar->bPersonalShopSwitch == true || pclchar->bPremiumPersonalShop == true)		continue;
					}

					// ���Ǳ��� ����� ĳ���Ͱ� �ƴѰ�� - �����̾� ���λ��� ĳ���͸� �������� �ʴ´�.
					if(pclchar->bPersonalShopSwitch == true && pclchar->bPremiumPersonalShop == true)			continue;

					// ���� ��ȯ���� ��� �ڽź��� ���ϸ� �������� �ʴ´�.
					if( pclchar->clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
					{
						if(clPB.GetBattlePower() > pclchar->clPB.GetBattlePower())
						{
							continue;
						}
						// [����] ��ȯ�� ���� ���� 
						if(pclchar->bNoFirstAttackSwitch == true)
						{
							continue;
						}
						// [����] ������ �����̾� ���� ���� ������ ��� ���� �Ұ�
						cltCharServer* pclParentChar = pclCM->GetCharServer(pclchar->GetSummonParentID());
						if( NULL != pclParentChar)
						{
							if( true == pclParentChar->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum)	continue;

							// [���] ������ �漮�� �ɾ� �ִ� ���¿����� ��ȯ�����׵� ���������� �ɸ���. (2009.09.23)
							if((pclParentChar->GetCurrentOrder() == ORDER_SITDOWN )&&( pclParentChar->IsHaveCushionItem() > 0))	
							{
								continue;
							}	
						}
					}

					if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
					{
						//[����] ��Ʈ ������ ���� ����.
						if( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK, USE_SETITEM_1 ) || 
							pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK, USE_SETITEM_2 ) ||
							pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK, USE_SETITEM_3 ) ||
							pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK, USE_SETITEM_4 ) ||
							pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_NO_FIRST_ATTACK, USE_SETITEM_5 ))
						{
							continue;
						}
					}
					// �� �����̾� ���� Ǯ������ Ư���ɷ� ����.
					//// �� Ǯ���� �϶� ���� ����
					//cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()	;
					//if ( pclHorse != NULL )
					//{
					//	if( pclHorse->GetPremiumPartsNum() == 3 )
					//	{
					//		SI32 siHorseUnique = pclHorse->siHorseUnique ;
					//		switch ( siHorseUnique )
					//		{
					//		case HORSEUNIQUE_TIGER :// ȣ����
					//		case HORSEUNIQUE_WOLF:// ����
					//		case HORSEUNIQUE_CAMEL:// ��Ÿ
					//		case HORSEUNIQUE_ELEPHANT:// �ڳ���
					//		case HORSEUNIQUE_MOTORCYCLE:// �������
					//		case HORSEUNIQUE_FIREHATCH:// ����ġ
					//			{
					//				continue	;
					//			}
					//			break;
					//		}
					//	}
					//}

					// ����� �����. 
					OrderAttack(siID, id, BY_PLAYER);
					return true;
				}
			}
		}

		return false;
}

// �����ϰ� �ֺ����� �̵��Ѵ�. 
bool cltCharServer::RandomMove()
{
	SI32 x, y;

	//return false;

	// �̵� �Ӽ��� ������ �̵����� �ʴ´�. 
	if(IsAtb(ATB_MOVE) == false)return false;

	//if ( GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_LIGHTSOLDIER")) )
	//{
	//	int temp = 0;
	//	temp++;
	//}

	SI32 npcgroup = GetNPCGroup();
	// NPCGroup�� ���� ���, 
	if(npcgroup >= 0)
	{
		// ���� ��ġ�� NPCGroup�������̸� Center�������� ����. 
		if(((cltServer*)pclClient)->IsInNPCGroup(npcgroup, GetMapIndex(), GetX(), GetY()) == false)
		{
			cltNPCGroup* pclnpcgroup = pclClient->GetNPCGroupPointer(npcgroup);
			if(pclnpcgroup)
			{
				x = pclnpcgroup->siX;
				y = pclnpcgroup->siY;

				// ����� �����. 
				OrderMove(siID, x, y, BY_PLAYER);
				return true;

			}

		}
		// ���� ��ġ�� NPCGroup�������̸� �����ϰ� ����. 
		else
		{
			x = GetX() + 5 - (rand() %11);
			y = GetY() + 5 - (rand() %11);

			// ����� �����. 
			if(pclMap->IsInMapArea(x, y) && IsColl(x, y) == false)
			{
				OrderStraightMove(siID, x, y, BY_PLAYER);
				return true;
			}
		}
	}
	// NPCGroup�� ������ ���� ���, 
	else
	{
		x = GetX() + 10 - (rand() %21);
		y = GetY() + 10 - (rand() %21);

		// ����� �����. 
		if(pclMap->IsInMapArea(x, y)  && IsColl(x, y) == false)
		{
			OrderStraightMove(siID, x, y, BY_PLAYER);
			return true;
		}
	}

	return false;

}

// ������ ���󰡰� �Ѵ�
bool cltCharServer::FollowGroupBoss(SI32 bossid)
{
	if ( !bossid ) return false ;
	if ( pclCM->IsAlive(bossid) == false ) return false ; // ������ �׾����� ������ �ʴ´�.

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[bossid];
	if ( pclchar == NULL ) return false ;

	SI32 length = max( TABS(pclchar->GetX() - GetX()) , TABS(pclchar->GetY() - GetY()) );
	SI32 x = pclchar->GetX() + 1 - (rand() % 3);
	SI32 y = pclchar->GetY() + 1 - (rand() % 3);

	// ����ġ�� ���� ������ ������ ���� ��Ų��. 
	if(length >= 8)
	{
		SI32 sx,sy ;
		if(pclchar->pclMap->FindEmptyAreaForCharLocate(GetKind(), x, y, 5, &sx, &sy, true) == true)
		{
			cltWarpInfo clinfo(true, pclchar->GetMapIndex(), false, false, sx, sy, -1, -1);
			clCharWarpInfo.Set(&clinfo);
			Warp();
		}
	}
	else if(length >= 4)
	{
		// �ڽſ��� �̵� ����� ������. 
		OrderMove(siID, x, y, BY_PLAYER);

		// �ڽ��� ������ �̿����� �̵��� �����Ѵ�. 
		cltOrderDataInfo clOrderDataInfo;
		if( pclClient->pclOrderManager->MakeOrder_MOVE(&clOrderDataInfo, x, y, BY_PLAYER) == true)
		{
			cltOrderData clOrderData;
			clOrderData.Make(GetCharUnique(), &clOrderDataInfo);

			cltMsg clMsg(GAMEMSG_RESPONSE_USERORDER, sizeof(clOrderData), (BYTE*)&clOrderData);
			SendNeighbourMsg(&clMsg, true);
			return true ;
		}
	}


	return false;
}

BOOL cltCharServer::OperateWaitServer()
{
	SI32 aniindex = 0;

	int i = 0, j = 0, k = 0;
	SHORT id = 0;

	//-------------------------------------------------
	// ����� ���� ���Ƽ�� �־��ٸ� �� ����� ���ش�. 
	//-------------------------------------------------
	if(bDeathPenaltySwitch	== true)
	{
		bDeathPenaltySwitch = false;
	}

	if(IsPC(CharUnique))return false;

	// ������ ���� ����� �ִ� ���Ͷ��, 
	if(pclKI->IsAtb(ATB_WAITSELFBOMB))
	{
		SelfBombAction();
		return true;
	}

	//===================================
	// NPC
	//===================================
	SI32 data = (rand() + siID) % (150 / CHAR_ACTION_INTERVAL_FRAME) ;

	if(data == 0)
	{   
		// ȣ������ ĳ������ ��� ���� ã�´�.
		SI32 range = 0;
		if(pclKI->siAggressive)	range = pclKI->siAggressive;
		switch(clIdentity.siIdentity) 
		{
		case IDENTITY_CASTLE:				range = 4;		break;
		case IDENTITY_VILLAGEGOD:			range = 4;		break;
		case IDENTITY_VILLAGEGOD_SUMMON:	range = 12;		break;	
		case IDENTITY_PERSON_SUMMON:		return true;	break;// ��ȯ���� idle�϶� ���� ���� ���� ���� �ʴ´�.
		case IDENTITY_VILLAGEHUNT:							break;
		case IDENTITY_BATTLEROYAL_MONSTER:	range = 20;		break;
			//case IDENTITY_SOULGUARD:			return true;	break;// ��ȣ �����϶��� �ƹ��� ���� ���ϵ��� �Ѵ�
		default:											break;
		}

		if(range)
		{
			if(SearchEnemy(pclKI->siAggressive) == true)		return true;
			if(clIdentity.siIdentity ==IDENTITY_PERSON_SUMMON)	return true;
		}

		// �����ؾ� �� ������ �ִ� ���, 
		if(siCharMode == CHARMODE_BLACKWAR)
		{
			// ������ ��ġ�� ã�´�.
			if( siCharModePara1 )
			{
				//SI32 x = pclClient->pclVillageManager->pclVillageInfo[siCharModePara1]->PosX;
				//SI32 y = pclClient->pclVillageManager->pclVillageInfo[siCharModePara1]->PosY;


			/*	// �� ��ġ�� ������ �ֺ��̶�� ���� ������ ����. 
				if(TABS(GetX() - x) <= 5 && TABS(GetY() - y) <= 5)
				{
				SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[ siCharModePara1 ]->siMapUnique;
				SI32 centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
				SI32 centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

				cltWarpInfo clinfo(true, siCharModePara1, false, false, centerx, centery, -1, -1);
				clCharWarpInfo.Set(&clinfo);
				Warp();
				} */
			}
			// �߿������� ���� ����. 
			else if(GetMapIndex() == 0)
			{
				// ���� �ֺ��� �ƴ϶�� �̵���Ų��. �ڱݼ����� �̵���Ų��.
				//OrderMove(siID, 288, 354, BY_PLAYER);

				// �����ϰ� �ֺ��� �̵��Ѵ�. - ���� �ֺ��� ��ȸ�ϴ� ������ �ϴ� ��� ���� - by LEEKH 2008-10-20
				if(RandomMove() == true)return true;

			/*	// �����ϰ� ������ ���� ã�´�.
				if(rand() % 50 == 0)
				{
					siCharModePara1 = pclClient->pclVillageManager->FindRandVillage();

					if(siCharModePara1)
					{
						// ������ ��ġ�� ã�´�.
						SI32 x = pclClient->pclVillageManager->pclVillageInfo[siCharModePara1]->PosX;
						SI32 y = pclClient->pclVillageManager->pclVillageInfo[siCharModePara1]->PosY;

						// ���� �ֺ��� �ƴ϶�� �̵���Ų��. 
						OrderMove(siID, x, y, BY_PLAYER);
					}
				}
				else
				{
					// �����ϰ� �ֺ��� �̵��Ѵ�. 
					if(RandomMove() == true)return true;
				}*/
			}
			else
			{
				// �����ϰ� �ֺ��� �̵��Ѵ�. 
				if(RandomMove() == true)return true;
			}
		}

		// ���ڸ����� ����ϴ� ������ �ƴ϶��, 
		if(bStaySwitch == false)
		{
			if(siGroupUnique)
			{
				// �׷��� �����̸�, 
				if(bGroupBossSwitch == TRUE)
				{
					// �����ϰ� �ֺ��� �̵��Ѵ�. 
					if(RandomMove() == true)return true;
				}
				else
				{
					// ������ ������.
					SI32 bossid = pclClient->pclMonsterGroupManager->GetBossID(siGroupUnique);
					if ( bossid )
					{
						if ( FollowGroupBoss(bossid) == true ) return true ;
					}
				}
			}
			else
			{
				// �����ϰ� �ֺ��� �̵��Ѵ�. 
				if(RandomMove() == true)return true;
			}
		}
	}
	// �ڵ� ġ��. 
	else if(data == 1)
	{
		HealAI();
	}
	// ���� 
	else if(data >= 2 && data < 10)
	{
		FishAI();
	}
	// ��� 
	else if(data >= 10 && data < 20)
	{
		FarmAI();
		MineAI();
	}
	else
	{
		// ���ڸ����� ����ϴ� ������ �ƴ϶��, 
		if(bStaySwitch == false)
		{
			if(siGroupUnique)
			{
				// �׷��� �����̸�, 
				if(bGroupBossSwitch == TRUE)
				{
					// �������� �������� �ִ��� Ȯ���Ͽ�  ��ġ�Ѵ�. 
					SI32 targetID = 0 ;
					if ( pclClient->pclMonsterGroupManager->FindBattleMember(&targetID,siGroupUnique,bGroupBossSwitch) == true )
						pclClient->pclMonsterGroupManager->MemberAttack(targetID,siGroupUnique);
				}
				else
				{
					// ������ ������.
					SI32 bossid = pclClient->pclMonsterGroupManager->GetBossID(siGroupUnique);
					if ( bossid )
					{
						if ( FollowGroupBoss(bossid) == true ) return true ;
					}
				}
			}
		}

	}



	return TRUE;
}

// �ΰ����� ����. 
void cltCharServer::FishAI()
{
	if(pclKI->IsAtb(ATB_FISH) == false)return ;

	// ��ȯ���� �ƴϸ� ����. 
	if(clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)return ;


	// ������ ���� ������ Ȯ���Ѵ�. 
	SI16 parentid = clIdentity.clSummonInfo.siParentCharUnique;
	if(pclCM->IsValidID(parentid) == false)return ;

	if(pclCM->CR[parentid]->GetCurrentOrder() != ORDER_FISH)return ;


	// ��ȯ���� ��ġ�� ���� ���� ��ġ���� Ȯ���Ѵ�. 
	SI32 dir = 0;
	if(IsFishArea(GetX(), GetY(), &dir) == true)
	{
		// ������ �����ϰ� �����. 
		OrderFish(GetID(), dir, BY_PLAYER);						
	}
	// ���� �Ұ��� ��ġ��� ��ġ�� ã�´�. 
	else
	{
		// ���� �ֺ��� ������ ���� ��ġ�� ã�´�.
		SI32 x, y;
		if(pclCM->CR[parentid]->FindFishArea(&x, &y) == true)
		{
			OrderMove(GetID(), x, y, BY_PLAYER);
		}
	}
}

// �ΰ����� ���
void cltCharServer::FarmAI()
{
	if(pclKI->IsAtb(ATB_FARM) == false)return ;

	// ��ȯ���� �ƴϸ� ����. 
	if(clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)return ;

	// �ڽ��� ������� �ƴϾ�� �Ѵ�. 
	if(GetCurrentOrder() == ORDER_FARM)return ;

	// ������ ��� ������ Ȯ���Ѵ�. 
	SI16 parentid = clIdentity.clSummonInfo.siParentCharUnique;
	if(pclCM->IsValidID(parentid) == false)return ;

	if(pclCM->CR[parentid]->GetCurrentOrder() != ORDER_FARM)return ;


	// ��ȯ���� ������� �Ѵ�. 
	OrderFarm(GetID(), pclCM->CR[parentid]->GetX(), pclCM->CR[parentid]->GetY(), BY_PLAYER);						
}

// �ΰ����� ä��
void cltCharServer::MineAI()
{
	if(pclKI->IsAtb(ATB_MINE) == false)return ;

	// ��ȯ���� �ƴϸ� ����. 
	if(clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)return ;

	// �ڽ��� ä������ �ƴϾ�� �Ѵ�. 
	if(GetCurrentOrder() == ORDER_MINE)return ;

	// ������ ä�� ������ Ȯ���Ѵ�. 
	SI16 parentid = clIdentity.clSummonInfo.siParentCharUnique;
	if(pclCM->IsValidID(parentid) == false)return ;

	if(pclCM->CR[parentid]->GetCurrentOrder() != ORDER_MINE)return ;


	// ��ȯ���� ä���ϰ� �Ѵ�. 
	OrderMine(GetID(), pclCM->CR[parentid]->GetX(), pclCM->CR[parentid]->GetY(), BY_PLAYER);

	return;
}