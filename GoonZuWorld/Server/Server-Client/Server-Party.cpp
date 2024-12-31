#include "..\Server.h"
#include "..\..\CommonLogic\Msg\MsgType-Party.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\Common\PartyMgr\PartyMgr.h"
#include "..\..\Common\PartyMgr\PartyObj.h"
#include "../../common/Order/order.h"
#include "Char\CharManager\CharManager.h"
#include "Map/map.h"

#include "../../CommonLogic/MsgRval-Define.h"
#include "../../client/ninterface/npartydlg/NPartyDlg.h"

/*
// ��Ƽ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_CREATE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Party_Create *pclPartyCreate = (cltGameMsgRequest_Party_Create *) pclMsg->cData;

	// ��Ƽ���� ���� �ؼ� ������ ����.
	if( _tcslen( pclPartyCreate->strPartyName ) < 1 )
	{
		return;
	}

	if ( pclCM->CR[id]->GetCharUnique() < 1 )
	{
		return;
	}

	// ��Ƽ�� �������̸�, ��Ƽ ���� �ȵ�.
	if ( pclCM->CR[id]->siPartyIndex > 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();

	if( FromPersonID < 1 )
		return ;

	SI32 siPartyIndex = pclPartyMgr->CreateParty( FromPersonID, pclCM->CR[id]->GetCharUnique() );

	// ��Ƽ ���� ���� �ʰ��� ���
	if (  siPartyIndex < 0 )
	{
		return;
	}

	pclCM->CR[id]->siPartyIndex  = siPartyIndex; 

	cltGameMsgResponse_Party_Create clGameMsgResponse_Party_Create( siPartyIndex );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CREATE, sizeof( clGameMsgResponse_Party_Create ), (BYTE*)&clGameMsgResponse_Party_Create );
	pclCM->CR[id]->SendNetMsg( (BYTE*)&clMsg );

	return;
}
*/

// ��Ƽ���� �ɷ��� ����� ��Ƽ�� �ϱ� ���ؼ� � �������� ��Ƽ �ʴ븦 �ϴ� �κ�
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_CREATEINVITE( cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	cltGameMsgRequest_Party_CreateInvite *pclPartyCreateInvite = (cltGameMsgRequest_Party_CreateInvite *) pclMsg->cData;

	if ( pclPartyCreateInvite->siInvitedCharUnique < 1 )
	{
		return;
	}

	// ��Ƽ ���̸� ��Ƽ ���� �ϸ鼭 �ʴ��ϴ� �� �޽����� ���� �� ����.
	if ( pclCM->CR[ id ]->siPartyIndex > 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	SI32 toid = pclCM->GetIDFromCharUnique( pclPartyCreateInvite->siInvitedCharUnique );
	if(toid < 1) return;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID < 1) return;

	// ��Ƽ�� �������̸�, ��Ƽ �ʴ� �ȵ�.
	if ( pclCM->CR[ toid ]->siPartyIndex > 0 )
	{
		SendServerResponseMsg(0, SRVAL_PARTYINVITE_ALREADYPARTY,  0, 0, id);
		return;
	}

	// ��Ƽ �ʴ� �ź� ����
	cltCharServer *pclChar = ( cltCharServer * )pclCM->CR[toid];

	if ( pclChar->bPartyInviteReject )
	{
		SendServerResponseMsg( 0, SRVAL_PARTYINVITE_REJECT,  0, 0, id );
		return;
	}

	TCHAR *strCharName = (TCHAR*)pclCM->CR[id]->pclCI->clBI.GetName();

	if ( strCharName == NULL )
	{
		return;
	}

	// ��Ƽ ��󿡰� ��Ƽ�� �����Ұ������� ����
	cltGameMsgResponse_Party_CreateInvite clGameMsgResponse_Party_CreateInvite( strCharName, FromPersonID );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CREATEINVITE, sizeof( clGameMsgResponse_Party_CreateInvite ), (BYTE*)&clGameMsgResponse_Party_CreateInvite );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg );

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_CREATEJOIN( cltMsg* pclMsg, SI32 id )
{
	WRITE_MEMLOG( 150, 1, 0, 0 );

	cltGameMsgRequest_Party_CreateJoin *pclPartyCreateJoin = (cltGameMsgRequest_Party_CreateJoin *) pclMsg->cData;


	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		cltCharServer* pclchar = pclCM->GetCharServer(id);
		if ( NULL == pclchar)
			return;

		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclchar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclchar) )
			{
				return;
			}
		}
	}

	if ( pclPartyCreateJoin->siLeaderPersonID < 1 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ��Ƽ ���̸鼭 �ٸ� ��Ƽ ���� �ʴ뿡 ���� ���� ���� ������...
	if ( pclCM->CR[ id ]->siPartyIndex > 0 )
	{
		return;
	}

	SI32 LeaderID = pclCM->GetIDFromPersonID( pclPartyCreateJoin->siLeaderPersonID );

	if(pclCM->IsValidID(LeaderID) == false) return;

	// ��û�� �� ���̿� ��Ƽ���� �� ����� ��Ƽ�� �������̸�, 
	if ( pclCM->CR[ LeaderID ]->siPartyIndex > 0 )
	{

		SendServerResponseMsg(0, SRVAL_PARTYINVITE_LEADERALREADYPARTY,  0, 0, id);

		WRITE_MEMLOG( 150, 2, 0, 0 );
		return;
	}

	SI32 siPartyIndex = pclPartyMgr->CreateParty( pclPartyCreateJoin->siLeaderPersonID, pclCM->CR[LeaderID]->GetCharUnique(), pclCM->CR[LeaderID]->pclCI->clIP.GetLevel() );

	// ��Ƽ ���� ���� �ʰ��� ���
	if (  siPartyIndex < 0 )
	{
		return;
	}

	pclCM->CR[LeaderID]->siPartyIndex = siPartyIndex; 
	pclCM->CR[id]->siPartyIndex = siPartyIndex; 

	CPartyObj *pPartyObj = pclPartyMgr->GetPartyObj( siPartyIndex );

	// �ε��� ��ȣ�� ��Ƽ�� �����Ѵ�.
	if ( pPartyObj == NULL )
	{
		return;
	}

	// ��Ƽ��ȣ�� ��Ƽ���� �´��� Ȯ���غ�
	if ( ! pPartyObj->IsPartyLeader( pclPartyCreateJoin->siLeaderPersonID ) )
	{
		return;
	}

	SI16 JoinedIndex = pPartyObj->JoinParty( FromPersonID, pclCM->CR[id]->GetCharUnique(),pclCM->CR[id]->pclCI->clIP.GetLevel() );

	// �� ���� �Ʒ��� JoinedIndex < 0  �� �� ���� ���� ������...
	if ( JoinedIndex < 0 )
	{
		pclLog->FilePrint( TEXT("PartyError.txt"), TEXT("Joined Index = %d"), JoinedIndex );
		return;
	}

	TCHAR *strLeaderCharName = (TCHAR*)pclCM->CR[LeaderID]->pclCI->clBI.GetName();
	if ( strLeaderCharName == NULL )
	{
		return;
	}

	TCHAR *strMemberCharName = (TCHAR*)pclCM->CR[id]->pclCI->clBI.GetName();
	if ( strMemberCharName == NULL )
	{
		return;
	}

	// ��Ƽ �̸� ������ ��Ƽ ������Ʈ�� ����
	TCHAR* pszPartyName = NULL;
	pszPartyName = m_pServer_PartyMatchingMgr->GetPartyName( pclCM->CR[LeaderID]->GetCharUnique() );
	pPartyObj->SetPartyName( pszPartyName );

	// ��Ƽ������ �ٸ� ��Ƽ�� �����ϴ� ����� ���� ��Ƽ��Ī�� �ִٸ� �����ش�.
	m_pServer_PartyMatchingMgr->Remove_PartyMatching( pclCM->CR[id]->GetCharUnique() );

	// ��Ƽ�� ���� ����
	bool bIsPartyQuestParty = false;
	SI32 siCategory = -1;
	SI32 siMission = -1;

	bIsPartyQuestParty = m_pServer_PartyMatchingMgr->IsExist( pclCM->CR[LeaderID]->GetCharUnique() );
	if ( true == bIsPartyQuestParty )
	{
		siCategory = m_pServer_PartyMatchingMgr->Get_Category( pclCM->CR[LeaderID]->GetCharUnique() );
		siMission = m_pServer_PartyMatchingMgr->Get_Mission( pclCM->CR[LeaderID]->GetCharUnique() );
	}

	//������ ��ġ
	cltCharPos clLeaderCharPos(pclCM->CR[LeaderID]->GetMapIndex(), pclCM->CR[LeaderID]->GetX(),pclCM->CR[LeaderID]->GetY());
	//��Ƽ���� ��ġ
	cltCharPos clMemberCharPos(pclCM->CR[id]->GetMapIndex(), pclCM->CR[id]->GetX(),pclCM->CR[id]->GetY());

	// ��Ƽ����
	cltGameMsgResponse_Party_CreateJoin clGameMsgResponse_Party_CreateJoin( siPartyIndex, pclPartyCreateJoin->siLeaderPersonID, pclCM->GetIDFromCharUnique(LeaderID), pclCM->CR[LeaderID]->pclCI->clIP.GetLevel(), strLeaderCharName, &clLeaderCharPos , FromPersonID, pclCM->GetIDFromCharUnique(id), pclCM->CR[id]->pclCI->clIP.GetLevel(), strMemberCharName,&clMemberCharPos, pszPartyName );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CREATEJOIN, sizeof( clGameMsgResponse_Party_CreateJoin ), (BYTE*)&clGameMsgResponse_Party_CreateJoin );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

	// ���岨
	cltGameMsgResponse_Party_CreateJoin clSendMsgInfo_toLeader( siPartyIndex, pclPartyCreateJoin->siLeaderPersonID, pclCM->GetIDFromCharUnique(LeaderID), pclCM->CR[LeaderID]->pclCI->clIP.GetLevel(), strLeaderCharName, &clLeaderCharPos , FromPersonID, pclCM->GetIDFromCharUnique(id), pclCM->CR[id]->pclCI->clIP.GetLevel(), strMemberCharName,&clMemberCharPos, pszPartyName, bIsPartyQuestParty, siCategory, siMission );
	cltMsg clMsg2( GAMEMSG_RESPONSE_PARTY_CREATEJOIN, sizeof( clSendMsgInfo_toLeader ), (BYTE*)&clSendMsgInfo_toLeader );
	pclCM->CR[LeaderID]->SendNetMsg((sPacketHeader*)&clMsg2 );

	WRITE_MEMLOG( 150, 3, 0, 0 );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��Ƽ ���� ����. 
		// Param1 == ��Ƽ ��ȣ. 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_CREATEJOIN, 
			0, (cltCharServer*)(pclCM->CR[id]), NULL, pclPartyCreateJoin->siLeaderPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			siPartyIndex, 0, 0, 0, 0, NULL, NULL);
	}
	return;
}

// ��Ƽ �ʴ�
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_INVITE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Party_Invite *pclPartyInvite = (cltGameMsgRequest_Party_Invite *) pclMsg->cData;

	if ( pclPartyInvite->siInvitedCharUnique < 1 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	// ��Ƽ��ȣ�� ��Ƽ���� �´��� Ȯ���غ�
	if ( ! pclPartyMgr->IsPartyLeader( FromPersonID, pclPartyInvite->siPartyIndex ) )
	{
		SendServerResponseMsg(0, SRVAL_PARTYINVITE_NOTLEADER,  0, 0, id);
		return;
	}

	// ��Ƽ�� ������ �� �߰��Ҽ� �ִ��� Ȯ��
	if ( ! pclPartyMgr->IsEmptyUserListExist( pclPartyInvite->siPartyIndex ) )
	{
		SendServerResponseMsg(0, SRVAL_PARTYINVITE_FULLPARTY,  0, 0, id);
		return;
	}

	SI32 toid = pclCM->GetIDFromCharUnique( pclPartyInvite->siInvitedCharUnique );
	if(pclCM->IsValidID(toid) == false) return;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if(ToPersonID < 1) return;

	// ��Ƽ�� �������̸�, ��Ƽ �ʴ� �ȵ�.
	if ( pclCM->CR[ toid ]->siPartyIndex > 0 )
	{
		SendServerResponseMsg(0, SRVAL_PARTYINVITE_ALREADYPARTY,  0, 0, id);
		return;
	}

	// ��Ƽ �ʴ� �ź� ����
	cltCharServer *pclChar = ( cltCharServer * )pclCM->CR[toid];

	if ( pclChar->bPartyInviteReject )
	{
		SendServerResponseMsg( 0, SRVAL_PARTYINVITE_REJECT,  0, 0, id );
		return;
	}

	TCHAR *strCharName = (TCHAR*)pclCM->CR[id]->pclCI->clBI.GetName();

	if ( strCharName == NULL )
	{
		return;
	}

	// ��Ƽ ��󿡰� ��Ƽ�� �����Ұ������� ����
	cltGameMsgResponse_Party_Invite clGameMsgResponse_Party_Invite( strCharName, FromPersonID, pclPartyInvite->siPartyIndex );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_INVITE, sizeof( clGameMsgResponse_Party_Invite ), (BYTE*)&clGameMsgResponse_Party_Invite );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg );

	return;
}

// ��Ƽ �ʴ� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_INVITEREJECT( cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->GetPersonID() < 1 )
	{
		return;
	}

	cltGameMsgRequest_Party_InviteReject *pclPartyInviteReject = (cltGameMsgRequest_Party_InviteReject *) pclMsg->cData;

	if ( pclPartyInviteReject->siPartyLeaderPersonID < 1 )
	{
		return;
	}

	SI32 LeaderID = pclCM->GetIDFromPersonID( pclPartyInviteReject->siPartyLeaderPersonID );
	if ( LeaderID && pclCM->IsValidID( LeaderID ) == TRUE )
	{
		TCHAR * RejectUserName = (TCHAR*)pclCM->CR[id]->GetName();

		if ( RejectUserName == NULL || _tcslen( RejectUserName ) < 1 )
		{
			return;
		}

		cltGameMsgResponse_Party_InviteReject clGameMsgResponse_Party_InviteReject( RejectUserName );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_INVITEREJECT, sizeof( clGameMsgResponse_Party_InviteReject ), (BYTE*)&clGameMsgResponse_Party_InviteReject );
		pclCM->CR[LeaderID]->SendNetMsg((sPacketHeader*)&clMsg );
	}

	return;
}

// [��Ƽ��Ī]
// ��Ƽ ������ ���ϴ� ������ ��Ƽ ���� ��û�� �ߴ�. (���� -> ����)
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_WANTJOIN( cltMsg* pclMsg, SI32 id )
{
	if ( false == pclCM->IsValidID( id ) ) return;
	if ( NULL == pclMsg ) return;

	cltGameMsgRequest_Party_WantJoin* pJoinInfo = (cltGameMsgRequest_Party_WantJoin*)pclMsg->cData;
	if ( NULL == pJoinInfo ) return;

	if ( false == m_pServer_PartyMatchingMgr->IsExist( pJoinInfo->siLeaderUnique ) ) return;

	SI32 siLeaderID = pclCM->GetIDFromCharUnique( pJoinInfo->siLeaderUnique );
	cltCharServer* pLeaderChar = pclCM->GetCharServer( siLeaderID );
	if ( NULL == pLeaderChar ) return;

	if ( 0 < pclCM->CR[id]->siPartyIndex )
	{
		SI16 siExceptionFlags = 0;
		siExceptionFlags = (PARTYMATCHING_ALREADY_PARTYMEMBER);

		cltGameResponse_PartyMatchingException clMsgInfo( siExceptionFlags );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

		return;
	}

	SI32 siMemberUnique = pclCM->CR[id]->GetCharUnique();

	cltGameMsgResponse_Party_WantJoin clMsgInfo( pJoinInfo->siLeaderUnique, siMemberUnique, (TCHAR*)pclCM->CR[id]->GetName(), 0 );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_WANTJOIN, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
	pclCM->CR[siLeaderID]->SendNetMsg( (sPacketHeader*)&clMsg );
}

// [��Ƽ��Ī]
// ������ ��Ƽ ������ ��� �Ѵٰ� ������ �˷��� (���� -> ����)
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_WANTJOINRESULT( cltMsg* pclMsg, SI32 id )
{
	WRITE_MEMLOG( 150, 1, 0, 0 );

	cltGameMsgRequest_Party_WantJoinResult *pJoinInfo = (cltGameMsgRequest_Party_WantJoinResult *) pclMsg->cData;
	if ( NULL == pJoinInfo ) return;

	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		cltCharServer* pclchar = pclCM->GetCharServer(id);
		if ( NULL == pclchar) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }

		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclchar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclchar) ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }
		}
	}

	cltCharServer* pCharServer = pclCM->GetCharServer( id );
	if ( NULL == pCharServer ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }

	SI32 siLeaderPersonID = 0;
	SI32 siMemberPersonID = 0;
	SI32 siLeaderID = 0;
	SI32 siMemberID = 0;
	SI32 siLeaderUnique = 0;
	SI32 siMemberUnique = 0;
	SI32 siPartyIndex = 0;
	CPartyObj* pPartyObj = NULL;
	SI16 siJoinedIndex = -1;
	TCHAR* pszPartyName = NULL;

	siLeaderPersonID = pCharServer->pclCI->GetPersonID();
	siMemberPersonID = pclCM->CR[ pclCM->GetIDFromCharUnique(pJoinInfo->siMemberUnique) ]->pclCI->GetPersonID();
	siLeaderID = pclCM->GetIDFromPersonID( siLeaderPersonID );
	siMemberID = pclCM->GetIDFromPersonID( siMemberPersonID );
	siLeaderUnique = pclCM->CR[siLeaderID]->GetCharUnique();
	siMemberUnique = pclCM->CR[siMemberID]->GetCharUnique();

	if ( 1 > siLeaderPersonID ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }
	if ( 1 > siMemberPersonID ) return;
	if ( false == pclCM->IsValidID(siLeaderID) ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }
	if ( false == pclCM->IsValidID(siMemberID) ) return;

	if ( 0 < pclCM->CR[siMemberID]->siPartyIndex )
	{
		SI16 siExceptionFlags = 0;
		siExceptionFlags = (PARTYMATCHING_ALREADY_PARTYMEMBER);

		cltGameResponse_PartyMatchingException clMsgInfo( siExceptionFlags );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTYMATCHINGEXCEPTION, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
		pclCM->CR[siMemberID]->SendNetMsg( (sPacketHeader*)&clMsg );

		return;
	}

	//////////////////////////////////////////////////////////////////////////

	// ��Ƽ ������ �������� ���
	if ( false == pJoinInfo->bResult )
	{
		//bool result, SI32 leaderunique, SI32 memberunique, SI32 partyindex, TCHAR* pszpartyname
		cltGameMsgResponse_Party_WantJoinResult clMsgInfo( false, siLeaderUnique, siMemberUnique, siPartyIndex, NULL );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_WANTJOINRESULT, sizeof(clMsgInfo), (BYTE*)&clMsgInfo );
		pclCM->CR[siMemberID]->SendNetMsg( (sPacketHeader*)&clMsg );

		return;
	}

	//////////////////////////////////////////////////////////////////////////


	// ��Ƽ�� ���� ���¿��� ������ �����̴�.
	if ( 0 >= pclCM->CR[siLeaderID]->siPartyIndex )						// ������ ��Ƽ�� ���ԵǾ� �ִ� ���°� �ƴ϶�� ��Ƽ�� ������ ������ ó��
	{
		siPartyIndex = pclPartyMgr->CreateParty( siLeaderPersonID, siLeaderUnique, pclCM->CR[siLeaderID]->pclCI->clIP.GetLevel() );
		if ( 0 > siPartyIndex ) return;	// ��Ƽ ���� ������ �ʰ��ؼ� 0���� ���� ���� ���ϵƴٸ� ����

		pclCM->CR[siLeaderID]->siPartyIndex = siPartyIndex;

		//////////////////////////////////////////////////////////////////////////

		pPartyObj = pclPartyMgr->GetPartyObj( siPartyIndex );
		if ( NULL == pPartyObj ) return;

		if ( false == pPartyObj->IsPartyLeader(siLeaderPersonID) ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }

		siJoinedIndex = pPartyObj->JoinParty( siMemberPersonID, siMemberUnique, pclCM->CR[siMemberID]->pclCI->clIP.GetLevel() );
		if ( siJoinedIndex < 0 )
		{
			pclLog->FilePrint( TEXT("PartyError.txt"), TEXT("Joined Index = %d"), siJoinedIndex );
			return;
		}

		pclCM->CR[siMemberID]->siPartyIndex = siPartyIndex;

		pszPartyName = m_pServer_PartyMatchingMgr->GetPartyName( siLeaderUnique );
		pPartyObj->SetPartyName( pszPartyName );

		TCHAR *strLeaderCharName = (TCHAR*)pclCM->CR[siLeaderID]->pclCI->clBI.GetName();
		if ( strLeaderCharName == NULL ) return;

		TCHAR *strMemberCharName = (TCHAR*)pclCM->CR[siMemberID]->pclCI->clBI.GetName();
		if ( strMemberCharName == NULL ) return;

		// ��Ƽ������ �ٸ� ��Ƽ�� �����ϴ� ����� ���� ��Ƽ��Ī�� �ִٸ� �����ش�.
		m_pServer_PartyMatchingMgr->Remove_PartyMatching( siMemberUnique );

		// ��Ƽ�� ���� ����
		bool bIsPartyQuestParty = false;
		SI32 siCategory = -1;
		SI32 siMission = -1;

		bIsPartyQuestParty = m_pServer_PartyMatchingMgr->IsExist( siLeaderUnique );
		if ( true == bIsPartyQuestParty )
		{
			siCategory = m_pServer_PartyMatchingMgr->Get_Category( siLeaderUnique );
			siMission = m_pServer_PartyMatchingMgr->Get_Mission( siLeaderUnique );
		}

		//������ ��ġ
		cltCharPos clLeaderCharPos(pclCM->CR[siLeaderID]->GetMapIndex(), pclCM->CR[siLeaderID]->GetX(),pclCM->CR[siLeaderID]->GetY());
		//��Ƽ���� ��ġ
		cltCharPos clMemberCharPos(pclCM->CR[siMemberID]->GetMapIndex(), pclCM->CR[siMemberID]->GetX(),pclCM->CR[siMemberID]->GetY());

		cltGameMsgResponse_Party_CreateJoin clGameMsgResponse_Party_CreateJoin( siPartyIndex, siLeaderPersonID, siLeaderID, pclCM->CR[siLeaderID]->pclCI->clIP.GetLevel(), strLeaderCharName, &clLeaderCharPos , siMemberPersonID, siMemberID, pclCM->CR[siMemberID]->pclCI->clIP.GetLevel(), strMemberCharName, &clMemberCharPos, pszPartyName );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CREATEJOIN, sizeof( clGameMsgResponse_Party_CreateJoin ), (BYTE*)&clGameMsgResponse_Party_CreateJoin );
		pclCM->CR[siMemberID]->SendNetMsg((sPacketHeader*)&clMsg );

		cltGameMsgResponse_Party_CreateJoin clSendMsgInfo_toLeader
			( 
			siPartyIndex, siLeaderPersonID, siLeaderID, pclCM->CR[siLeaderID]->pclCI->clIP.GetLevel(), strLeaderCharName, &clLeaderCharPos,
			siMemberPersonID, siMemberID, pclCM->CR[siMemberID]->pclCI->clIP.GetLevel(), strMemberCharName, &clMemberCharPos,
			pszPartyName, bIsPartyQuestParty, siCategory, siMission
			);
		cltMsg clMsg2( GAMEMSG_RESPONSE_PARTY_CREATEJOIN, sizeof( clSendMsgInfo_toLeader ), (BYTE*)&clSendMsgInfo_toLeader );
		pclCM->CR[siLeaderID]->SendNetMsg((sPacketHeader*)&clMsg2 );

		WRITE_MEMLOG( 150, 3, 0, 0 );

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��Ƽ ���� ����. 
			// Param1 == ��Ƽ ��ȣ. 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_CREATEJOIN, 
				0, (cltCharServer*)(pclCM->CR[siLeaderID]), NULL, siLeaderPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				siPartyIndex, 0, 0, 0, 0, NULL, NULL);
		}

		return;
	}
	// ��Ƽ�� �ִ� ���¿��� ������ �����̴�.
	else
	{
		siPartyIndex = pclCM->CR[siLeaderID]->siPartyIndex;

		//////////////////////////////////////////////////////////////////////////

		pPartyObj = pclPartyMgr->GetPartyObj( siPartyIndex );
		if ( NULL == pPartyObj ) return;

		if ( false == pPartyObj->IsPartyLeader(siLeaderPersonID) ) { m_pServer_PartyMatchingMgr->Remove_PartyMatching(pJoinInfo->siLeaderUnique); return; }

		siJoinedIndex = pPartyObj->JoinParty( siMemberPersonID, siMemberUnique, pclCM->CR[siMemberID]->pclCI->clIP.GetLevel() );
		if ( siJoinedIndex < 0 )
		{
			pclLog->FilePrint( TEXT("PartyError.txt"), TEXT("Joined Index = %d"), siJoinedIndex );
			return;
		}

		pclCM->CR[siMemberID]->siPartyIndex = siPartyIndex;

		pszPartyName = m_pServer_PartyMatchingMgr->GetPartyName( siLeaderUnique );
		pPartyObj->SetPartyName( pszPartyName );

		TCHAR *strLeaderCharName = (TCHAR*)pclCM->CR[siLeaderID]->pclCI->clBI.GetName();
		if ( strLeaderCharName == NULL ) return;

		TCHAR *strMemberCharName = (TCHAR*)pclCM->CR[siMemberID]->pclCI->clBI.GetName();
		if ( strMemberCharName == NULL ) return;

		// ��Ƽ������ �ٸ� ��Ƽ�� �����ϴ� ����� ���� ��Ƽ��Ī�� �ִٸ� �����ش�.
		m_pServer_PartyMatchingMgr->Remove_PartyMatching( siMemberUnique );


		// ��Ƽ�� ���� �Ǿ����� �˷���
		cltGameMsgResponse_Party_Join clGameMsgResponse_Party_Join( siPartyIndex, siJoinedIndex, pPartyObj->GetItemGetPattern(), pszPartyName );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_JOIN, sizeof( clGameMsgResponse_Party_Join ), (BYTE*)&clGameMsgResponse_Party_Join );
		pclCM->CR[siMemberID]->SendNetMsg((sPacketHeader*)&clMsg );

		// ��Ƽ������ ��ġ�� �˷��ֱ� ���� �޽����� �����δ�.
		cltCharPos clCharPos( pclCM->CR[siMemberID]->GetMapIndex(), pclCM->CR[siMemberID]->GetX(), pclCM->CR[siMemberID]->GetY() );

		cltGameMsgResponse_Party_AddUser clGameMsgResponse_Party_AddUser( siJoinedIndex, pclCM->CR[siMemberID]->GetCharUnique(), false, strMemberCharName, pclCM->CR[siMemberID]->pclCI->clIP.GetLevel(), &clCharPos );
		cltMsg clMsgAddUser( GAMEMSG_RESPONSE_PARTY_ADDUSER, sizeof( clGameMsgResponse_Party_AddUser ), (BYTE*)&clGameMsgResponse_Party_AddUser );

		for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
		{
			if ( ! pPartyObj->GetPartyUser( i )->bPartyStatus )
			{
				continue;
			}

			SI32 CharUnique = pPartyObj->GetPartyUser( i )->siCharUnique;

			if ( CharUnique < 1 )
			{
				continue;
			}

			SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

			if(pclCM->IsValidID(CharID) == false) continue;

			// ������ ��Ƽ���鿡�� ��Ƽ���� �߰��Ǿ����� �˸�
			if ( pclCM->IsValidID( CharID ) == TRUE )
			{
				if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pPartyObj->GetPartyUser( i )->siPersonID )
				{
					continue;
				}

				// �ڱ� �ڽ����״� �� ������
				if ( CharID == siMemberID )
				{
					continue;
				}

				pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsgAddUser );
			}
		}

		WRITE_MEMLOG( 150, 6, 0, 0 );
		return;
	}	
}

// ��Ƽ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_JOIN( cltMsg* pclMsg, SI32 id )
{
	WRITE_MEMLOG( 150, 5, 0, 0 );

	if(pclCM->IsValidID(id) == false) return;

	cltGameMsgRequest_Party_Join *pclPartyJoin = ( cltGameMsgRequest_Party_Join * ) pclMsg->cData;

	if ( pclCM->CR[id]->GetCharUnique() < 1 )
	{
		return;
	}

	// ��Ƽ�� �������̸�, ��Ƽ ���� �ȵ�.
	if ( pclCM->CR[id]->siPartyIndex > 0 )
	{
		return;
	}

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	CPartyObj *pTemp = pclPartyMgr->GetPartyObj( pclPartyJoin->siPartyIndex );

	// �ε��� ��ȣ�� ��Ƽ�� �����Ѵ�.
	if ( pTemp == NULL )
	{
		return;
	}

	// ��Ƽ��ȣ�� ��Ƽ���� �´��� Ȯ���غ�
	if ( ! pTemp->IsPartyLeader( pclPartyJoin->siPartyLeaderPersonID ) )
	{
		return;
	}

	SI16 JoinedIndex = pTemp->JoinParty( FromPersonID, pclCM->CR[id]->GetCharUnique(), pclCM->CR[id]->pclCI->clIP.GetLevel() );

	// ��Ƽ ���� �ο��� �� á��.
	if ( JoinedIndex < 0 )
	{
		return;
	}

	TCHAR *strName = (TCHAR*)pclCM->CR[id]->GetName();
	if ( strName == NULL )
	{
		return;
	}

	pclCM->CR[id]->siPartyIndex  = pclPartyJoin->siPartyIndex;

	// ��Ƽ������ �ٸ� ��Ƽ�� �����ϴ� ����� ���� ��Ƽ��Ī�� �ִٸ� �����ش�.
	m_pServer_PartyMatchingMgr->Remove_PartyMatching( pclCM->CR[id]->GetCharUnique() );


	cltServer* pServer = (cltServer*) pclClient;
	if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
	{
		// ��Ƽ����Ʈ�� ��Ƽ�� ���ԵǾ����Ƿ� �ش���Ƽ�� ��Ƽ����Ʈ�� ���� �մϴ�.
		if(pServer->pclPartyMgr->GetPartyObj(pclCM->CR[id]->siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
			pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(pclCM->CR[id]->siPartyIndex, 0, PARTYQUEST_MESSAGE_FAILED_ADDED_USER);
	}

	TCHAR* pszPartyName = NULL;
	pszPartyName = m_pServer_PartyMatchingMgr->GetPartyName( pclCM->CR[pclCM->GetIDFromPersonID(pclPartyJoin->siPartyLeaderPersonID)]->GetCharUnique() );
	if ( NULL != pszPartyName ) pTemp->SetPartyName( pszPartyName );

	// ��Ƽ�� ���� �Ǿ����� �˷���
	cltGameMsgResponse_Party_Join clGameMsgResponse_Party_Join( pclPartyJoin->siPartyIndex, JoinedIndex, pTemp->GetItemGetPattern(), pszPartyName );
	cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_JOIN, sizeof( clGameMsgResponse_Party_Join ), (BYTE*)&clGameMsgResponse_Party_Join );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

	pclCM->CR[id]->siPartyIndex = pclPartyJoin->siPartyIndex;	// ĳ���� ���� ������Ʈ


	// ��Ƽ������ ��ġ�� �˷��ֱ� ���� �޽����� �����δ�.
	cltCharPos clCharPos( pclCM->CR[id]->GetMapIndex(),pclCM->CR[id]->GetX(),pclCM->CR[id]->GetY() );

	cltGameMsgResponse_Party_AddUser clGameMsgResponse_Party_AddUser( JoinedIndex, pclCM->CR[id]->GetCharUnique(), false, strName, pclCM->CR[id]->pclCI->clIP.GetLevel(),&clCharPos );
	cltMsg clMsgAddUser( GAMEMSG_RESPONSE_PARTY_ADDUSER, sizeof( clGameMsgResponse_Party_AddUser ), (BYTE*)&clGameMsgResponse_Party_AddUser );

	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( ! pTemp->GetPartyUser( i )->bPartyStatus )
		{
			continue;
		}

		SI32 CharUnique = pTemp->GetPartyUser( i )->siCharUnique;

		if ( CharUnique < 1 )
		{
			continue;
		}

		SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

		if(pclCM->IsValidID(CharID) == false) continue;

		// ������ ��Ƽ���鿡�� ��Ƽ���� �߰��Ǿ����� �˸�
		if ( pclCM->IsValidID( CharID ) == TRUE )
		{
			if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
			{
				continue;
			}

			// �ڱ� �ڽ����״� �� ������
			if ( CharID == id )
			{
				continue;
			}

			pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsgAddUser );
		}
	}

	WRITE_MEMLOG( 150, 6, 0, 0 );
	return;
}

// ��Ƽ Ż��
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_LEAVE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Party_Leave *pclPartyLeave = ( cltGameMsgRequest_Party_Leave* ) pclMsg->cData;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();

	if( FromPersonID < 1 )
		return ;

	TCHAR *strName = (TCHAR*)pclCM->CR[id]->GetName();
	if ( strName == NULL )
	{
		return;
	}

	CPartyObj *pTemp = pclPartyMgr->GetPartyObj( pclPartyLeave->siPartyIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	SI16 MyPartyUserListIndex = pTemp->GetPartyUserListIndex( pclCM->CR[id]->GetCharUnique() );

	if ( MyPartyUserListIndex < 0 )			// ���� ��Ƽ�� ����Ʈ�� ����.
	{
		return;
	}

	// �������� ����� �����̾����� ��Ƽ��Ī ����Ʈ�� �ش� ������ ���� ��Ƽ��Ī�� �ִ��� �˻��ؼ� �����ش�.
	if( true == pTemp->IsPartyLeader(FromPersonID) )
	{
		if( NULL != pclClient->m_pServer_PartyMatchingMgr)
		{
			pclClient->m_pServer_PartyMatchingMgr->Remove_PartyMatching( pclCM->CR[id]->GetCharUnique() );
		}
	}

	// [����] ������ : ���� �������ȿ� ������ ��Ƽ ���� �Ұ�
	SI32 siMapIndex		= pclCM->CR[id]->GetMapIndex();

	if ( pclMapManager->IsPartyMap( siMapIndex ) == true )
	{
		return;
	}

	SI32 siRet = 0;
	SI16 ret = pTemp->LeaveParty( FromPersonID, &siRet );

	if ( ret < 0 ) 
	{
		return;
	}

	pclCM->CR[id]->siPartyIndex = 0;			// ĳ���� ���� ������Ʈ

	switch( ret )
	{
	case PARTY_DELETE:
		{
			// ������ �������� �˷���
			/*
			cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( siRet, pclCM->CR[id]->GetCharUnique() );
			cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
			pclCM->CR[id]->SendNetMsg( (BYTE*)&clMsg1 );
			*/

				if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
				{
					if(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
					{
						if(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->GetPartyUserNum() < m_pPartyQuestMgr->GetPartyQuestCategoryData(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->m_PartyQuestInfo.m_siCategoryIndex)->m_siMinUser)
						{
							cltServer* pServer = (cltServer*) pclClient;
							pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(pclPartyLeave->siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
						}	
					}
				}	


				for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
				{
					if ( pTemp->GetPartyUser( i )->bPartyStatus )
					{
						SI32 ListUserCharUnique = pTemp->GetPartyUser( i )->siCharUnique;

						if ( ListUserCharUnique < 1 )
						{
							continue;
						}

						SI32 ListUserCharID = pclCM->GetIDFromCharUnique( ListUserCharUnique );

						if ( ListUserCharID < 1 )
						{
							continue;
						}

						if ( pclCM->IsValidID( ListUserCharID ) == TRUE )
						{
							if ( pclCM->CR[ ListUserCharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
							{
								continue;
							}
							cltGameMsgResponse_Party_Delete clGameMsgResponse_Party_Delete( pclPartyLeave->siPartyIndex );
							cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_DELETE, sizeof( clGameMsgResponse_Party_Delete ), (BYTE*)&clGameMsgResponse_Party_Delete );
							pclCM->CR[ ListUserCharID ]->SendNetMsg((sPacketHeader*)&clMsg );

							if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
							{
								// [�α��߰� : Ȳ���� 2007. 9. 3] // ��Ƽ ���� ����.
								// param1 == ��Ƽ��ȣ.
								SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_END, 
									ret, (cltCharServer*)(pclCM->CR[ListUserCharID]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
									pclCM->CR[ ListUserCharID ]->siPartyIndex, 0, 0, 0, 0, NULL, NULL);
							}

							pclCM->CR[ ListUserCharID ]->siPartyIndex = 0;

							// [����] ������ : ������ ���� ��Ƽ�� �����ɰ�� ���縮���� �̵��Ѵ�
							pclPartyMgr->InPartyDungeonDeleteParty( ListUserCharID );

							/*
							if ( pclCM->CR[ListUserCharID]->GetMapIndex() >= MAPINDEX_DAEMADO )
							{
								// ��������� ���� ��Ų��. 
								OrderStop(id, BY_COMPUTER);

								cltWarpInfo clWarpInfo(1, MAPINDEX_DAEMADOGATE, false, false, 10, 30, -1, -1);
								((cltCharServer*)pclCM->CR[ListUserCharID])->SetWarpInfo(&clWarpInfo, 1054);
								// ������ ���� ��Ų��. 
								((cltCharServer*)pclCM->CR[ListUserCharID])->Warp();
							}
							*/
						}
					}
				}



				// ��Ƽ ����Ʈ���� ���ֱ�
				pclPartyMgr->DeleteParty( pTemp );


				return;					// ��Ƽ ���� �Ǿ����Ƿ�... �Ұ� ����.
		}
		break;

	case PARTY_CHANGE_LEADER:		// ���� ����� ��Ƽ���� �����Ƿ�... ��Ƽ�� ������ �˷���� ��
		{
			SI32 NewLeaderUserListIndex = siRet;
			SI32 NewLeaderPersonID = pTemp->GetPartyUser( 0 )->siPersonID;
			SI32 NewLeaderCharUnique = pTemp->GetPartyUser( 0 )->siCharUnique;

			// �� ������ �ü� ������... Ȥ�ó� �ؼ� ����ó��
			if ( NewLeaderUserListIndex < 0 )
			{
				return;
			}

			for ( SI16 i = 0; i < MAX_PARTY_USER_NUM; ++i )
			{
				if ( pTemp->GetPartyUser( i )->bPartyStatus )
				{
					SI32 CharUnique = pTemp->GetPartyUser( i )->siCharUnique;

					if ( CharUnique < 1 ) 
					{
						continue;
					}

					SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

					if ( CharID < 1 )
					{
						continue;
					}

					if ( pclCM->IsValidID( CharID ) == TRUE )
					{
						if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
						{
							continue;
						}

						// ������ �������� �˷���
						cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, pclCM->CR[id]->GetCharUnique() );
						cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
						pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsg1 );

						// ������ �ٲ������ �˷���
						cltGameMsgResponse_Party_ChangeLeader clGameMsgResponse_Party_ChangeLeader( NewLeaderUserListIndex, NewLeaderCharUnique );
						cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CHANGELEADER, sizeof( clGameMsgResponse_Party_ChangeLeader ), (BYTE*)&clGameMsgResponse_Party_ChangeLeader );
						pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsg );

					}
				}
			}

			// ��Ƽ���� �������
			if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
			{
				if(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
				{
					cltServer* pServer = (cltServer*) pclClient;
					pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(pclPartyLeave->siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
				}
			}	

			// �ڱ� �ڽ��� ��Ƽ���� �������� �˷���
			cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, pclCM->CR[id]->GetCharUnique() );
			cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1 );

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 9. 3] // ��Ƽ ���� ����. 
				// param1 == ��Ƽ ��ȣ.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_END, 
					ret, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					MyPartyUserListIndex, 0, 0, 0, 0, NULL, NULL);
			}


			/*
			if ( pclCM->CR[id]->GetMapIndex() >= MAPINDEX_DAEMADO )
			{
				//((cltCharServer*)pclCM->CR[id])->WarpToSafeZone() ;
				// ��������� ���� ��Ų��. 
				OrderStop(id, BY_COMPUTER);

				cltWarpInfo clWarpInfo(1, MAPINDEX_DAEMADOGATE, false, false, 10, 30, -1, -1);
				((cltCharServer*)pclCM->CR[id])->SetWarpInfo(&clWarpInfo, 1055);
				// ������ ���� ��Ų��. 
				((cltCharServer*)pclCM->CR[id])->Warp();
			}
			*/

				// cltGameMsgResponse_Party_ChangeLeader clGameMsgResponse_Party_ChangeLeader( ret, pclCM->CR[id]->GetCharUnique() );
		}
		break;

	default:						// ��Ƽ�� ������ �������Ƿ� �˷���� ��
		{
			for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
			{
				if ( ! pTemp->GetPartyUser( i )->bPartyStatus )
				{
					continue;
				}

				SI32 CharUnique = pTemp->GetPartyUser( i )->siCharUnique;

				if ( CharUnique < 1 )
				{
					continue;
				}

				SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

				if ( CharID < 1 )
				{
					continue;
				}

				if ( pclCM->IsValidID( CharID ) == TRUE )
				{
					if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
					{
						continue;
					}

					cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( siRet, pclCM->CR[id]->GetCharUnique() );
					cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
					pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsg );
				}
			}

			// ��Ƽ���� 3�� ������ ��쿡�� ��Ƽ����Ʈ�� ����˴ϴ�.
			if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
			{
				if(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
				{
					if(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->GetPartyUserNum() < m_pPartyQuestMgr->GetPartyQuestCategoryData(pclPartyMgr->GetPartyObj(pclPartyLeave->siPartyIndex)->m_PartyQuestInfo.m_siCategoryIndex)->m_siMinUser)
					{
						cltServer* pServer = (cltServer*) pclClient;
						pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(pclPartyLeave->siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
					}	
				}
			}	

			// �ڱ� �ڽ��� ��Ƽ���� �������� �˷���
			cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, pclCM->CR[id]->GetCharUnique() );
			cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1 );

			/*
			if ( pclCM->CR[id]->GetMapIndex() >= MAPINDEX_DAEMADO )
			{
				//((cltCharServer*)pclCM->CR[id])->WarpToSafeZone() ;
				// ��������� ���� ��Ų��. 
				OrderStop(id, BY_COMPUTER);

				cltWarpInfo clWarpInfo(1, MAPINDEX_DAEMADOGATE, false, false, 10, 30, -1, -1);
				((cltCharServer*)pclCM->CR[id])->SetWarpInfo(&clWarpInfo, 1056);
				// ������ ���� ��Ų��. 
				((cltCharServer*)pclCM->CR[id])->Warp();
			}
			*/

		}
		break;
	}

	return;
}

// ��Ƽ ��������  
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_FORCELEAVE( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Party_ForceLeave *pclForceLeave = (cltGameMsgRequest_Party_ForceLeave *) pclMsg->cData;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;


	SI32 toid = pclCM->GetIDFromCharUnique( pclForceLeave->siForceLeaveCharUnique );
	if ( pclCM->IsValidID(toid) == false ) return;

	SI32 ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
	if( ToPersonID < 1) return ;

	// �ڱ� �ڽ� ���� �ȵ�
	if ( ToPersonID == FromPersonID ) 
	{
		return;
	}

	// ���� ��Ƽ�� �ƴ϶��, �����ϸ� �ȵ� �Ƿ�...
	if ( pclCM->CR[ toid ]->siPartyIndex != pclForceLeave->siPartyIndex )
	{
		return;
	}

	CPartyObj *pTemp = pclPartyMgr->GetPartyObj( pclForceLeave->siPartyIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��Ƽ������ �ƴ��� üũ
	if( pTemp->GetSamePersonIDIndex( FromPersonID ) < 0 || pTemp->GetSamePersonIDIndex( ToPersonID ) < 0 )
	{
		return;
	}

	// ��Ƽ �������� Ȯ��(����� ������ �����ϹǷ�.. )
	if ( ! pTemp->IsPartyLeader( FromPersonID ) )
	{
		return;
	}

	// [����] ������ : ��Ƽ���� �������� ������ ��Ƽ ���� �Ұ�
	SI32 siMapIndex		= pclCM->CR[toid]->GetMapIndex();

	if ( pclMapManager->IsPartyMap( siMapIndex )  == true )
	{
		return;
	}

	// ĳ���� ���� ������Ʈ
	SI32 siPartyIndex = pclCM->CR[toid]->siPartyIndex;
	pclCM->CR[toid]->siPartyIndex = 0;

	SI32 ForcedLeaveUserIndex = pTemp->ForceLeaveParty( ToPersonID );

	if ( ForcedLeaveUserIndex < 0 )
	{
		return;
	}

	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( ! pTemp->GetPartyUser( i )->bPartyStatus )
		{
			continue;
		}

		SI32 CharUnique = pTemp->GetPartyUser( i )->siCharUnique;

		if ( CharUnique < 1 )
		{
			continue;
		}

		SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

		if ( CharID < 1 )
		{
			continue;
		}

		if ( pclCM->IsValidID( CharID ) == TRUE )
		{
			if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
			{
				continue;
			}

			cltGameMsgResponse_Party_ForceDelUser clGameMsgResponse_Party_ForceDelUser( ForcedLeaveUserIndex, pclCM->CR[toid]->GetCharUnique() );
			cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_FORCEDELUSER, sizeof( clGameMsgResponse_Party_ForceDelUser ), (BYTE*)&clGameMsgResponse_Party_ForceDelUser );
			pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsg );
		}
	}

	// ���� �Ǿ����� ����� �������� �˷���
	cltGameMsgResponse_Party_ForceDelUser clGameMsgResponse_Party_ForceDelUser( ForcedLeaveUserIndex, pclCM->CR[toid]->GetCharUnique() );
	cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_FORCEDELUSER, sizeof( clGameMsgResponse_Party_ForceDelUser ), (BYTE*)&clGameMsgResponse_Party_ForceDelUser );
	pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg1 );

	// ��Ƽ���� ����Ʈ�䱸 �ο� ������ ��쿡�� ��Ƽ����Ʈ�� ����˴ϴ�.
	if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
	{
		if(pclPartyMgr->GetPartyObj(pclForceLeave->siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
		{
			if(pTemp->GetPartyUserNum() < m_pPartyQuestMgr->GetPartyQuestCategoryData(pTemp->m_PartyQuestInfo.m_siCategoryIndex)->m_siMinUser)
			{
				cltServer* pServer = (cltServer*) pclClient;
				pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(siPartyIndex, toid, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
			}
		}
	}	

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 9. 3] // ��Ƽ ���� ����.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_FORCELEAVE, 
			0, (cltCharServer*)(pclCM->CR[toid]), NULL, FromPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			ForcedLeaveUserIndex, 0, 0, 0, 0, NULL, NULL);
	}

	if ( pTemp->GetPartyUserNum() < 2 )
	{
		cltGameMsgResponse_Party_Delete clGameMsgResponse_Party_Delete( pclForceLeave->siPartyIndex );
		cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_DELETE, sizeof( clGameMsgResponse_Party_Delete ), (BYTE*)&clGameMsgResponse_Party_Delete );
		pclCM->CR[ id ]->SendNetMsg((sPacketHeader*)&clMsg );

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 9] // ��Ƽ ���� ����.
			// param1 == ��Ƽ��ȣ.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_END, 
				0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclCM->CR[id]->siPartyIndex, 0, 0, 0, 0, NULL, NULL);
		}

		pclCM->CR[ id ]->siPartyIndex = 0;

		// ��Ƽ ����Ʈ���� ���ֱ�
		pclPartyMgr->DeleteParty( pTemp );
	}

	return;
}

// ��Ƽ ��ü ���� ����Ʈ ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_ALLUSERLIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Party_AllUserList *pclReqUserList = ( cltGameMsgRequest_Party_AllUserList* ) pclMsg->cData;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	CPartyObj *pTemp = pclPartyMgr->GetPartyObj( pclReqUserList->siPartyIndex );

	if ( pTemp == NULL )
	{
		return;
	}

	// ��û�� ����� ��Ƽ������ �ƴ��� üũ
	if( pTemp->GetSamePersonIDIndex( FromPersonID ) < 0 )
	{
		return;
	}

	for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
	{
		if ( ! pTemp->GetPartyUser( i )->bPartyStatus )
		{
			continue;
		}

		SI32 CharUnique = pTemp->GetPartyUser( i )->siCharUnique;

		if ( CharUnique < 1 )
		{
			continue;
		}

		SI32 CharID = pclCM->GetIDFromCharUnique( CharUnique );

		if ( CharID < 1 )
		{
			continue;
		}

		if ( pclCM->IsValidID( CharID ) == TRUE )
		{
			if ( pclCM->CR[ CharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
			{
				continue;
			}

			TCHAR *strName = (TCHAR*)pclCM->CR[ CharID ]->GetName();
			if ( strName == NULL )
			{
				continue;
			}			
			cltCharPos clCharPos( pclCM->CR[CharID]->GetMapIndex(),pclCM->CR[CharID]->GetX(),pclCM->CR[CharID]->GetY() );
			cltGameMsgResponse_Party_AddUser clGameMsgResponse_Party_AddUser( i, pclCM->CR[CharID]->GetCharUnique(), pTemp->GetPartyUser( i )->bIsPartyLeader, strName, pclCM->CR[CharID]->pclCI->clIP.GetLevel(), &clCharPos );
			cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_ADDUSER, sizeof( clGameMsgResponse_Party_AddUser ), (BYTE*)&clGameMsgResponse_Party_AddUser );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );			
		}
	}	
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTY_CHANGEITEMGETPATTERN(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Party_ChangeItemGetPattern* pclChangeItemGetPattern = (cltGameMsgRequest_Party_ChangeItemGetPattern*)pclMsg->cData;
	// ��Ƽ�� ���Ե� ������ �ƴ϶�� ��ȿ
	if(pclCM->CR[id]->siPartyIndex <=0) 	return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;


	CPartyObj *pPartyObj = pclPartyMgr->GetPartyObj( pclCM->CR[id]->siPartyIndex );
	if ( pPartyObj == NULL ) return;

	// ��û�� ����� ��Ƽ�������� �ƴ��� üũ
	if( pPartyObj->IsPartyLeader( FromPersonID ) == false )	return;

	SI16 siItemGetPattern = pclChangeItemGetPattern->siItemGetPattern;

	pPartyObj->SetItemGetPattern(siItemGetPattern);

	pPartyObj->NotifyItemGetPatternToPartyMember(siItemGetPattern );


	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ��Ƽ ���� ����.
		// param1 == ��Ƽ ��ȣ, param2 == ����.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PARTY, LOGCOMMAND_INDEX_PARTY_CHANGEITEMGETPATTERN, 
			0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			pPartyObj->GetPartyIndex(), siItemGetPattern, 0, 0, 0, NULL, NULL);
	}
	/*
	cltGameMsgResponse_Party_ChangeItemGetPattern clinfo(siItemGetPattern);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_CHANGEITEMGETPATTERN,sizeof(clinfo),(BYTE*)&clinfo);

	for(SI16 i = 0; i < MAX_PARTY_USER_NUM; i++)
	{
		stPartyUser* partyUser =  pPartyObj->GetPartyUser(i);

		// ��Ƽ���̸� �ٲ� ȹ�� ����� �˷��ش�.
		if(partyUser != NULL && partyUser->bPartyStatus )		// && partyUser->bIsPartyLeader == false)
		{
			if(pclCM->IsValidID(partyUser->siCharUnique) == false) continue;
			pclCM->CR[ partyUser->siCharUnique ]->SendNetMsg((sPacketHeader*)&clMsg );
		}		
	}    */
}


// [����] ���������� ������ �� �ִ��� Ȯ���ϴ� �Լ�
void cltServer::DoMsg_GAMEMSG_REQUEST_PIRATESHIP_ENTERFIELD(cltMsg* pclMsg,SI32 id)
{
	if ( pclClient->pclCM->IsAlive( id ) == false )
	{
		return;
	}

	SI32			siCharID	= id;
	cltCharServer*	pclChar		= (cltCharServer*)pclClient->pclCM->CR[ siCharID ];
	if ( pclChar == NULL )
	{
		return;
	}

	cltServer*		pclserver	= (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	SI32 siCondition		= MAPINDEX_PIRATESHIP+MAX_INSTANCE_MAP_NUMBER;
	SI32 siCanEnterMapIndex = 0;

	for ( SI32 siMapIndex=MAPINDEX_PIRATESHIP; siMapIndex<siCondition; siMapIndex++ )
	{
		// �δ��� ��� �ִ��� Ȯ���ϱ� ����
		siCanEnterMapIndex = pclClient->pclMapManager->GetEnterableInstanceMapIndex( siMapIndex, pclChar );

		// �̹� �ٸ� ��Ƽ�� �� �ִٸ�
		if ( siCanEnterMapIndex < 0 )
		{
			continue;
		}
		else if ( siCanEnterMapIndex == 0 )
		{
			// �̰��� ��Ƽ�� �ΰ� ���;� �ϴ� ���̴�
			pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_INSTANTDUNGEON_NO_PARTY, 0, 0, siCharID );
			return;
		}
		else
		{
			// ����ִ� �������� ���� ���� �������� Ȯ��
			if ( pclClient->pclMapManager->EnterInstanceMap( siCanEnterMapIndex, pclChar ) == true )
			{
				SI32		siWarpX = PIRATESHIP_START_POSITION_X + (rand() % 5);
				SI32		siWarpY = PIRATESHIP_START_POSITION_Y + (rand() % 5);
				cltWarpInfo clWarpPirateShip(1, siCanEnterMapIndex, false, false, siWarpX, siWarpY, -1, -1);

				pclChar->SetWarpInfo( &clWarpPirateShip, 1024 );
				pclChar->Warp();
				return;
			}
			else
			{
				// ���̻� ������ ��Ƽ ���� ����
				pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_INSTANTDUNGEON_OVER_PARTY_MAP, 0, 0, siCharID );
				return;
			}
		}
	}

	// ���̻� ������ ��Ƽ ���� ����
	pclserver->SendServerResponseMsg( 0, SRVAL_FAIL_INSTANTDUNGEON_OVER_PARTY_MAP, 0, 0, siCharID );

}


//KHY - 1113 - ũ�������� �̺�Ʈ - ����� �и� ���� ��Ű�� �Լ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_CHRISTMASEVET_ENTERFIELD(cltMsg* pclMsg,SI32 id)
{
	if ( pclClient->pclCM->IsAlive( id ) == false )
	{
		return;
	}

	SI32			siCharID	= id;
	cltCharServer*	pclChar		= (cltCharServer*)pclClient->pclCM->CR[ siCharID ];
	if ( pclChar == NULL )
	{
		return;
	}

	cltServer*		pclserver	= (cltServer*)pclClient;
	if ( pclserver == NULL )
	{
		return;
	}

	// ĳ���� ������ ã�´�.
	SI32 charlevel  = pclChar->pclCI->clIP.GetLevel();
	SI32 siCanEnterMapIndex = 0;

	if(charlevel <= 40)
	{
		siCanEnterMapIndex = MAPINDEX_SANTAFACTORY_1; // ������ ��Ÿ �۾���.
	}
	else if(charlevel > 30 && charlevel <= 80)
	{
		siCanEnterMapIndex = MAPINDEX_SANTAFACTORY_2; // û���� ��Ÿ �۾���.
	}		
	else if(charlevel > 80)
	{
		siCanEnterMapIndex = MAPINDEX_SANTAFACTORY_3; // ��� ��Ÿ �۾���.
	}

	// ��� ������� ��ǥ�� �����ϴ�.
	SI32		siWarpX = 56 + (rand() % 5);
	SI32		siWarpY = 89 + (rand() % 5);

	cltWarpInfo clWarpPirateShip(1, siCanEnterMapIndex, false, false, siWarpX, siWarpY, -1, -1);

	pclChar->SetWarpInfo( &clWarpPirateShip, 1024 );
	pclChar->Warp();

	return;
}


