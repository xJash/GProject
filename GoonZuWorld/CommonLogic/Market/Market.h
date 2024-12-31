//---------------------------------
// 2003/6/18 ���°�
//---------------------------------
#ifndef _MARKET_H
#define _MARKET_H

#include <Stdio.h>
#include "..\StructureClass\StructureClass.h"
#include "..\Account\\Account.h"

#include "../Client/Inventory/ItemInventoryBaseDefinition.h"

#include "..\..\Common\Item\ItemCommon\cltitem.h"
#include "..\TradeOrder\TradeOrder.h"

#define MAX_MARKET_TAB_NUMBER		4

// �߱��� �����ŷ� 20000��
#ifdef _CHINA
	#define MAX_MARKET_ORDER_NUMBER		30000
#else
	#define MAX_MARKET_ORDER_NUMBER		15000
#endif

#if defined (_CHINA)
	#define MAX_RESPONSE_ORDER_NUMBER	150				// ������ �ֹ� ������ �� ���� ��ŭ�� �޴´�. 
#elif defined (_KOREA)
	#define MAX_RESPONSE_ORDER_NUMBER	150
#else
	#define MAX_RESPONSE_ORDER_NUMBER	100	
#endif

#define MAX_PRICE_IN_MARKET			100000000000	// 1000��. ���ֿ� �÷� ���� �� �ִ� �ִ� ����. 
#define MARKET_ORDER_SEND_UNIT		10				// ���� �ֹ��� 10�� ������ Ŭ���̾�Ʈ�� ��������. 

#define MAX_NEWMARKET_ITEMLIST				 50
#define	MAX_PERSON_NEWMARKET_ORDER_NUM		 12	// PERSON �� �Ǹ� ����� ������ ��.

class cltTaxPaymentListDlg;

class cltGameMsgRequest_NewSellItem
{
public:
	cltNewTradeOrder	clTradeOrder;

	SI16				siPos;

	cltGameMsgRequest_NewSellItem(cltNewTradeOrder* pclorder,SI16 pos)
	{
		clTradeOrder.Set(pclorder);

		siPos = pos ;
	}
};

// ���ַκ��� �������� ȸ���ϱ� ���� ����. 
class cltGetItemFromMarketInfo
{
public:
	SI32	siPersonID;		// ����� �Ǵ� Person
	
	SI32	siFromPos;		// �������� ���³� ��ġ. 
	bool	bPileSwitch;	// �����Ǵ��� ����. 
	cltItem clFromItem;		// �������� ���³� ��ġ�� �����ϴ� ������.
							// ������ ������ siItemNum�� ������Ʈ �Ǿ� �־�� �Ѵ�. 

	SI32	siToPos;		// �������� ������ ���� �κ��� ��ġ. 
	cltItem clToItem;		// �������� ������ ���� �κ��� ��ġ�� �����ϴ� ������ ����. 


	cltGetItemFromMarketInfo(SI32 personid, SI32 frompos, bool pileswitch, cltItem* pclfromitem, SI32 topos, cltItem* pcltoitem)
	{
		siPersonID	= personid;
		siFromPos	= frompos;
		bPileSwitch	= pileswitch;
		clFromItem.Set(pclfromitem);

		siToPos		= topos;
		if(pcltoitem)
		{
			clToItem.Set(pcltoitem);
		}
		else
		{
			clToItem.Init();
		}
	}

};

// ������� ���� ã��
class cltGetItemFromNewMarketInfo{
public:

	SI32	siOrderIndex;		// �ֹ���ȣ
	bool	bPileSwitch;		// �����Ǵ��� ����. 
	cltItem clFromItem;		// �������� ���³� ��ġ�� �����ϴ� ������.
	//������ ������ siItemNum�� ������Ʈ �Ǿ� �־�� �Ѵ�. 

	SI32	siToPos;			// �������� ������ ���� �κ��� ��ġ. 
	cltItem clToItem;		// �������� ������ ���� �κ��� ��ġ�� �����ϴ� ������ ����. 


	cltGetItemFromNewMarketInfo(SI32 orderindex, bool pileswitch, cltItem* pclfromitem, SI32 topos, cltItem* pcltoitem)
	{
		siOrderIndex	= orderindex;
		bPileSwitch		= pileswitch;
		clFromItem.Set(pclfromitem);

		siToPos			= topos;
		pcltoitem ? clToItem.Set(pcltoitem) : clToItem.Init();
	}
};
//--------------------------------------------
// ���� ���� ����. 
//--------------------------------------------	
class cltMarketAccount 
{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMoney,	MAX_MARKET_ORDER_PER_PERSON>		clMoney;
	NSafeTArray<cltItem,	MAX_MARKET_ORDER_PER_PERSON>		clItem;
#else
	cltMoney	clMoney[MAX_MARKET_ORDER_PER_PERSON];		// �������� ����. 
	cltItem		clItem[MAX_MARKET_ORDER_PER_PERSON];		// ���ֿ� �÷����� ������ ����. 
#endif

	cltMarketAccount() 
	{
		Init();
	};


	~cltMarketAccount(){}
	
	void Init()
	{
		for(SI32 i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
		{
			clMoney[i].Init();
			clItem[i].Init();
		}
	}

	void Set(cltMarketAccount* pclinfo)
	{
		memcpy(this, pclinfo, sizeof(cltMarketAccount));
	}

	BOOL IsSame(cltMarketAccount* pclaccount);

	// Ư�� �������� ���� �ľ��ؼ� �����Ѵ�.
	SI32 GetItemNum(cltItem* pclitem);
	
	// ������  �߰��Ѵ�. 
	BOOL Add(cltItem* pclitem, SI32 tradeamount);
	// ������ ����.
	BOOL Sub(cltItem* pclitem, SI32 tradeamount);
	
	// Ư���� �������� ã�Ƽ� �� �����͸� �����ش�. 
	cltItem* FindItem(const cltItem* pclitem, bool numcomp);
	
	// ���� �ֹ� ������ ������Ʈ �Ѵ�. 
	bool UpdateMarketOrder(SI32 index, cltTradeOrder* pclorder);
};

class cltNewMarketAccount
{
public:

	SI32		siOrderIndex[MAX_NEWMARKET_ORDER_PER_PERSON];
	cltMoney	clMoney[MAX_NEWMARKET_ORDER_PER_PERSON];		// �������� ����. 
	cltItem		clItem[MAX_NEWMARKET_ORDER_PER_PERSON];			// ���ֿ� �÷����� ������ ����. 

	cltNewMarketAccount() 
	{
		Init();
	};


	~cltNewMarketAccount(){}

	void Init()
	{

		for(SI32 i = 0;i < MAX_NEWMARKET_ORDER_PER_PERSON;i++)
		{
			siOrderIndex[i] = -1;
			clMoney[i].Init();
			clItem[i].Init();
		}
	}

	void Set(cltNewMarketAccount* pclinfo)
	{
		memcpy(this, pclinfo, sizeof(cltNewMarketAccount));
	}

	BOOL IsSame(cltNewMarketAccount* pclaccount);

	// Ư�� �������� ���� �ľ��ؼ� �����Ѵ�.
	SI32 GetItemNum(cltItem* pclitem);

	// Ư���� �������� ã�Ƽ� �� �����͸� �����ش�. 
	cltItem* FindItem(const cltItem* pclitem, bool numcomp);
};

//-----------------------------------------------
// �������� ���� 
//-----------------------------------------------
class cltMarket : public cltStructureBasic
{
public:

	cltMarket(SI32 sivillageunique);
	~cltMarket();
};


//----------------------------------------------
// ���� ������. 
//----------------------------------------------
class cltMarketManager : public cltStructureMngBasic
{
public:
	cltTradeOrderManager*	pclOrderManager;		// ����, ���� �ֹ� ������. 

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32*,	MAX_ITEMTYPE_NUMBER>		pclItemTypeSearch;
	NSafeTArray<SI32*,	MAX_ITEMTYPE_NUMBER>		pclItemTypeOrder;
	NSafeTArray<SI32,	MAX_ITEMTYPE_NUMBER>		siItemTypeOrderIndex;
#else
	SI32*											pclItemTypeSearch[MAX_ITEMTYPE_NUMBER];	
	SI32*											pclItemTypeOrder[MAX_ITEMTYPE_NUMBER];	// �� ������ Ÿ�Ժ��� �ֹ� ���. 
	SI32											siItemTypeOrderIndex[MAX_ITEMTYPE_NUMBER];
#endif

	// ���Ͽ� ��ϵ� �����۵��� �ּҰ��ݰ� �� �������� ��� ������ �����Ѵ�.
#ifdef _SAFE_MEMORY
	NSafeTArray<GMONEY, MAX_ITEMINFO_NUMBER>		m_MinPrice;								// ������ �� ��������
	NSafeTArray<SI32,	MAX_ITEMINFO_NUMBER>		m_MinPriceAmount;						// �������� �������� ��� ����
#else
	GMONEY											m_MinPrice[MAX_ITEMINFO_NUMBER];		// ������ �� ��������
	SI32											m_MinPriceAmount[MAX_ITEMINFO_NUMBER];	// �������� �������� ��� ����
#endif

	BOOL					ImageListConnectedSwitch;
	cltPItemInfo			clOldPersonItemInfo;

	BOOL					ImageListConnectedToStorageSwitch;	
	cltMarketAccount		clOldAccount;

	BOOL					SellButtonEnableSwitch;
	BOOL					GetFromMarketButtonEnableSwitch;

	cltItem*				pclCurrentInvItem;						// ���� ���õ� �κ��丮 ������.
	cltItem					clCurrentInvItem;

	cltItem*				pclCurrentStgItem;						// ���� ���õ� ���� â�� ������.
	SI32					CurrentStgItemIndex;					// ���� ���õ� ���� â�� �������� â�� �ε���. 

	HBITMAP					m_hItemImage;
	HBITMAP 				m_hItemMallBitmap;

	cltItem 				clCurrentStgItem;

	BOOL 					bResponseEmptyOrder;
	BOOL 					ShowResponseOrderSiwtch;
	SI32 					siResponseOrderIndex;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltTradeOrder, MAX_RESPONSE_ORDER_NUMBER>	clResponseOrder;
#else
	cltTradeOrder											clResponseOrder[MAX_RESPONSE_ORDER_NUMBER];	// �������� ���� �ֹ������� ������ ����. 
#endif

	SI32 	CurrentSelectedBuyItemUnique;						// ���Ÿ� �������� ���� ���õ� �������� ����ũ. 

	HWND 	hUserDlgBuyHwnd;									// ���� ��ȭ������ �ڵ�. 

	HWND 	m_hUserDlgBuyList;									// �� ���� ����Ʈ�� �ڵ�
	SI32 	m_siSelectedBuyList;								// �� ���� ����Ʈ���� ������ ����

#ifdef _SAFE_MEMORY
	NSafeTArray<SI32, MAX_RESPONSE_ORDER_NUMBER>		m_siSelectedBuyIndex;
#else
	SI32												m_siSelectedBuyIndex[MAX_RESPONSE_ORDER_NUMBER];	// �� ���� ����Ʈ���� ������ ���ǵ��� �ε���
#endif

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_MARKET_ORDER_NUMBER>			siRefBuffer;
#else
	SI16												siRefBuffer[MAX_MARKET_ORDER_NUMBER];
#endif
	
	SI32	siRefBufferIndex;

	cltMarketManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltMarketManager();

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// ���ָ� �ż��Ѵ�.
	BOOL CreateMarket(SI32 siunique);

	// ���¿� �ִ´�. 
	BOOL Input(SI32 personid, SI32 acountnum, cltItem* pclitem, SI32 tradeamount);
	// ���¿��� ������. 
	BOOL Output(SI32 personid, SI32 acountnum, cltItem* pclitem, SI32 tradeamount);

	// Ư���������� ���� ������ �ֹ��� ã�´�. 
	bool FindLowPriceOrderInfo(SI32 unique, GMONEY* pprice, SI32* pamount);

	// ���Ͽ� ��ϵ� �����۵��� �ּҰ��ݰ� �� �������� ��� ������ �����Ѵ�.
	void MakeLowPriceOrderInfo();

	//--------------------------------------
	// Market-Manager.cpp
	//--------------------------------------
	// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
	void Action(bool bdaychangedswitch);

	// ���� ���ϰ� ó�� �Լ�. 
	void ServerRtnValOperate();

	// �������� ���� �ֹ� ������ �����Ѵ�. 
	// Ŭ���̾�Ʈ���� ���� ��û�ߴ� ������ ���� ���̴�. 
	BOOL PutResponseOrder(cltTradeOrder* pclorder);

	
	// ������ Ÿ�Ժ� ���ۿ� ���� �ֹ� ������ �߰��Ѵ�. 
	bool SetItemTypeOrder(cltTradeOrder* pclorder, SI32 orderunique);


	// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �����ϰ� ����. 
	SI16 GetRandomOrder(SI32 itemtype);

	// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �ý����� ������ ��ǰ�� �����Ѵ�. 
	cltTradeOrder* GetOrderForSystemBuy(SI32 itemtype);

	// ���ֿ� �ö�� �ִ� ��ǰ �߿��� �ý����� ������ ��ǰ�� �����Ѵ�.  - unique�� ����.	
	cltTradeOrder* GetOrderForSystemBuyUnique(SI16 itemUnique , GMONEY gPrice);

	void SystemBuyItemStatistics(SI16 siItemUnique, GMONEY gPrice);
};

//-----------------------------------------------
// �������� ����� 
//-----------------------------------------------
class cltNewMarket : public cltStructureBasic
{
public:

	cltNewMarket(SI32 sivillageunique);
	~cltNewMarket();
};


//----------------------------------------------
// ����� ������. 
//----------------------------------------------
class cltNewMarketManager : public cltStructureMngBasic
{
public:

	bool						m_bSetFee;						// �Ϸ翡 �ѹ��� ������ ������ �����ϰ�.
	bool						bUpdateItemPrice;
	bool						bUpdateItemReducePrice;

	// ���� ���� ���� 
	DWORD						dwUpdateTime;
	cltTaxPaymentListDlg*		pclTaxPaymentDlg;

	cltNewMarketManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, char *strFileName );
	~cltNewMarketManager();

	// ���� ȯ�� �λ��ȯ��ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// �����
	BOOL CreateNewMarket(SI32 siunique);

	// �Ӵ�Ḧ ó���ϴµ��� �׼��� ���Ѵ�. 
	void Action(cltTime* pcltime, clock_t CurrentClock);

	// ���� ���ϰ� ó�� �Լ�. 
	void ServerRtnValOperate();

};

#endif
