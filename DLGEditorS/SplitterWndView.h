#pragma once


#include "resource.h"
// CSplitterWndView �� ���Դϴ�.

class CSplitterWndView : public CFormView
{
	DECLARE_DYNCREATE(CSplitterWndView)

protected:
	CSplitterWndView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSplitterWndView();

public:
	enum { IDD = IDD_SPLITTERWNDVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


