#include "..\Common\CommonHeader.h"

//---------------------------------------
// Server
//---------------------------------------
#include "..\Server\Server.h"
#include "..\Server\Statistics\Statistics.h"


#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest3.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-DailyQuest3.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"


#include "..\Common\DailyQuest3\DailyQuest3Mgr.h"
#include "Char\CharManager\CharManager.h"

#include "../../CommonLogic/MsgRval-Define.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_DAILYQUEST3LIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuest3List * pclinfo = (cltGameMsgRequest_DailyQuest3List*)pclMsg->cData;
	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;	

	cltGameMsgResponse_DailyQuest3List clGameMsgResponse_DailyQuest3List;
#ifdef _SAFE_MEMORY
	pclDailyQuest3Mgr->GetDailyQuest3List( &clGameMsgResponse_DailyQuest3List.m_DailyQuest3ObjDataList[0] );
#else
	pclDailyQuest3Mgr->GetDailyQuest3List( clGameMsgResponse_DailyQuest3List.m_DailyQuest3ObjDataList );
#endif
	SI32 CharLevel  = pclClient->pclCM->CR[id]->pclCI->clIP.GetLevel();
	cltMsg clMsg( GAMEMSG_RESPONSE_DAILYQUEST3LIST, sizeof( clGameMsgResponse_DailyQuest3List ), (BYTE*)&clGameMsgResponse_DailyQuest3List );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//pclDailyQuestMgr->GetDailyQuestObj( pclinfo->siDailyQuestIndex, pclinfo->siDailyQuestCount, FromPersonID, id );
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuest3Select( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuest3Select * pclinfo = (cltGameMsgRequest_DailyQuest3Select*)pclMsg->cData;

	SI32 charlevel = pclCM->CR[id]->pclCI->clIP.GetLevel();

	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;
	
	// ������ DailyQuest ���������� üũ
	if ( pclCM->CR[id]->pclCI->clDailyQuest3Info.siItemUnique > 0 )
	{
		return;
	}
	
	SI32 ListIndex = -1;
	
	/*if (pclinfo->DailyQuest3ObjData.m_bHiddenQuest != true) {*/
		CDailyQuest3ObjData *pTemp = pclDailyQuest3Mgr->GetDailyQuest3ListObj( pclinfo->DailyQuest3ObjData.m_siIndex, 
			pclinfo->DailyQuest3ObjData.m_siCount,
			&ListIndex );

		if ( pTemp == NULL )
		{
			// ���� �� ����Ʈ�� �����ؼ� ����Ʈ�� ���� ���� ���� �Ұ���.
			SendServerResponseMsg(0, SRVAL_DAILYQUEST_FAIL_NOTEXISTLIST,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	//}
	// ������ ����Ʈ ����Ʈ ����Ʈ�� ����.
	
	// �ʿ� �������� �˻��ؼ� �����.
	int		Inventory;// �κ��丮, �ش� ������ 
	SI32	itemunique = ITEMUNIQUE(24084);

	for( Inventory = PERSONITEM_INV0; Inventory < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; Inventory++ )
	{
		cltItem* pclItem = &pclCM->CR[id]->pclCI->clCharItem.clItem[Inventory];
		cltItem Useitem = NULL;
		Useitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[Inventory]);
		Useitem.siItemNum = 1;
		if(pclItem == NULL)	return;
		if( pclItem->siUnique == itemunique)
		{
			sDBRequest_UseItem useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), Inventory, &Useitem, USEITEM_REASON_DAILYQUEST3);
			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
			break;

		}
		else{
			continue;
		}
	}

	// ������ ����Ʈ�� ���� ����Ʈ �����̶� ������ Ȯ��
	//if ( ! pTemp->IsSameData( &pclinfo->DailyQuest2ObjData ) )
	//{
	//	// ���� �� ����Ʈ�� �����ؼ� ����Ʈ�� ���� ���� ���� �Ұ���.
	//	SendServerResponseMsg(0, SRVAL_DAILYQUEST_FAIL_NOTEXISTLIST,  0, 0, pclCM->CR[id]->GetCharUnique());
	//	return;
	//}

	//pclinfo->DailyQuest2ObjData.m_siRewardExp 
	//	= (pclinfo->DailyQuest2ObjData.m_siRewardExp * pclinfo->DailyQuest2ObjData.m_siMonsterNum * 130 /100) * (charlevel-75)/10; // ����ġ ����
	//pclinfo->DailyQuest2ObjData.m_siRewardExp = (pclinfo->DailyQuest2ObjData.m_siRewardExp /100)*100;//����ġ ����.

    //pclinfo->DailyQuest2ObjData.m_siFee = (pclinfo->DailyQuest2ObjData.m_siRewardExp * 6) / 10;// ���������


	/*if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < pclinfo->DailyQuest2ObjData.m_siFee )
	{		
		return;
	}*/
	
	SI32 VillageUnique = pclCM->CR[id]->GetCurrentVillageUnique();

	cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice(pclClient->pclItemManager,ITEMUNIQUE(24082));//������ �ü� �޾� ����
	if (pclprice == NULL) return;
	GMONEY VillagePayFeeMoney = pclprice->siPrice*0.1;
	// ����Ʈ ���� ������ �ü��� ���Ͻü��� 10%�� ���� ���ͱ����� ����
	sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, VillageUnique, VillagePayFeeMoney);
	pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);

	if (pclinfo->DailyQuest3ObjData.m_bHiddenQuest == true) { // �̰� ���� ����Ʈ �̸�.
		pclinfo->DailyQuest3ObjData.m_siItemNum = 1;// �ű⸦ ����� ��� �Ѱ��� �����.
		pclinfo->DailyQuest3ObjData.m_siRewardItemNum = pclinfo->DailyQuest3ObjData.m_siRewardItemNum*2; // ���� ������ ���� 2��
		pclinfo->DailyQuest3ObjData.m_siRewardExp = pclinfo->DailyQuest3ObjData.m_siRewardExp *2; //�������ġ 2��
		// ���� Gp�� ����Ʈ�� �����鼭 ���� ����ؼ� �÷��ش�. ������ ���� �÷��ش�.
		//pclinfo->DailyQuest2ObjData.m_bHiddenQuest = true;
	}

	sDBRequest_DailyQuest3Add clMsg( 
		ListIndex,
		FromPersonID, 
		id,
		pclinfo->DailyQuest3ObjData.m_siItemUnique,
		pclinfo->DailyQuest3ObjData.m_siItemNum,
		pclinfo->DailyQuest3ObjData.m_siRewardItemUnique,
		pclinfo->DailyQuest3ObjData.m_siRewardItemNum,
		pclinfo->DailyQuest3ObjData.m_siRewardExp,
		pclinfo->DailyQuest3ObjData.m_siFee,
		pclinfo->DailyQuest3ObjData.m_siLeftTime,
		pclinfo->DailyQuest3ObjData.m_siLeftTime,
		VillageUnique,
		RANKTYPE_CITYHALL,
		VillagePayFeeMoney,
		false,
		pclinfo->bMoneySelected,
		pclinfo->DailyQuest3ObjData.m_bHiddenQuest
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuest3Situation( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuest3Situation * pclinfo = (cltGameMsgRequest_DailyQuest3Situation*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ DailyQuest �������� �ƴ϶�� return
	if ( pclCM->CR[id]->pclCI->clDailyQuest3Info.siItemUnique == 0 )
	{
		return;
	}

	cltGameMsgResponse_DailyQuest3Situation clGameMsgResponse_DailyQuest3Situation( &pclCM->CR[id]->pclCI->clDailyQuest3Info) ;
	cltMsg clMsg( GAMEMSG_RESPONSE_DAILYQUEST3SITUATION, sizeof( clGameMsgResponse_DailyQuest3Situation ), (BYTE*)&clGameMsgResponse_DailyQuest3Situation );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuest3End( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuest3End * pclinfo = (cltGameMsgRequest_DailyQuest3End*)pclMsg->cData;
	
	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ DailyQuest �������� �ƴ϶�� return
	if ( pclCM->CR[id]->pclCI->clDailyQuest3Info.siItemUnique == 0 )
	{
		return;
	}

	cltItem clItem;
	clItem.Init();
	sDBRequest_DailyQuest3Del clMsg(FromPersonID,id,0,0, pclCM->CR[id]->pclCI->clDailyQuest3Info.siItemUnique,&clItem,1,0,false);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
	return;
}