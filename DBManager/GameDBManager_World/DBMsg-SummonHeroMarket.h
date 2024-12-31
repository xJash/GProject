#ifndef _DBMSGSUMMONHEROMARKET_H
#define _DBMSGSUMMONHEROMARKET_H

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\SummonHeroMarket\SummonHeroMarket.h"

//------------------------------------------
// ���� ���� �񺯻� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_SUMMONHEROMARKET_ORDER_NUM	50


class sDBRequest_SummonHeroMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	sDBRequest_SummonHeroMarketGetManyOrder()
	{
		ZeroMemory( this, sizeof(sDBRequest_SummonHeroMarketGetManyOrder) );

		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketGetManyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_GETMANYORDER;
	}

};

class sDBResponse_SummonHeroMarketGetManyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.
	
	UI16				usCount;							// �ֹ� ����
	cltSummonOrder		clOrder[ GET_MANY_SUMMONHEROMARKET_ORDER_NUM ];

	sDBResponse_SummonHeroMarketGetManyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketGetManyOrder));

		for( SI32 siCount = 0; siCount < GET_MANY_SUMMONHEROMARKET_ORDER_NUM; ++siCount )
			clOrder[siCount].Init();
	}
};



//------------------------------------------
// ��ȯ���� �ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_SummonHeroMarketOrderSell
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

	SI32				siVillageUnique;		// �ֹ��� ���� ������ ��ġ. 

	cltSummonOrder		clOrder;				// DB�� �־�� �� �ֹ��� ����. 

	GMONEY				siTax;					// �����ؾ� �� ����. 

	TCHAR				szSelectPersonName[ MAX_PLAYER_NAME ];	// �����ŷ��� ������ person name 
																// NULL�̸� �����ŷ��ƴ�

	SI16				siPos;
	cltItem				clitem;

//#if defined(_LEON_ADD_SELECTSELL_CODE)
	UI08				uiTradeType;							// �Ϲ� �ŷ� : TRADE_TYPE_NORMAL, ���� �ŷ� : TRADE_TYPE_SELECTIVE
//#endif

	sDBRequest_SummonHeroMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonHeroMarketOrderSell));
	}

	sDBRequest_SummonHeroMarketOrderSell(SI32 id, SI32 villageunique, cltSummonOrder* pclorder, SI32 tax, TCHAR *personname, SI16 pos, cltItem *pclItem, UI08 tradetype )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketOrderSell );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_ORDERSELL;
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


class sDBResponse_SummonHeroMarketOrderSell
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;					// �����.

	SI32				siVillageUnique;			// VillageUnique
	cltSummonOrder		clOrder;					// DB�� ����� �ֹ��� ����. 

	GMONEY				siTax;						// ������ ����. 

	cltMoney			clSummonMarketMoney;		// ��ȯ���� �ŷ��� �����ڱ�
	GMONEY				siPersonMoney;				// person ������ 

	SI16				siPos;						// �κ��丮 ��ġ
	cltItem				clitem;						// ������

	sDBResponse_SummonHeroMarketOrderSell()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketOrderSell));
	}
};

//------------------------------------------
// ��ȯ���� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_SummonHeroMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;	// ��ȯ���� �ŷ��Ұ� ��ġ�� ���� VillageUnique
	cltFee				clFee;				// �����ؾ� �� �纹���� ������ ����


	sDBRequest_SummonHeroMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonHeroMarketSetFee));
	}

	sDBRequest_SummonHeroMarketSetFee( SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketSetFee );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_SETFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_SummonHeroMarketSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;
	SI32				siVillageUnique;	// ��ȯ�����ŷ��Ұ� ��ġ�� ������ VillageUnique
	cltFee				clFee;				// ��ȯ�����ŷ����� �ŷ� ������ ����. 

	sDBResponse_SummonHeroMarketSetFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketSetFee));
	}

};


//------------------------------------------
// ��ȯ�����ŷ��ҿ��� ��ȯ������ �ŷ��� ���� ��û 
//------------------------------------------

class sDBRequest_SummonHeroMarketBuy
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// �ֹ��� person id
	SI32				siVillageUnique;	// �ŷ��� ��û�ϴ� ������ VillageUnique. 	

	SI32				siOrderIndex;		// ������ ��ȯ������ �ֹ� ��ȣ
	GMONEY				siPrice;			// �ŷ� �ܰ�.

	sDBRequest_SummonHeroMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonHeroMarketBuy));
	}

	sDBRequest_SummonHeroMarketBuy(SI32 id, SI32 personid, SI32 villageunique, SI32 orderindex, GMONEY price )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketBuy );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_BUY;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;		
		siOrderIndex	= orderindex;
		siPrice			= price;
	}
};


class sDBResponse_SummonHeroMarketBuy
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
	cltSummon			clSummon;			// �ŷ��� ��ȯ���� ����

	SI32				siSellerPersonID;	// ������ PersonID
	cltMoney			clSellerBankMoney;	// ������ ���� �ܰ�

	sDBResponse_SummonHeroMarketBuy()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketBuy));
	}
};



//------------------------------------------
//  ���� �ֹ� ������ ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_SummonHeroMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ����� �Ǵ� Person

	sDBRequest_SummonHeroMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonHeroMarketMyOrder));
	}

	sDBRequest_SummonHeroMarketMyOrder(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketMyOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_MYORDER;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_SummonHeroMarketMyOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;											// �����.

	UI16				usCount;
	cltSummonOrder		clMyOrder[ MAX_SUMMONHEROMARKET_ORDER_PER_PERSON ];		// ���� �ֹ����� 
	
	sDBResponse_SummonHeroMarketMyOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketMyOrder));
	}
};


//------------------------------------------
// ��ȯ���� �ֹ��� ����Ѵ� 
//------------------------------------------
class sDBRequest_SummonHeroMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ����� �Ǵ� Person
	SI32				siOrderIndex;	// �ֹ���ȣ 

	sDBRequest_SummonHeroMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_SummonHeroMarketCancelOrder));
	}

	sDBRequest_SummonHeroMarketCancelOrder( SI32 id, SI32 personid, SI32 orderindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_SummonHeroMarketCancelOrder );
		packetHeader.usCmd = DBMSG_REQUEST_SUMMONHEROMARKET_CANCELORDER;
		usCharID		= id;

		siPersonID		= personid;
		siOrderIndex	= orderindex;
	}

};


class sDBResponse_SummonHeroMarketCancelOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person
	
	SI32				siOrderIndex;		// ������ �ֹ� ��ȣ 
	cltSummon			clSummon;			// ��ȯ���� ���� 

	sDBResponse_SummonHeroMarketCancelOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_SummonHeroMarketCancelOrder));
	}
};


//------------------------------------------
// �ֹ� ������ �����. 
//------------------------------------------
class sDBRequest_ReduceSummonHeroOrderPrice
{
public:
	sPacketHeader			packetHeader;

	int						arrayindex;
	cltSummonOrder			clOrder;

	sDBRequest_ReduceSummonHeroOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ReduceSummonHeroOrderPrice));
	}

	sDBRequest_ReduceSummonHeroOrderPrice( int index, cltSummonOrder* pclorder)
	{
		packetHeader.usSize = sizeof( sDBRequest_ReduceSummonHeroOrderPrice );
		packetHeader.usCmd = DBMSG_REQUEST_REDUCESUMMONHEROORDERPRICE;

		arrayindex = index;
		clOrder.Set(pclorder);
	}
};


class sDBResponse_ReduceSummonHeroOrderPrice
{
public:
	sPacketHeader			packetHeader;
	SI32					siResult;			// �����.

	int						arrayindex;
	cltSummonOrder			clOrder;			// DB�� ����� �ֹ��� ����. 

	sDBResponse_ReduceSummonHeroOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ReduceSummonHeroOrderPrice));
	}
};

#endif
