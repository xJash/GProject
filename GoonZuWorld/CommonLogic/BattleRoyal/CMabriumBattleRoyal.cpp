#include ".\CMabriumBattleRoyal.h"
#include "./CMabriumBattleRoyalGameMode.h"
#include "./CMabriumBattleRoyalReward.h"
#include "./CMabriumBattleRoyalStadium.h"

CMabriumBattleRoyal::CMabriumBattleRoyal(void)
{

}

CMabriumBattleRoyal::~CMabriumBattleRoyal(void)
{

}

//	����
BOOL	CMabriumBattleRoyal::Create()
{
	if( NULL != m_pclGameMode)
		return FALSE;
	if( NULL != m_pclReward)
		return FALSE;
	if( NULL != m_pclStadium)
		return FALSE;

	m_pclGameMode = new CMabriumBattleRoyalGameMode();
	if( NULL == m_pclGameMode)
	{
		return FALSE;
	}

	m_pclReward = new CMabriumBattleRoyalReward();
	if( NULL == m_pclReward)
	{
		return FALSE;
	}
	m_pclReward->Create();

	m_pclStadium = new CMabriumBattleRoyalStadiumServer();
	if( NULL == m_pclStadium)
	{
		return FALSE;
	}
	m_pclStadium->Init();
	m_pclGameMode->SetGamers(m_pclStadium->GetPersonChangedData(), CBattleRoyalStadiumServer::MAX_GAMER_COUNT,m_pclStadium->GetMobData());

	// ���� ��ü �ʱ�ȭ
	InitState();

	return TRUE;
}
