//---------------------------------
// 2003/6/3 ���°�
//---------------------------------
#include "Stock.h"
#include "..\..\CommonLogic\CommonLogic.h"

#include "..\..\Resource.h"

extern cltCommonLogic* pclClient;

//----------------------------------------------------
// cltStockAccount: �ֽ� ���� ����. 
//----------------------------------------------------

// Ư�� ������ �ֽļ��� �����Ѵ�. 
void cltStockAccount::Set(SI32 villageunique, SI32 amount)
{
	SI32 i;

	if(villageunique <= 0 && amount <= 0)return;

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		// ���ϴ� ������ ã����, 
		if(villageunique == clUnit[i].siVillageUnique)
		{
			clUnit[i].siAmount	= amount;
			if(amount == 0)
			{
				clUnit[i].siVillageUnique = 0;
			}
			return ;
		}
	}

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		// �� ĭ�� ã����, 
		if(clUnit[i].siVillageUnique == 0)
		{
			clUnit[i].Init(villageunique, amount);
			return ;
		}
	}
}

// Ư�� ������ �ֽ� ���� �ľ��ؼ� �����Ѵ�.
SI32 cltStockAccount::GetStockAmount(SI32 villageunique)
{
	SI32 i;

	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		// ���ϴ� ������ ã����, 
		if(villageunique == clUnit[i].siVillageUnique)
		{
			return clUnit[i].siAmount;
		}
	}

	return 0;

}

// �ֽ��� �߰��Ѵ�. 
BOOL cltStockAccount::Add(SI32 villageunique, SI32 tradeamount)
{
	SI32 i;

	// �̹� ���� ������ �ִ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		if(clUnit[i].siVillageUnique == villageunique)
		{
			clUnit[i].siAmount += tradeamount;
			return TRUE;
		}
	}

	// ���ο� �������� �߰��Ѵ�. 
	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		if(clUnit[i].siVillageUnique == 0)
		{
			clUnit[i].Init(villageunique, tradeamount);
			return TRUE;
		}
	}

	return FALSE;
}

// �ֽ��� ����.
BOOL cltStockAccount::Sub(SI32 villageunique, SI32 tradeamount)
{
	SI32 i;

	// �̹� ���� ������ �ִ��� Ȯ���Ѵ�. 
	for(i = 0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		if(clUnit[i].siVillageUnique == villageunique)
		{
			//���� �����ֺ��� �� ���� �ָ� ���� ����. 
			if(tradeamount > clUnit[i].siAmount )return FALSE;

			clUnit[i].siAmount -= tradeamount;
			return TRUE;
		}
	}

	return FALSE;
}

