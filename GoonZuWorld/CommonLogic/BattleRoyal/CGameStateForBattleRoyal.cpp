#include ".\CGameStateForBattleRoyal.h"

CGameStateForBattleRoyal::CGameStateForBattleRoyal(void)
{
}

CGameStateForBattleRoyal::~CGameStateForBattleRoyal(void)
{
}

BOOL	CGameStateForBattleRoyal::Handle()
{
	if( NULL == m_pclStadium)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	// 1. ���� ���� �Ұ��� ó�� - �����
	m_pclStadium->CloseGate();
	// 2. ���� ���� ����Ʈ ���� - �����
	if(FALSE == m_pclStadium->SaveGamerList())
		return FALSE;
	// 3. ���͸� �����Ѵ�. - �����
	if(FALSE == m_pclStadium->CreateMob())
		return FALSE;
	// 4. ���� ��� ���� ���� - ���� ���
	if(FALSE == m_pclGameMode->Apply())
		return FALSE;
	// 5. ���̵� ��� ������ ������ �����ش�. - ���� ���
	if(FALSE == m_pclGameMode->ChangeVisibleMode())
		return FALSE;
	
	return TRUE;
}