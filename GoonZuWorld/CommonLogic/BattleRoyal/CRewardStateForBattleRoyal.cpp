#include ".\CRewardStateForBattleRoyal.h"
#include "../common/Char/CharServer/Char-Server.h"

CRewardStateForBattleRoyal::CRewardStateForBattleRoyal(void)
{
}

CRewardStateForBattleRoyal::~CRewardStateForBattleRoyal(void)
{
}

BOOL	CRewardStateForBattleRoyal::Handle()
{
	if( NULL == m_pclStadium)
		return FALSE;
	if( NULL == m_pclReward)
		return FALSE;
	if( NULL == m_pclGameMode)
		return FALSE;

	// 1. ��� ��� ����. - ����� . ����
	if(FALSE == m_pclStadium->ProcessResult())
		return FALSE;
	cltCharCommon* pclChar = m_pclStadium->GetWinner();
	if( NULL !=  pclChar)
	{
		if(FALSE == m_pclReward->GiveRewardToWinner(pclChar))
			return FALSE;
	}
	
	// 2. ���� �ִ� ������ ��������.. - �����
	if(FALSE == m_pclStadium->BanGamer())
		return FALSE;
	
	// 3. ��� ������ ��ü �˾����� �˷��ش�.. - �����
	if(FALSE == m_pclStadium->NoticeResult())
		return FALSE;
	return TRUE;
}