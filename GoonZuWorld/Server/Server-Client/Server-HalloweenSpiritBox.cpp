#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../common/Order/order.h"
#include "../../common/JWLib/IsCorrectID/IsCorrectID.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "../../CommonLogic/MsgType-HalloweenSpiritBox.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_HALLOWEENSPIRITBOX_OK(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_HalloweenSpiritBox* pclInfo = (cltGameRequest_HalloweenSpiritBox*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
		return;

	// �ٸ� ���Ǹ� �ڽ� �����۵� ��� �ؾ� �ϴϱ� ����ó�� ����
	//if(pclInfo->m_siDelItemUinque != ITEMUNIQUE(13356))	// �ҷ������Ǹ��ڽ� �� �ƴϸ� ����
	//	return;

	//if(!(pclInfo->m_siAddItemUinque == ITEMUNIQUE(13626) || pclInfo->m_siAddItemUinque == ITEMUNIQUE(13627)))	// �ҷ��� ���Ǹ� �ٰŸ�, ���Ÿ��� �ƴϸ� ����
	//	return;

	// ������ ������ ����ũ ���� �˻� 
	if(pclInfo->m_siDelItemUinque <= 0 )	return	;
	if(pclInfo->m_siAddItemUinque <= 0 )	return	;

	// ������ Ÿ�� �˻� 

	SI32 siItemType_Box = pclItemManager->GetItemType( pclInfo->m_siDelItemUinque )		;		// �ش� ������ Ÿ���� ������ �´�
	SI32 siItemType_Sprit = pclItemManager->GetItemType( pclInfo->m_siAddItemUinque )	;	

	if ( siItemType_Box != ITEMTYPE_BOX || siItemType_Sprit != ITEMTYPE_PREMIUM )	return	;	// �ش� ������ Ÿ���� �ڽ��� �ƴϰų� �����̾��� �ƴϸ� ���� 

	// DB�� '���� ����' ��û

	SI32 siItemPosition = pclChar->pclCI->clCharItem.GetItemPos( pclInfo->m_siDelItemUinque );	// �ٲ� ������ ��ġ
	if(siItemPosition == -1)
		return;

	cltItem clDelItem;
	clDelItem.Set(&pclChar->pclCI->clCharItem.clItem[siItemPosition]);
	clDelItem.siItemNum = 1;


	cltItem clAddItem;
	SI16	brareswitch		= 0;
	UI08	uiDateUseDay	= 0;
	pclItemManager->MakeRandItemUnique(pclInfo->m_siAddItemUinque, &clAddItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, uiDateUseDay);


	SI16	invpos	= 0;
	SI32	rtnvalue= 0;

	cltItem cltoitem;
	if(pclChar->CanAddInv(INVMODE_ALL, &clAddItem, &invpos, &cltoitem, &rtnvalue) == false)
	{
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_TREASUREBOX_FAILEDOPEN_FULLINVEN, 0, 0, pclChar->GetID());
		return;
	}

	sDBRequest_OpenTreasureBox clMsg(	pclChar->pclCI->GetPersonID(), 
		siItemPosition, 
		&clDelItem, 
		0, 
		NULL, 
		invpos, 
		&clAddItem, 
		pclItemManager->CanPile(clAddItem.siUnique), 
		clAddItem.IsCreateSID(pclItemManager),
		false);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}
