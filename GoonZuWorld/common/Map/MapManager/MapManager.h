//---------------------------------
// 2003/7/29 ���°�
//---------------------------------

#ifndef _MAPMANAGER_H
#define _MAPMANAGER_H

#include <Directives.h>
#include "..\Map.h"

#include "../../../common/CommonHeader.h"

#include "../NetworkLib/ITZNetLib/ITZWorld.h"
#include "../NLib/NUpdateTimer.h"
#include "..\..\..\Server\ServerMap\ServerMap.h"


#define MAX_MAP_NAME_SIZE					32

#define GATESTART_INSTANCEMAP				600

#define INSTANCEMAP_MAX_TIME				1800000				// (30 * 60 * 1000) 30��(���ĸ��� ���ӽð�)
#define	INSTANCEMAP_PIRATESHIP_MAX_TIME		1800000				// (30 * 60 * 1000) 30��(������ �⺻ ���ӽð�)
#define INSTANCEMAP_PIRATESHIP_BONUSTIME	300000				// (5 * 60 * 1000)	5��(������ ���ʽ� �ð�)
#define INSTANCEMAP_SERVEREVENT_MAX_TIME	3600000				// (60 * 60 * 1000)	60��(�����̺�Ʈ ����Ʈ ���ӽð�)

#define INSTANCEMAP_PIRATESHIP_MAX_GATE		12					// ������ ����Ʈ �� ����

class cltVillageManager;
class cltCommonLogic;
class cltCharServer;

#include "MapTypeManager.h"
#include "../GateManager/GateManager.h"
#include "../GateManager/InstanceMapGateManager.h"

//----------------------------------------
// ���� ������ �ּ� ����. 
//---------------------------------------
class cltUnitMapBasicInfo{
public:
	TCHAR	szMapName[ MAX_MAP_NAME_SIZE ];
	TCHAR	szBGMFileName[ 256 ];
	SI32	siMapUnique;
	SI32	siLevelLimit;
	SI32	siMinLevel;
	SI32	siMaxLevel;
	bool	bBlockWarp;
	SI32	siVillageUnique;
	SI32	siParentMap;
	bool	bEncountMap;
	bool	bSeaMap;
	bool	bLandMap;
	bool	bFogMap;
	SI16	siInstanceMap;	// �ν��Ͻ��� Ÿ�� (enum INSTANCEMAP_TYPE)
	bool	bGuildMap;
	bool	bPkMap;
	bool	bHaveCloneMap;
	SI32	siCloneIndex;
	SI32	siUserLimit;
	SI32	siUserCount;
	bool	bCanMarket;		// [����] ������ �����ִ� �����ΰ�?

	cltUnitMapBasicInfo()
	{
		ZeroMemory( this, sizeof( cltUnitMapBasicInfo ) );
	}
	
};

class cltCloneMapInfo
{
public:
	SI32	siSrcMapIndex;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, CLONEMAP_NUM>		siDstMapIndex;
#else
	SI32	siDstMapIndex[CLONEMAP_NUM];
#endif

	bool	AddCloneMap( SI32 dstMapIndex )
	{
		for ( SI32 i=0; i<CLONEMAP_NUM; ++i )
		{
			if ( siDstMapIndex[i] == 0 ) 
			{
				siDstMapIndex[i] = dstMapIndex;
				return true;
			}
		}
		return false;
	}

	cltCloneMapInfo()
	{
		ZeroMemory( this, sizeof( cltCloneMapInfo ) );
	}
};

class cltMapManager
{
public:
	cltMapManager(SI32 gamemode, SI32 servicearea, cltVillageManager* pclvillagemanager);
	~cltMapManager();


	//-------------------------------------------
	// LoadMap
	//-------------------------------------------
	bool		LoadMap(cltCommonLogic* pclclient, SI32 mapunique, SI32 index,SI32 villageunique,
						SI32 parentmap, SI32 levellimit, TCHAR* mapname,
						BOOL encountmap = FALSE, BOOL seamap = FALSE, BOOL landmap = FALSE );
	BOOL		LoadMap(cltCommonLogic* pclclient, SI32 srcmapindex, SI32 mapunique);	// mapindex�� ����Ͽ� ������ �ҷ��´�. 
	BOOL		LoadAllMap(cltCommonLogic* pclclient);				// ��� ������ �� �о�´�. 
	void		LoadMapName(SI32 servicearea);						// ���� �̸��� �ҷ��� �����Ѵ�. 

	// ������ �ҷ��´�. 
	cltMapCommon* Load(SI32 mapindex, SI32 mapunique, TCHAR* filename, cltCharManager* pclcm, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager);


	bool		DeleteAllMap();
	
	bool		SetCurrentMapIndex(SI32 index);
	SI32		GetVillageUnique(SI32 index);

	SI32		GetMapIndexFromVillageUnique(SI32 villageunique);	// ���� ����ũ�� ������ �ش� ������ �ε����� ã�´�. 
	SI32		GetMapIndexFromName(TCHAR* name);					// ���� �̸��� ������ ������ �ε����� ã�´�. 

	cltMapCommon* GetMapPointer(SI32 index);

	bool		MakeLastMap(SI32 mapindex);

	bool		IsValidArea( SI32 mapindex, SI32 x, SI32 y );		// ��ȿ�� �����ΰ�. 

	bool		IsEncountMap(SI32 mapindex);
	bool		IsInstanceMap(SI32 mapindex);
	bool		IsSeaMap(SI32 mapindex);
	bool		IsLandMap(SI32 mapindex);
	bool		IsFogMap(SI32 mapindex);
	bool		IsHuntMap( SI32 siMapIndex );						// ���ƿ� �����ΰ�
	bool		IsGuildMap( SI32 mapindex );						// ��� ������ ������ �����ΰ�
	bool		IsPartyMap( SI32 siMapIndex );						// [����] ������ : ��Ƽ���� �δ� ���ΰ�
	bool		IsCanMarketOpenMap( SI32 siMapIndex );				// [����] ������ �� �� �ִ� �����ΰ�?
	
	//----------------------------------------------------------------
	// �������� �⺻ ���� ���� 
	//----------------------------------------------------------------
	void		SetMapBasicInfo(SI32 mapindex, SI32 mapunique, SI32 villageunique, 
								SI32 minlevel, SI32 maxlevel,
								bool blockwarp,
								SI32 parentmap, bool encountmap, 
								bool seamap, bool landmap,bool fogmap,
								SI16 instancemap, bool guildmap, bool pkMap,
								SI32 userlimit, 
								bool bCanMarket);
	
	SI32		GetParentMap(SI32 mapindex);
	bool		IsPkMap(SI32 MapIndex);
	SI32		GetLevelLimit(SI32 mapindex);
	SI32		GetMinLevel(SI32 mapindex);
	SI32		GetMaxLevel(SI32 mapindex);
	bool		IsEnterLevel(SI32 mapindex, SI32 level);
	bool		IsBlockWarp(SI32 mapindex);	// ������ ���� ���� ���� ���� ���̴�.
	void		SetBGM( SI32 mapindex, TCHAR* filename );
	void		SetMapName(SI32 mapindex, TCHAR* pname);
	TCHAR*		GetMapName(SI32 mapindex);
	SI32		GetMapUnique(SI32 mapindex);						// ������ ����ũ�� ��´�.
	void		AddCloneMap(SI32 srcMapIndex, SI32 dstMapIndex);
	bool		HaveCloneMap(SI32 mapindex);
	SI32		GetUserLimit(SI32 mapindex);
	SI32		GetCloneMap(SI32 mapindex);

	// �������� ����߸� ������ ���� ã�´�. 
	bool		FindProperAreaForDrop(SI32 mapindex, SI32 x, SI32 y, SI32* ptargetx, SI32* ptargety);

	void		InitUserCount();
	void		AddUserCount( SI32 mapindex );
	SI32		GetUserCount( SI32 mapindex );

	SI32		GetSourceMap( SI32 clonemapindex );

	//---------------------------------------------------------
	//	�ν��Ͻ� ���� ����
	//---------------------------------------------------------
	
	void		Init();	

	bool		EnterInstanceMap( SI32 mapindex, cltCharServer* pclchar );
	void		InitInstanceMap( SI32 mapindex );
	void		MakeInstanceMapGate( SI32 parentmapindex );
	void		LeaveInstanceMap( IN SI32 siMapIndex, OUT SI32* psiInCharID=NULL );

	void		SendInInstanceMapUser( SI32 siParentMap, sPacketHeader* psPacketHeader );

	// Get ����
	SI32		GetEnterableInstanceMapIndex( SI32 siMapIndex, cltCharServer* pclchar );
	SI32		GetUserCountByParentMap( SI32 mapindex );
	SI32		GetUserCountByMapIndex( SI32 siMapIndex );
	SI16		GetInstanceMapType( SI32 siMapIndex );
	SI08		GetInstanceMapPartyList( IN SI32 siPartyIndex, OUT SI32* psiPartyList );
	
	// ���� ó�� ����
	void		Action();

	void		ActionFor_GuildInstanceMap( SI32 siMapIndex, SI16 siMapType );
	void		ActionFor_PartyInstanceMap( SI32 siMapIndex, SI16 siMapType );
	void		ActionFor_VillageInstanceMap( SI32 siMapIndex, SI16 siMapType );
	void		ActionFor_ServerInstanceMap( SI32 siMapIndex, SI16 siMapType );

	// ��Ƽ�� ���� ����
	void		SendPartyInInstanceMapUser( SI32 siPartyIndex, sPacketHeader* psPacketHeader );
	void		GiveItemForPartyMapClear( SI32 siPartyIndex );
	void		PirateShipGateProcess();
	void		ChirstmasEventGateProcess();

	// �����̺�Ʈ �δ�����
	void		SendServrEventInstanceMapInfo( SI32 siParentMap );

	// ���� �̺�Ʈ (FALSE = NPC���ֱ�, TRUE = NPC�����) 
	void		FestivalEventGateProcess(BOOL bBeingNPC);


public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltUnitMapBasicInfo, MAX_MAP_NUMBER>	clUnitMapInfo;
	NSafeTArray<cltCloneMapInfo, MAX_CLONEMAP_TYPE>		clCloneMapInfo;
#else
	cltUnitMapBasicInfo		clUnitMapInfo[ MAX_MAP_NUMBER ];	
	cltCloneMapInfo			clCloneMapInfo[ MAX_CLONEMAP_TYPE ];
#endif

	cltVillageManager*		pclVillageManager;

	cltMapTypeManager*		pclMapTypeManager;
	cltGateManager*			pclGateManager;

	cltInstanceMapGateManager*	pclInstanceMapGateManager;
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltMapCommon*, MAX_MAP_NUMBER>		pclMapArray;
#else
	cltMapCommon*			pclMapArray[ MAX_MAP_NUMBER ];
#endif
	
	cltMapCommon*			pclCurrentMap;
	SI32					CurrentMapIndex;	

	SI32					GameMode;

	// ����� �ʰ��� 
	ITZWorld< cltServerMap >		m_world;

	// ���� ������ ��ġ. 
	BOOL					DlgRectInitSwitch;
	RECT					DlgRect;

	// Ÿ�̸�
	NUpdateTimer			m_UpdateTimer_Action;
	
	// [����] ����Ʈ�� ������ �ϴ� NPC�� ID
	SI32					m_siGatePositionID;
	SI32					m_siChristmasGatePositionID;
	SI32					m_siFestivalGatePositionID;

};


#endif
