#ifndef _MASTERCLIENTPROTOCOL_H
#define _MASTERCLIENTPROTOCOL_H

#include "ITZNetworkThread.h"
#include "MasterServer.h"

const SI32 ConstMAXMasterClientCount = 50;

class MasterClientProtocol : public ITZNetworkThread
{
public:
	MasterClientProtocol();
	~MasterClientProtocol();

public:
	void			Init();

	virtual void	Update();
	virtual void	SessionProc( ITZSession *pSession );
	
	ITZSessionFactory< cClient >	m_SF;

	ITZSession*						m_MasterClientSession[ ConstMAXMasterClientCount ];

protected:
	// ���� ���� ������ ���� �ð�
	SI32			m_siRefreshInfoLastSendTick;
	BOOL			m_bRefreshInfoSendState;
};




#endif

