//---------------------------------
// 2003/6/24 ���°�
//---------------------------------
#include <CommonLogic.h>

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"


#include "..\..\Resource.h"

#include "Market.h"
#include <JYLibFunction.h>

static bool bSelectedSwitch = false;

extern cltCommonLogic* pclClient;


// �������� ���� �ֹ� ������ �����Ѵ�. 
// Ŭ���̾�Ʈ���� ���� ��û�ߴ� ������ ���� ���̴�. 
BOOL cltMarketManager::PutResponseOrder(cltTradeOrder* pclorder)
{

	if(siResponseOrderIndex >= MAX_RESPONSE_ORDER_NUMBER)return FALSE;

	clResponseOrder[siResponseOrderIndex].Set(pclorder);

	siResponseOrderIndex++;

	// ȭ���� ������ �����ϵ��� �Ѵ�. 
	ShowResponseOrderSiwtch = TRUE;
	return TRUE;



}
