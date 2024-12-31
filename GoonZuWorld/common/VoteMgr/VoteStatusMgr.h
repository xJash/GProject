#pragma once

#include <Directives.h>
#include "CommonLogic.h"

#include "VoteBaseInfo.h"

class NUpdateTimer;

// �Ʒ� ���ڴ� �� ��ǥ �ð��� ���ϱ⵵ �Ѵ�
const SI32 Const_VoteStatusMgr_End_Count = 30;

class CVoteStatusMgr
{

public:
	CVoteStatusMgr();
	~CVoteStatusMgr();

	void	Init();
	void	Action();

public:
	void	StartVoteStatus( SI32 *psiVote );
	void	SendVoteStatus();

	void	WriteResult( SI32 *psiVote );

private:
	bool	ReadCandidateName();


public:
	// �ĺ��� �̸�
	TCHAR			m_tszCandidateName[MAX_CANDIDATURE_NUM][MAX_PLAYER_NAME];

	SI32			m_siTopVoteNum;							// �ִ� ��ǥ���� ��ǥ��	
	SI08			m_siCandidateNum;						// �ĺ��� ��
	SI32			m_siTotalVote;							// �� ��ǥ��

private:
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_CANDIDATURE_NUM>		m_siVote;
	NSafeTArray<SI32, MAX_CANDIDATURE_NUM>		m_siSendVote;
#else
	SI32			m_siVote[MAX_CANDIDATURE_NUM];			// �ĺ��ں� �� ��ǥ��
	SI32			m_siSendVote[MAX_CANDIDATURE_NUM];		// Ŭ���̾�Ʈ�� ���� �ĺ��ں� ��ǥ��
#endif
	
	SI08			m_siTimeCounter;						// 60���� �������� �ϱ� ����

	bool			m_bStart;								// ��ǥ�� ���۵Ǿ���

	NUpdateTimer	m_kActionTimer;							// Action�Լ� ���� Ÿ�̸�

};