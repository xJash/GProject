#pragma once


// CSplitterWndViewToolBar ���Դϴ�.

class CSplitterWndViewToolBar : public CView
{
	DECLARE_DYNCREATE(CSplitterWndViewToolBar)

protected:
	CSplitterWndViewToolBar();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSplitterWndViewToolBar();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


