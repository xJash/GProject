#include "Char/CharManager/CharManager.h"
#include "ServerEvent_Manager.h"
#include "MsgType-System.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../DBManager/GameDBManager_World/DBMsg-item.h"

extern cltCommonLogic* pclClient;



CNServerEvent_Manager::CNServerEvent_Manager(void)
{
	m_siBonusBufType				= 0;							
	m_siMsgFlag						= 0;
	m_ServerEventBonusMap.ZeroMem();
	m_InstanceMapDailyOpenCount		= 0;				
	m_BackUpDailyServerUniqueRank.ZeroMem();
	ZeroMemory( &m_clServerEvent_Rank_Record, sizeof(m_clServerEvent_Rank_Record));
	m_siServerEventState			= SERVER_EVENT_STATE_READY;
	m_siGoonzuDayDayEventScore		= 0;


	m_siGoonzuDayDayEventScore		= 0;
}

CNServerEvent_Manager::~CNServerEvent_Manager()
{

}

void CNServerEvent_Manager::Init(void)
{
	for(SI32 Count = 0; Count < SERVER_EVENT_BONUS_MAP; ++Count)
	{
		m_ServerEventBonusMap[Count] = SERVER_EVENT_BONUS_MAP_START_INDEX + Count;
	}
}

void CNServerEvent_Manager::Clear(void)
{
	ZeroMemory(this, sizeof(*this));
}

void CNServerEvent_Manager::Destroy(void)
{

}


void CNServerEvent_Manager::InstanceMapClear(void)
{
	SendDBMsgServerDailyScoreAdd();	// �Ϸ� ���� ������ ���� ����.
	InstanceMapClearReward();		// �δ� ���� �� ����.
}

void CNServerEvent_Manager::InstanceMapClearReward(void)
{
	SI32 RewardItemUnique = 0;
	if( 7 == GetInstanceMapStepCount(0) &&
		6 == GetInstanceMapStepCount(1) &&
		8 == GetInstanceMapStepCount(2) &&
		9 == GetInstanceMapStepCount(3)		)		
	{
		//return _7_6_8_9;
		
		RewardItemUnique = ITEMUNIQUE(3897);
	}
	else if( 11 == GetInstanceMapStepCount(0) &&
			 12 == GetInstanceMapStepCount(1) &&
			 13 == GetInstanceMapStepCount(2) &&
			 14 == GetInstanceMapStepCount(3)		)
	{
		//return _11_12_13_14;
		RewardItemUnique = ITEMUNIQUE(2765);
	}
	else if(  7 == GetInstanceMapStepCount(0) &&
			 10 == GetInstanceMapStepCount(1) &&
			  7 == GetInstanceMapStepCount(2) &&
			 10 == GetInstanceMapStepCount(3)		)
	{
		//return _7_10_7_10;
		RewardItemUnique = ITEMUNIQUE(2740);
	}
	else if( 6 == GetInstanceMapStepCount(0) &&
			 8 == GetInstanceMapStepCount(1) &&
			 2 == GetInstanceMapStepCount(2) &&
			 9 == GetInstanceMapStepCount(3)		)
	{
		//return _6_8_2_9;
		if( pclClient->IsWhereServiceArea(ConstServiceArea_Korea) )		
			RewardItemUnique = ITEMUNIQUE(2770);
		else
			RewardItemUnique = ITEMUNIQUE(3911);
	}
	else if(  9 == GetInstanceMapStepCount(0) &&
			 10 == GetInstanceMapStepCount(1) &&
			  9 == GetInstanceMapStepCount(2) &&
			 10 == GetInstanceMapStepCount(3)		)
	{
		//return _9_10_9_10;
		RewardItemUnique = ITEMUNIQUE(7860);
	}

	if(60 <= GetInstanceMapStepCountSum()) 
	{
		//return COUNT_60;
		RewardItemUnique = ITEMUNIQUE(2756);
	}
	if(0 < RewardItemUnique)
	{		
		pclClient->pclCM->GiveItem(0, RewardItemUnique, 1, GIVEITEM_MODE_ALL, INPUTITEMPERSON_OPTION_SERVER_EVENT, 0, 0, 20);

		SI16 Data[4] = { GetInstanceMapStepCount(0),
						 GetInstanceMapStepCount(1),
						 GetInstanceMapStepCount(2),
						 GetInstanceMapStepCount(3)		};

		cltGameMsgResponse_Server_Event_InstanceMap_Bonus_Figure cltInfo(Data);
		cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_INSTANCEMAP_BONUS_FIGURE, sizeof(cltInfo), (BYTE*)&cltInfo);
		pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2008. 7. 7] ���� �̺�Ʈ
			// param1 = �δ� 1�� �ܰ� ��.
			// param2 = �δ� 2�� �ܰ� ��.
			// param3 = �δ� 3�� �ܰ� ��.
			// param4 = �δ� 4�� �ܰ� ��.
			// param5 = ������ ����ũ.
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_DAILY_BONUS_ITEM, 
											0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											GetInstanceMapStepCount(0), GetInstanceMapStepCount(1), 
											GetInstanceMapStepCount(2), GetInstanceMapStepCount(3),
											RewardItemUnique, NULL, NULL);
		}
	}

	pclClient->pclLog->FilePrint( "config\\ServerEvent.log" , "[IndunBonusItem]\t %d \t IndunCount:%d, %d, %d, %d",  
																RewardItemUnique, 
																GetInstanceMapStepCount(0), GetInstanceMapStepCount(1), 
																GetInstanceMapStepCount(2), GetInstanceMapStepCount(3));

	// ���� ����.
	m_clInstanceMapInfo.Clear();
}

void CNServerEvent_Manager::SendDBMsgServerEventEnd(void)
{
	// ���� �̺�Ʈ�� ���õ� ���� ��û.
	sDBRequest_Server_Event_Rank_Info clMsg(pclClient->siServerUnique, SERVER_EVENT_REASON_END);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void CNServerEvent_Manager::SendDBMsgServerEventDaily(void)
{
	// ���� �̺�Ʈ�� ���õ� ���� ��û.
	sDBRequest_Server_Event_Rank_Info clMsg(pclClient->siServerUnique, SERVER_EVENT_REASON_DAILRY);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void CNServerEvent_Manager::SendDBMsgServerEventRequest(void)
{
	// ���� �̺�Ʈ�� ���õ� ���� ��û.
	sDBRequest_Server_Event_Rank_Info clMsg(pclClient->siServerUnique, SERVER_EVENT_REASON_INFO_REQUEST);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void CNServerEvent_Manager::SendDBMsgServerRankRequest(void)
{
	sDBRequest_Server_Event_Server_Info clMsg(pclClient->siServerUnique);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void CNServerEvent_Manager::SendDBMsgPersonalRankRequest(void)
{
	sDBRequest_Server_Event_Personal_Info clMsg(pclClient->siServerUnique);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void CNServerEvent_Manager::SendDBMsgServerScoreAdd(void)
{
	SI32 MyServerDailyRank = -1;
	for(SI32 Count = 0; Count < SERVER_MAX_NUM; ++Count)
	{
		if(pclClient->siServerUnique == GetBackUpDailyServerUniqueRank(Count))
		{
			MyServerDailyRank = Count;
		}
	}
				
	SI64 siServerScoreLast   = 0;	// ������ �߰��� ���� ����.
	//SI32 ServerScoreMultiply = 1;	// �������� �߰��� Ư�� ������ �����ϸ� ����� ���� ���� �������� ��.
	
	// ������ ������ ������ ������ 0��.
	//if(-1 == MyServerDailyRank)
	//{
	//	siServerScoreLast = 0;
	//}
	//else
	//{
	//	ServerScoreMultiply = SERVER_MAX_NUM - MyServerDailyRank;
	//	siServerScoreLast   = 5 * ServerScoreMultiply;
	//	
	//	// ������ ������ �־ �Ϸ� ���� ������ 0���� ���� ������ 0�� �̴�.
	//	if(0 >= m_clServerEvent_Rank_Record.GetServerDailyRankInfo(MyServerDailyRank)->GetScore())
	//		siServerScoreLast = 0;
	//}

	// ���� ���� �̺�Ʈ�� �ٲ�鼭 ���� ������ �־�����.
	siServerScoreLast = m_clServerEvent_Rank_Record.GetServerDailyRankInfo(MyServerDailyRank)->GetScore();

	sDBRequest_Server_Event_Server_Score_Add clMsg(pclClient->siServerUnique, GetInstanceMapDailyOpenCount(), siServerScoreLast);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� �̺�Ʈ ����.
		// param1 = �Ϸ� ���� ��.
		// param2 = ���� �� ������ �߰� ����.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_TOTAL_SCORE, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										GetInstanceMapDailyOpenCount(), siServerScoreLast, 0, 0, 0, NULL, NULL);
	}
	pclClient->pclLog->FilePrint( "config\\ServerEvent.log" , "[OndDayOpenCount]\t %d, \t [AllScore]\t %I64d",
																GetInstanceMapDailyOpenCount(), siServerScoreLast);

	// �δ� �Ϸ� ���� Ƚ��.
	m_InstanceMapDailyOpenCount = 0;
}

void CNServerEvent_Manager::SendDBMsgServerDailyScoreAdd(void)
{
	//SI32 MyServerRank = -1;
	//for(SI32 Count = 0; Count < SERVER_MAX_NUM; ++Count)
	//{
	//	if(pclClient->siServerUnique == m_clServerEvent_Rank_Record.GetServerRankInfo(Count)->GetServerUnique())
	//	{
	//		MyServerRank = Count;
	//	}
	//}

	//if(-1 == MyServerRank)
	//	MyServerRank = 0;	// �ڽ��� ������ ����� ������ �����ϰ� ���꿡 1�� ���ϱ� ����.

	SI64 siServerScoreLast   = 0;	// ������ �߰��� ���� ����.
	//SI32 ServerScoreMultiply = 1;	// �������� ���꿡 ���(�δ� �ܰ谡 ��� ������ �������� ���̰� ����) 
	//if( GetInstanceMapStepCount(0) == GetInstanceMapStepCount(1) ==	
	//	GetInstanceMapStepCount(2) == GetInstanceMapStepCount(3)	)
	//{
	//	ServerScoreMultiply = (MyServerRank % SERVER_MAX_NUM) + 1;
	//}

	// �δ� ���� �� ������ ������ ���ǿ� �°� ����.
	//siServerScoreLast = GetInstanceMapScore() * ServerScoreMultiply;
	
	//sDBRequest_Server_Event_Server_Daily_Score_Add clMsg(pclClient->siServerUnique, siServerScoreLast, m_InstanceMapDailyOpenCount, SERVER_EVENT_REASON_INSTANCE_MAP_CLEAR);
	//((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );


	//***********************************************************************************************
	//	
	//	���� ���� �̺�Ʈ�� ����� ��
	//
	//***********************************************************************************************

	siServerScoreLast = GetInstanceMapScore();	// ������ ����.

	// �δ� ���� �� ������ ������ ���ϱ�.
	sDBRequest_Server_Event_Server_Daily_Score_Add clMsg(pclClient->siServerUnique, GetInstanceMapScore(), m_InstanceMapDailyOpenCount, SERVER_EVENT_REASON_INSTANCE_MAP_CLEAR);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

	// �δ� ���� �� ������ ������ �������Ƿ� 0���� �ʱ�ȭ ����.
	SetInstanceMapScore( 0 );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� �̺�Ʈ ����.
		// param1 = �δ� 1�� �ܰ� ��.
		// param2 = �δ� 2�� �ܰ� ��.
		// param3 = �δ� 3�� �ܰ� ��.
		// param4 = �δ� 4�� �ܰ� ��.
		// param5 = �Ϸ� ���� ������ �߰� ����.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_DAILY_SCORE, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										GetInstanceMapStepCount(0), GetInstanceMapStepCount(1), 
										GetInstanceMapStepCount(2), GetInstanceMapStepCount(3), 
										siServerScoreLast, NULL, NULL);
	}

	pclClient->pclLog->FilePrint( "config\\ServerEvent.log" , "[OneDayScore]\t %I64d \t IndunCount:%d, %d, %d, %d \t ServerUnique:%d",  
																siServerScoreLast, 
																GetInstanceMapStepCount(0), GetInstanceMapStepCount(1), 
																GetInstanceMapStepCount(2), GetInstanceMapStepCount(3),
																pclClient->siServerUnique );
}

void CNServerEvent_Manager::ManagerExcute( SI32 siCommandType )
{
	if ( (SERVER_EVENT_COMMANDTYPE_NONE >= siCommandType) || (SERVER_EVENT_COMMANDTYPE_END <= siCommandType) )
	{
		return;
	}

	switch ( siCommandType ) 
	{
		case SERVER_EVENT_COMMANDTYPE_QUEST_START:
			{
			}
			break;

		case SERVER_EVENT_COMMANDTYPE_QUEST_END:
			{
			}
			break;

		case SERVER_EVENT_COMMANDTYPE_INDUN_START:
			{
				// �δ� �������� ���� Ƚ�� ����.
				AddInstanceMapDailyOpenCount(1);

				SetServerEventState( SERVER_EVENT_STATE_START_INDUN );
			}
			break;

		case SERVER_EVENT_COMMANDTYPE_INDUN_END:
			{
				// �δ� ����.
				InstanceMapClear();

				SetServerEventState( SERVER_EVENT_STATE_END_INDUN );
			}
			break;
	}
}

bool CNServerEvent_Manager::IsMyServerRankBest(void)
{
	// 1�� ������ ����ũ�� �� �������.
	if(pclClient->siServerUnique == GetServerUnique(0))
		return true;
	
	return false;
}

bool CNServerEvent_Manager::IsMyServerRankBest2(void)
{
	// 2�� ������ ����ũ�� �� �������.
	if(pclClient->siServerUnique == GetServerUnique(1))
		return true;

	return false;
}

void CNServerEvent_Manager::SetBonusBufType(SI16 _siBonusBufType)
{
	if(SERVER_EVENT_BUF_NO > _siBonusBufType || SERVER_EVENT_BUF_NUM <= _siBonusBufType)
		return;
	
	m_siBonusBufType = _siBonusBufType;
}

SI16 CNServerEvent_Manager::GetBonusBufType(void)
{
	return m_siBonusBufType;
}

void CNServerEvent_Manager::MyServerDailyRankBestBuf(void)
{
	// ���� ����Ÿ�� ����.
	m_siBonusBufType = ( rand() % SERVER_EVENT_BUF_ETC ) + 1;
		
	sDBRequest_Server_Event_Server_Buf_Kind clMsg(pclClient->siServerUnique, m_siBonusBufType);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}
void CNServerEvent_Manager::MyServerDailyRankBestBufNo(void)
{
	m_siBonusBufType = SERVER_EVENT_BUF_NO;

	sDBRequest_Server_Event_Server_Buf_Kind clMsg(pclClient->siServerUnique, m_siBonusBufType);
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

SI32 CNServerEvent_Manager::GetBonusMapIndex(SI32 _siLevel)
{
	if(_siLevel < 20)
	{
		return SERVER_EVENT_BONUS_MAP_START_INDEX;
	}	
	else if(_siLevel < 40)
	{
		return SERVER_EVENT_BONUS_MAP_START_INDEX + 1;
	}
	else if(_siLevel < 60)
	{
		return SERVER_EVENT_BONUS_MAP_START_INDEX + 2;
	}
	else if(_siLevel < 80)
	{
		return SERVER_EVENT_BONUS_MAP_START_INDEX + 3;
	}
	else if(_siLevel <= 100)
	{
		return SERVER_EVENT_BONUS_MAP_START_INDEX + 4;
	}

	// �ƹ��͵� �ƴϸ� ������ ������ ���� ���� �δ� ����.(�ü��� �ֳ�? ���� Ǯ����...����)
	return SERVER_EVENT_BONUS_MAP_START_INDEX + 4;
}

bool CNServerEvent_Manager::IsEventMap(SI32 _siMapIndex)
{
	if(SERVER_EVENT_BONUS_MAP_START_INDEX <= _siMapIndex &&
	   SERVER_EVENT_BONUS_MAP_START_INDEX + SERVER_EVENT_BONUS_MAP > _siMapIndex)
	   return true;

	return false;
}


CNServerEvent_Rank_Record* CNServerEvent_Manager::GetServerEventRankRecord(void)
{
	return &m_clServerEvent_Rank_Record;
}

CNServerEvent_Quest* CNServerEvent_Manager::GetServerEvent_Quest(void)
{
	return &m_clServerEvent_Quest;
}

CNInstanceMapInfo* CNServerEvent_Manager::GetInstanceMapInfo(void)
{
	return &m_clInstanceMapInfo;
}

void CNServerEvent_Manager::SetServerEventRankRecord(CNServerEvent_Rank_Record* _pRankInfo)
{
	SAFE_POINTER(_pRankInfo)

	memcpy(&m_clServerEvent_Rank_Record, _pRankInfo, sizeof(m_clServerEvent_Rank_Record));
}

void CNServerEvent_Manager::SetServerRank(CNServerRankInfo* _pRankInfo)
{
	SAFE_POINTER(_pRankInfo)

	memcpy(m_clServerEvent_Rank_Record.GetServerRankInfo(0), _pRankInfo, sizeof(CNServerRankInfo) * SERVER_MAX_NUM);
}

void CNServerEvent_Manager::SetServerDailyRank(CNServerDailyRankInfo* _pRankInfo)
{
	SAFE_POINTER(_pRankInfo)

	memcpy(m_clServerEvent_Rank_Record.GetServerDailyRankInfo(0), _pRankInfo, sizeof(CNServerDailyRankInfo) * SERVER_MAX_NUM);
}

void CNServerEvent_Manager::SetPersonalRank(CNPersonalRankInfo* _pRankInfo)
{
	SAFE_POINTER(_pRankInfo)

	memcpy(m_clServerEvent_Rank_Record.GetPersonalRankInfo(0), _pRankInfo, sizeof(CNPersonalRankInfo) * USER_MAX_NUM);
}

void CNServerEvent_Manager::SetServerUnique(SI32 _siServerRank, SI16 _siServerUnique) 
{
	m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->SetScore(_siServerUnique);
}
SI16 CNServerEvent_Manager::GetServerUnique(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->GetServerUnique();
}

// �������� ó��.
void CNServerEvent_Manager::SetServerScore(SI32 _siServerRank, SI64 _siServerScore)
{
	m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->SetScore(_siServerScore);
}	
SI64 CNServerEvent_Manager::GetServerScore(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->GetScore();
}

// ����� ���� ���� ó��.
void CNServerEvent_Manager::SetServerHuntingGroundCount(SI32 _siServerRank, SI16 _siServerHuntingGroundCount)
{
	m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->SetHuntingGroundCount(_siServerHuntingGroundCount);
}
SI16 CNServerEvent_Manager::GetServerHuntingGroundCount(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->GetHuntingGroundCount();
}

// �����̸� ó��.
void CNServerEvent_Manager::SetServerName(SI32 _siServerRank, TCHAR* _siServerName)
{
	m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->SetServerName(_siServerName);
}
TCHAR* CNServerEvent_Manager::GetServerName(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerRankInfo(_siServerRank)->GetServerName();
}

void CNServerEvent_Manager::SetServerUniqueDaily(SI32 _siServerRank, SI16 _siServerUnique)
{
	m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->SetScore(_siServerUnique);
}
SI16 CNServerEvent_Manager::GetServerUniqueDaily(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->GetServerUnique();
}

// �������� ó��.
void CNServerEvent_Manager::SetServerDailyScore(SI32 _siServerRank, SI64 _siServerScore)
{
	m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->SetScore(_siServerScore);
}
SI64 CNServerEvent_Manager::GetServerDailyScore(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->GetScore();
}

// ����� ���� ���� ó��.
void CNServerEvent_Manager::SetServerDailyHuntingGroundCount(SI32 _siServerRank, SI16 _siServerHuntingGroundCount)
{
	m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->SetHuntingGroundCount(_siServerHuntingGroundCount);
}
SI16 CNServerEvent_Manager::GetServerDailyHuntingGroundCount(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->GetHuntingGroundCount();
}

// �����̸� ó��.
void CNServerEvent_Manager::SetServerDailyName(SI32 _siServerRank, TCHAR* _siServerName)
{
	m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->SetServerName(_siServerName);
}
TCHAR* CNServerEvent_Manager::GetServerDailyName(SI32 _siServerRank)
{
	return m_clServerEvent_Rank_Record.GetServerDailyRankInfo(_siServerRank)->GetServerName();
}



// �������� ó��. 
void CNServerEvent_Manager::SetPersonalScore(SI32 _siPersonalRank, SI64 _siPersonalScore)
{
	return m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->SetScore(_siPersonalScore);
}
SI64 CNServerEvent_Manager::GetPersonalScore(SI32 _siPersonalRank)
{
	return m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->GetScore();
}

// ���η��� ó��.
void CNServerEvent_Manager::SetPersonalLevel(SI32 _siPersonalRank, SI16 _siPersonalLevel)
{
	return m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->SetLevel(_siPersonalLevel);
}
SI16 CNServerEvent_Manager::GetPersonalLevel(SI32 _siPersonalRank)
{
	return m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->GetLevel();
}

// ���� �̸�.
void CNServerEvent_Manager::SetPersonalName(SI32 _siPersonalRank, TCHAR* _siPersonalName)
{
	m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->SetPersonalName(_siPersonalName);
}
TCHAR* CNServerEvent_Manager::GetPersonalName(SI32 _siPersonalRank)
{
	return m_clServerEvent_Rank_Record.GetPersonalRankInfo(_siPersonalRank)->GetPersonalName();
}


void CNServerEvent_Manager::SetInstanceMapScore(SI64 _siScore)
{
	m_clInstanceMapInfo.SetScore(_siScore);
}

SI64 CNServerEvent_Manager::GetInstanceMapScore(void)
{
	return m_clInstanceMapInfo.GetScore();
}
void CNServerEvent_Manager::AddInstanceMapScore(SI64 _siAddScore)
{
	m_clInstanceMapInfo.AddScore(_siAddScore);
}

void CNServerEvent_Manager::SetInstanceMapStepCount(SI16 _Index, SI16 _siMapStepCount)
{
	m_clInstanceMapInfo.SetMapStepCount(_Index, _siMapStepCount);
}

SI16 CNServerEvent_Manager::GetInstanceMapStepCount(SI16 _Index)
{
	return m_clInstanceMapInfo.GetMapStepCount(_Index);
}

void CNServerEvent_Manager::AddInstanceMapStepCount(SI16 _Index, SI16 _siOpenCount)
{
	m_clInstanceMapInfo.AddMapStepCount(_Index, _siOpenCount);
}

SI16 CNServerEvent_Manager::GetInstanceMapStepCountSum(void)
{
	return m_clInstanceMapInfo.GetMapStepCountSum();
}

void CNServerEvent_Manager::SetInstanceMapDailyOpenCount(SI32 _siOpenCount)
{
	m_InstanceMapDailyOpenCount = _siOpenCount;
}
SI32 CNServerEvent_Manager::GetInstanceMapDailyOpenCount(void)
{
	return m_InstanceMapDailyOpenCount;
}
void CNServerEvent_Manager::AddInstanceMapDailyOpenCount(SI32 _siOpenCount)
{ 
	m_InstanceMapDailyOpenCount += _siOpenCount;
}

void CNServerEvent_Manager::SetInstanceMapClear(SI16 _Index, bool _bMapClear)
{
	m_clInstanceMapInfo.SetMapClear(_Index, _bMapClear);
}
bool CNServerEvent_Manager::GetInstanceMapClear(SI16 _Index)
{
	return m_clInstanceMapInfo.GetMapClear(_Index);
}
bool CNServerEvent_Manager::IsAllInstanceMapClear(void)
{
	return m_clInstanceMapInfo.IsAllMapClear();
}

void CNServerEvent_Manager::BackUpDailyServerUniqueRankClear(void)
{
#ifdef _SAFE_MEMORY
	m_BackUpDailyServerUniqueRank.ZeroMem();
#else
	ZeroMemory(m_BackUpDailyServerUniqueRank, sizeof(m_BackUpDailyServerUniqueRank));
#endif
}
void CNServerEvent_Manager::SetBackUpDailyServerUniqueRank(void)
{
	for(SI32 Count = 0; Count < SERVER_MAX_NUM; ++Count)
	{
		m_BackUpDailyServerUniqueRank[Count] = m_clServerEvent_Rank_Record.GetServerDailyRankInfo(Count)->GetServerUnique();
	}
}
SI16 CNServerEvent_Manager::GetBackUpDailyServerUniqueRank(SI16 _Index)
{
	return m_BackUpDailyServerUniqueRank[_Index];
}

void CNServerEvent_Manager::SetServerEventState( SI32 _siServerEventState )
{
	if ( (_siServerEventState <= SERVER_EVENT_STATE_NONE) || (_siServerEventState >= SERVER_EVENT_STATE_END) )
	{
		return;
	}

	m_siServerEventState = _siServerEventState;
}
void CNServerEvent_Manager::DeleteGate( void )
{
	// �������ִ� ����Ʈ�� ����.
	m_clInstanceMapInfo.DeleteGate();
}

void CNServerEvent_Manager::ServerEventStateReady( void )
{
	m_siServerEventState = SERVER_EVENT_STATE_READY;

	m_clServerEvent_Quest.Init();

	// �������ִ� ����Ʈ�� ����.
	m_clInstanceMapInfo.DeleteGate();
	m_clInstanceMapInfo.Clear();
}

SI32 CNServerEvent_Manager::GetServerEventState( void )
{
	return m_siServerEventState;
}

void CNServerEvent_Manager::ServerEventStateProcess( void )
{
	// �����´� ó���ϱ� �ʰ� �׳� ����
	if ( SERVER_EVENT_STATE_WAIT  ==  m_siServerEventState )
	{
		return;
	}

	switch ( m_siServerEventState )
	{
		case SERVER_EVENT_STATE_READY:
			{
				m_clServerEvent_Quest.SendMessageToDB( SERVEREVENT_QUEST_PACKETTYPE_GET_QUESTINFO );
				SetServerEventState( SERVER_EVENT_STATE_WAIT );
			}
			break;

		case SERVER_EVENT_STATE_START_QUEST:
			{
				cltServer* pclserver = (cltServer*)pclClient;
				if ( NULL == pclserver )
				{
					return;
				}

				if ( pclserver->pclEventTimeManager->InEventTime(TEXT( "GoonzuDay_Week" ), &pclserver->sTime) )
				{
					m_clServerEvent_Quest.StartServerEventQuest();
				}
				else
				{
					SetServerEventState( SERVER_EVENT_STATE_WAIT );
				}
			}
			break;

		case SERVER_EVENT_STATE_GOING_QUEST:
			{
				m_clServerEvent_Quest.Action();
			}
			break;

		case SERVER_EVENT_STATE_END_QUEST:
			{
			}
			break;
			
		case SERVER_EVENT_STATE_START_INDUN:
			{
				m_clInstanceMapInfo.OpenTheGate();
			}
			break;

		case SERVER_EVENT_STATE_GOING_INDUN:
			{
				m_clInstanceMapInfo.Action();
			}
			break;

		case SERVER_EVENT_STATE_END_INDUN:
			{
				m_clInstanceMapInfo.CloseTheGate();
				m_clInstanceMapInfo.LeaveLobbyInUser();
			}
			break;

	}

}

//******************************************************************************************
//
// ���� �̺�Ʈ�� ���� ���� �̺�Ʈ�� ����Ǿ� ���Ǵ� �Լ�. 
// * ���� �̺�Ʈ�� �����.
//
//******************************************************************************************
bool CNServerEvent_Manager::IsGoonzuDayEventSuccess( void )
{

	return true;
}


void CNServerEvent_Manager::ActionGoonzuDayReward(void)
{
	// ���������� ����
	if ( GAMEMODE_SERVER != pclClient->GameMode )	return;

	// [����] ���� �̺�Ʈ���� ������ �Ϻ��ϰ� �����ϱ� ���� �̰����� �ִ´�
	ServerEventStateProcess();

	// 5�� ���� DB�� ���� �̺�Ʈ ���� ��û.
	static DWORD StartTickCount = GetTickCount();
	if(20000 < GetTickCount() - StartTickCount)
	{
		StartTickCount = GetTickCount();

		SendDBMsgServerEventRequest();
	}
}

void CNServerEvent_Manager::ActionGoonzuDay(void)
{
	// ���������� ����
	if ( GAMEMODE_SERVER != pclClient->GameMode )	return;

	ServerEventStateProcess();

	cltServer* pclServer = (cltServer*)pclClient;

	// 5�� ���� DB�� ���� �̺�Ʈ ���� ��û.
	static DWORD StartTickCount = GetTickCount();
	if(20000 < GetTickCount() - StartTickCount)
	{
		StartTickCount = GetTickCount();

		SendDBMsgServerEventRequest();

		SendDBMsgServerDailyScoreAdd();	// �Ϸ� ���� ������ ���� ����.
	}
}