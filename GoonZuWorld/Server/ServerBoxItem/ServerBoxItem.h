#pragma once

#include "../../common/CommonHeader.h"
#include "../../common/Item/ItemCommon/ItemUnit.h"

// �ϳ��� ���ڿ� ����ִ� �����۵��� Ȯ�� ����
const SI32 Const_Max_BoxItem_TotalRate = 1000;

class cltBoxItem
{
private:
	SI16	m_siItemUnique;	// ������ ����ũ
	SI16	m_siItemNum;	// ������ ����
	SI16	m_siIRate;		// Ȯ��
	UI16	m_uiUseDate;	// ��� �Ⱓ
	SI16	m_siCanNotcie;	// ��� �˸� ����
	
public:
	cltBoxItem()
	{
		ZeroMemory( this, sizeof(cltBoxItem) );
	}
	cltBoxItem( cltBoxItem* pclBoxItem )
	{
		if ( pclBoxItem )
		{
			memcpy( this, pclBoxItem, sizeof(cltBoxItem) );
		}
	}
	cltBoxItem( SI16 siItemUnique, SI16 siItemNum, SI16 siRate, UI16 uiUseDate=0, SI16 siCanNotice=0 )
	{
		m_siItemUnique	= siItemUnique;
		m_siItemNum		= siItemNum;
		m_siIRate		= siRate;
		m_uiUseDate		= uiUseDate;
		m_siCanNotcie	= siCanNotice;
	}

	~cltBoxItem()	{};

	void Set( cltBoxItem* pclBoxItem )
	{
		if ( pclBoxItem )
		{
			memcpy( this, pclBoxItem, sizeof(cltBoxItem) );
		}
	}
	void Set( SI16 siItemUnique, SI16 siItemNum, SI16 siRate, UI16 uiUseDate=0, SI16 siCanNotice=0 )
	{
		m_siItemUnique	= siItemUnique;
		m_siItemNum		= siItemNum;
		m_siIRate		= siRate;
		m_uiUseDate		= uiUseDate;
		m_siCanNotcie	= siCanNotice;
	}

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltBoxItem) );
	}

public:
	SI16 GetItemUnique( void ) const				{	return m_siItemUnique;			}
	void SetItemUnique( const SI16 siItemUnique )	{	m_siItemUnique = siItemUnique;	}

	SI16 GetItemNum( void ) const					{	return m_siItemNum;				}
	void SetItemNum( const SI16 siItemNum )			{	m_siItemNum = siItemNum;		}

	SI16 GetRate( void ) const						{	return m_siIRate;				}
	void SetRate( const SI16 siRate )				{	m_siIRate = siRate;				}

	UI16 GetUseDate( void ) const					{	return m_uiUseDate;				}
	void SetUseDate( const UI16 uiUseDate )			{	m_uiUseDate = uiUseDate;		}

	SI16 GetCanNotice( void ) const					{	return m_siCanNotcie;			}
	void SetCanNotice( const SI16 siCanNotice )		{	m_siCanNotcie = siCanNotice;	}
};


class cltNewSelectBoxMgr
{
public:
	enum SELECTINDEX
	{
		SELECTINDEX_NONE	= -1,

		SELECTINDEX_00		= 0,
		SELECTINDEX_01,
		SELECTINDEX_02,
		SELECTINDEX_03,
		SELECTINDEX_04,
		SELECTINDEX_05,
		SELECTINDEX_06,
		SELECTINDEX_07,
		SELECTINDEX_08,
		SELECTINDEX_09,
		SELECTINDEX_10,
		SELECTINDEX_11,

		SELECTINDEX_MAX
	};
private:
	cltBoxItem* m_pclBoxItemList[MAX_NEWSELECTBOX_SELECTINDEX][MAX_NEWSELECTBOX_ITEM_LIST];
	SI16		m_siBoxItemListCount[MAX_NEWSELECTBOX_SELECTINDEX]; // ������ ����Ʈ�� �ִ� ����ִ� ������ ����

public:
	cltNewSelectBoxMgr();
	~cltNewSelectBoxMgr();

	bool LoadNewSelectBoxItemList( void );
	SI32 SelectStringToInteger( TCHAR* pszSelectString );

	void AddBoxItem( SI32 siIndex, IN cltBoxItem* pclBoxItem );

	bool GetItemListFromIndex( SI32 siIndex, OUT SI16* psiItemListArray );
	
	bool GetRandItemFromIndex( SI32 siIndex, OUT cltBoxItem* pclBoxItem );

	
};
