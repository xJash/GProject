// MainFrm.h : CMainFrame Ŭ������ �������̽�
//


#pragma once

#include "SplitterWnd_Base.h"
#include "SplitterWndView.h"
#include "SplitterWndViewToolBar.h"


class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	
// Ư��
public:

// �۾�
public:

// ������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
public:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
	// SplitterWnd �߰�
	CSplitterWnd_Base* m_pSplitterWnd;
	CSplitterWnd_Base* m_pSplitterWnd2;
	
	int m_nViewNo[10];

protected:
	CDialogBar m_wndDialogBar;

// �޽��� �� �Լ��� �����߽��ϴ�.
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnMove(int x, int y);
};


