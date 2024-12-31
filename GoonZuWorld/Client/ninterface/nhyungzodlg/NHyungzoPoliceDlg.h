#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CEdit;
class CStatic;
class CList;
class COutLine;

struct HyungzoPoliceList;
class CNHyungzoCriminalListDlg;

class CNHyungzoPoliceDlg : public CDialogController
{
public:

	CNHyungzoPoliceDlg();
	~CNHyungzoPoliceDlg();

	void Create( CControllerMgr *pParent );
	void Action();

	void Show();
	void Hide();

	static void CALLBACK StaticCallBackDialogNHyungzoPoliceDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNHyungzoPoliceDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void SetEnableButton(BOOL flag);
	void EnableButton(CButton* pButton, BOOL Flag);	// ��ư Ȱ��ȭ ��Ȱ��ȭ

	void ShowListDlg(HyungzoPoliceList* stHyungzoPoliceList);

public:

	CEdit*		m_pEdit[3];		// ������ ����� ��� �̸�����
	CList*		m_pList;		// ���� ����Ʈ
	CButton*	m_pButton[4];   // 0: ���� ���� 1: ���� 2: ����� ��� ���� 3: �Ű��ϱ�
	CStatic*	m_pStatic[5];
	COutLine*   m_pOutLine;

	SI32		m_siSelectList;
};