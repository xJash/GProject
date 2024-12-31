// ��Ƽ��Ī
#include "../Server.h"
#include "Char/CharManager/CharManager.h"

#include "../../CommonLogic/Msg/MsgType-PartyMatching.h"
#include "../../CommonLogic/PartyMatchingMgr/Server_PartyMatchingMgr.h"
#include "../../common/PartyMgr/PartyMgr.h"
#include "../../common/PartyMgr/PartyObj.h"









// ��Ƽ��Ī ��ȸâ : ���� ����� ��Ƽ��Ī ���� ��ư Ŭ������ ����� ��Ŷ�� ���� ������ ó��
void cltServer::DoMsg_GAMEMSG_REQUEST_REMOVEPARTYMATCHING( cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pCharServer = pclCM->GetCharServer( id );
	if ( NULL == pCharServer ) return;
	if ( NULL == m_pServer_PartyMatchingMgr ) return;

	SI32 siMyCharUnique = pCharServer->GetCharUnique();
	SI32 siCategory = m_pServer_PartyMatchingMgr->Get_Category( siMyCharUnique );
	if ( 0 > siCategory || MAX_PARTYQUEST_CATEGORY_NUM <= siCategory ) return;

	m_pServer_PartyMatchingMgr->Remove_PartyMatching( siMyCharUnique );
	m_pServer_PartyMatchingMgr->MsgProcess_Request_PartyMatchingLevel( id, siCategory );
}

// ��Ƽ��Ī�� ��Ƽ�� �̸� ������ �޶�� ��û�� ���� ó��
void cltServer::DoMsg_GAMEMSG_REQUEST_GETPARTYMEMBERNAMELIST( cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_GetPartyMemberInfo* pclInfo = (cltGameRequest_GetPartyMemberInfo*)pclMsg->cData;
	if ( NULL == pclInfo ) return;

	if ( NULL == m_pServer_PartyMatchingMgr ) return;
	if ( false == m_pServer_PartyMatchingMgr->IsExist( pclInfo->siLeaderUnique ) ) return;
	if ( NULL == pclPartyMgr ) return;
	cltCharServer* pCharServer = pclCM->GetCharServer( pclInfo->siLeaderUnique );
	if ( NULL == pCharServer ) return;

	CPartyObj* pPartyObj = pclPartyMgr->GetPartyObj( pCharServer->siPartyIndex );
	if ( NULL == pPartyObj ) return;
	//------------------------------------------------------------------------------


	//////////////////////////////////////////////////////////////////////////
	cltGameResponse_GetPartyMemberInfo clSndInfo( pclInfo->siLeaderUnique );

	for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		stPartyUser* pUser = NULL;
		pUser = pPartyObj->GetPartyUser( i );

		if ( NULL == pUser) 					continue;
		if ( false == pUser->bPartyStatus ) 	continue;
		if ( 1 > pUser->siCharUnique )			continue;

		SI32 siID = -1;
		siID = pclCM->GetIDFromCharUnique( pUser->siCharUnique );

		if ( 1 > siID ) 						continue;
		if ( false == pclCM->IsValidID(siID) ) 	continue;
		if ( pclCM->CR[siID]->pclCI->GetPersonID() != pPartyObj->GetPartyUser(i)->siPersonID ) continue;

		//------- ����ó���� ���ļ� ���� �����ϴ� ĳ���� ���ؼ��� �̸��� ��´�.
		clSndInfo.aPartyMemberNameList[i] = (TCHAR*)pclCM->CR[siID]->GetName();
	}

	cltMsg clSndMsg( GAMEMSG_RESPONSE_GETPARTYMEMBERNAMELIST, sizeof(clSndInfo), (BYTE*)&clSndInfo );
	pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clSndMsg );
	//------------------------------------------------------------------------------
}

// Ŭ�� -> ���� : ���������� �ش��ϴ� ��Ƽ��Ī ����Ʈ�� �޶�� ��û�� ���� ó��
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYMATCHING_LEVEL(cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_PartyMatchingLevel* pclInfo = (cltGameRequest_PartyMatchingLevel*)pclMsg->cData;
	if ( NULL == pclInfo ) return;

	cltCharServer* pCharServer = pclCM->GetCharServer( id );
	if ( NULL == pCharServer ) return;

	if ( NULL == m_pServer_PartyMatchingMgr ) return;

	m_pServer_PartyMatchingMgr->MsgProcess_Request_PartyMatchingLevel( id, pclInfo->m_siLevelType );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_APPYLYTOPARTYJOIN( cltMsg* pclMsg, SI32 id )
{

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CREATEMYPARTY( cltMsg* pclMsg, SI32 id)
{
	// ��Ƽ�� ������Ų��.


	// ��Ƽ����Ʈ �Ҵ�,
	//SetPartyQuestData(��Ƽ������Ʈ, )
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CREATECOMPLETEPARTY( cltMsg* pclMsg, SI32 id)
{
	cltGameRequest_PartyMatchingCreate* pclInfo = (cltGameRequest_PartyMatchingCreate*)pclMsg->cData;
	if ( NULL == pclInfo ) return;

	cltCharServer* pCharServer = pclCM->GetCharServer( id );
	if ( NULL == pCharServer ) return;

	// ĳ���Ͱ� �̹� ��Ƽ�� ���ԵǾ� �ִ�.
	if ( 0 < pCharServer->siPartyIndex )
	{
		CPartyObj* pPartyObj = NULL;
		pPartyObj = pclPartyMgr->GetPartyObj( pCharServer->siPartyIndex );
		if ( NULL != pPartyObj )
		{
			// ��Ƽ ���¿��� �������Ը� ��Ƽ��Ī�� ����Ҽ� �ְ� �Ϸ���...
			//if ( pPartyObj->GetPartyLeaderUnique() != pCharServer->GetCharUnique() )
			{
				SI16 siExceptionFlags = 0;
				siExceptionFlags = (PARTYMATCHING_ALREADY_PARTYMEMBER);

				cltGameResponse_PartyMatchingException clMsgInfo( siExceptionFlags );
				cltMsg clMsg( GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
				pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

				return;
			}
		}
	}

	if ( NULL == m_pServer_PartyMatchingMgr ) return;

	m_pServer_PartyMatchingMgr->MsgProcess_Request_PartyMatchingCreate( id, pclInfo->m_Info );
}