#pragma once

#include "../CommonLogic/CommonLogic.h"

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.18
// Ŭ������ : CDormancyPointItem
// ���� : �޸� ���� ����Ʈ ������ ������ Ŭ����
//================================================================================
class CDormancyPointItem
{
	// �ɹ� ����
public:

protected:
	// ����Ʈ ����
	SI32	m_siPoint;
	// ������ ����ũ
	SI32	m_siUnique;
	
	// �ɹ� �޼ҵ�
public:
	CDormancyPointItem(void);
	~CDormancyPointItem(void);

	VOID	SetUnique(SI32 siUnique);
	VOID	SetPoint(SI32 siPoint);

	SI32	GetPoint() const;
	SI32	GetUnique() const;
};

//================================================================================
// �ۼ��� : �ڱ���
// �ۼ��� : 2009.08.2
// Ŭ������ : CDormancyPointItemMgr
// ���� : �޸� ���� �ý����� ����Ʈ ������ ���� Ŭ����
//================================================================================

class CDormancyPointItemMgr
{
//�ɹ� ����
public:
	// �޸� ���� ���� ��� �������� �ִ� ��
	const static SI32 MAX_ITEM_COUNT = 16;	

private:
	// ������ ��
	SI32	m_siCount;

	// ������ �迭
	#ifdef _SAFE_MEMORY
		NSafeTArray<CDormancyPointItem, MAX_ITEM_COUNT>		m_ItemArray;
	#else
		CDormancyPointItem	m_ItemArray[MAX_ITEM_COUNT];
	#endif

//�ɹ� �޼ҵ�
public:
	CDormancyPointItemMgr(void);
	~CDormancyPointItemMgr(void);

	//	������ ���� - ���� �а� �޸𸮿� ���
	BOOL	Create();

	// ������ ����ũ�� ���� �ϴ��� ���� 
	BOOL	IsExist(SI32 siUnique);

	// �޸� ���� ��� ������ 
	CDormancyPointItem *GetDormancyPointItem(SI32 siUnique);
	// �ε����� ������ ���� ���
	CDormancyPointItem *GetDormancyPointItemFromIndex(SI32 siIndex);
	
	// ����Ʈ ������ ���� ����
	SI32	GetCount();
};
