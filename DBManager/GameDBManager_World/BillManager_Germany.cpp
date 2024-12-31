#include "BillManager_Germany.h"
#include "BillSocket_Germany.h"

CBillManager_Germany::CBillManager_Germany()
{

}

CBillManager_Germany::~CBillManager_Germany()
{
	CloseBillSocket();				//	end correspondence
}


//	PG�� ���� �ܾ��� ��û�Ѵ�.
BYTE*	CBillManager_Germany::ProcessBalance(SI32 siAccountNumber, char* accountid)
{
	BYTE* pBuffer	=	NULL;
	bool bResult	=	false;

	bResult = m_cBillSocket.ConnectToServer();

	if(bResult == true)
		bResult = m_cBillSocket.SendBalancePacket(siAccountNumber, accountid);									//	Send Balance Packet


	if(bResult == true)
		pBuffer = m_cBillSocket.ReceivePacket();

	CloseBillSocket();

	return pBuffer;
}

//	PG�� ������ �ܾ� �� ��Ÿ ������ ��û�Ѵ�.
BYTE*	CBillManager_Germany::ProcessBuyItem(SI32 siAccountNumber, TCHAR* accountid, TCHAR* szProductKey, SI32 siProductPrice, TCHAR* szProductName)
{
	BYTE* pBuffer	=	NULL;
	bool bResult	=	false;

	bResult = m_cBillSocket.ConnectToServer();

	if(bResult == true)
		bResult = m_cBillSocket.SendBuyPacket(siAccountNumber, accountid, szProductKey, siProductPrice, szProductName);


	if(bResult == true)
		pBuffer = m_cBillSocket.ReceivePacket();

	CloseBillSocket();

	return pBuffer;
}


//	PG�� ���� �� �ܾ� �� ��Ÿ ������ ��û�Ѵ�.
BYTE*	CBillManager_Germany::ProcessGiftItem(SI32 siAccountNumber, TCHAR* accountid, TCHAR* Recvaccountid, TCHAR* siProductKey, SI32 siProductPrice, TCHAR* szProductName)
{
	BYTE* pBuffer	=	NULL;
	bool bResult	=	false;

	bResult = m_cBillSocket.ConnectToServer();

	if(bResult == true)
		bResult = m_cBillSocket.SendGiftPacket(siAccountNumber, accountid, Recvaccountid, siProductKey, siProductPrice, szProductName);									//	Send Balance Packet

	if(bResult == true)
		pBuffer = m_cBillSocket.ReceivePacket();

	CloseBillSocket();

	return pBuffer;
}

//	���� ������� ������ �ݴ´�.
//	���� �ð��� ������ �ݰ� ���־�� �Ѵ�.
void	CBillManager_Germany::CloseBillSocket()
{
	m_cBillSocket.CloseBillSocket();				//	end correspondence
}

void	CBillManager_Germany::WriteErrorLog(TCHAR* pszSource, int nLine , TCHAR * pszMsg)
{
	if( pszMsg == NULL) return;

	SYSTEMTIME CT;
	GetLocalTime(&CT);

	TCHAR szFileName[256] = "";
	sprintf(szFileName, "LOG_Germany_Billing_%02d%02d%02d.txt", CT.wYear, CT.wMonth, CT.wDay);

	FILE * fp = NULL;

	fp = fopen (szFileName , "a+");

	if( fp == NULL ) return;

	fprintf(fp , "%2d-%2d-%2d\t%s\t%4d\t%s\n" , CT.wHour , CT.wMinute , CT.wSecond , pszMsg  , nLine, pszSource );
	fclose(fp);	
}