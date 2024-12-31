#pragma once
#include "CharView.h"

class sResponse_GMC_UserCharInfo;

// CCharFrame �������Դϴ�.

class CCharFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CCharFrame)
protected:
	CCharFrame();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CCharFrame();
	
	CCharView m_wndView;

public:
	void AddCharName(TCHAR* pszServerName, TCHAR* pszCharName, TCHAR* pszAccountID);
	void SetCharInfo(sResponse_GMC_UserCharInfo* pkInfo);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

private:
	TCHAR*	MakeItemName(SI32 siUnique);
	TCHAR	m_szItemName[64];
};


