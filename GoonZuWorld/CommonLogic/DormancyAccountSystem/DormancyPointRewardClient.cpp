#include ".\dormancypointreward.h"

#include "../../Client/InterfaceMgr/DialogController.h"
#include "../../Client/ninterface/NDormancyAccount/NDormancyPointDlg.h"
#include "../common/char/CharClient/Char-Client.h"
#include "../../Client/Client.h"
#include "../common/char/CharManager/CharManager.h"
#include "../MsgType.h"
#include "../msg/MsgType-DormancyAccount.h"

CDormancyPointRewardClient::CDormancyPointRewardClient(void) : CDormancyPointReward()
{
	// Ŭ���̾�Ʈ ��ü
	m_pclClient = (cltClient *)pclClient;
}

CDormancyPointRewardClient::~CDormancyPointRewardClient(void)
{
	m_pclClient = NULL;
}

// �޸�������� �� ��� �޸� ����Ʈ ���̾�α׸� �����Ѵ�.
BOOL	CDormancyPointRewardClient::CreatePointDlg()
{
	// Ŭ���̾�Ʈ ĳ����
	cltCharClient *pclCharClient = (cltCharClient *)m_pclClient->pclCM->CR[1];

	if( NULL == pclCharClient)
		return FALSE;

	// �޸� ����Ʈ ���̾�α�
	CNDormancyPointDlg* pclDialog = (CNDormancyPointDlg*)m_pclClient->m_pDialog[ NDORMANCYPOINT_DLG ];
	if( NULL == pclDialog )
	{
		m_pclClient->CreateInterface(NDORMANCYPOINT_DLG, TRUE);
	}
	
	return TRUE;
}

// ����Ʈ ������ ���� ���Ӽ����� ��û
BOOL	CDormancyPointRewardClient::BuyPointItemRequest(SI32 siItemUnique)
{
	// Ŭ���̾�Ʈ ĳ����
	cltCharClient *pclCharClient = (cltCharClient *)m_pclClient->pclCM->CR[1];	

	if( NULL == pclCharClient)
		return FALSE;

	cltGameMsgRequest_DormancyBuyPoinItem clInfo(siItemUnique);
	cltMsg clMsg( GAMEMSG_REQUEST_DORMANCY_BUYPOINTITEM, sizeof(clInfo), (BYTE*)&clInfo );
	m_pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

	return TRUE;
}

// �޸� ����Ʈ ���� ����
BOOL	CDormancyPointRewardClient::RecvDormancyInfo(cltCharClient*	pclChar, SI32 siPoint, SI32 siReaminedPlayTime, BOOL bDormancyState,SI16 siStartedYear, SI16 siStartedMonth, SI16 m_siStartedDay)
{
	if( NULL == pclChar)
		return FALSE;

	CDormancyInfo &pclDormancyInfo = pclChar->pclCI->clDormancyInfo;
	
	// ������ �Է� 
	pclDormancyInfo.SetDormancyPoint(siPoint);
	pclDormancyInfo.SetDormancyState(bDormancyState);
	pclDormancyInfo.SetRemainedDormancyPlayTime(siReaminedPlayTime);
	pclDormancyInfo.GetStartedDate()->wYear = siStartedYear;
	pclDormancyInfo.GetStartedDate()->wMonth = siStartedMonth;
	pclDormancyInfo.GetStartedDate()->wDay = m_siStartedDay;

	CNDormancyPointDlg* pclDialog = (CNDormancyPointDlg*)m_pclClient->m_pDialog[ NDORMANCYPOINT_DLG ];

	if( FALSE == bDormancyState )
	{
		if(NULL != pclDialog)
			pclDialog->Destroy();
		return FALSE;
	}

	if( NULL == pclDialog )
	{
		m_pclClient->CreateInterface(NDORMANCYPOINT_DLG, TRUE);
		pclDialog = (CNDormancyPointDlg*)m_pclClient->m_pDialog[ NDORMANCYPOINT_DLG ];
		if(NULL == pclDialog )
			return FALSE;
	}
	else
	{
		pclDialog->Show(TRUE);
	}

	// ���� ����
	pclDialog->RefreshDormancyInfo();

	return TRUE;
}