#pragma once


// CGuildView ��ȭ �����Դϴ�.

class CGuildView : public CDialog
{
	DECLARE_DYNAMIC(CGuildView)

public:
	CGuildView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGuildView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GUILDVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
