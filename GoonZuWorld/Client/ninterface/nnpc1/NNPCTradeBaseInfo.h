#ifdef __SUN_NNPCTRADE1__


#ifndef _NPCTRADEBASEINFO_H_
#define _NPCTRADEBASEINFO_H_

#include < Directives.h >

#include "..\..\..\Resource.h"

#include "..\..\..\Common\Item\ItemCommon\ItemUnit.h"
#include "..\..\..\Common\Item\ItemCommon\NPCItem.h"
#include "..\..\..\CommonLogic\ImageList\ImageList.h"
#include "..\..\..\Common\SystemNPC\SystemNPC.h"
#include <CommonLogic.h>


#define		NPCTRADEINVENTORY_SETTIMER_DEALY_TIME			1000

//------------------------------------------ NPC �ŷ����� ���Ǵ� �޽��� ����ü
struct stNPCTradeData
{
	SI16		si16Msg;
	SI32		si32lParam;
	SI32		siNPCCharUnique;
	cltItem		clItem;
};

//------------------------------------------ NPC �ŷ����� ���Ǵ� �޽���
#define	NPCTRADE_SELLITEM_TO_NPC		25000		// NPC ���� �������� �Ǹ�
#define NPCTRADE_BUYITEM_FROM_NPC		25001		// NPC�κ��� �������� ����

#endif

#endif