//---------------------------------
// 2003/5/17 김태곤
//---------------------------------

#include <CommonLogic.h>
#include "../../Client/Client.h"

#include "NPC.h"
#include "../../CommonLogic/CommonLogic.h"
#include "Char/CharServer/Char-Server.h"
#include "Char/CharManager/CharManager.h"
#include "../../Common/Order/Order.h"
#include "../../Common/util/util.h"

#include "../../common/PartyMgr/PartyObj.h"
#include "../../common/PartyMgr/PartyMgr.h"
#include "../../common/PartyMgr/PartyBaseInfo.h"

#include "../../Common/Char/MonsterGroupManager/MonsterGroupManager.h"

#include "../../CommonLogic/MsgType-System.h"

#include "../../CommonLogic/MsgRval-Define.h"

extern cltCommonLogic* pclClient;

cltNPCGroup::cltNPCGroup( SI32 id, SI32 maxnpcnumber, SI32 mapindex, SI32 x, SI32 y, SI32 radius, DWORD interval, bool bossGroup )
{
	SI32 i;

	ID					= id;
	MaxNPCNumber		= maxnpcnumber;
	siMapIndex			= mapindex;
	siX					= x;
	siY					= y;
	siRadius			= radius;

	bBossGroup			= bossGroup ;

	if(siRadius == 0)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("f97343"), TEXT("Fd0383"), MB_OK|MB_TOPMOST);
	}
	dwSetIntervalClock	= interval;
	dwLastCheckClock	= 0;
	dwLastNoticeClock	= 0;


	NPCKindNumber		= 0;
	CurrentNPCNumber	= 0;

	for(i = 0;i < MAX_NPC_KIND_PER_GROUP;i++)
	{
		clUnit[i].Init();
	}
}

cltNPCGroup::~cltNPCGroup()
{

}

// 그룹에 속할 NPC의 종류와 그 수를 추가한다.
BOOL cltNPCGroup::AddNPCKind(SI32 kind, SI32 num, SI32 level)
{

	if(NPCKindNumber >= MAX_NPC_KIND_PER_GROUP)
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("NPC Kind Exceed"), TEXT("Error"), MB_OK|MB_TOPMOST);
		return FALSE;
	}

	clUnit[NPCKindNumber].Set(kind, num, level);
	NPCKindNumber++;

	return TRUE;
}


bool cltNPCGroup::AddChar(SI32 id, SI32 kindindex)
{
	if(CurrentNPCNumber >= MAX_NPC_PER_GROUP)return false;

	NPCList[CurrentNPCNumber]		= id;
	NPCKindList[CurrentNPCNumber]	= kindindex;

	CurrentNPCNumber++;

	return true;
}

bool cltNPCGroup::SubChar(SI32 idindex)
{
	if(CurrentNPCNumber == 0)return false;

	NPCList[idindex]		= NPCList[CurrentNPCNumber-1];
	NPCKindList[idindex]	= NPCKindList[CurrentNPCNumber-1];

	CurrentNPCNumber--;

	return true;

}

// NPCGroup범위안에 존재하는가 ?
bool cltNPCGroup::IsInNPCGroup(SI32 mapindex, SI32 x, SI32 y)
{
	if(siMapIndex == mapindex
		&& x >= (siX - siRadius) && x <= (siX + siRadius)
		&& y >= (siY - siRadius) && y <= (siY + siRadius) )

	{
		return true;
	}

	return false;
}

// 특정 kind가 이 그룹에 존재하는가?
bool cltNPCGroup::IsInKind(SI32 kind)
{
	SI32 i;

	for(i = 0;i < MAX_NPC_KIND_PER_GROUP;i++)
	{
		if(clUnit[i].siKind == kind)return true;
	}

	return false;
}

//-------------------------------------------------------------------
//cltNPCManagerCommon
//-------------------------------------------------------------------
cltNPCManagerCommon::cltNPCManagerCommon(cltCharManager* pclcm)
{
	SI32 i;

	// 캐릭터 매니저 설정. 
	pclCM	= pclcm;

	for(i = 0;i < MAX_NPC_GROUP_NUMBER;i++)
	{
		pclNPCGroup[i]= NULL;
	}


	SetNPCGroup();
}

cltNPCManagerCommon::~cltNPCManagerCommon()
{
	SI32 i;

	for(i = 0;i < MAX_NPC_GROUP_NUMBER;i++)
	{
		if(pclNPCGroup[i])
		{
			delete pclNPCGroup[i];
			pclNPCGroup[i]= NULL;
		}
	}

}

BOOL cltNPCManagerCommon::SetNPCGroup(SI32& group, TCHAR* npcgroupname, bool clonemap, SI32 clonemapindex )
{

	SI32 i;
	TCHAR buffer[1024];
	FILE* fp;

	TCHAR filename[128];
	StringCchPrintf(filename, 128, TEXT("NPCGroup\\%s.txt"), npcgroupname);

	fp = _tfopen(filename, TEXT("rt"));
	if(fp)
	{
		// 첫 6줄은 무시한다. 
		for(i= 0;i < 6;i++)
		{
			_fgetts(buffer, 100, fp);
		}

		// 데이터 읽어오기.
		_fgetts(buffer, 100, fp);


		// 데이터 분석하기. 
		SI32 groupnum;
		SI32 maxnum;
		SI32 mapindex;
		SI32 centerx;
		SI32 centery;
		SI32 radius;
		SI32 interval;
		SI32 boss = 0 ;

		_stscanf(buffer, TEXT("%d %d %d %d %d %d %d %d"),
			&groupnum, &maxnum, &mapindex, &centerx, &centery, &radius, &interval, &boss);

		bool bossGroup = DATA_TO_BOOL(boss);

		if ( pclNPCGroup[group] == NULL )
		{
			if( clonemap  )
			{
				mapindex = clonemapindex;
			}
			pclNPCGroup[group] = new cltNPCGroup(group, maxnum, mapindex, centerx, centery, radius, interval * 1000, bossGroup );

			// 첫 3줄은 무시한다. 
			for(i= 0;i < 3;i++)
			{
				_fgetts(buffer, 100, fp);
			}

			i = 0 ;
			SI32 pKind[MAX_MONSTER_KIND_PER_GROUP] = {0,};
			SI32 pLevel[MAX_MONSTER_KIND_PER_GROUP] = {0,};
			SI32 pValue[MAX_MONSTER_KIND_PER_GROUP] = {0,};
			while(_fgetts(buffer, 100, fp) > 0)
			{
				TCHAR npccode[64];
				SI32 num;
				SI32 level;
				SI32 value = 0 ;

				_stscanf(buffer, TEXT("%s %d %d %d"), npccode, &num, &level,&value);

				if(_tcscmp(npccode, TEXT("NULL")) == 0)continue;

				SI32 kind = pclClient->pclKindInfoSet->FindKindFromCode(npccode);
				if(kind >0)
				{
					pclNPCGroup[group]->AddNPCKind(kind, num, level);
				}
				else
				{
					MsgBox(TEXT("fsdf8vjc"), TEXT("fSDfdsf:%s %s"), npcgroupname, npccode);
				}
			}

			// 그룹형 몬스터는 안 쓰니 주석처리 KKM 2007 / 08 / 22
			/*	if ( bGroup == true && pclClient->pclMonsterGroupManager )
			{
			if ( pclClient->pclMonsterGroupManager->SetInitFromFile(groupnum,mapindex,centerx,centery,radius,
			pKind,pLevel,pValue) == false )
			{
			MsgBox(TEXT("fsjyvvc"), TEXT("fdf3fdjy:%d %s"), groupnum, filename);
			}
			}*/

			// 클론 맵이 아니고 클론 맵을 가지고 있으면 NPC정보도 복사한다.
			if ( clonemap == false && pclClient->pclMapManager->HaveCloneMap(mapindex) )
			{
				SI32 cloneindex = pclClient->pclMapManager->clUnitMapInfo[mapindex].siCloneIndex;
				for ( SI32 i=0; i < CLONEMAP_NUM; ++i )
				{
					SI32 dstMapIndex = pclClient->pclMapManager->clCloneMapInfo[cloneindex].siDstMapIndex[i];
					if ( dstMapIndex > 0 )
					{
						++group;
						SetNPCGroup( group , npcgroupname, true, dstMapIndex );
					}
				}
			}
		}
		else
		{
			MsgBox(TEXT("fdsfvvc"), TEXT("fdf3fdfd:%d %s"), group, filename);
		}
	}
	else
	{
		MsgBox(TEXT("vc8cjdf"), TEXT("fej8:%s"), filename);
	}

	if(fp)
		fclose(fp);

	return TRUE;
}


// NPC 그룹을 설정한다.
BOOL cltNPCManagerCommon::SetNPCGroup()
{
	SI32 i;
	FILE* fp = NULL;
	SI32 index = 0;
	TCHAR buffer[256];

	//-----------------------------------
	// NPCGroup의 이름을 확보한다. 
	//-----------------------------------

	if( pclClient->siServiceArea == ConstServiceArea_English )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListE.txt"), TEXT("rt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListK.txt"), TEXT("rt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Taiwan )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListT.txt"), TEXT("rt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListU.txt"), TEXT("rt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_NHNChina )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListC.txt"), TEXT("rt"));
	}
	else if( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupListG.txt"), TEXT("rt"));
	}

	else
	{
		fp = _tfopen(TEXT("NPCGroup\\NPCGroupList.txt"), TEXT("rt"));
	}

	if(fp == NULL)
	{
		MsgBox(TEXT("fdsfk"), TEXT("vefd"));
		return FALSE;
	}

	for(i = 0;i < 5;i++)
	{
		_fgetts(buffer, 100, fp);
	}

	SI32 group =  1;
	while(_fgetts(buffer, 100, fp) > 0)
	{
		TCHAR list[128];
		_stscanf(buffer, TEXT("%s"), list);
		if(_tcscmp(list, TEXT("END")) == 0)break;

		// 확보된 NPCGroup을 근거로 NPCGroup을 만든다. 
		SetNPCGroup(group, list);
		group++;
	}

	fclose(fp);

	return TRUE;

	//BOOL bLoadFile = FALSE;
	//NDataLoader	dataloader;
	//bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/NPCGroup.txt") );

	//if (!bLoadFile)
	//{
	//       MsgBox(TEXT("Failed Open File"), TEXT("Data/NPCGroup.txt") );
	//	return FALSE;
	//}

	//TCHAR	szGroupName[MAX_PATH] = TEXT("");
	//SI32	siMaxNum = 0;
	//SI32	siMapIndex = 0;
	//SI32	siCenterX = 0;
	//SI32	siCenterY = 0;
	//SI32	siRadius = 0;
	//SI32	siInterval = 0;
	//SI32	siIsGroup = 0;
	//SI32	siIsBoss = 0;
	//TCHAR	szNPCCode[MAX_MONSTER_KIND_PER_GROUP][64];
	//SI32	siMinNum[MAX_MONSTER_KIND_PER_GROUP] = {0,};
	//SI32	siLevel[MAX_MONSTER_KIND_PER_GROUP] = {0,};
	//SI32	siValue[MAX_MONSTER_KIND_PER_GROUP] = {0,};

	//NDataTypeInfo pDataTypeInfo[] =
	//{
	//	NDATA_MBSTRING,	szGroupName,	MAX_PATH,
	//	NDATA_INT32,	&siMaxNum,		4,
	//	NDATA_INT32,	&siMapIndex,	4,
	//	NDATA_INT32,	&siCenterX,		4,
	//	NDATA_INT32,	&siCenterY,		4,
	//	NDATA_INT32,	&siRadius,		4,
	//	NDATA_INT32,	&siInterval,	4,
	//	NDATA_INT32,	&siIsGroup,		4,
	//	NDATA_INT32,	&siIsBoss,		4,
	//	NDATA_MBSTRING,	szNPCCode[0],	64,
	//	NDATA_INT32,	&siMinNum[0],	4,
	//	NDATA_INT32,	&siLevel[0],	4,
	//	NDATA_INT32,	&siValue[0],	4,
	//	NDATA_MBSTRING,	szNPCCode[1],	64,
	//	NDATA_INT32,	&siMinNum[1],	4,
	//	NDATA_INT32,	&siLevel[1],	4,
	//	NDATA_INT32,	&siValue[1],	4,
	//	NDATA_MBSTRING,	szNPCCode[2],	64,
	//	NDATA_INT32,	&siMinNum[2],	4,
	//	NDATA_INT32,	&siLevel[2],	4,
	//	NDATA_INT32,	&siValue[2],	4,
	//	NDATA_MBSTRING,	szNPCCode[3],	64,
	//	NDATA_INT32,	&siMinNum[3],	4,
	//	NDATA_INT32,	&siLevel[3],	4,
	//	NDATA_INT32,	&siValue[3],	4,
	//	NDATA_MBSTRING,	szNPCCode[4],	64,
	//	NDATA_INT32,	&siMinNum[4],	4,
	//	NDATA_INT32,	&siLevel[4],	4,
	//	NDATA_INT32,	&siValue[4],	4,
	//	0, 0, 0
	//};

	//dataloader.RegDataType(pDataTypeInfo );

	//bool	bGroup;
	//bool	bBoss;
	//SI32	id = 1;
	//SI32	group = 1;

	//while( !dataloader.IsEndOfData() ) 
	//{
	//	if (dataloader.ReadData())	
	//	{

	//		bGroup = DATA_TO_BOOL(siIsGroup);
	//		bBoss = DATA_TO_BOOL(siIsBoss);

	//		if ( !szGroupName[0] )
	//			continue;

	//		pclNPCGroup[id] = new cltNPCGroup( id, siMaxNum, siMapIndex, siCenterX, siCenterY, siRadius, siInterval*1000 );

	//		SI32 pKind[MAX_MONSTER_KIND_PER_GROUP] = {0,};
	//		SI32 pLevel[MAX_MONSTER_KIND_PER_GROUP] = {0,};
	//		SI32 pValue[MAX_MONSTER_KIND_PER_GROUP] = {0,};

	//		SI32 k = 0;

	//		for ( SI16 i = 0; i< MAX_MONSTER_KIND_PER_GROUP; i++ )
	//		{
	//			if ( ! szNPCCode[i][0] )
	//			{
	//				continue;
	//			}

	//			SI32 kind = pclClient->pclKindInfoSet->FindKindFromCode( szNPCCode[i] );

	//			if ( kind > 0 )
	//			{
	//				if ( bGroup == true )
	//				{
	//					pKind[k] = kind ;
	//					pLevel[k] = siLevel[i] ;
	//					pValue[k] = siValue[i] ;
	//					siMinNum[i] = 0 ;
	//					++k;
	//				}

	//				pclNPCGroup[id]->AddNPCKind( kind, siMinNum[i], siLevel[i] );
	//			}
	//			else
	//			{
	//				MsgBox(TEXT("NPCGroup Set Error"), TEXT("Fault CharacterKind:%s %s"), szGroupName, szNPCCode[i]);
	//			}
	//		}

	//		if ( bGroup == true && pclClient->pclMonsterGroupManager )
	//		{
	//			if ( pclClient->pclMonsterGroupManager->SetInitFromFile(group, siMapIndex, siCenterX, siCenterY, siRadius, pKind, pLevel, pValue ) == true )
	//			{
	//				++group;
	//			}
	//			else
	//			{
	//				MsgBox(TEXT("fsjyvvc"), TEXT("fdf3fdjy:%s"), szGroupName);
	//			}
	//		}
	//		++id;
	//	}
	//}
	//return TRUE;
}

// NPCGroup범위안에 존재하는가 ?
bool cltNPCManagerCommon::IsInNPCGroup(SI32 npcgroup, SI32 mapindex, SI32 x, SI32 y)
{
	if(npcgroup <= 0 || npcgroup >= MAX_NPC_GROUP_NUMBER)return false;
	if(pclNPCGroup[npcgroup] == NULL)return false;

	return pclNPCGroup[npcgroup]->IsInNPCGroup(mapindex, x, y);
}

SI32 cltNPCManagerCommon::GetKindLevel(SI32 kind)
{
	SI32 siLevel = 0;
	SI32 i, j;

	for(i = 0;i < MAX_NPC_GROUP_NUMBER; i++)
	{
		if(pclNPCGroup[i] == NULL)continue;

		for(j = 0;j < MAX_NPC_KIND_PER_GROUP;j++)
		{
			if(pclNPCGroup[i]->clUnit[j].siKind == kind)
			{
				siLevel = pclNPCGroup[i]->clUnit[j].siKindLevel;
				return siLevel;
			}
		}
	}

	return siLevel;
}

SI32 cltNPCManagerCommon::GetKindMaxLevel(SI32 kind)
{
	SI32 siMaxLevel = 0;
	SI32 i, j;

	for(i = 0;i < MAX_NPC_GROUP_NUMBER; i++)
	{
		if(pclNPCGroup[i] == NULL)continue;

		for(j = 0;j < MAX_NPC_KIND_PER_GROUP;j++)
		{
			if(pclNPCGroup[i]->clUnit[j].siKind == kind)
			{
				if(siMaxLevel < pclNPCGroup[i]->clUnit[j].siKindLevel)
					siMaxLevel = pclNPCGroup[i]->clUnit[j].siKindLevel;
			}
		}
	}

	return siMaxLevel;
}

//---------------------------------------------------------
// cltNPCManagerClient
//----------------------------------------------------------
cltNPCManagerClient::cltNPCManagerClient(cltCharManager* pclcm) : cltNPCManagerCommon(pclcm)
{


}

cltNPCManagerClient::~cltNPCManagerClient()
{

}

// npc 그룹에서 특정 kind의 위치 정보 text를 얻어온다.
bool cltNPCManagerClient::GetKindPos(SI32 kind, TCHAR* ptext, SI16 txtSize)
{
	SI32 i;
	TCHAR buffer[256];

	StringCchCopy(ptext, txtSize, TEXT(""));

	bool returnval = false;


	for(i = 0;i < MAX_NPC_GROUP_NUMBER;i++)
	{
		if(pclNPCGroup[i] == NULL)continue;

		// kind가 속한 그룹을 찾는다. 
		if(pclNPCGroup[i]->IsInKind(kind) == true)
		{
			SI32 mapindex = pclNPCGroup[i]->siMapIndex;

			TCHAR* pmapname = pclClient->pclMapManager->GetMapName(mapindex);

			StringCchPrintf(buffer, 256, TEXT("%s(%d, %d)\r\n"), pmapname, pclNPCGroup[i]->siX, pclNPCGroup[i]->siY);
			StringCchCat(ptext, txtSize, buffer);

			returnval = true;

		}
	}

	return returnval;
}


// npc 그룹에서 특정 kind의 위치 정보 text를 얻어온다.
bool cltNPCManagerClient::GetKindPos(SI32 kind, cltRegenPos *regenpos, SI32 *siCount)
{
	cltClient* pclclient = (cltClient*)pclClient;

	SI32 i;
	TCHAR buffer[256];

	bool returnval = false;
	SI32 siAddCount = 0;


	for(i = 0;i < MAX_NPC_GROUP_NUMBER;i++)
	{
		if(pclNPCGroup[i] == NULL)continue;

		// kind가 속한 그룹을 찾는다. 
		if(pclNPCGroup[i]->IsInKind(kind) == true)
		{
			SI32 mapindex = pclNPCGroup[i]->siMapIndex;
			TCHAR* pmapname = pclClient->pclMapManager->GetMapName(mapindex);

			StringCchPrintf(buffer, 256, TEXT("%s"),			pmapname);
			StringCchCopy(regenpos[siAddCount].szMapName, 50, buffer);

			StringCchPrintf(buffer, 256, TEXT("(%3d, %3d)"),	pclNPCGroup[i]->siX, pclNPCGroup[i]->siY);
			StringCchCopy(regenpos[siAddCount].szMapPos, 50, buffer);

			pclclient->GetNearMapInfo(mapindex,pclNPCGroup[i]->siX,pclNPCGroup[i]->siY,regenpos[siAddCount].szNearMapInfo, 50);

			/*			SI32 siVillageUnique;
			TCHAR strdir[30] = TEXT("") ;

			// 야외지역 
			if(mapindex == 0)
			{
			siVillageUnique = pclClient->pclVillageManager->FindNearVillage(pclNPCGroup[i]->siX, pclNPCGroup[i]->siY);
			SI32 x = pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->PosX;
			SI32 y = pclClient->pclVillageManager->pclVillageInfo[siVillageUnique]->PosY;

			GetDirectionStr(x, y, pclNPCGroup[i]->siX, pclNPCGroup[i]->siY, strdir);
			pmapname = pclClient->pclMapManager->GetMapName(siVillageUnique);
			sprintf(buffer, TEXT("%s %s"),		pmapname, strdir);
			_tcscpy(regenpos[siAddCount].szNearMapInfo, buffer);
			}
			else
			{
			_tcscpy(strdir, TEXT(""));
			if(_tcsstr(pmapname,      "수어장대"))		{	_tcscpy(strdir, TEXT("남한산성 상부"));	}
			else if(_tcsstr(pmapname, TEXT("지하감옥")))		{	_tcscpy(strdir, TEXT("남한산성 하부"));	}
			else if(_tcsstr(pmapname, TEXT("마늘소굴")))		{	_tcscpy(strdir, TEXT("웅녀동굴 내부"));	}
			else if(_tcsstr(pmapname, TEXT("화룡성")))			{	_tcscpy(strdir, TEXT("나무소굴 내부"));	}
			else if(_tcsstr(pmapname, TEXT("깨비집")))			{	_tcscpy(strdir, TEXT("깨비마을 내부"));	}
			else if(_tcsstr(pmapname, TEXT("초보자사낭터")))	{	_tcscpy(strdir, TEXT("한양 남서쪽 "));		}

			// 지도 바꿀때 꼭 확인할껏 
			else if(_tcsstr(pmapname, TEXT("남한산성")))		{	_tcscpy(strdir, TEXT("수원 동쪽"));		}
			else if(_tcsstr(pmapname, TEXT("웅녀동굴")))		{	_tcscpy(strdir, TEXT("홍천 남쪽"));		}
			else if(_tcsstr(pmapname, TEXT("나무소굴")))		{	_tcscpy(strdir, TEXT("포천 동쪽"));		}
			else if(_tcsstr(pmapname, TEXT("작은풀숲")))		{	_tcscpy(strdir, TEXT("대구 남쪽"));		}
			else if(_tcsstr(pmapname, TEXT("깨비마을")))		{	_tcscpy(strdir, TEXT("함양 북서쪽"));		}
			else if(_tcsstr(pmapname, TEXT("미황사")))			{	_tcscpy(strdir, TEXT("목포 남서쪽"));		}

			else if(_tcsstr(pmapname, TEXT("경상우수영")))		{	_tcscpy(strdir, TEXT("통영 동쪽"));		}
			else if(_tcsstr(pmapname, TEXT("귀곡산장")))		{	_tcscpy(strdir, TEXT("평안도순천 북쪽"));		}
			else if(_tcsstr(pmapname, TEXT("금하굴")))			{	_tcscpy(strdir, TEXT("문경 남서쪽"));		}
			else if(_tcsstr(pmapname, TEXT("용궁")))			{	_tcscpy(strdir, TEXT("해주 북서쪽"));		}
			else if(_tcsstr(pmapname, TEXT("산타작업장")))		{	_tcscpy(strdir, TEXT("중강진 남쪽"));		}

			else if(_tcsstr(pmapname, TEXT("한과공장")))		{	_tcscpy(strdir, TEXT("덕천 동쪽"));		}
			else if(_tcsstr(pmapname, TEXT("하회마을")))		{	_tcscpy(strdir, TEXT("안동 서쪽"));		}
			else if(_tcsstr(pmapname, TEXT("얼음성")))			{	_tcscpy(strdir, TEXT("중강진 남쪽"));		}
			else if(_tcsstr(pmapname, TEXT("백두산")))			{	_tcscpy(strdir, TEXT("혜산 북동쪽,대흥단 북서쪽"));		}

			if(_tcslen(strdir))	sprintf(buffer, TEXT("%s"),		strdir);
			else				sprintf(buffer, TEXT("%s"),		pmapname);
			_tcscpy(regenpos[siAddCount].szNearMapInfo, buffer);
			}*/

			returnval = true;
			siAddCount++;

		}
	}

	*siCount = siAddCount;
	return returnval;
}

/*bool cltNPCManagerClient::GetDirectionStr(SI32 sx, SI32 sy, SI32 dx, SI32 dy, TCHAR *szText)
{
SI32  rsx, rsy, rdx, rdy;
rsx = sx*2-sy*2;	rsy = sy*1+sx*1;
rdx = dx*2-dy*2;	rdy = dy*1+dx*1;

switch(DecideDirection8(rsx, rsy, rdx, rdy))
{
case SOUTH|EAST:	_tcscpy(szText, TEXT("남동쪽"));	break;
case SOUTH:			_tcscpy(szText, TEXT("남쪽"));		break;
case SOUTH|WEST:	_tcscpy(szText, TEXT("남서쪽"));	break;
case WEST:			_tcscpy(szText, TEXT("서쪽"));		break;
case WEST|NORTH:	_tcscpy(szText, TEXT("북서쪽"));	break;
case NORTH:			_tcscpy(szText, TEXT("북쪽"));		break;
case NORTH|EAST:	_tcscpy(szText, TEXT("북동쪽"));	break;
case EAST:			_tcscpy(szText, TEXT("동쪽"));		break;
default:			_tcscpy(szText, TEXT("근처"));		break;
}

return true;
}*/

// npc 그룹에서 특정 맵(index)에 있는 몬스터들의 kind를 가져온다.
bool cltNPCManagerClient::GetKindMapInx(SI32 mapindex, SI32 siKind[], SI32 siKindLevel[], SI32 siMaxSize)
{
	SI32 kindnumber = 0 ;

	for(SI32 i = 0 ; i < MAX_NPC_GROUP_NUMBER ; i++ )
	{
		if(pclNPCGroup[i] == NULL)continue;

		if ( pclNPCGroup[i]->siMapIndex == mapindex )
		{
			for ( SI32 j = 0 ; j < MAX_NPC_KIND_PER_GROUP ; j ++ )
			{
				if ( pclNPCGroup[i]->clUnit[j].siKind > 0 )
				{
					if ( FindKindData(siKind, siMaxSize, pclNPCGroup[i]->clUnit[j].siKind ) )	continue ;
					//if ( kindnumber >= MAX_NPC_KIND_PER_GROUP ) continue ;
					if( kindnumber >=  siMaxSize)											continue;
					siKind[kindnumber] = pclNPCGroup[i]->clUnit[j].siKind ;
					siKindLevel[kindnumber] = pclNPCGroup[i]->clUnit[j].siKindLevel ;
					kindnumber++ ;
					//if ( ConstServiceArea_China == pclClient->siServiceArea )
					//{
					//	siKindLevel[kindnumber] = pclClient->pclKindInfoSet->pclKI[pclNPCGroup[i]->clUnit[j].siKind]->clBA.GetBattleLevel();
					//}
					//else
					//{

					//}
				}
			}
		}
	}
	return true;
}

bool cltNPCManagerClient::FindKindData(SI32 siKind[], SI32 siCount, SI32 npckind)
{
	if ( npckind <= 0 ) return true ;

	//for ( SI32 i = 0 ; i < MAX_NPC_KIND_PER_GROUP ; i ++ )
	for ( SI32 i = 0 ; i < siCount ; i ++ )
	{
		if ( siKind[i] == npckind )
			return true ;
	}
	return false ;
}

//---------------------------------------------------------
// cltNPCManagerServer
//----------------------------------------------------------
cltNPCManagerServer::cltNPCManagerServer(cltCharManager* pclcm) : cltNPCManagerCommon(pclcm)
{


}

cltNPCManagerServer::~cltNPCManagerServer()
{
}

bool cltNPCManagerServer::FindKindData(SI32 siKind[], SI32 siCount, SI32 npckind)
{
	if ( npckind <= 0 ) return true ;

	//for ( SI32 i = 0 ; i < MAX_NPC_KIND_PER_GROUP ; i ++ )
	for ( SI32 i = 0 ; i < siCount ; i ++ )
	{
		if ( siKind[i] == npckind )
			return true ;
	}
	return false ;
}

bool cltNPCManagerServer::GetKindLevel(SI32 sLevel, SI32 eLevel, SI32 siKind[], SI32 maxsize)
{
	SI32 kindnumber = 0 ;

	for(SI32 i = 0 ; i < MAX_NPC_GROUP_NUMBER ; i++ )
	{
		if(pclNPCGroup[i] == NULL)	continue;

		for ( SI32 j = 0 ; j < MAX_NPC_KIND_PER_GROUP ; j ++ )
		{
			if ( sLevel <= pclNPCGroup[i]->clUnit[j].siKindLevel && eLevel >= pclNPCGroup[i]->clUnit[j].siKindLevel )
			{
				if ( FindKindData(siKind, maxsize, pclNPCGroup[i]->clUnit[j].siKind ) )		continue ;
				if ( kindnumber >= maxsize )												continue ;
				siKind[kindnumber] = pclNPCGroup[i]->clUnit[j].siKind ;

				if (pclNPCGroup[i]->clUnit[j].siKindLevel == 1)
				{
					int a= 0;
				}
				kindnumber++ ;
			}
		}
	}
	return true;
}

// NPC 그룹 정보에 따라 캐릭터를 추가한다.
BOOL cltNPCManagerServer::SetChar()
{
	SI32 i, j, k, z;
	SI32 id;

	if(pclClient->GetFrame() % 20)return FALSE;


	for(i = 0; i < MAX_NPC_GROUP_NUMBER;i++)
	{
		if(pclNPCGroup[i] == NULL)
			continue;

		// 시간 간격으로 나오는 그룹인 경우, 
		SI32 maxnumber		= pclNPCGroup[i]->MaxNPCNumber;
		SI32 npckindnumber	= pclNPCGroup[i]->NPCKindNumber;
		SI32 mapindex		= pclNPCGroup[i]->siMapIndex;

		if ( pclClient->pclMapManager->IsInstanceMap(mapindex) == false )
		{
			if(pclNPCGroup[i]->dwSetIntervalClock && (DWORD)TABS(pclClient->CurrentClock - pclNPCGroup[i]->dwLastCheckClock) < pclNPCGroup[i]->dwSetIntervalClock)
			{
				if( pclNPCGroup[i]->bBossGroup )
				{
					DWORD leftsecond = pclNPCGroup[i]->dwSetIntervalClock - TABS(pclClient->CurrentClock - pclNPCGroup[i]->dwLastCheckClock);

					// 해당 지역에 있는 사용자들에게 출현까지 남은 시간을 알려준다. 
					if(TABS(pclClient->CurrentClock - pclNPCGroup[i]->dwLastNoticeClock) >= 60000)
					{
						pclNPCGroup[i]->dwLastNoticeClock = pclClient->CurrentClock;

						cltGameMsgResponse_BossAppear clinfo(pclNPCGroup[i]->clUnit[0].siKind, leftsecond / 1000);
						cltMsg clMsg(GAMEMSG_RESPONSE_BOSSAPPEAR, sizeof(clinfo), (BYTE*)&clinfo);
						pclClient->pclCM->SendAllPersonInMapMsg((sPacketHeader*)&clMsg, pclNPCGroup[i]->siMapIndex);
					}
				}

				continue;
			}

			pclNPCGroup[i]->dwLastCheckClock = pclClient->CurrentClock;

			//---------------------------------
			// NPC그룹의 현재 개수를 초기화한다.
			//---------------------------------
			for(j = 0;j < npckindnumber;j++)
			{
				pclNPCGroup[i]->clUnit[j].siKindNum = 0;
			}

			//--------------------------------
			// NPC그룹의 정보를 재 설정한다. 
			//--------------------------------

			// NPC중 무효화된 것들을 제거한다. 
			for(j = 0;j < pclNPCGroup[i]->CurrentNPCNumber;j++)
			{
				id = pclNPCGroup[i]->NPCList[j];
				// 캐릭터가 죽었거나 같은 NPC그룹이 아닌경우에. 
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
				if(pclClient->pclCM->IsAlive(id) == FALSE || pclchar->GetNPCGroup() != i)
				{
					pclNPCGroup[i]->SubChar(j);
				}
				else
				{
					//-------------------------------------
					// NPC그룹에 추가한다.
					//-------------------------------------
					for(k =0;k < npckindnumber;k++)
					{
						if(pclNPCGroup[i]->clUnit[k].siKind == pclchar->GetKind())
						{
							pclNPCGroup[i]->clUnit[k].siKindNum++;
						}
					}
				}

			}

			SI32 currentnumber	= pclNPCGroup[i]->CurrentNPCNumber;

			// 현재의 NPC수가 최대 수보다 많거나 같으면 NPC를 추가하지 않는다.
			if(currentnumber >= maxnumber)continue;

			// 한번에 생성될 몬스터들
			if( pclNPCGroup[i]->dwSetIntervalClock > 0 && false == pclNPCGroup[i]->bBossGroup )
			{
				for(j = 0; j < npckindnumber;j++)
				{
					SI32 kind		= pclNPCGroup[i]->clUnit[j].siKind;
					SI32 kindmaxnum	= pclNPCGroup[i]->clUnit[j].siKindMaxNum;
					SI32 kindnumber	= pclNPCGroup[i]->clUnit[j].siKindNum;
					SI32 level		= pclNPCGroup[i]->clUnit[j].siKindLevel;

					// 캐릭터 숫자가 부족하지 않으면 문제되지 않는다. 
					for( z = kindnumber; z < kindmaxnum; ++z )
					{
						//---------------------------
						// 캐릭터를 만든다. 
						//---------------------------
						SI32 x = pclNPCGroup[i]->siX - pclNPCGroup[i]->siRadius/2 + (rand() % pclNPCGroup[i]->siRadius);
						SI32 y = pclNPCGroup[i]->siY - pclNPCGroup[i]->siRadius/2 + (rand() % pclNPCGroup[i]->siRadius);

						SI32 dx, dy;

					#ifdef _DEBUG
						if( NULL == pclClient->pclMapManager->pclMapArray[mapindex] )
						{
							TCHAR ErrorBuffer[128] = "";
							StringCchPrintf( ErrorBuffer, sizeof(ErrorBuffer), "Npc Group [ %d ]맵 정보가 없어!!", mapindex );
							MessageBox( NULL, ErrorBuffer, "없어!", 0 );
							continue;
						}
					#else
						if( NULL == pclClient->pclMapManager->pclMapArray[mapindex] ) continue;;
					#endif
						

						if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, x, y, 5, &dx, &dy, false) == false)continue;

						// 캐릭터를 생성한다. 
						cltOrderDataInfo clOrder;
						clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);

						cltSimpleRank clrank;
						clrank.Init();

						cltIdentity			clIdentity;
						cltInnerStatusInfo	clInnerStatus;
						clInnerStatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);	// 모든 사용자에게 적대적이다. 

						SI32 charunique;
						SI32 mode = 0;
						charunique = cltCharServer::FindEmptyCharUnique(mode);

						SI32 childcharuique = 0;
						SI32 cursummonindex	= 0;

						cltBufInfo clBufInfo;
						clBufInfo.Init();
						cltMakeCharInfo clMakeCharInfo( kind, 
														charunique, 
														level, 
														0, 
														dx, 
														dy, 
														mapindex, 
														childcharuique, 
														cursummonindex, 
														0, 
														0, 
														0, 
														0, 
														0, 
														0,
														0, 
														0,
														1,
														NULL,
														0, 
														0,
														0,
														0,
														0, 
														0,
														0,
														0,
														&clrank,
														0,
														0,
														&clOrder,
														&clIdentity,
														&clInnerStatus,
														0,
														0,
														0,
														false,
														0,
														NULL,
														NULL,
														false, 
														0, 
														false, 
														false, 
														false, 
														false, 
														0, 
														0,
														NULL, 
														false
														,NULL
														,0
														,0
														,0
														,0
														,0
														,0
														,0
														,0
														,0
														,0
														,false
														,&clBufInfo );

						id = pclCM->pclIDManager->GetID(mode);


						id = pclClient->SetChar(id, &clMakeCharInfo);
						if(id)
						{
							if(pclNPCGroup[i]->AddChar(id, j) == TRUE)
							{
								pclCM->CR[id]->SetNPCGroup(i);
							}

							//-------------------------------
							// 이 캐릭터에게 아이템을 준다. 
							//-------------------------------
							// KindInfo의 정보를 토대로 아이템을 만든다. 
							cltItem clItem;

							if(pclClient->pclItemManager->MakeRandItem(level, 0, &pclClient->pclKindInfoSet->pclKI[kind]->clItemPbtSet, &clItem) == true)
							{
								// 만들어진 아이템을 캐릭터에게 준다.
								pclCM->CR[id]->AddItemToInventory(&clItem);
							}
						}
					}
				}
			}
			else
			{
				for(j = 0; j < npckindnumber;j++)
				{
					SI32 kind		= pclNPCGroup[i]->clUnit[j].siKind;
					SI32 kindmaxnum	= pclNPCGroup[i]->clUnit[j].siKindMaxNum;
					SI32 kindnumber	= pclNPCGroup[i]->clUnit[j].siKindNum;
					SI32 level		= pclNPCGroup[i]->clUnit[j].siKindLevel;

					// 캐릭터 숫자가 부족하지 않으면 문제되지 않는다. 
					if(kindnumber >= kindmaxnum)continue;

					//---------------------------
					// 캐릭터를 만든다. 
					//---------------------------

					// 캐릭터를 생성할 적절한 위치를 찾는다. 
					SI32 x = pclNPCGroup[i]->siX - pclNPCGroup[i]->siRadius/2 + (rand() % pclNPCGroup[i]->siRadius);
					SI32 y = pclNPCGroup[i]->siY - pclNPCGroup[i]->siRadius/2 + (rand() % pclNPCGroup[i]->siRadius);

					SI32 dx, dy;
					if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, x, y, 5, &dx, &dy, false) == false)continue;


					// 캐릭터를 생성한다. 
					cltOrderDataInfo clOrder;
					clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);

					cltSimpleRank clrank;
					clrank.Init();

					cltIdentity			clIdentity;
					cltInnerStatusInfo	clInnerStatus;
					clInnerStatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);	// 모든 사용자에게 적대적이다. 

					SI32 charunique;
					SI32 mode = 0;
					charunique = cltCharServer::FindEmptyCharUnique(mode);

					SI32 childcharuique = 0;
					SI32 cursummonindex	= 0;

					cltBufInfo clBufInfo;
					clBufInfo.Init();
					cltMakeCharInfo clMakeCharInfo(kind, charunique, level, 0, dx, dy, mapindex, 
													childcharuique, 
													cursummonindex, 
													0, 0, 0, 0, 0, 0, 0, 0, 
													1, NULL, 0, 0, 0, 0, 0, 
													0, 0, 0, &clrank, 0, 0,
													&clOrder, &clIdentity, &clInnerStatus, 
													0, 0, 0, false, 0, NULL, NULL, 
													false, 0, false, false, false,	
													false, 0, 0, NULL, false,NULL
													,0,0,0,0,0,0,0,0,0,0,false, &clBufInfo
													);

					id = pclCM->pclIDManager->GetID(mode);


					id = pclClient->SetChar(id, &clMakeCharInfo);
					if(id)
					{
						if(pclNPCGroup[i]->AddChar(id, j) == TRUE)
						{
							pclCM->CR[id]->SetNPCGroup(i);
						}

						//-------------------------------
						// 이 캐릭터에게 아이템을 준다. 
						//-------------------------------
						// KindInfo의 정보를 토대로 아이템을 만든다. 
						cltItem clItem;

						if(pclClient->pclItemManager->MakeRandItem(level, 0, &pclClient->pclKindInfoSet->pclKI[kind]->clItemPbtSet, &clItem) == true)
						{
							// 만들어진 아이템을 캐릭터에게 준다.
							pclCM->CR[id]->AddItemToInventory(&clItem);
						}
					}
				}
			}
		}
		else
		{
			SetInstanceChar(mapindex) ;
		}
	}

	return TRUE;
}

//[추가 : 황진성 2007. 10. 31 도마돈 생성시 이름 생성된 지도내 몬스터 이름을 찾기위해 추가.]
// npc 그룹에서 특정 맵(index)에 있는 몬스터들의 kind를 가져온다.
bool cltNPCManagerServer::GetKindMapInx(SI32 mapindex, SI32 siKind[], SI32 siKindLevel[], SI32 siMaxSize)
{
	SI32 kindnumber = 0 ;

	for(SI32 i = 0 ; i < MAX_NPC_GROUP_NUMBER ; i++ )
	{
		if(pclNPCGroup[i] == NULL)continue;

		if ( pclNPCGroup[i]->siMapIndex == mapindex )
		{
			for ( SI32 j = 0 ; j < MAX_NPC_KIND_PER_GROUP ; j ++ )
			{
				if ( pclNPCGroup[i]->clUnit[j].siKind > 0 )
				{
					if ( FindKindData(siKind, siMaxSize, pclNPCGroup[i]->clUnit[j].siKind ) )	continue ;
					//if ( kindnumber >= MAX_NPC_KIND_PER_GROUP ) continue ;
					if( kindnumber >=  siMaxSize)											continue;
					siKind[kindnumber] = pclNPCGroup[i]->clUnit[j].siKind ;
					siKindLevel[kindnumber] = pclNPCGroup[i]->clUnit[j].siKindLevel ;
					kindnumber++ ;
					//if ( ConstServiceArea_China == pclClient->siServiceArea )
					//{
					//	siKindLevel[kindnumber] = pclClient->pclKindInfoSet->pclKI[pclNPCGroup[i]->clUnit[j].siKind]->clBA.GetBattleLevel();
					//}
					//else
					//{

					//}
				}
			}
		}
	}
	return true;
}
