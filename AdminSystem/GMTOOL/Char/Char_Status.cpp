// Char\Char_Status.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "CChar_Status.h"


// CChar_Status ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CChar_Status, CDHtmlDialog)

CChar_Status::CChar_Status(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CChar_Status::IDD, CChar_Status::IDH, pParent)
{
}

CChar_Status::~CChar_Status()
{
}

void CChar_Status::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CChar_Status::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

BEGIN_MESSAGE_MAP(CChar_Status, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CChar_Status)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CChar_Status �޽��� ó�����Դϴ�.

HRESULT CChar_Status::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

HRESULT CChar_Status::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
