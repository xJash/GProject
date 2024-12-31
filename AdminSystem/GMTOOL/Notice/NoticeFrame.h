#pragma once
#include "NoticeView.h"

// CNoticeFrame �������Դϴ�.

class CNoticeFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CNoticeFrame)
protected:
	CNoticeFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CNoticeFrame();
	CNoticeView	m_wndView;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


