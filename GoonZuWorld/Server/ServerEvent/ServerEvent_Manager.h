#ifndef _SERVER_EVENT_MANAGER_H_
#define _SERVER_EVENT_MANAGER_H_

#pragma once

#include "Directives.h"
#include "CommonLogic.h"
#include "ServerEvent_Rank_Record.h"
#include "ServerEvent-Quest.h"
#include "ServerEvent-InstanceMapInfo.h"

#define SAFE_POINTER(p)	if(NULL == p) return;

#define SERVER_EVENT_BONUS_MAP				  5
#define SERVER_EVENT_BONUS_MAP_START_INDEX	361

enum SERVER_EVENT_COMMANDTYPE
{
	SERVER_EVENT_COMMANDTYPE_NONE = 0,

	SERVER_EVENT_COMMANDTYPE_QUEST_START,
	SERVER_EVENT_COMMANDTYPE_QUEST_END,
	SERVER_EVENT_COMMANDTYPE_INDUN_START,
	SERVER_EVENT_COMMANDTYPE_INDUN_END,

	//-----------------------------------------------------------------------------------
	SERVER_EVENT_COMMANDTYPE_END
};

// ���� �̺�Ʈ ����
enum SERVER_EVENT_STATE
{
	SERVER_EVENT_STATE_NONE = 0,

	SERVER_EVENT_STATE_READY,		// ���� �������

	SERVER_EVENT_STATE_START_QUEST,	// ����Ʈ ����
	SERVER_EVENT_STATE_GOING_QUEST,	// ����Ʈ ������
	SERVER_EVENT_STATE_END_QUEST,	// ����Ʈ ����

	SERVER_EVENT_STATE_START_INDUN,	// �δ� ����
	SERVER_EVENT_STATE_GOING_INDUN,	// �δ� ������
	SERVER_EVENT_STATE_END_INDUN,	// �δ� ����

	SERVER_EVENT_STATE_WAIT,		// �� ���°� ����Ʈ/�δ� �� ������ ���� �ʴ´�

	//-----------------------------------------------------------------------------------
	SERVER_EVENT_STATE_END
};


class CNServerEvent_Manager
{
public:
	enum
	{
		 SERVER_EVENT_BUF_NO					// ���� ����.
		,SERVER_EVENT_BUF_ATTACK_EXP_150		// ���� ����ġ 150%
		,SERVER_EVENT_BUF_MAKE_EXP_150			// ���� ����ġ 150%
		,SERVER_EVENT_BUF_ATTACK_EXP_200		// ���� ����ġ 200%
		,SERVER_EVENT_BUF_MAKE_EXP_200			// ���� ����ġ 200%	
		,SERVER_EVENT_BUF_ETC					// ��ȹ, ����, ä��
		,SERVER_EVENT_BUF_NUM					// ���� ������ ����.					
	};

	enum
	{
		 MSG_FLAG_DAILY
		,MSG_FLAG_TOTAL_SCORE_ADD
		,MSG_FLAG_SERVER_RANK_CLEAR
	};


public:
	CNServerEvent_Manager(void);
	~CNServerEvent_Manager();

	void			Init(void);
	void			Clear(void);
	void			Destroy(void);
			
	void			SendDBMsgServerEventEnd(void);								// �̺�Ʈ ����� ������� ��û.(��ü ��ŷ ���� ��û)
	void			SendDBMsgServerEventDaily(void);							// �Ϸ� ���� ������ ��û.(��ü ��ŷ ���� ��û)
	void			SendDBMsgServerEventRequest(void);							// ���� �̺�Ʈ�� ���õ� ��� ���� ��û.(��ü ��ŷ ���� ��û)
	void			SendDBMsgServerRankRequest(void);							// ���� �̺�Ʈ�� ���õ� ������ŷ ���� ��û.
	void			SendDBMsgPersonalRankRequest(void);							// ���� �̺�Ʈ�� ���õ� ���η�ŷ ���� ��û.
	void			SendDBMsgServerScoreAdd(void);								// ���� �̺�Ʈ�� �������� ������Ʈ.
	void			SendDBMsgServerDailyScoreAdd(void);							// ���� �̺�Ʈ�� �Ϸ� �������� ������Ʈ.

	void			ManagerExcute( SI32 siCommandType );

	void			InstanceMapClear(void);										// �δ� ���� �� ȣ��. 
	void			InstanceMapClearReward(void);								// �����(����) �̺�Ʈ ���� �� Ŭ���� Ƚ�� ���տ� ���� ����. 
	bool			IsMyServerRankBest(void);									// �� ������ ��ŷ 1���ΰ�.
	bool			IsMyServerRankBest2(void);									// �� ������ ��ŷ 2���ΰ�.
	void			SetBonusBufType(SI16 _siBonusBufType);						// 1���� �ϰ� ���ʽ� ������ ���� Ÿ�� ����. 
	SI16			GetBonusBufType(void);										// 1���� �ϰ� ���ʽ� ������ ���� Ÿ�� ���. 
	void			MyServerDailyRankBestBuf(void);								// ������ 1���� �� ȣ��.
	void			MyServerDailyRankBestBufNo(void);							// ������ 1���� �ƴ� �� ȣ��.
	SI32			GetBonusMapIndex(SI32 _Level);								// ������ ������ ���� ���ʽ� ���� �ε����� �ش�.
	bool			IsEventMap(SI32 _siMapIndex);								// �ش� ���ε����� ���� �̺�Ʈ �� 1�� ������ ���ʽ� �������� �̵��ϴ� ������ Ȯ��.

public:
	// ���� ��ŷ ����.
	void			SetServerUnique(SI32 _siServerIndex, SI16 _siServerUnique);
	SI16			GetServerUnique(SI32 _siServerIndex);
	void			SetServerScore(SI32 _siServerIndex, SI64 _siServerScore);
	SI64			GetServerScore(SI32 _siServerIndex);
	void			SetServerHuntingGroundCount(SI32 _siPersonalRank, SI16 _siServerHuntingGroundCount);
	SI16			GetServerHuntingGroundCount(SI32 _siPersonalRank);
	void			SetServerName(SI32 _siServerRank, TCHAR* _siServerName);
	TCHAR*			GetServerName(SI32 _siServerRank);

	// �Ϸ� ���� ��ŷ ����.
	void			SetServerUniqueDaily(SI32 _siServerIndex, SI16 _siServerUnique);
	SI16			GetServerUniqueDaily(SI32 _siServerIndex);
	void			SetServerDailyScore(SI32 _siServerIndex, SI64 _siServerScore);
	SI64			GetServerDailyScore(SI32 _siServerIndex);
	void			SetServerDailyHuntingGroundCount(SI32 _siPersonalRank, SI16 _siServerHuntingGroundCount);
	SI16			GetServerDailyHuntingGroundCount(SI32 _siPersonalRank);
	void			SetServerDailyName(SI32 _siServerRank, TCHAR* _siServerName);
	TCHAR*			GetServerDailyName(SI32 _siServerRank);
	

	// ���� ��ŷ ����.
	void			SetPersonalScore(SI32 _siServerRank, SI64 _siPersonalScore);
	SI64			GetPersonalScore(SI32 _siServerRank);
	void			SetPersonalLevel(SI32 _siPersonalRank, SI16 _siPersonalLevel);
	SI16			GetPersonalLevel(SI32 _siPersonalRank);
	void			SetPersonalName(SI32 _siPersonalRank, TCHAR* _siPersonalName);
	TCHAR*			GetPersonalName(SI32 _siPersonalRank);

	// �δ� ���� ����.
	void			SetInstanceMapScore(SI64 _siScore);
	SI64			GetInstanceMapScore(void);
	void			AddInstanceMapScore(SI64 _siAddScore);
	void			SetInstanceMapStepCount(SI16 _Index, SI16 _siMapStepCount);
	SI16 			GetInstanceMapStepCount(SI16 _Index);
	void			AddInstanceMapStepCount(SI16 _Index, SI16 _siMapStepCount);
	SI16 			GetInstanceMapStepCountSum(void);

	void			SetInstanceMapDailyOpenCount(SI32 _siOpenCount);
	SI32 			GetInstanceMapDailyOpenCount(void);
	void			AddInstanceMapDailyOpenCount(SI32 _siOpenCount);

	void			SetInstanceMapClear(SI16 _Index, bool _bMapClear);
	bool 			GetInstanceMapClear(SI16 _Index);
	bool			IsAllInstanceMapClear(void);

	void			BackUpDailyServerUniqueRankClear(void);
	void			SetBackUpDailyServerUniqueRank(void);
	SI16 			GetBackUpDailyServerUniqueRank(SI16 _Index);

	// ���� �̺�Ʈ ���� ����
	void			SetServerEventState( SI32 _siServerEventState );
	void			ServerEventStateReady( void );
	SI32			GetServerEventState( void );

	void			ServerEventStateProcess( void );


	// ��ŷ ���� ����.
	CNServerEvent_Rank_Record*	GetServerEventRankRecord(void);											// ����, ���� ��ü ��ŷ���� ���.
	CNServerEvent_Quest*		GetServerEvent_Quest(void);												// ���� �̺�Ʈ ����Ʈ ���.
	CNInstanceMapInfo*			GetInstanceMapInfo(void);												// ���� �̺�Ʈ �δ� ���� ���� ���.

	void						SetServerEventRankRecord(CNServerEvent_Rank_Record* _pRankInfo);		// ����, ���� ��ü ��ŷ���� ����.
	void						SetServerRank(CNServerRankInfo* _pRankInfo);							// ���� ��ŷ���� ����.
	void						SetServerDailyRank(CNServerDailyRankInfo* _pRankInfo);					// �Ϸ� ���� ��ŷ���� ����.
	void						SetPersonalRank(CNPersonalRankInfo* _pRankInfo);						// ���� ��ŷ���� ����.
	
private:
	SI16						m_siBonusBufType;														// ���ʽ� ���� Ÿ��.
	SI32						m_siMsgFlag;															// �޽��� ȣ�� ���� �÷���.
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, SERVER_EVENT_BONUS_MAP>			m_ServerEventBonusMap;
#else
	SI32						m_ServerEventBonusMap[SERVER_EVENT_BONUS_MAP];							// ���� �̺�Ʈ ���ʽ� �� �ε���.
#endif
	SI32						m_InstanceMapDailyOpenCount;											// ��Ʈ��Ʈ ���� �Ϸ� ���� Ƚ��.

	SI32						m_siServerEventState;													// ���� ���� �̺�Ʈ ����
#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, SERVER_MAX_NUM>					m_BackUpDailyServerUniqueRank;
#else
	SI16						m_BackUpDailyServerUniqueRank[SERVER_MAX_NUM];							// �Ϸ� ������ ���� ��ŷ�� �ӽ� ����.      
#endif

private:
	CNServerEvent_Rank_Record		m_clServerEvent_Rank_Record;										// �����̺�Ʈ ��ŷ���� ���.(�迭 ������ ����)
	CNServerEvent_Quest				m_clServerEvent_Quest;												// �����̺�Ʈ ����Ʈ.
	CNInstanceMapInfo				m_clInstanceMapInfo;												// �����̺�Ʈ �δ����� ����.


//******************************************************************************************
//
// ��������:  2009.12.18 ~ 
//
// * ���� �̺�Ʈ�� ���� ���� �̺�Ʈ�� ����Ǿ� ���Ǵ� ����, �Լ�. 
//
// * ���� �̺�Ʈ�� �����.
//
//******************************************************************************************
public:	
	void				ActionGoonzuDay(void);				// ���� �̺�Ʈ�� ���ֵ��� �̺�Ʈ�� �����Ŵ. 
	void				ActionGoonzuDayReward(void);		// ����Ⱓ ���� ������ ��û��.
	bool				IsGoonzuDayEventSuccess( void );	// ���� ���� �̺�Ʈ �� ���� ������ �����ؾߵǴ� �ִ� ���� �̻��� �Ǹ� ����.
	void				DeleteGate( void );

private:	
	SI64				m_siGoonzuDayDayEventScore;
};

#endif