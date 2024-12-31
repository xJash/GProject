#pragma once

#include "../../common/CommonHeader.h"
#include "../../common/Char/ParametaBox/parametabox.h"

//----------------------------------------------------------
// ĳ���� ������ �����ϴ� ������ ����
//----------------------------------------------------------
const SI32 Const_Max_CreateCharReward_Item	= 20;
const SI32 Const_Max_RecommandReward_Item	= (MAX_CHARACTER_LEVEL) + 1;


class cltItem;

class cltRewardItem
{
private:
	SI32	m_siItemUnique;
	SI32	m_siItemNum;
	SI32	m_siPara1;			// �������ܻ�Ȳ��1
	SI32	m_siPara2;			// �������ܻ�Ȳ��2

public:
	cltRewardItem()							{	Init();								}

	cltRewardItem( cltRewardItem* pclRewardItem )
	{
		if ( pclRewardItem )
		{
			memcpy( this, pclRewardItem, sizeof(cltRewardItem) );
		}
	}

	cltRewardItem( SI32 siItemUnique, SI32 siItemNum, SI32 siPara1=0, SI32 siPara2=0 )
	{
		m_siItemUnique	= siItemUnique;
		m_siItemNum		= siItemNum;
		m_siPara1		= siPara1;
		m_siPara2		= siPara2;
	}

	~cltRewardItem()	{};

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltRewardItem) );
	}

	void Set( cltRewardItem* pclRewardItem )
	{
		if ( pclRewardItem )
		{
			memcpy( this, pclRewardItem, sizeof(cltRewardItem) );
		}
	}

	void Set( SI32 siItemUnique, SI32 siItemNum, SI32 siPara1=0, SI32 siPara2=0 )
	{
		m_siItemUnique	= siItemUnique;
		m_siItemNum		= siItemNum;
		m_siPara1		= siPara1;
		m_siPara2		= siPara2;
	}

	void SetItemUnique( SI32 siItemUnique )		{	m_siItemUnique = siItemUnique;	}
	SI32 GetItemUnique( void )					{	return m_siItemUnique;			}

	void SetItemNum( SI32 siItemNum )			{	m_siItemNum = siItemNum;		}
	SI32 GetItemNum( void )						{	return m_siItemNum;				}

	void SetPara1( SI32 siPara1 )				{	m_siPara1 = siPara1;			}
	SI32 GetPara1( void )						{	return m_siPara1;				}

	void SetPara2( SI32 siPara2 )				{	m_siPara2 = siPara2;			}
	SI32 GetPara2( void )						{	return m_siPara2;				}

};

//----------------------------------------------------------------------------------
// ĳ���� ������ ���� Ŭ����
//----------------------------------------------------------------------------------
class cltCreateCharReward
{
//-----------------------------------------
// Variable Area
//-----------------------------------------
private:
	cltRewardItem*	m_pclCreateCharReward[Const_Max_CreateCharReward_Item];
	SI32			m_siCreateCharRewardCount;

//-----------------------------------------
// Function Area
//-----------------------------------------
public:
	cltCreateCharReward();
	~cltCreateCharReward();

	void Init( void );
	// ���� ����Ʈ�� �о�´�
	bool LoadRewardItemList( void );
	// ���� ���� �۾��� �Ѵ�
	void GiveRewardItem( SI32 siPersonID );

private:
	bool GetRewardItem( IN SI32 siItemUnique, IN SI32 siItemNum, OUT cltItem* pclGiveItem );
	bool AddRewardItem( cltRewardItem* pclRewardItem );
};

//----------------------------------------------------------------------------------
// ĳ���� ��õ�� ���� Ŭ����
//----------------------------------------------------------------------------------
class cltRecommendReward
{
//-----------------------------------------
// Variable Area
//-----------------------------------------
private:
	cltRewardItem*	m_pclRecommendReward[Const_Max_RecommandReward_Item];			// ��õ�� ���� ������.
	cltRewardItem*	m_pclRecommendeeReward[Const_Max_RecommandReward_Item];			// �� ��õ�� ���� ������.

	//[����] �߱����� ������ �ٶ� �ڵ��� ������ �ȵ����� �ִ� ������ ����.
	cltRewardItem*	m_pclRecommendRewardNoAuth[Const_Max_RecommandReward_Item];		// ��õ�� ���� ������.
	cltRewardItem*	m_pclRecommendeeRewardNoAuth[Const_Max_RecommandReward_Item];	// �� ��õ�� ���� ������.
	
	SI32			m_siRecommendGiveItemMaxLevel;									// ��õ���� ������ �޴� �ְ� ����.   (�߱��� �������� ���� �ȵ����� ������ �޴� ������ ���ƾ� �Ѵ�.)
	SI32			m_siRecommendeeGiveItemMaxLevel;								// �� ��õ���� ������ �޴� �ְ� ����.(�߱��� �������� ���� �ȵ����� ������ �޴� ������ ���ƾ� �Ѵ�.)

//-----------------------------------------
// Function Area
//-----------------------------------------
public:
	cltRecommendReward();
	~cltRecommendReward();

	void Init( void );
	// ���� ����Ʈ�� �о�´�
	bool LoadRewardItemList( void );
	
	bool LoadRecommendRewardItemList( void );		// ��õ�� �� ����� ������.
	bool LoadRecommendeeRewardItemList( void );		// ��õ�� ���� ����� ������.

	// ���� ���� �۾��� �Ѵ�
	bool GiveRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName, bool _bAuth = false ); // true=��õ��, false=��õ���������
	bool IsGiveRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName );

	cltRewardItem**	GetRecommendRewardList()	{	return &m_pclRecommendReward[0];	}
	cltRewardItem**	GetRecommendeeRewardList()	{	return &m_pclRecommendeeReward[0];	}

	SI32	GetRecommendGiveItemMaxLevel( void )	{	return m_siRecommendGiveItemMaxLevel;	}
	SI32	GetRecommendeeGiveItemMaxLevel( void )	{	return m_siRecommendeeGiveItemMaxLevel;	}

private:
	bool AddRecommendRewardItemNoAuth( cltRewardItem* pclRewardItem );
	bool AddRecommendRewardItem( cltRewardItem* pclRewardItem );

	bool AddRecommendeeRewardItemNoAuth( cltRewardItem* pclRewardItem );
	bool AddRecommendeeRewardItem( cltRewardItem* pclRewardItem );
	
	void SendRecommenderMessage( cltRewardItem* pclRewardItem, SI32 siPersonID, SI32 siLevel, bool _bAuth  ); 
	void SendRecommendMessage( cltRewardItem* pclRewardItem, SI32 siPersonID, SI32 siLevel, TCHAR* pszRecommenderName, bool _bAuth  );
};


//----------------------------------------------------------------------------------
// ���� ������� �޴���
//----------------------------------------------------------------------------------
class cltRewardMgr
{
private:
	cltCreateCharReward	m_clCreateCharReward;
	cltRecommendReward	m_clRecommendReward;

public:
	cltRewardMgr();
	~cltRewardMgr();

	void			Init( void );

	void			LoadRewardList( void );

	// ĳ���� ���� ����
	void			GiveCreateCharRewardItem( SI32 siPersonID );

	// ��õ�� ������ ����
	bool			GiveRecommendRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName, bool _bAuth = false ); // true=��õ��, false=��õ���������
	bool			IsGiveRecommendRewardItem( SI32 siPersonID, SI32 siLevel, bool bGiveMode, TCHAR* pszRecommenderName );

	cltRewardItem**	GetRecommendRewardItemList( void );
	cltRewardItem**	GetRecommendeeRewardItemList( void );

	SI32			GetRecommendGiveItemMaxLevel( void )	{	return m_clRecommendReward.GetRecommendGiveItemMaxLevel();	}
	SI32			GetRecommendeeGiveItemMaxLevel( void )	{	return m_clRecommendReward.GetRecommendeeGiveItemMaxLevel();	}
	/*
	// ĳ���� ������ ����
	void	GiveLevelUpRewardItem(  );
	*/

};

