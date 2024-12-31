#pragma once
//#include "../SoulGuardMgr/SoulGuardMgr.h"

// ��� ��� �˷��ֱ�
class cltGameMsgResponse_BattleRoyalNoticeResult
{
public:
	// �¸��� �̸�
	TCHAR	m_szWinnerName[MAX_PLAYER_NAME];
	// �¸� �ߴ��� 
	bool	m_bResult;
	// ����� ��
	SI32	m_siMapIndex;
public:
	cltGameMsgResponse_BattleRoyalNoticeResult(const TCHAR* pszWinnerName , bool bResult, SI32 siMapIndex)
	{
		ZeroMemory(m_szWinnerName, MAX_PLAYER_NAME * sizeof(TCHAR));

		if ( NULL != pszWinnerName)
			memcpy(m_szWinnerName, pszWinnerName, MAX_PLAYER_NAME * sizeof(TCHAR));
		
		m_bResult = bResult;
		m_siMapIndex = siMapIndex;
	}
};	// GAMEMSG_RESPONSE_BATTLEROYAL_NOTICERESULT

// ��� ���۽� ���� ���� �ð� ��û
class cltGameMsgRequest_BattleRoyalRemainedTime
{
public:
	cltGameMsgRequest_BattleRoyalRemainedTime()
	{

	}
};	// GAMEMSG_REQUEST_BATTLEROYAL_REMAINEDTIME

// ��� ���۽� ���� ���� �ð� ����
class cltGameMsgResponse_BattleRoyalRemainedTime
{
public:
	SI32	m_siTime;
public:
	cltGameMsgResponse_BattleRoyalRemainedTime(SI32	siTime)
	{
		m_siTime = siTime;
	}
};	// GAMEMSG_RESPONSE_BATTLEROYAL_REMAINEDTIME

// ��� ���� 
class cltGameMsgResponse_BattleRoyalStartGame
{
public:
	SI32	m_siTime;	// �ɸ��� �ð�
	SI32	m_siMode;	// ���
public:
	cltGameMsgResponse_BattleRoyalStartGame(SI32 siTime, SI32 siMode)
	{
		m_siTime = siTime;
		m_siMode = siMode;
	}
};	// GAMEMSG_RESPONSE_BATTLEROYAL_STARTGAME

// ��� ����
class cltGameMsgResponse_BattleRoyalEndGame
{
public:
	cltGameMsgResponse_BattleRoyalEndGame()
	{
	}
};	// GAMEMSG_RESPONSE_BATTLEROYAL_ENDGAME

// ��� ���� 
class cltGameMsgResponse_BattleRoyalPowerupMode
{
public:
	SI32	m_siCharUnique;	// �Ŀ��� �� charid
	bool	m_bValue;
public:
	cltGameMsgResponse_BattleRoyalPowerupMode(SI32 siCharUnique, bool bValue)
	{
		m_siCharUnique = siCharUnique;
		m_bValue = bValue;
	}
};	// GAMEMSG_RESPONSE_BATTLEROYAL_POWERUPMODE