// SplitterWndViewToolBar.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DLGEditorS.h"
#include "SplitterWndViewToolBar.h"


// CSplitterWndViewToolBar

IMPLEMENT_DYNCREATE(CSplitterWndViewToolBar, CView)

CSplitterWndViewToolBar::CSplitterWndViewToolBar()
{
}

CSplitterWndViewToolBar::~CSplitterWndViewToolBar()
{
}

BEGIN_MESSAGE_MAP(CSplitterWndViewToolBar, CView)
END_MESSAGE_MAP()


// CSplitterWndViewToolBar �׸����Դϴ�.

void CSplitterWndViewToolBar::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CSplitterWndViewToolBar �����Դϴ�.

#ifdef _DEBUG
void CSplitterWndViewToolBar::AssertValid() const
{
	CView::AssertValid();
}

void CSplitterWndViewToolBar::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG


// CSplitterWndViewToolBar �޽��� ó�����Դϴ�.
