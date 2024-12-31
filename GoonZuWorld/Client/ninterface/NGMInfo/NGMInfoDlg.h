// [����] GM���� ���õ� ���� ���â
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"


class CEdit;


class CNGMInfoDlg : public CDialogController
{

//-- �Լ� ����
public:
	CNGMInfoDlg();
	~CNGMInfoDlg();

	void Create();
	void Action();

	static void CALLBACK StaticNGMInfoDlgProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NGMInfoDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);


private:
	void WriteGMInfo();


//-- ���� ����
private:
	CEdit	*m_pEdit; 

	bool	m_bAutoUnblock;
	bool	m_bGodMode;
	bool	m_bOneKill;			// ��ų���

};
