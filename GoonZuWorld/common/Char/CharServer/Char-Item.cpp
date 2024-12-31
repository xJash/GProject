#include "../Common/CommonHeader.h"
#include "../../Server/Server.h"

#include "char/CharServer/Char-Server.h"

#include "../../Client/Music/Music.h"

#include "Msg/MsgType-Party.h"
#include "Msg/MsgType-Feast.h"
#include "MsgType-System.h"
#include "Msg/MsgType-Village.h"
#include "Msg/MsgType-Fishing.h"
#include "Msg/MsgType-Agriculture.h"
#include "Msg/MsgType-HappyBeanQuest.h"

#include "../Common/Bullet/Bullet.h"
#include "../Common/Order/Order.h"
#include "../common/GameEvent/GameEvent.h"
#include "../common/Item/ItemCommon/Item-BookBox.h"
#include "../CharManager/CharManager.h"
#include "../CommonLogic/BoxItemMgr/BoxItemMgr.h"

#include "Util/Util.h"
#include "Skill/Skill-Manager.h"

#include "Guild/Guild.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Guild.h"

//--------------------------------------
// Server
//--------------------------------------
#include "Statistics/Statistics.h"

#include "../Common/PartyMgr/PartyObj.h"
#include "../Common/PartyMgr/PartyMgr.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Fishing.h"
#include "../../DBManager/GameDBManager_World/DBMsg-SoulGuard.h"
#include <MsgType-Person.h>
#include <MsgType-Item.h>
#include <MsgType-System.h>
#include <Msg/MsgType-ItemMall.h>
#include <Msg/MsgType-Fishing.h>
#include "MsgRval-Define.h"

#include "../Common/Fishing/FishingMgr.h"

#include "Char-Item.h"

extern cltCommonLogic* pclClient;


// ����Ǿ� �ִ� ��� ������ ó���� �Ѵ�. 
void cltCharServer::ItemUseReserveAction()
{
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))return;

	if(clItemUseReserveInfo.IsReserved() == false)return;

	// DB�� ����Ǿ� �ִ� �������� �����϶�� ��û�Ѵ�. 
	for(SI32 i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		SI32 unique		=  clItemUseReserveInfo.clInfo[i].siUnique;
		SI32 itemnum	=  clItemUseReserveInfo.clInfo[i].siItemNum;
		SI32 pos		=  clItemUseReserveInfo.clInfo[i].siItemPos;
		clItemUseReserveInfo.clInfo[i].Init();

		if(unique == 0)continue;

		cltItem clitem;

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(unique);
		if(ref <= 0)continue;

		// �������� �Ҹ��� ��. 
		if(itemnum < 0)
		{

			clitem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
			clitem.siItemNum = -itemnum;

			if (pos < 0)
				pos = pclCI->clCharItem.FindItemInv(&clitem, false);

			if(pos >= 0)
			{
				sDBRequest_UseItem clMsg(GetID(), pclCI->GetPersonID(), pos, &clitem,USEITEM_REASON_NONE);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
		// �������� ������ų ��. 
		else if(itemnum > 0)
		{
			clitem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
			clitem.siItemNum = itemnum;

			if (pos < 0)
				pos = pclCI->clCharItem.FindItemInv(&clitem, false);

			if(pos >= 0)
			{
				// ����ڿ��� �������� �ִ� �޽����� ����Ѵ�. 
				sDBRequest_InputItemToPerson clMsg(GetID(), pclCI->GetPersonID(), pos, INPUTITEMPERSON_OPTION_NONE, clitem.CanPile(pclClient->pclItemManager), &clitem, 0, clitem.IsCreateSID(pclClient->pclItemManager));
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}	
}

// ����Ǿ��ִ� ȭ�� �� źȯ�� �Һ��Ѵ�.
void cltCharServer::BulletUseReserveAction()
{
	SI32 siCharUnique = GetCharUnique();

	// ����� �ɸ��� �϶���
	if ( false == IsPC(GetCharUnique()) )
	{
		return;
	}


	// �ɸ��� �������� ����Ǿ� ������
	if ( true == clBulletUseReserveInfo.IsReserved() )
	{
		BulletUseReserveAction_ForPerson();
	}

	// �ɸ��Ͱ� ���� �ִ� ��ȯ���� �������� ����Ǿ� ������
	if ( true == clSummonBulletUseReserveInfo.IsReserved() )
	{
		BulletUseReserveAction_ForSummon();
	}

}

void cltCharServer::BulletUseReserveAction_ForPerson()
{
	for(SI32 i = 0;i < MAX_USEITEM_RESERVE_NUM;i++)
	{
		SI32 unique		=  clBulletUseReserveInfo.clInfo[i].siUnique;
		SI32 itemnum	=  clBulletUseReserveInfo.clInfo[i].siItemNum;
		SI32 pos		=  clBulletUseReserveInfo.clInfo[i].siItemPos;
		clBulletUseReserveInfo.clInfo[i].Init();

		if(unique == 0)continue;

		cltItem clitem;

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(unique);
		if(ref <= 0)continue;

		// �������� �Ҹ��� ��. 
		if(itemnum < 0)
		{
			clitem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
			clitem.siItemNum = -itemnum;

			if(pos >= 0)
			{
				sDBRequest_UseItem clMsg(GetID(), pclCI->GetPersonID(), pos, &clitem,USEITEM_REASON_NONE);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}	

}

void cltCharServer::BulletUseReserveAction_ForSummon()
{
	for ( SI32 siIndex=0; siIndex<MAX_USEITEM_RESERVE_NUM; siIndex++ )
	{
		SI16 siSummonIndex	= clSummonBulletUseReserveInfo.m_clInfo[ siIndex ].m_siSummonIndex;
		SI16 siItemUnique	= clSummonBulletUseReserveInfo.m_clInfo[ siIndex ].m_siItemUnique;
		SI16 siItemNum		= clSummonBulletUseReserveInfo.m_clInfo[ siIndex ].m_siItemNum;
		SI16 siItemPos		= clSummonBulletUseReserveInfo.m_clInfo[ siIndex ].m_siItemPos;


		if ( (0 > siSummonIndex) || (0 >= siItemUnique) || (0 <= siItemNum) || (0 > siItemPos) )
		{
			continue;
		}

		cltSummon* pclsummon = pclCI->clSummonInfo.GetSummon( siSummonIndex );
		if( pclsummon == NULL )			continue;

		SI32 siRef = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
		if ( 0 >= siRef )
		{
			continue;
		}

		cltItem clItem;

		clItem.Set( &pclClient->pclItemManager->pclItemInfo[ siRef ]->clItem );
		clItem.SetItemNum( (-siItemNum) );

		sDBRequest_SummonUseItem clMsg( GetID(), pclCI->GetPersonID(), pclsummon->siSummonID, siItemPos, &clItem, SUMMONUSEITEM_REASON_GENERAL );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	clSummonBulletUseReserveInfo.Init();

}

// ��ȯ���� ĳ���� ���� �����Ѵ�.
SI32 cltCharServer::CreateSummon(cltSummon* pclSummon)
{
	cltServer* pclserver = (cltServer*)pclClient;
	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;

	if( pclSummon == NULL )	return	0	;

	SI32 siSummonKind = pclSummon->siKind;
	//=========================================================================
	// �ش� ���Ͱ� �ɼ� �ִ��� �˻��Ѵ�.
	//=========================================================================
	//if(pclClient->pclKindInfoSet->pclKI[siSummonKind]->IsAtb(ATB_SUMMON) == FALSE)
	if(siSummonKind < 0 || siSummonKind >= MAX_KINDINFO_NUMBER)	return 0;
	cltKindInfo*	pclKI = NULL;
	if( pclClient->IsCountrySwitch(Switch_Summon_Separate) )
	{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[siSummonKind];	}
	else
	{	pclKI = pclClient->pclKindInfoSet->pclKI[siSummonKind];			}

	if(pclKI == NULL)					return 0;
	if(pclKI->siSummonRank <= 0)
	{
		return 0;
	}

	SI32 siSummonIndex = pclCI->clSummonInfo.GetSummonIndexFromSummonID(pclSummon->siSummonID);
	if ( siSummonIndex < 0 )	return	0	;

	SI32 serverminutevary = pclClient->GetMinuteFromsTime(pclserver->sTime);

	BOOL bCanTakeOut = FALSE;

	// PCK : ���� ��ȯ���� ��� �ð��� ������� ���¹̳ʰ� 0�̸� ��ȯ���� �ʴ´�.
	if( pclKI->IsAtb(ATB_SUMMONSTAMINASTATIC) )
	{
		if( pclSummon->clIP.GetLuk() <= 0 )
		{
			((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMON_NEEDCHARGESTAMINA,  0, 0, GetCharUnique());
			return 0;
		}
	}
	else
	{
		if(	pclSummon->clIP.GetLuk() <= 0 && 
			TABS(pclSummon->siTakeInMinute - serverminutevary) < SUMMON_TAKEOUT_DELAY)
		{
			((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMON_FAIL_TAKEOUTDELAY,  0, 0, GetCharUnique());
			return 0;
		}
	}

	//=========================================================================
	// DOLL �������� �ش� Monter Kind�� ���� ������ ��ȯ�Ѵ�.
	//=========================================================================
	SI32 siSummonsX, siSummonsY;
	if(pclMap->FindEmptyAreaForCharLocate(siSummonKind, GetX(), GetY(), 20, &siSummonsX, &siSummonsY, true) == true)
	{
		//// ���ĸ��� �̺�Ʈ ���������� ĳ���� ��ġ�� ������ ��ȯ�Ѵ�. - by LEEKH
		//if(pclMap->siMapIndex == MAPINDEX_MOFUMOFULAND)
		//{
		//	siSummonsX = GetX();
		//	siSummonsY = GetY();
		//}
		// �̺�Ʈ ���̶� ��ȯ���� ���� ���� �ϵ��� �Ѵ�.[����]
		cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(GetMapIndex());
		if(pclmap != NULL)
		{
			SI32 siColl = pclmap->CalcCollInfo( GetX(), GetY())	;
			if(siColl & BLOCK_EVENT4|| siColl & BLOCK_EVENT5 || siColl & BLOCK_EVENT6)
			{
				siSummonsX = GetX();
				siSummonsY = GetY();
			}
		}

		if(pclMap->siMapIndex == MAPINDEX_MOFUMOFULAND) // Ȥ�� ���� ��� �д�.
		{
			siSummonsX = GetX();
			siSummonsY = GetY();
		}

		cltIdentity clIdentity;
		clIdentity.MakeSummon(IDENTITY_PERSON_SUMMON, siSummonIndex, GetCharUnique(), pclCI->GetPersonID());

		cltInnerStatusInfo clinnerstatus;
		clinnerstatus.clEnemyType.Set(&clInnerStatus.clEnemyType);		// ������ ���� ������ ����Ѵ�. 


		SI32 siSummonID = pclserver->SetNPCChar(siSummonKind, 
			pclCI->clBI.siHomeVillage,  
			&clIdentity, 
			1, 
			pclSummon->clIP.GetLife(), 
			siSummonsX, 
			siSummonsY, 
			GetMapIndex(), 
			NPCITEMMODE_NONE, 
			&clinnerstatus );
		if(pclCM->IsValidID(siSummonID))
		{
			// ��ȯ������������� ������� ���������� �����ؾ��Ѵ�.

			// �߿� ������ ������Ʈ �Ѵ�. 
			pclserver->pclCM->CR[ siSummonID ]->pclCI->clIP.Set(&pclSummon->clIP);

#ifdef _SAFE_MEMORY
			SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclCI->clCharItem.clItem[0], siID );
#else
			SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, pclCI->clCharItem.clItem, siID );
#endif
			if (pclSummon->clIP.GetLuk() <= 0)
				pclserver->pclCM->CR[ siSummonID ]->pclCI->clIP.SetLuk(pclClient->GetMaxStaminaValue(summonskill, pclSummon->siKind));
			else	
				pclserver->pclCM->CR[ siSummonID ]->pclCI->clIP.SetLuk(pclSummon->clIP.GetLuk());

			pclserver->pclCM->CR[ siSummonID ]->SetUpdateSwitch(UPDATE_IP, true, 0);

			pclserver->pclCM->CR[ siSummonID ]->ParametaBoxAction();

			// ü�°� �������� �������ش�. 
			pclserver->pclCM->CR[ siSummonID ]->SetLife(pclSummon->clIP.GetLife());
			pclserver->pclCM->CR[ siSummonID ]->SetMana(pclSummon->clIP.GetMana());
			return siSummonID;
		}
	}

	return 0;
}

SI32 cltCharServer::CreateSoulGuard( cltSoulGuard* pclCreateSoulGuard )
{
	if ( NULL == pclCreateSoulGuard )
	{
		return 0;
	}

	if ( NULL == pclSoulGuard )
	{
		return 0;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return 0;
	}

	if ( NULL == pclserver->m_pclSoulGuardMgr )
	{
		return 0;
	}

	SI32 siSoulGuardKind = pclCreateSoulGuard->GetKind();
	if ( (0 > siSoulGuardKind) || (MAX_KINDINFO_NUMBER <= siSoulGuardKind) )
	{
		return 0;
	}

	SI32 siMyX			= GetX();
	SI32 siMyY			= GetY();

	SI32 siSoulGuardX	= 0;
	SI32 siSoulGuardY	= 0;

	// ��ȯ�� ��ġ�� ã�ƾ� �Ѵ�
	if ( false == pclMap->FindEmptyAreaForCharLocate(siSoulGuardKind, siMyX, siMyY, 20, &siSoulGuardX, &siSoulGuardY, true) )
	{
		return 0;
	}

	// ���ΰ��� �̺�Ʈ ������ ������ ���ΰ� ��ġ�� ������ �ش�
	cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer(GetMapIndex());
	if ( NULL != pclmap )
	{
		SI32 siCollInfo = pclmap->CalcCollInfo( siMyX, siMyY );
		if ( (BLOCK_EVENT4 & siCollInfo) || (BLOCK_EVENT5 & siCollInfo) || (BLOCK_EVENT6 & siCollInfo) )
		{
			siSoulGuardX = siMyX;
			siSoulGuardY = siMyY;
		}
	}

	// ���﷣���϶��� ������ ������ ��ġ�� �־��ش�
	if ( MAPINDEX_MOFUMOFULAND == pclMap->siMapIndex )
	{
		siSoulGuardX = siMyX;
		siSoulGuardY = siMyY;
	}

	// ��ȣ���ɿ� �ʿ��� �⺻ ���������� �Է��Ѵ�
	cltIdentity clSoulGuardIdentity;
	clSoulGuardIdentity.MakeSoulGuard( IDENTITY_SOULGUARD, GetCharUnique(), pclCI->GetPersonID() );

	cltInnerStatusInfo clSoulGuardInner;
	clSoulGuardInner.Init();

	// ���� ��ȣ���� ����
	SI32 siSoulGuardID = pclserver->SetNPCChar( siSoulGuardKind,		pclCI->clBI.siHomeVillage,
		&clSoulGuardIdentity, 
		1,						1,
		siSoulGuardX,			siSoulGuardY,				GetMapIndex(),
		NPCITEMMODE_NONE,
		&clSoulGuardInner
		);
	if ( false == pclCM->IsValidID(siSoulGuardID) )
	{
		return 0;
	}

	// ��ȣ������ �����ִ� �ɷ��� �̸� ������ �ش�
	SI32 siHaveAbility = pclserver->m_pclSoulGuardMgr->GetHaveAbility( siSoulGuardKind );

	pclSoulGuard->SetHaveAbility( siHaveAbility );

	// ��ȯ�� ���·� ����
	pclSoulGuard->SetStatus( SOULGUARD_STATUS_OUT );

	return siSoulGuardID;
}

void cltCharServer::DeleteSoulGuard( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	if ( NULL == pclSoulGuard )
	{
		return;
	}

	if ( false == pclserver->pclCM->IsValidID(siMySoulGuardUnique) )
	{
		return;
	}

	cltCharServer* pclSoulGuardChar = pclserver->pclCM->GetCharServer( siMySoulGuardUnique );
	if ( NULL == pclSoulGuardChar )
	{
		return;
	}

	if ( IDENTITY_SOULGUARD !=  pclSoulGuardChar->clIdentity.siIdentity )
	{
		return;
	}

	if ( pclCI->GetPersonID() != pclSoulGuardChar->clIdentity.clSoulGuard.m_siParentPersonID )
	{
		return;
	}

	// ���� ��ȣ������ �����Ѵ�
	pclSoulGuardChar->DeleteInCell();
	pclserver->pclCM->DeleteChar( siMySoulGuardUnique );

	// ���� ���� �ִ� ��ȣ���� ���� ����
	pclSoulGuard->SetStatus( SOULGUARD_STATUS_IN );

	siMySoulGuardUnique = 0;

}

// �������� ����Ѵ�. 
bool cltCharServer::UseItem(cltItem clitem,SI32 itempos)
{
	cltItemManagerCommon* pclItemManager;
	pclItemManager = pclClient->pclItemManager;

	SI32 siRealItemUniques[MAX_ITEM_UNIQUE];
	SI32 siRealItemCount = 0;

	// �������� ����� �� ���� ���̸� , 
	SI32 returnval = 0;
	if(CanUseItem(clitem, &returnval, itempos) == false)return false;

	cltServer* pclserver = (cltServer*)pclClient;

	if( true == bPersonalShopSwitch ||
		true == bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( clShopData.m_clItem[i].siUnique == clitem.siUnique  )
			{
				//KHY - 1023 - �Ѿ� ȭ�� ���ѻ�� ����.
				if(( clShopData.m_clItem[i].siUnique != ITEMUNIQUE( 7850 ))&& ( clShopData.m_clItem[i].siUnique != ITEMUNIQUE( 7855 )) )
				{
					if( clShopData.m_clItem[i].siItemNum >= clitem.siItemNum )
					{
						//	SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, GetID());
						return false;
					}
				}
			}
		}
	}

	SI32 itemunique = clitem.siUnique;
	SI32 ref		= pclItemManager->FindItemRefFromUnique(itemunique);
	if(ref <= 0)return false;

	SI32 itemtype	= pclItemManager->pclItemInfo[ref]->siType;
	GMONEY itematb	= pclItemManager->pclItemTypeInfo[itemtype]->siAtb;

	if(pclItemManager->pclItemInfo[ref]->IsItemInfoAtb(ITEMINFOATB_CANUSEITEM)  == false)return false;

	//	cltServer* pclserver = (cltServer*)pclClient;

	// ������� �ȿ��� ȸ������ ����� ���
	if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������
	{
		if( IsGuildWarMap_Use_New_GuildWar(GetMapIndex()) )	// ���� ������� ������
		{
			if( itemunique == ITEMUNIQUE( 2565 ) ||
				itemunique == ITEMUNIQUE( 2570 ) ||
				itemunique == ITEMUNIQUE( 2575 ) ||
				itemunique == ITEMUNIQUE( 2580 ) ||
				itemunique == ITEMUNIQUE( 2585 ) || 
				// ����ȸ������ �߰�
				itemunique == ITEMUNIQUE( 2590 ) ||
				itemunique == ITEMUNIQUE( 2595 ) ||
				itemunique == ITEMUNIQUE( 2600 ) ||
				itemunique == ITEMUNIQUE( 2605 ) 
				)
			{
				SI32 fieldindex =	0	;
				if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������
				{
					fieldindex =  GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( GetMapIndex() );
				}
				else	// ������
				{
					fieldindex = GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( GetMapIndex() );
				}
				if ( pclserver->IsCountrySwitch( Switch_NewGuildHuntMapWar ))	// ������
				{
					if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM_OLD &&
						pclserver->pclGuildWarManager[fieldindex]->CanDrinkPotion(pclCI->GetPersonID()) )
					{
						pclserver->pclGuildWarManager[fieldindex]->DrinkPotion( pclCI->GetPersonID() );
					}
					else
					{
						return false;
					}
				}
				else	// ������ 
				{
					if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM &&
						pclserver->pclGuildWarManager[fieldindex]->CanDrinkPotion(pclCI->GetPersonID()) )
					{
						pclserver->pclGuildWarManager[fieldindex]->DrinkPotion( pclCI->GetPersonID() );
					}
					else
					{
						return false;
					}

				}
			}
		}


	}
	else	// ������
	{
		if( IsGuildWarMap_Not_Use_New_GuildWar(GetMapIndex()) )	// ���� ������� ������
		{
			if( itemunique == ITEMUNIQUE( 2565 ) ||
				itemunique == ITEMUNIQUE( 2570 ) ||
				itemunique == ITEMUNIQUE( 2575 ) ||
				itemunique == ITEMUNIQUE( 2580 ) ||
				itemunique == ITEMUNIQUE( 2585 ) || 
				// ����ȸ������ �߰�
				itemunique == ITEMUNIQUE( 2590 ) ||
				itemunique == ITEMUNIQUE( 2595 ) ||
				itemunique == ITEMUNIQUE( 2600 ) ||
				itemunique == ITEMUNIQUE( 2605 ) 
				)
			{
				SI32 fieldindex =	0	;
				if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ������
				{
					fieldindex =  GetGuildWarFieldIndexFromMapIndex_Use_New_Guild_War( GetMapIndex() );
				}
				else	// ������
				{
					fieldindex = GetGuildWarFieldIndexFromMapIndex_Not_Use_New_Guild_War( GetMapIndex() );
				}
				if ( pclserver->IsCountrySwitch( Switch_NewGuildHuntMapWar ))	// ������
				{
					if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM_OLD &&
						pclserver->pclGuildWarManager[fieldindex]->CanDrinkPotion(pclCI->GetPersonID()) )
					{
						pclserver->pclGuildWarManager[fieldindex]->DrinkPotion( pclCI->GetPersonID() );
					}
					else
					{
						return false;
					}
				}
				else	// ������ 
				{
					if ( fieldindex >= 0 && fieldindex < GUILDWAR_FIELDNUM &&
						pclserver->pclGuildWarManager[fieldindex]->CanDrinkPotion(pclCI->GetPersonID()) )
					{
						pclserver->pclGuildWarManager[fieldindex]->DrinkPotion( pclCI->GetPersonID() );
					}
					else
					{
						return false;
					}

				}
			}
		}
	}
	switch(itemtype)
	{
		//==============================================================================================================================
		// DOLL
		//==============================================================================================================================
	case ITEMTYPE_DOLL:
		{
			// ��ȯ�� �������� DB�� ������̹Ƿ� ����
			if(bIsNowAddSummonThroughDB)		{		return false;		}

			//------------------------------
			// �������� 
			//------------------------------
			bool bsuccess = false;
			if(itemunique == ITEMUNIQUE(12000))		// ������ 
			{
				if(rand() % 100 < HATCH_SUMMON_PERCENT)
				{
					bsuccess = true;
				}
			}
			else
			{
				bsuccess = true;
			}

			if(bsuccess)
			{
				cltServer* pclserver = (cltServer*)pclClient;

				SI32 siSummonKind = 0, preturn = 0, siSummonIndex = 0;
				if(CanUseSummonDoll(itemunique, &siSummonKind, &siSummonIndex, &preturn) == true)
				{
					//--------------------------------
					// ��ȭ���� ��ȯ�� Kind�� �����Ѵ�.
					//--------------------------------
					if(siSummonKind <= 0 || siSummonKind >= MAX_KIND_NUMBER)	return false;

					//====================================================
					// ���� ������� ��ȯ���� �����Ѵ�. - �⺻���� ����
					//====================================================
					cltPIPInfoCommon	clipinfo;
					cltPIPInfo			clipinfo2;

					//[����] ��ȯ�� ���̺� �и� �� ���� ��ȯ�� ���� ���� ����. => 2008-6-18
					cltKindInfo* pclki = NULL;
					cltGMCommandKindInfo* pclGMki = NULL;

					if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
					{
						pclki = pclClient->pclKindInfoSet->pclSummonKI[siSummonKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[siSummonKind];
					}
					else
					{
						pclki = pclClient->pclKindInfoSet->pclKI[siSummonKind];
						pclGMki = pclClient->pclKindInfoSet->pclGMCommandKindInfo[siSummonKind];
					}
					if(NULL == pclki)
						break;

					clipinfo.SetBasicAbility(&pclki->clBA);	
					clipinfo2.Set(&clipinfo);

					// ��ȯ�� �ɷ�ġ ����
					cltParametaBox clPB;
					clPB.Init(pclClient->pclItemManager, &clipinfo2, NULL, pclki, pclGMki);
					clPB.Action(NULL, 0, PERSONITEM_WEAPON1, NULL, NULL, NULL, NULL, NULL, NULL, GAMEMODE_SERVER, true, false);

					//cyj ��ȯ���� Luk�� ���¹̳ʷ� ���
#ifdef _SAFE_MEMORY
					SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclCI->clCharItem.clItem[0], siID );
#else
					SI32 summonskill = pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, pclCI->clCharItem.clItem, siID );
#endif
					// ��ȯ�� ���׹̳� ����
					clipinfo.SetLuk( pclClient->GetMaxStaminaValue(summonskill, siSummonKind) );
					clipinfo.SetLife(clPB.GetMaxLife());	
					clipinfo.SetMana(clPB.GetMaxMana());

					cltSummonScroll clscroll(pclki->siSummonScroll[0], 0, pclki->siSummonScroll[1], 0);

					SI32 siSummonStatus = 0;
					if ( pclClient->IsCountrySwitch(Switch_SummonHouse) )
					{
						// �����ҷ� �ٷ� ���Ƿ� ���´� TAKEIN�̴�.
						siSummonStatus = SUMMON_STATUS_TAKEIN;
					}
					else
					{
						if(GetSummonID())	siSummonStatus = SUMMON_STATUS_TAKEIN;
						else				siSummonStatus = SUMMON_STATUS_TAKEOUT;
					}

					// ��ȯ�� �̸� ����
					TCHAR* pText = GetTxtFromMgr(449);
					TCHAR summonname[MAX_PLAYER_NAME] = TEXT("");
					StringCchCopy(summonname, MAX_PLAYER_NAME, pText);

					SI08 siIdentity = SUMMON_IDENTITY_NORMAL;

					cltSummonItemInfo clItemInfo;
					clItemInfo.Init();

					SI32 siTransformKind    = 0;
					SI32 siTransformAbility = 0;
					if( pclClient->IsCountrySwitch( Switch_SummonTramsform ) )
					{
						pclserver->GetSummonTransformManager()->GetTransformSummonInfo( siSummonKind, siTransformKind, siTransformAbility );					
					}
					// DB�� ��ȯ���� �����Ѵ�.
					cltSummon clSummon(	0,
						siSummonKind,
						summonname,
						siSummonStatus,
						SUMMON_ATTACKTYPE_AVOID,
						siIdentity,
						0,
						0,
						0,
						&clipinfo,		
						&clscroll,
						0
						);

					// Switch_SummonHouse ����ġ�� ����������, siSummonIndex �� 0 ~ 6 ����
					// Switch_SummonHouse ����ġ�� ����������, siSummonIndex �� 0 ~ 2 ����
					SendDBSummon(SETSUMMON_REASON_MAKE, siSummonIndex, &clSummon);

					// Ŭ���̾�Ʈ�� ����� �˸���.
					((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMONSUCCESS,  0, 0, GetCharUnique());

					//-------------------------------------
					// ��ȯ���� ��ȯ���̹Ƿ� ���� ��ȯ���� ��ȯ��Ű�� ���ϰ� �Ѵ�.
					//-------------------------------------
					bIsNowAddSummonThroughDB = true;

				}
				else
				{
					return false;
				}
			}
			else
			{
				// Ŭ���̾�Ʈ�� ����� �˸���. 
				((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMONHATCHFAIL,  0, 0, GetCharUnique());
			}
		}
		break;

		//==============================================================================================================================
		// BOOK
		//==============================================================================================================================
	case ITEMTYPE_BOOK:
		{	
			//[����] ��ų��.
			if( pclClient->pclItemManager->IsItemInfoAtb( clitem.siUnique, ITEMINFOATB_SKILLBOOK ) )
			{
				static cltSkillBookManager*	pclSkillBookManager = pclClient->pclItemManager->pclSkillBookManager;
				if( NULL == pclSkillBookManager ) return false;

				// ��ų�� �����̸�.(���������� �ƴϴ�)
				if( 0 >= pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( clitem.siUnique ) )
				{
					cltSkillBookMagic clAddSkillBookMagic( 0, 0, &pclserver->sTime );
					switch( GetAttackType() )
					{
					case ATTACKTYPE_SWORD:		clAddSkillBookMagic.SetSkillUnique(SKILL_USESWORD1);	break;
					case ATTACKTYPE_SPEAR:		clAddSkillBookMagic.SetSkillUnique(SKILL_USESPEAR1);	break;
					case ATTACKTYPE_AXE:		clAddSkillBookMagic.SetSkillUnique(SKILL_USEAXE1);		break;
					case ATTACKTYPE_STAFF:		clAddSkillBookMagic.SetSkillUnique(SKILL_USESTAFF1);	break;
					case ATTACKTYPE_STAFF1:		clAddSkillBookMagic.SetSkillUnique(SKILL_USESTAFF1);	break;
					case ATTACKTYPE_STAFF2:		clAddSkillBookMagic.SetSkillUnique(SKILL_USESTAFF1);	break;
					case ATTACKTYPE_NEW_STAFF2:	clAddSkillBookMagic.SetSkillUnique(SKILL_USESTAFF1);	break;
					case ATTACKTYPE_BOW:		clAddSkillBookMagic.SetSkillUnique(SKILL_USEBOW1);		break;
					case ATTACKTYPE_BOW1:		clAddSkillBookMagic.SetSkillUnique(SKILL_USEBOW1);		break;
					case ATTACKTYPE_NEW_BOW1:	clAddSkillBookMagic.SetSkillUnique(SKILL_USEBOW1);		break;
					case ATTACKTYPE_GUN:		clAddSkillBookMagic.SetSkillUnique(SKILL_USEGUN1);		break;
					case ATTACKTYPE_GUN1:		clAddSkillBookMagic.SetSkillUnique(SKILL_USEGUN1);		break;
					case ATTACKTYPE_NEW_GUN1:	clAddSkillBookMagic.SetSkillUnique(SKILL_USEGUN1);		break;
					default:					return false;
					}

					clAddSkillBookMagic.SetMagicKind( pclSkillBookManager->GetSkillBookMagicFromItemUnique( clitem.siUnique ) );
					if( 0 >= clAddSkillBookMagic.GetMagicKind() ) return false;

					SI08 siIndex = pclCharSkillBookInfo->GetIndexFromAttackType( GetAttackType() );
					if( 0 > siIndex ) return false;

					sDBRequest_SkillBook_Magic_Add	clMsg( GetID(), pclCI->GetPersonID(), siIndex, &clAddSkillBookMagic );
					pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
				}
				// ���� ����.
				else
				{
					if( pclClient->pclItemManager->pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( clitem.siUnique ) )
					{
						SI32 skilllevel  = pclCI->clCharSkill.GetTotalSkillLevel( clitem.GetSkillUnique( pclItemManager ), 0, 0 );
						SI32 skilllimit  = clitem.GetSkillLevelLimit( pclClient->pclItemManager );
						if( skilllevel < skilllimit ) return false;
					}

					SI32 siMagicKind		= pclSkillBookManager->GetSkillBookMagicFromItemUnique( clitem.siUnique );
					SI32 siParentMagicKind	= pclSkillBookManager->GetSkillBookParentMagicFromItemUnique( clitem.siUnique );

					if( 0 >= siMagicKind || 0 >= siParentMagicKind ) return false;

					SI32 skillunique = clitem.GetSkillUnique( pclItemManager );
					cltSkillBookSubMagic clSkillBookSubMagic( skillunique, siParentMagicKind, siMagicKind, &pclserver->sTime );

					sDBRequest_SkillBook_SubMagic_Add	clMsg( GetID(), pclCI->GetPersonID(), &clSkillBookSubMagic );
					pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
				}


				// ��ų�� ����ϱ� ����Ʈ ���̶��
				IncQuestPara(QUEST_CLEAR_COND_USE_SKILLBOOK, 1, clitem.siItemNum);
			}
			else
			{
				//----------------------------------
				// ��ų�� ������ Ȯ���Ѵ�.
				//----------------------------------
				SI32 skillunique	= clitem.GetSkillUnique(pclClient->pclItemManager);
				SI32 maxskilllevel	= pclClient->pclSkillManager->GetMaxLevel(skillunique);
				SI32 siDecreaseSkillPoint = 1;

				// ����Ȱ��ȭ : ������ ���õ� å�� ��ų ���ʽ� ����Ʈ�� �Ҹ����� �ʴ´�. by LEEKH 2007.07.30
				//if(	pclClient->IsWhereServiceArea(ConstSwitch_ManufactureRevitalize) && 
				if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
					pclClient->pclSkillManager->IsManufactureSkill(skillunique))
				{
					siDecreaseSkillPoint = 0;
				}

				sDBRequest_IncreaseSkill clMsg(GetID(), pclCI->GetPersonID(), skillunique, 1, maxskilllevel, siDecreaseSkillPoint, clitem);
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
		break;

		//==============================================================================================================================
		// FOOD
		//==============================================================================================================================
	case ITEMTYPE_FOOD:
	case ITEMTYPE_SEAFOOD:
		{
			cltServer* pclserver = (cltServer*)pclClient;

			// ���̾�Ʈ ���� ��Ȱ �� ��Ʈ.
			if( itemunique == ITEMUNIQUE(3937) )
			{
				if( 80 > rand()%100 ) 
				{
					SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.

					SI16 siPercent = 1;
					stBuf* pstBuf = pclCI->clBI.clBufInfo.GetBuf( BUF_GIANTRACCOON_RESURRECT_EVENT );
					if( pstBuf )
					{
						siPercent = pstBuf->siPercent;
						switch( siPercent )
						{
						case 1:   
						case 2:	
						case 3:	
						case 4:	siPercent++;					break;
						case 5:	siPercent = pstBuf->siPercent;	break;
						}
					}

					SI16 index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_GIANTRACCOON_RESURRECT_EVENT );
					if( index > -1 )
					{
						stBuf DelBuf( BUF_GIANTRACCOON_RESURRECT_EVENT, 0, 0, 0 );
						sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), index, &DelBuf );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
					else
					{
						// ���ο� �������� �� �� �ε��� ���.
						index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_GIANTRACCOON_RESURRECT_EVENT, false );		
					}

					if( index > -1 )
					{
						// ������ �ش�.
						stBuf addBuf( BUF_GIANTRACCOON_RESURRECT_EVENT, siPercent, usetime );
						AddBufThroughDB( index, &addBuf , false, 0, NULL, 0 );
					}
				}
				else
				{
					((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_GIANTRACCOONRESURRECTEVENT_FAIL_USE_ITEM, 0, 0, GetID() );	
				}
			}
			//cyj �ػ����� ���
			else if( itemunique == ITEMUNIQUE(3860) || itemunique == ITEMUNIQUE(3865) || itemunique == ITEMUNIQUE(3870))
			{
				if ( bIsSetPremium ) return false ;
				if ( pclCI->clBI.bPremiumService ) return false ;
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ; 
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP ) ) return false;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS ) ) return false;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP ) ) return false;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300 ) ) return false;

				SI32 usedate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() + 2 ;
				sDBRequest_SetPremium clPremium(GetCharUnique(),pclCI->GetPersonID(),true,usedate, 0, 0, 0, 0, &clitem,itempos,SETPREMIUM_EXP);
				((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clPremium);		
				bIsSetPremium = true ;
				// �������������� �ٸ� ���� ȿ���� ������ ����!!!
				return false ;

			}
			// [�߰� : Ȳ���� 2007. 11. 12.  �߼� ������ �̺�Ʈ. ĥ���� �丮 ���.]
			else if(itemunique == ITEMUNIQUE(3911))
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				SI32 usetime =  0;
				usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 15 ;// 30�а����				
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_THANKSGIVING_DAY, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_THANKSGIVING_DAY, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			// ������ ����
			else if( itemunique == ITEMUNIQUE(3903) )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS ) ) return false ; 

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_NOTBONUSTIME_MAKEEXPUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_NOTBONUSTIME_MAKEEXPUP, 50, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );

				}
				// ���� ����� �ٸ� ���� ȿ���� ������ ����!!!
				return false;
			}
			// ���� ����
			else if( itemunique == ITEMUNIQUE(3880) )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS ) ) return false ; 

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_MAKEEXPUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_MAKEEXPUP, 50, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );

				}
				// ���� ����� �ٸ� ���� ȿ���� ������ ����!!!
				return false;
			}
			//cyj �������� ����
			else if( itemunique == ITEMUNIQUE(3875))
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ; 
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_MAKEEXPUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_MAKEEXPUP, 20, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false;
			}
			// ����� ���ݸ�
			else if( itemunique == ITEMUNIQUE(3890)  || itemunique == ITEMUNIQUE(3899) )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300) ) return false ;	// ����� ����

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_LOVEPOWER, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_LOVEPOWER, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;			
			}
			// ������ ���ݸ�
			else if( itemunique == ITEMUNIQUE(3895) || itemunique == ITEMUNIQUE(3901) )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300) ) return false ;	// ����� ����

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_FRIENDSHIP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_FRIENDSHIP, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;	
			}
			// ��������
			else if( itemunique == ITEMUNIQUE(3897) )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300) ) return false ;	// ����� ����

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_HINAMOCHI, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_HINAMOCHI, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;	
			}
			//ä���� ���� ������ 
			else if( itemunique == ITEMUNIQUE(3918)|| itemunique == ITEMUNIQUE(3919) || itemunique == ITEMUNIQUE(3920))
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false;
				//1���� ���� 7���� ���� 30���� ���̸� ��� ���� ���� ���� ����� ��,
				SI32 usetime =  0;
				//�������� ������ ���� ���� �ٸ� �ð��� �ش�.
				if( itemunique == ITEMUNIQUE(3918))	// ���ǽð�  1�� =  30 * 720 = 21600  / 30 �ð�   ����????
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 720 ;
				else if( itemunique == ITEMUNIQUE(3919) )	// ���ǽð� 15�� = 30 * 24 = 720 /2 �ð�  30 * 720 = 21600/2 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 5040 ;
				else if( itemunique == ITEMUNIQUE(3920) )	// ���ǽð� 30�� = 30 * 24 = 720�ð�  30 * 720 = 21600 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;
				else
					return false ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_FARMINGNMININGFOREVER, true );
				if ( index > -1 )
				{
					stBuf addBuf(BUF_FARMINGNMININGFOREVER, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			//----------------------------------------------------------------------------------
			// [����] ����ü�� ������.
			//       - ����ϸ� ���� ����ȿ�� �߿��� �������� 48�а� ���� �� �ִ� ��ȸ�� ������.
			//----------------------------------------------------------------------------------
			else if( itemunique == ITEMUNIQUE(3926) )	
			{
				// �ش�������� �κ��� ���� �� �ִ��� Ȯ��
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				//����ü�� ������ �ɷ������� �� ������ �����Ѵ�.
				SI16 index0 = -1;

				index0 = pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_RUMBLECHERRY);
				{
					if( index0 > -1) // ������ ������쿡
					{
						// ������ �ɷ��ִ� ������ �����Ѵ�.
						stBuf DelBuf( pclCI->clBI.clBufInfo.m_stBuf[index0].siBufType, 0, 0, 0 );
						sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), index0, &DelBuf );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
				}

				// �⺻ ���� ���¸� ã�� �����Ѵ�.
				SI16 IsHaveBufType[12] = 
				{
					BUF_PREMIUMEXPUP,			// ����ġ 150% ȹ�氡��. (������)
						BUF_ATTACKUP,				// ���ݷ� 20% ����.
						BUF_DEFENSEUP,				// ���� 20% ����.

						BUF_MAKEEXPUP,				// ���� ����ġ 150% ����.
						BUF_NOFIRSTATTACK,			// ���� ���� ȿ��.
						BUF_SUCCESS_MANUFACTURE,	// ������ ���� 100% ���� ȿ��. (���� �Ѹ���)

						BUF_FOURLEAF,				// ����ũ�ι�(������ȹ�� *2) ȿ��.
						BUF_LOVEPOWER,				// ����� ĵ�� ȿ�� - ����/���� ����ġ 150% ����, ��ȯ�����׹̳� ���� ȿ��, ��ȯ�� ������ ����.
						BUF_FRIENDSHIP,				// ������ ĵ�� ȿ�� - ����/���� ����ġ 120% �� ��, ���ݷ�/���� 120% ����.

						BUF_HINAMOCHI,				// ���κ��� ����ũ ȿ�� - ����/���� ����ġ 200% ����, ���ݷ�/���� 120% ���, ��������.
						BUF_SUMMONATACUP,			// ��ȯ�� ������ ȿ�� - ��ȯ�� ���ݷ�, ���� 20% ����.
						BUF_FARMINGNMININGFOREVER   // ���� ȿ�� - ���, ä���� ������ ���� ����.
				};

				// ��� ��
				SI16 BufCreateRate_Const[12] = 
				{
					50,
						150,
						150,

						80,
						110,
						120,

						10,
						30,
						30,

						20,
						150,
						100
				};

				// ����ġ�� �����ϴ� ������ ������ ���� �� 
				// DB����->ĳ���ͱ⺻����.������������.�������ִ¹���()
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) )
				{
					IsHaveBufType[0] = 0;
					BufCreateRate_Const[0] = 0;
				}

				// ���ݷ� ����.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||
					pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP30) )
				{
					IsHaveBufType[1] = 0;
					BufCreateRate_Const[1] = 0;
				}
				// ���� ����.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||
					pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP30) )
				{
					IsHaveBufType[2] = 0;
					BufCreateRate_Const[2] = 0;
				}

				// ���� ����ġ ����.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MAKEEXPUP) )
				{
					IsHaveBufType[3] = 0;
					BufCreateRate_Const[3] = 0;
				}

				// ���� ���� ȿ��.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )
				{
					IsHaveBufType[4] = 0;
					BufCreateRate_Const[4] = 0;
				}

				// ���� �Ѹ���.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUCCESS_MANUFACTURE) )
				{
					IsHaveBufType[5] = 0;
					BufCreateRate_Const[5] = 0;
				}

				// ����ũ�ι� ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF) )
				{
					IsHaveBufType[6] = 0;
					BufCreateRate_Const[6] = 0;
				}

				// ����� ĵ�� ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) )
				{
					IsHaveBufType[7] = 0;
					BufCreateRate_Const[7] = 0;
				}

				// ������ ĵ�� ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) )
				{
					IsHaveBufType[8] = 0;
					BufCreateRate_Const[8] = 0;
				}

				// ���κ��� ����ũ ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) )
				{
					IsHaveBufType[9] = 0;
					BufCreateRate_Const[9] = 0;
				}

				// ��ȯ�� ������ ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP) )
				{
					IsHaveBufType[10] = 0;
					BufCreateRate_Const[10] = 0;
				}

				// ���� ȿ��.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FARMINGNMININGFOREVER) )
				{
					IsHaveBufType[11] = 0;
					BufCreateRate_Const[11] = 0;
				}

				SI16 BufRateConstTotal = 0;		// ������� �� ��.

				//������� ���� ���Ѵ�.
				for( int j = 0; j < 12; j++)
				{
					BufRateConstTotal = BufRateConstTotal + BufCreateRate_Const[j];
				}

				SI16 SelectedValue = 0;								//��� ���� ��ŭ�� ������ �ϳ��� ���� ����

				SelectedValue = rand() % BufRateConstTotal +  1;	//�������� ������ ( 1 ~ �������)

				//���� ���� � ������ Ȯ���� ���ԵǴ��� �˱� ���� ������� ���ʷ� �����ذ��� üũ�Ѵ�.
				SI16 tmpConstTotal = 0;

				for( int k = 0; k < 12; ++k)
				{
					tmpConstTotal  = tmpConstTotal + BufCreateRate_Const[k];
					if( SelectedValue <= tmpConstTotal) // ���õ� ���� ������ ������ ������� ������ ���Եȴٸ�.
					{
						//� ������ ���;� �ϴ��� ������ �ε����� ������ ���� ����.
						SelectedValue = k; // ����� ���� �ε���!
						break;
					}
				}

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( IsHaveBufType[SelectedValue], false );


				SI16 siPercent = 0; //Ÿ�Կ� ���� ����.


				switch(IsHaveBufType[SelectedValue])
				{
				case BUF_MAKEEXPUP:
					siPercent = 50;
					break;
				case BUF_ATTACKUP:
				case BUF_DEFENSEUP:
				case BUF_SUMMONATACUP:	
					siPercent = 20;
					break;
				case BUF_PREMIUMEXPUP:
				case BUF_NOFIRSTATTACK:						
				case BUF_SUCCESS_MANUFACTURE:
				case BUF_FOURLEAF:
					siPercent = 0;						
					break;
				}

				if( index > -1 ) // ������ ������
				{
					stBuf addBuf(IsHaveBufType[SelectedValue], siPercent , usetime, BUF_GET_TYPE_RUMBLECHERRY);
					AddBufThroughDB( index, &addBuf , true, itempos, &clitem);
				}
				return false;
			}

			//[�߰� : ���� ���ϵ� ���� �̺�Ʈ�� ��������� �̿�, Ȳ���� 2007.9.18]
			// �������� ���������� �̺�Ʈ��(���پ�����) �ܿ��� ���� �� ���� �������̹Ƿ� ���� �ڵ� ����.
			else if( itemunique == ITEMUNIQUE(3730))
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 ItemUnique = 0;	
				ItemUnique = GetUniqueWithRange( ItemUnique_3730_ItemNum, sizeof(ItemUnique_3730_ItemNum) / sizeof(cltUniqueRange), 100);

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				switch(ItemUnique)
				{
				case 15900: usedate = 30;	break;		// ����	7�Ϸ� �Ǿ��־ 30�Ϸ� ����
				case 18110: usedate = 7;	break;		// ��������
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				SI32 ItemCnt = 0;
				switch(ItemUnique)
				{
				case 5620:	ItemCnt = 1;	break;
				case 24040: ItemCnt = 5;	break;
				case 15900: ItemCnt = 1;	break;
				case 18110: ItemCnt = 1;	break;
				case 2575:	ItemCnt = 30;	break;
				case 2580:	ItemCnt = 15;	break;
				case 24015: ItemCnt = 2;	break;
				case 24000: ItemCnt = 5;	break;
				}
				clDrawItem.SetItemNum( ItemCnt );

				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}

				return false;	
			}
			// [���] ���ڹ���
			else if(itemunique == ITEMUNIQUE(3927))
			{
				if ( itempos <= 0 || itempos  >= MAX_ITEM_PER_PERSON)	return false;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.

				SI16 Index = pclCI->clBI.clBufInfo.FindBufSlot(BUF_WATERMELON);
				if(0 > Index)
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_WATERMELON, false);	

				// ������ ���� ������ �ɷ������� �����ش�.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_WATERMELON) )
				{
					stBuf DelBuf( pclCI->clBI.clBufInfo.m_stBuf[Index].siBufType, 0, 0, BUF_WATERMELON );
					sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), Index, &DelBuf );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					// ���Ӱ� �ٽ� �ð��� ������ �ش�.
					stBuf addBuf(BUF_WATERMELON, 0, usetime);
					AddBufThroughDB( Index, &addBuf , true , itempos , &clitem );
				}
				else
				{
					stBuf addBuf(BUF_WATERMELON, 0, usetime);
					AddBufThroughDB( Index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			else if( ITEMUNIQUE(3928) == itemunique )
			{
				if ( NULL == pclSoulGuard )
				{
					return false;
				}

				if ( TRUE == pclSoulGuard->IsEmpty() )
				{
					return false;
				}

				SI16 siSetFellowShip = pclSoulGuard->GetFellowShip() + 10;
				if ( Const_Max_SoulGuard_FellowShip < siSetFellowShip )
				{
					siSetFellowShip = Const_Max_SoulGuard_FellowShip;
				}

				// ĳ���� ���� ������ �ְ�
				pclSoulGuard->SetFellowShip( siSetFellowShip );

				// DB�� ������
				sDBRequest_SoulGuard_FellowShipSet clMsg( pclCI->GetPersonID(), pclSoulGuard->GetSoulGuardID(), pclSoulGuard->GetFellowShip() );
				pclserver->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

			}
			// PCK : �߽��� ���� �߰�(�������, Ÿ�ھ߳�, ��������, �ػ���, ����ġ, �ٳ���ť - 09.08.04)
			// 1. �������
			else if( itemunique == ITEMUNIQUE(3934) )
			{
				// �ƶ�����Ʈ Ʈ���ɶ�� ���� ����Ʈ ���� �߿��� �߽��� ���� ����� �� �ֵ��� �������� �ּ�ó��.
				//if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS) ) return false;

				SI32 id = GetID(); 

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[7];
				SI16		siPercent[7];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FRUITBROS");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FROKEN");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FROZENKNIGHT");
				siPercent[siCharTransCount] = 150;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FROZENSORCERER");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_ICEHOUND");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_MARIONETTE");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FROZENQUEEN");
				siPercent[siCharTransCount] = 50;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				Index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );				

				// ������ ���� ������ �ɷ������� �����ش�.
				if( -1 >= Index )
				{
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);	
				}

				stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
				AddBufThroughDB( Index, &addBuf , true, itempos, &clitem);

				return false;
			}
			// 2. Ÿ�ھ߳� (���� ���Ǹ� �� �ϳ��� ����)
			else if( itemunique == ITEMUNIQUE(3931)  )
			{
				// �ƶ�����Ʈ Ʈ���ɶ�� ���� ����Ʈ ���� �߿��� �߽��� ���� ����� �� �ֵ��� �������� �ּ�ó��.
				//if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS) ) return false;

				SI32 id = GetID();

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[13];
				SI16		siPercent[13];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_PYEONGGANG");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_ONDAL");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_NINJAMAN");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_NINJAGIRL");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CATMELEE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CATRANGE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE");
				siPercent[siCharTransCount] = 80;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_OCTOPUS");
				siPercent[siCharTransCount] = 40;
				if(siCharKind[siCharTransCount] > 0 && siCurKind != siCharKind[siCharTransCount])	siCharTransCount++;

				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				Index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );				

				// ������ ���� ������ �ɷ������� �����ش�.
				if( -1 >= Index )
				{
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);	
				}

				stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
				AddBufThroughDB( Index, &addBuf , true, itempos, &clitem);
				return false;
			}
			// 3. ��������
			else if( itemunique == ITEMUNIQUE(3930) )
			{
				// �ƶ�����Ʈ Ʈ���ɶ�� ���� ����Ʈ ���� �߿��� �߽��� ���� ����� �� �ֵ��� �������� �ּ�ó��.
				//if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS) ) return false;

				SI32 id = GetID();

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[7];
				SI16		siPercent[7];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_MUSHROOM");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_WILDBOAR");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CATFISH");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_SHARK");
				siPercent[siCharTransCount] = 150;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_STONECOW");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_RACCOONDOG");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_OTOHIME");
				siPercent[siCharTransCount] = 50;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;


				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				Index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );				

				// ������ ���� ������ �ɷ������� �����ش�.
				if( -1 >= Index )
				{
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);	
				}

				stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
				AddBufThroughDB( Index, &addBuf , true, itempos, &clitem);

				return false;
			}
			// 4. �ػ��� (Ż���� �ܰ��� �������� �ٲ�)
			else if( itemunique == ITEMUNIQUE(3929))
			{
				SI32 id = GetID();

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[20];
				SI16		siPercent[20];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM_HORSE))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM_HORSE);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = HORSEUNIQUE_BROWN;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_BLACK;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_WHITE;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_RED;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_RUDOLF;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_TIGER;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_THOUSAND;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_STEEL;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_WOLF;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_ZEBRA;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_BEAST;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_FOAL;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_CAMEL;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_TIGER2;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_ELEPHANT;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_WHITETIGER;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_MOTORCYCLE;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_FIREHATCH;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = HORSEUNIQUE_WHITE_TEST;
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				//siCharKind[siCharTransCount] = HORSEUNIQUE_BAPHOMET;
				//siPercent[siCharTransCount] = 47;
				//if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_RACCOON");
				siPercent[siCharTransCount] = 47;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				SI16 siIndexTransForm = -1;

				Index			 = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM_HORSE );				
				siIndexTransForm = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );

				cltHorse* pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if( pclHorse == NULL || pclHorse->siHorseUnique <= 0 )
				{
					return false;
				}

				// ������ ���� ������ �ɷ��ְų� ���� ź���°� �ƴϸ� �ػ��� ����� ���Ѵ�.
				if( siIndexTransForm > -1 || pclClient->pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == false)
				{
					return false;
				}

				// ������ �ɸ��� �������� �ƴ� ĳ���� ������ �Ѵ�.
				if( siKind == pclClient->GetUniqueFromHash("KIND_RACCOON") )
				{
					// �������� �ɸ� ���¶�� �������� Ǯ�� ���� ������ �Ѵ�.
					if(Index > -1)
					{
						stBuf DelBuf( pclCI->clBI.clBufInfo.m_stBuf[Index].siBufType, 0, 0, BUF_TRANSFORM_HORSE );
						sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), Index, &DelBuf );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

						siIndexTransForm = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);

						// ���Ӱ� �ٽ� �ð��� ������ �ش�.
						stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
						AddBufThroughDB( siIndexTransForm, &addBuf , true, itempos, &clitem );
					}
					else
					{
						siIndexTransForm = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);

						// ���Ӱ� �ٽ� �ð��� ������ �ش�.
						stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
						AddBufThroughDB( siIndexTransForm, &addBuf , true, itempos, &clitem);
					}
				}
				else
				{
					if( -1 >= Index )
					{
						Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM_HORSE, false);	
					}

					stBuf addBuf(BUF_TRANSFORM_HORSE, siKind, usetime);
					AddBufThroughDB( Index, &addBuf, true, itempos, &clitem);
				}

				return false;
			}
			// 5. ����ġ
			else if( itemunique == ITEMUNIQUE(3932))
			{
				// �ƶ�����Ʈ Ʈ���ɶ�� ���� ����Ʈ ���� �߿��� �߽��� ���� ����� �� �ֵ��� �������� �ּ�ó��.
				//if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS) ) return false;

				SI32 id = GetID();

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[7];
				SI16		siPercent[7];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_TIGER");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_COW");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_LADYBUG");
				siPercent[siCharTransCount] = 200;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_RABBIT");
				siPercent[siCharTransCount] = 150;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_HARPY");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_WILDCAT");
				siPercent[siCharTransCount] = 100;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_MANDRAGORA");
				siPercent[siCharTransCount] = 50;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				Index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );				

				// ������ ���� ������ �ɷ������� �����ش�.
				if( -1 >= Index )
				{
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);	
				}

				stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
				AddBufThroughDB( Index, &addBuf , true, itempos, &clitem);

				return false;
			}
			// 6. �ٳ���ť
			else if( itemunique == ITEMUNIQUE(3933) )
			{
				// �ƶ�����Ʈ Ʈ���ɶ�� ���� ����Ʈ ���� �߿��� �߽��� ���� ����� �� �ֵ��� �������� �ּ�ó��.
				//if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS) ) return false;

				SI32 id = GetID();

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24;		//���ǽð� 48�а�

				SI32		siCurKind = 0;
				SI16		siCharKind[6];
				SI16		siPercent[6];
				SI32		siCharTransCount = 0;
				SI32		siKind = 0;

				if(pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
				{
					stBuf* pclBuf = pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
					if(pclBuf)
					{
						siCurKind = pclBuf->siPercent;
					}
				}

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_BEARTANG");
				siPercent[siCharTransCount] = 190;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_SUPERBEARTANG");
				siPercent[siCharTransCount] = 190;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_CATPET");
				siPercent[siCharTransCount] = 190;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_RUDOLPHPET");
				siPercent[siCharTransCount] = 190;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_MINEGIRL");
				siPercent[siCharTransCount] = 190;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				siCharKind[siCharTransCount] = pclClient->GetUniqueFromHash("KIND_COSMOSRABBIT2");
				siPercent[siCharTransCount] = 50;
				if(siCharKind[siCharTransCount] > 0 )	siCharTransCount++;

				SI32 siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];
				}

				SI32 siRand = rand() % siTotalPercent;
				SI32 siSelected = -1;
				siTotalPercent = 0;

				for(SI32 i=0; i<siCharTransCount; i++)
				{
					siTotalPercent += siPercent[i];		
					if( siRand < siTotalPercent )
					{
						siSelected = i;
						break;
					}
				}

				siKind = siCharKind[siSelected];

				SI16 Index = -1;
				Index = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );				

				// ������ ���� ������ �ɷ������� �����ش�.
				if( -1 >= Index )
				{
					Index = pclCI->clBI.clBufInfo.FindEmptySlot(BUF_TRANSFORM, false);	
				}

				stBuf addBuf(BUF_TRANSFORM, siKind, usetime, BUF_GET_TYPE_NIGHTMARKET);
				AddBufThroughDB( Index, &addBuf , true, itempos, &clitem);

				return false;
			}

			// ���� �������� ���, 
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 1)
			{
				// ���� ������ ����� �� ����. 
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if( pclhorse == NULL || pclhorse->siHorseUnique < 0 || 
					pclhorse->siHorseUnique == HORSEUNIQUE_WOLF )
				{
					return false;
				}

				// �� ���̸� �ش�. 
				if(pclClient->pclHorseManager->GiveFood(pclhorse, &clitem) == true)
				{
					// Ŭ���̾�Ʈ�� �� ������ �����Ѵ�. 
					SetUpdateSwitch(UPDATE_HORSE, true, 0);

					// DB�� �����Ѵ�. 
					UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

					DoQuestCheckAndAction(QUEST_CLEAR_COND_FEEDHORSE1);
				}
			}
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 2)
			{
				// ���� ������ ����� �� ����. 
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if( pclhorse == NULL || pclhorse->siHorseUnique < 0 || 
					pclhorse->siHorseUnique == HORSEUNIQUE_WOLF )
				{
					return false;
				}

				// �� ���̸� �ش�. 
				if(pclClient->pclHorseManager->GiveFood(pclhorse, &clitem) == true)
				{
					// Ŭ���̾�Ʈ�� �� ������ �����Ѵ�. 
					SetUpdateSwitch(UPDATE_HORSE, true, 0);

					// DB�� �����Ѵ�. 
					UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

					DoQuestCheckAndAction(QUEST_CLEAR_COND_FEEDHORSE1);
				}
			}
			else if(pclItemManager->pclItemInfo[ref]->siHorseFoodSwitch == 3)
			{
				// ���� ������ ����� �� ����. 
				cltHorse* pclhorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if( pclhorse == NULL || pclhorse->siHorseUnique < 0 || 
					pclhorse->siHorseUnique == HORSEUNIQUE_WOLF )
				{
					return false;
				}

				// �� ���̸� �ش�. 
				if(pclClient->pclHorseManager->GiveFood(pclhorse, &clitem) == true)
				{
					// Ŭ���̾�Ʈ�� �� ������ �����Ѵ�. 
					SetUpdateSwitch(UPDATE_HORSE, true, 0);

					// DB�� �����Ѵ�. 
					UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

					DoQuestCheckAndAction(QUEST_CLEAR_COND_FEEDHORSE2);
				}
			}
			else if ( pclItemManager->pclItemInfo[ref]->bFishingBaitSwitch == true )
			{
				// ��� �Ұ��� ��� return false �ϸ� ��.

				// ��ó�� ������ ���� ���ٸ� ����� �� ����.				
				SI32 dir = 0;
				if(IsFishArea(GetX(), GetY(), &dir) == true)
				{
					SI16 FishKindListRef = pclClient->pclFishingMgr->IsAvailableBait( clitem.siUnique );

					if ( FishKindListRef < 0)
					{
						FishingStop();
						return false;
					}

					// �ش� �����Ϳ��� ���̴� ������ ���� �̳��� ���ؼ� ���� ���� ������ ���ø� ���� �ʴ´�. (PCK : 08.04.03)

					if( pclClient->IsCountrySwitch( Switch_FishFarmMineChange ) )
					{
						cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

						SI32 XPos = pclchar->pclCI->clBI.GetX();
						SI32 YPos = pclchar->pclCI->clBI.GetY();
						SI16 FishKindList[MAX_FISHKIND_NUMBER];
						memset( FishKindList, 0, sizeof( SI16 ) * MAX_FISHKIND_NUMBER );
						SI16 Counter = 0;

						for ( SI16 i = 0; i < MAX_FISHKIND_NUMBER; ++i )
						{
							if ( pclClient->pclFishingMgr->m_pFishKindList[i] != NULL )
							{
								if(pclClient->pclFishingMgr->m_pFishKindList[i]->IsAvailableGainFish(XPos,YPos))
								{
									++Counter;
									FishKindList[Counter] = pclClient->pclFishingMgr->m_pFishKindList[i]->GetFishItemUnique();
								}

								if(pclClient->pclFishingMgr->m_pFishKindList[i]->IsSameFishItemUnique(FishKindList[Counter]) == TRUE)
								{
									if(pclClient->pclFishingMgr->m_pFishKindList[i]->IsAvailableBait(clitem.siUnique) == FALSE)
									{
										FishingStop();

										// �̳��� ������ ���� ������ �޽����� �ٸ��� �����Ѵ�.
										if (clitem.siUnique == ITEMUNIQUE(16010))	// ��������
										{
											((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHNOTBAITSHRIMP, ITEMUNIQUE(16140), 0, GetCharUnique());
											return FALSE;
										}
										else if (clitem.siUnique == ITEMUNIQUE(16140))	// ����
										{
											((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_FISHNOTBAITLUGWORM, ITEMUNIQUE(16010), 0, GetCharUnique());
											return FALSE;
										}
									}
								}
							}
						}

						if(Counter <= 0)
						{
							FishingStop();
							((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_NOPROPERFISHAREA, 0, 0, GetCharUnique());
							return FALSE;
						}
					}
					else
					{
						//[����] ���̸� �ƹ��������� ���� ��尡 �Ǵ°� ����. ���ҽ����� �������� Ȯ��. => 2008-9-4
						SI16 Counter = 0;
						for ( SI16 i = 0; i < MAX_FISHKIND_NUMBER; ++i )
						{
							if ( pclClient->pclFishingMgr->m_pFishKindList[i] != NULL )
							{
								if( pclClient->pclFishingMgr->m_pFishKindList[i]->IsAvailableGainFish( GetX(), GetY() ) )
								{
									++Counter;
								}
							}
						}

						if(Counter <= 0)
						{
							FishingStop();
							((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_NOPROPERFISHAREA, 0, 0, GetCharUnique());
							return FALSE;
						}
					}

					if ( ! IsAvailableFishing( clitem.siUnique, FishKindListRef ) )
					{
						FishingStop();
						return false;
					}

					// ���� ������ ���� ��� ���� ���� üũ
					DBToolInfo clFishingToolList[ MAX_FISHING_TOOL_NUMBER ];

					for ( SI16 kk = 0; kk < MAX_FISHING_TOOL_NUMBER; ++kk )
					{
						clFishingToolList[ kk ].Init();
					}

					if ( ! GetFishingToolInfo( FishKindListRef, clFishingToolList ) )
					{
						FishingStop();
						return false;
					}						

					// �̳��� �� ���������� �ϰ� ���ø� �Ѵ�.
					siFishingBaitItemUnique = clitem.siUnique;

					// ���ô� ������ ���� �ٷ� �� ���� �ð� ���� �����..
					dwPreCatchFishClock = pclClient->CurrentClock;

					// ���� ������ �������� ���� �帰��.
					sDBRequest_FishingDecreaseToolDurability dbMsg( pclCI->GetPersonID(), GetID(), clFishingToolList );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&dbMsg);

					cltGameMsgResponse_FishingStart clMsgResponse_FishingStart( siFishingBaitItemUnique, clFishingToolList );
					cltMsg clMsg( GAMEMSG_RESPONSE_FISHINGSTART, sizeof( clMsgResponse_FishingStart ), (BYTE*)&clMsgResponse_FishingStart );
					SendNetMsg((sPacketHeader*)&clMsg );

					// ������ �����ϰ� �����. 
					OrderFish(GetID(), dir, BY_PLAYER);						
				}
				else
				{
					// Ŭ���̾�Ʈ�� ����� �˸���. 
					((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_NOPROPERFISHAREA,  0, 0, GetCharUnique());
					return false;
				}					
			}
			else
			{

				SI32 max = MAXORG(pclCI->clIP.GetLevel());
				UI32 hungryrecover = clitem.GetHungry(pclClient->pclItemManager);

				//------------------------------------
				// ������� ���� ����. 
				//------------------------------------
				bool bnormalswitch = false; 
				if(clPB.clHealth.GetHungryStatus(pclCI->clIP.GetLevel()) & (HEALTH_STATUS_HUNGRY_NORMAL|HEALTH_STATUS_HUNGRY_7|HEALTH_STATUS_HUNGRY_8|HEALTH_STATUS_HUNGRY_9))
				{
					bnormalswitch = true;
				}

				// �������� ȸ�������ش�.
				clPB.clHealth.IncreaseHungry(hungryrecover);

				// ��ȭ����� ������ �ش�. 
				if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty)
				{
					if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty < 0 || bnormalswitch)
					{

						SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg1Penalty / 10;
						SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg1Penalty) % 10;

						pclCI->clHealthInfo.IncreaseInnerOrg1(penalty);

						if((rand() % 10) < modul)
						{
							if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty > 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg1(1);
							}
							if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty < 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg1(-1);
							}
						}

						// �ִ밪 ������ ����� �ʴ´�. 
						if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG1) > max)
						{
							pclCI->clHealthInfo.siInnerOrg1 = max;
						}
						else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG1) < -max)
						{
							pclCI->clHealthInfo.siInnerOrg1 = -max;
						}

						SetUpdateSwitch(UPDATE_HEALTH, true, 0);
					}
				}

				// ��ȯ����� ������ �ش�. 
				if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty)
				{
					if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty < 0 || bnormalswitch)
					{
						SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg2Penalty / 10;
						SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg2Penalty) % 10;

						pclCI->clHealthInfo.IncreaseInnerOrg2(penalty);

						if((rand() % 10) < modul)
						{
							if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty > 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg2(1);
							}
							if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty < 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg2(-1);
							}
						}

						// �ִ밪 ������ ����� �ʴ´�. 
						if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG2) > max)
						{
							pclCI->clHealthInfo.siInnerOrg2 = max;
						}
						else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG2) < -max)
						{
							pclCI->clHealthInfo.siInnerOrg2 = -max;
						}

						SetUpdateSwitch(UPDATE_HEALTH, true, 0);
					}
				}
				// ȣ������ ������ �ش�. 
				if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty)
				{
					if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty < 0 || bnormalswitch)
					{

						SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg3Penalty / 10;
						SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg3Penalty) % 10;

						pclCI->clHealthInfo.IncreaseInnerOrg3(penalty);

						if((rand() % 10) < modul)
						{
							if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty > 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg3(1);
							}
							if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty < 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg3(-1);
							}
						}

						// �ִ밪 ������ ����� �ʴ´�. 
						if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG3) > max)
						{
							pclCI->clHealthInfo.siInnerOrg3 = max;
						}
						else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG3) < -max)
						{
							pclCI->clHealthInfo.siInnerOrg3 = -max;
						}


						SetUpdateSwitch(UPDATE_HEALTH, true, 0);
					}
				}
				// �Ű����� ������ �ش�. 
				if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty)
				{
					if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty < 0 || bnormalswitch)
					{

						SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg4Penalty / 10;
						SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg4Penalty) % 10;

						pclCI->clHealthInfo.IncreaseInnerOrg4(penalty);

						if((rand() % 10) < modul)
						{
							if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty > 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg4(1);
							}
							if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty < 0)
							{
								pclCI->clHealthInfo.IncreaseInnerOrg4(-1);
							}

						}

						// �ִ밪 ������ ����� �ʴ´�. 
						if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG4) > max)
						{
							pclCI->clHealthInfo.siInnerOrg4 = max;
						}
						else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG4) < -max)
						{
							pclCI->clHealthInfo.siInnerOrg4 = -max;
						}


						SetUpdateSwitch(UPDATE_HEALTH, true, 0);
					}
				}


				SI16 questtype, unique ,para1, para2;

				if( pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_HUNGRY ,&questtype, &unique, &para1, &para2 ))
				{
					if( clitem.siUnique == para1 && 
						questtype >= 0 && questtype < MAX_QUEST_TYPE )   // ����Ʈ �����۰� �� �� ��θ� ����Ʈ ����
					{
						pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 = 1;
						SetUpdateSwitch(UPDATE_QUEST, true, 0);
					}
				}				

				// Ŭ���̾�Ʈ���� ���� ����� �谡 �ҷ����� �뺸�Ѵ�. 
				cltGameMsgResponse_IncHungry clInfo(clitem.siUnique, clPB.clHealth.pclInfo->siHungry);
				cltMsg clMsg(GAMEMSG_REPONSE_INCHUNGRY, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		break;

		//==============================================================================================================================
		// HEAL
		//==============================================================================================================================
	case ITEMTYPE_HEAL:
		{
			//[����] ������ ����� �׳� ��Ŭ������ ��� ���ϰ� ����.
			if( ITEMUNIQUE(2789) == clitem.siUnique )	return false;

			//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ.
			if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_BLACKCACAORANDOM ) //�� īī��.
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;	

				// �⺻ ���� ���¸� ã�� �����Ѵ�.
				SI16 IsHaveBufType[8] = {	
					BUF_PREMIUMEXPUP,			// ������.//����EXP ������ ���� ���Ұ�
						BUF_ATTACKUP,				// ���ݷ� ����.
						BUF_DEFENSEUP,				// ���� ����.
						BUF_MAKEEXPUP,				// ���� ����ġ ����.
						BUF_NOFIRSTATTACK,			// ���� ���� ȿ��.
						BUF_SUCCESS_MANUFACTURE,	// ���� 100% ȿ���� �ִٸ�
						BUF_FOURLEAF,				// ����Ŭ�ι� - ������ ����� 2��.
						BUF_SUMMONATACUP};			// ��ȯ�� ��ȭ. 


					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) ||pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) // ������.//����EXP ������ ���� ���Ұ�
						IsHaveBufType[0] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||  // ���ݷ� ����.
						pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP30) ) 
						IsHaveBufType[1] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||  // ���� ����.
						pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP30) ) 
						IsHaveBufType[2] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MAKEEXPUP) )  // ���� ����ġ ����.
						IsHaveBufType[3] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )  // ���� ���� ȿ��.
						IsHaveBufType[4] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUCCESS_MANUFACTURE) )  //���� 100% ȿ���� �ִٸ�
						IsHaveBufType[5] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF) )  // ����Ŭ�ι� - ������ ����� 2��.
						IsHaveBufType[6] = 0;

					if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ||pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP))  //��ȯ�� ��ȭ.
						IsHaveBufType[7] = 0;


					SI16 SelectBufType[8] = {0,}; // ���� ������ ������ �����Ѵ�.
					SI16 noneSelect = 0;


					for(int i = 0; i < 8 ; i++)
					{
						if(IsHaveBufType[i] > 0)
						{
							SelectBufType[noneSelect] = IsHaveBufType[i] ;
							noneSelect++;
						}
					}

					if(noneSelect == 0) // �ɸ��� ������ ����.
						return false ;

					SI32 siRand = 0 ;
					siRand = rand()%noneSelect;  // ���� ������ �����Ѵ�.

					SI16 Buftype = SelectBufType[siRand];

					SI16 siPercent = 0; //Ÿ�Կ� ���� ����.

					switch(Buftype)
					{
					case BUF_MAKEEXPUP:
						siPercent = 50;
						break;
					case BUF_ATTACKUP:
					case BUF_DEFENSEUP:
					case BUF_SUMMONATACUP:	
						siPercent = 20;
						break;
					case BUF_PREMIUMEXPUP:
					case BUF_NOFIRSTATTACK:						
					case BUF_SUCCESS_MANUFACTURE:
					case BUF_FOURLEAF:
						siPercent = 0;						
						break;
					}

					SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;  // 1��  = 48��
					SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( Buftype, false );

					if ( index > -1 )
					{
						stBuf addBuf(Buftype, siPercent, usetime);
						AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
					}

					return false ;

			}
			//KHY - 0218 ȭ��Ʈ���� �̺�Ʈ.
			else if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_CANDYRANDOM ) //�� īī��.
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;	

				// �⺻ ���� ���¸� ã�� �����Ѵ�.
				SI16 IsHaveBufType[8] = {BUF_PREMIUMEXPUP, // ������.//����EXP ������ ���� ���Ұ�
					BUF_ATTACKUP,  // ���ݷ� ����.
					BUF_DEFENSEUP,  // ���� ����.
					BUF_MAKEEXPUP,  // ���� ����ġ ����.
					BUF_NOFIRSTATTACK,  // ���� ���� ȿ��.
					BUF_SUCCESS_MANUFACTURE,  //���� 100% ȿ���� �ִٸ�
					BUF_FOURLEAF, // ����Ŭ�ι� - ������ ����� 2��.
					BUF_SUMMONATACUP};//��ȯ�� ��ȭ. 


				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) ||pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) // ������.//����EXP ������ ���� ���Ұ�
					IsHaveBufType[0] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||  // ���ݷ� ����.
					pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP30) ) 
					IsHaveBufType[1] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ||  // ���� ����.
					pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) || pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP30) ) 
					IsHaveBufType[2] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MAKEEXPUP) )  // ���� ����ġ ����.
					IsHaveBufType[3] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )  // ���� ���� ȿ��.
					IsHaveBufType[4] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUCCESS_MANUFACTURE) )  //���� 100% ȿ���� �ִٸ�
					IsHaveBufType[5] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF) )  // ����Ŭ�ι� - ������ ����� 2��.
					IsHaveBufType[6] = 0;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ||pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP))  //��ȯ�� ��ȭ.
					IsHaveBufType[7] = 0;


				SI16 SelectBufType[8] = {0,}; // ���� ������ ������ �����Ѵ�.
				SI16 noneSelect = 0;

				for(int i = 0; i < 8 ; i++)
				{
					if(IsHaveBufType[i] > 0)
					{
						SelectBufType[noneSelect] = IsHaveBufType[i] ;
						noneSelect++;
					}
				}

				if(noneSelect == 0) // �ɸ��� ������ ����.
					return false ;

				SI32 siRand = 0 ;
				siRand = rand()%noneSelect;  // ���� ������ �����Ѵ�.

				SI16 Buftype = SelectBufType[siRand];

				SI16 siPercent = 0; //Ÿ�Կ� ���� ����.

				switch(Buftype)
				{
				case BUF_MAKEEXPUP:
					siPercent = 50;
					break;
				case BUF_ATTACKUP:
				case BUF_DEFENSEUP:
				case BUF_SUMMONATACUP:	
					siPercent = 20;
					break;
				case BUF_PREMIUMEXPUP:
				case BUF_NOFIRSTATTACK:						
				case BUF_SUCCESS_MANUFACTURE:
				case BUF_FOURLEAF:
					siPercent = 0;						
					break;
				}

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;  // 1��  = 48��
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( Buftype, false );

				if ( index > -1 )
				{
					stBuf addBuf(Buftype, siPercent, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;

			}			
			else if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HEROATTACKUP )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP30) ) return false ;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				
				// ���� �������� ����Ǿ� 
				stBuf addBuf(BUF_ATTACKUP, 20, usetime);
				AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );

				//SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_ATTACKUP, false );

				//if ( index > -1 )
				//{
				//	stBuf addBuf(BUF_ATTACKUP, 20, usetime);
				//	//AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				//	AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );
				//}

				return false ;
			}
			else if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HEROATTACKUP30 )
			{//������ ������ 30�ϰ�[2007.08.30 �ռ���]
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_ATTACKUP) ) return false ;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600;
				//21600 ;//���� �ð� ������ �ȵ��� �׽�Ʈ ���� ª������
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_ATTACKUP30, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_ATTACKUP30, 20, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			// ���� ���� ��
			else if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HERODEFENSEUP )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP30) ) return false ;



				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;

				// ���� �������� ����� ó�� �Լ� ����
				stBuf addBuf(BUF_DEFENSEUP, 20, usetime);
				AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );

				//SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_DEFENSEUP, false );

				//if ( index > -1 )
				//{
				//	stBuf addBuf(BUF_DEFENSEUP, 20, usetime);
				//	//AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				//	 AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );
				//}

				return false ;
			}
			else if( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HERODEFENSEUP30 )
			{//���� ������ 30�ϰ�[2007.08.30 �ռ���]
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_DEFENSEUP) ) return false ;



				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;//21600 30�� �ð�. ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_DEFENSEUP30, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_DEFENSEUP30, 20, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}//���� ������ 30�ϰ�[2007.08.30 �ռ���]

			// ���� Ŭ�ι�			
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_FOURLEAF )
			{
				if(pclClient->IsCountrySwitch(Switch_FourLeaf))
				{
					if( ITEMUNIQUE(2755) == clitem.siUnique || ITEMUNIQUE(2754) == clitem.siUnique	)
					{
						//[����] ���� ��밡���� ����ũ�ι����� Ȯ��. => 2008-8-14
						if( clitem.siUnique != pclserver->siFourLeafUnique )
						{
							pclserver->SendServerResponseMsg( 0, SRVAL_RETURN_NOT_USE_FOURLEAF, 0, 0, GetCharUnique() );
							return false;
						}
					}
				}

				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false ;//�̰� ���ʽ�

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_FOURLEAF, false );

				if ( index > -1 )
				{		
					stBuf addBuf(BUF_FOURLEAF, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;

			}
			// ���Ǻ� ����Ÿ�� [2007.08.22 �ռ���]
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HAPPYBEAN )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				SI32 usetime =  0;
				usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 15 ;// 30�а����				
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_HAPPYBEAN, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_HAPPYBEAN, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}


			//���� EXP ĸ��
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUPEREXPUP )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) ) return false ;//�ﷹ�� ������
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;	//����ĸ��
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ) return false ;	//���κ���
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;	//����
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false ;	//�̰����ʽ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300) ) return false ;	// ����� ����

				SI32 usetime =  0;

				if( itemunique == ITEMUNIQUE(2775) )	// ���ǽð�  7�� =  7 * 24 = 168�ð�  30 * 168 =  5040 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 5040 ;
				else if( itemunique == ITEMUNIQUE(2778) )	// ���ǽð� 15�� = 30 * 24 = 720 /2 �ð�  30 * 720 = 21600/2 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + (21600/2) ;
				else if( itemunique == ITEMUNIQUE(2780) )	// ���ǽð� 30�� = 30 * 24 = 720�ð�  30 * 720 = 21600 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;
				else
					return false ;

				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_SUPEREXPUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_SUPEREXPUP, 0, usetime);
					/*addBuf.siBufType = BUF_SUPEREXPUP;
					addBuf.siPercent = 0;
					addBuf.siAdd = 0;
					addBuf.siOverTime = usetime;
					addBuf.bOverlap = false;*/

						AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			// Ư�� �ĳ��� ���� ���			
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUMEXPUP )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;  // �κ��� �����ִ��� Ȯ��.	
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false ;// ����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300) ) return false ;	// ����� ����
				if ( true == pclCI->clBI.bPremiumService ) return false;

				SI32 usetime =  0;

				if( itemunique == ITEMUNIQUE(2757) )		// ���ǽð�  1�� =  1 * 24 =  24�ð�  30 *  24 =   720 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 720 ;
				else if( itemunique == ITEMUNIQUE(2759) )	// ���ǽð�  7�� =  7 * 24 = 168�ð�  30 * 168 =  5040 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 5040 ;
				else if( itemunique == ITEMUNIQUE(2760) )	// ���ǽð� 30�� = 30 * 24 = 720�ð�  30 * 720 = 21600 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;
				else if( itemunique == ITEMUNIQUE(2761) )	// ���ǽð� 30�� = 30 * 24 = 720�ð�  30 * 720 = 21600 �ð�
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;
				else if( itemunique == ITEMUNIQUE(2798) )	// GoonzuEvent Item (ITEMUNIQUE(2757)�� ���� ����� �Ѵ�.)
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 720 ;
				else
					return false ;


				// ������������ ����Ǿ ó�� �Լ� ����
				stBuf addBuf(BUF_PREMIUMEXPUP, 0, usetime);
				AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );

				//SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_PREMIUMEXPUP, false );

				//if ( index > -1 )
				//{
				//	stBuf addBuf(BUF_PREMIUMEXPUP, 0, usetime);
				//	/*addBuf.siBufType =	BUF_PREMIUMEXPUP;
				//	addBuf.siPercent = 0;
				//	addBuf.siAdd = 0;
				//	addBuf.siOverTime = usetime;
				//	addBuf.bOverlap = false;*/

				//		//AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				//		AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );

				//}

				return false ;
			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_NOFIRSTATTACK_PREMIUM)
			{
				// [����] �������� ������ ������̸� �ش� ����Ʈ Ŭ����.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK ) )
					IncQuestPara(QUEST_CLEAR_COND_USEITEM, clitem.siUnique, clitem.siItemNum);

				// �������� ȿ���� �ߺ��ؼ� ��� �� �� ����.
				//if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )	return false ;

				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )	return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) )	return false ;

				// �̹� 60��¥�� �� ���� �ִٸ� �� �� ����.
				//if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )	return false ;

				SI32 usetime = 0;
				if( ITEMUNIQUE(2792) == clitem.siUnique )
					usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;		//21600 30�� �ð�.
				else
					usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;			// ���ǽð� 48��.

				// ������������ ����Ǿ ó�� �Լ� ����
				stBuf addBuf(BUF_NOFIRSTATTACK, 0, usetime);
				AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );


				//SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_NOFIRSTATTACK, false );
				//if ( index > -1 )
				//{
				//	stBuf addBuf(BUF_NOFIRSTATTACK, 0, usetime);
				//	//AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				//	AddBufThroughDB_AccumulateEnable( &addBuf , true , itempos , &clitem );
				//}
				return false ;				
			}

			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_NOFIRSTATTACK)		//	[��ȣ] �̹� �������� �������� �������¶�� 60��¥�� ���������������� �ߺ��ɼ� ����.
			{
				// [����] �������� ������ ������̸� �ش� ����Ʈ Ŭ����.
				if( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK ) )
					IncQuestPara(QUEST_CLEAR_COND_USEITEM, clitem.siUnique, clitem.siItemNum);

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOFIRSTATTACK) )	return false ;
			}

			//��ȯ�� ���ݷ� ���� ���� (48��¥��(���ӽð� �Ϸ�) ȿ���� �ִٸ�,
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUMMONATACUP)
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) ) return false;	// ������� ȿ���� �� ���ϹǷ� ���Դ´�.

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_SUMMONATACUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_SUMMONATACUP, 20, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;				
			}

			//���� 100% ȿ���� �ִٸ�
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUCCESS_MANUFACTURE)
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_SUCCESS_MANUFACTURE, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_SUCCESS_MANUFACTURE, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;				
			}

			// ���ĸ��� ��� ȿ���� �ִٸ�...
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_MOFUMOFU_PERFUME)
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_MOFUMOFU_PERFUME, false );

				SI16 siKind = pclClient->GetUniqueFromHash("KIND_RABBIT");
				if ( index > -1 )
				{
					stBuf addBuf(BUF_MOFUMOFU_PERFUME, siKind, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}
				return false ;				
			}
			// �̰����� ����
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_REWARDBONUS )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_MAKEEXPUP) ) return false ;// ���� ����ġ ����
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false ;//����EXP ������ ���� ���Ұ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) ) return false ;//�ﷹ�� ������
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false ;//����ĸ��
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ) return false ;//���κ���
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false ;//����
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF) ) return false ;// ���� Ŭ�ι�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_NOTBONUSTIME_MAKEEXPUP ) ) return false ;// ���� Ŭ�ι�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SPECIALAMPUL_EXPUP300 ) ) return false ;// ����� ����

				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 720;	// ���ǽð� 1��
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_REWARDBONUS, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_REWARDBONUS, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );

					// �ش� �������� ����ϸ�, �޽���â�� ��µȴ�.
					pclserver->SendServerResponseMsg(0, SRVAL_ITEMUSE_REWARDBONUS, 8515, 0, GetCharID());
				}

				return false ;				
			}
			// PCK : ���� �����̾� ������
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUMMAKEEXPUP )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;			

				SI32 usetime = 0;
				if( itemunique == ITEMUNIQUE(2788) )	// ���ǽð�  1�� =  1 * 24 = 24�ð�  30 * 24 =  720 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 720 ;
				else if( itemunique == ITEMUNIQUE(2787) )	// ���ǽð� 7�� =  7 * 24 = 168�ð�  30 * 168 =  5040 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 5040 ;
				else if( itemunique == ITEMUNIQUE(2786) )	// ���ǽð� 30�� = 30 * 24 = 720�ð�  30 * 720 = 21600 �ð� 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;
				else
					return false ;

				//SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600;	// ���ǽð� 30��
				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_PREMIUMMAKEEXPUP, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_PREMIUMMAKEEXPUP, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;				
			}
			// ����� ����			
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SPECIALAMPUL )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUPEREXPUP) ) return false;	// ���� EXP ĸ��
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_PREMIUMEXPUP) ) return false; // Ư�� �ĳ��� ������(��Ƽ ��Ÿ��)
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_HINAMOCHI) ) return false;	// ���κ�������ũ
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER) ) return false;	// ��Ʈĵ��,���귯�� ���ݸ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP) ) return false;	// ��Ÿĵ��,������ ���ڷ�
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_REWARDBONUS) ) return false;	// �̰����� ������(�ﷹ���� �ػ� �����̾� ���)
				if ( pclCI->clBI.clBufInfo.IsHaveBuf( BUF_RESIDENTS_EXPUP_10) ) return false; // ���� EXP ĸ��


				SI32 usetime =  0;

				if( itemunique == ITEMUNIQUE(2790) ) 
					usetime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // ���ǽð� 48�а�.

				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_SPECIALAMPUL_EXPUP300, false );

				if ( index > -1 )
				{
					stBuf addBuf(BUF_SPECIALAMPUL_EXPUP300, 0, usetime);
					AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
				}

				return false ;
			}
			//------------------------------------------------------------------------------------------------
			// ���� EXP ĸ��
			//------------------------------------------------------------------------------------------------
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESIDENTS_EXPUP_10 )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )	return false;
				if( itemunique != ITEMUNIQUE( 2801 ) ) return false;

				cltServer* pServer = (cltServer*)pclClient;
				SI32 siMyHomeTownUnique = 0;

				//////////////////////////////////////////////////////////////////////////
				SI32 usetime = 0;															// �ϴ� �ɾ��� ������ ������ ���� ����Ʈ ������ ����� (�������� ������ �ٶ� ����ϴ°� �ƴ� �� ������ ������ ��Ƶδ� �뵵�� ���)
				usetime = pServer->pclTime->clDate.GetHourVary() + 24;		// ����Ʈ ���� ���ǽð� 48�а� (���ӽð�1��).
				stBuf addBuf( BUF_RESIDENTS_EXPUP_10, 0, usetime );

				//////////////////////////////////////////////////////////////////////////
				if ( RANKTYPE_CITYHALL == pclCI->clCharRank.siType )						// ������ ����� ����� �����϶�
				{
					siMyHomeTownUnique = pclCI->clCharRank.GetVillageUnique();				// ���� �϶� ��ũ �������� ���� ����ũ�� ��´�. (ĳ���� �⺻ �������� ������� �ʱ� ����)
				}
				else																		// ������ ����� ����� ���ְ� �ƴҶ�
				{
					siMyHomeTownUnique = pclCI->clBI.siHomeVillage;
				}

				//////////////////////////////////////////////////////////////////////////
				if ( true == pServer->pclVillageManager->IsValidVillage( siMyHomeTownUnique ) )
				{
					// ���� ĳ���� ���� ó�� (���ִ� clBI.siHomeVillage�� ���� ������ �ȵǾ� �ֱ� ������ AddBufToAllTownPerson()�Լ����� üũ���� �ʴ´�)
					if ( RANKTYPE_CITYHALL == pclCI->clCharRank.siType )					// ������ ����� ����� �����϶�
					{
						if ( true == IsValidConnection() )
						{
							if ( false == pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SPECIALAMPUL_EXPUP300) )
							{
								AddTownBufThroughDB( this, &addBuf );
							}
						}
					}
					else																	// ������ ����� ����� ���ְ� �ƴҶ�
					{
						cltRank* pclRank = pServer->pclRankManager->GetRank( RANKTYPE_CITYHALL, siMyHomeTownUnique );
						if ( NULL != pclRank )
						{
							cltRank clRank;
							SI32 siPersonID = 0;
							clRank.Set( pclRank );

							siPersonID = clRank.clPerson.GetPersonID();
							if ( 0 < siPersonID )
							{
								SI32 siCharID = 0;
								siCharID = pServer->pclCM->GetIDFromPersonID( siPersonID );
								if ( 0 < siCharID )
								{
									cltCharServer* pCityJJang = (cltCharServer*)pServer->pclCM->CR[siCharID];
									if ( NULL != pCityJJang )		// ���� ĳ���͸� ã�Ҵٸ�
									{
										if ( true == pCityJJang->IsValidConnection() )
										{
											if ( false == pCityJJang->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_SPECIALAMPUL_EXPUP300) )
											{
												pCityJJang->AddTownBufThroughDB( pCityJJang, &addBuf );
											}
										}
									}
								}
							}
						}
					}

					// �ش� ���� �ֹε鿡�� ������ �ش�
					AddBufToAllTownPerson( siMyHomeTownUnique, &addBuf, BUF_SPECIALAMPUL_EXPUP300, 0 );
				}

				//////////////////////////////////////////////////////////////////////////
				// ����� ������ �����۸� 1�� ���� (������ �������� ���ҵǸ鼭 �߻��ϴ� ȿ���� ���°Ͱ� ��������)
				sDBRequest_UseItem clMsg( GetID(), pclCI->GetPersonID(), itempos, &clitem, USEITEM_REASON_NONE );
				pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

				return false;
			}
			//------------------------------------------------------------------------------------------------
			// ���� ��ȭ��
			//------------------------------------------------------------------------------------------------
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESIDENTS_STRONG )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )	return false;
				if( itemunique != ITEMUNIQUE( 2802 ) ) return false;

				cltServer* pServer = (cltServer*)pclClient;
				SI32 siMyHomeTownUnique = 0;

				//////////////////////////////////////////////////////////////////////////
				SI32 usetime = 0;															// �ϴ� �ɾ��� ������ ������ ���� ����Ʈ ������ ����� (�������� ������ �ٶ� ����ϴ°� �ƴ� �� ������ ������ ��Ƶδ� �뵵�� ���)
				usetime = pServer->pclTime->clDate.GetHourVary() + 24;		// ����Ʈ ���� ���ǽð� 48�а� (���ӽð�1��).
				stBuf addBuf( BUF_RESIDENTS_STRONG, 10, usetime );

				//////////////////////////////////////////////////////////////////////////
				if ( RANKTYPE_CITYHALL == pclCI->clCharRank.siType )						// ������ ����� ����� �����϶�
				{
					siMyHomeTownUnique = pclCI->clCharRank.GetVillageUnique();				// ���� �϶� ��ũ �������� ���� ����ũ�� ��´�. (ĳ���� �⺻ �������� ������� �ʱ� ����)
				}
				else																		// ������ ����� ����� ���ְ� �ƴҶ�
				{
					siMyHomeTownUnique = pclCI->clBI.siHomeVillage;
				}

				//////////////////////////////////////////////////////////////////////////
				if ( true == pServer->pclVillageManager->IsValidVillage( siMyHomeTownUnique ) )
				{
					// ���� ĳ���� ���� ó�� (���ִ� clBI.siHomeVillage�� ���� ������ �ȵǾ� �ֱ� ������ AddBufToAllTownPerson()�Լ����� üũ���� �ʴ´�)
					if ( RANKTYPE_CITYHALL == pclCI->clCharRank.siType )					// ������ ����� ����� �����϶�
					{
						if ( true == IsValidConnection() )
						{
							AddTownBufThroughDB( this, &addBuf );
						}
					}
					else																	// ������ ����� ����� ���ְ� �ƴҶ�
					{
						cltRank* pclRank = pServer->pclRankManager->GetRank( RANKTYPE_CITYHALL, siMyHomeTownUnique );
						if ( NULL != pclRank )
						{
							cltRank clRank;
							SI32 siPersonID = 0;
							clRank.Set( pclRank );

							siPersonID = clRank.clPerson.GetPersonID();
							if ( 0 < siPersonID )
							{
								SI32 siCharID = 0;
								siCharID = pServer->pclCM->GetIDFromPersonID( siPersonID );
								if ( 0 < siCharID )
								{
									cltCharServer* pCityJJang = (cltCharServer*)pServer->pclCM->CR[siCharID];
									if ( NULL != pCityJJang )		// ���� ĳ���͸� ã�Ҵٸ�
									{
										if ( true == pCityJJang->IsValidConnection() )
										{
											pCityJJang->AddTownBufThroughDB( pCityJJang, &addBuf );
										}
									}
								}
							}
						}
					}

					// �ش� ���� �ֹε鿡�� ������ �ش�
					AddBufToAllTownPerson( siMyHomeTownUnique, &addBuf, 0, 0 );
				}

				//////////////////////////////////////////////////////////////////////////
				// ����� ������ �����۸� 1�� ���� (������ �������� ���ҵǸ鼭 �߻��ϴ� ȿ���� ���°Ͱ� ��������)
				sDBRequest_UseItem clMsg( GetID(), pclCI->GetPersonID(), itempos, &clitem, USEITEM_REASON_NONE );
				pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

				return false;
			}

			// ����Ʈ�� ��Ƽ ����
			else if ( pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_QUEST_ANTIPOTION )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )
				{
					return false;
				}

				SI32 siUseItem = 0;
				if ( ITEMUNIQUE(2796) == itemunique )
				{
					siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // ���ǽð� 48�а�.
				}

				SI16 siEmptySlot = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_QUEST_ANTIPOTION, false );
				if ( -1 < siEmptySlot )
				{
					stBuf addBuf(BUF_QUEST_ANTIPOTION, 0, siUseItem);
					AddBufThroughDB( siEmptySlot, &addBuf , true , itempos , &clitem );
				}

				return false;
			}
			// �ص����� ����ߴٸ�,
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ANTIDOTES)
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				SI32 siChangeType = 0;
				// �ߵ� ���� �ص�.
				if( clInnerStatus.IsStatus( INNERSTATUS_POISON ) )
				{
					clInnerStatus.DelStatus(INNERSTATUS_POISON);
					siChangeType = CHANGETYPE_POISON;
				}
				else if( clInnerStatus.IsStatus( INNERSTATUS_POISON_SETITEM_EFFECT ) )
				{
					clInnerStatus.DelStatus(INNERSTATUS_POISON_SETITEM_EFFECT);
					siChangeType = CHANGETYPE_POISON_SETITEM_EFFECT;
				}
				
				// �̿����� �뺸 
				cltCharChangeStatusInfo	StatusInfo( siChangeType, false );
				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}
			else if( HEALEFT_TRANSFORM_SYNCRO_UP == pclItemManager->pclItemInfo[ref]->siHealEft )
			{	
				static const SI32 siAddTime = 28512;

				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )	return false ;

				if( false == clTransFormInfo.bTransFormMode )	return false;

				// ��ũ�� 100% �� �������� �Ҹ����� �ʴ´�.
				if( (SI32)clTransFormInfo.GetSynchroTransForm( clTransFormInfo.uiNowTransFormKind ) >= 100 )
				{
					pclserver->SendServerResponseMsg( 0, SRVAL_TRANSFORM_SYNCRO_UP, 100, 0,  GetID() );
					return false; 
				}

				// DB�� ���� �ð��� �߰����ش�.
				sDBRequest_Transform_AddTime clMsg1(GetCharID(), pclCI->GetPersonID(), clTransFormInfo.uiNowTransFormKind, siAddTime );
				pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);


				UI16 tKind = clTransFormInfo.uiNowTransFormKind;
				SI32 siBeforeSync = (SI32)clTransFormInfo.GetSynchroTransForm( tKind );
				// �ش� ������ ���ð��� ���Ѵ�.
				clTransFormInfo.AddTransFormTime(tKind, siAddTime);
				SI32 siCurSync = (SI32)clTransFormInfo.GetSynchroTransForm( tKind );

				if( siCurSync == 100 && siBeforeSync < siCurSync )
				{
					// ��ũ�� 100�� �޼��� ��� ��ǰ �˸�â�� ����.
					cltItem clItem;		clItem.Init();

					SI32 siItemUnique = GetItemUniqueFromCharKind(clTransFormInfo.uiNowTransFormKind);
					if(siItemUnique > 0)
					{
						SI16 brareswitch = 0;
						if( pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clItem, 0, 0, &brareswitch,0,0,0,0,0,0) == true )
						{
							clItem.SetItemNum(1);
							cltGameMsgResponse_MaxSyncro_Attainment clMaxSyncro( &clItem, clTransFormInfo.uiNowTransFormKind, pclCI->clBI.GetName() );
							cltMsg clMsg( GAMEMSG_RESPONSE_MAXSYNCRO_ATTAINMENT, sizeof(clMaxSyncro), (BYTE*)&clMaxSyncro );
							pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
						}
					}
				}

				// ��ũ���� ����Ǿ����Ƿ�, Ŭ���̾�Ʈ�� �ѹ� �����Ѵ�.
				if( siCurSync != siBeforeSync )
				{
					// Ŭ���̾�Ʈ�� ������ �����Ѵ�.
					cltGameMsgResponse_SetTransForm	clTrasFormInfo( &clTransFormInfo );
					cltMsg clMsg( GAMEMSG_RESPONSE_TRANSFORM, sizeof(cltTransFormInfo), (BYTE*)&clTrasFormInfo );
					SendNetMsg( (sPacketHeader*)&clMsg );			

					pclserver->SendServerResponseMsg( 0, SRVAL_TRANSFORM_SYNCRO_UP, 200, 0,  GetID() );
				}

				// ���� 100% ����Ʈ�� �׷��ش�.
				if( siCurSync >= 100 )
				{
					cltCharChangeStatusInfo clchangeinfo(CHANGETYPE_TRANSFORM100EFFECT, true);
					cltGameMsgResponse_StatusInfo clinfo(GetID(), &clchangeinfo);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
					SendNeighbourMsg(&clMsg, true);	
				}


			}
			// ���� ���� ȿ���� �ִٸ�, 
			if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_NOFIRSTATTACK)
			{
				bNoFirstAttackSwitch = true;
				dwNoFirstAttackClock = pclClient->CurrentClock;

				// �̿����� �뺸 
				cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACK, bNoFirstAttackSwitch);
				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}
			// [����] ��ȯ�� �������� ����
			if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUMMONNOFIRSTATTACK)
			{
				SI32 siSummonID = GetSummonID();

				// ��ȯ��
				cltCharServer *pclSummon = pclCM->GetCharServer(siSummonID);
				if(NULL != pclSummon)
				{
					// �̹� �������� ���¶��
					if( true == pclSummon->bNoFirstAttackSwitch)
					{
						return false;
					}

					// �����̾� �������� ������ ���� ���¶��
					if( true == pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum)
					{
						return false;
					}

					pclSummon->bNoFirstAttackSwitch = true;
					pclSummon->dwNoFirstAttackClock = pclClient->CurrentClock;

					// �̿����� �뺸 
					cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_SUMMONNOFIRSTATTACK, pclSummon->bNoFirstAttackSwitch);
					cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
					cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
					SendNeighbourMsg(&clMsg, true);
				}
				else
				{
					return false;
				}
			}
			// �� �ɷ� ��� ȿ���� �ִٸ�, 
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HORSEWINGS)
			{
				// ���� �־�� �������� ����Ѵ�. - by LEEKH 2007.10.18
				cltHorse *pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if(pclHorse == NULL || pclHorse->siHorseUnique <= 0)
				{
					return false;
				}

				// ������̴� Ż�� ��ȭ�� ������ ���� �ʴ´�.->2009-03-04 ��ȹ���� ��û���� ������̵� Ż�Ͱ�ȭ���� ����Ҽ� �ֵ��� ���� 
				//if(pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
				//	return false;

				if ( pclHorse->siStatusTicketNum == 0 )
				{
					pclHorse->clAddStatusDate.Set(&((cltServer*)pclClient)->pclTime->clDate);
				}
				pclHorse->siStatusTicketNum += 1 ;

				// DB�� �����Ѵ�. 
				SetUpdateSwitch(UPDATE_HORSE, true, 0);
				UpdateHorseToDB((cltServer*)pclClient,
					pclCI->clHorseInfo.siCurrentShowHorse,
					pclHorse, SETHORSE_REASON_TICKET);
			}
			// �ص� ȿ������ �ִٸ�, 
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_UNFREEZE)
			{
				// �ص� ���� �ؼ�. 
				clInnerStatus.DelStatus(INNERSTATUS_ICE);

				// �̿����� �뺸 (ICE ��� ����)
				dwNoIceAttackClock = pclClient->CurrentClock;
				bNoIceAttackSwitch = true;
				cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOICEATTACK, bNoIceAttackSwitch);

				cltGameMsgResponse_StatusInfo clChangeInfo(GetCharUnique(), &StatusInfo);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
				SendNeighbourMsg(&clMsg, true);
			}
			// �����̾� ȿ���� �ִٸ�
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_PREMIUM )
			{
				if ( bIsSetPremium ) return false ;
				if ( pclCI->clBI.bPremiumService ) return false ;
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) ) return false;	// ������� ȿ���� �� ���ϹǷ� ���Դ´�.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_FRIENDSHIP) ) return false;	// ������� ȿ���� �� ���ϹǷ� ���Դ´�.
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI) ) return false;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_PREMIUMEXPUP) ) return false;

				SI32 usedate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() + 2 ;
				sDBRequest_SetPremium clPremium(GetCharUnique(),pclCI->GetPersonID(),true,usedate,0,0,0,0,&clitem,itempos,SETPREMIUM_EXP);
				((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clPremium);


				bIsSetPremium = true ;

				return false ;
			}

			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_COMBAT )
			{
				if ( bIsSetCombat ) return false ;
				if ( pclCI->clBI.bCombatService ) return false ;
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				SI32 usedate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() + 30 ;
				sDBRequest_SetPremium clCombat(GetCharUnique(),pclCI->GetPersonID(),true,0,usedate,0,0,0,&clitem,itempos,SETPREMIUM_COMBAT);
				((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clCombat);

				bIsSetCombat = true ;

				return false ;
			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_BULLET )
			{
				if ( bIsBulletService ) return false ;
				if ( pclCI->clBI.bBulletService ) return false ;
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				SI32 usedate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() + 361;
				sDBRequest_SetPremium clCombat(GetCharUnique(),pclCI->GetPersonID(),true,0,0,0, usedate,0,&clitem,itempos,SETPREMIUM_BULLET);
				((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clCombat);

				bIsBulletService = true ;

				return false ;
			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_SUMMONSTAMINA )
			{
				if( pclCI->clSummonInfo.IsSummonTranform( siSummonIndex ) )	
				{
					pclserver->SendServerResponseMsg( 0, SRVAL_RETURN_SUMMON_TRANSFORM_USE_STAMINA_ITEM, 0, 0, GetID() );
					return false;
				}

				if ( bIsSummonStaminaService )							return false ;
				if ( pclCI->clBI.bSummonStaminaService )				return false ;
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON )	return false ;
				if ( pclCI->clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) )	return false;	// ������� ȿ���� �� ���ϹǷ� ���Դ´�.

				SI32 usedate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() + 2;
				//					sDBRequest_SetPremium clCombat(GetCharUnique(),pclCI->GetPersonID(),true,0,0,0,usedate,0,&clitem,itempos,SETPREMIUM_SUMMONSTIMINA);
				//KHY - 0910 - ��ȯ���¹̳��� ��� ���׼���.
				sDBRequest_SetPremium clCombat(GetCharUnique(),pclCI->GetPersonID(),true,0,0,0,0,usedate,&clitem,itempos,SETPREMIUM_SUMMONSTIMINA);
				((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clCombat);

				bIsSummonStaminaService = true ;

				return false ;
			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_HEROSTAMINA )
			{
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				if(pclCI->clHealthInfo.uiHealthPoint < 110)	// �ִ� �ǰ� ��ġ�� �ѱ� ���� ����. 
				{
					pclCI->clHealthInfo.uiHealthPoint++;
				}
				else
				{
					return false;
				}

				SetUpdateSwitch(UPDATE_HEALTH, true, 0);

			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_DIGESTIVE )
			{					
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;


				SI32 hungryrecover = -20;
				// �������� ȸ�������ش�.
				clPB.clHealth.IncreaseHungry(hungryrecover);

				SetUpdateSwitch(UPDATE_HEALTH, true, 0);

			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ALLDESEASE )
			{	
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;


				cltCurDisease clCurDisease;
				if(clPB.clHealth.GetCurDisease(&clCurDisease) == true)
				{
					// ����ũ�� ��ġ�ϴ��� Ȯ���Ѵ�. 


					// ������ ġ���Ѵ�. 
					if( clCurDisease.siOrg1Unique > 0 )					
					{
						clPB.clHealth.CureDisease(clCurDisease.siOrg1Unique);
					}
					if( clCurDisease.siOrg2Unique > 0 )					
					{
						clPB.clHealth.CureDisease(clCurDisease.siOrg2Unique);
					}
					if( clCurDisease.siOrg3Unique > 0 )					
					{
						clPB.clHealth.CureDisease(clCurDisease.siOrg3Unique);
					}
					if( clCurDisease.siOrg4Unique > 0 )					
					{
						clPB.clHealth.CureDisease(clCurDisease.siOrg4Unique);
					}


					// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
					SetUpdateSwitch(UPDATE_HEALTH, true, 0);

					// DB�� �����Ѵ�. 
					sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


				}	
			}
			else if(pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_FAME )
			{	
				if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) return false ;

				IncreaseFameExp(10);
			}
			else if (pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ADDEXP)
			{
				if (itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON){ return false;}
				else if (pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_ADDEXP){
					if (itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON){
						return false;
					}
					//���� Ȯ������ ����ġ ���� [2007.07.25 �ռ���]
					SI64 AddExp= 0		;
					SI32 PercentNum = 0	;
					PercentNum = rand() % 1000;
					if ( PercentNum > 0  && PercentNum <=700 )
					{
						AddExp = rand() % 10000 + 10000;
					}
					else if ( PercentNum >700 && PercentNum <=820 )
					{
						AddExp = rand() % 10000 + 20000;
					}
					else if ( PercentNum >820  && PercentNum <=890  )
					{
						AddExp = rand() % 10000 + 40000;
					}
					else if ( PercentNum >890  && PercentNum <= 940  )
					{
						AddExp = rand() % 10000 + 60000;
					}
					else if ( PercentNum >940 && PercentNum <=970 )
					{
						AddExp = rand() % 10000 + 70000;
					}
					else if ( PercentNum >970 && PercentNum <=990 )
					{
						AddExp = rand() % 10000 + 80000;
					}
					else if ( PercentNum >990 && PercentNum <=100 )
					{
						AddExp = rand() % 10000 + 90000;
					}
					IncreaseExp(AddExp);
				}
			}


			cltCharServer* pcltargetchar = NULL; 
			if(pclItemManager->pclItemInfo[ref]->siAdapt == ADAPT_SUMMON)
			{
				SI32 id = GetSummonID();

				if(pclCM->IsAlive(id))
				{
					pcltargetchar = (cltCharServer*)pclCM->CR[id];
				}

				if(pcltargetchar == NULL)	break;
			}
			else
			{
				pcltargetchar = this;
			}

			SI32 orglife	= pcltargetchar->pclCI->clIP.GetLife();
			SI32 orgmana	= pcltargetchar->pclCI->clIP.GetMana();

			SI32 life		= clitem.GetLife(pclClient->pclItemManager);
			SI32 mana		= clitem.GetMana(pclClient->pclItemManager);
			SI32 disease	= clitem.GetDisease(pclClient->pclItemManager); 

			SI32 lifediff	= max(0, pcltargetchar->clPB.GetMaxLife() - orglife - pcltargetchar->clPB.siReservedLife);
			SI32 inclife	= min(lifediff, life);
			pcltargetchar->clPB.siReservedLife += inclife;


			SI32 max = MAXORG(pcltargetchar->pclCI->clIP.GetLevel());

			if(pcltargetchar->clPB.GetMaxMana() > orgmana + (SI32)mana)
			{
				pcltargetchar->pclCI->clIP.IncreaseMana(mana);
			}
			else
			{
				pcltargetchar->pclCI->clIP.SetMana(pcltargetchar->clPB.GetMaxMana());
			}

			SI32 diffmana = pcltargetchar->pclCI->clIP.GetMana() - orgmana;


			// ��ȯ���� ��� ������ �����͸� ������Ʈ�ϰ� Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
			if(pclItemManager->pclItemInfo[ref]->siAdapt == ADAPT_SUMMON)
			{
			}
			// ����� ��� �ǰ����� �����Ѵ�. 
			else if(pclItemManager->pclItemInfo[ref]->siAdapt == ADAPT_MAN)
			{
				// ��ȭ����� �ջ��Ų��. 
				if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty)
				{
					SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg1Penalty / 10;
					SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg1Penalty) % 10;

					pclCI->clHealthInfo.IncreaseInnerOrg1(penalty);

					if((rand() % 10) < modul)
					{
						if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty > 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg1(1);
						}
						if(pclItemManager->pclItemInfo[ref]->siOrg1Penalty < 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg1(-1);
						}

					}
					// �ִ밪 ������ ����� �ʴ´�. 
					if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG1) > max)
					{
						pclCI->clHealthInfo.siInnerOrg1 = max;
					}
					else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG1) < -max)
					{
						pclCI->clHealthInfo.siInnerOrg1 = -max;
					}


					SetUpdateSwitch(UPDATE_HEALTH, true, 0);

					// DB�� �����Ѵ�. 
					sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}

				// ��ȯ����� �ջ��Ų��. 
				if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty)
				{
					SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg2Penalty / 10;
					SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg2Penalty) % 10;

					pclCI->clHealthInfo.IncreaseInnerOrg2(penalty);

					if((rand() % 10) < modul)
					{
						if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty > 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg2(1);
						}
						if(pclItemManager->pclItemInfo[ref]->siOrg2Penalty < 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg2(-1);
						}

					}

					// �ִ밪 ������ ����� �ʴ´�. 
					if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG2) > max)
					{
						pclCI->clHealthInfo.siInnerOrg2 = max;
					}
					else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG2) < -max)
					{
						pclCI->clHealthInfo.siInnerOrg2 = -max;
					}


					SetUpdateSwitch(UPDATE_HEALTH, true, 0);

					// DB�� �����Ѵ�. 
					sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}


				// ȣ������ �ջ��Ų��. 
				if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty)
				{
					SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg3Penalty / 10;
					SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg3Penalty) % 10;

					pclCI->clHealthInfo.IncreaseInnerOrg3(penalty);

					if((rand() % 10) < modul)
					{
						if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty > 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg3(1);
						}
						if(pclItemManager->pclItemInfo[ref]->siOrg3Penalty < 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg3(-1);
						}

					}

					// �ִ밪 ������ ����� �ʴ´�. 
					if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG3) > max)
					{
						pclCI->clHealthInfo.siInnerOrg3 = max;
					}
					else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG3) < -max)
					{
						pclCI->clHealthInfo.siInnerOrg3 = -max;
					}


					SetUpdateSwitch(UPDATE_HEALTH, true, 0);

					// DB�� �����Ѵ�. 
					sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}

				// �Ű����� �ջ��Ų��. 
				if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty)
				{
					SI32 penalty	= pclItemManager->pclItemInfo[ref]->siOrg4Penalty / 10;
					SI32 modul		= TABS(pclItemManager->pclItemInfo[ref]->siOrg4Penalty) % 10;

					pclCI->clHealthInfo.IncreaseInnerOrg4(penalty);

					if((rand() % 10) < modul)
					{
						if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty > 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg4(1);
						}
						if(pclItemManager->pclItemInfo[ref]->siOrg4Penalty < 0)
						{
							pclCI->clHealthInfo.IncreaseInnerOrg4(-1);
						}

					}

					// �ִ밪 ������ ����� �ʴ´�. 
					if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG4) > max)
					{
						pclCI->clHealthInfo.siInnerOrg4 = max;
					}
					else if(pclCI->clHealthInfo.GetOrg(HEALTH_ORGAN_TYPE_ORG4) < -max)
					{
						pclCI->clHealthInfo.siInnerOrg4 = -max;
					}

					SetUpdateSwitch(UPDATE_HEALTH, true, 0);

					// DB�� �����Ѵ�. 
					sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}

				// ġ���� �� �ִ� ������ �ִٸ�, 
				if(disease)
				{
					// ������ ���� ����ũ�� ���´�. 
					cltCurDisease clCurDisease;
					if(pcltargetchar->clPB.clHealth.GetCurDisease(&clCurDisease) == true)
					{
						// ����ũ�� ��ġ�ϴ��� Ȯ���Ѵ�. 
						if(clCurDisease.IsIn(disease) == true)
						{
							// ������ ġ���Ѵ�. 
							pcltargetchar->clPB.clHealth.CureDisease(disease);

							// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
							pcltargetchar->SetUpdateSwitch(UPDATE_HEALTH, true, 0);

							// DB�� �����Ѵ�. 
							sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

						}
					}
				}
			}


			if(inclife)
			{
				cltGameMsgResponse_IncLife clInfo(pcltargetchar->GetCharUnique(), pcltargetchar->pclCI->clIP.GetLife(), 0, pcltargetchar->clPB.siReservedLife, inclife, INCLIFE_REASON_HEAL);
				cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);

			}
			if(diffmana)
			{
				cltGameMsgResponse_IncMana clInfo(pcltargetchar->GetCharUnique(), pcltargetchar->pclCI->clIP.GetMana(), diffmana, INCMANA_REASON_HEAL);
				cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		break;

		//==============================================================================================================================
		// ANIMAL
		//==============================================================================================================================
	case ITEMTYPE_ANIMAL:
		{
			cltServer* pclserver = (cltServer*)pclClient;


			bool bnoticeallswitch = false;
			SI32 speed			= 0;
			SI32 sistr = 0, sidex = 0, simag = 0;
			SI16 life = 1;

			SI32 horseunique	= HORSEUNIQUE_BROWN;		
			TCHAR* pText = GetTxtFromMgr(667);
			TCHAR horsename[128];
			StringCchCopy(horsename, 128, pText);

			switch(pclItemManager->pclItemInfo[ref]->clItem.siUnique)
			{
			case ITEMUNIQUE(5605):	// ���� 30�� ���� ���� ���� �������� ������ �޴�
				{
					speed = 1500;
					sistr	= 2000;
					sidex	= 2000;
					simag	= 2000;	
					life	= 2700;
				}
				break;

			case ITEMUNIQUE(5600):	// ������ - ���� �޴�
				{
					// �븸 ũ�������� �̺�Ʈ (PCK - 2007.11.16)
					cltUniqueRange TaiwanChristmasEvent_SmallMedal[] = 
					{
						{	HORSEUNIQUE_BLACK,		2	}	// < 2		�渶
						,{	HORSEUNIQUE_WHITE,		2	}	// < 4		�鸶
						,{  HORSEUNIQUE_ZEBRA,		2	}	// < 6		��踶
						,{	HORSEUNIQUE_RUDOLF,		10	}	// < 16		�絹��	
					};

					// �۷ι�, USA, �Ϻ� ũ�������� �̺�Ʈ (PCK - 2007.11.29)
					cltUniqueRange ChristmasEvent_SmallMedal[]=
					{
						{	HORSEUNIQUE_BLACK,		3	}	// < 3		�渶
						,{	HORSEUNIQUE_WHITE,		3	}	// < 6		�鸶
						,{	HORSEUNIQUE_ZEBRA,		1	}	// < 7		��踶
						,{	HORSEUNIQUE_THOUSAND,	1	}	// < 8		õ����
						,{	HORSEUNIQUE_RED,		1	}	// < 9		���丶
						,{	HORSEUNIQUE_STEEL,		1	}	// < 10		ö�⸶
						,{	HORSEUNIQUE_RUDOLF,		10	}	// < 20		�絹��
					};

					cltUniqueRange* pChristmasEvent = NULL;
					SI32			siCount = 0;

					SYSTEMTIME st_eventstart;
					SYSTEMTIME st_eventend;
					ZeroMemory(&st_eventstart, sizeof(st_eventstart));
					ZeroMemory(&st_eventend,   sizeof(st_eventend));

					if(pclClient->IsWhereServiceArea(ConstServiceArea_Taiwan))
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 11;	st_eventstart.wDay = 27;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 27;

						pChristmasEvent = TaiwanChristmasEvent_SmallMedal;
						siCount = sizeof(TaiwanChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else if(pclClient->IsWhereServiceArea(ConstServiceArea_USA))
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 12;	st_eventstart.wDay = 12;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 27;	

						pChristmasEvent = ChristmasEvent_SmallMedal;
						siCount = sizeof(ChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else if(pclClient->IsWhereServiceArea(ConstServiceArea_Japan))
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 12;	st_eventstart.wDay = 12;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 26;	st_eventend.wHour = 11;	

						pChristmasEvent = ChristmasEvent_SmallMedal;
						siCount = sizeof(ChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else if(pclClient->IsWhereServiceArea(ConstServiceArea_English))
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 12;	st_eventstart.wDay = 04;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 27;

						pChristmasEvent = ChristmasEvent_SmallMedal;
						siCount = sizeof(ChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else if(pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina))//NHN�߱��� ũ���������̺�Ʈ�� ���״� �Ⱓ�߰�
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 12;	st_eventstart.wDay = 04;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 27;

						pChristmasEvent = ChristmasEvent_SmallMedal;
						siCount = sizeof(ChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else if ( pclClient->IsWhereServiceArea(ConstServiceArea_EUROPE) )
					{
						st_eventstart.wYear = 2007;		st_eventstart.wMonth = 12;	st_eventstart.wDay = 04;
						st_eventend.wYear = 2007;		st_eventend.wMonth = 12;	st_eventend.wDay = 27;

						pChristmasEvent = ChristmasEvent_SmallMedal;
						siCount = sizeof(ChristmasEvent_SmallMedal) / sizeof(cltUniqueRange);
					}
					else
					{
						st_eventstart.wYear = 2001;		st_eventstart.wMonth = 1;	st_eventstart.wDay = 1;
						st_eventend.wYear = 2001;		st_eventend.wMonth = 1;	st_eventend.wDay = 2;
					}

					if(TimeInBounds(&pclserver->sTime, &st_eventstart, &st_eventend))
					{
						if(pChristmasEvent != NULL)
							horseunique = GetUniqueWithRange( pChristmasEvent, siCount, 100);
					}
					else
					{
						horseunique = GetUniqueWithRange( ItemUnique_5600_SmallMedal, sizeof(ItemUnique_5600_SmallMedal) / sizeof(cltUniqueRange), 1000);
					}

					// �������� ��������.
					if(horseunique == 0)		horseunique	= HORSEUNIQUE_BROWN;

					if ( pclClient->siServiceArea == ConstServiceArea_China )
					{
						horseunique = HORSEUNIQUE_BROWN;
					}

					// �ʱ� �ɷ�ġ�� �븸�� �ٸ��� ������ (PCK - 2007.09.11)
					//if (pclClient->IsWhereServiceArea(ConstSwitch_HorseAbility))
					if (pclClient->IsCountrySwitch(Switch_HorseAbility))
					{
						// �ɷ� ����, ��ο��� �˸� ����
						switch(horseunique)
						{
						case HORSEUNIQUE_BLACK:	
						case HORSEUNIQUE_WHITE:	
						case HORSEUNIQUE_ZEBRA:	
						case HORSEUNIQUE_THOUSAND:
						case HORSEUNIQUE_RED:	
						case HORSEUNIQUE_STEEL:
						case HORSEUNIQUE_RUDOLF:
							{
								speed = 1400;
								sistr = 500;
								sidex = 500;
								simag = 500;

								bnoticeallswitch = true;
							}
							break;
						case HORSEUNIQUE_BROWN:
							{
								speed = 1400;
								sistr = 500;
								sidex = 500;
								simag = 500;
							}
							break;
						}
					}
					else
					{
						// �ɷ� ����, ��ο��� �˸� ����
						switch(horseunique)
						{
						case HORSEUNIQUE_BLACK:	
						case HORSEUNIQUE_WHITE:	
						case HORSEUNIQUE_ZEBRA:	
						case HORSEUNIQUE_THOUSAND:
						case HORSEUNIQUE_RED:	
						case HORSEUNIQUE_STEEL:	
							{
								speed = 800;
								sistr	= 500;
								sidex	= 500;
								simag	= 500;

								bnoticeallswitch = true;
							}
							break;
						case HORSEUNIQUE_BROWN:
							{
								speed = 500 + (300  - (rand() % 600));
								sistr	= 50 + rand() % 10;
								sidex	= 50 + rand() % 10;
								simag	= 50 + rand() % 10;
							}
							break;
						case HORSEUNIQUE_RUDOLF:
							{
								speed = 1400;
								sistr = 500;
								sidex = 500;
								simag = 500;
							}
							break;
						}
					}

					// �� �̸� ����
					switch(horseunique)
					{
					case HORSEUNIQUE_BLACK:	{	TCHAR* pText1 = GetTxtFromMgr(2806);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_WHITE:	{	TCHAR* pText1 = GetTxtFromMgr(2805);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_ZEBRA:	{	TCHAR* pText1 = GetTxtFromMgr(2769);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_THOUSAND:{	TCHAR* pText1 = GetTxtFromMgr(2791);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_RED:	{	TCHAR* pText1 = GetTxtFromMgr(2753);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_STEEL:	{	TCHAR* pText1 = GetTxtFromMgr(5174);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_RUDOLF:{	TCHAR* pText1 = GetTxtFromMgr(3370);	StringCchCopy(horsename, 128, pText1);	}	break;
					case HORSEUNIQUE_BROWN:	{	}	break;
					}
				}
				break;

			case ITEMUNIQUE(5700): // ����ȣ
				{
					horseunique = HORSEUNIQUE_BEAST;
					TCHAR* pText1 = GetTxtFromMgr(6418);
					StringCchCopy(horsename, 128, pText1);
					speed = 800;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;

			case ITEMUNIQUE(5695): //  ����
				{
					horseunique = HORSEUNIQUE_WOLF;
					TCHAR* pText1 = GetTxtFromMgr(7059);
					StringCchCopy(horsename, 128, pText1);
					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_WOLF );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_WOLF );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_WOLF );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_WOLF );
				}
				break;
				//KHY - 0911 - ȣ���� �߰�.	
			case ITEMUNIQUE(5690): //  ȣ����
				{
					horseunique = HORSEUNIQUE_TIGER;
					TCHAR* pText1 = GetTxtFromMgr(5394);
					StringCchCopy(horsename, 128, pText1);
					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_TIGER );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_TIGER );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_TIGER );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_TIGER );
				}
				break;
				//KHY - 0622 - ����S �ʺ��ڿ�  ������ �߰�.
			case ITEMUNIQUE(5603): //  ���� �ʺ��ڿ� ���� ���	
				{
					horseunique = HORSEUNIQUE_FOAL;
					TCHAR* pText1 = GetTxtFromMgr(7505);
					StringCchCopy(horsename, 128, pText1);
					//KHY - 0820 - ����S ������ ����.
					// �븸�� ���� ���ӽð� 1500�Ϸ� ����.
					//if(pclClient->IsWhereServiceArea(ConstSwitch_HorseAbility)){	/*life = 3500;*/	}
					if(pclClient->IsCountrySwitch(Switch_HorseAbility)){	/*life = 3500;*/	}
					else													   {	life = 1050;	}	//���ӽð� 450��.

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_FOAL );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_FOAL );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_FOAL );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_FOAL );
				}
				break;
				//KHY - 0917 - ����S �������� ������ �Ŵ�.
			case ITEMUNIQUE(5620): // ������.
				{
					life	= 2000; //���ӽð� 1000��.

					//speed = 500 + (300  - (rand() % 600));

					speed = 1400;
					sistr	= 500 + rand() % 100;
					sidex	= 500 + rand() % 100;
					simag	= 500 + rand() % 100;
				}
				break;
				// kkm �߱� ����Ʈ ������
			case ITEMUNIQUE(5610): 
				{
					horseunique = HORSEUNIQUE_FOAL;
					TCHAR* pText1 = GetTxtFromMgr(7505);
					StringCchCopy(horsename, 128, pText1);
					life	= 1050; //���ӽð� 450��.

					speed	= 1500;
					sistr	= 3000;
					sidex	= 3000;
					simag	= 3000;
				}
				break;
				// kkm �߱� ��޸���
			case ITEMUNIQUE(5615):	
				{
					SI32 horseUniqueArray[6] = { HORSEUNIQUE_BLACK, HORSEUNIQUE_WHITE, HORSEUNIQUE_RED, 
						HORSEUNIQUE_THOUSAND, HORSEUNIQUE_STEEL, HORSEUNIQUE_ZEBRA };

					SI32 index = rand() % 6;
					horseunique = horseUniqueArray[index];

					// �ɷ� ����, ��ο��� �˸� ����
					speed = 800;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;

					// �� �̸� ����
					StringCchCopy( horsename, 128, pclClient->pclHorseManager->GetHorseName(horseunique) );

					pclClient->pclLog->FileConfigPrint( "horse", "%d %s", horseunique, horsename );
				}
				break;
				// PCK - �絹�� �޴� �߰� (07.11.28)
			case ITEMUNIQUE(5705):
				{
					horseunique = HORSEUNIQUE_RUDOLF;
					TCHAR* pText1 = GetTxtFromMgr(3370);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (�渶�޴� - 07.12.11)
			case ITEMUNIQUE(5710):
				{
					horseunique = HORSEUNIQUE_BLACK;
					TCHAR* pText1 = GetTxtFromMgr(2806);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (�鸶�޴� - 07.12.11)
			case ITEMUNIQUE(5715):
				{
					horseunique = HORSEUNIQUE_WHITE;
					TCHAR* pText1 = GetTxtFromMgr(2805);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (���丶�޴� - 07.12.11)
			case ITEMUNIQUE(5720):
				{
					horseunique = HORSEUNIQUE_RED;
					TCHAR* pText1 = GetTxtFromMgr(2753);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (��踶�޴� - 07.12.11)
			case ITEMUNIQUE(5725):
				{
					horseunique = HORSEUNIQUE_ZEBRA;
					TCHAR* pText1 = GetTxtFromMgr(2769);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (õ�����޴� - 07.12.11)
			case ITEMUNIQUE(5730):
				{
					horseunique = HORSEUNIQUE_THOUSAND;
					TCHAR* pText1 = GetTxtFromMgr(2791);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��µ��� �޴޵�� (ö�⸶�޴� - 07.12.11)
			case ITEMUNIQUE(5735):
				{
					horseunique = HORSEUNIQUE_STEEL;
					TCHAR* pText1 = GetTxtFromMgr(5174);
					StringCchCopy(horsename, 128, pText1);

					speed	= 1400;
					sistr	= 500;
					sidex	= 500;
					simag	= 500;
				}
				break;
				// PCK - ��Ÿ�޴� ��� (08.02.18)
			case ITEMUNIQUE(5685):
				{
					horseunique = HORSEUNIQUE_CAMEL;
					TCHAR* pText1 = GetTxtFromMgr(7936);
					StringCchCopy(horsename, 128, pText1);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_CAMEL );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_CAMEL );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_CAMEL );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_CAMEL );
				}
				break;
				// PCK : ����S�� �̺�Ʈ ȣ���� ��� (PCK : 08.04.01)
			case ITEMUNIQUE(5625):
				{
					horseunique = HORSEUNIQUE_TIGER2;
					TCHAR* pText1 = GetTxtFromMgr(5394);
					StringCchCopy(horsename, 128, pText1);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_TIGER2 );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_TIGER2 );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_TIGER2 );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_TIGER2 );
				}
				break;
				// PCK : �ڳ��� �߰� (08.06.12)
			case ITEMUNIQUE(5740):
				{
					horseunique = HORSEUNIQUE_ELEPHANT;
					TCHAR* pText1 = GetTxtFromMgr(8460);
					StringCchCopy(horsename, 128, pText1);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_ELEPHANT );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_ELEPHANT );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_ELEPHANT );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_ELEPHANT );
				}
				break;
				// PCK :��ȣ �߰� (08.08.14)
			case ITEMUNIQUE(5745):
				{
					horseunique = HORSEUNIQUE_WHITETIGER;
					TCHAR* pText = GetTxtFromMgr(8752);
					StringCchCopy(horsename, 128, pText);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_WHITETIGER );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_WHITETIGER );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_WHITETIGER );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_WHITETIGER );
				}
				break;
				// PCK :������� �߰� (08.08.14)
				//KHY - 1111 - ������� �߰�.	
			case ITEMUNIQUE(5748):
				{
					horseunique = HORSEUNIQUE_MOTORCYCLE;
					TCHAR* pText = GetTxtFromMgr(8795);
					StringCchCopy(horsename, 128, pText);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_MOTORCYCLE );
					sistr	= 4000;
					sidex	= 4000;
					simag	= 4000;

					// ������ �ð� ���� - 10000L = 20000�� = 120����. 
					SI32 siAddTime = 10000 * 2 * 60 ;

					// DB�� �����Ѵ�. 
					cltItem clitem2; // �ǹ� ���� ������.

					sDBRequest_TimeMeterRate_AddTime clMsg(GetCharID(), pclCI->GetPersonID(), TIMEMETERRATE_MOTORCYCLE, siAddTime, &clitem2, -1);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);				
				}
				break;
				// PCK : ����ġ �߰� (08.12.10)
			case ITEMUNIQUE(5749):
				{
					horseunique = HORSEUNIQUE_FIREHATCH;
					TCHAR* pText = GetTxtFromMgr(2788);
					StringCchCopy(horsename, 128, pText);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_FIREHATCH );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_FIREHATCH );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_FIREHATCH );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_FIREHATCH );
				}
				break;
				// �ռ��� - ä��� �鸶 2009-03-17
			case ITEMUNIQUE(5746):
				{
					horseunique = HORSEUNIQUE_WHITE_TEST;
					TCHAR* pText = GetTxtFromMgr(9897);
					StringCchCopy(horsename, 128, pText);

					speed	= 1500;
					sistr	= 2000;
					sidex	= 2000;
					simag	= 2000;
				}
				break;
				// PCK : ������Ʈ �߰� (09.07.30)
			case ITEMUNIQUE(5751):
				{
					horseunique = HORSEUNIQUE_BAPHOMET;
					TCHAR* pText = GetTxtFromMgr(30304);
					StringCchCopy(horsename, 128, pText);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_BAPHOMET );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_BAPHOMET );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_BAPHOMET );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_BAPHOMET );
				}
				break;
			
			case ITEMUNIQUE(5750): //  ȸ�� ���� �߰� : �ڱ���( 2009.8.30)
				{
					horseunique = HORSEUNIQUE_GRAYWOLF;
					TCHAR* pszText = GetTxtFromMgr(40047);
					StringCchCopy(horsename, 128, pszText);
					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_GRAYWOLF );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_GRAYWOLF );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_GRAYWOLF );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_GRAYWOLF );
				}
				break;
				// ���� : �����
			case ITEMUNIQUE(5752):
				{
					horseunique = HORSEUNIQUE_SASURI;
					TCHAR* pText = GetTxtFromMgr(14035);
					StringCchCopy(horsename, 128, pText);

					speed	= pclClient->pclHorseManager->GetFullSpeed( HORSEUNIQUE_SASURI );
					sistr	= pclClient->pclHorseManager->GetFullStr( HORSEUNIQUE_SASURI );
					sidex	= pclClient->pclHorseManager->GetFullDex( HORSEUNIQUE_SASURI );
					simag	= pclClient->pclHorseManager->GetFullMag( HORSEUNIQUE_SASURI );
				}
				break;
			default:
				return false;
			}

			//------------------------------
			// ���� ����. 
			//------------------------------
			SI32 sisex = ANIMAL_MALE;
			if(rand() % 5 == 0)
			{
				sisex = ANIMAL_FEMALE;
			}

			SI32 curhour = pclserver->pclTime->clDate.GetHourVary();


			SI32 randomvalue = rand() % 1000;
			TCHAR randomstr[128]=TEXT("");
			_itot(randomvalue, randomstr, 10);

			StringCchCat(horsename, 128, randomstr);

			cltDate cldate;
			cldate.MakeFullDateFromDateVary(0);

			cltHorse clHorse(horseunique, horsename, &pclserver->pclTime->clDate, sisex, life, 0,
				sistr, sidex, simag, speed, curhour,0,&cldate,0
				,&cldate,0
				,&cldate,0
				,&cldate,0
				,0);

			if(pclserver->pclTime->clDate.uiMonth == 0)
			{
				TCHAR* pText = GetTxtFromMgr(2807);
				if (pclClient->GameMode == GAMEMODE_SERVER)
					pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), pText, 
					pclserver->pclTime->clDate.uiYear, pclserver->pclTime->clDate.uiMonth, pclserver->pclTime->clDate.uiDay);
			}

			// �� ������ ���� �߰��Ѵ�. 
			SI32 index;
			if(pclCI->clHorseInfo.Add(&clHorse, &index) == true)
			{
				//KHY - 1001 - ��µ��� 5���� ���� ����.
				pclCI->clHorseInfo.SetCurrentShowHorseIndex(index);

				// DB�� ���� �߰��Ѵ�.  // index,
				UpdateHorseToDB((cltServer*)pclClient, index, &clHorse, SETHORSE_REASON_MAKE);

				// ���ΰ� �̿����� �� ������ ������. 
				SendNeighbourMyHorseStatus(index);

				//// ���� �������� ��ü �����Ѵ�. 
				if(bnoticeallswitch && GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
				{
					cltGameMsgResponse_GoodHorse clinfo((TCHAR*)GetName(), pclCI->GetPersonID(), horseunique, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_GOODHORSE, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
				}

				//cyj �� �����ϸ� ���κ��丮�� �ִ� ������ ���� ���������� �߰�
				sDBRequest_PersonItemInfoGet clMsg(siID, pclCI->GetPersonID());
				pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);

			}
			else
			{
				cltGameMsgResponse_NoAddHorse clinfo( 0 ); // 0 = �� �߰� ����. - 
				cltMsg clMsg(GAMEMSG_RESPONSE_NOADDHORSE, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				return false;
			}

		}
		break;
		//==============================================================================================================================
		// ETC
		//==============================================================================================================================
	case ITEMTYPE_ETC:
		{
			if(clitem.siUnique == ITEMUNIQUE(7860) )	// ��ȯ��
			{
				cltServer *pclserver = (cltServer*)pclClient;
				if (pclserver->pclCM->pclIDManager->GetNPCCharNumber() > MAX_NPC_NUMBER - 1000)
				{
					return false;
				}

				if (GetMapIndex() == MAPINDEX_BEGINNER1 || GetMapIndex() == MAPINDEX_PALACE || GetMapIndex() == MAPINDEX_MOFUMOFULAND)
				{
					return false;
				}

				SI32 pos = 0 ;
				SI32 x, y;
				SI32 tempx, tempy, level;
				SI32 mapindex = 0;

				bool bSelectKind = false;

				SI32 randvalue = rand() % 100;
				SI32 cnt = 0;

				SI32 minSort = 0, maxSort = 0; 

				//cltValuesRange ItemUnique_7860_Values_Christmas[] = 
				//{
				//	{	10,		0,		10,		0	}	// < 10
				//	,{	39,		10,		40,		0	}	// < 49
				//	,{	29,		40,		100,	0	}	// < 78
				//	,{	5,		100,	150,	0	}	// < 83
				//	,{	5,		150,	160,	0	}	// < 88
				//	,{	1,		160,	170,	0	}	// < 89
				//	,{	10,		170,	171,	0	}	// < 99
				//	,{	1,		180,	190,	0	}	// < 100
				//};

				SI32 siCount = sizeof(ItemUnique_7860_Values)/ sizeof(cltValuesRange);
				cltValuesRange* pValuesRange = (cltValuesRange*)ItemUnique_7860_Values;

				bool bSantaRacoon = false;
				bool bKoinobory	= false;

					// ũ�������� �̺�Ʈ���� ��ȯ�� Ȯ���� ����ȴ�
					if ( true == pclserver->pclEventTimeManager->InEventTime(TEXT("ChristmasEvent"), &pclserver->sTime) )
					{
						SI16 siSantaRacoonPercent = 0;
						siSantaRacoonPercent = rand() % 10;
						// 1/10�� Ȯ���̴ϱ� 0�� ������ �̺�Ʈ ���� ����
						if ( 0 == siSantaRacoonPercent )
						{
							bSantaRacoon = true;
						}

						cltValuesRange* pValuesRange = (cltValuesRange*)ItemUnique_7860_Values;
						siCount = sizeof(ItemUnique_7860_Values) / sizeof(cltUniqueRange);

						//pValuesRange = ItemUnique_7860_Values_Christmas;
						//siCount = sizeof(ItemUnique_7860_Values_Christmas) / sizeof(cltUniqueRange);
					}
					// [����] ��� ��ũ���� ��ȯ�� Ȯ���� ����ȴ�
					else if ( true == pclserver->pclEventTimeManager->InEventTime(TEXT("GoldenWeekEvent"), &pclserver->sTime) )
					{
						SI16 siKoinoboryPercent = 0;
						siKoinoboryPercent = rand() % 10;
						// 1/10�� Ȯ���̴ϱ� 0�� ������ �̺�Ʈ ���� ����
						if ( 0 == siKoinoboryPercent )
						{
							bKoinobory = true;
						}

						cltValuesRange* pValuesRange = (cltValuesRange*)ItemUnique_7860_Values;
						siCount = sizeof(ItemUnique_7860_Values) / sizeof(cltUniqueRange);

						//pValuesRange = (cltValuesRange*)ItemUnique_7860_Values_GoldenWeek;
						//siCount = sizeof(ItemUnique_7860_Values_GoldenWeek) / sizeof(cltUniqueRange);
					}

					// ��Ÿ����, ���̳뺸���� �ƴ� �Ϲ����� ���� ��Ʈ���� ������ ���õ�����
					cltValuesRange* pValues = GetValuesWithRange(pValuesRange, siCount, 100);
					if(pValues)
					{
						minSort = pValues->siPara1;
						maxSort = pValues->siPara2;
					}

					// ������ ���õ�����
					if ( true == bSantaRacoon )
					{
						minSort = 1001;   // �̺�Ʈ ���� ��Ʈ ���� (���ǽĿ� �ɷ� �ϳ� ���� ������ ����)
						maxSort = 1002;   // �̺�Ʈ ���� ��Ʈ ����
					}

					// ���̳뺸���� ���� ������
					if( true == bKoinobory)
					{
						minSort = 1000;   // ���̳뺸�� ��Ʈ ����
						maxSort = 1001;   // ���̳뺸�� ��Ʈ ����
					}

					SI32 ValidKindCnt = 0;
					SI32 ValidKindArray[MAX_KINDINFO_NUMBER]= {0, };
					SI32 i = 0;
					for(  i = 0 ; i < MAX_KINDINFO_NUMBER ; i ++ )
					{
						if (pclClient->pclKindInfoSet->IsValidKind(i))
						{
							cltKindInfo *pclki = pclClient->pclKindInfoSet->pclKI[i];

							switch (pclClient->siServiceArea)
							{
							case ConstServiceArea_Korea :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_KOREA ) == false)
									continue;
								break;
							case ConstServiceArea_China :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_CHINA ) == false)
									continue;
								break;
							case ConstServiceArea_Japan :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_JAPAN ) == false)
									continue;
								break;
							case ConstServiceArea_English :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_ENGLISH ) == false)
									continue;
								break;
							case ConstServiceArea_Taiwan :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_TAIWAN ) == false)
									continue;
								break;
							case ConstServiceArea_USA :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_USA ) == false)
									continue;
								break;
							case ConstServiceArea_NHNChina :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_NHNCHINA ) == false)
									continue;
								break;
							case ConstServiceArea_EUROPE :
								if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_EUROPE ) == false)
									continue;
								break;
							}

							if (pclClient->pclKindInfoSet->pclKI[i]->IsAtb(ATB_MONSTER) == false 
								||	pclClient->pclKindInfoSet->GetSortLevel( i ) <= 0 )
							{
								continue;
							}

							if( pclClient->pclKindInfoSet->GetSortLevel( i ) > minSort
								&& pclClient->pclKindInfoSet->GetSortLevel( i ) <=maxSort )
							{
								ValidKindArray[ValidKindCnt] = i;
								ValidKindCnt++;
							}
						}					
					}

					if(ValidKindCnt > 0 &&  ValidKindCnt <= MAX_KINDINFO_NUMBER  )
					{
						SI32 rndIndex = rand() % ValidKindCnt;					

						if( ValidKindArray[rndIndex] > 0 )
						{
							mapindex = GetMapIndex();

							tempx = GetX();
							tempy = GetY();

							// ���͸� ��ġ�� ������ ���� ã�´�. 
							if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(	ValidKindArray[rndIndex] , tempx, tempy, 10, &x, &y, true) == false)
							{
								break;
							}

							level = rand() % 50 + 1;

							cltInnerStatusInfo clinnerstatus;
							clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

							SI32 id = pclserver->SetNPCChar(	ValidKindArray[rndIndex] , VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );

							if(pclCM->IsValidID(id))
							{
								pclserver->SendServerResponseMsg(0, SRVAL_SUMMONEGG_USED, ValidKindArray[rndIndex], 0, GetID());
							}
						}

					}
					else
					{
						return false;
					}
			}
			// 2007.4.16 �������� ��ȯ�� 2 - By. �����
			else if(clitem.siUnique == ITEMUNIQUE(7865))	// ����������ȯ��2
			{
				cltServer *pclserver = (cltServer*)pclClient;
				if (pclserver->pclCM->pclIDManager->GetNPCCharNumber() > MAX_NPC_NUMBER - 1000)
				{
					return false;
				}

				if (GetMapIndex() == MAPINDEX_BEGINNER1 || GetMapIndex() == MAPINDEX_PALACE || GetMapIndex() == MAPINDEX_MOFUMOFULAND)
				{
					return false;
				}

				SI32 pos = 0 ;
				SI32 x, y;
				SI32 tempx, tempy, level;
				SI32 mapindex = 0;

				bool bSelectKind = false;

				SI32 randvalue = rand() % 100;
				SI32 cnt = 0;

				SI32 SortLevel = 0;

				// Ȯ�����
				if( randvalue < 3 )			{		SortLevel = 1;		}
				else if( randvalue < 6)		{		SortLevel = 2;		}
				else if( randvalue < 9)		{		SortLevel = 3;		}
				else if( randvalue < 12)	{		SortLevel = 4;		}
				else if( randvalue < 15)	{		SortLevel = 5;		}
				else if( randvalue < 18)	{		SortLevel = 6;		}
				else if( randvalue < 11)	{		SortLevel = 7;		}
				else if( randvalue < 24)	{		SortLevel = 8;		}
				else if( randvalue < 27)	{		SortLevel = 9;		}
				else if( randvalue < 30)	{		SortLevel = 10;		}
				else if( randvalue < 33)	{		SortLevel = 11;		}
				else if( randvalue < 36)	{		SortLevel = 12;		}
				else if( randvalue < 39)	{		SortLevel = 13;		}
				else if( randvalue < 42)	{		SortLevel = 14;		}
				else if( randvalue < 45)	{		SortLevel = 15;		}
				else if( randvalue < 48)	{		SortLevel = 16;		}
				else if( randvalue < 51)	{		SortLevel = 17;		}
				else if( randvalue < 54)	{		SortLevel = 18;		}
				else if( randvalue < 57)	{		SortLevel = 19;		}
				else if( randvalue < 60)	{		SortLevel = 20;		}
				else if( randvalue < 63)	{		SortLevel = 21;		}
				else if( randvalue < 66)	{		SortLevel = 22;		}
				else if( randvalue < 69)	{		SortLevel = 23;		}
				else if( randvalue < 74)	{		SortLevel = 501;		} // (91~97) => (501~507) ��Ʈ���� �������� ����.
				else if( randvalue < 79)	{		SortLevel = 502;		}
				else if( randvalue < 84)	{		SortLevel = 503;		}
				else if( randvalue < 88)	{		SortLevel = 504;		}
				else if( randvalue < 82)	{		SortLevel = 505;		}
				else if( randvalue < 96)	{		SortLevel = 506;		}
				else if( randvalue < 100)	{		SortLevel = 507;		}

				SI32 ValidKindCnt = 0;
				SI32 ValidKindArray[MAX_KINDINFO_NUMBER]= {0, };
				SI32 i = 0;
				for(  i = 0 ; i < MAX_KINDINFO_NUMBER ; i ++ )
				{
					if (pclClient->pclKindInfoSet->IsValidKind(i))
					{
						cltKindInfo *pclki = pclClient->pclKindInfoSet->pclKI[i];

						switch (pclClient->siServiceArea)
						{
						case ConstServiceArea_Korea :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_KOREA ) == false)
								continue;
							break;
						case ConstServiceArea_China :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_CHINA ) == false)
								continue;
							break;
						case ConstServiceArea_Japan :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_JAPAN ) == false)
								continue;
							break;
						case ConstServiceArea_English :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_ENGLISH ) == false)
								continue;
							break;
						case ConstServiceArea_Taiwan :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_TAIWAN ) == false)
								continue;
							break;
						case ConstServiceArea_USA :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_USA ) == false)
								continue;
							break;
						case ConstServiceArea_NHNChina :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_NHNCHINA ) == false)
								continue;
							break;
						case ConstServiceArea_EUROPE :
							if ( pclki->IsServiceAreaAtb( SERVICEAREA_ATB_EUROPE ) == false)
								continue;
							break;

						}

						if (pclClient->pclKindInfoSet->pclKI[i]->IsAtb(ATB_MONSTER) == false 
							||	pclClient->pclKindInfoSet->GetSortLevel( i ) <= 0 )
						{
							continue;
						}

						if( pclClient->pclKindInfoSet->GetSortLevel( i ) == SortLevel)
						{
							ValidKindArray[ValidKindCnt] = i;
							ValidKindCnt++;
						}
					}					
				}					

				if(ValidKindCnt > 0 &&  ValidKindCnt <= MAX_KINDINFO_NUMBER  )
				{
					SI32 rndIndex = rand() % ValidKindCnt;					

					if( ValidKindArray[rndIndex] > 0 )
					{
						// �����Գ� ��ȯ�˿��� �������� ���������� �̾Ƴ���.
						int num = (rand() % 5) + 1;
						int count = 0, created = 0;
						while( count < num)
						{
							count++;

							mapindex = GetMapIndex();

							tempx = GetX();
							tempy = GetY();

							// ���͸� ��ġ�� ������ ���� ã�´�. 
							if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(	ValidKindArray[rndIndex] , tempx, tempy, 10, &x, &y, true) == false)
							{
								continue;
							}

							level = rand() % 50 + 1;

							cltInnerStatusInfo clinnerstatus;
							clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

							SI32 id = pclserver->SetNPCChar(	ValidKindArray[rndIndex] , VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
							if(pclCM->IsValidID(id))
							{
								// �������� ��ȯ��2�� ���� ��ȯ�� �����̴�.
								cltCharServer* pclchar = (cltCharServer*)(pclClient->pclCM->CR[id]);
								pclchar->siCharMode = CHARMODE_SUMMON_EGG2;

								created++;
							}							
						}
						if(created > 0)		pclserver->SendServerResponseMsg(0, SRVAL_SUMMONEGG_USED, ValidKindArray[rndIndex], 0, GetID());
						else
							return false;
					}
				}
				else
				{
					return false;
				}
			}		
			//KHY - ���� ����  - 
			else if ( clitem.siUnique == ITEMUNIQUE(7975)) // å ����
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				cltServer* pclserver = (cltServer*)pclClient;

				SI32 siItemUnique = pclserver->pclBookBox->GetRandBookUnique();
				if ( siItemUnique )
				{
					cltItem clDrawItem;	// ��÷�ؼ� ���� ���������
					clDrawItem.Init();

					SI16 brareswitch = 0;

					if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clDrawItem, 0, 0, &brareswitch ) == false)
						return false;

					clDrawItem.SetItemNum(1);

					SI16 invpos;
					cltItem cltoitem;
					SI32 rtnvalue;
					if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
					{
						((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
						return false;
					}

					pclItemManager->AddBookBoxItemNum(clDrawItem.siUnique, clDrawItem.siItemNum);

					// ���ο� ��� - å���ڿ� ���� ���� ��ǰ�� ��踦 ����.
					//NStatistics_Add("Item", clDrawItem.siUnique, "BookBox", clDrawItem.siItemNum);


					if ( clitem.siUnique != 0 )
					{
						sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
				}
				return false;

			}
			// [����] ���̳븮��
			else if ( clitem.siUnique == ITEMUNIQUE(8114) )
			{
				cltServer *pclserver = (cltServer*)pclClient;
				if (pclserver->pclCM->pclIDManager->GetNPCCharNumber() > MAX_NPC_NUMBER - 1000)
				{
					return false;
				}

				SI32 siKind		= pclClient->GetUniqueFromHash( TEXT("KIND_KOINOBORYGREEN") );

				SI32 siMapIndex = GetMapIndex();
				SI32 siNowX		= GetX();
				SI32 siNowY		= GetY();

				SI32 siGetX		= 0;
				SI32 siGetY		= 0;

				SI32 siLevel	= 1;
				SI32 siEnergy	= 100;

				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

				cltMapCommon* pclMapCom = pclClient->pclMapManager->pclMapArray[siMapIndex];
				if ( NULL == pclMapCom )
				{
					return false;
				}

				// Ȥ�� �������� ���ҰͿ� ����ؼ� ��� ���ƺ���
				for ( SI32 siCount=0; siCount<10; siCount++ )
				{
					if ( false == pclMapCom->FindEmptyAreaForCharLocate(siKind, siNowX, siNowY, 20, &siGetX, &siGetY, true) )
					{
						continue;
					}

					SI32 siCharID = pclserver->SetNPCChar( siKind, VILLAGE_NONE, NULL, siLevel, siEnergy, siGetX, siGetY, siMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
					if ( pclCM->IsValidID(siCharID) )
					{
						// ����Ʈ ���� ���ͷ� �ź� ����
						cltCharServer* pclMonster = (cltCharServer*)pclClient->pclCM->GetCharServer(siCharID);
						if ( NULL == pclMonster )
						{
							continue;
						}

						pclMonster->clIdentity.MakeSoulBound( IDENTITY_SOULBOUND, pclCI->GetPersonID() );
						break;
					}							
				}

			}
			// PCK : �Ҿ���� ���迡�� ������ ���ȭ��, �ݼӻ������ ��Ŭ������ ��� ���ϰ� �Ѵ�. (09.05.13)
			else if(clitem.siUnique == ITEMUNIQUE(8115) || clitem.siUnique == ITEMUNIQUE(8116))
			{
				return false;
			}
			// PCK : �Ҿ���� ���迡�� ������ ���� ���ž��� ����ϸ� Ʈ���ɶ�񽺷� �����Ѵ�. (09.05.13)
			else if(clitem.siUnique == ITEMUNIQUE(8117))
			{
				SI32 id = GetID();

				if(pclClient->pclCM->CR[id]->pclCI->clQuestInfo.IsQuestGoing(QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS))
				{
					SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;

					SI16 siKind = pclClient->GetUniqueFromHash("KIND_TRICERAMONS");

					SI16 siBufIndex = -1;

					if ( true == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) )
					{
						siBufIndex = pclCI->clBI.clBufInfo.FindBufSlot( BUF_TRANSFORM );
					}
					else
					{
						siBufIndex = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_TRANSFORM );
					}

					if ( -1 < siBufIndex )
					{
						stBuf addBuf(BUF_TRANSFORM, siKind, usetime);
						((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( siBufIndex, &addBuf ,false, 0, NULL, 0);
					}
				}

				return false;
			}
			// PCK : �Ҿ���� ���迡�� ������ ���ݹ������ ����ϸ� ���ݷ� 30%���� ������ ��´�.
			else if ( clitem.siUnique == ITEMUNIQUE(8118) )
			{
				SI32 id = GetID();

				SI32 siUseItem = 0;

				siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // ���ǽð� 48�а�.

				SI16 siEmptySlot = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_QUEST_ATTACK, false );

				if ( -1 < siEmptySlot )
				{
					stBuf addBuf(BUF_QUEST_ATTACK, 0, siUseItem);
					AddBufThroughDB( siEmptySlot, &addBuf , false , 0 , &clitem );
				}

				return false;
			}
			else if ( (ITEMUNIQUE(8119) == clitem.siUnique) || (ITEMUNIQUE(8120) == clitem.siUnique) )
			{
				if ( FALSE == IsMarried() )
				{
					return false;
				}

				SI32 siNowHourVary		= pclserver->pclTime->clDate.GetHourVary();
				SI32 siSetLimitHourVary	= siNowHourVary + 24; // ���ӽð� 24�ð�(���ǽð� 48���� ���Ѵ�)
				SI32 siGetPersonID		= pclCI->GetPersonID();
				SI32 siGetLoveLevel		= pclMarriage->GetLoveLevel();

				/*
				if ( MARRIAGE_LOVE_LEVEL_10 <= siGetLoveLevel )
				{
					return false;
				}
				*/

					// �����ۿ� ���� �������� ������ �ٸ��� �Ѵ�
					if ( ITEMUNIQUE(8119) == clitem.siUnique )
					{
						siGetLoveLevel += 1;

						// �ִ� �����϶��� ������� �ð��� �þ�Ƿ� ������ 10���� ���ش�
						if ( MARRIAGE_LOVE_LEVEL_10 <= siGetLoveLevel )
						{
							siGetLoveLevel = MARRIAGE_LOVE_LEVEL_10;
						}
					}
					else if ( ITEMUNIQUE(8120) == clitem.siUnique )
					{
						siGetLoveLevel = MARRIAGE_LOVE_LEVEL_10;
					}

					// ����� ĳ���͵� ���� ������Ʈ
					SI32			siMateCharID	= pclserver->pclCM->GetIDFromPersonID( pclMarriage->GetMatePersonID() );
					cltCharServer*	pclMateChar		= pclserver->pclCM->GetCharServer( siMateCharID );
					if ( NULL == pclMateChar )
					{
						return false;
					}

					if ( FALSE == pclMateChar->IsMarried() )
					{
						return false;
					}

					// �������� �̸� ������ �ش�. DB�ٳ�»��� ����ڰ� �� �������� ���� �׶��� �������� �ö󰡾� �ϴϱ�
					// ��ĳ����
					pclMarriage->SetLoveLevel( siGetLoveLevel );
					pclMarriage->SetLimitHourVary( siSetLimitHourVary );
					pclMarriage->SetUseHourVary( siNowHourVary );

					// �����
					pclMateChar->pclMarriage->SetLoveLevel( siGetLoveLevel );
					pclMateChar->pclMarriage->SetLimitHourVary( siSetLimitHourVary );

					// DB�� �����ش�
					sDBRequest_Marry_Love_Set clMsg( siGetPersonID, siNowHourVary, siSetLimitHourVary, siGetLoveLevel );
					pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
			}
			//----------------------------------------------------------------------------------
			//���ֵ��̹̼� �̿�� : ��ȹ ���� �������� ������ �ο�/��� ����� �ƴ� ����Ʈ �ο� ������� ����Ǽ� �ڵ� ����
			//else if(clitem.siUnique == ITEMUNIQUE(8154))
			//{	
			//	// ���ֵ����� ��쿡�� ��밡��.
			//	if (  true == pclserver->pclEventTimeManager->InEventTime(TEXT("GoonzuDay_Week"), &pclserver->sTime) )
			//	{
			//		if(Make_GoonzuDayMission() == false)
			//		{
			//			// �ϴ� ���� �������� ���� ��Ȳ�� �߻��ϴ°Ϳ� ���ؼ� ����
			//			return false;
			//		}
			//	}	
			//}
			//------------------------------------------------------------------------------------------------------
			// ���Ŀ� ��Ű
			else if ( (ITEMUNIQUE(8122) == clitem.siUnique))
			{
				if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
				{
					if( pclFamily != NULL )
					{
						SI32 siMyFamilyClass = pclFamily->GetMyClass_InFamily() ;

						if ( MYCLASS_IN_FAMILY_CHILDREN == siMyFamilyClass )
						{
							SI32 siMyPersonID = pclCI->GetPersonID()	;
							SI32 siCookieEndTime_Now = pclFamily->GetMyCookie_EndTime( siMyPersonID ) ;	// ���� ���� ��Ű �ð�
							SI32 siHourVary = pclserver->pclTime->clDate.GetHourVary()	;			// ���� ���� �ð�.

							// �ϴ� ���� ���� ��Ű �ð��� �������� Ȯ���Ѵ�.
							if ( siCookieEndTime_Now <= siHourVary )	// ���� ��Ű ���� �ð��� ������. 
							{

								SI32 siEndDatevary   = siHourVary	+ 24	;
								SI32 siLimitDatevary = siHourVary	+ 10	;
								SI32 siCookieLevel   = USE_COOKIE_LEVEL_1	;	// �������� �ٽ� 1
								// DB�� ���.
								// DB�۾��� ���ؼ� ���� �ȳ����� �ٷ�..Ŭ��� ������ 
								sDBRequest_Set_My_CookeEffect clMsg( siMyPersonID, siEndDatevary, siLimitDatevary, siCookieLevel );
								pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
							}
							else	// ���� ��Ű ��� �ð��� ���� �ִ�.
							{
								SI32 siEndDatevary = siHourVary	+ 24	;		// ��Ű ���� �Ѱ� �ð�
								SI32 siLimitDatevary = siHourVary	+ 10	;	// ��Ű ��� ���� �ð� 		

								SI32 siCookieLevel = pclFamily->GetMyCookieLevel(siMyPersonID )	;
								siCookieLevel += 1 ;// �� �������� �Ѵܰ� ���� 
								if ( siCookieLevel >= USE_COOKIE_LEVEL_5) 
								{
									siCookieLevel = USE_COOKIE_LEVEL_5	;
								}

								// DB�� ���.
								// DB�۾��� ���ؼ� ���� �ȳ����� �ٷ�..Ŭ��� ������ 
								sDBRequest_Set_My_CookeEffect clMsg( siMyPersonID, siEndDatevary, siLimitDatevary, siCookieLevel );
								pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);

							}
						}
						else
						{
							return false;	
						}
					}
				}				
			}
			// PCK : ������ Ÿ�� ETC�� �̵� (09.06.17)
			else if ( ITEMUNIQUE(8121) == clitem.siUnique )
			{
				SI32 siMonsterKind	= pclClient->GetUniqueFromHash( TEXT("KIND_QUESTEMPERORMASTER") );
				if ( 0 >= siMonsterKind )
				{
					return false;
				}

				SI32 siGetMapIndex	= GetMapIndex();
				if ( (0 > siGetMapIndex) || (MAX_MAP_NUMBER <= siGetMapIndex) )
				{
					return false;
				}

				SI32 siSourceX		= GetX();
				SI32 siSourceY		= GetY();
				SI32 siDestX		= 0;
				SI32 siDestY		= 0;

				bool bIsCreated		= false;

				cltMapCommon* pclMapCommon = pclClient->pclMapManager->pclMapArray[siGetMapIndex];
				if ( NULL == pclMapCommon )
				{
					return false;
				}

				// Ȥ�� ���� ��ġ�� ã�� ���ߴٸ� �����ϰ� ��ġ�� ��� �� ���鼭 ��ġ�� ã�´�
				for ( SI32 siCount=0; siCount<10; siCount++ )
				{
					if ( false == pclMapCommon->FindEmptyAreaForCharLocate(siMonsterKind, siSourceX, siSourceY, 10, &siDestX, &siDestY, true) )
					{
						continue;
					}

					cltInnerStatusInfo clinnerstatus;
					clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

					SI32 siCreatedID = pclserver->SetNPCChar( siMonsterKind, VILLAGE_NONE, NULL, 0, 0, siDestX, siDestY, siGetMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
					if ( pclCM->IsValidID(siCreatedID) )
					{
						// ����Ʈ ���� ���ͷ� �ź� ����
						cltCharServer* pclMonster = (cltCharServer*)pclClient->pclCM->GetCharServer(siCreatedID);
						if ( NULL == pclMonster )
						{
							continue;
						}

						pclMonster->clIdentity.MakeQuest( IDENTITY_QUEST, pclCI->GetPersonID(), GetCharUnique() );
						pclMonster->dwTimerClock = pclserver->CurrentClock;

						bIsCreated = true;

						break;
					}							
				}

				if ( false == bIsCreated )
				{
					return false;
				}
			}

			// ��Ƽ����Ʈ ���� ������ ���� 
			else if (	ITEMUNIQUE(8148) == clitem.siUnique || ITEMUNIQUE(8136) == clitem.siUnique ||
						ITEMUNIQUE(8140) == clitem.siUnique || ITEMUNIQUE(8144) == clitem.siUnique ||
						ITEMUNIQUE(8125) == clitem.siUnique || ITEMUNIQUE(8129) == clitem.siUnique)
			{
				switch (clitem.siUnique)
				{
				// �Ϲ�����Ʈ ���� 
				case ITEMUNIQUE(8136):
				case ITEMUNIQUE(8140):
				case ITEMUNIQUE(8144):
				case ITEMUNIQUE(8148):
					{
						SI16 siIsHaveBuf[4] = {BUF_EXP_UP, BUF_ATTACKUP, BUF_DEFENSEUP, BUF_MAKEEXPUP};

						// ����Ҽ� �ִ� �����鸸 �߷����ϴ�.
						for(SI32 i = 0; i < 4; i++)
						{
							if ( pclCI->clBI.clBufInfo.IsHaveBuf(siIsHaveBuf[i]) == true)
								siIsHaveBuf[i] = 0;
						}

						// ����Ҽ� �ִ� �������� �迭�� �� ���� �մϴ�.
						SI32 siCount = 0; // ����Ҽ� �ִ� ������ ����
						SI16 siSelectBufType[4] = {0,};

						for(i = 0; i < 4; i++)
						{
							if(siIsHaveBuf[i] > 0)
							{
								siSelectBufType[siCount] = siIsHaveBuf[i];
								siCount++;
							}
						}

						// ����Ҽ� �ִ� ������ ���ٸ� Return;
						if(siCount <= 0)
							return false;

						// ���⼭ ���� ���� �ִ� ���� üũ �� ����
						SI32 siAddBufIndex = rand()%siCount;

                        
						SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;  // 1��  = 48��
						SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( siSelectBufType[siAddBufIndex], false );

						SI16 siPercent = 0;

						switch(siSelectBufType[siAddBufIndex])
						{
						case BUF_EXP_UP:	siPercent = 20;	break;
						case BUF_ATTACKUP:	siPercent = 20;	break;
						case BUF_DEFENSEUP:	siPercent = 20;	break;
						case BUF_MAKEEXPUP:	siPercent = 20;	break;
						}

						if ( index > -1 )
						{
							stBuf addBuf(siSelectBufType[siAddBufIndex], siPercent, usetime);
							AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
						}							
					}
					break;

				// �ǽù�����Ʈ ����
				case ITEMUNIQUE(8125):
				case ITEMUNIQUE(8129):
					{
						SI16 siIsHaveBuf[4] = {BUF_EXP_UP, BUF_ATTACKUP, BUF_DEFENSEUP, BUF_MAKEEXPUP};

						// ����Ҽ� �ִ� �����鸸 �߷����ϴ�.
						for(SI32 i = 0; i < 4; i++)
						{
							if ( pclCI->clBI.clBufInfo.IsHaveBuf(siIsHaveBuf[i]) == true)
								siIsHaveBuf[i] = 0;
						}

						// ����Ҽ� �ִ� �������� �迭�� �� ���� �մϴ�.
						SI32 siCount = 0; // ����Ҽ� �ִ� ������ ����
						SI16 siSelectBufType[4] = {0,};

						for(i = 0; i < 4; i++)
						{
							if(siIsHaveBuf[i] > 0)
							{
								siSelectBufType[siCount] = siIsHaveBuf[i];
								siCount++;
							}
						}

						// ����Ҽ� �ִ� ������ ���ٸ� Return;
						if(siCount <= 0)
							return false;

						// ���⼭ ���� ���� �ִ� ���� üũ �� ����
						SI32 siAddBufIndex = rand()%siCount;


						SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;  // 1��  = 48��
						SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( siSelectBufType[siAddBufIndex], false );

						SI16 siPercent = 0;

						switch(siSelectBufType[siAddBufIndex])
						{
						case BUF_EXP_UP:	siPercent = 50;	break;
						case BUF_ATTACKUP:	siPercent = 50;	break;
						case BUF_DEFENSEUP:	siPercent = 50;	break;
						case BUF_MAKEEXPUP:	siPercent = 50;	break;
						}

						if ( index > -1 )
						{
							stBuf addBuf(siSelectBufType[siAddBufIndex], siPercent, usetime);
							AddBufThroughDB( index, &addBuf , true , itempos , &clitem );
						}		
					}
					break;
				}
			}
			
		}
		break;

	case ITEMTYPE_TICKET:
		{
			if ( clitem.siUnique == ITEMUNIQUE(14300) || clitem.siUnique == ITEMUNIQUE(14400) || clitem.siUnique == ITEMUNIQUE(14500) ) // �����,����,��»�
			{
				pclClient->pclGameEventManager->CheckPrizeEvent(GetCharUnique(),clitem.siUnique);
			}
		}
		break;

	case ITEMTYPE_CRYSTAL:				//��Ƽ��Ʈ ����ü.
		{
			return false;
		}
		break;
	case ITEMTYPE_COMPOSITIONMATERIAL:	//��Ƽ��Ʈ �ռ�����
		{
			return false;
		}
		break;
	case ITEMTYPE_EVENTITEM:			//�̺�Ʈ ������
		{
			// [����] �߼� �̺�Ʈ. �߼����� ��������. => 2008-8-7
			if(itemunique == ITEMUNIQUE(13047))
			{
				SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;// 48�а����				
				SI16 siBufType	=  BUF_STATUE_UP_STR + ( rand() % 5 );
				SI16 index		= pclCI->clBI.clBufInfo.FindEmptySlot( siBufType, false );

				if ( index > -1 )
				{
					stBuf addBuf( siBufType, 5, usetime );
					AddBufThroughDB( index, &addBuf , false , itempos , &clitem );
				}

				return false ;
			}
			//---------------------------------------------------------------------------------------------------------------
			//	����ã�� �̺�Ʈ
			//	
			//
			//---------------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13058) )
			{

				//MakeTreasureQuest_Start()	;


			}			
			//-------------------------------------------------------------------------------------------------------------

			// [����] �߼� �̺�Ʈ. ���׿��� ��������. => 2008-8-14
			else if(itemunique == ITEMUNIQUE(13048))
			{
				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;// 48�а����				
				SI16 index	 = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_EGGMOONCAKE, false );

				if ( index > -1 )
				{
					stBuf addBuf( BUF_EVENT_EGGMOONCAKE, 20, usetime );
					AddBufThroughDB( index, &addBuf , false , itempos , &clitem );
				}

				return false ;
			}
			//----------------------------------------------------------------------------------
			// �������
			else if(clitem.siUnique == ITEMUNIQUE(13025))
			{	
				// Ư�� ����Ʈ�� �����. 
				if(MakeSpecialQuest() == false)
				{
					// �� �Ǿ����� �˸���. 
					((cltServer*)pclClient)->SendServerResponseMsg( 0, SRVAL_LOTTOFAIL,  0, 0, GetCharUnique() );
				}
			}
			//------------------------------------------------------------------------------------------------------

			else if ( clitem.siUnique == ITEMUNIQUE(13042) ) // ����
			{
				if( GetCurrentVillageUnique() <= 0 ) 
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_FEAST_FAIL_USE_ONLY_VILLAGE, 0, 0, GetID());					
					return false;
				}

				SI16 FeastKind[4] = {3,5,6,7};

				SI16 randFeast[cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE];


				SI16 siStartPosX = (SI16)GetX();
				SI16 siStartPosY = (SI16)GetY();

				randFeast[0] = FeastKind[ rand() % 4 ];

				// ������ �ִ� ��� Ŭ���̾�Ʈ�� ���� ������
				cltGameMsgResponse_FeastUseEffect sendMsg( randFeast, cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE, siStartPosX, siStartPosY);
				cltMsg clMsg( GAMEMSG_RESPONSE_FEAST_USEEFFECT, sizeof( sendMsg ), (BYTE*)&sendMsg );

				pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg, GetCurrentVillageUnique());
			}
			//----------------------------------------------------------------------------------
			// ũ�������� �縻
			else if ( clitem.siUnique == ITEMUNIQUE(13002))
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 ItemUnique = 0;	
				ItemUnique = GetUniqueWithRange( ItemUnique_13002_ItemNum, sizeof(ItemUnique_13002_ItemNum) / sizeof(cltUniqueRange), 1000);

				SI16 brareswitch = 0;
				SI32 usedate	 = 0;					// ���Ⱓ.
				cltItem clDrawItem;						// ��÷�ؼ� ���� ���������
				clDrawItem.Init();


				SI32 ItemCnt = 1;
				switch(ItemUnique)
				{
				case 24094:		ItemCnt = 1; usedate = 1; break;
				case 7865:	
				case 3915:		ItemCnt = 3;	break;
				case 18161:		usedate = 7;	break;
				case 23581:		usedate = 7;	break;
				default:		ItemCnt = 1;	break;
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				clDrawItem.SetItemNum( ItemCnt );

				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}

				// ��ǰ ����ϱ� ����Ʈ �������̾����� Ȯ���Ͽ� ��ġ�Ѵ�. 
				IncQuestPara(QUEST_CLEAR_COND_USEITEM, clitem.siUnique, clitem.siItemNum);

				return false;

			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13063) && true == pclClient->IsCountrySwitch(Switch_NewYearEvent_2010) )	// 2010�ų��̺�Ʈ - ������Ű - 2009.10.14
			{
				if(pclClient->pclEventTimeManager->InEventTime("Fortune_Event", &pclserver->sTime) == false )	return false	;

				// '��' ������ ������ ������ ����Ʈ�� ���� ����
				if ( true == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_FORTUNE_BAD ) )
				{
					if(MakeQuest_RemoveUnLuckStatus() == false)
					{
						// �ϴ� ���� �������� ���� ��Ȳ�� �߻��ϴ°Ϳ� ���ؼ� ����

						return false;
					}

					// ��񿡼� ��Ű�� 1�� �ٿ��ְ�
					if ( clitem.siUnique != 0 )
					{
						sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}

					cltMissionQuestInfo* pQuestInfo = &pclCI->clQuestInfo.clMissionQuestInfo;

					// � �̱�
					cltValuesRange* pFortune = NULL;

					pFortune = GetValuesWithRange( ItemValue_UnFortune, sizeof(ItemValue_UnFortune) / sizeof(cltValuesRange), 100);
					if ( NULL == pFortune ) return false;

					SI32 siFortuneQuality = pFortune->siPara2;
					SI32 siTextUnique = pFortune->siPara3;

					// '��' ������ �޾Ҵٰ� Ŭ���̾�Ʈ�� ��Ŷ ����
					cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclCI->GetPersonID(), 3, siTextUnique, 0, pQuestInfo->clQuestClearConditionInfo.siFlag, pQuestInfo->clQuestClearConditionInfo.siPara1, pQuestInfo->clQuestClearConditionInfo.siPara2 );
					cltMsg clMsg( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
					SendNetMsg( (sPacketHeader*)&clMsg );

					return false;
				}

				// '��' ������ ������ �������� ��ƾ���� ó��
				// �� �κ� ���� Ȯ��?
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13063, sizeof(ItemValue_13063) / sizeof(cltValuesRange), 100);
				if(pItemValue == NULL)			return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				cltItem clOutPutItem;
				clOutPutItem.Init();

				// ���� �����ۿ� ���� ó��
				if ( -1 == ItemUnique )		// ��ϰ�쿣 � ���� ó��
				{
					SI32 siBuffNameUnique = -1;		// ���� �̸��� ����ũ�� ������ ����

					//////////////////////////////////////////////////////////////////////////
					// � �̱�
					cltValuesRange* pFortune = NULL;

					pFortune = GetValuesWithRange( ItemValue_Fortune, sizeof(ItemValue_Fortune) / sizeof(cltValuesRange), 1000);
					if ( NULL == pFortune ) return false;

					SI32 siFortuneQuality = pFortune->siPara2;
					SI32 siTextUnique = pFortune->siPara3;


					//////////////////////////////////////////////////////////////////////////
					// ��� ��� ó��
					if ( 1 == siFortuneQuality )		// ��� �϶�
					{
						// �������� ���� (13358)
						ItemUnique = 13358;

						if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
							return false;

						Count = 1;
						clOutPutItem.SetItemNum( Count );

						//------------------------------------------
						// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
						//------------------------------------------
						SI16 invpos;
						cltItem cltoitem;
						SI32 rtnvalue;
						if(CanAddInv(INVMODE_ALL, &clOutPutItem, &invpos, &cltoitem, &rtnvalue) == false)
						{
							((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
							return false;
						}

						if ( clitem.siUnique != 0 )
						{
							sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clOutPutItem, pclItemManager->CanPile(clOutPutItem.siUnique), clOutPutItem.IsCreateSID(pclItemManager), false );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}

						//////////////////////////////////////////////////////////////////////////
						// hp, mp�� �����ϰ� 50~500 ä���.
						SI16 siHealAmount = 0;

						siHealAmount = rand() % 451 + 50;	// ������ 50~500 ����
						IncreaseLife( siHealAmount );

						// ������� ���, Ŭ���̾�Ʈ�� �����ش�. 
						if(IsPC(GetCharUnique()))
						{
							cltGameMsgResponse_IncLife clInfo(GetCharUnique(), pclCI->clIP.GetLife(),  siHealAmount, clPB.siReservedLife, 0, INCMANA_REASON_HEAL);
							cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
							SendNetMsg((sPacketHeader*)&clMsg);
						}

						siHealAmount = rand() % 451 + 50;	// ������ 50~500 ����
						IncreaseMana( siHealAmount );

						// ������� ���, Ŭ���̾�Ʈ�� �����ش�. 
						if(IsPC(GetCharUnique()))
						{
							cltGameMsgResponse_IncMana clInfo(GetCharUnique(), pclCI->clIP.GetMana(),  siHealAmount, INCMANA_REASON_HEAL);
							cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
							SendNetMsg((sPacketHeader*)&clMsg);
						}
						//////////////////////////////////////////////////////////////////////////

						// '���'�� ���Դٰ� Ŭ���̾�Ʈ�� ��Ŷ ���� (Ŭ�� �ʿ��� ��ȭ���ڵ��� ó���� �� ��Ŷ ó���ο���)
						cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclCI->GetPersonID(), siFortuneQuality, siTextUnique, 0, 0, 0, 0 );
						cltMsg clMsg( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
						SendNetMsg( (sPacketHeader*)&clMsg );

						return false;
					}
					else if ( 2 == siFortuneQuality )	// �� �϶�
					{
						SI16 index = -1;
						index = pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_FORTUNECOOKIE);
						// 1. '��'���� �����ΰ�?
						if ( -1 < index )
						{
							// ������ �ɷ��ִ� ������ �����Ѵ�.
							stBuf DelBuf( pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0 );
							sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), index, &DelBuf );
							((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}

						//////////////////////////////////////////////////////////////////////////
						cltValuesRange clBufRange[30];
						ZeroMemory( clBufRange, sizeof(clBufRange) );

						SI32 siOriginalCount = sizeof(ItemValue_Fortune_Buf) / sizeof(ItemValue_Fortune_Buf[0]);
						siOriginalCount = min( siOriginalCount, 30 );

						SI32 siRealCount	= 0;	// ���� ������ ������ �Ǵ� ����
						SI32 siRealPercent	= 0;	// ���� Ȯ��

						for ( SI32 siIndex=0; siIndex<siOriginalCount; siIndex++ )
						{
							// ���� ���� ���� ������ ������ �ش�
							if ( false == pclCI->clBI.clBufInfo.IsHaveBuf(ItemValue_Fortune_Buf[siIndex].siPara1) )
							{
								clBufRange[siRealCount++].Set( ItemValue_Fortune_Buf[siIndex].siPercent, ItemValue_Fortune_Buf[siIndex].siPara1, ItemValue_Fortune_Buf[siIndex].siPara2, ItemValue_Fortune_Buf[siIndex].siPara3 );

								siRealPercent += ItemValue_Fortune_Buf[siIndex].siPercent;
							}
						}
						
						// ���� �ɾ��� ������ ����
						cltValuesRange* pFortuneBuf = NULL;
						pFortuneBuf = GetValuesWithRange(clBufRange, siRealCount, siRealPercent);
						if(pFortuneBuf == NULL)			return false;

						SI32 siBufType			= pFortuneBuf->siPara1;
						SI32 siBufValue			= pFortuneBuf->siPara2;
						siBuffNameUnique		= pFortuneBuf->siPara3;	// ���� �̸� ����ũ
						SI32 siUseTime			= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;// 48�а����

						// ���� �ɾ��� ������ ���� Ÿ���� ������ ������ �����.
						SI16 index0 = -1;
						index0 = pclCI->clBI.clBufInfo.FindEmptySlot( siBufType );
						if ( -1 >= index0 )
						{
							return false;
						}

						stBuf addBuf0( siBufType, siBufValue, siUseTime, BUF_GET_TYPE_FORTUNECOOKIE );
						AddBufThroughDB( index0, &addBuf0 , false , itempos , &clitem );

						// ��񿡼� ��Ű�� 1�� �ٿ��ְ�
						if ( clitem.siUnique != 0 )
						{
							sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}

						//////////////////////////////////////////////////////////////////////////
						// hp, mp�� �����ϰ� 50~500 ä���.
						SI16 siHealAmount = 0;

						siHealAmount = rand() % 451 + 50;	// ������ 50~500 ����
						IncreaseLife( siHealAmount );

						// ������� ���, Ŭ���̾�Ʈ�� �����ش�. 
						if(IsPC(GetCharUnique()))
						{
							cltGameMsgResponse_IncLife clInfo(GetCharUnique(), pclCI->clIP.GetLife(),  siHealAmount, clPB.siReservedLife, 0, INCMANA_REASON_HEAL);
							cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
							SendNetMsg((sPacketHeader*)&clMsg);
						}

						siHealAmount = rand() % 451 + 50;	// ������ 50~500 ����
						IncreaseMana( siHealAmount );

						// ������� ���, Ŭ���̾�Ʈ�� �����ش�. 
						if(IsPC(GetCharUnique()))
						{
							cltGameMsgResponse_IncMana clInfo(GetCharUnique(), pclCI->clIP.GetMana(),  siHealAmount, INCMANA_REASON_HEAL);
							cltMsg clMsg(GAMEMSG_RESPONSE_INCMANA, sizeof(clInfo), (BYTE*)&clInfo);
							SendNetMsg((sPacketHeader*)&clMsg);
						}
						//////////////////////////////////////////////////////////////////////////

						// '��'�� ���Դٰ� Ŭ�� ��Ŷ ���� ('��'�� ���� Ŭ������ ��ȭ���ڵ��� ó���� �� ��Ŷ ó���ο���)
						cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclCI->GetPersonID(), siFortuneQuality, siTextUnique, siBuffNameUnique, 0, 0, 0 );
						cltMsg clMsg( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
						SendNetMsg( (sPacketHeader*)&clMsg );

						return false;
					}
					else if ( 3 == siFortuneQuality )	// ���� ��� '��' �϶�
					{
						//////////////////////////////////////////////////////////////////////////

						// '��' ������ �̹� ������ �����ش�
						SI16 index = -1;
						index = pclCI->clBI.clBufInfo.FindBufGetTypeSlot( BUF_GET_TYPE_FORTUNECOOKIE );
						if ( -1 < index )
						{
							// ������ �ɷ��ִ� ������ �����Ѵ�.
							stBuf DelBuf( pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0 );
							sDBRequest_DeleteBuf clMsg( pclCI->GetPersonID(), index, &DelBuf );
							((cltServer*)pclClient)->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}

						//////////////////////////////////////////////////////////////////////////

						// '��' ������ �ش�.
						SI32 siUseTime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 21600 ;// 30���� �ش�.(�̺�Ʈ �Ⱓ���� ���� ����, �뷫30�Ϸ� ��)
						index			= pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_FORTUNE_BAD, false );

						stBuf addBuf( BUF_EVENT_FORTUNE_BAD, 0, siUseTime );
						AddBufThroughDB( index, &addBuf , false , itempos , &clitem );

						//'��' ������ ��ĥ�� �ִ� ����Ʈ�� ����
						if ( false == MakeQuest_RemoveUnLuckStatus() )
						{
							// �ϴ� ���� ������ ���� ��쿡 ���ؼ� �������� �ʴ´�.

							return false;
						}

						cltMissionQuestInfo* pQuestInfo = &pclCI->clQuestInfo.clMissionQuestInfo;

						// ��񿡼� ��Ű�� 1�� �ٿ��ְ�
						if ( clitem.siUnique != 0 )
						{
							sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem );
							pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
						}

						// '��' ������ �޾Ҵٰ� Ŭ���̾�Ʈ�� ��Ŷ ����
						cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclCI->GetPersonID(), siFortuneQuality, siTextUnique, 0, pQuestInfo->clQuestClearConditionInfo.siFlag, pQuestInfo->clQuestClearConditionInfo.siPara1, pQuestInfo->clQuestClearConditionInfo.siPara2 );
						cltMsg clMsg( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
						SendNetMsg( (sPacketHeader*)&clMsg );

						return false;
					}

					return false;
				}
				else	// �������ϰ�쿣 ������ ���� ó��
				{
					Count = (13062 == ItemUnique) ? (rand()%3+1) : 1 ; // ��Ű�����ϰ�쿣 1~3���� ���� ����

					if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
						return false;

					clOutPutItem.SetItemNum( Count );

					//------------------------------------------
					// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
					//------------------------------------------
					SI16 invpos;
					cltItem cltoitem;
					SI32 rtnvalue;
					if(CanAddInv(INVMODE_ALL, &clOutPutItem, &invpos, &cltoitem, &rtnvalue) == false)
					{
						((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
						return false;
					}

					if ( clitem.siUnique != 0 )
					{
						sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clOutPutItem, pclItemManager->CanPile(clOutPutItem.siUnique), clOutPutItem.IsCreateSID(pclItemManager), false );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}

					// Ŭ�� ��Ű���� �������� �̾Ҵٰ� ��Ŷ ���� (������ �����Ϳ� ���� Ŭ������ ��ȭ���ڵ��� ó���� �� ��Ŷ ó���ο���)

					// ��Ű�� 100���� ��� (�ǹ̴� ����)
					NTCHARString128 pUserName = GetName();
					cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclCI->GetPersonID(), 100, 0, 0, 0, 0, 0, pUserName );
					cltMsg clMsg( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
					pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );

					return false;
				}

				return false;
			}

			//----------------------------------------------------------------------------------
			// Ȳ�ݾ�
			else if(clitem.siUnique == ITEMUNIQUE(13005) )
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				// ���� ������ ���
				const SI32 siBoxItemList[]=
				{
					ITEMUNIQUE(5350),
						ITEMUNIQUE(5355),
						ITEMUNIQUE(5360),
						ITEMUNIQUE(5365),
						ITEMUNIQUE(5370),
						ITEMUNIQUE(2710),
						ITEMUNIQUE(24020),
						ITEMUNIQUE(2735),
						ITEMUNIQUE(2685),
						ITEMUNIQUE(2680)	
				};


				SI32 rndItemIndex = rand() % ( sizeof(siBoxItemList) / sizeof(SI32) );

				SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				SI32 Itemnum = 1;

				SI32 randItemnumVal = rand() % 100;

				// Ȯ���� ���� ���� ����
				if( randItemnumVal < 10 )			{		Itemnum = 1;		}
				else if( randItemnumVal < 24 )		{		Itemnum = 2;		}
				else if( randItemnumVal < 44 )		{		Itemnum = 3;		}
				else if( randItemnumVal < 58 )		{		Itemnum = 4;		}
				else if( randItemnumVal < 70 )		{		Itemnum = 5;		}
				else if( randItemnumVal < 80 )		{		Itemnum = 6;		}
				else if( randItemnumVal < 88 )		{		Itemnum = 7;		}
				else if( randItemnumVal < 94 )		{		Itemnum = 8;		}
				else if( randItemnumVal < 98 )		{		Itemnum = 9;		}
				else if( randItemnumVal < 100 )		{		Itemnum = 10;		}


				clDrawItem.SetItemNum( Itemnum );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}			
			//----------------------------------------------------------------------------------
			// Ȳ�ݶ����
			else if( clitem.siUnique == ITEMUNIQUE(13028) )	
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;
				SI32 usedate = 0;
				SI16 brareswitch = 0;
				//[����] �����̺�Ʈ ���� �̺�Ʈ�� ���� 2009-10
				if(pclClient->IsCountrySwitch(Switch_RaccoonEvent_Change_Goonzu))	// ���� �������� ���� �Ǹ� Ȳ�� ������� �Ʒ� ����Ʈ�� ���� 
				{
					SI32 rndVal = rand() % 1000;
					if( rndVal < 2 )				{		rndItemUnique = ITEMUNIQUE(5600);							}	// �����޴�					0.2%
					else if (rndVal < 4)			{		rndItemUnique = ITEMUNIQUE(5370);							}	// �ູ�� ��				0.2%
					else if (rndVal < 8)			{		rndItemUnique = ITEMUNIQUE(5365);							}	// ���� �Ӽ���				0.4%
					else if (rndVal < 12)			{		rndItemUnique = ITEMUNIQUE(5360);							}	// �ٶ��� �Ӽ���			0.4%
					else if (rndVal < 16)			{		rndItemUnique = ITEMUNIQUE(5350);							}	// ���� �Ӽ���				0.4%
					else if (rndVal < 20)			{		rndItemUnique = ITEMUNIQUE(5355);							}	// ���� �Ӽ���				0.4%
					else if (rndVal < 110)			{		rndItemUnique = ITEMUNIQUE(5380);							}	// ƼŸ�Ͽ�					9%
					else if (rndVal < 200)			{		rndItemUnique = ITEMUNIQUE(6140);							}	// ��ȣ����					9%
					else if (rndVal < 290)			{		rndItemUnique = ITEMUNIQUE(7175);							}	// �ƶ�̵�					9%
					else if (rndVal < 380)			{		rndItemUnique = ITEMUNIQUE(7185);							}	// ������ũ					9%
					else if (rndVal < 690)			{		rndItemUnique = ITEMUNIQUE(24075);							}	// �����̾� ���λ��� �̿�� 31%
					else if (rndVal < 1000)			{		rndItemUnique = ITEMUNIQUE(24047);							}	// �ڸ�����̿��			31%
				}
				else
				{
					SI32 rndVal = rand() % 100;
					//KHY - 1217 - Ȳ�� ����� ���� ����. - 
					if(pclClient->IsCountrySwitch(Switch_RaccoonGoldeggChange))
					{
						if( rndVal < 1 )		{		rndItemUnique = ITEMUNIQUE(5600);							}
						else if( rndVal < 2 )	{		rndItemUnique = ITEMUNIQUE(23090);		usedate = 7;		}
						else if( rndVal < 8 )	{		rndItemUnique = ITEMUNIQUE(2720);							}
						else if( rndVal < 15 )	{		rndItemUnique = ITEMUNIQUE(2715);							}
						else if( rndVal < 57 )	{		rndItemUnique = ITEMUNIQUE(24075);							}
						else if( rndVal < 100 )	{		rndItemUnique = ITEMUNIQUE(24047);							}
					}
					else
					{
						if( rndVal < 2 )		{		rndItemUnique = ITEMUNIQUE(5600);							}
						else if( rndVal < 3 )	{		rndItemUnique = ITEMUNIQUE(5370);							}
						else if( rndVal < 8 )	{		rndItemUnique = ITEMUNIQUE(5365);							}
						else if( rndVal < 12 )	{		rndItemUnique = ITEMUNIQUE(5360);							}
						else if( rndVal < 16 )	{		rndItemUnique = ITEMUNIQUE(5350);							}
						else if( rndVal < 20 )	{		rndItemUnique = ITEMUNIQUE(5355);							}
						else if( rndVal < 60 )	{		rndItemUnique = ITEMUNIQUE(24075);							}
						else if( rndVal < 100 )	{		rndItemUnique = ITEMUNIQUE(24047);							}
					}
				}
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
				{
					return false;
				}

				SI32 rndItemNum = 1; // 1 ����.

				clDrawItem.SetItemNum( rndItemNum );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			//----------------------------------------------------------------------------------
			// ��� ����
			else if( clitem.siUnique == ITEMUNIQUE(13021) )	
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;
				SI32 rndVal = rand() % 100;

				//KHY - 0218  - ȭ��Ʈ���� 
				if( rndVal < 5 )			{		rndItemUnique = ITEMUNIQUE(5600);		}
				else if( rndVal < 15 )		{		rndItemUnique = ITEMUNIQUE(3899); 		} //����� ĵ��
				else if( rndVal < 25 )		{		rndItemUnique = ITEMUNIQUE(3901);		} //������ ĵ��
				else if( rndVal < 30 )		{		rndItemUnique = ITEMUNIQUE(24094);		}
				else if( rndVal < 45 )		{		rndItemUnique = ITEMUNIQUE(2730);		}
				else if( rndVal < 60 )		{		rndItemUnique = ITEMUNIQUE(7860);		}
				else if( rndVal < 65 )		{		rndItemUnique = ITEMUNIQUE(24040);		}
				else if( rndVal < 70 )		{		rndItemUnique = ITEMUNIQUE(5400);		}
				else if( rndVal < 90 )		{		rndItemUnique = ITEMUNIQUE(24000);		}
				else if( rndVal < 100 )		{		rndItemUnique = ITEMUNIQUE(2705);		}

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				SI32 rndItemNum = 1;

				clDrawItem.SetItemNum( rndItemNum );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			//-----------------------------------------------------------------------------------------------
			// ��� ����
			else if( clitem.siUnique == ITEMUNIQUE(13015) )	
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;
				SI32 rndVal = rand() % 100;

				//KHY - 0115 �߷�Ÿ�ε��� �̺�Ʈ. - ������ ����, Ȯ�� ����.
				if( rndVal < 5 )			{			rndItemUnique = ITEMUNIQUE(5600);			}
				else if( rndVal < 15 )		{			rndItemUnique = ITEMUNIQUE(3890);			}
				else if( rndVal < 25 )		{			rndItemUnique = ITEMUNIQUE(3895);			}
				else if( rndVal < 30 )		{			rndItemUnique = ITEMUNIQUE(24094);			}
				else if( rndVal < 45 )		{			rndItemUnique = ITEMUNIQUE(2730);			}
				else if( rndVal < 60 )		{			rndItemUnique = ITEMUNIQUE(7860);			}
				else if( rndVal < 65 )		{			rndItemUnique = ITEMUNIQUE(24040);			}
				else if( rndVal < 70 )		{			rndItemUnique = ITEMUNIQUE(5400);			}
				else if( rndVal < 90 )		{			rndItemUnique = ITEMUNIQUE(24000);			}
				else if( rndVal < 100 )		{			rndItemUnique = ITEMUNIQUE(2705);			}

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				SI32 rndItemNum = 1;

				clDrawItem.SetItemNum( rndItemNum );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;

			}
			////-----------------------------------------------------------------------------------------------
			//// ����ã�� �̺�Ʈ ���� �蹶ġ.
			//else if( clitem.siUnique == ITEMUNIQUE(13347) )
			//{
			//	if( IsBlankInv(1,INVMODE_ALL) == false )
			//	{
			//		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
			//		return false;
			//	}

			//	SI32 rndItemUnique = 0;
			//	SI32 rndVal = rand() % 100;
			//	SI32 rndItemNum = 0;

			//	if( rndVal < 20 )			{			rndItemUnique = ITEMUNIQUE(5020);			rndItemNum = rand()%3+1 ;	}
			//	else if( rndVal < 40 )		{			rndItemUnique = ITEMUNIQUE(5010);			rndItemNum = rand()%3+1 ;	}
			//	else if( rndVal < 55 )		{			rndItemUnique = ITEMUNIQUE(5050);			rndItemNum = rand()%3+1 ;	}
			//	else if( rndVal < 70 )		{			rndItemUnique = ITEMUNIQUE(5040);			rndItemNum = rand()%3+1 ;	}

			//	else if( rndVal < 75 )		{			rndItemUnique = ITEMUNIQUE(13051);			rndItemNum = 1	; }
			//	else if( rndVal < 80 )		{			rndItemUnique = ITEMUNIQUE(13052);			rndItemNum = 1	;}
			//	else if( rndVal < 85 )		{			rndItemUnique = ITEMUNIQUE(13053);			rndItemNum = 1	;}
			//	else if( rndVal < 90 )		{			rndItemUnique = ITEMUNIQUE(13054);			rndItemNum = 1	;}
			//	else if( rndVal < 95 )		{			rndItemUnique = ITEMUNIQUE(13055);			rndItemNum = 1	;}
			//	else if( rndVal < 100 )		{			rndItemUnique = ITEMUNIQUE(13056);			rndItemNum = 1	;}

			//	SI16 brareswitch = 0;
			//	SI32 usedate = 0;
			//	cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
			//	clDrawItem.Init();

			//	if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
			//		return false;
			//	clDrawItem.SetItemNum( rndItemNum );
			//	//------------------------------------------
			//	// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
			//	//------------------------------------------
			//	SI16 invpos;
			//	cltItem cltoitem;
			//	SI32 rtnvalue;
			//	if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
			//	{
			//		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
			//		return false;
			//	}

			//	if ( clitem.siUnique != 0 )
			//	{
			//		sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager));
			//		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			//	}

			//	return false;

			//}
			////-------------------------------------------------------------------------------------------------------------
			// ����ã�� �̺�Ʈ.
			// ��� ��Ʈ
			// -60%Ȯ���� �Ϲ� ����-
			// -35%Ȯ���� ���ӳ� ���� NPC-
			// -5%Ȯ���� ���� ���� NPC-
			// ������ ��� �ӽ� 
			else if(clitem.siUnique == ITEMUNIQUE(13057))
			{
				if ( pclClient->IsCountrySwitch(Switch_TreasureEvent)  )
				{
					if( pclClient->pclEventTimeManager->InEventTime("TreasureEvent", &pclserver->sTime) == true )
					{
						cltServer *pclserver = (cltServer*)pclClient;

						if (pclserver->pclCM->pclIDManager->GetNPCCharNumber() > MAX_NPC_NUMBER - 1000)
						{
							return false;
						}
						if (GetMapIndex() == MAPINDEX_BEGINNER1 || GetMapIndex() == MAPINDEX_PALACE || GetMapIndex() == MAPINDEX_MOFUMOFULAND)
						{
							return false;
						}
						SI32 pos = 0 ;
						SI32 x, y;
						SI32 tempx, tempy, level;
						SI32 mapindex = 0;

						bool bSelectKind = false;

						SI32 siMonsterKind	=	0	;
						SI32 TempKind	=	0	;
						// �ϴ� ���� ���͸� ��ȯ���� ���� �ؾ� ����
						// -60%Ȯ���� �Ϲ� ����-
						// -35%Ȯ���� ���ӳ� ���� NPC-
						// -5%Ȯ���� ���� ���� NPC-
						// �Ϲ� �������� Ȥ ���ɵ����� ���� �Ѵ�.
						//SI32 TempKind = GetUniqueWithRange( ItemUnique_13057_Treasure, sizeof(ItemUnique_13057_Treasure) / sizeof(cltUniqueRange), 1000);

						SI32 siSelectMonClass = rand() % 100 ;
						if ( siSelectMonClass <60 )	// �Ϲ� ���� 
						{
							TempKind	=	3	;
						}
						else if (siSelectMonClass < 95 )	//	�Ϲ�����
						{
							TempKind	=	1	;
						}
						else if (siSelectMonClass <100 )	// ����
						{
							TempKind	=	2	;
						}

						if ( TempKind == 1  )	// �Ϲ� ������ ���� ��Ų��
						{
							SI32 rndVal = rand() % 100;
							if( rndVal < 17 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_DAEGUM1");		}	//17
							else if( rndVal < 34 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_CATAR1");		}	//17
							else if( rndVal < 51 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_RIFLE1");		}	//17
							else if( rndVal < 66 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_DAEGUM2");		}	//15
							else if( rndVal < 81 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_CATAR2");		}	//15
							else if( rndVal < 96 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_RIFLE2");		}	//15
							else if( rndVal < 98 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_REDSHABEL");		}	//2
							else if( rndVal < 100 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_TREASURE_BLUESHABEL");		}	//2
						}
						else if ( TempKind == 2  )	// ���� ������ ���� ��Ų��.
						{
							siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_CURSEHIRO");
						}
						else	// �Ϲ� ���͵��� ���� �ϰ� ���� ��Ų��.
						{
							SI32 rndVal = rand() % 100;
							if( rndVal < 18 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_RACCOON");		}	//18
							else if( rndVal < 33 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_VINE");		}	//15
							else if( rndVal < 46 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_GOTPA");		}	//13
							else if( rndVal < 59 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_MARIONETTE");		}	//13
							else if( rndVal < 71 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_SHARK");		}	//12
							else if( rndVal < 81 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_CANNONMOL");		}	//10
							else if( rndVal < 89 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_DEACON");		}	//8
							else if( rndVal < 96 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_REDBAT");		}	//7
							else if( rndVal < 99 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_BROWNWOLF");		}	//3
							else if( rndVal < 100 )			{			siMonsterKind	=	pclClient->GetUniqueFromHash("KIND_GREATWALLSLIME");		}	//1
						}

						if(siMonsterKind > 0 )
						{
							mapindex = GetMapIndex();

							tempx = GetX();
							tempy = GetY();

							// ���͸� ��ġ�� ������ ���� ã�´�. 
							if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(	siMonsterKind , tempx, tempy, 10, &x, &y, true) == false)
							{
								break;
							}

							level = rand() % 50 + 1;

							cltInnerStatusInfo clinnerstatus;
							clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

							cltIdentity clIdentity;
							clIdentity.MakeTreasureEvent(IDENTITY_TREASURE_EVENT);

							SI32 id = pclserver->SetNPCChar( siMonsterKind , VILLAGE_NONE, &clIdentity, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
							cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

							pclchar->dwTimerClock = pclserver->CurrentClock;
							pclchar->siCharMode = CHARMODE_TREASUREEVENT;

						}
						else
						{
							return false;
						}
					}

				}
			}
			//[����] ���� �̺�Ʈ. NDE ���� �Ҹ�. => 2008-6-18
			else if( clitem.siUnique == ITEMUNIQUE(13043) )	
			{
				/*if ( itempos <= 0 || itempos >= MAX_ITEM_PER_PERSON ) 
				return false;*/

					// DB�� ������ ����� �ϴ� ���̱� ������ �ƹ�ó���� �����ʴ´�.
					if(IsNowAddBufThroughDB())		return false;

				const SI32 BuffKindNum = 6;													// ������ �Ҹ� �� ���� �� �ִ� ���� ����.
				cltUniqueRange SetBuffKind[BuffKindNum];									// ������ ������ ������ Ȯ��.
				ZeroMemory(SetBuffKind, sizeof(SetBuffKind));
				for(SI32 Count = 0; Count < BuffKindNum - 1; ++Count)	
				{
					if(Count >= BuffKindNum)
						break;

					SetBuffKind[Count].siUnique  = BUF_STATUE_UP_STR + Count;
					SetBuffKind[Count].siPercent = 19;
				}
				SetBuffKind[BuffKindNum-1].siUnique  = BUF_EXP_UP;
				SetBuffKind[BuffKindNum-1].siPercent = 5;

				SI32 CompleteBuffKind = GetUniqueWithRange(SetBuffKind, BuffKindNum, 100);
				if(0 < CompleteBuffKind)
				{
					SI16 siPercent = 30; 
					if(BUF_EXP_UP == CompleteBuffKind)
					{
						siPercent = 100;
					}

					SI16 siIndex = pclCI->clBI.clBufInfo.FindBufSlot(CompleteBuffKind);
					if(0 > siIndex)
						siIndex = pclCI->clBI.clBufInfo.FindEmptySlot(CompleteBuffKind, false);	

					//������ 48��.
					SI32 siUsetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;

					// ������ ������ �־����� �ش���� �ð� ����.
					if(true == pclCI->clBI.clBufInfo.IsHaveBuf(CompleteBuffKind)) 
					{
						SI32 siOverTime = pclCI->clBI.clBufInfo.GetBuf(CompleteBuffKind)->siOverTime;
						SI32 siCurTime  = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary();

						// ���� ������� ������ �����ð��� ���.
						SI32 RemainTime = siOverTime - siCurTime;

						// ���� ������ �����ϰ� 
						stBuf DelBuf(CompleteBuffKind, 0, 0);
						sDBRequest_DeleteBuf clMsg(pclCI->GetPersonID(), siIndex, &DelBuf);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

						// ���� �����ε� �ð��� �����ؼ� �ٽ� ����.
						stBuf addBuf(CompleteBuffKind, siPercent, RemainTime + siUsetime);
						AddBufThroughDB(siIndex, &addBuf , false, itempos, &clitem, 0);
					}
					// ������ ������ �������� ���� ���� ����.
					else
					{
						stBuf addBuf(CompleteBuffKind, siPercent, siUsetime);
						AddBufThroughDB(siIndex, &addBuf , false, itempos, &clitem, 0);
					}
				}
				return false;
			}
			//-----------------------------------------------------------------------------------------------
			else if(
				clitem.siUnique == ITEMUNIQUE(13044) ||		// �ݸ޴�	(�ӽ� ����ũ)
				clitem.siUnique == ITEMUNIQUE(13045) ||		// ���޴�	(�ӽ� ����ũ)
				clitem.siUnique == ITEMUNIQUE(13046)		// ���޴�	(�ӽ� ����ũ)
				)	
			{
				if (pclCI->clBI.clBufInfo.IsHaveBuf( BUF_OLYMPICMEDAL ))	return false;
				cltUniqueRange SetBuffKind;
				SetBuffKind.Init();
				switch( clitem.siUnique ) {
	case ITEMUNIQUE(13044) :{	// �ݸ޴�
		SetBuffKind.siUnique	=	BUF_OLYMPICMEDAL	;
		SetBuffKind.siPercent	=	20	;
							}
							break;
	case ITEMUNIQUE(13045) :{// ���޴�
		SetBuffKind.siUnique	=	BUF_OLYMPICMEDAL	;
		SetBuffKind.siPercent	=	10	;
							}
							break;
	case ITEMUNIQUE(13046) :{// ���޴�
		SetBuffKind.siUnique	=	BUF_OLYMPICMEDAL	;
		SetBuffKind.siPercent	=	5	;
							}
							break;
				}
				if( 0 < SetBuffKind.siUnique && 
					0 < SetBuffKind.siPercent &&
					false == pclCI->clBI.clBufInfo.IsHaveBuf( BUF_OLYMPICMEDAL ))
				{
					SI16 siIndex = pclCI->clBI.clBufInfo.FindEmptySlot(SetBuffKind.siUnique, false);
					//������ 48��.
					SI32 siUsetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ;
					stBuf addBuf(SetBuffKind.siUnique, SetBuffKind.siPercent, siUsetime);
					AddBufThroughDB(siIndex, &addBuf , false, itempos, &clitem, 0);
				}
				return false;
			}
			//----------------------------------------------------------------------------------
			// Trick or Treat ����
			else if( clitem.siUnique == ITEMUNIQUE(13050) )	
			{
				if (pclClient->IsCountrySwitch(Switch_HalloweenEvent) == false) 			return false;

				if( pclClient->pclEventTimeManager->InEventTime("HalloweenEvent", &pclserver->sTime) == true )
				{
					SI32	siType = rand() % 2;
					SI32	siSkillUnique = 0;

					if( siType == 0 )
					{
						SI32	siAddExp = (rand() % 40001) + 10000;		// 10,000 ~ 50,000
						IncreaseExp( (SI64)siAddExp, GETEXP_REASON_EVENT );
					}
					else
					{
						SI32	siAddExp = (rand() % 4001) + 1000;		// 1,000 ~ 5,000
						SI16 siSkillCount = 0;
						SI16 siSkills[MAX_SKILL_NUMBER] = { 0, };

						for(SI32 i=0; i<MAX_SKILL_NUMBER; i++)
						{
							cltSkillInfo* pclSkillInfo = pclClient->pclSkillManager->pclSkillInfo[i];
							if(pclSkillInfo)
							{
								switch(pclSkillInfo->siSkillType)
								{
								case SKILLTYPE_R_USEWEAPON:
								case SKILLTYPE_R_MAKEWEAPON:
								case SKILLTYPE_R_ARMOR:
								case SKILLTYPE_R_MAKEHARVEST:
								case SKILLTYPE_R_HARVEST:
								case SKILLTYPE_R_MAKECLOTH:
								case SKILLTYPE_R_MAKEACCESSARY:
								case SKILLTYPE_R_ETC:
									// ������ ������ ����.	
									//case SKILLTYPE_FIGHT:
									{
										siSkills[siSkillCount++] = pclSkillInfo->siUnique;
									}
									break;
								}
							}
						}

						if(siSkillCount > 0)		siSkillUnique = siSkills[rand() %siSkillCount];
						if(siSkillUnique > 0)		SetSkillUpdate( siSkillUnique, siAddExp );
					}
				}
				else
					return false;
			}
			//-----------------------------------------------------------------------------------------------

			// [���] - �� ���� ���� (48�а� ���� ��ɽ� ���� Ȯ���� ȣ�����ó��� ���� ȹ�� ����)
			else if(clitem.siUnique == ITEMUNIQUE(13059))
			{
				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.

				SI16 index	= pclCI->clBI.clBufInfo.FindEmptySlot( BUF_CHRISTMASEVENT_SNOWBLESS, false );

				if ( index > -1 )
				{
					stBuf addBuf( BUF_CHRISTMASEVENT_SNOWBLESS, 0, usetime );
					AddBufThroughDB( index, &addBuf , false , itempos , &clitem );
				}

				return false ;
			}
			// [���] - ũ�������� ��� ���� ( 48�а� Ż���� ���ɷ�ġ�� +5 �÷��ִ� ����)
			else if(clitem.siUnique == ITEMUNIQUE(13061))
			{
				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.

				SI16 index	= pclCI->clBI.clBufInfo.FindEmptySlot( BUF_CHRISTMASEVENT_DECORATION, false );

				if ( index > -1 )
				{
					stBuf addBuf( BUF_CHRISTMASEVENT_DECORATION, 0, usetime );
					AddBufThroughDB( index, &addBuf , false , itempos , &clitem );
				}

				return false ;
			}
			else if( ITEMUNIQUE(13064) == clitem.siUnique )	// [����] ���̾�Ʈ ���� ��Ȱ��.
			{
				if( IsBlankInv(1, INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI16	brareswitch		= 0;
				SI32	usedate			= 0;			// ���Ⱓ.
				SI32	siItemUnique	= 0;
				cltItem clInputItem;					// ��÷�ؼ� ���� ���������
				clInputItem.Init();
				
				switch( rand()%4 )
				{
					case 0:	siItemUnique = ITEMUNIQUE(13065); break;
					case 1:	siItemUnique = ITEMUNIQUE(13066); break;
					case 2:	siItemUnique = ITEMUNIQUE(13067); break;
					case 3:	siItemUnique = ITEMUNIQUE(13068); break;
				}

				if( pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clInputItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				clInputItem.SetItemNum( 1 );

				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16	invpos;
				cltItem cltoitem;
				SI32	rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clInputItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clInputItem, pclItemManager->CanPile(clInputItem.siUnique), clInputItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					pclClient->pclLog->FilePrint( "config\\GiantRaccoonResurrectEvent.log" , "[OpenItem] %s : ", pclItemManager->GetName( clInputItem.siUnique ) );
				}
			}
		}
		break;
	case ITEMTYPE_BOX://�ڽ������� - �ڽ��� ���� �ٸ� �������� �����ȴ�.
		{
			cltItem		clOutPutItem[MAX_BOX_OUTPUT];		// �ִ� 2������ �ѹ��� ������ �����ϴ�.
			SI16		brareswitch = 0;
			bool		bCanNotice[MAX_BOX_OUTPUT]	= {0,};	// ��� �˸�����

			//====================================================================
			// �����ϰ� ���� �������� �����Ѵ�.
			//====================================================================

			//------------------------------------------------------------------------------------------------------
			if ( (pclClient->m_pclBoxItemMgr) && (TRUE == pclClient->m_pclBoxItemMgr->IsNormalBoxItem(clitem.siUnique)) )
			{
				if ( false == IsBlankInv(1, INVMODE_ALL) )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				CBoxItemUnit* pclGetBoxItemUnit = pclClient->m_pclBoxItemMgr->GetRandItemFromUnique( clitem.siUnique );
				if ( NULL == pclGetBoxItemUnit )
				{
					return FALSE;
				}

				SI16 siGetRareSwitch	= 0;
				SI32 siGetItemUnique	= pclGetBoxItemUnit->GetItemUnique();
				SI32 siGetItemNum		= pclGetBoxItemUnit->GetItemNum();

				SI32 siReference		= pclItemManager->FindItemRefFromUnique( siGetItemUnique );
				if ( 0 >= siReference )
				{
					return false;
				}

				SI32 siGetUseDate		= pclItemManager->pclItemInfo[siReference]->clItem.uiDateUseDay;

				// ���޽� ��¥�� ������ �ִٸ� ������ ��¥�� ����
				if ( 0 < pclGetBoxItemUnit->GetItemUseDate() )
				{
					siGetUseDate = pclGetBoxItemUnit->GetItemUseDate();
				}

				if ( false == pclClient->pclItemManager->MakeRandItemUnique(siGetItemUnique, &clOutPutItem[0], 0, 0, &siGetRareSwitch, 0, 0, 0, 0, 0, siGetUseDate) )
				{
					return false;
				}

				clOutPutItem[0].SetItemNum( siGetItemNum );
				// ��ھ˸� ����
				bCanNotice[0]	= DATA_TO_BOOL( pclGetBoxItemUnit->GetCanNotice() );

			}
			// ȣ�ڻ��ڷ� ó��
			else if ( (pclClient->m_pclBoxItemMgr) && (TRUE == pclClient->m_pclBoxItemMgr->IsAmberBoxItem(clitem.siUnique)) )
			{
				if ( false == IsBlankInv(1, INVMODE_ALL) )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 siInBoxItemList[AMBER_BOX_LIST_NUM] = { 0, };

				SI32 siListCount = pclClient->m_pclBoxItemMgr->GetInBoxItemList( clitem.siUnique, siInBoxItemList, AMBER_BOX_LIST_NUM );
				if ( 0 >= siListCount )
				{
					return false;
				}

				// ������ �ڽ� ����Ʈ
				cltGameMsgResponse_Amber_Box_List clinfo( siInBoxItemList, siListCount, clitem.siUnique );
				cltMsg clMsg(GAMEMSG_RESPONSE_AMBER_BOX_LIST, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				// Ŭ���Ͽ� �����ϰ� ���õ� ������ ���� ��û.		
				sDBRequest_Amber_Box_Select_Item_List clMsg2( GetID(), pclCI->GetPersonID(), clitem.siUnique );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);

			}
			else if(clitem.siUnique == ITEMUNIQUE(13300))	// �������� �ʻ���
			{
				if(pclClient->pclItemManager->MakeRandItemUnique( ITEMUNIQUE(23695), &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( ITEMUNIQUE(23395), &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;
			}
			//-----------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13322) ) // ������ ����   Cushion Box
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;

				switch(GetKind())
				{
				case KIND_HERO3 :
					rndItemUnique = ITEMUNIQUE(13617); //�ڽ���Ʈ
					break;
				case KIND_HEROINE3 :
					rndItemUnique = ITEMUNIQUE(13619); //����
					break;
				case KIND_HERO4 :
					rndItemUnique = ITEMUNIQUE(13618); //����Ǫ��
					break;
				case KIND_HEROINE4 :
					rndItemUnique = ITEMUNIQUE(13620); //�ú����� �㽺Ű
					break;
				}

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;
				clDrawItem.SetItemNum( 1 );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			//-----------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13336) ) // �̺� ����.
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;

				switch(GetKind())
				{
				case KIND_HERO3 :
					rndItemUnique = ITEMUNIQUE(13629);
					break;
				case KIND_HEROINE3 :
					rndItemUnique = ITEMUNIQUE(13628);
					break;
				case KIND_HERO4 :
					rndItemUnique = ITEMUNIQUE(13629); 
					break;
				case KIND_HEROINE4 :
					rndItemUnique = ITEMUNIQUE(13628); 
					break;
				}

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;
				clDrawItem.SetItemNum( 1 );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			else if( clitem.siUnique == ITEMUNIQUE(13350) ) // PCK :  ���ڴ� �Ŀ��� ���� (09.06.12)
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = 0;

				switch(GetKind())
				{
				case KIND_HERO3 :
					rndItemUnique = ITEMUNIQUE(13649);
					break;
				case KIND_HEROINE3 :
					rndItemUnique = ITEMUNIQUE(13650);
					break;
				case KIND_HERO4 :
					rndItemUnique = ITEMUNIQUE(13647);
					break;
				case KIND_HEROINE4 :
					rndItemUnique = ITEMUNIQUE(13648);
					break;
				}

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;
				clDrawItem.SetItemNum( 1 );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			// �� �ָӴ� - by LEEKH 2007.12.26
			else if( clitem.siUnique == ITEMUNIQUE(13329) )	
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				SI32 rndItemUnique = GetUniqueWithRandom(siItemUnique_8115_ItemUnique, sizeof(siItemUnique_8115_ItemUnique) / sizeof(SI32) );
				if(rndItemUnique <= 0)
					return false;

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				clDrawItem.SetItemNum( 1 );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				return false;
			}
			//------------------------------------------------------------------------------------------------------
			//KHY - 1104 -  ����2 -���� ���� ����.  - ���� ���ָӴ�
			else if( clitem.siUnique == ITEMUNIQUE(13337) )	
			{
				if( IsBlankInv(1,INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}
				// ���� ���� ������.
				SI32 rndItemUnique = 0;

				// ���ʽ� �������� ���⼭ �����Ѵ�.
				SI32 bonusItemUnique = ITEMUNIQUE(12506); // ���.
				SI32 bonusItemRate = 5; // ���ʽ� �������� ���� Ȯ��.

				SI32 randBonus = rand()%1000;

				if(randBonus < bonusItemRate)
				{
					rndItemUnique = bonusItemUnique;
				}
				else
				{
					rndItemUnique = GetUniqueWithRandom(siItemUnique_13337_ItemUnique, sizeof(siItemUnique_13337_ItemUnique) / sizeof(SI32) );				
				}

				if(rndItemUnique <= 0)
					return false;

				SI16 brareswitch = 0;
				SI32 usedate = 0;
				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clDrawItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
					return false;

				clDrawItem.SetItemNum( 1 );
				//------------------------------------------
				// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
				//------------------------------------------
				SI16 invpos;
				cltItem cltoitem;
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clDrawItem, &invpos, &cltoitem, &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				if ( clitem.siUnique != 0 )
				{
					sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos, &clDrawItem, pclItemManager->CanPile(clDrawItem.siUnique), clDrawItem.IsCreateSID(pclItemManager), false);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}

				// ���ʽ� �������� ���Դٸ�.
				if(rndItemUnique == bonusItemUnique)
					((cltServer*)(pclClient))->SendRareItemMade(GetCharID(), &clDrawItem, RAREITEM_NOTICE_SWITCH_GACHA );

				return false;
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13301))	// ƾƾ����
			{
#ifdef _CHINA
				const SI32 siTreasureBoxItemList[]=
				{
					ITEMUNIQUE(24000),
						ITEMUNIQUE(24020),
						ITEMUNIQUE(5350),
						ITEMUNIQUE(5355),
						ITEMUNIQUE(5360),
						ITEMUNIQUE(5365),
						ITEMUNIQUE(24045),
				};
#else
				const SI32 siTreasureBoxItemList[]=
				{
					ITEMUNIQUE(24000),
						ITEMUNIQUE(7860),
						ITEMUNIQUE(24020),
						ITEMUNIQUE(2710),
						ITEMUNIQUE(2700),
						ITEMUNIQUE(5350),
						ITEMUNIQUE(5355),
						ITEMUNIQUE(5360),
						ITEMUNIQUE(5365),
						ITEMUNIQUE(24045),
						ITEMUNIQUE(3865),
				};
#endif
				const SI32 siTinTinUnique			= ITEMUNIQUE(18510);	// ��ȣ�� ���� ����ũ
				const SI32 siArchdevilMakeUnique	= ITEMUNIQUE(13027);	// ��Ǹ� ���� ����ũ

				SI32 siRand = rand() % 100 + 1;

				//KHY - 0829 - ��õ�� ��Ǹ�. ����߰�.
				if(pclClient->IsCountrySwitch(Switch_ArchangelArchdevil))
				{
					if ( siRand <= 5 ) 
					{
						SI16 brareswitch = 0;
						SI32 usedate = 30;

						if(pclClient->pclItemManager->MakeRandItemUnique( siTinTinUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
							return false;

						clOutPutItem[0].SetItemNum( 1 );
					}
					else if ( (siRand > 5) &&(siRand <= 10)) // ���мȿ��� 5%�� �����Ǿ� ��ġ ����. 20->10
					{
						SI16 brareswitch = 0;
						SI32 usedate = 7;

						if(pclClient->pclItemManager->MakeRandItemUnique( siArchdevilMakeUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
							return false;

						clOutPutItem[0].SetItemNum( 1 );
					}
					else
					{
						SI32 siRand2 = rand() % ( sizeof(siTreasureBoxItemList) / sizeof(SI32) );


						SI16 brareswitch = 0;
						if(pclClient->pclItemManager->MakeRandItemUnique( siTreasureBoxItemList[siRand2], &clOutPutItem[0], 0, 0, &brareswitch) == false)
							return false;

						SI32 siRand3 = rand() % 100 + 1;

						if ( siRand3 <= 30 )		{		clOutPutItem[0].SetItemNum(1);		}
						else if ( siRand3 <= 65 )	{		clOutPutItem[0].SetItemNum(2);		}
						else if ( siRand3 <= 90 )	{		clOutPutItem[0].SetItemNum(3);		}
						else if ( siRand3 <= 95 )	{		clOutPutItem[0].SetItemNum(4);		}
						else						{		clOutPutItem[0].SetItemNum(5);		}
					}
				}
				else
				{
					if ( siRand <= 5 ) 
					{
						SI16 brareswitch = 0;
						SI32 usedate = 30;

						if(pclClient->pclItemManager->MakeRandItemUnique( siTinTinUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)
							return false;

						clOutPutItem[0].SetItemNum( 1 );
					}
					else
					{
						SI32 siRand2 = rand() % ( sizeof(siTreasureBoxItemList) / sizeof(SI32) );


						SI16 brareswitch = 0;
						if(pclClient->pclItemManager->MakeRandItemUnique( siTreasureBoxItemList[siRand2], &clOutPutItem[0], 0, 0, &brareswitch) == false)
							return false;

						SI32 siRand3 = rand() % 100 + 1;

						if ( siRand3 <= 30 )			{		clOutPutItem[0].SetItemNum(1);			}
						else if ( siRand3 <= 65 )		{		clOutPutItem[0].SetItemNum(2);			}
						else if ( siRand3 <= 90 )		{		clOutPutItem[0].SetItemNum(3);			}
						else if ( siRand3 <= 95 )		{		clOutPutItem[0].SetItemNum(4);			}
						else							{		clOutPutItem[0].SetItemNum(5);			}
					}
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13302))	// Ű�޶� ����
			{
				SI32 siItemUnique = 0;

				if		(pclClient->IsWhereServiceArea(ConstServiceArea_China))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_China, sizeof(siItemUnique_13302_ItemUnique_China) / sizeof(SI32));
				}
				else if (pclClient->IsWhereServiceArea(ConstServiceArea_English))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_English, sizeof(siItemUnique_13302_ItemUnique_English) / sizeof(SI32));
				}
				else if (pclClient->IsWhereServiceArea(ConstServiceArea_Japan))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_Japan, sizeof(siItemUnique_13302_ItemUnique_Japan) / sizeof(SI32));
				}
				else if (pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_Korea, sizeof(siItemUnique_13302_ItemUnique_Korea) / sizeof(SI32));
				}
				else if (pclClient->IsWhereServiceArea(ConstServiceArea_NHNChina))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_NHNChina, sizeof(siItemUnique_13302_ItemUnique_NHNChina) / sizeof(SI32));
				}
				else if (pclClient->IsWhereServiceArea(ConstServiceArea_EUROPE))
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_Europe, sizeof(siItemUnique_13302_ItemUnique_Europe) / sizeof(SI32));
				}
				else
				{
					siItemUnique = GetUniqueWithRandom(siItemUnique_13302_ItemUnique_Etc, sizeof(siItemUnique_13302_ItemUnique_Etc) / sizeof(SI32));
				}

				if(siItemUnique <= 0)			return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13303))	// ����ǻ���
			{
				SI32 ItemUnique = GetUniqueWithRange( ItemUnique_13303_ItemNum, sizeof(ItemUnique_13303_ItemNum) / sizeof(cltUniqueRange), 100);

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, 0) == false)
					return false;

				clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13304))	// å ����
			{
				siRealItemCount = MakeRealItemUnqiues(	ItemUnique_13304_ItemUnique, sizeof(ItemUnique_13304_ItemUnique) / sizeof(SI32), 
					siRealItemUniques, MAX_ITEM_UNIQUE);

				SI32 siItemUnique = GetUniqueWithRandom( siRealItemUniques, siRealItemCount );
				if ( siItemUnique <= 0 )		return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}	

			else if(clitem.siUnique == ITEMUNIQUE(13344))	// �ƹ�Ÿ å����
			{
				siRealItemCount = MakeRealItemUnqiues(	ItemUnique_13344_ItemUnique, sizeof(ItemUnique_13344_ItemUnique) / sizeof(SI32), 
					siRealItemUniques, MAX_ITEM_UNIQUE);

				SI32 siItemUnique = GetUniqueWithRandom( siRealItemUniques, siRealItemCount );
				if ( siItemUnique <= 0 )		return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}
			else if(clitem.siUnique == ITEMUNIQUE(13361))	// ���� å����
			{
				siRealItemCount = MakeRealItemUnqiues(	ItemUnique_13361_ItemUnique, sizeof(ItemUnique_13361_ItemUnique) / sizeof(SI32), 
					siRealItemUniques, MAX_ITEM_UNIQUE);

				SI32 siItemUnique = GetUniqueWithRandom( siRealItemUniques, siRealItemCount );
				if ( siItemUnique <= 0 )		return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}
			else if(clitem.siUnique == ITEMUNIQUE(13362))	// ��� å����
			{
				siRealItemCount = MakeRealItemUnqiues(	ItemUnique_13362_ItemUnique, sizeof(ItemUnique_13362_ItemUnique) / sizeof(SI32), 
					siRealItemUniques, MAX_ITEM_UNIQUE);

				SI32 siItemUnique = GetUniqueWithRandom( siRealItemUniques, siRealItemCount );
				if ( siItemUnique <= 0 )		return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}
			else if(clitem.siUnique == ITEMUNIQUE(13363))	// ���� å����
			{
				siRealItemCount = MakeRealItemUnqiues(	ItemUnique_13363_ItemUnique, sizeof(ItemUnique_13363_ItemUnique) / sizeof(SI32), 
					siRealItemUniques, MAX_ITEM_UNIQUE);

				SI32 siItemUnique = GetUniqueWithRandom( siRealItemUniques, siRealItemCount );
				if ( siItemUnique <= 0 )		return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( siItemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
			}

			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13305))	// �Ŀ��� �漮
			{
				/*
				// ���� ������ ���
				const SI32 siBoxItemList[]=
				{
					ITEMUNIQUE(13608),
						ITEMUNIQUE(13609),
						ITEMUNIQUE(13610),
						ITEMUNIQUE(13611)						
				};

				SI32 rndItemIndex = rand() % ( sizeof(siBoxItemList) / sizeof(SI32) );
				SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				// �Ϻ��� ������ ��� ������ �ڽ��� ĳ���Ϳ� �´� ����̰� ���´�.
				// by LEEKH 2008.01.04 - ������
				if( pclClient->IsWhereServiceArea(ConstServiceArea_Japan) == false )
				{
					switch(GetKind())
					{
					case KIND_HERO3 :
						rndItemUnique = ITEMUNIQUE(13610);
						break;
					case KIND_HEROINE3 :
						rndItemUnique = ITEMUNIQUE(13611);
						break;
					case KIND_HERO4 :
						rndItemUnique = ITEMUNIQUE(13608);
						break;
					case KIND_HEROINE4 :
						rndItemUnique = ITEMUNIQUE(13609);
						break;
					}
				}
				*/
					SI32 rndItemUnique = 0;

				switch(GetKind())
				{
				case KIND_HERO3 :
					rndItemUnique = ITEMUNIQUE(13610);
					break;
				case KIND_HEROINE3 :
					rndItemUnique = ITEMUNIQUE(13611);
					break;
				case KIND_HERO4 :
					rndItemUnique = ITEMUNIQUE(13608);
					break;
				case KIND_HEROINE4 :
					rndItemUnique = ITEMUNIQUE(13609);
					break;
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13306))	// ���̵庹 ����
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23392);	// �۫﫤�ȫ֫�ࣨ�����ģ�- HAT
						rndItemUnique2 = ITEMUNIQUE(23692);	// ���׫��ɫ쫹�������ģ�- DRESS
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23390);	// �۫﫤�ȫ֫�ࣨҳ���ģ�- HAT
						rndItemUnique2 = ITEMUNIQUE(23690);	// ���׫��ɫ쫹��ҳ���ģ�- DRESS
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23690),
							ITEMUNIQUE(23390),
							ITEMUNIQUE(23692),
							ITEMUNIQUE(23392),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13307) ||		// ��ȭ�� �ٷ¹������� 
				clitem.siUnique == ITEMUNIQUE(13308) ||		// ��ȭ�� ���߷¹�������
				clitem.siUnique == ITEMUNIQUE(13309) || 	// ��ȭ�� ����¹�������
				clitem.siUnique == ITEMUNIQUE(13310) || 	// ��ȭ�� ���¹�������
				clitem.siUnique == ITEMUNIQUE(13311) || 	// ��ȭ�� �����ֹ�������
				clitem.siUnique == ITEMUNIQUE(13312) )		// ��ȭ�� ����������
			{

				SI32 itemUnique = 0;

				switch( clitem.siUnique )
				{
				case ITEMUNIQUE(13307): itemunique = ITEMUNIQUE(7530);		break;
				case ITEMUNIQUE(13308): itemunique = ITEMUNIQUE(7535);		break;
				case ITEMUNIQUE(13309): itemunique = ITEMUNIQUE(7540);		break;
				case ITEMUNIQUE(13310): itemunique = ITEMUNIQUE(7545);		break;
				case ITEMUNIQUE(13311): itemunique = ITEMUNIQUE(7550);		break;
				case ITEMUNIQUE(13312): itemunique = ITEMUNIQUE(7555);		break;
				}

				// 30��¥�� ������ �����Ѵ�.
				if(pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,30) == false)
					return false;

				clOutPutItem[0].SetItemNum( 1 );
				SI32 rndVal = rand() % 10 + 6;

				//KHY - 0820 - ���� �ɷ�ġ ���� ����.
				switch( clitem.siUnique )
				{
				case ITEMUNIQUE(13307): clOutPutItem[0].clItemRing.uiStr = rndVal ;		break;
				case ITEMUNIQUE(13308): clOutPutItem[0].clItemRing.uiDex = rndVal ;		break;
				case ITEMUNIQUE(13309): clOutPutItem[0].clItemRing.uiVit = rndVal ;		break;
				case ITEMUNIQUE(13310): clOutPutItem[0].clItemRing.uiMag = rndVal ;		break;
				case ITEMUNIQUE(13311): clOutPutItem[0].clItemRing.uiHnd = rndVal ;		break;
				case ITEMUNIQUE(13312): clOutPutItem[0].clItemRing.uiLuk = rndVal ;		break;
				}
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13313))	// Greek Box
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23388);	// �۫﫤�ȫ֫�ࣨ�����ģ�- HAT
						rndItemUnique2 = ITEMUNIQUE(23688);	// ���׫��ɫ쫹�������ģ�- DRESS
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23386);	// �۫﫤�ȫ֫�ࣨҳ���ģ�- HAT
						rndItemUnique2 = ITEMUNIQUE(23686);	// ���׫��ɫ쫹��ҳ���ģ�- DRESS
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23388),
							ITEMUNIQUE(23688),
							ITEMUNIQUE(23386),
							ITEMUNIQUE(23686),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13314))
			{
				const SI32 siTreasureBoxItemNumList[20] =
				{
					10, 20,			// �ּ�, �ִ밪
						10, 20,
						10, 20,
						10, 20,
						1, 5,
						1, 5,
						1, 5,
						1, 5,
						1, 5,
						5, 10
				};

				SI32 itemUnique = GetUniqueWithRandom(siItemUnique_13314_ItemUnique, sizeof(siItemUnique_13314_ItemUnique) / sizeof(SI32));
				if(itemUnique <= 0)		return false;

				SI32 itemCount = max( 1, sizeof(siItemUnique_13314_ItemUnique) / sizeof(SI32) );
				SI32 selectedItem = rand() % itemCount;

				SI32 minNum = siTreasureBoxItemNumList[selectedItem*2];
				SI32 maxNum = siTreasureBoxItemNumList[selectedItem*2+1];
				SI32 itemNum = minNum + max(1, rand()%(maxNum-minNum+1) );

				if(pclClient->pclItemManager->MakeRandItemUnique( itemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				// �������� ����
				clOutPutItem[0].SetItemNum( itemNum );
			}

			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13360))	// ���� ����
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(siItemUnique_13360_ItemUnique, sizeof(siItemUnique_13360_ItemUnique) / sizeof(cltValuesRange), 1000);

				if ( pItemValue == NULL )		return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13315))	// ��� ����
			{
				const SI32 siTreasureBoxItemNumList[20] =
				{
					10, 20,			// �ּ�, �ִ밪
						10, 20,
						10, 20,
						10, 20,
						10, 20,
						10, 20,
						10, 20,
						10, 20,
						10, 20,
						10, 20
				};

				SI32 itemUnique = GetUniqueWithRandom(siItemUnique_13315_ItemUnique, sizeof(siItemUnique_13315_ItemUnique) / sizeof(SI32));;
				if(itemUnique <= 0)				return false;

				SI32 itemCount = max( 1, sizeof(siItemUnique_13315_ItemUnique) / sizeof(SI32) );
				SI32 selectedItem = rand() % itemCount;

				SI32 minNum = siTreasureBoxItemNumList[selectedItem*2];
				SI32 maxNum = siTreasureBoxItemNumList[selectedItem*2+1];
				SI32 itemNum = minNum + max(1, rand()%(maxNum-minNum+1) );

				if(pclClient->pclItemManager->MakeRandItemUnique( itemUnique, &clOutPutItem[0], 0, 0, &brareswitch ) == false)
					return false;

				// �������� ����
				clOutPutItem[0].SetItemNum( itemNum );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13316))	// �ų� ��� ����
			{
				cltValuesRange* pItemValue = NULL;

				//if(pclClient->siServiceArea == ConstServiceArea_USA || pclClient->siServiceArea == ConstServiceArea_Korea)
				//{				
				//	pItemValue = GetValuesWithRange(ItemValue_13316_ItemNumUSA_KOR, sizeof(ItemValue_13316_ItemNumUSA_KOR) / sizeof(cltValuesRange), 1000);
				//}
				//else
				//{
				//	pItemValue = GetValuesWithRange(ItemValue_13316_ItemNum, sizeof(ItemValue_13316_ItemNum) / sizeof(cltValuesRange), 1000);
				//}

				// [���] �ų� ��� ������ ��� ��,�࿡ ���� ������ ������ ������ �޶�����. (08.11.13)
				// [���] ���� : �Ϻ��� ��� �ų��������� ������ �ٸ��� (08.12.18)
				if(pclClient->IsWhereServiceArea(ConstServiceArea_Japan))
				{
					// ������ ���				
					if(GetKind() == KIND_HERO1 ||  GetKind() == KIND_HERO2 || GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4)
					{
						pItemValue = GetValuesWithRange(ItemValue_13316WithManJapan_ItemNum, sizeof(ItemValue_13316WithManJapan_ItemNum) / sizeof(cltValuesRange), 1000);
					}
					// ������ ���
					else if(GetKind() == KIND_HEROINE1 ||  GetKind() == KIND_HEROINE2 || GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4)
					{
						pItemValue = GetValuesWithRange(ItemValue_13316WithWomanJapan_ItemNum, sizeof(ItemValue_13316WithWomanJapan_ItemNum) / sizeof(cltValuesRange), 1000);
					}
				}
				else
				{
					// ������ ���				
					if(GetKind() == KIND_HERO1 ||  GetKind() == KIND_HERO2 || GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4)
					{
						pItemValue = GetValuesWithRange(ItemValue_13316WithMan_ItemNum, sizeof(ItemValue_13316WithMan_ItemNum) / sizeof(cltValuesRange), 1000);
					}
					// ������ ���
					else if(GetKind() == KIND_HEROINE1 ||  GetKind() == KIND_HEROINE2 || GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4)
					{
						pItemValue = GetValuesWithRange(ItemValue_13316WithWoman_ItemNum, sizeof(ItemValue_13316WithWoman_ItemNum) / sizeof(cltValuesRange), 1000);
					}
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->siServiceArea == ConstServiceArea_Taiwan)
				{
					if(15900 == ItemUnique)
					{
						ItemUnique = 15901;
					}
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
				clOutPutItem[0].CancellationSealingUp( pclserver->sTime );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13317))	// NinJa Spirit Box
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13615), //����  - ��  - ���Ÿ�.
				//		ITEMUNIQUE(13616) //����  - ��  - �ٰŸ�.				
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13338))	// Christmas Spirit BOX
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13633), //ũ�������� �ٰŸ�����
				//		ITEMUNIQUE(13632)  //ũ�������� ���Ÿ�����

				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13318))	// Random Chocolat Box
			{
				cltValuesRange* pItemValue = NULL;

				// ���� : ������ �����ϰ� ���ڻ��ڿ��� ������ ������ ������ (08.12.23)

				pItemValue = GetValuesWithRange(ItemValue_13318_ItemNum, sizeof(ItemValue_13318_ItemNum) / sizeof(cltValuesRange), 1000);

				if ( pItemValue == NULL )		return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13319))	// Random Candy Box
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13319_ItemNum, sizeof(ItemValue_13319_ItemNum) / sizeof(cltValuesRange), 1000);

				if ( pItemValue == NULL )					return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//[����] �߱� ���θ��� ��õ�� ����.
			else if(clitem.siUnique == ITEMUNIQUE(13349))
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13349_ItemNum, sizeof(ItemValue_13349_ItemNum) / sizeof(cltValuesRange), 1000);

				if ( pItemValue == NULL )					return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13342))	// ���ֻ���
			{
				cltValuesRange* pItemValue = NULL;

				if ( pclClient->IsWhereServiceArea(ConstServiceArea_Japan) )
					pItemValue = GetValuesWithRange(ItemValue_13342_ItemNum_Japan, sizeof(ItemValue_13342_ItemNum_Japan) / sizeof(cltValuesRange), 1000);
				else
					pItemValue = GetValuesWithRange(ItemValue_13342_ItemNum, sizeof(ItemValue_13342_ItemNum) / sizeof(cltValuesRange), 1000);

				if ( pItemValue == NULL )					return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}

			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13320))	// Pirate's Chest
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					rndItemUnique1 = ITEMUNIQUE(23718);	// �����Ǻ� 
					rndItemUnique2 = ITEMUNIQUE(23108);	// ��������.
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23718),
						ITEMUNIQUE(23108),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13321))	// �ݺ�����
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13321, sizeof(ItemValue_13321) / sizeof(cltValuesRange), 100);
				if(pItemValue == NULL)			return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(ItemUnique <= 0)				return false;

				if(ItemUnique == 2765)	// ���� �ٽ� ����
				{
					Count = rand()%5+1; // 1~5���� ���� ����
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13358) )	// 2010�ų��̺�Ʈ - �������� - 2009.10.14
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13358, sizeof(ItemValue_13358) / sizeof(cltValuesRange), 1000);
				if(pItemValue == NULL)			return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(ItemUnique <= 0)				return false;

				if(ItemUnique == 3770)	// ���� �ٽ� ����
				{
					Count = rand()%3+1; // 1~3���� ���� ����
				}

				if( ItemUnique == 15900 )
				{
					usedate = 30;
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			// ����ã��-���� �蹶ġ
			else if(clitem.siUnique == ITEMUNIQUE(13347))
			{
				cltValuesRange* pItemValue = NULL;

				pItemValue = GetValuesWithRange(ItemValue_13347, sizeof(ItemValue_13347) / sizeof(cltValuesRange), 100);
				if(pItemValue == NULL)			return false;

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				if(ItemUnique <= 0)				return false;

				switch( ItemUnique ) 
				{
					case ITEMUNIQUE(5010):
					case ITEMUNIQUE(5020):
					case ITEMUNIQUE(5040):
					case ITEMUNIQUE(5050):
						{
							Count = rand()%2+2; 
						}
						break;
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13323) ) // �絹�� �ʻ���
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23095);	
						rndItemUnique2 = ITEMUNIQUE(23705);	
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23096);	
						rndItemUnique2 = ITEMUNIQUE(23710);	
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23095),
							ITEMUNIQUE(23705),
							ITEMUNIQUE(23096),
							ITEMUNIQUE(23710),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				clOutPutItem[0].SetItemNum(1);
				clOutPutItem[1].SetItemNum(1);
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13324) )	// [����] �ų� ���ָӴ�(�븸����) 2008.01.22
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_8120_ItemNumTaiwan, sizeof(ItemValue_8120_ItemNumTaiwan) / sizeof(cltValuesRange), 1000);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13351) )	// ���� [�߱�] pc�� ���� ������
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13351_ItemNum_ChinaPcBang, sizeof(ItemValue_13351_ItemNum_ChinaPcBang) / sizeof(cltValuesRange), 1000);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13326) )	// [����] ��ڻ���(���) -> [����] �����̺�Ʈ. �������ڷ� ����. ������� �ʾƼ�.. 2008-8-12
			{
				if( IsBlankInv(1, INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				cltValuesRange* pItemValue = NULL;
				//[����] �Ϻ��� ���� ó��. => 2008-9-9
				if ( pclClient->IsWhereServiceArea(ConstServiceArea_Japan) )
					pItemValue = GetValuesWithRange(ItemValue_13326_ItemNum_Japan, sizeof(ItemValue_13326_ItemNum_Japan) / sizeof(cltValuesRange), 10000);
				else
					pItemValue = GetValuesWithRange(ItemValue_13326_ItemNum, sizeof(ItemValue_13326_ItemNum) / sizeof(cltValuesRange), 10000);




				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 =  0;

				if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
					Count = pItemValue->siPara2;
				else
					Count = (rand() % pItemValue->siPara2) + 1;


				SI32 ref		= pclItemManager->FindItemRefFromUnique(ItemUnique);
				if(ref <= 0)	return false;

				SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13327) )	// [����] ��ڻ���(ä��)
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13327_ItemNum, sizeof(ItemValue_13327_ItemNum) / sizeof(cltValuesRange), 100);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;

				SI32 ref		= pclItemManager->FindItemRefFromUnique(ItemUnique);
				if(ref <= 0)	return false;

				SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//----------------------------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13331) )	// [����] 2�����ָӴ� 2008.06.30
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13331_ItemNum, sizeof(ItemValue_13331_ItemNum) / sizeof(cltValuesRange), 1000);
				cltValuesRange* pItemValueExtra = GetValuesWithRange(ItemValue_1333_ItemNum_Extra, sizeof(ItemValue_1333_ItemNum_Extra) / sizeof(cltValuesRange), 1000);
				if ( pItemValue == NULL || 
					pItemValueExtra == NULL)
				{
					return false;
				}
				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();
				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;
				clOutPutItem[0].SetItemNum( Count );

				if ( rand()%10 >= 2 )
				{
					SI16 brareswitch = 0;
					SI32 ItemUniqueExtra  = pItemValueExtra->siPara1;
					SI32 CountExtra		 = pItemValueExtra->siPara2;
					SI32 usedateExtra	 = pItemValueExtra->siPara3;

					if ( ItemUniqueExtra <= 0 ) return false;
					cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
					clDrawItem.Init();
					if(pclClient->pclItemManager->MakeRandItemUnique( ItemUniqueExtra, &clOutPutItem[1], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedateExtra) == false)
						return false;
					clOutPutItem[1].SetItemNum( CountExtra );

				}
			}
			//----------------------------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13359))		// [���] 3�� ���ָӴ� (2009.11.26)
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13359_ItemNum, sizeof(ItemValue_13359_ItemNum) / sizeof(cltValuesRange), 1200);
				cltValuesRange* pItemValueExtra = GetValuesWithRange(ItemValue_13359_ItemNum_Extra, sizeof(ItemValue_13359_ItemNum_Extra) / sizeof(cltValuesRange), 10000);

				if ( pItemValue == NULL || pItemValueExtra == NULL)
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;
				SI32 usedate	 = pItemValue->siPara3;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)	return false;
				clOutPutItem[0].SetItemNum( Count );

				// 80%�� Ȯ���� �߰� �������� ���� �� �ִ�.
				if ( rand()%10 >= 2 )
				{
					SI16 brareswitch = 0;
					SI32 ItemUniqueExtra  = pItemValueExtra->siPara1;
					SI32 CountExtra		 = pItemValueExtra->siPara2;
					SI32 usedateExtra	 = pItemValueExtra->siPara3;

					if ( ItemUniqueExtra <= 0 ) return false;
					cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
					clDrawItem.Init();
					if(pclClient->pclItemManager->MakeRandItemUnique( ItemUniqueExtra, &clOutPutItem[1], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedateExtra) == false)	return false;
					clOutPutItem[1].SetItemNum( CountExtra );

				}
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13328) )	// [����] ���
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13328_ItemNum, sizeof(ItemValue_13328_ItemNum) / sizeof(cltValuesRange), 100);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;

				SI32 ref		= pclItemManager->FindItemRefFromUnique(ItemUnique);
				if(ref <= 0)	return false;

				SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13330))	// ����� ���� ����.
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13623), //����� -  ���Ÿ�.
				//		ITEMUNIQUE(13624) // ����� -  �ٰŸ�.				
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if( clitem.siUnique == ITEMUNIQUE(13333) )	//KHY - 0909 - �������� ����  - ���� ���� ����
			{
				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13333_ItemNum, sizeof(ItemValue_13333_ItemNum) / sizeof(cltValuesRange), 1000);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;

				SI32 Count		 = 0;

				if((pItemValue->siPara2) == (pItemValue->siPara3))
				{
					Count = pItemValue->siPara2;
				}
				else
				{
					Count = pItemValue->siPara2 + (rand()%(pItemValue->siPara2+1) );
				}

				SI32 ref		= pclItemManager->FindItemRefFromUnique(ItemUnique);
				if(ref <= 0)	return false;

				SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//==========================================================================================================================================
			//else if(clitem.siUnique == ITEMUNIQUE(13351))	// �߱��� PC�� ���� ���� ����
			//{
			//	cltValuesRange* pItemValue = NULL;

			//	pItemValue = GetValuesWithRange(ItemValue_13351_ItemNum, sizeof(ItemValue_13351_ItemNum) / sizeof(cltValuesRange), 1000);

			//	if ( pItemValue == NULL )		return false;

			//	SI16 brareswitch = 0;
			//	SI32 ItemUnique  = pItemValue->siPara1;
			//	SI32 Count		 = pItemValue->siPara2;
			//	SI32 usedate	 = pItemValue->siPara3;

			//	if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
			//		return false;

			//	clOutPutItem[0].SetItemNum( Count );
			//}
			//==========================================================================================================================================
			// [����] ��̳ʸ�(USA) 1�ֳ� ��� ���� ����  => 2008-9-25
			else if( ITEMUNIQUE(13335) == clitem.siUnique )	
			{
				if( IsBlankInv(1, INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}

				cltValuesRange* pItemValue = GetValuesWithRange(ItemValue_13335_ItemNum, sizeof(ItemValue_13335_ItemNum) / sizeof(cltValuesRange), 1000);
				if ( pItemValue == NULL )
				{
					return false;
				}

				SI16 brareswitch = 0;
				SI32 ItemUnique  = pItemValue->siPara1;
				SI32 Count		 = pItemValue->siPara2;

				SI32 ref		= pclItemManager->FindItemRefFromUnique(ItemUnique);
				if(ref <= 0)	return false;

				SI32 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;;

				cltItem clDrawItem;					// ��÷�ؼ� ���� ���������
				clDrawItem.Init();

				if(pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clOutPutItem[0], 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == false)
					return false;

				clOutPutItem[0].SetItemNum( Count );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13332))	// ȣ�� �Ǻ� ����
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23112);	// �ҷ��� ����
						rndItemUnique2 = ITEMUNIQUE(23729);	// �ҷ��� �Ǻ�
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23113);	// �ҷ��� ����	
						rndItemUnique2 = ITEMUNIQUE(23730);	// �ҷ��� �Ǻ�
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23112),
							ITEMUNIQUE(23729),
							ITEMUNIQUE(23113),
							ITEMUNIQUE(23730),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

			}

			else if(clitem.siUnique == ITEMUNIQUE(13341))	// ������ �Ǻ� ����
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23115);	// ������ ����
						rndItemUnique2 = ITEMUNIQUE(23734);	// ������ �Ǻ�
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23116);	// ������ ����	
						rndItemUnique2 = ITEMUNIQUE(23735);	// ������ �Ǻ�
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23115),
							ITEMUNIQUE(23734),
							ITEMUNIQUE(23116),
							ITEMUNIQUE(23735),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13343))	// ���� ���Ǹ� ����
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13641),	// �˻罺�Ǹ�(��) - �ٰŸ�
				//		ITEMUNIQUE(13642)	// �ųʽ��Ǹ�(��) - ���Ÿ�
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------	
			else if(clitem.siUnique == ITEMUNIQUE(13352))	// �� ���Ǹ� ����
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13652),	// ���� ���Ǹ�(��) - ���Ÿ�
				//		ITEMUNIQUE(13653)	// ���� ���Ǹ�(��) - �ٰŸ�
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------	
			else if(clitem.siUnique == ITEMUNIQUE(13357 ))	// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
			{
				// �ٰŸ��� ���Ÿ��� �����Ҽ� �ֵ��� �Ѵ�.
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13656 ),	// ������ġ
				//		ITEMUNIQUE(13657 )	// ���� ����
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			else if(clitem.siUnique == ITEMUNIQUE(13356))	// �ҷ��� ���Ǹ� �ڽ�
			{
				//const SI32 siBoxItemList[]=
				//{
				//	ITEMUNIQUE(13626),	// �ҷ��� ���Ǹ� - �ٰŸ�
				//	ITEMUNIQUE(13627)	// �ҷ��� ���Ǹ� - ���Ÿ�
				//};

				//SI32 rndItemIndex = rand() % 2;
				//SI32 rndItemUnique = siBoxItemList[rndItemIndex];

				//UI16 uTransFormChar = 0;
				//cltCharServer* pclchar =(cltCharServer*)(pclClient->pclCM->CR[GetID()]);

				//uTransFormChar = pclchar->GetCharKindFromItemUnique(rndItemUnique);

				//if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true) // �̹� �ִٴ� ǥ�������� �ٸ��ϳ��� �����Ѵ�.
				//{
				//	if(rndItemIndex == 0 )				rndItemIndex = 1;
				//	else if(rndItemIndex == 1 )			rndItemIndex = 0;

				//	rndItemUnique = siBoxItemList[rndItemIndex];
				//}

				//if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
				//	return false;
				//clOutPutItem[0].SetItemNum( 1 );
			}
			//------------------------------------------------------------------------------------------------------
			else if(clitem.siUnique == ITEMUNIQUE(13346))	// ��ȥ ���� ����
			{
				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if( pclClient->IsCountrySwitch(Switch_GachaAvatarCorrect) )
				{
					if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23117);	// ��ȥ ���� �Ӹ�
						rndItemUnique2 = ITEMUNIQUE(23696);	// ��ȥ ���Ŀ� �νõ�
					}
					else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
					{
						rndItemUnique1 = ITEMUNIQUE(23118);	// ��ȥ�� �����
						rndItemUnique2 = ITEMUNIQUE(23698);	// ������ �巹��
					}
				}
				else
				{
					const SI32 siBoxItemList[] =	// ���� ������ ���
					{
						ITEMUNIQUE(23117),
							ITEMUNIQUE(23696),
							ITEMUNIQUE(23118),
							ITEMUNIQUE(23698),
					};

					SI32 rndVal = rand();
					SI32 rndItemIndex = rndVal % ( sizeof(siBoxItemList) / sizeof(SI32) ) / 2;

					rndItemUnique1 = siBoxItemList[rndItemIndex*2];
					rndItemUnique2 = siBoxItemList[rndItemIndex*2 + 1];	
				}

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

			}
			//[����] �Ǹ� �Ǻ� ����.
			else if(clitem.siUnique == ITEMUNIQUE(13364))	
			{
				if( IsBlankInv(2, INVMODE_ALL) == false )
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 200, 0, GetID());
					return false;
				}

				SI32 rndItemUnique1 = 0;
				SI32 rndItemUnique2 = 0;

				if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
				{
					rndItemUnique1 = ITEMUNIQUE(23741);	
					rndItemUnique2 = ITEMUNIQUE(23410);	
				}
				else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
				{
					rndItemUnique1 = ITEMUNIQUE(23742);	
					rndItemUnique2 = ITEMUNIQUE(23411);	
				}
				
				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

				if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique2, &clOutPutItem[1], 0, 0, &brareswitch,0,0,0,0,0,0) == false)
					return false;

			}
			else if ( clitem.siUnique == ITEMUNIQUE(13348) ) // ��ȥ�� ���� ���� ����
			{
				SI32 rndItemUnique1 = 0;

				if ( GetKind() == KIND_HERO3 || GetKind() == KIND_HERO4 )
				{
					rndItemUnique1 = ITEMUNIQUE(23736);	// ��ȥ ���Ŀ� �νõ�
				}
				else if ( GetKind() == KIND_HEROINE3 || GetKind() == KIND_HEROINE4 )
				{
					rndItemUnique1 = ITEMUNIQUE(23737);	// ������ �巹��
				}

				if ( rndItemUnique1 )
				{
					if(pclClient->pclItemManager->MakeRandItemUnique( rndItemUnique1, &clOutPutItem[0], 0, 0, &brareswitch,0,0,0,0,0,1) == false)
					{
						return false;
					}

					cltServer* pclserver = (cltServer*)pclClient;
					if ( pclserver )
					{
						clOutPutItem[0].CancellationSealingUp( pclserver->sTime );
					}
				}
				else
				{
					return false;
				}
			}
			
			//------------------------------------------------------------------------------------------------------
			//====================================================================
			// ������ ������ �������� �����Ѵ�.
			//====================================================================

			SI32 i = 0;
			SI32 siOutItemCount = 0;

			// ���޵Ǵ� �������� ����
			for (i=0; i<MAX_BOX_OUTPUT; i++)
			{
				if(clOutPutItem[i].siUnique <= 0)		continue;
				if(clOutPutItem[i].siItemNum <= 0)		continue;

				siOutItemCount++;
			}

			// �κ��丮 �� ���� üũ
			if( IsBlankInv(siOutItemCount,INVMODE_ALL) == false )
			{
				((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
				return false;
			}

			cltItem cltoitem[MAX_BOX_OUTPUT];
			SI16	invpos[MAX_BOX_OUTPUT];

			ZeroMemory(invpos, sizeof(invpos));

			for (i=0; i<MAX_BOX_OUTPUT; i++)
			{
				if(clOutPutItem[i].siUnique <= 0)		continue;
				if(clOutPutItem[i].siItemNum <= 0)		continue;

				// ������ ����
				SI32 rtnvalue;
				if(CanAddInv(INVMODE_ALL, &clOutPutItem[i], &invpos[i], &cltoitem[i], &rtnvalue) == false)
				{
					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, GetID());
					return false;
				}
				else
				{
					if(invpos[i] >= PERSONITEM_INV0 && invpos[i] < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON)
					{
						SetInputItemReserve( invpos[i] , pclClient->CurrentClock );
					}
					else
					{
						return false;
					}
				}
			}

			if ( siOutItemCount == 1 )
			{
				sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos[0], &clOutPutItem[0], pclItemManager->CanPile(clOutPutItem[0].siUnique), clOutPutItem[0].IsCreateSID(pclItemManager), bCanNotice[0] );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
			else if ( siOutItemCount == 2)
			{
				sDBRequest_OpenTreasureBox clMsg( pclCI->GetPersonID(), itempos, &clitem, 0, NULL, invpos[0], &clOutPutItem[0], pclItemManager->CanPile(clOutPutItem[0].siUnique), clOutPutItem[0].IsCreateSID(pclItemManager), bCanNotice[0], invpos[1], &clOutPutItem[1], pclItemManager->CanPile(clOutPutItem[1].siUnique), clOutPutItem[1].IsCreateSID(pclItemManager), bCanNotice[1]  );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}

			//-------------------------------------------------------------------------------
			// sDBRequest_OpenTreasureBox ��Ŷ���� �������� ����ϹǷ� return false
			return false;
			//-------------------------------------------------------------------------------
		}
		break;

	case ITEMTYPE_PREMIUM://�����̾�������.
		{
			if( clitem.siUnique == ITEMUNIQUE(13661))	// ������ ���ݸ�
			{
				SI32 usetime = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // ���ǽð� 48�а�.				

				SI16 index = pclCI->clBI.clBufInfo.FindEmptySlot( BUF_VALENTINEDAY, false );

				if ( index > -1 )
				{
					stBuf addBuf( BUF_VALENTINEDAY, 0, usetime );
					AddBufThroughDB( index, &addBuf , false, 0, NULL, 0 );

					return false;
				}
			}

			// ���� ����Ŭ ��
			if( clitem.siUnique == ITEMUNIQUE(13635) || //������Ʈ
				clitem.siUnique == ITEMUNIQUE(13636) || // �Ҳ���
				clitem.siUnique == ITEMUNIQUE(13637)) //LED���׳�
			{
				cltHorse *pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if(pclHorse == NULL || pclHorse->siHorseUnique <= 0)	return false;
				if(pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)
				{
					if ( pclHorse->HaveSamePremiumParts( clitem.siUnique) ==  false )// ���� ������ �ִ��� ���� �Ѵ�.
					{
						pclHorse->SetPremiumParts( &((cltServer*)pclClient)->pclTime->clDate,clitem.siUnique );
						// DB�� �����Ѵ�. 
						SetUpdateSwitch(UPDATE_HORSE, true, 0);
						UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclHorse, SETHORSE_REASON_PREMIUM_PARTS);
						// ���ΰ� �̿����� �� ������ ������. 
						SendNeighbourMyHorseStatus(pclCI->clHorseInfo.siCurrentShowHorse);
					}					
				}					
			}
			//���ͻ���Ŭ �ƴѰſ� 3��			
			else if (clitem.siUnique == ITEMUNIQUE(13638) ||//����
				clitem.siUnique == ITEMUNIQUE(13639) || //���
				clitem.siUnique == ITEMUNIQUE(13640) )//���
			{
				// ���� �־�� �������� ����Ѵ�. - by LEEKH 2007.10.18
				cltHorse *pclHorse = pclCI->clHorseInfo.GetCurrentShowHorse();
				if(pclHorse == NULL || pclHorse->siHorseUnique <= 0)	return false;
				// ������̴� Ż�� ��ȭ�� ������ ���� �ʴ´�.
				if(pclHorse->siHorseUnique == HORSEUNIQUE_MOTORCYCLE)	return false	;
				if ( pclHorse->HaveSamePremiumParts( clitem.siUnique) ==  false )// ���� ������ �ִ��� ���� �Ѵ�.
				{
					pclHorse->SetPremiumParts( &((cltServer*)pclClient)->pclTime->clDate,clitem.siUnique );
					// DB�� �����Ѵ�. 
					SetUpdateSwitch(UPDATE_HORSE, true, 0);
					UpdateHorseToDB((cltServer*)pclClient, pclCI->clHorseInfo.siCurrentShowHorse, pclHorse, SETHORSE_REASON_PREMIUM_PARTS);
					// ���ΰ� �̿����� �� ������ ������. 
					SendNeighbourMyHorseStatus(pclCI->clHorseInfo.siCurrentShowHorse);
				}
			}
			// ��ȣ���� ��ȯ		- [����] : 2010�ų��̺�Ʈ - ��Ű����[�̺�Ʈ] (13658) �߰�
			else if ( ITEMUNIQUE(13646) == clitem.siUnique || ITEMUNIQUE(13651) == clitem.siUnique|| ITEMUNIQUE(13655) == clitem.siUnique|| ITEMUNIQUE(13654) == clitem.siUnique || ITEMUNIQUE(13659) == clitem.siUnique || ITEMUNIQUE(13658) == clitem.siUnique)
			{
				SI16 siSoulGuardKind	= 0;
				SI16 siLife				= 0;
				SI16 siFellowShip		= 0;

				SI32 siTempReturn		= 0;

				if ( false == CanUseSoulGuardItem(clitem.siUnique, &siSoulGuardKind, &siLife, &siFellowShip, &siTempReturn) )
				{
					return false;
				}

				TCHAR*	pszName			= GetTxtFromMgr( 30146 );	// ��ȣ����
				SI16	siStatus		= SOULGUARD_STATUS_IN;
				SI32	siLimitLife		= 0;
				if ( Const_Unlimit_SoulGuard_Life <= siLife )
				{
					// ���� ���� ��¥ �����Ǿ� �ִٸ� ���� �ִ밪���� �о�־��ش�
					siLimitLife = MAX_SI32;
				}
				else
				{
					// �޾ƿ� ��¥�� �����ð� 1�� �����̹Ƿ� ���ӽð����� �����ϱ� ���� (* 30)�� �����ش�
					siLimitLife = pclserver->pclTime->clDate.GetDateVary() + (siLife*30);
				}

				sDBRequest_SoulGuardCreate clMsg( pclCI->GetPersonID(), pszName, siStatus, siSoulGuardKind, siLimitLife, siFellowShip );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			}
			return false;
		}
		break;
	case ITEMTYPE_QUEST: // ����Ʈ ���� ������
		{
			//if ( ITEMUNIQUE(8121) == clitem.siUnique )
			//{
			//	SI32 siMonsterKind	= pclClient->GetUniqueFromHash( TEXT("KIND_QUESTEMPERORMASTER") );
			//	if ( 0 >= siMonsterKind )
			//	{
			//		return false;
			//	}

			//	SI32 siGetMapIndex	= GetMapIndex();
			//	if ( (0 > siGetMapIndex) || (MAX_MAP_NUMBER <= siGetMapIndex) )
			//	{
			//		return false;
			//	}

			//	SI32 siSourceX		= GetX();
			//	SI32 siSourceY		= GetY();
			//	SI32 siDestX		= 0;
			//	SI32 siDestY		= 0;

			//	bool bIsCreated		= false;

			//	cltMapCommon* pclMapCommon = pclClient->pclMapManager->pclMapArray[siGetMapIndex];
			//	if ( NULL == pclMapCommon )
			//	{
			//		return false;
			//	}
			//	
			//	// Ȥ�� ���� ��ġ�� ã�� ���ߴٸ� �����ϰ� ��ġ�� ��� �� ���鼭 ��ġ�� ã�´�
			//	for ( SI32 siCount=0; siCount<10; siCount++ )
			//	{
			//		if ( false == pclMapCommon->FindEmptyAreaForCharLocate(siMonsterKind, siSourceX, siSourceY, 10, &siDestX, &siDestY, true) )
			//		{
			//			continue;
			//		}

			//		cltInnerStatusInfo clinnerstatus;
			//		clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

			//		SI32 siCreatedID = pclserver->SetNPCChar( siMonsterKind, VILLAGE_NONE, NULL, 0, 0, siDestX, siDestY, siGetMapIndex, NPCITEMMODE_NORMAL, &clinnerstatus );
			//		if ( pclCM->IsValidID(siCreatedID) )
			//		{
			//			// ����Ʈ ���� ���ͷ� �ź� ����
			//			cltCharServer* pclMonster = (cltCharServer*)pclClient->pclCM->GetCharServer(siCreatedID);
			//			if ( NULL == pclMonster )
			//			{
			//				continue;
			//			}

			//			pclMonster->clIdentity.MakeQuest( IDENTITY_QUEST, pclCI->GetPersonID(), GetCharUnique() );
			//			pclMonster->dwTimerClock = pclserver->CurrentClock;
			//			
			//			bIsCreated = true;

			//			break;
			//		}							
			//	}

			//	if ( false == bIsCreated )
			//	{
			//		return false;
			//	}
			//}
		}
		break;

	default:
		MsgBox(TEXT("UseItem()"), TEXT("re974:%d"), itemtype);
		return false;
	}

	//---------------------------------------
	// ��ǰ ����ϱ� ����Ʈ �������̾����� Ȯ���Ͽ� ��ġ�Ѵ�. 
	//---------------------------------------
	// ��ǰ�� ����ϴ� ����Ʈ�� �������̾��� ?
	IncQuestPara(QUEST_CLEAR_COND_USEITEM, clitem.siUnique, clitem.siItemNum);

	// [����] ���� ����Ʈ �̺�Ʈ : ������ ����ϱ�
	if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
	{
		CNServerEvent_Quest* pclSE_Quest = (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();
		if ( pclSE_Quest )
		{
			SI32 siUseItemNum = max(clitem.siItemNum, siQuestCount);

			pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_USEITEM, clitem.siUnique, siUseItemNum );
		}
	}

	return true;
}   

// �������� �κ��丮�� �ִ´�. 
BOOL cltCharServer::AddItemToInventory(cltItem* pclitem)
{
	if(pclitem == NULL)return FALSE;

	// ���Ը� Ȯ���Ѵ�. 
	// �ִ� ���Ը� �ʰ��ϸ� ���̻� �� �� ����. 
	SI32 itemweight = pclitem->GetWeight(pclClient->pclItemManager, TRUE);
	if(pclCI->clCharItem.GetTotalWeight(pclClient->pclItemManager) + itemweight > clPB.GetMaxWeight())
	{
		return FALSE;
	}

	return pclCI->clCharItem.AddInv(pclClient->pclItemManager, pclitem);

}

//ĳ���Ϳ��� �������� �ش�. 
// frompersonid : �������Լ� �������� ���� �ִ°�. 
bool cltCharServer::InputItem(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32 inputitemreason, SI32* prtnvalue)
{
	SI16 itemtopos;
	cltItem cltoitem;

	SI32 topersonid		= pclCI->GetPersonID();
	if(topersonid <= 0)return false;

	// �ڸ��� �ִ��� �˻��Ѵ�.
	bool bInvetoryFull = CanAddInv(INVMODE_ALL, pclitem, &itemtopos, &cltoitem, prtnvalue) ;
	bool bigitem = false ;

	// ��ĥ�� ���� �������̶�� ������ 1�� �ٲ۴�. - by LEEKH 2007.11.23
	if( pclitem->CanPile(pclClient->pclItemManager) == false )
	{
		pclitem->SetItemNum(1);
	}

	// ����� ������ ���ְ� ����!
	// �߰��Ǵ� �������� ��� �������̸�, 
	if( inputitemreason == INPUTITEMPERSON_OPTION_WORDASSEMBLE		// �ܾ��������� ��� �� �������̸�, 
		|| inputitemreason == INPUTITEMPERSON_OPTION_CRAZYEVENT			// ������ �ݰ� �̺�Ʈ�� ��� �� �������̸�
		)
	{
		cltGameMsgResponse_BigWarItem clinfo(GetName(), pclCI->GetPersonID(), 
			pclitem, 0, inputitemreason, 0);

		cltMsg clMsg(GAMEMSG_RESPONSE_BIGWARITEM, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

		// ��� ��ǰ ���� ���. 
		((cltServer*)pclClient)->pclStatisticsManager->clDailyStatistics.siBigItemNum ++;

		// ��� �������� ������ ����Ѵ�.  
		if(inputitemreason == INPUTITEMPERSON_OPTION_WAR)
		{
			// ��� �������̸� �����Ѵ�. 
			TCHAR* pText = GetTxtFromMgr(2808);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_FARM)
		{
			TCHAR* pText = GetTxtFromMgr(2809);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_FARMSUMMON)
		{
			TCHAR* pText = GetTxtFromMgr(2810);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_FISH)
		{
			TCHAR* pText = GetTxtFromMgr(2811);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_FISHSUMMON)
		{
			TCHAR* pText = GetTxtFromMgr(2812);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_FAMELEVEL)
		{
			TCHAR* pText = GetTxtFromMgr(2814);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);

		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_WORDASSEMBLE)
		{
			TCHAR* pText = GetTxtFromMgr(2815);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);

		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_SPEECIALQUEST)
		{
			TCHAR* pText = GetTxtFromMgr(2816);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"), pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_OSAKA)
		{
			TCHAR* pText = GetTxtFromMgr(5278);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_KANGHWADO)
		{
			TCHAR* pText = GetTxtFromMgr(5281);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_CRAZYEVENT)
		{
			TCHAR* pText = GetTxtFromMgr(5299);
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_ROULETTEGAME)
		{
			TCHAR* pText = TEXT("BigItem(�ڴ��)-Name:%s Item:%s Num:%d Success:%d");
			pclClient->pclLog->FilePrint(TEXT("Config\\BigItem.log"),  pText, 
				GetName(), pclitem->GetShortName(pclClient->pclItemManager), pclitem->GetItemNum(),(SI32)bInvetoryFull);
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_INSTANCEMAP)
		{
			pclClient->pclLog->FilePrint(TEXT("Config\\InstanceItem.log"), TEXT("User : [%s] Item : [%s] "),
				GetName(),pclitem->GetShortName(pclClient->pclItemManager));
		}
		else if(inputitemreason == INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE_SPECIAL)
		{
			pclClient->pclLog->FilePrint(TEXT("Config\\PVPLEAGUE_SPECIALPRIZE.log"), TEXT("User : [%s] Item : [%s] "),
				GetName(),pclitem->GetShortName(pclClient->pclItemManager));
		}

		bigitem = true ;
	}

	// �ڸ��� ������ �� �ش�. ��ι��� ���⼭ ������ش�!
	if(bInvetoryFull == false)
	{
		if ( bigitem ) // ��� �������̸� �α׸� ������.
		{
			((cltServer*)pclClient)->SendLog_InventoryFull( pclCI->GetPersonID(),
				pclitem->siUnique,pclitem->GetItemNum(),inputitemreason);
		}

		return false;
	}

	// �̹� �ش� �������� �ִ� ���̶��, 
	SI64 atb = pclItemManager->GetItemAtb(pclitem->siUnique);
	if(cltoitem.siItemNum && (atb & ITEMATB_FIRSTWARITEM))
	{
		while(clItemUseReserveInfo.Push(pclitem->siUnique, pclitem->siItemNum, itemtopos) == false)
		{
			ItemUseReserveAction();
		}
		pclCI->clCharItem.clItem[itemtopos].Increase(pclitem->siItemNum);

		// Ŭ���̾�Ʈ�� ������ ������. 
		cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(pclitem->siUnique);
		if(pclprice)
		{
			cltGameMsgResponse_PersonItemInfo clinfo(itemtopos, PERSONITEMINFO_OPTION_WARITEM, pclitem->siItemNum, 0, &pclCI->clCharItem.clItem[itemtopos], pclprice->siPrice);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);
		}	



		if( INPUTITEMPERSON_OPTION_WAR == inputitemreason)
		{
			// ����Ʈ ������Ʈ
			SI32 siQuestItemNum = pclitem->siItemNum;

			// [����] ����Ʈ ī��Ʈ ����
			if ( 0 < siQuestCount )
			{
				siQuestItemNum = siQuestCount;
			}

			IncQuestPara(QUEST_CLEAR_COND_HUNT_ITEM, pclitem->siUnique,	siQuestItemNum );

			if( siPartyIndex >0 )
			{
				CPartyObj* pParty = pclClient->pclPartyMgr->GetPartyObj( siPartyIndex );

				if(pParty)
				{
					pParty->NotifyGetIemToPartyMember(GetCharUnique(), pclitem );
				}
			}
		}

		// ��Ƽ�� ���Ե� ������� ��Ƽ���鿡�Ե� ������ ȹ�� �޽����� ������

		//��Ƽȹ�渷��
		/*
		if( siPartyIndex > 0 && INPUTITEMPERSON_OPTION_WAR == inputitemreason)
		{
			CPartyObj* pParty = ((cltServer*)pclClient)->pclPartyMgr->GetPartyObj(siPartyIndex);
			if(pParty != NULL)
				for(SI16 i = 0; i < MAX_PARTY_USER_NUM; i++ )
				{
					stPartyUser* pPartyUser = pParty->GetPartyUser(i);
					if(pPartyUser->bPartyStatus == false &&  pPartyUser->siCharUnique <=0) continue;

					SI32 partyUserID = pclCM->GetIDFromCharUnique(pPartyUser->siCharUnique);

					if( partyUserID == siID || ((cltServer*)pclClient)->pclCM->IsValidID(partyUserID) == false) continue;

					cltGameMsgResponse_Party_NotifyItemGet clinfo( GetCharUnique()  , pclitem );
					cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_NOTIFYITEMGET,sizeof(clinfo), (BYTE*)&clinfo);
					((cltServer*)pclClient)->pclCM->CR[partyUserID]->SendNetMsg((sPacketHeader*)&clMsg);
				}
		}
		*/

	}
	else
	{
		//---------------------------------------------
		// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		ItemUseReserveAction();

		//---------------------------------------------
		// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		BulletUseReserveAction();

		// �������� �߰��Ǵ� �ڸ��� �����Ѵ�. 
		clSimpleVary.dwItemInputReserveClock[itemtopos] = pclClient->CurrentClock;

		// ����ڿ��� �������� �ִ� �޽����� ����Ѵ�. 
		sDBRequest_InputItemToPerson clMsg(GetID(), topersonid, itemtopos, inputitemreason, pclitem->CanPile(pclItemManager), pclitem, 0, pclitem->IsCreateSID(pclItemManager));
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return true;
}

// ĳ���Ϳ��� �������� �ְ� �ʿ��� ��ġ�� ���Ѵ�. 
SI32 cltCharServer::GiveItem(SI32 itemunique, SI32 itemnum, SI32 giveitemreason,SI32 usedate, SI32 siSealMode/* =GIVEITEM_SEAL_MODE_NONE */, SI32 EnchantType, SI32 EnchantLevel, SI32 SlotNum)
{
	if ( itemunique		< 1 || itemnum < 1 )
		return 0;

	// �ش� �������� �����ϰ� �����. 
	cltItem clItem;
	SI16 brareswitch = 0;

	// [���] /seq ��ɾ ����ؼ� ���鶧 ��� �߰�
	if(giveitemreason == INPUTITEMPERSON_OPTION_SEQGMCOMMAND)
	{
		// RareRate ����
		SI32 RareRate[4];
		for ( SI32 i = 0 ; i < 4 ; i++ )
		{
			RareRate[i] = GetRareItemRate(i);
		}

		if(pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clItem, RareRate[0], 0, &brareswitch,RareRate[0],RareRate[1],RareRate[2],RareRate[3], 0, usedate, EnchantType, EnchantLevel, SlotNum, true) == false)		return false;
	}
	else
	{
		if(pclClient->pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)		return false;
	}

	// ������ �����Ѵ�. 
	// ��ø ������ �������� ���ϴ� ������ŭ ���� �� �ִ�. 
	if(clItem.CanPile(pclClient->pclItemManager) == true)
	{
		clItem.SetItemNum(itemnum);
	}
	// ��ø �Ұ� �������� 1���� ���� �� �ִ�. 
	else
	{
		clItem.SetItemNum(1);
	}

	// ���Ⱓ�� �ִ� ���� siSealMode���� �к�/���� ���θ� �����Ѵ�
	if ( (0 < clItem.uiDateUseDay) && (0 < siSealMode) )
	{
		if ( GIVEITEM_SEAL_MODE_SEAL == siSealMode )
		{
			clItem.uiDateYear	= 0;
			clItem.uiDateMonth	= 0;
			clItem.uiDateDay	= 0;
		}
		else if ( GIVEITEM_SEAL_MODE_CANCEL == siSealMode )
		{
			cltServer* pclserver = (cltServer*)pclClient;
			if ( pclserver )
			{
				clItem.CancellationSealingUp( pclserver->sTime );
			}
		}
	}

	// �ش�������� �κ��� ���� �� �ִ��� Ȯ���Ѵ�. 
	SI16 itempos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(CanAddInv(INVMODE_ALL, &clItem, &itempos, &cltoitem, &rtnvalue) == false)
	{
		return GIVEITEM_RESULT_NOINVEN;
	}

	//[����] ��ƼȦ. ��Ƽ�忡�� �����ϴ� �������� ��� �����Ѵ�. => 2008. 3. 12
	if( INPUTITEMPERSON_OPTION_PARTYHALL_ITEM == giveitemreason )
	{
		cltItem temp;
		temp.Init();
		temp.siItemNum  = clItem.siItemNum;
		temp.siUnique	= clItem.siUnique;
		temp.clItemCommon.clCommonInfo.uiGetItemReason = cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM;

		if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
		{
			temp.clItemCommon.clCommonInfo.uiDurability		= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
			temp.clItemCommon.clCommonInfo.uiMaxDurability	= (UI32)pclClient->GetGlobalValue( TEXT("GV_Forever_Durability") );
		}

		clItem.Init();
		clItem.Set(&temp);	
	}
	else
	{
		clItem.clItemCommon.clCommonInfo.uiGetItemReason = cltItemCommonInfo::REASON_NO;
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	BulletUseReserveAction();

	// �������� �߰��Ǵ� �ڸ��� �����Ѵ�. 
	clSimpleVary.dwItemInputReserveClock[itempos] = pclClient->CurrentClock;

	// ���� �� �ִٸ� DB�Ŵ������� �������� Ư�� ��ġ�� �ֵ��� ��û �Ѵ�.
	sDBRequest_InputItemToPerson clMsg(GetID(), pclCI->GetPersonID(), itempos, giveitemreason, clItem.CanPile(pclClient->pclItemManager), &clItem, 0, clItem.IsCreateSID(pclClient->pclItemManager));
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	return GIVEITEM_RESULT_SUCCESS;
}

bool cltCharServer::TakeOutItem(SI32 itemunique, SI32 itemnum, SI32 takeoutitemreason)
{
	cltPItemInfo* pcliteminfo = NULL;
	cltCharServer* pclchar = (cltCharServer*)this;
	cltItem clitem;

	pcliteminfo = &pclCI->clCharItem;

	int	i;
	for(i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		if(pcliteminfo->clItem[i].siUnique == itemunique)
		{
			clitem.Set(&pcliteminfo->clItem[i]);
			cltItem *pclFrom = &pclchar->pclCI->clCharItem.clItem[ i ];
			SI32 InvPos = pcliteminfo->GetItemPos( clitem.siUnique );

			if(itemnum <= clitem.siItemNum)
			{
				clitem.siItemNum = itemnum;

				//cyj ��������ۿ� ��ġ ���� �߰�
				while( pclchar->clItemUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, InvPos ) == false )
				{
					pclchar->ItemUseReserveAction();
				}

				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( pclFrom->siItemNum <= clitem.siItemNum )
				{
					pclchar->ItemUseReserveAction();
				}

				// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
				// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
				pclFrom->Decrease(clitem.siItemNum);

				// Ŭ���̾�Ʈ�� ����� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo( i, takeoutitemreason, 0, 0, pclFrom, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				itemnum = 0;
			}
			else
			{
				//cyj ��������ۿ� ��ġ ���� �߰�
				while( pclchar->clItemUseReserveInfo.Push( clitem.siUnique, -clitem.siItemNum, InvPos ) == false )
				{
					pclchar->ItemUseReserveAction();
				}

				// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
				if( pclFrom->siItemNum <= clitem.siItemNum )
				{
					pclchar->ItemUseReserveAction();
				}

				// pclchar->ItemUseReserveAction(); �ؿ� �־�� �Ѵ�. 
				// �׷��� ������ �κ����� ��ǰ�� ��ġ�� ã�� �� ����.!
				pclFrom->Decrease(clitem.siItemNum);

				// Ŭ���̾�Ʈ�� ����� ������ ������. 
				cltGameMsgResponse_PersonItemInfo clinfo( i, takeoutitemreason, 0, 0, pclFrom, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				itemnum -= clitem.siItemNum;
			}
		}
	}
	return true;
}


bool cltCharServer::CanEnchantItem(cltGameMsgRequest_MakeItemInv* pclinfo, SI32 *returnval, SI32 *preturnpara1)
{
	SI32 makeitemunique = pclinfo->siItemUnique;
	SI32 makeitemnum	= pclinfo->siItemNum;


	cltPItemInfo* pclmaterialinv	= NULL;

	// �Ƿ��ڰ� ���� ��� �������� �κ��� �����κ����� ��´�.
	if(pclmaterialinv == NULL)
	{
		pclmaterialinv = &pclCI->clCharItem;

	}

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)return false;

	//----------------------------------------------------------------------
	// �������� ����� ����..
	//-----------------------------------------------------------------------

	// ���������� ������ ���� �Ұ� �Ұ�. 
	if( clInnerStatus.IsStatus(INNERSTATUS_PRISON))
	{			
		*returnval = SRVAL_CAN_NOT_ENCHANTITEM_IN_PRISON;
		return false;
	}

	if( true == bPersonalShopSwitch ||
		true == bPremiumPersonalShop )
	{
		SI32 j = 0;
		if( clShopData.m_siShopMode == PSHOP_MODE_SELL )
		{
			for( j = 0 ; j < MAX_SHOP_ITEM_NUMBER; ++j )
			{
				if( clShopData.m_clItem[j].siUnique == makeitemunique  )
				{
					*returnval		= SRVAL_FAIL_PERSONALSHOP_USEITEM;
					return false;
				}
			}
		}
	}

	//------------------------------------------------------------------------
	// �κ��� �������� �ٰŷ� ������� �ϴ� �������� ���� �� �ִ��� Ȯ���Ѵ�.
	//------------------------------------------------------------------------
	SI32 producenum = 0;
	SI32 canmakertn	= 0;
	SI32 canmakertnpara1 = 0;
	/*
	if(pclClient->pclItemManager->pclItemInfo[ref]->CanMake(MAX_INVITEM_PER_PERSON, 
		&pclmaterialinv->clItem[PERSONITEM_INV0], 
		&pclCI->clCharItem.clItem[PERSONITEM_INV0], 
		&producenum, &canmakertn, &canmakertnpara1,
		false) == false)
	{
		if(canmakertn == CANMAKE_ERROR_NOMATERIAL)
		{
			*returnval		= SRVAL_INSUFFICIENTMATERIAL;		// ���� ����. 
			*preturnpara1	= canmakertnpara1;
		}
		else 
		{
			*returnval	= SRVAL_INSUFFICIENTTOOL;		// ���� ����. 
			*preturnpara1	= canmakertnpara1;
		}
		return false;
	}

	*/


		//-------------------------------------------
		// ���꿡 �ʿ��� ���� �� ������ �����Ѵ�. 
		//-------------------------------------------
		SI32 makeunit = 1;
	if(makeunit <= 0)return false;


	//----------------------------------------------
	// �κ��� �������� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//----------------------------------------------

	// �ش� �κ��� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
	cltItem clOutputItem;
	clOutputItem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
	clOutputItem.SetItemNum( makeitemnum );

	//SI16 sitopos;
	//cltItem cltoitem;
	//SI32 rtnvalue;
	//if(pclmaterialinv->CanAddInv(pclClient->pclItemManager, INVMODE_ALL, &clOutputItem, NULL, &sitopos,&cltoitem, &rtnvalue) ==  false)
	//{
	//	*returnval	= SRVAL_NOEMPTYAREA;		// �� �ڸ��� ��� ����. 
	//	return false;
	//}

	return true;

}

// Item �� ������ִ��� �˻��Ѵ�.
bool cltCharServer::CanMakeItem(cltGameMsgRequest_MakeItemInv* pclinfo, SI32 *returnval, SI32 *preturnpara1)
{	

	SI32 makeitemunique = pclinfo->siItemUnique;
	SI32 makeitemnum	= pclinfo->siItemNum;

	cltPItemInfo* pclmaterialinv	= NULL;
	BOOL	bTutorialQuest = FALSE;
	BOOL	bUseQuestItem = FALSE;

	cltMaterialInfo clMaterialInfo[MAX_MATERIAL_NUMBER];


	// ���� �Ƿ��ڰ� ������ �ִ� ���, ��ȿ�ϸ� ����. 
	if(pclinfo->siMaterialCharUnique)
	{
		if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == false)return false;

		// �Ƿ��� �κ��� �����͸� ���Ѵ�. 
		pclmaterialinv = &pclCM->CR[ pclinfo->siMaterialCharUnique ]->pclCI->clCharItem;
	}

	// �Ƿ��ڰ� ���� ��� �������� �κ��� �����κ����� ��´�.
	if(pclmaterialinv == NULL)
	{
		pclmaterialinv = &pclCI->clCharItem;
	}

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)return false;


	//----------------------------------------------------------------------
	// �������� ����� ����..
	//-----------------------------------------------------------------------
	// ���������� ������ ���� �Ұ� �Ұ�. 
	if( clInnerStatus.IsStatus(INNERSTATUS_PRISON))
	{			
		*returnval = SRVAL_CAN_NOT_MAKEITEM_IN_PRISON;
		return false;
	}
	//----------------------------------------------------------------------
	// Ʃ�丮�� ���� ����Ʈ ������ üũ�Ѵ�.
	//-----------------------------------------------------------------------

	SI16 questtype, questunique, para1, para2;
	SI16 questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKEITEM;

	if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
		&& 	pclinfo->siMaterialCharUnique == 0	) // �����Ƿ� �̸� �ȵȴ�.
	{
		if( para1 == makeitemunique 
			&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1)
			&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2)
			)
		{
			bTutorialQuest = TRUE;

			// ����Ʈ ���� �������� ����ϴ��� ����
			if(pclClient->pclQuestManager->GetTutorialMakeQuestItem(questunique,makeitemunique,clMaterialInfo) == true)
			{
				bUseQuestItem = TRUE;
			}	
			else
			{
				bUseQuestItem = FALSE;
			}
		}
	}

	questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKELEVELITEM;
	if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
		&& 	pclinfo->siMaterialCharUnique == 0	) // �����Ƿ� �̸� �ȵȴ�.
	{
		if( para1 == pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel 
			&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1)
			&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2)
			)
		{
			bTutorialQuest = TRUE;

			// ����Ʈ ���� �������� ����ϴ��� ����
			if(pclClient->pclQuestManager->GetTutorialMakeQuestItem(questunique,makeitemunique,clMaterialInfo) == true)
			{
				bUseQuestItem = TRUE;
			}	
			else
			{
				bUseQuestItem = FALSE;
			}
		}
	}

	//----------------------------------------------------------------------
	// �������� ���� �� �ִ� ����� �غ�Ǿ� �ִ��� Ȯ���Ѵ�.
	// Ʃ�丮�� ����Ʈ ���̰ų� NPC�� ���� �����ϰ�� ����!
	//-----------------------------------------------------------------------
	if(	bTutorialQuest == FALSE && pclinfo->bNPCMake == false )
	{		
		if(pclClient->pclItemManager->pclItemInfo[ref]->CanMake_Skill(&pclCI->clCharSkill, &pclCI->clCharItem, &clPB.clTotalBA) == false)
		{
			*returnval	= SRVAL_SKILLNOTREADYFORMAKE;
			return false;
		}
	}
	else
	{
		// Ʃ�丮�� ����Ʈ ���̶�� ��ų������ ������ �ʴ´�.
	}

	//----------------------------------------------------------------------
	// ��Ƽ ������ �ش� ���� ����Ʈ �ÿ��� ���� �����ϴ�
	//----------------------------------------------------------------------
	SI16 siAntiPotion = ITEMUNIQUE(2796);

	if ( siAntiPotion == makeitemunique )
	{
		questclearcond = QUEST_CLEAR_COND_MAKEITEM;

		if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, siAntiPotion) )
		{
			*returnval = SRVAL_SKILLNOTREADYFORMAKE;
			return false;
		}
	}

	//----------------------------------------------------------------------------------------
	// PCK : �Ҿ���� ����Ʈ���� �����ϴ� �������� �ش� ����Ʈ �ÿ��� ���� �����ϴ�.(09.05.08)
	//----------------------------------------------------------------------------------------

	if ( makeitemunique  == ITEMUNIQUE(8115) || makeitemunique  == ITEMUNIQUE(8116) 
		|| makeitemunique  == ITEMUNIQUE(8117) || makeitemunique  == ITEMUNIQUE(8118))
	{
		questclearcond = QUEST_CLEAR_COND_MAKEITEM;

		if ( false == pclCI->clQuestInfo.IsSameParaQuestGoing(questclearcond, makeitemunique) )
		{
			*returnval = SRVAL_SKILLNOTREADYFORMAKE;
			return false;
		}
	}

	//------------------------------------------------------------------------
	// �κ��� �������� �ٰŷ� ������� �ϴ� �������� ���� �� �ִ��� Ȯ���Ѵ�.
	//------------------------------------------------------------------------


	SI32 producenum = 0;
	SI32 canmakertn	= 0;
	SI32 canmakertnpara1 = 0; 

	if( pclinfo->siMaterialCharUnique || pclinfo->bNPCMake ) // ���� �Ƿ��� ��� ���� ��� ä��
	{
		if(pclClient->pclItemManager->pclItemInfo[ref]->CanMake(MAX_INVITEM_PER_PERSON, 
			&pclmaterialinv->clItem[PERSONITEM_INV0], 
			&pclCI->clCharItem.clItem[PERSONITEM_INV0], 
			&producenum, &canmakertn, &canmakertnpara1,
			pclinfo->bNPCMake, bTutorialQuest,bUseQuestItem,clMaterialInfo) == false)
		{
			if(canmakertn == CANMAKE_ERROR_NOMATERIAL)
			{
				*returnval		= SRVAL_INSUFFICIENTMATERIAL;		// ���� ����. 
				*preturnpara1	= canmakertnpara1;
			}
			else if(canmakertn == CANMAKE_ERROR_NOTOOL) 
			{
				*returnval	= SRVAL_INSUFFICIENTTOOL;		// ���� ����. 
				*preturnpara1	= canmakertnpara1;
			}

			return false;
		}
		//KHY - 1211 - ���ݻ�ǰ - ���� ����
		else if(canmakertn == CANMAKE_USE_ALLPURPOSETOOL) //True �̰� - ���ɵ��� ���� ���.  
		{
			*returnval	= SRVAL_RETURN_USE_ALLPURPOSETOOL;		// ���ɵ��� ���� ���.
		}
	}
	else // �ڽ��� ���� ����� ��� �κ��丮 �ε������� �Ѱ��ָ� üũ
	{
		bool check = false;
		if( true == bPersonalShopSwitch ||
			true == bPremiumPersonalShop )
		{
			if( PSHOP_MODE_SELL == clShopData.m_siShopMode )
			{
				check = true;
			}
		}

		if(pclClient->pclItemManager->pclItemInfo[ref]->CanMakeForServer(MAX_INVITEM_PER_PERSON, 
			&pclmaterialinv->clItem[PERSONITEM_INV0], 
			&pclCI->clCharItem.clItem[PERSONITEM_INV0], 
			&producenum, &canmakertn, &canmakertnpara1,
			false, &siInvMakeItemIndex[0] , &clShopData.m_clItem[0], check, bTutorialQuest,bUseQuestItem,clMaterialInfo) == false)
		{
			if(canmakertn == CANMAKE_ERROR_NOMATERIAL)
			{
				*returnval		= SRVAL_INSUFFICIENTMATERIAL;		// ���� ����. 
				*preturnpara1	= canmakertnpara1;
			}
			else if( CANMAKE_ERROR_USE_PERSONSHOP == canmakertn )
			{
				*returnval	= SRVAL_FAIL_PERSONALSHOP_USEITEM;		// �Ǹ����� ���λ��� �������� ����� �� ����. 
				*preturnpara1	= canmakertnpara1;
			}
			else
			{
				*returnval	= SRVAL_INSUFFICIENTTOOL;		// ���� ����. 
				*preturnpara1	= canmakertnpara1;
			}

			return false;
		}
		//KHY - 1211 - ���ݻ�ǰ - ���� ����
		else if(canmakertn == CANMAKE_USE_ALLPURPOSETOOL) //True �̰� - ���ɵ��� ���� ���.  
		{
			*returnval	= SRVAL_RETURN_USE_ALLPURPOSETOOL;		// ���ɵ��� ���� ���.
		}	
	}

	//-------------------------------------------
	// ���� ������ ���� ���� �䱸������ ������ ����.
	//-------------------------------------------
	if(producenum < makeitemnum)
	{
		*returnval	= SRVAL_MATMATCHNUM;		// ���� ����ġ. 
		return false;
	}

	//-------------------------------------------
	// ���꿡 �ʿ��� ���� �� ������ �����Ѵ�. 
	//-------------------------------------------
	SI32 makeunit = pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.siProductUnit;
	if(makeunit <= 0)return false;

	//-------------------------------------------
	//cyj ����� ������ �����Ͽ� MAX_ITEM_PILE_NUMBER�� �Ѿ�� ����
	//-------------------------------------------
	SI32 needskillunique	= pclClient->pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
	SI32 needskilllevel		= pclClient->pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;


	SI32 tempmakeitemnum = 0;

	if( bTutorialQuest == FALSE )
	{
		tempmakeitemnum = GetMakeItemNum(needskillunique, needskilllevel, makeitemunique, makeitemnum);
	}
	else
	{
		// Ʃ�丮�� ����Ʈ ���̶�� ��ų������ ������ ���������� �̸� ����ġ �ʴ´�. ��ų������ ������ ���� ��������.
		tempmakeitemnum = makeitemnum;
	}


	if(tempmakeitemnum > MAX_ITEM_PILE_NUMBER)
	{
		*returnval	= SRVAL_TOOMANYITEMMAKE;
		*preturnpara1 = tempmakeitemnum;

		return false;

	}

	//----------------------------------------------
	// �κ��� �������� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//----------------------------------------------

	// �ش� �κ��� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
	cltItem clOutputItem;
	clOutputItem.Set(&pclClient->pclItemManager->pclItemInfo[ref]->clItem);
	clOutputItem.SetItemNum( makeitemnum );

	SI16 sitopos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclmaterialinv->CanAddInv(pclClient->pclItemManager, INVMODE_ALL, &clOutputItem, NULL, &sitopos,&cltoitem, &rtnvalue) ==  false)
	{
		*returnval	= SRVAL_NOEMPTYAREA;		// �� �ڸ��� ��� ����. 
		return false;
	}

	//[����] - 2010�ų��̺�Ʈ : �̺�Ʈ �Ⱓ�߿� ��Ű������ ���� �κ��丮 ������ üũ)
	if( pclClient->IsCountrySwitch( Switch_NewYearEvent_2010) )
	{
		//if ( false == IsBlankInv( 2, INVMODE_ALL ) )
		//{
		//	*returnval = SRVAL_NOEMPTYAREA;  // �� �ڸ��� ��� ����. 
		//	return false;
		//}

		SI32 refFortuneCookiePiece = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
		if(ref <= 0)
		{
			*returnval	= SRVAL_NOEMPTYAREA;		// �� �ڸ��� ��� ����. 
			return false;
		}

		cltItem clFortuneCookiePieceItem;
		clFortuneCookiePieceItem.Set( &pclClient->pclItemManager->pclItemInfo[refFortuneCookiePiece]->clItem );
		clFortuneCookiePieceItem.SetItemNum( 8 );	// ������ �ִ�ġ ��ŭ�� ��������(8ĭ)�� üũ

		if(pclmaterialinv->CanAddInv(pclClient->pclItemManager, INVMODE_ALL, &clFortuneCookiePieceItem, NULL, &sitopos, &cltoitem, &rtnvalue) ==  false)
		{
			*returnval	= SRVAL_NOEMPTYAREA;		// �� �ڸ��� ��� ����. 
			return false;
		}
	}

	return true;
}


// �ֹ��� �ٰŷ� ������ �����. 
bool cltCharServer::MakeItem(cltGameMsgRequest_MakeItemInv* pclinfo)
{
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 i, j;
	SI16 para1	= 0;		// �ݵ�� �ʱ�ȭ�Ǿ�� �Ѵ�. 
	SI16 para2	= 0;
	GMONEY sifee	= 0;

	SI32 personid = pclCI->GetPersonID();
	if(personid <= 0)return false;

	// ���� �Ƿ��ڰ� �����Ǿ� ������ ��ȿ���� ������ ����. 
	cltPItemInfo* pclmaterialinv = NULL;
	cltCharServer* pclMaterialChar	= NULL;

	BOOL bTutorialQuest = FALSE;
	SI32 materialpersonid = personid;
	SI32 materialcharunique	= GetCharUnique();
	BOOL bForce_Manufacture_Success = FALSE;		// ������ �������� ������ش�. - ���������, �����Ѹ���

	// ���� �Ѹ��� ȿ���� �ִٸ� ����100%
	cltBufInfo* pclMyBuf = &pclCI->clBI.clBufInfo;
	if(pclMyBuf->IsHaveBuf(BUF_SUCCESS_MANUFACTURE))	bForce_Manufacture_Success = TRUE;

	// ������ ��û�� �Ƿ��ڰ� �ִٸ�...
	if(pclinfo->siMaterialCharUnique)
	{		
		if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == false)
		{
			// �Ƿ��ڰ� �׾��ٸ�... �޽����� �����Ѵ�.
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}

		// ���� �Ѹ��� ȿ���� �ִٸ� ����100%
		cltBufInfo* pclMaterialBuf = &pclClient->pclCM->CR[pclinfo->siMaterialCharUnique]->pclCI->clBI.clBufInfo;
		if(pclMaterialBuf->IsHaveBuf(BUF_SUCCESS_MANUFACTURE))	bForce_Manufacture_Success = TRUE;

		// �Ƿ��ڿ��� ����Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		((cltCharServer*)(pclCM->CR[ pclinfo->siMaterialCharUnique ]))->ItemUseReserveAction();

		//---------------------------------------------
		// �Ƿ��ڿ��� ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
		//---------------------------------------------
		((cltCharServer*)(pclCM->CR[ pclinfo->siMaterialCharUnique ]))->BulletUseReserveAction();


		materialcharunique	= pclinfo->siMaterialCharUnique;
		materialpersonid	= pclCM->CR[ pclinfo->siMaterialCharUnique ]->pclCI->GetPersonID();
		pclmaterialinv = &pclCM->CR[ pclinfo->siMaterialCharUnique ]->pclCI->clCharItem;
		pclMaterialChar	= (cltCharServer*)pclCM->CR[ pclinfo->siMaterialCharUnique ];

	}

	// ���� �κ��� �����͸� Ȯ���Ѵ�. 
	// �Ƿ��ڰ� ���� ���� �� ������������ �Ҵ��Ѵ�.
	if(pclmaterialinv == NULL)
	{
		pclmaterialinv = &pclCI->clCharItem;
		pclMaterialChar	= this;
	}


	//---------------------------------------------
	// �����ڿ��� ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	ItemUseReserveAction();        

	//---------------------------------------------
	// �����ڿ��� ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	BulletUseReserveAction();



	SI32 makeitemunique = pclinfo->siItemUnique;
	SI32 makeitemnum	= pclinfo->siItemNum;
	// �������� ��ø���� �ʴ� ���̶�� ���� ������ ������ 1�� �����ȴ�. 
	SI64 atb = pclClient->pclItemManager->GetItemAtb(makeitemunique);
	if(atb & ITEMATB_OBJECT)
	{
		makeitemnum = 1;
	}

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)
	{
		siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		SendNeighbourMyMakeItemStatus();

		return false;
	}

	// �� ĳ������ ��� ������ ���Ѵ�.
	bool bluckuseswitch = false;			// ��� ��Ұ� ���Ǿ��°�?

	// ���깰�� ���� ������ ���Ѵ�. 
	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(makeitemunique); 


	SI32 returnval		= 0;
	SI32 returnpara1	= 0;
	//__try
	{

		//----------------------------------------------------------------------
		// Ʃ�丮�� ���� ����Ʈ ������ üũ�Ѵ�.
		//-----------------------------------------------------------------------
		SI16 questtype, questunique, para1, para2;
		SI16 questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKEITEM;
		if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
			&& 	pclinfo->siMaterialCharUnique == 0	) // �����Ƿ� �̸� �ȵȴ�.
		{
			if(para1 == makeitemunique
				&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1)
				&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2)
				)				
			{
				bTutorialQuest = TRUE;
			}
		}

		questclearcond =  QUEST_CLEAR_COND_TUTORIALMAKEITEM;
		if(pclCI->clQuestInfo.IsQuestGoing(questclearcond, &questtype, &questunique, &para1, &para2) == true
			&& 	pclinfo->siMaterialCharUnique == 0	) // �����Ƿ� �̸� �ȵȴ�.
		{
			if(para1 == pclClient->pclItemManager->pclItemInfo[ref]->clCondition.siLevel
				&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara1 == para1)
				&& ( pclCI->clQuestInfo.clUnit[questtype].siQuestPara2 < para2)
				)				
			{
				bTutorialQuest = TRUE;
			}
		}

		// �������� ����� ���ٸ� ���ư���.
		if(CanMakeItem(pclinfo, &returnval, &returnpara1) == false)
		{
			// true, false�� �����ش�.
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}

		//-------------------------------------------
		// ���꿡 �ʿ��� ���� �� ������ �����Ѵ�. 
		//-------------------------------------------
		SI32 makeunit = pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.siProductUnit;
		if(makeunit <= 0)
		{
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}

		// ���� ������ �߸� �����Ǿ� �Դ�. 
		// �������Ѵ�. 
		makeitemnum  = makeitemnum / makeunit;
		if( makeitemnum <= 0)makeitemnum	= 1;
		makeitemnum = makeitemnum * makeunit;

		SI32 makerate = makeitemnum / makeunit;

		// DB�� ��� ������ - ��������� �ڸ��� Ȯ���Ѵ�.
		DBMaterialInfo clinfo[MAX_MATERIAL_NUMBER_FOR_DB];
		SI32 materialindex= 0;


		// ����� ���� ��� ���� ��Ḧ �����Ѵ�.

		cltMaterialInfo clMaterials[MAX_MATERIAL_NUMBER];

		if(bTutorialQuest == FALSE)
		{
#ifdef _SAFE_MEMORY
			memcpy( clMaterials	, &pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.clMaterial[0], MAX_MATERIAL_NUMBER * sizeof(cltMaterialInfo) );
#else
			memcpy( clMaterials	, pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.clMaterial, MAX_MATERIAL_NUMBER * sizeof(cltMaterialInfo) );
#endif
		}
		else	// Ʃ�丮�� ����Ʈ ���̶�� ����Ʈ�� ��Ḧ ���ؿ� �����Ѵ�. ����Ʈ�� ��ᰡ ���� ������ ���� ��Ḧ �����Ѵ�.
		{
			cltMaterialInfo clQuestMaterialInfo[MAX_MATERIAL_NUMBER];
			if(pclClient->pclQuestManager->GetTutorialMakeQuestItem(questunique,makeitemunique,clQuestMaterialInfo) == false)
			{
#ifdef _SAFE_MEMORY
				memcpy( clMaterials, &pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.clMaterial[0], MAX_MATERIAL_NUMBER * sizeof(cltMaterialInfo) );
#else
				memcpy( clMaterials, pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.clMaterial, MAX_MATERIAL_NUMBER * sizeof(cltMaterialInfo) );
#endif
			}	
			else
			{
				memcpy( clMaterials	, clQuestMaterialInfo ,MAX_MATERIAL_NUMBER * sizeof(cltMaterialInfo) );
			}			
		}

		for(i = 0;i < MAX_MATERIAL_NUMBER;i++)
		{
			SI32 materialunique = clMaterials[i].siUnique;
			if(materialunique <= 0)continue;
			SI32 materialnum	= clMaterials[i].siNeedNum;

			bool bmaterialfinddswitch = false;

			for(SI32 k =0 ; k < 28 ; k++) //�ڱ� �ڽ��϶�
			{

				if(bmaterialfinddswitch == true)continue;

				SI32 siitemindex = pclCM->CR[materialcharunique]->siInvMakeItemIndex[k];
				if(siitemindex > 0 )
				{
					if(pclmaterialinv->clItem[siitemindex].siUnique == materialunique)
					{
						clinfo[materialindex].siItemUnique	= materialunique;
						clinfo[materialindex].siStgPos		= siitemindex;
						clinfo[materialindex].siUseItemNum	= materialnum * makerate;
						materialindex++;
						j = MAX_INVITEM_PER_PERSON;
						k = 28;
						bmaterialfinddswitch = true;
					}
				}
			}


			if(bmaterialfinddswitch ==false)
			{
				// �κ����� �ش� ��Ḧ ã�´�. 
				for(j = 0;j < MAX_INVITEM_PER_PERSON;j++)
				{
					// �̹� ��Ḧ ã�Ҵٸ�, ���� ���� �� ã�� �ʴ´�. 
					if(bmaterialfinddswitch == true)break;

					if(  (pclmaterialinv->clItem[PERSONITEM_INV0 + j].siUnique == materialunique) &&
						(pclmaterialinv->clItem[PERSONITEM_INV0 + j].siItemNum >= materialnum * makerate)
						)
					{
						clinfo[materialindex].siItemUnique	= materialunique;
						clinfo[materialindex].siStgPos		= PERSONITEM_INV0 + j;
						clinfo[materialindex].siUseItemNum	= materialnum * makerate;


						materialindex++;

						// ���ϴ� ��Ḧ ã�Ҵ�. 
						bmaterialfinddswitch = true;
					}
				}
			}
		}

		// �����ϱ� ���� �÷����� ����߿� ����������� �ִ��� ã�ƺ���.
		for(SI32 k =0 ; k < 28 ; k++)
		{
			SI32 siitemindex = pclCM->CR[materialcharunique]->siInvMakeItemIndex[k];
			if(siitemindex > 0 )
			{
				// ����������� ����100%�� �����Ѵ�.
				if(	pclmaterialinv->clItem[siitemindex].siUnique == ITEMUNIQUE(5395) &&
					pclmaterialinv->clItem[siitemindex].siItemNum >= 1)
				{
					clinfo[materialindex].siItemUnique	= pclmaterialinv->clItem[siitemindex].siUnique;
					clinfo[materialindex].siStgPos		= siitemindex;
					clinfo[materialindex].siUseItemNum	= 1;
					materialindex++;

					bForce_Manufacture_Success = TRUE;
				}
			}
		}

		//KHY - 1211 - ���ݻ�ǰ - ���� ����
		if(returnval == SRVAL_RETURN_USE_ALLPURPOSETOOL) // ���� ������ ���.
		{
			SI32 itemunique = ITEMUNIQUE(8109) ; // ���ɵ���
			SI32 id = GetID();
			cltCharServer* pclChar = NULL;
			pclChar = (cltCharServer*)pclCM->CR[id];

			SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);

			clinfo[materialindex].siItemUnique	= itemunique;
			clinfo[materialindex].siStgPos		= pos;
			clinfo[materialindex].siUseItemNum	= 1;
			materialindex++;
		}
		//------------------------------------------
		// ���꿡 �ʿ��� ������ �������� ������Ų��.
		//------------------------------------------
		if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
		{
			SI32 siSkillLevel = pclClient->pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;
			SI32 decdur = max(1, siSkillLevel/6);

			for(i = 0;i < MAX_TOOL_NUMBER;i++)
			{
				SI32 toolunique = pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.clTool[i].siUnique;
				if(toolunique <= 0)continue;

				bool alreadydealswitch = false;

				// �κ����� �ش� ��Ḧ ã�´�. 
				for(j = 0;j < MAX_INVITEM_PER_PERSON;j++)
				{
					// �̹� �ʿ��� ������ ã�Ҵٸ� , 
					if(alreadydealswitch)continue;
					cltItem* pclToolItem = &pclCI->clCharItem.clItem[PERSONITEM_INV0 + j];

					if(pclToolItem->siUnique == toolunique)
					{
						// �������� �Ҹ��Ų��.
						if ( 0 < pclToolItem->GetDurability() )
						{
							DecreaseEquipDur( PERSONITEM_INV0 + j, decdur );

							if ( 0 >= pclToolItem->GetDurability() )
							{
								UseItemReasonDurabilityZero( PERSONITEM_INV0 + j );
							}
						}
						else
						{
							returnval	= SRVAL_NOTENOUGHTOOLDURABILITY;		// ������ �������� �����ϴ�. 
							para1		= toolunique;
							para2		= decdur;

							//----------------------------------------------
							// ������ �������� ���
							//----------------------------------------------

							SetRareItemRate(0,0,0,0);

							siPersonalMakeItemType = 0;

							cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
							cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
							SendNetMsg((sPacketHeader*)&clMsg);

							//----------------------------------------------
							// �̿��鿡�Ե� �˸���. 
							//----------------------------------------------
							SendNeighbourMyMakeItemStatus();
							return false;
						}

						alreadydealswitch = true;
					}
				}
			}
		}

		//--------------------------------------------
		// Ȯ��. 
		//--------------------------------------------
		SI32 needskillunique	= 0;
		needskillunique			= pclClient->pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
		SI32 needskilllevel		= 0;
		needskilllevel			= pclClient->pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel;

		//cyj ��ų������ ���� ���� �����۰��� ���ϴ� ��ƾ �Լ��� ��
		if(bTutorialQuest == FALSE && pclinfo->bNPCMake == false )
		{
			SI32 siItemNum = 0;

			//����ü ������ ���� ���� ����.
			if(pclClient->pclItemManager->pclItemInfo[ref]->siType != ITEMTYPE_CRYSTAL)
			{
				siItemNum = GetMakeItemNum(needskillunique, needskilllevel, makeitemunique, makeitemnum);			
			}
			else
				siItemNum = makeitemnum;

			if(bForce_Manufacture_Success && siItemNum < makeitemnum)
			{
				// ���� ����ȿ���� �ִµ� ���ж��, ������ ���� ���·� �������ش�.
				makeitemnum = makeitemnum;
			}
			else
			{
				makeitemnum = siItemNum;
			}
		}
		else
		{

			//[����] Ʃ�丮�� ����Ʈ �߿� ��ų������ ���� ������ ������ ��ȭ�� ����.
		}

		// ���� �ֽ�ȸ�� ������ ���� ���� ������ ���ϰų� ���Ѵ�. ������Ʈ�� �ƴ� ���
		// �̴ϰ��� ������ 10000�� �Ѿ�� ������ 10000������ ó��
		if( 10000 <= siMonsterCorp )
		{
			siMonsterCorp = 10000;
		}

		if((atb & ITEMATB_OBJECT) == 0)
		{
			SI32 rate = min(1000,max(-1000,siMonsterCorp / 10)) ;

			makeitemnum = makeitemnum + ( ( makeitemnum * rate ) / 10000 ); 
		}

		//����ü ������ ���� ���� ����.
		if(pclClient->pclItemManager->pclItemInfo[ref]->siType == ITEMTYPE_CRYSTAL)
		{
			makeitemnum = GetMakeCrystalItemNum(needskillunique, needskilllevel, makeitemunique, makeitemnum);							
		}


		//cyj ���� �ֽ�ȸ�� ������ �������ķ� ���Ƶ� ���оȵǵ���
		//// 1���� �̻� ������ �Ұ�. 
		//if(makeitemnum > MAX_ITEM_PILE_NUMBER)
		//{
		//	returnval	= SRVAL_TOOMANYITEMMAKE;	
		//	para1		= makeitemnum;
		//	return false;
		//}

		//------------------------------------------
		// ���� ������ �غ��Ѵ�. 
		//------------------------------------------
		cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;
		SI32 addlevel = 0;
		SI32 qualityrrate = pclitemmanager->GetQualityRate(makeitemunique, GetID(), &addlevel);

		//------------------------------------------
		// ��ȣ���ɿ� ���� ������ �ɷ� ���
		//------------------------------------------
		if ( pclClient->IsCountrySwitch(Switch_SoulGuard) )
		{
			SI32 siAddQualIty = SoulGuardAbilityActivity( SOULGUARD_ABILITY_MAKEABILITY_UP );
			if ( 0 < siAddQualIty )
			{
				qualityrrate = qualityrrate + ((qualityrrate*siAddQualIty)/100);
			}
		}

		// ���� ����. 
		// obj�������� ��� ������ ���缭 �����. 
		bool balmostfailswitch = false;

		// �������й��� - by LEEKH 2007.07.23
		//if( pclClient->IsWhereServiceArea(ConstSwitch_DoNotFailedMakeItem) )
		if( pclClient->IsCountrySwitch(Switch_DoNotFailedMakeItem) )
		{
			if(makeitemnum == 0 && atb & ITEMATB_OBJECT)
			{
				makeitemnum	= 1;
				qualityrrate = rand() % 41 + 10;
				balmostfailswitch	= true;
			}
		}

		//cyj �����۷� ����
		//// ���� ����Ǿ� ���и� ����Ѵ�. 
		//SI32 luckquality = 0;
		//if(pclprice)
		//{
		//	SI32 curprice	= pclprice->siPrice;
		//	
		//	// ���ں�Ȱ 
		//	if(makeitemnum == 0)
		//	{
		//		if(atb & ITEMATB_OBJECT)
		//		{
		//			curprice /= 3000;
		//			
		//			if(curprice)
		//			{
		//				SI32 luckrate = 20 + min(30, luck * 100 / curprice);
		//				
		//				if((rand() % 100) < luckrate)
		//				{
		//					makeitemnum	= 1;
		//					qualityrrate = 20 + rand() % 10;
		//					
		//					bluckuseswitch		= true;
		//					balmostfailswitch	= true;
		//				}
		//			}
		//		}
		//	}
		//	
		//	// � ���� ������ �������� ����, 
		//	curprice	= pclprice->siPrice;
		//	if(atb & ITEMATB_OBJECT)
		//	{
		//		curprice /= 3000;
		//		
		//		if(curprice)
		//		{
		//			SI32 luckrate = min(50, luck * 100 / curprice);
		//			
		//			if((rand() % 100) < luckrate)
		//			{
		//				SI32 data = pclprice->siPrice / 10000;
		//				if(data)
		//				{
		//					luckquality = min(15, luck * 100 / data);
		//					bluckuseswitch	= true;
		//				}
		//			}
		//		}
		//	}
		//}


		cltItem clOutputItem;
		SI16 brareswitch = 0;

		// ��ڴ� ������ RareRate�� ����Ѵ�.
		SI32 RareRate[4];
		for ( int k = 0 ; k < 4 ; k ++ )	RareRate[k] = GetRareItemRate(k);

		// �������� �����Ѵ�.
		if(pclClient->pclItemManager->MakeRandItemUnique(makeitemunique, &clOutputItem,
			qualityrrate , addlevel, &brareswitch,
			RareRate[0],RareRate[1],RareRate[2],RareRate[3],siMonsterCorp) == false)
		{
			//----------------------------------------------
			// ������ �������� ���
			//----------------------------------------------

			SetRareItemRate(0,0,0,0);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();


			return false;
		}
		SetRareItemRate(0,0,0,0);

		SI16 siMakerServerUnique = 0;
		// ��ǰ�̸� ��ǰ �ڵ带 �����Ѵ�.
		// ��ǰ�̸� ��ǰ �ڵ带 �����Ѵ�.
		if(brareswitch == 1 )			// ��ǰ
		{
			clOutputItem.siMakerPersonID = personid;
			clOutputItem.clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_2;
			siMakerServerUnique = pclserver->siServerUnique;
		}
		else if ( brareswitch == 2 )	// ȣǰ
		{
			clOutputItem.siMakerPersonID = personid;
			clOutputItem.clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_1;
			siMakerServerUnique = pclserver->siServerUnique;
		}
		else if ( brareswitch == 3 && pclClient->siServiceArea != ConstServiceArea_China )	// ���ǰ
		{
			clOutputItem.siMakerPersonID = personid;
			clOutputItem.clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_5;
			siMakerServerUnique = pclserver->siServerUnique;
		}
		// ��ǰ
		else if( -1 == brareswitch )
		{
			clOutputItem.clItemCommon.clCommonInfo.uiRareInfo = RARELEVEL_6;
		}


		// ��ǰ �Ǵ� ȣǰ�� ���
		if ( brareswitch == 1 || brareswitch == 2 )
		{
			// ��尡 �ִٸ� �������Ʈ�� ������Ų��.
			if ( pclCI->clBI.clGuildRank.IsGuildMember() == true )
			{
				cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCI->clBI.clGuildRank.GetGuildUnitIndex());
				if ( pGuild )
				{
					sDBRequest_Guild_ChangeGuildPoint clMsg(pGuild->siUnique,pclCI->GetPersonID(),100,TYPE_GUILDPOINT_ADD_MAKERARE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}
		}

		//----------------------------------------------
		// �κ��� �������� ���� ������ �ִ��� Ȯ���Ѵ�. 
		//----------------------------------------------

		// �ش� �κ��� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
		SI16 sitopos;
		cltItem cltoitem;
		SI32 rtnvalue;

		clOutputItem.SetItemNum(makeitemnum);
		if(makeitemnum	== 0)
		{
			bluckuseswitch = false;		// ���꿡 �����ϴ� ��쿡�� ���� ���� �ʴ´�. 

			clOutputItem.Init();

			// ���������� Ŭ���̾�Ʈ�� �˸���. 
			cltItem clitem;
			clitem.siUnique = makeitemunique;
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_MAKEFAIL, 0, 0, &clitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;
			cltGameMsgResponse_MakeItemSwitch clinfo2( 0 );
			cltMsg clMsg2(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo2), (BYTE*)&clinfo2);
			SendNetMsg((sPacketHeader*)&clMsg2);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();


		}

		if(pclMaterialChar->CanAddInv(INVMODE_ALL, &clOutputItem, &sitopos,&cltoitem, &rtnvalue) ==  false)
		{
			if ( makeitemnum > 0 )
			{
				returnval	= SRVAL_NOEMPTYAREA;		// �� �ڸ��� ��� ����.

				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;
			}
		}

		// ������� �����. 
		MakeHunger();

		// �������ٺ�
		SI32 ordernumber = min(pclinfo->siItemNum, makeitemnum);
		//---------------------------------------------------------------
		// �Ƿ��ڿ� �����ڰ� �ٸ� ���, �Ƿ����� ���λ��� ������ �����Ѵ�. 
		//---------------------------------------------------------------
		bool	bRequest_Want_Make	=	false	;
		// ���� �����Ƿ� ���
		if ( pclinfo->bRequestManufacture ==true ) 
		{
			bRequest_Want_Make	= true	;
			// �����Ƿ��ڰ� ���������� üũ �ؾ��Ѵ�
			cltCharServer* pclcharshopper	= (cltCharServer* )pclCM->CR[ pclinfo->siMakeCharUnique ];	
			if(pclcharshopper == NULL)	return false;	//�߸��� �ɸ�������
			if(pclcharshopper->bPersonalShopSwitch == false)
			{
				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;// ������ �����ϰ� ���� �ʴ�.
			}
			// ���� ������ �����Ƿ������� Ȯ���Ѵ�. 
			if(pclcharshopper->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM_WANT)
			{
				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;// ������ ��尡 MAKE ITEM�� �ƴϴ�.
			}
			// �����Ƿ�ǰ���� �������� Ȯ���Ѵ�. 
			if(pclcharshopper->clShopData.m_clItem[0].siUnique != pclinfo->siItemUnique)
			{
				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;
			}
			// ���� �Ƿ� ���λ����� �����ִ� �Ƿ� ������ ���� �ִ����� �˻��Ѵ�.
			if(ordernumber <= 0)
			{
				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
				cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;
			}
			// ���� �Ƿ� ���λ����� �����ִ� �����ۼ��� Update �Ѵ�.
			pclcharshopper->clShopData.m_clItem[0].siItemNum =  0	;
			//---------------------------------------------------------------
			sifee	= pclcharshopper->clShopData.m_siPrice[0];
		}
		else
		{
			///�׿��� ��� 
			if(pclinfo->siMaterialCharUnique)
			{
				cltCharServer* pclcharshopper	= (cltCharServer* )pclCM->CR[ materialcharunique ];
				if(pclcharshopper->bPersonalShopSwitch == false)
				{
					siPersonalMakeItemType = 0;

					cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
					SendNetMsg((sPacketHeader*)&clMsg);

					//----------------------------------------------
					// �̿��鿡�Ե� �˸���. 
					//----------------------------------------------
					SendNeighbourMyMakeItemStatus();

					return false;// ������ �����ϰ� ���� �ʴ�.
				}
				// ���� ������ �����Ƿ������� Ȯ���Ѵ�. 
				if(pclcharshopper->clShopData.m_siShopMode != PSHOP_MODE_MAKEITEM)
				{
					siPersonalMakeItemType = 0;

					cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
					SendNetMsg((sPacketHeader*)&clMsg);

					//----------------------------------------------
					// �̿��鿡�Ե� �˸���. 
					//----------------------------------------------
					SendNeighbourMyMakeItemStatus();

					return false;// ������ ��尡 MAKE ITEM�� �ƴϴ�.
				}
				// �����Ƿ�ǰ���� �������� Ȯ���Ѵ�. 
				if(pclcharshopper->clShopData.m_clItem[0].siUnique != pclinfo->siItemUnique)
				{
					siPersonalMakeItemType = 0;

					cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
					SendNetMsg((sPacketHeader*)&clMsg);

					//----------------------------------------------
					// �̿��鿡�Ե� �˸���. 
					//----------------------------------------------
					SendNeighbourMyMakeItemStatus();

					return false;
				}
				// ���� �Ƿ� ���λ����� �����ִ� �Ƿ� ������ ���� �ִ����� �˻��Ѵ�.
				if(pclcharshopper->clShopData.m_clItem[0].siItemNum - ordernumber < 0)
				{
					siPersonalMakeItemType = 0;

					cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
					cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
					SendNetMsg((sPacketHeader*)&clMsg);

					//----------------------------------------------
					// �̿��鿡�Ե� �˸���. 
					//----------------------------------------------
					SendNeighbourMyMakeItemStatus();

					return false;
				}
				// ���� �Ƿ� ���λ����� �����ִ� �����ۼ��� Update �Ѵ�.
				pclcharshopper->clShopData.m_clItem[0].siItemNum -= ordernumber;
				//---------------------------------------------------------------
				sifee	= pclcharshopper->clShopData.m_siPrice[0];
			}
		}
		// NPC������ ��쿡
		if ( pclinfo->bNPCMake )
		{
			// ���� �ü��� 10% �� ������� �����Ѵ�.
			cltItemPriceUnit* pPrice = pclitemmanager->GetCurrentPrice( clOutputItem.siUnique );
			if ( pPrice )
			{
				sifee = pPrice->siPrice / 10;
			}
			else
			{
				return false;
			}
		}

		//-------------------------------------------
		// ���� �� ������ DBManager���� ��û�Ѵ�. 
		//-------------------------------------------
		// �������� �߰��Ǵ� �ڸ��� �����Ѵ�. 
		pclMaterialChar->clSimpleVary.dwItemInputReserveClock[sitopos] = pclClient->CurrentClock;

		sDBRequest_MakeItemInv clMsg(GetID(), personid, materialpersonid, clinfo,/* clToolList,*/ sitopos, &clOutputItem, clOutputItem.CanPile(pclClient->pclItemManager), balmostfailswitch, clOutputItem.IsCreateSID(pclClient->pclItemManager), 0, 
			sifee * ordernumber,  ordernumber, pclinfo->siItemUnique, pclinfo->bNPCMake, siMakerServerUnique,bRequest_Want_Make);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


		//------------------------------------------------------
		// �Ҹ�� ���Ḧ ��賽��. - ��������� ����
		//------------------------------------------------------
		for(i = 0;i < MAX_MATERIAL_NUMBER_FOR_DB;i++)
		{
			if(clinfo[i].siItemUnique)
			{
				pclitemmanager->AddUseNum(clinfo[i].siItemUnique, clinfo[i].siUseItemNum);

				// ���ο� ��� - ������ ��� ��踦 ����.
				NStatistics_Add("Item", clinfo[i].siItemUnique, "UsedMakeMtrl", clinfo[i].siUseItemNum);
				NStatistics_Set("Item", clinfo[i].siItemUnique, "Name", pclClient->pclItemManager->GetName(clinfo[i].siItemUnique));
			}
		}

		//-------------------------------------------------------
		// ����� ���� ��� ��� ������ �������� ���ҽ�Ų��. 
		//-------------------------------------------------------
		//DecreaseSkillItemEquipDur(needskillunique, true);

		// ��ǰ�� ������� ��� ��ü ������ �˸���. 
		if( makeitemnum && brareswitch > 0)
		{
			// ����� �����. 
			TCHAR itemname[128]=TEXT("");
			if( clOutputItem.GetFullName(((cltServer*)(pclClient))->pclItemManager, itemname, 128) == true)
			{
				SI32 extraskilllevel = addlevel % 1000;		// ��ų ��ġ (���̰�)
				SI32 extrahand = (addlevel / 1000) / 5;		// ������ ��ġ (���̰�)

				switch( brareswitch )
				{
				case RARELEVEL_1:	// ȣǰ
				case RARELEVEL_2:	// ��ǰ
					{
						((cltServer*)(pclClient))->pclLog->FilePrint(TEXT("config\\RareItemRecord.log"), TEXT("Person:[%s]	item:[%s]	stiwch[%d]	useday[%d]	ExtraSkill[%d]	ExtraHand[%d]"), GetName(), itemname, RAREITEM_NOTICE_SWITCH_MADE , clOutputItem.uiDateUseDay, extraskilllevel, extrahand);
					}
					break;
				case RARELEVEL_5:	// ���ǰ
					{
						((cltServer*)(pclClient))->pclLog->FilePrint(TEXT("config\\RareItemRecord_HighGrade.log"), TEXT("Person:[%s]	item:[%s]	stiwch[%d]	useday[%d]	ExtraSkill[%d]	ExtraHand[%d]"), GetName(), itemname, RAREITEM_NOTICE_SWITCH_MADE , clOutputItem.uiDateUseDay, extraskilllevel, extrahand);
					}
					break;
				case RARELEVEL_6:	// ��ǰ - ����� ������ ����.
				case RARELEVEL_3:	// ������
				case RARELEVEL_4:	// ������
					{
					}
					break;
				}
			}

			// ��ǰ, ȣǰ�϶��� �˷��ش�.
			if( 1 == brareswitch || 2 == brareswitch  )
			{
				SI32 makerid = pclCM->GetIDFromPersonID(pclCI->GetPersonID());

				((cltServer*)(pclClient))->SendRareItemMade(makerid, &clOutputItem, RAREITEM_NOTICE_SWITCH_MADE );
			}
		}
		// [����] ���� ��ȯ���� ���������� 
		else if ( (makeitemnum) && (( ITEMUNIQUE(12520) == clOutputItem.siUnique ) || ( ITEMUNIQUE(12525) == clOutputItem.siUnique )) ) 
		{
			SI32 makerid = pclCM->GetIDFromPersonID(pclCI->GetPersonID());

			((cltServer*)(pclClient))->SendRareItemMade(makerid, &clOutputItem, RARAITEM_NOTICE_SWITCH_SUMMONDOLL );
		}


		//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�
		// ������ ����� �� ����� �������� ��´�.

		DecreaseCrystalDurAC(CRYSTAL_DECREASE_DURABILITY_MKNUM);
		DecreaseCrystalDurDE(CRYSTAL_DECREASE_DURABILITY_MKNUM);


		//[����] - ������ ���� �۾��� �Ϸ� �Ǹ� 3% Ȯ���� 1���� ��Ű������ ���� (�̺�Ʈ �Ⱓ�� �ƴϰų� ������ �������� ��Ű �϶� �۵� ����)
		if ( ITEMUNIQUE(13063) != clOutputItem.siUnique )
		{
			if ( 0 < needskillunique && 0 < needskilllevel )
			{
				GiveFortuneCookiePiece( 30, 1);		
			}
		}
	}
	//__finally
	{
		if( returnval > 0 )
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendServerResponseMsg(0, returnval,  para1, para2, GetCharUnique());
			siMonsterCorp = 0 ;
			dwStartMiniGameTime = 0;
		}

	}

	return true;
}


// �ֹ��� �ٰŷ� ������ �����. 
bool cltCharServer::EnchantItem(cltGameMsgRequest_MakeItemInv* pclinfo)
{
	SI32 i;
	SI16 para1	= 0;		// �ݵ�� �ʱ�ȭ�Ǿ�� �Ѵ�. 
	SI16 para2	= 0;
	SI64 sifee	= 0;

	SI32 personid = pclCI->GetPersonID();
	if(personid <= 0)
		return false;

	// ���� �Ƿ��ڰ� �����Ǿ� ������ ��ȿ���� ������ ����. 
	cltPItemInfo* pclmaterialinv = NULL;
	cltCharServer* pclMaterialChar	= NULL;

	SI32 materialpersonid = personid;
	SI32 materialcharunique	 = 0;

	BOOL bUseBlessingStone = FALSE;
	SI32 siSuccessUpItemNum = 0; 

	if(pclinfo->siMaterialCharUnique==0)
		materialcharunique	= GetCharUnique();
	else
		materialcharunique= pclinfo->siMaterialCharUnique;


	if(pclinfo->siMaterialCharUnique)
	{
		if(pclCM->IsAlive(pclinfo->siMaterialCharUnique) == false)
		{
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}

		// �Ƿ��ڿ��� ����Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
		((cltCharServer*)(pclCM->CR[ pclinfo->siMaterialCharUnique ]))->ItemUseReserveAction();

		materialcharunique	= pclinfo->siMaterialCharUnique;
		materialpersonid	= pclCM->CR[ pclinfo->siMaterialCharUnique ]->pclCI->GetPersonID();
		pclmaterialinv = &pclCM->CR[ pclinfo->siMaterialCharUnique ]->pclCI->clCharItem;
		pclMaterialChar	= (cltCharServer*)pclCM->CR[ pclinfo->siMaterialCharUnique ];

	}

	// ���� �κ��� �����͸� Ȯ���Ѵ�. 
	if(pclmaterialinv == NULL)
	{
		pclmaterialinv = &pclCI->clCharItem;
		pclMaterialChar	= this;
	}


	//---------------------------------------------
	// �����ڿ��� ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	ItemUseReserveAction();                                                                                                                                                                                                                                                              



	SI32 makeitemunique = pclinfo->siItemUnique;
	SI32 makeitemnum	= 1;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	if(ref <= 0)
	{
		siPersonalMakeItemType = 0;

		cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);

		//----------------------------------------------
		// �̿��鿡�Ե� �˸���. 
		//----------------------------------------------
		SendNeighbourMyMakeItemStatus();

		return false;
	}



	// ���깰�� ���� ������ ���Ѵ�. 
	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(makeitemunique); 


	SI32 returnval		= 0;
	SI32 returnpara1	= 0;
	// by LEEKH 2008-10-06 __try ���� ����
	//__try
	{

		// �������� ����� ���ٸ� ���ư���.
		if(CanEnchantItem(pclinfo, &returnval, &returnpara1) == false) 
		{
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}
		//-------------------------------------------
		// ���꿡 �ʿ��� ���� �� ������ �����Ѵ�. 
		//-------------------------------------------
		SI32 makeunit = pclClient->pclItemManager->pclItemInfo[ref]->clProductionInfo.siProductUnit;
		if(makeunit <= 0)
		{
			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo( 0 );
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}
		// ���� ������ �߸� �����Ǿ� �Դ�. 
		// �������Ѵ�. 

		if( makeitemnum <= 0)makeitemnum	= 1;
		SI32 makerate = makeitemnum / makeunit;

		DBMaterialInfo clinfo[MAX_ENCHANT_NUMBER];
		SI32 matunique[MAX_ENCHANT_NUMBER] ;	

		for(i =0; i < MAX_ENCHANT_NUMBER; i++)
		{
			clinfo[i].Init();
			matunique[i]= 0;
		}

		////////// ��þƮ ������ ���� �ູ�� ���� ������ üũ

		bUseBlessingStone = FALSE;
		siSuccessUpItemNum = 0;
		BOOL bUseSealingIgnore = FALSE;

		for(SI32 i =0; i< NOW_ENCHANT_NUMBER; i++)
		{
			SI32 siItemIndex = 0;

			siItemIndex  = pclCM->CR[GetCharUnique()]->siElementEnchantInx[i];

			if( siItemIndex > 0	&& siItemIndex < MAX_ITEM_PER_PERSON )
			{
				if (pclmaterialinv->clItem[siItemIndex].siUnique == ITEMUNIQUE(5370) )
				{
					bUseBlessingStone = TRUE;
				}

				if( pclmaterialinv->clItem[siItemIndex].siUnique == ITEMUNIQUE(13606) )
				{
					siSuccessUpItemNum = pclmaterialinv->clItem[siItemIndex].GetItemNum();
					siSuccessUpItemNum = min(10,siSuccessUpItemNum);
				}
				if( pclmaterialinv->clItem[siItemIndex].siUnique == ITEMUNIQUE(13607) )
				{
					bUseSealingIgnore = TRUE;
				}
			}
		}

		SI32 materialindex= 0;		
		SI32 OrgInx =pclCM->CR[GetCharUnique()]->siOrgInvEnchantInx; //pclCM->CR[materialcharunique]->siOrgInvEnchantInx;
		cltItem orgitem = pclmaterialinv->clItem[OrgInx];

		// �ͼ��� �ȵ� �������̶�� �Ͻùк� ���� ������� �ʴ´�.
		if( bUseSealingIgnore && orgitem.IsBelonging( ((cltServer*)pclClient)->pclItemManager ) == false )
		{
			bUseSealingIgnore = FALSE;
		}

		stEnchantNeed materialunique1;
		pclClient->pclItemManager->GetEnchantNeedItem(orgitem, &materialunique1, siSuccessUpItemNum ,bUseBlessingStone,bUseSealingIgnore);

		//cyj ��� ������� ��þƮ 100% ����
		if(bSuccessEnchant && GetGameMasterLevel() > BASIC_GAMEMASTER_LEVEL)
		{
			materialunique1.EnchantRate	= 1.0f;
			materialunique1.siNeedSkill = 0;
		} 

		//if(	pclClient->IsWhereServiceArea( ConstSwitch_EnchantNoSealing) )
		if(	pclClient->IsCountrySwitch( Switch_EnchantNoSealing) )
		{
			//KHY - 0720 - ��þƮ ���� �ͼ� �����۵� ��æƮ ����.
		}
		else
		{
			// �ͼӹ��� �����۵� ��� ���߰� ������ Ǯ���ִٸ� ����� �ɼ� ����.		
			if( orgitem.IsBelonging( ((cltServer*)pclClient)->pclItemManager ) && bUseSealingIgnore == FALSE )	
			{
				cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_NOSEALINGUP_ENCHANTFAIL, 0, 0, &orgitem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				SendNetMsg((sPacketHeader*)&clMsg);

				siPersonalMakeItemType = 0;

				cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
				cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
				SendNetMsg((sPacketHeader*)&clMsg1);

				//----------------------------------------------
				// �̿��鿡�Ե� �˸���. 
				//----------------------------------------------
				SendNeighbourMyMakeItemStatus();

				return false;
			}
		}
		SI32 siMaxGrade = pclClient->pclItemManager->GetItemGrade(orgitem.siUnique);
		SI32 siOrgGrade = orgitem.Element.siPower;

		//�ֻ��� ��æƮ ������ ���� üũ
		if(siMaxGrade <= siOrgGrade)
		{
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_ENCHANTITEMFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			return false;
		}

		bool bitemenchant = true;

		SI32 materialunique =0;
		SI32 materialnum =0;
		SI32 siitemindex =0;

		for(SI32 i =0; i< MAX_ENCHANT_NUMBER; i++)
		{
			bool bmaterialfinddswitch = false;

			matunique[i] = materialunique1.siElementUnique[i];
			materialunique = matunique[i];
			if(materialunique <= 0) continue;
			for(SI32 k =0 ; k < (NOW_ENCHANT_NUMBER+1)  ; k++) //�ڱ� �ڽ��϶�				
			{
				materialnum = 0;

				if(bmaterialfinddswitch == true)continue;

				siitemindex = 0;
				if(k==0 )
					siitemindex = pclCM->CR[GetCharUnique()]->siMatInvEnchantInx;
				else
					siitemindex = pclCM->CR[GetCharUnique()]->siElementEnchantInx[k -1];

				materialnum= materialunique1.siElementNum[i];
				if(siitemindex > 0 )
				{
					if(pclmaterialinv->clItem[siitemindex].siUnique == materialunique)
					{
						clinfo[materialindex].siItemUnique	= materialunique;
						clinfo[materialindex].siStgPos		= siitemindex;
						clinfo[materialindex].siUseItemNum	=materialnum;						
						k =  (NOW_ENCHANT_NUMBER+1);
						bmaterialfinddswitch = true;
						if(clinfo[materialindex].siUseItemNum > pclmaterialinv->clItem[siitemindex].siItemNum)
							bitemenchant= false;

						materialindex++;

					}
				}
			}
			// ������ ������������ �������� ã�� ���ߴٸ�
			if(bmaterialfinddswitch == false)
			{
				bitemenchant= false;
			}
		}

		siitemindex = 0;
		siitemindex = pclCM->CR[GetCharUnique()]->siOrgInvEnchantInx;

		if(bitemenchant==false)
		{
			//��ᰡ ����.
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_NOMATENCHANTITEMFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);


			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();
			return false;

		}

		if( materialunique1.siElementUnique[0]==0)
		{
			//����� 10����̹Ƿ� �� �̻� ���׷��̵带 �� �ʿ䰡 ����.
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_LASTENCHANTITEMFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();
			return false;
		}




		//------------------------------------------
		// ���� ������ �غ��Ѵ�. 
		//------------------------------------------
		cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;


		cltItem clOutputItem;		
		SI16 brareswitch = 0;

		//----------------------------------------------
		// �κ��� �������� ���� ������ �ִ��� Ȯ���Ѵ�. 
		//----------------------------------------------
		// �ش� �κ��� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
		SI16 sitopos;

		// ������� �����. 
		MakeHunger();

		clOutputItem.Set(&pclmaterialinv->clItem[OrgInx]);
		sitopos = pclCM->CR[GetCharUnique()]->siOrgInvEnchantInx;
		//pclmaterialinv->clItem[OrgInx].Element.siPower = materialunique1.siItemGrade;		

		//��� ���� 


		SI32 siItemType = pclitemmanager->GetItemType(clOutputItem.siUnique);
		SI32 simakeflag=true;

		SI32 tempUnique = materialcharunique;
		materialcharunique = GetCharUnique();

		if(clOutputItem.Element.siType!=0)
		{
			pclCM->CR[materialcharunique]->siElementType = clOutputItem.Element.siType;
		}

		switch(siItemType)
		{
		case ITEMTYPE_SWORD:	
			{
				SI32 skillunique  = SKILL_MAKESWORD1;
#ifdef _SAFE_MEMORY
				SI32 level  = pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  = pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;

			}
			break;
		case ITEMTYPE_SPEAR:
			{
				SI32 skillunique  = SKILL_MAKESPEAR1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;

			}
			break;
		case ITEMTYPE_STAFF:			
			{
				SI32 skillunique  = SKILL_MAKESTAFF1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;

			}
			break;
		case ITEMTYPE_AXE:			
			{
				SI32 skillunique  = SKILL_MAKEAXE1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;

			}
			break;
		case ITEMTYPE_BOW:			
			{
				SI32 skillunique  = SKILL_MAKEBOW1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;

			}
			break;
		case ITEMTYPE_GUN:
			{
				SI32 skillunique  = SKILL_MAKEGUN1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;


			}
			break;		
		case ITEMTYPE_ARMOUR:
			{
				SI32 skillunique  = SKILL_MAKEARMOUR1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;


			}
			break;	
		case ITEMTYPE_DRESS:
			{
				SI32 skillunique  = SKILL_MAKEDRESS1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;

			}
			break;
		case ITEMTYPE_BELT:
			{
				SI32 skillunique  = SKILL_MAKEBELT1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;

			}
			break;
		case ITEMTYPE_SHOES:
			{
				SI32 skillunique  = SKILL_MAKESHOES1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;

			}
			break;
		case ITEMTYPE_HELMET:
			{
				SI32 skillunique  = SKILL_MAKEHELMET1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}
			break;
		case ITEMTYPE_HAT:
			{
				SI32 skillunique  = SKILL_MAKEHAT1;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;


			// �ֹ��� �ٰŷ� �ƹ�Ÿ �������� �����.

			// �ƹ�Ÿ ����
		case ITEMTYPE_AVATAR_MANTLE:
			{
				SI32 skillunique  = SKILL_MAKEAVATAR_MANTLE;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}
			break;

			// �ƹ�Ÿ ����
		case ITEMTYPE_AVATAR_HAT:
			{
				SI32 skillunique  = SKILL_MAKEAVATAR_HAT;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;

			// �ƹ�Ÿ �Ǻ�
		case ITEMTYPE_AVATAR_DRESS:
			{
				SI32 skillunique  = SKILL_MAKEAVATAR_DRESS;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;

			// �ƹ�Ÿ �����
		case ITEMTYPE_AVATAR_NECK:
			{
				SI32 skillunique  = SKILL_MAKEAVATAR_NECK;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;

			// �ƹ�Ÿ ����
		case ITEMTYPE_AVATAR_RING:
			{
				SI32 skillunique  = SKILL_MAKEAVATAR_RING;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;

		case ITEMTYPE_CRYSTAL:// ��Ƽ��Ʈ ���� ���� ����
			{
				SI32 skillunique  = SKILL_ARTIFACT;
#ifdef _SAFE_MEMORY
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  &pclCI->clCharItem.clItem[0] , 1);
#else
				SI32 level  =pclClient->pclCM->CR[materialcharunique]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0,  pclCI->clCharItem.clItem , 1);
#endif
				SI32 MaxLevel = materialunique1.siNeedSkill;
				if(level < MaxLevel) simakeflag = false;
				pclCM->CR[materialcharunique]->siElementType = pclCM->CR[materialcharunique]->siElementType  + 1;
			}			
			break;
		}

		//��ų ����
		if(simakeflag ==false)
		{
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_NOSKILLENCHANTFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();
			return false;

		}

		materialcharunique = tempUnique;

		if(clOutputItem. Element.siPower < 1 )
		{
			clOutputItem.Element.siType = pclCM->CR[materialcharunique]->siElementType;
		}	

		if(clOutputItem.Element.siType < 0 ) //return false;
			simakeflag = false;


		SI32 sitemp = TABS(pclClient->CurrentClock  + rand()) % 1000 ;
		if( sitemp  < (SI32)(materialunique1.EnchantRate * 1000 ))
		{
			simakeflag = ENCHANT_SUCCESS;
		}
		else if( sitemp < (SI32)((materialunique1.EnchantRate + materialunique1.EnchantDownRate) * 1000 ))
		{
			simakeflag = ENCHANT_DOWNGRADE;
		}
		else if( sitemp < (SI32)((materialunique1.EnchantRate + materialunique1.EnchantDownRate + materialunique1.EnchantFailRate) * 1000 ))
		{
			simakeflag = ENCHANT_BROKEN;
		}	
		else
		{
			simakeflag = ENCHANT_FAIL;
		}


		bool bmoneyflag = true;

		cltItemPriceUnit* fee = pclitemmanager->GetCurrentPrice(clOutputItem.siUnique);

		sifee = (SI64)(fee->siPrice * 0.05 ) ;
		if(personid == materialpersonid)
			sifee = 0;


		GMONEY mymoney = pclCM->CR[materialcharunique]->pclCI->clIP.GetMoney();
		if(mymoney < sifee) bmoneyflag = false;
		//������ ����
		if(bmoneyflag ==false)
		{
			cltGameMsgResponse_PersonItemInfo clinfo(-1, PERSONITEMINFO_OPTION_NOMONEYENCHANTFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clinfo1( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clinfo1), (BYTE*)&clinfo1);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();
			return false;
		}

		//-----------------------------------------------------
		//		  ��æƮ ���� ���и� ����������� �����.
		//-----------------------------------------------------
#if  MAKE_BY_MUNIN //2007-06-05
		SI32 siItemGrade = clOutputItem.Element.siPower;
		static DWORD dwLastEnchantStatisticClock = 0;
		static bool backUpEnchantDataLoaded = false;

		if((backUpEnchantDataLoaded == false) ||(pclClient->GetFrame() > 100 && TABS(pclClient->CurrentClock - dwLastEnchantStatisticClock) > ENCHANT_WRITE_TIME))
		{
			_SYSTEMTIME sysNowtime;
			GetLocalTime( &sysNowtime );

			dwLastEnchantStatisticClock = pclClient->CurrentClock;

			pclClient->pclItemManager->AddEnchantNum(clOutputItem.siUnique,siItemGrade, clinfo ,simakeflag );
			pclClient->pclItemManager->WriteEnchantStatisticAction(backUpEnchantDataLoaded,sysNowtime);

			if(backUpEnchantDataLoaded ==false)
			{
				pclClient->pclItemManager->AddEnchantNum(clOutputItem.siUnique,siItemGrade, clinfo ,simakeflag );
				backUpEnchantDataLoaded = true;
			}
		}
		else
		{
			pclClient->pclItemManager->AddEnchantNum(clOutputItem.siUnique,siItemGrade, clinfo ,simakeflag );
		}
#endif
		//��æƮ ���� 
		if( simakeflag != ENCHANT_SUCCESS )
		{

			cltGameMsgResponse_PersonItemInfo clPersonItemlinfo(-1, PERSONITEMINFO_OPTION_LASTENCHANTITEMFAIL, 0, 0, &orgitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clPersonItemlinfo), (BYTE*)&clPersonItemlinfo);
			SendNetMsg((sPacketHeader*)&clMsg);

			siPersonalMakeItemType = 0;

			cltGameMsgResponse_MakeItemSwitch clMakeIteminfo( 0 );
			cltMsg clMsg1(GAMEMSG_RESPONSE_MAKEITEMSWITCH, sizeof(clMakeIteminfo), (BYTE*)&clMakeIteminfo);
			SendNetMsg((sPacketHeader*)&clMsg1);

			//----------------------------------------------
			// �̿��鿡�Ե� �˸���. 
			//----------------------------------------------
			SendNeighbourMyMakeItemStatus();

			//���н� 

			if( simakeflag == ENCHANT_BROKEN )
			{
				clOutputItem.Init();	
			}

			else if(simakeflag == ENCHANT_DOWNGRADE )
			{

				--clOutputItem.Element.siPower ;

				// �ٿ� �׷��̵�� �������� ����� 0 ���� ���ų� ���ٸ� �Ӽ��� �ʱ�ȭ���ش�.
				if( clOutputItem.Element.siPower <= 0 )
				{
					clOutputItem.Element.siType = 0;
				}

			}
		}
		else
		{
			clOutputItem.Element.siPower = materialunique1.siItemGrade;
		}

		cltServer * pclserver = (cltServer*)pclClient;

		sDBRequest_EnchantItemInv clMsg(GetID(), simakeflag , personid, materialpersonid, clinfo, sitopos, &clOutputItem, sifee, clOutputItem.IsCreateSID(pclserver->pclItemManager) );		
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


		//------------------------------------------------------
		// �Ҹ�� ���Ḧ ��賽��. 
		//------------------------------------------------------
		for(SI32 i = 0;i < MAX_ENCHANT_NUMBER; i++)
		{
			if(clinfo[i].siItemUnique)
			{ 
				pclitemmanager->AddUseNum(clinfo[i].siItemUnique, clinfo[i].siUseItemNum);

				// ���ο� ��� - ������ ��� ��踦 ����.
				NStatistics_Add("Item", clinfo[i].siItemUnique, "UsedEnchantMtrl", clinfo[i].siUseItemNum);
				NStatistics_Set("Item", clinfo[i].siItemUnique, "Name", pclClient->pclItemManager->GetName(clinfo[i].siItemUnique));
			}
		}
	}
	// by LEEKH 2008-10-06 __try, __finally ����
	//	__finally
	{
		if( returnval > 0 )
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendServerResponseMsg(0, returnval,  para1, para2, GetCharUnique());
			siMonsterCorp = 0 ;
			dwStartMiniGameTime = 0;
		}

	}

	return true;
}

// ���� �����Ѵ�.
bool cltCharServer::SetReserverMakeItem(DWORD productclock, cltGameMsgRequest_MakeItemInv* pclinfo)
{
	bMakeItemReserveSwitch = true;
	dwMakeItemStartClock	= pclClient->CurrentClock;
	dwMakeItemDelayClock	= productclock;

	pclReservedMakeItemData->Set(pclinfo);

	return true;
}


// ���� ���� ��ǰ��  �������� ���ҽ�Ų��. 
/*void cltCharServer::DecreaseSkillItemEquipDur(SI32 skillunique, bool bluckdemand)
{
	if( IsPC(GetCharUnique()) == false)return ;

	cltServer* pclserver = (cltServer*)pclClient;

	SI32 itempos = 0;
	for(SI32 i = 0;i < 5;i++)
	{
		if(i == 0)
		{
			itempos = PERSONITEM_HAT;
		}
		if(i == 1)
		{
			itempos = PERSONITEM_HELMET;
		}
		if(i == 2)
		{
			itempos = PERSONITEM_ARMOUR;
		}
		if(i == 3)
		{
			itempos = PERSONITEM_DRESS;
		}
		if(i == 4)
		{
			itempos = PERSONITEM_NECK;
		}

		cltItem* pclitem = &pclCI->clCharItem.clItem[itempos];
		if(pclitem->siUnique <= 0)continue;

		// Ư�� ����� �䱸�Ǵ� ���, �� ����� ���� ���� �����Ѵ�. 
		bool bskillswitch = false; 
		if(skillunique && pclitem->GetUpgradeSkillLevel(pclClient->pclItemManager, skillunique))
		{
			bskillswitch = true;
		}

		// ����� ���� ���� �����Ѵ�. 
		bool bluckswitch = true;
		//cyj �������

		bool bsuccess = false;
		// ����� �䱸�Ǵ� ��Ȳ���� ����� �����Ѵ�.
		if(skillunique)
		{
			if(bskillswitch == true)bsuccess = true;
		}
		// ���� �䱸�Ǵ� ��Ȳ���� ���� �����Ѵ�. 
		if(bluckdemand)
		{
			if(bluckswitch == true)bsuccess = true;
		}

		if(bsuccess == false)continue ;

		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
		if(ref <= 0)	return;

		SI32 decdur = pclClient->pclItemManager->pclItemInfo[ref]->siDecDur;			// ���ҽ�ų ������. 

		// �ڰ��� ���� �ʴ� ������ ���� 3���� ������ ����. 
		SI32 returnval = 0;
		if(CheckEquipCondition(pclClient->pclItemManager, itempos, pclitem, &returnval) == false)
		{
			decdur = 3;
		}

		pclitem->DecreaseDurability(pclserver->pclItemManager, decdur);
		SetWasteDurUpdateSwitch(itempos, true);		// ���� �������� ����Ǿ����� ���� 

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		SI32 option = 0;
		if(pclitem->siUnique)			{	option = PERSONITEMINFO_OPTION_NONE;	}
		else							{	option = PERSONITEMINFO_OPTION_WASTE;	}
		cltGameMsgResponse_PersonItemInfo clinfo(itempos, option, 0, 0, pclitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);

	}

}*/

void cltCharServer::DecreaseSkillItemEquipDur( SI32 skillunique )
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	if( IsPC(GetCharUnique()) == false)return ;
	cltServer* pclserver = (cltServer*)pclClient;

	if( skillunique <= 0 )																	return;
	for(SI32 i = 0;i < PERSONITEM_INV0;i++)
	{
		cltItem* pclitem = &pclCI->clCharItem.clItem[ i ];
		if( pclitem || pclitem->siUnique <= 0 )												continue;
		if( pclitem->GetUpgradeSkillLevel(pclClient->pclItemManager, skillunique) <= 0 )	continue;

		SI32 decdur = 1;

		pclitem->DecreaseDurability(pclserver->pclItemManager, decdur);
		SetWasteDurUpdateSwitch(i, true);		// ���� �������� ����Ǿ����� ���� 

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(i, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltCharServer::DecreaseEquipDurFromDead(  )
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	if( IsPC(GetCharUnique()) == false && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )return ;

	SI32 i = 0;
	// ItemPos, Percent
	cltUniqueRange MaxCount[] =
	{
		1,  70, 
			2,	25,
			3,	5 
	};
	SI32 MaxCount_Count = sizeof(MaxCount) / sizeof(cltUniqueRange);
	SI32 siSeletedMaxCount = GetUniqueWithRange(MaxCount, MaxCount_Count, 100);
	if( siSeletedMaxCount <= 0 )									return;
	if( siSeletedMaxCount > PERSONITEM_INV0 )						return;

	// ������ 20���δ�
	SI32 decdur = 20;
	SI32 ItemPos[PERSONITEM_INV0] = { -1, };

	SI32 siMaxCharEquipCount = 0;
	for( i=0; i< PERSONITEM_INV0; i++ )
	{
		bool	bHaveEquip = false;
		if( i == PERSONITEM_BAG || i == PERSONITEM_BAG_SUB )								continue;
		if( (i == PERSONITEM_WEAPON1 || i == PERSONITEM_WEAPON2) && (i != ActiveWeapon) )	continue;

		if( GetSummonParentID() )
		{
			SI32 siCharID = GetSummonParentID();
			cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siCharID );
			if( pclchar )
			{
				SI32 siSummonIndex = GetSummonIndex();
				cltItem* pclitem = pclchar->pclCI->clSummonInfo.GetSummonEquipItem( GetSummonIndex(), i );
				if( pclitem && pclitem->siUnique > 0 )				bHaveEquip = true;
			}
		}
		else
		{
			if( pclCI->clCharItem.clItem[i].siUnique > 0 )		bHaveEquip = true;
		}

		if( bHaveEquip )
		{
			ItemPos[siMaxCharEquipCount] = i;
			siMaxCharEquipCount++;
		}
	}
	if( siSeletedMaxCount > siMaxCharEquipCount )		siSeletedMaxCount = siMaxCharEquipCount;

	SI32 Count = siMaxCharEquipCount;

	for( i=0 ; i< siSeletedMaxCount; i++ )
	{
		SI32 siSelItemPos = rand() % Count;

		if( GetSummonParentID() )
		{	
			SI32 siCharID = GetSummonParentID();
			cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siCharID );
			if(pclchar)
			{
				pclchar->DecreaseSummonEquipDur( GetSummonIndex(), ItemPos[siSelItemPos], decdur );	
			}
		}
		else
		{	
			DecreaseEquipDur(ItemPos[siSelItemPos], decdur);	

			if ( (PERSONITEM_WEAPON1 == ItemPos[siSelItemPos]) || (PERSONITEM_WEAPON2 == ItemPos[siSelItemPos]) )
			{
				UseItemReasonDurabilityZero( ItemPos[siSelItemPos] );
			}
		}

		if( Count > 0 )	{	ItemPos[siSelItemPos] = ItemPos[Count-1];	}
		Count--;

		if( Count <= 0 )			break;
	}
}

void cltCharServer::DecreaseWeaponDur( SI32 siEnemyID )
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	if( IsPC(GetCharUnique()) == false && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )return ;

	cltCharServer* pclEnemychar = pclClient->pclCM->GetCharServer( siEnemyID );
	if( pclEnemychar == NULL )			return;

#ifdef _DEBUG
	static SI32 siTotal = 0, siSucc = 0;
	siTotal++;
#endif

	// 50% percent
	SI32 siRand = rand() % 1000;
	if( siRand > 50 )		return;

#ifdef _DEBUG
	siSucc++;
	NTCHARString64 kMsg;
	kMsg += "Total[";
	kMsg += SI32ToString(siTotal);
	kMsg += "] Succ[";
	kMsg += SI32ToString(siSucc);
	kMsg += "] Percent[";
	REAL32 fPercent = (REAL32)siSucc * 100.0f / (REAL32)siTotal;
	kMsg += REAL32ToString(fPercent);
	kMsg += "]\n";
	OutputDebugString( kMsg );
#endif

	//SI32 decdur = 2;
	SI32 siConstA	= (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Weapon_ConstA" );
	SI32 siConstB	= (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Weapon_ConstB" );
	SI32 siWasteMin = (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Weapon_Min" );
	SI32 siWasteMax = (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Weapon_Max" );

	if ( 0 >= siConstB )
	{
#ifdef _DEBUG
		MessageBox(NULL, TEXT("GV_Waste_Dur_Armour_ConstB value is Zero"), TEXT("Wrong Value"), MB_OK|MB_TOPMOST);
#endif
		return;
	}

	SI16 siAttackerLevel = pclCI->clIP.GetLevel();
	SI16 siDefenderLevel = pclEnemychar->pclCI->clIP.GetLevel();
	SI32 decdur = siConstA + ( max(0, (siDefenderLevel - siAttackerLevel) / siConstB) );
	decdur = max( decdur, siWasteMin );
	decdur = min( decdur, siWasteMax );

	if( GetSummonParentID() )
	{
		SI32 siCharID = GetSummonParentID();
		cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siCharID );
		if(pclchar)
		{
			siSummonIndex = GetSummonIndex();
			pclchar->DecreaseSummonEquipDur( siSummonIndex, ActiveWeapon, decdur );
		}
	}
	else
	{
		DecreaseEquipDur(ActiveWeapon, decdur);

		UseItemReasonDurabilityZero( ActiveWeapon );
	}
}

void cltCharServer::DecreaseSummonEquipDur(SI32 siSummonIndex, SI32 itempos, SI32 durwaste)
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	if(siSummonIndex < 0 || siSummonIndex >= MAX_SUMMON_OWN )		return;
	if(itempos < 0 || itempos >= MAX_SHAPE_ITEM)					return;
	if(durwaste < 0)												return;

	cltItem* pclitem = pclCI->clSummonInfo.GetSummonEquipItem( siSummonIndex, itempos );
	if( pclitem == NULL || pclitem->siUnique <= 0 )					return;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if( ref >0 )	{	durwaste += pclClient->pclItemManager->pclItemInfo[ref]->siDecDur;			}	

	SI32 decdur = durwaste;
	pclitem->DecreaseDurability(pclClient->pclItemManager, decdur);
	SetSummonWasteDurUpdateSwitch(siSummonIndex, itempos, true);

	cltGameMsgResponse_SummonChangeItem clSummonChangItem( siSummonIndex, itempos, pclitem );
	cltMsg clSummonMsg( GAMEMSG_RESPONSE_SUMMONCHANGEITEM, sizeof(clSummonChangItem), (BYTE*)&clSummonChangItem );
	SendNetMsg( (sPacketHeader*)&clSummonMsg );
}

void cltCharServer::DecreaseArmourDur( SI32 siEnemyID )
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	// ����ڵ� �ƴϰ� ��ȯ���� �ƴϸ�, ����. 
	if( IsPC(GetCharUnique()) == false && clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )return ;

	cltCharServer* pclEnemychar = pclClient->pclCM->GetCharServer( siEnemyID );
	if( pclEnemychar == NULL )			return;

	// 20%
	SI32 siRand = rand() % 1000;
	if( siRand > 200 )										return;

	// ItemPos, Percent
	cltUniqueRange ItemPos[] =
	{
		PERSONITEM_HELMET,  16, 
			PERSONITEM_HAT,		6, 
			PERSONITEM_ARMOUR,  16, 
			PERSONITEM_DRESS,	6, 
			PERSONITEM_BELT,	13,
			PERSONITEM_SHOES,	13, 
			PERSONITEM_MANTLE,	10,
			PERSONITEM_NECK,	6,
			PERSONITEM_RING1,	7,
			PERSONITEM_RING2,	7,
	};
	SI32 ItemPos_Count = sizeof(ItemPos) / sizeof(cltUniqueRange);
	SI32 siSeletedItemPos = GetUniqueWithRange(ItemPos, ItemPos_Count, 100);

	//	SI32 decdur = 2;
	SI32 siConstA	= (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Armour_ConstA" );
	SI32 siConstB	= (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Armour_ConstB" );
	SI32 siWasteMin = (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Armour_Min" );
	SI32 siWasteMax = (SI32)pclClient->GetGlobalValue( "GV_Waste_Dur_Armour_Max" );

	if ( 0 >= siConstB )
	{
#ifdef _DEBUG
		MessageBox(NULL, TEXT("GV_Waste_Dur_Armour_ConstB value is Zero"), TEXT("Wrong Value"), MB_OK|MB_TOPMOST);
#endif
		return;
	}

	SI16 siAttackerLevel = pclEnemychar->pclCI->clIP.GetLevel();
	SI16 siDefenderLevel = pclCI->clIP.GetLevel();
	SI32 decdur = siConstA + ( max(0, (siAttackerLevel - siDefenderLevel) / siConstB) );
	decdur = max( decdur, siWasteMin );
	decdur = min( decdur, siWasteMax );

	if( GetSummonParentID() )
	{
		SI32 siCharID = GetSummonParentID();
		cltCharServer* pclchar = pclClient->pclCM->GetCharServer( siCharID );
		if(pclchar)
		{
			siSummonIndex = GetSummonIndex();
			pclchar->DecreaseSummonEquipDur( siSummonIndex, siSeletedItemPos, decdur );
		}
	}
	else
	{
		DecreaseEquipDur(siSeletedItemPos, decdur);
	}
}

void cltCharServer::DecreaseEquipDur(SI32 itempos, SI32 durwaste)
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )	return;
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)		return;
	if(durwaste < 0)										return;

	cltItem* pclitem = &pclCI->clCharItem.clItem[itempos];
	if( pclitem == NULL || pclitem->siUnique <= 0 )			return;

	SI32 returnval = 0;
	if(CheckEquipCondition(pclClient->pclItemManager, itempos, pclitem, &returnval) == false)	return;

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
	if( ref >0 )	{	durwaste += pclClient->pclItemManager->pclItemInfo[ref]->siDecDur;			}	

	SI32 decdur = durwaste;
	pclitem->DecreaseDurability(pclClient->pclItemManager, decdur);
	SetWasteDurUpdateSwitch(itempos, true);

	cltGameMsgResponse_PersonItemInfo clinfo(itempos, PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
	SendNetMsg((sPacketHeader*)&clMsg);
}

void cltCharServer::UseItemReasonDurabilityZero( SI32 siItemPos )
{
	if ( false == pclClient->IsCountrySwitch(Switch_NewDurability) )
	{
		return;
	}

	if ( (0 > siItemPos) || (MAX_ITEM_PER_PERSON <= siItemPos) )
	{
		return;
	}

	cltItem* pclitem = &pclCI->clCharItem.clItem[siItemPos];
	if ( (NULL == pclitem) || (0 >= pclitem->siUnique) )
	{
		return;
	}

	if ( 0 < pclitem->GetDurability() )
	{
		return;
	}

	// ������ 0�� ���� �ı��� �Ʒ� 4���� Ÿ�Ը� �����ϴ� �׿� Ÿ���� ������ ����
	switch ( pclitem->GetType(pclClient->pclItemManager) )
	{
	case ITEMTYPE_IRON:
	case ITEMTYPE_FISHINGROD:
	case ITEMTYPE_DISH:
	case ITEMTYPE_PAPER:
		{
		}
		break;

	default:
		{
			return;
		}
	}

	sDBRequest_UseItem useitem( GetCharID(), pclCI->GetPersonID(), siItemPos, pclitem, USEITEM_REASON_DURABILITY_ZERO );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&useitem);

}


// ������  �������� ���ҽ�Ų��. 
/*
void cltCharServer::DecreaseWeaponDur()
{
	// ����ڵ� �ƴϰ� ��ȯ���� �ƴϸ�, ����. 
	if( IsPC(GetCharUnique()) == false
		&& clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )return ;

	// �����ڰ� ������� ��� ������ �������� ����߸���. 
	// 5%�� Ȯ���� �������� ������. 
	if(rand() % 14)return ;

	cltItem* pclitem = NULL;
	SI32 parentid = GetSummonParentID();
	// ��ȯ���̸�, 

	cltCharServer* pclchar = NULL;

	SI32 decdur = 2;

	if(parentid)
	{
		SI32 siSummonIndex = GetSummonIndex();
		if ( (0 > siSummonIndex) || (MAX_SUMMON_OWN <= siSummonIndex) )
		{
#ifdef _DEBUG
			MsgBox(TEXT("��ȯ�� �ε��� ����"), TEXT("�߸��� ��ȯ�� �ε��� %d"), GetSummonIndex());
#endif
			return;
		}

		// ��� ĳ���͸� ���Ѵ�. 
		pclchar = (cltCharServer*)(pclCM->CR[parentid]);
		pclitem = pclchar->pclCI->clSummonInfo.GetSummonItem( siSummonIndex, ActiveWeapon );
	}
	else
	{
		// ��� ĳ���͸� ���Ѵ�. 
		pclchar = this;
		pclitem = &pclchar->pclCI->clCharItem.clItem[ActiveWeapon];
	}



	if ( (NULL == pclitem) || (pclitem->siUnique <= 0) )
	{
		return ;
	}

	//pclchar->DecreaseEquipDur(ActiveWeapon, decdur);

}
*/
// �� ����� �������� ���ҽ�Ų��. 
/*
void cltCharServer::DecreaseEquipDur(SI32 itempos, SI32 durwaste)
{
	if(itempos < 0 || itempos >= MAX_ITEM_PER_PERSON)		return;

	cltServer* pclserver = (cltServer*)pclClient;

	cltItem* pclitem = &pclCI->clCharItem.clItem[itempos];
	if(pclitem->siUnique)
	{
		SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclitem->siUnique);
		if(ref >0)
		{
			durwaste += pclClient->pclItemManager->pclItemInfo[ref]->siDecDur;				// ���� ���� ������ ���Ұ� Ŀ���� ���� �ִ�. 
		}

		SI32 decdur = durwaste;

		// �ڰ��� ���� �ʴ� ����� ���� 3���� ������ ����. 
		SI32 returnval = 0;
		if(CheckEquipCondition(pclClient->pclItemManager, itempos, pclitem, &returnval) == false)
		{
			decdur *= 3;
		}
		pclitem->DecreaseDurability(pclserver->pclItemManager, decdur);
		SetWasteDurUpdateSwitch(itempos, true);		// ���� �������� ����Ǿ����� ���� 

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		SI32 option = 0;
		if(pclitem->siUnique)			{	option = PERSONITEMINFO_OPTION_NONE;	}
		else							{	option = PERSONITEMINFO_OPTION_WASTE;	}
		cltGameMsgResponse_PersonItemInfo clinfo(itempos, option, 0, 0, pclitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		SendNetMsg((sPacketHeader*)&clMsg);

	}

}
*/
// �汸�� �������� ���ҽ�Ų��. 
/*
void cltCharServer::DecreaseArmourDur()
{
	// ����ڵ� �ƴϰ� ��ȯ���� �ƴϸ�, ����. 
	if( IsPC(GetCharUnique()) == false
		&& clIdentity.siIdentity != IDENTITY_PERSON_SUMMON )return ;

	if(rand() % 3 )return ;

	SI32 randpos[] = {	PERSONITEM_ARMOUR,  4, 
		PERSONITEM_DRESS,	4, 
		PERSONITEM_HELMET,  4, 
		PERSONITEM_HAT,		4, 
		PERSONITEM_SHOES,	8, 
		PERSONITEM_BELT,	4,
		PERSONITEM_RING1,	8,
		PERSONITEM_RING2,	8,
		PERSONITEM_NECK,	4,
		PERSONITEM_MANTLE,	4,
		PERSONITEM_BAG,		4};	

	SI32 tempindex	= (rand() % 11);
	SI32 itempos	= randpos[ tempindex * 2];
	SI32 durwaste	= (rand() % randpos[tempindex * 2 + 1] ) ;

	cltItem* pclitem = NULL;
	SI32 parentid = GetSummonParentID();

	SI32 index = 0;
	cltCharServer* pclchar = NULL;

	// ��ȯ���̸�, 
	if(parentid)
	{
		// ��� ĳ���͸� ���Ѵ�. 
		pclchar = (cltCharServer*)(pclCM->CR[parentid]);

		switch(GetSummonIndex())
		{
		case 0:	index = PERSONITEM_SUMMON1EQUIP0;	break;
		case 1:	index = PERSONITEM_SUMMON2EQUIP0;	break;
		default:
			MsgBox(TEXT("v222dd83jf"), TEXT("vdfe83:%d"), GetSummonIndex());
			return ;
		}

		//durwaste *= 1.3 ;
	}
	else
	{
		// ��� ĳ���͸� ���Ѵ�. 
		pclchar = this;
	}


	// �� ��ġ�� �������� ���ҽ�Ų��. 
	//pclchar->DecreaseEquipDur(index + itempos, durwaste);

}
*/
// InputItem�� ����� �ڸ��� �����Ѵ�. 
void cltCharServer::InputItemReserveAction()
{
	SI32 i;

	for(i = 0;i < MAX_ITEM_PER_PERSON;i++)
	{
		if(clSimpleVary.dwItemInputReserveClock[i] == 0)continue;
		if(TABS(pclClient->CurrentClock - clSimpleVary.dwItemInputReserveClock[i]) > 10000)
		{
			clSimpleVary.dwItemInputReserveClock[i] = 0;
		}
	}
}
bool cltCharServer::CheckItemForEmptyAnyItemSlotByHiddenQuesst(SI32 invmode, cltItem* pclitem,cltItem* pclitem2)
{
	bool	ret		= false	;
	bool	ret2	= false	;

	bool	LastRetuenValue	= false	;

	cltItem clToItem;
	clToItem.Init();
	SI16 InvPos = -1;
	SI32 rtnvalue;

	cltItem clToItem2	;
	clToItem2.Init()	;
	SI16 InvPos2 = -1	;
	SI32 rtnvalue2		;
	// ��ø�ɼ� �ִ��� �κ��丮�� Ȯ���� ����.
	ret = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_ALL, pclitem, &clSimpleVary.dwItemInputReserveClock[0], &InvPos, &clToItem, &rtnvalue);
	ret2 = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_ALL, pclitem2, &clSimpleVary.dwItemInputReserveClock[0], &InvPos2, &clToItem2, &rtnvalue2);
	// ��ø�ɼ� �ִ� ������ ������ ������� 2���� �־�� �Ѵ�.
	if ( ret == false && ret2 ==false )
	{
		if (IsBlankInv(2,INVMODE_ALL))	
		{
			LastRetuenValue = true;
		}
	}
	// ���� �ϳ��� ��ø�ɼ� �ִٸ� ������� 1���� ������ �ȴ�.
	if ( ret == false && ret2 ==true )
	{
		SI32 siItempos = pclCI->clCharItem.FindItemInv(pclitem2->siUnique)	;
		if ( siItempos > 0 )// ��ĥ�� �ִ� �������� ������ 
		{
			if( IsBlankInv(	1,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}
		}
		else
		{
			if( IsBlankInv(	2,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}
		}
	}
	else if ( ret == true && ret2 ==false )
	{
		SI32 siItempos = pclCI->clCharItem.FindItemInv(pclitem->siUnique)	;
		if ( siItempos > 0 )// ��ĥ�� �ִ� �������� ������ 
		{
			if( IsBlankInv(	1,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}
		}
		else
		{
			if( IsBlankInv(	2,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}
		}
	}
	else if( ret == true && ret2 ==true )
	{
		// �Ѵ� ��ø ���� �ϸ� �����۵��� �ִ� �� �κ����� Ȯ�� �Ѵ�.
		SI32 siItempos1 = pclCI->clCharItem.FindItemInv(pclitem->siUnique)	;
		SI32 siItempos2 = pclCI->clCharItem.FindItemInv(pclitem2->siUnique)	;
		if ( siItempos1  < 0 && siItempos2 > 0 ) 
		{
			if( IsBlankInv(	1,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}

		}
		else if ( siItempos1  > 0 && siItempos2 < 0 ) 
		{
			if( IsBlankInv(	1,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}

		}
		else if ( siItempos1  < 0 && siItempos2 < 0 ) 
		{
			if( IsBlankInv(	2,INVMODE_ALL )	)
			{
				LastRetuenValue = true;
			}
		}
		else
		{
			LastRetuenValue = true;
		}
	}
	return LastRetuenValue ;
}
bool cltCharServer::CanAddInv(SI32 invmode, cltItem* pclitem, SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue)
{
	// ALL����̸� ��ü�� �ϳ� �ϳ� üũ�Ѵ�.
	if(invmode == INVMODE_ALL)
	{
		bool	ret;

		// ��ü ��ø üũ �� ĳ���� �κ��� ���ο� ��ġ �˻�
		ret = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_ALL, pclitem, &clSimpleVary.dwItemInputReserveClock[0], pitempos, pcltoitem, prtnvalue);
		if(ret)			return ret;
		// �� �κ��丮 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(HaveHorse() == true)
		{
			ret = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_HORSE, pclitem, &clSimpleVary.dwItemInputReserveClock[0], pitempos, pcltoitem, prtnvalue);
			if(ret)			return ret;
		}
		// ����1 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique > 0)
		{
			ret = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG, pclitem, &clSimpleVary.dwItemInputReserveClock[0], pitempos, pcltoitem, prtnvalue);
			if(ret)			return ret;
		}
		// ����2 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique > 0)
		{
			ret = pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, INVMODE_BAG_SUB, pclitem, &clSimpleVary.dwItemInputReserveClock[0], pitempos, pcltoitem, prtnvalue);
			if(ret)			return ret;
		}

		// INVMODE_ALL ���� ���⼭ ������.
		return ret;
	}

	return pclCI->clCharItem.CanAddInv(pclClient->pclItemManager, invmode, pclitem, &clSimpleVary.dwItemInputReserveClock[0], pitempos, pcltoitem, prtnvalue);
}

bool cltCharServer::IsBlankInv(SI32 invnum,SI32 invmode)
{
	// ALL����̸� ��ü�� �ϳ� �ϳ� üũ�Ѵ�.
	if(invmode == INVMODE_ALL)
	{
		bool	ret;

		// ��� �κ��丮 �˻�
		ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_PERSON);
		if(ret)			return ret;
		// �� �κ��丮 �˻�
		if(HaveHorse() == true)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_HORSE);
			if(ret)			return ret;
		}
		// ����1 �κ��丮 �˻�
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique > 0)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_BAG);
			if(ret)			return ret;
		}
		// ����2 �κ��丮 �˻�
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique > 0)
		{
			ret = pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager, invnum, INVMODE_BAG_SUB);
			if(ret)			return ret;
		}

		// INVMODE_ALL ���� ���⼭ ������.
		return ret;
	}

	return pclCI->clCharItem.IsBlankInv(pclClient->pclItemManager,invnum,invmode);
}

bool cltCharServer::CanAddInvManyItems(SI32 invmode, cltItem* pclitem, SI32* prtnvalue)
{
	// ALL����̸� ��ü�� �ϳ� �ϳ� üũ�Ѵ�.
	if(invmode == INVMODE_ALL)
	{
		bool	ret;

		// ��ü ��ø üũ �� ĳ���� �κ��� ���ο� ��ġ �˻�
		ret = pclCI->clCharItem.CanAddInvManyItems(pclClient->pclItemManager, INVMODE_ALL, pclitem, &clSimpleVary.dwItemInputReserveClock[0], prtnvalue);
		if(ret)			return ret;
		// �� �κ��丮 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(HaveHorse() == true)
		{
			ret = pclCI->clCharItem.CanAddInvManyItems(pclClient->pclItemManager, INVMODE_HORSE, pclitem, &clSimpleVary.dwItemInputReserveClock[0], prtnvalue);
			if(ret)			return ret;
		}
		// ����1 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG].siUnique > 0)
		{
			ret = pclCI->clCharItem.CanAddInvManyItems(pclClient->pclItemManager, INVMODE_BAG, pclitem, &clSimpleVary.dwItemInputReserveClock[0], prtnvalue);
			if(ret)			return ret;
		}
		// ����2 ���ο� ��ġ �˻� (��ø��ġ�� ������ �˻��Ǿ���.)
		if(pclCI->clCharItem.clItem[PERSONITEM_BAG_SUB].siUnique > 0)
		{
			ret = pclCI->clCharItem.CanAddInvManyItems(pclClient->pclItemManager, INVMODE_BAG_SUB, pclitem, &clSimpleVary.dwItemInputReserveClock[0], prtnvalue);
			if(ret)			return ret;
		}

		// INVMODE_ALL ���� ���⼭ ������.
		return ret;
	}
	return pclCI->clCharItem.CanAddInvManyItems(pclClient->pclItemManager, invmode, pclitem, &clSimpleVary.dwItemInputReserveClock[0], prtnvalue);
}


void cltCharServer::SetRoulette(bool bcheck)
{
	if( bcheck)
	{
		bRouletteStart = true;
		dwRouletteStartClock = pclClient->CurrentClock;
		dwRouletteDelayClock = 30000;
	}
	else
	{
		bRouletteStart = false;
		m_siBettingCount = 0;
		m_siResultCount = 0;
		dwRouletteStartClock = 0;
		dwRouletteDelayClock = 0;

		SI32 x = 0, y = 0;
		for( y = 0 ; y< 5; ++y )
		{
			m_siRandomValue[y] = 0;	// ���õ� ������ 0

			for( x = 0; x < 5; ++x )
			{
				m_stRouletteTable[y][x].m_bUserSelect = false;
				m_stRouletteTable[y][x].m_bCpuSelect  = false;
				m_stRouletteTable[y][x].m_bResult     = false;

				m_stRouletteTable[y][x].m_siX = 0;
				m_stRouletteTable[y][x].m_siY = 0;
				m_stRouletteTable[y][x].m_siValue = y*5 + (x + 1);
			}
		}
	}
}

void cltCharServer::CheckRoulette()
{
	SI32 x = 0, y = 0;
	for( y = 0 ; y< 5; ++y )
	{
		for( x = 0; x < 5; ++x )
		{
			if( m_stRouletteTable[y][x].m_bUserSelect == true && m_stRouletteTable[y][x].m_bCpuSelect)
			{
				m_stRouletteTable[y][x].m_bResult = true;
				m_siResultCount++;
			}
		}
	}
}

bool cltCharServer::CheckLottoRoulette()
{
	SI32 x = 0, y = 0;
	bool bResult = false;

	// ���� üũ���ְ�
	for( y = 0 ; y< 5; ++y )
	{
		if( m_stRouletteTable[y][0].m_bResult != true )
			continue;

		for( x = 1; x < 5; ++x )
		{
			if( m_stRouletteTable[y][x].m_bResult != true )
			{
				bResult = false;
				break;
			}

			bResult = true;
		}
	}
	// ���� äũ���ְ�
	for( x = 0 ; x< 5; ++x )
	{
		if( m_stRouletteTable[0][x].m_bResult != true )
			continue;

		for( y = 1; y < 5; ++y )
		{
			if( m_stRouletteTable[y][x].m_bResult != true )
			{
				bResult = false;
				break;
			}

			bResult = true;
		}
	}
	// �밢�� ����
	for( y = 0; y < 5; ++y )
	{
		if( m_stRouletteTable[y][y].m_bResult != true )
		{
			bResult = false;
			break;
		}
		bResult = true;
	}
	for( y = 4; y >= 0; --y )
	{
		if( m_stRouletteTable[y][y].m_bResult != true )
		{
			bResult = false;
			break;
		}
		bResult = true;
	}

	return bResult;
}

void cltCharServer::SetInputItemReserve(SI32 itempos, DWORD data)
{
	if( itempos < 0 || itempos >= MAX_ITEM_PER_PERSON )			return;

	clSimpleVary.dwItemInputReserveClock[itempos] = data;
}

SI32 cltCharServer::GetMakeItemNum(SI32 needskillunique, SI32 needskilllevel, SI32 makeitemunique, SI32 makeitemnum)
{
	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);
	SI64 atb = pclClient->pclItemManager->GetItemAtb(makeitemunique);

	cltItemPriceUnit* pclprice = pclClient->pclItemManager->GetCurrentPrice(makeitemunique); 

	if (ref > 0)
	{
		// ���� ���� Ȯ���� ���Ѵ�. 
		if(needskillunique > 0 && needskilllevel)
		{
#ifdef _SAFE_MEMORY
			SI32 skilllevel	= pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, &pclCI->clCharItem.clItem[0]);
#else
			SI32 skilllevel	= pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, pclCI->clCharItem.clItem);
#endif
			float makepbt	= pclClient->pclItemManager->pclItemInfo[ref]->GetTotalMakePbt(skilllevel);
			SI32  simakepbt	= (SI32)(makepbt * 10);
			SI32  makenum	= 0;

			if(simakepbt >= 1000)
			{

				// obj �������� �ƴϸ� ���� ���ɼ��� �������� �� ���� ������ ���������.  
				if((atb & ITEMATB_OBJECT) == 0)
				{
					makeitemnum = (makeitemnum * simakepbt) / 1000;
				}

			}
			else
			{
				for(SI32 i = 0;i < makeitemnum;i++)
				{
					if(rand() % 1000 <= simakepbt)
					{
						makenum++;
					}
				}

				makeitemnum	= makenum;
			}
		}

	}
	else
		makeitemnum = 0;

	return makeitemnum;
}


SI32 cltCharServer::GetMakeCrystalItemNum(SI32 needskillunique, SI32 needskilllevel, SI32 makeitemunique, SI32 makeitemnum)
{
	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(makeitemunique);

	if (ref > 0)
	{
		// ���� ���� Ȯ���� ���Ѵ�. 
		if(needskillunique > 0 && needskilllevel)
		{
#ifdef _SAFE_MEMORY
			SI32 skilllevel	= pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, &pclCI->clCharItem.clItem[0]);
#else
			SI32 skilllevel	= pclCI->clCharSkill.GetTotalSkillLevel(needskillunique, 0, 0, pclCI->clCharItem.clItem);
#endif
			SI32 temMinnum = 0;
			SI32 temnum = 0;
			SI32 AddPer = 0;

			//makeitemnum =((makeitemnum*140)/100);
			if(skilllevel >= 30 && skilllevel < 45)
			{
				temMinnum = ((makeitemnum*1200)/1000); // �ּҰ�.

				AddPer = (skilllevel - 30) * 13; 
				temnum = ((makeitemnum*(1200+AddPer))/1000); // ��� ������ ���� �ƽ���.

				makeitemnum = max(temMinnum ,temnum );
			}
			else if(skilllevel >= 45 && skilllevel < 60)
			{
				temMinnum = ((makeitemnum*1400)/1000); // �ּҰ�.

				AddPer = (skilllevel - 45) * 13; 
				temnum = ((makeitemnum*(1400+AddPer))/1000); // ��� ������ ���� �ƽ���.

				makeitemnum = max(temMinnum ,temnum );			
			}
			else if(skilllevel >= 60 && skilllevel < 75)
			{
				temMinnum = ((makeitemnum*1600)/1000); // �ּҰ�.

				AddPer = (skilllevel - 60) * 13; 
				temnum = ((makeitemnum*(1600+AddPer))/1000); // ��� ������ ���� �ƽ���.

				makeitemnum = max(temMinnum ,temnum );
			}
			else if(skilllevel >= 75 && skilllevel < 100)
			{
				temMinnum = ((makeitemnum*1800)/1000); // �ּҰ�.

				AddPer = (skilllevel - 75) * 13; 
				temnum = ((makeitemnum*(1800+AddPer))/1000); // ��� ������ ���� �ƽ���.

				makeitemnum = max(temMinnum ,temnum );
			}
			else if(skilllevel ==  100)
			{
				makeitemnum =((makeitemnum*2000)/1000);
			}
		}
	}
	else
		makeitemnum = 0;

	return makeitemnum;
}
// ���λ����� �ڽ��� Ư�� �������� ��ϵǾ�����..
bool cltCharServer::IsExistItemOnOpeningPersonShop(SI32 siItemPos)
{
	if( bPersonalShopSwitch == true && clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( clShopData.m_siSelectedInventoryPos[i] == siItemPos )
			{
				if( clShopData.m_clItem[i].siUnique > 0  )
					return true;
			}
		}

		// �ͼ����� ���λ���
		if( clShopData.m_siSelectedSpacialInventoryPos == siItemPos	)
		{
			// ���� �������� ������ �����ϴ��� üũ 
			if( clShopData.m_clSpacialItem.siUnique > 0 )
			{
				return true;
			}
		}
	}

	return false;
}
