#pragma once


// CItemInfoDlg ��ȭ �����Դϴ�.

class CItemInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemInfoDlg)

public:
	CItemInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ITEMINFO };
	
	void SetInfoText(TCHAR *pszInfoText);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
