#include ".\dormancyequipitemreward.h"

#include "../CommonLogic/MsgRval-Define.h"
#include "../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../Server/Server.h"

CDormancyEquipItemRewardServer::CDormancyEquipItemRewardServer(void) : CDormancyEquipItemReward()
{
	m_pclServer = (cltServer *)pclClient;
}

CDormancyEquipItemRewardServer::~CDormancyEquipItemRewardServer(void)
{
}

//��� ������ ����
BOOL	CDormancyEquipItemRewardServer::GiveItemToPlayer(SI32 siBoxUnique, SI32 siItemUnique, SI32 siIBoxPos, cltCharServer *pclChar, SI32 siItemIndex)
{
	if( NULL == pclChar)
		return FALSE;
	if( (0 > siIBoxPos) || siIBoxPos >= MAX_ITEM_PER_PERSON)
		return FALSE;

	CDormancyBox*	pclDormancyBox = NULL;
	CDormancyEquipItem*	pclDormancyEquipItem = NULL;
	const SI32	ITEMNUM = 1;

	//	���� �ڽ� ���
	if( NULL == (pclDormancyBox = m_pclDormancyBoxMgr->GetDormancyBox(siBoxUnique)))
	{
		return FALSE;
	}
	
	//	���� �ڽ� ���� ��� ������ ����
	if( NULL == (pclDormancyEquipItem = pclDormancyBox->GetEquipItem(siItemIndex)))
	{
		return FALSE;
	}

	SI16 brareswitch = 0;
	cltItem clSelectedItem;					// ������ ������ 
	clSelectedItem.Init();
	
	// ������ �Ⱓ�� ��� ����
	// ������ ���Ⱓ�� ���������� �����۾�
	cltItemInfo* pclItemInfo = m_pclServer->pclItemManager->FindItemInfo(siItemUnique);
	if( NULL == pclItemInfo )

		return FALSE;

	cltItem *pclItem = &pclItemInfo->clItem;
	// ������ ���Ⱓ
	UI32 uiUsedate = pclItem->uiDateUseDay;

	if( FALSE == m_pclServer->pclItemManager->MakeRandItemUnique(siItemUnique, &clSelectedItem, 0, 0, &brareswitch,0,0,0,0,0,uiUsedate))
		return FALSE;

	clSelectedItem.SetItemNum( ITEMNUM );

	// ������ ���׷��̵�
	UpgradeItemInfo(pclChar, &clSelectedItem);

	// �к� ���
	clSelectedItem.CancellationSealingUp( m_pclServer->sTime );

	//------------------------------------------
	// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//------------------------------------------
	SI16 siInvPos;
	cltItem clToItem;
	SI32 rtnvalue;
	if(pclChar->CanAddInv(INVMODE_ALL, &clSelectedItem, &siInvPos, &clToItem, &rtnvalue) == false)
	{
		m_pclServer->SendServerResponseMsg(0, SRVAL_FAIL_IS_FULLIVEN, 100, 0, pclChar->GetID());
		return false;
	}

	// ĳ���� �κ��丮�� �ִ� �ڽ� ������
	cltItem* pclBoxItem = &pclChar->pclCI->clCharItem.clItem[siIBoxPos];
	cltItem clUsedBoxItem;
	clUsedBoxItem.Set(pclBoxItem);
	clUsedBoxItem.SetItemNum(ITEMNUM);

	// DB�� '���� ����' ��û
	sDBRequest_OpenTreasureBox clMsg( pclChar->pclCI->GetPersonID(), siIBoxPos, &clUsedBoxItem, 0, NULL, siInvPos, &clSelectedItem, m_pclServer->pclItemManager->CanPile(clSelectedItem.siUnique), clSelectedItem.IsCreateSID(m_pclServer->pclItemManager), false);
	m_pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	
	return TRUE;
}

//�ý��� ���� : ��� ���� ���� 2�� �ֱ�
BOOL	CDormancyEquipItemRewardServer::GiveEquipBox(cltCharServer *pclCharServer)
{
	if ( NULL == pclCharServer)
		return FALSE;
	if ( NULL == m_pclDormancyBoxMgr)
		return FALSE;
	if ( NULL == m_pclServer->pclGameDBProcess)
		return FALSE;
	
	// �޸� ���� ���°� �ƴ϶�� ���� ���� �ʴ´�.
	CDormancyInfo &rclDormancyInfo = pclCharServer->pclCI->clDormancyInfo;
	if( FALSE == rclDormancyInfo.GetDormancyState())
		return FALSE;

	TCHAR*	pReasonText = GetTxtFromMgr( 40091 );	// �����ϴ� ����

	cltSystemRewardInfo		clInfo;			// ������ ���� ���� ����
	clInfo.m_siIndex = SystemRewardInfoType_DormancyEquipItem; // �ý��� ���� ���� �ε���
	// ���� ��¥
	clInfo.m_sGiveTime		= m_pclServer->sTime;
	TimeAddDate(&clInfo.m_sGiveTime, CDormancyBox::GIVESYSTEMDATE, &clInfo.m_sExpireTime);
	// ���� ����
	if ( pReasonText )
	{
		StringCchCopy( clInfo.m_szReason, 256, pReasonText );
	}

	// �ڽ� ������
	CDormancyBox *pclBox = NULL;
	// ������ ���� �ε���
	SI32 ref = 0;
	// ���� ������ 
	cltItem *pclRewardItem = NULL;

	// ���� �ؾ� �� �ڽ� �����۵��� ���� �˻�
	BOOL bError = FALSE;
	for(SI32 i = 0 ; i < m_pclDormancyBoxMgr->GetCount(); i++)
	{	
		if(NULL == m_pclDormancyBoxMgr->GetDormancyBoxByIndex(i))
		{
			bError = TRUE;
		}
	}
	
	// �˻� �� �̻� ���� ��
	if ( FALSE == bError)
	{
		cltItemInfo* pclItemInfo = NULL;
		cltItem *pclItem = NULL;
		for(SI32 i = 0 ; i < m_pclDormancyBoxMgr->GetCount(); i++)
		{	
			pclBox = m_pclDormancyBoxMgr->GetDormancyBoxByIndex(i);
			// ������
			pclItemInfo = m_pclServer->pclItemManager->FindItemInfo(pclBox->GetUnique());
			if( NULL == pclItemInfo )
				return FALSE;

			pclRewardItem = &pclItemInfo->clItem;
			clInfo.m_clItem.Set( pclRewardItem );

			// �������� ���� �϶�� ��û
			sDBRequest_GiveSystemReward clMsgReward( GIVEREWARD_SERVER, pclCharServer->pclCI->GetPersonID(), pclCharServer->GetID(), &clInfo );
			m_pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsgReward);
		}
		// �������� ���޵Ǿ��ٴ� �޽����� �����
		m_pclServer->SendServerResponseMsg( 0, SRVAL_REWARDITEM_FOR_DORMANCYEQUIPBOX, 0, 0, pclCharServer->GetID() );

		return TRUE;
	}
	return FALSE;
}

//��� ������ ��ȭ�ϱ�
BOOL	CDormancyEquipItemRewardServer::UpgradeItem(cltCharCommon *pclChar, SI32 siItemUnique, SI32 siItemPos, SI32 siType)
{
	if( NULL == pclChar)
		return FALSE;
	if( NULL == m_pclServer->pclGameDBProcess)
		return FALSE;

	// �޸� ���� ��� ������ ����
	CDormancyEquipItem*	pclDormancyEquipItem = m_pclDormancyEquipItemMgr->GetDormancyEquipItem(siItemUnique);
	if(NULL == pclDormancyEquipItem)
		return FALSE;
	// ������ �Ŵ���
	cltItemManagerCommon *pclItemManager = m_pclServer->pclItemManager;
	if( NULL == pclItemManager)
		return FALSE;


	//================= 1. ���׷��̵��� �κ� ���� ������ =========================================================//
	// ĳ������ �κ��丮�� ������
	cltPItemInfo &rclPItemInfo =  pclChar->pclCI->clCharItem;
	// �޸� ���� ��� ������
	cltItem &rclItem = rclPItemInfo.clItem[siItemPos];

	//================= 2. �޸� ������ ���� ���� ================================================================//
	cltItem clItemSource;
	clItemSource.Set(&rclItem);

	//================= 3. Ÿ�� ������ ���ϱ�====================================================================// 
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
	// Ÿ�� ������
	cltItem &rclTargetItem = pclTargetItemInfo->clItem;

	//================= 4. ������ ���� �ɷ�ġ ���� �˻� & �޸� ������ �ɷ�ġ ���׷��̵�=====================// 
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
			if((rclItem.clItemWeapon.uiMinDamage == rclTargetItem.clItemWeapon.uiMinDamage)
				&& (rclItem.clItemWeapon.uiMaxDamage == rclTargetItem.clItemWeapon.uiMaxDamage)
				&& (rclItem.clItemWeapon.uiMag == rclTargetItem.clItemWeapon.uiMag))
			{
				return FALSE;
			}

			clItemSource.clItemWeapon.uiMinDamage = rclTargetItem.clItemWeapon.uiMinDamage;
			clItemSource.clItemWeapon.uiMaxDamage = rclTargetItem.clItemWeapon.uiMaxDamage;
			clItemSource.clItemWeapon.uiMag = rclTargetItem.clItemWeapon.uiMag;
			break;
		}
		//�������� �� �ֱ�
	case ITEMTYPE_ARMOUR:				// ����
	case ITEMTYPE_BELT:					// �㸮��
	case ITEMTYPE_HELMET:				// ����
		{
			if((rclItem.clItemArmour.uiAC == rclTargetItem.clItemArmour.uiAC)
				&& (rclItem.clItemArmour.uiLuck == rclTargetItem.clItemArmour.uiLuck)
				&& (rclItem.clItemArmour.uiSkillUp == rclTargetItem.clItemArmour.uiSkillUp))
			{
				return FALSE;
			}

			clItemSource.clItemArmour.uiAC = pclTargetItemInfo->clItem.clItemArmour.uiAC;
			clItemSource.clItemArmour.uiLuck = pclTargetItemInfo->clItem.clItemArmour.uiLuck;
			clItemSource.clItemArmour.uiSkillUp = pclTargetItemInfo->clItem.clItemArmour.uiSkillUp;
			break;
		}
	case ITEMTYPE_SHOES:				// �Ź�
		{
			if((rclItem.clItemShoes.uiAC == rclTargetItem.clItemShoes.uiAC)
				&& (rclItem.clItemShoes.uiMoveSpeed == rclTargetItem.clItemShoes.uiMoveSpeed))
			{
				return FALSE;
			}

			clItemSource.clItemShoes.uiAC = pclTargetItemInfo->clItem.clItemShoes.uiAC;
			clItemSource.clItemShoes.uiMoveSpeed = pclTargetItemInfo->clItem.clItemShoes.uiMoveSpeed;
			break;
		}
	default:
		{
			return FALSE;
		}
	}

	//================= 6. DB�� ������ ���� �޽��� ����========================================================// 
	sDBRequest_ExchangeItem clSendMsg(pclChar->pclCI->GetPersonID(), siItemPos, &rclItem, &clItemSource, EXCHANGEITEM_REASON_DORMANCY);
	m_pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clSendMsg);

	return TRUE;
}