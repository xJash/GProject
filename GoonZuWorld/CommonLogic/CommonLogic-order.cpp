#include "Char\CharManager\CharManager.h"
#include "..\Client\Client.h"
#include "..\Common\Order\Order.h"

//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

// ĳ���Ϳ��� ���������� ����� �����Ѵ�.
BOOL cltCommonLogic::LetOrder(cltOrderData *porder, SI32 id)
{
	if(porder == NULL)return FALSE;

	if(id == 0)
	{
		id = pclCM->GetIDFromCharUnique(porder->CharUnique);
	}

	// ��Ȱ ����� �ƴϸ� ���� ĳ���Ϳ��� �� �� ����.
	if(porder->ODI.siOrder != ORDER_REVIVE)
	{
		if(pclCM->IsAlive(id)==FALSE)return FALSE;
	}

	cltOrderDataInfo odi(&porder->ODI);

	//--------------------------------------------
	// CharUnique ������ Id ������ ��ȯ�Ѵ�. 
	//--------------------------------------------
    odi.siPara2		=	pclCM->GetIDFromCharUnique(porder->ODI.siPara2) ;

	pclCM->CR[id]->PushOrder(odi);
	
	return TRUE;
}



