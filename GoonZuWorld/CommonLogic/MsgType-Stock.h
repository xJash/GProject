#ifndef _MSGTYPESTOCK_H
#define _MSGTYPESTOCK_H

#include "../common/StockOfferingManager/StockOfferingManager.h"
#include "../CommonLogic/TradeOrder/TradeOrder.h"


//-----------------------------------------
// ������ �÷� ���� �ֽ� �ֹ� ������ ���� ������ ���� ��û�ϰ� �����ش�. 
//------------------------------------------
class cltGameMsgRequest_StockOrderInfo
{
public:
	SI16 siVillageUnique;	// ����� �Ǵ� ������ ����ũ. 
	//SI16 siOrderMode;		// ���� �ֹ��� ã�°�. ���� �ֹ��� ã�°� ?

	cltGameMsgRequest_StockOrderInfo(SI16 villageunique)
	{
		siVillageUnique = villageunique;
		//siOrderMode		= ordermode;
	}
};


class cltGameMsgResponse_StockOrderInfo
{
public:
	// SI16 siOrderMode;		// ���� �ֹ��� ã�°�. ���� �ֹ��� ã�°� ?

#ifdef _SAFE_MEMORY
	NSafeTArray<cltTradeOrder, MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM>		clSellTradeOrder;
	NSafeTArray<cltTradeOrder, MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM>		clBuyTradeOrder;
#else
	cltTradeOrder		clSellTradeOrder[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];	// ���� �ֹ� ����. 
	cltTradeOrder		clBuyTradeOrder[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];	// ���� �ֹ� ����. 
#endif
	
	GMONEY				siAverageSell;
	GMONEY				siAverageBuy;

	cltGameMsgResponse_StockOrderInfo(cltTradeOrder* pclSellOrder , cltTradeOrder * pclBuyOrder , GMONEY	AverageSell,GMONEY AverageBuy )
	{
		//siOrderMode	= ordermode;
#ifdef _SAFE_MEMORY
		clSellTradeOrder.ZeroMem();
		clBuyTradeOrder.ZeroMem();

		clSellTradeOrder.MemCpy( pclSellOrder );
		clBuyTradeOrder.MemCpy( pclBuyOrder );
#else
		memcpy( clSellTradeOrder,pclSellOrder,sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
		memcpy( clBuyTradeOrder,pclBuyOrder,sizeof(cltTradeOrder) * MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM );
#endif
		
		siAverageSell = AverageSell;
		siAverageBuy = AverageBuy;

	}
};


// ���� ���� ���� ������ ������ ��´� 
class cltGameMsgResponse_StockBidVillageList
{
public:

	UI16			usCount;						// ���� ���� ���� ����

#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockBidVillageInfo, MAX_VILLAGE_NUMBER>		clStockBidVillageInfo;
#else
	cltStockBidVillageInfo	clStockBidVillageInfo[ MAX_VILLAGE_NUMBER ];
#endif

	cltGameMsgResponse_StockBidVillageList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_StockBidVillageList ) );
	}

	SI32	GetTotalSize() {
		return sizeof( SI32 ) + sizeof( cltStockBidVillageInfo ) * ( usCount );
	}	

};

// ���� �ֽ� ������ ������ ���´�
class cltGameMsgResponse_StockBidder
{
public:
	SI32					siVillageUnique;								// ���� ����ũ
	UI16					usCount;										// ������ ����

#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockBidder, MAX_STOCKBIDDER_INVILLAGE>			clStockBidder;
#else
	cltStockBidder			clStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];		// ������ �迭
#endif

	cltGameMsgResponse_StockBidder()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_StockBidder ) );
	}

	SI32					GetTotalSize() {
		return sizeof( SI32 ) + sizeof( SI32 ) + usCount * sizeof( cltStockBidder );
	}

};


//// ���� ��û�� �Ѵ� 
//class cltGameMsgRequest_BidStock
//{
//public:
//	SI32					siVillageUnique;
//	SI32					siAmount;
//	cltMoney				clPrice;
//	
//
//	cltGameMsgRequest_BidStock( SI32 villageUnique, SI32 amount, cltMoney *price )
//	{
//		siVillageUnique = villageUnique;
//
//		siAmount = amount;
//
//		clPrice.Set( price );
//	}
//
//};

// ���� ��û�� �Ѵ� 
class cltGameMsgRequest_BidStock
{
public:
	SI32	siVillageUnique;
	GMONEY	siStockMoney;	//	1�ִ� �ֽİ���			

	cltGameMsgRequest_BidStock( SI32 villageUnique, GMONEY StockMoney )
	{
		siVillageUnique = villageUnique;
		siStockMoney = StockMoney;
	}

};

// ���� ��û�� ����Ѵ� 
class cltGameMsgRequest_CancelBidStock
{
public:
	SI32				siVillageUnique;
	SI32				siPersonID;

	cltGameMsgRequest_CancelBidStock( SI32 villageUnique, SI32 personid )
	{
		siVillageUnique = villageUnique;
		siPersonID = personid;
	}
};

class cltGameMsgResponse_StockBidDate
{
public:
	SI32				siVillageUnique;
	cltDate				clBidDate;

	cltGameMsgResponse_StockBidDate( SI32 villageUnique, cltDate *pclDate )
	{
		siVillageUnique = villageUnique;
		clBidDate.Set( pclDate );
	}
};



// ��ڰ� �ֽ� ���� ���� ������ �˸�
class cltGameMsgResponse_StockDistributionSet
{
public:
	SI32					siVillageUnique;
	SI32					siMaxAmount;
	SI32					siEachPersonAmount;
	GMONEY					siStockPrice;
	bool					bVillageWarStockDistribution;

	cltGameMsgResponse_StockDistributionSet( SI32 VillageUnique, SI32 MaxAmount, SI32 EachPersonAmount, GMONEY StockPrice, bool VillageWarStockDistribution )
	{
		siVillageUnique = VillageUnique;
		siMaxAmount = MaxAmount;
		siEachPersonAmount = EachPersonAmount;
		siStockPrice = StockPrice;

		bVillageWarStockDistribution = VillageWarStockDistribution;
	}
};


// ������ �ֽ� ���� ����
class cltGameMsgRequest_StockDistributionOrder
{
public:
	SI32	siVillageUnique;
	SI32	siAmount;

	bool	bVillageWarStockDistribution;
	
	cltGameMsgRequest_StockDistributionOrder( SI32 VillageUnique, SI32 Amount, bool VillageWarStockDistribution )
	{
		siVillageUnique = VillageUnique;
		siAmount = Amount;
		bVillageWarStockDistribution = VillageWarStockDistribution;
	}
};

class cltGameMsgResponse_StockDistributionOrder
{
public:
	SI32	siVillageUnique;
	SI32	siAmount;				// ���� ���� ����... ������ �з��� �� �� �� ��쵵 �����Ƿ�..
	GMONEY	siPrice;				// �ִ� ���� ����

	cltGameMsgResponse_StockDistributionOrder( SI32 VillageUnique, SI32 Amount, GMONEY Price )
	{
		siVillageUnique = VillageUnique;
		siAmount = Amount;
		siPrice = Price;	
	}
};

//-----------------------------------------------
// ������ �ֽ� ��Ȳ Ŭ���̾�Ʈ�� �뺸 
//-----------------------------------------------
class cltGameMsgResponse_StockTradeInfo
{
public:
	SI16	siVillageUnique;
	GMONEY	siSellPrice;
	SI32	siSellAmount;
	GMONEY	siBuyPrice;
	SI32	siBuyAmount;

	cltGameMsgResponse_StockTradeInfo(SI16 villageunique, GMONEY sellprice, SI32 sellamount, GMONEY buyprice, SI32 buyamount)
	{
		siVillageUnique	= villageunique;
		siSellPrice		= sellprice;
		siSellAmount	= sellamount;
		siBuyPrice		= buyprice;
		siBuyAmount		= buyamount;

	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_Investlist
//
// Last Modified 	: 2006 / 02 / 07
// Created		 	: �豤��
//
// Function			: ������ ������ ���������� ��û�Ѵ�.
//
//***************************************************************************************************
class cltGameMsgRequest_Investlist
{
public:
	SI32 siVillageUnique_;

	cltGameMsgRequest_Investlist() : siVillageUnique_( 0 ) {}

	cltGameMsgRequest_Investlist( SI32 VillageUnique) : siVillageUnique_( VillageUnique ) {}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_BuyBidStock
//
// Last Modified 	: 2006 / 02 / 07
// Created		 	: �豤��
//
// Function			: �����ֽ� ��°��� ��û�Ѵ�.
//
//*************************************************************************************************** 
class cltGameMsgRequest_BuyBidStock
{
public:
	SI16					siType_;	// 0�� �����϶� 1�� �Ϲ��� ��ü�϶�
	SI32					siVillageUnique_;
	SI32					siAmount_;
	cltMoney				clPrice_;


	cltGameMsgRequest_BuyBidStock( SI16 siType, SI32 villageUnique, SI32 amount, cltMoney *price )
	{
		siType_ = siType;
		siVillageUnique_ = villageUnique;
		siAmount_ = amount;
		clPrice_.Set( price );
	}
};

// ���� �ֽ� ���� ���� ������ ������ ��´� 
class cltGameMsgResponse_StockOfferingInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockOfferingInfo, MAX_VILLAGE_NUMBER>		clStockOfferingInfo;
#else
	cltStockOfferingInfo	clStockOfferingInfo[ MAX_VILLAGE_NUMBER ];
#endif

	cltGameMsgResponse_StockOfferingInfo()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_StockOfferingInfo ) );
	}
};

// ����ݾ׺������� �ֽ��ֹ� ��� �˸�
class cltGameMsgResponse_CancelStockOrder
{
public:
	cltGameMsgResponse_CancelStockOrder()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_CancelStockOrder ) );
	}
};

class cltGameMsgRequest_StockOfferingOrder
{
public:
	SI32			siVillageUnique;
	TCHAR			szMacAddress[20];
	TCHAR			szPrivateIP[20];

public:
	cltGameMsgRequest_StockOfferingOrder(SI32 VillageUnique, TCHAR* pszPrivateIP, TCHAR* pszMacAddress)
	{
		szMacAddress[0] = '\0';

		siVillageUnique = VillageUnique;
		if(pszMacAddress)		MStrCpy(szMacAddress, pszMacAddress, sizeof(szMacAddress));
		if(pszPrivateIP)		MStrCpy(szPrivateIP,  pszPrivateIP,  sizeof(szPrivateIP));
	}
};

//***************************************************************************************************
//
// Class Name 		: cltGameMsgRequest_ExchangeStock
//
// Last Modified 	: 2006 / 02 / 07
// Created		 	: �豤��
//
// Function			: �ֽ��� �������� �ٲ۴�
//
//***************************************************************************************************
class cltGameMsgRequest_ExchangeStock
{
public:
	SI32 siVillageUnique;
	SI32 siSellAmount;
	SI32 siBankType;
	TCHAR szBankAccount[MAX_PLAYER_NAME];
	TCHAR szSecondPassWord[MAX_PLAYER_NAME];

	cltGameMsgRequest_ExchangeStock( SI32 VillageUnique, SI32 SellAmount, SI32 BankType, TCHAR* BankAccount, TCHAR* SecondPassWord )
	{
		siVillageUnique = VillageUnique;
		siSellAmount = SellAmount;
		siBankType = BankType;
		StringCchCopy( szBankAccount, MAX_PLAYER_NAME, BankAccount );
		StringCchCopy( szSecondPassWord, MAX_PLAYER_NAME, SecondPassWord );
	}
};

class cltGameMsgResponse_ExchangeStock
{
public:
	bool bResult;
	SI32 siVillageUnique;
	SI32 siSellAmount;
	SI32 siLeftAmount;

	cltGameMsgResponse_ExchangeStock( bool Result, SI32 VillageUnique, SI32 SellAmount, SI32 LeftAmount) : bResult( Result ), siVillageUnique( VillageUnique ), siSellAmount( SellAmount ), siLeftAmount( LeftAmount ) {}
};
#endif

