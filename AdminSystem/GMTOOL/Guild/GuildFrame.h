#pragma once
#include "GuildView.h"


// CGuildFrame �������Դϴ�.

class CGuildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGuildFrame)
protected:
	CGuildFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CGuildFrame();
	CGuildView m_wndView;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


