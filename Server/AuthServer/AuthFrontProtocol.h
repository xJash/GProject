#ifndef _AUTHFRONTPROTOCOL_H
#define _AUTHFRONTPROTOCOL_H

#include "AuthServer.h"
#include "ITZNetworkThread.h"
//KHY - 0218 - �߱� NHN �Ƿε� ��� ����
#ifdef USE_HANANTITOXIC
	#define MAX_SID_BUF 64
#endif

class AuthFrontProtocol : public ITZNetworkThread
{
public:
	AuthFrontProtocol();
	~AuthFrontProtocol();

public:
	void			Init(UI16 usFrontServerListenPort);

	virtual void	Update();
	virtual void	LogOut( ITZSession *pSession );
	virtual void	SessionProc( ITZSession *pSession );

public:
	ITZSessionFactory< cFront >	m_SF;
};


//---------------------------------------------------------
//KHY - 0617 - �Ϻ� ä�θ� �߰�. - �����Ͼƿ� ���� �Լ�.
/*int HttpsPostAuth(TCHAR *pszID, TCHAR *pszPW);	// For �����Ͼ�

int SoapAuth(TCHAR *pszID, TCHAR *pszPW ,  TCHAR *puserIP);	// For GamePot
int GamePotAuth(char* pszID, char* pszPW, char* pszIP);*/

void DeltPublisherID(TCHAR * Input_userid ,TCHAR * Output_userid);

bool SSNCreate(SI08 siAge, SI08 siSex, TCHAR* pszRet, UI32 uiRetSize);		// �ֹε�� �����Լ�

// �Ϻ� �ؽ� �� �Ľ��Լ�.
void NexonjpIDDataDivision(sRequest_NEXONJP_FrontAuth *FfrontAuth , sDBRequest_IDNumGet *FsendMsg);

#endif
