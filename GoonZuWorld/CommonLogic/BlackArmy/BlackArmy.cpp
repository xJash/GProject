//---------------------------------
// 2004/2/18 김태곤
//---------------------------------

#include "BlackArmy.h"

#include <CommonLogic.h>
#include "..\..\Server\Server.h"
#include "Music\music.h"

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharServer\Char-Server.h"
#include "Char\CharManager\CharManager.h"
#include "MsgType-System.h"
#include "MsgType-Person.h"
#include "MsgRval-Define.h"

#include "..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "NDataLoader.h"

#include "WarRank\WarRank.h"
#include "PartyMgr\PartyObj.h"
#include "PartyMgr\PartyMgr.h"

#include "Minister\MinisterMgr.h"
#include "Minister\Minister-Byungzo.h"

extern cltCommonLogic* pclClient;

//---------------------------------------
// cltBackArmyApplyPerson
//---------------------------------------
cltBlackArmyApplyPerson::cltBlackArmyApplyPerson()
{
	Init();
}

cltBlackArmyApplyPerson::cltBlackArmyApplyPerson(cltSimplePerson applyperson)
{
	Init();

	clApplyPerson.Set(&applyperson);
//	siPartyIndex = partyindex;
//	bPartyLearder = partyleader;
}

cltBlackArmyApplyPerson::~cltBlackArmyApplyPerson()
{
}

void cltBlackArmyApplyPerson::Init()
{
	clApplyPerson.Init();
	siWarMapUnique = 0;
//	bPartyLearder = false;
//	siPartyIndex = 0;
	bWarMapAlloc = false;
}


void cltBlackArmyApplyPerson::Set(cltBlackArmyApplyPerson *pinfo)
{
	clApplyPerson.Set(&pinfo->clApplyPerson);
	siWarMapUnique = pinfo->siWarMapUnique;
//	bPartyLearder = pinfo->bPartyLearder;
//	siPartyIndex = pinfo->siPartyIndex;
	bWarMapAlloc = pinfo->bWarMapAlloc;
}

//---------------------------------------
// cltBackArmyApplyList
//---------------------------------------
cltBlackArmyApplyList::cltBlackArmyApplyList()
{
	siPersonIndex = 0;
	InitList();
}

cltBlackArmyApplyList::~cltBlackArmyApplyList()
{
}


SI32 cltBlackArmyApplyList::AddApplyPerson(cltBlackArmyApplyPerson *pPerson)
{
	SI32 retPersonIndex = -1;

	if (siPersonIndex >= 0 && siPersonIndex < MAX_BLACKARMY_APPLY_CNT)
	{
		clApplyPersonList[siPersonIndex].Set(pPerson);

		retPersonIndex = siPersonIndex;
		siPersonIndex++;

	}

	return retPersonIndex;
}

void cltBlackArmyApplyList::InitList()
{
	for (int i = 0; i < MAX_BLACKARMY_APPLY_CNT; i++)
	{
		clApplyPersonList[i].Init();
	}

	siPersonIndex = 0;
}

SI32 cltBlackArmyApplyList::FindApplyFromPersonid(SI32 personid)
{
	SI32 retApplyIndex = -1;

	for (int i = 0; i < siPersonIndex; i++)
	{
		if (clApplyPersonList[i].clApplyPerson.GetPersonID() == personid)
			retApplyIndex = i;
	}

	return	retApplyIndex;

}


//---------------------------------------
// cltBackArmyWarMap
//---------------------------------------
cltBlackArmyWarMap::cltBlackArmyWarMap()
{
	Init();
}

cltBlackArmyWarMap::~cltBlackArmyWarMap()
{
}

void cltBlackArmyWarMap::Init()
{
	siPersonIndex = 0;
	siMapIndex = 0;

	siGateUnique = 0;

	siMapUnitNum = 0;
	siMapCurUnitNum = 0;
	siMapMadeNum = 0;

	//siWarStep = 0;

	siWarcmd = 0;

	bWarDoing = false;

	for (SI32 i = 0; i < MAX_BLACKARMY_UNITKIND; i++)
	{
		clBlackArmyUnit[i].Init();
	}

	InitList();
}


SI32 cltBlackArmyWarMap::AddWarPerson(cltBlackArmyApplyPerson *pPerson)
{
	SI32 retPersonIndex = -1;

	if (siPersonIndex >= 0 && siPersonIndex < MAX_BLACKARMY_MAP_PERSON_CNT)
	{
		clWarPersonList[siPersonIndex].Set(pPerson);

		retPersonIndex = siPersonIndex;
		siPersonIndex++;

	}

	return retPersonIndex;

}

void cltBlackArmyWarMap::InitList()
{
	for (int i = 0; i < MAX_BLACKARMY_MAP_PERSON_CNT; i++)
	{
		clWarPersonList[i].Init();
	}

	siPersonIndex = 0;
}

//---------------------------------------
// cltBlackArmyUnit
//---------------------------------------
cltBlackArmyUnit::cltBlackArmyUnit()
{
	Init();
}

cltBlackArmyUnit::cltBlackArmyUnit(SI32 kind, SI32 num, SI32 curnum, SI32 madenum, SI32 basic, SI32 rand)
{
	siKind		= kind;
	siNum		= num;
	siCurNum	= curnum;
	siMadeNum	= madenum;
	siBasicLevel= basic;
	siRandLevel	= rand;
}

void cltBlackArmyUnit::Init()
{
	siKind		= 0;
	siNum		= 0;
	siCurNum	= 0;
	siMadeNum	= 0;
	siBasicLevel= 0;
	siRandLevel	= 0;
}

void cltBlackArmyUnit::Set(cltBlackArmyUnit *blackarmyunit)
{
	siKind		= blackarmyunit->siKind;
	siNum		= blackarmyunit->siNum;
	siCurNum	= blackarmyunit->siCurNum;
	siMadeNum	= blackarmyunit->siMadeNum;
	siBasicLevel= blackarmyunit->siBasicLevel;
	siRandLevel	= blackarmyunit->siRandLevel;
}


//---------------------------------------
// cltBlackArmyManager
//---------------------------------------
cltBlackArmyManager::cltBlackArmyManager()
{
	bWarSwitch	= false;
	bApplySwitch = false;
	bAutoBlackWarSwitch = false;
	
	//siTotalUnitNum= 0;		// 전체 병사수. 
	//siTotalCurUnitNum = 0;		// 현재 병사수. 

	siSettingMonNum = 0;

	siUnitKind = 0;				// 유니트는 몇 종이 있는가?
	uiLeftTime = 0;				// 남은 시간. (ms) 
	dwWarStartClock = 0;

	bDrawSwitch = false;
	siDrawCmdFont = 0;
	dwDrawStartClock = 0;
}


cltBlackArmyManager::~cltBlackArmyManager()
{
}

void cltBlackArmyManager::Init()
{
	LoadWarInfoFile();
}

void cltBlackArmyManager::LoadWarInfoFile()
{
	// 병력 데이터 초기화
	siUnitKind	= 0;

	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	bLoadFile = dataloader.LoadDataFromFile( TEXT("ServerInfo\\WarInfo.txt") );
	if (!bLoadFile)
	{
		MsgBox(TEXT("Error"), TEXT("Don't LoadFile: WarInfo.txt"));
		return;
	}

	SI32 num		= 0;
	SI32 basic		= 0;
	SI32 randlevel	= 0;
	TCHAR charname[128] = { '\0' };

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	charname,		128,
		NDATA_INT32,	&num,			4,		
		NDATA_INT32,	&basic,			4,		
		NDATA_INT32,	&randlevel,		4,		
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			if(siUnitKind >= MAX_BLACKARMY_UNITKIND)	{	MsgBox("fdj82jfd", "dsif83jf");		continue;	}

			// 보스는 추가하지 않는다.
			if( strncmp(charname, "KIND_BLACKBOSS", strlen("KIND_BLACKBOSS")) == 0 )			continue;

			SI32 kind = pclClient->pclKindInfoSet->FindKindFromCode(charname);
			if(kind)
			{
				oneMapUnit[siUnitKind].Init();
				oneMapUnit[siUnitKind].siKind		= kind;
				oneMapUnit[siUnitKind].siNum 		= num;
				oneMapUnit[siUnitKind].siBasicLevel	= basic;
				oneMapUnit[siUnitKind].siRandLevel	= randlevel;

				siUnitKind++;
			}
		}
	}

	bLoadFile = dataloader.LoadDataFromFile( TEXT("ServerInfo\\WarInfo.txt") );
	SI32 BossKind = siUnitKind;

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			if(BossKind >= MAX_BLACKARMY_UNITKIND)	{	MsgBox("fdj82jfd", "dsif83jf");		continue;	}

			// 보스만 추가한다.
			if( strncmp(charname, "KIND_BLACKBOSS", strlen("KIND_BLACKBOSS")) != 0 )			continue;

			SI32 kind = pclClient->pclKindInfoSet->FindKindFromCode(charname);
			if(kind)
			{
				oneMapUnit[BossKind].Init();
				oneMapUnit[BossKind].siKind			= kind;
				oneMapUnit[BossKind].siNum 			= num;
				oneMapUnit[BossKind].siBasicLevel	= basic;
				oneMapUnit[BossKind].siRandLevel	= randlevel;

				BossKind++;
			}
		}
	}

}

SI32 cltBlackArmyManager::ApplyPerson(cltBlackArmyApplyPerson *pPerson)
{
	if (clApplyList.FindApplyFromPersonid(pPerson->clApplyPerson.GetPersonID()) >= 0)
	{
		return -2;
	}

	return clApplyList.AddApplyPerson(pPerson);
}

void cltBlackArmyManager::JoinWarMap(SI16 ApplyIndex)
{
	SI16 retWapMapUnique = -1;
	SI16 i = 0;
	SI32 id = 0;
	cltCharServer* pclchar = NULL;

	cltBlackArmyApplyPerson clPerson = clApplyList.clApplyPersonList[ApplyIndex];

	if (clPerson.bWarMapAlloc)									return;
	if (clPerson.clApplyPerson.GetPersonID() <= 0)				return;

	id = pclClient->pclCM->GetIDFromPersonID(clPerson.clApplyPerson.GetPersonID());
	if (id <= 0 || pclClient->pclCM->IsValidID(id) == false)	return;
    pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
//	SI32 max_warmap_usernum = MAX_BLACKARMY_MAP_PERSON_CNT;

	// 파티원은 여기서 처리하지 않는다.
	if( pclchar->siPartyIndex > 0 )								return;

	// 맵에 할당한다.
//    for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	i = siNextJoinMap;
	SI32 siCheckMapCount = 0;

	while ( siCheckMapCount < MAX_BLACKARMY_MAP_CNT)
	{
		if( MAX_BLACKARMY_MAP_PERSON_CNT - clWarMap[i].siPersonIndex > 0 )
//		if (clWarMap[i].siPersonIndex < max_warmap_usernum )
		{
			SI32 siApplyIndex = clWarMap[i].AddWarPerson(&clPerson);
			if( siApplyIndex >= 0 )
			{
				SI32 id = pclClient->pclCM->GetIDFromPersonID(clPerson.clApplyPerson.GetPersonID());
				if (id > 0 && pclClient->pclCM->IsValidID(id))
				{
					cltCharServer *pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
					pclchar->siBlackArmyWarMapIndex = i;
					clApplyList.clApplyPersonList[ApplyIndex].siWarMapUnique = clWarMap[i].siMapIndex;
					clApplyList.clApplyPersonList[ApplyIndex].bWarMapAlloc = true;

					// 5의 배수만큼 유저를 채우고 다음 맵으로 진행한다.
					if( clWarMap[i].siPersonIndex % 5 == 0)				siNextJoinMap = (i+1) % MAX_BLACKARMY_MAP_CNT;
				}
				break;
			}
		}
		i = (i+1) % MAX_BLACKARMY_MAP_CNT;		// 다음맵 체크
		siCheckMapCount++;						// 체크 맵 개수
	}
}

// 파티 단위 인원 할당
void cltBlackArmyManager::JoinWarMapWithParty(SI16 ApplyIndex)
{
	SI32 totalPartyMembers = 0; 
	SI32 partyindex = 0;
	SI32 i = 0, j = 0;

	SI32 id	 = 0;
	cltCharServer *pclchar = NULL;

	cltBlackArmyApplyPerson clPerson = clApplyList.clApplyPersonList[ApplyIndex];

	// 이미 맵에 할당받은 유저는 처리하지 않는다.
	if (clPerson.bWarMapAlloc)									return;
	if (clPerson.clApplyPerson.GetPersonID() <= 0)				return;

	// 접속 하지 않는 유저는 제외
	id = pclClient->pclCM->GetIDFromPersonID(clPerson.clApplyPerson.GetPersonID());
	if (id <= 0 || pclClient->pclCM->IsValidID(id) == false)	return;
	pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

	//SI32 max_warmap_usernum = MAX_BLACKARMY_MAP_PERSON_CNT;

	SI32 PartyApplyIndex[MAX_PARTY_USER_NUM];
	for (i = 0; i < MAX_PARTY_USER_NUM; i++)	{	PartyApplyIndex[i] = -1;	}

	// 파티원이 아닌 유저는 처리하지 않는다.
	partyindex = pclchar->siPartyIndex;
	if( partyindex <= 0 )										return;

	// 신청인원중에 파티인원을 찾는다.
	for (i = 0; i < clApplyList.siPersonIndex; i++)
	{
		id = pclClient->pclCM->GetIDFromPersonID(clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID());
		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
			if (pclchar->siPartyIndex == partyindex && clApplyList.clApplyPersonList[i].bWarMapAlloc == false)
			{
				PartyApplyIndex[totalPartyMembers] = i;
				totalPartyMembers++;
			}
		}
	}

	// 맵에 할당한다.
	//for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	i = siNextJoinMap;
	SI32 siCheckMapCount = 0;

	while ( siCheckMapCount < MAX_BLACKARMY_MAP_CNT)
	{
		if( MAX_BLACKARMY_MAP_PERSON_CNT - clWarMap[i].siPersonIndex >= totalPartyMembers )
		{
			for (j = 0; j < totalPartyMembers; j++)
			{
				cltBlackArmyApplyPerson clPartyPerson = clApplyList.clApplyPersonList[PartyApplyIndex[j]];
				SI32 siApplyIndex = clWarMap[i].AddWarPerson(&clPartyPerson);

				if( siApplyIndex >= 0 )
				{
					id = pclClient->pclCM->GetIDFromPersonID(clPartyPerson.clApplyPerson.GetPersonID());
					if (id > 0 && pclClient->pclCM->IsValidID(id))
					{
						pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
						pclchar->siBlackArmyWarMapIndex = i;

						clApplyList.clApplyPersonList[PartyApplyIndex[j]].siWarMapUnique = clWarMap[i].siMapIndex;
						clApplyList.clApplyPersonList[PartyApplyIndex[j]].bWarMapAlloc = true;
					}
				}
			}
			// 다음 맵으로 진행
			siNextJoinMap = (i+1) % MAX_BLACKARMY_MAP_CNT;
			break;
		}
		i = (i+1) % MAX_BLACKARMY_MAP_CNT;		// 다음맵 체크
		siCheckMapCount++;						// 체크 맵 개수
	}
}

// 전쟁을 기획한다. 
bool cltBlackArmyManager::MakeWar(DWORD clock)
{
	// 전쟁중이라면, 시작할 수 없다.
	if (bWarSwitch)			return false;

	// 전쟁에 참여할 병사수와 병종을 설정한다 
	SI32 i;

	// 병조 설정정보 가져오기
	cltServer* pclserver = (cltServer*)pclClient;
	CMinisterByungzo* pclminister = (CMinisterByungzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_BYUNGZO);

	// 설정된 병력의 수
	siSettingMonNum = pclminister->m_siBlackArmyNum;

	// 병력의 수 값을 유효한 값으로 변경
	if (siSettingMonNum < 100 && siSettingMonNum > 600)		{	siSettingMonNum = 100;	}

	// 병력 데이터 초기화
/*	siUnitKind	= 0;
	siTotalUnitNum	= 0;

	// 파일 데이터 저장 공간
	cltBlackArmyUnit oneMapUnit[MAX_BLACKARMY_UNITKIND];

	// 병력 설정 파일 로딩
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	bLoadFile = dataloader.LoadDataFromFile( TEXT("ServerInfo\\WarInfo.txt") );
	if (!bLoadFile)
	{
		MsgBox(TEXT("Error"), TEXT("Don't LoadFile: WarInfo.txt"));
		return false;
	}

	SI32 num		= 0;
	SI32 basic		= 0;
	SI32 randlevel	= 0;
	TCHAR charname[128] = { '\0' };

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_MBSTRING,	charname,		128,
		NDATA_INT32,	&num,			4,		
		NDATA_INT32,	&basic,			4,		
		NDATA_INT32,	&randlevel,		4,		
		0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );

	while( !dataloader.IsEndOfData() ) 
	{
		if( dataloader.ReadData())
		{
			if(siUnitKind >= MAX_BLACKARMY_UNITKIND)
			{
				MsgBox("fdj82jfd", "dsif83jf");
				continue;
			}

			// 보스는 추가하지 않는다.
			//if( strncmp(charname, "KIND_BLACKBOSS", strlen("KIND_BLACKBOSS")) == 0 )		continue;

			SI32 kind = pclClient->pclKindInfoSet->FindKindFromCode(charname);
			if(kind)
			{
				oneMapUnit[siUnitKind].Init();
				oneMapUnit[siUnitKind].siKind		= kind;
				oneMapUnit[siUnitKind].siNum 		= num;
				oneMapUnit[siUnitKind].siBasicLevel	= basic;
				oneMapUnit[siUnitKind].siRandLevel	= randlevel;

				siUnitKind++;
			}
		}
	}*/

	// 병력 정보 잘못됨
	if (siUnitKind <= 0)		return false;

//	siTotalUnitNum = 0;

	// 흑의 군단 이벤트 배틀 필드 맵 정보 초기화
	SI32 j;
	for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	{
		clWarMap[i].Init();
		clWarMap[i].siMapUnitNum = siSettingMonNum;		// 병조가 설정한 몬스터 수치
		
		for (j = 0; j < MAX_BLACKARMY_UNITKIND; j++)
			clWarMap[i].clBlackArmyUnit[j].Set(&oneMapUnit[j]);

		//siTotalUnitNum += clWarMap[i].siMapUnitNum;

		clWarMap[i].siMapIndex = BLACKARMY_MAP_STARTINDEX + i;		// 필드맵 설정
		clWarMap[i].siGateUnique = BLACKARMY_GATEUNIQUE_START + i;	// 필드맵 설정

		clWarMap[i].bWarDoing = true;
		clWarMap[i].bBossMaked = false;
	}

	// 모든 유저들의 전쟁 정보를 초기화한다.
	pclClient->pclCM->DeleteAllWarKill();

	// 전쟁 시작 - 전쟁은 30분 동안 진행된다.
	bWarSwitch			= true;
	uiLeftTime			= 1800000 ;// 30분. 
	dwWarStartClock		= clock;

	// 참가 신청 마감
	bApplySwitch = false;

	SI32 id = 0;

	siNextJoinMap = 0;
	// 전쟁맵에 유저 분배 - 1. 파티유저
	for (i = 0; i < clApplyList.siPersonIndex; i++)
	{
		id = pclClient->pclCM->GetIDFromPersonID(clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID());
		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			if (pclClient->pclCM->CR[id]->siPartyIndex > 0)
			{
				JoinWarMapWithParty(i);
			}
		}
	}

    siNextJoinMap = 0;
	// 전쟁맵에 유저 분배 - 2. 개인유저
	for (i = 0; i < clApplyList.siPersonIndex; i++)
	{
		id = pclClient->pclCM->GetIDFromPersonID(clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID());
		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			if (pclClient->pclCM->CR[id]->siPartyIndex <= 0)
			{
				JoinWarMap(i);
			}
		}
	}

	// 전쟁맵을 부여받지 못한 신청자 처리 및 로그 전송
	for (i = 0; i < clApplyList.siPersonIndex; i++)
	{
		if (clApplyList.clApplyPersonList[i].bWarMapAlloc == false)
		{
			// 배정되지 않은 신청자에게 메세지 보내고, 참가비 돌려주도록 
			id = pclClient->pclCM->GetIDFromPersonID(clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID());
			if (id > 0 && pclClient->pclCM->IsValidID(id))
			{
				// 게임을 하고 있는 유저
				((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_BLACKARMY_FAILALLOC, 0, 0, id);

				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				sDBRequest_ChangeMoney clMsg(pclchar->GetID(), pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BLACKARMYAPPLY, BLACKARMY_APPLY_MONEY );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				pclserver->pclDelMoneyStatistics->Del(DELMONEY_ENTEREVENT, BLACKARMY_APPLY_MONEY);
			}
			else
			{
				// 게임을 하고 있는 않은 유저
				sDBRequest_ChangeMoney clMsg(0, clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID(), CHANGE_MONEY_REASON_BLACKARMYAPPLY, BLACKARMY_APPLY_MONEY );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				pclserver->pclDelMoneyStatistics->Del(DELMONEY_ENTEREVENT, BLACKARMY_APPLY_MONEY);
			}
		}

		// 맵 할당 정보를 로그로 전송
		// param1 = 참가자 번호
		// param2 = 참가자 PersonID
		// param3 = 참가 맵 인덱스
		// param4 = 맵 할당 여부
		cltCharServer* pclchar = pclClient->pclCM->GetCharServer(id);
		((cltServer*)pclClient)->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BLACKARMY, LOGCOMMAND_INDEX_BLACKARMY_APPLYMAP, 0, pclchar, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								i, clApplyList.clApplyPersonList[i].clApplyPerson.GetPersonID(), clApplyList.clApplyPersonList[i].siWarMapUnique, clApplyList.clApplyPersonList[i].bWarMapAlloc, 0,
								NULL, NULL);
	}

/*	for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	{
		//--------------------------------
		// 병사들을 배치한다. 
		//--------------------------------
		while(clWarMap[i].siMapMadeNum < siSettingMonNum) 
		{
			SI32 j = rand() % siUnitKind;
			SI32 kind = clWarMap[i].clBlackArmyUnit[ j ].siKind;

			// 블랙보스는 맵의 몹이 반수로 줄었을 경우 출현
			if (kind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")) )
				continue; 

			SI32 pos = 0 ; 
			SI32 x, y;
			SI32 tempx, tempy, level;
			SI32 mapindex = 0;

			mapindex = clWarMap[i].siMapIndex;

			tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetXsize();
			tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetYsize();

			// 몬스터를 배치할 적절한 곳을 찾는다. 
			if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, tempx, tempy, 10, &x, &y, true) == false)
			{
				continue;
			}

			level = clWarMap[i].clBlackArmyUnit[ j ].siBasicLevel + rand() % clWarMap[i].clBlackArmyUnit[ j ].siRandLevel;

			cltInnerStatusInfo clinnerstatus;
			clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

			SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
			if(id > 0 && pclClient->pclCM->IsValidID(id))
			{
				clWarMap[i].siMapMadeNum ++;
				clWarMap[i].siMapCurUnitNum++;
				clWarMap[i].clBlackArmyUnit[ j ].siCurNum++;
				clWarMap[i].clBlackArmyUnit[ j ].siMadeNum++;

				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
				
				pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);
			}
		}

		// 첫번째 단계 몬스터 생성
		clWarMap[i].siWarStep = 1;
	}*/

	// 전쟁이 시작되면 신청은 중단한다.

	//--------------------------------------------------
	// 모든 클라이언트들에게 전쟁이 시작되었음을 알린다. 
	//--------------------------------------------------
	for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	{
		// 로그기록
		// param1 = 맵 기록 위치
		// param2 = 전쟁 맵 인덱스
		// param3 = 전쟁 맵에 할당된 캐릭터 수
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BLACKARMY, LOGCOMMAND_INDEX_BLACKARMY_START, 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										i, clWarMap[i].siMapIndex, clWarMap[i].siPersonIndex, 0, 0, NULL, NULL);
		SendWarMsg(WAR_CMD_BREAK, i);
	}

	// 전쟁을 발발 시킨다. 
	return true;
}

void cltBlackArmyManager::Action()
{
	SI32 i;
	cltServer* pclserver = (cltServer*)pclClient;

	//------------------------------------------------------------------------------------------
	// MVP 유저 처리
	list<cltMVPEffectList>::iterator itor = NULL;
	list<cltMVPEffectList>::iterator deleteitor = NULL;

	for (itor = listMvpEffect.begin(); itor != listMvpEffect.end(); itor++)
	{
		cltMVPEffectList mvpperson = (cltMVPEffectList)*itor;

		if (TABS(pclClient->CurrentClock - mvpperson.dwSelectMVPClock) >= 10000)
		{
			if (mvpperson.siID > 0 && pclClient->pclCM->IsValidID(mvpperson.siID))
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[mvpperson.siID];

				// 클라이언트로 MVP 이펙트 뿌려준다.
				cltGameMsgResponse_BlackArmy_MVPEffect clinfo(pclchar->GetCharUnique());
				cltMsg clMsg(GAMEMSG_RESPONSE_BLACKARMY_MVPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNeighbourMsg(&clMsg, true);
			}

			deleteitor = itor;
		}

	}
	if (deleteitor != NULL)
	{
		listMvpEffect.erase(deleteitor);
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// 신청 & 전쟁 시작 처리
	if (pclserver->pclMinisterMgr)
	{
		// 병조판서(청룡관) 설정에 따라 전쟁실시
		CMinisterByungzo *pclminister = (CMinisterByungzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_BYUNGZO);
		if (pclminister)
		{
			if (pclminister->m_siWarStartTime > 0)
			{
				_SYSTEMTIME startTime = pclClient->GetTimeFromsMinute( (UI32) pclminister->m_siWarStartTime );

				// 설정된 시간부터 신청개시
				if (startTime.wYear == pclserver->sTime.wYear &&
					startTime.wMonth == pclserver->sTime.wMonth &&
					startTime.wDay == pclserver->sTime.wDay &&
					startTime.wHour == pclserver->sTime.wHour )
				{
					bApplySwitch = true;
				}

				// 신청받은후 59분 후에 전쟁개시 ㅡ.ㅡ;;
				if ( bApplySwitch == true && bAutoBlackWarSwitch == false )
				{
					if (startTime.wYear == pclserver->sTime.wYear &&
						startTime.wMonth == pclserver->sTime.wMonth &&
						startTime.wDay == pclserver->sTime.wDay &&
						startTime.wHour == pclserver->sTime.wHour &&
						pclserver->sTime.wMinute == 59 )
					{
						MakeWar(pclserver->CurrentClock);
						bAutoBlackWarSwitch = true;

						return;
					}
				}
			}
		}
	}
	//------------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------------
	// 전쟁과정 처리
	if(bWarSwitch == false)					return ;
		
	//--------------------------------------
	// 일정시간마다 병사들의 상황을 체크한다. 
	//---------------------------------------
	static DWORD dwLastWarCheckClock = 0;
	SI32 cmd = 0;
	if(TABS(pclClient->CurrentClock - dwLastWarCheckClock ) > 10000)
	{
		dwLastWarCheckClock = pclClient->CurrentClock;

		//---------------------------
		// 남은 시간을 확인한다. 
		//---------------------------
		DWORD lastclock = TABS(pclClient->CurrentClock - dwWarStartClock);
		dwWarStartClock	= pclClient->CurrentClock;

		if(uiLeftTime > lastclock)
		{
			uiLeftTime -= lastclock;

			for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
			{
				if (clWarMap[i].siWarcmd != WAR_CMD_WIN)
					clWarMap[i].siWarcmd = WAR_CMD_GOING;
			}
		}
		else
		{
			uiLeftTime = 0;

			AllWarEnd();
			return;
		}

		// 모든 전쟁이 끝났는지 확인한다.
		bool bAllWarEnd = true;
		for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
		{
			if (clWarMap[i].bWarDoing == true)
				bAllWarEnd = false;
		}

		// 모든 전쟁이 끝났다면, 마무리를 한다.
		if (bAllWarEnd == true)
		{
			AllWarEnd();
			return;
		}

		//siTotalCurUnitNum = 0;
        for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
		{
			if( clWarMap[i].bWarDoing == false )		continue;		// 전쟁중인 맵이 아니다.

			if( clWarMap[i].siMapMadeNum >= clWarMap[i].siMapUnitNum )
			{
				// 모든 병사가 다 만들어 졌다. - 보스 소환
				if( clWarMap[i].siMapCurUnitNum <= MAX_BLACKARMY_MAP_REGEN_CNT &&
					clWarMap[i].bBossMaked == false )
				{
					SI32 unitindex = -1;
					SI32 pos = 0 ;
					SI32 x, y;
					SI32 tempx, tempy, level;
					SI32 mapindex = 0;

					for (SI32 j = 0; j < MAX_BLACKARMY_UNITKIND; j++)
					{
						if (clWarMap[i].clBlackArmyUnit[j].siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")) )
							unitindex = j;
					}

					// 보스 소환
					if (unitindex == -1 || clWarMap[i].clBlackArmyUnit[unitindex].siMadeNum >= clWarMap[i].clBlackArmyUnit[unitindex].siNum)
						continue;

					mapindex = clWarMap[i].siMapIndex;

					tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetXsize();
					tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetYsize();

					// 몬스터를 배치할 적절한 곳을 찾는다. 
					if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")), tempx, tempy, 10, &x, &y, true) == false)
					{
						continue;
					}

					cltInnerStatusInfo clinnerstatus;
					clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

					// 보스와 같은 위치에 보디가드를 세운다.
					SI32 id;
					for (SI32 k = 0; k < BLACKARMY_BOSS_BODYGUARD; k++)
					{
						level = BLACKARMY_INC_LEVEL * 3;
						id = pclserver->SetNPCChar( pclClient->GetUniqueFromHash( TEXT("KIND_DAEGUM")), VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
						if(id > 0 && pclClient->pclCM->IsValidID(id))
						{
							clWarMap[i].siMapMadeNum ++;
							clWarMap[i].siMapCurUnitNum++;
							clWarMap[i].clBlackArmyUnit[ unitindex ].siCurNum++;
							clWarMap[i].clBlackArmyUnit[ unitindex ].siMadeNum++;

							cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
							pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);
						}
					}

					level = clWarMap[i].clBlackArmyUnit[ unitindex ].siBasicLevel + rand() % clWarMap[i].clBlackArmyUnit[ unitindex ].siRandLevel;
					id = pclserver->SetNPCChar(pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")), VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
					if(id > 0 && pclClient->pclCM->IsValidID(id))
					{
						clWarMap[i].siMapMadeNum ++;
						clWarMap[i].siMapCurUnitNum++;
						clWarMap[i].clBlackArmyUnit[ unitindex ].siCurNum++;
						clWarMap[i].clBlackArmyUnit[ unitindex ].siMadeNum++;

						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
						pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);

						// param1 = 맵 관리 인덱스
						// param2 = 맵 인덱스
						((cltServer*)pclClient)->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BLACKARMY, LOGCOMMAND_INDEX_BLACKARMY_BOSS, 0, NULL, NULL, 0, 0, 0, 0, 0, pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")), 0, 0, 0, 0,
													i, clWarMap[i].siMapIndex, 0, 0, 0, NULL, NULL);

						// 보스가 생성됨.
						clWarMap[i].bBossMaked = true;

						// 보스출현시 메세지 뿌려줌
						for (j = 0; j < clWarMap[i].siPersonIndex; j++)
						{
							SI32 userid = pclClient->pclCM->GetIDFromPersonID(clWarMap[i].clWarPersonList[j].clApplyPerson.GetPersonID());

							if (userid > 0 && pclClient->pclCM->IsValidID(userid))
							{
								TCHAR* pTitle = GetTxtFromMgr(5857);
								TCHAR* pText = GetTxtFromMgr(5858);

								cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
								cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

								pclClient->pclCM->CR[userid]->SendNetMsg((sPacketHeader*)&clMsg);
							}
						}
					}
				}
			}
			else
			{
				// 아직 만들 병사가 남았다.
				if( clWarMap[i].siMapCurUnitNum <= MAX_BLACKARMY_MAP_REGEN_CNT )
				{
					// 최대 맵에 존재할 수 있는 병사까지만 생성한다.
					while( clWarMap[i].siMapCurUnitNum < MAX_BLACKARMY_MAP_ARMY_CNT &&
						   clWarMap[i].siMapMadeNum < clWarMap[i].siMapUnitNum)
					{
						SI32 j = rand() % siUnitKind;
						SI32 kind = clWarMap[i].clBlackArmyUnit[ j ].siKind;

						SI32 pos = 0 ;
						SI32 x, y;
						SI32 tempx, tempy, level;
						SI32 mapindex = 0;

						mapindex = clWarMap[i].siMapIndex;
						tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetXsize();
						tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetYsize();

						// 몬스터를 배치할 적절한 곳을 찾는다. 
						if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, tempx, tempy, 10, &x, &y, true) == false)
						{
							continue;
						}

						level = clWarMap[i].clBlackArmyUnit[ j ].siBasicLevel + rand() % clWarMap[i].clBlackArmyUnit[ j ].siRandLevel;

						cltInnerStatusInfo clinnerstatus;
						clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

						SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
						if(id > 0 && pclClient->pclCM->IsValidID(id))
						{
							clWarMap[i].siMapMadeNum ++;
							clWarMap[i].siMapCurUnitNum++;
							clWarMap[i].clBlackArmyUnit[ j ].siCurNum++;
							clWarMap[i].clBlackArmyUnit[ j ].siMadeNum++;

							cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

							pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);

						}
					}
				}
			}
/*			//--------------------------------
			// 나머지 병사 배치
			//--------------------------------
			// BlackBoss 출현 조건
			if (clWarMap[i].siMapCurUnitNum <= siSettingMonNum / 10 && clWarMap[i].siWarStep > 2)
			{
				SI32 unitindex = -1;
				SI32 pos = 0 ;
				SI32 x, y;
				SI32 tempx, tempy, level;
				SI32 mapindex = 0;

				for (SI32 j = 0; j < MAX_BLACKARMY_UNITKIND; j++)
				{
					if (clWarMap[i].clBlackArmyUnit[j].siKind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")) )
						unitindex = j;
				}

				if (unitindex == -1 || clWarMap[i].clBlackArmyUnit[unitindex].siMadeNum >= clWarMap[i].clBlackArmyUnit[unitindex].siNum)
					continue;

				mapindex = clWarMap[i].siMapIndex;

				tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetXsize();
				tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetYsize();

				// 몬스터를 배치할 적절한 곳을 찾는다. 
				if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")), tempx, tempy, 10, &x, &y, true) == false)
				{
					continue;
				}

				cltInnerStatusInfo clinnerstatus;
				clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

				SI32 id;

				for (SI32 k = 0; k < BLACKARMY_BOSS_BODYGUARD; k++)
				{
					level = BLACKARMY_INC_LEVEL * 3;
					id = pclserver->SetNPCChar( pclClient->GetUniqueFromHash( TEXT("KIND_DAEGUM")), VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
					if(id > 0 && pclClient->pclCM->IsValidID(id))
					{
						clWarMap[i].siMapMadeNum ++;
						clWarMap[i].siMapCurUnitNum++;
						clWarMap[i].clBlackArmyUnit[ unitindex ].siCurNum++;
						clWarMap[i].clBlackArmyUnit[ unitindex ].siMadeNum++;

						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
						pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);
					}
				}

				level = clWarMap[i].clBlackArmyUnit[ unitindex ].siBasicLevel + rand() % clWarMap[i].clBlackArmyUnit[ unitindex ].siRandLevel;

				id = pclserver->SetNPCChar(pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")), VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
				if(id > 0 && pclClient->pclCM->IsValidID(id))
				{
					clWarMap[i].siMapMadeNum ++;
					clWarMap[i].siMapCurUnitNum++;
					clWarMap[i].clBlackArmyUnit[ unitindex ].siCurNum++;
					clWarMap[i].clBlackArmyUnit[ unitindex ].siMadeNum++;

					cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
					pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);

					// 보스출현시 메세지 뿌려줌
					for (j = 0; j < clWarMap[i].siPersonIndex; j++)
					{
						SI32 userid = pclClient->pclCM->GetIDFromPersonID(clWarMap[i].clWarPersonList[j].clApplyPerson.GetPersonID());

						if (userid > 0 && pclClient->pclCM->IsValidID(userid))
						{

							TCHAR* pTitle = GetTxtFromMgr(5857);
							TCHAR* pText = GetTxtFromMgr(5858);

							cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
							cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

							pclClient->pclCM->CR[userid]->SendNetMsg((sPacketHeader*)&clMsg);
						}
					}
				}
			}
			// siSettingMonNum / 20 이하로 적 남으면 적증원
			else if(clWarMap[i].bWarDoing == true && clWarMap[i].siMapCurUnitNum < siSettingMonNum / 20)
			{
				SI32 rejenMonsterCnt;

				// 두번째 단계에서는 siSettingMonNum / 3 * 2 만큼
				if (clWarMap[i].siWarStep == 1)
				{
					rejenMonsterCnt = siSettingMonNum / 3 * 2;
				}
				// 마지막에는 나머지 모두
				else
				{
					rejenMonsterCnt = siSettingMonNum;
				}

				pclClient->pclLog->LogPrint("clWarMap[i].siMapMadeNum < rejenMonsterCnt\n", clWarMap[i].siMapMadeNum, rejenMonsterCnt);

				while(clWarMap[i].siMapMadeNum < rejenMonsterCnt)
				{
					SI32 j = rand() % siUnitKind;
					SI32 kind = clWarMap[i].clBlackArmyUnit[ j ].siKind;

					// 블랙보스는 맵의 몹이 50으로 줄었을 경우 출현
					if (kind == pclClient->GetUniqueFromHash(TEXT("KIND_BLACKBOSS")))
						continue;


					SI32 pos = 0 ;
					SI32 x, y;
					SI32 tempx, tempy, level;
					SI32 mapindex = 0;

					mapindex = clWarMap[i].siMapIndex;
					tempx = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetXsize();
					tempy = 1 + rand() % pclClient->pclMapManager->pclMapArray[mapindex]->GetYsize();

					// 몬스터를 배치할 적절한 곳을 찾는다. 
					if(pclClient->pclMapManager->pclMapArray[mapindex]->FindEmptyAreaForCharLocate(kind, tempx, tempy, 10, &x, &y, true) == false)
					{
						continue;
					}

					level = clWarMap[i].clBlackArmyUnit[ j ].siBasicLevel + rand() % clWarMap[i].clBlackArmyUnit[ j ].siRandLevel;

					if (clWarMap[i].siWarStep == 1)
					{
						level = BLACKARMY_INC_LEVEL;
					}
					else
					{
						level = BLACKARMY_INC_LEVEL * 2;
					}

					cltInnerStatusInfo clinnerstatus;
					clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);

					SI32 id = pclserver->SetNPCChar(kind, VILLAGE_NONE, NULL, level, 0, x, y, mapindex, NPCITEMMODE_NORMAL, &clinnerstatus );
					if(id > 0 && pclClient->pclCM->IsValidID(id))
					{
						clWarMap[i].siMapMadeNum ++;
						clWarMap[i].siMapCurUnitNum++;
						clWarMap[i].clBlackArmyUnit[ j ].siCurNum++;
						clWarMap[i].clBlackArmyUnit[ j ].siMadeNum++;

						cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

						pclchar->clIdentity.MakeBlackArmy(IDENTITY_BLACKARMY, i, clWarMap[i].siMapIndex);

					}

				}
				
				// 적증원시 메세지 뿌려줌
				if (clWarMap[i].siWarStep <= 2)
				{
					for (SI32 j = 0; j < clWarMap[i].siPersonIndex; j++)
					{
						SI32 userid = pclClient->pclCM->GetIDFromPersonID(clWarMap[i].clWarPersonList[j].clApplyPerson.GetPersonID());

						if (userid > 0 && pclClient->pclCM->IsValidID(userid))
						{

							TCHAR* pTitle = GetTxtFromMgr(4903);
							TCHAR* pText = GetTxtFromMgr(5897);

							cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
							cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);

							pclClient->pclCM->CR[userid]->SendNetMsg((sPacketHeader*)&clMsg);

						}

					}
				}

				clWarMap[i].siWarStep++;
				pclClient->pclLog->LogPrint("clWarMap[i].siWarStep = %d\n", i, clWarMap[i].siWarStep);
			}
			siTotalCurUnitNum += clWarMap[i].siMapCurUnitNum;*/
		}

		for (i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
		{
			//전쟁이 승리하거나 시간이 지났을때만 끝나도록 변경
			if(clWarMap[i].siWarcmd == WAR_CMD_WIN)
			{
				WarEnd(i);
				continue;
			}		

			SendWarMsg(clWarMap[i].siWarcmd, i);
		}		
	}
}

SI16 cltBlackArmyManager::FindWarMapIndex(SI32 mapindex)
{
	SI16 retWarMapIndex = -1;
	for (int i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	{
		if (clWarMap[i].siMapIndex == mapindex)
			retWarMapIndex = i;
	}

	return retWarMapIndex;
}

SI16 cltBlackArmyManager::FindWarUnitIndex(SI32 kind)
{
	SI16 retWarUnitIndex = -1;
	for (int i = 0; i < MAX_BLACKARMY_UNITKIND; i++)
	{
		if (clWarMap[0].clBlackArmyUnit[i].siKind == kind)
			retWarUnitIndex = i;
	}

	return retWarUnitIndex;
}

void cltBlackArmyManager::AllWarEnd()
{
	if (bWarSwitch == false) return;

	for (SI32 i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
	{
		if (clWarMap[i].siWarcmd != WAR_CMD_WIN)
			clWarMap[i].siWarcmd = WAR_CMD_LOSE;

		WarEnd(i);
	}

	clApplyList.InitList();

	bWarSwitch = false;
	bApplySwitch = false;

	if (bAutoBlackWarSwitch)
	{
		cltServer *pclserver = (cltServer*)pclClient;
		CMinisterByungzo *pclminister = (CMinisterByungzo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_BYUNGZO);
		if (pclminister)
		{
			SI32 siID = 0;

			// 전쟁 끝났으니 전쟁설정카운트 증가, 전쟁시작시간 초기화
			pclminister->m_siSetWarCount++;
			pclminister->m_siWarStartTime = 0;

			sDBRequest_SetByungzoInfo clMsg(siID, pclminister->m_siPersonID,
				pclminister->m_szGreeting, pclminister->m_siVillageWarTime , pclminister->m_siSetTime, pclminister->m_siWarStartTime, 
				pclminister->m_siSetWarCount, pclminister->m_siBlackArmyNum);

			((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
	}

	bAutoBlackWarSwitch = false;
}


void cltBlackArmyManager::WarEnd(SI32 warmapindex)
{
	SI32 i, j;
	SI32 statistic[10];

	if (clWarMap[warmapindex].bWarDoing == false)
		return;

	for(i = 0;i < 10;i++)
	{
		statistic[i] = 0;
	}

	//----------------------------------
	// 전쟁 병사들의 전쟁 목표를 없앤다.
	//----------------------------------
	
	SI32 index = 0;
	SI32 id;
	while(id = pclClient->pclCM->GetCharOrder(index))
	{
		index++;
		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
			if (pclchar->clIdentity.siIdentity == IDENTITY_BLACKARMY)
			{
				if (pclchar->clIdentity.clBlackArmyInfo.siWarMapIndex == warmapindex)
				{
					// 셀 내에서의 정보를 삭제한다. 
					pclClient->pclCM->CR[id]->DeleteInCell();
					if(pclClient->pclCM->DeleteChar( id ) == TRUE)
					{
						index--;
					}
				}
			}
		}
	}

	//----------------------------------
	// 전공이 높은 상위 MAX_WARRANK_PERSON_PER_MAP 명을 소트한다. 
	//----------------------------------
	SI32 siWarSortRecordChar[MAX_WARRANK_PERSON_PER_MAP];
	ZeroMemory(siWarSortRecordChar, sizeof(SI32) * MAX_WARRANK_PERSON_PER_MAP);
	pclClient->pclCM->SortWarRecord(siWarSortRecordChar, MAX_WARRANK_PERSON_PER_MAP, warmapindex);

	SI32 personid, score;
	TCHAR charname[256];

	cltWarRankInfo warrank;
	warrank.m_warmapindex = warmapindex;

	for (i = 0; i < MAX_WARRANK_PERSON_PER_MAP; i++)
	{
		if (clWarMap[warmapindex].siWarcmd == WAR_CMD_WIN)
		{
			SI32 id = siWarSortRecordChar[i];
			if (id > 0 && pclClient->pclCM->IsValidID(id))
			{
				personid = pclClient->pclCM->CR[id]->pclCI->clBI.clPerson.GetPersonID();
				StringCchCopy(charname, 256, pclClient->pclCM->CR[id]->GetName());
				score = pclClient->pclCM->CR[id]->siWarEnemyKillNumber;
			}
			else
			{
				personid = -1;
				StringCchCopy(charname, 256, TEXT(""));
				score = -1;
			}

		}
		else
		{
			personid = -1;
			StringCchCopy(charname, 256, TEXT(""));
			score = -1;
		}

		warrank.SetRankPerson( i + 1, personid, charname, score);
	}

	sDBRequest_SetWarRankInfo clRankMsg(&warrank);
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clRankMsg);

	for (i = 0; i < clWarMap[warmapindex].siPersonIndex; i++)
	{
		id = pclClient->pclCM->GetIDFromPersonID(clWarMap[warmapindex].clWarPersonList[i].clApplyPerson.GetPersonID());
		// 사용자인 컴에게만 전달한다. 
		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			if(pclClient->pclCM->CR[id]->IsValidConnection() == true)
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
				if (pclchar->siBlackArmyWarMapIndex == warmapindex )
				{
					if (clWarMap[warmapindex].siGateUnique > 0 && pclchar->GetMapIndex() == clWarMap[warmapindex].siMapIndex && pclClient->pclCM->IsAlive(id))
					{
						cltGate gate = pclClient->pclMapManager->pclGateManager->clGate[clWarMap[warmapindex].siGateUnique];

						cltWarpInfo clinfo(true, gate.SrcMapIndex, false, false, gate.SrcX, gate.SrcY, -1, -1);
						pclchar->SetWarpInfo(&clinfo,56);
					}

					if (clWarMap[warmapindex].siWarcmd == WAR_CMD_WIN)
					{
						//---------------------------------------------
						// 이긴맵의 사용자들에게 전리품을 지급
						//---------------------------------------------
						GMONEY money = pclchar->siWarEnemyKillNumber * 50; 
						SI32 personalfameexp = 0;
						SI32 rewarditemnum = 0;
						SI32 rewarditemunique = ITEMUNIQUE(5045); //ITEMUNIQUE(5316);

						SI32 ranking = 0;
						for (j = 0; j < MAX_WARRANK_PERSON_PER_MAP; j++)
						{
							if (pclchar->siID == siWarSortRecordChar[j])
							{
								ranking = j + 1;
							}
						}

						switch (ranking)
						{
						case 1 : 
							personalfameexp = 500;
							rewarditemnum = 50;
							break;
						case 2 : 
							personalfameexp = 400;
							rewarditemnum = 40;
							break;
						case 3 : 
							personalfameexp = 300;
							rewarditemnum = 30;
							break;
						case 4 : 
							personalfameexp = 200;
							rewarditemnum = 20;
							break;
						case 5 : 
							personalfameexp = 100;
							rewarditemnum = 10;
							break;
						}

						// 피로방지 시스템 적용
						rewarditemnum = pclchar->CalcTiredPoint( rewarditemnum );
						money = pclchar->CalcTiredPoint( money );

						if ( rewarditemnum > 0 )
						{
							if ( pclchar->GiveItem(rewarditemunique, rewarditemnum,INPUTITEMPERSON_OPTION_BLACKARMY, 0) == false )
							{
								((cltServer*)pclClient)->SendLog_InventoryFull(pclchar->pclCI->GetPersonID(),rewarditemunique,rewarditemnum,INPUTITEMPERSON_OPTION_WAR);
							}
						}

						// 클라이언트에게 돈과 경험치를 받았음을 통보한다. 
						cltGameMsgResponse_WinWarPrize clinfo(-1, money, 0, 0, 0, rewarditemunique, rewarditemnum);
						cltMsg clMsg(GAMEMSG_RESPONSE_WINWARPRIZE, sizeof(clinfo), (BYTE*)&clinfo);
						pclchar->SendNetMsg((sPacketHeader*)&clMsg);

						sDBRequest_ChangeMoney clMoneyMsg(id, pclClient->pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_WARWIN, money);
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMoneyMsg);

						((cltServer*)pclClient)->pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_EVENT, money);

						// 통화량 집계한다. 
						cltServer* pclserver = (cltServer*)pclClient;
						cltMoney clmoney;
						clmoney.Set(money);
						pclserver->clCurrencyInfo.clInputMoney_War.Increase(&clmoney);

					}
				}
			}
		}
	}

	SendWarMsg(clWarMap[warmapindex].siWarcmd, warmapindex);

	if (clWarMap[warmapindex].siWarcmd == WAR_CMD_WIN)
	{
		TCHAR mvpname[MAX_PLAYER_NAME];
		if (warrank.GetRankPerson(1)->m_score > 0)
		{
			StringCchCopy(mvpname, MAX_PLAYER_NAME, warrank.GetRankPerson(1)->m_szPlayerName);

			TCHAR *MapName = pclClient->pclMapManager->GetMapName(clWarMap[warmapindex].siMapIndex);
			TCHAR *pTitle = GetTxtFromMgr(5884);
			TCHAR *pText = GetTxtFromMgr(5883);
			TCHAR buf[256];
			StringCchPrintf(buf, 256, pText, MapName, MapName, mvpname);

			((cltServer*)pclClient)->PushSpecialNews( buf, pTitle , NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);

			id = pclClient->pclCM->GetIDFromPersonID(warrank.GetRankPerson(1)->m_personid);
			
			if (id > 0 && pclClient->pclCM->IsValidID(id))
			{
				if(pclClient->pclCM->CR[id]->IsValidConnection() == true)
				{
					// 이펙트 뿌려줄 캐릭id 저장
					cltMVPEffectList mvpperson(pclClient->CurrentClock, id);

                    listMvpEffect.push_back(mvpperson);
				}
			}

		}
	}
	else
	{
		TCHAR *MapName = pclClient->pclMapManager->GetMapName(clWarMap[warmapindex].siMapIndex);
		TCHAR *pTitle = GetTxtFromMgr(5884);
		TCHAR *pText = GetTxtFromMgr(5885);
		TCHAR buf[256];
		StringCchPrintf(buf, 256, pText, MapName);

		((cltServer*)pclClient)->PushSpecialNews( buf, pTitle ,NULL, CAPTIONKIND_NEWS,CAPTIONKIND_NEWSCHAT);

	}

	((cltServer*)pclClient)->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BLACKARMY, LOGCOMMAND_INDEX_BLACKARMY_END, 0, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
												0, 0, 0, 0, 0, NULL, NULL);
	clWarMap[warmapindex].bWarDoing = false;
	clWarMap[warmapindex].bBossMaked = false;
	clWarMap[warmapindex].InitList();
}

void cltBlackArmyManager::SendWarMsg(SI32 cmd, SI32 warmapindex)
{

	SI32 index = 0;
	SI32 id;
	SI32 i;
    
	//----------------------------------
	// 전공이 높은 상위 MAX_WARRANK_PERSON_PER_MAP명을 소트한다. 
	//----------------------------------
	SI32 siWarSortRecordChar[MAX_WARRANK_PERSON_PER_MAP];
	TCHAR szWarSortCharName[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];
	SI32 siWarScore[MAX_WARRANK_PERSON_PER_MAP];

	ZeroMemory(siWarSortRecordChar, sizeof(SI32) * MAX_WARRANK_PERSON_PER_MAP);
	pclClient->pclCM->SortWarRecord(siWarSortRecordChar, MAX_WARRANK_PERSON_PER_MAP, warmapindex);

	for (i = 0; i < MAX_WARRANK_PERSON_PER_MAP; i++)
	{
		id = siWarSortRecordChar[i];

		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			const TCHAR *pName = pclClient->pclCM->CR[siWarSortRecordChar[i]]->GetName();

			if (pName != NULL && _tcscmp(pName, "") != 0)
			{
				StringCchPrintf(szWarSortCharName[i], MAX_PLAYER_NAME, TEXT("%s"), pName);
				siWarScore[i] = pclClient->pclCM->CR[siWarSortRecordChar[i]]->siWarEnemyKillNumber;
			}
			else
			{
				StringCchPrintf(szWarSortCharName[i], MAX_PLAYER_NAME, TEXT(""));
				siWarScore[i] = 0;
			}
		}
		else
		{
			StringCchPrintf(szWarSortCharName[i], MAX_PLAYER_NAME, TEXT(""));
			siWarScore[i] = 0;
		}
		
	}

	for (i = 0; i < clWarMap[warmapindex].siPersonIndex; i++)
	{
		id = pclClient->pclCM->GetIDFromPersonID(clWarMap[warmapindex].clWarPersonList[i].clApplyPerson.GetPersonID());

		if (id > 0 && pclClient->pclCM->IsValidID(id))
		{
			// 사용자인 컴에게만 전달한다. 
			if(pclClient->pclCM->CR[id]->IsValidConnection() == true)
			{
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				if (pclchar->siBlackArmyWarMapIndex == warmapindex)
				{
					cltGameMsgResponse_BlackArmy_War clwar(cmd, uiLeftTime, warmapindex, clWarMap[warmapindex].siMapCurUnitNum, (TCHAR**)szWarSortCharName, (SI32*)siWarScore);
					cltMsg clMsg(GAMEMSG_RESPONSE_BLACKARMYWAR, sizeof(clwar), (BYTE*)&clwar);

					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				}

				if (cmd == WAR_CMD_BREAK)
				{
					// [영훈] 개인상점을 개설한 상태에서는 메시지를 보내지 않음
					if ( ( true == pclClient->pclCM->CR[id]->bPersonalShopSwitch )
						|| ( true == pclClient->pclCM->CR[id]->bPremiumPersonalShop )
					)
					{
						continue;
					}

					((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_BLACKARMY_MAPPOSITION,  
						clWarMap[warmapindex].siGateUnique, 0, pclchar->GetCharUnique());
				}

			}


		}

	}


}

void cltBlackArmyManager::SetDraw(SI32 cmd)
{
	bDrawSwitch = true;

	switch(cmd)
	{
	case WAR_CMD_BREAK:
		{
			siDrawCmdFont	= 0;
			pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WARBREAK")), 0, 0);
			((cltClient*)pclClient)->PlayBackgroundMusic(0);
		}
		break;
	case WAR_CMD_WIN:	
		siDrawCmdFont	= 1;	
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WARWIN")), 0, 0);
		break;
	case WAR_CMD_LOSE:	
		siDrawCmdFont	= 2;	
		pclClient->PushEffect(pclClient->GetUniqueFromHash(TEXT("SOUND_EFFECT_WARLOSE")), 0, 0);	
		break;	
	}

	if ( cmd == WAR_CMD_WIN || cmd == WAR_CMD_LOSE )
	{
		((cltClient*)pclClient)->PlayBackgroundMusic(pclClient->pclCM->CR[1]->GetMapIndex());
	}

	dwDrawStartClock = pclClient->CurrentClock;
}

// 전황을 표시한다. 
void cltBlackArmyManager::Draw(LPDIRECTDRAWSURFACE7 lpsurface, SI32 rx, SI32 ry)
{
	if(bDrawSwitch == false)return ;

	if( TABS(pclClient->CurrentClock - dwDrawStartClock) > 10000)
	{
		bDrawSwitch = false;
	}

	TSpr* pspr = pclClient->GetGlobalSpr(GIMG_MAGIC_WAR);
	if(pspr == NULL)return ;

	cltClient* pclclient = (cltClient*)pclClient;

	SI32 yindent = 0 ;

	if ( g_SoundOnOffDlg.m_bFullScreenMode )
	{
		yindent = 30 ;
	}

	if(GP.LockSurface(lpsurface)==TRUE)
	{
		GP.PutSpr( pspr, (pclclient->siClientScreenXsize - pspr->GetXSize())/2 + rx, 
			50  + ry + yindent , siDrawCmdFont);

		GP.UnlockSurface(lpsurface);
	}
}
