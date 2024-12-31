#include "LogPrint.h"

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : �� �� ��
//	Date : 2002. 11. 20
//	Update : 
//--------------------------------------------------------------------------------------------
CLogPrint::CLogPrint()
{
	InitializeCriticalSection(&m_LogCrit);
	//::DeleteFile(TEXT("./Log.txt"));
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : �� �� ��
//	Date : 2002. 11. 20
//	Update : 
//--------------------------------------------------------------------------------------------
CLogPrint::~CLogPrint()
{
	DeleteCriticalSection(&m_LogCrit);
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : ȭ�� ���
//	Date : 2002. 11. 20
//	Update : 2003. 06. 09 - printf ���� OutputDebugString ���� �Լ� ���� ����
//--------------------------------------------------------------------------------------------
void CLogPrint::LogPrint(TCHAR *format,...)
{
#ifdef _DEBUG	

	EnterCriticalSection(&m_LogCrit);

    va_list vl;
    TCHAR    dbgbuf[2048];

    va_start(vl, format);
    StringCchVPrintf(dbgbuf, 2048, format, vl);
    va_end(vl);

    OutputDebugString(dbgbuf);
	//printf(dbgbuf);

	LeaveCriticalSection(&m_LogCrit);

#endif
}

//--------------------------------------------------------------------------------------------
//	Name : Sang Min, Lee (duryzip@hotmail.com)
//	Desc : ���� ���
//	Date : 2002. 11. 20
//	Update : 
//--------------------------------------------------------------------------------------------
void CLogPrint::FilePrint( TCHAR* filename, TCHAR *format,... )
{
	EnterCriticalSection(&m_LogCrit);

    va_list vl;    

    va_start( vl, format );
    StringCchVPrintf( dbgbuf, 2048, format, vl );
    va_end( vl );

    //OutputDebugString(dbgbuf);

	FILE *fp = NULL;

	//fp = _tfopen(TEXT("./Log.txt"), TEXT("a+"));
	fp = _tfopen( filename, TEXT("a+") );

	if ( ! fp )
	{
		//printf(TEXT("File : Log.txt Make Error\n"));
		//StringCchPrintf()

		LeaveCriticalSection(&m_LogCrit);

		return;
	}



	_tstrdate( m_Date );
    //printf( TEXT("Date : %s"), tmpbuf );

	_tstrtime( m_Time );
    //printf( TEXT("Time : %s"), tmpbuf );
	
	_ftprintf( fp, TEXT("%s \t %s \t %s\n"), dbgbuf, m_Date, m_Time );

	fclose(fp);

	LeaveCriticalSection(&m_LogCrit);
}

//--------------------------------------------------------------------------------------------
//	Name : �豤��
//	Desc : ���� ���
//	Date : 2007. 03. 28
//	Update : 
//--------------------------------------------------------------------------------------------
void CLogPrint::FileConfigPrint( TCHAR* filename, TCHAR *format,... )
{
	EnterCriticalSection(&m_LogCrit);

	va_list vl;    

	va_start( vl, format );
	StringCchVPrintf( dbgbuf, 2048, format, vl );
	va_end( vl );

	SYSTEMTIME sysTime;
	GetLocalTime( &sysTime );
	char szDirectoryName[ MAX_PATH ] = {'\0'};
#ifdef _DEBUG
	// �⵵
    _stprintf( szDirectoryName, "c:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear", sysTime.wYear );
	CreateDirectory( szDirectoryName, NULL );

	// �⵵ / �� 
	_stprintf( szDirectoryName, "c:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear\\%dMonth", sysTime.wYear, sysTime.wMonth );
	CreateDirectory( szDirectoryName, NULL );

	// �⵵ / �� / �̸�
	_stprintf( szDirectoryName, "c:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear\\%dMonth\\%s", sysTime.wYear, sysTime.wMonth, filename );
	CreateDirectory( szDirectoryName, NULL );
#else
	// �⵵
	_stprintf( szDirectoryName, "d:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear", sysTime.wYear );
	CreateDirectory( szDirectoryName, NULL );

	// �⵵ / �� 
	_stprintf( szDirectoryName, "d:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear\\%dMonth", sysTime.wYear, sysTime.wMonth );
	CreateDirectory( szDirectoryName, NULL );

	// �⵵ / �� / �̸�
	_stprintf( szDirectoryName, "d:\\GoonZuWorld\\Goonzu_China\\Config\\%dYear\\%dMonth\\%s", sysTime.wYear, sysTime.wMonth, filename );
	CreateDirectory( szDirectoryName, NULL );
#endif

	char szFileName[ MAX_PATH ] = {'\0'};
	if( 10 > sysTime.wMonth && 10 > sysTime.wDay )
		_stprintf( szFileName, "%s\\%s%d%0d%0d.txt", szDirectoryName, filename, sysTime.wYear, sysTime.wMonth, sysTime.wDay );
	else if ( 10 > sysTime.wDay )
	{
		_stprintf( szFileName, "%s\\%s%d%d%0d.txt", szDirectoryName, filename, sysTime.wYear, sysTime.wMonth, sysTime.wDay );
	}
	else
		_stprintf( szFileName, "%s\\%s%d%d%d.txt", szDirectoryName, filename, sysTime.wYear, sysTime.wMonth, sysTime.wDay );

	FILE *fp = _tfopen( szFileName, TEXT("a+") );

	if ( ! fp )
	{
		LeaveCriticalSection(&m_LogCrit);
		return;
	}

	_tstrdate( m_Date );
	//printf( TEXT("Date : %s"), tmpbuf );

	_tstrtime( m_Time );
	//printf( TEXT("Time : %s"), tmpbuf );

	_ftprintf( fp, TEXT("%s \t %s \t %s\n"), dbgbuf, m_Date, m_Time );

	fclose(fp);

	LeaveCriticalSection(&m_LogCrit);

}