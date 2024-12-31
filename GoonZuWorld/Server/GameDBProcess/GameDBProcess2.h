#ifndef _GAMEDBPROCESS2_H
#define _GAMEDBPROCESS2_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

class cGameDB2 : public ITZPerson
{
public:
	cGameDB2() {};
	~cGameDB2() {};
};


class GameDBProcess2
{
private:

public:
	GameDBProcess2();
	~GameDBProcess2();

public:
	void			Init( TCHAR *ip, UI16 usPort );
	void			Run();

	bool			SendMsg(sPacketHeader *pPacket);

	ITZSession*		GetSession() { return m_pGameDBSession; };

private:
	ITZSessionFactory< cGameDB2 >	m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pGameDBSession;				// ���� DB�Ŵ��� ���� ������

	TCHAR							m_gameDBManagerIP[ 20 ];		// ���� DB�Ŵ��� IP
	UI16							m_gameDBManagerPort;			// ���� DB�Ŵ��� PORT

};

#endif