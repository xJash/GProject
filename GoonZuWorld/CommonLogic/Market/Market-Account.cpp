//---------------------------------
// 2003/6/20 ���°�
//---------------------------------
#include "..\..\CommonLogic\CommonLogic.h"

#include "..\..\Resource.h"

#include "Market.h"

extern cltCommonLogic* pclClient;

//--------------------------------------------------------------------
//	cltmarketAccount
//--------------------------------------------------------------------

// ������ �߰��Ѵ�. 
BOOL cltMarketAccount::Add(cltItem* pclitem, SI32 tradeamount)
{
	SI32 i;
	BOOL pileswitch = FALSE;			// �������� ��ø ��� ����. 

	if(pclitem == NULL)return FALSE;

	// ��ø�� �ȵǴ� ���������� Ȯ���Ѵ�. 
	SI32 type = pclitem->GetType(pclClient->pclItemManager);
	if(type)
	{
		SI64 atb = pclClient->pclItemManager->pclItemTypeInfo[type]->siAtb;

		// ITEMATB_OBJECT�� �ƴϸ� ��ø�� ����Ѵ�. 
		if((atb & ITEMATB_OBJECT) == 0)
		{
			pileswitch = TRUE;
		}
	}

	// ��ø�� ���Ǵ� �������̸�, 
	if(pileswitch == TRUE)
	{
		// �̹� ���� ������ �ִ��� Ȯ���Ѵ�. 
		for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
		{
			if(clItem[i].siUnique == pclitem->siUnique)
			{
				clItem[i].Increase(tradeamount);
				
				return TRUE;
			}
		}
	}

	// ���ο� �������� �߰��Ѵ�. 
	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		if(clItem[i].siUnique == 0)
		{
			clItem[i].Set(pclitem);
			clItem[i].SetItemNum(tradeamount);
			return TRUE;
		}
	}


	return FALSE;
}

// ������ ����.
BOOL cltMarketAccount::Sub(cltItem* pclitem, SI32 tradeamount)
{
	SI32 i;

	// �̹� ���� ������ �ִ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		cltItem* pclSrcItem = &clItem[i];

		if(pclSrcItem->IsSame(pclitem, false) == TRUE)
		{
			//���� �����ֺ��� �� ���� �ָ� ���� ����. 
			if(tradeamount > pclSrcItem->GetItemNum())return FALSE;

			pclSrcItem->Decrease(tradeamount);
			if(pclSrcItem->GetItemNum() == 0)
			{
				pclSrcItem->Init();
			}

			return TRUE;
		}
	}

	return FALSE;
}

// Ư���� �������� ã�Ƽ� �� �����͸� �����ش�. 
cltItem* cltMarketAccount::FindItem(const cltItem* pclitem, bool numcomp)
{
	SI32 i;

	if(pclitem == NULL)return NULL;

	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		if(clItem[i].IsSame( (cltItem*)pclitem, numcomp )== TRUE)
		{
			return &clItem[i];
		}
	}

	return NULL;
}

// Ư�� �������� ���� �ľ��ؼ� �����Ѵ�.
SI32 cltMarketAccount::GetItemNum(cltItem* pclitem)
{
	cltItem* pclsrcitem = FindItem(pclitem, false);
	if(pclsrcitem == NULL)return 0;

	return pclsrcitem->GetItemNum();
}

BOOL cltMarketAccount::IsSame(cltMarketAccount* pclaccount)
{
	SI32 i;

	if(pclaccount == NULL)return FALSE;

	for(i = 0;i < MAX_MARKET_ORDER_PER_PERSON;i++)
	{
		// �Ѱ��� �������̶� ���� Ʋ���ٸ� Ʋ�� ���̴�. 
		if(clItem[i].IsSame(&pclaccount->clItem[i], true) == false)
		{
			return FALSE;
		}
	}

	return TRUE;
}

// ���� �ֹ� ������ ������Ʈ �Ѵ�. 
bool cltMarketAccount::UpdateMarketOrder(SI32 index, cltTradeOrder* pclorder)
{
	if(pclorder == NULL)return false;

	// ������ 0 �̸� �ֹ��� �����ϴ� ������ �ν��Ѵ�. 
	if(pclorder->siPrice == 0)
	{
		clItem[index].Init();
	}
	else
	{
		clItem[index].Set(&pclorder->clItemData);
	}

	
	clMoney[index].Set(pclorder->siPrice);
	
	
	return true;

}


BOOL cltNewMarketAccount::IsSame(cltNewMarketAccount* pclaccount)
{
	SI32 i;

	if(pclaccount == NULL)return FALSE;

	for(i = 0;i < MAX_NEWMARKET_ORDER_PER_PERSON;i++)
	{
		// �Ѱ��� �������̶� ���� Ʋ���ٸ� Ʋ�� ���̴�. 
		if(clItem[i].IsSame(&pclaccount->clItem[i], true) == false)
		{
			return FALSE;
		}
	}

	return TRUE;
}

SI32 cltNewMarketAccount::GetItemNum(cltItem* pclitem)
{
	cltItem* pclsrcitem = FindItem(pclitem, false);
	if(pclsrcitem == NULL)return 0;

	return pclsrcitem->GetItemNum();
}

cltItem* cltNewMarketAccount::FindItem(const cltItem* pclitem, bool numcomp)
{
	SI32 i;

	if(pclitem == NULL)return NULL;

	for(i = 0;i < MAX_NEWMARKET_ORDER_PER_PERSON;i++)
	{
		if(clItem[i].IsSame((cltItem*)pclitem, numcomp)== TRUE)
		{
			return &clItem[i];
		}
	}

	return NULL;
}

