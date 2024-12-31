#ifndef _ACCOUNTDBPROCESS_H
#define _ACCOUNTDBPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#include "MasterServer.h"

class cAccountDB : public ITZPerson
{
public:
	cAccountDB() {};
	~cAccountDB() {};
};

class AccountDBProcess
{
public:
	AccountDBProcess();
	~AccountDBProcess();

public:
	void			Init( char *ip, UI16 usPort );
	void			Run();

	ITZSession*		GetSession() { return m_pAccountDBSession; };

private:
	ITZSessionFactory< cAccountDB >	m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pAccountDBSession;			// ���� DB�Ŵ��� ���� ������

	char							m_accountDBManagerIP[ 20 ];		// ���� DB�Ŵ��� IP
	UI16							m_accountDBManagerPort;			// ���� DB�Ŵ��� PORT

};

#endif