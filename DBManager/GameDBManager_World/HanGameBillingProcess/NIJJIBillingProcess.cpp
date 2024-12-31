//=============================================================================
//
//	NIJJIBillingProcess.cpp
//
//=============================================================================
#include "NIJJIBillingProcess.h"

NIJJIBillingProcess::NIJJIBillingProcess()
{
	m_coin = NULL;
	m_hdll = NULL;

	m_bTest = false;

}

NIJJIBillingProcess::~NIJJIBillingProcess()
{
	delete m_coin;
	FreeLibrary(m_hdll);
}

void NIJJIBillingProcess::Init( TCHAR *pszIP, UI16 usPort, UI32 uiTimeOut )
{ 	
	//---------------------------------------------------
	// �̱� ���񽺰� �ƴϸ� �ƹ��͵� ���� �ʴ´�.
#ifndef _USA
	return;
#endif
	//---------------------------------------------------

	if(m_hdll != NULL)			return;
	if(m_coin != NULL)			return;

	if (_tcscmp(pszIP, "TEST") == 0)
	{
		// �׽�Ʈ ���
		m_bTest = true;

		printf("=============================\n");
		printf("Test Billing Mode \n");
		printf("=============================\n");

		return;
	}

	// DLL �ε�
	m_hdll = LoadLibrary(DLL_LIBRARY);
	printf("=============================\n");
	if (m_hdll == NULL)
	{
		printf("Can't Load Library - %s\n", DLL_LIBRARY);
		return;
	}
	else
	{
		printf("Load Library Ok - %s\n", DLL_LIBRARY);
	}
	printf("=============================\n");


	// Ŭ���� �ν��Ͻ� �����Լ� �ε�
	PFunc func = (PFunc)GetProcAddress(m_hdll, "CreateNHNCoinInstance");
	printf("=============================\n");
	if (func == NULL)
	{
		printf("Can't Load Function - CreateNHNCoinInstance\n" );
		return;
	}
	else
	{
		printf("Load Function Ok - CreateNHNCoinInstance\n" );
	}
	printf("=============================\n");

	// Ŭ���� �ν��Ͻ� ����
	m_coin = (func)(pszIP, usPort, uiTimeOut);
	printf("=============================\n");
	if (m_coin == NULL)
	{
		printf("Fail to Create Instance - NHNCoin(IP:%s, Port:%d, TimeOut:%d) \n", pszIP, usPort, uiTimeOut );
		return;
	}
	else
	{
		printf("Create Instance Ok - NHNCoin(IP:%s, Port:%d, TimeOut:%d) \n", pszIP, usPort, uiTimeOut );
	}
	printf("=============================\n");
}

//[����] �Ѱ��� ����.  
bool NIJJIBillingProcess::GetBillingBalance(TCHAR* pszAccountID, SI32 siIDNo, SI32* psiToTalCoin )
{
	if(m_coin == NULL)
	{
		// ���� �α�
		TCHAR szMsg[2048];
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin == NULL") );
		WriteErrorLog(__FILE__,__LINE__, szMsg);
		return false;
	}

	char msg[1024] = {0};
	NHNCoin::RET_CODE retCode;
	int rtn = 0, totbal = 0;

	// IN
	TCHAR szIDNo[32];
	StringCchPrintf(szIDNo, sizeof(szIDNo), TEXT("%d"), siIDNo);

	// Process �α�
	TCHAR szMsg[2048];
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin->queryCoin() AccountID:%s, IDNo:%s"), pszAccountID, szIDNo );
	WriteProcessLog(__FILE__,__LINE__, szMsg);

	int siHanCoin, siInnerEvent, siOuterEvent, siGiftCard ;
	retCode = m_coin->queryCoin(pszAccountID, szIDNo, &rtn, msg, psiToTalCoin, &siHanCoin, &siInnerEvent, &siOuterEvent,  &siGiftCard);

	if(rtn == 0)
	{
		return true;
	}

	// ���� �α�
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("ID: %s, IDNo: %s, Code: %d, Msg: %s"), pszAccountID, szIDNo, rtn, msg);
	WriteErrorLog(__FILE__,__LINE__, szMsg);
}

bool NIJJIBillingProcess::GetBillingBalance(TCHAR* pszAccountID, SI32 siIDNo, SI32* psiHanCoin, SI32* psiGiftCard, SI32* psiInnerEvent, SI32* psiOuterEvent)
{
	// �׽�Ʈ ���
	if( m_bTest )
	{
		*psiHanCoin = 100000;
		return true;
	}

	if(m_coin == NULL)
	{
		// ���� �α�
		TCHAR szMsg[2048];
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin == NULL") );
		WriteErrorLog(__FILE__,__LINE__, szMsg);
		return false;
	}

	char msg[1024] = {0};
	NHNCoin::RET_CODE retCode;
	int rtn = 0, totbal = 0;

	// IN
	TCHAR szIDNo[32];
	StringCchPrintf(szIDNo, sizeof(szIDNo), TEXT("%d"), siIDNo);

	// Process �α�
	TCHAR szMsg[2048];
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin->queryCoin() AccountID:%s, IDNo:%s"), pszAccountID, szIDNo );
	WriteProcessLog(__FILE__,__LINE__, szMsg);

	retCode = m_coin->queryCoin(pszAccountID, szIDNo, &rtn, msg, &totbal, psiHanCoin, psiInnerEvent, psiOuterEvent, psiGiftCard);

	if(rtn == 0)
	{
		return true;
	}

	// ���� �α�
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("ID: %s, IDNo: %s, Code: %d, Msg: %s"), pszAccountID, szIDNo, rtn, msg);
	WriteErrorLog(__FILE__,__LINE__, szMsg);

	return false;
}


bool NIJJIBillingProcess::ChargeItem(TCHAR * pszAccountID , SI32 siIDNo, TCHAR* pszIP, SI32 siProductKey, TCHAR* pszProductName, SI32 siPrice , SI32 siProductNum )
{
	// �׽�Ʈ ���
	if( m_bTest )
	{
		return true;
	}

	if(m_coin == NULL)
	{
		// ���� �α�
		TCHAR szMsg[2048];
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin == NULL") );
		WriteErrorLog(__FILE__,__LINE__, szMsg);
		return false;
	}

	char sid[32] = {0};
	int rtn = 0, bal = 0;
	char msg[1024] = {0};

	// IN
	TCHAR szIDNo[32];
	StringCchPrintf(szIDNo, sizeof(szIDNo), TEXT("%d"), siIDNo);

	// IN - "0006" ���� USA�� ���ǵ� ��������.
	TCHAR szProductKind[32];
	StringCchPrintf(szProductKind, sizeof(szProductKind), TEXT("0006") );

	// IN
	TCHAR szProductKey[32];
	StringCchPrintf(szProductKey, sizeof(szProductKey), TEXT("%d"), siProductKey);

	// IN
	TCHAR szRefKey[32];
	StringCchPrintf(szRefKey, sizeof(szRefKey), TEXT("0"));

	// OUT
	TCHAR szSID[20] = {0};

	// Process �α�
	TCHAR szMsg[2048];
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin->useCoin() AccountID:%s, IDNo:%s"), pszAccountID, szIDNo );
	WriteProcessLog(__FILE__,__LINE__, szMsg);

	NHNCoin::RET_CODE retCode = m_coin->useCoin(pszAccountID, szIDNo, szProductKind, szProductKey, pszProductName, siPrice, szRefKey, pszIP, szSID, &rtn, &bal, msg);

	if(rtn == 0)
	{
		return true;
	}

	// ���� �α�
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("ID: %s, IDNo: %s, Code: %d, Msg: %s"), pszAccountID, szIDNo, rtn, msg);
	WriteErrorLog(__FILE__,__LINE__, szMsg);

	return false;
}

//[����] �����ֱ�. => 2008-7-23
BOOL NIJJIBillingProcess::GiftItem(TCHAR * pszGiftSendID, TCHAR * pszGiftRecvID , SI32 siIDNo, TCHAR* pszIP, SI32 siProductKey, TCHAR* pszProductName, SI32 siPrice , SI32 siProductNum )
{
	// �׽�Ʈ ���
	if( m_bTest )
	{
		return true;
	}

	if(m_coin == NULL)
	{
		// ���� �α�
		TCHAR szMsg[2048];
		StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin == NULL") );
		WriteErrorLog(__FILE__,__LINE__, szMsg);
		return false;
	}

	char sid[32] = {0};
	int rtn = 0, bal = 0;
	char msg[1024] = {0};

	// IN
	TCHAR szIDNo[32];
	StringCchPrintf(szIDNo, sizeof(szIDNo), TEXT("%d"), siIDNo);

	// IN - "0006" ���� USA�� ���ǵ� ��������.
	TCHAR szProductKind[32];
	StringCchPrintf(szProductKind, sizeof(szProductKind), TEXT("0006") );

	// IN
	TCHAR szProductKey[32];
	StringCchPrintf(szProductKey, sizeof(szProductKey), TEXT("%d"), siProductKey);

	// IN
	TCHAR szRefKey[32];
	StringCchPrintf(szRefKey, sizeof(szRefKey), TEXT("0"));

	// OUT
	TCHAR szSID[20] = {0};

	// Process �α�
	TCHAR szMsg[2048];
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("m_coin->useCoin() AccountID:%s, IDNo:%s"), pszGiftSendID, szIDNo );
	WriteProcessLog(__FILE__,__LINE__, szMsg);

	NHNCoin::RET_CODE retCode = m_coin->useCoinGift(pszGiftSendID, szIDNo, szProductKind, szProductKey, pszProductName, siPrice, szRefKey, pszIP, szSID, &rtn, &bal, msg);

	//[����] ijji�� ���� ���� ������ �������� ����-����ȸ���ʰ� �Ǵ� �ֱٱ��ű�Ϻ��� => 2008-7-23
	if(rtn == 0)
	{
		return TRUE;
	}

	// ���� �α�
	StringCchPrintf(szMsg, sizeof(szMsg), TEXT("ID: %s, IDNo: %s, Code: %d, Msg: %s"), pszGiftSendID, szIDNo, rtn, msg);
	WriteErrorLog(__FILE__,__LINE__, szMsg);

	return rtn;
}

void NIJJIBillingProcess::WriteProcessLog(TCHAR* pszSource, int nLine , TCHAR * pszMsg)
{
	if( pszMsg == NULL) return;

	SYSTEMTIME CT;
	GetLocalTime(&CT);

	TCHAR szFileName[256] = "";
	sprintf(szFileName, "ProcessLog_%02d%02d%02d.txt", CT.wYear, CT.wMonth, CT.wDay);

	FILE * fp = NULL;

	fp = fopen (szFileName , "a+");

	if( fp == NULL ) return;

	fprintf(fp , "%2d-%2d-%2d\t%s\t%4d\t%s\n" , CT.wHour , CT.wMinute , CT.wSecond , pszMsg  , nLine, pszSource );

	fclose(fp);

}
void NIJJIBillingProcess::WriteErrorLog(TCHAR* pszSource, int nLine , TCHAR * pszMsg)
{
	if( pszMsg == NULL) return;

	SYSTEMTIME CT;
	GetLocalTime(&CT);

	TCHAR szFileName[256] = "";
	sprintf(szFileName, "ErrorLog_%02d%02d%02d.txt", CT.wYear, CT.wMonth, CT.wDay);

	FILE * fp = NULL;

	fp = fopen (szFileName , "a+");

	if( fp == NULL ) return;

	fprintf(fp , "%2d-%2d-%2d\t%s\t%4d\t%s\n" , CT.wHour , CT.wMinute , CT.wSecond , pszMsg  , nLine, pszSource );

	fclose(fp);

}