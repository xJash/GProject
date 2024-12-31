//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _SKILL_H
#define _SKILL_H

#include <Directives.h>

#define MAX_SKILL_NUMBER			121		// ��ų�� �ִ� ����. (120->121)
#define ALL_MAKESKILL_UNIQUE		((MAX_SKILL_NUMBER) + 1)	// ������ų ���θ� ����Ŵ
#define ALL_WEAPONSKILL_UNIQUE		((MAX_SKILL_NUMBER) + 2)	// ���⽺ų ����
#define ALL_PRODUCTSKILL_UNIQUE		((MAX_SKILL_NUMBER) + 3)	// ���꽺ų ����
#define ALL_ALLSKILL_UNIQUE			((MAX_SKILL_NUMBER) + 4)	// ��� ��ų
#define ALL_ALLAVATARSKILL_UNIQUE	((MAX_SKILL_NUMBER) + 5)	// ��� �ƹ�Ÿ ��ų

#define MAX_CHILD_SKILL_NUM			4
#define MAX_SKILL_TYPE_NUMBER		15

//KHY - 0318 - �����߱� ��ų 70����.
#if _NHN_CHINA
	#define MAX_SKILL_LEVEL				70			// ���迡 ���� ���� �ְ�ܰ�. 
#else
	#define MAX_SKILL_LEVEL				80			// ���迡 ���� ���� �ְ�ܰ�. 
#endif

#define MAX_WEAPONSKILL_LEVEL		5			// �������� �ְ� ����

#define MAX_SKILL_NAME_LENGTH		64			// ��ų �̸��� �ִ� ����. 
#define MAX_SKILL_TYPE_NAME_LENGTH	64
#define MAX_SKILL_TYPE_CODE_LENGTH	64

#define MAX_SKILL_TREEDLG_TIMER		1000		// ��� Ʈ�� ���̾�α��� Ÿ�̸� ���� ����

//--------------------------------
// ��ų�� Ÿ��.
//--------------------------------
// 1 ~ MAX_SKILL_TYPE_NUMBER���� ���������� ������ �Ѵ�. 

// �Ʒ��� type
//#define SKILLTYPE_MED				1			// �Ǽ�
//#define SKILLTYPE_FOOD		    2			// �丮��

//#define SKILLTYPE_WEAR				1			// ������ۼ�  
//#define SKILLTYPE_MAKEWEAPON		2			// �������ۼ�
//#define SKILLTYPE_ACCESSARY			3			// ��ű����ۼ�
//#define SKILLTYPE_USEWEAPON			4			// ���� ����
//#define SKILLTYPE_MAKETOOL			5			// ���� ���ۼ� 
//#define SKILLTYPE_SEA				6			// �ؾ���
//#define SKILLTYPE_HARVEST			7			// �⺻�����
//#define SKILLTYPE_ETC				8			// ��Ÿ���
//#define SKILLTYPE_FIGHT				9			// ����������
//#define SKILLTYPE_MAKEAVATAR		10			// �ƹ�Ÿ ������


//	[��ȣ_SKILLINTERFACE]
#define SKILLTYPE_R_USEWEAPON			1			// �������
#define SKILLTYPE_R_MAKEWEAPON			2			// �������ۼ�
#define SKILLTYPE_R_ARMOR				3			// �����ۼ�
#define SKILLTYPE_R_MAKEHARVEST			4			// �������ۼ�
#define SKILLTYPE_R_HARVEST				5			// ������
#define SKILLTYPE_R_MAKECLOTH			6			// ��ܼ�
#define SKILLTYPE_R_MAKEACCESSARY		7			// �Ǽ��縮 ���ۼ�		
#define SKILLTYPE_R_ETC					8			// ��Ÿ���
#define SKILLTYPE_FIGHT					9			// ����������



// ���� ��ų����
#define WEAPONSKILLTYPE_SWORD		1
#define WEAPONSKILLTYPE_SPEAR		2
#define WEAPONSKILLTYPE_AXE			3
#define WEAPONSKILLTYPE_STAFF		4
#define WEAPONSKILLTYPE_BOW			5
#define WEAPONSKILLTYPE_GUN			6

#define MAX_WEAPONSKILLTYPE_NUM		6				// ���⽺ų �ִ� ����

//�Ʒ� ����� unique ��
#define SKILL_MAKEMED					1			// ��������.
#define SKILL_MAKEFOOD					2			// �丮��.
#define SKILL_MAKEARMOUR1				3			// �������ۼ�1
#define SKILL_MAKEHELMET1				4			// �������ۼ�1
#define SKILL_MAKESWORD1				5			// �����ۼ�1
#define SKILL_MAKESPEAR1				6			// â���ۼ�1
#define SKILL_MAKEAXE1					7			// �������ۼ�1
#define SKILL_MAKESTAFF1				8			// ���������ۼ�1
#define SKILL_MAKEBOW1					9			// Ȱ���ۼ�1
#define SKILL_MAKEGUN1					10			// �����ۼ�1
#define SKILL_MAKESHOES1				11			// �Ź����ۼ�1	
#define SKILL_MAKEBELT1					12			// ������ۼ�1	
//cyj �������ۼ� ���� #define SKILL_MAKERING1				13			// �������ۼ�1
#define SKILL_MAKEDRESS1				14			// �Ǻ����ۼ�1
#define SKILL_USESWORD1					16			// �˼�
#define SKILL_USESPEAR1					17			// â��
#define SKILL_USEBOW1					18			// �ü�
#define SKILL_USEAXE1					19			// �μ�(������)
#define SKILL_USEGUN1					20			// �Ѽ�
#define SKILL_USESTAFF1					21			// �����̼�
#define SKILL_SUMMON					22			// ��ȯ�� 
#define SKILL_FISH						23			// ��ȹ�� 
//cyj ��������ۼ� ���� #define SKILL_MAKENECK1				25			// ��������ۼ�1
#define SKILL_HORSETRAINING				26			// �����ü�
#define SKILL_MAKEIRON1					27			// ö�����ۼ� 

//cyj ����/���汸/� ���ۼ� ����
//#define SKILL_MAKEFISHINGROD		24			// ����ۼ�. 
//#define SKILL_MAKEDISH1			28			// �������ۼ� 

//cyj �������ۼ� ���� #define SKILL_MAKECANNON			29			// ����������
//cyj �������ۼ� ���� #define SKILL_MAKESCROLL			30			// �������ۼ�
#define SKILL_CAPTURE					31			// ��ȹ��
#define SKILL_MAKEHAT1					32			// �������ۼ�
//cyj ��ó���� ���� #define SKILL_ALCHEMY				33			// ��ó����
#define SKILL_FARM						34			// ����
#define SKILL_MINE						35			// ä����

#define SKILL_SWORD_INCDR				36			// �˼� : ����ȸ��������
#define SKILL_SWORD_INCVIT				37			// �˼� : �ִ���������
#define SKILL_SWORD_INCMAGAT			38			// �˼� : �������ݷ����� (���� SKILL_SWORD_INCWEAAT:������ݷ� ����)

#define SKILL_SPEAR_INCAC				39			// â�� : ������������
#define SKILL_SPEAR_DOUBLEAT			40			// â�� : ����Ȯ���� ���ݷ��� 2�� (���� SKILL_SPEAR_INCRECMANA:����ȸ��������)
#define SKILL_SPEAR_INCMAGAT			41			// â�� : �������ݷ�����

#define SKILL_AXE_DECGAP				42			// �μ� : ���ݷ°��ݰ��� (���� SKILL_AXE_INCRECLIFE:ü��ȸ��������)
#define SKILL_AXE_INDURE				43			// �μ� : �ǰݵ��۽ð�����
#define SKILL_AXE_INCCRI				44			// �μ� : �ʻ�������

#define SKILL_BOW_DRAIN					45			// �ü� : ü����� (���� SKILL_BOW_INCAR:����������)
#define SKILL_BOW_INCRANGE				46			// �ü� : ��Ÿ�����
#define SKILL_BOW_INCMAGAT				47			// �ü� : �������ݷ�����

#define SKILL_GUN_INCPHYAR				48			// �Ѽ� : �������߷����� (���� SKILL_GUN_INCMOVE:�̵��ӵ�����)
#define SKILL_GUN_DECMAGDELAY			49			// �Ѽ� : ������밣�ݰ���
#define SKILL_GUN_INCWEAAT				50			// �Ѽ� : ������ݷ�����

#define SKILL_STAFF_INCMAG				51			// �����̼� : �ִ뵵������
#define SKILL_STAFF_DECUSEMANA			52			// �����̼� : �����ʿ䵵�°���
#define SKILL_STAFF_INCMAGAT			53			// �����̼� : �������ݷ�����

#define SKILL_MAKETOOL1					54			// ���굵�����ۼ�

#define SKILL_ARTIFACT					55			// [�߰� : Ȳ���� 2008. 2. 25 => ��Ƽ��Ʈ �� (����ü ������) ]
// �� �������� ���� 1�ܰ�
#define SKILL_SWORD_SPEAR_INCAC			56
#define SKILL_SWORD_AXE_DECGAP			57
#define SKILL_SWORD_BOW_DRAIN			58
#define SKILL_SWORD_GUN_INCPHYAR		59
#define SKILL_SWORD_STAFF_INCMAG		60
// �� �������� ���� 2�ܰ�
#define SKILL_SWORD_SPEAR_DOUBLEAT		61
#define SKILL_SWORD_AXE_INDURE			62
#define SKILL_SWORD_BOW_INCRANGE		63
#define SKILL_SWORD_GUN_DECMAGDELAY		64
#define SKILL_SWORD_STAFF_DECUSEMANA	65

// â �������� ���� 1�ܰ�
#define	SKILL_SPEAR_SWORD_INCDR			66
#define	SKILL_SPEAR_AXE_DECGAP			67
#define	SKILL_SPEAR_BOW_DRAIN			68
#define	SKILL_SPEAR_GUN_INCPHYAR		69
#define	SKILL_SPEAR_STAFF_INCMAG		70
// â �������� ���� 2�ܰ�
#define	SKILL_SPEAR_SWORD_INCVIT		71
#define	SKILL_SPEAR_AXE_INDURE			72
#define	SKILL_SPEAR_BOW_INCRANGE		73
#define	SKILL_SPEAR_GUN_DECMAGDELAY		74
#define	SKILL_SPEAR_STAFF_DECUSEMANA	75

// ���� �������� ���� 1�ܰ�
#define	SKILL_AXE_SWORD_INCDR			76
#define	SKILL_AXE_SPEAR_INCAC			77
#define	SKILL_AXE_BOW_DRAIN				78
#define	SKILL_AXE_GUN_INCPHYAR			79
#define	SKILL_AXE_STAFF_INCMAG			80
// ���� �������� ���� 2�ܰ�
#define	SKILL_AXE_SWORD_INCVIT			81
#define	SKILL_AXE_SPEAR_DOUBLEAT		82
#define	SKILL_AXE_BOW_INCRANGE			83
#define	SKILL_AXE_GUN_DECMAGDELAY		84
#define	SKILL_AXE_STAFF_DECUSEMANA		85

// Ȱ �������� ���� 1�ܰ�
#define	SKILL_BOW_SWORD_INCDR			86
#define	SKILL_BOW_SPEAR_INCAC			87
#define	SKILL_BOW_AXE_DECGAP			88
#define	SKILL_BOW_GUN_INCPHYAR			89
#define	SKILL_BOW_STAFF_INCMAG			90
// Ȱ �������� ���� 2�ܰ�
#define	SKILL_BOW_SWORD_INCVIT			91
#define	SKILL_BOW_SPEAR_DOUBLEAT		92
#define	SKILL_BOW_AXE_INDURE			93
#define	SKILL_BOW_GUN_DECMAGDELAY		94
#define	SKILL_BOW_STAFF_DECUSEMANA		95

// �� �������� ���� 1�ܰ�
#define	SKILL_GUN_SWORD_INCDR			96
#define	SKILL_GUN_SPEAR_INCAC			97
#define	SKILL_GUN_AXE_DECGAP			98
#define	SKILL_GUN_BOW_DRAIN				99
#define	SKILL_GUN_STAFF_INCMAG			100
// �� �������� ���� 2�ܰ�
#define	SKILL_GUN_SWORD_INCVIT			101
#define	SKILL_GUN_SPEAR_DOUBLEAT		102
#define	SKILL_GUN_AXE_INDURE			103
#define	SKILL_GUN_BOW_INCRANGE			104
#define	SKILL_GUN_STAFF_DECUSEMANA		105

// ������ �������� ���� 1�ܰ�
#define	SKILL_STAFF_SWORD_INCDR			106
#define	SKILL_STAFF_SPEAR_INCAC			107
#define	SKILL_STAFF_AXE_DECGAP			108
#define	SKILL_STAFF_BOW_DRAIN			109
#define	SKILL_STAFF_GUN_INCPHYAR		110
// ������ �������� ���� 2�ܰ�
#define	SKILL_STAFF_SWORD_INCVIT		111
#define	SKILL_STAFF_SPEAR_DOUBLEAT		112
#define	SKILL_STAFF_AXE_INDURE			113
#define	SKILL_STAFF_BOW_INCRANGE		114
#define	SKILL_STAFF_GUN_DECMAGDELAY		115

//	�ƹ�Ÿ ������
#define SKILL_MAKEAVATAR_DRESS			116			//	[��ȣ]	�ƹ�Ÿ �Ǻ� ���ۼ�
#define SKILL_MAKEAVATAR_HAT			117			//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
#define SKILL_MAKEAVATAR_MANTLE			118			//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
#define SKILL_MAKEAVATAR_RING			119			//	[��ȣ]	�ƹ�Ÿ ���� ���ۼ�
#define SKILL_MAKEAVATAR_NECK			120			//	[��ȣ]	�ƹ�Ÿ ����� ���ۼ�

#define SKILL_SIKLLBOOK					121			//	[����]	��ų�� ��ų. �� ��ų�� �������̴�. � ��ų�ΰ��� ���������� �ʴ�.





//[�˸�: ��ų ������ �ִ� 255(����� MAX_SKILL_NUMBER=120) ������ ���� �մϴ�. �� �ø����� DB�۾� �ʿ��մϴ�]
//---------------------------------------------------------------------------------------------------------------------

// �� ������� �Ӽ�. 
#define SKILLATB_LIST				0x00000001	// ���ε�� ��� ��Ͽ� �ִ� ���. 
#define SKILLATB_WEAPON				0x00000002	// �������â ��Ͽ� �ִ� ���
#define SKILLATB_HIDDENGRADE1		0x00000004	// �������� ���� 1�ܰ� ���
#define SKILLATB_HIDDENGRADE2		0x00000008	// �������� ���� 2�ܰ� ���

#define MAX_WEAPONSKILL_POW1		1			// 20% ����
#define MAX_WEAPONSKILL_POW2		2			// 30% ����
#define MAX_WEAPONSKILL_POW3		3			// 40% ����

//-----------------------------------------
// Bit ���� 
//----------------------------------------
#define UPGRADESKILLTYPE_MAKE				1
#define UPGRADESKILLTYPE_USEWEAPON			2
#define UPGRADESKILLTYPE_USE_TABLE_VALUE	4	// ���̺� �ִ� ���� ����Ϸ��� �̰��� ����. 
#define UPGRADESKILLTYPE_STATUS_UP_20		8	// �Ǻ�(����, ��)�� �������� ���� +20 �����. 



// ���������
enum SKILLMASTER
{
	SKILLMASTER_NONE				= 0,

	SKILLMASTER_PHYSICALATTACK,		// ��������
	SKILLMASTER_PHYSICALDEFENSE,	// �������
	SKILLMASTER_PHYSICALDODGE,		// ����ȸ��
	SKILLMASTER_PHYSICALHIT,		// ��������

	SKILLMASTER_MAGICALATTACK,		// ��������
	SKILLMASTER_MAGICALDEFENSE,		// �������
	SKILLMASTER_MAGICALDODGE,		// ����ȸ��
	SKILLMASTER_MAGICALHIT,			// ��������

	SKILLMASTER_STR,				// �ٷ�
	SKILLMASTER_HAND,				// ������
	SKILLMASTER_DEX,				// ���߷�
	SKILLMASTER_MAG,				// ����
	SKILLMASTER_WIS,				// ����
	SKILLMASTER_VIT,				// �����
	SKILLMASTER_LUCK,				// ���

	SKILLMASTER_CRITICAL,			// ũ��Ƽ��
	SKILLMASTER_ATTACKRANGE,		// ���ݹ���
	SKILLMASTER_ATTACKINTERVAL,		// ���ݼӵ�

	//---------------------------------------------
	// ���ο� ����� ���밪�� �� ���� ���ּ���
	//---------------------------------------------
	SKILLMASTER_MAX
};

enum SKILLMASTER_WEAPONTYPE
{
	SKILLMSTER_WEAPONTYPE_NONE	= 0,

	SKILLMSTER_WEAPONTYPE_SWORD,
	SKILLMSTER_WEAPONTYPE_SPEAR,
	SKILLMSTER_WEAPONTYPE_BOW,
	SKILLMSTER_WEAPONTYPE_AXE,
	SKILLMSTER_WEAPONTYPE_GUN,
	SKILLMSTER_WEAPONTYPE_STAFF,

	SKILLMSTER_WEAPONTYPE_MAX
};

class cltCharManager;
class cltItem;
class cltSkillManager;

// ������ ��ų�� ���� ����. 
class cltSkillSaveUnit{
public:
	UI08 uiSkillUnique;
	UI08 uiLevel;

	SI32 siSkillExp;		// ��� ����ġ.

	cltSkillSaveUnit()
	{
		uiSkillUnique	= 0;
		uiLevel			= 0;
		siSkillExp		= 0;
	}
	void Set(cltSkillSaveUnit* pclinfo)
	{
		uiSkillUnique	= pclinfo->uiSkillUnique;
		uiLevel			= pclinfo->uiLevel;
		siSkillExp		= pclinfo->siSkillExp;
	}
};

#define		THAT_SKILL_EXIST			3100		// ������ ��ų�� �����Ѵ�.
#define		PARENT_NOT_EXIST			3200		// �θ� ��ų�� ���� �������� ���ߴ�.
//---------------------------------------
// ��ų�� ������ ����� �Ŵ���. 
//---------------------------------------
class cltPSkillInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltSkillSaveUnit, MAX_SKILL_NUMBER>	clSkill;
#else
	cltSkillSaveUnit								clSkill[MAX_SKILL_NUMBER];
#endif

	cltPSkillInfo()
	{
	}

	~cltPSkillInfo(){};


	void Set(cltPSkillInfo* pskill);

	// ����� ���� �� �ִ��� Ȯ���Ѵ�. 
	bool CanMake(SI32 skillunique, SI32* pskillindex, SI32 *pRetVal);

	// ��ų�� ���ʷ� �����Ѵ�.
	BOOL MakeSkill(SI32 skillunique);

	// ��ų�� �����ش�.
	BOOL IncreaseSkillLevel(SI32 skillunique, SI32 level);
	//// ���� ������ �����ش�.
	//BOOL IncreaseSkillExpLevel(SI32 skillunique, SI32 level);

	// Ư�� ��ų�� ����ġ�� �����´�.
#ifdef _SAFE_MEMORY
	SI32 GetSkillExp(SI32 skillunique)	{return clSkill[skillunique].siSkillExp ;}
#else
	SI32 GetSkillExp(SI32 skillunique)const{return clSkill[skillunique].siSkillExp ;}
#endif

	// Ư�� ��ų�� ������ ���Ѵ�. 
	SI32 GetSkillLevel(SI32 skillunique);
	// Ư�� ��ų�� ���跹���� ���Ѵ�. 
	SI32 GetSkillExpLevel(SI32 skillunique);
	// Ư�� ��ų�� �ѷ����� ���Ѵ�. 
	SI32 GetTotalSkillLevel(SI32 skillunique, SI32 sikind, SI32 level, cltItem* pclitemlist = NULL, SI32 id = 0);

	// [����] Ư�� ��ų�� �� ����ġ�� ���Ѵ�.
	SI32 GetTotalSkillExp(SI32 skilluinque);

	// ���� ������ ���� ��ų�� ���ߵǾ� �ִ��� Ȯ���Ѵ�. 
	bool ChcekUseWeaponSkill(SI32 type, cltItem* pclitemlist, SI32* preturnval);

	// 2003.10.23
	// ���� ������ ���� ������ �����´�. ( � ������ �����Ѱ��� �������Ʈ�� �˾ƾ� �ϹǷ�.. )
	bool GetMountSkillKind(SI32 type, cltItem* pclitemlist, SI32 *pMountSkill, SI32 *pSkillPoint );

	// �θ� ����� ������ ���Ѵ�. 
	UI32 GetParentSkillLevel(SI32 skillunique, cltItem* pclitemlist);

	// ������� ����� �����ϰ� ���׷��̵� ��ų ����� ������ ���� ���Ѵ�.
	bool GetRandSkillForUpgrade(cltSkillManager* pclskillmanager, cltItem* pclitemlist, SI32* pskillunique, SI32* pupgradeskilllevel);

	// [����] ������� �������� �ϳ��� ����, �ش� ��ų�� ���� ����ġ����Ʈ + 1 �� ��ŭ�� ��ǥ ����ġ�� ����Ʈ ���� ��� �κ����� �����ش�.
	bool GetRandSkillEXPupForUpgrade(cltSkillManager* pclskillmanager, cltItem* pclitemlist, SI32* pskillunique, SI32* increaseSkillExp);
};

// �������� ���� ����
class cltWeaponSkillInfo{
public:
	SI32	siUnique;					// ��ų ����ũ

	SI32	siLimitLevel;				// �ּ� ������ ����
	SI32	siBasicSkillLimitLevel;		// �⺻ ��ų ����

	SI32	siLimitSkillUnique;			// ���� ��ų
	SI32	siSkillLimitLevel;			// �ּ� ���� ��ų ����

	SI32	siNeedSkillPoint;			// ��ų ���µ� �ʿ��� ��ų����Ʈ

	GMONEY	siSkillCost;				// ��ų ���µ� ��� ���

	SI16	siApplyPercent;				// ��ų�ɷ�ġ ���� �ۼ�Ʈ
	
	// �� �������� �⺻������ �ش� �����϶��� ��ȿ�� ���������� �Ʒ� �������� �ٸ� ���⿩��	��� �� �ִ� �����̴�
	SI16	siHiddenSkillGrade;			// �� ��ų�� ��ܰ� ��ų�ΰ�(���� 1�� ����� 4�ܰ�, ���� 2�� ����� 5�ܰ�)
	SI16	siHiddenLimitLevel;			// �ּ� ���� ����
	SI16	siHiddenLimitSkillLevel;	// �ּ� ��ų ���� ����

	SI16	siItemUnique;				// ���� ��ų ��ﶧ �ʿ��� ������
	SI16	siItemNum;					// ���� ��ų ��ﶧ �ʿ��� ������ ����


	cltWeaponSkillInfo()
	{
		ZeroMemory( this, sizeof(cltWeaponSkillInfo) );
	}
};

class cltSkillInfo{
public:
	SI32 siUnique;			// ��ų ������ �ĺ���.
	SI32 siParentRef;		// �θ��� ���۷���. 

	SI32 siSkillType;
	SI32 siWeaponType;

	SI32 siMaxSkillLevel;	// �ִ� ��ų ����. 

	SI32 siSkillAtb;		// ����� �Ӽ�. 

	SI32 siBitMapIndex;		// ��Ʈ���� �ε���. 

	TCHAR szName[MAX_SKILL_NAME_LENGTH];
	TCHAR szCode[MAX_SKILL_NAME_LENGTH];
	TCHAR szSkillTitle[MAX_SKILL_NAME_LENGTH];

	SI32 siExplainUnique;		// ���� �ؽ�Ʈ ����ũ. 

	cltWeaponSkillInfo	** pclWeaponSkillInfo;

	cltSkillInfo(SI32 unique, SI32 skilltype, SI32 skillatb, TCHAR *code, TCHAR* name, SI32 maxskilllevel,
		SI32 parentref, SI32 bitmapindex, SI32 explainunique,SI32 weapontype );
	~cltSkillInfo();

	void MakeSkillTitle();

};

class cltSkillTypeInfo{
public:
	SI32 siSkillType;
	TCHAR szSkillCode[MAX_SKILL_TYPE_CODE_LENGTH];
	TCHAR szName[MAX_SKILL_TYPE_NAME_LENGTH];

	BOOL bShowData;

	cltSkillTypeInfo(SI32 skilltype, TCHAR* pskillcode, TCHAR* name,BOOL bshow );
	~cltSkillTypeInfo();
};

//--------------------------------------------------------------------------------------------------
// ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ����
//--------------------------------------------------------------------------------------------------
class cltWeaponSkillMaster
{
private:
	SI16 m_siApplyLevel;	// ���뷹��
	SI16 m_siApplyAbility;	// ����ɷ�	(SKILLMASTER ���߿� �ϳ���)
	SI32 m_siApplyValue;	// ���밪

public:
	cltWeaponSkillMaster();
	cltWeaponSkillMaster( SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue );

	~cltWeaponSkillMaster();

	void Init( void );

	void Set( SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue );
	SI32 GetValue( SI16 siApplyLevel, SI16 siApplyAbility );

	bool IsEmpty( void );

	SI16 GetApplyLevel( void );
	SI16 GetApplyAbility( void );
	SI32 GetApplyValue( void );

};

class cltWeaponSkillMasterManager
{
private:
	NSafeTArray<cltWeaponSkillMaster, SKILLMSTER_WEAPONTYPE_MAX> m_clWeaponSkillMaster;

public:
	cltWeaponSkillMasterManager();
	~cltWeaponSkillMasterManager();

	void Init( void );

	void LoadSkillMasterFile( void );

	SI32 GetApplyValue( SI32 siItemType, SI16 siSkillLevel, SI16 siApplyAbility );
	SI32 GetSkillUseWeaponFromItemType( SI32 siItemType );

	bool GetEmblemExplain( IN SI32 siItemType, IN SI32 siSkillLevel, OUT TCHAR* pszExplain, IN SI32 siTextSize );
	bool IsCanTakeEmblemWithNotice( IN SI32 siSkillUnique, IN SI32 siSkillLevel, OUT TCHAR* pszNotice, IN SI32 siTextSize );
	//bool GetEmblemGimgAndFontIndex( IN SI32 siItemType, IN SI32 siSkillLevel, OUT SI32* psiGimg, OUT SI32* psiFontIndex );
	UI08 GetEmblemIndex( IN SI32 siItemType, IN SI32 siSkillLevel );

private:
	SI32 ConvertTextToWeaponType( TCHAR* pszWeaponTypeText );
	SI32 ConvertTextToAbility( TCHAR* pszAbilityText );

	void Add( SI32 siWeaponType, SI16 siApplyLevel, SI16 siApplyAbility, SI32 siApplyValue );
	SI32 GetWeaponTypeFromItemType( SI32 siItemType );
	SI32 GetWeaponTypeFromSkillUnique( SI32 siSkillUnique );

	SI32 GetEmblemTextNum( SI32 siWeaponType );
	SI32 GetAbilityTextNum( SI32 siAbility );

};

//--------------------------------------------------------------------------------------------------
// ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ���� / ������� ����
//--------------------------------------------------------------------------------------------------

// level�� �ʿ��� ����ġ ��. (1���� �����Ѵ�.)
SI32 GetRequiredSkillExpForLevel(SI32 level);
BOOL LoadSkillExpData();
// ��� ����ġ�� �ٰŷ� ���跹���� ���Ѵ�. 
SI32 GetSkillLevelFromExp(SI32 exp);

// ��ų ������ ���� �䱸�Ǵ� ������ �Ҹ� ���Ѵ�. 
SI32 GetWasteDurability(SI32 skilllevel);

SI32 ConvertTextToSkillUnique( TCHAR* pszSkillUnique );
SI32 ConvertTextToSkillTypeUnique(TCHAR* pszSkillUnique);

#endif