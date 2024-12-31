#ifndef _DBMSGSUMMONMARKET_H
#define _DBMSGSUMMONMARKET_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\SummonMarket\SummonMarket.h"

//------------------------------------------
// ���� ���� ��ȯ���ŷ��� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_SUMMONMARKET_ORDER_NUM	50


class sDBRequest_SummonMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBRequest_SummonMarketGetManyOrder()
	{
		ZeroMemory( this, sizeof(sDBRequest_SummonMarketGetManyOrder) );

		packetHeader.usSize = sizeof( sDBRequest_SummonMarketGetManyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_GETMANYORDER;
	}

};

class sDBResponse_SummonMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.
	
	UI16				usCount;							// �ֹ� ����
	cltSummonOrder		clOrder[ GET_MANY_SUMMONMARKET_ORDER_NUM ];

	sDBResponse_SummonMarketGetManyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketGetManyOrder));
	}
};



//------------------------------------------
// ��ȯ�� �ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_SummonMarketOrderSell
{
public:
//#if defined(_LEON_ADD_SELECTSELL_CODE)
	enum {
        TRADE_TYPE_NORMAL = 1,
		TRADE_TYPE_SELECTIVE = 2,
	};
//#endif

	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;						// �ֹ��� ���� ������ ��ġ. 

	cltSummonOrder		clOrder;								// DB�� �־�� �� �ֹ��� ����. 

	GMONEY				siTax;									// �����ؾ� �� ����. 

	TCHAR				szSelectPersonName[ MAX_PLAYER_NAME ];	// �����ŷ��� ������ person name 
																// NULL�̸� �����ŷ��ƴ�

	SI16				siPos;
	cltItem				clitem;

//#if defined(_LEON_ADD_SELECTSELL_CODE)
	UI08				uiTradeType;							// �Ϲ� �ŷ� : TRADE_TYPE_NORMAL, ���� �ŷ� : TRADE_TYPE_SELECTIVE
//#endif

	sDBRequest_SummonMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonMarketOrderSell));
	}

	sDBRequest_SummonMarketOrderSell(SI32 id, SI32 villageunique, cltSummonOrder* pclorder, GMONEY tax, TCHAR *personname, SI16 pos, cltItem *pclItem, UI08 tradetype )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonMarketOrderSell );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_ORDERSELL;
		usCharID		= id;

		siVillageUnique	= villageunique;
		clOrder.Set( pclorder );
		siTax			= tax;

		memcpy( szSelectPersonName, personname, MAX_PLAYER_NAME );
		szSelectPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

		siPos = pos;
		clitem.Set( pclItem );

//#if defined(_LEON_ADD_SELECTSELL_CODE)
		uiTradeType = tradetype;
//#endif
	}
};


class sDBResponse_SummonMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	SI32				siVillageUnique;			// VillageUnique
	cltSummonOrder		clOrder;					// DB�� ����� �ֹ��� ����. 

	GMONEY				siTax;						// ������ ����. 

	cltMoney			clSummonMarketMoney;		// ��ȯ�� �ŷ��� �����ڱ�
	GMONEY				siPersonMoney;				// person ������ 

	SI16				siPos;						// �κ��丮 ��ġ
	cltItem				clitem;						// ������


	sDBResponse_SummonMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketOrderSell));
	}
};

//------------------------------------------
// ��ȯ�� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_SummonMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;	// ��ȯ�� �ŷ��Ұ� ��ġ�� ���� VillageUnique
	cltFee				clFee;				// �����ؾ� �� �纹���� ������ ����


	sDBRequest_SummonMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonMarketSetFee));
	}

	sDBRequest_SummonMarketSetFee( SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonMarketSetFee );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_SETFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_SummonMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;
	SI32				siVillageUnique;	// ��ȯ���ŷ��Ұ� ��ġ�� ������ VillageUnique
	cltFee				clFee;				// ��ȯ���ŷ����� �ŷ� ������ ����. 

	sDBResponse_SummonMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketSetFee));
	}

};


//------------------------------------------
// ��ȯ���ŷ��ҿ��� ��ȯ���� �ŷ��� ���� ��û 
//------------------------------------------

class sDBRequest_SummonMarketBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// �ֹ��� person id
	SI32				siVillageUnique;	// �ŷ��� ��û�ϴ� ������ VillageUnique. 	

	SI32				siOrderIndex;		// ������ ��ȯ���� �ֹ� ��ȣ
	GMONEY				siPrice;			// �ŷ� �ܰ�.

	sDBRequest_SummonMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonMarketBuy));
	}

	sDBRequest_SummonMarketBuy(SI32 id, SI32 personid, SI32 villageunique, SI32 orderindex, GMONEY price )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonMarketBuy );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_BUY;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;		
		siOrderIndex	= orderindex;
		siPrice			= price;
	}
};


class sDBResponse_SummonMarketBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������ Person 

	GMONEY				siMoney;			// �ŷ� �� ������ 
	SI32				siVillageUnique;	// Request���� �Էµ� VillageUnique
	SI32				siOrderIndex;		// �ֹ� ��ȣ

	GMONEY				siTradePrice;		// ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0)
	cltSummon			clSummon;			// �ŷ��� ��ȯ�� ����

	SI32				siSellerPersonID;	// ������ PersonID
	cltMoney			clSellerBankMoney;	// ������ ���� �ܰ�

	sDBResponse_SummonMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketBuy));
	}
};



//------------------------------------------
//  ���� �ֹ� ������ ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_SummonMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� Person

	sDBRequest_SummonMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonMarketMyOrder));
	}

	sDBRequest_SummonMarketMyOrder(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonMarketMyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_MYORDER;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_SummonMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;											// �����.

	UI16				usCount;
	cltSummonOrder		clMyOrder[ MAX_SUMMONMARKET_ORDER_PER_PERSON ];		// ���� �ֹ����� 
	
	sDBResponse_SummonMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketMyOrder));
	}
};


//------------------------------------------
// ��ȯ�� �ֹ��� ����Ѵ� 
//------------------------------------------
class sDBRequest_SummonMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ����� �Ǵ� Person
	SI32				siOrderIndex;	// �ֹ���ȣ 

	sDBRequest_SummonMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonMarketCancelOrder));
	}

	sDBRequest_SummonMarketCancelOrder( SI32 id, SI32 personid, SI32 orderindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonMarketCancelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONMARKET_CANCELORDER;
		usCharID		= id;

		siPersonID		= personid;
		siOrderIndex	= orderindex;
	}

};


class sDBResponse_SummonMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person
	
	SI32				siOrderIndex;		// ������ �ֹ� ��ȣ 
	cltSummon			clSummon;			// ��ȯ�� ���� 

	sDBResponse_SummonMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonMarketCancelOrder));
	}
};


//------------------------------------------
// �ֹ� ������ �����. 
//------------------------------------------
class sDBRequest_ReduceSummonOrderPrice
{
public:
	sPacketHeader			packetHeader;

	int						arrayindex;
	cltSummonOrder			clOrder;

	sDBRequest_ReduceSummonOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ReduceSummonOrderPrice));
	}

	sDBRequest_ReduceSummonOrderPrice( int index, cltSummonOrder* pclorder)
	{
		packetHeader.usSize = sizeof( sDBRequest_ReduceSummonOrderPrice );
		packetHeader.usCmd = DBMSG_REQUEST_REDUCESUMMONORDERPRICE;

		arrayindex = index;
		clOrder.Set(pclorder);
	}
};


class sDBResponse_ReduceSummonOrderPrice
{
public:
	sPacketHeader			packetHeader;
	SI32					siResult;			// �����.

	int						arrayindex;
	cltSummonOrder			clOrder;			// DB�� ����� �ֹ��� ����. 

	sDBResponse_ReduceSummonOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ReduceSummonOrderPrice));
	}
};

#endif
