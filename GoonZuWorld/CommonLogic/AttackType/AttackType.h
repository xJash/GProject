//---------------------------------
// 2003/6/11 ���°�
//---------------------------------

#ifndef _ATTACKTYPE_H
#define _ATTACKTYPE_H

#include <Directives.h>
//-------------------------------
// ���� Ÿ��
//-------------------------------
enum ATTACKTYPE
{
	ATTACKTYPE_NONE					= 0

	,ATTACKTYPE_HAND				= 1
	,ATTACKTYPE_SWORD						
	,ATTACKTYPE_SPEAR						
	,ATTACKTYPE_AXE							
	,ATTACKTYPE_STAFF						
	,ATTACKTYPE_STAFF1						
	,ATTACKTYPE_BOW							
	,ATTACKTYPE_GUN							
	,ATTACKTYPE_CAKE						
	
	,ATTACKTYPE_EGG							
	,ATTACKTYPE_CANNON						
	,ATTACKTYPE_SHELL						
	,ATTACKTYPE_CATFISH						
	,ATTACKTYPE_LADYBUGFAN					
	,ATTACKTYPE_SNOW						
	,ATTACKTYPE_SELFBOMB				// ���� 
	,ATTACKTYPE_MADOGHOSTFIRE				
	,ATTACKTYPE_JAPANHEADER					
	,ATTACKTYPE_TOHANG						
	
	,ATTACKTYPE_MAGIC						
	,ATTACKTYPE_POISONSTATUS			// �ߵ��Ǿ� �ִ� ���¿����� Ÿ�̸� Ÿ��. 
	,ATTACKTYPE_SKULLBATFIRE				
	,ATTACKTYPE_FIREGOBLIN					
	,ATTACKTYPE_CASTLECANNON				
	,ATTACKTYPE_POISON					// �ߵ��� ��ų �� �ִ� ��. 
	,ATTACKTYPE_ICE							
	,ATTACKTYPE_KNIFE						
	,ATTACKTYPE_GREENFIRE						
	,ATTACKTYPE_BLACKINK					

	,ATTACKTYPE_BOOMERANG				// �θ޶� 
	,ATTACKTYPE_WINDBLADE				// ���Ż
	,ATTACKTYPE_SHELLFISHBOMB			// ��������
	,ATTACKTYPE_TREEMON					// ������ - ��¥�Ѿ� ���
	,ATTACKTYPE_VINE					// �ܴ����� - ��¥�Ѿ� ���
	,ATTACKTYPE_GHOSTFIRE				// ���ɱͽ�
	,ATTACKTYPE_SIMTORYONG				// �����
	,ATTACKTYPE_KINGCUTTLEFISH			// ��տ�����
	,ATTACKTYPE_CRANE					// ź������
	,ATTACKTYPE_MONKEY					// ź��������

	,ATTACKTYPE_CURSEDEFENSE			// ���� ����
	,ATTACKTYPE_CURSEMOVESPEED			// ���ݷ� ���� 
	,ATTACKTYPE_BUTCHER					// ���ּ�����
	,ATTACKTYPE_STONEOLDMAN				// ���ϸ���
	,ATTACKTYPE_KINGCRAB				// ��ռҶ��
	,ATTACKTYPE_FIREARROW				// ��ȭ��
	,ATTACKTYPE_LOBSTER					// �������
	,ATTACKTYPE_DEADMESSENGER			// ���»���
	,ATTACKTYPE_MASKMONK				// ��Ż
	,ATTACKTYPE_PERSONCANNON			// ������ź

	,ATTACKTYPE_CANNON_MAGIC			// �ֹ��� ����
	,ATTACKTYPE_HEROSWORD				// ��ȯ������ ��
	,ATTACKTYPE_STAFF2						
	,ATTACKTYPE_BOW1						
	,ATTACKTYPE_GUN1						
	,ATTACKTYPE_FOAM					// �Ա��� ��ǰ
	,ATTACKTYPE_FIREBALL				// �Ϲ� ���� ȭ���ӱ�
	,ATTACKTYPE_MORTAL					// ȸ�������� ������ ����
	,ATTACKTYPE_WATERARROW				// ��ȭ��
	,ATTACKTYPE_STAFFWIND				// ����� ��ǳ

	,ATTACKTYPE_FLYVINE					// ���ư��� ����
	,ATTACKTYPE_MAGICFIRESTATUS			// �ҿ� Ÿ�鼭 �޴� ����
	,ATTACKTYPE_MAGICFIREBURN			// �� �¿�� ����
	,ATTACKTYPE_SKELLFISH				// ���ư��� ������
	,ATTACKTYPE_FROZEN					// ������ ��
	,ATTACKTYPE_ICESTONE				// ������ ����
	,ATTACKTYPE_NEW_STAFF2				// �����̼�(4���̻�)
	,ATTACKTYPE_NEW_BOW1				// Ȱ(4���̻�)
	,ATTACKTYPE_NEW_GUN1				// ��(4���̻�)
	,ATTACKTYPE_ENERGYARROW				// ���ȱ�

	,ATTACKTYPE_SPEAR_MANA				// ����
	,ATTACKTYPE_BLACKBOSS				// ���� ���� �θ�
	,ATTACKTYPE_OCTOPUS					// ����
	,ATTACKTYPE_OTOHIME					// ����
	,ATTACKTYPE_BLACKSPIDER				// ��Ź�
	,ATTACKTYPE_EVILEYE					// �̺����
	,ATTACKTYPE_FROZENSORCERER			// ��
	,ATTACKTYPE_CANNONMOL				// ĳ���(����䱫)
	,ATTACKTYPE_PRIEST					// Ÿ��������
	,ATTACKTYPE_MINEGIRL				// ź���ҳ�

	,ATTACKTYPE_GREENTURTLE				// �ʿ��ź�
	,ATTACKTYPE_MAGICALRACCOON			// �����ø���
	,ATTACKTYPE_MAMARACCOON				// ��������
	,ATTACKTYPE_RACCOONTOWER			// ����Ÿ��
	,ATTACKTYPE_CHICKENBIG				// �մޱ�
	,ATTACKTYPE_MOONBLADE				// �򰭰���
	,ATTACKTYPE_EMPERORARCHER			// �밻��
	,ATTACKTYPE_NINJAMAN				// ���ڳ�  - ���Ÿ�.
	,ATTACKTYPE_PIRATEARCHER			// �������ذ�ú�
	,ATTACKTYPE_EMPERORMASTER			// �밻��

	,ATTACKTYPE_GREATWALLSOLDIER		// ������
	,ATTACKTYPE_GREATWALLMAGICIAN		// �Ӹ���
	,ATTACKTYPE_CATRANGE				// ����� ���Ǹ�
	
	,ATTACKTYPE_GREATWALLSPIDER			// ����
	,ATTACKTYPE_BEARTANG				// ����
	,ATTACKTYPE_SUPERBEARTANG			// ��������

	,ATTACKTYPE_HALLOWEENGHOST			// �ҷ���
	,ATTACKTYPE_CHRISTMASRANGE			// ũ�������� ���Ÿ�.
	,ATTACKTYPE_GREATWALLASURA			// ��������� �Ƽ��� - �Ҳ� ���.
	,ATTACKTYPE_FIGHTINGMENRANGE		// �ųʽ��Ǹ�
	,ATTACKTYPE_FROZENQUEEN				// ������ ��.
	,ATTACKTYPE_FAIRYRANGE				// �������Ǹ�(��)
	,ATTACKTYPE_SNOWQUEEN				// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
	,ATTACKTYPE_CLOWN					// �Ȱ��̱� - �����

	//----------------------------------------------------------------
	//
	// �� ���� �߰��� �ּ���
	//
	//----------------------------------------------------------------
	,MAX_ATTACKTYPE_NUMBER
};

// ��ȯ�� ���� Ÿ��
#define SUMMON_EQUIPTYPE_NONE					0	// ����Ÿ���� ����(��� ����Ұ���)
#define SUMMON_EQUIPTYPE_FARDISTANCE			1	// �ٰŸ� ����
#define SUMMON_EQUIPTYPE_LONGDISTANCE			2	// ���Ÿ� ����
/*
#define MAX_ATTACKTYPE_NUMBER					100

//-------------------------------
// ���� Ÿ��
//-------------------------------
#define ATTACKTYPE_HAND							1
#define ATTACKTYPE_SWORD						2
#define ATTACKTYPE_SPEAR						3
#define ATTACKTYPE_AXE							4
#define ATTACKTYPE_STAFF						5
#define ATTACKTYPE_STAFF1						6
#define ATTACKTYPE_BOW							7
#define ATTACKTYPE_GUN							8
#define ATTACKTYPE_CAKE							9
#define ATTACKTYPE_EGG							10
#define ATTACKTYPE_CANNON						11
#define ATTACKTYPE_SHELL						12
#define ATTACKTYPE_CATFISH						13
#define ATTACKTYPE_LADYBUGFAN					14
#define ATTACKTYPE_SNOW							15
#define ATTACKTYPE_SELFBOMB						16		// ���� 
#define ATTACKTYPE_MADOGHOSTFIRE				17
#define ATTACKTYPE_JAPANHEADER					18
#define ATTACKTYPE_TOHANG						19
#define ATTACKTYPE_MAGIC						20
#define ATTACKTYPE_POISONSTATUS					21		// �ߵ��Ǿ� �ִ� ���¿����� Ÿ�̸� Ÿ��. 
#define ATTACKTYPE_SKULLBATFIRE					22
#define ATTACKTYPE_FIREGOBLIN					23
#define ATTACKTYPE_CASTLECANNON					24
#define ATTACKTYPE_POISON						25		// �ߵ��� ��ų �� �ִ� ��. 
#define ATTACKTYPE_ICE							26
#define ATTACKTYPE_KNIFE						27
#define ATTACKTYPE_GREENFIRE					28	
#define ATTACKTYPE_BLACKINK						29
#define ATTACKTYPE_BOOMERANG					30		// �θ޶� 
#define ATTACKTYPE_WINDBLADE					31		// ���Ż
#define ATTACKTYPE_SHELLFISHBOMB				32		// ��������
#define ATTACKTYPE_TREEMON						33		// ������ - ��¥�Ѿ� ���
#define ATTACKTYPE_VINE							34		// �ܴ����� - ��¥�Ѿ� ���
#define ATTACKTYPE_GHOSTFIRE					35		// ���ɱͽ�
#define ATTACKTYPE_SIMTORYONG					36		// �����
#define ATTACKTYPE_KINGCUTTLEFISH				37		// ��տ�����
#define ATTACKTYPE_CRANE						38		// ź������
#define ATTACKTYPE_MONKEY						40		// ź��������
#define ATTACKTYPE_CURSEDEFENSE					41		// ���� ����
#define ATTACKTYPE_CURSEMOVESPEED				42		// ���ݷ� ���� 
#define ATTACKTYPE_BUTCHER						43		// ���ּ�����
#define ATTACKTYPE_STONEOLDMAN					44		// ���ϸ���
#define ATTACKTYPE_KINGCRAB						45		// ��ռҶ��
#define ATTACKTYPE_FIREARROW					46		// ��ȭ��
#define ATTACKTYPE_LOBSTER						47		// �������
#define ATTACKTYPE_DEADMESSENGER				48		// ���»���
#define ATTACKTYPE_MASKMONK						49		// ��Ż
#define ATTACKTYPE_PERSONCANNON					50		// ������ź
#define ATTACKTYPE_CANNON_MAGIC					51		// �ֹ��� ����
#define ATTACKTYPE_HEROSWORD					52		// ��ȯ������ ��

#define ATTACKTYPE_STAFF2						53
#define ATTACKTYPE_BOW1							54
#define ATTACKTYPE_GUN1							55

#define ATTACKTYPE_FOAM							56		// �Ա��� ��ǰ
#define ATTACKTYPE_FIREBALL						57		// �Ϲ� ���� ȭ���ӱ�
#define ATTACKTYPE_MORTAL						58		// ȸ�������� ������ ����
#define ATTACKTYPE_WATERARROW					59		// ��ȭ��

#define ATTACKTYPE_STAFFWIND					60		// ����� ��ǳ

#define ATTACKTYPE_FLYVINE						61		// ���ư��� ����

#define ATTACKTYPE_MAGICFIRESTATUS				62		// �ҿ� Ÿ�鼭 �޴� ����
#define ATTACKTYPE_MAGICFIREBURN				63		// �� �¿�� ����

#define ATTACKTYPE_SKELLFISH					64		// ���ư��� ������

#define ATTACKTYPE_FROZEN						65		// ������ ��
#define ATTACKTYPE_ICESTONE						66		// ������ ����

#define ATTACKTYPE_NEW_STAFF2					67	// �����̼�(4���̻�)
#define ATTACKTYPE_NEW_BOW1						68	// Ȱ(4���̻�)
#define ATTACKTYPE_NEW_GUN1						69	// ��(4���̻�)

#define ATTACKTYPE_ENERGYARROW					70 // ���ȱ�
#define ATTACKTYPE_SPEAR_MANA					71 // ����

#define ATTACKTYPE_BLACKBOSS					72 // ���� ���� �θ�
#define ATTACKTYPE_OCTOPUS						73		// ����
#define ATTACKTYPE_OTOHIME						74		// ����

#define ATTACKTYPE_BLACKSPIDER					75	// ��Ź�
#define ATTACKTYPE_EVILEYE						76	// �̺����

#define ATTACKTYPE_FROZENSORCERER				77	// ��
#define ATTACKTYPE_CANNONMOL					78	// ĳ���(����䱫)

#define	ATTACKTYPE_PRIEST						79	// Ÿ��������

#define ATTACKTYPE_MINEGIRL						80	// ź���ҳ�

#define ATTACKTYPE_GREENTURTLE					81	// �ʿ��ź�
#define	ATTACKTYPE_MAGICALRACCOON				82	// �����ø���
#define ATTACKTYPE_MAMARACCOON					83	// ��������
#define ATTACKTYPE_RACCOONTOWER					84	// ����Ÿ��
#define	ATTACKTYPE_CHICKENBIG					85	// �մޱ�
#define ATTACKTYPE_MOONBLADE					86  // �򰭰���
#define ATTACKTYPE_EMPERORARCHER				87	// �밻��
#define ATTACKTYPE_NINJAMAN						88	// ���ڳ�  - ���Ÿ�.
#define ATTACKTYPE_PIRATEARCHER					89	// �������ذ�ú�
*/

//#define MAX_ATTACKTYPE_NUMBER					80
//-------------------------------
// ����Ÿ���� �Ӽ�
//-------------------------------
// ���� ����� ���� �Ӽ�. 
#define ATTACKTYPE_ATB_RANGE1						0x1		// �ֺ����� �˻��ؼ� ��ǥ���� �����Ѵ�. 		
#define ATTACKTYPE_ATB_RANGE2						0x2		// ��ǥ���� ������ �´´�. 
#define ATTACKTYPE_ATB_RANGE3						0x4		// ���� �������� ���� ��� �����Ѵ�. 	

// ���� ȿ���� ���� �Ӽ�. 
#define ATTACKTYPE_ATB_PHYSICS						0x1
#define ATTACKTYPE_ATB_MAGIC						0x2


// ��Ÿ �Ӽ�. 
#define ATTACKTYPE_ATB_MINRANGE						0x2
#define ATTACKTYPE_ATB_PULL							0x4			// �ǰݽ� �ڷ� �и�. 
#define ATTACKTYPE_ATB_PALSY						0x8			// �ǰݽ� ���� ȿ��. 
#define ATTACKTYPE_ATB_CRITICAL						0x10		// �ʻ�Ⱑ �۵��ϴ°�. 

//---------------------------------
// cltAttackTargetList
//---------------------------------
#define MAX_ATTACK_TARGET_LIST_NUMBER				20

class cltAttackDamageInfo{
public:
	SI32 siAttackType;
	SI32 siDamage;
	SI32 siMagicKind;

	cltAttackDamageInfo()
	{
		Init();
	}
	cltAttackDamageInfo(SI32 attacktype, SI32 damage, SI32 magickind)
	{
		siAttackType	= attacktype;
		siDamage		= damage;
		siMagicKind		= magickind;
	}
	void Init()
	{
		siAttackType	= 0;
		siDamage		= 0;
		siMagicKind		= 0;

	}

	void Set(cltAttackDamageInfo* pcldamageinfo)
	{
		siAttackType	= pcldamageinfo->siAttackType;
		siDamage		= pcldamageinfo->siDamage;
		siMagicKind		= pcldamageinfo->siMagicKind;
	}

};

class cltAttackTargetList{
private:
	SI32 siIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_ATTACK_TARGET_LIST_NUMBER>					siID;
	NSafeTArray<cltAttackDamageInfo, MAX_ATTACK_TARGET_LIST_NUMBER>		clDamageInfo;
#else
	SI32 siID[MAX_ATTACK_TARGET_LIST_NUMBER];
	cltAttackDamageInfo clDamageInfo[MAX_ATTACK_TARGET_LIST_NUMBER];
#endif

public:
	cltAttackTargetList();
	BOOL IsInList(SI32 id);
	void Push(SI32 id, cltAttackDamageInfo* pcldamageinfo);
	BOOL Pop(SI32* pid, cltAttackDamageInfo* pcldamageinfo);

};

//---------------------------------
// ���� Ÿ�� ���� 
//---------------------------------
class cltAttackTypeInfo{
public:
	TCHAR	szAttackTypeCode[60];

	SI32 siAttackType;
	SI32 siBulletUnique;		// �ҷ�
	SI32 siFlag1;				// ���� ������ ���� ���� 
	SI32 siFlag2;				// ������ ����/���� �Ӽ��� ���� ����. 
	SI32 siFlag3;				// ��Ÿ ����. 

	cltAttackTypeInfo(TCHAR* szattacktypecode, SI32 attacktype, SI32 bulletunique, SI32 flag1, SI32 flag2, SI32 flag3);

	~cltAttackTypeInfo();

	SI32 GetFlagRange()const{return siFlag1;}
	SI32 GetFlagPower()const{return siFlag2;}
	SI32 GetFlagEtc()const{return siFlag3;}
};

//----------------------------------
// ���� Ÿ�� ���� ������. 
//----------------------------------
class cltAttackTypeInfoManager{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltAttackTypeInfo*, MAX_ATTACKTYPE_NUMBER>	pclAttackTypeInfo;
#else
	cltAttackTypeInfo *pclAttackTypeInfo[MAX_ATTACKTYPE_NUMBER];
#endif

	cltAttackTypeInfoManager();
	~cltAttackTypeInfoManager();

	// ���� Ÿ���� �߰��Ѵ�. 
	BOOL Add(SI32 attacktype, TCHAR* szattacktypecode, SI32 bulletunique, SI32 flag1, SI32 flag2, SI32 flag3);

	// ���� Ÿ���� �Ѿ� ������ ���Ѵ�.
	SI32 GetBulletUnique(SI32 attacktype);

	// Code�� �ٰŷ� AttackType�� ã�´�.
	SI32 FindAttackTypeFromCode(TCHAR* code);
	
	// ���� Ÿ���� �Ӽ��� Ȯ���Ѵ�. 
	bool IsAtb(SI32 attacktype, SI32 atb);


};

#endif
