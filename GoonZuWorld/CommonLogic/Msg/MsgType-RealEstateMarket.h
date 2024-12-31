#ifndef _MSGTYPEREALESTATEMARKET_H
#define _MSGTYPEREALESTATEMARKET_H

#include "..\RealEstate\RealEstate.h"

// �Ű� �� �ֹ� ���� 
class cltGameMsgRequest_RealEstateMarketMyOrder
{
public:
	cltGameMsgRequest_RealEstateMarketMyOrder()
	{
	}

};

class cltGameMsgResponse_RealEstateMarketMyOrder
{
public:
	UI16				usCount;
	cltRealEstateOrder	clMyOrder[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];

	cltGameMsgResponse_RealEstateMarketMyOrder()
	{
		usCount = 0;
	}

};

// �Ű� �ֹ� ����Ʈ
class cltGameMsgRequest_RealEstateMarketOrderList
{
public:
	int a;

	cltGameMsgRequest_RealEstateMarketOrderList()
	{

	}

};

class cltGameMsgResponse_RealEstateMarketOrderList
{
public:
	UI16				usCount;
	cltRealEstateOrder	clOrder[ MAX_REALESTATEMARKET_RESPONSE_ORDER_NUMBER ];

	cltGameMsgResponse_RealEstateMarketOrderList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_RealEstateMarketOrderList ) );
	}

	SI32			GetTotalSize() {
		return sizeof( cltRealEstateOrder ) * usCount + 8;
	}

};

// �Ű� �ε��� �ȱ� 
class cltGameMsgRequest_RealEstateMarketSell
{
public:
	SI32			siVillageUnique;
	SI32			siHouseIndex;
	GMONEY			siPrice;
	

	cltGameMsgRequest_RealEstateMarketSell( SI32 villageunique, SI32 houseindex, GMONEY price )
	{
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
		siPrice = price;
	}
};

class cltGameMsgResponse_RealEstateMarketSell
{
public:
	cltRealEstateOrder	clRealEstateOrder;

	cltGameMsgResponse_RealEstateMarketSell()
	{
		clRealEstateOrder.Init();
	}

	cltGameMsgResponse_RealEstateMarketSell( cltRealEstateOrder *pclOrder )
	{
		clRealEstateOrder.Set( pclOrder );
	}
};



// �Ű� �ε��� ���� 
class cltGameMsgRequest_RealEstateMarketBuy
{
public:
	SI32	siOrderIndex;
	SI32	siVillageUnique;
	SI32	siHouseIndex;

	cltGameMsgRequest_RealEstateMarketBuy( SI32 orderindex, SI32 villageunique, SI32 houseindex )
	{
		siOrderIndex = orderindex;
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
	}

};

class cltGameMsgResponse_RealEstateMarketBuy
{
public:
	SI32			siOrderIndex;
	SI32			siVillageUnique;
	SI32			siHouseIndex;
	cltRentContract	clContract;

	cltGameMsgResponse_RealEstateMarketBuy( SI32 orderIndex, SI32 villageunique, SI32 houseindex, cltRentContract *pContract )
	{
		siOrderIndex = orderIndex;
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
		clContract.Set( pContract );
	}


};

class cltGameMsgRequest_RealEstateMarketCancelOrder
{
public:
	SI32			siVillageUnique;
	SI32			siHouseIndex;

	cltGameMsgRequest_RealEstateMarketCancelOrder( SI32 villageunique, SI32 houseindex )
	{
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
	}

};

class cltGameMsgResponse_RealEstateMarketCancelOrder
{
public:

	SI32			siOrderIndex;
	SI32			siVillageUnique;
	SI32			siHouseIndex;		

	cltGameMsgResponse_RealEstateMarketCancelOrder( SI32 orderindex, SI32 villageunique, SI32 houseindex )
	{
		siOrderIndex = orderindex;
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
	}
};


// �Ű� ������ ����
class cltGameMsgRequest_RealEstateMarketSetFee
{
public:
	cltFee				clFee;						// �ŷ� ������ 

	cltGameMsgRequest_RealEstateMarketSetFee()
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_RealEstateMarketSetFee ) );
	}

	cltGameMsgRequest_RealEstateMarketSetFee( cltFee* pclFee )
	{
		clFee.Set( pclFee );
	}

};

// �ε��� �� ���� ��û 
class cltGameMsgRequest_RealEstateMarketDetailInfo
{
public:
	SI32				siVillageUnique;
	SI32				siHouseIndex;

	cltGameMsgRequest_RealEstateMarketDetailInfo( SI32 villageunique, SI32 houseindex )
	{
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
	}
};

class cltGameMsgResponse_RealEstateMarketDetailInfo
{
public:
	SI32				siVillageUnique;
	SI32				siHouseIndex;

	GMONEY				siCurrentRentFee;
	GMONEY				siRentFee;
	SI32				siRentPeriod;
	cltDate				clContractDate;

	SI32				siItemNum;
	SI32				siStableNum;
	SI32				siHorseNum;

	cltGameMsgResponse_RealEstateMarketDetailInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_RealEstateMarketDetailInfo ) );
	}

};

#endif