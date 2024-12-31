// Guild\GuildView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "GuildView.h"
#include ".\guildview.h"


// CGuildView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CGuildView, CDialog)
CGuildView::CGuildView(CWnd* pParent /*=NULL*/)
	: CDialog(CGuildView::IDD, pParent)
{
}

CGuildView::~CGuildView()
{
}

void CGuildView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGuildView, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGuildView �޽��� ó�����Դϴ�.

BOOL CGuildView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CListCtrl* pkListCtrl_GuildL = (CListCtrl*)GetDlgItem(IDC_LIST_GUILDL);
	if(pkListCtrl_GuildL != NULL)
	{
		pkListCtrl_GuildL->InsertColumn(0, "NUM",			LVCFMT_LEFT,  60);
		pkListCtrl_GuildL->InsertColumn(1, "DATE",			LVCFMT_LEFT, 140);
		pkListCtrl_GuildL->InsertColumn(2, "SERVER",		LVCFMT_LEFT, 100);

		DWORD dwExStyle;
		dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

		pkListCtrl_GuildL->SetExtendedStyle(dwExStyle);

		DWORD dwStyle = pkListCtrl_GuildL->GetStyle();
		dwStyle = dwStyle | LVS_SHOWSELALWAYS;
		::SetWindowLong(pkListCtrl_GuildL->m_hWnd, GWL_STYLE, dwStyle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CGuildView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect	rc;
	GetClientRect(rc);
}



BOOL CGuildView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�
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
