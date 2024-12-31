#include "..\Common\CommonHeader.h"

//---------------------------------------
// Server
//---------------------------------------
#include "..\Server\Server.h"
#include "..\Server\Statistics\Statistics.h"


#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-DailyQuest.h"

#include "..\Common\DailyQuest\DailyQuestMgr.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_DAILYQUESTLIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuestList * pclinfo = (cltGameMsgRequest_DailyQuestList*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;	
	
	cltGameMsgResponse_DailyQuestList clGameMsgResponse_DailyQuestList;
#ifdef _SAFE_MEMORY
	pclDailyQuestMgr->GetDailyQuestList( &clGameMsgResponse_DailyQuestList.m_DailyQuestObjDataList[0] );
#else
	pclDailyQuestMgr->GetDailyQuestList( clGameMsgResponse_DailyQuestList.m_DailyQuestObjDataList );
#endif
	cltMsg clMsg( GAMEMSG_RESPONSE_DAILYQUESTLIST, sizeof( clGameMsgResponse_DailyQuestList ), (BYTE*)&clGameMsgResponse_DailyQuestList );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//pclDailyQuestMgr->GetDailyQuestObj( pclinfo->siDailyQuestIndex, pclinfo->siDailyQuestCount, FromPersonID, id );
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuestSelect( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuestSelect * pclinfo = (cltGameMsgRequest_DailyQuestSelect*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;
	
	// ������ DailyQuest ���������� üũ
	if ( pclCM->CR[id]->pclCI->clDailyQuestInfo.siMonsterKind > 0 )
	{
		return;
	}
	
	SI16 ListIndex = -1;
	// ������ ����Ʈ ����Ʈ ����Ʈ�� ����.
	CDailyQuestObjData *pTemp = pclDailyQuestMgr->GetDailyQuestListObj( pclinfo->DailyQuestObjData.m_siIndex, pclinfo->DailyQuestObjData.m_siCount, &ListIndex );
	
	if ( pTemp == NULL )
	{
		// ���� �� ����Ʈ�� �����ؼ� ����Ʈ�� ���� ���� ���� �Ұ���.
		SendServerResponseMsg(0, SRVAL_DAILYQUEST_FAIL_NOTEXISTLIST,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	// pc�� ����Ʈ�� ��� ����ڰ� pc������ ���� Ȯ��
/*	if ( pTemp->m_bPCRoomQuest )
	{
		if( !pclCM->CR[ id ]->pclCI->clBI.IsPCRoom() ) return;
	}*/

	// ������ ����Ʈ�� ���� ����Ʈ �����̶� ������ Ȯ��
	if ( ! pTemp->IsSameData( &pclinfo->DailyQuestObjData ) )
	{
		// ���� �� ����Ʈ�� �����ؼ� ����Ʈ�� ���� ���� ���� �Ұ���.
		SendServerResponseMsg(0, SRVAL_DAILYQUEST_FAIL_NOTEXISTLIST,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < pclinfo->DailyQuestObjData.m_siFee )
	{		
		return;
	}
	
	SI32 VillageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	// �ʵ忡���� �𺴰� ���̾�α� ���������� �ǰ� �ҷ��� �� ����
	//if( VillageUnique < 1 || VillageUnique >= MAX_VILLAGE_NUMBER )	
	//{
	//	return;
	//}

	GMONEY VillagePayFeeMoney = pclinfo->DailyQuestObjData.m_siFee * VILLAGE_PROFIT_RATE_FOR_DAILYQUEST /100;

	// ����Ʈ�� ���õǾ����Ƿ�, ����Ʈ���� �����Ѵ�.
	pclDailyQuestMgr->InitQuestListData( ListIndex, pclinfo->DailyQuestObjData.m_siMonsterKind, 
										 pclinfo->DailyQuestObjData.m_siMonsterNum,
										 pclinfo->DailyQuestObjData.m_siRewardItemUnique, pclinfo->DailyQuestObjData.m_siRewardItemNum, 
										 pclinfo->DailyQuestObjData.m_siRewardMoney, pclinfo->DailyQuestObjData.m_siRewardExp, 
										 pclinfo->DailyQuestObjData.m_siFee, pclinfo->DailyQuestObjData.m_siLeftTime);

	sDBRequest_DailyQuestAdd clMsg( 
		ListIndex,
		FromPersonID, 
		id,
		pclinfo->DailyQuestObjData.m_siMonsterKind,
		pclinfo->DailyQuestObjData.m_siMonsterNum,
		pclinfo->DailyQuestObjData.m_siRewardItemUnique,
		pclinfo->DailyQuestObjData.m_siRewardItemNum,
		pclinfo->DailyQuestObjData.m_siRewardMoney,
		pclinfo->DailyQuestObjData.m_siRewardExp,
		pclinfo->DailyQuestObjData.m_siFee,
		pclinfo->DailyQuestObjData.m_siLeftTime,
		pclinfo->DailyQuestObjData.m_siLeftTime,
		VillageUnique,
		RANKTYPE_CITYHALL,
		VillagePayFeeMoney,
		false,
		pclinfo->bMoneySelected
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, VillagePayFeeMoney);
	
	// �𺴰� ����Ʈ ���� ���. 
	pclStatisticsManager->clDailyStatistics.siDailyQuestAcceptNum ++;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuestSituation( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuestSituation * pclinfo = (cltGameMsgRequest_DailyQuestSituation*)pclMsg->cData;

	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ DailyQuest �������� �ƴ϶�� return
	if ( pclCM->CR[id]->pclCI->clDailyQuestInfo.siMonsterKind == 0 )
	{
		return;
	}

	cltGameMsgResponse_DailyQuestSituation clGameMsgResponse_DailyQuestSituation( &pclCM->CR[id]->pclCI->clDailyQuestInfo) ;
	cltMsg clMsg( GAMEMSG_RESPONSE_DAILYQUESTSITUATION, sizeof( clGameMsgResponse_DailyQuestSituation ), (BYTE*)&clGameMsgResponse_DailyQuestSituation );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DailyQuestEnd( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DailyQuestEnd * pclinfo = (cltGameMsgRequest_DailyQuestEnd*)pclMsg->cData;
	
	if( pclCM->IsValidID( id ) == false )return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ������ DailyQuest �������� �ƴ϶�� return
	if ( pclCM->CR[id]->pclCI->clDailyQuestInfo.siMonsterKind == 0 )
	{
		return;
	}

	cltItem clItem;
	clItem.Init();
	sDBRequest_DailyQuestDel clMsg(
		FromPersonID,
		id,
		0,
		0,
		&clItem,
		1,
		0,
		0,
		0
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
	return;
}