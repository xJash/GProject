//---------------------------------
// 2003/7/29 김태곤
//---------------------------------

#include <CommonLogic.h>
#include "MapManager.h"

#include "../../../NLib/NTextManager.h"

#include "SmallMap\SmallMap.h"
#include "MapTypeManager.h"
//#include "../GateManager/GateManager.h"
//#include "../GateManager/InstanceMapGateManager.h"
#include "../../Char/ParametaBox/parametabox.h"
#include "../../Char/CharServer/Char-Server.h"
#include "../../Char/CharManager/CharManager.h"
#include "../../../Server/Server.h"

#include "../../../CommonLogic/MsgType-System.h"
#include "../../../CommonLogic/Msg/MsgType-Hunt.h"
#include "../../../CommonLogic/MsgRval-Define.h"

#include "../../../Common/PartyMgr/PartyObj.h"
#include "../../../Common/PartyMgr/PartyMgr.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"

#include "../../NPCManager/NPC.h"

#include "NDataLoader.h"

#include "NTCHARString.h"

cltMapCommon* OrgAddress[MAX_MAP_NUMBER];

extern cltCommonLogic* pclClient;

//----------------------------------------------
// cltMapManager
//----------------------------------------------
cltMapManager::cltMapManager(SI32 gamemode, SI32 servicearea, cltVillageManager*		pclvillagemanager)
{
	int i;

	pclVillageManager	= pclvillagemanager;

	if(pclvillagemanager == NULL)
	{
		MsgBox(TEXT("fsd39f"), TEXT("sffds"));
	}

	GameMode = gamemode;

	CurrentMapIndex	= 0;
	pclCurrentMap	= NULL;

	for( i = 0; i < MAX_MAP_NUMBER; ++i )
	{
		pclMapArray[i] = NULL;
	}

	pclMapTypeManager	= new cltMapTypeManager;


	// 지도 이름을 불러서 설정한다. 
	LoadMapName(servicearea);

	pclGateManager		= new cltGateManager();
	pclInstanceMapGateManager = NULL;

	// 작은 지도의 위치. 
	DlgRectInitSwitch	= FALSE;

	if( gamemode == GAMEMODE_SERVER )
	{

		m_world.CreateWorld( MAX_MAP_NUMBER, 
			MAX_CHAR_NUMBER, 
			800, 
			600, 
			MAP_TILE_XSIZE, 
			MAP_TILE_YSIZE );
	}

	m_UpdateTimer_Action.Init( 10 * 1000 );		// 10초 업데이트
	m_UpdateTimer_Action.SetActive( true, ::GetTickCount() );

	m_siGatePositionID = 0;
	m_siChristmasGatePositionID = 0;
	m_siFestivalGatePositionID = 0;
}

cltMapManager::~cltMapManager()
{

	for( int i = 0; i < MAX_MAP_NUMBER; ++i )
	{
		NDelete( pclMapArray[i] );
	}

	NDelete( pclMapTypeManager );
	NDelete( pclGateManager );
	NDelete( pclInstanceMapGateManager );
}

void cltMapManager::Init()
{
	pclInstanceMapGateManager = new cltInstanceMapGateManager();
}

// 지도 이름을 불러서 설정한다. 
void cltMapManager::LoadMapName(SI32 servicearea)
{
	TCHAR szFileName[MAX_PATH] = TEXT("");

#ifdef _DEV
	StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_DEV.ntx") );
#else
	switch ( pclClient->siServiceArea )
	{
	case ConstServiceArea_Korea:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_KOR.ntx") );
		}
		break;
	case ConstServiceArea_Japan:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_JPN.ntx") );
		}
		break;
	case ConstServiceArea_China:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_CHI.ntx") );
		}
		break;
	case ConstServiceArea_English:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_ENG.ntx") );
		}
		break;
	case ConstServiceArea_Taiwan:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_TAI.ntx") );
		}
		break;
	case ConstServiceArea_USA:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_ENG.ntx") );
		}
		break;
	case ConstServiceArea_NHNChina:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_CHI.ntx") );
		}
		break;
	case ConstServiceArea_EUROPE:
		{
			StringCchCopy( szFileName, MAX_PATH, TEXT("TextMgr\\TextMgr_Map_EUR.ntx") );
		}
		break;
	}
#endif

	NTextManager MapNameText;
	MapNameText.CreateTextManager();

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		MapNameText.LoadTextFromCryptFile( szFileName, 1 );	
	}
	else
	{
		MapNameText.LoadTextFromFile( szFileName, 1 );
	}

/*
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	switch( pclClient->siServiceArea )
	{
	case ConstServiceArea_Korea :
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoK.txt") );
		break;
	case ConstServiceArea_China :
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoC.txt") );
		break;
	case ConstServiceArea_Japan : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoJ.txt") );
		break;
	case ConstServiceArea_English : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoE.txt") );
		break;
	case ConstServiceArea_Taiwan : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoT.txt") );
		break;
	case ConstServiceArea_USA : 
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfoU.txt") );
		break;

	default:
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data\\MapInfo.txt") );
		break;
	}
*/
	TCHAR	datfilename[35];
	if( pclClient->siServiceArea == ConstServiceArea_Korea )	// 한국
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoK.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Japan )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoJ.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )	
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_English )  // 영어
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoE.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoT.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )  
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoU.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )  // NHNChina
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoC.txt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		StringCchCopy(datfilename, MAX_PATH, TEXT("Data\\MapInfoG.txt"));
	}

	/*
	NTextManager MapNameText;
	MapNameText.CreateTextManager();

	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		MapNameText.LoadTextFromCryptFile(TEXT("TextMgr\\MapTextMgr.txt"), pclClient->GetTextColumn());	
	}
	else
	{
		MapNameText.LoadTextFromFile(TEXT("TextMgr\\MapTextMgr.txt"), pclClient->GetTextColumn());
	}
	*/
	

	NDataLoader	dataloader;
	BOOL bLoadFile = FALSE;

	//KHY - 0810 - 텍스트 리소스 암호화.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( datfilename);		
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile(datfilename);							
	}
	
	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile MapInfo"),TEXT("Error"));
		return;
	}

	SI32 mapindex;
	TCHAR mapname[1024];
	SI32 mapunique;
	SI32 villageunique;
	SI32 parentmap;
	SI32 minlevel;
	SI32 maxlevel;
	SI32 blockwarp;
	SI32 encountmap;
	SI32 seamap;
	SI32 landmap;
	SI32 fogmap;
	SI32 instancemap;
	SI32 guildmap;
	SI32 pkMap;
	SI32 cloneMap = 0;
	SI32 userLimit = 0;
	SI32 siCanMarket = 0;
	TCHAR musicfile[256];

	NDataTypeInfo pDataTypeInfo[] =
	{
			NDATA_INT32,	&mapindex,   4,		
			NDATA_MBSTRING,	mapname,	256,
			NDATA_INT32,	&mapunique,	4,
			NDATA_INT32,	&villageunique,	4,
			NDATA_INT32,	&parentmap,	4,
			NDATA_INT32,	&minlevel,		4,
			NDATA_INT32,	&maxlevel,		4,
			NDATA_INT32,	&blockwarp,		4,			
			NDATA_INT32,	&encountmap,	4,
			NDATA_INT32,	&seamap,	4,
			NDATA_INT32,	&landmap,	4,
			NDATA_INT32,	&fogmap,	4,
			NDATA_INT32,	&instancemap,	4,
			NDATA_INT32,	&guildmap,	4,
			NDATA_INT32,	&pkMap,	4,
			NDATA_INT32,	&cloneMap,	4,
			NDATA_INT32,	&userLimit,	4,
			NDATA_INT32,	&siCanMarket,	4,
			NDATA_MBSTRING,	musicfile,	256,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData() ) 
		{
			// MapTextMgr.txt 에서 맵 이름을 가져온다.

			TCHAR* szMapNameText = MapNameText.GetText(SI32ToString(mapindex));
			
			if(szMapNameText == NULL)
			{
				MessageBox(NULL, TEXT("MapInfo::MapName Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
				return;
			}

			StringCchCopy(mapname, sizeof(mapname), szMapNameText);

			if (mapname[0] != NULL)
			{
				if(villageunique)
				{
					TCHAR* pvillagename = pclVillageManager->GetName(villageunique);
					if(pvillagename)
					{
						SetMapName(mapindex, pvillagename);
					}
				}
				else if(IsHuntMap(mapindex))
				{
					SI32 huntvillageunique = mapindex - 200;
					TCHAR* pvillagename = pclVillageManager->GetName(huntvillageunique);
					if(pvillagename)
					{
						TCHAR temp[256];
						StringCchCopy(temp, 256, pvillagename);
						TCHAR* pText = GetTxtFromMgr(1704);
						StringCchCat(temp, 256, pText);

						SetMapName(mapindex, temp);

					}

				}
				else
				{
					SetMapName(mapindex, mapname);
				}

				SetBGM( mapindex, musicfile );

				// MaxLevel이 0 이면 현재 최고레벨로 바꾸어 준다.
				if(maxlevel <= 0)		maxlevel = MAX_CHARACTER_LEVEL;

				SetMapBasicInfo(mapindex, mapunique, villageunique, 
					minlevel, maxlevel, DATA_TO_BOOL(blockwarp), parentmap,
					DATA_TO_BOOL(encountmap), DATA_TO_BOOL(seamap),
					DATA_TO_BOOL(landmap), DATA_TO_BOOL(fogmap),
					instancemap, DATA_TO_BOOL(guildmap), DATA_TO_BOOL(pkMap),
					userLimit, DATA_TO_BOOL(siCanMarket) );

				if( cloneMap )
				{
					AddCloneMap( cloneMap, mapindex );
				}

			}
		}
	}



	/*cyj
	//-------------------------------------------
	// 서비스 지역에 따라 다른 텍스트를 불러온다. 
	//-------------------------------------------
	if(servicearea == ConstServiceArea_Korea )	// 한국
	{
		StringCchCopy(filename, 128, TEXT("Map\\MapInfo.txt"));

	}

	else if(servicearea == ConstServiceArea_China)
	{
		StringCchCopy(filename, 128, TEXT("Map\\MapInfoC.txt"));
	}
	else if(servicearea == ConstServiceArea_English)
	{
		StringCchCopy(filename, 128, TEXT("Map\\MapInfoE.txt"));
		//_tcscpy(filename, TEXT("Map\\MapInfo_China.txt"));
	}
	else if(servicearea == ConstServiceArea_Japan)
	{
		StringCchCopy(filename, 128, TEXT("Map\\MapInfoJ.txt"));
		//_tcscpy(filename, TEXT("Map\\MapInfo_China.txt"));
	}
	else
	{
		MsgBox(TEXT("fdf38fj"), TEXT("fdd3:%d"), servicearea);
		return ;
	}
	
	fp = _tfopen(filename, TEXT("rt"));

	if(fp == NULL)
	{
		MessageBox(NULL, TEXT("MapInfo Load Error"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return ;
	}

	// 첫번째 6줄은 무시한다. 
	for(i = 0;i < 6;i++)
		_fgetts(buffer, 1024, fp);
	
	while( _fgetts(buffer, 1024, fp) != NULL)
	{
		ParseText( buffer );

		mapindex = _tstoi( tokens[0] );
		MStrCpy( mapname, tokens[1], 256 );
		mapunique = _tstoi( tokens[2] );
		villageunique = _tstoi( tokens[3] );
		parentmap = _tstoi( tokens[4] );
		levellimit = _tstoi( tokens[5] );
		encountmap = _tstoi( tokens[6] );
		seamap = _tstoi( tokens[7] );
		landmap = _tstoi( tokens[8] );
		fogmap = _tstoi( tokens[9] );
		instancemap = _tstoi( tokens[10] );

	//	_stscanf(buffer, TEXT("%d %s %d %d %d %d %d %d %d %d %d"),
	//		&mapindex, mapname, &mapunique, &villageunique, &parentmap, &levellimit,&encountmap,
	//		&seamap, &landmap,&fogmap,&instancemap);

		if(villageunique)
		{
			TCHAR* pvillagename = pclVillageManager->GetName(villageunique);
			if(pvillagename)
			{
				SetMapName(mapindex, pvillagename);
			}
		}
		else if(IsHuntMap(mapindex))
		{
			SI32 huntvillageunique = mapindex - 200;
			TCHAR* pvillagename = pclVillageManager->GetName(huntvillageunique);
			if(pvillagename)
			{
				TCHAR temp[256];
				StringCchCopy(temp, 256, pvillagename);
				TCHAR* pText = GetTxtFromMgr(1704);
				StringCchCat(temp, 256, pText);

				SetMapName(mapindex, temp);
			}
		}
		else
		{
			SetMapName(mapindex, mapname);
		}

		SetMapBasicInfo(mapindex, mapunique, villageunique, levellimit, parentmap,
			DATA_TO_TYPE_BOOL(encountmap), DATA_TO_TYPE_BOOL(seamap),
			DATA_TO_TYPE_BOOL(landmap),DATA_TO_TYPE_BOOL(fogmap),DATA_TO_TYPE_BOOL(instancemap));
	}

	fclose(fp);
	*/

}


bool cltMapManager::DeleteAllMap()
{
	for( int i = 0; i < MAX_MAP_NUMBER; ++i )
	{
		NDelete( pclMapArray[i] );
	}			
	return true;
}

bool cltMapManager::SetCurrentMapIndex(SI32 index)
{
	if(index < 0 || index >= MAX_MAP_NUMBER)return false;

	CurrentMapIndex	= index;
	pclCurrentMap	= pclMapArray[ CurrentMapIndex ];
	return true;
}

SI32 cltMapManager::GetVillageUnique(SI32 index)
{
	if(index < 0 || index >= MAX_MAP_NUMBER)return 0;
	if(pclMapArray[index] == NULL)return 0;

	return pclMapArray[index]->siVillageUnique;
}

// 마을 유니크를 가지고 해당 지도의 인덱스를 찾는다. 
SI32 cltMapManager::GetMapIndexFromVillageUnique(SI32 villageunique)
{
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return -1;

	SI32 i;

	for(i = 0;i < MAX_MAP_NUMBER;i++)
	{
		if(pclMapArray[i] && pclMapArray[i]->siVillageUnique == villageunique)
		{
			return i;
		}
	}
	return -1;
}

// 지도 이름을 가지고 지도의 인덱스를 찾는다. 
SI32 cltMapManager::GetMapIndexFromName(TCHAR* name)
{
	SI32 i;

	for(i = 0;i < MAX_MAP_NUMBER;i++)
	{
		// KHY - 1122 - 순간이동 이용권 개선.
		if( pclClient->GameMode == GAMEMODE_SERVER )
		{
			if( pclMapArray[i] && _tcscmp(clUnitMapInfo[i].szMapName, name) == 0 )
			{
				return i;
			}
		}
		else if ( pclClient->GameMode == GAMEMODE_CLIENT )
		{
			if( _tcscmp(clUnitMapInfo[i].szMapName, name) == 0 )
			{
				return i;
			}
		}
	}
	return -1;
}


cltMapCommon* cltMapManager::GetMapPointer(SI32 index)
{
	if(index < 0 || index >= MAX_MAP_NUMBER)return NULL;
	if(pclMapArray[index] == NULL)return NULL;

	return pclMapArray[index];
}


// 지도를 불러온다. 
cltMapCommon* cltMapManager::Load(SI32 mapindex, SI32 mapunique, TCHAR* filename, cltCharManager* pclcm, cltTileManager* pcltileset, cltFieldObjectManager* pclfieldobjectmanager)
{
	DWORD loadTime = GetTickCount();

	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return NULL;

	FILE* fp;
	cltMapHeader MH;
	cltMapCommon* pclMap = NULL;

	// 지도의 헤더를 읽어온다. 
	fp=_tfopen(filename, TEXT("rb"));
	if(fp==NULL)
	{
#ifdef _DEBUG
		NTCHARStringBuilder	build;
		build.SetFormat("{1} 파일이 없습니다.") << filename;
		MessageBox(NULL, build, "cltMapManager::Load", MB_OK);
#endif
		return pclMap;
	}

	fread(&MH, sizeof(cltMapHeader), 1, fp);

	fclose(fp);

	// 지도를 초기화한한다. 
	if(GameMode == GAMEMODE_SERVER)
	{
		pclMap = new cltMapServer( (ITZWorld< ITZMap > *)&m_world, mapindex, mapunique, MH.MapXsize, MH.MapYsize, MH.TileSet1, MH.TileSet2, pclcm, pcltileset, pclfieldobjectmanager);

	}
	else
	{
		pclMap = new cltMapClient(mapindex, mapunique, MH.MapXsize, MH.MapYsize, MH.TileSet1, MH.TileSet2, pclcm, pcltileset, pclfieldobjectmanager);
	}

	

	// 지도를 정상적으로 읽어온다. 
	fp=_tfopen(filename, TEXT("rb"));
	if(fp==NULL)
	{
		delete pclMap;
		pclMap = NULL;
		return pclMap;
	}

	fread(&pclMap->MH, sizeof(cltMapHeader), 1, fp);

	pclMap->ReadIDMap(fp);
	pclMap->ReadCollMap(fp);
	
	pclMap->pclLayer[0]->Read(fp);
	pclMap->pclLayer[1]->Read(fp);

	pclMap->ReadFieldObjectMap(fp);
	pclMap->ReadFieldObjectMapPara(fp);

	if(pclMap->MH.Version  >= 2)
	{
		// 한국은 정보를 읽지 않는다.	- By LeeKH
		if( pclClient->siServiceArea != ConstServiceArea_Korea )
			pclMap->pclMapGeoInfo->Read(fp);
	}

	fclose(fp);
	
	
	pclMapArray[mapindex] = pclMap;
	OrgAddress[mapindex] = pclMapArray[mapindex];

#ifdef _DEBUG
//	loadTime = TABS( loadTime - GetTickCount() );
	TCHAR buf[256] = {0,};
	if ( GameMode == GAMEMODE_CLIENT )
	{
		StringCchPrintf( buf, 256, TEXT("MapLoadTime : %dms"), GetTickCount() - loadTime );
		pclClient->pclMessage->SetMsg( buf );
	}
	loadTime = GetTickCount();
#endif

	if ( pclClient->IsCountrySwitch( Switch_FieldObjectPreLoad) )
	{

		pclfieldobjectmanager->DeleteIfNotUse( 0 );

		bool bmainmap = ( mapindex==MAPINDEX_MAINFIELD )?true:false;

		bmainmap = false; // 일단 메인맵 로딩 다시 하게..

		for ( SI32 i=0; i < pclMap->GetXsize(); ++i )
		{
			for ( SI32 j=0; j < pclMap->GetYsize(); ++ j )
			{
				if ( pclMap->IsInMapArea( i, j ) == false )
					continue;

				SI32 fieldobject = pclMap->GetFieldObject_Unique(i, j);

				SI32 ref = pclfieldobjectmanager->FindRefFromUniqueMinus(fieldobject);
				if(ref < 0) continue;

				SI32 file = 0;
				SI32 font = 0;

				if( pclfieldobjectmanager->pclInfo[ref]->siFOSprRef < 0)
				{
					pclfieldobjectmanager->LoadSet(pclClient->GetFrame(), pclfieldobjectmanager->pclInfo[ref], bmainmap );
				}

				TSpr* pspr = pclfieldobjectmanager->pclInfo[ref]->GetSpr(pclfieldobjectmanager, 0);
			}
		}

#ifdef _DEBUG
		//loadTime = TABS( loadTime - GetTickCount() );
		if ( GameMode == GAMEMODE_CLIENT )
		{
			StringCchPrintf( buf, 256, TEXT("FOLoadTime : %dms"), GetTickCount() - loadTime );
			pclClient->pclMessage->SetMsg( buf );
		}
#endif
	}

	return pclMap;
}

bool cltMapManager::MakeLastMap(SI32 mapindex)
{
	SI32 i, j, k;

	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return false;
	if(pclMapArray[mapindex] == NULL)return false;


	pclMapArray[mapindex]->MakeLastMap();


	// 게이트를 추가한다. 
	// 맵 에디트 모드가 아니어야 한다. 

	//cyj 맵에디트 모드있때도 게이트 보이도록 수정
	//if(GameMode != GAMEMODE_MAPEDIT)
	//{
		for(i = 0;i < MAX_GATE_NUMBER;i++)
		{
			cltGate* pclgate = &pclGateManager->clGate[i];

			if(pclgate->FOUnique == 0)continue;
			
			if(pclgate->SrcMapIndex != mapindex)continue;
			
			pclMapArray[mapindex]->PutGateFieldObject(pclgate->SrcX, pclgate->SrcY, pclgate->FOUnique, pclgate->siUnique);
			
			// Gate Field Object주변에 충돌 영역을 설정한다. 
			for(k= -10;k<10;k++)
				for(j= - 10;j<10;j++)
				{
					SI32 collinfo = pclMapArray[mapindex]->CalcCollInfo(pclgate->SrcX + j, pclgate->SrcY + k);
					if(collinfo)
					{
						pclMapArray[mapindex]->SetCollMap(pclgate->SrcX + j, pclgate->SrcY + k, collinfo);
					}
				}
			
		}

	//}

	return true;
}

// 수렵용 지도인가. 
bool cltMapManager::IsHuntMap(SI32 siMapIndex)
{
	if(siMapIndex < 0)				return false;
	if(siMapIndex >= MAX_MAP_NUMBER)return false;

	// 200번 넘는 지도중 마을과연결되는 경우
	if(siMapIndex > 200 && siMapIndex < 200 + MAX_VILLAGE_NUMBER)
	{
		if(pclVillageManager->pclVillageInfo[siMapIndex - 200])	return true;
	}

	return false;
}
// 유효한 지역인가. 
bool cltMapManager::IsValidArea(SI32 mapindex, SI32 x, SI32 y)
{
	if(mapindex < 0)return false;
	if(mapindex  >= MAX_MAP_NUMBER)return false;
	if(pclMapArray[mapindex] == NULL)return false;

	if(x < 0)return false;
	if(pclMapArray[mapindex]->MH.MapXsize <= x)return false;

	if(y < 0)return false;
	if(pclMapArray[mapindex]->MH.MapYsize <= y)return false;

	return true;
}

bool cltMapManager::LoadMap(cltCommonLogic* pclclient, SI32 mapunique, SI32 index, SI32 villageunique,
							 SI32 parentmap, SI32 levellimit, TCHAR* mapname,
							 BOOL encountmap,BOOL seamap, BOOL landmap)
{
	TCHAR buffer[FILE_NAME_SIZE];

	TCHAR *pmaptype = NULL;
	
	pmaptype = pclMapTypeManager->GetMapTypeNameFromUnique(mapunique);
	if(pmaptype == NULL)return false;

	//sprintf( buffer, TEXT("%s\n"), pmaptype );
	

	StringCchPrintf(buffer, FILE_NAME_SIZE, TEXT("map\\%s\\%s.Map"), pmaptype, pmaptype);


	// 서버가 아니어야 타일을 불러온다. 
	// 서버에서는 타일을 로딩하지 않는다. 
	if(GameMode != GAMEMODE_SERVER)
	{
		//----------------------------
		// 지도의 헤더를 분석한다. 
		//----------------------------
		cltMapHeader clHeader;
		if(GetMapInfo(buffer, &clHeader) == FALSE)
		{
			MsgBox(TEXT("f9nnf"), TEXT("f9j2f:%s"), buffer);
			return FALSE;
		}
		
		
		//-----------------------------
		// 타일 세트를 불러온다. 
		//-----------------------------
		
		// 기존의 타일 세트를 삭제한다. 
		pclclient->pclTileManager->FreeTileSet();

		// 새로운 타일 세티를 불러온다. 
		pclclient->pclTileManager->LoadTileSet(clHeader.TileSet1, clHeader.TileSet2);
		

	}

	//-----------------------------
	// 지도를 불러온다. 
	//-----------------------------

	Load(index, mapunique, buffer, pclclient->pclCM, pclclient->pclTileManager, pclclient->pclFieldObjectManager);

	if(GameMode == GAMEMODE_SERVER)
	{
		pclMapArray[index]->siMapUnique = mapunique;
	}



	StringCchPrintf(buffer, FILE_NAME_SIZE, TEXT("map\\%s\\%s.Spr"), pmaptype, pmaptype);

	SI32 smallmapmode;

	// 게임의 모드에 따라 작은 지도의 모드도 달라진다. 
	if(GameMode == GAMEMODE_MAPEDIT)
	{
		smallmapmode = SMALLMAPMODE_MAPEDIT;
	}
	else
	{
		smallmapmode = SMALLMAPMODE_GAME;
	}

	pclMapArray[index]->MakeSmallMap(smallmapmode, buffer);

	// 메인 지도에서는 마을을 지도에 붙인다.
	if(index == 0)
	{
		pclMapArray[index]->DeattachVillage();

		// 마을을 불러온다.
		pclMapArray[index]->AttachVillage();
	}

	// 지도와 마을의 관계를 설정한다.
	pclMapArray[index]->siVillageUnique = villageunique;

    // 불러오거나 임의로 설정된 지도를 최종적으로 확정한다. 
    MakeLastMap(index);

	return TRUE;

}

// mapindex를 사용하여 지도를 불러온다. 
BOOL cltMapManager::LoadMap(cltCommonLogic* pclclient, SI32 srcmapindex, SI32 mapunique)
{
	SI32 i;

	for(i = 0;i < MAX_MAP_NUMBER;i++)
	{
		if(clUnitMapInfo[i].siMapUnique == 0)continue;

		if(srcmapindex == i)
		{
			if(mapunique == 0)mapunique = clUnitMapInfo[i].siMapUnique;
			LoadMap(pclclient, mapunique, i, clUnitMapInfo[i].siVillageUnique, clUnitMapInfo[i].siParentMap, clUnitMapInfo[i].siLevelLimit, clUnitMapInfo[i].szMapName, clUnitMapInfo[i].bEncountMap, clUnitMapInfo[i].bSeaMap, clUnitMapInfo[i].bLandMap);
			return true;
		}

	}

	return false;

}


// 모든 지도를 다 읽어온다. 
BOOL cltMapManager::LoadAllMap(cltCommonLogic* pclclient)
{
	SI32 i;

	for(i = 0;i < MAX_MAP_NUMBER;i++)
	{
		if(clUnitMapInfo[i].siMapUnique == 0)continue;

		// 모든 마을 지도를 불러오지 않는다. 
		if(clUnitMapInfo[i].siVillageUnique > CUR_VILLAGE_LIMIT)continue;
	
		LoadMap(pclclient, clUnitMapInfo[i].siMapUnique, i, clUnitMapInfo[i].siVillageUnique, clUnitMapInfo[i].siParentMap, clUnitMapInfo[i].siLevelLimit, clUnitMapInfo[i].szMapName, clUnitMapInfo[i].bEncountMap, clUnitMapInfo[i].bSeaMap, clUnitMapInfo[i].bLandMap);
	}

	return TRUE;
}


// 아이템을 떨어뜨릴 적절한 곳을 찾는다. 
bool cltMapManager::FindProperAreaForDrop(SI32 mapindex, SI32 x, SI32 y, SI32* ptargetx, SI32* ptargety)
{
	SI32 length = 0;
	SI32 minlength = 1000;
	SI32 minx = 0;
	SI32 miny = 0;
	SI32 i, j;
	SI32 block = BLOCK_DEEPWATER|BLOCK_SHALLOWWATER|BLOCK_CUSTOM|BLOCK_NORMAL;

	for(i = -2;i <= 2;i++)
		for(j = -2;j <= 2;j++)
		{
			SI32 tempx = x + j;
			SI32 tempy = y + i;
			
			// 지도 유효 범위를 체크한다. 
			if(pclMapArray[mapindex]->IsInMapArea(tempx, tempy) == false)continue;
			// 바다에는 물품을 버릴 수 없다. 
			if(pclMapArray[mapindex]->IsColl(tempx, tempy, block))continue;
			
			cltItemMapInfo* pclitemmapinfo = (cltItemMapInfo*)pclMapArray[mapindex]->GetItemMap(tempx, tempy);
			if(pclitemmapinfo == NULL)continue;
			// 이미 다른 물건이 있다면 실패. 
			if(pclitemmapinfo->uiItemUnique)continue ;
			
			length = max(TABS(j) , TABS(i));
			if(length < minlength)
			{
				minlength = length;
				minx = tempx;
				miny = tempy;
			}
		}
		
		// 가까운 영역에 버릴 곳이 없다면, 
		if(minlength == 1000)
		{
			return false;
		}
		
		*ptargetx = minx;
		*ptargety = miny;
		
		return true;
}

void cltMapManager::SetMapBasicInfo(SI32 mapindex, SI32 mapunique, 
									SI32 villageunique,
									SI32 minlevel, SI32 maxlevel,
									bool blockwarp,
									SI32 parentmap, bool encountmap, 
									bool seamap, bool landmap,bool fogmap,
									SI16 instancemap, bool guildmap, bool pkMap,
									SI32 userlimit,
									bool bCanMarket)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return ;

	clUnitMapInfo[mapindex].siMapUnique		= mapunique;
	clUnitMapInfo[mapindex].siVillageUnique	= villageunique;
	clUnitMapInfo[mapindex].siLevelLimit	= 0;
	clUnitMapInfo[mapindex].siMinLevel		= minlevel;
	clUnitMapInfo[mapindex].siMaxLevel		= maxlevel;
	clUnitMapInfo[mapindex].bBlockWarp		= blockwarp;
	clUnitMapInfo[mapindex].siParentMap		= parentmap;
	clUnitMapInfo[mapindex].bEncountMap		= encountmap;
	clUnitMapInfo[mapindex].bSeaMap			= seamap;
	clUnitMapInfo[mapindex].bLandMap		= landmap;
	clUnitMapInfo[mapindex].bFogMap			= fogmap;
	clUnitMapInfo[mapindex].siInstanceMap	= instancemap;
	clUnitMapInfo[mapindex].bGuildMap		= guildmap;
	clUnitMapInfo[mapindex].bPkMap			= pkMap;
	clUnitMapInfo[mapindex].siUserLimit		= userlimit;
	clUnitMapInfo[mapindex].bCanMarket		= bCanMarket;
}

bool cltMapManager::IsEncountMap(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return false;

	return clUnitMapInfo[mapindex].bEncountMap;

}
bool cltMapManager::IsSeaMap(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return false;

	return clUnitMapInfo[mapindex].bSeaMap;

}
bool cltMapManager::IsInstanceMap(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return false;

	return ( clUnitMapInfo[mapindex].siInstanceMap > INSTANCEMAP_TYPE_NONE );
}
bool cltMapManager::IsLandMap(SI32 mapindex)
{
	if( mapindex < 0 || mapindex >= MAX_MAP_NUMBER ) return false;

	return clUnitMapInfo[mapindex].bLandMap;
}

bool cltMapManager::IsFogMap(SI32 mapindex)
{
	if( mapindex < 0 || mapindex >= MAX_MAP_NUMBER )return false;

	return clUnitMapInfo[mapindex].bFogMap;
}

//길드 소유가 가능한 지도인가.
bool cltMapManager::IsGuildMap(SI32 mapindex )
{
	if( mapindex < 0 || mapindex >= MAX_MAP_NUMBER )return false;

	return clUnitMapInfo[mapindex].bGuildMap;
}

SI32 cltMapManager::GetParentMap(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return 0;

	return clUnitMapInfo[mapindex].siParentMap;
}

bool cltMapManager::IsPkMap(SI32 MapIndex)
{
	if(MapIndex < 0 || MapIndex >= MAX_MAP_NUMBER)
		return false;

	return clUnitMapInfo[MapIndex].bPkMap;
}

SI32 cltMapManager::GetLevelLimit(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return 0;

	//return clUnitMapInfo[mapindex].siLevelLimit;
	return clUnitMapInfo[mapindex].siMinLevel;
}

SI32 cltMapManager::GetMinLevel(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return 0;

	return clUnitMapInfo[mapindex].siMinLevel;
}

SI32 cltMapManager::GetMaxLevel(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return 0;

	return clUnitMapInfo[mapindex].siMaxLevel;
}

bool cltMapManager::IsEnterLevel(SI32 mapindex, SI32 level)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)	return false;
	if(	clUnitMapInfo[mapindex].siMinLevel <= level && 
		clUnitMapInfo[mapindex].siMaxLevel >= level)
	{
		return true;
	}

	return false;
}

bool cltMapManager::IsBlockWarp(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)	return false;

	if( clUnitMapInfo[mapindex].bBlockWarp == true )
	{
		return true;
	}

	return false;    
}

void cltMapManager::SetMapName(SI32 mapindex, TCHAR* pname)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return;

	StringCchCopy(clUnitMapInfo[mapindex].szMapName, MAX_MAP_NAME_SIZE, pname);
}

TCHAR* cltMapManager::GetMapName(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return NULL;

	return clUnitMapInfo[mapindex].szMapName;
}




// 지도의 유니크를 얻는다.
SI32 cltMapManager::GetMapUnique(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER)return 0;

	return clUnitMapInfo[mapindex].siMapUnique;
}
// 맵의 BGM을 설정한다.
void cltMapManager::SetBGM( SI32 mapindex, TCHAR* filename )
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return;

	StringCchCopy(clUnitMapInfo[mapindex].szBGMFileName, 256, filename );
}
bool cltMapManager::HaveCloneMap( SI32 mapindex )
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return false;

	return clUnitMapInfo[mapindex].bHaveCloneMap;
}
SI32 cltMapManager::GetUserLimit( SI32 mapindex )
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return 0;

	return clUnitMapInfo[mapindex].siUserLimit;
}
void cltMapManager::InitUserCount()
{
	for( SI32 i=0; i<MAX_MAP_NUMBER; i++ )
	{
		clUnitMapInfo[i].siUserCount = 0;
	}
}
void cltMapManager::AddUserCount( SI32 mapindex )
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return;

	++clUnitMapInfo[mapindex].siUserCount;
}
SI32 cltMapManager::GetUserCount( SI32 mapindex )
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return 0;

	if( pclClient->GameMode != GAMEMODE_SERVER ) return 0;

	SI32 userCount = 0;
	for ( SI32 i=0; i<MAX_PERSON_NUMBER; ++i )
	{
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[i];
		if ( pclClient->pclCM->IsValidID(i) )
		{
			if ( pclClient->pclCM->CR[i]->GetMapIndex() == mapindex )
			{
				++userCount;
			}
		}
	}
	return userCount;

//	return clUnitMapInfo[mapindex].siUserCount;
}

SI32 cltMapManager::GetCloneMap(SI32 mapindex)
{
	if(mapindex < 0 || mapindex >= MAX_MAP_NUMBER) return 0;

	if ( clUnitMapInfo[mapindex].bHaveCloneMap == false ) return 0;

	SI32 cloneindex = clUnitMapInfo[mapindex].siCloneIndex;

	SI32 selectedMapUserCount =0;
	SI32 selectedMapIndex = 0;

	for ( SI32 i=0; i < CLONEMAP_NUM ; ++i )
	{
		SI32 dstMap = clCloneMapInfo[cloneindex].siDstMapIndex[i];
		if ( dstMap <= 0 ) continue;

		if ( GetUserLimit( mapindex ) > GetUserCount( dstMap ) )
		{
			if ( selectedMapUserCount <= GetUserCount( dstMap ) )
			{
				selectedMapUserCount = GetUserCount( dstMap );
				selectedMapIndex = dstMap;
			}
		}
	}
	if ( selectedMapIndex > 0 )
	{
		return selectedMapIndex;
	}
	else
	{
		return 0;
	}
}
void cltMapManager::AddCloneMap(SI32 srcMapIndex, SI32 dstMapIndex)
{
	if(srcMapIndex < 0 || srcMapIndex >= MAX_MAP_NUMBER) return ;
	if(dstMapIndex < 0 || dstMapIndex >= MAX_MAP_NUMBER) return ;

	for ( SI32 i=0; i<MAX_CLONEMAP_TYPE; ++i )
	{
		if ( clCloneMapInfo[i].siSrcMapIndex == srcMapIndex )
		{
			if ( clCloneMapInfo[i].AddCloneMap( dstMapIndex ) )
			{
				//clUnitMapInfo[srcMapIndex].siCloneIndex = i;
				return;
			}
			else
			{
				MsgBox(TEXT("Error"), TEXT("Clone Map Add Error"));
				return;
			}
		}
	}

	for ( SI32 i=0; i<MAX_CLONEMAP_TYPE; ++i )
	{
		if ( clCloneMapInfo[i].siSrcMapIndex == 0 )
		{
			clCloneMapInfo[i].siSrcMapIndex = srcMapIndex;

			if (  clCloneMapInfo[i].AddCloneMap( dstMapIndex ) ) 	
			{ 
				clUnitMapInfo[srcMapIndex].siCloneIndex = i;
				clUnitMapInfo[srcMapIndex].bHaveCloneMap = true;

				return;
			}
		}
	}

	MsgBox(TEXT("Error"), TEXT("Clone Map Add Error"));
}

SI32 cltMapManager::GetSourceMap( SI32 clonemapindex )
{
	for (SI32 i=0; i<MAX_CLONEMAP_TYPE; i++)
	{
		for (SI32 j=0; j<CLONEMAP_NUM; j++)
		{
			if(clCloneMapInfo[i].siDstMapIndex[j] == clonemapindex)
				return clCloneMapInfo[i].siSrcMapIndex;
		}
	}

	return 0;
}

void cltMapManager::Action()
{
	// 서버에서만 처리한다.
	if( pclClient->GameMode != GAMEMODE_SERVER )						return;
	cltServer* pclserver = (cltServer*)pclClient;

	if( m_UpdateTimer_Action.IsTimed( ::GetTickCount() ) == false )		return;

	SI32	i;
	SI32	siMapType;

	// 해적선 게이트 처리
	if ( pclClient->IsCountrySwitch( Switch_PirateShip ) == true )
	{
		PirateShipGateProcess();
	}

	// 기형 2009.8.28 - 축제 이벤트 - 이벤트 게이트 
	/*if( pclClient->pclEventTimeManager->InEventTime("FestivalEvent", &pclserver->sTime) )
	{
		FestivalEventGateProcess(TRUE);
	}
	else
	{
		FestivalEventGateProcess(FALSE);
	}*/
	
	//KHY - 1113 - 크리스마스 이벤트 - 이벤트 게이트.
	if( pclClient->pclEventTimeManager->InEventTime("ChristmasEvent", &pclserver->sTime) )
	{
		ChirstmasEventGateProcess();
	}
	else
	{
		if ( pclserver->pclCM->IsValidID( m_siChristmasGatePositionID ) != false )
		{
			// 해당 아이디의 케릭터가 없다면 리턴
			cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->CR[m_siChristmasGatePositionID];
			if ( pclGateChar != NULL )
			{
				SI32 siGateKind		= pclClient->GetUniqueFromHash("KIND_SANTAGATE");	// 게이트 몬스터의 KIND

				// 해당 아이디의 케릭터를 받아왔지만 게이트가 아니라면 리턴
				if ( pclGateChar->GetKind() == siGateKind )
				{
					// 해당 게이트를 삭제하고
					pclGateChar->DeleteInCell();

					// 삭제가 완료되었으면 게이트 아이디를 다시 초기화시킴
					if ( pclserver->pclCM->DeleteChar( m_siChristmasGatePositionID ) == TRUE )
					{
						m_siChristmasGatePositionID = 0;
					}				
				}
			}
		}		
	}

	for( i=0; i < MAX_MAP_NUMBER; i++)
	{
		if( IsInstanceMap(i) == false )		continue;

		siMapType = GetInstanceMapType( i );

		switch ( siMapType )
		{
			case INSTANCEMAP_TYPE_GUILD:
				{
					ActionFor_GuildInstanceMap( i, siMapType );
				}
				break;

			case INSTANCEMAP_TYPE_PARTY:
				{
					ActionFor_PartyInstanceMap( i, siMapType );
				}
				break;

			case INSTANCEMAP_TYPE_VILLAGE:
				{
					ActionFor_VillageInstanceMap( i, siMapType );
				}
				break;

			case INSTANCEMAP_TYPE_SERVER:
				{
					ActionFor_ServerInstanceMap( i, siMapType );
				}
		} // switch ( GetInstanceMapType( i ) ) 종료

	} // for( i=0; i < MAX_MAP_NUMBER; i++) 종료
}

void cltMapManager::ActionFor_GuildInstanceMap( SI32 siMapIndex, SI16 siMapType )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( pclserver == NULL )							return;

	bool bEnd_InstanceMap = false;
	SI32 siParentMap = GetParentMap( siMapIndex );
	if( siParentMap <= 0 )							return;

	cltMapCommon* pclMap = GetMapPointer( siParentMap );
	if( pclMap == NULL )							return;
	if( pclMap->m_dwInstanceMapStartTime <= 0 )		return;


	// 게이트 몬스터를 잡았으므로 게이트 생성
	cltCharServer* pclchar = NULL;

	if( pclMap->m_siInstanceMapGateIndex < 0 )
	{
		if( pclMap->m_siGateMonID > 0)
		{
			if( IsInstanceNPC(pclMap->m_siGateMonID) )		pclchar = (cltCharServer*)pclClient->pclCM->CR[pclMap->m_siGateMonID];
			if( pclchar == NULL || 
				pclchar->GetKind() != pclClient->GetUniqueFromHash("KIND_KEY_RACCOON") )
			{
				pclMap->m_siInstanceMapGateIndex = rand() % pclInstanceMapGateManager->m_siMaxSetCount;
				NTCHARStringBuilder		kbuild;
				kbuild.SetFormat("m_siInstanceMapGateIndex : {1}, Max : {2} \n") << pclMap->m_siInstanceMapGateIndex << pclInstanceMapGateManager->m_siMaxSetCount;
				pclClient->pclLog->LogPrint((TCHAR*)(const TCHAR*)kbuild);
				MakeInstanceMapGate( siParentMap );

				// 맵에 있는 클라이언트에게 게이트 정보 전송
				cltInstanceMapGate	clGates[MAX_INSTANCEMAPGATE_COUNT];

				SI32 siCount = pclClient->pclMapManager->pclInstanceMapGateManager->GetInstanceMapGates( 
					siParentMap, pclMap->m_siInstanceMapGateIndex,
					clGates, MAX_INSTANCEMAPGATE_COUNT );

				cltGameMsgResponse_InstanceMap_GateInfo clinfo(clGates, siCount);
				cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTMAP_GATEINFO, clinfo.GetSize(), (BYTE*)&clinfo);
				pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg, siParentMap );

				cltServerResponseValue clreturn(0, SRVAL_INSTANTDUNGEON_MAKEGATE, 0, 0);
				// 클라이언트로 정보를 보낸다. 
				cltMsg clRtnMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
				pclserver->pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clRtnMsg, siParentMap );
			}
		}
	}

	// 보스 몬스터 사냥을 해서 인던 종료
	if( pclMap->m_siBossID > 0 )
	{
		pclchar = NULL;
		if( IsInstanceNPC(pclMap->m_siBossID) )			pclchar = (cltCharServer*)pclClient->pclCM->CR[pclMap->m_siBossID];

		if( pclchar == NULL || 
			pclchar->GetKind() != pclClient->GetUniqueFromHash("KIND_BIGRACCOON_AGIT") )
		{
			bEnd_InstanceMap = true;
		}
	}

	// 시간이 경과되어 인던 종료
	if( (DWORD)TABS(pclMap->m_dwInstanceMapStartTime - pclserver->CurrentClock) >= pclMap->m_dwInstanceMapMaxTime )
	{
		bEnd_InstanceMap = true;
	}

	SI32   siGuildMark = -1;
	if( bEnd_InstanceMap )
	{
		SI32 siInCharID = 0;
		LeaveInstanceMap( siMapIndex, &siInCharID );

		if ( pclClient->pclCM->IsValidID( siInCharID ) == true )
		{
			siGuildMark = pclClient->pclCM->CR[ siInCharID ]->pclCI->clBI.clGuildRank.siMarkIndex;
		}

		SI32 siClearTime = pclserver->CurrentClock - pclMap->m_dwInstanceMapStartTime;
		// DB에 결과를 전송한다.
		sDBRequest_InstanceMapPoint_Insert clInsert( INSTANCEMAPPOINT_TYPE_GUILD, pclMap->m_siInstanceMapData, pclMap->m_siInstanceMapScore, pclserver->pclTime->clDate.uiYear, siClearTime, pclserver->sTime );
		pclClient->SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clInsert);

		// 1등이 교체되는지 확인한다.
		bool bChangeTop = false;
		if( pclClient->pclGuildManager->siTopClearPoint < pclMap->m_siInstanceMapScore )	bChangeTop = true;

		// 1등 정보를 갱신한다.
		if( bChangeTop )
		{
			pclClient->pclGuildManager->siTopClearPoint = pclMap->m_siInstanceMapScore;

			TCHAR* pGuildName  = pclserver->pclGuildManager->GetGuildName(pclMap->m_siInstanceMapData);
			SI32   siScore     = pclClient->pclGuildManager->siTopClearPoint;

			cltGuildInfo* GuildInfo = pclserver->pclGuildManager->GetGuildInfo(pGuildName);
			if(GuildInfo)
			{
				SI32 id	= pclClient->pclCM->GetIDFromPersonID(GuildInfo->siMasterPersonID);
				TCHAR* pName = NULL;
				if(pclClient->pclCM->IsValidID(id))
				{
					pName = (TCHAR*)pclClient->pclCM->CR[id]->GetName();
				}
				//[추가 : 황진성 2008. 1. 17 => 최강 길드가 변경됨을 전체 유저에게 알림.]
				cltGameMsgResponse_InstantDungeon_Top_Change sendMsg(pGuildName, siGuildMark, siScore, pName);
				cltMsg clMsg( GAMEMSG_RESPONSE_INSTANTSDUNGEON_TOP_CHANGE, sizeof(sendMsg), (BYTE*)&sendMsg );
				pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);	
			}
		}

		InitInstanceMap( siMapIndex );
		pclserver->pclNPCManager->DeleteNPCInstance( siParentMap );

		if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
		{
			CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();
			if ( pclSE_Quest )
			{
				pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_INSTANCEMAPCLEAR, siMapType, 1 );
			}
		}
	}
	else
	{
		cltGameMsgResponse_cInstantsDungeonRunInfo	clInfo(0, pclMap->m_siInstanceMapScore, pclClient->pclGuildManager->siTopClearPoint, DUNGEONRUN_UPDATE, siMapType);
		cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS, sizeof(clInfo), (BYTE*)&clInfo);
		SendInInstanceMapUser( siParentMap, (sPacketHeader*)&clMsg );
	}

}

void cltMapManager::ActionFor_PartyInstanceMap( SI32 siMapIndex, SI16 siMapType  )
{
	cltServer*	pclserver			= (cltServer*)pclClient;
	if( pclserver == NULL )							return;

	bool		bEnd_InstanceMap	= false;	// 인던을 종료 시키는 변수
	SI32		siParentMap			= GetParentMap( siMapIndex );
	if( siParentMap <= 0 )							return;

	cltMapCommon* pclMap			= GetMapPointer( siParentMap );
	if( pclMap == NULL )							return;
	if( pclMap->m_dwInstanceMapStartTime <= 0 )		return;

	SI32		siAddBonusTime		= 0; // 보너스 몬스터를 잡았을 때 추가되는 시간
	SI32		siAddBonusCount		= 0; // 보너스 몬스터 카운터


	// 보너스 몬스터를 잡으면 각각 5분의 시간이 추가된다
	if ( pclMap->m_siInstanceMapGateIndex < 0 )
	{
		for ( SI32	siIndex=0; siIndex<MAX_INSTANCE_BONUS_MONSTER_NUMBER; siIndex++ )
		{
			cltCharServer*	pclBonusChar		= NULL;
			SI32			siBonusMonsterID	= pclMap->m_siBonusMonID[siIndex];

			if ( siBonusMonsterID <= 0 ) continue;
			
			// 보너스 몬스터가 있는지 없는지를 확인하기 위해 찾아본다
			if ( IsInstanceNPC(siBonusMonsterID) )
			{
				pclBonusChar = (cltCharServer*)pclClient->pclCM->CR[siBonusMonsterID];
			}

			// 보너스 몬스터를 불러오지 못한다거나 찾아본 몬스터의 카인드가 보너스 몬스터의 카인드와 다르면 보너스 타임 추가
			if ( (pclBonusChar == NULL) || (pclBonusChar->GetKind() != pclClient->GetUniqueFromHash("KIND_PTIMEBONUS")) )
			{
				siAddBonusTime				+= (INSTANCEMAP_PIRATESHIP_BONUSTIME);
				siAddBonusCount				+= 1;
			}
		} // for ( SI32	siIndex=0; siIndex<MAX_INSTANCE_BONUS_MONSTER_NUMBER; siIndex++ )
	} // if ( pclMap->m_siInstanceMapGateIndex < 0 ) 종료

	pclMap->m_siBonusMonCount = siAddBonusCount;

	// 보스 몬스터를 잡으면 해적선 종료
	if ( pclMap->m_siBossID > 0 )
	{
		cltCharServer* pclBossChar = NULL;

		if ( IsInstanceNPC(pclMap->m_siBossID) )
		{
			pclBossChar = (cltCharServer*)pclClient->pclCM->CR[pclMap->m_siBossID];
		}

		if ( (pclBossChar == NULL) || (pclBossChar->GetKind() != pclClient->GetUniqueFromHash("KIND_PIRATEMASTER")) )
		{
			bEnd_InstanceMap = true;
		}
	} // if ( pclMap->m_siBossID > 0 )

	// 기본 30분과 보너스 몬스터를 잡은수에 5분을 곱한 숫자를 더한 값을 보너스 타임으로 한다.
	if ( (DWORD)TABS(pclMap->m_dwInstanceMapStartTime - pclserver->CurrentClock) >= (pclMap->m_dwInstanceMapMaxTime+siAddBonusTime) ) 
	{
		bEnd_InstanceMap = true;
	}

	// 맵의 모든 몬스터를 죽여도 인던 종료
	if ( pclMap->m_siMaxMonsterNum <= pclMap->m_siKillCount )
	{
		bEnd_InstanceMap = true;
	}

	// 인던 종료
	if ( bEnd_InstanceMap == true )
	{
		pclClient->pclLog->FilePrint( TEXT("config/PirateShiplog.log"), TEXT("[END]\tPirateShip") );

		SI32	siInCharID		= 0;
		SI32	siPartyIndex	= 0;

		// 인던에 있는 파티원 모두를 내보낸다
		LeaveInstanceMap( siMapIndex, &siInCharID );

		// 인던에 있던 파티원 중 한명의 아이디를 뽑아서 파티 Index를 찾아낸다
		if ( pclClient->pclCM->IsValidID( siInCharID ) == true )
		{
			siPartyIndex = pclClient->pclCM->CR[ siInCharID ]->siPartyIndex;
		}

		// 맵에 있는 몬스터를 모두 죽여서 인던을 클리어한것이라면 파티원중에 한명에게 아이템을 준다
		if ( (pclMap->m_siMaxMonsterNum <= pclMap->m_siKillCount) && (siPartyIndex >= 0) && (siPartyIndex<MAX_PARTY_OBJ_NUM) )
		{
			pclClient->pclLog->FilePrint( TEXT("config/PirateShiplog.log"), TEXT("[CLEAR]\tPirateShip") );

			GiveItemForPartyMapClear( siPartyIndex );
			
			if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclserver->pclServerEventManager->GetServerEvent_Quest();
				if ( pclSE_Quest )
				{
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_INSTANCEMAPCLEAR, siMapType, 1 );
				}
			}
		} // if ( (pclMap->m_siMaxMonsterNum <= pclMap->m_siKillCount) && (siPartyIndex >= 0) && (siPartyIndex<MAX_PARTY_OBJ_NUM) ) 종료


		// 인던을 초기화 시킨다
		InitInstanceMap( siMapIndex );
		pclserver->pclNPCManager->DeleteNPCInstance( siParentMap );

	} // if ( bEnd_InstanceMap == true ) 종료
	else
	{
		SI32	siKillCount		= (pclMap->m_siMaxMonsterNum - pclMap->m_siKillCount);
		SI32	siBonusCount	= pclMap->m_siBonusMonCount;

		cltGameMsgResponse_cInstantsDungeonRunInfo	clInfo(0, siKillCount, siBonusCount, DUNGEONRUN_UPDATE, INSTANCEMAP_TYPE_PARTY);
		cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS, sizeof(clInfo), (BYTE*)&clInfo);
		SendPartyInInstanceMapUser( pclMap->m_siInstanceMapData, (sPacketHeader*)&clMsg );
	}
}

void cltMapManager::ActionFor_VillageInstanceMap( SI32 siMapIndex, SI16 siMapType )
{
}

void cltMapManager::ActionFor_ServerInstanceMap( SI32 siMapIndex, SI16 siMapType )
{
	cltServer*	pclserver			= (cltServer*)pclClient;
	if( pclserver == NULL )							return;

	bool		bEnd_InstanceMap	= false;	// 인던을 종료 시키는 변수
	SI32		siParentMap			= GetParentMap( siMapIndex );
	if( siParentMap <= 0 )							return;

	cltMapCommon* pclMap			= GetMapPointer( siParentMap );
	if( pclMap == NULL )							return;
	if( pclMap->m_dwInstanceMapStartTime <= 0 )		return;


	// 인던내 모든 몬스터를 죽였으므로 다시 몬스터 리젠
	if (pclMap->m_siMaxMonsterNum <= pclMap->m_siKillCount)
	{
		SI32			siIncGroupID	= pclMap->m_siNPCGroupID + 1;
		cltNPCGroup*	pclnpcgroup		= (cltNPCGroup*)pclserver->pclNPCManager->pclNPCGroup[ siIncGroupID ];


		if ( (NULL == pclnpcgroup) || (siMapIndex != pclnpcgroup->siMapIndex) )
		{
			for ( SI32 siGroupIndex=0; siGroupIndex<MAX_NPC_GROUP_NUMBER; siGroupIndex++ )
			{
				cltNPCGroup* pclSearchGroup = (cltNPCGroup*)pclserver->pclNPCManager->pclNPCGroup[ siGroupIndex ];

				if ( (NULL != pclSearchGroup) && (siMapIndex == pclSearchGroup->siMapIndex) )
				{
					siIncGroupID = siGroupIndex;
					break;
				}
			}
		}

		pclMap->m_siMaxMonsterNum	= 0;
		pclMap->m_siKillCount		= 0;
		pclMap->m_siNPCGroupID		= siIncGroupID;
		pclMap->m_siClearStep		+= 1;

		pclserver->pclNPCManager->MakeNPCInstance( siMapIndex, 0 );
	}

	// 인던 종료 시간
	if ( (DWORD)TABS(pclMap->m_dwInstanceMapStartTime - pclserver->CurrentClock) >= pclMap->m_dwInstanceMapMaxTime )
	{
		bEnd_InstanceMap = true;
	}

	// 인던 종료
	if ( bEnd_InstanceMap == true )
	{
		if ( pclserver->IsCountrySwitch(Switch_Server_Event) )
		{
			SI32 siIndex = siMapIndex - MAPINDEX_SERVEREVENT_DUNGEON1;

			pclserver->pclServerEventManager->SetInstanceMapClear(siIndex, true);
			pclserver->pclServerEventManager->AddInstanceMapStepCount( siIndex, pclMap->m_siClearStep );
			
			if(true == pclserver->pclServerEventManager->IsAllInstanceMapClear())
			{
				pclserver->pclServerEventManager->ManagerExcute( SERVER_EVENT_COMMANDTYPE_INDUN_END );
			}
		}

		LeaveInstanceMap( siMapIndex );

		// 인던을 초기화 시킨다
		InitInstanceMap( siMapIndex );
		pclserver->pclNPCManager->DeleteNPCInstance( siParentMap );
		
	}
	else
	{
		SendServrEventInstanceMapInfo( siParentMap );
	}
}

// return  > 0 : 들어갈수 있는 맵의 인덱스
//         = 0 : 인원수 초과
//         < 0 : 더이상 들어갈 맵이 없음
SI32 cltMapManager::GetEnterableInstanceMapIndex( SI32 siMapIndex, cltCharServer* pclchar )
{
	if( IsInstanceMap( siMapIndex ) == false )			return 0;
	if( pclchar == NULL )								return 0;
	if( pclClient->GameMode != GAMEMODE_SERVER )		return 0;

	SI32	siRetMapIndex = 0;

	SI32	siParentMapIndex = GetParentMap( siMapIndex );
	if( siParentMapIndex == 0 )							return 0;
	if( IsInstanceMap( siParentMapIndex ) == false )	return 0;

	SI32 siCharInstanceData = 0;
	// 맵의 타입에 따라 캐릭터의 정보를 복사한다.
	switch( clUnitMapInfo[siParentMapIndex].siInstanceMap )
	{
	case INSTANCEMAP_TYPE_GUILD:
		{
			if(pclchar->pclCI->clBI.clGuildRank.IsGuildMember() == true)
				siCharInstanceData = pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex;
		}
		break;
	case INSTANCEMAP_TYPE_PARTY:	siCharInstanceData = pclchar->siPartyIndex;								break;
	case INSTANCEMAP_TYPE_VILLAGE:	siCharInstanceData = pclchar->pclCI->clBI.siHomeVillage;				break;
	case INSTANCEMAP_TYPE_SERVER:	siCharInstanceData = siMapIndex;										break;
	}
	if( siCharInstanceData <= 0	)						return 0;

	cltMapCommon* pclParentMap = GetMapPointer( siParentMapIndex );
	if( pclParentMap == NULL)							return 0;

	bool bEnterable = false;

	// 길드인 경우 길드 이름도 체크한다.
	if( clUnitMapInfo[siParentMapIndex].siInstanceMap == INSTANCEMAP_TYPE_GUILD)
	{
		if( pclParentMap->m_siInstanceMapData == siCharInstanceData && 
			strcmp(pclParentMap->m_szGuildName, pclchar->pclCI->clBI.clGuildRank.szGuildName) == 0 )
			bEnterable = true;
	}
	else
	{
		if( pclParentMap->m_siInstanceMapData == siCharInstanceData )
			bEnterable = true;
	}
	
	// 1.1 기존 맵에 입장할 수 있는 맵을 찾는다.
	if( bEnterable )
	{
		if( GetUserLimit( siParentMapIndex ) > GetUserCountByParentMap( siParentMapIndex ) )
			siRetMapIndex = siParentMapIndex;
		else
            siRetMapIndex = -1;
	}

	// 1.2 기존 맵에 입장할 수 있는 맵을 찾는다. - 클론맵.
	if( siRetMapIndex <= 0 && clUnitMapInfo[siParentMapIndex].bHaveCloneMap )
	{
		SI32 cloneindex = clUnitMapInfo[siParentMapIndex].siCloneIndex;

		for ( SI32 i=0; i < CLONEMAP_NUM ; ++i )
		{
			SI32 dstMap = clCloneMapInfo[cloneindex].siDstMapIndex[i];
			if ( dstMap <= 0 )		continue;

			cltMapCommon* pclMap = GetMapPointer( dstMap );
			if( pclMap == NULL)		continue;

			bEnterable = false;
			// 길드인 경우 길드 이름도 체크한다.
			if( clUnitMapInfo[dstMap].siInstanceMap == INSTANCEMAP_TYPE_GUILD)
			{
				if( pclMap->m_siInstanceMapData == siCharInstanceData && 
					strcmp(pclMap->m_szGuildName, pclchar->pclCI->clBI.clGuildRank.szGuildName) == 0 )
					bEnterable = true;
			}
			else
			{
				if( pclMap->m_siInstanceMapData == siCharInstanceData )
					bEnterable = true;
			}

			if( bEnterable )
			{
				if( GetUserLimit( dstMap ) > GetUserCountByParentMap( dstMap ) )
					siRetMapIndex = dstMap;
				else
					siRetMapIndex = -1;
			}
		}
	}

	// 1.3 기존 맵에 유저가 모두 다 찼다.
	if( siRetMapIndex < 0 )						return -1;

	// 2.1 새로 입장할 수 있는 맵을 찾는다.
	if( siRetMapIndex <= 0 )
	{
		if( pclParentMap->m_siInstanceMapData == 0 )
		{
			siRetMapIndex = siParentMapIndex;
		}

		// 2.2 새로 입장할 수 있는 맵을 찾는다. - 클론맵.
		if( siRetMapIndex <= 0 && clUnitMapInfo[siParentMapIndex].bHaveCloneMap )
		{
			SI32 cloneindex = clUnitMapInfo[siParentMapIndex].siCloneIndex;

			for ( SI32 i=0; i < CLONEMAP_NUM ; ++i )
			{
				SI32 dstMap = clCloneMapInfo[cloneindex].siDstMapIndex[i];
				if ( dstMap <= 0 )		continue;

				cltMapCommon* pclMap = GetMapPointer( dstMap );
				if( pclMap == NULL)		continue;

				if( pclMap->m_siInstanceMapData == 0 )
				{
					siRetMapIndex = dstMap;
					break;
				}
			}
		}
	}
    
	return siRetMapIndex;
}

SI32 cltMapManager::GetUserCountByParentMap( SI32 mapindex )
{
	if( mapindex < 0 || mapindex >= MAX_MAP_NUMBER )	return 0;
	if( pclClient->GameMode != GAMEMODE_SERVER )		return 0;

	SI32 siParentMapIndex = pclClient->pclMapManager->GetParentMap(mapindex);
	if( siParentMapIndex < 0 || siParentMapIndex >= MAX_MAP_NUMBER )	return 0;

	SI32 userCount = 0;
	for ( SI32 i=0; i<MAX_PERSON_NUMBER; ++i )
	{
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[i];
		if ( pclClient->pclCM->IsValidID(i) )
		{
			// 캐릭터가 있는 맵 인덱스
			SI32 siCharParentMap = GetParentMap( pclchar->GetMapIndex() );
			if(siCharParentMap < 0 || siCharParentMap >= MAX_MAP_NUMBER)	continue;

			// 같은 맵에 있는 캐릭터의 수를 센다.
			if( siParentMapIndex != siCharParentMap )						continue;

			// 죽은 캐릭터 체크 - 죽은 캐릭터중
			// KilledMode가 KILLEDMODE_INSTANCEMAP이 아니면, 쓸데 없는 캐릭터이다.
			if( pclClient->pclCM->IsAlive(i) == FALSE && pclchar->siKilledMode != KILLEDMODE_INSTANCEMAP )		continue;

			++userCount;
		}
	}
	return userCount;
}

SI32 cltMapManager::GetUserCountByMapIndex( SI32 siMapIndex )
{
	if ( (0 > siMapIndex) || (MAX_MAP_NUMBER <= siMapIndex) )
	{
		return 0;
	}
	
	if ( GAMEMODE_SERVER != pclClient->GameMode )		
	{
		return 0;
	}

	SI32 siUserCount = 0;

	for ( SI32 i=0; i<MAX_PERSON_NUMBER; ++i )
	{
		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[i];
		if ( pclClient->pclCM->IsValidID(i) )
		{
			// 캐릭터가 있는 맵 인덱스
			SI32 siUSerMapIndex = pclchar->GetMapIndex();
			if ( (0 > siUSerMapIndex) || (MAX_MAP_NUMBER <= siUSerMapIndex) )	
			{
				continue;
			}

			// 같은 맵에 있는 캐릭터의 수를 센다.
			if( siMapIndex != siUSerMapIndex )						
			{
				continue;
			}

			// 죽은 캐릭터 체크 - 죽은 캐릭터중
			// KilledMode가 KILLEDMODE_INSTANCEMAP이 아니면, 쓸데 없는 캐릭터이다.
			if( pclClient->pclCM->IsAlive(i) == FALSE && pclchar->siKilledMode != KILLEDMODE_INSTANCEMAP )		continue;

			++siUserCount;
		}
	}

	return siUserCount;
}

SI16 cltMapManager::GetInstanceMapType( SI32 siMapIndex )
{
	if ( IsInstanceMap( siMapIndex ) == false )
	{
		return INSTANCEMAP_TYPE_NONE;
	}

	return clUnitMapInfo[siMapIndex].siInstanceMap;
}

bool cltMapManager::EnterInstanceMap( SI32 parentmapindex, cltCharServer* pclchar )
{
	cltServer* pclserver = (cltServer*)pclClient;

	cltMapCommon* pclMap = GetMapPointer( parentmapindex );
	if( pclMap == NULL)									return false;
	if( pclchar == NULL)								return false;

	SI32 siCharInstanceData = 0;
	// 맵의 타입에 따라 캐릭터의 정보를 복사한다.
	switch( clUnitMapInfo[parentmapindex].siInstanceMap )
	{
	case INSTANCEMAP_TYPE_GUILD:	
		{
			// [추가 : 황진성 2008. 1. 25 => 인던 입장시 길드조건 검사.]
			if( pclchar->pclCI->clBI.clGuildRank.IsGuildMember())
			{
				siCharInstanceData = pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex;	
			}
		}
		break;
	case INSTANCEMAP_TYPE_PARTY:	siCharInstanceData = pclchar->siPartyIndex;								break;
	case INSTANCEMAP_TYPE_VILLAGE:	siCharInstanceData = pclchar->pclCI->clBI.siHomeVillage;				break;
	case INSTANCEMAP_TYPE_SERVER:	siCharInstanceData = parentmapindex;									break;
	}
	if( siCharInstanceData <= 0	)						return false;

	// 입장할 수 없는 맵에 입장하려고 한다.
	if( pclMap->m_siInstanceMapData > 0 && pclMap->m_siInstanceMapData != siCharInstanceData)		return false;

	if( pclMap->m_siInstanceMapData == 0 )
	{
		pclMap->m_siInstanceMapData = siCharInstanceData;

		// 맵 시작 시간
		if ( pclserver->IsCountrySwitch(Switch_Server_Event) && (pclserver->pclServerEventManager) )
		{
			if ( INSTANCEMAP_TYPE_SERVER == clUnitMapInfo[parentmapindex].siInstanceMap )
			{
				pclMap->m_dwInstanceMapStartTime = pclserver->pclServerEventManager->GetInstanceMapInfo()->GetStartTime() ;
			}
		}
		
		// 시작 시간이 설정되어있지 않으면 현재 시간으로
		if ( 0 >= pclMap->m_dwInstanceMapStartTime )
		{
			pclMap->m_dwInstanceMapStartTime = pclClient->CurrentClock;
		}

		pclMap->m_dwInstanceMapMaxTime = pclMap->GetInstanceMapMaxTime();
		
		// 맵이 시작되었으므로 몬스터 생성
		pclserver->pclNPCManager->MakeNPCInstance( parentmapindex, 0, false );

		if( clUnitMapInfo[parentmapindex].siInstanceMap == INSTANCEMAP_TYPE_GUILD )
		{
			// 길드맵인 경우 길드 이름도 저장
			StringCchCopy(pclMap->m_szGuildName, sizeof(pclMap->m_szGuildName), pclchar->pclCI->clBI.clGuildRank.szGuildName);

			//[추가 : 황진성 2008. 1. 14 => 해당 길드원에게 인던에 참여가능함을 길드 채팅창으로 날린다.]
			TCHAR* pText = GetTxtFromMgr(7832);
			cltGameMsgResponse_Chat clChat(pclchar->GetCharUnique(), CHATMODE_GUILD, (TCHAR*)pclchar->GetName(), pText);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);

			//KHY - 0131 - 길드 멤버 메시지 전달 - 이름으로 검색 - 유니크번호 검사제외!
			pclClient->pclCM->SendAllGuildMemberMsg((sPacketHeader*)&clMsg, pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex,pclchar->pclCI->clBI.clGuildRank.szGuildName);
		}
	}
	
	return true;
}

void cltMapManager::InitInstanceMap( SI32 mapindex )
{
	cltMapCommon* pclMap = GetMapPointer( mapindex );
	if( pclMap == NULL)									return;

	pclMap->m_siInstanceMapData			= 0;
	pclMap->m_dwInstanceMapStartTime	= 0;
	pclMap->m_dwInstanceMapMaxTime		= pclMap->GetInstanceMapMaxTime();
	pclMap->m_siInstanceMapScore		= 0;
	pclMap->m_siInstanceMapGateIndex	= -1;
	pclMap->m_siGateMonID				= -1;
	pclMap->m_siBossID					= -1;
	pclMap->m_siMaxMonsterNum			= 0;
	pclMap->m_siKillCount				= 0;
	pclMap->m_siBonusMonCount			= 0;
	pclMap->m_siClearStep				= 0;
	pclMap->m_siNPCGroupID				= 0;
	
	ZeroMemory(pclMap->m_szGuildName, sizeof(pclMap->m_szGuildName));
#ifdef _SAFE_MEMORY
	pclMap->m_siBonusMonID.ZeroMem();
#else
	ZeroMemory(pclMap->m_siBonusMonID, sizeof(pclMap->m_siBonusMonID));
#endif
}


void cltMapManager::MakeInstanceMapGate( SI32 parentmapindex )
{
	if( IsInstanceMap( parentmapindex ) == false )					return;
	cltMapCommon* pclParentMap = GetMapPointer( parentmapindex );
	if( pclParentMap == NULL )										return;
	if( pclParentMap->m_siInstanceMapGateIndex < 0 )				return;

	SI32	i;
	for( i=0; i<MAX_TOTAL_INSTANCEMAPGATE_NUMBER; i++ )
	{
		cltInstanceMapGate* pclGate = pclInstanceMapGateManager->GetGatebyIndex(i, pclParentMap->m_siInstanceMapGateIndex);
		if( pclGate == NULL )								continue;
		if(	pclGate->siUnique <= 0)							continue;
		if(	pclGate->FOUnique <= 0)							continue;

		SI32 mapindex = pclGate->SrcMapIndex;
		if( mapindex <= 0 || mapindex >= MAX_MAP_NUMBER )	continue;
		if( GetParentMap( mapindex ) != parentmapindex )	continue;

		cltMapCommon* pclMap = GetMapPointer( mapindex );
		if( pclMap == NULL )								continue;

		// 기존의 문은 삭제한다. 
		pclMap->DeleteFieldObject( pclGate->SrcX, pclGate->SrcY );
		// 새로운 문을 만든다. 
		pclMap->PutFieldObject( pclGate->SrcX, pclGate->SrcY, pclGate->FOUnique, pclGate->siUnique );
	}	
}

// 해적선 게이트 관련 처리 함수
void cltMapManager::PirateShipGateProcess()
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	UI16 uiNowMinute	= pclserver->sTime.wMinute;								// 현재 시간(분)
	bool bOpenGate		= ((uiNowMinute == 0) || (uiNowMinute == 30));			// 30분 단위로 게이트가 열린다
	bool bCloseGate		= ((uiNowMinute == 10) || (uiNowMinute == 40));			// 게이트가 열린후 10분후 닫힌다

	SI32 siGateKind		= pclClient->GetUniqueFromHash("KIND_PIRATESHIP_GATE");	// 게이트 몬스터의 KIND


	if ( siGateKind <= 0 )
	{
		return;
	}

	if ( (bOpenGate == false) && (bCloseGate == false) )
	{
		return;
	}

	// 30분 단위로 메인 맵에 해적선 게이트가 생성된다
	if ( bOpenGate && (m_siGatePositionID == 0) )
	{
		// 게이트가 나타나는 위치( 이중에서 랜덤하게 한곳이 나타남 )
		POINT pointGate[INSTANCEMAP_PIRATESHIP_MAX_GATE] = {
			{160,160}
			,{169,96}
			,{214,286}
			,{176,339}
			,{360,251}
			,{414,104}
			,{214,423}
			,{437,371}
			,{291,529}
			,{269,717}
			,{475,714}
			,{578,574}
		};
		
		// 위의 좌표를 기준으로 랜덤하게 값을 뽑아 온다
		SI32 siGateIndex = (SI32)(rand() % INSTANCEMAP_PIRATESHIP_MAX_GATE);
		if ( (siGateIndex < 0) || (siGateIndex >= INSTANCEMAP_PIRATESHIP_MAX_GATE) )
		{
			return;
		}
		
		// 실제로 뽑아온 게이트의 X,Y좌표
		SI32 siX = (SI32)pointGate[siGateIndex].x;
		SI32 siY = (SI32)pointGate[siGateIndex].y;

		// 해적선 게이트 생성
		m_siGatePositionID = pclserver->SetNPCChar(siGateKind, VILLAGE_NONE, NULL, 1, 0, siX, siY, 0, NPCITEMMODE_NONE, NULL );

		// 해적선이 나타났다는 메시지를 보냄
		if ( m_siGatePositionID	> 0 )
		{
			//cltMsg clMsg( GAMEMSG_RESPONSE_PIRATESHIP_APPEAR, 0, NULL );
			//pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );

			// 서버리턴 사용
			cltServerResponseValue clreturn(0, SRVAL_PIRATESHIP_APPEAR, siX, siY);
			// 클라이언트로 정보를 보낸다. 
			cltMsg clRtnMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
			
			pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clRtnMsg );

		}
	}

	// 게이트가 생성된뒤 10분후 게이트가 사라진다
	if ( bCloseGate && (m_siGatePositionID > 0) )
	{	
		// 게이트가 생성될때 받아온 아이디로 조건을 진행한다
		if ( pclserver->pclCM->IsValidID( m_siGatePositionID ) == false )
		{
			return;
		}
		
		// 해당 아이디의 케릭터가 없다면 리턴
		cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->CR[m_siGatePositionID];
		if ( pclGateChar == NULL )
		{
			return;
		}
		
		// 해당 아이디의 케릭터를 받아왔지만 게이트가 아니라면 리턴
		if ( pclGateChar->GetKind() != siGateKind )
		{
			return;
		}
		
		// 해당 게이트를 삭제하고
		pclGateChar->DeleteInCell();

		// 삭제가 완료되었으면 게이트 아이디를 다시 초기화시킴
		if ( pclserver->pclCM->DeleteChar( m_siGatePositionID ) == TRUE )
		{
			m_siGatePositionID = 0;
		}
	}
}

//KHY - 1113 - 크리스마스 이벤트
void cltMapManager::ChirstmasEventGateProcess()
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL)
		return;

	cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->CR[m_siChristmasGatePositionID];
	if(pclGateChar != NULL) // 이미 있다.
		return;


	SI32 siGateKind		= pclClient->GetUniqueFromHash("KIND_SANTAGATE");	// 게이트 몬스터의 KIND


	if ( siGateKind <= 0 )
	{
		return;
	}

	// 게이트가 나타나는 위치
	POINT pointGate[1] = {
		{292,327}
	};
	
	// 위의 좌표를 기준으로 값을 뽑아 온다
	SI32 siGateIndex = 0;
	
	// 실제로 뽑아온 게이트의 X,Y좌표
	SI32 siX = (SI32)pointGate[siGateIndex].x;
	SI32 siY = (SI32)pointGate[siGateIndex].y;

	//  게이트 생성
	m_siChristmasGatePositionID = pclserver->SetNPCChar(siGateKind, VILLAGE_NONE, NULL, 1, 0, siX, siY, 0, NPCITEMMODE_NONE, NULL );
/*
		//메시지를 보냄
		if ( m_siGatePositionID	> 0 )
		{
			//cltMsg clMsg( GAMEMSG_RESPONSE_PIRATESHIP_APPEAR, 0, NULL );
			//pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );

			// 서버리턴 사용
			cltServerResponseValue clreturn(0, SRVAL_PIRATESHIP_APPEAR, siX, siY);
			// 클라이언트로 정보를 보낸다. 
			cltMsg clRtnMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
			
			pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clRtnMsg );

		}
*/
}

//기형 - 2009.8.28 - 축제 이벤트
void cltMapManager::FestivalEventGateProcess(BOOL bBeingNPC)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL)
		return;

	cltCharServer* pclGateChar = (cltCharServer*)pclClient->pclCM->GetCharServer(m_siFestivalGatePositionID);

	SI32 siGateKind		= pclClient->GetUniqueFromHash("KIND_FESTIVALGATE");	// 게이트 몬스터의 KIND

	if ( siGateKind <= 0 )
	{
		return;
	}

	if( TRUE == bBeingNPC)
	{
		if(pclGateChar != NULL) // 이미 있다.
			return;
	}
	else
	{
		if(pclGateChar != NULL)
		{
			// 게이트가 아니라면 
			if(pclGateChar->GetKind() != siGateKind)
			{
				return;
			}
			pclGateChar->SetLife(0);
			m_siFestivalGatePositionID = 0;

			// 축제 이벤트 맵에 있던 사용자를 엔펠리스로 워프 시킨다.
			/*cltCharServer* pclCharServer = NULL;
			for (SI32 id = 0; id < MAX_PERSON_NUMBER; id++)
			{

				pclCharServer = pclClient->pclCM->GetCharServer(id);
				if( NULL == pclCharServer)
					continue;

				if(  MAPINDEX_FESTIVAL == pclCharServer->GetMapIndex())
				{
					SI32		siWarpX = 288;
					SI32		siWarpY = 354;
					cltWarpInfo clWarp(1, MAPINDEX_MAINFIELD, false, false, siWarpX, siWarpY, -1, -1);

					pclCharServer->SetWarpInfo( &clWarp, 1024 );
					pclCharServer->Warp();
				}
			}*/
		}
		return;
	}
	
	// 게이트가 나타나는 위치
	POINT pointGate[1] = {
		{243,322}
	};

	// 위의 좌표를 기준으로 값을 뽑아 온다
	SI32 siGateIndex = 0;

	// 실제로 뽑아온 게이트의 X,Y좌표
	SI32 siX = (SI32)pointGate[siGateIndex].x;
	SI32 siY = (SI32)pointGate[siGateIndex].y;

	//  게이트 생성
	m_siFestivalGatePositionID = pclserver->SetNPCChar(siGateKind, VILLAGE_NONE, NULL, 1, 0, siX, siY, 0, NPCITEMMODE_NONE, NULL );
}


// 인던 종료시 인던에 있는 케릭터 모두 밖으로 보내는 함수
void cltMapManager::LeaveInstanceMap( IN SI32 siMapIndex, OUT SI32* psiInCharID/* =NULL  */)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if( pclserver == NULL )							return;

	SI32 siParentMap = GetParentMap( siMapIndex );
	if( siParentMap <= 0 )							return;

	cltMapCommon* pclMap = GetMapPointer( siParentMap );
	if( pclMap == NULL )							return;
	if( pclMap->m_dwInstanceMapStartTime <= 0 )		return;

	SI32 siMapType = GetInstanceMapType( siParentMap );

	// 맵에 있는 캐릭터를 맵 밖으로 이동시킨다.
	SI32 index = 0;
	SI32 id;

	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;

		cltCharServer* pclchar = (cltCharServer* )pclClient->pclCM->CR[id];

		if( !IsPC(id) ) continue;																// 유저
		if( GetParentMap(pclClient->pclCM->CR[id]->GetMapIndex()) != siParentMap)	continue;	// 인던에 없음.

		SI32 x = 0 , y = 0;
		cltWarpInfo clWarpInfo(1, 0, false, true, x, y, -1, -1);

		if (pclGateManager->FindMainFieldPos( MAPINDEX_PALACE, &x, &y ) == false )
			return;

		clWarpInfo.uiMapIndex = 0; //무조건 메인 맵 상태다.
		clWarpInfo.uiX = x+2;
		clWarpInfo.uiY = y+2;

		// 엔펠리스 앞으로 이동 시킨다.
		if (pclClient->pclCM->IsAlive(id) == FALSE)
		{
			pclchar->siKilledMode = 0;
		}
		else
		{
			SI32 siVillageMapIndex	= pclchar->pclCI->clBI.siHomeVillage;

			if ( pclserver->IsCountrySwitch(Switch_Server_Event) && (0 < siVillageMapIndex))
			{
				SI32 siMapTypeUnique	= pclserver->pclMapManager->pclMapArray[ siVillageMapIndex ]->siMapUnique;
				UI32 uiX				= (UI32)pclserver->pclMapManager->pclMapTypeManager->pclMapTypeInfo[ siMapTypeUnique ]->siCenterX;
				UI32 uiY				= (UI32)pclserver->pclMapManager->pclMapTypeManager->pclMapTypeInfo[ siMapTypeUnique ]->siCenterY;
				
				clWarpInfo.uiMapIndex	= (UI32)siVillageMapIndex;
				clWarpInfo.uiX			= uiX;
				clWarpInfo.uiY			= uiY;
			}

			pclchar->SetWarpInfo(&clWarpInfo, 3000);
			pclchar->Warp();
		}
		// 인던 내 상황판 종료
		switch ( siMapType )
		{
			case INSTANCEMAP_TYPE_GUILD:
				{
					cltGameMsgResponse_cInstantsDungeonRunInfo	clInfo(0, pclMap->m_siInstanceMapScore, pclClient->pclGuildManager->siTopClearPoint, DUNGEONRUN_END, siMapType);
					cltMsg clMsg(GAMEMSG_RESPONSE_INSTANTSDUNGEON_RUN_STATUS, sizeof(clInfo), (BYTE*)&clInfo);

					pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
				}
				break;

		}
		
		// 해당 맵에 있는 캐릭터 아이디를 보낸다( 맨마지막에 찾아낸 캐릭터 )
		if ( psiInCharID != NULL )
		{
			*psiInCharID = id;
		}
	} // while(id = pclClient->pclCM->GetCharOrder(index)) 종료
}

// 파티원의 리스트를 구하고 리턴값으로 파티원이 몇명인지 알 수 있다
SI08 cltMapManager::GetInstanceMapPartyList( IN SI32 siPartyIndex, OUT SI32* psiPartyList )
{
	if ( siPartyIndex <= 0 )		return -1;
	if ( psiPartyList == NULL )		return -1;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )		return -1;


	CPartyObj* pclparty = pclClient->pclPartyMgr->GetPartyObj( siPartyIndex );
	if ( pclparty == NULL )			return -1;

	SI08 siTotalPartyNum = 0;


	// 유효한 파티원의 리스트를 구한다. 
	for ( SI32 siPartyNum=0; siPartyNum<MAX_PARTY_USER_NUM; siPartyNum++ )
	{
		// 파티원을 한명씩 뽑아낸다
		stPartyUser* pstPartyMember = pclparty->GetPartyUser(siPartyNum);

		// 파티원을 못뽑아냈거나 파티상태가 아니라면 리턴
		if ( (pstPartyMember == NULL) || (pstPartyMember->bPartyStatus == false) )
		{
			continue;
		}
		
		// 현재 뽑아온 파티원의 아이디가 유효하지 않다면 리턴
		if ( pclClient->pclCM->IsValidID( pstPartyMember->siCharUnique ) == false )
		{
			continue;
		}
		
		// 뽑아온 파티 리스트의 PersonID와 실제로 존재하는 케릭터의 PersonID가 다르면 리턴
		if ( pclClient->pclCM->CR[ pstPartyMember->siCharUnique ]->pclCI->GetPersonID() != pstPartyMember->siPersonID )
		{
			continue;
		}

		psiPartyList[ siTotalPartyNum ] = pstPartyMember->siCharUnique;
		siTotalPartyNum++;
	} // for ( SI32 siPartyNum=0; siPartyNum<MAX_PARTY_USER_NUM; siPartyNum++ ) 종료

	return siTotalPartyNum;

}

// [영훈] 인던안에 있는 유저에게 패킷을 보낸다
void cltMapManager::SendInInstanceMapUser( SI32 siParentMap, sPacketHeader* psPacketHeader )
{
	if ( psPacketHeader == NULL )								return;
	if ( (siParentMap < 0) || (MAX_MAP_NUMBER<siParentMap) )	return;

	SI32 siIndex	= 0;
	SI32 siID		= 0;


	while(siID = pclClient->pclCM->GetCharOrder(siIndex))
	{
		siIndex++;

		// 유효한 아이디만 뽑아온다
		if ( pclClient->pclCM->IsValidID( siID ) == false )
		{
			continue;
		}

		cltCharServer* pclchar = (cltCharServer* )pclClient->pclCM->CR[siID];
        if ( pclchar == NULL )
		{
			continue;
		}
		// 인던에 없음
		if( GetParentMap(pclchar->GetMapIndex()) != siParentMap )
		{
			continue;
		}

		pclchar->SendNetMsg( psPacketHeader );
	}
}

// [영훈] 파티인던 맵 내에 있는 유저에게 패킷을 보낸다
void cltMapManager::SendPartyInInstanceMapUser( SI32 siPartyIndex, sPacketHeader* psPacketHeader )
{
	if ( psPacketHeader == NULL )								return;
	if ( (siPartyIndex<0) || (MAX_MAP_NUMBER<siPartyIndex) )	return;

	SI32 siPartyList[ MAX_PARTY_USER_NUM ]	= {0,};
	SI08 siTotalPartyNum					= 0;


	ZeroMemory( siPartyList, sizeof(siPartyList) );

	siTotalPartyNum = GetInstanceMapPartyList( siPartyIndex, siPartyList );
	if ( siTotalPartyNum <= 0 )									return;

	for ( SI08 siIndex=0; siIndex<siTotalPartyNum; siIndex++ )
	{
		SI32 siPartyID = siPartyList[siIndex];
		if ( pclClient->pclCM->IsValidID( siPartyID ) == FALSE )
		{
			continue;
		}

		cltCharServer* pclPartyChar = (cltCharServer*)pclClient->pclCM->CR[siPartyID];
		if ( pclPartyChar == NULL )
		{
			continue;
		}

		if ( IsPartyMap(pclPartyChar->GetMapIndex()) == false )
		{
			continue;
		}

		pclPartyChar->SendNetMsg( psPacketHeader );
	}

}

// [영훈] 이맵이 파티 인던 맵인지 체크
bool cltMapManager::IsPartyMap( SI32 siMapIndex )
{
	if ( (siMapIndex < 0) || (MAX_MAP_NUMBER<siMapIndex) )
	{
		return false;
	}

	if ( IsInstanceMap( siMapIndex ) == false )
	{
		return false;
	}

	SI32 siParentMapIndex = GetParentMap( siMapIndex );

	if ( GetInstanceMapType( siParentMapIndex )  != INSTANCEMAP_TYPE_PARTY )
	{
		return false;
	}

	return true;
}

void cltMapManager::GiveItemForPartyMapClear( SI32 siPartyIndex )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	bool			bGiveItem							= false;
	SI32			siPartyList[ MAX_PARTY_USER_NUM ]	= {0,};
	SI08			siTotalPartyNum						= 0;
	SI32			siGivePartyMemberIndex				= -1;

	SI32			siGiveCharID						= 0;
	SI32			siGivePersonID						= 0;
	cltCharServer*	pclchar								= NULL;


	ZeroMemory( siPartyList, sizeof(siPartyList) );

	// 줄 캐릭터 아이디 뽑아내기
	siTotalPartyNum = GetInstanceMapPartyList( siPartyIndex, siPartyList );

	if ( (siTotalPartyNum > 0) && (siTotalPartyNum <= MAX_PARTY_USER_NUM) )
	{
		siGivePartyMemberIndex = (SI32)(rand() % siTotalPartyNum);

		if ( (siGivePartyMemberIndex >= 0) && (siGivePartyMemberIndex < siTotalPartyNum) )
		{
			bGiveItem = true;
		}
	}

	if ( bGiveItem == false )
	{
		return;
	}
	//----------------------------------------------------------------------------------------------------
	siGiveCharID = siPartyList[ siGivePartyMemberIndex ];
	if ( pclClient->pclCM->IsValidID( siGiveCharID ) == false )
	{
		return;
	}

	pclchar = (cltCharServer*)pclClient->pclCM->CR[ siGiveCharID ];
	if ( pclchar == NULL )
	{
		return;
	}

	siGivePersonID = pclchar->pclCI->GetPersonID();
	//----------------------------------------------------------------------------------------------------
	bool		bMakeResult			= false;				// 아이템 생성결과
	bool		bReferenceCheck		= false;				// 아이템 참조자 찾기 결과

	cltItem		clRewardItem;								// 보상할 아이템
	SI32		siRewardItemUnique	= ITEMUNIQUE( 18527 );	// 엥무새 망토 

	SI32		siReference			= pclClient->pclItemManager->FindItemRefFromUnique( siRewardItemUnique );

	SI16		siUsedate			= 0;
	SI16		siRareswitch		= 0;


	if ( siReference > 0 )
	{
		siUsedate			= pclClient->pclItemManager->pclItemInfo[ siReference ]->clItem.uiDateUseDay;

		bReferenceCheck		= true;
		bMakeResult			= pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique, &clRewardItem, 0, 0, &siRareswitch,0,0,0,0,0,siUsedate );
	}

	if ( (bMakeResult == true) && (bReferenceCheck == true) )
	{
		pclClient->pclLog->FilePrint( TEXT("config/PirateShiplog.log"), TEXT("[GiveItem]\tPirateShip\tPersonID:%d\tItemUnique:%d\tItemNum:%d"), siGivePersonID, clRewardItem.siUnique, clRewardItem.siItemNum );

		cltSystemRewardInfo		clInfo;			// 아이템 보상에 따른 정보
		//NDate					kExpireDate;	// 만료일자 설정을 위한 임시 변수
		//_SYSTEMTIME				sExpireTime;	// 만료일자 설정을 위한 임시 변수2
		TCHAR*					pReasonText	= GetTxtFromMgr( 8079 );	// 지급하는 이유(PC방 프리미엄)


		// 만료일 설정(지급된 다음날(+1달)로 설정)
		//kExpireDate.SetDate( pclserver->sTime.wYear, pclserver->sTime.wMonth, pclserver->sTime.wDay );
		//kExpireDate.AddMonths( 1 );

		//ZeroMemory( &sExpireTime, sizeof(_SYSTEMTIME) );
		//sExpireTime.wYear		= kExpireDate.m_uiYear;
		//sExpireTime.wMonth		= kExpireDate.m_uiMonth;
		//sExpireTime.wDay		= kExpireDate.m_uiDay;

		// 받은 날짜
		clInfo.m_sGiveTime		= pclserver->sTime;
		// 만료 날짜 - 지급받은 날부터 30일 동안 수령할 수 있다.
		//clInfo.m_sExpireTime	= sExpireTime;
		TimeAddDate(&clInfo.m_sGiveTime, 30, &clInfo.m_sExpireTime);
		// 지급할 아이템
		clInfo.m_clItem.Set( &clRewardItem );
		// 지급 이유
		if ( pReasonText )
		{
			StringCchCopy( clInfo.m_szReason, 256, pReasonText );
		}

		// 아이템을 지급 하라는 요청
		sDBRequest_GiveSystemReward clMsgReward( GIVEREWARD_CHAR, siGivePersonID, siGiveCharID, &clInfo );
		pclserver->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsgReward);


		// 유저에게 지급되었다는 메시지를 띄워줌
		pclserver->SendServerResponseMsg( 0, SRVAL_INSTANTDUNGEON_CLEAR_REWARD_ITEM, 0, 0, siGiveCharID );
		


		// 해적선을 클리어 해서 아이템을 받았다는 메시지를 모든 클라이언트에 뿌림
		NTCHARString64	kUserName( pclchar->GetName() );

		cltGameMsgResponse_InstantDungeon_Party_Clear sendMsg( kUserName, siRewardItemUnique );
		cltMsg clMsg( GAMEMSG_RESPONSE_INSTANTDUNGEON_PARTY_CLEAR, sizeof(sendMsg), (BYTE*)&sendMsg );
		pclClient->pclCM->SendAllPersonMsg( (sPacketHeader*)&clMsg );

	}

}

// [영훈] 마켓을 열 수 있는 지역인가?
bool cltMapManager::IsCanMarketOpenMap( SI32 siMapIndex )
{
	if( siMapIndex < 0 || siMapIndex >= MAX_MAP_NUMBER )return false;

	return clUnitMapInfo[siMapIndex].bCanMarket;

}

void cltMapManager::SendServrEventInstanceMapInfo( SI32 siParentMap )
{
	if ( (siParentMap < 0) || (MAX_MAP_NUMBER<siParentMap) )
	{
		return;
	}

	cltMapCommon* pclMap = GetMapPointer( siParentMap );
	if ( NULL == pclMap )
	{
		return;
	}

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return;
	}

	SI16	siServerUnique	= pclClient->siServerUnique;
	SI32	siClearStep		= pclMap->m_siClearStep;
	DWORD	dwRemainTime	= (pclMap->m_dwInstanceMapStartTime+pclMap->m_dwInstanceMapMaxTime) - pclClient->CurrentClock;
	SI32	siRemainMonster = pclMap->m_siMaxMonsterNum - pclMap->m_siKillCount;
	SI64	siScore			= 0;
	SI32	siDungeonScore	= pclMap->m_siInstanceMapScore;


	SI32 siIndex	= 0;
	SI32 siID		= 0;


	while(siID = pclClient->pclCM->GetCharOrder(siIndex))
	{
		siIndex++;

		// 유효한 아이디만 뽑아온다
		if ( pclClient->pclCM->IsValidID( siID ) == false )
		{
			continue;
		}

		if ( IsPC( siID ) == false )
		{
			continue;
		}

		cltCharServer* pclchar = (cltCharServer* )pclClient->pclCM->CR[siID];
		if ( pclchar == NULL )
		{
			continue;
		}

		
		// 인던에 없음
		if( GetParentMap(pclchar->GetMapIndex()) != siParentMap )
		{
			continue;
		}

		siScore = pclchar->siServerEvent_IndunScore;
		
		// 클라이언트에게 정보 전단
		cltGameMsgResponse_Server_Event_InstanceDungeon_RunInfo	clInfo( siServerUnique, siClearStep, dwRemainTime, siRemainMonster, siScore, siDungeonScore );
		cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEDUNGEON_RUNINFO, sizeof(clInfo), (BYTE*)&clInfo);
		pclchar->SendNetMsg( (sPacketHeader*)&clMsg );

		if ( 0 < siScore )
		{
			// DB에 개인 점수 저장
			sDBRequest_Server_Event_Server_Person_Score_Set clScore( siID, pclchar->pclCI->GetPersonID(), siScore );
			pclserver->pclGameDBProcess->SendMsg( (sPacketHeader *)&clScore );
		}
	
	}
}
