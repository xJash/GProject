#pragma once


// CCharView ��ȭ �����Դϴ�.

class CCharView : public CDialog
{
	DECLARE_DYNAMIC(CCharView)

public:
	CCharView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCharView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHARVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMDblclkListname(NMHDR *pNMHDR, LRESULT *pResult);
};
