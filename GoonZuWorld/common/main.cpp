#include <Mouse.h>
#include <mainfunction.h> 
#include "..\Client\Music\Music.h"
#include "..\MapEdit\MapEdit.h"
#include "Bullet\bullet.h"
#include "Smoke\Smoke.h"

#include "Map\Map.h"
#include "..\Client\Client.h"
#include "..\Server\Server.h"
#include "..\resource.h"
#include "..\Client\Interface\SoundOnOffDlg\SoundOnOffDlg.h"
#include "../Client/NInterface/NSoundOnOffDlg/NSoundOnOffDlg.h"

#include "..\Client\Interface\ServerOnStepNotifyDlg\ServerOnStepNotifyDlg.h"
#include "DevTool\DevCharInfo\DevCharInfo.h"
#include "../Lib/WebHTML/WebHTML.h"
#include "Main.h"
#include "../Client/DLGPositionSave/DLGPositionSave.h"
#include "../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../Client/MiniHomeUpdates/PopupCheck.h"

#include <crtdbg.h>

#include "NUtil.h"
#include "NFile.h"

// BugTrap includes //////////////////////////////////////////////////////////////
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <eh.h>                 // include set_terminate() declaration

// Include main BugTrap header.
#include "../BugTrap/BugTrap.h"

#include "../NLib/NUpdateTimer.h"//딜레이위한 헤더

// Link with one of BugTrap libraries.
#ifdef _UNICODE
#pragma comment(lib, "BugTrap\\BugTrapU.lib")
#else
#pragma comment(lib, "BugTrap\\BugTrap.lib")
#endif

#include "../../NLib/NTech/sdk/nkcore/Include/NkCore.h"
NkCoreInitImplement( NkStaticDataInitor, 0 );

INT_PTR g_iLogHandle = -1;

//--------------------------------------------------------------------------------------------------
// MINI DUMP - by LEEKH 2007.11.15 - 아틀란티카팀에서 가르쳐준 덤프 생성
//--------------------------------------------------------------------------------------------------
#if defined (USE_MINIDUMP)

LPCSTR MiniDumper::m_szAppName;

MiniDumper::MiniDumper()
{
	m_szAppName = "GoonZu";

	::SetUnhandledExceptionFilter( TopLevelFilter );
}

MiniDumper::~MiniDumper(void)
{
}

LONG MiniDumper::TopLevelFilter( struct _EXCEPTION_POINTERS* exceptioninfo )
{
	LONG retval  = EXCEPTION_CONTINUE_SEARCH;
	HWND hParent = NULL; 

	HMODULE hDll = NULL;
	char dbghelp[_MAX_PATH];

	SI32 siGameMode;
	SI32 siRes, siFull, siContryCode, siRunMode;

	bool bEXCEPTION_ARRAY_BOUNDS_EXCEEDED = true;

	// 덤프 출력 옵션파일을 읽는다.
	FILE* fp = fopen("WriteDump.txt", "r");
	if(fp != NULL)
	{
		char szLine[256] = { '\0' };
		char szName[256] = { '\0' };
		SI32 siVal = 0;
		while( fgets(szLine, 256, fp) != NULL )
		{
			sscanf( szLine, "%s %d", szName, &siVal );
			if( _tcscmp(szLine, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED") == 0 )	bEXCEPTION_ARRAY_BOUNDS_EXCEEDED = (siVal == 1);
		}
		fclose(fp);
	}

	bool bWriteDump = true;
	if( exceptioninfo->ExceptionRecord->ExceptionCode == EXCEPTION_ARRAY_BOUNDS_EXCEEDED &&	bEXCEPTION_ARRAY_BOUNDS_EXCEEDED == false)	bWriteDump = false;

	if( bWriteDump )
	{
		GetGameModeInFile(&siGameMode, &siRes, &siFull, &siContryCode, &siRunMode);

		if( GetModuleFileName( NULL, dbghelp, _MAX_PATH ))
		{
			char* pSlash = _tcsrchr( dbghelp, '\\' );
			if( pSlash )
			{
				_tcscpy( pSlash + 1, "DBGHELP.DLL" );
				hDll = ::LoadLibrary( dbghelp );
			}
		}

		if( hDll == NULL )
			hDll = ::LoadLibrary( "DBGHELP.DLL" );

		LPCTSTR result = NULL;

		if( hDll )
		{
			MINIDUMPWRITEDUMP pDump = ( MINIDUMPWRITEDUMP )::GetProcAddress( hDll, "MiniDumpWriteDump" );

			if( pDump )
			{
				TCHAR szDumpFileName[MAX_PATH];

#ifdef _CLIENT_MINIDUMP
				if ( true )
#else
				// 서버일경우
				if( siGameMode == GAMEMODE_SERVER )
#endif
				{
					// 저장파일명 셋팅
					SYSTEMTIME st_Time;
					GetLocalTime(&st_Time);

					StringCchPrintf(szDumpFileName, sizeof(szDumpFileName), TEXT("C:\\GoonZuDump\\GoonZu_%04d%02d%02d_%02d%02d%02d.dmp"), 
						st_Time.wYear, st_Time.wMonth, st_Time.wDay, st_Time.wHour, st_Time.wMinute, st_Time.wSecond );

					CreateDirectory("C:\\GoonZuDump",NULL);
				}

				HANDLE hFile = NULL;
				if(_tcslen(szDumpFileName) > 0)
				{
					// 덤프파일 생성
					hFile = ::CreateFile(	szDumpFileName, 
											GENERIC_WRITE, 
											FILE_SHARE_WRITE, 
											NULL, 
											CREATE_ALWAYS,
											FILE_ATTRIBUTE_NORMAL, 
											NULL );
				}

				if( hFile != INVALID_HANDLE_VALUE )
				{

					_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

					ExInfo.ThreadId			 = ::GetCurrentThreadId();
					ExInfo.ExceptionPointers = exceptioninfo;
					ExInfo.ClientPointers	 = NULL;

					// write the dump
					BOOL bOK = pDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );

					::CloseHandle( hFile );
				}
			}
		}
	}

	// 배열 인덱스 초과는 정상처리로 돌린다.
	if( exceptioninfo->ExceptionRecord->ExceptionCode == EXCEPTION_ARRAY_BOUNDS_EXCEEDED )
		retval = EXCEPTION_CONTINUE_EXECUTION;

	return retval;
}

#endif
//--------------------------------------------------------------------------------------------------

#ifdef _CHINA
	#ifdef _DEBUG
	#else
		#ifdef _SERVER
		#else
			static void SetupExceptionHandler()
			{
				// required since VS 2005 SP1
				BT_InstallSehFilter();

				// Setup exception handler
			#ifdef _SERVER
			//	BT_SetAppName(_T("GoonzuBugServerReport"));
			#else
				BT_SetActivityType(BTA_SENDREPORT);
				BT_SetAppName(_T("GoonzuBugClinetReport"));
			#endif
				BT_SetSupportEMail(_T(""));
				BT_SetFlags(BTF_DETAILEDMODE);

				// = BugTrapServer ===========================================
				BT_SetSupportServer(_T("222.246.132.110"), 9999);
				// - or -
				//BT_SetSupportServer(_T("127.0.0.1"), 9999);

				// = BugTrapWebServer ========================================
				//BT_SetSupportServer(_T("http://localhost/BugTrapWebServer/RequestHandler.aspx"), BUGTRAP_HTTP_PORT);

				// Add custom log file using default name
				g_iLogHandle = BT_OpenLogFile(NULL, BTLF_TEXT);
				BT_SetLogSizeInEntries(g_iLogHandle, 100);
				BT_SetLogFlags(g_iLogHandle, BTLF_SHOWTIMESTAMP);
				BT_SetLogEchoMode(g_iLogHandle, BTLE_STDERR | BTLE_DBGOUT);

				PCTSTR pszLogFileName = BT_GetLogFileName(g_iLogHandle);
				BT_AddLogFile(pszLogFileName);
			}
		#endif
	#endif
#endif

// BugTrap includes //////////////////////////////////////////////////////////////

SI16 g_siChannelingCode;
char g_nm_id[ 1024 ];
char g_nm_pw[ 1024 ];

// WEB LOGIN SERVICE
char g_szWeb_id[ 1024 ];
char g_szWeb_pw[ 1024 ];
bool g_bWebLoginService;

bool g_bHanAuth;


//[진성] USA 새로운 인증.
bool g_bUSA_Auth;

//KHY - 0204 -  중국 PurpleAuth 인증 모듈
#ifdef USE_PORTEAUTH
bool g_bPorteAuth;
char g_szServerIP[20]; // 인증서버 IP
char g_szServerPORTE[10]; // 인증서버 PORTE
#endif

//PCK : IOVATION 인증 모듈
bool	g_bIovationAuth;

DWORD dwQuitTimer;

// 클라이언트 통합 객체. 
cltCommonLogic *pclClient;

// 게임가드 전역 객체
#ifdef USE_GAME_GUARD_CLIENT
	CNPGameLib * pNpgl = NULL;
	TCHAR g_szHackMsg[256] = { 0 };
#endif

// 활성화 여부 
bool		bActiveSwitch;	
SI32		gsiResolution;				// 게임의 해상도. 
BOOL		g_bFullScreen = TRUE;		// 풀스크린 여부 
SI32		g_siContryCode = 0;			// 국가(언어) 코드
//SI32		g_siRunMode = 0;			// 실행 모드

SI32		g_siServiceAreaCode = 0 ;	// 서비스 코드

// 게임에서 사용되는 변수 
RECT		ScreenRect;					// 지도가 표시되는 영역 

HINSTANCE	g_hInstance;
HINSTANCE	g_hIMEDll = NULL;
HINSTANCE	g_hVersionIMEDll = NULL;

LPDIRECTDRAWSURFACE7 g_lpBackScreen = NULL;	// 게임이 그려질 화면 뒤의 서피스. 
bool		g_bCreate = false;

HANDLE FileMapHandle1;
// USE_NELO
#ifdef USE_NELO
	#ifdef _CLIENT
		NELO_HANDLE								hNELO = NULL	;
	#endif _CLIENT
#endif USE_NELO
// USE_NELO


BOOL CheckDupGame1(TCHAR *name, TCHAR* title)
{
	FileMapHandle1 = CreateFileMapping((HANDLE)0xffffffff, NULL, PAGE_READWRITE, 0, 1024, name);
	if(FileMapHandle1 != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return TRUE;
	}

	return FALSE;
}

void CloseDupGameHandle1()
{
	if(FileMapHandle1)
		CloseHandle(FileMapHandle1);
}

BOOL CheckMultiClient()
{
	SI32	siCheckIndex		= 0;
	char	szUniqueMutex[1024]	= "";
	
	for ( siCheckIndex=0; siCheckIndex<MAX_MULTICLIENT_NUM; siCheckIndex++ )
	{
		// 유니크한 뮤텍스 인덱스 설정후
		ZeroMemory( szUniqueMutex, sizeof(szUniqueMutex) );
		sprintf( szUniqueMutex, "GOONZU_MUTEX_UNIQUE_%02d", siCheckIndex );

		// 무텍스 생성
		HANDLE hUniqueMutex = CreateMutex( NULL, TRUE, szUniqueMutex );

		// 이미 만들어진 것이라면 이것은 기존에 다른 클라가 생성한 것이다
		if ( ::GetLastError() == ERROR_ALREADY_EXISTS )
		{
			CloseHandle( hUniqueMutex );

			// 다음 뮤텍스가 존재하는지 검사하기위해서 여기에서 컨티뉴
			continue;
		}

		break;
	}

	// 검사한 후 
	if ( MAX_MULTICLIENT_NUM <= siCheckIndex )
	{
		return TRUE;
	}

	return FALSE;
	
}

int GetArgument(char* pszString, char* pszOut, SI32 siOutLen)
{
	bool	bQuotation = false;
	SI32	siPtr = 0;
	SI32	siOut = 0;

	if(pszString[siPtr] == '\"' || pszString[siPtr] == '\'')
	{
		bQuotation = true;
		pszOut[siOut++] = pszString[siPtr];
		siPtr++;
	}
	
	while(siOut < siOutLen && pszString[siPtr] != '\0')
	{
		if(pszString[siPtr] == ' ')
		{
			if(bQuotation == false)		break;
			pszOut[siOut++] = pszString[siPtr];
		}
		else if(pszString[siPtr] == '\'' || pszString[siPtr] == '\"')
		{
			pszOut[siOut++] = pszString[siPtr];
			break;
		}
		else
		{
			pszOut[siOut++] = pszString[siPtr];
		}
		siPtr++;
	}

	pszOut[siOut] = '\0';

	//if(bQuotation == true)		siOut += 2;

	return siOut;
}

int MakeArgument( TCHAR* pszString, TCHAR** pszArgc )
{
	bool	bQuotation = false;
	SI32	siPtr = 0;
	SI32	siCount = 0;

	pszArgc[siCount] = pszString;

	if(pszString[siPtr] == '\"' || pszString[siPtr] == '\'')
	{
		bQuotation = true;
		siPtr++;
	}

	while(pszString[siPtr] != '\0')
	{
		if(pszString[siPtr] == ' ')
		{
			if(bQuotation == false)
			{
				siCount++;
				pszString[siPtr] = '\0';
				pszArgc[siCount] = &pszString[siPtr+1];
			}
		}
		else if(pszString[siPtr] == '\'' || pszString[siPtr] == '\"')
		{
			bQuotation = !bQuotation;
		}
		siPtr++;
	}

	return siCount;
}

//--------------------------------------------------------------------------
// Name: WinMain()
// Desc: 윈도우 Main 함수 
//--------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// -USE_NELO 크래싱 모듈이라서 생성 하면서 바로 핸들을 만든다.
#ifdef USE_NELO
	#ifdef _CLIENT
		hNELO = NELO_Create( "C_GZ","1.0.0.3","新樂君主");
		if ( hNELO != NULL)
		{
			// 핸들이 널이 아닐때 넬로를 셋팅하고 시작한다.
			NELO_SetReportServer(hNELO,"ecs.naver.com",10007);	// 서버 셋팅
			NELO_SetAutoReport(true);							// 자동 리포트 기능 활선화
			NELO_StartCrashHandler(hNELO);						// 서버 시작
			NELO_SendLog_TCP(hNELO,NELLO_LL_INFO,"TCPSENDLOG","NELOSTART","NULL");
			NELO_SendLog_UDP(hNELO,NELLO_LL_INFO,"UDPSENDLOG","NELOSTART","NULL");
		}
	#endif _CLIENT
#endif USE_NELO
	// -USE_NELO

	//_CrtSetBreakAlloc(6920);

	// 크리티컬 오류 팝업
	size_t	size_Item =		sizeof(cltItem);
	size_t	size_Itemdata	= sizeof(cltItemData);
	if( size_Item != size_Itemdata )
	{
		MessageBox( NULL, "ERROR", "아이템구조체의 크기가 틀립니다.", MB_OK );
	}

	//-------------------------------------------------------------------------------
	// 실행파일에 붙어오는 인자값 처리
	// 배열 0번째 Argument는 항상 실행파일명이도록 처리한다.
	//-------------------------------------------------------------------------------
	TCHAR* pszCmdLine = GetCommandLine();
	SI32 siCmdLineSize = _tcslen(pszCmdLine);
	TCHAR* pszArgs = new TCHAR[siCmdLineSize + 1];	if( pszArgs == NULL )		return -1;
	_tcsncpy(pszArgs, pszCmdLine, siCmdLineSize);	pszArgs[siCmdLineSize] = '\0';

	TCHAR* pszArgv[32];		ZeroMemory(pszArgv, sizeof(pszArgv));
	SI32   siArgc = MakeArgument(pszArgs, pszArgv);

	TCHAR szModuleFileName[MAX_PATH];
	NTCHARStringPath	kModuleFileName;;
	GetModuleFileName( NULL, szModuleFileName, sizeof(szModuleFileName));
	kModuleFileName = "\"";	kModuleFileName += szModuleFileName;	kModuleFileName += "\"";
	if( siArgc <= 0 || pszArgv[0] == NULL )		{		siArgc = 1;		pszArgv[0] = kModuleFileName;	}
	
	TCHAR* pszArg0 = &pszArgv[0][0];
	if( pszArgv[0][0] == '\"' ||  pszArgv[0][0] == '\'' )	{		pszArg0 = &pszArgv[0][1];		}
	if( _tcsncmp( pszArg0, szModuleFileName, sizeof(szModuleFileName) ) != 0 )
	{
		// ARG0이 실행 파일이 아닌 경우
		for( SI32 i=siArgc; i >= 0; i-- )
		{
			pszArgv[i+1] = pszArgv[i];
		}
		siArgc++;
		pszArgv[0] = kModuleFileName;
	}
	//-------------------------------------------------------------------------------

#ifdef _CHINA
	#ifdef _DEBUG
	#else
		#ifdef _SERVER
		#else
//			SetupExceptionHandler();
		#endif
	#endif
#endif

#if defined (USE_MINIDUMP)
	MiniDumper		GoonZuDump;
#endif
	//---------------------------------------------------------------------------------
	// 넷마블 id, pw 인자를 넘겨 받는지 검사..
	g_siChannelingCode = 0;

	//---------------------------------------------------------------------------------
	// NHN GameString
	g_bHanAuth	= false;

	//[진성] USA 새로운 인증.
	g_bUSA_Auth		 = false;
	
	//PCK : IOVATION 인증 모듈
	g_bIovationAuth = false;

#ifdef USE_HANAUTH
	char	szHanAuth_GameString[SIZE_GAMESTRING];
#endif //USE_HANAUTH

#ifdef _USA_NEW_AUTH_
	char	szUSAAuth_GameString[4096];
#endif //USE_HANAUTH

//KHY - 0204 -  중국 PurpleAuth 인증 모듈
#ifdef USE_PORTEAUTH
	g_bPorteAuth = false;
#ifndef _SERVER //서버가 정의되어 있지 않다면.
	char	szPorteAuth_GameInfoString[SIZE_GAMEINFOSTRING];
#endif
#endif // USE_PORTEAUTH	


// 일본 서비스
#ifdef _JAPAN
#ifndef _DEBUG
	{

		char szCmdLine[ 10 ][ 1024 ];
		for( int i = 0; i < 10; ++i ) szCmdLine[ i ][ 0 ] = NULL;

		char *temp;
		char *argv;
		char *token;
		char seps[] = " "; 

		temp = argv = GetCommandLine(); 

		int c = 0;
		while( c < 2 && *argv ) {
			if( *argv == '\"' ) ++c;
			++argv;
		}
		
		if( c < 2 ) argv = temp;
		c = 0;	

		if( argv ) {

			if( *argv == ' ' ) ++argv;

			token = strtok( argv, seps );
			while( token != NULL && c < 9 ) {

				if( token ) {		
					strcpy( szCmdLine[ c ], token );
				}
				++c;

				token = strtok(NULL, seps);
			}
		}

		g_nm_id[0] = '\0';
		g_nm_pw[0] = '\0';
		
		//---------------------------------------------------------
		//KHY - 0617 - 일본 채널링 추가. - 웹로그인의 경우에만 채널링 표시.
		//---------------------------------------------------------
		if( szCmdLine[0][0] && szCmdLine[1][0] && strcmp( szCmdLine[2], "HANGAMEJP") == 0 )
		{
			g_siChannelingCode = CHANNELINGCODE_HANGAMEJP;
			strcpy(  g_nm_id , szCmdLine[0] );
			strcpy(  g_nm_pw , szCmdLine[1] );
		}
		else if( szCmdLine[0][0] && szCmdLine[1][0] && strcmp( szCmdLine[2], "GAMANIAJP") == 0 )
		{
			g_siChannelingCode = CHANNELINGCODE_GAMANIAJP;
			strcpy(  g_nm_id , szCmdLine[0] );
			strcpy(  g_nm_pw , szCmdLine[1] );
		}
		else if( szCmdLine[0][0] && szCmdLine[1][0] && strcmp( szCmdLine[2], "GAMEPOTJP") == 0 )
		{
			g_siChannelingCode = CHANNELINGCODE_GAMEPOTJP;
			strcpy(  g_nm_id , szCmdLine[0] );
			strcpy(  g_nm_pw , szCmdLine[1] );
		}
		else if( szCmdLine[0][0] && szCmdLine[1][0] && strcmp( szCmdLine[2], "NEXONJP") == 0 )
		{
			g_siChannelingCode = CHANNELINGCODE_NEXONJP;
			strcpy(  g_nm_id , szCmdLine[0] );
			strcpy(  g_nm_pw , szCmdLine[1] );
		}
		else  // NDE 는 웹 로근인이 아니다.
		{
			g_siChannelingCode = 0; 
		}
		/*
		else if( szCmdLine[0][0] && szCmdLine[1][0] )
		{
			g_siChannelingCode = CHANNELINGCODE_NETMARBLEJP;
			strcpy(  g_nm_id , szCmdLine[0] );
			strcpy( g_nm_pw , szCmdLine[1] );
		}
		*/
		//---------------------------------------------------------
	}
#endif
#endif

	// 대만 서비스
#ifdef _TAIWAN
#ifndef _DEBUG

	char *argv;
	SI32 siPtr = 0;
	char szFileName[MAX_PATH];
	SI32 siLen = 0;
	argv = GetCommandLine();

	// 실행파일명
//	siLen = GetArgument(&argv[siPtr], szFileName, MAX_PATH);
//	siPtr += siLen;
//	siPtr++;

	// 첫번째 Argument
	siLen = GetArgument(&argv[siPtr], g_szWeb_id, 1024);
	siPtr += siLen;
	siPtr++;

	// 첫번째 Argument
	siLen = GetArgument(&argv[siPtr], g_szWeb_pw, 1024);
	siPtr += siLen;
	siPtr++;

	g_bWebLoginService = true;

	//TCHAR szBuf[256];
	//wsprintf(szBuf, "WEBID:%s, WEBPW:%s", g_szWeb_id, g_szWeb_pw);
	//MessageBox(NULL, szBuf, "DEBUG", MB_OK);

#endif
#endif

#ifdef USE_HANAUTH
	{
		char *argv;
		SI32 siPtr = 0;
		char szFileName[MAX_PATH];
		SI32 siLen = 0;
		argv = GetCommandLine();

		// 실행파일명
		siLen = GetArgument(&argv[siPtr], szFileName, MAX_PATH);
		siPtr += siLen;
		siPtr++;
		// 첫번째 Argument
		siLen = GetArgument(&argv[siPtr], szHanAuth_GameString, SIZE_GAMESTRING);

		// 해당 변수가 true이면 한게임 인증을 사용한다.
		g_bHanAuth = true;

		//if(strlen(szHanAuth_GameString) > 0)
		//	MessageBox(NULL, szHanAuth_GameString, TEXT("HanAuth"), MB_OK);

		HanAuthMiniExplorer( false );	// 익스플로러 감추기
	}
#endif // USE_HANAUTH

//KHY - 0204 -  중국 PurpleAuth 인증 모듈
#ifdef USE_PORTEAUTH
#ifndef _SERVER //서버가 정의되어 있지 않다면.
	{
		char *argv;
		SI32 siPtr = 0;
		char szFileName[MAX_PATH];
		SI32 siLen = 0;
		argv = GetCommandLine();

#if 1 // 주의하자~!
		// 실행파일명
		siLen = GetArgument(&argv[siPtr], szFileName, MAX_PATH);
		siPtr += siLen;
		siPtr++;
		// 첫번째 Argument
		siLen = GetArgument(&argv[siPtr], szPorteAuth_GameInfoString, SIZE_GAMEINFOSTRING);

		// 두번째 Argument - 인증서버 접속용 IP가 들어올 예정.
		//siLen = GetArgument(&argv[siPtr], g_szServerIP, 20);
#else
		strcpy(  szPorteAuth_GameInfoString , 
			"P=&P0=bmRvb3JzMDg=&P1=Q19HWg==&P2=NDM1Ng==&P4=QzRVK3RuUTAxRytpbmNvRUE4K0YxYUZaeHJsc3dScmVRYTlNMXpicXp0aldtTk9FcnRqMWZkbzIxVCs4amhDMm5hamI2RDJIYW0wbG84cndHNlk5d3NKd2VkVWNXb0Nzb2xTdkluT1RDSXM2dkVvOXV1L2taSERybm1ZWGJiYVp5SzFNdjBYdjhIeHVOY2Z1ZHBNdlVDc0R1UWp5aTE0anhhY0pZL0c4b0FvaDRxN1V3dUg3STZiazhMbE5hZXUw&P5=dmY=&PC1=Tg==&PC2=Tg==&H1=&H2=");

		strcpy(  g_szServerIP , 
			"116.127.220.204"
			);

		// 임시 주석.
		if(strlen(szPorteAuth_GameInfoString) > 0)
			MessageBox(NULL, szPorteAuth_GameInfoString, TEXT("PurpleAuth"), MB_OK);
#endif

		// 해당 변수가 true이면 PurpleAuth 인증을 사용한다.
		g_bPorteAuth = true;

	}
#endif
#endif // USE_PORTEAUTH

#ifdef _IOVATION
	#ifdef _USA_NEW_AUTH_
		//진성 test
		//MessageBox(NULL, "으~ 짱나!!", TEXT("USA 이관작업이다."), MB_OK);
		
		char *argv;
		SI32 siPtr = 0;
		char szFileName[MAX_PATH];
		char szidentity[8];
		SI32 siLen = 0;
		argv = GetCommandLine();

		// 실행파일명
		siLen = GetArgument(&argv[siPtr], szFileName, MAX_PATH);
		siPtr += siLen;
		siPtr++;

		// 첫번째 Argument (인증스트링)
		siLen = GetArgument(&argv[siPtr], szUSAAuth_GameString, 4096);

		// 인증스트링이 10개 이상 넘어오면 USA로 실행, 아니면 글로벌로 실행
		if( 10 < strlen(szUSAAuth_GameString) )
		{
			// 해당 변수가 true이면 한게임 인증을 사용한다.
			g_bUSA_Auth = true;
		}
		else
	#endif
		{
			g_bIovationAuth = true;
		}
#endif

	#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//		_CrtSetBreakAlloc( 25146 );
	#endif

	// 입력 Argument 처리 메모리 해제
	delete[] pszArgs;

	SI32 gamemode	= 0; // 1: Server 2: Client 3: MapEdit
	SI32 runmode	= 0; // 1: Server 2: Client 3: MapEdit

	if(GetGameModeInFile(&gamemode, &gsiResolution, &g_bFullScreen, &g_siContryCode, &runmode ) == false)
	{
		return FALSE ;
	}

	// FullScreen 여부를 얻어온다.
	GetFullScreenInFile( &g_bFullScreen );

	int status=0;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	static int index=0;

	int x, y;

	DWORD windowstyle;

	DWORD dwwidth, dwheight, dwcaptionheight;

	// 디폴트 서비스 지역을 찾는다. 
	SI32 defaultservicearea = 0;
	if(GetDefaultServiceArea(&defaultservicearea) == false)
	{
	}

/*
	// 디폴트 서비스 지역이랑 서비스 코드가 다르면 실행 못한다.
	if ( g_siServiceAreaCode != 0 && g_siServiceAreaCode != defaultservicearea )
		return FALSE ;
*/

	TCHAR NAME[20] = TEXT("") ;
	TCHAR TITLE[20] = TEXT("") ;

	// 한국 HANGAME 서비스 명
	if ( defaultservicearea == ConstServiceArea_Korea )
	{
		MStrCpy(NAME,TEXT("군주 Special"),20);
		MStrCpy(TITLE,TEXT("군주 Special"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_China )
	{
		if( GAMEMODE_CLIENT == gamemode )
		{
			MStrCpy(NAME,TEXT("뻑있엌寮"),20);
			MStrCpy(TITLE,TEXT("뻑있엌寮"),20);
		}
		else
		{
			MStrCpy(NAME,TEXT("GoonzuChina"),20);
			MStrCpy(TITLE,TEXT("GoonzuChina"),20);
		}
	}
	else if ( defaultservicearea == ConstServiceArea_Japan )
	{
		MStrCpy(NAME,TEXT("똍롥"),20);
		MStrCpy(TITLE,TEXT("똍롥"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_English )
	{
		MStrCpy(NAME,TEXT("GoonZu"),20);
		MStrCpy(TITLE,TEXT("GoonZu"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_Taiwan )
	{
		MStrCpy(NAME,TEXT("GoonZu-Taiwan"),20);
		MStrCpy(TITLE,TEXT("GoonZu-Taiwan"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_USA  )
	{
		MStrCpy(NAME,TEXT("Luminary"),20);
		MStrCpy(TITLE,TEXT("Luminary"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_EUROPE )
	{
		MStrCpy(NAME,TEXT("Luminary"),20);
		MStrCpy(TITLE,TEXT("Luminary"),20);
	}
	else if ( defaultservicearea == ConstServiceArea_NHNChina )
	{
		MStrCpy(NAME,TEXT("뻑있엌寮"),20);
		MStrCpy(TITLE,TEXT("뻑있엌寮"),20);
	}

	//------------------------------------------------------------
	// 윈도우 만들기 
	//------------------------------------------------------------
	HWND hwnd;
	WNDCLASS wc;

	wc.style=/*CS_HREDRAW|CS_VREDRAW|*/CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc=WindowProc;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON_GOONZU));
	wc.hCursor=LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName=NAME;
	wc.lpszClassName=NAME;
	RegisterClass(&wc);
	
	g_hInstance = hInstance;

	if( g_bFullScreen )
	{	
		windowstyle = WS_POPUP;
		x = 0;
		y = 0;

		dwwidth = (DWORD)CW_USEDEFAULT;
		dwheight = (DWORD)CW_USEDEFAULT;

		dwcaptionheight = 0;

	}
	else
	{
		windowstyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
		x = 0;
		y = 0;

		dwwidth = 800;
		dwheight = 600;
		
		// 비스타 인지 체크 해서 창 사이즈를 가로, 세로 3픽셀식 줄여준다. 
		// 여의치 않다면 서페이스를 늘려주는 방안을 검토해 볼참. [영진]
		
		
		
		OSVERSIONINFOEX osvi;
		//BOOL bOsVersionInfoEx;

		ZeroMemory( &osvi , sizeof(OSVERSIONINFOEX) );
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		
		// 성공적으로 운영체제 정보를 읽어왔다면
		bool bOsVersinInfoGet = false;
		bool bIsVista = false;

		// Ex 함수로 못읽어 오면 걍 함수로 읽어온다
		if( GetVersionEx((OSVERSIONINFO*)&osvi) )
		{
			bOsVersinInfoGet = true;			
		}
		else
		{
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			if( GetVersionEx((OSVERSIONINFO*)&osvi) )
			{
				bOsVersinInfoGet = true;			
			}
			else
			{
				bOsVersinInfoGet = false;			
			}
		}

		// OS 정보를 성공적으로 읽어온 경우 비스타인지 판별한다
		if(bOsVersinInfoGet == true)
		{
			if( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT )
			{
				// 비스타인가?
				if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 && osvi.wProductType == VER_NT_WORKSTATION )
				{
                    bIsVista = true;

					dwwidth = 797;
					dwheight = 597;
				}
				// 윈도우 7
				else if( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1 && osvi.wProductType == VER_NT_WORKSTATION )
				{
					dwwidth = 797;
					dwheight = 597;
				}
			}
		}



		/*
		dwwidth			= GetSystemMetrics(SM_CXSIZEFRAME);
		dwheight		= GetSystemMetrics(SM_CYSIZEFRAME);
		*/

		dwcaptionheight	= GetSystemMetrics(SM_CYCAPTION);
	}
	
	hwnd=CreateWindowEx
		(
		//WS_EX_OVERLAPPEDWINDOW,
        WS_EX_APPWINDOW,
        NAME,
        TITLE,
        windowstyle,
		x, y,
		dwwidth,
		dwheight,
		NULL, 
		NULL,
		hInstance,
		NULL);

	if(hwnd==NULL)
		return FALSE;

	HANDLE	hMutex = NULL;

#ifndef _DEBUG

	#ifndef _CHINA
	#ifndef _KOREA
	#ifndef _TAIWAN
	#ifndef _NHN_CHINA
		// 중복된 게임이 있는지 확인한다. 
		if( (_taccess( TEXT("Config/master.dat"), 0 )) == -1)
		{
			if( CheckDupGame1(NAME, TITLE) == TRUE )
			{
				SetForegroundWindow( FindWindowEx( NULL, NULL, NAME, TITLE ) );
				CloseDupGameHandle1();

				return FALSE;
			}
		}
	#endif
	#endif
	#endif
	#endif
	
	#ifdef _NHN_CHINA
		// NHN중국은 멀티 제한 개수가 다르기 때문에 새로운 루틴으로 검사한다
		if ( TRUE == CheckMultiClient() )
		{
			return FALSE;
		}
	#endif

#endif

	if( g_bFullScreen )
	{
		ShowWindow( hwnd, nCmdShow );
		UpdateWindow(hwnd);
	}

	g_hIMEDll = LoadLibrary( TEXT("imm32.dll") );
	g_hVersionIMEDll = LoadLibrary( TEXT("version.dll") );


	//-----------------------------------------
	// 해상도를 결정한다. 
	//-----------------------------------------
	//-------------------------------------
	// 윈도우 해상도 체크
	//-------------------------------------
	// KHY - 1218 - 1024x600 해상도 추가. imsi

	if(g_SoundOnOffDlg.m_bBigDisplayMode == 1) // 디폴트가 true 이기 때문에  항상 1024x768 이 기본이다.
	{
		gsiResolution	= 2; // 1024x768
		
	//	if (gamemode== GAMEMODE_MAPEDIT )
	//	{
	//		gsiResolution = 3 ;
	//	}
	}
	else
	{
		gsiResolution	= 1; // 800x600 - 들어갈 일이 없다.
	}

	//게임모드가 서버가 아닐때 해상도 체크.
	if( gamemode != 1) 
	{
		
			RECT rc;
			::GetWindowRect(GetDesktopWindow(), &rc);

			//if( (rc.right - rc.left < 1024) || (rc.bottom - rc.top < 768) )
			if( (rc.right - rc.left < 1024) || (rc.bottom - rc.top < 600) )
			{
				TCHAR* pTitle = GetTxtFromMgr(836);
				TCHAR* pText = GetTxtFromMgr(7103);

				MsgBox(pTitle, pText);
		#ifdef USE_GAME_GUARD_CLIENT
				SAFE_DELETE(pNpgl);
		#endif
				SAFE_DELETE(pclClient);
				
				// 프로그램 종료
				return FALSE;
			}
		

			else if (rc.bottom - rc.top == 600)
			{
				gsiResolution	= 4; // 1024x600		
			}

	}

	//----------------------------------------

	//-----------------------------------------
	// 다이얼로그 위치 파일을 불러온다. 
	//-----------------------------------------
	g_DlgPositionSave.LoadPosition();

	// 클라이언트 객체를 만든다.
	if(gamemode == 1)
	{
		ShowWindow(hwnd, SW_SHOWNORMAL );
		UpdateWindow(hwnd);

//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

		pclClient = NkNew cltServer( NAME, hwnd, hInstance, GAMEMODE_SERVER, defaultservicearea, runmode );

#else

		MessageBox(NULL, TEXT("can't execute mode"), TEXT("exe"), MB_OK|MB_TOPMOST);
		return FALSE;

//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
	}
	else
	{
		/*
		if ( CreateDirectDraw( hwnd, g_SoundOnOffDlg.m_bBigDisplayMode?MODE_GRAPHICS1024_768:MODE_GRAPHICS800_600 ) == FALSE )
		{
			MessageBox( NULL, TEXT("DDraw Init Fail"), TEXT("Error"), MB_OK );
		}
		*/

		if(gamemode == 2)
		{
			//g_ServerOnStepNotifyDlg.Create( hInstance, hwnd, GAMEMODE_CLIENT ,g_SoundOnOffDlg.m_bBigDisplayMode?MODE_GRAPHICS1024_768:MODE_GRAPHICS800_600 , defaultservicearea );

			// KHY - 1218 - 1024x600 해상도 추가. imsi
			SI16 ScreenMode = 0;

			switch(gsiResolution)
			{
				case 2:
					ScreenMode = MODE_GRAPHICS1024_768;
					break;
				case 4:
					ScreenMode = MODE_GRAPHICS1024_600;
					break;
				case 1:
					ScreenMode = MODE_GRAPHICS800_600;
					break;
				default:
					break;
			}

			g_ServerOnStepNotifyDlg.Create( hInstance, hwnd, GAMEMODE_CLIENT ,ScreenMode , defaultservicearea );

#ifdef USE_HANAUTH
			pclClient = new cltClient( NAME, hwnd, hInstance, GAMEMODE_CLIENT, defaultservicearea, szHanAuth_GameString, runmode);
#else
	#ifdef _USA_NEW_AUTH_
			if( g_bUSA_Auth )
			{
				//MessageBox(NULL, "USA 클라이언트 객체 생성및 초기화", TEXT("클라이언트 초기화"), MB_OK);
				pclClient = new cltClient( NAME, hwnd, hInstance, GAMEMODE_CLIENT, defaultservicearea, szUSAAuth_GameString, runmode);
			}
			else
			{
				pclClient = new cltClient( NAME, hwnd, hInstance, GAMEMODE_CLIENT, defaultservicearea, NULL, runmode);
			}
	#else
		//KHY - 0204 -  중국 PurpleAuth 인증 모듈
		#ifdef USE_PORTEAUTH
			#ifndef _SERVER //서버가 정의되어 있지 않다면.
					pclClient = NkNew cltClient( NAME, hwnd, hInstance, GAMEMODE_CLIENT, defaultservicearea, szPorteAuth_GameInfoString, runmode);
			#endif
		#else
				pclClient = NkNew cltClient( NAME, hwnd, hInstance, GAMEMODE_CLIENT, defaultservicearea, NULL, runmode);
		#endif
	#endif
#endif

			cltClient* pclclient = (cltClient*)pclClient;


			// 게임가드 초기화 및 결과 처리
#ifdef USE_GAME_GUARD_CLIENT

			if( defaultservicearea == ConstServiceArea_Korea )
			{
#ifdef USE_HANAUTH
				if(pclclient->m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
				{
					pNpgl = new CNPGameLib("GoonzuSKRTest");
				}
				else
				{
					pNpgl = new CNPGameLib("GoonzuSKR");
				}
#else //USE_HANAUTH
				pNpgl = new CNPGameLib("GoonzuSKR");
#endif //USE_HANAUTH
			}
			else if( defaultservicearea == ConstServiceArea_Taiwan )
			{
				if( pclClient->siRunMode == RUNMODE_REAL )
				{
					pNpgl = new CNPGameLib("GoonzuTW");
				}
				else if ( pclClient->siRunMode == RUNMODE_TEST )
				{
					pNpgl = new CNPGameLib("GoonzuTWTEST");
				}
			}			
			else if( defaultservicearea == ConstServiceArea_USA )
			{
#ifdef USE_HANAUTH
				if(pclclient->m_siHanAuth_ServiceTypeCode == SERVICE_ALPHA)
				{
					pNpgl = new CNPGameLib("GoonzuUSTest");
				}
				else
				{
					pNpgl = new CNPGameLib("GoonzuUS");
				}
#else //USE_HANAUTH
			pNpgl = new CNPGameLib("GoonzuUS");
#endif //USE_HANAUTH
			}

			DWORD dwResult = pNpgl->Init();
			//pclClient->pclLog->FilePrint( "config\\nProtectLog.txt" , "pNpgl->Init()" );

			if( dwResult != NPGAMEMON_SUCCESS )
			{				
				TCHAR msg[256];
				LPCSTR lpszMsg;

				//  '주요에러코드'를 참조하여 상황에 맞는 메시지를 출력해줍니다.
				switch (dwResult)
				{
				case NPGAMEMON_ERROR_EXIST:
#ifdef _KOREA
					lpszMsg = "게임가드가 실행 중 입니다. 잠시 후나 재부팅 후에 다시 실행해보시기 바랍니다.";
#else
					lpszMsg = "GameGuard is already running. Try rebooting first and executing the game again.";
#endif
					break;
				case NPGAMEMON_ERROR_GAME_EXIST:
#ifdef _KOREA
					lpszMsg = "게임이 중복 실행되었거나 게임가드가 이미 실행 중 입니다. 게임 종료 후 다시 실행해보시기 바랍니다.";
#else
					lpszMsg = "There are multiple events of game execution or GameGuard is already running. Close the game then try again.";
#endif
					break;
				case NPGAMEMON_ERROR_INIT:
#ifdef _KOREA
					lpszMsg = "게임가드 초기화 에러입니다. 재부팅 후 다시 실행해보거나 충돌할 수 있는 다른 프로그램들을 종료한 후 실행해 보시기 바랍니다.";
#else
					lpszMsg = "GameGuard initialization error. Try rebooting and executing the game or close the program considered to cause a collision.";
#endif					break;
				case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
				case NPGAMEMON_ERROR_NFOUND_GG:
				case NPGAMEMON_ERROR_AUTH_INI:
				case NPGAMEMON_ERROR_NFOUND_INI:
#ifdef _KOREA
					lpszMsg = "게임가드 파일이 없거나 변조되었습니다. 게임가드 셋업 파일을 설치해보시기 바랍니다.";
#else
					lpszMsg = "GameGuard file does not exist or is corrupted. Please install the GameGuard setup file.";
#endif
					break;
				case NPGAMEMON_ERROR_CRYPTOAPI:
#ifdef _KOREA 
					lpszMsg = "윈도우의 일부 시스템 파일이 손상되었습니다. 인터넷 익스플로러(IE)를 다시 설치해보시기 바랍니다.";
#else
					lpszMsg = "Window system files might be corrupted. Please reinstall the Internet Explorer(IE).";
#endif
					break;
				case NPGAMEMON_ERROR_EXECUTE:
#ifdef _KOREA
					lpszMsg = "게임가드 실행에 실패했습니다. 게임가드 셋업 파일을 다시 설치해보시기 바랍니다.";
#else
					lpszMsg = "Fail to run GameGuard. Please reinstall the GameGuard setup file.";
#endif
					break;
				case NPGAMEMON_ERROR_ILLEGAL_PRG:
#ifdef _KOREA
					lpszMsg = "불법 프로그램이 발견되었습니다. 불필요한 프로그램을 종료한 후 다시 실행해보시기 바랍니다.";
#else
					lpszMsg = "Illegal program detected. Close all the unnecessary programs before running the game.";
#endif
					break;
				case NPGMUP_ERROR_ABORT:
#ifdef _KOREA
					lpszMsg = "게임가드 업데이트를 취소하셨습니다. 접속이 계속 되지 않을 경우 인터넷 및 개인 방화벽 설정을 조정해 보시기 바랍니다.";
#else
					lpszMsg = "GameGuard update has been aborted. Please check the status of Internet network or personal firewall settings when unable to connect continuously.";
#endif
					break;
				case NPGMUP_ERROR_CONNECT:
#ifdef _KOREA
					lpszMsg = "게임가드 업데이트 서버 접속에 실패하였습니다. 잠시 후 다시 접속하거나, 네트웍 상태를 점검해봅니다.";
#else
					lpszMsg = "Fail to connect the GameGuard update server. Please try again after a while, or check personal Firewall settings if any.";
#endif					
					break;
			/*case HOOK_TIMEOUT:
					lpszMsg = "바이러스나 스파이웨어로 인해 후킹이 실패하였습니다. 최신백신을 받으신 후 컴퓨터 전체검사를 해봅니다.";
					break;*/
				case NPGAMEMON_ERROR_GAMEGUARD:
#ifdef _KOREA
					lpszMsg = "게임가드 초기화 에러 또는 구버젼의 게임가드 파일입니다. 게임가드 셋업파일을 다시 설치하고 게임을 실행해봅니다.";
#else
					lpszMsg = "Game Guard Initialization fails or Previous Game Guard File exists. Please reinstall the Game Guard setup file and retry the game.";
#endif
					break;
#ifdef _TAIWAN
				case NPGMUP_ERROR_PARAM:
					//lpszMsg = "ini 파일이 없거나 변조되었습니다. 게임가드 셋업 파일을 설치하면 해결할 수 있습니다.";

					lpszMsg = "ini file does not exist or is corrupted. Please install the Game Guard setup file and retry the game.";
					break;
				case NPGMUP_ERROR_INIT:
					//lpszMsg = "npgmup.des 초기화 에러입니다. 게임가드폴더를 삭제후 다시 게임실행을 해봅니다.";

					lpszMsg = "npgmup.des initialization error. Please delete the Game Guard folder and retry the game.";
					break;
#endif
				case NPGMUP_ERROR_DOWNCFG:
#ifdef _KOREA
					lpszMsg = "게임가드 업데이트 서버 접속에 실패하였습니다. 잠시 후 재시도 해보거나, 개인 방화벽이 있다면 설정을 조정해 보시기 바랍니다.";
#else
					lpszMsg = "Fail to connect the GameGuard update server. Please try again after a while, or check personal Firewall settings if any.";
#endif
					break;
				case NPGMUP_ERROR_AUTH:
#ifdef _KOREA
					lpszMsg = "게임가드 업데이트를 완료하지 못 했습니다. 바이러스 백신을 일시 중시 시킨 후 재시도 해보시거나, PC 관리 프로그램을 사용하시면 설정을 조정해 보시기 바랍니다.";
#else
					lpszMsg = "“Fail to complete GameGuard update. Suspend Anti-Virus program temporarily and try the game, or check the settings of PC management programs if any.";
#endif
					break;
				case NPGAMEMON_ERROR_NPSCAN:
#ifdef _KOREA
					lpszMsg = "바이러스 및 해킹툴 검사 모듈 로딩에 실패 했습니다. 메모리 부족이거나 바이러스에 의한 감염일 수 있습니다.";
#else 
					lpszMsg = "“Failed to load virus and hacking tool scanning module. Possibly due to lack of memory or virus infection.";
#endif
					break;
#ifdef _TAIWAN
				case NPGG_ERROR_COLLISION:
					//lpszMsg = "게임가드와 충돌 프로그램이 발견되었습니다.";

					lpszMsg = "Collision program detected with Game Guard";
					break;
#endif
				default:
					// 적절한 종료 메시지 출력
#ifdef _KOREA
					lpszMsg = "게임가드 실행 중 에러가 발생하였습니다. 게임 폴더 안의 GameGuard 폴더에 있는 *.erl 파일들을 Game1@inca.co.kr로 첨부하여 메일 보내주시기 바랍니다.";
#else
					lpszMsg = "Error occurred while running GameGuard. Please send all *.erl files in GameGuard folder to Game2@inca.co.kr via email.";
#endif
					break;
				}
#ifdef _KOREA
				wsprintf(msg, "게임가드 에러 : %lu", dwResult);
#else
				wsprintf(msg, "GameGuard execute error : %lu", dwResult);
#endif
				MessageBox(NULL, lpszMsg, msg, MB_OK);

#ifdef _KOREA
				//// 게임에 맞게 종료 코드
				//dwQuitTimer = 1;
				//// 에러 코드를 넘겨주면 에러 발생시 자동으로 게임가드 FAQ 페이지를 띄워줌
				//pNpgl->RunFAQ(dwResult);
#endif

#ifdef _TAIWAN
				return FALSE;
#endif

			}

#endif // USE_GAME_GUARD_CLIENT


			//cltClient* pclclient = (cltClient*)pclClient;
			pclclient = (cltClient*)pclClient;
			if(pclclient)
			{
				if(pclClient->siServiceArea == ConstServiceArea_NHNChina)
				{
					pclclient->HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(pclclient->clSelectedWorldInfo.baseinfo.siServerID ,pclclient->m_szPorteAuth_UserID, HANREPORT_CLIENT_GAMESTART);
				}
				else
				{
					pclclient->HanAuth_Lib_HanReportSendPosLog_Client(pclclient->m_szHanAuth_UserID, HANREPORT_CLIENT_GAMESTART);

				}

			}

#ifndef _DEBUG
			// Serverinfo 폴더, 파일 삭제
			/*DeleteFile(TEXT("Serverinfo/Serverinfo.txt"));
			DeleteFile(TEXT("Serverinfo/Serverinfo.txt"));
			RemoveDirectory(TEXT("Serverinfo"));*/
#endif

			DeleteFile(TEXT("Config.ErrorLog.log"));
		}
		else 
		{
			ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);

			pclClient = NkNew cltMapEdit( NAME, hwnd, hInstance, GAMEMODE_MAPEDIT, defaultservicearea, runmode );
		}

	}

	if(pclClient)
	{
		// 비스타 인지 체크 해서 창 사이즈를 가로, 세로 3픽셀식 줄여준다. 
		// 여의치 않다면 서페이스를 늘려주는 방안을 검토해 볼참. [영진]

		OSVERSIONINFOEX osvi;
		//BOOL bOsVersionInfoEx;

		ZeroMemory( &osvi , sizeof(OSVERSIONINFOEX) );
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

		// 성공적으로 운영체제 정보를 읽어왔다면
		bool bOsVersinInfoGet = false;

		// Ex 함수로 못읽어 오면 걍 함수로 읽어온다
		if( GetVersionEx((OSVERSIONINFO*)&osvi) )
		{
			bOsVersinInfoGet = true;			
		}
		else
		{
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			if( GetVersionEx((OSVERSIONINFO*)&osvi) )
			{
				bOsVersinInfoGet = true;			
			}
			else
			{
				bOsVersinInfoGet = false;			
			}
		}

		// OS 정보를 성공적으로 읽어온 경우 비스타인지 판별한다
		if(bOsVersinInfoGet == true)
		{
			
			pclClient->dwPlatformId = osvi.dwPlatformId;
			pclClient->dwMajorVersion = osvi.dwMajorVersion;
			pclClient->dwMinorVersion = osvi.dwMinorVersion;
			pclClient->wProductType = osvi.wProductType;
		}

		pclClient->Create();
		pclClient->MainInit();
		if(gamemode == GAMEMODE_MAPEDIT)
		{
			_tcscpy(((cltMapEdit*)pclClient)->MapFileShortName, TEXT("MainMap.map"));
		}
	}
	else
	{
		MessageBox(NULL, TEXT("ds9f37jf"), TEXT("fd927jff"), MB_OK|MB_TOPMOST);
	}

// 윈도우 해상도 체크를 먼저한다.	
/*	
	//-------------------------------------
	// 윈도우 해상도 체크
	//-------------------------------------
	RECT rc;
	::GetWindowRect(GetDesktopWindow(), &rc);

	// KHY - 1218 - 1024x600 해상도 추가. imsi
	//if( (rc.right - rc.left < 1024) || (rc.bottom - rc.top < 768) )
	if( (rc.right - rc.left < 1024) || (rc.bottom - rc.top < 600) )
	{
		TCHAR* pTitle = GetTxtFromMgr(836);
		TCHAR* pText = GetTxtFromMgr(7103);

		MsgBox(pTitle, pText);
#ifdef USE_GAME_GUARD_CLIENT
		SAFE_DELETE(pNpgl);
#endif
		SAFE_DELETE(pclClient);
		
		// 프로그램 종료
		return FALSE;
	}
*/
	HACCEL haccel;      // handle to accelerator table 
	haccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR)); 

#ifdef USE_HANREPORT
	// 한게임 보고 모듈 코딩
	if(gamemode == 1)
	{
	}
	else if(gamemode == 2)
	{
		cltClient* pclclient = (cltClient*)pclClient;
		if(pclclient)
		{
			if(pclClient->siServiceArea == ConstServiceArea_NHNChina)
			{
				pclclient->HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(pclclient->clSelectedWorldInfo.baseinfo.siServerID ,pclclient->m_szPorteAuth_UserID, HANREPORT_CLIENT_INITCOMPLETE);
			}
			else
			{
				pclclient->HanAuth_Lib_HanReportSendPosLog_Client(pclclient->m_szHanAuth_UserID, HANREPORT_CLIENT_INITCOMPLETE);

			}
		}
	}
#endif //USE_HANREPORT

	//게임가드에 게임 클라이언트의 메인 윈도우 핸들 전달


#ifdef USE_GAME_GUARD_SERVER
	
	DWORD dwResult = InitGameguardAuth( "./nProtect/" , 50 , true ,  NPLOG_DEBUG | NPLOG_ERROR );

	if( dwResult != ERROR_SUCCESS )
	{		
		MessageBox( NULL, "Fail InitGameguardAuth", "nProtect", MB_OK );
		dwQuitTimer = 1;
	}

	SetUpdateCondition(30, 50);

	// 게임가드 타이머
	if(gamemode == 1)
	{
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->m_kUpdateTimer_GameGuard.Init(5 * 60 * 1000);	//5분 주기 권장
		pclserver->m_kUpdateTimer_GameGuard.SetActive(true, GetTickCount());
	}

	// 게임가드용 로그 폴더 생성
	CreateDirectory("GameGuardLog", NULL);

#endif


#ifdef USE_GAME_GUARD_CLIENT

	pNpgl->SetHwnd( pclClient->GetHwnd() );

#endif

	// Config 폴더 생성
	CreateDirectory("Config", NULL);

	int i;
	bool loop = true;
	while( loop )
    {

		for( i = 0; i < 10; ++i ) { 

			if (PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE))
			{
				if (!GetMessage( &msg, NULL, 0, 0))
				{ 
					return msg.wParam;
				}

				
				SI32 siTranslated = 0;
				// login 후에나 Translate 되도록 한다.
				if(pclClient && pclClient->GetFrame()>0 
				  && pclClient->GetGameStatus() == GS_GAME )
				{
					siTranslated = TranslateAccelerator(hwnd, haccel,&msg);
				}
				
				if(!siTranslated)
				{
					if(pclClient == NULL || pclClient->ModalessDlgProc(&msg) == FALSE )
					{
						TranslateMessage(&msg); 
						DispatchMessage(&msg);
					}
				}
				
			}
			else
			{
				if(gamemode == 1) Sleep(10);
			}
		}
		
		// 종료자가설정되어 있다면 종료한다. 
		if(dwQuitTimer)
		{
			bool bquitswitch = false;
			if(pclClient)
			{
				if((pclClient->CurrentClock - dwQuitTimer) > 2000)
				{
					dwQuitTimer = 0;

//					cltMsg clMsg(GAMEMSG_REQUEST_HOPETOQUIT, 0, NULL);
//					pclClient->SendMsgToServer((sPacketHeader*)&clMsg);

					bquitswitch = true;
				}

			}
			else
			{
				bquitswitch = true;
			}

			if(bquitswitch)
			{
				#ifdef USE_NELO
					#ifdef _CLIENT
						// -USE_NELO 윈도우를 디스트로이 하기 전에
						NELO_SendLog_TCP(hNELO,NELLO_LL_INFO,"TCPSENDLOG","NELOEND","NULL");
						NELO_SendLog_UDP(hNELO,NELLO_LL_INFO,"UDPSENDLOG","NELOEND","NULL");
						NELO_StopCrashHandler(hNELO);
						NELO_Destroy(hNELO);
					#endif _CLIENT
				#endif USE_NELO
				// -USE_NELO

				DestroyWindow(hwnd);
			}
		}


		if(pclClient)
		{
			pclClient->CurrentClock	= timeGetTime();
			
			// 네트워크 게임 메시지를 처리한다. 
			pclClient->NetworkOperation();

			pclClient->ClientWinMain();
		}

	}

	if ( g_hIMEDll )
	{
		FreeLibrary( g_hIMEDll );
		g_hIMEDll = NULL;
	}

	if ( g_hVersionIMEDll )
	{
		FreeLibrary( g_hVersionIMEDll );
		g_hVersionIMEDll = NULL;
	}

#ifdef USE_GAME_GUARD_CLIENT
	if(g_szHackMsg)
	{
		MessageBox ( NULL , g_szHackMsg , "nProtect GameGuard", MB_OK );
	}

	if( pNpgl )
	{
		SAFE_DELETE(pNpgl);
	}
#endif

#ifdef USE_GAME_GUARD_SERVER
	CleanupGameguardAuth();
#endif

	if(hMutex)
	{
		CloseHandle(hMutex);
		hMutex = NULL;
	}


	return msg.wParam;
}


bool GetDefaultServiceArea(SI32* pservicearea)//, SI32* psiAge /* = NULL */ )
{
	FILE* fp;
	TCHAR buffer[1024];
	TCHAR szservicearea[128];

	fp = _tfopen( TEXT("ServiceArea.txt"), TEXT("rt") );
	if(fp == NULL)
	{
		MsgBox( TEXT(" No <ServiceArea.txt> file"), TEXT("Error") );
		return false;
	}

	_fgetts(buffer, 1024, fp);
	_stscanf(buffer, TEXT("%s"), 	szservicearea);

	fclose(fp);

#ifdef _JAPAN
#ifndef _DEBUG

	fp = _tfopen( TEXT("NDE"), TEXT("r") );
	if(fp != NULL)
	{
		g_siChannelingCode = CHANNELINGCODE_NDEJP;

		fclose(fp);



	}

#endif
#endif


	*pservicearea = GetServiceAreaFromCode(szservicearea);

	//if( (*pservicearea != ConstServiceArea_Korea) )
	//{
		g_SoundOnOffDlg.m_bFullScreenMode = true;
		g_SoundOnOffDlg.m_bTmpFullScreenMode = true;

		if( g_bFullScreen )
		{
			g_SoundOnOffDlg.m_bMaxWindowMode = true;
			g_SoundOnOffDlg.m_bTmpMaxWindowMode = true;

			if( g_SoundOnOffDlg.m_bFullScreenMode == false )
			{
				g_SoundOnOffDlg.m_bFullScreenMode = true;
				g_SoundOnOffDlg.m_bTmpFullScreenMode = true;
			}
		}
		else
		{
			g_SoundOnOffDlg.m_bMaxWindowMode = false;
			g_SoundOnOffDlg.m_bTmpMaxWindowMode = false;
		}
	//}

	return true;
}

// 서비스 지역 코드를 근거로 서비스지역 정보를 얻는다. 
SI32 GetServiceAreaFromCode(TCHAR* sztext)
{
	if(_tcscmp(sztext, TEXT("SERVICEAREA_KOREA")) == 0)
	{
		return ConstServiceArea_Korea;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_CHINA")) == 0)
	{
		return ConstServiceArea_China;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_TAIWAN")) == 0)
	{
		return ConstServiceArea_Taiwan;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_JAPAN")) == 0)
	{
		return ConstServiceArea_Japan;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_ENGLISH")) == 0)
	{
		return ConstServiceArea_English;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_USA")) == 0)
	{
		return ConstServiceArea_USA ;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_NHNCHINA")) == 0)
	{
		return ConstServiceArea_NHNChina;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_EUROPE")) == 0)
	{
		return ConstServiceArea_EUROPE;
	}
	else 	if(_tcscmp(sztext, TEXT("SERVICEAREA_DEV")) == 0)
	{
		return ConstServiceArea_DEV;
	}
	
	else
	{
		MsgBox(TEXT("vc38fj"), TEXT("fd3:%s"), sztext);
	}

	return 0;
}

// 파일에서 GameMode를 얻어온다. 
bool GetGameModeInFile( SI32* pgamemode, SI32* pres, BOOL* bFullScreen, SI32* siContryCode, SI32* siRunMode )
{
	FILE* fp = NULL;
	TCHAR buffer[1024];

	SI32 gamemode = 0;
	SI32 resolution = 0;
	SI32 bfull = 0;
	SI32 contry = 0;
	SI32 runmode = 0;

	SI16 siSuccess = 0;

	NFile file; 

	file.LoadFile( TEXT("GameMode.dat") );

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{

		NLoadCryptFile( TEXT("GameMode.dat"),  (BYTE*)buffer );
		buffer[ pHeader->dwDataSize ] = NULL;


	} else {

		fp = _tfopen( TEXT("GameMode.dat"), TEXT("rt") );
		if(fp == NULL)
		{
			MsgBox(TEXT(" No <GameMode.dat> file"), TEXT("Error"));
			return false;
		}

		_fgetts(buffer, 1024, fp);
	}

	siSuccess = _stscanf( buffer, TEXT("%d %d %d %d %d"), 	&gamemode, &resolution, &bfull, &contry, &runmode );

	if( fp )fclose(fp);

	if(siSuccess == 4)
	{
		runmode = RUNMODE_REAL;
	}
	else if(siSuccess == 3)
	{
		contry = 0;
		runmode = RUNMODE_REAL;
	}
	else if(siSuccess == 2)
	{
		bfull = 0;
		contry = 0;
		runmode = RUNMODE_REAL;
	}
	else if(siSuccess == 1 )
	{
        resolution = 1;        
		bfull = 0;
		contry = 0;
		runmode = RUNMODE_REAL;
	}
	else if(siSuccess < 1 )
	{
		gamemode = GAMEMODE_CLIENT;	// Default GameMode!!
        resolution = 1;        
		bfull = 0;
		contry = 0;
		runmode = RUNMODE_REAL;
	}

	*pgamemode		= gamemode;
	*pres			= resolution;
	*bFullScreen	= bfull;
	*siContryCode	= contry;
	*siRunMode		= runmode;

	return true;
}

bool SetGameModeInFile(SI32 gamemode, SI32 res, BOOL bFullScreen, SI32 runmode )
{
	if(gamemode != GAMEMODE_CLIENT && gamemode != GAMEMODE_SERVER && gamemode != GAMEMODE_MAPEDIT)
		return false;
	if( res != 0 && res != 1 && res != 2)
		return false;

	char buffer[ 4096 ];

	/*
	FILE* fp;

	fp = _tfopen(TEXT("GameMode.txt"), TEXT("wt"));

	if( fp == NULL )
	{
		MsgBox(TEXT(" Fail to Create <GameMode.txt> file"), TEXT("Error"));
		return false;
	}
	
	if( bFullScreen == TRUE )
		_ftprintf( fp, TEXT("%d %d %d"), gamemode, res, 1 );
	else
		_ftprintf( fp, TEXT("%d %d %d"), gamemode, res, 0 );

	fclose( fp );
	*/

	buffer[ 0 ] = NULL;

	if( bFullScreen == TRUE )
		sprintf( buffer, TEXT("%d %d %d %d %d"), gamemode, res, 1, 0, runmode );
	else
		sprintf( buffer, TEXT("%d %d %d %d %d"), gamemode, res, 0, 0, runmode );

	
	int len = strlen( buffer );

	if( len > 0 ) NWriteCryptFile( TEXT("GameMode.dat"), (BYTE*)buffer, len );

	return true;
}


SI32 GetGameVersionInFile()
{
	FILE* fp = NULL;
	TCHAR buffer[1024];

	SI32 gameversion = 0;
	SI16 siSuccess = 0;

	NFile file; 

	if(file.LoadFile( TEXT("Version.dat") ) == false)
	{
		return gameversion;
	}

	NCryptHeader *pHeader = (NCryptHeader *)file.GetBuffer();
	if( pHeader->id[ 0 ] == 'N' &&
		pHeader->id[ 1 ] == 'C' &&
		pHeader->id[ 2 ] == 'R' ) 
	{

		NLoadCryptFile( TEXT("Version.dat"),  (BYTE*)buffer );
		buffer[ pHeader->dwDataSize ] = NULL;


	} else {

		fp = _tfopen( TEXT("Version.dat"), TEXT("rt") );
		if(fp == NULL)
		{
			MsgBox(TEXT(" No <Version.dat> file"), TEXT("Error"));
			return false;
		}

		_fgetts(buffer, 1024, fp);
	}

	siSuccess = _stscanf(buffer, TEXT("%d"), &gameversion );
	if( fp )fclose(fp);

	if(siSuccess == 1)
	{
		
	}
	else
	{
		gameversion = 0;
	}

	return gameversion;
}

bool SetGameVersionInFile(SI32 siVersion)
{
	if(siVersion <= 0)
		return false;

	char buffer[ 4096 ];
	buffer[ 0 ] = NULL;

	sprintf( buffer, TEXT("%d"), siVersion );
	int len = strlen( buffer );

	if( len > 0 ) NWriteCryptFile( TEXT("Version.dat"), (BYTE*)buffer, len );

	return true;
}

// 파일에서 FullScreen 여부를 얻어온다. 
bool GetFullScreenInFile( BOOL* bFullScreen )
{
	FILE* fp;
	TCHAR buffer[1024];

	//*bFullScreen = 0;	// 창모드를 디폴트로
	SI32 bfull = 0;

	SI16 siSuccess = 0;

	fp = _tfopen(TEXT("FullScreen.txt"), TEXT("rt"));
	if(fp == NULL)
	{
#if defined(_DEBUG)
//		MsgBox(TEXT(" No <FullScreen.txt> file"), TEXT("Error"));
#endif
		return false;
	}

	_fgetts(buffer, 1024, fp);

	siSuccess = _stscanf(buffer, TEXT("%d"), 	&bfull );

	fclose(fp);

	if(siSuccess != 1 )
	{
		bfull = 0;
	}

	*bFullScreen	= bfull;

	return true;
}

bool SetFullScreenInFile( BOOL bFullScreen )
{
	if( bFullScreen < 0 )
		return false;

	FILE* fp;

	fp = _tfopen(TEXT("FullScreen.txt"), TEXT("wt"));

	if( fp == NULL )
	{
#if defined(_DEBUG)
//		MsgBox(TEXT(" Fail to Create <FullScreen.txt> file"), TEXT("Error"));
#endif
		return false;
	}
	
	if( bFullScreen == TRUE )
		_ftprintf( fp, TEXT("%d"), 1 );
	else
		_ftprintf( fp, TEXT("%d"), 0 );

	fclose( fp );

	return true;
}

void GetServerNameFromServerUnique(SI32 ServerUnique, TCHAR* szServername)
{

#ifndef _ENGLISH
	switch(ServerUnique)
	{
	case 0:  sprintf(szServername,"%s","테스트"); break;
	case 1:  sprintf(szServername,"%s","jpn1"); break;
	case 2:  sprintf(szServername,"%s","jpn2"); break;
	default: 
		{
			sprintf(szServername,"%s","없음");
			MsgBox("fhjskhfjd", "servername:%s", szServername);			
			break;
		}		
	}	
#else
	switch(ServerUnique)
	{
	case 0:  sprintf(szServername,"%s","테스트"); break;
	case 1:  sprintf(szServername,"%s","global"); break;
	default: 
			 {
				 sprintf(szServername,"%s","없음"); break;
				 //MsgBox("fhjskhfjd", "servername:%s", szServername);			
			 }		
	}	
#endif

}
