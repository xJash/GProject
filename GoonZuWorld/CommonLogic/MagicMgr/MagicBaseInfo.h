#ifndef _MAGICBASEINFO_H_
#define _MAGICBASEINFO_H_

#include "../../Common/SMLib/BaseInclude/BaseInclude.h"
//#include <Graphic.h>

#include "../../Client/GlobalImgFile/GlobalImgFile.h"
#include "..\..\Common\CommonHeader.h"

class cltCharCommon;

//----------------------------------------------------------
// ������ ���� �ε����� �����ϱ� ���ؼ�
enum	MAGIC_TYPE
{	
	MAGIC_TYPE_START = 0, 
	MAGIC_TYPE_SWORD = MAGIC_TYPE_START, 
	MAGIC_TYPE_SPEAR,	
	MAGIC_TYPE_AXE,	
	MAGIC_TYPE_STAFF, 
	MAGIC_TYPE_BOW,		
	MAGIC_TYPE_GUN,
	MAGIC_TYPE_MON,
	MAGIC_TYPE_SOULGUARD,
	MAGIC_TYPE_SKILL_BOOK,
	MAGIC_TYPE_LAST	 = MAGIC_TYPE_SKILL_BOOK,
};

enum	MAGIC_GROUP
{	
	MAGIC_GROUP_START		= 1, 
	// [1]
	MAGIC_GROUP_FIREBALL	= MAGIC_GROUP_START, 
	MAGIC_GROUP_BIGWIND,	
	MAGIC_GROUP_THUNDER,
	MAGIC_GROUP_THUNDER1,
	MAGIC_GROUP_WHIRLPOOL,	
	MAGIC_GROUP_FLAME,		
	MAGIC_GROUP_ROCKSLIDE,   
	MAGIC_GROUP_HEAL,		
	MAGIC_GROUP_POISON,
	MAGIC_GROUP_ICE,
	// [11]
	MAGIC_GROUP_DRAIN,
	MAGIC_GROUP_LIGHTINGFIST,
	MAGIC_GROUP_POISONFLAME,
	MAGIC_GROUP_METEOR,	
	MAGIC_GROUP_DROPMONEY,
	MAGIC_GROUP_BLACKINK,
	MAGIC_GROUP_DROPSNOWMAN,
	MAGIC_GROUP_DROPFORK,
	MAGIC_GROUP_CURSEATTACK,	 
	MAGIC_GROUP_CURSECRITICAL,	
	// [21]
	MAGIC_GROUP_CURSEDEFENSE,	
	MAGIC_GROUP_CURSEMOVESPEED,
	MAGIC_GROUP_THROWKNIFE,
	MAGIC_GROUP_LASERBEAM,
	MAGIC_GROUP_TRIMETEOR,
	MAGIC_GROUP_FIREGOUND,
	MAGIC_GROUP_SWORDBOMB,
	MAGIC_GROUP_FREEZEEXPLOSION,
	MAGIC_GROUP_UPPERDRGON,
	MAGIC_GROUP_PALMWIND,
	// [31]
	MAGIC_GROUP_AURABLADE,
	MAGIC_GROUP_TRIPLEDEATH,
	MAGIC_GROUP_BLESSDAMAGE,
	MAGIC_GROUP_BLESSCIRICAL,
	MAGIC_GROUP_BLESSHITRATE,
	MAGIC_GROUP_BLESSRANGE,
	MAGIC_GROUP_BLESSATTACKINTERVAL,
	MAGIC_GROUP_BLESSMPRECOVERYTIME,
	MAGIC_GROUP_BLESSHP,
	MAGIC_GROUP_SUMMONDRAGON,
	// [41]
	MAGIC_GROUP_FIREBURN,
	MAGIC_GROUP_SKELLGHOST,
	MAGIC_GROUP_SWORDMETEOR,
	MAGIC_GROUP_FROZEN,
	MAGIC_GROUP_TWINSPEAR,
	MAGIC_GROUP_FIREWHIRLWIND,
	MAGIC_GROUP_NORTHWIND,
	MAGIC_GROUP_FIRESTORM,
	MAGIC_GROUP_EARTHQUAKE,
	MAGIC_GROUP_SPEAR_DRAGON,
	// [51]
	MAGIC_GROUP_GARGOYLE,
	MAGIC_GROUP_CERBERUS,
	MAGIC_GROUP_FROZENSORCERER,
	MAGIC_GROUP_MARIONETTE,
	MAGIC_GROUP_FROKEN,
	MAGIC_GROUP_ICEHOUND,
	MAGIC_GROUP_FROZENGOLEM,
	MAGIC_GROUP_FROZENKNIGHT,
	MAGIC_GROUP_FROZENQUEEN,
	MAGIC_GROUP_GOTPA,
	// [61]
	MAGIC_GROUP_NINJAPANDA,
	MAGIC_GROUP_RACCOONDOG,
	MAGIC_GROUP_BOSSMONKEY,
	MAGIC_GROUP_TOADPOISON,
	MAGIC_GROUP_BLOODBAT,
	MAGIC_GROUP_WEREWOLF,
	MAGIC_GROUP_PRIEST,
	MAGIC_GROUP_DEVILOUS,
	MAGIC_GROUP_GANGSI,
	MAGIC_GROUP_DRACULA,
	// [71]
	MAGIC_GROUP_HARPY,
	MAGIC_GROUP_MANDRAGORA,
	MAGIC_GROUP_GIRAFFE,
	MAGIC_GROUP_PAPAGOBLIN,
	MAGIC_GROUP_PIRATESOLDIER,
	MAGIC_GROUP_PIRATEARCHER,
	MAGIC_GROUP_BLACKBOSS,
	MAGIC_GROUP_EMPERORCAVALRY,
	MAGIC_GROUP_EMPERORMASTER,
	MAGIC_GROUP_GREATWALLSOLDIER,
	// [81]
	MAGIC_GROUP_GREATWALLMAGICIAN,
	MAGIC_GROUP_EMPERORWARRIOR,
	MAGIC_GROUP_GREATWALLSPIDER,
	MAGIC_GROUP_GREATWALLTWINHEAD,
	MAGIC_GROUP_BEARTANG,
	MAGIC_GROUP_SUPERBEARTANG,
	MAGIC_GROUP_SFROZENGOLEM,
	MAGIC_GROUP_SFROZENQUEEN,
	MAGIC_GROUP_CATPET,
	MAGIC_GROUP_COSMOSRABBIT,
	// [91]
	MAGIC_GROUP_RUDOLPHPET,
	MAGIC_GROUP_DROPGREATWALLASURA,
	MAGIC_GROUP_AMBERSAURUS,
	MAGIC_GROUP_ROLLINGSTEGO,
	MAGIC_GROUP_PUMPKIN,					// �ҿ� ���� ��Ų�� ��� �ϴ� ����
	MAGIC_GROUP_SUMMONDRAGON_STUN,			//[����] �巡��.
	MAGIC_GROUP_DRAGONFIRE,					//[����] �̴� �巡��.

	MAGIC_GROUP_SKILL_BOOK_FLAMEBUSTER,		//[����] ��ų��
	MAGIC_GROUP_SKILL_BOOK_FLAMEWHIRL,	
	MAGIC_GROUP_SKILL_BOOK_ICERAIN,		
	MAGIC_GROUP_SKILL_BOOK_WETFOG,		
	MAGIC_GROUP_SKILL_BOOK_CRASH,			
	MAGIC_GROUP_SKILL_BOOK_SLING,			
	MAGIC_GROUP_SKILL_BOOK_TORNADO,		
	MAGIC_GROUP_SKILL_BOOK_WINDCUTER,		

	MAGIC_GROUP_SKILL_BOOK_SUB,		
	
	MAGIC_GROUP_CLOWNBALL,
	MAGIC_GROUP_BOUQUET,

	MAGIC_GROUP_LAST = MAGIC_GROUP_BOUQUET,
};

enum	//MAGIC_TYPE_SWORD // 1 ~
{ 
	MAGIC_INDEX_START		= 1,
	MAGIC_SWORD_START		= MAGIC_INDEX_START,
	MAGIC_SWORD_STRIKING	= MAGIC_SWORD_START,
	MAGIC_SWORD_AURABLADE,
	MAGIC_SWORD_POISON,			
	MAGIC_SWORD_SWORDBOMB,
	MAGIC_SWORD_LAST		= MAGIC_SWORD_SWORDBOMB,

};
enum	//MAGIC_TYPE_SPEAR  
{ 
	MAGIC_SPEAR_START		= MAGIC_SWORD_LAST + 1,
	MAGIC_SPEAR_DEATHBLOW	= MAGIC_SPEAR_START,			
	MAGIC_SPEAR_POISON,			
	MAGIC_SPEAR_CURSECRITICAL,
	MAGIC_SPEAR_UPPERDRAGON,
	MAGIC_SPEAR_LAST		= MAGIC_SPEAR_UPPERDRAGON, 
};
enum	//MAGIC_TYPE_AXE 
{ 
	MAGIC_AXE_START			= MAGIC_SPEAR_LAST + 1,
	MAGIC_AXE_HITPOINT		= MAGIC_AXE_START,				
	MAGIC_AXE_POISON,
	MAGIC_AXE_DRAIN,
	MAGIC_AXE_METEOR,
	MAGIC_AXE_LAST			= MAGIC_AXE_METEOR, 
};
//-----------------------------------------------------------------
// ����2�� ĳ���� �ɷ�ġ ����Ǹ鼭 ������ ���� ���� ����
//-----------------------------------------------------------------
// !!!!!!!!! ���� �̷��� ���� ���ÿ�!!!!!!!!!!!!!!!!!!!!!!!!!
//-----------------------------------------------------------------
//-----------------------------------------------------------------
// !! �Ʒ� �ΰ��� enum .. ������ Ʋ���� �ȵ�
enum MAGIC_TYPE_STAFF_ORG	//MAGIC_TYPE_STAFF 
{ 
	ORG_MAGIC_STAFF_START	 = MAGIC_AXE_LAST + 1,		
	ORG_MAGIC_STAFF_FIREBALL = ORG_MAGIC_STAFF_START,
	ORG_MAGIC_STAFF_BIGWIND,		
	ORG_MAGIC_STAFF_THUNDER, 	
	ORG_MAGIC_STAFF_WHIRLPOOL,		
	ORG_MAGIC_STAFF_FLAME,			
	ORG_MAGIC_STAFF_POISON,
	ORG_MAGIC_STAFF_ICE,
	ORG_MAGIC_STAFF_QUICKMANA,
	ORG_MAGIC_STAFF_GAIN,
	ORG_MAGIC_STAFF_LAST	= ORG_MAGIC_STAFF_GAIN,
};
enum MAGIC_TYPE_STAFF_NEW	//MAGIC_TYPE_STAFF 
{ 
	NEW_MAGIC_STAFF_START	 = MAGIC_AXE_LAST + 1,		
	NEW_MAGIC_STAFF_FIREBALL = NEW_MAGIC_STAFF_START,
	NEW_MAGIC_STAFF_BIGWIND,		
	NEW_MAGIC_STAFF_THUNDER,
	NEW_MAGIC_STAFF_POISON,
	NEW_MAGIC_STAFF_ICE,
	NEW_MAGIC_STAFF_WHIRLPOOL,		
	NEW_MAGIC_STAFF_FLAME,
	NEW_MAGIC_STAFF_QUICKMANA,
	NEW_MAGIC_STAFF_GAIN,
	NEW_MAGIC_STAFF_LAST	= NEW_MAGIC_STAFF_GAIN,
};
//-----------------------------------------------------------------
// !! ���� �ΰ��� enum .. ������ Ʋ���� �ȵ�
//-----------------------------------------------------------------
// !!!!!!!!! ���� �̷��� ���� ���ÿ�!!!!!!!!!!!!!!!!!!!!!!!!!
//-----------------------------------------------------------------
enum	//MAGIC_TYPE_BOW 
{ 
	MAGIC_BOW_START			= ORG_MAGIC_STAFF_LAST + 1,
	MAGIC_BOW_HITPOINT		= MAGIC_BOW_START,
	MAGIC_BOW_TRIPLEDEATH,
	MAGIC_BOW_ICE,
	MAGIC_BOW_TRIMETEOR,
	MAGIC_BOW_LAST			= MAGIC_BOW_TRIMETEOR,
};

enum	//MAGIC_TYPE_GUN
{ 
	MAGIC_GUN_START			= MAGIC_BOW_LAST + 1,
	MAGIC_GUN_WIDEVISION	= MAGIC_GUN_START,
	MAGIC_GUN_CANNON,
	MAGIC_GUN_ICE,
	MAGIC_GUN_PALMWIND,
	MAGIC_GUN_LAST			= MAGIC_GUN_PALMWIND,
};

enum	//MAGIC_TYPE_MON
{ 
	MAGIC_MON_START		= MAGIC_GUN_LAST + 1,
	MAGIC_MON_FIREBALL  = MAGIC_MON_START,		
	MAGIC_MON_BIGWIND,
	MAGIC_MON_LIGHTINGFIST,
	MAGIC_MON_THUNDER,
	MAGIC_MON_THUNDER1,
	MAGIC_MON_WHIRLPOOL,
	MAGIC_MON_FLAME,
	MAGIC_MON_POISONFLAME,
	MAGIC_MON_ROCKSLIDE,
	MAGIC_MON_HEAL,
	MAGIC_MON_POISON,
	MAGIC_MON_ICE,
	MAGIC_MON_METEOR,
	MAGIC_MON_DRAIN,
	MAGIC_MON_DROPMONEY,
	MAGIC_MON_BLACKINK,
	MAGIC_MON_DROPSNOWMAN,
	MAGIC_MON_DROPFORK,
	MAGIC_MON_CURSEATTACK,
	MAGIC_MON_CURSECRITICAL,

	MAGIC_MON_CURSEDEFENSE,
	MAGIC_MON_CURSEMOVESPEED,
	MAGIC_MON_THROWKNIFE,
	MAGIC_MON_LASERBEAM,
	MAGIC_MON_TRIMETEOR,
	MAGIC_MON_FIREGROUND,
	MAGIC_MON_SWORDBOMB,
	MAGIC_MON_FREEZEEXPLOSION,

	MAGIC_MON_UPPERDRAGON,
	MAGIC_MON_PALMWIND,
	MAGIC_MON_SUMMONDRAGON,

	MAGIC_MON_FIREBURN,

	MAGIC_MON_SKELLGHOST,
	MAGIC_MON_SWORDMETEOR,

	MAGIC_MON_FROZEN,

	MAGIC_MON_TWINSPEAR,
	MAGIC_MON_FIREWHIRLWIND,

	MAGIC_MON_NORTHWIND,
	MAGIC_MON_FIRESTORM,
	MAGIC_MON_EARTHQUAKE,
	MAGIC_MON_SPEAR_DRAGON,

	MAGIC_MON_GARGOYLE,
	MAGIC_MON_CERBERUS,

	MAGIC_MON_FROZENSORCERER,
	MAGIC_MON_MARIONETTE,
	MAGIC_MON_FROKEN,
	MAGIC_MON_ICEHOUND,
	MAGIC_MON_FROZENGOLEM,
	MAGIC_MON_FROZENKNIGHT,
	MAGIC_MON_FROZENQUEEN,
	MAGIC_MON_GOTPA,
	MAGIC_MON_NINJAPANDA,
	MAGIC_MON_RACCOONDOG,
	MAGIC_MON_BOSSMONKEY,
	MAGIC_MON_TOADPOISON,

	MAGIC_MON_BLOODBAT,
	MAGIC_MON_WEREWOLF,
	MAGIC_MON_PRIEST,
	MAGIC_MON_DEVILOUS,
	MAGIC_MON_GANGSI,
	MAGIC_MON_DRACULA,
	
	MAGIC_MON_HARPY,
	MAGIC_MON_MANDRAGORA,
	MAGIC_MON_GIRAFFE,
	MAGIC_MON_PAPAGOBLIN,
	MAGIC_MON_PIRATESOLDIER,
	MAGIC_MON_PIRATEARCHER,
	MAGIC_MON_BLACKBOSS,
	MAGIC_MON_EMPERORCAVALRY,
	MAGIC_MON_EMPERORMASTER,
	MAGIC_MON_GREATWALLSOLDIER,
	MAGIC_MON_GREATWALLMAGICIAN,
	MAGIC_MON_EMPERORWARRIOR,
	MAGIC_MON_GREATWALLSPIDER,
	MAGIC_MON_GREATWALLTWINHEAD,
	MAGIC_MON_BEARTANG,
	MAGIC_MON_SUPERBEARTANG,
	MAGIC_MON_SFROZENGOLEM,
	MAGIC_MON_SFROZENQUEEN,
	MAGIC_MON_CATPET,
	MAGIC_MON_COSMOSRABBIT,
	MAGIC_MON_RUDOLPHPET,
	MAGIC_MON_DROPGREATWALLASURA,
	MAGIC_MON_AMBERSAURUS,
	MAGIC_MON_ROLLINGSTEGO,
	MAGIC_MON_SUMMONDRAGON_STUN,
	MAGIC_MON_DRAGONFIRE,
	MAGIC_MON_CLOWNBALL,
	MAGIC_MON_BOUQUET,


	MAGIC_MON_LAST		= MAGIC_MON_BOUQUET,
//	MAGIC_INDEX_LAST	= MAGIC_MON_LAST,
//	MAGIC_TOTAL	
};

enum MAGIC_TYPE_SOULGUARD
{
	MAGIC_SOULGUARD_START = MAGIC_MON_LAST + 1,
	MAGIC_SOULGUARD_FIRE  = MAGIC_SOULGUARD_START,
	MAGIC_SOULGUARD_PUMKIN,							// �ҿ� ���� ��Ų�� ����ϴ� ����

	MAGIC_SOULGUARD_LAST  = MAGIC_SOULGUARD_PUMKIN,

	//MAGIC_INDEX_LAST	  = MAGIC_SOULGUARD_LAST,
	//MAGIC_TOTAL	
};

enum MAGIC_TYPE_SKILL_BOOK
{
	MAGIC_SKILL_BOOK_START			= MAGIC_SOULGUARD_LAST + 1,
	
	MAGIC_SKILL_BOOK_FLAMEBUSTER	= MAGIC_SKILL_BOOK_START,
	MAGIC_SKILL_BOOK_FLAMEWHIRL,									// �ҿ� ���� ��Ų�� ����ϴ� ����
	MAGIC_SKILL_BOOK_ICERAIN,
	MAGIC_SKILL_BOOK_WETFOG,
	MAGIC_SKILL_BOOK_CRASH,
	MAGIC_SKILL_BOOK_SLING,
	MAGIC_SKILL_BOOK_TORNADO,
	MAGIC_SKILL_BOOK_WINDCUTER,

	MAGIC_SKILL_BOOK_BUFTIMEINCREASE1,		
	MAGIC_SKILL_BOOK_BUFTIMEINCREASE2,		
	MAGIC_SKILL_BOOK_HITCOUNTINCREASE,		
	MAGIC_SKILL_BOOK_FREEZINGTIMEINCREASE,	
	MAGIC_SKILL_BOOK_ADDMAGIC,				
	MAGIC_SKILL_BOOK_ATTINCREASE,			
	MAGIC_SKILL_BOOK_ATTINCREASE_CANE,		
	MAGIC_SKILL_BOOK_RANGEINCREASE,			
	MAGIC_SKILL_BOOK_COOLTIMEDECREASE,		
	MAGIC_SKILL_BOOK_MPDECREASE,			
	MAGIC_SKILL_BOOK_ORGDECREASE,			


	MAGIC_SKILL_BOOK_LAST			= MAGIC_SKILL_BOOK_ORGDECREASE,
	
	MAGIC_INDEX_LAST				= MAGIC_SKILL_BOOK_LAST,

	MAGIC_TOTAL	
};

enum	{ MAGIC_REST_STATUS, MAGIC_PLAY_STATUS, MAGIC_STOP_STATUS, MAGIC_COMPLETE_STATUS };		// ���� ������ ����� ����

//-----------���� ������ ����-------------------------------
#define	MAX_MAGIC_KIND_NUM					MAGIC_TOTAL				// ������ ���� �ִ� ����
//----------------------------------------------------------

//---------- �� ������ ���� ������ �ִ� ����----------------
//==============================================================
// GAMEMODE_CLIENT, GAMEMODE_MAPEDIT 
//==============================================================
#define MAX_MAGIC_CLIENT_NUM			100						// Ŭ���̾�Ʈ���� �� ������ �� �� �ִ� �� ����

//---------- ���� MSG ���� ---------------------------------
#define	MAX_MAGIC_MSG_NUM				500						// �޽��� �ִ��
//----------------------------------------------------------

#define MAX_MAGIC_MSG_LENGTH			256						// �޽����� �ִ� 256 byte

//==============================================================
// GAMEMODE_SERVER
//==============================================================
#define MAX_MAGIC_SERVER_NUM			1500					// �������� �� ������ �� �� �ִ� �� ����

//---------- ���� MSG ���� ---------------------------------
#define	MAX_MAGIC_MSG_SERVER_NUM		3000					// �޽��� �ִ��
//==============================================================




#define MAX_MAGIC_NAME_LENGTH				64

//==============================================================
// ���� ���� Ÿ��
//==============================================================
enum MAGIC_CASTTYPE
{
	MAGIC_CASTTYPE_PASSIVE = 0,	// �нú���
	MAGIC_CASTTYPE_ACTIVE,		// ��Ƽ����
	MAGIC_CASTTYPE_BUF,			// ������
};

// ���� �Ӽ�.
enum MAGIC_ATTRIBUTE
{
	MAGIC_ATTRIBUTE_NONE,	// ����.
	MAGIC_ATTRIBUTE_FIRE,	// ��.
	MAGIC_ATTRIBUTE_WATER,	// ��.
	MAGIC_ATTRIBUTE_EARTH,	// ��.
	MAGIC_ATTRIBUTE_WIND,	// �ٶ�.

	MAGIC_ATTRIBUTE_NUM
};

// �߰� �ÿ� ����. 
enum MAGIC_ADDMAGIC
{
	ADDMAGIC_NONE,				// ����.
	ADDMAGIC_CURSE_POISON,		// ��.
	ADDMAGIC_CURSE_ATTACK,		
	ADDMAGIC_CURSE_DEFENSE,	
	ADDMAGIC_CURSE_DODGE,		
	ADDMAGIC_CURSE_HIT,	
	ADDMAGIC_CURSE_ICE,

	ADDMAGIC_NUM
};

//---------- ������ �⺻ �Ӽ��� ----------------------------
struct	stMagicAttributeData
{
	TCHAR	strMagicKindName[ MAX_MAGIC_NAME_LENGTH ];
	TCHAR	strMagicName[ MAX_MAGIC_NAME_LENGTH ];	
	SI16	si16MagicUserUsing;							// ������ ��� ������ �������� ������
	SI08	si08MagicCastType;							// ���� ���� Ÿ��(0:Passive, 1:Active, 2:Buf)
	SI32	si32MagicDelay;								// ������ ����ǰ� ���� ������ ����Ǳ� ������ ����( �°����� �ʿ��� ó���ϰ� ���� )
	SI32	si32MagicSpendMana;
	SI32	si32MagicYIndent;
	SI32	si32MagicMaxDrawFrame;
	SI32	si32MagicDirection;
	SI32	si32MagicMinDamage;
	SI32	si32MagicMaxDamage;
	SI32	si32MagicRadius;
	SI32	si32MagicDistance;
	SI32	si32MagicHitIDExist;
	SI32	si32MagicMaxActionFrame;					// ������ ���� �ð����� ���ӵǾ�� �ϴ°� ���� �� �����Ƿ�...
	SI32	si32MagicNextFrameDelay;					// �� ���� �Ŀ� ���� ������ �ֱ� ���� delay time
	SI16	si16MagicSkillSpendMana;					// ��ų ������ ���� ���� �Ҹ�(%)
	SI16	si16MagicSkillIncreaseDamage;				// ��ų ������ ���� Ÿ�� ������(%)
	SI16	si16MagicSkillLevel;						// si32MagicSkillUnique ��ų �� ���� ���밡������...
	TCHAR	strMagicOrganName[MAX_MAGIC_NAME_LENGTH];	// ������ ���� ������ ���� ���ڿ� 
	SI16	si16MagicOrganKind;							// ������ ���� ������ ����
	SI16	si16MagicOrganDamage;						// ������ ���� 
	SI32	si32MagicExplainNum;						// ���� ���� �ؽ�Ʈ �޴��� ��ȣ
	SI08	siAttribute;								// ���� �Ӽ�.
	SI16	siAddMagic;									// �߰� �ÿ� ����. 
	DWORD	dwAddMagicDuration;							// �߰� �ÿ� ���� ����. 
	SI16	siAddMagicValue;							// �߰� �ÿ� ���� ���� �ð�. 

};
//----------------------------------------------------------


//---------- Push �� Pop ���� �޽��� ���� �� ����ü --------
#define	MAGIC_INCREASE_LIFE					35000					// ������ ä�� ( ���� ���� )
#define	MAGIC_DAMAGE						35001					// ������ ���� ( Ÿ���� �޾��� �ÿ� )
#define MAGIC_CIRCLE_DAMAGE					35002					// ������ ���� ( Ÿ���� �޾��� �ÿ� �ݰ��� �߽�����... ) - �ݰ��� ��� Ʋ�� ( �߽� ��ǥ ���� )
#define MAGIC_WHIRLPOOL_DAMAGE				35003					// ������ ���� ( Ÿ���� �޾��� �ÿ� �ݰ��� �߽�����... ) - �ݰ��� ���� ( �߽� ��ǥ �̵� )

struct	stMagicMsgHeader
{
	SI16				si16MsgSize;								// �޽��� ũ��
	SI32				si32MagicKind;								// ������ ����
	SI32				si32MsgKind;								// �޽��� ����
};

struct	stMagicMsgDamage
{
	stMagicMsgHeader	sMagicMsgHeader;
	
	
	SI32				si32FromID;
	SI32				si32ToID;

	SI32				si32Damage;									// Ÿ��ġ

};

struct	stMagicMsgCircleDamage
{
	stMagicMsgHeader	sMagicMsgHeader;
	SI32				si32FromID;
	SI32				si32ToID;
	SI32				si32Damage;									// Ÿ��ġ
	SI32				si32CurrentRadius;							// ���� �ݰ�( ���� �ݰ泻���� ������ �ֱ� ���ؼ�... )
	SI32				si32Radius;									// �ݰ�
};

struct	stMagicMsgWhirlPoolDamage
{
	stMagicMsgHeader	sMagicMsgHeader;
	SI32				si32FromID;
	SI32				si32ToID;
	SI32				si32Damage;									// Ÿ��ġ	
	SI32				si32Radius;									// �ݰ�
	SI32				si32XCenterPos;
	SI32				si32YCenterPos;
};


//=========================================================

struct stMagicHeader
{
	SI32				si32MagicKind;
	SI32				si32Size;
	SI32				si32FromID;
	SI32				si32ToID;
	SI32				si32Mana;
};

// 
struct stMagicInfo
{
	stMagicHeader sHeader;

	stMagicInfo()
	{
		sHeader.si32MagicKind	= 0;
		sHeader.si32Size		= sizeof(stMagicInfo);
		sHeader.si32FromID		= 0;
		sHeader.si32ToID		= 0;
		sHeader.si32Mana		= 0;
	}
	stMagicInfo(SI32 kind, SI32 fromid, SI32 toid, SI32 mana)
	{
		sHeader.si32MagicKind	= kind;
		sHeader.si32Size		= sizeof(stMagicInfo);
		sHeader.si32FromID		= fromid;
		sHeader.si32ToID		= toid;
		sHeader.si32Mana		= mana;
	}
};

//--------------------------------------------------------------------------------
// ���� ���� ���� ����
//--------------------------------------------------------------------------------
#define MAX_MAGICBUF_NUM	2	// �ѹ��� ȿ���� ����Ǵ� ���� ���� ����(�� ������ �ø��� �ٸ� �۾� �ʿ���� �����ȴ�)

//--------------------------------------------------------------------------------
// ���� ���� ���� ����
//--------------------------------------------------------------------------------
class CNMagicBuf
{
private:
	SI32	m_siMagicKind;		// ���� ����(���� ������ ���´�)
	SI32	m_siActionFrame;	// ���� ȿ���� ���Ǵ� �����Ӽ�(20�� 1�ʷ� ����Ѵ�)
	SI32	m_siDelayFrame;		// ���� ������ ����ϱ������ ��� �ð�(20�� 1�ʷ� ����Ѵ�)

	SI32	m_siStartTime;		// Ŭ���̾�Ʈ�� �������� �ƴ϶� ���� �ð����� �ð��� ���Ѵ�(�и�������)
	SI32	m_siActionTime;		// �ش� ������ �� �����ð�(�и�������)

	SI16	m_siDrawFrame;		// ������� ���� ����Ʈ �׸� ������
	SI16	m_siMaxFrame;		// �� ������ �׷����� �ִ� ������

public:
	CNMagicBuf()	{	Init();	};
	~CNMagicBuf()	{			};

	void	Init( void )
	{
		ZeroMemory( this, sizeof(CNMagicBuf) );
	}

	void	Set( CNMagicBuf* pclMagicBuf )
	{
		if ( pclMagicBuf )
		{	
			memcpy( this, pclMagicBuf, sizeof(CNMagicBuf) );
		}
	}

	void	Set( SI32 siMagicKind, SI32 siLemainFrame, SI32 siDelayFrame, SI32 siStartTime, SI32 siActionTime, SI16 siDrawFrame=0, SI16 siMaxFrame=0 )
	{
		m_siMagicKind	= siMagicKind;

		m_siActionFrame	= siLemainFrame;
		m_siDelayFrame	= siDelayFrame;

		m_siStartTime	= siStartTime;
		m_siActionTime	= siActionTime;

		m_siDrawFrame	= siDrawFrame;
		m_siMaxFrame	= siMaxFrame;
	}

	SI32	GetMagicKind( void )					{	return m_siMagicKind;					}
	void	SetMagicKind( SI32 siMagicKind )		{	m_siMagicKind = siMagicKind;			}

	SI32	GetActionFrame( void )					{	return m_siActionFrame;					}
	void	SetActionFrame( SI32 siActionFrame )	{	m_siActionFrame = siActionFrame;		}
	SI32	AddActionFrame( SI32 siAddFrame )		{	return (m_siActionFrame += siAddFrame);	}
	SI32	SubActionFrame( SI32 siSubFrame )		{	return (m_siActionFrame -= siSubFrame);	}

	SI32	GetDelayFrame( void )					{	return m_siDelayFrame;					}
	void	SetDelayFrame( SI32 siDelayFrame )		{	m_siDelayFrame = siDelayFrame;			}
	SI32	AddDelayFrame( SI32 siAddFrame )		{	return (m_siDelayFrame += siAddFrame);	}
	SI32	SubDelayFrame( SI32	siSubFrame )		{	return (m_siDelayFrame -= siSubFrame);	}

	SI32	GetStartTime( void )					{	return m_siStartTime;					}
	void	SetStartTime( SI32 siStartTime )		{	m_siStartTime = siStartTime;			}

	SI32	GetActionTime( void )					{	return m_siActionTime;					}
	void	SetActionTime( SI32 siActionTime )		{	m_siActionTime = siActionTime;			}

	SI16	GetDrawFrame( void )					{	return m_siDrawFrame;					}
	void	SetDrawFrame( SI16 siDrawFrame )		{	m_siDrawFrame = siDrawFrame;			}
	SI16	AddDrawFrame( SI16 siAddFrame )			{	return (m_siDrawFrame += siAddFrame);	}
	SI16	SubDrawFrame( SI16 siSubFrame )			{	return (m_siDrawFrame -= siSubFrame);	}

	SI16	GetMaxFrame( void )						{	return m_siMaxFrame;					}
	void	SetMaxFrame( SI16 siMaxFrame )			{	m_siMaxFrame = siMaxFrame;				}

	bool	IsEmpty( void )							{	return (m_siMagicKind<=0?true:false);	}

};

//--------------------------------------------------------------------------------
// ���� ���� ���� �޴���
//--------------------------------------------------------------------------------
class CNMagicBufMgr
{
public:
	enum MBM_VARIABLE
	{
		MBM_VARIABLE_RET_DONOTHAVE = -1,
	};
private:
	CNMagicBuf	m_clMagicBuf[MAX_MAGICBUF_NUM];

public:
	CNMagicBufMgr()
	{
		Init();
	}
	~CNMagicBufMgr()
	{
	}

	void	Init( void )
	{
		ZeroMemory( this, sizeof(CNMagicBufMgr) );
	}

	void	Set( CNMagicBufMgr* pclMagicBufMgr );

	void	PushMagicBuf( SI32 siMagicKind, SI32 siDecMagicDelayRate, SI32 siID );


	// �ش� ������ �� �� �ִ� ������ Ÿ���� �˻��Ѵ�
	bool	CheckDelay( SI32 siMagicKind );
	// ������ �� �� �ִ� ������ �ִ����� �˻�
	bool	CheckMagicBufSlot( SI32 siMagicKind );
	// ��Ÿ��/��ȿ�ð� �������� �����Ѵ�(siDecFram�� ����̴�)
	void	DecFrame( SI32 siDecFrame );

	void	Draw( SI32 si32CenterXPos, SI32	si32CenterYPos );
	void	MagicBufDraw( SI32 siMagicBufSlotNum, SI32 si32CenterXPos, SI32	si32CenterYPos );
	SI32	GetGIMGIndex( SI32 siMagicGroup );


	SI32	GetIncDamage( cltCharCommon* pclCharCommon );			// ������ �����Ǵ� ���ݷ�
	SI32	GetIncCriticalRate( cltCharCommon* pclCharCommon );		// ������ �����Ǵ� �ʻ��
	SI32	GetIncHitRate( cltCharCommon* pclCharCommon );			// ������ �����Ǵ� ���߷�
	SI32	GetIncRange( cltCharCommon* pclCharCommon );			// ������ �����Ǵ� �����Ÿ�
	SI32	GetIncAttackInterval( cltCharCommon* pclCharCommon );	// ������ �����Ǵ� ���ݼӵ�
	SI32	GetIncMPRecoveryTime( cltCharCommon* pclCharCommon );	// ������ �����Ǵ� MP ȸ���ð�
	SI32	GetIncHP( cltCharCommon* pclCharCommon );				// ������ �����Ǵ� HP

	void	MoveToFront( void );						// ��� ������ 0������������ �̵���Ų��

	CNMagicBuf*	GetMagicBuf( SI32 siIndex );
private:
	// ���� ���� �ִ� �����߿� siMagicGroup�� ���� �ִ°�?
	SI32	IsHaveMagicGroup( SI32 siMagicGroup );
	SI32	GetTotalSkillLevel( cltCharCommon* pclCharCommon, SI32 siMagicKind );
	void	PlayTheEffect( SI32 siMagicGroup );

};

#endif