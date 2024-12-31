//---------------------------------
// 2003/5/28 ���°�
//---------------------------------
#ifndef _CLTKINDINFO_H
#define _CLTKINDINFO_H  

#include "../../Char/CharAni/CharAni.h"
#include "../ParametaBox/ParametaBox.h"
#include "../../Item/ItemCommon/cltItem.h"

//-----------------
// Definition
//-----------------
#define MAX_KIND_NAME_LENGTH					50
#define MAX_KINDINFO_NUMBER						500			// ���Ǿ� ������ �ƽ� ��ġ ����. 400->420->500
#define MAX_ITEM_PROBABILITY_PER_KIND			5			// �������� Kind�� ������ �� �ִ� �ʱ� �������� ��.
#define MAX_SUMMON_CHATCOMMANDNUMBER			100			// ä��Ŀ�ǵ��� �ִ� ����
//---------------------------------------------------------------------
// ĳ������ ����
//---------------------------------------------------------------------
#define KIND_HERO1						1		// ����
#define KIND_HEROINE1					2		// ����
#define KIND_HERO2						3		// ����
#define KIND_HEROINE2					4		// ����¦
#define KIND_HERO3						5		// �Ϻ���
#define KIND_HEROINE3					6		// �Ϻ���
#define KIND_HERO4						7		// ���糲
#define KIND_HEROINE4					8		// �����

#define KIND_SYSTEM						9		// �ý��۴�� ������ ĳ����. (�������� ĳ�����̴�.) 

#define KIND_JOKER						253		// ������� ����

//#define MAX_KINDINFO_NUMBER			240		
//#define MAX_KIND_NUMBER				240

//--------------------------------
//�� �Ķ��Ÿ���� ���� 
//--------------------------------

#define DPOWER(x)			(x)		// ���� ���� 
#define MOVESPEED(x)	    (x)		// �̵��ӵ� ���� 
#define SIZE(x)				(x)		// ������ ���� 
#define ATTACKINTERVAL(x)	(x)		// ���� �ֱ� 
#define PERCENT(x)			(x)		// �ۼ�Ʈ ���� 

// ���� ���� ����
#define SWORD_DP(x)			(x)
#define SPEAR_DP(x)			(x)
#define AXE_DP(x)			(x)
#define BOW_DP(x)			(x)
#define GUN_DP(x)			(x)
#define STAFF_DP(x)			(x)
#define CANNON_DP(x)		(x)

class cltQuestRewardInfo;


//---------------------------------------------
// DROP ITEM ������ ���������� ����ü //JAYCEE
//---------------------------------------------
class cltDropItem{
public:
	TCHAR szName[MAX_ITEM_NAME_LENGTH]; // MAX_ITEM_NAME_LENGTH
	TCHAR szItemNum[20];
	TCHAR szPercent[15];

	cltDropItem();
	
};

//--------------------------------------------
// ���� ĳ���� �ǰݽ� �ִ� ��ǰ ���� 
//--------------------------------------------
class cltBossItemInfoUnit{
public:
	SI16 siItemUnique;
	SI16 siRate;		
	
	cltBossItemInfoUnit();
	cltBossItemInfoUnit(SI16 itemunique, SI16 rate);

	void Init();
	void Set(cltBossItemInfoUnit* pclinfo);
	
};
#define MAX_BOSS_ITEM_NUMBER	30
class cltBossItemInfo{
public:

	SI32	siItemIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltBossItemInfoUnit, MAX_BOSS_ITEM_NUMBER>	clUnit;
#else
	cltBossItemInfoUnit clUnit[MAX_BOSS_ITEM_NUMBER];
#endif

	cltBossItemInfo();
	void Init();
	void Set(cltBossItemInfo* pclinfo);
	void Add(cltBossItemInfoUnit* pclinfo);
	void Add(SI16 itemunique, SI16 rate);

	// ������ �������� ã�´�. 
	bool GetRandItem(SI32* pitemunique, SI32* pitemnum);


};

//---------------------------------------------
// ĳ���Ͱ� ���� �Ǵ� �������� ������ �� ����. 
//---------------------------------------------
class cltKindItemProbability{
public:
	SI32	siItemUnique;
	SI32	siProbability;						//  1/10000
	SI32	siItemNum;							// ������ �������� ����. 
	SI32	siItemMinNum;

	cltKindItemProbability();
	~cltKindItemProbability();

	void Set(SI32 unique, SI32 probability, SI32 itemnum,SI32 minnum);
};

class cltKindItemProbabilitySet{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltKindItemProbability, MAX_ITEM_PROBABILITY_PER_KIND>		clKindItemProbability;
#else
	cltKindItemProbability clKindItemProbability[MAX_ITEM_PROBABILITY_PER_KIND];
#endif

	cltKindItemProbabilitySet(){};
	~cltKindItemProbabilitySet(){}

	void Init();

	// �������� �߰��Ѵ�. 
	//prbability : 1/10000 Ȯ��. 
	BOOL Add(SI32 siitemunique, SI32 prbability, SI32 itemnum,SI32 minnum);

	// �����ϰ� �ϳ��� �������� ����ũ ���� �����Ѵ�. �ƹ��͵� �������� ���� ���� �ִ�.
	bool GetRandDropItem(SI32 level, SI32 AddRate, SI32* punique, SI32* pitemnum);

	// �������� ����ũ�� �ٰŷ� �� ĳ���Ͱ� �� ������ �ִ� �Ͱ� ���õ� ������ ã�´�. 
	cltKindItemProbability* FindItem(SI32 itemunique);

};

//---------------------------------------
// ����Ʈ ���� �Ӽ� 
//---------------------------------------
class cltDefaultWeaponInfo{
private:
	SI32 siAttackType;			// ���� Ÿ�� (ATTACKTYPE_SWORD..) 
	SI32 siAttackRange;			// �����Ÿ� ���� 

	SI32 siDefaultMinDamage;
	SI32 siDefaultMaxDamage;

	SI32 siDefaultAC;

public:
	cltDefaultWeaponInfo();

	void Set(SI32 attacktype, SI32 range, SI32 mindamage, SI32 maxdamage, SI32 ac);
	void Set(cltDefaultWeaponInfo* pclinfo);

	SI32 GetAttackType() const;
	SI32 GetAttackRange() const;

	SI32 GetDefaultMinDamage() const;
	SI32 GetDefaultMaxDamage() const;

	SI32 GetDefaultAC() const;
};

//-------------------------------------
// KindInfo�� ��°��� ���� 
//-------------------------------------
class cltKIDrawInfo{
public:
	SI32 siPortraitFont;
	SI32 siHeadNameFont;				// �Ӹ� ���� �ߴ� �̸�. (NPC)	
	SI32 siBottomIndent;        	
	SI32 siXsizePercent,  siYsizePercent;
	SI16 siTransparentMode;
	bool bHideShadow;
	SI08 siAlphaValue;

	cltKIDrawInfo();

	void Set(SI32 portrait, SI32 headnamefont, SI32 bottomindent,
			 SI32 xpercent, SI32 ypercent, SI32 transparentmode,bool hideshadow = false ,SI08 alphavalue = 0 );
};

//--------------------------------------------
// ȿ���� ����. 
//--------------------------------------------
class cltKIEffectInfo{
public:
	SI32	siHitEffect;			// �ǰݽ� ����Ʈ. (��..) 
	SI32	siAttackEffect;			// ���ݽ� ����Ʈ. (����... )
	SI32	siAttackEffect1;		// ���ݽ� ����Ʈ. (��������~��)
	SI32	siDyingEffect;			// ����� ����Ʈ. (�ƾ�..) 
	SI32	siSelectEffect1;			// ���ý� ����Ʈ. 
	SI32	siSelectEffect2;			// ���ý� ����Ʈ. 
	SI32	siSelectEffect3;			// ���ý� ����Ʈ. 

	cltKIEffectInfo();

	void Set(SI32 hiteffect, SI32 attackeffect, SI32 attackeffect1, SI32 dyingeffect, SI32 selecteffect1, SI32 selecteffect2, SI32 selecteffect3);
	void Set(cltKIEffectInfo* pclinfo);
    
	SI32 GetRandomeSelectEffect();
};

#define MAX_NPC_TEXT_NUM	5
//--------------------------------------
// ����� NPC ���
//--------------------------------------
class cltWarChatInfo{
public:
	SI32 siWinChatNum;
	SI32 siChatNum;

#ifdef _SAFE_MEMORY
	NSafeTArray<TCHAR*, MAX_NPC_TEXT_NUM>	pszWarTextWin;
	NSafeTArray<TCHAR*, MAX_NPC_TEXT_NUM>	pszWarText;
#else
	TCHAR* pszWarTextWin[MAX_NPC_TEXT_NUM];
	TCHAR* pszWarText[MAX_NPC_TEXT_NUM];
#endif

	SI32 siMapindex;

	cltWarChatInfo();
	~cltWarChatInfo();

	void AddWin(TCHAR* ptext,SI32 mapindex);
	void Add(TCHAR* ptext,SI32 mapindex);
};

//--------------------------------------
// NPC ��� 
//--------------------------------------

class cltKindChatInfo{
public:
	SI32 siChatNum;
#ifdef _SAFE_MEMORY
	NSafeTArray<TCHAR*, MAX_NPC_TEXT_NUM>	pszRandText;
#else
	TCHAR* pszRandText[MAX_NPC_TEXT_NUM];
#endif

	cltKindChatInfo();
	~cltKindChatInfo();

	void Add(TCHAR* ptext);
};


//---------------------------------------
//  Kind ��� ����. 
//---------------------------------------
class cltKindHireCondition{
public:
	GMONEY	siBasicMoney;			// ��� �ּ� ���. 
	SI32	siMinVillageLevel;		// ��� �ּ� ���� ���� 

	cltKindHireCondition();

	void Init();
	void Init(GMONEY money, SI32 villagelevel);

	void Set(cltKindHireCondition* pclinfo);
};

//-----------------------------------------------
// �� ������ �Ӽ�
//----------------------------------------------
class cltCharElemental
{
private:
	SI32 siFire; // ��
	SI32 siWater; // ��
	SI32 siLand; // ��
	SI32 siWind; // �ٶ�
	SI32 siNature; // ����
	SI32 siFireA;
	SI32 siWaterA;
	SI32 siLandA;
	SI32 siWindA;

public:



	void Init()
	{
		siFire = 0 ;
		siWater = 0 ;
		siLand = 0 ;
		siWind = 0 ;
		siNature = 0 ;
		siFireA = 0;
		siWaterA = 0;
		siLandA = 0;
		siWindA = 0 ;
	}

	SI32 GetFire(){return siFire;}
	SI32 GetWater(){return siWater;}
	SI32 GetLand(){return siLand;}
	SI32 GetWind(){return siWind;}
	SI32 GetNature(){return siNature;}
	SI32 GetFireA(){return siFireA;}
	SI32 GetWaterA(){return siWaterA;}
	SI32 GetLandA(){return siLandA;}
	SI32 GetWindA(){return siWindA;}



	void Set(SI32 fire,SI32 water,SI32 land,SI32 wind,SI32 nature, SI32 fireA,SI32 waterA,SI32 landA ,SI32 windA)
	{
		siFire = fire;
		siWater = water;
		siLand = land ;
		siWind = wind ;
		siNature = nature ;
		siFireA = fireA;
		siWaterA = waterA;
		siLandA = landA ;
		siWindA = windA ;

	}
	void Set(cltCharElemental*pclinfo)
	{
		siFire = pclinfo->GetFire();
		siWater = pclinfo->GetWater();
		siLand = pclinfo->GetLand();
		siWind = pclinfo->GetWind();
		siNature = pclinfo->GetNature();
		siFireA = pclinfo->GetFireA();
		siWaterA = pclinfo->GetWaterA();
		siLandA = pclinfo->GetLandA();
		siWindA = pclinfo->GetWindA();
	}
};

//---------------------------------------
// cltKindInfo
//---------------------------------------
class cltKindInfo 
{
private:
	TCHAR 					szName[MAX_KIND_NAME_LENGTH];
	
public:
	SI32					siDollUnique;				// �� ĳ���͸� ��ȯ�� �� �ִ� ���� �������� ����ũ. 
	TCHAR					szCode[MAX_KIND_NAME_LENGTH];

	SI32					siPreferenceCharNum;
	SI32					siKindLifeTime;

	SI32					siDefaultCountry; // ���ϴ� ���� �ڵ� . ��ȯ���� �� PC�� ����Ѵ�.

	cltBasicAbility				clBA;				// �� ĳ���Ͱ� ������ �� �⺻ �ɷ�ġ.(���� ���� �Ǵ� ������)  
	cltBasicParametaBox			clBPB;				// �� ĳ���Ͱ� ������ �� �⺻ �ɷ�ġ.(�ѹ� �������� ������� �ʴ� ������)  
	cltKindItemProbabilitySet	clItemPbtSet;		// �������� ���� Ȯ�� 
	cltDefaultWeaponInfo		clDefaultWeaponInfo;// ����Ʈ ���� ����. 
	cltKIDrawInfo				clKIDrawInfo;		//��°��� ����. 
	cltKIEffectInfo				clKIEffectInfo;		// ���� ����Ʈ ����. 	
	cltKindHireCondition		clHireCond;			// ���������� ��� ����. 
	cltBossItemInfo				clBossItemInfo;		// ���� ĳ������ ������ ����. 
	//cltAtkTypeTolerance			clAtkTypeTolerance; // ���⿡ ���� ����

	SI32 					siMoveSpeed;
	SI32					siSize;					// ĳ������ ������. 
	
	SI32					siBlock;
						
	DWORD 					dwAttackInterval;
	SI32					siCriticalRate;		// �ʻ�� Ȯ�� 
	SI32 					siAtb;
	SI32					siServiceAreaAtb;	// ���Ǵ� ���� ���� �Ӽ�

	DWORD 					DefenceAtb;
	SHORT 					VibrateSwitch;

	SHORT 					Exp;				
	SI32					siAggressive;		// ȣ����. 
	SI32					siMagic;			// ����ϴ� ����. 
	SI32					siSkillLevel;		// ��ų���� 
	SI32					siSex;				// ����. (1: ����. ��Ÿ:����.)

	SI32					siSortLevel;		// ��� ����
	SI32					siSummonRank;		// ��ȯ�� ���
	SI32					siMagicLamp;		// �������(��������Ʈ �� ���ͷ����� ��� �ִ� ����)

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SCROLL_SUMMON_PER_KIND>	siSummonScroll;
#else
	SI32					siSummonScroll[MAX_SCROLL_SUMMON_PER_KIND]; // ��ȯ���� �ٸ� ���ִ� ���� �ڵ�
#endif
	
	SI32					siEvolveLevel;		// ��ȭ ����
	SI16					siSummonPortrait;	// ��ȯ�� �������̽� �ʻ�ȭ 
	SI16					siSummonJob;		// ��ȯ���� Ư�� ��� (����,����..)
	SI32					siSubSkillLevel;	// ��ȯ���� Ư�� ��� ��ų ����
	
	BOOL					bSummonMall;		// �����۸����� �Ĵ� ��ȯ��
	BOOL					bSummonTrade;		// ��ȯ�� �ŷ�.<SetSummonEtcInfo()���� > 
	SI32					siSummonStamina;	// ��ȯ���� ���¹̳� (PCK - 08.07.18)
	SI16					siSummonEquip;		// ��ȯ�� ��� ����( 0=��������Ҽ�����, 1=�ٰŸ�, 2=���Ÿ� )

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_ATTACKTYPE_PER_KIND>	siAttackList;
#else
	SI32					siAttackList[MAX_ATTACKTYPE_PER_KIND] ;	// ���� �ִϵ��� Ÿ��
#endif
	SI32					siMaxAttackType;

	cltCharAnimationManager clCharAniManager;

	cltKindChatInfo*		pclChatInfo;			// ä�� ����. 

	cltWarChatInfo*			pclWarChatInfo;			// ����� ä�� ����
	
	cltCharElemental		pclCharElemental;		// ĳ���� �Ӽ� ����
	// ��ȹ ���� 
	SI32		siCaptureLevel;				// ��ȹ�� �ʿ��� ��� ���� 
	SI32		siBasicPbt;
	SI32		siAdvPbt;					// ��ȹ�� 1�� ���Ǵ� ��ȹȮ��. 

	cltKindInfo(TCHAR* szcode, 
				cltKIDrawInfo*				pclKIDrawInfo,
				cltKIEffectInfo*			pcleffectinfo, 
				cltKindHireCondition*		pclhireinfo,
				cltBossItemInfo*			pclBossItemInfo,
			/*	cltAtkTypeTolerance*		pclAtkTypeTolerance,*/
				SI32 movespeed, 
				SI32 sisize,
				SI32 siblock,
				DWORD atb, 
				DWORD ServiceAreaAtb,
				DWORD defenceatb,
				SHORT vibrateswitch, 
				TCHAR* name,
				SI32 countury = 0 );

	~cltKindInfo();


	void IncreasePreferenceCharNum(SI32 lifetime);	

	BOOL SetFile(SI32 Ani, BOOL DirSwitch, TCHAR* FileName,SI32 Font,SI32 Frame,SI32 Instant,
				 SI32 Delay, SI32 atb, SI32 EffectFont ,SI32 transmode = 0 ,SI08 alphavalue = 0 ,
				 bool attacktype = false, SI32 ShadowAni = 0 , SI32 ShadowFont = 0 );
	BOOL SetShadowIndentXY(SI32 anitype , SI32 x , SI32 y);

	SI32 GetAttackType();

	DWORD Add();

	SI32 GetPortraitFont() const;
	SI32 GetBottomIndent() const;
	SI32 GetXsizePercent() const;
	SI32 GetYsizePercent() const;

	const TCHAR*	GetName() const;

	// ������ ������ �м��Ѵ�. 
	bool AnalyzeItemInfo(TCHAR* szitemtext);

	bool IsAtb(SI32 atb);
	bool IsServiceAreaAtb(SI32 saAtb);
	SI32 GetCaptureRate(SI32 skilllevel);				// ��ȹȮ���� ���Ѵ�. 
	
	// ��Ȳ���� ���� ��� 
	bool CanDefulatVillageGod();						// �� ���Ͱ� Defaut ������ �˻��Ѵ�.
	bool CanGodForVillage(SI32 villageunique);			// �� ���Ͱ� ��Ȳ������ �ɼ��ִ��� 
	SI32 GetResidentNumForVillageGod();					// ��Ȳ���� �Ǳ����� �ʿ��� �α��� 
	GMONEY GetMoneyForVillageGod();						// ��Ȳ���� ����ϴµ� �ʿ��� ��� 
	GMONEY GetUpMoneyForVillageGod();						// ��Ȳ���� ���׷��̵� �ϴµ� �ʿ��� ��� 

	// NPC�� ȥ�㸻�� �����Ѵ�. 
	void AddChat(TCHAR* ptext);
	void AddWarWinChat(TCHAR* ptext, SI32 mapindex);
	void AddWarChat(TCHAR* ptext, SI32 mapindex);

	// �����ϰ� ȥ�㸻�� ���Ѵ�. 
	TCHAR* cltKindInfo::GetRandChatText();
	TCHAR* cltKindInfo::GetWarRandChatWinText(SI32 mapindex);
	TCHAR* cltKindInfo::GetWarRandChatText(SI32 mapindex);
};


#define SUMMON_JOB_NULL		0
#define SUMMON_JOB_FISHING	1
#define SUMMON_JOB_FARMING	2
#define SUMMON_JOB_MINING	3
#define MAX_SUMMON_JOB		4


class cltKindSummonJob
{
public:
	TCHAR szJobCode[MAX_SUMMON_JOB][30];
	TCHAR szJobName[MAX_SUMMON_JOB][30];
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SUMMON_JOB>	siJobSkill;
#else
	SI32 siJobSkill[MAX_SUMMON_JOB];
#endif
	SI32 siCount;

	cltKindSummonJob();
	SI32 FindSummonJobFromJobCode(TCHAR *pJobCode);
	TCHAR *FindSummonJobNameFromJob(SI32 siJob);
	SI32 FindSummonJobSkillFromJob(SI32 siJob);
};

// PCK - ��ȯ�� ä�� Ŀ�ǵ� �߰� (08.07.22)
class cltSummonChatCommand
{
public:
	SI32	siChatTextLine;
	SI16	siAniType;
	SI32	siLevel;	// ä�� Ŀ�ǵ带 ��밡���� ��ȯ���� Level,
	SI16	siCharKind;	// ä�� Ŀ�ǵ带 ����ϴ� ��ȯ�� Kind
	
	cltSummonChatCommand()
	{
		siChatTextLine	= 0;
		siAniType		= 0;
		siLevel			= 0;
		siCharKind		= 0;
	}
};

// PCK : /CMT��ɾ�� �������� ���� ���� �߰�
class cltGMCommandKindInfo
{
public:
	cltBasicAbility				clBA;				// �� ĳ���Ͱ� ������ �� �⺻ �ɷ�ġ.(���� ���� �Ǵ� ������)  
	cltDefaultWeaponInfo		clDefaultWeaponInfo;// ����Ʈ ���� ����. 

	DWORD 					dwAttackInterval;
	SI32					siCriticalRate;		// �ʻ�� Ȯ�� 
	SI32					siAggressive;		// ȣ����. 

	cltCharElemental		clCharElemental;	// ĳ���� �Ӽ� ����
};

//------------------------------------------
// cltKindInfoSet
//------------------------------------------
class cltKindInfoSet
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltKindInfo*, MAX_KINDINFO_NUMBER>	pclKI;

	NSafeTArray<cltKindInfo*, MAX_KINDINFO_NUMBER>	pclSummonKI;	//[����]��ȯ�� ���� �и�. => 2008-6-18

	NSafeTArray<cltSummonChatCommand*, MAX_SUMMON_CHATCOMMANDNUMBER>	pclSummonChatCommand;	// [���] ��ȯ�� ä�� Ŀ�ǵ� �߰� (08.07.22)

	NSafeTArray<cltGMCommandKindInfo*, MAX_KINDINFO_NUMBER>	pclGMCommandKindInfo;		// [���] /CMT��ɾ�� ����� ���� ����
#else
	cltKindInfo* pclKI[MAX_KINDINFO_NUMBER];

	cltKindInfo* pclSummonKI[MAX_KINDINFO_NUMBER];					//[����]��ȯ�� ���� �и�. => 2008-6-18

	cltSummonChatCommand*	pclSummonChatCommand[MAX_SUMMON_CHATCOMMANDNUMBER];	// [���] ��ȯ�� ä�� Ŀ�ǵ� �߰� (08.07.22)

	cltGMCommandKindInfo*	pclGMCommandKindInfo[MAX_KINDINFO_NUMBER];		// [���] /CMT��ɾ�� ����� ���� ����
#endif

	cltKindSummonJob	clSummonJob;		// ��ȯ���� �ΰ����� 
	cltKindInfoSet();
	~cltKindInfoSet();

	//------------------------------------
	// ���ӿ� ���Ǵ� Block������ ��Ÿ����
	//------------------------------------
	SHORT BasicBlock		;
	SHORT ShallowWaterBlock	;
	SHORT DeepWaterBlock	;

	bool IsValidKind(SI32 kind);
	
	void AddCharKindInfoSetFromFile();

	SI32 FindKindFromName(TCHAR* npcname);							// NPC �̸��� �ٰŷ� Kind�� ���Ѵ�. 
	SI32 FindKindFromCode(TCHAR* npccode);							// NPC Code��  �ٰŷ� Kind�� ���Ѵ�. 
	void SetCharAttackInfo(TCHAR* datafilename);						// ĳ������ ���� �Ӽ��� �����Ѵ�.
	void SetCharEtcInfo(TCHAR * datafilename);						// ĳ������ ��Ÿ �Ӽ��� �����Ѵ�. - sortlevel , etc...
	void GetCharAttackInfo( SI32 siKind, TCHAR *pBuffer, SI16 txtSize );			// ĳ������ ������ ���� ���� �Ӽ��� text�� ���´�.	
	void SetCharItemInfo(TCHAR* datafilename);						// ĳ������ �������� �����Ѵ�. 

	// PCK - ��ȯ�� ä�� Ŀ�ǵ� �߰� (08.07.22)
	void SetSummonChatCommand();

	//[����] ��ȯ�� ���̺� �и�. => 2008-6-
	void SetSummonEtcInfo(TCHAR* datafilename);
	void SetSummonAttackInfo(TCHAR* datafilename);
	//void GetCharItemInfo( SI32 siKind, TCHAR *pBuffer );			// ĳ������ ������ ���� �������� text�� ���´�.

	SI32 GetSortLevel(SI32 kind);									// ���� ��� ����
	SI32 GetSubSkillLevel(SI32 kind,SI32 skill);					// ��ȯ���� ���� ��ų

	bool GetItemMonsterExplain(SI32 itemunique, TCHAR* explaintext, SI16 txtSize);	// Ư�� �������� �ִ� ������ ������ ���´�. 
	bool GetItemMonsterExplain(SI32 itemunique, cltDropItem *dropitem, SI32 *siCount);

	bool GetItemFromKindExplain(SI32 kind, TCHAR* explaintext, SI16 txtSize );							// Ư�� ĳ���Ͱ� �ִ� �������� ������ ���´�.
	bool GetItemFromKindExplain(SI32 kind, cltDropItem *dropitem, SI32 *siCount);		// Ư�� ĳ���Ͱ� �ִ� �������� ������ ���´�.
	
	const TCHAR* GetName(SI32 kind);				// kind�� �ٰŷ� �̸��� ���´�. 
	void IncreasePreferenceChar( SI32 kind, SI32 lifetime );
	void ReadPreferenceCharData(TCHAR * filename);
	void WritePreferenceCharData(_SYSTEMTIME sTime);
	void SetDollInfo();							// ĳ������ ��ȯ �������� �����Ѵ�. 
	SI32 GetDefaultVillageGod();				// �⺻ ��Ȳ���� ���´�.
	SI32 GetDefaultCastle();					// �⺻ ������  ���´�.
	bool GetDailyQuestKindInfo(SI32* pkind, SI32*pbattlepower, SI32* pexp);			// ���� ����Ʈ ��� ���Ϳ� �������� �����ϰ� ���Ѵ�. 
	bool GetDailyQuest2KindInfo(SI32* pkind, SI32*pbattlepower, SI32* pexp);		// ���� ����Ʈ2 ��� ���Ϳ� �������� �����ϰ� ���Ѵ�.
	
	GMONEY GetHireBasicMoney(SI32 kind);			// ��� �⺻ ��� ȹ��. 
	SI32 GetHireVillageLevel(SI32 kind);			// ��� ���� ���� ����
	bool FindGoodMonsterForSpecialQuest(SI32 level, SI32* pkind, SI32* pmonnum, cltQuestRewardInfo* pclrewardinfo);	// Ư�� �ӹ��� ��ɿ����� ������ ���͸� ���Ѵ�. 
	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	bool FindGoodMonsterForHappyBeanQuest(SI32 level, SI32* pkind, SI32* pmonnum, cltQuestRewardInfo* pclrewardinfo);	// Ư�� �ӹ��� ��ɿ����� ������ ���͸� ���Ѵ�. 

	// 2010�ų��̺�Ʈ.
	bool FindGoodMonsterForRemoveUnLuckStatusQuest( SI32 level, SI32* pkind, SI32* pmonnum, cltQuestRewardInfo* pclrewardinfo );	// ��� ����Ʈ������ ������ ���͸� ���Ѵ�.
	bool Find_MakeLevel_ItemNum(SI32 level, SI32 makelevel);	// ĳ���� ������ ���������� �´� ����, ��� �� ���� ������ ���Ѵ�.

	void DeleteIfNotUse(DWORD curclock);			// ������ �ʴ� ������ �����Ѵ�.
	bool IsSummonFromRank(SI32 rank);				// �־��� ��ũ�� �ش��ϴ� ��ȯ���� �����ϳ�? �ٸ� ��ȯ������ ��쿣 �������� �ʴ´�

	bool GetNPCImageFileAndFont(SI32 siKind, TCHAR* pszFileName, SI32 siLen, SI32* siFont);
	bool GetNPCImageFileAndFontsmall(SI32 siKind, TCHAR* pszFileName, SI32 siLen, SI32* siFont);

	SI16 GetAnitypeFromText(TCHAR* pszText, SI16 siKind, SI16 siLevel);
	SI32 GetTextMgrCanSummonChatCommand(SI16 siKind, SI16 siLevel);

	bool GetNPCGlobalImageIndexAndFont( IN SI32 siKind, OUT SI32* psiGimgIndex, OUT SI32* psiFont );

	// ���ֵ��̹̼�
	bool FindGoodMonsterForGoonzuDay( SI32 level, SI32* pkind, SI32* pmonnum ); // ��� ����Ʈ������ ������ ���͸� ���Ѵ�.
};

#endif