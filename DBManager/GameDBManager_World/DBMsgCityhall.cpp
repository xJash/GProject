#include "DBGameProtocol.h"
#include "DBMsg-Structure.h"
#include "DBMsg-Cityhall.h"
#include "DBMsg-Item.h"

void DBGameProtocol::GetCityhallStrInfo()
{
	// ���� ��Ŷ
	sDBRequest_GetStrInfo *pRecvMsg = (sDBRequest_GetStrInfo *)m_pPacket;

	SendCityhallStrInfo( pRecvMsg->siVillageUnique, pRecvMsg->usCharID );
}

void DBGameProtocol::SendCityhallStrInfo( SI32 siVillageUnique, UI16 usCharID )
{
	sDBResponse_GetStrInfo sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GETSTRINFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = usCharID;

	sendMsg.clStrInfo.clCommonInfo.siStrType = RANKTYPE_CITYHALL;

	// DB Query
	BEGIN_SP( "rsp_CityHallInfoGet" )
		m_odbc.SetParam( SQL_INTEGER, &siVillageUnique,	sizeof(siVillageUnique) );
	END_SP()
	
	EXEC_SQL()
	
	SI32 siDate = 0;

	/* ������� */
	BEGIN_FETCHDATA()
		m_odbc.GetData( &(sendMsg.siResult), 0);
		m_odbc.GetData( &sendMsg.siVillageUnique,	0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.clMoney.itMoney, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clProfitMoney.itMoney, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siStockPrice, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siBeginningPrice, 0 );
		m_odbc.GetData( sendMsg.clStrInfo.clCommonInfo.strNotice, sizeof(sendMsg.clStrInfo.clCommonInfo.strNotice) );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siSymbolKind, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siSymbolLife, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siSymbolMana, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siSymbolCapa, 0 );
		m_odbc.GetData( &siDate, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clLastSymbolUpdate.MakeFullDateFromDateVary( siDate );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siCastleKind, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siCastleLife, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siCastleMana, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siCastleCapa, 0 );
		m_odbc.GetData( &siDate, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clLastCastleUpdate.MakeFullDateFromDateVary( siDate );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siVillageLevel, 0 );
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siLastDestroyStrDate, 0 );
		m_odbc.GetData( &siDate, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clChiefDate.MakeFullDateFromDateVary(siDate);
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siVisitLevel, 0 );
		m_odbc.GetData( &siDate, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clResignDate.MakeFullDateFromDateVary(siDate);
		m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.usCurStatus, 0 );
	END_FETCHDATA()

	// ��������
	SI32 siDeclareWarVillage = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			siDeclareWarVillage = 0;
			m_odbc.GetData( &siDeclareWarVillage,	0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.bDeclareWarVillage[siDeclareWarVillage], 0 );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// ������, ���� �й���
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiDeclareWarDateYear, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiDeclareWarDateMonth, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiDeclareWarDateDay, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiLastWarLoseDateYear, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiLastWarLoseDateMonth, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.uiLastWarLoseDateDay, 0 );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// ���� ���м�
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siVillaeWarRecordWin,	0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siVillaeWarRecordLose, 0 );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// ��� ����
	SI32 i = 0;
	SI32 siDateVary = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			if(i >= MAX_DIVIDEND_RECORD)
				break;		
			m_odbc.GetData( &siDateVary, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clDividendInfo.clDividendUnitInfo[i].clDate.MakeFullDateFromDateVary( siDateVary );
			m_odbc.GetData( &(sendMsg.clStrInfo.clCityhallStrInfo.clDividendInfo.clDividendUnitInfo[i].siTotalStock), 0);
			m_odbc.GetData( &(sendMsg.clStrInfo.clCityhallStrInfo.clDividendInfo.clDividendUnitInfo[i].clDividendPrice), 0);
			i++;
		END_FETCHDATA()
		sendMsg.clStrInfo.clCityhallStrInfo.clDividendInfo.siCount = i;
	END_NEXTRECORDSET()


	// NPC�������
	ZeroMemory( sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC, sizeof( sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC ) );
	ZeroMemory( sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC, sizeof( sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC ) );
	i = 0;
	SI32 siHireDateVary = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &(i), 0);
			if(i >= MAX_HIRED_NPC_NUM)
				MessageBox(NULL, "MAX_HIRED_NPC_NUM", "GameDBManager", MB_OK);
			m_odbc.GetData( &(sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC[i].siNPCKind), 0);
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC[i].siHirePay, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC[i].siMonthlyPay, 0 );
			m_odbc.GetData( &siHireDateVary, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clHiredNPC[i].clHireDate.MakeFullDateFromDateVary( siHireDateVary );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	i = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &(i), 0);
			if(i >= MAX_HIRED_NPC_NUM)
				MessageBox(NULL, "MAX_HIRED_CHRISTMASTREE", "GameDBManager", MB_OK);
			m_odbc.GetData( &(sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC[i].siNPCKind), 0);
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC[i].siHirePay, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC[i].siMonthlyPay, 0 );
			m_odbc.GetData( &siHireDateVary, 0 ); sendMsg.clStrInfo.clCityhallStrInfo.clHiredEventNPC[i].clHireDate.MakeFullDateFromDateVary( siHireDateVary );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// �� �ֹ� ��, �� ���� �ֽ� ��
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siResidentNum, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.siTotalStockAmount, 0 );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// ����ڱ� ����� ����
	SI32 siCount = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			if(siCount >= MAX_INOUTMONEY_RECORD)
				break;
			SI32 siDateVary = 0;
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.clInOutMoneyUnitInfo[siCount].siStrType, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.clInOutMoneyUnitInfo[siCount].siInOutCode, 0 );
			m_odbc.GetData( &siDateVary, 0 );	sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.clInOutMoneyUnitInfo[siCount].clDate.MakeFullDateFromDateVary( siDateVary );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.clInOutMoneyUnitInfo[siCount].clInOutMoney.itMoney, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.clInOutMoneyUnitInfo[siCount].clCityhallMoney.itMoney, 0 );
			siCount++;
		END_FETCHDATA()
	END_NEXTRECORDSET()
	
	sendMsg.clStrInfo.clCityhallStrInfo.clInOutMoneyInfo.siCount = siCount;


	// �ǹ� �⺻����
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.siStrDura, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.siNeedItemUnique, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.siNeedItemNum, 0 );
			m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.siUseItemNum, 0 );
			m_odbc.GetData( &(sendMsg.clStrInfo.clCommonInfo.clBaseMoney.itMoney), 0);
			m_odbc.GetData( &sendMsg.clStrInfo.clCommonInfo.siRepairStrDura, 0 );
		END_FETCHDATA()
	END_NEXTRECORDSET()


	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::PayDividend()
{
	// ���� ��Ŷ
	sDBRequest_PayDividend *pRecvMsg = (sDBRequest_PayDividend *)m_pPacket;
	sDBResponse_PayDividend sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_PAYDIVIDEND;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	cltGameDate clGameDate(&pRecvMsg->clDate);

	SI32 siDateVary = pRecvMsg->clDate.GetDateVary();
	SI32 siYear = pRecvMsg->usYear;
	// DB Query
	BEGIN_SP( "rsp_CityHallDividendPay" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->clTotalDividend.itMoney, sizeof(pRecvMsg->clTotalDividend.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siChiefPay, sizeof(pRecvMsg->siChiefPay) );
		m_odbc.SetParam( SQL_INTEGER, &siYear, sizeof(siYear) );
		m_odbc.SetParam( SQL_INTEGER, &siDateVary, sizeof(siDateVary) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siParentVillage, sizeof(pRecvMsg->siParentVillage) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siParentPay, sizeof(pRecvMsg->siParentPay) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siKingPay, sizeof(pRecvMsg->siKingPay) );
	END_SP()
	
	EXEC_SQL()
	
	siYear = siDateVary = 0;
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.siTotalStock, 0 );
		m_odbc.GetData( &sendMsg.clDividendPrice.itMoney, 0 );
		m_odbc.GetData( &sendMsg.siChiefPay, 0 );
		m_odbc.GetData( &sendMsg.siKingPersonID, 0 );
		m_odbc.GetData( &sendMsg.siKingPay, 0 );
		m_odbc.GetData( &sendMsg.siParentVillage, 0 );
		m_odbc.GetData( &sendMsg.siParentPay, 0 );
		m_odbc.GetData( &sendMsg.clParentCityhallMoney.itMoney, 0 );
		m_odbc.GetData( &siYear, 0 ); sendMsg.usYear = siYear;
		m_odbc.GetData( &siDateVary, 0 ); sendMsg.clDate.MakeFullDateFromDateVary( siDateVary );
		m_odbc.GetData( &sendMsg.clCityhallMoney.itMoney, 0 );
		m_odbc.GetData( &sendMsg.siPersonMoney, 0 );
	END_FETCHDATA()

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, TotalStock = %d, DividendPrice = %I64d, ChiefPay = %I64d, KingPay = %I64d, ParentVillage = %d, ParentPay = %I64d, CityHallMoney = %I64d, ParentCityHallMoney = %I64d, AfterChiefMoney = %I64d"
				, sendMsg.siVillageUnique, sendMsg.siTotalStock, sendMsg.clDividendPrice.itMoney, sendMsg.siChiefPay, sendMsg.siKingPay, sendMsg.siParentVillage, sendMsg.siParentPay, sendMsg.clCityhallMoney.itMoney, sendMsg.clParentCityhallMoney.itMoney, sendMsg.siPersonMoney
				);
		sDBLogMsg_QueryString LogMsg("Pay Dividend", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}

	BEGIN_NEXTRECORDSET()
		// ��� ����Ʈ
		sendMsg.usPersonCount = 0;
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.clDividendPerson[sendMsg.usPersonCount].siPersonID, 0 );
			m_odbc.GetData( &sendMsg.clDividendPerson[sendMsg.usPersonCount].clMoney.itMoney, 0 );

			// �α� �ۼ�
			if(sendMsg.siResult == 1)
			{
				char log[512] = "";
				sprintf(log, "VillageUnique = %d, DividendMoney = %I64d"
						, sendMsg.siVillageUnique, sendMsg.clDividendPerson[sendMsg.usPersonCount].clMoney.itMoney
						);
				sDBLogMsg_QueryString LogMsg("Pay Dividend", sendMsg.clDividendPerson[sendMsg.usPersonCount].siPersonID, NULL, NULL, log);
				SendLogMsg((sPacketHeader *)&LogMsg);
			}

			sendMsg.usPersonCount++;
		END_FETCHDATA()
	END_NEXTRECORDSET()

	sendMsg.siKingPayPersent = pRecvMsg->siKingPayPersent;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::AppplyResident()
{
	// ���� ��Ŷ
	sDBRequest_ApplyResident *pRecvMsg = (sDBRequest_ApplyResident *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_ApplyResident sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_APPLYRESIDENT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bSendMsg = pRecvMsg->bSendMsg;


	SI32 siMAX_RESIDENT_APPLYER = MAX_RESIDENT_APPLYER;
	cltGameDate clDate( &pRecvMsg->clDate );
	
	// DB Query
	BEGIN_SP( "rsp_ResidentApply" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		SetGameDate( &clDate );
		m_odbc.SetParam( SQL_INTEGER, &siMAX_RESIDENT_APPLYER, sizeof(siMAX_RESIDENT_APPLYER) );
		//m_odbc.SetParam( SQL_BIT, &pRecvMsg->bAutoResident, sizeof(pRecvMsg->bAutoResident) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		GetResidentApplyerInfo( &sendMsg.clApplyer );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::GetResidentApplyerList()
{
	// ���� ��Ŷ
	sDBRequest_GetResidentApplyerList *pRecvMsg = (sDBRequest_GetResidentApplyerList *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_GetResidentApplyerList sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GETRESIDENTAPPLYERLIST;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ResidentApplyerListGet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
	END_FETCHDATA()

	// ���� ���ڵ������ �̵��Ѵ�.
	BEGIN_NEXTRECORDSET()
		SI32 i = 0;
		BEGIN_FETCHDATA()
			if(i >= MAX_RESIDENT_APPLYER)
			{
				char szCount[12];
				_itoa(i, szCount, 10);
				MessageBox( NULL, szCount, "GameDBManager - MAX_RESIDENT_APPLYER", MB_OK );
				break;
			}
			GetResidentApplyerInfo( &sendMsg.clApplyer[i++] );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}


void DBGameProtocol::GetResidentList()
{
	// ���� ��Ŷ
	sDBRequest_GetResidentList *pRecvMsg = (sDBRequest_GetResidentList *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_GetResidentList sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GETRESIDENTLIST;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ResidentListGet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siSort, sizeof(pRecvMsg->siSort) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
	END_FETCHDATA()

	// ���� ���ڵ������ �̵��Ѵ�.
	BEGIN_NEXTRECORDSET()
		SI32 i = 0;
		BEGIN_FETCHDATA()
			if(i >= MAX_RESIDENT_NUMBER)
			{
				/*
				char szCount[12];
				_itoa(i, szCount, 10);
				MessageBox( NULL, szCount, "GameDBManager - MAX_RESIDENT_NUMBER", MB_OK );
				*/
				break;
			}
			GetResidentInfo( &sendMsg.clResident[i++] );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::BeResident()
{
	// ���� ��Ŷ
	sDBRequest_BeResident *pRecvMsg = (sDBRequest_BeResident *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_BeResident sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_BERESIDENT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	cltGameDate clDate( &pRecvMsg->clDate );
	
	SI32 siMAX_RESIDENT_NUMBER = MAX_RESIDENT_NUMBER;

	// [����] �ʺ��� ���� : �ʺ��� ���� �ֹμ� ������ Const_BV_Max_Resident_Num�� �ٲ�
	if ( Const_Beginner_Village == pRecvMsg->siVillageUnique )
	{
		siMAX_RESIDENT_NUMBER = Const_BV_Max_Resident_Num;
	}

	// DB Query
	BEGIN_SP( "rsp_ResidentSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		SetGameDate( &clDate );
		m_odbc.SetParam( SQL_INTEGER, &siMAX_RESIDENT_NUMBER, sizeof(siMAX_RESIDENT_NUMBER) );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bAutoResident, sizeof(pRecvMsg->bAutoResident) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		GetResidentInfo( &sendMsg.clResident );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d"
				,	pRecvMsg->siVillageUnique
				);
		sDBLogMsg_QueryString LogMsg("Resident Set", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::CancelResident()
{
	// ���� ��Ŷ
	sDBRequest_CancelResident *pRecvMsg = (sDBRequest_CancelResident *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_CancelResident sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CANCELRESIDENT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ResidentCancel" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bAutoCancel, sizeof(pRecvMsg->bAutoCancel) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.siResidentNum, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d"
				,	pRecvMsg->siVillageUnique
				);
		sDBLogMsg_QueryString LogMsg("Resident Cancel", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::GetResidentInfo()
{
	// ���� ��Ŷ
	sDBRequest_GetResidentInfo *pRecvMsg = (sDBRequest_GetResidentInfo *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_GetResidentInfo sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GETRESIDENTINFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ResidentInfoGet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szPersonName,	sizeof(pRecvMsg->szPersonName) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );		
		m_odbc.GetData( sendMsg.szPersonName, sizeof( sendMsg.szPersonName) );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siScore, 0 );
		GetGameDate( &sendMsg.clRegDate );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::SetResidentScore()
{
	// ���� ��Ŷ
	sDBRequest_SetResidentScore *pRecvMsg = (sDBRequest_SetResidentScore *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_SetResidentScore sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_SETRESIDENTSCORE;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ResidentScoreSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,	sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siScore,	sizeof(pRecvMsg->siScore) );
	END_SP()

	EXEC_SQL()

	SI32 siResult;

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::HireNPC()
{
	// ���� ��Ŷ
	sDBRequest_HireNPC *pRecvMsg	= (sDBRequest_HireNPC *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_HireNPC sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_HIRENPC;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	SI32 siHireDate = pRecvMsg->clHireNPCInfo.clHireDate.GetDateVary();
	// DB Query
	BEGIN_SP( "rsp_NpcHire" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_SMALLINT, &(pRecvMsg->usSlot), sizeof(pRecvMsg->usSlot) );
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->clHireNPCInfo.siNPCKind), sizeof(pRecvMsg->clHireNPCInfo.siNPCKind) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clHireNPCInfo.siHirePay), sizeof(pRecvMsg->clHireNPCInfo.siHirePay) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clHireNPCInfo.siMonthlyPay), sizeof(pRecvMsg->clHireNPCInfo.siMonthlyPay) );
		m_odbc.SetParam( SQL_INTEGER, &(siHireDate), sizeof(siHireDate) );
		m_odbc.SetParam( SQL_TINYINT, &(pRecvMsg->uiMode), sizeof(pRecvMsg->uiMode) );
	END_SP()

	EXEC_SQL()
	
	siHireDate = 0;
	BEGIN_FETCHDATA()
		m_odbc.GetData( &(sendMsg.siResult), 0 );
		m_odbc.GetData( &(sendMsg.siVillageUnique), 0 );
		m_odbc.GetData( &(sendMsg.usSlot), 0 );
		m_odbc.GetData( &(sendMsg.clHireNPCInfo.siNPCKind), 0 );
		m_odbc.GetData( &(sendMsg.clHireNPCInfo.siHirePay), 0 );
		m_odbc.GetData( &(sendMsg.clHireNPCInfo.siMonthlyPay), 0 );
		m_odbc.GetData( &siHireDate, 0 ); sendMsg.clHireNPCInfo.clHireDate.MakeFullDateFromDateVary(siHireDate);
		m_odbc.GetData( &(sendMsg.clCityhallMoney.itMoney), 0);
		m_odbc.GetData( &(sendMsg.uiMode), 0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, Mode = %d, NpcSlot = %d, NpcKind = %d, HirePay = %I64d, MonthlyPay = %I64d, CityhallMoney = %I64d"
				, pRecvMsg->siVillageUnique, pRecvMsg->uiMode, pRecvMsg->usSlot, pRecvMsg->clHireNPCInfo.siNPCKind
				, pRecvMsg->clHireNPCInfo.siHirePay, pRecvMsg->clHireNPCInfo.siMonthlyPay, sendMsg.clCityhallMoney.itMoney
				);
		sDBLogMsg_QueryString LogMsg("NPC Hire", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::ResidentShare()
{
	// ���� ��Ŷ
	sDBRequest_ResidentShare *pRecvMsg = (sDBRequest_ResidentShare *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ResidentShare sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_RESIDENTSHARE;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
//	sendMsg.usCharID = pRecvMsg->usCharID;

	SI32 siResult	= 0;
	GMONEY itMoney	= 0;

	GMONEY itTotalShareMoney = 0;

	// �ֹι����� �ջ��Ѵ�.
	for(SI32 i = 0; i < pRecvMsg->siCount; i++)
	{
		itTotalShareMoney += pRecvMsg->siShareMoney[i];
	}

	if(pRecvMsg->clTotalShareMoney.itMoney >= itTotalShareMoney)
	{
		/* �����ڱݿ��� ���� ����. */
		ResidentShareSetVillage( pRecvMsg->siVillageUnique, pRecvMsg->clTotalShareMoney.itMoney, &siResult, &itMoney);

		/* ��ܺ����ڱ��� ����ϴٸ� ���� �ֹο��� ����� �ǽ��Ѵ�. */
		if( siResult == 1 )
		{
			for(SI32 siCount = 0; siCount < pRecvMsg->siCount; siCount++)
			{
				ResidentShareSetPerson( pRecvMsg->siVillageUnique, pRecvMsg->siPersonID[siCount], pRecvMsg->siShareMoney[siCount], &sendMsg.siMoney[siCount] );

				sendMsg.siCharIndex[ siCount ] = pRecvMsg->siCharIndex[ siCount ];
				sendMsg.siPersonID[ siCount ] = pRecvMsg->siPersonID[ siCount ];
				sendMsg.siShareMoney[ siCount ] = pRecvMsg->siShareMoney[ siCount ];
			}
		}
		sendMsg.siResult			= siResult;
	}
	else
	{
		sendMsg.siResult			= 3;
	}

	sendMsg.siVillageUnique			= pRecvMsg->siVillageUnique;
	sendMsg.clTotalShareMoney.Set( &pRecvMsg->clTotalShareMoney );
	sendMsg.clCityhallMoney.itMoney	= itMoney;
	sendMsg.siCount					= pRecvMsg->siCount;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ResidentManyOut()
{
	// ���� ��Ŷ
	sDBRequest_ManyResidentOut *pRecvMsg = (sDBRequest_ManyResidentOut *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ManyResidentOut sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_MANYRESIDENTOUT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	SI32 siDate = pRecvMsg->clDate.GetDateVary();
	SI32 siCount = 0;
	// DB Query
	BEGIN_SP( "rsp_ResidentManyOut" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &(siDate), sizeof(siDate) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.usCount, 0);
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
	BEGIN_FETCHDATA()
		if(siCount >= 200)
			continue;
		m_odbc.GetData( &sendMsg.siPersonID[siCount++], 0 );
	END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}


void DBGameProtocol::SetInOutMoney()
{
	// ���� ��Ŷ
	sDBRequest_CityHallSetInOutMoney *pRecvMsg	= (sDBRequest_CityHallSetInOutMoney *)m_pPacket;
	
	// ���� ��Ŷ
	SI32 siDateVary = pRecvMsg->clDate.GetDateVary();

	// PCK : �α׿� ���� ��Ŷ �߰�
	sDBResponse_CityHallSetInOutMoney sendMsg;

	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_CITYHALL_SETINOUTMONEY;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID			= pRecvMsg->usCharID;
	sendMsg.siVillageUnique		= pRecvMsg->siVillageUnique;
	sendMsg.siStrType			= pRecvMsg->siStrType;
	sendMsg.siInOutCode			= pRecvMsg->siInOutCode;
	sendMsg.clCityHallMoney.Set( &pRecvMsg->clCityHallMoney);
	sendMsg.clInOutMoney.Set( &pRecvMsg->clInOutMoney);
	sendMsg.clDate.Set( &pRecvMsg->clDate);

	// DB Query
	BEGIN_SP( "rsp_CityHallInoutMoneySet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique,			sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siStrType,					sizeof(pRecvMsg->siStrType) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siInOutCode,				sizeof(pRecvMsg->siInOutCode) );
		m_odbc.SetParam( SQL_INTEGER, &siDateVary,							sizeof(siDateVary) );
		m_odbc.SetParam( SQL_BIGINT,  &pRecvMsg->clInOutMoney.itMoney,		sizeof(pRecvMsg->clInOutMoney.itMoney) );
		m_odbc.SetParam( SQL_BIGINT,  &pRecvMsg->clCityHallMoney.itMoney,	sizeof(pRecvMsg->clCityHallMoney.itMoney) );
	END_SP()

	EXEC_SQL()

	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, StrType = %d, InOutCode = %d, InoutMoney = %I64d, CityHallMoney = %I64d"
				, pRecvMsg->siVillageUnique, pRecvMsg->siStrType, pRecvMsg->siInOutCode, pRecvMsg->clInOutMoney.itMoney, pRecvMsg->clCityHallMoney.itMoney
				);
		sDBLogMsg_QueryString LogMsg("CityHall InOut Money", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::ChangeCityHallProfitMoney()
{
	// ���� ��Ŷ
	sDBRequest_ChangeCityhallProfitMoney *pRecvMsg	= (sDBRequest_ChangeCityhallProfitMoney *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_ChangeCityhallProfitMoney sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CHANGECITYHALLPROFITMONEY;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
//	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_CityhallChangeProfit" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->siMoney), sizeof(pRecvMsg->siMoney) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.clMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.siChangeMoney, 0);
	END_FETCHDATA()

	sendMsg.siReason = pRecvMsg->siReason;
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, Reason = %d, CityhallMoney = %I64d, ChangedMoney = %I64d"
				, pRecvMsg->siVillageUnique, sendMsg.siReason, sendMsg.clMoney.itMoney, sendMsg.siChangeMoney
				);
		sDBLogMsg_QueryString LogMsg("Change Cityhall Profit", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::ProfitToCapitalFund()
{
	// ���� ��Ŷ
	sDBRequest_ProfitToCapitalFund *pRecvMsg	= (sDBRequest_ProfitToCapitalFund *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_ProfitToCapitalFund sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_PROFITTOCAPITALFUND;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	// DB Query
	BEGIN_SP( "rsp_CityhallProfitToCapitalFund" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->siMoney), sizeof(pRecvMsg->siMoney) );
	END_SP()

	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.clCapitalFund.itMoney, 0);
		m_odbc.GetData( &sendMsg.clProfitMoney.itMoney, 0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, CapitalFund = %I64d, ProfitMoney = %I64d, ChangedMoney = %I64d"
				, pRecvMsg->siVillageUnique, sendMsg.clCapitalFund.itMoney, sendMsg.clProfitMoney.itMoney, pRecvMsg->siMoney
				);
		sDBLogMsg_QueryString LogMsg("Cityhall Profit to CapitalFund", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::CityHallStateChange()
{
	// ���� ��Ŷ
	sDBRequest_CityHall_State_Changed *pRecvMsg	= (sDBRequest_CityHall_State_Changed *)m_pPacket;

	// ���� ��Ŷ
	sDBReponse_CityHall_State_Changed sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CITYHALL_STATE_CHANGED;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
//	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_CityhallStateChange" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_TINYINT, &(pRecvMsg->usPrevStatus), sizeof(pRecvMsg->usPrevStatus) );
		m_odbc.SetParam( SQL_TINYINT, &(pRecvMsg->usCurStatus), sizeof(pRecvMsg->usCurStatus) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.usPrevStatus, 0);
		m_odbc.GetData( &sendMsg.usCurStatus, 0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, PrevStatus = %d, CurStatus = %d"
			, pRecvMsg->siVillageUnique, sendMsg.usPrevStatus, sendMsg.usCurStatus
			);
		sDBLogMsg_QueryString LogMsg("Cityhall State Change", 0, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::NotifyCityhallBankruptcy()
{
	// ���� ��Ŷ
	sDBRequest_Notify_Cityhall_Bankruptcy *pRecvMsg	= (sDBRequest_Notify_Cityhall_Bankruptcy *)m_pPacket;

	// ���� ��Ŷ
	sDBReponse_Notify_Cityhall_Bankruptcy sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_NOTIFY_CITYHALL_BANKRUPTCY;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	//	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_CityhallNotifyBankruptcy" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
	END_SP()

	EXEC_SQL()

	SI32 siCount = 0;
	BEGIN_FETCHDATA()
		if(siCount >= MAX_BANKRUPT_STOCKHOLDER_NUMBER_TO_BE_NOTIFIED)
		{
			break;
		}
		m_odbc.GetData( &sendMsg.siPersonID[siCount++], 0 );
	END_FETCHDATA()

	if(siCount > 0)
	{
		sendMsg.siResult = 1;
	}

	sendMsg.usType = pRecvMsg->usType;
	sendMsg.siVillageUnique = pRecvMsg->siVillageUnique;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::AutoPayDividend()
{
	// ���� ��Ŷ
	sDBRequest_AutoPayDividend *pRecvMsg	= (sDBRequest_AutoPayDividend *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_AutoPayDividend sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_AUTOPAYDIVIDEND;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	SI32 siDate = pRecvMsg->clDate.GetDateVary();
	SI32 siChiefPersonID = 0;

	// DB Query
	BEGIN_SP( "rsp_CityHallAutoPayDividend" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->clStockDividend.itMoney, sizeof(pRecvMsg->clStockDividend.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->clResidentDividend.itMoney, sizeof(pRecvMsg->clResidentDividend.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->clTaxlDividend.itMoney, sizeof(pRecvMsg->clTaxlDividend.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siChiefPay, sizeof(pRecvMsg->siChiefPay) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siKingPay, sizeof(pRecvMsg->siKingPay) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->usYear, sizeof(pRecvMsg->usYear) );
		m_odbc.SetParam( SQL_INTEGER, &siDate, sizeof(siDate) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siVillageUnique, 0 );
		m_odbc.GetData( &sendMsg.siTotalStock, 0 );
		m_odbc.GetData( &sendMsg.clStockDividendPrice.itMoney, 0 );
		m_odbc.GetData( &sendMsg.clResidentDividendPrice.itMoney, 0 );
		m_odbc.GetData( &sendMsg.clTaxDividendPrice.itMoney, 0 );
		m_odbc.GetData( &sendMsg.siChiefPay, 0 );
		m_odbc.GetData( &sendMsg.siKingPersonID, 0 );
		m_odbc.GetData( &sendMsg.siKingPay, 0 );
		m_odbc.GetData( &sendMsg.clKingAllMoney, 0 );
		m_odbc.GetData( &sendMsg.clCityhallMoney.itMoney, 0 );
		m_odbc.GetData( &sendMsg.siPersonMoney, 0 );
		m_odbc.GetData( &siChiefPersonID, 0 );
	END_FETCHDATA()

	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.usStockPersonCount );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			m_odbc.GetData( &sendMsg.usResidentPersonCount );
		END_FETCHDATA()
	END_NEXTRECORDSET()


	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, StockHolder = %d, TotalStock = %d, MoneyPerStock = %I64d, Residents = %d, MoneyPerResident = %I64d, Tax = %I64d, LeftCityhallProfitMoney = %I64d, LeftChiefMoney = %I64d"
			, pRecvMsg->siVillageUnique, sendMsg.usStockPersonCount, sendMsg.siTotalStock, sendMsg.clStockDividendPrice.itMoney, sendMsg.usResidentPersonCount, sendMsg.clResidentDividendPrice.itMoney
			, sendMsg.clTaxDividendPrice.itMoney, sendMsg.clCityhallMoney.itMoney, sendMsg.siPersonMoney
			);
		sDBLogMsg_QueryString LogMsg("Dividend Summary", 0, siChiefPersonID, sendMsg.siKingPersonID, log);
		SendLogMsg((sPacketHeader *)&LogMsg);

	}

	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, ChiefPay = %I64d, ChiefBankMoney = %I64d"
			, pRecvMsg->siVillageUnique, sendMsg.siChiefPay, sendMsg.siPersonMoney
			);
		sDBLogMsg_QueryString LogMsg("Dividend ChiefPay", 0, siChiefPersonID, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}

	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, KingPay = %I64d, KingBankMoney = %I64d"
			, pRecvMsg->siVillageUnique, sendMsg.siKingPay, sendMsg.clKingAllMoney
			);
		sDBLogMsg_QueryString LogMsg("Dividend KingPay", 0, sendMsg.siKingPersonID, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}

	SI32 siIndex = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			if(siIndex >= MAX_DIVIDEND_PERSON) break;
			m_odbc.GetData( &sendMsg.clStockDividendPerson[siIndex].siPersonID);
			m_odbc.GetData( &sendMsg.clStockDividendPerson[siIndex].clMoney.itMoney);
			m_odbc.GetData( &sendMsg.clStockDividendPerson[siIndex].clAllMoney.itMoney);
			// �α� �ۼ�
			if(sendMsg.siResult == 1)
			{
				char log[512] = "";
				sprintf(log, "VillageUnique = %d, DividendMoney = %I64d, BankMoney = %I64d"
					, sendMsg.siVillageUnique, sendMsg.clStockDividendPerson[siIndex].clMoney.itMoney, sendMsg.clStockDividendPerson[siIndex].clAllMoney.itMoney
					);
				sDBLogMsg_QueryString LogMsg("Dividend ResidentsDividend StockHolder", 0, sendMsg.clStockDividendPerson[siIndex].siPersonID, NULL, log);
				SendLogMsg((sPacketHeader *)&LogMsg);
			}
			siIndex++;
		END_FETCHDATA()
	END_NEXTRECORDSET()

	siIndex = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			if(siIndex >= MAX_DIVIDEND_PERSON) break;
			m_odbc.GetData( &sendMsg.clResidentDividendPerson[siIndex].siPersonID);
			m_odbc.GetData( &sendMsg.clResidentDividendPerson[siIndex].clMoney.itMoney);
			m_odbc.GetData( &sendMsg.clResidentDividendPerson[siIndex].clAllMoney.itMoney);
			// �α� �ۼ�
			if(sendMsg.siResult == 1)
			{
				char log[512] = "";
				sprintf(log, "VillageUnique = %d, DividendMoney = %I64d, BankMoney = %I64d"
					, sendMsg.siVillageUnique, sendMsg.clResidentDividendPerson[siIndex].clMoney.itMoney, sendMsg.clResidentDividendPerson[siIndex].clAllMoney.itMoney
					);
				sDBLogMsg_QueryString LogMsg("Dividend Residents", 0, sendMsg.clResidentDividendPerson[siIndex].siPersonID, NULL, log);
				SendLogMsg((sPacketHeader *)&LogMsg);
			}
			siIndex++;
		END_FETCHDATA()
	END_NEXTRECORDSET()

	sendMsg.usYear = pRecvMsg->usYear;
	sendMsg.clDate.Set(&pRecvMsg->clDate);
	sendMsg.siKingPayPersent = pRecvMsg->siKingPayPersent;

	// send
	SendPacket( (BYTE *)&sendMsg );
}


void DBGameProtocol::GiveVillageItem()
{
	// ���� ��Ŷ
	sDBRequest_GiveVillageItem *pRecvMsg	= (sDBRequest_GiveVillageItem *)m_pPacket;

	// PCK : �α׿� ���� ��Ŷ �ۼ�
	sDBResponse_GiveVillageItem sendMsg;

	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_GIVEVILLAGEITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.siVillageUnique		= pRecvMsg->siVillageUnique;
	sendMsg.siUseDate			= pRecvMsg->siUseDate;
	
	sendMsg.clItem.Set( &pRecvMsg->clItem);	
	MStrCpy(sendMsg.szMsg, pRecvMsg->szMsg, sizeof(sendMsg.szMsg));

	// ���� ��Ŷ
//	sDBReponse_Notify_Cityhall_Bankruptcy sendMsg;

//	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GIVEVILLAGEITEM;
//	sendMsg.packetHeader.usSize = sizeof( sendMsg );
//	sendMsg.usCharID = pRecvMsg->usCharID;

	SI32 siResult = 0;
	SI32 siSendCount = 0;

	// DB Query
	BEGIN_SP( "rsp_VillageGiveItem" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMsg, sizeof(pRecvMsg->szMsg) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult );
		m_odbc.GetData( &siSendCount );
	END_FETCHDATA()

	// send
	//	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, SendPersonNum = %d"
			, pRecvMsg->siVillageUnique, siSendCount
			);
		sDBLogMsg_QueryString LogMsg("Village Give Item", 0, NULL, pRecvMsg->clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}


void DBGameProtocol::DonateVillageMoney()
{
	// ���� ��Ŷ
	sDBRequest_DonateVillageMoney *pRecvMsg	= (sDBRequest_DonateVillageMoney *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_DonateVillageMoney sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_DONATEVILLAGEMONEY;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.siCharID = pRecvMsg->siCharID;

	// DB Query
	BEGIN_SP( "rsp_CityhallDonateMoney" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siDonateDate, sizeof(pRecvMsg->siDonateDate) );
		m_odbc.SetParam( SQL_BIGINT, &pRecvMsg->siDonateMoney, sizeof(pRecvMsg->siDonateMoney) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult );
		m_odbc.GetData( &sendMsg.siPersonID );
		m_odbc.GetData( &sendMsg.siVillageUnique );
		m_odbc.GetData( &sendMsg.siDonateDate );
		m_odbc.GetData( &sendMsg.siDonateMoney );
		m_odbc.GetData( sendMsg.szDonateName, sizeof(sendMsg.szDonateName) );
		m_odbc.GetData( &sendMsg.siChangedVillageProfitMoney );
		m_odbc.GetData( &sendMsg.siChangedMyMoney );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, DonateMoney = %I64d, LeftMoney = %I64d, CityhallProfitMoney = %I64d, DonateDate = %d"
			, sendMsg.siVillageUnique, sendMsg.siDonateMoney, sendMsg.siChangedMyMoney, sendMsg.siChangedVillageProfitMoney, sendMsg.siDonateDate
			);
		sDBLogMsg_QueryString LogMsg("Donate Village Money", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}


void DBGameProtocol::DonateMemberList()
{
	// ���� ��Ŷ
	sDBRequest_DonateMemberList *pRecvMsg	= (sDBRequest_DonateMemberList *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_DonateMemberList sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_DONATEMEMBERLIST;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.siCharID = pRecvMsg->siCharID;

	SI32 siMAX_DONATEMEMBERLIST_PER_PAGE = MAX_DONATEMEMBERLIST_PER_PAGE;

	// DB Query
	BEGIN_SP( "rsp_CityhallDonateMMemberList" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siRequestPage, sizeof(pRecvMsg->siRequestPage) );
		m_odbc.SetParam( SQL_INTEGER, &siMAX_DONATEMEMBERLIST_PER_PAGE, sizeof(siMAX_DONATEMEMBERLIST_PER_PAGE) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult );
		m_odbc.GetData( &sendMsg.siVillageUnique );
		m_odbc.GetData( &sendMsg.siRequestPage );
		m_odbc.GetData( &sendMsg.siMaxPage );
	END_FETCHDATA()

	SI32 siIndex = 0;
	BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
			if(siIndex >= MAX_DONATEMEMBERLIST_PER_PAGE) break;
			m_odbc.GetData( sendMsg.sDonateMemberList[siIndex].szDonateName, sizeof(sendMsg.sDonateMemberList[siIndex].szDonateName) );
			m_odbc.GetData( &sendMsg.sDonateMemberList[siIndex].siDonateDate );
			m_odbc.GetData( &sendMsg.sDonateMemberList[siIndex++].siDonateMoney );
		END_FETCHDATA()
	END_NEXTRECORDSET()

	// send
	SendPacket( (BYTE *)&sendMsg );
}
