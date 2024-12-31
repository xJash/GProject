//---------------------------------
// 2004/2/18 ���°�
//---------------------------------
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Friend.h"

#include "..\Common\Order\Order.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-Friend.h"

#include "../../Lib/HashTable/HashTable_StringInt.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDADD( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendAdd* pclinfo = (cltGameMsgRequest_FriendAdd*)pclMsg->cData;

	StringCchCopy(m_szFriendAccountID, MAX_PLAYER_NAME,TEXT(""));

	if( pclCM->IsAlive( id ) == false )return ;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	if ( pclinfo->strFriendName == NULL || _tcslen( pclinfo->strFriendName ) < 1 )
	{
		return;
	}


	TCHAR *strName = (TCHAR*)pclCM->CR[id]->GetName();
	if ( strName == NULL )
	{
		return;
	}

	// �ڱ� �ڽ��� �߰� �� �� ����.
	if ( _tcscmp( strName, pclinfo->strFriendName ) == 0 )
	{
		return;
	}

	if(pclCM->CR[id]->pclFriendInfo == NULL)		return;

	// ������ ��Ͽ� �ִ��� üũ
	cltSimplePerson* pSimplePersonInfo = NULL;
	for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
	{
		pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];
		
		if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
		{
			if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclinfo->strFriendName ) == 0 )
			{
				// ģ�� ��Ͽ� �����Ƿ� �߰��� �ʿ� ����.
				return;
			}
		}
	}

	/*
	sDBRequest_FriendAdd clMsg( 
		FromPersonID, 
		id, 
		pclinfo->strFriendName
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	*/
	
	//----------------------------------------------------
	// Hash ���̺��� �̸����� �˻��ؼ� PersonID �� CharID �� �޾ƿ�
	// false �� ���� �Ǵ� ���� ������ ���� ���ӵ��� ���� ������
	SI32 ToPersonID, ToCharID;
	if ( pclHashTable->Find( pclinfo->strFriendName, ToPersonID, ToCharID , 50) == false  )
	{
		SendServerResponseMsg(0, SRVAL_FRIEND_NOTCONNECTED,  0, 0, id);
		return;
	}
	//----------------------------------------------------
	
	if( pclCM->IsValidID(ToCharID) == false )	return;

	cltCharServer *pclChar = ( cltCharServer * )pclCM->CR[ToCharID];

	// ģ�� �߰� �ź� ����
	if ( pclChar->bFriendAddReject )
	{
		SendServerResponseMsg(0, SRVAL_FRIENDADD_REJECT,  0, 0, id);
		return;
	}
	
	
	StringCchCopy(m_szFriendAccountID, MAX_PLAYER_NAME, pclCM->CR[id]->pclCI->clBI.szAccountID);
	
	// ģ���� �߰��ϱ⸦ ���ϴ� �������� �߰� ��û ����
	cltGameMsgResponse_FriendAdd clGameMsgResponse_FriendAdd( pclinfo->siGroupID, id, FromPersonID, strName );
	cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDADD, sizeof( clGameMsgResponse_FriendAdd ), (BYTE*)&clGameMsgResponse_FriendAdd );
	pclCM->CR[ToCharID]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDDEL( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendDel* pclinfo = (cltGameMsgRequest_FriendDel*)pclMsg->cData;
	
	if(pclCM->IsAlive(id) == false)return ;
	
	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	if ( pclinfo->siPersonID < 1 )
	{
		return;
	}

	if(pclCM->CR[id]->pclFriendInfo == NULL)		return;

	SI16 i = 0;
	cltSimplePerson* pSimplePersonInfo = NULL;
	for (; i < MAX_FRIEND_NUMBER; ++i )
	{
		pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];
		
		if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclinfo->siPersonID )
		{
			break;
		}
	}

	// ������ �� �ִ� PersonID �� �߰� �� �� ����.
	if ( i == MAX_FRIEND_NUMBER )
	{
		return;
	}

	sDBRequest_FriendDelList clMsg( 
		FromPersonID, 
		id, 
		pclinfo->siPersonID
		);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

// ģ�� �߰��� ���ؼ� accept �� �Դٸ�, ������ �ϰ� �׳� ģ�� �߰� ��.
// �ֳ��ϸ�, ���� �Ǿ �����Ͱ� ���ƿ´ٰ� �ص� �� ���� �ȵɵ�...
void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDADDACCEPT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendAddAccept* pclinfo = (cltGameMsgRequest_FriendAddAccept*)pclMsg->cData;
	
	if( pclCM->IsAlive( id ) == false )
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1 )
		return ;
	
	// accept �� �� ���� ������ �ϰ� �Ѿ. �Ʒ� if ������ üũ�ϴ� ����, �߰��Ǵ� ������ �����ε�...
	// ���� �� ������ ���ٰ� �ؼ� ģ�� �߰��� �� �ȴٸ�... �̻���...
	// ex) ģ�� �߰� ��û�� 10������ �޾Ҵµ�... �� �� �ڸ��� ��� accept �� ���ϴٰ�,
	// 10�еڿ� �ͼ� �߰� �Ҷ� �� ����� ���ٰ� ģ�� �߰��� �ȵǸ� �̻����ݾ�??
	//if ( pclCM->IsValidID ( pclinfo->siCharID ) && pclCM->CR[ pclinfo->siCharID ]->pclCI->GetPersonID() == 
	
	if ( pclinfo->strCharName == NULL || _tcslen( pclinfo->strCharName ) < 1 )
	{
		return;
	}


	if ( pclCM->CR[id]->GetName() == NULL || _tcslen( pclCM->CR[id]->GetName() ) < 1 )
	{
		return;
	}

	// �ڱ� �ڽ��� �߰� �� �� ����
	if ( _tcscmp( pclinfo->strCharName, pclCM->CR[id]->GetName() ) == 0 )
	{
		return;
	}

	if( pclCM->CR[id]->pclFriendInfo == NULL )				return;

	// ������ ��Ͽ� �ִ��� üũ
	cltSimplePerson* pSimplePersonInfo = NULL;
	for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
	{
		pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];
		
		if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
		{
			if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclinfo->strCharName ) == 0 )
			{
				// ģ�� ��Ͽ� �����Ƿ� �߰��� �ʿ� ����.
				return;
			}
		}
	}

	sDBRequest_FriendAddList clMsg( pclinfo->siGroupID, FromPersonID, id, (TCHAR*)pclCM->CR[id]->GetName(), FRIEND_GROUP_UNKNOWN, pclinfo->siPersonID, pclinfo->siCharID, pclinfo->strCharName );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_REJECTFRIENDADD( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendAddAccept* pclinfo = (cltGameMsgRequest_FriendAddAccept*)pclMsg->cData;

	if( pclCM->IsValidID(id) == false )
		return;

	if( 0 > pclinfo->siPersonID )
		return;

	cltLetterMsg_AcceptFriend_Result clletter( cltLetterMsg_AcceptFriend_Result::REJECTFRIEND, (TCHAR*)pclCM->CR[id]->GetName() );
	// ������ DB�� Ŭ���̾�Ʈ���� ������. 
	SendLetterMsg( pclinfo->siPersonID, (cltLetterHeader*)&clletter);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDLIST( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsAlive( id ) == false )
		return;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1 )
		return ;

	if(pclCM->CR[id]->pclFriendInfo == NULL)		return;

	SI32 mapindex[MAX_FRIEND_NUMBER] = {0,};
	SI32 level[MAX_FRIEND_NUMBER] = {0,};
	SI32 homemapindex[MAX_FRIEND_NUMBER] = {0,};
	SI32 charkind[MAX_FRIEND_NUMBER] = {0,};
	cltSimpleRank clcharRank[MAX_FRIEND_NUMBER];
	UI08 gRank[MAX_FRIEND_NUMBER] = {0,};


	cltCharCommon* pclchar = NULL;
	for( SI32 i=0 ; i<MAX_FRIEND_NUMBER ; i++ )
	{
		SI32 friendid = pclCM->GetIDFromPersonID(pclCM->CR[id]->pclFriendInfo->clFriend[i].GetPersonID());

		if ( pclCM->IsValidID( friendid ) == false  )
			continue;

		pclchar = pclCM->CR[friendid];

		if ( pclchar )
		{
			mapindex[i] = pclchar->GetMapIndex();
			level[i] = pclchar->pclCI->clIP.GetLevel();
			homemapindex[i] = pclchar->pclCI->clBI.siHomeVillage;
			charkind[i] = pclchar->GetKind();
			clcharRank[i].Set( &pclchar->pclCI->clCharRank );
			gRank[i] = pclchar->pclCI->clBI.uiGRank;
		}
	}

#ifdef _SAFE_MEMORY
	cltGameMsgResponse_FriendList clinfo( &pclCM->CR[id]->pclFriendInfo->siGroupID[0], &pclCM->CR[id]->pclFriendInfo->clFriend[0], mapindex, level, homemapindex, charkind, clcharRank, gRank );
#else
	cltGameMsgResponse_FriendList clinfo( pclCM->CR[id]->pclFriendInfo->siGroupID, pclCM->CR[id]->pclFriendInfo->clFriend, mapindex, level, homemapindex, charkind, clcharRank, gRank );
#endif
	cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDLIST, sizeof( cltGameMsgResponse_FriendList ), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDMEMO(cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID( id ) ==  false )
		return;

	cltGameMsgRequest_FriendMemo* pclinfo = (cltGameMsgRequest_FriendMemo*)pclMsg->cData;

	sDBRequest_FriendMemo clMsg( pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siFriendPersonID, id );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDMEMOSET(cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	cltGameMsgRequest_FriendMemoSet* pclinfo = (cltGameMsgRequest_FriendMemoSet*)pclMsg->cData;

	sDBRequest_FriendMemoSet clMsg( pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siFriendPersonID, pclinfo->szFriendMemo, id );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDCHANGEGROUP( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendChangeGroup* pclinfo = (cltGameMsgRequest_FriendChangeGroup*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)return ;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	if ( pclinfo->siFriendPersonID < 1 )
	{
		return;
	}

	if( pclCM->CR[id]->pclFriendInfo == NULL )			return;

	SI16 i = 0;
	cltSimplePerson* pSimplePersonInfo = NULL;
	for (; i < MAX_FRIEND_NUMBER; ++i )
	{
		pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];

		if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclinfo->siFriendPersonID )
		{
			break;
		}
	}

	// �׷��� ������ �� �ִ� PersonID �� �߰� �� �� ����.
	if ( i == MAX_FRIEND_NUMBER )
	{
		return;
	}

	sDBRequest_FriendChangeGroup clMsg( 
		FromPersonID, 
		id, 
		pclinfo->siGroupID,
		pclinfo->siFriendPersonID
		);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDCHANGEGROUPNAME( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FriendChangeGroupName* pclinfo = (cltGameMsgRequest_FriendChangeGroupName*)pclMsg->cData;

	if(pclCM->IsAlive(id) == false)return ;

	SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( FromPersonID < 1) return ;

	sDBRequest_FriendChangeGroupName clMsg( 
		FromPersonID, 
		id
		);

	for(int i=0; i<MAX_FRIEND_GROUP; i++)
		MStrCpy(clMsg.strGroupName[i], pclinfo->szGroupName[i], MAX_FRIEND_GROUPNAME);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}