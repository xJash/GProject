#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "AccountDB.h"
#include "DBAuthProtocol.h"
#include "DBMasterProtocol.h"
#include "AgentProcess.h"

#include "../../NLib/NUtil.h"

#define DBCONNECTION_NUMBER		10

void dispInitView();


DBAuthProtocol		g_dap[ DBCONNECTION_NUMBER ];
DBMasterProtocol	g_dmp;

AgentProcess			g_agent;

BOOL					g_bInitReady;						// 초기화 준비가 됨 
BOOL					g_bInitComplete;					// 초기화 완료 됨 

SI32					g_siServerID;


char					g_dbname[ 128 ];
char					g_dbid[ 128 ];
char					g_dbpw[ 128 ];

//char					g_DBGW_ADDR[ 256 ];

unsigned int			g_uiTimeTick;
SYSTEMTIME				g_stLastTime;

char					g_szServiceArea[12];
char					g_szServiceMode[8];



/*void GetHanGameInfo()
{
	FILE* fp;
	TCHAR buffer[1024];
	TCHAR* pfilename = TEXT("HanGameInfo.txt");
	fp = _tfopen(pfilename, TEXT("rt"));
	if(fp == NULL)							return;

	TCHAR key[256], value[256];

	while(_fgetts(buffer, 1024, fp) != NULL)
	{
		_stscanf(buffer, TEXT("%s %s"), key, value);

		if(		strcmp(key, "ServiceType") == 0)	{												}
		else if(strcmp(key, "ServiceAge") == 0)		{												}
		else if(strcmp(key, "DBGW_Address") == 0)	{		strcpy(g_DBGW_ADDR, value);				}
	}

	fclose(fp);
}*/

void InitServer( char *szDBIP, char *szDatabase, char *szUserID, char *szUserPW )
{

	strcpy( g_dbname, szDatabase );
	strcpy( g_dbid, szUserID );
	strcpy( g_dbpw, szUserPW );

	int i;

//#ifdef USE_DBGW
//	printf( "- DBGW Connecting (ADDR:%s)\n", g_DBGW_ADDR);
//#else
	printf( "- Database Connecting (IP:%s)\n", szDBIP );
//#endif

	for( i = 0; i < DBCONNECTION_NUMBER; ++i ) {
		g_dap[ i ].Init( 10001 + i, szDBIP, szDatabase, szUserID, szUserPW );
		g_dap[ i ].CreateThread();
	}

	g_dmp.Init( 9100, szDBIP, szDatabase, szUserID, szUserPW );
	g_dmp.CreateThread();

	printf( "Init Completed\n" );
}


void main()
{
	int i;

	g_bInitReady = FALSE;
	g_bInitComplete = FALSE;

//	GetHanGameInfo();

	dispInitView();
	
	g_agent.Init( "127.0.0.1", 6400 );

	BOOL bRun = TRUE;

	g_uiTimeTick = GetTickCount();

	// 초기 시간 설정
	GetLocalTime(&g_stLastTime);

	// console
	while( bRun ) {

		Sleep( 10 );

		g_agent.Run();

		// 초기화가 준비 되었으면, 리슨 포트를 열고 초기화를 완료한다 
		if( g_bInitReady == TRUE && g_bInitComplete == FALSE ) {

			for( i = 0; i < DBCONNECTION_NUMBER; ++i ) {
				g_dap[ i ].GetListen()->Start();
			}
			g_dmp.GetListen()->Start();	

			g_bInitComplete = TRUE;
		}


		if( g_bInitComplete == TRUE ) {

			bool		bDayChange = false;

			bool		bExecute = false;
			if( strcmp(g_szServiceArea, "KOREA") == 0 )		bExecute = true;
				
			if( bExecute && GetTickCount() - g_uiTimeTick >= 1000 )
			{
				SYSTEMTIME	stTime;		GetLocalTime(&stTime);
				if( g_stLastTime.wDay != stTime.wDay )	{	bDayChange = true;	}

				memcpy(&g_stLastTime, &stTime, sizeof(g_stLastTime));

				// 날짜가 바뀌었으면...
				if( stTime.wHour == 0 &&
					stTime.wMinute == 0 &&
					stTime.wSecond >= 0 &&
					stTime.wSecond <= 10 &&
					bDayChange)
				{
					// 하루 전날의 통계를 요청한다.
					SYSTEMTIME sStatisticsTime;
					TimeSubDate(&stTime, 1, &sStatisticsTime);

					// 1. 동접보고
					g_dap[0].Statistics_UserCount(sStatisticsTime);

					// 2. 이용자 지수
					g_dap[0].Statistics_UserInfo(sStatisticsTime);

					// 3. 전체 이용자 레벨별 분포

					// 4. 주간 이용자 레벨별 분포
					g_dap[0].Statistics_WeekUserLevel(sStatisticsTime);

					// 5. 신규고객 레벨별 분포
					g_dap[0].Statistics_NewUserLevel(sStatisticsTime);

					// 6. 액티브이용자 레벨별 분포
					g_dap[0].Statistics_ActiveUserLevel(sStatisticsTime);

					// 7. 전체 이용자 성별 및 연령 구분
					g_dap[0].Statistics_TotalUserAgeGender(sStatisticsTime);

					// 8. 주간 이용자 성별 및 연령 구분
					g_dap[0].Statistics_WeekUserAgeGender(sStatisticsTime);

					// 9. 신규 고객 성별 및 연령 구분
					g_dap[0].Statistics_NewUserAgeGender(sStatisticsTime);

					// 10. 액티브 이용자 성별 및 연령 구분
					g_dap[0].Statistics_ActiveUserAgeGender(sStatisticsTime);
				}
			}
		}

		if( kbhit() ) {

			switch( getch() )
			{
			case 27:
					bRun = FALSE;
				break;

			}

		}

	}

}

void dispInitView()
{
	printf( "-------------------------------------------------------------------------------\n" );
	printf( "AccountDBManager\n" );
	printf( "-------------------------------------------------------------------------------\n" );

	printf( "- Trying to Connect to ServerAgent..\n" );
}
