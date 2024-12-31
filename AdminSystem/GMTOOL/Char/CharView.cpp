// Char\CharView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "./CharView.h"
#include ".\charview.h"

#include "../MainFrm.h"
#include "../NGMClientProcess.h"
#include "../../MasterServer/ServerInfo.h"
#include "../../MasterServer/MasterMsg.h"

// CCharView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCharView, CDialog)
CCharView::CCharView(CWnd* pParent /*=NULL*/)
	: CDialog(CCharView::IDD, pParent)
{
}

CCharView::~CCharView()
{
}

void CCharView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCharView, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTNAME, OnNMDblclkListname)
END_MESSAGE_MAP()


// CCharView �޽��� ó�����Դϴ�.

void CCharView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CListCtrl* pkListCtrl_ListName = (CListCtrl*)GetDlgItem(IDC_LISTNAME);
	if(pkListCtrl_ListName == NULL)			return;

	CEdit* pkEdit_ID_EditList= (CEdit*)GetDlgItem(IDC_ID_EDITLIST);
	if(pkEdit_ID_EditList == NULL)			return;

	CRect	rc;
	GetClientRect(rc);

	CRect	listrc;
	pkListCtrl_ListName->GetWindowRect(listrc);
	ScreenToClient(listrc);
	




	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CCharView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
    //�޺��ڽ��� �����߰�
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	CComboBox* pComboBox_Server = (CComboBox*)GetDlgItem(IDC_CHARVIEW_COMBOBOX_SERVER);
	if(pComboBox_Server)
	{
		if(pMainFrame)
		{
			ServerInfo* pServerInfo = pMainFrame->m_pServerInfo;
			if(pServerInfo)
			{
				for(SI32 i=0; i<pServerInfo->GetWorldCount(); i++)
				{
					if(pServerInfo->m_gameWorldInfo[i].usWorldID > 0)
						pComboBox_Server->AddString(pServerInfo->m_gameWorldInfo[i].szWorldName);
				}				
			}
		}
	}

    //�޺��ڽ��� name�߰�.
	CComboBox* pkComboBox_CharName = (CComboBox*)GetDlgItem(IDC_CHARNAME);
	if(pkComboBox_CharName)
	{
		pkComboBox_CharName->AddString("ID");
		//pkComboBox_CharName->AddString("CharName");

		pkComboBox_CharName->SetCurSel(0);
	}
		CComboBox* pkComboBox_IdSingleList = (CComboBox*)GetDlgItem(IDC_CHAR_SINGLELIST);
	if(pkComboBox_CharName)
	{
		pkComboBox_IdSingleList->AddString("LIST");
		pkComboBox_IdSingleList->AddString("SINGLE");

		pkComboBox_IdSingleList->SetCurSel(0);
	}
	//Į��
	CListCtrl* pkListCtrl_ListName = (CListCtrl*)GetDlgItem(IDC_LISTNAME);
	if(pkListCtrl_ListName != NULL)
	{
		pkListCtrl_ListName->InsertColumn(0, "SERVER",			LVCFMT_LEFT, 100);
		pkListCtrl_ListName->InsertColumn(1, "CHARNAME",		LVCFMT_LEFT, 120);
		pkListCtrl_ListName->InsertColumn(2, "ACCOUNTID",		LVCFMT_LEFT, 120);

		DWORD dwExStyle;
		dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

		pkListCtrl_ListName->SetExtendedStyle(dwExStyle);

		DWORD dwStyle = pkListCtrl_ListName->GetStyle();
		dwStyle = dwStyle | LVS_SHOWSELALWAYS;
		::SetWindowLong(pkListCtrl_ListName->m_hWnd, GWL_STYLE, dwStyle);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CCharView::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame == NULL)				return;

	CListCtrl* pkListCtrl_ListName = (CListCtrl*)GetDlgItem(IDC_LISTNAME);
	if(pkListCtrl_ListName == NULL)		return;
	pkListCtrl_ListName->DeleteAllItems();

	CComboBox* pkComboBox_CharName = (CComboBox*)GetDlgItem(IDC_CHARNAME);
	if(pkComboBox_CharName == NULL)		return;
	int nSelection = pkComboBox_CharName->GetCurSel();

	int nServerID = 0;
	CComboBox* pkComboBox_ServerName = (CComboBox*)GetDlgItem(IDC_CHARVIEW_COMBOBOX_SERVER);
	if(pkComboBox_ServerName == NULL)		return;

	CString strInput;
	GetDlgItemText(IDC_EDIT_INPUT, strInput);
	if(strInput.GetLength() <= 0)			return;

	switch(nSelection)
	{
	case 1:
		{
		}
		break;
	}
}

void CCharView::OnNMDblclkListname(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	CMainFrame* pkMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pkMainFrame == NULL)								return;

	CListCtrl* pkListCtrl_ListName = (CListCtrl*)GetDlgItem(IDC_LISTNAME);
	if(pkListCtrl_ListName == NULL)						return;
	if(pkListCtrl_ListName->GetSelectedCount() <= 0)	return;

	POSITION pos = pkListCtrl_ListName->GetFirstSelectedItemPosition();
	if(pos)
	{
		int nItem = pkListCtrl_ListName->GetNextSelectedItem(pos);
		if(nItem < 0)					return;

		CString strServerName;
		CString strCharName;
		strServerName = pkListCtrl_ListName->GetItemText(nItem, 0);
		strCharName = pkListCtrl_ListName->GetItemText(nItem, 1);

		SI32 siServerID = pkMainFrame->GetGameServerID((TCHAR*)(LPCTSTR)strServerName);
		if(siServerID <= 0)				return;
	}
}
