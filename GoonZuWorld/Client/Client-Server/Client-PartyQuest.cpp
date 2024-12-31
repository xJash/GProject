#include "../Client.h"
#include "../Music\Music.h"
#include "../CommonLogic/MsgType.h"

#include "Char/CharManager/CharManager.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"
#include "../ninterface/npartydlg/NPartyDlg.h"

#include "../../CommonLogic/MsgType-PartyQuest.h"
#include "../PartyQuestMgr/PartyQuestMgr_Client.h"


// [��ȣ] ��Ƽ����Ʈ ���۽� ���� üũ ���
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_CHECKSTART(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PartyQuest_CheckStart* pclInfo = (cltGameMsgResponse_PartyQuest_CheckStart*)pclMsg->cData;

	if(pclInfo == NULL)
		return;

	// �̰����� ����Ʈ ���۽� ���� üũ ����� ���� ó���� �մϴ�.
	
	// ��Ƽ����Ʈ ���� ����/�Ұ���
	SI32 siMessage = 0;
	if(pclInfo->m_bResult == true)
		siMessage = PARTYQUEST_MESSAGE_CAN_START;
	else
		siMessage = PARTYQUEST_MESSAGE_CANNOT_START;


	((CNPartyDlg*)m_pDialog[NPARTY_DLG])->StartPartyQuestMessage(siMessage);
}


// [��ȣ] ��Ƽ����Ʈ ���� ��û ���
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_START(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PartyQuest_Start* pclInfo = (cltGameMsgResponse_PartyQuest_Start*)pclMsg->cData;

	if(pclInfo == NULL)
		return;

	// ��Ƽ����Ʈ�� �޾ҽ��ϴ�.
	m_pPartyQuestMgr->StartPartyQuestData(&pclInfo->m_PartyQuestData);
}


// ��Ƽ����Ʈ ���� ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_UPDATE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PartyQuest_Update* pclInfo = (cltGameMsgResponse_PartyQuest_Update*)pclMsg->cData;

	if(pclInfo == NULL)
		return;


    m_pPartyQuestMgr->UpdatePartyQuestData(&pclInfo->m_PartyQuestData, pclInfo->m_dwQuestTime, pclInfo->m_bClear);
}


// ��Ƽ����Ʈ ����
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTY_QUEST_GIVEUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_PartyQuest_GiveUp* pclInfo = (cltGameMsgResponse_PartyQuest_GiveUp*)pclMsg->cData;

	if(pclInfo == NULL)
		return;

	// ��Ƽ����Ʈ�� ����ƽ��ϴ�. �÷��̾ �������ִ� ��Ƽ����Ʈ ������ �ʱ�ȭ �մϴ�.
	cltClient* pClient = (cltClient*)pclClient;
	pClient->m_pPartyQuestMgr->DoGiveUpPartyQuest();

	// ��Ƽ���鿡�� �˷��ݴϴ�.
	((CNPartyDlg*)m_pDialog[NPARTY_DLG])->StartPartyQuestMessage(pclInfo->m_siMessage);
}


