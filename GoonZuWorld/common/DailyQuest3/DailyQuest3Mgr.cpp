#include "DailyQuest3Mgr.h"
#include "DailyQuest3Obj.h"

#include "../Item/ItemCommon/cltItem.h"

#include "..\SMLib\LibList\LibList.h"

#include "..\CommonLogic\CommonLogic.h"
extern cltCommonLogic *pclClient;

#define MAX_DAILYQUEST3_MONSTER_NUM			150			// DailyQuest ���� �ִ��
// ���� ������ ����Ʈ ������ MAX_AVAILABLE_DAILYQUEST2_NUM=20���� �����Ѵ�.
// �������� �������� ������ ����Ʈ ������ ������( 1��� ����Ʈ 1���� �������̶�� ���� �� )
#define MAX_DAILYQUEST3_OBJ_NUM			MAX_PERSON_NUMBER

CDailyQuest3Mgr::CDailyQuest3Mgr() : CLibListMgr()
{
	m_pDailyQuest3ObjDataList = new CDailyQuest3ObjData[ MAX_AVAILABLE_DAILYQUEST3_NUM ];

	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST3_NUM; ++i )
	{
		m_pDailyQuest3ObjDataList[ i ].m_siIndex = i + 1;
	}
}

CDailyQuest3Mgr::~CDailyQuest3Mgr()
{
	if ( m_pDailyQuest3ObjDataList )
	{
		delete [] m_pDailyQuest3ObjDataList;
		m_pDailyQuest3ObjDataList = NULL;
	}
}

void CDailyQuest3Mgr::Action( clock_t CurrentClock )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST3_NUM; ++i )
	{
		if ( m_pDailyQuest3ObjDataList[ i ].m_siItemUnique == 0 )
		{
			SetDailyQuest3List( i, 0);
			m_PreClock[ i ] = CurrentClock;
		}
		else if ( TABS( CurrentClock - m_PreClock[ i ] ) >120000)	// 10 �д� 1���� �ٲ���.// 20�п� �ѹ����� ����
		{
			m_pDailyQuest3ObjDataList[ i ].Init();
			m_PreClock[ i ] = CurrentClock;
		}
	}
	
	return;
}

CDailyQuest3ObjData* CDailyQuest3Mgr::GetDailyQuest3ListObj( SI32 Index, SI32 Count, SI32 *pListIndex )
{
	for ( SI16 i = 0; i < MAX_AVAILABLE_DAILYQUEST3_NUM; ++i )
	{
		if ( m_pDailyQuest3ObjDataList[ i ].m_siIndex == Index && m_pDailyQuest3ObjDataList[ i ].m_siCount == Count )
		{
			*pListIndex = i;
			return &m_pDailyQuest3ObjDataList[ i ];
		}
	}

	return NULL;
}

void CDailyQuest3Mgr::GetDailyQuest3List( CDailyQuest3ObjData* pDailyQuest3ObjDataList )
{
	memcpy( pDailyQuest3ObjDataList, m_pDailyQuest3ObjDataList, sizeof( CDailyQuest3ObjData ) * MAX_AVAILABLE_DAILYQUEST3_NUM );

	return;
}
//---------------------------------------------------------------------------------------------------------------------------------
// �ҿ� ����Ʈ ( DailyQuest3 ) ����.
bool CDailyQuest3Mgr::SetDailyQuest3List( SI32 ListIndex, SI16 Itemunique)
{
	// Index �����ϰ� ��� �ʱ�ȭ ( Count �� ������. )
	m_pDailyQuest3ObjDataList[ ListIndex ].Init();
	//---------------------------------------------------------------------------------------------------------------------------------
	// �ʿ� ���� ����
	//---------------------------------------------------------------------------------------------------------------------------------
	bool bHiddenQuest		=	false ;		//	���� ����Ʈ ���� (�⺻ false)
	SI16 siItemUnique		=	Itemunique ;//	���� ������ ����ũ
	SI16 siMakeItemNum		=	0 ;			//	�������ϴ� ������ ����
	SI16 siMakedItemNum		=	0 ;			//	���� ������ ����
	SI16 siRewardItemUnique	=	0 ;			//	���� ������ ����ũ
	SI16 siRewardItemNum	=	0 ;			//	���� ������ ����
	SI32 siRewardExp		=	0 ;			//	���� ����ġ
	SI32 SkillLevelLimit	=	0 ;			//	�ش� �������� ���۱�� ����
	SI32 siLeftTime			=	0 ;			//	����Ʈ ������ ���� �ð� ����
	
	SI16 SpecialMat			=	0 ;			//	��� ���� Ȯ��.
	GMONEY siFee			=	0 ;			//	����Ʈ ��������� ������ �������� ����ϴ� ���. ������ ���� �ʴ´�.
	//---------------------------------------------------------------------------------------------------------------------------------
	// ���� �������� ����
	//---------------------------------------------------------------------------------------------------------------------------------
	if ( ! pclClient->pclItemManager->GetDailyQuest3KindInfo( &siItemUnique, &siMakeItemNum ) )
	{
		return false;
	}
    // ���� �������� Ref �� ��� ������ ���Ѵ�.
	SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( siItemUnique );
	if (Ref <= 0) return false ;
	SkillLevelLimit = pclClient->pclItemManager->pclItemInfo[Ref]->clSkillInfo.siSkillLevel; // ���۱��Lev
	if (SkillLevelLimit <= 0) return false;
	// ���� �ð� ����.
	siLeftTime = SkillLevelLimit * siMakeItemNum *30 ;
	siLeftTime = siLeftTime - ( siLeftTime % 60 ) + 60;	// �ʸ� 60���� (�� ����)�� ���߱� ���ؼ�...
	siLeftTime = siLeftTime - ( siLeftTime % 300 );		// ���� 5�� ������ ���߱� ���ؼ�..
	
	//---------------------------------------------------------------------------------------------------------------------------------
	// ���� ������ ����
	//---------------------------------------------------------------------------------------------------------------------------------
	if ( ! pclClient->pclItemManager->GetDailyQuest3RewardInfo( &siRewardExp, siMakeItemNum, &siRewardItemUnique, &siRewardItemNum, SkillLevelLimit ) )
	{
		return false;
	}
	//---------------------------------------------------------------------------------------------------------------------------------
	// ���� Ȯ���� ���� ���Ḧ �ش�.
	//---------------------------------------------------------------------------------------------------------------------------------
	// 5������ Ȯ���� ���� ��Ḧ �ش�.
	//---------------------------------------------------------------------------------------------------------------------------------
	SpecialMat = rand() % 100;
	if( SpecialMat == 45 ||SpecialMat == 13 || SpecialMat == 89 || SpecialMat == 65 ||	SpecialMat == 49 ){
		SI16 specialitemnum = rand()%11+5;
        switch(rand()%3) {			 
			case 0:
				siRewardItemUnique = ITEMUNIQUE(5380);
				siRewardItemNum = specialitemnum;
				if (siRewardItemNum > 10) {
					siRewardItemNum = 10;
				}
				break;
			case 1:
				siRewardItemUnique = ITEMUNIQUE(7175);
				siRewardItemNum = specialitemnum;
				if (siRewardItemNum > 10) {
					siRewardItemNum = 10;
				}
				break;
			case 2:
				siRewardItemUnique = ITEMUNIQUE(6140);
				siRewardItemNum = specialitemnum;
				if (siRewardItemNum > 10) {
					siRewardItemNum = 10;
				}
				break;
			}
	}
	// ���� ���� ��а� ������ �ʵ��� �մϴ�.
	////---------------------------------------------------------------------------------------------------------------------------------
	//// 3 ���� Ȯ���� õ���� ���
	////---------------------------------------------------------------------------------------------------------------------------------
	//if ( SpecialMat == 1 || SpecialMat == 19 || SpecialMat == 72 ) {
	//	siRewardItemUnique = ITEMUNIQUE(8064);
	//	siRewardItemNum = rand()%4+2;
	//	if (siRewardItemNum > 5) {
	//		siRewardItemNum = 5;
	//	}
	//}
	////---------------------------------------------------------------------------------------------------------------------------------
	//// 1���� Ȯ���� �Ǹ��� ���
	////---------------------------------------------------------------------------------------------------------------------------------
	//if ( SpecialMat == 73) { 
	//	siRewardItemUnique = ITEMUNIQUE(8066);
	//	siRewardItemNum = rand()%4+2;
	//	if (siRewardItemNum > 3) {
	//		siRewardItemNum = 3;
	//	}
	//}

	//---------------------------------------------------------------------------------------------------------------------------------
	// m_pDailyQuest3ObjDataList ����
	//---------------------------------------------------------------------------------------------------------------------------------
	m_pDailyQuest3ObjDataList[ ListIndex ].Set(siItemUnique, siMakeItemNum, siRewardItemUnique,siRewardItemNum, siRewardExp,
		 siFee, siLeftTime, siMakedItemNum, bHiddenQuest);
	
	return true;
}

void CDailyQuest3Mgr::InitQuest3ListData( SI32 ListIndex, SI16 ItemUnique, SI16 siItemNum, SI16 RewardItemUnique, 
										 SI16 RewardItemNum, GMONEY Fee, SI32 LeftTime,SI32 RewardExp, bool bHiddenQuest){

	SI32 Ref = pclClient->pclItemManager->FindItemRefFromUnique( ItemUnique );

	if (pclClient->pclItemManager->pclItemInfo[Ref] == NULL) return;
	
	if ( m_pDailyQuest3ObjDataList[ ListIndex ].m_siItemUnique  == ItemUnique &&
		m_pDailyQuest3ObjDataList[ ListIndex ].m_siItemNum  == siItemNum &&
		m_pDailyQuest3ObjDataList[ ListIndex ].m_siRewardExp  == RewardExp &&
		m_pDailyQuest3ObjDataList[ ListIndex ].m_siRewardItemNum== RewardItemNum &&
		m_pDailyQuest3ObjDataList[ ListIndex ].m_siRewardItemUnique  == RewardItemUnique)
	{
		m_pDailyQuest3ObjDataList[ ListIndex ].Init();
	}
	
	while ( ! SetDailyQuest3List( ListIndex, ItemUnique));
	m_PreClock[ ListIndex ] = pclClient->CurrentClock;
	
	return;
}
