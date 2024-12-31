#ifndef _LOGDBPROCESS_H
#define _LOGDBPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

class cLogDB : public ITZPerson
{
public:
	cLogDB() {};
	~cLogDB() {};
};


class LogDBProcess
{
private:

public:
	LogDBProcess();
	~LogDBProcess();

public:
	void			Init( TCHAR *ip, UI16 usPort );
	void			Run();

	bool			SendMsg(sPacketHeader *pPacket);

	ITZSession*		GetSession() { return m_pGameDBSession; };

private:
	ITZSessionFactory< cLogDB >		m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pGameDBSession;				// ���� DB�Ŵ��� ���� ������

	TCHAR							m_gameDBManagerIP[ 20 ];		// ���� DB�Ŵ��� IP
	UI16							m_gameDBManagerPort;			// ���� DB�Ŵ��� PORT

};

#endif