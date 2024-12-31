#include "PartyQuestMgr_Client.h"

#include "Char/CharManager/CharManager.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../Lib/dxutil.h"
#include "../../Client/Client.h"

#include "../../client/InterfaceMgr/InterfaceFile.h"
#include "../../client/InterfaceMgr/InterfaceMgr.h"


#include "../../client/ninterface/npartydlg/NPartyDlg.h"
#include "../../CommonLogic/PartyMatchingMgr/Client_PartyMatchingMgr.h"

extern cltCommonLogic* pclClient;

CPartyQuestMgr_Client::CPartyQuestMgr_Client()
{
	ZeroMemory(this, sizeof(CPartyQuestMgr_Client));
}

CPartyQuestMgr_Client::~CPartyQuestMgr_Client()
{
	
}


bool CPartyQuestMgr_Client::Initialize()
{
	bool bResult = false;
	
	CPartyQuestMgr_Common::LoadFiles_PartyQuest();

	return bResult;
}


// ��Ƽ����Ʈ ���� ���� ���� üũ
bool CPartyQuestMgr_Client::DoCheckPartyQuest(SI32 siPartyUserNum, stClientPartyUser ClientPartyUser[])
{
	// �ش� ��Ƽ������ ��Ƽ����Ʈ�� �������� üũ �մϴ�.

	bool bResult = false;

	bResult = CheckAlreadyPartyQuest();				// �̹� ����Ʈ ���ΰ�

	if(bResult == true)
		bResult = CheckPartyLeader();				// ��Ƽ���� ��Ƽ��Ī�� �̿��ؼ� ��Ƽ���� �Ǿ��°�?

	if(bResult == true)
		bResult = CheckUserNum(siPartyUserNum);		// ��Ƽ������ �ο��� ����Ʈ ���ǿ� ���� �ϴ°�?

	if(bResult == true)
		bResult = CheckLevel(ClientPartyUser);		// ��Ƽ������ ������ ����Ʈ ���ǿ� ���� �ϴ°�?

	return bResult;
}

bool CPartyQuestMgr_Client::CheckAlreadyPartyQuest()
{
	if(m_PartyQuestData.m_bGoingQuest == false)
		return true;
	else
		return true;

}
// �ش� ��Ƽ�� ��Ƽ���� ��Ƽ��Ī �Ŵ����� ��� �Ǿ��ִ��� üũ
bool CPartyQuestMgr_Client::CheckPartyLeader()
{
	cltClient* pClient = (cltClient*)pclClient;
	CNPartyDlg* pDlg = (CNPartyDlg*)pClient->m_pDialog[NPARTY_DLG];

	if ( NULL == pDlg ) return false;
	if ( false == pDlg->m_bIsPartyLeader ) return false;
	if ( false == pDlg->m_bIsPartyQuestParty) return false;
	if ( 0 > pDlg->m_siCategory ) return false;

	return true;
}

bool CPartyQuestMgr_Client::CheckUserNum(SI32 siPartyUserNum)
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( false == CheckPartyLeader() ) return false;

	CNPartyDlg* pDlg = (CNPartyDlg*)pClient->m_pDialog[NPARTY_DLG];
	if ( NULL == pDlg ) return false;

	// ī�װ� �ε����� �ʱⰪ�� -1�� ���� : ��Ƽ����Ʈ �Ŵ����� ���ҽ��� �迭�� �о�鿴�� ������ 0�� �ǹ� �ִ� ���̹Ƿ� �ʱⰪ���� ������� ����. �ʱⰪ�� -1�� ���� �迭 ���� ����� ���� �߻����� �ʵ��� ����ó�� �� ����� ��.
	SI32 siCategoryIndex = pDlg->m_siCategory;

	if(siCategoryIndex < 0 || siCategoryIndex >= MAX_PARTYQUEST_CATEGORY_NUM)
		return false;

	PartyQuest_CatecoryData* pCategoryData	=	&m_PartyQuest_CategoryData[siCategoryIndex];

	if(siPartyUserNum < pCategoryData->m_siMinUser || siPartyUserNum > pCategoryData->m_siMaxUser)
		return false;

	return true;
}

bool CPartyQuestMgr_Client::CheckLevel(stClientPartyUser ClientPartyUser[])
{
	cltClient* pClient = (cltClient*)pclClient;

	if ( false == CheckPartyLeader() ) return false;

	CNPartyDlg* pDlg = (CNPartyDlg*)pClient->m_pDialog[NPARTY_DLG];
	if ( NULL == pDlg ) return false;

	SI32 siCategoryIndex = pDlg->m_siCategory;

	PartyQuest_CatecoryData*	pCategoryData	=	&m_PartyQuest_CategoryData[siCategoryIndex];

	for(SI32 siIndex = 0; siIndex < MAX_PARTY_USER_NUM; siIndex++)
	{
		SI32 siLevel = 0;

		if(ClientPartyUser[siIndex].bPartyStatus == true)
		{
			siLevel = ClientPartyUser[siIndex].siLevel;

			// ��Ƽ������ ������ ����Ʈ ���ǿ� ���� �ϴ°�?
			if(siLevel < pCategoryData->m_siMinLevel || siLevel > pCategoryData->m_siMaxLevel)
				return false;
		}
	}

	return true;
}

// ��Ƽ����Ʈ ������ ����
void CPartyQuestMgr_Client::StartPartyQuestData(PartyQuest_UnitData* PartyQuestData)
{
	if(PartyQuestData == NULL)
		return;

	// ��Ƽ����Ʈ ������ ����
	CopyMemory(&m_PartyQuestData, PartyQuestData, sizeof(PartyQuest_UnitData));
	m_PartyQuestData.m_bGoingQuest = true;
	
	// ����Ʈ ������ ȭ�鿡 ��� �մϴ�.
	UpdatePartyInfoMsg(PartyQuestData, m_PartyQuestData.m_siTimeLimit,false);
}

// ��Ƽ����Ʈ ������ ����
void CPartyQuestMgr_Client::UpdatePartyQuestData(PartyQuest_UnitData* PartyQuestData, DWORD dwQuestTime, bool bClear)
{
	if(PartyQuestData == NULL)
		return;

	// ��Ƽ����Ʈ ������ ����
	if(bClear == false)
	{
		CopyMemory(&m_PartyQuestData, PartyQuestData, sizeof(PartyQuest_UnitData));

		// ����Ʈ ������ ȭ�鿡 ��� �մϴ�.
		UpdatePartyInfoMsg(PartyQuestData, dwQuestTime, bClear);
	}
	else
	{
		// ����Ʈ ������ ȭ�鿡 ��� �մϴ�.
		UpdatePartyInfoMsg(&m_PartyQuestData, dwQuestTime, true);

		CopyMemory(&m_PartyQuestData, PartyQuestData, sizeof(PartyQuest_UnitData));

		UpdatePartyInfoMsg(PartyQuestData, dwQuestTime, false);
	}
}

void CPartyQuestMgr_Client::UpdatePartyInfoMsg(PartyQuest_UnitData* PartyQuestData, DWORD dwQuestTime, bool bClear)
{
	if(PartyQuestData == NULL)
		return;

	TCHAR szObject[MAX_KIND_NAME_LENGTH] = "";

	switch(PartyQuestData->m_siQuestType)
	{
	case PARTYQUEST_TYPE_HUNTING:
		{
			StringCchCopy(szObject, MAX_KIND_NAME_LENGTH, pclClient->pclKindInfoSet->pclKI[m_PartyQuestData.m_siCondition1]->GetName());

			TCHAR szQuestStep[256] = "";
			itoa(m_PartyQuestData.m_siQuestStep+1, szQuestStep, 10);

			if(bClear == true)
				m_PartyQuestData.m_siAmount = CPartyQuestMgr_Common::GetPartyQuestUnitData(m_PartyQuestData.m_siCategoryIndex, m_PartyQuestData.m_siMissionIndex, m_PartyQuestData.m_siQuestStep)->m_siAmount;

			TCHAR szCurAmount[256] = "";
			itoa(m_PartyQuestData.m_siAmount, szCurAmount, 10);

			TCHAR szMaxAmount[256] = "";
			itoa(CPartyQuestMgr_Common::GetPartyQuestUnitData(m_PartyQuestData.m_siCategoryIndex, m_PartyQuestData.m_siMissionIndex, m_PartyQuestData.m_siQuestStep)->m_siAmount, szMaxAmount, 10);

			TCHAR szTime[256] = "";
			itoa(dwQuestTime ,szTime, 10);

			NTCHARString256	szQuestInfo(GetTxtFromMgr(40790));
			szQuestInfo.Replace("#index#", szQuestStep);
			szQuestInfo.Replace("#monster#", szObject);
			szQuestInfo.Replace("#cur#", szCurAmount);
			szQuestInfo.Replace("#max#", szMaxAmount);
			szQuestInfo.Replace("#time#", szTime);

		
			if(bClear == true)
			{
				szQuestInfo+=GetTxtFromMgr(TEXT(6141)); // [�Ϸ�]
				ZeroMemory(m_szQuestInfoForDlg, sizeof(m_szQuestInfoForDlg));
			}
			else
			{
				ZeroMemory(m_szQuestInfoForDlg, sizeof(m_szQuestInfoForDlg));
				StringCchCopy(m_szQuestInfoForDlg, sizeof(szQuestInfo), szQuestInfo);
			}

			pclClient->pclMessage->SetPartyQuestGameModeMsg(szQuestInfo, bClear);
		}
		break;

	case PARTYQUEST_TYPE_MAKEITEM:
		{
			StringCchCopy(szObject, MAX_ITEM_NAME_LENGTH, pclClient->pclItemManager->GetName(m_PartyQuestData.m_siCondition1));

			TCHAR szQuestStep[256] = "";
			itoa(m_PartyQuestData.m_siQuestStep+1, szQuestStep, 10);

			if(bClear == true)
				m_PartyQuestData.m_siAmount = CPartyQuestMgr_Common::GetPartyQuestUnitData(m_PartyQuestData.m_siCategoryIndex, m_PartyQuestData.m_siMissionIndex, m_PartyQuestData.m_siQuestStep)->m_siAmount;

			TCHAR szCurAmount[256] = "";
			itoa(m_PartyQuestData.m_siAmount, szCurAmount, 10);

			TCHAR szMaxAmount[256] = "";
			itoa(CPartyQuestMgr_Common::GetPartyQuestUnitData(m_PartyQuestData.m_siCategoryIndex, m_PartyQuestData.m_siMissionIndex, m_PartyQuestData.m_siQuestStep)->m_siAmount, szMaxAmount, 10);

			TCHAR szTime[256] = "";
			itoa(dwQuestTime, szTime, 10);

			NTCHARString256	szQuestInfo(GetTxtFromMgr(40799));
			szQuestInfo.Replace("#index#", szQuestStep);
			szQuestInfo.Replace("#item#", szObject);
			szQuestInfo.Replace("#cur#", szCurAmount);
			szQuestInfo.Replace("#max#", szMaxAmount);
			szQuestInfo.Replace("#time#", szTime);

			if(bClear == true)
			{
				szQuestInfo+=GetTxtFromMgr(TEXT(6141)); // [�Ϸ�]
				ZeroMemory(m_szQuestInfoForDlg, sizeof(m_szQuestInfoForDlg));
			}
			else
			{
				ZeroMemory(m_szQuestInfoForDlg, sizeof(m_szQuestInfoForDlg));
				StringCchCopy(m_szQuestInfoForDlg, sizeof(szQuestInfo), szQuestInfo);
			}

			pclClient->pclMessage->SetPartyQuestGameModeMsg(szQuestInfo, bClear);
		}
		break;
	
	}
}

void CPartyQuestMgr_Client::DoGiveUpPartyQuest()
{
	ZeroMemory(&m_PartyQuestData, sizeof(PartyQuest_UnitData));
	ZeroMemory(m_szQuestInfoForDlg, sizeof(m_szQuestInfoForDlg));
}	

