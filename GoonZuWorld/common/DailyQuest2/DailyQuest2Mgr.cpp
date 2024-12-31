#include "DailyQuest2Mgr.h"
#include "DailyQuest2Obj.h"

#include "../Char/KindInfo/kindinfo.h"
#include "DailyQuest2BaseInfo.h"

#include "../Item/ItemCommon/cltItem.h"

#include "..\SMLib\LibList\LibList.h"

#include "..\CommonLogic\CommonLogic.h"
extern cltCommonLogic *pclClient;

// ���� ������ ����Ʈ ������ MAX_AVAILABLE_DAILYQUEST2_NUM=20���� �����Ѵ�.

// �������� �������� ������ ����Ʈ ������ ������( 1��� ����Ʈ 1���� �������̶�� ���� �� )
#define MAX_DAILYQUEST2_OBJ_NUM			MAX_PERSON_NUMBER

CDailyQuest2Mgr::CDailyQuest2Mgr() : CLibListMgr()
{
	m_pDailyQuest2ObjDataList = new CDailyQuest2ObjData[ MAX_AVAILABLE_DAILYQUEST2_NUM ];

	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST2_NUM; ++i )
	{
		m_pDailyQuest2ObjDataList[ i ].m_siIndex = i + 1;
		//SetDailyQuestList( i );
	}
}

CDailyQuest2Mgr::~CDailyQuest2Mgr()
{
	if ( m_pDailyQuest2ObjDataList )
	{
		delete [] m_pDailyQuest2ObjDataList;
		m_pDailyQuest2ObjDataList = NULL;
	}
}

void CDailyQuest2Mgr::Action( clock_t CurrentClock )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST2_NUM; ++i )
	{
		if ( m_pDailyQuest2ObjDataList[ i ].m_siMonsterKind == 0 )
		{
		SetDailyQuest2List( i, 0);
		m_PreClock[ i ] = CurrentClock;
		}
		else if ( TABS( CurrentClock - m_PreClock[ i ] ) > 1200000) //600000 )			// 10 �д� 1���� �ٲ���.// 20�п� �ѹ����� ����
		{
			m_pDailyQuest2ObjDataList[ i ].Init();
			m_PreClock[ i ] = CurrentClock;
		}
	}
	
	return;
}

CDailyQuest2ObjData* CDailyQuest2Mgr::GetDailyQuest2ListObj( SI16 Index, SI16 Count, SI16 *pListIndex )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST2_NUM; ++i )
	{
		if ( m_pDailyQuest2ObjDataList[ i ].m_siIndex == Index && m_pDailyQuest2ObjDataList[ i ].m_siCount == Count )
		{
			*pListIndex = i;
			return &m_pDailyQuest2ObjDataList[ i ];
		}
	}

	return NULL;
}

void CDailyQuest2Mgr::GetDailyQuest2List( CDailyQuest2ObjData* pDailyQuest2ObjDataList )
{
	memcpy( pDailyQuest2ObjDataList, m_pDailyQuest2ObjDataList, sizeof( CDailyQuest2ObjData ) * MAX_AVAILABLE_DAILYQUEST2_NUM );

	return;
}

//bool CDailyQuest2Mgr::SetDailyQuest2List( SI16 ListIndex, SI16 MonsterKind)
//{
//	// Index �����ϰ� ��� �ʱ�ȭ ( Count �� ������. )
//	m_pDailyQuest2ObjDataList[ ListIndex ].Init();
//
//	SI32 siMonsterKind		=	MonsterKind ;	// ���� ī�ε�
//	SI32 siMonsterLevel		=	0 ;
//	SI32 siExp				=	0 ;			// ���� 1������ ��� ����ġ
//	GMONEY siFee			=	0 ;			// ����Ʈ ��� ( ��� ���� )
//	SI16 siMonsterNum		=	0 ;			// ��ƾ��� ���� ����
//	SI32 siLeftTime			=	0 ;			// ����Ʈ ���� �ð�
//	SI32 siRewardItemUnique	=	0 ;			// ���� ������ ����ũ
//	SI32 siRewardItemNum	=	0 ;			// ��������� ����
//	SI32 siRewardExp		=	siExp ;		// ���� ����ġ ( ������ �̰����� ���� ���Ѵ�.���⼭�� �������ġ�� �Ѹ��� �������� ����ġ)
//	SI32 siRewardGuildPoint	=	0 ;			// ���� ��� ����ġ
//	GMONEY siRewardMoney	=	0 ;			// ���� ��
//	bool bHiddenQuest		=	false ;		// ���� ����Ʈ ���� ���� ( �⺻ false )
//	//------------------------------------------------------------------------------------------------------------------
//	// ����Ʈ ���� ����
//	//------------------------------------------------------------------------------------------------------------------
//	if ( ! pclClient->pclKindInfoSet->GetDailyQuest2KindInfo( &siMonsterKind, &siMonsterLevel, &siExp ) )
//	{
//		return false;
//	}
//	// ��ƾ��� ���� ���ڴ� 80~150 ����
//	siMonsterNum =  ( rand() % MAX_DAILYQUEST2_MONSTER_NUM ) + 80;
//	// 150������ �Ѿ�� 150 ������ ��´�
//	if (siMonsterNum >= MAX_DAILYQUEST2_MONSTER_NUM) siMonsterNum = MAX_DAILYQUEST2_MONSTER_NUM;	
//	// ���� ���� ������ �ڸ����� 10������ �����
//	siMonsterNum = siMonsterNum - ( siMonsterNum % 10 );
//	// ����Ʈ ���� �ð� ����.
//	siLeftTime = ( siExp * 1 / 4 ) * siMonsterNum/2;		// 60 �� �� ��ġ�� ���µ� �ɸ��� �ð�
//	siLeftTime = siLeftTime - ( siLeftTime % 60 ) + 60;	// �ʸ� 60���� (�� ����)�� ���߱� ���ؼ�...	
//	siLeftTime = siLeftTime - ( siLeftTime % 300 );		// ���� 5�� ������ ���߱� ���ؼ�..
//	//------------------------------------------------------------------------------------------------------------------
//	// ����Ʈ ���� ����
//	//------------------------------------------------------------------------------------------------------------------
//	if ( ! pclClient->pclItemManager->GetDailyQuest2RewardInfo( &siRewardItemUnique, &siRewardItemNum, &siRewardMoney ) )
//	{
//		return false;
//	}
//	//------------------------------------------------------------------------------------------------------------------
//	// ����Ʈ ����
//	//------------------------------------------------------------------------------------------------------------------
//	m_pDailyQuest2ObjDataList[ ListIndex ].Set( siMonsterKind, 
//												siMonsterNum, 
//												siRewardItemUnique, 
//												siRewardItemNum, 
//												siRewardMoney, 
//												siRewardExp, 
//												(GMONEY)siFee, 
//												siLeftTime, 
//												0, 
//												siRewardGuildPoint, 
//												bHiddenQuest);
//	
//	return true;
//}

bool CDailyQuest2Mgr::SetDailyQuest2List( SI16 ListIndex, SI16 MonsterKind)//, BOOL bPCRoomQuest )
{
	// Index �����ϰ� ��� �ʱ�ȭ ( Count �� ������. )
	m_pDailyQuest2ObjDataList[ ListIndex ].Init();

	SI32 siMonsterKind = MonsterKind;
	SI32 siAttackPower = 0 ;
	SI32 siExp = 0;				// ���� 1������ ��� ����ġ// SI32->SI64 ����ġ �����÷ο춧���� ����

	if ( ! pclClient->pclKindInfoSet->GetDailyQuest2KindInfo( &siMonsterKind, &siAttackPower, &siExp ) )
	{
		return false;
	}

	//���� ���ڴ� 80~150����
	SI16 siMonsterNum = ( rand() % MAX_DAILYQUEST2_MONSTER_NUM ) + 80;//�⺻ ���� ����
	if (siMonsterNum >= MAX_DAILYQUEST2_MONSTER_NUM) siMonsterNum = MAX_DAILYQUEST2_MONSTER_NUM;	
	siMonsterNum = siMonsterNum - ( siMonsterNum % 10 );				// ���� ���� 10������ ���߱� ���ؼ�..

	SI32 siRewardItemUnique = 0;
	SI32 siRewardItemNum = 0;
	SI32 siRewardExp = siExp ;
	SI32 siRewardGuildPoint = 0;// �ִ� ����ġ	
	GMONEY siRewardMoney = 0;											// �ִ� ��

	if ( ! pclClient->pclItemManager->GetDailyQuest2RewardInfo( siRewardExp * 10, &siRewardItemUnique, &siRewardItemNum, &siRewardMoney ) )
	{
		return false;
	}

	GMONEY siFee = 0 ;/*siRewardExp * 6 / 10*/;

	SI32 siLeftTime = ( siExp * 1 / 4 ) * siMonsterNum/2;		// 60 �� �� ��ġ�� ���µ� �ɸ��� �ð�
	siLeftTime = siLeftTime - ( siLeftTime % 60 ) + 60;	// �ʸ� 60���� (�� ����)�� ���߱� ���ؼ�...

	siLeftTime = siLeftTime - ( siLeftTime % 300 );		// ���� 5�� ������ ���߱� ���ؼ�..

	siRewardGuildPoint = 0;

	bool bHiddenQuest = false;

	m_pDailyQuest2ObjDataList[ ListIndex ].Set( siMonsterKind, siMonsterNum, siRewardItemUnique, siRewardItemNum, siRewardMoney, siRewardExp, (GMONEY)siFee, siLeftTime, 0, siRewardGuildPoint, bHiddenQuest);//, bPCRoomQuest );

	return true;
}
void CDailyQuest2Mgr::InitQuest2ListData( SI16 ListIndex, SI16 MonsterKind, SI16 MonsterNum, SI16 RewardItemUnique, 
										 SI16 RewardItemNum, GMONEY RewardMoney, SI32 RewardExp, 
										 GMONEY Fee, SI32 LeftTime, bool bHiddenQuest)
{
	if (pclClient->pclKindInfoSet->pclKI[MonsterKind] != NULL)
	{
		switch (pclClient->siServiceArea)
		{
		case ConstServiceArea_Korea :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_KOREA))
					return;
			}
			break;
		case ConstServiceArea_Japan :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_JAPAN))
					return;

			}
			break;
		case ConstServiceArea_China :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_CHINA))
					return;
			}
			break;
		case ConstServiceArea_English :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_ENGLISH))
					return;
			}
			break;
		case ConstServiceArea_Taiwan :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_TAIWAN))
					return;
			}
			break;
		case ConstServiceArea_USA :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_USA))
					return;
			}
			break;
		case ConstServiceArea_NHNChina :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_NHNCHINA))
					return;
			}
			break;
		case ConstServiceArea_EUROPE :
			{
				if (!(pclClient->pclKindInfoSet->pclKI[MonsterKind]->siServiceAreaAtb & SERVICEAREA_ATB_EUROPE))
					return;
			}
			break;

		}
	}
	

	if ( m_pDailyQuest2ObjDataList[ ListIndex ].m_siMonsterKind == MonsterKind &&
		m_pDailyQuest2ObjDataList[ ListIndex ].m_siMonsterNum == MonsterNum &&
		m_pDailyQuest2ObjDataList[ ListIndex ].m_siRewardItemUnique == RewardItemUnique &&
		m_pDailyQuest2ObjDataList[ ListIndex ].m_siLeftTime == LeftTime)
	{
		m_pDailyQuest2ObjDataList[ ListIndex ].Init();
	}	
	while ( ! SetDailyQuest2List( ListIndex, MonsterKind));
	m_PreClock[ ListIndex ] = pclClient->CurrentClock;
	
	return;
}
