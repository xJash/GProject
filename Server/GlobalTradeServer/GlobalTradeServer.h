// GlobalTradeServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ
#include "ITZPerson.h"


// CGlobalTradeServerApp:
// �� Ŭ������ ������ ���ؼ��� GlobalTradeServer.cpp�� �����Ͻʽÿ�.
//

class CGlobalTradeServerApp : public CWinApp
{
public:
	CGlobalTradeServerApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CGlobalTradeServerApp theApp;

enum HEARTBEATSYSTEM_STATE
{
	HEARTBEATSYSTEM_STATE_NONE,
	HEARTBEATSYSTEM_STATE_HEARTBEAT_SEND,
	HEARTBEATSYSTEM_STATE_HEARTBEAT_RECEIVED,
};

class cHeartBeatSystem
{
public:
	cHeartBeatSystem()
	{
		Init();
	}

	void Init();
	bool Send_HeartBeat( ITZSession* pSession );
	bool Receive_HeartBeat( ITZSession* pSession );

protected:
	SI16			m_siState;
};

// �������� ���� ����
// 100 : 1.00 -> ó�� ���� ����
// 200 : 2.00 -> �������� - 1. ��Ʈ��Ʈ ���, 2. SellInfo�� ���Ӽ����� ��û
class cGame : public ITZPerson
{
public:
	cGame()		{	m_pHeartBeatSystem = new cHeartBeatSystem;	m_dwHeartBeatClock = 0;						}
	~cGame()	{	if(m_pHeartBeatSystem)	delete m_pHeartBeatSystem;		m_pHeartBeatSystem = NULL;		}

public:
	virtual void Init() {	m_siVersion = 100;	m_dwHeartBeatClock = 0;	OutputDebugString("cGame::Init()\n");		}
	virtual void Close() {	OutputDebugString("cGame::Close()\n");	};

	bool Request_HeartBeat();
	bool Received_HeartBeat();

	SI32 m_siVersion;		// �������� ���� ����

protected:
	cHeartBeatSystem*	m_pHeartBeatSystem;
	DWORD				m_dwHeartBeatClock;
};

class cDB : public ITZPerson
{
public:
	cDB() {};
	~cDB() {};

public:
	virtual void Init() {};
	virtual void Close() {};
};

