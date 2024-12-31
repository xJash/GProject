#ifndef _AGENTPROCESS_H
#define _AGENTPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#define AGENT_HEARTBEAT_INTERVAL		5000		// ����������Ʈ�� ������ ��Ʈ��Ʈ �ֱ� (5��)

class cAgent : public ITZPerson
{
public:
	cAgent() {};
	~cAgent() {};

	virtual void Init() { printf( "ServerAgent Connected\n" ); };
	virtual void Close() { printf( "ServerAgent Disconnected\n" ); };
};


class AgentProcess
{
public:
	AgentProcess();
	~AgentProcess();

	void				Init( char *szIP, UI16 usPort );
	void				Run();

	ITZSession*			GetAgentSession() { return m_pAgentSession; };

public:
	ITZSessionFactory< cAgent >		m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pAgentSession;				// ����������Ʈ ���� ������

	char							m_szIP[ 16 ];
	UI16							m_usPort;

	DWORD							m_dwLastTick;

	BOOL							m_bSendFilePath;

};

#endif

