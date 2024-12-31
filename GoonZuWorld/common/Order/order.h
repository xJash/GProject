#ifndef _ORDER_H
#define _ORDER_H      1

#define MAX_ORDER_BUFFER_NUMBER			3      // �����Ӵ� �Է� ������ �ִ� ��� ���� 


#define ORDERATB_NORMAL					1
#define ORDERATB_MAGIC					16
#define ORDERATB_ONLY					256
#define ORDERATB_GOODS					512


//-------------------------------------
// ����� ����. 
//-------------------------------------
class cltOrderInfo {
public:
	SHORT Atb;
	SHORT Object;
	int Para1, Para2;

	int Info;

	// ����� ���� ������ �����Ѵ�. 
    void SetOrder(SHORT atb, SHORT object, int info, int para1, int para2);
	// ����� �Ӽ��� ���Ѵ�. 
    BOOL IsAtb(SHORT atb);
	int GetPara1();
	int GetPara2();


};



class cltOrder{
private:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltOrderData, MAX_ORDER_BUFFER_NUMBER>		OrderBuffer;
#else
	cltOrderData OrderBuffer[MAX_ORDER_BUFFER_NUMBER];
#endif
	SI32 OrderBufferIndex;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltOrderData, MAX_ORDER_QUE>				OrderQue;
#else
	cltOrderData OrderQue[MAX_ORDER_QUE];
#endif

public:
	cltOrder();

public:
private:
	BOOL PopOrderBuffer(cltOrderData* porder);
	void PushOrderBuffer(cltOrderData order);

public:
	BOOL Action(cltOrderData* porder);
	// ����� orderbuffer�� �־� ���´�. 
	BOOL MakeOrder(SI32 order, SI32 x, SI32 y, SI16 para2, SI16 para3, SI16 para4);

private:
	BOOL PushOrder(cltOrderData order);
	BOOL PopOrder(cltOrderData* porder);

};

//----------------------------------------
// ��� ������.
//---------------------------------------
class cltOrderManager{
public:
	///-----------------------------------
	// ����� ��� �ӽ� ���� ����. 
	//------------------------------------
	cltOrder clOrder;

	//------------------------------------
	// ���� ���� ������ ���� ������ 
	//------------------------------------
#ifdef _SAFE_MEMORY
	NSafeTArray<cltOrderInfo, MAX_ORDER_NUMBER>				Order;
#else
	cltOrderInfo   Order[MAX_ORDER_NUMBER];
#endif

	cltOrderManager();
	~cltOrderManager();

	void OrderInit();
	
	// �̵� ����� �����.
	bool MakeOrder_MOVE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode);
	// ���� �̵� ����� �����.
	bool MakeOrder_STRAIGHTMOVE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode);
	
	// ���� ����� �����.
	bool MakeOrder_ATTACK(cltOrderDataInfo* pclorder, SI32 id, SI08 hostmode, SI16 para4 = 0);
	bool MakeOrder_ATTACK_CLIENT(cltOrderDataInfo* pclorder, SI32 id, SI08 hostmode);
	// ���� ����� �����.
	bool MakeOrder_MAGIC(cltOrderDataInfo* pclorder, SI32 id, SI16 magickind, SI08 hostmode, SI16 para4 = 0);
	// ���� ����� �����.
	bool MakeOrder_FISH(cltOrderDataInfo* pclorder, SI32 dir, SI08 hostmode);
	// ��� ����� �����.
	bool MakeOrder_FARM(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode);
	// ä�� ����� �����.
	bool MakeOrder_MINE(cltOrderDataInfo* pclorder, SI32 x, SI32 y, SI08 hostmode);
	// �ɱ� ����� �����.
	bool MakeOrder_SITDOWN(cltOrderDataInfo* pclorder, SI32 Dir, SI08 hostmode);
	// ���� ��ȯ�� �ൿ ����� �����.
	bool MakeOrder_SPECIAL_ACTION(cltOrderDataInfo* pclorder, SI16 siAnytype, SI08 hostmode);

	
	
	// ���� ���� ����� �����.
	bool MakeOrder_FORCESTOP(cltOrderDataInfo* pclorder, SI08 hostmode);



	bool OrderMagic(SI32 id, SI16 targetid, SI16 magickind, SI08 host);
	


};

BOOL DoOrder(SHORT order, SI32 id, int para1, SI16 para2, SI16 para3, SI16 para4, SI08 host);

void OrderStop(SI32 id, SI08 host);
void OrderForceStop(SI32 id, SI08 host);
void OrderMove(SI32 id, int x, int y, int hostmode);
void OrderStraightMove(SI32 id, int x, int y, int hostmode);
void OrderFarm(SI32 id, int x, int y, int hostmode);
BOOL OrderAttack(SI32 id, SI32 attackid, SI08 host);
BOOL OrderAttackClient(SI32 id, SI32 attackid, SI08 host);
BOOL OrderFish(SI32 id, SI32 dir, SI08 host);
void OrderMine(SI32 id, int x, int y, int hostmode);
void OrderSitDown( SI32 id, SI32 Dir, SI08 hostmode );
BOOL OrderRevive(SI32 id);
void OrderDie(SI32 id, SI08 host);
void OrderSpecialAction(SI32 id, SI16 anitype, SI08 host);
#endif
