#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../Common/SystemReward/SystemReward.h"

class CNSystemRewardListDlg : public CDialogController
{
private:
	SI32 m_siCurPage;
	SI32 m_siMaxPage;

public:
	CNSystemRewardListDlg();
	~CNSystemRewardListDlg();

	void Init();
	void Destroy();

	void Create();

	static void CALLBACK StaticSystemRewardListDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NSystemRewardListDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	InterfaceFactory	m_InterfaceFactory;

	cltSystemRewardInfo	m_clSystemRewardInfo[MAX_SYSTEMREWARD_LIST];

	void SetRewardList( cltSystemRewardInfo* pclinfo );				//����Ʈ�� ������ �Է�.
	void RequestRewardList();			//���� ����Ʈ�� ��û�Ѵ�.
	void RequestRecieve();				//������ �޾ƿ´�.
	void ShowDetailInfo();

	void ExchangeStock();

	void UpdatePageInfo(SI32  siCurPage, SI32  siMaxPage);				// [��ȣ_NHN->NDOORS] ���� ����¡ �߰�
};