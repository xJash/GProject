#pragma once


// CNoticeView ��ȭ �����Դϴ�.

class CNoticeView : public CDialog
{
	DECLARE_DYNAMIC(CNoticeView)

public:
	CNoticeView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNoticeView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NOTICEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
