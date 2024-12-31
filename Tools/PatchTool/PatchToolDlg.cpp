// PatchToolDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PatchTool.h"
#include "PatchToolDlg.h"
#include ".\patchtooldlg.h"

#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <process.h>

#define DEFAULT_SVN_PATH			"C:\\Program Files\\Subversion\\bin\\svn.exe"
#define DEFAULT_INCREDIBUILD_PATH	"C:\\Program Files\\Xoreax\\IncrediBuild\\BuildConsole.exe"

#define DEFAULT_RESOURCE_BASE		"E:\\02_Resources"
#define DEFAULT_SOURCE_BASE			"E:\\01_SourceFile"
#define DEFAULT_PATCHFILE_BASE		"E:\\03_PatchFiles"

#define SOURCESAFE4_SVN_PATH		"svn://sourcesafe4"
#define SOURCESAFE4_SOURCE_PATH		"svn://sourcesafe4/GProjectWork"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

// CPatchToolDlg ��ȭ ����



CPatchToolDlg::CPatchToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPatchToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bPatching = FALSE;
}

void CPatchToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COUNTRY, m_combo_Country);
	DDX_Control(pDX, IDC_COMBO_PATCH, m_combo_patch);
}

BEGIN_MESSAGE_MAP(CPatchToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPatchToolDlg �޽��� ó����

BOOL CPatchToolDlg::OnInitDialog()
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
	m_combo_Country.AddString("GoonZu_English");
	m_combo_Country.AddString("GoonZu_N");
	m_combo_Country.AddString("GoonZu_USA");
	m_combo_Country.AddString("GoonZu_Taiwan");
	m_combo_Country.AddString("GoonZu_Japan");

	char	szLine[1024];
	char	szName[1024];
	char	szVal[1024];
	FILE* fp = fopen("option.txt", "r");
	if( fp )
	{
		while( fgets(szLine, sizeof(szLine), fp) )
		{
			ZeroMemory(szName, sizeof(szName));
			ZeroMemory(szVal, sizeof(szVal));

			sscanf(szLine, "%s\t%s", szName, szVal);
			if( strcmp(szName, "Country") == 0 )				{		m_combo_Country.SetCurSel(m_combo_Country.FindString(0, szVal));		}

			if( strcmp(szName, "SVN_Folder") == 0 )				{		m_SVN = szVal;									}
			if( strcmp(szName, "IncrediBuild_Folder") == 0 )	{		m_IncrediBuild = szVal;							}
			if( strcmp(szName, "PatchFileBase") == 0 )			{		m_PatchFolder = szVal;							}
			if( strcmp(szName, "SourceFileBase") == 0 )			{		m_SourceFolder = szVal;							}
			if( strcmp(szName, "ResourceFileBase") == 0 )		{		m_ResourceFolder = szVal;						}
		}

		fclose( fp );
	}

	// �������� ������ �⺻ �� ����
	if( m_SVN.GetLength() == 0 )					
	{
		m_SVN = DEFAULT_SVN_PATH;
		m_SVN_Arg0.Format("\"%s\"", (LPCSTR)m_SVN);
	}
	if( m_IncrediBuild.GetLength() == 0 )
	{
		m_IncrediBuild = DEFAULT_INCREDIBUILD_PATH;
		m_IncrediBuild_Arg0.Format("\"%s\"", (LPCSTR)m_IncrediBuild);
	}
	if( m_SourceFolder.GetLength() == 0 )		{		m_SourceFolder = DEFAULT_SOURCE_BASE;		}
	if( m_PatchFolder.GetLength() == 0 )		{		m_PatchFolder = DEFAULT_PATCHFILE_BASE;		}
	if( m_ResourceFolder.GetLength() == 0 )		{		m_ResourceFolder = DEFAULT_RESOURCE_BASE;	}
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CPatchToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPatchToolDlg::OnPaint() 
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
HCURSOR CPatchToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPatchToolDlg::PumpMessage()
{
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

void CPatchToolDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if( m_bPatching )
	{
		AfxMessageBox( "��ġ�� �������Դϴ�. ���� �ڿ� �ٽ� �õ��Ͻʽÿ�." );
		return;
	}

	Patch();

	m_bPatching = FALSE;
}

BOOL CPatchToolDlg::ReBuild( LPCSTR pszSolutionPath, LPCSTR pszProjectName, LPCSTR BuildCfg )
{
	if( pszSolutionPath == NULL )			return FALSE;
	if( BuildCfg == NULL )					return FALSE;

	CString		strProject;
	if( pszProjectName )		strProject.Format("/prj=%s", pszProjectName);

	HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_IncrediBuild,
												m_IncrediBuild_Arg0, 
												pszSolutionPath,
												strProject,
												"/rebuild",
												BuildCfg,
												NULL );

	int nExitCode = STILL_ACTIVE;
	if( hProcess != INVALID_HANDLE_VALUE )
	{
		while(nExitCode == STILL_ACTIVE)
		{
			GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

			PumpMessage();
		}
	}
    
	if( nExitCode != 0 )		return FALSE;

	return TRUE;
}

BOOL CPatchToolDlg::SvnExistPath( LPCSTR pszPath )
{
	HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_SVN, 
												m_SVN_Arg0,
												"list",
												pszPath,
												NULL );

	int nExitCode = STILL_ACTIVE;
	if( hProcess != INVALID_HANDLE_VALUE )
	{
		while(nExitCode == STILL_ACTIVE)
		{
			GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

			PumpMessage();
		}
	}

	if( nExitCode == 0 )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CPatchToolDlg::SvnBranch(LPCSTR pszSrc, LPCSTR pszBranchTarget)
{
	HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_SVN,
												m_SVN_Arg0,
												"copy",
												pszSrc,
												pszBranchTarget,
												"-m byPatchProgram",
												NULL );

	int nExitCode = STILL_ACTIVE;
	if( hProcess != INVALID_HANDLE_VALUE )
	{
		while(nExitCode == STILL_ACTIVE)
		{
			GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

			PumpMessage();
		}
	}
    
	if( nExitCode != 0 )		return FALSE;

	return TRUE;
}

INT CPatchToolDlg::SvnExport(CStringArray &files, LPCSTR pszSVNBase, LPCSTR pszTargetBase)
{
	if( pszTargetBase == NULL )			return -1;
	if( pszSVNBase == NULL )			return -1;

	INT nRetCount = 0;
	int nExitCode = STILL_ACTIVE;
	CString	strSrc, strTgt;
	for(int i=0; i<files.GetSize(); i++)
	{
		strSrc = pszSVNBase;		strSrc += files.GetAt(i);
		strSrc.Insert(0, "\"");		strSrc += "\"";

		strTgt = pszTargetBase;		strTgt += files.GetAt(i);	strTgt.Replace("/", "\\");
		strTgt.Insert(0, "\"");		strTgt += "\"";
		
		MakeFolder( strTgt );

		HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_SVN, 
													m_SVN_Arg0,
													"export",
													strSrc,
													strTgt,
													NULL );

		if( hProcess != INVALID_HANDLE_VALUE )
		{
			while(nExitCode == STILL_ACTIVE)
			{
				GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

				PumpMessage();
			}
		}
		if( nExitCode != 0 )									return -1;

		nRetCount++;
		// ���� �α� �ۼ�
	}

	return nRetCount;
}

enum PIPES { READ, WRITE }; /* Constants 0 and 1 for READ and WRITE */
#define BUF_SIZE		1024

BOOL CPatchToolDlg::SvnDiff(LPCSTR pszOld, LPCSTR pszNew, CStringArray &files)
{
	if( pszOld == NULL )			return FALSE;
	if( pszNew == NULL )			return FALSE;

	int fdStdOut;
	int myPipe[2];

	char szBuf[BUF_SIZE];
	CString	strOut;

	// Create the pipe
	int ret = _pipe(myPipe, 512, O_BINARY | O_NOINHERIT);

	// Set stdout
	fdStdOut = _dup( 1 );
	_dup2( myPipe[WRITE], 1 );
	close( myPipe[WRITE] );

	CString	strOld, strNew;
	strOld = pszOld;	strOld.Insert(0, "\"");		strOld += "\"";
	strNew = pszNew;	strNew.Insert(0, "\"");		strNew += "\"";	

	HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_SVN,
												m_SVN_Arg0,
												"diff",
												strOld,
												strNew,
												"--summarize",
												NULL );

	_dup2( fdStdOut, 1 );
	close( fdStdOut );

	int nExitCode = STILL_ACTIVE;
	if( hProcess != INVALID_HANDLE_VALUE )
	{
		GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );
		while( nExitCode == STILL_ACTIVE )
		{
			ZeroMemory(szBuf, sizeof(szBuf));
			int nRead = read(myPipe[READ], szBuf, BUF_SIZE - 1);

			if( nRead > 0)
			{
				strOut += szBuf;
			}
			else
			{
				int a = 0;
			}

			GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

			PumpMessage();
		}
	}

	if( nExitCode != 0 )		return FALSE;

	CString strLine;
	int nStart = 0;

	CString	strMode, strFile;
	while( strOut.GetLength() > nStart )
	{
		strLine = strOut.Mid(nStart, strOut.Find('\n', nStart) - nStart);
		nStart = strOut.Find('\n', nStart) + 1;

		strLine.Replace("\r", "");	strLine.Replace("\n", "");

		strMode = strLine.Mid(0, 7);
		strFile = strLine.Mid(7);

		strFile.Replace(pszOld, "");

		if( strMode.Mid(0, 1).Compare("M") == 0 || 
			strMode.Mid(0, 1).Compare("A") == 0 )
			files.Add(strFile);
	}

	return TRUE;
}


BOOL CPatchToolDlg::SvnSwitch( LPCSTR pszSVNPath, LPCSTR pszTargetPath )
{
	HANDLE hProcess = (HANDLE)spawnl( P_NOWAIT, m_SVN,
												m_SVN_Arg0,
												"switch",
												pszSVNPath,
												pszTargetPath,
												NULL );

	int nExitCode = STILL_ACTIVE;
	if( hProcess != INVALID_HANDLE_VALUE )
	{
		while(nExitCode == STILL_ACTIVE)
		{
			GetExitCodeProcess( hProcess, (LPDWORD)&nExitCode );

			PumpMessage();
		}
	}
    
	if( nExitCode != 0 )		return FALSE;

	return TRUE;
}

BOOL CPatchToolDlg::Patch()
{
	CString strOld, strNew;
	CString Country;
	CString OldVersion;
	CString NewVersion;
	CString PatchPath, SrcPath;

	GetDlgItemText(IDC_COMBO_COUNTRY, Country);
	GetDlgItemText(IDC_EDIT_PATH, PatchPath);		// Resource PATH
	GetDlgItemText(IDC_EDIT_SRCPATH, SrcPath);		// Source PATH
	GetDlgItemText(IDC_EDIT_OLDVER, OldVersion);	// OLD VERSION
	GetDlgItemText(IDC_EDIT_NEWVER, NewVersion);	// NEW VERSION

	AddOutput( "1. ���α׷� �ҽ� �۾�" );
	AddOutput( "------------------------------------------------------------" );

	//--------------------------------------------------------------------------------------------------------------------
	// 1. �ҽ� �۾�
	//--------------------------------------------------------------------------------------------------------------------
	// 1.1 - ��ġ �������� �귣ġ ����
	CString svn_src_path;
	svn_src_path  = SOURCESAFE4_SOURCE_PATH;
	svn_src_path += "/branches/Pacth/";
	svn_src_path += SrcPath;

	CString svn_src_target_path;
	svn_src_target_path  = Create_SrcTarget_SVNPath( Country );
	svn_src_target_path += "/";
	svn_src_target_path += NewVersion;

	// SVN ���� Ȯ��
	if( SvnExistPath(svn_src_path) == FALSE )
	{
		AddOutput( "path [%s] Cann't Find", svn_src_path );
		return FALSE;
	}

	// SVN ���� Ȯ��
	if( SvnExistPath(svn_src_target_path) )
	{
		AddOutput( "path [%s] is Already Exist", svn_src_target_path );
		return FALSE;
	}

	AddOutput( "Create Branches ----" );
	AddOutput( "Src : %s", svn_src_path );
	AddOutput( "Dest : %s", svn_src_target_path );

	if( SvnBranch( svn_src_path, svn_src_target_path ) == FALSE )
	{
		AddOutput( "Create Branches ---- Fail" );
		// ����!!
		return FALSE;
	}

	AddOutput( "Create Branches ---- Success" );

	// 1.2 - ������ �귣ġ���� �ҽ� ������Ʈ
	CString local_src_path;
	local_src_path  = m_SourceFolder;
	local_src_path += "\\";
	local_src_path += Country;

	AddOutput( "Source Update ----" );
	AddOutput( "Src : %s", svn_src_target_path );
	AddOutput( "Dest : %s", local_src_path );

	if( SvnSwitch( svn_src_target_path, local_src_path) == FALSE )
	{
		// ����!!
		AddOutput( "Source Update ---- Fail" );
		return FALSE;
	}

	AddOutput( "Source Update ---- Success" );

	// 1.3 - ������ - GameDBManager
	CString local_solution_path;
	local_solution_path  = local_src_path;
	local_solution_path += "\\";
	local_solution_path += "GProject.sln";

	AddOutput( "Rebuild GameDBManager ----" );
	AddOutput( "Solution Path : %s", local_solution_path );

	if( ReBuild( local_solution_path, "GameDBManager", GetBuildCfg_DBManager(Country) ) == FALSE )
	{
		// ����!!
		AddOutput( "Rebuild GameDBManager ---- Fail" );
		return FALSE;
	}
	
	AddOutput( "Rebuild GameDBManager ---- Success" );

	// 1.3 - ������ - GoonZu Server
	local_solution_path  = local_src_path;
	local_solution_path += "\\";
	local_solution_path += "GProject.sln";

	AddOutput( "Rebuild Game Server ----" );
	AddOutput( "Solution Path : %s", local_solution_path );

	if( ReBuild( local_solution_path, "BeTheRich", GetBuildCfg_Game(Country, TRUE) ) == FALSE )
	{
		// ����!!
		AddOutput( "Rebuild Game Server ---- Fail" );
		return FALSE;
	}
	
	AddOutput( "Rebuild Game Server ---- Success" );

	// 1.3 - ������ - GoonZu Client
	local_solution_path  = local_src_path;
	local_solution_path += "\\";
	local_solution_path += "GProject.sln";

	AddOutput( "Rebuild Game Client ----" );
	AddOutput( "Solution Path : %s", local_solution_path );

	if( ReBuild( local_solution_path, "BeTheRich", GetBuildCfg_Game(Country, FALSE) ) == FALSE )
	{
		// ����!!
		AddOutput( "Rebuild Game Client ---- Fail" );
		return FALSE;
	}

	AddOutput( "Rebuild Game Client ---- Success" );

	AddOutput( "2. ���ҽ� �۾�" );
	AddOutput( "------------------------------------------------------------" );

	//--------------------------------------------------------------------------------------------------------------------
	// 2. ���ҽ� �۾�
	//--------------------------------------------------------------------------------------------------------------------
	// 2.1 - ��ġ �������� �귣ġ ����
	svn_src_path  = SOURCESAFE4_SVN_PATH;
	svn_src_path += "/";
	svn_src_path += Country;
	svn_src_path += "/branches/Patch/";
	svn_src_path += PatchPath;

	svn_src_target_path = SOURCESAFE4_SVN_PATH;
	svn_src_target_path += "/";
	svn_src_target_path += Country;
	svn_src_target_path += "/branches/";
	svn_src_target_path += NewVersion;

	// SVN ���� Ȯ��
	if( SvnExistPath(svn_src_path) == FALSE )
	{
		AddOutput( "path [%s] Cann't Find", svn_src_path );
		return FALSE;
	}

	// SVN ���� Ȯ��
	if( SvnExistPath(svn_src_target_path) == TRUE )
	{
		AddOutput( "path [%s] is Already Exist", svn_src_target_path );
		return FALSE;
	}

	AddOutput( "Create Branches ----" );
	AddOutput( "Src : %s", svn_src_path );
	AddOutput( "Dest : %s", svn_src_target_path );

	if( SvnBranch( svn_src_path, svn_src_target_path ) == FALSE )
	{
		// ����!!
		AddOutput( "Create Branches ---- Fail" );
		return FALSE;
	}

	AddOutput( "Create Branches ---- Success" );

	CString new_path, old_path;
	old_path  = SOURCESAFE4_SVN_PATH;
	old_path += "/";
	old_path += Country;
	old_path += "/branches/";
	old_path += OldVersion;

	new_path  = SOURCESAFE4_SVN_PATH;
	new_path += "/";
	new_path += Country;
	new_path += "/branches/";
	new_path += NewVersion;

	AddOutput( "File Diff ----" );

	CStringArray files;
	// 2.2 - ���� ������ ���Ͽ� Ʋ�� ���� ���� ����
	if( SvnDiff( old_path, new_path, files) == FALSE )
	{
		// ����!!
		AddOutput( "File Diff ---- Fail" );
		return FALSE;
	}

	AddOutput( "File Diff ---- Success [FileCount : %d]", files.GetCount() );

	// 2.2 - ���� ���� - Server
	CString local_pathfile_path;
	local_pathfile_path  = m_PatchFolder;
	local_pathfile_path += "\\";
	local_pathfile_path += Country;
	local_pathfile_path += "\\";
	local_pathfile_path += NewVersion;
	local_pathfile_path += "\\";
	local_pathfile_path += "Server";
	INT nRetCnt = 0;

	AddOutput( "File Export Server ----" );
	AddOutput( "SrcVersion : %s", NewVersion );
	AddOutput( "Dest : %s", local_pathfile_path );

	if( (nRetCnt = SvnExport( files, NewVersion, local_pathfile_path )) == -1 )
	{
		// ����!!
		AddOutput( "File Export Server ---- Fail" );
		return FALSE;
	}

	AddOutput( "File Export Server ---- Success [FileCount : %d]", nRetCnt );

	// 2.2 - ���� ���� - Client
	local_pathfile_path  = m_PatchFolder;
	local_pathfile_path += "\\";
	local_pathfile_path += Country;
	local_pathfile_path += "\\";
	local_pathfile_path += NewVersion;
	local_pathfile_path += "\\";
	local_pathfile_path += "Client";

	AddOutput( "File Export Client ----" );
	AddOutput( "SrcVersion : %s", NewVersion );
	AddOutput( "Dest : %s", local_pathfile_path );

	if( (nRetCnt = SvnExport( files, NewVersion, local_pathfile_path )) == -1 )
	{
		// ����!!
		AddOutput( "File Export Client ---- Fail" );
		return FALSE;
	}

	AddOutput( "File Export Client ---- Success [FileCount : %d]", nRetCnt );

	//--------------------------------------------------------------------------------------------------------------------

	return TRUE;
}


void CPatchToolDlg::MakeFolder( LPCSTR pszFolder )
{
	CString strTgt = pszFolder;
	CString	strDir;

	int nStart = 0;
	while( strTgt.GetLength() > nStart )
	{
		int nFind = strTgt.Find('\\', nStart);
		if( nFind == -1 )		break;

		strDir = strTgt.Mid(0, nFind);
		nStart = nFind + 1;

		CreateDirectory(strDir, NULL);
	}
}

void CPatchToolDlg::AddOutput(LPCSTR pszFormat, ...)
{
	CString strFormat;

	va_list valist;
	va_start(valist, pszFormat);
	strFormat.FormatV(pszFormat, valist);
	va_end(valist);

	CString tmp;
	GetDlgItemText(IDC_EDIT_OUTPUT, tmp);
	tmp += strFormat;
	tmp += "\r\n";
	SetDlgItemText(IDC_EDIT_OUTPUT, tmp);

	CEdit* pkEdit = (CEdit*)GetDlgItem(IDC_EDIT_OUTPUT);
	pkEdit->LineScroll( pkEdit->GetLineCount() );

	PumpMessage();
}

CString CPatchToolDlg::Create_SrcTarget_SVNPath( LPCSTR pszCountry )
{
	CString	ret;
	if( pszCountry == NULL )			return ret;

	ret  = SOURCESAFE4_SOURCE_PATH;
	ret += "/branches/";

	if( strcmp(pszCountry, "GoonZu_English") == 0 )
	{
		ret += "English";
	}
	else if ( strcmp(pszCountry, "GoonZu_N") == 0 )
	{
		ret += "Korea";
	}
	else if ( strcmp(pszCountry, "GoonZu_USA") == 0 )
	{
		ret += "USA";
	}
	else if ( strcmp(pszCountry, "GoonZu_Taiwan") == 0 )
	{
		ret += "Taiwan";
	}
	else if ( strcmp(pszCountry, "GoonZu_Japan") == 0 )
	{
		ret += "Japan";
	}

	return ret;
}

CString CPatchToolDlg::GetBuildCfg_DBManager( LPCSTR pszCountry )
{
	CString	ret;
	if( pszCountry == NULL )			return ret;

	if( strcmp(pszCountry, "GoonZu_English") == 0 )
	{
		ret = "Debug_English";
	}
	else if ( strcmp(pszCountry, "GoonZu_N") == 0 )
	{
		ret = "Debug_Korea_Alpha";
	}
	else if ( strcmp(pszCountry, "GoonZu_USA") == 0 )
	{
		ret = "Debug_USA";
	}
	else if ( strcmp(pszCountry, "GoonZu_Taiwan") == 0 )
	{
		ret = "Debug_Taiwan";
	}
	else if ( strcmp(pszCountry, "GoonZu_Japan") == 0 )
	{
		ret = "Debug_Japan";
	}

	return ret;
}

CString CPatchToolDlg::GetBuildCfg_Game( LPCSTR pszCountry, BOOL bServer )
{
	CString	ret;
	if( pszCountry == NULL )			return ret;

	if( strcmp(pszCountry, "GoonZu_English") == 0 )
	{
		if( bServer )	ret = "ReleaseServer_English";
		else			ret = "Release_English";
	}
	else if ( strcmp(pszCountry, "GoonZu_N") == 0 )
	{
		if( bServer )	ret = "ReleaseServer_Korea";
		else			ret = "Release_Korea";
	}
	else if ( strcmp(pszCountry, "GoonZu_USA") == 0 )
	{
		if( bServer )	ret = "ReleaseServer_USA";
		else			ret = "Release_USA";
	}
	else if ( strcmp(pszCountry, "GoonZu_Taiwan") == 0 )
	{
		if( bServer )	ret = "ReleaseServer_Taiwan";
		else			ret = "Release_Taiwan";
	}
	else if ( strcmp(pszCountry, "GoonZu_Japan") == 0 )
	{
		if( bServer )	ret = "ReleaseServer_Japan";
		else			ret = "Release_Japan";
	}

	return ret;
}

void CPatchToolDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if( m_bPatching )
	{
		AfxMessageBox( "��ġ ���� ���Դϴ�." );
		return;
	}

	CDialog::OnClose();
}
