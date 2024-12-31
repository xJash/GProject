
#include "..\Server\Server.h"
#include "MsgRval-Define.h"

#include "../CommonLogic/Msg/MsgType-NamingQuest.h"

#include "Char/CharManager/CharManager.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"


void cltServer::DoMsg_GAMEMSG_REQUEST_NAMINGQUEST_START(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NamingQuestStart* pclinfo = (cltGameMsgRequest_NamingQuestStart*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// ĳ���Ͱ� ������ �ִ� ����Ʈ ������ Ȯ���Ѵ�.
	// ĳ���Ͱ� ������ �ִ� ����Ʈ������ �̻��� ��쿡�� ������ �����Ѵ�.
	if( (pclchar->pclCI->clQuestInfo.clNamingQuestInfo.siUnique > 0 || pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestUnique > 0) &&
		pclchar->pclCI->clQuestInfo.clNamingQuestInfo.siUnique != pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestUnique )
	{
		// �̻������� �α׷� ����Ѵ�.
		pclLog->FilePrint("Config\\QuestError.log", "Name[%s], NamingQuestUnique[%d, %d]", pclchar->GetName(),
			pclchar->pclCI->clQuestInfo.clNamingQuestInfo.siUnique,
			pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestUnique );

		pclchar->pclCI->clQuestInfo.clNamingQuestInfo.Init();
		pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].Init();
	}

	if ( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_NAMING].siCurQuestUnique > 0) 
	{
		cltServerResponseValue clreturn(0, SRVAL_NAMINGQUEST_START_FAIL, 0, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		return ;
	}

	if ( pclchar->MakeNamingQuest( pclinfo->siIndex, pclinfo->siLevel ) == false )
	{
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETPERSONCURRENTNAMING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetPeronCurrentNaming* pclinfo = (cltGameMsgRequest_SetPeronCurrentNaming*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;
	if( pclinfo->siIndex < 0 || pclinfo->siIndex >= MAX_NAMINGQUEST_INDEX )	return;

	if ( pclchar->pclCI->clPersonNaming.m_siLevel[pclinfo->siIndex] < pclinfo->siLevel )
		return;

	if ( pclNamingQuestManager->GetMaxLevel(pclinfo->siIndex) < pclinfo->siLevel )
		return;

	// ����Ʈ ���¸� DB�� �����Ѵ�.
	sDBRequest_SetPersonCurrentNaming clMsg2(pclchar->pclCI->GetPersonID(), pclinfo->siIndex, pclinfo->siLevel);
	SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);
}