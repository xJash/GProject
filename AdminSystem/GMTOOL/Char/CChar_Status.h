#pragma once


// CChar_Status ��ȭ �����Դϴ�.

class CChar_Status : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CChar_Status)

public:
	CChar_Status(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChar_Status();
// ������
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHAR_STAUS, IDH = IDR_HTML_CHAR_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
