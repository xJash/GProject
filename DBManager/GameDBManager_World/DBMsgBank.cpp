#include "DBGameProtocol.h"
#include "DBMsg-Structure.h"
#include "DBMsg-Bank.h"

void DBGameProtocol::GetBankStrInfo()
{
	// ���� ��Ŷ
	sDBRequest_GetStrInfo *pRecvMsg = (sDBRequest_GetStrInfo *)m_pPacket;

	SendBankStrInfo(pRecvMsg->siVillageUnique, pRecvMsg->usCharID);
}

void DBGameProtocol::SendBankStrInfo(SI32 siVillageUnique, UI16 usCharID)
{
	// ���� ��Ŷ
	sDBRequest_GetStrInfo *pRecvMsg = (sDBRequest_GetStrInfo *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_GetStrInfo sendMsg;
	sendMsg.clStrInfo.clCommonInfo.siStrType = RANKTYPE_BANK;
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GETSTRINFO;
	sendMsg.packetHeader.usSize = sendMsg.GetTotalSize();
	sendMsg.usCharID = usCharID;


	// DB Query
	SI32 siFeeRate;
	GMONEY siMinFee, siMaxFee;

	BEGIN_SP( "rsp_BankInfoGet" )
		m_odbc.SetParam( SQL_INTEGER, &siVillageUnique, sizeof(siVillageUnique) );
	END_SP()

		EXEC_SQL()

		siFeeRate = 0;
	siMinFee = siMaxFee = 0;

	BEGIN_FETCHDATA()
		m_odbc.GetData( &(sendMsg.siResult), 0);
		m_odbc.GetData( &(sendMsg.siVillageUnique), 0);
		m_odbc.GetData( &siFeeRate, 0);	sendMsg.clStrInfo.clBankStrInfo.clFee.SetFeeRate(siFeeRate);
		m_odbc.GetData( &siMinFee, 0);		sendMsg.clStrInfo.clBankStrInfo.clFee.SetMinFee(siMinFee);
		m_odbc.GetData( &siMaxFee, 0);		sendMsg.clStrInfo.clBankStrInfo.clFee.SetMaxFee(siMaxFee);
		m_odbc.GetData( &(sendMsg.clStrInfo.clBankStrInfo.clMaxMoney.itMoney), 0);
		m_odbc.GetData( &(sendMsg.clStrInfo.clBankStrInfo.clTotalInputMoney.itMoney), 0);
		m_odbc.GetData( &(sendMsg.clStrInfo.clCommonInfo.clMoney.itMoney), 0);
		m_odbc.GetData( (sendMsg.clStrInfo.clCommonInfo.strNotice), sizeof(sendMsg.clStrInfo.clCommonInfo.strNotice) );
	END_FETCHDATA()

		/* �ǹ� �⺻���� */
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

	// ���������� ��´�.
	GetTaxList( &sendMsg.clStrInfo.clCommonInfo.clTaxInfo, sendMsg.siVillageUnique, sendMsg.clStrInfo.clCommonInfo.siStrType );

	// send
	SendPacket( (BYTE *)&sendMsg );
}


void DBGameProtocol::InputMoneyToBank()
{
	// ���� ��Ŷ
	sDBRequest_InputMoneyToBank *pRecvMsg = (sDBRequest_InputMoneyToBank *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_InputMoneyToBank sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_INPUTMONEYTOBANK;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	//[�߰� : Ȳ���� 2007. 10. 29 �α׿� ����� �Աݾװ� ������ ����.]
	sendMsg.clInputMoney.itMoney = pRecvMsg->clMoney.itMoney;
	sendMsg.siFee				 = pRecvMsg->siFee;


	// DB Query
	BEGIN_SP( "rsp_BankMoneyInput" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siPersonID), sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clMoney.itMoney), sizeof(pRecvMsg->clMoney.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->siFee), sizeof(pRecvMsg->siFee) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0);
		GetBankAccount( &sendMsg.clBankAccount);
		m_odbc.GetData( &sendMsg.clMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clTotalInputMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clCurrentLeftMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.siByBankVillageUnique, 0);
		m_odbc.GetData( &sendMsg.clByBankTotalInputMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clByBankCurrentLeftMoney.itMoney, 0);
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// ����� ���������� ������.
	SendBankStrInfo(pRecvMsg->siVillageUnique, pRecvMsg->usCharID);

	// �α׸� �ۼ��Ѵ�.
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "InputMoney = %I64d, LeftBankMoney = %I64d, LeftPersonMoney = %I64d, Fee = %I64d"
				, pRecvMsg->clMoney.itMoney, sendMsg.clBankAccount.GetMoney(), sendMsg.clMoney.itMoney, pRecvMsg->siFee
				);
		sDBLogMsg_QueryString LogMsg("Input Bankmoney", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}


void DBGameProtocol::OutputMoneyFromBank()
{
	// ���� ��Ŷ
	sDBRequest_OutputMoneyFromBank *pRecvMsg = (sDBRequest_OutputMoneyFromBank *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_OutputMoneyFromBank sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_OUTPUTMONEYFROMBANK;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	//[�߰� : Ȳ���� 2007. 10. 29 �α׿� ����� ��ݾװ� ������ ����.]
	sendMsg.clOutputMoney.itMoney = pRecvMsg->clMoney.itMoney;
	sendMsg.siFee				  = pRecvMsg->siFee;


	// DB Query
	BEGIN_SP( "rsp_BankMoneyOutput" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siPersonID), sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clMoney.itMoney), sizeof(pRecvMsg->clMoney.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->siFee), sizeof(pRecvMsg->siFee) );
	END_SP()
	
	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0);
		GetBankAccount( &sendMsg.clBankAccount);
		m_odbc.GetData( &sendMsg.clMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clTotalInputMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clCurrentLeftMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.siByBankVillageUnique, 0);
		m_odbc.GetData( &sendMsg.clByBankTotalInputMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.clByBankCurrentLeftMoney.itMoney, 0);
		m_odbc.GetData( &sendMsg.bCancelStockOrder, 0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// ����� ���������� ������.
	SendBankStrInfo(pRecvMsg->siVillageUnique, pRecvMsg->usCharID);

	// �α׸� �ۼ��Ѵ�.
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "OutputMoney = %I64d, LeftBankMoney = %I64d, LeftPersonMoney = %I64d, Fee = %I64d, CancelStockOrder = %d"
				, pRecvMsg->clMoney.itMoney, sendMsg.clBankAccount.GetMoney(), sendMsg.clMoney.itMoney, pRecvMsg->siFee, sendMsg.bCancelStockOrder
				);
		sDBLogMsg_QueryString LogMsg("Output Bankmoney", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}


void DBGameProtocol::SetBankInfo()
{
	// ���� ��Ŷ
	sDBRequest_SetStrInfo *pRecvMsg = (sDBRequest_SetStrInfo *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_SetStrInfo sendMsg;

	sendMsg.clStrInfo.clCommonInfo.siStrType= RANKTYPE_BANK;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_SETSTRINFO;
	sendMsg.packetHeader.usSize = sendMsg.GetTotalSize();
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	// DB Query
	SI32 siFeeRate	= pRecvMsg->clStrInfo.clBankStrInfo.clFee.GetFeeRate();
	GMONEY siMinFee	= pRecvMsg->clStrInfo.clBankStrInfo.clFee.GetMinFee();
	GMONEY siMaxFee	= pRecvMsg->clStrInfo.clBankStrInfo.clFee.GetMaxFee();
	
	BEGIN_SP( "rsp_BankInfoSet" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siVillageUnique), sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &siFeeRate, sizeof(siFeeRate) );
		m_odbc.SetParam( SQL_BIGINT, &siMinFee, sizeof(siMinFee) );
		m_odbc.SetParam( SQL_BIGINT, &siMaxFee, sizeof(siMaxFee) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clStrInfo.clBankStrInfo.clMaxMoney.itMoney), sizeof(pRecvMsg->clStrInfo.clBankStrInfo.clMaxMoney.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clStrInfo.clBankStrInfo.clTotalInputMoney.itMoney), sizeof(pRecvMsg->clStrInfo.clBankStrInfo.clTotalInputMoney.itMoney) );
		m_odbc.SetParam( SQL_BIGINT, &(pRecvMsg->clStrInfo.clCommonInfo.clMoney.itMoney), sizeof(pRecvMsg->clStrInfo.clCommonInfo.clMoney.itMoney) );
	END_SP()
	
	EXEC_SQL()
	
	siFeeRate = 0;
	siMinFee = siMaxFee = 0;
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &(sendMsg.siResult), 0);
		m_odbc.GetData( &(sendMsg.siVillageUnique), 0);
		m_odbc.GetData( &siFeeRate, 0);	sendMsg.clStrInfo.clBankStrInfo.clFee.SetFeeRate(siFeeRate);
		m_odbc.GetData( &siMinFee, 0);		sendMsg.clStrInfo.clBankStrInfo.clFee.SetMinFee(siMinFee);
		m_odbc.GetData( &siMaxFee, 0);		sendMsg.clStrInfo.clBankStrInfo.clFee.SetMaxFee(siMaxFee);
		m_odbc.GetData( &(sendMsg.clStrInfo.clBankStrInfo.clMaxMoney.itMoney), 0);
		m_odbc.GetData( &(sendMsg.clStrInfo.clBankStrInfo.clMaxMoney.itMoney), 0);
		m_odbc.GetData( &(sendMsg.clStrInfo.clCommonInfo.clMoney.itMoney), 0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α׸� �ۼ��Ѵ�.
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, FeeRate = %d, MinFee = %I64d, MaxFee = %I64d, TotalInputMoney = %I64d, CurrentLeftMoney = %I64d"
				, sendMsg.siVillageUnique, siFeeRate, siMinFee, siMaxFee, sendMsg.clStrInfo.clBankStrInfo.clMaxMoney.itMoney, sendMsg.clStrInfo.clCommonInfo.clMoney.itMoney );
		sDBLogMsg_QueryString LogMsg("Set BankInfo", NULL, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::SetBankFee()
{
	// ���� ��Ŷ
	sDBRequest_SetBankFee *pRecvMsg = (sDBRequest_SetBankFee *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_SetBankFee sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_SETBANKFEE;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	// DB Query
	SI32 siFeeRate	= pRecvMsg->clFee.GetFeeRate();
	GMONEY siMinFee	= pRecvMsg->clFee.GetMinFee();
	GMONEY siMaxFee	= pRecvMsg->clFee.GetMaxFee();
	
	BEGIN_SP( "rsp_BankFeeSet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
		m_odbc.SetParam( SQL_INTEGER, &siFeeRate, sizeof(siFeeRate) );
		m_odbc.SetParam( SQL_BIGINT, &siMinFee, sizeof(siMinFee) );
		m_odbc.SetParam( SQL_BIGINT, &siMaxFee, sizeof(siMaxFee) );
	END_SP()
	
	EXEC_SQL()
	
	siFeeRate = 0;
	siMinFee = siMaxFee = 0;
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0);
		m_odbc.GetData( &sendMsg.siPersonID, 0);
		m_odbc.GetData( &sendMsg.siVillageUnique, 0);
		m_odbc.GetData( &siFeeRate, 0);		sendMsg.clFee.SetFeeRate(siFeeRate);
		m_odbc.GetData( &siMinFee, 0);		sendMsg.clFee.SetMinFee(siMinFee);
		m_odbc.GetData( &siMaxFee, 0);		sendMsg.clFee.SetMaxFee(siMaxFee);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α׸� �ۼ��Ѵ�.
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d, FeeRate = %d, MinFee = %I64d, MaxFee = %I64d", sendMsg.siVillageUnique, siFeeRate, siMinFee, siMaxFee );
		sDBLogMsg_QueryString LogMsg("Set Bankfee", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

/*/////////////////////////////////////////////////////////////////////////////
	������ ���¸� �����. ������ ���� ������ �����ش�.
/////////////////////////////////////////////////////////////////////////////*/
void DBGameProtocol::CreateBankAccount()
{
	// ���� ��Ŷ
	sDBRequest_CreateBankAccount *pRecvMsg = (sDBRequest_CreateBankAccount *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_CreateBankAccount sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CREATEBANKACCOUNT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;


	// DB Query
	BEGIN_SP( "rsp_BankAccountCreate" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
	END_SP()
	
	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0);
		GetBankAccount( &sendMsg.clBankAccount);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α׸� �ۼ��Ѵ�.
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "VillageUnique = %d"
			, pRecvMsg->siVillageUnique
			);
		sDBLogMsg_QueryString LogMsg("Create BankAccount", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

/*/////////////////////////////////////////////////////////////////////////////
	������ ���¸� �����Ѵ�.
/////////////////////////////////////////////////////////////////////////////*/
void DBGameProtocol::CloseBankAccount()
{
	// ���� ��Ŷ
	sDBRequest_CloseBankAccount *pRecvMsg = (sDBRequest_CloseBankAccount *)m_pPacket;
	
	// ���� ��Ŷ
	sDBResponse_CloseBankAccount sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CLOSEBANKACCOUNT;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	// [�߰� : Ȳ���� 2007. 10. 29 ���������� �α׸� ���� ���� ������ ���� �߰�.]
	sendMsg.siVillageUnique = pRecvMsg->siVillageUnique;

	// DB Query
	BEGIN_SP( "rsp_BankAccountClose" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siVillageUnique, sizeof(pRecvMsg->siVillageUnique) );
	END_SP()
	
	EXEC_SQL()
	
	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0);
		GetBankAccount( &sendMsg.clBankAccount);
		m_odbc.GetData( &sendMsg.siMoney, 0);
	END_FETCHDATA()
	
	// send
	SendPacket( (BYTE *)&sendMsg );
	// �α׸� �ۼ��Ѵ�.

	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "Money = %I64d", sendMsg.siMoney );
		sDBLogMsg_QueryString LogMsg("Close BankAccount", pRecvMsg->siPersonID, NULL, NULL, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}