#pragma once


// CNoticeVirw ��ȭ �����Դϴ�.

class CNoticeVirw : public CDialog
{
	DECLARE_DYNAMIC(CNoticeVirw)

public:
	CNoticeVirw(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CNoticeVirw();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_NOTICEVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
