#ifndef _AGENTPROCESS_H
#define _AGENTPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#define AGENT_HEARTBEAT_INTERVAL		3000		// ����������Ʈ�� ������ ��Ʈ��Ʈ �ֱ� (3��)

class cAgent : public ITZPerson
{
public:
	cAgent() {};
	~cAgent() {};

	virtual void Init() {};
	virtual void Close() {};
};


class AgentProcess
{
public:
	AgentProcess();
	~AgentProcess();

	void				Init( TCHAR *szIP, UI16 usPort );
	void				Run();

	ITZSession*			GetAgentSession() { return m_pAgentSession; };

	BOOL				IsInitReady() { return m_bInitReady; };

private:
	ITZSessionFactory< cAgent >		m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pAgentSession;				// ����������Ʈ ���� ������

	TCHAR							m_szIP[ 16 ];
	UI16							m_usPort;

	DWORD							m_dwLastTick;

	BOOL							m_bSendFilePath;

	BOOL							m_bInitReady;

};

#endif

