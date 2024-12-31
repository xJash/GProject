#ifndef _DBMSGSTOCK_H
#define _DBMSGSTOCK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Stock\Stock.h"

#define MIN_AUTODIVIEND_MONEY	1000000

//-----------------------------------------------------------------
// Person�� �ֽ� ���¸� ��û�Ѵ�.
//-----------------------------------------------------------------
class sDBRequest_PersonStockAccountGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� PersonID

	sDBRequest_PersonStockAccountGet(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonStockAccountGet);
		packetHeader.usCmd = DBMSG_REQUEST_PERSONSTOCKACCOUNTGET;

		siPersonID		= personid;
	}
};


class sDBResponse_PersonStockAccountGet
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				Result;
	SI32				siPersonID;			// ����� �Ǵ� PersonID
	cltStockAccount		clStockAccount;		// �ֽ� ���� ����. 

	sDBResponse_PersonStockAccountGet()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonStockAccountGet));
	}
};


//------------------------------------------
// �ֽ� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_STOCK_ORDER_NUM	100
class sDBRequest_GetManyStockOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siStartIndex;	//  ���;� �� ������ ���� �ε��� 

	sDBRequest_GetManyStockOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetManyStockOrder));
	}

	sDBRequest_GetManyStockOrder(SI32 id, SI32 ordermode, SI32 startindex)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetManyStockOrder );
		packetHeader.usCmd = DBMSG_REQUEST_GETMANYSTOCKORDER;
		usCharID		= id;

		siOrderMode		= ordermode;
		siStartIndex	= startindex;
	}
};


class sDBResponse_GetManyStockOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siStartIndex;		// ���� �ֹ��� ���� �ε���.
	cltTradeOrder		clTradeOrder[GET_MANY_STOCK_ORDER_NUM];

	sDBResponse_GetManyStockOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetManyStockOrder));
	}
};

//------------------------------------------
// �ֽ��� �ŷ��� ���� ��û 
//------------------------------------------
class sDBRequest_TradeStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siVillageUnique;// �ŷ��� ��û�ϴ� ������ VillageUnique. 	
	cltTradeOrder		clOrgOrder;		// Ŭ���̾�Ʈ�κ��� �� �ֹ�. 
	SI32				siDstOrderIndex;// �ݴ� �ֹ��� �ε��� (�ֹ���ȣ)

	GMONEY				siPrice;		// �ŷ� �ܰ�.

	sDBRequest_TradeStock()
	{
		ZeroMemory(this, sizeof(sDBRequest_TradeStock));
	}

	sDBRequest_TradeStock(SI32 id, SI32 ordermode, SI32 villageunique, cltTradeOrder* pclorgorder, SI32 dstorderindex, GMONEY price)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeStock );
		packetHeader.usCmd = DBMSG_REQUEST_TRADESTOCK;
		usCharID		= id;

		siOrderMode		= ordermode;
		siVillageUnique	= villageunique;
		clOrgOrder.Set(pclorgorder);
		siDstOrderIndex	= dstorderindex;
		siPrice			= price;
	}
};


class sDBResponse_TradeStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI08				siOrderMode;		// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI08				siVillageUnique;	// Request���� �Էµ� VillageUnique
	GMONEY				siTradePrice;		// ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0)

	// Org �ֹ���. 
	SI16				siTradeAmount;		// �ŷ��� �ֽļ�. 
	SI32				siLeftAmount;		// ���� �ֽļ�. 
	GMONEY				siBankMoney;		// ���� �ܰ�. (�ŷ���. ) 

	// Dst �ֹ���. 
	SI32				siDstLeftAmount;	// ���� �ֽļ�. 
	GMONEY				siDstBankMoney;		// ���� �ܰ�. (�ŷ���. ) 

	cltTradeOrder		clOrgOrder;			// ������ Ŭ���̾�Ʈ�� �ֹ�. 
	cltTradeOrder		clDstOrder;			// �ݴ� �ֹ��� ������ ����. 


	sDBResponse_TradeStock()
	{
		ZeroMemory(this, sizeof(sDBResponse_TradeStock));
	}
};


//------------------------------------------
// �ֽ��ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_OrderStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	cltTradeOrder		clOrder;		// DB�� �־�� �� �ֹ��� ����. 

	sDBRequest_OrderStock()
	{
		ZeroMemory(this, sizeof(sDBRequest_OrderStock));
	}

	sDBRequest_OrderStock(SI32 id, SI32 ordermode, cltTradeOrder* pclorder)
	{
		packetHeader.usSize = sizeof( sDBRequest_OrderStock );
		packetHeader.usCmd = DBMSG_REQUEST_ORDERSTOCK;
		usCharID		= id;

		siOrderMode		= ordermode;
		clOrder.Set(pclorder);
	}
};


class sDBResponse_OrderStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siOrderMode;		// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	cltTradeOrder		clOrder;			// DB�� ����� �ֹ��� ����. 

	sDBResponse_OrderStock()
	{
		ZeroMemory(this, sizeof(sDBResponse_OrderStock));
	}
};



//------------------------------------------
// �ֽ��ֹ��� ����� ���� ��û 
//------------------------------------------
class sDBRequest_CancelStockOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;


	SI32				siPersonID;		// �ֹ��� ����� PersonID

	sDBRequest_CancelStockOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_CancelStockOrder));
	}

	sDBRequest_CancelStockOrder(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_CancelStockOrder );
		packetHeader.usCmd = DBMSG_REQUEST_CANCELSTOCKORDER;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_CancelStockOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	SI32				siPersonID;			// �ֹ� ��Ҹ� ��û�ߴ� PersonID

	sDBResponse_CancelStockOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_CancelStockOrder));
	}
};

//------------------------------------------
// �������� �ֽ� ������ ��û
//------------------------------------------
class sDBRequest_ManyStockPrice
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_ManyStockPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyStockPrice));
		packetHeader.usSize = sizeof( sDBRequest_ManyStockPrice );
		packetHeader.usCmd = DBMSG_REQUEST_MANYSTOCKPRICE;
	}
};


class sDBResponse_ManyStockPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	GMONEY				siCurrentStockPrice[MAX_VILLAGE_NUMBER];	// ������ �ְ�. (�ð�) 
	GMONEY				siAverageStockPrice[MAX_VILLAGE_NUMBER];	// ��� �ְ�

	sDBResponse_ManyStockPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyStockPrice));
	}
};



//------------------------------------------
// ���� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_SetStockFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Who
	SI32				siPersonID;

	// Where
	SI32				siVillageUnique;	// ���ְ� ��ġ�� ���� VillageUnique

	// What
	cltFee				clFee;				// �����ؾ� �� ������ ������ ����


	sDBRequest_SetStockFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetStockFee));
	}

	sDBRequest_SetStockFee(SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetStockFee );
		packetHeader.usCmd = DBMSG_REQUEST_SETSTOCKFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_SetStockFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// result 
	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;

	// where
	SI32				siVillageUnique;	// ���ְ� ��ġ�� ������ VillageUnique

	// what
	cltFee				clFee;				// ������ �ŷ� ������ ����. 

	sDBResponse_SetStockFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetStockFee));
	}

};



//---------------------------------------
// ���� ���� ���� ���� ���� ������ ���´�
//---------------------------------------
class sDBResponse_GetStockBidVillageList
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	UI16					usCount;											// �������� ���� ����  
	cltStockBidVillageInfo	clStockBidVillageInfo[ MAX_VILLAGE_NUMBER ];		// �������� ���� ����

	sDBResponse_GetStockBidVillageList()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetStockBidVillageList ) );
	}

};

//---------------------------------------
// ���� ���� ������ ������ ����Ʈ�� ��û�Ѵ� 
//---------------------------------------
class sDBRequest_GetStockBidderList
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siVillageUnique;

	sDBRequest_GetStockBidderList( SI32 villageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetStockBidderList );
		packetHeader.usCmd = DBMSG_REQUEST_GETSTOCKBIDDERLIST;

		siVillageUnique = villageUnique;
	}
};


//---------------------------------------
// ���� ���� ������ ������ ����Ʈ�� ��ȯ�Ѵ�
//---------------------------------------
class sDBResponse_GetStockBidderList
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siVillageUnique;

	UI16					usCount;
	cltStockBidder			clStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];

	sDBResponse_GetStockBidderList()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetStockBidderList ) );
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_BidStock
//
// Last Modified 	: 2006 / 01 / 27
// Created		 	: �豤��
//
// Function			: [��û] ������� ���� ��û�Ѵ�.
//
//***************************************************************************************************
class sDBRequest_BidStock
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siPersonID;			
	SI32					siVillageUnique;		// �ֽ� ����(����)
	GMONEY					siStockMoney;			// ���� �ֽ��� ���� 1��

	cltDate					clDate;					// ������	

	sDBRequest_BidStock( UI16 id, SI32 personid, SI32 villageUnique, SI64 StockMoney, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_BidStock );
		packetHeader.usCmd = DBMSG_REQUEST_BIDSTOCK;

		usCharID = id;

		siPersonID = personid;
		siVillageUnique = villageUnique;
		siStockMoney = StockMoney;

		clDate.Set( pclDate );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_BidStock
//
// Last Modified 	: 2006 / 01 / 27
// Created		 	: �豤��
//
// Function			: [����] ������� ���� ��û�Ѵ�.
//
//***************************************************************************************************
class sDBResponse_BidStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	cltStockBidVillageInfo	clStockBidVillageInfo;

	// PCK : �α׿� ��Ŷ �߰�
	SI32				siVillageUnique;

	sDBResponse_BidStock()
	{
		ZeroMemory( this, sizeof( sDBResponse_BidStock ) );
	}
};
/*
//---------------------------------------
// ���� �ֽĿ� ���� ��û�Ѵ�
//---------------------------------------
class sDBRequest_BidStock
{
public:
sPacketHeader			packetHeader;
UI16					usCharID;

SI32					siPersonID;			

SI32					siTradeVillageUnique;	// �ŷ� ���� 
SI64					siFee;					// ������ 

SI32					siVillageUnique;		// �ֽ� ����(����)
SI32					siAmount;				// �ֽ� ���� 
cltMoney				clPrice;				// �ֽ� ���� 

cltDate					clDate;					// ������	

sDBRequest_BidStock( UI16 id, SI32 personid, SI32 tradeVillage, SI64 fee, SI32 villageUnique, SI32 amount, cltMoney *pclMoney, cltDate *pclDate )
{
packetHeader.usSize = sizeof( sDBRequest_BidStock );
packetHeader.usCmd = DBMSG_REQUEST_BIDSTOCK;

usCharID = id;

siPersonID = personid;

siTradeVillageUnique = tradeVillage;
siFee = fee;

siVillageUnique = villageUnique;
siAmount = amount;
clPrice.Set( pclMoney );
clDate.Set( pclDate );
}
};


//---------------------------------------
// ���� �ֽĿ� ���� ��û�� ���� ���� 
//---------------------------------------
class sDBResponse_BidStock
{
public:
sPacketHeader		packetHeader;
UI16				usCharID;

SI32				siResult;

SI32				siTradeVillageUnique;
cltMoney			clTradeStockStrMoney;

SI32				siVillageUnique;
cltStockBidder		clStockBidder;

cltMoney			clPersonBankMoney;

cltDate				clDate;						// ������ 

sDBResponse_BidStock()
{
ZeroMemory( this, sizeof( sDBResponse_BidStock ) );
}

};
*/

//---------------------------------------
// ���� �ֽĿ� ���� ��û ��� ��û
//---------------------------------------
class sDBRequest_CancelBidStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;

	sDBRequest_CancelBidStock( SI32 villageUnique, SI32 personid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CANCELBIDSTOCK;
		packetHeader.usSize = sizeof( sDBRequest_CancelBidStock );

		siVillageUnique = villageUnique;
		siPersonID = personid;
	}
};



//---------------------------------------
// ���� �ֽĿ� ���� ��û ��ҿ� ���� ���� 
//---------------------------------------
class sDBResponse_CancelBidStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	sDBResponse_CancelBidStock()
	{
		ZeroMemory( this, sizeof( sDBResponse_CancelBidStock ) );
	}

};



//---------------------------------------
// ���� ���� ������ �����Ѵ�
//---------------------------------------
class sDBRequest_SetStockBidVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;								// ����
	SI32				siStockAmount;									// ���� �ֽļ�
	cltDate				clDate;											// ������
	GMONEY				siBeginningPrice;								// ���۰� 

	sDBRequest_SetStockBidVillage( SI32 villageUnique, SI32 stockAmount, cltDate *pclDate, GMONEY beginningPrice )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetStockBidVillage );
		packetHeader.usCmd = DBMSG_REQUEST_SETSTOCKBIDVILLAGE;

		siVillageUnique = villageUnique;
		siStockAmount = stockAmount;
		clDate.Set( pclDate );
		siBeginningPrice = beginningPrice;
	}
};


//---------------------------------------
// ���� ���� ������ �����Ѵ�
//---------------------------------------
class sDBResponse_SetStockBidVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;								// ����
	SI32				siStockAmount;									// ���� �ֽļ�
	cltDate				clDate;											// ������
	GMONEY				siBeginningPrice;								// ���۰�

	sDBResponse_SetStockBidVillage()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetStockBidVillage ) );
	}

};

//---------------------------------------
// ��Ÿ� �����Ѵ� 
//---------------------------------------
class sDBRequest_CompleteStockBidVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// ����

	sDBRequest_CompleteStockBidVillage( SI32 villageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_CompleteStockBidVillage );
		packetHeader.usCmd = DBMSG_REQUEST_COMPLETESTOCKBIDVILLAGE;

		siVillageUnique = villageUnique;
	}

};

//---------------------------------------
// ��� ���� ��� 
//---------------------------------------
class sDBResponse_CompleteStockBidVillage
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siResult;											// ��� ���� ����(1:���� 0:����)

	SI32					siVillageUnique;
	cltMoney				clTotalMoney;										// ���� �ݾ�
	cltMoney				clCityhallMoney;									// ��� �ڱ� 
	cltMoney				clTaxMoney;											// ���ڷ� ���� ���ݾ�

	cltResultStockBidder	clResultStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];

	sDBResponse_CompleteStockBidVillage()
	{
		ZeroMemory( this, sizeof( sDBResponse_CompleteStockBidVillage ) );
	}

};


//--------------------------------------
// ���ڽ� ���� �ֽ��� ���� ���۰� ���� ��û 
//--------------------------------------
class sDBRequest_SetBeginningPrice
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siVillageUnique;
	GMONEY					siBeginningPrice;

	sDBRequest_SetBeginningPrice( SI32 villageUnique, GMONEY beginningPrice )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetBeginningPrice );
		packetHeader.usCmd = DBMSG_REQUEST_SETBEGINNINGPRICE;

		siVillageUnique = villageUnique;
		siBeginningPrice = beginningPrice;
	}


};


//--------------------------------------
// �ֽ� ���𿡼� ������ �ֽ� ���� ��û
//--------------------------------------
class sDBRequest_StockDistributionOrder
{
public:
	sPacketHeader			packetHeader;

	SI32					siVillageUnique;

	SI32					siPersonID;
	SI32					siCharID;

	SI32					siStockDistributionNum;
	GMONEY					siStockPrice;

	bool					bVillageWarStockDistribution;

	sDBRequest_StockDistributionOrder( SI32 VillageUnique, SI32 PersonID, SI32 CharID, SI32 StockDistributionNum, GMONEY StockPrice, bool VillageWarStockDistribution )
	{
		packetHeader.usSize = sizeof( sDBRequest_StockDistributionOrder );
		packetHeader.usCmd = DBMSG_REQUEST_STOCKDISTRIBUTIONORDER;

		siVillageUnique = VillageUnique;
		siPersonID = PersonID;
		siCharID = CharID;

		siStockDistributionNum = StockDistributionNum;
		siStockPrice = StockPrice;

		bVillageWarStockDistribution = VillageWarStockDistribution;
	}
};

class sDBResponse_StockDistributionOrder
{
public:
	sPacketHeader			packetHeader;

	SI32					siResult;

	SI32					siVillageUnique;

	SI32					siPersonID;
	SI32					siCharID;

	SI32					siStockDistributionNum;
	GMONEY					siStockPrice;

	cltMoney				clPersonMoney;

	bool					bVillageWarStockDistribution;

	sDBResponse_StockDistributionOrder()
	{
		ZeroMemory( this, sizeof( sDBResponse_StockDistributionOrder ) );
	}
};


class sDBRequest_MaxStockDistributionNum
{
public:
	sPacketHeader			packetHeader;

	SI32					siVillageUnique;

	SI32					siMaxStockDistributionNum;

	SI32					siStockDistributionNum;
	GMONEY					siStockPrice;

	bool					bVillageWarStockDistribution;

	UI08					uiRememberVillageUnique;

	SI32					siVillageWarWinVillageUnique;

	sDBRequest_MaxStockDistributionNum( SI32 VillageUnique, SI32 MaxStockDistributionNum, SI32 StockDistributionNum, GMONEY StockPrice, bool VillageWarStockDistribution, UI08 RememberVillageUnique, SI32 VillageWarWinVillageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_MaxStockDistributionNum );
		packetHeader.usCmd = DBMSG_REQUEST_MAXSTOCKDISTRIBUTIONNUM;

		siVillageUnique = VillageUnique;

		siMaxStockDistributionNum = MaxStockDistributionNum;

		siStockDistributionNum = StockDistributionNum;

		siStockPrice = StockPrice;

		bVillageWarStockDistribution = VillageWarStockDistribution;

		uiRememberVillageUnique = RememberVillageUnique;

		siVillageWarWinVillageUnique = VillageWarWinVillageUnique;
	}
};

class sDBResponse_MaxStockDistributionNum
{
public:
	sPacketHeader			packetHeader;

	SI32					siResult;

	SI32					siVillageUnique;

	SI32					siMaxStockDistributionNum;

	SI32					siStockDistributionNum;
	GMONEY					siStockPrice;

	bool					bVillageWarStockDistribution;

	UI08					uiRememberVillageUnique;

	SI32					siVillageWarWinVillageUnique;

	sDBResponse_MaxStockDistributionNum()
	{
		ZeroMemory( this, sizeof( sDBResponse_MaxStockDistributionNum ) );
	}
};

//#if defined(_CITYHALL_BANKRUPTCY)
//---------------------------------------
// [��û] ������ �Ļ��Ͽ� �ֽ� ��� ������ ��� �����ش�.
//---------------------------------------
class sDBRequest_ReturnStockBidVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// ����

	sDBRequest_ReturnStockBidVillage( SI32 villageUnique )
	{
		packetHeader.usSize = sizeof( sDBRequest_ReturnStockBidVillage );
		packetHeader.usCmd = DBMSG_REQUEST_RETURNSTOCKBIDVILLAGE;

		siVillageUnique = villageUnique;
	}

};

//---------------------------------------
// [����] ������ �Ļ��Ͽ� �ֽ� ��� ������ ��� �����ش�.
//---------------------------------------
class sDBResponse_ReturnStockBidVillage
{
public:
	sPacketHeader			packetHeader;
	UI16					usCharID;

	SI32					siResult;											// ��� ���� ���� ���� ����(1:���� 0:����)

	SI32					siVillageUnique;

	cltResultStockBidder	clResultStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];

	sDBResponse_ReturnStockBidVillage()
	{
		ZeroMemory( this, sizeof( sDBResponse_ReturnStockBidVillage ) );
	}

};
//#endif

//***************************************************************************************************
//
// Class Name 		: sDBRequest_BuyBidStock
//
// Last Modified 	: 2006 / 02 / 07
// Created		 	: �豤��
//
// Function			: [��û] �����ֽ� ���
//
//***************************************************************************************************
class sDBRequest_BuyBidStock
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		 // ����� ��û�� ���
	SI08				siBuyMode;		 // 0 : ���� 1 : �Ϲ�
	SI32				siVillageUnique; // ���� �ֽ��� ����� �ϴ� ���� ����ũ 	
	SI32				siAmount;		 // �ֹ� ���� (�ֹ���ȣ)
	GMONEY				siPrice;		 // 1�ִ� �ݾ�
	GMONEY				siTotalPrice;	 // �� �ŷ� �ݾ�
	bool				bBuySwitch;		 // ���ְ� �������� true �ߺ� ��� ����
	GMONEY				siFee;			 // �����ֽ��� ������

	sDBRequest_BuyBidStock()
	{
		ZeroMemory(this, sizeof(sDBRequest_BuyBidStock));
	}

	sDBRequest_BuyBidStock(SI32 ID, SI32 PersonID, SI08 BuyMode, SI32 VillageUnique, SI32 Amount, GMONEY Price, GMONEY TotalPrice, bool BuySwitch, GMONEY Fee )
	{
		packetHeader.usSize = sizeof( sDBRequest_BuyBidStock );
		packetHeader.usCmd = DBMSG_REQUEST_BUYBIDSTOCK;

		usCharID		= ID;

		siPersonID		= PersonID;
		siBuyMode		= BuyMode;
		siVillageUnique	= VillageUnique;
		siAmount		= Amount;
		siPrice		    = Price;
		siTotalPrice	= TotalPrice;
		bBuySwitch	    = BuySwitch;
		siFee			= Fee;
	}
};

class sDBResponse_BuyBidStock
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;

	SI08				siBuyMode;		 // 0 : ���� 1 : �Ϲ�
	SI32				siPersonID;		 // ����� ��û�� ���
	SI32				siResult;
	SI32				siAmount;		 // �ֹ� ���� (�ֹ���ȣ)
	GMONEY				siTotalPrice;	 // �� �ŷ� �ݾ�
	GMONEY				siFee;
	GMONEY				siBuyStockLeftMoney; // �ֽ��� ��� �� �Ŀ� �� ������

	cltStockBidVillageInfo clStockBidVillageInfo;

	cltMoney				clCityhallMoney;									// ��� �ڱ� 

	sDBResponse_BuyBidStock()
	{
		ZeroMemory( this, sizeof( sDBResponse_BuyBidStock ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_BuyBidStock
//
// Last Modified 	: 2006 / 02 / 07
// Created		 	: �豤��
//
// Function			: [��û] �����ֽ� ���
//
//***************************************************************************************************
class sDBRequest_MyStockInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;		 // ����� ��û�� ���


	sDBRequest_MyStockInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_MyStockInfo));
	}

	sDBRequest_MyStockInfo(UI16 ID, SI32 PersonID )
	{
		packetHeader.usSize = sizeof( sDBRequest_MyStockInfo );
		packetHeader.usCmd = DBMSG_REQUEST_MYSTOCKINFO;

		usCharID		= ID;
		siPersonID		= PersonID;
	}
};

class sDBResponse_MyStockInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	UI16				usCharID;

	SI32				siPersonID;		 // ����� ��û�� ���

	cltStockAccount		clInfo;			// ������Ʈ �� �ֽ� ����

	sDBResponse_MyStockInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_MyStockInfo ) );
	}
};



//-------------------------------------------------------------------------------------------------------
// �ֽ� ����
//-------------------------------------------------------------------------------------------------------

// �ֽ� ���� ���� ������ ȹ���Ѵ�
class sDBRequest_GetStockOfferingInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	sDBRequest_GetStockOfferingInfo( SI32 villageunique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetStockOfferingInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETSTOCKOFFERINGINFO;

		siVillageUnique		= villageunique;
	}
};


class sDBResponse_GetStockOfferingInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;
	SI32				siStatus;				// ���� ( 0: ���� �ƴ�, 1: ���� û�� ��,  2: ���� û�� ����)
	SI32				siTotalOffering;		// �� ���� �ֽ� ����
	SI32				siStockAmount;			// 1�δ� ��� �ֽ� ��
	GMONEY				siPrice;				// 1�δ� ��� �ֽ� ����


	sDBResponse_GetStockOfferingInfo()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetStockOfferingInfo) );
	}

};


// �ֽ� ���� ���� ���� (���� û�� ����)
class sDBRequest_SetStockOffering
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;
	SI32				siTotalOffering;		// �� ���� �ֽ� ����
	SI32				siStockAmount;			// 1�δ� ��� �ֽ� ��
	GMONEY				siPrice;				// 1�δ� ��� �ֽ� ����

	sDBRequest_SetStockOffering( SI32 villageunique, SI32 totaloffering, SI32 stockamount, GMONEY price  )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetStockOffering );
		packetHeader.usCmd = DBMSG_REQUEST_SETSTOCKOFFERING;

		siVillageUnique	= villageunique;
		siTotalOffering = totaloffering;
		siStockAmount = stockamount;
		siPrice = price;
	}

};

class sDBResponse_SetStockOffering
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;
	SI32				siTotalOffering;		// �� ���� �ֽ� ����
	SI32				siStockAmount;			// 1�δ� ��� �ֽ� ��
	GMONEY				siPrice;				// 1�δ� ��� �ֽ� ����

	sDBResponse_SetStockOffering()
	{
		ZeroMemory( this, sizeof(sDBResponse_SetStockOffering) );
	}

};


// �ֽ� ���� û�� ����
class sDBRequest_EndStockOffering
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	sDBRequest_EndStockOffering( SI32 villageunique )
	{
		packetHeader.usSize = sizeof( sDBRequest_EndStockOffering );
		packetHeader.usCmd = DBMSG_REQUEST_ENDSTOCKOFFERING;

		siVillageUnique		= villageunique;
	}

};

class sDBResponse_EndStockOffering
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	sDBResponse_EndStockOffering()
	{
		ZeroMemory( this, sizeof(sDBResponse_EndStockOffering) );
	}

};

// �ֽ� ���� û�� �ֹ�
class sDBRequest_StockOfferingOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siStockAmount;
	GMONEY				siMoney;

	TCHAR				szIP[20];
	TCHAR				szPrivateIP[20];
	TCHAR				szMacAddress[20];

	sDBRequest_StockOfferingOrder( UI16 charid, SI32 villageunique, SI32 personid, SI32 stockamount, GMONEY money, TCHAR* pszIP, TCHAR* pszPrivateIP, TCHAR* pszMacAddress )
	{
		packetHeader.usSize = sizeof( sDBRequest_StockOfferingOrder );
		packetHeader.usCmd = DBMSG_REQUEST_STOCKOFFERINGORDER;

		usCharID			= charid;
		siVillageUnique		= villageunique;
		siPersonID			= personid;
		siStockAmount		= stockamount;
		siMoney				= money;

		szIP[0]				= '\0';
		szPrivateIP[0]		= '\0';
		szMacAddress[0]		= '\0';

		if(pszIP)			MStrCpy(szIP, pszIP, sizeof(szIP));
		if(pszPrivateIP)	MStrCpy(szPrivateIP, pszPrivateIP, sizeof(szPrivateIP));
		if(pszMacAddress)	MStrCpy(szMacAddress, pszMacAddress, sizeof(szMacAddress));
	}
};

class sDBResponse_StockOfferingOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siStockAmount;
	GMONEY				siMoney;

	GMONEY				siPersonMoney;

	sDBResponse_StockOfferingOrder()
	{
		ZeroMemory( this, sizeof(sDBResponse_StockOfferingOrder) );
	}
};


// �ֽ� û���� ����Ʈ
class sDBRequest_GetStockOfferingOrderList
{
public:
	sPacketHeader		packetHeader;
	SI32				siVillageUnique;

	sDBRequest_GetStockOfferingOrderList( SI32 villageunique )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetStockOfferingOrderList );
		packetHeader.usCmd = DBMSG_REQUEST_GETSTOCKOFFERINGORDERLIST;

		siVillageUnique = villageunique;
	}


};

class sDBResponse_GetStockOfferingOrderList
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siStockAmount;
	GMONEY				siMoney;

	TCHAR				szIP[20];
	TCHAR				szPrivateIP[20];
	TCHAR				szMacAddress[20];

	sDBResponse_GetStockOfferingOrderList()
	{
		ZeroMemory( this, sizeof(sDBResponse_GetStockOfferingOrderList) );
	}

};


// �ֽ� û�� �ֹ� ����
class sDBRequest_ExecuteStockOfferingOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siType;				// 1: �ֽ� ��� ��÷,  2: �ֽ� ��� ��÷ ����

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siStockAmount;
	GMONEY				siMoney;

	TCHAR				szIP[20];
	TCHAR				szPrivateIP[20];
	TCHAR				szMacAddress[20];

	sDBRequest_ExecuteStockOfferingOrder(UI16 id, SI32 type, SI32 villageunique, SI32 personid, SI32 stockamount, GMONEY money, TCHAR* pszIP, TCHAR* pszPrivateIP, TCHAR* pszMacAddress )
	{
		packetHeader.usSize = sizeof( sDBRequest_ExecuteStockOfferingOrder );
		packetHeader.usCmd = DBMSG_REQUEST_EXECUTESTOCKOFFERINGORDER;

		usCharID = id;
		
		siType			= type;
		siVillageUnique	= villageunique;
		siPersonID		= personid;
		siStockAmount	= stockamount;
		siMoney			= money;

		szIP[0]				= '\0';
		szPrivateIP[0]		= '\0';
		szMacAddress[0]		= '\0';

		if(pszIP)			MStrCpy(szIP, pszIP, sizeof(szIP));
		if(pszPrivateIP)	MStrCpy(szPrivateIP, pszPrivateIP, sizeof(szPrivateIP));
		if(pszMacAddress)	MStrCpy(szMacAddress, pszMacAddress, sizeof(szMacAddress));
	}

};

class sDBResponse_ExecuteStockOfferingOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siType;				// 1: �ֽ� ��� ��÷,  2: �ֽ� ��� ��÷ ����

	SI32				siVillageUnique;
	SI32				siPersonID;
	SI32				siStockAmount;
	GMONEY				siMoney;

	TCHAR				szIP[20];
	TCHAR				szPrivateIP[20];
	TCHAR				szMacAddress[20];

	sDBResponse_ExecuteStockOfferingOrder()
	{
		ZeroMemory( this, sizeof(sDBResponse_ExecuteStockOfferingOrder) );
	}

};


class sDBRequest_ResetStockOfferingOrderList
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	sDBRequest_ResetStockOfferingOrderList( SI32 villageunique )
	{
		packetHeader.usSize = sizeof( sDBRequest_ResetStockOfferingOrderList );
		packetHeader.usCmd = DBMSG_REQUEST_RESETSTOCKOFFERINGORDERLIST;

		siVillageUnique = villageunique;


	}
};

class sDBResponse_ResetStockOfferingOrderList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siVillageUnique;

	sDBResponse_ResetStockOfferingOrderList()
	{
		ZeroMemory( this, sizeof( sDBResponse_ResetStockOfferingOrderList ) );
	}
};


//***************************************************************************************************
//
// Class Name 		: sDBRequest_ExchangeFromStock
//
// Last Modified 	: 2007 / 11 / 01 
// Created		 	: �豤��
//
// Function			: [��û] �ֽ� 1�ִ� ���� �� 1�������� �ٲ��ش�.
//
//*************************************************************************************************** 
class sDBRequest_ExchangeFromStock
{
public:
	sPacketHeader	packetHeader;

	/// �ֽ��� ������ �ٲٷ��� �ϴ� ���
	SI32			siCharID;
	/// �ֽ��� ������ �ٲٷ��� �ϴ� ��� PersonID
	SI32			siPersonID;
	/// �ֽ��� �ٲٷ��� �ϴ� ��� 2����й�ȣ
	TCHAR			szSecondPassWord[MAX_PLAYER_NAME];
	/// ���� �ֽ� ����ũ
	SI32			siStockUnique;
	/// �ȷ��� �ϴ� ����
	SI32			siSellAmount;
	/// ���� ���� ����
	SI32			siBankType;
	/// ���� ���� ����
	TCHAR			szBankAccount[MAX_PLAYER_NAME];

	sDBRequest_ExchangeFromStock( SI32 CharID, SI32 PersonID, TCHAR* SecondPassWord,
								  SI32 StockUnique, SI32 SellAmount, SI32 BankType, TCHAR* BankAccount )
	{
		packetHeader.usSize = sizeof( sDBRequest_ExchangeFromStock );
		packetHeader.usCmd = DBMSG_REQUEST_EXCHANGEFROMSTOCK;

		siCharID = CharID;
		siPersonID = PersonID;
		StringCchCopy( szSecondPassWord, MAX_PLAYER_NAME, SecondPassWord );
		siStockUnique = StockUnique;
		siSellAmount = SellAmount;
		siBankType = BankType;
		StringCchCopy( szBankAccount, MAX_PLAYER_NAME, BankAccount );

	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ExchangeFromStock
//
// Last Modified 	: 2007 / 11 / 01 
// Created		 	: �豤��
//
// Function			: [��û] �ֽ� 1�ִ� ���� �� 1�������� �ٲ��ش�.
//
//*************************************************************************************************** 
class sDBResponse_ExchangeFromStock
{
public:
	sPacketHeader		packetHeader;

	/// �����
	SI32				siResult;
	/// ��û�� ���
	SI32				siCharID;
	/// �Ǹ��� �ֽ� ����ũ
	SI32				siStockUnique;
	/// �Ǹ��� ����
	SI32				siSellAmount;
    /// �Ǹ��ϰ� ���� ����(����)
	SI32				siLeftStockAmount;
	/// �Ǹ��ϰ� ���� ������ ��ü �ֽļ�
	SI32				siTotalStockAmount;

	sDBResponse_ExchangeFromStock()
	{
		ZeroMemory( this, sizeof( sDBResponse_ExchangeFromStock ) );
	}
};

// [����] �ʺ��� ���� : �ֽ��� �ֶ�� ��û�Ѵ�
class sDBRequest_GiveStock
{
public:
	sPacketHeader	packetHeader;

	SI32			siCharID;
	SI32			siPersonID;

	SI32			siVillageUnique;	// ��� ������ �ֽ��ΰ�
	SI32			siStockAmount;		// �󸶸� ��� �ϴ°�

	sDBRequest_GiveStock( SI32 para_siCharID, SI32 para_siPersonID, SI32 para_siVillageUnique, SI32 para_siStockAmount )
	{
		packetHeader.usSize	= sizeof( sDBRequest_GiveStock );
		packetHeader.usCmd	= DBMSG_REQUEST_GIVESTOCK;

		siCharID			= para_siCharID;
		siPersonID			= para_siPersonID;

		siVillageUnique		= para_siVillageUnique;	
		siStockAmount		= para_siStockAmount;
	}
};

// [����] �ʺ��� ���� : �ֽ��� �ֶ�� ��û�� ���
class sDBResponse_GiveStock
{
public:
	sPacketHeader	packetHeader;

	SI32			siResult;			// �����

	SI32			siCharID;
	SI32			siPersonID;

	SI32			siVillageUnique;	// ������� �ֽ��ΰ�
	SI32			siStockAmount;		// �󸶸� ��°�

	
	sDBResponse_GiveStock()
	{
		ZeroMemory( this, sizeof( sDBResponse_GiveStock ) );
	}

};

#endif