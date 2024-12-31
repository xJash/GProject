// ��Ƽ��Ī
#include "../Client.h"
#include "../Music\Music.h"
#include "../CommonLogic/MsgType.h"

#include "Char/CharClient/Char-Client.h"
#include "Char/CharManager/CharManager.h"

#include "../Interface/ErrorMsgDlg/ErrorMsgDlg.h"
#include "../Interface/NotifyMsgDlg/NotifyMsgDlg.h"

#include "../../CommonLogic/Msg/MsgType-PartyMatching.h"

#include "../../CommonLogic/PartyMatchingMgr/Client_PartyMatchingMgr.h"
#include "../../Client/ninterface/NPartyQuest_PartyMatchingDlg/NPartyMatching_ApplytoPartyDlg.h"





// ���ܻ�Ȳ�� ���� ó��
void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_PartyMatchingException* pRcvInfo = (cltGameResponse_PartyMatchingException*)pclMsg->cData;
	if ( NULL == pRcvInfo ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;

	// ���ܿ� ���� ó����
	if ( PARTYMATCHING_ALREADY_PARTYMEMBER & pRcvInfo->siExceptionFlags )
	{
		TCHAR* pTitle = GetTxtFromMgr( 512 );		// ����
		TCHAR* pBody = GetTxtFromMgr( 40782 );		// ��Ƽ�� ���ԵǾ� �ִ� ���¿��� �Ҽ� �����ϴ�.
		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

		return;		// �ϳ��� �˸� ��ȭâ�� ������ �̿������� ��ȭ���ڰ� ���� �ٸ��� ����ϴ� ���ܻ�Ȳ�϶� return �Ƚ��ѵ� ��.
	}

	if ( PARTYMATCHING_WRONG_LEVELCONDITION & pRcvInfo->siExceptionFlags )
	{
		TCHAR* pTitle = GetTxtFromMgr( 512 );		// ����
		TCHAR* pBody = GetTxtFromMgr( 40782 );		// ���� ������ �������� �ʽ��ϴ�.
		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

		return;
	}

	if ( PARTYMATCHING_WRONG_CHARID & pRcvInfo->siExceptionFlags )
	{
		TCHAR* pTitle = GetTxtFromMgr( 512 );		// ����
		TCHAR* pBody = GetTxtFromMgr( 40782 );		// �ش� ĳ���͸� ã������ �����ϴ�.
		pClient->m_pDialog[NOTIFYMSG_DLG]->SetText(pTitle, pBody);

		return;
	}
}

// �������� �� ��Ƽ�� �̸� ���� ó��
void cltClient::DoMsg_GAMEMSG_RESPONSE_GETPARTYMEMBERNAMELIST( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_GetPartyMemberInfo* pRcvInfo = (cltGameResponse_GetPartyMemberInfo*)pclMsg->cData;
	if ( NULL == pRcvInfo ) return;

	CNApplytoParty_PartyMatching* pDlg = (CNApplytoParty_PartyMatching*)m_pDialog[NPARTY_MATCHING_BASE_DLG];
	if ( NULL == pDlg ) return;
	if ( NULL == pDlg->pMemberList ) return;

	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		stListBoxItemData item;
		item.Init();
		item.Set( 0, pRcvInfo->aPartyMemberNameList[i] );
		pDlg->pMemberList->AddItem( &item );
	}

	pDlg->pMemberList->Refresh();
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_PARTYMATCHING_LEVEL( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_PartyMatchingLevel* pInfo = (cltGameResponse_PartyMatchingLevel*)pclMsg->cData;
	if ( NULL == pInfo ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;
	if ( NULL == pClient->m_pClient_PartyMatchingMgr ) return;

	pClient->m_pClient_PartyMatchingMgr->MsgProcess_Response_PartyMatchingLevel( id, pInfo );
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_APPLYTOPARTYJOIN( cltMsg* pclMsg, SI32 id )
{
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CREATEMYPARTY( cltMsg* pclMsg, SI32 id )
{
}

void cltClient::DoMsg_GAMEMSG_RESPONSE_CREATECOMPLETEPARTY( cltMsg* pclMsg, SI32 id )
{
	cltGameResponse_PartyMatchingCreate* pInfo = (cltGameResponse_PartyMatchingCreate*)pclMsg->cData;
	if ( NULL == pInfo ) return;

	cltClient* pClient = (cltClient*)pclClient;
	if ( NULL == pClient ) return;
	if ( NULL == pClient->m_pClient_PartyMatchingMgr ) return;

	pClient->m_pClient_PartyMatchingMgr->MsgProcess_Response_PartyMatchingCreate( id, pInfo->m_bResult );
}