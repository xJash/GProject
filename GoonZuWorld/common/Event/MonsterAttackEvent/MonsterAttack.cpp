#include "MonsterAttack.h"

#include "Char\CharManager\CharManager.h"
#include "../Server/Server.h"
#include "../CommonLogic/CommonLogic.h"
#include "../CommonLogic/MsgRval-Define.h"
#include "../CommonLogic/MsgType-Person.h"
#include "../CommonLogic/Msg/MsgType-Village.h"

#include "../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../DBManager/GameDBManager_World/DBMsg-Village.h"
#include "../common/Util/Util.h"
#include "../../NLib/NUtil.h"

#include "../common/Event/event.h"


extern cltCommonLogic* pclClient;

CMonsterAttackEvent::CMonsterAttackEvent() 
{
	Clear();

	m_arEventCount_EachVillage.ZeroMem();
}

void CMonsterAttackEvent::Clear(void)
{
	//ZeroMemory(this, sizeof(CMonsterAttackEvent)); 

	m_bEvent = false;
	ZeroMemory( &m_stStartTime, sizeof(m_stStartTime) );
	ZeroMemory( &m_stEndTime, sizeof(m_stEndTime) );
#ifdef _SAFE_MEMORY
	m_siMosterInfo.ZeroMem();
#else
	ZeroMemory( m_siMosterInfo, sizeof(m_siMosterInfo) );
#endif
	m_dwStartTickCount = 0;
	m_dwRemainSecondTime = 0;	
	m_siEventVillageUnique = -1;
}

CMonsterAttackEvent::~CMonsterAttackEvent() 
{
	
}

bool CMonsterAttackEvent::IsEvent(void)
{
	return m_bEvent;
}

void CMonsterAttackEvent::StartEvent(SI32 _siEventVillageUnique)
{
	m_bEvent = EVENT_START;

	m_dwStartTickCount	 = GetTickCount();
	m_dwRemainSecondTime = 50 * 60;

	// ���۽ð� ����.
	m_stStartTime = ((cltServer*)pclClient)->sTime;

	m_siEventVillageUnique = _siEventVillageUnique;

	// �̺�Ʈ ���� Ƚ�� ����
	MonsterAttack_EventCount_Increase();
	
	// ������ �ð� ����.
	TimeAddMinute( &m_stStartTime, RUN_TIME, &m_stEndTime );
	
	CreateMonster();

	SendMsg(SRVAL_MONSTER_ATTACK_EVENT);

	pclClient->pclLog->FilePrint(TEXT("Config\\MonsterAttack.log"), "[START] VillageUnique = %d", _siEventVillageUnique );
}

void CMonsterAttackEvent::EndEvent(bool b_GiveReward)
{
	m_bEvent = EVENT_END;

	DestroyMonster();
	
	if(true == b_GiveReward)
	{
		EventReward();

		SI32 siRewardItemUnique	= ITEMUNIQUE(24082);
		SI32 siRewardItemNum = 0;

		// ���ֵ����̰�, ���� ���� �̺�Ʈ ���� Ƚ���� 1ȸ �϶��� ������ 2�� ����
		if ( pclClient->pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &(((cltServer*)pclClient)->sTime))
			&& EVENT_SPECIALREWARD_COUNT == MonsterAttack_EventCount_Get() )
		{
			siRewardItemNum		= 2;
		}
		else
		{
			siRewardItemNum		= 1;
		}

		// ����� ���� ó���� ���� �޼��� ������ �Ķ���� Ȯ���� ���� �ʰ� ���� ��Ŷ���� ����� ���� ó��
		//SendMsg(MONSTER_ATTACK_EVENT_END_SUCCED, 500); -> �� �ڵ尡 �Ʒ�ó�� ����

		//////////////////////////////////////////////////////////////////////////
		if(0 >= m_siEventVillageUnique)
			return;

		cltServer* pclserver = (cltServer*)pclClient;

		//���� �������� �޽����� ������.
		cltCharServer* pclchar = NULL;
		for( SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount )
		{
			if(false == pclClient->pclCM->IsValidID(UserCount))
				continue;

			pclchar = (cltCharServer*)pclClient->pclCM->CR[UserCount];
			if(NULL == pclchar) continue;

			if( m_siEventVillageUnique == (SI16)pclchar->pclCI->clBI.siHomeVillage )			
			{
				cltGameMsgResponse_Event_MonsterAttack_Reward clSndInfo( 0, 500, siRewardItemUnique, siRewardItemNum );
				cltMsg clSndMsg( GAMEMSG_RESPONSE_MONSTER_ATTACK_REWARD, sizeof(clSndInfo), (BYTE*)&clSndInfo );
				pclchar->SendNetMsg( (sPacketHeader*)&clSndMsg );

				// �����Ѵٰ� ���� ��������ֱ� ���� �ڵ�
				cltMsg clMsg(GAMEMSG_RESPONSE_MONSTER_ATTACK_START, sizeof(m_siEventVillageUnique), (BYTE*)&m_siEventVillageUnique);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
		//////////////////////////////////////////////////////////////////////////

		pclClient->pclLog->FilePrint(TEXT("Config\\MonsterAttack.log"), "[END] WIN VillageUnoque = %d", GetEventVillageUnique() );
	}
	else
	{
		SendMsg(MONSTER_ATTACK_EVENT_END_FAIL);
		
		pclClient->pclLog->FilePrint(TEXT("Config\\MonsterAttack.log"), "[END] LOSE VillageUnoque = %d", GetEventVillageUnique() );
	}

	

	Clear();
}

void CMonsterAttackEvent::CreateMonster(void)
{
	SI32	siRet = 0;

	cltServer* pclserver = (cltServer*)pclClient;
	
	// ���� ���� ����
	SetMonsterKind();

	// ���Ͱ� ������ ���� ������ �����ϰ�.
	RandMap();

	SI32 tempx 			= (rand() % 5);
	SI32 tempy 			= (rand() % 5);
	SI32 x 				= 0;
	SI32 y 				= 0;
	SI32 MapIndex		= 0;
	SI32 NPCKind		= 0;

	const SI32 Const_Limit_Count = 30;
	SI32 siExitCnt		= 0;
	bool bFindLocate	= false;

	cltInnerStatusInfo clinnerstatus;
	clinnerstatus.clEnemyType.Set(ENEMYTYPE_ALLPC, 0);   

	for( SI32 MonsterCount = 0; MonsterCount < MOSTER_NUM; ++MonsterCount )
	{
		siExitCnt	= 0;
		bFindLocate	= false;
		MapIndex	= m_siMosterInfo[MonsterCount].GetMapIndex();
		NPCKind		= m_siMosterInfo[MonsterCount].GetMonsterkind();

		// ��ġ�� ��ã�� ���ٸ� �ִ� 30������ ������ ����
		do 
		{
			if ( siExitCnt++ > Const_Limit_Count )
			{
				break;
			}

			tempx		= 1 + rand() % pclClient->pclMapManager->pclMapArray[MapIndex]->GetXsize();
			tempy		= 1 + rand() % pclClient->pclMapManager->pclMapArray[MapIndex]->GetYsize();

			bFindLocate	= pclClient->pclMapManager->pclMapArray[MapIndex]->FindEmptyAreaForCharLocate(MapIndex, tempx, tempy, 10, &x, &y, true);

		} while( false == bFindLocate );
		  

		if ( true == bFindLocate )
		{
			SI32 id = pclserver->SetNPCChar(NPCKind, VILLAGE_NONE, NULL, 90, 0, x, y, MapIndex, NPCITEMMODE_NORMAL, &clinnerstatus);
			if(id > 0)
			{ 
				// ������ ���̵� ����.
				m_siMosterInfo[MonsterCount].SetMonsterID(id);
							
				// ���� ���� �̺�Ʈ ĳ���� �ź� 
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
				pclchar->clIdentity.MakeMonsterAttackEvent(IDENTITY_MONSTER_ATTACK_EVENT);

				pclClient->pclLog->FilePrint( TEXT("Config\\MonsterAttack.log"), TEXT("[CreateMonster]\tKIND=%d\tMapIndex=%d\tX=%d\tY=%d\t"), NPCKind, MapIndex, x, y );
			}
		}
	}
}

void CMonsterAttackEvent::DestroyMonster(void)
{
	SI32		   id = 0;
	cltCharServer* pclchar = NULL;
	
	for( SI32 MonsterCount = 0; MonsterCount < MOSTER_NUM; ++MonsterCount )
	{
		// ���� ��� �ִ� �ѵ��� ����.
		if(m_siMosterInfo[MonsterCount].IsLive())
		{
			id = m_siMosterInfo[MonsterCount].GetMonsterID();
			
			if(false == pclClient->pclCM->IsValidID(id))
				continue;

			pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

			cltGameMsgResponse_IncLife clInfo(pclchar->GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_TIMEOUT);
			cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
			pclchar->SendNeighbourMsg(&clMsg, true);

			pclchar->SetLife(0);
		}
	}
}

void CMonsterAttackEvent::MonsterDie( SI32 _DieMonsterKind )
{
	for( SI32 SlotCount = 0; SlotCount < MOSTER_NUM; ++SlotCount )
	{
		if( m_siMosterInfo[SlotCount].GetMonsterkind() == _DieMonsterKind )
		{
			m_siMosterInfo[SlotCount].Die();
			SendMsg(MONSTER_ATTACK_EVENT_MONSTER_DIE, SlotCount);
		}
	}

	// ���Ͱ� �� �׾����� ����.
	if(true == MonsterAllDie())
	{
		EndEvent(true);
	}
}

void CMonsterAttackEvent::EventReward(void)
{
	if(0 >= m_siEventVillageUnique)
		return;
	
	cltCharServer* pclchar = NULL;
	SI32		   ItemNum = 0;

	for( SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount )
	{
		if(false == pclClient->pclCM->IsValidID(UserCount))
			continue;

		pclchar = (cltCharServer*)pclClient->pclCM->CR[UserCount];

		SI32 siRewardItemUnique = 0;
		SI32 siRewardItemNum	= 0;

		// ���� �ּ�ó��-------------------------------------------
		/*if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
		{
			siRewardItemUnique	= ITEMUNIQUE(8113);
			siRewardItemNum		= 3;
		}
		else*/
		//---------------------------------------------------------

		/*{
			siRewardItemUnique	= ITEMUNIQUE(24082);
			siRewardItemNum		= 1;
		}*/

		
		cltServer* pServer = (cltServer*)pclClient;
		if ( NULL == pServer )
		{
			return;
		}

		siRewardItemUnique	= ITEMUNIQUE(24082);

		// ���ֵ����̰�, ���� ���� �̺�Ʈ ���� Ƚ���� 1ȸ �϶��� ������ 2�� ����
		if ( pServer->pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &pServer->sTime)
			&& EVENT_SPECIALREWARD_COUNT == MonsterAttack_EventCount_Get() )
		{
			siRewardItemNum		= 2;
		}
	
		else
		{
			siRewardItemNum		= 1;
		}

		if(siRewardItemUnique > 0 && siRewardItemNum > 0)
		{
			// ���� ���� �̶�� �������� �ش�.
			if( m_siEventVillageUnique == pclchar->pclCI->clBI.siHomeVillage )
			{
				if(GIVEITEM_RESULT_SUCCESS == pclchar->GiveItem(siRewardItemUnique, siRewardItemNum, INPUTITEMPERSON_OPTION_NONE, 0))
				{
					pclClient->pclLog->FilePrint(	TEXT("Config\\MonsterAttack.log"), 
													"[REWARD ITEM] VillageUnique = %d, Name = %s, ItemUnique = %d, ItemNum = %d", 
													m_siEventVillageUnique,
													pclchar->pclCI->clBI.GetName(),
													siRewardItemUnique,
													siRewardItemNum		);
				}
			}
		}
	}
	

	//���� ���� ����.
	sDBRequest_Add_Village_Score clMsg(m_siEventVillageUnique, 500);
	pclClient->SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
}

bool CMonsterAttackEvent::TimeOver(void)
{
	cltServer* pclserver = (cltServer*)pclClient;
	
	if(false == TimeInBounds(&pclserver->sTime, &m_stStartTime, &m_stEndTime))
	{
		return true;
	}
	
	return false;
}

bool CMonsterAttackEvent::MonsterAllDie(void)
{
	for( SI32 SlotCount = 0; SlotCount < MOSTER_NUM; ++SlotCount )
	{
		if(true == m_siMosterInfo[SlotCount].IsLive())
		{
			return false;
		}
	}

	return true;
}

void CMonsterAttackEvent::RandMap(void)
{
	SI32 Index[]	= {  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11 };
	SI32 MapIndex[] = { 94, 104, 105, 109, 116, 117, 118, 120, 121, 122, 170, 171 };											

	SI32 IndexNum	= sizeof(Index)/sizeof(Index[0]);
	SI32 MapNum		= sizeof(MapIndex)/sizeof(MapIndex[0]);

	if(IndexNum != MapNum)
	{
#ifdef _DEBUG
		MessageBox(NULL, "���� ���� �ߵ��ϴµ� �� ������ �޶�.", "���� ������ �޶�.", 0);
#endif
		return;
	}



	SI32 RandIndex = 0;

	// 12���� 
	for(SI32 Count = 0; Count < 10; ++Count) 
	{
		for(SI32 Count = 0; Count < MOSTER_NUM; ++Count) 
		{
			RandIndex = rand()%IndexNum;
			if(Count == RandIndex)
				continue;

			Index[Count] ^= Index[RandIndex] ^= Index[Count] ^= Index[RandIndex];
		}
	}
	

	SI32 MapRandIndex = 0;
	for( SI32 Count = 0; Count < MOSTER_NUM; ++Count )
	{
		MapRandIndex = MapIndex[Index[Count]];
		
		m_siMosterInfo[Count].SetMapIndex(MapRandIndex);
	}
}

void CMonsterAttackEvent::SetMonsterKind(void)
{
	// ���� ����.
	m_siMosterInfo[0].Live(pclClient->GetUniqueFromHash(TEXT("KIND_GIRAFFE_2")));
	m_siMosterInfo[1].Live(pclClient->GetUniqueFromHash(TEXT("KIND_MOWINGSNOWMAN")));
	m_siMosterInfo[2].Live(pclClient->GetUniqueFromHash(TEXT("KIND_EVILPIG")));
	m_siMosterInfo[3].Live(pclClient->GetUniqueFromHash(TEXT("KIND_HUNGRYGOBLIN")));
	m_siMosterInfo[4].Live(pclClient->GetUniqueFromHash(TEXT("KIND_SKULLBAT")));
	m_siMosterInfo[5].Live(pclClient->GetUniqueFromHash(TEXT("KIND_CYCLOPS")));
	m_siMosterInfo[6].Live(pclClient->GetUniqueFromHash(TEXT("KIND_PAPAGOBLIN_2")));   
}

void CMonsterAttackEvent::SendMsg(SI32 _para1, SI32 _para2)
{
	if(0 >= m_siEventVillageUnique)
		return;

	cltServer* pclserver = (cltServer*)pclClient;

	//���� �������� �޽����� ������.
	cltCharServer* pclchar = NULL;
	for( SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount )
	{
		if(false == pclClient->pclCM->IsValidID(UserCount))
			continue;

		pclchar = (cltCharServer*)pclClient->pclCM->CR[UserCount];
		if(NULL == pclchar) continue;

		// ���� ���� �̶�� �������� �ش�.
		if( m_siEventVillageUnique == (SI16)pclchar->pclCI->clBI.siHomeVillage )			
		{
			pclserver->SendServerResponseMsg(0, SRVAL_MONSTER_ATTACK_EVENT,  _para1, _para2, pclchar->GetCharUnique());		

			// �����Ѵٰ� ���� ��������ֱ� ���� �ڵ�
			cltMsg clMsg(GAMEMSG_RESPONSE_MONSTER_ATTACK_START, sizeof(m_siEventVillageUnique), (BYTE*)&m_siEventVillageUnique);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}
bool CMonsterAttackEvent::NotifyTime(void)
{
	cltServer* pclserver = (cltServer*)pclClient;
	
	static SYSTEMTIME PrevTime = pclserver->sTime;
		   SYSTEMTIME NextTime;	
	
    TimeAddMinute(&PrevTime, 1, &NextTime);	

	if(false == TimeInBounds(&pclserver->sTime, &PrevTime, &NextTime))
	{
		PrevTime = pclserver->sTime;
		return true;
	}

	return false;	
}

void CMonsterAttackEvent::RemainTime(void)
{
	DWORD dwTickCount	  = GetTickCount();
	DWORD dwTime		  = dwTickCount - m_dwStartTickCount;
	DWORD SecondTimeCount = 0;
	if(dwTime > 1000)
	{
		m_dwStartTickCount = dwTickCount;

		SecondTimeCount = (dwTime / 1000);

		m_dwRemainSecondTime -= SecondTimeCount;
	}
}

void CMonsterAttackEvent::Action(void)
{
	if(true == IsEvent())
	{
		if(true == TimeOver())	
		{
			EndEvent();
		}
		
		RemainTime();

		if(true == NotifyTime())
		{
			// â ���� ������.
			SendMsg(MONSTER_ATTACK_EVENT_START);
			SendMsg(MONSTER_ATTACK_EVENT_REMAIN_TIME, m_dwRemainSecondTime);

			for( SI32 SlotCount = 0; SlotCount < MOSTER_NUM; ++SlotCount )
			{
				if(false == m_siMosterInfo[SlotCount].IsLive())
				{
					// ���� �ִ� ������.
					SendMsg(MONSTER_ATTACK_EVENT_MONSTER_DIE, SlotCount);
				}
			}
		}
	}
}

void CMonsterAttackEvent::MonsterAttack_EventCount_Increase()
{
	//++m_siMonsterAttackEventCount;
	if ( MAX_VILLAGE_NUMBER <= m_siEventVillageUnique || 0 > m_siEventVillageUnique ) return;
	m_arEventCount_EachVillage[m_siEventVillageUnique] = m_arEventCount_EachVillage[m_siEventVillageUnique] + 1;
}

void CMonsterAttackEvent::MonsterAttack_EventCount_Reset()
{
	//m_siMonsterAttackEventCount = 0;
	m_arEventCount_EachVillage.ZeroMem();
}

SI16 CMonsterAttackEvent::MonsterAttack_EventCount_Get()
{
	//return m_siMonsterAttackEventCount;
	if ( MAX_VILLAGE_NUMBER <= m_siEventVillageUnique || 0 > m_siEventVillageUnique ) return 0;
	else return m_arEventCount_EachVillage[m_siEventVillageUnique];
}










