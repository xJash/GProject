#ifndef	__GAWIBAWIBOMGR_SERVER_H__
#define __GAWIBAWIBOMGR_SERVER_H__

#pragma once

#include <Directives.h>
#include "../../Common/CommonHeader.h"
#include "../../Client/client.h"

#include <vector>

class CGawiBawiBoMgr_Server
{
public:
	enum ENUM_GAWIBAWIBO_CALCULATE_RESULT
	{
		GAWIBAWIBO_RESULT_NONE,
		GAWIBAWIBO_RESULT_ABUSE_WIN,
		GAWIBAWIBO_RESULT_WIN,
		GAWIBAWIBO_RESULT_DRAW,
		GAWIBAWIBO_RESULT_LOSE,
		GAWIBAWIBO_RESULT_END,
	};

	enum ENUM_GAWIBAWIBO_CALCULATE_RESULT_CASE
	{
		GAWIBAWIBO_RESULT_VALIDCOUNT_NONE,
		GAWIBAWIBO_RESULT_VALIDCOUNT_MAXWIN,	// �ְ����� �ߴ�.
		GAWIBAWIBO_RESULT_VALIDCOUNT_INVALID,	// �����ִ� ��
		GAWIBAWIBO_RESULT_VALIDCOUNT_VALID,		// ��ȿ�� ��
	};

private:
	SI16			m_siStatus;
	SI16			m_siResult;
	SI32			m_siWInPercentage[GAWIBAWIBO_RESULT_END];
	vector<SI32>	m_vecStraightWins;
	bool			m_bAlwaysWin;				// gm��ɾ� ���� �������
	SI32			m_siLimitWin;				// ���� ����
	
public:
	bool	Initialize();	//	�Ŵ��� �ʱ�ȭ
	void	Action();		//	Action

	bool	LoadGawiBawiBoFiles();	//	���������� ���ҽ� Read

	void	SetStatus(SI16 siStatus){m_siStatus = siStatus;}
	SI16	GetStatus(){return m_siStatus;}

	SI08	GetCalculateResult();
	GMONEY	GetChargedMoney();										//	������ �ݾ��� ����
	GMONEY  GetCalculateCumulativeMoney(SI08 siStraightWins);		//	�����ݾ� ���
	SI08	IsValidCount(SI08 siCount);								//	 ���� ī��Ʈ���� ��ȿ�Ѱ��ΰ�

	void	ToggleAlwaysWin(){m_bAlwaysWin = !m_bAlwaysWin;}		//   �׻� �̱�� ��� ���
	bool	IsAlwaysWin(){return m_bAlwaysWin;}						//	 �׻� �̱�� ����ΰ�?
	void	SetLimitWin(SI32 siLimitWin);
	SI32	GetLimitWin(){return m_siLimitWin;}
	

public:
	CGawiBawiBoMgr_Server();
	~CGawiBawiBoMgr_Server();
};

#endif