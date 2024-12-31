// Id\IdView.cpp : ���� �����Դϴ�.
//

#include "../stdafx.h"
#include "../GMTOOL.h"
#include "IdView.h"
#include ".\idview.h"

#include "../MainFrm.h"
#include "../NGMClientProcess.h"
#include "../../MasterServer/ServerInfo.h"
#include "../../MasterServer/MasterMsg.h"


// CIdView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CIdView, CDialog)
CIdView::CIdView(CWnd* pParent /*=NULL*/)
	: CDialog(CIdView::IDD, pParent)
{
}

CIdView::~CIdView()
{
}

void CIdView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIdView, CDialog)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO5, OnCbnSelchangeCombo5)
END_MESSAGE_MAP()


// CIdView �޽��� ó�����Դϴ�.

void CIdView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CIdView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//DB REAL & LIKE
	CComboBox* pkComboBox_IdRealLike = (CComboBox*)GetDlgItem(IDC_ID_REALLIKE);
	if(pkComboBox_IdRealLike)
	{
		pkComboBox_IdRealLike->AddString("REAL");
		pkComboBox_IdRealLike->AddString("LIKE");

		pkComboBox_IdRealLike->SetCurSel(1);
	}

	CComboBox* pkComboBox_IdrName = (CComboBox*)GetDlgItem(IDC_ID_IDNAME);
	if(pkComboBox_IdrName)
	{
		pkComboBox_IdrName->AddString("ID");
		pkComboBox_IdrName->AddString("Server");

		pkComboBox_IdrName->SetCurSel(0);
	}
	
	//Į���߰�
	CListCtrl* pkListCtrl_ListID = (CListCtrl*)GetDlgItem(IDC_LISTID);
	if(pkListCtrl_ListID != NULL)
	{
		pkListCtrl_ListID->InsertColumn(0, "ID",			LVCFMT_LEFT,  100);
		pkListCtrl_ListID->InsertColumn(1, "SERVER",			LVCFMT_LEFT, 170);
		
		DWORD dwExStyle;
		dwExStyle = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

		pkListCtrl_ListID->SetExtendedStyle(dwExStyle);

		DWORD dwStyle = pkListCtrl_ListID->GetStyle();
		dwStyle = dwStyle | LVS_SHOWSELALWAYS;
		::SetWindowLong(pkListCtrl_ListID->m_hWnd, GWL_STYLE, dwStyle);
	}
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CIdView::OnCbnSelchangeCombo5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
