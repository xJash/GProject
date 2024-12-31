#ifndef _ACCOUNTDBPROCESS_H
#define _ACCOUNTDBPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#include "AuthServer.h"

#define DBCONNECTION_NUMBER		10

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
	void			Init( char *szAccountDBManagerIP, UI16 usPort, char *szAccountDBIP );
	void			Run();

	void			SendMsg( sPacketHeader *pPacket );

	SI32			m_siWorkSlot;

	CRITICAL_SECTION	m_cs;

	char							m_accountDBIP[ 20 ];

private:
	ITZSessionFactory< cAccountDB >	m_sf;										// ���� ���丮
	ITZSessionManager				m_sm;										// ���� �Ŵ���
	ITZNetIOCP						m_iocp;										// IOCP 

	ITZSession*						m_pAccountDBSession[ DBCONNECTION_NUMBER ];	// ���� DB�Ŵ��� ���� ������

	char							m_accountDBManagerIP[ 20 ];					// ���� DB�Ŵ��� IP
	UI16							m_accountDBManagerPort;						// ���� DB�Ŵ��� PORT

};

#endif