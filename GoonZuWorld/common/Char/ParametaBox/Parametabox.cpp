//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "../Client/Client.h"
#include "../Server/Server.h"
#include <math.h>

#include <stdio.h>
#include "ParametaBox.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "Char/CharManager/CharManager.h"

#include "..\..\..\GoonZuWorld\CommonLogic\Cityhall\Cityhall.h"

#include "../../Skill/Skill.h"
#include "../../Skill/Skill-Manager.h"
#include "../../../common/Item/ItemCommon/cltSetItem.h"
#include "../../../CommonLogic/Marriage/MarriageManager.h"

#include <MsgType-Person.h>
#include <MsgType-Item.h >

#include "NFile.h"
#include "NUtil.h"

#include "Guild/Guild.h"

#include "../CommonLogic/StructureClass/StructureClass.h"
#include "../CommonLogic/CommonLogic.h"

extern cltCommonLogic* pclClient;

//SI64 ExpForLevelUp[MAX_PERSON_LEVEL][3];// SI32->SI64 ����ġ �����÷ο춧���� ����
//SI32 FameExpForLevelUp[MAX_FAME_LEVEL][3];
ExpTable			ExpForLevelUp;							// ����ġ ���̺�
FameExpTable		FameExpForLevelUp;						// �� ����ġ ���̺�
cltLevelUpReward	LevelUpReward[MAX_CHARACTER_LEVEL+1];	// ĳ���� ������ ���� ���̺�

//--------------------------------------------
// cltPIPInfoCommon
//-------------------------------------------
BOOL cltPIPInfoCommon::IncreaseExp(SI64 exp)// SI32->SI64 ����ġ �����÷ο춧���� ����
{
	if(exp <= 0)return FALSE;

	SetCurExp(GetCurExp() + exp);

	if(GetCurExp() >= GetRequiredExpForLevel(GetLevel() + 1) && GetLevel() < MAX_CHARACTER_LEVEL)// SI32->SI64 ����ġ �����÷ο춧���� ����
		return TRUE;

	return FALSE;
}

// ������ ���� ������ ��� ȿ���� ���Ѵ�. 
SI32 cltPIPInfoCommon::CalcLevelDamage()
{
	SI32 sidamage = 0;
	SI32 level = siLevel;

	if(level > 90)
	{
		sidamage += ((level - 90) / 1);
		level = 90;
	}
	if(level > 70)
	{
		sidamage += ((level - 70) / 2);
		level = 70;
	}
	if(level > 60)
	{
		sidamage += ((level - 60) / 3);
		level = 60;
	}
	if(level > 50)
	{
		sidamage += ((level - 50) / 4);
		level = 50;
	}
	if(level > 40)
	{
		sidamage += ((level - 40) / 5);
		level = 40;
	}
	sidamage	+= (level / 10);

	return sidamage;
}

// ������ ���� ���� ������ ������ ��´�.
BOOL cltPIPInfoCommon::GetLevelUpRewardItem(SI32 level, SI32* pItemUnique, SI32* pItemCount, SI16* psiNotice)
{
	if(level <= 0)					return FALSE;
	if(level > MAX_CHARACTER_LEVEL)	return FALSE;
	if(pItemUnique == NULL)			return FALSE;
	if(pItemCount == NULL)			return FALSE;
	if(psiNotice == NULL)			return FALSE;

	SI32	i;

	for(i=0; i<MAX_LEVELUP_REWARD_ITEM; i++)
	{
		pItemUnique[i] = 0;
		pItemCount[i] = 0;
		psiNotice[i] = 0;
	}

	for(i=0; i<MAX_LEVELUP_REWARD_ITEM; i++)
	{
		pItemUnique[i] = LevelUpReward[level].ItemUnique[i];
		pItemCount[i] = LevelUpReward[level].ItemCount[i];
		psiNotice[i] = LevelUpReward[level].siNotice[i];
	}

	return TRUE;
}

void cltPIPInfoCommon::GetGMSectionData(GMSectionData* pkGMSectionData)
{
	if( pkGMSectionData == NULL )		return;

	pkGMSectionData->BeginData( "IPInfoCommon" );
	{
		pkGMSectionData->AddDataInt( "life",	Life);
		pkGMSectionData->AddDataInt( "mana",	Mana);
		pkGMSectionData->AddDataInt( "level",	siLevel);
		pkGMSectionData->AddDataInt( "bonus",	siBonus);
		pkGMSectionData->AddDataInt( "exp",		siExp);
	}
	pkGMSectionData->EndData( "IPInfoCommon" );
}


//--------------------------------------------
// cltPIPInfo
//--------------------------------------------
void  cltPIPInfo::Set(cltPIPInfo ip)
{
	ZeroMemory(this, sizeof(cltPIPInfo));
	memcpy(this, &ip, sizeof(cltPIPInfo));					//ok
}

void  cltPIPInfo::Set(cltPIPInfo* pip)
{
	if(pip == NULL)return ;

	ZeroMemory(this, sizeof(cltPIPInfo));

	memcpy(this, pip, sizeof(cltPIPInfo));					//ok
}


void  cltPIPInfo::Set(cltPIPInfoCommon* pip)
{
	if(pip == NULL)return ;

	Init();

	cltPIPInfoCommon::Set(pip);
}


bool cltPIPInfo::IncreaseFameExp(SI32 exp)
{
	if(exp < 0)return FALSE;

	siFameExp += exp;

	SI32 famelevel = GetFameLevelFromExp( siFameExp );
	if(famelevel > siFameLevel)return true;

	return false;
}

void cltPIPInfo::GetGMSectionData(GMSectionData* pkGMSectionData)
{
	if( pkGMSectionData == NULL )		return;

	((cltBasicAbility*)this)->GetGMSectionData(pkGMSectionData);
	((cltPIPInfoCommon*)this)->GetGMSectionData(pkGMSectionData);

	pkGMSectionData->BeginData( "IPInfo" );
	{
		pkGMSectionData->AddDataInt( "skillbonus",	siSkillBonus);
		pkGMSectionData->AddDataInt( "fameexp",		siFameExp);	
		pkGMSectionData->AddDataInt( "famelevel",	siFameLevel);
		pkGMSectionData->AddDataInt( "money",		siMoney);	
	}
	pkGMSectionData->EndData( "IPInfo" );
}


//----------------------------------------------
// cltParametaBox
//----------------------------------------------
cltParametaBox::cltParametaBox()
{
	pclCI			= NULL;

	Init(NULL, NULL, NULL, NULL, NULL);
}

void cltParametaBox::Init(cltItemManagerCommon* pclitemmanager, cltPIPInfo* pclip, cltHealthInfo* pclhealthinfo, cltKindInfo* pclki, cltGMCommandKindInfo* pclGMki)
{
	pclItemManager		= pclitemmanager;
	pclIP				= pclip;
	clHealth.pclInfo	= pclhealthinfo;
	pclKI				= pclki;
	pclGMCommandKindInfo = pclGMki;

	if(pclki)
	{
		pclBPB				= &pclKI->clBPB;
	}
	else
	{
		pclBPB = NULL;
	}

	//------------------------------------------------------------------------
	siTotalPHysicalMinAttackDmg= 0;
	siTotalPHysicalMaxAttackDmg= 0;
	siEquipPHysicalMinAttackDmg= 0;
	siEquipPHysicalMaxAttackDmg= 0;
	siStrPHysicalAttackDmg= 0;

	siTotalMagicalMinAttackDmg= 0;
	siTotalMagicalMaxAttackDmg= 0;
	siEquipMagicalMinAttackDmg= 0;
	siEquipMagicalMaxAttackDmg= 0;

	siTotalPHysicalHitRate= 0;
	siPHysicalHitRateRank= 0;
	siPHysicalHitRateLevel= 0;
	siEquipPHysicalHitRate= 0;
	siAddPHysicalHitRate= 0;

	siTotalMagicalHitRate= 0;
	siMagicalHitRateRank= 0;
	siMagicalHitRateLevel= 0;
	siEquipMagicalHitRate= 0;
	siAddMagicalHitRate= 0;

	siTotalPHysicalDefensiveRate= 0;
	siPHysicalDefensive= 0;
	siEquipPHysicalDefensive= 0;
	siHndPHysicalDefensive= 0;

	siTotalMagicalDefensiveRate= 0;
	siMagicalDefensive= 0;
	siEquipMagicalDefensive= 0;
	siWisMagicalDefensive= 0;

	siTotalPHysicalDodgeRate= 0;
	siPHysicalDodgeRateRank= 0;
	siPHysicalDodgeRateLevel= 0;
	siEquipPHysicalDodgeRate= 0;

	siTotalMagicalDodgeRate= 0;
	siMagicalDodgeRateRank= 0;
	siMagicalDodgeRateLevel= 0;
	siEquipMagicalDodgeRate= 0;

	siTotalHitpoint= 0;
	siEquipHitpoint= 0;
	siVitHitpoint= 0;

	siTotalManapoint= 0;
	siEquipManapoint= 0;
	siMagManapoint= 0;

//---------------------------------------------------------------------

	uiParaActionFrame			= 0;		// ���������� Action�� ���� ������. 
	uiLastGetCriticalRateFrame	= 0;		// ���������� ũ��Ƽ�� ���� Ȯ���� ���� ������. 
	siOldLevel					= 0;

	siReservedLife		= 0;

	//----------------------
	// ũ��Ƽ�� ���� Ȯ�� 
	//----------------------
	siCriticalRate		= 0;

	//---------------------
	// MagicDelay ���̱�
	//---------------------
	siMagicDecDelay		= 0;

	//----------------------
	// ����. 
	//----------------------
	siLevelAC			= 0;		// ������ ���� ���� 
	siEquipAC			= 0;
	siDefaultAC			= 0;
	siGeneralAC			= 0;
	dwGeneralACClock	= 0;
	siEvolveAC			= 0;
	siBufAC				= 0;
	siNamingAC			= 0;
	siTransFormAC		= 0;
	TotalAC				= 0;

	//----------------------
	// ������ 
	//----------------------
	siStrDamage			= 0;		// �ٷ¿� ���� ������. 
	siStaffSkillDamage	= 0;		// �����̼��� ���� ������. 
	siLevelDamage		= 0;		// ������ ���� ������. 
	siTorpedoDamage		= 0;
	siNamingDamage		= 0;

	TotalEquipMinDamage	= 0;	// ���⿡ ���� ������. 
	TotalEquipMaxDamage	= 0;

	siGeneralDamage		= 0;
	dwGeneralDamageClock= 0;

	siBufDamage			= 0;

	siEvolveDamage		= 0;

	TotalMinDamage		= 0;
	TotalMaxDamage		= 0;

	siAttackType		= 0;								// ���� ���. 	
	dwAttackInterval	= 0;								// ���� �ֱ�. 

	//---------------------
	// ��
	//---------------------
	siTotalLuck			= 0;
	siEquipLuck			= 0;

	//--------------------------
	// ��� ���� 
	//--------------------------
	siArmWeaponUnique	= 0;
	clShapeEquip.Init();

	//--------------------------
	// ���߷� 
	//--------------------------
	AR				= 0;
	DR				= 0;
	HitRate			= 0;
	siEquipAssistHitRate	= 0;
	siWeaponDefaultHitRate	= 0;

	//--------------------------
	// ��� ���� ������ ����. 
	//--------------------------
	siEquipAssistDamageReduceRate	= 0;

	//-------------------------
	// �̵��ӵ� 
	//-------------------------
	BasicMoveSpeed	= 0;
	ShoesMoveSpeed	= 0;
	BufMoveSpeed	= 0;
	TotalMoveSpeed	= 0;
	GivenMoveSpeed	= 0;


	siHealthStrRate	= 0;
	siHealthDexRate	= 0;
	siHealthMagRate = 0;
/*
	siGuildStr=0;	
	siGuildDex=0;	
	siGuildMag=0;	
	siGuildVit=0;	
	siGuildHnd=0;	
	siGuildLuck=0;
*/
	siSkillVitRate	= 0;
	siSkillMagRate	= 0;

	siHorseStr		= 0;
	siHorseDex		= 0;
	siHorseMag		= 0;	

	clEquipBA.Init();
	clTotalBA.Init();

	bSetTotalBA		= false;

	//KHY - 1220 - ���Žý���.
	clTransFormBA.Init();
	siTransFormSyc	= 0;
}

// ���� ������ �ö󰡴µ� �ʿ��� ����ġ. 
SI64 cltParametaBox::GetNextExp()// SI32->SI64 ����ġ �����÷ο춧���� ����
{
	return GetRequiredExpForLevel(pclIP->GetLevel() + 1);
}

// ���� �������� ���� ������ �ö���µ� �ʿ��ߴ� ����ġ. 
SI64 cltParametaBox::GetPrevExp()// SI32->SI64 ����ġ �����÷ο춧���� ����
{
	return GetRequiredExpForLevel(pclIP->GetLevel());
}


// ������ �������� �� ���ݷ��� ���Ѵ�. 
SI32 cltParametaBox::CalcApower()
{

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SI32 diff = siTotalPHysicalMaxAttackDmg - siTotalPHysicalMinAttackDmg;
		if(diff < 0)diff = 0;

		return siTotalPHysicalMinAttackDmg + pclClient->GetFrame() % (diff + 1);
	}
	else
	{
		SI32 diff = TotalMaxDamage - TotalMinDamage;
		if(diff < 0)diff = 0;

		return TotalMinDamage + pclClient->GetFrame() % (diff + 1);
	}

	//return 0;

}


// ��æƮ ���� by tae-yang
SI32 cltParametaBox::GetEnchantDefDamage(SI32 EnchantType, cltItem *pclItemList)
{
	SI32 EnchantDamage = 0 ;

	EnchantDamage = pclItemManager->GetEnchantACFrom(pclItemList, EnchantType);

	return EnchantDamage;
}

// ��æƮ ���� by tae-yang
SI32 cltParametaBox::GetEnchantAttDamage(SI32 EnchantType, cltItem *pclItemList)
{
	SI32 EnchantDamage = 0 ;

	EnchantDamage = pclItemManager->GetEnchantAttFrom(pclItemList, EnchantType);

	return EnchantDamage;
}

////  101. ���� ���ݷ� 
void cltParametaBox::SetPhysicalAttackDemage(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo ,bool *bSwitch, SI16 siAttackWearStoneNum)
{
	SI32 totalStr = clTotalBA.GetStr();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 101.1 �����Ǿ��ִ� �⺻ ������  - ĳ���Ϳ� ���� ���ҽ��� ����.
	//--------------------------------------
	SI32 defaultweaponmindamage = 0;
	SI32 defaultweaponmaxdamage = 0;
	
	// ��ȯ���϶� ��� �ִٸ�
	if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (pclitemlist) && (pclitemlist[PERSONITEM_WEAPON1].siUnique) )
	{	
		// ����� ������ ���� ������ ���ƾ� �⺻ ������ ����
		if ( pclchar->pclCI->clIP.GetLevel() == siAttackWearStoneNum )
		{
			defaultweaponmindamage = pclKI->clDefaultWeaponInfo.GetDefaultMinDamage();
			defaultweaponmaxdamage = pclKI->clDefaultWeaponInfo.GetDefaultMaxDamage();
		}
	}
	else if((pclidentityinfo) && pclidentityinfo->siIdentity == IDENTITY_GMCREATE_MONSTER)
	{
		defaultweaponmindamage = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultMinDamage();
		defaultweaponmaxdamage = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultMaxDamage();
	}
	// ��ȯ���� �ƴϰų� ��� ���ٸ�
	else
	{
		defaultweaponmindamage = pclKI->clDefaultWeaponInfo.GetDefaultMinDamage();
		defaultweaponmaxdamage = pclKI->clDefaultWeaponInfo.GetDefaultMaxDamage();
	}


	//--------------------------------------
	// 101.2  �ٷ¿� ���� ���� ������ ����.
	//--------------------------------------

	switch(siAttackType)
	{
		case ATTACKTYPE_SWORD:
		case ATTACKTYPE_SPEAR:
		case ATTACKTYPE_AXE:
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/20000);
			break;
		case ATTACKTYPE_BOW:
		case ATTACKTYPE_BOW1:
		case ATTACKTYPE_NEW_BOW1:
		case ATTACKTYPE_GUN:
		case ATTACKTYPE_GUN1:
		case ATTACKTYPE_NEW_GUN1:
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/150000 *6);
			break;
		case ATTACKTYPE_STAFF:
		case ATTACKTYPE_STAFF1:
		case ATTACKTYPE_STAFF2:
		case ATTACKTYPE_NEW_STAFF2:
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/150000 *3);
			break;
		//KHY - 0410 - ��ȯ����  - ���Ÿ� ����.
		case	ATTACKTYPE_HALLOWEENGHOST	:
		case	ATTACKTYPE_CAKE:
		case	ATTACKTYPE_EGG			:
		case	ATTACKTYPE_CATFISH			:
		case	ATTACKTYPE_LADYBUGFAN			:
		case	ATTACKTYPE_TOHANG			:
		case	ATTACKTYPE_OCTOPUS			:
		case	ATTACKTYPE_BOOMERANG			:
		case	ATTACKTYPE_SHELLFISHBOMB			:
		case	ATTACKTYPE_VINE			:
		case	ATTACKTYPE_MONKEY			:
		case	ATTACKTYPE_FIREBALL			:
		case	ATTACKTYPE_FLYVINE			:
		case	ATTACKTYPE_BLACKSPIDER			:
		case	ATTACKTYPE_FROZENSORCERER			:
		case	ATTACKTYPE_CANNONMOL			:
		case	ATTACKTYPE_PRIEST			:
		case	ATTACKTYPE_EMPERORARCHER			:
		case	ATTACKTYPE_PIRATEARCHER			:
		case	ATTACKTYPE_MINEGIRL			:
		case	ATTACKTYPE_GREENTURTLE			:
		case	ATTACKTYPE_CASTLECANNON			:
		case	ATTACKTYPE_CHICKENBIG			:
		case	ATTACKTYPE_EVILEYE			:
		case	ATTACKTYPE_OTOHIME			:
		case	ATTACKTYPE_MAGICALRACCOON			:
		case	ATTACKTYPE_GREATWALLMAGICIAN			:
		case	ATTACKTYPE_GREATWALLASURA			:
		case	ATTACKTYPE_BEARTANG			:
		case	ATTACKTYPE_SUPERBEARTANG			:
		case	ATTACKTYPE_CHRISTMASRANGE			:
		case	ATTACKTYPE_EMPERORMASTER			:
		case	ATTACKTYPE_FROZENQUEEN			:
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/150000 *6);
			break;
		case	ATTACKTYPE_SIMTORYONG			:
		case	ATTACKTYPE_MAMARACCOON			:
		case	ATTACKTYPE_RACCOONTOWER			:
		case	ATTACKTYPE_GREATWALLSPIDER			:
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/20000);
			break;

		default : // ��Ÿ ��� Ÿ�� - �Ǽ�����.
			siStrPHysicalAttackDmg = (totalStr* ((dwAttackInterval*10)+(level*50))/20000);
			break;
	}

	//--------------------------------------
	// 101.3  ��� ���� ���� ������ ����. 
	//--------------------------------------
	SI16 minDmg = 0;
	SI16 maxDmg = 0;

	SI32 CrysTalMinPer = 0;
	SI32 CrysTalMaxPer = 0;

	if(pclitemlist)
	{
		if (pclClient->IsCountrySwitch(Switch_StatusBug)) 
		{
			minDmg = (SI16)pclItemManager->GetWeaponMinDamage(pclitemlist, activeweaponpos); 
			maxDmg = (SI16)pclItemManager->GetWeaponMaxDamage(pclitemlist, activeweaponpos);
		}
		else
		{
			minDmg = (SI16)pclItemManager->GetWeaponMinDamage(pclitemlist, activeweaponpos,pclchar , &CrysTalMinPer); 
			maxDmg = (SI16)pclItemManager->GetWeaponMaxDamage(pclitemlist, activeweaponpos,pclchar ,&CrysTalMaxPer);
		}

		if(minDmg >0)
			siEquipPHysicalMinAttackDmg = minDmg;
		else
			siEquipPHysicalMinAttackDmg = 0;
		
		if(maxDmg >0)
			siEquipPHysicalMaxAttackDmg = maxDmg;
		else
			siEquipPHysicalMaxAttackDmg = 0;
	}

	//--------------------------------------
	// 101.4  ���ſ� ���� ���� ������ ����.
	//--------------------------------------
	//KHY - 1220 - ���Žý���.
	SI16 TminDmg = 0;
	SI16 TmaxDmg = 0;
	
	if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
	{
		switch(siAttackType)
		{ 
			case ATTACKTYPE_SWORD:
			case ATTACKTYPE_SPEAR:
				{
					if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
					{
						TminDmg = 20;
						TmaxDmg = 20;
					}
				}
				break;
			case ATTACKTYPE_AXE:
				{
					TminDmg = (SI16)(siTransFormSyc/2);
					TmaxDmg = (SI16)(siTransFormSyc/2);
				}
				break;					
			case ATTACKTYPE_GUN:
				{
					TminDmg = (SI16)((REAL32)siTransFormSyc*(REAL32)0.4);
					TmaxDmg = (SI16)((REAL32)siTransFormSyc*(REAL32)0.4);
				}
				break;					
		}
	}		

	//--------------------------------------
	// 101.5  ��ȯ�� ��񼮿� ���� ������ ���
	//--------------------------------------
	SI16 siAttackWearStoneMinDmg = 0;
	SI16 siAttackWearStoneMaxDmg = 0;

	if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (SUMMON_EQUIP_LIMITMINLEVEL < siAttackWearStoneNum) )
	{
		REAL32 siAttackWearStoneIncreasePercent = (siAttackWearStoneNum - SUMMON_EQUIP_LIMITMINLEVEL) * 1.0;

		siAttackWearStoneMinDmg = (SI16)((REAL32)(siEquipPHysicalMinAttackDmg/100) * siAttackWearStoneIncreasePercent);
		siAttackWearStoneMaxDmg = (SI16)((REAL32)(siEquipPHysicalMaxAttackDmg/100) * siAttackWearStoneIncreasePercent);
	}

	//--------------------------------------
	// 101.6 PCK : ����ġ�� Ÿ�� ���� ��� �������ݷ� + 100�� ���ش�.
	// [���] ��ȣ�� Ÿ�� ���� ��� ���� ���ݷ� + 100�� ���ش�. (09.05.15)
	// [���] ������Ʈ�� Ÿ�� ���� ��� ���� ���ݷ� +100�� ���ش�. (09.07.30)
	// [����] ������� Ÿ�� ���� ��� ���� ���ݷ� +100�� ���ش�. (09.12.31)
	//--------------------------------------
	SI16	siFireHatchMinDmg = 0;
	SI16	siFireHatchMaxDmg = 0;

	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if(pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_FIREHATCH ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_BAPHOMET ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_SASURI)
		{
			siFireHatchMinDmg = 100;
			siFireHatchMaxDmg = 100;
		}
	}

	//--------------------------------------
	// 101.8.6 ��ȥ ���� ������ ���
	//--------------------------------------
	SI16 siMarriageMinDmg = 0;
	SI16 siMarriageMaxDmg = 0;

	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) && (pclchar->IsMarried()) )	bMarriageCondition = true;
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) && (pclchar->IsMarried()) )		bMarriageCondition = true;
		}

		if ( (pclClient->m_pclMarriageMgr) && (true == bMarriageCondition) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
		{
			SI16 siMarriageValue = (SI16)pclClient->m_pclMarriageMgr->GetTotalAttackAbilityValue( pclchar->pclMarriage->GetLoveLevel() );
			if ( 0 < siMarriageValue )
			{
				siMarriageMinDmg = siMarriageValue;
				siMarriageMaxDmg = siMarriageValue;
			}
		}
	}

	//--------------------------------------
	// 101.7  ���� ȿ���� ���� ���� ������ ���.
	//--------------------------------------
	minDmg = defaultweaponmindamage + siEquipPHysicalMinAttackDmg + (SI16)siStrPHysicalAttackDmg + TminDmg + siAttackWearStoneMinDmg + siFireHatchMinDmg + siMarriageMinDmg;
	maxDmg = defaultweaponmaxdamage + siEquipPHysicalMaxAttackDmg + (SI16)siStrPHysicalAttackDmg + TmaxDmg + siAttackWearStoneMaxDmg + siFireHatchMaxDmg + siMarriageMaxDmg;

	//--------------------------------------
	// 101.8.1   Identity �� �����ϴ� Ư�� ĳ������ ��� , ���ݷ� 
	//--------------------------------------
	if(pclidentityinfo)
	{

		switch(pclidentityinfo->siIdentity)
		{
		case IDENTITY_CASTLE:		
			break;
		case IDENTITY_VILLAGEGOD:	
		case IDENTITY_VILLAGEGOD_SUMMON:
			break;
		case IDENTITY_PERSON_SUMMON:
			{
				minDmg = minDmg + (SI32)(minDmg * PERSON_SUMMON_ATTACKBONUS_PERCENT * 0.01f) ;
				maxDmg = maxDmg + (SI32)(maxDmg * PERSON_SUMMON_ATTACKBONUS_PERCENT * 0.01f) ;

				if (pclchar)
				{
					// ���� ��ȯ�����
					SI32 parentid = pclchar->GetSummonParentID();
					if(pclClient->pclCM->IsValidID(parentid))
					{
						SI32 summonskill = 0;

						if(pclskillinfo)
						{
							summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON,
								0,
								0,
								&pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
						}

						// ��ȯ�� ������ ��ȯ�� ��ų ������ ���� ��ȯ���� ���ݷ��� ������Ų��.
						SI32 attackBonusPercent = 0;
						attackBonusPercent = pclClient->GetSummonAttackBonus( summonskill );

						minDmg += minDmg * attackBonusPercent / 100;
						maxDmg += maxDmg * attackBonusPercent / 100;

						// ��ȯ�� ������ ��ȯ�� ���ݷ�, ���� ���� ������ ������ �ִٸ� 

						SI32 bufBonusPercent = 0;

						if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP ) == true )
						{
							bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent( BUF_SUMMONATACUP ) );
						}   
						if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) == true )
						{
							bufBonusPercent = max( bufBonusPercent , 20 );
						}   

						if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_EGGMOONCAKE ) == true )
						{
							SI32 percent = 0;
							SI32 siBufIndex = pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
							if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
								percent = max( percent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.m_stBuf[siBufIndex].siPercent );
						
							bufBonusPercent = max( bufBonusPercent , percent );
						}  

						minDmg += minDmg * bufBonusPercent / 100;
						maxDmg += maxDmg * bufBonusPercent / 100;
					}

				}

			}
			break;
		case IDENTITY_VILLAGEHUNT:								break;
		default:												break;
		}
	}

	//--------------------------------------
	// 101.8.2  ����ȿ���� ���� ���.
	//--------------------------------------
	*bSwitch = false;	
	if(siGeneralDamage)
	{		
		//-------------------------------
		// ���Ӽ����� ��쿡�� ����ȿ���� �ð��� Ȯ���Ѵ�. 
		//-------------------------------
		if(gamemode == GAMEMODE_SERVER)
		{
			if(TABS(pclClient->CurrentClock - dwGeneralDamageClock) > 10000)
			{
				siGeneralDamage			= 0;				
				dwGeneralDamageClock	= 0;

				*bSwitch = true;
			}
		}

		minDmg = minDmg * (100 + siGeneralDamage ) / 100;
		maxDmg = maxDmg * (100 + siGeneralDamage ) / 100;
	}

	// Ȱ������ ���� Attack���
	if(gamemode == GAMEMODE_SERVER)
	{
		if ( pclchar && IsPC( pclchar->GetID() ) && pclchar->pclCI->clBI.bCombatService )
		{
			CrysTalMinPer += 30 ;
			CrysTalMaxPer += 30 ;
		}
	}
	else if(gamemode == GAMEMODE_CLIENT)
	{
		if ( pclchar && pclchar->GetID() == 1 && pclchar->pclCI->clBI.bCombatService )
		{
			CrysTalMinPer += 30 ;
			CrysTalMaxPer += 30 ;
		}		
	}
	// �� �����̾� ���� Ǯ������ Ư���ɷ� ����.
	//// �����̾� ���� Ǯ���� �϶� ���ݷ� 5% ���� 
	//if(gamemode == GAMEMODE_SERVER)
	//{
	//	if ( pclchar && IsPC( pclchar->GetID() ))
	//	{
	//		cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse();
	//		if ( pclHorse != NULL )
	//		{
	//			SI32 siEquipPremiumPartsNum = pclHorse->GetPremiumPartsNum()	;
	//			if (siEquipPremiumPartsNum == 3 )
	//			{
	//				SI32 siHorseunique = pclHorse->siHorseUnique	;
	//				switch (siHorseunique )
	//				{
	//				case HORSEUNIQUE_BROWN:	// ������
	//				case HORSEUNIQUE_BLACK:// �渶
	//				case HORSEUNIQUE_WHITE:// �鸶
	//				case HORSEUNIQUE_RED://���丶
	//				case HORSEUNIQUE_RUDOLF ://�絹��
	//				case HORSEUNIQUE_STEEL ://ö�⸶
	//				case HORSEUNIQUE_BEAST ://����ȣ
	//				case HORSEUNIQUE_THOUSAND ://õ����
	//				case HORSEUNIQUE_ZEBRA ://��踶
	//					{
	//						CrysTalMinPer += 5 ;
	//						CrysTalMaxPer += 5 ;
	//					}
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
	//else if(gamemode == GAMEMODE_CLIENT)
	//{
	//	if ( pclchar && pclchar->GetID() == 1 )
	//	{
	//		cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse();
	//		if ( pclHorse != NULL )
	//		{
	//			SI32 siEquipPremiumPartsNum = pclHorse->GetPremiumPartsNum()	;
	//			if (siEquipPremiumPartsNum == 3 )
	//			{
	//				SI32 siHorseunique = pclHorse->siHorseUnique	;
	//				switch (siHorseunique )
	//				{
	//				case HORSEUNIQUE_BROWN:	// ������
	//				case HORSEUNIQUE_BLACK:// �渶
	//				case HORSEUNIQUE_WHITE:// �鸶
	//				case HORSEUNIQUE_RED://���丶
	//				case HORSEUNIQUE_RUDOLF ://�絹��
	//				case HORSEUNIQUE_STEEL ://ö�⸶
	//				case HORSEUNIQUE_BEAST ://����ȣ
	//				case HORSEUNIQUE_THOUSAND ://õ����
	//				case HORSEUNIQUE_ZEBRA ://��踶
	//					{
	//						CrysTalMinPer += 5 ;
	//						CrysTalMaxPer += 5 ;
	//					}
	//					break;
	//				}
	//			}
	//		}
	//		
	//	}		
	//}
	//--------------------------------------
	// 101.8.3  ������ ���� ���ݷ� ���
	//--------------------------------------
	if( gamemode == GAMEMODE_SERVER )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;

			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
				percent += 20;
			
			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
				percent += 20;

			if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}
			
			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}
					
			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_MENTOR) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}

			if( clBuf.IsHaveBuf(BUF_VALENTINEDAY) )
			{
				percent += 10;
			}



			// ũ��������Ʈ���� ���� ���ݷ� ����
			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. S]
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				cltServer* pclserver = (cltServer*)pclClient;
				cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );
				if (
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))	   == TRUE ||		//[����] ������ ���� �ϼ��� ���ݷ� ����. => 2008-6-12
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))	   == TRUE   //KHY - 1113 - ũ�������� �̺�Ʈ -ũ�������� �����߰�.
					)
					
					percent += 10;
			}

			siBufDamage = percent;
			CrysTalMinPer += percent;
			CrysTalMaxPer += percent;
		}
	}
	else if( gamemode == GAMEMODE_CLIENT )
	{
		if ( (pclchar) && ( 1 == pclchar->GetID()) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;

			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
			{
				percent += 20;
			}

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
			{
				percent += 20;
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}
			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}			
			if( clBuf.IsHaveBuf(BUF_MENTOR) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_VALENTINEDAY) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}
			
			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. C]
			cltCharClient* pclcharclient = (cltCharClient*)pclchar;
			for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
				if( pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))		 ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))	 ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		 ||		
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))	
					)				
				{
					percent += 10;
				}
			}

			siBufDamage = percent;
			CrysTalMinPer += percent;
			CrysTalMaxPer += percent;
		}
	}

	// ��Ʈ �����ۿ� ���� ���� ���ݷ� ���
	if( gamemode == GAMEMODE_SERVER )
	{
		// ��Ʈ ȿ���� ���� ���� ���ݷ� ���.
		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if( pclchar->m_siSetItemType )
				{
					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 );
				}
			}
		}
	}
	//Ŭ��
	else if( gamemode == GAMEMODE_CLIENT )
	{
		// ��Ʈ ȿ���� ���� ���� ���ݷ� ���.
		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if( pclchar->m_siSetItemType )
				{
					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_1 );
					
					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_2 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_3 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_4 );

					CrysTalMinPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 );
					CrysTalMaxPer += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_ATTACK, USE_SETITEM_5 );
				}
			}
		}
	}


	// ��Ű�� ���� ���ݷ� ��� 

	if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
	{
		if(gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if ( pclchar->pclFamily != NULL )
				{
					if ( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )
					{
						if(pclchar->pclFamily->GetOnChildrenNum() > 0 && pclchar->pclFamily->GetOnParentNum() > 0 )
						{
							cltServer* pclserver = (cltServer*)pclClient;
							SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
							if ( siPersonID > 0) 
							{
								SI32 siEndDateVary =	0	;
								SI32 siServerDateVary =	0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
								siServerDateVary = pclserver->pclTime->clDate.GetHourVary();
								if ( siEndDateVary>0 &&siServerDateVary>0  ) 
								{
									if(  siEndDateVary  >  siServerDateVary )
									{
										SI32 percent	= 0;
										SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel(siPersonID )	;// ������ ���� ����
										percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

										CrysTalMinPer += percent	;
										CrysTalMaxPer += percent	;
									}
								}
							}
						}
					}
				}
			}

		}
		else if(gamemode == GAMEMODE_CLIENT)
		{
			if ( pclchar && pclchar->GetID() == 1)
			{
				if(pclchar->pclFamily != NULL )
				{
					if ( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )
					{
						if(pclchar->pclFamily->GetOnChildrenNum() > 0 && pclchar->pclFamily->GetOnParentNum() > 0)
						{
							SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
							if ( siPersonID > 0 ) 
							{
								SI32 siEndDateVary = 0	;
								SI32 siClientDateVary = 0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
								siClientDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;

								if(   siEndDateVary >0 && siClientDateVary > 0 )
								{
									if ( siEndDateVary > siClientDateVary ) 
									{
										SI32 percent	= 0;
										SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( siPersonID )	;// ������ ���� ����
										percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

										CrysTalMinPer += percent	;
										CrysTalMaxPer += percent	;

									}
								}
							}
						}
					}
				}
			}
		}
	}


	//--------------------------------------
	// 101.8.4   ��Ī�� ���� ���ݷ� ���
	//--------------------------------------
	if ( gamemode == GAMEMODE_SERVER)
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
			{
				cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
				if ( pclunit )
				{
					CrysTalMinPer +=  pclunit->GetAttack();
					CrysTalMaxPer +=  pclunit->GetAttack();

					siNamingDamage = pclunit->GetAttack();
				}

			}
			else
			{
				siNamingDamage = 0;
			}
		}
	}
	else if ( gamemode == GAMEMODE_CLIENT )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) == 1 )
		{
			if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
			{
				cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
				if ( pclunit )
				{
					CrysTalMinPer +=  pclunit->GetAttack();
					CrysTalMaxPer +=  pclunit->GetAttack();
					
					siNamingDamage = pclunit->GetAttack();
				}

			}
			else
			{
				siNamingDamage = 0;
			}
		}
	}

	//--------------------------------------
	// 101.8.5   ��ų���� ���ⵥ���� ���
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	SI32 siDecMinMaxGapRate = 0;

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//---------------------------------------
		// ���������� ���� ������ ���
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_INCWEAAT;	}	break;

		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				CrysTalMinPer +=  siWeaponSkillRate;
				CrysTalMaxPer +=  siWeaponSkillRate;
			}
		}
		
		//---------------------------------------
		// ���� ������ ���� Min/Max���� ����
		siSkillUnique = 0;
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_AXE_DECGAP;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_AXE_DECGAP;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_DECGAP;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_AXE_DECGAP;	}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_AXE_DECGAP;	}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_AXE_DECGAP;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siDecMinMaxGapRate = siWeaponSkillRate;
			}
		}

		//---------------------------------------
		// ������� ����
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_PHYSICALATTACK );
			if ( 0 < siSkillMasterRate )
			{
				CrysTalMinPer +=  siSkillMasterRate;
				CrysTalMaxPer +=  siSkillMasterRate;
			}
		}

	}
	//--------------------------------------
	// 101.5  ���� ���� ������ ����.  - PvP�� ���� ����ó���� �ִ�.  -CrysTalMinPer,CrysTalMaxPer�� Ȯ�� ���� ��Ƽ� �ѹ��� ����Ѵ�.
	//--------------------------------------
	if(CrysTalMaxPer>0)				
		siTotalPHysicalMaxAttackDmg = maxDmg + (maxDmg *CrysTalMaxPer /100) ;
	else
		siTotalPHysicalMaxAttackDmg = maxDmg ;

	if(CrysTalMinPer>0)
		minDmg = minDmg + (minDmg *CrysTalMinPer /100) ;
	
	//----------------------------------------
	// ���� ������ ���� Min/Max���� ����
	SI32 siDamageGap = siTotalPHysicalMaxAttackDmg - minDmg;
	if ( (0 < siDamageGap) && (0 < siDecMinMaxGapRate) )
	{
		minDmg += (siDamageGap * siDecMinMaxGapRate / 100);
	}

	// �ּ� ��������, �ִ� �������� ���� �� ����.
	SI16 siCurPHysicalMaxAttackDmg = 0;
	if(minDmg >siTotalPHysicalMaxAttackDmg)
	{
		siCurPHysicalMaxAttackDmg = siTotalPHysicalMaxAttackDmg;
	}
	else
		siCurPHysicalMaxAttackDmg = minDmg;

    siTotalPHysicalMinAttackDmg = siCurPHysicalMaxAttackDmg;

	SI32 siCurseAttack = 0;
	if( pclchar )
	{
		if( pclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_ATTACK, pclchar->GetID() ) )
		{
			siTotalPHysicalMinAttackDmg += (siTotalPHysicalMinAttackDmg * pclchar->m_clCharCurseEffect.GetPara()) / 100;
			siTotalPHysicalMaxAttackDmg += (siTotalPHysicalMaxAttackDmg * pclchar->m_clCharCurseEffect.GetPara()) / 100;
		}

		if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT))
		{
			siTotalPHysicalMinAttackDmg += 1 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siTotalPHysicalMinAttackDmg * 5) / 100 : 0;
			siTotalPHysicalMaxAttackDmg += 1 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siTotalPHysicalMaxAttackDmg * 5) / 100 : 0;
		}
	}

	//// [����] ��Ʋ �ξ��� �Ŀ��� ���¶��
	//if( (pclchar) && ( true == pclchar->bBattleRoyalPowerupMode))
	//{
	//	siTotalPHysicalMinAttackDmg = siTotalPHysicalMinAttackDmg * 2;
	//	siTotalPHysicalMaxAttackDmg = siTotalPHysicalMaxAttackDmg * 2;
	//}
}

////  102. ���� ���ݷ� 
void cltParametaBox::SetMagicalAttackDemage(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo , bool *bSwitch)
{
	SI32 totalMag = clTotalBA.GetMag();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 102.1 �����Ǿ��ִ� �⺻ ������  - ĳ���Ϳ� ���� ���ҽ��� ����. - ������ ����.
	//--------------------------------------

	//--------------------------------------
	// 102.2  ���°� ������ ���� ���� ������ ����.
	//--------------------------------------
	SI16 minDmg = 0;
	SI16 maxDmg = 0;

	minDmg = (totalMag *(4000 + (level*50))/20000);
	maxDmg = (totalMag *(6000 + (level*50))/20000);

	//--------------------------------------
	// 102.3  ��� ���� ���� ������ ����.  - ���� ���� % ��.
	//--------------------------------------
	SI16 EminPer = 0;
	SI16 EmaxPer = 0;

	if(pclitemlist)
	{
		if (pclClient->IsCountrySwitch(Switch_StatusBug)) 
		{
			//minDmg = pclItemManager->GetAddMagicalDamage(pclitemlist, activeweaponpos); 
			//maxDmg = pclItemManager->GetAddMagicalDamage(pclitemlist, activeweaponpos);
		}
		else
		{
			EminPer = (SI16)pclItemManager->GetAddMagicalMinDamage(pclitemlist, activeweaponpos,pclchar);  
			EmaxPer = (SI16)pclItemManager->GetAddMagicalMaxDamage(pclitemlist, activeweaponpos,pclchar);
		}

		if(EminPer >0)
			siEquipMagicalMinAttackDmg = EminPer;
		else
			siEquipMagicalMinAttackDmg = 0;

		if(EmaxPer >0)
			siEquipMagicalMaxAttackDmg = EmaxPer;
		else
			siEquipMagicalMaxAttackDmg = 0;
	}

	// PCK : ����ġ�� Ÿ�� ���� ��� �������ݷ� + 100�� ���ش�.
	// [���] ��ȣ�� Ÿ�� ���� ��� ���� ���ݷ� + 100�� ���ش�. (09.05.15)
	// [���] ������Ʈ�� Ÿ�� ���� ��� ���� ���ݷ� + 100�� ���ش�. (09.07.30)
	// [����] ������� Ÿ�� ���� ��� ���� ���ݷ� + 100�� ���ش�. (09.12.31)
	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if(pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_FIREHATCH ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_BAPHOMET ||
			pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_SASURI)
		{
			minDmg += 100;
			maxDmg += 100;
		}
	}	

	//--------------------------------------
	// 101.5.1  ����ȿ���� ���� ���.
	//--------------------------------------
	*bSwitch = false;	
	if(siGeneralDamage)
	{		
		//-------------------------------
		// ���Ӽ����� ��쿡�� ����ȿ���� �ð��� Ȯ���Ѵ�. 
		//-------------------------------
		if(gamemode == GAMEMODE_SERVER)
		{
			if(TABS(pclClient->CurrentClock - dwGeneralDamageClock) > 10000)
			{
				siGeneralDamage			= 0;				
				dwGeneralDamageClock	= 0;

				*bSwitch = true;
			}
		}

		minDmg = minDmg * (100 + siGeneralDamage ) / 100;
		maxDmg = maxDmg * (100 + siGeneralDamage ) / 100;
	}

	//--------------------------------------
	// 101.5.2 ��ȥ ���� ������ ���
	//--------------------------------------
	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) && (pclchar->IsMarried()) )	bMarriageCondition = true;
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) && (pclchar->IsMarried()) )		bMarriageCondition = true;
		}

		if ( (pclClient->m_pclMarriageMgr) && (true == bMarriageCondition) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
		{
			SI16 siMarriageValue = (SI16)pclClient->m_pclMarriageMgr->GetTotalAttackAbilityValue( pclchar->pclMarriage->GetLoveLevel() );
			if ( 0 < siMarriageValue )
			{
				minDmg +=  siMarriageValue;
				maxDmg +=  siMarriageValue;
			}
		}
	}

	// Ȱ������ ���� Attack���
	if(gamemode == GAMEMODE_SERVER)
	{
		if ( pclchar && IsPC( pclchar->GetID() ) && pclchar->pclCI->clBI.bCombatService )
		{
			EminPer += 30 ;
			EmaxPer += 30 ;
		}
	}
	else if(gamemode == GAMEMODE_CLIENT)
	{
		if ( pclchar && pclchar->GetID() == 1 && pclchar->pclCI->clBI.bCombatService )
		{
			EminPer += 30 ;
			EmaxPer += 30 ;
		}		
	}
	//Ŭ��
	//--------------------------------------
	// 101.5.1  ������ ���� ���ݷ� ���
	//--------------------------------------
	if( gamemode == GAMEMODE_SERVER )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;


			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
				percent += 20;
			
			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
				percent += 20;


			if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}
		
			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}


			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
			{
				percent += 10;
			}
			
			if( clBuf.IsHaveBuf(BUF_MENTOR) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}
			

			// ũ��������Ʈ���� ���� ���ݷ� ����
			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. S]
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				cltServer* pclserver = (cltServer*)pclClient;
				cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );
				if (pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) == TRUE ||
					pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")))	   == TRUE ||
					pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))   == TRUE ||
					pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))	   == TRUE ||
					pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))	   == TRUE	||
					pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))	   == TRUE
					)
					
					percent += 10;
			}

			siBufDamage = percent;
			EminPer += percent;
			EmaxPer += percent;
		}

	}
	else if( gamemode == GAMEMODE_CLIENT )
	{
		if ( (pclchar) && ( 1 == pclchar->GetID()) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;

			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
			{
				percent += 20;
			}

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
			{
				percent += 20;
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

            if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}


			if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
			{
				percent += 10;
			}

			if( clBuf.IsHaveBuf(BUF_MENTOR) )
			{
				percent += 10;
			}
			
			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}

			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. C]
			cltCharClient* pclcharclient = (cltCharClient*)pclchar;
			for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
				if( pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))		 ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))	 ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		 ||
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")) ||		
					pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))		 
					)				
				{
					percent += 10;
				}
			}
			
			siBufDamage = percent;
			EminPer += percent;
			EmaxPer += percent;
		}
	}

	//--------------------------------------
	// 101.5.3  ��Ʈ �����ۿ� ���� ���ݷ� ���
	//--------------------------------------
	/*
	if( gamemode == GAMEMODE_SERVER )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			// ��Ʈ ȿ���� ���� ���� ���ݷ� ���.
			if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				if( pclchar->m_siSetItemType )
				{
					SI16 siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_1 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_2 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_3 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_4 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_5 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;
				}
			}

			// �ҷ��� ��Ʈ�� ������ ���������� 10% ����
			else if( pclchar->m_siSetItemType == HALLOWEEN1_SETITEM 
				|| pclchar->m_siSetItemType == HALLOWEEN2_SETITEM
				|| pclchar->m_siSetItemType == HALLOWEEN3_SETITEM
				|| pclchar->m_siSetItemType == HALLOWEEN4_SETITEM)
			{
				EminPer += 10 ;
				EmaxPer += 10 ;
			}
		}
	}
	//Ŭ��
	else if( gamemode == GAMEMODE_CLIENT )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) == 1 )
		{
			// ��Ʈ ȿ���� ���� ���� ���ݷ� ���.
			if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				if( pclchar->m_siSetItemType )
				{
					SI16 siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_1 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_2 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_3 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_4 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;

					siAddValue = pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_ATTACK, USE_SETITEM_5 );
					EminPer += siAddValue;
					EmaxPer += siAddValue;
				}
			}

			// �ҷ��� ��Ʈ�� ������ ���������� 10% ����
			else if(   pclchar->m_siSetItemType == HALLOWEEN1_SETITEM 
				|| pclchar->m_siSetItemType == HALLOWEEN2_SETITEM
				|| pclchar->m_siSetItemType == HALLOWEEN3_SETITEM
				|| pclchar->m_siSetItemType == HALLOWEEN4_SETITEM)
			{
				EminPer += 10 ;
				EmaxPer += 10 ;
			}
		}
	}
	*/


	// ��Ű�� ���� ���ݷ� ��� 

	if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
	{
		if(gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if ( pclchar->pclFamily != NULL )
				{
					if ( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )
					{
						if(pclchar->pclFamily->GetOnChildrenNum() > 0 && pclchar->pclFamily->GetOnParentNum() > 0 )
						{
							cltServer* pclserver = (cltServer*)pclClient;
							SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
							if ( siPersonID > 0) 
							{
								SI32 siEndDateVary =	0	;
								SI32 siServerDateVary =	0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
								siServerDateVary = pclserver->pclTime->clDate.GetHourVary();
								if ( siEndDateVary>0 &&siServerDateVary>0  ) 
								{
									if(  siEndDateVary  >  siServerDateVary )
									{
										SI32 percent	= 0;
										SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel(siPersonID )	;// ������ ���� ����
										percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

										EminPer += percent	;
										EmaxPer += percent	;
									}
								}
							}
						}
					}
				}
			}

		}
		else if(gamemode == GAMEMODE_CLIENT)
		{
			if ( pclchar && pclchar->GetID() == 1)
			{
				if(pclchar->pclFamily != NULL )
				{
					if ( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )
					{
						if(pclchar->pclFamily->GetOnChildrenNum() > 0 && pclchar->pclFamily->GetOnParentNum() > 0)
						{
							SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
							if ( siPersonID > 0 ) 
							{
								SI32 siEndDateVary = 0	;
								SI32 siClientDateVary = 0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
								siClientDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;

								if(   siEndDateVary >0 && siClientDateVary > 0 )
								{
									if ( siEndDateVary > siClientDateVary ) 
									{
										SI32 percent	= 0;
										SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( siPersonID )	;// ������ ���� ����
										percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

										EminPer += percent	;
										EmaxPer += percent	;

									}
								}
							}
						}
					}
				}
			}
		}
	}


	//--------------------------------------
	// 101.5.3  ��ų�� ���� ���� ���ݷ� ���
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		// ���������� ���� ���� ���ݷ� ���
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCMAGAT;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_INCMAGAT;	}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_INCMAGAT;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_INCMAGAT;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				EminPer += siWeaponSkillRate;
				EmaxPer += siWeaponSkillRate;
			}
		}
		
		// ������� ���ο� ���� ���� ���ݷ� ���
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_MAGICALATTACK );
			if ( 0 < siSkillMasterRate )
			{
				EminPer +=  siSkillMasterRate;
				EmaxPer +=  siSkillMasterRate;
			}
		}

	}

	// ��ȣ���ɿ� ���� �������ݷ� ���
	/*
	if(pclClient->IsCountrySwitch(Switch_SoulGuard))
	{
		if(pclClient->GameMode == GAMEMODE_SERVER)
		{
			if((pclchar != NULL))
			{
				if(pclchar->IsSoulGuardStatusOut() == TRUE && pclchar->pclSoulGuard->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SOULGUARD_PUMPKIN")))
				{		
					EminPer += 10	;
					EmaxPer += 10	;
				}
			}
		}
		else if(pclClient->GameMode == GAMEMODE_CLIENT)
		{
			if((pclchar) && (1 == pclchar->GetID()))
			{
				if(pclchar->IsSoulGuardStatusOut() == TRUE && pclchar->pclSoulGuard->GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_SOULGUARD_PUMPKIN")))
				{		
					EminPer += 10	;
					EmaxPer += 10	;
				}
			}
		}	
	}
	*/
	
	//--------------------------------------
	// 102.4  ���� ���� ������ ����.  - ���� ���� �ߵ��� �÷��� �Ǵ� ���̴�. - PvP�� ����Ǵ� ���� �ߵ��� ����(?)
	//--------------------------------------
	if(EmaxPer>0)	
		siTotalMagicalMaxAttackDmg = (SI16)(maxDmg + (maxDmg *EmaxPer / 100));
	else
		siTotalMagicalMaxAttackDmg = (SI16)maxDmg ;

	if(EminPer >0)
		minDmg = (SI16)(minDmg + (minDmg *EminPer / 100));

	// �ּ� ��������, �ִ� �������� ���� �� ����.
	SI16 siCurMagicalMinAttackDmg = 0;
	if(minDmg >siTotalMagicalMaxAttackDmg)
		siCurMagicalMinAttackDmg = siTotalMagicalMaxAttackDmg;
	else
		siCurMagicalMinAttackDmg = minDmg;	

	SI32 siCurseAttack = 0;
	
	siTotalMagicalMinAttackDmg = siCurMagicalMinAttackDmg;

	if( pclchar )
	{
		if( pclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_ATTACK, pclchar->GetID() ) )
		{
			siTotalMagicalMinAttackDmg += (siTotalMagicalMinAttackDmg * pclchar->m_clCharCurseEffect.GetPara()) / 100;
			siTotalMagicalMaxAttackDmg += (siTotalMagicalMaxAttackDmg * pclchar->m_clCharCurseEffect.GetPara()) / 100;
		}

		if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT))
		{
			siTotalMagicalMinAttackDmg += 4 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siTotalMagicalMinAttackDmg * 5) / 100 : 0;
			siTotalMagicalMaxAttackDmg += 4 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siTotalMagicalMaxAttackDmg * 5) / 100 : 0;
		}
	}

	

	// [����] ��Ʋ �ξ��� �Ŀ��� ���¶��
	/*if( (pclchar) && (true == pclchar->bBattleRoyalPowerupMode) )
	{
		siTotalMagicalMinAttackDmg = siTotalMagicalMinAttackDmg * 2;
		siTotalMagicalMaxAttackDmg = siTotalMagicalMaxAttackDmg * 2;
	}*/
}

////  103. ���� ���߷� 
void cltParametaBox::SetPhysicalHitRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltIdentity* pclidentityinfo, cltPSkillInfo* pclskillinfo)
{
	if( NULL == pclchar ) return; 

	SI32 totalHnd = clTotalBA.GetHnd();
	SI32 level = pclIP->GetLevel();
	
	//SI32 WeaponDefaultHitRate	= pclitemlist[activeweaponpos].GetDefaultHitRate(pclItemManager); // �Ⱦ���� ����.

	//--------------------------------------
	// 103.1 NPC�� ��NPC�� �����Ѵ�.
	//--------------------------------------
	if(bnpc == false)
	{
		//--------------------------------------
		// 103.2 ������� ���� ���߷� ����� ���Ѵ�. - NPC�� ��� �������� ����.
		//--------------------------------------
		SI16 EHitRate = 0;

		if(pclitemlist)
		{
			EHitRate = pclItemManager->GetEquipCrystalPhysicalHitRate(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ���߷� ���  - % 
		}

		if(EHitRate>0)
			siEquipPHysicalHitRate = EHitRate;
		else
			siEquipPHysicalHitRate = 0;

		//KHY - 1220 - ���Žý���.
		if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
		{
			switch(siAttackType)
			{				
				case ATTACKTYPE_SPEAR :
				case ATTACKTYPE_BOW :
					siAddPHysicalHitRate = (SI32)(siTransFormSyc/20);
					break;
			}
		}
	}
	else if(pclidentityinfo && pclidentityinfo->siIdentity)	
	{
		//--------------------------------------
		// 103.3 Identity �� �����ϴ� Ư�� ĳ������ ��� , ���߷� ������
		//--------------------------------------
		switch(pclidentityinfo->siIdentity)
		{
		case IDENTITY_CASTLE:				siAddPHysicalHitRate = 1000; break; 
		case IDENTITY_VILLAGEGOD:			siAddPHysicalHitRate = 500;	 break;
		case IDENTITY_VILLAGEGOD_SUMMON:	siAddPHysicalHitRate = 200;	 break;
		case IDENTITY_VILLAGEHUNT:			siAddPHysicalHitRate = 200;	 break;
		default:					break;
		}
	}

	//--------------------------------------
	// 103.4 ��Ʈ�����ۿ� ���� ���� ���߷� ���
	//--------------------------------------
	SI16 siAddPHysicalHitRateSetItem = 0;				// ��Ʈ �����ۿ� ���� ���� ���߷�. 
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		//[����] ��Ʈ ������ ���� ���� ���߷� ����.
		if( pclchar && pclchar->m_siSetItemType )
		{	
			siAddPHysicalHitRateSetItem += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_1 );
			siAddPHysicalHitRateSetItem += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_2 );
			siAddPHysicalHitRateSetItem += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_3 );
			siAddPHysicalHitRateSetItem += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_4 );
			siAddPHysicalHitRateSetItem += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_5 );
		}
	}

	//--------------------------------------
	// 103.5 ��ų�� ���� ���� ���߷� ���
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	SI16 siAddWeaponSkillHitRate = 0;
	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 103.6 ��������
		//--------------------------------------
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_GUN_INCPHYAR;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_GUN_INCPHYAR;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_GUN_INCPHYAR;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_GUN_INCPHYAR;		}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_INCPHYAR;			}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_GUN_INCPHYAR;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siAddWeaponSkillHitRate	+= siWeaponSkillRate;
			}
		}

		//--------------------------------------
		// 103.7 ������� ����
		//--------------------------------------
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI16 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_PHYSICALHIT );
			if ( 0 < siSkillMasterRate )
			{
				siAddWeaponSkillHitRate += siSkillMasterRate;
			}
		}

	}

	//--------------------------------------
	// 103.8 ���� ���� ��� ����.  - �⺻��
	//--------------------------------------
	SI16 tempHitRateRank = 0;
	
	if((totalHnd >0) && (level > 0))
		tempHitRateRank = ((totalHnd *3) +level) + siAddPHysicalHitRate;
	else
		tempHitRateRank = 0;


	//--------------------------------------
	// 103.9  ���� ���� ��� ����. - ��� ���� ������.
	//--------------------------------------
	if ( (siEquipPHysicalHitRate > 0) || (siAddPHysicalHitRateSetItem > 0) || (siAddWeaponSkillHitRate > 0) ) 
		siPHysicalHitRateRank = tempHitRateRank + (tempHitRateRank * (siEquipPHysicalHitRate + siAddPHysicalHitRateSetItem + siAddWeaponSkillHitRate) / 100); //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ���Ѵ�.
	else
		siPHysicalHitRateRank = tempHitRateRank ; //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ����

	//--------------------------------------
	// ��Ÿ: ���߷��� �������� GetHitRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------

}

////  104. ���� ���߷� 
void cltParametaBox::SetMagicalHitRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltIdentity* pclidentityinfo, cltPSkillInfo* pclskillinfo)
{
	if( NULL == pclchar ) return; 

	SI32 totalWis = clTotalBA.GetWis();
	SI32 level = pclIP->GetLevel();

	//SI32 WeaponDefaultHitRate	= pclitemlist[activeweaponpos].GetDefaultHitRate(pclItemManager); // �Ⱦ���� ����.

	//--------------------------------------
	// 104.1 NPC�� ��NPC�� �����Ѵ�.
	//--------------------------------------
	if(bnpc == false)
	{
		//--------------------------------------
		// 104.2 ������� ���� ���߷� ����� ���Ѵ�. - NPC�� ��� �������� ����.
		//--------------------------------------
		SI16 EHitRate = 0;

		if(pclitemlist)
		{
			EHitRate = pclItemManager->GetEquipCrystalMagicalHitRate(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ���߷� ���  - % 
		}

		if(EHitRate>0)
			siEquipMagicalHitRate = EHitRate;
		else
			siEquipMagicalHitRate = 0;
	}
	else if(pclidentityinfo && pclidentityinfo->siIdentity)	
	{
		//--------------------------------------
		// 104.3 Identity �� �����ϴ� Ư�� ĳ������ ��� , ���߷� ������
		//--------------------------------------
		switch(pclidentityinfo->siIdentity)
		{
		case IDENTITY_CASTLE:				siAddMagicalHitRate = 1000; break; 
		case IDENTITY_VILLAGEGOD:			siAddMagicalHitRate = 500;	 break;
		case IDENTITY_VILLAGEGOD_SUMMON:	siAddMagicalHitRate = 200;	 break;
		case IDENTITY_VILLAGEHUNT:			siAddMagicalHitRate = 200;	 break;
		default:					break;
		}
	}


	//--------------------------------------
	// 104.4 [����] ��Ʈ ������ ���� ���� ���߷� ����.
	//--------------------------------------
	SI32 AddSetItemHitRate = 0;
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		//[����] ��Ʈ ������ ���� ���� ���߷� ����.
		if( pclchar && pclchar->m_siSetItemType )
		{	
			AddSetItemHitRate += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_1 );
			AddSetItemHitRate += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_2 );
			AddSetItemHitRate += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_3 );
			AddSetItemHitRate += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_4 );
			AddSetItemHitRate += pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HIT_RATE, USE_SETITEM_5 );
		}
	}

	//--------------------------------------
	// 104.5 ��ų�� ���� ���� ���߷� ���
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	SI16 siAddWeaponSkillHitRate = 0;
	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 104.6 ������� ����
		//--------------------------------------
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		SI32 siSkillUnique		= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI16 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_MAGICALHIT );
			if ( 0 < siSkillMasterRate )
			{
				siAddWeaponSkillHitRate += siSkillMasterRate;
			}
		}
	}

	//--------------------------------------
	// 104.3 ���� ���� ��� ����.  - �⺻��
	//--------------------------------------
	SI16 tempHitRateRank = 0;

	if((totalWis >0) && (level > 0))
		tempHitRateRank = ((totalWis* 2)+level);
	else
		tempHitRateRank = 0;

	// %
	SI32 silastHiRate = siEquipMagicalHitRate + AddSetItemHitRate + siAddWeaponSkillHitRate;

	//--------------------------------------
	// 103.6  ���� ���� ��� ����. . - ��� ���� ������.
	//--------------------------------------
	if (silastHiRate >0)
		siMagicalHitRateRank = tempHitRateRank + (tempHitRateRank * silastHiRate /100); //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ���Ѵ�.
	else
		siMagicalHitRateRank = tempHitRateRank ; //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ����


	//--------------------------------------
	// ��Ÿ: ���߷��� �������� GetHitRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------

}

////  105. ���� �����
void cltParametaBox::SetPhysicalDefensiveRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo, bool *bSwitch, SI16 siDefenseWearStoneNum)
{
	SI32 totalHnd = clTotalBA.GetHnd();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 105.1 �����Ǿ��ִ� �⺻ ����  - ĳ���Ϳ� ���� ���ҽ��� ����.
	//--------------------------------------
	SI32 DefaultAC = 0;

	if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (pclitemlist) && 
		( pclitemlist[PERSONITEM_HELMET].siUnique || pclitemlist[PERSONITEM_ARMOUR].siUnique || pclitemlist[PERSONITEM_BELT].siUnique || 
		pclitemlist[PERSONITEM_SHOES].siUnique || pclitemlist[PERSONITEM_MANTLE].siUnique ) 

	)
	{	
		// ����� ������ ���� ������ ���ƾ� �⺻ ������ ����
		if ( pclchar->pclCI->clIP.GetLevel() == siDefenseWearStoneNum )
		{
			DefaultAC = pclKI->clDefaultWeaponInfo.GetDefaultAC(); 
		}
	}
	else if((pclidentityinfo) && pclidentityinfo->siIdentity == IDENTITY_GMCREATE_MONSTER)
	{
		DefaultAC = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultAC();
	}
	// ��ȯ���� �ƴϰų� ��� ���ٸ�
	else
	{
		DefaultAC = pclKI->clDefaultWeaponInfo.GetDefaultAC(); 
	}


	//--------------------------------------
	// 105.2  �����ֿ� ���� ���� ���� ����.
	//--------------------------------------

	siHndPHysicalDefensive = (totalHnd+level)*60/100 ;

	//--------------------------------------
	// 105.3  ��� ���� ���� ���� ����. 
	//--------------------------------------
	SI16 Edefansive = 0;
	SI32 CrysTalPer = 0;

	// Edefansive = ���� ��� ����.
	// CrysTalPer = ����ü�����Ͽ� �ö󰡾� �ϴ� �ۼ�Ʈ.
	
	if(pclitemlist)
	{
		Edefansive = (SI16)pclItemManager->GetEquipCrystalPhysicalDefensiveRate(pclitemlist, activeweaponpos,pclchar , &CrysTalPer); 

		if(Edefansive>0)
			siEquipPHysicalDefensive = Edefansive;
		else
			siEquipPHysicalDefensive = 0;
	}

	//--------------------------------------
	// 105.4.1 ���� ���� ���� .  
	//--------------------------------------	
	SI16 sTransFormAC = 0; // ���ſ� ���ſ� ���� �ö󰡴� ����.
	
	if ( pclchar ) 
	{
		//KHY - 0124 - ��í����- ���� ���� ������.
		if(pclchar->clTransFormInfo.bTransFormMode ==true)
		{
			if( (pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAMAN"))			||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAGIRL"))			||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATMELEE"))			||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATRANGE"))			||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE"))	||	// �����
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE"))	||	// �˻罺�Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE"))	||	// �ųʽ��Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYMELEE"))		||	// �������Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYRANGE"))		||	// �������Ǹ�(��)
				// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICERANGE"))			||	// ���� ����
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICEMELEE"))				// �罺��ġ
			  )		
			{
				// ���� ����.
				sTransFormAC = 80; // �⺻ ����.
				SI32 temState = 0;
				temState = sTransFormAC * (siTransFormSyc/2) / 100;

				sTransFormAC = sTransFormAC + temState; // ��ũ���� ������.
			}
		}
	}

	//--------------------------------------
	// 105.5  ��ȯ�� ��񼮿� ���� ���� ��°�
	//--------------------------------------
	SI16 siDefenseWearStoneAC = 0;

	if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (SUMMON_EQUIP_LIMITMINLEVEL < siDefenseWearStoneNum) )
	{
		REAL32 siDefenseWearStoneIncreasePercent = (siDefenseWearStoneNum - SUMMON_EQUIP_LIMITMINLEVEL) * 1.0;

		siDefenseWearStoneAC = (SI16)((REAL32)(siEquipPHysicalDefensive/100) * siDefenseWearStoneIncreasePercent);
	}

	//--------------------------------------
	// 105.6  ��ȥ ���� ���� ��°�
	//--------------------------------------
	SI16 siDefenseMarriageAC = 0;

	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) && (pclchar->IsMarried()) )	bMarriageCondition = true;
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) && (pclchar->IsMarried()) )		bMarriageCondition = true;
		}

		if ( (pclClient->m_pclMarriageMgr) && (true == bMarriageCondition) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
		{
			SI16 siMarriageValue = (SI16)pclClient->m_pclMarriageMgr->GetTotalDefenseAbilityValue( pclchar->pclMarriage->GetLoveLevel() );
			if ( 0 < siMarriageValue )
			{
				siDefenseMarriageAC = siMarriageValue;
			}
		}
	}
	SI32 siCookieEffect = 0 ;
	// ��Ű ȿ��
	if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) )
			{
				if( pclchar->pclFamily != NULL )
				{
					if( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)
					{
						if(pclchar->pclFamily->GetOnParentNum() > 0 )
						{
							cltServer* pclserver = (cltServer*)pclClient;
							SI32 siEndDateVary = 0	;
							SI32 siNowDateVary = 0	;
							SI32 siCookieLevel =	0	;
							SI32 siEffect =	0	;
							siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
							siNowDateVary = pclserver->pclTime->clDate.GetHourVary()	;
							if(  siEndDateVary > 0 && siNowDateVary > 0 && siEndDateVary > siNowDateVary )
							{
								siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;
								siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;			

								siCookieEffect	 = siEffect	; // ������ų %
							}

						}
					}
				}	
			}
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) )
			{
				if( pclchar->pclFamily != NULL )
				{
					if( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)
					{
						if(pclchar->pclFamily->GetOnParentNum() > 0  )
						{
							SI32 siEndDateVary =	0	;
							SI32 siNowDateVary =	0	;
							SI32 siCookieLevel =	0	;
							SI32 siEffect =	0	;

							siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
							siNowDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;
							if(  siEndDateVary > 0 && siNowDateVary > 0 &&siEndDateVary > siNowDateVary )
							{
								
								siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;
								siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;
								siCookieEffect	 = siEffect	; // ������ų %
							}

						}
					}
				}	
			}
		}

	}	
	//----------------------------------------------------------------
	// 105.7 Ż��(��ȣ)�� Ÿ�� �Ǹ� ���������� 100 ����Ѵ�.(09.05.13)
	//----------------------------------------------------------------
	SI16	siPhysicalDefenseHorseAC = 0;

	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if(pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER)
		{
			siPhysicalDefenseHorseAC = 100;
		}
	}

	//--------------------------------------
	// 105.8  ��Ÿ ���� ���� ����.  
	//--------------------------------------
	SI32 temPhysicalDFensive = 0;
	
	temPhysicalDFensive = siHndPHysicalDefensive + siEquipPHysicalDefensive + DefaultAC + sTransFormAC 
		+ siDefenseWearStoneAC + siDefenseMarriageAC + siPhysicalDefenseHorseAC  ; // ������ + ���  + �⺻ + ���� + ��ȯ����� + ��ȥ + Ż��(��ȣ)

	SI32 etcDefansiveFer = 0; // ��Ÿ ������ ���� ���� ���밪 �ջ�.		
	
	etcDefansiveFer = etcPhysicalDefensiveRate( pclitemlist, activeweaponpos, pclchar , &CrysTalPer ,gamemode,pclskillinfo ,bSwitch);

	//--------------------------------------
	// 105.9  ���� ���� ���� ����.   - CrysTalPer = % �� ���� ��°� �ջ�.
	//--------------------------------------
	if( etcDefansiveFer >0 && siCookieEffect <=0 )
	{
		siPHysicalDefensive = temPhysicalDFensive + (temPhysicalDFensive * etcDefansiveFer / 100);
	}
	else if ( etcDefansiveFer <= 0 && siCookieEffect >0 )	// ��Ű ����Ʈ 
	{
		siPHysicalDefensive = temPhysicalDFensive + (temPhysicalDFensive * siCookieEffect / 100) ;
	}
	else if ( etcDefansiveFer > 0 && siCookieEffect > 0 )	// ��Ű ����Ʈ 
	{
		siPHysicalDefensive = temPhysicalDFensive + (temPhysicalDFensive * (etcDefansiveFer + siCookieEffect) / 100) ;
	}
	else
		siPHysicalDefensive = temPhysicalDFensive;

	if( pclchar )
	{
		if( pclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_DEFENSE, pclchar->GetID() ) )
		{
			siPHysicalDefensive += (siPHysicalDefensive * pclchar->m_clCharCurseEffect.GetPara()) / 100; 
		}

		if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT))
		{
			siPHysicalDefensive += 2 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siPHysicalDefensive * 5) / 100 : 0;
		}
	}

	

	//--------------------------------------
	// ��Ÿ: ������� �������� GetDefensiveRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------	
}

// ����� ��Ÿ ���� ó��.
SI16 cltParametaBox::etcPhysicalDefensiveRate(cltItem* pclitemlist, SI16 activeweaponpos,cltCharCommon* pclchar,  SI32 * DefensivePer , SI32 gamemode ,cltPSkillInfo*	pclskillinfo, bool *bSwitch)
{
	SI16 temPhysicalDRate = 0; // �ۼ�Ʈ ���̴�.


	//--------------------------------------
	// 105.4.1  ���� ����- ����ü�� ���� ����.
	//--------------------------------------
	temPhysicalDRate += *DefensivePer;

	//[����] ��Ʈ ȿ���� ���� ���� ���.
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			if( pclchar->m_siSetItemType ) 
			{
				temPhysicalDRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_DEFENSIVE, USE_SETITEM_1);
				temPhysicalDRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_DEFENSIVE, USE_SETITEM_2);
				temPhysicalDRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_DEFENSIVE, USE_SETITEM_3);
				temPhysicalDRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_DEFENSIVE, USE_SETITEM_4);
				temPhysicalDRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_DEFENSIVE, USE_SETITEM_5);
			}
		}
	}
	else if( pclchar && ( pclchar->m_siSetItemType == BOY_SULBIM_SETITEM  || pclchar->m_siSetItemType == GIRL_SULBIM_SETITEM ) )
	{
		temPhysicalDRate += 20;
	}

	//--------------------------------------
	// 105.4.3 ����ȿ���� ���� AC���. 
	//--------------------------------------	
	*bSwitch = false;
	if(siGeneralAC)
	{
		//-------------------------------
		// ���Ӽ����� ��쿡�� ����ȿ���� �ð��� Ȯ���Ѵ�. 
		//-------------------------------
		if(gamemode == GAMEMODE_SERVER)
		{
			if(TABS(pclClient->CurrentClock - dwGeneralACClock) > 10000)
			{
				siGeneralAC			= 0;
				dwGeneralACClock	= 0;

				*bSwitch = true;
			}
		}
		temPhysicalDRate +=  siGeneralAC;
	}

	//--------------------------------------
	// 105.4.4 Ȱ������ ���� AC���
	//--------------------------------------	
	if(gamemode == GAMEMODE_SERVER)
	{
		if ( pclchar && IsPC( pclchar->GetID() ) && pclchar->pclCI->clBI.bCombatService )
		{
			temPhysicalDRate += 30;
		}
	}
	else if(gamemode == GAMEMODE_CLIENT)
	{
		if ( pclchar && pclchar->GetID() == 1 && pclchar->pclCI->clBI.bCombatService )
		{
			temPhysicalDRate += 30;
		}		
	}

	//--------------------------------------
	// 105.4.5  ������ ���� AC ���
	//--------------------------------------
	if( gamemode == GAMEMODE_SERVER )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent =0;
			SI16 add = 0;

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
				percent += 20;

			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
				percent += 20;

			if( clBuf.IsHaveBuf(BUF_MENTOR) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_VALENTINEDAY) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_DEFENSEUP) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_DEFENSEUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_DEFENSEUP30) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_DEFENSEUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}
			
			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}
			
			// ũ��������Ʈ���� ���� ���� ����
			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. S]
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				cltServer* pclserver = (cltServer*)pclClient;
				cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );

				if (	
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))	   == TRUE || 	
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))	   == TRUE || 	
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))	   == TRUE		//[����] ������ ���� �ϼ��� ���� ����. => 2008-6-12
					)
					percent += 10;
			}

			siBufAC = percent;
			temPhysicalDRate += percent;
		}
	}
	else if( gamemode == GAMEMODE_CLIENT )
	{
		if ( (pclchar) && ( 1 == pclchar->GetID()) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			SI16 percent = 0 ;
			SI16 add = 0;

			if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
				percent += 20;

			if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
				percent += 20;
			
			if( clBuf.IsHaveBuf(BUF_MENTOR) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_VALENTINEDAY) )
				percent += 10;

			if( clBuf.IsHaveBuf(BUF_DEFENSEUP) )
			{
				SI32 siBufIndex = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_DEFENSEUP);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_DEFENSEUP30) )
			{
				SI32 siBufIndex = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_DEFENSEUP30);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
					percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
			}

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					percent += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}

			// ũ��������Ʈ���� ���� ���� ����
			//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. C]
			cltCharClient* pclcharclient = (cltCharClient*)pclchar;
			for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
					if( 
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))   ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))	 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))				//[����] ������ ���� �ϼ��� ���� ����. => 2008-6-12
					)
					
				{
					percent += 10;
				}
			}	
			siBufAC = percent;
			temPhysicalDRate += percent;
		}
	}

	//--------------------------------------
	// 105.4.6 ��Ī�� ���� ���� ���
	//--------------------------------------
	if ( gamemode == GAMEMODE_SERVER)
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
			{
				cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
				if ( pclunit )
				{
					temPhysicalDRate +=  pclunit->GetDefense();
					siNamingAC = pclunit->GetDefense();
				}
			}
			else
			{
				siNamingAC = 0;
			}
		}
	}
	else if ( gamemode == GAMEMODE_CLIENT )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) == 1 )
		{
			if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
			{
				cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
				if ( pclunit )
				{
					temPhysicalDRate += pclunit->GetDefense();
					siNamingAC = pclunit->GetDefense();
				}
			}
			else
			{
				siNamingAC = 0;
			}
		}
	}

	//--------------------------------------
	// 105.4.7 ��ų�� ���� �������� ���
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 105.4.8 ��������
		//--------------------------------------
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_INCAC;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				temPhysicalDRate += siWeaponSkillRate;
			}
		}

		//--------------------------------------
		// 105.4.9 ������� ����
		//--------------------------------------
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_PHYSICALDEFENSE );
			if ( 0 < siSkillMasterRate )
			{
				temPhysicalDRate += siSkillMasterRate;
			}
		}

	}
	
	//--------------------------------------
	// 105.4.7 ��ȯ�� ���ݷ� ���� ������ ����  ���� ��� - ���� ��ȯ�����.
	//--------------------------------------
	if (pclchar)
	{
		// ���� ��ȯ�����
		SI32 parentid = pclchar->GetSummonParentID();
		if(pclClient->pclCM->IsValidID(parentid))
		{
			// ��ȯ�� ������ ��ȯ�� ���ݷ�, ���� ���� ������ ������ �ִٸ� 
			SI32 summonskill = 0;

			if(pclskillinfo)
			{
				summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
			}
			// ��ȯ�� ������ ��ȯ�� ��ų ������ ���� ��ȯ���� ������ ������Ų��.

			SI32 defBonusPercent = 0;
			defBonusPercent = pclClient->GetSummonDefBonus( summonskill );

			//TotalAC += TotalAC * defBonusPercent / 100;		
			temPhysicalDRate += defBonusPercent;

			SI32 bufBonusPercent = 0;

			if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP ) == true )
			{
				// ���� ���ʽ� ���� ���� ���� �ʴ´�
				bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_SUMMONATACUP) );
			}    

			if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) == true )
			{
				// ���� ���ʽ� ���� ���� ���� �ʴ´�
				bufBonusPercent = max( bufBonusPercent , 50 );
			}   

			if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_EGGMOONCAKE ) == true )
			{
				bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_EVENT_EGGMOONCAKE) );
			}

			//TotalAC += TotalAC * bufBonusPercent / 100;
			temPhysicalDRate += bufBonusPercent;
		}
	}
		
	return temPhysicalDRate;
}


////  106. ���� �����
void cltParametaBox::SetMagicalDefensiveRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo)
{
	SI32 totalWis = clTotalBA.GetWis();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 106.1 �����Ǿ��ִ� �⺻ ����  - ĳ���Ϳ� ���� ���ҽ��� ����.
	//--------------------------------------
	//SI32 DefaultAC = pclKI->clDefaultWeaponInfo.GetDefaultAC(); // - �ϴ� �Ⱦ���.

	//--------------------------------------
	// 106.2  ������ ���� ���� ���� ����.
	//--------------------------------------

	siWisMagicalDefensive = (totalWis+level)*90/100 ;

	//--------------------------------------
	// 106.3  ��� ���� ���� ���� ����. 
	//--------------------------------------
	SI16 Edefansive = 0;
	SI32 CrysTalPer = 0;

	if(pclitemlist)
	{
		Edefansive = (SI16)pclItemManager->GetEquipCrystalMagicalDefensiveRate(pclitemlist, activeweaponpos,pclchar , &CrysTalPer); 

		if(Edefansive>0)
			siEquipMagicalDefensive = Edefansive;
		else
			siEquipMagicalDefensive = 0;
	}

	//--------------------------------------
	// 106.4  ��ų�� ���� ���� ����
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	SI32 siWeaponSkillRate = 0;
	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 106.5 ������� ����
		//--------------------------------------
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		SI32 siSkillUnique		= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_MAGICALDEFENSE );
			if ( 0 < siSkillMasterRate )
			{
				siWeaponSkillRate += siSkillMasterRate;
			}
		}
	}

	//--------------------------------------
	// 106.5 ��ȥ
	//--------------------------------------
	SI16 siMarriageMagicalDefensive = 0;

	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) && (pclchar->IsMarried()) )	bMarriageCondition = true;
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) && (pclchar->IsMarried()) )		bMarriageCondition = true;
		}

		if ( (pclClient->m_pclMarriageMgr) && (true == bMarriageCondition) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
		{
			SI16 siMarriageValue = (SI16)pclClient->m_pclMarriageMgr->GetTotalDefenseAbilityValue( pclchar->pclMarriage->GetLoveLevel() );
			if ( 0 < siMarriageValue )
			{
				siMarriageMagicalDefensive = siMarriageValue;
			}
		}
	}

	//--------------------------------------
	// ���� ��ȭ���� ���� �������� ���
	//--------------------------------------
	SI32 siMagicDefRate_ByBuf = 0;
	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );

			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					siMagicDefRate_ByBuf += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}
		}
	}

	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if ( (pclchar) && ( 1 == pclchar->GetID()) )
		{
			cltBufInfo clBuf;
			clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
			
			if( clBuf.IsHaveBuf(BUF_RESIDENTS_STRONG) )
			{
				SI32 siBufIndex = clBuf.FindBufSlot(BUF_RESIDENTS_STRONG);
				if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
				{
					siMagicDefRate_ByBuf += clBuf.m_stBuf[siBufIndex].siPercent;
				}
			}
		}
	}

	// ��Ű ȿ��
	SI32 siCookieEffect = 0 ;
	if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
	{
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() ))  )
			{
				if(pclchar->pclFamily != NULL )
				{
					if( pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )	// ��Űȿ���� �ڽ��϶��� �ȴ�
					{
						if(pclchar->pclFamily->GetOnParentNum() > 0 )
						{
							cltServer* pclserver = (cltServer*)pclClient;
							SI32 siEndDateVary = 0;
							SI32 siNowDateVary = 0;
							SI32 siCookieLevel	=	0	;
							SI32 siEffect	=	0;
							siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
							siNowDateVary = pclserver->pclTime->clDate.GetHourVary()	;
							if(  siEndDateVary > 0 && siEndDateVary > siNowDateVary )
							{
								siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;
								siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;

								siCookieEffect	=	siEffect;
							}
						}
					}	
				}
			}
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) )
			{
				if( pclchar->pclFamily != NULL )
				{
					if( pclchar->pclFamily->GetMyClass_InFamily() ==  MYCLASS_IN_FAMILY_CHILDREN)
					{
						if(pclchar->pclFamily->GetOnParentNum() > 0)
						{
							SI32 siEndDateVary = 0;
							SI32 siNowDateVary = 0;
							SI32 siCookieLevel	=	0	;
							SI32 siEffect	=	0;

							siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
							siNowDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;
							if(  siEndDateVary > 0 && siEndDateVary > siNowDateVary )
							{
								siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;
								siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;

								siCookieEffect	=	siEffect;
							}

						}
					}
				}
			}
		}
	}	
	//----------------------------------------------------------------
	// 106.6 Ż��(��ȣ)�� Ÿ�� �Ǹ� ���� ������ 100 ����Ѵ�.(09.05.13)
	//----------------------------------------------------------------
	SI16	siMagicalDefenseHorseAC = 0;

	if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
	{
		if(pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER)
		{
			siMagicalDefenseHorseAC = 100;
		}
	}

	//----------------------------------------------------------------
	// [����] ��Ʈ ȿ���� ���� ���� ���� ��� ( %)
	//----------------------------------------------------------------
	SI32 setMagicDefenceRate = 0;
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		if ( pclchar && IsPC( pclchar->GetID() ) )
		{
			if( pclchar->m_siSetItemType ) 
			{
				setMagicDefenceRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_DEFENCE, USE_SETITEM_1);
				setMagicDefenceRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_DEFENCE, USE_SETITEM_2);
				setMagicDefenceRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_DEFENCE, USE_SETITEM_3);
				setMagicDefenceRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_DEFENCE, USE_SETITEM_4);
				setMagicDefenceRate  +=  pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MAGIC_DEFENCE, USE_SETITEM_5);
			}
		}
	}

	//--------------------------------------
	// 106.7  % ���� ���� ��
	//--------------------------------------
	SI32 siMagicalDefensiveRate = CrysTalPer + siWeaponSkillRate + setMagicDefenceRate + siMagicDefRate_ByBuf;		// [����] ������ ���� �������� ���� ȿ�� �߰�.

	//--------------------------------------
	// 106.8  ���� ���� ���� ����.  
	//--------------------------------------
	Edefansive =siWisMagicalDefensive +  siEquipMagicalDefensive + siMarriageMagicalDefensive + siMagicalDefenseHorseAC  ;

	if( siMagicalDefensiveRate>0 && siCookieEffect<= 0)
	{
		siMagicalDefensive = Edefansive + (Edefansive *siMagicalDefensiveRate /100) ;
	}
	else if( siCookieEffect> 0 && siMagicalDefensiveRate <= 0 )
	{
		siMagicalDefensive = Edefansive + (Edefansive *siCookieEffect /100) ;
	}
	else if (siCookieEffect > 0 && siMagicalDefensiveRate > 0 )
	{
		siMagicalDefensive = Edefansive + (Edefansive *(siCookieEffect + siMagicalDefensiveRate ) /100) ;
	}
	else
		siMagicalDefensive = Edefansive ;

	if( pclchar )
	{
		if( pclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_DEFENSE, pclchar->GetID() ) )
		{
			siMagicalDefensive += (siMagicalDefensive * pclchar->m_clCharCurseEffect.GetPara()) / 100; 
		}

		if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT))
		{
			siMagicalDefensive += 5 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siMagicalDefensive * 5) / 100 : 0;
		}
	}
		
	
	//--------------------------------------
	// ��Ÿ: ������� �������� GetDefensiveRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------	

}

////  107. ���� ȸ����
void cltParametaBox::SetPhysicalDodgeRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo)
{
	SI32 totalDex = clTotalBA.GetDex();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 107.1 ���� ȸ�� ��� ����. -�⺻��.
	//--------------------------------------
	SI16 temDodgerateRank = 0;

	if ( (totalDex >0) && (level > 0) )
	{
		temDodgerateRank = ((totalDex * 3)+level);
	}
	else
	{
		temDodgerateRank = 0;
	}
	
	//--------------------------------------
	// 107.2 ������� ���� ȸ���� ����� ���Ѵ�. 
	//--------------------------------------
	SI16 siCrystalDodgeRank = 0;
	if(pclitemlist)
	{
		SI16 EDodgeRate = pclItemManager->GetEquipCrystalPhysicalDodgeRate(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ȸ�Ƿ� ���  - % 
		if ( 0 < EDodgeRate )
		{
			siCrystalDodgeRank = temDodgerateRank * EDodgeRate / 100;
		}
	}

	//--------------------------------------
	// 107.3 ��ų�� ���� ���� ȸ���� ����� ���Ѵ�. 
	//--------------------------------------
	SI16	siWeaponDodgeRank	= 0;
	bool	bCalcWeaponSkill	= false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 107.3.1 ��������
		//--------------------------------------
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCDR;			}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_SWORD_INCDR;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_SWORD_INCDR;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_SWORD_INCDR;		}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_SWORD_INCDR;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_SWORD_INCDR;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siWeaponDodgeRank = temDodgerateRank * siWeaponSkillRate / 100;
			}
		}

		//--------------------------------------
		// 107.3.2 ������� ����
		//--------------------------------------
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_PHYSICALDODGE );
			if ( 0 < siSkillMasterRate )
			{
				siWeaponDodgeRank +=  siSkillMasterRate;
			}
		}
	}

	//--------------------------------------
	// 107.4 ������� ���� ȸ�ǵ�� ���� - ���/�������� ���� ������.
	//--------------------------------------
	siPHysicalDodgeRateRank = temDodgerateRank + siCrystalDodgeRank + siWeaponDodgeRank;

	//--------------------------------------
	// ��Ÿ: ȸ�Ƿ��� �������� GetDodgeRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------
}

////  108. ���� ȸ����
void cltParametaBox::SetMagicalDodgeRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo)
{
	SI32 totalDex = clTotalBA.GetDex();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 108.1 ������� ���� ȸ���� ����� ���Ѵ�. 
	//--------------------------------------
	SI16 EDodgeRate = 0;
	if(pclitemlist)
	{
		EDodgeRate = pclItemManager->GetEquipCrystalMagicalDodgeRate(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ȸ���� ���  - % 

		if(EDodgeRate >0)
			siEquipMagicalDodgeRate = EDodgeRate;
		else
			siEquipMagicalDodgeRate = 0;
	}

	//--------------------------------------
	// 108.2 ��ų�� ���� ���� ȸ���� ����� ���Ѵ�. 
	//--------------------------------------
	SI16	siWeaponDodgeRate	= 0;
	bool	bCalcWeaponSkill	= false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 108.2.1 ������� ����
		//--------------------------------------
		SI32 siItemType		= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		SI32 siSkillUnique	= pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_MAGICALDODGE );
			if ( 0 < siSkillMasterRate )
			{
				siWeaponDodgeRate += siSkillMasterRate;
			}
		}
	}

	//--------------------------------------
	// 108.2 ���� ȸ�� ��� ����.   -�⺻��.
	//--------------------------------------
	SI16 temDodgerateRank = 0;
	
	if((totalDex >0) && (level > 0))
		temDodgerateRank = ((totalDex * 2)+level);
	else
		temDodgerateRank = 0;

	//--------------------------------------
	// 108.3 ���� ȸ�� % ������ ����
	//--------------------------------------
	SI32 siMagicalDodgeRate = siEquipMagicalDodgeRate + siWeaponDodgeRate;

	//--------------------------------------
	// 108.4 ������� ���� ȸ�ǵ�� ���� - ��� ���� ������.
	//--------------------------------------
	if(siMagicalDodgeRate >0)
		siMagicalDodgeRateRank = temDodgerateRank + (temDodgerateRank * siMagicalDodgeRate /100); //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ���Ѵ�.
	else
		siMagicalDodgeRateRank = temDodgerateRank ; //ũ����Ż�� ���� ȸ���� ��� ��ġ�� ���Ѵ�.

	//--------------------------------------
	// ��Ÿ: ȸ�Ƿ��� �������� GetDodgeRate() ���� , ������ ������ ���� �����ȴ�. 
	//--------------------------------------
}

////  109. ü�� 
void cltParametaBox::SetHitPoint(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos, bool bnpc, cltPSkillInfo* pclskillinfo)
{
	SI32 totalVit = clTotalBA.GetVit();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 109.1  ����¿� ���� ü�� ����.
	//--------------------------------------
	siVitHitpoint = (totalVit * (8000 + (level *5)))/1000 ;	// ���� ���� �ٲٰ� �Ǹ�, �ݵ�� DoMsg_GAMEMSG_REQUEST_MAKENEWCHAR���� �ʱⰪ ���ĵ� �ٲ���� �Ѵ�.
	
	//--------------------------------------
	// 109.2 ������� ü�� ����� ���Ѵ�. 
	//--------------------------------------
	SI16 EHitpointPer = 0;
	
	if(pclitemlist)
	{
		EHitpointPer = pclItemManager->GetEquipCrystalHitpoint(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ȸ�Ƿ� ���  - % 

		if(EHitpointPer>0)
			siEquipHitpoint = EHitpointPer;
		else
			siEquipHitpoint = 0;
	}

	//--------------------------------------
	// 109.3  ���� ü�� ����.  
	//--------------------------------------
	if(siEquipHitpoint >0)
		siTotalHitpoint = siVitHitpoint + (siVitHitpoint *siEquipHitpoint /100) ;
	else
		siTotalHitpoint = siVitHitpoint ;

	//--------------------------------------
	// 109.4  ���������� ���� ����� ����
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCVIT;			}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_SWORD_INCVIT;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_SWORD_INCVIT;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_SWORD_INCVIT;		}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_SWORD_INCVIT;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_SWORD_INCVIT;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siTotalHitpoint = siTotalHitpoint + (siTotalHitpoint * siWeaponSkillRate / 100);
			}
		}
	}

	//--------------------------------------
	// 109.5  ���� ������ ���� ����� ����
	//--------------------------------------
	if ( (pclchar) && (IsPC(pclchar->GetID())) )
	{
		siTotalHitpoint += pclchar->m_clMagicBufMgr.GetIncHP( pclchar );
	}

	//--------------------------------------
	// 109.5 ��ȥ ���� ����� ����
	//--------------------------------------
	if ( pclClient->IsCountrySwitch(Switch_WeddingSystem) )
	{
		bool bMarriageCondition = false;
		if ( GAMEMODE_SERVER == pclClient->GameMode )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) && (pclchar->IsMarried()) )	bMarriageCondition = true;
		}
		else if ( GAMEMODE_CLIENT == pclClient->GameMode )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) && (pclchar->IsMarried()) )		bMarriageCondition = true;
		}

		if ( (pclClient->m_pclMarriageMgr) && (true == bMarriageCondition) && (MARRIAGE_MATE_CONNECT_MODE_SAMEMAP == pclchar->pclMarriage->GetConnectMode()) )
		{
			SI32 siMarriageValue = pclClient->m_pclMarriageMgr->GetTotalLifeAbilityValue( pclchar->pclMarriage->GetLoveLevel() );
			if ( 0 < siMarriageValue )
			{
				siTotalHitpoint += siMarriageValue;
			}
		}
	}
	//--------------------------------------
	// 109.5  PVP/PVP_League/SetItem�� ���� ����� ����
	//--------------------------------------
	if (pclchar != NULL) 
	{
		// pvp�� pvp_league �� 5�� ����
		if ( pclchar->siEnemUnique > 0 ) 
		{
				siTotalHitpoint = siTotalHitpoint * 5;
		}
		else if ( pclchar->GetPVP_LeagueEnemyPersonID() > 0 ) 
		{
			siTotalHitpoint = siTotalHitpoint * 5;
		}
		if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )
		{
			if( IsGuildWarMap_NEW( pclchar->GetMapIndex() ) )
			{
				if( 0 < pclchar->pclCI->clBI.clGuildRank.GetEnemyGuild() )// ����� ����ũ�� ������ 
				{
					siTotalHitpoint = siTotalHitpoint * 5;
				}
			}
		}
		if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
		{
			if( pclchar->m_siSetItemType )
			{
				siTotalHitpoint +=	 siTotalHitpoint *  ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_1 ) 
														+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_2 )
														+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_3 )
														+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_4 )
														+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_5 )) * 0.01;
			}
		}

		if( pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_GIANTRACCOON_RESURRECT_EVENT))
		{
			siTotalHitpoint += 3 <= pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_GIANTRACCOON_RESURRECT_EVENT)->siPercent ? (siTotalHitpoint * 10) / 100 : 0;
		}
	}

	//--------------------------------------
	// 109.5 ��Ÿ ���� ����.  
	//--------------------------------------
	if((pclchar!= NULL) && (pclitemlist != NULL)&&(pclchar->GetKind() != KIND_SYSTEM))
	{
		if(pclchar->pclCI->clIP.GetLife() > siTotalHitpoint)
		{
			pclchar->pclCI->clIP.SetLife(siTotalHitpoint);
		}
	}	
	
	
	/*	if(pclchar!= NULL)
	{
		if(pclchar->GetChangeEquipAbility() >= 0) // ���� Ȥ�� Ż���� �����. - �ٽ� �����Ѵ�.
		{	
			if(pclchar->GetLife() >siTotalHitpoint)
				pclchar->SetLife(siTotalHitpoint);

			pclchar->SetChangeEquipAbility(-1); //�ٽ� �ʱ�ȭ.
		}
	}
*/
}

////  110. ������
void cltParametaBox::SetManaPoint(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo)
{
	SI32 totalMag = clTotalBA.GetMag();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 110.1 ���¿� ���� ���� ����.
	//--------------------------------------
	siMagManapoint = (totalMag * (4000 + (level *5)))/1000 ;	// ���� ���� �ٲٰ� �Ǹ�, �ݵ�� DoMsg_GAMEMSG_REQUEST_MAKENEWCHAR���� �ʱⰪ ���ĵ� �ٲ���� �Ѵ�.
	
	//--------------------------------------
	// 110.2 ������� ���� ����� ���Ѵ�. 
	//--------------------------------------
	SI16 EManapointPer = 0;
	
	if(pclitemlist)
	{
		EManapointPer = pclItemManager->GetEquipCrystalManapoint(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ȸ�Ƿ� ���  - % 

		if(EManapointPer>0)
			siEquipManapoint = EManapointPer;
		else
			siEquipManapoint = 0;
	}

	//--------------------------------------
	// 110.3  ���� ���� ����.  
	//--------------------------------------
	if(siEquipManapoint >0)
		siTotalManapoint = siMagManapoint + (siMagManapoint *siEquipManapoint /100) ;
	else
		siTotalManapoint = siMagManapoint ;

	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		if( pclchar && pclchar->m_siSetItemType )
		{
			siTotalManapoint +=  siTotalManapoint * ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_1 )
													+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_2 )
													+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_3 )
													+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_4 )
													+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_5 )) * 0.01;
		}
	}

	if ( (pclchar) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_STAFF_INCMAG;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_STAFF_INCMAG;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_STAFF_INCMAG;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_STAFF_INCMAG;		}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_STAFF_INCMAG;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_INCMAG;			}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siTotalManapoint += (siTotalManapoint * siWeaponSkillRate / 100);
			}
		}
	}


	
	//--------------------------------------
	// 110.4 ��Ÿ ���� ����.  
	//--------------------------------------
	if((pclchar!= NULL) && (pclitemlist != NULL)&&(pclchar->GetKind() != KIND_SYSTEM))
	{
		if(pclchar->pclCI->clIP.GetMana() > siTotalManapoint)
			pclchar->pclCI->clIP.SetMana(siTotalManapoint);
	}	
	/*	if(pclchar!= NULL)
	{
		if(pclchar->GetChangeEquipAbility() >= 0) // ���� Ȥ�� Ż���� �����. - �ٽ� �����Ѵ�.
		{	
			if(pclchar->GetMana() >siTotalManapoint)
				pclchar->SetMana(siTotalManapoint);
			else if(pclchar->GetMana() <0)
				pclchar->SetMana(1);

			pclchar->SetChangeEquipAbility(-1); //�ٽ� �ʱ�ȭ.
		}
	}
*/
}

////  111. ���Է�
void cltParametaBox::SetWeight(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc)
{
	SI32 totalStr = clTotalBA.GetStr();
	SI32 level = pclIP->GetLevel();

	//--------------------------------------
	// 109.1  ���� ���� ���Է� ����.
	//--------------------------------------
	siStrWeigt = (totalStr * 200) + (level *800);	
	
	//--------------------------------------
	// 109.2 ������� ���Է� ����� ���Ѵ�. 
	//--------------------------------------
	SI16 EWeightPer = 0;
	
	if(pclitemlist)
	{
		EWeightPer = pclItemManager->GetEquipCrystalWeigt(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ȸ�Ƿ� ���  - % 

		if(EWeightPer>0)
			siEquipWeigt = EWeightPer;
		else
			siEquipWeigt = 0;
	}

	//--------------------------------------
	// 109.3  ���� ���Է� ����.  
	//--------------------------------------
	if(siEquipWeigt > 0)
		siTotalWeigt = siStrWeigt + (siStrWeigt *siEquipWeigt /100) ;
	else
		siTotalWeigt = siStrWeigt ;

}

////  112. ũ��Ƽ�� ����.
void cltParametaBox::SetCritcalRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltPSkillInfo*	pclskillinfo,cltSummonScroll*	pclsummonscroll)
{
	if(bnpc == false)
	{
		if(TABS(pclClient->GetFrame() - uiLastGetCriticalRateFrame )  > 100)
		{
			uiLastGetCriticalRateFrame = pclClient->GetFrame();

			SI32 skilllevel = 0;
			switch(siAttackType)
			{
			case ATTACKTYPE_SWORD:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESWORD1, 0, 0, pclitemlist);
				}
				break;
			case ATTACKTYPE_SPEAR:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESPEAR1, 0, 0, pclitemlist);
				}
				break;
			case ATTACKTYPE_AXE:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEAXE1, 0, 0, pclitemlist);
				}
				break;
			case ATTACKTYPE_STAFF:
			case ATTACKTYPE_STAFF1:
			case ATTACKTYPE_STAFF2:
			case ATTACKTYPE_NEW_STAFF2:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESTAFF1, 0, 0, pclitemlist);
				}
				break;
			case ATTACKTYPE_BOW:
			case ATTACKTYPE_BOW1:
			case ATTACKTYPE_NEW_BOW1:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEBOW1, 0, 0, pclitemlist);
				}
				break;
			case ATTACKTYPE_GUN:
			case ATTACKTYPE_GUN1:
			case ATTACKTYPE_NEW_GUN1:
				if(pclskillinfo)
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEGUN1, 0, 0, pclitemlist);
				}
				break;
			}

			siCriticalRate = 0;
			if(skilllevel > 30)
			{
				siCriticalRate += ((skilllevel - 30) * 2);
				skilllevel = 30;
			}
			if(skilllevel > 20)
			{
				siCriticalRate += ((skilllevel - 20) * 5);
				skilllevel = 20;
			}

      
			siCriticalRate += (skilllevel * 8);

			// ���⿡ �߰��� �ΰ��� Critical Rate�� �ΰ��Ѵ�.
			if(pclitemlist)
			{
				//siCriticalRate += pclItemManager->GetEquipCriticalHitRate(pclitemlist, activeweaponpos);				
				siCriticalRate += pclItemManager->GetEquipCrystalCriticalHitRate(pclitemlist, activeweaponpos,pclchar);				
			}

			// ��ų�� �ο��� ũ��Ƽ��������
			SI32 siWeaponSkillCriticalRate = 0;

			if ( (pclchar) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
			{
				// ��������
				SI32 siSkillUnique		= 0;
				SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
				switch ( siItemType )
				{
					case ITEMTYPE_AXE:	{	siSkillUnique = SKILL_AXE_INCCRI;	}	break;
				}

				if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
				{
					SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
					SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
					if ( 0 < siWeaponSkillRate )
					{
						siWeaponSkillCriticalRate += siWeaponSkillRate;
					}
				}

				// ������� ����
				siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
				if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
				{
					SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
					SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_CRITICAL );
					if ( 0 < siSkillMasterRate )
					{
						siWeaponSkillCriticalRate += siSkillMasterRate;
					}
				}

				if ( 0 < siWeaponSkillCriticalRate )
				{
					siCriticalRate = siCriticalRate + (siCriticalRate * siWeaponSkillCriticalRate / 100);
				}
			}

			siCriticalRate = min(MAX_SCROLL_EFFECT, siCriticalRate);
		}

		//KHY - 1220 - ���Žý���.
		if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
		{
			if(siAttackType == ATTACKTYPE_SWORD)
			{								
				siCriticalRate += (SI32)(siTransFormSyc/2);
			}
			//���� ���� 100% ȿ�� ����
			else if(siAttackType == ATTACKTYPE_AXE)
			{
				//AXE 100% - ���� ������.
				if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
				{
					DWORD dTransFormAXEInterval = 1000;

					dwAttackInterval = dTransFormAXEInterval;
					//pclItemManager->pclItemInfo[ref]->SetAttackInterval(dTransFormAXEInterval);
				}
			}
		}
		
		SI32 siWeaponSkillAttackIntervalRate = 0;

		siMagicDecDelay = 0;

		if ( (pclchar) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
		{
			// ���������� ���� �����ֱ� ����
			SI32 siSkillUnique		= 0;
			SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
			/*
			switch ( siItemType )
			{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_AXE_DECWEAINT;	}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_AXE_DECWEAINT;	}	break;
				case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_DECWEAINT;		}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_AXE_DECWEAINT;	}	break;
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_AXE_DECWEAINT;	}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_AXE_DECWEAINT;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					siWeaponSkillAttackIntervalRate += siWeaponSkillRate;
				}
			}
			*/

			// ������� ���ο� ���� �����ֱ� ����
			siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
				SI32 siSkillMasterRate	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_ATTACKINTERVAL );
				if ( 0 < siSkillMasterRate )
				{
					siWeaponSkillAttackIntervalRate += siSkillMasterRate;
				}
			}

			if ( 0 < siWeaponSkillAttackIntervalRate )
			{
				dwAttackInterval = dwAttackInterval - (dwAttackInterval * siWeaponSkillAttackIntervalRate / 100);
			}

			// ���������� ���� ��������ֱ� ����
			siSkillUnique = 0;
			switch ( siItemType )
			{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_GUN_DECMAGDELAY;	}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_GUN_DECMAGDELAY;	}	break;
				case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_GUN_DECMAGDELAY;		}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_GUN_DECMAGDELAY;		}	break;
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_DECMAGDELAY;			}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_GUN_DECMAGDELAY;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					siMagicDecDelay = siWeaponSkillRate;
				}
			}
		}
		
	}
	else	// NPC
	{
		siCriticalRate = pclKI->siCriticalRate;			//Kind�⺻�� �ʻ�� Ȯ���� ����ȴ�.

		//----------------------------------------------------
		// ��ȯ�� ������ ���� Critical Hit ���
		//----------------------------------------------------
		if(pclsummonscroll)
		{
			siCriticalRate	+= pclsummonscroll->GetScrollCriticalHitRate(pclItemManager);
		}

		siCriticalRate = min(MAX_SCROLL_EFFECT, siCriticalRate);

	}

}

void cltParametaBox::SetEtcSetting(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltPSkillInfo*	pclskillinfo,cltSummonScroll*	pclsummonscroll, cltPersonHorseInfo* pclhorseinfo)
{
	//--------------------------------------------------
	// �̵� �ӵ��� ���Ѵ�. 
	//--------------------------------------------------
	BasicMoveSpeed		= pclKI->siMoveSpeed;
	
	if(pclitemlist)
	{
		if (pclClient->IsCountrySwitch(Switch_StatusBug)) {
			ShoesMoveSpeed		= pclItemManager->GetMoveSpeed(pclitemlist);
		}
		else{
			ShoesMoveSpeed		= pclItemManager->GetMoveSpeed(pclitemlist,pclchar);
		}
		
	}
	else
	{
		ShoesMoveSpeed = 0;
	}

	if(GivenMoveSpeed)
	{
		TotalMoveSpeed		= GivenMoveSpeed;
	}
	else
	{
		// ���� Ÿ�� �ִٸ�, 
		if(pclhorseinfo && pclhorseinfo->siCurrentHorseRIDEHORSE == true)
		{
			cltHorse* pclhorse = pclhorseinfo->GetCurrentShowHorse();
			if (pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HAPPYBEAN) ||			//���Ǻ� �̺�Ʈ ����Ÿ���� ������ �̼��ִ� [2007.08.27 �ռ���]
						    pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_THANKSGIVING_DAY)) )	//[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. �̵��ӵ� �ִ�]
			{ 
				TotalMoveSpeed = 20;
			}
			else if(pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_MENTOR)))
			{
				if( 15 > BasicMoveSpeed + ShoesMoveSpeed && 15 > pclhorse->GetRealMoveSpeed())
				{
					TotalMoveSpeed = 15;
				}
				else if(pclhorse)
					TotalMoveSpeed	= pclhorse->GetRealMoveSpeed();		// ���� �̵��ӵ��� �ӵ��� ��ü�Ѵ�.
			}
			else
			{
				if(pclhorse)
					TotalMoveSpeed	= pclhorse->GetRealMoveSpeed();		// ���� �̵��ӵ��� �ӵ��� ��ü�Ѵ�. 

			}
		}
			
		// ���� Ÿ�� ���� ���¶��, 
		else 
		{
			if (pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HAPPYBEAN) ||			//���Ǻ� �̺�Ʈ ����Ÿ���� ������ �̼��ִ� [2007.08.27 �ռ���]
							pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_THANKSGIVING_DAY)) )	//[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. �̵��ӵ� �ִ�] 
			{ 
				TotalMoveSpeed = 20;
			}
			else if(pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_MENTOR)))
			{
				if( 15 > BasicMoveSpeed + ShoesMoveSpeed )
				{
					TotalMoveSpeed = 15;
				}
			}
			else
			{// ������ ���� ���� Ÿ�� ���� ���¶��
				TotalMoveSpeed		= BasicMoveSpeed + ShoesMoveSpeed;
			}			
		}
	}

	//--------------------------------------
	// 109.3  ��ȯ�� ���׹̳� ����.  
	//--------------------------------------
	if (pclchar)
	{
		// ���� ��ȯ�����
		SI32 parentid = pclchar->GetSummonParentID();
		if(pclClient->pclCM->IsValidID(parentid))
		{
			SI32 summonskill = 0;

			if(pclskillinfo)
			{
				summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
			}
			
			MaxStamina		= pclClient->GetMaxStaminaValue(summonskill, pclchar->GetKind());

		}
	}
	else
		MaxStamina		= 10;

	//--------------------------------------
	// 109.4  ��ų�� ���� ��Ÿ�����
	//--------------------------------------
	bool bCalcWeaponSkill = false;
	if ( GAMEMODE_SERVER == pclClient->GameMode )
	{
		if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
	}

	if ( (bCalcWeaponSkill) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
	{
		//--------------------------------------
		// 109.4.1  �������� %�� ����
		//--------------------------------------
		SI32 siSkillUnique		= 0;
		SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
		switch ( siItemType )
		{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_BOW_INCRANGE;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_BOW_INCRANGE;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_BOW_INCRANGE;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_INCRANGE;			}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_BOW_INCRANGE;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_BOW_INCRANGE;	}	break;
		}

		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
			SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
			if ( 0 < siWeaponSkillRate )
			{
				siAttackRange += (siAttackRange * siWeaponSkillRate / 100);
			}
		}

		//--------------------------------------
		// 109.4.2  ������� ���� ���밪���� ����
		//--------------------------------------
		siSkillUnique = pclClient->pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel		= pclskillinfo->GetSkillExpLevel( siSkillUnique );
			SI32 siSkillMasterValue	= pclClient->pclSkillManager->m_clMasterManager.GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_ATTACKRANGE );
			if ( 0 < siSkillMasterValue )
			{
				siAttackRange += siSkillMasterValue;
			}
		}
	}
	
}

// ������ ������ �ٰŷ� ���� �Ӽ��� �ľ��Ѵ�. 
void cltParametaBox::CalculateAttackType(cltCharCommon* pclchar, SI16 activeweaponpos, cltItem* pclitemlist)
{

	SI32 attacktype = 0;
	SI32 attackskill = 0 ;

	if(pclitemlist)
	{
		attacktype = pclItemManager->GetWeaponAttackType(pclitemlist, activeweaponpos);
		SI32 ref = pclItemManager->FindItemRefFromUnique(pclitemlist[activeweaponpos].siUnique);
		if ( ref )
		{
			attackskill = pclItemManager->pclItemInfo[ref]->clCondition.siSkillKind ;
		}
	}

	// ������ �ϰ� �ִ� ���¸� ������ ���� Ÿ���� ����Ѵ�. 
	if(pclitemlist && attacktype)
	{
		siAttackType		= attacktype;
		siAttackRange		= pclItemManager->GetWeaponAttackRange(pclitemlist, activeweaponpos);

		//--------------------------------------
		// 109.3 ���� ����. 
		//--------------------------------------
		//KHY - 1220 - ���Žý���.
		if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
		{
			if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
			{
				switch(siAttackType)
				{ 
					case ATTACKTYPE_BOW:
					case ATTACKTYPE_GUN:
						siAttackRange += 1;
						break;
				}
			}
		}

		if(siAttackType == ATTACKTYPE_STAFF1 || siAttackType == ATTACKTYPE_STAFF2 || siAttackType == ATTACKTYPE_NEW_STAFF2)
		{
			if(pclIP->GetMana() < 2)
			{
				siAttackType	= ATTACKTYPE_STAFF;
				siAttackRange	= 1;
			}
		}

		dwAttackInterval	= pclItemManager->GetWeaponAttackInterval(pclitemlist, activeweaponpos);
		siArmWeaponUnique	= pclitemlist[activeweaponpos].GetType(pclItemManager);
	}
	else if(clShapeEquip.clWeapon.uiUnique)
	{
		SI32 ref = pclItemManager->FindItemRefFromUnique(clShapeEquip.clWeapon.uiUnique);
		if(ref > 0)
		{
			siAttackType		= pclItemManager->pclItemInfo[ref]->GetAttackType();
			siAttackRange		= pclItemManager->pclItemInfo[ref]->GetAttackRange();

			dwAttackInterval	= pclItemManager->pclItemInfo[ref]->GetAttackInterval();
			siArmWeaponUnique	= pclItemManager->pclItemInfo[ref]->siType;

			attackskill = pclItemManager->pclItemInfo[ref]->clCondition.siSkillKind ;
		}
	}
	else
	{
		// by LEEKH 2007.12.28 TRANSFORM
		if( pclchar != NULL && pclchar->clTransFormInfo.bTransFormMode )
		{
			// �����̸� ĳ���� ������ ���� Ÿ���� ����Ѵ�.
			siAttackType		= pclchar->GetKindInfo()->clDefaultWeaponInfo.GetAttackType();		
			// �����̸� ĳ���� ������ ��Ÿ��� ���´�. 
			//siAttackRange		= pclchar->GetKindInfo()->clDefaultWeaponInfo.GetAttackRange();
			//dwAttackInterval	= pclchar->GetKindInfo()->dwAttackInterval;
			siArmWeaponUnique	= 0;
		}
		else
		{
			// �����̸� ĳ���� ������ ���� Ÿ���� ����Ѵ�.
			siAttackType		= pclKI->clDefaultWeaponInfo.GetAttackType();		
			// �����̸� ĳ���� ������ ��Ÿ��� ���´�. 
			siAttackRange		= pclKI->clDefaultWeaponInfo.GetAttackRange();
			dwAttackInterval	= pclKI->dwAttackInterval;
			siArmWeaponUnique	= 0;
		}

		// by LEEKH 2007.12.28 TRANSFORM
		/*		if( pclchar != NULL && pclchar->clTransFormInfo.bTransFormMode )
		{
		// �����̸� ĳ���� ������ ���� Ÿ���� ����Ѵ�.
		siAttackType		= pclchar->GetKindInfo()->clDefaultWeaponInfo.GetAttackType();		
		// �����̸� ĳ���� ������ ��Ÿ��� ���´�. 
		//siAttackRange		= pclchar->GetKindInfo()->clDefaultWeaponInfo.GetAttackRange();
		//dwAttackInterval	= pclchar->GetKindInfo()->dwAttackInterval;
		siArmWeaponUnique	= 0;
		}*/
	}

}

// ���� �ɷ��� ��ġȭ�ؼ� ���´�. 
SI32 cltParametaBox::GetBattlePower()
{
	SI32 power = pclIP->siStr + pclIP->siDex + pclIP->siMag + pclIP->siVit;

	return power / 2;
}
SI32 cltParametaBox::GetBattleLevel()
{
	SI32 battleLevel =( 
		sqrt( (double)((pclIP->siDex-7)*48 ) ) + 
		sqrt( (double)((pclIP->siVit-6)*14 ) ) 
		)/2;

	battleLevel = max( 1, battleLevel );

	return battleLevel;
}
SI32 cltParametaBox::GetBossBattleLevel()
{
	SI32 battleLevel =( 
		sqrt( (double)(pclIP->siDex*35 ) ) + 
		sqrt( (double)((pclIP->siVit+1200)*5 ) ) 
		)/2 + (pclIP->siMag/25);

	battleLevel = max( 1, battleLevel );

	return battleLevel;
}


// bnpc���� ����. 
// bmonsterhero : ���Ϳ��� ��ȭ�� ��ȯ�����ΰ�. 
BOOL cltParametaBox::Action(cltCharCommon* pclchar, SI32 personid, SI32 activeweaponpos, 
							cltItem*			pclitemlist,	// ���ǰ ������ ����Ʈ . 				
							//cltPItemInfo* pclcharitem, 
							cltPersonHorseInfo* pclhorseinfo, 
							cltHealthInfo*		pclhealthinfo, 
							cltPSkillInfo*		pclskillinfo, 
							cltIdentity*		pclidentityinfo, 
							SI16				siAttackWearStoneNum,
							SI16				siDefenseWearStoneNum,
							SI32 gamemode, bool bnpc,
							bool bmonsterhero
							)
{

	// Ŭ���̾�Ʈ����...
	if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		cltClient* pclclient = (cltClient*)pclClient;
		// ���ΰ��� ������ ���� ���� ���¶��, �ɷ�ġ ����� ���� �ʴ´�.
		if( pclchar != NULL && pclchar->GetCharUnique() == pclclient->MyCharUnique )
		{
			if( pclclient->bReceiveMyCharAllInfoSwitch == false )
				return FALSE;
		}
	}
	if(pclIP == NULL)return FALSE;

	//--------------------------------------------
	// �ǰ� ���� ���� 
	//--------------------------------------------
	if(gamemode == GAMEMODE_SERVER)
	{
		// personid�� ��ȿ���� �ݵ�� Ȯ���ؾ� �Ѵ�. 
		if(bnpc == false && personid)
		{
			if(pclhealthinfo && clHealth.Action(pclIP->GetLevel(), pclClient->CurrentClock) == true)
			{
				// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
				if(pclchar)
				{
					pclchar->SetUpdateSwitch(UPDATE_HEALTH, true, 0);
				}

			}
		}
	}

	// 1. �ɷ�ġ ���


	// 1.0 - �⺻ �ɷ�
	clBasicBA.SetStr(pclIP->GetStr());
	clBasicBA.SetDex(pclIP->GetDex());
	clBasicBA.SetVit(pclIP->GetVit());
	clBasicBA.SetMag(pclIP->GetMag());
	clBasicBA.SetHnd(pclIP->GetHnd());
	clBasicBA.SetLuk(pclIP->GetLuk());
	clBasicBA.SetWis(pclIP->GetWis());

	// 1.1 - ���
	SetEquipBasicAbility(pclchar, pclitemlist, activeweaponpos);

	// 1.2 - ����
	SetTransformBasicAbility(pclchar, pclitemlist, activeweaponpos);

	// 1.3 - ��
	SetHorseBasicAbility(pclhorseinfo, pclchar);

	// 1.4 - �ǰ��� ���� �߰� �ɷ�ġ -10% ~ +10%
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SetHealthAddAbility(pclhealthinfo,
							cltBasicAbility(
								pclIP->GetStr() + clEquipBA.GetStr() + clHorseBA.GetStr() + clTransFormBA.GetStr(),
								pclIP->GetDex() + clEquipBA.GetDex() + clHorseBA.GetDex() + clTransFormBA.GetDex(),
								0, // ����� �߰� ����
								pclIP->GetMag() + clEquipBA.GetMag() + clHorseBA.GetMag() + clTransFormBA.GetMag(),
								pclIP->GetHnd() + clEquipBA.GetHnd() + clHorseBA.GetHnd() + clTransFormBA.GetHnd(),
								pclIP->GetLuk() + clEquipBA.GetLuk() + clHorseBA.GetLuk() + clTransFormBA.GetLuk(),
								pclIP->GetWis() + clEquipBA.GetWis() + clHorseBA.GetWis() + clTransFormBA.GetWis()
							) );
	}
	else
	{
		SetHealthAddAbility(pclhealthinfo,	cltBasicAbility(	pclIP->GetStr() + clEquipBA.GetStr() + clHorseBA.GetStr() + clTransFormBA.GetStr(),
																pclIP->GetDex() + clEquipBA.GetDex() + clHorseBA.GetDex() + clTransFormBA.GetDex(),
																0, // ����� �߰� ����
																pclIP->GetMag() + clEquipBA.GetMag() + clHorseBA.GetMag() + clTransFormBA.GetMag(),
																0,	// ������ �߰� ����
																0,	// ��� �߰� ����
																0	// ���� 
															) );
	}
	// 1.5 - ��忡 ���� �߰� �ɷ�ġ
	SetGuildBasicAbility(pclchar);

	// 1.6 - ��Ʈ �����ۿ� ���� �߰� �ɷ�ġ
	SetSetItemAddAbility(pclchar, pclitemlist);

	// 1.7 - ��ų�� ���� �߰� �ɷ�ġ
	SetSkillAddAbility( pclitemlist, activeweaponpos,
						pclskillinfo,
						cltBasicAbility(
							pclIP->GetStr() + clEquipBA.GetStr() + clHorseBA.GetStr() + clTransFormBA.GetStr() + clGuildBA.GetStr(), 
							pclIP->GetDex() + clEquipBA.GetDex() + clHorseBA.GetDex() + clTransFormBA.GetDex() + clGuildBA.GetDex(), 
							pclIP->GetVit() + clEquipBA.GetVit() + clHorseBA.GetVit() + clTransFormBA.GetVit() + clGuildBA.GetVit(), 
							pclIP->GetMag() + clEquipBA.GetMag() + clHorseBA.GetMag() + clTransFormBA.GetMag() + clGuildBA.GetMag(), 
							pclIP->GetHnd() + clEquipBA.GetHnd() + clHorseBA.GetHnd() + clTransFormBA.GetHnd() + clGuildBA.GetHnd(),
							pclIP->GetLuk() + clEquipBA.GetLuk() + clHorseBA.GetLuk() + clTransFormBA.GetLuk() + clGuildBA.GetLuk(),
							pclIP->GetWis() + clEquipBA.GetWis() + clHorseBA.GetWis() + clTransFormBA.GetWis() + clGuildBA.GetWis()
						) );
	
	//[����] ������ ���� ���ȿ� ����Ǵ� �ɷ�ġ. => 2008-6-18
	SetBufStatusUp(pclchar);

	//[����] ������. 
	SetElixirAddAbility( pclchar );

	// PCK : �������긮 �̺�Ʈ �Ⱓ���� ���� ��� (08.12.17)
	SetHinamatsuriAbility( pclchar );

	SetValentineEventAbility( pclchar);

	// �������� ���� �߰� �ɷ�ġ
	//SetPremiumPartsstatusUp( pclchar );

	// [����] ��ȣ���ɿ� ���� �ɷ�ġ ���
	SetSoulGuardAddAbility( pclchar );

	// [���] ũ�������� �̺�Ʈ�� ���� �ɷ�ġ ���
	SetWorldChristmasTreeAbility( pclchar );

	// 1.8 �ɷ�ġ �ջ�
	clTotalBA.SetStr( clBasicBA.GetStr() + 
					  clEquipBA.GetStr() +
					  clHorseBA.GetStr() +
					  clGuildBA.GetStr() +
					  clHealthAdd.GetStr() + 
					  clSetItemAdd.GetStr() +
					  clSkillAdd.GetStr() +
					  clTransFormBA.GetStr() + 
					  clbufAdd.GetStr()	+
					  clElixirAdd.GetStr() + 		
					  clHinamatsuriAdd.GetStr() +
					  clSoulGuardAdd.GetStr() +
					  clWorldChristmasTreeAdd.GetStr() +
					  clValentineAdd.GetStr()
					  /* +
					  clHorsePartsAdd.GetStr()*/);

	clTotalBA.SetDex( clBasicBA.GetDex() + 
					  clEquipBA.GetDex() +
					  clHorseBA.GetDex() +
					  clGuildBA.GetDex() +
					  clHealthAdd.GetDex() + 
					  clSetItemAdd.GetDex() +
					  clSkillAdd.GetDex() +
					  clTransFormBA.GetDex() + 
					  clbufAdd.GetDex() +
					  clElixirAdd.GetDex() +
					  clHinamatsuriAdd.GetDex() +
					  clSoulGuardAdd.GetDex() + 
					  clWorldChristmasTreeAdd.GetDex() +
					  clValentineAdd.GetDex()
					  /*clHorsePartsAdd.GetDex()*/);

	clTotalBA.SetMag( clBasicBA.GetMag() + 
					  clEquipBA.GetMag() +
					  clHorseBA.GetMag() +
					  clGuildBA.GetMag() +
					  clHealthAdd.GetMag() + 
					  clSetItemAdd.GetMag() +
					  clSkillAdd.GetMag() +
					  clTransFormBA.GetMag() + 
					  clbufAdd.GetMag() + 
					  clElixirAdd.GetMag() + 
					  clHinamatsuriAdd.GetMag() +
					  clSoulGuardAdd.GetMag() +
					  clWorldChristmasTreeAdd.GetMag() +
					  clValentineAdd.GetMag()
					  /*clHorsePartsAdd.GetMag()*/);

	clTotalBA.SetVit( clBasicBA.GetVit() + 
					  clEquipBA.GetVit() +
					  clHorseBA.GetVit() +
					  clGuildBA.GetVit() +
					  clHealthAdd.GetVit() + 
					  clSetItemAdd.GetVit() +
					  clSkillAdd.GetVit() +
					  clTransFormBA.GetVit() + 
					  clbufAdd.GetVit() + 
					  clElixirAdd.GetVit() +
					  clHinamatsuriAdd.GetVit() +
					  clSoulGuardAdd.GetVit() +
					  clWorldChristmasTreeAdd.GetVit() +
					  clValentineAdd.GetVit()
					  /* +
					  clHorsePartsAdd.GetVit()*/);

	clTotalBA.SetHnd( clBasicBA.GetHnd() + 
					  clEquipBA.GetHnd() +
					  clHorseBA.GetHnd() +
					  clGuildBA.GetHnd() +
					  clHealthAdd.GetHnd() + 
					  clSetItemAdd.GetHnd() +
					  clSkillAdd.GetHnd() +
					  clTransFormBA.GetHnd() + 
					  clbufAdd.GetHnd() +
					  clElixirAdd.GetHnd() + 
					  clHinamatsuriAdd.GetHnd() +
					  clSoulGuardAdd.GetHnd() + 
					  clWorldChristmasTreeAdd.GetHnd()+
					  clValentineAdd.GetHnd()
					  /* +
					  clHorsePartsAdd.GetHnd()*/ );

	clTotalBA.SetWis( clBasicBA.GetWis() + 
					  clEquipBA.GetWis() +
					  clHorseBA.GetWis() +
					  clGuildBA.GetWis() +
					  clHealthAdd.GetWis() + 
					  clSetItemAdd.GetWis() +
					  clSkillAdd.GetWis() +
					  clTransFormBA.GetWis() + 
					  clbufAdd.GetWis() +
					  clElixirAdd.GetWis() + 
					  clHinamatsuriAdd.GetWis() +
					  clSoulGuardAdd.GetWis() + 
					  clWorldChristmasTreeAdd.GetWis() +
					  clValentineAdd.GetWis()
					  /*	+
					   clHorsePartsAdd.GetWis()*/
					   );

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		clTotalBA.SetLuk( clBasicBA.GetLuk() +
						clEquipBA.GetLuk() +
						  clHorseBA.GetLuk() +
						  clGuildBA.GetLuk() +
						  clHealthAdd.GetLuk() + 
						  clSetItemAdd.GetLuk() +
						  clSkillAdd.GetLuk()+
						  clTransFormBA.GetLuk() + 
						  clbufAdd.GetLuk());
	}
	else
	{
		if (bnpc == false)
		{
			clTotalBA.SetLuk( clBasicBA.GetLuk() +
							clEquipBA.GetLuk() +
							  clHorseBA.GetLuk() +
							  clGuildBA.GetLuk() +
							  clHealthAdd.GetLuk() + 
							  clSetItemAdd.GetLuk() +
							  clSkillAdd.GetLuk() +
							  clTransFormBA.GetLuk() + 
							  clbufAdd.GetLuk());
		}
	}

	// �ɷ�ġ ���ܻ�Ȳ
	if(pclidentityinfo)
	{
		switch(pclidentityinfo->siIdentity)
		{
		case IDENTITY_CASTLE:				clTotalBA.SetVit( clTotalBA.GetVit() * pclidentityinfo->clGodInfo.siCapa* 2);	break;
		case IDENTITY_VILLAGEGOD:
			{
				if ( pclKI->IsAtb(ATB_GOD) )
				{
					clTotalBA.SetVit( clTotalBA.GetVit() * pclidentityinfo->clGodInfo.siCapa * 2);
				}
				else
				{
					clTotalBA.SetVit( clTotalBA.GetVit() * pclidentityinfo->clGodInfo.siCapa * 1.6 );
				}

				// [����] �����ݰ����϶��� �Ʒ��� ����
				if( false == pclClient->IsCountrySwitch(Switch_HealthAddChange) )
				{
					if ( pclIP->Life > clTotalBA.GetVit() * 4 )
					{
						pclIP->SetLife(clTotalBA.GetVit() * 4);
					}
				}
				
			}
			break;
		case IDENTITY_VILLAGEGOD_SUMMON:	clTotalBA.SetVit( clTotalBA.GetVit() * pclidentityinfo->clGodInfo.siCapa* 2);	break;
		case IDENTITY_PERSON_SUMMON:		break;
		case IDENTITY_VILLAGEHUNT:			break;
		default:							break;
		}
	}

	bSetTotalBA = true;

	//--------------------------------------
	// ��� ���� ���� ���Ѵ�. 
	//--------------------------------------
	if(bnpc == false)
	{
		if(pclitemlist)
			siEquipLuck	= pclItemManager->GetLuck(pclitemlist);
		else
			siEquipLuck = 0;
	}

	siTotalLuck	+= siEquipLuck;

	////////////////////////////////////// /////////////////////////////////////////////////////////////////////////
	////  100. ��Ÿ �⺻ ����
	////  101. ���� ���ݷ� 
	////  102. ���� ���ݷ� 
	////  103. ���� ���߷� 
	////  104. ���� ���߷� 
	////  105. ���� ���� 
	////  106. ���� ���� 
	////  107. ���� ȸ���� 
	////  108. ���� ȸ���� 
	////  109. ü��
	////  110. ������ 
	////  111. ���Է� (?)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//--------------------------------------
	////  100. ��Ÿ �⺻ ����
	//--------------------------------------

	//--------------------------------------
	// ���� Ÿ���� ���Ѵ�. 
	//--------------------------------------
	CalculateAttackType(pclchar, activeweaponpos, pclitemlist);


	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		bool bacswitch = false;
		bool bdamageswitch = false;	
		
		//--------------------------------------
		////  101. ���� ���ݷ� 
		//--------------------------------------
		SetPhysicalAttackDemage(pclchar,pclitemlist, activeweaponpos, bnpc ,gamemode , pclskillinfo  ,pclidentityinfo , &bdamageswitch, siAttackWearStoneNum);

		//--------------------------------------
		////  102. ���� ���ݷ� 
		//--------------------------------------
		SetMagicalAttackDemage(pclchar,pclitemlist, activeweaponpos, bnpc ,gamemode , pclskillinfo ,pclidentityinfo , &bdamageswitch);

		//--------------------------------------
		////  103. ���� ���߷� 
		//--------------------------------------
		SetPhysicalHitRate(pclchar,pclitemlist, activeweaponpos, bnpc ,pclidentityinfo, pclskillinfo);

		//--------------------------------------
		////  104. ���� ���߷� 
		//--------------------------------------
		SetMagicalHitRate(pclchar,pclitemlist, activeweaponpos,bnpc ,pclidentityinfo, pclskillinfo);

		//--------------------------------------
		////  105. ���� ���� 
		//--------------------------------------
		SetPhysicalDefensiveRate(pclchar,pclitemlist, activeweaponpos,bnpc ,gamemode , pclskillinfo, pclidentityinfo, &bacswitch, siDefenseWearStoneNum);

		//--------------------------------------
		////  106. ���� ���� 
		//--------------------------------------
		SetMagicalDefensiveRate(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo);

		//--------------------------------------
		////  107. ���� ȸ���� 
		//--------------------------------------
		SetPhysicalDodgeRate(pclchar,pclitemlist, activeweaponpos, bnpc, pclskillinfo);

		//--------------------------------------
		////  108. ���� ȸ���� 
		//--------------------------------------
		SetMagicalDodgeRate(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo);

		//--------------------------------------
		////  109. ü�� 
		//--------------------------------------
		SetHitPoint(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo);

		//--------------------------------------
		////  110. ������ 
		//--------------------------------------
		SetManaPoint(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo);

		//--------------------------------------
		////  111. ���Է� 
		//--------------------------------------
		SetWeight(pclchar,pclitemlist, activeweaponpos,bnpc);


		//--------------------------------------
		////  112. ũ��Ƽ�� Ȯ�� �� ���� ������(�����ӵ�) ����.
		//--------------------------------------
		SetCritcalRate(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo , NULL);

		//--------------------------------------
		////  113. ��Ÿ��� ���� ����. - �̵��ӵ�, ��ȯ�� ���׹̳���.
		//--------------------------------------
		SetEtcSetting(pclchar,pclitemlist, activeweaponpos,bnpc, pclskillinfo , NULL , pclhorseinfo);

		if(bacswitch || bdamageswitch)
		{
			// Ŭ���̾�Ʈ���� �˸���. 
			if(pclchar)
			{

				cltGameMsgResponse_GeneralEft clinfo(pclchar->GetCharUnique(), siGeneralAC   , siGeneralDamage );
				cltMsg clMsg(GAMEMSG_RESPONSE_GENERALEFT, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclchar)->SendNeighbourMsg(&clMsg, true);
			}

		}

	}
	else  /////////////---------------- �̰����� ���� �����̴�.----------------------------------------------------------////////////////////////
	{
		// ���������� ����ؾ��ϴ����� �����ϴ� ����
		bool bCalcWeaponSkill = false;
		if ( (GAMEMODE_SERVER == pclClient->GameMode) && (pclitemlist) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
		{
			if ( (pclchar) && (IsPC( pclchar->GetID() )) )	bCalcWeaponSkill = true;
		}
		else if ( (GAMEMODE_CLIENT == pclClient->GameMode)  && (pclitemlist) && (pclitemlist) && (pclskillinfo) && ((PERSONITEM_WEAPON1 == activeweaponpos) || (PERSONITEM_WEAPON2 == activeweaponpos)) )
		{
			if ( (pclchar) && (1 == pclchar->GetID()) )		bCalcWeaponSkill = true;
		}

		//-------------------------------------------
		// ���׷��� ���Ѵ�. -�Ⱦ���.
		//-------------------------------------------
		if(pclBPB)
		{
			TotalDamageResist	= pclBPB->GetDamageResist(); // ���� ���׷�.
			TotalMagicResist	= pclBPB->GetMagicResist();  // ���� ���׷�.
		}
		else
		{
			TotalDamageResist	= 0;
			TotalMagicResist	= 0;
		}

		//--------------------------------------
		// ���� Ÿ���� ���Ѵ�. 
		//--------------------------------------
		CalculateAttackType(pclchar, activeweaponpos, pclitemlist);

		//--------------------------------------
		// ��� ���� ���� ���Ѵ�. 
		//--------------------------------------
		if(bnpc == false)
		{
			if(pclitemlist)
				siEquipLuck	= pclItemManager->GetLuck(pclitemlist);
			else
				siEquipLuck = 0;
		}

		siTotalLuck	+= siEquipLuck;


		//-----------------------------------
		// ������ ���� ������, ���� ���Ѵ�. 
		//-----------------------------------
		SI32 level = pclIP->GetLevel();
		if(level != siOldLevel)
		{
			siOldLevel		= level;
			siLevelDamage	= pclIP->CalcLevelDamage();
			siLevelAC		= CalcLevelAC(level);
		}

		//---------------------------------------------------------
		// ��æƮ�� ���� ������, ���� ���Ѵ�.      by tae-yang
		//---------------------------------------------------------
		if(pclitemlist)
		{
			pclBPB->siDefenR		= pclItemManager->GetEnchantAC(pclitemlist,pclchar);
		}

		//--------------------------------------
		// ���忡 ���� AC
		//-------------------------------------
		//-�¾�
		if(pclitemlist)
		{
			if (pclClient->IsCountrySwitch(Switch_StatusBug))
			{siEquipAC		= pclItemManager->GetAC(pclitemlist,pclchar);}
			else
			{siEquipAC		= pclItemManager->GetAC(pclitemlist,pclchar);}
		}
		else
		{
			siEquipAC = 0;
		}

		//cyj ���߿� �������ѿ� �ɸ��°��� ������ ���� 20% ����
		if(pclitemlist)
		{
			SI32 returnval = 0;
			if ((pclitemlist[PERSONITEM_HELMET].siUnique > 0 && (NULL != pclchar) && pclchar->CheckEquipCondition(pclClient->pclItemManager, PERSONITEM_HELMET, &pclitemlist[PERSONITEM_HELMET], &returnval) == false) ||
				(pclitemlist[PERSONITEM_ARMOUR].siUnique > 0 && (NULL != pclchar) && pclchar->CheckEquipCondition(pclClient->pclItemManager, PERSONITEM_ARMOUR, &pclitemlist[PERSONITEM_ARMOUR], &returnval) == false) ||
				(pclitemlist[PERSONITEM_BELT].siUnique   > 0 && (NULL != pclchar) && pclchar->CheckEquipCondition(pclClient->pclItemManager, PERSONITEM_BELT,   &pclitemlist[PERSONITEM_BELT],   &returnval) == false) )
			{
				siEquipAC = siEquipAC * 80 / 100;
			}
		}

		// �⺻ ����
		// ��ȯ���̰� ��� ���� ��
		if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (pclitemlist) && 
			( pclitemlist[PERSONITEM_HELMET].siUnique || pclitemlist[PERSONITEM_ARMOUR].siUnique || pclitemlist[PERSONITEM_BELT].siUnique || 
			pclitemlist[PERSONITEM_SHOES].siUnique || pclitemlist[PERSONITEM_MANTLE].siUnique ) 
		)
		{
			// ����� ������ ���� ������ ���ƾ� �⺻ ������ ����
			if ( pclchar->pclCI->clIP.GetLevel() == siDefenseWearStoneNum )
			{
				siDefaultAC = pclKI->clDefaultWeaponInfo.GetDefaultAC(); 
			}
		}
		else if((pclidentityinfo) && pclidentityinfo->siIdentity == IDENTITY_GMCREATE_MONSTER)
		{
			siDefaultAC = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultAC();
		}
		else
		{
			siDefaultAC = pclKI->clDefaultWeaponInfo.GetDefaultAC(); 
		}



		if(bmonsterhero)
		{
			siEvolveAC	= siDefaultAC;
		}
		else if ( pclKI->bSummonMall == TRUE )
		{
			/*
			siEvolveAC	= 0;

			if ( siEquipAC > 0 )
			{
				siDefaultAC = 0 ;
			}
			*/
		}
		else
		{
			siEvolveAC	= 0;
		}


		if ( pclchar ) 
		{

			//KHY - 0124 - ��í����- ���� ���� ������.
			if(pclchar->clTransFormInfo.bTransFormMode == true)
			{
				if( (pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAMAN"))			||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAGIRL"))			||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATMELEE"))			||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATRANGE"))			||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN"))  ||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST"))	||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE"))	||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE"))	||
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE"))	||	// �˻罺�Ǹ�(��)
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE"))	||	// �ųʽ��Ǹ�(��)
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYMELEE"))		||	// �������Ǹ�(��)
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYRANGE"))		||	// �ųʽ��Ǹ�(��)
					// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICERANGE"))			||	// ���� ����
					(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICEMELEE"))				// �罺��ġ
				  )				
					{
						// ���� ����.
						siTransFormAC = 80; // �⺻ ����.
						SI32 temState = 0;
						temState = siTransFormAC * (siTransFormSyc/2) / 100;

						siTransFormAC = siTransFormAC + temState; // ��ũ���� ������.				
					}
			}
		}

		//-----------------------------------------------
		// ��ȯ�� ��񼮿� ���� ���� ���
		//-----------------------------------------------
		SI16 siDefenseWearStoneAC = 0;

		if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (SUMMON_EQUIP_LIMITMINLEVEL < siDefenseWearStoneNum) )
		{
			REAL32 siDefenseWearStoneIncreasePercent = (siDefenseWearStoneNum - SUMMON_EQUIP_LIMITMINLEVEL) * 1.0;

			siDefenseWearStoneAC = (SI16)((REAL32)(siEquipPHysicalDefensive/100) * siDefenseWearStoneIncreasePercent);
		}

		//KHY - 0124 - ��í����- ���� ���� ������.
		TotalAC		= siLevelAC + siDefaultAC + siEquipAC + siEvolveAC + siTransFormAC + siDefenseWearStoneAC;

		// Identity �� �����ϴ� Ư�� ĳ������ ��� , ���� 
		if(pclidentityinfo)
		{
			switch(pclidentityinfo->siIdentity)
			{
			case IDENTITY_CASTLE:		TotalAC = TotalAC * pclidentityinfo->clGodInfo.siCapa*80/100;	break;
			case IDENTITY_VILLAGEGOD:
			case IDENTITY_VILLAGEGOD_SUMMON:
				{
					SI32 totalac = TotalAC;
					SI32 value = 0;

					if(totalac > 70)	
					{
						value += ((totalac - 70) * pclidentityinfo->clGodInfo.siCapa * 1 / 100);	
						totalac = 70;
					}
					if(totalac > 60)	
					{
						value += ((totalac - 60) * pclidentityinfo->clGodInfo.siCapa * 2 / 100);	
						totalac = 60;
					}
					if(totalac > 50)	
					{
						value += ((totalac - 50) * pclidentityinfo->clGodInfo.siCapa * 3 / 100);	
						totalac = 50;
					}
					if(totalac > 40)	
					{
						value += ((totalac - 40) * pclidentityinfo->clGodInfo.siCapa * 5 / 100);	
						totalac = 40;
					}
					if(totalac > 20)	
					{
						value += ((totalac - 20) * pclidentityinfo->clGodInfo.siCapa * 10 / 100);	
						totalac = 20;
					}
					if(totalac > 10)	
					{
						value += ((totalac - 10) * pclidentityinfo->clGodInfo.siCapa * 20 / 100);	
						totalac = 10;
					}
					if(totalac > 5)
					{
						value += ((totalac - 5) * pclidentityinfo->clGodInfo.siCapa * 30 / 100);		
						totalac = 5; 
					}

					value += (totalac * pclidentityinfo->clGodInfo.siCapa * 40 / 100);					


					TotalAC = value;	
					if(pclidentityinfo->siIdentity == IDENTITY_VILLAGEGOD_SUMMON)	{	TotalAC /= 3;			}
				}
				break;
			case IDENTITY_PERSON_SUMMON:break;
			case IDENTITY_VILLAGEHUNT:	break;
			default:					break;
			}
		}



		// ��Ʈ ȿ���� ���� AC���
		if( pclchar &&  
			( pclchar->m_siSetItemType == BOY_SULBIM_SETITEM  || pclchar->m_siSetItemType == GIRL_SULBIM_SETITEM ) )
		{
			TotalAC = TotalAC + 20;
		}

		// ����ȿ���� ���� AC���. 
		bool bacswitch = false;


		if(siGeneralAC)
		{
			//-------------------------------
			// ���Ӽ����� ��쿡�� ����ȿ���� �ð��� Ȯ���Ѵ�. 
			//-------------------------------
			if(gamemode == GAMEMODE_SERVER)
			{
				if(TABS(pclClient->CurrentClock - dwGeneralACClock) > 10000)
				{
					siGeneralAC			= 0;
					dwGeneralACClock	= 0;

					bacswitch = true;

				}
			}


			TotalAC = TotalAC * (100 + siGeneralAC ) / 100;
		}

		// Ȱ������ ���� AC���
		if(gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) && pclchar->pclCI->clBI.bCombatService )
			{
				TotalAC = TotalAC * 130 / 100;
			}
		}
		else if(gamemode == GAMEMODE_CLIENT)
		{
			if ( pclchar && pclchar->GetID() == 1 && pclchar->pclCI->clBI.bCombatService )
			{
				TotalAC = TotalAC * 130 / 100;
			}		
		}

		// ������ ���� AC ���
		if( gamemode == GAMEMODE_SERVER )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
				SI16 percent = 0 ;
				SI16 add = 0;

				if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
					percent += 20;

				if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
					percent += 20;

				if( clBuf.IsHaveBuf(BUF_DEFENSEUP) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_DEFENSEUP);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_DEFENSEUP30) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_DEFENSEUP30);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_MENTOR) )
					percent += 10;

				// [����] ������ ���๰�� �ִٸ� �߰��Ǵ� ����.	
				if( pclchar->pclCI->clBI.siHomeVillage > 0 )
				{
					cltServer* pclserver = (cltServer*)pclClient;
					cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );

					if (
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) 	== TRUE ||
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")))	   	== TRUE ||
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))   	== TRUE ||
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))	   	== TRUE || 	
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))	== TRUE || 
							pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))	== TRUE  		//[����] ������ ���� �ϼ��� ���� ����. => 2008-6-12
						)				
						percent += 10;
				}

				siBufAC = percent;
				TotalAC += TotalAC * percent / 100;
				TotalAC += add;
			}
		}
		else if( gamemode == GAMEMODE_CLIENT )
		{
			if ( (pclchar) && ( 1 == pclchar->GetID()) )
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
				SI16 percent = 0 ;
				SI16 add = 0;

				if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
					percent += 20;

				if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
					percent += 20;

				if( clBuf.IsHaveBuf(BUF_DEFENSEUP) )
				{
					SI32 siBufIndex = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_DEFENSEUP);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_DEFENSEUP30) )
				{
					SI32 siBufIndex = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_DEFENSEUP30);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_MENTOR) )
					percent += 10;

				// ũ��������Ʈ���� ���� ���� ����
				//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. C]
				cltCharClient* pclcharclient = (cltCharClient*)pclchar;
				for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
					if( pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))   ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		 ||		
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	)			
					{
						percent += 10;
					}
				}	
				siBufAC = percent;
				TotalAC += TotalAC * percent / 100;
				TotalAC += add;
			}
		}

		// ��Ī�� ���� ���� ���
		if ( gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
				{
					cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
					if ( pclunit )
					{
						TotalAC += TotalAC * pclunit->GetDefense() / 100;
						siNamingAC = pclunit->GetDefense();
					}
				}
				else
				{
					siNamingAC = 0;
				}
			}
		}
		else if ( gamemode == GAMEMODE_CLIENT )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) == 1 )
			{
				if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
				{
					cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
					if ( pclunit )
					{
						TotalAC += TotalAC * pclunit->GetDefense() / 100;
						siNamingAC = pclunit->GetDefense();
					}
				}
				else
				{
					siNamingAC = 0;
				}
			}
		}

		// ��ȯ�� ���ݷ� ���� ������ ����  ���� ���
		if (pclchar)
		{
			// ���� ��ȯ�����
			SI32 parentid = pclchar->GetSummonParentID();
			if(pclClient->pclCM->IsValidID(parentid))
			{
				// ��ȯ�� ������ ��ȯ�� ���ݷ�, ���� ���� ������ ������ �ִٸ� 
				SI32 summonskill = 0;

				if(pclskillinfo)
				{
					summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
				}
				// ��ȯ�� ������ ��ȯ�� ��ų ������ ���� ��ȯ���� ������ ������Ų��.

				SI32 defBonusPercent = 0;
				defBonusPercent = pclClient->GetSummonDefBonus( summonskill );

				TotalAC += TotalAC * defBonusPercent / 100;		

				SI32 bufBonusPercent = 0;

				if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP ) == true )
				{
					// ���� ���ʽ� ���� ���� ���� �ʴ´�
					bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_SUMMONATACUP) );
				}    

				if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) == true )
				{
					// ���� ���ʽ� ���� ���� ���� �ʴ´�
					bufBonusPercent = max( bufBonusPercent , 50 );
				}   

				if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_EGGMOONCAKE ) == true )
				{
					bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent(BUF_EVENT_EGGMOONCAKE) );
				}

				TotalAC += TotalAC * bufBonusPercent / 100;

			}

		}
		if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
		{
			// ��Űȿ���� ���ؤ� ������ ����Ѵ�.
			if ( gamemode == GAMEMODE_SERVER)
			{
				if ( pclchar && IsPC( pclchar->GetID() )  )
				{
					if(pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)
						{
							if(pclchar->pclFamily->GetOnParentNum() > 0 )
							{
								SI32 siEndDateVary = 0 ;
								SI32 siNowDateVary = 0	;
								SI32 siCookieLevel =	0	;
								SI32 siEffect =		0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
								siNowDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;
								if(  siEndDateVary > 0 && siEndDateVary > siNowDateVary )
								{									
									siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;
									siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;
									TotalAC = TotalAC + (TotalAC * siEffect / 100)	;
								}
							}	
						}						
					}
				}
			}
			else if (gamemode == GAMEMODE_CLIENT)
			{
				if ( pclchar && pclchar->GetID() == 1)
				{
					if(pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)
						{
							if(pclchar->pclFamily->GetOnParentNum() > 0 )
							{
								SI32 siEndDateVary = 0;
								SI32 siNowDateVary = 0;
								SI32 siCookieLevel =	0	;
								SI32 siEffect =		0	;
								siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( pclchar->pclCI->GetPersonID() ) ;
								siNowDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;
								if(  siEndDateVary > 0 &&  siEndDateVary > siNowDateVary )
								{	
									siCookieLevel = pclchar->pclFamily->GetMyCookieLevel(pclchar->pclCI->GetPersonID())	;
									siEffect = pclchar->pclFamily->GetCookieEffect( siCookieLevel)	;

									TotalAC = TotalAC + (TotalAC * siEffect / 100)	;

								}
							}
						}
					}
				}
			}


		}
		// PCK : Ż��(��ȣ)�� Ÿ�� �Ǹ� ������ 100 ����Ѵ�. (09.05.15)
		if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
		{
			if( pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER )
			{
				TotalAC += 100;
			}
		}

		//--------------------------------------
		// ���忡 ���� �ּ� ������ 
		//--------------------------------------
		bool bAttackWearStoneCondition	= false;
		SI32 defaultweaponmindamage		= 0;
		SI32 defaultweaponmaxdamage		= 0;

		// ��ȯ���϶� ��� �ִٸ�
		if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (pclitemlist) && (pclitemlist[PERSONITEM_WEAPON1].siUnique) )
		{	
			// ����� ������ ���� ������ ���ƾ� �⺻ ������ ����
			if ( pclchar->pclCI->clIP.GetLevel() == siAttackWearStoneNum )
			{
				bAttackWearStoneCondition	= true;
				defaultweaponmindamage		= pclKI->clDefaultWeaponInfo.GetDefaultMinDamage();
				defaultweaponmaxdamage		= pclKI->clDefaultWeaponInfo.GetDefaultMaxDamage();
			}
		}
		else if((pclidentityinfo) && pclidentityinfo->siIdentity == IDENTITY_GMCREATE_MONSTER)
		{
			defaultweaponmindamage = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultMinDamage();
			defaultweaponmaxdamage = pclGMCommandKindInfo->clDefaultWeaponInfo.GetDefaultMaxDamage();
		}
		// ��ȯ���� �ƴϰų� ��� ���ٸ�
		else
		{
			defaultweaponmindamage = pclKI->clDefaultWeaponInfo.GetDefaultMinDamage();
			defaultweaponmaxdamage = pclKI->clDefaultWeaponInfo.GetDefaultMaxDamage();
		}

		//----------------------------------------------------
		// ��ȯ������ ��ȭ�� ��ȯ������ ���, ��庥Ƽ�� ���� 
		//----------------------------------------------------
		if(bmonsterhero)
		{
			siEvolveDamage = defaultweaponmindamage * 3 / 2;
		}

		// ������ ������ �� ������ �������� ���Ѵ�. 
		SI32 damage = 0;
		if(pclitemlist)
		{//�ϴ�.
			if (pclClient->IsCountrySwitch(Switch_StatusBug)) {
				damage = pclItemManager->GetWeaponMinDamage(pclitemlist, activeweaponpos); 

				//cyj ��빫�Ⱑ �������ѿ� �ɸ��� ������ 20% ����
				SI32 returnval = 0;
				if ((pclitemlist[activeweaponpos].siUnique > 0) && (pclchar != NULL) && (pclchar->CheckEquipCondition(pclClient->pclItemManager, activeweaponpos, &pclitemlist[activeweaponpos], &returnval) == false) )
				{
					damage = damage * 80 / 100;
				}

				// ��� ���뼮 ���ǿ� �´� ��ȯ����� �⺻ �������� �����ش�
				if ( bAttackWearStoneCondition == true )
				{
					damage += defaultweaponmindamage ;
				}
			}
			else{
				damage = pclItemManager->GetWeaponMinDamage(pclitemlist, activeweaponpos, pclchar); 

				//cyj ��빫�Ⱑ �������ѿ� �ɸ��� ������ 20% ����
				SI32 returnval = 0;

				if ((pclitemlist[activeweaponpos].siUnique > 0)  && (pclchar != NULL) &&  (pclchar->CheckEquipCondition(pclClient->pclItemManager, activeweaponpos, &pclitemlist[activeweaponpos], &returnval) == false) )
				{
					damage = damage * 80 / 100;
				}

				// ��� ���뼮 ���ǿ� �´� ��ȯ����� �⺻ �������� �����ش�
				if ( bAttackWearStoneCondition == true )
				{
					damage += defaultweaponmindamage ;
				}
			}
			
		}
		else
		{
			damage = 0;
		}

		if(damage)
		{
			TotalEquipMinDamage = damage;
		}
		else
		{
			// ������ ������ ����Ʈ �������� ���Ѵ�. 
			TotalEquipMinDamage	= defaultweaponmindamage;
		}
		//-------------------------------------
		//��æƮ�� ���� ���嵥����  by tae-yang - �Ⱦ���.
		//-------------------------------------


		SI32 Enchantdamage = 0;
		SI32 EnchantRingdamage = 0;	
		SI32 EnchantType = 0;
		if(pclitemlist)
		{		

			for(SI32 i=0; i < 4; i++)
			{			
				EnchantRingdamage = EnchantRingdamage +  pclItemManager->GetEnchantAttFrom(pclitemlist, (i * 2 ) + 1); 			
			}		

			Enchantdamage =Enchantdamage + EnchantRingdamage;	
			EnchantType = pclItemManager->GetEnchantWeaponType(pclitemlist, activeweaponpos); 
		}
		else
		{
			Enchantdamage = 0;
			EnchantType = 0;
		}

		if(damage)
		{
			pclBPB->siAttackR = Enchantdamage;
			pclBPB->siAttackE = EnchantType;
		}
		else
		{
			// ������ ������ ����Ʈ ��æƮ �������� ���Ѵ�. 
			//pclBPB->siAttackR 	= 0;
			//pclBPB->siAttackE = 0;
		}
		//--------------------------------------
		// ���忡 ���� �ִ� ������ 
		//--------------------------------------
		if(pclitemlist)
		{

			if (pclClient->IsCountrySwitch(Switch_StatusBug)) {
				damage = pclItemManager->GetWeaponMaxDamage(pclitemlist, activeweaponpos); 
				/*		// ��ȯ������ ��쿡�� ����Ʈ �������� �����ش�.
				if ( pclKI->bSummonMall == TRUE )
				{
				damage += defaultweaponmaxdamage ;
				}*/
				//cyj ��빫�Ⱑ �������ѿ� �ɸ��� ������ 20% ����
				SI32 returnval = 0;
				if ( (pclitemlist[activeweaponpos].siUnique > 0) && (pclchar != NULL) && (pclchar->CheckEquipCondition(pclClient->pclItemManager, activeweaponpos, &pclitemlist[activeweaponpos], &returnval) == false) )
				{
					damage = damage * 80 / 100;
				}

				// ��� ���뼮 ���ǿ� �´� ��ȯ����� �⺻ �������� �����ش�
				if ( bAttackWearStoneCondition == true )
				{
					damage += defaultweaponmaxdamage ;
				}

			}
			else
			{
				damage = pclItemManager->GetWeaponMaxDamage(pclitemlist, activeweaponpos, pclchar); 
				/*		// ��ȯ������ ��쿡�� ����Ʈ �������� �����ش�.
				if ( pclKI->bSummonMall == TRUE )
				{
				damage += defaultweaponmaxdamage ;
				}*/
				//cyj ��빫�Ⱑ �������ѿ� �ɸ��� ������ 20% ����
				SI32 returnval = 0;
				if ( (pclitemlist[activeweaponpos].siUnique > 0)  && (pclchar != NULL) && (pclchar->CheckEquipCondition(pclClient->pclItemManager, activeweaponpos, &pclitemlist[activeweaponpos], &returnval) == false) )
				{
					damage = damage * 80 / 100;
				}

				// ��� ���뼮 ���ǿ� �´� ��ȯ����� �⺻ �������� �����ش�
				if ( bAttackWearStoneCondition == true )
				{
					damage += defaultweaponmaxdamage ;
				}
			}

		}
		else
		{
			damage = 0;
		}

		if(damage)
		{
			TotalEquipMaxDamage = damage;
		}
		else
		{
			// ������ ������ ����Ʈ �������� ���Ѵ�. 
			TotalEquipMaxDamage	= defaultweaponmaxdamage;
		}

		//----------------------------------------------------
		// ��ȯ�� ��񼮿� ���� ������ ���
		//----------------------------------------------------
		SI16 siAttackWearStoneMinDmg = 0;
		SI16 siAttackWearStoneMaxDmg = 0;

		if ( (pclidentityinfo) && (IDENTITY_PERSON_SUMMON == pclidentityinfo->siIdentity) && (SUMMON_EQUIP_LIMITMINLEVEL < siAttackWearStoneNum) )
		{
			REAL32 siAttackWearStoneIncreasePercent = (siAttackWearStoneNum - SUMMON_EQUIP_LIMITMINLEVEL) * 1.0;

			siAttackWearStoneMinDmg = (SI16)((REAL32)(TotalEquipMinDamage/100) * siAttackWearStoneIncreasePercent);
			siAttackWearStoneMaxDmg = (SI16)((REAL32)(TotalEquipMaxDamage/100) * siAttackWearStoneIncreasePercent);
		}

		//-----------------------------------
		// �ٷ¿� ���� ������. 
		//-----------------------------------
		// by LEEKH 2007.10.10 - PVP ��������ġ�� ServerInfo�� ����
		//if( pclClient->IsWhereServiceArea( ConstSwitch_PVP ) )
		if(pclClient->siEnablePVP == 1)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				siStrDamage		= clTotalBA.GetStrDamage(true);
			}
			else
			{
				siStrDamage		= clTotalBA.GetStrDamage(false);
			}
		}
		else
			siStrDamage		= clTotalBA.GetStrDamage(false);

		//----------------------------------
		// ������� ���߿� ���� ������. 
		//----------------------------------
		if(bnpc == false)
		{
			if(TABS(pclClient->GetFrame() - uiLastGetCriticalRateFrame )  > 100)
			{
				uiLastGetCriticalRateFrame = pclClient->GetFrame();

				SI32 skilllevel = 0;
				switch(siAttackType)
				{
				case ATTACKTYPE_SWORD:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESWORD1, 0, 0, pclitemlist);
					}
					break;
				case ATTACKTYPE_SPEAR:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESPEAR1, 0, 0, pclitemlist);
					}
					break;
				case ATTACKTYPE_AXE:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEAXE1, 0, 0, pclitemlist);
					}
					break;
				case ATTACKTYPE_STAFF:
				case ATTACKTYPE_STAFF1:
				case ATTACKTYPE_STAFF2:
				case ATTACKTYPE_NEW_STAFF2:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESTAFF1, 0, 0, pclitemlist);
					}
					break;
				case ATTACKTYPE_BOW:
				case ATTACKTYPE_BOW1:
				case ATTACKTYPE_NEW_BOW1:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEBOW1, 0, 0, pclitemlist);
					}
					break;
				case ATTACKTYPE_GUN:
				case ATTACKTYPE_GUN1:
				case ATTACKTYPE_NEW_GUN1:
					if(pclskillinfo)
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USEGUN1, 0, 0, pclitemlist);
					}
					break;
				}

				siCriticalRate = 0;
				if(skilllevel > 30)
				{
					siCriticalRate += ((skilllevel - 30) * 2);
					skilllevel = 30;
				}
				if(skilllevel > 20)
				{
					siCriticalRate += ((skilllevel - 20) * 5);
					skilllevel = 20;
				}

	      
				siCriticalRate += (skilllevel * 8);

				// ���⿡ �߰��� �ΰ��� Critical Rate�� �ΰ��Ѵ�.
				if(pclitemlist)
				{
					siCriticalRate += pclItemManager->GetEquipCriticalHitRate(pclitemlist, activeweaponpos);				
				}
				
				siMagicDecDelay = 0;
				if ( true == bCalcWeaponSkill )
				{
					// ���������� ���� �ʻ�� ����
					SI32 siSkillUnique		= 0;
					SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
					switch ( siItemType )
					{
						case ITEMTYPE_AXE:	{	siSkillUnique = SKILL_AXE_INCCRI;	}	break;
					}

					if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
					{
						SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
						SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
						if ( 0 < siWeaponSkillRate )
						{
							siCriticalRate = siCriticalRate + (siCriticalRate * siWeaponSkillRate / 100);
						}
					}

					// ���������� ���� �����ֱ� ����
					/*
					siSkillUnique = 0;
					switch ( siItemType )
					{
						case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_AXE_DECWEAINT;	}	break;
						case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_AXE_DECWEAINT;	}	break;
						case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_DECWEAINT;		}	break;
						case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_AXE_DECWEAINT;	}	break;
						case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_AXE_DECWEAINT;	}	break;
						case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_AXE_DECWEAINT;	}	break;
					}

					if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
					{
						SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
						SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
						if ( 0 < siWeaponSkillRate )
						{
							dwAttackInterval = dwAttackInterval - (dwAttackInterval * siWeaponSkillRate / 100);
						}
					}
					*/

					// ���������� ���� ��������ֱ� ����
					siSkillUnique = 0;
					switch ( siItemType )
					{
						case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_GUN_DECMAGDELAY;	}	break;
						case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_GUN_DECMAGDELAY;	}	break;
						case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_GUN_DECMAGDELAY;		}	break;
						case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_GUN_DECMAGDELAY;		}	break;
						case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_DECMAGDELAY;			}	break;
						case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_GUN_DECMAGDELAY;	}	break;
					}

					if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
					{
						SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0, pclitemlist );
						SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
						if ( 0 < siWeaponSkillRate )
						{
							siMagicDecDelay = siWeaponSkillRate;
						}
					}
				}
				/*
				// ���������� ���� �߰��ʻ��� �� ���� ���� �ӵ� ���̱⸦ �����Ѵ�.
				SI32 itemtype = 0 ;
				if ( pclitemlist )
					itemtype = pclItemManager->GetItemType(pclitemlist[activeweaponpos].siUnique) ;
				skilllevel = 0 ;
				siMagicDecDelay = 0 ;
				switch ( itemtype )
				{
				case ITEMTYPE_AXE:
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_AXE_INCCRI, 0, 0, pclitemlist);
						if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
						{
							SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW2,skilllevel) ;

							// SJY DEBUG
							siCriticalRate = siCriticalRate + siCriticalRate * rate / 100 ;
						}
					}
					break;
				case ITEMTYPE_GUN:
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_GUN_DECMAGDELAY, 0, 0, pclitemlist);
						if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
						{
							// SJY DEBUG
							siMagicDecDelay = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW2,skilllevel) ;
						}
					}
					break;
				}
				*/

				siCriticalRate = min(MAX_SCROLL_EFFECT, siCriticalRate);
			}

			//KHY - 1220 - ���Žý���.
			if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
			{
				if(siAttackType == ATTACKTYPE_SWORD)
				{								
					siCriticalRate += (SI32)(siTransFormSyc/2);
				}
				//���� ���� 100% ȿ�� ����
				else if(siAttackType == ATTACKTYPE_AXE)
				{
					//AXE 100% - ���� ������.
					if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
					{
						DWORD dTransFormAXEInterval = 1000;

						dwAttackInterval = dTransFormAXEInterval;
						//pclItemManager->pclItemInfo[ref]->SetAttackInterval(dTransFormAXEInterval);
					}
				}
			}
		}
		else	// NPC
		{

			siCriticalRate = pclKI->siCriticalRate;			//Kind�⺻�� �ʻ�� Ȯ���� ����ȴ�. 
			//----------------------------------------------------
			// ��ȯ�� ������ ���� Critical Hit ���
			//----------------------------------------------------
			/*
			if(pclsummonscroll)
			{
				siCriticalRate	+= pclsummonscroll->GetScrollCriticalHitRate(pclItemManager);
			}
			*/
			siCriticalRate = min(MAX_SCROLL_EFFECT, siCriticalRate);
			

		}

		if(bnpc == false)
		{
			//----------------------------------------------------
			// ������ �⺻ ���߷�
			//----------------------------------------------------
			if(pclitemlist)
			{
				siWeaponDefaultHitRate	= pclitemlist[activeweaponpos].GetDefaultHitRate(pclItemManager);
			}
			else
			{
				siWeaponDefaultHitRate = 0;
			}

			//KHY - 1220 - ���Žý���.
			if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
			{
				switch(siAttackType)
				{				
					case ATTACKTYPE_SPEAR :
					case ATTACKTYPE_BOW :
						siWeaponDefaultHitRate += (SI32)(siTransFormSyc/20);
						break;
				}
			}

			//----------------------------------------------------
			// ��� ���� ���߷� ��� 
			//----------------------------------------------------
			if(pclitemlist)
			{
				siEquipAssistHitRate	= min(150, pclItemManager->GetEquipHitRate(pclitemlist, activeweaponpos)); 
			}
			else
			{
				siEquipAssistHitRate = 0;
			}

			siEquipAssistHitRate = min(MAX_SCROLL_EFFECT, siEquipAssistHitRate);

			if(pclitemlist)
			{
				//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
				//siAddCrystalPhysicalHitRate = pclItemManager->GetEquipCrystalPhysicalHitRate(pclitemlist, activeweaponpos,pclchar);	// ����ü������ ���� ���߷� ���  - % 
				//siAddCrystalMagicalHitRate = pclItemManager->GetEquipCrystalMagicalHitRate(pclitemlist, activeweaponpos,pclchar);  // ����ü������ ���� ���߷� ���  - % 
			}

			//----------------------------------------------------
			// ��� ���� ������ ����. 
			//----------------------------------------------------
			if(pclitemlist)
			{

				siEquipAssistDamageReduceRate	= min(150, pclItemManager->GetDamageReduceRate(pclitemlist)); 
			}
			else
			{
				siEquipAssistDamageReduceRate = 0;
			}

			siEquipAssistDamageReduceRate = min(MAX_SCROLL_EFFECT, siEquipAssistDamageReduceRate);


		}
		else if(pclidentityinfo && pclidentityinfo->siIdentity)	
		{
			// Identity �� �����ϴ� Ư�� ĳ������ ��� , ���߷� 
			switch(pclidentityinfo->siIdentity)
			{
			case IDENTITY_CASTLE:				siEquipAssistHitRate = 1000; break; 
			case IDENTITY_VILLAGEGOD:			siEquipAssistHitRate = 500;	 break;
			case IDENTITY_VILLAGEGOD_SUMMON:	siEquipAssistHitRate = 200;	 break;
			case IDENTITY_PERSON_SUMMON:
				{
					siEquipAssistHitRate = 0;
					//----------------------------------------------------
					// ������ �⺻ ���߷�
					//----------------------------------------------------
					if(pclitemlist) siWeaponDefaultHitRate	= pclitemlist[activeweaponpos].GetDefaultHitRate(pclItemManager);
					else siWeaponDefaultHitRate = 0;
					//----------------------------------------------------
					// ��� ���� ���߷� ��� 
					//----------------------------------------------------
					if(pclitemlist) siEquipAssistHitRate	= min(150, pclItemManager->GetEquipHitRate(pclitemlist, activeweaponpos)); 
					else siEquipAssistHitRate = 0;

					siEquipAssistHitRate = min(MAX_SCROLL_EFFECT, siEquipAssistHitRate);

					//----------------------------------------------------
					// ��� ���� ������ ����. 
					//----------------------------------------------------
					if(pclitemlist) siEquipAssistDamageReduceRate	= min(150, pclItemManager->GetDamageReduceRate(pclitemlist)); 
					else siEquipAssistDamageReduceRate = 0;

					siEquipAssistDamageReduceRate = min(MAX_SCROLL_EFFECT, siEquipAssistDamageReduceRate);
				}
				break;
			case IDENTITY_VILLAGEHUNT:			siEquipAssistHitRate = 200;	 break;
			default:					break;
			}

			//----------------------------------------------------
			// ��ȯ�� ������ ���� ���߷� ���
			//----------------------------------------------------
			/*
			if(pclsummonscroll)
			{
				siEquipAssistHitRate			= siEquipAssistHitRate + pclsummonscroll->GetScrollHitRate(pclItemManager);
			}
			*/

			siEquipAssistHitRate = min(MAX_SCROLL_EFFECT, siEquipAssistHitRate);

			//----------------------------------------------------
			// ��ȯ�� ������ ���� Reduce Damage ���
			//----------------------------------------------------
			/*
			if(pclsummonscroll)
			{
				siEquipAssistDamageReduceRate	= siEquipAssistDamageReduceRate + pclsummonscroll->GetScrollDamageReduceRate(pclItemManager);
			}
			*/

			siEquipAssistDamageReduceRate = min(MAX_SCROLL_EFFECT, siEquipAssistDamageReduceRate);
		}


		//----------------------------------------------------
		// �������� �ִ�ġ�� ���Ѵ�.
		//----------------------------------------------------
		//MaxLife				= clTotalBA.GetVit() * VIT_LIFE_RATE;
		//MaxMana				= clTotalBA.GetMag() * INT_MANA_RATE;

		// �������������� ����������
		MaxMana = clTotalBA.GetMag() * INT_MANA_RATE;

		if ( true == bCalcWeaponSkill )
		{
			SI32 siSkillUnique		= 0;
			SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
			switch ( siItemType )
			{
			case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_STAFF_INCMAG;	}	break;
			case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_STAFF_INCMAG;	}	break;
			case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_STAFF_INCMAG;		}	break;
			case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_STAFF_INCMAG;		}	break;
			case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_STAFF_INCMAG;		}	break;
			case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_INCMAG;			}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					MaxMana = MaxMana + (MaxMana * siWeaponSkillRate / 100);
				}
			}
		}


		MaxLife = clTotalBA.GetVit() * VIT_LIFE_RATE;
		
		// �������������� ü������
		if ( true == bCalcWeaponSkill )
		{
			SI32 siSkillUnique		= 0;
			SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
			switch ( siItemType )
			{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCVIT;			}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_SWORD_INCVIT;	}	break;
				case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_SWORD_INCVIT;		}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_SWORD_INCVIT;		}	break;
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_SWORD_INCVIT;		}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_SWORD_INCVIT;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					MaxLife = MaxLife + (MaxLife * siWeaponSkillRate / 100);
				}
			}
		}

		if(pclchar!= NULL)
		{
			//SI32 siParentID = pclchar->GetSummonParentID();
			// PVP�� PVP_League�� 5�� ����.
			if(pclchar->siEnemUnique > 0)
			{
				MaxLife = MaxLife * 5	;
			}
			else if( pclchar->GetPVP_LeagueEnemyPersonID() > 0 )
			{
				MaxLife = MaxLife * 5	;
			}

			if ( pclClient->IsCountrySwitch(Switch_NewGuildHuntMapWar) )	// ����� ����ũ�� ������ hp5�� ��Ƣ��.
			{
				if( 0 < pclchar->pclCI->clBI.clGuildRank.GetEnemyGuild() )
				{
					MaxLife = MaxLife * 5	;
				}
			}

			if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				if( pclchar->m_siSetItemType )
				{
					MaxLife += MaxLife *    ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_1 )
										    + pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_2 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_3 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_4 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_HP, USE_SETITEM_5 )) * 0.01;
					
					MaxMana += MaxLife *    ( pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_1 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_2 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_3 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_4 )
											+ pclClient->pclItemManager->pcltSetItemAbilityManager->GetSetItemAbilityValue( pclchar, SETITEM_ABILITY_TYPE_MP, USE_SETITEM_5 )) * 0.01;	
				}
			}
		}

		// ������ ���� ����� �߰�
		if ( (pclchar) && (IsPC(pclchar->GetID())) )
		{
			MaxLife += pclchar->m_clMagicBufMgr.GetIncHP( pclchar );
		}

		if((pclchar!= NULL) && (pclitemlist != NULL)&&(pclchar->GetKind() != KIND_SYSTEM))
		{
			if(pclchar->pclCI->clIP.GetLife() > MaxLife)
				pclchar->pclCI->clIP.SetLife(MaxLife);
		}

		if((pclchar!= NULL) && (pclitemlist != NULL)&&(pclchar->GetKind() != KIND_SYSTEM))
		{
			//if(pclchar->pclCI->clIP.GetMana() > MaxMana)
				//pclchar->pclCI->clIP.SetMana(MaxMana);
		}

		if (pclchar)
		{
			// ���� ��ȯ�����
			SI32 parentid = pclchar->GetSummonParentID();
			if(pclClient->pclCM->IsValidID(parentid))
			{
				SI32 summonskill = 0;

				if(pclskillinfo)
				{
					summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON, 0, 0, &pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
				}
				MaxStamina		= pclClient->GetMaxStaminaValue(summonskill, pclchar->GetKind());

			}
		}
		else
			MaxStamina		= 10;

		//---------------------------------------------------
		// ���� ���ӿ� ���� ���ݷ��� ���Ѵ�.
		//---------------------------------------------------
		if(siAttackType == ATTACKTYPE_STAFF1 || siAttackType == ATTACKTYPE_STAFF2 || siAttackType == ATTACKTYPE_NEW_STAFF2)
		{
			// �����̼��� ���� �������� ���Ѵ�. 
			siStaffSkillDamage = 0;
			SI32 staffskilllevel = 0;

			if(pclskillinfo)
			{
				staffskilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_USESTAFF1, 0, 0, pclitemlist);
			}

			if(staffskilllevel > 40)
			{
				siStaffSkillDamage += (staffskilllevel - 40) / 2;
				staffskilllevel	= 40;
			}
			siStaffSkillDamage += (staffskilllevel * 2 / 4);

			if ( pclKI->bSummonMall == TRUE )
			{
				TotalMinDamage		= TotalEquipMinDamage * 2 + GetAddMagicDamage() + siStaffSkillDamage + siLevelDamage + siEvolveDamage;
				TotalMaxDamage		= TotalEquipMaxDamage * 2 + GetAddMagicDamage() + siStaffSkillDamage + siLevelDamage + siEvolveDamage;
			}
			else
			{
				TotalMinDamage		= TotalEquipMinDamage + GetAddMagicDamage() + siStaffSkillDamage + siLevelDamage + siEvolveDamage;
				TotalMaxDamage		= TotalEquipMaxDamage + GetAddMagicDamage() + siStaffSkillDamage + siLevelDamage + siEvolveDamage;
			}
		}
		else if ( siAttackType == ATTACKTYPE_STAFFWIND && pclKI->bSummonMall == TRUE ) // ������� ���
		{
			if ( pclitemlist )
			{
				TotalMinDamage		= TotalEquipMinDamage * 2 + GetAddMagicDamage() + siLevelDamage + siEvolveDamage;
				TotalMaxDamage		= TotalEquipMaxDamage * 2 + GetAddMagicDamage() + siLevelDamage + siEvolveDamage;
			}
			else
			{
				TotalMinDamage		= TotalEquipMinDamage + GetAddMagicDamage() + siLevelDamage + siEvolveDamage;
				TotalMaxDamage		= TotalEquipMaxDamage + GetAddMagicDamage() + siLevelDamage + siEvolveDamage;
			}
		}
		else
		{
			TotalMinDamage		= TotalEquipMinDamage + siStrDamage + siLevelDamage + siTorpedoDamage	+ siEvolveDamage;
			TotalMaxDamage		= TotalEquipMaxDamage + siStrDamage + siLevelDamage + siTorpedoDamage	+ siEvolveDamage;

			//KHY - 1220 - ���Žý���.
			if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
			{
				switch(siAttackType)
				{ 
					case ATTACKTYPE_SWORD:
					case ATTACKTYPE_SPEAR:
						{
							if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
							{
								TotalMinDamage += 20;
								TotalMaxDamage += 20;
							}
						}
						break;
					case ATTACKTYPE_AXE:
						{
							TotalMinDamage += (SI32)(siTransFormSyc/2);
							TotalMaxDamage += (SI32)(siTransFormSyc/2);
						}
						break;					
					case ATTACKTYPE_GUN:
						{
							TotalMinDamage += (SI32)((REAL32)siTransFormSyc*(REAL32)0.4);
							TotalMaxDamage += (SI32)((REAL32)siTransFormSyc*(REAL32)0.4);
						}
						break;					
				}
			}		
		}

		// Identity �� �����ϴ� Ư�� ĳ������ ��� , ���ݷ� 
		if(pclidentityinfo)
		{

			switch(pclidentityinfo->siIdentity)
			{
			case IDENTITY_CASTLE:		
				{
					TotalMinDamage *= pclidentityinfo->clGodInfo.siCapa * 10 /100;
					TotalMaxDamage *= pclidentityinfo->clGodInfo.siCapa * 10 /100;		
				}
				break;
			case IDENTITY_VILLAGEGOD:	
			case IDENTITY_VILLAGEGOD_SUMMON:
				{
					SI32 totalmindamage = TotalMinDamage;
					SI32 totalmaxdamage = TotalMaxDamage;
					SI32 value = 0;
					SI32 capa	= pclidentityinfo->clGodInfo.siCapa;

					if(totalmindamage > 50)
					{
						value += ((totalmindamage - 50) * capa * 1 / 100);	
						totalmindamage = 50;
					}
					if(totalmindamage > 40)
					{
						value += ((totalmindamage - 40) * capa * 2 / 100);	
						totalmindamage = 40;
					}
					if(totalmindamage > 30)
					{
						value += ((totalmindamage - 30) * capa * 3 / 100);	
						totalmindamage = 30;
					}
					if(totalmindamage > 20)
					{
						value += ((totalmindamage - 20) * capa * 5 / 100);	
						totalmindamage = 20;
					}
					if(totalmindamage > 10)
					{
						value += ((totalmindamage - 10) * capa * 10 / 100);	
						totalmindamage = 10;
					}
					if(totalmindamage > 5)
					{
						value += ((totalmindamage - 5) * capa * 20 / 100);	
						totalmindamage = 5;
					}
					value += (totalmindamage * capa * 30 / 100);	

					TotalMinDamage = value;	

					value = 0;

					if(totalmaxdamage > 50)
					{
						value += ((totalmaxdamage - 50) * capa * 1 / 100);	
						totalmaxdamage = 50;
					}
					if(totalmaxdamage > 40)
					{
						value += ((totalmaxdamage - 40) * capa * 2 / 100);	
						totalmaxdamage = 40;
					}
					if(totalmaxdamage > 30)
					{
						value += ((totalmaxdamage - 30) * capa * 3 / 100);	
						totalmaxdamage = 30;
					}
					if(totalmaxdamage > 20)
					{
						value += ((totalmaxdamage - 20) * capa * 5 / 100);	
						totalmaxdamage = 20;
					}
					if(totalmaxdamage > 10)
					{
						value += ((totalmaxdamage - 10) * capa * 10 / 100);	
						totalmaxdamage = 10;
					}
					if(totalmaxdamage > 5)
					{
						value += ((totalmaxdamage - 5) * capa * 20 / 100);	
						totalmaxdamage = 5;
					}
					value += (totalmaxdamage * capa * 30 / 100);	

					TotalMaxDamage = value;	
				}
				break;
			case IDENTITY_PERSON_SUMMON:
				{
					TotalMinDamage = TotalMinDamage + (SI32)(TotalMinDamage * PERSON_SUMMON_ATTACKBONUS_PERCENT * 0.01f) + siAttackWearStoneMinDmg;
					TotalMaxDamage = TotalMaxDamage + (SI32)(TotalMaxDamage * PERSON_SUMMON_ATTACKBONUS_PERCENT * 0.01f) + siAttackWearStoneMaxDmg;

					if (pclchar)
					{
						// ���� ��ȯ�����
						SI32 parentid = pclchar->GetSummonParentID();
						if(pclClient->pclCM->IsValidID(parentid))
						{
							SI32 summonskill = 0;

							if(pclskillinfo)
							{
								summonskill = pclClient->pclCM->CR[parentid]->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_SUMMON,
									0,
									0,
									&pclClient->pclCM->CR[parentid]->pclCI->clCharItem.clItem[0], parentid );
							}

							// ��ȯ�� ������ ��ȯ�� ��ų ������ ���� ��ȯ���� ���ݷ��� ������Ų��.
							SI32 attackBonusPercent = 0;
							attackBonusPercent = pclClient->GetSummonAttackBonus( summonskill );

							TotalMinDamage += TotalMinDamage * attackBonusPercent / 100;
							TotalMaxDamage += TotalMaxDamage * attackBonusPercent / 100;

							// ��ȯ�� ������ ��ȯ�� ���ݷ�, ���� ���� ������ ������ �ִٸ� 

							SI32 bufBonusPercent = 0;

							if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_SUMMONATACUP ) == true )
							{
								bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent( BUF_SUMMONATACUP ) );
							}   
							if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) == true )
							{
								bufBonusPercent = max( bufBonusPercent , 20 );
							}   

							if( pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_EVENT_EGGMOONCAKE ) == true )
							{
								bufBonusPercent = max( bufBonusPercent , pclClient->pclCM->CR[parentid]->pclCI->clBI.clBufInfo.GetBufPercent( BUF_EVENT_EGGMOONCAKE ) );
							}

							TotalMinDamage += TotalMinDamage * bufBonusPercent / 100;
							TotalMaxDamage += TotalMaxDamage * bufBonusPercent / 100;
						}

					}

				}
				break;
			case IDENTITY_VILLAGEHUNT:								break;
			default:												break;
			}
		}
		
		// PCK : ����ġ�� Ÿ�� ���� ��� ���ݷ� + 100�� ���ش�.
		// [���] ��ȣ�� Ÿ�� ���� ��� ���ݷ� + 100�� ���ش�. (09.05.15)
		// [���] ������Ʈ�� Ÿ�� ���� ��� ���ݷ� + 100�� ���ش�. (09.07.30)
		// [����] ������� Ÿ�� ���� ��� ���ݷ� + 100�� ���ش�. (09.12.31)
		if((pclchar) && (IsPC(pclchar->GetID())) && (pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
		{
			if( pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_FIREHATCH || 
				pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_WHITETIGER ||
				pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_BAPHOMET ||
				pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()->siHorseUnique == HORSEUNIQUE_SASURI)
			{
				TotalMinDamage += 100;
				TotalMaxDamage += 100;
			}
		}

		// ����ȿ���� ���� ���������. 
		bool bdamageswitch = false;	
		if(siGeneralDamage)
		{		
			//-------------------------------
			// ���Ӽ����� ��쿡�� ����ȿ���� �ð��� Ȯ���Ѵ�. 
			//-------------------------------
			if(gamemode == GAMEMODE_SERVER)
			{
				if(TABS(pclClient->CurrentClock - dwGeneralDamageClock) > 10000)
				{
					siGeneralDamage			= 0;				
					dwGeneralDamageClock	= 0;

					bdamageswitch = true;
				}
			}

			TotalMinDamage = TotalMinDamage * (100 + siGeneralDamage ) / 100;
			TotalMaxDamage = TotalMaxDamage * (100 + siGeneralDamage ) / 100;
		}

		// ���������� ���� ���ݷ��� �����Ѵ�.
		if ( true == bCalcWeaponSkill )
		{
			// ���� �������ͽ��� ��� ����/���� ���ݷ��� �������� ���� �ʱ� ������ �ΰ���� �����ش�
			SI32 siSkillUnique		= 0;
			SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );

			// �������ݷ����
			switch ( siItemType )
			{
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_INCWEAAT;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					TotalMinDamage = TotalMinDamage + (TotalMinDamage * siWeaponSkillRate / 100);
					TotalMaxDamage = TotalMaxDamage + (TotalMinDamage * siWeaponSkillRate / 100);
				}
			}

			// �������ݷ����
			siSkillUnique = 0;
			switch ( siItemType )
			{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCMAGAT;	}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_INCMAGAT;	}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_INCMAGAT;		}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_INCMAGAT;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					TotalMinDamage = TotalMinDamage + (TotalMinDamage * siWeaponSkillRate / 100);
					TotalMaxDamage = TotalMaxDamage + (TotalMinDamage * siWeaponSkillRate / 100);
				}
			}

			
		}
		/*
		//	if ( gamemode == GAMEMODE_SERVER )
		{
			if(bnpc == false && personid)
			{
				SI32 itemtype = 0 ;
				if ( pclitemlist )
					itemtype = pclItemManager->GetItemType(pclitemlist[activeweaponpos].siUnique) ;
				SI32 skilllevel = 0 ;

				switch ( itemtype )
				{
				case ITEMTYPE_SWORD:
					{
						//skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_SWORD_INCWEAAT, 0, 0, pclitemlist);//
					}
					break;
				case ITEMTYPE_GUN:
					{
						skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_GUN_INCWEAAT, 0, 0, pclitemlist);
					}
					break;
				}

				if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
				{
					// SJY DEBUG
					SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW2,skilllevel) ;

					TotalMinDamage = TotalMinDamage + TotalMinDamage * rate / 100 ;
					TotalMaxDamage = TotalMaxDamage + TotalMaxDamage * rate / 100 ;
				}
			}
		}
		*/

		// Ȱ������ ���� Attack���
		if(gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) && pclchar->pclCI->clBI.bCombatService )
			{
				TotalMinDamage = TotalMinDamage + TotalMinDamage * 30 / 100 ;
				TotalMaxDamage = TotalMaxDamage + TotalMaxDamage * 30 / 100 ;
			}
		}
		else if(gamemode == GAMEMODE_CLIENT)
		{
			if ( pclchar && pclchar->GetID() == 1 && pclchar->pclCI->clBI.bCombatService )
			{
				TotalMinDamage = TotalMinDamage + TotalMinDamage * 30 / 100 ;
				TotalMaxDamage = TotalMaxDamage + TotalMaxDamage * 30 / 100 ;
			}		
		}
		if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
		{
			// ��Ű�� ���� ���ݷ� ��� 
			if(gamemode == GAMEMODE_SERVER)
			{
				if ( pclchar && IsPC( pclchar->GetID() ) )
				{
					if ( pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)	// ��Ű ȿ���� �ڽ��϶���
						{
							if(pclchar->pclFamily->GetOnParentNum() > 0 && pclchar->pclFamily->GetOnChildrenNum() > 0 )
							{
								cltServer* pclserver = (cltServer*)pclClient;
								SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
								if ( siPersonID > 0) 
								{
									
									SI32 siEndDateVary =	0	;
									SI32 siServerDateVary =	0	;
									siEndDateVary =pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
									siServerDateVary = pclserver->pclTime->clDate.GetHourVary();
									if ( siEndDateVary>0 && siServerDateVary>0  ) 
									{
										if(  siEndDateVary  >  siServerDateVary )
										{
											SI32 percent	= 0;
											SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel(siPersonID )	;// ������ ���� ����
											percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

											TotalMinDamage += TotalMinDamage * percent / 100;
											TotalMaxDamage += TotalMaxDamage * percent / 100;
										}
									}
								}
							}
						}
					}
				}
			}
			else if(gamemode == GAMEMODE_CLIENT)
			{
				if ( pclchar && pclchar->GetID() == 1)
				{
					if( pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN)	// ��Ű ȿ���� �ڽ��϶���
						{
							if(pclchar->pclFamily->GetOnParentNum() > 0 && pclchar->pclFamily->GetOnChildrenNum() > 0)
							{
								SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
								if ( siPersonID > 0 ) 
								{
									
									SI32 siEndDateVary = 0	;
									SI32 siClientDateVary = 0	;
									siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
									siClientDateVary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;

									if(   siEndDateVary >0 && siClientDateVary > 0 )
									{
										if ( siEndDateVary > siClientDateVary ) 
										{
											SI32 percent	= 0;
											SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( siPersonID )	;// ������ ���� ����
											percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;
											TotalMinDamage += TotalMinDamage * percent / 100;
											TotalMaxDamage += TotalMaxDamage * percent / 100;
										}
									}

								}
							}

						}
					}				
				}		
			}
		}
		
		// �� �����̾� ���� Ǯ������ Ư���ɷ� ����.
		//// �����̾� ������ Ǯ���� �϶� ���ݷ� 5% ����
		//if(gamemode == GAMEMODE_SERVER)
		//{
		//	if ( pclchar && IsPC( pclchar->GetID() ) )
		//	{
		//		cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()	;
		//		if ( pclHorse == NULL)
		//		{
		//		}
		//		else
		//		{
		//			SI32 siEquipPremiumPartsNum = pclHorse->GetPremiumPartsNum()	;
		//			if ( siEquipPremiumPartsNum == 3 )
		//			{
		//				SI32 siHorseUnique = pclHorse->siHorseUnique ;
		//				switch (siHorseUnique )
		//				{
		//				case HORSEUNIQUE_BROWN:	// ������
		//				case HORSEUNIQUE_BLACK:// �渶
		//				case HORSEUNIQUE_WHITE:// �鸶
		//				case HORSEUNIQUE_RED://���丶
		//				case HORSEUNIQUE_RUDOLF ://�絹��
		//				case HORSEUNIQUE_STEEL ://ö�⸶
		//				case HORSEUNIQUE_BEAST ://����ȣ
		//				case HORSEUNIQUE_THOUSAND ://õ����
		//				case HORSEUNIQUE_ZEBRA ://��踶
		//					{
		//						TotalMinDamage = TotalMinDamage + TotalMinDamage * 5 / 100 ;
		//						TotalMaxDamage = TotalMaxDamage + TotalMaxDamage * 5 / 100 ;
		//					}
		//				}
		//			}
		//			
		//		}
		//	}
		//}
		//else if(gamemode == GAMEMODE_CLIENT)
		//{
		//	if ( pclchar && pclchar->GetID() == 1 )
		//	{
		//		cltHorse* pclHorse = pclchar->pclCI->clHorseInfo.GetCurrentShowHorse()	;
		//		if ( pclHorse == NULL)
		//		{
		//		}
		//		else
		//		{
		//			SI32 siEquipPremiumPartsNum = pclHorse->GetPremiumPartsNum()	;
		//			if ( siEquipPremiumPartsNum == 3 )
		//			{
		//				SI32 siHorseUnique = pclHorse->siHorseUnique ;
		//				switch (siHorseUnique )
		//				{
		//				case HORSEUNIQUE_BROWN:	// ������
		//				case HORSEUNIQUE_BLACK:// �渶
		//				case HORSEUNIQUE_WHITE:// �鸶
		//				case HORSEUNIQUE_RED://���丶
		//				case HORSEUNIQUE_RUDOLF ://�絹��
		//				case HORSEUNIQUE_STEEL ://ö�⸶
		//				case HORSEUNIQUE_BEAST ://����ȣ
		//				case HORSEUNIQUE_THOUSAND ://õ����
		//				case HORSEUNIQUE_ZEBRA ://��踶
		//					{
		//						TotalMinDamage = TotalMinDamage + TotalMinDamage * 5 / 100 ;
		//						TotalMaxDamage = TotalMaxDamage + TotalMaxDamage * 5 / 100 ;
		//					}
		//				}

		//			}
		//		}
		//	}		
		//}		
		// ������ ���� ���ݷ� ���
		if( gamemode == GAMEMODE_SERVER )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
				SI16 percent = 0 ;
				SI16 add = 0;


				if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
					percent += 20;
				
				if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
					percent += 10;

				if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
					percent += 10;

				if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
					percent += 20;


				if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}
			
				if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
				{
					percent += 10;
				}

				if( clBuf.IsHaveBuf(BUF_THANKSGIVING_DAY) )
				{
					percent += 10;
				}

				if( clBuf.IsHaveBuf(BUF_MENTOR) )
					percent += 10;

				// ũ��������Ʈ���� ���� ���ݷ� ����
				//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. S]
				if( pclchar->pclCI->clBI.siHomeVillage > 0 )
				{
					cltServer* pclserver = (cltServer*)pclClient;
					cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );
					if (pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE"))) == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))	   == TRUE ||
						pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))	   == TRUE		)
						
						percent += 10;
				}
				siBufDamage = percent;
				TotalMinDamage += TotalMinDamage * percent / 100;
				TotalMinDamage += add;
				TotalMaxDamage += TotalMaxDamage * percent / 100;
				TotalMaxDamage += add;
			}
		}
		else if( gamemode == GAMEMODE_CLIENT )
		{
			if ( (pclchar) && ( 1 == pclchar->GetID()) )
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );
				SI16 percent = 0 ;
				SI16 add = 0;

				if( clBuf.IsHaveBuf(BUF_FRIENDSHIP) )
				{
					percent += 20;
				}

				if( clBuf.IsHaveBuf(BUF_HINAMOCHI) )
				{
					percent += 20;
				}

				if( clBuf.IsHaveBuf(BUF_ATTACKUP) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_ATTACKUP30) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_ATTACKUP30);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) )
				{
					SI32 siBufIndex = clBuf.FindBufSlot(BUF_EVENT_EGGMOONCAKE);
					if( siBufIndex >= 0 && siBufIndex < MAX_BUF_COUNT )
						percent = max( percent , clBuf.m_stBuf[siBufIndex].siPercent );
				}

				if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
				{
					percent += 10;
				}


				if( clBuf.IsHaveBuf(BUF_HAPPYBEAN) )
				{
					percent += 10;
				}

				if( clBuf.IsHaveBuf(BUF_MENTOR) )
					percent += 10;

				//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� ��������� ���� �ֹο��� ���� ����. C]
				cltCharClient* pclcharclient = (cltCharClient*)pclchar;
				for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
					if( pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE")) ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_KADOMACH"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE"))	 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))		 ||		
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1"))		 ||
						pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE"))	)				
					{
						percent += 10;
					}
				}

				siBufDamage = percent;
				TotalMinDamage += TotalMinDamage * percent / 100;
				TotalMinDamage += add;
				TotalMaxDamage += TotalMaxDamage * percent / 100;
				TotalMaxDamage += add;
			}
		}

		// ��Ī�� ���� ���ݷ� ���
		if ( gamemode == GAMEMODE_SERVER)
		{
			if ( pclchar && IsPC( pclchar->GetID() ) )
			{
				if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
				{
					cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
					if ( pclunit )
					{
						TotalMinDamage += TotalMinDamage * pclunit->GetAttack() / 100;
						TotalMaxDamage += TotalMaxDamage * pclunit->GetAttack() / 100;

						siNamingDamage = pclunit->GetAttack();
					}

				}
				else
				{
					siNamingDamage = 0;
				}
			}
		}
		else if ( gamemode == GAMEMODE_CLIENT )
		{
			if ( pclchar && IsPC( pclchar->GetID() ) == 1 )
			{
				if ( pclchar->pclCI->clPersonNaming.m_siSelectedLevel > 0 )
				{
					cltNamingQuestUnit* pclunit = pclClient->pclNamingQuestManager->GetQuestInfo( pclchar->pclCI->clPersonNaming.m_siSelectedIndex, pclchar->pclCI->clPersonNaming.m_siSelectedLevel );
					if ( pclunit )
					{
						TotalMinDamage += TotalMinDamage * pclunit->GetAttack() / 100;
						TotalMaxDamage += TotalMaxDamage * pclunit->GetAttack() / 100;
						
						siNamingDamage = pclunit->GetAttack();
					}

				}
				else
				{
					siNamingDamage = 0;
				}
			}
		}

		// ��Ű�� ���� ���ݷ� ��� 
		if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
		{
			if(gamemode == GAMEMODE_SERVER)
			{
				if ( pclchar && IsPC( pclchar->GetID() ) )
				{
					if(pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN  )
						{
							if( pclchar->pclFamily->GetOnParentNum() > 0 && pclchar->pclFamily->GetOnChildrenNum() > 0 )
							{
								cltServer* pclserver = (cltServer*)pclClient;
								SI32 siPersonID = pclchar->pclCI->GetPersonID()	;
								if ( siPersonID > 0 ) 
								{
									SI32 siEndDateVary =	0	;
									SI32 siServerHourVary =	0	;
									siEndDateVary = pclchar->pclFamily->GetMyCookie_EndTime(siPersonID )	;
									siServerHourVary = pclserver->pclTime->clDate.GetHourVary()	;
									if(  siEndDateVary > 0 &&  siServerHourVary > 0 )
									{
										if ( siEndDateVary >siServerHourVary) 
										{
											SI32 percent	= 0;
											SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( siPersonID )	;// ������ ���� ����
											percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;

											TotalMinDamage += TotalMinDamage * percent / 100;
											TotalMaxDamage += TotalMaxDamage * percent / 100;
										}
									}
								}
							}				
						}						
					}				
				}
			}
			else if(gamemode == GAMEMODE_CLIENT)
			{
				if ( pclchar && pclchar->GetID() == 1)
				{
					if(pclchar->pclFamily != NULL )
					{
						if(pclchar->pclFamily->GetMyClass_InFamily() == MYCLASS_IN_FAMILY_CHILDREN )
						{
							if(pclchar->pclFamily->GetOnParentNum() > 0 && pclchar->pclFamily->GetOnChildrenNum() > 0)
							{
								SI32  siPersonID = pclchar->pclCI->GetPersonID();
								if ( siPersonID > 0 ) 
								{
									SI32 siEndHourvary = pclchar->pclFamily->GetMyCookie_EndTime( siPersonID )	;
									SI32 siClientHourvary = ((cltClient*)pclClient)->clClientDate.GetHourVary()	;
									if(    siEndHourvary > 0 &&    siClientHourvary > 0 )
									{
										if( siEndHourvary > siClientHourvary  )
										{
											SI32 percent	= 0;
											SI32 siCookieLevel = pclchar->pclFamily->GetMyCookieLevel( pclchar->pclCI->GetPersonID() )	;// ������ ���� ����
											percent = pclchar->pclFamily->GetCookieEffect( siCookieLevel )	;
											TotalMinDamage += TotalMinDamage * percent / 100;
											TotalMaxDamage += TotalMaxDamage * percent / 100;
										}
									}
								}							
							}
						}
					}				
				}		
			}


		}
		
		//--------------------------------------------------
		// �̵� �ӵ��� ���Ѵ�. 
		//--------------------------------------------------
		BasicMoveSpeed		= pclKI->siMoveSpeed;
		
		if(pclitemlist)
		{
			if (pclClient->IsCountrySwitch(Switch_StatusBug)) {
				ShoesMoveSpeed		= pclItemManager->GetMoveSpeed(pclitemlist);
			}
			else{
				ShoesMoveSpeed		= pclItemManager->GetMoveSpeed(pclitemlist,pclchar);
			}
			
		}
		else
		{
			ShoesMoveSpeed = 0;
		}

		if(GivenMoveSpeed)
		{
			TotalMoveSpeed		= GivenMoveSpeed;
		}
		else
		{
			// ���� Ÿ�� �ִٸ�, 
			if(pclhorseinfo && pclhorseinfo->siCurrentHorseRIDEHORSE == true)
			{
				cltHorse* pclhorse = pclhorseinfo->GetCurrentShowHorse();
				if (pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HAPPYBEAN) ||			//���Ǻ� �̺�Ʈ ����Ÿ���� ������ �̼��ִ� [2007.08.27 �ռ���]
							pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_THANKSGIVING_DAY)) )	//[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. �̵��ӵ� �ִ�]
				{ 
					TotalMoveSpeed = 20;
				}
				else if(pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_MENTOR)))
				{
					if( 15 > BasicMoveSpeed + ShoesMoveSpeed && 15 > pclhorse->GetRealMoveSpeed())
					{
						TotalMoveSpeed = 15;
					}
					else if(pclhorse)
						TotalMoveSpeed	= pclhorse->GetRealMoveSpeed();		// ���� �̵��ӵ��� �ӵ��� ��ü�Ѵ�.
				}
				else
				{
					if(pclhorse)
						TotalMoveSpeed	= pclhorse->GetRealMoveSpeed();		// ���� �̵��ӵ��� �ӵ��� ��ü�Ѵ�. 

				}
			}
				
			// ���� Ÿ�� ���� ���¶��, 
			else 
			{
				if (pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_HAPPYBEAN) ||			//���Ǻ� �̺�Ʈ ����Ÿ���� ������ �̼��ִ� [2007.08.27 �ռ���]
								pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_THANKSGIVING_DAY)) )	//[�߰� : Ȳ���� 2007. 11. 12 �߼� ������ �̺�Ʈ. �̵��ӵ� �ִ�] 
				{ 
					TotalMoveSpeed = 20;
				}
				else if(pclchar && (pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_MENTOR)))
				{
					if( 15 > BasicMoveSpeed + ShoesMoveSpeed )
					{
						TotalMoveSpeed = 15;
					}
				}
				else
				{// ������ ���� ���� Ÿ�� ���� ���¶��
					TotalMoveSpeed		= BasicMoveSpeed + ShoesMoveSpeed;
				}			
			}
		}


		//--------------------------------------------------
		// ���� ���ɼ��� ��� ���ɼ��� ���Ѵ�. 
		//--------------------------------------------------
		AR					= ( clTotalBA.GetDex() * 10 ) / 10;		// ��ø���� 100% ����. 
		DR					= (AR / 3) + (TotalAC / 2);

        
		// ���������� ���� ������, ȸ����, ������ �����Ѵ�.
		if ( true == bCalcWeaponSkill )
		{
			// ȸ����
			SI32 siSkillUnique		= 0;
			SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
			switch ( siItemType )
			{
				case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_INCDR;			}	break;
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_SWORD_INCDR;	}	break;
				case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_SWORD_INCDR;		}	break;
				case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_SWORD_INCDR;		}	break;
				case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_SWORD_INCDR;		}	break;
				case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_SWORD_INCDR;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					DR = DR + (DR * siWeaponSkillRate / 100);
				}
			}

			// �����
			siSkillUnique = 0;
			switch ( siItemType )
			{
				case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_INCAC;	}	break;
			}

			if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
			{
				SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
				SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
				if ( 0 < siWeaponSkillRate )
				{
					TotalAC = TotalAC + (TotalAC * siWeaponSkillRate / 100);
				}
			}

		}


		//	if ( gamemode == GAMEMODE_SERVER )
		//	{
		/*
		if(bnpc == false && personid)
		{
			SI32 itemtype = 0 ;
			if ( pclitemlist )
				itemtype = pclItemManager->GetItemType(pclitemlist[activeweaponpos].siUnique) ;
			SI32 skilllevel = 0 ;

			switch ( itemtype )
			{
			case ITEMTYPE_SWORD:
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_SWORD_INCDR, 0, 0, pclitemlist);
					if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
					{
						// SJY DEBUG
						SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW1,skilllevel) ;

						DR = DR + DR * rate / 100 ;
					}
				}
				break;
			case ITEMTYPE_SPEAR:
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_SPEAR_INCAC, 0, 0, pclitemlist);
					if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
					{
						// SJY DEBUG
						SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW1,skilllevel) ;
						TotalAC = TotalAC + TotalAC * rate / 100 ;
					}
				}
				break;
		
			case ITEMTYPE_BOW:
				{
					skilllevel = pclskillinfo->GetTotalSkillLevel(SKILL_BOW_INCAR, 0, 0, pclitemlist);
					if ( skilllevel > 0 && skilllevel <= MAX_WEAPONSKILL_LEVEL )
					{
						// SJY DEBUG
						SI32 rate = pclClient->pclSkillManager->GetWeaponSkillRate(MAX_WEAPONSKILL_POW1,skilllevel) ;
						AR = AR + AR * rate / 100 ;
					}
				}
				break;
		
			}
		}
		*/
		//	}

		// �̵��ӵ�, �����Ÿ��� ����Ѵ�.
		{
			if(bnpc == false && personid)
			{
				// ���������� ���� ���ݹ��� ����
				if ( true == bCalcWeaponSkill )
				{
					SI32 siSkillUnique		= 0;
					SI32 siItemType			= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
					switch ( siItemType )
					{
						case ITEMTYPE_SWORD:	{	siSkillUnique = SKILL_SWORD_BOW_INCRANGE;	}	break;
						case ITEMTYPE_SPEAR:	{	siSkillUnique = SKILL_SPEAR_BOW_INCRANGE;	}	break;
						case ITEMTYPE_AXE:		{	siSkillUnique = SKILL_AXE_BOW_INCRANGE;		}	break;
						case ITEMTYPE_BOW:		{	siSkillUnique = SKILL_BOW_INCRANGE;			}	break;
						case ITEMTYPE_GUN:		{	siSkillUnique = SKILL_GUN_BOW_INCRANGE;		}	break;
						case ITEMTYPE_STAFF:	{	siSkillUnique = SKILL_STAFF_BOW_INCRANGE;	}	break;
					}

					if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
					{
						SI32 siSkillLevel		= pclskillinfo->GetTotalSkillLevel( siSkillUnique, 0, 0 );
						SI16 siWeaponSkillRate	= pclClient->pclSkillManager->GetWeaponSkillRate( siSkillUnique, siSkillLevel );
						if ( 0 < siWeaponSkillRate )
						{
							siAttackRange += (siAttackRange * siWeaponSkillRate / 100);
						}
					}
				}

				//KHY - 1220 - ���Žý���.
				if((pclchar) && (pclchar->clTransFormInfo.bTransFormMode == true))
				{
					if(siTransFormSyc >= 100) // ��ũ�� 100% ���ʽ�.
					{
						switch(siAttackType)
						{ 
							case ATTACKTYPE_BOW:
							case ATTACKTYPE_GUN:
								siAttackRange += 1;
								break;
						}
					}
				}
			}
		}
	
		//-------------------------------------------------
		// ����ȿ���� Ŭ���̾�Ʈ���� �뺸�Ѵ�. 
		//-------------------------------------------------
		if(bacswitch || bdamageswitch)
		{
			// Ŭ���̾�Ʈ���� �˸���. 
			if(pclchar)
			{

				cltGameMsgResponse_GeneralEft clinfo(pclchar->GetCharUnique(), siGeneralAC   , siGeneralDamage );
				cltMsg clMsg(GAMEMSG_RESPONSE_GENERALEFT, sizeof(clinfo), (BYTE*)&clinfo);
				((cltCharServer*)pclchar)->SendNeighbourMsg(&clMsg, true);
			}

		}
	} //�ϴ� �� ��Ҵ�.
	return TRUE;
}

// ������ �����Ѵ�.
SI32 cltParametaBox::GetDefensiveRate(cltCharCommon* Enemypclchar,bool MagicFlag)	
{
	SI32 Enemylevel = Enemypclchar->clPB.pclIP->GetLevel();
	SI32 Mylevel = pclIP->GetLevel();

	if( true == MagicFlag )
	{
		//--------------------------------------
		// 106.5  ���� ���� ����� ����.  -%  
		//--------------------------------------
		//siTotalMagicalDefensiveRate = (siMagicalDefensive*10000)/(siMagicalDefensive+200+(Enemylevel*10)) + (Mylevel*10);
		siTotalMagicalDefensiveRate = (((siMagicalDefensive*10000)/(siMagicalDefensive+700))*(10000+((Mylevel-Enemylevel)*200)))/10000;

		siTotalMagicalDefensiveRate = max(1000,siTotalMagicalDefensiveRate);
		siTotalMagicalDefensiveRate = min(9000,siTotalMagicalDefensiveRate);

		return siTotalMagicalDefensiveRate;
	}
	else
	{
		//--------------------------------------
		// 105.5  ���� ���� ����� ����.  -%  
		//--------------------------------------
		//siTotalPHysicalDefensiveRate = (siPHysicalDefensive*10000)/(siPHysicalDefensive+200+(Enemylevel*10)) + (Mylevel*10);
		siTotalPHysicalDefensiveRate = (((siPHysicalDefensive*10000)/(siPHysicalDefensive+700))*(10000+((Mylevel-Enemylevel)*200)))/10000;

		siTotalPHysicalDefensiveRate = max(1000,siTotalPHysicalDefensiveRate);
		siTotalPHysicalDefensiveRate = min(9000,siTotalPHysicalDefensiveRate);

		return siTotalPHysicalDefensiveRate;
	}
	//return 0;
}

// ������ �����Ѵ�.
SI32 cltParametaBox::GetClientDefensiveRate(bool MagicFlag)	
{
	SI32 Mylevel = pclIP->GetLevel();
	SI32 Enemylevel = Mylevel;
	SI32 pDefensive = 0;

	if( true == MagicFlag )
	{
		//--------------------------------------
		// 106.5  ���� ���� ����� ����.  -%  
		//--------------------------------------
		//pDefensive = (siMagicalDefensive*10000)/(siMagicalDefensive+200+(Enemylevel*10)) + (Mylevel*10);
		pDefensive = (((siMagicalDefensive*10000)/(siMagicalDefensive+700))*(10000+((Mylevel-Enemylevel)*200)))/10000;

		pDefensive = max(1000,pDefensive);
		pDefensive = min(9000,pDefensive);

		return pDefensive;
	}
	else
	{
		//--------------------------------------
		// 105.5  ���� ���� ����� ����.  -%  
		//--------------------------------------
		//pDefensive = (siPHysicalDefensive*10000)/(siPHysicalDefensive+200+(Enemylevel*10)) + (Mylevel*10);
		pDefensive = (((siPHysicalDefensive*10000)/(siPHysicalDefensive+700))*(10000+((Mylevel-Enemylevel)*200)))/10000;

		pDefensive = max(1000,pDefensive);
		pDefensive = min(9000,pDefensive);

		return pDefensive;
	}
	//return 0;
}

// ������ DR�� ���� AR�� �ٰŷ� ���߷��� ���Ѵ�.  - ���� ��Ʈ ��� Ȯ���� ���ϴ� ���̴�.
SI32 cltParametaBox::GetHitRate(cltCharCommon* Enemypclchar, cltCharCommon* pclAttackChar, bool MagicFlag )			
{
	SI16 enemydr = Enemypclchar->clPB.GetDR();

	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		SI32 Enemylevel = Enemypclchar->clPB.pclIP->GetLevel();
		SI32 Mylevel = pclIP->GetLevel();
		SI32 toTalHitRate = 0;

		if( true == MagicFlag )
		{
			//--------------------------------------
			// 104.4 ���� ���� �������� ����. 
			//--------------------------------------
			siMagicalHitRateLevel = (Mylevel - Enemylevel) * 50;

			//--------------------------------------
			// 104.5 ���� ���߷� ����. 
			//--------------------------------------
			toTalHitRate = min(10000, ((7000+(siMagicalHitRateRank*6)) * (10000 +siMagicalHitRateLevel))/10000);

			if(toTalHitRate >0)
				siTotalMagicalHitRate = toTalHitRate; //ũ����Ż�� ���� ���߷� ��� ��ġ�� ���Ѵ�.

			if( Enemypclchar )
			{
				if( Enemypclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_DODGE, Enemypclchar->GetID() ) )
				{
					siTotalMagicalHitRate -= (siTotalMagicalHitRate * Enemypclchar->m_clCharCurseEffect.GetPara()) / 100; 
				}
			}

			return siTotalMagicalHitRate;
		}
		else
		{
			//--------------------------------------
			// 103.4 ���� ���� �������� ����. 
			//--------------------------------------
			siPHysicalHitRateLevel = (Mylevel - Enemylevel) * 50;


			//--------------------------------------
			// 103.5 ���� ���߷� ����. 
			//--------------------------------------
			toTalHitRate = min(10000, ((7000+(siPHysicalHitRateRank*6)) * (10000 +siPHysicalHitRateLevel))/10000);

			if(toTalHitRate>0)
				siTotalPHysicalHitRate = toTalHitRate; //ũ����Ż�� ���� ���߷� ��� ��ġ�� ���Ѵ�.

			if( Enemypclchar )
			{
				if( Enemypclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_DODGE, Enemypclchar->GetID() ) )
				{
					siTotalPHysicalHitRate -= (siTotalPHysicalHitRate * Enemypclchar->m_clCharCurseEffect.GetPara()) / 100; 
				}
			}

			return siTotalPHysicalHitRate;

			//siTotalPHysicalHitRate = toTalHitRate + (toTalHitRate * siEquipPHysicalHitRate /100); //ũ����Ż�� ���� ���߷� ��� ��ġ�� ���Ѵ�.
		}
	}
	else
	{
		HitRate = 0;
		if( true == MagicFlag )
		{
			HitRate	= (AR * 120) / (AR + enemydr) + (siEquipAssistHitRate/10) + 30;	// ��� ���� ���߷� ��� ��ġ�� ���Ѵ�. ������ �� �� �����ش�.
		}
		else
		{
			HitRate	= (AR * 120) / (AR + enemydr) + (siEquipAssistHitRate/10);	// ��� ���� ���߷� ��� ��ġ�� ���Ѵ�. 

			// ���߷��� 60% �̸��̸�, ����Ʈ ���߷��� �����ش�. 
			if(HitRate < 60)
			{
				HitRate = min(60, HitRate + siWeaponDefaultHitRate);
			}
		}

		HitRate = min(100, HitRate);

		return HitRate;
	}
	//return 0;
}

// ������ DR�� ���� AR�� �ٰŷ� ���߷��� ���Ѵ�.  - ���� ��Ʈ ��� Ȯ���� ���ϴ� ���̴�.
SI32 cltParametaBox::GetClientHitRate(bool MagicFlag)			
{
	SI32 Mylevel = pclIP->GetLevel();

	//���� ���� �����ʹ� '��'�� ���ٰ� �����Ѵ�.
	SI32 Enemylevel = Mylevel;   

	SI32 toTalHitRate = 0;

	if( true == MagicFlag )
	{
		//--------------------------------------
		// 104.4 ���� ���� �������� ����. 
		//--------------------------------------
		siMagicalHitRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 104.5 ���� ���߷� ����. 
		//--------------------------------------
		toTalHitRate = min(10000, ((7500+(siMagicalHitRateRank*6)) * (10000 +siMagicalHitRateLevel))/10000);

		if(toTalHitRate >0)
			siTotalMagicalHitRate = toTalHitRate; //ũ����Ż�� ���� ���߷� ��� ��ġ�� ���Ѵ�.

		return siTotalMagicalHitRate;
	}
	else
	{
		//--------------------------------------
		// 103.4 ���� ���� �������� ����. 
		//--------------------------------------
		siPHysicalHitRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 103.5 ���� ���߷� ����. 
		//--------------------------------------
		toTalHitRate = min(10000, ((7000+(siPHysicalHitRateRank*6)) * (10000 +siPHysicalHitRateLevel))/10000);

		if(toTalHitRate>0)
			siTotalPHysicalHitRate = toTalHitRate; //ũ����Ż�� ���� ���߷� ��� ��ġ�� ���Ѵ�.

		return siTotalPHysicalHitRate;
	}

	//return 0;
}

// ȸ������ ���Ѵ�.
SI32 cltParametaBox::GetDodgeRate(cltCharCommon* Enemypclchar, cltCharCommon* pclAttackChar, bool MagicFlag)			
{
	SI32 Enemylevel = Enemypclchar->clPB.pclIP->GetLevel();
	SI32 Mylevel = pclIP->GetLevel();
	SI32 toTalDodgeRate = 0;

	if( true == MagicFlag )
	{
		//--------------------------------------
		// 108.4 ���� ȸ�� �������� ����. 
		//--------------------------------------
		siMagicalDodgeRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 108.5 ���� ȸ�Ƿ� ����. 
		//--------------------------------------
		toTalDodgeRate = min(5000, (siMagicalDodgeRateRank*7*(10000+siMagicalDodgeRateLevel))/10000);

		if(toTalDodgeRate >0)
			siTotalMagicalDodgeRate = toTalDodgeRate; 

		if( Enemypclchar )
		{
			if( Enemypclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_HIT, Enemypclchar->GetID() ) )
			{
				siTotalMagicalDodgeRate += (siTotalMagicalDodgeRate * Enemypclchar->m_clCharCurseEffect.GetPara()) / 100; 
			}
		}

		return siTotalMagicalDodgeRate;
	}
	else
	{
		//--------------------------------------
		// 107.4 ���� ȸ�� �������� ����. 
		//--------------------------------------	
		siPHysicalDodgeRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 107.5 ���� ȸ�Ƿ� ����. 
		//--------------------------------------
		toTalDodgeRate = min(5000, (siPHysicalDodgeRateRank*6*(10000+siPHysicalDodgeRateLevel))/10000);

		if(toTalDodgeRate >0)
			siTotalPHysicalDodgeRate = toTalDodgeRate; 

		if( Enemypclchar )
		{
			if( Enemypclchar->m_clCharCurseEffect.IsCurse( cltCharCurseEffect::CURSE_HIT, Enemypclchar->GetID() ) )
			{
				siTotalPHysicalDodgeRate += (siTotalPHysicalDodgeRate * Enemypclchar->m_clCharCurseEffect.GetPara()) / 100; 
			}
		}

		return siTotalPHysicalDodgeRate;
	}

//	return 0 ;
}

// ȸ������ ���Ѵ�.
SI32 cltParametaBox::GetClientDodgeRate(bool MagicFlag)			
{
	SI32 Mylevel = pclIP->GetLevel();
	SI32 Enemylevel = Mylevel;

	SI32 toTalDodgeRate = 0;

	if( true == MagicFlag )
	{
		//--------------------------------------
		// 108.4 ���� ȸ�� �������� ����. 
		//--------------------------------------
		siMagicalDodgeRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 108.5 ���� ȸ�Ƿ� ����. 
		//--------------------------------------
		toTalDodgeRate = min(5000, (siMagicalDodgeRateRank*7*(10000+siMagicalDodgeRateLevel))/10000);

		if(siEquipMagicalDodgeRate >0)
			toTalDodgeRate = toTalDodgeRate ; 

		return toTalDodgeRate;
	}
	else
	{
		//--------------------------------------
		// 107.4 ���� ȸ�� �������� ����. 
		//--------------------------------------	
		siPHysicalDodgeRateLevel = (Mylevel - Enemylevel) * 50;

		//--------------------------------------
		// 107.5 ���� ȸ�Ƿ� ����. 
		//--------------------------------------
		toTalDodgeRate = min(5000, (siPHysicalDodgeRateRank*6*(10000+siPHysicalDodgeRateLevel))/10000);

		if(siEquipPHysicalDodgeRate >0)
			toTalDodgeRate = toTalDodgeRate; 

		return toTalDodgeRate;
	}

//	return 0 ;
}


//------------------------
// ü��
//------------------------
SI32 cltParametaBox::GetMaxLife()
{
	SI32 life = 0;
	
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		life = GetTotalHitpoint();
	}
	else
	{
		life = MaxLife;
	}

	return life;
}

//------------------------
// ����
//------------------------
SI32 cltParametaBox::GetMaxMana()
{
	SI32 mana = 0;
	
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		mana = GetTotalManapoint();
	}
	else
	{
		mana = MaxMana;
	}

	return mana;
}

//------------------------
// ���� 
//------------------------
SI32 cltParametaBox::GetMaxWeight()
{
	SI32 weight = 0;
	
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{
		weight = GetTotalWeight();
	}
	else
	{
		weight = pclIP->GetLevel() * 1000;
	}

	return weight;
}



// ������ ���� ���� ��� ȿ���� ���Ѵ�. 
SI32 cltParametaBox::CalcLevelAC(SI32 level)
{
	SI32 ac = 0;

	if(level > 90)	{	ac += ((level - 90) / 1);		level = 90;		}
	if(level > 70)	{	ac += ((level - 70) / 2);		level = 70;		}
	if(level > 60)	{	ac += ((level - 60) / 3);		level = 60;		}
	if(level > 50)	{	ac += ((level - 50) / 4);		level = 50;		}
	if(level > 40)	{	ac += ((level - 40) / 5);		level = 40;		}
	ac	+= (level / 10);
	ac /= 2;

	return ac;
}


//----------------------------------------------------------
// �ɷ�ġ ��� �Լ�
//----------------------------------------------------------
void cltParametaBox::SetEquipBasicAbility(cltCharCommon* pclchar, cltItem* pclitemlist, SI32 activeweaponpos)
{
	clEquipBA.Init();

	if(pclitemlist == NULL)			return;

	if(pclClient->IsCountrySwitch(Switch_StatusBug))
	{
		SI32 siStr = pclItemManager->GetEquipStr(pclitemlist, activeweaponpos);
		SI32 siDex = pclItemManager->GetEquipDex(pclitemlist, activeweaponpos);
		SI32 siVit = pclItemManager->GetEquipVit(pclitemlist, activeweaponpos);
		SI32 siMag = pclItemManager->GetEquipMag(pclitemlist, activeweaponpos);
		SI32 siLuk = pclItemManager->GetEquipLuk(pclitemlist, activeweaponpos);
		SI32 siHnd = pclItemManager->GetEquipHnd(pclitemlist, activeweaponpos);	
		//SI32 siWis = pclItemManager->GetEquipWis(pclitemlist, activeweaponpos);

		clEquipBA.SetStr(siStr);
		clEquipBA.SetDex(siDex);
		clEquipBA.SetVit(siVit);
		clEquipBA.SetMag(siMag);
		clEquipBA.SetLuk(siLuk);
		clEquipBA.SetHnd(siHnd);
	}
	else
	{
		SI32 siStr = pclItemManager->GetEquipStr(pclitemlist, activeweaponpos, pclchar);
		SI32 siDex = pclItemManager->GetEquipDex(pclitemlist, activeweaponpos, pclchar);
		SI32 siVit = pclItemManager->GetEquipVit(pclitemlist, activeweaponpos, pclchar);
		SI32 siMag = pclItemManager->GetEquipMag(pclitemlist, activeweaponpos, pclchar);
		SI32 siLuk = pclItemManager->GetEquipLuk(pclitemlist, activeweaponpos, pclchar);
		SI32 siHnd = pclItemManager->GetEquipHnd(pclitemlist, activeweaponpos, pclchar);	
		SI32 siWis = pclItemManager->GetEquipWis(pclitemlist, activeweaponpos, pclchar);

		clEquipBA.SetStr(siStr);
		clEquipBA.SetDex(siDex);
		clEquipBA.SetVit(siVit);
		clEquipBA.SetMag(siMag);
		clEquipBA.SetLuk(siLuk);
		clEquipBA.SetHnd(siHnd);
		clEquipBA.SetWis(siWis);
	}
}

void cltParametaBox::SetTransformBasicAbility(cltCharCommon* pclchar, cltItem* pclitemlist, SI32 activeweaponpos)
{
	if(pclchar == NULL)				return;

	cltKindInfo* pclki = pclClient->pclKindInfoSet->pclKI[pclchar->clTransFormInfo.uiNowTransFormKind];
	if(pclki == NULL)			return;

	SI32 itemtype = 0 ;
	if ( pclitemlist )	itemtype = pclItemManager->GetItemType(pclitemlist[activeweaponpos].siUnique) ;

	clTransFormBA.Init();
	if(pclchar->clTransFormInfo.bTransFormMode == true)
	{
		// �ش� ���� ĳ������ �⺻ �ɷ� ����.
		clTransFormBA.Set(&pclki->clBA);

		//��ũ������ ���� �߰� ȿ���� ���Ѵ�.
		SI32 temState = 0;
		siTransFormSyc = (SI32)pclchar->clTransFormInfo.GetSynchroTransForm(pclchar->clTransFormInfo.uiNowTransFormKind);

		// ��ø ����.
		temState = clTransFormBA.GetDex() * (siTransFormSyc/2) / 100;
		clTransFormBA.IncreaseDex(temState);

		// �� ����.
		temState = clTransFormBA.GetStr() * (siTransFormSyc/2) / 100;
		clTransFormBA.IncreaseStr(temState);

		// ü�� ����.
		temState = clTransFormBA.GetVit() * (siTransFormSyc/2) / 100;
		clTransFormBA.IncreaseVit(temState);

		// ���� ����.
		temState = clTransFormBA.GetWis() * (siTransFormSyc/2) / 100;
		clTransFormBA.IncreaseWis(temState);

		// ���� ����.
		temState = clTransFormBA.GetMag() * (siTransFormSyc/2) / 100;

		// ������  = ���� ��ũ�� %�� �� ������. 
		if(itemtype == ITEMTYPE_STAFF)
			temState += (SI32)(siTransFormSyc/5);

		clTransFormBA.IncreaseMag(temState);

		//KHY - 0124 - ��í����- ���� ���� ������.
		if((pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAMAN"))			||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAGIRL"))			||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATMELEE"))			||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATRANGE"))			||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN"))	||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST"))	||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE"))	||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE"))	||
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE"))	||	// �˻罺�Ǹ�(��)
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE"))  ||	// �ųʽ��Ǹ�(��)
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYMELEE"))		||	// �������Ǹ���)
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYRANGE"))		||	// �������Ǹ�(��)
			// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICERANGE"))			||	// ���� ����
			(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICEMELEE"))				// �罺��ġ
		   )		
		{
			// ���� ����.
			siTransFormAC = 80; // �⺻ ����.
			temState = siTransFormAC * (siTransFormSyc/2) / 100;

			siTransFormAC = siTransFormAC + temState; // ��ũ���� ������.				
		}

		if(siTransFormSyc >= 100) // ��ũ���� 100% ���ʽ�. - 10 ����.
		{
			if( (pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAMAN"))  		||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_NINJAGIRL")) 		||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATMELEE"))  		||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CATRANGE"))			||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENPUMPKIN"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_HALLOWEENGHOST"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASMELEE"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_CHRISTMASRANGE"))	||
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENMELEE"))	||	// �˻罺�Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FIGHTINGMENRANGE"))	||  // �ųʽ��Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYMELEE"))		||	// �������Ǹ�(��)
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_FAIRYRANGE"))		||	// �������Ǹ�(��)
				// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICERANGE"))			||	// ���� ����
				(pclchar->clTransFormInfo.uiNowTransFormKind == pclClient->GetUniqueFromHash("KIND_ICEMELEE"))				// �罺��ġ
			  )		
			{
				clTransFormBA.IncreaseHnd(15);
				clTransFormBA.IncreaseLuk(15);
			}
			else
			{
				clTransFormBA.IncreaseHnd(10);
				clTransFormBA.IncreaseLuk(10);
			}
		}
	}
}

void cltParametaBox::SetHorseBasicAbility(cltPersonHorseInfo* pclhorseinfo, cltCharCommon* pclchar)
{
	clHorseBA.Init();

	if(pclhorseinfo == NULL)							return;
	if(pclhorseinfo->siCurrentHorseRIDEHORSE == false)	return;

	cltHorse* pclhorse = pclhorseinfo->GetCurrentShowHorse();

	if(pclhorse)
	{
		clHorseBA.siStr	= pclhorse->siStr / 100;
		clHorseBA.siDex	= pclhorse->siDex / 100;
		clHorseBA.siMag	= pclhorse->siMag / 100;

		SI32 horsedate = pclClient->pclHorseManager->GetAddStatusLimitDateVary(pclhorse) ;
		SI32 Premiumhorsedate_Slot1 = pclClient->pclHorseManager->GetPremiumPArtsDateVary_Slot1(pclhorse) ;
		SI32 Premiumhorsedate_Slot2 = pclClient->pclHorseManager->GetPremiumPArtsDateVary_Slot2(pclhorse) ;
		SI32 Premiumhorsedate_Slot3 = pclClient->pclHorseManager->GetPremiumPArtsDateVary_Slot3(pclhorse) ;
		SI32 siEquipPremiumPartsNum	=	 pclhorse->GetPremiumPartsNum();
		if ( pclClient->GameMode == GAMEMODE_SERVER )
		{
			if ( pclhorse->siStatusTicketNum > 0 && horsedate > 0 && 
				((cltServer*)pclClient)->pclTime->clDate.GetDateVary() < horsedate )
			{
				clHorseBA.siStr	+= MAX_HORSE_ADDSTATUS ;
				clHorseBA.siDex	+= MAX_HORSE_ADDSTATUS ;
				clHorseBA.siMag	+= MAX_HORSE_ADDSTATUS ;				
			}
			// �����̾� �������� ���� �߰� �ɷ�ġ			
			// ���� 1 
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot1 > 0 &&
				((cltServer*)pclClient)->pclTime->clDate.GetDateVary() < Premiumhorsedate_Slot1)
			{
				SI32 siPremiumUnique	= pclhorse->GetPremiumUnique_Slot1();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}				
			}
			// ���� 2
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot2 > 0 &&
				((cltServer*)pclClient)->pclTime->clDate.GetDateVary() < Premiumhorsedate_Slot2)
			{
				SI32 siPremiumUnique = pclhorse->GetPremiumUnique_Slot2();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}
			}
			// ���� 3 
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot3 > 0 &&
				((cltServer*)pclClient)->pclTime->clDate.GetDateVary() < Premiumhorsedate_Slot3)
			{
				SI32 siPremiumUnique	= pclhorse->GetPremiumUnique_Slot3();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}
			}

			// [���] ũ�������� �̺�Ʈ - ũ�������� ��� ������ ������ Ż���� �ɷ�ġ + 5�� ���ش�.
			if(pclchar && IsPC( pclchar->GetCharUnique() ))
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );

				if(clBuf.IsHaveBuf(BUF_CHRISTMASEVENT_DECORATION))
				{
					clHorseBA.siStr += 5;
					clHorseBA.siDex += 5;
					clHorseBA.siVit += 5;
					clHorseBA.siWis += 5;
					clHorseBA.siMag += 5;
					clHorseBA.siLuk += 5;
					clHorseBA.siHnd += 5;
				}
			}
		}
		else if (pclClient->GameMode == GAMEMODE_CLIENT )
		{
			if ( pclhorse->siStatusTicketNum > 0 && horsedate > 0 && 
				((cltClient*)pclClient)->clClientDate.GetDateVary() < horsedate )
			{
				clHorseBA.siStr	+= MAX_HORSE_ADDSTATUS ;
				clHorseBA.siDex	+= MAX_HORSE_ADDSTATUS ;
				clHorseBA.siMag	+= MAX_HORSE_ADDSTATUS ;
			}
			// �����̾� �������� ���� �߰� �ɷ�ġ
			// ���� 1 
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot1 > 0 )
			{
				SI32 siPremiumUnique = pclhorse->GetPremiumUnique_Slot1();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}				
			}
			// ���� 2
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot2 > 0 )
			{
				SI32 siPremiumUnique = pclhorse->GetPremiumUnique_Slot2();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}				
			}
			// ���� 3 
			if ( siEquipPremiumPartsNum > 0 &&  Premiumhorsedate_Slot3 > 0 )
			{
				SI32 siPremiumUnique = pclhorse->GetPremiumUnique_Slot3();
				if ( siPremiumUnique > 0)
				{
					// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
					SetPremiumPartsstatusUp( siPremiumUnique );
				}				
			}

			// [���] ũ�������� �̺�Ʈ - ũ�������� ��� ������ ������ Ż���� �ɷ�ġ + 5�� ���ش�.
			if(pclchar && IsPC( pclchar->GetCharUnique() ))
			{
				cltBufInfo clBuf;
				clBuf.SetBuf( &pclchar->pclCI->clBI.clBufInfo );

				if(clBuf.IsHaveBuf(BUF_CHRISTMASEVENT_DECORATION))
				{
					clHorseBA.siStr += 5;
					clHorseBA.siDex += 5;
					clHorseBA.siVit += 5;
					clHorseBA.siWis += 5;
					clHorseBA.siMag += 5;
					clHorseBA.siLuk += 5;
					clHorseBA.siHnd += 5;
				}
			}
		}
	}
}
void cltParametaBox::SetPremiumPartsstatusUp( SI32 PremiumItemUnique )
{	// �޸���ŭ ���� ���� �ɷ�ġ�� ���� �Ѵ�.
	switch ( PremiumItemUnique )
	{
	case ITEMUNIQUE(13635):	// ������Ʈ
		{
			clHorseBA.siDex	+= 30 ;
		}
		break;
	case ITEMUNIQUE(13636):	// �Ҳ���
		{
			clHorseBA.siStr	+= 30 ;	// �ٷ� 10
		}
		break;
	case ITEMUNIQUE(13637):	// LED���׳�
		{
			clHorseBA.siMag	+= 30 ;;	// ���� 25
		}
		break;
	case ITEMUNIQUE(13638):	// ��ȭ ����
		{
			clHorseBA.siDex	+= 30 ;	// ���߷� 10
		}
		break;
	case ITEMUNIQUE(13639):	// ��ȭ ���
		{
			clHorseBA.siStr	+= 30;	// �ٷ� 5
		}
		break;
	case ITEMUNIQUE(13640):	// ��ȭ ���
		{
			clHorseBA.siMag	+= 30;	// ���� 15
		}
		break;
	}
}
void cltParametaBox::SetGuildBasicAbility(cltCharCommon* pclchar)
{
	if(pclchar == NULL)			return;

	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		clGuildBA.Init();

		if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() )
		{
			if ( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == false ) return; // ��� �ɹ��� �ƴϸ� �������ͽ� ����� ��Ű�� �ʴ´�.
			if ( pclchar->pclCI->clBI.clGuildRank.GetRankType() == GUILDRANKTYPE_STANDING ) return; // ��� �ɹ��� �ƴϸ� �������ͽ� ����� ��Ű�� �ʴ´�.
			
			cltGuildInfo* pclGuild = pclClient->pclGuildManager->GetGuildInfo(pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex);
			if ( pclGuild != NULL )
			{
				clGuildBA.siStr = pclGuild->clStatus.siStr ;
				clGuildBA.siDex = pclGuild->clStatus.siDex ;
				clGuildBA.siMag = pclGuild->clStatus.siMag ;
				clGuildBA.siVit = pclGuild->clStatus.siVit ;
				clGuildBA.siHnd = pclGuild->clStatus.siHnd ;
				clGuildBA.siLuk = pclGuild->clStatus.siLuk ;
				clGuildBA.siWis= pclGuild->clStatus.siWis;
			}
		}
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		/*	
		if( pclchar->pclCI->clBI.clGuildRank.IsGuildMember() )
		{

			clGuildBA.siStr = siGuildStr;
			clGuildBA.siDex = siGuildDex;
			clGuildBA.siMag = siGuildMag;
			clGuildBA.siVit = siGuildVit;
			clGuildBA.siHnd = siGuildHnd;
			clGuildBA.siLuk = siGuildLuck;
			clGuildBA.siWis= siGuildWis;
		}
		*/

	}
}

void cltParametaBox::SetHealthAddAbility(cltHealthInfo*	pclhealthinfo, cltBasicAbility BasicBA)
{
	siHealthStrRate = 0;
	siHealthDexRate = 0;
	siHealthMagRate = 0;

	siHealthHndRate = 0;
	siHealthLukRate = 0;
	siHealthWisRate = 0;


	clHealthAdd.Init();

	if(pclhealthinfo == NULL)			return;
	
	siHealthStrRate	= pclhealthinfo->uiHealthPoint - 100;
	siHealthDexRate	= pclhealthinfo->uiHealthPoint - 100;
	siHealthMagRate	= pclhealthinfo->uiHealthPoint - 100;

	siHealthHndRate	= pclhealthinfo->uiHealthPoint - 100;
	siHealthLukRate	= pclhealthinfo->uiHealthPoint - 100;
	siHealthWisRate	= pclhealthinfo->uiHealthPoint - 100;


	clHealthAdd.SetStr( (BasicBA.GetStr() * siHealthStrRate) / 100 );
	clHealthAdd.SetDex( (BasicBA.GetDex() * siHealthDexRate) / 100 );
	clHealthAdd.SetMag( (BasicBA.GetMag() * siHealthMagRate) / 100 );

	clHealthAdd.SetHnd( (BasicBA.GetHnd() * siHealthHndRate) / 100 );
	clHealthAdd.SetLuk( (BasicBA.GetLuk() * siHealthLukRate) / 100 );
	clHealthAdd.SetWis( (BasicBA.GetWis() * siHealthWisRate) / 100 );

}

void cltParametaBox::SetElixirAddAbility( cltCharCommon* pclchar )
{
	if( false == pclClient->IsCountrySwitch( Switch_Elixir) ) return;
	
	if( pclchar && IsPC( pclchar->GetCharUnique() ) )
	{
		// [����] ������ 
		clElixirAdd.Init();

		if( pclchar->pcltElixir )
		{
			clElixirAdd.SetStr( pclchar->pcltElixir->GetStr() );
			clElixirAdd.SetDex( pclchar->pcltElixir->GetDex() );
			clElixirAdd.SetMag( pclchar->pcltElixir->GetMag() );
			clElixirAdd.SetVit( pclchar->pcltElixir->GetVit() );
			clElixirAdd.SetHnd( pclchar->pcltElixir->GetHnd() );
			clElixirAdd.SetWis( pclchar->pcltElixir->GetWis() );
		}
	}
}

void cltParametaBox::SetSetItemAddAbility(cltCharCommon* pclchar, cltItem* pclitemlist)
{
	clSetItemAdd.Init();

	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if( pclchar && IsPC( pclchar->GetCharUnique() ) )
		{
			if( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{			
				//-----------------------------------------------------------------------------
				SI16	 oldSetItemType =  pclchar->m_siSetItemType; // �ٲ������ ���ϱ� ����.
				SI16	 oldSetItemType2 =  pclchar->m_siSetItemType2; // �ٲ������ ���ϱ� ����.
				SI16	 oldSetItemType3 =  pclchar->m_siSetItemType3; // �ٲ������ ���ϱ� ����.
				SI16	 oldSetItemType4 =  pclchar->m_siSetItemType4; // �ٲ������ ���ϱ� ����.
				SI16	 oldSetItemType5 =  pclchar->m_siSetItemType5; // �ٲ������ ���ϱ� ����.

				cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;
				
				SI16 setItemType  = 0;
				SI16 setItemStep  = 0;
				SI16 setItemType2 = 0;
				SI16 setItemStep2 = 0;
				SI16 setItemType3 = 0;
				SI16 setItemStep3 = 0;
				SI16 setItemType4 = 0;
				SI16 setItemStep4 = 0;
				SI16 setItemType5 = 0;
				SI16 setItemStep5 = 0;

				setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep, USE_SETITEM_1 );
				setItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep2, USE_SETITEM_2 );
				setItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep3, USE_SETITEM_3 );
				setItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep4, USE_SETITEM_4 );
				setItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep5, USE_SETITEM_5 );

				pclchar->m_siSetItemType = setItemType;
				pclchar->m_siSetItemStep = setItemStep;

				pclchar->m_siSetItemType2 = setItemType2;
				pclchar->m_siSetItemStep2 = setItemStep2;

				pclchar->m_siSetItemType3 = setItemType3;
				pclchar->m_siSetItemStep3 = setItemStep3;

				pclchar->m_siSetItemType4 = setItemType4;
				pclchar->m_siSetItemStep4 = setItemStep4;

				pclchar->m_siSetItemType5 = setItemType5;
				pclchar->m_siSetItemStep5 = setItemStep5;

				if(	(oldSetItemType  != pclchar->m_siSetItemType)	|| 
					(oldSetItemType2 != pclchar->m_siSetItemType2)	|| 
					(oldSetItemType3 != pclchar->m_siSetItemType3)	|| 
					(oldSetItemType4 != pclchar->m_siSetItemType4)	|| 
					(oldSetItemType5 != pclchar->m_siSetItemType5))
				{
					cltGameMsgResponse_SetItemTypeInfo clinfo3( setItemType, setItemStep, setItemType2, setItemStep2, setItemType3, setItemStep3, setItemType4, setItemStep4, setItemType5, setItemStep5);
					cltMsg clMsg3(GAMEMSG_RESPONSE_SETITEMTYPEINFO, sizeof(clinfo3), (BYTE*)&clinfo3);
					//pclchar->SendNetMsg((sPacketHeader*)&clMsg3);
					((cltCharServer*)pclchar)->SendNeighbourMsg(&clMsg3, true);
				}
				//-----------------------------------------------------------------------------

				if( pclchar->m_siSetItemType )
				{
					cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
					if( pcltSetItemAbilityManager )
					{
						clSetItemAdd.SetStr( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_5)  );
						clSetItemAdd.SetDex( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_5)  );
						clSetItemAdd.SetMag( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_5)  );
						clSetItemAdd.SetVit( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_5)  );
						clSetItemAdd.SetHnd( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_1) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_5) );
						clSetItemAdd.SetLuk( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_5)  );
						clSetItemAdd.SetWis( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_2)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_3)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_4)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_5)  );
					}
				}
			}
			else
			{
				if( pclchar && pclchar->m_siSetItemType == VAMPIRE_SETITEM )
				{
					clSetItemAdd.SetStr( 10 );
					clSetItemAdd.SetDex( 10 );
					clSetItemAdd.SetMag( 10 );
					clSetItemAdd.SetVit( 10 );
				}
			}
		}
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if( pclchar && (IsPC( pclchar->GetID() ) == 1))
		{
			if( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
			{
				//-----------------------------------------------------------------------------
				cltItemManagerClient* pclitemmanager = (cltItemManagerClient*)pclClient->pclItemManager;

				SI16 setItemType  = 0;
				SI16 setItemStep  = 0;
				SI16 setItemType2 = 0;
				SI16 setItemStep2 = 0;
				SI16 setItemType3 = 0;
				SI16 setItemStep3 = 0;
				SI16 setItemType4 = 0;
				SI16 setItemStep4 = 0;
				SI16 setItemType5 = 0;
				SI16 setItemStep5 = 0;

				setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep, USE_SETITEM_1 );
				setItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep2, USE_SETITEM_2 );
				setItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep3, USE_SETITEM_3 );
				setItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep4, USE_SETITEM_4 );
				setItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep5, USE_SETITEM_5 );

				pclchar->m_siSetItemType = setItemType;
				pclchar->m_siSetItemStep = setItemStep;

				pclchar->m_siSetItemType2 = setItemType2;
				pclchar->m_siSetItemStep2 = setItemStep2;

				pclchar->m_siSetItemType3 = setItemType3;
				pclchar->m_siSetItemStep3 = setItemStep3;

				pclchar->m_siSetItemType4 = setItemType4;
				pclchar->m_siSetItemStep4 = setItemStep4;

				pclchar->m_siSetItemType5 = setItemType5;
				pclchar->m_siSetItemStep5 = setItemStep5;
				//-----------------------------------------------------------------------------

				if( pclchar->m_siSetItemType )
				{
					cltSetItemAbilityManager* pcltSetItemAbilityManager = pclClient->pclItemManager->pcltSetItemAbilityManager;
					if( pcltSetItemAbilityManager )
					{
						clSetItemAdd.SetStr( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_STR, USE_SETITEM_5) );
						clSetItemAdd.SetDex( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_DEX, USE_SETITEM_5) );
						clSetItemAdd.SetMag( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_MAG, USE_SETITEM_5) );
						clSetItemAdd.SetVit( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_VIT, USE_SETITEM_5) );
						clSetItemAdd.SetHnd( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_1)  + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_2)+ pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_3)+ pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_4)+ pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_HAND, USE_SETITEM_5));
						clSetItemAdd.SetLuk( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_LUK, USE_SETITEM_5) );
						clSetItemAdd.SetWis( pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_1)   + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_2) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_3) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_4) + pcltSetItemAbilityManager->GetSetItemAbilityValue(pclchar, SETITEM_ABILITY_TYPE_WIS, USE_SETITEM_5) );
					}
				}
			}
			else
			{
				if( pclchar && pclchar->m_siSetItemType == VAMPIRE_SETITEM )
				{
					clSetItemAdd.SetStr( 10 );
					clSetItemAdd.SetDex( 10 );
					clSetItemAdd.SetMag( 10 );
					clSetItemAdd.SetVit( 10 );
				}
			}
		}
	}
}

void cltParametaBox::SetSkillAddAbility(cltItem* pclitemlist, SI32 activeweaponpos, cltPSkillInfo* pclskillinfo, cltBasicAbility BasicBA)
{
	// ������� ���ο� ���� �������
	clSkillAdd.Init();

	if ( NULL == pclitemlist )																	return;
	if ( !(PERSONITEM_WEAPON1 == activeweaponpos) && !(PERSONITEM_WEAPON2 == activeweaponpos) )	return;
	if ( NULL == pclskillinfo )																	return;

	cltWeaponSkillMasterManager* pclGetMasterMgr = &pclClient->pclSkillManager->m_clMasterManager;
	if ( NULL == pclGetMasterMgr )																return;

	SI32 siStrRate		= 0;
	SI32 siHndRate		= 0;
	SI32 siDexRate		= 0;
	SI32 siMagRate		= 0;
	SI32 siWisRate		= 0;
	SI32 siVitRate		= 0;
	SI32 siLukRate		= 0;

	SI32 siItemType		= pclItemManager->GetItemType( pclitemlist[activeweaponpos].siUnique );
	SI32 siSkillUnique	= pclGetMasterMgr->GetSkillUseWeaponFromItemType( siItemType ) ;
	SI32 siSkillLevel	= 0;

	if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
	{
		siSkillLevel	= pclskillinfo->GetSkillExpLevel( siSkillUnique );

		siStrRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_STR );
		siHndRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_HAND );
		siDexRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_DEX );
		siMagRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_MAG );
		siWisRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_WIS );
		siVitRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_VIT );
		siLukRate		= pclGetMasterMgr->GetApplyValue( siItemType, siSkillLevel, SKILLMASTER_LUCK );

		if ( siStrRate )	clSkillAdd.SetStr( (BasicBA.GetStr()*siStrRate/100) );
		if ( siHndRate )	clSkillAdd.SetHnd( (BasicBA.GetHnd()*siHndRate/100) );
		if ( siDexRate )	clSkillAdd.SetDex( (BasicBA.GetDex()*siDexRate/100) );
		if ( siMagRate )	clSkillAdd.SetMag( (BasicBA.GetMag()*siMagRate/100) );
		if ( siWisRate )	clSkillAdd.SetWis( (BasicBA.GetWis()*siWisRate/100) );
		if ( siVitRate )	clSkillAdd.SetVit( (BasicBA.GetVit()*siVitRate/100) );
		if ( siLukRate )	clSkillAdd.SetLuk( (BasicBA.GetLuk()*siLukRate/100) );
	}

}

void cltParametaBox::SetSoulGuardAddAbility(cltCharCommon* pclchar )
{
	clSoulGuardAdd.Init();

	if ( false == pclClient->IsCountrySwitch(Switch_SoulGuard) )
	{
		return;
	}

	if (NULL == pclchar)
	{
		return;
	}

	if (GAMEMODE_SERVER == pclClient->GameMode)  
	{
		if ( false == IsPC(pclchar->GetCharUnique()) )	return;
	}
	else if ( GAMEMODE_CLIENT == pclClient->GameMode )
	{
		if ( pclchar->GetID() != 1 )					return;
	}

	if ( FALSE == pclchar->IsSoulGuardStatusOut() )
	{
		return;
	}

	SI16 siGetFellowShip = pclchar->pclSoulGuard->GetFellowShip();
	if ( 0 >= siGetFellowShip )
	{
		return;
	}

	SI16 siSoulGuardKind = pclchar->pclSoulGuard->GetKind();
	if ( (0 >= siSoulGuardKind) || (MAX_KIND_NUMBER <= siSoulGuardKind) )	
	{
		return;
	}

	cltKindInfo* pclGetKI = pclClient->pclKindInfoSet->pclKI[siSoulGuardKind];
	if ( NULL == pclGetKI )
	{
		return;
	}
		
	SI32 siStrAdd = (pclGetKI->clBA.GetStr() * siGetFellowShip) / 100;
	SI32 siHndAdd = (pclGetKI->clBA.GetHnd() * siGetFellowShip) / 100;
	SI32 siDexAdd = (pclGetKI->clBA.GetDex() * siGetFellowShip) / 100;
	SI32 siMagAdd = (pclGetKI->clBA.GetMag() * siGetFellowShip) / 100;
	SI32 siWisAdd = (pclGetKI->clBA.GetWis() * siGetFellowShip) / 100;
	SI32 siVitAdd = (pclGetKI->clBA.GetVit() * siGetFellowShip) / 100;
	SI32 siLukAdd = (pclGetKI->clBA.GetLuk() * siGetFellowShip) / 100;

	clSoulGuardAdd.SetStr( siStrAdd );
	clSoulGuardAdd.SetHnd( siHndAdd );
	clSoulGuardAdd.SetDex( siDexAdd );
	clSoulGuardAdd.SetMag( siMagAdd );
	clSoulGuardAdd.SetWis( siWisAdd );
	clSoulGuardAdd.SetVit( siVitAdd );
	clSoulGuardAdd.SetLuk( siLukAdd );
}

void cltParametaBox::SetBufStatusUp(cltCharCommon* pclchar)
{
	if ( pclchar && IsPC( pclchar->GetCharUnique() ) )
	{
		ZeroMemory(&clbufAdd, sizeof(clbufAdd));

		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_STR))
		{
			clbufAdd.SetStr(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_STR)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_DEX))
		{
			clbufAdd.SetDex(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_DEX)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_MAG))
		{
			clbufAdd.SetMag(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_MAG)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_WIS))
		{
			clbufAdd.SetWis(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_WIS)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_VIT))
		{
			clbufAdd.SetVit(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_VIT)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_STATUE_UP_HAND))
		{
			clbufAdd.SetHnd(pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_STATUE_UP_HAND)->siPercent);
		}
		if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_OLYMPICMEDAL))// �ݸ޴�
		{
			SI32 siStr = pclchar->pclCI->clBI.clBufInfo.GetBufPercent(BUF_STATUE_UP_STR) ;
			SI32 siDex = pclchar->pclCI->clBI.clBufInfo.GetBufPercent(BUF_STATUE_UP_DEX) ;
			SI32 siMag = pclchar->pclCI->clBI.clBufInfo.GetBufPercent(BUF_STATUE_UP_MAG) ;
			SI32 siVit = pclchar->pclCI->clBI.clBufInfo.GetBufPercent(BUF_STATUE_UP_VIT) ;
			SI32 siHnd = pclchar->pclCI->clBI.clBufInfo.GetBufPercent(BUF_STATUE_UP_HAND) ;

			clbufAdd.SetStr(siStr + pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_OLYMPICMEDAL)->siPercent);
			clbufAdd.SetDex(siDex + pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_OLYMPICMEDAL)->siPercent);
			clbufAdd.SetMag(siMag + pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_OLYMPICMEDAL)->siPercent);
			clbufAdd.SetVit(siVit + pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_OLYMPICMEDAL)->siPercent);
			clbufAdd.SetHnd(siHnd + pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_OLYMPICMEDAL)->siPercent);
		}
	}
}

//[����] �߷�Ÿ�� �̺�Ʈ - ���� ����
void cltParametaBox::SetValentineEventAbility(cltCharCommon* pclchar)
{
	if( NULL == pclchar)
		return;

	clValentineAdd.Init();

	if( NULL == pclClient->m_pclValentineEventMgr)
		return;

	if( !IsPC(pclchar->GetID()))
		return;

	pclClient->m_pclValentineEventMgr->GetValentineBuf(pclchar,clValentineAdd);
}

void cltParametaBox::SetHinamatsuriAbility(cltCharCommon* pclchar)
{
	clHinamatsuriAdd.Init();

	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if( pclchar && IsPC( pclchar->GetCharUnique() ) )
		{
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				cltServer* pclserver = (cltServer*)pclClient;
				cltStrInfo* pclinfo = pclserver->pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );

				if (pclinfo->clCityhallStrInfo.IHaveEventNpc(pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL"))) == TRUE )
				{
					clHinamatsuriAdd.SetStr( 5 );
					clHinamatsuriAdd.SetDex( 5 );
					clHinamatsuriAdd.SetMag( 5 );
					clHinamatsuriAdd.SetVit( 5 );
					clHinamatsuriAdd.SetHnd( 5 );
					clHinamatsuriAdd.SetWis( 5 );
				}
			}
		}
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if( pclchar && IsPC( pclchar->GetCharUnique() ) )
		{
			cltCharClient* pclcharclient = (cltCharClient*)pclchar;

			for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) 
			{
				if( pclcharclient->siEventNPCKind[i] == pclClient->GetUniqueFromHash(TEXT("KIND_HINADOLL")))				
				{
					clHinamatsuriAdd.SetStr( 5 );
					clHinamatsuriAdd.SetDex( 5 );
					clHinamatsuriAdd.SetMag( 5 );
					clHinamatsuriAdd.SetVit( 5 );
					clHinamatsuriAdd.SetHnd( 5 );
					clHinamatsuriAdd.SetWis( 5 );
				}
			}
		}
	}
}

void cltParametaBox::SetWorldChristmasTreeAbility(cltCharCommon* pclchar)
{
	clWorldChristmasTreeAdd.Init();
	SI32	siWorldChristmasTree01Kind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE01"));
	SI32	siWorldChristmasTree02Kind = pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASWORLDTREE02"));

	if( pclClient->GameMode == GAMEMODE_SERVER )
	{
		if( pclchar && IsPC( pclchar->GetCharUnique() ) )
		{
			cltServer* pclserver = (cltServer*)pclClient;

			SI32 siWorldChristmasTree01ID = pclserver->siWorldTreeID[0];
			SI32 siWorldChristmasTree02ID = pclserver->siWorldTreeID[1];

			cltCharServer*	pclWorldChristmasTreeChar01 = (cltCharServer*)pclClient->pclCM->CR[siWorldChristmasTree01ID];
			cltCharServer*	pclWorldChristmasTreeChar02 = (cltCharServer*)pclClient->pclCM->CR[siWorldChristmasTree02ID];

			if(pclWorldChristmasTreeChar01)
			{
				if((pclWorldChristmasTreeChar01->GetMapIndex() == MAPINDEX_MAINFIELD) && (pclWorldChristmasTreeChar01->GetKind() == siWorldChristmasTree01Kind))
				{
					clWorldChristmasTreeAdd.SetStr( 5 );
					clWorldChristmasTreeAdd.SetDex( 5 );
					clWorldChristmasTreeAdd.SetMag( 5 );
					clWorldChristmasTreeAdd.SetVit( 5 );
					clWorldChristmasTreeAdd.SetHnd( 5 );
					clWorldChristmasTreeAdd.SetWis( 5 );
				}
			}

			if(pclWorldChristmasTreeChar02)
			{
				if((pclWorldChristmasTreeChar02->GetMapIndex() == MAPINDEX_MAINFIELD) && (pclWorldChristmasTreeChar02->GetKind() == siWorldChristmasTree02Kind))
				{
					clWorldChristmasTreeAdd.SetStr( 10 );
					clWorldChristmasTreeAdd.SetDex( 10 );
					clWorldChristmasTreeAdd.SetMag( 10 );
					clWorldChristmasTreeAdd.SetVit( 10 );
					clWorldChristmasTreeAdd.SetHnd( 10 );
					clWorldChristmasTreeAdd.SetWis( 10 );
				}
			}
		}
	}
	else if( pclClient->GameMode == GAMEMODE_CLIENT )
	{
		if( pclchar && IsPC( pclchar->GetCharUnique() ) )
		{
			SI32 siWorldChristmasTree01ID = pclClient->siWorldTreeID[0];
			SI32 siWorldChristmasTree02ID = pclClient->siWorldTreeID[1];

			if(siWorldChristmasTree01ID > 0)
			{
				clWorldChristmasTreeAdd.SetStr( 5 );
				clWorldChristmasTreeAdd.SetDex( 5 );
				clWorldChristmasTreeAdd.SetMag( 5 );
				clWorldChristmasTreeAdd.SetVit( 5 );
				clWorldChristmasTreeAdd.SetHnd( 5 );
				clWorldChristmasTreeAdd.SetWis( 5 );
			}

			if(siWorldChristmasTree02ID > 0)
			{
				clWorldChristmasTreeAdd.SetStr( 10 );
				clWorldChristmasTreeAdd.SetDex( 10 );
				clWorldChristmasTreeAdd.SetMag( 10 );
				clWorldChristmasTreeAdd.SetVit( 10 );
				clWorldChristmasTreeAdd.SetHnd( 10 );
				clWorldChristmasTreeAdd.SetWis( 10 );
			}
		}
	}
}

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI64 GetRequiredExpForLevel(SI32 level, SI32 siType)// SI32->SI64 ����ġ �����÷ο춧���� ����
{
	if(level < 1)								return 0;
	if(level > ExpForLevelUp.GetSize() )		return 0;

	switch(siType)
	{
	case EXPFORLEVEL_TYPE_CHARACTOR:
		{
			if( level > MAX_CHARACTER_LEVEL )	return 0;
		}
		break;
	case EXPFORLEVEL_TYPE_GUILD:
		{
			if( level > MAX_GUILD_LEVEL )	return 0;
		}
		break;
	}

	return ExpForLevelUp[level - 1][1];
}

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI32 GetRequiredFameExpForLevel(SI32 level)
{
	if(level < 1)								return 0;

	return FameExpForLevelUp[level - 1][1];

}

// �� ����ġ�� �ٰŷ� ������� ���Ѵ�. 
SI32 GetFameLevelFromExp(SI32 exp)
{
	for(SI32 i = 0; i < FameExpForLevelUp.GetSize(); i++)
	{
		if(FameExpForLevelUp[i][1] > exp)return i;
	}

	return 0;
}

// ����ġ�� �ٰŷ� �� ����ġ�� ������ ���Ѵ�.
SI32 GetLevelFromExp(SI32 exp, SI32 siType)
{
	if ( exp <= 0 ) return 1 ;

	for ( SI32 i = 0 ; i < ExpForLevelUp.GetSize() ; i ++ )
	{
		if ( exp < ExpForLevelUp[i][1] )
		{
			return i ;
		}
	}

	SI32 siReturnLevel = ExpForLevelUp.GetSize();

	switch(siType)
	{
	case EXPFORLEVEL_TYPE_CHARACTOR:
		{
			siReturnLevel = MAX_CHARACTER_LEVEL;
		}
		break;
	case EXPFORLEVEL_TYPE_GUILD:
		{
			siReturnLevel = MAX_GUILD_LEVEL;
		}
		break;
	}

	return siReturnLevel;
}

BOOL LoadExpData()
{
	FILE	*fp = NULL;

	SI64	data;
	TCHAR	buffer[1024 * 100];
	TCHAR	delimiter[] = TEXT("`\t\n");
	TCHAR	*pToken = NULL;
	INT		index;

	//----------------------------------
	// ����ġ�� ���Ѵ�. 
	//----------------------------------
	NFile file; 

	file.LoadFile( TEXT("LevelUpExp.dat") );

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{

		NLoadCryptFile( TEXT("LevelUpExp.dat"),  (BYTE*)buffer );
		buffer[ pHeader->dwDataSize ] = NULL;

		TCHAR *pStart = &buffer[ 0 ];
		int pos = 0;
		int lc = 0;

		while( pos < (int)pHeader->dwDataSize && lc < 4 ) 
		{

			if( buffer[ pos ] == 13 ) { ++lc; pos+=2; }
			else ++pos;
		}

		lc = 0;
		pStart = &buffer[ pos ];
		while( pos < (int)pHeader->dwDataSize && lc < ExpForLevelUp.GetSize() ) 
		{
			if( buffer[ pos ] == 13 ) 
			{ 
				pos+=2; pStart = &buffer[ pos ]; 
				_stscanf(pStart, TEXT("%I64d %I64d %I64d %I64d"), &ExpForLevelUp[lc][0], &ExpForLevelUp[lc][1], &ExpForLevelUp[lc][2], &data);
				++lc; 
			}
			else ++pos;
		}


	} else {

		if ( (fp = _tfopen(TEXT("LevelUpExp.dat"), TEXT("rt"))) == NULL )
		{
			MsgBox(TEXT("Error"), TEXT("File Open Error"));
			return FALSE;
		}

		// ù��° 5���� �����Ѵ�. 
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);

		index = 0;

		while( _fgetts(buffer, 1024, fp) != NULL)
		{ 
			if( index >= ExpForLevelUp.GetSize())	break;

			_stscanf(buffer, TEXT("%I64d %I64d %I64d %I64d"), &ExpForLevelUp[index][0], &ExpForLevelUp[index][1], &ExpForLevelUp[index][2], &data);
			index++;
		}

	}

	if( fp ) fclose(fp);

	//----------------------------------
	// ������ġ�� ���Ѵ�. 
	//----------------------------------
	file.LoadFile( TEXT("LevelUpFame.dat") );

	pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{

		NLoadCryptFile( TEXT("LevelUpFame.dat"),  (BYTE*)buffer );
		buffer[ pHeader->dwDataSize ] = NULL;

		TCHAR *pStart = &buffer[ 0 ];
		int pos = 0;
		int lc = 0;

		while( pos < (int)pHeader->dwDataSize && lc < 4 ) 
		{

			if( buffer[ pos ] == 13 ) { ++lc; pos+=2; }
			else ++pos;
		}

		lc = 0;
		pStart = &buffer[ pos ];
		while( pos < (int)pHeader->dwDataSize && lc < FameExpForLevelUp.GetSize() ) 
		{
			if( buffer[ pos ] == 13 ) 
			{ 
				pos+=2; pStart = &buffer[ pos ]; 
				_stscanf(pStart, TEXT("%I64d %I64d %I64d"), &FameExpForLevelUp[lc][0], &FameExpForLevelUp[lc][1], &FameExpForLevelUp[lc][2]);
				++lc; 
			}
			else ++pos;
		}
	}
	else
	{
		if ( (fp = _tfopen(TEXT("LevelUpFame.dat"), TEXT("rt"))) == NULL )
		{
			MsgBox(TEXT("Error"), TEXT("File Open Error fd3"));
			return FALSE;
		}

		// ù��° 5���� �����Ѵ�. 
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);
		_fgetts(buffer, 1024, fp);

		index = 0;

		while( _fgetts(buffer, 1024, fp) != NULL)
		{ 
			if( index >= FameExpForLevelUp.GetSize())	break;

			_stscanf(buffer, TEXT("%I64d %I64d %I64d"), &FameExpForLevelUp[index][0], &FameExpForLevelUp[index][1], &FameExpForLevelUp[index][2]);
			index++;
		}

		fclose(fp);
	}


	return TRUE;

}

BOOL LoadLevelUpReward()
{
	TCHAR	datfilename[MAX_PATH];
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// �ѱ�
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // ����
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  //NHN�߱�
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("ServerData\\LevelUpRewardG.txt"));
	}

	NDataLoader	dataloader;
	BOOL bLoadFile = FALSE;

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datfilename);		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile(datfilename);							
	}

	if (!bLoadFile)
	{
		MsgBox(TEXT("LoadLevelupReward()"), TEXT("LoadError:[%s]"), datfilename);
		return FALSE;
	}

	SI32 level;
	SI32 itemunique;
	SI32 itemcount;
	SI32 notice;
	TCHAR explain[256] = {0,};

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&level,			4,		
			NDATA_INT32,	&itemunique,	4,		
			NDATA_INT32,	&itemcount,		4,		
			NDATA_INT32,	&notice,		4,		
			NDATA_MBSTRING,	explain,	256,
			0,0,0
	};
	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() )
	{
		if( dataloader.ReadData())
		{
			if(level <= 0 || level > MAX_CHARACTER_LEVEL)
			{
				MsgBox(TEXT("Error"), TEXT("Invalid Level"));
			}

			bool bSet = false;
			for(int i=0; i<MAX_LEVELUP_REWARD_ITEM; i++)
			{
				if(!LevelUpReward[level].IsSetItem(i))
				{
					if(LevelUpReward[level].SetItem(i, itemunique, itemcount, notice))
					{
						bSet = true;
						break;
					}
				}
			}
			if(bSet == false)
			{
				MsgBox(TEXT("Error"), TEXT("NoMore Item Reward"));
			}
		}
	}

	return TRUE;
}

