//---------------------------------
// 2004/11/27 ���°�
//---------------------------------

#ifndef _MAIN_H
#define _MAIN_H


bool GetGameModeInFile(SI32* pgamemode, SI32* pres, BOOL* bFullScreen, SI32 *siContryCode, SI32* siRunMode );
bool SetGameModeInFile(SI32 gamemode, SI32 res, BOOL bFullScreen, SI32 runmode );
// ���ӹ���
SI32 GetGameVersionInFile();
bool SetGameVersionInFile(SI32 siVersion);

bool GetDefaultServiceArea(SI32* servicearea);
// ���� ���� �ڵ带 �ٰŷ� �������� ������ ��´�. 
SI32 GetServiceAreaFromCode(TCHAR* sztext);
void GetServerNameFromServerUnique(SI32 serverUnqiue, TCHAR* servername);

// ���Ͽ��� FullScreen ���θ� ���´�. 
bool GetFullScreenInFile( BOOL* bFullScreen );
bool SetFullScreenInFile( BOOL bFullScreen );

BOOL CheckDupGame1(TCHAR *name, TCHAR* title);
void CloseDupGameHandle1();

// ��ƼŬ���̾�Ʈ �������� ����
#define	MAX_MULTICLIENT_NUM	2

BOOL CheckMultiClient( void );
// ��ƼŬ���̾�Ʈ �������� ��
#include "dbghelp.h"

// -USE_NELO
#ifdef USE_NELO
	#ifdef _CLIENT
		#include "../HanAuth/NELO/include/NELO.h"
		#ifdef _DEBUG
			#pragma comment(lib, "HanAuth\\NELO\\lib\\NELOD.lib") 
		#else
			#pragma comment(lib, "HanAuth\\NELO\\lib\\NELO.lib") 
		#endif
	#endif
#endif
// -USE_NELO

//--------------------------------------------------------------------------------------------------
// MINI DUMP - by LEEKH 2007.11.15 - ��Ʋ��Ƽī������ �������� ���� ����
//--------------------------------------------------------------------------------------------------
#if defined (USE_MINIDUMP)
// based on dbghelp.h
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
										 CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
										 CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
										 CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam );

class MiniDumper
{
public:
	MiniDumper();
	virtual ~MiniDumper(void);

	static void SetHwnd( HWND hwnd )
	{
		m_hWnd = hwnd;
	}

private:
	static LPCSTR m_szAppName;
	static HWND	  m_hWnd;

	static LONG WINAPI TopLevelFilter( struct _EXCEPTION_POINTERS* exceptioninfo );

};

#endif
//--------------------------------------------------------------------------------------------------


#endif
