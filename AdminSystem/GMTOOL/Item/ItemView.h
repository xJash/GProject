#pragma once


// CItemView ��ȭ �����Դϴ�.

class CItemView : public CDialog
{
	DECLARE_DYNAMIC(CItemView)

public:
	CItemView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ITEMVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
