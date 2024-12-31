#pragma once
#include "IdView.h"


// CIdFrame �������Դϴ�.

class CIdFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CIdFrame)
protected:
	CIdFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CIdFrame();
	CIdView	m_wndView;

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


