#ifndef _MSGTYPEHORSEMARKET_H
#define _MSGTYPEHORSEMARKET_H

#include "..\HorseMarket\HorseMarket.h"

// �纹�� �� �ֹ� ���� 
class cltGameMsgRequest_HorseMarketMyAccount
{
public:
	cltGameMsgRequest_HorseMarketMyAccount()
	{
	}

};

class cltGameMsgResponse_HorseMarketMyAccount
{
public:
	cltHorseOrder	clHorseOrder;

	cltGameMsgResponse_HorseMarketMyAccount( cltHorseOrder *pclHorseOrder )
	{
		clHorseOrder.Set( pclHorseOrder );
	}

};

// �纹�� �ֹ� ����Ʈ
class cltGameMsgRequest_HorseMarketOrderList
{
public:
	SI32	siHorseUnique;	
	SI32	siPriceType;

	cltGameMsgRequest_HorseMarketOrderList( SI32 horseUnique, SI32 pricetype )
	{
		siHorseUnique = horseUnique;
		siPriceType = pricetype;
	}

};

class cltGameMsgResponse_HorseMarketOrderList
{
public:
	UI16			usCount;
#ifdef _SAFE_MEMORY
	NSafeTArray<cltHorseOrder, MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER>		clHorseOrder;
#else
	cltHorseOrder	clHorseOrder[ MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER ];
#endif

	cltGameMsgResponse_HorseMarketOrderList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_HorseMarketOrderList ) );
	}

	SI32			GetTotalSize() {
		return sizeof( cltHorseOrder ) * usCount + 8;
	}

};

// �纹�� �� �ȱ� 
class cltGameMsgRequest_HorseMarketSellHorse
{
public:
	SI16			siHorseIndex;				// �� ���� 
	GMONEY			siPrice;					// �Ǹ� ���� 
	

	cltGameMsgRequest_HorseMarketSellHorse( SI16 horseindex, GMONEY price )
	{
		siHorseIndex = horseindex;
		siPrice = price;
	}
};

class cltGameMsgResponse_HorseMarketSellHorse
{
public:
	SI16		siHorseIndex;
	cltHorseOrder	clHorseOrder;

	cltGameMsgResponse_HorseMarketSellHorse()
	{
		clHorseOrder.Init();
	}

	cltGameMsgResponse_HorseMarketSellHorse( SI16 horseindex, cltHorseOrder *pclHorseOrder )
	{
		siHorseIndex = horseindex;
		clHorseOrder.Set( pclHorseOrder );
	}
};



// �纹�� �� ���� 
class cltGameMsgRequest_HorseMarketBuyHorse
{
public:
	SI32	siOrderIndex;
	SI32	siSellerPersonID;

	cltGameMsgRequest_HorseMarketBuyHorse( SI32 orderindex, SI32 sellerpersonid )
	{
		siOrderIndex = orderindex;
		siSellerPersonID = sellerpersonid;
	}

};

class cltGameMsgResponse_HorseMarketBuyHorse
{
public:
	SI16			siHorseIndex;
	cltHorse		clHorse;
	SI32			siOrderIndex;

	cltGameMsgResponse_HorseMarketBuyHorse( SI16 horseindex, cltHorse *pclHorse, SI32 orderIndex )
	{
		siHorseIndex = horseindex;
		if(pclHorse)	clHorse.Set( pclHorse );
		siOrderIndex = orderIndex;
	}


};

class cltGameMsgRequest_HorseMarketOutHorse
{
public:
	cltGameMsgRequest_HorseMarketOutHorse()
	{
	}

};

class cltGameMsgResponse_HorseMarketOutHorse
{
public:
	SI16		siHorseIndex;
	cltHorse		clHorse;

	cltGameMsgResponse_HorseMarketOutHorse( SI16 horseindex, cltHorse *pclHorse )
	{
		siHorseIndex = horseindex;
		if(pclHorse)	clHorse.Set( pclHorse );
	}
};


// �纹�� ������ ����
class cltGameMsgRequest_HorseMarketSetFee
{
public:
	cltFee				clFee;						// �ŷ� ������ 

	cltGameMsgRequest_HorseMarketSetFee()
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_HorseMarketSetFee ) );
	}

	cltGameMsgRequest_HorseMarketSetFee( cltFee* pclFee )
	{
		clFee.Set( pclFee );
	}

};


#endif