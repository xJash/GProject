#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
/**************************************************************************************/
//
//	[�߰� : Ȳ���� 2007. 12. 20 ���� ���� ���丮 Ŭ���� �߰�.]
//
/**************************************************************************************/

class CNChartransformStroyDlg : public CDialogController
{ 
public:
	CNChartransformStroyDlg();
	~CNChartransformStroyDlg();

	void Init();
	void Destroy();
	void Create();
	void Action();

	static void CALLBACK StaticChartransformStroyDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NChartransformStroyDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


private:
	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siMouseOverIndex;
};

