// GLogClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include ".\glogclientdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLogClientDlg ��ȭ ����



CGLogClientDlg::CGLogClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGLogClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pclLogClientProcess	= NULL;
	m_bSearching			= FALSE;
}

void CGLogClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CGLogClientDlg::PreTranslateMessage(MSG* pMsg)
{
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

	return CDialog::PreTranslateMessage( pMsg );
}


BEGIN_MESSAGE_MAP(CGLogClientDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGLogClientDlg �޽��� ó����

BOOL CGLogClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_pclLogClientProcess = new NLogClientProcess();
    m_pclLogClientProcess->Init();

	// ���� �۾��� ���� Ÿ�̸�
	SetTimer(LOGCLIENT_NETWORK_TIMER, LOGCLIENT_NETWORK_TIMER_ELAPSE, NULL);

	// "Searching..." ���� ������ Ÿ�̸�
	SetTimer(LOGCLIENT_SHOW_TIMER, LOGCLIENT_SHOW_TIMER_ELAPSE, NULL);

	// ���ϵ� â ����
	m_LogToolBarDlg.Create(IDD_TOOL_DIALOG, this);
	m_LogToolResultDlg.Create(IDD_RESULT_DIALOG, this);

	CRect winrc;
	GetClientRect(winrc);

	CRect toolrc;
	m_LogToolBarDlg.GetWindowRect(toolrc);

	m_LogToolBarDlg.MoveWindow(0, 0, winrc.Width(), toolrc.Height());
	m_LogToolResultDlg.MoveWindow(0, toolrc.Height(), winrc.Width(), winrc.Height() - toolrc.Height());

	m_LogToolBarDlg.UpdateWindow();
	m_LogToolBarDlg.ShowWindow(SW_SHOW);

	m_LogToolResultDlg.UpdateWindow();
	m_LogToolResultDlg.ShowWindow(SW_SHOW);

	m_LogToolBarDlg.Init();
	m_LogToolResultDlg.Init();

	SearchEnable(TRUE);

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CGLogClientDlg::OnPaint() 
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
HCURSOR CGLogClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//=============================================================================
//  @Name   OnTimer()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CGLogClientDlg::OnTimer(UINT nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(nIDEvent)
	{
	case LOGCLIENT_NETWORK_TIMER:
		{
			NetworkProcess();
		}
		break;

	case LOGCLIENT_SHOW_TIMER:
		{
			CStatic* pStatic = (CStatic*)m_LogToolBarDlg.GetDlgItem(IDC_STATIC_SEARCHING);
			if(pStatic)
			{
				if(m_bSearching)
				{
					static BOOL bShow = FALSE;
					bShow = !bShow;
					pStatic->ShowWindow(bShow);
				}
				else
				{
					pStatic->ShowWindow(FALSE);
				}
			}
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

//=============================================================================
//  @Name   OnDestroy()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CGLogClientDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	// ��Ʈ��ũ ó���� ���� Ÿ�̸� ����
	KillTimer(LOGCLIENT_NETWORK_TIMER);

	if(m_pclLogClientProcess)
	{
		delete m_pclLogClientProcess;
		m_pclLogClientProcess = NULL;
	}
}

//=============================================================================
//  @Name   OnSize()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CGLogClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	int		nTop = 0;

	if(m_LogToolBarDlg.m_hWnd != NULL)
	{
		CRect rc;
		m_LogToolBarDlg.GetWindowRect(rc);
		m_LogToolBarDlg.MoveWindow(0, 0, cx, rc.Height());

		nTop += rc.Height();
	}

	if(m_LogToolResultDlg.m_hWnd != NULL)
	{
		CRect rc;
		CRect winrc;
		m_LogToolResultDlg.GetWindowRect(rc);
		GetClientRect(winrc);
		m_LogToolResultDlg.MoveWindow(0, nTop, cx, winrc.Height() - nTop);
	}

}

//===========================================================================
// ��� �Լ�
//===========================================================================
void CGLogClientDlg::NetworkProcess()
{
	if( m_pclLogClientProcess != NULL )
	{
		m_pclLogClientProcess->Run();
	}
}

//===========================================================================
// �������̽�
//===========================================================================
BOOL CGLogClientDlg::RequestLogData(char* pszStartTime, char* pszEndTime, char* pszServerName, char* pszCommand, char* pszCategory, char* pszPersonName, char* pszDstPersonName, char* pszItemUnique, char* pszUserSearch)
{
	if( m_pclLogClientProcess == NULL )						return FALSE;

	if( m_pclLogClientProcess->GetProcessState() != LOGCLIENTPROCESS_STATE_IDLE)
	{
		AfxMessageBox("In Working. Please Try a few minutes later.", MB_OK);
		return FALSE;
	}

	sDBRequest_Log	LogMsg(	0,
							m_pclLogClientProcess->GetLoginID(),
							m_pclLogClientProcess->GetLoginPW(),
							pszCommand, pszCategory,
							pszServerName, pszPersonName, pszDstPersonName,
							pszItemUnique,
							pszUserSearch,
							pszStartTime, pszEndTime);

	m_siSearchCount = 0;
	SearchEnable(FALSE);
	m_pclLogClientProcess->RequsetLog(&LogMsg);

	return TRUE;
}

//=============================================================================
//  @Name   Stop()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  �α� ������ �޴°��� �����Ѵ�.
//=============================================================================
BOOL CGLogClientDlg::Stop()
{
	BOOL bRet;
	if(m_pclLogClientProcess != NULL)
	{
		bRet = m_pclLogClientProcess->Stop();
	}

	return bRet;
}

//=============================================================================
//  @Name   AddLogData()
//! @author LeeKH						
//! @date   2007-3-6
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
BOOL CGLogClientDlg::AddLogData(stLOGData* pLogData)
{
	if(pLogData == NULL)									return FALSE;

	for(SI32 i=0; i<MAX_STLOGDATA_PER_PACKET; i++)
	{
		if(strlen(pLogData[i].szDate) > 0)
		{
			m_LogToolResultDlg.AddLogData(	pLogData[i].szDate, pLogData[i].szServerName, pLogData[i].szCommand, 
											pLogData[i].szPersonName, pLogData[i].szDstPersonName,
											pLogData[i].szItemUnique, 
											pLogData[i].szLogTxt);
			m_siSearchCount++;
		}
	}

	return TRUE;
}

//=============================================================================
//  @Name   ClearLog()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CGLogClientDlg::ClearLog()
{
	m_LogToolResultDlg.ClearLog();
}

//=============================================================================
//  @Name   SearchEnable()
//! @author LeeKH						
//! @date   2007-3-12
//! @param  X   X
//! @return X
//! @brief  
//=============================================================================
void CGLogClientDlg::SearchEnable(BOOL nEnable)
{
	CButton* pSearchButton = (CButton*)m_LogToolBarDlg.GetDlgItem(IDC_BTN_SEARCH);
	if(pSearchButton != NULL)
	{
		pSearchButton->EnableWindow(nEnable);
	}

	CButton* pStopButton = (CButton*)m_LogToolBarDlg.GetDlgItem(IDC_BUTTON_STOP);
	if(pStopButton != NULL)
	{
		pStopButton->EnableWindow(!nEnable);
	}

	m_bSearching = !nEnable;
}