#ifndef _TRADELOGDBMSG_H_
#define _TRADELOGDBMSG_H_

#include "itzbase.h"
#include <strsafe.h>

#define MAX_DBLOG_SIZE_DATE				24 // DBLog szDate �ִ�
#define MAX_DBLOG_SIZE_LOGTEXT			512 // DBLog szLogTxt �ִ�
#define MAX_DBLOG_SIZE_NATIONCODE		4	// DBLog �����ڵ�
#define MAX_DBLOG_SIZE_ITEMUNIQUE		10 // DBLog szItemUnique

#define MAX_CHARNAME_SIZE				20 // ĳ���� �̸� ������

#define MAX_STLOGDATA_PER_PACKET		10

enum {
	TRADELOG_DBMSG_REQUEST_SELLED_LOG = 100,
	TRADELOG_DBMSG_RESPONSE_SELLED_LOG,

	TRADELOG_DBMSG_REQUEST_TRADE_LOG,
	TRADELOG_DBMSG_RESPONSE_TRADE_LOG,

	TRADELOG_DBMSG_END,
};

//=============================================================================
//	CLASS   stLOGData_SelledItem
//! @brief  
//=============================================================================
class stLOGData_SelledItem
{
public:
	SI08		siSendFlag;
	SI08		siCancelFlag;
	SI08		siItemAcceptFlag;

	char		szBuyServerNation[MAX_DBLOG_SIZE_NATIONCODE];
	SI16		siBuyServerIndex;
	SI16		siBuyCharNation;
    char		szBuyUserID[MAX_CHARNAME_SIZE];
	char		szBuyCharName[MAX_CHARNAME_SIZE];
	SI32		siBuyPersonID;

	char		szSellServerNation[MAX_DBLOG_SIZE_NATIONCODE];
	SI16		siSellServerIndex;
	SI16		siSellCharNation;
	char		szSellUserID[MAX_CHARNAME_SIZE];
	char		szSellCharName[MAX_CHARNAME_SIZE];
	SI32		siSellPersonID;

	SI16		siItemUnique;
	SI16		siItemNum;
	SI64		siPrice;

	SYSTEMTIME		stSellDate;
	SYSTEMTIME		stBuyDate;

	void Init()
	{
		ZeroMemory(this, sizeof(*this));
	}

	void Set(stLOGData_SelledItem* pstlogdata)
	{
		memcpy( this, pstlogdata, sizeof( stLOGData_SelledItem ));
	}
};

//=============================================================================
//	CLASS   X
//! @brief  
//=============================================================================
struct sDBRequest_SelledItemLog
{
	sPacketHeader		packetHeader;
	UI16				usCharID;

	char				szBuyServerNation[MAX_DBLOG_SIZE_NATIONCODE];	// ���� �ڵ�
	SI16				siBuyServerIndex;									// ������ȣ
	char				szBuyID[MAX_CHARNAME_SIZE];
	char				szBuyCharName[MAX_CHARNAME_SIZE];

	char				szSellServerNation[MAX_DBLOG_SIZE_NATIONCODE];	// ���� �ڵ�
	SI16				siSellServerIndex;									// ������ȣ
	char				szSellID[MAX_CHARNAME_SIZE];
	char				szSellCharName[MAX_CHARNAME_SIZE];

	SI16				siItemUnique;

	char				szStartDate[MAX_DBLOG_SIZE_DATE];			// �˻������� ��¥ ex:2004-08-10 10:30
	char				szEndDate[MAX_DBLOG_SIZE_DATE];				// �˻� ���� ��¥ ex:2004-08-10 10:31

	// �÷��� �� ---------------------------------------------------------------------------------------
	// ���               : uiSendFlag = 0 and uiCancelFlag = 1 and uiAcceptFlag = 0
	// �ǸŸ� �� ������   : uiSendFlag = 1 and uiCancelFlag = 0 and uiAcceptFlag = 0
	// �Ǹ� �Ϸ�� ������ : uiSendFlag = 1 and uiCancelFlag = 0 and uiAcceptFlag = 1
	// �ǸŰ� �Ϸ�� �������� �Ǹ��ڿ��� ��ť���� ���޵� �����̰�,
	// �ǸŸ� �� �������� �����ڿ��� �������� ���޵Ǿ����� �Ǹ��ڿ��� ��ť�� ���޵��� ���� �������̴�.
	SI08				siSendFlag;
	SI08				siCancelFlag;
	SI08				siAcceptFlag;
	// -------------------------------------------------------------------------------------------------

	sDBRequest_SelledItemLog()
	{
		ZeroMemory(this, sizeof(*this));

		packetHeader.usSize = sizeof( sDBRequest_SelledItemLog );
		packetHeader.usCmd	= TRADELOG_DBMSG_REQUEST_SELLED_LOG;
	}

	sDBRequest_SelledItemLog(	UI16 CharID, 
								char* pszBuyServerNation, SI16 BuyServerIndex, char* pszBuyID, char* pszBuyCharName,
								char* pszSellServerNation, SI16 SellServerIndex, char* pszSellID, char* pszSellCharName,
								SI16 ItemUnique, 
								char* pszStartDate, char* pszEndDate,
								SI08 SendFlag, SI08 CancelFlag, SI08 AcceptFlag )
	{
		ZeroMemory(this, sizeof(*this));

		packetHeader.usSize = sizeof( sDBRequest_SelledItemLog );
		packetHeader.usCmd	= TRADELOG_DBMSG_REQUEST_SELLED_LOG;

		usCharID		= CharID;

		StringCchCopy(szBuyServerNation, sizeof(szBuyServerNation), pszBuyServerNation);
		siBuyServerIndex = BuyServerIndex;
		StringCchCopy(szBuyID, sizeof(szBuyID), pszBuyID);
		StringCchCopy(szBuyCharName, sizeof(szBuyCharName), pszBuyCharName);

		StringCchCopy(szSellServerNation, sizeof(szSellServerNation), pszSellServerNation);
		siSellServerIndex = SellServerIndex;
		StringCchCopy(szSellID, sizeof(szSellID), pszSellID);
		StringCchCopy(szSellCharName, sizeof(szSellCharName), pszSellCharName);
		
		siItemUnique = ItemUnique;

		StringCchCopy(szStartDate, sizeof(szStartDate), pszStartDate);
		StringCchCopy(szEndDate, sizeof(szEndDate), pszEndDate);

		siSendFlag		= SendFlag;
		siCancelFlag	= CancelFlag;
		siAcceptFlag	= AcceptFlag;
	}

	void Set(sDBRequest_SelledItemLog *pLog)
	{
		if(pLog == NULL)			return;

		memcpy(this, pLog, sizeof(*this));
	}
};

struct sDBResponse_SelledItemLog
{
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siResult;

	stLOGData_SelledItem	stLogData[MAX_STLOGDATA_PER_PACKET];

	sDBResponse_SelledItemLog()
	{
		ZeroMemory( this, sizeof( sDBResponse_SelledItemLog ) );
	}
};

//=============================================================================
//	CLASS   stLOGData_TradeItem
//! @brief  
//=============================================================================
class stLOGData_TradeItem
{
public:
	SI32		siOrderIndex;

	char		szServerNation[MAX_DBLOG_SIZE_NATIONCODE];
	SI16		siServerIndex;
	SI16		siCharNation;
	char		szUserID[MAX_CHARNAME_SIZE];
	char		szCharName[MAX_CHARNAME_SIZE];
	SI32		siPersonID;

	SI16		siItemUnique;
	SI16		siItemNum;
	SI64		siPrice;

	SYSTEMTIME	stSellDate;

	SI08		siHoldAcu;

	void Init()
	{
		ZeroMemory(this, sizeof(*this));
	}

	void Set(stLOGData_TradeItem* pstlogdata)
	{
		memcpy( this, pstlogdata, sizeof( stLOGData_TradeItem ));
	}
};

//=============================================================================
//	CLASS   X
//! @brief  
//=============================================================================
struct sDBRequest_TradeItemLog
{
	sPacketHeader		packetHeader;
	UI16				usCharID;

	char				szServerNation[MAX_DBLOG_SIZE_NATIONCODE];	// ���� �ڵ�
	SI16				siServerIndex;									// ������ȣ
	char				szID[MAX_CHARNAME_SIZE];
	char				szCharName[MAX_CHARNAME_SIZE];

	SI16				siItemUnique;

	char				szStartDate[MAX_DBLOG_SIZE_DATE];			// �˻������� ��¥ ex:2004-08-10 10:30
	char				szEndDate[MAX_DBLOG_SIZE_DATE];				// �˻� ���� ��¥ ex:2004-08-10 10:31

	sDBRequest_TradeItemLog()
	{
		ZeroMemory(this, sizeof(*this));

		packetHeader.usSize = sizeof( sDBRequest_TradeItemLog );
		packetHeader.usCmd	= TRADELOG_DBMSG_REQUEST_TRADE_LOG;
	}

	sDBRequest_TradeItemLog(	UI16 CharID,
								char* pszServerNation, SI16 ServerIndex, char* pszID, char* pszCharName,
								char* pszStartDate, char* pszEndDate)
	{
		ZeroMemory(this, sizeof(*this));

		packetHeader.usSize = sizeof( sDBRequest_TradeItemLog );
		packetHeader.usCmd	= TRADELOG_DBMSG_REQUEST_TRADE_LOG;

		usCharID = CharID;

		StringCchCopy(szServerNation, sizeof(szServerNation), pszServerNation);
		siServerIndex = ServerIndex;
		StringCchCopy(szID, sizeof(szID), pszID);
		StringCchCopy(szCharName, sizeof(szCharName), pszCharName);

		StringCchCopy(szStartDate, sizeof(szStartDate), pszStartDate);
		StringCchCopy(szEndDate, sizeof(szEndDate), pszEndDate);
	}

	void Set(sDBRequest_TradeItemLog *pLog)
	{
		if(pLog == NULL)			return;

		memcpy(this, pLog, sizeof(*this));
	}
};

struct sDBResponse_TradeItemLog
{
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siResult;

	stLOGData_TradeItem		stLogData[MAX_STLOGDATA_PER_PACKET];

	sDBResponse_TradeItemLog()
	{
		ZeroMemory( this, sizeof( sDBResponse_TradeItemLog ) );
	}
};

#endif
