#ifndef _FISHKIND_H_
#define _FISHKIND_H_

#include "FishingBaseInfo.h"

struct stFishInfo
{
	SI32 siNeedFishingSkillLevel;									// �� ����⸦ ���� ���� �ּ� ��� ����

	SI32 siIncFishingSkillExp;										// ��� ����ġ ȹ��

	SI32 siCatchPercent;											// �� ����⸦ ���� Ȯ��
	SI32 siIncCatchPercentFromSkillLevel;							// ��ų ������ ���� ������ ���

	SI32 siFishingRodAtb;											// ���Ǵ� ���õ��� ����
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_FISHING_TOOL_NUMBER>		siFishingToolItemUniqueList;
	NSafeTArray<SI32, MAX_BAIT_ITEM_NUMBER>			siBaitItemUniqueList;
	NSafeTArray<SI32, FISHING_PLACE_END>			siFishCreatePlaceList;
	NSafeTArray<RECT, MAX_CREATE_FISH_PLACE_LIST>	FishCreatePlaceRectList;
#else
	SI32 siFishingToolItemUniqueList[ MAX_FISHING_TOOL_NUMBER ];	// ���õ��� ����Ʈ
	SI32 siBaitItemUniqueList[ MAX_BAIT_ITEM_NUMBER ];				// �� ����⸦ ���� ���ؼ� �ʿ��� �̳� ����Ʈ.
	SI32 siFishCreatePlaceList[ FISHING_PLACE_END ];				// �� ����Ⱑ ��ȹ �����Ѱ�( ��, ����, ����, ���� )
	RECT FishCreatePlaceRectList[MAX_CREATE_FISH_PLACE_LIST];		// �� ����Ⱑ ��Ÿ���� �� ( Ÿ�� ��ǥ )
#endif
	
	stFishInfo()
	{
		Init();
	}

	void Init()
	{
		memset ( this, 0, sizeof( stFishInfo ) );
	}

	void Set( stFishInfo *pFishInfo )
	{
		memcpy( this, pFishInfo, sizeof( stFishInfo ) );
	}
};

// �ػ깰 ������ ���� ����
// ��� ( ��, �ؾȰ�, ����, ���� )
// ��ų �� ���� ���� �� �ִ���?
// �� %�� Ȯ���� ���̴���... �� �׷� ������..
class CFishKind
{
public:
	CFishKind();
	~CFishKind();

	void Init();

	void SetFishKindInfo
		(
		SI32 FishItemUnique,
		SI32 NeedFishingSkillLevel,
		SI32 IncFishingSkillExp,
		SI32 CatchPercent, 
		SI32 IncCatchPercentFromSkillLevel,
		TCHAR *FishName, 
		TCHAR *FishingToolAtb, 
		TCHAR *FishingToolList, 
		SI32 BaitItemUnique,
		TCHAR *FishCreatePlaceList,
		TCHAR *FishCreatePlaceRectList
		);

	void AnalyzeFishingToolAtb( TCHAR *FishingToolAtb );
	void AnalyzeFishingToolList( TCHAR *FishingToolList );
	void AnalyzeBaitItemUniqueList( TCHAR *BaitItemUniqueList );
	void AnalyzeFishCreatePlaceList( TCHAR *FishCreatePlaceList );
	void AnalyzeFishCreatePlaceRectList( TCHAR *FishCreatePlaceRectList );


	SI32 GetFishItemUnique();
	bool IsSameFishItemUnique( SI32 FishItemUnique );

	stFishInfo *GetFishInfoPtr();
	bool GetFishInfo( stFishInfo *pFishInfo );

	// � X, Y ��ǥ���� � �̳��� �� ����⸦ ȹ���Ҽ� �ִ���?
	bool IsAvailableGainFish( SI32 FishingBaitItemUnique, SI32 PosX, SI32 PosY );
	bool IsAvailableGainFish( SI32 PosX, SI32 PosY );
	bool IsAvailableBait( SI32 BaitItemUnique );

	SI16 GetCatchFishPercent( SI16 FishSkillLevel, SI16 FishingBaitItemUnique );
	SI32 CatchFish( SI32 FishSkillLevel, SI32 CatchPercent, SI16 SpecialIncreaseSkillLevel );

	SI32 *GetFishingToolItemUniqueListPtr();


	stFishInfo	m_stFishInfo;

private:

	SI32		m_siFishItemUnique;
	TCHAR		m_strFishName[ MAX_PLAYER_NAME ];	
};


#endif