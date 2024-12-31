#include "..\..\Client\Client.h"


#include "Order.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;

// ����� ���� ������ �����Ѵ�. 
void cltOrderInfo::SetOrder(SHORT atb, SHORT object, int info, int para1, int para2)
{
	Atb=atb;
	Object=object;
	Info=info;
	Para1=para1;
	Para2=para2;
}

// ����� �Ӽ��� ���Ѵ�. 
BOOL cltOrderInfo::IsAtb(SHORT atb)
{
	if(Atb&atb)return TRUE;
	return FALSE;
}

int cltOrderInfo::GetPara1()
{
	return Para1;
}

int cltOrderInfo::GetPara2()
{
	return Para2;
}

//-----------------------------------------------------------------------------
cltOrder::cltOrder()
{
	SI32 i;

	OrderBufferIndex = 0;

	for(i = 0;i < MAX_ORDER_QUE;i++)
	{
		ZeroMemory(&OrderQue[i], sizeof(cltOrderData));
	}
}

BOOL cltOrder::PushOrder(cltOrderData order)
{
	int i;
	int index=-1;

	index=-1;
	
	for(i=0;i<MAX_ORDER_QUE;i++)
	{
		if(OrderQue[i].ODI.siOrder==0)
		{
			index=i;
			break;
		}
	}
	if(index < 0)return FALSE;
	
	OrderQue[index].ODI.Set(&order.ODI);
	OrderQue[index].ODI.siHostMode	=	BY_PLAYER;
	
	OrderQue[index].CharUnique	    =	order.CharUnique;

	return TRUE;
}


BOOL cltOrder::PopOrder(cltOrderData* porder)
{
	int j;
	
	for(j = 0;j < MAX_ORDER_QUE;j++)
	{
		
		if(OrderQue[j].ODI.siOrder)
		{
			memcpy(porder, &OrderQue[j], sizeof(cltOrderData));

			OrderQue[j].ODI.Init();
			OrderQue[j].ODI.siOrder = 0;

			return TRUE;
		}
	}
	
    return FALSE;
}

void cltOrder::PushOrderBuffer(cltOrderData order)
{
	if(OrderBufferIndex >= MAX_ORDER_BUFFER_NUMBER)return ;

	OrderBuffer[OrderBufferIndex] = order;
	OrderBufferIndex++;

}

BOOL cltOrder::PopOrderBuffer(cltOrderData* porder)
{
	int i;

	// ����ڷκ��� ���� ����� ���ٸ�, 
	if(OrderBufferIndex<=0)return FALSE;

	// ����� ����� �����Ѵ�. 
#ifdef _SAFE_MEMORY
	memcpy(porder, &OrderBuffer[0], sizeof(cltOrderData));
#else
	memcpy(porder, OrderBuffer, sizeof(cltOrderData));
#endif
	for(i=1;i<OrderBufferIndex;i++)
	{
		OrderBuffer[i-1]=OrderBuffer[i];
	}

	OrderBufferIndex--;

	return TRUE;

}


// ����� orderbuffer�� �־� ���´�. 
BOOL cltOrder::MakeOrder(SI32 order, SI32 x, SI32 y, SI16 para2, SI16 para3, SI16 para4)
{
	int index = 0;
	SI32 id = 1;

	cltOrderData temporder;

	ZeroMemory(&temporder, sizeof(cltOrderData));

	//-----------------------------------------
	// Order
	//-----------------------------------------
	temporder.ODI.siOrder         = order;

	//-----------------------------------------
	// Para1 
	//-----------------------------------------
	temporder.ODI.siPara1         = x | (y <<16);

	//-----------------------------------------
	// Para2 
	//-----------------------------------------
	if(pclClient->pclCM->IsAlive(para2))
	{
		temporder.ODI.siPara2         = pclClient->pclCM->CR[para2]->GetCharUnique();
	}
	else
	{ 
		temporder.ODI.siPara2         = 0;
	}
	
	//-----------------------------------------
	// Para3
	//-----------------------------------------
	temporder.ODI.siPara3				= para3;

	//-----------------------------------------
	// Para4
	//-----------------------------------------
	temporder.ODI.siPara4				= para4;
	
	temporder.ODI.siHostMode      = BY_PLAYER;

	index = 0;

	if(pclClient->pclCM->IsAlive(id) == TRUE)
	{
		temporder.CharUnique	= pclClient->pclCM->CR[id]->GetCharUnique();
		index++;
	}

	PushOrderBuffer(temporder);

	return TRUE;
}


BOOL cltOrder::Action(cltOrderData* porder)
{
	cltOrderData order;

	// ����ڷκ��� �Էµ� ����� �ִٸ�,
	if(PopOrderBuffer(&order) == TRUE)
	{
		// ó���� ���ֵ��� OrderQue�� �ִ´�. 
		PushOrder(order);
	}

	// OrderQue�� ����� ����� ó���Ѵ�. 
	if(PopOrder(&order) == TRUE)
	{

		memcpy(porder, &order, sizeof(cltOrderData));
		return TRUE;
	}

	return FALSE;
}

//-------------------------------------------
// cltOrderManager
//-------------------------------------------
cltOrderManager::cltOrderManager()
{
	// �� ��ɿ� ���� Ư��ġ���� �����Ѵ�.
	OrderInit();

}

cltOrderManager::~cltOrderManager()
{
}


void cltOrderManager::OrderInit()
{
	Order[ORDER_WAIT]				.SetOrder(ORDERATB_NORMAL, NOOBJECT,  0, 0, 0);
	Order[ORDER_STOP]				.SetOrder(ORDERATB_NORMAL, NOOBJECT,  0, 0, 0);
	Order[ORDER_FORCESTOP]			.SetOrder(ORDERATB_NORMAL, NOOBJECT,  0, 0, 0);
	Order[ORDER_MOVE]				.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_ATTACK]				.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_ATTACK_SUMMON]		.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_DIE]				.SetOrder(ORDERATB_NORMAL, NOOBJECT , 0, 0, 0);
	Order[ORDER_DEAD]				.SetOrder(ORDERATB_NORMAL, NOOBJECT , 0, 0, 0);
	Order[ORDER_STRAIGHTMOVE]		.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_FISH]				.SetOrder(ORDERATB_NORMAL, NOOBJECT , 0, 0, 0);
	Order[ORDER_FARM]				.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_MINE]				.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	Order[ORDER_MOVE_SUMMON]		.SetOrder(ORDERATB_NORMAL, OBJECT1 ,  0, 0, 0);
	//Order[ORDER_MAGIC_SUMMON]		.SetOrder(ORDERATB_NORMAL, OBJECT1,	  0, 0, 0);
	Order[ORDER_SITDOWN]			.SetOrder(ORDERATB_NORMAL, NOOBJECT,  0, 0, 0);
	Order[ORDER_ATTACK_CLIENT]		.SetOrder(ORDERATB_NORMAL, OBJECT1,   0, 0, 0);
	Order[ORDER_SPECIAL_ACTION]		.SetOrder(ORDERATB_NORMAL, NOOBJECT,  0, 0, 0);

}

// ���� ����� �����.
bool cltOrderManager::MakeOrder_FORCESTOP(cltOrderDataInfo* pclorder, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_FORCESTOP,  hostmode, 0, 0, 0, 0);
	return true;
}

// �̵� ����� �����.
bool cltOrderManager::MakeOrder_MOVE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_MOVE,  hostmode, (x|(y<<16)), 0, 0, 0);
	return true;
}

// ��� ����� �����. 
bool cltOrderManager::MakeOrder_FARM(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_FARM,  hostmode, (x|(y<<16)), 0, 0, 0);
	return true;
}

// ä�� ����� �����. 
bool cltOrderManager::MakeOrder_MINE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_MINE,  hostmode, (x|(y<<16)), 0, 0, 0);
	return true;
}

// �ɱ� ����� �����. 
bool cltOrderManager::MakeOrder_SITDOWN(cltOrderDataInfo* pclorder, SI32 Dir, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_SITDOWN,  hostmode, Dir, 0, 0, 0);
	return true;
}

// ���� ��ȯ�� �ൿ ����� �����.
bool cltOrderManager::MakeOrder_SPECIAL_ACTION(cltOrderDataInfo* pclorder, SI16 siAnytype, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_SPECIAL_ACTION,  hostmode, siAnytype, 0, 0, 0);
	return true;
}



// ���� �̵� ����� �����.
bool cltOrderManager::MakeOrder_STRAIGHTMOVE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_STRAIGHTMOVE,  hostmode, (x|(y<<16)), 0, 0, 0);
	return true;
}


// ���� ����� �����.
bool cltOrderManager::MakeOrder_ATTACK(cltOrderDataInfo* pclorder, SI32 id, SI08 hostmode, SI16 para4)
{
	if(pclorder == NULL)return false;
	if(pclClient->pclCM->IsAlive(id) == false)return false;

	pclorder->Make(ORDER_ATTACK, hostmode, 0, pclClient->pclCM->CR[id]->GetCharUnique(), 0, para4);
	return true;
}

// ���� ����� �����.
bool cltOrderManager::MakeOrder_ATTACK_CLIENT(cltOrderDataInfo* pclorder, SI32 id, SI08 hostmode)
{
	if(pclorder == NULL)return false;
	if(pclClient->pclCM->IsAlive(id) == false)return false;

	pclorder->Make(ORDER_ATTACK_CLIENT, hostmode, 0, pclClient->pclCM->CR[id]->GetCharUnique(), 0, 0);
	return true;

}

// ���� ����� �����.
bool cltOrderManager::MakeOrder_MAGIC(cltOrderDataInfo* pclorder, SI32 id, SI16 magickind, SI08 hostmode, SI16 para4)
{
	if(pclorder == NULL)return false;
	if(pclClient->pclCM->IsAlive(id) == false)return false;

	pclorder->Make(ORDER_MAGIC, hostmode, 0, pclClient->pclCM->CR[id]->GetCharUnique(), magickind, para4);
	return true;

}

// ���� ����� �����.
bool cltOrderManager::MakeOrder_FISH(cltOrderDataInfo* pclorder, SI32 dir, SI08 hostmode)
{
	if(pclorder == NULL)return false;

	pclorder->Make(ORDER_FISH, hostmode, dir, 0, 0, 0);
	return true;

}


bool cltOrderManager::OrderMagic(SI32 id, SI16 targetid, SI16 magickind, SI08 host)
{
	// ��� �־�߸� �Ѵ�. 
	if(pclClient->pclCM->IsAlive(id)==FALSE)return false;

	cltOrderDataInfo odi;
	MakeOrder_MAGIC(&odi, targetid, magickind, host);

	pclClient->pclCM->CR[id]->PushOrder(odi);
	return true;
}



// ��ǻ�Ͱ� �ڽſ��� ����� �����Ѵ�. 
BOOL DoOrder(SHORT order, SI32 id, int para1, SI16 para2, SI16 para3, SI16 para4, SI08 host)
{
	if(pclClient->pclCM->IsAlive(id)==FALSE)return FALSE;
	
	cltOrderDataInfo odi;

	odi.Make(order, host, para1, para2, para3, para4);
	
	pclClient->pclCM->CR[id]->PushOrder(odi);
	return TRUE;

}

void OrderStop(SI32 id, SI08 hostmode)
{
	DoOrder(ORDER_STOP, id, 0, 0, 0, 0, hostmode);
}


void OrderForceStop(SI32 id, SI08 hostmode)
{
	DoOrder(ORDER_FORCESTOP, id, 0, 0, 0, 0, hostmode);
}



// ĳ���͸� �̵���Ų��. 
// servermode:  ������ �����ؼ� Ŭ���̾�Ʈ�鿡�Ե� ���� �ϴ� ����ΰ� ?
void OrderMove(SI32 id, int x, int y, int hostmode)
{
	DoOrder(ORDER_MOVE, id, (x|(y<<16)), 0, 0, 0,hostmode);
}

// ĳ���͸� ���� �̵���Ų��. 
// servermode:  ������ �����ؼ� Ŭ���̾�Ʈ�鿡�Ե� ���� �ϴ� ����ΰ� ?
void OrderStraightMove(SI32 id, int x, int y, int hostmode)
{
	DoOrder(ORDER_STRAIGHTMOVE, id, (x|(y<<16)), 0, 0, 0, hostmode);
}

void OrderFarm(SI32 id, int x, int y, int hostmode)
{
	DoOrder(ORDER_FARM, id, (x|(y<<16)), 0, 0, 0,hostmode);
}

void OrderMine(SI32 id, int x, int y, int hostmode)
{
	DoOrder(ORDER_MINE, id, (x|(y<<16)), 0, 0, 0,hostmode);
}

void OrderSitDown( SI32 id, SI32 Dir, SI08 hostmode )
{
	DoOrder(ORDER_SITDOWN, id, Dir, 0, 0, 0, hostmode);
}


BOOL OrderAttack(SI32 id, SI32 attackid, SI08 host)
{

	DoOrder(ORDER_ATTACK, id, 0, attackid, 0, 0, host);
	return TRUE;
}

BOOL OrderAttackClient(SI32 id, SI32 attackid, SI08 host)
{

	DoOrder(ORDER_ATTACK_CLIENT, id, 0, attackid, 0, 0, host);
	return TRUE;
}

BOOL OrderFish(SI32 id, SI32 dir, SI08 host)
{

	DoOrder(ORDER_FISH, id, dir, 0, 0, 0, host);
	return TRUE;
}


BOOL OrderRevive(SI32 id)
{
	DoOrder(ORDER_REVIVE, id, 0, 0, 0, 0, BY_PLAYER);
	return TRUE;

}

void OrderDie(SI32 id, SI08 host)
{
	DoOrder(ORDER_DIE, id, 0, 0, 0, 0, host);
}


void OrderSpecialAction(SI32 id, SI16 anitype, SI08 host)
{
	DoOrder(ORDER_SPECIAL_ACTION, id, anitype, 0, 0, 0, host);
}



