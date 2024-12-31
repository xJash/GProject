// ItemExplain.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GoonzuUserlog.h"
#include "ItemExplain.h"


// CItemExplain ��ȭ �����Դϴ�.

IMPLEMENT_DYNCREATE(CItemExplain, CDHtmlDialog)

CItemExplain::CItemExplain(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CItemExplain::IDD, CItemExplain::IDH, pParent)
{
}

CItemExplain::~CItemExplain()
{
}

void CItemExplain::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ExplainEdit);
}

BOOL CItemExplain::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

BEGIN_MESSAGE_MAP(CItemExplain, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CItemExplain)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CItemExplain �޽��� ó�����Դϴ�.

HRESULT CItemExplain::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

HRESULT CItemExplain::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
