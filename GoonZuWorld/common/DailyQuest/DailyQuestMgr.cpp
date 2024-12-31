#include "DailyQuestMgr.h"
#include "DailyQuestObj.h"

#include "../Char/KindInfo/kindinfo.h"
#include "DailyQuestBaseInfo.h"

#include "../Item/ItemCommon/cltItem.h"

#include "..\SMLib\LibList\LibList.h"

#include "..\CommonLogic\CommonLogic.h"
extern cltCommonLogic *pclClient;

// ���� ������ ����Ʈ ������ MAX_AVAILABLE_DAILYQUEST_NUM=20���� �����Ѵ�.

// �������� �������� ������ ����Ʈ ������ ������( 1��� ����Ʈ 1���� �������̶�� ���� �� )
#define MAX_DAILYQUEST_OBJ_NUM			MAX_PERSON_NUMBER

CDailyQuestMgr::CDailyQuestMgr() : CLibListMgr()
{
	m_pDailyQuestObjDataList = new CDailyQuestObjData[ MAX_AVAILABLE_DAILYQUEST_NUM ];

	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST_NUM; ++i )
	{
		m_pDailyQuestObjDataList[ i ].m_siIndex = i + 1;
		//SetDailyQuestList( i );
	}
}

CDailyQuestMgr::~CDailyQuestMgr()
{
	if ( m_pDailyQuestObjDataList )
	{
		delete [] m_pDailyQuestObjDataList;
		m_pDailyQuestObjDataList = NULL;
	}
}

void CDailyQuestMgr::Action( clock_t CurrentClock )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST_NUM; ++i )
	{
		if ( m_pDailyQuestObjDataList[ i ].m_siMonsterKind == 0 )
		{
			//int pcroom = 0;
//			for( int j = 0; j < MAX_AVAILABLE_DAILYQUEST_NUM; ++j ) {
//				if( m_pDailyQuestObjDataList[ j ].m_bPCRoomQuest ) pcroom++;
//			}

//			if( pcroom < 5 ) {
//				SetDailyQuestList( i, 0, TRUE );
//			} else {
				SetDailyQuestList( i, 0);//, FALSE );
//			}
			m_PreClock[ i ] = CurrentClock;
		}
		else if ( TABS( CurrentClock - m_PreClock[ i ] ) > 600000 )			// 10 �д� 1���� �ٲ���.
		{
			m_pDailyQuestObjDataList[ i ].Init();
			m_PreClock[ i ] = CurrentClock;
		}
	}
	
	return;
}

CDailyQuestObjData*	CDailyQuestMgr::GetDailyQuestListObj( SI16 Index, SI16 Count, SI16 *pListIndex )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST_NUM; ++i )
	{
		if ( m_pDailyQuestObjDataList[ i ].m_siIndex == Index && m_pDailyQuestObjDataList[ i ].m_siCount == Count )
		{
			*pListIndex = i;
			return &m_pDailyQuestObjDataList[ i ];
		}
	}

	return NULL;
}

void CDailyQuestMgr::GetDailyQuestList( CDailyQuestObjData* pDailyQuestObjDataList )
{
	memcpy( pDailyQuestObjDataList, m_pDailyQuestObjDataList, sizeof( CDailyQuestObjData ) * MAX_AVAILABLE_DAILYQUEST_NUM );

	return;
}

bool CDailyQuestMgr::SetDailyQuestList( SI16 ListIndex, SI16 MonsterKind)//, BOOL bPCRoomQuest )
{
	// Index �����ϰ� ��� �ʱ�ȭ ( Count �� ������. )
	m_pDailyQuestObjDataList[ ListIndex ].Init();

	//m_pDailyQuestObjDataList[ ListIndex ].m_siMonsterKind

	SI32 siMonsterKind = MonsterKind;
	SI32 siAttackPower = 0 ;
	SI32 siExp = 0;				// ���� 1������ ��� ����ġ

	if ( ! pclClient->pclKindInfoSet->GetDailyQuestKindInfo( &siMonsterKind, &siAttackPower, &siExp ) )
	{
		return false;
	}

	// �ּ� 10 ����
	SI16 siMonsterNum = ( rand() % MAX_DAILYQUEST_MONSTER_NUM ) + 20;

	siMonsterNum = siMonsterNum - ( siMonsterNum % 10 );				// ���� ���� 10������ ���߱� ���ؼ�..
	
	SI32 siRewardItemUnique = 0;
	SI32 siRewardItemNum = 0;
	SI32 siRewardExp = siExp * siMonsterNum * 0.7;						// �ִ� ����ġ�� �ϴ� �⺻ ���� ����ġ�� �־� �ش�.
																		// ����ġ�� ���� ����Ʈ�� ������ ���Ѵ�.
	GMONEY siRewardMoney = 0;											// �ִ� ��

	siRewardExp = siRewardExp - ( siRewardExp % 100 ) + 100;
	if ( siRewardExp < 100 )
	{
		siRewardExp = 100;
	}

	if ( ! pclClient->pclItemManager->GetDailyQuestRewardInfo( siRewardExp * 10, &siRewardItemUnique, &siRewardItemNum, &siRewardMoney ) )
	{
		return false;
	}

	//siRewardItemNum = siRewardItemNum - ( siRewardItemNum % 10 ) + 10;		// ������ 10 ������ ���߱� ���ؼ�...

	GMONEY siFee = siRewardExp * 6 / 10;

	siFee = siFee - ( siFee % 100 ) + 100;

	if ( siFee < 100 )
	{
		siFee = 100;
	}

	//SI32 siLeftTime = ( siExp / 3 + 10 ) * siMonsterNum;
	SI32 siLeftTime = ( siExp * 1 / 2 ) * siMonsterNum + 60;		// 60 �� �� ��ġ�� ���µ� �ɸ��� �ð�
	siLeftTime = siLeftTime - ( siLeftTime % 60 ) + 60;	// �ʸ� 60���� (�� ����)�� ���߱� ���ؼ�...
	
	siLeftTime = siLeftTime - ( siLeftTime % 300 );		// ���� 5�� ������ ���߱� ���ؼ�.. (������ �ð��� ����, �ð��� �� �˳��Ѱ� ���Ƽ�... )

	if ( siLeftTime < 300 )
	{
		siLeftTime = 300;
	}

//	if( bPCRoomQuest ) siRewardItemNum = siRewardItemNum * 3;
	
	m_pDailyQuestObjDataList[ ListIndex ].Set( siMonsterKind, siMonsterNum, siRewardItemUnique, siRewardItemNum, siRewardMoney, siRewardExp, (GMONEY)siFee, siLeftTime, 0);//, bPCRoomQuest );
	
	return true;
}

void CDailyQuestMgr::InitQuestListData( SI16 ListIndex, SI16 MonsterKind, SI16 MonsterNum, 
									   SI16 RewardItemUnique, SI16 RewardItemNum, GMONEY RewardMoney, 
									   SI32 RewardExp, GMONEY Fee, SI32 LeftTime)//, BOOL bPCRoomQuest )
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
	

	if ( m_pDailyQuestObjDataList[ ListIndex ].m_siMonsterKind == MonsterKind &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siMonsterNum == MonsterNum &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siRewardItemUnique == RewardItemUnique &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siRewardItemNum == RewardItemNum &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siRewardExp == RewardExp &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siRewardMoney == RewardMoney &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siFee == Fee &&
		m_pDailyQuestObjDataList[ ListIndex ].m_siLeftTime == LeftTime )
//		m_pDailyQuestObjDataList[ ListIndex ].m_bPCRoomQuest == bPCRoomQuest )
	{
		m_pDailyQuestObjDataList[ ListIndex ].Init();
	}
	
	while ( ! SetDailyQuestList( ListIndex, MonsterKind));//, bPCRoomQuest ) );
	m_PreClock[ ListIndex ] = pclClient->CurrentClock;
	
	return;
}
