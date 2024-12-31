#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../common/Order/order.h"
#include "../../common/JWLib/IsCorrectID/IsCorrectID.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "../../CommonLogic/MsgType-PartyQuest.h"

#include "../../common/PartyMgr/PartyMgr.h"
#include "../../common/PartyMgr/PartyObj.h"

// [��ȣ] ��Ƽ����Ʈ ���۽� ���� üũ	
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_QUEST_CHECKSTART(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PartyQuest_CheckStart* pclInfo = (cltGameMsgRequest_PartyQuest_CheckStart*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if( NULL == pclChar)
		return;

	// �̰����� ��Ƽ����Ʈ ���� ��û�� �� ��Ƽ�� ��Ƽ����Ʈ ���� ������ ���߰� �ִ��� üũ �մϴ�.
	bool bResult = false;

	cltServer* pClient = (cltServer*)pclClient;

	CPartyObj* pPartyObject = pClient->pclPartyMgr->GetPartyObj(pclInfo->m_siPartyIndex);
	if(pPartyObject == NULL)
		return;

	bResult = m_pPartyQuestMgr->DoCheckPartyQuest(pPartyObject);

	// üũ �� ��� ���� ���� �մϴ�.
	cltGameMsgResponse_PartyQuest_CheckStart clInfo(bResult);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg);
}


// [��ȣ] ��Ƽ����Ʈ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_QUEST_START(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PartyQuest_Start* pclInfo = (cltGameMsgRequest_PartyQuest_Start*)pclMsg->cData;
	if(NULL == pclInfo)
		return;

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if( NULL == pclChar)
		return;

	// ��Ƽ����Ʈ �����ϱ� ������ ��Ƽ������ ������ ����Ǿ����� �����Ƿ� �ο��ϱ� ���� �ٽ� üũ �մϴ�.
	cltServer* pClient = (cltServer*)pclClient;

	CPartyObj* pPartyObject = pClient->pclPartyMgr->GetPartyObj(pclInfo->m_siPartyIndex);
	if(pPartyObject == NULL)
		return;

	bool bResult = m_pPartyQuestMgr->DoCheckPartyQuest(pPartyObject);
	
	if(bResult == false)
	{
		cltGameMsgResponse_PartyQuest_CheckStart clInfo(false);
		cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART, sizeof(clInfo), (BYTE*)&clInfo);
		pclChar->SendNetMsg( (sPacketHeader*)&clMsg);
		
		return;
	}

	// �ش� ��Ƽ�� ����Ʈ�� �ο� �մϴ�.
	SI32 siCategoryIndex	= pclClient->m_pServer_PartyMatchingMgr->Get_Category(pPartyObject->GetPartyLeaderUnique());
	SI32 siMissionIndex		= pclClient->m_pServer_PartyMatchingMgr->Get_Mission(pPartyObject->GetPartyLeaderUnique());

	if(siCategoryIndex < 0 || siCategoryIndex >= MAX_PARTYQUEST_CATEGORY_NUM)
		return;

	if(siMissionIndex < 0 || siMissionIndex >= MAX_PARTYQUEST_MISSION_NUM)
		return;

	// ��Ƽ���� ��Ƽ����Ʈ �ο�
	bResult = pClient->m_pPartyQuestMgr->SetPartyQuestData(&pPartyObject->m_PartyQuestInfo, siCategoryIndex, siMissionIndex);

	pPartyObject->m_dwEndTime = pclClient->CurrentClock + (pPartyObject->m_PartyQuestInfo.m_siTimeLimit*1000);
	pPartyObject->m_dwElapseTime = pclClient->CurrentClock;

	if(bResult == false)
	{
		cltGameMsgResponse_PartyQuest_CheckStart clInfo(false);
		cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART, sizeof(clInfo), (BYTE*)&clInfo);
		pclChar->SendNetMsg( (sPacketHeader*)&clMsg);

		return;
	}

		

	// ����Ʈ�� ���� �Ǿ����ϴ�. ��Ƽ���鿡�� �˷��ݴϴ�.
	cltGameMsgResponse_PartyQuest_Start clInfo(&pPartyObject->m_PartyQuestInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_START, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->SendAllPartyMemberMsg((sPacketHeader*)&clMsg, pclChar->siPartyIndex);

	// ���������� ����Ʈ ������ ����Ǹ� ��Ƽ��Ī ����Ʈ���� ��Ƽ��Ī �÷ȴ��� �����ش�.
	if ( NULL != pclClient->m_pServer_PartyMatchingMgr )
	{
		pclClient->m_pServer_PartyMatchingMgr->Remove_PartyMatching( pclChar->GetCharUnique() );
	}
}






