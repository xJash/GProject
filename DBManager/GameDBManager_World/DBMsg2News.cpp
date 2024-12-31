#include "DBGameProtocol2.h"
#include "DBMsg.h"
#include "DBMsg-Web.h"

void DBGameProtocol2::News()
{
	// ���� ��Ŷ
	sDBRequest_News *pRecvMsg = (sDBRequest_News *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_News sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_NEWS;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );

	char szTime[20];
	ZeroMemory(szTime, sizeof(szTime));

	sprintf( szTime, "%d-%d-%d %d:%d:%d"
			, pRecvMsg->sTime.wYear, pRecvMsg->sTime.wMonth, pRecvMsg->sTime.wDay
			, pRecvMsg->sTime.wHour, pRecvMsg->sTime.wMinute, pRecvMsg->sTime.wSecond);

	// DB Query
	BEGIN_SP( "rsp_News" )
		m_odbc.SetParam( SQL_CHAR, szTime, sizeof(szTime) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		ZeroMemory( sendMsg.szNewsTitle, sizeof(sendMsg.szNewsTitle) );
		ZeroMemory( sendMsg.szNewspaperName, sizeof(sendMsg.szNewspaperName) );
		ZeroMemory( sendMsg.szNewURL, sizeof(sendMsg.szNewURL) );

		sendMsg.siResult = 1;
		m_odbc.GetData( sendMsg.szNewspaperName, sizeof(sendMsg.szNewspaperName) );
		m_odbc.GetData( sendMsg.szNewsTitle, sizeof(sendMsg.szNewsTitle) );
		m_odbc.GetData( sendMsg.szNewURL, sizeof(sendMsg.szNewURL) );
		// send
		SendPacket( (BYTE *)&sendMsg );
	END_FETCHDATA()

}