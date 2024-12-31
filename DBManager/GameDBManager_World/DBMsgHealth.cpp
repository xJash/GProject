#include "DBGameProtocol.h"
//#include "DBMsg.h"
#include "DBMsg-Person.h"

void DBGameProtocol::SetHealth()
{
	// ���� ��Ŷ
	sDBRequest_SetHealth *pRecvMsg = (sDBRequest_SetHealth *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_SetHealth sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_SETHEALTH;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
//	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_HealthInfoSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		SetHealthInfo( &pRecvMsg->clHealthInfo );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		TCHAR log[512] = "";
		sprintf(log, "Hungry = %d, 	InnerOrg1 = %d,	InnerOrg2 = %d,	InnerOrg3 = %d,	InnerOrg4 = %d, Org1Disease = %d, Org2Disease = %d,	Org3Disease = %d, Org4Disease = %d,	HealthPoint = %d"
			, pRecvMsg->clHealthInfo.siHungry
			, pRecvMsg->clHealthInfo.siInnerOrg1, pRecvMsg->clHealthInfo.siInnerOrg2
			, pRecvMsg->clHealthInfo.siInnerOrg3, pRecvMsg->clHealthInfo.siInnerOrg4
			, pRecvMsg->clHealthInfo.uiOrg1Disease, pRecvMsg->clHealthInfo.uiOrg2Disease
			, pRecvMsg->clHealthInfo.uiOrg3Disease, pRecvMsg->clHealthInfo.uiOrg4Disease
			, pRecvMsg->clHealthInfo.uiHealthPoint
			);
		sDBLogMsg_QueryString LogMsg("Health Info Set", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}
