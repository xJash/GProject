#ifndef _DBMSGMARKET_H
#define _DBMSGMARKET_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

//------------------------------------------
// �������� ���� �ֹ��� �˷��� ���� ��û 
//------------------------------------------
#define GET_MANY_MARKET_ORDER_NUM	50
class sDBRequest_GetManyMarketOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siStartIndex;	//  ���;� �� ������ ���� �ε��� 

	sDBRequest_GetManyMarketOrder()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetManyMarketOrder));
	}

	sDBRequest_GetManyMarketOrder(SI32 id, SI32 ordermode, SI32 startindex)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetManyMarketOrder );
		packetHeader.usCmd = DBMSG_REQUEST_GETMANYMARKETORDER;
		usCharID		= id;

		siOrderMode		= ordermode;
		siStartIndex	= startindex;
	}
};

class sDBResponse_GetManyMarketOrder
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siStartIndex;		// ���� �ֹ��� ���� �ε���.
	cltTradeOrder		clTradeOrder[GET_MANY_MARKET_ORDER_NUM];

	sDBResponse_GetManyMarketOrder()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetManyMarketOrder));
	}
};




//------------------------------------------
// �ֹ� ������ �����. 
//------------------------------------------
class sDBRequest_ReduceOrderPrice
{
public:
	sPacketHeader		packetHeader;

	cltTradeOrder		clOrder;

	// PCK : ���̱� ���� ����
	GMONEY	siPrice;

	sDBRequest_ReduceOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ReduceOrderPrice));
	}

	sDBRequest_ReduceOrderPrice(cltTradeOrder* pclorder, GMONEY Price)
	{
		packetHeader.usSize = sizeof( sDBRequest_ReduceOrderPrice );
		packetHeader.usCmd = DBMSG_REQUEST_REDUCEORDERPRICE;

		clOrder.Set(pclorder);
		siPrice = Price;
	}
};


class sDBResponse_ReduceOrderPrice
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI16				siMarketIndex;		// ���ֳ��� �� ��ǰ�߿����� �ε���. 
	cltTradeOrder		clOrder;			// DB�� ����� �ֹ��� ����. 

	// PCK : �α׿� ��Ŷ
	GMONEY	siPrice;						// ���̱� ���� ���İ���.
	sDBResponse_ReduceOrderPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ReduceOrderPrice));
	}
};


//------------------------------------------
// �����ֹ��� DB�� ���� ���� ��û 
//------------------------------------------
class sDBRequest_OrderMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siOrderMode;	// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	SI32				siVillageUnique;	// �ֹ��� ���� ������ ��ġ. 
	cltTradeOrder		clOrder;		// DB�� �־�� �� �ֹ��� ����. 

	SI16				siItemPos;		// Person���� �������� ��ġ�ϰ� �ִ� ��. 
	bool				bPileSwitch;	// �ű� �������� ��ø�Ǵ��� ����. 

	GMONEY				siTax;			// �����ؾ� �� ����. 

	sDBRequest_OrderMarket()
	{
		ZeroMemory(this, sizeof(sDBRequest_OrderMarket));
	}

	sDBRequest_OrderMarket(SI32 id, SI32 ordermode, SI32 villageunique, cltTradeOrder* pclorder, SI32 itempos, bool bpileswitch, GMONEY tax)
	{
		packetHeader.usSize = sizeof( sDBRequest_OrderMarket );
		packetHeader.usCmd = DBMSG_REQUEST_ORDERMARKET;
		usCharID		= id;

		siOrderMode		= ordermode;
		siVillageUnique	= villageunique;
		clOrder.Set(pclorder);

		siItemPos		= itempos;
		bPileSwitch		= bpileswitch;
		siTax			= tax;
	}
};


class sDBResponse_OrderMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siOrderMode;		// ���� �ֹ��ΰ�. ���� �ֹ��ΰ�..(ORDERMODE_SELL, ORDERMODE_BUY) 
	cltTradeOrder		clOrder;			// DB�� ����� �ֹ��� ����. 

	SI16				siItemFromPos;		// Person���� �������� ��ġ�ϴ� ��. 
	cltItem				clFromItem;			// Person�� �������� �ֽ� ����. 

	GMONEY				siTax;				// �����ؾ� �� ����. 

	//[�߰� : Ȳ���� 2007. 10. 25 �α׿��� �̿�, �Ĵ� ������ ����]
	cltItem				clOrderItem;

	sDBResponse_OrderMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_OrderMarket));
	}
};

//------------------------------------------
// �Ѱ� ������ ������ DB�� �����Ѵ�. 
//------------------------------------------
class sDBRequest_SetItemPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siItemUnique;
	GMONEY				siPrice;
	REAL64				fPrice;
	SI32				siItemNum;
	TCHAR				szItemName[64];

	sDBRequest_SetItemPrice(SI32 itemunique, GMONEY price, REAL64 fprice, SI32 itemnum, const TCHAR* pszItemName)
	{
		ZeroMemory(this, sizeof(sDBRequest_SetItemPrice));
		packetHeader.usSize = sizeof( sDBRequest_SetItemPrice);
		packetHeader.usCmd = DBMSG_REQUEST_SETITEMPRICE;

		siItemUnique	= itemunique;
		siPrice			= price;
		fPrice			= fprice;
		siItemNum		= itemnum;

		if(pszItemName != NULL)		strncpy(szItemName, pszItemName, sizeof(szItemName));
	}
};

class sDBResponse_SetItemPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	sDBResponse_SetItemPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetItemPrice));
	}
};

//------------------------------------------
//KHY - 0530 ���� ���� ��������. - 1�� ���� ������ ���� �׼��� �����Ѵ�. 
//------------------------------------------

// ������� ���ŵ� �ݾ��� ���� - ���� ��¥( )������ ���ո��� �����Ѵ�. 
class sDBRequest_SetForeignMerchantNowMoney
{
public:
	sPacketHeader		packetHeader;

	//SI16					siForeignMerchantKind;
	GMONEY				gPrice;

	sDBRequest_SetForeignMerchantNowMoney(GMONEY price)
	{
		ZeroMemory(this, sizeof(sDBRequest_SetForeignMerchantNowMoney));

		packetHeader.usSize = sizeof( sDBRequest_SetForeignMerchantNowMoney);
		packetHeader.usCmd = DBMSG_REQUEST_SET_FOREIGNMERCHANTNOWMONEY;
		
		//siForeignMerchantKind = ForeignMerchantKind;
		gPrice			= price;
	}
};

class sDBResponse_SetForeignMerchantNowMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	sDBResponse_SetForeignMerchantNowMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetForeignMerchantNowMoney));
	}
};

// ������� ���ŵ� �ݾ��� ���� - ���� ��¥( )������ ������ �����´�.
class sDBRequest_GetForeignMerchantNowMoney
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetForeignMerchantNowMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetForeignMerchantNowMoney));

		packetHeader.usSize = sizeof( sDBRequest_GetForeignMerchantNowMoney);
		packetHeader.usCmd = DBMSG_REQUEST_GET_FOREIGNMERCHANTNOWMONEY;
	}
};

class sDBResponse_GetForeignMerchantNowMoney
{
public:
	sPacketHeader		packetHeader;

	SI32					siResult;			// �����. (1: ���� 0:����) 
	GMONEY				gPrice;

	sDBResponse_GetForeignMerchantNowMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetForeignMerchantNowMoney));
	}
};


// ������ �� �ִ� �ݾ� ����. - ������ ������ �ǰų�, GM ��ɾ� ( SetForeignMerchantBuyLimit ) �� ���ؼ� �����ȴ�.
class sDBRequest_SetForeignMerchantBuyLimit
{
public:
	sPacketHeader		packetHeader	;

	GMONEY				gPrice			;
	float				fUpPercent		;
	float				fDownPercent	;

	sDBRequest_SetForeignMerchantBuyLimit( GMONEY price, float upPercent, float downPercent )
	{
		ZeroMemory(this, sizeof(sDBRequest_SetForeignMerchantBuyLimit));

		packetHeader.usSize = sizeof( sDBRequest_SetForeignMerchantBuyLimit);
		packetHeader.usCmd = DBMSG_REQUEST_SET_FOREIGNMERCHANTBUYLIMIT;

		gPrice			=	price;
		fUpPercent		=	upPercent;
		fDownPercent	=	downPercent;
	}
};

class sDBResponse_SetForeignMerchantBuyLimit
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	sDBResponse_SetForeignMerchantBuyLimit()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetForeignMerchantBuyLimit));
	}
};
// ������� �������� �ݾ��� ������ �´�.
class sDBRequest_GetForeignMerchantBuyLimit
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetForeignMerchantBuyLimit()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetForeignMerchantBuyLimit));

		packetHeader.usSize = sizeof( sDBRequest_GetForeignMerchantBuyLimit);
		packetHeader.usCmd = DBMSG_REQUEST_GET_FOREIGNMERCHANTBUYLIMIT;
	}
};

class sDBResponse_GetForeignMerchantBuyLimit
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	GMONEY				gPrice;
	float				fUpPercent;
	float				fDownPercent;

	sDBResponse_GetForeignMerchantBuyLimit()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetForeignMerchantBuyLimit));
	}
};

// KHY - 0901 -  ���� ������ �ڵ����� ����.
// ������� ���ŵ� �ݾ��� ���� - ���� ��¥( )������ ���ո��� �����Ѵ�. 
class sDBRequest_SetSystemBuyItemNowMoney
{
public:
	sPacketHeader		packetHeader;

	GMONEY				gPrice;

	sDBRequest_SetSystemBuyItemNowMoney(GMONEY price)
	{
		ZeroMemory(this, sizeof(sDBRequest_SetSystemBuyItemNowMoney));

		packetHeader.usSize = sizeof( sDBRequest_SetSystemBuyItemNowMoney);
		packetHeader.usCmd = DBMSG_REQUEST_SET_SYSTEMBUYITEMNOWMONEY;
		
		gPrice			= price;
	}
};

class sDBResponse_SetSystemBuyItemNowMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	GMONEY				gPrice;

	sDBResponse_SetSystemBuyItemNowMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetSystemBuyItemNowMoney));
	}
};

class sDBRequest_GetSystemBuyItemNowMoney
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetSystemBuyItemNowMoney()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetSystemBuyItemNowMoney));

		packetHeader.usSize = sizeof( sDBRequest_GetSystemBuyItemNowMoney);
		packetHeader.usCmd = DBMSG_REQUEST_GET_SYSTEMBUYITEMNOWMONEY;
	}
};

class sDBResponse_GetSystemBuyItemNowMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	GMONEY				gPrice;

	sDBResponse_GetSystemBuyItemNowMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetSystemBuyItemNowMoney));
	}
};
//------------------------------------------
// �������� ������ ������ ��û
//------------------------------------------
class sDBRequest_ManyItemPrice
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_ManyItemPrice()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyItemPrice));
		packetHeader.usSize = sizeof( sDBRequest_ManyItemPrice);
		packetHeader.usCmd = DBMSG_REQUEST_MANYITEMPRICE;
	}
};

#define MANYITEM_PRICE_NUMBER	50
class sDBResponse_ManyItemPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ����, 0: ����, -1: ������) 
	SI32				siItemUnique[MANYITEM_PRICE_NUMBER];			// �������� ����ũ. 
	GMONEY				siCurrentItemPrice[MANYITEM_PRICE_NUMBER];	// ������ ���� (�ð�) 
	REAL64				fPrice[MANYITEM_PRICE_NUMBER];
	SI32				siItemNum[MANYITEM_PRICE_NUMBER];			// ����� ����. 

	sDBResponse_ManyItemPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyItemPrice));
	}
};

//------------------------------------------
// ���� �ŷ� �����Ḧ  ������ ���� ��û
//------------------------------------------
class sDBRequest_SetMarketFee
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


	sDBRequest_SetMarketFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetMarketFee));
	}

	sDBRequest_SetMarketFee(SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetMarketFee );
		packetHeader.usCmd = DBMSG_REQUEST_SETMARKETFEE;
		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};


class sDBResponse_SetMarketFee
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

	sDBResponse_SetMarketFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetMarketFee));
	}

};


//------------------------------------------
// ���ֿ��� ��ǰ�� �ŷ��� ���� ��û 
//------------------------------------------

#define MARKETTRADE_REASON_NORMAL		1
#define MARKETTRADE_REASON_EQUIPITEM	2
#define MARKETTRADE_REASON_CASHITEM		3

class sDBRequest_TradeMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;// �ŷ��� ��û�ϴ� ������ VillageUnique. 	
	bool				bPileSwitch;	// �����Ǵ��� ����. 
	cltTradeOrder		clOrgOrder;		// Ŭ���̾�Ʈ�κ��� �� �ֹ�. 
	SI32				siDstOrderIndex;// �ݴ� �ֹ��� �ε��� (�ֹ���ȣ)

	GMONEY				siPrice;		// �ŷ� �ܰ�.
	SI16				siItemPos;		// �������� ��ġ�� ����. 

	SI16				siReason;

	sDBRequest_TradeMarket()
	{
		ZeroMemory(this, sizeof(sDBRequest_TradeMarket));
	}

	sDBRequest_TradeMarket(SI32 id, SI32 villageunique, bool pileswitch, cltTradeOrder* pclorgorder, SI32 dstorderindex, GMONEY price, SI16 itempos, SI16 reason)
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeMarket );
		packetHeader.usCmd = DBMSG_REQUEST_TRADEMARKET;
		usCharID		= id;

		siVillageUnique	= villageunique;
		bPileSwitch		= pileswitch;
		clOrgOrder.Set(pclorgorder);
		siDstOrderIndex	= dstorderindex;
		siPrice			= price;
		siItemPos		= itempos;

		siReason		= reason;
	}
};


class sDBResponse_TradeMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// �ŷ��� �̷���� Person
	GMONEY				siMoney;			// ���� ��Ȳ. 
	SI32				siVillageUnique;	// Request���� �Էµ� VillageUnique
	cltTradeOrder		clDstOrder;			// ���� �ֹ��� ������ ����. 

	GMONEY				siTradePrice;		// ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0)
	SI16				siItemPos;			// �ŷ� ��� �߰��� �������� ��ġ
	cltItem				clItem;				// �ŷ� ��� �߰��� �������� ����. 
	
	SI32				siSellerPersonID;	// ������ PersonID
	GMONEY				siSellerBankMoney;	// ������ ���� �ܰ�. 
	SI32				siTradeItemNum;		// �ŷ��� �������� ����. 

	//[�߰� : Ȳ���� 2007. 10. 25 �����ϰ� �ŷ��� ������ ����]
	cltItem				clTradeItem;		 
	SI16				siReason;

	sDBResponse_TradeMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_TradeMarket));
	}
};


//------------------------------------------
// ���ְ��� ������ ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_MarketAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;		// ����� �Ǵ� Person

	sDBRequest_MarketAccount()
	{
		ZeroMemory(this, sizeof(sDBRequest_MarketAccount));
	}

	sDBRequest_MarketAccount(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_MarketAccount );
		packetHeader.usCmd = DBMSG_REQUEST_MARKETACCOUNT;
		usCharID		= id;

		siPersonID		= personid;
	}
};


class sDBResponse_MarketAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person

	cltMarketAccount	clMarketAccount;	// ���� ���� ����. 
	
	sDBResponse_MarketAccount()
	{
		ZeroMemory(this, sizeof(sDBResponse_MarketAccount));
	}
};


//------------------------------------------
// ���� â��κ��� �������� ������ ���� ��û�Ѵ�. 
//------------------------------------------
class sDBRequest_GetItemFromMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;


	SI32 siPersonID;		// ����� �Ǵ� Person
	
	SI16 siFromPos;			// �������� ���³� ��ġ. 
	bool bPileSwitch;		// �����Ǵ��� ����. 
	cltItem clFromItem;		// �������� ���³� ��ġ�� �����ϴ� ������.
							//������ ������ siItemNum�� ������Ʈ �Ǿ� �־�� �Ѵ�. 

	SI16 siToPos;			// �������� ������ ���� �κ��� ��ġ. 


	sDBRequest_GetItemFromMarket()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetItemFromMarket));
	}

	sDBRequest_GetItemFromMarket(SI32 id, SI32 personid, SI32 frompos, bool pileswitch, cltItem* pclfromitem, SI32 topos)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetItemFromMarket );
		packetHeader.usCmd = DBMSG_REQUEST_GETITEMFROMMARKET;
		usCharID		= id;

		siPersonID		= personid;
		siFromPos		= frompos;
		bPileSwitch		= pileswitch;
		clFromItem.Set(pclfromitem);

		siToPos			= topos;
	}

	sDBRequest_GetItemFromMarket(SI32 id, cltGetItemFromMarketInfo* pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetItemFromMarket );
		packetHeader.usCmd = DBMSG_REQUEST_GETITEMFROMMARKET;
		usCharID		= id;

		siPersonID		= pclinfo->siPersonID;
		siFromPos		= pclinfo->siFromPos;
		bPileSwitch		= pclinfo->bPileSwitch;
		clFromItem.Set(&pclinfo->clFromItem);

		siToPos			= pclinfo->siToPos;
	}
};


class sDBResponse_GetItemFromMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;		// ����� �Ǵ� Person
	
	SI16				siFromPos;			// �������� ���³� ��ġ. 
	cltItem				clFromItem;		// �������� ���³� ��ġ�� �����ϴ� ������.
										

	SI16				siToPos;		// �������� ������ ���� �κ��� ��ġ. 
	cltItem				clToItem;		// �������� ������ ���� �κ��� ��ġ�� �����ϴ� ������ ����. 
	
	cltTradeOrder		clOrder;		// ������ ȸ���� ��� ����� �ֹ� ����. 

	//[�߰� : Ȳ���� 2007. 10. 25 �α׿� �̿�. ȸ�� ������ ����]
	cltItem				clGetItem;		

	sDBResponse_GetItemFromMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetItemFromMarket));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_GetItemFromNewMarket
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ��� ��ǰ ã��
//
//***************************************************************************************************
class sDBRequest_GetItemFromNewMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32 siServerUnique;	// ã������ �ϴ� ����� ���� ���� ����ũ
	SI32 siPersonID;		// ����� �Ǵ� Person
	SI32 siOrderIndex;		// ã������ �ϴ� �������� �ֹ���ȣ

	bool bPileSwitch;		// �����Ǵ��� ����. 
	cltItem clFromItem;		// �������� ���³� ��ġ�� �����ϴ� ������.
	//������ ������ siItemNum�� ������Ʈ �Ǿ� �־�� �Ѵ�. 

	SI16 siToPos;			// �������� ������ ���� �κ��� ��ġ. 

	sDBRequest_GetItemFromNewMarket(SI32 id, SI32 serverunique, SI32 personid, SI32 orderindex, bool pileswitch, cltItem* pclfromitem, SI32 topos)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetItemFromNewMarket );
		packetHeader.usCmd = DBMSG_REQUEST_GETITEMFROMNEWARKET;
		usCharID		= id;

		siServerUnique = serverunique;
		siPersonID		= personid;
		siOrderIndex = orderindex;
		bPileSwitch		= pileswitch;
		clFromItem.Set(pclfromitem);

		siToPos			= topos;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_GetItemFromNewMarket
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [����]���� ���ֿ��� ��ǰ ã��
//
//***************************************************************************************************
class sDBResponse_GetItemFromNewMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;		// �����.
	SI32				siPersonID;		// ����� �Ǵ� Person

	SI16				siToPos;		// �������� ������ ���� �κ��� ��ġ. 
	cltItem				clToItem;		// �������� ������ ���� �κ��� ��ġ�� �����ϴ� ������ ����. 

	//[�߰� : Ȳ���� 2007. 10. 25 �α׿� �̿�. ȸ�� ������ ����]
	cltItem				clGetItem;		

	sDBResponse_GetItemFromNewMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetItemFromNewMarket));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewMarketItemList
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ� �÷��� ������ ����Ʈ ��û
//
//***************************************************************************************************
class sDBRequest_NewMarketItemList
{
public:

	enum
	{
		TYPE_NORMAL_LIST = 0,
		TYPE_CHEAP_LIST
	};

	sPacketHeader		packetHeader;
	UI16				usCharID;

	UI08				uiType;
	SI32				siItemUnique;	// ����Ʈ�� ��û�� �������� ����ũ 
	SI16				siRequestPage;	// ��û�� ������ ����

	sDBRequest_NewMarketItemList( SI32 id, UI08 type, SI32 itemunique, SI32 requestpage )
	{
		packetHeader.usSize = sizeof( sDBRequest_NewMarketItemList );
		packetHeader.usCmd = DBMSG_REQUEST_NEWMARKETITEMLIST;
		usCharID		= id;

		uiType			= type;
		siItemUnique	= itemunique;
		siRequestPage   = requestpage;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewMarketItemList
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [����]���� ���ֿ� �÷��� ������ ����Ʈ ��û
//
//***************************************************************************************************
class sDBResponse_NewMarketItemList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	UI08				uiType;
	SI32				siResult;		// �����.
	SI32				siItemUnique;	// ��û�� ������ ����ũ
	SI16				siMaxPage;		// ����Ʈ�� �� ������ ��
	SI64				siCurrentPrice; // ���� �ü�
	float				fCurrentPrice;  
	cltNewTradeOrder	clNewTradeOrder[MAX_NEWMARKET_ITEMLIST];

	sDBResponse_NewMarketItemList()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewMarketItemList));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewOrderMarket
//
// Last Modified 	: 2008/10/20
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ� �������� �ø���.
//
//***************************************************************************************************
class sDBRequest_NewOrderMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;	// �ֹ��� ���� ������ ��ġ. 
	cltNewTradeOrder	clOrder;			// DB�� �־�� �� �ֹ��� ����. 

	SI16				siItemPos;			// Person���� �������� ��ġ�ϰ� �ִ� ��. 
	bool				bPileSwitch;		// �ű� �������� ��ø�Ǵ��� ����. 

	SI64				siTax;				// �����ؾ� �� ����. 

	UI08				uiOrderMode;		// �ֹ����(0:�����, 1:�ý���)

	sDBRequest_NewOrderMarket(SI32 id, SI32 villageunique, cltNewTradeOrder* pclorder, SI32 itempos, bool bpileswitch, SI64 tax, UI08 uiordermode )
	{
		packetHeader.usSize = sizeof( sDBRequest_NewOrderMarket );
		packetHeader.usCmd = DBMSG_REQUEST_NEWORDERMARKET;
		usCharID		= id;

		siVillageUnique	= villageunique;
		clOrder.Set(pclorder);

		siItemPos		= itempos;
		bPileSwitch		= bpileswitch;
		siTax			= tax;

		uiOrderMode		=	uiordermode;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_NewOrderMarket
//
// Last Modified 	: 2008/10/20
// Created		 	: �豤��
//
// Function			: [����]���� ���ֿ� �������� �ø���.
//
//***************************************************************************************************
class sDBResponse_NewOrderMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	cltNewTradeOrder	clOrder;			// DB�� ����� �ֹ��� ����. 

	SI16				siItemFromPos;		// Person���� �������� ��ġ�ϴ� ��. 
	cltItem				clFromItem;			// Person�� �������� �ֽ� ����. 

	SI64				siTax;				// �����ؾ� �� ����. 
	SI32				siVillageUnique;	// �ֹ��� ���� ������ ��ġ. 

	sDBResponse_NewOrderMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewOrderMarket));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewTradeMarket
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [��û]���� ���ַ� ���ſ�û�� �Ѵ�.
//***************************************************************************************************
class sDBRequest_NewTradeMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siServerUnique;
	SI32				siVillageUnique;// �ŷ��� ��û�ϴ� ������ VillageUnique.
	SI32				siBuyerPersonID;
	cltNewTradeOrder	clOrgOrder;		// Ŭ���̾�Ʈ�κ��� �� �ֹ�. 

	SI64				siPrice;		// �ŷ� �ܰ�.
	SI16				siItemPos;		// �������� ��ġ�� ����. 

	bool				bPileSwitch;

	bool				m_bCreateSID;		// SID ���� ����

	SYSTEMTIME			stRequestTime;		// �ŷ� ��û�� �ð� (���ǽð�)

	sDBRequest_NewTradeMarket()
	{
		ZeroMemory(this, sizeof(sDBRequest_NewTradeMarket));
	}

	sDBRequest_NewTradeMarket(SI32 id, SI32 serverunique, SI32 villageunique, SI32 buyerpersonid, cltNewTradeOrder* pclorgorder, SI64 price, SI16 itempos, bool PileSwitch, bool bCreateSID, SYSTEMTIME*	pRequestTime )
	{
		packetHeader.usSize = sizeof( sDBRequest_NewTradeMarket );
		packetHeader.usCmd = DBMSG_REQUEST_NEWTRADEMARKET;
		usCharID		= id;

		siServerUnique = serverunique;
		siVillageUnique	= villageunique;
		siBuyerPersonID = buyerpersonid;
		clOrgOrder.Set(pclorgorder);
		siPrice			= price;
		siItemPos		= itempos;
		bPileSwitch		= PileSwitch;
		m_bCreateSID	= bCreateSID;

		memcpy( &stRequestTime, pRequestTime, sizeof(stRequestTime) );
	}
};


//***************************************************************************************************
//
// Class Name 		: sDBResponse_NewTradeMarket
//
// Last Modified 	: 2008/10/23
// Created		 	: �豤��
//
// Function			: [����]���� ���ַ� ���ſ�û�� �Ѵ�.
//***************************************************************************************************
class sDBResponse_NewTradeMarket
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;				// �����.
	SI32				siBuyerPersonID;		// �ŷ��� �̷���� Person
	SI64				siMoney;				// ���� ��Ȳ. 
	SI32				siVillageUnique;		// Request���� �Էµ� VillageUnique

	SI64				siTradePrice;			// ������ �ŷ��� ����. (�ŷ��� �̷������ �ʾҴٸ� 0)
	SI16				siItemPos;				// �ŷ� ��� �߰��� �������� ��ġ
	cltItem				clItem;					// �ŷ� ��� �߰��� �������� ����. 

	SI32				siSellerServerUnique;	// ������ ��������ũ
	SI32				siSellerPersonID;		// ������ PersonID
	SI64				siSellerBankMoney;		// ������ ���� �ܰ�. 
	SI32				siTradeItemNum;			// �ŷ��� �������� ����. 

	float				fPrice;					// �������� ���ü�
	bool				m_bSystem;

	//[�߰� : Ȳ���� 2007. 10. 25 �����ϰ� �ŷ��� ������ ����]
	cltItem				clTradeItem;		 

	sDBResponse_NewTradeMarket()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewTradeMarket));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewMarketAccount
//
// Last Modified 	: 2008/10/20
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ� �ø� ��ǰ ������ ��û�Ѵ�.
//
//***************************************************************************************************
class sDBRequest_NewMarketAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI16				siServerUnique;
	SI32				siPersonID;		// ����� �Ǵ� Person

	sDBRequest_NewMarketAccount()
	{
		ZeroMemory(this, sizeof(sDBRequest_NewMarketAccount));
	}

	sDBRequest_NewMarketAccount(SI32 id, SI16 serverunique, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_NewMarketAccount );
		packetHeader.usCmd = DBMSG_REQUEST_NEWMARKETACCOUNT;
		usCharID		= id;

		siServerUnique = serverunique;
		siPersonID		= personid;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_NewMarketAccount
//
// Last Modified 	: 2008/10/20
// Created		 	: �豤��
//
// Function			: [����]���� ���ֿ� �ø� ��ǰ ������ ��û�Ѵ�.
//
//***************************************************************************************************
class sDBResponse_NewMarketAccount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siServerUnique;		// ����� �Ǵ� Server

	cltNewMarketAccount	clMarketAccount;	// ���� ���� ����. 

	sDBResponse_NewMarketAccount()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewMarketAccount));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewMarketResult
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ��� �ȸ� ������ �� ������ ������Ʈ �Ѵ�.
//
//***************************************************************************************************
class sDBRequest_NewMarketResult
{
public:
	sPacketHeader		packetHeader;

	SI16				siServerUnique;

	sDBRequest_NewMarketResult()
	{
		ZeroMemory(this, sizeof(sDBRequest_NewMarketResult));
	}

	sDBRequest_NewMarketResult(SI16 serverunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_NewMarketResult );
		packetHeader.usCmd = DBMSG_REQUEST_NEWMARKETRESULT;

		siServerUnique = serverunique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_NewMarketResult
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]���� ���ֿ��� �ȸ� ������ �� ������ ������Ʈ �Ѵ�.
//
//***************************************************************************************************
const SI16 MAX_NEWMARKET_RESULTLIST = 100;
class sDBResponse_NewMarketResult
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI16				siServerUnique;		// ����� �Ǵ� Server

	SellerInfo			stSellerInfo[MAX_NEWMARKET_RESULTLIST];

	sDBResponse_NewMarketResult()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewMarketResult));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_SetNewMarketFee
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]����� ������ ����
//
//***************************************************************************************************
class sDBRequest_SetNewMarketFee
{
public:
	sPacketHeader		packetHeader;
	SI32				siCharID;

	// Who
	SI32				siPersonID;

	// Where
	SI32				siVillageUnique;	// ���ְ� ��ġ�� ���� VillageUnique

	// What
	cltFee				clFee;				// �����ؾ� �� ������ ������ ����

	sDBRequest_SetNewMarketFee(SI32 id, SI32 personid, SI32 villageunique, cltFee* pclfee)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetNewMarketFee );
		packetHeader.usCmd = DBMSG_REQUEST_SETNEWMARKETFEE;
		siCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clFee.Set(pclfee);
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_SetNewMarketFee
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]����� ������ ����
//
//***************************************************************************************************
class sDBResponse_SetNewMarketFee
{
public:
	sPacketHeader		packetHeader;
	SI32				siCharID;

	// result 
	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;

	// where
	SI32				siVillageUnique;	// ���ְ� ��ġ�� ������ VillageUnique

	// what
	cltFee				clFee;				// ������ �ŷ� ������ ����. 

	sDBResponse_SetNewMarketFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetNewMarketFee));
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NewMarket_IncreaseBankMoney
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]��������� �Ǹŵ� �ݾ��� ������Ʈ ��Ų��.
//
//***************************************************************************************************
class sDBRequest_NewMarket_IncreaseBankMoney
{
public:
	sPacketHeader		packetHeader;
	SI32				siCharID;

	// Who
	SI32				siPersonID;
	SI64				siIncreaseMoney;

	sDBRequest_NewMarket_IncreaseBankMoney(SI32 id, SI32 personid, SI64 IncreaseMoney)
	{
		packetHeader.usSize = sizeof( sDBRequest_NewMarket_IncreaseBankMoney );
		packetHeader.usCmd = DBMSG_REQUEST_NEWMARKET_INCREASEBANKMONEY;
		siCharID		= id;

		siPersonID		= personid;
		siIncreaseMoney = IncreaseMoney;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_NewMarket_IncreaseBankMoney
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [����]��������� �Ǹŵ� �ݾ��� ������Ʈ ��Ų��.
//
//***************************************************************************************************
class sDBResponse_NewMarket_IncreaseBankMoney
{
public:
	sPacketHeader		packetHeader;
	SI32				siCharID;

	// result 
	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;

	//cltBankAccount		clBankAccount;			// �Ա� �� �ݾ�. 	
	cltMoney			clTotalMoney;		// �Ա� �� �ѱݾ�. 
	// to bank info
	SI32				siVillageUnique;		
	cltMoney			clCurrentLeftMoney;		// �����ڱ� 
	cltMoney			clTotalInputMoney;		// �Ѽ��Ծ�


	sDBResponse_NewMarket_IncreaseBankMoney()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewMarket_IncreaseBankMoney));
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ManyItemNewPrice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]������ �ü��� �޾ƿ´�
//
//***************************************************************************************************
class sDBRequest_ManyItemNewPrice
{
public:

	enum
	{
		REQUEST_ALLITEM = 0,
		REQUEST_CHANGE_PRICE_ITEM
	};

	sPacketHeader		packetHeader;

	UI08 uiType;

	SYSTEMTIME			stRequestTime;	// �����϶� ������ ��û�� �ð� (���ǽð�)

	sDBRequest_ManyItemNewPrice( UI08 Type, SYSTEMTIME*	pRequestTime )
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyItemNewPrice));
		packetHeader.usSize = sizeof( sDBRequest_ManyItemNewPrice);
		packetHeader.usCmd = DBMSG_REQUEST_MANYITEMNEWPRICE;

		uiType = Type;

		memcpy( &stRequestTime, pRequestTime, sizeof(stRequestTime) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ManyItemNewPrice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [����]������ �ü��� �޾ƿ´�
//
//***************************************************************************************************
class sDBResponse_ManyItemNewPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 
	SI16				siItemUnique[MANYITEM_PRICE_NUMBER];			// �������� ����ũ. 
	SI64				siCurrentItemPrice[MANYITEM_PRICE_NUMBER];	// ������ ���� (�ð�) 
	float				fPrice[MANYITEM_PRICE_NUMBER];
	SI32				siItemNum[MANYITEM_PRICE_NUMBER];			// ����� ����. 

	sDBResponse_ManyItemNewPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyItemNewPrice));
	}
};

class sDBResponse_ManyItemNewPrice_Completed
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	sDBResponse_ManyItemNewPrice_Completed()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyItemNewPrice_Completed));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ManyItemNewPrice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û]������ �ü��� �����Ѵ�
//
//***************************************************************************************************
class sDBRequest_SetItemNewPrice
{
public:
	sPacketHeader		packetHeader;

	SI16				siItemUnique;
	SI64				siPrice;
	float				fPrice;
	SI32				siItemNum;

	sDBRequest_SetItemNewPrice(SI16 itemunique, SI64 price, float fprice, SI32 itemnum)
	{
		ZeroMemory(this, sizeof(sDBRequest_SetItemNewPrice));
		packetHeader.usSize = sizeof( sDBRequest_SetItemNewPrice);
		packetHeader.usCmd = DBMSG_REQUEST_SETITEMNEWPRICE;

		siItemUnique	= itemunique;
		siPrice			= price;
		fPrice			= fprice;
		siItemNum		= itemnum;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ManyItemNewPrice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [����]������ �ü��� �����Ѵ�.
//
//***************************************************************************************************
class sDBResponse_SetItemNewPrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	sDBResponse_SetItemNewPrice()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetItemNewPrice));
	}
};

//***************************************************************************************************
//
// Class Name 		: NewMarketReducePriceNotice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [��û] �������� ��������� ������ �϶��� ������ ��û�Ѵ�.
//
//***************************************************************************************************
class sDBRequest_NewMarketReducePriceNotice
{
public:
	sPacketHeader		packetHeader;

	SI16				siServerUnique;

	SYSTEMTIME			stRequestTime;	// �����϶� ������ ��û�� �ð� (���ǽð�)

	sDBRequest_NewMarketReducePriceNotice( SI16 ServerUnique, SYSTEMTIME* pRequestTime )
	{
		packetHeader.usSize = sizeof( sDBRequest_NewMarketReducePriceNotice);
		packetHeader.usCmd = DBMSG_REQUEST_NEWMARKETREDUCEPRICENOTICE;

		siServerUnique = ServerUnique;
		memcpy( &stRequestTime, pRequestTime, sizeof(stRequestTime) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ManyItemNewPrice
//
// Last Modified 	: 2008/11/05
// Created		 	: �豤��
//
// Function			: [����]������ �ü��� �����Ѵ�.
//
//***************************************************************************************************
SI16 const MAX_REDUCEPRICE_USERLIST = 1000;
class sDBResponse_NewMarketReducePriceNotice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����. (1: ���� 0:����) 

	struct	
	{		
		SI32			siPersonID;
		SI32			siItemUnique;
		SI32			siItemQty;
		cltMoney		clPrice;
	}stData[ MAX_REDUCEPRICE_USERLIST ];

	//SI32				siPersonID[MAX_REDUCEPRICE_USERLIST];

	sDBResponse_NewMarketReducePriceNotice()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewMarketReducePriceNotice));
	}
};

#endif
