
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\CommonLogic\Msg\MsgType-Friend.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Friend.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDALLLIST(sPacketHeader* pPacket)
{
	sDBResponse_FriendAllList * pclMsg = (sDBResponse_FriendAllList *)pPacket;

	SI32 id	= pclMsg->siCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;
	if(pclCM->CR[id]->pclFriendInfo == NULL)		return;

	pclCM->CR[id]->pclFriendInfo->Set(&pclMsg->clPFriendInfo);

	int		i;
	// ���� ���� �� ���� ������ �ִٸ�, CharID ���� �����
	for (i = 0 ; i < MAX_FRIEND_NUMBER; ++i )
	{
		if ( pclMsg->clPFriendInfo.clFriend[ i ].siPersonID > 0 )
		{
			SI32 CharID = pclCM->GetIDFromPersonID( pclMsg->clPFriendInfo.clFriend[ i ].siPersonID );
			if ( CharID > 0 )
			{
				// LEEKH TEMP CODE - ģ������ CharCommon���� �ű�
				pclCM->CR[id]->pclFriendInfo->Set( i, pclMsg->clPFriendInfo.siGroupID[i], CharID, true ,pclCM->CR[CharID]->pclCI->clBI.szAccountID);

				// ģ���� ģ������Ʈ���� �α����ߴٴ� ������ �ٲ������( �� �׷��� �α׾ƿ� �����̹Ƿ�... )
				for ( SI16 k = 0; k < MAX_FRIEND_NUMBER; ++k )
				{
					if ( pclCM->CR[CharID]->pclFriendInfo->clFriend[k].GetPersonID() > 0 && pclCM->CR[CharID]->pclFriendInfo->clFriend[k].GetPersonID() == pclCM->CR[id]->pclCI->GetPersonID() )
					{
						pclCM->CR[CharID]->pclFriendInfo->bConnectStatus[k] = true;
						pclCM->CR[CharID]->pclFriendInfo->siCharID[k] =id;

						break;
					}
				}

				// �α����� ��쿡�� �˸���.
				if(pclMsg->siLogin == 1)
				{
					// ģ������ �α��������� �˷���
					cltGameMsgResponse_FriendLogin clGameMsgResponse_FriendLogin( pclMsg->clPFriendInfo.siGroupID[i], pclCM->CR[id]->pclCI->GetPersonID(), id ,pclCM->CR[id]->pclCI->clBI.szAccountID);
					cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDLOGIN, sizeof( clGameMsgResponse_FriendLogin ), (BYTE*)&clGameMsgResponse_FriendLogin );
					pclCM->CR[CharID]->SendNetMsg((sPacketHeader*)&clMsg );
				}
			}
			else
			{
				// LEEKH TEMP CODE - ģ������ CharCommon���� �ű�
				pclCM->CR[id]->pclFriendInfo->Set( i, pclMsg->clPFriendInfo.siGroupID[i], 0, false ,pclMsg->clPFriendInfo.szAccountID[i]);
			}
		}
		else
		{
			// LEEKH TEMP CODE - ģ������ CharCommon���� �ű�
			pclCM->CR[id]->pclFriendInfo->Set( i, pclMsg->clPFriendInfo.siGroupID[i], 0, false ,pclMsg->clPFriendInfo.szAccountID[i]);
		}
	}

	// Ŭ���̾�Ʈ�� ���� ����
	cltGameMsgResponse_FriendAllList clinfo;
	clinfo.clFriendInfo.Set(pclCM->CR[id]->pclFriendInfo);

	cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDALLLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDADD(sPacketHeader* pPacket)
{
	sDBResponse_FriendAdd * pclMsg = (sDBResponse_FriendAdd *)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		return;
	}
	
	SI32 id = pclMsg->siCharID;
	if(pclCM->IsValidID(id) == false)		return;

	if ( pclMsg->siFromPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siToPersonID < 1 )
	{
		return;
	}

	if ( pclMsg->strToPersonName == NULL || _tcslen( pclMsg->strToPersonName ) < 1 )
	{
		return;
	}

	if(pclCM->CR[id]->pclFriendInfo == NULL)			return;

	SI16 i = 0;
	for (; i < MAX_FRIEND_NUMBER; ++i )
	{
		cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];
		
		if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
		{
			if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->strToPersonName ) == 0 )
			{
				// ģ�� ��Ͽ� ���� �����Ƿ� �߰��� �ʿ� ����.
				return;
			}
		}
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siFromPersonID )
	{
		// �������� ģ�� �߰� ����		
		for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];

			if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() < 1 )
			{
				pSimplePersonInfo->Set( pclMsg->siToPersonID, pclMsg->strToPersonName );
				break;
			}
		}
		
		if ( i < MAX_FRIEND_NUMBER )
		{
			// ģ���� ���° ����Ʈ�� �߰� �Ǿ����� �˷���
			cltGameMsgResponse_FriendAdd clinfo( FRIEND_GROUP_UNKNOWN, i, pclMsg->siToPersonID, pclMsg->strToPersonName );
			cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDADD, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDDEL(sPacketHeader* pPacket)
{
	sDBResponse_FriendDel *pclMsg = (sDBResponse_FriendDel *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}
	
	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siFromPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siToPersonID < 1 )
	{
		return;
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siFromPersonID )
	{
		if(pclCM->CR[id]->pclFriendInfo == NULL)			return;

		// �������� ģ�� ���� ����
		for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];

			if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclMsg->siToPersonID )
			{
				pSimplePersonInfo->Init();
				break;
			}
		}

		if ( i < MAX_FRIEND_NUMBER )
		{
			// ���° ����Ʈ�� �ִ� PersonID ��  �����Ǿ������� �˷���.
			cltGameMsgResponse_FriendDel clinfo( i, pclMsg->siToPersonID );
			cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDDEL, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDADDLIST(sPacketHeader* pPacket)
{
	sDBResponse_FriendAddList *pclMsg = (sDBResponse_FriendAddList*)pPacket;


	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if( pclMsg->siFromPersonID < 1 || pclMsg->siFromCharID < 1 )
	{
		if( pclMsg->siToPersonID > 0 || pclMsg->siToCharID > 0 )
		{
			cltCharServer* pclChar = pclCM->GetCharServer(pclMsg->siToCharID);
			if( pclChar ) 
			{
				SI32 i = 0;
				// ģ�� ����Ʈ ��Ͽ� �ִ��� ������ üũ
				for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
				{
					cltSimplePerson *pSimplePersonInfo = &pclChar->pclFriendInfo->clFriend[i];

					if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
					{
						if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->strFromPersonName ) == 0 )
						{
							// ģ�� ��Ͽ� ���� �����Ƿ� �߰��� �ʿ� ����.
							break;
						}
					}
				}

				// ģ�� ��Ͽ� �����Ƿ�, �߰��� ��.
				if ( i == MAX_FRIEND_NUMBER )
				{
					// �������� ģ�� �߰� ����		
					for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
					{
						cltSimplePerson *pSimplePersonInfo = &pclChar->pclFriendInfo->clFriend[i];

						if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() < 1 )
						{
							pclChar->pclFriendInfo->Set( i, pclMsg->siFromGroupID, pclMsg->siFromPersonID, 0, pclMsg->strFromPersonName, false ,TEXT(""));
							break;
						}
					}
				}
			}
		}
		return;
	}

	if( pclMsg->siToPersonID < 1 || pclMsg->siToCharID < 1 )
	{
		return;
	}

	SI32 id1 = pclMsg->siFromCharID;
	SI32 id2 = pclCM->GetIDFromPersonID( pclMsg->siToPersonID );

	//---------------------------------------------------------------
	// ģ���� ��ϵǾ����� 2���� �˷���
	SI16 i = 0;
	if ( pclCM->IsValidID(id1) && pclCM->CR[id1]->pclCI->GetPersonID() == pclMsg->siFromPersonID )
	{
		if(pclCM->CR[id1]->pclFriendInfo)
		{
			for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id1]->pclFriendInfo->clFriend[i];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
				{
					if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->strToPersonName ) == 0 )
					{
						// ģ�� ��Ͽ� ���� �����Ƿ� �߰��� �ʿ� ����.
						break;
					}
				}
			}

			// ģ�� ��Ͽ� �����Ƿ�, �߰��� ��.
			if ( i == MAX_FRIEND_NUMBER )
			{
				// �������� ģ�� �߰� ����		
				for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
				{
					cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id1]->pclFriendInfo->clFriend[i];
					
					if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() < 1 )
					{
						if(  id2 > 0 )
						{
							pclCM->CR[id1]->pclFriendInfo->Set( i, pclMsg->siToGroupID, pclMsg->siToPersonID, id2, pclMsg->strToPersonName, true ,pclCM->CR[id2]->pclCI->clBI.szAccountID);
							StringCchCopy(m_szFriendAccountID, MAX_PLAYER_NAME, pclCM->CR[id2]->pclCI->clBI.szAccountID);
						}
						else
						{
							pclCM->CR[id1]->pclFriendInfo->Set( i, pclMsg->siToGroupID, pclMsg->siToPersonID, 0, pclMsg->strToPersonName, false ,m_szFriendAccountID);
						}
						break;
					}
				}

				// ģ���� �߰��� ��쿡 �˷���� �ϹǷ�...
				if ( i < MAX_FRIEND_NUMBER )
				{
					// ģ���� ���° ����Ʈ�� �߰� �Ǿ����� �˷���
					cltGameMsgResponse_FriendAddAccept clinfo( i, pclMsg->siToGroupID, pclMsg->siToPersonID, id2, pclMsg->strToPersonName ,m_szFriendAccountID);
					cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDADDACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id1]->SendNetMsg((sPacketHeader*)&clMsg);
					
					// LEEKH MODIFY 2007.10.25
					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 9. 3] // ģ�� ��� ����. 
						// param1 == ģ�� �߰� ��ġ, param2 == �׷� ���̵�
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FRIEND, LOGCOMMAND_INDEX_FRIEND_ADD, 
					 						0, (cltCharServer*)(pclCM->CR[id1]), NULL, pclMsg->siToPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											i, pclMsg->siToGroupID, 0, 0, 0, NULL, NULL);
					}

					cltLetterMsg_AcceptFriend_Result clletter( cltLetterMsg_AcceptFriend_Result::ACCEPTFRIEND, pclMsg->strToPersonName );
					// ������ DB�� Ŭ���̾�Ʈ���� ������. 
					SendLetterMsg( pclCM->CR[id1]->pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
				}
			}
		}
	}

	if ( pclCM->IsValidID(id2) && pclCM->CR[id2]->pclCI->GetPersonID() == pclMsg->siToPersonID )
	{
		if(pclCM->CR[id2]->pclFriendInfo)
		{
			// ģ�� ����Ʈ ��Ͽ� �ִ��� ������ üũ
			for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id2]->pclFriendInfo->clFriend[i];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
				{
					if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->strFromPersonName ) == 0 )
					{
						// ģ�� ��Ͽ� ���� �����Ƿ� �߰��� �ʿ� ����.
						break;
					}
				}
			}
		
			// ģ�� ��Ͽ� �����Ƿ�, �߰��� ��.
			if ( i == MAX_FRIEND_NUMBER )
			{
				// �������� ģ�� �߰� ����		
				for ( i = 0; i < MAX_FRIEND_NUMBER; ++i )
				{
					cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id2]->pclFriendInfo->clFriend[i];
					
					if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() < 1 )
					{
						if ( pclCM->IsValidID(id1) )
						{
							pclCM->CR[id2]->pclFriendInfo->Set( i, pclMsg->siFromGroupID, pclMsg->siFromPersonID, pclMsg->siFromCharID, pclMsg->strFromPersonName, true ,pclCM->CR[id1]->pclCI->clBI.szAccountID);
						}
						else
						{
							pclCM->CR[id2]->pclFriendInfo->Set( i, pclMsg->siFromGroupID, pclMsg->siFromPersonID, 0, pclMsg->strFromPersonName, false ,TEXT(""));
						}
						break;
					}
				}
				
				// ģ���� �߰� ���� �˷���.
				if ( i < MAX_FRIEND_NUMBER )
				{
					// ģ���� ���° ����Ʈ�� �߰� �Ǿ����� �˷���
					cltGameMsgResponse_FriendAddAccept clinfo( i, pclMsg->siFromGroupID, pclMsg->siFromPersonID, pclMsg->siFromCharID, pclMsg->strFromPersonName,pclCM->CR[id1]->pclCI->clBI.szAccountID );
					cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDADDACCEPT, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id2]->SendNetMsg((sPacketHeader*)&clMsg);

					// LEEKH MODIFY 2007.10.25
					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [�α��߰� : Ȳ���� 2007. 9. 3] // ģ�� ��� ����. 
						// param1 == ģ�� �߰� ��ġ, param2 == �׷� ���̵�
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FRIEND, LOGCOMMAND_INDEX_FRIEND_ADD, 
											0, (cltCharServer*)(pclCM->CR[id2]), NULL, pclMsg->siFromPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											i, pclMsg->siFromGroupID, 0, 0, 0, NULL, NULL);
					}

					cltLetterMsg_AcceptFriend_Result clletter( cltLetterMsg_AcceptFriend_Result::ACCEPTFRIEND, pclMsg->strFromPersonName );
					// ������ DB�� Ŭ���̾�Ʈ���� ������. 
					SendLetterMsg( pclCM->CR[id2]->pclCI->GetPersonID(), (cltLetterHeader*)&clletter);
				}
			}
		}
	}
	//---------------------------------------------------------------


	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDDELLIST(sPacketHeader* pPacket)
{
	sDBResponse_FriendDelList *pclMsg = (sDBResponse_FriendDelList*)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( pclMsg->siFromPersonID < 1 || pclMsg->siToPersonID < 1 )
	{
		return;
	}

	SI32 FromID = pclMsg->siFromCharID;
	
	// ���� ���� ����� �����ϴ� ���( �˷���� �ϹǷ� )
	SI32 ToID = pclCM->GetIDFromPersonID( pclMsg->siToPersonID );
	if ( ToID > 0 )
	{	
		if(pclCM->CR[ToID]->pclFriendInfo)
		{
			// �������� ģ�� ���� ����
			for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				cltSimplePerson *pSimplePersonInfo = &pclCM->CR[ToID]->pclFriendInfo->clFriend[ i ];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclMsg->siFromPersonID )
				{
					pclCM->CR[ToID]->pclFriendInfo->Init( i );
					break;
				}
			}

			if ( i < MAX_FRIEND_NUMBER )
			{
				// ���° ����Ʈ�� �ִ� PersonID ��  �����Ǿ������� �˷���.
				cltGameMsgResponse_FriendDel clinfo( i, pclMsg->siFromPersonID );
				cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDDEL, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[ToID]->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 9] // ģ�� ���� ����. 
					// param1 == ����Ʈ ��ȣ.
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FRIEND, LOGCOMMAND_INDEX_FRIEND_DEL, 
						0, (cltCharServer*)(pclCM->CR[ToID]), NULL, pclMsg->siFromPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						i, 0, 0, 0, 0, NULL, NULL);
				}
			}
		}
	}

	// ���� ��û�� ����� �����ϴ� ���( �˷���� �ϹǷ� )
	if ( pclCM->IsValidID(FromID) && pclCM->CR[FromID]->pclCI->GetPersonID() == pclMsg->siFromPersonID )
	{
		if(pclCM->CR[FromID]->pclFriendInfo)
		{
			// �������� ģ�� ���� ����
			for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				cltSimplePerson *pSimplePersonInfo = &pclCM->CR[FromID]->pclFriendInfo->clFriend[ i ];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclMsg->siToPersonID )
				{
					pclCM->CR[FromID]->pclFriendInfo->Init( i );
					break;
				}
			}

			if ( i < MAX_FRIEND_NUMBER )
			{
				// ���° ����Ʈ�� �ִ� PersonID ��  �����Ǿ������� �˷���.
				cltGameMsgResponse_FriendDel clinfo( i, pclMsg->siToPersonID );
				cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDDEL, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[FromID]->SendNetMsg((sPacketHeader*)&clMsg);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 9] // ģ�� ���� ����.
					// param1 == ����Ʈ ��ȣ.
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FRIEND, LOGCOMMAND_INDEX_FRIEND_DEL, 
						0, (cltCharServer*)(pclCM->CR[FromID]), NULL, pclMsg->siToPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
						i, 0, 0, 0, 0, NULL, NULL);
				}
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDMEMO(sPacketHeader* pPacket)
{
	sDBResponse_FriendMemo *pclMsg = (sDBResponse_FriendMemo*)pPacket;

	if ( pclMsg->siResult < 1 )
		return;

	if ( pclCM->IsValidID( pclMsg->siCharID ) )
	{
		cltGameMsgResponse_FriendMemo clinfo( pclMsg->szFriendMemo );
		cltMsg clMsg(GAMEMSG_RESPONSE_FRIENDMEMO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[pclMsg->siCharID]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDMEMOSET(sPacketHeader* pPacket)
{
	sDBResponse_FriendMemoSet *pclMsg = (sDBResponse_FriendMemoSet*)pPacket;

	if ( pclCM->IsValidID( pclMsg->siCharID ) == false ) 
		return;

	bool bSuccess = false;

    if ( pclMsg->siResult == 1 )
		bSuccess = true;

	cltGameMsgResponse_FriendMemoSet clinfo( bSuccess );
	cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDMEMOSET, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[pclMsg->siCharID]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDCHANGEGROUP(sPacketHeader* pPacket)
{
	sDBResponse_FriendChangeGroup *pclMsg = (sDBResponse_FriendChangeGroup*)pPacket;

	if ( pclCM->IsValidID( pclMsg->siCharID ) == false ) 
		return;

	if ( pclMsg->siResult != 1 )
		return;

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siToPersonID < 1 )
	{
		return;
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siFromPersonID )
	{
		if(pclCM->CR[id]->pclFriendInfo)
		{
			// �������� ģ���� �׷��� �ٲ�
			for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				cltSimplePerson *pSimplePersonInfo = &pclCM->CR[id]->pclFriendInfo->clFriend[i];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() == pclMsg->siToPersonID )
				{
					pclCM->CR[id]->pclFriendInfo->siGroupID[i] = pclMsg->siGroupID;
					break;
				}
			}

			if ( i < MAX_FRIEND_NUMBER )
			{
				// ���° ����Ʈ�� �ִ� PersonID �� �׷�ID�� ����Ǿ����� �˷���.
				cltGameMsgResponse_FriendChangeGroup clinfo( i, pclMsg->siGroupID, pclMsg->siToPersonID );
				cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDCHANGEGROUP, sizeof(clinfo), (BYTE*)&clinfo );
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_FRIENDCHANGEGROUPNAME(sPacketHeader* pPacket)
{
	sDBResponse_FriendChangeGroupName *pclMsg = (sDBResponse_FriendChangeGroupName*)pPacket;

	if ( pclCM->IsValidID( pclMsg->siCharID ) == false ) 
		return;

	bool bSuccess = false;

	if ( pclMsg->siResult == 1 )
		bSuccess = true;

	cltGameMsgResponse_FriendChangeGroupName clinfo( bSuccess );
	for(int i=0; i<MAX_FRIEND_GROUP; i++)
		MStrCpy(clinfo.szGroupName[i], pclMsg->strGroupName[i], MAX_FRIEND_GROUPNAME);

	cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDCHANGEGROUPNAME, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[pclMsg->siCharID]->SendNetMsg((sPacketHeader*)&clMsg);
}