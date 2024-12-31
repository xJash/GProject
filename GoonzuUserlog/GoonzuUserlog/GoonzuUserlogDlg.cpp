// GoonzuUserlogDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GoonzuUserlog.h"
#include "GoonzuUserlogDlg.h"
#include ".\goonzuuserlogdlg.h"
#include "ODBC/RichODBC.h"
#include "VillageManager/VillageManager.h"
#include "item/itemcommon/textmgr.h"

#include "GoonzuLogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern cltTextMgr g_pTextMgr;
// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

	// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGoonzuUserlogDlg ��ȭ ����



CGoonzuUserlogDlg::CGoonzuUserlogDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGoonzuUserlogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGoonzuUserlogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_NameEdit);
	DDX_Control(pDX, IDC_EDIT2, m_PassWord);
	DDX_Control(pDX, IDC_COMBO_SERVERSELECT, m_cbServerSelect);
}

BEGIN_MESSAGE_MAP(CGoonzuUserlogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	//	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CGoonzuUserlogDlg �޽��� ó����

BOOL CGoonzuUserlogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pGoonzuLogView= NULL;
	strcpy(UserID,"");
	strcpy(PassWord,"");

	BYTE	szGoonzuPath[MAX_PATH] = "";
	char	szTextMgr[512] = "";
	DWORD	dwSize = sizeof(szGoonzuPath);
	HKEY	hKey;
	LONG	lReturn;
	CString	szError;

	lReturn = RegOpenKey(HKEY_CURRENT_USER, "Software\\Intizen\\Goonzu", &hKey);
	if(lReturn != ERROR_SUCCESS)
	{
		szError.Find("������Ʈ���� �� �� �����ϴ�\nErrorCode : %d", lReturn);
		AfxMessageBox(szError);
		return TRUE;
	}
	lReturn = RegQueryValueEx(hKey, "PATH", NULL, NULL, szGoonzuPath, &dwSize);
	if(lReturn != ERROR_SUCCESS)
	{
		szError.Find("���ְ� ��ġ�� ������ ã�� �� �����ϴ�\nErrorCode : %d", lReturn);
		AfxMessageBox(szError);
		return TRUE;
	}

	RegCloseKey(hKey);

	sprintf(szTextMgr, "%sTextMgr\\Textmgr.txt", szGoonzuPath);
	g_pTextMgr.Create(szTextMgr);


	m_cbServerSelect.AddString("Ndoors");
	m_cbServerSelect.AddString("NetMarble");
	m_cbServerSelect.SetCurSel(0);

	// ID�� PW�� ���ڷ� ���� �װ����� �����Ѵ�.
	if(__argc == 3)
	{
		OnBnClickedOk();
	}

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CGoonzuUserlogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGoonzuUserlogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CGoonzuUserlogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGoonzuUserlogDlg::OnBnClickedOk()
{
#ifdef _DEBUG

	//	CVillageManager village= CVillageManager();
	//	village.Set("123");

	//Item.Set("123","456");


#endif


	if(__argc == 1)
	{
		m_NameEdit.GetWindowText(UserID,20);
		m_PassWord.GetWindowText(PassWord,20);
	}
	else if(__argc == 3)
	{
		strncpy(UserID, __argv[1], 20);
		strncpy(PassWord, __argv[2], 20);
	}

	if ( strlen( UserID ) < 1 || strlen( PassWord ) < 1)
	{
		OnCancel();
		return;
	}

	if(strcmp(UserID,"sa")==0)
	{
		OnCancel();
		return;
	}

	// �ν��Ͻ� ����
	RichODBC *pDB = new RichODBC;
	BOOL dbCon = FALSE;


	CString szServerName;
	int	siServerSelect;

	m_cbServerSelect.GetWindowText(szServerName);

//	if(strcmp(szServerName, "Ndoors") == 0)
	if(szServerName == "Ndoors")
	{
		siServerSelect = NDOORS;
		dbCon = pDB->Connect("SQL Server", SERVERIP, "RichLog", UserID, PassWord);
	}
	else
	{
		siServerSelect = NETMARBLE;
		dbCon = pDB->Connect("SQL Server", NETMARBLESERVERIP, "RichLog", UserID, PassWord);
	}

	dbCon = pDB->Connect("SQL Server", SERVERIP, "RichLog", UserID, PassWord);
	pDB->Disconnect();

	delete pDB;




	// DB ����
	if (dbCon)
	{

		if(m_pGoonzuLogView)
		{
			delete m_pGoonzuLogView;
			m_pGoonzuLogView= NULL;
		}
		m_pGoonzuLogView = new CGoonzuLogView(this);
		m_pGoonzuLogView->SetAccount( UserID, PassWord );
		m_pGoonzuLogView->SetServerSelect(siServerSelect);
		strcpy( UserID, "" );
		strcpy( PassWord, "" );
		m_pGoonzuLogView->Create( IDD_DIALOG1, this);
		ShowWindow( SW_SHOWMINIMIZED | SW_HIDE);
		m_pGoonzuLogView->ShowWindow(SW_SHOWNORMAL );
		m_pGoonzuLogView->ShowUserLog();
	}
	else
	{
		OnCancel();
	}


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//OnOK();
}

void CGoonzuUserlogDlg::ExitProcess()
{

	if ( m_pGoonzuLogView )
	{
		delete m_pGoonzuLogView;
		m_pGoonzuLogView = NULL;
	}

	EndDialog( 0 );
	return;
}

//BOOL CGoonzuUserlogDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//
//	AfxMessageBox("�Դ�");
//	m_pGoonzuLogView->OnCopyData(pWnd, pCopyDataStruct);
//	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
//}

