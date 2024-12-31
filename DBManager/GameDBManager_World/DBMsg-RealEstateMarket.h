#ifndef _DBMSGREALESTATEMARKET_H
#define _DBMSGREALESTATEMARKET_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\RealEstate\RealEstate.h"

//------------------------------------------
// ���� ���� �Ű� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_REALESTATEMARKET_ORDER_NUM	50


class sDBRequest_RealEstateMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBRequest_RealEstateMarketGetManyOrder()
	{
		ZeroMemory( this, sizeof(sDBRequest_RealEstateMarketGetManyOrder) );

		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketGetManyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_GETMANYORDER;
	}

};

class sDBResponse_RealEstateMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.
	
	UI16				usCount;							// �ֹ� ����
	cltRealEstateOrder	clOrder[ GET_MANY_REALESTATEMARKET_ORDER_NUM ];

	sDBResponse_RealEstateMarketGetManyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketGetManyOrder));
	}
};




//------------------------------------------
// �Ű� �ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_RealEstateMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// �ֹ��� ���� ������ ��ġ. 

	cltRealEstateOrder	clOrder;				// DB�� �־�� �� �ֹ��� ����. 

	GMONEY				siTax;					// �����ؾ� �� ����. 

	sDBRequest_RealEstateMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealEstateMarketOrderSell));
	}

	sDBRequest_RealEstateMarketOrderSell(SI32 id, SI32 villageunique, cltRealEstateOrder* pclorder, GMONEY tax)
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketOrderSell );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_ORDERSELL;
		usCharID		= id;

		siVillageUnique	= villageunique;
		clOrder.Set( pclorder );
		siTax			= tax;
	}
};


class sDBResponse_RealEstateMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	SI32				siVillageUnique;			// VillageUnique
	cltRealEstateOrder	clOrder;					// DB�� ����� �ֹ��� ����. 

	GMONEY				siTax;						// ������ ����. 

	cltMoney			clRealEstateMarketMoney;	// �Ű� �����ڱ�
	GMONEY				siPersonMoney;				// person ������ 

	sDBResponse_RealEstateMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketOrderSell));
	}
};

//------------------------------------------
// �纹�� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_RealEstateMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;	// �纹�ð� ��ġ�� ���� VillageUnique
	cltFee				clFee;				// �����ؾ� �� �纹���� ������ ����


	sDBRequest_RealEstateMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealEstateMarketSetFee));
	}

	sDBRequest_RealEstateMarketSetFee( SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee )
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketSetFee );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_SETFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_RealEstateMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;
	SI32				siVillageUnique;	// �纹�ð� ��ġ�� ������ VillageUnique
	cltFee				clFee;				// �纹���� �ŷ� ������ ����. 

	sDBResponse_RealEstateMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketSetFee));
	}

};


//------------------------------------------
// �Ű����� �ε����� �ŷ��� ���� ��û 
//------------------------------------------

class sDBRequest_RealEstateMarketBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// �ֹ��� person id
	SI32				siVillageUnique;	// �ŷ��� ��û�ϴ� ������ VillageUnique. 	

	SI32				siOrderIndex;		// ������ �ε����� �ֹ� ��ȣ 
	SI32				siHouseVillage;		// ������ �ε����� ��ġ�� ���� 
	SI32				siHouseIndex;		// ������ �ε����� ������ȣ 
	GMONEY				siPrice;			// �ŷ� �ܰ�.

	sDBRequest_RealEstateMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealEstateMarketBuy));
	}

	sDBRequest_RealEstateMarketBuy(SI32 id, SI32 personid, SI32 villageunique, SI32 orderindex, SI32 housevillage, SI32 houseindex, GMONEY price )
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketBuy );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_BUY;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;		
		siOrderIndex	= orderindex;
		siHouseVillage  = housevillage;
		siHouseIndex	= houseindex;
		siPrice			= price;
	}
};


class sDBResponse_RealEstateMarketBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������ Person 
	TCHAR				szPersonName[ MAX_PLAYER_NAME ];
	GMONEY				siMoney;			// �ŷ� �� ������ 
	SI32				siVillageUnique;	// Request���� �Էµ� VillageUnique
	SI32				siOrderIndex;		// �ֹ� ��ȣ

	GMONEY				siTradePrice;		// ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0)
 	SI32				siHouseVillage;		// �ŷ� �ε��� ��ġ ���� 
	SI32				siHouseIndex;		// �ŷ� �ε��� ���� ��ȣ
	
	SI32				siSellerPersonID;	// ������ PersonID
	cltMoney			clSellerBankMoney;	// ������ ���� �ܰ�

	sDBResponse_RealEstateMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketBuy));
	}
};


//------------------------------------------
// �Ű� ���� �ֹ� ������ ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_RealEstateMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� Person

	sDBRequest_RealEstateMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealEstateMarketMyOrder));
	}

	sDBRequest_RealEstateMarketMyOrder(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketMyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_MYORDER;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_RealEstateMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;											// �����.

	UI16				usCount;
	cltRealEstateOrder	clMyOrder[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];		// ���� �ֹ����� 
	
	sDBResponse_RealEstateMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketMyOrder));
	}
};


//------------------------------------------
// �Ű� �ֹ��� ����Ѵ� 
//------------------------------------------
class sDBRequest_RealEstateMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ����� �Ǵ� Person
	SI32				siVillageUnique;
	SI32				siHouseIndex;

	sDBRequest_RealEstateMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_RealEstateMarketCancelOrder));
	}

	sDBRequest_RealEstateMarketCancelOrder( SI32 id, SI32 personid, SI32 villageunique, SI32 houseindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketCancelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_CANCELORDER;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique = villageunique;
		siHouseIndex    = houseindex;
	}

};


class sDBResponse_RealEstateMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person
	
	SI32				siOrderIndex;		// ������ �ֹ� ��ȣ 
	SI32				siVillageUnique;
	SI32				siHouseIndex;

	sDBResponse_RealEstateMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_RealEstateMarketCancelOrder));
	}
};


//------------------------------------------
// �ֹ� ������ �����. 
//------------------------------------------
class sDBRequest_ReduceRealEstateOrderPrice
{
public:
	sPacketHeader			packetHeader;

	int						arrayindex;
	cltRealEstateOrder		clOrder;

	sDBRequest_ReduceRealEstateOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ReduceRealEstateOrderPrice));
	}

	sDBRequest_ReduceRealEstateOrderPrice( int index, cltRealEstateOrder* pclorder)
	{
		packetHeader.usSize = sizeof( sDBRequest_ReduceRealEstateOrderPrice );
		packetHeader.usCmd = DBMSG_REQUEST_REDUCEREALESTATEORDERPRICE;

		arrayindex = index;
		clOrder.Set(pclorder);
	}
};


class sDBResponse_ReduceRealEstateOrderPrice
{
public:
	sPacketHeader			packetHeader;
	SI32					siResult;			// �����.

	int						arrayindex;
	cltRealEstateOrder		clOrder;			// DB�� ����� �ֹ��� ����. 

	sDBResponse_ReduceRealEstateOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ReduceRealEstateOrderPrice));
	}
};

class sDBRequest_RealEstateMarketDelOrder
{
public:
	sPacketHeader			packetHeader;
	
	SI32					siOrderIndex;
	SI32					siPersonID;

	sDBRequest_RealEstateMarketDelOrder( SI32 orderindex, SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_RealEstateMarketDelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_REALESTATEMARKET_DELORDER;

		siOrderIndex = orderindex;
		siPersonID = personid;
	}

};

class sDBResponse_RealEstateMarketDelOrder
{
public:
	sPacketHeader			packetHeader;
	SI32					siResult;			// �����.

	SI32					siOrderIndex;
	SI32					siPersonID;

	sDBResponse_RealEstateMarketDelOrder()
	{
		ZeroMemory( this, sizeof( sDBResponse_RealEstateMarketDelOrder ) );
	}
};


#endif
