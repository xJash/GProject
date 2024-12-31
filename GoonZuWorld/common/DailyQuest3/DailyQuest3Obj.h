#ifndef _DAILYQUEST3OBJ_H_
#define _DAILYQUEST3OBJ_H_

#include "..\SMLib\LibList\Obj.h"
#include "NDataTypes.h"

class CDailyQuest3ObjData
{
public:
	bool m_bHiddenQuest;		// ���� ����Ʈ ����.
	SI16 m_siIndex;
	SI16 m_siCount;
	SI16 m_siItemUnique;		// ���� ������ ����ũ
	SI16 m_siItemNum;			// ���� ������ ����.
	SI16 m_siRewardItemUnique;	// ���� ������ ����ũ
	SI16 m_siRewardItemNum;		// ���� ������ ����.
	SI32 m_siRewardExp;			// ���� ����ġ
	GMONEY m_siFee;				// ����Ʈ ������.
	SI32 m_siLeftTime;			// ����Ʈ ���� �ð�.
	SI32 m_siMakeItemNum;		// ���� ������ ����.
	

	CDailyQuest3ObjData()
	{
		memset( this, 0, sizeof( CDailyQuest3ObjData ) );
	}

	CDailyQuest3ObjData( SI16 Index )
	{
		memset( this, 0, sizeof( CDailyQuest3ObjData ) );
		m_siIndex = Index;
	}	

	void Init()
	{
		if ( m_siCount++ > 30000 )
		{
			m_siCount = 0;
		}

		m_siItemUnique			=	0	;
		m_siItemNum				=	0	;	

		m_siRewardItemUnique	=	0	;
		m_siRewardItemNum		=	0	;
		m_siRewardExp			=	0 ;


		m_siFee					=	0	;	
		m_siLeftTime			=	0	;	

		m_siMakeItemNum			=	0	;	
		m_bHiddenQuest			=	false	;	

	//	m_siItemUnique			=	0 ;			
	//	m_siItemNum				=	0 ;

	//	m_siRewardItemUnique	=	0 ;	
	//	m_siRewardItemNum		=	0 ;
	//	m_siRewardExp			=	0 ;			

	//	m_siFee					=	0 ;				
	//	m_siLeftTime			=	0 ;			

	//	m_siMakeItemNum			=	0 ;		
	//	m_bHiddenQuest			=	false;	//�⺻������ ��������Ʈ�� false
	}

	void Set(SI32 ItemUnique,SI32 ItemNum, SI32 RewardItemUnique, SI32 RewardItemNum,SI32 RewardExp,
		GMONEY Fee, SI32 LeftTime, SI32 MakeItemNum, bool HiddenQuest)
	{

		m_siItemUnique			=	ItemUnique	;
		m_siItemNum				=	ItemNum	;	
        
		m_siRewardItemUnique	=	RewardItemUnique	;
		m_siRewardItemNum		=	RewardItemNum	;
		m_siRewardExp			=	RewardExp ;
		

		m_siFee					=	Fee	;	
		m_siLeftTime			=	LeftTime	;	

		m_siMakeItemNum			=	MakeItemNum	;	
		m_bHiddenQuest			=	HiddenQuest	;	
	}

	bool IsSame( SI16 Index, SI16 Count )
	{
		if ( m_siIndex == Index && m_siCount == Count )
		{
			return true;
		}

		return false;
	}
};

#endif