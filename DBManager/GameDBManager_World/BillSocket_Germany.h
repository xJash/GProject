#ifndef __BILLSOCKET_H__
#define __BILLSOCKET_H__

#define		MAX_PACKETSIZE				1024	//	��Ŷ �ִ�ũ��	
#define		LIMIT_RECEIVETIME			10000	//	��Ŷ������ �ִ� �ִ� �ð� 10��

#include "itzbase.h"

/********************************************************************
	created:	2009/04/30
	created:	30:4:2009   14:03
	filename: 	d:\GProject\DBManager\GameDBManager_World\BillSocket_Germany.h
	file path:	d:\GProject\DBManager\GameDBManager_World
	file base:	BillSocket_Germany
	file ext:	h
	author:		����ȣ
	
	purpose:	PG�� ���������� ����ϴ� Ŭ���� �Դϴ�.
				BillSocketManager�κ��� ��û�� ������ �̰�����
				���� ��û�� ���� PG���� ��� �� Data�� Return ��ŵ�ϴ�.
*********************************************************************/

class CBillSocket_Germany
{
private: 
	SOCKET		m_hSocket;
	BYTE		m_szBuf[MAX_PACKETSIZE];		//	PG�����κ��� ���� Packet�� ������ Buffer
	DWORD		m_StartTime;					//	Receive���۽ð�

	SOCKADDR_IN	m_sServerAddress;				//	PG�� IP �� Port


public:
	CBillSocket_Germany();
	~CBillSocket_Germany();

public:
	bool						ConnectToServer();
	BYTE*						ReceivePacket();
	bool						SendBalancePacket(SI32 siAccountNumber, char* accountid);	
	bool						SendBuyPacket(SI32 siAccountNumber, TCHAR* accountid, TCHAR* szProductKey, SI32 siProductPrice, TCHAR* szProductName);
	bool						SendGiftPacket(SI32 siAccountNumber, char *accountid, char* szRecvUserName, TCHAR* szProductKey, SI32 siProductPrice, TCHAR* szProductName);
	bool						CheckOverTime_Bill();
	void						CloseBillSocket();
	void						WriteErrorLog(TCHAR* pszSource, int nLine , TCHAR * pszMsg);
};





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	PG ���� ����� Packet ����ü
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)

struct BILL_PACK_HEADER
{
	WORD	m_ReqLen;
	WORD	m_ReqType;
	WORD	m_RetCode;
};

//	�ܾ���ȸ
struct BILL_PACK_BALANCE
{
	BILL_PACK_HEADER m_Header;

	int		m_nUserNo;
	char	m_szUserID[50+1];

	DWORD	m_nCashRemain;	
};


//	����
struct BILL_PACK_BUY
{
	BILL_PACK_HEADER m_Header;

	int		m_nUserNo;
	char	m_szUserID[50+1];

	DWORD	m_nCashRemain;	
	char	m_szChargeNo[19+1];

	char	m_szItemID[30+1];
	int		m_nItemPrice;
	char	m_szItemName[50+1];
};


//	����
struct BILL_PACK_GIFT
{
	BILL_PACK_HEADER m_Header;

	int		m_nUserNo;
	char	m_szUserID[50+1];
	char	m_szReceiveUserID[50+1];

	DWORD	m_nCashRemain;	
	char	m_szChargeNo[19+1];

	char	m_szItemID[30+1];
	int		m_nItemPrice;
	char	m_szItemName[50+1];
};

#pragma pack()

#endif	//__BILLSOCKET_H__

