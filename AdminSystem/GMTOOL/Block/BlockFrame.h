#pragma once
#include "BlockView.h"


// CBlockFrame �������Դϴ�.

class CBlockFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBlockFrame)
protected:
	CBlockFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CBlockFrame();
	CBlockView m_wndView;


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


