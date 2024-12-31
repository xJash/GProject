#include ".\dormancysystem.h"

CDormancySystem::~CDormancySystem(void)
{
	if( GAMEMODE_SERVER == m_siGameMode)
	{
		if(NULL != m_pclDormancyEquipItemReward)
		{
			delete (m_pclDormancyEquipItemReward);
			m_pclDormancyEquipItemReward = NULL;
		}
		if(NULL != m_pclDormancyPointReward)
		{
			delete (m_pclDormancyPointReward);
			m_pclDormancyPointReward = NULL;
		}
	}
	else
	{
		if(NULL != m_pclDormancyEquipItemReward)
		{
			delete (m_pclDormancyEquipItemReward);
			m_pclDormancyEquipItemReward = NULL;
		}
		if(NULL != m_pclDormancyPointReward)
		{
			delete (m_pclDormancyPointReward);
			m_pclDormancyPointReward = NULL;
		}
	}
}

CDormancySystem::CDormancySystem(SI32 siGameMode)
{
	// �޸����������� Ŭ���� 
	m_pclDormancyEquipItemReward = NULL;
	// �޸��������Ʈ Ŭ���� 
	m_pclDormancyPointReward = NULL;
	// ���� ���
	m_siGameMode = siGameMode;
}

// �޸����������� Ŭ���� ������ ���
const CDormancyEquipItemReward *CDormancySystem::GetDormancyEquipItemReward() const
{
	return m_pclDormancyEquipItemReward;
}

// �޸��������Ʈ Ŭ���� ������ ���
const CDormancyPointReward *CDormancySystem::GetDormancyPointReward() const
{
	return m_pclDormancyPointReward;
}

//����
BOOL	CDormancySystem::Create()
{
	if(NULL != m_pclDormancyEquipItemReward)
		return FALSE;
	if(NULL != m_pclDormancyPointReward)
		return FALSE;

	if( GAMEMODE_SERVER == m_siGameMode)
	{
		m_pclDormancyEquipItemReward = (CDormancyEquipItemReward*) new CDormancyEquipItemRewardServer();
		m_pclDormancyPointReward =(CDormancyPointReward*) new CDormancyPointRewardServer();
	}
	else
	{
		m_pclDormancyEquipItemReward = (CDormancyEquipItemReward*) new CDormancyEquipItemRewardClient();
		m_pclDormancyPointReward =(CDormancyPointReward*) new CDormancyPointRewardClient();
	}
	
	if(NULL == m_pclDormancyEquipItemReward)
		return FALSE;
	if(NULL == m_pclDormancyPointReward)
		return FALSE;

	if(!m_pclDormancyEquipItemReward->Create())
	{
		return FALSE;
	}
	if(!m_pclDormancyPointReward->Create())
	{
		return FALSE;
	}

	return TRUE;
}

//���� ���
SI32	CDormancySystem::GetGameMode()
{
	return m_siGameMode;
}
