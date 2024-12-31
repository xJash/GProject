#pragma once

#include "../CommonLogic/CommonLogic.h"

#include "DormancyEquipItemReward.h"
#include "DormancyPointReward.h"
#include "DormancyInfo.h"

class	CDormancyEquipItemReward;
class	CDormancyPointReward;
class	CDormancyInfo;

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.07.30
// Ŭ������ : CDormancySystem
// ���� : �޸� ���� �ý��� ���� ��� Ŭ����
//================================================================================
class CDormancySystem
{
// �ɹ� ����
public:
	// �޸����������� Ŭ���� 
	CDormancyEquipItemReward* m_pclDormancyEquipItemReward;
	// �޸��������Ʈ Ŭ���� 
	CDormancyPointReward* m_pclDormancyPointReward;
	// ��� �÷���
	SI32	m_siGameMode;


// ��� �޼ҵ�
public:
	// �Ҹ���
	virtual ~CDormancySystem();

	// ������
	CDormancySystem(SI32 siGameMode = GAMEMODE_CLIENT);
	
	// �޸����������� Ŭ���� ������ ���
	const CDormancyEquipItemReward *GetDormancyEquipItemReward() const;
	// �޸��������Ʈ Ŭ���� ������ ���
	const CDormancyPointReward *GetDormancyPointReward() const;

	//����
	BOOL	Create();

	//���� ���
	SI32	GetGameMode();
};