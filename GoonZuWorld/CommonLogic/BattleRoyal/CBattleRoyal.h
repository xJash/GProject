//
//
//  @ File Name : CBattleRoyal.h
//  @ Date : 2009-09-25
//  @ Author : �ڱ���
//	@ Desc : ��Ʋ�ξ� ó�� Ŭ����
//


#if !defined(_CBATTLEROYAL_H)
#define _CBATTLEROYAL_H

#include "../CommonLogic.h"
#include "./CWaitStateForBattleRoyal.h"
#include "./CGameStateForBattleRoyal.h"
#include "./CEndStateForBattleRoyal.h"
#include "./CRewardStateForBattleRoyal.h"
#include "./CStartStateForBattleRoyal.h"

#include "./CAbstractState.h"

#include "./CBattleRoyalGameMode.h"
#include "./CBattleRoyalReward.h"
#include "./CBattleRoyalStadium.h"

#include "../common/DailyEventTimer/DailyEventTimer.h"

class CWaitStateForBattleRoyal;
class CGameStateForBattleRoyal;
class CEndStateForBattleRoyal;
class CRewardStateForBattleRoyal;
class CStartStateForBattleRoyal;

class CAbstractState;

class CBattleRoyalGameMode;
class CBattleRoyalReward;
class CBattleRoyalStadium;

class CDailyEventTimer;

enum
{
	BATTLEROYAL_ENTERERROR_ISOPENED = 2,
	BATTLEROYAL_ENTERERROR_WASJOINED,
	BATTLERPYAL_ENTERERROR_ISMAKING,
	BATTLERPYAL_ENTERERROR_TAKEDOUTSUMMON,
	BATTLERPYAL_ENTERERROR_FULLEDGAMER,
	BATTLERPYAL_ENTERERROR_JOINPARTY
};

class CBattleRoyal {

public:
	CBattleRoyal();
	virtual ~CBattleRoyal();

	virtual	BOOL	Create() = 0;	// ����

	// ���� ���� ===================================================
	BOOL	Waiting();	// ��� ���·�
	BOOL	Gaming();	// ���� ���·�
	BOOL	Ending();	// ���� ���·�
	BOOL	Rewarding();// ���� ���·�
	BOOL	Starting(); // ���� ���·�
	BOOL	Action();	// �ൿ

	BOOL	IsWaiteState();	// ����������
	BOOL	IsGamingState();// ���ӻ�������
	BOOL	IsEndState();	// �����������
	BOOL	IsRewardState();// �����������
	BOOL	IsStartState(); // ���ۻ�������
	// =============================================================

	BOOL	CanEnter(cltCharServer* pclChar);	// ���� ��������  
	BOOL	GetCanEnterLevel(UI32* uiMinLevel, UI32* uiMaxLevel);	// ���� ���� ����
	BOOL	GiveItemToKiller(cltCharServer* pclChar); // ��Ʋ�ξ� �߿� ������ ���� ������� �������� �ش�.(100% Ȯ�� �ƴ�)
	SI32	GetStadiumMapIndex();				// �� �ε���
	BOOL	CheckOutGamer();					// ������� �������� ���������� üũ
	BOOL	IsEarlyEnd();
	BOOL	DieMob();
	void	SetNextStartTime(SI32 siNextStartTime);
	SI32	GetNextStartRemainedTime();
	BOOL	CanUseHealItem();	// ������������ ��� �� �� �ִ� ��
	BOOL	SetGameTime(SI32 siTime);	// ���� �÷��� �ð� ����
	BOOL	IsExistStadium(cltCharServer* pclChar);
	BOOL	ActionGameMode();
	BOOL	SetGMGameMode(SI32 siMode);
	BOOL	TakeinHorse(cltCharServer* pclChar);	// ����忡 �� �� ������ ���� �ִٸ� ������ �� �ֱ�
	BOOL	RestorChar(cltCharServer* pclChar);		// ����忡 ���ͼ� ���� ���� ������ �����·� ������.
	BOOL	TransformChar(cltCharServer* pclChar);		// ������ ������ ���� ��Ų��.
	static	void WarpFrontOfStadium(cltCharServer* pclChar);	// ����� ������ �̵�
protected:

	void	InitState();	// ���� ��ü �ʱ�ȭ

	CWaitStateForBattleRoyal	m_clWaitState;	// ��� ���� ��ü
	CGameStateForBattleRoyal	m_clGameState;	// ���� ���� ��ü
	CEndStateForBattleRoyal		m_clEndState;	// ���� ���� ��ü
	CRewardStateForBattleRoyal	m_clRewardState;// ���� ���� ��ü
	CStartStateForBattleRoyal	m_clStartState; // ���� ���� ��ü

	CAbstractState*				m_pclState;		// ���� ����

	CBattleRoyalGameMode*		m_pclGameMode;	// ���� ���
	CBattleRoyalReward*			m_pclReward;	// ����
	CBattleRoyalStadiumServer*	m_pclStadium;	// �����

	SI32						m_siNextStartTime;	// ���� ��� ���� �ð�
};

#endif  //_CBATTLEROYAL_H