// GlobalTradeServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "GlobalTradeServer.h"
#include "GlobalTradeServerDlg.h"

#include "DBProcess.h"
#include "DBProtocol.h"
#include "GameProtocol.h"
#include "DBLogProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern DBProcess		g_DBProcess;
extern DBProtocol		g_DBProtocol;
extern GameProtocol 	g_GameProtocol;
extern DBLogProtocol	g_dap;


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


// CGlobalTradeServerDlg ��ȭ ����



CGlobalTradeServerDlg::CGlobalTradeServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlobalTradeServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlobalTradeServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}

BEGIN_MESSAGE_MAP(CGlobalTradeServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGlobalTradeServerDlg �޽��� ó����

BOOL CGlobalTradeServerDlg::OnInitDialog()
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
	CRect rect;
	m_ListCtrl.GetClientRect(&rect);

	m_ListCtrl.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT );

	LV_COLUMN lvColum;
	lvColum.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvColum.fmt = LVCFMT_CENTER;

	for( int  i = 0 ; i < 2; ++i )
	{
		lvColum.iSubItem = i;
		switch(i)
		{
		case 0:
			{
				lvColum.cx = (rect.Width() - 30) / 2;
				lvColum.pszText = "IP";
			}
			break;
		case 1:
			{
				lvColum.cx = (rect.Width() - 30) / 2;
				lvColum.pszText = "STATE";
			}
			break;
		}

		m_ListCtrl.InsertColumn( i, &lvColum );
	}

	LV_ITEM lvItem;
	for ( SI32 i = 0 ; i < g_GameProtocol.GetSessionManager()->m_siMaxSize ; i ++ )
	{
		ITZSession* pSession = g_GameProtocol.GetSessionManager()->GetSession(i);

		lvItem.iItem = i;
		lvItem.mask = LVIF_TEXT;
		lvItem.iSubItem = 0;

		if ( pSession == NULL )
		{
			lvItem.pszText = "";
			m_ListCtrl.InsertItem( &lvItem );
			m_ListCtrl.SetItemText(lvItem.iItem, 1, "SESSION_STATE_NONE" );

			continue;
		}

		lvItem.pszText = pSession->m_szIP;
		m_ListCtrl.InsertItem( &lvItem );

		if( SESSION_STATE_NONE == pSession->GetState() )
		{
			m_ListCtrl.SetItemText(lvItem.iItem, 1, "SESSION_STATE_NONE" );
		}
		else if( SESSION_STATE_CONNECTED == pSession->GetState() )
		{
			m_ListCtrl.SetItemText(lvItem.iItem, 1, "SESSION_STATE_CONNECTED" );
		}
		else if( SESSION_STATE_ESTABLISHED == pSession->GetState() )
		{
			m_ListCtrl.SetItemText(lvItem.iItem, 1, "SESSION_STATE_ESTABLISHED" );
		}
		else if( SESSION_STATE_DISCONNECTED == pSession->GetState() )
		{
			m_ListCtrl.SetItemText(lvItem.iItem, 1, "SESSION_STATE_DISCONNECTED" );
		}
	}

	m_bWorkRun = false;
	SetTimer( 1, 200, NULL );
	SetTimer( 2, 10000, NULL );

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CGlobalTradeServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGlobalTradeServerDlg::OnPaint() 
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
HCURSOR CGlobalTradeServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlobalTradeServerDlg::OnTimer(UINT nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CDialog::OnTimer(nIDEvent);

	if( m_bWorkRun == false )
	{
		m_bWorkRun = true;

		g_DBProcess.Run();

		m_bWorkRun = false;
	}

	if( 2 == nIDEvent )
	{
		for ( SI32 i = 0 ; i < g_GameProtocol.GetSessionManager()->m_siMaxSize ; i ++ )
		{
			ITZSession* pSession = g_GameProtocol.GetSessionManager()->GetSession(i);
			if ( pSession == NULL )				continue;

			m_ListCtrl.SetItemText( i, 0, pSession->m_szIP );

			if( SESSION_STATE_NONE == pSession->GetState() )
			{
				m_ListCtrl.SetItemText(i, 1, "SESSION_STATE_NONE" );
			}
			else if( SESSION_STATE_CONNECTED == pSession->GetState() )
			{
				m_ListCtrl.SetItemText(i, 1, "SESSION_STATE_CONNECTED" );
			}
			else if( SESSION_STATE_ESTABLISHED == pSession->GetState() )
			{
				m_ListCtrl.SetItemText(i, 1, "SESSION_STATE_ESTABLISHED" );
			}
			else if( SESSION_STATE_DISCONNECTED == pSession->GetState() )
			{
				m_ListCtrl.SetItemText(i, 1, "SESSION_STATE_DISCONNECTED" );
			}
		}
	}
}
