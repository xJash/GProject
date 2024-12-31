#ifndef _DBMSGWORLDMONEY_H
#define _DBMSGWORLDMONEY_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "../../GoonzuWorld/CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"
#include "../../GoonzuWorld/Server/NTradeServerProcess/TradeServerMsg.h"
#include "../../GoonZuWorld/CommonLogic/WorldPassport/WorldPassport.h"

// ��ť�� �ý��ۿ��Լ� ���.
#define INPUTREASON_WORLDMONEY_DISTRIBUTION		1	// ���������� ���.

class sDBRequest_Distribution_WorldMoney
{
public:
	sPacketHeader			packetHeader;

	UI16					usCharId;
	SI32					siPersonID;

	GMONEY					siMoney;			// ��ť��µ� �� ��
	SI64					siWorldMoney;		// �� ��ť

	SI32					siReason;

	sDBRequest_Distribution_WorldMoney( UI16 charid,SI32 personid,GMONEY money , SI64 worldmoney,SI32 reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_Distribution_WorldMoney );
		packetHeader.usCmd = DBMSG_REQUEST_DISTRIBUTION_WORLDMONEY;

		usCharId = charid ;
		siPersonID = personid ;

		siMoney = money ;
		siWorldMoney = worldmoney ;

		siReason = reason ;
	}
};

class sDBResponse_Distribution_WorldMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	GMONEY				siMoney;			// ��ť��µ� �� ��
	GMONEY				siLeftMoney;		// ��ť ��� ���� ��
	SI64				siWorldMoney;		// �� ��ť
	SI64				siLeftWorldMoney;	// �� ���� ��ť

	SI32				siReason;

	sDBResponse_Distribution_WorldMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_Distribution_WorldMoney));
	}
};

class sDBRequest_WorldMoney_TradeList
{
public:
	sPacketHeader			packetHeader;

	SI32					siPage;

	sDBRequest_WorldMoney_TradeList(SI32 page )
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_TradeList );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_TRADELIST;

		siPage = page ;
	}
};

class sDBResponse_WorldMoney_TradeList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPage;

	SI32				siPersonID[MAX_WORLDMONEY_TRADELIST_PER_SEND];
	SI64				siWorldMoney[MAX_WORLDMONEY_TRADELIST_PER_SEND];
	GMONEY				siPrice[MAX_WORLDMONEY_TRADELIST_PER_SEND];
	SI32				siDate[MAX_WORLDMONEY_TRADELIST_PER_SEND];

	sDBResponse_WorldMoney_TradeList()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_TradeList));
	}
};

// ��ť �ȱ⸦ ��û�Ѵ�.
class sDBRequest_WorldMoney_SellOrder
{
public:
	sPacketHeader			packetHeader;

	UI16					usCharId;
	SI32					siPersonID;

	GMONEY					siPrice; // ��ť�� ���� ( ���� )
	SI64					siWorldMoney; // �ø� ��ť

	GMONEY					siFee; // ������

	SI32					siDate; // �ø� �ð�(���ӽð�)

	sDBRequest_WorldMoney_SellOrder(UI16 charid , SI32 personid , GMONEY price,SI64 worldmoney , GMONEY fee,SI32 date)
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_SellOrder );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_SELLORDER;

		usCharId = charid ;
		siPersonID = personid ;

		siPrice = price ;
		siWorldMoney = worldmoney ;

		siFee = fee ;

		siDate = date ;
	}
};

class sDBResponse_WorldMoney_SellOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharId;
	SI32				siPersonID;

	SI32				siListIndex; // ����Ʈ������ �ε���
	GMONEY				siPrice; // ��ť�� ���� ( ���� )
	SI64				siWorldMoney; // �ø� ��ť

	GMONEY				siLeftMoney; //�����Ḧ ���ϰ� ���� ��
	SI64				siLeftWorldMoney; // �ø��� ���� ��ť

	SI32				siDate; // �ø� �ð�(���ӽð�)

	// PCK : �α׿� ��Ŷ �߰�
	GMONEY				siFee;

	sDBResponse_WorldMoney_SellOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_SellOrder));
	}
};

// ��ť ��⸦ ��û�Ѵ�.
class sDBRequest_WorldMoney_BuyOrder
{
public:
	sPacketHeader			packetHeader;

	UI16					usCharId;
	SI32					siPersonID;

	SI32					siListIndex;

	SI64					siWorldMoney; // ��� ����ϴ� ��ť
	GMONEY					siPrice; // ��� ����

	sDBRequest_WorldMoney_BuyOrder(UI16 charid , SI32 personid , SI32 index,SI64 worldmoney , GMONEY price)
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_BuyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_BUYORDER;

		usCharId = charid ;
		siPersonID = personid ;

		siListIndex = index ;

		siWorldMoney = worldmoney ;
		siPrice = price ;
	}
};

class sDBResponse_WorldMoney_BuyOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharId;
	SI32				siPersonID;

	SI32				siListIndex; // ����Ʈ������ �ε���

	SI64				siWorldMoney; // �� ��ť
	SI64				siLeftListWorldMoney; // ����Ʈ������ ��� ���� ��ť - �� �ȷ����� 0

	GMONEY				siPrice; // �� ���� - �̰ŷ��� 0
	GMONEY				siLeftMoney; // ��� ���� ��
	SI64				siLeftWorldMoney; // �� ���� ��ť

	SI32				siSellerPersonID;
	GMONEY				siSellerBankMoney;

	sDBResponse_WorldMoney_BuyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_BuyOrder));
	}
};

// �÷ȴ� ��ť�� ����ؼ� ȸ���Ѵ�.
class sDBRequest_WorldMoney_CancelOrder
{
public:
	sPacketHeader			packetHeader;

	UI16					usCharId;
	SI32					siPersonID;

	sDBRequest_WorldMoney_CancelOrder(UI16 charid , SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_CancelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_CANCELORDER;

		usCharId = charid ;
		siPersonID = personid ;
	}
};

class sDBResponse_WorldMoney_CancelOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharId;
	SI32				siPersonID;

	SI32				siListIndex; // ����Ʈ������ �ε���

	SI64				siLeftWorldMoney; // ����ϰ� ���� ���� ��ť��

	sDBResponse_WorldMoney_CancelOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_CancelOrder));
	}
};

// ��ť�� ������ ������.
class sDBRequest_WorldMoney_ReducePrice
{
public:
	sPacketHeader			packetHeader;

	SI32					siIndex; // ������ �ֹ��� �ε���
	GMONEY					siPrice; // ���� ����

	SI32					siDate; // ����� ���� �ð�

	SI32					siPersonID; // personid Ȯ�ο�
	SI64					siWorldMoney; // worldmoney Ȯ�ο�

	sDBRequest_WorldMoney_ReducePrice(SI32 index , GMONEY price , SI32 date , SI32 personid , SI64 worldmoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_ReducePrice );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_REDUCEPRICE;

		siIndex = index ;
		siPrice = price ;

		siDate = date ;

		siPersonID = personid ;
		siWorldMoney = worldmoney ;
	}
};

class sDBResponse_WorldMoney_ReducePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siPersonID;

	SI32				siIndex; // ����� �ֹ��� �ε���
	GMONEY				siPrice; // ����� ����

	SI32				siDate; // ����� ���� �ð�

	sDBResponse_WorldMoney_ReducePrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_ReducePrice));
	}
};

// ��ť�� �־��ش�.
class sDBRequest_WorldMoney_Set_Char
{
public:
	sPacketHeader			packetHeader;

	SI32					siCharID;
	SI32					siPersonID;

	SI64					siWorldMoney;

	sDBRequest_WorldMoney_Set_Char(SI32 charid,SI32 personid,SI64 worldmoney)
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_Set_Char );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_SET_CHAR;

		siCharID = charid;
		siPersonID = personid ;

		siWorldMoney = worldmoney ;
	}
};

class sDBResponse_WorldMoney_Set_Char
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siCharID;
	SI32				siPersonID;

	SI64				siWorldMoney;	// �־��� ��ť
	SI64				siLeftWorldMoney; // �־��ص� ���� ��ť��

	sDBResponse_WorldMoney_Set_Char()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_Set_Char));
	}
};

//--------------------------------------------
// TradeServer
//--------------------------------------------

// Ʈ���̵� ������ �ֹ��� ����ߴ�.
class sDBRequest_TradeServer_SetOrder
{
public:
	sPacketHeader			packetHeader;

	SI32					siCharId;
	SI32					siPersonID;

	cltTradeServerOrder		clOrder; // �ֹ� ����
	SI16					siPos;

	GMONEY					siWorldMoneyFee; // ���� ������

	sDBRequest_TradeServer_SetOrder(SI32 charid,SI32 personid,cltTradeServerOrder*pclOrder,SI16 pos,SI64 fee)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeServer_SetOrder );
		packetHeader.usCmd = DBMSG_REQUEST_TRADESERVER_SETORDER;

		siCharId = charid;
		siPersonID = personid ;

		clOrder.Set(pclOrder);
		siPos = pos ;

		siWorldMoneyFee = fee ;
	}
};

class sDBResponse_TradeServer_SetOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ���� ����

	SI32				siCharID;
	SI32				siPersonID;

	cltTradeServerOrder	clOrder;
	SI16				siPos;

	cltItem				clLeftItem; // �ֹ��� �� ���� ������
	SI64				siLeftWorldMoney; // �ֹ��� �� ���� ��ť

	// PCK : �α׿� ��Ŷ �߰�
	GMONEY				siWorldMoneyFee;		// ����Ҷ� �����ϴ� ������

	sDBResponse_TradeServer_SetOrder()
	{
		ZeroMemory(this,sizeof(sDBResponse_TradeServer_SetOrder));
	}
};

//���� ������ �ø� �ֹ��� ����Ѵ�.
class sDBRequest_TradeServer_CancelOrder
{
public:
	sPacketHeader			packetHeader;

	SI32					siCharId;
	SI32					siPersonID;

	cltTradeServerOrder		clOrder; // �ֹ� ����
	SI16					siPos;

	cltItem					clitem; // ����� �������� ���� ����Ÿ

	sDBRequest_TradeServer_CancelOrder(SI32 charid,SI32 personid,cltTradeServerOrder*pclOrder,SI16 pos,cltItem*pclitem)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeServer_CancelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_TRADESERVER_CANCELORDER;

		siCharId = charid;
		siPersonID = personid ;

		clOrder.Set(pclOrder);
		siPos = pos ;

		clitem.Set(pclitem);
	}
};

// ��ť �ü��� �����Ѵ�.
class sDBRequest_WorldMoney_SetAveragePrice
{
public:
	sPacketHeader			packetHeader;

	SI64					siAverageWorldMoneyPrice; // ��ť �ü�

	sDBRequest_WorldMoney_SetAveragePrice(SI64 price)
	{
		packetHeader.usSize = sizeof( sDBRequest_WorldMoney_SetAveragePrice );
		packetHeader.usCmd = DBMSG_REQUEST_WORLDMONEY_SETAVERAGEPRICE;

		siAverageWorldMoneyPrice = price ;
	}
};

class sDBResponse_WorldMoney_SetAveragePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	GMONEY				siAverageWorldMoneyPrice;

	sDBResponse_WorldMoney_SetAveragePrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_WorldMoney_SetAveragePrice));
	}
};

class sDBResponse_TradeServer_CancelOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ���� ����

	SI32				siCharID;
	SI32				siPersonID;

	cltTradeServerOrder	clOrder;
	SI16				siPos;

	cltItem				clLeftItem; // �ֹ��� �� ���� ������

	sDBResponse_TradeServer_CancelOrder()
	{
		ZeroMemory(this,sizeof(sDBResponse_TradeServer_CancelOrder));
	}
};

// ���� �������� ������ ���.
class sDBRequest_TradeServer_BuyItem
{
public:
	sPacketHeader			packetHeader;

	SI32					siCharId;
	SI32					siPersonID;

	cltTradeServerOrder		clOrder; // �ֹ� ����
	char					szSellerServer[20];
	SI16					siPos;

	cltItem					clitem;

	//sDBRequest_TradeServer_BuyItem(SI32 charid,SI32 personid,cltTradeServerOrder*pclOrder,SI16 pos,cltItem*pclitem)
	sDBRequest_TradeServer_BuyItem(SI32 charid,SI32 personid,cltTradeServerOrder*pclOrder,SI16 pos,cltItem*pclitem,char*sellerserver)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeServer_BuyItem );
		packetHeader.usCmd = DBMSG_REQUEST_TRADESERVER_BUYITEM;

		siCharId = charid;
		siPersonID = personid ;

		clOrder.Set(pclOrder);
		siPos = pos ;

		clitem.Set(pclitem);

		MStrCpy(szSellerServer,sellerserver,20);
	}
};

class sDBResponse_TradeServer_BuyItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ���� ����

	SI32				siCharID;
	SI32				siPersonID;

	cltTradeServerOrder	clOrder;
	SI16				siPos;

	cltItem				clLeftItem; // �ֹ��� �� ���� ������
	SI64				siLeftWorldMoney;

	sDBResponse_TradeServer_BuyItem()
	{
		ZeroMemory(this,sizeof(sDBResponse_TradeServer_BuyItem));
	}
};

// ���� �������� �ȸ� ���ǿ� ���� ������ �����Ѵ�.
class sDBRequest_TradeServer_Set_SellInfo
{
public:
	sPacketHeader			packetHeader;

	//	SI32					siPersonID;
	char				szBuyerServer[20] ; // �� ����� �ִ� ����
	char				szBuyerName[20] ; // �� ����� �̸�
	char				szBuyerAccountID[20] ; // �� ����� ����

	cltTradeServerOrder		clOrder; // �ȸ� �ֹ� ����

	sDBRequest_TradeServer_Set_SellInfo(char*buyserver,char*buyname,char*buyaccount,cltTradeServerOrder*pclOrder)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeServer_Set_SellInfo );
		packetHeader.usCmd = DBMSG_REQUEST_TRADESERVER_SET_SELLINFO;

		MStrCpy(szBuyerServer,buyserver,20);
		MStrCpy(szBuyerName,buyname,20);
		MStrCpy(szBuyerAccountID,buyaccount,20);

		clOrder.Set(pclOrder);
	}
};

class sDBResponse_TradeServer_Set_SellInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ���� ����

	//	SI32				siPersonID;
	char				szBuyerServer[20] ; // �� ����� �ִ� ����
	char				szBuyerName[20] ; // �� ����� �̸�
	char				szBuyerAccountID[20] ; // �� ����� ����

	cltTradeServerOrder	clOrder;
	SI64				siLeftWorldMoney;

	sDBResponse_TradeServer_Set_SellInfo()
	{
		ZeroMemory(this,sizeof(sDBResponse_TradeServer_Set_SellInfo));
	}
};

// ������������ ����� ��ť �ޱ�
class sDBRequest_TradeServer_Get_Withdraw_Acu
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;
	SI32				m_siCharID;

	SI64				m_siLeftSavedAcu;	// ���������� ����� ��ť
	SI64				m_siWithdrawAcu;	// ���� ��ť

	SI32				m_siReservedNum;	// ��ť�� �ް� ���� ���������� �� ��ȣ�� ��ť�� ���޵Ǿ��ٰ� ���� ��ȣ

	sDBRequest_TradeServer_Get_Withdraw_Acu( SI32 siPersonID, SI32 siCharID, SI64 siLeftSavedAcu, SI64 siWithdrawAcu, SI32 siReservedNum )
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_TradeServer_Get_Withdraw_Acu );
		m_packetHeader.usCmd	= DBMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU;

		m_siPersonID			= siPersonID;
		m_siCharID				= siCharID;

		m_siLeftSavedAcu		= siLeftSavedAcu;
		m_siWithdrawAcu			= siWithdrawAcu;

		m_siReservedNum			= siReservedNum;
	}
};

class sDBResponse_TradeServer_Get_Withdraw_Acu
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;

	SI32				m_siPersonID;
	SI32				m_siCharID;

	SI64				m_siLeftSavedAcu;	// ���������� ����� ��ť
	SI64				m_siWithdrawAcu;	// ���� ��ť

	SI64				m_siLeftAcu;		// ����� �� ��ť

	SI32				m_siReservedNum;	// �̹�ȣ�� ���������� �� ��ȣ�� ��ť�� �޾Ҵٰ� ������ ���ѿ�


	sDBResponse_TradeServer_Get_Withdraw_Acu( )
	{
		ZeroMemory( this, sizeof(sDBResponse_TradeServer_Get_Withdraw_Acu) );
	}
};	// DBMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU


//===================================================================================================================
//
// WorldPassport(�������� ����)
//
//===================================================================================================================

// ������ �����Ѵ�

class sDBRequest_WorldPassport_Set
{
public:
	sPacketHeader	packetHeader;

	SI32			m_siPersonID;
	SI32			m_siCharID;
	
	TCHAR			m_szPassportName[Const_Max_WorldPassport_Name];	// �����̸�

	SI32			m_siIssueDateVary;								// ������
	SI32			m_siExpireDateVary;								// ��ȿ�Ⱓ

	SI64			m_siPaidAcu;									// �߱޺��

	
	sDBRequest_WorldPassport_Set( SI32 siPersonID, SI32 siCharID, TCHAR* pszPassportName, SI32 siIssueDateVary, SI32 siExpireDateVary, SI64 siPaidAcu )
	{
		packetHeader.usSize	= sizeof( sDBRequest_WorldPassport_Set );
		packetHeader.usCmd	= DBMSG_REQUEST_WORLDPASSPORT_SET;

		m_siPersonID		= siPersonID;
		m_siCharID			= siCharID;

		MStrCpy( m_szPassportName, pszPassportName, Const_Max_WorldPassport_Name );

		m_siIssueDateVary	= siIssueDateVary;
		m_siExpireDateVary	= siExpireDateVary;

		m_siPaidAcu			= siPaidAcu;
	}
	
};

class sDBResponse_WorldPassport_Set
{
public:
	sPacketHeader	packetHeader;

	SI32			m_siResult;										// �����

	SI32			m_siPersonID;
	SI32			m_siCharID;

	TCHAR			m_szPassportName[Const_Max_WorldPassport_Name];	// �����̸�

	SI32			m_siIssueDateVary;								// ������
	SI32			m_siExpireDateVary;								// ��ȿ�Ⱓ

	SI64			m_siPaidAcu;									// �߱޺��
	SI64			m_siLeftAcu;									// ���� ���� ����� ��ť


	sDBResponse_WorldPassport_Set()
	{
		ZeroMemory( this, sizeof(sDBResponse_WorldPassport_Set) );
	}

};	// DBMSG_RESPONSE_WORLDPASSPORT_SET

// ������ �����Ѵ�

class sDBRequest_WorldPassport_Extend
{
public:
	sPacketHeader	packetHeader;

	SI32			m_siPersonID;
	SI32			m_siCharID;

	SI32			m_siExpireDateVary;								// ��ȿ�Ⱓ

	SI64			m_siPaidAcu;									// ������


	sDBRequest_WorldPassport_Extend( SI32 siPersonID, SI32 siCharID, SI32 siExpireDateVary, SI64 siPaidAcu )
	{
		packetHeader.usSize	= sizeof( sDBRequest_WorldPassport_Extend );
		packetHeader.usCmd	= DBMSG_REQUEST_WORLDPASSPORT_EXTEND;

		m_siPersonID		= siPersonID;
		m_siCharID			= siCharID;

		m_siExpireDateVary	= siExpireDateVary;

		m_siPaidAcu			= siPaidAcu;
	}

};

class sDBResponse_WorldPassport_Extend
{
public:
	sPacketHeader	packetHeader;

	SI32			m_siResult;										// �����

	SI32			m_siPersonID;
	SI32			m_siCharID;

	SI32			m_siExpireDateVary;								// ��ȿ�Ⱓ

	SI64			m_siPaidAcu;									// ������
	SI64			m_siLeftAcu;									// ���� ���� ����� ��ť


	sDBResponse_WorldPassport_Extend()
	{
		ZeroMemory( this, sizeof(sDBResponse_WorldPassport_Extend) );
	}

};	// DBMSG_RESPONSE_WORLDPASSPORT_EXTEND



#endif

