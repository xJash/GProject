#include ".\dormancyequipitemreward.h"
#include "../../Client/InterfaceMgr/DialogController.h"
#include "../../Client/ninterface/NDormancyAccount/NDormancyArmourBoxDlg.h"
#include "../../Client/Client.h"
#include "../CommonLogic/Msg/MsgType-DormancyAccount.h"

CDormancyEquipItemRewardClient::CDormancyEquipItemRewardClient(void)  : CDormancyEquipItemReward()
{
	m_pclClient = (cltClient *)pclClient;
}

CDormancyEquipItemRewardClient::~CDormancyEquipItemRewardClient(void)
{
	m_pclClient = NULL;
}

//	������ ����
BOOL	CDormancyEquipItemRewardClient::SelectItemInBox(SI32 siItemIndex,SI32 siBoxUnique, SI32 siBoxPos)
{
	CDormancyBox*	pclDormancyBox = NULL;
	CDormancyEquipItem*	pclDormancyEquipItem = NULL;

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

	SI32 siDlgIndex = 0;

	//	���� ����(��)
	switch(siBoxUnique)
	{
	case	ITEMUNIQUE(13353):
		{
			siDlgIndex = NDORMANCYARMOURBOX_DLG;
			break;
		}
	case	ITEMUNIQUE(13354):
		{
			siDlgIndex = NDORMANCYWEAPONBOX_DLG;
			break;
		}
	default:
		{
			return FALSE;
		}
	}

	// ���� ���� ���̾�α�
	CDialogController* pclDialog = (CDialogController*)m_pclClient->m_pDialog[ siDlgIndex ];
	if(NULL == pclDialog)
		return FALSE;

	// ���̾�α� ����
	((CNDormancyArmourBoxDlg*)pclDialog)->Destroy();

	cltGameMsgRequest_DormancyTakeOutEquipItemInBox clInfo(siBoxUnique,siBoxPos,pclDormancyEquipItem->GetUnique(),siItemIndex);
	cltMsg clMsg( GAMEMSG_REQUEST_DORMANCY_TAKEOUTEQUIPITEMINBOX, sizeof(clInfo), (BYTE*)&clInfo );
	m_pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
	
	
	return TRUE;
}

//��� ������ ����
BOOL	CDormancyEquipItemRewardClient::UseBox(SI32 siItemUnique, SI32 siPos)
{
	CDialogController* pclDialog = NULL;

	SI32 siDlgIndex = 0;

	//	���� ����(��)
	switch(siItemUnique)
	{
	case	ITEMUNIQUE(13353):
		{
			siDlgIndex = NDORMANCYARMOURBOX_DLG;
			break;
		}
	case	ITEMUNIQUE(13354):
		{
			siDlgIndex = NDORMANCYWEAPONBOX_DLG;
			break;
		}
	default:
		{
			return FALSE;
		}
	}

	pclDialog = (CDialogController*)m_pclClient->m_pDialog[ siDlgIndex ];
	if( NULL == pclDialog )
	{
		m_pclClient->CreateInterface(siDlgIndex, TRUE);
		pclDialog = (CDialogController*)m_pclClient->m_pDialog[ siDlgIndex ];
		if( NULL == pclDialog )
		{
			return FALSE;
		}

		((CNDormancyArmourBoxDlg*)pclDialog)->SetBoxInfo(siItemUnique, siPos);
	}
	else
	{
		pclDialog->Show(TRUE);
	}
	
	return TRUE;
}