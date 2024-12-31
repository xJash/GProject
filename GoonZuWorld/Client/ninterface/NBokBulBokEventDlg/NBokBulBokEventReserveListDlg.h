#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../common/BokBulBokEventMgr/BokBulBokEvent.h"


class CBokBulBokEventReserveListDlg: public CDialogController
{
public:
	CBokBulBokEventReserveListDlg();
	~CBokBulBokEventReserveListDlg();

	void init();
	void Destroy();
	void Create();

	static void CALLBACK StaticBokBulBokEventReserveListDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NBokBulBokEventReserveListDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	InterfaceFactory	m_InterfaceFactory;
	
	//CReserveData			m_clReserveListInfo[MAX_RESERVATION_NUM];

	void GetReserveList( SI32 siPersonID );							//����Ʈ�� ���� �����͸� ��û�Ѵ�
	void SetReserveList();				
	
	void SetListData(TCHAR** ppWaitList);	//����Ʈ�� ������ �Է�
};





	
