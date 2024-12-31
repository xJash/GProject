#ifndef _ATIFACT_RESTORE_MANAGER_H_
#define _ATIFACT_RESTORE_MANAGER_H_

#include <Directives.h>
#include "CommonLogic.h"

#define ELEMENT_RESTORE_MAX_LIST	200
#define POWDER_RESTORE_MAX_LIST		150

#define	ITEM_BY_RESTORE_MAX_NUM		5	// ���� �������� �ټ��ִ� �ִ� ����.
#define	ITEM_BY_ELEMENT_KIND_NUM    3	// �� ������ ���� �������� �ִ� ������ ����.
#define	ITEM_BY_POWDER_KIND_NUM     5	// �� ������ ���� �������� �ִ� ������ ����.


class clElementRestore
{
public:
	
	SI32	m_siLevel;									// ����
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, ITEM_BY_ELEMENT_KIND_NUM>		m_siItemUnique;
	NSafeTArray<SI32, ITEM_BY_ELEMENT_KIND_NUM>		m_siMinNum;
	NSafeTArray<SI32, ITEM_BY_ELEMENT_KIND_NUM>		m_siMaxNum;
	NSafeTArray<SI32, ITEM_BY_ELEMENT_KIND_NUM>		m_siRate;
#else
	SI32	m_siItemUnique[ITEM_BY_ELEMENT_KIND_NUM];	// �ִ� �������� ����ũ.
	SI32	m_siMinNum[ITEM_BY_ELEMENT_KIND_NUM];		// �ִ� �������� ���� ����.
	SI32	m_siMaxNum[ITEM_BY_ELEMENT_KIND_NUM];		// �ִ� �������� �ִ� ����.
	SI32    m_siRate[ITEM_BY_ELEMENT_KIND_NUM];			// �������� ������ Ȯ��.
#endif

	clElementRestore()
	{
		ZeroMemory( this, sizeof( clElementRestore ) );
	}

	bool LevelEqual(SI32 _siLevel)
	{
		if( m_siLevel == _siLevel )
		{
			return true;
		}
		
		return false;
	}
};

class clPowderRestore
{
public:

	SI32	m_siLevel;									// ����

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, ITEM_BY_POWDER_KIND_NUM>		m_siItemUnique;
	NSafeTArray<SI32, ITEM_BY_POWDER_KIND_NUM>		m_siMinNum;
	NSafeTArray<SI32, ITEM_BY_POWDER_KIND_NUM>		m_siMaxNum;
	NSafeTArray<SI32, ITEM_BY_POWDER_KIND_NUM>		m_siRate;
#else
	SI32	m_siItemUnique[ITEM_BY_POWDER_KIND_NUM];	// �ִ� �������� ����ũ.
	SI32	m_siMinNum[ITEM_BY_POWDER_KIND_NUM];		// �ִ� �������� ���� ����.
	SI32	m_siMaxNum[ITEM_BY_POWDER_KIND_NUM];		// �ִ� �������� �ִ� ����.
	SI32    m_siRate[ITEM_BY_POWDER_KIND_NUM];			// �������� ������ Ȯ��.
#endif

	clPowderRestore()
	{
		ZeroMemory( this, sizeof( clPowderRestore ) );
	}

	bool LevelEqual(SI32 _siLevel)
	{
		if( m_siLevel == _siLevel )
		{
			return true;
		}

		return false;
	}
};


class CArtifactRestoreManager
{
public:

	CArtifactRestoreManager();
	~CArtifactRestoreManager();
	
	void Init( void );
	bool LoadElementRestoreDataFromTxt( void );
	bool LoadPowderRestoreDataFromTxt( void );
	
	
public:	
#ifdef _SAFE_MEMORY
	NSafeTArray<clElementRestore, ELEMENT_RESTORE_MAX_LIST>		m_clElementRestore;
	NSafeTArray<clPowderRestore, POWDER_RESTORE_MAX_LIST>		m_clPowderRestore;
#else
	clElementRestore	m_clElementRestore[ ELEMENT_RESTORE_MAX_LIST ];
	clPowderRestore		m_clPowderRestore[ POWDER_RESTORE_MAX_LIST  ];
#endif
};

#endif
