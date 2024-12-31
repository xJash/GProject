#include "ODBC/RichODBC.h"
#include <conio.h>
#include <typeinfo.h>

void main(void)
{
	// �ν��Ͻ� ����
	RichODBC db;
	
	// DB ����
	db.Connect("SQL Server", "192.168.1.49", "RichLog", "sa", "emfla");



/*
	//============================================================================================
	//	������ �����ϱ�...
	//============================================================================================
	{
		//--------------------------------------
		// �׽�Ʈ�� ���� ����..
		int idnum = 1, index = 0;
		int kind = 99, mapindex = 1, x = 44, y = 55;
		char name[21] = "123";
		int ret;
		//--------------------------------------
		// ���� �غ�..
		db.SetQuery("{call rsp_SetTest (?, ?, ?, ?, ?, ?, ?)}");

		// �Է� �Ķ��Ÿ�� ����.
		///////////////////////////////////////////////////////////////////////
		//siType�� ����
		//	SQL_VARCHAR		: char * (���ڿ�)
		//	SQL_CHAR		: char * (���ڿ�)
		//	SQL_TINYINT		: char (1byte)
		//	SQL_SMALLINT	: small int (2byte)
		//	SQL_INT			: long int	(4byte)
		//	SQL_BIGINT		: _int64	(8byte)
		//	SQL_BINARY		: unsigned char * (�������ڿ�, �ִ���� 8000����Ʈ)
		///////////////////////////////////////////////////////////////////////
		db.SetParam(1, SQL_INTEGER, &idnum, 0);
		db.SetParam(2, SQL_INTEGER, &index, 0);
		db.SetParam(3, SQL_INTEGER, &kind, 0);
		db.SetParam(4, SQL_VARCHAR, name, sizeof(name)-1);
		db.SetParam(5, SQL_INTEGER, &mapindex, 0);
		db.SetParam(6, SQL_INTEGER, &x, 0);
		db.SetParam(7, SQL_INTEGER, &y, 0);

		// ���� ����
		db.ExecSQL();

		while(db.FetchData()>0)
		{
			db.GetData(1, &ret, sizeof(ret));
		}

		printf("return = %d\n", ret);

		ret = 0;
	}
*/

	//============================================================================================
	//	������ ������...
	//============================================================================================
	{
		//--------------------------------------
		// �׽�Ʈ�� ���� ����..
		//--------------------------------------
		int siLogType = 2;
		char szServerName[20] = "����";
		char szPersonName[20] = "�̸�3";
		int siItemUnique = 0;
		char szStartDate[20] = "2005-06-08 00:00";
		char szEndDate[20] = "2005-06-08 23:59";

		// ���� �غ�..
		db.SetQuery("{call rsp_PersonalLog (?, ?, ?, ?, ?, ?)}");

		// �Է� �Ķ��Ÿ�� ����.
	//	db.SetParam(1, SQL_INTEGER, &idnum, sizeof(idnum));
		db.SetParam( 1, SQL_INTEGER, &siLogType, sizeof(siLogType) );
		db.SetParam( 2, SQL_VARCHAR, &szServerName, sizeof(szServerName) );
		db.SetParam( 3, SQL_VARCHAR, &szPersonName, sizeof(szPersonName) );
		db.SetParam( 4, SQL_INTEGER, &siItemUnique, sizeof(siItemUnique) );
		db.SetParam( 5, SQL_VARCHAR, &szStartDate, sizeof(szStartDate) );
		db.SetParam( 6, SQL_VARCHAR, &szEndDate, sizeof(szEndDate) );
		
		// ���� ����
		db.ExecSQL();
		
		char szDate[20] = "";
		char szCommand[50] = "";
		char szRetPersonName[20] = "";
		char szDstPersonName[20] = "";
		int siRetItemUnique = 0;
		char szLogTxt[512] = "";

		// ��� ���ϱ�.
		//db.GetResult(&idnum, sizeof(idnum));
		while(db.FetchData()>0)
		{
//			db.GetData(1, &kind, sizeof(kind));
//			db.GetData(2, name, sizeof(name));
//			db.GetData(3, &mapindex, sizeof(mapindex));
//			db.GetData(4, &x, sizeof(x));
//			db.GetData(5, &y, sizeof(y));
//			printf("kind:%d, name:%s, mapindex:%d, x:%d, y:%d\n", kind, name, mapindex, x, y);
			db.GetData( 1, &szDate, sizeof(szDate) );
			db.GetData( 2, &szCommand, sizeof(szCommand) );
			db.GetData( 3, &szRetPersonName, sizeof(szRetPersonName) );
			db.GetData( 4, &szDstPersonName, sizeof(szDstPersonName) );
			db.GetData( 5, &siRetItemUnique, 0 );
			db.GetData( 6, &szLogTxt, sizeof(szLogTxt) );
			printf("%s, %s, %s, %s, %d, %s\n", szDate, szCommand, szRetPersonName, szDstPersonName, siRetItemUnique, szLogTxt);
		}
	}
	//============================================================================================



	// DB ��������..
	db.Disconnect();
}
