#include "PartyMgr.h"
#include "PartyObj.h"

#include "..\SMLib\LibList\LibList.h"

#include "..\Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"


#include "..\CommonLogic\Msg\MsgType-Party.h"

#include "..\CommonLogic\CommonLogic.h"

#include "../common/Char/CharServer/Char-Server.h"
#include "../../Server/Server.h"
#include "../client/ninterface/npartydlg/NPartyDlg.h"

//--------------------------------------
// Common
//--------------------------------------
#include "PersonInfo.h"

extern cltCommonLogic *pclClient;

CPartyMgr::CPartyMgr() : CLibListMgr()
{
	Initialize();
	CreateMaxEmptyObj();
}

CPartyMgr::~CPartyMgr()
{
	Destroy();
}

void CPartyMgr::Initialize()
{
	return;
}

void CPartyMgr::Destroy()
{
	return;
}

void CPartyMgr::CreateMaxEmptyObj()
{
	CPartyObj *pTemp = NULL;

	for ( int i = 0; i < MAX_PARTY_OBJ_NUM; ++i )
	{
		pTemp = new CPartyObj( i + 1 );		// ��Ƽ ������ ���� �ε����� �ο��ؼ� �� �� ȿ�������� �����ϱ� ���ؼ�
		PushBackToEmptyList( pTemp );
	}

	return;
}

void CPartyMgr::Action()
{
	static clock_t PreClock = 0;

	if( TABS( pclClient->CurrentClock - PreClock ) < 10000 )
	{
		return;
	}

	PreClock = pclClient->CurrentClock;

	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		pTemp->NotifyExp();
			
		// ��ȿ�� ��Ƽ�� �������� ��Ƽ����Ʈ�� �ð��� �ɷ��ִٸ�
		if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching))
		{
			cltServer* pServer = (cltServer*) pclClient;

			if(pTemp->GetPartyIndex() > 0 && pTemp->m_PartyQuestInfo.m_bGoingQuest == true && pTemp->m_PartyQuestInfo.m_siTimeLimit > 0)
			{
				// �ð�����
				if(TABS(pTemp->m_dwEndTime) <= TABS(pclClient->CurrentClock))
				{
					pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(pTemp->GetPartyIndex(), 0, PARTYQUEST_MESSAGE_TIMEOUT);
				}
				else
				{
					// 1�и��� �����ð��� �����ݴϴ�.	
					if(TABS(pclClient->CurrentClock - pTemp->m_dwElapseTime) > 30 * 1000)
					{
						pServer->m_pPartyQuestMgr->UpdatePartyQuestTime(pTemp->GetPartyIndex(), &pTemp->m_PartyQuestInfo);
						pTemp->m_dwElapseTime = pclClient->CurrentClock;
					}
				}
			}
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return;
}

SI32 CPartyMgr::CreateParty( SI32 PersonID, SI32 CharUnique, SI32 Level )
{
	CPartyObj *pTemp = (CPartyObj *)PopFrontToEmptyListAndPushBackToExistList();

	if ( pTemp == NULL )		// ��Ƽ ���� �ʰ�
	{
		return -1;
	}

	pTemp->Initialize();		// ������ ������ ������ ���� �ʱ�ȭ ��Ŵ.

	return pTemp->CreateParty( PersonID, CharUnique, Level );	// ��Ƽ �ε����� ��������
}

/*
// ���ε� ��ġ(m_stPartyUserList[index]�� index��)�� ������.
SI16 CPartyMgr::JoinParty( SI32 FromPersonID, SI32 CharUnique, SI32 PartyIndex )
{
	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsSamePartyIndex( PartyIndex ) )
		{			
			return pTemp->JoinParty( FromPersonID, CharUnique );
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return -1;			// ��Ƽ�� �������� �ʰų�, ��Ƽ���� �ƴ� ����� �������� �ߴ� ���
}
*/

SI16 CPartyMgr::LeaveParty( SI32 PersonID, SI32 PartyIndex, SI32 *pRet )
{
	cltServer* pServer = (cltServer*) pclClient;

	if ( PartyIndex < 1 )
	{
		return -1;
	}

	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsSamePartyIndex( PartyIndex ) )
		{
			SI32 CharUnique = pTemp->GetCharUnique( PersonID );
			
			if ( CharUnique < 1 )
			{
				return -1;
			}
			
			SI32 id = pclClient->pclCM->GetIDFromCharUnique( CharUnique );

			if ( id < 1 )
			{
				return -1;
			}

			if ( pclClient->pclCM->CR[ id ]->pclCI->GetPersonID() != PersonID )
			{
				return -1;
			}

			SI16 MyPartyUserListIndex = pTemp->GetPartyUserListIndex( CharUnique );

			if ( MyPartyUserListIndex < 0 )			// ���� ��Ƽ�� ����Ʈ�� ����.
			{
				return -1;
			}

			SI16 Ret = pTemp->LeaveParty( PersonID, pRet );

			if ( Ret < 0 )
			{
				return -1;
			}

			SI32 siPartyIndex = pclClient->pclCM->CR[id]->siPartyIndex;

			pclClient->pclCM->CR[id]->siPartyIndex = 0;			// ĳ���� ���� ������Ʈ


			switch ( Ret )
			{
			case PARTY_DELETE:				// ��Ƽ ����
				{
					if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
					{
						if(GetPartyObj(siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
						{
							if(GetPartyObj(siPartyIndex)->GetPartyUserNum() <  pServer->m_pPartyQuestMgr->GetPartyQuestCategoryData(GetPartyObj(siPartyIndex)->m_PartyQuestInfo.m_siCategoryIndex)->m_siMinUser)
							{
								pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
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

							SI32 ListUserCharID = pclClient->pclCM->GetIDFromCharUnique( ListUserCharUnique );

							if ( ListUserCharID < 1 )
							{
								continue;
							}

							if ( pclClient->pclCM->IsValidID( ListUserCharID ) == TRUE )
							{
								if ( pclClient->pclCM->CR[ ListUserCharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
								{
									continue;
								}

								cltGameMsgResponse_Party_Delete clGameMsgResponse_Party_Delete( PartyIndex );
								cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_DELETE, sizeof( clGameMsgResponse_Party_Delete ), (BYTE*)&clGameMsgResponse_Party_Delete );
								pclClient->pclCM->CR[ ListUserCharID ]->SendNetMsg((sPacketHeader*)&clMsg );

								pclClient->pclCM->CR[ListUserCharID]->siPartyIndex = 0;

								InPartyDungeonDeleteParty( ListUserCharID );
							}
						}
					}

					
					/*
					// ������ �������� �˷���
					cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( *pRet, CharUnique );
					cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1 );
					*/

					pTemp->Initialize();
					GetExistList()->Pop( pTemp );
					PushBackToEmptyList( pTemp );
					return PARTY_DELETE;
				}
				break;

			case PARTY_CHANGE_LEADER:		// ��Ƽ�� ����
				{
					SI32 NewLeaderUserListIndex = *pRet;
					SI32 NewLeaderPersonID = pTemp->GetPartyUser( 0 )->siPersonID;
					SI32 NewLeaderCharUnique = pTemp->GetPartyUser( 0 )->siCharUnique;

					// �� ������ �ü� ������... Ȥ�ó� �ؼ� ����ó��
					if ( NewLeaderUserListIndex < 0 )
					{
						return -1;
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

							SI32 ListUserCharID = pclClient->pclCM->GetIDFromCharUnique( ListUserCharUnique );

							if ( ListUserCharID < 1 )
							{
								continue;
							}

							if ( pclClient->pclCM->IsValidID( ListUserCharID ) == TRUE )
							{
								if ( pclClient->pclCM->CR[ ListUserCharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
								{
									continue;
								}

								// ������ �������� �˷���
								cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, CharUnique );
								cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
								pclClient->pclCM->CR[ListUserCharID]->SendNetMsg((sPacketHeader*)&clMsg1 );

								// ������ �ٲ������ �˷���
								cltGameMsgResponse_Party_ChangeLeader clGameMsgResponse_Party_ChangeLeader( NewLeaderUserListIndex, NewLeaderCharUnique );
								cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_CHANGELEADER, sizeof( clGameMsgResponse_Party_ChangeLeader ), (BYTE*)&clGameMsgResponse_Party_ChangeLeader );
								pclClient->pclCM->CR[ListUserCharID]->SendNetMsg((sPacketHeader*)&clMsg );
							}
						}
					}
					
					// ��Ƽ���� �������
					if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
					{
						if(GetPartyObj(siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
						{
							pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
						}
					}	


					// �ڱ� �ڽ��� ��Ƽ���� �������� �˷���
					cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, CharUnique );
					cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1 );


					return PARTY_CHANGE_LEADER;
				}
				break;

			default:						// ��Ƽ�� �Ѹ� ����
				{
					for ( SI32 i = 0; i < MAX_PARTY_USER_NUM; ++i )
					{
						if ( ! pTemp->GetPartyUser( i )->bPartyStatus )
						{
							continue;
						}

						SI32 ListUserCharUnique = pTemp->GetPartyUser( i )->siCharUnique;

						if ( ListUserCharUnique < 1 )
						{
							continue;
						}

						SI32 ListUserCharID = pclClient->pclCM->GetIDFromCharUnique( ListUserCharUnique );

						if ( ListUserCharID < 1 )
						{
							continue;
						}

						if ( pclClient->pclCM->IsValidID( ListUserCharID ) == TRUE )
						{
							if ( pclClient->pclCM->CR[ ListUserCharID ]->pclCI->GetPersonID() != pTemp->GetPartyUser( i )->siPersonID )
							{
								continue;
							}

							cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( *pRet, CharUnique );
							cltMsg clMsg( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
							pclClient->pclCM->CR[ListUserCharID]->SendNetMsg((sPacketHeader*)&clMsg );
						
						}
					}

					// ��Ƽ���� 3�� ������ ��쿡�� ��Ƽ����Ʈ�� ����˴ϴ�.
					if(pclClient->IsCountrySwitch(Switch_PartyQuest_PartyMatching) == true)
					{
						if(GetPartyObj(siPartyIndex)->m_PartyQuestInfo.m_bGoingQuest == true)
						{
							if(GetPartyObj(siPartyIndex)->GetPartyUserNum() < pServer->m_pPartyQuestMgr->GetPartyQuestCategoryData(GetPartyObj(siPartyIndex)->m_PartyQuestInfo.m_siCategoryIndex)->m_siMinUser)
							{
								pServer->m_pPartyQuestMgr->DoGiveUpPartyQuest(siPartyIndex, id, PARTYQUEST_MESSAGE_FAILED_LESS_USER);
							}	
						}
					}	

					// �ڱ� �ڽ��� ��Ƽ���� �������� �˷���
					cltGameMsgResponse_Party_DelUser clGameMsgResponse_Party_DelUser( MyPartyUserListIndex, CharUnique );
					cltMsg clMsg1( GAMEMSG_RESPONSE_PARTY_DELUSER, sizeof( clGameMsgResponse_Party_DelUser ), (BYTE*)&clGameMsgResponse_Party_DelUser );
					pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1 );

					return PARTY_USER_LEAVE;
				}
				break;
			}
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return -1;
}

/*
// ��Ƽ���� ��Ƽ���� ���� ���� ��Ŵ
SI16 CPartyMgr::ForceLeaveParty( SI32 FromPersonID, SI32 ToPersonID, SI32 PartyIndex )
{
	if ( FromPersonID == ToPersonID )		// �ڱ� �ڽ��� ���� ��ų�� ����.
	{
		return -1;
	}

	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		// FromPersonID �� ��Ƽ������ Ȯ��
		if ( pTemp->IsSamePartyIndex( PartyIndex ) && pTemp->IsPartyLeader( FromPersonID ) )
		{
			SI16 ForcedLeaveUserListIndex = pTemp->ForceLeaveParty( ToPersonID );

			if (  ForcedLeaveUserListIndex < 0 )		// ���� ������ ���� ���� ��Ű����.
			{
				return -1;
			}
			else
			{
				return ForcedLeaveUserListIndex;
			}
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}
	
	return -1;	// ��Ƽ�� �������� �ʰų�, ��Ƽ���� �ƴϹǷ� �����Ҽ� ����.
}
*/


CPartyObj *CPartyMgr::GetPartyObj( SI32 PartyIndex )
{
	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsSamePartyIndex( PartyIndex ) )
		{
			return pTemp;
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return NULL;
}

// ��Ƽ��ȣ�� FromPersondID �� ��Ƽ������ Ȯ��
bool CPartyMgr::IsPartyLeader( SI32 FromPersonID, SI32 PartyIndex )
{
	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsSamePartyIndex( PartyIndex ) && pTemp->IsPartyLeader( FromPersonID ) )
		{
			return true;
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return false;
}

bool CPartyMgr::IsPartyMember( SI32 siPersionID, SI32 siPartyIndex )
{
	CPartyObj* pclPartyObj = GetPartyObj( siPartyIndex );
	if ( NULL == pclPartyObj )
	{
		return false;
	}

	if ( 0 <= pclPartyObj->GetSamePersonIDIndex(siPersionID) )
	{
		return true;
	}

	return false;

}

bool CPartyMgr::IsEmptyUserListExist( SI32 PartyIndex )
{
	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		if ( pTemp->IsSamePartyIndex( PartyIndex ) && pTemp->IsEmptyUserListExist() )
		{
			return true;
		}

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return false;
}

void CPartyMgr::DeleteParty( CPartyObj *pObj )
{
	pObj->Initialize();
	GetExistList()->Pop( pObj );
	PushBackToEmptyList( pObj );
	
	return;
}

UI32 CPartyMgr::GetPartyNum()
{
	return GetExistList()->GetObjNum();
}

UI32 CPartyMgr::GetPartyTotalUserNum()
{
	UI32 TotalPartyUserNum = 0;

	CPartyObj *pTemp = (CPartyObj *)GetExistList()->GetFirst();
	
	while( pTemp )
	{
		TotalPartyUserNum += pTemp->GetPartyUserNum();

		pTemp = (CPartyObj *)pTemp->GetNext();
	}

	return TotalPartyUserNum;
}

void CPartyMgr::IncreaseExp( SI32 PartyIndex, SI32 PersonID, SI32 Exp )
{
	CPartyObj *pTemp = GetPartyObj( PartyIndex );
	
	if ( pTemp == NULL )
	{
		return;
	}

	pTemp->IncreaseExp( PersonID, Exp );

	return;
}

void CPartyMgr::InPartyDungeonDeleteParty( SI32 siCharID )
{
	if ( pclClient->pclCM->IsValidID( siCharID ) == false )
	{
		return;
	}

	cltCharServer *pclChar = (cltCharServer*)pclClient->pclCM->CR[ siCharID ];
	if ( pclChar == NULL )
	{
		return;
	}
	
	SI32 siMapIndex	= pclChar->GetMapIndex();

	if ( pclClient->pclMapManager->IsPartyMap( siMapIndex ) == true )
	{
		if ( pclClient->pclCM->IsAlive( siCharID ) == FALSE )
		{
			pclChar->siKilledMode = 0;
		}	
		else
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);
			pclChar->SetWarpInfo(&clWarpInfo, 56);
			pclChar->Warp();
		}
	}
	
}

SI32 CPartyMgr::CountQuestPalyUserNum( SI32 siPartyIndex, SI32 siClearCondition )
{
	CPartyObj *pclPartyObj = GetPartyObj( siPartyIndex );
	if ( NULL == pclPartyObj )
	{
		return 0;
	}

	SI32			siReturnCount	= 0;
	cltCharCommon*	pclchar			= NULL;
	stPartyUser*	pstUser			= NULL;
	
	for ( SI32 siIndex=0; siIndex<MAX_PARTY_USER_NUM; siIndex++ )
	{
		pstUser = pclPartyObj->GetPartyUser( siIndex );
		if ( NULL == pstUser )
		{
			continue;
		}

		if ( (false == pstUser->bPartyStatus) || (0 >= pstUser->siCharUnique) )
		{
			continue;
		}

		pclchar = pclClient->pclCM->GetChar( pstUser->siCharUnique );
		if ( NULL == pclchar )
		{
			continue;
		}

		if ( true == pclchar->pclCI->clQuestInfo.IsQuestGoing(siClearCondition) )
		{
			siReturnCount++;
		}
	}

	return siReturnCount;

}