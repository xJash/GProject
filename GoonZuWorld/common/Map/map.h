#ifndef _MAP_H
#define _MAP_H     1

#include <windows.h>
#include <ddraw.h>
#include "../Map\TileSet\TileSet.h"
//#include "Map\FieldObject\FieldObject.h"
#include "..\..\Client\Cloud\CloudMgr.h"
#include "..\..\Client\Effect\WaterDrop\WaterDropMgr.h"
#include "..\..\Client\Effect\SeedDrop\SeedDropMgr.h"

// ��Ʈ��ũ�� ���. 
#include "..\..\NetworkLib\ITZNetLib\ITZNetworkThread.h"
#include "..\..\NetworkLib\ITZNetLib\ITZPerson.h"
#include "..\..\NetworkLib\ITZNetLib\ITZListen.h"

#include "../../CommonLogic/Guild/Guild.h"

#include "MapLayor\Map-Layor.h"

class CAStarListMgr;

class _MoveMark;
class cltCharManager;
class cltServerMap;
class cltMapCommon;
class CFireFlyMgr;
class CIceFlashMgr;
class cltHelpManager;
class cltFieldObjectManager;
class cltClient;

#define MAP_TILE_XSIZE			80
#define MAP_TILE_XSIZE_HALF		40
#define MAP_TILE_YSIZE			40
#define MAP_TILE_YSIZE_HALF		20

#define MAX_MAP_LAYER			2
#define MOUSETILEATB_FARM		1


//--------------------------------------------------
// �浹 �Ӽ� 
//--------------------------------------------------
// 0x1000���� ���۵ȴ�. 
#define BLOCK_CHAR							((DWORD)1<<12)      // ĳ������ �Ӽ� 10������ 4096
#define BLOCK_SYSTEMNPC						((DWORD)1<<14)		//

#define BLOCK_NONE							((DWORD)1)
#define BLOCK_DEEPWATER						((DWORD)1<<1)
#define BLOCK_SHALLOWWATER					((DWORD)1<<2)
#define BLOCK_NORMAL						((DWORD)1<<3)
#define BLOCK_LAND							((DWORD)1<<4)
#define BLOCK_CUSTOM						((DWORD)1<<5)		// ���� ������ ���� �浹 ����. (��ġ ����Ǹ� �ȵ�) 
#define BLOCK_EVENT1						((DWORD)1<<6)		// �̺�Ʈ ���� �浹 ����( ��ġ ����Ǹ� �ȵ�)
#define BLOCK_EVENT2						((DWORD)1<<7)		// �̺�Ʈ ���� �浹 ����( ��ġ ����Ǹ� �ȵ�)
#define BLOCK_EVENT3						((DWORD)1<<8)		// �̺�Ʈ ���� �浹 ����( ��ġ ����Ǹ� �ȵ�)
#define BLOCK_EVENT4						((DWORD)1<<9)
#define BLOCK_EVENT5						((DWORD)1<<10)
#define BLOCK_EVENT6						((DWORD)1<<11)
#define BLOCK_EVENT7						((DWORD)1<<13)
	

//-------------------------------------------------
// �ֿ����� MapIndex
//-------------------------------------------------
#define MAPINDEX_MAINFIELD						0			// �����ʵ� 
#define MAPINDEX_BEGINNER1						108			// �ʺ��ڻ����1
#define MAPINDEX_PALACE							158			// ���縮��.

//#define MAPINDEX_BATTLESEA					162			// ������ո�
//#define MAPINDEX_DOCKDO						171			// ����
#define MAPINDEX_MASTERWORLD					329			// ���ڳ���
//#define MAPINDEX_DAEMADOGATE					173			// �븶�������ұ��Ա�
//#define MAPINDEX_DAEMADO						300			// �븶��

//#define MAPINDEX_CHINABORDER					176
//#define MAPINDEX_BEGINNER2					177			// �ʺ��ڻ����2

#define MAPINDEX_TRADINGPORT					179			// ������

#define MAPINDEX_GUILDWARFIELD					195			// ����� �ʵ� 195~199	->	���� ����� �ʵ�� ������Ű�� ���ο� ��������� ����Ѵ�

#define MAPINDEX_GUILDWARFIELD_OLD				369			// ����� �ʵ� 369~371 -> �Ϲ� ������� 3���� ��� �Ǹ鼭 ����� ���� �ű��.

#define MAPINDEX_MOFUMOFULAND					103			// ���ĸ��� ���� �̺�Ʈ ��

#define MAPINDEX_MOFUMOFU_AGIT					320			// ���ĸ��� ����Ʈ �δ�

#define MAPINDEX_PIRATESHIP						330			// ������ ��Ƽ�� �δ� ��

#define MAPINDEX_PRIVATEMARKETAREA				95			// ���λ��� ����
#define MAPINDEX_FESTIVAL						97			// ������ ����

#define MAX_INSTANCE_MAP_NUMBER					5			// �ν��Ͻ� ������ ��
#define MAX_INSTANCE_BONUS_MONSTER_NUMBER		3			// �ν��Ͻ� ���� ������ ���ʽ� ���� ��

#define MAX_INSTACNE_REGEN_MONSTER_NUMBER		2			// �ν��Ͻ� ���� ������ ���� ���� ��

#define PIRATESHIP_START_POSITION_X				12			// ������ ���� ��ŸƮ ��ġ X				
#define PIRATESHIP_START_POSITION_Y				180			// ������ ���� ��ŸƮ ��ġ Y

#define MAPINDEX_SERVEREVENT_LOBBY				356			// ���� �̺�Ʈ �ν��Ͻ����� 1

#define MAPINDEX_SERVEREVENT_DUNGEON1			357			// ���� �̺�Ʈ �ν��Ͻ����� 1
#define MAPINDEX_SERVEREVENT_DUNGEON2			358			// 2
#define MAPINDEX_SERVEREVENT_DUNGEON3			359			// 3
#define MAPINDEX_SERVEREVENT_DUNGEON4			360			// 4

#define MAPINDEX_PARTYHALL_1					335			// ��ƼȦ(������Ƽ��)
#define MAPINDEX_PARTYHALL_2					336			// ��ƼȦ(Ȳ���� ��)
#define MAPINDEX_PARTYHALL_3					337			// ��ƼȦ(���ε� ��Ƽ)
#define MAPINDEX_PARTYHALL_4					338			// ��ƼȦ(������ ��)
#define MAPINDEX_PARTYHALL_5					339			// ��ƼȦ(������Ƽ)

#define MAPINDEX_PVPMAP							380			// PVPMAP

#define MAPINDEX_SANTAFACTORY_1					385			// ������ ��Ÿ �۾���.
#define MAPINDEX_SANTAFACTORY_2					386			// û���� ��Ÿ �۾���.
#define MAPINDEX_SANTAFACTORY_3					387			// ��� ��Ÿ �۾���.
#define MAPINDEX_SANTAFACTORY_1_2				102			// ������ ��Ÿ �۾���.
#define MAPINDEX_SANTAFACTORY_2_2				123			// û���� ��Ÿ �۾���.
#define MAPINDEX_SANTAFACTORY_3_2				124			// ��� ��Ÿ �۾���.

#define MAPINDEX_WEDDINGHALL					372			// ������
#define MAPINDEX_BATTLEROYAL_MABRIUM			373			// ��Ʋ�ξ� - ���긮��
#define MAPINDEX_BATTLEROYAL_GRANDMABRIUM		374			// ��Ʋ�ξ� - �׶����긮��

#define MAPINDEX_LABYRINTH_1					375			// �Ȱ��̱� 1��

//#define MAPINDEX_BOKBULBOK_NPC					95			// ���� - ���Һ�NPC	



//-------------------------------------------------
// PVP�� ������ MapIndex
//-------------------------------------------------
#define PVP_MAPINDEX1							135			

enum INSTANCEMAP_TYPE
{
	INSTANCEMAP_TYPE_NONE,
	INSTANCEMAP_TYPE_GUILD,
	INSTANCEMAP_TYPE_PARTY,
	INSTANCEMAP_TYPE_VILLAGE,
	INSTANCEMAP_TYPE_SERVER,
	

	//---------------------------------------------------------
	//	�� ���� �߰��� �ּ���
	//---------------------------------------------------------
	INSTANCEMAP_TYPE_MAX
};

//-------------------------------------
// FOG(�Ȱ�)
//----------------------------------
// ���� �Ӽ�
#define FOG_BLACK				2		// ���� ��ο�
#define FOG_HALF				1		// ������
#define FOG_NONE				0		// ����

// ����ó���� ����. 
#define FOG_SOUTH		1
#define FOG_SW			2
#define FOG_WEST		4
#define FOG_NW			8
#define FOG_NORTH		16	
#define FOG_NE			32
#define FOG_EAST		64	
#define FOG_SE			128

//---------------------------------------------------
// ������ ���. 
//---------------------------------------------------
class cltMapHeader{
public:
	DWORD Version;                          // ������ ���� 
	DWORD Unique;                           // ���� ���� 
	TCHAR Text[128];                         // ���ڿ� ���� 
	DWORD Reserved0;	                   // ���ӿ� �����ϴ� ���� �� .
	SHORT MapXsize, MapYsize;               // ������ ���� ���� ������ 
	SI32 MapType;                          // ���� Ÿ���� ���� 
	SI32 TileSet1;							// Layor1 �� Ÿ�ϼ�Ʈ

	bool bWeatherSwitch;					// ������ �۵��ϴ� �����ΰ� ?(�����̳� ���..) 

	SI16 TileSet2;							// Layor2 �� Ÿ�ϼ�Ʈ 

	TCHAR Reserved[19];                   

	cltMapHeader();

};

// �Ϲ����� Field Object�� ������ �м���. 
class cltFieldObjectBitField_Normal{
private:
	UI32 FieldUnique:		15;
	UI32 ValidSwitch:		1;
	UI32 RandomValue:		4;
	UI32 LengthToBottom:	4;		// �ش� FieldObject �� �Ʒ��ʰ��� ���� 
	UI32 LengthToRight:		4;		// �ش� FieldObject �� �����ʰ��� ���� 
	UI32 Reserved:			4;

public:
	UI32 GetFieldUnique()const;
	void SetFieldUnique(UI32 unique);
	UI32 GetValidSwitch()const;
	void SetValidSwitch(UI32 valid);
	UI32 GetRandomValue()const;
	void SetRandomValue(UI32 random);
	UI32 GetLengthToBottom()const;
	void SetLengthToBottom(UI32 bottom);
	UI32 GetLengthToRight()const;
	void SetLengthToRight(UI32 right);

};

//-----------------------------------------
// ������ ���� 
//-----------------------------------------
class cltItemMapInfo{
public:
	UI16 uiItemUnique;		// �������� ����ũ. 
	UI16 uiItemIndex;		// ���� �����۸���Ʈ ���� �ε���. 

	cltItemMapInfo();
};


#define MAX_EFFECT_PER_MAP			200
//--------------------------------------
// ����Ʈ ����
//----------------------------------------
class cltEffectMapInfo{
public:
	SI32			gimg;
	SI32			x;
	SI32			y;
	SI32			font;
	bool			reverse;

	void Init();
	void Set(cltEffectMapInfo* pclinfo);
};

// Field Object ������ ���� �м��ϱ� ���� ���Ͽ�. 
union uFieldObjectUnion{
	UI32 Data32;

	cltFieldObjectBitField_Normal FieldObject_Normal;
};

//-----------------------------------------------------
// ���� ���� �ȳ� ���� 
//-----------------------------------------------------
#define MAX_GEO_NUMBER	256
#define GEO_TEXT_LENGTH	64
class cltMapGeoInfo{
public:
	cltMapCommon* pclMap;
	SI32		siXsize, siYsize;
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_GEO_NUMBER>		siGeoPosX;
	NSafeTArray<SI32, MAX_GEO_NUMBER>		siGeoPosY;
	NSafeTArray<SI32, MAX_GEO_NUMBER>		siGeoPosAccount;
#else
	SI32		siGeoPosX[MAX_GEO_NUMBER];
	SI32		siGeoPosY[MAX_GEO_NUMBER];
	SI32		siGeoPosAccount[MAX_GEO_NUMBER];	
#endif

	TCHAR		szGetText[MAX_GEO_NUMBER][GEO_TEXT_LENGTH];	// ���������� �ؽ�Ʈ�� ����� ����. 
	UI08*		pclGeoMap;									// ���� ������ �� ����. 

	cltMapGeoInfo(cltMapCommon* pclmap, SI32 xsize, SI32 ysize);
	~cltMapGeoInfo();

	void SetGeoMap(SI32 x, SI32 y, UI08 data);
	UI08 GetGeoMap(SI32 x, SI32 y);
				
	void InitGeoPosInfo();									// ���������� ��ġ ������ �ʱ�ȭ�Ѵ�. 
	void UpdateGeoPos(SI32 x, SI32 y, SI32 geoinfo);		// �������� ��ġ�� ������Ʈ �Ѵ�. 

	BOOL Write(FILE* fp);
	BOOL Read(FILE* fp);
};

//----------------------------------------------
// cltMapCommon
//----------------------------------------------
class cltMapCommon{
public:
	// ������ �⺻ ����. 
	cltMapHeader			MH;
	
	SI32					siMapUnique;			// ������ ����ũ.
	SI32					siMapIndex;

protected:
	short					*pIDMap;

	// �浹 �Ӽ��� �����Ѵ�. 
	short					*pCollMap;  

	DWORD					*pFieldObjectMap;  
	DWORD					*pFieldObjectMapPara;

	cltItemMapInfo*			pclItemMap;				// �������� ���� ������ ����. 

public:
	cltMapGeoInfo			*pclMapGeoInfo;			// �����ȳ� ����. 

	cltTileManager*			pclTileManager;
	cltFieldObjectManager*	pclFieldObjectManager;

	//-----------------------------------
	// ĳ���� ������. 
	//-----------------------------------
	cltCharManager*			pclCM;

	//-----------------------------------
	// ������ ����ũ. 
	//------------------------------------
	SI32					siVillageUnique; // �������� ������ ������� �� ������ ������ Unique���� ����ȴ�. 
	
	//------------------------------------------
	// ��ã�� ��ü 
	//------------------------------------------
	CAStarListMgr*			pclPath;
	SI32					MoveID;

	//---------------------------------------
	// ���� �˻��� Ref
	//---------------------------------------
	SI32*					YOff;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMapLayer*, MAX_MAP_LAYER>		pclLayer;
#else
	cltMapLayer*			pclLayer[MAX_MAP_LAYER];
#endif

	RECT					ValidRect;		// ������ ���� ���� 

	//---------------------------------------
	// �ν��Ͻ� ������ ������
	//---------------------------------------
	SI32					m_siInstanceMapData;		// �ν��Ͻ� ���� ���� ����
	DWORD					m_dwInstanceMapStartTime;	// �ν��Ͻ� ���� ���� �ð�
	DWORD					m_dwInstanceMapMaxTime;		// �ν��Ͻ� ���� ���� �ð�
	SI32					m_siInstanceMapScore;		// ���� 
	SI16					m_siInstanceMapGateIndex;	// ����Ʈ ��Ʈ ��ȣ
	SI32					m_siGateMonID;				// ����Ʈ ���� ����
	SI32					m_siBossID;					// ����Ʈ ���� ����
	
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_INSTANCE_BONUS_MONSTER_NUMBER>		m_siBonusMonID;
#else
	SI32					m_siBonusMonID[MAX_INSTANCE_BONUS_MONSTER_NUMBER];	// �ν��Ͻ� ������ ���ʽ� ����
#endif
	SI32					m_siMaxMonsterNum;			// �� ������ ���� ��
	SI32					m_siKillCount;				// ���� ���� ��
	SI32					m_siBonusMonCount;			// ���ʽ� �ð����� ���ʽ� ���͸� �󸶳� �׿�����
	
	SI32					m_siClearStep;				// ���� �δ��� �� �ܰ� Ŭ���� �ߴ°�?
	SI32					m_siNPCGroupID;				// ���� ��ȯ�Ǿ��ִ� NPC GroupID
    	

	// ��� ���׿� ���� �ӽ� ������ - by LEEKH 2008.02.13
	TCHAR					m_szGuildName[MAX_GUILD_NAME];

public:
	cltMapCommon();
	cltMapCommon(SI32 mapindex, SI32 mapunique, SHORT xsize, SHORT ysize, SI32 tileset1, SI32 tileset2, cltCharManager* pclCM, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager);
	
	virtual ~cltMapCommon();
	void Init();

	virtual BOOL MakeSmallMap(SI32 smallmapmode, TCHAR* mapfilename){return FALSE;}
	virtual void DeleteSmallMap(){}
	

	//-----------------------------------
	// �⺻ ���� ����. 
	//-----------------------------------
	SHORT	GetXsize();
	SHORT	GetYsize();

	//---------------------------------------
	// ���� �Ҵ� �� ���� 
	//--------------------------------------
	void AllocMap(SHORT xsize, SHORT ysize);
	void FreeMap();

	//--------------------------------------------------------
	// Field Object ���� 
	//--------------------------------------------------------
	BOOL PutFieldObject(SI32 six, SI32 siy, TCHAR* name, SI32 para);
	BOOL PutFieldObject(SI32 six, SI32 siy, SI32 siunique, SI32 para = 0);
	BOOL PutGateFieldObject(SI32 six, SI32 siy, SI32 siunique, SI32 para);

	BOOL DeleteFieldObject(SI32 six, SI32 siy);						// six, siy��ǥ�� �ִ� Field Object�� �����Ѵ�.
	void DeleteFieldObjectUnique(SI32 siUnique);					// �ش� ����ũ�� Field Object�� ��� �����
	BOOL PutFieldObjectBrush(SI32 six, SI32 siy, SI32 brush);		// Field Object �귯�ø� ����ؼ� ����ش�. 

	BOOL SetFieldObject_Unique(SI32 six, SI32 siy, SI32 siunique);
	SI32 GetFieldObject_Unique(SI32 six, SI32 siy);

	BOOL SetFieldObjectPara(SI32 six, SI32 siy, SI32 para);
	SI32 GetFieldObjectPara(SI32 six, SI32 siy);

	BOOL GetFieldObjectValidSwitch(SI32 six, SI32 siy);
	void SetFieldObjectValidSwitch(SI32 six, SI32 siy, BOOL bmode);		// �ʵ� ������Ʈ�� ��� ��ȿ�ϰ� �ϰų� ��ȿ�ϰ� �Ѵ�. 

	void SetFieldObjectRandomValue(SI32 six, SI32 siy, BOOL value);
	UI32 GetFieldObjectRandomValue(SI32 six, SI32 siy);

	void SetFieldObjectLengthToBottom(SI32 six, SI32 siy, SI32 length);
	UI32 GetFieldObjectLengthToBottom(SI32 six, SI32 siy);

	void SetFieldObjectLengthToRight(SI32 six, SI32 siy, SI32 length);
	UI32 GetFieldObjectLengthToRight(SI32 six, SI32 siy);
	bool GetFieldObjectCenterPos(SI32 six, SI32 siy, SI32* pcenterx, SI32* pcentery);		// six, siy������ �ִ� Field Object�� �߽� ��ġ�� ���ؼ� �����Ѵ�. 
	
	void NewFieldObjectSetInMap();		// ������ ���Ӱ� Field Object�� ��ġ�Ѵ�. 

	//------------------------------------------------
	// ���� Ȯ�� 
	//------------------------------------------------
	// x, y�� ���� ��ǥ �ȿ� �ִ°�?
	// x, y �⺻��ǥ 
	bool	IsInMapArea(SI32 x, SI32 y);

	//---------------------------------------------
	// ��ǥ ��ȯ 
	//---------------------------------------------
	// �������� X, Y��ǥ�� �߽��� ��Ʈ ��ǥ�� �����ش�. (������ǥ)
	// ȭ����� ��ǥ�� �ƴ϶� ���� ��ǥ�̴�. 
	BOOL GetXYDotFromXYCord(SI32 x, SI32, SI32 & centerx, SI32 & centery);
	void GetRealTileByRealDot(SHORT realx, SHORT realy, SI32* x, SI32* y);

	//----------------------------------
	// Save & Load
	//----------------------------------
	BOOL WriteIDMap(FILE *fp);
	BOOL ReadIDMap(FILE *fp);

	BOOL WriteCollMap(FILE *fp);
	BOOL ReadCollMap(FILE *fp);

	BOOL WriteFieldObjectMap(FILE *fp);
	BOOL ReadFieldObjectMap(FILE *fp);

	BOOL WriteFieldObjectMapPara(FILE *fp);
	BOOL ReadFieldObjectMapPara(FILE *fp);

    BOOL Save(TCHAR* filename);		// ������ �����Ѵ�. 

	//---------------------------------------------------------
	// �ǹ� ���� 
	//---------------------------------------------------------
	
	void MakeVillageStructure();				// ������ �ǹ����� �����. 
	void DeleteVillageStructure(SI32 slot);		// Ư�� ���Կ� �ִ� �ǹ��� �����. 

	
	
	// ���ϰ� : -1 -> ������ �ƴ� ��
	// ������ Ư�� ��ǥ�� �� �� �ǹ��� ���Կ� �ش��ϴ��� �˷��ش�. 
	SI32 GetStructureSlot(SI32 villageunique, SI32 mapx, SI32 mapy);	
	
	// Ư�� ������ ���� ��ǥ�� �˷��ش�.
	bool GetSlotStartPos(SI32 villageunique, SI32 slot, SI32* pstartx, SI32* pstarty);

//------------------------------------------------------------
//   Ÿ�� ���� �Լ� 
//------------------------------------------------------------
	
	void SetUnique(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 siunique);				// Ÿ���� ������� ����Ͽ� Unique�� �����Ѵ�.
	void SetUniqueSouth(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 siunique);			// �־��� Ÿ���� ���ʿ� ���� unique�� �����Ѵ�.
	void SetUniqueWest(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 siunique);			// �־��� Ÿ���� ���ʿ� ���� unique�� �����Ѵ�.
	void SetUniqueNorth(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 siunique);			// �־��� Ÿ���� ���ʿ� ���� unique�� �����Ѵ�.
	void SetUniqueEast(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 siunique);			// �־��� Ÿ���� ���ʿ� ���� unique�� �����Ѵ�.
	
	SI32 GetSelfUniqueInfo(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 workunique);		// �ڱ� ���� ���¸� �ľ��Ѵ�. 
	void SetDrawInfo(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 unique, SI32 sifile, SI32 sifont);		// ��¿� ������ Ÿ�Ͽ� ����Ѵ�. 

	void PutTileXpr(SI32 layor, SI32 six, SI32 siy, SI32 unique);
	void PutTile0(SI32 layor, SI32 six, SI32 siy, SI32 unique);
    BOOL PutTile2(SI32 layer, SI32 six, SI32 sy, SI32 siunique);
	BOOL PutTile4(SI32 layer, SI32 six, SI32 sy, SI32 siunique);
	
	BOOL IsChildTile(SI32 layer, SI32 six, SI32 siy, SI32 rate, SI32 unique, SI32* pchildunique);		// layer, six, siy ������ DrawInfo�� ��� Ÿ�� ��Ʈ�� uniqueŸ�� ��Ʈ�� �ڽ� ��Ʈ���� Ȯ���Ѵ�. 
	BOOL IsDiffTileSet(SI32 sisrcunique, SI32 sidstunique);		// sisrcunique�� sidstunique�� ���� ����Ÿ��(������ �ʰ� �θ��ڽ� ���赵 �ƴ� )������ ���θ� �˷��ش�. 
	BOOL GetProperFileNFont(SI32 unique, SI32 result, SI32& file, SI32& font);


	//-------------------------------------------
	// ������ ���������� ��밡���ϰ� ����� �Լ�. 
	//--------------------------------------------
	virtual void MakeLastMap();

	//-----------------------------------------
	// �浹 ���� 
	//----------------------------------------
	SI32 CalcCollInfo(SI32 x, SI32 y);		// ���� x, y������ �浹������ ���θ� ����Ѵ�. 
	
    BOOL	SetCollMap(SHORT x, SHORT y, SHORT block);		// �浹 �Ӽ��� �����Ѵ�. 
	SHORT	GetCollMap(SI32 x, SI32 y);
	
    void	DeleteCollMap(SHORT x, SHORT y, SHORT block);	// Ư�� ��Ʈ�� �����. 
	BOOL	DeleteCharCollMap(SHORT x, SHORT y);

    bool	IsColl(SHORT x, SHORT y, SHORT block);			// ��������� �浹 ���θ� �˷��ش�. 

	//----------------------------------------------
	// IDMap ���� 
	//----------------------------------------------
	void	SetIDMap(SHORT id, SI32 x, SI32 y);
    SHORT	GetIDMap(SI32 x, SI32 y);
	void	ClearIDMap(int x, int y);

	//------------------------------------------------
	// ������ ���� ���� 
	//------------------------------------------------
	 void SetItemMap(SI32 x, SI32 y, UI16 itemunique, UI16 itemlistindex);
	 cltItemMapInfo* GetItemMap(SI32 x, SI32 y);
	
	//-----------------------------------------
	// ����
	//-----------------------------------------
	void AttachVillage();			// ������ ������ ���δ�.
	void DeattachVillage();			// ������ �������� �����.

	void DeattachGate();			// ����Ʈ�� �������� �����.

	//---------------------------------
	// ����� ã�� 
	//---------------------------------
	// ĳ���͸� ��ġ��Ű�� ���� orgx, orgy �ֺ��� �� ������ ã�´�. 
	bool FindEmptyAreaForCharLocate(SI32 kind,  SI32 orgx, SI32 orgy, SI32 range, SI32 *pdestx, SI32 *pdesty, bool bcharswitch);
    bool	IsEmpty(SI32 x, SI32 y);				// ������ ��� �ִ°�? ���� ĳ���Ͱ� �ִ°�, ��, �Ϲ� ��ֹ�
    BOOL	IsEmptyWater(SHORT x, SHORT y);			// ������ ��� �ִ°�? ���� ĳ���Ͱ� �ִ°�, ��, �Ϲ� ��ֹ�
    BOOL	IsEmpty(SHORT x, SHORT y, SHORT xsize, SHORT ysize, SHORT idx, SHORT idy); // ������ ��� �ִ°�? ���� ĳ���Ͱ� �ִ°�, ��, �Ϲ� ��ֹ�
    BOOL	IsEmptyWater(SHORT x, SHORT y, SHORT xsize, SHORT ysize, SHORT idx, SHORT idy);	// ��� �ִ°�?

	SI32	GetMouseTileAtb(SI32 x, SI32 y);			// Ư�� ��ǥ�� Ÿ�� ������ ���´�. 
	SI32	GetUserNum(SI32 x, SI32 y);

	DWORD	GetInstanceMapMaxTime();
};


//-----------------------------------------------
// cltMapServer
//-----------------------------------------------

#include "../NetworkLib/ITZNetLib/ITZWorld.h"
class cltMapServer : public cltMapCommon {
public:

	cltServerMap* pclServerMap;

	cltMapServer ( ITZWorld< ITZMap > *pWorld, UI32 mapindex, SI32 mapunique, SHORT xsize, SHORT ysize,  SI32 tileset1, SI32 tileset2, cltCharManager* pclcm, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager);
	~cltMapServer ();

	
};


//-----------------------------------------------
// cltMapClient
//-----------------------------------------------
class cltMapClient : public cltMapCommon {
public:

	//------------------------------------
	// �� ���
	//------------------------------------
	CWaterDropMgr	*pclWaterDrop;

	//------------------------------------
	// �ݵ���
	//------------------------------------
	CFireFlyMgr		*pclFireFly;
	
	//-----------------------------------
	// ������ ��¦��
	//-----------------------------------
	CIceFlashMgr	*pclIceFlash;

	//-----------------------------------
	// ����Ǯ�� Ȧ��
	//-----------------------------------
	CSeedDropMgr	*pclSeedDrop;

	//------------------------------------
	// �̵� ǥ�� 
	//------------------------------------
	_MoveMark*				pclMoveMark;

	//-----------------------------------
	// ȭ���� �߽� 
	//-----------------------------------
	int						VirtualMapX, VirtualMapY;
	SI32					siOldVirtualMapX, siOldVirtualMapY;

	bool					bMapDrawSwitch;						// ������ �׸����� ������

	bool					bCollDrawSwitch;					// �浹 ������ ǥ���ϴ��� ���θ� �˷��ִ� ����. 

	// ����Ʈ ����
#ifdef _SAFE_MEMORY
	NSafeTArray<cltEffectMapInfo, MAX_EFFECT_PER_MAP>		pclEffectMap;
#else
	cltEffectMapInfo		pclEffectMap[MAX_EFFECT_PER_MAP];
#endif
	SI32					CurrentEffect;

	UI08					* uiFogMap;

public:

	cltMapClient();
	cltMapClient(SI32 mapindex, SI32 mapunique, SHORT xsize, SHORT ysize, SI32 tileset1, SI32 tileset2, cltCharManager* pclCM, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager);
	~cltMapClient();

	//-------------------------------------------
	// ������ ���������� ��밡���ϰ� ����� �Լ�. 
	//--------------------------------------------
	void MakeLastMap();

	//------------------------------------
	// ���� Ȯ�� 
	//------------------------------------
	// x, y��ǥ�� ȭ��ȿ� �ִ��� Ȯ���Ѵ�.
    BOOL	IsInScreen(SHORT x, SHORT y);
	// x, y Ÿ�� ��ǥ�� ȭ��ȿ� �ִ��� Ȯ���Ѵ�.
	BOOL IsInScreenTile(SI32 x, SI32 y);


	//------------------------------------
	// ȭ�� �߽� Ÿ�� ��ǥ Ȯ�� 
	//------------------------------------
	SHORT	GetVirtualMapX();
	SHORT	GetVirtualMapY();


	//------------------------------------
	// ��� 
	//------------------------------------
    void SetMapDrawSwitch(bool mode);

	//----------------------------------------------
	// ����(�Ȱ�)
	//----------------------------------------------
	bool DrawFog(LPDIRECTDRAWSURFACE7 lpsurface , cltClient * pclclient);
	// �Ѱ��� FOG_BLACK�� �׸���. 
	BOOL DrawFogBlack(cltClient* pclclient, SI32 x, SI32 y, SI32 centerx, SI32 centery);

	UI32 GetFogMap(SI32 x, SI32 y);
	
	void SetFogMap(SI32 x, SI32 y, UI32 data);
	
	// ���� ó��. 
	void FogRecoverAction();
	UI08 GetFogData(SI32 x, SI32 y, SI32 fog);
	// Ư�� Ÿ�Ͽ� ���� ���� �۾��� �����Ѵ�. 
	void PutFog(SI32 x, SI32 y, SI32 fog);
	// Ư�� ��ġ�� ���� ������ ����Ѵ�. 
	bool CalcFogData(SI32 x, SI32 y, SI32* pfont);

	//-----------------------------------
	// ��ǥ ��ȯ (ȭ�� ���� ) 
	//-----------------------------------
    // �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ����ǥ)
    BOOL	GetCenterXYByMapCenterXY(SHORT x, SHORT y, SHORT & centerx, SHORT & centery);
	

	// �������� ����� �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (������ǥ)
	// ���� ��ǥ 
	// �������� X, Y��ǥ�� �߽��� ��ǥ�� �����ش�. (ȭ�� ��ǥ)
    BOOL	GetCenterXY(SHORT X, SHORT Y, SHORT & centerx, SHORT & centery);
    BOOL	GetRefXY(SHORT X, SHORT Y, SHORT & centerx, SHORT & centery);
	
	
    // ���� ��ǥ�� ȭ�� ��ǥ�� ��ȯ�Ѵ�.
    void	TransFromRealDotToScreenDot(SHORT realx, SHORT realy, SHORT& screenx, SHORT &screeny);
    // ȭ�� ��ǥ�� ���� ��ǥ�� ��ȯ�Ѵ�.
    void	TransFromScreenToRealXY(SHORT screenx, SHORT screeny, SHORT& realx, SHORT &realy);


	BOOL	IncreaseVirtualMapX(int mount);
	BOOL	DecreaseVirtualMapX(int mount);
	BOOL	IncreaseVirtualMapY(int mount);
	BOOL	DecreaseVirtualMapY(int mount);


	// mousex, mousey�� Ŭ���̾�Ʈ ������ �ִ°�?
    BOOL	IsPtInMap(SHORT mouse_x, SHORT mouse_y);


//-----------------------------
// �׸��� �Լ� 
//-----------------------------

	// ����ؾ� �� �߽� ��ġ�� ���Ѵ�. 
	void GetDrawCenterXY(SI32 x, SI32 y, SI32* pcenterx, SI32* pcentery);

	// ĳ���� �̸��� ǥ���Ѵ�. 
	void DrawCharName();

	// ������ �׸���. 
    BOOL DrawMap();
	// �������� ��ũ��. 
	void Scroll_North(cltClient* pclclient);
	// �������� ��ũ��. 
	void Scroll_South(cltClient* pclclient);
	// �������� ��ũ��. 
	void Scroll_East(cltClient* pclclient);
	// �������� ��ũ��. 
	void Scroll_West(cltClient* pclclient);
	// �ϵ������� ��ũ��. 
	void Scroll_NorthEast(cltClient* pclclient);
	// �ϼ������� ��ũ��.
	void Scroll_NorthWest(cltClient* pclclient);
	// ���������� ��ũ��.
	void Scroll_SouthEast(cltClient* pclclient);
	// �Լ������� ��ũ��.
	void Scroll_SouthWest(cltClient* pclclient);





    BOOL DrawObj();
	// ������ �浹 ������ ǥ���Ѵ�. 
	void DrawMapCollInfo();
	// ���� ���콺�� ��ġ�� Ÿ���� ��ġ�� ǥ���Ѵ�. 
	void DrawCurrentTilePos(SI32 mapx, SI32 mapy);
	

	// ���� ������ �������� �׸���.		
	void DrawLandItem();	
	// ĳ���͸� ������ �׸���. 
	void DrawCharInMap(SI32 x, SI32 y);


	// ���� ���� �����͸� �����Ѵ�. 
	void SetGeoInfo(HDC hdc);

	// ���� ���� �����͸� �����ش�. 
	void DrawGeoInfo(LPDIRECTDRAWSURFACE7 lpsurface, cltHelpManager* pclhelpmanager);


	// Field Object �� �׸���. 
	void DrawFieldObject(SHORT mapx, SHORT mapy, SHORT cx, SHORT cy, SI32 fieldobjectunique, SI32 siForceTransMode = NULL);
	
	// ���� �׷��ش�. 
	void DrawFire(SHORT mapx, SHORT mapy, SHORT cx, SHORT cy, SI32 file);


	// ���� ��Ҹ� �׸��� �Լ��� 
    // �ٴ��� �׸���. 
    BOOL DrawLayer(SHORT centerx, SHORT centery, SI32 layer, SHORT x, SHORT y);

	// x, y:2�����ǥ 
    BOOL DrawMousePos(SHORT centerx, SHORT centery, SHORT x, SHORT y, BYTE * table, SHORT mode);

	void DrawTile(SI32 ref, SI32 file, SI32 font, SI32 x, SI32 y, SI32 startx, SI32 starty);


////////////////////////////////////////////////////////////////////
/// ������ �����ϰų� �ҷ��´�. 
///////////////////////////////////////////////////////////////////
	
	BOOL MapSaveAsPCX(LPDIRECTDRAWSURFACE7 pSurface, int xsize, int ysize);		// ������  ĸ���Ѵ�. 
	BOOL MapSaveAsBMP(LPDIRECTDRAWSURFACE7 pSurface, int xsize, int ysize);
 	
	BOOL IsLand(SHORT x, SHORT y);		// x, y�⺻ ��ǥ 
	BOOL IsSea(SHORT x, SHORT y);		// x, y�⺻ ��ǥ 		

	void SetVirtualPos(SI16 siX, SI16 siY);

	//-------------------------------------------------
	// ���� ĸ�� ���� 
	// Map-Capture.cpp
	//-------------------------------------------------
	BOOL MapCapture();
	static BOOL CALLBACK StaticMapCaptureDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK MapCaptureDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	//----------------------------------------
	// ���� ���� ���� 
	//----------------------------------------
	BOOL MakeSmallMap(SI32 smallmapmode, TCHAR* SmallMapFileName);
	
	
	//---------------------------------------
	// ���� ���� ���� 
	//---------------------------------------
	void ScrollOperation();

	
	void PlayBackEffect();		// ��� ȿ������ �����Ѵ�. 
	void MakeRareItemSmoke(bool breverseswitch, SI32 x, SI32 y, SI32 xsize, SI32 ysize, UI08* image, SI32 rare,
						   bool horse = false );		// ��ǰ �����ۿ��� ǥ���Ѵ�.

	
	void PopEffect();			// ����Ʈ ����
	void PushEffect(cltEffectMapInfo * pclinfo);

};

// ȭ���̸��� ���� ������ ������ ���´�. 
BOOL GetMapInfo(TCHAR* filename, cltMapHeader* header);

bool IsMoveColl(int x, int y, int SrcX, int SrcY, void* thisptr);


// ��¹��� ����. 
#define DRAWOBJ_TYPE_FIELDOBJ	1
#define DRAWOBJ_TYPE_CHAR		2

class cltFieldObjDrawData{
public:
	SI32 x, y;
	SI32 cx, cy;
	SI32 founique;
	SI32 type;

	void Set(cltFieldObjDrawData* pcldata);
};

class cltDrawObjData{
public:
	SI32 siType;			// � ������ ��¹��ΰ�.?

	union {
		SI32				siID;				// DRAWOBJ_TYPE_FIELDOBJ�� ���, 
		cltFieldObjDrawData clFODrawData;		// DRAWOBJ_TYPE_CHAR�� ���, 
	};

	cltDrawObjData();

	cltDrawObjData(SI32 type, SI32 id);
	cltDrawObjData(SI32 type, cltFieldObjDrawData* pcldata);

};


#endif
