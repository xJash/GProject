#ifndef	__HUNTQUESTITEMMGR_H__
#define __HUNTQUESTITEMMGR_H__

#include <Directives.h>
#include "../../Common/CommonHeader.h"

const SI32 MAX_HUNTQUESTITEM_UNIQUE_NUM = 30;	//	����Ʈ ����ũ MAX NUM
const SI32 MAX_HUNTQUESTITEM_UNIT_NUM	= 10;	//	������������ MAX NUM



struct HuntQuestItem_Unit
{
	SI32	m_siMonsterKind;
	SI32	m_siItemUnique;
	SI32	m_siRandomRate;

	HuntQuestItem_Unit(){ZeroMemory(this, sizeof(HuntQuestItem_Unit));}
};

struct HuntQuestItem_Unit_Info
{
	SI32	m_siQuestUnique;
	
	HuntQuestItem_Unit	m_HuntQuestItem_Unit[MAX_HUNTQUESTITEM_UNIT_NUM];

	HuntQuestItem_Unit_Info(){ZeroMemory(this, sizeof(HuntQuestItem_Unit_Info));}
};

class CHuntQuestItemMgr
{
private:
	SI32						m_siQuestUniqueNum;

	HuntQuestItem_Unit_Info		m_HuntQuestItem_Unit_info[MAX_HUNTQUESTITEM_UNIQUE_NUM];		// ����Ʈ �������� ���� ����
	
public:
	bool				Initialize();				//	�Ŵ��� �ʱ�ȭ
	bool				LoadHuntQuestItemData();	//	����Ʈ������ Resource Load

	HuntQuestItem_Unit* FindQuestItem(SI32 siQuestUnique, SI32 siMonsterKind);

public:
	CHuntQuestItemMgr();
	~CHuntQuestItemMgr();
};

#endif //__HUNTQUESTITEMMGR_H__