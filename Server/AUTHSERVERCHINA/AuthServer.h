#ifndef _AUTHSERVER_H
#define _AUTHSERVER_H

#include "GleeService.h"
#include "AuthMsg.h"
#include "ITZPerson.h"

#include "../../DBManager/AccountDBManager/AccountDBMsg.h"

#define MAX_SBSLOGIN_NUMBER				9

class AuthUserList;
class AccountDBProcess;
class AuthGameProtocol;
class AuthFrontProtocol;
class AgentProcess;
class CGash;
class CUserManager;

//extern AuthUserList			g_authUserList;
extern AccountDBProcess		g_accountDB;
extern AuthGameProtocol		g_agp;
extern AuthFrontProtocol	g_afp;
extern AgentProcess			g_agent;
extern CGash				g_gash;
extern GameActivService::CGameActivService	g_GameActivServiceT;

extern BOOL					g_bInitReady;						// �ʱ�ȭ �غ� �� 
extern BOOL					g_bInitComplete;					// �ʱ�ȭ �Ϸ� �� 

extern SI32					g_siServerID;

extern CUserManager			g_usermanager;

class cFront : public ITZPerson
{
public:
	cFront() {};
	~cFront() {};

public:
	virtual void Init() { printf( "Front Server Connected\n" ); };
	virtual void Close() { printf( "Front Server Disconnected\n" ); };

};


class cGame : public ITZPerson
{
public:
	cGame() {};
	~cGame() {};

public:
	virtual void Init() { printf( "Game Server Connected\n" ); };
	virtual void Close() { printf( "Game Server Disconnected\n" ); };
};


class cUserInfo : public ITZObject
{
public:
	cUserInfo() {};
	~cUserInfo() {};

public:
	char			userid[ 20 ];
	char			userpw[ 20 ];

	SI32			idnum;
	UI16			usAuthKey;					// Auth�������� user����Ʈ������ �ε��� 
	SI16			siGameMasterLevel;			// ��� ���

	DWORD			dwLastTick;					// �ֱ� ��� �ð�
	
};

#endif

