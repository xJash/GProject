#include ".\dormancypointreward.h"

#include "../common/char/CharCommon/Char-Common.h"
CDormancyPointReward::CDormancyPointReward(void)
{
	// ����Ʈ ������ ���� Ŭ����
	m_pclDormancyPointItemMgr = NULL;
	// ���� ���� ��ü
	m_pclCommon = pclClient;
}

CDormancyPointReward::~CDormancyPointReward(void)
{
	if(NULL != m_pclDormancyPointItemMgr)
	{
		delete m_pclDormancyPointItemMgr;
		m_pclDormancyPointItemMgr = NULL;
	}
}

//����
BOOL		CDormancyPointReward::Create()
{
	if(NULL != m_pclDormancyPointItemMgr)
		return FALSE;

	m_pclDormancyPointItemMgr = new CDormancyPointItemMgr();
	if(NULL == m_pclDormancyPointItemMgr)
		return FALSE;
	if(!m_pclDormancyPointItemMgr->Create())
		return FALSE;

	return TRUE;
}

//�ε����� ������ ������ �˾� ����
cltItemInfo	*CDormancyPointReward::GetItemInfo(SI32 siIndex)
{
	if( NULL == m_pclDormancyPointItemMgr)
		return NULL;
	if( NULL == m_pclCommon->pclItemManager)
		return NULL;

	CDormancyPointItem *pclPointItem = m_pclDormancyPointItemMgr->GetDormancyPointItemFromIndex(siIndex);
	if( NULL == pclPointItem)
		return NULL;

	return m_pclCommon->pclItemManager->FindItemInfo(pclPointItem->GetUnique());
}

//�ε����� ������ ����ũ�� �˾� ����.
SI32		CDormancyPointReward::GetItemUnique(SI32 siIndex)
{
	SI32 siReturnValue = 0;
	cltItemInfo	*pclItemInfo = GetItemInfo(siIndex);
	if(NULL != pclItemInfo)
		siReturnValue = pclItemInfo->clItem.siUnique;

	return siReturnValue;
}

//����Ʈ ������ ���� ����
SI32		CDormancyPointReward::GetItemCount()
{
	if( NULL == m_pclDormancyPointItemMgr)
		return 0;
	return m_pclDormancyPointItemMgr->GetCount();
}

//�������� �޸� ����Ʈ�� �Ŵ����� �ε����� �˾Ƴ���.
SI32		CDormancyPointReward::GetItemPoint(SI32 siIndex)
{
	if( NULL == m_pclDormancyPointItemMgr)
		return -1;

	CDormancyPointItem *pclPointItem = m_pclDormancyPointItemMgr->GetDormancyPointItemFromIndex(siIndex);
	if( NULL == pclPointItem)
		return -1;
	
	return pclPointItem->GetPoint();
}