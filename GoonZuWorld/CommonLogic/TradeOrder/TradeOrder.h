//---------------------------------
// 2003/6/20 ���°�
//---------------------------------
#ifndef _TRADEORDER_H
#define _TRADEORDER_H

#include <Directives.h>
#include "../../Lib/EtcTool/EtcTool.h"

#include "../../../NLib/NDataTypes.h"
#include "../../common/Item/ItemCommon/ItemUnit.h"

#define TRADEORDER_DATASIZE 16		// cltItem�� ����� �� ������ ����� �ȴ�. 

//-------------------------------------------
// �ֹ� Ÿ�� 
//-------------------------------------------
#define TRADEORDER_TYPE_STOCK		1			// �ֽ� 
#define TRADEORDER_TYPE_OBJECT		3			// ������Ʈ ������. 
//_LEON_GUILD_STOCK
#define TRADEORDER_TYPE_GUILDSTOCK	5			// ����ֽ�




#define MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM	8

//------------------------------------------
// ���, �ȱ�. 
//------------------------------------------
// ��� �ֹ��ΰ�. �Ĵ� �ֹ��ΰ�..
#define ORDERMODE_SELL			1
#define ORDERMODE_BUY			2

class cltNewTradeOrder
{
public:

	cltItem clItemData;
	bool 	bBankError;			// ���忡 ���� �� ���� �ŷ��� �ȵǴ� �����̳�? ( �ü� ���� �� ��ģ�� )
	SI16 	siServerUnique;		// �ֹ��� �� ������ ���� ����ũ
	SI32 	siOrderIndex;		// ���� ���ֿ� �÷��� Index
	SI32 	siPersonID;			// �ֹ��� �� PersonID
	SI32 	siAmount;			// �ֹ� ����. 
	SI32 	siDate;				// ��¥ ����.
	GMONEY 	siPrice;			// �ֹ� ���� ����. 

public:
	cltNewTradeOrder()
	{
		Init();
	}

	~cltNewTradeOrder()
	{
	}

	void Init()
	{
		clItemData.Init();
		bBankError		= false;
		siServerUnique	= 0;
		siOrderIndex	= 0;
		siPersonID		= 0;
		siAmount		= 0;
		siDate			= 0;
		siPrice			= 0;
	}

	cltNewTradeOrder( const cltItem* pclitem, bool bankerror, SI16 serverunique, SI32 orderindex, SI32 personid, SI32 amount, SI32 datevary, GMONEY price )
	{
		clItemData.Set(pclitem);
		bBankError		= bankerror;
		siServerUnique	= serverunique;
		siOrderIndex	= orderindex;
		siPersonID		= personid;
		siAmount		= amount;
		siDate			= datevary;
		siPrice			= price;

	}

	bool IsSame(cltNewTradeOrder* porder);

	// ��ȿ�� �ֹ����� Ȯ���Ѵ�. 
	bool IsValid()
	{
		if(siAmount == 0)
			return false;

		return true;
	}

	void Set(cltNewTradeOrder* porder)
	{
		memcpy(this, porder, sizeof(cltNewTradeOrder));
	}

	//---------------------------
	// �������� ���, 
	//---------------------------
	SI16 GetItemUnique()const		// ���ϰ��� SI16�̾�� �Ѵ�. 
	{
		return clItemData.siUnique;
	}
};

class cltTradeOrder
{
public:
	SI16		siIndex;		// �ֹ� ������ �ĺ���(�ε���) (0~�� 16000) 
	SI16		siType;			// ������� �ֹ��ΰ�?	// �ֽ�, ������, Ȥ�� ����ֽ�
	SI32		siPersonID;		// �ֹ��� �� PersonID
	GMONEY		siPrice;		// �ֹ� ���� ����. 
	SI32		siAmount;		// �ֹ� ����. 
	SI32		siDate;			// �ð� ����.
	bool		bBankError;		// ���忡 ���� �� ���� �ŷ��� �ȵǴ� �����̳�? ( �ü� ���� �� ��ģ�� )

public:
	cltItemData clItemData;
	SI32		siVillageUnique;	// �ֹ��� ����� �Ǵ� �ֽ��� ���� ����ũ 
	
public:
	cltTradeOrder()
	{
		Init();
	}

	cltTradeOrder(SI32 personid, GMONEY price, SI32 amount, SI32 datevary, SI32 villageunique)
	{
		siIndex		= 0;
		siType		= TRADEORDER_TYPE_STOCK;
		siPersonID	= personid;
		siPrice		= price;
		siAmount	= amount;
		siDate		= datevary;
		bBankError	= false;

		clItemData.Init();
		siVillageUnique = villageunique;
	}
	cltTradeOrder(SI32 type, SI32 personid, GMONEY price, SI32 amount, SI32 datevary, const cltItem* pclitem)
	{
		siIndex		= 0;
		siType		= type;
		siPersonID	= personid;
		siPrice		= price;
		siAmount	= amount;
		siDate		= datevary;
		bBankError	= false;

		siVillageUnique = 0;		// ���Ͽ��̹Ƿ� ���� �ʱ�ȭ�Ѵ�.
		clItemData.Set(pclitem);
	}

	void Init()
	{
		siIndex		= 0;
		siType		= 0;
		siPersonID	= 0;
		siPrice		= 0;
		siAmount	= 0;
		siDate		= 0;
		bBankError	= false;

		clItemData.Init();
		siVillageUnique = 0;
	}

	BOOL IsSame(cltTradeOrder* porder);

	// ��ȿ�� �ֹ����� Ȯ���Ѵ�. 
	BOOL IsValid()
	{
		if(siAmount == 0)return FALSE;

		return TRUE;
	}

	void Set(cltTradeOrder* porder)
	{
		memcpy(this, porder, sizeof(cltTradeOrder));
	}

	//----------------------------
	// �ֽ��� ���, 
	//----------------------------
	SI32 GetVillageUnique()const{return siVillageUnique;}


	//---------------------------
	// �������� ���, 
	//---------------------------
	SI16 GetItemUnique()const		// ���ϰ��� SI16�̾�� �Ѵ�. 
	{
		return clItemData.siUnique;
	}
};

class cltTradeOrderManager{
public:
	SI32 siMaxOrderNum;

	cltTradeOrder** pclOrderSell;	// ���� �ֹ� 
	cltTradeOrder** pclOrderBuy;	// ���� �ֹ� 	

	cltTradeOrderManager(SI32 ordernum);
	~cltTradeOrderManager();

	// �ֹ��� �ֹ� ������ ������ �ڸ��� �ִ´�. 
	bool SetOrder(SI32 ordermode, cltTradeOrder* porder);
	
	// �־��� �ֹ��� ������ �ݴ� �ֹ��� ã�´�. 
	// ã���� �� �ݴ� �ֹ��� �����͸� �����ϰ� �� ã���� NULL�� �����Ѵ�.
	// PersonID : ���� ����� �ڱⰡ �÷� ���� �ݴ� �ֹ��� ã�� �� ����.
	cltTradeOrder* FindOpositeOrder(SI32 ordermode, cltTradeOrder* porder);

	bool GetMostSellBuyOrder(IN cltTradeOrder* porder, OUT cltTradeOrder* pSellMostOrderList, OUT cltTradeOrder* pBuyMostOrderList, OUT GMONEY * averageSell, OUT  GMONEY * averageBuy) ;

	// PersonID������ �ֹ��� ��� ����ϰ� �Ѵ�. 
	BOOL CancelOrder(SI32 personid);

	// ���� �������� Ȯ���Ѵ�. 
	BOOL IsSameKind(const cltTradeOrder* pclsrc, const cltTradeOrder* pcldst);

	// ��ǰ �ֹ��� ���� ������ �ֹ��� ������ ã�´�. 
	bool FindLowPriceOrderInfo(SI32 unique, GMONEY* pprice, SI32* pamount);

	// �ֽ�  �ֹ��� ���� ������ �ֹ��� ������ ã�´�. 
	bool FindLowPriceStockOrderInfo(SI32 villageunique, GMONEY* pprice, SI32* pamount);

	// �ֽ� �ֹ��� ���� ��� �ֹ��� ������ ã�´�. 
	bool FindHighPriceStockOrderInfo(SI32 villageunique, GMONEY* pprice, SI32* pamount);



	// �ֹ� ����Ʈ���� �ε����� �ֹ� ������ Ȯ���Ѵ�. 
	cltTradeOrder* GetOrder(SI32 ordermode, SI32 index);

	// �ֹ��� ������ ���Ѵ�. 
	SI32 GetOrderNum(SI32 ordermode);
};

#define MAX_ORDER_PER_PERSON	5	// Person�� ���� �� �ִ� �ֽ� �ֹ� ����. 
#define MAX_STOCK_TOTURIAL_NUM 20	// ��ī�� �ֽ��� ������ �ִ� �ֹ� ����.

// Person�� ���� �� �ִ� �����ִ� �ֹ� ��
const SI32 MAX_MARKET_ORDER_PER_PERSON		= 8;
const SI32 MAX_NEWMARKET_ORDER_PER_PERSON	= 12;	//[����] ���ս���.

//--------------------------------------
// person�� �ֹ� ����. 
//--------------------------------------
class cltCharOrderInfoUnit{
public:
	SI32			siOrderMode;	// ORDERMODE_SELL, ORDERMODE_BUY
	cltTradeOrder	clOrder;

	cltCharOrderInfoUnit()
	{
		siOrderMode = 0;
	}
};

class cltCharOrderInfo{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltCharOrderInfoUnit, MAX_MARKET_ORDER_PER_PERSON>		clOrderUnit;
#else
	cltCharOrderInfoUnit clOrderUnit[MAX_MARKET_ORDER_PER_PERSON];
#endif

	cltCharOrderInfo()
	{
		ZeroMemory(this, sizeof(cltCharOrderInfo));
	}

	void Set(cltCharOrderInfo* porder)
	{
		memcpy(this, porder, sizeof(cltCharOrderInfo));
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltCharOrderInfo));
	}

	// �ֹ� ������ �����Ѵ�.
	BOOL Set(SI32 ordertype, cltTradeOrder* pclorder);

	// �ֹ��� ������ ���Ѵ�. 
#ifdef _SAFE_MEMORY
	SI32 GetOrderNumber();
#else
	SI32 GetOrderNumber()const;
#endif
	// �ֹ� ��ȣ�� �ٰŷ� ������ �ֹ��� ã�´�. 
	cltCharOrderInfoUnit* FindOrder(SI32 orderindex)
	{
		SI32 i;

		for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
		{
			if(clOrderUnit[i].clOrder.siIndex == orderindex)
			{
				return &clOrderUnit[i];
			}
		}
		return NULL;
	}

};

struct SellerInfo
{
	SI32				siSellerPersonID;		// ������ PersonID
	SI16				siSellItemUnique;		// �ŷ��� ������ ����ũ
	GMONEY				siSellPrice;			// �ŷ��� ����(�Ѱ���)
	SI32				siSellItemNum;			// �ŷ��� �������� ����.
	SI32				siVillageUnique;		// ������ �ø� ���� ����ũ

	SellerInfo() : siSellerPersonID(0), siSellItemUnique(0), siSellPrice(0), siSellItemNum(0), siVillageUnique(0) 
	{
	}
	~SellerInfo()
	{}
};

#endif
