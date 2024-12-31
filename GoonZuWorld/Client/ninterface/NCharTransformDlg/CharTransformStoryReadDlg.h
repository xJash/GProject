#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
/**************************************************************************************/
//
//	[�߰� : Ȳ���� 2007. 12. 20 ���� ���� ���丮 Ŭ���� �߰�.]
//
/**************************************************************************************/

class CNChartransformStroyReadDlg : public CDialogController
{ 
public:
	CNChartransformStroyReadDlg();
	~CNChartransformStroyReadDlg();

	void Init();
	void Destroy();
	void Create();
	void Action();

	static void CALLBACK StaticChartransformStroyReadDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NChartransformStroyReadDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


private:
	InterfaceFactory	m_InterfaceFactory;
};

