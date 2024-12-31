#pragma once 

#include <Directives.h>
#include "..\..\Common\CommonHeader.h"

#define WEDDING_RESERVE_LIST_NUM			24		// ���� ����Ʈ ����
#define WEDDING_RESERVE_BASIC_COST			100000	// ���� ���� ����

#define WEDDING_RESERVE_LIST_PAGE_PER_NUM	5		// ���ʴ� ������ ����Ʈ ����

enum WEDDING_RESERVE_RESULT
{
	WEDDING_RESERVE_RESULT_INVALID = 0,		// �Ϲ����� ������ �ȵ�

	WEDDING_RESERVE_RESULT_ALREADY_OTHER,	// �ٸ���� ����Ǿ� ����
	WEDDING_RESERVE_RESULT_ALREADY_MY,		// ���� ����Ǿ� ����


	WEDDING_RESERVE_RESULT_SUCCESS
};

enum WEDDING_RESERVE_STATUS
{
	WEDDING_RESERVE_STATUS_NONE	= 0,	// ���� ����
	WEDDING_RESERVE_STATUS_RESERVE,		// ���� ������
	WEDDING_RESERVE_STATUS_PROGRESS,	// ������
};

class cltWeddingReserveUnit
{
public:
	SI32		m_siReserveNum;		// ���� ��ȣ

	SI32		m_siMate1_PersonID;	// ������1
	TCHAR		m_szMate1_Name[MAX_PLAYER_NAME];

	SI32		m_siMate2_PersonID;	// ������2
	TCHAR		m_szMate2_Name[MAX_PLAYER_NAME];

	SYSTEMTIME	m_stReserveTime;	// ���� �ð�

public:
	cltWeddingReserveUnit( void )
	{
		ZeroMemory( this, sizeof(cltWeddingReserveUnit) );
	}

	~cltWeddingReserveUnit( void )
	{
	}

	void	Init( void )
	{
		ZeroMemory( this, sizeof(cltWeddingReserveUnit) );
	}

	void	Set( cltWeddingReserveUnit* pclUnit )
	{
		if ( NULL == pclUnit )
		{
			return;
		}

		memcpy( this, pclUnit, sizeof(cltWeddingReserveUnit) );
	}

	void	Set( SI32 siReserveNum, SI32 siMate1_PersonID, TCHAR* pszMate1_Name, SI32 siMate2_PersonID, TCHAR* pszMate2_Name,  SYSTEMTIME& stReserveTime )
	{
		m_siReserveNum		= siReserveNum;

		m_siMate1_PersonID	= siMate1_PersonID;
		if ( pszMate1_Name )	StringCchCopy( m_szMate1_Name, sizeof(m_szMate1_Name), pszMate1_Name );

		m_siMate2_PersonID	= siMate2_PersonID;
		if ( pszMate2_Name )	StringCchCopy( m_szMate2_Name, sizeof(m_szMate2_Name), pszMate2_Name );

		memcpy( &m_stReserveTime, &stReserveTime, sizeof(m_stReserveTime) );
	}

	void	Set( SI32 siReserveNum, SI32 siMate1_PersonID, TCHAR* pszMate1_Name, SI32 siMate2_PersonID, TCHAR* pszMate2_Name, SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour )
	{
		m_siReserveNum		= siReserveNum;

		m_siMate1_PersonID	= siMate1_PersonID;
		if ( pszMate1_Name )	StringCchCopy( m_szMate1_Name, sizeof(m_szMate1_Name), pszMate1_Name );

		m_siMate2_PersonID	= siMate2_PersonID;
		if ( pszMate2_Name )	StringCchCopy( m_szMate2_Name, sizeof(m_szMate2_Name), pszMate2_Name );


		ZeroMemory( &m_stReserveTime, sizeof(m_stReserveTime) );

		m_stReserveTime.wYear	= siYear;
		m_stReserveTime.wMonth	= siMonth;
		m_stReserveTime.wDay	= siDay;
		m_stReserveTime.wHour	= siHour;
	}

//Utility Function
	BOOL	IsSameTime( SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour )
	{
		if ( m_stReserveTime.wYear != siYear )		return FALSE;
		if ( m_stReserveTime.wMonth != siMonth )	return FALSE;
		if ( m_stReserveTime.wDay != siDay )		return FALSE;
		if ( m_stReserveTime.wHour != siHour )		return FALSE;

		return TRUE;
	}

	BOOL	IsReserved( void )
	{
		if ( 0 < m_siMate1_PersonID )	return TRUE;
		if ( 0 < m_siMate2_PersonID )	return TRUE;

		return FALSE;
	}

	void	InitExecptTime( void )
	{
		SI16 siYear		= m_stReserveTime.wYear;
		SI16 siMonth	= m_stReserveTime.wMonth;
		SI16 siDay		= m_stReserveTime.wDay;
		SI16 siHour		= m_stReserveTime.wHour;

		Init();

		m_stReserveTime.wYear	= siYear;
		m_stReserveTime.wMonth	= siMonth;
		m_stReserveTime.wDay	= siDay;
		m_stReserveTime.wHour	= siHour;
	}
};

// ���� ������ ���� ����� ��Ÿ����(�ð� ���� ����)
class cltWeddingReserveSimpleUnit
{
public:
	SYSTEMTIME	m_stReserveTime;

	SI16		m_siReserveStatus;

public:
	cltWeddingReserveSimpleUnit( void )
	{
		ZeroMemory( this, sizeof(cltWeddingReserveSimpleUnit) );
	}

	~cltWeddingReserveSimpleUnit( void )
	{

	}

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltWeddingReserveSimpleUnit) );
	}

	void Set( cltWeddingReserveSimpleUnit* pclSimpleUnit )
	{
		if ( NULL == pclSimpleUnit )
		{
			return;
		}

		memcpy( this, pclSimpleUnit, sizeof(cltWeddingReserveSimpleUnit) );
	}

	void Set( SYSTEMTIME& rstReserveTime, SI16 siReserveStatus )
	{
		memcpy( &m_stReserveTime, &rstReserveTime, sizeof(m_stReserveTime) );

		m_siReserveStatus = siReserveStatus;
	}

};

typedef NSafeTArray<cltWeddingReserveUnit, WEDDING_RESERVE_LIST_NUM> NSafty_WeddingReserveList;

class cltWeddingReserveList
{
private:
#ifdef _SAFE_MEMORY
	NSafty_WeddingReserveList	m_clReserveList;
#else
	cltWeddingReserveUnit		m_clReserveList[WEDDING_RESERVE_LIST_NUM];
#endif

	SI16						m_siRequestHour;

public:
	cltWeddingReserveList();
	~cltWeddingReserveList();

	void Init( void );

	// ���� �ð����� ���� ����Ʈ�� �����Ѵ�
	void SetReserveListTime( SI16 siAddHour=0 );

	// ��û�� �ð��� �Ǿ��°�
	BOOL IsRequestHour( void );

	// ����Ʈ ��û ���μ���
	void RequestListProcess( bool bFirst=false );

	// ��¥�� �⺻���� ����Ʈ �ε����� �����´�
	SI32 GetReserveListIndex( SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour );

	// ������ �� �ִ°�?
	SI32 CanReserve( SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siPersonID );

	// ���� �Ѵ�
	BOOL Reserve( SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour, SI32 siPersonID );

	// DB���� �޾ƿ� ���� ������ �����Ѵ�
	void SetReserve( SI32 siListIndex, cltWeddingReserveUnit* pclReserveUnit );

	// ���� ���� Ŭ��ũ �����͸� �����´�
	cltWeddingReserveUnit* GetReserveUnitPtr( SI16 siYear, SI16 siMonth, SI16 siDay, SI16 siHour );

	// ���� ���� Ŭ��ũ �����͸� �����´�
	cltWeddingReserveUnit* GetReserveUnitPtr( SI32 siListIndex );

	// ���� ���� Ŭ��ũ �����͸� �����´�
	cltWeddingReserveUnit* GetReserveUnitPtrFromNowTime( void );

	// ���� ��ȣ�� �ش��ϴ� ���� �ϳ��� ���������� �ð��� �����ϰ� �����
	BOOL InitOneUnitExecptTime( SI32 siReserveNum );


};