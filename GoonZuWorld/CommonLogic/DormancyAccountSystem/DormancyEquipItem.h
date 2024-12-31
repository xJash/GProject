#pragma once

#include "../CommonLogic/CommonLogic.h"

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.07.30
// Ŭ������ : CDormancyEquipItem
// ���� : �޸� ���� ���� ��� ������ ������ Ŭ����
//================================================================================
class CDormancyEquipItem
{
// �ɹ� ����
public:

protected:
	// ������� ����ũ
	SI32	m_siBoxUnique;
	// ������ ����ũ
	SI32	m_siUnique;
	// �迭 ũ��
	const static SI32 MAX_ARRAY_SIZE  = MAX_CHARACTER_LEVEL+1;

	// ������ ������ ����ũ ( ���������� ���׷��̵� �� ������ �迭�� �ε����� ���� �Ͽ� �˻� �ӵ��� ���δ�.)
	// ���� �� ������ �� �����ۿ� ���ؼ��� ����� ������ ���ؼ��� �ذ��.
#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_ARRAY_SIZE>		m_TargetItemUniqueArray;
#else
	SI32 m_TargetItemUniqueArray[MAX_ARRAY_SIZE];
#endif

// �ɹ� �޼ҵ�
public:
	CDormancyEquipItem(void);
	~CDormancyEquipItem(void);

	// ���׷��̵� �� Ÿ�� ��� �������� ����ũ�� �����Ѵ�.
	BOOL	InsertTargetItem(SI32 siTargetUnique, SI32 siUpgradeLevel);
	// ���׷��̵� �� Ÿ�� ��� �������� ����ũ �� ����
	SI32	GetTargetItemUnique(SI32 siUpgradeLevel);


	VOID	SetBoxUnique(SI32 siBoxUnique);
	VOID	SetUnique(SI32 siUnique);

	const	SI32	GetBoxUnique() const;
	const	SI32	GetUnique() const;
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.07.30
// Ŭ������ : CDormancyEquipItemMgr
// ���� : �޸� ���� ���� ��� ������ ���� Ŭ����
//================================================================================
class CDormancyEquipItemMgr
{
// �ɹ� ����
public:
	
	// �޸� ���� ���� ��� �������� �ִ� ��
	const static SI32 MAX_ITEM_COUNT = 32;	
private:

	// ������ �迭
	#ifdef _SAFE_MEMORY
		NSafeTArray<CDormancyEquipItem, MAX_ITEM_COUNT>		m_ItemArray;
	#else
		CDormancyEquipItem	m_ItemArray[MAX_ITEM_COUNT];
	#endif

// �ɹ� �޼ҵ�
public:
	CDormancyEquipItemMgr(void);
	~CDormancyEquipItemMgr(void);

	//	������ ���� - ���� �а� �޸𸮿� ���
	BOOL	Create();

	// ������ ����ũ�� ���� �ϴ��� ���� 
	BOOL	IsExist(SI32 siUnique);

	// �޸� ���� ��� ������ 
	CDormancyEquipItem *GetDormancyEquipItem(SI32 siUnique);
private:

	// ������ ������ �޸� ���� ������ ���� �ƴ��� �οﰪ �Է�
	BOOL	SetIsDormancyToItemInfo(SI32 siUnique);
};
