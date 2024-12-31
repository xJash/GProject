#ifndef _DBMSGPERSONALSHOP_H
#define _DBMSGPERSONALSHOP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

//------------------------------------------
// ���� ������ �����ϱ����ؼ� Ticket�� ����Ѵ�.
//------------------------------------------
class sDBRequest_StartPersonalShop
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI16				siItemPos;
	SI16				siItemUnique;
	SI16				siItemNum;

	cltShopTradeData	clShopData;

	cltItem				clItem;

	sDBRequest_StartPersonalShop()
	{
		ZeroMemory(this, sizeof(sDBRequest_StartPersonalShop));
	}

	sDBRequest_StartPersonalShop(SI32 id,	   SI32 personid,   SI32 villageunique,	
							     SI16 itempos, SI16 itemunique, SI16 itemnum, cltShopTradeData	*pclshopdata, cltItem *pclItem)
	{
		packetHeader.usSize = sizeof( sDBRequest_StartPersonalShop );
		packetHeader.usCmd = DBMSG_REQUEST_STARTPERSONALSHOP;
		
		siCharID	= id;
		siPersonID	= personid;
		
		siVillageUnique = villageunique;
		siItemPos		= itempos;
		siItemUnique	= itemunique;
		siItemNum		= itemnum;
		clShopData.Set(pclshopdata);
		clItem.Set(pclItem);
	}

};

class sDBResponse_StartPersonalShop
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI16				siItemPos;
	cltItem				clItem;
	// �޼��� ������ ���ؼ� �� ��带 �߰� [����]
	SI08		    m_siShopMode;


	// PCK : �α׿� ��Ŷ �߰�
	cltItem				clItem_Log;

	sDBResponse_StartPersonalShop()
	{
		ZeroMemory( this, sizeof( sDBResponse_StartPersonalShop ) );
	}
};
//------------------------------------------
// ���λ����� ���� Person�� Item�� ���� �ְ� �Ѵ�.
//------------------------------------------
class sDBRequest_PersonalShopBuyItem
{
public:
	sPacketHeader		packetHeader;
	SI16				siCharID;
	SI32				siBuyerPersonID;	

	SI16				siShopperCharID;
	SI32				siShopperPersonID;	
	
	SI16				siBuyerInvPos;		// Buyer���� ������ �������� �־���ϴ� Inventory ��ġ 
	SI16				siShopperInvPos;	// Shoper�� �ش� Inventory ��ġ 
	
	SI16				siShowCaseIndex;
	GMONEY				siItemCost;			// Buyer���Լ� �����ϴ� MONEY

	cltItem				clBuyItem;			// Shopper���Լ� ���� Buyer���� �־���ϴ� ������ ���� 
	bool				bPileSwitch;		// ��ø ��� ����. 	
	
	sDBRequest_PersonalShopBuyItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonalShopBuyItem));
	}

	sDBRequest_PersonalShopBuyItem(SI32 id,			SI32 buyerpersonid, 
							SI32 shopperid,			SI32 shopperpersonid, 
							SI16 buyerInv,			SI16 shopperInv, 
							SI16 shwcaseindex,	    GMONEY sicost,
							cltItem* pclbuyitem,	bool bpile)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonalShopBuyItem );
		packetHeader.usCmd  = DBMSG_REQUEST_PERSONALSHOPBUYITEM;

		siCharID			= id;
		siBuyerPersonID		= buyerpersonid;

		siShopperCharID		= shopperid;
		siShopperPersonID	= shopperpersonid;	

		siBuyerInvPos		= buyerInv;
		siShopperInvPos		= shopperInv;

		siShowCaseIndex		= shwcaseindex;
		siItemCost			= sicost;

		clBuyItem.Set(pclbuyitem);
		bPileSwitch			= bpile;
	}
};


class sDBResponse_PersonalShopBuyItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����. (���� 1:  ���� : 0)

	SI16				siCharID;
	SI32				siBuyerPersonID;	

	SI16				siShopperCharID;
	SI32				siShopperPersonID;	

	SI16				siBuyerInvPos;		// Buyer���� ������ �������� �־���ϴ� Inventory ��ġ 
	SI16				siShopperInvPos;	// Shoper�� �ش� Inventory ��ġ 

	cltItem				clBuyerInvItem;		// Buyer�� Inventory�� �����Ǿ���ϴ� Item ���� 
	cltItem				clShopperInvItem;	// Shopper Inventory�� �����Ǿ���ϴ� Item ���� 

	GMONEY				siBuyerMoney;		// Buyer�� ���� ���� 
	GMONEY				siShopperMoney;		// Buyer�� ���� ���� 

	GMONEY				siItemCost;			// ��� ���� �� 
	SI16				siShowCaseIndex;	// Showcase Index
	SI32				siBuyItemNum;		// clBuyItem.siItemNum �� ������ �޾� ��� ����� �����Ѵ�.
	
	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿�. Buyer�� �����ϰ� ����̴� ������]
	cltItem				clBuyItem;			

	sDBResponse_PersonalShopBuyItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonalShopBuyItem));
	}

};


//------------------------------------------
// ���λ����� ���� Person�� Item�� ���� �ְ� �Ѵ�.
//------------------------------------------
class sDBRequest_PersonalShopSellItem
{
public:
	sPacketHeader		packetHeader;
	SI16				siCharID;
	SI32				siSellerPersonID;	

	SI16				siShopperCharID;
	SI32				siShopperPersonID;	
	
	SI16				siSellerInvPos;		// Seller�� �ش� Inventory ��ġ 
	SI16				siShopperInvPos;	// Seller���� ������ �������� �־���ϴ� Inventory ��ġ 
	
	SI16				siShowCaseIndex;
	GMONEY				siItemCost;			// Shopper���Լ� �����ϴ� MONEY

	cltItem				clSellItem;			// Seller���Լ� ���� Shopper���� �־���ϴ� ������ ���� 
	bool				bPileSwitch;		// ��ø ��� ����. 	
	
	sDBRequest_PersonalShopSellItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_PersonalShopSellItem));
	}

	sDBRequest_PersonalShopSellItem(SI32 id,			SI32 sellerpersonid, 
							SI32 shopperid,			SI32 shopperpersonid, 
							SI16 sellerInv,			SI16 shopperInv, 
							SI16 shwcaseindex,	    GMONEY sicost,
							cltItem* pclsellitem,	bool bpile)
	{
		packetHeader.usSize = sizeof( sDBRequest_PersonalShopSellItem );
		packetHeader.usCmd  = DBMSG_REQUEST_PERSONALSHOPSELLITEM;

		siCharID			= id;
		siSellerPersonID	= sellerpersonid;

		siShopperCharID		= shopperid;
		siShopperPersonID	= shopperpersonid;	

		siSellerInvPos		= sellerInv;
		siShopperInvPos		= shopperInv;

		siShowCaseIndex		= shwcaseindex;
		siItemCost			= sicost;

		clSellItem.Set(pclsellitem);
		bPileSwitch			= bpile;
	}
};


class sDBResponse_PersonalShopSellItem
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����. (���� 1:  ���� : 0)

	SI16				siCharID;
	SI32				siSellerPersonID;	

	SI16				siShopperCharID;
	SI32				siShopperPersonID;	

	SI16				siSellerInvPos;		// Seller�� �ش� Inventory ��ġ 
	SI16				siShopperInvPos;	// Seller���� ������ �������� �־���ϴ� Inventory ��ġ 

	cltItem				clSellerInvItem;	// Seller�� Inventory�� �����Ǿ���ϴ� Item ���� 
	cltItem				clShopperInvItem;	// Shopper  Inventory�� �����Ǿ���ϴ� Item ���� 

	GMONEY				siSellerMoney;		// Seller�� ���� ���� 
	GMONEY				siShopperMoney;		// Shopper�� ���� ���� 

	GMONEY				siItemCost;			// ��� ���� �� 
	SI16				siShowCaseIndex;	// Showcase Index
	SI32				siSellItemNum;		// clSellItem.siItemNum �� ������ �޾� ��� ����� �����Ѵ�.
	
	// PCK - �α׿� ��Ŷ
	cltItem				clSellerInvItem_Log;

	sDBResponse_PersonalShopSellItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_PersonalShopSellItem));
	}

};



#endif
