#include ".\dormancyequipitemreward.h"

#include "../common/char/CharCommon/Char-Common.h"

CDormancyEquipItemReward::~CDormancyEquipItemReward(void)
{
	if(NULL != m_pclDormancyEquipItemMgr)
	{
		delete m_pclDormancyEquipItemMgr;
	}
	if(NULL != m_pclDormancyBoxMgr)
	{
		delete m_pclDormancyBoxMgr;
	}
}

CDormancyEquipItemReward::CDormancyEquipItemReward()
{
	// ���� ���� ���� Ŭ����
	m_pclDormancyEquipItemMgr = NULL;
	// ���� ��� ������ ���� Ŭ����
	m_pclDormancyBoxMgr = NULL;
	// ���� ���� ��ü
	m_pclCommon = pclClient;
}

//����
BOOL	CDormancyEquipItemReward::Create()
{
	if(NULL != m_pclDormancyEquipItemMgr)
		return FALSE;
	if(NULL != m_pclDormancyBoxMgr)
		return FALSE;

	m_pclDormancyEquipItemMgr = new CDormancyEquipItemMgr();
	if(NULL == m_pclDormancyEquipItemMgr)
		return FALSE;
	if(!m_pclDormancyEquipItemMgr->Create())
		return FALSE;

	m_pclDormancyBoxMgr = new CDormancyBoxMgr(m_pclDormancyEquipItemMgr);
	if(NULL == m_pclDormancyBoxMgr)
		return FALSE;
	if(!m_pclDormancyBoxMgr->Create())
		return FALSE;

	return TRUE;
}

//���� ���ڿ� ��� �ִ� �������� �ε��� ���� ��� ����.
cltItemInfo* CDormancyEquipItemReward::GetItemInfoInBox(SI32 siBoxUnique, SI32 siIndex)
{
	if( NULL == m_pclDormancyBoxMgr)
		return NULL;
	if( NULL == m_pclDormancyEquipItemMgr)
		return NULL;

	CDormancyBox* pclDormancyBox = m_pclDormancyBoxMgr->GetDormancyBox(siBoxUnique);
	if(NULL == pclDormancyBox)
		return NULL;

	CDormancyEquipItem* pclDormancyEquipItem = pclDormancyBox->GetEquipItem(siIndex);
	if(NULL == pclDormancyEquipItem)
		return NULL;

	return m_pclCommon->pclItemManager->FindItemInfo(pclDormancyEquipItem->GetUnique());
}

//���� ���ڿ� ��� �ִ� �������� �ε��� ���� ��� ����.
SI32 CDormancyEquipItemReward::GetItemUniqueInBox(SI32 siBoxUnique, SI32 siIndex)
{
	if( NULL == m_pclDormancyBoxMgr)
		return -1;
	if( NULL == m_pclDormancyEquipItemMgr)
		return -1;

	CDormancyBox* pclDormancyBox = m_pclDormancyBoxMgr->GetDormancyBox(siBoxUnique);
	if(NULL == pclDormancyBox)
		return -1;

	CDormancyEquipItem* pclDormancyEquipItem = pclDormancyBox->GetEquipItem(siIndex);
	if(NULL == pclDormancyEquipItem)
		return -1;

	return pclDormancyEquipItem->GetUnique();
}

//��� ������ ��ȭ�ϱ�
BOOL	CDormancyEquipItemReward::UpgradeItemInven(cltCharCommon *pclChar)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclCommon)
		return FALSE;

	// ĳ������ �κ��丮�� ������
	cltPItemInfo &pclPItemInfo = pclChar->pclCI->clCharItem;

	// ������ �Ŵ���
	cltItemManagerCommon *pclItemManager = m_pclCommon->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;

	//	���� ������ ����
	cltItemInfo *pclDormancyItemInfo = NULL;

	cltItem *pclItem = NULL;
	for(SI32 siItemPos = 0 ; siItemPos < MAX_ITEM_PER_PERSON; siItemPos++)
	{
		pclItem = &pclPItemInfo.clItem[siItemPos];
		if( NULL == pclItem)
			continue;

		pclDormancyItemInfo = pclItemManager->FindItemInfo(pclItem->siUnique);
		if(NULL == pclDormancyItemInfo)
			continue;
		if(pclDormancyItemInfo->IsDormancy())
		{
			UpgradeItem(pclChar, pclItem->siUnique, siItemPos, pclDormancyItemInfo->siType);
		}		
	}
	return TRUE;
}

//��� ������ ��ȭ�ϱ�
BOOL	CDormancyEquipItemReward::UpgradeItem(cltCharCommon *pclChar, SI32 siItemUnique, SI32 siItemPos, SI32 siType)
{
	if( NULL == pclChar)
		return FALSE;
	if( (0 > siItemPos) || (siItemPos >= MAX_ITEM_PER_PERSON) )
		return FALSE;

	// �޸� ���� ��� ������ ����
	CDormancyEquipItem*	pclDormancyEquipItem = m_pclDormancyEquipItemMgr->GetDormancyEquipItem(siItemUnique);
	if(NULL == pclDormancyEquipItem)
		return FALSE;

	// ĳ������ �κ��丮�� ������
	cltPItemInfo &pclPItemInfo =  pclChar->pclCI->clCharItem;

	// ������ �Ŵ���
	cltItemManagerCommon *pclItemManager = m_pclCommon->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;

	// �޸� ���� ��� ������
	cltItem &pclItem = pclPItemInfo.clItem[siItemPos];
	
	// ���� �������� ���׷��̵� �� Ÿ�� ������ ����ũ
	SI32 siTargetItemUnique = 0;
	//	���� �������� ���׷��̵� �� Ÿ�� ������ ����
	cltItemInfo *pclTargetItemInfo = NULL;
	// ĳ���Ͱ� ���� ����
	SI32 siNextLevel = pclChar->pclCI->clIP.GetLevel() + 1;

	if( (siTargetItemUnique =  pclDormancyEquipItem->GetTargetItemUnique(siNextLevel)) == 0 )
	{
		return FALSE;
	}
	pclTargetItemInfo = pclItemManager->FindItemInfo(siTargetItemUnique);

	if(NULL == pclTargetItemInfo)
		return FALSE;

	switch(siType)
	{
		//��������� �� �ֱ�
	case ITEMTYPE_SWORD:				// ��
	case ITEMTYPE_SPEAR:				// â
	case ITEMTYPE_STAFF:				// ������
	case ITEMTYPE_AXE:					// ����
	case ITEMTYPE_BOW:					// Ȱ
	case ITEMTYPE_GUN:					// ��
		{
			pclItem.clItemWeapon.uiMinDamage = pclTargetItemInfo->clItem.clItemWeapon.uiMinDamage;
			pclItem.clItemWeapon.uiMaxDamage = pclTargetItemInfo->clItem.clItemWeapon.uiMaxDamage;
			pclItem.clItemWeapon.uiMag = pclTargetItemInfo->clItem.clItemWeapon.uiMag;
			break;
		}
		//�������� �� �ֱ�
	case ITEMTYPE_ARMOUR:				// ����
	case ITEMTYPE_BELT:					// �㸮��
	case ITEMTYPE_SHOES:				// �Ź�
	case ITEMTYPE_HELMET:				// ����
		{
			pclItem.clItemArmour.uiAC = pclTargetItemInfo->clItem.clItemArmour.uiAC;
			pclItem.clItemArmour.uiLuck = pclTargetItemInfo->clItem.clItemArmour.uiLuck;
			pclItem.clItemArmour.uiSkillUp = pclTargetItemInfo->clItem.clItemArmour.uiSkillUp;
			break;
		}
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}

//��� ������ ��ȭ�ϱ�(Ư�� ������)
BOOL	CDormancyEquipItemReward::UpgradeItemInfo(cltCharCommon *pclChar,cltItem *pclItem)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == pclItem)
		return FALSE;

	// �޸� ���� ��� ������ ����
	CDormancyEquipItem*	pclDormancyEquipItem = m_pclDormancyEquipItemMgr->GetDormancyEquipItem(pclItem->siUnique);
	if(NULL == pclDormancyEquipItem)
		return FALSE;

	// ������ �Ŵ���
	cltItemManagerCommon *pclItemManager = m_pclCommon->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;

	// ���� �������� ���׷��̵� �� Ÿ�� ������ ����ũ
	SI32 siTargetItemUnique = 0;
	//	���� �������� ���׷��̵� �� Ÿ�� ������ ����
	cltItemInfo *pclTargetItemInfo = NULL;

	if( (siTargetItemUnique =  pclDormancyEquipItem->GetTargetItemUnique(pclChar->pclCI->clIP.GetLevel())) == 0 )
	{
		return FALSE;
	}
	pclTargetItemInfo = pclItemManager->FindItemInfo(siTargetItemUnique);

	if(NULL == pclTargetItemInfo)
		return FALSE;

	switch(pclItem->GetType(pclItemManager))
	{
		//��������� �� �ֱ�
	case ITEMTYPE_SWORD:				// ��
	case ITEMTYPE_SPEAR:				// â
	case ITEMTYPE_STAFF:				// ������
	case ITEMTYPE_AXE:					// ����
	case ITEMTYPE_BOW:					// Ȱ
	case ITEMTYPE_GUN:					// ��
		{
			pclItem->clItemWeapon.uiMinDamage = pclTargetItemInfo->clItem.clItemWeapon.uiMinDamage;
			pclItem->clItemWeapon.uiMaxDamage = pclTargetItemInfo->clItem.clItemWeapon.uiMaxDamage;
			pclItem->clItemWeapon.uiMag = pclTargetItemInfo->clItem.clItemWeapon.uiMag;
			break;
		}
		//�������� �� �ֱ�
	case ITEMTYPE_ARMOUR:				// ����
	case ITEMTYPE_BELT:					// �㸮��
	case ITEMTYPE_SHOES:				// �Ź�
	case ITEMTYPE_HELMET:				// ����
		{
			pclItem->clItemArmour.uiAC = pclTargetItemInfo->clItem.clItemArmour.uiAC;
			pclItem->clItemArmour.uiLuck = pclTargetItemInfo->clItem.clItemArmour.uiLuck;
			pclItem->clItemArmour.uiSkillUp = pclTargetItemInfo->clItem.clItemArmour.uiSkillUp;
			break;
		}
	default:
		{
			return FALSE;
		}
	}

	return TRUE;
}


// �޸� ��� ���������� Ȯ���Ѵ�.
BOOL	CDormancyEquipItemReward::IsDormancyEquipItem(SI32 siItemUnique)
{
	if( NULL == m_pclDormancyEquipItemMgr)
		return FALSE;

	return m_pclDormancyEquipItemMgr->IsExist(siItemUnique);
	
	
}