// FieldObjectMergeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "FieldObjectMerge.h"
#include "FieldObjectMergeDlg.h"
#include ".\fieldobjectmergedlg.h"
#include <process.h>

#include "../../NLib/NDataLoader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFieldObjectMergeDlg ��ȭ ����



CFieldObjectMergeDlg::CFieldObjectMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFieldObjectMergeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CFieldObjectMergeDlg::~CFieldObjectMergeDlg()
{
	for( int i=0; i<m_arrFieldObject.GetSize(); i++ )
	{
		CFieldObject*	pkFieldObject = (CFieldObject*)m_arrFieldObject.GetAt( i );
		delete pkFieldObject;
		m_arrFieldObject.RemoveAt( i );
	}
}

void CFieldObjectMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFieldObjectMergeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE, OnBnClickedButtonExecute)
END_MESSAGE_MAP()


// CFieldObjectMergeDlg �޽��� ó����

BOOL CFieldObjectMergeDlg::OnInitDialog()
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

void CFieldObjectMergeDlg::OnPaint() 
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
HCURSOR CFieldObjectMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFieldObjectMergeDlg::OnBnClickedButtonExecute()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString		strPath;
	GetDlgItemText(IDC_EDIT_PATH, strPath);
	if( strPath[strPath.GetLength() - 1] == '\\' )
	{
		strPath.Delete( strPath.GetLength() - 1, 1 );
	}

	BOOL bLoadFile = FALSE;
	NDataLoader	dataloader;

	SI32 unique = 0 ;
	SI32 imagenumber = 0 ;
	TCHAR type[128] = TEXT("") ;
	TCHAR name[128] = TEXT("") ;
	SI32 transmode = 0 ;
	SI32 alphavalue = 0 ;
	SI32 shadow = 0 ; // ���� �׸��ڵ�
	TCHAR zipname[128] = TEXT("") ;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&unique,		4,
		NDATA_MBSTRING,	type,			128,
		NDATA_INT32,	&imagenumber,	4,
		NDATA_MBSTRING,	name,			128,
		NDATA_INT32,	&transmode,		4,
		NDATA_INT32,	&alphavalue, 	4,
		NDATA_INT32,	&shadow,		4,
		NDATA_MBSTRING,	zipname,		128,
		0,0,0
	};

	CString	strFile;
	strFile = strPath;
	strFile += "\\Data\\FieldObjectSetInfo.txt";

	dataloader.RegDataType( pDataTypeInfo );
	bLoadFile = dataloader.LoadDataFromFile( (TCHAR*)(LPCTSTR)strFile );

	SI32 index = 0;
	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData())
		{
			CFieldObject*	pnewfieldobject = new CFieldObject();
			pnewfieldobject->m_strName = name;
			pnewfieldobject->m_ZipName = zipname;

			m_arrFieldObject.Add( pnewfieldobject );
		}
	}

	int i;
    CString src, dest, path;

	for( i=0; i<m_arrFieldObject.GetSize(); i++ )
	{
		CFieldObject*	pkFieldObject = (CFieldObject*)m_arrFieldObject.GetAt( i );

		path.Format( "%s\\FieldObject\\%s.pak",  (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_ZipName );
		CreateDirectory( path, NULL);

		path.Format( "%s\\FieldObject\\%s.pak\\%s",  (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_ZipName, (LPCSTR)pkFieldObject->m_strName);
		CreateDirectory( path, NULL );

		src.Format("%s\\FieldObject\\%s\\%s1.mpr", (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_strName, (LPCSTR)pkFieldObject->m_strName );
		dest.Format("%s\\FieldObject\\%s.pak\\%s\\%s1.mpr", (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_ZipName, (LPCSTR)pkFieldObject->m_strName, (LPCSTR)pkFieldObject->m_strName );
		MoveFile( src, dest );

		src.Format("%s\\FieldObject\\%s\\%s.txt", (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_strName, (LPCSTR)pkFieldObject->m_strName );
		dest.Format("%s\\FieldObject\\%s.pak\\%s\\%s.txt", (LPCSTR)strPath, (LPCSTR)pkFieldObject->m_ZipName, (LPCSTR)pkFieldObject->m_strName, (LPCSTR)pkFieldObject->m_strName );
		MoveFile( src, dest );
	}

	for( i=0; i<m_arrFieldObject.GetSize(); i++ )
	{
		CFieldObject*	pkFieldObject = (CFieldObject*)m_arrFieldObject.GetAt( i );
		delete pkFieldObject;
		m_arrFieldObject.RemoveAt( i );
	}

	CFileFind cf;
	CString		strFindfile;

	strFindfile = strPath;
	strFindfile += "\\FieldObject\\";
	strFindfile += "*.*";
	BOOL bRet = cf.FindFile( strFindfile );

	while ( bRet )
	{
		bRet = cf.FindNextFile();

		if( cf.IsDirectory() == FALSE )		continue;
		if( cf.IsDots() == TRUE )			continue;

		CString	src;
		CString dest;
		CString filename;
		CString workingdir;
		filename = cf.GetFileName();
		filename.MakeUpper();

		if( strncmp( (LPCSTR)filename, ".SVN", 4 ) == 0 )			continue;
		if( strncmp( (LPCSTR)filename, "_SVN", 4 ) == 0 )			continue;

		int nFind = filename.Find(".PAK");
		if( nFind < 0 )												continue;

		src.Format("\"%s\\FieldObject\\%s\\*\"", (LPCSTR)strPath, (LPCSTR)cf.GetFileName() );
		dest.Format("\"%s\\FieldObject\\%s\"", (LPCSTR)strPath, (LPCSTR)cf.GetFileName() );
		dest.Replace(".pak", ".mz");
		workingdir.Format("\"%s\\FieldObject\"", (LPCSTR)strPath);

		SetCurrentDirectory( workingdir );

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
