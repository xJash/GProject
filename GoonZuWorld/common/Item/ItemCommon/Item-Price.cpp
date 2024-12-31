//---------------------------------
// 2003/6/24 ���°�
//---------------------------------

#include <stdio.h>
#include "cltItem.h"
#include "NPCItem.h"

#include "../../../CommonLogic/CommonLogic.h"
#include "../../../Server/Server.h"

extern cltCommonLogic* pclClient;

cltItemPrice::cltItemPrice(cltItemManagerCommon* pclitemmanager)
{
	pclItemManager = pclitemmanager;

	SI32 i;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(pclItemManager->pclItemInfo[i])
		{
			clUnit[i].siUnique	= pclItemManager->pclItemInfo[i]->clItem.siUnique;
		}
	}

}

cltItemPrice::~cltItemPrice()
{
}

// �������� ������ �����Ѵ�.
void cltItemPrice::SetPrice(cltItemManagerCommon* pclitemmanager, SI32 unique, GMONEY price, SI32 itemnum, bool bforceswitch)
{
	SI32 index = pclitemmanager->FindItemRefFromUnique(unique);
	if(index <= 0)
	{
		return ;
	}

	if(bforceswitch == true)
	{
		clUnit[index].siItemNum = itemnum;
		clUnit[index].siPrice	= price;
		clUnit[index].fPrice	= (float)price;
		return ;
	}

	// ������Ʈ�� ��ǰ�� ��� �����ش�.
	if(pclitemmanager->GetItemAtb(unique) & ITEMATB_OBJECT)
	{
		return ;
	}

	// MIN_ITEM_PRICE�� ���Ϸδ� �������� �ʴ´�. 
	price = max(MIN_ITEM_PRICE, price);


	// ������ �ʹ� ���� �͵� �����Ѵ�. 
	if(itemnum > 500)itemnum = 500;


	if(clUnit[index].siPrice)
	{
		//---------------------------------------------------
		// ������ �ü����� 5%���� ��δٸ� 5%������ �ݿ��Ѵ�. 
		//---------------------------------------------------
		GMONEY maxprice = max(1, (clUnit[index].siPrice * 105 / 100));
		if(maxprice == clUnit[index].siPrice)
		{
			maxprice++;
		}

		//---------------------------------------------------
		// ������ �ü����� 70%���϶�� 70%������ �ݿ��Ѵ�.
		//---------------------------------------------------
		GMONEY minprice = max(1, (clUnit[index].siPrice * 70 / 100));
		if(minprice == clUnit[index].siPrice )
		{
			minprice = max(1, minprice-1);
		}
	
		// ��ΰ� �����Ǵ� ���� ���������� �����Ѵ�.
		if(price > maxprice)
		{
			price = maxprice;

			// ������ �ʹ� ���� �͵� �����Ѵ�. 
			if(itemnum > 10)itemnum = 10;
		}
		// �ΰ� �����Ǵ� ���� ���������� �ݿ��Ѵ�. 
		else if(price < minprice)
		{
			price = minprice;
			
			// ������ �ʹ� ���� �͵� �����Ѵ�. 
			if(itemnum > 3000)itemnum = 3000;
		}
	}

	clUnit[index].siUnique	= unique;

	if(clUnit[index].siItemNum == 0)
	{
		// ���� ������ 100�ɿ��� �����Ѵ�. 
		if(price > 100)price = 100;

		SI64 oldPrice = clUnit[index].siPrice;

		clUnit[index].siItemNum = min(10, itemnum);
		clUnit[index].siPrice	= price;
		clUnit[index].fPrice	= (float)price;
	}
	else
	{
		SI32 orgitemnum = min(10000, clUnit[index].siItemNum);

		SI64 oldPrice = (SI64)clUnit[index].fPrice;

		clUnit[index].fPrice	= (float)( (orgitemnum * clUnit[index].fPrice) + (price * itemnum) ) / (orgitemnum + itemnum);
		clUnit[index].siPrice	= (SI64)clUnit[index].fPrice;
		clUnit[index].siItemNum = min(10000, clUnit[index].siItemNum + itemnum);
	}
}

// �������� ������ ���Ѵ�. 
cltItemPriceUnit* cltItemPrice::GetPrice(cltItemManagerCommon* pclitemmanager,SI32 unique)
{
	SI32 index = pclitemmanager->FindItemRefFromUnique(unique);
	if(index <= 0)return NULL;

	return &clUnit[index];
}

// ���� �ֹ������� �����Ѵ�. 
void cltItemPrice::SetMarketOrderPrice(cltItemManagerCommon* pclitemmanager,SI32 unique, GMONEY price)
{
	SI32 index = pclitemmanager->FindItemRefFromUnique(unique);
	if(index <= 0)return ;

	clUnit[index].siUnique				= unique;
	clUnit[index].siMarketOrderPrice	= price;
}



// ���� �ֹ������� ���´�. 
GMONEY cltItemPrice::GetMarketOrderPrice(SI32 unique)
{
	SI32 i;

	for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
	{
		if(clUnit[i].siUnique == unique)
		{
			return clUnit[i].siMarketOrderPrice;
		}
	}

	return 0;
}

// Ư�� ��ǰ�� �ü��� �˷��ش�.(NPC��)
GMONEY cltItemPrice::GetPriceSellToNPC(cltItemManagerCommon* pclitemmanager, SI32 unique)
{
	//-------------------------
	// �������� Ÿ���� ���Ѵ�. 
	//-------------------------
	cltItemInfo* pcliteminfo = pclitemmanager->FindItemInfo(unique);
	if(pcliteminfo == NULL)return 0;
	
	GMONEY price = 0;

	//---------------------------------------------------------------------------
	// 1. �������� Ÿ�Կ� ���� ������ ���Ѵ�.
	//---------------------------------------------------------------------------
	switch(pcliteminfo->siType)
	{

	case ITEMTYPE_SWORD:
	case ITEMTYPE_SPEAR:
	case ITEMTYPE_STAFF:
	case ITEMTYPE_AXE:
	case ITEMTYPE_BOW:
	case ITEMTYPE_GUN:
	case ITEMTYPE_CANNON:
	case ITEMTYPE_TORPEDO:
	case ITEMTYPE_ARMOUR:
	case ITEMTYPE_DRESS:
	case ITEMTYPE_HELMET:
	case ITEMTYPE_HAT:		
	case ITEMTYPE_BAG:
	case ITEMTYPE_MANTLE:
		price	= 200;	break;

	case ITEMTYPE_NECK:
	case ITEMTYPE_RING:
	case ITEMTYPE_BELT:
	case ITEMTYPE_SHOES:
		price	= 100;	break;

	case ITEMTYPE_BOOK:		price	= 200;				break;
		
	case ITEMTYPE_HEAL:
		// �����̸�, (���꿡 �ʿ��� ��ǰ�� ���� ���̶��) 
		if(pcliteminfo->clProductionInfo.clMaterial[0].siUnique == 0)
		{
			price	= 40;
		}
		else
		{
			price	= MIN_ITEM_PRICE;
		}
		break;

	default:				price	= MIN_ITEM_PRICE;	break;		
	}
	//---------------------------------------------------------------------------


	//---------------------------------------------------------------------------
	// 2. �������� ����ũ�� ���� ������ ���Ѵ�.
	//---------------------------------------------------------------------------
	if ( ITEMUNIQUE(24105) == unique )
	{	
		// �븸�� �ݾ��� �ٸ�
		if ( pclClient->IsWhereServiceArea(ConstServiceArea_Taiwan) )
		{
			price = 88888;
		}
		else
		{
			price = 1000000;
		}
	}
	//---------------------------------------------------------------------------

	return price;
}



