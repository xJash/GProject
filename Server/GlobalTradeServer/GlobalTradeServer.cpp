// GlobalTradeServer.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "GlobalTradeServer.h"
#include "GlobalTradeServerDlg.h"

#include "../BeTheRich/Server/NTradeServerProcess/TradeServerMsg.h"

#include "GameProtocol.h"
#include "DBProtocol.h"
#include "DBProcess.h"
#include "DBLogProtocol.h"

GameProtocol	g_GameProtocol;
DBProtocol		g_DBProtocol;
DBProcess		g_DBProcess;

DBLogProtocol	g_LogProtocol;

char		g_dbip[ 128 ];
char		g_dbname[ 128 ];
char		g_dbid[ 128 ];
char		g_dbpw[ 128 ];
unsigned short		g_listenport;
unsigned short		g_loglistenport;

int			g_maxclient;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGlobalTradeServerApp

BEGIN_MESSAGE_MAP(CGlobalTradeServerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGlobalTradeServerApp ����

CGlobalTradeServerApp::CGlobalTradeServerApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CGlobalTradeServerApp ��ü�Դϴ�.

CGlobalTradeServerApp theApp;


// CGlobalTradeServerApp �ʱ�ȭ

BOOL CGlobalTradeServerApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	// SJY
	FILE* fp;
	char buffer[1024] = "" ;
	char ip[20] = "" ;

	//fp = fopen("ServerIP.txt", "rt");
	fp = fopen("ServerInfo.txt", "rt");
	if(fp == NULL)
	{
		MessageBox(NULL," No <ServerIP.txt> file", "Error",MB_OK);
		return FALSE;
	}

	char szName[128];
	char szValue[128];

	while( fgets(buffer, 1024, fp) != NULL )
	{
		sscanf( buffer, "%s %s", szName, szValue );

		if		( strcmp( szName, "TradeServerIP") == 0 )		{	strncpy(ip, szValue, sizeof(ip));				}
		else if	( strcmp( szName, "ClientListenPort") == 0 )	{	g_listenport = atoi(szValue);					}
		else if	( strcmp( szName, "DatabaseName") == 0 )		{	strncpy(g_dbname, szValue, sizeof(g_dbname));	}
		else if	( strcmp( szName, "DatabaseIP") == 0 )			{	strncpy(g_dbip, szValue, sizeof(g_dbip));		}
		else if	( strcmp( szName, "DatabaseLoginID") == 0 )		{	strncpy(g_dbid, szValue, sizeof(g_dbid));		}
		else if	( strcmp( szName, "DatabaseLoginPW") == 0 )		{	strncpy(g_dbpw, szValue, sizeof(g_dbpw));		}
		else if	( strcmp( szName, "LogClientListenPort") == 0 )	{	g_loglistenport = atoi(szValue);				}
	}

//	fgets(buffer, 1024, fp);
//	sscanf(buffer, "%s",ip);
	fclose(fp);

	g_GameProtocol.Init();
	g_GameProtocol.CreateThread();
	g_GameProtocol.GetListen()->Start();

	g_LogProtocol.Init( g_loglistenport, g_dbip, g_dbname, g_dbid, g_dbpw );
	g_LogProtocol.CreateThread();
	g_LogProtocol.GetListen()->Start();

//#ifdef _DEBUG
	//g_DBProcess.Init( "116.127.222.221", 20002 );
//#else
	g_DBProcess.Init(ip, 20012);
//#endif
	g_DBProcess.Run();

//	strcpy(g_dbname, "TradeServer");
//	strcpy(g_dbid, "TradeServerClient");
//	strcpy(g_dbpw, "emfla");

	g_DBProtocol.Init( 20012 , g_dbip, g_dbname, g_dbid, g_dbpw );
	g_DBProtocol.CreateThread();
	g_DBProtocol.GetListen()->Start();

	CGlobalTradeServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� Ȯ���� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ ��ȭ ���ڰ� ��Ҹ� ���� �������� ��� ó����
		// �ڵ带 ��ġ�մϴ�.
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�
	// ���� ���α׷��� ���� �� �ֵ��� FALSE�� ��ȯ�մϴ�.
	return FALSE;
}

void cHeartBeatSystem::Init()
{
	m_siState =	HEARTBEATSYSTEM_STATE_NONE;
}

bool cHeartBeatSystem::Send_HeartBeat( ITZSession* pSession )
{
	if( pSession == NULL )									return false;
	if( pSession->GetState() != SESSION_STATE_ESTABLISHED )	return false;

	switch( m_siState )
	{
	case HEARTBEATSYSTEM_STATE_NONE:
	case HEARTBEATSYSTEM_STATE_HEARTBEAT_RECEIVED:		{					}		break;

	// ������ ��û�� ��Ʈ��Ʈ�� ���� ����� ���� ���ϸ�, ��û���� �ʴ´�.
	case HEARTBEATSYSTEM_STATE_HEARTBEAT_SEND:			{	return false;	}		break;
	}

	NTradeServerResponse_HeartBeat clHeartBeat;
	pSession->GetSendBuffer()->Write((char*)&clHeartBeat);

	// ��Ʈ��Ʈ�� ��û�� ������ üũ
	m_siState = HEARTBEATSYSTEM_STATE_HEARTBEAT_SEND;

	return true;
}

bool cHeartBeatSystem::Receive_HeartBeat( ITZSession* pSession )
{
	if( pSession == NULL )									return false;
	if( pSession->GetState() != SESSION_STATE_ESTABLISHED )	return false;

	// ������ ��Ʈ��Ʈ�� ��û�� ����� ���ٸ�, ��û ���
	if( m_siState != HEARTBEATSYSTEM_STATE_HEARTBEAT_SEND )		return false;

	// ����� ���� ������ üũ
	m_siState = HEARTBEATSYSTEM_STATE_HEARTBEAT_RECEIVED;

	return true;
}

bool cGame::Request_HeartBeat()
{
	if( m_pHeartBeatSystem == NULL )			return false;
	
	if( m_dwHeartBeatClock == 0 )
	{
		// �ʱ� �ð� ����
		m_dwHeartBeatClock = GetTickCount();
		return true;
	}

	if( GetSession() && GetSession()->GetState() == SESSION_STATE_ESTABLISHED )
	{
		if( GetTickCount() - m_dwHeartBeatClock >= 30 * 1000 )		// 30�ʸ��� �ѹ��� ��û�Ѵ�.
		{
			m_dwHeartBeatClock = GetTickCount();
			if( m_pHeartBeatSystem->Send_HeartBeat( GetSession() ) == false )
			{
				// ��Ʈ��Ʈ�� ����� ������ ���ϸ�, ������ ���´�.
				GetSession()->CloseSocket();
				return false;
			}
		}
	}
	return true;
}

bool cGame::Received_HeartBeat()
{
	if( m_pHeartBeatSystem == NULL )			return false;

	if( GetSession() && GetSession()->GetState() == SESSION_STATE_ESTABLISHED )
	{
		if( m_pHeartBeatSystem->Receive_HeartBeat( GetSession() ) == false )
		{
			// ��Ʈ��Ʈ�� ����� ���� ���ϸ�, ������ ���´�.
			GetSession()->CloseSocket();
			return false;
		}
	}
	return true;
}
