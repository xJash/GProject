#pragma once


// CServerStateDlg ��ȭ �����Դϴ�.

class CServerStateDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerStateDlg)

public:
	CServerStateDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CServerStateDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERVERSTATEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
