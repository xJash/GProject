#pragma once


// CLogDlg ��ȭ �����Դϴ�.

class CLogDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogDlg)

public:
	CLogDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LOGDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
