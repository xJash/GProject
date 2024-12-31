//---------------------------------
// 2003/10/16 ���°�
//---------------------------------
#ifndef _CHARSERVER_H
#define _CHARSERVER_H

#include "Char\CharCommon\Char-Common.h"
#include "../Client/MiniGame/Roulette/RouletteLogic.h"

#include "../../Agriculture/Agriculture.h"

#include "../../NLib/NUpdateTimer.h"

#define CHAT_INPUT_MIN_CLOCK	400				// ä�� �Է��� �ּ� ����. 

#define CHARMODE_NONE				0
#define CHARMODE_INSTANCEMAP		1			// �ν��Ͻ� ������ ĳ����
#define CHARMODE_BLACKWAR			2			// ���Ǳ��� ����� ĳ����. 
#define CHARMODE_SUMMON_EGG2		3			// ����������ȯ��2�� ��ȯ�� ĳ����
#define CHARMODE_KINGGURI			4			// ��ձ�����
#define CHARMODE_SANTARACCOON		5			// [�߰� : Ȳ���� 2007. 11. 29 ��Ÿ���� ��� �߰�.]
#define CHARMODE_TREASUREEVENT		6			// // ����ã�� �̺�Ʈ ����NPC ��������NPC�� �׾�����.
#define CHARMODE_BATTLEROYAL		7			// ��Ʋ�ξ��� ĳ����

#define KILLEDMODE_BLACKWAR			1			// ���Ǳ��� �̺�Ʈ���� ���. 
#define KILLEDMODE_VILLAGEWAR		2			// ���������� ���. 
#define KILLEDMODE_BEGINNERMAP		3			// �ʺ��� ����� ���. 
#define KILLEDMODE_VILLAGEHUNT		4			// �Ұ��縮���� ���. 
#define KILLEDMODE_BLACKARMY		5			// ���Ǳ��� �̺�Ʈ���� ���
#define KILLEDMODE_MOFUMOFUEVENT	6			// ���ĸ��� �̺�Ʈ���� ���
#define KILLEDMODE_GUILDWAR			7			// ��������� ���
#define KILLEDMODE_PVP				8			// PVP���� ���
#define KILLEDMODE_INSTANCEMAP		9			// �ν��Ͻ��ʿ��� ���
#define KILLEDMODE_GOTOSAFEZONE		10			// ���縮���� ������ �ϴ� ����̴�.
#define KILLEDMODE_BATTLEROYAL		11			// ��Ʋ�ξ⿡�� ���

#define MINING_DECREASEORG_CNT		2
#define FARMING_DECREASEORG_CNT		4

#define MINING_DECREASEORG_AMT		5
#define FARMING_DECREASEORG_AMT		5
#define ANTIDOTES_DECREASEORG_AMT	3			// �ص��� ���� �Ű��� -3 ��ŭ�� ȿ���� �޴´�.

#define REMOVEUNLUCK_QUESTNPC_COUNT	9			// [����] : 2010�ų��̺�Ʈ - ����� ����Ʈ �ִ� npc�� �� ������

#ifdef _TAIWAN
	#define	GAMEGUARD_GAMESTART_CERTIFICATION	2*60+30	// 2�� 30��
	#define GAMEGUARD_CERTIFICATION				1*60	// 1��
#else
	#define	GAMEGUARD_GAMESTART_CERTIFICATION	50	// 50��
	#define GAMEGUARD_CERTIFICATION				25	// 25��
#endif

class cltGameMsgRequest_MakeItemInv;
class DBToolInfo;
class cltSummon;
class cltAccountLetterUnit;
class cltSummonTransformManager;
class cltCharManager;

//-----------------------------------------
// ĳ������ ������Ʈ ����. 
//-----------------------------------------
class cltCharUpdateInfo{
public:
	bool bMode;
	SI32 siPara1;

	cltCharUpdateInfo();
	void Init();
};

//-----------------------------------------
// ĳ������ ���ֹ̼� ���� ���ο� ���� ����Ʈ ����. 
//-----------------------------------------
class cltCharGoonzuDayMissionInfo
{
public:
	UI16 uiYear;			
	UI08 uiMonth;			
	UI08 uiDate;			
	UI16 uiCount;			// �̼� ī��Ʈ

	cltCharGoonzuDayMissionInfo()
	{
		ZeroMemory( this, sizeof(cltCharGoonzuDayMissionInfo) );
	}

	cltCharGoonzuDayMissionInfo(UI16 year, UI08 month, UI08 date, UI16 count)
	{
		ZeroMemory( this, sizeof(cltCharGoonzuDayMissionInfo) );

		uiYear = year;
		uiMonth = month;
		uiDate = date;
		uiCount = count;
	}

	void Clear()
	{
		ZeroMemory( this, sizeof(cltCharGoonzuDayMissionInfo) );
	}
};

//-----------------------------------------
// ���Ǵ� ������ ���� ����. 
//-----------------------------------------
class cltItemReserveUnitInfo{
public:
	SI16 siUnique;
	SI16 siItemNum;
	SI16 siItemPos;
	
	cltItemReserveUnitInfo();
	void Init();
	void Set(cltItemReserveUnitInfo* pclinfo);
};

#define MAX_USEITEM_RESERVE_NUM 128
class cltUseItemReserveInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemReserveUnitInfo, MAX_USEITEM_RESERVE_NUM>	clInfo;
#else
	cltItemReserveUnitInfo clInfo[MAX_USEITEM_RESERVE_NUM];
#endif

	void Init();
	bool Push(SI32 unique, SI32 itemnum, SI32 itempos= -1);
	bool IsReserved();

};

class cltBulletUseReserveInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItemReserveUnitInfo, MAX_USEITEM_RESERVE_NUM>	clInfo;
#else
	cltItemReserveUnitInfo clInfo[MAX_USEITEM_RESERVE_NUM];
#endif

	void Init();
	bool Push(SI32 unique, SI32 itemnum, SI32 itempos);
	bool IsReserved();

};

//-----------------------------------------
// ��ȯ�� ������ �������
//-----------------------------------------
class cltSummonItemReserveUnitInfo{
public:
	SI08 m_siSummonIndex;
	SI16 m_siItemUnique;
	SI16 m_siItemNum;
	SI16 m_siItemPos;

	cltSummonItemReserveUnitInfo();
	cltSummonItemReserveUnitInfo( SI08 siSummonIndex, SI16 siItemUnique, SI16 siItemNum, SI16 siItemPos );
	void Init();
	void Set( cltSummonItemReserveUnitInfo* pclinfo );
	void Set( SI08 siSummonIndex, SI16 siItemUnique, SI16 siItemNum, SI16 siItemPos );

};

class cltSummonBulletUseReserveInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltSummonItemReserveUnitInfo, MAX_USEITEM_RESERVE_NUM>		m_clInfo;
#else
	cltSummonItemReserveUnitInfo m_clInfo[MAX_USEITEM_RESERVE_NUM];
#endif

	cltSummonBulletUseReserveInfo();
	void Init();
	bool Push( SI08 siSummonIndex, SI16 siItemUnique, SI16 siItemNum, SI16 siItemPos );
	bool IsReserved();

};


//---------------------------------------------
// ĳ���Ϳ� ���� ������..
//---------------------------------------------
class cltCharSimpleVary{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<DWORD, MAX_ITEM_PER_PERSON>		dwItemInputReserveClock;
#else
	DWORD	dwItemInputReserveClock[MAX_ITEM_PER_PERSON];	//  ������ �߰��� ���� ���� ����. 
#endif
	bool	bCheckFameLevelSwitch;					// ������ ���� ����. 
	
	bool	bSkillExpUpdateSwitch;							// ��� ����ġ�� ������Ʈ �Ȱ��� �ϳ��� �ִ°�. 
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_SKILL_NUMBER>			SkillUpdateSwitch;
#else
	bool	SkillUpdateSwitch[MAX_SKILL_NUMBER];			// Skill Update (��ų ����ġ�� �ٲ���� �˻�)
#endif

	// ������ Update���� 
	bool	bWasteDurSwitch;								// ������ ���� ��ǰ�� �ϳ��� �ִٸ�. 
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_ITEM_PER_PERSON>		WasteDurUpdateSwitch;
#else
	bool	WasteDurUpdateSwitch[MAX_ITEM_PER_PERSON];
#endif

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	// ������ Update���� 
	bool	bCrystalDurSwitch;								// ������ ���� ��ǰ�� �ϳ��� �ִٸ�. 
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_SHAPE_ITEM>			CrystalDurUpdateSwitch;
#else
	bool	CrystalDurUpdateSwitch[MAX_SHAPE_ITEM];
#endif

	// LEEKH - SummonItem Durability Add
	NSafeTArray<BOOL, MAX_SUMMON_OWN>										bSummonWasteDurSwitch;
	NSafeTArray< NSafeTArray<bool, MAX_ITEM_PER_PERSON>, MAX_SUMMON_OWN>	SummonWasteDurUpdateSwitch;

	DWORD	dwLastHorseActionClock;							// �� ���� �׼��� ���� ������ �ð�. 

	DWORD dwlastCheckCharServerStatusActionClock;
	DWORD dwLastCheckCharServerNPCActionClock;
	DWORD dwlastCheckHorseSpeedQuestClock;
	DWORD dwLastCheckCharServerActionPCClock;
	DWORD dwLastKillClock;		// �ٸ� ĳ���͸� ���������� óġ�� �ð�. (�ڵ���� ������ ���� ��ġ) 
	SI32  siCheckMonsterNum;							// ���� ���� ���� ����(��ũ��)
	DWORD dwRealKillClock;							// ��ũ�� �ð� üũ 
	DWORD dwGuildPointClock;							// ���ӽð� - ��� GP�� ���
	DWORD dwLastGameGuardCheckClock;				// nProtect ���� üũ 
	
	//bool	bDemandAttend;						// �⼮üũ �䱸 �Ͽ�����.

	//-----------------------------------
	// �α����� ��ȣ 
	//-----------------------------------
	bool	bInitProtectSwitch;
	DWORD	dwInitProtectClock;

#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_ITEM_PER_PERSON>		bNoMoveItemSwitch;
#else
	bool	bNoMoveItemSwitch[MAX_ITEM_PER_PERSON];	// ������ ����� ����Ǿ����ϱ� �����̸� �ȵȴ� -  TradeServer ����!
#endif

	cltCharSimpleVary();
	void Init();
};

enum
{
	CHAR_UPDATETIMER_TIMEMETERRATE_DB,
	CHAR_UPDATETIMER_TIMEMETERRATE_CLIENT,
	CHAR_UPDATETIMER_TRANSFORMINFO_CLIENT,
	CHAR_UPDATETIMER_TRANSFORM_TIME_LIMIT,

	CHAR_UPDATETIMER_CRYSTALITEM_DB,
	CHAR_UPDATETIMER_CRYSTALITEMINFO_CLIENT,

	CHAR_UPDATETIMER_TIREDSYSTEM_TIME_LIMIT,

	CHAR_UPDATETIMER_30SECOND,
	CHAR_UPDATETIMER_3SECOND,

	CHAR_UPDATETIMER_BUGCHAR_CHECK,

	//---------------------------------------------
	CHAR_UPDATETIMER_END
};

// �������� �ٶ� ������ �к�/���� ���θ� �����Ѵ�
enum GIVEITEM_SEAL_MODE
{
	GIVEITEM_SEAL_MODE_NONE = 0,	// �ƹ��͵� �ƴ�
	GIVEITEM_SEAL_MODE_SEAL,		// �к��Ѵ�
	GIVEITEM_SEAL_MODE_CANCEL		// �к��� �����Ѵ�
};

//---------------------------------------------
// ĳ���Ϳ� UpdateTimer
//---------------------------------------------
class cltCharUpdateTimer
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<NUpdateTimer, CHAR_UPDATETIMER_END>		m_clTimer;
#else
	NUpdateTimer		m_clTimer[CHAR_UPDATETIMER_END];
#endif

public:
	cltCharUpdateTimer();
	~cltCharUpdateTimer()	{}

	void Init();

	NUpdateTimer& operator [] (SI32 siIndex)
	{
		return m_clTimer[siIndex];
	}
};

#ifdef USE_GAME_GUARD_SERVER

	enum CCAAUTH_STATE
	{
		CCSAUTH_STATE_NONE,
		CCSAUTH_STATE_INIT,
		CCSAUTH_STATE_FIRST_AUTH_SENDED,
		CCSAUTH_STATE_FIRST_AUTH_RECEIVED,
		CCSAUTH_STATE_N_AUTH_SEND,
		CCSAUTH_STATE_N_WAIT_NEXTTIME,
	};

#endif

class cltAgriculture
{
private:
	SI32	m_siVillageUnique[MAX_AGRICULTURE_COUNT];
	UI32	m_uiExpireTime[MAX_AGRICULTURE_COUNT];

	DWORD	m_dwStartAgricultureClock;		// ���� Ȱ�� ���۽ð�
	SI32	m_siCurrentVillageUnique;		// ���� ����Ȱ���� �ϰ� �ִ� ���� ����ũ

public:
	cltAgriculture()
	{
		Init();
	}

	~cltAgriculture()
	{
	}

	void Init()		{		ZeroMemory(this, sizeof(cltAgriculture));		}

	void AddAgriculture( SI32 siVillageUnique, UI32 uiExpireTime );
	void DeleteAgriculture( SI32 siVillageUnique );
	UI32 GetExpireTime( SI32 siVillageUnique );
	bool IsLeaseAgriculture( SI32 siVillageUnique );

	bool StartAgriculture( SI32 siVillageUnique, DWORD dwStartClock );
	bool EndAgriculture( SI32 siVillageUnique );

	SI32  GetCurrentVillageUnique()		{		return m_siCurrentVillageUnique;	}
	DWORD GetStartAgricultureClock()	{		return m_dwStartAgricultureClock;	}

protected:
	SI32 FindVillageUnique( SI32 siVillageUnique );
};

//------------------------------------------
// cltCharServer : Server�� 
//------------------------------------------
class cltCharServer	: public cltCharCommon
{
private:
	DWORD			LastReceveFromClientClock;	// Ŭ���̾�Ʈ�κ��� �޽����� ���� ������ �ð�. 
	DWORD			dwLastCheckAutoFoodClock;	// ���������� �ڵ� ���̱�� üũ �ð�. 

	SI32			NPCGroup;
	cltWarpInfo		clCharWarpInfo;		// �����ؾ� �ϴ°�. 
	SI32			siWarpUnique;		// � ������ ������ �ߴ��� �ĺ���. 	

	bool			bSendSecretNCHarUniqueSwitch;	// ĳ���� �����Ŀ� ��ȣȭŰ�� ĳ���� ����ũ ���� Ŭ���̾�Ʈ�� �������� ����.
	
	SI32			siMagicDelay;					// ���� ���� �ð�. 
	

	cltCharSimpleVary clSimpleVary;

	//----------------------------------------
	// ���� ���� ����. 
	//----------------------------------------
	DWORD			uiLevelInfoUpdateFrame;
	cltLevelInfo	clOldLevelInfo;				// ���� ���� ����. 
	
	DWORD	dwLastVisitVillageClock;			// ���������� ������ �湮�� �ð�. 
	
public:

	//----------------------------------------
	// ���� ����� �����
	//----------------------------------------
#ifdef USE_GAME_GUARD_SERVER
	//cltWrapCCSAuth2	clWarpCSA;

	CCSAuth2		m_clCSA;

	bool			m_bCCSAuthInit;
	SI32			m_siCCSAuthState;

	DWORD			m_dwCCSAuthLastActionTick;

	SI32			m_siCCSAuthCount;

	void CCSAuthInit();
	void CCSAuthClose();

	void CCSCloseClient();

	void CCSReceivedAuth(GG_AUTH_DATA* ggData);

	void CCSAuthRun();

	void CCSAuthWriteProcessLog(TCHAR* pszMsg);
	void CCSAuthWriteErrorLog(TCHAR* pszMsg);

#endif

	UI32			uiCSAAuth_Count;
	DWORD			dwLastGameGuardAuthClock;
	bool			bWaitGameGuardClientAuth;

	DWORD 			dwTimerClock;					// ���� �Ⱓ�� ������ �ִ� ĳ������. 
	SI32			siOldWeaponMagic;				// ������ ���õǾ��� ���� ���.

	// Ŭ���̾�Ʈ�� ��� �غ� ���ƴ°� ? 
	// ������ �ٷ� �� ĳ���͸� ���� �ൿ�� �� ������ 
	// Ŭ���̾�Ʈ�� �ε带 ������ �Ϸ��� �۾��� 
	// �ʿ��ѵ� �׷��� �۾��� �Ϸ�Ǹ� Ŭ���̾�Ʈ�� �Ϸ� ��ȣ�� ������ 
	// ������ �ǰ� ������ �� ����ġ�� �۵���Ų��. 
	// �� ����ġ�� �۵��� ���Ŀ��� �������� �� ĳ���Ϳ� ���� �ൿ�� �̷������ �ȴ�. 
	bool	bReadySwitch;	

	// �� ĳ���Ͱ� �������� ����� �ѹ� ���� ���� ������ ������Ʈ �ϴ� �۾��� �����ؾ� �Ѵ�. 
	// ���۾��� �� ĳ���� �ϻ��� �ѹ��� �̷������ �ȴ�. ���� ĳ������ �̵��� ���� �������� 
	// ������Ʈ�� ���÷� �̷�������� ���� ������ ���� �۾��� �ѹ��� �̷������ ���̴�. 
	// �� �۾��� �ѹ��� �̷������ �����ϴ� ����. 
	bool	bFirstCellOpSwtich;
	
	//-----------------------------------
	// �� ������ ���� �Ǵ� 3�� ĳ���� ����. 
	//-----------------------------------
	//cltCharListInfo clCharListInfo[MAX_CHAR_PER_USER];
	cltCharListInfo* pclCharListInfo;;

	// ������Ʈ ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray<class cltCharUpdateInfo, MAX_UPDATE_SWITCH>		clUpdateInfo;
#else
	class cltCharUpdateInfo	clUpdateInfo[MAX_UPDATE_SWITCH];
#endif

	//----------------------------
	// ��� ���� 
	//---------------------------
	bool bDeathPenaltySwitch;
	bool bRequestReviveSwitch;
	clock_t DeathClock;
	SI32 siCharDyingDelay;

	//-----------------------------
	// �ڵ� ȸ�� ���� 
	//-----------------------------
	DWORD			dwAutoRecoverLifeClock;		// ���������� �ڵ� ȸ���� �Ǿ��� �ð�. 
	DWORD			dwAutoRecoverManaClock;		// ���������� �ڵ� ȸ���� �Ǿ��� �ð�. 

	//-----------------------------
	// ����� ��� �ڵ� ȸ�� ����  Cushion
	//-----------------------------	
	DWORD			dwCusionRecoverLifeClock;		// ���������� �ڵ� ȸ���� �Ǿ��� �ð�. 
	DWORD			dwCusionRecoverManaClock;		// ���������� �ڵ� ȸ���� �Ǿ��� �ð�. 

	DWORD			dwCusionRecoverOragansClock;	// ���������� ��� ȸ���� �Ǿ��� �ð�. 
	DWORD			dwCusionFallSatisfiedClock;		// ���������� ������ �϶��� �Ǿ��� �ð�.

	// PCK : ���ڴ� �Ŀ��� ��� ��ȯ�� �ڵ� ȸ�� ���� (09.06.15)
	DWORD			dwCusionRecoverSummonLifeClock;		// ���������� ��ȯ�� �ڵ� ȸ���� �Ǿ��� �ð�. 
	DWORD			dwCusionRecoverSummonManaClock;		// ���������� ��ȯ�� �ڵ� ȸ���� �Ǿ��� �ð�. 

	//KHY - 1220 - ���Žý���. - �ڵ�ȸ��
	DWORD			dwTransFormRecoverManaClock;		// ���������� �ڵ� ȸ���� �Ǿ��� �ð�. 

	// Ÿ�̸�
	cltCharUpdateTimer m_clCharUpdateTimer;

public:
	SHORT 			WaitCount;
	SHORT 			Wait;
		
	SI32			RepeatNumber;

	//----------------------------
	// �Ӹ��� 
	//----------------------------

	bool bHeadChatSwitch;		// ���� �Ӹ����� �����Ǿ� �ִ°�?
	TCHAR szHeadChatText[MAX_HEAD_CHAT_TEXT_SIZE];

	//----------------------------
	// ���λ��� ������ 
	//----------------------------
	cltShopBannerData	clShopBanner;
	cltShopTradeData	clShopData;

	//----------------------------
	// ������û ������
	//----------------------------
	cltShopRepairData*	m_pclShopRepairData;

	//----------------------------
	// ĳ���� ���. 
	//----------------------------
	SI16	siCharMode;				// �� ĳ���Ͱ� � ���� �۵��ϴ°� ?(�ֱ�����, .. ) 
	SI16	siCharModePara1;		// ĳ���� ���� �Ķ��Ÿ. 

	SI16	siKilledMode;							// ��� ���. 
	TCHAR	szKillMeCharName[MAX_PLAYER_NAME];		// ���� ���� ĳ������ �̸�. 


	//-------------------------
	// ���ڸ����� ��� 
	//-------------------------
	bool bStaySwitch;				// ���ڸ��� ���缭 �ִ��� ����. 

	//-------------------------
	// �÷��� �ð� ���ϱ� 
	//-------------------------
	DWORD dwStartClock;
	DWORD dwInstantPlayTime;		// ���� ������ �÷���Ÿ��(DB����ȵ�)
	
	//-------------------------
	// ���ӿ� ������ �ð� ���
	//-------------------------
	_SYSTEMTIME sTimeStartTime;
	
	//-------------------------
	// ���� �α��������� �ڽ��Ƿ��� ���
	//-------------------------
	SI32 siLoginedLevel;
	//-------------------------
	// ����ȿ��. 
	//-------------------------
	DWORD dwGeneralEftSetClock;
	
	//-------------------------
	// ä�� �Է� �ð� 
	//-------------------------
	DWORD dwLastChatInputClock;
	

	//-------------------------
	// Daily Quest ���� �ֱ������� ����
	//-------------------------
	DWORD dwDailyQuestClock;
	DWORD dwDailyQuest2Clock;
	DWORD dwDailyQuest3Clock;


	//-------------------------
	// �����ϴ� ���̶��, ���� ������
	//-------------------------
	SI16			siFishingBaitItemUnique;
	//-------------------------
	// �ڵ� ����
	//-------------------------
	bool			bAutoFishing;
	//-------------------------
	// ���� �ֱ�
	//-------------------------
	DWORD			dwPreCatchFishClock;
	DWORD		    dwSummonFishClock;     //�迡 Ÿ�� ������ ��ȯ���� �����ϱ� ���� �ֱ�

	//-------------------------
	// ��þƮ 100% ���� ����ġ (����϶���)
	//-------------------------
	bool			bSuccessEnchant;
	
	//-------------------------
	// ��� ���̶��,  ȹ���ҷ��� ��� ������
	//-------------------------
	SI16			siFarmingItemUnique;
	//-------------------------
	// ��� �Ӵ��� ����( �ӽ÷� ) - ������� ��� ���� ���������..
	//-------------------------
	//SI16			siFarmingRentVillageUnique;
	//-------------------------
	// �ڵ� ���
	//-------------------------
	bool			bAutoFarming;

	//-------------------------
	// ��� ȹ�� ������ ����
	//-------------------------
	SI16			siFarmingItemCount;

	//-------------------------
	// ��� �ֱ�
	//-------------------------
	DWORD			dwPreGetFarmingItemClock;
	SI16			siFarmingActionCount;
	DWORD			dwFarmingClock;

	//-------------------------
	// ä��
	//-------------------------
	SI16			siMiningItemUnique;
	//SI16			siMiningRentVillageUnique;
	bool			bAutoMining;
	//SI16			siMiningItemCount;
	DWORD			dwPreGetMiningItemClock;
	SI16			siMiningActionCount;
	DWORD			dwMiningClock;
	
	//DWORD			dwStartAgricultureClock;
//	SI32			siLeaseLandVillage;			// �ӽ÷� ���� �����̳� ������ ���� ����ũ
//	UI32			uiLeaseLandExpire;			// �ӽ÷� ���� �����̳� ������ ��� ���� �ð�(������ ����)

	//-------------------------------------
	// Agriculture ������
	//-------------------------------------
	cltAgriculture*	m_pclAgriculture;
	
	//-------------------------------------
	// ���� ���� �ð�. 
	//-------------------------------------
	DWORD dwNoFirstAttackClock;					// ���� ������ ������ �ð�. 
	//-------------------------------------
	// ICE ���� �ð�. 
	//-------------------------------------
	DWORD dwNoIceAttackClock;					// ICE ������ ������ �ð� 

	//---------------------------------------
	// Ŭ���̾�Ʈ�� �޽��� ���� ������ �ð�. 
	//---------------------------------------
	DWORD dwLastSendServerClock;

	//-------------------------------------
	// ���� ���� 
	//-------------------------------------
	bool bMakeItemReserveSwitch;
	DWORD dwMakeItemStartClock;
	DWORD dwMakeItemDelayClock;
	cltGameMsgRequest_MakeItemInv* pclReservedMakeItemData;

	bool bMakeItemNoMinigame;		// �̴ϰ��Ӿ��� ����� �͵��̴�.
	bool bMakeItemMinigameSwitch;	// �̴ϰ��ӿ� ���� ���� �޾Ҵ�.
	bool bMakeItemSwitch;			// ������ �� �������.
	
	bool bEnchantItemSwitch;		// �������� ��æƮ ��Ų��.
	bool bFinishEnchantItemSwitch;	// ������ ��æƮ�� ���ƴ�.

	SI32 siMonsterCorp;				// ���� �ֽ� ȸ�� ����
	DWORD dwStartMiniGameTime;		// �̴� ������ �� �ð�

	cltCharGoonzuDayMissionInfo clGoonzuDayMissionInfo;		// [����] ���ֵ��̹̼� : �̼� ���� ����(Ƚ��)

	// �ڴ�� ����
	bool bRouletteStart;
	SI16  m_siBettingCount;
	SI16  m_siResultCount;
	DWORD dwRouletteStartClock;
	DWORD dwRouletteDelayClock;
#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<RouletteTable, 5>, 5>		m_stRouletteTable;
	NSafeTArray<SI16, 5>								m_siRandomValue;
#else
	RouletteTable	m_stRouletteTable[5][5];
	SI16			m_siRandomValue[5];
#endif
	//-----------------------------------
	// ���� ��� ���� ����. 
	//-----------------------------------
	bool bHopeToQuitSwitch;
	
	//----------------------------------
	// ���� �ð� ����� ���� ���� 
	//----------------------------------
	bool bCloseSocketSwitch;
	DWORD dwCloseSocketTimer;

	//---------------------------------
	// ������ ��� ����. 
	//---------------------------------
	DWORD dwLastCheckUseReserveItemClock;
	cltUseItemReserveInfo			clItemUseReserveInfo;
	cltBulletUseReserveInfo			clBulletUseReserveInfo;
	cltSummonBulletUseReserveInfo	clSummonBulletUseReserveInfo;	// ��ȯ�� ���� �߻�ü ����
	
	//---------------------------------
	// ȯ�� ����
	//---------------------------------
	bool bWhisperChatReject;
	bool bPrivateTradeReject;
	bool bPartyInviteReject;
	bool bFriendAddReject;
	//---------------------------------
	// ���� ��ġ �浹 üũ ����. 
	//---------------------------------
	DWORD dwLastCheckCollClock;


	//---------------------------------
	// �нż� ���� �ð� 
	//---------------------------------
	DWORD dwLastClone;

	//-----------------------------
	// �����ؾ��� �ڸ� ����
	//-----------------------------
	SI16			siCaptionKind;
	
	//-----------------------------
	// ��ƿ ���� 
	//-----------------------------
	DWORD			dwStealClock;
	SI16			siStealNum;			// ��ƿ�� Ƚ��. 

	//----------------------------
	// ���� ���� 
	//----------------------------
	DWORD dwPrisonClock;
	
	//-----------------------------------
	// ����Ʈ�� �Ϸ����� �ʾ� ������ �Ұ� ���� �ð�
	//--------------------------------------------
	DWORD dwLastLevelUpFailForQuestClock;


	//-----------------------------------
	// ���� ���� 
	//-----------------------------------
	SI16 siReservedAttackTargetID;
	
	//-----------------------------------
	// ��ȯ�� ó�� 
	//-----------------------------------
	bool bIsEvolving;		// ��ȯ�� ��ȭ ó�� �������� ������ 
	bool bIsTradeing;		// ��ȯ�� �ȱ���

	//------------------------------------
	// WeaponSkill ó��
	//----------------------------------
	bool bIsWeaponSkillUp;

	//----------------------------------
	// GameEvent
	//-----------------------------------
	bool bCheckGameEvent;

	//--------------------------------------------
	// ������ ���� - �ߺ��ؼ� ����� ���´�.
	//--------------------------------------------
	bool bIsSetPremium;
	//--------------------------------------------
	// Ȱ���� ���� - �ߺ��ؼ� ����� ���´�.
	//--------------------------------------------
	bool bIsSetCombat;

	//--------------------------------------------
	// ����� ���� - �ߺ��ؼ� ����� ���´�.
	//--------------------------------------------
	bool bIsSetMakeItem;

	bool bIsBulletService;

	bool bIsSummonStaminaService;

	//--------------------------------------------
	// ĳ�� ������ �ȱ� ���� - �ߺ� �ȱ� ����
	//--------------------------------------------
	bool bIsBuyCashItem;

	//--------------------------------------------
	// ������ �ݰ� �ִ�.
	//--------------------------------------------
	bool bIsPickUpItem;

	//-------------------------------------------------
	// ������ ������ ������ �ް� �ִ�.
	//-------------------------------------------------
	bool bIsItemMallGetItem;
	//-------------------------------------------------
	// ������ ������ ������ ��ų� ������ �ִ�.
	//-------------------------------------------------
	bool bIsItemMallBuyItem;

	//--------------------------------------
	// ���ָӴ� ������ �����
	//--------------------------------------
	bool bUseBagItem;

	//--------------------------------------
	// ���� ���� ������ �����
	//--------------------------------------
	bool bUseChangeHeroItem;

	//-------------------------------------
	// ���� �ŷ����̴�.
	//-------------------------------------
	bool bTradeServerUsing;

	//-------------------------------------
	// ���� ������ ���� ����.
	//-------------------------------------
	SI32 siVillageWarKillScore;

	//-------------------------------------
	// ���� �������� �Դ� ���̴�. ���ÿ� �Ծ ������ ������� ������ �ذ��ϱ� ���� ����
	//-------------------------------------
	bool bIsNowAddBufThroughDB;
	
	//-------------------------------------
	// ���� �������� �̴� ���̴�. �ѹ��� ������ ������ �Ҽ� ���Բ� �ϴ� ����
	//-------------------------------------
	bool bNowGachaBuy;

	//-------------------------------------
	// ��ȯ���� ��ȯ���̹Ƿ� ���� ��ȯ���� ��ȯ��Ű�� ���ϰ� �Ѵ�.
	//-------------------------------------
	bool bIsNowAddSummonThroughDB;

	//-------------------------------------
	// ��ȣ���� ����
	//-------------------------------------
	bool	bIsNowAddSoulGuardThroughDB;			// ��ȣ������ �̾Ƽ� DB�� ������̴�
	DWORD	dwLastSoulGuardActionClock;				// ��ȣ���� ���ǵ��� Ȯ�� Ÿ��
	DWORD	dwLastSoulGuardParentDeadMessageClock;	// ��ȣ���� ������ �׾����� ü�� �޽����� �Ѹ� �ð�

public:
	//--------------------------------------------------------------
	// ���� �׷� �Ŵ��� - ����� ���͸� ���
	//---------------------------------------------------------------
	SI32 siGroupUnique; // �ڽ��� ���� �׷��� ����ũ
	SI32 siGroupMember; // �ڽ��� ���� �׷쿡�� ���° ����ΰ�(��� �����ΰ�?)
	BOOL bGroupBossSwitch; // �ڽ��� ���� �׷��� ������ �ƴϳ�

	//---------------------------------
	// ���� ���� ���� ��Ȳ
	//---------------------------------
	bool	bSwordScroll;
	bool	bSpearScroll;
	bool	bAxeScroll;
	bool	bGunScroll;
	bool	bBowScroll;
	bool	bStaffScroll;
	bool	bCannonScroll;
	
	//---------------------------------
	// ���� ���� ������ ��Ȳ
	//---------------------------------
	SI08	siSwordScrollNum;
	SI08	siSpearScrollNum;
	SI08	siAxeScrollNum;
	SI08	siGunScrollNum;
	SI08	siBowScrollNum;
	SI08	siStaffScrollNum;

	// APEX-
	bool bApexLogin;
	// -APEX

	// �Ƿι���-
	bool	bTiredSystem;
	UI08	uiTiredState;
	DWORD	dwPlayingTime;	// ������ �����ؼ� ������ �� �ð�
	SI16 siTiredNotice;
	SI32   lastTiredNoticedovertime; // ������ �޽����� �ߺ��� ���� ���ؼ�.

	// ������ ����Ʈ ����ð�
	clock_t	lastQuestSaveDBTime;
	
	// �̴� ������ ������ �ð�
//	DWORD	dwStartMiniGame;

	UI32	uiIDNo;			// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

	bool	bMakeTimeReduce;	// ���� �ð� ���� - true : �����ð� ������ 1�� - by LEEKH 2008.05.09

	SI32	siQuestCount;		// ����Ʈ�� ī��Ʈ ���� ��

	SI64	siServerEvent_IndunScore;	//���� �̺�Ʈ �δ� ������

	SI16	siCharRouletteValue;		// ĳ���� �귿 ��� ���� ����

	SI16	siDivinationValue;			// �ų�귿 ��� ���� ����

	SI16	m_siNewSelectBoxValue;		// ���ο� ���� �ý��� �ӽ� �����(�� ���� ���� Ŭ�� ������ �������� ������)

public:


	cltCharServer();
	virtual ~cltCharServer();

	//----------------------------
	// ���� ĳ������ �ൿ. 
	//----------------------------
	void CharServerAction();
	void CharServerAction_NPC();
	void CharServerAction_PC();
	void CharServerAction_Summon();
	void CharServerAction_SoulGuard();

	void SummonFollowHost();		// ��ȯ���� ������ ���󰡰� �Ѵ�. 
	void SummonAutoHeal();			// ��ȯ���� �ڵ� ȸ���� �Ѵ�.

	//--------------------------------
	// ��ȣ����
	//--------------------------------
	void SoulGuardFollowHost( void );
	// ��ȣ���� �ɷ��� �ߵ� ��Ų��(Ȯ���� ���ؼ� �ߵ� �ȵɼ��� ����)
	SI32 SoulGuardAbilityActivity( SI32 siAbility, SI32 siLessThanValue=0, SI32 siMoreThanValue=0 );
	void SendSoulGuardParentDeadMessage( void );



	void InitCharServer();

	BOOL SendNeighbourMsg(cltMsg* pclmsg, bool bselfswitch);		// �̿����� �޽����� ������. 
	BOOL SendNeighbourExceptMeMsg(cltMsg* pclmsg);

	BOOL SetNeighbour();		// ĳ���� �ֺ��� �̿� �����͸� �����Ѵ�. 

	void CalculateRealXY();		// ���� ��ǥ�� ����Ѵ�. 

	void GetBottomPoint(cltPos* pclpos);

	//--------------------------------------
	// Ŭ���̾�Ʈ�� �뺸 �Լ� 
	//--------------------------------------
	bool SendInnerStatusToNeighbour();	// InnerStatus�� �̿��� �ڱ��ڽſ��� �뺸�Ѵ�. 
	BOOL SendChangedDataToClient();
	
	void InitPreGetOrder();				// ����� ���� �����ϱ� ���� �ؾ��� �ʱ�ȭ 

	//-----------------------
	//	��ȣȭŰ�� ĳ���� ����ũ ���� �뺸. 
	//-----------------------
	void SecretNCharUniqueSendOperation();		// ĳ���� ���� �Ŀ� ��ȣȭŰ�� ĳ���� ����ũ ���� Ŭ���̾�Ʈ�� ������. 

	//-----------------------------------
	// ���� �̵� ���� 
	//-----------------------------------
	void InitWarpInfo();
	void SetWarpInfo(const cltWarpInfo* pclCharWarpInfo, SI32 warpunique);
	void SetWarpToVillage(cltMapManager* pclmapmanager, SI16 villageunique, SI32 warpunique);	// Ư�� ������ �����ϰ� �Ѵ�. 

	BOOL Warp(bool bwritelog = false);	// ���� �̵���Ų��. 
	void WarpToSafeZone();				// ��������� �����̵��Ѵ�. 
	
	bool IsWarpStatus();

	//--------------------------------
	// CharServer-Magic.cpp
	//--------------------------------
	void SetMagicDelay(SI32 delay);
	SI32 GetMagicDelay();
	
	void CheckCurrentMagic( SI32 _siPrevActiveWeapon );		// ���� ������ ������ �������� �����Ѵ�. 
	bool MagicInAttackAction();		// ������ ���� ������ ���� ����. 

	SI32 			GetTotalMaxHealth();	// ���� �ƽ��ｺ ���� ���Ѵ�. 
	
	bool IsExistItemOnOpeningPersonShop(SI32 siItemPos);		// ���λ����� �ڽ��� Ư�� �������� ��ϵǾ�����..
	
//-----------------------------------------------------------------------------------
//  ���� ���� 
//-----------------------------------------------------------------------------------
	BOOL 			FindEmptyArea(SHORT& x, SHORT &y);
	BOOL 			FindEmptyArea(SHORT& x, SHORT &y, SHORT xsize, SHORT ysize);

//-----------------------------------------------------------------------------------
// ���� �ΰ����� ����. 
//-----------------------------------------------------------------------------------

	BOOL			CanWork();					// ���� �� �غ� �Ǿ� �ִ°�?
    bool			FindEnemyAction(SI32 id);	// ���� ���� ��ó 
	BOOL			Pull(SI32 dir);				// Ư�� �������� ĳ���͸� �о��. 
	
	//--------------------------------------
	// ���ݰ��� 
	//--------------------------------------
	void SetLastKillClock(DWORD clock);							// ���������� ����� �ð��� üũ�Ѵ�. 
	void SetReservedAttackTargetID(SI16 id);
	void AddKillMonsterNum(SI32 add)
	{
		clSimpleVary.siCheckMonsterNum += add ;
	}
	void SetKillMonsterNum(SI32 num)
	{
		clSimpleVary.siCheckMonsterNum = num ;
	}

	bool  DoReservedAttackAction(cltOrderDataInfo* pclorder);	// ����Ǿ� �ִ� ���� ����� �����Ѵ�. 
	bool  DoReservedAttackClientAction(cltOrderDataInfo* pclorder);

	void GetShapeEquipInfo(cltShapeEquipInfo* pclequip);		// �� �ܾ� ��� ��Ȳ�� ���´�. 
	
	void  CheckWeaponSkillScroll(cltItemManagerCommon* pclItemManager);		// ���� ���� ���� ��� ���¸� üũ�Ѵ�. 

	//-------------------------------------
	// ���� ������ ĳ���Ͱ� ���ϴ� ����
	//-------------------------------------
	
    BOOL OperateWaitServer();		// ������ �ൿ 
	bool SearchEnemy(SI32 range);	// ��ó�� ���� ã�´�. 
	bool RandomMove();				// �����ϰ� �ֺ����� �̵��Ѵ�. 
	
	bool FollowGroupBoss(SI32 bossid);		// ������ ������ ������ ���󰡰� �Ѵ�.

	// mode :	1 -> PC
	//			0 -> NPC
	//			2 -> Instance NPC
	static SI32 FindEmptyCharUnique(SI32 mode)
	{
		SI32 i;


		if(mode == 1)
		{
			for(i =1; i < MAX_PERSON_NUMBER;i++)
			{
				if(CharUniqueInfo[i] == 0)return i;
			}
		}
		else if(mode == 2)
		{
			for(i = (MAX_PERSON_NUMBER ); i < (MAX_PERSON_NUMBER +MAX_INSTANCE_NPC_NUMBER);i++)
			{
				if(CharUniqueInfo[i] == 0)return i;
			}
		}
		else
		{
			for(i = (MAX_PERSON_NUMBER +MAX_INSTANCE_NPC_NUMBER); i < MAX_CHAR_NUMBER;i++)
			{
				if(CharUniqueInfo[i] == 0)return i;
			}
		}

		return 0;
	}
	
	//------------------------------------------------
	// ������ ���� 
	//-----------------------------------------------

	SI32 CreateSoulGuard( cltSoulGuard* pclCreateSoulGuard );
	void DeleteSoulGuard( void );
	
	SI32 CreateSummon(cltSummon* pclSummon);		// �������� ����Ѵ�
	bool UseItem(cltItem clitem,SI32 itempos = 0);	// �������� ����Ѵ�. 

	void ItemUseReserveAction();					// ����Ǿ� �ִ� ��� ������ ó���� �Ѵ�. 
	void BulletUseReserveAction();					// ����Ǿ� �ִ� źȯ ������ ó���� �Ѵ�. 
	void BulletUseReserveAction_ForPerson();		// �ɸ��� źȯ ������ ���ó�� 
	void BulletUseReserveAction_ForSummon();		// �ɸ��� źȯ ������ ���ó��
	BOOL AddItemToInventory(cltItem* pclitem);		// �������� �κ��丮�� �ִ´�. 
		
	bool InputItem(cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32 inputitemreason, SI32* prtnvalue);	//ĳ���Ϳ��� �������� �ش�. 
	void InputItemReserveAction();		// InputItem�� ����� �ڸ��� �����Ѵ�. 

	// Ʈ���̵� ���� ����! Ʈ���̵����� ���� �������� ���ϰ� �Ѵ�!
	void SetNoMoveItemSwitch(SI32 itempos,bool move)
	{
		if ( itempos >= 0 && itempos < MAX_ITEM_PER_PERSON )
			clSimpleVary.bNoMoveItemSwitch[itempos] = move ;
	}

	SI32 GetNoMoveItemSwitch(SI32 itempos)
	{
		if ( itempos >= 0 && itempos < MAX_ITEM_PER_PERSON )
		{
			if ( clSimpleVary.bNoMoveItemSwitch[itempos] )
			{
				// �̹� �̵����̴�!
				return 1 ;
			}
			else return 0 ; // �̵����� �ƴϴ�!
		}
		else return -1 ; // ��ġ�� �߸� �Ǿ���!
	}

	void SetInputItemReserve(SI32 itempos, DWORD data);

	SI32 GiveItem(SI32 itemunique, SI32 itemnum, SI32 giveitemreason,SI32 usedate, SI32 siSealMode=GIVEITEM_SEAL_MODE_NONE, SI32 EnchantType = 0, SI32 EnchantLevel = 0, SI32 SlotNum = 0);	// ĳ���Ϳ��� �������� �ְ� �ʿ��� ��ġ�� ���Ѵ�. 
	bool TakeOutItem(SI32 itemunique, SI32 itemnum, SI32 takeoutitemreason);		// ĳ���Ϳ��Լ� �������� �����ϰ� �ʿ��� ��ġ�� ���Ѵ�. 
	// �ֹ��� �ٰŷ� ������ ��þ �Ҽ� �ִ��� �˻��Ѵ�.
	bool CanEnchantItem(cltGameMsgRequest_MakeItemInv* pclinfo, SI32 *returnval, SI32 *preturnpara1);
	// �ֹ��� �ٰŷ� ������ ����� �ִ��� �˻��Ѵ�.
	bool CanMakeItem(cltGameMsgRequest_MakeItemInv* pclinfo, SI32 *returnval, SI32* preturnpara1);		
	
	// ��þƮ�Ѵ�
	bool EnchantItem(cltGameMsgRequest_MakeItemInv* pclinfo);
	
	bool MakeItem(cltGameMsgRequest_MakeItemInv* pclinfo);		// �ֹ��� �ٰŷ� ������ �����. 
	bool SetReserverMakeItem(DWORD productclock, cltGameMsgRequest_MakeItemInv* pclinfo);		// ���� �����Ѵ�.

	SI32 GetMakeItemNum(SI32 needskillunique, SI32 needskilllevel, SI32 makeitemunique, SI32 makeitemnum);
	SI32 GetMakeCrystalItemNum(SI32 needskillunique, SI32 needskilllevel, SI32 makeitemunique, SI32 makeitemnum);

	void DecreaseEquipDur(SI32 itempos, SI32 durwaste);						// �� ����� �������� ���ҽ�Ų��. 
	void DecreaseSummonEquipDur(SI32 siSummonIndex, SI32 itempos, SI32 durwaste);
	void DecreaseArmourDur( SI32 siEnemyID );								// �汸�� �������� ���ҽ�Ų��. 
	void DecreaseWeaponDur( SI32 siEnemyID );								// ������  �������� ���ҽ�Ų��. 
	void DecreaseSkillItemEquipDur( SI32 skillunique );		// Ư�� ����̳� ����� ���� ��ǰ �������� �Ҹ��Ų��. 
	void DecreaseEquipDurFromDead( );

	void UseItemReasonDurabilityZero( SI32 siItemPos );	// �������� 0�̾ �����Ѵ�

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�. - ������ ���� ����.
	void SetCrystalDurUpdateSwitch(SI32 itemposition, bool mode);
	void SubDecreaseCrystalDur(SI16 ActiveItem,SI16 durvary);
	void DecreaseCrystalDurAC(SI16 durvary); // ��Ƽ�ε� ������ ����ü �������� ���ҽ�Ų��.
	void DecreaseCrystalDurDE(SI16 durvary); // ��� ���� ����ü �������� ���ҽ�Ų��.

	void SendClientCrystalDurability(); // ����� ����ü ������ ������ Client�� ������.
	void SubSendClientCrystalDurability(SI16 ActiveItem);

	// [����] ��ȯ�� ������� : ��ȯ�� ��� ũ����Ż ����
	void SubDecreaseCrystalDurForSummon( SI16 siActiveItem, SI16 siDurvary );
	void DecreaseCrystalDurACForSummon( SI16 siDurvary );
	void DecreaseCrystalDurDEForSummon( SI16 siDurvary );

	void SendClientCrystalDurabilityForSummon();

	//-------------------------------------------------------------------------------------

	bool CanAddInv(SI32 invmode, cltItem* pclitem, SI16* pitempos, cltItem* pcltoitem, SI32* prtnvalue);
	
	bool IsBlankInv(SI32 invnum,SI32 invmode);

	// �ѹ��� ������������ ������ üũ�� ���� ����.
	bool CanAddInvManyItems(SI32 invmode, cltItem* pclitem, SI32* prtnvalue);

	void SetRoulette(bool bcheck);	// �����Ҳ��� �����Ҳ���
	void CheckRoulette();			// ���� �귿 üũ
	bool CheckLottoRoulette();		// ������� üũ

	bool CheckSubBigItem();
	//���� ����Ʈ �϶� 2���ϱ� �˻�....'';�̰� �ƴѵ�..
	bool CheckItemForEmptyAnyItemSlotByHiddenQuesst( SI32 invmode, cltItem* pclitem,cltItem* pclitem2);
	
	// ������ �߰��ϴ� �޼ҵ� ( ������ DB�� ���� ������ �߰��Ǳ� ���� �ٸ� ������ �߰��Ҽ� ���� ) [����]
	bool AddBufThroughDB(SI16 index, stBuf* buf, bool useitem, SI16 itempos, cltItem* pclitem, GMONEY money = 0);
	// [����] �����̾� �������� ���� ���� ������ ���� �Լ� �߰�.
	bool AddBufThroughDB_AccumulateEnable(stBuf* pBuf, bool useitem, SI16 itempos, cltItem* pclitem, GMONEY money = 0);
	// [����] ���� �������ִ� ���� �������� ������ �ش�. (������ ����� ����� ���� ���� �������..)
	bool AddBufToAllTownPerson(SI32 siTownUnique, stBuf* pBuf, SI32 siSkipBuf1 = 0, SI32 siSkipBuf2 = 0);
	bool AddTownBufThroughDB(cltCharServer* pCharServer, stBuf* pBuf);
	bool IsNowAddBufThroughDB();

	//-------------------------------------------
	// Rank ���� 
	//-------------------------------------------
	BOOL SetRank(cltSimpleRank* pclrank);

	//----------------------------------
	// Skill
	//----------------------------------
	BOOL DevelopSkill(SI32 skillunique);		// ��ų�� ���ʷ� �����Ѵ�. 

	//---------------------------------
	// Update
	//---------------------------------
	void SetUpdateSwitch(SI32 updatetype, bool mode, SI32 para1);
	void SetSkillUpdate(SI32 skillunique, SI32 addskillexp);
	void SetWasteDurUpdateSwitch(SI32 itemposition, bool mode);
	void SetSummonWasteDurUpdateSwitch(SI32 SummonIndex, SI32 itemposition, bool mode);

	//--------------------------------
	// Group
	//--------------------------------
	void SetNPCGroup(SI32 group);
	SI32 GetNPCGroup()const;

	//------------------------------------
	// CharServer-Session.cpp
	//------------------------------------
	///----------------------------------
	// Session ������ ȣ�� �Լ�. 
	//-----------------------------------
	void Init();
	void Close();
	void CloseAction(cltServer* pclServer, bool bnormalquitswitch);		// ������ �����ϱ� ���� ĳ���Ͱ� �����ؾ� �� �ϵ�. 

	//----------------------------------
	// ��� ���� 
	//----------------------------------
	bool IsDeathPenaltyCondition();
	void DeathPenalty(SI32 killedmode = -1, TCHAR* szkillername= NULL);		// ����� ���� ���Ƽ. 
	void RequestRevive(SI32 id, SI16 DieMode);
	void Revive();			// ��Ȱ�ϱ�. 
	void Resurrection( bool pvpFlag );	// ���ڸ� ��� ��Ȱ�ϱ�.

	//---------------------------------
	// Ŭ���̾�Ʈ�κ��� �޽����� ���� �ð�.
	//---------------------------------
	void SetLastReceveFromClientClock(DWORD clock);

	//----------------------------------
	// �α� �ƿ� ���� 
	//---------------------------------
	bool AutoLogOut();			// �ð� ����� ���� �ڵ� �α׾ƿ�. 

	//----------------------------------
	// ������ �۾�.
	//----------------------------------
	void CellAction();			//ĳ���Ͱ� ó�� ����� ������ ���� ��Ϲ� ���� ���� ��û�� ���� �ӹ��� �����Ѵ�. 
	void DeleteInCell();		// �� �������� ������ �����Ѵ�. 

	//----------------------------------------------------------
	// Ŭ���̾�Ʈ���� ���� �Լ�. 
	//----------------------------------------------------------
	void SendLetterMsg(cltLetterUnit* pclletter);		//������ ������. 
	void SendAccountLetterMsg(cltAccountLetterUnit* pclletter); // 

	//--------------------------------------------------------
	// CharServer-SendDB.cpp
	//--------------------------------------------------------
	void SendDB_PosLifeMana();									// ��ġ, ü��, ������ ������ DB�� �����Ѵ�. 
	void SendDBLevelInfo(SI32 incbonus, SI32 incskillbonus);	// level ������ DB�� �����Ѵ�. 
	void SendDBSkillExp();										// ����� SKill������ DB�� �����Ѵ�.
	void SendDBWasteDurability();								// ����� ������ ������ DB�� �����Ѵ�.
	void SendDBSummonWasteDurability();
	void SendDBSummon(SI32 siReason, UI08 siSummonIndex, cltSummon *pSummon);		// ����� ��ȯ�� ������ DB�� �����Ѵ�.
	void SendDBSummon(SI32 siReason, SI32 siSummonIndex);
	void UpdateTakeOutSummon();									// ������ �����ִ� ��ȯ���� ������ ���ο��� update ��Ų��.
	void SendDBUpdateTeacherPoint( SI32 Level );

	//KHY - 0227 - ����ü (ũ����Ż) ���� �߰�.
	void SendDBCrystalDurability();								// ����� ����ü ������ ������ DB�� ������.
	void SendDBCrystalDurabilityForSummon();					// ��ȯ���� ����ü ������ ����
	//-----------------------------------
	// �α����� ��ȣ 
	//-----------------------------------
	void SetInitProtectSwitch();
	bool GetInitProtectSwitch();
	
	void AutoRecoverLife();		// �ڵ� ȸ�� ���. 
	void AutoRecoverMana();

	void AutoCushionRecoverLife();	// ����� ��ǿ� ���� �ڵ� ȸ�����
	void AutoCushionRecoverMana();

	// PCK : ���ڴ� �Ŀ��� �漮�� ���� ��ȯ�� �ڵ� ȸ����� (09.06.15)
	void AutoCushionRecoverSummonLife();
	void AutoCushionRecoverSummonMana();

	//KHY - 1220 - ���Žý���.
	void AutoTransFormRecoverMana();

	void LevelUpAction();								// ���� ���� ���� �۾�. 
	bool IncreaseExp(SI64 exp, SI32 reason = 0);		// ����ġ�� �ø��� �ʿ��� ��� ��ġ�� ���Ѵ�.// SI32->SI64 ����ġ �����÷ο춧���� ����	 
	bool IncreaseFameExp(SI32 exp, SI32 reason =0);		// �� ����ġ�� �ø��� �ʿ��� ��� ��ġ�� ���Ѵ�. 
	 

	void SetHeadChat(bool bheadchatswitch, TCHAR* ptext);			// ĳ������ �Ӹ����� �����Ѵ�. 
	void SetPersonalShopBanner(cltShopTradeData* pclshopdata);		// ĳ������ PersonalShop������ �����Ѵ�.
	void SetPersonalShopData(bool bRepairShopSW, cltShopTradeData* pclshopdata);

	void SetRepairShopData( bool bRepairShopSW, cltShopRepairData* pclRepairData );
	
	bool AfterCharAction();
	void CalcPlayTime();		// ���� �÷��� �ð��� ����Ѵ�. 

	//---------------------------------------
	// ���� ȿ��
	//---------------------------------------
	void GeneralEft(bool bacswitch, SI32 acuprate, bool bdamageswitch, SI32 damageuprate , bool alluser );	// ���� ȿ���� �����Ѵ�. 
	
	//[�߰� : Ȳ���� 2007. 12. 11 ������ �ų�Ʈ���� �ִٸ� ���� ����. ���� ������]
	void NewYearTreeEft(SI32 _VillageUnique);


	bool HealAI();		// �ΰ����� ġ��. 
	void FishAI();		// �ΰ����� ����. 
	void FarmAI();		// �ΰ����� ���
	void MineAI();		// �ΰ����� ä��
	
	bool CheckItemMallBadRequest();				// �����۸��� ������ ������ ������ üũ�Ѵ�. 1�ʿ� 5ȸ �̻��� ��û�� ���� 
	bool CheckLastMsgClock(DWORD interval);		// Ŭ���̾�Ʈ�� ������ ���� ������ �޽������� �ð� ������ Ȯ���Ѵ�. 
	void MakeHunger(SI32 addHunger = 0);							// ������� �����. 

	BOOL DoAnimationDelay(BOOL atb = 0);
	void CharServerStatusAction();

	//=================================================
	BOOL SetPoison( SI32 poisoner, SI32 damage, DWORD _dwAddClock = 20000 );			// �ߵ��� ��Ų��. 
	BOOL SetPoisonSetItemEffect( SI32 poisoner, SI32 damage, DWORD _dwAddClock = 20000 );		//��Ʈ �������� ȿ���� �ߵ��� ��Ų��. 
	BOOL SetIce(SI32 damage, DWORD _dwAddClock = 0);									// ĳ���͸� �󸰴�. 
	
	BOOL SetDrain(SI32 damage, SI32 passivedamage, SI32 passivemana);		// Drain���� ���� �������� �߰��Ѵ�.
	BOOL SetCurseAttack(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid);		// ���ݷ��� ���ϵȴ�.
	BOOL SetCurseCritical(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid);		// Critical Ȯ���� ��������.
	BOOL SetCurseDefense(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid);		// ������ ��������. (�� ���ݷ��� ����)
	BOOL SetCurseMovespeed(SI32 damage, SI32 passivedamage, SI32 passivemana, SI32 enemyid);	// �̵��ӵ� ���� 
	
	BOOL SetMagicFire(SI32 enemy, SI32 damage);		// �ҿ� �¿��.
	BOOL SetFrozen(SI32 damage);					// ���� �������� �󸰴�.
	BOOL SetStun(SI32 damage);						// ������ �Ǵ�
	BOOL SetSoulGuardIce(SI32 damage);				// �ҿﰡ�� - �󸰴�
	//=================================================

	//=================================================
	BOOL DeletePoison();							// �ߵ� ���¸� �����Ѵ�.
	BOOL DeletePoisonSetItemEffect( void );
	BOOL DeleteIce();								// ���� ���¸� �����Ѵ�.

	BOOL DeleteCurseAttack();						// ���ݷ��� ���� ���¸� �����Ѵ�.
	BOOL DeleteCurseCritical();						// Critical Ȯ���� �������� ���¸� �����Ѵ�.
	BOOL DeleteCurseDefense();						// ������ �������� ���¸� �����Ѵ�.
	BOOL DeleteCurseMovespeed();					// �̵��ӵ� ���� ���¸� �����Ѵ�.

	BOOL DeleteMagicFire();							// �ҿ� Ÿ�� ���¸� �����Ѵ�.
	BOOL DeleteFrozen();							// ���� ���� ���¸� �����Ѵ�.
	BOOL DeleteStun();								// ���� ���¸� ���� �Ѵ�.
	BOOL DeleteCurseEffect();						// [����] ����� ���� ����.
	//=================================================

	void BeHitOperate(SI32 attackid);				//ĳ���Ͱ� ���� �޾��� �� ó���ؾ��� �ϵ�. 
	SI32 DecreaseLife(SI32 life);
	
	bool SendNeighbourMyShapeStatus();				// �̿����� �� �ܾ� ������ �뺸�Ѵ�. 
	bool SendNeighbourMyMakeItemStatus();

	//------------------------------------------
	// ĳ���� ������ ���� �⺻ ���� 
	//------------------------------------------
	bool GetMakeCharInfo(cltMakeCharInfo* pclinfo, bool borderswitch, bool bticketusewarpswitch);
	
	cltCharServer* GetHostChar();		// ���� ĳ������ �����͸� ���Ѵ�. 

	//---------------------------------
	// CharServer-Dying.cpp
	//---------------------------------
	bool	Action_Dying();
	void	Dead();					// ��� ó��. 
	bool	TugDieOperation();		// �ٴٸ��� ����忡�� �׾������ ���������� ó���ϴ� �Լ� 
	void	SelfBombAction();			// ����ó��. 
	
	//----------------------------------------------
	// Char-Horse.cpp
	//----------------------------------------------
	SI32 CharHorseAction(cltHorse* pclhorse, bool bselfswitch);		// ����ڰ� ������ ���� ���� ������ ó���Ѵ�. 
	bool SendNeighbourMyHorseStatus(SI32 index);					// �̿����� �� ���� ���¸� �뺸�Ѵ�. 
	bool AutoHorseFood(SI32 itemunique, SI32 itemnum);				// �ڵ����� �� ���̸� �ش�. 

	void UpdateHorseToDB(cltServer* pclserver, SI32 index, cltHorse* pclhorse, SI32 reason);		// �� ������ DB�� ������Ʈ �Ѵ�. 
	void CharServerMoveByGate(SI32 x, SI32 y);						// �������� ĳ������ ���� �̵� ����.

	//-----------------------------------------------
	// CharServer-Manner.cpp
	//-----------------------------------------------
	SI16 GetStealNum();		// ��ƿ�� Ƚ���� ���´�. 
	bool SendPrison();		// ������ ������. 
	bool IsAutoHunting();	// �ڵ� ������� ���θ� Ȯ���Ѵ�. 

	//----------------------------------------------
	// CharServer-Fish.cpp
	//----------------------------------------------
	bool CatchFishAction( bool IsPerson );				// ����⸦ ��Ҵ�.
	SI32 CatchFish_GoldMineral(SI32 FishSkillLevel);
	SI32 CatchFish_SpecialItem();
	SI32 CatchFish_BigItem(SI32 FishSkillLevel);
	bool FishingStart( SI32 FishingBaitItemUnique );	// ���� ����
	void FishingStop();									// ���� �ߴ� 
	bool GetFishingToolInfo( SI16 FishKindListRef, DBToolInfo *pFishingToolList );		// ������ ����Ѵ�.
	bool IsAvailableFishing( SI32 FishingBaitItemUnique, SI16 FishKindListRef );		// ���� �������� üũ

	//----------------------------------------------
	// CharServer-Farm.cpp
	//----------------------------------------------
	bool FarmingAction( bool IsPerson );
	void FarmingStop();	

	SI32 FarmingBigItem();
	SI32 FarmingBigItem_New(SI32 FarmSkillLevel);

	//----------------------------------------------
	// CharServer-Mine.cpp
	//----------------------------------------------
	bool MiningAction( bool IsPerson );
	void MiningStop();
	bool IsLeaseAgriculture( SI32 villageUnique );

	SI32 MiningBigItem();
	SI32 MiningBigItem_New( SI32 MineSkillLevel );
	
	//-------------------------------------------
	// CharServer-Quest.cpp 
	//-------------------------------------------
	void IncQuestPara(SI32 clearcond, SI32 para1, SI32 incnum);		// ����Ʈ�� �Ķ��Ÿ�� ������Ų��. 
	void DoQuestCheckAndAction(SI32 questclearcond);				// ĳ���Ͱ� �����ϰ� �ִ� ����Ʈ�� �����Ͽ� �����Ų��. 
	
	bool MakeSpecialQuest();			// Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Battle();		// ������ Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Farm();		// �������� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Fish();		// �����ϱ�� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Mine();		// ä���ϱ�� Ư�� ����Ʈ�� �����.
	bool MakeSpecialQuest_Skill();		// ��� �ø���  Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_UseItem();	// ���� ����� ����Ʈ�� �����. 
	bool MakeSpecialQuest_MakeFriend();	// ģ�������� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_GetItem();	// ��ǰ �������� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_MakeItem();	// ��ǰ �����ϱ� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Equip();		// ��� �����ϱ� Ư�� ����Ʈ�� �����. 
	bool MakeSpecialQuest_Scroll();		// ��� ���� �ٸ���.
	bool MakeNamingQuest( SI32 index, SI32 level );		// ��Ī ����Ʈ�� �����.
	bool MakeSpecialQuest_Gomap();		// [����/090605] ���� ��ȸ�ϱ� ����Ʈ�� �����.
	bool MakeSpecialQuest_MakeSkillExpup();	// [����/090608] ���� ����ġ +1 �ø��� ����Ʈ�� �����.

	// [����- 2009.10.14] �ų��̺�Ʈ - �� ������ �������� �����ϴ� ����Ʈ�� �����.
	bool MakeQuest_RemoveUnLuckStatus();
	bool MakeQuest_RemoveUnLuckStatus_Battle();				// ���� ��� ����Ʈ�� �����.
	bool MakeQuest_RemoveUnLuckStatus_MakeItem();			// ��ǰ �����ϱ� ����Ʈ�� �����.
	bool MakeQuest_RemoveUnLuckStatus_NPCQuestComplete();	// NPC�� �����ϰ� �ִ� ����Ʈ�� �Ϸ��ϴ� ����Ʈ�� �����.

	//void EventReward_NewYear2010();		// 2010�ų��̺�Ʈ - ��Ű ����

	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	bool MakeHappyBeanQuest();
	bool MakeHappyBeanQuest_Battle();	// ������ Ư�� ����Ʈ�� �����. 	
	bool MakeHappyBeanQuest_Skill();		// ��� �ø���  Ư�� ����Ʈ�� �����. 
	bool MakeHappyBeanQuest_GetItem();	// ��ǰ �������� Ư�� ����Ʈ�� �����. 
	bool MakeHappyBeanQuest_MakeItem();	// ��ǰ �����ϱ� Ư�� ����Ʈ�� �����. 
	//	bool MakeHappyBinQuest_Equip();		// ��� �����ϱ� Ư�� ����Ʈ�� �����. 

	bool MakeMissionQuest(SI32 siMissionUnique);
	bool MakeMissionQuest_Holloween();

	// [���� - 2010.01.06] ���� ���̶� ������ �� �ִ� �̼� �߰�. (���δ��)
	bool Make_GoonzuDayMission();				// ���ֵ��̹̼�		
	bool Make_GoonzuDayMission_Battle();		// ���� ��� ����Ʈ�� �����.
	bool Make_GoonzuDayMission_MakeItem();		// ��ǰ �����ϱ� ����Ʈ�� �����.
	bool Make_GoonzuDayMission_Collect();		// ��ǰ �����ϱ� ����Ʈ�� �����.
	bool Make_GoonzuDayMission_UseItem();		// ��ǰ ����ϱ� ����Ʈ�� �����.
	
	//-------------------------------------------
	// CharServer-Jim.cpp
	//-------------------------------------------
	void LoseJim();		// ���� Ǯ����. 

	//-------------------------------------------
	// CharServer-Attack.cpp
	//-------------------------------------------
    void SetBeAttackedSwitch(cltServer* pclserver, SHORT enemyid);	// ������ ���ݹް� ������ ȣ���ϴ� �Լ� 
    void BeAttackedAction();										// ������ ���ݹ������� ��ġ 

	void MakeTorpedo(cltServer* pclserver, SI32 attackid, cltItem* pcltorpedo);		// ��� ���������κ��� ��� ĳ���͸� �����Ѵ�.
	
	// �Ƿε� �ý��� 
    SI64 CalcTiredPoint( SI64 point );
	SI32 CalcTiredPoint( SI32 point );
	SI16 CalcTiredPoint( SI16 point );

	bool CharTransform( SI16 siCharKind , SI16 ActiveWeapon ,cltItem* pclitemlist , cltPSkillInfo *pclskillinfo);

	//KHY - 1014 - �漮 �߰�. - �̺� Ư���ɷ�, ���ȸ��. ������ �϶�.
	void AutoCushionRecoverOragans();
	void AutoCushionFallSatisfied();

	//KHY - 1113 - ũ�������� �̺�Ʈ - ũ�������� ����Ʈ�� Ư���ϴ�.
	void ChristamsEventQuest(SI32 *Enemykind);

	void TransformSummon( IN cltCharManager* _pclCM, IN cltSummonTransformManager* _pclSummonTransformManager );
	void UpDateSummonTransForm( IN cltSummonTransformManager* _pclSummonTransformManager, IN cltSummon* _pSummon, IN SI32 siTansformSummonIndex, OUT cltSummon** _pTranformSummon );
	SI32 CalcuSummonTransFormAbility( IN SI32 siStatus, IN SI32 _siAbility );
	void TransformSummonStaminaUp( cltCharServer* pclParentChar, SI32 amt );
	void TransformSummonStaminaDown( cltCharServer* pclParentChar, SI32 amt );

	void HuntQuestitem(SI32 siCharID, SI32 siMonsterKind);				// ������� ����Ʈ������ ȹ��

	//[����] - 2010�ų��̺�Ʈ ���� ( 1/1000 Ȯ�� ���� (1�� ������� 0.1%, 10�� 1%) )
	void GiveFortuneCookiePiece(SI16 siRate, SI16 siCount);

	//[����] - 2010�ų��̺�Ʈ ���� - ����� ����Ʈ�� ���� �ؽ�Ʈ npc ī�ε带 �����ص� �迭
#ifdef _SAFE_MEMORY
	NSafeTArray<NTCHARString128, REMOVEUNLUCK_QUESTNPC_COUNT>		m_arRemoveUnluckQuest_NPC;
	NSafeTArray<SI32, REMOVEUNLUCK_QUESTNPC_COUNT>					m_arRemoveUnluckQuest_Unique;
#else
	NTCHARString128													m_arRemoveUnluckQuest_NPC[REMOVEUNLUCK_QUESTNPC_COUNT];
	SI32															m_arRemoveUnluckQuest_Unique[REMOVEUNLUCK_QUESTNPC_COUNT];
#endif

	void InitArray_RemoveUnLuckQuestNPC();
};


#endif
