#pragma once

#include "../common/CommonHeader.h"

const SI32 Const_Max_SoulGuard_ActiveProbably	= 1000;		// ��ȣ���� �ɷ� �ߵ��� Ȯ�� �ִ� %
const SI32 Const_Max_SoulGuard_FellowShip		= 100;		// ��ȣ������ ���� �� �ִ� �ִ� ģȭ��

const SI32 Const_Unlimit_SoulGuard_Life			= 30000;

const SI32 Const_SoulGuardHouse_ItemUnique		= 24123;	// ��ȣ���� ������ ������ ����ũ
const SI32 Const_SoulGuardHouse_ItemNum			= 1;		// ��ȣ���� ������ ������ ���� �ʿ� ������ ����


class cltSoulGuardHouseUnit
{
private:
	SI32	m_siSoulGuardID;
	SI16	m_siKindUnique;

public:
	cltSoulGuardHouseUnit( void );
	~cltSoulGuardHouseUnit( void );

	void Init( void );

	void Set( SI32 siSoulGuardID, SI16 siKindUnique )
	{
		m_siSoulGuardID	= siSoulGuardID;
		m_siKindUnique	= siKindUnique;
	}

	void Set( cltSoulGuardHouseUnit* pclUnit )
	{
		if ( pclUnit )
		{
			memcpy( this, pclUnit, sizeof(cltSoulGuardHouseUnit) );
		}
	}

public:
	SI32 GetSoulGuardID( void )					{	return m_siSoulGuardID;				}
	void SetSoulGuardID( SI32 siSoulGuardID )	{	m_siSoulGuardID = siSoulGuardID;	}

	SI16 GetKindUnique( void )					{	return m_siKindUnique;				}
	void SetKindUnique( SI16 siKindUnique )		{	m_siKindUnique = siKindUnique;		}

};

typedef NSafeTArray<cltSoulGuardHouseUnit, MAX_SOULGUARD_HOUSE_NUM>	NSafe_SoulGuardHouseUnit;


class cltSoulGuardHouse
{
private:
#ifdef _SAFE_MEMORY
	NSafe_SoulGuardHouseUnit	m_clSoulGuardHouse;
#else
	cltSoulGuardHouseUnit		m_clSoulGuardHouse[MAX_SOULGUARD_HOUSE_NUM];
#endif

	SI16						m_siMaxHaveHouseNum;	// ���� �ո� ��ȣ���� ������ ����(MAX_SOULGUARD_HOUSE_NUM�� ���� �� ����)

public:
	cltSoulGuardHouse();
	~cltSoulGuardHouse();

	void Init( void );

public:
	void Set( SI16 siMaxHaveHouseNum, SI32* psiSoulGuardID, SI16* psiSoulGuardKind );
	void SetHouseUnit( SI32 siIndex, SI32 siSoulGuardID, SI16 siKindUnique );

	SI32 GetSoulGuardIDFromIndex( SI32 siIndex );
	SI16 GetKindUniqueFromIndex( SI32 siIndex );

public:
	SI16 GetMaxHaveHouseNum( void )						{	return m_siMaxHaveHouseNum;					}
	void SetMaxHaveHouseNum( SI16 siMaxHaveHouseNum )	{	m_siMaxHaveHouseNum = siMaxHaveHouseNum;	}

};


enum SOULGUARD_STATUS
{
	SOULGUARD_STATUS_IN = 0,	// �ȿ� �ִ�(ȸ����)
	SOULGUARD_STATUS_OUT,		// �ۿ� �����ִ�(��ȯ��)
	SOULGUARD_STATUS_DEAD,		// ��ȣ���� ����
};

class cltSoulGuard
{
private:
	SI32	m_siSoulGuadrID;				// ������ ID(�����ɶ� �߱޵�)
	TCHAR	m_szName[MAX_SOULGUARD_NAME];	// �̸�

	SI16	m_siStatus;						// ����(In,Out)
	SI16	m_siKind;						// Kind Unique

	SI32	m_siLimitDateVary;				// �̶����� ��ȿ�ϴ�

	SI16	m_siFellowShip;					// ģȭ��

	// �Ʒ������� DB���� ������� ����
	SI32	m_siHaveAbility;				// ���� �ִ� �ɷ� BIT����ũ�������� ó��(���߿� ������ �ɷ��� �ִ��� �������� ���ҽ����� üũ�ϱ� ���ٴ� �̸� ������ ���ٰ� �̿��Ҽ��ֵ��� �Ѵ�)

public:
	cltSoulGuard( void );
	~cltSoulGuard( void );

	void	Init( void );				// cltSoulGuard Ŭ���� ��ü�� �ʱ�ȭ ��Ų��
	void	InitExceptHouse( void );	// �ɹ� ������ �����Ҵ� �����ϰ� �ʱ�ȭ ��Ų��

	void	SetSoulGuard( SI32 siSoulGuardID, TCHAR* pszName, SI16 siStatus, SI16 siKind, SI32 siLimitDateVary, SI16 siFellowShip );

public:
	SI32	GetSoulGuardID( void )						{	return m_siSoulGuadrID;					}
	void	SetSoulGuardID( SI32 siSoulGuardID )		{	m_siSoulGuadrID = siSoulGuardID;		}

	TCHAR*	GetName( void )								{	return m_szName;						}
	void	SetName( TCHAR* pszName )					{	if ( pszName ) StringCchCopy( m_szName, sizeof(m_szName), pszName );	}

	SI16	GetStatus( void )							{	return m_siStatus;						}
	void	SetStatus( SI16 siStatus )					{	m_siStatus = siStatus;					}

	SI16	GetKind( void )								{	return m_siKind;						}
	void	SetKind( SI16 siKind )						{	m_siKind = siKind;						}

	SI32	GetLimitDateVary( void )					{	return m_siLimitDateVary;				}
	void	SetLimitDateVary( SI32 siLimitDateVary )	{	m_siLimitDateVary = siLimitDateVary;	}

	SI16	GetFellowShip( void )						{	return m_siFellowShip;					}
	void	SetFellowShip( SI16 siFellowShip )			{	m_siFellowShip = siFellowShip;			}

	void	SetHaveAbility( SI32 siAbility )			{	m_siHaveAbility = siAbility;			}
	void	AddHaveAbility( SI32 siAbility )			{	m_siHaveAbility |= siAbility;			}
	BOOL	IsHaveAbility( SI32 siAbility )				{	return (m_siHaveAbility & siAbility);	}
	void	ClearHaveAbility( void )					{	m_siHaveAbility = 0;					}

public:
	BOOL	IsEmpty( void )
	{
		if ( 0 < m_siSoulGuadrID )		return FALSE;
		if ( 0 < m_siKind )				return FALSE;
		if ( 0 < m_siLimitDateVary )	return FALSE;
		
		return TRUE;
	}

public:
	cltSoulGuardHouse	m_clHouse;	// ��ȣ���� ������
};