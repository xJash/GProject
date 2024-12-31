//---------------------------------
// 2003/6/2 ���°�
//---------------------------------

#ifndef _STOCK_H
#define _STOCK_H

#include <Directives.h>

#include <Stdio.h>
#include "..\StructureClass\StructureClass.h"
#include "..\Account\\Account.h"
#include "..\TradeOrder\TradeOrder.h"
#include "..\Common\StockOfferingManager\StockOfferingManager.h"

#define MAX_STOCK_TAB_NUMBER		4
#define MAX_STOCK_ORDER_NUMBER		5000	// ���� ���� �ֹ� ����. 
#define MAX_AMOUNT_PER_DEAL			1000	// �ѹ��� �ֹ��� �� �� �ִ� �ִ� ��. 
#define MAX_STOCK_ACOUNT_NUMBER		100000	// �ֽİ��� ����. 
#define MAX_STOCK_KIND_IN_ACOUNT	10		// �Ѱ��´� ���� ���ִ� �ֽ� ���� ��. 

#define MAX_STOCKBIDDER_INVILLAGE	20		// �Ѹ����� �ִ� �����ڼ�

class cltTime;

class cltTaxPaymentListDlg;


//***************************************************************************************************
//
// Class Name 		: CRequsetIncreaseStockInfo
//
// Last Modified 	: 2006 / 01 / 26
// Created		 	: �豤��
//
// Function			: ���� ���� �ֽ� ���� ����
//
//***************************************************************************************************
class cltStockBidVillageInfo
{
public:
	SI32	siVillageUnique_;				 // ���� ����ũ 
	SI32	siTotalStockAmount_;
	SI32	siTottalIncreaseStockAmount_;	 // �� ���� �ֽļ� 
	SI32	siLeftIncreaseStockAmount_;		 // ���� �ֽķ�
	GMONEY	siCurrentStockPrice_;			 // 1�� ���� �ֽİ� 

	cltDate	clBiddingDate_; // ���� ������

	cltStockBidVillageInfo()
	{
		siVillageUnique_ = 0;
		siTotalStockAmount_ = 0;
		siTottalIncreaseStockAmount_ = 0;
		siLeftIncreaseStockAmount_ = 0;
		siCurrentStockPrice_ = 0;

		clBiddingDate_.Set( 0, 0, 0, 0, 0 );
	}

	void Set( cltStockBidVillageInfo *pStockBidVillageInfo )
	{
		siVillageUnique_ = pStockBidVillageInfo->siVillageUnique_;
		siTotalStockAmount_ = pStockBidVillageInfo->siTotalStockAmount_;
		siTottalIncreaseStockAmount_ = pStockBidVillageInfo->siTottalIncreaseStockAmount_;
		siLeftIncreaseStockAmount_ = pStockBidVillageInfo->siLeftIncreaseStockAmount_;
		siCurrentStockPrice_ = pStockBidVillageInfo->siCurrentStockPrice_;

		clBiddingDate_.Set( &pStockBidVillageInfo->clBiddingDate_ );
	};
};
/*
class cltStockBidVillageInfo
{
public:
cltStockBidVillageInfo() {};

void Set( cltStockBidVillageInfo *pStockBidVillageInfo ) {

siVillageUnique = pStockBidVillageInfo->siVillageUnique;
clBiddingDate.Set( &pStockBidVillageInfo->clBiddingDate );
siStockAmount = pStockBidVillageInfo->siStockAmount;
siBeginningPrice = pStockBidVillageInfo->siBeginningPrice;
};

SI32					siVillageUnique;				// ���� ����ũ 
cltDate					clBiddingDate;					// �ֱ� �ֽ� �����
SI32					siStockAmount;					// ���� �ֽļ� 
GMONEY					siBeginningPrice;				// ���� ���۰� 
};
*/

// ���� �ֽ� ������ 
class cltStockBidder
{
public:
	cltStockBidder() {};

	cltSimplePerson			clPerson;			// ������ 

	SI32					siVillageUnique;	// ���� ���� 

	SI32					siAmount;			// �ֽ� ���� 
	GMONEY					siPrice;			// �ֽ� ���� 

	cltDate					clDate;				// ������


public:
	void					Set( cltStockBidder *pclStockBidder )
	{
		clPerson.Set( &pclStockBidder->clPerson );

		siVillageUnique = pclStockBidder->siVillageUnique;

		siAmount = pclStockBidder->siAmount;
		siPrice = pclStockBidder->siPrice;

		clDate.Set( &pclStockBidder->clDate );
	}
};


// �ֽ� ������ ������ 
class cltStockBidderManager
{
public:
	cltStockBidderManager() {};

#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockBidder, MAX_STOCKBIDDER_INVILLAGE>		clStockBidder;
#else
	cltStockBidder			clStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];			// ������ ����Ʈ
#endif

	cltDate					clBiddingDate;										// �ֱ� ���� �ֽ� ����� 

	BOOL					bBidding;											// ������
};

// ��� ���� �� ������ ó��
class cltResultStockBidder
{
public:
	cltResultStockBidder() {
		ZeroMemory( this, sizeof( cltResultStockBidder ) );
	};

	BOOL					bSuccessfulBid;				// ���� ����

	SI32					siPersonID;					// ������ PersonID
	cltMoney				clPersonBankMoney;			// ������ ���� ���� �ܰ�

	BOOL					bExceedLimit;				// �ѵ��� �ʰ� �ߴ°�?
	cltMoney				clBidMoney;					// �� ���� �ݾ� 
};



//-------------------------------
// �ֽİ�������.
//-------------------------------
//class cltStockAccountUnit{
//private:
//
//public:
//	SI32 siVillageUnique;
//	SI32 siAmount;
//
//	cltStockAccountUnit()
//	{
//		ZeroMemory(this, sizeof(cltStockAccountUnit));
//	}
//
//	void Init()
//	{
//		ZeroMemory(this, sizeof(cltStockAccountUnit));
//	}
//
//	void Init(SI32 villageunique, SI32 amount)
//	{
//		siVillageUnique		= villageunique;
//		siAmount			= amount;
//	}
//
//	bool IsSame(cltStockAccountUnit* pclunit)
//	{
//		if(siVillageUnique != pclunit->siVillageUnique)return false;
//
//		if(siAmount != pclunit->siAmount)return false;
//
//		return true;
//	}
//	
//};
class cltStockAccountUnit
{
private:

public:
	SI32 siVillageUnique;
	SI32 siAmount;
	SI32 siLimitBuyBidStockAmount;
	bool bBuySwitch; // false�϶� �����ֽ��� �� �� �ִ�

	cltStockAccountUnit()
	{
		ZeroMemory(this, sizeof(cltStockAccountUnit));
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltStockAccountUnit));
	}

	void Init(SI32 villageunique, SI32 amount)
	{
		siVillageUnique		= villageunique;
		siAmount			= amount;
		siLimitBuyBidStockAmount = 0;
		bBuySwitch			= false;
	}

	bool IsSame(cltStockAccountUnit* pclunit)
	{
		if(siVillageUnique != pclunit->siVillageUnique)return false;

		if(siAmount != pclunit->siAmount)return false;

		return true;
	}

};


class cltStockAccount {
public:
	SI32			siPersonID;		// ���� ���� PersonID

#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockAccountUnit, MAX_STOCK_KIND_IN_ACOUNT>		clUnit;
#else
	cltStockAccountUnit clUnit[MAX_STOCK_KIND_IN_ACOUNT];			// �ܰ� . 
#endif
	
	cltStockAccount()
	{
		siPersonID	= 0;
	};

	cltStockAccount(SI32 sipersonid)
	{
		siPersonID	= sipersonid;
	};

	~cltStockAccount(){}
	
	void Init()
	{
		siPersonID	= 0;

		for(SI32 i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
		{
			clUnit[i].Init();
		}
	}

	void Init(SI32 sipersonid)
	{
		siPersonID	= sipersonid;

		for(SI32 i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
		{
			clUnit[i].Init();
		}
	}
	
	void Set(cltStockAccount* pclinfo)
	{
		memcpy(this, pclinfo, sizeof(cltStockAccount));
	}
	
	// Ư�� ������ �ֽļ��� �����Ѵ�. 
	void Set(SI32 villageunique, SI32 amount);
	
	// Ư�� ������ �ֽ� ���� �ľ��ؼ� �����Ѵ�.
	SI32 GetStockAmount(SI32 villageunique);
	
	// �ֽ��� �߰��Ѵ�. 
	BOOL Add(SI32 villageunique, SI32 tradeamount);
	// �ֽ��� ����.
	BOOL Sub(SI32 villageunique, SI32 tradeamount);

	// ���� �����ΰ�?
	bool IsSame(cltStockAccount* pclaccount)
	{
		if(siPersonID != pclaccount->siPersonID)return false;

		for(SI32 i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
		{
			if(clUnit[i].IsSame( &pclaccount->clUnit[i] ) == false)return false;
		}

		return true;
	}
	
	
	// �ֽ��� �ּ��� 1�� �̻� ������ �ִ°�?
	bool HaveStock()
	{
		for(SI32 i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
		{
			if(clUnit[i].siVillageUnique)return true;
		}

		return false;
	}
};


//-----------------------------------------------
// ���� ���� �ֹ� ������. 
//-----------------------------------------------
class cltStockOrderManager : public cltTradeOrderManager{
public:

	cltStockOrderManager();
	~cltStockOrderManager();

};


//-------------------------------------------------
// �������� ����. 
//-------------------------------------------------
class cltStockMarket : public cltStructureBasic{
private:

public:
	cltStockMarket(SI32 sivillageunique);
	~cltStockMarket();

};



//--------------------------------------------------
// ���ǰ�����. 
//--------------------------------------------------
class cltStockManager : public cltStructureMngBasic{
public:

	cltStockOrderManager*	pclOrderManager;		// �ֽ� ����, ���� �ֹ� ������. 

	// SI32					siMostOrderMode;		// ���� �ֹ��� ���. (����, ����. ) 
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTradeOrder, MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM>		clSellMostOrder;
	NSafeTArray<cltTradeOrder, MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM>		clBuyMostOrder;
#else
	cltTradeOrder			clSellMostOrder[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];			// ���� �ֹ�. 
	cltTradeOrder			clBuyMostOrder[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM];			// ���� �ֹ�. 
#endif
	
    GMONEY					siAverageSellMoney;
	GMONEY					siAverageBuyMoney;

	cltStockAccount			clOldStockInfo;


	BOOL					bInitBuyOrder;
	BOOL					bInitSellOrder;

	// ���� ���� 
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockBidVillageInfo, MAX_VILLAGE_NUMBER>		clStockBidVillageInfo;
	NSafeTArray<cltStockBidderManager, MAX_VILLAGE_NUMBER>		clStockBidderManager;

	NSafeTArray<cltStockBidder, MAX_STOCKBIDDER_INVILLAGE>		clClientStockBidder;
#else
	cltStockBidVillageInfo	clStockBidVillageInfo[ MAX_VILLAGE_NUMBER ];		// �������� ���� ���� 
	cltStockBidderManager	clStockBidderManager[ MAX_VILLAGE_NUMBER ];			// ������ ����

	cltStockBidder			clClientStockBidder[ MAX_STOCKBIDDER_INVILLAGE ];
#endif
	BOOL bBidding;

	BOOL UpdateStockBidVillageSwitch;											
	BOOL UpdateStockBidderSwitch;
	BOOL UpdateInvestSwitch;			// ���� ���� ���
	BOOL UpdateStockOfferingInfoSwitch;

	DWORD tickTemp;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltStockOfferingInfo, MAX_VILLAGE_NUMBER>		clStockOfferingInfo;
#else
	cltStockOfferingInfo	clStockOfferingInfo[ MAX_VILLAGE_NUMBER ];
#endif


	void InitStockBidVillage();
	void InitStockBidder( SI32 villageUnique );
	void InitClientStockBidder();
	
	//void SetStockBidVillage( SI32 villageUnique, cltDate *pclDate, SI32 siStockAmount, SI32 beginningPrice );	// ��� ���� ���� 
	void SetStockBidVillage( SI32 VillageUnique, SI32 TotalStockAmount, SI32 TottalIncreaseStockAmount, SI32 LeftIncreaseStockAmount, GMONEY CurrentStockPrice, cltDate *pclDate );	// ���ڸ��� ����
	void CompletionStockBidVillage( SI32 villageUnique );									// ��� �Ϸ� 

	cltStockManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltStockManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 charunique);
	// ������ �ż��Ѵ�.
	SI32 CreateStock(SI32 siunique);


	// ���� �ֽ��� ǥ���Ѵ�. 
	void SetHaveStock(HWND hDlg);
	// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
	void SetStockOrderList(HWND hDlg);

	void SetComboBuyKind(HWND hDlg);
	// �ŵ� ������ �޺� �ڽ��� �߰��Ѵ�. 
	void SetComboSellKind(HWND hDlg);

	// ������ �ֽ� ���� ���� ���� �ֹ��� �����Ѵ�.
	void SetMostOrder(cltTradeOrder* pclSellOrder, cltTradeOrder* pclBuyOrder, GMONEY AverageSell , GMONEY AverageBuy );

	void ShowFeeInfo( HWND hDlg );

	void SetBidItem();

	void Action(cltTime* pcltime);


	// ������ �ֹ��� �����ϴµ� �׼��� ���Ѵ�. 
	void Action(bool bdaychangedswitch);

	BOOL	ShowFeeRate( HWND hDlg, SI32 rate );
	BOOL	ShowFeeRange( HWND hDlg );
	
};


#endif
