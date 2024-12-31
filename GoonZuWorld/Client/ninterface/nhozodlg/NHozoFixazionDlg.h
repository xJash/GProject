#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class CEdit;
class CStatic;
class COutLine;

class CNHozoFixazionDlg : public CDialogController	// ö�ڰ� Ʋ������ �׳ɰ��� ��.��
{
public:

	CNHozoFixazionDlg();
	~CNHozoFixazionDlg();

	void Create( CControllerMgr *pParent );
	void Action();

	void Show();
	void Hide();

	static void CALLBACK StaticCallBackDialogNHozoFixazionDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHozoFixazionDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

public:
	
	COutLine*	m_pOutLine;
	CStatic*	m_pStatic[4];
	CEdit*		m_pEdit;

	CStatic*	m_pStatic_ankarandividend;
	CStatic*	m_pStatic_NONAME12;
	CStatic*	m_pStatic_NONAME13;
	CEdit*		m_pEdit_ankarandividend;
};