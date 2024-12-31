//---------------------------------
// 2003/7/4 ���°�
//---------------------------------
#ifndef _BULLET_H
#define _BULLET_H

#include <CommonHeader.h>
#include "..\Map\Map.h"
#include <TSpr.h>

#define MAX_SHOOT_RANGE							200     

//------------------------------------------------------------------------------------------------
// �Ѿ��� �۵� 
//------------------------------------------------------------------------------------------------
#define ORDER_BULLET_MOVE						1
#define ORDER_BULLET_EXP     					2

//------------------------------------------------------------------------------------------------
// �Ѿ��� �ִϸ��̼� ����. 
//------------------------------------------------------------------------------------------------
#define ANI_BULLET_MOVE							1
#define ANI_BULLET_WAIT							2



//------------------------------------------------------------------------------------------------
// �Ѿ� ���� 
//------------------------------------------------------------------------------------------------
// [����] ���� define�� enum���� ����

enum BULLETKIND
{
	BULLETKIND_NONE					= 0	// �ƹ��͵� �ƴ�

	,BULLETKIND_ARROW				= 1
	,BULLETKIND_GUN						
	,BULLETKIND_CAKE					
	,BULLETKIND_EGG						
	,BULLETKIND_CANNONBALL				
	,BULLETKIND_TURTLEBACKSHELL			
	,BULLETKIND_CATFISH					
	,BULLETKIND_LADYBUGFAN				
	,BULLETKIND_SNOW					
	,BULLETKIND_STAFF1					

	,BULLETKIND_MADOGHOSTFIRE			
	,BULLETKIND_JAPANHEADER				
	,BULLETKIND_TOHANG					
	,BULLETKIND_SKULLBATFIRE			
	,BULLETKIND_FIREGOBLIN				
	,BULLETKIND_CASTLECANNONBALL		
	,BULLETKIND_SELFBOMB				
	,BULLETKIND_KNIFE					
	,BULLETKIND_GREENFIRE				
	,BULLETKIND_BLACKINK				

	,BULLETKIND_WINDBLADE				
	,BULLETKIND_SHELLFISHBOMB			
	,BULLETKIND_MAGICFIREBALL			
	,BULLETKIND_MAGICBIGWIND			
	,BULLETKIND_MAGICPOISON				
	,BULLETKIND_MAGICICE				
	,BULLETKIND_MAGICLIGHTINGFIST		
	,BULLETKIND_BOOMERANG				// �Ӽ��� �θ޶��� �ϳ� �������.
	,BULLETKIND_TREEMON					// ������ - ��¥�Ѿ� ���(SUNKEN)
	,BULLETKIND_VINE					// �ܴ����� - ��¥�Ѿ� ���(SUNKEN)

	,BULLETKIND_GHOSTFIRE				// ���ɱͽ�
	,BULLETKIND_SIMTORYONG				// �����
	,BULLETKIND_KINGCUTTLEFISH			// ��տ�����
	,BULLETKIND_CRANE					// ź������
	,BULLETKIND_SELFBOMBWHALE			// ���� ����
	,BULLETKIND_MONKEYDRILL				// ź��������
	,BULLETKIND_MAGICCURSEDEFENSE		// ����   ���� �Ѿ� 
	,BULLETKIND_MAGICCURSEMOVESPEED		// �̵��ӵ� ���� �Ѿ�
	,BULLETKIND_BUTCHER					// ���ּ�����
	,BULLETKIND_STONEOLDMAN				// ���ϸ���

	,BULLETKIND_MAGICTHROWKNIFE_RIGHT	// ǥâ���� ���� �Ѿ� ������
	,BULLETKIND_MAGICTHROWKNIFE_LEFT	// ǥâ���� ���� �Ѿ� ����
	,BULLETKIND_KINGCRAB				// ��ռҶ��
	,BULLETKIND_FIREARROW				// ��ȭ��
	,BULLETKIND_LOBSTER					// �������
	,BULLETKIND_DEADMESSENGER			// ���»���
	,BULLETKIND_MASKMONK				// ��Ż
	,BULLETKIND_PERSONCANNON			// ���δ���
	,BULLETKIND_CANNON_MAGIC			// �ֹ��� ����
	,BULLETKIND_BOW_SCROLL				// �ü�����(1��) �߷��� ��

	,BULLETKIND_GUN_SCROLL				// �ü�����(1��) �߷��� ��
	,BULLETKIND_STAFF_SCROLL			// �ü�����(1��) �߷��� ��
	,BULLETKIND_FOAM_FIRE				// �Ա���
	,BULLETKIND_FIREBALL				// �Ϲݰ���
	,BULLETKIND_MORTAL					// �ٰŸ� ������ �� �ֺ��η� ������ ��ó�� ���̰� �� - ȸ��������
	,BULLETKIND_WATERARROW				// ��ȭ��
	,BULETKIND_MAGICPALMWIND			// ����� ��ǳ����
	,BULLETKIND_STAFFWIND				// ����� ��ǳ
	,BULLETKIND_FLYVINE					// ���ư��� ����(����?)
	,BULLETKIND_MAGICSKELLGHOST			// ���ư��� �ذ�����

	,BULLETKIND_SKELLFISH				// ���ư��� ������
	,BULLETKIND_MAGICFROZEN				// ���� ���� ����
	,BULLETKIND_ICESTONE				// ������ ����
	,BULLETKIND_TWINSPEAR				// �糯â
	,BULLETKIND_NORTHWIND				// ��ǳ
	,BULLETKIND_NEW_BOW_SCROLL			// �ü�����(2��) �߷��� ��
	,BULLETKIND_NEW_GUN_SCROLL			// �ü�����(2��) �߷��� ��
	,BULLETKIND_NEW_STAFF_SCROLL		// �ü�����(2��) �߷��� ��
	,BULLETKIND_FIRESTORM				
	,BULLETKIND_ENERGYARROW				// ���ȱ�
	,BULLETKIND_SPEAR_MANA				// ���� �Ϲ� ����
	,BULLETKIND_SPEAR_DRAGON			// ���� ���� ����

	,BULLETKIND_BLACKBOSS				// ���� ���� �θ�
	,BULLETKIND_OCTOPUS					// ����
	,BULLETKIND_OTOHIME					
	,BULLETKIND_BLACKSPIDER				// ��Ź�
	,BULLETKIND_EVILEYE					// �̺����
	,BULLETKIND_GARGOYLE				// ������ ����
	,BULLETKIND_CERBERUS				// �̺��ν� ����
	,BULLETKIND_FROZENSORCERER			// ������ �Ҽ��� �Ϲ�
	,BULLETKIND_MARIONETTE				
	,BULLETKIND_FROKEN					// ���� ������

	,BULLETKIND_ICEHOUND				// ���̽��Ͽ��
	,BULLETKIND_FROZENKNIGHT			// ������ ����Ʈ
	,BULLETKIND_FROZENSORCERER_MAGIC	// ������ �Ҽ��� ����
	,BULLETKIND_NINJAPANDA				// �����Ǵ� ����
	,BULLETKIND_RACCOONDOG				// �а��ʱ��� ����
	,BULLETKIND_BOSSMONKEY				// ���� ������ ����
	,BULLETKIND_CANNONMOL				// ĳ���(����䱫)
	,BULLETKIND_BLOODBAT				// ��������
	,BULLETKIND_WEREWOLF				// �����ΰ�
	,BULLETKIND_DEVILOUS				// ��������

	,BULLETKIND_GANGSI					// ����
	,BULLETKIND_PRIEST					// Ÿ��������
	,BULLETKIND_HARPY					// Ÿ��������
	,BULLETKIND_GIRAFFE					// �⸰~
	,BULLETKIND_PAPAGOBLIN				// �⸰~
	,BULLETKIND_MINEGIRL				// ź���ҳ�
	,BULLETKIND_GREENTURTLE				// �ʿ��ź�
	,BULLETKIND_MAGICALRACCOON			// �����ø���
	,BULLETKIND_MAMARACCOON				// ��������
	,BULLETKIND_RACCOONTOWER			// ����Ÿ��

	,BULLETKIND_CHICKENBIG				// �մޱ�
	,BULLETKIND_MOONBLADE				// �򰭰���
	,BULLETKIND_EMPERORARCHER			// �밻��
	,BULLETKIND_NINJAMAN				// ������(��)
	,BULLETKIND_PIRATEARCHER			// �������ذ�ú�(ȭ��)
	,BULLETKIND_PIRATEARCHER_MAGIC		// �������ذ�ú�(����)
	,BULLETKIND_PIRATESOLDIER			// �������ذ񺴻�
	,BULLETKIND_EMPERORCAVALRY			// �밻����
	,BULLETKIND_EMPERORMASTER			// �밻��
	,BULLETKIND_GREATWALLSOLDIER		// ������

	,BULLETKIND_GREATWALLMAGICIAN		// �Ӹ��� - �Ӹ�������
	,BULLETKIND_CATRANGE				// ��í ����� (���Ÿ�)

	,BULLETKIND_EMPERORWARRIOR			// �񷽺���
	,BULLETKIND_GREATWALLSPIDER			// ����
	,BULLETKIND_GREATWALLTWINHEAD		// �θӸ�
	,BULLETKIND_BEARTANG				// ���� - ��������
	,BULLETKIND_BEARTANG_MAGIC			// ���� - ��������
	,BULLETKIND_SUPERBEARTANG			// �������� - ��������
	,BULLETKIND_SUPERBEARTANG_MAGIC		// �������� - ��������
	,BULLETKIND_HALLOWEENGHOST			// �ҷ���
	,BULLETKIND_TRIPLEDEATH_MAGIC		// Ȱ ����(Ʈ���õ���)
	,BULLETKIND_COSMOSRABBIT			// �����䳢 ���Ÿ�����
	,BULLETKIND_CHRISTMASRANGE			// ũ�������� ���Ÿ�����
	,BULLETKIND_RUDOLPHPET				// �絹�� ��ȯ�� - ������ź
	,BULLETKIND_GREATWALLASURA			// ��������� �Ƽ��� - �Ҳ� ���.
	,BULLETKIND_AMBERSAURUS				// �Ҿ�������� �������罺
	,BULLETKIND_ROLLINGSTEGO			// �Ҿ�������� �Ѹ����װ�
	,BULLETKIND_FIGHTINGMENRANGE		// ���Ÿ����� ���Ǹ� - �ų�
	,BULLETKIND_FAIRYRANGE				// �������Ǹ�(��) - ���Ÿ�
	,BULLETKIND_SNOWQUEEN				// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ

	,BULLETKIND_FLAMEBUSTER				// [����] ��ų�� 
	,BULLETKIND_FLAMEWHIRL				// [����] ��ų�� 
	,BULLETKIND_WETFOG					// [����] ��ų�� 
	,BULLETKIND_SLING					// [����] ��ų�� 
	,BULLETKIND_WINDCUTER				// [����] ��ų�� 

	,BULLETKIND_CLOWN					// [���] �Ȱ��̱� - �����
	,BULLETKIND_CLOWN_MAGIC				// [���] �Ȱ��̱� - �����(����)
	,BULLETKIND_BOUQUET					// [���] �Ȱ��ź� ����(���ɴ�����)

	//**************************************************************//
	//
	// [����] �� �߰��� �� ���� ���ּ���
	//
	//**************************************************************//
	,MAX_BULLET_KIND_NUMBER
};
/*
#define MAX_BULLET_KIND_NUMBER       			120

#define BULLETKIND_ARROW						1
#define BULLETKIND_GUN							2
#define BULLETKIND_CAKE							3
#define BULLETKIND_EGG							4
#define BULLETKIND_CANNONBALL					6
#define BULLETKIND_TURTLEBACKSHELL				7
#define BULLETKIND_CATFISH						8
#define BULLETKIND_LADYBUGFAN					9
#define BULLETKIND_SNOW							10
#define BULLETKIND_STAFF1						11
#define BULLETKIND_MADOGHOSTFIRE				12
#define BULLETKIND_JAPANHEADER					13
#define BULLETKIND_TOHANG						14
#define BULLETKIND_SKULLBATFIRE					15
#define BULLETKIND_FIREGOBLIN					16
#define BULLETKIND_CASTLECANNONBALL				17
#define BULLETKIND_SELFBOMB						18
#define BULLETKIND_KNIFE						19
#define BULLETKIND_GREENFIRE					20
#define BULLETKIND_BLACKINK						21
#define BULLETKIND_WINDBLADE					22
#define BULLETKIND_SHELLFISHBOMB				23

#define BULLETKIND_MAGICFIREBALL				24
#define BULLETKIND_MAGICBIGWIND					25
#define BULLETKIND_MAGICPOISON					26
#define BULLETKIND_MAGICICE						27
#define BULLETKIND_MAGICLIGHTINGFIST			28

#define BULLETKIND_BOOMERANG					29 // �Ӽ��� �θ޶��� �ϳ� �������.

#define BULLETKIND_TREEMON						30 // ������ - ��¥�Ѿ� ���(SUNKEN)
#define BULLETKIND_VINE							31 // �ܴ����� - ��¥�Ѿ� ���(SUNKEN)

#define BULLETKIND_GHOSTFIRE					32 // ���ɱͽ�
#define BULLETKIND_SIMTORYONG					33 // �����
#define BULLETKIND_KINGCUTTLEFISH				34 // ��տ�����
#define BULLETKIND_CRANE						35 // ź������
#define BULLETKIND_SELFBOMBWHALE				36 // ���� ����
#define BULLETKIND_MONKEYDRILL					37 // ź��������

#define BULLETKIND_MAGICCURSEDEFENSE			38 // ����   ���� �Ѿ� 
#define BULLETKIND_MAGICCURSEMOVESPEED			39 // �̵��ӵ� ���� �Ѿ�

#define BULLETKIND_BUTCHER						40 // ���ּ�����
#define BULLETKIND_STONEOLDMAN					41 // ���ϸ���

#define BULLETKIND_MAGICTHROWKNIFE_RIGHT		42 // ǥâ���� ���� �Ѿ� ������
#define BULLETKIND_MAGICTHROWKNIFE_LEFT			43 // ǥâ���� ���� �Ѿ� ����

#define BULLETKIND_KINGCRAB						44 // ��ռҶ��

#define BULLETKIND_FIREARROW					45 // ��ȭ��

#define BULLETKIND_LOBSTER						46 // �������
#define BULLETKIND_DEADMESSENGER				47 // ���»���
#define BULLETKIND_MASKMONK						48 // ��Ż

#define BULLETKIND_PERSONCANNON					49 // ���δ���
#define BULLETKIND_CANNON_MAGIC					50 // �ֹ��� ����

#define BULLETKIND_BOW_SCROLL					51 // �ü�����(1��) �߷��� ��
#define BULLETKIND_GUN_SCROLL					52 // �ü�����(1��) �߷��� ��
#define BULLETKIND_STAFF_SCROLL					53 // �ü�����(1��) �߷��� ��

#define BULLETKIND_FOAM_FIRE					54 // �Ա���
#define BULLETKIND_FIREBALL						55 // �Ϲݰ���
#define BULLETKIND_MORTAL						56 // �ٰŸ� ������ �� �ֺ��η� ������ ��ó�� ���̰� �� - ȸ��������

#define BULLETKIND_WATERARROW					57 // ��ȭ��

#define BULETKIND_MAGICPALMWIND					58 // ����� ��ǳ����
#define BULLETKIND_STAFFWIND					59 // ����� ��ǳ

#define BULLETKIND_FLYVINE						60 // ���ư��� ����(����?)

#define BULLETKIND_MAGICSKELLGHOST				61 // ���ư��� �ذ�����

#define BULLETKIND_SKELLFISH					62 // ���ư��� ������

#define BULLETKIND_MAGICFROZEN					63 // ���� ���� ����
#define BULLETKIND_ICESTONE						64 // ������ ����
#define BULLETKIND_TWINSPEAR					65 // �糯â

#define BULLETKIND_NORTHWIND					66 // ��ǳ

#define BULLETKIND_NEW_BOW_SCROLL				67 // �ü�����(2��) �߷��� ��
#define BULLETKIND_NEW_GUN_SCROLL				68 // �ü�����(2��) �߷��� ��
#define BULLETKIND_NEW_STAFF_SCROLL				69 // �ü�����(2��) �߷��� ��

#define BULLETKIND_FIRESTORM					70
#define BULLETKIND_ENERGYARROW					71 // ���ȱ�

#define BULLETKIND_SPEAR_MANA					72 // ���� �Ϲ� ����
#define BULLETKIND_SPEAR_DRAGON					73 // ���� ���� ����

#define BULLETKIND_BLACKBOSS					74 // ���� ���� �θ�
#define BULLETKIND_OCTOPUS						75 // ����

#define BULLETKIND_OTOHIME						76

#define BULLETKIND_BLACKSPIDER					77	// ��Ź�
#define BULLETKIND_EVILEYE						78	// �̺����

#define BULLETKIND_GARGOYLE						79	// ������ ����
#define BULLETKIND_CERBERUS						80	// �̺��ν� ����

#define BULLETKIND_FROZENSORCERER				81	// ������ �Ҽ��� �Ϲ�
#define BULLETKIND_MARIONETTE					82
#define BULLETKIND_FROKEN						83	// ���� ������
#define BULLETKIND_ICEHOUND						84	// ���̽��Ͽ��
#define BULLETKIND_FROZENKNIGHT					85	// ������ ����Ʈ
#define BULLETKIND_FROZENSORCERER_MAGIC			86	// ������ �Ҽ��� ����

#define BULLETKIND_NINJAPANDA					87	// �����Ǵ� ����
#define BULLETKIND_RACCOONDOG					88	// �а��ʱ��� ����

#define BULLETKIND_BOSSMONKEY					89	// ���� ������ ����
#define BULLETKIND_CANNONMOL					90	// ĳ���(����䱫)

#define BULLETKIND_BLOODBAT						91	// ��������
#define BULLETKIND_WEREWOLF						92	// �����ΰ�
#define BULLETKIND_DEVILOUS						93	// ��������
#define	BULLETKIND_GANGSI						94	// ����
#define BULLETKIND_PRIEST						95	// Ÿ��������

#define BULLETKIND_HARPY						96	// Ÿ��������
#define BULLETKIND_GIRAFFE						97	// �⸰~

#define BULLETKIND_PAPAGOBLIN						98	// �⸰~

#define BULLETKIND_MINEGIRL						99 // ź���ҳ�

#define BULLETKIND_GREENTURTLE						100 // �ʿ��ź�
#define BULLETKIND_MAGICALRACCOON				101	// �����ø���
#define	BULLETKIND_MAMARACCOON					102 // ��������
#define	BULLETKIND_RACCOONTOWER					103	// ����Ÿ��
#define BULLETKIND_CHICKENBIG					104 // �մޱ�
#define BULLETKIND_MOONBLADE					105 // �򰭰���
#define BULLETKIND_EMPERORARCHER				106 // �밻��
#define BULLETKIND_NINJAMAN						107 // ������(��)
#define BULLETKIND_PIRATEARCHER					108 // �������ذ�ú�
#define BULLETKIND_PIRATESOLDIER				109 // �������ذ񺴻�


//#define MAX_BULLET_KIND_NUMBER       			80
*/
//-----------------------------------------------------
// �Ѿ� �Ӽ� 
//-----------------------------------------------------
#define BLTATB_RANGE1				0x1 
#define BLTATB_RANGE2				0x2 
#define BLTATB_RANGE3				0x4 
#define BLTATB_FRAGMENT				0x8
#define BLTATB_CURVE				0x10			// � ź�� �Ѿ�. 
#define BLTATB_BOOMERANG			0x20			// �θ޶� 


#define MAX_HIT_ID								25		// 5*5 ����� ���Ͽ� , 
// ���ݿ� ���Ͽ� ���ظ� �Դ� ĳ������ ���� ������ 

#define MAX_BULLET_FILE_NAME_LENGTH				64

#define MAX_DIRECTION	5

class cltBulletadjust
{
public :

	cltPos clAdjustPos[MAX_DIRECTION];	// 0 : ��, 1 : ����, 2 : ��, 3 : ����, 4 : ��

	cltBulletadjust()
	{
		Init();
	}

	cltBulletadjust(SI32 x1, SI32 y1, SI32 x2, SI32 y2, SI32 x3, SI32 y3, 
		SI32 x4, SI32 y4, SI32 x5, SI32 y5 )
	{
		Init();

		clAdjustPos[0].siX = x1;
		clAdjustPos[0].siY = y1;

		clAdjustPos[1].siX = x2;
		clAdjustPos[1].siY = y2;

		clAdjustPos[2].siX = x3;
		clAdjustPos[2].siY = y3;

		clAdjustPos[3].siX = x4;
		clAdjustPos[3].siY = y4;

		clAdjustPos[4].siX = x5;
		clAdjustPos[4].siY = y5;

	}

	void Init()
	{
		for (SI32 i = 0; i < MAX_DIRECTION; i++)
		{
			clAdjustPos[i].Init();
		}
	}
};


class cltBulletSoundInfo
{
private:
	SI32	m_si32AttackSoundIndex;
	SI32	m_si32HitSoundIndex;

public:

	cltBulletSoundInfo()
	{
		Init();
	}

	cltBulletSoundInfo( SI32 AttackSoundIndex, SI32 HitSoundIndex )
	{
		Set( AttackSoundIndex, HitSoundIndex );
	}

	void Init()
	{
		m_si32AttackSoundIndex = 0;
		m_si32HitSoundIndex = 0;
	}

	void Set( SI32 AttackSoundIndex, SI32 HitSoundIndex )
	{
		m_si32AttackSoundIndex = AttackSoundIndex;
		m_si32HitSoundIndex = HitSoundIndex;
	}

	SI32 GetAttackSoundIndex()
	{
		return m_si32AttackSoundIndex;
	}

	SI32 GetHitSoundIndex()
	{
		return m_si32HitSoundIndex;
	}
};

class cltBulletDrawInfo
{
public:
	TCHAR	m_strFileName[ _MAX_PATH ];				// ���ϸ�
	TCHAR	m_strLightFileName[ _MAX_PATH ];		// �Ѿ� LIGHT ���ϸ�
	SI16	m_StartFont;							// ���� ��Ʈ
	SI32	m_EachDirectionFrameNum;				// �� ���⺰ �̹��� ����

	SI32	m_siTailSmoke;							// ���� ���� ���� ( 0 �� ���� ���� ����. )
	bool	m_bDirectionSwitch;						// ���⼺�� �ִ���

	//bool	bChaseSwitch;							// �Ѿ��� ������ ������?
	//bool	bCurveSwitch;							// �Ѿ��� Ŀ��� ���ư��� ��

	SI32	m_TransParentMode;						// ���� ȿ��
	SI32	m_siLightMode;

	SI32	m_siIndent;								// Y��ǥ �߰�
	SI16	m_siLoopStartFont;						// ������ ��ŸƮ ��Ʈ

	cltBulletadjust	clBulletadjust;					// �Ѿ� ������ ��ġ ����

	cltBulletDrawInfo()
	{
		Init();
	}

	void Init()
	{
		memset( m_strFileName,		0, _MAX_PATH );
		memset( m_strLightFileName, 0, _MAX_PATH );
		m_StartFont = 0;
		m_EachDirectionFrameNum = 0;
		m_siTailSmoke = 0;
		m_bDirectionSwitch = false;
		m_TransParentMode = 0;
		m_siLightMode = 0;
		m_siIndent = 0;
		m_siLoopStartFont = 0;
	}

	cltBulletDrawInfo( TCHAR *strFileName, TCHAR *strLightFileName, cltBulletadjust bulletadjust, SI16 StartFont, SI32 EachDirectionFrameNum, SI32 siTailSmoke, bool bDirectionSwitch, SI32 TransParentMode, SI32 siLightMode , SI32 siIndent )
	{
		Set( strFileName, strLightFileName, bulletadjust, StartFont, EachDirectionFrameNum, false, false, 0 , siLightMode, siIndent );
	}

	void Set( TCHAR *strFileName, TCHAR *strLightFileName, cltBulletadjust bulletadjust, SI16 StartFont, 
		SI32 EachDirectionFrameNum, SI32 siTailSmoke = 0, bool bDirectionSwitch = false, 
		SI32 TransParentMode = 0, SI32 siLightMode=0 , SI32 siIndent = 0 , SI16 LoopStartFont = 0)
	{
		memset( m_strFileName,		0, _MAX_PATH );
		memset( m_strLightFileName, 0, _MAX_PATH );

		if(strFileName)			StringCchCopy( m_strFileName, _MAX_PATH, strFileName );
		if(strLightFileName)	StringCchCopy( m_strLightFileName, _MAX_PATH, strLightFileName );

		m_StartFont			= StartFont;
		m_EachDirectionFrameNum = EachDirectionFrameNum;

		clBulletadjust		= bulletadjust;

		m_siTailSmoke		= siTailSmoke;
		m_bDirectionSwitch	= bDirectionSwitch;
		m_TransParentMode	= TransParentMode;
		m_siLightMode		= siLightMode;
		m_siIndent			= siIndent;

		m_siLoopStartFont	= LoopStartFont;
	}
};

class cltBulletLayerInfo{
public:
	SI32 siFont;
	bool bTransMode;

	cltBulletLayerInfo()
	{
		Init();
	}

	cltBulletLayerInfo(SI32 font, bool transmode)
	{
		Set(font, transmode);
	}

	void Init()
	{
		siFont		= -1;
		bTransMode	= false;
	}

	void Set(cltBulletLayerInfo* pclinfo)
	{
		Set(pclinfo->siFont, pclinfo->bTransMode);
	}

	void Set(SI32 font, bool transmode)
	{
		siFont		= font;
		bTransMode	= transmode;
	}

};

//------------------------------------
// cltBulletKindInfo
//------------------------------------
class cltBulletKindInfo
{
public:
	void Init(SHORT stepwidth, SHORT chaseswitch, SHORT curveswitch, SI32 attacktype, SI32 BulletAtb, SI32 BulletSmokeAtb, SI32 sidelay,
		SI32 firesmoke, SI32 hitsmoke, 
		cltBulletSoundInfo* pclSoundInfo,
		cltBulletLayerInfo* pcllayerinfo,
		cltBulletDrawInfo* pclDrawInfo,
		SI32 hitegroundsmoke = 0
		);

	void LoadSpr();

	SHORT StepWidth;
	TCHAR szFileName[MAX_BULLET_FILE_NAME_LENGTH];
	TCHAR szLightFileName[MAX_BULLET_FILE_NAME_LENGTH];
	SI32 Font;
	SI32  siMoveFrameNumber;


	cltBulletLayerInfo	clLayerInfo;

	// ���⸶�� �ٸ� �׸����� �����ϴ°�(TRUE), �Ѱ��� �׸��� �����ϴ°� ?(FALSE)
	BOOL bDirSwitch;                          

	BOOL TransparentSwitch;
	BOOL ChaseSwitch, CurveSwitch;			

	// 2003.10.29
	SI32 TailSmoke;


	// �Ѿ��� LIGHT
	SI32 m_siLightMode;

	// �Ѿ� ���� ����
	SI32 m_siIndent;
	cltBulletadjust clBulletadjust;
	SI16 m_siLoopStartFont;

	//----------------------
	// ���� Ÿ��. 
	//----------------------
	SI32 siAttackType;		


	SI32 siAtb;
	SI32 siSmokeAtb;

	SI32 siDelay;

	TSpr Spr;
	TSpr LightSpr;

	//-----------------------
	// ���� 
	//-----------------------
	SI32 siFireSmoke;		// �߻�� ����
	SI32 siHitSmoke;		// ������ ����
	SI32 siHiteGroundSmoke; // ������ ���� �ڿ� ���� �򸮴� ��

	//-----------------------
	// ȿ���� 
	//-----------------------
	SI32 siFireEffect;		// ���ݽ� ����
	SI32 siHitEffect;		// �ǰݽ� ����

	cltBulletKindInfo();
	~cltBulletKindInfo();

};

//--------------------------------------
// cltBulletCommon
//--------------------------------------
class cltBulletCommon{
public:
	cltMapCommon*				pclMap;
	const cltBulletKindInfo*	pclBKI;

	//------------------
	// �ڽ��� �ź� ����
	//------------------
	SI32 Kind;                        // � ������ obj�ΰ�?
	SI32 siMagicKind;				  // ���������� �Ѿ��̶�� ������ �����Ѵ�.

	SI32 Type;

	//-----------------
	// ���� �۾� ��Ȳ 
	//-----------------
	SI32  CurrentOrder;               // ���� ĳ���Ͱ� �ϰ� �ִ� �۾� 

	//------------------
	// ��ǥ ���� 
	//------------------
	cltPos clRealSrcPos;
	cltPos clRealDestPos;
	SI32 CurveBulletRealX, CurveBulletRealY;
	SI32 MapSX, MapSY;
	SI32  MapDX, MapDY;
	SI32  X, Y;                        // obj�� �߽� ��ġ 
	SI32 CenterX, CenterY;

	//------------------
	// ������ ���� 
	//------------------
	SI32 ShooterID;
	SI32 Apower;

	//-------------------
	// ���� ��ǥ ���� 
	//--------------------
	cltAttackTarget clAttackTarget;		// �Ѿ��� �����ؾ� �� ���. 
	int TargetDirection;               // ��ǥ�� ���� 
	int OldTargetDirection;			   // ��ǥ�� ���� ����

	//--------------------
	// ������ ���� 
	//--------------------
	int TempDirection;                // 16������ �����ϴ°�?
	SI32 CurveRate;					 // �󸶳� ��� �̷�°�?
	BOOL CurveSwitch;

	SI32 MoveStep;
	SI32 MaxMoveStep;

	SI32 StepWidth;                    // �̵� ����

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_SHOOT_RANGE>		CourseX;
	NSafeTArray<SI32, MAX_SHOOT_RANGE>		CourseY;
#else
	SI32 CourseX[MAX_SHOOT_RANGE];
	SI32 CourseY[MAX_SHOOT_RANGE];
#endif

	//-----------------------
	// ���� ��� 
	//-----------------------
	BOOL ChaseSwitch;    // ������ ���ΰ� �����ΰ�?
	BOOL ChaseRepeatNumber;

public:
	virtual void Init(){};
	virtual void SetAnimation(SI32 ani){}
	virtual void AniStepAction(){}
	virtual	BOOL Draw(){return FALSE;}
	virtual void MakeTail(SI32 tempdirection){};
	virtual void MakeHitSmoke(){};
	virtual void MakeHitSound(){};

	cltBulletCommon();

	bool Init(cltMapCommon* pclmap, SHORT kind, SHORT magickind, SHORT id, 
		SI32 shooter_id, SHORT apower, 
		const cltPos* pcltilestartpos, 
		const cltPos* pcldotstartpos, 
		const cltAttackTarget* pcltarget, 
		const cltPos* pcldotdestpos, 
		cltBulletKindInfo* pclbki);

	void DecideDirection(SHORT x1, SHORT y1, SHORT x2, SHORT y2);

	void GetCourse( double SpeedIncTime = 0.3 );

	BOOL Action();

	void CalculateRealXY();

	BOOL Hit();
	BOOL HitNormal();
	BOOL HitFragment(); 

};

//---------------------------------------
// cltBulletServer
//---------------------------------------
class cltBulletServer : public cltBulletCommon{

public:


	SHORT BallSize;


	SI32 HitIDIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_HIT_ID>		HitID;
#else
	SI32 HitID[MAX_HIT_ID];
#endif

public:
	cltBulletServer();

	void Init();

	// �ѹ� ������ ĳ���͸� �ٽ� �������� �ʱ� ���ؼ�.
	// ������ �ʱ�ȭ�Ѵ�. 
	void InitPushID();
	void PushHitID(SI32 id);
	BOOL IsAlreadyPushID(SI32 id);

};

//---------------------------------------
// cltBulletClient
//---------------------------------------
class cltBulletClient : public cltBulletCommon{
public:

	//---------------------------------
	// ��� �ɼ�. 
	//---------------------------------
	bool bDrawSwitch;				   // ��� ����. 
	bool bReverseSwitch;                // �̷��� ����. 

	SI32 siFont;

	TSpr* pSpr;
	TSpr* pLightSpr;

	SI32 siAnimation;									// � ������ �ִϸ��̼��� �����ϴ°�?
	SI32 siAniStep;

	// �̵����� 
	SI08		MoveFrameNumber;
#ifdef _SAFE_MEMORY
	NSafeTArray<TSpr*, 9>		pMoveFileSpr;

	NSafeTArray<SI32, 9>		MoveFont;
#else
	TSpr*	pMoveFileSpr[9];

	SI32		MoveFont[9];
#endif

	BOOL TransparentSwitch;
	SI32  DrawStartX, DrawStartY;      // �׸��� �׷����� ���� ��ġ 
	SI32  LightDrawStartX, LightDrawStartY;

	SI32 CurveBulletDrawX, CurveBulletDrawY;

	// 2003.10.29
	SI32 TailSmoke;                    // ���� ����

	UI16 uiAdjustFrame;				   // ��ġ������ ���� ��
	SI32 AdjustPosX;
	SI32 AdjustPosY;

	cltBulletClient();
	void Init();
	void SetFileNFont();
	// ���� ��ġ�� ����Ѵ�.
	void CalculateDrawStartXY();
	BOOL Draw();

	// ���� �� �׸��� �����Ѵ�. 
	void DecideFont();
	void DecideFontMove();
	void DecideDir();

	void SetAnimation(SI32 ani){siAnimation = ani;}
	SI32 GetAnimation()const{return siAnimation;}

	void AniStepAction();

	void SetMoveImage16(TSpr* pspr, SHORT font, SHORT frame);

	void SetMoveImage(SHORT ani, TSpr* pspr, SHORT font);

	//���� ���⸦ �����. 
	void MakeTail(SI32 tempdirection);

	// �ǰ� ���⸦ �����. 
	void MakeHitSmoke();

	// �ǰ� ���带 ����Ѵ�.
	void MakeHitSound();

};

//---------------------------------------------
// cltBulletManager
//--------------------------------------------
class cltBulletManager{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltBulletKindInfo, MAX_BULLET_KIND_NUMBER>	BKI;
#else
	cltBulletKindInfo BKI[MAX_BULLET_KIND_NUMBER];
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<cltBulletCommon*, MAX_BULLET_NUMBER>		pclBullet;
	NSafeTArray<SI32, MAX_BULLET_NUMBER>				BulletInfo;
#else
	cltBulletCommon*	pclBullet[MAX_BULLET_NUMBER]; // �Ѿ˿� ������ 
	SI32				BulletInfo[MAX_BULLET_NUMBER]; // �Ѿ˿� ���� ������ ������ ���� 
#endif

private:
	SI32 FindEmptyBullet();
	void DeleteBullet(SI32 id);
	void InitBulletKindInfo();

public:

	cltBulletManager(SI32 gamemode);
	~cltBulletManager();

	void DeleteBullet();

	SI32 SetBullet(cltMapCommon* pclmap, SHORT kind, SHORT magickind,
		SI32 shooter_id, 
		SHORT apower, 
		const cltPos* pcltilestartpos, 
		const cltPos* pcldotstartpos, 
		const cltAttackTarget* pcltarget, 
		const cltPos* pcldotdestpos);

	BOOL Action();
	BOOL Draw();

};




#endif

