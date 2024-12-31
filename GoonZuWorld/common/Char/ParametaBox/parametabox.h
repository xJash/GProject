//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _PARAMETABOX_H
#define _PARAMETABOX_H

#include "../../../Lib/Directives.h"
#include "..\Health\Health.h"

#define VIT_LIFE_RATE						4			// Life = Vit * VIT_LIFE_RATE
#define INT_MANA_RATE						4			// Mana	= Int * INT_MANA_RATE

#define MAX_LEVELUP_REWARD_ITEM				2

class cltPersonInfo;
class cltKindInfo;
class cltItemManagerCommon;
class cltHorse;
class cltCharCommon;
class cltPersonHorseInfo;
class cltPItemInfo;
class cltPersonHorseInfo;
class cltPSkillInfo;
class cltSummonScroll;
class cltIdentity;
class cltItem;

class cltBasicAbility;
class cltGMCommandKindInfo;

//---------------------------------
// LevelInfo
//---------------------------------
class cltLevelInfo{
public:
	SI64		siExp;// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	SI16		siLevel;
	SI16		siBonus;
	SI16		siSkillBonus;
	
	SI32		siFameExp;		// ������ġ. 
	SI16		siFameLevel;


	cltLevelInfo()
	{
		Init();
	}

	cltLevelInfo(SI64 exp, SI16 level, SI16 bonus, SI16 skillbonus, SI32 fameexp, SI16 famelevel)// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	{
		Set(exp, level, bonus, skillbonus, fameexp, famelevel);
	}
	
	void Init()
	{
		siExp			= 0;
		siLevel			= 0;	
		siBonus			= 0;
		siSkillBonus	= 0;
		siFameExp		= 0;
		siFameLevel		= 0;
	}

	void Set(SI64 exp, SI16 level, SI16 bonus, SI16 skillbonus, SI32 fameexp, SI32 famelevel)// sI32-> Si64 �� �����ϸ鼭 ������ ������ ���� ��������
	{
		siExp			= exp;
		siLevel			= level;	
		siBonus			= bonus;
		siSkillBonus	= skillbonus;
		siFameExp		= fameexp;
		siFameLevel		= famelevel;
	}

	bool IsSame(cltLevelInfo* pclinfo)
	{
		if(pclinfo == NULL)return false;

		if(siExp		!= pclinfo->siExp)return false;
		if(siLevel		!= pclinfo->siLevel)return false;
		if(siBonus		!= pclinfo->siBonus)return false;
		if(siSkillBonus != pclinfo->siSkillBonus)return false;
		if(siFameExp	!= pclinfo->siFameExp)	return false;
		if(siFameLevel	!= pclinfo->siFameLevel)	return false;

		return true;
	}
};


//--------------------------------
// ������ ���޵Ǿ�� �� �ʼ� �Ķ��Ÿ. 
//--------------------------------
class cltPIPInfoCommon : public cltBasicAbility{
public:
	// �⺻ �ɷ�ġ.(����ڰ� ���ʽ��� ������ �ø��� �ɷ�ġ.) 
/*	SI32	siStr;				// �ٷ�	
	SI32	siDex;				// ���߷�
	SI32	siVit;				// ����� 
	SI32	siMag;				// ����
	SI32	siLuk;				// ��� (2005-12-21�߰� by cyj)
	SI32	siWis;				//KHY - 0325 - ���� �߰�.
*/

	// ���� ����. 
	SI16	siLevel;
	SI16	siBonus;
	SI32	Life;				// ü�� 
	SI32	Mana;				// ����
	SI64	siExp;				// SI32->SI64 ����ġ �����÷ο춧���� ����
	
	cltPIPInfoCommon()
	{
		Init();
	}

	void Set(cltPIPInfoCommon* pip)
	{
		siStr	= pip->siStr;				// �ٷ�	
		siDex	= pip->siDex;				// ���߷�
		siVit	= pip->siVit;				// ����� 
		siMag	= pip->siMag;				// ���� 
		siLuk	= pip->siLuk;
		siWis	= pip->siWis;
		siHnd	= pip->siHnd;
		
		siExp	= pip->siExp;
		siLevel	= pip->siLevel;
		siBonus	= pip->siBonus;
		
		Life	= pip->Life;				// ü�� 
		Mana	= pip->Mana;				// ������ 
	}

	void Init()
	{
		siStr	= 5;
		siDex	= 5;
		siVit	= 5;
		siMag	= 5;
		siLuk	= 5;

		Life	= 5 * VIT_LIFE_RATE;
		Mana	= 5 * INT_MANA_RATE;

		// ������ �⺻������ 1�������� �����Ѵ�.
		siExp		= 0;
		siLevel		= 1;
		siBonus		= 5;
	}

	SI64 GetCurExp()const				{	return siExp;						}	// SI32->SI64 ����ġ �����÷ο춧���� ����
	void SetCurExp(SI64 exp)			{	siExp = max(0, exp);				}	// SI32->SI64 ����ġ �����÷ο춧���� ����

	SI32 GetBonus()const				{	return siBonus;						}
	void SetBonus(SI32 dat)				{	siBonus = dat;						}
	SI32 IncreaseBonus(SI32 amount)		{	siBonus+=amount; return siBonus;	}
	SI32 DecreaseBonus(SI32 amount)
	{ 
		if( siBonus > amount ) 	siBonus -= amount; 
		else					siBonus  = 0;
		
		return siBonus;
	}

	SI32 GetLevel()const				{	return siLevel;						}
	void SetLevel(SI32 dat)				{	siLevel = dat;						}
	SI32 IncreaseLevel(SI32 amount)
	{
		siLevel += amount;
		if( siLevel > MAX_CHARACTER_LEVEL )	siLevel = MAX_CHARACTER_LEVEL;

		return siLevel;
	}


	SI32 GetLife()const					{	return Life;						}
	void SetLife(SI32 life)				{	Life = life;						}
	SI32 DecreaseLife(SI32 mount)
	{
		if(Life > mount)	Life-= mount;
		else				Life = 0;

		return Life;
	}
	SI32 IncreaseLife(SI32 amount)
	{
		Life += amount;
		return Life;
	}

	SI32 GetMana()const{return Mana;}
	void SetMana(SI32 mana) 
	{ 
		Mana = mana; 
		Mana = Mana < 0 ? 0 : Mana; 
	} // [����] ���� ������ ���ü� ������.
	  // ó���� �ȹٲ���� ���� DataCopy �ϰ� �Ǹ� SetMana  �Լ��� ������� ���� ���̹Ƿ�. ���߿� ������ �׼��� �ִ� ������..
	SI32 DecreaseMana(SI32 mount)
	{
		if(Mana > mount)	Mana-= mount;
		else				Mana = 0;

		return Mana;
	}
	SI32 IncreaseMana(SI32 amount)
	{
		Mana += amount;
		return Mana;
	}

	// ����ġ�� �÷��ش�. 
	BOOL IncreaseExp(SI64 exp);// SI32->SI64 ����ġ �����÷ο춧���� ����	
	

	// ����ġ�� �����ش�. 
	void DecreaseExp(SI32 exp)
	{
		if(siExp >= exp)siExp -= exp;
		else siExp = 0;
	}

	void SetBasicAbility(cltBasicAbility* pclba)
	{
		siStr	= pclba->siStr;
		siDex	= pclba->siDex;
		siVit	= pclba->siVit;
		siMag	= pclba->siMag;
		siLuk	= pclba->siLuk;
		siWis	= pclba->siWis;
		siHnd	= pclba->siHnd;
	}

	SI32 CalcLevelDamage();
	
	// ������ ���� ���� ������ ������ ��´�.
	BOOL cltPIPInfoCommon::GetLevelUpRewardItem(SI32 level, SI32* pItemUnique, SI32* pItemCount, SI16* psiNotice);

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};

class cltPIPInfo : public cltPIPInfoCommon{
public:
//	SI32		siHnd;				// ������. 
	SI16		siFameLevel;
	SI16		siSkillBonus;
	SI32		siFameExp;			// ������ġ. 
	GMONEY		siMoney;			// ������.

public:

	cltPIPInfo()
	{
		Init();
	};

	~cltPIPInfo(){}

	void Init()
	{
		cltPIPInfoCommon::Init();

		siSkillBonus	= 1;
		siFameExp	= 0;
		siFameLevel	= 0;

		siMoney			= 0;

		siHnd	= 5;

	}

	void Set(cltPIPInfo* pip);
	void Set(cltPIPInfo ip);

	void Set(cltPIPInfoCommon* pip);

/*
	SI32 GetHnd()const{return siHnd;	}
	void SetHnd(SI32 dat){ siHnd = dat;}
	SI32 IncreaseHnd(SI32 amount){ siHnd += amount ; return siHnd;}
	SI32 DecreaseHnd(SI32 amount){ siHnd -= amount; return siHnd;}
*/
	SI32 GetSkillBonus()const{ return siSkillBonus;	}
	void SetSkillBonus(SI32 dat){siSkillBonus = dat;}
	SI32 IncreaseSkillBonus(SI32 amount){ siSkillBonus+=amount; return siSkillBonus;}
	SI32 DecreaseSkillBonus(SI32 amount)
	{ 
		if(siSkillBonus > amount) siSkillBonus-=amount; 
		else siSkillBonus = 0;
		return siSkillBonus;
	}


	void SetMoney(GMONEY money){siMoney	= money;}
	GMONEY GetMoney()const{return siMoney;}
	GMONEY IncreaseMoney(GMONEY money){siMoney += money; return siMoney;}
	GMONEY DecreaseMoney(GMONEY money){siMoney -= money; return siMoney;}

	// �� ����ġ�� �÷��ش�. 
	bool IncreaseFameExp(SI32 exp);

	void SetBasicAbility(cltBasicAbility* pclba)
	{
		cltPIPInfoCommon::SetBasicAbility(pclba);
		//siHnd	= pclba->siHnd;
	}

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};


//------------------------------------------
// KindInfo���� ���� ����. 
//------------------------------------------
class cltBasicParametaBox{

public:
	SI16	siWeightConstant;	// ������ ���� �� �ִ� ���� �����ϴ� ���. 

	SI16	siDamageResist;	// �������׷� 
	SI16	siMagicResist;	// �������׷�.

	SI32	siAttackE;		//���� �Ӽ�
	SI32    siAttackR;		//���� ����
	SI32	siDefenE;		//��� �Ӽ�
	SI32    siDefenR;		//��� ����

	cltBasicParametaBox()
	{
		ZeroMemory(this, sizeof(cltBasicParametaBox));
	}

	void Set(SI32 weightconstant, SI32 damageresist, SI32 magicresist,SI32 AttackE, SI32 AttackR, SI32 DefenE, SI32 DefenR )
	{
		siWeightConstant	= weightconstant;
		siDamageResist		= damageresist;
		siMagicResist		= magicresist;
		siAttackE			= AttackE;
		siAttackR			= AttackR;	
		siDefenE			= DefenE;
		siDefenR			= DefenR;	

	}
	void Set(cltBasicParametaBox* pclbpb)
	{
		siWeightConstant	= pclbpb->siWeightConstant;
		siDamageResist		= pclbpb->siDamageResist;
		siMagicResist		= pclbpb->siMagicResist;
	}

	SI32 GetAttackElementType(){ return siAttackE;}
	SI32 GetAttackElementPower(){ return siAttackR;}
	SI32 GetDefenElementType(){ return siDefenE;}
	SI32 GetDefenElementPower(){ return siDefenR;}


	SI32 GetWeightConstant()const{return siWeightConstant;}

	SI32 GetDamageResist()const{return siDamageResist;}

	SI32 GetMagicResist()const{return siMagicResist;}
};

//-------------------------------------------------------
// cltParametaBox
//-------------------------------------------------------
class cltParametaBox{
private:
	UI32 uiParaActionFrame;				// ���������� Action�� ���� ������. 

	UI32 uiLastGetCriticalRateFrame;	// ���������� ũ��Ƽ�� ���� Ȯ���� ���� ������. 
	SI32 siOldLevel;					// ���������� üũ�� ����. 

public:

	cltPIPInfo*				pclIP;

	cltBasicParametaBox*	pclBPB;		// KindInfo���� ���� ���´�. 

	cltKindInfo*			pclKI;

	cltPersonInfo*			pclCI;
	cltItemManagerCommon*	pclItemManager;
	

	SI32					siHealthStrRate;	// �ǰ��� ���� �ٷ� ����. 
	SI32					siHealthDexRate;	// �ǰ��� ���� ���߷� ����. 
	SI32					siHealthMagRate;	// �ǰ��� ���� ���� ����. 

	SI32					siHealthHndRate;	// �ǰ��� ���� ������ ����. 
	SI32					siHealthLukRate;	// �ǰ��� ���� ��� ����. 
	SI32					siHealthWisRate;	// �ǰ��� ���� ���� ����. 

	SI32					siSkillVitRate;		// ���������� ���� ����� ����
	SI32					siSkillMagRate;		// ���������� ���� ���� ����


/*	SI32					siGuildStr;			// ��� ��
	SI32					siGuildDex;			// ��� ����
	SI32					siGuildMag;			// ��� ����
	SI32					siGuildVit;			// ��� ü��
	SI32					siGuildHnd;			// ��� ������
	SI32					siGuildLuck;		// ��� ��
	SI32					siGuildWis;			// ��� ����*/

	SI32					siHorseStr;
	SI32					siHorseDex;
	SI32					siHorseMag;

	cltBasicAbility			clBasicBA;	// �⺻ �ɷ�
	cltBasicAbility			clEquipBA;	// ��� ���� �ɷ�ġ ���. 
	cltBasicAbility			clTotalBA;	
	cltBasicAbility			clHorseBA;
	cltBasicAbility			clGuildBA;
	cltBasicAbility			clHealthAdd;
	cltBasicAbility			clSetItemAdd;
	cltBasicAbility			clSkillAdd;
	cltBasicAbility			clbufAdd;		//[����] ������ ���� ���� ����. => 2008-6-18
	cltBasicAbility			clElixirAdd;	//[����] ������ ���� ����.		=> 2008-6-18
	cltBasicAbility			clHinamatsuriAdd;	// PCK : �������긮 �̺�Ʈ�Ⱓ�� �޴� ���� ���� (08.12.17)
	cltBasicAbility			clValentineAdd;	//[����] �߷�Ÿ�� ���� ���� ���� ����
	//cltBasicAbility			clHorsePartsAdd;

	cltBasicAbility			clSoulGuardAdd;	// ��ȣ���ɿ����� �߰� �ɷ�ġ
	cltBasicAbility			clWorldChristmasTreeAdd;		// [���] ũ�������� �̺�Ʈ�� ���� �߰� �ɷ�ġ

	bool					bSetTotalBA;	// TotalBA�� �ѹ��̶� ����ϸ�, true�� �����ȴ�.

	//KHY - 1220 - ���Žý���.
	cltBasicAbility			clTransFormBA;	// ���ſ� ���� �ɷ�ġ ���. 
	SI32					siTransFormSyc; // ���� ĳ������  ��ũ�� %.

	SI32					siReservedLife;		// ����� ü��. 

	cltHealth				clHealth;	// �ǰ� .

	cltGMCommandKindInfo*	pclGMCommandKindInfo;	// CMT��ɾ�� ������ ������ ����

//--------------------------------------------------------------------------------------
//KHY - 0326 - ���ο� ���Ŀ� ���� ������. - �ƿ� �и� ���״�. - ���� Ÿ�Կ� ����.
// ���߿� �̰͸� ���� �����ָ� �ȴ�.
//--------------------------------------------------------------------------------------
protected:

	//���� ���ݷ� - �̰����� �����Ǵ� ���� ���� ���� ������ ���̴�.
	SI16 siTotalPHysicalMinAttackDmg;		// ���� �ּ� ���� ������.
	SI16 siTotalPHysicalMaxAttackDmg;		// ���� �ִ� ���� ������.
	SI16 siEquipPHysicalMinAttackDmg;		// ��� ���� �ּ� ���� ������. 
	SI16 siEquipPHysicalMaxAttackDmg;		// ��� ���� �ִ� ���� ������. 
	SI16 siStrPHysicalAttackDmg;			// �ٷ¿� ���� ���� ������.

	//���� ���ݷ� - �̰����� ������ ����, �� ������ ���� ���㰡 �ջ�Ǿ� ���� ���� ���㰡 ���´�.
	SI16 siTotalMagicalMinAttackDmg;		// ���� �ּ� ���� ������.
	SI16 siTotalMagicalMaxAttackDmg;		// ���� �ִ� ���� ������.
	SI16 siEquipMagicalMinAttackDmg;		// ��� ���� �ּ� ���� ������. - %
	SI16 siEquipMagicalMaxAttackDmg;		// ��� ���� �ִ� ���� ������. - %
	//REAL32 siMagMagicalAttackDmg;			// ���� �� ���� ���� ������. - �ʿ����.

	//���� ���߷� - Hit �ÿ� ���� ��� �ȴ�.
	SI32 siTotalPHysicalHitRate;			// ���� ���� ���߷�.
	SI32 siPHysicalHitRateRank;				// ���� ���ߵ�� - Hnd ����.
	SI32 siPHysicalHitRateLevel;			// ���� ���� ���� ����.
	SI32 siEquipPHysicalHitRate;			// ��� ���� ���� ���߷�. - %
	SI16 siAddPHysicalHitRate;				// �߰� ���� ���߷�. - NPC��

	//���� ���߷� - Hit �ÿ� ���� ��� �ȴ�.
	SI32 siTotalMagicalHitRate;			// ���� ���� ���߷�.
	SI32 siMagicalHitRateRank;				// ���� ���ߵ�� - Wis ����.
	SI32 siMagicalHitRateLevel;				// ���� ���� ���� ����.
	SI32 siEquipMagicalHitRate;				// ��� ���� ���� ���߷�. - %
	SI16 siAddMagicalHitRate;				// �߰� ���� ���߷�. - NPC��

	// ���� ���� 
	SI32 siTotalPHysicalDefensiveRate;			// ���� ���� ����. - %
	SI32 siPHysicalDefensive;					// ���� ����.
	SI16 siEquipPHysicalDefensive;				// ��� ���� ���� ����. 
	SI32 siHndPHysicalDefensive;				// �����ֿ� ���� ���� ����.
	
	// ���� ���� 
	SI32 siTotalMagicalDefensiveRate;			// ���� ���� ����. - %
	SI32 siMagicalDefensive;						// ���� ����.
	SI16 siEquipMagicalDefensive;				// ��� ���� ���� ����. - %
	SI32 siWisMagicalDefensive;				// ������ ���� ���� ����.

	//���� ȸ�Ƿ� - Hit �ÿ� ���� ��� �ȴ�.
	SI32 siTotalPHysicalDodgeRate;		// ���� ���� ȸ�Ƿ�.
	SI32 siPHysicalDodgeRateRank;		// ���� ȸ�ǵ��
	SI32 siPHysicalDodgeRateLevel;		// ���� ȸ�� ���� ����.
	SI16 siEquipPHysicalDodgeRate;		// ��� ���� ���� ȸ�Ƿ�. - %

	//���� ȸ�Ƿ� - Hit �ÿ� ���� ��� �ȴ�.
	SI32 siTotalMagicalDodgeRate;		// ���� ���� ȸ�Ƿ�.
	SI32 siMagicalDodgeRateRank;		// ���� ȸ�ǵ��
	SI32 siMagicalDodgeRateLevel;		// ���� ȸ�� ���� ����.
	SI16 siEquipMagicalDodgeRate;		// ��� ���� ���� ȸ�Ƿ�. -%

	//ü��.(�����)
	SI32 siTotalHitpoint;		// ���� ü��.
	SI16 siEquipHitpoint;		// ��� ���� ü��. - %
	SI32 siVitHitpoint;		// ����¿� ���� ü��.

	//������.(����)
	SI32 siTotalManapoint;		// ���� ����.
	SI16 siEquipManapoint;		// ��� ���� ����. - %
	SI32 siMagManapoint;		// ���¿� ���� ����.

	//���Է� (����ǰ)
	SI32 siTotalWeigt;		// ����ǰ ���Է�.
	SI16 siEquipWeigt;		// ��� ���� ���Է�. - %
	SI32 siStrWeigt;			// ���� ���� ���Է�

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// �� �������ͽ� - ���� ���Ŀ��� ���ȴ�.
//--------------------------------------------------------------------------------------

public:

	//--------------------------------
	// ����. 
	//--------------------------------
	SI32	siLevelAC;			// ������ ���� ����. 
	SI32	siEquipAC;			// ��� ���� ����.
	SI32	siDefaultAC;
	
	SI32	siGeneralAC;		// ����� ����ȿ���� ���� ����. 
	DWORD	dwGeneralACClock;	// ����ȿ�� ���� �ð�. 

	SI32	siEvolveAC;			// ��ȭ�� ���� ����. 
	SI32	siBufAC;			// ������ ���� ����(%)
	SI32	siNamingAC;			// ��Ī�� ���� ����(%)
	//KHY - 0124 - ��í����- ���� ���� ������.
	SI32	siTransFormAC;			// ���ſ� ���� ����(%)
	

	SI32	TotalAC;			// ��ü ����. 

	SI32 TotalDamageResist;

	SI32 TotalMagicResist;
	


	SI32 siAttackRange, siItemAttackRange;                 // ���� �����Ÿ� 

//---------------------
//  ���� �������ͽ� 
//---------------------
	SI32 MaxLife;
	SI32 MaxMana;
	SI32 MaxStamina;

	//----------------------
	// ũ��Ƽ�� ���� Ȯ�� 
	//----------------------
	SI32 siCriticalRate;

	//----------------------
	// ������ 
	//----------------------
	SI16 siStrDamage;			// �ٷ¿� ���� ������. 
	SI16 siStaffSkillDamage;	// �����̼��� ���� ������. 
	SI16 siLevelDamage;			// ������ ���� ������ 
	SI16 siTorpedoDamage;		// ��ڿ� ���� ���ݷ� ��� ȿ��. 

	SI32 TotalEquipMinDamage;	// ���⿡ ���� ������. 
	SI32 TotalEquipMaxDamage;

	SI32	siGeneralDamage;		// ����� ����ȿ���� ���� ������.
	DWORD	dwGeneralDamageClock;	// ����ȿ�� ���� �ð�. 

	SI32 siEvolveDamage;			// ��ȭ�� ���� ������. 

	SI32 siBufDamage;				// ������ ���� ������(%).
	SI32 siNamingDamage;			// ��Ī�� ���� ������(%).
	
	SI32 TotalMinDamage;
	SI32 TotalMaxDamage;
	
	//---------------------
	// ��
	//---------------------
	SI32 siTotalLuck;
	SI32 siEquipLuck;


	//----------------------
	// MagicDelay ���̱�
	//-----------------------
	SI32 siMagicDecDelay;


	//--------------------
	// �̵��ӵ�. 
	//--------------------
	SI32 BasicMoveSpeed;
	SI32 ShoesMoveSpeed;
	SI32 TotalMoveSpeed;
	SI32 BufMoveSpeed;
	
	SI32 GivenMoveSpeed;	// �����κ��� �־��� �̵� �ӵ�. 


	SI32 siAttackType;								// ���� ���. 	
	DWORD dwAttackInterval;							// ���� �ֱ�.   = ���� �ӵ�.

	//--------------------------
	// ���߷� 
	//--------------------------
	SI32 AR;
	SI32 DR;
	SI32 HitRate;
	SI32 siEquipAssistHitRate;
	SI32 siWeaponDefaultHitRate;

	//--------------------------
	// ��� ���� ������ ����. 
	//--------------------------
	SI32 siEquipAssistDamageReduceRate;

	//--------------------------
	// ��� ���� 
	//--------------------------
	SI32 siArmWeaponUnique;						// ���� ����ϰ� �ִ� ������ ����ũ..

	cltShapeEquipInfo clShapeEquip;

protected:

	// ������ ���� ���� ��� ȿ���� ���Ѵ�. 
	SI32 CalcLevelAC(SI32 level);
	
	//----------------------------------------------------------
	// ����(�������ͽ�) ��� �Լ�
	//----------------------------------------------------------
	void SetEquipBasicAbility(cltCharCommon* pclchar, cltItem* pclitemlist, SI32 activeweaponpos);
	void SetTransformBasicAbility(cltCharCommon* pclchar, cltItem* pclitemlist, SI32 activeweaponpos);
	void SetHorseBasicAbility(cltPersonHorseInfo* pclhorseinfo, cltCharCommon* pclchar);
	void SetGuildBasicAbility(cltCharCommon* pclchar);
	void SetHealthAddAbility(cltHealthInfo* pclhealthinfo, cltBasicAbility BasicBA);
	void SetSetItemAddAbility(cltCharCommon* pclchar, cltItem* pclitemlist);
	void SetSkillAddAbility(cltItem* pclitemlist, SI32 activeweaponpos, cltPSkillInfo* pclskillinfo, cltBasicAbility BasicBA);
	void SetElixirAddAbility(cltCharCommon* pclchar );
	void SetSoulGuardAddAbility(cltCharCommon* pclchar );

	//[����] ������ ���� ���ȿ� ����Ǵ� �ɷ�ġ. => 2008-6-18
	void SetBufStatusUp(cltCharCommon* pclchar);

	//[����] �߷�Ÿ�� �̺�Ʈ - ���� ����
	void SetValentineEventAbility(cltCharCommon* pclchar);

	// PCK : �������긮 �̺�Ʈ �Ⱓ���ȿ� �޴� ���� �ɷ�ġ (08.12.17)
	void SetHinamatsuriAbility(cltCharCommon* pclchar);
	//// ���� �����̾� ������ �����ϸ� �������ͽ� ���
	void SetPremiumPartsstatusUp(  SI32 PremiumItemUnique );
	// [���] ũ�������� �̺�Ʈ - ���縮�� �տ� ũ�������� Ʈ���� �Ǽ��Ǹ� 1��: +5, 2��: +10�� �������ͽ� ��� ȿ���� �ش�. (09.10.20)
	void SetWorldChristmasTreeAbility(cltCharCommon* pclchar);

	//-----------------------------------------------------------
	// �ɷ�ġ ���� �Լ�. - ���ݷ�, ����, ���߷�,ȸ����
	//-----------------------------------------------------------
	void SetPhysicalAttackDemage(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo ,bool *bSwitch, SI16 siAttackWearStoneNum); // ���� �ּ�, �ִ� ���ݷ� ����.
	void SetMagicalAttackDemage(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo ,bool *bSwitch);  // ���� �ּ�, �ִ� ���ݷ� ����.

	void SetPhysicalHitRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltIdentity* pclidentityinfo, cltPSkillInfo* pclskillinfo); // ���� ���߷� ����.
	void SetMagicalHitRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltIdentity* pclidentityinfo, cltPSkillInfo* pclskillinfo);  // ���� ���߷� ����.

	void SetPhysicalDefensiveRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc ,SI32 gamemode ,cltPSkillInfo* pclskillinfo,cltIdentity* pclidentityinfo, bool *bSwitch, SI16 siDefenseWearStoneNum);// ���� ����� ����.
	void SetMagicalDefensiveRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo);  // ���� ���������.

	void SetPhysicalDodgeRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo); // ���� ȸ���� ����.
	void SetMagicalDodgeRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo);  // ���� ȸ���� ����.

	void SetHitPoint(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos, bool bnpc, cltPSkillInfo* pclskillinfo); 	// ����� ����.
	void SetManaPoint(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc, cltPSkillInfo* pclskillinfo);// ������ ����.
	void SetWeight(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc); 	// ���Է� ����.

	void SetCritcalRate(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltPSkillInfo*	pclskillinfo,cltSummonScroll*	pclsummonscroll);
	void SetEtcSetting(cltCharCommon* pclchar, cltItem* pclitemlist, SI16 activeweaponpos,bool bnpc,cltPSkillInfo*	pclskillinfo,cltSummonScroll*	pclsummonscroll, cltPersonHorseInfo* pclhorseinfo);

	//-----------------------------------------------------------

	SI16 etcPhysicalDefensiveRate(cltItem* pclitemlist, SI16 activeweaponpos,cltCharCommon* pclchar,  SI32 * DefensivePer , SI32 gamemode ,cltPSkillInfo* pclskillinfo , bool *bSwitch);
	//-----------------------------------------------------------

public:

	cltParametaBox();
	void Init(cltItemManagerCommon* pclitemmanager, cltPIPInfo* pclip, cltHealthInfo* pclhealthinfo, cltKindInfo* pclki, cltGMCommandKindInfo* pclGMki) ;


	BOOL Action(cltCharCommon* pclchar, SI32 personid, SI32 activeweaponpos, 
		cltItem*			pclitemlist,	// ���ǰ ������ ����Ʈ . 				
		//cltPItemInfo* pclcharitem, 
		cltPersonHorseInfo* pclhorseinfo, 
		cltHealthInfo*		pclhealthinfo, 
		cltPSkillInfo*		pclskillinfo, 
		cltIdentity*		pclidentityinfo, 
		//cltSummonScroll*	pclsummonscroll,
		SI16				siSummonAttackWearStoneNum,
		SI16				siSummonDefenseWearStoneNum,
		SI32 gamemode, bool bnpc, bool bmonsterhero = false );

	
	SI32 GetTotalAC()			{return TotalAC;}
	SI32 GetTotalDamageResist()	{return TotalDamageResist;}
	SI32 GetTotalMagicResist()	{return TotalMagicResist;}
	SI32 GetTotalEquipMinDamage(){return TotalEquipMinDamage;}
	SI32 GetTotalEquipMaxDamage(){return TotalEquipMaxDamage;}
	SI32 GetTotalMoveSpeed()	{return TotalMoveSpeed;}
	SI32 GetAR()				{return AR;}
	SI32 GetDR()				{return DR;}
	SI32 GetHitRate(SI32 enemydr, bool MagicFlag = false);			
	//-----------------------------------------------------------------------------
	//KHY - 0327
	SI32 GetHitRate(cltCharCommon* pclchar, cltCharCommon* pclAttackChar, bool MagicFlag = false); // ���߷��� ���Ѵ�.			
	SI32 GetDodgeRate(cltCharCommon* Enemypclchar, cltCharCommon* pclAttackChar, bool MagicFlag= false); // ȸ������ ���Ѵ�.
	SI32 GetDefensiveRate(cltCharCommon* Enemypclchar,bool MagicFlag = false); // ������ ���Ѵ�.	

	SI32 GetClientHitRate( bool MagicFlag ); // ���߷��� ���Ѵ�. - Ŭ���̾�Ʈ���̴�. - ���� �ڱ� ������ �����ؼ� ����Ѵ�.			
	SI32 GetClientDodgeRate(bool MagicFlag ); // ȸ������ ���Ѵ�.- Ŭ���̾�Ʈ���̴�. - ���� �ڱ� ������ �����ؼ� ����Ѵ�.
	SI32 GetClientDefensiveRate(bool MagicFlag ); // ������ ���Ѵ�.	- Ŭ���̾�Ʈ���̴�. - ���� �ڱ� ������ �����ؼ� ����Ѵ�.
	//-----------------------------------------------------------------------------

	SI16 GetTotalPHysicalMinAttackDmg( ){return siTotalPHysicalMinAttackDmg;}  // ���� �ּ� ���� ������.
	SI16 GetTotalPHysicalMaxAttackDmg( ){return siTotalPHysicalMaxAttackDmg;} // ���� �ִ� ���� ������.
	
	SI16 GetTotalMagicalMinAttackDmg( ){return siTotalMagicalMinAttackDmg;}  // ���� �ּ� ���� ������.
	SI16 GetTotalMagicalMaxAttackDmg( ){return siTotalMagicalMaxAttackDmg;} // ���� �ִ� ���� ������.

	//SI16 GetTotalPHysicalHitRate( ){return siTotalPHysicalHitRate;} 				 // ���� ���� ���߷�.
	SI16 GetPHysicalHitRate( ){return siPHysicalHitRateRank;} 			 // ���� ���ߵ�� - Hnd ����.
	SI16 GetEquipPHysicalHitRate( ){return siEquipPHysicalHitRate;}  		//  ��� ���� ���� ���߷�. - %

	//SI16 GetTotalMagicalHitRate( ){return siTotalMagicalHitRate;} 			// ���� ���� ���߷�.
	SI16 GetMagicalHitRate( ){return siMagicalHitRateRank;} 			// ���� ���� ���߷�.
	SI16 GetEquipMagicalHitRate( ){return siEquipMagicalHitRate;} 	// ��� ���� ���� ���߷�. - %

	//SI16 GetTotalPHysicalDefensiveRate( ){return siTotalPHysicalDefensiveRate;}  // ���� ���� ����.
	SI16 GetPHysicalDefensive( ){return siPHysicalDefensive;}  			// ���� ����.
	SI16 GetEquipPHysicalDefensive( ){return siEquipPHysicalDefensive;} // ��� ���� ���� ����. 

	//SI16 GetTotalMagicalDefensiveRate( ){return siTotalMagicalDefensiveRate;} 	// ���� ���� ����.
	SI16 GetMagicalDefensive( ){return siMagicalDefensive;} 				// ���� ����.
	SI16 GetEquipMagicalDefensive( ){return siEquipMagicalDefensive;} 	// ��� ���� ���� ����. - %

	//SI16 GetTotalPHysicalDodgeRate( ){return siTotalPHysicalDodgeRate;} 			// ���� ���� ȸ�Ƿ�.
	SI16 GetPHysicalDodgeRateRank( ){return siPHysicalDodgeRateRank;} 	// ���� ȸ�ǵ��
	SI16 GetEquipPHysicalDodgeRate( ){return siEquipPHysicalDodgeRate;} 	// ��� ���� ���� ȸ�Ƿ�. - %

	//SI16 GetTotalMagicalDodgeRate( ){return siTotalMagicalDodgeRate;} 				// ���� ���� ȸ�Ƿ�.
	SI16 GetMagicalDodgeRateRank( ){return siMagicalDodgeRateRank;} 		// ���� ȸ�ǵ��
	SI16 GetsiEquipMagicalDodgeRate( ){return siEquipMagicalDodgeRate;} 	// ��� ���� ���� ȸ�Ƿ�. -%

	SI32 GetTotalHitpoint( ){return siTotalHitpoint;} // ���� ü��.
	SI32 GetTotalManapoint( ){return siTotalManapoint;} 	// ���� ����.
	SI32 GetTotalWeight( ){return siTotalWeigt;} 	// ���� ����.
	
	//-----------------------------------------------------------------------------

	SI32 GetMaxLife();	
	void SetMaxLife(SI32 life)	{MaxLife = life;}
	SI32 GetMaxMana()	;
	void SetMaxMana(SI32 mana)	{MaxMana = mana;}
	void SetMaxStamina(SI32 stamina)	{MaxStamina = stamina;}

	SI32 GetTotalMinDamage(){return TotalMinDamage;}
	SI32 GetTotalMaxDamage(){return TotalMaxDamage;}
	//SI32 GetDpower(){return Dpower;}

	//--------------------------------
	// ��Ÿ� ���� �Լ� 
	//--------------------------------
	SI32 GetItemAttackRange(){return siItemAttackRange;}
	void SetItemAttackRange(SI32 range){siItemAttackRange = range;}

	SI32 GetAttackRange()const{ return siAttackRange;}

	//-------------------------------
	// ���ݹ�� ���� �Լ�. 
	//-------------------------------
	SI32 GetAttackType()const{return siAttackType;}
	void SetAttackType(SI32 type){siAttackType = type;}

	// ������ ������ �ٰŷ� ���� �Ӽ��� �ľ��Ѵ�. 
	void CalculateAttackType(cltCharCommon* pclchar, SI16 activeweapon, cltItem* pclitemlist);

	//----------------------------------
	// ũ��Ƽ�� ���� Ȯ�� ���ϱ�. 
	//----------------------------------
	SI32 GetCriticalRate()const{return siCriticalRate;}

	//----------------------------------------
	// ��æƮ ���� by tae-yang
	//----------------------------------------
	SI32 GetEnchantDefDamage(SI32 EnchantType, cltItem *pclItemList);
	SI32 GetEnchantAttDamage(SI32 EnchantType, cltItem *pclItemList);


	// �ּҰ��ݷ�, �ִ� ���ݷ��� �����Ͽ� ���� ���ݷ��� ���´�. 
	SI32 CalcApower();

	// ���� ������ �ö󰡴µ� �ʿ��� ����ġ. 
	SI64 GetNextExp();// SI32->SI64 ����ġ �����÷ο춧���� ����
	// ���� �������� ���� ������ �ö���µ� �ʿ��ߴ� ����ġ. 
	SI64 GetPrevExp();// SI32->SI64 ����ġ �����÷ο춧���� ����

	//------------------------
	// ���� ������ �߰��� 
	//------------------------
	SI32 GetAddMagicDamage()
	{
		return clTotalBA.GetMag()/4;
	}

	// �������ͽ��� ��ȭ�ǰ� �ɰ���� �������� �̸� ����غ��� �Լ�
	// ������ ���� 2.5�� 1�� ����
	SI32 GetStrDamageIfChange(SI32 ChangeStr, bool Flag)
	{
		if( Flag )
		{
			return  (clTotalBA.GetStr() + ChangeStr) * 2 / 5;
		}
		else
			return  (clTotalBA.GetStr() + ChangeStr) / 5;
	}

	SI32 GetMagDamageIfChange(SI32 ChangeMag)
	{
		return  (clTotalBA.GetMag() + ChangeMag)/4;
	}

	// ���� �ɷ��� ��ġȭ�ؼ� ���´�. 
	SI32 GetBattlePower();
	// ���� �ɷ��� ������ ��ȯ�ؼ� ���´�.
	SI32 GetBattleLevel();
	SI32 GetBossBattleLevel();

	//------------------------
	// ���� 
	//------------------------
	SI32 GetMaxWeight();
	
};


//---------------------------------
// LevelInfo
//---------------------------------
class cltLevelUpReward{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_LEVELUP_REWARD_ITEM>		ItemUnique;
	NSafeTArray<SI32, MAX_LEVELUP_REWARD_ITEM>		ItemCount;
	NSafeTArray<SI16, MAX_LEVELUP_REWARD_ITEM>		siNotice;
#else
	SI32	ItemUnique[MAX_LEVELUP_REWARD_ITEM];
	SI32	ItemCount[MAX_LEVELUP_REWARD_ITEM];
	SI16	siNotice[MAX_LEVELUP_REWARD_ITEM];
#endif

	cltLevelUpReward()
	{
		Init();
	}

	void Init()
	{
		ZeroMemory( this, sizeof(cltLevelUpReward) );
	}

	bool IsSetItem(SI32 index)
	{
		if(index < 0 || index > MAX_LEVELUP_REWARD_ITEM-1)	return true;

		if(ItemUnique[index] > 0)	return true;
		if(ItemCount[index] > 0)	return true;

		return false;
	}

	bool SetItem(SI32 index, SI32 Unique, SI32 Count, SI16 Notice)
	{
		if(index < 0 || index > MAX_LEVELUP_REWARD_ITEM-1)	return false;
		
		ItemUnique[index]	= Unique;
		ItemCount[index]	= Count;
		siNotice[index]		= Notice;

		return true;
	}
};

enum EXPFORLEVEL_TYPE
{
	EXPFORLEVEL_TYPE_CHARACTOR,
	EXPFORLEVEL_TYPE_GUILD,
};

BOOL LoadExpData();

// �������� ���� ���� �ε� - 2007.02.06 ������ - by LEEKH
BOOL LoadLevelUpReward();

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI64 GetRequiredExpForLevel(SI32 level, SI32 siType = EXPFORLEVEL_TYPE_CHARACTOR);// SI32->SI64 ����ġ �����÷ο춧���� ����

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI32 GetRequiredFameExpForLevel(SI32 level);

// �� ����ġ�� �ٰŷ� ������� ���Ѵ�. 
SI32 GetFameLevelFromExp(SI32 exp);

// ����ġ�� �ٰŷ� �� ����ġ�� ������ ���Ѵ�.
SI32 GetLevelFromExp(SI32 exp, SI32 siType = EXPFORLEVEL_TYPE_CHARACTOR);

// �������� ���� ���� ������ - 2007.02.06 ������ - by LEEKH
BOOL GetLevelUpRewardItem(SI32* pItemUnique, SI32* pItemCount, SI16* psiNotice);

#endif
