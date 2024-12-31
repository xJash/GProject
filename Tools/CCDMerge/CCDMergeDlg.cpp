// CCDMergeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CCDMerge.h"
#include "CCDMergeDlg.h"
#include ".\ccdmergedlg.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCCDMergeDlg ��ȭ ����



CCCDMergeDlg::CCCDMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCDMergeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCCDMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCCDMergeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_FINDPATH, OnBnClickedButtonFindpath)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, OnBnClickedButtonExecute)
END_MESSAGE_MAP()


// CCCDMergeDlg �޽��� ó����

BOOL CCCDMergeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCCDMergeDlg::OnPaint() 
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
HCURSOR CCCDMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCCDMergeDlg::OnBnClickedButtonFindpath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CCCDMergeDlg::OnBnClickedButtonExecute()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
    CString		strPath;
	GetDlgItemText(IDC_EDIT_PATH, strPath);
	if( strPath[strPath.GetLength() - 1] == '\\' )
	{
		strPath.Delete( strPath.GetLength() - 1, 1 );
	}

	strPath += "\\CCD\\ImageData";

	CString		strFindfile;
	strFindfile = strPath;
	strFindfile += "\\";
	strFindfile += "*.spr";

	CFileFind cf;
	BOOL bRet = cf.FindFile( strFindfile );
	while ( bRet )
	{
		bRet = cf.FindNextFile();

		CString	dest;
		CString folder;
		CString filename;
		filename = cf.GetFileName();
		folder = cf.GetFileName().Mid(0, 5);
		folder.MakeUpper();
		if( strncmp( (LPCSTR)folder, "KOR", 3 ) == 0 )			continue;

		dest.Format("%s\\%s", (LPCSTR)strPath, (LPCSTR)folder );
		CreateDirectory( dest, NULL );
		dest.Format("%s\\%s\\%s", (LPCSTR)strPath, (LPCSTR)folder, (LPCSTR)cf.GetFileName() );
		MoveFile( cf.GetFilePath(), dest );

		_AFX_THREAD_STATE* pState = AfxGetThreadState();
		if( pState )
		{
			if( PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE) )
			{
				if( GetMessage(&(pState->m_msgCur), NULL, NULL, NULL) )
				{
					TranslateMessage(&(pState->m_msgCur));
					DispatchMessage(&(pState->m_msgCur));
				}
			}
		}
	}

	strFindfile = strPath;
	strFindfile += "\\";
	strFindfile += "*.*";
	bRet = cf.FindFile( strFindfile );

	while ( bRet )
	{
		bRet = cf.FindNextFile();

		if( cf.IsDirectory() == FALSE )		continue;
		if( cf.IsDots() == TRUE )			continue;

		CString	src;
		CString folder;
		CString dest;
		CString filename;
		filename = cf.GetFileName();
		folder = cf.GetFileName().Mid(0, 5);
		folder.MakeUpper();

		if( strncmp( (LPCSTR)folder, ".SVN", 4 ) == 0 )			continue;
		if( strncmp( (LPCSTR)folder, "_SVN", 4 ) == 0 )			continue;

		src.Format("\"%s\\%s\\*\"", (LPCSTR)strPath, (LPCSTR)folder );
		dest.Format("\"%s\\%s.sz\"", (LPCSTR)strPath, (LPCSTR)folder );

		HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, "C:\\Program Files\\7-zip\\7z.exe", 
											"\"C:\\Program Files\\7-zip\\7z.exe\"",
											"a",
											"-tzip",
											(LPCSTR)dest,
											(LPCSTR)src,
											NULL);


		int nExitCode = STILL_ACTIVE;
		if( hProcess != INVALID_HANDLE_VALUE )
		{
			while(nExitCode == STILL_ACTIVE)
			{
				GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

				_AFX_THREAD_STATE* pState = AfxGetThreadState();
				if( pState )
				{
					if( PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE) )
					{
						if( GetMessage(&(pState->m_msgCur), NULL, NULL, NULL) )
						{
							TranslateMessage(&(pState->m_msgCur));
							DispatchMessage(&(pState->m_msgCur));
						}
					}
				}
			}
			if( nExitCode == 0 )
			{
				CListBox* pkListBox_Output = (CListBox*)GetDlgItem(IDC_LIST_OUTPUT);
				INT nItem = pkListBox_Output->GetCount();
				CString tmp;
				tmp.Format("[%s] Create Success...", dest);
				pkListBox_Output->AddString(tmp);
			}
			else
			{
				CListBox* pkListBox_Output = (CListBox*)GetDlgItem(IDC_LIST_OUTPUT);
				INT nItem = pkListBox_Output->GetCount();
				CString tmp;
				tmp.Format("[%s] Create Failed!!!!", dest);
				pkListBox_Output->AddString(tmp);
			}
		}
	}
}
