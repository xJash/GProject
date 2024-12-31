#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CEdit;
class CStatic;
class CList;
class COutLine;

struct HyungzoCriminalList;

class CNHyungzoCriminalListDlg : public CDialogController
{
public:

	CNHyungzoCriminalListDlg();
	~CNHyungzoCriminalListDlg();

	void Create();
	void Action();

	void Show();
	void Hide();

	static void CALLBACK StaticCallBackDialogNHyungzoCriminalListDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHyungzoCriminalListDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetEnableButton(BOOL flag);
	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ

	void ShowListDlg(HyungzoCriminalList* stHyungzoCriminalList);

public:

	CList*		m_pList;		// ����� ����Ʈ
	CButton*	m_pButton[2];   // 0: ���� ���� 1: Ǯ���ֱ�

	SI32		m_siSelectList;	// ����� �� �ε���
};