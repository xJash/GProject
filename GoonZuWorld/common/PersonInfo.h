//---------------------------------
// 2003/7/4 ���°�
//---------------------------------

#ifndef _PERSONINFO_H
#define _PERSONINFO_H

//-------------------------------
// Common
//-------------------------------
#include "Quest\Quest.h"
#include "Quest/NamingQuest.h"
#include "Char\ParametaBox\ParametaBox.h"
#include "Char\CharCommon\Char-Economyinfo.h"
#include "Skill\Skill.h"
#include "Horse\Horse.h"

#include "Char\CharCommon\Char-Common.h"

//-------------------------------
// CommonLogic
//-------------------------------
#include "../CommonLogic/Bank/Bank.h"
#include "../CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"
#include "../CommonLogic/WorldPassport/WorldPassport.h"

#include "../CommonLogic/MagicMgr/MagicBaseInfo.h"
#include "../CommonLogic/DormancyAccountSystem/DormancySystem.h"
#include "../CommonLogic/DormancyAccountSystem/DormancyInfo.h"

#define MAX_SUMMON_OWN		3							// �ִ�� ������ �ִ� ��ȯ�� ����.
#define MAX_HAVE_SUMMON		8							// �ִ�� ������ �ִ� ��ȯ�� ����.
#define MAX_ELEMENTAL_OWN	3							// �ִ�� ������ �ִ� ���ɼ� ����

enum CHANNELING_USER
{
	CHANNELING_USER_NONE,
	CHANNELING_USER_JAPAN_NDE,
	CHANNELING_USER_JAPAN_HANGAME,
	CHANNELING_USER_JAPAN_GAMEPOT,
	CHANNELING_USER_JAPAN_GAMANIA,
	CHANNELING_USER_JAPAN_NEXON,
	CHANNELING_USER_ENGLISH_NDI,
	CHANNELING_USER_ENGLISH_USA,
};

class cltSummonScroll
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_SCROLL_SUMMON_PER_KIND>	siUnique;
	NSafeTArray<SI16, MAX_SCROLL_SUMMON_PER_KIND>	siPercent;
#else
	SI16 siUnique[MAX_SCROLL_SUMMON_PER_KIND];
	SI16 siPercent[MAX_SCROLL_SUMMON_PER_KIND];
#endif
	
	cltSummonScroll();
	cltSummonScroll(SI16 unique0, SI16 percent0, SI16 unique1, SI16 percent1);

	void Init();
	void Set(cltSummonScroll* pclSummonScroll);
	
	SI16 GetPercent(SI16 scroll);
	BOOL FindUnique(SI16 scroll);
	
	BOOL SetPercent(SI16 scroll, SI16 percent);
	BOOL AddPercent(SI16 scroll, SI16 percent);
	
	SI32 GetScrollRate(cltItemManagerCommon* pclItemManager, SI32 siScrollFunction);
	
	// GetEquipHitRate
	inline SI32 GetScrollHitRate(cltItemManagerCommon* pclItemManager)	
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_UPHITRATE);
	}
	// GetEquipCriticalHitRate
	inline SI32 GetScrollCriticalHitRate(cltItemManagerCommon* pclItemManager)	
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_UPCRITICAL);
	}
	// GetDamageReduceRate
	inline SI32 GetScrollDamageReduceRate(cltItemManagerCommon* pclItemManager)	
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_REDUCEDAMAGE);
	}
	// GetEquipPoisonRate
	inline SI32 GetScrollPoisonRate(cltItemManagerCommon* pclItemManager)	
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_POISON);
	}
	// GetEquipIceRate
	inline SI32 GetScrollIceRate(cltItemManagerCommon* pclItemManager)	
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_ICE);
	}
	// GetEquipDrainRate
	inline SI32 GetScrollDrainRate(cltItemManagerCommon* pclItemManager)
	{
		return GetScrollRate(pclItemManager, SCROLL_UNIQUE_FUNCTION_DRAIN);
	}
	
};

// [����] ��ȯ�� �Ѹ����� ��� ������ ����
class cltSummonItemInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_SHAPE_ITEM >	clEquipItem;	// ��ȯ�� ��� ������
#else
	cltItem		clEquipItem[MAX_SHAPE_ITEM];				// ��ȯ�� ��� ������
#endif

	cltSummonItemInfo()		{ Init(); };
	~cltSummonItemInfo()	{};

	void Set(cltSummonItemInfo* pclSummonItemInfo)
	{
		memcpy ( this, pclSummonItemInfo, sizeof(cltSummonItemInfo) );
	};

	void Init()
	{
		ZeroMemory( this, sizeof(cltSummonItemInfo) );
	};


};

class cltSummon;

class cltSimpleSummon{
public:
	SI16				siKind;						// ��ȯ���� ���� 
	SI16				siLevel;					// ��ȯ���� ����
	SI32				siSummonID;					// ��ȯ��ID
	TCHAR				szName[MAX_SUMMON_NAME];	// �̸�
public:
	cltSimpleSummon();
	cltSimpleSummon(
		SI16 kind,
		SI16 Level,
		SI32 SummonID,				
		TCHAR* pname
	);

	void Init();
	void Set(cltSimpleSummon* pclSimpleSummon);
	void Set(cltSummon* pclSummon);
};

class cltSummon{
public:
	//SI08				siUnique;
	SI08				siStatus;
	SI08				siAttackType;
	SI08				siIdentity;
	SI16				siKind;						// ��ȯ���� ���� 
	SI16				siAttackWearStoneNum;		// ���� ��� ���뼮 ����
	SI16				siDefenseWearStoneNum;		// �� ��� ���뼮 ����
	SI32				siTakeInMinute;
	SI32				siSummonID;					// ��ȯ��ID
	TCHAR				szName[MAX_SUMMON_NAME];	// �̸� 
	SI16				m_siTranformStamina;		// [����] ��ȯ���� ���� ���¹̳�.

	cltPIPInfoCommon	clIP;
	cltSummonScroll		clScroll;
	
public:

	cltSummon();
	cltSummon(
		SI32				SummonID,
		SI16				kind,			
		TCHAR*				pname, 
		SI08				status,		
		SI08				attacktype,	
		SI08				identity, 
		SI32				takeinminute,
		SI16				attackWearStoneNum,
		SI16				defenseWearStoneNum,
		cltPIPInfoCommon*	pclip,  
		cltSummonScroll*	pscroll,
		SI16				_siTranformStamina	);

	void Init();
	void Set( cltSummon* pclSummon );
};

//---------------------------------------------
// ��ȯ���� ������ ���� Ŭ���� 
//---------------------------------------------
class cltSummonInfo
{
public:

	//SI16		siCurrentSummon;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltSummon,			MAX_SUMMON_OWN>		clSummon;
	NSafeTArray<cltSummonItemInfo,	MAX_SUMMON_OWN>		clItemInfo;					// ��ȯ�� ��� ������
	NSafeTArray<cltSimpleSummon,	MAX_HAVE_SUMMON>	clSummonBase;
#else
	cltSummon			clSummon[MAX_SUMMON_OWN];
	cltSummonItemInfo	clItemInfo[MAX_SUMMON_OWN];									// ��ȯ�� ��� ������
	cltSimpleSummon		clSummonBase[MAX_HAVE_SUMMON];
#endif

	SI16			siSelectAutoHeal;
	bool			bAutoHeal;

	bool			m_bIsSummonTranform;												// [����] ��ȯ�� ���� ����.
	SI16			m_siSummonTranformIndex;											// [����] ���� ��ȯ�� �ε���.
	DWORD			m_dwSummonTranformTickCount;										// [����] ���� �� �纯���̳� ȸ���� ���ѽð�.
	
public:

	cltSummonInfo();
	~cltSummonInfo();
	void Init();
	void Set(cltSummonInfo* pclSummoninfo);
	
	BOOL				CanHaveSummon();
	BOOL				GetEmptySummonIndex(SI32 *index);
	BOOL				GetEmptySummonIndexInHouse(SI32 *index); // ��ȯ�� �����ҿ��� ���� Index�� ã�´�
	BOOL				HaveSummon();
	void				SetSummon(SI16 index, cltSummon *pclSummon);
	cltSummon*			GetSummon(SI16 index);
	cltSimpleSummon*	GetSummonBase( SI16 index );
	cltSummon*			GetSummonFromSummonID(SI32 siSummonID);
	cltSimpleSummon*	GetSimpleSummonFromSummonID(SI32 siSummonID);
	void				SummonInit(SI16 index);
	SI08				GetSummonIndexFromSummonID(SI32 siSummonID);
	SI08				GetSummonBaseIndexFromSummonID(SI32 siSummonID);

	bool				IsSummonTranform( SI32 siTranformIndex );
	void				SetIsSummonTranform( bool _bIsSummonTranform );
	
	SI16				GetSummonTranformIndex(void);
	void				SetSummonTranformIndex(SI16 _siSummonTranformIndex);
	
	bool				IsSummonTranformTickCount( void );
	void				SetSummonTranformTickCount( void );
	void				EndSummonTranformTickCount( void );



	//-------------------------------------------
	// ��ȯ�� ������ ����
	//-------------------------------------------
	
	// �ش� ��ȯ���� ��� �������� �ϳ��� ���� �ִ��� �˻�
	BOOL		IsHaveEquipItem( SI16 siSummonIndex );
	// �ش� ��ȯ���� ������ ��ġ�� �������� Set�Ѵ�
	void		SetSummonEquipItem( SI16 siSummonIndex, SI16 siItemPos, cltItem* pclItem );
	// �ش� ��ȯ���� ������ ��ġ�� �������� Get�Ѵ�
	cltItem*	GetSummonEquipItem( SI16 siSummonIndex, SI16 siItemPos );
	// �ش� ��ȯ���� �����۹迭 ���θ� Get�Ѵ�.
	cltItem*	GetSummonEquipItemList( SI16 siSummonIndex );

	// �ش� ������ ����ũ�� ��� �ִ��� �˻�
	BOOL		IsHaveEquipItemFromItemUnique( SI16 siSummonIndex, SI32 siItemUnique );
	// �ش� ������ ����ũ�� ��� �ִ���
	SI32		GetHaveItemNumFromItemUnique( SI16 siSummonIndex, SI32 siItemUnique );
	// �ش� �������� ��� �ִ���
	SI32		GetItemPosInEquip( SI16 siSummonIndex, SI32 siItemUnique );
	// ����� �ߵ��� ����� ���Ѵ�(�ٰŸ� ���⸸)
	SI32		GetSummonEquipPoisonRate( SI16 siSummonIndex, cltItemManagerCommon* pclItemManager, SI16 siActiveweapon);
	// ����� �����Ѽ�Ȯ�� ����� ���Ѵ�(���Ÿ� ���⸸)
	SI32		GetSummonEquipIceRate( SI16 siSummonIndex, cltItemManagerCommon* pclItemManager, SI16 siActiveweapon);
	// ����� ����Ȯ�� ����� ���Ѵ�(�Ź߸�)
	SI32		GetSummonEquipDrainRate( SI16 siSummonIndex, cltItemManagerCommon* pclItemManager,SI16 siActive);
};

//***************************************************************************************************
//
// Class Name 		: cltPersonInfoOne
//
// Last Modified 	: 2007 / 03 / 08
// Created		 	: �豤��
//
// Function			: cltPersonInfo ������ ����1
//
//***************************************************************************************************
class cltPersonInfoOne
{
public:

	cltPBasicInfo			clBI;				// ĳ������ ���� �⺻�� �Ǵ� ����. 
	cltPIPInfo				clIP;				// �ٽ����� ����. 	
	cltPSkillInfo			clCharSkill;		// ��ų�� ���õ� ������ ����. 
//	cltPItemInfo			clCharItem;			// ������ ���� ��� ���õ� ����. 
	cltSimpleRank			clCharRank;			// �źа��� ����. 
	cltPItemMallItemInfo	clItemMall;			// ������ �� ������ ����.

	//-------------------------------
	// ���� ���� ������ 
	//-------------------------------
	cltBankAccount			clBank;
	cltPStockInfo			clStock;
	cltPMarketInfo			clMarket;
	cltCharRealEstate		clRealEstate;
	cltWorldMoneyAccount	clWorldMoney;

	//------------------------------
	// �ǰ� ����. 
	//------------------------------
	cltHealthInfo		clHealthInfo;

	//----------------------------
	// �� ���� ����. 
	//----------------------------
	cltPersonHorseInfo clHorseInfo;

	//----------------------------
	//����Ʈ ���� ����. 
	//----------------------------
	cltPQuestInfo clQuestInfo;

	//---------------------------
	// ���� ���� ����
	//---------------------------
	cltGuiltyInfo	clGuiltyInfo;
	
	//--------------------------
	// ���Ӽ��� ����. 
	//--------------------------
	cltPCharOptionInfo	clCharOption;

	//--------------------------
	// DailyQuest ����. 
	//--------------------------
	cltPDailyQuestInfo clDailyQuestInfo;

	//--------------------------
	// DailyQuest2 ����. 
	//--------------------------
	cltPDailyQuest2Info clDailyQuest2Info;
	//--------------------------
	// DailyQuest3 ����. 
	//--------------------------
	cltPDailyQuest3Info clDailyQuest3Info;

	
	//--------------------------
	// ���� ���� ����
	//--------------------------
	cltWorldOrder clWorldOrder;

	UI16 uiGachaCnt;

	//--------------------------
	// ĳ���� ��Ī
	//--------------------------
	cltPersonNaming	clPersonNaming;

	//--------------------------
	// �������� ����
	//--------------------------
	cltWorldPassport clWorldPassport;

	cltPersonInfoOne()
	{
		uiGachaCnt = 0;
	}

	~cltPersonInfoOne()
	{
	}

	void Set(cltPersonInfoOne* pclinfo)
	{
		clBI.Set(&pclinfo->clBI);
		clIP.Set(&pclinfo->clIP);
		clCharSkill.Set(&pclinfo->clCharSkill);
		clCharRank.Set(&pclinfo->clCharRank);
		clBank.Set(&pclinfo->clBank);
		clStock.Set(&pclinfo->clStock);

		clMarket.Set(&pclinfo->clMarket);
		clRealEstate.Set(&pclinfo->clRealEstate);
		clWorldMoney.Set(&pclinfo->clWorldMoney);

		clHealthInfo.Set(&pclinfo->clHealthInfo);
		clHorseInfo.Set(&pclinfo->clHorseInfo);
		clQuestInfo.Set(&pclinfo->clQuestInfo);
		clGuiltyInfo.Set(&pclinfo->clGuiltyInfo);
		clCharOption.Set(&pclinfo->clCharOption);
		clDailyQuestInfo.Set(&pclinfo->clDailyQuestInfo);
		clDailyQuest2Info.Set(&pclinfo->clDailyQuest2Info);
		clDailyQuest3Info.Set(&pclinfo->clDailyQuest3Info);


		//clSummonInfo.Set(&pclinfo->clSummonInfo);
		clWorldOrder.Set(&pclinfo->clWorldOrder);
		uiGachaCnt = pclinfo->uiGachaCnt;
		clPersonNaming.Set(&pclinfo->clPersonNaming );

		clWorldPassport.Set( &pclinfo->clWorldPassport );
	}
};

//***************************************************************************************************
//
// Class Name 		: cltPersonInfoTwo
//
// Last Modified 	: 2007 / 03 / 08
// Created		 	: �豤��
//
// Function			: cltPersonInfo ������ ����2 ���ο� ���� �߰��� ���⿡ �սô�.
//					  cltPersonInfo.SetTwo()-> �ڿ� �־��־�� �մϴ�. 
//
//***************************************************************************************************
class cltPersonInfoTwo
{
public:
	//------------------------------
	// ������ ����. 
	//------------------------------
	cltPItemInfo			clCharItem;			// ������ ���� ��� ���õ� ����. 
	//--------------------------
	// ��ȯ�� ����. 
	//--------------------------
	cltSummonInfo		clSummonInfo;

	cltPersonInfoTwo()
	{
	}

	~cltPersonInfoTwo()
	{
	}

	void Set(cltPersonInfoTwo* pclinfo)
	{
		clCharItem.Set(&pclinfo->clCharItem);
		clSummonInfo.Set(&pclinfo->clSummonInfo);
	}
};

//-----------------------------------------------
// ����� ĳ������ ������ ��� ���� Ŭ���� 
// �� Ŭ������ DB�� ����Ǵ� ĳ���� ������ �ȴ�. 
//------------------------------------------------
class cltCharServer;
class cltPersonInfo
{
public:

	cltPBasicInfo			clBI;				// ĳ������ ���� �⺻�� �Ǵ� ����. 
	cltPIPInfo				clIP;				// �ٽ����� ����. 	
	cltPSkillInfo			clCharSkill;		// ��ų�� ���õ� ������ ����. 
	cltPItemInfo			clCharItem;			// ������ ���� ��� ���õ� ����. 

	//[�߰� : Ȳ���� 2008. 1. 29 => ���� ���ڿ� ���������� ������ ����.]
//	cltSpaceBox				clSpaceBoxItem;		// ������ ���� ��� ���õ� ����.
//	cltTreasureBox			clTreasureBoxItem;	// ������ ���� ��� ���õ� ����.

	cltSimpleRank			clCharRank;			// �źа��� ����. 
	cltPItemMallItemInfo	clItemMall;			// ������ �� ������ ����.

	//-------------------------------
	// ���� ���� ������ 
	//-------------------------------
	cltBankAccount			clBank;
	cltPStockInfo			clStock;
	cltPMarketInfo			clMarket;
	cltCharRealEstate		clRealEstate;
	cltWorldMoneyAccount	clWorldMoney;

	//------------------------------
	// �ǰ� ����. 
	//------------------------------
	cltHealthInfo		clHealthInfo;

	//----------------------------
	// �� ���� ����. 
	//----------------------------
	cltPersonHorseInfo clHorseInfo;

	//----------------------------
	//����Ʈ ���� ����. 
	//----------------------------
	cltPQuestInfo clQuestInfo;

	//---------------------------
	// ���� ���� ����
	//---------------------------
	cltGuiltyInfo	clGuiltyInfo;

	//--------------------------
	// ���Ӽ��� ����. 
	//--------------------------
	cltPCharOptionInfo	clCharOption;
	
	//--------------------------
	// DailyQuest ����. 
	//--------------------------
	cltPDailyQuestInfo clDailyQuestInfo;

	//--------------------------
	// DailyQuest2 ����. 
	//--------------------------
	cltPDailyQuest2Info clDailyQuest2Info;

	//--------------------------
	// DailyQuest3 ����. 
	//--------------------------
	cltPDailyQuest3Info clDailyQuest3Info;

	//--------------------------
	// ��ȯ�� ����. 
	//--------------------------
	cltSummonInfo		clSummonInfo;
	
	//--------------------------
	// ���� ���� ����
	//--------------------------
	cltWorldOrder clWorldOrder;
	
	UI16 uiGachaCnt;

	//--------------------------
	// ĳ���� ��Ī
	//--------------------------
	cltPersonNaming	clPersonNaming;

	//--------------------------
	// �������� ����
	//--------------------------
	cltWorldPassport	clWorldPassport;

	//--------------------------
	// �޸� ���� �ý��� ����
	//--------------------------
	CDormancyInfo	clDormancyInfo;


	cltPersonInfo()
	{
		uiGachaCnt = 0;
	}

	~cltPersonInfo()
	{
	}

	void Set(cltPersonInfo* pclinfo)
	{
		clBI.Set(&pclinfo->clBI);
		clIP.Set(&pclinfo->clIP);
		clCharSkill.Set(&pclinfo->clCharSkill);
		clCharItem.Set(&pclinfo->clCharItem);
		clCharRank.Set(&pclinfo->clCharRank);
		clBank.Set(&pclinfo->clBank);
		clStock.Set(&pclinfo->clStock);
		clMarket.Set(&pclinfo->clMarket);
		clRealEstate.Set(&pclinfo->clRealEstate);
		clWorldMoney.Set(&pclinfo->clWorldMoney);

		clHealthInfo.Set(&pclinfo->clHealthInfo);
		clHorseInfo.Set(&pclinfo->clHorseInfo);
		clQuestInfo.Set(&pclinfo->clQuestInfo);
		clGuiltyInfo.Set(&pclinfo->clGuiltyInfo);
		clCharOption.Set(&pclinfo->clCharOption);
		clDailyQuestInfo.Set(&pclinfo->clDailyQuestInfo);
		clDailyQuest2Info.Set(&pclinfo->clDailyQuest2Info);
		clDailyQuest3Info.Set(&pclinfo->clDailyQuest3Info);
		clSummonInfo.Set(&pclinfo->clSummonInfo);
		clWorldOrder.Set(&pclinfo->clWorldOrder);
		uiGachaCnt = pclinfo->uiGachaCnt;
		clPersonNaming.Set(&pclinfo->clPersonNaming);

		clWorldPassport.Set( &pclinfo->clWorldPassport );
		clDormancyInfo.Set( &pclinfo->clDormancyInfo);
	}

	void SetPersonID(SI32 id)
	{
		clBI.clPerson.siPersonID = id;
	}

	SI32 GetPersonID() const
	{
		return clBI.clPerson.siPersonID;
	}

	// cltPersonInfoOne�� ������ �����Ѵ�
	void SetOne(cltPersonInfoOne* pclinfo)
	{
		clBI.Set(&pclinfo->clBI);
		clIP.Set(&pclinfo->clIP);
		clCharSkill.Set(&pclinfo->clCharSkill);
		clCharRank.Set(&pclinfo->clCharRank);
		clBank.Set(&pclinfo->clBank);
		clStock.Set(&pclinfo->clStock);
		clMarket.Set(&pclinfo->clMarket);
		clRealEstate.Set(&pclinfo->clRealEstate);
		clWorldMoney.Set(&pclinfo->clWorldMoney);

		clHealthInfo.Set(&pclinfo->clHealthInfo);
		clHorseInfo.Set(&pclinfo->clHorseInfo);
		clQuestInfo.Set(&pclinfo->clQuestInfo);
		clGuiltyInfo.Set(&pclinfo->clGuiltyInfo);
		clCharOption.Set(&pclinfo->clCharOption);
		clDailyQuestInfo.Set(&pclinfo->clDailyQuestInfo);
		clDailyQuest2Info.Set(&pclinfo->clDailyQuest2Info);
		clDailyQuest3Info.Set(&pclinfo->clDailyQuest3Info);
		clWorldOrder.Set(&pclinfo->clWorldOrder);
		uiGachaCnt = pclinfo->uiGachaCnt;
		clPersonNaming.Set(&pclinfo->clPersonNaming);

		clWorldPassport.Set( &pclinfo->clWorldPassport );
	}

	// cltPersonInfoTwo�� ������ �����Ѵ�
	void SetTwo(cltPersonInfoTwo* pclinfo)
	{
		clCharItem.Set(&pclinfo->clCharItem);
		clSummonInfo.Set(&pclinfo->clSummonInfo);
	}
};



//-------------------------------------------
// ���ΰ� ĳ���� ���� ����� ������. 
//-------------------------------------------
class cltHeroDataBackup{
public:
	cltPersonInfo			clMyCharPersonInfo;
	SI32					siWarEnemyKillNumber;// ���￡�� óġ�� ���� ���� ���. 
	SI32					siWarKilledNumber;		//���￡�� ���� ���� ���. 
	SI32					siBlackArmyWarMapIndex;
	SI32					siBlackWarEnemyKillNumber;	// ���Ǳ��� ���￡�� óġ�� ���� ���� ���. 
	SI32					siBlackWarKilledNumber;		// ���Ǳ��� ���￡�� ���� ���� ���. 

	//[�߰� : Ȳ���� 2008. 1. 28 => ���� ���� ���� ���� ���]
	SI32					siBlackWarEnemyKillScore;			// [Ȳ���� 2008. 1. 28 => ���￡�� óġ�� ���� ����.]
	SI32					siBlackWarEnemyKillVillageScore;	// [Ȳ���� 2008. 1. 28 => ���￡�� óġ�� ���� �ش��ϴ� �� ���� ����.]

	bool					bStartMakeItemSwitch;
	DWORD					dwStartMakeItemClock;
	DWORD					dwDelayMakeItemClock;
	
	SI32                    siOldActiveClothes;
	SI32                    siOldActiveHat;
	SI32					siOldActiveWeapon;

	SI32					siOldCurrnetMagic;
	SI08					siOldCurrnetMagicCastType;

	SI32					siOldBasicMoveSpeed;
	SI32					siOldShoesMoveSpeed;
	SI32					siOldTotalMoveSpeed;
	SI32					siOldGivenMoveSpeed;	// �����κ��� �־��� �̵� �ӵ�. 

/*
	SI32					siGuildOldStr;			// ��� ��
	SI32					siGuildOldDex;			// ��� ����
	SI32					siGuildOldMag;			// ��� ����
	SI32					siGuildOldVit;			// ��� ü��
	SI32					siGuildOldHnd;			// ��� ������
	SI32					siGuildOldLuck;			// ��� ��
*/
	cltBasicAbility			clGuildOldBA;

	
	cltInnerStatusInfo		clOldInnerStatus;
	cltCharAddStatusInfo	clOldAddInfo;
	cltPItemMallItemInfo	clOldItemMall;
//	cltPLimitDateItemInfo	clOldLimitDateItemInfo;

	cltSpaceBox				clSpaceBoxItem;		// ������ ���� ��� ���õ� ����.
	cltTreasureBox			clTreasureBoxItem;	// ������ ���� ��� ���õ� ����.

	CNMagicBufMgr			clOldMagicBufMgr;	// ���� ���� ����

	SYSTEMTIME				stMuteTime;

	// �߷�Ÿ�ε��� ���� ����
	cltValentineWarInfo		clValentinewarinfo;

	cltPVP_LeagueInfo		clPVP_LeagueInfo;
	
	cltHeroDataBackup();
	~cltHeroDataBackup();
	
};

SI32 GetChannelingUser(TCHAR* pszID);

#endif


