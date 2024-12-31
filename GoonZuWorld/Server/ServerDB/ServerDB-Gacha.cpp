//---------------------------------
// ���� [07/04/17]
//---------------------------------

#include "Char/CharManager/CharManager.h"

#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Gacha.h"

#include "../../CommonLogic/Msg/MsgType-Gacha.h"
#include "../../CommonLogic/MsgType-System.h"

#include "../../Server/GachaManager/GachaManager.h"

#include "../../CommonLogic/MsgRval-Define.h"



void cltServer::DoMsg_DBMSG_RESPONSE_GACHABUY( sPacketHeader* pPacket )
{
	sDBResponse_GachaBuy* pclinfo = (sDBResponse_GachaBuy*)pPacket;

	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false ) return ;
	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	pclchar->bNowGachaBuy = false;

	if( pclinfo->siGetItemPos < 0 || pclinfo->siGetItemPos >= MAX_ITEM_PER_PERSON )		return;
	if( pclinfo->siKeyItemPos < 0 || pclinfo->siKeyItemPos >= MAX_ITEM_PER_PERSON )		return;

	if ( pclinfo->siResult != 1 )
	{
		if( pclinfo->siResult == -2 )
		{
			SendServerResponseMsg(0, SRVAL_GACHA_FAIL_KEYNEED, 0, 0, pclchar->GetID());
			return; 	
		}

		return ;
	}
	// ĳ������ ���� ������ ������Ʈ �Ѵ�.

	pclchar->pclCI->uiGachaCnt = pclinfo->uiGachaCnt;


	// �κ��丮�� ������Ʈ �Ѵ�.

	// ���� �����Ѵ�.
	pclchar->SetInputItemReserve( pclinfo->siGetItemPos , 0 );
	pclchar->SetInputItemReserve( pclinfo->siKeyItemPos , 0);

	pclchar->pclCI->clCharItem.clItem[pclinfo->siGetItemPos].Set(&pclinfo->clGetItem);
	pclchar->pclCI->clCharItem.clItem[pclinfo->siKeyItemPos].Set(&pclinfo->clKeyItem);

	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	{
		cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siGetItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclinfo->clGetItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}
	{
		cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siKeyItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclinfo->clKeyItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}

	// �ְ� ��ǰ�� �������̶�� ��ü �˸�
	if( pclinfo->bBestProduct )
	{
		((cltServer*)(pclClient))->SendRareItemMade(id, &pclinfo->clGetItem, RAREITEM_NOTICE_SWITCH_GACHA );
	}

	// Ŭ���̾�Ʈ�� ���� ���� ������ ������.
	//[����] ���� ����. ������ ���� ������ ������ �������ɷ� ����. => 2008-9-2
	cltGameMsgResponse_GachaBuy clinfo( pclinfo->bBestProduct , &pclinfo->clGachaGetItem, pclinfo->uiGachaCnt );
	cltMsg clMsg(GAMEMSG_RESPONSE_GACHABUY, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	// ������ ������ �߰�
	pclItemManager->AddUseNum( pclinfo->clUseKeyItem.siUnique, pclinfo->clUseKeyItem.siItemNum );

	// ����Ű ��� �α�
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� ����� �������� ������ ���� ��û. 
		// param1	== ����� Ű ��ġ
		// param2	== ���� ȸ��
		// param3	== ���� Add Count

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GACHA, LOGCOMMAND_INDEX_GACHA_BUYUSED, 
										0, (cltCharServer*)pclchar, NULL, 0, 0, 0, &pclinfo->clUseKeyItem, pclinfo->clKeyItem.siItemNum, 0, 0, 0, 0, 0,
										pclinfo->siKeyItemPos, pclinfo->uiGachaCnt, pclinfo->uiGachaCntAdd, 0, 0,
										NULL, NULL);
	}

	// ȹ�� ������ �α�
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� ����� �������� ������ ���� ��û. 
		// param1		== ���� ������ ��ġ, 
		// param2		== ���� ȸ��
		// param3		== �ְ��ǰ����
		// param4       == Ű����������ũ
		// param5		== ���� Add Count

		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_GACHA, LOGCOMMAND_INDEX_GACHA_BUY, 
							0, (cltCharServer*)pclchar, NULL, 0, 0, 0, &pclinfo->clGachaGetItem, pclinfo->clGetItem.siItemNum, 0, 0, 0, 0, 0,
							pclinfo->siGetItemPos, pclinfo->uiGachaCnt, pclinfo->bBestProduct, pclinfo->clUseKeyItem.siUnique, pclinfo->uiGachaCntAdd,
							NULL, NULL);
	}
}