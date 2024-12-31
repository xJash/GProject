//////////////////////////////////////////////////////////////////////////
//	created:	2009/04/30
//	created:	30:4:2009   13:51
//	filename: 	d:\GProject\DBManager\GameDBManager_World\BillManager_Germany.h
//	file path:	d:\GProject\DBManager\GameDBManager_World
//	file base:	BillManager_Germany
//	file ext:	h
//	author:		����ȣ
//	
//	purpose:	������ PG�� Bill ���� Manager
//				���Ӽ����κ��� PG ���� ��û�� �ýÿ� 
//				BillSocket�� ���� PG�� ��û�մϴ�.
//////////////////////////////////////////////////////////////////////////

#ifndef	__BILLMANAGER_H__
#define __BILLMANAGER_H__

#include "BillSocket_Germany.h"

//	CMD
enum REQTYPE_BILL
{
	REQTYPE_BILL_GET_BALANCE = 	10,			//	�ܾ���ȸ
	REQTYPE_BILL_PURCHASE	 =	20,			//	����
	REQTYPE_BILL_GIFT		 = 	30,			//	����
	REQTYPE_BILL_CALCEL		 =	40,			//	���
};

class CBillManager_Germany
{;
private:
	CBillSocket_Germany	m_cBillSocket;		//	�� ������ ���ؼ� PG�� ��� �մϴ�.


public:
	CBillManager_Germany();
	~CBillManager_Germany();

public:
	BYTE*	ProcessBalance(SI32 siAccountNumber, char* accountid);		
	BYTE*	ProcessBuyItem(SI32 siAccountNumber, TCHAR* accountid, TCHAR* szProductKey, SI32 siProductPrice, TCHAR* szProductName);	
	BYTE*	ProcessGiftItem(SI32 siAccountNumber, TCHAR* accountid, TCHAR* Recvaccountid, TCHAR* siProductKey, SI32 siProductPrice, TCHAR* szProductName);
	void	CloseBillSocket();
	void	WriteErrorLog(TCHAR* pszSource, int nLine , TCHAR * pszMsg);

};

#endif	//	__BILLMANAGER_H__