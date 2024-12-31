#pragma once 

#include <Directives.h>
#include "../../Common/CommonHeader.h"

// ��ȣ���� ��ȯ���� ���ҽ� ������ ���� 
#define MAX_SOULGUARDINFO_NUM					40

// ��ȣ���� �ɷ�
#define SOULGUARD_ABILITY_NONE					0x00000000	//�ƹ��͵� �ƴ�

#define SOULGUARD_ABILITY_DROPITEM				0x00000001	// ��ɽ� ����Ȯ���� ��� ������ ���� �þ
#define SOULGUARD_ABILITY_RECOVER_HP			0x00000002	// ��ɽ� ����Ȯ���� ĳ���� HP ȸ��
#define SOULGUARD_ABILITY_RECOVER_MP			0x00000004	// ��ɽ� ����Ȯ���� ĳ���� MP ȸ��
#define SOULGUARD_ABILITY_DAMAGE_DOWN			0x00000008	// ��ɽ� ����Ȯ���� ���ͷκ��� ��� ������� �����Ѵ�
#define SOULGUARD_ABILITY_DAMAGE_UP				0x00000010	// ��ɽ� ����Ȯ���� ������� �����Ѵ�
#define SOULGUARD_ABILITY_ELEMENTDAMAGE_UP		0x00000020	// ��ɽ� ����Ȯ���� ĳ������ ��� �Ӽ� ������ ���� �����ش�
#define SOULGUARD_ABILITY_HUNGRY_UP				0x00000040	// ��ɽ� ����Ȯ���� ĳ������ �������� �÷��ش�
#define SOULGUARD_ABILITY_EXP_UP				0x00000080	// ��ɽ� ����Ȯ���� ȹ��Ǵ� ����ġ�� �����ȴ�
#define SOULGUARD_ABILITY_SUMMONRECOVERY_HP		0x00000100	// ��ɽ� ����Ȯ���� ��ȯ���� HP ȸ��
#define SOULGUARD_ABILITY_SOMMONRECOVERY_MP		0x00000200	// ��ɽ� ����Ȯ���� ��ȯ���� MP ȸ��
#define SOULGUARD_ABILITY_MAKEABILITY_UP		0x00000400	// ������ ����Ȯ���� ������ �ɷ��� ���ȴ�
#define SOULGUARD_ABILITY_MAKETIME_SHORT		0x00000800	// ������ ����Ȯ���� ���� �ð��� �����ʷ� �ȴ�
#define SOULGUARD_ABILITY_NOICE					0x00001000	// ��ɽ� ����Ȯ���� ������ �ɷ��� ��� ������ Ǯ���ش�.
#define SOULGUARD_ABILITY_DEFENSE_MAGIC			0x00002000	// ��ɽ� ����Ȯ���� ���Ϳ��� ���� �� ������ �߻��Ѵ�.
#define SOULGUARD_ABILITY_ATTACK_MAGIC			0x00004000	// ��ɽ� ����Ȯ���� ���Ϳ��� ���� ������ ����Ѵ�
#define SOULGUARD_ABILITY_ATTACK_STUN			0x00008000	// ��ɽ� ����Ȯ���� ���͸� �������̰� �Ѵ�
#define SOULGUARD_ABILITY_MANA_ZERO				0x00010000	// ���� ���� ���� Ȯ���� ���� ����� 0���� �Ѵ�
#define SOULGUARD_ABILITY_DEFENSE_SUMMON		0x00020000	// ��ɽ� ���� Ȯ���� 20�ʵ��� ��ȯ���� ��ȯ�Ѵ�
#define SOULGUARD_ABILITY_MAGIC_DEFENSE			0x00040000	// ��ɽ� ����Ȯ���� ���� ���� �������� �ٿ��ش�
#define SOULGUARD_ABILITY_ATTACK_SOULICE		0x00080000	// ��ɽ� ����Ȯ���� ���� ���� �������� �ٿ��ش�
#define SOULGUARD_ABILITY_ATTACK_DEFENSE		0x00100000	// ��ɽ� ����Ȯ���� ���Ϳ� ������ ������� �÷��ش�


// �� ��ȣ������ ������ �ִ� �ɷ�ġ�� �����̴� �� ���� ������ ���� �ʿ�� ����
// �� ��ȣ������ �ɷ�ġ�� �ִ� ���� ������ŭ �����������Ƿ� ������ �ʿ��Ҽ��� ����
#define MAX_SOULGUARD_HAVE_ABILITY_NUM			8			// ��ȣ������ ���� �� �ִ� �ִ� �ɷ�ġ ���� 

enum SOULGUARD_ABILITY_UNIT_ADD
{
	SOULGUARD_ABILITY_UNIT_ADD_INVALID = 0,		// �˼����� ����

	SOULGUARD_ABILITY_UNIT_ADD_FAIL_COUNT,		// ���� �� �ִ� ������ �ʰ�
	SOULGUARD_ABILITY_UNIT_ADD_FAIL_ALREADY,	// �̹� �������� ���� �����Ͱ� �ִ�
	SOULGUARD_ABILITY_UNIT_ADD_FAIL_SAME,		// ���� �����Ͱ� �ִ�

	SOULGUARD_ABILITY_UNIT_ADD_SUCCESS			// ����
};


class cltSoulGuardAbilityUnit
{
private:
	SI32	m_siAbilityType;	// �ߵ� �ɷ�
	SI16	m_siValue;			// �ߵ��� ����� �ɷ�ġ

	SI16	m_siProbably;		// �ߵ� Ȯ��

	SI16	m_siDecFellowShip;	// �Ҹ�Ǵ� ģȭ��
	SI16	m_siCoolTimeSec;	// �ɷ¹��ֽ� ��Ÿ��(�ʴ�����)

public:
	cltSoulGuardAbilityUnit()
	{
		Init();
	}

	~cltSoulGuardAbilityUnit()
	{
		
	}

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltSoulGuardAbilityUnit) );
	}

	void Set( cltSoulGuardAbilityUnit* pclUnit )
	{
		if ( pclUnit )
		{
			memcpy( this, pclUnit, sizeof(cltSoulGuardAbilityUnit) );
		}
	}

	void Set( SI32 siAbilityType, SI16 siValue, SI16 siProbably, SI16 siDecFellowShip, SI16 siCoolTimeSec )
	{
		m_siAbilityType		= siAbilityType;
		m_siValue			= siValue;

		m_siProbably		= siProbably;

		m_siDecFellowShip	= siDecFellowShip;
		m_siCoolTimeSec		= siCoolTimeSec;
	}

public:
	SI32 GetAbilityType( void )						{	return m_siAbilityType;					}
	void SetAbilityType( SI32 siAbilityType )		{	m_siAbilityType = siAbilityType;		}

	SI16 GetValue( void )							{	return m_siValue;						}
	void SetValue( SI16 siValue )					{	m_siValue = siValue;					}

	SI16 GetProbably( void )						{	return m_siProbably;					}
	void SetProbably( SI16 siProbably )				{	m_siProbably = siProbably;				}

	SI16 GetDecFellowShip( void )					{	return m_siDecFellowShip;				}
	void SetDecFellowShip( SI16 siDecFellowShip )	{	m_siDecFellowShip = siDecFellowShip;	}

	SI16 GetCoolTimeSec( void )						{	return m_siCoolTimeSec;					}
	void SetCoolTimeSec( SI16 siCoolTimeSec )		{	m_siCoolTimeSec = siCoolTimeSec;		}
};

class cltSoulGuardAbilityList
{
private:
	SI16						m_siHaveCount;	// ���� ���� �ִ� ������ ����, �翬�� ��������� MAX_SOULGUARD_HAVE_ABILITY_NUM�� �������� ����
	cltSoulGuardAbilityUnit*	m_pclAbilityUnit[MAX_SOULGUARD_HAVE_ABILITY_NUM];

public:
	cltSoulGuardAbilityList();
	~cltSoulGuardAbilityList();
	
public:
	SI32						AddUnit( cltSoulGuardAbilityUnit* pclUnit );
	cltSoulGuardAbilityUnit*	GetUnit( SI32 siAbilityType );

	SI32						GetHaveAbility( void );

};

class cltSoulGuardInfoUnit
{
private:
	SI16						m_siKindUnique;		// ��ȣ���� ī�ε�
	SI16						m_siLife;			// ��ȣ���� ����

	SI16						m_siFellowShip;		// ��ȣ���� ģȭ��

	SI32						m_siItemUnique;		// �� �������� ����ϸ� ���� ī�ε��� ��ȣ������ ���´�

private:
	cltSoulGuardAbilityList		m_clAbilityList;	// �� ��ȣ������ ���� �ִ� �ɷ� ���
	

public:
	cltSoulGuardInfoUnit();
	~cltSoulGuardInfoUnit();

	void Init( void );

public:
	void SetInfo( SI16 siKindUnique, SI16 siLife, SI16 siFellowShip, SI32 siItemUnique )
	{
		m_siKindUnique	= siKindUnique;
		m_siLife		= siLife;		
	
		m_siFellowShip	= siFellowShip;

		m_siItemUnique	= siItemUnique;
	}

public:
	SI16 GetKindUnique( void )					{	return m_siKindUnique;			}
	void SetKindUnique( SI16 siKindUnique )		{	m_siKindUnique = siKindUnique;	}

	SI16 GetLife( void )						{	return m_siLife;				}
	void SetLife( SI16 siLife )					{	m_siLife = siLife;				}

	SI16 GetFellowShip( void )					{	return m_siFellowShip;			}
	void SetFellowShip( SI16 siFellowShip )		{	m_siFellowShip = siFellowShip;	}

	SI32 GetItemUnique( void )					{	return m_siItemUnique;			}
	void SetItemUnique( SI32 siItemUnique )		{	m_siItemUnique = siItemUnique;	}

public:
	void						SetUnit( cltSoulGuardAbilityUnit* pclUnit );
	cltSoulGuardAbilityUnit*	GetUnitFromAbilityType( SI32 siAbilityType );

	SI32 GetHaveAbility( void )
	{
		return m_clAbilityList.GetHaveAbility();
	}


public:
	
};

typedef NSafeTArray<cltSoulGuardInfoUnit, MAX_SOULGUARDINFO_NUM> NSafe_SoulGuardInfoUnit;

class cltSoulGuardInfoList
{
private:
#ifdef _SAFE_MEMORY
	NSafe_SoulGuardInfoUnit	m_clInfoList;
#else
	cltSoulGuardInfoUnit	m_clInfoList[MAX_SOULGUARDINFO_NUM];
#endif

	SI32					m_siListCount;

public:
	cltSoulGuardInfoList();
	~cltSoulGuardInfoList();

	void						Init( );
public:
	BOOL						LoadSoulGuardInfo( void );

private:
	void						AddSoulGuardInfoUnit( SI16 siKindUnique, SI16 siLife, SI16 siFellowShip, SI32 siItemUnique, cltSoulGuardAbilityUnit* pclUnit );
	SI32						ConvertAbilityTypeFromText( TCHAR* pszAbilityType );

public:
	cltSoulGuardInfoUnit*		GetUnitFromItemUnique( SI32 siItemUnique );
	cltSoulGuardInfoUnit*		GetUnitFromKindUnique( SI32 siKindUnique );

	SI32						GetHaveAbilityFromKindUnique( SI16 siKindUnique );

	cltSoulGuardAbilityUnit*	GetUnitFromKindUniqueAndAbilityType( SI16 siKindUnique, SI32 siAbilityType );
};

class cltSoulGuardMgr
{
private:
	cltSoulGuardInfoList	m_clSoulGuardInfoList;

public:
	cltSoulGuardMgr();
	~cltSoulGuardMgr();

	void Init();

public:
	cltSoulGuardInfoUnit*		GetSoulGuardUnitFromItemUnique( SI32 siItemUnique );
	cltSoulGuardInfoUnit*		GetSoulGuardUnitFromKindUnique( SI32 siKindUnique );

	cltSoulGuardAbilityUnit*	GetAbilityUnit( SI16 siKindUnique, SI32 siAbility );
	SI32						GetHaveAbility( SI16 siKindUnique );

public:
	SI32						GetSoulGuardSpeechTextNum( SI32 siAbility );
	SI32						GetSoulGuardExplainTextNum( SI32 siAbility );
};