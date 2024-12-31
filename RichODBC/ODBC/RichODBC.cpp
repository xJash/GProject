#ifndef _RICHODBC_H
#define _RICHODBC_H

// RichODBC.cpp: implementation of the RichODBC class.
//
//////////////////////////////////////////////////////////////////////

#include "RichODBC.h"


#define _SIZE_ERROR_MESSAGE

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define REGULAR_SERVER	FALSE // TRUE�� ���� ������ �ø��� ���� , FALSE�� �׽�Ʈ ������ �ø��� ����

RichODBC::RichODBC()
{
	if(CheckMDAC("2.8") == FALSE)
	{
		::exit(0);
	}

//	m_pszQuery = new char[MAX_QUERY_SIZE];
	InitODBC();

	m_pErrorQueryFunc = NULL;
}

RichODBC::~RichODBC()
{
	ReleaseODBC();
//	if(m_pszQuery != NULL)
//		delete[] m_pszQuery;

//	if(pclHashTableString)		NDelete(pclHashTableString);
//	if(pclPerformance)			NDelete(pclPerformance);
}

/*////////////////////////////////////////////////////////////////////
Function Name : Destructor
Param : N/A
Desc : �޸� ����
	   ////////////////////////////////////////////////////////////////////*/
	   void RichODBC::ReleaseODBC()
{
	if(m_hdbc)
		SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);

	if(m_henv)
		SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
}


/*////////////////////////////////////////////////////////////////////
Function Name : Constructor
Param : N/A
Desc : ��� �������� �ʱ�ȭ
	   ////////////////////////////////////////////////////////////////////*/
	   void RichODBC::InitODBC()
{
	m_henv		= SQL_NULL_HENV;
	m_hdbc		= SQL_NULL_HDBC;
	m_hstmt		= SQL_NULL_HSTMT;

	m_siNTS		= SQL_NTS;
	m_siZero	= 0;
	m_siNULL	= SQL_NULL_DATA;

	m_siParamNo = 0;

	SetPooling(FALSE);

	m_kQuery = "";
	m_kErrQuery = "";

//	ZeroMemory(m_pszQuery, sizeof(m_pszQuery));

//	ZeroMemory(m_cErrQuery, sizeof(m_cErrQuery));

//	pclHashTableString = new NHashTableString< int >;
//	pclHashTableString->CreateHashTableString( MAX_PRCEDURE_COUNT, MAX_PRCEDURE_COUNT, 128 );

//	pclPerformance = new cltPerformance[MAX_PRCEDURE_COUNT];
//	if(pclPerformance)		ZeroMemory(pclPerformance, sizeof(cltPerformance) * MAX_PRCEDURE_COUNT);

//	dwLastTick = GetTickCount();
//	dwCurrentTick = 0;
}

void RichODBC::SetErroyQueryFunc(RICHODBC_ERRORQUERY pFunc)
{
	m_pErrorQueryFunc = pFunc;
}

/*////////////////////////////////////////////////////////////////////
Function Name : Connect
Param1 : Driver (char*) ex) "SQL Server"
Param2 : Server (char*) ex) "111.111.111.111"
Param3 : Database (char*) ex) "TestDB"
Param4 : USER ID (char*) ex) "sa"
Param5 : Password (char*) ex) "password"
Desc : Database�� ����
	   return : void
	   ////////////////////////////////////////////////////////////////////*/
	   BOOL RichODBC::Connect(char *cDriver, char *cServer, char *cDatabase, char *cUserID, char *cPasswd)
{
	ZeroMemory(m_cConnectionString, sizeof(m_cConnectionString));

	strcpy(m_cConnectionString, "DRIVER={");
	strcat(m_cConnectionString, cDriver);
	strcat(m_cConnectionString, "};SERVER=");
	strcat(m_cConnectionString, cServer);
	strcat(m_cConnectionString, ";DATABASE=");
	strcat(m_cConnectionString, cDatabase);
	strcat(m_cConnectionString, ";UID=");
	strcat(m_cConnectionString, cUserID);
	strcat(m_cConnectionString, ";PWD=");
	strcat(m_cConnectionString, cPasswd);
	strcat(m_cConnectionString, ";APP=RichODBC");
	strcat(m_cConnectionString, ";Auto Translate=FALSE");

	if(ConnectProcess() == TRUE)
	{
		SetReconnect(FALSE);
		return TRUE;
	}
	else
	{
		SetReconnect(TRUE);
		return FALSE;
	}
}


BOOL RichODBC::ConnectProcess()
{

	SQLTCHAR	szConnStrOut[1024+1];
	SQLSMALLINT	siStrLen;

	InitODBC();

	if( IsPooling )
	{
		m_retcode = SQLSetEnvAttr(NULL, SQL_ATTR_CONNECTION_POOLING, (PTR)SQL_CP_ONE_PER_DRIVER , SQL_IS_UINTEGER );
		if(!IsSuccess())
		{
			CheckError( SQL_HANDLE_ENV, m_henv );
			return FALSE;
		}
	}

	// ODBC ȯ�� ������ ���� �޸� �Ҵ�
	// Allocate the ODBC environment and save handle.
	m_retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
	if(!IsSuccess())
	{
		CheckError( SQL_HANDLE_ENV, m_henv );
		return FALSE;
	}

	// ODBC ȯ�� �Ӽ� ���� (ODBC���� 3.0)
	// Notify ODBC that this is an ODBC 3.0 app.
	m_retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
	if(!IsSuccess())
	{
		CheckError( SQL_HANDLE_ENV, m_henv );
		return FALSE;
	}

	// ODBC ������ ���� �޸� �Ҵ�
	// Allocate ODBC connection handle and connect.
	m_retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
	if(!IsSuccess())
	{
		CheckError( SQL_HANDLE_ENV, m_henv );
		return FALSE;
	}

	// ODBC�� �̿��� �����ͺ��̽����� ����Ӽ� ����
	//Make sure that autocommit is set to ON.
	m_retcode = SQLSetConnectAttr(m_hdbc,SQL_ATTR_AUTOCOMMIT,(void *)SQL_AUTOCOMMIT_ON,0);


	// Connect.
	m_retcode = SQLDriverConnect(m_hdbc, NULL, (SQLTCHAR*)m_cConnectionString, SQL_NTS, szConnStrOut, 1024, &siStrLen, SQL_DRIVER_NOPROMPT);
	if(!IsSuccess())
	{
		CheckError( SQL_HANDLE_DBC, m_hdbc );
		char szMessage[1024] = "";
		sprintf(szMessage, "Connect Fail\n", m_cConnectionString);
		MessageBox(NULL, szMessage, "SQLDriverConnect", MB_OK);
		return FALSE;
	}

	return TRUE;
}


BOOL RichODBC::Reconnect()
{

	SetReconnect(true);
	Disconnect();
	ReleaseODBC();
	return ConnectProcess();
}



/*////////////////////////////////////////////////////////////////////
Function Name : Prepare
Param1 : N/A
Desc : �ٸ� ������ �����Ͽ� �����Ҷ� ȣ���Ѵ�.
	   return : N/A
	   ////////////////////////////////////////////////////////////////////*/
	   void RichODBC::Prepare()
{
	SetReconnect(false);

	// Allocate statement handle.
	if(m_hstmt!=NULL)
	{
		m_retcode = SQLFreeHandle(SQL_HANDLE_STMT,m_hstmt);
		if(!IsSuccess())
		{
			CheckError( SQL_HANDLE_ENV, m_henv );
		}
	}

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if(!IsSuccess())
	{
		CheckError( SQL_HANDLE_ENV, m_henv );
	}
}


/*////////////////////////////////////////////////////////////////////
Function Name : SetQuery
Param1 : ���� (char*)
Desc : ������ ������ �Է¹���.
	   return : int(������ ���, ���н� ����)
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::SetQuery(char *pszQuery)
{
	Prepare();

	/*
	if(m_pszQuery != NULL)
	delete[] m_pszQuery;

	m_pszQuery = new char[strlen(pszQuery) + 1];
	*/
//	if( sizeof(pszQuery) >= MAX_QUERY_SIZE )
//		MessageBox(NULL, "������ ���� ������ ũ�Ⱑ ���ڸ��ϴ�.", "Error", MB_OK);

//	strncpy(m_pszQuery, pszQuery, MAX_QUERY_SIZE);
	m_kQuery = pszQuery;

	PrintQuery(pszQuery);

	return 1;
}

/*////////////////////////////////////////////////////////////////////
Function Name : Disconnect
Param1 : N/A
Desc : ������ �����ϰ� DB�ڵ��� ���� �����ش�.
	   return : int(������ ���, ���н� ����)
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::Disconnect()
{

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	m_retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	m_retcode = SQLDisconnect(m_hdbc);

	if(IsSuccess())
		return 1;
	else
		return m_retcode;
}


/*////////////////////////////////////////////////////////////////////
Function Name : GetData
Param1 : �÷� ��ȣ
Param2 : �޾ƿ� �������� ũ��
Param3 : ������ ������ 
Desc	  : ���� �������� ���� �����͸� �޴´�.
			return : int(������ ���, ���н� ����)
			////////////////////////////////////////////////////////////////////*/
			int RichODBC::GetData(int iColNo, void* pvData, long lDataSize)
{
	long ntd;
	if(IsSuccess())
		m_retcode = SQLGetData(m_hstmt, iColNo, SQL_C_DEFAULT, pvData, lDataSize, &ntd);
	else
		return -1;

	return 1;
}


/*////////////////////////////////////////////////////////////////////
Function Name : GetData
Param1 : �÷� ��ȣ
Param2 : ������ Ÿ�� (SQL_INTEGER, SQL_BINARY, SQL_CHAR)
Param3 : �޾ƿ� �������� ũ��
Param4 : ������ ������ 
Desc : ���� �������� ���� �����͸� �޴´�.
	   return : int(������ ���, ���н� ����)
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::GetData(int iColNo, int iType, void* pvData, long lDataSize)
{
	long ntd;
	if(IsSuccess())
		m_retcode = SQLGetData(m_hstmt, iColNo, iType, pvData, lDataSize, &ntd);
	else
		return -1;

	return 1;
}

/*////////////////////////////////////////////////////////////////////
Function Name : FetchData
Param1 : N/A
Desc : ���� �����͸� Fetch��Ų��.
return : int(������ ���, ���н� ����)
////////////////////////////////////////////////////////////////////*/
int RichODBC::FetchData()
{	
	m_siParamNo = 1;

	m_retcode = SQLFetch(m_hstmt);
	if(IsSuccess())
	{
		return 1;
	}
	else
	{
		if ( m_retcode != SQL_NO_DATA )
			CheckError(SQL_HANDLE_STMT, m_hstmt);
		return -1;
	}
}

/*////////////////////////////////////////////////////////////////////
Function Name : NextRecordSet
Param1 : N/A
Desc : ���� ���ڵ������ �̵��Ѵ�.
	   return : int(������ ���, ���̻� �����Ͱ� ������ 0, ���н� ����)
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::NextRecordSet()
{
	m_retcode = SQLMoreResults(m_hstmt);
	if(IsSuccess())
		return 1;
	else
	{
		if(m_retcode == SQL_NO_DATA)
			return 0;
		CheckError(SQL_HANDLE_STMT, m_hstmt);
		return -1;
	}
}

/*////////////////////////////////////////////////////////////////////
Function Name : ExecSQL
Param1 : N/A
Desc : ���õ� ������ �����Ѵ�.
	   return : int(������ ���, ���н� ����)
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::ExecSQL()
{
	//m_retcode = SQLExecDirect(m_hstmt,(SQLCHAR*)(LPSTR)(LPCSTR)m_pszQuery, SQL_NTS);
	char*	pszQuery = m_kQuery;
	m_retcode = SQLExecDirect(m_hstmt, (SQLCHAR*)pszQuery, SQL_NTS);

	if(!IsSuccess())
	{
		bCanFetchRow = FALSE;
		CheckError(SQL_HANDLE_STMT, m_hstmt, pszQuery);
		WriteQuery();
		return 0;
	}
	else
	{
		return 1;
	}
}


/*////////////////////////////////////////////////////////////////////
Function Name : IsSuccess
Param1 : N/A
Desc : ODBC���� ����� �����ߴ��� �����ߴ��� �Ǵ��Ѵ�.
	   return : BOOL (������ TRUE, ���н� FALSE)
	   ////////////////////////////////////////////////////////////////////*/
	   BOOL RichODBC::IsSuccess(void)
{
	if(m_retcode == SQL_SUCCESS)
		return TRUE;
	else if(m_retcode == SQL_SUCCESS_WITH_INFO)
		return TRUE;
	else
		return FALSE;
}


/*////////////////////////////////////////////////////////////////////
Function Name : CheckError
Param1 : �ڵ��� ���� (SQL_HANDLE_STMT, SQL_HANDLE_DBC, SQL_HANDLE_ENV���)
Param2 : �ڵ�
Param3 : �����޽����� �߰��� ǥ�õ� ��Ʈ...
Desc : ���� �߻��� �߻��� ������ ǥ���Ѵ�.
	   return : N/A
	   ////////////////////////////////////////////////////////////////////*/
	   BOOL RichODBC::CheckError(SQLSMALLINT hType, SQLHANDLE handle, char* hint, HWND hwnd)
{
	SQLCHAR       SqlState[6], Msg[SQL_MAX_MESSAGE_LENGTH];
	char caption[256]="", err[2048]="";
	SQLINTEGER    NativeError =0;
	SQLSMALLINT   i = 1, MsgLen;
	SQLRETURN	 thisRet ;
	BOOL	ret = TRUE ;

	ZeroMemory ( SqlState, sizeof(SqlState ) );
	ZeroMemory ( Msg, sizeof(Msg ) );

	if( hint ){
		strncpy(caption, hint, sizeof(caption) );
		strcat(caption, "\n" );
	}
	while ((thisRet = SQLGetDiagRec(hType, handle, i, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen) != SQL_NO_DATA))
	{
		if( thisRet == SQL_INVALID_HANDLE )
		{
			strncpy(err, "Invalid Handle\n", sizeof(err));
			break;
		}
		else if ( thisRet == SQL_ERROR )
		{
			strncpy(err, "RecNumber was negative or 0 \n", sizeof(err));
			strcat(err, "BufferLength was less than zero \n");
			break;
		} 

		if( hType == SQL_HANDLE_DBC && handle == m_hdbc && m_retcode == SQL_SUCCESS_WITH_INFO
			&& !strcmp( (char*)SqlState , "01000" ) )
		{
			ret = FALSE ;
		}
		else
		{
			ret = TRUE ;
			sprintf(err, "%s %s\n", SqlState, Msg);
			strcpy(err, (char*)SqlState);
			strcat(err, " ");
			strcat(err, (char*)Msg);
		}
		i++;
		PrintErrMsg(err);
	}

	if( !strcmp( (char*)SqlState, "08S01" ) )
	{
		Reconnect();
	}
	else if (		strcmp( (char*)SqlState, "01000" )
		&&	strcmp( (char*)SqlState, "24000" )
		&&	strcmp( (char*)SqlState, "23000" )
		&&	strcmp( (char*)SqlState, "42000" )
		)
	{
		//MessageBox(hwnd, m_cErrQuery, hint, MB_OK);
	}
	return ret;
}

BOOL RichODBC::CheckMDAC(char *cRequire)
{
	HKEY hKey;
	char cData[256]= "";
	char msg[1024];
	LONG result = 0;
	BOOL ret = FALSE;
	DWORD size = sizeof(cData);

	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\DataAccess", 0, KEY_READ, &hKey);
	if(result != ERROR_SUCCESS)
	{
		printf("Registry Open Failed : %d\n", result);
	}

	result = RegQueryValueEx(hKey, "FullInstallVer", 0, NULL, (BYTE*)cData, &size);
	if(result != ERROR_SUCCESS)
	{
		printf("Registry Query Failed : %d\n", result);
	}
	else
	{
		if(strcmp(cData, cRequire) >= 0)
			ret = TRUE;
		else
		{
			sprintf(msg, "�䱸���� : %s\n������� : %s", cRequire, cData);
			MessageBox(NULL, msg, "MDAC Version", MB_OK);
		}
	}

	RegCloseKey(hKey);
	return ret;
}

/*////////////////////////////////////////////////////////////////////
Function Name : GetResult
Param1 : ����� ���� ������
Param2 : �������� �ִ�ũ��.
Desc : ������ ������ ������� ��´�. ( ������ ����� 1�ο�/1�÷��� ��츸.)
	   return : N/A
	   ////////////////////////////////////////////////////////////////////*/
	   VOID RichODBC::GetResult(VOID *pvResult, long siDatasize)
{
	//	SQLINTEGER siRowcount=0;
	//	SQLSetStmtAttr(m_hstmt, SQL_ATTR_ROWS_FETCHED_PTR, &siRowcount, 0);

	while ( FetchData() > 0 )
	{
		//		m_siRowcount = siRowcount;
		GetData(1, SQL_C_DEFAULT, pvResult, siDatasize);
	}
}



/*////////////////////////////////////////////////////////////////////
Function Name : GetRowcount
Param1 : N/A
Desc : ���ϵ� ����� �ִ� �� ���� ��´�.
	   return : int
	   ////////////////////////////////////////////////////////////////////*/
	   int RichODBC::GetRowcount()
{
	return m_siRowcount;
}



/*////////////////////////////////////////////////////////////////////
Function Name : SetParam
Param1 : �Ķ��Ÿ ��ȣ
Param2 : ����Ÿ Ÿ��
Param3 : ����Ÿ
Param4 : ����Ÿ ����
Desc : ������ ȣ���Ҷ� ����� �Ķ��Ÿ�� �����Ѵ�.
	   return : N/A
	   ////////////////////////////////////////////////////////////////////*/
	   VOID RichODBC::SetParam(int siParamNo, int siType, void *pData, int siDatasize, SQLSMALLINT siParamType, bool bNull)
{
	/*///////////////////////////////////////////////////////////////////
	siType�� ����
SQL_CHAR		: char * (���ڿ�)
SQL_VARCHAR		: char * (���ڿ�)
SQL_TINYINT		: unsigned char (1byte)
SQL_SMALLINT	: small int (2byte)
SQL_INT			: long int	(4byte)
SQL_BIGINT		: _int64	(8byte)
SQL_REAL		: float		(4byte)
SQL_BINARY		: unsigned char * (�������ڿ�, �ִ���� 8000����Ʈ)
SQL_TYPE_TIMESTAMP : TIMESTAMP_STRUCT	(16byte)
					 ///////////////////////////////////////////////////////////////////*/
					 char buffer[100];
	ZeroMemory(buffer, sizeof(buffer));

	SQLINTEGER *pStrLen_or_IndPtr;


	switch(siType)
	{
	case SQL_CHAR:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siNTS;
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_TCHAR, SQL_CHAR, siDatasize, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam((char*)pData);
		}
		break;

	case SQL_VARCHAR:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siNTS;
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_TCHAR, SQL_VARCHAR, siDatasize, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam((char*)pData);
		}
		break;

	case SQL_BIT:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((char*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(char))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_BIT(1Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_BIT, SQL_BIT, 0, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_TINYINT:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((char*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(char))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_TINYINT(1Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_TINYINT, SQL_TINYINT, 0, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_SMALLINT:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((short*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(short int))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_SMALLINT(2Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_SHORT, SQL_SMALLINT, 0, 0, pData, 0,pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_INTEGER:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((short*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(int))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_INTEGER(4Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_LONG, SQL_INTEGER, 0, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_BIGINT:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((int*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(__int64))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_BIGINT(8Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_REAL:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((int*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(float))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_REAL(4Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_FLOAT, SQL_REAL, 0, 0, pData, 0, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;

	case SQL_FLOAT:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			_itoa( *((int*)(pData)), buffer, 10);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(double))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_FLOAT(8Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_DOUBLE, SQL_FLOAT, 0, 0, pData, 0, &m_siZero);
			PrintParam(buffer);
		}
		break;

	case SQL_BINARY:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siParamSize;
			m_siParamSize = siDatasize; // StrLen_or_IndPtr���ڴ� ���� Execute�ÿ� �����ϹǷ� ���������� ���� �����ϸ� �ʵȴ�.
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_BINARY, siDatasize, 0, pData, siDatasize, pStrLen_or_IndPtr);
			PrintParam("binary data");
		}
		break;

	case SQL_TIMESTAMP:
		{
			pStrLen_or_IndPtr = bNull?&m_siNULL:&m_siZero;
			sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d.%03d", ((TIMESTAMP_STRUCT*)pData)->year, ((TIMESTAMP_STRUCT*)pData)->month, ((TIMESTAMP_STRUCT*)pData)->day, ((TIMESTAMP_STRUCT*)pData)->hour, ((TIMESTAMP_STRUCT*)pData)->minute, ((TIMESTAMP_STRUCT*)pData)->second, ((TIMESTAMP_STRUCT*)pData)->fraction/1000000);
#ifdef _SIZE_ERROR_MESSAGE
			if(siDatasize != sizeof(TIMESTAMP_STRUCT))
			{
				char err[2048] = "";
				wsprintf( err, "ParamNo = %d, RequireSize = SQL_TIMESTAMP(16Byte), InputSize = %d\n%s\n", siParamNo, siDatasize, (TCHAR*)m_kQuery);
				BOOL bServer = REGULAR_SERVER ;
				if ( !bServer )
					MessageBox(NULL, err, "������ Ÿ���� Ʋ����", MB_OK);
			}
#endif
			m_retcode = SQLBindParameter(m_hstmt, siParamNo, siParamType, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 0, pData, 16, pStrLen_or_IndPtr);
			PrintParam(buffer);
		}
		break;
		
	}

	if(!IsSuccess())
	{
		bCanFetchRow = FALSE;
		CheckError(SQL_HANDLE_STMT, m_hstmt, (TCHAR*)m_kQuery);
		WriteQuery();
	}
}


void RichODBC::PrintQuery(char *msg)
{
	//ZeroMemory(m_cErrQuery, sizeof(m_cErrQuery));
	//sprintf(m_cErrQuery, "%s\n", msg);
	m_kErrQuery = msg;
	m_kErrQuery += "\n";
}

void RichODBC::PrintErrMsg(char *msg)
{
	//strcat(m_cErrQuery, "\n\t");
	m_kErrQuery += "\n\t";
	//strcat(m_cErrQuery, msg);
	m_kErrQuery += msg;
	//strcat(m_cErrQuery, "\n");
	m_kErrQuery += "\n";
}

void RichODBC::PrintParam(char *msg)
{
	//strcat(m_cErrQuery, "\t\t");
	m_kErrQuery += "\t\t";
	//strcat(m_cErrQuery, msg);
	m_kErrQuery += msg;
	//strcat(m_cErrQuery, "\n");
	m_kErrQuery += "\n";
}

void RichODBC::WriteQuery()
{
	SYSTEMTIME CT;
	GetLocalTime(&CT);

	char szFileName[256] = "";
	sprintf(szFileName, "ErrorQuery_%02d%02d%02d.log", CT.wYear, CT.wMonth, CT.wDay);

	m_Queryfp = fopen(szFileName, "a+");

	if(m_Queryfp)
	{
		fprintf(m_Queryfp, "\n%02d/%02d/%02d %02d:%02d:%02d %04d\n%s", CT.wYear, CT.wMonth, CT.wDay, CT.wHour, CT.wMinute, CT.wSecond, CT.wMilliseconds, (TCHAR*)m_kErrQuery);
		fclose(m_Queryfp);
	}

	if( m_pErrorQueryFunc )
	{
		m_pErrorQueryFunc( (const char*)m_kErrQuery );
	}
}

//*/////////////////////////////////////////////////////////
void RichODBC::BeginSP(char *pszQuery)
{
	Prepare();

	m_siParamNo = 0;

	//int index = 0;
	//bool bFind  = pclHashTableString->Find(pszQuery, index);

/*	if(bFind)
	{
		if(pclPerformance != NULL && index >= 0 && index < MAX_PRCEDURE_COUNT)
		{
			pclPerformance[index].siCall++;
		}
	}
	else
	{
		if(pclPerformance != NULL && siPerformanceCount >= 0 && siPerformanceCount < MAX_PRCEDURE_COUNT)
		{
			strncpy(pclPerformance[siPerformanceCount].szProcedureName, pszQuery, 128);
			pclPerformance[siPerformanceCount].szProcedureName[127] = '\0';
			pclHashTableString->Insert(pszQuery, siPerformanceCount);
			pclPerformance[siPerformanceCount].siCall++;
			siPerformanceCount++;
		}
	}*/

	//strcpy(m_pszQuery, "{call ");
	m_kQuery =  "{call ";
	//strcat(m_pszQuery, pszQuery);
	m_kQuery += pszQuery;

	PrintQuery((TCHAR*)pszQuery);

/*	if( GetTickCount() - dwLastTick > 300000 )		// 5�п� �ѹ��� ����
	{
		dwCurrentTick += GetTickCount() - dwLastTick;

		dwLastTick = GetTickCount();

		// �ϴ� ������ �α�����, �������� �Ǵ��Ѵ�.
		TCHAR	szFileName[256];
		if( siPerformanceCount < 10 )	{		strncpy(szFileName, "Procedure_Performance_Log.log", 256);		}
		else							{		strncpy(szFileName, "Procedure_Performance_Game.log", 256);		}

		FILE* fp = fopen(szFileName, "w");
		if(fp)
		{
			fprintf(fp, "Procedure\tCall\tCall/Sec\n");
			for(SI32 i=0; i<siPerformanceCount; i++)
			{
				SI32 siSec = dwCurrentTick / 1000;
				if(siSec <= 0)		siSec = 1;
				fprintf(fp, "%s\t%d\t%f\n", pclPerformance[i].szProcedureName, 
											pclPerformance[i].siCall, 
											(float)pclPerformance[i].siCall / (float)siSec);
			}
			fclose(fp);
		}
	}*/
}

void RichODBC::EndSP()
{
	if( m_siParamNo == 0 )
	{
		//strcat( m_pszQuery, "}" );
		m_kQuery += "}";
	}
	else
	{
		//strcat( m_pszQuery, " )}" );
		m_kQuery += " )}";
	}
}

void RichODBC::SetParam(int siType, void *pData, int siDatasize, SQLSMALLINT siParamType, bool bNull)
{
	if( m_siParamNo == 0 )
		//strcat( m_pszQuery, " ( ?" );
		m_kQuery += " ( ?";
	else
		//strcat( m_pszQuery, ", ?" );
		m_kQuery += ", ?";

	SetParam( ++m_siParamNo, siType, pData, siDatasize, siParamType, bNull );
}


int RichODBC::GetData(void *pvData, long siDataSize)
{
	return GetData( m_siParamNo++, pvData, siDataSize);
}
/////////////////////////////////////////////////////////*/


#endif