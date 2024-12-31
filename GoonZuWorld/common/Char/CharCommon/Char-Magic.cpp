//---------------------------------
// 2003/10/19 ���°�
//---------------------------------

#include "..\..\Client\Client.h"

#include "..\..\Client\Music\Music.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"
#include "..\..\Util\Util.h"
#include "..\..\Order\Order.h"
#include "..\..\CommonLogic\MagicMgr\MagicAttribute\MagicAttribute.h"
#include "..\..\CommonLogic\MagicMgr\MagicMgr.h"

#include "..\..\Common\Skill\Skill-Manager.h"

#include "../../Char//CharServer/Char-Server.h"

extern cltCommonLogic* pclClient;



BOOL cltCharCommon::Magic()
{
	SI32 healability = 0 ;

	// ���� ���� ������ �غ�Ǿ� ������, 
	SI32 ref = pclKI->clCharAniManager.FindRefFromAnitype(ANITYPE_MAGIC);
	if(ref >= 0)
	{
		SetAnimation(ANITYPE_MAGIC);
	}
	else
	{
		SetAnimation(ANITYPE_ATTACK);
	}
	
	if(DoAnimationDelay() == FALSE)return FALSE;
	
	 if(clAniInfo.IsInstant() && bHitDoneSwitch == false)
	 {
		 bHitDoneSwitch = true;

		 MagicOperation();

	     OrderStop(siID, BY_COMPUTER);
	 }

	 if(clAniInfo.GetAniStep() == 0 )//&& clAniInfo.siRetryNum > 0 )
	 {
		 bHitDoneSwitch = false;
		 bBusySwitch	= false;
	   return TRUE;
	 }
	 else
	 {
		 // �ൿ �߿��� �ٻڴ�. 
		 bBusySwitch	= true;
		 return FALSE;
	 }

}



void cltCharCommon::MagicOperation()
{
	SI32 attackid	= clCurOrder.siPara2;
	SI16 magickind	= clCurOrder.siPara3;

	if ( pclCM->IsValidID(attackid) == false )
	{
		return;
	}

	stMagicAttributeData* psMagicData = pclClient->pclMagicManager->GetMagicAttribute( magickind );
	if ( NULL == psMagicData )
	{
		return;
	}

	CMagicAttribute *pMagicAttributePtr = pclClient->pclMagicManager->GetMagicAttributePtr();
	if ( NULL == pMagicAttributePtr )
	{
		return;
	}

	SI32 returnval = 0;

	if ( MAGIC_CASTTYPE_BUF == psMagicData->si08MagicCastType )
	{
		if ( false == CanMagicBuf(magickind, &returnval) )			return;
	}
	else
	{
		if ( false == CanMagic(attackid, magickind, &returnval) )	return;
	}

	

	//////////////////////////////////////////////////////////////////////////
	// MANA Check
	//////////////////////////////////////////////////////////////////////////
	SI32 kind = 0;
	if(IsNPC(GetCharUnique())||IsInstanceNPC(GetCharUnique()))	kind = GetKind();
	SI32 SkillType = pMagicAttributePtr->GetMagicSkillType(magickind);

	// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
	if( SKILL_SIKLLBOOK == SkillType && IsPC(GetID())  )
	{
		cltSkillBookMagic*	pclSkillBookMagic = pclCharSkillBookInfo->GetSkillBookMagic( GetAttackType() );	
		if( NULL == pclSkillBookMagic ) return;

		SkillType = pclSkillBookMagic->GetSkillUnique();
	}

#ifdef _SAFE_MEMORY
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel(SkillType, kind, pclCI->clIP.GetLevel(), &pclCI->clCharItem.clItem[0], GetID());
#else
	SI32 SkillLevel = pclCI->clCharSkill.GetTotalSkillLevel(SkillType, kind, pclCI->clIP.GetLevel(), pclCI->clCharItem.clItem, GetID());
#endif
	SI32 mana		= 0;

	// [����] ���� ������ ���� ���.
	SI32	siSubMagickind			= 0;
	SI32	siSubMagicOrganDamage	= 0;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(attackid);
	if( pclChar )
	{
		if( pclClient->IsCountrySwitch(Switch_SkillBook) && pclChar->pclCharSkillBookInfo )
		{
			stMagicAttributeData* psSubMagicData = pclChar->pclCharSkillBookInfo->FindMagicAttributeDataFromParentMagic( magickind, siSubMagickind );
			if( psSubMagicData )
			{
				siSubMagicOrganDamage = psSubMagicData->si16MagicOrganDamage;
			}
		}	
	}

	if ( pclClient->GameMode == GAMEMODE_SERVER )
	{
		// ���� ������ 0���� �ʱ�ȭ�Ѵ�.
		if ( MAGIC_CASTTYPE_BUF != psMagicData->si08MagicCastType )
		{
			SetMagicDelay(0);
		}
		
		// Mana�� �Ҹ��Ѵ�. 
		mana = pclClient->pclMagicManager->GetSpendMana(magickind, SkillLevel,GetCharUnique());
		
		// MAGIC_TYPE_SOULGUARD �̸� ��ų���߰� mana�� ���������� ���Ѵ�.
		if(magickind == MAGIC_SOULGUARD_FIRE)
		{
			SkillLevel = 1;
			mana = 0;
		}
		// �ҿ� ���� ��Ų�� ����ϴ� ����
		if(magickind == MAGIC_SOULGUARD_PUMKIN)
		{	
			SkillLevel = 1;
			mana = 0;
		}
		if(pclClient->IsCountrySwitch(Switch_SoulGuard))
		{
			// ��Ų ���� ����Ȯ���� ���� ���� ������ 0�����Ѵ�.
			SI32 siCharPersonID = pclCI->GetPersonID()	;
			SI32 siCharId = pclCM->GetIDFromPersonID( siCharPersonID)	;
			cltCharServer* pclCharServer = pclCM->GetCharServer(siCharId)	;
			if(pclCharServer != NULL )
			{
				SI32 siValue =  pclCharServer->SoulGuardAbilityActivity( SOULGUARD_ABILITY_MANA_ZERO );
				if ( 0 < siValue )
				{
					mana = 0;
				}
			}
		}
		
		if(mana)
		{
			DecreaseMana(mana);
			SetUpdateSwitch(UPDATE_BASICINFO, true, 0);
			if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
			{
				SetUpdateSwitch(UPDATE_IP, true, 0);
				SI32 parentid = GetSummonParentID() ;
				if ( IsPC(parentid) )
				{
					pclCM->CR[parentid]->SetUpdateSwitch(UPDATE_SUMMON,true ,0);
				}
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// CHAR MAGIC
	//////////////////////////////////////////////////////////////////////////
	// SKILLTYPE�� ������ �ش� Magic�� SET�Ѵ�.
	if ( SkillType!= -1 )
	{
		if ( MAGIC_CASTTYPE_BUF == psMagicData->si08MagicCastType )
		{
			m_clMagicBufMgr.PushMagicBuf( magickind, clPB.siMagicDecDelay, GetID() );

			// HP�� �÷��ִ� ������ ���� ���ÿ� �Ķ���͹ڽ��� �����Ѵ�
			SI32 siMagicGroup = pMagicAttributePtr->GetMagicGroup( magickind );
			if ( MAGIC_GROUP_BLESSHP == siMagicGroup )
			{
				ParametaBoxAction();
			}

			if ( GAMEMODE_SERVER == pclClient->GameMode )
			{
				SI32 siMagicOrganDamage = psMagicData->si16MagicOrganDamage 
										+ ((psMagicData->si16MagicOrganDamage * siSubMagicOrganDamage) / 100);
				if (pclCI->clHealthInfo.DecreaseOrg(	psMagicData->si16MagicOrganKind, 
														siMagicOrganDamage, 
														pclCI->clIP.GetLevel()) == true )
				{
					SetUpdateSwitch(UPDATE_HEALTH, true, 0);		// Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
				}
			}
		}	// if ( MAGIC_CASTTYPE_BUF == psMagicData->si08MagicCastType ) ����
		else
		{
			stMagicInfo clMagicInfo(magickind, GetCharUnique(), pclCM->CR[attackid]->GetCharUnique(), mana);
			pclClient->pclMagicManager->SetMagic(	(stMagicHeader *)&clMagicInfo, 
													clPB.GetAddMagicDamage(), 
													pclMap, 
													SkillLevel, 
													pclCI->clHealthInfo.GetOrg(psMagicData->si16MagicOrganKind) );

			// ����������, 
			if(pclClient->GameMode == GAMEMODE_SERVER)
			{
				// ������뿡 ���� �������� �ջ��� �߻���Ų��.
				if(IsPC(GetCharUnique()))
				{
					SI32 siMagicOrganDamage = psMagicData->si16MagicOrganDamage 
											+ ((psMagicData->si16MagicOrganDamage * siSubMagicOrganDamage) / 100);

					if(pclCI->clHealthInfo.DecreaseOrg(	psMagicData->si16MagicOrganKind, 
														siMagicOrganDamage, 
														pclCI->clIP.GetLevel()) == true	)
					{
						SetUpdateSwitch(UPDATE_HEALTH, true, 0);		// Ŭ���̾�Ʈ�� ������Ʈ ��Ų��. 
					}
				}
			}
		}	// else ����
	}
}