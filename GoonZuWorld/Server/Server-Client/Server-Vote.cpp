#include "Char\CharManager\CharManager.h"
#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Vote.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-Vote.h"

#include "..\Common\VoteMgr\VoteMgr.h"
#include "../common/VoteMgr/VoteBaseInfo.h"
#include "../common/VoteMgr/VoteStatusMgr.h"


void cltServer::DoMsg_GAMEMSG_REQUEST_VOTEKINGSELECTION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_VoteKingSelection* pclinfo = (cltGameMsgRequest_VoteKingSelection*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)return ;
	
	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;
	
	// ��ǥ�� ���� 40 �̸��� ���� �Ұ���
	if ( pclCM->CR[id]->pclCI->clIP.GetLevel() < Const_CanVote_MinLevel )
	{
		return;
	}

	// �ĺ��ڴ� 1~MAX_CANDIDATURE_NUM ������ ��ȣ�� ������ ����.
	if ( pclinfo->siListIndex < 1 || pclinfo->siListIndex > MAX_CANDIDATURE_NUM )
	{
		return;
	}
	
	// ������ ��ǥ �س���, �� ��ǥ �ϴ� ��� ( ���� �ϸ� �����ϹǷ�... )
	if ( pclCM->CR[id]->pclCI->clBI.siVoteKingSelectionIndex > 0 )
	{
		return;
	}
	
	sDBRequest_VoteKingSelection clMsg(
		FromPersonID, 
		id, 
		pclinfo->siListIndex
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	// ���� ���ſ� ��ǥ�� �ϴ� ����Ʈ �����̾��ٸ� üũ

	pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_VOTEKING);


	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_STARTELECTIONSTUMP( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_StartElectionStump* pclinfo = (cltGameMsgRequest_StartElectionStump*)pclMsg->cData;
	if ( pclinfo == NULL )
	{
		return;
	}

	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	// ���� �����Ⱓ�� �ƴ϶�� ������
	if ( false == bVoteCampaign )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}
	
	// ���� �����߿��� ���� ���� ���Ѵ�
	if ( (pclChar->bPersonalShopSwitch == true) || (pclChar->bPersonalShopSwitch == true) )
	{
		return;
	}

	// �̹� �������̶�� ���� �ʿ� ���µ�
	if ( pclChar->bIsElectionStump == true )
	{
		return;
	}

	// �ĺ��ڸ�/���������� ������ ���°��� �ִٸ�
	if ( (_tcscmp( pclinfo->m_tszCandidate, TEXT("") ) == 0)
		|| (_tcscmp( pclinfo->m_tszMaintenance, TEXT("") ) == 0)
	)
	{
		return;
	}

	SI32 siCharID		= id;
	SI32 siPersonID		= pclChar->pclCI->GetPersonID();

	SI32 siStumpUnique	= ITEMUNIQUE(24080);
	SI32 siStumpNumber	= 1;
	SI32 siStumpPosition = pclChar->pclCI->clCharItem.GetItemPos( siStumpUnique );

	// �����̿�� �������� �κ���ġ�� �̻��� ���̶��
	if ( (siStumpPosition<PERSONITEM_INV0) || (siStumpPosition>=MAX_ITEM_PER_PERSON) )
	{
		return;
	}
	
	// �����̿�� �������� ������ 1���� ���ٸ�
	if ( pclChar->pclCI->clCharItem.clItem[ siStumpPosition ].siItemNum < siStumpNumber )
	{
		return;
	}

	// ���� ���� ����
	pclChar->bIsElectionStump = true;

	StringCchCopy( pclChar->szCandidate, Const_Max_Candidate, pclinfo->m_tszCandidate );
	pclChar->szCandidate[Const_Max_Candidate-1] = '\0';

	StringCchCopy( pclChar->szMaintenance, Const_Max_Maintenance, pclinfo->m_tszMaintenance );
	pclChar->szMaintenance[Const_Max_Maintenance-1] = '\0';

	// ����â�� �����
	pclChar->SetHeadChat( false, NULL );

	// �����̿���� ����ϵ����Ѵ�
	cltItem clStumpItem;

	clStumpItem.Set( &pclChar->pclCI->clCharItem.clItem[ siStumpPosition ] );
	clStumpItem.siItemNum = siStumpNumber;

	sDBRequest_UseItem clMsgUseItem( siCharID, siPersonID, siStumpPosition, &clStumpItem, USEITEM_REASON_NONE );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsgUseItem);

	// �̿��鿡�� ���ʸ� ��쵵�� �Ѵ�
	cltGameMsgResponse_StartElectionStump clMsgElectionStump( pclChar->GetCharUnique(), pclinfo->m_tszCandidate, pclinfo->m_tszMaintenance );
	cltMsg clMsg(GAMEMSG_RESPONSE_STARTELECTIONSTUMP, sizeof(clMsgElectionStump), (BYTE*)&clMsgElectionStump);
	pclChar->SendNeighbourMsg( &clMsg, true );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_ENDELECTIONSTUMP( cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}

	// �����ߵ� �ƴѵ� �ߴ��� �ʿ����
	if ( pclChar->bIsElectionStump == false )
	{
		return;
	}

	pclChar->bIsElectionStump = false;
	StringCchCopy( pclChar->szCandidate,	Const_Max_Candidate,	TEXT("") );
	StringCchCopy( pclChar->szMaintenance,	Const_Max_Maintenance,	TEXT("") );
	
	cltGameMsgResponse_EndElectionStump clMsgEnd( pclChar->GetCharUnique() );
	cltMsg clMsg(GAMEMSG_RESPONSE_ENDELECTIONSTUMP, sizeof(clMsgEnd), (BYTE*)&clMsgEnd);
	pclChar->SendNeighbourMsg( &clMsg, true );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ELECTIONSTUMP( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_ElectionStump* pclinfo = (cltGameMsgRequest_ElectionStump*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	SI32 siCharID = pclCM->GetIDFromCharUnique(pclinfo->m_siCharUnique);
	if ( false == pclCM->IsValidID(siCharID) )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siCharID];
	if ( NULL == pclchar )
	{
		return;
	}

	if ( false == pclchar->bIsElectionStump )
	{
		return ;
	}

	cltGameMsgResponse_StartElectionStump clMsgElectionStump( pclinfo->m_siCharUnique, pclchar->szCandidate, pclchar->szMaintenance );
	cltMsg clMsg(GAMEMSG_RESPONSE_STARTELECTIONSTUMP, sizeof(clMsgElectionStump), (BYTE*)&clMsgElectionStump);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

// [����] ���� �ý��� : ��ǥ�� �������� �̵��ض�
void cltServer::DoMsg_GAMEMSG_REQUEST_WARPTOPOLLMAP( cltMsg* pclMsg, SI32 id )
{
	// ���� ���� ��ǥ���� �ƴ϶�� �� �ʿ� ����
	if ( pclVoteMgr->IsPlayStatus() == false )
	{
		return;
	}

	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}
	
	SI32 siMapIndex = pclChar->GetMapIndex();
	// Ȥ�� ���� �ִ� ���� ��ǥ�� �����̶�� �� ������ �ʿ䰡 ������?
	if ( Const_MapIndex_PollMap == siMapIndex )
	{
		return;
	}

	// ���λ����� ������ ���¿����� �̵��� �ȵȴ�
	if ( (true == pclChar->bPersonalShopSwitch) || (true == pclChar->bPremiumPersonalShop) )
	{
		return;
	}

	
	// �����Ǿ� �ִ� ���¶�� �̵��� �ȵȴ�.
	if ( pclChar->clInnerStatus.IsStatus(INNERSTATUS_PRISON) )
	{
		return;
	}

	
	SI32		siWarpX = 26;
	SI32		siWarpY = 38;
	cltWarpInfo clWarpPollMap(1, Const_MapIndex_PollMap, true, false, siWarpX, siWarpY, -1, -1);

	pclChar->SetWarpInfo( &clWarpPollMap, 905 );
	pclChar->Warp();

}

void cltServer::DoMsg_GAMEMSG_REQUEST_VOTEKINGAVAILABLE( cltMsg* pclMsg, SI32 id )
{
	// ���� ���� ��ǥ���� �ƴ϶�� ��ǥ�� �ʿ� ����
	if ( pclVoteMgr->IsPlayStatus() == false )
	{
		return;
	}

	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}
	
	// �̹� ��ǥ�� �ߴ�
	if ( pclChar->pclCI->clBI.siVoteKingSelectionIndex > 0 )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_REASON_ALREADYVOTE, 0, 0, pclChar->GetID() );
		return;
	}
	
	// ��ǥ�� �� �� ���� �����̶��
	if ( pclChar->pclCI->clIP.GetLevel() < Const_CanVote_MinLevel )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_REASON_DONOTARRIVELEVLE, 0, 0, pclChar->GetID() );
		return;
	}

	cltGameMsgResponse_VoteKingAvailable clVoteKing( pclVoteMgr->GetVoteExplain(), pclVoteMgr->GetCandidatureList() );
	cltMsg clMsg( GAMEMSG_RESPONSE_VOTEKINGAVAILABLE, sizeof(clVoteKing), (BYTE*)&clVoteKing );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_STARTVOTESTATUS( cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsAlive(id) == false )
	{
		return;
	}

	cltCharServer* pclChar = (cltCharServer*)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}


	cltGameMsgResponse_StartVoteStatus clMsgStartVoteStatus( 
		(TCHAR**)pclVoteStatusMgr->m_tszCandidateName
		,pclVoteStatusMgr->m_siCandidateNum
		,pclVoteStatusMgr->m_siTotalVote
		,pclVoteStatusMgr->m_siTopVoteNum
	);
	cltMsg clMsg( GAMEMSG_RESPONSE_STARTVOTESTATUS, sizeof(clMsgStartVoteStatus), (BYTE*)&clMsgStartVoteStatus);
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );

}