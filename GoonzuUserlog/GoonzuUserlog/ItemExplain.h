#pragma once
#include "afxwin.h"


// CItemExplain ��ȭ �����Դϴ�.

class CItemExplain : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CItemExplain)

public:
	CItemExplain(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CItemExplain();
// ������
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2, IDH = IDR_HTML_ITEMEXPLAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CEdit m_ExplainEdit;
};
