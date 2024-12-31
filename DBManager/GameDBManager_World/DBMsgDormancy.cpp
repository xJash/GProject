#include "DBGameProtocol.h"
#include "DBMsg-Dormancy.h"

//����Ʈ ����
void DBGameProtocol::DormancyBuyPointItem()
{	
	// ���� ��Ŷ
	sDBRequest_BuyDormancyPointItem* pRecvMsg = (sDBRequest_BuyDormancyPointItem*)m_pPacket;

	// ���� ��Ŷ
	sDBResonse_BuyDormancyPointItem sendMsg;
	sendMsg.m_sPacketHeader.usCmd	= DBMSG_RESPONSE_DORMANCY_POINTITEM_BUY;
	sendMsg.m_sPacketHeader.usSize	= sizeof(sendMsg);

	sendMsg.m_siItemPoint = pRecvMsg->m_siItemPoint;

	// DB Query
	BEGIN_SP( "rsp_DormancyPointItemBuy" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID));
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siItemPoint, sizeof(pRecvMsg->m_siItemPoint));
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->m_siItemPos, sizeof(pRecvMsg->m_siItemPos));
		SetItemParam( &pRecvMsg->m_clItem );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->m_bPileSwitch, sizeof(pRecvMsg->m_bPileSwitch));
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.m_siResult );
		m_odbc.GetData( &sendMsg.m_siPersonID );
		m_odbc.GetData( &sendMsg.m_siPoint );
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.m_siItemPos );
			GetItemData( &sendMsg.m_clItem );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

//����Ʈ ���� ���� ����
void DBGameProtocol::DormancySetPointInfo()
{
	// ���� ��Ŷ
	sDBRequest_SetDormancyPointInfo* pRecvMsg = (sDBRequest_SetDormancyPointInfo*)m_pPacket;

	// ���� ��Ŷ
	sDBResonse_SetDormancyPointInfo sendMsg;
	sendMsg.m_sPacketHeader.usCmd	= DBMSG_RESPONSE_DORMANCY_POINTINFO_SET;
	sendMsg.m_sPacketHeader.usSize	= sizeof(sendMsg);


	// DB Query
	BEGIN_SP( "rsp_DormancyPointSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID));
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPoint, sizeof(pRecvMsg->m_siPoint));
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siRemainedPlayTime, sizeof(pRecvMsg->m_siRemainedPlayTime));
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.m_siResult );
	END_FETCHDATA()
	
	sendMsg.m_siPersonID = pRecvMsg->m_siPersonID;
	sendMsg.m_siPoint = pRecvMsg->m_siPoint;
	sendMsg.m_siRemainedPlayTime = pRecvMsg->m_siRemainedPlayTime;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

//�޸� ���� ����
void DBGameProtocol::DormancyChangeState()
{
	// ���� ��Ŷ
	sDBRequest_ChangeDormancyState* pRecvMsg = (sDBRequest_ChangeDormancyState*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ChangeDormancyState sendMsg;
	sendMsg.m_sPacketHeader.usCmd	= DBMSG_RESPONSE_DORMANCY_STATE_CHANGE;
	sendMsg.m_sPacketHeader.usSize	= sizeof(sendMsg);

	// DB Query
	BEGIN_SP( "rsp_DormancyStateChange" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->m_siPersonID, sizeof(pRecvMsg->m_siPersonID));
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->m_bDormancyState, sizeof(pRecvMsg->m_bDormancyState));
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.m_siResult );
	END_FETCHDATA()

	sendMsg.m_siPersonID = pRecvMsg->m_siPersonID;
	sendMsg.m_bDormancyState = pRecvMsg->m_bDormancyState;

	// send
	SendPacket( (BYTE *)&sendMsg );
}