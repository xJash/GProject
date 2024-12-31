//---------------------------------
// 2004/10/18 ���°�
//---------------------------------
#include "..\Common\CommonHeader.h"
#include "..\Common\Order\Order.h"
#include "..\Common\Util\Util.h"

#include "..\..\Client\Client.h"
#include "..\..\Server\Server.h"

#include "../CommonLogic/Land/Land.h"
#include "../CommonLogic/MsgRval-Define.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"

extern cltCommonLogic* pclClient;

// ��縦 ���� �� �ִ°� ?
bool cltCharCommon::CanFarm(SI32 x, SI32 y, SI32* prtnval)
{
	cltServer* pclserver = (cltServer*)pclClient;

	if(pclMap == NULL)return false;

	if(pclMap->IsInMapArea(x, y) == false)return false;

	if((pclMap->GetMouseTileAtb(x, y) & MOUSETILEATB_FARM) == 0)return false;

	SI32 siUseAbleDay	= 0;
	BOOL bUseAble		= FALSE;

	if ( pclClient->GameMode == GAMEMODE_SERVER )
	{
		// ��ȯ���̸� �����̳� ��ⱸ�� Ȯ������ �ʴ´�. 
		if(clIdentity.siIdentity != IDENTITY_PERSON_SUMMON)
		{
			// ������ Ȯ���Ѵ�. 
#ifdef _SAFE_MEMORY
			if(pclCI->clCharSkill.GetTotalSkillLevel(SKILL_FARM, 0, 0, &pclCI->clCharItem.clItem[0]) <= 0)
#else
			if(pclCI->clCharSkill.GetTotalSkillLevel(SKILL_FARM, 0, 0, pclCI->clCharItem.clItem) <= 0)
#endif
			{
				// ��ų���Ѿ��� ��� ����Ʈ ���̶�� ����.
				SI16 siQuestType, siQuestUnique, siPara1, siPara2;
				SI16 siQuestClearCond = QUEST_CLEAR_COND_FARMNOSKILL;
				if( pclCI->clQuestInfo.IsQuestGoing(siQuestClearCond, &siQuestType, &siQuestUnique, &siPara1, &siPara2) == false )
				{
					*prtnval = CANFARM_ERROR_NOSKILL;
					return false;
				}
			}
			
			// ��ⱸ�� Ȯ���Ѵ�. 
			if( ActiveWeapon < 0 || ActiveWeapon >= MAX_ITEM_PER_PERSON )
			{
				*prtnval = CANFARM_ERROR_NOTOOL;
				return false;
			}
			cltItem* pclitem = &pclCI->clCharItem.clItem[ ActiveWeapon];
			bUseAble = pclserver->GetItemUseAbleDay(&pclCI->clCharItem.clItem[ActiveWeapon], &siUseAbleDay);

			// PCK : ���� ���Ⱓ�� Ȯ���ؼ� �������� ���̻� ä���� �Ҽ����� �Ѵ�.
			if(siUseAbleDay < 0)	return false;

			if(pclClient->pclItemManager->IsItemInfoAtb(pclitem->siUnique, ITEMINFOATB_FARMTOOL)  == false)
			{
				*prtnval = CANFARM_ERROR_NOTOOL;
				return false;
			}

			// ������ �������� 0�϶� �۵�����
			if ( pclClient->IsCountrySwitch(Switch_NewDurability) )
			{
				if ( 0 >= pclitem->GetDurability() )
				{
					*prtnval = CANFARM_ERROR_NOTOOL;
					return false;
				}
			}

		}
	}
	
	return true;
}

//---------------------------------
// ĳ���͸� �������  ����� ���� ������ �Ѵ�. 
//---------------------------------
bool cltCharCommon::SetFarm(SI32 dx, SI32 dy)
{
	if(dx <  0)						dx	=	0;
	if(dx >= pclMap->MH.MapXsize)	dx	=	pclMap->MH.MapXsize - 1;
    if(dy < 0)						dy	=	0;
 	if(dy >= pclMap->MH.MapYsize)	dy	=	pclMap->MH.MapYsize - 1;

	siFarmX	=	dx; 
	siFarmY	=	dy;

	siSubOrder = CHARWORKSTEP_DECIDELENGTH;
	
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		cltCharServer *pclChar = ( cltCharServer *)this;
		pclChar->siFarmingItemUnique = 0;

		// �ӽ÷� ���� ������� ���� �Ǿ����...
		//pclChar->siFarmingRentVillageUnique = 0;
	}
	

	return TRUE;
}

bool cltCharCommon::Farm()
{

   SHORT status;

   if(siSubOrder == CHARWORKSTEP_MOVE)
   {
		status = Move();
		
		if(MoveDone())bBusySwitch = false;
		else
		{
			bBusySwitch = true;
		}

		if(bBusySwitch == false)
		{
		   // �������� �����ϰų� �߰� ������ �����ϸ�, 
		   if(status > 0)
		   {
		      siSubOrder	 =	CHARWORKSTEP_DECIDELENGTH;
		   }

		}
   }

   if(siSubOrder == CHARWORKSTEP_DECIDELENGTH)
   {
	   // ���� ������ �� ���� ���¶�� �ߴ��Ѵ�.
	   SI32 rtnval = 0;
	   if(CanFarm(siFarmX, siFarmY, &rtnval) == false)
	   {   
		   bBusySwitch	=	false;
		   return false;
	   }
	   
	   
	   if(GetX() == siFarmX && GetY() == siFarmY)
	   {
		   siSubOrder = CHARWORKSTEP_ACTION;
		   cltCharServer *pclChar = (cltCharServer *)this;
	   }
	   else
	   {
		   SetMove(siFarmX, siFarmY);
		   siSubOrder = CHARWORKSTEP_MOVE;
	   }
  
   }

   if(siSubOrder == CHARWORKSTEP_ACTION)
   {
	   bBusySwitch = false;

	    if(FarmAction() == true)
		{
		   siSubOrder	=	CHARWORKSTEP_DECIDELENGTH;
		}

   }

	return true;
}


bool cltCharCommon::FarmAction()
{

	SetAnimation(ANITYPE_FARM);
	
	if(DoAnimationDelay() == FALSE)return false;

	// ������ ������ ������ �Ͼ��. 
	if(clAniInfo.IsInstant())
	{
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			cltCharServer *pclChar = (cltCharServer *)this;
			if ( IsPC( GetCharUnique() ) )
			{
				pclChar->FarmingAction( true );
			}
			else
			{
				pclChar->FarmingAction( false );
			}
		}
	}

	if(clAniInfo.GetAniStep() == 0  )//&& clAniInfo.siRetryNum > 0)
	{
		bHitDoneSwitch	= false;
		bBusySwitch		= false;
		
		return true;
	}
	else return false;
	
}
