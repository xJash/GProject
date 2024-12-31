#pragma once
#include "GMClientView.h"


// CGMClientFrame �������Դϴ�.

class CGMClientFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGMClientFrame)
protected:
	CGMClientFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CGMClientFrame();
	CGMClientView	m_wndView;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


