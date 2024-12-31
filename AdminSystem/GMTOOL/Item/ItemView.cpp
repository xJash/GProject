// Item\ItemView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "ItemView.h"
#include ".\itemview.h"


// CItemView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemView, CDialog)
CItemView::CItemView(CWnd* pParent /*=NULL*/)
	: CDialog(CItemView::IDD, pParent)
{
}

CItemView::~CItemView()
{
}

void CItemView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CItemView, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CItemView �޽��� ó�����Դϴ�.

void CItemView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect	rc;
	GetClientRect(rc);

}

BOOL CItemView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CListCtrl* pkListCtrl_List_ItemResult = (CListCtrl*)GetDlgItem(IDC_LIST_ITEMRESULT);
	if(pkListCtrl_List_ItemResult != NULL)
	{
		pkListCtrl_List_ItemResult->InsertColumn(0, "NUM",			LVCFMT_LEFT,  60);
		pkListCtrl_List_ItemResult->InsertColumn(1, "DATE",			LVCFMT_LEFT, 140);
		pkListCtrl_List_ItemResult->InsertColumn(2, "SERVER",		LVCFMT_LEFT, 100);
		pkListCtrl_List_ItemResult->InsertColumn(3, "COMMAND",		LVCFMT_LEFT, 140);
		pkListCtrl_List_ItemResult->InsertColumn(4, "USER",			LVCFMT_LEFT, 120);
		pkListCtrl_List_ItemResult->InsertColumn(5, "TARGET USER",	LVCFMT_LEFT, 120);
		pkListCtrl_List_ItemResult->InsertColumn(6, "ITEM UNIQUE",	LVCFMT_LEFT, 100);
		pkListCtrl_List_ItemResult->InsertColumn(7, "LOGTEXT",		LVCFMT_LEFT, 220);

		DWORD dwExStyle;
		dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

		pkListCtrl_List_ItemResult->SetExtendedStyle(dwExStyle);

		DWORD dwStyle = pkListCtrl_List_ItemResult->GetStyle();
		dwStyle = dwStyle | LVS_SHOWSELALWAYS;
		::SetWindowLong(pkListCtrl_List_ItemResult->m_hWnd, GWL_STYLE, dwStyle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

BOOL CItemView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			{
				return TRUE;
			}
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
