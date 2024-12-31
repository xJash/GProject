#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
/**************************************************************************************/
//
//	[�߰� : Ȳ���� 2007. 12. 11 �ų� �̺�Ʈ ��ưâ Ŭ���� �߰�.]
//
/**************************************************************************************/

class CNNewYearDlg : public CDialogController
{ 
public:
	CNNewYearDlg();
	~CNNewYearDlg();

	void Init();
	void Destroy();
	void Create();
	void Action();

	static void CALLBACK StaticNewYearDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NNewYearDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


private:
	InterfaceFactory	m_InterfaceFactory;
};

