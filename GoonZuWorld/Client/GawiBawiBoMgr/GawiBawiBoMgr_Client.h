#pragma once

#include <Directives.h>
#include "../../Common/CommonHeader.h"
#include "../client.h"
#include <vector>

class CGawiBawiBoMgr_Client
{
private:
	enum ENUM_GAWIBAWIBO_CALCULATE_RESULT
	{
		GAWIBAWIBO_RESULT_NONE,
		GAWIBAWIBO_RESULT_ABUSE_WIN,
		GAWIBAWIBO_RESULT_WIN,
		GAWIBAWIBO_RESULT_DRAW,
		GAWIBAWIBO_RESULT_LOSE,
		GAWIBAWIBO_RESULT_END,
	};

	enum ENUM_GAWIBAWIBO_MAX_TIME
	{
		GAWIBAWIBO_NEXTSTEP_TIME	= 1000,
		GAWIBAWIBO_MIN_TIME			= 5000,	
		GAWIBAWIBO_MAX_TIME			= 30000,	
	};

	SI16	m_siStatus;
	SI08	m_siResult;
	GMONEY	m_siCumulativeMoney;	//	�����ݾ�

	SI08	m_siGawiBawiBoCount;	//	���� ī��Ʈ

	DWORD	m_Timer;

	SI32	m_siWInPercentage[GAWIBAWIBO_RESULT_END];
	vector<SI32> m_vecStraightWins;
	bool	m_bIsMaxWins;

public:
	enum GAWIBAWIBO_STATUS
	{
		GAWIBAWIBO_NONE,						//	none
		GAWIBAWIBO_INIT,						//	�ʱ�ȭ
		GAWIBAWIBO_WAIT_PLAYER,					//	�÷��̾� ��ٸ�����
		GAWIBAWIBO_DO_CHECK_MONEY,				//	�÷��� ���� üũ ��ƾ��������
		GAWIBAWIBO_NOW_CHECKING,				//	�÷��� �������� üũ��
		GAWIBAWIBO_DO_CHARGEDMONEY,				//	�ݾ� ������������
		GAWIBAWIBO_NOW_CHARGINGMONEY,			//	�ݾ� ������
		GAWIBAWIBO_WAIT_SELECT,					//	�÷��̾� ���� ��ٸ��� ����
		GAWIBAWIBO_NOW_WAIT_SELECT,				//	�÷��̾� ���� ��ٸ�����
		GAWIBAWIBO_SELECT,						//	�� ������
		GAWIBAWIBO_NOW_CALCULATE_SELECT,		//	���� ��� ������
		GAWIBAWIBO_CALCULATE_SELECT_COMPLETE,	//	��� ���� �Ϸ�
		GAWIBAWIBO_SHOW_CALCULATE_SELECT,		//	������ ��� �����ִ� ��
		GAWIBAWIBO_RESULT,						//	Calculate and Result
		GAWIBAWIBO_SHOW_CEREMONY,				//	�̱�� �� ������� �����ֱ�
		GAWIBAWIBO_RESULT_PROCESS,				//	����� ���� ����
		GAWIBAWIBO_NOW_RESULT_PROCESS,			//	����� ���� ���� ��
		GAWIBAWIBO_END,
	};

public:
	bool		Initialize();	//	�Ŵ��� �ʱ�ȭ
	bool		StartGame();	//	���������� �Ŵ��� �۵�
	void		Action();		//	Action
	bool		LoadGawiBawiBoFiles();

	void		SetStatus(SI16 siStatus);
	SI16		GetStatus(){return m_siStatus;}
	void		EndGame(){m_siStatus = GAWIBAWIBO_WAIT_PLAYER; m_siGawiBawiBoCount = 0; m_siCumulativeMoney = 0; m_bIsMaxWins = false;}
	void		ReGame(){m_siStatus = GAWIBAWIBO_DO_CHECK_MONEY;}
	void		GiveUp();

	void		DrawGame(){m_siStatus = GAWIBAWIBO_WAIT_SELECT;}
	void		Lose();

	void		SetResult(SI08 siResult);	// ���������� ���� ���
	SI08		GetResult(){return m_siResult;}

	inline void	NextSteps(){m_siStatus++;}	//	�������� ����

	void		InitTimer();
	void		SetTimer(clock_t lnTime);
	bool		IsTimePassed();
	clock_t		GetTimePassed();
	GMONEY		GetCumulativeMoney(){return m_siCumulativeMoney;}	//	���� �����ݾ� Get
	GMONEY		GetCalculateCumulativeMoney(SI08 siCount);			//	�����ݾ� ���
	void		SetCalculateCumulativeMoney(GMONEY siMoney){m_siCumulativeMoney = siMoney;}

	SI08		GetCount();
	void		SetCount(SI08 siCount){m_siGawiBawiBoCount = siCount;}
	
	void		SetMaximumWins(bool bMaximumWin){m_bIsMaxWins = bMaximumWin;}		// �ְ��½�
	bool		GetMaximumWins(){return m_bIsMaxWins;}		// �ְ��½�

public:
	CGawiBawiBoMgr_Client();
	~CGawiBawiBoMgr_Client();
};

