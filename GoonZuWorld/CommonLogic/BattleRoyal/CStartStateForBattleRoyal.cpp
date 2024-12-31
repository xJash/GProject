#include ".\CStartStateForBattleRoyal.h"

CStartStateForBattleRoyal::CStartStateForBattleRoyal(void)
{
}

CStartStateForBattleRoyal::~CStartStateForBattleRoyal(void)
{
}

BOOL	CStartStateForBattleRoyal::Handle()
{
	if( NULL == m_pclStadium)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	// 1. ����� �Ա��� ����. - �����
	m_pclStadium->OpenGate();
	// 2. ��ü ���� �޽����� ������ ��ΰ� ������ �˸���. - �����
	if(FALSE == m_pclStadium->NoticeOpen())
		return FALSE;
	return TRUE;
}