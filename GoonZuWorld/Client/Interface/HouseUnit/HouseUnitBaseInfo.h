#ifndef _HOUSEUNITBASEINFO_H_
#define _HOUSEUNITBASEINFO_H_

#include < Directives.h >

#include "..\..\..\Resource.h"

#include "..\..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "../../../common/CommonHeader.h"

#define		HOUSEUNIT_SETTIMER_DEALY_TIME			1000

#define		TABCTRL_TAB_NUM							4

/*
//------------------------------------------ NPC �ŷ����� ���Ǵ� �޽��� ����ü
struct stNPCTradeData
{
	SI16		si16Msg;
	SI32		si32lParam;
	cltItem		clItem;
};

//------------------------------------------ NPC �ŷ����� ���Ǵ� �޽���
#define	NPCTRADE_SELLITEM_TO_NPC		25000		// NPC ���� �������� �Ǹ�
#define NPCTRADE_BUYITEM_FROM_NPC		25001		// NPC�κ��� �������� ����


*/

//------------------------------------------ â�� �ŷ����� ���Ǵ� �޽��� ����ü
struct stHouseUnitData
{	
	SI16			si16Msg;
	SI32			si32lParam1;
	SI32			si32lParam2;
	SI32			si32VillageUnique;					//â�� �ִ� ������ ��ġ(��� �����̳�)
	SI32			si32HouseUnitSlot;					//������ ��ġ(��� ���̳�)
	cltItem			clItem;
	cltRentContract	clContract;
};

#define	HOUSEUNIT_INPUT_USERINVENTORY_TO_WAREHOUSE		26000
#define	HOUSEUNIT_OUTPUT_USERINVENTORY_FROM_WAREHOUSE	26001

// lParam = ������ ������ �������� index, clItem �� �ǹ� ����.
#define	HOUSEUNIT_WAREHOUSE_MAKEITEM					26100

// �Ķ���� ����
#define HOUSEUNIT_RETAL_EXTENSION						26002


#endif