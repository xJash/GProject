// ItemInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GMTOOL.h"
#include "ItemInfoDlg.h"


// CItemInfoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CItemInfoDlg, CDialog)
CItemInfoDlg::CItemInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemInfoDlg::IDD, pParent)
{
	AfxInitRichEdit2(); 
}

CItemInfoDlg::~CItemInfoDlg()
{
}

void CItemInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CItemInfoDlg::SetInfoText(TCHAR *pszInfoText)
{

	CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_ITEMINFO);
	richEdit->SetWindowText(pszInfoText);
	//SetDlgItemText(IDC_RICHEDIT_ITEMINFO, strInfoText);
}

BEGIN_MESSAGE_MAP(CItemInfoDlg, CDialog)
END_MESSAGE_MAP()


// CItemInfoDlg �޽��� ó�����Դϴ�.
