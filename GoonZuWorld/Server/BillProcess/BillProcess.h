#ifndef _BillProcess_H
#define _BillProcess_H

#include "ITZSessionFactory.h"
#include "ITZSessionManager.h"
#include "ITZNetIOCP.h"
#include "ITZPerson.h"

#include "../../Server/FrontServer/FrontMsg.h"


#define BILL_HEARTBEAT_INTERVAL	5000							// �� ������ ������ ��Ʈ��Ʈ �ֱ� (3��)


class cBill : public ITZPerson
{
public:
	cBill() {};
	~cBill() {};
};


class BillProcess
{
public:
	BillProcess();
	~BillProcess();

	void				Init( TCHAR *billIP, UI16 billPort);
	void				Run();

	ITZSession*			GetBillSession() { return m_pBillSession; };

private:
	ITZSessionFactory< cBill >	m_sf;							// ���� ���丮
	ITZSessionManager				m_sm;							// ���� �Ŵ���
	ITZNetIOCP						m_iocp;							// IOCP 

	ITZSession*						m_pBillSession;				// �� ���� ���� ������


	TCHAR							m_BillIP[ 20 ];				// ����Ʈ ���� IP
	UI16							m_BillPort;					// ����Ʈ ���� PORT

	DWORD							m_BillLastTick;

public:
	GAMESERVER_REFRESHINFO			m_refreshInfo;

public:
	bool SendMsg(sPacketHeader* pPacket);
};



#endif