#pragma once


// CBlockView ��ȭ �����Դϴ�.

class CBlockView : public CDialog
{
	DECLARE_DYNAMIC(CBlockView)

public:
	CBlockView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBlockView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BLOCKVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
