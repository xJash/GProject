#ifndef _GAMEDBPROCESS_H
#define _GAMEDBPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

class cGameDB : public ITZPerson
{
public:
	cGameDB() {};
	~cGameDB() {};

	virtual void Init() { printf( "GameDB Manager�� ���� ����\n" ); }
	virtual void Close() { printf( "GameDB Manager�� ���� ����\n" ); }
};


class GameDBProcess
{
public:
	GameDBProcess();
	~GameDBProcess();

public:
	void			Init( char *ip, UI16 usPort );
	void			Run();

	ITZSession*		GetSession() { return m_pGameDBSession; };

private:
	ITZSessionFactory< cGameDB >	m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pGameDBSession;				// ���� DB�Ŵ��� ���� ������

	char							m_gameDBManagerIP[ 20 ];		// ���� DB�Ŵ��� IP
	UI16							m_gameDBManagerPort;			// ���� DB�Ŵ��� PORT

};

#endif