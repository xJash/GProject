#pragma once

//#include "../../Client/Client.h"
#include "../CommonLogic/CommonLogic.h"

#include "DormancyEquipItem.h"
#include "DormancyBox.h"

class CDormancyBoxMgr;
class CDormancyEquipItemMgr;
class cltClient;
class cltServer;

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.1
// Ŭ������ : CDormancyEquipItemReward
// ���� : �޸� ���� �ý����� ��� ���� ���� ��Ʈ�ѷ� Ŭ����
//================================================================================
class CDormancyEquipItemReward
{
// �ɹ� ����
public:
	// ���� ��� ������ ���� Ŭ����
	CDormancyEquipItemMgr*	m_pclDormancyEquipItemMgr;
	// ���� ���� ���� Ŭ����
	CDormancyBoxMgr*	m_pclDormancyBoxMgr;

private:
	// Ŭ���̾�Ʈ ��ü
	cltCommonLogic*	m_pclCommon;

// �ɹ� �޼ҵ�
public:
	// ������
	CDormancyEquipItemReward();
	// �Ҹ���
	virtual ~CDormancyEquipItemReward(void);

	//����
	BOOL		Create();

	// �޸� ��� ���������� Ȯ���Ѵ�.
	BOOL		IsDormancyEquipItem(SI32 siItemUnique);

	//���� ���ڿ� ��� �ִ� �������� �ε��� ���� ��� ����.
	cltItemInfo	*GetItemInfoInBox(SI32 siBoxUnique, SI32 siIndex);

	//���� ���ڿ� ��� �ִ� �������� �ε��� ���� ��� ����.
	SI32		GetItemUniqueInBox(SI32 siBoxUnique, SI32 siIndex);

	//��� ������ ��ȭ�ϱ�(�κ��丮�� �ִ� �������� ��� �˻� �ؼ�)
	BOOL	UpgradeItemInven(cltCharCommon *pclChar);
	//��� ������ ��ȭ�ϱ�(Ư�� ������)
	BOOL	UpgradeItemInfo(cltCharCommon *pclChar,cltItem *pclItem);
	//��� ������ ��ȭ�ϱ�(�κ��丮�� �ִ� Ư�� ������)
	virtual BOOL	UpgradeItem(cltCharCommon *pclChar, SI32 siItemUnique, SI32 siItemPos, SI32 siType);
};


//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.2
// Ŭ������ : CDormancyEquipItemRewardClient
// ���� : �޸� ���� �ý����� ��� ���� ���� ��Ʈ�ѷ� Ŭ����(Ŭ���̾�Ʈ��)
//================================================================================
class CDormancyEquipItemRewardClient : public CDormancyEquipItemReward
{
// �ɹ� ����
public:

private:
	// Ŭ���̾�Ʈ ��ü
	cltClient*	m_pclClient;

// �ɹ� �޼ҵ�
public:
	// ������
	CDormancyEquipItemRewardClient();
	// �Ҹ���
	virtual ~CDormancyEquipItemRewardClient(void);

	//	������ ����
	BOOL	SelectItemInBox(SI32 siItemIndex,SI32 siBoxUnique, SI32 siBoxPos);

	//�ڽ� ���
	BOOL	UseBox(SI32 siItemUnique, SI32 siPos);
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.2
// Ŭ������ : CDormancyEquipItemRewardServer
// ���� : �޸� ���� �ý����� ��� ���� ���� ��Ʈ�ѷ� Ŭ����(������)
//================================================================================
class CDormancyEquipItemRewardServer : public CDormancyEquipItemReward
{
// �ɹ� ����
public:

private:
	// ���� ��ü
	cltServer*	m_pclServer;

// �ɹ� �޼ҵ�
public:
	// ������
	CDormancyEquipItemRewardServer();
	// �Ҹ���
	virtual ~CDormancyEquipItemRewardServer(void);

	//��� ������ ����
	BOOL	GiveItemToPlayer(SI32 siBoxUnique, SI32 siItemUnique, SI32 siIBoxPos,cltCharServer *pclChar, SI32 siItemIndex);	

	//�ý��� ���� : ��� ���� ���� 2�� �ֱ�
	BOOL	GiveEquipBox(cltCharServer *pclCharServer);

	//��� ������ ��ȭ�ϱ�(�κ��丮�� �ִ� Ư�� ������)
	virtual BOOL	UpgradeItem(cltCharCommon *pclChar, SI32 siItemUnique, SI32 siItemPos, SI32 siType);
};