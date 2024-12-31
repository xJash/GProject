#pragma once

#include "CommonLogic.h"
#include "../../common/Char/KindInfo/kindinfo.h"

// [����] ��ȯ���� ���ſ� ���� �⺻������ ���´�.
class cltSummonTransformInfo
{
public:		
	cltSummonTransformInfo()												{ ZeroMemory( this, sizeof(*this) );						}
	~cltSummonTransformInfo()												{															}

	SI32 GetSummonKind( void )												{ return m_siSummonKind;									}
	void SetSummonKind( SI32 _siSummonKind )								{ m_siSummonKind = _siSummonKind;							}	

	SI32 GetTransformSummonKind( void )										{ return m_siTransformSummonKind;							}
	void SetTransformSummonKind( SI32 _siTransformSummonKind )				{ m_siTransformSummonKind = _siTransformSummonKind;			}

	SI32 GetAbility( void )													{ return m_siAbility;										}
	void SetAbility( SI32 _siAbility )										{ m_siAbility = _siAbility;									}

private:
	SI32	m_siSummonKind;				// ������ 
	SI32	m_siTransformSummonKind;
	SI32	m_siAbility;
};

//[����] ��ȯ�� ���� �޴���.
class cltSummonTransformManager
{
public:
	cltSummonTransformManager( void )		{ ZeroMemory( this, sizeof(*this) );		}
	~cltSummonTransformManager( void )		{											}

	bool	Init( void );
	bool	LoadFile( void );

	bool	IsTransformSummonInfo( IN SI32 _siSummonKind );
	void	GetTransformSummonInfo( IN SI32 _siSummonKind, OUT SI32 &TransformSummonKind, OUT SI32 &TransformSummonAbiliy );	// ��ȯ���� ���� ������ ���Ϲ���.


private:
	cltSummonTransformInfo	m_clSummonTransformInfo[MAX_KINDINFO_NUMBER];
};
