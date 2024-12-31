// Notice\NoticeView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "NoticeView.h"
#include ".\noticeview.h"


// CNoticeView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNoticeView, CDialog)
CNoticeView::CNoticeView(CWnd* pParent /*=NULL*/)
	: CDialog(CNoticeView::IDD, pParent)
{
}

CNoticeView::~CNoticeView()
{
}

void CNoticeView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNoticeView, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNoticeView �޽��� ó�����Դϴ�.

BOOL CNoticeView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	CListCtrl* pkListCtrl_Notice_Listt = (CListCtrl*)GetDlgItem(IDC_NOTICE_LIST);
	if(pkListCtrl_Notice_Listt != NULL)
	{
		pkListCtrl_Notice_Listt->InsertColumn(0, "NUM",			LVCFMT_LEFT,  60);
		pkListCtrl_Notice_Listt->InsertColumn(1, "DATE",			LVCFMT_LEFT, 140);
		pkListCtrl_Notice_Listt->InsertColumn(2, "SERVER",		LVCFMT_LEFT, 100);
		pkListCtrl_Notice_Listt->InsertColumn(3, "COMMAND",		LVCFMT_LEFT, 140);
		pkListCtrl_Notice_Listt->InsertColumn(4, "USER",			LVCFMT_LEFT, 120);
		pkListCtrl_Notice_Listt->InsertColumn(5, "TARGET USER",	LVCFMT_LEFT, 120);
		pkListCtrl_Notice_Listt->InsertColumn(6, "ITEM UNIQUE",	LVCFMT_LEFT, 100);
		pkListCtrl_Notice_Listt->InsertColumn(7, "LOGTEXT",		LVCFMT_LEFT, 220);

		DWORD dwExStyle;
		dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

		pkListCtrl_Notice_Listt->SetExtendedStyle(dwExStyle);

		DWORD dwStyle = pkListCtrl_Notice_Listt->GetStyle();
		dwStyle = dwStyle | LVS_SHOWSELALWAYS;
		::SetWindowLong(pkListCtrl_Notice_Listt->m_hWnd, GWL_STYLE, dwStyle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CNoticeView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CNoticeView::PreTranslateMessage(MSG* pMsg)
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
