//---------------------------------
// 2003/11/22 ���°�
//---------------------------------

#ifndef _QUEST_H
#define _QUEST_H

#include <Directives.h>

#include "../../Lib/commonutil.h"
#include "../../common/Item/ItemCommon/ItemUnit.h"
#include "../../NLib/NDataTypes.h"
#include "../../NLib/NArray.h"
#include "../../common/CommonHeader.h"

#include "../../../NLib/NTextManager.h"

class HashStringInt;
class cltQuestManager;
class cltCharCommon;
class cltCharClient;

#define MAX_START_CONVERSATION_NUM	10			// ó�� ��ȭ�� ��
#define MAX_END_CONVERSATION_NUM	10			// ������ ��ȭ�� ��
#define MAX_TITLE_TEXT_SIZE			256

#define MAX_QUEST_PER_TYPE_NUMBER	32		// �ϳ��� ����Ʈ Ÿ�Դ� �ִ� ����Ʈ ��. 

#define MAX_QUEST_REWARD_NUMBER		6

//---------------------------------
// ����Ʈ �ܰ� 
//---------------------------------
#define QUEST_STEP_GREETING			10
#define QUEST_STEP_MIDDLE			20
#define QUEST_STEP_GOING			30
#define QUEST_STEP_CLEAR			40
#define QUEST_STEP_NEXTQUEST		50

//---------------------------------
// ����Ʈ Ÿ�� 
//---------------------------------

// [����] ����ƮŸ�� enum���� ��ü
enum QUEST_TYPE
{
	QUEST_TYPE_NONE					= -1,	//-1 �ƹ� ����Ʈ Ÿ�Ե� �ƴϴ�

	QUEST_TYPE_SPECIAL				= 0,	//00 ����� ����Ʈ. 
	QUEST_TYPE_BATTLE1				= 1,	//01 ���� ����. (�����������)
	QUEST_TYPE_MAKEHEAL1,					//02 ���� ������
	QUEST_TYPE_MAKESWORD1,					//03 ���� ��������
	QUEST_TYPE_MAKEBOW1,					//04 ���� Ȱ������
	QUEST_TYPE_MAKEHELMET1,					//05 ���� ����������
	QUEST_TYPE_BEGINNER3,					//06 ����ȣ ����Ʈ 
	QUEST_TYPE_MAKESPEAR1,					//07 ���� â������
	QUEST_TYPE_MAKEARMOUR1,					//08 ���� ������
	QUEST_TYPE_MAKEAX1,						//09 ���� ������

	QUEST_TYPE_MAKEGUN1,					//10 �� ������
	QUEST_TYPE_MAKESTAFF1,					//11 ������ ������
	QUEST_TYPE_MAKEBELT1,					//12 ��� ������
	QUEST_TYPE_MAKESHOES1,					//13 �Ź� ������
	QUEST_TYPE_BEGINNER2,					//14 ���� ����Ʈ 
	QUEST_TYPE_BATTLE2,						//15 ���� ����Ʈ
	QUEST_TYPE_BASIC1,						//16 ���� ���. (����� ����Ʈ)
	QUEST_TYPE_BEGINNER4,					//17 ���˼�����Ʈ
	QUEST_TYPE_MAKEBEGINNER1,				//18 �ʺ��ڸ� ���� ���� ����Ʈ
	QUEST_TYPE_HUNTINGETC01,				//19 �߿�NPC1

	QUEST_TYPE_NAMING,						//20 ���̹� ����Ʈ
	QUEST_TYPE_HAPPYBEAN,					//21 KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
	QUEST_TYPE_HUNTINGGROUND01,				//22 �̻��ѿ�õ ����Ʈ
	QUEST_TYPE_HUNTINGGROUND02,				//23 �δ���ź��
	QUEST_TYPE_MAKESANTAHAT,				//24 ũ�������� �̺�Ʈ ����Ʈ 1
	QUEST_TYPE_MAKECAKE,					//25 ũ�������� �̺�Ʈ ����Ʈ 2
	QUEST_TYPE_PLAYCHRISTMAS,				//26 ũ�������� �̺�Ʈ ����Ʈ 3
	QUEST_TYPE_HUNTINGGROUND03,				//27 ������ ����Ʈ
	QUEST_TYPE_HUNTINGGROUND04,				//28 ������ �� ����Ʈ
	QUEST_TYPE_HUNTINGGROUND05,				//29 ����Ÿ ����Ʈ

	QUEST_TYPE_HUNTINGGROUND06,				//30 ���Ͼ ����Ʈ
	QUEST_TYPE_HUNTINGGROUND07,				//31 �̶� ����Ʈ
	QUEST_TYPE_HUNTINGGROUND08,				//32 ������ ����Ʈ
	QUEST_TYPE_HUNTINGGROUND09,				//33 ���� ����Ʈ
	QUEST_TYPE_HUNTINGGROUND10,				//34 ���긮�� ����Ʈ
	QUEST_TYPE_HUNTINGGROUND11,				//35 �ϸ��Ƴ� ����Ʈ
	QUEST_TYPE_MAKEFOOD1,					//36 �������� ����Ʈ
	QUEST_TYPE_BEGINNER1,					//37 ���̸� ����Ʈ
	QUEST_TYPE_DAILYQUEST2,					//38 ���ϸ� ����Ʈ2
	QUEST_TYPE_DAILYQUEST3,					//39 ���ϸ� ����Ʈ3

	QUEST_TYPE_MAKEARTIFACT1,				//40 ��Ƽ��Ʈ ����Ʈ(�ŵ�)
	QUEST_TYPE_MISSION1,					//41 �̼� ����Ʈ
	QUEST_TYPE_HUNTINGGROUND12,				//42 �����帯 ����Ʈ
	QUEST_TYPE_HUNTINGGROUND13,				//43 ���̵� ����Ʈ

	QUEST_TYPE_FINDTREASURE,				//44 ����ã�� �̺�Ʈ _����Ʈ ����
	QUEST_TYPE_HUNTINGGROUND14,				//45 �Ҿ���� ���� ����Ʈ

	QUEST_TYPE_AVATAR_DRESS,				//46 �ƹ�Ÿ �巹�� ����Ʈ
	QUEST_TYPE_AVATAR_HAT,					//47 �ƹ�Ÿ ���� ����Ʈ
	QUEST_TYPE_AVATAR_MENTAL,				//48 �ƹ�Ÿ ���� ����Ʈ
	QUEST_TYPE_AVATAR_RING,					//49 �ƹ�Ÿ ���� ����Ʈ
	QUEST_TYPE_AVATAR_NECK,					//50 �ƹ�Ÿ ����� ����Ʈ
	QUEST_TYPE_PLAYCHRISTMASHIDDEN,			//51 ũ�������� �̺�Ʈ ����Ʈ 4

	QUEST_TYPE_HUNTINGGROUND15,				//52 �Ȱ��̱� ����Ʈ

	//---------------------------
	//	�� ���� �߰����� �ּ���
	//---------------------------
	MAX_QUEST_TYPE
};
//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
//---------------------------------
// ���Ǻ� ����Ʈ �ܰ� 
//---------------------------------
#define QUEST_HAPPYBEAN_STEP_NON			0
#define QUEST_HAPPYBEAN_STEP_START		10
#define QUEST_HAPPYBEAN_STEP_COMPLETE	20

#define MAX_QUEST_ONEDAY_COUNT	2  //�Ϸ翡 ���� �Ǵ� ����Ʈ ��.

enum MISSIONQUEST_UNIQUE
{
	MISSIONQUEST_UNIQUE_NONE = 0,
	//--------------------------------------
	MISSIONQUEST_UNIQUE_HOLLOWEEN,
	MISSIONQUEST_UNIQUE_REMOVE_UNLUCK,
	MISSIONQUEST_UNIQUE_GOONZUDAY,
};

//---------------------------------
// Person QUest�� Ÿ�Ժ� ���� ����. 
//---------------------------------
class cltPersonQuestUnitInfo{
public:
	SI32 siQuestState;			// ����Ʈ Ŭ���� ����. (�� ��Ʈ������ 0�̸� ��Ŭ���� 1�̸� Ŭ����. ) 
	SI16 siCurQuestUnique;		// ���� �������� �� Ÿ�Ժ� ����Ʈ Unique. 
	SI16 siCurQuestStep;		// ���� �������� �� Ÿ�Ժ� ����Ʈ�� �ܰ�. 
	
	SI16 siQuestCmd;			// �����ؾ� �� �ӹ��� Ÿ��. 
	SI16 siQuestPara1;
	SI16 siQuestPara2;

	cltPersonQuestUnitInfo()
	{
		Init();
	}

	void Init()
	{
		siQuestState		= 0;
		siCurQuestUnique	= 0;
		siCurQuestStep		= 0;

		siQuestCmd			= 0;
		siQuestPara1		= 0;
		siQuestPara2		= 0;
	}

	void Set(cltPersonQuestUnitInfo* pclinfo)
	{
		siQuestState		= pclinfo->siQuestState;
		siCurQuestUnique	= pclinfo->siCurQuestUnique;
		siCurQuestStep		= pclinfo->siCurQuestStep;
		siQuestCmd			= pclinfo->siQuestCmd;
		siQuestPara1		= pclinfo->siQuestPara1;
		siQuestPara2		= pclinfo->siQuestPara2;
	}

	BOOL IsSame( cltPersonQuestUnitInfo* pclinfo )
	{
		if(siQuestState	!= pclinfo->siQuestState)
			return FALSE;
		if(siCurQuestUnique	!= pclinfo->siCurQuestUnique)
			return FALSE;
		if(siCurQuestStep	!= pclinfo->siCurQuestStep)
			return FALSE;
		if(siQuestCmd	!= pclinfo->siQuestCmd)
			return FALSE;
		if(siQuestPara1	!= pclinfo->siQuestPara1)
			return FALSE;
		if(siQuestPara2	!= pclinfo->siQuestPara2)
			return FALSE;
		return TRUE;
	}


	// Ư�� ��Ʈ�� �����Ѵ�. 
	void SetBit(SI32 bit, SI32 data)
	{
		if(data)
		{
			siQuestState |= (1 << bit);
		}
		else
		{
			if(siQuestState  & (1 << bit))
			{
				siQuestState -= (1 << bit);
			}
		}
	}

	// Ư�� ��Ʈ�� ������ ���´�. 
	SI32 GetBit(SI32 bit)
	{
		return (siQuestState & (1 << bit));
	}

	
};


//----------------------------------
// ����Ʈ �߰� ����. 
//----------------------------------
class cltQuestMiddleInfo{
public:
	GMONEY siGiveMoney;		// ����ڿ��� �� ��. 	
	cltItem clItem;			// ����ڿ��� �� ������. 

	cltQuestMiddleInfo()
	{
		Init();
	}
	void Init()
	{
		siGiveMoney = 0;
		clItem.Init();
	}
	void Set(cltQuestMiddleInfo* pclinfo)
	{
		siGiveMoney = pclinfo->siGiveMoney;
		clItem.Set(&pclinfo->clItem);
	}
};

//--------------------------------------------
// ����Ʈ txt ����
//------------------------------------------
class cltQuestTxtInfo{
public:
	// ����Ʈ ��ȭ��
	TCHAR szStartQuestConversation[MAX_START_CONVERSATION_NUM][1024];
	// ����Ʈ ��ȭ��
	TCHAR szEndQuestConversation[MAX_END_CONVERSATION_NUM][1024];
	// ����Ʈ ���� txt
	TCHAR szQuestGreeting[1024];
	// ����Ʈ ���� txt
	TCHAR szQuestMiddle[1024];
	// ����Ʈ ���� txt
	TCHAR szQuestClear[1024];

#ifdef _SAFE_MEMORY
	// ����Ʈ NPC �� ǥ�� �ε���
	NSafeTArray<SI32, MAX_START_CONVERSATION_NUM>		siStartSprIndex;
	// ���� �� ǥ�� �ε���
	NSafeTArray<SI32, MAX_END_CONVERSATION_NUM>			siEndSprIndex;
#else
	// ����Ʈ NPC �� ǥ�� �ε���
	SI32 siStartSprIndex[MAX_START_CONVERSATION_NUM];
	// ���� �� ǥ�� �ε���
	SI32 siEndSprIndex[MAX_END_CONVERSATION_NUM];
#endif
	SI32 siStartConversationNum;
	SI32 siEndConversationNum;
	SI32 siGreetingSpr;
	SI32 siMiddleSpr;
	SI32 siClearSpr;

	cltQuestTxtInfo()
	{
		Init();
	}

	void Init()
	{
		for(SI32 i=0; i<MAX_START_CONVERSATION_NUM; ++i)
		{
			MStrCpy(szStartQuestConversation[i], TEXT(""), 1024);
			siStartSprIndex[i] = 0;
		}
		for(SI32 i=0; i<MAX_END_CONVERSATION_NUM; ++i)
		{
			MStrCpy(szEndQuestConversation[i], TEXT(""), 1024);
			siEndSprIndex[i] = 0;
		}
		
		MStrCpy(szQuestGreeting,TEXT(""),1024);
		MStrCpy(szQuestMiddle,TEXT(""),1024);
		MStrCpy(szQuestClear,TEXT(""),1024);

		siStartConversationNum = 0;
		siEndConversationNum = 0;
		siGreetingSpr = 0 ;
		siMiddleSpr = 0 ;
		siClearSpr = 0 ;
	}

	void Set(cltQuestTxtInfo* pclinfo)
	{
		for(SI32 i=0; pclinfo->siStartConversationNum; ++i)
		{
			MStrCpy(szStartQuestConversation[i], pclinfo->szStartQuestConversation[i], 1024);
			siStartSprIndex[i] = pclinfo->siStartSprIndex[i];
		}
		for(SI32 i=0; pclinfo->siEndConversationNum; ++i)
		{
			MStrCpy(szEndQuestConversation[i], pclinfo->szEndQuestConversation[i], 1024);
			siEndSprIndex[i] = pclinfo->siEndSprIndex[i];
		}

		MStrCpy(szQuestGreeting,pclinfo->szQuestGreeting,1024);
		MStrCpy(szQuestMiddle,pclinfo->szQuestMiddle,1024);
		MStrCpy(szQuestClear,pclinfo->szQuestClear,1024);

		siStartConversationNum = pclinfo->siStartConversationNum;
		siEndConversationNum = pclinfo->siEndConversationNum;
		siGreetingSpr = pclinfo->siGreetingSpr ;
		siMiddleSpr = pclinfo->siMiddleSpr ;
		siClearSpr = pclinfo->siClearSpr ;
	}
};

//---------------------------------
// ����Ʈ �Ϸ� ����. 
//---------------------------------

// [����] ����Ʈ Ŭ���� ����� enum���� ����
enum QUEST_CLEAR_COND
{
	QUEST_CLEAR_COND_NOTMEAN				= 0	//000 ����Ʈ Ŭ���� �����(�ƹ��͵� �ƴ�)

	,QUEST_CLEAR_COND_BONUSZERO				= 1	//001 ���� ���ʽ� ��ġ��  ��ȿ�ϴ�.
	,QUEST_CLEAR_COND_ITEM						//002 �������� ���� �־�� �Ѵ�. 
	,QUEST_CLEAR_COND_KILLMON					//003 ���� ������ óġ. 
	,QUEST_CLEAR_COND_MAKEITEM					//004 ��ǰ �����ؾ� �Ѵ�.  
	,QUEST_CLEAR_COND_OPENCHARSTATUS			//005 ĳ���� ����â�� ����� �Ѵ�. 
	,QUEST_CLEAR_COND_LEVEL						//006 ĳ���� ������ �� �̻��̾�� �Ѵ�. 
	,QUEST_CLEAR_COND_FULLLIFE					//007 �ִ� ü�� ä���. 
	,QUEST_CLEAR_COND_OPENSKILL					//008 ĳ���� ��� ����â�� ����� �Ѵ�. 
	,QUEST_CLEAR_COND_SKILL						//009 Ư�� ����� ������ �� �̻��̾�� �Ѵ�. 

	,QUEST_CLEAR_COND_EQUIP						//010 Ư�� ��ǰ ����. 
	,QUEST_CLEAR_COND_SELLNPC					//011 Ư�� NPC���� ������ �Ǵ�. 
	,QUEST_CLEAR_COND_MONEY						//012 ���� �� ��ƿ´�. 
	,QUEST_CLEAR_COND_BANK						//013 ���忡 ���� �� �Ա��Ѵ�. 
	,QUEST_CLEAR_COND_HUNGRY					//014 ������� ���ش�. 
	,QUEST_CLEAR_COND_REPAIRWEAPON				//015 ���⸦ �����Ѵ�.  
	,QUEST_CLEAR_COND_ITEMINFO					//016 ������ ������ Ȯ���Ѵ�.
	,QUEST_CLEAR_COND_NEWS						//017 ���� �̵��ͷ� �̵��ؾ� �Ѵ�. 
	,QUEST_CLEAR_COND_SKILLBONUSZERO			//018 ��� ������ 0���� ������ �Ѵ�.
	,QUEST_CLEAR_COND_GOMAP						//019 Ư�� ������ ���ٿ;� �Ѵ�.. 

	,QUEST_CLEAR_COND_GETQUEST					//020 Ư�� ����Ʈ�� �ο��޾ƾ� �Ѵ�.
	,QUEST_CLEAR_COND_SELLMARKET				//021 Ư�� ��ǰ�� ���ֿ��� �Ⱦƾ� �Ѵ�.  
	,QUEST_CLEAR_COND_BASICWEAPONSKILL			//022 �⺻ ���� ���� ����(��, Ȱ, ������)
	,QUEST_CLEAR_COND_STRUCTUREOPEN				//023 Ư�� �ǹ��� �����. 
	,QUEST_CLEAR_COND_ITEMINFODLG				//024 ��ǰ �� ����â ����. 
	,QUEST_CLEAR_COND_SELLSWORDNPC				//025 �˻��ο��� Ư�� ���� �Ǹ��Ѵ�. 
	,QUEST_CLEAR_COND_OTHERMINIHOME				//026 �ٸ� ��� ���� ����. 
	,QUEST_CLEAR_COND_OPENHEADCHAT				//027 ����â ���� 
	,QUEST_CLEAR_COND_BUYFROMPBSTORE			//028 ���λ������� �����ϱ�. 
	,QUEST_CLEAR_COND_OPENPBSTORE				//029 ���λ������� 

	,QUEST_CLEAR_COND_OPENSTOCKMARKET			//030 ���� ���� 	
	,QUEST_CLEAR_COND_STOCK						//031 �ֽ� ������. 
	,QUEST_CLEAR_COND_OPENCITYHALL				//032 ��� ���� 	
	,QUEST_CLEAR_COND_APPLYVILLAGE				//033 ���� �ֹ� ��û�ϱ�. 
	,QUEST_CLEAR_COND_USEFAN					//034 ��ä���� �̿��Ͽ� ���� ���� ���� 
	,QUEST_CLEAR_COND_USEWENNYOLDMAN			//035 Ȥ�θ����� �̿��Ͽ� ȣǰ ����� 
	,QUEST_CLEAR_COND_HORSE						//036 �� ������ 
	,QUEST_CLEAR_COND_OPENHUNT					//037 ������ ���� 	
	,QUEST_CLEAR_COND_USEWARPTICKET1			//038 �����̵��̿�� �̿��ϱ� (��������) 
	,QUEST_CLEAR_COND_USEWARPTICKET2			//038 �����̵��̿�� �̿��ϱ� (����Ͱ���) 

	,QUEST_CLEAR_COND_SUMMON					//040 ��ȯ�� �������� 
	,QUEST_CLEAR_COND_BROADCAST					//041 ���� ��� ��� 
	,QUEST_CLEAR_COND_SKILLMASTER				//042 �� ���� �������� ��ȸ�ϱ�. 
	,QUEST_CLEAR_COND_MAKEFRIEND				//043 ģ������ϱ�. 
	,QUEST_CLEAR_COND_LOOKPANSEO				//044 ���� �Ǽ�å�� ������ 
	,QUEST_CLEAR_COND_OPENVILLAGEBOARD			//045 ��� �Խ��� �����. 
	,QUEST_CLEAR_COND_FAMELEVEL					//046 �� ���� �ø���(1�����)  
	,QUEST_CLEAR_COND_USEITEM					//047 Ư�� ��ǰ�� Ư�� ������ŭ ����ϱ� 
	,QUEST_CLEAR_COND_SENDITEMBYPOST			//048 ������ ���� �ٸ� ������� ������ ��������.(������ �ƹ��ų� �����ϴ�.)  
	,QUEST_CLEAR_COND_VILLAGEDETAILINFO			//049 ���� �� ��������

	,QUEST_CLEAR_COND_USEWENNYOLDMAN2			//050 Ȥ�θ����� �̿��Ͽ� �����ϱ�. 
	,QUEST_CLEAR_COND_SUMMON2					//051 ��ȯ�� 2���� Ű���. 
	,QUEST_CLEAR_COND_ITEMMALL					//052 �����۸����� ������ �纸��. 
	,QUEST_CLEAR_COND_GGOMGICHANGE				//053 (X)���� ������ ������ �λ縻 �����ϱ�. 
	,QUEST_CLEAR_COND_BAG						//054 ���濡 ���� �־� ����. 
	,QUEST_CLEAR_COND_EQUIPPOS					//055 Ư�� ������ ����. (����, �����, ���, �Ź�, �Ǻ�, ����, ����, ���� ��..) 
	,QUEST_CLEAR_COND_FISH						//056 ����ڰ� �����ϱ� 
	,QUEST_CLEAR_COND_SUMMONBONUS				//057 ��� ��ȯ���� ���ʽ��� 0���� �����. 
	,QUEST_CLEAR_COND_BERESIDENT				//058 (X)���� �ֹ� �Ǳ�. 
	,QUEST_CLEAR_COND_VILLAGEHUNT				//059 (X)�Ұ��縮 ��� �����ϱ� . 

	,QUEST_CLEAR_COND_GOGU						//060 (X)����������ȣ�̺�Ʈ �����ϱ�.
	,QUEST_CLEAR_COND_SCROLL					//061 �ƹ������̳� ��� �����غ���. 
	,QUEST_CLEAR_COND_MAXUPSCROLL				//062 (X)�ִ볻����º��� �ƹ� ��� �����غ���. 
	,QUEST_CLEAR_COND_SELLTRADER				//063 �������ο��� ���� �Ⱦƺ���. (�� ������ ) 
	,QUEST_CLEAR_COND_FEEDHORSE1				//064 ���� ���ϴ� ���� ���̱�. 
	,QUEST_CLEAR_COND_FEEDHORSE2				//065 ����� ���̱�. 
	,QUEST_CLEAR_COND_REVIVESUMMON				//066 ��ȯ����Ȱ�̿�� ����Ͽ� ��ȯ�� �������.
	,QUEST_CLEAR_COND_DAILYQUEST				//067 �𺴰� ����Ʈ ����. 
	,QUEST_CLEAR_COND_SPECIALQUEST				//068 ��ι�����Ʈ ���� 
	,QUEST_CLEAR_COND_SKILLLEVEL				//069 (X)Ư�� ����� ������ Ư�� �������� �ø���.(����� å�� �о��..) 

	,QUEST_CLEAR_COND_SUMMONEVOLUTION			//070 ��ȯ���� ��ȭ��Ű��(��ȯ���� ��ȭ��Ű�� �ȴ�.)
	,QUEST_CLEAR_COND_CLEARQUEST				//071 Ư�� ����Ʈ�� ���� �Ѵ�. 
	,QUEST_CLEAR_COND_HORSESPEED				//072 ���ӵ��� 10�̻� �����. 
	,QUEST_CLEAR_COND_SUMMONSCROLL				//073 ������ ����Ͽ� ��ȯ�� ��ȭ�ϱ�. 
	,QUEST_CLEAR_COND_SUMMONBATTLE				//074 ��ȯ���� ����(para1)�� para2��ŭ ����غ���. 
	,QUEST_CLEAR_COND_USEMAGIC					//075 �ƹ� �����̳� Ư�� ȸ�� ����� ����. 
	,QUEST_CLEAR_COND_FARM						//076 Ư�� �۹�(para1)�� Ư������(para2)��ŭ ��Ȯ�϶�. 
	,QUEST_CLEAR_COND_STOCKPROMPT				//077 (X)�ֽ� ������ �ڸ������� ���̰� �ϱ�. 
	,QUEST_CLEAR_COND_MINE						//078 Ư�� ����(para1)�� Ư������(para2)��ŭ ä���϶�.
	,QUEST_CLEAR_COND_WEBFAME					//079 (X)���� �湮�ڼ��� �÷��� ������ �ޱ�(���� 120�̻�).

	,QUEST_CLEAR_COND_HAVEHOUSE					//080 (X)������ ������ ��������. (���� 100�̻�) 
	,QUEST_CLEAR_COND_MAKEREQUEST				//081 (X)�ٸ� ������� �����Ƿ� �غ���, �ƹ��ų� �����Ƿ��ؼ� �����Ǹ� Ŭ����(�߷�) 
	,QUEST_CLEAR_COND_GONPC						//082 Ư�� NPC���� ���� �޴� ������ ����
	,QUEST_CLEAR_COND_SETFATHER					//083 ���� �����ϱ�
	,QUEST_CLEAR_COND_CLICKITEMINFO				//084 Ư�� �������� ���� ���� Ŭ���� ����
	,QUEST_CLEAR_COND_OPENMAKEITEM				//085 ����â ����
	,QUEST_CLEAR_COND_CLICKMAKEBUTTON			//086 ��ư ������
	,QUEST_CLEAR_COND_TUTORIALMAKEITEM			//087 Ư�� ������ ���� ����Ʈ(����(����,������,��ų)�� ������ �ʰ� ������ ���ش�. ���� ��� �̿��� �ٸ� �������� �Ҹ��ŰŰ�� ��)
	,QUEST_CLEAR_COND_ITEMCHECK					//088 Ư�� �������� ������ �־�� �Ѵ�. ������� �ʰ� üũ�� �Ѵ�.
	,QUEST_CLEAR_COND_UPITEMTOMARKET			//089 Ư�� �������� ���Ͽ� �÷��� �Ѵ�.

	,QUEST_CLEAR_COND_OPENENCHANTITEM			//090 ��þƮ â�� ����� �Ѵ�.
	,QUEST_CLEAR_COND_SETENCHANTITEM			//091 Ư�� �������� ��þƮ â�� �÷��� �Ѵ�.
	,QUEST_CLEAR_COND_SETENCHANTELEMENT			//092 �ƹ� �Ӽ��̳� ��þƮ �Ӽ��� �����ؾ� �Ѵ�.
	,QUEST_CLEAR_COND_ENCHANTITEM				//093 Ư�� �������� ��þƮ �ؾ� �Ѵ�.
	,QUEST_CLEAR_COND_WARPTOPALACE				//094 �溹������ �����ϱ�
	,QUEST_CLEAR_COND_PRIVATETRADE				//095 ���ΰŷ� �غ���
	,QUEST_CLEAR_COND_SELLFROMPBSTORE			//096 ���λ������� ������ �Ⱦƺ���
	,QUEST_CLEAR_COND_MAKEBOOK					//097 å ������
	,QUEST_CLEAR_COND_HUNTMAPINFODLG			//098 ����� ����â�� �����
	,QUEST_CLEAR_COND_SEARCHMONSTERINFO			//099 Ư�� ������ ������ �˻��� ���� (para1) �� ���� KIND_UNIQUE

	,QUEST_CLEAR_COND_PARTYHUNTING				//100 ��Ƽ�� �ΰ� ����� �Ѵ�.
	,QUEST_CLEAR_COND_MAGICINFODLG				//101 ���� ����â�� �����.
	,QUEST_CLEAR_COND_OPENHOUSE					//102 �Ӵ�â�� �����
	,QUEST_CLEAR_COND_OPENREALESTATEMARKET		//103 �ε��� �����
	,QUEST_CLEAR_COND_BLACKARMY					//104 ���� ���� ������ ����
	,QUEST_CLEAR_COND_OPENHORSEMARKET			//105 ���� �ǹ� �����
	,QUEST_CLEAR_COND_SUMMONEVOLUTIONRANK		//106 ��ȯ���� Ư�� ��ޱ��� ��ȭ��Ű�� (para1 == Ư�� ���)
	,QUEST_CLEAR_COND_REVIVESUMMONBYDOLL		//107 ��ȯ���� ������ ����Ͽ� ��Ȱ��Ų��
	,QUEST_CLEAR_COND_OPENHOZODLG			 	//108 ȣ���Ǽ�(��ȣ��)�� ����â�� �����
	,QUEST_CLEAR_COND_OPENBYUNGZODLG		 	//109 �����Ǽ�(û���)�� ����â�� �����

	,QUEST_CLEAR_COND_OPENGONGZODLG			 	//110 �����Ǽ�(������)�� ����â�� �����
	,QUEST_CLEAR_COND_OPENIZODLG			 	//111 �����Ǽ�(���۰�)�� ����â�� �����
	,QUEST_CLEAR_COND_OPENGOONZUDLG			 	//112 ������ ����â�� �����
	,QUEST_CLEAR_COND_VOTEKING					//113 ���ּ��ſ� ������ ����
	,QUEST_CLEAR_COND_USEWARPTICKET3			//114 �����̵��̿�� �̿��ϱ� (ģ�����԰���)
	,QUEST_CLEAR_COND_BUYTOPBSTORE				//115 ���λ����� ���� �����ϱ�
	,QUEST_CLEAR_COND_NONE						//116 �׳� Ŭ���� �Ǵ� ����Ʈ �̴�
	,QUEST_CLEAR_COND_ENCHANTANYITEM			//117 �ƹ� �������̳� ��þƮ �غ���
	,QUEST_CLEAR_COND_HUNT_ITEM					//118 ������� ������ ȹ��.
	,QUEST_CLEAR_COND_GOHUNTMAP					//119 ������ ����

	,QUEST_CLEAR_COND_MAGICACTIVE				//120 ���� ����ϱ� (����Ű )
	,QUEST_CLEAR_COND_OPENFRIEND				//121 ģ�� ���â�� ����.
	,QUEST_CLEAR_COND_OPENMASTER				//122 ���� ����â�� ����.
	,QUEST_CLEAR_COND_OPENMAKEREQUEST			//123 ���� �Ƿ�â�� ����.
	,QUEST_CLEAR_COND_MAKEREQUESTSTART			//124 ���� �Ƿ� ���� ( �����Ƿ� �Ѵٴ� ��ǳ�� ����).
	,QUEST_CLEAR_COND_DISASSEMBLEITEM			//125 �����Ѵ�.(����ũ �������)
	,QUEST_CLEAR_COND_OPENNAMINGQUEST			//126 ��Ī ����Ʈ â�� ����.
	,QUEST_CLEAR_COND_SUMMONACTIVE				//127 ��ȯ�� Ȱ��ȭ
	,QUEST_CLEAR_COND_SUMMONDIE					//128 ��ȯ�� ���.
	,QUEST_CLEAR_COND_SUMMONCHANGESTATUS		//129 ��ȯ�� ���� â ����

	,QUEST_CLEAR_COND_PARTYKILLMON				//130 ��Ƽ�� ����ϱ�.
	,QUEST_CLEAR_COND_SUMMONATTACK				//131 ��ȯ���� ���� �����غ���
	,QUEST_CLEAR_COND_SUMMONLEVELUP				//132 ��ȯ�� ������
	,QUEST_CLEAR_COND_MAKEINTBOOK				//133 �߱�å �����
	,QUEST_CLEAR_COND_SETGREETING				//134 �λ縻 ����
	,QUEST_CLEAR_COND_OPENGUILD					//135 ���â ����
	,QUEST_CLEAR_COND_APPLYGUILD				//136 ��� ����, ����( ����ߵ� ���)
	,QUEST_CLEAR_COND_LOOKPRISON				//137 ������ ��Ȳ ����
	,QUEST_CLEAR_COND_OPENGOONZUDLG_NOTICE		//138 ���� ��å ����
	,QUEST_CLEAR_COND_MAKEPARTY					//139 ��Ƽ �α�

	,QUEST_CLEAR_COND_SORTRESIDENT				//140 ���� ���� ���� - ���� �ֹμ� ����
	,QUEST_CLEAR_COND_CLICKITEMPROPERTY			//141 ������ �Ӽ����� Ŭ��
	,QUEST_CLEAR_COND_OPENSKILLETC				//142 ��Ÿ ��ų ��ư ������
	,QUEST_CLEAR_COND_MINENOSKILL				//143 ä���ϱ�( ��ų �ø��� �ʾƵ� ���� )
	,QUEST_CLEAR_COND_SITDOWN					//144 �ɱ�(�Ͼ��)
	,QUEST_CLEAR_COND_NPCINFO					//145 NPC������ Ȯ���Ѵ�.
	,QUEST_CLEAR_COND_HITMON					//146 ���� ������ ������.
	,QUEST_CLEAR_COND_OPENGUILDUSER				//147 ���â���� ������û ����
	,QUEST_CLEAR_COND_SEARCHSTOCKINFO			//148 �������� â���� �ֽİŷ��� �˻��ϱ�
	,QUEST_CLEAR_COND_CLICKSTOCKOFFER		 	//149 ����û�� ��ư Ŭ���ϱ�

	,QUEST_CLEAR_COND_CLICKCITYHALLFUND		 	//150 ��û->��û�ڱ� ��ư Ŭ��
	,QUEST_CLEAR_COND_CLICKGENERALMETTING	 	//151 ��û->������ȸ ��ư Ŭ��
	,QUEST_CLEAR_COND_CLICKPERSONALSHOP		 	//152 Ŀ�´�Ƽ->���λ��� Ŭ��
	,QUEST_CLEAR_COND_OPENITEMMALL			 	//153 ������ �� â ����
	,QUEST_CLEAR_COND_ANGELLISTCLICK		 	//154 ���� -> ��ȣõ�� ���� -> ��ȣõ�� ��� Ŭ��
	,QUEST_CLEAR_COND_POLICESETCLICK		 	//155 ���� -> ���Ȱ� ���� Ŭ��
	,QUEST_CLEAR_COND_SEARCHFARM			 	//156 �������� -> ���� -> ���� ����
	,QUEST_CLEAR_COND_FARMNOSKILL			 	//157 ���忡�� ������ ȹ��(��ų�ʿ����)
	,QUEST_CLEAR_COND_LEASECLICK			 	//158 â�� -> ������û Ŭ��
	,QUEST_CLEAR_COND_GETMAGICLAMPQUEST		 	//159 ������� ����Ʈ �ޱ�

	,QUEST_CLEAR_COND_OPENQUESTDIALOG		 	//160 ����Ʈ â ����
	,QUEST_CLEAR_COND_FISHNOSKILL			 	//161 �����ؼ� ������ ȹ�� �غ���(��ų�ʿ����)
	,QUEST_CLEAR_COND_ISLEARNED_MANUFACTURE	 	//162 ������ų�߿� �ϳ��� ������ ������ ����Ʈ Ŭ���� 
	,QUEST_CLEAR_COND_ISGET_MANUFACTUREQUEST 	//163 ���縮���� �ִ� ���� ����Ʈ �� ����̶� 1�ܰ� �̻� Ŭ����
	,QUEST_CLEAR_COND_REQUESTMENTORSUCCESS	 	//164 ����â -> ���´Խ�û Ŭ���ؼ� ����Ʈ�� ����ϱ�(������ �־ ��)
	,QUEST_CLEAR_COND_TAKEPUPILS				//165 �������� ���ڷ� �޾ƾ� �Ѵ�
	,QUEST_CLEAR_COND_CHATTOBEGGINER			//166 �ʺ��� ����Ʈ�� ���������� �Ӹ� ��û�ϱ�
	,QUEST_CLEAR_COND_CHECKSTATUS				//167 (Para1)[Quest-LoadTxt.cpp:515����]�� ������ (Para2) �̻��̾�� �Ѵ�
	,QUEST_CLEAR_COND_ALLWEAPONSKILL			//168 ���⽺ų �߿� ������(para1) �̻��� �ִ� �� Ȯ��
	,QUEST_CLEAR_COND_MEMOCLICK					//169 ģ�����-> �޸��ư Ŭ��

	,QUEST_CLEAR_COND_MOVETOGROUPCLICK			//170 ģ�����-> �׷��̵� ��ư Ŭ��
	,QUEST_CLEAR_COND_EQUIPBAG					//171 ����ĭ 2ĭ �߿� �Ѱ��� ������ ��â�Ǿ� �ִ°�?
	,QUEST_CLEAR_COND_KILLDARKSOLDIER			//172 ���� ���ܸɹ� �ƹ��� (para2)��ŭ �׿��� �Ѵ�.
	,QUEST_CLEAR_COND_MAKE_RAREITEM				//173 �ű�,��ǰ,ȣǰ �������� �������Ѵ�(para1�� 0�϶��� �ƹ��ų�, �׿ܿ��� unique@ para2�� ����)
	,QUEST_CLEAR_COND_FULL_ORGAN				//174 ���� ����� ��� �Ѱ��̶� Max�̸� Ŭ����
	,QUEST_CLEAR_COND_TWOWAYKILLMON				//175 ȥ�� Ȥ�� ��Ƽ �ΰ� ����ص� ���� ų���� ���� �ö�
	,QUEST_CLEAR_COND_BUYMARKET					//176 ���忡�� ���� ���
	,QUEST_CLEAR_COND_OPENFATHERDIALOG			//177 ����â �����
	,QUEST_CLEAR_COND_ORDERTOMARKET				//178 ���忡 ���� �ø���
	,QUEST_CLEAR_COND_OPENPOSTOFFICEDIALOG		//179 ��ü��â �����

	,QUEST_CLEAR_COND_MAKELEVELITEM				//180 Para1�� �ش��ϴ� ������ �������� Para2��ŭ �����
	,QUEST_CLEAR_COND_TAKEEQUIPLEVELWEAPON		//181 Para1�� �ش��ϴ� ������ ���⸦ Para2��ŭ ��������
	,QUEST_CLEAR_COND_GETELEMENT_RESTORE		//182 ȯ���� ���� Para2��ŭ ���� ������ ���
	,QUEST_CLEAR_COND_GETPOWDER_RESTORE			//183 ȯ���� ���� Para2��ŭ �Ӽ����� ������ ���
	,QUEST_CLEAR_COND_ENCHANTEQUIPLEVELWEAPON	//184 Para1�� �ش��ϴ� ������ ���⸦ ��þƮ �غ���
	,QUEST_CLEAR_COND_TAKEITEM_MATERIAL			//185 Para1�� �ش��ϴ� �������� Para2������ ����� �ִ� ������ �������
	,QUEST_CLEAR_COND_TAKEWEAPONHAVESLOT		//186 ������ �ִ� ���⸦ Para2��ŭ �����Ͷ�
	,QUEST_CLEAR_COND_ARTIFACTMIXWEAPON			//187 Para2�� ������ŭ ���� �����ۿ� ����ü �����غ���
	,QUEST_CLEAR_COND_MAKECRYSTAL				//188 Para1�� ����� ����ü�� Para2������ŭ ������
	,QUEST_CLEAR_COND_TEACHERSET				//189 [����] ���´� �����ϱ� ��ư Ŭ��. => 2008-10-7

	,QUEST_CLEAR_COND_SUMMONBONUSZERO			//190 ��ȯ�� ��ȯ���� ���ʽ� ��ġ�� 0���� �����
	,QUEST_CLEAR_COND_TUTORIALMAKELEVELITEM		//191 Para1�� �ش��ϴ� ������ �������� Para2��ŭ ����� - ��ų ���� üũ ����
	,QUEST_CLEAR_COND_SWORDSKILLCLICK			//192 �˷���(��������) â���� �˼���ư Ŭ���غ���
	,QUEST_CLEAR_COND_LEARNWEAPONSKILL			//193 Para1�ܰ��� ��ų�� Para2�̻� ����
	,QUEST_CLEAR_COND_PVPWIN					//194 PVP�¸��� para2�̻� �ϱ�
	,QUEST_CLEAR_COND_PVPLEAGUERESERVE			//195 PVP���� �����غ���
	,QUEST_CLEAR_COND_PVPLEAGUEWIN				//196 PVP���� �¸��� para2�̻� �ϱ�
	,QUEST_CLEAR_COND_TWOWAYKILLMONBONUS		//197 ȥ�� Ȥ�� ��Ƽ �ΰ� ����ص� ���� ų���� ���� �ö�(���� Ŭ���� ������� ��Ƽ �ο��� 2�� �̻��� ��� ���� ���� �� ���ʽ� 20% �߰�)
	,QUEST_CLEAR_COND_ARTIFACTMIX				//198 Para2��ŭ ��Ƽ��Ʈ ������ ����
	,QUEST_CLEAR_COND_SETMYKEY					//199 ������ �޴� ������ ����

	,QUEST_CLEAR_COND_SUMMONHOUSE_INPUT			//200 ��ȯ�� �����ҿ� ��ȯ�� �ֱ�
	,QUEST_CLEAR_COND_SUMMONHOUSE_OUTPUT		//201 ��ȯ�� �����ҿ��� ��ȯ�� ����
	,QUEST_CLEAR_COND_MARKETCONDITION			//202 Ŭ��� �ü� Ȯ���� ���� (Para1�� ������ Ÿ���� �Ϲݰ˻� �غ���)
	,QUEST_CLEAR_COND_FIND_TREASUREBOX			//203 ����ã�� �̺�Ʈ	// �ϴ� Ŭ���� ����Ǹ� ����� ����.
	,QUEST_CLEAR_COND_ENCHANTEQUIPPOS			//204 ���������̻� ��æƮ�� ��� ������ ����
	,QUEST_CLEAR_COND_BUFFCLICK					//205 �κ��丮 â�� �Ⱓ����ư - ���� ��ư Ŭ���� ����
	,QUEST_CLEAR_COND_GONPC_INFORMATION			//206 Ư�� ���ǽ÷� ���� �޴��� Ŭ���ϰ� �Ǹ� Ư���� ������ ����.
	,QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS	//207 �Ҿ���� ���� - ���ͷ� �����Ŀ� ������ ��ġ �ֺ��� �����ؼ� ���� ���� �ľ��ϱ�.
	,QUEST_CLEAR_COND_MAPKILLMON				//208 para1 �ʿ� �ִ� ���� para2���̱�
	,QUEST_CLEAR_COND_MAKESKILLEXPUP			//209 [����] ���� ����ġ�� 1 �̻� �ö󰡾� �Ѵ�.

	,QUEST_CLEAR_COND_LAMPGOMAP					//210 [����] ������� ���� ��ȸ ����Ʈ�� ���� (���� GOMAP������ ���� ����ϴ°��� ������ ���� �и���)

	,QUEST_CLEAR_COND_FORTUNE_NPCCOMPLETE		//211 [����] 2010�ų��̺�Ʈ - npc

	, QUEST_CLEAR_COND_SEARCH_TOTALMAP			//212 �Ȱ��̱� - ��ü�������� Ư�� ��ġ �˻� para1 : CheckIndex, para2 : SelectIndex
	, QUEST_CLEAR_COND_USE_SKILLBOOK			//213 �Ȱ��̱� - ������ų�� ����ϱ�         para1 : 1         , para2 : amount

	//-----------------------------------
	// �� ���� �߰��� �ּ���
	//-----------------------------------
	,MAX_QUEST_CLEAR_COND_NUMBER
};


class cltQuestClearConditionInfo{
public:
	SI16	siFlag;			// � ������ ��ȿ���� �ľ�. 

	SI32	siPara1;
	SI32	siPara2;

	cltQuestClearConditionInfo()
	{
		Init();
	}
	void Init()
	{
		siFlag	= 0;
		siPara1	= 0;
		siPara2 = 0;
	}

	void Set(cltQuestClearConditionInfo* pclinfo)
	{
		siFlag	= pclinfo->siFlag;
		siPara1	= pclinfo->siPara1;
		siPara2 = pclinfo->siPara2;
	}

};

// Ư�� ��ǥ���� �����ۻ���ϱ� ����Ʈ
struct stCoordinate_UseItem
{
	SI32 m_siQuestType;
	SI32 m_siQuestUnique;
	SI32 m_siMapIndex;
	SI32 m_siX;
	SI32 m_siY;
};

//---------------------------------
// ����Ʈ ���� 
//---------------------------------
class cltQuestRewardInfo{
public:
	
	GMONEY siMoney;			// ���� �������� �ش�. 
	
	SI32 siExp;				// ����ġ ����. 
	
	SI16 siFameExp;			// �� ����ġ ���� 
	
	SI32 siNCoin;			// NCoin ����. 
	
	BOOL bMoveBuf;			// �̵��ӵ� ���� ����

	bool bSelectItem;		// ������ ����

	// ���̹� ����
	SI32 siNamingIndex;		// � ������ ���̹�����
	SI32 siNamingLevel;		// ��ܰ� ���̹�����.

	//KHY - 0219 - ��ų ����ġ ����.
	SI32 siSkillType;		// � ��ų Ÿ������
	SI32 siSkillExp;		// ��ų ����ġ

	bool bIsGetMaterial;	// ��������� ���� ���� ���ΰ�?

	bool bApplyNpcRate;		// �� ���� NPCRate�� �������� ����

	//[����] : 2010�ų��̺�Ʈ - ����� ���� (Ư�� ������ �ϳ� �����ش�. �ϴ��� ������ '��'������ ����)
	bool bDeBuff;

	// ������ ����.
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_QUEST_REWARD_NUMBER>		siItemUnique;
	NSafeTArray<SI16, MAX_QUEST_REWARD_NUMBER>		siItemNum;
	NSafeTArray<SI32, MAX_QUEST_REWARD_NUMBER>		siItemUseDate;
#else
	SI16 siItemUnique[MAX_QUEST_REWARD_NUMBER];
	SI16 siItemNum[MAX_QUEST_REWARD_NUMBER];
	SI32 siItemUseDate[MAX_QUEST_REWARD_NUMBER];
#endif
	

	cltQuestRewardInfo()
	{
		Init();
	}

	void Init()
	{
		memset(this,0,sizeof(cltQuestRewardInfo));		

	}

	void Set(cltQuestRewardInfo* pclinfo)
	{
		siMoney			= pclinfo->siMoney;
		bApplyNpcRate	= pclinfo->bApplyNpcRate;

		siExp			= pclinfo->siExp;
				
		siFameExp		= pclinfo->siFameExp;
		siNCoin			= pclinfo->siNCoin;	
		bMoveBuf		= pclinfo->bMoveBuf;

		siNamingIndex	= pclinfo->siNamingIndex;
		siNamingLevel	= pclinfo->siNamingLevel;

		siSkillType		= pclinfo->siSkillType;
		siSkillExp		= pclinfo->siSkillExp;

		bIsGetMaterial	= pclinfo->bIsGetMaterial;

		bSelectItem		= pclinfo->bSelectItem;

		for( SI32 i = 0; i < MAX_QUEST_REWARD_NUMBER ; i++ )
		{
			siItemUnique[i]		= pclinfo->siItemUnique[i];
			siItemNum[i]		= pclinfo->siItemNum[i];
			siItemUseDate[i]	= pclinfo->siItemUseDate[i];
		}

		bDeBuff			= pclinfo->bDeBuff;
	}

	// ���� ������ �ؽ�Ʈ�� ��Ƴ���.
	bool GetExplainText(TCHAR* ptext, SI16 txtSize);
};

//--------------------------------
// ����Ʈ �ο� ����. 
//--------------------------------
class cltQuestInitConditionInfo{
public:
	SI32 siLevel;
	SI32 siSkillUnique;
	SI32 siSkillLevel;
	SI32 siMustClearQuestUnique;

	cltQuestInitConditionInfo()
	{
		Init();
	}
	void Init()
	{
		siLevel			=	0;
		siSkillUnique	=	0;
		siSkillLevel	= 	0;
		siMustClearQuestUnique = 0;
	}
	
	cltQuestInitConditionInfo(SI32 level, SI32 skillunique, SI32 skilllevel, SI32 mustclearquestunique )
	{
		siLevel			=	level;
		siSkillUnique	=	skillunique;
		siSkillLevel	= 	skilllevel;
		siMustClearQuestUnique = mustclearquestunique;
	}

	void Set(cltQuestInitConditionInfo* pclinfo)
	{
		siLevel			=	pclinfo->siLevel;
		siSkillUnique	=	pclinfo->siSkillUnique;
		siSkillLevel	= 	pclinfo->siSkillLevel;
		siMustClearQuestUnique = pclinfo->siMustClearQuestUnique;
	}
};

//---------------------------------
// �Ѱ� ����Ʈ�� ����. 
//---------------------------------
class cltQuestInfoCommon{
public:
	SI32 siUnique;		// ����Ʈ ���� ����ũ. 

	//--------------------
	// �Ϸ�����. 
	//--------------------
	cltQuestClearConditionInfo clQuestClearConditionInfo;

	//-------------------
	// ���� 
	//--------------------
	cltQuestRewardInfo clQuestRewardInfo;

	cltQuestInfoCommon()
	{
		siUnique	= 0;
	}

	void Init()
	{
		siUnique	= 0;

		clQuestClearConditionInfo.Init();
		clQuestRewardInfo.Init();
	}

	void Set(cltQuestInfoCommon* pclinfo)
	{
		siUnique	= pclinfo->siUnique;
		clQuestClearConditionInfo.Set(&pclinfo->clQuestClearConditionInfo);
		clQuestRewardInfo.Set(&pclinfo->clQuestRewardInfo);

	}
};

class cltQuestInfo : public cltQuestInfoCommon{
public:
	SI32 siType;		// ����Ʈ�� Ÿ��. 

	TCHAR szTitleText[MAX_TITLE_TEXT_SIZE];

	//--------------------
	// �ʱ��ʰ� 
	//--------------------
	cltQuestInitConditionInfo clInitConditionInfo;

	//--------------------
	// �߰� �׼� 
	//--------------------
	cltQuestMiddleInfo clMiddleInfo;


	TCHAR*	pImageFileName;

	cltQuestInfo() : cltQuestInfoCommon()
	{
		szTitleText[ 0 ] = NULL;
		siType		= 0;

		pImageFileName		= NULL;
	}
	
	~cltQuestInfo()
	{
		if(pImageFileName)
		{
			delete[] pImageFileName;
			pImageFileName = NULL;
		}
	}

	void Init()
	{
		cltQuestInfoCommon::Init();

		siType		= 0;
	
		szTitleText[ 0 ] = NULL;
		clInitConditionInfo.Init();
		clMiddleInfo.Init();
	}

	void Set(cltQuestInfo* pclinfo)
	{
		cltQuestInfoCommon::Set( (cltQuestInfoCommon*)pclinfo);

		siType = pclinfo->siType;

		MStrCpy( szTitleText, pclinfo->szTitleText, MAX_TITLE_TEXT_SIZE );
		clInitConditionInfo.Set(&pclinfo->clInitConditionInfo);
		clMiddleInfo.Set(&pclinfo->clMiddleInfo);
	}

	void Set(SI32 type, SI32 unique, cltQuestInitConditionInfo* pclinitcond, cltQuestClearConditionInfo* pclclearcond, cltQuestRewardInfo* pclreward, 
		TCHAR* titletext, TCHAR* pimagefilename);
};

class cltMissionQuestInfo : public cltQuestInfoCommon
{
private:
	SI32	m_siLeftTimeSec;

public:
	cltMissionQuestInfo() : cltQuestInfoCommon()
	{
		Init();
	}

	~cltMissionQuestInfo()
	{		
	}

	void Init()
	{
		cltQuestInfoCommon::Init();
		m_siLeftTimeSec		= 0;
	}

	void Set(cltMissionQuestInfo* pclinfo)
	{
		cltQuestInfoCommon::Set((cltQuestInfoCommon*)pclinfo);

		m_siLeftTimeSec	= pclinfo->m_siLeftTimeSec;
	}

	bool IsTimeLeft()
	{
		return (bool)(m_siLeftTimeSec > 0);
	}

	bool TimeReduce(SI32 siTimeSec)
	{
		// 2�䱥 ���Ÿ� ���� �̼��ϰ�쿣 �ð��� �پ���� �ʴ´�. (�ð������� ����)
		if ( MISSIONQUEST_UNIQUE_REMOVE_UNLUCK == siUnique )
		{
			return IsTimeLeft();
		}
		else
		{
			m_siLeftTimeSec -= siTimeSec;
			if(m_siLeftTimeSec < 0)		m_siLeftTimeSec = 0;

			return IsTimeLeft();
		}
	}

	inline SI32 GetLeftTime()						{		return m_siLeftTimeSec;				}
	inline void SetLeftTime(SI32 siLeftTimeSec)		{		m_siLeftTimeSec = siLeftTimeSec;	}	
};

//----------------------------------
// Person�� ����Ʈ ����. 
//----------------------------------
#define MAX_WORD_ASSEMBLY_CHAR_NUMBER	10
class cltPQuestInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<bool, MAX_WORD_ASSEMBLY_CHAR_NUMBER>	bWordAssemblySwitch;
#else
	bool bWordAssemblySwitch[MAX_WORD_ASSEMBLY_CHAR_NUMBER];
#endif

	SI32 siClearWordSpecialQuest;
	SI32 siEventClearWordSpecialQuest;		// �̺�Ʈ �Ⱓ�� �ܾ����� ����Ʈ Ŭ���� Ƚ �� ������ ���� ����.
	SI32 siClearCount;

	// ����Ʈ ����.  
	cltQuestInfoCommon	clSpecialQuestInfo;
	cltQuestInfoCommon	clNamingQuestInfo;
	cltQuestInfoCommon	clHappyBeanQuestInfo;		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.	

	// �̼� ����Ʈ ����
	cltMissionQuestInfo	clMissionQuestInfo;			// �̼� ����Ʈ - by LEEKH 2008-09-09

	// �ų��̺�Ʈ ����Ʈ (��������)
	cltQuestInfoCommon	clRemoveUnLuckQuestInfo;	// [����-2009.10.14]
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltPersonQuestUnitInfo, MAX_QUEST_TYPE>		clUnit;
#else
	cltPersonQuestUnitInfo clUnit[MAX_QUEST_TYPE];
#endif

	cltPQuestInfo()
	{
		SI32 i;

		for(i = 0;i < MAX_WORD_ASSEMBLY_CHAR_NUMBER;i++)
		{
			bWordAssemblySwitch[i] = false;
		}

		siClearWordSpecialQuest = 0 ;
		siEventClearWordSpecialQuest = 0;
		siClearCount = 0;

		clSpecialQuestInfo.Init();
		clNamingQuestInfo.Init();		
		clHappyBeanQuestInfo.Init();		//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����. �ϴ� �˻�������.
		clMissionQuestInfo.Init();
		for(i = 0;i < MAX_QUEST_TYPE;i++)				{		clUnit[i].Init();					}
	}

	void Set(cltPQuestInfo* pclinfo)
	{
		SI32 i;

		for(i = 0;i < MAX_WORD_ASSEMBLY_CHAR_NUMBER;i++)
		{
			bWordAssemblySwitch[i] = pclinfo->bWordAssemblySwitch[i];
		}

		siClearWordSpecialQuest = pclinfo->siClearWordSpecialQuest ;
		siEventClearWordSpecialQuest = pclinfo->siEventClearWordSpecialQuest;

		clSpecialQuestInfo.Set(&pclinfo->clSpecialQuestInfo);
		clNamingQuestInfo.Set(&pclinfo->clNamingQuestInfo);		
		clHappyBeanQuestInfo.Set(&pclinfo->clHappyBeanQuestInfo);	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�. ����. �ϴ� �˻�������.

		clMissionQuestInfo.Set(&pclinfo->clMissionQuestInfo);
		for(i = 0;i < MAX_QUEST_TYPE;i++)			{	clUnit[i].Set(&pclinfo->clUnit[i]);								}
	}

	// Ư�� ����Ʈ�� ���������� Ȯ���Ѵ� 
	bool IsQuestGoing(SI32 clearcond, SI16* ptype, SI16* punique, SI16* prara1, SI16* ppara2, SI32* pstartindex = NULL);
	bool IsQuestGoing( SI32 siClearCondition );

	// Ư�� �����, Para1/2���� ������ ����Ʈ�� �ִ°�
	bool IsSameParaQuestGoing( SI32 siClearCond, SI16 siPara1, SI16 siPara2=0 );

	// �Ķ��Ÿ�� ������Ų��. 
	bool IncPara(SI32 questtype, SI32 para1, SI32 incnum);

	// ���� ��ǰ�� ���� ������Ų��. 
	SI32 IncMakeItem(SI32 itemunique, SI32 incnum);

	// ����� ��ǰ�� ���� ������Ų��. 
	SI32 IncUseItem(SI32 itemunique, SI32 incnum);

	// Ư�� Ÿ���� ����Ʈ�� �������̰ų� ����� ���� �ִ��� Ȯ���Ѵ�. 
	bool IsQuestClearOrGoing(SI32 questtype);

	// �������� ����Ʈ�� DB�� �����Ѵ�. 
	bool SaveGoingQuestToDB(cltCharCommon* pclchar);

	// Ư�� ����Ʈ�� �����°�. 
	bool IsQuestEnd(SI32 questunique);

	// Ư�� ����ũ�� ����Ʈ�� �����ߴ°�. 
	bool IsClear(cltQuestManager* pclquestmanager, SI32 questunique);
	
	// Ư�� Ÿ���� ����Ʈ�� ��� �Ϸ�Ǿ����� Ȯ���Ѵ�. 
	bool IsAllClear(cltQuestManager* pclquestmanager, SI32 questtype);

	// �Ϸ�� ����Ʈ�� ���� ���Ѵ�. 
	SI32 GetClearQuestNum(cltQuestManager* pclquestmanager, SI32 questtype);

	//-----------------------------------------
	// �ܾ� ���� ���� 
	//-----------------------------------------
	// ��ι� ����Ʈ�� �ܾ� ���߱Ⱑ  �Ϸ�Ǿ��ٸ�, 
	bool IsWordAssembleCompleted(cltQuestManager* pclQuestManager);

	// �ܾ� ���� ������ �ʱ�ȭ�Ѵ�. 
	void InitWordAssemble();

	// ��ι� ����Ʈ ���� �ܾ� ������
	bool GetWordAssembleText( cltQuestManager* pclQuestManager, TCHAR* pszBuffer, SI32 siBufferSize );
};

//---------------------------------
// ����Ʈ ������. 
//---------------------------------
class cltQuestManager{
public:
	HWND m_hDlg;

	BOOL DlgRectInitSwitch;
	RECT DlgRect;
	HBITMAP hPortraitBitmap;
	HBITMAP hItemImage;
	SI32 siKind;				// NPC Kind
	SI32 siID;					// ����� �Ǵ� ĳ����. 
	SI32 siQuestType;			// � Ÿ���� ����Ʈ�ΰ� ?
	SI32 siCurrentQuestUnique;	// ���� �� ��ȭ���ڰ� �����ϴ� ����Ʈ
	SI32 siCurrentQuestStep;	// ���� �������� ����Ʈ�� �ܰ�. 
	SI32 siStartConversationNum;		// ����Ʈ ������
	SI32 siStartConversationCounter;	// ��ȭ �����
	SI32 siEndConversationNum;			// ����Ʈ Ŭ������
	SI32 siEndConversationCounter;		// ��ȭ �����
	SI32 siViewState;			// 0: ��ȭ���� 1: �ӹ�����
	BOOL bNewQuseOpened;		// ����(�ӽ÷�) �� ����Ʈâ�� �����°�?
	BOOL bNewQuestDoing;		// ���� �� ����Ʈ�� �ϴ���?

	SI32 siWordAssemblyNumber;
	TCHAR szWordAssemblyString[MAX_WORD_ASSEMBLY_CHAR_NUMBER][10];

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<SI32, MAX_QUEST_PER_TYPE_NUMBER>, MAX_QUEST_TYPE>	siQuestBitInfo;
#else
	// ����Ʈ�� ��Ʈ�� ����. 
	SI32 siQuestBitInfo[MAX_QUEST_TYPE][MAX_QUEST_PER_TYPE_NUMBER];
#endif

	// ����Ʈ Ÿ�� �̸�. 
	TCHAR szQuestTypeName[MAX_QUEST_TYPE][128];

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<cltQuestInfo, MAX_QUEST_PER_TYPE_NUMBER>, MAX_QUEST_TYPE>	clQuestInfo;
#else
	//  ����Ʈ. 
	cltQuestInfo clQuestInfo[MAX_QUEST_TYPE][MAX_QUEST_PER_TYPE_NUMBER];
#endif

	// ����Ʈ ������ ������ ���� �޾Ҵ�.
	bool bQuestInfoChangedSwitch;

	HashStringInt*		pclHashTable;

	NTextManager*		m_pQuestText;

	cltQuestManager();
	~cltQuestManager();

	// ����Ʈ�� �߰��Ѵ�. 
	void Add(SI32 type, SI32 unique, cltQuestInitConditionInfo* pclinitcond, cltQuestClearConditionInfo* pclclearcond, cltQuestRewardInfo* pclreward, 
		TCHAR* titletext, TCHAR* pimagefilename);

	// ����Ʈ�� ��Ʈ�� ������ ��ġ�ϴ� ����ũ�� ã�´�.
	SI32 GetQuestUniqueFromBit(SI32 questtype, SI32 minbit);

	// �ؽ�Ʈ�� ȭ�鿡 �����ش�. 
	void ShowText(HWND hDlg, bool forceswitch);

	// ����Ʈ�� ����ũ�� ���ܿ� ���� ������ ��縦 ���� �ִ� �����̸��� ���´�.
	bool  GetText(SI32 questunique, SI32 queststep, TCHAR *filename);

	// questunique�� ������ ������ ����Ʈ ������ ã�´�. 
	cltQuestInfo* GetQuestInfo(SI32 questunique);

	// �������� ����Ʈ�� Ȯ���Ѵ�. 
	void GetCurrentQuestInfo();

	// ����Ʈ�� ����ũ�� �ٰŷ� �ش� ��Ʈ�� ã�´�.
	SI32 GetBitFromUnique(SI32 questtype, SI32 questunique);
	
	// ��Ʈ�� �ٰŷ� ����ũ�� ã�´�. 
	SI32 GetUniqueFromBit(SI32 questtype, SI32 bit);

	
	BOOL CALLBACK QuestDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	
	// ����Ʈ�� ����ũ�� ��Ʈ�� �����Ѵ�.
	bool ConnectBitWithUnique();

	// ����Ʈ �ؽ�Ʈ�� �ҷ��´�. 
	bool LoadQuestText();

	// ����Ʈ �ؽ�Ʈ�� �ҷ��´�. 
	bool LoadQuestText(SI32 questtype, SI32 questunique);

	// ����Ʈ ������ ���� �ؽ�Ʈ�� �����Ѵ�.
	bool GetCurStatusText(cltCharClient* pclchar,  SI16 questtype, cltQuestInfoCommon* pclquestinfo, TCHAR* ptext, SI16 txtSize);

	// ���� ��Ȳ�� ���� ���� �ؽ�Ʈ�� ���´�.
	bool GetCurStatusText(SI32 id, SI32 questtype, SI32 questunique, TCHAR* ptext, SI16 txtSize);
/*
	// ���� �������� ����Ʈ ������ ȭ�鿡 �����ش�. 
	void ShowQuestClearInfo(SI32 id, HWND hDlg, SI32 dlgitem, SI32 sumdlgitem);

	// ���� �������� ����Ʈ ������ ȭ�鿡 �����ش�. 
	void ShowCurrentQuestInfo(SI32 id, HWND hDlg, SI32 dlgitem, SI32 dlgitem2);
*/
	// NPCKind�� �ο��ϴ� ����Ʈ�� Ÿ���� ���´�. 
	SI32 GetQuestTypeFromNPCKind(SI32 kind);

	// ����Ʈ Ÿ���� �ٰŷ� �� ����Ʈ�� �ο��ϴ� NPC��  kind�� ã�´�. 
	SI32 GetNPCKindFromQuestType(SI32 questtype);
	
	// NPCKind�� ����Ʈ�� ���� ������ ����.
	bool GetQuestExplain(SI32 kind, TCHAR* ptext, SI16 txtSize);
	
	// ����Ʈ Ÿ�� �̸��� ���Ѵ�. 
	TCHAR* GetQuestTypeName(SI32 questtype);
	
	// ����Ʈ�� ���� ��Ȳ�� �ؽ�Ʈ�� ���´�. 
	bool GetQuestProgressText(SI16 questtype, cltPQuestInfo* pclquestinfo, TCHAR* ptext, SI16 txtSize);


	// Ư�� Ÿ�� ����Ʈ�� ������ ���Ѵ�. 
	SI32 GetQuestNum(SI32 type);

	// ��ι� ����Ʈ�� ���� ���߱� �ܾ��߿��� �����ϰ� �� ���ڸ� ã�´�. 
	SI32 GetRandWordAssembly();

	// NInterface������ �߰��Ǵ� �Լ���
	void InitDialog(SI32 kind);

	void ShowText(bool forceswitch);
	TCHAR* GetText(SI32 questunique, SI32 queststep);
	bool GetSprPath(SI32 questunique,SI32 queststep,SI32 * font , TCHAR * fullpathname);

	void Action();

#ifdef _SAFE_MEMORY
	NSafeTArray< NSafeTArray<cltQuestTxtInfo, MAX_QUEST_PER_TYPE_NUMBER>, MAX_QUEST_TYPE>		clQuestTxtInfo;
#else
	cltQuestTxtInfo clQuestTxtInfo[MAX_QUEST_TYPE][MAX_QUEST_PER_TYPE_NUMBER];
#endif

	// ���� ���콺���
	void DrawClickMouse(LPDIRECTDRAWSURFACE7 lpSurface, SI32 unique);
	// ���� �����
	void DrawDirectionArrow( SI32 drawX, SI32 drawY );
	void DrawDirectionArrow( SI32 drawX, SI32 drawY, SI32 direction );

	bool GetTutorialMakeQuestItem(SI16 QuestUnique, SI32 ItemUnique, OUT cltMaterialInfo * clMaterialItem);
	void ShowSelectItemDlg( cltQuestRewardInfo* pclinfo, SI16 questtype, SI16 questunique);

	// 
	SI16 ConvertQuestTypeTextToNum( TCHAR* pszQuestType );

	// [����] �ð����� ����Ʈ�� �ð� ���� ǥ�� : �����ð� ���� �Լ�
	void UpdateRemainTime( SI32 siTimeReduce = 0 );	
};




#endif
