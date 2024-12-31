#pragma once

#include "../common/CommonHeader.h"

const SI32 Const_Marriage_Min_Level			= 50;					// ��ȥ�Ҽ��ִ� �ּ� ����

const SI32 Const_Max_Propose_Message		= 128;					// ���������Ҷ� ���̴� �ִ� �޽��� ����

const SI32 Const_Family_Item_Unique			= ITEMUNIQUE(24119);	// �����̿��
const SI32 Const_Family_Item_Num			= 1;					// �����̿�� ���� �ʿ��� ������ ����

const SI32 Const_WeddingAnniversary_Unique	= ITEMUNIQUE(8120);		// ��ȥ ����� ���� ������ ����ũ
const SI32 Const_WeddingAnniversary_Num		= 1;					// ��ȥ ����� ���� ������ ����

const SI32 Const_Wedding_FullDress_Unique	= ITEMUNIQUE(13348);	// ��ȥ�Ǻ� ����
const SI32 Const_Wedding_FullDress_Num		= 1;

enum MARRIAGE_MATE_CONNECT_MODE
{
	MARRIAGE_MATE_CONNECT_MODE_NONE		= 0,
	MARRIAGE_MATE_CONNECT_MODE_CONNECT,
	MARRIAGE_MATE_CONNECT_MODE_SAMEMAP,
};
// ��ȥ�� ���� ����
enum MARRIAGE_LOVE_LEVEL
{
	MARRIAGE_LOVE_LEVEL_NONE = 0,	// �ƹ� ��޵� �ƴϴ�

	MARRIAGE_LOVE_LEVEL_01,			// ��ȥ�ϰ� �Ǹ� �⺻������ �޴� ���
	MARRIAGE_LOVE_LEVEL_02,
	MARRIAGE_LOVE_LEVEL_03,
	MARRIAGE_LOVE_LEVEL_04,
	MARRIAGE_LOVE_LEVEL_05,
	MARRIAGE_LOVE_LEVEL_06,
	MARRIAGE_LOVE_LEVEL_07,
	MARRIAGE_LOVE_LEVEL_08,
	MARRIAGE_LOVE_LEVEL_09,
	MARRIAGE_LOVE_LEVEL_10,

	MARRIAGE_LOVE_LEVEL_MAX
};

class CMarriage
{
private:
	SI32	m_siMatePersonID;				// �����(��ȥ ������� 0�̰� ����� ���̵� ������ ���������ϴ� ����̴�)
	TCHAR	m_szMateName[MAX_PLAYER_NAME];	// ����� �̸�

	SI32	m_siWeddingDateVary;			// ��ȥ��
	SI32	m_siItemGetDateVary;			// ��ȥ����� ������ ���� ��¥
	BOOL	m_bRequestItemGet;				// ��ȥ����� �������� ������� ��û�ߴ�
    
	SI16	m_siLoveLevel;					// ������
	SI32	m_siUseHourVary;				// ������ ������ ���� ���ð�
	SI32	m_siLimitHourVary;				// ������ ������ ���� �ð�

	SI16	m_siConnectMode;				// ���� ���

public:
	CMarriage( void )		{	ZeroMemory(this, sizeof(CMarriage));	}
	~CMarriage( void )		{	}

	void	Init( void )
	{
		ZeroMemory(this, sizeof(CMarriage));
	}

	void	Set( CMarriage* pclMarriage )
	{
		if ( pclMarriage )
		{
			memcpy( this, pclMarriage, sizeof(CMarriage) );
		}
	}

	void	Set( SI32 siMatePersonID,	TCHAR* pszMateName, 
				SI32 siWeddingDateVary,	SI32 siItemGetDateVary,	BOOL bRequestItemGet,
				SI16 siLoveLevel,		SI32 siUseHourVary,		SI32 siLimitHourVary, 
				SI16 siConnectMode )
	{
		m_siMatePersonID	= siMatePersonID;
		if ( pszMateName )
		{
			StringCchCopy( m_szMateName, sizeof(m_szMateName), pszMateName );
		}

		m_siWeddingDateVary	= siWeddingDateVary;
		m_siItemGetDateVary	= siItemGetDateVary;
		m_bRequestItemGet	= bRequestItemGet;

		m_siLoveLevel		= siLoveLevel;
		m_siUseHourVary		= siUseHourVary;
		m_siLimitHourVary	= siLimitHourVary;

		m_siConnectMode		= siConnectMode;
	}

	// Interface Function
public:
	void	SetMatePersonID( SI32 siMatePersonID )				{	m_siMatePersonID = siMatePersonID;			}
	SI32	GetMatePersonID( void )								{	return m_siMatePersonID;					}

	void	SetMateName( TCHAR* pszMateName )					{	if ( pszMateName ) StringCchCopy( m_szMateName, sizeof(m_szMateName), pszMateName );	}
	TCHAR*	GetMateName( void )									{	return m_szMateName;						}

	void	SetWeddingDateVary( SI32 siWeddingDateVary )		{	m_siWeddingDateVary = siWeddingDateVary;	}
	SI32	GetWeddingDateVary( void )							{	return m_siWeddingDateVary;					}

	void	SetItemGetDateVary( SI32 siItemGetDateVary )		{	m_siItemGetDateVary = siItemGetDateVary;	}
	SI32	GetItemGetDateVary( void )							{	return m_siItemGetDateVary;					}

	void	SetRequestItemGet( BOOL bRequestItemGet )			{	m_bRequestItemGet = bRequestItemGet;		}
	BOOL	GetRequestItemGet( void )							{	return m_bRequestItemGet;					}

	void	SetLoveLevel( SI16 siLovelovel )					{	m_siLoveLevel = siLovelovel;				}
	SI16	GetLoveLevel( void )								{	return m_siLoveLevel;						}

	void	SetUseHourVary( SI32 siUseHourVary )				{	m_siUseHourVary = siUseHourVary;			}
	SI32	GetUseHourVary( void )								{	return m_siUseHourVary;						}

	void	SetLimitHourVary( SI32 siLimitHourVary )			{	m_siLimitHourVary = siLimitHourVary;		}
	SI32	GetLimitHourVary( void )							{	return m_siLimitHourVary;					}
	
	void	SetConnectMode( SI16 siConnectMode )				{	m_siConnectMode = siConnectMode;			}
	SI16	GetConnectMode( void )								{	return m_siConnectMode;						}

	// Utility Function
public:
	BOOL	IsMarried( void )
	{
		// ������۽����̵�� ��ȥ����� �Ѵ� �����Ǿ�� ��ȥ�Ѱ��̴�
		if ( (0 < m_siMatePersonID) && (0 < m_siWeddingDateVary) )
		{
			return TRUE;
		}

		return FALSE;
	}

	SI16	CalcNowLoveLevel( SI32 siNowHourVary );

	// ��ȥ ������ΰ�?
	BOOL	IsWeddingAnniversary( SI32 siNowDateVary );
	// ��ȥ ����� �������� �޾Ҵ°�?
	BOOL	IsWeddingItemGet( SI32 siNowDateVary );
	// ���� �ð��� �����´�
	SI32	GetRemainHourVary( SI32 siNowHourVary );


};