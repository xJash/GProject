#include "stdafx.h"
#include "Patch.h"
#include "Http.h"
#include "TextMgr.h"

unsigned __stdcall CHttp::FileRecvThread(void* lpArg)
{
	CHttp *pHttp = (CHttp *) lpArg;

	pHttp->FileRecv();

	_endthreadex( 0 );

	return 0;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - Connect( char * strURL )
//	Desc : �� �� ��
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
CHttp::CHttp()
{
	m_hInternet = NULL;
	m_hURL = NULL;

	Initialize();
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - Connect( char * strURL )
//	Desc : �� �� ��
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
CHttp::~CHttp()
{
	Destroy();	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - Connect( char * strURL )
//	Desc : http ���� �ʱ�ȭ
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::Initialize()
{	
	if ( m_hURL )
	{
		::InternetCloseHandle( m_hURL );
		m_hURL = NULL;
	}

	if ( m_hInternet )
	{
		::InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
	}

	m_bThreadRun = false;

	m_dwFileSize = 0;
	ZeroMemory( m_strLocalFileNamePath, 1536 );

	m_ucDownLoadStatus = STOP_STATUS;

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - Connect( char * strURL )
//	Desc : http ���� ���� ó��
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::Destroy()
{
	HttpDownLoadThreadEnd();
	DisConnect();

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - DisConnect()
//	Desc : ���� ����
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::DisConnect()
{
	if ( m_hURL )
	{
		::InternetCloseHandle( m_hURL );
		m_hURL = NULL;
	}

	if ( m_hInternet != NULL )
	{
		::InternetCloseHandle( m_hInternet );
		m_hInternet = NULL;
	}

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - Connect()
//	Desc : http �� �� ȭ
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
bool CHttp::Connect()
{
	m_hInternet = ::InternetOpen( "HTTPDOWNLOAD", INTERNET_OPEN_TYPE_DIRECT , NULL, NULL, 0 );
	char * pText = GetTxtFromMgr(13);
	
	//m_hInternet = ::InternetOpen( "HTTPDOWNLOAD", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );

	if ( m_hInternet == NULL )
	{
		AfxMessageBox(pText);
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - HttpFileConnect( char* strURL, char* strLocalFileName )
//	Desc : http file �ޱ� ���� http ���� ( HTTP ���� URL�� ���� ó�� )
//		   �� �Լ��� �ܺο��� �� Ŭ������ ��ü�� ������ ������ ȣ���ϵ��� ��.
//		   �ϵ忡 ������ ���ϸ� ����, http�� �޾ƿ� ������ ������ ������ ��.
//	Date : 2003. 06. 10
//	Update : 2003. 06. 13 - �ϵ忡 ������ ���ϸ� ����, http�� �޾ƿ� ������ ������ ������ ��.
//--------------------------------------------------------------------------------------------
bool CHttp::HttpFileConnect( char* strURL, char* strLocalFileName )
{
	m_hURL = ::InternetOpenUrl( m_hInternet, strURL, NULL, 0, INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE| INTERNET_FLAG_KEEP_CONNECTION, 0 );
	
	char *pText = GetTxtFromMgr(14);
	if ( m_hURL == NULL )
	{
		AfxMessageBox(pText);
		return false;
	}

	char bufQuery[32] ;
	DWORD dwLengthBufQuery = sizeof(bufQuery);
	
	if ( ::HttpQueryInfo( m_hURL, HTTP_QUERY_CONTENT_LENGTH, bufQuery, &dwLengthBufQuery, NULL ) == FALSE )
	{
		pText = GetTxtFromMgr(19);
		AfxMessageBox(pText);
		return false;
	}

	m_dwFileSize = (DWORD)atoi(bufQuery) ;

	strcpy( m_strLocalFileNamePath, strLocalFileName );
	
	return true;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - HttpDownLoadThreadStart()
//	Desc : HTTP ������ �ޱ� ���� �����带 ����
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::HttpDownLoadThreadStart()
{
	m_ucDownLoadStatus = DOWNLOAD_STATUS;
	UI32 uiFileRecvThreadID = 0;
	m_bThreadRun = true;
	
	m_hFileRecvThreadHandle = (HANDLE)_beginthreadex( NULL, 0, &FileRecvThread, this, 0, &uiFileRecvThreadID );

	return;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CHttp::HttpDownLoadThreadEnd()
//	Desc : HTTP ������ �� �޾�����, �����带 �����ϰ� ���� ��Ű�� ���ؼ� ȣ�� �ϴ� ����. - �Ϲ����� ������ ���� ���
//	Date : 2003. 06. 10
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::HttpDownLoadThreadEnd()
{
	if ( m_bThreadRun )
	{
		m_bThreadRun = false;
		::WaitForSingleObject( m_hFileRecvThreadHandle, INFINITE );
	}

	::CloseHandle( m_hFileRecvThreadHandle );
	m_hFileRecvThreadHandle = NULL;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - void CHttp::FileRecvStop()
//	Desc : ���� �޴� ���� ��, ���� ���� ��Ŵ. - �������� ������ ����
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
void CHttp::FileRecvStop()
{
	m_ucDownLoadStatus = DOWNLOAD_STOP;

	if ( m_bThreadRun )
	{
		m_bThreadRun = false;
		::WaitForSingleObject( m_hFileRecvThreadHandle, INFINITE );
	}

	::CloseHandle( m_hFileRecvThreadHandle );
	m_hFileRecvThreadHandle = NULL;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - UC08 CHttp::GetDownLoadStatus()
//	Desc : ���� �ٿ�ε� ���¸� �˾ƿ��� ���ؼ�...
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
UC08 CHttp::GetDownLoadStatus()
{
	return m_ucDownLoadStatus;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - FileRecv()
//	Desc : �����忡�� �� �Լ��� ȣ����. ������ �޴� �κ��� ���⼭ ������.
//	Date : 2003. 06. 10
//	Update : 2003. 06. 13 - ���� ���� �޴� �κ� �ڵ�.
//--------------------------------------------------------------------------------------------
void CHttp::FileRecv()
{
	HANDLE hFile;
	DWORD dwSize = 0;
	DWORD dwRead = 0;
	DWORD dwWritten = 0;
	m_dwFileRecvSize = 0;

	CC08 Buf[1000000];	//���� MB ������ Recv ������ �ʰ���... ���ͳ� �ӵ��� �׸�ŭ �Ǹ�... ��... �Ѥ�

	BOOL Result;

	hFile = ::CreateFile( m_strLocalFileNamePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	if ( hFile == INVALID_HANDLE_VALUE  )
	{
		m_ucDownLoadStatus = LOCALFILE_MAKE_ERROR;
		return;
	}

	while( m_bThreadRun )						// m_bThreadRun �� FileRecv �� ȣ���ϴ� ������ �������� ���̴� ���� �̹Ƿ�, �� ���� ���� ���߿� false�� ���ϸ� ��� �����尡 ������.
	{
		::InternetQueryDataAvailable( m_hURL, &dwSize, 0, 0 );

		if ( dwSize > 1000000 )
		{
			char *pText = GetTxtFromMgr(20);
			AfxMessageBox(pText);
			
			::CloseHandle( hFile );
			hFile = NULL;

			::DeleteFile( m_strLocalFileNamePath );			//�޴� ������ ������.
			
			::InternetCloseHandle( m_hURL );
			m_hURL = NULL;

			m_ucDownLoadStatus = DOWNLOAD_SPEED_ERROR;
			m_bThreadRun = false;
			break;
		}

		Result = ::InternetReadFile( m_hURL, Buf, dwSize, &dwRead );

		if ( dwRead == 0 && Result == TRUE )
		{
			::CloseHandle( hFile );
			hFile = NULL;
			::InternetCloseHandle( m_hURL );
			m_hURL = NULL;

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
	
	if ( m_hURL )
	{
		::InternetCloseHandle( m_hURL );
		m_hURL = NULL;
	}	
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - __int64 CHttp::GetFileSize()
//	Desc : ���� ������ ����� ����
//	Date : 2003. 08. 22
//	Update : 
//--------------------------------------------------------------------------------------------
__int64 CHttp::GetFileSize()
{
	return m_dwFileSize;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - __int64	CHttp::GetFileRecvSize()
//	Desc : ���� ������ ����� ����
//	Date : 2003. 08. 22
//	Update : 
//--------------------------------------------------------------------------------------------
__int64	CHttp::GetFileRecvSize()
{
	return m_dwFileRecvSize;
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com) - float CHttp::GetFileRecvPercent()
//	Desc : �� �ۼ�Ʈ �޾Ҵ��� �˾Ƴ��� ���ؼ�...
//	Date : 2003. 06. 23
//	Update : 
//--------------------------------------------------------------------------------------------
DWORD CHttp::GetFileRecvPercent()
{
	DWORD dwDownLoadPercentage = (DWORD)(( m_dwFileRecvSize * 100 ) / m_dwFileSize);

	if ( dwDownLoadPercentage > 100 )
	{
		return 100;
	}

	return dwDownLoadPercentage;
}