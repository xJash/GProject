#include "DBGameProtocol.h"
#include "DBMsg-ItemMall.h"
#include "BillInterfaces.h"
#include "BillManager_Germany.h"
#include "BillManager_nDoors_Korea.h"

//const char* szServerIP = "222.122.40.29";
const char* szServerIP = "10.10.30.32";
const char* szServerPort = "50050";

// �Ѱ��� ���� ���� - ���� ���
extern SI32					g_BillingMode;

//KHY - 0304 - �߱� NHNChinaBilling - 
#ifdef USE_NHNCHINABILLING
	#include "./NHNChinaBilling/NHNChinaBilling.h"

	using namespace NHNChinaBilling;
	using namespace NHNChinaUtil;
	//using namespace Porte::PorteAuthSystem;
#endif



extern char		g_szServiceArea[12];
extern char		g_szServiceMode[8];

void DBGameProtocol::ItemMallExistence()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallExistence *pRecvMsg = (sDBRequest_ItemMallExistence *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallExistence sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLEXISTENCE;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallExistence" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	m_odbc.GetData( &sendMsg.siPersonID, 0 );
	m_odbc.GetData( &siExistence, 0 );
	END_FETCHDATA()

		sendMsg.bExistence = (siExistence == 1) ? true : false;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallItemList()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallItemList *pRecvMsg = (sDBRequest_ItemMallItemList *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallItemList sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLITEMLIST;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	char szTotalRecord[11]; ZeroMemory(szTotalRecord, sizeof(szTotalRecord));
	char szItemName[51]; ZeroMemory(szItemName, sizeof(szItemName));
	SI32 siItemCount = 0;
	SI32 siItemNum = 0;
	SI32 siReceiptNum = 0;
	SI32 siOrderCount = 0;



	/*
	�Է� ���� : @PersonID, @ListPage
		���� ����:	total_record -- varchar(10) // �� 100����� '100'���� �� ����.
		item_seq -- INT				// ���Ź�ȣ
		item_unique -- SMALLINT		// ����������
		item_num -- SMALLINT		// �� ���ż���
		item_name -- VARCHAR(50)	// ���Ӽ����� ������ �ʿ� ����
		receipt_num -- SMALLINT		// �̹� ������ ����
		order_count -- SMALLINT		// ����Ƚ��

		���� �����ۼ����� item_num * order_count - receipt_num ��.
		*/
		// DB Query
	BEGIN_SP( "rsp_ItemMallItemList" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siMaxListItemNum, sizeof(pRecvMsg->siMaxListItemNum) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siListPage, sizeof(pRecvMsg->siListPage) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		if(siItemCount >= MAX_ITEMNUM_PER_ITEMMALL)
			continue;

		m_odbc.GetData( &sendMsg.siTotalItemNum , 0 );
		m_odbc.GetData( &sendMsg.siItemID[siItemCount], 0 );
		m_odbc.GetData( &sendMsg.clItem[siItemCount].siUnique, 0 );
		m_odbc.GetData( &siItemNum, 0 );
		m_odbc.GetData( szItemName, sizeof(szItemName) );
		m_odbc.GetData( &siReceiptNum, 0 );
		m_odbc.GetData( &sendMsg.clItem[siItemCount].uiDateUseDay, 0 );

		sendMsg.clItem[siItemCount].siItemNum = siItemNum - siReceiptNum;
		siItemCount++;
	END_FETCHDATA()

	sendMsg.siResult = (siItemCount > 0) ? 1 : 0;
	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siListPage = pRecvMsg->siListPage;



	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallGetItem()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem *pRecvMsg = (sDBRequest_ItemMallGetItem *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &(pRecvMsg->bCreateSID),	sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

		// send
		SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "Success : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::NewsChatAdmission()
{
	// ���� ��Ŷ
	sDBRequest_NewsChatAddmission *pRecvMsg = (sDBRequest_NewsChatAddmission *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_NewsChatAddmission sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_NEWSCHATADDMISSION;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bUseColorNews = pRecvMsg->bUseColorNews;

	// DB Query
	BEGIN_SP( "rsp_PersonItemNewsChatAdmission" )
		m_odbc.SetParam( SQL_INTEGER, &(pRecvMsg->siPersonID),			sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_SMALLINT, &(pRecvMsg->siInvPos),			sizeof(pRecvMsg->siInvPos) );
	SetItemParam( &pRecvMsg->clItem );
	END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	m_odbc.GetData( &sendMsg.siPersonID, 0 );
	m_odbc.GetData( &sendMsg.siInvPos, 0 );
	GetItemData( &sendMsg.clItem );
	END_FETCHDATA()

		memcpy(sendMsg.szChatText, pRecvMsg->szChatText, sizeof(sendMsg.szChatText));

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "ItemPos = %d, Amount = %d, LeftItemNum = %d, %s"
			, pRecvMsg->siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, pRecvMsg->szChatText
			);
		sDBLogMsg_QueryString LogMsg( "NewsChat Admission", sendMsg.siPersonID, NULL, pRecvMsg->clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::NoLimitTicketWarp()
{
	// ���� ��Ŷ
	sDBRequest_NoLimitTicket_Warp *pRecvMsg = (sDBRequest_NoLimitTicket_Warp *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_NoLimitTicket_Warp sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_NOLIMITTICKET_WARP;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_TicketService" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siType, sizeof(pRecvMsg->siType) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bUsing, sizeof(pRecvMsg->bUsing) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siDateVary, sizeof(pRecvMsg->siDateVary) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		SetItemParam( &pRecvMsg->clItem );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siType, 0 );
		m_odbc.GetData( &sendMsg.bUsing, 0 );
		m_odbc.GetData( &sendMsg.siDateVary, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		GetItemData( &sendMsg.clItem );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Type = %d, Using = %d, DataVary = %d, InvPos = %d"
		, pRecvMsg->siType, pRecvMsg->bUsing, pRecvMsg->siDateVary, pRecvMsg->siInvPos
		);
	sDBLogMsg_QueryString LogMsg("Ticket Service", pRecvMsg->siPersonID, NULL, pRecvMsg->clItem.siUnique, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::CheckAccountID()
{
	// ���� ��Ŷ
	sDBRequest_Check_AccountID *pRecvMsg = (sDBRequest_Check_AccountID *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Check_AccountID sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_CHECK_ACCOUNTID;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ItemMallCheckAccountID" )
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siServerUnique, sizeof(pRecvMsg->siServerUnique) );
		m_odbc.SetParam( SQL_VARCHAR,   pRecvMsg->szCharName,     sizeof(pRecvMsg->szCharName) );
	END_SP()

		EXEC_SQL()

		char szUserName[MAX_PLAYER_NAME] = "";
	char szNickName[MAX_PLAYER_NAME] = "";
	SI32 siAuth = 0;

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( sendMsg.szAccountID, sizeof(sendMsg.szAccountID) );
	END_FETCHDATA()

	sendMsg.siPersonID		= pRecvMsg->siPersonID;
	sendMsg.siServerUnique	= pRecvMsg->siServerUnique;
	memcpy(sendMsg.szCharName,		pRecvMsg->szCharName,	sizeof(sendMsg.szCharName) );
	memcpy(sendMsg.szAccountName,	sendMsg.szAccountID,	sizeof(sendMsg.szAccountName) );

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallGiftItem()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem *pRecvMsg = (sDBRequest_ItemMall_Giftitem *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	// DB Query
	BEGIN_SP( "rsp_ItemMallGIftItem" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
	m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
	m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
	m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
	m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
	m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
	m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
	m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
	m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
	m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
	END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
	END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
	sendMsg.siEventCash = siEventMoney;

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallBuyItem()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem *pRecvMsg = (sDBRequest_ItemMall_Buyitem *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;

	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	// DB Query
	BEGIN_SP( "rsp_ItemMallBuyItem" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
	END_FETCHDATA()

	sendMsg.siCash = siRealMoney + siBonusMoney;
	sendMsg.siEventCash = siEventMoney;

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallItemInfo()
{
	// ���� ��Ŷ
	sDBRequest_Get_ItemMall_ItemInfo *pRecvMsg = (sDBRequest_Get_ItemMall_ItemInfo *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Get_ItemMall_ItemInfo sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_ITEMMALL_ITEMINFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ItemMallItemInfo" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siGroupKey, sizeof(pRecvMsg->siGroupKey) );
	END_SP()

		EXEC_SQL()

		SI32 siCount = 0;
	BEGIN_FETCHDATA()
		if(siCount >= 3) continue;
	GetItemMallDateItemInfo( &sendMsg.clItemData[siCount] );
	siCount++;
	END_FETCHDATA()

		sendMsg.siResult = 1;
	sendMsg.siPersonID = pRecvMsg->siPersonID;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallSelPGList()
{
	// ���� ��Ŷ
	sDBRequest_Get_Sel_PGList *pRecvMsg = (sDBRequest_Get_Sel_PGList *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_Get_Sel_PGList sendMsg;


	sendMsg.packetHeader.usCmd  = DBMSG_RESPONSE_GET_SEL_PGLIST;
	sendMsg.packetHeader.usSize = sizeof(sendMsg);
	sendMsg.usCharID			= pRecvMsg->usCharID;

	sendMsg.siPersonID			= pRecvMsg->siPersonID;
	sendMsg.siMainCategory		= pRecvMsg->siMainCategory;
	sendMsg.siSubCategory		= pRecvMsg->siSubCategory;
	memcpy( sendMsg.szType, pRecvMsg->szType, sizeof(sendMsg.szType) );
	sendMsg.siPage				= pRecvMsg->siPage;

	// DB Query
	BEGIN_SP( "rsp_ItemMallPGList_Main" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,			sizeof(pRecvMsg->siPersonID)		 );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siMainCategory,		sizeof(pRecvMsg->siMainCategory)	 );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siSubCategory,			sizeof(pRecvMsg->siSubCategory)		 );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szType,					sizeof(pRecvMsg->szType)			 );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPage,				sizeof(pRecvMsg->siPage)			 );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->siAllowGrownUpItem,	sizeof(pRecvMsg->siAllowGrownUpItem) );
	END_SP()
	
	EXEC_SQL()
		SI32 siMaxRowcount	= 0;
		SI32 siCurRowcount	= 0;
	BEGIN_FETCHDATA()
		m_odbc.GetData( &siMaxRowcount, 0 );
		GetItemMallListData( &sendMsg.clListData[siCurRowcount] );
		siCurRowcount++;
	END_FETCHDATA()
	
	sendMsg.siResult = 1;

	if(siMaxRowcount > 0) siMaxRowcount -= 1; // ��Ȯ�� ���������� ���ϱ� ���� �ϳ��� ���� ������.

	sendMsg.siMaxPage = siMaxRowcount / 6 + 1;	// �� �������� 6���� �����Ǿ�����.



	for( int j = 0; j < MAX_ITEMMALL_LIST_NUM; j++)
	{
		if(sendMsg.clListData[j].siProductKey > 0)
		{
			BEGIN_SP( "rsp_ItemMallPGList_Sub" )
				m_odbc.SetParam( SQL_INTEGER, &sendMsg.clListData[j].siProductKey, sizeof(sendMsg.clListData[j].siProductKey) );
			END_SP()

			EXEC_SQL()
				SI32	siCount		= 0;
				SI32	siItemSeq	= 0;	// ���ӿ����� ������� �ʴ´�.
				TCHAR	szItemName[50];
				SI16	siUseDay	= 0;
			BEGIN_FETCHDATA()
				if(siCount > MAX_ITEMMALL_SET_NUM) continue;
				m_odbc.GetData( &siItemSeq,										0 );
				m_odbc.GetData( &sendMsg.clItemData[j].siUnique[siCount],		0 );
				m_odbc.GetData( &sendMsg.clItemData[j].siItemNum[siCount],		0 );
				m_odbc.GetData( szItemName,										0 );
				m_odbc.GetData( &siUseDay,										0 );
				m_odbc.GetData( &sendMsg.clItemData[j].siLimitLevel[siCount],	0 );
				siCount++;
			END_FETCHDATA()
		}
	}
	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallSellLimitCheck(SI32 siPersonID, SI32 siOrderPrice, bool *pbResult, char *accountid, SI32 siProductKey, SI32 siProductNum)
{
	SI32 siEventMoney = 0;
	SI32 siRet = CBillManager_nDoors_Korea::GetUsePkgCash(accountid, &siEventMoney);

	if(siRet != 0)
	{
		*pbResult = false;
		return;
	}

	siOrderPrice -= siEventMoney;

	if(siOrderPrice < 0)
		siOrderPrice = 0;


	SI32 siLimitCheckResult = -99;
	SI32 siAuthCheckResult	= -99;
	*pbResult = false;

	// �������ѱݾ� �˻�.
	BEGIN_SP( "rsp_ItemMallSelLimitCheck" )
		m_odbc.SetParam( SQL_INTEGER, &siPersonID, sizeof(siPersonID) );
	m_odbc.SetParam( SQL_INTEGER, &siOrderPrice, sizeof(siOrderPrice) );
	m_odbc.SetParam( SQL_INTEGER, &siProductKey, sizeof(siProductKey) );
	m_odbc.SetParam( SQL_INTEGER, &siProductNum, sizeof(siProductNum) );
	END_SP()

		EXEC_SQL()

		SI32 siYear = 0;

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siLimitCheckResult, 0 );
	m_odbc.GetData( &siYear, 0 );
	END_FETCHDATA()

		// ������ ���´�.
		BEGIN_NEXTRECORDSET()
		BEGIN_FETCHDATA()
		m_odbc.GetData( accountid, sizeof(char) * MAX_PLAYER_NAME );
	END_FETCHDATA()
		END_NEXTRECORDSET()

		if(siLimitCheckResult == 0)
		{
			if(siYear >= 19)
			{
				// �����ΰ��
				siAuthCheckResult = 1;
			}
			else
			{
				// �̼��⵿�ǿ��� ��ȸ
				BEGIN_SP( "rsp_ItemMallAuthCheck" )
					m_odbc.SetParam( SQL_INTEGER, &siPersonID, sizeof(siPersonID) );
				END_SP()

					EXEC_SQL()

					BEGIN_FETCHDATA()
					m_odbc.GetData( &siAuthCheckResult, 0 );
				END_FETCHDATA()
			}
		}

		// �� �� �����ؾ���.
		// siLimitCheckResult( 0 ���Ű��� / -1 ���źҰ� / �׿� ���� )
		// siAuthCheckResult( 1 ���� / 0 ������ )
		if(siLimitCheckResult == 0 && siAuthCheckResult == 1)
			*pbResult = true;
}

void DBGameProtocol::ItemMallMyCashInfo()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info *pRecvMsg = (SDBRequest_Get_MyCash_Info *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ItemMallMyCashGet" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
	END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siCash, 0 );
	END_FETCHDATA()

		sendMsg.siResult = 1;
	sendMsg.siEventCash = 0;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

//============================================
// �۷ι������� �����۱���, ���� �޼����ڵ鷯
//============================================
void DBGameProtocol::ItemMallGiftItem_Global()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_Global *pRecvMsg = (sDBRequest_ItemMall_Giftitem_Global *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	long siRealMoney	= 0;
	long siBonusMoney	= 0;
	long siEventMoney	= 0;
	SI32 siResult		= -99;
	long siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	bCheck = ItemMallIPGProcess(pRecvMsg->szMyAccountID, &siTotalPrice, &siRealMoney, &siBonusMoney, &siEventMoney, 
		szTxCode, pRecvMsg->siProductKey, pRecvMsg->szItemName, pRecvMsg->szIP, pRecvMsg->siProductNum);

	if (bCheck == true)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallGIftItemGlobal" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

			sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;
	}
	else
	{
		siResult = -97;
	}

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item_Global", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallBuyItem_Global()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_Global *pRecvMsg = (sDBRequest_ItemMall_Buyitem_Global *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	long siRealMoney	= 0;
	long siBonusMoney	= 0;
	long siEventMoney	= 0;
	SI32 siResult		= -99;
	long siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	long siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
			
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	bCheck = ItemMallIPGProcess(pRecvMsg->szMyAccountID, &siTotalPrice, &siRealMoney, &siBonusMoney, &siEventMoney, 
		szTxCode, pRecvMsg->siProductKey, pRecvMsg->szItemName, pRecvMsg->szIP, pRecvMsg->siProductNum);

	if (bCheck == true)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallBuyItemGlobal" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

			sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;
	}
	else
	{
		siResult = -97;
	}


	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item_Global", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallMyCashInfo_Global()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_Global *pRecvMsg = (SDBRequest_Get_MyCash_Info_Global *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	long siRealMoney	= 0;
	long siBonusMoney	= 0;
	long siEventMoney	= 0;
	long siEtcMoney		= 0;

	bool bCheck			= false;

	bCheck = ItemMallIPGCashInfo(pRecvMsg->szMyAccountID, &siRealMoney, &siBonusMoney, &siEventMoney );

	if (bCheck)
	{
		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		sendMsg.siResult = 1;
	}
	else
	{
		sendMsg.siResult = -1;
	}

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallGetItem_Global()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_Global *pRecvMsg = (sDBRequest_ItemMallGetItem_Global *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItemGlobal" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

bool DBGameProtocol::ItemMallIPGProcess(char *accountid, long *price, long *realmoney, long *bonusmoney, long *eventmoney, char *txcode, SI32 ProductKey, char *ProductName, char *UserIP, SI32 ProductNum)
{
	long siEtcMoney			= 0;
	long siLeftMoney		= *price;
	long siUseRealMoney		= 0;
	long siUseBonusMoney	= 0;
	long siUseEventMoney	= 0;

	SI32 siRet				= -1;

	char szCode[50]			= "" ;

	if( _tcscmp(g_szServiceMode, "DEBUG") == 0 ||
		_tcscmp(g_szServiceMode, "TEST") == 0 )
	{
		return true;
	}

	char	szBillServer[128];
	sprintf(szBillServer, "%s:%s;%s:%s", szServerIP, szServerPort, szServerIP, szServerPort);

	siRet = BillInterfaces::GetUserBalance(
		szBillServer, 
		accountid, 
		realmoney, 
		bonusmoney, 
		eventmoney);

	// �ܾ���ȸ ����
	if (siRet != 0)
	{
		return false;
	}

	// ����+���� ������ ���ž׺��� ������ ����
	if(*price > (*realmoney + *bonusmoney) )
		return false;

	char szProductKey[128];
	sprintf(szProductKey, "%d", ProductKey);

	sprintf(szBillServer, "%s:%s;%s:%s", szServerIP, szServerPort, szServerIP, szServerPort);

	siRet = BillInterfaces::ChargeItem
		(
		szBillServer,		// [IN]
		accountid,			// [IN]
		szProductKey,		// [IN]
		ProductName,		// [IN] 
		UserIP,				// [IN] UserIP (���� : PCK - "111.111.111.111"�� �Ǿ��ִ°��� szUserIP�� ���� (08.12.23)
		*price,				// [IN]
		1,					// [IN] ItemPiece�� 1�� ����
		ProductNum,			// [IN] ������ �����۰���
		1,					// [IN] 1:�Ϲݱ���, 2:����
		1,					// [IN] ������ ���� CP(1:����,2:��Ʋ��Ƽī)

		&siUseRealMoney,	// [OUT] ������ Real ĳ�� �ܾ�
		&siUseBonusMoney,	// [OUT] ������ Bonus ĳ�� �ܾ�
		&siUseEventMoney,	// [OUT] ������ Mileage �ܾ�
		szCode				// [OUT] ���ݹ�ȣ(19 Bytes) (����Ҷ� �ʿ���.)
		);

	if (siRet != 0)
		return false;


	*realmoney	= siUseRealMoney;
	*bonusmoney	= siUseBonusMoney;
	*eventmoney	= siUseEventMoney;

	strcpy(txcode,szCode);

	return true;

}

bool DBGameProtocol::ItemMallIPGCashInfo(char *accountid, long *realmoney, long *bonusmoney, long *eventmoney)
{
	SI32 siRet				= -1;
	char	szBillServer[128];
	sprintf(szBillServer, "%s:%s;%s:%s", szServerIP, szServerPort, szServerIP, szServerPort);

	if( _tcscmp(g_szServiceMode, "DEBUG") == 0 ||
		_tcscmp(g_szServiceMode, "TEST") == 0 )
	{
		*realmoney = 2000;
		*bonusmoney = 0;
		*eventmoney = 0;
		return true;
	}

	siRet = BillInterfaces::GetUserBalance(
		szBillServer, 
		accountid, 
		realmoney, 
		bonusmoney, 
		eventmoney);

	// �ܾ���ȸ ����
	if (siRet != 0)
	{
		return false;
	}

	return true;
}

//============================================

void DBGameProtocol::ItemMallMyCashInfo_China()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_China *pRecvMsg = (SDBRequest_Get_MyCash_Info_China *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_ItemMallMyCashGet_China" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siCash, 0 );
		m_odbc.GetData( &sendMsg.siEventCash, 0 );
	END_FETCHDATA()

	sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallGiftItem_China()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_China *pRecvMsg = (sDBRequest_ItemMall_Giftitem_China *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}

	// DB Query
	BEGIN_SP( "rsp_ItemMallGIftItem_China" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szSecondPassWord, sizeof(pRecvMsg->szSecondPassWord) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetCharName, sizeof(pRecvMsg->szGetCharName) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
		m_odbc.GetData( &sendMsg.siGetItemPersonID, 0 );
	END_FETCHDATA()

	sendMsg.siCash = siRealMoney + siBonusMoney;
	sendMsg.siEventCash = siEventMoney;

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallBuyItem_China()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_China *pRecvMsg = (sDBRequest_ItemMall_Buyitem_China *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->siCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= pRecvMsg->siEventPrice   * pRecvMsg->siProductNum;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,		sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice,	sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siEventPrice,		sizeof(pRecvMsg->siEventPrice) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}

	// DB Query
	BEGIN_SP( "rsp_ItemMallBuyItem_China" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,		sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,		sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID,		sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum,		sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice,				sizeof(siTotalPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney,					sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney,				sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney,				sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode,						sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP,				sizeof(pRecvMsg->szIP) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szSecondPassWord,	sizeof(pRecvMsg->szSecondPassWord) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
	END_FETCHDATA()

	sendMsg.siCash = siRealMoney + siBonusMoney;
	sendMsg.siEventCash = siEventMoney;

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallGetItem_China()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_China *pRecvMsg = (sDBRequest_ItemMallGetItem_China *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_China" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

		// send
		SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}



void DBGameProtocol::ItemMallMyCashInfo_Korea()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_Korea *pRecvMsg = (SDBRequest_Get_MyCash_Info_Korea *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;


	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;
	
	BOOL bSuccess = FALSE;


	if ( g_BillingMode == HANGAME_BILLINGMODE_SOCKET )
		bSuccess = clHangameBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	else if( g_BillingMode == HANGAME_BILLINGMODE_NEVERBILL )
		bSuccess = clHannEverBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );

	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);        
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;
	}

	// ����������쿡�� 0 ������ ��������.
	sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );
}



// [��ȣ_NHN->NDOORS] �ݾ���ȸ
void DBGameProtocol::ItemMallMyCashInfo_nDoors_Korea()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_nDoors_Korea* pRecvMsg = (SDBRequest_Get_MyCash_Info_nDoors_Korea*)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info	sendMsg;
	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID			= pRecvMsg->usCharID;

	// IPG BILLING MODULE �� ���ؼ� �ݾ��� ��ȸ�մϴ�.
	
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siEtcMoney		= 0;

	SI32 siRet			= -1;

	// ����, ���� �ܾ���ȸ
	siRet = CBillManager_nDoors_Korea::GetUserCash(pRecvMsg->szMyAccountID, &siRealMoney, &siBonusMoney, &siEtcMoney);
	if(siRet == 0 )
	{
		// �̺�Ʈ �ܾ���ȸ
		siRet = CBillManager_nDoors_Korea::GetUsePkgCash(pRecvMsg->szMyAccountID, &siEventMoney);
		if(siRet == 0 )
		{
			sendMsg.siResult = 1;
			sendMsg.siCash = siRealMoney + siBonusMoney;
			sendMsg.siEventCash = siEventMoney;
		}
		else
		{
			sendMsg.siResult = -2;
		}
	}
	else
	{
		sendMsg.siResult = -1;
	}


	// ��Ŷ ������
	SendPacket((BYTE*)&sendMsg);
}



void DBGameProtocol::ItemMallBuyItem_nDoors_Korea()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_nDoors_Korea* pRecvMsg = (sDBRequest_ItemMall_Buyitem_nDoors_Korea*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;
	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof(sendMsg);
	sendMsg.usCharID			= pRecvMsg->usCharID;

	// IPG BILLING MODULE �� ���ؼ� ĳ�� ������ �մϴ�.
	char szAccountID[MAX_PLAYER_NAME] = "";
	StringCchCopy(szAccountID, MAX_PLAYER_NAME, pRecvMsg->szMyAccountID);

	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siCheckMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siCheckBuyPrice	= 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,		sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice,	sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siCheckMoney,	sizeof(siCheckMoney) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siCheckBuyPrice, 0 );
	END_FETCHDATA()

		// [��ȣ_NHN->NDOORS] ���� ���� �ѵ� �Ѿ� ����� (����� ���ʰ� ������ �ȵ� �����̹Ƿ� ������ ����)
#ifndef _DEBUG
		if (siCheckBuyPrice != 1)
			return;
#endif


	bool bGiftMoney = false;
	bool bCheck = false;

	// ��ǰ�˻� ( ���������ѱݾ�, �̼��ⱸ�� )
	ItemMallSellLimitCheck(pRecvMsg->siPersonID, siTotalPrice, &bCheck, szAccountID, pRecvMsg->siProductKey, pRecvMsg->siProductNum);

	if(bCheck == true)
		bCheck = BuyItemProcess_Korea(szAccountID, &siTotalPrice, &siRealMoney, &siBonusMoney, &siEventMoney, szTxCode, bGiftMoney );
	else
		siResult = -98;


	// ����ó��(GZITEMMALL)
	if(bCheck == true)
	{
		BEGIN_SP( "rsp_ItemMallBuyItem_Special" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		//sendMsg.siCash = siRealMoney + siBonusMoney;
		//sendMsg.siEventCash = siEventMoney;
	}
	else
	{
		if(siResult != -98)
			siResult = -97;
	}

	if(siResult == 0)
	{
		sendMsg.siResult = 1;

		SI32 siRet = -1;

		// ����, ���� �ܾ���ȸ
		siRet = CBillManager_nDoors_Korea::GetUserCash(pRecvMsg->szMyAccountID, &siRealMoney, &siBonusMoney, &siEventMoney);
		if(siRet == 0 )
		{
			// �̺�Ʈ �ܾ���ȸ
			siRet = CBillManager_nDoors_Korea::GetUsePkgCash(pRecvMsg->szMyAccountID, &siEventMoney);
			if(siRet == 0 )
			{
				sendMsg.siCash = siRealMoney + siBonusMoney;
				sendMsg.siEventCash = siEventMoney;
			}
		}
	}
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;


	// ��Ŷ ������
	SendPacket((BYTE*)&sendMsg);
}


void DBGameProtocol::ItemMallGiftItem_nDoors_Korea()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_nDoors_Korea* pRecvMsg = (sDBRequest_ItemMall_Giftitem_nDoors_Korea*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;
	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID			= pRecvMsg->usCharID;

	char szAccountID[MAX_PLAYER_NAME] = "";
	StringCchCopy(szAccountID, MAX_PLAYER_NAME, pRecvMsg->szMyAccountID);

	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siCheckMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;

	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siCheckMoney,	sizeof(siCheckMoney) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			// [��ȣ_NHN->NDOORS] ���� ���� �ѵ� �Ѿ� ����� (����� ���ʰ� ������ �ȵ� �����̹Ƿ� ������ ����)
#ifndef _DEBUG
			if (siCheckBuyPrice != 1)
				return;
#endif
	}

	// [��ȣ] ������ �̼��⿡�� ������ �õ��ϴ��� üũ
	// DB Query
	SI32 siAge = 0;
	SI32 siAdultProduct = 0;
	BEGIN_SP( "rsp_ItemMallCheckAge" )
		m_odbc.SetParam( SQL_VARCHAR, &pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &siAge, 0);
		m_odbc.GetData( &siAdultProduct, 0);
	END_FETCHDATA()


	bool bGiftMoney = false;
	bool bCheck = false;

	// ���� ���� ����� ���� �ΰ��
	if((siAge >= 18 && siAdultProduct == 1) || (siAdultProduct == 0))
	{
		// ��ǰ�˻� ( ���������ѱݾ�, �̼��ⱸ�� )
		ItemMallSellLimitCheck(pRecvMsg->siPersonID, siTotalPrice, &bCheck, szAccountID, pRecvMsg->siProductKey, pRecvMsg->siProductNum);
	}

	if(bCheck == true)
		bCheck = BuyItemProcess_Korea(szAccountID, &siTotalPrice, &siRealMoney, &siBonusMoney, &siEventMoney, szTxCode, bGiftMoney );
	else
	{
		if(siAge < 18 && siAdultProduct == 1)
			siResult = -95;	// ���̿� �ɸ�
		else
			siResult = -98;	// �������ѿ� �ɸ�.
	}

	// ����ó��(GZITEMMALL)
	if(bCheck == true)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallGIftItem_Special" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

			sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;
	}
	else
	{
		if(siResult != -98 && siResult != -95)
			siResult = -97;
	}

	if(siResult == 0)
	{
		sendMsg.siResult = 1;

		SI32 siRet = -1;

		// ����, ���� �ܾ���ȸ
		siRet = CBillManager_nDoors_Korea::GetUserCash(pRecvMsg->szMyAccountID, &siRealMoney, &siBonusMoney, &siEventMoney);
		if(siRet == 0 )
		{
			// �̺�Ʈ �ܾ���ȸ
			siRet = CBillManager_nDoors_Korea::GetUsePkgCash(pRecvMsg->szMyAccountID, &siEventMoney);
			if(siRet == 0 )
			{
				sendMsg.siCash = siRealMoney + siBonusMoney;
				sendMsg.siEventCash = siEventMoney;
			}
		}
	}
	else
		sendMsg.siResult = siResult;

	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;


	// ��Ŷ ������
	SendPacket((BYTE*)&sendMsg);
}



//KHY - 0304 - �߱� NHNChinaBilling -
void DBGameProtocol::ItemMallMyCashInfo_NHNChina()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_NHNChina *pRecvMsg = (SDBRequest_Get_MyCash_Info_NHNChina *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;


	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	
//KHY - 0304 - �߱� NHNChinaBilling - �ܾ���ȸ
#ifdef USE_NHNCHINABILLING

	SI64 balance1 = 0;  //	  ���� ������
	SI64 balance2 = 0;  //	  ���� ������
	SI64 balance3 = 0;  //	  [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ�.
	char balanceErr[NHNCHINABILLING_MSG_SIZE];

	//NHNChinaBilling::Connection con("purple.billing/sqlmap");
	NHNChinaBilling::Connection con("purple.billing/sqlmap");
	ReturnCode ret;	

	// ����ID�� �޾� ����.
	//ret = GetBalance(con,"C_GZ",pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1,&balance2);	
	
	// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
	ret = GiftBalance(con, "C_GZ", pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1, &balance2, &balance3);	

	if( SUCC == ret )	
	{		
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(balance3+balance2);  // �ϴ� �� �׼��� ������ �ѱ��.      
		
		// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
		//sendMsg.siEventCash = 0;
		sendMsg.siEventCash = (SI32)balance1;
	}
	else
	{
		sendMsg.siCash      = 0;
		sendMsg.siEventCash = 0;
	}
#else
		sendMsg.siCash      = 0;
		sendMsg.siEventCash = 0;
#endif

	// ����������쿡�� 0 ������ ��������.
	sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

//KHY - 0304 - �߱� NHNChinaBilling - 
void DBGameProtocol::ItemMallBuyItem_NHNChina()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_NHNChina *pRecvMsg = (sDBRequest_ItemMall_Buyitem_NHNChina *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]		= "";
	SI32 siRealMoney		= 0;
	SI32 siBonusMoney		= 0;
	SI32 siEventMoney		= 0;
	SI32 siResult			= -99;
	SI32 siTotalPrice		= pRecvMsg->siProductPrice		* pRecvMsg->siProductNum;
	SI32 siEventPrice		= pRecvMsg->siProductEventPrice * pRecvMsg->siProductNum;
	SI32 siCheckBuyPrice	= 0;
	SI32 siBuySeqNum		= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,			sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice,		sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductEventPrice,	sizeof(pRecvMsg->siProductEventPrice) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}
	
	// �ֹ���ȣ ����.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMall_BuySeqGet" )
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siBuySeqNum, 0 );
		END_FETCHDATA()		
	}

	//char logseq[NHNCHINABILLING_LOGSEQ_SIZE];

	SI32 rVal =	ItemMallProductBuyProcess_NHNChina( pRecvMsg->siServerID, // ���� ID
 												  pRecvMsg->szMyAccountID ,
  												  pRecvMsg->szName,
												  pRecvMsg->siProductKey , 
												  siBuySeqNum,  // �ֹ���ȣ
												  pRecvMsg->siProductNum,
												  siTotalPrice ,
												  siEventPrice ,
												  pRecvMsg->szIP,
												  szTxCode
												 );
	if( 1 == rVal )
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallBuyItem_China" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,	sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,	sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID,	sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum,	sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice,			sizeof(siTotalPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney,				sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney,			sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney,			sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode,					sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP,			sizeof(pRecvMsg->szIP) );
			m_odbc.SetParam( SQL_INTEGER, &siBuySeqNum,				sizeof(siBuySeqNum) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()



		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;

		sendMsg.siPersonID = pRecvMsg->siPersonID;
		sendMsg.siProductKey = pRecvMsg->siProductKey;
		memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
		memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
		sendMsg.siProductNum = pRecvMsg->siProductNum;
		sendMsg.siProductPrice = pRecvMsg->siProductPrice;
	}
	else
	{
		siResult = -97;
	}

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;



	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û-----------------------------------------------
	SI64 balance1 = 0;  // ���� ������
	SI64 balance2 = 0;  //	  ���� ������
	SI64 balance3 = 0;  //	  [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ�.

	BOOL bSuccess = FALSE;

//KHY - 0304 - �߱� NHNChinaBilling - �ܾ���ȸ
#ifdef USE_NHNCHINABILLING
	char balanceErr[NHNCHINABILLING_MSG_SIZE];

	NHNChinaBilling::Connection con3("purple.billing/sqlmap");
	ReturnCode ret3;

	// ����ID�� �޾� ����.
	//ret3 = GetBalance(con3,"C_GZ",pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1,&balance2);	
	// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
	ret3 = GiftBalance(con3,"C_GZ",pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1,&balance2, &balance3);	


	if( SUCC == ret3 )	
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(balance3 + balance2);
		
		// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
		//sendMsg.siEventCash = 0;
		sendMsg.siEventCash   = (SI32)balance1;
	}
	else
	{
		sendMsg.siCash      = 0;
		sendMsg.siEventCash = 0;		
	}
#endif

	// Ȯ�� ��------------------------------------------------------------------------------------------------

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}


SI32 DBGameProtocol::ItemMallProductBuyProcess_NHNChina(IN  SI32	siServerID,		  // ����ID
														IN  char*	accountid,		  // ���� ��.
														IN  char*	szName,			  // ĳ���� ��
														IN  SI32	siProductKey,	  // ������ �ڵ�
														IN  SI32	siBuySeqNum,	  // �ֹ���ȣ  - ���ӻ� �ŷ���ȣ
														IN  SI32	siProductNum,	  // ������ ����
														IN  SI32	siPrice,          // �ŷ� �ݾ�  - ��Ż�� ���´�.
														IN  SI32	siEventPrice,     // �ŷ� �ݾ�  - ��Ż�� ���´�.
														IN  char*	szIP,             // Client IP
														OUT char*	logseq
																)
{
	// �ܾ� ��� ����Ȯ��-------------------------------------------------------------------------------------

	SI64 balance1 = 0;  // ���� ������
	SI64 balance2 = 0;  // ���� ������
	SI64 balance3 = 0;  // [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ�.

	BOOL bSuccess = FALSE;

//KHY - 0304 - �߱� NHNChinaBilling - �ܾ���ȸ
#ifdef USE_NHNCHINABILLING
	char balanceErr[NHNCHINABILLING_MSG_SIZE];

	NHNChinaBilling::Connection con1("purple.billing/sqlmap");
	ReturnCode ret1;

	// ����ID�� �޾� ����.
	//ret1 = GetBalance(con1,"C_GZ",siServerID, accountid , balanceErr, &balance1,&balance2);	

	// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
	ret1 = GiftBalance(con1, "C_GZ", siServerID, accountid , balanceErr, &balance1, &balance2, &balance3);	
 
	if (SUCC != ret1)	
	{		
		return -1;	// ���� �� �˾ƿ��� ����
	}

	// ����+���� ������ ���ž׺��� ������ ����
	if( siPrice > balance3 +balance2 )
		return -2;  // ���� �����ؼ� ����

	// [����] �߱� �����۸�.
	if( siEventPrice > balance1 )
		return -2;  // �̺�Ʈ���� �����ؼ� ����
#endif

	// Ȯ�� ��------------------------------------------------------------------------------------------------

	// ���� ����---------------------------------------------------------------------------------------------

//KHY - 0304 - �߱� NHNChinaBilling - ������ ����.
#ifdef USE_NHNCHINABILLING

	NHNChinaBilling::Connection con2("purple.billing/sqlmap");	
	ReturnCode ret2;	

	char msg[NHNCHINABILLING_MSG_SIZE];	
	char	szProductKey[256] = {0,};

	sprintf(szProductKey , "%d" , siProductKey);
	// ����ID�� �޾� ����.
	//ret2 = UseCoin(con2, "C_GZ",siServerID, accountid, szName, szProductKey, siBuySeqNum, siProductNum, siPrice, szIP, "this is memo", "I", msg, logseq);
	
	// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
	ret2 = GiftCoin(con2, "C_GZ",siServerID, accountid, szName, szProductKey, siBuySeqNum, siProductNum, siPrice, siEventPrice, szIP, "this is memo", "I", msg, logseq);

	if (SUCC != ret2)	
	{	
		//msg
		return -3;	// ���� �� �˾ƿ��� ����
	}
	else
	{
		bSuccess = TRUE;  		
	}

#endif

	if( TRUE == bSuccess )
	{
		return 1;
	}

	return -4; // ���� ������ ����
	// ���� ��------------------------------------------------------------------------------------------------
}

					 
void DBGameProtocol::ItemMallGiftItem_NHNChina()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_NHNChina *pRecvMsg = (sDBRequest_ItemMall_Giftitem_NHNChina *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME]	= "";
	char szTxCode[50]					= "";
	SI32 siRealMoney					= 0;
	SI32 siBonusMoney					= 0;
	SI32 siEventMoney					= 0;
	SI32 siResult						= -99;
	SI32 siTotalPrice					= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice					= pRecvMsg->siProductEventPrice * pRecvMsg->siProductNum;
	SI32 siCheckBuyPrice				= 0;
	SI32 siBuySeqNum					= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,			sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice,		sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductEventPrice,	sizeof(pRecvMsg->siProductEventPrice) );
		END_SP()

			EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}

	// �ֹ���ȣ ����.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMall_BuySeqGet" )
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siBuySeqNum, 0 );
		END_FETCHDATA()		
	}

	//char logseq[NHNCHINABILLING_LOGSEQ_SIZE];

	SI32 rVal =	ItemMallProductBuyProcess_NHNChina( pRecvMsg->siServerID, // ���� ID
 												  	pRecvMsg->szMyAccountID ,
  												  	pRecvMsg->szName,
												  	pRecvMsg->siProductKey , 
												  	siBuySeqNum,  // �ֹ���ȣ
												  	pRecvMsg->siProductNum,
												  	siTotalPrice ,
												  	siEventPrice ,
												  	pRecvMsg->szIP,
												  	szTxCode
												 );

	if (1 == rVal)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallGiftItem_China" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,	sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,	sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID,	sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum,	sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice,			sizeof(siTotalPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney,				sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, 			sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney, 			sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode,					sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment,		sizeof(pRecvMsg->szComment) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP,			sizeof(pRecvMsg->szIP) );
			m_odbc.SetParam( SQL_INTEGER, &siBuySeqNum,				sizeof(siBuySeqNum) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;
		// ���ν��� �����ߴٸ� sendMsg.siResult �� �� ����
	}
	else
	{
		siResult = -97;
	}


	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;


	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );


	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û-----------------------------------------------
	SI64 balance1 = 0;  // ���� ������
	SI64 balance2 = 0;  // ���� ������
	SI64 balance3 = 0;  // [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ�.

//KHY - 0304 - �߱� NHNChinaBilling - �ܾ���ȸ
#ifdef USE_NHNCHINABILLING
	char balanceErr[NHNCHINABILLING_MSG_SIZE];

	NHNChinaBilling::Connection con3("purple.billing/sqlmap");
	ReturnCode ret3;

	// ����ID�� �޾� ����.
	//ret3 = GetBalance(con3,"C_GZ",pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1,&balance2);	

	// [����] �߱� �����۸�. �̺�Ʈ ��� �ܾ��� �߰�.
	ret3 = GiftBalance(con3,"C_GZ",pRecvMsg->siServerID, pRecvMsg->szMyAccountID , balanceErr, &balance1,&balance2, &balance3);	

	if (SUCC == ret3)	
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(balance2+ balance2);
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = balance1;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;		
	}
#endif

	// Ȯ�� ��------------------------------------------------------------------------------------------------

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallGetItem_NHNChina()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_NHNChina *pRecvMsg = (sDBRequest_ItemMallGetItem_NHNChina *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_China" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}
void DBGameProtocol::ItemMallMyCashInfo_USA()
{
	// ���� ��Ŷ
	sDBRequest_Get_MyCash_Info_USA *pRecvMsg = (sDBRequest_Get_MyCash_Info_USA *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	//SI32 siHanCoin = 0;
	//SI32 siGiftCard = 0;
	//SI32 siInnerEvent = 0;
	//SI32 siOuterEvent = 0;
	SI32 siToTalCoin = 0;

	BOOL bSuccess = FALSE;

	//bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , pRecvMsg->uiIDNo, &siHanCoin , &siGiftCard , &siInnerEvent , & siOuterEvent );
	bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , pRecvMsg->uiIDNo, &siToTalCoin );

	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		//sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);        
		sendMsg.siCash = siToTalCoin;
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;
	}

	// ����������쿡�� 0 ������ ��������.
	sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMallBuyItem_Korea()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_Korea *pRecvMsg = (sDBRequest_ItemMall_Buyitem_Korea *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}
	

	SI32 rVal =	ItemMallProductBuyProcess_Korea( pRecvMsg->szMyAccountID , pRecvMsg->siProductPrice , pRecvMsg->siProductKey , pRecvMsg->siProductNum );

	if( 1 == rVal )
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallBuyItem_Special" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;

		sendMsg.siPersonID = pRecvMsg->siPersonID;
		sendMsg.siProductKey = pRecvMsg->siProductKey;
		memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
		memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
		sendMsg.siProductNum = pRecvMsg->siProductNum;
		sendMsg.siProductPrice = pRecvMsg->siProductPrice;
	}
	else
	{
		siResult = -97;
	}

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;



	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;
	BOOL bSuccess = FALSE;


	if ( g_BillingMode == HANGAME_BILLINGMODE_SOCKET )
		bSuccess = clHangameBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	else if( g_BillingMode == HANGAME_BILLINGMODE_NEVERBILL )
		bSuccess = clHannEverBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );

	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;		
	}
	// ������ �˾ƿ� ��

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

SI32 DBGameProtocol::ItemMallProductBuyProcess_Korea(IN char * accountid , IN SI32 siPrice , 
													 IN SI32 siProductKey ,IN SI32 siProductNum )
{
	// �ܾ� ��� ����Ȯ��

	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;

	BOOL bSuccess = FALSE;

	if( g_BillingMode == HANGAME_BILLINGMODE_SOCKET )
		bSuccess = clHangameBillingProcess.GetBillingBalance( accountid , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	else if( g_BillingMode == HANGAME_BILLINGMODE_NEVERBILL )
		bSuccess = clHannEverBillingProcess.GetBillingBalance(accountid , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );

	if( FALSE == bSuccess )
	{
		return -1;	// ���� �� �˾ƿ��� ����
	}

	// ����+���� ������ ���ž׺��� ������ ����
	if( siPrice * siProductNum > siHanCoin + siGiftCard + siInnerEvent + siOuterEvent )
		return -2;  // ���� �����ؼ� ����
	// Ȯ�� ��

	bSuccess = FALSE;

	if( g_BillingMode == HANGAME_BILLINGMODE_SOCKET )
		bSuccess = clHangameBillingProcess.ChargeItem( accountid , siProductKey , siPrice , siProductNum );
	else if( g_BillingMode == HANGAME_BILLINGMODE_NEVERBILL )
		bSuccess = clHannEverBillingProcess.ChargeItem( accountid , siProductKey , siPrice , siProductNum );

	if( TRUE == bSuccess )
	{
		return 1;
	}
	else
	{
		return -2; // ���� ������ ����
	}

}

void DBGameProtocol::ItemMallBuyItem_USA()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_USA *pRecvMsg = (sDBRequest_ItemMall_Buyitem_USA *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}
	

	SI32 rVal =	ItemMallProductBuyProcess_USA( pRecvMsg->szMyAccountID , (SI32)pRecvMsg->uiIDNo, pRecvMsg->szIP, pRecvMsg->siProductPrice , pRecvMsg->siProductKey , pRecvMsg->szProductName, pRecvMsg->siProductNum );

	if( 1 == rVal )
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallBuyItem_USA" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;

		sendMsg.siPersonID = pRecvMsg->siPersonID;
		sendMsg.siProductKey = pRecvMsg->siProductKey;
		memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
		memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
		sendMsg.siProductNum = pRecvMsg->siProductNum;
		sendMsg.siProductPrice = pRecvMsg->siProductPrice;
	}
	else
	{
		siResult = -97;
	}

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;



	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	/*SI32 siHanCoin = 0;
	SI32 siGiftCard = 0;
	SI32 siInnerEvent = 0;
	SI32 siOuterEvent = 0;*/
	SI32 siToTalCoin = 0;
	BOOL bSuccess = FALSE;

	//bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , (SI32)pRecvMsg->uiIDNo, &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , pRecvMsg->uiIDNo, &siToTalCoin );

	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		//sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);
		sendMsg.siCash = siToTalCoin;
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;		
	}
	// ������ �˾ƿ� ��

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

SI32 DBGameProtocol::ItemMallProductBuyProcess_USA(IN char * accountid , IN SI32 siIDNo, TCHAR* pszIP, IN SI32 siPrice , 
													 IN SI32 siProductKey ,IN TCHAR* pszProductName, IN SI32 siProductNum )
{
	// �ܾ� ��� ����Ȯ��

	/*SI32 siHanCoin = 0;
	SI32 siGiftCard = 0;
	SI32 siInnerEvent = 0;
	SI32 siOuterEvent = 0;*/
	SI32 siToTalCoin  = 0;

	BOOL bSuccess = FALSE;

	//bSuccess = clIJJIBillingProcess.GetBillingBalance( accountid , siIDNo, &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	bSuccess = clIJJIBillingProcess.GetBillingBalance(accountid , siIDNo, &siToTalCoin );
	
	if( FALSE == bSuccess )
	{
		return -1;	// ���� �� �˾ƿ��� ����
	}

	// ����+���� ������ ���ž׺��� ������ ����
	//if( siPrice * siProductNum > siHanCoin + siGiftCard + siInnerEvent + siOuterEvent )
	if( siPrice * siProductNum > siToTalCoin )
		return -2;  // ���� �����ؼ� ����
	// Ȯ�� ��

	bSuccess = false;

	bSuccess = clIJJIBillingProcess.ChargeItem( accountid , siIDNo, pszIP, siProductKey , pszProductName, siPrice , siProductNum );

	if( TRUE == bSuccess )
	{
		return 1;
	}
	else
	{
		return -2; // ���� ������ ����
	}

}

//[����] �����ֱ�. => 2008-7-23
SI32 DBGameProtocol::ItemMallProductGiftProcess_USA(IN TCHAR* pszGiftSendID, IN TCHAR* pszGiftRecvID,  IN SI32 siIDNo, TCHAR* pszIP, IN SI32 siPrice ,
												    IN SI32	  siProductKey,  IN TCHAR* pszProductName, IN SI32 siProductNum )
{
	// �ܾ� ��� ����Ȯ��

	/*SI32 siHanCoin = 0;
	SI32 siGiftCard = 0;
	SI32 siInnerEvent = 0;
	SI32 siOuterEvent = 0;*/
	SI32 siToTalCoin = 0;

	BOOL bSuccess = FALSE;

	//bSuccess = clIJJIBillingProcess.GetBillingBalance( pszGiftSendID , siIDNo, &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	bSuccess = clIJJIBillingProcess.GetBillingBalance(pszGiftSendID , siIDNo, &siToTalCoin );

	if( FALSE == bSuccess )
	{
		return -1;	// ���� �� �˾ƿ��� ����
	}

	// ����+���� ������ ���ž׺��� ������ ����
	//if( siPrice * siProductNum > siHanCoin + siGiftCard + siInnerEvent + siOuterEvent )
	if( siPrice * siProductNum > siToTalCoin )
		return -2;  // ���� �����ؼ� ����
	// Ȯ�� ��

	bSuccess = false;

	bSuccess = clIJJIBillingProcess.GiftItem( pszGiftSendID , pszGiftRecvID, siIDNo, pszIP, siProductKey , pszProductName, siPrice , siProductNum );

	if( TRUE == bSuccess )
	{
		return 1;
	}
	else
	{
		return bSuccess; // ���� ������ ����
	}
}


void DBGameProtocol::ItemMallGiftItem_Korea()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_Korea *pRecvMsg = (sDBRequest_ItemMall_Giftitem_Korea *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}

	SI32 rVal =	ItemMallProductBuyProcess_Korea( pRecvMsg->szMyAccountID , pRecvMsg->siProductPrice , pRecvMsg->siProductKey,pRecvMsg->siProductNum );

	if (1 == rVal)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallGIftItem_Special" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;
		// ���ν��� �����ߴٸ� sendMsg.siResult �� �� ����
	}
	else
	{
		siResult = -97;
	}


	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;


	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );


	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;
	BOOL bSuccess = FALSE;

	if( g_BillingMode == HANGAME_BILLINGMODE_SOCKET )
		bSuccess = clHangameBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	else if( g_BillingMode == HANGAME_BILLINGMODE_NEVERBILL )
		bSuccess = clHannEverBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );

	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;		
	}
	// ������ �˾ƿ� ��

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallGiftItem_USA()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_USA *pRecvMsg = (sDBRequest_ItemMall_Giftitem_USA *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

		if (siCheckBuyPrice != 1)
		{
			return;
		}
	}
	
	//[����] �����ֱ�. => 2008-7-23
	SI32 rVal =	ItemMallProductGiftProcess_USA( pRecvMsg->szMyAccountID , pRecvMsg->szGetAccountID, (SI32)pRecvMsg->uiIDNo, pRecvMsg->szIP, pRecvMsg->siProductPrice , pRecvMsg->siProductKey, pRecvMsg->szProductName, pRecvMsg->siProductNum );
		
	//[����] �Ѱ��ӿ��� �����ϱ� ������ ����. => 2008-7-23
	sendMsg.siHanFailReason = rVal;

	if (1 == rVal)
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallGIftItem_USA" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID,	sizeof(pRecvMsg->siPersonID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey,	sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID,	sizeof(pRecvMsg->szMyAccountID) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum,	sizeof(pRecvMsg->siProductNum) );
			m_odbc.SetParam( SQL_INTEGER, &siTotalPrice,			sizeof(siTotalPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siRealMoney,				sizeof(siRealMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siBonusMoney,			sizeof(siBonusMoney) );
			m_odbc.SetParam( SQL_INTEGER, &siEventMoney,			sizeof(siEventMoney) );
			m_odbc.SetParam( SQL_VARCHAR, szTxCode,					sizeof(szTxCode) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment,		sizeof(pRecvMsg->szComment) );
			m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP,			sizeof(pRecvMsg->szIP) );
		END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

		sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;
		// ���ν��� �����ߴٸ� sendMsg.siResult �� �� ����
	}
	else
	{
		siResult = -97;
	}


	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;


	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont   = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName,  pRecvMsg->szGetCharName,  sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );


	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	/*SI32 siHanCoin = 0;
	SI32 siGiftCard = 0;
	SI32 siInnerEvent = 0;
	SI32 siOuterEvent = 0;*/
	SI32 siToTalCoin = 0;
	BOOL bSuccess = FALSE;

	//bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID, (SI32)pRecvMsg->uiIDNo, &siHanCoin , &siGiftCard , &siInnerEvent , &siOuterEvent );
	bSuccess = clIJJIBillingProcess.GetBillingBalance(pRecvMsg->szMyAccountID , pRecvMsg->uiIDNo, &siToTalCoin );
	if( TRUE == bSuccess )
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		//sendMsg.siCash = (SI32)(siHanCoin + siGiftCard + siInnerEvent + siOuterEvent);
		sendMsg.siCash = siToTalCoin;
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash		= 0;
		sendMsg.siEventCash = 0;		
	}
	// ������ �˾ƿ� ��

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

void DBGameProtocol::ItemMallGetItem_Korea()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_Korea *pRecvMsg = (sDBRequest_ItemMallGetItem_Korea *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_Special" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::ItemMallGetItem_USA()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_USA *pRecvMsg = (sDBRequest_ItemMallGetItem_USA *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_USA" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
		m_odbc.GetData( &sendMsg.siPersonID, 0 );
		m_odbc.GetData( &sendMsg.siInvPos, 0 );
		m_odbc.GetData( &sendMsg.siItemID, 0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

void DBGameProtocol::ItemMallBuyItem_XNoti()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_ForXNoti *pRecvMsg = (sDBRequest_ItemMall_Buyitem_ForXNoti *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem_ForXNoti sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM_FORXNOTI;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.siArrayIndex = pRecvMsg->siArrayIndex;
	sendMsg.siIdx = pRecvMsg->siIdx;
	
	SI32	siPersonID = 0;
	SI32	siMoney = 0;
	TCHAR	szIP[20] = { 0, };

	if( pRecvMsg->siServiceArea == ConstServiceArea_Korea )
	{
		BEGIN_SP( "rsp_ItemMallBuyItem_Special" )
	}
	else if ( pRecvMsg->siServiceArea == ConstServiceArea_USA )
	{
		BEGIN_SP( "rsp_ItemMallBuyItem_USA" )
	}
		m_odbc.SetParam( SQL_INTEGER, &siPersonID, sizeof(siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szTxCode, sizeof(pRecvMsg->szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, szIP, sizeof(szIP) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	END_FETCHDATA()

	if(sendMsg.siResult == 0)
		sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );

	//char log[512] = "";
	//sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
	//	, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
	//	, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
	//	);
	//sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	//SendLogMsg((sPacketHeader *)&LogMsg);

}

void DBGameProtocol::ItemMallGiftItem_XNoti()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_ForXNoti *pRecvMsg = (sDBRequest_ItemMall_Giftitem_ForXNoti *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem_ForXNoti sendMsg;
	
	//[����] �����ϱ�. ������ �������� �������� ����. => 2008-7-24
	sendMsg.siProductKey    =	pRecvMsg->siProductKey; 
	sendMsg.siProductNum	=	pRecvMsg->siProductNum;
	sendMsg.siProductPrice	=	pRecvMsg->siProductPrice;
	memcpy(sendMsg.szMyAccountID,  pRecvMsg->szMyAccountID,  sizeof(sendMsg.szMyAccountID));
	memcpy(sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID));
	memcpy(sendMsg.szComment,	   pRecvMsg->szComment,		 sizeof(sendMsg.szComment));
	memcpy(sendMsg.szGetCharName,  pRecvMsg->szGetCharName,  sizeof(sendMsg.szGetCharName));
	memcpy(sendMsg.szSendCharName, pRecvMsg->szSendCharName, sizeof(sendMsg.szSendCharName));
	//-------------------------------------------------------------------------------------------

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM_FORXNOTI;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.siArrayIndex = pRecvMsg->siArrayIndex;
	sendMsg.siIdx = pRecvMsg->siIdx;

	SI32	siPersonID	= 0;
	SI32	siMoney		= 0;
	TCHAR	szIP[20]	= { 0, };

	// DB Query
	BEGIN_SP( "rsp_ItemMallGIftItem_Special" )
		m_odbc.SetParam( SQL_INTEGER, &siPersonID, sizeof(siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siMoney, sizeof(siMoney) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szTxCode, sizeof(pRecvMsg->szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
		m_odbc.SetParam( SQL_VARCHAR, szIP, sizeof(szIP) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	END_FETCHDATA()

	if(sendMsg.siResult == 0)
		sendMsg.siResult = 1;

	// send
	SendPacket( (BYTE *)&sendMsg );
}

void DBGameProtocol::ItemMall_CancelOrder_XNoti()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_CancelOrder_XNoti *pRecvMsg = (sDBRequest_ItemMall_CancelOrder_XNoti *)m_pPacket;

	// DB Query
	BEGIN_SP( "rsp_ItemMallBuyOrderCancel" )
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szTxCode, sizeof(pRecvMsg->szTxCode) );
	END_SP()

	EXEC_SQL()
}

void DBGameProtocol::ItemMallGetItem_Taiwan()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_Taiwan *pRecvMsg = (sDBRequest_ItemMallGetItem_Taiwan *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd	= DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );

	sendMsg.usCharID		= pRecvMsg->usCharID;
	sendMsg.bPossession		= pRecvMsg->bPossession; 

	SI32 siExistence = 0;
	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_Taiwan" )
		m_odbc.SetParam( SQL_INTEGER,	&pRecvMsg->siPersonID,	sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_SMALLINT,	&pRecvMsg->siInvPos,	sizeof(pRecvMsg->siInvPos)	 );
		m_odbc.SetParam( SQL_INTEGER,	&pRecvMsg->siItemID,	sizeof(pRecvMsg->siItemID)	 );
		SetItemParam( &pRecvMsg->clItem );
		m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
		m_odbc.SetParam( SQL_TINYINT,	&pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult,		0 );
		m_odbc.GetData( &sendMsg.siPersonID,	0 );
		m_odbc.GetData( &sendMsg.siInvPos,		0 );
		m_odbc.GetData( &sendMsg.siItemID,		0 );
		GetItemData( &sendMsg.clItem );
		m_odbc.GetData( &sendMsg.bPossession,	0 );
	END_FETCHDATA()

		// send
		SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}



//	[��ȣ] ���� ���� - ���� Cash ��ȸ
void DBGameProtocol::ItemMallMyCashInfo_Germany()
{
	// ���� ��Ŷ
	SDBRequest_Get_MyCash_Info_Germany *pRecvMsg = (SDBRequest_Get_MyCash_Info_Germany *)m_pPacket;

	// ���� ��Ŷ
	SDBResponse_Get_MyCash_Info sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_GET_MYCASH_INFO;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	DWORD dwRealMoney	= 0;

	//	PG���� ���� Cash �ܾ��� ��û�Ѵ�.
	BILL_PACK_BALANCE* pBalanceData = GetBalance_Germany(pRecvMsg->siIDNumber, pRecvMsg->szMyAccountID);

	if(pBalanceData != NULL)
	{
		sendMsg.siCash		=	(SI32)pBalanceData->m_nCashRemain;
		sendMsg.siEventCash =	0;
	}

	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;
	}

	sendMsg.siResult = 1;


	// send
	SendPacket( (BYTE *)&sendMsg );
}



BILL_PACK_BALANCE* DBGameProtocol::GetBalance_Germany(SI32 siAccountNumber, char* accountid)
{
	if( _tcscmp(g_szServiceMode, "DEBUG") == 0 || _tcscmp(g_szServiceMode, "TEST") == 0 )		//	�׽�Ʈ ����̰ų� ����� ��� �ΰ��
	{
		BILL_PACK_BALANCE TestBalance;
		ZeroMemory(&TestBalance, sizeof(BILL_PACK_BALANCE));

		TestBalance.m_Header.m_RetCode	= 0;
		TestBalance.m_nCashRemain			= 100000;
		TestBalance.m_nUserNo				= siAccountNumber;	
		strncpy(TestBalance.m_szUserID, accountid, strlen(TestBalance.m_szUserID));

		return &TestBalance;
	}

	//	�ܾ���ȸ
	BILL_PACK_BALANCE* pPcaketBalance = (BILL_PACK_BALANCE*)cBillBalanceManager.ProcessBalance(siAccountNumber, accountid);

	if(pPcaketBalance == NULL || pPcaketBalance->m_Header.m_RetCode != 0)
		return NULL;

	return pPcaketBalance;
}


//	[��ȣ] ���� ���� - ������ ����
void DBGameProtocol::ItemMallBuyItem_Germany()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Buyitem_Germany *pRecvMsg = (sDBRequest_ItemMall_Buyitem_Germany*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Buyitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_BUYITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

		EXEC_SQL()
			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	//	PG���� ���� ��û�� �մϴ�.
	BILL_PACK_BUY* pBuyData = GetBuy_Germany(pRecvMsg->siIDNumber, pRecvMsg->szMyAccountID, pRecvMsg->siProductKey, siTotalPrice, pRecvMsg->szItemName);

	if(pBuyData != NULL)
	{
		siRealMoney = (SI32)pBuyData->m_nCashRemain;								//	������ �ݾ�
		strncpy(szTxCode, pBuyData->m_szChargeNo, sizeof(pBuyData->m_szChargeNo));	//	PG�κ��� ���� ���Ż�ǰ�ڵ�

		// DB Query
		BEGIN_SP( "rsp_ItemMallBuyItem_German" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(pRecvMsg->siProductPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

			sendMsg.siCash = siRealMoney;
		sendMsg.siEventCash = 0;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;

		sendMsg.siPersonID = pRecvMsg->siPersonID;
		sendMsg.siProductKey = pRecvMsg->siProductKey;
		memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
		memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
		sendMsg.siProductNum = pRecvMsg->siProductNum;
		sendMsg.siProductPrice = pRecvMsg->siProductPrice;
	}
	else
	{
		siResult = -97;
	}

	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;



	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;
	BOOL bSuccess = FALSE;

	BILL_PACK_BALANCE* pBalanceData = GetBalance_Germany(pRecvMsg->siIDNumber, pRecvMsg->szMyAccountID);

	if(pBalanceData != NULL)
	{
		// �Ѱ����� Cash������ ������ �����Ѵ�.
		sendMsg.siCash = (SI32)pBalanceData->m_nCashRemain;
		//sendMsg.siEventCash = (SI32)(siInnerEvent + siOuterEvent);
		sendMsg.siEventCash = 0;
		// ������ �˾ƿ� ��
	}
	else
	{
		sendMsg.siCash = 0;
		sendMsg.siEventCash = 0;
	}

	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, TxCode = %s, IP = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szMyAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szIP
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Buy Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}

BILL_PACK_BUY* DBGameProtocol::GetBuy_Germany(SI32 siAccountNumber, TCHAR* accountid, SI32 siProductKey, SI32 siProductPrice, TCHAR* szProductName)
{
	SI32 siRet				= -1;
	char szCode[50]			= "" ;

	if( _tcscmp(g_szServiceMode, "DEBUG") == 0 || _tcscmp(g_szServiceMode, "TEST") == 0 )		//	�׽�Ʈ ����̰ų� ����� ��� �ΰ��
	{
		BILL_PACK_BUY TestBuy;
		ZeroMemory(&TestBuy, sizeof(BILL_PACK_BUY));

		TestBuy.m_Header.m_RetCode	= 0;
		TestBuy.m_nCashRemain		= 100000;
		TestBuy.m_nUserNo			= siAccountNumber;	

		TestBuy.m_nItemPrice		=	siProductPrice;
		strncpy(TestBuy.m_szUserID,		accountid,		strlen(TestBuy.m_szUserID));
		strncpy(TestBuy.m_szItemName,	szProductName,	strlen(TestBuy.m_szItemName));

		char szProductKey[128];
		sprintf(TestBuy.m_szItemID, "%d", siProductKey);

		return &TestBuy;
	}


	//	�ܾ���ȸ
	BILL_PACK_BALANCE* pPcaketBalance = (BILL_PACK_BALANCE*)cBillBalanceManager.ProcessBalance(siAccountNumber, accountid);


	if(pPcaketBalance == NULL || pPcaketBalance->m_Header.m_RetCode != 0)		//	��ȸ ���н�
		return NULL;
	else
	{
		if(siProductPrice > (SI32)pPcaketBalance->m_nCashRemain)		//	���� �ݾ����� �����Ҽ� �ִ��� üũ
			return NULL;
	}


	char szProductKey[128];
	sprintf(szProductKey, "%d", siProductKey);


	//	����
	BILL_PACK_BUY* pPacketBuy = (BILL_PACK_BUY*)cBillBalanceManager.ProcessBuyItem(siAccountNumber, accountid, szProductKey, siProductPrice, szProductName);

	if(pPacketBuy == NULL || pPacketBuy->m_Header.m_RetCode != 0)
		return NULL;

	return pPacketBuy;
}


//	���� Billing ������ ����
void DBGameProtocol::ItemMallGiftItem_Germany()
{
	// ���� ��Ŷ
	sDBRequest_ItemMall_Giftitem_Germany *pRecvMsg = (sDBRequest_ItemMall_Giftitem_Germany*)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMall_Giftitem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALL_GIFTITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	bool bCheck = false;
	char szAccountID[MAX_PLAYER_NAME] = "";
	char szTxCode[50]	= "";
	SI32 siRealMoney	= 0;
	SI32 siBonusMoney	= 0;
	SI32 siEventMoney	= 0;
	SI32 siResult		= -99;
	SI32 siTotalPrice	= pRecvMsg->siProductPrice * pRecvMsg->siProductNum;
	SI32 siEventPrice	= 0;
	SI32 siCheckBuyPrice	= 0;

	// ���űݾ� Ȯ��.
	{
		// DB Query
		BEGIN_SP( "rsp_ItemMallCheckBuyPrice" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductPrice, sizeof(pRecvMsg->siProductPrice) );
			m_odbc.SetParam( SQL_INTEGER, &siEventPrice,			sizeof(siEventPrice) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siCheckBuyPrice, 0 );
		END_FETCHDATA()

			if (siCheckBuyPrice != 1)
			{
				return;
			}
	}

	//	PG���� ������ ���� ���� Packet�� ��û �մϴ�.
	BILL_PACK_GIFT* pGiftData = GetGift_Germany(pRecvMsg->siIDNumber, pRecvMsg->szMyAccountID, pRecvMsg->szGetAccountID, pRecvMsg->siProductKey, siTotalPrice, pRecvMsg->szItemName);

	if (pGiftData != NULL)
	{
		siRealMoney = pGiftData->m_nCashRemain;
		strncpy(szTxCode, pGiftData->m_szChargeNo, sizeof(pGiftData->m_szChargeNo));

		// DB Query
		BEGIN_SP( "rsp_ItemMallGIftItem_German" )
			m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductKey, sizeof(pRecvMsg->siProductKey) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szMyAccountID, sizeof(pRecvMsg->szMyAccountID) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szGetAccountID, sizeof(pRecvMsg->szGetAccountID) );
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siProductNum, sizeof(pRecvMsg->siProductNum) );
		m_odbc.SetParam( SQL_INTEGER, &siTotalPrice, sizeof(siTotalPrice) );
		m_odbc.SetParam( SQL_INTEGER, &siRealMoney, sizeof(siRealMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siBonusMoney, sizeof(siBonusMoney) );
		m_odbc.SetParam( SQL_INTEGER, &siEventMoney, sizeof(siEventMoney) );
		m_odbc.SetParam( SQL_VARCHAR, szTxCode, sizeof(szTxCode) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szComment, sizeof(pRecvMsg->szComment) );
		m_odbc.SetParam( SQL_VARCHAR, pRecvMsg->szIP, sizeof(pRecvMsg->szIP) );
		END_SP()

			EXEC_SQL()

			BEGIN_FETCHDATA()
			m_odbc.GetData( &siResult, 0 );
		END_FETCHDATA()

			sendMsg.siCash = siRealMoney + siBonusMoney;
		sendMsg.siEventCash = siEventMoney;

		if(siResult == 0)
			sendMsg.siResult = 1;
		else
			sendMsg.siResult = siResult;
		// ���ν��� �����ߴٸ� sendMsg.siResult �� �� ����
	}
	else
	{
		siResult = -97;
	}


	if(siResult == 0)
		sendMsg.siResult = 1;
	else
		sendMsg.siResult = siResult;


	sendMsg.siPersonID = pRecvMsg->siPersonID;
	sendMsg.siProductKey = pRecvMsg->siProductKey;
	memcpy( sendMsg.szItemName, pRecvMsg->szItemName, sizeof(sendMsg.szItemName));
	memcpy( sendMsg.szMyAccountID, pRecvMsg->szMyAccountID, sizeof(sendMsg.szMyAccountID) );
	sendMsg.siProductNum = pRecvMsg->siProductNum;
	sendMsg.siProductPrice = pRecvMsg->siProductPrice;

	sendMsg.siGetServerUnique = pRecvMsg->siGetServerUnique;
	sendMsg.siItemImageFont = pRecvMsg->siItemImageFont;
	memcpy( sendMsg.szGetAccountID, pRecvMsg->szGetAccountID, sizeof(sendMsg.szGetAccountID) );
	memcpy( sendMsg.szGetCharName, pRecvMsg->szGetCharName, sizeof(sendMsg.szGetCharName) );
	memcpy( sendMsg.szComment, pRecvMsg->szComment, sizeof(sendMsg.szComment) );


	// �پ�� �ܾ��� �˾ƿ��� ���� �ٽ��ѹ� ������ ������ �������� ��û

	SI64 siHanCoin = 0;
	SI64 siGiftCard = 0;
	SI64 siInnerEvent = 0;
	SI64 siOuterEvent = 0;
	BOOL bSuccess = FALSE;

	BILL_PACK_BALANCE* pBalanceData = GetBalance_Germany(pRecvMsg->siIDNumber, pRecvMsg->szMyAccountID);

	siRealMoney = pBalanceData->m_nCashRemain;


	if(pBalanceData != NULL)
	{
		sendMsg.siCash = siRealMoney;
		sendMsg.siEventCash = 0;
	}
	else
	{
		sendMsg.siCash		= 0;
		sendMsg.siEventCash = 0;
	}


	// send
	SendPacket( (BYTE *)&sendMsg );

	char log[512] = "";
	sprintf(log, "Result = %d, ProductKey = %d, ToAccountID = %s, siTotalPrice = %d, ProductNum = %d, ProductPrice = %d, RealMoney = %d, BonusMoney = %d, EventMoney = %d, , TxCode = %s, Comments = %s, IP = %s, ServerUnique = %d, ToCharName = %s"
		, sendMsg.siResult, pRecvMsg->siProductKey, pRecvMsg->szGetAccountID, siTotalPrice, pRecvMsg->siProductNum, pRecvMsg->siProductPrice
		, siRealMoney, siBonusMoney, siEventMoney, szTxCode, pRecvMsg->szComment, pRecvMsg->szIP,sendMsg.siGetServerUnique,sendMsg.szGetCharName
		);
	sDBLogMsg_QueryString LogMsg("ItemMall Gift Item", pRecvMsg->siPersonID, NULL, NULL, log);
	SendLogMsg((sPacketHeader *)&LogMsg);
}



BILL_PACK_GIFT* DBGameProtocol::GetGift_Germany(SI32 siAccountNumber, TCHAR* accountid, TCHAR* Recvaccountid, SI32 siProductKey, SI32 siProductPrice, TCHAR* szProductName)
{
	SI32 siRet				= -1;
	char szCode[50]			= "" ;

	SI32 siPrice			= siProductPrice;

	if( _tcscmp(g_szServiceMode, "DEBUG") == 0 || _tcscmp(g_szServiceMode, "TEST") == 0 )		//	�׽�Ʈ ����̰ų� ����� ��� �ΰ��
	{
		BILL_PACK_GIFT TestGift;
		ZeroMemory(&TestGift, sizeof(BILL_PACK_GIFT));

		TestGift.m_Header.m_RetCode	= 0;
		TestGift.m_nCashRemain		= 100000;
		TestGift.m_nUserNo			= siAccountNumber;	

		TestGift.m_nItemPrice		=	siProductPrice;
		strncpy(TestGift.m_szUserID,		accountid,		strlen(TestGift.m_szUserID));
		strncpy(TestGift.m_szReceiveUserID, Recvaccountid,	strlen(TestGift.m_szReceiveUserID));
		strncpy(TestGift.m_szItemName,		szProductName,	strlen(TestGift.m_szItemName));

		char szProductKey[128];
		sprintf(TestGift.m_szItemID, "%d", siProductKey);

		return &TestGift;
	}

	//	�ܾ���ȸ
	BILL_PACK_BALANCE* pPacketBalance = (BILL_PACK_BALANCE*)cBillBalanceManager.ProcessBalance(siAccountNumber, accountid);

	if(pPacketBalance == NULL || pPacketBalance->m_Header.m_RetCode != 0)
		return NULL;

	char szProductKey[128];
	sprintf(szProductKey, "%d", siProductKey);


	//	����
	BILL_PACK_GIFT* pPacketGift = (BILL_PACK_GIFT*)cBillBalanceManager.ProcessGiftItem(siAccountNumber, accountid, Recvaccountid, szProductKey, siProductPrice, szProductName);

	if(pPacketGift == NULL || pPacketGift->m_Header.m_RetCode != 0)
		return NULL;

	return pPacketGift;
}

void DBGameProtocol::ItemMallGetItem_Germany()
{
	// ���� ��Ŷ
	sDBRequest_ItemMallGetItem_Germany *pRecvMsg = (sDBRequest_ItemMallGetItem_Germany *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_ItemMallGetItem sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_ITEMMALLGETITEM;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;
	sendMsg.bPossession = pRecvMsg->bPossession; 
	SI32 siExistence = 0;

	// DB Query
	BEGIN_SP( "rsp_ItemMallGetItem_German" )
		m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siItemID, sizeof(pRecvMsg->siItemID) );
	SetItemParam( &pRecvMsg->clItem );
	m_odbc.SetParam( SQL_BIT, &pRecvMsg->bCreateSID, sizeof(pRecvMsg->bCreateSID) );
	m_odbc.SetParam( SQL_TINYINT, &pRecvMsg->bPossession, sizeof(pRecvMsg->bPossession) );
	END_SP()

		EXEC_SQL()

		BEGIN_FETCHDATA()
		m_odbc.GetData( &sendMsg.siResult, 0 );
	m_odbc.GetData( &sendMsg.siPersonID, 0 );
	m_odbc.GetData( &sendMsg.siInvPos, 0 );
	m_odbc.GetData( &sendMsg.siItemID, 0 );
	GetItemData( &sendMsg.clItem );
	m_odbc.GetData( &sendMsg.bPossession, 0 );
	END_FETCHDATA()

		// send
		SendPacket( (BYTE *)&sendMsg );

	// �α� �ۼ�
	// ���� ���� ������ => (-1) ���� ������������ ���� ��� => 404
	if(sendMsg.siResult == 1)
	{
		char log[512] = "";
		sprintf(log, "���� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d, bPossession = %d, UseDate = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum, sendMsg.bPossession, sendMsg.clItem.uiDateUseDay
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == -1)
	{
		char log[512] = "";
		sprintf(log, "�������� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
	else if(sendMsg.siResult == 404)
	{
		char log[512] = "";
		sprintf(log, "���ž����۾��� : item_seq = %d, InvPos = %d, Amount = %d, BeforeItemNum = %d, AfterItemAmount = %d"
			, sendMsg.siItemID, sendMsg.siInvPos, pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum - pRecvMsg->clItem.siItemNum, sendMsg.clItem.siItemNum
			);
		sDBLogMsg_QueryString LogMsg("ItemMall Get Item", sendMsg.siPersonID, NULL, sendMsg.clItem.siUnique, log);
		SendLogMsg((sPacketHeader *)&LogMsg);
	}
}

// [��ȣ_NHN->NDOORS] ���� ���μ���
bool DBGameProtocol::BuyItemProcess_Korea(char *accountid, SI32 *price, SI32 *realmoney, SI32 *bonusmoney, SI32 *eventmoney, char *txcode, bool bGift )
{
	SI32 siEtcMoney			= 0;
	SI32 siLeftMoney		= *price;
	SI32 siUseRealMoney		= 0;
	SI32 siUseBonusMoney	= 0;
	SI32 siUseEventMoney	= 0;

	SI32 siRet				= -1;

	char szCode[50]			= "" ;

	// ����, ���� �ܾ���ȸ
	siRet = CBillManager_nDoors_Korea::GetUserCash(accountid, realmoney, bonusmoney, eventmoney);
	if(siRet != 0 )
		return false;

	// �̺�Ʈ �ܾ���ȸ
	siRet = CBillManager_nDoors_Korea::GetUsePkgCash(accountid, eventmoney);
	if(siRet != 0 )
		return false;

	// ����+����+�̺�Ʈ�Ӵ� ������ ���ž׺��� ������ ����
	if(*price > (*realmoney + *bonusmoney + *eventmoney) )
		return false;

	// ���ο�û
	siRet = CBillManager_nDoors_Korea::Get_Approve(accountid, price, szCode, bGift);
	if(siRet != 0 )
		return false;

	// ������û
	siRet = CBillManager_nDoors_Korea::ConfirmTX(accountid, *price, szCode, bGift);
	if(siRet != 0 )
		return false;

	if ( bGift == false )
	{
		// ���ݾ� ����. �̺�Ʈ -> ���� -> ���� ������ �����Ѵ�.
		if(siLeftMoney > *eventmoney)
		{
			siUseEventMoney = *eventmoney;
			siLeftMoney -= *eventmoney;
		}
		else
		{
			siUseEventMoney = siLeftMoney;
			siLeftMoney = 0;
		}

		if(siLeftMoney > 0)
		{
			if(siLeftMoney > *bonusmoney)
			{
				siUseBonusMoney = *bonusmoney;
				siLeftMoney -= *bonusmoney;
			}
			else
			{
				siUseBonusMoney = siLeftMoney;
				siLeftMoney = 0;
			}
		}

		if(siLeftMoney > 0)
		{
			if(siLeftMoney > *realmoney)
			{
				siUseRealMoney = *realmoney;
				siLeftMoney -= *realmoney;
			}
			else
			{
				siUseRealMoney = siLeftMoney;
				siLeftMoney = 0;
			}
		}

		*realmoney	= siUseRealMoney;
		*bonusmoney	= siUseBonusMoney;
		*eventmoney	= siUseEventMoney;
	}
	else//(����, ����, �̺�Ʈ)
	{
		if ( siLeftMoney > *realmoney )
		{
			siUseRealMoney = *realmoney;
			siLeftMoney -= *realmoney;
		}
		else
		{
			siUseRealMoney = siLeftMoney;
			siLeftMoney = 0;
		}

		if(siLeftMoney > 0)
		{
			if(siLeftMoney > *bonusmoney)
			{
				siUseBonusMoney = *bonusmoney;
				siLeftMoney -= *bonusmoney;
			}
			else
			{
				siUseBonusMoney = siLeftMoney;
				siLeftMoney = 0;
			}
		}

		if(siLeftMoney > 0)
		{
			if(siLeftMoney > *eventmoney)
			{
				siUseEventMoney = *eventmoney;
				siLeftMoney -= *eventmoney;
			}
			else
			{
				siUseEventMoney = siLeftMoney;
				siLeftMoney = 0;
			}
		}

		*realmoney	= siUseRealMoney;
		*bonusmoney	= siUseBonusMoney;
		*eventmoney	= siUseEventMoney;
	}

	//// ����, ���� �ܾ���ȸ
	//siRet = GetUserCash(accountid, realmoney, bonusmoney, eventmoney);
	//if(siRet != 0 )
	//	return false;

	strcpy(txcode,szCode);

	return true;
}
void DBGameProtocol::Warp_TargetWorld()
{
	// ���� ��Ŷ
	sDBRequest_Warp_TargetWorld *pRecvMsg = (sDBRequest_Warp_TargetWorld *)m_pPacket;

	// ���� ��Ŷ
	sDBResponse_TargetWorld sendMsg;

	sendMsg.packetHeader.usCmd = DBMSG_RESPONSE_WARP_TARGETWORLD;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );
	sendMsg.usCharID = pRecvMsg->usCharID;

	// DB Query
	BEGIN_SP( "rsp_warp_TargetWorld" )
	m_odbc.SetParam( SQL_INTEGER, &pRecvMsg->siPersonID, sizeof(pRecvMsg->siPersonID) );
	m_odbc.SetParam( SQL_SMALLINT, &pRecvMsg->siInvPos, sizeof(pRecvMsg->siInvPos) );
	SetItemParam( &pRecvMsg->clItem );
	END_SP()

	EXEC_SQL()

	BEGIN_FETCHDATA()
	m_odbc.GetData( &sendMsg.siResult, 0 );
	m_odbc.GetData( &sendMsg.siPersonID, 0 );
	m_odbc.GetData( &sendMsg.siInvPos, 0 );
	GetItemData( &sendMsg.clItem );
	END_FETCHDATA()

	// send
	SendPacket( (BYTE *)&sendMsg );

	// ����� �α� 
	/*char log[512] = "";
	sprintf(log, "Type = %d, Using = %d, DataVary = %d, InvPos = %d"
		, pRecvMsg->siType, pRecvMsg->bUsing, pRecvMsg->siDateVary, pRecvMsg->siInvPos
		);
	sDBLogMsg_QueryString LogMsg("Ticket Service", pRecvMsg->siPersonID, NULL, pRecvMsg->clItem.siUnique, log);
	SendLogMsg((sPacketHeader *)&LogMsg);*/
}

