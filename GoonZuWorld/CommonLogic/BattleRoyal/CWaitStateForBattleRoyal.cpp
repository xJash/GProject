#include ".\CWaitStateForBattleRoyal.h"

CWaitStateForBattleRoyal::CWaitStateForBattleRoyal(void)
{
}

CWaitStateForBattleRoyal::~CWaitStateForBattleRoyal(void)
{
}

BOOL	CWaitStateForBattleRoyal::Handle()
{
	if( NULL == m_pclStadium)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	// 1. ���� �ʱ�ȭ
	m_pclStadium->InitData();

	// 2. ��ü ���� �޽����� 5�� �� ���� ������ �˸���. - �����
	if(FALSE == m_pclStadium->NoticeWait())
		return FALSE;

	// 3. ���� ��� ���� - ���� ���
	if(FALSE == m_pclGameMode->DetermineMode())
		return FALSE;
	return TRUE;
}
