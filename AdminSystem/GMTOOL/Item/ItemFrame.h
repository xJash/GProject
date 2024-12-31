#pragma once

#include "ItemView.h"


// CItemFrame �������Դϴ�.

class CItemFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CItemFrame)
protected:
	CItemFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CItemFrame();

	CItemView m_wndView;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


