#pragma once

#include "../../InterfaceMgr/DialogController.h"

// �������� �ʴ��ϱ�
class CNInviteEmpireDlg : public CDialogController
{
public:

	InterfaceFactory	m_InterfaceFactory_;

	CNInviteEmpireDlg();
	~CNInviteEmpireDlg();

	void Create();

	CControllerObj* AddInterface( SI16 Type, SI32 TypeID );

	static void CALLBACK StaticCallBackDialogNInviteEmpireDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNInviteEmpireDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
};