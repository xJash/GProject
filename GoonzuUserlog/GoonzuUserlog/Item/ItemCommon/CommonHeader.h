//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

// ������ Ŭ���̾�Ʈ ��� �������� ����ϴ� Define

#ifndef _COMMONHEADER_H
#define _COMMONHEADER_H


#include "commonutil.h"

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>


#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>
#include <assert.h>
#include <io.h>
#include <wingdi.h>
#include <math.h>
#include <commctrl.h>

#include <directives.h>

#define NAME  "����"
#define TITLE "����"


//-------------------------------------------------------------
// ���� ���� 
//-------------------------------------------------------------
const SI32 ConstServiceArea_Korea	= 	1;
const SI32 ConstServiceArea_China	=	2;
const SI32 ConstServiceArea_Taiwan	=	3;
const SI32 ConstServiceArea_Japan	=	4;
const SI32 ConstServiceArea_English	=	5;


#define NOOBJECT								0
#define OBJECT1									1


#define NEW_SELECTED_DELAY						6

#define MAX_WAIT_STEP_NUMBER					16	// ĳ���Ͱ� ���� �� �ִ� �ִ� ���� ��� �������� �� 
#define MAX_WAIT_TYPE							2   // ���� ���ϴ� �ִϸ��̼��� �ִ� �� .

#define MAX_MOVE_STEP_NUMBER					10	// ĳ���Ͱ� ���� �� �ִ� �ִ� �̵� ��� �������� �� 
#define MAX_DYING_STEP_NUMBER					16	// ĳ���Ͱ� ���� �� �ִ� �ִ� ��� ��� �������� �� 
#define  MAX_ATTACK_STEP_NUMBER					16	// ĳ���Ͱ� ���� �� �ִ� �ִ� ���� ��� �������� �� 

#define GAMECOLOR_RED						69
#define GAMECOLOR_YELLOW					70
#define GAMECOLOR_GREEN						68

//============================================================
// DIALOG BOX COLOR ���� 
//============================================================
#define COLOR_DIALOG_YELLOW					RGB(248, 255, 199)
#define COLOR_DIALOG_GREEN					RGB(136, 251, 148)
#define COLOR_DIALOG_RED					RGB(226, 114, 150)
#define COLOR_DIALOG_LIGHTRED				RGB(255, 167, 179)
#define COLOR_DIALOG_BLUE					RGB(15,  167, 240)
#define COLOR_DIALOG_BLACK					RGB( 0, 0, 0 )
#define COLOR_DIALOG_WHITE					RGB(255, 255, 255)
#define COLOR_DIALOG_LIGHTBLUE				RGB(143, 202, 233)
#define COLOR_DIALOG_WHITEBLUE				RGB(238, 238, 255)
#define COLOR_DIALOG_GRAY					RGB(224,213,213)
#define COLOR_DIALOG_DLG_BLUE				RGB(205, 205, 205)
#define COLOR_DIALOG_STATIC_BLUE			RGB(226, 222, 207)
//============================================================

#define DOUBLE_CLICK_DELAY						300

// ���� ���� 						
#define SOUTH              						1
#define SW                 						2
#define WEST               						4
#define NW										8
#define NORTH               					16
#define NE                  					32
#define EAST                					64
#define SE                  					128 
						
#define SSW										1000						
#define WWS 									1001						
#define WWN 									1002						
#define NNW 									1003						
#define NNE 									1004						
#define EEN 									1005						
#define EES 									1006
#define SSE 									1007


//----------------------------------------------------
//    ĳ����  �Ӽ� 
//----------------------------------------------------
#define ATB_MOVE							0x00000001			// �����̴� ĳ���� �Ӽ� 
#define ATB_HERO							0x00000002			// ������ĳ���� �Ӽ�.  
#define ATB_ATTACK							0x00000004			// ���� �Ӽ�
#define ATB_SHIP							0x00000008  		// ����
#define ATB_WEAKENEMYNOATTACK				0x00000010  		// ���� ���� �������� �ʴ� �Ӽ�. 
#define ATB_FISH							0x00000020  		// ���� ����. 
#define ATB_NOJJIM							0x00000040		// ����� �ʴ� ĳ����. 
#define ATB_MINRANGE						0x00000080		// ������ �Ұ� 
#define ATB_HORSE							0x00000100		// ����. 
#define ATB_SYSTEMNPC						0x00000200		// SystemNPC
#define ATB_SELFBOMB						0x00000400		// �������
#define ATB_WAITSELFBOMB					0x00000800		// ������ �������
#define ATB_NONPCLIST						0x00001000		// NPC����Ʈ�� ���Ե��� �ʴ´�. 
#define ATB_COWORK							0x00002000		// �ֺ� ������ ���������Ѵ�. 
#define ATB_MONSTER							0x00004000		// ����
#define ATB_GOD								0x00008000		// ��Ȳ���� �ɼ��ִ� ĳ���� 
#define ATB_DEFAULTGOD						0x00010000		// ��Ȳ���� ���� �⺻�� �Ǵ� ĳ���� 
#define ATB_DEFAULTCASTLE					0x00020000		// ������ ���� �⺻�� �Ǵ� ĳ���� 
#define ATB_DAILYQUEST						0x00040000		// DailyQuest�� ������ ĳ����
#define ATB_WARMONSTER						0x00080000		// �����߿��� ������ ���� - ���� ǥ��â�� ǥ�� �Ұ�
#define ATB_EVENTXBOX						0x00100000		// EVENT �Ӽ��� ���� �ִ�.
#define ATB_CLONE							0x00200000		// �нż��� ������ �Ѵ�.
#define ATB_DEFAULTSUMMON					0x00400000		// ��ȯ���� �ɼ� �ִ��� �����Ѵ�..
#define ATB_HIREABLE						0x00800000		// �������� ��밡���ϴ�. 
#define ATB_BOSS							0x01000000		// ������ �����̴�.
#define ATB_FARM							0x02000000		// ������Ⱑ �����ϴ�. 
#define ATB_DAMAGELIMIT						0x04000000		// �ǰݽ� �������� �Ѱ谡 �ִ�. 
#define ATB_MINE							0x08000000		// ä���� �����ϴ�.



//------------------------------------------------------------------------------------------------
// 
//------------------------------------------------------------------------------------------------
#define TRANSPARENT_MODE_NORMAL					1
#define TRANSPARENT_MODE_OLDTRANS				2
#define TRANSPARENT_MODE_HALFTRANS				3
#define TRANSPARENT_MODE_SCREEN					4
#define TRANSPARENT_MODE_MULTIPLY				5
#define TRANSPARENT_MODE_ADD					6
#define	TRANSPARENT_MODE_ALPHA					7

//------------------------------------------------------------------------------------------------
// �ź� �Ӽ� 
//------------------------------------------------------------------------------------------------
#define IDENTITY_CASTLE							1			// �ź��� ����   ����
#define IDENTITY_VILLAGEGOD						2			// �ź��� ��Ȳ�� ����
#define IDENTITY_VILLAGEGOD_SUMMON				3			// �ź��� ������ ��Ȳ���� ��ȯ�� ��ȯ�� ����
#define IDENTITY_PERSON_SUMMON					4			// �ź��� ������ ��ȯ�� ��ȯ�� ���� 
#define IDENTITY_VILLAGEHUNT					5			// �ź��� ������� ��ɿ� ���� 

//------------------------------------------------------------------------------------------------
// ��� �Ӽ�		
//------------------------------------------------------------------------------------------------
#define DEFENCEATB_HUMAN    					1			// �Ϲ� ���� 
#define DEFENCEATB_SWORD    					2			// �Ϲ� ���� 
#define DEFENCEATB_ARMOUR   					3			// ���� 
#define DEFENCEATB_HORSE    					4			// �⺴ 
#define DEFENCEATB_STONE    					6			// �ǹ� 



//----------------------------------------
// ĳ���� ��� 
//----------------------------------------
#define MAX_ORDER_NUMBER				20

#define ORDER_WAIT    					1
#define ORDER_STOP    					2 
#define ORDER_FORCESTOP    				3					// Ŭ���̾�Ʈ�� ���޵Ǿ������� ���� STOP	 
#define ORDER_MOVE    					4					// �ܼ��̵� 
#define ORDER_ATTACK  					5					// �ܼ� ���� 
#define ORDER_ATTACK_SUMMON				6					// ��ȯ���� ����.  
#define ORDER_DIE     					7
#define ORDER_DEAD    					8
#define ORDER_MAGIC						9
#define ORDER_REVIVE					10
#define ORDER_STRAIGHTMOVE				11					// �����̵�. 
#define ORDER_FISH						12					// ���� �ϱ�. 
#define ORDER_FARM						13					// �������. 
#define ORDER_MAGIC_SUMMON				14					// ��ȯ���� ���� ����
#define ORDER_MINE						15					// ä��



#define MAX_HORSE_NAME			12	// �� �̸��� ����. 
#define MAX_SUMMON_NAME			12	// ��ȯ�� �̸��� ����. 

#define MAX_HORSE_TYPE			8	// �� ǰ�� �ִ��

#define MAX_RENT_FEE			1000000
#define MAX_RENT_PERIOD			10

// ���� �̸� ���� 
#define FILE_NAME_SIZE							128

#define NORMAL_TEXT_COLOR	RGB(250, 250, 250)
#define BLANK_TEXT_COLOR	RGB(10, 10, 10)


#define MAX_ORDER_QUE							50

#define MAX_CHAR_NUMBER							18500			// ���ӿ� ������ �� �ִ� �ִ��� ĳ���� ���� 
#define MAX_PERSON_NUMBER						3000
#define MAX_SHIP_NUMBER							500
#define MAX_NPC_NUMBER							9500	// �ǹ��� ĳ���� ������.
#define MAX_INSTANCE_NPC_NUMBER					5500		// �ν��Ͻ� ���� NPC

#define MAX_KIND_NUMBER							220		// �� ĳ������ ���� ���� 
#define MAX_KIND_PER_PLAYER						10		// ���ΰ� ĳ������ ���� ����(���� +1��! 10���� NPC)

#define MAX_BULLET_NUMBER						1000
#define MAX_SMOKE_NUMBER						1500

#define MAX_PLAYER_NAME							20	// ����ڰ� ���� �� �ִ� �ִ� �̸� ũ��.

#define MAX_SHIP_NAME							30	// ����ڰ� ���� �� �ִ� �ִ� �̸� ũ��.

#define MAX_CHAR_PER_USER						3	// �� ������ ���� �� �ִ� ĳ������ ��. 

#define MAX_VILLAGE_NUMBER						100	// ���ӿ� ������ ��� ���°� ?
#define VILLAGE_NONE							0	// 0 ������( ���� ������ �ǹ� ) 	

#define MAX_RESIDENTS_PER_VILLAGE				300 // �� ������ �ִ� �ֹμ�

#define MAX_INVEST_NUMBER						15	// ����ؾ� �ϴ� ������ ������ ����Ʈ 10 	

#define	MAX_CONSTRUCTION_NUM					9	// �� ������ ���� �� �ִ� �ǹ��� �ִ��. 

#define MAX_HEAD_CHAT_TEXT_SIZE					128

#define MAX_CHILDINFO_NUMBER					10	// ���� ������ �ѹ��� ���� �� �ִ� �ִ� ��. 

#define WAR_REWARD_VILLAGE_NUMBER				20	// �ֱ� ����� 20�� �������� �����ؼ� �����Ѵ�. 

#define	MAX_CHAT_DATA_LENGTH					100	// �ѱ� 50 ��

#define MAX_PERSONAL_SHOP_TEXT_SIZE				100	// �ѱ� 30�� ���λ��� banner 

#define MAX_BLOCKREASON_SIZE					200 // ����� ���� �� ������ �ؽ�Ʈ ������. 

#define MAX_SCROLL_SUMMON_PER_KIND				2			// �������� ��ȯ���� �ٸ� ���ִ� �ִ� ������

#define MAX_HORSE_LIFE							3000



//-----------------------------------
// �� ����
//-----------------------------------
#define MAX_SHIP_PER_PERSON				3				// �� ����� ������ �ִ� ���� �ִ��
#define MAX_SHIP_SUMMON_NUMBER			5				// �迡 �� ��ȯ���� �ִ��
// �踦 ����� �� �ִ� ���� ����
#define MIN_USING_SHIP_LEVEL			50

enum { ShipPos_Start = -2, ShipPos_HouseUnit, ShipPos_Field, ShipPos_Port };
enum { SHIP_JOB_START, SHIP_JOB_PASSENGER, SHIP_JOB_GUNNER, SHIP_JOB_OWNER, SHIP_JOB_END };
enum { SHIP_SUMMON_JOB_START, SHIP_SUMMON_JOB_BOATMAN, SHIP_SUMMON_JOB_GUNNER, SHIP_SUMMON_JOB_CANNON, SHIP_SUMMON_JOB_END };


//-----------------------------------
// ������ġ ���� 
//-----------------------------------
#define PRISON_MAPINDEX	0
#define PRISON_X		379
#define PRISON_Y		503


// PC�ΰ� ?
#define IsPC(x)			(x > 0 && x < MAX_PERSON_NUMBER)
// Ship�ΰ� ?
#define IsShip(x)		(x >= MAX_PERSON_NUMBER && x < (MAX_PERSON_NUMBER + MAX_SHIP_NUMBER))
// InstanceNPC�ΰ�?
#define IsInstanceNPC(x)	(x >= (MAX_PERSON_NUMBER + MAX_SHIP_NUMBER) && x < (MAX_PERSON_NUMBER + MAX_SHIP_NUMBER+MAX_INSTANCE_NPC_NUMBER))
// NPC�ΰ� ?
#define IsNPC(x)		(x >= (MAX_PERSON_NUMBER + MAX_SHIP_NUMBER+MAX_INSTANCE_NPC_NUMBER) && x < MAX_CHAR_NUMBER )

#define NETWORK_SERVER		1
#define NETWORK_CLIENT		2

enum eGameMode{
	GAMEMODE_SERVER	= 1	,
	GAMEMODE_CLIENT		,
	GAMEMODE_MAPEDIT
};

#define BY_PLAYER     0		
#define BY_COMPUTER   1

#define MIN_ITEM_PRICE	20			// ������ ������ �ּҰ�(�� ���Ϸδ� �������� �ʴ´�.) 

#define MAX_MATERIAL_NUMBER	10		// ������ ��� ���� �ִ밪

#define FATHER_LEVEL	20
#define INIT_LEVEL		10			// �ʱ�ȭ �Ǵ� ���� 

//--------------------------
// ��ü ��� 
//--------------------------
#define ORG_1			1			// ��ȭ�� 
#define ORG_2			2			// ��ȯ�� 
#define ORG_3			3			// ȣ��� 
#define ORG_4			4			// �Ű�� 


#define MAX_LEVEL_FOR_BEGINNERMAP	10		// �ʺ��� ����� ������ ���� �ִ� ���� 

//----------------------------------------
// ������ Ÿ�� 
//----------------------------------------
#define MAX_RANKTYPE_NUMBER	20

#define RANKTYPE_CITYHALL				1		// �����
#define RANKTYPE_BANK					2		// ������� 
#define RANKTYPE_STOCK					3		// ������� 
#define RANKTYPE_MARKET					4		// �������
#define RANKTYPE_HOUSE					5		// �������
#define RANKTYPE_HUNT					6		// ��������� 
#define RANKTYPE_POSTOFFICE				7		// ��ü�����
#define RANKTYPE_PORT					8		// �������
#define RANKTYPE_HORSEMARKET			9		// �纹�����
#define RANKTYPE_REALESTATEMARKET		10		// �Ű����
#define RANKTYPE_SUMMONMARKET			11		// �忹�����
#define RANKTYPE_SHIPMARKET				12		// ���Ի���� 
#define RANKTYPE_LAND					13		// �������  
#define RANKTYPE_FEAST					14		// ���ڽ����
#define RANKTYPE_SUMMONHEROMARKET		15		// �񺯻����
#define RANKTYPE_MINE					16		// �������
#define RANKTYPE_GUILD					17		// ������ 	

// ������ �ִ� ����. 
#define MAX_MAP_NUMBER					400

#define MAX_DUR_FOR_TUNE	200		// ������ �ʿ��� �ִ� ������(�� ��ġ �����̾�� �Ѵ�.) 

//------------------------------------
// ���� ���� ���� ���� 
//------------------------------------
#define VILLAGE_PROFIT_RATE_FOR_MERCHANT	5	// ������ �ŷ� ����� �� %�� ���� �������� �����ϴ°�. 
#define VILLAGE_PROFIT_RATE_FOR_DAILYQUEST	5	// �𺴰� ����Ʈ  ����� �� %�� ���� �������� �����ϴ°�. 
#define VILLAGE_PROFIT_RATE_FOR_NPCREPAIR	5	// �念�� ���� ����� �� %�� ���� �������� �����ϴ°�. 
#define VILLAGE_PROFIT_FOR_WENNYOLDMAN		5000
#define VILLAGE_PROFIT_FOR_FANPRIEST		2000
#define VILLAGE_PROFIT_FOR_PERSONALSHOP     5000
#define VILLAGE_PROFIT_FOR_INVESTMENT		5000 // ���ڻ�㰡(���� �輱��)

#define MAX_EVENT_NUMBER					6		// �̺�Ʈ�� ����. 
#define MIN_LEVEL_FOR_HORSE					20		// ���� �����ϱ� ���� �ּ� ���� 

//--------------------------------
// ������ ���� 
//--------------------------------
#define SEASON_SPRING		0
#define SEASON_AUTUMN		1
#define SEASON_WINTER		2


//------------------------------
// ������ Ÿ�� 
//------------------------------
#define VILLAGETYPE_SPRING_NORMAL		1
#define VILLAGETYPE_SPRING_PORT			2
#define VILLAGETYPE_AUTUMN_NORMAL		3
#define VILLAGETYPE_AUTUMN_PORT			4
#define VILLAGETYPE_WINTER_NORMAL		5
#define VILLAGETYPE_WINTER_PORT			6

//-----------------------------------------------------------------------------
// Data x�� ���� ����ִ��� ������ �˻� ������ true(TRUE) , ������ false(FALSE)
//-----------------------------------------------------------------------------
#define DATA_TO_BOOL(x)				(x!=0)?(x>0):false?true:false
#define DATA_TO_TYPE_BOOL(x)		(x!=0)?(x>0):FALSE?TRUE:FALSE

//-----------------------------------------------------------------------------
// ������ ����� ������

enum
{
	GONGZO_SKILL_START = 1 ,
	GONGZO_SKILL_SWORD = GONGZO_SKILL_START ,
	GONGZO_SKILL_SPEAR ,
	GONGZO_SKILL_STAFF ,
	GONGZO_SKILL_AXE ,
	GONGZO_SKILL_BOW ,
	GONGZO_SKILL_GUN ,
	GONGZO_SKILL_LAST = GONGZO_SKILL_GUN ,
	GONGZO_SKILL_TOTAL,
};

struct GongzoMember
{
	SI16	siPriceValue[GONGZO_SKILL_TOTAL];
	SI16	siSkillValue[GONGZO_SKILL_TOTAL];
};

#define MAX_INVESTMENT_ITEM_NUMBER	100 // ���ڻ�㰡�� ������ ���� ���� �� ����

struct InvestmentLines
{
	SI32	siInvestmentItemUnique; // �������� ����ũ
	SI32	siInvestmentItemPrice; // �������� ����

	SI32	siMarginalProfit; // ����

	SI32	siMaterialItemPrice[MAX_MATERIAL_NUMBER];
};

//-------------------------------------------
// �� 
//-------------------------------------------
#define MAX_MONEY	99999999	// ���� �ִ� ����. 
class cltMoney{
public:
	SI64 itMoney;

	void Init()
	{
		itMoney = 0;
	}

	void Set(cltMoney* pclmoney)
	{
		if(pclmoney == NULL)return;

		Set(pclmoney->itMoney);

	}

	void Set(SI64 money)
	{
		itMoney = money;
	}
	
	cltMoney Minus(cltMoney* pclmoney)
	{
		cltMoney clmoney;
		clmoney.Set(this);
		clmoney.Decrease(pclmoney);

		return clmoney;
	}

	cltMoney Plus(cltMoney* pclmoney)
	{
		cltMoney clmoney;
		clmoney.Set(this);
		clmoney.Increase(pclmoney);

		return clmoney;
	}

	void Increase(cltMoney* pclmoney)
	{
		if(pclmoney == NULL)return ;

		itMoney += pclmoney->itMoney;
		if(itMoney > 2000000000)itMoney = 2000000000;
	}

	void Decrease(cltMoney* pclmoney)
	{
		if(pclmoney == NULL)return ;

		if(itMoney >=  pclmoney->itMoney)
		{
			itMoney -= pclmoney->itMoney;
		}
		else
		{
			itMoney = 0;
		}
	}

	// itMoney���� pclmoney�� �����ϴ� ����. 
	SI32 GetPercent(cltMoney* pclmoney)
	{
		if(itMoney)
		{
			SI64 percent = (pclmoney->itMoney * 100) / itMoney;
			return (SI32)percent;
		}

		return 0;
	}

	void Clear()
	{
		itMoney = 0;
	}

	bool Empty()
	{
		if(itMoney == 0)return true;

		return false;
	}

	bool Large(cltMoney* pclmoney)
	{
		if(itMoney > pclmoney->itMoney)return true;
		return false;
	}

	bool Small(cltMoney* pclmoney)
	{
		if(itMoney < pclmoney->itMoney)return true;
		return false;
	}

};


//-------------------------------------------
// ��ġ ���� 
//-------------------------------------------
class cltPos{
public:
	SI32 siX;
	SI32 siY;

	cltPos()
	{
		siX = 0; siY = 0;
	}
	cltPos(SI32 x, SI32 y)
	{
		siX = x; siY = y;
	}

	void Init()
	{
		siX = 0;
		siY = 0;
	}

	void Set(const cltPos* pclpos)
	{
		siX = pclpos->siX;
		siY	= pclpos->siY;
	}
	void Set(SI32 six, SI32 siy)
	{
		siX	= six;
		siY	= siy;
	}
};

// ���� ����. 
class cltWarpInfo{
public:
	UI32 uiWarpSwitch:		1;
	UI32 uiMapIndex:		9;
	UI32 uiForceSwitch:		1;		// ���ֺ��ڸ� �˻� ���� �ٷ� ���ڸ��� ���� 
	UI32 uiTicketUseSwitch:	1;		// ���� �������� ����� ����. (Ư�� ȿ���� ������� �Ѵ�) 
	UI32 uiX:				10;
	UI32 uiY:				10; 

	SI16	siGateX, siGateY;	// ����Ʈ ��ġ. (����Ʈ�� ���� �������� -1) 

public:

	cltWarpInfo()
	{
		Init();
	}

	cltWarpInfo(UI32 warpswitch, UI32 mapindex, UI32 forceswitch, UI32 ticketuse, UI32 x, UI32 y, SI16 gatex, SI16 gatey)
	{
		uiWarpSwitch		= warpswitch;
		uiMapIndex			= mapindex;
		uiForceSwitch		= forceswitch;
		uiTicketUseSwitch	=ticketuse;
		uiX					= x;
		uiY					= y;
		siGateX				= gatex;
		siGateY				= gatey;
	}

	void Set(const cltWarpInfo* pclinfo)
	{
		uiWarpSwitch		= pclinfo->uiWarpSwitch;
		uiMapIndex			= pclinfo->uiMapIndex;
		uiForceSwitch		= pclinfo->uiForceSwitch;
		uiTicketUseSwitch	= pclinfo->uiTicketUseSwitch;
		uiX					= pclinfo->uiX;
		uiY					= pclinfo->uiY;
		siGateX				= pclinfo->siGateX;
		siGateY				= pclinfo->siGateY;
	}

	void Init()
	{
		uiWarpSwitch		= 0;
		uiMapIndex			= 0;
		uiX					= 0;
		uiY					= 0;
		uiForceSwitch		= 0;
		uiTicketUseSwitch	= 0;
		siGateX				= -1;
		siGateY				= -1;
	}

	UI32 GetWarpSwitch()const{return uiWarpSwitch;}
	void SetWarpSwitch(UI32 mode){uiWarpSwitch = mode;}

	UI32 GetMapIndex()const{return uiMapIndex;}
	UI32 GetX()const{return uiX;}
	UI32 GetY()const{return uiY;}

	SI16 GetGateX()const{return siGateX;}
	SI16 GetGateY()const{return siGateY;}
};


//---------------------------------
// ������ Person���� 
//---------------------------------
class cltSimplePerson{
public:
	SI32 siPersonID;
	char szName[MAX_PLAYER_NAME];


	cltSimplePerson()
	{
		Init();
	}

	cltSimplePerson(SI32 personid, const char* pname)
	{
		Set(personid, pname);
	}

	void Set(const cltSimplePerson* pinfo)
	{
		siPersonID	= pinfo->GetPersonID();
		MStrCpy(szName, pinfo->GetName(), MAX_PLAYER_NAME );
	}

	void Set(SI32 personid, const char* pname)
	{
		siPersonID = personid;
		MStrCpy(szName, pname, MAX_PLAYER_NAME );
	}

	void Init()
	{
		siPersonID = 0;
		MStrCpy(szName, "NOPERSONNAME", MAX_PLAYER_NAME );
	}

	SI32 GetPersonID()const{return siPersonID;}
	void SetPersonID(SI32 id){ siPersonID = id;}

	const char* GetName()const{return szName;}
	void SetName(const char* pname)
	{
		MStrCpy(szName, pname, MAX_PLAYER_NAME );
	}

};



//-------------------------------
// ĳ������ ��ġ ���� 
//-------------------------------
class cltCharPos{
public:
	SI16 siMapIndex;	// ĳ������ ��ġ.(���� �ε���)  
	SI16 siX;			// ĳ������ ��ġ (���� ��ǥ ) 
	SI16 siY;			// ĳ������ ��ġ (���� ��ǥ ) 
	SI16 siReserved;

public:
	cltCharPos()
	{
		Init();
	}

	cltCharPos(SI32 mapindex, SI32 x, SI32 y)
	{
		siMapIndex	= mapindex;
		siX			= x;
		siY			= y;
	}

	void Set(const cltCharPos* pclpos)
	{
		memcpy(this, pclpos, sizeof(cltCharPos));
	}

	void Init()
	{
		siMapIndex	= 0;
		siX			= 0;
		siY			= 0;
	}

	void SetMapIndex(SI32 index){siMapIndex = index;}
	SI32 GetMapIndex()const{return siMapIndex;}

	void SetX(SI32 x){siX = x;}
	SI32 GetX()const{return siX;}

	void SetY(SI32 y){siY = y;}
	SI32 GetY()const{return siY;}
};


//----------------------------------
// ���� ������ ������ �ź� ���� 
//----------------------------------
class cltSimpleRank{
public:
	SI08 siType;			// ������ Ÿ��. 
	SI08 siVillageUnique;	// ������ ���õ� ������ ��� �ش� ����. 

public:

	cltSimpleRank()
	{
		Init();
	}
	
	cltSimpleRank(SI32 ranktype, SI32 villageunique)
	{
		siType			= ranktype;
		siVillageUnique = villageunique;
	}
	cltSimpleRank(cltSimpleRank* pclrank)
	{
		memcpy(this, pclrank, sizeof(cltSimpleRank));
	}


	void Init()
	{
		siType			= 0;
		siVillageUnique = 0;
	}

	void Set(SI08 ranktype, SI08 villageunique)
	{
		siType			= ranktype;
		siVillageUnique = villageunique;
	}

	void Set(const cltSimpleRank* pinfo)
	{
		memcpy(this, pinfo, sizeof(cltSimpleRank));
	}

	void SetRankType(SI08 type){siType = type;}
	SI32 GetRankType()const{return siType;}

	void SetVillageUnique(SI08 villageunique){siVillageUnique = villageunique;}
	SI32 GetVillageUnique()const{return siVillageUnique;}

	BOOL IsSame(cltSimpleRank* pclrank)const
	{
		if(pclrank == NULL)return FALSE;

		if(siType == pclrank->GetRankType() && siVillageUnique == pclrank->GetVillageUnique())
			return TRUE;

		return FALSE;
	}
};

//----------------------------------
// ���� ������ ������ ��� �ź� ���� 
//----------------------------------
class cltSimpleGuildRank{
public:
	SI08 siType;			// ������ Ÿ��. 
	SI08 siVillageUnique;	// ��� �Ҽ� ����
	SI08 siGuildUnitIndex;	// ��� �ε��� 

public:

	cltSimpleGuildRank()
	{
		Init();
	}
	
	cltSimpleGuildRank( SI32 ranktype, SI32 villageunique, SI32 guildunitindex )
	{
		siType			 = ranktype;
		siVillageUnique  = villageunique;
		siGuildUnitIndex = guildunitindex;
	}

	cltSimpleGuildRank( cltSimpleGuildRank* pclrank )
	{
		siType		  	 = pclrank->siType;
		siVillageUnique  = pclrank->siVillageUnique;
		siGuildUnitIndex = pclrank->siGuildUnitIndex;
	}

	void Init()
	{
		siType			= 0;
		siVillageUnique = 0;
		siGuildUnitIndex = 0;
	}

	void Set( SI08 ranktype, SI08 villageunique, SI08 guildunitindex )
	{
		siType			 = ranktype;
		siVillageUnique  = villageunique;
		siGuildUnitIndex = guildunitindex; 
	}

	void Set(const cltSimpleGuildRank* pclrank)
	{
		siType		  	 = pclrank->siType;
		siVillageUnique  = pclrank->siVillageUnique;
		siGuildUnitIndex = pclrank->siGuildUnitIndex;
	}

	void SetRankType(SI08 type){siType = type;}
	SI32 GetRankType()const{return siType;}

	void SetVillageUnique(SI08 villageunique){siVillageUnique = villageunique;}
	SI32 GetVillageUnique()const{return siVillageUnique;}

	void SetGuildUnitIndex(SI08 guildunitindex){siGuildUnitIndex = guildunitindex;}
	SI32 GetGuildUnitIndex()const{return siGuildUnitIndex;}

	BOOL IsSame(cltSimpleGuildRank* pclrank)const
	{
		if(pclrank == NULL)return FALSE;

		if(siType == pclrank->siType && 
		   siVillageUnique == pclrank->siVillageUnique &&
		   siGuildUnitIndex == pclrank->siGuildUnitIndex )
			return TRUE;

		return FALSE;
	}
};


//----------------------------------
// ���¹�ȣ Ŭ���� 
//---------------------------------
class cltAccountNum{
public:
	SI32 siVillageUnique;	// ������ �ִ� ������ ����ũ. 
	SI32 siAccountNum;		// ���¹�ȣ. 


	cltAccountNum()
	{
		Init();
	}

	cltAccountNum(SI32 villageunique, SI32 accountnum)
	{
		siVillageUnique = villageunique;
		siAccountNum	= accountnum;

	}


	void Init()
	{
		siVillageUnique		= 0;
		siAccountNum		= 0;	
	}

	void Set(const cltAccountNum* pclaccountnum)
	{
		memcpy(this, pclaccountnum, sizeof(cltAccountNum));
	}

	// �� ���� ���°� ��ȿ�Ѱ�?
	BOOL IsValid()
	{
		if(siAccountNum)return TRUE;
		return FALSE;
	}

	bool IsSame(cltAccountNum* pclnum)
	{
		if(siVillageUnique != pclnum->siVillageUnique)return false;

		if(siAccountNum != pclnum->siAccountNum)return false;

		return true;
	}

	void SetVillageUnique(SI32 villageunique){siVillageUnique = villageunique; }
	SI32 GetVillageUnique()const{return siVillageUnique;}

	void SetAccountNum(SI32 num){siAccountNum = num;}
	SI32 GetAccountNum()const{return siAccountNum;}

};

//-------------------------------------
// �ź��� ���� ����� ����. 
// (�����, �������, ������� ���...
//-------------------------------------
class cltRankPerson{
public:
	SI32 siVillageUnique;
	cltSimplePerson	clPerson;

	cltRankPerson()
	{
		siVillageUnique = 0;
	};

	cltRankPerson(SI32 sivillageunique, const cltSimplePerson* pinfo)
	{
		siVillageUnique = sivillageunique;
		clPerson.Set(pinfo);
	}

	void Set(const cltRankPerson* pclinfo)
	{
		memcpy(this, pclinfo, sizeof(cltRankPerson));
	}
	void Set(SI32 sivillageunique, const cltSimplePerson* pinfo)
	{
		siVillageUnique = sivillageunique;
		clPerson.Set(pinfo);
	}


	void Init(SI32 villageunique)
	{
		siVillageUnique = villageunique;
		clPerson.Init();

	}

	SI32 GetPersonID()const{return clPerson.GetPersonID();}
	SI32 GetVillageUnique()const{return siVillageUnique;}
};


//------------------------------------------
// ������ Ŭ���̾�Ʈ�� ������ ���ϰ� Ŭ���� 
//------------------------------------------
class cltServerResponseValue{
public:
	SI16 siReceiver;
	SI16 siReturnValue;
	SI16 siPara1;
	SI16 siPara2;

	cltServerResponseValue()
	{
		siReceiver		= 0;
		siReturnValue	= 0;
		siPara1			= 0;
		siPara2			= 0;
	}

	cltServerResponseValue(SI16 receiver, SI16 value, SI16 sipara1, SI16 sipara2)
	{
		siReceiver		= receiver;
		siReturnValue	= value;
		siPara1			= sipara1;
		siPara2			= sipara2;
	}
};

#define MIN_FEE	100
#define MAX_FEE	100000
#define MAX_FEE_RATE	100		// 10%

//-----------------------------------------
// ������ ���� 
//-----------------------------------------
class cltFee{
private:
	SI32 siFeeRate;		// Ÿ�� ����� ������ (�۹�) 
	SI32 siMinFee;		// ���� ������. 
	SI32 siMaxFee;		// �ִ� ������. 	
public:

	void Set(cltFee* pclfee)
	{
		memcpy(this, pclfee, sizeof(cltFee));

		if( siFeeRate < 10 ) siFeeRate = 10;
	}

	// �ŷ� �ݾ��� �ٰŷ� �����Ḧ ����Ѵ�. 
	SI32 CalcFee(SI32 money)
	{
		//return max(siMinFee, min(siMaxFee, money * siFeeRate / 1000)) ;

		if( siFeeRate < 10 ) siFeeRate = 10;

		SI32 ret = (int)( money * ( siFeeRate / 1000. ) );
		
		if( ret < 0 ) return 0;
		return ret;
	}

	BOOL SetFeeRate(SI32 rate)
	{
		if( rate < 10 ) { siFeeRate = 10; return FALSE; }
		if( rate > 200 ) { siFeeRate = 200; return FALSE; }
		siFeeRate = rate;
		return TRUE;
	}
	SI32 GetFeeRate()const{return max(10, siFeeRate);}

	BOOL SetMinFee(SI32 fee)
	{
		if(fee < 0 || fee > MAX_FEE)return FALSE;

		siMinFee = fee;
		return TRUE;
	}
	SI32 GetMinFee()const{return siMinFee;}


	BOOL SetMaxFee(SI32 fee)
	{
		if(fee < 0 || fee > MAX_FEE || fee < siMinFee)return FALSE;

		siMaxFee = fee;
		return TRUE;
	}
	SI32 GetMaxFee()const{return siMaxFee;}


	// ���� �����ᰡ �������� Ȯ���Ѵ�. 
	BOOL IsValid()
	{
		if(siFeeRate < 10 || siFeeRate > MAX_FEE_RATE)return FALSE;
		return TRUE;
	}


};

//-------------------------------------
// �α��ο�û ���� 
//-------------------------------------
class cltLogInInfo{
public:
	SI32	siAuthKey;
	char	szID[MAX_PLAYER_NAME];			// ���̵��� ������. 
	char	szPassword[MAX_PLAYER_NAME];	// ��ȣ�� ������. 
	UI08	uiGameMode;						// ���� Ŭ���̾�Ʈ ���� ��� : 0 => ������ â + ������ �������̽����, 
											// 1 => ������ + ���������̽� ���, 2 => ��üȭ�� + ���������̽� ���

	cltLogInInfo(SI32	authkey, char* id, char* password, UI08 gamemode)
	{
		siAuthKey	= authkey;
		MStrCpy(szID,	id,	MAX_PLAYER_NAME );
		MStrCpy(szPassword, password,	MAX_PLAYER_NAME );
		uiGameMode = gamemode;
	}
};


//-------------------------------
// ĳ���Ϳ��� �־����� ��� 
//-------------------------------
class cltOrderDataInfo{
public:
	SI08 siOrder;             // �����ؾ� �� ��� �ڵ� 
	SI08 siHostMode;          // ����� ���� ��ü (�÷��̾� �Ǵ� ��ǻ�� )

	SI32 siPara1;					// ��ɿ� ���� ���� �Ķ��Ÿ 
	SI16 siPara2;				// ��ɿ� ���� ���� �Ķ��Ÿ 
	SI16 siPara3;				// ��ɿ� ���� ���� �Ķ��Ÿ 

	cltOrderDataInfo()
	{
		Init();
	}

	cltOrderDataInfo(SI08 order, SI08 hostmode, SI32 para1, SI16 para2, SI16 para3)
	{
		Make(order, hostmode, para1, para2, para3);
	}

	cltOrderDataInfo(cltOrderDataInfo* pclinfo)
	{
		Set(pclinfo);
	}

	void Init()
	{
		siOrder		= ORDER_WAIT;
		siHostMode	= 0;
		siPara1		= 0;
		siPara2		= 0;
		siPara3		= 0;
	}

	void Make(SI08 order, SI08 hostmode, SI32 para1, SI16 para2, SI16 para3)
	{
		siOrder		= order;
		siHostMode	= hostmode;

		siPara1		= para1;
		siPara2		= para2;
		siPara3		= para3;

	}

	void Set(cltOrderDataInfo* pclorder)
	{
		siOrder		=	pclorder->siOrder;
		siHostMode	=	pclorder->siHostMode;
		siPara1		=	pclorder->siPara1;
		siPara2		=	pclorder->siPara2;
		siPara3		=	pclorder->siPara3;
	}

};

// ����� ��ü 
// ��ǻ�Ͱ� ������ �����ϴ� ����� ������ 
class cltOrderData {
public:
    cltOrderDataInfo ODI;

	SI32 CharUnique;					 // ����� �����ؾ� �� ĳ������ CharUnique

	cltOrderData(){ZeroMemory(this, sizeof(cltOrderData));};

	void Make(SI32 order, SI32 charunique, SI32 para1, SI16 para2, SI16 para3, char hostmode)
	{
		ODI.Make(order, hostmode, para1, para2, para3);

		CharUnique		 = charunique;
	}
	void Make(SI32 charunique, cltOrderDataInfo* pclinfo)
	{
		CharUnique = charunique;
		ODI.Set(pclinfo);
	}
	
};

class cltShapeEquipInfoUnit{
public:
	UI32	uiUnique:	16;
	UI32	uiRare:		3;
	UI32	uiReserved:	13;

	cltShapeEquipInfoUnit()
	{
		Init();
	}
	cltShapeEquipInfoUnit(UI32 unique, UI32 rare)
	{
		uiUnique	= unique;
		uiRare		= rare;
		uiReserved	= 0;

	}
	void Init()
	{
		uiUnique	= 0;
		uiRare		= 0;
		uiReserved	= 0;
	}
	void Set(cltShapeEquipInfoUnit* pclinfo)
	{
		uiUnique	= pclinfo->uiUnique;
		uiRare		= pclinfo->uiRare;
		uiReserved	= pclinfo->uiReserved;
	}

};
// �ܺ� ���ǰ ����.
class cltShapeEquipInfo{
public:
	cltShapeEquipInfoUnit clArmour;
	cltShapeEquipInfoUnit clHelmet;
	cltShapeEquipInfoUnit clMantle;
	cltShapeEquipInfoUnit clWeapon;

	UI32	uiSwordScroll:	1;
	UI32	uiSpearScroll:	1;
	UI32	uiAxeScroll:	1;
	UI32	uiGunScroll:	1;
	UI32	uiBowScroll:	1;
	UI32	uiStaffScroll:	1;
	UI32	uiCannonScroll:	1;

	SI08	siSwordScrollNum;
	SI08	siSpearScrollNum;
	SI08	siAxeScrollNum;
	SI08	siGunScrollNum;
	SI08	siBowScrollNum;
	SI08	siStaffScrollNum;
	
	cltShapeEquipInfo()
	{
		Init();
	}

	cltShapeEquipInfo(cltShapeEquipInfoUnit* pclArmour, cltShapeEquipInfoUnit* pclHelmet, cltShapeEquipInfoUnit* pclMantle, cltShapeEquipInfoUnit* pclWeapon,
		bool bsword, bool bspear, bool baxe, bool bgun, bool bbow, bool bstaff, bool bcannon,
		SI08 SwordScrollNum, SI08 SpearScrollNum, SI08 AxeScrollNum,
		SI08 GunScrollNum, SI08 BowScrollNum, SI08 StaffScrollNum)
	{
		clArmour.Set(pclArmour);
		clHelmet.Set(pclHelmet);
		clMantle.Set(pclMantle);
		clWeapon.Set(pclWeapon);

		uiSwordScroll	= bsword;
		uiSpearScroll	= bspear;
		uiAxeScroll		= baxe;	
		uiGunScroll		= bgun;		
		uiBowScroll		= bbow;		
		uiStaffScroll	= bstaff;
		uiCannonScroll	= bcannon;

		siSwordScrollNum = SwordScrollNum;
		siSpearScrollNum = SpearScrollNum;
		siAxeScrollNum = AxeScrollNum;
		siGunScrollNum = GunScrollNum;
		siBowScrollNum = BowScrollNum;
		siStaffScrollNum = StaffScrollNum;
	}

	void Init()
	{
		clArmour.Init();
		clHelmet.Init();
		clMantle.Init();
		clWeapon.Init();

		uiSwordScroll	= 0;
		uiSpearScroll	= 0;
		uiAxeScroll		= 0;	
		uiGunScroll		= 0;		
		uiBowScroll		= 0;		
		uiStaffScroll	= 0;
		uiCannonScroll	= 0;

		siSwordScrollNum = 0;
		siSpearScrollNum = 0;
		siAxeScrollNum = 0;
		siGunScrollNum = 0;
		siBowScrollNum = 0;
		siStaffScrollNum = 0;
	}

	void Set(cltShapeEquipInfo* pclinfo)
	{
		clArmour.Set(&pclinfo->clArmour);
		clHelmet.Set(&pclinfo->clHelmet);
		clMantle.Set(&pclinfo->clMantle);
		clWeapon.Set(&pclinfo->clWeapon);

		uiSwordScroll	= pclinfo->uiSwordScroll;
		uiSpearScroll	= pclinfo->uiSpearScroll;
		uiAxeScroll		= pclinfo->uiAxeScroll;	
		uiGunScroll		= pclinfo->uiGunScroll;		
		uiBowScroll		= pclinfo->uiBowScroll;		
		uiStaffScroll	= pclinfo->uiStaffScroll;
		uiCannonScroll	= pclinfo->uiCannonScroll;

		siSwordScrollNum  = pclinfo->siSwordScrollNum;
		siSpearScrollNum  = pclinfo->siSpearScrollNum;
		siAxeScrollNum	  = pclinfo->siAxeScrollNum;
		siGunScrollNum    = pclinfo->siGunScrollNum;
		siBowScrollNum    = pclinfo->siBowScrollNum;
		siStaffScrollNum  = pclinfo->siStaffScrollNum;
	}

};

//
#define CHANGETYPE_POISON			1
#define CHANGETYPE_ICE				2
#define CHANGETYPE_DRAIN			3
#define CHANGETYPE_HEAL				4
#define CHANGETYPE_NOFIRSTATTACK	5	// ���� ���� ȿ��. 
#define CHANGETYPE_NOICEATTACK		6	// ���� ���� ȿ��. 
#define CHANGETYPE_CURSEATTACK		7	// 
#define CHANGETYPE_CURSECRITICAL	8
#define CHANGETYPE_CURSEDEFENSE		9	// 
#define CHANGETYPE_CURSEMOVESPEED	10
#define CHANGETYPE_ANGEL			11	// ��ȣõ�� ���� ����. 
#define CHANGETYPE_AUTOFOOD			12	// �ڵ� ������ ���� ���� ����. 
#define CHANGETYPE_TOPSKILLUNIQUE	13	// �ְ������� ��� 
#define CHANGETYPE_MAGICFIRE		14	// ����ġ�� ���� ������ ��
#define CHANGETYPE_FROZEN			15	// ������ ������ �� ����

//----------------------------------------
// ĳ���͵��� ���� �������� ���� ����
//-----------------------------------------
class cltCharChangeStatusInfo{
public:
	SI32	siChangeType;
	bool	bChangeSwitch;
	SI32	siChageAmount1;
	SI32	siChageAmount2;
	SI32	siChageAmount3;

	cltCharChangeStatusInfo ()
	{
		siChangeType	= 0;
		bChangeSwitch	= false;
		siChageAmount1	= 0;
		siChageAmount2	= 0;
		siChageAmount3	= 0;
	};

	cltCharChangeStatusInfo (SI32 changetype, bool bswitch, SI32 amount1 = 0, SI32 amount2 =0, SI32 amount3 = 0 )
	{
		siChangeType	= changetype;
		bChangeSwitch	= bswitch;
		siChageAmount1	= amount1;
		siChageAmount2  = amount2;
		siChageAmount3  = amount3;
	};
	void Set(cltCharChangeStatusInfo *pclInfo)
	{
		siChangeType	= pclInfo->siChangeType;
		bChangeSwitch	= pclInfo->bChangeSwitch;
		siChageAmount1	= pclInfo->siChageAmount1;
		siChageAmount2  = pclInfo->siChageAmount2;
		siChageAmount3  = pclInfo->siChageAmount3;

	};
};

//----------------------------------------
// ĳ���͵��� �ΰ��������� ���� ����
//-----------------------------------------
class cltCharAddStatusInfo{
public:
	SI16			siReserved[2];

/*	SI08			siIdentity;
	SI16			siHome;							// ��Ȳ���� ��� �ڽ��� �����ϴ� ������ Unique ��
	SI16			siCapa;							// ��Ȳ���� �������� 

	SI32			siChildCharUnique;				// ��ȯ���� ���� �ִٸ� ��ȯ���� Unique
	SI32			siParentCharUnique;				// �ڽ��� ��ȯ���̶�� �θ��� Unique
	SI32			siParentPersonID;				// �ڽ��� ��ȯ���̶�� �θ��� PersonID : Ȯ���ϰ� ���ϱ� ���ؼ���
	SI16			siSummonIndex;					// �ڽ��� ��ȯ����� ��ȯ�� Index	
*/

	cltCharAddStatusInfo ()
	{
/*		siIdentity			= 0;
		siHome				= 0;
		siCapa				= 0;
		siChildCharUnique	= 0;
		siParentCharUnique	= 0;
		siParentPersonID	= 0;
		siSummonIndex		= 0;
		*/
	};

/*	cltCharAddStatusInfo (SI08 identity, SI16 home, SI16 capa, SI32 childunique, SI32 parentunique, SI32 parentperson, SI16 summonindex)
	{
		siIdentity			= identity;
		siHome				= home;
		siCapa				= capa;
		siChildCharUnique	= childunique;
		siParentCharUnique	= parentunique;
		siParentPersonID	= parentperson;
		siSummonIndex		= summonindex;
	};
*/
	void Init()
	{
/*		siIdentity			= 0;
		siHome				= 0;
		siCapa				= 0;
		siChildCharUnique	= 0;
		siParentCharUnique	= 0;
		siParentPersonID	= 0;
		siSummonIndex		= 0;
		*/
	};

	void Set(cltCharAddStatusInfo *pclInfo)
	{
/*		siIdentity			= pclInfo->siIdentity;
		siHome				= pclInfo->siHome;
		siCapa				= pclInfo->siCapa;
		siChildCharUnique	= pclInfo->siChildCharUnique;	
		siParentCharUnique	= pclInfo->siParentCharUnique;
		siParentPersonID	= pclInfo->siParentPersonID;	
		siSummonIndex		= pclInfo->siSummonIndex;
		*/
	}
};

//------------------------------------
// Event ĳ���� ���� ����. 
//------------------------------------
class cltEventCharInfo{
public:
	UI32 bEvent1Switch:		1;
	UI32 bEvent2Switch:		1;
	UI32 bEvent3Switch:		1;
	UI32 bEvent4Switch:		1;
	UI32 bEvent5Switch:		1;

	UI32 bOXQuizSwitch:		1;		// OX���� ���� ����. 

	cltEventCharInfo()
	{
		Init();
	}

	void Init()
	{
		bEvent1Switch	= false;
		bEvent2Switch	= false;
		bEvent3Switch	= false;
		bEvent4Switch	= false;
		bEvent5Switch	= false;

		bOXQuizSwitch	= false;
	}

	void Set(cltEventCharInfo* pclinfo)
	{
		bEvent1Switch	= pclinfo->bEvent1Switch;
		bEvent2Switch	= pclinfo->bEvent2Switch;
		bEvent3Switch	= pclinfo->bEvent3Switch;
		bEvent4Switch	= pclinfo->bEvent4Switch;
		bEvent5Switch	= pclinfo->bEvent5Switch;

		bOXQuizSwitch	= pclinfo->bOXQuizSwitch;
	}
};
//------------------------------------
// Battlezone ĳ���� ���� 
//------------------------------------
#define BATTLEZONE_READY_NONE		0
#define BATTLEZONE_READY_A			1
#define BATTLEZONE_READY_B			2
#define BATTLEZONE_READY_ALL		3
#define BATTLEZONE_READY_GAMESTART	4

#define BATTLEZONE_SIDE_NONE		0
#define BATTLEZONE_SIDE_A			1
#define BATTLEZONE_SIDE_B			2
#define BATTLEZONE_SIDE_A_OBSERVER	3
#define BATTLEZONE_SIDE_B_OBSERVER	4
#define BATTLEZONE_SIDE_A_APPLIER	5
#define BATTLEZONE_SIDE_B_APPLIER	6

class cltBattleZoneCharInfo
{
public: 
	UI32 siReady	:	3;
	UI32 bLeader	:	1;
	UI32 uiSide		:	3;
	UI32 uiMapIndex :  10;	
	UI32 uiSession  :   7;	

	cltBattleZoneCharInfo()
	{
		Init();
	}
	void Init()
	{
		siReady			= BATTLEZONE_READY_NONE;
		bLeader			= false;
		uiSide			= 0;
		uiMapIndex		= 0;
		uiSession		= 0;
	}
	void Set(cltBattleZoneCharInfo* pclinfo)
	{
		siReady			= pclinfo->siReady;
		bLeader			= pclinfo->bLeader;
		uiSide			= pclinfo->uiSide;
		uiMapIndex		= pclinfo->uiMapIndex;
		uiSession		= pclinfo->uiSession;
	}	
};

//----------------------------------------
// ĳ������ ���� Status ���� 
//-----------------------------------------
#define ENEMYTYPE_ALLPC							1	// ��� ����ڿ� ������. 
#define ENEMYTYPE_ALLNPC						2	// ��� NPC�� ������ 
#define ENEMYTYPE_VILLAGE						4	// �������� ������ ������. 
#define ENEMYTYPE_ONEVILLAGE					8	// Ư�� �� �������� ������ (para1�� Ư�� ������ ����ũ ����) 
#define ENEMYTYPE_BATTLEZONE					16	// ��Ʋ�� ���� ���� (para1�� ��Ʋ�������� �� ���� ) 

class cltEnemyTypeInfo{
public:
	SI16	siEnemyType;
	SI16	siPara1;

	cltEnemyTypeInfo()
	{
		Init();
	}
	void Init()
	{
		siEnemyType = 0;
		siPara1		= 0;
	}
	void Set(cltEnemyTypeInfo* pclinfo)
	{
		siEnemyType = pclinfo->siEnemyType;
		siPara1		= pclinfo->siPara1;
	}
	void Set(SI16 type, SI16 para1)
	{
		siEnemyType = type;
		siPara1		= para1;
	}
	
	bool IsType(SI32 type)
	{
		if(siEnemyType & type)return true;

		return false;
	}


};

#define INNERSTATUS_POISON						1
#define INNERSTATUS_ICE							2
#define INNERSTATUS_CURSEATTACK					4
#define INNERSTATUS_CURSECRITICAL				8
#define INNERSTATUS_CLONE						16
#define INNERSTATUS_PRISON						32
#define INNERSTATUS_CURSEDEFENSE				64
#define INNERSTATUS_CURSEMOVESPEED				128
#define INNERSTATUS_MAGICFIRE					256 // ����ġ ������ ���ؼ� �� ����
#define INNERSTATUS_FROZEN						512 // ������ ���� ������ �¾Ƽ� ������

class cltInnerStatusInfo{	
public:
	SI32	siStatus;
	cltEnemyTypeInfo		clEnemyType;		// ���� ���� ����. 
	cltEventCharInfo		clEventInfo;		// ĳ������ �̺�Ʈ ���� ����. 
	cltBattleZoneCharInfo	clBZInfo;

	SI32	siRideShipID;						// ��� ĳ���� ������ �ڱⰡ �¼��� ���� ShipID
	SI32	siSelfShipID;						// �� ĳ���� ������ �ڱ� �ڽ��� ShipID

	SI16	siShipCharUnique;					// ���� CharUnique
	SI16	siShipOwnerCharUnique;				// �� �������� CharUnique
	
	SI16	siTopSkillUnique;					// �ְ� ������ ����� ����ũ 

	cltInnerStatusInfo()
	{
		ZeroMemory(this, sizeof(cltInnerStatusInfo));
	};

	cltInnerStatusInfo(SI32 status,	cltEnemyTypeInfo* pclenemytype, 
		cltEventCharInfo* pclevent, cltBattleZoneCharInfo* pclbz, 
		SI32 RideShipID, SI32 SelfShipID, SI16 ShipCharUnique, SI16 ShipOwnerCharUnique, SI16 topskillunique )
	{
		siStatus		= status;
		clEnemyType.Set(pclenemytype);
		clEventInfo.Set(pclevent);
		clBZInfo.Set(pclbz);		

		siRideShipID	= RideShipID;
		siSelfShipID	= SelfShipID;
		siShipCharUnique= ShipCharUnique;
		siShipOwnerCharUnique = ShipOwnerCharUnique;
		siTopSkillUnique	= topskillunique;
	}
	
	void Set(cltInnerStatusInfo* pclinfo)
	{
		siStatus		= pclinfo->siStatus;
		clEnemyType.Set(&pclinfo->clEnemyType);
		clEventInfo.Set(&pclinfo->clEventInfo);
		clBZInfo.Set(&pclinfo->clBZInfo);		
		siRideShipID			= pclinfo->siRideShipID;
		siSelfShipID			= pclinfo->siSelfShipID;
		siShipCharUnique		= pclinfo->siShipCharUnique;
		siShipOwnerCharUnique	= pclinfo->siShipOwnerCharUnique;
		siTopSkillUnique		= pclinfo->siTopSkillUnique;
	}

	void Init()
	{
		siStatus				= 0;
		clEnemyType.Init();
		clEventInfo.Init();
		clBZInfo.Init();		
		siRideShipID			= 0;
		siSelfShipID			= 0;
		siShipCharUnique		= 0;
		siShipOwnerCharUnique	= 0;
		siTopSkillUnique		= 0;
	}
	
	bool IsStatus(SI32 status)
	{
		if(siStatus & status)return true;

		return false;
	}

	void SetStatus(SI32 status)
	{
		siStatus |= status;
	}

	void DelStatus(SI32 status)
	{
		if(siStatus & status)
		{
			siStatus -= status;
		}
	}
};

//--------------------------------
// ĳ���� ���̵�Ƽ ���� 
//--------------------------------
class cltIdentityCommonInfo{
public:
	SI16	siPara1;
	SI16	siPara2;
	SI32	siPara3;
};

class cltIdentitySummonInfo{
public:
	SI16	siMySummonIndex;
	SI16	siParentCharUnique;
	SI32	siParentPersonID;
};

class cltIdentityVillageGodInfo{
public:
	SI16	siCapa;
};

class cltIdentityVillageHuntInfo{
public:
	SI16	siHome;
	SI16	siPara2;
};



class cltIdentity{
public:
	SI08	siIdentity;

	union
	{
		cltIdentityCommonInfo		clCommonInfo;
		cltIdentitySummonInfo		clSummonInfo;
		cltIdentityVillageGodInfo	clGodInfo;
		cltIdentityVillageHuntInfo	clHuntInfo;
	};

	cltIdentity()
	{
		Init();
	}
	cltIdentity(SI08 identity, SI16 para1, SI16 para2, SI32 para3)
	{
		siIdentity	= identity;
		clCommonInfo.siPara1		= para1;
		clCommonInfo.siPara2		= para2;
		clCommonInfo.siPara3		= para3;
	}
	void Init()
	{
		siIdentity	= 0;
		clCommonInfo.siPara1		= 0;
		clCommonInfo.siPara2		= 0;
		clCommonInfo.siPara3		= 0;
	}

	void Set(cltIdentity* pclinfo)
	{
		siIdentity	= pclinfo->siIdentity;
		clCommonInfo.siPara1		= pclinfo->clCommonInfo.siPara1;
		clCommonInfo.siPara2		= pclinfo->clCommonInfo.siPara2;
		clCommonInfo.siPara3		= pclinfo->clCommonInfo.siPara3;
	}

	// ��ȯ���� �����Ѵ�. 
	void MakeSummon(SI32 iddentity, SI32 index, SI32 parentcharid, SI32 parentpersonid)
	{
		siIdentity			= iddentity;

		clSummonInfo.siMySummonIndex		= index;
		clSummonInfo.siParentCharUnique	= parentcharid;
		clSummonInfo.siParentPersonID	= parentpersonid;
	}

	// ����, ��Ȳ��, ��ȯ�ż�ȯ���� �����Ѵ�.
	void MakeGod(SI32 iddentity, SI32 capa)
	{
		siIdentity			= iddentity;
		clGodInfo.siCapa	= capa;
	}

	// �Ұ��縮�� �����Ѵ�.
	void MakeHunt(SI32 iddentity, SI32 villageunique)
	{
		siIdentity			= iddentity;
		clHuntInfo.siHome	= villageunique;
	}

	
};

#define MAKECHARTYPE_NPC		0
#define MAKECHARTYPE_PC			1


//----------------------------------------
// ĳ���͸� ���鶧 ����ϴ� ����. 
//-----------------------------------------
class cltMakeCharInfoCommon{
public:
	UI32	uiType:					1;		// NPC���ΰ� ����� ���ΰ�. 
	UI32    uiMakeCharKind:			8;		// ����� ������ ĳ���� ����. 
	UI32    uiMakeCharUnique:		16;		// �� �޽����� ����� ��������� �� ĳ������ CharUnique
	UI32	uiLevel:				8;		// (0~255)
	UI32	uiLife:					20;		// ���� �� ĳ������ ü��. 
	UI32	uiX:					10;
	UI32	uiY:					10;
	UI32	uiMapIndex:				10;		// ���� �ε��� (0~2^10 = 1024)
	UI32	uiTotalMoveSpeed:		6;	
	SI08	siHomeVillageUnique;		// �ּ��� ������ ����ũ. 
	SI16	siJimCharUnique;			// �� ĳ���͸� ���� ĳ������ ����ũ. 
	cltOrderDataInfo	clOrder;		// ĳ���Ͱ� ������� �� ���ؾ� �� �ӹ�. 		
	cltIdentity			clIdentity;		// ���̵�Ƽ ����. 
	cltInnerStatusInfo	clInnerStatus;	// ĳ������ �߰����� (��, ����)

	cltMakeCharInfoCommon()
	{
		Init();
	}

	cltMakeCharInfoCommon(UI32 makekind, UI32 makecharunique, SI32 home, UI32 level, 
		UI32 life, UI32 x, UI32 y, UI32 mapindex, UI32 speed, SI16 jimcharunique, 
		cltOrderDataInfo* pclorder,
		cltIdentity* pclidentity, 
		cltInnerStatusInfo* pclinnerstatus)
	{
		if(IsPC(makecharunique))
		{
			uiType				= MAKECHARTYPE_PC;
		}
		else
		{
			uiType				= MAKECHARTYPE_NPC;
		}
		
		uiMakeCharKind		= makekind;
		uiMakeCharUnique	= makecharunique;
		siHomeVillageUnique	= home;
		uiLevel				= level;
		uiLife				= life;
		uiX					= x;
		uiY					= y;
		uiMapIndex			= mapindex;
		uiTotalMoveSpeed	= speed;
		siJimCharUnique		= jimcharunique;
		if(pclorder)
		{
			clOrder.Set(pclorder);
		}
		
		if(pclidentity)
		{
			clIdentity.Set(pclidentity);
		}
		
		if(pclinnerstatus)
		{
			clInnerStatus.Set(pclinnerstatus);
		}
	}

	void Init()
	{
		uiType				= 0;
		uiMakeCharKind		= 0;
		uiMakeCharUnique	= 0;
		siHomeVillageUnique	= 0;
		uiLevel				= 0;
		uiLife				= 0;
		uiX					= 0;
		uiY					= 0;
		uiMapIndex			= 0;
		uiTotalMoveSpeed	= 0;
		siJimCharUnique		= 0;

		clOrder.Init();
		
		clIdentity.Init();
		
		clInnerStatus.Init();
	}

	void Set(cltMakeCharInfoCommon* pclinfo)
	{
		uiType				= pclinfo->uiType;
		uiMakeCharKind		= pclinfo->uiMakeCharKind;
		uiMakeCharUnique	= pclinfo->uiMakeCharUnique;
		siHomeVillageUnique	= pclinfo->siHomeVillageUnique;
		uiLevel				= pclinfo->uiLevel;
		uiLife				= pclinfo->uiLife;
		uiX					= pclinfo->uiX;
		uiY					= pclinfo->uiY;
		uiMapIndex			= pclinfo->uiMapIndex;
		uiTotalMoveSpeed	= pclinfo->uiTotalMoveSpeed;
		siJimCharUnique		= pclinfo->siJimCharUnique;
		clOrder.Set(&pclinfo->clOrder);
		clIdentity.Set(&pclinfo->clIdentity);
		clInnerStatus.Set(&pclinfo->clInnerStatus);
	}
};

class cltMakeCharInfoUser{
public:

};


class cltMakeCharInfo : public cltMakeCharInfoCommon{
public:
	//--------------------------------
	// ����� ���� ���� 
	//--------------------------------
	UI32	uiChildCharUnique:		16;			// ������ ��ȯ���� ����ũ. 
	UI32	uiSummonIndex:			3;			// ���� ��ȯ���� �ε���. 
	UI32	uiHeadChatSwitch:		1;			// �Ӹ����� �ִ°� ?
	UI32	uiPersonalShopSwitch:	1;			// ���λ����� �ִ°�?
	UI32	uiNoFirstAttackSwitch:	1;			// ���� �� �����Ǿ� �ִ°�?
	UI32	uiNoIceAttackSwitch:	1;			// ICE �� �����Ǿ� �ִ°�?
	UI32	uiSex:					1;			// ����. 

	
	UI32	uiHorseUnique1:			8;		// ���� ����.
	UI32	uiSchoolUnique:			10;		// �б��� ����ũ. 
	UI32	uiRequestAddinfo:		1;		// �ź��� ���� �߰����� ��û ����
	UI32	uiTicketWarpSwitch:		1;		// �����̿���� ����� �����̵��ΰ�. 

	SI08	siHorseIndex;
	SI08	siGameMasterLevel;			// ��� ���� �ܰ�. 
	SI16	siMapUnique;				// ������ũ. 

	cltShapeEquipInfo clShapeEquip;
	
	cltSimpleRank		clRank;

	SI32				siAddStatusDate;
	SI32				siStatusTicketNum;

	bool				bPCRoom;		// pc�� �����ΰ�

	cltMakeCharInfo() : cltMakeCharInfoCommon()
	{
		Init();
	};


	cltMakeCharInfo(UI32 uikind, UI32 makecharunique, UI32 level, UI32 life, UI32 x, UI32 y, UI32 mapindex, 
		UI32 childcharunique, 
		UI32 summonindex, 
		UI32 bheadchatswitch, 
		UI32 bpersonalshopswitch, 
		UI32 bnofirstattackswitch,
		UI32 bnoiceattackswitch,
		UI32 bsex,
		cltShapeEquipInfo* pclequipinfo, 
		SI08 horseindex, UI32 totalmovespeed, 
		SI16 jimcharunique, 
		SI08 gamemasterlevel, 
		SI16 mapunique, 
		UI32 horseunique1, 
		UI32 homevillageunique, 
		UI32 schoolunique,
		cltSimpleRank* pclrank,SI32 addstatusdate,SI32 ticketnum, cltOrderDataInfo* pclorder, 
		cltIdentity* pclidentity,
		cltInnerStatusInfo *pclinnerstatus, UI32 requestaddinfo,
		UI32 ticketwarp,
		bool bpcroom ) 
		: cltMakeCharInfoCommon (uikind, makecharunique, homevillageunique, level, 
		life, x, y, mapindex, totalmovespeed, jimcharunique, 
		pclorder,
		pclidentity, 
		pclinnerstatus )
	{
		
		uiChildCharUnique		= childcharunique;
		uiSummonIndex			= summonindex;

		uiHeadChatSwitch		= bheadchatswitch;
		uiPersonalShopSwitch	= bpersonalshopswitch;
		
		uiNoFirstAttackSwitch	= bnofirstattackswitch;
		uiNoIceAttackSwitch		= bnoiceattackswitch;
		uiSex					= bsex;

		uiHorseUnique1		= horseunique1;
		uiSchoolUnique		= schoolunique;

		siHorseIndex		= horseindex;
		uiRequestAddinfo    = requestaddinfo;
		uiTicketWarpSwitch	= ticketwarp;


		siGameMasterLevel	= gamemasterlevel;
		siMapUnique			= mapunique;

		if(pclequipinfo)
		{
			clShapeEquip.Set(pclequipinfo);
		}

		if(pclrank)
		{
			clRank.Set(pclrank);
		}

		siAddStatusDate = addstatusdate ;
		siStatusTicketNum = ticketnum;

		bPCRoom = bpcroom;
	}

	void Init()
	{
		cltMakeCharInfoCommon::Init();
		
		uiChildCharUnique	= 0;
		uiSummonIndex	= 0;
		uiHeadChatSwitch	= 0;
		uiPersonalShopSwitch	= 0;
		uiNoFirstAttackSwitch	= 0;
		uiNoIceAttackSwitch	= 0;
		uiSex	= 0;
		
		
		uiHorseUnique1	= 0;
		uiSchoolUnique	= 0;
		uiRequestAddinfo	= 0;
		uiTicketWarpSwitch	= 0;
						
		siHorseIndex	= 0;
		siGameMasterLevel	= 0;
		siMapUnique		= 0;
		
		clShapeEquip.Init();
		
		clRank.Init();

		siAddStatusDate = 0 ;
		siStatusTicketNum = 0 ;
		
		bPCRoom = false;
	}


	void Set(cltMakeCharInfoCommon* pclinfo)
	{
		Init();
		cltMakeCharInfoCommon::Set(pclinfo);
	}
	
	void Set(cltMakeCharInfo* pclinfo)
	{
		cltMakeCharInfoCommon::Set(pclinfo);

		uiChildCharUnique	= pclinfo->uiChildCharUnique;
		uiSummonIndex		= pclinfo->uiSummonIndex;

		uiHeadChatSwitch	= pclinfo->uiHeadChatSwitch;
		uiPersonalShopSwitch= pclinfo->uiPersonalShopSwitch;

		uiNoFirstAttackSwitch	= pclinfo->uiNoFirstAttackSwitch;
		uiNoIceAttackSwitch		= pclinfo->uiNoIceAttackSwitch;
		uiSex					= pclinfo->uiSex;	

		uiHorseUnique1	 = pclinfo->uiHorseUnique1;
		uiSchoolUnique	= pclinfo->uiSchoolUnique;

		siHorseIndex		= pclinfo->siHorseIndex;
		uiRequestAddinfo	= pclinfo->uiRequestAddinfo;
		uiTicketWarpSwitch	= pclinfo->uiTicketWarpSwitch;

		siGameMasterLevel	= pclinfo->siGameMasterLevel;
		siMapUnique			= pclinfo->siMapUnique;

		clShapeEquip.Set(&pclinfo->clShapeEquip);
		
		clRank.Set(&pclinfo->clRank);

		siAddStatusDate = pclinfo->siAddStatusDate ;
		siStatusTicketNum = pclinfo->siStatusTicketNum ;

		bPCRoom = pclinfo->bPCRoom;
	}
};


class cltPFatherInfo{
public:
	cltSimplePerson	clFather;			// ���� ����. 
	char			szAccountID[MAX_PLAYER_NAME];
	SI08			siMyLevelForFather;	// ������ ������ ����� �� ���� 
	SI08			siFatherChangeNumber;	// ������ ������ Ƚ��. 

	cltPFatherInfo()
	{
		Init();
	}

	void Init()
	{
		clFather.Init();
		szAccountID[ 0 ] = NULL;
		siMyLevelForFather		= 0;
		siFatherChangeNumber	= 0;
	}

	void Set(cltPFatherInfo* pclinfo)
	{
		clFather.Set(&pclinfo->clFather);
		MStrCpy( szAccountID, pclinfo->szAccountID, MAX_PLAYER_NAME );
		siMyLevelForFather		= pclinfo->siMyLevelForFather;
		siFatherChangeNumber	= pclinfo->siFatherChangeNumber;
	}
};

//------------------------------------
// �ź�. 
//------------------------------------
#define GRANK_KING			1		// �� 
#define GRANK_MINISTER1		2		// �����Ǽ� 
#define GRANK_MINISTER2		3		// ȣ�� 
#define GRANK_MINISTER3		4		// ����
#define GRANK_MINISTER4		5		// ���� 
#define GRANK_MINISTER5		6		// ���� 
#define GRANK_MINISTER6		7		// ���� 

#define GRANK_MC_WOMAN		100		// ���� MC
#define GRANK_MC_MAN		101		// ���� MC

//-----------------------------------
// ���� �⺻��  �Ǵ� ĳ���� ����. 
//-----------------------------------
class cltPBasicInfo{
public:
	SI32		siIDNum;						// �� Person�� �Ҽӵ� IDNum
	char		szAccountID[MAX_PLAYER_NAME];	// �� Person�� �Ҽӵ� ������ ���̵�. 	
	UI08		uiIndex;		// ĳ���� ������ �� ��° ���Կ� ��ġ�ϴ°� ?
	UI08		uiSex;			// ����, (���� 1, ���� 0)
	UI08		uiKind;			// ĳ������ ����. 
	SI08		siHomeVillage;	// �ּ���. 
	UI08		uiGRank;		// �ź�. 
	UI08		uiAngelSwitch;	// ��ȣõ������ ����. 
	cltCharPos	clPos;	// ĳ������ ��ġ 
	SI32		siPlaySecond;	// �÷����� �� ���� �ð�(��) 
	cltPos		clLastMainMapPos;	// �߿������� ���� ��ġ. 
	SI16		siSchoolUnique;	// ��� �б��� ����ũ. 
	
	// ��� ���� ����. 
	SI32		siWealthRank;		// ������. 
	cltMoney	clTotalWealthMoney;	// �� ����. 
	SI32		siWealthCalcDay;	//	������ ����� ��. 

	cltSimplePerson	clPerson;	// �ڽ��� ����. 

	// ���� ���� ����.
	cltPFatherInfo clFatherInfo;

	// ��õ�� ���� ����
	cltSimplePerson clRecommenderInfo;	// ��õ�� ����
	
	SI16	siVoteKingSelectionIndex;	// ��ǥ�� �ĺ��� ��ȣ	
	
	// �⼮ ���� 
	bool	bTodayFirstAttendanceSwitch;	// ���� ù��° �⼮�ΰ�.	
	SI32	siAttendanceDays;				// ���� �⼮�ϼ�. 

	bool	bWennyOldManUpgrade;			// ȣǰ �� ���� �ִ���?

	bool	bNewAccount; // Ư���� ���Ŀ� ������ �����ΰ�?
	bool	bGameEvent; // ���� ����ǰ� �ִ� �̺�Ʈ�� �����ߴ°�?
	bool	bWinPrizeEvent; // ���� ����ǰ� �ִ� �̺�Ʈ�� ��÷�Ǿ��°�?

	bool	bUseNoLimitTicketWarp ; // ���ѿ��� �ϴ°�?
	SI32	siNoLimitTicketWarpDateVary ; // ���ѿ��� �Ⱓ

	bool	bPCRoom;	// PC�� �����ΰ�?
	bool	bQuestEvolve; // ����Ʈ ��ȭ�� ������ �ִ���?

public:

	cltPBasicInfo()
	{		
		siIDNum				= 0;
		uiIndex				= 0;
		uiSex				= 0;
		uiKind				= 0;
		siHomeVillage		= 0;
		uiGRank				= 0;
		uiAngelSwitch		= 0;
		siPlaySecond		= 0;
		clLastMainMapPos.Init();
		siSchoolUnique		= 0;
		clPerson.Init();
		clFatherInfo.Init();
		clRecommenderInfo.Init();
		siVoteKingSelectionIndex = 0;

		siWealthRank		= 0;
		clTotalWealthMoney.Clear();
		siWealthCalcDay		= 0;

		szAccountID[ 0 ] = NULL;

		bTodayFirstAttendanceSwitch	= false;
		siAttendanceDays			= 0;

		bWennyOldManUpgrade = false ;

		bNewAccount = false ;
		bGameEvent = false ;
		bWinPrizeEvent = false ;

		bUseNoLimitTicketWarp = false ;
		siNoLimitTicketWarpDateVary = 0 ;

		bPCRoom = false;
		bQuestEvolve = false ;
	}

	cltPBasicInfo(char* paccountid, SI32 idnum, UI08 index, UI08 sex, cltSimplePerson* pclperson, 
		UI08 kind, SI08 homevillage, cltCharPos* pclpos, SI32 playsecond, SI16 schoolunique, 
		cltPos* pclmainmappos, cltPFatherInfo* pclfather, cltSimplePerson* pclRecommenderInfo, 
		SI16 VoteKingSelectionIndex, SI32 wealthrank, cltMoney totalmoney, SI32 wealthday,
		bool attendanceswitch, SI32 attendanceday,bool wennyoldmanupgrade,bool newaccount,
		bool gameevent , bool winprizeevent,bool nolimitticketwarp , SI32 warpticketdatevary,
		bool bpcroom ,bool bquestevolve)
	{
		MStrCpy(szAccountID, paccountid, MAX_PLAYER_NAME );

		siIDNum			= idnum;
		uiIndex			= index;
		uiSex			= sex;

		uiKind			= kind;
		siHomeVillage	= homevillage;
		uiGRank			= 0;
		uiAngelSwitch	= 0;
		clPos.Set(pclpos);
		siPlaySecond	= playsecond;
		siSchoolUnique	= schoolunique;
		clLastMainMapPos.Set(pclmainmappos);

		clPerson.Set(pclperson);

		clFatherInfo.Set(pclfather);
		clRecommenderInfo.Set(pclRecommenderInfo);
		siVoteKingSelectionIndex = VoteKingSelectionIndex;

		siWealthRank		= wealthrank; 
		clTotalWealthMoney.Set(&totalmoney);
		siWealthCalcDay		= wealthday;

		bTodayFirstAttendanceSwitch	= attendanceswitch;
		siAttendanceDays			= attendanceday;

		bWennyOldManUpgrade = wennyoldmanupgrade ;

		bNewAccount = newaccount ;
		bGameEvent = gameevent ;
		bWinPrizeEvent = winprizeevent ;

		bUseNoLimitTicketWarp = nolimitticketwarp ;
		siNoLimitTicketWarpDateVary = warpticketdatevary ;

		bPCRoom = bpcroom;
		bQuestEvolve = bquestevolve ;
	}
	void Set(cltPBasicInfo* pclinfo)
	{
		MStrCpy( szAccountID, pclinfo->szAccountID, MAX_PLAYER_NAME );

		siIDNum			= pclinfo->siIDNum;
		uiIndex			= pclinfo->GetIndex();
		uiSex			= pclinfo->uiSex;
		uiKind			= pclinfo->GetKind();
		siHomeVillage	= pclinfo->siHomeVillage;
		uiGRank			= pclinfo->uiGRank;
		uiAngelSwitch	= pclinfo->uiAngelSwitch;
		clPos.Set(pclinfo->GetPos());
		siPlaySecond	= pclinfo->siPlaySecond;
		siSchoolUnique	= pclinfo->siSchoolUnique;
		clLastMainMapPos.Set(&pclinfo->clLastMainMapPos);

		clPerson.Set(&pclinfo->clPerson);
		clFatherInfo.Set(&pclinfo->clFatherInfo);
		clRecommenderInfo.Set(&pclinfo->clRecommenderInfo);
		siVoteKingSelectionIndex = pclinfo->siVoteKingSelectionIndex;

		siWealthRank		= pclinfo->siWealthRank; 
		clTotalWealthMoney.Set(&pclinfo->clTotalWealthMoney);
		siWealthCalcDay		= pclinfo->siWealthCalcDay;

		bTodayFirstAttendanceSwitch	= pclinfo->bTodayFirstAttendanceSwitch;
		siAttendanceDays			= pclinfo->siAttendanceDays;

		bWennyOldManUpgrade			= pclinfo->bWennyOldManUpgrade ;

		bNewAccount					= pclinfo->bNewAccount ;
		bGameEvent					= pclinfo->bGameEvent ;
		bWinPrizeEvent				= pclinfo->bWinPrizeEvent ;

		bUseNoLimitTicketWarp = pclinfo->bUseNoLimitTicketWarp ;
		siNoLimitTicketWarpDateVary = pclinfo->siNoLimitTicketWarpDateVary ;

		bPCRoom						= pclinfo->bPCRoom;
		bQuestEvolve				= pclinfo->bQuestEvolve ;
	}


	~cltPBasicInfo(){};

	void Init()
	{
		szAccountID[ 0 ] = NULL;
		siIDNum		= 0;
		uiIndex		= 0;
		uiSex		= 0;
		uiKind		= 0;
		siHomeVillage	= 0;
		siPlaySecond	= 0;
		siSchoolUnique	= 0;
		uiGRank			= 0;
		uiAngelSwitch	= 0;

		clPos.Init();
		clLastMainMapPos.Init();

		clPerson.Init();
		clFatherInfo.Init();
		clRecommenderInfo.Init();
		siVoteKingSelectionIndex = 0;
		
		siWealthRank		= 0;
		clTotalWealthMoney.Clear();
		siWealthCalcDay		= 0;

		bTodayFirstAttendanceSwitch	= false;
		siAttendanceDays			= 0;

		bWennyOldManUpgrade = false ;

		bNewAccount = false ;
		bGameEvent = false ;
		bWinPrizeEvent = false ;

		bUseNoLimitTicketWarp = false ;
		siNoLimitTicketWarpDateVary = 0 ;

		bPCRoom = false;
		bQuestEvolve = false ;
	}

	void SetIndex(SI32 index){uiIndex = index;}
	SI32 GetIndex()const{return uiIndex;}

	void SetKind(SI32 kind){uiKind = kind;}
	SI32 GetKind()const{return uiKind;}

	const cltCharPos* GetPos()const{return &clPos;}

	void SetMapIndex(SI32 index){clPos.SetMapIndex(index);}
	SI32 GetMapIndex()const{return clPos.GetMapIndex();}

	void SetX(SI32 x){clPos.SetX(x);}
	SI32 GetX()const{return clPos.GetX();}

	void SetY(SI32 y){clPos.SetY(y);}
	SI32 GetY()const{return clPos.GetY();}

	void SetName(const char* pname)
	{
		MStrCpy( clPerson.szName, pname, MAX_PLAYER_NAME );
	}
	const char*GetName()const{return clPerson.szName;}

	bool IsPCRoom() { return bPCRoom; }

	bool IsQuestEvolve() { return bQuestEvolve ; }
	void SetQuestEvolve(bool questevolve)
	{
		bQuestEvolve = questevolve ;
	}

};

//-------------------------------
// �⺻�� �Ǵ� �ɷ�ġ. 
//-------------------------------
class cltBasicAbility{
public:
	// �⺻ �ɷ�ġ.(����ڰ� ���ʽ��� ������ �ø��� �ɷ�ġ.) 
	SI32	siStr;				// �ٷ�	
	SI32	siDex;				// ���߷�
	SI32	siVit;				// ����� 
	SI32	siMag;				// ���� 
	SI32	siHnd;				// ������. 
	
	cltBasicAbility()
	{
		Init();		
	}

	~cltBasicAbility(){};

	void Init()
	{
		ZeroMemory(this, sizeof(cltBasicAbility));
	}

	void Set(SI32 str, SI32 dex, SI32 vit, SI32 mag, SI32 hnd)
	{
		siStr	= str;
		siDex	= dex;
		siVit	= vit;
		siMag	= mag;
		siHnd	= hnd;
	}
	void Set(cltBasicAbility* pclinfo)
	{
		Set(pclinfo->siStr, pclinfo->siDex, pclinfo->siVit, pclinfo->siMag, pclinfo->siHnd);
	}

	SI32 GetStr()const{return siStr;}
	void SetStr(SI32 dat){	siStr = dat;}
	SI32 IncreaseStr(SI32 amount){ siStr += amount; return siStr;}
	SI32 DecreaseStr(SI32 amount){ siStr -= amount; return siStr;}
	SI32 GetStrDamage(){return siStr / 5;}

	SI32 GetDex()const{	return siDex;}
	void SetDex(SI32 dat){	siDex = dat;}
	SI32 IncreaseDex(SI32 amount){ siDex += amount; return siDex;}
	SI32 DecreaseDex(SI32 amount){ siDex -= amount; return siDex;}

	SI32 GetVit()const{return siVit;	}
	void SetVit(SI32 dat){siVit = dat;}
	SI32 IncreaseVit(SI32 amount){ siVit += amount; return siVit;}
	SI32 DecreaseVit(SI32 amount){ siVit -= amount; return siVit;}
	
	SI32 GetMag()const{return siMag;	}
	void SetMag(SI32 dat){siMag = dat;}
	SI32 IncreaseMag(SI32 amount){ siMag += amount; return siMag;}
	SI32 DecreaseMag(SI32 amount){ siMag -= amount; return siMag;}

	SI32 GetHnd()const{return siHnd;	}
	void SetHnd(SI32 dat){siHnd = dat;}
	SI32 IncreaseHnd(SI32 amount){ siHnd += amount; return siHnd;}
	SI32 DecreaseHnd(SI32 amount){ siHnd -= amount; return siHnd;}

};

//-----------------------------------------
// ���� ������ ����
//-----------------------------------------
class cltInvestInfo{
public:
	cltSimplePerson	clPerson;
	SI32			siStockNum;		// ���� �ֽļ�. 

public:
	cltInvestInfo()
	{
		Init();
	}

	void Set(cltInvestInfo* pinfo)
	{
		clPerson.Set(&pinfo->clPerson);
		siStockNum	= pinfo->siStockNum;
	}

	void Init()
	{
		clPerson.Init();
		siStockNum	= 0;
	}

	SI32 GetStockNum()const{return siStockNum;}
	void SetStockNum(SI32 num){siStockNum = num;}
};

class cltVillageInvestInfo{
public:
	SI32 siVillageUnique;
	cltInvestInfo clInvestInfo[MAX_INVEST_NUMBER];

	cltVillageInvestInfo()
	{
		siVillageUnique = 0;
	}

	void Set(cltVillageInvestInfo* pclMayorInfo)
	{
		memcpy(this, pclMayorInfo, sizeof(cltVillageInvestInfo));
	}
};

//--------------------------------------
// �ǰ� ����
//--------------------------------------
#define HEALTH_ORGAN_TYPE_ORG1			1		// ��ȭ���
#define HEALTH_ORGAN_TYPE_ORG2			2		// ��ȯ���
#define HEALTH_ORGAN_TYPE_ORG3			3		// ȣ����
#define HEALTH_ORGAN_TYPE_ORG4			4		// �Ű���

//--------------------------------
// �ǰ� Ŭ����. (�ٽ�) 
//--------------------------------
class cltHealthInfo{
public:
	//------------------------
	// ���� ���� 
	//------------------------
	SI16 siHungry		;			// �����.		(0~ 256)	�⺻�� 128	

	//-------------------------
	// ��� ���� 
	//-------------------------
	SI08 siInnerOrg1	;		// ��ȭ�� (-100 ~ 100)
	SI08 siInnerOrg2	;		// ��ȯ�� 
	SI08 siInnerOrg3	;		// ȣ��� 
	SI08 siInnerOrg4	;		// �Ű�� 

	//------------------------
	// ���� ���� 
	//------------------------
	UI08 uiOrg1Disease	;		// ��ȭ�� ����.			
	UI08 uiOrg2Disease	;		// ��ȯ�� ����. 
	UI08 uiOrg3Disease	;		// ȣ��� ����. 
	UI08 uiOrg4Disease	;		// �Ű�� ����. 

	//-----------------------
	// ���� �ǰ� ����.
	//-----------------------
	UI08 uiHealthPoint;		// 0 ~ 100	:100�̸� �ɷ�ġ�� ��� ������ �� �ֵ�. 

	cltHealthInfo()
	{
		Init();
	}

	void Init()
	{
		//------------------------
		// ���� ���� 
		//------------------------
		siHungry		= 0;			// �����.		
		
		//-------------------------
		// ��� ���� 
		//-------------------------
		siInnerOrg1		= 0;		// ��ȭ�� 
		siInnerOrg2		= 0;		// ��ȯ�� 
		siInnerOrg3		= 0;		// ȣ��� 
		siInnerOrg4		= 0;		// �Ű�� 
		
		//------------------------
		// ���� ���� 
		//------------------------
		uiOrg1Disease	= 0;		// ��ȭ�� ����.			
		uiOrg2Disease	= 0;		// ��ȯ�� ����. 
		uiOrg3Disease	= 0;		// ȣ��� ����. 
		uiOrg4Disease	= 0;		// �Ű�� ����. 
		
		//-----------------------
		// ���� �ǰ� ����.
		//-----------------------
		uiHealthPoint	= 100;
	}

	void Set(cltHealthInfo* pclinfo)
	{
		memcpy(this, pclinfo, sizeof(cltHealthInfo));
	}
	
	void IncreaseInnerOrg1(SI32 amount)
	{
		SI32 sum = siInnerOrg1 + amount;

		siInnerOrg1 = max(-100, min(100, sum));
	}
	void IncreaseInnerOrg2(SI32 amount)
	{
		SI32 sum = siInnerOrg2 + amount;

		siInnerOrg2 = max(-100, min(100, sum));
	}
	void IncreaseInnerOrg3(SI32 amount)
	{
		SI32 sum = siInnerOrg3 + amount;

		siInnerOrg3 = max(-100, min(100, sum));
	}
	void IncreaseInnerOrg4(SI32 amount)
	{
		SI32 sum = siInnerOrg4 + amount;

		siInnerOrg4 = max(-100, min(100, sum));
	}

	// ���� ����� �ջ��Ų��. 
	bool DecreaseOrg(SI32 type, SI32 amount, SI32 level);

	// ���� ����� ���¸� ���´�. 
	SI32 GetOrg(SI32 type)
	{
		switch(type)
		{
		case HEALTH_ORGAN_TYPE_ORG1: return siInnerOrg1;
		case HEALTH_ORGAN_TYPE_ORG2: return siInnerOrg2;
		case HEALTH_ORGAN_TYPE_ORG3: return siInnerOrg3;
		case HEALTH_ORGAN_TYPE_ORG4: return siInnerOrg4;
		}

		return 0;
	}
	
};

//-------------------------
// �ð������� ���� Ŭ���� 
//-------------------------
class cltDate{
public:
	UI32 uiYear:	8;	// 0 ~255
	UI32 uiMonth:	4;	// 0 ~15
	UI32 uiDay:		6;	// 0 ~63
	UI32 uiHour:	5;	// 0 ~31
	UI32 uiMinute:	6;	// 0 ~63
	UI32 uiReserved:3;	

public:

	void Set(SI32 year, SI32 month, SI32 day, SI32 hour, SI32 minute)
	{
		uiYear		= year;
		uiMonth		= month;
		uiDay		= day;
		uiHour		= hour;
		uiMinute	= minute;
		uiReserved	= 0;
	}

	void Set(const cltDate* pdate)
	{
		memcpy(this, pdate, sizeof(cltDate));
	}

	BOOL IncreaseTime(bool* pbdaychangedswitch, bool bforcetimeswitch);

	// �ð��� ���ڿ��� �����. 
	BOOL GetDateText(char* buffer);

	// ���� ���Ѵ�. 
	void AddMonth(SI32 month);
	
	// ��¥ ������ ���Ѵ�. (SI32 ���� �ϳ��� ��¥�� ��� ���ױ׸���) 
	SI32 GetDateVary()
	{
		SI32 vary ;
		vary = (uiDay-1) + (uiMonth-1)*30 + (uiYear*12)*30;

		return vary;
	}
	// �ð� ������ ���Ѵ�. 
	SI32 GetHourVary()
	{
		return  GetDateVary() * 24 + uiHour;
	}

	// DateVary�� ������ ���� ��¥ ������ �����Ѵ�. 
	void MakeFullDateFromDateVary(SI32 datevary)
	{
		uiYear  = datevary / (12* 30);
		datevary %= (12* 30);

		uiMonth = datevary / 30 + 1;
		datevary %= 30;

		uiDay		= datevary + 1;

		uiHour		= 0;
		uiMinute	= 0;
	}
	
	BOOL IsLaterDayThan( cltDate* pclDate );
	BOOL IsLaterMonthThan( cltDate* pclDate );

	void DiffDate( cltDate *pCurrentDate, cltDate *pOldDate );
	
	SI32 GetDay()
	{
		return min(30, max(1, uiDay));
	}
};

//----------------------------------------
// �Ӵ��� ���� 
//----------------------------------------
class cltRentContract{
public:
	SI32 siRentFee;		// �� �Ӵ��. 
	SI32 siRentPeriod;	// �Ӵ�Ⱓ. 
	cltDate	clDate;		// ����Ͻ�. 

	void Set(SI32 fee, SI32 period)
	{
		siRentFee		= fee;
		siRentPeriod	= period;		
	}
	
	void Set( SI32 Fee, SI32 Period, cltDate *pclDate )
	{
		siRentFee = Fee;
		siRentPeriod = Period;
		clDate.Set( pclDate );
	}

	void Set(const cltRentContract* pclcontract)
	{
		siRentFee		= pclcontract->siRentFee;
		siRentPeriod	= pclcontract->siRentPeriod;
		clDate.Set(&pclcontract->clDate);
	}

	BOOL IsValid()
	{
		if(siRentFee < 0		|| siRentFee > MAX_RENT_FEE)return FALSE;
		if(siRentPeriod <= 0	|| siRentPeriod > MAX_RENT_PERIOD)return FALSE;

		return TRUE;
	}

	BOOL IsSame(const cltRentContract* pclcontract)
	{
		if(siRentFee != pclcontract->siRentFee)return FALSE;
		if(siRentPeriod != pclcontract->siRentPeriod)return FALSE;

		return TRUE;
	}
	// ����� ����Ǿ��°�?
	bool IsEnd(cltDate* pcldate)
	{
		if(clDate.uiYear + siRentPeriod < pcldate->uiYear)return true;
		else if(clDate.uiYear + siRentPeriod == pcldate->uiYear)
		{
			if(clDate.uiMonth	< pcldate->uiMonth)return true;
			else if(clDate.uiMonth	== pcldate->uiMonth)
			{
				if( clDate.uiDay <= pcldate->uiDay)return true;
			}
		}

		return false;
	}

	void Init()
	{
		siRentFee		= 0;		// �� �Ӵ��. 
		siRentPeriod	= 0;		// �Ӵ�Ⱓ.
		clDate.Set(0, 0, 0, 0, 0);
	}
};


//-----------------------------------------------
// ���� ���� 
//-----------------------------------------------
#define HORSE_NEED_FEED			1		// ���̸� �� ���� �䱸. 

#define HORSE_REWARDTYPE_SPEED	1
#define HORSE_REWARDTYPE_STR	2
#define HORSE_REWARDTYPE_DEX	3
#define HORSE_REWARDTYPE_MAG	4

class cltHorse{
public:

	SI16 siHorseUnique;
	char	szName[MAX_HORSE_NAME];		// �̸� 
	cltDate clBirthDate;				// ���� 

	SI08	siSex;						// ���� 
	SI08	siPregnentPeriod;			// �ӽűⰣ
	SI16	siLife;						// ���� 

	SI16	siStr;
	SI16	siDex;
	SI16	siMag;
	SI16	siMoveSpeed;

	SI32	siStatusBonus;				// �� ���ʽ�

	cltDate clAddStatusDate;			// ���ɷ�����̿�� �ٸ� ����
	SI32	siStatusTicketNum;			// ���ɷ�����̿�� ���� �߶���

	//------------------------------
	// ���������� ������Ʈ �� �ð�. 
	//------------------------------
	SI32	siLastUpdateSecond;
	
	//---------------------------
	// ���� �䱸 ���� ���� 
	//---------------------------
	SI32	siLastNeedTime;				// ���������� �䱸�ߴ� �ð�. 
	SI32	siDueTime;					// �䱸���� ������ �Ѱ� �ð�. ( �� �ð����� �䱸������ ������Ű�� ���ϸ� ����) 

	SI16	siNeed;						// ���� �䱸����. 
	SI16	siPara1;		
	SI16	siPara2;
	SI16	siSupply;					// ���� ��Ȳ. 
	SI16	siRate;						// ���� �䱸�� ������ Ȯ��. 

	//--------------------------
	// ���� ���� 
	//--------------------------
	SI16	siRewardType;
	SI16	siRewardAmount;

public:

	cltHorse()
	{
		Init();
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltHorse));
	}

	cltHorse(SI16 unique, char* pname, cltDate* pcldate, SI08 sex, SI16 life, SI08 siPregnentPeriod,
			 SI16 str, SI16 dex, SI16 mag, SI16 movepseed, SI32 curhourvary,SI32 bonus,
			 cltDate* pclstatusdate , SI32 ticketnum )
	{
		siHorseUnique	= unique;
		MStrCpy( szName, pname, MAX_HORSE_NAME );
		clBirthDate.Set(pcldate);

		siSex				= sex;
		siPregnentPeriod	= siPregnentPeriod;
		siLife				= life;

		siStr				= str;
		siDex				= dex;
		siMag				= mag;
		siMoveSpeed			= movepseed;

		siStatusBonus		= bonus ;

		siLastUpdateSecond	= 0;
		siLastNeedTime		= curhourvary;	
		siDueTime			= 0;
		siNeed				= 0;
		siPara1				= 0;
		siPara2				= 0;
		siSupply			= 0;
		siRate				= 0;

		siRewardType		= 0;
		siRewardAmount		= 0;

		clAddStatusDate.Set(pclstatusdate);
		siStatusTicketNum	= ticketnum;
	}

	void Set(cltHorse* pclhorse)
	{
		memcpy(this, pclhorse, sizeof(cltHorse));
	}

	// ���ӿ� ����� ���� �̵� �ӵ��� ���Ѵ�.
	SI16 GetRealMoveSpeed()
	{
		return siMoveSpeed/100;
	}

	// ���̸� ���Ѵ�. 
	SI32 GetAge(SI32 curday)
	{
		SI32 birthday	= clBirthDate.GetDateVary();

		if(curday >= birthday)
		{
			SI32 age = (curday - birthday) / 360 + 1;
			return age;
		}
		return 0;
	}

	// ���� ������ ���θ� �Ǵ��Ѵ�. 
	bool IsSame(cltHorse* pclhorse)
	{
		if(pclhorse == NULL)return false;
		if(siHorseUnique	!= pclhorse->siHorseUnique)return false;
		if(siSex			!= pclhorse->siSex)return false;
		if(siLife			!= pclhorse->siLife)return false;
		if(siStr			!= pclhorse->siStr)return false;
		if(siDex			!= pclhorse->siDex)return false;
		if(siMag			!= pclhorse->siMag)return false;
		if(siMoveSpeed		!= pclhorse->siMoveSpeed)return false;
		if(siStatusBonus	!= pclhorse->siStatusBonus)return false;
		if(strcmp(szName, pclhorse->szName) != 0)return false;

		return true;
	}
};


//-------------------------------------------------
// cltAttackTarget
//-------------------------------------------------
class cltAttackTarget{
public:
	SI32 			siAttackID;                    // ������ ��� ���̵� 
	cltCharPos		clPos;
	
	SI32			siHitRate;						// ���� ��� ���� ���߷�. 

	cltAttackTarget()
	{
		siAttackID	= 0;

		siHitRate	= 0;
	}

	cltAttackTarget(SI32 attackid, const cltCharPos* pclpos, SI32 hitrate)
	{
		siAttackID	= attackid;
		clPos.Set(pclpos);

		siHitRate	= hitrate;
	}

	void Set(const cltAttackTarget* pcltarget)
	{
		siAttackID	= pcltarget->siAttackID;
		clPos.Set(&pcltarget->clPos);

		siHitRate	= pcltarget->siHitRate;
	}

	void Init()
	{
		siAttackID	= 0;
		siHitRate	= 0;
	}

	void SetAttackID(SI32 id){siAttackID	= id;}
	SI32 GetAttackID()const{return siAttackID;}

};

//---------------------------------
// ���� ���. 
//---------------------------------
#define MAX_PRISON_REASON_SIZE	50
#define MAX_PRISON_SECOND		30
#define MAX_PRISON_LIST_NUM		50 // �����Ǽ� â���� ������ ����Ʈ �� ����

struct HyungzoMember
{
	SI32	siDate;										// ����������
	SI32	siPrisonSecond;								// �����ð�
	char	szCharName[MAX_PLAYER_NAME];				// ������
	char	szPrisonReason[MAX_PRISON_REASON_SIZE];		// ��������
};

class cltGuiltyInfo{
public:
	SI32	siTotalPrisonSecond;			// �� �����ð�. 
	SI32	siLeftPrisonSecond;			// ���� �����ð�. 
	char	szPrisonReason[MAX_PRISON_REASON_SIZE];

	cltGuiltyInfo()
	{
		Init();
	}
	void Init()
	{
		siTotalPrisonSecond = 0;
		siLeftPrisonSecond	= 0;
		szPrisonReason[ 0 ] = NULL;
	}
	void Set(cltGuiltyInfo* pclinfo)
	{
		siTotalPrisonSecond = pclinfo->siTotalPrisonSecond;
		siLeftPrisonSecond	= pclinfo->siLeftPrisonSecond;

		MStrCpy( szPrisonReason, pclinfo->szPrisonReason, MAX_PRISON_REASON_SIZE );
	}
	void SetTotalPrisonSecond(SI32 second)
	{
		siTotalPrisonSecond = second ;
	}
	void SetLeftPrisonSecond(SI32 second)
	{
		siLeftPrisonSecond = second ;
	}
	void SetPrisonReason(char * reason)
	{
		MStrCpy(szPrisonReason, reason, MAX_PRISON_REASON_SIZE );
	}
};

//----------------------------------------------
// ������ ���� ���� 
//----------------------------------------------
class cltHuntStg{
public:
	SI16 siItemUnique;
	SI16 siItemNum;

	void Set(cltHuntStg* pclstg)
	{
		siItemUnique	= pclstg->siItemUnique;
		siItemNum		= pclstg->siItemNum;
	}

};

class cltHuntLineUp{
public:
	SI16 siLineUpKind;		// ������ ��ġ�� ���� ����
	SI16 siLineUpKindNum;	// ������ ��ġ�� ���� ����
	SI16 siLineUpKindLevel; // ������ ��ġ�� ���� ����

	void Set(cltHuntLineUp* pclinfo)
	{
		siLineUpKind		= pclinfo->siLineUpKind;
		siLineUpKindNum		= pclinfo->siLineUpKindNum;
		siLineUpKindLevel	= pclinfo->siLineUpKindLevel;
	}
};

#define MAX_FEAST_PRESENT_NUMBER							10
#define MAX_FEAST_STG_NUMBER								10

// ���ڽ� â�� ����
class cltFeastStg 
{
public:
	SI16 siItemUnique;
	SI16 siItemNum;

	void Set( cltFeastStg* pclstg )
	{
		siItemUnique	= pclstg->siItemUnique;
		siItemNum		= pclstg->siItemNum;
	}

};


//-----------------------------------------
// ���� ��� ��û�� ����. 
//-----------------------------------------
#define MAX_FATHER_APPLYER_LIST_NUMBER	50

class cltFatherApplyerInfo{
public:
	SI16 siCharUnique;
	SI32 siPersonID;
	SI16 siLevel;
	SI16 siFameLevel;
	bool bAngelSwitch;					// ��ȣõ������ ����. 
	char szAccountID[MAX_PLAYER_NAME];
	char szName[MAX_PLAYER_NAME];

	cltFatherApplyerInfo()
	{
		Init();
	}
	
	cltFatherApplyerInfo(SI16 charunique, SI32 personid, char* pname, char* paccountid, SI16 level, SI16 famelevel, bool bangel)
	{
		siCharUnique	= charunique;
		siPersonID		= personid;
		MStrCpy(szName,		pname, MAX_PLAYER_NAME);
		MStrCpy(szAccountID, paccountid, MAX_PLAYER_NAME);

		siLevel			= level;
		siFameLevel		= famelevel;
		bAngelSwitch	= bangel;
	}

	void Init()
	{
		siCharUnique	= 0;
		siPersonID		= 0;
		szName[ 0 ] = NULL;
		szAccountID[ 0 ] = NULL;

		siLevel			= 0;
		siFameLevel		= 0;
		bAngelSwitch	= false;
	}

	void Set(cltFatherApplyerInfo* pclinfo)
	{
		siCharUnique	= pclinfo->siCharUnique;
		siPersonID		= pclinfo->siPersonID;
		MStrCpy(szName, pclinfo->szName, MAX_PLAYER_NAME);

		MStrCpy(szAccountID, pclinfo->szAccountID, MAX_PLAYER_NAME);

		siLevel			= pclinfo->siLevel;
		siFameLevel		= pclinfo->siFameLevel;
		bAngelSwitch	= pclinfo->bAngelSwitch;
	}

};

//-------------------------------------
// ���� 1���� ����. 
//-------------------------------------
class cltChildInfo{
public:
	cltSimplePerson clPerson;
	SI16			siLevel;
	char			szAccountID[MAX_PLAYER_NAME];

	cltChildInfo()
	{
		siLevel = 0;
		szAccountID[ 0 ] = NULL;
	}
	cltChildInfo(cltSimplePerson* pclperson, SI16 level,char * accountID)
	{
		clPerson.Set(pclperson);
		siLevel	= level;
		MStrCpy(szAccountID,accountID,MAX_PLAYER_NAME);
	}
	void Init()
	{
		clPerson.Init();
		siLevel = 0;
		szAccountID[ 0 ] = NULL;
	}
	void Set(cltChildInfo* pclchild)
	{
		clPerson.Set(&pclchild->clPerson);
		siLevel	= pclchild->siLevel;
		MStrCpy(szAccountID,pclchild->szAccountID,MAX_PLAYER_NAME);
	}

};

//------------------------------
// Personģ�� ����. 
//------------------------------
#define MAX_FRIEND_NUMBER					20
class cltPFriendInfo{
public:
	cltSimplePerson clFriend[MAX_FRIEND_NUMBER];
	char szAccountID[MAX_FRIEND_NUMBER][MAX_PLAYER_NAME];
	void Set(cltPFriendInfo* pclinfo)
	{
		SI32 i;

		for(i = 0;i < MAX_FRIEND_NUMBER;i++)
		{
			clFriend[i].Set(&pclinfo->clFriend[i]);
			MStrCpy(szAccountID[i],pclinfo->szAccountID[i],MAX_PLAYER_NAME);
		}
	}
};

class cltFriendInfo : public cltPFriendInfo
{
public:
	SI32 siCharID[ MAX_FRIEND_NUMBER ];
	bool bConnectStatus[ MAX_FRIEND_NUMBER ];
//	char szAccountID[ MAX_FRIEND_NUMBER ][MAX_PLAYER_NAME];

	void Init()
	{
		for( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			memset( &clFriend[ i ], 0, sizeof( cltSimplePerson ) );
			siCharID[ i ] = 0;
			bConnectStatus[ i ] = false;
			szAccountID[ i ][ 0 ] = NULL;
		}
	}

	void Init( SI16 Index )
	{
		memset( &clFriend[ Index ], 0, sizeof( cltSimplePerson ) );
		siCharID[ Index ] = 0;
		bConnectStatus[ Index ] = false;
		szAccountID[ Index ][ 0 ] = NULL;
	}

	void Set( SI16 Index, SI32 PersonID, SI32 CharID, char *CharName, bool ConnectStatus ,char *AccountID)
	{
		siCharID[ Index ] = CharID;
		bConnectStatus[ Index ] = ConnectStatus;
		clFriend[ Index ].Set( PersonID, CharName );
		MStrCpy(szAccountID[Index],AccountID,MAX_PLAYER_NAME);
	}

	void Set( SI16 Index, SI32 CharID, bool ConnectStatus ,char * AccountID)
	{
		siCharID[ Index ] = CharID;
		bConnectStatus[ Index ] = ConnectStatus;
		MStrCpy(szAccountID[Index],AccountID, MAX_PLAYER_NAME);
	}
	
	void Set( cltPFriendInfo *pclInfo )
	{
		SI32 i;

		for(i = 0;i < MAX_FRIEND_NUMBER;i++)
		{
			clFriend[i].Set(&pclInfo->clFriend[i]);
		}
	}
	
	void Set( cltFriendInfo *pclInfo )
	{
		memcpy( this, pclInfo, sizeof( cltFriendInfo) );
	}
	
	SI16 GetFriendNum()
	{
		SI16 Counter = 0;
		for( SI32 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			if ( clFriend[ i ].GetPersonID() > 0 )
			{
				++Counter;
			}
		}

		return Counter;
	}
};

class cltPDailyQuestInfo
{
public:
	SI16 siMonsterKind;
	SI16 siMonsterNum;

	SI16 siRewardItemUnique;
	SI16 siRewardItemNum;
	SI32 siRewardExp;

	SI32 siFee;
	SI32 siLeftTime;

	SI16 siKillMonsterNum;

	cltPDailyQuestInfo()
	{
		Init();
	}

	void Init()
	{
		memset( this, 0, sizeof( cltPDailyQuestInfo ) );
	}

	void Set( SI16 MonsterKind, SI16 MonsterNum, SI16 RewardItemUnique, SI16 RewardItemNum, SI32 RewardExp, SI32 Fee, SI32 LeftTime, SI16 KillMonsterNum )
	{
		siMonsterKind = MonsterKind;
		siMonsterNum = MonsterNum;

		siRewardItemUnique = RewardItemUnique;
		siRewardItemNum = RewardItemNum;
		siRewardExp = RewardExp;
		
		siFee = Fee;

		siLeftTime = LeftTime;

		siKillMonsterNum = KillMonsterNum;
	}

	void Set( cltPDailyQuestInfo *pclInfo )
	{
		memcpy( this, pclInfo, sizeof( cltPDailyQuestInfo) );
	}
};

//--------------------------------------
// ���
//--------------------------------------
class cltMaterialInfo {
public:
	SI32	siUnique;		// ����� ����ũ. 
	SI32	siNeedNum;		// ����� �ʿ� ����. 

	cltMaterialInfo()
	{
		siUnique	= 0;
		siNeedNum	= 0;
	}

	cltMaterialInfo(SI32 unique, SI32 itemnum)
	{
		siUnique	= unique;
		siNeedNum	= itemnum;
	}

	void Set(cltMaterialInfo* pclmaterial)
	{
		siUnique	= pclmaterial->siUnique;
		siNeedNum	= pclmaterial->siNeedNum;
	}
	void Set(SI32 unique, SI32 itemnum)
	{
		siUnique	= unique;
		siNeedNum	= itemnum;
	}
};

//--------------------------------------
// ����
//--------------------------------------
class cltToolInfo {
public:
	SI32	siUnique;		// ������ ����ũ. 

	cltToolInfo()
	{
		siUnique	= 0;
	}

	cltToolInfo(SI32 unique)
	{
		siUnique	= unique;
	}

	void Set(cltToolInfo* pcltool)
	{
		siUnique	= pcltool->siUnique;
	}
	void Set(SI32 unique)
	{
		siUnique	= unique;
	}
};


class cltShipCarryWeight
{
public:
	SI32		siShipWeaponWeight;				// ���� �Ǵ� �� ���� ���� ����	
	SI32		siTransportWeight;				// �� ���� ����( ��� �Ǵ� �� + �Ҹ�Ǵ� �� ) - �Ҹ�� ���� �Ǵ� ������ �ǰ���...
	SI32		siPassengerWeight;				// ��� ���� ����

	cltShipCarryWeight()
	{
		Init();
	}

	void Init()
	{
		memset( this, 0, sizeof( cltShipCarryWeight ) );
	}

	void Set( cltShipCarryWeight *pclShipCarryWeight )
	{
		memcpy( this, pclShipCarryWeight, sizeof( cltShipCarryWeight ));
	}

	void Set( SI32 ShipWeaponWeight, SI32 TransportWeight, SI32 PassengerWeight )
	{
		siShipWeaponWeight = ShipWeaponWeight;		
		siTransportWeight = TransportWeight;
		siPassengerWeight = PassengerWeight;
	}
};

//--------------------------------------
// ������ ���� �⺻ ����. ( ���� ���� ex) Ȳ������ - kind = 1, ���� �⺻ �ɷ�ġ, �� �⺻ ���� ����.
//--------------------------------------
class cltShipBaseInfo
{
public:
	SI32				siKind;						// �� ����	

	SI16				siAP;						// �⺻ ���ݷ�( Attack Power )
	SI16				siAC;						// �⺻ ����( Armor Class )
	SI16				siMoveSpeed;				// �⺻ �̵��ӵ�. 

	SI16				siDurability;				// ���� ������
	SI16				siDecreaseDurability;		// �ִ� ������ ���̴� ��.
	
	cltShipCarryWeight	clShipCarryWeight;			// �� �⺻ ���� ����

	cltShipBaseInfo()
	{
		Init();
	}
	
	cltShipBaseInfo( SI16 kind, SI16 Damage, SI16 ac, SI16 movespeed, SI16 Durability, SI16 DecreaseDurability, cltShipCarryWeight *pclShipCarryWeight );

	void Init()
	{
		memset( this, 0, sizeof( cltShipBaseInfo ) );
	}

	void Set( cltShipBaseInfo *pclShipInfo )
	{
		memcpy( this, pclShipInfo, sizeof( cltShipBaseInfo ) );
	}

	void Set( SI32 Kind, SI32 Damage, SI32 AC, SI32 MoveSpeed, SI32 Durability, SI32 DecreaseDurability, cltShipCarryWeight *pclShipCarryWeight );

	// �� �⺻ ���� ������ ����.
	bool GetShipStatus( cltShipBaseInfo *pclShipBaseInfo );
	
};

class cltShip : public cltShipBaseInfo
{
public:
	SI32				siShipID;						// ���� ���� Ű( PersonID ���� �� )
	
	char				szName[MAX_SHIP_NAME];		// ���� �̸�.

	SI16				siShipPos;						// ���� ��ġ( ����, �ʵ�, ����, ���� )
	SI16				siPortUnitSlot;					// �谡 ������ �ִ� ��� ���� ��ȣ
	cltCharPos			clPos;							// �谡 ��ġ�Ѱ�.( �ʵ��� ��쿡�� )
	
	cltShip() : cltShipBaseInfo()
	{
		Init();
	}
	
	void Init()
	{
		ZeroMemory(this, sizeof(cltShip));
		siPortUnitSlot = -1;
		return;
	}
	
	cltShip( SI32 ShipID, SI16 kind, SI16 ShipPos, SI16 PortUnitSlot, cltCharPos *pclpos, SI16 ac, SI16 movespeed, cltShipCarryWeight *pclShipCarryWeight );

	void Set(cltShip* pclship)
	{
		memcpy( this, pclship, sizeof( cltShip ) );
		return;
	}
	
	void Set( cltShipBaseInfo *pclShipBaseInfo )
	{
		cltShipBaseInfo::Set( pclShipBaseInfo );
		return;
	}

	void Set( SI32 Kind, SI32 Damage, SI32 AC, SI32 MoveSpeed, SI32 Durability, SI32 MaxDurability, cltShipCarryWeight *pclShipCarryWeight,
		SI32 ShipID, char *Name, SI16 ShipPos, SI16 PortUnitSlot, cltCharPos *pclPos );

	bool GetShipPos( SI16 *pShipPos, SI16* pPortUnitSlot, cltCharPos *pclPos );
	bool SetShipPos( SI16 ShipPos, SI16 PortUnitSlot, cltCharPos *pclPos );
	
	char* GetName();
	bool SetName( char *ShipName );
};


//------------------------------------
// ����ڰ� ���� ���� ������. 
//------------------------------------
class cltPShipInfo{
public:	
	SI32					siRideShipID;
	cltShip					clShip[MAX_SHIP_PER_PERSON];
	
	cltPShipInfo()
	{
		Init();
	}

	void Init()
	{
		memset( this, 0, sizeof( cltPShipInfo ) );
	}
		
	void Set(cltPShipInfo* pclinfo )
	{
		memcpy( this, pclinfo, sizeof( cltPShipInfo ) );
	}

	SI32 GetShipNumber();

	bool IsShipExist( SI32 ShipID );

	cltShip *GetShipDataPtr( SI32 ShipID );
	SI16 GetShipDataIndex( SI32 ShipID );
	
	bool GetShipData( SI32 ShipID, cltShip *pclShip );
	bool SetShipDataChange( cltShip *pclShip );
		

	SI32 AddShip( cltShip *pclShip );
	
	// �谡 ���� ����. �������� 0 �̰ų�, ������ ��ü�� �ؼ�...
	bool ShipExplode( SI32 ShipID );
};

#endif

