//---------------------------------
// 2003/7/4 ���°�
//---------------------------------
#ifndef _CHARCOMMON_H
#define _CHARCOMMON_H

#include "../../Char\KindInfo\KindInfo.h"

#include <windows.h>
#include <windowsx.h>
#include <dplay8.h>
#include <directives.h>
#include "../../Char\CharAni\CharAni.h"
#include "../../Char\parametaBox\ParametaBox.h"
#include "../../Item\ItemCommon\cltItem.h"
#include "../../../CommonLogic\Bank\Bank.h"
#include "../../Char\CharClient\CharCut\CharCut.h"
#include "../../Horse\Horse.h"
#include "../../../Client\Effect\LevelUpEffect\LevelUpEffect.h"
#include "../../../CLient/Effect/HeartEffect/HeartEffect.h"
#include "../../../CLient/Effect/FoueLeafEffect/FourLeafEffect.h"
#include "../../../Client/Effect/Cushion/CushionEffect.h"
#include "../../../Client/Effect/CushionCat/CushionCatEffect.h"



#include "../../../Client\Effect\MVPEffect\MVPEffect.h"
#include "../../../Client\Effect\EnchantEffect\EnchantEffect.h"
#include "../../../Client\Effect\QuestEffect\QuestEffect.h"
#include "../../../Client\Effect\Regeneration\Regeneration.h"
#include "../../../Client\Effect\BossEffect\BossEffect.h"
#include "../../../Client\Effect\SkillLevelUpEffect\SkillLevelUpEffect.h"
#include "../../../Client/Effect/Emoticon/EmoticonMgr.h"

#include "../../Char\IDManager\IDManager.h"
#include "../../Char\CharCommon\Char-EconomyInfo.h"
#include "../../Char\CharManager\CharManager.h"


// ��Ʈ��ũ�� ���. 
#include "..\..\NetworkLib\ITZNetLib\ITZNetworkThread.h"
#include "..\..\NetworkLib\ITZNetLib\ITZPerson.h"
#include "..\..\NetworkLib\ITZNetLib\ITZListen.h"

// ������ ĳ���Ϳ� ���. 
#include "../../Char\CCD\BaseDefinition.h"
#include "../../Char\CCD\XSPRMgr.h"
#include "../../Char\CCD\CharacterDrawing.h"

#include "../../PersonInfo.h"
#include "../../../CommonLogic/MagicMgr/MagicBaseInfo.h"

#include "../../../common/Family/Marriage.h"
#include "../../../common/Family/Family.h"	//��������

#include "../../../common/SoulGuard/SoulGuard.h"

//�ð��񱳸����ؼ� �߰�. ���������� ���� �߰�
#include "../NLib/NUtil.h"
#include "../../../../NLib/NTech/sdk/nkcore/Include/NkList.h"

//----------------------------
// ĳ���� �̵� ���ϰ�. 
//----------------------------
#define MOVERTNVAL_MOVING    0    // Moving
#define MOVERTNVAL_MOVEDONE  1    // Move Done
#define MOVERTNVAL_HALFDONE  2    // arrive Middle Point  

//----------------------------
// �������� ����ڿ��� �ִ� ���. 
//----------------------------
#define GIVEITEM_MODE_PERSON		1	// Ư�� ����� 1�ο��Ը� �ش�. 
#define GIVEITEM_MODE_ADULT			2	// ���� FATHER_LEVEL�̻� ����ڿ��Ը� �ش�.
#define GIVEITEM_MODE_ALL			3	// ��� ����ڿ��� �ش�. 
#define GIVEITEM_MODE_PCROOM		4	// pc�濡�� ������ ����ڿ��� �������� �����Ѵ�.
#define GIVEITEM_MODE_MINLEVEL		5	// �ش� ���� �̻��� �������Ը� ������ ����.
#define GIVEITEM_MODE_VILLAGER		6	// ���� �ֹο��� ����
#define GIVEITEM_MODE_SEQGMCOMMAND	7	// [���] /seq ��ɾ ����ؼ� ����

//----------------------------
// �������� ����ڿ��� �ٶ� ��� ����
//----------------------------
#define GIVEITEM_RESULT_SUCCESS	1
#define GIVEITEM_RESULT_NOINVEN	2

#define MAX_FLY_VIBRATE     8

#ifdef _CHINA
	#define CANFARM_LEVEL			30	// ��� ���� ����
	#define CANMINE_LEVEL			30	// ä�� ���� ����
#else
	#define CANFARM_LEVEL			20	// ��� ���� ����
	#define CANMINE_LEVEL			20	// ä�� ���� ����
#endif


//--------------------------------------
// ��� ���� ���� 
//--------------------------------------
#define CANFARM_ERROR_NOSKILL		1		// ���� ����. 
#define CANFARM_ERROR_NOTOOL		2		// ��ⱸ ����. 
#define CANFARM_ERORR_NORENT		3		// ������ ����� ����. 
#define CANFARM_ERORR_HAVEDISEASE	4		// ������ �ɸ�
#define CANFARM_ERORR_CANNOTLEVEL	5		// ������ �ȵ�
#define CANFARM_ERORR_RENTING		6		// �̹� �ٸ������� �Ӵ����̶� �Ӵ�� �ٽ� �� �ʿ����.

#define CANMINE_ERROR_NOSKILL		1		// ä���� ����. 
#define CANMINE_ERROR_NOTOOL		2		// ä�� �ⱸ ����. 
#define CANMINE_ERORR_NORENT		3		// ������ ä���� ����. 
#define CANMINE_ERORR_HAVEDISEASE	4		// ������ �ɸ�
#define CANMINE_ERORR_CANNOTLEVEL	5		// ������ �ȵ�
#define	CANMINE_ERORR_RENTING		6		// �̹� �ٸ������� �Ӵ����̶� �Ӵ�� �ٽ� �� �ʿ����.


#define MAX_CANADDINV_CHECK_NUM		10		// ���� ���� �������� �ѹ��� �κ��� ���� ������ üũ�Ҷ� �ִ밡����

#define SUMMON_TAKEOUT_DELAY		20		// ��ȯ�� ���ȯ���� ��� �ð�(����: ��)

#define INCREASEMOVESPEED_DELAY		600000
#define INCREASEMOVESPEED_POWER		4
//-----------------------------------------
// ������ ����Ʈ�� �� ���� 
//-----------------------------------------
#define  BASIC_QUEST_LEVEL_OVER100	20	// �׽�Ʈ�� ���� 20���� �Ѵ�.
class cltCharManager;
class cltIDManager;
class cltMapCommon;
class cltMsg;
class CDrawChat;
class cltLetterUnit;
class CExpCounter;
class CHealCounter;
class CCharCriticalEffect;
class cltGameMsgRequest_MakeItemInv;
class cltStatisticsManager;
class cltPersonInfo;
class cltQuestClearConditionInfo;
class cltMapManager;


#define MAX_UPDATE_SWITCH			18
#define  UPDATE_BASICINFO			0
#define  UPDATE_IP					1
#define  UPDATE_SKILL				2
#define  UPDATE_INVENTORY			3
#define  UPDATE_BANK				4
#define  UPDATE_STOCK				5
#define  UPDATE_STOCKORDER			6
#define  UPDATE_MARKET				7
#define  UPDATE_RANK				8
#define  UPDATE_REALESTATE			9
#define  UPDATE_HEALTH				10
#define  UPDATE_QUEST				11
#define  UPDATE_HORSE				12
#define  UPDATE_SUMMON				13
#define  UPDATE_GUILTY				14
//_LEON_GUILD_STOCK
#define  UPDATE_GUILDSTOCK			15
#define  UPDATE_GUILDSTOCKORDER		16
#define	 UPDATE_WORLDMONEY			17



//--------------------------------------------
// ĳ������ ���� �ܰ� 
//--------------------------------------------
#define CHARWORKSTEP_DECIDELENGTH		 	1	
#define CHARWORKSTEP_ACTION        			2
#define CHARWORKSTEP_MOVE	    			3
#define CHARWORKSTEP_RETREAT       			4


//-------------------------------------------
// ĳ������ ������ ���� ���� �޽���. 
//-------------------------------------------
enum CANUSEITEM_ERROR
{
	CANUSEITEM_ERROR_INVALID			= 0,			// ���� �Ҹ�.
	CANUSEITEM_ERROR_DEADCHAR,							//01 ������ ����ڰ� �׾���. 
	CANUSEITEM_ERROR_NOSKILLPOINT,						//02 ��� ������ ���� ���� ���Ұ� 
	CANUSEITEM_ERROR_NOTFITCOND,						//03 ��������� ������Ű�� ����. 
	CANUSEITEM_ERROR_ALREADYMAXSKILL,					//04 �̹� �ְ� �������� ����� ��� ���״�. 
	CANUSEITEM_ERROR_NEEDPARENTSKILL,					//05 �θ��� �ʿ�. 
	CANUSEITEM_ERROR_LIMITSKILLLEVEL,					//06 ��� ��� ����. 
	CANUSEITEM_ERROR_NOUSEABLE,							//07 ���Ӽ��� �ƴϴ�. 
	CANUSEITEM_ERROR_NOHORSE,							//08 ���� �ƴ϶� ����� �� ����. 
	CANUSEITEM_ERROR_NEEDLEVEL,							//09 ��뷹���� �������� ���Ͽ�����Ҽ�����.
	CANUSEITEM_ERROR_NOMORE,							//10 �̹� ���� �־� ����� �� �� ����.
	CANUSEITEM_ERROR_SUMMON_NOMORE,						//11 ��ȯ�� �ִ� ���� ���� 
	CANUSEITEM_ERROR_NOPROPERFISHAREA,					//12 ������ ���� ��� ���ø� �Ҽ� ����.
	CANUSEITEM_ERROR_NOCOUNTRY,							//13 ���� ������ �ƴϴ�.
	CANUSEITEM_ERROR_NOMOREUSE,							//14 ���̻��� �� ����Ѵ�.
	CANUSEITEM_ERROR_NOMORE_DIGEST,						//15 �谡 �θ� ���°� �ƴ϶� ���̻��� �������� ��� ���Ѵ�.
	CANUSEITEM_ERROR_NOMORE_DESEASE,					//16 ���ɾ��� �������� ���� ��� �����ϴ�.
	CANUSEITEM_ERROR_NOUSE_THISPLACE,					//17 �ش���ҿ����� ��� �Ұ�
	CANUSEITEM_ERROR_OVERMAXHORSE,						//18 �ִ밪�̻��� ���� ����Ҽ��� ����.
	CANUSEITEM_ERROR_RIDEHORSEUSEITEM,					//19 ���� �ö�ź ���¿��� �������� ����ߴ�.
	CANUSEITEM_ERROR_CANTOVERSLOT,						//20 ���̻� ������ ��� ��ȯ�� �� ����.
	CANUSEITEM_ERROR_TICKETOVERDATE,					//21 ������ �Ⱓ�� �� �Ǿ���.
	CANUSEITEM_ERROR_BEFOREUSE_SAMEITEM,				//22 �����̾� ������ �̹� ���� ������ ������̴�.
	CANUSEITEM_ERROR_CANNOTUSETYPEGORSE_SAMEITEM,		//23 �����̾� ������ �̹� ���� ������ ������̴�.
	CANUSEITEM_ERROR_CANNOTUSEPREMIUMITEM,				//24 �����̾� ������ �ν������� ��� �ϸ� �������� ����� �Ұ��� �ϴ�.
	CANUSEITEM_ERROR_NOTMARRIED,						//25 ��ȥ���� �ʾҴ�
	CANUSEITEM_ERROR_CANNOT_SAMEMAP,					//26 ���� �ʻ� ���� �ʴ�
	CANUSEITEM_ERROR_ALREADY_MAX_LOVELEVEL,				//27 �̹� �ְ� �������̴�
	CANUSEITEM_ERROR_CAN_NOT_USETIME,					//28 ���� ����Ҽ��ִ� �ð��� �ƴϴ�
	CANUSEITEM_ERROR_CAN_NOT_FAMILY,					//29 �������谡 ����.
	CANUSEITEM_ERROR_NOT_ENOUGH_GET_TREASUR,			//30 ����ã�� �̺�Ʈ�� ���� ������ �ȵȴ�.-�޸��� ����Ʈ�� ������ ����ã�⸦ �Ҽ� �ִ�.-
	CANUSEITEM_ERROR_SOULGUARD_NOMORE,					//31 ���̻� ��ȣ������ ���� �� ����
	CANUSEITEM_ERROR_CANNOT_USE_COOKIE_NO_OVER_TIME,	//32 ���� ��Ű�� �� Ÿ�̹��� �ȵƴ�
	CANUSEITEM_ERROR_SKILL_BOOK,						//33 ��ų��.
	CANUSEITEM_ERROR_SKILL_BOOK_SUB_MAGIC_FULL,			//34 ��ų�� ���� ���� 3�� �̻� ������ �Ұ�.
	CANUSEITEM_ERROR_BATTLEROYALMAP							    //35 ��Ʋ�ξ� �� ����
};



#define BASIC_PLAYERMASTER_LEVEL			90	// �÷��̾� ��� �⺻ ����
#define BASIC_GAMEMASTER_LEVEL				100	// ��� �⺻ ����

#define CHAR_ACTION_INTERVAL_FRAME			6	// ĳ���� ������ �̷������ ������ ����.

//-------------------------------------------
// ĳ������ ���� ���� ���� �޽���. 
//-------------------------------------------
#define	CANUSEMAGIC_ERROR_INVALID			0		// 
#define	CANUSEMAGIC_ERROR_NEEDMANA			1		// ���� ���� 
#define	CANUSEMAGIC_ERROR_FARDISTANCE		2		// MAX Distance�� �Ѿ��.
#define	CANUSEMAGIC_ERROR_NEEDTIMEDELAY		3		// ���� Delay �ð��� �ʿ��ϴ�.
#define CANUSEMAGIC_ERROR_NOTENOUGHSKILL	4		// ��������� �����Ͽ� ��� �Ұ�. 

enum {	CAPTIONKIND_NEWSCHAT, 
		CAPTIONKIND_STOCK,
		CAPTIONKIND_NEWS, 
		CAPTIONKIND_MARKET,
		CAPTIONKIND_PERSONALSHOP, 
		CAPTIONKIND_GUILD, 
		CAPTIONKIND_COLORNEWSCHAT,
		CAPTIONKIND_END				};


#define MAX_SHOP_ITEM_NUMBER				5
#define MAX_SHOP_MAKEITEM_NUMBER			1		// MAX_SHOP_ITEM_NUMBER 5 ���� �۰ų� ���ƾ��Ѵ�.
#define MAX_SHOP_TITLE_LENGTH				21		// ���� Ÿ��Ʋ�� �ִ� ���� ũ��

//---------------------------------
// ���λ��� 
//---------------------------------
#define PSHOP_MODE_NONE						0		// ���� ��尡 ����.						
#define PSHOP_MODE_BUY						1		// ���� ��� ��� 
#define PSHOP_MODE_SELL						2		// ���� ��� �ȱ� 
#define PSHOP_MODE_MAKEITEM					3		// ���� ��� ������ �����Ƿ�	-	������ �Ƿ� �ϱ⸦ ���ϴ� ��� 
#define PSHOP_MODE_MAKEITEM_WANT			4		// ���� ��� ������ �����Ƿ�	-	������ �ϱ⸦ ���ϴ� ��� 

#define	SUMMON_DECREASESTAMINA_AMT			10		// ��ȯ���� �⺻ ���¹̳� �Ҹ�( 1�д�)
#define	MAX_SUMMON_TRANSFORM_TIME			600		// [����] ��ȯ�� ���� ���׹̳� �ִ� 600 (60��) 
#define	SUMMON_POSSIBLE_TRANSFORM_TIME		10		// [����] ��ȯ�� ���� ���׹̳� �ִ�  10 ( 1��) 



//--------------------------------
// ��������
//--------------------------------

#define MAKE_ANI_ARMOR	1
#define MAKE_ANI_HEAL	2
#define MAKE_ANI_FOOD	3

#define ENCHANT_ANI_WEPONE 101
#define ENCHANT_ANI_ARMOR 102

//KHY - 1014 - �漮 �߰�.
#define MAX_CUSHION_NUM 5

//[����] �Ϸ絿�� ������ �� �ִ� Ƚ��.
#define MAX_DAILY_QUESTION_NUM 5

#define MAX_EXPLAIN_LENTH	1024


//---------------------------------
// ���λ��� 
//---------------------------------
class  cltShopTradeData
{
public:
	SI08		    m_siShopMode;			// PSHOP_MODE_BUY, PSHOP_MODE_SELL
	SI32			m_siPersonID;
	TCHAR			m_szAccountID[MAX_PLAYER_NAME];
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem,	MAX_SHOP_ITEM_NUMBER>		m_clItem;
	NSafeTArray<SI16,		MAX_SHOP_ITEM_NUMBER>		m_siSelectedInventoryPos;
	NSafeTArray<GMONEY,		MAX_SHOP_ITEM_NUMBER>		m_siPrice;
	NSafeTArray<GMONEY,		MAX_SHOP_ITEM_NUMBER>		m_siCurrentPrice;
#else
	cltItem			m_clItem[ MAX_SHOP_ITEM_NUMBER ];
	SI16			m_siSelectedInventoryPos[ MAX_SHOP_ITEM_NUMBER ];
	GMONEY			m_siPrice[ MAX_SHOP_ITEM_NUMBER ];
	GMONEY			m_siCurrentPrice[ MAX_SHOP_ITEM_NUMBER ];
#endif
	SI16			m_siHandPoint;	// ���� �������̽� ���� ���Ŀ��� ����� ���
	SI16			m_siSkillLevel;
	TCHAR			m_szShopTitle[MAX_SHOP_TITLE_LENGTH];
	bool			m_bPremium;
	
	cltItem			m_clSpacialItem;									//[����] �к� �����̾� ���� �̿�� �������� ��ϵȴ�.
	SI16			m_siSelectedSpacialInventoryPos;					//[����] ��ġ�� ��ϵȴ�.

	cltShopTradeData();

	void Init();
	void InitData();

	void Set(cltShopTradeData *pclData);
	void SetCurrentPrice(cltItemManagerCommon *pclitemmanager);
};

//---------------------------------
// ���λ��� ��� 
//---------------------------------
class  cltShopBannerData
{
public:
	SI08		    m_siShopMode;			// PSHOP_MODE_BUY, PSHOP_MODE_SELL

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16,	MAX_SHOP_ITEM_NUMBER>		m_siUnique;
	NSafeTArray<GMONEY,	MAX_SHOP_ITEM_NUMBER>		m_siPrice;
#else
	SI16			m_siUnique[ MAX_SHOP_ITEM_NUMBER ];
	GMONEY			m_siPrice[ MAX_SHOP_ITEM_NUMBER ];
#endif
	SI16			m_siHandPoint;
	SI16			m_siSkillLevel;
	TCHAR			m_szShpoTitle[MAX_SHOP_TITLE_LENGTH];
	bool			m_bPremium;

	cltShopBannerData();
	void Init();
	void Set(cltShopBannerData *pclBanner);
	void SetData(cltShopTradeData *pclData);
	void MakeBannerText(cltItemManagerCommon* pclItemManager, TCHAR *ptext,TCHAR *pShopTitle = NULL);
};

//---------------------------------
// �����Ƿ�
//---------------------------------
class  cltShopRepairData
{
public:
	SI32			m_siPersonID;
	TCHAR			m_szAccountID[MAX_PLAYER_NAME];

	cltItem			m_clRepairItem;
	SI16			m_siRepairItemPos;
	GMONEY			m_siPrice;

    RepairItemExtraMaterial	m_kMaterial;

	cltShopRepairData();

	void Init();
	void InitData();

	void Set( cltShopRepairData *pclData );
	bool ExistItem( SI16 siPos, cltItem* pclitem );
};

//---------------------------------
// ���λ��� �˻� ���� 
//---------------------------------
#define MAX_SEARCHSHOP_ITEM_NUMBER			50

class cltSearchShopData	
{
public:
	SI32	m_siShopMode;
	SI32	m_siItemUniqueType;
	GMONEY	m_siItemSearchPrice;
	
	TCHAR	m_szName[MAX_SEARCHSHOP_ITEM_NUMBER][MAX_PLAYER_NAME];

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siLevel;

	NSafeTArray<SI16,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siMapIndex;
	NSafeTArray<SI32,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siMapX;
	NSafeTArray<SI32,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siMapY;

	NSafeTArray<cltItem, MAX_SEARCHSHOP_ITEM_NUMBER>	m_clItem;
	NSafeTArray<GMONEY,  MAX_SEARCHSHOP_ITEM_NUMBER>	m_siPrice;

	NSafeTArray<SI16,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siHandPoint;
	NSafeTArray<SI16,	MAX_SEARCHSHOP_ITEM_NUMBER>		m_siSkillLevel;
#else
	SI32	m_siLevel[MAX_SEARCHSHOP_ITEM_NUMBER];

	SI16	m_siMapIndex[MAX_SEARCHSHOP_ITEM_NUMBER];
	SI32	m_siMapX[MAX_SEARCHSHOP_ITEM_NUMBER];
	SI32	m_siMapY[MAX_SEARCHSHOP_ITEM_NUMBER];

	cltItem m_clItem[MAX_SEARCHSHOP_ITEM_NUMBER];
	GMONEY  m_siPrice[MAX_SEARCHSHOP_ITEM_NUMBER];
	
	SI16	m_siHandPoint[MAX_SEARCHSHOP_ITEM_NUMBER];
	SI16	m_siSkillLevel[MAX_SEARCHSHOP_ITEM_NUMBER];
#endif
	
	cltSearchShopData();
	void Init();
	
	void CopyGeneralData(cltSearchShopData *pclData);
	void CopyData(SI32 index1, SI32 index2, cltSearchShopData *pclData);
	void ClearData(SI32 index1);
	void MoveData(SI32 index1, SI32 index2, cltSearchShopData *pclData);
	void Set(cltSearchShopData *pclData);
};

//---------------------------------
// �ǰ� ����. 
//---------------------------------
class cltBeHitInfo{
public:
	bool 			bBeAttackedSwitch;
	SI16			siAttackerID;

	cltBeHitInfo();
	void Init();
	void Set(bool bhitswitch, SI16 attackerid);
};


class cltJim{
public:
	SI32	siJimHostCharUnique;		// ���� ��ü ĳ����. 
	SI32	siJimSlaveCharUnique;		// ����� ĳ����. 
	DWORD	dwJimFrame;					// ����� ������. 
	DWORD	dwNewJimFrame;				// �űԷ� ����� ������. 

	cltJim();
	void Init();

	bool SetJim(SI32 slavecharunique);	// ���ϴ�. 
	bool SetBeJimed(SI32 hostcharunique, DWORD frame);		// �� �Ǵ�. 
};


// ������� �α��ν� ������ Ŭ���̾�Ʈ�� ������ ĳ������ ������ ���� Ŭ����
// ���� �Ʒ��� �ִ� cltUserCharInfo �� ����ϸ� ���� �������� cltPersonInfo �� �뷮�� 
// �ʹ� ũ�� ĳ���� ���� ȭ�鿡�� ���� �ʿ���� ���������� �����ϰ� �����Ƿ� ������ Ŭ������ 
// �������. 
class cltCharListInfo{
public:
	cltPBasicInfo			clBI;			// ĳ������ ���� �⺻�� �Ǵ� ����. 
	cltPIPInfo				clIP;			// �ٽ����� ����. 	
	/*
#ifdef _SAFE_MEMORY
	NSafeTArray<cltItem, MAX_SHAPE_ITEM>		clCharItem;
#else
	cltItem					clCharItem[MAX_SHAPE_ITEM];		// ������ ���� ��� ���õ� ����.
#endif
	*/
	SYSTEMTIME				DelCharTime;	// �ɸ��ͻ��������Ⱓ�� ���� �߰��� �ý��۽ð�
	
public:	

	cltCharListInfo();
	void Init();
	void Set(cltCharListInfo* pclinfo);
};


//-----------------------------------
// ��ȯ���� ���� 
//-----------------------------------
#define SUMMON_STATUS_TAKEOUT		1
#define SUMMON_STATUS_TAKEIN		2
#define SUMMON_STATUS_DEAD			3

#define SUMMON_ATTACKTYPE_ACTIVE	1
#define SUMMON_ATTACKTYPE_AVOID		2

#define SUMMON_IDENTITY_NORMAL		0
#define SUMMON_IDENTITY_ITEMMALL	1


#define LIMIT_LEVEL_HATCH_DOLL		20		// Level�� 20�� �Ǿ�� ��ȯ�� ����Ҽ� �ִ�.	
#define HATCH_SUMMON_PERCENT		60		// 10% Ȯ�� 
#define BASICTICKET_SUMMON_RANK_EVOLVE	7	// 6 �ܰ� ������ �⺻ Ƽ������ ��ȭ�� �ȴ�.
#define LIMIT_SUMMON_RANK_EVOLVE		1000	// ��ȯ�� ��ȭ ���� ���� (������ ���ٰ� ������ )
#define LIMIT_SUMMON_ADD_SCROLL_PERCENT	300	// ��ȯ�� ��ũ�� ��ȭ PERCENT (1000 ����)

inline SI32 GetSummonTicketNum(SI32 SummonRank)
{

	if( SummonRank < BASICTICKET_SUMMON_RANK_EVOLVE )	// 6��� �̸��϶��� ��ȭ�̿�� 1������ ����ϴ�.
	{
		return 10 ;
	}

	SI32 siTicketNum = 1;

	siTicketNum = ( SummonRank/8 + 1 ) * 10 ;

	if ( SummonRank == 48 )
	{
		return 200 ;
	}
	else if ( SummonRank == 46 || SummonRank == 47)
	{
		return 100 ;
	}
	else if ( SummonRank >= 39 )
		return min(50, siTicketNum);	// �൹ ���� ����	

	return min(40, siTicketNum);		// �൹ ���� ����	
}

// ���� 6�ܰ� �̸��� ��ȯ�� �ϰ�� Ƽ������ ��ȭ ��Ų��.
inline SI32 GetSummonTicketUnique(SI32 SummonRank)
{
	if( SummonRank < BASICTICKET_SUMMON_RANK_EVOLVE )	// 6��� �̸��϶��� ��ȭ�̿�� 1������ ����ϴ�.
	{
		return ITEMUNIQUE(24015);
	}

	return ITEMUNIQUE(5370);		// �൹ ���� ����	
}

//inline SI32 GetSummonTicketNum(SI32 SummonRank)
//{
//	SI32 siTicketNum = 1;
//	siTicketNum = SummonRank/8 + 1;
//
//	if ( SummonRank >= 39 )
//		return min(5, siTicketNum);					// ��ȭ�̿�� ���� ����	
//
//	return min(4, siTicketNum);					// ��ȭ�̿�� ���� ����	
//}




//-------------------------------------------
// ĳ���Ͱ� �̵��ϰ� �Ǵ� ���.
//-------------------------------------------
#define MAX_CHAR_MOVE_POINT 10
class cltMovePointList{
public:
	SI32	siPointNum;					// ����� ����. 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltPos, MAX_CHAR_MOVE_POINT>	clPos;
#else
	cltPos	clPos[MAX_CHAR_MOVE_POINT];	// ���� �̵� ���. 
#endif

	cltMovePointList();
	void Init();
	bool AddPos(SI32 six, SI32 siy);
	bool IsArrive(SI32 six, SI32 siy);		// ù��° ������ �����ߴ°�?

	// ù��° ������ ����ó��.
	void Arrive();
};

//------------------------------------------
// ĳ���� �̵� ���� ����. 
//------------------------------------------
class cltCharMoveInfo{
public:
	SI32			siDX, siDY;			// ������ 
	SI32			siMovePercent;		// �̵� %
	SI32			siSparePercent;		// ������ %
	SI32 			siNX, siNY;			// ĳ������ ���� ��ġ 
	SI32			siStepWidth;        // �̵� ����

	DWORD			dwLastMoveClock;	// ���������� �̵���ġ�� �ð�. 	


	cltCharMoveInfo();
	void Init();
	
	SI32 IncMovePercent(SI32 movespeed);		// �̵� %�� ������Ų��. 
};



class cltCharCommonSimpleVary{
public:
	bool	bForceparametaBoxActionSwitch;					// ParametaBoxAction�� ������ �����ϰ� �ϴ� ����. 
	DWORD	dwLastCheckParametaBoxActionClock;				// ParametaBoxAction�� ���������� ������ �ð�. 

	cltCharCommonSimpleVary();
};

class cltFairyStoreInfo
{
public:
	SI08	siIndex;
	
	UI08 	uiDateYear;
	UI08 	uiDateMonth;
	UI08 	uiDateDay;
	UI16 	uiDateUseDay;

	cltFairyStoreInfo()
	{
		Init();
	}

	void Init()
	{
		siIndex			= 0;
		uiDateYear		= 0;
		uiDateMonth		= 0;
		uiDateDay		= 0;
		uiDateUseDay	= 0;
	}

	void Set(cltFairyStoreInfo* pclFairyStoreInfo)
	{
		if(pclFairyStoreInfo == NULL)		return;

		siIndex			= pclFairyStoreInfo->siIndex;
		uiDateYear		= pclFairyStoreInfo->uiDateYear;
		uiDateMonth		= pclFairyStoreInfo->uiDateMonth;
		uiDateDay		= pclFairyStoreInfo->uiDateDay;
		uiDateUseDay	= pclFairyStoreInfo->uiDateUseDay;
	}
};

class cltFairyInfo
{
public:
	// �� ����� 3��
	cltFairyStoreInfo	clFairyHorseStore[3];

	// ������ ����� 3��
	cltFairyStoreInfo	clFairyItemStore[3];

	// DB���� �޾Ƽ� �����ϰ� �ִ� ���� �����
	SI16			siCurFairyHorseStore;
	SI16			siCurFairyItemStore;

	// �� 5��
	cltHorse		clFairyHorse[5];

	// ������ 30��
	cltItem			clFairyItems[30];
};

//[����] ��ų������ ȹ���� ����
class cltSkillBookMagic
{
public:
	enum 
	{
		LIMIT_DAY = 12,	// ���� ��� ���� �ð�.(��)
	};


	cltSkillBookMagic( void )	
	{
		Clear();
	}
	void Clear( void )
	{
		m_siSkillUnique = 0;
		m_siMagicKind	= 0;
	}

	cltSkillBookMagic( SI32 _siSkillUnique, SI32 _siMagicKind, SYSTEMTIME* _pstStartTime = NULL )	
	{
		m_siSkillUnique = _siSkillUnique;
		m_siMagicKind	= _siMagicKind;

		if( _pstStartTime )
			memcpy( &m_stTime, _pstStartTime, sizeof(m_stTime) );
		else
			ZeroMemory( &m_stTime, sizeof(m_stTime) );	
	}
	cltSkillBookMagic( cltSkillBookMagic* _pclSkillBookMagic )	
	{
		memcpy( this, _pclSkillBookMagic, sizeof(*this) );
	}
	~cltSkillBookMagic(){}

	void		Set( cltSkillBookMagic* _pclSkillBookMagic )		{	memcpy( this, _pclSkillBookMagic, sizeof(*this) );	}

	void		SetSkillUnique( SI32 _siSkillUnique )				{	m_siSkillUnique = _siSkillUnique;					}
	SI32		GetSkillUnique( void )								{	return m_siSkillUnique;								}

	void		SetMagicKind( SI32 _siMagicKind )					{	m_siMagicKind = _siMagicKind;						}
	SI32		GetMagicKind( void )								{	return m_siMagicKind;								}

	void		SetStartTime( SYSTEMTIME* _pstStartTime )			{	memcpy( &m_stTime, _pstStartTime, sizeof(m_stTime) );	}
	SYSTEMTIME*	GetStartTime( void )								{	return &m_stTime;									}

	bool		IsTimeOver( SYSTEMTIME* _stCurTime )				
	{
		if( 0 >= m_siMagicKind || 0 >= m_siSkillUnique )	return false;
		if( 0 == m_stTime.wYear )							return false;
		 		
		if( LIMIT_DAY <= DiffDate( _stCurTime, &m_stTime ) )
		{
			m_stTime.wYear = 0;
			return true;
		}

		return false;
	}

	SI32		m_siSkillUnique;	// ������ ������ִ� ���(��, ����, â��...)
	SI32		m_siMagicKind;		// ������ ����
	SYSTEMTIME	m_stTime;			// ���� ȹ�� �ð� (���ǽð�)
};

//[����] ��ų������ ���� ����
class cltSkillBookSubMagic
{
public:
	enum 
	{
		LIMIT_DAY = 30,	// ���� ��� ���� �ð�.(��)
	};

	cltSkillBookSubMagic( void )	
	{
		ZeroMemory(this, sizeof(*this));	
	}
	cltSkillBookSubMagic( SI32	_siSkillUnique, SI32 _siParentMagicKind, SI32 _siMagicKind, SYSTEMTIME* _pstStartTime = NULL)	
	{
		m_siSkillUnique		= _siSkillUnique;
		m_siParentMagicKind = _siParentMagicKind;
		m_siMagicKind		= _siMagicKind;

		if( _pstStartTime )
			memcpy( &m_stTime, _pstStartTime, sizeof(m_stTime) );
		else
			ZeroMemory( &m_stTime, sizeof(m_stTime) );	
	}
	cltSkillBookSubMagic( cltSkillBookSubMagic* _pclSkillBookSubMagic )	
	{
		memcpy( this, _pclSkillBookSubMagic, sizeof(*this ) );
	}
	~cltSkillBookSubMagic()	{}

	void Clear( void )
	{
		m_siParentMagicKind = 0;
		m_siMagicKind		= 0;
	}

	void		Set( cltSkillBookSubMagic* _pclSkillBookSubMagic )		{	memcpy( this, _pclSkillBookSubMagic, sizeof(*this) );	}

	void		SetSkillUnique( SI32 _siSkillUnique )					{	m_siSkillUnique = _siSkillUnique;						}
	SI32		GetSkillUnique( void )									{	return m_siSkillUnique;									}

	void		SetParentMagicKind( SI32 _siParentMagicKind )			{	m_siParentMagicKind = _siParentMagicKind;				}
	SI32		GetParentMagicKind( void )	const						{	return m_siParentMagicKind;								}

	void		SetMagicKind( SI32 _siMagicKind )						{	m_siMagicKind = _siMagicKind;							}
	SI32		GetMagicKind( void )		const						{	return m_siMagicKind;									}

	void		SetStartTime( SYSTEMTIME* _pstStartTime )				{	memcpy( &m_stTime, _pstStartTime, sizeof(m_stTime) );	}
	SYSTEMTIME*	GetStartTime( void )									{	return &m_stTime;										}

	bool		IsTimeOver( SYSTEMTIME* _stCurTime )				
	{
		if( 0 >= m_siMagicKind || 0 >= m_siParentMagicKind )	return false;
		if( 0 == m_stTime.wYear )								return false;

		if( LIMIT_DAY <= DiffDate( _stCurTime, &m_stTime ) )
		{
			m_stTime.wYear = 0;
			return true;
		}

		return false;
	}

	friend bool operator==( const cltSkillBookSubMagic& _LValue, cltSkillBookSubMagic& _RValue );

	SI32		m_siSkillUnique;		// ������ ������ִ� ���(��, ����, â��...)
	SI32		m_siParentMagicKind;	// ���������� ������ִ� ����
	SI32		m_siMagicKind;			// ���������� ����
	SYSTEMTIME	m_stTime;				// ���� ȹ�� �ð� (���ǽð�)
};

//[����] ��ų�ϰ��� ĳ���� ����
#define MAX_SKILLBOOK_SUBMAGIC_NUM 30 // ���������� ������ �ִ� 30���̴�.
#define SKILLBOOK_MAGIC_NUM			6
class cltCharSkillBookInfo : public NkMemory 
{
public:
	cltCharSkillBookInfo( void )	
	{
		Clear();
	}
	~cltCharSkillBookInfo( void )	
	{
		m_clSkillBookSubMagicList.RemoveAll();
	}
	void							Clear( void );
	bool 							IsSkillBookMagic( void );
	void							SetSkillBookMagic( IN SI32 _siIndex, cltSkillBookMagic* _pclAddSkillBookMagic );
	void 							AddSkillBookMagic( IN SI32 _siAttackType, IN cltSkillBookMagic* _pclAddSkillBookMagic );
	cltSkillBookMagic*				GetSkillBookMagicIndex( IN SI32 _siIndex );
	void 							DelSkillBookMagic( IN SI32 _siAttackType );
	void 							AddSkillBookSubMagic( IN cltSkillBookSubMagic _clAddSkillBookSubMagic );
	cltSkillBookSubMagic*			FindSkillBookSubMagicFromParentMagic( IN SI32 _siParentMagic );
	stMagicAttributeData*			FindMagicAttributeDataFromParentMagic( IN SI32 _siParentMagic, OUT SI32& _siSubMagicKind );
	void							DelSkillBookSubMagic( IN const cltSkillBookSubMagic _clAddSkillBookSubMagic );
	SI32							GetIndexFromAttackType( IN SI32 _siAttackType );
	cltSkillBookMagic*				GetSkillBookMagic( IN SI32 _siAttackType );			
	NkList<cltSkillBookSubMagic>*	GetSkillBookSubMagicList( void );
	bool							IsTimeOver( IN cltCharServer* _pclChar );
	bool							IsFullSubMagic( IN SI32 _siSkillunique );
	
		
private:
	NSafeTArray<cltSkillBookMagic, SKILLBOOK_MAGIC_NUM>		m_clSkillBookMagic;
	NkList<cltSkillBookSubMagic>							m_clSkillBookSubMagicList;
};

// ĳ���Ϳ��� ���ظ� �ִ� ��.
class cltCharCurseEffect
{
public:
	enum CURSE_EFFECT
	{
		CURSE_NONE		= 0x00000000,
		CURSE_ATTACK	= 0x00000001,
		CURSE_DEFENSE	= 0x00000002,
		CURSE_DODGE		= 0x00000004,
		CURSE_HIT		= 0x00000008,
	};

	cltCharCurseEffect()	{ m_dwCurseType = CURSE_NONE;	}
	~cltCharCurseEffect()	{								}

	void SendMsgCurseInfo( SI32 _siTargetID );
	
	void Clear( void )
	{
		ZeroMemory( this, sizeof(*this) );
		
		m_dwCurseType = CURSE_NONE; // �ϳ��� ����
	}

	void SetCurse( cltCharCurseEffect* _pclCharCurseEffect, SI32 _siTargetID )
	{
		m_dwCurseType   = _pclCharCurseEffect->m_dwCurseType;   
		m_siPara		= _pclCharCurseEffect->m_siPara;		
		m_dwStartClock  = _pclCharCurseEffect->m_dwStartClock ;			
		m_dwClock		= _pclCharCurseEffect->m_dwClock;		

		SendMsgCurseInfo( _siTargetID );
	}

	void SetCurse( DWORD _dwCurse, DWORD _dwClock, SI32	_siPara, SI32 _siTargetID )
	{ 
		m_dwCurseType	= CURSE_NONE; // �ϳ��� ����

		m_dwCurseType   = _dwCurse; 
		m_siPara		= _siPara;
		m_dwStartClock  = pclClient->CurrentClock;			
		m_dwClock		= _dwClock;

		SendMsgCurseInfo( _siTargetID );
	}

	bool IsCurse( DWORD _dwCurse, SI32 _siTargetID )
	{
		switch( m_dwCurseType )
		{
		case CURSE_ATTACK:
		case CURSE_DEFENSE:
		case CURSE_DODGE:
		case CURSE_HIT: 
			{
				if(	   pclClient->GameMode == GAMEMODE_SERVER
					&& (DWORD)TABS(pclClient->CurrentClock - m_dwStartClock) > m_dwClock )	
				{
					m_dwCurseType = CURSE_NONE; 
					SendMsgCurseInfo( _siTargetID );
				}
			}
			break;
		}
		return m_dwCurseType & _dwCurse ? true : false;
	}

	DWORD GetCurse( SI32 _siTargetID ) 
	{ 
		switch( m_dwCurseType )
		{
		case CURSE_ATTACK:
		case CURSE_DEFENSE:
		case CURSE_DODGE:
		case CURSE_HIT: 
			{
				if(    pclClient->GameMode == GAMEMODE_SERVER
					&& (DWORD)TABS(pclClient->CurrentClock - m_dwStartClock) > m_dwClock )	
				{
					m_dwCurseType = CURSE_NONE; 
					SendMsgCurseInfo( _siTargetID );
				}
			}
			break;
		}

		return m_dwCurseType;
	}

	bool IsTimeOver( SI32 _siTargetID )
	{
		if( m_dwCurseType == CURSE_NONE ) return false; 

		if(    pclClient->GameMode == GAMEMODE_SERVER
			&& (DWORD)TABS(pclClient->CurrentClock - m_dwStartClock) > m_dwClock )	
		{
			m_dwCurseType = CURSE_NONE; 
			SendMsgCurseInfo( _siTargetID );
			return true;
		}
		return false;
	}

	SI32 GetPara( void ) 
	{ 
		return m_siPara;
	}

	SI32 Dead( SI32 _siTargetID ) 
	{ 
		m_dwCurseType = CURSE_NONE; 
		SendMsgCurseInfo( _siTargetID );
		return true;
	}

private:
	DWORD	m_dwStartClock;	// ���� �ð�.
	DWORD	m_dwClock;		// ���� �ð�.
	DWORD	m_dwCurseType;
	SI32	m_siPara;
};





//-------------------------------------------
// cltCharCommon(Ŭ���̾�Ʈ �������� ���� ���Ǵ� ĳ���� Ŭ������ Parent
//-------------------------------------------
class cltCharCommon : public ITZPerson{
protected:
	cltCharManager* pclCM;
	SI32 			siCenterX, siCenterY;           // ĳ������ �߽� ��ǥ(������ǥ) 

	//------------------------------
	// ��� 
	//------------------------------
	cltOrderDataInfo	clCurOrder;					// ���� �����ϴ� ���. 
	cltOrderDataInfo	ReserveOrder;				// ���� ������ ���. 

	bool				bBusySwitch;   				// �������� ���� �ִ°� ? (true�̸� false�� �ɶ� ���� �ٸ� ���� �Ҵ���� �ʴ´�.) 
	SI16				siSubOrder;					// �������� �۾��� ���� �ܰ�. 
	
	//----------------------------
	// �̵� 
	//----------------------------
	cltMovePointList	clMovePointList;				// ĳ������ �̵����. 
	SI16				siMoveMapIndex;					// �̵��� ������ ���� �� �ε���. 

	//-----------------------------
	// ���� ���� 
	//-----------------------------
	SI16				siReservedTopSkillUnique;		// ���� ����Ǿ� �ִ� ž ��� 
public:

	SI16				siAccountStatus; 
	SI32				siIDNUM;
	

	//---------------------------
	// ���� 
	//---------------------------
	cltMapCommon*		pclMap;							// ĳ���Ͱ� Ȱ���� ���� 

 
	//-----------------------------
	// �ź�
	//-----------------------------
    SI16				siID;
	SI16				CharUnique;
	cltIdentity			clIdentity;
	SI16				siChildCharUnique;
	SI16				siSummonIndex;		// ���� ���忡�� ���� �����ִ� ��ȯ���� ����ũ. 

	//-----------------------------
	// [����] ��ȣ����_090525
	//-----------------------------
	SI16				siMySoulGuardUnique;	// ���� �ҷ��� ��ȣ���� ����ũ
	DWORD				clockSoulGuardCoolTime;	// Ư���ɷ� ��Ÿ��(���� ������ �ð� �̻��� �Ǿ�� �ɷ��� ��)
	cltSoulGuard*		pclSoulGuard;			// ��ȣ����

	//-----------------------------
	// []
	//-----------------------------
	cltCharSkillBookInfo*	pclCharSkillBookInfo;
	cltCharCurseEffect		m_clCharCurseEffect;

	//--------------------------------
	// ������ ���� ���� ����
	//--------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, 29>		siInvMakeItemIndex;
#else
    SI32			siInvMakeItemIndex[29];
#endif

	//--------------------------------
	// ��æƮ�� ���� ���� ����
	//--------------------------------
	SI16			siOrgInvEnchantInx;  
	SI16			siMatInvEnchantInx;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, NOW_ENCHANT_NUMBER>	siElementEnchantInx;
#else
	SI16			siElementEnchantInx[NOW_ENCHANT_NUMBER];
#endif
	SI16			siElementType;
	
	//������ ��带 ���� ����Ʈ ������ ����
	cltItem			clMouseInvItem;
	SI16			siMouseInvItem;

public:
#ifdef _SAFE_MEMORY
	static NSafeTArray<SI32, MAX_CHAR_NUMBER>		CharUniqueInfo;
#else
	static	SI32	CharUniqueInfo[MAX_CHAR_NUMBER];	
#endif

	bool			bGodMode;
	bool			bOneKill;			// ��ų���

	cltCharAddStatusInfo clAddInfo;					// Ư�� ĳ���Ϳ��Ը� �����ϴ� ������ 

	//----------------------------
	// ���� ��� 
	//----------------------------
	cltAttackTarget	clAttackTarget;
	SI16 siCurrentAttackType;					// ���� ���ݵ��� Ÿ�� 

protected:

	//-----------------------------
	// �Ӽ��� 
	//----------------------------
	SI32			Atb;
	SI32			DefenceAtb;


	BOOL			bActiveNPC;



public:
	cltPersonInfo*			pclCI;					// DB�� ����Ǿ�� ĳ������ �߿������� ���� ����. 
	cltParametaBox			clPB;					// ĳ������ �ൿ�� �����ϴ� �Ķ��Ÿ���� Ŭ����. 

	cltKindInfo*			pclKI;
	cltGMCommandKindInfo*	pclGMCommandKindInfo;

	//--------------------------
	// ģ�� ����.
	// cltPersonInfo���� �и�
	// �޸� ���� - �����ͷ� ����
	//--------------------------
	//cltFriendInfo	clFriendInfo;
	cltFriendInfo* pclFriendInfo;

	//_LEON_GUILD
	//------------------------------------
	// ���κ� ������ġ ���� ���� �ӽ� ����
	//-----------------------------------
    SI32					siExpForMyGuild;		// ��� Ż��� �ʱ�ȭ �ʿ�
	//------------------------------------
	// ���κ� ������ͱ� ���� ���� �ӽ� ����
	//-----------------------------------
    cltMoney				clProfitForMyGuild;		// ��� Ż��� �ʱ�ȭ �ʿ�


	//------------------------------------
	// pclCM
	//-----------------------------------
	void SetpclCM(cltCharManager* pclcm);

	//-------------------------------------------------------------
	// �浹 ���� ����. 
	//------------------------------------------------------------
	SI32 			SelfBlock;                   				// ��ü �浹 �Ӽ� 
	DWORD 			Block;                         				// �浹�ϴ� �Ӽ� 

	BOOL 			SetIDSwitch;                            // ������ ������ �����ߴ��� ���θ� ����Ѵ�.

	//----------------------------------
	// ��°� ����� ������ 
	//----------------------------------
	SI16 			Animation;					// � ������ �ִϸ��̼��� �����ϴ°�?
	SI16			HeroAnimation;
	bool 			bUpdateAnimationSwitch;		// �ִϸ��̼��� �����������θ� �˷��ش�. 
	SI16 			Frame;                		// ���� ��� �ܰ踦 �����ϰ� �ִ°�?

	// ���� ���� 
	SI16 			MaxWaitType;   // �� ������ ���� �ִϸ��̼����� ���� �� �ִ� �ִ��� ���� 
	SI16 			WaitType;       // ���� �� ������ ���ϰ� �ִ� ���� �ִ� 

	//----------------------------
	// ���� 
	//----------------------------
	SI16			siDirection;                     				// ���� 
	SI16			TempDirection;                				// 16������ �����ϴ°�?
	SI16			TargetDirection;               				// ��ǥ�� ���� 

	//------------------------------
	// ���ݰ��� 
	//------------------------------
	DWORD			dwAttackGiveUpDelay;		// ���� ���� �ð�.( �� �ð��� ��� ������ ������ �������� ���ϸ� ���� ����) 
	DWORD			dwLastAttackClock;			// ������ ���� ���� �ð�. 
	DWORD 			dwLastAttackIntervalClock;
	DWORD			dwLastMagicClock;			// ���������� ������ ������ �����Ϸ��� �ߴ� �ð�. 

	DWORD			dwLastTorpedoClock;			// ���������� ������ ��ڸ� ����� �ߴ� �ð�

	SI16			ActiveWeapon;				// ���� Ȱ��ȭ�� Weapon 1 or 2
	SI16			ActiveClothes;				// ���� �������� �� 
	SI16            ActiveHat;

	//---------------------------
	// �̵�
	//---------------------------
	cltCharMoveInfo clMoveInfo;

	//---------------------------
	// ��� 
	//---------------------------
	SI16 siFarmX, siFarmY;


	//---------------------------
	// ä��
	//---------------------------
	SI16 siMineX, siMineY;


	// -----------
	// �ִϸ޴ϼ� 
	//------------
	DWORD		dwAniStartClock;
	cltAniInfo	clAniInfo;
	CCharacterDrawing* pclCharDraw;						// ������ ĳ���� ��¿� Ŭ����. 
	bool		bHitDoneSwitch;							// Ÿ���� �̹� ��������. 

	//------------------------------------
	// ���� ���õ� ���� 
	//------------------------------------
	SI16	siCurrentMagic;
	SI08	siCurrentMagicCastType;

	//------------------------------------
	// ���� ������. 
	//------------------------------------
	cltInnerStatusInfo		clInnerStatus;

	//------------
	// �ߵ� ���� 
	//------------
	SI16	siPoisonCharUnique;			// ���� �ߵ���Ų ĳ���� ����ũ. 
	DWORD	dwPoisonLastClock;			// �ߵ��� �����ð�. 
	DWORD	dwPoisonStartClock;			// �ߵ� ���۽ð�. 
	SI32	siPoisonPower;				// �ߵ��� ����. 
	DWORD	dwPoisonCheckClock;			// �����ð����ݸ��� �˻��ؼ� Life�� �ٿ��ֱ����� �ӽ� �ð� ���� 
	

	//-------------
	// ���� ���� 
	//-------------
	DWORD	dwIceLastClock;
	DWORD	dwIceStartClock;

	//----------------------
	// ������ ���� ����
	//-----------------------
	DWORD	dwFrozenLastClock;
	DWORD	dwFrozenStartClock;


	//----------------------
	// ����
	//-----------------------
	DWORD	dwStunLastClock;
	DWORD	dwStunStartClock;


	//-------------
	// ���ݷ� ���� ���� ���� 
	//-------------
	DWORD	dwCurseAttackStartClock;
	DWORD	dwCurseAttackLastClock;
	SI32	siCurseAttackPower;			// ����. 

	//-------------
	// CRITICAL ���� ���� ���� 
	//-------------
	DWORD	dwCurseCriticalStartClock;
	DWORD	dwCurseCriticalLastClock;
	SI32	siCurseCriticalPower;		// ����. 
		
	//-------------
	// DEFENSE ���� ���� ���� 
	//-------------
	DWORD	dwCurseDefenseStartClock;
	DWORD	dwCurseDefenseLastClock;
	SI32	siCurseDefensePower;		// ����. 

	//-------------
	// MOVESPEED ���� ���� ���� 
	//-------------
	DWORD	dwCurseMovespeedStartClock;
	DWORD	dwCurseMovespeedLastClock;
	SI32	siCurseMovespeedPower;		// ����. 

	//-------------
	// MOVESPEED ���� ���� ���� 
	//-------------
	DWORD	dwIncreaseMovespeedStartClock;
	DWORD	dwIncreaseMovespeedLastClock;
	SI32	siIncreaseMovespeedPower;		// ����. 

	//------------
	// ������ �� ���� 
	//------------
	SI16	siMagicFireCharUnique;			// ���� �Һٰ��� ĳ���� ����ũ
	DWORD	dwMagicFireLastClock;			// ���� �����ð�. 
	DWORD	dwMagicFireStartClock;			// �� ���۽ð�. 
	SI32	siMagicFirePower;				// ���� ����. 
	DWORD	dwMagicFireCheckClock;			// �����ð����ݸ��� �˻��ؼ� Life�� �ٿ��ֱ����� �ӽ� �ð� ���� 

	//-------------
	// DRAIN ���� 
	//-------------
	bool	bDrainSwitch;
	SI16	siDrainFrame;

	UI32	uiStaminaFrame;
	
	//--------------
	// �ǰ�
	//--------------
	bool bHitSwitch;		// �ǰ� ������ ����. 

	//-------------------
	// ���� 
	//-------------------
	SI32	siWarEnemyKillNumber;	// ���￡�� óġ�� ���Ǽ�. 
	SI32	siWarKilledNumber;		// ������ ����� Ƚ��. 
	SI16	siBlackArmyWarMapIndex; // ���Ǳ��� ����� �ε���

	//-------------------
	// ���Ǳ��� ���� 
	//-------------------
	SI32	siBlackWarEnemyKillNumber;	// ���￡�� óġ�� ���Ǽ�. 
	SI32	siBlackWarKilledNumber;		// ������ ����� Ƚ��. 
	SI32	siBlackWarEnemyKillScore;			// [�߰� : Ȳ���� 2008. 1. 21 => ���￡�� óġ�� ���� ����.]
	SI32	siBlackWarEnemyKillVillageScore;	// [�߰� : Ȳ���� 2008. 1. 23 => ���￡�� óġ�� ���� �ش��ϴ� �� ���� ����.]

	
	//------------------------------------
	// ���ĸ��� �̺�Ʈ
	//------------------------------------
//	SI08	siMofuMofuEventField;		// ���ĸ��� �̺�Ʈ ���� ���� - ���ĺ��縦 ���� �� �ʵ��ȣ

	//------------------------------------
	// ��
	//------------------------------------
	cltJim	clJim;

	//------------------------------------
	// ��Ƽ �ε���.
	//------------------------------------
	SI16 siPartyIndex;
	
	//------------------------------------
	// ������� ������
	//------------------------------------
	DWORD dwMakeFrame;

	//-------------------------------------
	// ���� ��� ����. 
	//-------------------------------------
	bool bNoFirstAttackSwitch;
	
	//-------------------------------------
	// ICE ��� ����. 
	//-------------------------------------
	bool bNoIceAttackSwitch;

	//-------------------------------------
	// ��Ʈ ����Ʈ ����.  ( Ŭ���̾�Ʈ������ ��ȿ�ϰ� ���δ�. �������� BUF_LOVEPOWER, BUF_FRIENDSHIP �ΰ��� �ߺ��� ����̴� )
	//-------------------------------------
	bool bHeartEffectSwitch;

	//-------------------------------------
	// ���� Ŭ�ι� ����.  ( Ŭ���̾�Ʈ������ ��ȿ�ϰ� ���δ�. �������� BUF_FOURLEAF )
	//-------------------------------------
	bool bFourLeafSwitch;

	//-------------------------------------
	// ����� ���Ǵ� ����. 
	//-------------------------------------
	bool	bDyingSwitch;

	//----------------------------
	// ���λ��� ������ 
	//----------------------------
	bool bPersonalShopSwitch;	// ���λ����� ���� �ִ°�?
	bool bPremiumPersonalShop;	// �����̾� ���� �����ΰ�?

	//----------------------------
	// �����Ƿ� ������
	//----------------------------
	bool bRepairShopSwitch;		// �����Ƿڰ� �����Ǿ� �ִ°�?

	//----------------------------
	// ���� �������ΰ� 
	//----------------------------
	SI08 siPersonalMakeItemType;


	//bool bPersonalMakeItemSwitch;

	bool bPersonalEnchantItemSwitch;

	//���Ǻ� �̺�Ʈ ���ΰ�
	bool bHappyBean;

	//-------------------------------------
	// ���� Ŭ�ι� ����.  ( Ŭ���̾�Ʈ������ ��ȿ�ϰ� ���δ�. �������� BUF_FOURLEAF )
	//-------------------------------------
	bool bfarmminingSwitch;
	
	// ���� �������� �ؼ� ������ �����ΰ�
	bool bLevelUpDrawSwitch;

	// [����] ���� �귿 �۵����ΰ�? => 2008-6-10
	bool bBuffRouletteSwitch;

	//-------------------------------------	
	// [����] ������.
	//-------------------------------------
	bool bElixirSwitch;

	// [����] PVP���� ���� �Ӹ����� ī��Ʈ �̹����� �׸���.
	bool bPvpCountDown;

	// [����] �����̺�Ʈ ���� ���� �Ӹ����� ī��Ʈ �̹����� �׸���
	bool bRacoonDodgeEventCountDown;

	// [����] ���Һ� �̺�Ʈ : �׷��� ���ҽ� ��� : 5�� ī��Ʈ
	bool	bBBBEvent_5SecCountDownFlag;
	DWORD	siBBBEvent_5SecCountDown;

	bool	bBBBEvent_StageFailFlag;
	DWORD	siBBBEvent_StageFailCountDown;

	bool	bBBBEvent_StageClearFlag;
	DWORD	siBBBEvent_StageClearCountDown;

	bool	bBBBEvent_TotalStageClearFlag;
	DWORD	siBBBEvent_TotalStageClearCountDown;
	SI16	siBBBEvent_TotalStageClearResultImageIndex;

	//-------------------------------------
	// ���Ź��� ĳ���� KIND.  ( Ŭ���̾�Ʈ������ ��ȿ�ϰ� ���δ�. �������� BUF_TRANSFORM )
	//-------------------------------------
	SI16 siBufTransformKind;

	//--------------------------
	// ��Ʋ�ξ� �Ŀ��� ��� ���� ����
	//--------------------------
	bool	bBattleRoyalPowerupMode;

	//-------------------------------------------------
	// ��ȯ�� �� ����ڰ� ��Ʈ�� // Server���� ���� ĳ����Unique , Client���� 1�� ���� ĳ���� , �ƴϸ� ��ȯ�� Unique
	//-----------------------------------------------
	SI16 siSelectedCharIndex;

	//[����] ���θ���.
	bool bCellularPhoneAuth;	//[����] �ڵ��� ���� ����.
	bool bIsPromoter;			//[����] ���θ��Ͱ� �ִ°�?
	
	//KHY - 1220 - ���Žý���.
	//-------------------------------------
	// ĳ���� ���Ž� �ʿ��� ����.
	//-------------------------------------
	cltTransFormInfo clTransFormInfo;
	//-------------------------------------
	// �ɸ��� �ɼ�
	//-------------------------------------
	cltPCharOptionInfo	clCharOption;
	// [�߰� : Ȳ���� 2008. 1. 14 => �ڽ��� ��尡 �ְ��ΰ�.]
	UI32 uiBestGuild;
	//-------------------------------------------------------
	// pvp�� �� ���� Unique (DB�� �������� �ʴ´�.)
	SI16 siEnemUnique	;
	// pvp�� ��ٸ� �ð� (DB�� �������� �ʴ´�.)
	DWORD siPVPWaitTime	;
	// pvp�� ��ٸ� ���� ������ ID�� �����صд�. (DB�� �������� �ʴ´�.)
	SI16 siPVPWaitRequestId	;
	SI16 siPVPWaitAcceptId	;
	// PVP ���
	bool siPVPWin			;	// �¸�
	bool siPVPLose			;	// �й�
	bool siPVPDraw			;	// ���
	//-------------------------------------	
	// [����] ���� PVP �ο�� �ð�
	//-------------------------------------
	DWORD	siPVPTime	;
	// pvp�����ð� �ð� (DB�� �������� �ʴ´�.)
	DWORD siPVPEndTime	;
	// [����] PVP���׶� �Ӹ����� �׸���.
	bool bPvpLeague;
	cltPVP_LeagueInfo*	pclPVP_LeagueInfo;
	// �߷�Ÿ�ε��� �̺�Ʈ�� ���� �ڽ��� �ַ����� Ŀ������ ����� �ð�.
	DWORD dwValentineAnswerTime	;
	//-------------------------------------------------------

	CMarriage*			pclMarriage;	// ��ȥ
	CFamily*			pclFamily;		// ��������


	//  [8/11/2009 ��ȣ_GAWIBAWIBO] ���������� ���� ���� ī��Ʈ
	SI08				m_siGawiBawiBoCount;		

	cltValentineWarInfo*	pclValentineWar	;

	// �����̺�Ʈ ���� ���� ��ٸ��� 5�� (DB�� �������� �ʴ´�.)
	DWORD siRacoonDodgeWaitTime	;//Switch_10MonthEvent_RacoonDodge

	//------------------------
	// ��� ��� ����
	//------------------------
	SI32 bHaveCushion;

	//-------------------------------------
	// Protected Member Methods
	//-------------------------------------
//protected:
	//------------------------------------
	// ��� ���� ���. 
	//------------------------------------
	SI16 siGameMasterLevel;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, 4>	siRareItemRate;
#else
	SI16 siRareItemRate[4];
#endif
	bool bWennyOldMan ;
	SI16 siWennyOldMan ;

	//-----------------------------
	// �ǰݰ��� 
	//-----------------------------
	cltBeHitInfo	clBeHitInfo;


	cltCharCommonSimpleVary clCommonSimpleVary;

	SI16	m_siSetItemType;
	SI16	m_siSetItemStep;	//[����] ��Ʈ �������� �ܰ�. 2008-11-12

	SI16	m_siSetItemType2;
	SI16	m_siSetItemStep2;	//[����] 2��° ��Ʈ �������� �ܰ�. 2008-11-12

	SI16	m_siSetItemType3;
	SI16	m_siSetItemStep3;	

	SI16	m_siSetItemType4;
	SI16	m_siSetItemStep4;	

	SI16	m_siSetItemType5;
	SI16	m_siSetItemStep5;	

	//-----------------------------
	// ���Žý���
	//-----------------------------
	bool	bIsElectionStump;						// [����] ���Žý��� : �������� �������ΰ�?
	TCHAR	szCandidate[ Const_Max_Candidate ];		// ���� �ĺ��� �̸�
	TCHAR	szMaintenance[ Const_Max_Maintenance ];	// ��������

	// KHY - 0404 - ��� ����, Ż�� ���� Ȯ�ΰ�. - ������ ����°� ������ ����.
	//SI16 ChangeEquipAbility ;  // ��� ����, Ż�� ���� Ȯ��  - ���� ����Ż���� ����� ��ġ��.	

	// cltPersonInfo���� �ű�. - by LEEKH 2008-09-03
	cltSpaceBox*			pclSpaceBoxItem;		// ������ ���� ��� ���õ� ����.
	cltTreasureBox*			pclTreasureBoxItem;		// ������ ���� ��� ���õ� ����.

	cltElixir*				pcltElixir;				//[����] ������.

	//-----------------------------
	// ������������
	//-----------------------------
	CNMagicBufMgr			m_clMagicBufMgr;

	//[����] �����. �Ϸ� ������ Ƚ���� ����.
	UI08					m_uiDailyQuestionCount;

	//-----------------------------
	// ä�ú� ����
	//-----------------------------
	SYSTEMTIME				m_stMuteTime;			// ä�� �� �ð�

	//-----------------------------
	// ������� ���� - ����
	//-----------------------------
	UI08					m_uiWeaponSkillMasterEmblem;

	// �Ƿι��� ����
	enum { TIRED_STATUS_NORMAL = 0, TIRED_STATUS_LITTLE_TIRED, TIRED_STATUS_MUCH_TIRED };

	// �Ƿι��� �ð� ���� ��� ��.
	enum { TIRED_NOTICE_1_HOUR = 1, TIRED_NOTICE_2_HOUR, TIRED_NOTICE_2_5_HOUR,TIRED_NOTICE_3_HOUR,
		TIRED_NOTICE_3_5_HOUR,TIRED_NOTICE_4_HOUR ,TIRED_NOTICE_4_5_HOUR,TIRED_NOTICE_5_HOUR,TIRED_NOTICE_5_OVER_HOUR};

public:
	//------------------------------------
	// Virtual Function
	//------------------------------------
	virtual void CalculateRealXY(){};
	virtual BOOL SetNeighbour(){return FALSE;}
	//virtual void SetNewSelectedSwitch(bool mode){}; //[����] �������� Ŀ�տ��� �ʿ䰡 ���ٴ� �Ǵ��Ͽ� ������ ����
	virtual void InitWarpInfo(){}
	virtual void SetWarpInfo(const cltWarpInfo* pclCharWarpInfo, SI32 warpunique){}
	virtual void SetWarpToVillage(cltMapManager* pclmapmanager, SI16 villageunique, SI32 warpunique){}

	virtual BOOL IsAbsPtInObj(SHORT x, SHORT y, SHORT& length){return FALSE;};
	virtual void SetUpdateSwitch(SI32 updatetype, bool mode, SI32 para1){}
	virtual void SetNPCGroup(SI32 group){}
	virtual BOOL AddItemToInventory(cltItem* pclitem){return FALSE;}
	virtual bool UseItem(cltItem clitem){return false;}
	virtual void Revive(){};
	virtual BOOL Warp(){return FALSE;}
	virtual	void DrawName(HDC hdc){};
	virtual	void DrawName(){};
	virtual	void DrawChatBalloon(){};
	virtual SI32 GetRX() const{return 0;}
	virtual SI32 GetRY() const{return 0;}
	virtual void CalculateRXY(){};
	virtual void SetMoveStandardPos(SI32 mox, SI32 moy, SI32 mdx, SI32 mdy){}
	virtual void SetHitDrawSwitch(bool mode){};
	virtual void CharBossAction(){};
	virtual void CharRegenerationAction(){};
	virtual void SetCharRegeneration(){};
	virtual void CharCutAction(){}
	virtual void SetCharCut(SI32 mode){}
	virtual	void SetLevelUp(){}
	virtual	void SetMVPEffect(){}
	virtual void SetEnchantEffect(SI08 AniType){}
	virtual void SetQuestEffectReceive(){}
	virtual void SetQuestEffectClear(){}
	virtual void SetSkillLevelUp(){}
	virtual	void SetLastReceveFromClientClock(DWORD clock){}
	virtual void DeleteInCell(){};
	virtual bool Action_Dying();
	virtual void Dead(){}
	virtual void SendLetterMsg(cltLetterUnit* pclletter){};
	virtual void GetBottomPoint(cltPos* pclpos){};
	virtual	void SetMagicDelay(SI32 delay){}
	virtual SI32 GetMagicDelay(){return 10000;}
	virtual void SendDBLevelInfo(SI32 incbonus, SI32 incskillbonus){};
	virtual	bool ChangeArmCode(SI32 itempos, SI32 siunique){return false;}
	virtual void ChangeHorseCode(SI32 code,cltDate* cldate = NULL , SI32 ticket = 0 ){};
	virtual bool GetInitProtectSwitch(){return false;}
	virtual void DeleteOperation(){}
	virtual void DeleteSlave(){};
	virtual bool AfterCharAction() = 0;
	virtual bool IsWarpStatus(){return false;}
	virtual DWORD GetDrawFrame(){return 0;}
	virtual void SetJimShow(){};
	virtual bool MagicInAttackAction(){return false;}
	virtual bool CheckLastMsgClock(DWORD interval){return false;}
	virtual bool MakeItem(cltGameMsgRequest_MakeItemInv* pclinfo){return false;}
	virtual bool SetReserverMakeItem(DWORD productclock, cltGameMsgRequest_MakeItemInv* pclinfo){return false;}
	virtual bool SetMakeDelayDraw(DWORD delayclock){return false;}
	virtual void CellAction(){};
	virtual void DoQuestCheckAndAction(SI32 questclearcond){}
	virtual void FogAction(){}		// ���װ���
	virtual void AddKillMonsterNum(){}	//

	cltCharCommon();
	virtual ~cltCharCommon();

	void CharInit(SI32 id, SI32 charunique, SI32 childcharunique, SI32 summonindex, SI32 dir, cltMapCommon* pclmap, 
		cltIdentity* pclidentityinfo, cltPersonInfo* pclUserCharInfo, cltInnerStatusInfo* pclInnerStatus, SI16 mySoulGuardUnique);

	void SetInfo();		// ĳ���Ͱ� �����Ǿ����� �˸���. 

	SI32 GetCharUnique()const;
	void SetCharUnique(SI32 unique);

	void SetCurrentOrder(SI32 order);
	SI32 GetCurrentOrder()const;

	void SetID(SI32 id);
	SI32 GetID()const;

	SI32 GetX()const;
	SI32 GetY()const;

	void  SetX(SI32 x);
	void  SetY(SI32 y);

	SI32 GetKind()const;		// ������ �����ش�.
	void SetKind(SI32 kind);
	cltKindInfo* GetKindInfo(bool bForDraw = false);	// KindInfo ������ �����ش� - ���� �Ŀ��� ���ŵ� ĳ������ ������ ��ȯ�ȴ�. - by LEEKH 2007.12.24
														// �ܰ����� ������ ���� ���� �߰� - by LEEKH 2008-09-10

	SI32 GetMapIndex()const;			// �� �ε����� ���´�. 
	void SetMapIndex(SI32 index);		// �� �ε����� �����Ѵ�.  

	SI32 GetCurrentVillageUnique();		// Person�� ���� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 GetHuntVillageUnique();		// Person�� ���� ��ġ�� �������� �ִ� ������ Unique�� ���Ѵ�. 

	SI32 GetCenterX()const;
	SI32 GetCenterY()const;

	const TCHAR* GetName()const;			// ĳ������ �̸��� ���´�. 
	void SetName(const TCHAR* name);

	SI32 GetMana();
	void SetMana(SI32 mana);
	SI32 DecreaseMana(SI32 mana);
	SI32 IncreaseMana(SI32 mana);

	SI32 GetLife();
	void SetLife(SI32 life);

	SI32 IncreaseLife(SI32 life);

	SI32 GetWis()const;

	SI32 GetStr()const;
	
	SI32 GetDex()const;

	SI32 GetVit()const;
	void SetVit(SI32 vit);

	SI32 GetMag()const;
	void SetMag(SI32 mag);

	SI32 GetHnd()const;
	void SetHnd(SI32 hnd);


	SI32 GetSubOrder();			// �������� �۾��� ���� �ܰ踦 ���´�.

	SI64 GetMyExp()const;		// �� �ڽ��� ����ġ�� ���Ѵ�.(��밡 ���� óġ���� �� ���� �� �ִ� ����ġ. ) // SI32->SI64 ����ġ �����÷ο춧���� ����

	SI32 GetAttackRange()const;
	SI32 GetAttackType();

	SI32 GetMaxWeight();		// �� �� �ִ� �ִ� ���Ը� ���Ѵ�.
	SI32 GetTotalWeight();		// ������ ���� �հ踦 ���Ѵ�. 
	
	BOOL IsSameMap(const cltMapCommon* pclmap);
	
	bool IsSBS();				// SBS������ΰ�. 

	SI32 GetSummonID();			// ���� ��ȯ�� ID�� ���´�.
	SI32 GetSummonParentID();	// ��ȯ���� PARENT ID�� ���´�.
	SI32 GetSummonIndex();		// ��ȯ���� Unique Index�� ���´�.

	// [����] ��ȣ����_090525
	SI32 GetSoulGuardParentCharID( void );	// ��ȣ������ �θ� CharID�� ���´�
	SI32 GetSoulGuardCharID( void );

	void	InitGawiBawiBoCount(){m_siGawiBawiBoCount = 0;}  // ���������� ���� ���� �ʱ�ȭ
 	SI08	IncreaseGawiBawiBoCount(){return m_siGawiBawiBoCount++;}  // ���������� ����
	SI08	GetGawiBawiBoCount(){return m_siGawiBawiBoCount;}
    
	//-----------------------------------------------------------------------------------
	// KHY - 0404 - ��� ����, Ż�� ���� Ȯ�ΰ�. - ������ ����°� ������ ����.
	//-----------------------------------------------------------------------------------
	/*void SetChangeEquipAbility (SI16 equipPos)
	{
		ChangeEquipAbility= equipPos;
	}

	SI16 GetChangeEquipAbility()
	{
		return ChangeEquipAbility;
	}
*/
	//--------------------------------------
	// �Ӽ� 
	//--------------------------------------	
	BOOL 			IsAtb(SI32 atb);	// �Ӽ��� ���Ѵ�. 
	BOOL 			IsAtbAnd(SI32 atb);	// ��� ������ �����Ǿ�� 
    BOOL 			IsDefenceAtb(SI32 atb);
    
	//---------------------------------------
	// ����/���� 
	//---------------------------------------
    void GetHitPoint(cltPos* pclpos);
	void DecideAttackPoint(SI32 port, SI32& x, SI32&y );
	BOOL IsInRange(SI32 id, SI32 range);	// id�� range�����ȿ� �ִ°�?

	BOOL CanAttack( SI32 id, bool pvpflag = false );
	BOOL CanAttack(const cltAttackTarget* pcltarget);
	
	bool CanMagicManaDelay(SI32 magickind, SI32* preturn );							// ������ ����ϱ����� ������ �ð��� �������� �˻��Ѵ�.
	bool CanMagic(SI32 targetid, SI32 magickind,  SI32* preturn, bool PVP = false);	// �������� ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
	bool CanMagicBuf( SI32 siMagicKind, SI32* psiReturn );							// ���� ������ ����� �� �ִ��� �˻�
	
	bool IsEnemyPCvsNOTPC(SI32 myid, SI32 enemyid);		// PC vs !PC ĳ���͸� ������ �� �ִ��� ���θ� �˷��ش�. 
	bool IsEnemy(SI32 id);					// id�� ���� ���ΰ�?
	bool IsEnemyPCvsPC( SI32 enemyid );		// ���� �ٸ� ������ ������ �� �ֳ�? 
	
	BOOL IsInMinRange(SHORT id, SHORT minrange);		// id�� ���� �ּ� �����ȿ� �ִ��� Ȯ���Ѵ�. 
	bool Fire();
	bool FireSub();
	SI32 GetApower();

	BOOL GetBulletUnique_Char(SI16* psiBulletUnique);						// ����Ÿ�԰� ��ġ�ϴ� �Ѿ�(ȭ��)�� ����ũ�� �����ش�. - ĳ����
	BOOL GetBulletUnique_Summon(SI32 siSummonIndex, SI16* psiBulletUnique);	// ����Ÿ�԰� ��ġ�ϴ� �Ѿ�(ȭ��)�� ����ũ�� �����ش�. - ��ȯ��

	//---------------------------------------
	// Action
	//---------------------------------------
	// ���ϰ�:  FALSE  .  Ư�� ���� ���� 
	//          TRUE   ->  ĳ���͸� ������ 
	BOOL Action();
	bool PreCharAction();

	//---------------------------------------
	// ��� ó�� 
	//--------------------------------------
	void InitPreGetOrder();			// ����� ���� �����ϱ� ���� �ؾ��� �ʱ�ȭ 
	BOOL GetOrderBuffer();			// ����� ����� ������ �����Ѵ�. 
	BOOL PushOrder(cltOrderDataInfo order);		// ����� ���ۿ� �ִ´�. 

	//-------------------------------------
	//	ĳ���� ������ �ɰų� ���� 
	//-------------------------------------
	BOOL SetID();			// ĳ������ ������ ����� 
	BOOL DeleteID();		// ĳ������ ������ ���ش�. 

	//-------------------------------------
    /// ���� ����. 
	//-------------------------------------
	BOOL Magic();
	void MagicOperation();	
	
	//-------------------------------------
	// ���� 
	//-------------------------------------
	bool IsFishArea(SI32 x, SI32 y, SI32* pdir);		// ���ð��� �����ΰ� ?
	bool FindFishArea(SI32* px, SI32* py);				// �� ĳ���� �ֺ��� ������ ���� ��ġ�� ã�´�. 
	
	bool Fish();

	//-------------------------------------
	// ��� 
	//-------------------------------------
	bool CanFarm(SI32 dx, SI32 dy, SI32* ptrnval);		// ��縦 ���� �� �ִ°� ?

	bool SetFarm(SI32 dx, SI32 dy);
	bool Farm();
	bool FarmAction();

	//-------------------------------------
	// ä��
	//-------------------------------------
	bool CanMine(SI32 dx, SI32 dy, SI32* ptrnval);

	bool SetMine(SI32 dx, SI32 dy);
	bool Mine();
	bool MineAction();


	//-------------------------------------
	// �ɱ�
	//-------------------------------------
	bool SitDown(SI32 SitDownAnytype);


	//--------------------------------------------------
	//   �̵� ���� �Լ� 
	//--------------------------------------------------
	bool			SetMove(SI32 dx, SI32 dy);		// ĳ���͸� �̵��ϰ� ����� ���� ������ �Ѵ�. 

	int 			Move(bool bstraightswitch = false);

	int				GetMovePercent();
	
	BOOL			MoveDone();

	BOOL			CanMoveTo(SI32 x, SI32 y);
	BOOL			MoveTo(SI32 x, SI32 y);

	bool			IsColl(SHORT x, SHORT y);					// ĳ���Ͱ� x, y��ġ�� ���� �� �ִ°� ���°�?
	bool			IsColl(SHORT x, SHORT y, SHORT block);		// ĳ���Ͱ� x, y��ġ�� ���� �� �ִ°� ���°�?

	void			MoveInit();

	bool SetBlock();		// �浹 ������ �����Ѵ�. 


	//---------------------------------
	//���� ���� �Լ� 
	//---------------------------------
    SI32 Action_Attack();

	BOOL TryAttack();
	BOOL Escape();

	BOOL ReadyToFire();			// fire������ Ȯ�� 
	BOOL SetAttack(SI32 id, bool PVPHit = false);	////  attack_id ���� �����ϰ� ����� �Լ� 

    BOOL PreAttack();			// �������� ������ ���� ���� ó���ؾ� �� ���� ó���Ѵ�. 

	//-------------------
	// �ִϸ��̼� ����. 
	//-------------------
	SI32 CalcHeroAnimation();	// Hero Animation �ڵ带 �����Ѵ�. 

	void			SetAnimation(SI32 ani);
	virtual BOOL			DoAnimationDelay(BOOL atb = 0);

	//---------------------------
	// ������ȯ ���� 
	//----------------------------
    BOOL			ChangeDirection(SHORT destdir);			// ĳ������ ������ ��ȯ�Ѵ�. 
    BOOL			ChangeDirectionNormal(SHORT destdir);	// ĳ������ ������ ��ȯ�Ѵ�. 
    BOOL			ChangeDirection16(SHORT destdir);		// ĳ������ ������ ��ȯ�Ѵ�. 

	//---------------------------------------------
	// EconomyInfo����. 
	//---------------------------------------------
	GMONEY GetBankMoney()const;				// ���� �ܰ� �����Ѵ�. 
	SI32 GetStockOrderNumber()const;		// �ֽ� �ֹ� ������ Ȯ���Ѵ�. 
	SI32 GetGuildStockOrderNumber()const;	// ��� �ֽ� �ֹ� ������ Ȯ���Ѵ�. 
	SI32 GetMarketOrderNumber()const;		// ��ǰ �ֹ� ������ Ȯ���Ѵ�. 
	SI32 GetNewMarketOrderNumber() const; //[����] ���ո��� ��ǰ �ֹ� ������ Ȯ���Ѵ�. 

	//-----------------------------------
	// �޽��� �����Լ�.
	//-----------------------------------
	void SendNetMsg(sPacketHeader* pmsg);

	bool IsValidConnection();		// ������ �Ǿ� �ִ� Person���� ����. 

	//-----------------------------------
	// �� ���� 
	//-----------------------------------
	virtual bool RideHorse();		// ���� ź��. 
	virtual bool UnrideHorse();		// ������ ������.

	bool HaveHorse();	// ���� ������ �ִ°�?


	//----------------------
	// �ǰ� 
	//---------------------
	virtual void SetHitSwitch(bool mode);
	
	bool BeHitOperation();		// �ǰ� �ൿ�� ���Ѵ�. 

	//----------------------------------
	// ���� ���� 
	//----------------------------------
	void ChangeTopSkillUnique(SI32 skillunique);		// �ְ� ���� ��� ���θ� �����Ѵ�. 

	//---------------------------------
	// ���� �ؽ�Ʈ 
	//---------------------------------
	bool GetCharInfoText(TCHAR* buffer);				// ĳ������ ������ �ؽ�Ʈ�� �����ؼ� �޴´�.

	//------------------------------------
	// ��� ���� ���. 
	//------------------------------------
	SI32 GetGameMasterLevel();
	void SetGameMasterLevel(SI32 level);
	SI32 GetRareItemRate(SI32 where);
	void SetRareItemRate(SI32 attack,SI32 mag,SI32 skill,SI32 dur);
	bool GetWennyOldManSuccess();
	SI32 GetWennyOldManMode();
	void SetWennyOldMan(bool success,SI32 mode);

	//---------------------------------
	// ����Ʈ ���� 
	//----------------------------------
	bool IsClearCondition(SI32 questtype, cltQuestClearConditionInfo* pclcond);		// �ӹ��� �Ϸ� ������ ������Ű�°�?
	bool DoClearCondition(cltQuestClearConditionInfo* pclcond);		// �ӹ��� �Ϸ� ���ǿ��� �������� �䱸�Ǹ� �������� ĳ���Ϳ��Լ� �����Ѵ�. 
	bool ClearQuest(SI32 questunique);			// Ư�� ����ũ�� ����Ʈ�� �Ϸ��ߴ��� Ȯ���Ѵ�. 
	SI32 GetMinBit(SI32 type);					// ���� �Ϸ���� ���� ���� ���� ����Ʈ�Ǻ�Ʈ�� ã�´�. 
	
	//----------------------------
	// ������ 
	//-----------------------------
	bool CanUseSummonDoll(SI32 itemunique, SI32 *summonkind,SI32 *summonindex, SI32 *preturn);	// ��ȯ������ �̿��� ��ȯ���� ���� 
	bool CanUseItem(cltItem clitem, SI32* preturn, SI32 siPos);		// �������� ����Ҽ� �ִ� ������ Ȯ���Ѵ�.
	// �������� ����Ͽ� ��ȣ������ ��ȯ�Ҽ��ִ°�?
	bool CanUseSoulGuardItem( SI32 siItemUnique, SI16* psiSoulGuardKind, SI16* psiLife, SI16* psiFellowShip, SI32* pReturn );
	bool CanRepairItem( cltItem* pclitem );

	//---------------------------
	// ��� 
	//---------------------------
	bool CheckEquipCondition(cltItemManagerCommon* pclItemManager, SI32 pos, cltItem* pclitem, SI32* preturnval);

	//------------------------------------
	// ���� ���õ� ���� 
	//------------------------------------
	void SetCurrentMagic(SI32 magic, SI08 siCastType);
	SI32 GetCurrentMagic();
	SI08 GetCurrentMagicCastType();
	
	//-------------------------------------
	// �̺�Ʈ ���� �Լ�. 
	//-------------------------------------
	void SetEventChar(SI32 eventindex, bool bmode);		// �̺�Ʈ ĳ���ͷ� �����Ѵ�. 
	
	//-----------------------------------------
	// ��ȣõ�� ���� 
	//-----------------------------------------
	void SetAngel(bool mode);

	//-----------------------------------------
	// ���� ���� 
	//-----------------------------------------
	void SetPolice(bool mode);
	
	void GetShapeEquipInfo(cltShapeEquipInfo* pclequip);		// �� �ܾ� ��� ��Ȳ�� ���´�. 


	// ��� ������ ����
	SI32 IsHaveCushionItem();

	//KHY - 1220 - ���Žý���.
	bool IsCanTransFormRecover();
	bool CanTransFormAttackType(SI32 siCharKind);

	SI32 GetItemUniqueFromCharKind(SI32 siCharKind);
	SI32 GetCharKindFromItemUnique(SI32 siItemUnique);

	SI32 GetFarmRate(SI32 farmskilllevel);		// ����� ���ؼ� ���� �� �ִ� �۹��� Ȯ��. 
	SI32 GetMineRate(SI32 mineskilllevel);		// ä���� ���ؼ� ���� �� �ִ� ������ Ȯ���� ����. 

	void ParametaBoxAction();
	void SetParametaBoxAction(bool mode);

	//---------------------------------------------
	// CharCommon-Summon.cpp
	//---------------------------------------------
	SI16 GetCannonCrewDamage(cltKindInfoSet* pclkindmanager,  SI16 SummonPos );		// ������ ��ȯ�� ���ݷ��� ���´�.
	SI16 GetGunCrewDamage( cltKindInfoSet* pclkindmanager,  SI16 SummonPos );		// ����� ��ȯ�� ���ݷ��� ���´�.
	//bool IsSummonHaveItem(SI32 summonindex);		// ��ȯ���� ��ǰ�� ����ϰ� �ִ°�? - �Ⱦ�

	//---------------------------------------------
	// ���� ���� �Լ�
	//---------------------------------------------
	bool CanWarpFrom();
	bool CanWarpTo( SI32 siToMapIndex );
	bool CanFreeWarp( SI32 siDestMapIndex );
	bool CanWarpToChar( SI32 siCharID );		// ���� ����

	void PartyHallItemRemove(SI32 id);				//[����] ��ƼȦ. ��Ƽ�忡�� ��� �������� ����.
	void NotFourLeafItemRemove( SI32 id );			//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ���� => 2008-8-14
	void FestivalFoodItemRemove( SI32 id );			//[����] ���� ����.
	
	//---------------------------------------------
	// ���� ���� �Լ�
	//---------------------------------------------
	bool Action_Special();

	// ���� �־� �ϴ� ���ϸ��̼� Ÿ������ �����Ѵ�.
	bool selectRealAnyType( );

	//---------------------------------------------
	// PVP_League ���� �Լ�
	//---------------------------------------------
	SI16 GetPVP_LeagueEnemyPersonID( void );
	void SetPVP_LeagueEnemyPersonID( SI16 siEnemyID );

	SI16 GetPVP_League_Win( void );
	void SetPVP_League_Win( SI16 siWin );
	void IncPVP_League_Win( SI16 siWin );

	SI16 GetPVP_League_Draw( void );
	void SetPVP_League_Draw( SI16 siDraw );
	void IncPVP_League_Draw( SI16 siDraw );

	SI16 GetPVP_League_Lose( void );
	void SetPVP_League_Lose( SI16 siLose );
	void IncPVP_League_Lose( SI16 siLose );

	SI16 GetPVP_LeagueStraight_Win( void );
	void SetPVP_LeagueStraight_Win( SI16 siWin );
	void IncPVP_LeagueStraight_Win( SI16 siWin );

	SI16 GetPVP_LeagueStraight_Draw( void );
	void SetPVP_LeagueStraight_Draw( SI16 siDraw );
	void IncPVP_LeagueStraight_Draw( SI16 siDraw );

	SI16 GetPVP_LeagueStraight_Lose( void );
	void SetPVP_LeagueStraight_Lose( SI16 siLose );
	void IncPVP_LeagueStraight_Lose( SI16 siLose );

	SI16 GetPVP_LeagueGrade( void );
	void SetPVP_LeagueGrade( SI16 siGrade );

	bool IsPVP_LeagueLatestPersonID( SI32 siDestPersonID );
	void PushPVP_LeagueLatestPersonID( SI32 siDestPersonID );

	void SetPVP_LeagueStraight_Lose_Grade( SI16 siWin );
	SI16 GetPVP_LeagueStraight_Lose_Grade( void );
	void SetPVP_LeagueStraight_Win_Grade( SI16 siWin );
	SI16 GetPVP_LeagueStraight_Win_Grade( void );

	SYSTEMTIME GetPVP_LeagueEndBAttleTime( void );
	void SetPVP_LeagueEndBAttleTime( SYSTEMTIME stEndTiem );

	// ��ȥ ����
	BOOL IsMarried( void );
	void SetProposePersonID( SI32 siProposePersonID );
	SI32 GetProposePersonID( void );
	// ��������
	SI32 GetMyFamilyClass( void )	;

	//---------------------------------------------
	// ��ȣ����
	//---------------------------------------------
	BOOL IsSoulGuardStatusOut( void );	// ��ȣ������ ���� ��ȯ�Ǿ����ִ� �������� �˻�
};



#endif
