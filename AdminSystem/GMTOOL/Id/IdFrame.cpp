// Id\IdFrame.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "IdFrame.h"
#include ".\idframe.h"


// CIdFrame

IMPLEMENT_DYNCREATE(CIdFrame, CMDIChildWnd)

CIdFrame::CIdFrame()
{
}

CIdFrame::~CIdFrame()
{
}


BEGIN_MESSAGE_MAP(CIdFrame, CMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CIdFrame �޽��� ó�����Դϴ�.

int CIdFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (!m_wndView.Create(IDD_IDVIEW, this))	
	{
		return -1;
	}

	m_wndView.SetParent(this);

	RECT	rc;
	GetClientRect(&rc);
	m_wndView.MoveWindow(&rc, TRUE);

	return 0;
}

void CIdFrame::OnDestroy()
{
	CMDIChildWnd::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CIdFrame::OnSetFocus(CWnd* pOldWnd)
{
	CMDIChildWnd::OnSetFocus(pOldWnd);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_wndView.SetFocus();
}

void CIdFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWnd::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(m_wndView.m_hWnd != NULL)
	{
		CRect	rc;
		GetClientRect(rc);

		m_wndView.MoveWindow(rc);
	}
}

BOOL CIdFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if ( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style =	WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX ;//| WS_MAXIMIZE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}
