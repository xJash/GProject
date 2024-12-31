#include "stdafx.h"
#include "patch.h"
#include "FtpDownLoad.h"
#include "TextMgr.h"

unsigned __stdcall CFtpDownLoad::FileRecvThread(void* lpArg)
{
	CFtpDownLoad *pFtp = ( CFtpDownLoad *) lpArg;

	pFtp->FileRecv();

	_endthreadex( 0 );

	return 0;
}


//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CFtpDownLoad::CFtpDownLoad()
//	Desc : �� �� ��
//	Date : 2003. 08. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CFtpDownLoad::CFtpDownLoad()
{
	m_hInternet = NULL;
	m_hFtp = NULL;
	m_hFtpFile = NULL;
	m_FindFile = NULL;
	m_hFileRecvThreadHandle  = NULL;

	m_dwFileSize = 0;
	m_dwFileRecvSize = 0;

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - CFtpDownLoad::~CFtpDownLoad()
//	Desc : �� �� ��
//	Date : 2003. 08. 24
//	Update : 
//--------------------------------------------------------------------------------------------
CFtpDownLoad::~CFtpDownLoad()
{
	Destroy();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::Initialize()
//	Desc : Ftp ���� �ʱ�ȭ
//	Date : 2003. 08. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::Initialize()
{	
	if ( m_hFtpFile )
	{
		::InternetCloseHandle( m_hFtpFile );
		m_hFtpFile = NULL;
	}
	
	if ( m_FindFile )
	{
		::InternetCloseHandle( m_FindFile );
		m_FindFile = NULL;
	}

	if ( m_hFtp )
	{
		::InternetCloseHandle( m_hFtp );
		m_hFtp = NULL;
	}

	if ( m_hInternet )
	{
		::InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
	}

	m_bThreadRun = false;

	m_dwFileSize = 0;
	ZeroMemory( m_strLocalFileNamePath, 512 );

	m_ucDownLoadStatus = STOP_STATUS;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::Destroy()
//	Desc : Ftp ���� ���� ó��
//	Date : 2003. 08. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::Destroy()
{
	FtpDownLoadThreadEnd();

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::DisConnect()
//	Desc : ���� ����
//	Date : 2003. 08. 24
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::DisConnect()
{
	if ( m_hFtpFile )
	{
		::InternetCloseHandle( m_hFtpFile );
		m_hFtpFile = NULL;
	}
	
	if ( m_FindFile )
	{
		::InternetCloseHandle( m_FindFile );
		m_FindFile = NULL;
	}

	if ( m_hFtp )
	{
		::InternetCloseHandle( m_hFtp );
		m_hFtp = NULL;
	}

	if ( m_hInternet )
	{
		::InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CFtpDownLoad::Connect( char *ServerIP, char *strFolderPath, char *strID, char *strPassWord, US16 usFtpPort )
//	Desc : Ftp �� �� ȭ
//	Date : 2003. 08. 24
//	Update : Connect �Ķ���͵� Front Server ���� �޾ƿ��� ���� - 2003. 10. 15
//--------------------------------------------------------------------------------------------
bool CFtpDownLoad::Connect( char *ServerIP, char *strFolderPath, char *strID, char *strPassWord, US16 usFtpPort )
{
	memset( m_strServerIP, 0, 128 );
	strcpy( m_strServerIP, ServerIP );
	char * pText = TEXT("Error1, Inspect Your Internet Connection, Please.\r");

	m_hInternet = ::InternetOpen( "GoonZuFtp"
		, INTERNET_OPEN_TYPE_PRECONFIG
		, NULL, NULL, 0);

	if ( m_hInternet == NULL )
	{
		AfxMessageBox(pText);
		return false;
	}


	if ( strPassWord != NULL )
	{
		m_hFtp = ::InternetConnect
			( m_hInternet, m_strServerIP, usFtpPort
			, strID, strPassWord
			, INTERNET_SERVICE_FTP
			, INTERNET_FLAG_PASSIVE
			, 0);
	}
	else
	{
		m_hFtp = ::InternetConnect
			( m_hInternet, m_strServerIP, usFtpPort
			, NULL, NULL
			, INTERNET_SERVICE_FTP
			, INTERNET_FLAG_PASSIVE
			, 0);
	}

	if ( m_hFtp == NULL )
	{
		char *pText = TEXT("Error2, Inspect Your Internet Connection, Please.\r")	;
		AfxMessageBox(pText);
		return false;
	}

	if ( strFolderPath != NULL )
	{
		::FtpSetCurrentDirectory( m_hFtp, strFolderPath );
	}
	

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - bool CFtpDownLoad::FtpFileConnect( char* strFileName, char* strLocalFileName )
//	Desc : Ftp File �ޱ� ���� Ftp ���� ( FTP ���� ���� ó�� )
//		   �� �Լ��� �ܺο��� �� Ŭ������ ��ü�� ������ ������ ȣ���ϵ��� ��.
//		   �ϵ忡 ������ ���ϸ� ����, Ftp�� �޾ƿ� ������ ������ ������ ��.
//	Date : 2003. 08. 24
//	Update :
//--------------------------------------------------------------------------------------------
bool CFtpDownLoad::FtpFileConnect( char* strFileName, char* strLocalFileName )
{
	WIN32_FIND_DATA wfd;

	m_FindFile = ::FtpFindFirstFile( m_hFtp, strFileName, &wfd, 0 ,0);
	char*pText = TEXT("Error3, Inspect Your Internet Connection, Please.\r");

	if( m_FindFile == NULL )
	{	
		AfxMessageBox(pText);
		return false;
	}
	
	m_hFtpFile = ::FtpOpenFile( m_hFtp, strFileName, GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, 0 );

	if( m_hFtpFile == NULL )
	{	
		char*pText = TEXT("Error4, Inspect Your Internet Connection, Please.\r");
		AfxMessageBox(pText);
		return false;
	}

	m_dwFileSize = wfd.nFileSizeLow;

	strcpy( m_strLocalFileNamePath, strLocalFileName );
	
	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::FtpDownLoadThreadStart()
//	Desc : FTP ������ �ޱ� ���� �����带 ����
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::FtpDownLoadThreadStart()
{
	m_ucDownLoadStatus = DOWNLOAD_STATUS;
	UI32 uiFileRecvThreadID = 0;
	m_bThreadRun = true;
	
	m_hFileRecvThreadHandle = (HANDLE)_beginthreadex( NULL, 0, &FileRecvThread, this, 0, &uiFileRecvThreadID );

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::FtpDownLoadThreadEnd()
//	Desc : FTP ������ �� �޾�����, �����带 �����ϰ� ���� ��Ű�� ���ؼ� ȣ�� �ϴ� ����. - �Ϲ����� ������ ���� ���
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::FtpDownLoadThreadEnd()
{
	if ( m_bThreadRun )
	{
		m_bThreadRun = false;
		::WaitForSingleObject( m_hFileRecvThreadHandle, INFINITE );
	}

	if ( m_hFileRecvThreadHandle )
	{
		::CloseHandle( m_hFileRecvThreadHandle );
		m_hFileRecvThreadHandle = NULL;
	}	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::FileRecvStop()
//	Desc : ���� �޴� ���� ��, ���� ���� ��Ŵ. - �������� ������ ����
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::FileRecvStop()
{
	m_ucDownLoadStatus = DOWNLOAD_STOP;

	if ( m_bThreadRun )
	{
		m_bThreadRun = false;

		if ( m_hFileRecvThreadHandle )
		{
			::WaitForSingleObject( m_hFileRecvThreadHandle, INFINITE );
			::CloseHandle( m_hFileRecvThreadHandle );
			m_hFileRecvThreadHandle = NULL;
		}
	}

	if ( m_hFileRecvThreadHandle )
	{
		::CloseHandle( m_hFileRecvThreadHandle );
		m_hFileRecvThreadHandle = NULL;
	}	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - UC08 CFtpDownLoad::GetDownLoadStatus()
//	Desc : ���� �ٿ�ε� ���¸� �˾ƿ��� ���ؼ�...
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
UC08 CFtpDownLoad::GetDownLoadStatus()
{
	return m_ucDownLoadStatus;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CFtpDownLoad::FileRecv()
//	Desc : �����忡�� �� �Լ��� ȣ����. ������ �޴� �κ��� ���⼭ ������.
//	Date : 2003. 06. 10
//	Update : 2003. 06. 13 - ���� ���� �޴� �κ� �ڵ�.
//--------------------------------------------------------------------------------------------
void CFtpDownLoad::FileRecv()
{
	HANDLE hFile;
	DWORD dwRead = 0;
	DWORD dwWritten = 0;
	m_dwFileRecvSize = 0;

	CC08 Buf[ 1000 ];				// �ѹ��� �ִ� 1KB ��ŭ�� ����.

	BOOL Result;

	hFile = ::CreateFile( m_strLocalFileNamePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	if ( hFile == INVALID_HANDLE_VALUE  )
	{
		m_ucDownLoadStatus = LOCALFILE_MAKE_ERROR;
		return;
	}

	while( m_bThreadRun )						// m_bThreadRun �� FileRecv �� ȣ���ϴ� ������ �������� ���̴� ���� �̹Ƿ�, �� ���� ���� ���߿� false�� ���ϸ� ��� �����尡 ������.
	{
		//::InternetQueryDataAvailable( m_hURL, &dwSize, 0, 0 );
		Result = ::InternetReadFile( m_hFtpFile, Buf, 1000, &dwRead );
		
		if ( dwRead == 0 && Result == TRUE )
		{
			::CloseHandle( hFile );
			hFile = NULL;
			::InternetCloseHandle( m_hFtpFile );
			m_hFtpFile = NULL;

			m_ucDownLoadStatus = DOWNLOAD_COMPLETE_STATUS;
			m_bThreadRun = false;

			break;
		}

		::WriteFile( hFile, Buf, dwRead, &dwWritten, NULL );

		m_dwFileRecvSize += dwWritten;

		Sleep(1);
	}
	
	if ( hFile )			//�� ���� DownLoad �� ���� �ߴ� ��Ų ����̹Ƿ�, �ް� �ִ� ������ ���� �Ŀ� ������.
	{
		::CloseHandle( hFile );
		::DeleteFile( m_strLocalFileNamePath );
	}

	if ( m_hFtpFile )
	{
		::InternetCloseHandle( m_hFtpFile );
		m_hFtpFile = NULL;
	}
	
	if ( m_FindFile )
	{
		::InternetCloseHandle( m_FindFile );
		m_FindFile = NULL;
	}

	if ( m_hFtp )
	{
		::InternetCloseHandle( m_hFtp );
		m_hFtp = NULL;
	}	

	if ( m_hInternet )
	{
		::InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
	}

}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - __int64 CFtpDownLoad::GetFileSize()
//	Desc : ���� ������ ����� ����
//	Date : 2003. 08. 22
//	Update : 
//--------------------------------------------------------------------------------------------
__int64 CFtpDownLoad::GetFileSize()
{
	return m_dwFileSize;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - __int64	CFtpDownLoad::GetFileRecvSize()
//	Desc : ���� ������ ����� ����
//	Date : 2003. 08. 22
//	Update : 
//--------------------------------------------------------------------------------------------
__int64	CFtpDownLoad::GetFileRecvSize()
{
	return m_dwFileRecvSize;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - DWORD CFtpDownLoad::GetFileRecvPercent()
//	Desc : �� �ۼ�Ʈ �޾Ҵ��� �˾Ƴ��� ���ؼ�...
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
DWORD CFtpDownLoad::GetFileRecvPercent()
{
	DWORD dwDownLoadPercentage = (DWORD)(( m_dwFileRecvSize * 100 ) / m_dwFileSize);

	if ( dwDownLoadPercentage > 100 )
	{
		return 100;
	}

	return dwDownLoadPercentage;
}
