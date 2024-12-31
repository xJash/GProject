//==========================================================================
// ����: 2010�ų��̺�Ʈ � ���̾�α� �ڽ�.
//==========================================================================
#pragma once

#include "../../Client/Client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "MsgType-System.h"


class CFortuneCookieDlg: public CDialogController
{
public:

	CFortuneCookieDlg();
	~CFortuneCookieDlg();

	void init();

	void Create();

	void Destroy();

	static void CALLBACK StaticNFortuneCookie_DlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NNFortuneCookie_InfoDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetText(TCHAR* pszText);

private:
	InterfaceFactory	m_InterfaceFactory;
	CEdit*				m_pEdit;
};




