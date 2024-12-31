#ifndef _FRONTAUTHPROCESS_H
#define _FRONTAUTHPROCESS_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#include "../../Server/FrontServer/FrontMsg.h"


#define FRONT_HEARTBEAT_INTERVAL	3000							// ����Ʈ ������ ������ ��Ʈ��Ʈ �ֱ� (3��)
#define AUTH_HEARTBEAT_INTERVAL		5000							// ���� ������ ������ ��Ʈ��Ʈ �ֱ� (5��)

class cFrontAuth : public ITZPerson
{
public:
	cFrontAuth() {};
	~cFrontAuth() {};
};


class FrontAuthProcess
{
public:
	FrontAuthProcess();
	~FrontAuthProcess();

	void				Init( TCHAR *frontIP, UI16 frontPort, TCHAR *authIP, UI16 authPort );
	void				Run();

	ITZSession*			GetFrontSession() { return m_pFrontSession; };
	ITZSession*			GetAuthSession() { return m_pAuthSession; };

private:
	ITZSessionFactory< cFrontAuth >	m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pFrontSession;				// ����Ʈ ���� ���� ������
	ITZSession*						m_pAuthSession;					// ���� ���� ���� ������

	TCHAR							m_frontIP[ 20 ];				// ����Ʈ ���� IP
	UI16							m_frontPort;					// ����Ʈ ���� PORT

	TCHAR							m_authIP[ 20 ];					// ���� ���� IP
	UI16							m_authPort;						// ���� ���� PORT

	DWORD							m_frontLastTick;
	DWORD							m_authLastTick;

public:
	GAMESERVER_REFRESHINFO			m_refreshInfo;

public:
	bool SendMsg(sPacketHeader* pPacket);
};



#endif