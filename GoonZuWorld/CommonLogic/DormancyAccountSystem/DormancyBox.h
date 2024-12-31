#pragma once

#include "../CommonLogic/CommonLogic.h"
#include "DormancyEquipItem.h"

class CDormancyEquipItem;
class CDormancyEquipItemMgr;

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.07.31
// Ŭ������ : CDormancyBox
// ���� : �޸� ���� ���� ���� ������ Ŭ����
//================================================================================
class CDormancyBox
{
public:
	// ������ ���� ���� �Ⱓ
	const static SI32 GIVESYSTEMDATE = 30;

// �ɹ� ����
protected:
	// �������� ����� ��
	SI32	m_siItemCount;
	// ������ ����ũ
	SI32	m_siUnique;

	// �޸� ���� ���� ���ڿ� ���� ��� �������� �ִ� ��
	const static SI32 MAX_ITEM_COUNT = 6;	

	// ������ �迭
#ifdef _SAFE_MEMORY
	NSafeTArray<CDormancyEquipItem *, MAX_ITEM_COUNT>		m_ItemArray;
#else
	CDormancyEquipItem	*m_ItemArray[MAX_ITEM_COUNT];
#endif

	 
// �ɹ� �޼ҵ�
public:
	CDormancyBox(void);
	~CDormancyBox(void);

	// ���ڿ� ��� �������� �ִ´�.
	BOOL	InsertItem(CDormancyEquipItem *pclDormancyEquipItem);

	// ���ڿ� ��� �ִ� ������ ��
	SI32	GetItemCount() const;

	VOID	SetUnique(SI32 siUnique);
	SI32	GetUnique() const;

	// �ε����� ��� ������ �ε����� ��´�.
	CDormancyEquipItem*	GetEquipItem(SI32 siIndex);
};
//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.07.31
// Ŭ������ : CDormancyBoxMgr
// ���� : �޸� ���� ���� ���� ���� Ŭ����
//================================================================================
class CDormancyBoxMgr
{
// �ɹ� ����
public:
	
private:
	// �ڽ� ��
	SI32	m_siCount;
	// �޸� ���� ��� ������ ����
	CDormancyEquipItemMgr *m_pclDormancyEquipItemMgr;

	// �޸� ���� ���� ���� �������� �ִ� ��
	const static SI32 MAX_ITEM_COUNT = 4;	

	// ������ �迭
#ifdef _SAFE_MEMORY
	NSafeTArray<CDormancyBox, MAX_ITEM_COUNT>		m_ItemArray;
#else
	CDormancyBox	m_ItemArray[MAX_ITEM_COUNT];
#endif

// �ɹ� �޼ҵ�
public:
	CDormancyBoxMgr(CDormancyEquipItemMgr *pclDormancyEquipItemMgr);
	~CDormancyBoxMgr(void);


	// ������ ����ũ�� ���� ���ڰ� ���� �ϴ��� ���� 
	BOOL	IsExist(SI32 siUnique);

	// �޸� ���� ���� ����
	CDormancyBox *GetDormancyBox(SI32 siUnique);

	//	������ ���� - ���� �а� �޸𸮿� ���
	BOOL	Create();

	// �ڽ� ��
	SI32	GetCount();

	// �޸� ���� ���� ���� (�Ŵ����� �ε�����)
	CDormancyBox *GetDormancyBoxByIndex(SI32 siIndex);
protected:
	CDormancyBoxMgr(void);
};
