#ifndef _TOOLSLOG_H
#define _TOOLSLOG_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#include "itzbase.h"

class CToolsLog : public ITZPerson
{
public:
	CToolsLog() {};
	~CToolsLog() {};

public:
	virtual void Init() {};
	virtual void Close() {};
};

class CToolsLogProcess
{
public:
	CToolsLogProcess();
	~CToolsLogProcess();

	void				Init( char *szIP, UI16 usPort );
	void				Run();

	ITZSession*			GetToolsLogSession() { return m_pToolsLogSession; };

	void				SendMsg( sPacketHeader *pPacket );

private:
	ITZSessionFactory< CToolsLog >	m_sf;									// ���� ���丮
	ITZSessionManager				m_sm;									// ���� �Ŵ���
	ITZNetIOCP						m_iocp;									// IOCP 

	ITZSession*						m_pToolsLogSession;						// ����������Ʈ ���� ������

	char							m_szIP[ 16 ];
	UI16							m_usPort;

};

#endif 
