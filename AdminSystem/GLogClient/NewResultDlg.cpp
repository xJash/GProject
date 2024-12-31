// NewResultDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include ".\newresultdlg.h"


// CNewResultDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CNewResultDlg, CDialog)
CNewResultDlg::CNewResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewResultDlg::IDD, pParent)
{
	m_pResultDlg = NULL;
}

CNewResultDlg::~CNewResultDlg()
{
	if(	m_pResultDlg != NULL &&	m_pResultDlg->m_hWnd != NULL)
	{
		m_pResultDlg->DestroyWindow();
		delete m_pResultDlg;
		m_pResultDlg = NULL;
	}
}

void CNewResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CNewResultDlg::PreTranslateMessage(MSG* pMsg)
{
	//if(pMsg->message == WM_KEYDOWN)
	//{
	//	switch(pMsg->wParam)
	//	{
	//	case VK_ESCAPE:
	//	case VK_RETURN:
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	}
	//}

	return CDialog::PreTranslateMessage( pMsg );
}


BEGIN_MESSAGE_MAP(CNewResultDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CNewResultDlg �޽��� ó�����Դϴ�.
BOOL CNewResultDlg::OnInitDialog()
{
	m_pResultDlg = new CLogToolResultDlg();
	if(m_pResultDlg == NULL)				return FALSE;

	m_pResultDlg->Create(IDD_RESULT_DIALOG, this);

	CRect rc;
	GetClientRect(rc);
	m_pResultDlg->MoveWindow(rc);

	m_pResultDlg->UpdateWindow();
	m_pResultDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

void CNewResultDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(	m_pResultDlg != NULL &&	m_pResultDlg->m_hWnd != NULL)
	{
		m_pResultDlg->DestroyWindow();
		delete m_pResultDlg;
		m_pResultDlg = NULL;
	}
}

void CNewResultDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(	m_pResultDlg != NULL && m_pResultDlg->m_hWnd != NULL)
	{
		m_pResultDlg->MoveWindow(0, 0, cx, cy);
	}

}

void CNewResultDlg::AddLogData(LPCSTR pszDate, LPCSTR pszServer, LPCSTR pszCommand, LPCSTR pszUser, LPCSTR pszTargetUser, LPCSTR pszItemUnique, LPCSTR pszLogText)
{
	if(m_pResultDlg != NULL && m_pResultDlg->m_hWnd != NULL)
	{
		CLogToolResultDlg* pResult = (CLogToolResultDlg*)m_pResultDlg;
		if(pResult != NULL)		pResult->AddLogData(pszDate, pszServer, pszCommand, pszUser, pszTargetUser, pszItemUnique, pszLogText);
	}
}