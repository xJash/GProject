#pragma once
#include "afxwin.h"

#include "../../NLib/NLua.h"

// CExeScript ��ȭ �����Դϴ�.

class CExeScript : public CDialog
{
	DECLARE_DYNAMIC(CExeScript)

public:
	CExeScript(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CExeScript();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_SCRIPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_Input;
	CEdit m_edit_Output;
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	NLua	m_clLua;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonExecute();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};
