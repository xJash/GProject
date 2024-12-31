// ��Ƽ��Ī
#include "Client_PartyMatchingMgr.h"
#include "../../commonlogic/msg/MsgType-PartyMatching.h"
#include "../../CommonLogic/PartyMatchingMgr/Defines_PartyMatchingMgr.h"
#include "../../CommonLogic/PartyQuestMgr/PartyQuestMgr_Common.h"

#include "../../Client/InterfaceMgr/DialogController.h"
#include "../../Client/ninterface/NPartyQuest_PartyMatchingDlg/NPartyMatching_ApplytoPartyDlg.h"
#include "../../Client/ninterface/NPartyQuest_PartyMatchingDlg/NPartyMatching_CreatePartyDlg.h"

#include "../../Client/Client.h"

#include "../../commonlogic/msgtype.h"
#include "../../CommonLogic/Msg/MsgType-Party.h"






CClient_PartyMatchingMgr::CClient_PartyMatchingMgr()
{
	m_PartyList.RemoveAll();

	m_siSelectedCategory = -1;
	m_siSelectedMission = -1;
}

CClient_PartyMatchingMgr::~CClient_PartyMatchingMgr()
{
	m_PartyList.RemoveAll();
}

void CClient_PartyMatchingMgr::Click_PartyMatchingNPC()
{
	cltClient* pClient = (cltClient*)pclClient;

	if(pClient)
	{
		// ��Ƽ ����Ʈ ���� ��ȭ���� ���
		if(pClient->m_pDialog[NSELECT_QUEST_BASE_DLG] == NULL )
		{
			pClient->CreateInterface( NSELECT_QUEST_BASE_DLG );
		}
	}
}

void CClient_PartyMatchingMgr::Click_DestroyDlgButton()
{
	cltClient* pClient = (cltClient*)pclClient;

	if(pClient)
	{
		// ��Ƽ ����Ʈ ���� ��ȭ���� ���
		if (pClient->m_pDialog[NSELECT_QUEST_BASE_DLG] != NULL)
		{
			pClient->m_pDialog[NSELECT_QUEST_BASE_DLG]->DeleteDialog();
		}
	}	
}

void CClient_PartyMatchingMgr::Click_CategoryButton(SI16 siIndex)
{
	// ����ó��
	if ( 0 > siIndex || MAX_PARTYQUEST_CATEGORY_NUM <= siIndex ) return;
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;
	cltCharClient* pclCharClient = pclClient->pclCM->GetCharClient(1);
	if ( NULL == pclCharClient ) return;
	if ( NULL == pClient->m_pPartyQuestMgr ) return;
	PartyQuest_CatecoryData* pCategoryData = NULL;
	pCategoryData = ((CPartyQuestMgr_Common*)pClient->m_pPartyQuestMgr)->GetPartyQuestCategoryData( siIndex );
	if ( NULL == pCategoryData ) return;
	//------------------------------------------------------------------------------------------------------

	// ���� �۾� ó��
	const SI16 siCharLevel = pclCharClient->pclCI->clIP.GetLevel();

	if ( PARTYQUEST_KIND_PCROOM == pCategoryData->m_siKind )
	{
		if ( true != pclCharClient->pclCI->clBI.bPCRoom )
		{
			TCHAR*	pTitle	= GetTxtFromMgr(512);	// ����
			TCHAR*	pBody	= GetTxtFromMgr(40395); // �ش� ����Ʈ�� PC�� ������ ���� �� �� �ִ� ����Ʈ �Դϴ�.
			pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

			return;
		}
	}

	if ( siCharLevel >= pCategoryData->m_siMinLevel && siCharLevel <= pCategoryData->m_siMaxLevel )
	{
		// ��Ƽ ����Ʈ ���� ��ȭ���� ���
		if (pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG] == NULL)
		{
			pClient->CreateInterface( NPARTY_MATCHING_BASE_DLG );
		}

		// ����Ʈ ����Ʈ ��ȭ���ڸ� �ݴ´�.
		if (pClient->m_pDialog[NSELECT_QUEST_BASE_DLG] != NULL)
		{
			pClient->m_pDialog[NSELECT_QUEST_BASE_DLG]->DeleteDialog();
		}

		// ������ ī�װ�(����Ʈ �׷� �ε���)�� �����Ѵ�.
		((CNApplytoParty_PartyMatching*)(pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG]))->siTempCategory = siIndex;

		MsgProcess_Request_PartyMatchingList( siIndex );
	}
	else // ������ ���� ������ 
	{
		NTCHARString256 strTitle = GetTxtFromMgr(512);	// ����
		NTCHARString256 strText = GetTxtFromMgr(40394); // �ش� ����Ʈ�� #level# ������ ������ ���� �� �� �ִ� ����Ʈ �Դϴ�.
		NTCHARString32 strLevel;
		strLevel = SI16ToString( pCategoryData->m_siMinLevel );
		strLevel = strLevel + TEXT("~");
		strLevel = strLevel + ((TCHAR*)(SI16ToString( pCategoryData->m_siMaxLevel )));
		strText.Replace( TEXT("#level#"), strLevel );

		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText( strTitle, strText );
	}
}

void CClient_PartyMatchingMgr::Click_PartyEnterRequestButton(SI16 siSelectedIndex)
{
	// 1. ��û�Ϸ��� �ڽ��� ��Ƽ�� ���� �������� üũ
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	cltCharClient* pCharClient = (cltCharClient*)pClient->pclCM->GetCharClient(1);
	if ( NULL == pCharClient ) return;

	SI32 siIndex = -1;
	siIndex = AlreadyExist( pCharClient->GetCharUnique() );

	if ( 0 <= siIndex )
	{
		// ��Ƽ��Ī�� ����� ���¿����� �ٸ� ��Ƽ��Ī�� �����Ҽ� ����.
		TCHAR* pTitle = GetTxtFromMgr( 512 );		// ����
		TCHAR* pBody = GetTxtFromMgr( 40798 );		// ��Ƽ��Ī�� ����� ���¿����� �ٸ� ��Ƽ��Ī�� �����Ҽ� �����ϴ�.
		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);
		return;
	}

	// 2. ������ �ش� ��Ƽ�� ������ �ϰ� �ʹٴ� ��Ŷ�� ����
	MsgProcess_Request_JoinPartyMatching( siSelectedIndex );
}

void CClient_PartyMatchingMgr::Click_WhisperButton(SI16 siSelectedIndex)
{
	if ( 0 > siSelectedIndex || m_PartyList.GetCount() <= (unsigned int)siSelectedIndex ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	if ( 0 > m_PartyList[siSelectedIndex].m_siLeaderID ) return;
	cltCharClient* pCharClient = (cltCharClient*)pClient->pclCM->GetCharClient( 1 );

	SI32 siMyCharUnique = pCharClient->GetCharUnique();
	if ( m_PartyList[siSelectedIndex].m_siLeaderID == siMyCharUnique ) return;

	if ( false == m_PartyList[siSelectedIndex].m_strLeaderName.IsEmpty() && _tcslen( m_PartyList[siSelectedIndex].m_strLeaderName ) > 0 )
	{
		pClient->RequestSecretChatByCharUnique( m_PartyList[siSelectedIndex].m_siLeaderID );
	}
}

void CClient_PartyMatchingMgr::Click_PartyMakeButton(SI16 siTmpCate)
{
	// NCREATE_PARTY_BASE_DLG
	cltClient* pClient = (cltClient*)pclClient;
	if ( 0 > siTmpCate ) return;

	if( NULL != pClient )
	{
		// ��Ƽ ����Ʈ ���� ��ȭ���� ���
		if(pClient->m_pDialog[NCREATE_PARTY_BASE_DLG] == NULL )
		{
			pClient->CreateInterface( NCREATE_PARTY_BASE_DLG );

			((CNCreatePartyDlg*)(pClient->m_pDialog[NCREATE_PARTY_BASE_DLG]))->siTempCategory = siTmpCate;
			((CNCreatePartyDlg*)(pClient->m_pDialog[NCREATE_PARTY_BASE_DLG]))->Init();
		}
	}
}

void CClient_PartyMatchingMgr::Click_PartyMakeButton2() // ��Ƽ�����â���� ��Ƽ �����.
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	CNCreatePartyDlg* pDlg = (CNCreatePartyDlg*)pClient->m_pDialog[NCREATE_PARTY_BASE_DLG];
	if ( NULL == pDlg ) return;

	CNApplytoParty_PartyMatching* pListDlg = (CNApplytoParty_PartyMatching*)pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG];
	if ( NULL == pListDlg ) return;

	CInfo_PartyMatching questInfo;

	// ��Ƽ���� ���� ��Ƽ ����� ���� ������ �´��� üũ �Ѵ�.
	if ( false == Get_Info_PartyMemberInfo( questInfo ) )
	{
		// ���ǿ� ���� ���� ���.
		cltClient* pClient = (cltClient*)pclClient;

		TCHAR* pTitle = GetTxtFromMgr(512);		// ����
		TCHAR* pBody = GetTxtFromMgr(40426);	// ��Ƽ�� ���Ե� ���¿����� ��Ƽ ����Ⱑ �Ұ��� �մϴ�.

		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText( pTitle, pBody );

		return;
	}

	// ��ȭ���ڿ� �Էµ� �����Ϸ��� ����Ʈ �������� ���� ��Ƽ��Ī ������ �ִ´�.
	if ( false == pDlg->Get_Info_PartyMatchingCreate( questInfo ) )
	{
		// ���⼱ �ƹ� ó���� ����
		return;
	}

	// ��Ī ���� ��û �϶�� ������ ��Ŷ ����
	MsgProcess_Request_CreatePartyMatching( questInfo );
}

bool CClient_PartyMatchingMgr::Get_Info_PartyMemberInfo(CInfo_PartyMatching& rInfo)
{
	// ��Ƽ ����� ���� ������ üũ �ϰ� ��Ƽ ����� ������ ��Ƽ��Ī ������ �ִ´�.
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return false;

	// 1. ������ �ٸ� ��Ƽ�� ���ԵǾ� �ִٸ�
	cltCharClient* pclCharClient = pClient->pclCM->GetCharClient(1);
	if( NULL == pclCharClient ) return false;

	// ���������� ���� ������ ��Ƽ ����� ���� ������ ����
	rInfo.m_siLeaderID = pclCharClient->GetCharUnique();
	rInfo.m_strLeaderName = pclCharClient->GetName();

	return true;
}

void CClient_PartyMatchingMgr::Set_Category(SI32 siCategory)
{
	if ( 0 > siCategory || MAX_PARTYQUEST_CATEGORY_NUM <= siCategory ) return;

	m_siSelectedCategory = siCategory;
}

void CClient_PartyMatchingMgr::Set_Mission(SI32 siMission)
{
	if ( 0 > siMission || MAX_PARTYQUEST_MISSION_NUM <= siMission ) return;

	m_siSelectedMission = siMission;
}

SI32 CClient_PartyMatchingMgr::Get_Category()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return -1;

	SI32 siCount = 0;
	siCount = m_PartyList.GetCount();

	for ( SI16 i = 0; i < siCount; ++i)
	{
		if ( 0 >= m_PartyList[i].m_siLeaderID ) continue;
		cltCharClient* pCharClient = (cltCharClient*)pClient->pclCM->GetCharClient( 1 );

		SI32 siMyCharUnique = pCharClient->GetCharUnique();
		if ( m_PartyList[i].m_siLeaderID == siMyCharUnique ) return m_PartyList[i].m_siParentQuest;
	}

	return -1;
}

SI32 CClient_PartyMatchingMgr::Get_Mission()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return -1;

	SI32 siCount = 0;
	siCount = m_PartyList.GetCount();

	for ( SI16 i = 0; i < siCount; ++i)
	{
		if ( 0 >= m_PartyList[i].m_siLeaderID ) continue;
		cltCharClient* pCharClient = (cltCharClient*)pClient->pclCM->GetCharClient( 1 );

		SI32 siMyCharUnique = pCharClient->GetCharUnique();
		if ( m_PartyList[i].m_siLeaderID == siMyCharUnique ) return m_PartyList[i].m_siChildQuest;
	}

	return -1;
}

void CClient_PartyMatchingMgr::Action()
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	// ��Ƽ��Ī ����Ʈ ��ȭ������ ��Ŷ ������ ��ư�鿡 ���� ��Ÿ ����
	CNApplytoParty_PartyMatching* pListDlg = (CNApplytoParty_PartyMatching*)pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG];
	if ( NULL != pListDlg )
	{
		if ( true == pListDlg->bPacketSended )
		{
			if ( pClient->CurrentClock > pListDlg->dwPacketBlockTime )
			{
				pListDlg->bPacketSended = false;
				pListDlg->pJoinRequest->Enable( true );
				pListDlg->pJoinRequest->Refresh();
			}
		}
	}
}

CInfo_PartyMatching* CClient_PartyMatchingMgr::Get_PartyMatchingInfo(SI16 siSelectedIndex)
{
	if ( 0 > siSelectedIndex || m_PartyList.GetCount() <= (unsigned int)siSelectedIndex ) return NULL;

	return &m_PartyList[siSelectedIndex];
}

SI32 CClient_PartyMatchingMgr::AlreadyExist(SI32 siMyCharUnique)
{
	unsigned int iCount = m_PartyList.GetCount();
	for ( unsigned int i = 0; i < iCount; ++i )
	{
		if ( siMyCharUnique == m_PartyList[i].m_siLeaderID )
		{
			return (SI32)i;
		}
	}

	return -1;
}


//---------------------------------------------------------------------------------------------------------
// ��Ŷ ó���ϴ� �Լ���
//---------------------------------------------------------------------------------------------------------

//-- Request

// ���ο� ��Ƽ��Ī�� �����ϰ� �ʹٰ� ������ ��Ŷ ����
void CClient_PartyMatchingMgr::MsgProcess_Request_CreatePartyMatching(CInfo_PartyMatching& rInfo)
{
	if( false == rInfo.CheckCondition() ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	CNCreatePartyDlg* pDlg = (CNCreatePartyDlg*)pClient->m_pDialog[NCREATE_PARTY_BASE_DLG];
	if ( NULL == pDlg ) return;

	pDlg->DeleteDialog();

	if ( true == pDlg->bPacketSended ) return;

	cltGameRequest_PartyMatchingCreate clinfo(rInfo);
	cltMsg clMsg( GAMEMSG_REQUEST_CREATECOMPLETEPARTY, sizeof(clinfo), (BYTE*)&clinfo );
	pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );

	if ( NULL != pDlg ) pDlg->bPacketSended = true;
}

// ��Ƽ�� �����ϰ� �ʹٴ� ��û
void CClient_PartyMatchingMgr::MsgProcess_Request_JoinPartyMatching(SI16 siSelectedIndex)
{
	// ������ ��û
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	if ( 0 > siSelectedIndex || m_PartyList.GetCount() <= (unsigned int)siSelectedIndex ) return;

	if ( 0 > m_PartyList[siSelectedIndex].m_siLeaderID ) return;

	cltCharClient* pLeaderChar = (cltCharClient*)pClient->pclCM->CR[m_PartyList[siSelectedIndex].m_siLeaderID];
	if ( NULL == pLeaderChar ) return;

	SI32 siLeaderUnique = m_PartyList[siSelectedIndex].m_siLeaderID;
	if ( 0 >= siLeaderUnique ) return;

	cltCharClient* pMemberChar = (cltCharClient*)pClient->pclCM->GetCharClient( 1 );
	if ( NULL == pMemberChar ) return;

	SI32 siMemberUnique = pMemberChar->GetCharUnique();
	if ( 0 >= siMemberUnique ) return;

	NTCHARString16 strMemberName( pMemberChar->GetName() );
	if ( true == strMemberName.IsEmpty() ) return;

	CNApplytoParty_PartyMatching* pDlg = (CNApplytoParty_PartyMatching*)pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG];
	if ( NULL == pDlg ) return;

	cltGameMsgRequest_Party_WantJoin clMsgInfo( siLeaderUnique, siMemberUnique, (TCHAR*)strMemberName );
	cltMsg clMsg( GAMEMSG_REQUEST_PARTY_WANTJOIN, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
	pclClient->SendMsgToServer( (sPacketHeader*)&clMsg );

	pDlg->bPacketSended = true;
	pDlg->dwPacketBlockTime = pClient->CurrentClock + 3000;
	pDlg->pJoinRequest->Enable( false );
	pDlg->pJoinRequest->Refresh();
}

//-- Response

// ��Ƽ��Ī ����Ʈ ��û�� ���� ���� ��Ŷ ó��
void CClient_PartyMatchingMgr::MsgProcess_Response_PartyMatchingLevel(SI32 siCharID, cltGameResponse_PartyMatchingLevel* pInfo)
{
	if ( NULL == pInfo ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	if ( NULL == pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG] )
	{
		pClient->CreateInterface( NPARTY_MATCHING_BASE_DLG );
	}

	CNApplytoParty_PartyMatching* pDlg = (CNApplytoParty_PartyMatching*)pClient->m_pDialog[NPARTY_MATCHING_BASE_DLG];
	if ( NULL == pDlg ) return;

	if ( true == pInfo->bNeedClearOldList )
	{
		m_PartyList.RemoveAll();
		pDlg->Clear_Controls();
	}

	for ( SI16 i = 0; i < MAX_PARTYMATCHING_LIST_SEND_SIZE; ++i )
	{
		if ( 0 >= pInfo->m_PartyMatchingList[i].m_siLeaderID ) continue;	// ���� ���̵� 0���� �۰ų� ���� ���� ���Դٴ°� �߸��� ������� ��.

		pDlg->AddListItem_PartyMatchingView( &(pInfo->m_PartyMatchingList[i]) );
		m_PartyList.PushBack( pInfo->m_PartyMatchingList[i] );
	}
}

// ��Ƽ��Ī ���� ����� ��û�� ���� ����
void CClient_PartyMatchingMgr::MsgProcess_Response_PartyMatchingCreate(SI32 siCharID, bool bResult)
{
	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	TCHAR* pTitle = NULL;
	TCHAR* pBody = NULL;

	if ( true == bResult )
	{
		pTitle = GetTxtFromMgr( 389 );		// ����
		pBody = GetTxtFromMgr( 40780 );		// ��Ƽ ����Ⱑ ���������� �̷�������ϴ�.

		// ��Ƽ ���� ��ȭ���ڰ� ��������� �ݾ��ش�.
		if( pClient->m_pDialog[NCREATE_PARTY_BASE_DLG] != NULL )
		{
			pClient->m_pDialog[NCREATE_PARTY_BASE_DLG]->DeleteDialog();
		}
	}
	else
	{
		pTitle = GetTxtFromMgr( 512 );		// ����
		pBody = GetTxtFromMgr( 40782 );		// �˼����� ������ ����� �����߾��. ��� //��Ƽ�� ���Ե� ���¿����� ��Ƽ ���� ��û�� �Ұ����մϴ�.
	}

	pClient->m_pDialog[NOTIFYMSG_DLG]->SetText( pTitle, pBody );
}

// ��Ƽ�� �����ϰ� �ʹٴ� ��û�� ���� ���� (��� ���Ҽ��� ����)
void CClient_PartyMatchingMgr::MsgProcess_Response_PartyMatchingJoin()
{
}

// ������ �ش� ī�װ��� ��Ƽ��Ī ����Ʈ�� �޶�� ��û�Ѵ�.
void CClient_PartyMatchingMgr::MsgProcess_Request_PartyMatchingList(SI16 siCategory)
{
	if ( 0 > siCategory || MAX_PARTYQUEST_CATEGORY_NUM <= siCategory ) return;
	if ( NULL == pclClient ) return;
	if ( NULL == pclClient->pclCM ) return;
	cltCharClient* pMyChar = (cltCharClient*)pclClient->pclCM->GetCharClient( 1 );
	if ( NULL == pMyChar ) return;

	cltGameRequest_PartyMatchingLevel clinfo( pMyChar->pclCI->GetPersonID(), siCategory );
	cltMsg clMsg(GAMEMSG_REQUEST_PARTYMATCHING_LEVEL, sizeof(clinfo), (BYTE*)&clinfo);
	pclClient->SendMsgToServer((sPacketHeader*)&clMsg);
}