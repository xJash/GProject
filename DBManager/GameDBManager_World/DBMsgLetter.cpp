#include "DBGameProtocol.h"
#include "DBMsg.h"

void DBGameProtocol::PushLetter()
{
	// ���� ��Ŷ
	sDBRequest_PushLetter *pRecvMsg = (sDBRequest_PushLetter *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_PushLetter sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_PUSHLETTER;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );

	// DB Query
	BEGIN_SP( "rsp_LetterPush" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_BINARY, &pRecvMsg->clLetterUnit.cData, sizeof(pRecvMsg->clLetterUnit.cData) );
	END_SP()
	
	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
		m_odbc.GetData( &sendMsg.siPersonID,	0);
		m_odbc.GetData( &sendMsg.siLetterNum,	0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::PopLetter()
{
	// ���� ��Ŷ
	sDBRequest_PopLetter *pRecvMsg = (sDBRequest_PopLetter *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_PopLetter sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_POPLETTER;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_LetterPop" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( sendMsg.clLetterUnit.cData, sizeof(sendMsg.clLetterUnit.cData) );
		// send
		SendPacket( (BYTE *)&sendMsg );
	END_FETCHDATA()
}

void DBGameProtocol::PushAccountLetter()
{
	// ���� ��Ŷ
	sDBRequest_PushAccountLetter *pRecvMsg = (sDBRequest_PushAccountLetter *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_PushAccountLetter sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_PUSHACCOUNTLETTER;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );

	// DB Query
	BEGIN_SP( "rsp_LetterPushAccount" )
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szAccountID, sizeof(pRecvMsg->szAccountID) );
		m_odbc.SetParam( SQL_BINARY, pRecvMsg->clLetterUnit.cData, sizeof(pRecvMsg->clLetterUnit.cData) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0);
		m_odbc.GetData( sendMsg.szAccountID,	0);
		m_odbc.GetData( &sendMsg.siLetterNum,	0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::PopAccountLetter()
{
	// ���� ��Ŷ
	sDBRequest_PopAccountLetter *pRecvMsg = (sDBRequest_PopAccountLetter *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_PopAccountLetter sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_POPACCOUNTLETTER;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_LetterPopAccount" )
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szAccountID, sizeof(pRecvMsg->szAccountID) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( sendMsg.szAccountID, sizeof(sendMsg.szAccountID) );
		m_odbc.GetData( sendMsg.clLetterUnit.cData, sizeof(sendMsg.clLetterUnit.cData) );
		// send
		SendPacket( (BYTE *)&sendMsg );
	END_FETCHDATA()
}
