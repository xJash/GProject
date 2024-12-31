// GoonzuUserlogDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
class CGoonzuLogView;

enum SERVERSELECT
{
	NDOORS,
	NETMARBLE
};

// CGoonzuUserlogDlg ��ȭ ����
class CGoonzuUserlogDlg : public CDialog
{
// ����
public:
	CGoonzuUserlogDlg(CWnd* pParent = NULL);	// ǥ�� ������
	void ExitProcess();

// ��ȭ ���� ������
	enum { IDD = IDD_GOONZUUSERLOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����

	


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	char UserID[264];
	char PassWord[64];
	CGoonzuLogView *m_pGoonzuLogView;
	afx_msg void OnBnClickedOk();
	CEdit m_NameEdit;
	CEdit m_PassWord;
//	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	CComboBox m_cbServerSelect;
};
