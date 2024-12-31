// RichODBC.h: interface for the RichODBC class.
//
//////////////////////////////////////////////////////////////////////

//#if !defined(AFX_RichODBC_H__9820EFEA_1038_4AB4_AB7E_997758F992C7__INCLUDED_)
//#define AFX_RichODBC_H__9820EFEA_1038_4AB4_AB7E_997758F992C7__INCLUDED_

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <Sqltypes.h>
#include <stdio.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_QUERY_SIZE	1024

class RichODBC  
{
public:
	RichODBC();
	~RichODBC();

	void		InitODBC();
	void		ReleaseODBC();

	VOID		SetParam(int siParamNo, int siType, void *pData, int siDatasize);
	int			GetData(int iColNo, int iType, void *pvData, long siDataSize);
	int			GetData(int iColNo, void *pvData, long siDataSize);
public:
	VOID		GetResult(VOID *pvResult, long siDatasize);
	int			GetRowcount();
	int			GetRetcode() { return m_retcode; }

	VOID		SetPooling(BOOL data) { IsPooling = data; }

private:
	BOOL		bReconnectStat;
	BOOL		bCanFetchRow;
public:
	void		inline SetReconnect(BOOL bStat) { bReconnectStat = bStat; }
	BOOL		inline GetReconnectStat() { return bReconnectStat; }

	BOOL		Connect(char *cDriver, char *cServer, char *cDatabase, char *cUserID, char *cPasswd);
	BOOL		ConnectProcess();
	BOOL		Reconnect();
	int			Disconnect();

	VOID		Prepare();
	int			ExecSQL();

	int			FetchData();
	int			NextRecordSet();

	int			SetQuery(char *pszQuery);

	//////////////////////////////////////////////////////////
	void		BeginSP(char *pszQuery);
	void		EndSP();
	void		SetParam(int siType, void *pData, int siDatasize);
	int			GetData(void *pvData, long siDataSize);
	/////////////////////////////////////////////////////////*/
	
	BOOL		CheckMDAC(char *cRequire);
	BOOL		CheckError(SQLSMALLINT hType, SQLHANDLE handle,char* hint=NULL, HWND hwnd = NULL);
	BOOL		IsSuccess(void);

	int			m_siParamNo;
	SQLINTEGER	m_siParamSize;

//protected:
	SQLHDBC		m_hdbc;
	SQLHSTMT	m_hstmt;
	SQLHENV		m_henv;

	SQLUINTEGER	m_siRowcount;
	SQLINTEGER	m_siNTS, m_siZero;
	char		m_cConnectionString[1024];
	char		*m_pszQuery;


private:
	RETCODE		m_retcode;
	long		m_lbytes;
	BOOL		IsPooling;
	
private:
	FILE		*m_Queryfp;
	char		m_cErrQuery[8192];
	void		PrintErrMsg(char *msg);
	void		PrintQuery(char *msg);
	void		PrintParam(char *msg);
	void		WriteQuery();
};

//#endif // !defined(AFX_RichODBC_H__9820EFEA_1038_4AB4_AB7E_997758F992C7__INCLUDED_)