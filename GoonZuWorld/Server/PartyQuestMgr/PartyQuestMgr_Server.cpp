#include "PartyQuestMgr_Server.h"

#include "Char/CharManager/CharManager.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../Lib/dxutil.h"
#include "../../Client/Client.h"

#include "../../client/InterfaceMgr/InterfaceFile.h"
#include "../../client/InterfaceMgr/InterfaceMgr.h"
#include "../../common/CommonHeader.h"
#include "../../common/PartyMgr/PartyMgr.h"
#include "../../common/PartyMgr/PartyObj.h"
#include "../../Server/server.h"
#include "../../CommonLogic/MsgType-PartyQuest.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"


extern cltCommonLogic* pclClient;

CPartyQuestMgr_Server::CPartyQuestMgr_Server()
{
	ZeroMemory(this, sizeof(CPartyQuestMgr_Server));
}

CPartyQuestMgr_Server::~CPartyQuestMgr_Server()
{
	
}


bool CPartyQuestMgr_Server::Initialize()			//	�Ŵ��� �ʱ�ȭ
{
	bool bResult = false;
	
	CPartyQuestMgr_Common::LoadFiles_PartyQuest();

	return bResult;
}

bool CPartyQuestMgr_Server::CheckSameArea(CPartyObj* pPartyObj)
{	
	cltServer* pServer = (cltServer*)pclClient;

	SI32 siLeaderID = pPartyObj->GetPartyLeaderUnique();
	
	if(pServer->pclCM->IsValidID(siLeaderID) == false)
		return false;

	for(SI32 i = 0; i < MAX_PARTY_USER_NUM; i++)
	{
		stPartyUser* pstPartyMember = pPartyObj->GetPartyUser(i);

		if((pstPartyMember == NULL) || (pstPartyMember->bPartyStatus == false))	
			continue;

		if(pclClient->pclCM->IsValidID(pstPartyMember->siCharUnique) == false)	
			continue;

		if(pclClient->pclCM->CR[pstPartyMember->siCharUnique]->pclCI->GetPersonID() != pstPartyMember->siPersonID)
			continue;

		if(pServer->pclCM->CR[siLeaderID]->GetMapIndex() != pServer->pclCM->CR[pstPartyMember->siCharUnique]->GetMapIndex())
			return false;
	}

	return true;
}

// ��Ƽ����Ʈ ���� ����
void CPartyQuestMgr_Server::UpdatePartyQuest(SI32 siCharID, SI32 siPartyIndex, SI32 siQuestType, SI32 siCondition, SI32 siAmount)
{
	cltServer* pServer = (cltServer*)pclClient;

	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return;


    bool bResult = CheckSameArea(pPartyObject); // ���� ������ ���ٸ� ����Ʈ ������ �ȵ˴ϴ�.

	if(bResult == false)	return;
		

	cltCharServer* pclChar = pServer->pclCM->GetCharServer(siCharID);
	if( NULL == pclChar)
		return;

	SI32 siState = PARTYQUEST_UPDATE_STATE_NONE;
	
	bool bIncreaseCondition = false;
	bool bCurQuestClear		= false;

	bIncreaseCondition	= IncreasePartyQuestCondition(siPartyIndex, siQuestType, siCondition, siAmount);	// ����Ʈ Amount ����

	if(bIncreaseCondition == true)
		bCurQuestClear	= ProcessCurrentQuestClear(siPartyIndex, siCharID);									// ���� ������ ����Ʈ�� Ŭ���� �Ǿ����� üũ �մϴ�.
	
	if(bCurQuestClear == true)
		siState = PARTYQUEST_UPDATE_STATE_CLEAR;
	else if(bIncreaseCondition == true)
		siState = PARTYQUEST_UPDATE_STATE_INCREASE;


	// ���ŵ� ����Ʈ ������ �ִٸ� ��Ƽ���鿡�� �˸��ϴ�.
	if(bIncreaseCondition == true)
	{
		DWORD dwQuestTime = (TABS(pPartyObject->m_dwEndTime) - TABS(pclClient->CurrentClock)) / 1000; // per second
		cltGameMsgResponse_PartyQuest_Update clInfo(bCurQuestClear ,&pPartyObject->m_PartyQuestInfo, dwQuestTime);
		cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_UPDATE, sizeof(clInfo), (BYTE*)&clInfo);
		pServer->pclCM->SendAllPartyMemberMsg((sPacketHeader*)&clMsg, pclChar->siPartyIndex);
	}

	return;
}

bool CPartyQuestMgr_Server::ProcessAllQuestClear(SI32 siPartyIndex)
{
	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return false;

	SI32 siCurStep = pPartyObject->m_PartyQuestInfo.m_siQuestStep;

	SI32 siCategoryIndex	= pPartyObject->m_PartyQuestInfo.m_siCategoryIndex;
	SI32 siMissionIndex		= pPartyObject->m_PartyQuestInfo.m_siMissionIndex;

	// 
	if(CPartyQuestMgr_Common::GetPartyQuestUnitData(siCategoryIndex, siMissionIndex, siCurStep+1)->m_siQuestType == PARTYQUEST_TYPE_CLEAR)
	{
		// �ش� ��Ƽ�� �����ϰ� �ִ� ��Ƽ����Ʈ ������ �ʱ�ȭ �մϴ�.
		ZeroMemory(&pPartyObject->m_PartyQuestInfo, sizeof(PartyQuest_UnitData));
		return true;
	}
	
	return false;
}

bool CPartyQuestMgr_Server::ProcessCurrentQuestClear(SI32 siPartyIndex, SI32 siCharID)
{
	// ���� �������� ����Ʈ�� Ŭ���� �Ǿ����� Ȯ���մϴ�.

	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return false;


	SI32 siCategoryIndex	= pPartyObject->m_PartyQuestInfo.m_siCategoryIndex;
	SI32 siMissionIndex		= pPartyObject->m_PartyQuestInfo.m_siMissionIndex;
	SI32 siStep				= pPartyObject->m_PartyQuestInfo.m_siQuestStep;
	
	switch(pPartyObject->m_PartyQuestInfo.m_siQuestType)
	{
	case PARTYQUEST_TYPE_NONE:
		break;

	case PARTYQUEST_TYPE_HUNTING:
		{
			SI32 siCurAmount = pPartyObject->m_PartyQuestInfo.m_siAmount;										// ���� ����� ���� ��
			SI32 siMaxAmount = GetPartyQuestUnitData(siCategoryIndex, siMissionIndex, siStep)->m_siAmount;		// ��ǥġ ���� ��

			// ���� ����Ʈ�� Ŭ���� �ߴٸ� 
			if(siCurAmount >= siMaxAmount)
			{
				// ����Ʈ ����
				ProcessReward(siPartyIndex, siCharID);

				// ����Ʈ�� ���� ������ ����Ʈ�� ���� �մϴ�.					
				if(ProcessAllQuestClear(siPartyIndex) == false) 
				{
					SI32 siCurStep = pPartyObject->m_PartyQuestInfo.m_siQuestStep;
					CPartyQuestMgr_Common::SetPartyQuestData(&pPartyObject->m_PartyQuestInfo, siCategoryIndex, siMissionIndex, siCurStep+1);

					pPartyObject->m_dwEndTime = pclClient->CurrentClock + (pPartyObject->m_PartyQuestInfo.m_siTimeLimit*1000);
					pPartyObject->m_dwElapseTime = pclClient->CurrentClock;
				}

				return true;
			}
		}
		break;

	case PARTYQUEST_TYPE_MAKEITEM:
		{
			SI32 siCurAmount = pPartyObject->m_PartyQuestInfo.m_siAmount;										// ���� ������ ������ ����
			SI32 siMaxAmount = GetPartyQuestUnitData(siCategoryIndex, siMissionIndex, siStep)->m_siAmount;		// �� �����ؾ��� ������ ����

			// ���� ����Ʈ�� Ŭ���� �ߴٸ� 
			if(siCurAmount >= siMaxAmount)
			{
				// ����Ʈ ����
				ProcessReward(siPartyIndex, siCharID);

				// ����Ʈ�� ���� ������ ����Ʈ�� ���� �մϴ�.					
				if(ProcessAllQuestClear(siPartyIndex) == false) 
				{
					SI32 siCurStep = pPartyObject->m_PartyQuestInfo.m_siQuestStep;
					CPartyQuestMgr_Common::SetPartyQuestData(&pPartyObject->m_PartyQuestInfo, siCategoryIndex, siMissionIndex, siCurStep+1);

					pPartyObject->m_dwEndTime = pclClient->CurrentClock + (pPartyObject->m_PartyQuestInfo.m_siTimeLimit*1000);
					pPartyObject->m_dwElapseTime = pclClient->CurrentClock;
				}

				return true;
			}
		}
		break;

	default:
		break;
	}

	return false;
}

void CPartyQuestMgr_Server::ProcessReward(SI32 siPartyIndex, SI32 siCharID)
{
	cltServer* pServer = (cltServer*)pclClient;

	cltCharServer* pclChar = pServer->pclCM->GetCharServer(siCharID);
	if ( NULL == pclChar )
		return;
	
	// ���� Ŭ������ ����Ʈ�� ���� ������ ���ݴϴ�.
	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return;

	 
	// ��Ƽ������ �������� �Ѹ��� ����������� �����մϴ�.

	SI32 siItemUnique = 0;
	SI32 siItemAmount = 0;
	SI32 siItemUseDay = 0;

	SI32 RewardUserArray[MAX_PARTY_USER_NUM];
	ZeroMemory(RewardUserArray, sizeof(RewardUserArray));
	SI32 siCount = 0;

	// ��Ƽ�� �ε����� ��ȿ�� ��Ƽ���� �߷�����.
	for(SI32 siPlayerIndex = 0; siPlayerIndex < MAX_PARTY_USER_NUM; siPlayerIndex++)
	{
		stPartyUser* pUser = pServer->pclPartyMgr->GetPartyObj(pclChar->siPartyIndex)->GetPartyUser(siPlayerIndex);
		
		if(pUser == NULL || pServer->pclCM->IsValidID(pUser->siCharUnique) == false)
			continue;

		RewardUserArray[siCount] = pUser->siCharUnique;
		siCount++;
	}

	if(siCount <= 0)
		return;

	// // ��ȿ�� ��Ƽ���鿡�� �������ġ�� �����ŵ�ϴ�.
	for(SI32 siRewardEXPIndex = 0; siRewardEXPIndex < siCount; siRewardEXPIndex++)
	{
		cltCharServer* pclRewardEXPChar = pServer->pclCM->GetCharServer(RewardUserArray[siRewardEXPIndex]);
		if ( NULL == pclRewardEXPChar )
			continue;

		pclRewardEXPChar->IncreaseExp((SI64)pPartyObject->m_PartyQuestInfo.m_siRewardEXP);
	}

	SI32 siRewardCharUnique = RewardUserArray[rand()%siCount];
	
	cltCharServer* pclRewardChar = pServer->pclCM->GetCharServer(siRewardCharUnique);
	if ( NULL == pclRewardChar )
		return;

	// ���� ������ ����
	for(SI32 i = 0; i < MAX_PARTYQUEST_REWARD_NUM; i++)
	{
		siItemUnique = pPartyObject->m_PartyQuestInfo.m_siRewardItemUnique[i];
		siItemAmount = pPartyObject->m_PartyQuestInfo.m_siRewardItemAmount[i];
		siItemUseDay = pPartyObject->m_PartyQuestInfo.m_siRewardItemUseDay[i];

		SI32 ref = pServer->pclItemManager->FindItemRefFromUnique(siItemUnique);
		
		if (ref <= 0)	
			continue;

		if(siItemAmount <= 0)
			continue;

		// ����������� ���� ��Ƽ���� �������� ����.

		cltItem			clitem;
		ZeroMemory(&clitem, sizeof(clitem));
		clitem.siUnique  = siItemUnique;		
		clitem.siItemNum =	  siItemAmount;

		if(siItemUseDay <= 0)
			clitem.uiDateUseDay = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;
		else
			clitem.uiDateUseDay = siItemUseDay;


		pServer->InputItem(pclRewardChar, &clitem, INPUTITEMPERSON_OPTION_PARTYQUEST);
	}
}

bool CPartyQuestMgr_Server::IncreasePartyQuestCondition(SI32 siPartyIndex, SI32 siQuestType, SI32 siCondition, SI32 siAmount)
{
	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return false;

	// ���� �������� ����Ʈ Ÿ������ Ȯ�� �մϴ�.
	if(pPartyObject->m_PartyQuestInfo.m_siQuestType != siQuestType)
		return false;

	switch(siQuestType)
	{
	case PARTYQUEST_TYPE_NONE:
		break;

	case PARTYQUEST_TYPE_HUNTING:
		{
			if(pPartyObject->m_PartyQuestInfo.m_siCondition1 == siCondition)	// �����ϰ� �ִ� �������Ʈ�� MonsterKind�� ����� MonsterKind�� ������ üũ �մϴ�.
			{
				pPartyObject->m_PartyQuestInfo.m_siAmount += siAmount;			// �ش� ����Ʈ�� ���͸� ����ߴٸ� Amount�� ���� �����ݴϴ�.
				return true;
			}
		}
		break;

	case PARTYQUEST_TYPE_MAKEITEM:
		{
			if(pPartyObject->m_PartyQuestInfo.m_siCondition1 == siCondition)	// ����Ʈ���� �����������̶� ���� ������ �������� �������������� üũ �մϴ�.
			{
				pPartyObject->m_PartyQuestInfo.m_siAmount += siAmount;			// �������� ����Ʈ�������� �����ߴٸ� ī��Ʈ�� ���� ��ŵ�ϴ�.
				return true;
			}
		}
		break;

	default:
		break;
	}	

	// ������Ʈ �� ����Ʈ�� ���ٸ� return false
	return false;
}


// ��Ƽ����Ʈ ���� ���� ���� üũ
bool CPartyQuestMgr_Server::DoCheckPartyQuest(CPartyObj* pPartyObject)
{
	// �ش� ��Ƽ������ ��Ƽ����Ʈ�� �������� üũ �մϴ�.

	bool bResult = false;

	bResult = CheckAlreadyPartyQuest(pPartyObject);	// �̹� ��Ƽ ����Ʈ���ΰ�

	if(bResult == true)
		bResult = CheckPartyLeader(pPartyObject);		// ��Ƽ���� ��Ƽ��Ī�� �̿��ؼ� ��Ƽ���� �Ǿ��°�?

	if(bResult == true)
		bResult = CheckUserNum(pPartyObject);	// ��Ƽ������ �ο��� ����Ʈ ���ǿ� ���� �ϴ°�?

	if(bResult == true)
		bResult = CheckLevel(pPartyObject);		// ��Ƽ������ ������ ����Ʈ ���ǿ� ���� �ϴ°�?

	if(bResult == true)
		bResult = CheckPCRoom(pPartyObject);	// �ǽù� ����Ʈ ���� üũ

	return bResult;
}

bool CPartyQuestMgr_Server::CheckAlreadyPartyQuest(CPartyObj* pPartyObject)
{
	if(pPartyObject == NULL)
		return false;

	return !(pPartyObject->m_PartyQuestInfo.m_bGoingQuest);
}

// �ش� ��Ƽ�� ��Ƽ���� ��Ƽ��Ī �Ŵ����� ��� �Ǿ��ִ��� üũ
bool CPartyQuestMgr_Server::CheckPartyLeader(CPartyObj* pPartyObject)
{
	SI32 siResult = -1;

	siResult = pclClient->m_pServer_PartyMatchingMgr->Get_Category(pPartyObject->GetPartyLeaderUnique());

	if(siResult < 0)
		return false;

	return true;
}

bool CPartyQuestMgr_Server::CheckUserNum(CPartyObj* pPartyObject)
{
	SI32 siCategoryIndex = pclClient->m_pServer_PartyMatchingMgr->Get_Category(pPartyObject->GetPartyLeaderUnique());

	PartyQuest_CatecoryData*	pCategoryData	=	&m_PartyQuest_CategoryData[siCategoryIndex];

	if(pPartyObject->GetPartyUserNum() < pCategoryData->m_siMinUser || pPartyObject->GetPartyUserNum() > pCategoryData->m_siMaxUser)
		return false;

	return true;
}

bool CPartyQuestMgr_Server::CheckLevel(CPartyObj* pPartyObject)
{
	SI32 siCategoryIndex = pclClient->m_pServer_PartyMatchingMgr->Get_Category(pPartyObject->GetPartyLeaderUnique());
	PartyQuest_CatecoryData*	pCategoryData	=	&m_PartyQuest_CategoryData[siCategoryIndex];

	for(SI32 siIndex = 0; siIndex < MAX_PARTY_USER_NUM; siIndex++)
	{
		SI32 siCharUnique = pPartyObject->GetPartyUser(siIndex)->siCharUnique;

		if ( pclClient->pclCM->IsValidID(siCharUnique) == false )
			continue;

		cltCharCommon* pCharacter = pclClient->pclCM->GetChar(siCharUnique);
		SI32 siLevel = pCharacter->pclCI->clIP.GetLevel();

		// ��Ƽ������ ������ ����Ʈ ���ǿ� ���� �ϴ°�?
		if(siLevel < pCategoryData->m_siMinLevel || siLevel > pCategoryData->m_siMaxLevel)
			return false;
	}

	return true;
}

bool CPartyQuestMgr_Server::CheckPCRoom(CPartyObj* pPartyObject)
{
	SI32 siCategoryIndex = pclClient->m_pServer_PartyMatchingMgr->Get_Category(pPartyObject->GetPartyLeaderUnique());

	PartyQuest_CatecoryData*	pCategoryData	=	&m_PartyQuest_CategoryData[siCategoryIndex];

	for(SI32 siIndex = 0; siIndex < MAX_PARTY_USER_NUM; siIndex++)
	{
		SI32 siCharUnique = pPartyObject->GetPartyUser(siIndex)->siCharUnique;

		if ( pclClient->pclCM->IsValidID(siCharUnique) == false )
			continue;

		cltCharCommon* pCharacter = pclClient->pclCM->GetChar(siCharUnique);

		// �Ϸ��� ����Ʈ�� PC�� ���� ����Ʈ �ΰ�?
		if(pCategoryData->m_siKind == PARTYQUEST_KIND_PCROOM )
		{
			if(pCharacter->pclCI->clBI.bPCRoom == false)
				return false;
		}
	}

	return true;
}


// ��Ƽ����Ʈ ����� 
bool CPartyQuestMgr_Server::DoGiveUpPartyQuest(SI32 siPartyIndex, SI32 siLeaveCharID, SI32 siMessage)
{
	cltServer* pServer = (cltServer*)pclClient;

	CPartyObj* pPartyObject = pclClient->pclPartyMgr->GetPartyObj(siPartyIndex);
	if(pPartyObject == NULL)
		return false;	

	PartyQuest_UnitData* pQuestData = &pPartyObject->m_PartyQuestInfo;

	if(pQuestData == NULL || pQuestData->m_bGoingQuest == false)
		return false;

	ZeroMemory(pQuestData, sizeof(PartyQuest_UnitData));

	pPartyObject->m_dwStartTime	 = 0;
	pPartyObject->m_dwElapseTime = 0;
	pPartyObject->m_dwEndTime	 = 0;

	cltGameMsgResponse_PartyQuest_GiveUp clInfo(siMessage);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_GIVEUP, sizeof(clInfo), (BYTE*)&clInfo);
	pServer->pclCM->SendAllPartyMemberMsg((sPacketHeader*)&clMsg, siPartyIndex);		



	cltCharServer* pclChar = pServer->pclCM->GetCharServer( siLeaveCharID );
	if ( NULL == pclChar )
		return false;

	cltGameMsgResponse_PartyQuest_GiveUp clInfo2(siMessage);
	cltMsg clMsg2(GAMEMSG_RESPONSE_PARTY_QUEST_GIVEUP, sizeof(clInfo2), (BYTE*)&clInfo2);
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg2);

	return true;
}

void CPartyQuestMgr_Server::UpdatePartyQuestTime(SI32 siPartyIndex,  PartyQuest_UnitData* pPartyQuestData)
{
	cltServer* pServer = (cltServer*)pclClient;

	if(pPartyQuestData == NULL)
		return;

	if(siPartyIndex <= 0)
		return;


	CPartyObj* pPartyObject = pServer->pclPartyMgr->GetPartyObj(siPartyIndex);
	
	if(pPartyObject == NULL)
		return;
	

	DWORD dwQuestTime = (TABS(pPartyObject->m_dwEndTime) - TABS(pclClient->CurrentClock)) / 1000; // per second
	cltGameMsgResponse_PartyQuest_Update clInfo(false, pPartyQuestData, dwQuestTime);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_QUEST_UPDATE, sizeof(clInfo), (BYTE*)&clInfo);
	pServer->pclCM->SendAllPartyMemberMsg((sPacketHeader*)&clMsg, siPartyIndex);	
}




