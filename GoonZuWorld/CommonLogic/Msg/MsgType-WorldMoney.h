#ifndef _MSGTYPEWORLDMONEY_H
#define _MSGTYPEWORLDMONEY_H

#include "../../../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"
#include "../../CommonLogic/WorldMoneyMgr/WorldMoneyMgr.h"

//-------------------------------------------
// ��ť ��� â�� ����. - ��� ��ɾ��
//-------------------------------------------
class cltGameMsgResponse_SetWorldMoney_BuyDlg{
public:
	SI64				siWorldMoney; // �� �� �ִ� ��ť
	SI64				siWorldMoneyPrice; // ��ť�� ���� ( 1��ť�� �� )
	SI64				siTotalWorldMoney; // �� ����� ��ť

	cltGameMsgResponse_SetWorldMoney_BuyDlg(SI64 money , SI64 price,SI64 total)
	{
		siWorldMoney = money ;
		siWorldMoneyPrice = price ;
		siTotalWorldMoney = total ;
	}
};

class cltGameMsgRequest_Distrubution_WorldMoney{
public:
	SI64			siWorldMoney; // ��� ��ť�� ��
	SI64			siWorldMoneyPrice; // ��� ��ť�� ����

	cltGameMsgRequest_Distrubution_WorldMoney(SI64 money,SI64 price)
	{
		siWorldMoney = money ;
		siWorldMoneyPrice = price ;
	}
};

class cltGameMsgResponse_Distrubution_WorldMoney{
public:
	SI64			siWorldMoney; // ��� ��ť�� ��
	SI64			siLeftWorldMoney; // �� ���� ��ť�� ��
	SI64			siWorldMoneyPrice; // �� ��ť�� ����
	SI64			siLeftMoney; // ��� ���� ��

	cltGameMsgResponse_Distrubution_WorldMoney(SI64 worldmoney,SI64 leftworldmoney,SI64 price,SI64 leftmoney)
	{
		siWorldMoney = worldmoney ; // ��� ��ť�� ��
		siLeftWorldMoney = leftworldmoney; // �� ���� ��ť�� ��
		siWorldMoneyPrice = price; // �� ��ť�� ����
		siLeftMoney = leftmoney; // ��� ���� ��
	}
};

// ��ť �ŷ��� ����Ʈ�� �����ش�
class cltGameMsgResponse_WorldMoney_TradeList
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltWorldMoneyTradeList, 50>		clInfo;
#else
	cltWorldMoneyTradeList		clInfo[50];
#endif
	SI32						siPage;
	bool						bEnd;

	SI64						siAverageWorldMoneyPrice;

	cltGameMsgResponse_WorldMoney_TradeList(cltWorldMoneyTradeList*pclinfo,SI32 page ,bool end,SI64 price)
	{
		for ( SI32 i = 0 ; i < 50 ; i ++ )
			clInfo[i].Set(&pclinfo[i]);

		siPage = page ;
		bEnd = end ;

		siAverageWorldMoneyPrice = price;
	}
};

// ��ť�� �ŷ��ҿ� ����Ѵ�.
class cltGameMsgRequest_WorldMoney_SellOrder
{
public:
	SI64		siWorldMoney; // ����� ��ť
	SI64		siPrice; // ����� ����

	cltGameMsgRequest_WorldMoney_SellOrder(SI64 worldmoney,SI64 price)
	{
		siWorldMoney = worldmoney ;
		siPrice = price ;
	}
};

class cltGameMsgResponse_WorldMoney_SellOrder
{
public:
	SI32		siResult;

	SI64		siWorldMoney; // ����� ��ť
	SI64		siPrice; // ����� ����

	SI64		siLeftWorldMoney; // ����� ���� ��ť

	SI64		siLeftMoney; // ���� ���� ���� ��

	cltGameMsgResponse_WorldMoney_SellOrder(SI32 result,SI64 worldmoney,SI64 leftworldmoney,SI64 price,SI64 leftmoney)
	{
		siResult = result;

		siWorldMoney = worldmoney ;
		siPrice = price ;

		siLeftWorldMoney = leftworldmoney ;

		siLeftMoney = leftmoney ;
	}
};

// ��ť�� �ŷ��ҿ��� �����Ѵ�.
class cltGameMsgRequest_WorldMoney_BuyOrder
{
public:
	SI32		siIndex; // �� ����Ʈ�� �ε���
	SI64		siWorldMoney; // �� ��ť

	cltGameMsgRequest_WorldMoney_BuyOrder(SI32 index , SI64 worldmoney)
	{
		siIndex = index ;
		siWorldMoney = worldmoney ;
	}
};

class cltGameMsgResponse_WorldMoney_BuyOrder
{
public:
	SI32		siResult;

	SI64		siWorldMoney; // �� ��ť
	SI64		siLeftWorldMoney; // �� ���� �� ��ť

	SI64		siLeftMoney; // ��� ���� ��

	cltGameMsgResponse_WorldMoney_BuyOrder(SI32 result,SI64 worldmoney,SI64 leftworldmoney,SI64 leftmoney)
	{
		siResult = result ;

		siWorldMoney = worldmoney ;
		siLeftWorldMoney = leftworldmoney ;

		siLeftMoney = leftmoney ;
	}
};

class cltGameMsgResponse_WorldMoney_CancelOrder
{
public:
	SI32		siResult;

	SI64		siLeftWorldMoney; // ȸ���� ���� �� ��ť

	cltGameMsgResponse_WorldMoney_CancelOrder(SI32 result,SI64 leftworldmoney)
	{
		siResult = result ;

		siLeftWorldMoney = leftworldmoney ;
	}
};

class cltGameMsgResponse_WorldMoney_Set_Char
{
public:
	TCHAR		szCharName[MAX_PLAYER_NAME];

	SI64		siWorldMoney;
	SI64		siLeftWorldMoney;

	cltGameMsgResponse_WorldMoney_Set_Char(TCHAR *name,SI64 worldmoney,SI64 leftworldmoney)
	{
		MStrCpy(szCharName,name,MAX_PLAYER_NAME);

		siWorldMoney = worldmoney ;
		siLeftWorldMoney = leftworldmoney ;
	}
};


//----------------------------------------------
// TradeServer
//----------------------------------------------
// Ʈ���̵� ������ �ֹ��� �ø���.
class cltGameMsgRequest_TradeServer_Set_SellOrder
{
public:
	cltItem			clitem; // �ֹ�ǰ
	SI16			siPos; // �ֹ�ǰ ��ġ

	SI64			siPrice; // �ֹ�ǰ ����

	cltGameMsgRequest_TradeServer_Set_SellOrder(cltItem*pclitem,SI16 pos,SI64 price)
	{
		clitem.Set(pclitem) ;
		siPos = pos ;

		siPrice = price ;
	}
};

class cltGameMsgResponse_TradeServer_Set_SellOrder
{
public:
	SI32		siResult;

	//cltItem		clitem; // �ֹ�ǰ
	cltTradeServerOrder clOrder;
	SI16		siPos; // �ֹ�ǰ ��ġ
	cltItem		clLeftItem; // �ֹ��� ���� ������

	SI64		siLeftWorldMoney; // �ֹ��� ���� ��ť

	cltGameMsgResponse_TradeServer_Set_SellOrder(SI32 result,cltTradeServerOrder*pclorder,SI16 pos,cltItem*pclleftitem,SI64 leftworldmoney)
	{
		siResult = result ;

		clOrder.Set(pclorder);
		siPos = pos ;
		clLeftItem.Set(pclleftitem);

		siLeftWorldMoney = leftworldmoney ;
	}
};

// Ʈ���̵� ������ �ֹ��� ������.
class cltGameMsgRequest_TradeServer_Cancel_SellOrder
{
public:
	SI32			siItemUnique;
	SI32			siItemNum;
	SI32			siIndex;

	cltGameMsgRequest_TradeServer_Cancel_SellOrder(SI32 unique,SI32 itemnum,SI32 index)
	{
		siItemUnique = unique ;
		siItemNum = itemnum ;
		siIndex = index ;
	}
};

class cltGameMsgResponse_TradeServer_Cancel_SellOrder
{
public:
	SI32		siResult;

	cltTradeServerOrder		clOrder; // �ֹ�ǰ
	SI16		siPos; // �ֹ�ǰ ��ġ
	cltItem		clLeftItem; // �ֹ��� ���� ������

	cltGameMsgResponse_TradeServer_Cancel_SellOrder(SI32 result,cltTradeServerOrder*pclOrder,SI16 pos,cltItem*pclleftitem)
	{
		siResult = result ;

		clOrder.Set(pclOrder);
		siPos = pos ;
		clLeftItem.Set(pclleftitem);
	}
};

// Ʈ���̵� ������ �ֹ��� ���.
class cltGameMsgRequest_TradeServer_Set_BuyOrder
{
public:
	cltTradeServerOrder		clOrder; // �ֹ�ǰ

	cltGameMsgRequest_TradeServer_Set_BuyOrder(cltTradeServerOrder*pclorder)
	{
		clOrder.Set(pclorder);
	}
};

class cltGameMsgResponse_TradeServer_Set_BuyOrder
{
public:
	SI32		siResult;

	cltTradeServerOrder		clOrder; // �ֹ�ǰ
	SI16		siPos; // �ֹ�ǰ ��ġ
	cltItem		clLeftItem; // �ֹ��� ���� ������
	SI64		siLeftWorldMoney;

	cltGameMsgResponse_TradeServer_Set_BuyOrder(SI32 result,cltTradeServerOrder*pclOrder,SI16 pos,cltItem*pclleftitem,SI64 worldmoney)
	{
		siResult = result ;

		clOrder.Set(pclOrder);
		siPos = pos ;
		clLeftItem.Set(pclleftitem);
		siLeftWorldMoney = worldmoney;
	}
};

// Ʈ���̵� ������ ����Ʈ�� ��û�Ѵ�.
class cltGameMsgRequest_TradeServer_Get_ListInfo
{
public:
	SI32			siIndex; // ������ ����ũ��!

	cltGameMsgRequest_TradeServer_Get_ListInfo(SI32 index)
	{
		siIndex = index ;
	}
};

//class cltGameMsgResponse_TradeServer_Get_ListInfo
//{
//public:
//	cltTradeServerOrder			clInfo[MAX_TRADESERVER_GET_LIST];
//
//	SI32						siIndex;
//	bool						bEnd;
//
//	cltGameMsgResponse_TradeServer_Get_ListInfo(cltTradeServerOrder*pclinfo,SI32 index,bool end)
//	{
//		for ( SI32 i = 0 ; i < 50 ; i ++ )
//		{
//			clInfo[i].Set(&pclinfo[i]);
//		}
//
//		siIndex = index ;
//		bEnd = end ;
//	}
//};

class cltGameMsgResponse_TradeServer_Get_ListInfo
{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltTradeServerOrder, MAX_TRADESERVER_GET_LIST>		clInfo;
#else
	cltTradeServerOrder			clInfo[MAX_TRADESERVER_GET_LIST];
#endif

	SI32						siIndex;
	bool						bEnd;
	SI64						siAveragePrice; // ��ǰ�� �ü�
	SI64						siAverageWorldMoney; // ��ť�� �ü�
	bool						bIsItem; // �ö�� �ִ� �������� �ֳ�?

	bool						bIsWorldTradeTax;			// ���� ���� ���뿩��
	SI32						siSpecialTaxRange;		// Ư���� ���� ����
	SI32						siSpecialTaxRate;		// Ư������

	cltGameMsgResponse_TradeServer_Get_ListInfo(cltTradeServerOrder*pclinfo,SI32 index,bool end,
		SI64 price,SI64 worldmoney,bool isitem, bool isworldtradetax, SI32 specialtaxrange,
		SI32 specialtaxrate )
	{
		for ( SI32 i = 0 ; i < 50 ; i ++ )
		{
			clInfo[i].Set(&pclinfo[i]);
		}

		siIndex = index ;
		bEnd = end ;

		siAveragePrice = price ;
		siAverageWorldMoney = worldmoney ;

		bIsItem = isitem ;

		bIsWorldTradeTax = isworldtradetax;
		siSpecialTaxRange = specialtaxrange;
		siSpecialTaxRate = specialtaxrate;
	}
};


// Ʈ���̵� �������� �ȸ� ���ǿ� ���� ������ �޾Ѵ�.
class cltGameMsgResponse_TradeServer_Get_SellInfo
{
public:
	cltTradeServerOrder	clOrder;

	SI64				siLeftWorldMoney;

	cltGameMsgResponse_TradeServer_Get_SellInfo(cltTradeServerOrder*pclinfo,SI64 worldmoney)
	{
		clOrder.Set(pclinfo);

		siLeftWorldMoney = worldmoney ;
	}
};

// Ʈ���̵� ������ �ø� �ڱ� ������ ������ �޴´� - �̰� ���� �������� �ð����� ���Ͽ� Ʋ�� ���� �ִ�!
class cltGameMsgResponse_TradeServer_Get_MyInfo
{
public:
	cltTradeServerOrder clOrder;

	cltGameMsgResponse_TradeServer_Get_MyInfo(cltTradeServerOrder* pclorder)
	{
		clOrder.Set(pclorder);
	}
};


// ���������� ����� ��ť�� �ŷ������� �޴´�
class cltGameMsgResponse_TradeServer_Get_SavedACU_List
{
public:
	SI64				m_siSavedACU;

	cltTradeAcuList		m_clAcuList[MAX_TRADESERVER_GET_LIST];

	cltGameMsgResponse_TradeServer_Get_SavedACU_List( SI64 siSavedACU, cltTradeAcuList* pclAcuList )
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_TradeServer_Get_SavedACU_List) );

		m_siSavedACU = siSavedACU;

		if ( pclAcuList )
		{
			memcpy( m_clAcuList, pclAcuList, sizeof(m_clAcuList) );
		}
	}
};	// GAMEMSG_RESPONSE_TRADESERVER_GET_SAVEDACU_LIST

// ����� ��ť �޾ƿ���
class cltGameMsgRequest_TradeServer_Get_Withdraw_Acu
{
public:
	SI64	m_siWithdrawAcu;

	cltGameMsgRequest_TradeServer_Get_Withdraw_Acu( SI64 siWithdrawAcu )
	{
		m_siWithdrawAcu = siWithdrawAcu;
	}
};	// GAMEMSG_REQUEST_TRADESERVER_GET_WITHDRAW_ACU

class cltGameMsgResponse_TradeServer_Get_Withdraw_Acu
{
public:
	SI64	m_siHoldingAcu;		// ����� ���� ���� �ִ� ��ť

	SI64	m_siLeftSavedAcu;	// ���޵ǰ� ���� ����� ��ť
	

	cltGameMsgResponse_TradeServer_Get_Withdraw_Acu( SI64 siHoldingAcu, SI64 siLeftSavedAcu )
	{
		m_siHoldingAcu		= siHoldingAcu;
		m_siLeftSavedAcu	= siLeftSavedAcu;
	}
};	// GAMEMSG_RESPONSE_TRADESERVER_GET_WITHDRAW_ACU
//-----------------------------------------------------------------------------------------------
//
// �������� ����
//
//-----------------------------------------------------------------------------------------------

// ���� �߱�
class cltGameMsgRequest_WorldPassport_Set
{
public:
	TCHAR	m_szPassportName[ Const_Max_WorldPassport_Name ];
	

	cltGameMsgRequest_WorldPassport_Set( TCHAR* pszPassportName )
	{
		// Init
		ZeroMemory( this, sizeof(cltGameMsgRequest_WorldPassport_Set) );

		// Set
		if ( pszPassportName )
		{
			MStrCpy( m_szPassportName, pszPassportName, Const_Max_WorldPassport_Name );
		}
	}
};	// GAMEMSG_REQUEST_WORLDPASSPORT_SET

class cltGameMsgResponse_WorldPassport_Set
{
public:
	TCHAR	m_szPassportName[ Const_Max_WorldPassport_Name ];

	SI32	m_siIssueDateVary;	// ������
	SI32	m_siExpireDateVary;	// ������

	SI64	m_siLeftAcu;		// ���� ����� ���� ���� �� ��ť


	cltGameMsgResponse_WorldPassport_Set( TCHAR* pszPassportName, SI32 siIssueDateVary, SI32 siExpireDateVary, SI64 siLeftAcu )
	{
		// Init
		ZeroMemory( this, sizeof(cltGameMsgResponse_WorldPassport_Set) );

		// Set
		if ( pszPassportName )
		{
			MStrCpy( m_szPassportName, pszPassportName, Const_Max_WorldPassport_Name );
		}

		m_siIssueDateVary	= siIssueDateVary;
		m_siExpireDateVary	= siExpireDateVary;

		m_siLeftAcu			= siLeftAcu;
		
	}
};	// GAMEMSG_RESPONSE_WORLDPASSPORT_SET

// ���� �Ⱓ ����

//----------------------------------------------------------------
// Request�� �޽����� ����
// GAMEMSG_REQUEST_WORLDPASSPORT_EXTEND
//----------------------------------------------------------------

class cltGameMsgResponse_WorldPassport_Extend
{
public:
	SI32	m_siExpireDateVary;	// ������

	SI64	m_siLeftAcu;		// ���� ����� ���� ���� �� ��ť

	
	cltGameMsgResponse_WorldPassport_Extend( SI32 siExpireDateVary, SI64 siLeftAcu )
	{
		// Init
		ZeroMemory( this, sizeof(cltGameMsgResponse_WorldPassport_Extend) );

		// Set
		m_siExpireDateVary	= siExpireDateVary;

		m_siLeftAcu			= siLeftAcu;
	}

	
};	// GAMEMSG_RESPONSE_WORLDPASSPORT_EXTEND

#endif