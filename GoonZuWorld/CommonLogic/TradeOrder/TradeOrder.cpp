//---------------------------------
// 2003/6/20 ���°�
//---------------------------------

#include "TradeOrder.h"
#include "..\..\CommonLogic\CommonLogic.h"

extern cltCommonLogic* pclClient;

//----------------------------------------------------------
//	cltTradeOrder
//----------------------------------------------------------
BOOL cltTradeOrder::IsSame(cltTradeOrder* porder)
{
	if(siPersonID	!= porder->siPersonID)			return FALSE;
	if(siPrice		!= porder->siPrice)				return FALSE;
	if(siAmount		!= porder->siAmount)			return FALSE;
	
	switch(siType)
	{
	case TRADEORDER_TYPE_STOCK:
		if(siVillageUnique != porder->GetVillageUnique())return FALSE;
		break;
	case TRADEORDER_TYPE_OBJECT:
		{
			cltItem clsrcitem;
			clsrcitem.Set(&clItemData);
			
			cltItem cldstitem;
			cldstitem.Set(&porder->clItemData);
			
			return clsrcitem.IsSame(&cldstitem, true);
		}
		break;
	default:
		MsgBox(TEXT("fd93"), TEXT("fd983:%d"),siType);
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------
// cltTradeOrderManager
//----------------------------------------------------------
cltTradeOrderManager::cltTradeOrderManager(SI32 maxordernum)
{
	SI32 i;

	siMaxOrderNum	= maxordernum;

	pclOrderSell	= new cltTradeOrder*[maxordernum];
	pclOrderBuy		= new cltTradeOrder*[maxordernum];


	for(i = 0;i < siMaxOrderNum;i++)
	{
		pclOrderSell[i] = new cltTradeOrder;	// ���� �ֹ� 
		pclOrderBuy[i]	= new cltTradeOrder;	// ���� �ֹ� 	
	}


}

cltTradeOrderManager::~cltTradeOrderManager()
{
	SI32 i;

	for(i = 0;i < siMaxOrderNum;i++)
	{
		if(pclOrderSell[i])
		{
			delete pclOrderSell[i];
			pclOrderSell[i] = NULL;
		}

		if(pclOrderBuy[i])
		{
			delete pclOrderBuy[i];
			pclOrderBuy[i] = NULL;
		}
	}

	if(pclOrderSell)
	{
		delete[] pclOrderSell;
		pclOrderSell = NULL;
	}
	if(pclOrderBuy)
	{
		delete[] pclOrderBuy;
		pclOrderBuy = NULL;
	}

}

// �ֹ��� �ֹ� ������ ������ �ڸ��� �ִ´�. 
bool cltTradeOrderManager::SetOrder(SI32 ordermode, cltTradeOrder* porder)
{
	if(porder == NULL)return false;

	cltTradeOrder** ppDstStockOrder = NULL;			// �ֹ�. 

	if(ordermode == ORDERMODE_SELL)
	{
		ppDstStockOrder	= pclOrderSell;
	}
	else
	{
		ppDstStockOrder	= pclOrderBuy;
	}
	
	if(porder->siType == 1)
	{
		if(porder->siAmount != 0 && porder->siVillageUnique == 0)
		{
			TCHAR* pTitle = GetTxtFromMgr(422);
			TCHAR* pText = GetTxtFromMgr(1681);
			MsgBox(pTitle, pText);
			return false;
		}
	}


	// ������ ��ġ�� �ֹ��� ������ �ִ´�.
	if(porder->siIndex < 0 || porder->siIndex >= siMaxOrderNum)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("SetOrder():0 ordermode:%d index:%d type:%d villageunique:%d price:%d"), ordermode, porder->siIndex, porder->siType, porder->siVillageUnique, porder->siPrice);
		return false;
	}
	if(ppDstStockOrder[porder->siIndex] == NULL)
	{
		if (pclClient->GameMode == GAMEMODE_SERVER)
			pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("SetOrder():1 ordermode:%d index:%d type:%d villageunique:%d price:%d"), ordermode, porder->siIndex, porder->siType, porder->siVillageUnique, porder->siPrice);
		return false;
	}

	// �ֹ� ������ 0 �̸� ������ �ۿ�. 
	if(porder->siPrice == 0)
	{
		ppDstStockOrder[porder->siIndex]->Init();
	}
	else
	{
		ppDstStockOrder[porder->siIndex]->Set(porder);
	}
	
	return true;
}

// �־��� �ֹ��� ������ �ݴ� �ֹ��� ã�´�. 
// ã���� �� �ݴ� �ֹ��� �����͸� �����ϰ� �� ã���� NULL�� �����Ѵ�. 
cltTradeOrder* cltTradeOrderManager::FindOpositeOrder(SI32 ordermode, cltTradeOrder* porder)
{

	SI32 i;
	SI32 bestindex = -1;
	GMONEY bestprice;
	
	if(ordermode == ORDERMODE_SELL)
	{
		bestprice			= porder->siPrice;

		// ������ ������ų �� �ִ� ��� �ֹ��� �ִ��� Ȯ���Ѵ�. 
		for(i = 0;i < siMaxOrderNum;i++)
		{
			// ���� ������ �ֽ��� ã�´�. 
			if(IsSameKind(pclOrderBuy[i], porder) == TRUE)
			{
				// ������ ��ȿ�� ���� ã�´�.
				if(pclOrderBuy[i]->siPrice >=  porder->siPrice)
				{
					if(pclOrderBuy[i]->siPrice >= bestprice)
					{
						// �������� �ֹ��� ������� �ʴ´�. 
						if(pclOrderBuy[i]->siPersonID != porder->siPersonID)
						{
							bestindex	= i;
							bestprice	= pclOrderBuy[i]->siPrice;
						}
					}
				}
			}
		}

		if(bestindex >= 0)
		{
			return pclOrderBuy[bestindex];
		}
	}
	else
	{
		bestprice			= porder->siPrice;

		// ������ ������ų �� �ִ� ��� �ֹ��� �ִ��� Ȯ���Ѵ�. 
		for(i = 0;i < siMaxOrderNum;i++)
		{
			// ���� ������ �ֽ��� ã�´�. 
			if(IsSameKind(pclOrderSell[i], porder) == TRUE)
			{
				// ������ ��ȿ�� ���� ã�´�.
				if(pclOrderSell[i]->siPrice <=  porder->siPrice)
				{
					if(pclOrderSell[i]->siPrice <= bestprice)
					{
						// �������� �ֹ��� ������� �ʴ´�. 
						if(pclOrderSell[i]->siPersonID != porder->siPersonID)
						{
							bestindex	= i;
							bestprice	= pclOrderSell[i]->siPrice;
						}
					}
				}
			}
		}

		if(bestindex >= 0)
		{
			return pclOrderSell[bestindex];
		}
	}
	
	return NULL;
}


bool cltTradeOrderManager::GetMostSellBuyOrder(IN cltTradeOrder* porder, OUT cltTradeOrder* pSellMostOrderList, OUT cltTradeOrder* pBuyMostOrderList, OUT GMONEY * averageSell, OUT  GMONEY * averageBuy)
{
	// ��� �ֹ��� �˻��Ͽ� ���� �� �ֹ� 10���� ���� ��� �ֹ� 10���� ã�Ƴ���.

	GMONEY worstPrice = 0;
	GMONEY sumSell = 0;
	GMONEY sumBuy = 0;
	SI32 cntSell = 0;
	SI32 cntBuy = 0;

	SI32 i = 0 , j = 0, k = 0;
	
	// ���� �� �ֹ��� 10�� ã�´�.

	for(i = 0;i < siMaxOrderNum;i++)
	{
		// ���� ������ �ֽ��� ã�´�. 
		if(IsSameKind(pclOrderSell[i], porder) == TRUE )
		{
			sumSell += pclOrderSell[i]->siPrice;
			cntSell ++;

			// �ϴ� �� ����� ������ ä���ְ� ����.
			if( pSellMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1].IsValid() == false )
			{
				for( j = 0; j < MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM; j ++ )
				{
					if( pSellMostOrderList[ j ].IsValid() == false )
					{
						pSellMostOrderList[ j ].Set( pclOrderSell[i] );
						
						break;
					}
					else if( pSellMostOrderList[ j ].siPrice > pclOrderSell[i]->siPrice )
					{
						// ����� �ϳ��� �а� ���ڸ��� ���� �ִ´�.
						for( k = MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1 ; k > j ; k-- )
						{							
							pSellMostOrderList[ k ].Set( &pSellMostOrderList[ k - 1 ] );
						}
						
                        pSellMostOrderList[ j ].Set( pclOrderSell[ i ] );
						break;	
					}					
				}				
			}
			// ������ ���� ��� ��ϰ� ���Ͽ� �� �� �ֽ��� �ִٸ� ��� ������ ���� �ִ´�.
			else if( pSellMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1].siPrice > pclOrderSell[i]->siPrice )
			{
				for( j = 0; j < MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM; j ++ )
				{
					if( pSellMostOrderList[ j ].siPrice > pclOrderSell[i]->siPrice )
					{
						// ����� �ϳ��� �а� ���ڸ��� ���� �ִ´�.
						for( k = MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1 ; k > j ; k-- )
						{							
							pSellMostOrderList[ k ].Set( &pSellMostOrderList[ k - 1 ] );
						}

						pSellMostOrderList[ j ].Set( pclOrderSell[ i ] );
						break;
					}
				}
			}
		}


		// ���� ������ �ֽ��� ã�´�. 
		if(IsSameKind(pclOrderBuy[i], porder) == TRUE )
		{
			sumBuy += pclOrderBuy[i]->siPrice;
			cntBuy ++;

			// �ϴ� �� ����� ������ ä���ְ� ����.
			if( pBuyMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1].IsValid() == false )
			{
				for( j = 0; j < MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM; j ++ )
				{
					if( pBuyMostOrderList[ j ].IsValid() == false )
					{
						pBuyMostOrderList[ j ].Set( pclOrderBuy[i] );

						break;
					}
					else if( pBuyMostOrderList[ j ].siPrice < pclOrderBuy[i]->siPrice )
					{
						// ����� �ϳ��� �а� ���ڸ��� ���� �ִ´�.
						for( k = MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1 ; k > j ; k-- )
						{							
							pBuyMostOrderList[ k ].Set( &pBuyMostOrderList[ k - 1 ] );
						}

						pBuyMostOrderList[ j ].Set( pclOrderBuy[ i ] );
						break;

					}					
				}				
			}
			// ������ ���� ��� ��ϰ� ���Ͽ� ��  ��� �ֽ� �ֹ��� �ִٸ� ��� ������ ���� �ִ´�.
			else if( pBuyMostOrderList[MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1].siPrice < pclOrderBuy[i]->siPrice )
			{
				for( j = 0; j < MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM; j ++ )
				{
					if( pBuyMostOrderList[ j ].siPrice < pclOrderBuy[i]->siPrice )
					{
						// ����� �ϳ��� �а� ���ڸ��� ���� �ִ´�.
						for( k = MAX_VILLAGESTOCK_PRICE_INFO_LIST_NUM - 1 ; k > j ; k-- )
						{							
							pBuyMostOrderList[ k ].Set( &pBuyMostOrderList[ k - 1 ] );
						}

						pBuyMostOrderList[ j ].Set( pclOrderBuy[ i ] );
						break;
					}
				}
			}
		}
	}

	if( cntSell > 0 )
	{
		*averageSell = sumSell / cntSell;		
	}
	else
	{
		averageSell = 0;
	}
	
	if( cntBuy > 0 )
	{
		*averageBuy = sumBuy / cntBuy;		
	}
	else
	{
		averageBuy = 0;
	}	

	
	return true;
}

// PersonID������ �ֹ��� ��� ����ϰ� �Ѵ�. 
BOOL cltTradeOrderManager::CancelOrder(SI32 personid)
{
	SI32 i;

	for(i = 0;i < siMaxOrderNum;i++)
	{
		if(pclOrderSell[i]->siPersonID == personid)
		{
			pclOrderSell[i]->Init();
		}

		if(pclOrderBuy[i]->siPersonID == personid)
		{
			pclOrderBuy[i]->Init();
		}

	}

	return TRUE;
}

// �ֹ� ����Ʈ���� �ε����� �ֹ� ������ Ȯ���Ѵ�. 
cltTradeOrder* cltTradeOrderManager::GetOrder(SI32 ordermode, SI32 index)
{
	if(index < 0 || index >= siMaxOrderNum)return NULL;
	
	if(ordermode == ORDERMODE_SELL)
	{
		return pclOrderSell[index];
	}
	else
	{
		return pclOrderBuy[index];
	}
}


// ���� �������� Ȯ���Ѵ�. 
BOOL cltTradeOrderManager::IsSameKind(const cltTradeOrder* pclsrc, const cltTradeOrder* pcldst)
{

	if(pclsrc->siType != pcldst->siType)return FALSE;

	
	switch(pclsrc->siType )
	{
		// �ֽ��� ��� 
	case TRADEORDER_TYPE_STOCK:
		if(pclsrc->GetVillageUnique() == pcldst->GetVillageUnique())return TRUE;
		break;
	case TRADEORDER_TYPE_OBJECT:
		{
			cltItem clItem1, clItem2;
			clItem1.Set(&pclsrc->clItemData);
			clItem2.Set(&pcldst->clItemData);
			return clItem1.IsSame(&clItem2, true);
		}
		break;

	default:
		MsgBox(TEXT("cltTradeOrderManager::IsSameKind()"), TEXT("fd98yj:%d"), pclsrc->siType);
	}
	
	return FALSE;
}

// ��ǰ �ֹ��� ���� ������ �ֹ��� ������ ã�´�. 
bool cltTradeOrderManager::FindLowPriceOrderInfo(SI32 unique, GMONEY* pprice, SI32* pamount)
{
	SI32	i;
	GMONEY minprice	= 100000000;
	SI32 minamount	= -1;

	cltItem  clItem;
	for(i = 0;i < siMaxOrderNum;i++)
	{
		clItem.Set(&pclOrderSell[i]->clItemData);
		
		if(clItem.siUnique == unique)
		{
			if(pclOrderSell[i]->siPrice < minprice && pclOrderSell[i]->bBankError == false )
			{
				minprice	= pclOrderSell[i]->siPrice;
				minamount	= pclOrderSell[i]->siAmount;
			}
		}
	}

	if(minamount > 0)
	{
		*pprice		=	minprice;
		*pamount	=	minamount;
		return true;
	}
	return false;
}


// �ֽ�  �ֹ��� ���� ������ �ֹ��� ������ ã�´�. 
bool cltTradeOrderManager::FindLowPriceStockOrderInfo(SI32 villageunique, GMONEY* pprice, SI32* pamount)
{
	SI32	i;
	GMONEY minprice	= 100000000;
	SI32 minamount	= -1;

	if(villageunique <= 0)return false;

	for(i = 0;i < siMaxOrderNum;i++)
	{
		if(villageunique == pclOrderSell[i]->siVillageUnique)
		{
			if(pclOrderSell[i]->siPrice < minprice)
			{
				minprice	= pclOrderSell[i]->siPrice;
				minamount	= pclOrderSell[i]->siAmount;
			}
		}
	}

	if(minamount > 0)
	{
		*pprice		=	minprice;
		*pamount	=	minamount;
		return true;
	}
	return false;
}

// �ֽ� �ֹ��� ���� ��� �ֹ��� ������ ã�´�. 
bool cltTradeOrderManager::FindHighPriceStockOrderInfo(SI32 villageunique, GMONEY* pprice, SI32* pamount)
{
	SI32	i;
	GMONEY maxprice	= 0;
	SI32 minamount	= -1;

	if(villageunique <= 0)return false;
	
	for(i = 0;i < siMaxOrderNum;i++)
	{
		if(villageunique == pclOrderBuy[i]->siVillageUnique)
		{
			if(pclOrderBuy[i]->siPrice > maxprice)
			{
				maxprice	= pclOrderBuy[i]->siPrice;
				minamount	= pclOrderBuy[i]->siAmount;
			}
		}
	}

	if(minamount > 0)
	{
		*pprice		=	maxprice;
		*pamount	=	minamount;
		return true;
	}
	return false;
}


// �ֹ��� ������ ���Ѵ�. 
SI32 cltTradeOrderManager::GetOrderNum(SI32 ordermode)
{
	SI32 i;
	SI32 num = 0;
	cltTradeOrder** ppOrder;

	if(ordermode == ORDERMODE_SELL)
	{
		ppOrder = pclOrderSell;
	}
	else
	{
		ppOrder = pclOrderBuy;
	}

	for(i = 0;i < siMaxOrderNum;i++)
	{
		if(ppOrder[i]->siAmount)
		{
			num ++;
		}
	}

	return num;
}

//----------------------------------------------
// cltCharOrderInfo
//----------------------------------------------
#ifdef _SAFE_MEMORY
	SI32 cltCharOrderInfo::GetOrderNumber()
#else
	SI32 cltCharOrderInfo::GetOrderNumber()const
#endif
{
	SI32 i;
	SI32 num = 0;

	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		// ������ �ִ� �͸� ��ȿ�ϴ�. 
		if(clOrderUnit[i].clOrder.siAmount)
		{
			num++;
		}
	}

	return num;
}

// �ֹ� ������ �����Ѵ�.
BOOL cltCharOrderInfo::Set(SI32 ordermode, cltTradeOrder* pclorder)
{
	SI32 i;
	
	//-----------------------------------------------
	// �̹� ���� �ε����� �ֹ��� �ִ��� Ȯ���Ѵ�. 
	//-----------------------------------------------
	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		if(clOrderUnit[i].siOrderMode)
		{
			// �ֹ��� ������ ���� �ֹ���ȣ�� ���ٸ� �����δ� ���� �ֹ��̴�. 
			// �̷� ��쿡�� ���� �ֹ��� �߰����� �ʰ� ���� �ֹ��� �����Ѵ�. 
			if(clOrderUnit[i].siOrderMode			== ordermode
				&& clOrderUnit[i].clOrder.siIndex	== pclorder->siIndex)
			{
				// ��ȿ�� �ֹ��� ���� �ʱ�ȭ�Ѵ�. 
				if(pclorder->siAmount)
				{
					clOrderUnit[i].clOrder.Set(pclorder);
				}
				else
				{
					clOrderUnit[i].siOrderMode	= 0;
					clOrderUnit[i].clOrder.Init();
				}
				
				return TRUE;
			}
		}
	}
	
	//------------------------------------------------
	// ������ �ֹ��� ���ٸ�, 
	//------------------------------------------------
	for(i = 0; i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		if(clOrderUnit[i].siOrderMode == 0)
		{
			// ��ȿ�� �ֹ��� ���� �ʱ�ȭ�Ѵ�. 
			if(pclorder->siAmount)
			{
				clOrderUnit[i].siOrderMode	= ordermode;
				clOrderUnit[i].clOrder.Set(pclorder);
			}
			else
			{
				clOrderUnit[i].siOrderMode	= 0;
				clOrderUnit[i].clOrder.Init();
			}
			return TRUE;
		}
	}
	return FALSE;
}
