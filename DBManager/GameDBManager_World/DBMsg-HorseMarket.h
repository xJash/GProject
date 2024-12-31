#ifndef _DBMSGHORSEMARKET_H
#define _DBMSGHORSEMARKET_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\HorseMarket\HorseMarket.h"

//------------------------------------------
// ���� ���� �纹�� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_HORSEMARKET_ORDER_NUM	50


class sDBRequest_HorseMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBRequest_HorseMarketGetManyOrder()
	{
		ZeroMemory( this, sizeof(sDBRequest_HorseMarketGetManyOrder) );

		packetHeader.usSize = sizeof( sDBRequest_HorseMarketGetManyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_GETMANYORDER;
	}

};

class sDBResponse_HorseMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.
	
	UI16				usCount;							// �ֹ� ����
	cltHorseOrder		clHorseOrder[ GET_MANY_HORSEMARKET_ORDER_NUM ];

	sDBResponse_HorseMarketGetManyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketGetManyOrder));
	}
};




//------------------------------------------
// �纹�� �ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_HorseMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// �ֹ��� ���� ������ ��ġ. 

	SI16				siHorseIndex;			// �� ����
	cltHorseOrder		clHorseOrder;			// DB�� �־�� �� �ֹ��� ����. 

	GMONEY				siTax;					// �����ؾ� �� ����. 

	sDBRequest_HorseMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBRequest_HorseMarketOrderSell));
	}

	sDBRequest_HorseMarketOrderSell(SI32 id, SI32 villageunique, SI16 horseindex, cltHorseOrder* pclorder, GMONEY tax )
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseMarketOrderSell );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_ORDERSELL;
		usCharID		= id;

		siVillageUnique	= villageunique;
		siHorseIndex = horseindex;
		clHorseOrder.Set( pclorder );
		siTax			= tax;
	}
};


class sDBResponse_HorseMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// VillageUnique
	SI16				siHorseIndex;
	cltHorseOrder		clHorseOrder;		// DB�� ����� �ֹ��� ����. 

	GMONEY				siTax;				// ������ ����. 

	cltMoney			clHorseMarketMoney;	// �纹�� �����ڱ�
	GMONEY				siPersonMoney;		// person ������ 

	sDBResponse_HorseMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketOrderSell));
	}
};

//------------------------------------------
// �纹�� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_HorseMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;	// �纹�ð� ��ġ�� ���� VillageUnique
	cltFee				clFee;				// �����ؾ� �� �纹���� ������ ����


	sDBRequest_HorseMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_HorseMarketSetFee));
	}

	sDBRequest_HorseMarketSetFee( SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee )
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseMarketSetFee );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_SETFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_HorseMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;
	SI32				siVillageUnique;	// �纹�ð� ��ġ�� ������ VillageUnique
	cltFee				clFee;				// �纹���� �ŷ� ������ ����. 

	sDBResponse_HorseMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketSetFee));
	}

};


//------------------------------------------
// �纹�ÿ��� ���� �ŷ��� ���� ��û 
//------------------------------------------

class sDBRequest_HorseMarketBuyHorse
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// �ֹ��� person id
	SI16				siHorseIndex;		// �� ����
	SI32				siVillageUnique;	// �ŷ��� ��û�ϴ� ������ VillageUnique. 	
	
	SI32				siOrderIndex;		// ������ ���� �ֹ� ��ȣ 

	GMONEY				siPrice;			// �ŷ� �ܰ�.

	sDBRequest_HorseMarketBuyHorse()
	{
		ZeroMemory(this, sizeof(sDBRequest_HorseMarketBuyHorse));
	}

	sDBRequest_HorseMarketBuyHorse(SI32 id, SI32 personid, SI16 horseindex, SI32 villageunique, SI32 orderindex, GMONEY price )
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseMarketBuyHorse );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_BUYHORSE;
		usCharID		= id;

		siPersonID		= personid;
		siHorseIndex	= horseindex;
		siVillageUnique	= villageunique;		
		siOrderIndex	= orderindex;
		siPrice			= price;
	}
};


class sDBResponse_HorseMarketBuyHorse
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
 	cltHorse			clHorse;			// �ŷ� �� ���� 
	SI16				siHorseIndex;		// �� ���� 
	
	SI32				siSellerPersonID;	// ������ PersonID
	cltMoney			clSellerBankMoney;	// ������ ���� �ܰ�

	sDBResponse_HorseMarketBuyHorse()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketBuyHorse));
	}
};


//------------------------------------------
// �纹�� ���� �ֹ� ������ ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_HorseMarketMyAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� Person

	sDBRequest_HorseMarketMyAccount()
	{
		ZeroMemory(this, sizeof(sDBRequest_HorseMarketMyAccount));
	}

	sDBRequest_HorseMarketMyAccount(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseMarketMyAccount );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_MYACCOUNT;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_HorseMarketMyAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltHorseOrder		clHorseOrder;		// �� �ֹ� ���� 
	
	sDBResponse_HorseMarketMyAccount()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketMyAccount));
	}
};


//------------------------------------------
// �纹�� â��κ��� ���� ������ ���� ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_HorseMarketOutHorse
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ����� �Ǵ� Person

	SI16				siHorseIndex;	// �� ����

	sDBRequest_HorseMarketOutHorse()
	{
		ZeroMemory(this, sizeof(sDBRequest_HorseMarketOutHorse));
	}

	sDBRequest_HorseMarketOutHorse(SI32 id, SI32 personid, SI16 horseindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HorseMarketOutHorse );
		packetHeader.usCmd = DBMSG_REQUEST_HORSEMARKET_OUTHORSE;
		usCharID		= id;

		siPersonID		= personid;

		siHorseIndex	= horseindex;
	}

};


class sDBResponse_HorseMarketOutHorse
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person
	
	SI32				siOrderIndex;		// ������ �ֹ� ��ȣ 
	cltHorse			clHorse;			// �� ���� 
	SI16				siHorseIndex;		// �� ���� 

	sDBResponse_HorseMarketOutHorse()
	{
		ZeroMemory(this, sizeof(sDBResponse_HorseMarketOutHorse));
	}
};


//------------------------------------------
// �ֹ� ������ �����. 
//------------------------------------------
class sDBRequest_ReduceHorseOrderPrice
{
public:
	sPacketHeader		packetHeader;

	int					arrayindex;
	cltHorseOrder		clOrder;

	sDBRequest_ReduceHorseOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ReduceHorseOrderPrice));
	}

	sDBRequest_ReduceHorseOrderPrice( int index, cltHorseOrder* pclorder)
	{
		packetHeader.usSize = sizeof( sDBRequest_ReduceHorseOrderPrice );
		packetHeader.usCmd = DBMSG_REQUEST_REDUCEHORSEORDERPRICE;

		arrayindex = index;
		clOrder.Set(pclorder);
	}
};


class sDBResponse_ReduceHorseOrderPrice
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	int					arrayindex;
	cltHorseOrder		clOrder;			// DB�� ����� �ֹ��� ����. 

	sDBResponse_ReduceHorseOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ReduceHorseOrderPrice));
	}
};

#endif
