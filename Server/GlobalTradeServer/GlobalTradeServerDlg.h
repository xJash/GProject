// GlobalTradeServerDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"


// CGlobalTradeServerDlg ��ȭ ����
class CGlobalTradeServerDlg : public CDialog
{
// ����
public:
	CGlobalTradeServerDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_GLOBALTRADESERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����

	BOOL	m_bWorkRun;


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
	afx_msg void OnTimer(UINT nIDEvent);
	CListCtrl m_ListCtrl;
};
