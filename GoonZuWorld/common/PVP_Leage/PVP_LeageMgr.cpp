#include "PVP_LeageMgr.h"


#include "../Common/CommonHeader.h"
#include "../CommonLogic/CommonLogic.h"
#include "../../Server/Server.h"
#include "../../NLib/NUtil.h"

#include "../Char/CharServer/Char-Server.h"
#include "../Char/CharManager/CharManager.h"
#include "../Char/CharCommon/Char-Common.h"

#include "../common/Event/event.h"

#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../CommonLogic/MsgType-Person.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "MsgType-System.h"

//========================================================================================
// CPVP_Leage_List
//========================================================================================
CPVP_Leage_List::CPVP_Leage_List()
{
	Init();
}

CPVP_Leage_List::~CPVP_Leage_List()
{
}

void CPVP_Leage_List::Init()
{
	for (SI32 i = 0 ; i<MAX_RESERVE_PERSON; i++) 
	{
		m_clPVP_LeageReserveList[i].InitPVP_LeagueData();
	}
}

SI32 CPVP_Leage_List::Add( SI32 siPersonID, SI16 siGrade )		// ���ฮ��Ʈ�� �ѻ���� �߰��Ѵ�
{
	if ( 0 >= siPersonID )							return PVP_LEAGUE_APPLY_RESULT_NONE;

	// �̹� ��ϵ� �����̴�.
	if ( 0 <= GetPersonIndex(siPersonID) )			return PVP_LEAGUE_APPLY_RESULT_ALREADY;

	// ����� ã��
	SI32 siEmptyPos = -1;
	for(SI32 i=0; i<MAX_RESERVE_PERSON; i++)
	{
		if( m_clPVP_LeageReserveList[i].GetPersonID() <= 0 )
		{
			siEmptyPos = i;
			break;
		}
	}
	// ���̻� ������ ����.
	if ( siEmptyPos < 0 )							return PVP_LEAGUE_APPLY_RESULT_FULL;

	// ���� ����Ʈ�� ��� ��Ų��
	m_clPVP_LeageReserveList[siEmptyPos].SetPVP_LeagueData( siPersonID, siGrade, PVP_LEAGUE_RESERVE_STATUS_POSSIBLE );

	// �α� ���
	return PVP_LEAGUE_APPLY_RESULT_SUCCESS;
}

void CPVP_Leage_List::Delete( SI32 siPersonID )					// ���ฮ��Ʈ���� Ư�� ����� ����
{
	if ( 0 >= siPersonID )				return;

	SI32 siIndex = GetPersonIndex( siPersonID );
	if( 0 <= siIndex )
	{
		m_clPVP_LeageReserveList[siIndex].InitPVP_LeagueData();
	}
}

SI32 CPVP_Leage_List::GetPersonIndex( SI32 siPersonID )
{
	if ( 0 >= siPersonID )				return -1;

	for ( SI32 i=0; i< MAX_RESERVE_PERSON; ++i )
	{
		if ( true == m_clPVP_LeageReserveList[i].IsSamePersonID(siPersonID) )
		{
			return i;
		}
	}

	return -1;
}

SI32 CPVP_Leage_List::GetPersonID(SI32 siIndex)
{
	if( siIndex < 0 || siIndex >= MAX_RESERVE_PERSON )		return 0;
	return m_clPVP_LeageReserveList[siIndex].GetPersonID();
}

SI32 CPVP_Leage_List::GetCount()
{
	SI32	siCount = 0;

	for ( SI32 i=0; i< MAX_RESERVE_PERSON; ++i )
	{
		if ( false == m_clPVP_LeageReserveList[i].IsEmpty() )
		{
			siCount++;
		}
	}

	return siCount;
}

void CPVP_Leage_List::ArrangeList()
{
#ifdef _SAFE_MEMORY
	NSafeTArray<CPVP_Leage_ListData, MAX_RESERVE_PERSON>	clPVP_LeageReserveList	;	//	PVP_League	����Ʈ
#else
	CPVP_Leage_ListData				clPVP_LeageReserveList[MAX_RESERVE_PERSON]	;	//	PVP_League	����Ʈ
#endif

	SI32	i;
	// ��ü ����
	for(i=0; i<MAX_RESERVE_PERSON; i++)				{	clPVP_LeageReserveList[i].SetPVP_LeagueData( &m_clPVP_LeageReserveList[i] );	}
	// ��ü ����
	for (i = 0 ; i<MAX_RESERVE_PERSON; i++)			{	m_clPVP_LeageReserveList[i].InitPVP_LeagueData();								}

	// �����͸� �ٽ� ä��
	SI32	siIndex = 0;
	for(i=0; i<MAX_RESERVE_PERSON; i++)
	{
		if( false == clPVP_LeageReserveList[i].IsEmpty() )
		{
			if( siIndex >= MAX_RESERVE_PERSON )			continue;
			m_clPVP_LeageReserveList[siIndex++].SetPVP_LeagueData( &clPVP_LeageReserveList[i] );
		}
	}
}

void CPVP_Leage_List::DeleteNoPossiblePerson()				// ��Ī�� ������ �ʴ� ������ �����Ѵ�.
{
	for(SI32 i=0; i<MAX_RESERVE_PERSON; i++)
	{
		if( m_clPVP_LeageReserveList[i].IsEmpty() )			continue;

		// ����Ʈ�� ���� �� ���� ���¶�� ����Ʈ���� ���� ������
		if ( PVP_LEAGUE_RESERVE_STATUS_POSSIBLE != m_clPVP_LeageReserveList[i].GetSatus() )
		{
			m_clPVP_LeageReserveList[i].InitPVP_LeagueData();
		}
	}

	ArrangeList();
}

void CPVP_Leage_List::SetStatus(SI32 siPersonID, SI32 siStatus)
{
	SI32 siIndex = GetPersonIndex( siPersonID );
	if( siIndex >= 0 )
	{
		m_clPVP_LeageReserveList[siIndex].SetSatus( siStatus );
	}
}

SI32 CPVP_Leage_List::FindMatchPerson(SI32 siPersonID)
{
	if( 0 >= siPersonID )					return 0;

	SI32 siIndex = GetPersonIndex( siPersonID );
	if( siIndex < 0 )						return 0;

	SI32 siSourceGrade		= m_clPVP_LeageReserveList[siIndex].GetGrade();
	SI32 siSourcePersonID	= m_clPVP_LeageReserveList[siIndex].GetPersonID();
	SI32 siDestPersonID		= 0;
	SI32 siGradeGab			= PVP_LEAGUE_GRADE_MAX;

	for ( SI32 i=0; i<MAX_RESERVE_PERSON; ++i )
	{
		if ( true == m_clPVP_LeageReserveList[siIndex].IsEmpty() )		continue;		// �������
		if ( m_clPVP_LeageReserveList[i].GetPersonID() == siPersonID)	continue;		// �ڱ� �ڽŰ��� �ο� �� ����

		SI32 siTempPersonID	= m_clPVP_LeageReserveList[i].GetPersonID();
		SI32 siDestGrade	= m_clPVP_LeageReserveList[i].GetGrade();
		SI32 siTempGeb		= siGradeGab;

		// ���ϰ��� �ϴ� ����� ����� ���ٸ� �ٷ� ��Ī ����Ʈ��
		if ( siSourceGrade == siDestGrade )
		{
			if ( true == CPVP_LeagueMgr::IsValidPerson(siSourcePersonID, siTempPersonID) )
			{
				siDestPersonID	= siTempPersonID;
				break;
			}
		}
		// �� ����� ���� �ȿ� �ִ� ������� �˻�
		else if ( true == CPVP_LeagueMgr::CheckTheGrade(siSourceGrade, siDestGrade, &siTempGeb) )
		{
			if ( true == CPVP_LeagueMgr::IsValidPerson(siSourcePersonID, siTempPersonID) )
			{
				siDestPersonID	= siTempPersonID;
				siGradeGab		= siTempGeb;
			}
		}
	}

	return siDestPersonID;
}

void CPVP_Leage_List::SendToAgainReserveQuestion( void )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )			return;

	for ( SI32 siIndex=0; siIndex<MAX_RESERVE_PERSON; ++siIndex )
	{
		// �۽� ���̵� ���ٸ� �� ����Ʈ
		SI32 siGetPersonID = m_clPVP_LeageReserveList[siIndex].GetPersonID();
		if ( 0 >= siGetPersonID )		continue;

		// ���� ĳ���� ���̵� ��ȿ���� �ʴٸ� �׻���� ���� ����̶�� ���� ����
		SI32 siGetCharID = pclserver->pclCM->GetIDFromPersonID( siGetPersonID );
		if ( false == pclserver->pclCM->IsValidID(siGetCharID) )
		{
			m_clPVP_LeageReserveList[siIndex].InitPVP_LeagueData();
			continue;
		}

		// �޽����� ������ ��
		pclserver->SendServerResponseMsg( 0, SRVAL_PVP_LEAGUE_AGAIN_RESERVE, 0, 0, siGetCharID );

		// ���¸� ���� �����·� �����Ѵ�
		m_clPVP_LeageReserveList[siIndex].SetSatus( PVP_LEAGUE_RESERVE_STATUS_READYFORRESPON );
	}
}

//========================================================================================
// CPVP_Leage_MatchingList
//========================================================================================
CPVP_Leage_MatchingList::CPVP_Leage_MatchingList()
{
	Init();
}

CPVP_Leage_MatchingList::~CPVP_Leage_MatchingList()
{
}

void CPVP_Leage_MatchingList::Init()
{
	for (SI32 i = 0 ; i<MAX_MATCHING_PERSON; i++) 
	{
		m_clPVP_LeageMatchingList[i].InitPVP_Leage_MatchingListData();
	}
}

bool CPVP_Leage_MatchingList::Add( SI32 siSourcePersonID, SI32 siDestPersonID, SI32 siTotalScore )
{
	SI32	siEmptyIndex = -1;
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_LeageMatchingList[i].IsEmpty() == true )
		{
			siEmptyIndex = i;
			break;
		}
	}

	if( siEmptyIndex < 0 )			return false;

	m_clPVP_LeageMatchingList[siEmptyIndex].SetPVP_Leage_MatchingListData(siSourcePersonID,
		siDestPersonID,
		CPVP_LeagueMgr::GetTotalScore(siSourcePersonID, siDestPersonID));
	return true;
}

SI32 CPVP_Leage_MatchingList::GetIndex( SI32 siSourcePersonID, SI32 siDestPersonID )
{
	SI32	siRetIndex = -1;
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_LeageMatchingList[i].IsMatch(siSourcePersonID, siDestPersonID) == true )
		{
			siRetIndex = i;
			break;
		}
	}

	return siRetIndex;
}

SI32 CPVP_Leage_MatchingList::GetBattlePersonIDHome( SI32 siIndex )
{
	if( siIndex < 0 || siIndex >= MAX_MATCHING_PERSON )		return 0;
	return m_clPVP_LeageMatchingList[siIndex].GetBattlePersonIDHome();
}

SI32 CPVP_Leage_MatchingList::GetBattlePersonIDAway( SI32 siIndex )
{
	if( siIndex < 0 || siIndex >= MAX_MATCHING_PERSON )		return 0;
	return m_clPVP_LeageMatchingList[siIndex].GetBattlePersonIDAway();
}

SI32 CPVP_Leage_MatchingList::FindPersonID( SI32 siPersonID )
{
	SI32	siRetIndex = -1;
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_LeageMatchingList[i].GetBattlePersonIDHome() == siPersonID ||
			m_clPVP_LeageMatchingList[i].GetBattlePersonIDAway() == siPersonID )
		{
			siRetIndex = i;
			break;
		}
	}

	return siRetIndex;
}

SI32 CPVP_Leage_MatchingList::FindEnemyPersonID( SI32 siPersonID )
{
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_LeageMatchingList[i].GetBattlePersonIDHome() == siPersonID )
			return m_clPVP_LeageMatchingList[i].GetBattlePersonIDAway();
		if( m_clPVP_LeageMatchingList[i].GetBattlePersonIDAway() == siPersonID )
			return m_clPVP_LeageMatchingList[i].GetBattlePersonIDHome();
	}

	return 0;
}

bool CPVP_Leage_MatchingList::Delete( SI32 siSourcePersonID, SI32 siDestPersonID )
{
	SI32 siIndex = GetIndex(siSourcePersonID, siDestPersonID);
	if(siIndex < 0)			return false;

	m_clPVP_LeageMatchingList[siIndex].InitPVP_Leage_MatchingListData();

	return true;
}

SI32 CPVP_Leage_MatchingList::GetCount()
{
	SI32 siRetCount = 0;
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_LeageMatchingList[i].IsEmpty() == false )
		{
			siRetCount++;
			break;
		}
	}
	return siRetCount;
}

bool CPVP_Leage_MatchingList::IsFull()
{
	return GetCount() == MAX_MATCHING_PERSON;
}

int score_compare( const void *arg1, const void *arg2 )
{
	CPVP_Leage_MatchingListData*	pParam1 = (CPVP_Leage_MatchingListData*)arg1;
	CPVP_Leage_MatchingListData*	pParam2 = (CPVP_Leage_MatchingListData*)arg2;

	if( pParam1->GetScore() > pParam2->GetScore() )			return -1;
	else if( pParam1->GetScore() == pParam2->GetScore() )	return 0;
	else													return 1;
}

void CPVP_Leage_MatchingList::SortByTotalScore()
{
	qsort(&m_clPVP_LeageMatchingList[0], MAX_MATCHING_PERSON, sizeof(CPVP_Leage_MatchingListData), score_compare);
}

// ù��° ��Ī����Ʈ�� ������� �������� �Ѵ�.
void CPVP_Leage_MatchingList::NoticeSpecialNews()
{
	if ( true == m_clPVP_LeageMatchingList[0].IsEmpty() )		return;

	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )									return;

	SI32			siHomePersonID	= m_clPVP_LeageMatchingList[0].GetBattlePersonIDHome();
	SI32			siHomeCharID	= pclserver->pclCM->GetIDFromPersonID( siHomePersonID );
	cltCharServer*	pclHomeChar		= pclserver->pclCM->GetCharServer( siHomeCharID );
	if ( NULL == pclHomeChar )									return;

	SI32			siAwayPersonID	= m_clPVP_LeageMatchingList[0].GetBattlePersonIDAway();
	SI32			siAwayCharID	= pclserver->pclCM->GetIDFromPersonID( siAwayPersonID );
	cltCharServer*	pclAwayChar		= pclserver->pclCM->GetCharServer( siAwayCharID );
	if ( NULL == pclAwayChar )									return;

	NTCHARString64	strTitle	= GetTxtFromMgr(9581);
	NTCHARString256 strNews		= GetTxtFromMgr(9633);
	strNews.Replace( TEXT("#user1#"), pclHomeChar->GetName() );
	strNews.Replace( TEXT("#user2#"), pclAwayChar->GetName() );

	pclserver->PushSpecialNews( strNews, strTitle, NULL, CAPTIONKIND_NEWS, CAPTIONKIND_NEWSCHAT );
}

void CPVP_Leage_MatchingList::NoticeStartPVP()
{
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 siIndex=0; siIndex<MAX_MATCHING_PERSON; siIndex++ )
	{
		SI32			siHomePersonID	= m_clPVP_LeageMatchingList[siIndex].GetBattlePersonIDHome();
		SI32			siHomeCharID	= pclserver->pclCM->GetIDFromPersonID( siHomePersonID );
		cltCharServer*	pclHomeChar		= pclserver->pclCM->GetCharServer( siHomeCharID );
		if ( NULL == pclHomeChar )			continue;

		SI32			siAwayPersonID	= m_clPVP_LeageMatchingList[siIndex].GetBattlePersonIDAway();
		SI32			siAwayCharID	= pclserver->pclCM->GetIDFromPersonID( siAwayPersonID );
		cltCharServer*	pclAwayChar		= pclserver->pclCM->GetCharServer( siAwayCharID );
		if ( NULL == pclAwayChar )			continue;

		cltGameMsgResponse_PVP_Request clHome( PVP_LEAGUESTART ,0 , 0, TEXT("") );	
		cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clHome), (BYTE*)&clHome );
		pclHomeChar->SendNeighbourMsg(&clMsg, true);

		cltGameMsgResponse_PVP_Request clAway( PVP_LEAGUESTART ,0 , 0, TEXT("") );	
		cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAway), (BYTE*)&clAway );
		pclAwayChar->SendNeighbourMsg(&clMsg2, true);
	}
}

void CPVP_Leage_MatchingList::PVP_League_MatchingLog( void )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	for ( SI32 siSlot = 0; siSlot < MAX_MATCHING_PERSON ; siSlot++)
	{
		// Ȩ�� ����� �۽����̵� ������ �´�.
		SI32 siHomePersonId = m_clPVP_LeageMatchingList[siSlot].GetBattlePersonIDHome()	;
		SI32 siAwayPersonId = m_clPVP_LeageMatchingList[siSlot].GetBattlePersonIDAway()	;
		SI32 siHomeId	=	pclClient->pclCM->GetIDFromPersonID( siHomePersonId )	;
		SI32 siAwayId	=	pclClient->pclCM->GetIDFromPersonID( siAwayPersonId )	;
		if ( pclClient->pclCM->IsValidID( siHomeId ) == false )	return	;
		if ( pclClient->pclCM->IsValidID( siAwayId ) == false )	return	;
		cltCharServer* pclHomeChar = pclClient->pclCM->GetCharServer(siHomeId);			if(pclHomeChar == NULL)			return ;
		cltCharServer* pclAwayChar = pclClient->pclCM->GetCharServer(siAwayId);			if(pclAwayChar == NULL)			return ;

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// para1 = ��Ī�� �ɸ��� 1 para2 ��� �ɸ��� 
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_MATCHING, 
				0,NULL ,NULL,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclHomeChar->pclCI->GetPersonID(), pclAwayChar->pclCI->GetPersonID(), 0, 0, 0, NULL, NULL);
		}

		// ������ �����.
		TCHAR fileNameBuffer[256];
		//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
		TCHAR szTime[128];
		TCHAR szBuffer0[128];
		SYSTEMTIME stTimeInfo;
		GetLocalTime(&stTimeInfo);
		StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
		StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
		StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
			, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_MATCHINGLIST \t PERSONNAME : [%s]\t PERSONNAME : [%s]\t Time"),
			pclHomeChar->GetName(),pclAwayChar->GetName(),szBuffer0 );
	}
}


//========================================================================================
// CPVP_Leage_EndGameList
//========================================================================================
CPVP_Leage_EndGameList::CPVP_Leage_EndGameList()
{
	Init();
}

CPVP_Leage_EndGameList::~CPVP_Leage_EndGameList()
{
}

void CPVP_Leage_EndGameList::Init()
{
	for (SI32 i = 0 ; i<MAX_MATCHING_PERSON; i++) 
	{
		m_clPVP_Leage_EndGameList[i].InitPVP_Leage_EndGameListData()	;
	}
}

void CPVP_Leage_EndGameList::Add( SI32 WinnerID, SI32 LoserID )
{
	SI32	siEmptyIndex = -1;

	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_Leage_EndGameList[i].IsEmpty() == true )
		{
			siEmptyIndex = i;
			break;
		}
	}

	if( siEmptyIndex < 0 )			return;

	m_clPVP_Leage_EndGameList[siEmptyIndex].SetBattlePersonIDWin(WinnerID);
	m_clPVP_Leage_EndGameList[siEmptyIndex].SetBattlePersonIDLose(LoserID);
}

SI32 CPVP_Leage_EndGameList::FindPersonID( SI32 siPersonID )
{
	SI32	siRetIndex = -1;
	for(SI32 i=0; i<MAX_MATCHING_PERSON; i++)
	{
		if( m_clPVP_Leage_EndGameList[i].GetBattlePersonIDWin() == siPersonID ||
			m_clPVP_Leage_EndGameList[i].GetBattlePersonIDLose() == siPersonID )
		{
			siRetIndex = i;
			break;
		}
	}

	return siRetIndex;
}

void CPVP_Leage_EndGameList::PVP_LeagueEndWarp()
{
	// ���� �Ǿ������� ������ ������ ���� ��Ų��.
	for ( SI32 siSlot = 0 ; siSlot < MAX_MATCHING_PERSON ; siSlot++ ) 
	{
		// ������ ��� ���� 
		SI32 siHomePerson = m_clPVP_Leage_EndGameList[ siSlot].GetBattlePersonIDWin()	;
		SI32 siAwayPerson = m_clPVP_Leage_EndGameList[ siSlot].GetBattlePersonIDLose()	;
		if ( siHomePerson <=0 && siAwayPerson <= 0)		continue	;

		cltWarpInfo	clMAinMapWarpInfo (1, MAPINDEX_MAINFIELD, true, false,313 ,341 , -1,  -1)	;
		clMAinMapWarpInfo.uiMapIndex = MAPINDEX_MAINFIELD	;

		cltWarpInfo clinPVPMAPWarpInfo(1, MAPINDEX_PVPMAP, true, false, 49,55, -1,  -1)	;
		clinPVPMAPWarpInfo.uiMapIndex = MAPINDEX_PVPMAP	;

		SI32 Homeid = pclClient->pclCM->GetIDFromPersonID( siHomePerson ) ;
		cltCharServer* pclHomechar = (cltCharServer*)pclClient->pclCM->CR[ Homeid ]	;/*		if (pclHomechar == NULL )	return	;*/
		if ( pclHomechar != NULL) 
		{
			// ���� ���� ���θ��ʵ忡 �ִٸ�.HOME
			if(	pclHomechar->GetMapIndex() == MAPINDEX_MAINFIELD	)
			{
				cltMapCommon* pclHomemap = pclClient->pclMapManager->GetMapPointer(pclHomechar->GetMapIndex())	;

				if(pclHomemap != NULL)
				{
					SI32 siColl = pclHomemap->CalcCollInfo( pclHomechar->GetX(), pclHomechar->GetY())	;
					if( siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						pclHomechar->SetWarpInfo(&clMAinMapWarpInfo, 3000);
						pclHomechar->Warp();
						// ���� ��ȯ���� ������ ���ڸ��� ���� �ش�.
						SI32 siHomesummonId = pclHomechar->GetSummonID()	;
						if ( siHomesummonId > 0 ) 
						{
							cltCharServer* pclHomeSummon = (cltCharServer*)pclClient->pclCM->CR[ siHomesummonId ]	;
							if ( pclHomeSummon != NULL ) 
							{
								pclHomeSummon->SetWarpInfo(&clMAinMapWarpInfo, 3000);
								pclHomeSummon->Warp();
							}
						}						
					}
				}
			}
			else if(pclHomechar->GetMapIndex() == MAPINDEX_PVPMAP )
			{
				pclHomechar->SetWarpInfo(&clinPVPMAPWarpInfo, 3000);
				pclHomechar->Warp();
			}
		}

		SI32 Awayid = pclClient->pclCM->GetIDFromPersonID( siAwayPerson ) ;
		cltCharServer* pclAwaychar = (cltCharServer*)pclClient->pclCM->CR[ Awayid ]	;/*		if (pclAwaychar == NULL )	return	;*/
		if ( pclAwaychar != NULL )
		{
			// ���� �����ʵ忡 �ִٸ� AWAY
			if(	pclAwaychar->GetMapIndex() == MAPINDEX_MAINFIELD	)
			{
				cltMapCommon* pclAwaymap = pclClient->pclMapManager->GetMapPointer(pclAwaychar->GetMapIndex())	;

				if(pclAwaymap != NULL)
				{
					SI32 siColl = pclAwaymap->CalcCollInfo( pclAwaychar->GetX(), pclAwaychar->GetY())	;
					if( siColl & BLOCK_EVENT4 )	// 4�� �̺�Ÿ Ÿ���� ��� ������.
					{
						pclAwaychar->SetWarpInfo(&clMAinMapWarpInfo, 3000);
						pclAwaychar->Warp();
					}
				}
			}
			else if(pclAwaychar->GetMapIndex() == MAPINDEX_PVPMAP )
			{
				pclAwaychar->SetWarpInfo(&clinPVPMAPWarpInfo, 3000);
				pclAwaychar->Warp();
				// ���� ��ȯ���� ������ ���ڸ��� ���� �ش�.
				SI32 siAwaysummonId = pclAwaychar->GetSummonID()	;
				if ( siAwaysummonId > 0 ) 
				{
					cltCharServer* pclAwaySummon = (cltCharServer*)pclClient->pclCM->CR[ siAwaysummonId ]	;
					if ( pclAwaySummon != NULL ) 
					{
						pclAwaySummon->SetWarpInfo(&clMAinMapWarpInfo, 3000);
						pclAwaySummon->Warp();
					}
				}						
			}
		}
	}
}


//========================================================================================
// CPVP_LeagueMgr
//========================================================================================
// ������
CPVP_LeagueMgr::CPVP_LeagueMgr()
{
	ZeroMemory( this, sizeof(CPVP_LeagueMgr) );
}
// �Ҹ���
CPVP_LeagueMgr::~CPVP_LeagueMgr()
{

}

void CPVP_LeagueMgr::Init( void )
{
	m_clPVP_LeageReserveList.Init();
	m_clPVP_LeageMatchingList.Init();
	m_clPVP_Leage_EndGameList.Init();
}

void CPVP_LeagueMgr::AddEndGameList( SI32 WinnerID, SI32 LoserID )	// ������ ���ӵ��� ������ ���� ��� �Ѵ�.
{
	// ������ ���� ĳ������ �����̻��� ġ���Ѵ�.
	SI32 siWinnerCharID = pclClient->pclCM->GetIDFromPersonID( WinnerID );
	SI32 siLoserCharID  = pclClient->pclCM->GetIDFromPersonID( LoserID );

	cltCharServer* pclCharWinner = pclClient->pclCM->GetCharServer( siWinnerCharID );
	if( pclCharWinner )
	{
		pclCharWinner->DeletePoison();					// �ߵ� ���¸� �����Ѵ�.
		pclCharWinner->DeletePoisonSetItemEffect();		// �ߵ� ���¸� �����Ѵ�.
		pclCharWinner->DeleteIce();						// ���� ���¸� �����Ѵ�.

		pclCharWinner->DeleteCurseAttack();				// ���ݷ��� ���� ���¸� �����Ѵ�.
		pclCharWinner->DeleteCurseCritical();			// Critical Ȯ���� �������� ���¸� �����Ѵ�.
		pclCharWinner->DeleteCurseDefense();			// ������ �������� ���¸� �����Ѵ�.
		pclCharWinner->DeleteCurseMovespeed();			// �̵��ӵ� ���� ���¸� �����Ѵ�.

		pclCharWinner->DeleteMagicFire();				// �ҿ� Ÿ�� ���¸� �����Ѵ�.
		pclCharWinner->DeleteFrozen();					// ���� ���� ���¸� �����Ѵ�.
	}

	cltCharServer* pclCharLoser = pclClient->pclCM->GetCharServer( siLoserCharID );
	if( pclCharLoser )
	{
		pclCharLoser->DeletePoison();					// �ߵ� ���¸� �����Ѵ�.
		pclCharLoser->DeletePoisonSetItemEffect();		// �ߵ� ���¸� �����Ѵ�.
		pclCharLoser->DeleteIce();						// ���� ���¸� �����Ѵ�.

		pclCharLoser->DeleteCurseAttack();				// ���ݷ��� ���� ���¸� �����Ѵ�.
		pclCharLoser->DeleteCurseCritical();			// Critical Ȯ���� �������� ���¸� �����Ѵ�.
		pclCharLoser->DeleteCurseDefense();				// ������ �������� ���¸� �����Ѵ�.
		pclCharLoser->DeleteCurseMovespeed();			// �̵��ӵ� ���� ���¸� �����Ѵ�.

		pclCharLoser->DeleteMagicFire();				// �ҿ� Ÿ�� ���¸� �����Ѵ�.
		pclCharLoser->DeleteFrozen();					// ���� ���� ���¸� �����Ѵ�.
	}

	// ����� �����۽��� ����ϰ�
	m_clPVP_Leage_EndGameList.Add( WinnerID, LoserID );

	// ��Ī����Ʈ���� �����Ѵ�.
	m_clPVP_LeageMatchingList.Delete( WinnerID, LoserID );
}

SI32 CPVP_LeagueMgr::AddReserveList( SI32 siPersonID, SI16 siGrade )
{
	// �������� ��� 
	LogReserve( siPersonID)	;
	return m_clPVP_LeageReserveList.Add( siPersonID, siGrade );
}

void CPVP_LeagueMgr::SubReserveList( SI32 siPersonID )
{
	m_clPVP_LeageReserveList.Delete( siPersonID );
	m_clPVP_LeageReserveList.ArrangeList();
}

void CPVP_LeagueMgr::AgainReserveList( SI32 siPersonID, bool bAnswer )
{
	if( bAnswer )
	{
		m_clPVP_LeageReserveList.SetStatus( siPersonID, PVP_LEAGUE_RESERVE_STATUS_POSSIBLE);
	}
	else
	{
		m_clPVP_LeageReserveList.Delete( siPersonID );
		m_clPVP_LeageReserveList.ArrangeList();
	}
}

void CPVP_LeagueMgr::MakeMatchingList( void )
{
	// ������ �ִ� ��Ī����Ʈ�� �ʱ�ȭ
	m_clPVP_LeageMatchingList.Init();

	// ��Ī�� �� �� ���� ����� ��� ����������
	m_clPVP_LeageReserveList.DeleteNoPossiblePerson();

	// ����Ʈ�� �ο��� 0 �����϶��� �����ʿ䰡 ����
	if( 0 >= m_clPVP_LeageReserveList.GetCount() )			return;

	for( SI32 i=0; i<MAX_RESERVE_PERSON; i++ )
	{
		SI32 siSourcePersonID = m_clPVP_LeageReserveList.GetPersonID( i );
		if( siSourcePersonID <= 0 )										continue;

		SI32 siDestPersonID = m_clPVP_LeageReserveList.FindMatchPerson( siSourcePersonID );

		if( siDestPersonID > 0 )
		{
			SI32 siTotalScore = GetTotalScore( siSourcePersonID, siDestPersonID );
			if ( true == m_clPVP_LeageMatchingList.Add(siSourcePersonID, siDestPersonID, siTotalScore) )
			{			
				// ����Ʈ�� �� ����� ��û�� ��Ͽ��� �����
				m_clPVP_LeageReserveList.Delete( siSourcePersonID );
				m_clPVP_LeageReserveList.Delete( siDestPersonID );
			}
		}

		if( m_clPVP_LeageMatchingList.IsFull() )
		{
			break;
		}
	}

	m_clPVP_LeageMatchingList.SortByTotalScore();
}

SI32 CPVP_LeagueMgr::GetRerserveListCount()
{
	return m_clPVP_LeageReserveList.GetCount();
}

bool CPVP_LeagueMgr::CheckTheGrade( SI16 siSourceGrade, SI16 siDestGrade, SI32* psiGradeGab )
{
	SI16 siGradeTable[] = {
		PVP_LEAGUE_GRADE_NONE,
			PVP_LEAGUE_GRADE_9,
			PVP_LEAGUE_GRADE_8,
			PVP_LEAGUE_GRADE_7,
			PVP_LEAGUE_GRADE_6,
			PVP_LEAGUE_GRADE_5,
			PVP_LEAGUE_GRADE_4,
			PVP_LEAGUE_GRADE_3,
			PVP_LEAGUE_GRADE_2,
			PVP_LEAGUE_GRADE_1
	};

	SI32 siGradeTableCount = sizeof(siGradeTable)	/ sizeof(siGradeTable[0]);
	if ( 0 >= siGradeTableCount )
	{
		return false;
	}

	SI32 siSourcePosition	= -1;
	SI32 siDestPosition		= -1;

	for ( SI32 siIndex=0; siIndex<siGradeTableCount; ++siIndex )
	{
		if ( siGradeTable[siIndex] == siSourceGrade )
		{
			siSourcePosition = siIndex;
		}

		if ( siGradeTable[siIndex] == siDestGrade )
		{
			siDestPosition = siIndex;
		}

		if ( (0 <= siSourcePosition) && (0 <= siDestPosition) )
		{
			break;
		}
	}

	// Ȥ�� ��� ������ ���� ã�� ���ߴٸ�
	if ( (0 > siSourcePosition) || (0 > siDestPosition) )
	{
		return false;
	}

	// ��� ���̰� MAX_PVP_LEAGUE_GRADE_GAB ������ �ȵȴ�
	SI32 siGab = TABS(siSourcePosition - siDestPosition);
	if ( siGab  > MAX_PVP_LEAGUE_GRADE_GAB )
	{
		return false;
	}

	// 3��� �̳����� ������ �˻��ߴ� ����� ���̺��� ���ٸ� 
	if ( siGab < *psiGradeGab )
	{
		*psiGradeGab = siGab;
		return true;
	}

	return false;
}

bool CPVP_LeagueMgr::IsValidPerson( SI32 siSourcePersonID, SI32 siDestPersonID )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )		return false;
	//���� ���� ���̵� ������ �´�
	SI32 siDestCharID = pclserver->pclCM->GetIDFromPersonID( siDestPersonID );				if ( false == pclserver->pclCM->IsValidID(siDestCharID) )	return false;
	SI32 siSourceCharID = pclserver->pclCM->GetIDFromPersonID( siSourcePersonID );			if ( false == pclserver->pclCM->IsValidID(siSourceCharID) )	return false;

	cltCharServer* pclSourceChar = pclserver->pclCM->GetCharServer( siSourceCharID );		if ( NULL == pclSourceChar )return false;
	cltCharServer* pclDesteChar = pclserver->pclCM->GetCharServer( siDestCharID );			if ( NULL == pclDesteChar )return false;

	// �̹� �ֱ� 2��� ����ڶ��	
	if ( true == pclSourceChar->IsPVP_LeagueLatestPersonID(siDestPersonID) )		return false;
	else if ( true == pclDesteChar->IsPVP_LeagueLatestPersonID(siSourceCharID) )	return false;

	return true;
}
void CPVP_LeagueMgr::NoticeSpecialNews( void )
{
	m_clPVP_LeageMatchingList.NoticeSpecialNews();
}

void CPVP_LeagueMgr::NoticeStartPVP( void )
{
	m_clPVP_LeageMatchingList.NoticeStartPVP();
}

void CPVP_LeagueMgr::NoticeStartTime( void )
{
	// ���ҽ� ���� �ð��� ���� �´�
	cltEventTime* pclPVPLeagueMatch = pclClient->pclEventTimeManager->GetEvent("PVP_LeagueMatch");
	if ( NULL == pclPVPLeagueMatch )
	{
		return;
	}

	SI32	siStartHour		= pclPVPLeagueMatch->m_StartTime.wHour;
	SI32	siStartMinute	= pclPVPLeagueMatch->m_StartTime.wMinute+5;
	TCHAR	szStartTime[64]	= { '\0', };

	StringCchPrintf( szStartTime, sizeof(szStartTime), TEXT("%02d:%02d"), siStartHour, siStartMinute );

	// ������ ���� �ؽ�Ʈ���� ���� �´�
	NTCHARString64	strTitle( GetTxtFromMgr(5482) );
	NTCHARString128	strText( GetTxtFromMgr(9728) );

	strText.Replace( TEXT("#time#"), szStartTime );

	cltGameMsgResponse_Notice clNotice( strTitle, strText, true );
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice );
	// �������ִ� ��� ����鿡�� �˷��ش�
	pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);	

}
void CPVP_LeagueMgr::NoticeEndTime( void )
{

	// ������ ���� �ؽ�Ʈ���� ���� �´�
	NTCHARString64	strTitle( GetTxtFromMgr(9581) );
	NTCHARString128	strText( GetTxtFromMgr(9781) );

	cltGameMsgResponse_Notice clNotice( strTitle, strText, true );
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice );
	// �������ִ� ��� ����鿡�� �˷��ش�
	pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);	

}

void CPVP_LeagueMgr::Action()
{
	if (pclClient->GameMode != GAMEMODE_SERVER  )				return	;
	cltServer* pclserver = (cltServer*)pclClient;

	SYSTEMTIME stTime	= pclserver->sTime	;
	stTime.wHour	=	pclserver->sTime.wHour		;
	stTime.wMinute	=	pclserver->sTime.wMinute	;
	stTime.wSecond	=	pclserver->sTime.wSecond	;

	if(true ==  pclserver->pclEventTimeManager->InEventTime("PVP_LeagueReserve", &stTime) 
		|| true ==  pclserver->pclEventTimeManager->InEventTime("PVP_LeagueMatch", &stTime) ) // �̺�Ʈ Ÿ���϶�.
	{
		SI32 si_Battle_Status	= Get_PVP_League_Status()	;
		switch( si_Battle_Status ) 
		{
		case PVP_LEAGUE_PROGRESS_READY:
			{
				if( pclserver->pclEventTimeManager->IsEventStartTiem( "PVP_LeagueReserve", &stTime ) == true )	// ���� ó�� ���� �������� �����ش�.
				{
					NoticeStartTime()	;	// ���� ���� �ð��� ���� �Ѵ�.
					bEndNotice	= false	;	// ������ ���� �ؾ� �ϴϱ�� 
				}				
				Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_BEFORE_1_M )	;// ���¸� ���� �Ѵ�.
			}
			break;
		case PVP_LEAGUE_PROGRESS_BEFORE_1_M://======1����	��Ī ����Ʈ�� ������.
			{
				if( pclserver->pclEventTimeManager->InEventTime( "PVP_LeagueMatch", &stTime ) == false )	return	;
				if(stTime.wMinute % 5 == 4 )	// 4���϶� ����Ʈ�� �����.
				{
					m_clPVP_Leage_EndGameList.Init();		// ���� ����Ʈ�� �ʱ�ȭ.
					MakeMatchingList()		;				// ��Ī ����Ʈ�� �����.

					m_clPVP_LeageReserveList.SendToAgainReserveQuestion();		// ��Ī�� �ȵ� ��������״� �ٽ� ����Ʈ�� �������� Ȯ�� �޽��� ����					
					m_clPVP_LeageReserveList.ArrangeList();						// ��û�� ����Ʈ�� ��� ����Ǿ����� ����Ʈ�� ������					
					NoticeSpecialNews();										// Ư���������� �ڸ��� ������

					m_clPVP_LeageMatchingList.PVP_League_MatchingLog();			// ��Ī ����Ʈ�� ����� �α׸� �����.
					PVP_League_Before1m()	;									// 1�е� ���Ҵٴ� �޼��� ������.
					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_BEFORE_10_S )	;
				}
			}
			break;
		case PVP_LEAGUE_PROGRESS_BEFORE_10_S://======10�����̴�. �غ� �϶�� �޼����� ������.
			{
				if(stTime.wMinute % 5 == 4	&&	stTime.wSecond >=50 )
				{
					NoticeStartPVP()				;	// �� ���� �ȴٴ� �޼����� ������. 
					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_ONTIME )	;
				}				
			}
			break;
		case PVP_LEAGUE_PROGRESS_ONTIME://======== 5�еƴ�. ���� ��Ų��.
			{
				if(stTime.wMinute % 5 == 0 )
				{
					PVP_LeagueReady()	;
					//m_siEndGameListCount = 0	;	// ���� ���� ����Ʈ �ʱ�ȭ 

					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_AFTER_30_S )	;
				}				
			}
			break;
		case PVP_LEAGUE_PROGRESS_AFTER_30_S:// �����ѵ� �� 30�� ���� ���Ŀ� ������ �Ѵ�.
			{
				if( stTime.wMinute % 5 == 0 && stTime.wSecond >= 30 )
				{
					PVP_LeagueStart( )	;	// PVP���׸� ���� �Ѵ�.
					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_END_BATTLE )	;
				}				
			}
			break;
		case PVP_LEAGUE_PROGRESS_END_BATTLE://======�������� �ܰ�. 3�� ������ ������ ���� ��Ų��.
			{
				if(stTime.wMinute % 5 == 3	&&	stTime.wSecond >= 30 )
				{
					// ������ �ºθ� ���� ������� ��� ó��
					PVP_Battle_Step_Draw()	;
					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_END_ESCAPEGROUND )	;
				}
				else
				{
					// ���� ������ üũ�Ѵ�.
					PVP_Battle_Step_Game()	;
				}
			}
			break;
		case PVP_LEAGUE_PROGRESS_END_ESCAPEGROUND:
			{
				if(stTime.wMinute % 5 == 3	&&	stTime.wSecond >= 30 )
				{
					//�����ð��� ��� �Ǿ� ������ ��� ��Ī�ƴ� �ɸ��͵��� ���� ��Ų��.(���� ��Ų��.)
					m_clPVP_Leage_EndGameList.PVP_LeagueEndWarp();
					Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_READY )	;
				}
			}
			break;
		default:
			{
			}
		}
	}	
	if( true == pclserver->pclEventTimeManager->IsEventEndTiem("PVP_LeagueMatch", &stTime) ) // �̺�Ʈ Ÿ���� ������ �ð��϶�
	{
		if ( bEndNotice == false ) 
		{
			SI32 si_Battle_Status	= Get_PVP_League_Status()	;
			NoticeEndTime();// �����ٰ� �����ش�.
			bEndNotice	= true	;
			Init();
			Set_PVP_League_Status( PVP_LEAGUE_PROGRESS_READY )	;
		}

	}
}

void CPVP_LeagueMgr::End_PVP_Battle_End( SI32 siWinnerPersonID, SI32 siLoserPersonID)
{
	// End ���� ����Ʈ�� ����ִ� ĳ���ʹ� �̹� ������ ���� ĳ�����̴�.
	if( InEndGameList( siWinnerPersonID ) == true )	return	;
	if( InEndGameList( siLoserPersonID) == true )	return	;

	// DB�� ��� ����
	sendResultDB( siWinnerPersonID,siLoserPersonID)		;

	// �α� ���
	LogWinLose( siWinnerPersonID,siLoserPersonID)		;

	// ��Ⱑ �������Ƿ� End���� ����Ʈ�� �����Ѵ�.
	AddEndGameList(siWinnerPersonID,siLoserPersonID)	;
}

void CPVP_LeagueMgr::End_PVP_Battle_Draw( SI32 siFirstPerson, SI32 siSecondPerson )
{
	sendResultDrawDB( siFirstPerson,siSecondPerson)		;
	AddEndGameList(siFirstPerson,siSecondPerson)	;
}

// ���а� ���� ���
void CPVP_LeagueMgr::sendResultDB( SI32 siWinnerPersonID, SI32 siLoserPersonID)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if (siWinnerPersonID <= 0 && siLoserPersonID <= 0 )	return	;

	// ���� ��� ����� ������. ---------------------------------
	sDBRequest_PVP_League_Battle_End clMsg(  siWinnerPersonID , siLoserPersonID, PVPLEAGUE_RESULT_WIN,pclserver->sTime);
	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg)	;

	sDBRequest_PVP_League_Battle_End clMsg2(  siLoserPersonID , siWinnerPersonID, PVPLEAGUE_RESULT_LOSE,pclserver->sTime);
	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2)	;
}

// ����� ���
void CPVP_LeagueMgr::sendResultDrawDB( SI32 siFirstPerson, SI32 siSecondPerson)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if (siFirstPerson <= 0  && siSecondPerson <= 0 )	return	;

	// ���� ��� ����� ������. ---------------------------------
	sDBRequest_PVP_League_Battle_End clMsg(  siSecondPerson , siFirstPerson, PVPLEAGUE_RESULT_DRAW,pclserver->sTime);
	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	sDBRequest_PVP_League_Battle_End clMsg2(  siFirstPerson ,siSecondPerson , PVPLEAGUE_RESULT_DRAW,pclserver->sTime);
	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
}

// ���и� ���� Ŭ���̾�Ʈ�� �˷�����.
void CPVP_LeagueMgr::Send_PVP_Battle_Result( SI32 siWinPerson, SI32 siLosePerson, SI32 siFlag )
{
	SI32 siWinID = pclClient->pclCM->GetIDFromPersonID( siWinPerson );
	cltCharServer* pclWinChar = NULL;
	if( pclClient->pclCM->IsValidID( siWinID ) )	pclWinChar = pclClient->pclCM->GetCharServer( siWinID );

	SI32 siLoseID = pclClient->pclCM->GetIDFromPersonID( siLosePerson );
	cltCharServer* pclLoseChar = NULL;
	if( pclClient->pclCM->IsValidID( siLoseID ) )	pclLoseChar = pclClient->pclCM->GetCharServer( siLoseID );

	switch( siFlag )
	{
	case PVPLEAGUE_RESULT_WIN:
		{
			// ĳ���Ͱ� ���������� ���ӿ� �ִ� ��쿡�� ó���Ѵ�.
			if( pclWinChar )
			{
				SetAfterPVP_League_Record_Win( siWinID ); // �¸��� ����� ��Ͽ� ���� ó��.

				pclWinChar->siEnemUnique	=	0	;	// �̰����ϱ� �� �ɸ��� �ʱ�ȭ.
				pclWinChar->SetPVP_LeagueEnemyPersonID(0)	;

				pclWinChar->IncQuestPara( QUEST_CLEAR_COND_PVPLEAGUEWIN, 0, 1 );

				// �¸���
				cltGameMsgResponse_PVP_Request clWinner( END_PVP , WIN_PVP, pclWinChar->GetCharUnique(), TEXT("") );	
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
				pclWinChar->SendNeighbourMsg(&clMsg, true);
			}
		}
		break;
	case PVPLEAGUE_RESULT_LOSE:
		{
			// ĳ���Ͱ� ���������� ���ӿ� �ִ� ��쿡�� ó���Ѵ�.
			if( pclLoseChar )
			{
				SetAfterPVP_League_Record_Lose( siLoseID ); // �й��� ����� ��Ͽ� ���� ó��.

				// PVP���� ��ġ�� �ִ� ĳ���͸� ���ڸ� ��Ȱ�� �����ش�.
				if( Is_MatchingListPeron_TruePosition( siLosePerson ) )
				{		pclLoseChar->siEnemUnique	=	-100	;		}
				else
				{		pclLoseChar->siEnemUnique	=	0	;			}

				pclLoseChar->SetPVP_LeagueEnemyPersonID(0)	;

				// �й���
				cltGameMsgResponse_PVP_Request clclLoser( END_PVP , LOSE_PVP, pclLoseChar->GetCharUnique(), TEXT("") );
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclLoser), (BYTE*)&clclLoser );
				pclLoseChar->SendNeighbourMsg(&clMsg2, true);
			}
		}
		break;
	case PVPLEAGUE_RESULT_DRAW:
		{
			// ĳ���Ͱ� ���������� ���ӿ� �ִ� ��쿡�� ó���Ѵ�.
			if( pclWinChar )
			{
				SetAfterPVP_League_Record_Draw( siWinID )	;

				pclWinChar->siEnemUnique	=	0	;
				pclWinChar->SetPVP_LeagueEnemyPersonID(0)	;

				cltGameMsgResponse_PVP_Request clWinner( END_PVP , DRAW_PVP, pclWinChar->GetCharUnique(), TEXT("") );	
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
				pclWinChar->SendNeighbourMsg(&clMsg, true);
			}
		}
		break;
	}
}

void CPVP_LeagueMgr::SetAfterPVP_League_Record_Win( SI32 siID )
{
	if ( pclClient->pclCM->IsValidID( siID ) == false )		return	;
	cltCharCommon* pclWinCharCommon = pclClient->pclCM->CR[siID]		;

	pclWinCharCommon->SetPVP_LeagueEnemyPersonID(0)	;
	// �¸��� ������ ������ ���� ��ϵ� 0
	//------------------------------------------------------
	pclWinCharCommon->SetPVP_LeagueStraight_Draw( 0 )	;
	//------------------------------------------------------
	pclWinCharCommon->SetPVP_LeagueStraight_Lose( 0 )	;
	pclWinCharCommon->SetPVP_LeagueStraight_Lose_Grade( 0 )	;
	//------------------------------------------------------
	// ���±���� ������ �´�
	SI16 siStraight_Win	=	pclWinCharCommon->GetPVP_LeagueStraight_Win()	;
	pclWinCharCommon->SetPVP_LeagueStraight_Win( siStraight_Win + 1)	;
	SI16 siWinCount		=	pclWinCharCommon->GetPVP_LeagueStraight_Win()	;

	// ����� ���� ��� ��� �߰�
	SI32 siWinCountGradeNow = pclWinCharCommon->GetPVP_LeagueStraight_Win_Grade()	;
	pclWinCharCommon->SetPVP_LeagueStraight_Win_Grade( siWinCountGradeNow+1 )	;
	SI32 siWinCountGrade = pclWinCharCommon->GetPVP_LeagueStraight_Win_Grade()	;

	//��� �� ��ǰ�� �ش�	
	AfterPVP_League_Record_Win_Prize(siID ,siWinCount)	;
	// ��� ����
	PVP_League_LevelUp(siID, siWinCountGrade )	;
}

void CPVP_LeagueMgr::SetAfterPVP_League_Record_Draw( SI32 siID )
{
	SI32 siDrawId = siID	;
	if ( pclClient->pclCM->IsValidID( siDrawId ) == false )		return	;
	cltCharCommon* pclDrawCharCommon = pclClient->pclCM->CR[siDrawId]		;

	// PVP�� �������� ��� ������ ����.
	pclDrawCharCommon->SetPVP_LeagueEnemyPersonID(0)	;
	// ���ºΰ� ������ �¸� ��ϵ��� �������.
	//------------------------------------------------------
	pclDrawCharCommon->SetPVP_LeagueStraight_Win( 0 )	;
	pclDrawCharCommon->SetPVP_LeagueStraight_Lose( 0 )	;
	//------------------------------------------------------
	pclDrawCharCommon->SetPVP_LeagueStraight_Win_Grade( 0 )	;
	pclDrawCharCommon->SetPVP_LeagueStraight_Lose( 0 )	;
	//------------------------------------------------------
	// ���� ���º� ��� 1 ���� 
	SI32 siDrawRecord = pclDrawCharCommon->GetPVP_LeagueStraight_Draw( )	;
	pclDrawCharCommon->SetPVP_LeagueStraight_Draw( siDrawRecord + 1)	;	
	SI32 siStright_Draw = pclDrawCharCommon->GetPVP_LeagueStraight_Draw()		;
	//��� �� ��ǰ�� �ش�	
	AfterPVP_League_Record_Draw_Prize(siDrawId ,siStright_Draw)	;
}

void CPVP_LeagueMgr::SetAfterPVP_League_Record_Lose( SI32 siID )
{
	SI32 siLoserId = siID	;
	if ( pclClient->pclCM->IsValidID( siLoserId ) == false )		return	;
	SI32 siLoserChaeParentID = pclClient->pclCM->CR[ siLoserId ]->GetSummonParentID()	;
	if ( siLoserChaeParentID == 0 )	siLoserChaeParentID = siLoserId
		;
	cltCharCommon* pclLoseCharCommon = pclClient->pclCM->CR[siLoserChaeParentID]		;

	pclLoseCharCommon->SetPVP_LeagueEnemyPersonID(0)	;
	// �й������� ���� ��ϵ� ��� ����.
	//------------------------------------------------------
	pclLoseCharCommon->SetPVP_LeagueStraight_Win( 0 )	;
	pclLoseCharCommon->SetPVP_LeagueStraight_Win_Grade( 0 )	;
	pclLoseCharCommon->SetPVP_LeagueStraight_Draw( 0 )	;
	//------------------------------------------------------

	// ���� �й� ��Ͽ� 1�� �߰�
	SI32 siLoseRecord = pclLoseCharCommon->GetPVP_LeagueStraight_Lose( )		;
	pclLoseCharCommon->SetPVP_LeagueStraight_Lose( siLoseRecord + 1)			;	
	SI32 siStright_Lose = pclLoseCharCommon->GetPVP_LeagueStraight_Lose()	;

	// ����� ���� �й� ��� �߰�
	SI32 siLoseCountGradeNow = pclLoseCharCommon->GetPVP_LeagueStraight_Lose_Grade()	;
	pclLoseCharCommon->SetPVP_LeagueStraight_Lose_Grade( siLoseCountGradeNow+1 )	;
	SI32 siLoseCountGrade = pclLoseCharCommon->GetPVP_LeagueStraight_Lose_Grade()	;
	//��� �� ��ǰ�� �ش�	
	AfterPVP_League_Record_Lose_Prize( siLoserId , siStright_Lose )		;
	// ��� ����
	PVP_League_LevelDown(siLoserId, siLoseCountGrade );

}

void CPVP_LeagueMgr::AfterPVP_League_Record_Win_Prize( SI32 siID, SI32 siStrightWinCount) // �۽����̵� �ƴմϴ� ����ũ �޽��ϴ�.
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID	;
	if ( pclClient->pclCM->IsValidID( siID ) == false )		return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siId);			if(pclChar == NULL)			return ;

	//���ӱ�Ͽ� ���� ����
	SI32 strightdraw100 = pclClient->GetGlobalValue("GV_straight_win100")	;
	SI32 strightdraw1000 = pclClient->GetGlobalValue("GV_straight_win1000")	;

	SI32 strightdraw100Unique = pclClient->GetGlobalValue("GV_straight_win100Unique")	;
	SI32 strightdraw1000Unique = pclClient->GetGlobalValue("GV_straight_win1000Unique")	;

	SI32 siRewardItemUnique	=	pclClient->GetGlobalValue("GV_PVP_League_Win_Unique")	;
	PVP_League_GiveItem(siId, siRewardItemUnique , false );

	if ( siStrightWinCount % strightdraw1000	==	0	) 
	{
		// 1000���� �޼����� ������ ������.
		// �������� �ش�
		LogGoal( pclChar->pclCI->GetPersonID(),PVP_LEAGUE_END_RESULT_1000WIN  )	;
		PVP_League_GiveItem(siId, strightdraw1000Unique,true );
		PVP_Battle_HaveItemMessage( siId, strightdraw1000Unique );
	}

	else if ( siStrightWinCount 	%	strightdraw100  == 0	) 
	{
		// 100���� �޼����� ������ ������.
		// �������� �ش�.
		LogGoal( pclChar->pclCI->GetPersonID(),PVP_LEAGUE_END_RESULT_100WIN )	;
		PVP_League_GiveItem(siId, strightdraw100Unique, true );
		PVP_Battle_HaveItemMessage( siId, strightdraw100Unique);
	}

}

void CPVP_LeagueMgr::AfterPVP_League_Record_Draw_Prize( SI32 siID , SI32 siStrightWinCount)
{
	SI32 siId = siID	;
	if ( pclClient->pclCM->IsValidID( siId ) == false )		return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siId);			if(pclChar == NULL)			return ;

	//���ӱ�Ͽ� ���� ����
	SI32 strightdraw100 = pclClient->GetGlobalValue("GV_straight_Draw100")		;
	SI32 strightdraw1000 = pclClient->GetGlobalValue("GV_straight_draw1000")	;

	SI32 strightdraw100Unique = pclClient->GetGlobalValue("GV_straight_Draw100Unique")		;
	SI32 strightdraw1000Unique = pclClient->GetGlobalValue("GV_straight_draw1000Unique")	;

	SI32 siRewardItemUnique	=	pclClient->GetGlobalValue("GV_PVP_League_Draw_Unique")	;

	PVP_League_GiveItem(siId,siRewardItemUnique, true)	;
	if ( siStrightWinCount % strightdraw1000 == 0 ) 
	{
		// 1000��� ���� ���º����� �˸���.
		// ��ǰ�� �ش�
		LogGoal( pclChar->pclCI->GetPersonID(),PVP_LEAGUE_END_RESULT_1000DRAW  )	;
		PVP_League_GiveItem(siId, strightdraw1000Unique,true )	;
		PVP_Battle_HaveItemMessage( siId, strightdraw1000Unique );
	}	
	else if ( siStrightWinCount % strightdraw100 == 0 ) 
	{
		// 100��� ���� ���º����� �˸���.
		// ��ǰ�� �ش�
		LogGoal( pclChar->pclCI->GetPersonID(),PVP_LEAGUE_END_RESULT_100DRAW  )	;
		PVP_League_GiveItem(siId, strightdraw100Unique, true )	;
		PVP_Battle_HaveItemMessage( siId, strightdraw100Unique );
	}

}

void CPVP_LeagueMgr::AfterPVP_League_Record_Lose_Prize( SI32 siID , SI32 siStrightLoseCount)
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID;
	if ( pclClient->pclCM->IsValidID( siId ) == false )		return	;
	SI32 siParentID = pclClient->pclCM->CR[ siId ]->GetSummonParentID()		;
	if ( siParentID == 0 )	siParentID = siId		;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;

	SI32 siRewardItemUnique	=	pclClient->GetGlobalValue("GV_PVP_League_Draw_Unique")	;

	// �й� ������ �Ѵ�.
	PVP_League_GiveItem(siParentID, siRewardItemUnique , false )	;
}

//--���
void CPVP_LeagueMgr::PVP_League_LevelUp( SI32 siID ,SI32 siStrightWinCountGrade )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID	;
	if ( pclClient->pclCM->IsValidID( siID ) == false )		return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siId);			if(pclChar == NULL)			return ;
	SI32 siGradeNow	=	pclChar->GetPVP_LeagueGrade()	;
	SI32 ChangedGrade = ChangeGrade(siGradeNow,siStrightWinCountGrade,PVP_LEAGUE_END_GRADEUP )	;

	if(pclChar->GetPVP_LeagueGrade() != ChangedGrade )
	{
		pclChar->SetPVP_LeagueStraight_Win_Grade( 0 )	;
		LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siGradeNow, ChangedGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_UP );

		sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangedGrade ,pclserver->sTime );
		pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	//// 5��� �̻� 3���� ���� ��쿡 �ɸ����� ����� �÷��ش�.
	//if( siGradeNow > PVP_LEAGUE_GRADE_6  && siStrightWinCountGrade != 0 && siStrightWinCountGrade % 3 == 0 )
	//{
	//	SI32 ChangedGrade = siGradeNow + MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	;
	//	if ( ChangedGrade > PVP_LEAGUE_GRADE_1 ) 
	//	{
	//		ChangedGrade = PVP_LEAGUE_GRADE_1	;
	//	}
	//	pclChar->SetPVP_LeagueStraight_Win_Grade( 0 )	;
	//	LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siGradeNow, ChangedGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_UP );
	//	sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangedGrade );
	//	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	//}
	//// 5��� �̸� 2���� ���� ��� �ɸ����� ����� �÷��ش�
	//else if(siGradeNow <= PVP_LEAGUE_GRADE_6 && siStrightWinCountGrade != 0  && siStrightWinCountGrade % 2 == 0 )
	//{
	//	SI32 ChangedGrade = siGradeNow + MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	;
	//	if ( ChangedGrade >  PVP_LEAGUE_GRADE_1 ) 
	//	{
	//		ChangedGrade = PVP_LEAGUE_GRADE_1	;
	//	}
	//	pclChar->SetPVP_LeagueStraight_Win_Grade( 0 )	;
	//	LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siGradeNow, ChangedGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_UP );
	//	sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangedGrade );
	//	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);		
	//}
}

void CPVP_LeagueMgr::PVP_League_LevelDown( SI32 siID , SI32 siStrightLoseCountGrade )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID	;
	if ( pclClient->pclCM->IsValidID( siID ) == false )		return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siId);			if(pclChar == NULL)			return ;
	SI32 siGradeNow	=	pclChar->GetPVP_LeagueGrade()	;
	SI32 ChangedGrade = ChangeGrade(siGradeNow,siStrightLoseCountGrade,PVP_LEAGUE_END_GRADEDOWN )	;

	if(pclChar->GetPVP_LeagueGrade() != ChangedGrade )
	{
		pclChar->SetPVP_LeagueStraight_Lose_Grade( 0 )	;
		LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siGradeNow, ChangedGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_DOWN );

		sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangedGrade,pclserver->sTime );
		pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}

	//// 5��� �̻� 3���� ���� ��쿡 �ɸ����� ����� ������
	//if( pclChar->GetPVP_LeagueGrade() > PVP_LEAGUE_GRADE_6  && siStrightLoseCountGrade != 0 && siStrightLoseCountGrade % 3 == 0 )
	//{
	//	SI32 siMyGrade = pclChar->GetPVP_LeagueGrade()	;
	//	SI32 ChangeGrade = siMyGrade - MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	;
	//	if ( ChangeGrade <= PVP_LEAGUE_GRADE_9 ) 
	//	{
	//		ChangeGrade = PVP_LEAGUE_GRADE_9	;
	//	}
	//	pclChar->SetPVP_LeagueStraight_Lose_Grade( 0 )	;
	//	LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siMyGrade, ChangeGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_DOWN );
	//	sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangeGrade );
	//	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);		
	//}
	//// 5��� �̸� 2���� ���� ��� �ɸ����� ����� ������.
	//else if(pclChar->GetPVP_LeagueGrade() <= PVP_LEAGUE_GRADE_6  &&	siStrightLoseCountGrade != 0 && siStrightLoseCountGrade % 2 == 0 ) 
	//{
	//	SI32 siMyGrade = pclChar->GetPVP_LeagueGrade()	;
	//	SI32 ChangeGrade = siMyGrade - MAX_PVP_LEAGUE_GRADE_UP_DOWN_POINT	;
	//	if ( ChangeGrade <= PVP_LEAGUE_GRADE_9 ) 
	//	{
	//		ChangeGrade = PVP_LEAGUE_GRADE_9	;
	//	}
	//	pclChar->SetPVP_LeagueStraight_Lose_Grade( 0 )	;
	//	LogGradeUpDown(pclChar->pclCI->GetPersonID() ,siMyGrade, ChangeGrade,LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_DOWN );
	//	sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  pclChar->pclCI->GetPersonID() ,  ChangeGrade );
	//	pclserver->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);		

	//}
}

void CPVP_LeagueMgr::PVP_LeagueReady()
{
	//���⼭�� ������ ���ش�.
	for ( SI32 siSlot = 0 ; siSlot < MAX_MATCHING_PERSON ; siSlot++ ) 
	{
		// ������ ��� ���� 
		SI32 siHomePerson = m_clPVP_LeageMatchingList.GetBattlePersonIDHome(siSlot)	;
		SI32 siAwayPerson = m_clPVP_LeageMatchingList.GetBattlePersonIDAway(siSlot)	;
		if ( siHomePerson <=0 && siAwayPerson <= 0)		continue	;

		if ( 0 == siSlot) 
		{
			PVP_League_Warp_Stage( siHomePerson, siAwayPerson , MAPINDEX_MAINFIELD, siSlot)	;
		}
		else
		{
			PVP_League_Warp_Stage( siHomePerson, siAwayPerson , MAPINDEX_PVPMAP, siSlot)	;
		}
	}
}

void CPVP_LeagueMgr::PVP_League_Warp_Stage( SI32 siHomePersonID,SI32 siAwayPersonID, SI32 siMapIndex, SI32 siSlot )
{
	cltWarpInfo clHomeWarpInfo(1, siMapIndex, true, false, pclmapinfo[siSlot].m_HomeX, pclmapinfo[siSlot].m_HomeY, -1,  -1)	;

	SI32 Homeid = pclClient->pclCM->GetIDFromPersonID( siHomePersonID ) ;
	cltCharServer* pclHomechar = NULL;
	// ��� �������� ��ȯ �Ѵ�,.
	if( pclClient->pclCM->IsAlive(Homeid) )	pclHomechar = (cltCharServer*)pclClient->pclCM->GetCharServer( Homeid );
	if (pclHomechar )
	{
		pclHomechar->PushPVP_LeagueLatestPersonID( siAwayPersonID )	;
		pclHomechar->SetWarpInfo(&clHomeWarpInfo, 3000);
		pclHomechar->Warp();		
	}

	cltWarpInfo clAwayWarpInfo(1, siMapIndex, true, false, pclmapinfo[siSlot].m_AwayX, pclmapinfo[siSlot].m_AwayY, -1,  -1)	;
	clAwayWarpInfo.uiMapIndex = siMapIndex	;
	SI32 Awayid = pclClient->pclCM->GetIDFromPersonID( siAwayPersonID ) ;
	cltCharServer* pclAwaychar = NULL;
	// ��� �������� ��ȯ �Ѵ�,.
	if( pclClient->pclCM->IsAlive(Awayid) )	pclAwaychar = (cltCharServer*)pclClient->pclCM->GetCharServer( Awayid );
	if (pclAwaychar )
	{
		pclAwaychar->PushPVP_LeagueLatestPersonID( siHomePersonID )	;
		pclAwaychar->SetWarpInfo(&clAwayWarpInfo, 3000);
		pclAwaychar->Warp();
		
	}
}

void CPVP_LeagueMgr::PVP_LeagueStart()
{	
	cltServer* pclserver = (cltServer*)pclClient;

	for ( SI32 siSlot = 0 ; siSlot < MAX_MATCHING_PERSON ; siSlot++ ) 
	{
		// ������ ��� ���� 
		SI32 siHomePerson = m_clPVP_LeageMatchingList.GetBattlePersonIDHome(siSlot)	;
		SI32 siAwayPerson = m_clPVP_LeageMatchingList.GetBattlePersonIDAway(siSlot)	;
		if ( siHomePerson <= 0 && siAwayPerson <= 0)						continue	;

		SI32 siHomeId		=	pclserver->pclCM->GetIDFromPersonID(siHomePerson)	;
		SI32 siAwayId		=	pclserver->pclCM->GetIDFromPersonID( siAwayPerson)	;

		cltCharServer* pclHomeChar = NULL;
		cltCharServer* pclAwayChar = NULL;

		if( pclClient->pclCM->IsAlive( siHomeId) )		pclHomeChar = pclClient->pclCM->GetCharServer(siHomeId);	
		if( pclClient->pclCM->IsAlive( siAwayId) )		pclAwayChar = pclClient->pclCM->GetCharServer(siAwayId);	

		if( pclHomeChar )
		{
			pclHomeChar->siPVPWaitRequestId		=	siHomeId			;// PVP ��û�� ��� ID
			pclHomeChar->siPVPWaitAcceptId		=	siAwayId			;// PVP ��û�� �޾Ƽ� ok �� ��� ID

			pclHomeChar->SetPVP_LeagueEnemyPersonID( siAwayPerson )	;

			cltGameMsgResponse_PVP_Request clAcceptToRequest( READY_PVP,0,0,TEXT(""));	// ���� ��ٸ���� �޼����� �����ش� ���� �ð��� ������.
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
			pclHomeChar->SendNetMsg((sPacketHeader*)&clMsg);
		}

		if( pclAwayChar )
		{
			pclAwayChar->siPVPWaitRequestId		=	siHomeId			;// PVP ��û�� ��� ID
			pclAwayChar->siPVPWaitAcceptId		=	siAwayId			;// PVP ��û�� �޾Ƽ� ok �� ��� ID

			pclAwayChar->SetPVP_LeagueEnemyPersonID( siHomePerson )	;

			//���� Ŭ���̾�Ʈ�� �˷��ش�.
			cltGameMsgResponse_PVP_Request clclAcceptToAccepeter( READY_PVP ,0,0,TEXT(""));// ��ٸ���� �޼����� �����ش� �����ð��� ������
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclAcceptToAccepeter), (BYTE*)&clclAcceptToAccepeter );
			pclAwayChar->SendNetMsg((sPacketHeader*)&clMsg2);
		}
	}
}

void CPVP_LeagueMgr::PVP_LeagueMapInfo()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/PVPMapInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/PVPMapInfo.txt") );
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile PVPMapInfo"),TEXT("Error"));
		return;
	}

	SI32 pslot,pmapindex, phomeX,phomeY,pawayX,pawayY;

	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&pslot,	4,
			NDATA_INT32,	&pmapindex,	4,
			NDATA_INT32,	&phomeX,	4,
			NDATA_INT32,	&phomeY,	4,
			NDATA_INT32,	&pawayX,	4,
			NDATA_INT32,	&pawayY,	4,
			0,0,0
	};

	dataloader.RegDataType( pDataTypeInfo );


	SI16 index = 0 ;

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData( true ))	
		{
			pclmapinfo[index].m_slot	=	pslot	;
			pclmapinfo[index].m_index	=	pmapindex	;
			pclmapinfo[index].m_HomeX	=	phomeX	;
			pclmapinfo[index].m_HomeY	=	phomeY	;
			pclmapinfo[index].m_AwayX	=	pawayX	;
			pclmapinfo[index].m_AwayY	=	pawayY	;
			index++;
		}
	}
}

void CPVP_LeagueMgr::PVP_Battle_Step_Draw( void )
{
	for (SI32 siSLot = 0 ; siSLot < MAX_MATCHING_PERSON; siSLot++) 
	{
		SI32 siHome = m_clPVP_LeageMatchingList.GetBattlePersonIDHome(siSLot)	;
		SI32 siAway = m_clPVP_LeageMatchingList.GetBattlePersonIDAway(siSLot)	;
		if ( siHome == 0 && siAway == 0 )	continue	;

		End_PVP_Battle_Draw(siHome,siAway);
		LogDraw( siHome,siAway )	;
	}	
}

void CPVP_LeagueMgr::PVP_Battle_Step_Game( void )
{
	// ���� ���� - ��, ��, ����� ó���Ѵ�.
	for (SI32 siSLot = 0 ; siSLot < MAX_MATCHING_PERSON; siSLot++) 
	{
		SI32 siHome = m_clPVP_LeageMatchingList.GetBattlePersonIDHome(siSLot)	;
		SI32 siAway = m_clPVP_LeageMatchingList.GetBattlePersonIDAway(siSLot)	;
		if ( siHome == 0 && siAway == 0 )	continue	;

		SI32 siHomeCharID = pclClient->pclCM->GetIDFromPersonID( siHome );
		SI32 siAwayCharID = pclClient->pclCM->GetIDFromPersonID( siAway );

		bool IsHomeLose = false;		// �������� �������� ã�´�.
		bool IsAwayLose = false;		// �������� �������� ã�´�.

		cltCharServer* pclCharHome = pclClient->pclCM->GetCharServer( siHomeCharID );
		cltCharServer* pclCharAway = pclClient->pclCM->GetCharServer( siAwayCharID );

		if( pclClient->pclCM->IsAlive( siHomeCharID ) == false ||		// ������� �ʰų�, ĳ���Ͱ� ���°��� ���Ŵ�.
			pclCharHome->pclCI->GetPersonID() != siHome )				// ĳ���Ͱ� �ٲ���� ���Ŵ�.
		{	IsHomeLose = true;	}

		if( pclClient->pclCM->IsAlive( siAwayCharID ) == false ||		// ������� �ʰų�, ĳ���Ͱ� ���°��� ���Ŵ�.
			pclCharAway->pclCI->GetPersonID() != siAway )				// ĳ���Ͱ� �ٲ���� ���Ŵ�.
		{	IsAwayLose = true;	}

		if( Is_MatchingListPeron_TruePosition( siHome ) == false )		// ���׸ʿ� ���� ������ ���Ŵ�.
		{	IsHomeLose = true;	}

		if( Is_MatchingListPeron_TruePosition( siAway ) == false )		// ���׸ʿ� ���� ������ ���Ŵ�.
		{	IsAwayLose = true;	}

		if( IsHomeLose == true && IsAwayLose == true )
		{
			// �Ѵ� ������ ���.
			End_PVP_Battle_Draw( siHome, siAway );
		}
		else if ( IsHomeLose == true && IsAwayLose == false)
		{
			// Away �̱�
			End_PVP_Battle_End( siAway, siHome );
		}
		else if( IsHomeLose == false && IsAwayLose == true )
		{
			// Home �̱�
			End_PVP_Battle_End( siHome, siAway );
		}
	}	
}

void CPVP_LeagueMgr::PVP_Battle_HaveItemMessage( SI32 siID, SI32 siItemUnique )	// �������� �޾Ҵٰ� ��ǰ����â�� �̿��ؼ� �˸���.
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID ;//pclClient->pclCM->GetIDFromPersonID(siPersonID ); // ���̵� ������ �´�.
	if ( pclClient->pclCM->IsValidID( siId ) == false )		return	;
	SI32 siParentID = pclClient->pclCM->CR[ siId ]->GetSummonParentID()		;
	if ( siParentID == 0 )	siParentID = siId		;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;
	SI16 brareswitch = 0 ;
	cltItem clitemGoal;	
	pclserver->pclItemManager->MakeRandItemUnique(siItemUnique, &clitemGoal, 0, 0,&brareswitch , 0, 0, 0, 0, 0, 0);
	// ��ǰ �˸� ������ ����Ͽ� ������ ȹ���� �˸���.
	cltGameMsgResponse_RareItemMade	clinfo((TCHAR*)(pclChar->GetName()), pclChar->pclCI->GetPersonID(), 
		&clitemGoal,
		RARAITEM_NOTICE_SWITCH_PVPLEAGUEPRIZE,
		0);
	cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMMADE, sizeof(clinfo), (BYTE*)&clinfo);
	pclClient->pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
}

void CPVP_LeagueMgr::PVP_League_Before1m( void )
{
	for ( SI32 siIndex=0; siIndex<MAX_MATCHING_PERSON; ++siIndex ) 
	{
		//�� ������ ��Ī ����Ʈ�� �ִ� ����� ã�Ƽ�
		SI32 siHomePersonID	=	m_clPVP_LeageMatchingList.GetBattlePersonIDHome(siIndex)	;
		SI32 siAwayPersonID	=	m_clPVP_LeageMatchingList.GetBattlePersonIDAway(siIndex)	;
		if ( siHomePersonID <= 0 && siAwayPersonID <= 0 )	continue	;	// 0�̸� ���� ����

		SI32 siHomeID = pclClient->pclCM->GetIDFromPersonID( siHomePersonID)	;
		SI32 siAwayID = pclClient->pclCM->GetIDFromPersonID(siAwayPersonID)	;
		cltCharServer* pclHomeChar = pclClient->pclCM->GetCharServer(siHomeID);
		cltCharServer* pclAwayChar = pclClient->pclCM->GetCharServer(siAwayID);

		if( pclHomeChar )
		{
			cltGameMsgResponse_PVP_Request cltoHome( PVP_LEAGUEBEFORE1M ,0,0,TEXT(""))	;
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(cltoHome), (BYTE*)&cltoHome )	;
			pclHomeChar->SendNetMsg((sPacketHeader*)&clMsg)	;
		}

		if( pclAwayChar )
		{
			cltGameMsgResponse_PVP_Request clToAway( PVP_LEAGUEBEFORE1M ,0,0,TEXT(""))	;
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clToAway), (BYTE*)&clToAway )	;
			pclAwayChar->SendNetMsg((sPacketHeader*)&clMsg2)	;
		}
	}
}

// �Ϲ� ���� ������
void CPVP_LeagueMgr::PVP_League_GiveItem( SI32 siID, SI32 siItemUnique, bool bSpecial )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = siID	;
	if ( pclClient->pclCM->IsValidID( siID ) == false )		return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siId);			if(pclChar == NULL)			return ;

	SI32 siSpecial = 0	;
	if(bSpecial == true)	{siSpecial = INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE_SPECIAL	;	}
	else {siSpecial	=	INPUTITEMPERSON_OPTION_PVPLEAGUEPRIZE	;	}

	SI32 siRewardItemUnique	=	siItemUnique ;
	if( siRewardItemUnique ) 
	{
		cltItem clItem;
		SI16 brareswitch = 0;
		if ( pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique,&clItem,0,0,&brareswitch,0,0,0,0,0) == true ) 
		{
			clItem.siItemNum = 1;
			SI32 rtnvalue = 0;
			if(pclChar->InputItem(pclClient->pclItemManager, &clItem, siSpecial, &rtnvalue))
			{
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α�] �������� �ش�
					pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_GIFT, 
						0, pclChar,NULL ,0, 0, 0, &clItem, 0, 0, 0, 0, 0, 0, 
						0, 0, 0, 0, 0, NULL, NULL);
				}

				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPLEAGUE_GIVEITEM \t PERSONNAME : [%s]\t \tITEM : [%d]\t NUM : [%d] Time"),
					pclChar->GetName(),clItem.siUnique,clItem.siItemNum,szBuffer0 );
			}
			else
			{
				if(rtnvalue == CANADDINV_FAIL_FULL)
				{
					pclserver->SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclChar->GetCharUnique());
				}
			}
		}		
	}
}

void CPVP_LeagueMgr::LogWinLose( SI32 siWinnerPersonId , SI32 siLoserPersonId )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	// Ȩ�� ����� �۽����̵� ������ �´�.
	SI32 siWinnerId	=	pclClient->pclCM->GetIDFromPersonID( siWinnerPersonId )	;
	SI32 siLoserId	=	pclClient->pclCM->GetIDFromPersonID( siLoserPersonId )	;
	if ( pclClient->pclCM->IsValidID( siWinnerId ) == false )	return	;
	if ( pclClient->pclCM->IsValidID( siLoserId ) == false )	return	;
	cltCharServer* pclWinnerChar = pclClient->pclCM->GetCharServer(siWinnerId)	;			if(pclWinnerChar == NULL)			return	;
	cltCharServer* pclLoserChar = pclClient->pclCM->GetCharServer(siLoserId)	;			if(pclLoserChar == NULL)			return	;

	SI16 siWinnerActiveWeapone = pclWinnerChar->ActiveWeapon	;
	SI16 siLoserActiveWeapone = pclLoserChar->ActiveWeapon	;
	SI32 siWinnerWeaponeITemType = pclWinnerChar->pclCI->clCharItem.clItem[siWinnerActiveWeapone].GetType( pclClient->pclItemManager)	;
	SI32 siLoserWeaponeITemType = pclLoserChar->pclCI->clCharItem.clItem[siLoserActiveWeapone].GetType( pclClient->pclItemManager)	;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// para1 = �̱��ɸ��� �ɸ��� ,para2 : �̱��� ������ Ÿ��  para3 �� �ɸ���  para3 : ����� ������ Ÿ��
		// PCK : ���� - PersonID�� ĳ�����̸��� ���ؼ� ���� ���� �����Ѵ�. (09.07.31)

		TCHAR szCharName[100];
		ZeroMemory(szCharName, sizeof(szCharName));
		StringCchPrintf(szCharName, sizeof(szCharName), TEXT("WinnerChar:%s, LoserChar:%s"), pclWinnerChar->GetName(), pclLoserChar->GetName());

		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_RESULT, 
			0,NULL ,NULL,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
			pclWinnerChar->pclCI->GetPersonID(),siWinnerWeaponeITemType, pclLoserChar->pclCI->GetPersonID(), siLoserWeaponeITemType, 0, szCharName, NULL);
	}
	// ������ �����.
	TCHAR fileNameBuffer[256];
	//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
	TCHAR szTime[128];
	TCHAR szBuffer0[128];
	SYSTEMTIME stTimeInfo;
	GetLocalTime(&stTimeInfo);
	StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
	StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
	StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
		, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

	pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
		TEXT(" PVPLEAGUE_RESULT \t Winner : [%s]\tLoser : [%s]\t \t WinnerWeapone vs LoserWeapone : [%d] vs [%d] \tTime"),
		pclWinnerChar->GetName(),pclLoserChar->GetName(),siWinnerWeaponeITemType,siLoserWeaponeITemType,szBuffer0 );
}

void CPVP_LeagueMgr::LogDraw( SI32 siDrawPersonId1 , SI32 siDrawPersonId )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	// Ȩ�� ����� �۽����̵� ������ �´�.
	SI32 siDrawId1	=	pclClient->pclCM->GetIDFromPersonID( siDrawPersonId1 )	;
	SI32 siDrawId2	=	pclClient->pclCM->GetIDFromPersonID( siDrawPersonId )	;
	if ( pclClient->pclCM->IsValidID( siDrawId1 ) == false )	return	;
	if ( pclClient->pclCM->IsValidID( siDrawId2 ) == false )	return	;
	cltCharServer* pclDrawChar1 = pclClient->pclCM->GetCharServer(siDrawId1)	;			if(pclDrawChar1 == NULL)			return	;
	cltCharServer* pclDrawChar2 = pclClient->pclCM->GetCharServer(siDrawId2)	;			if(pclDrawChar2 == NULL)			return	;

	SI16 siDraw1ActiveWeapone = pclDrawChar1->ActiveWeapon	;
	SI16 siDraw2ActiveWeapone = pclDrawChar2->ActiveWeapon	;

	SI32 siDraw1WeaponeITemType = pclDrawChar1->pclCI->clCharItem.clItem[siDraw1ActiveWeapone].GetType( pclClient->pclItemManager)	;
	SI32 siDraw2WeaponeITemType = pclDrawChar2->pclCI->clCharItem.clItem[siDraw2ActiveWeapone].GetType( pclClient->pclItemManager)	;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// para1 = ��� �ɸ��� 1 para2 ��� �ɸ��� 
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_RESULT_DRAW, 
			0,NULL ,NULL,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			pclDrawChar1->pclCI->GetPersonID(), pclDrawChar2->pclCI->GetPersonID(), 0, 0, 0, NULL, NULL);
	}

	// ������ �����.
	TCHAR fileNameBuffer[256];
	//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
	TCHAR szTime[128];
	TCHAR szBuffer0[128];
	SYSTEMTIME stTimeInfo;
	GetLocalTime(&stTimeInfo);
	StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
	StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
	StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
		, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

	pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
		TEXT(" PVPLEAGUE_DRAW \t Person1 : [%s]\t Person2 : [%s]\t Weapone VS Weapone : [%d] vs [%d][]Time"),
		pclDrawChar1->GetName(),pclDrawChar2->GetName(),siDraw1WeaponeITemType,siDraw2WeaponeITemType,szBuffer0 );
}

void CPVP_LeagueMgr::LogGoal( SI32 siPersonID , SI32 siGoalFlag )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siID	=	pclClient->pclCM->GetIDFromPersonID( siPersonID )	;
	if ( pclClient->pclCM->IsValidID( siID ) == false )	return	;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siID)	;			if(pclChar == NULL)			return	;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// prar1�� ��ǥ �޼� ����
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_GOAL, 
			0,pclChar ,NULL,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			siGoalFlag, 0, 0, 0, 0, NULL, NULL);
	}

	// ������ �����.
	TCHAR fileNameBuffer[256];
	//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
	TCHAR szTime[128];
	TCHAR szBuffer0[128];
	SYSTEMTIME stTimeInfo;
	GetLocalTime(&stTimeInfo);
	StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
	StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
	StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
		, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

	if ( siGoalFlag == PVP_LEAGUE_END_RESULT_100WIN) 
	{
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_Goal \t NAME : [%s]\t GoalFlag : [%d]\t Time"),
			pclChar->GetName(),PVP_LEAGUE_END_RESULT_100WIN,szBuffer0 );
	}
	else if ( siGoalFlag == PVP_LEAGUE_END_RESULT_1000WIN) 
	{
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_Goal \t NAME : [%s]\t GoalFlag : [%d]\t Time"),
			pclChar->GetName(),PVP_LEAGUE_END_RESULT_1000WIN,szBuffer0 );
	}
	else if ( siGoalFlag == PVP_LEAGUE_END_RESULT_100DRAW) 
	{
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_Goal \t NAME : [%s]\t GoalFlag : [%d]\t Time"),
			pclChar->GetName(),PVP_LEAGUE_END_RESULT_100DRAW,szBuffer0 );
	}
	else if ( siGoalFlag == PVP_LEAGUE_END_RESULT_1000DRAW) 
	{
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_Goal \t NAME : [%s]\t GoalFlag : [%d]\t Time"),
			pclChar->GetName(),PVP_LEAGUE_END_RESULT_1000DRAW,szBuffer0 );
	}
}

void CPVP_LeagueMgr::LogReserve( SI32 siPersonID )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = pclClient->pclCM->GetIDFromPersonID( siPersonID )	;
	if ( pclClient->pclCM->IsValidID( siId ) == false )		return	;
	SI32 siParentID = pclClient->pclCM->CR[ siId ]->GetSummonParentID()		;
	if ( siParentID == 0 )	siParentID = siId		;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : �ռ����� 2008. 10. 29] // pvp Ÿ�ٿ� ��û
		// Ÿ�� personID 
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_RESERVE, 
			0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, NULL, NULL);
	}

	// ������ �����.
	TCHAR fileNameBuffer[256];
	//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
	TCHAR szTime[128];
	TCHAR szBuffer0[128];
	SYSTEMTIME stTimeInfo;
	GetLocalTime(&stTimeInfo);
	StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
	StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
	StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
		, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

	pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
		TEXT(" PVPLEAGUE_RESERVE \t PERSONNAME : [%s]\t Time"),
		pclChar->GetName(),szBuffer0 );
}

void CPVP_LeagueMgr::LogGradeUpDown( SI32 siPersonID,SI32 siBeforeGrade, SI32 siAfterGrade, SI32 UpDownFlag )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId = pclClient->pclCM->GetIDFromPersonID( siPersonID )	;
	if ( pclClient->pclCM->IsValidID( siId ) == false )		return	;
	SI32 siParentID = pclClient->pclCM->CR[ siId ]->GetSummonParentID()		;
	if ( siParentID == 0 )	siParentID = siId		;
	cltCharServer* pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;
	if ( LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_UP == UpDownFlag ) 
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// para1 : ���� ��� para2 : ���ĵ��
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_UP, 
				0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				siBeforeGrade, siAfterGrade, 0, 0, 0, NULL, NULL);
		}
		// ������ �����.
		TCHAR fileNameBuffer[256];
		//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
		TCHAR szTime[128];
		TCHAR szBuffer0[128];
		SYSTEMTIME stTimeInfo;
		GetLocalTime(&stTimeInfo);
		StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
		StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
		StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
			, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

		pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
			TEXT(" PVPLEAGUE_GRADEUP \t PERSONNAME:[%s] \t BEFOREGRADE:[%d] \t AFTERGRADE:[%d] \t Time"),
			pclChar->GetName(),siBeforeGrade,siAfterGrade,szBuffer0 );
	}
	else if ( LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_DOWN == UpDownFlag) 
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// para1 : ���� ��� para2 : ���ĵ��
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP_LEAGUE, LOGCOMMAND_INDEX_PVP_LEAGUE_GRADE_DOWN, 
				0, pclChar,NULL ,0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				siBeforeGrade, siAfterGrade, 0, 0, 0, NULL, NULL);
		}

		// ������ �����.
		TCHAR fileNameBuffer[256];
		//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
		TCHAR szTime[128];
		TCHAR szBuffer0[128];
		SYSTEMTIME stTimeInfo;
		GetLocalTime(&stTimeInfo);
		StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
		StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
		StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLeagueLog_%04d%02d%02d.log") 
			, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );

		pclChar = pclClient->pclCM->GetCharServer(siParentID);			if(pclChar == NULL)			return ;
		pclClient->pclLog->FilePrint(TEXT(fileNameBuffer),
			TEXT(" PVPLEAGUE_GRADEDOWN \t PERSONNAME:[%s] \t BEFOREGRADE:[%d] \t AFTERGRADE:[%d] \t Time"),
			pclChar->GetName(),siBeforeGrade,siAfterGrade,szBuffer0 );
	}	
}

bool CPVP_LeagueMgr::InMatchingList( SI32 siPersonID )	// ���� ��Ī ����Ʈ�� �ִ��� Ȯ�� �Ѵ�.
{
	return (m_clPVP_LeageMatchingList.FindPersonID( siPersonID ) > 0 );
}

SI32 CPVP_LeagueMgr::GetEnemyPersonID( SI32 siPersonID )	// ���� ���� �ִ��� Ȯ�� �Ѵ�
{
	return m_clPVP_LeageMatchingList.FindEnemyPersonID( siPersonID );
}

bool CPVP_LeagueMgr::InEndGameList( SI32 siPersonID )	// ���� EndGame ����Ʈ�� �ִ��� Ȯ�� �Ѵ�.
{
	return ( m_clPVP_Leage_EndGameList.FindPersonID( siPersonID ) > 0);
}

// �ش� �۽����̵��� ����� ��Ī����Ʈ�� �ְ� ������ġ�� �ִ��� �������� Ȯ�� �ϱ� ���� 
bool CPVP_LeagueMgr::Is_MatchingListPeron_TruePosition( SI32 siPersonID )
{
	cltServer* pclserver = (cltServer*)pclClient	;

	SI32 siId		=	pclserver->pclCM->GetIDFromPersonID(siPersonID)	;
	if( pclserver->pclCM->IsValidID( siId ) == false )		return	false	; // ��û�� ����� �������� ID�ΰ� Ȯ��
	cltCharServer* pclChar = pclserver->pclCM->GetCharServer(siId);			if(pclChar == NULL)		return	false ;

	// ���� �Ҷ� ��Ȯ�� ������ �ִ��� Ȯ�� �Ѵ�.
	SI32 siMapIndex = pclChar->GetMapIndex()	;
	cltMapCommon* pclmap = pclClient->pclMapManager->GetMapPointer( siMapIndex )	;
	if ( pclmap != NULL	 )
	{
		SI32 siColl = pclmap->GetCollMap(	pclChar->GetX() , pclChar->GetY()	)	;

		if( MAPINDEX_MAINFIELD == siMapIndex ) 
		{
			if ( siColl & BLOCK_EVENT4 ) //PVP���� ���̰� ����� ������ ���� �ϸ� 
			{
				return true ;
			}
		}

		else if ( MAPINDEX_PVPMAP == siMapIndex ) 
		{
			if ( siColl & BLOCK_EVENT4 ) //PVP���� ���̰� ����� ������ ���� �ϸ� 
			{
				return true ;
			}
		}
	}

	return false	;
}

SI32 CPVP_LeagueMgr::GetTotalScore( SI32 siSourcePersonID, SI32 siDestPersonID )
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( NULL == pclserver )
	{
		return 0;
	}

	SI32			siSourceCharID	= pclserver->pclCM->GetIDFromPersonID( siSourcePersonID );
	cltCharServer*	pclSourceChar	= pclserver->pclCM->GetCharServer( siSourceCharID );
	if ( NULL == pclSourceChar )
	{
		return 0;
	}

	SI32			siDestCharID	= pclserver->pclCM->GetIDFromPersonID( siDestPersonID );
	cltCharServer*	pclDestChar		= pclserver->pclCM->GetCharServer( siDestCharID );
	if ( NULL == pclDestChar )
	{
		return 0;
	}

	// Ư���� ����ڸ� �̱����� �� ���ǵ鿡 ������ �ο��Ѵ�
	SI32 siGradeScore	= (pclSourceChar->GetPVP_LeagueGrade() + pclDestChar->GetPVP_LeagueGrade()) * 10000000;
	SI32 siLevelScore	= (pclSourceChar->pclCI->clIP.GetLevel() + pclDestChar->pclCI->clIP.GetLevel()) * 10000;
	SI32 siWinScore		= (pclSourceChar->GetPVP_LeagueStraight_Win() + pclDestChar->GetPVP_LeagueStraight_Win());

	SI32 siTotalScore	= siGradeScore + siLevelScore + siWinScore;

	return siTotalScore;
}


//PVP���׿��� �׷��̵� ������ ���������Ϸ� ���� �о� �´�.
void CPVP_LeagueMgr::PVP_LeagueGradeInfo()
{
	NDataLoader	dataloader;
	BOOL bLoadFile=FALSE;

	//KHY - 0810 - �ؽ�Ʈ ���ҽ� ��ȣȭ.
	if( pclClient->IsWhereServiceArea( ConstSwitch_TextEncryption ) )
	{
		bLoadFile = dataloader.LoadDataFromCryptFile( TEXT("Data/PVPGradeInfo.txt") );
	}
	else
	{
		bLoadFile = dataloader.LoadDataFromFile( TEXT("Data/PVPGradeInfo.txt") );
	}

	if (!bLoadFile)
	{
		MsgBox( TEXT("Not LoadFromFile PVP_League_Grade"),TEXT("Error"));
		return;
	}

	SI32 pGrade, pGradeValue,pUpWin, pDownLose;

	// pGradePostion�� �׷��̵� 1��� 2��� �̷��� pGradeUnique�� PVP_LEAGUE_GRADE_MAX������, pGradeValue�� �������� ���̴� ��
	NDataTypeInfo pDataTypeInfo[] =
	{
		NDATA_INT32,	&pGrade,	4,
			NDATA_INT32,	&pGradeValue,	4,
			NDATA_INT32,	&pUpWin,	4,
			NDATA_INT32,	&pDownLose,	4,
			0,0,0
	};	
	dataloader.RegDataType( pDataTypeInfo );

	SI16 index = 0 ;

	while( !dataloader.IsEndOfData() ) 
	{
		if (dataloader.ReadData( true ))	
		{
			pclGradeInfo[index].m_Grade			=	pGrade;
			pclGradeInfo[index].m_GradeValue	=	pGradeValue;
			pclGradeInfo[index].m_UpWin			=	pUpWin;		// ���� ��޿� �ö󰥼� �ִ� ���� �¼�
			pclGradeInfo[index].m_DownLose		=	pDownLose;	// ���� ������� �������� �ִ� ���� �м�
			m_siLastGradeIndex = index	;						// ������ �׷��̵��� ��ġ�� �˱� ���ؼ�
			index++;
		}
	}
}
// ���� ����� ������ ���� ����� �����Ѵ�.
SI32 CPVP_LeagueMgr::ChangeGrade( SI32 GradeNow, SI32 WinLoseCount, SI32 siUpDown )
{
	// GradeNow�� GetPVP_LeagueGrade()�ؼ� ���� �����μ� ���ҽ��� value���� ����.�׷��� value ���� ���� ã�´�.�׷��� ���� ��ġ��
	// grade�� �˼� �ִ�.
	SI32 siGradeNow				=	0	;	// �̰� ���� �� ���� ���
	SI32 siChangedGradevalue	=	GradeNow	;	// �⺻ �����δ� ���� ���
	SI32 siUpWins	=	0	;
	SI32 siDownLose	=	0	;
	for ( SI32 siIndex = 0; siIndex <MAX_GRADECOUNT ; siIndex++) 
	{
		if( pclGradeInfo[ siIndex ].m_GradeValue == GradeNow )
		{
			siGradeNow = pclGradeInfo[ siIndex ].m_Grade	;	// �̰� �̻���� ���� ����̴�. 1����̸� 1�̷��� ���´�.
			siUpWins = pclGradeInfo[ siIndex ].m_UpWin	;		// ��� ��¿� �ʿ��� ���� �¼�
			siDownLose = pclGradeInfo[ siIndex ].m_DownLose	;	// ��� �϶��� �ʿ��� ���� �м�
			break;
		}
	}
	switch( siUpDown )  
	{
	case PVP_LEAGUE_END_GRADEUP :
		{
			if(siUpWins == WinLoseCount)
			{
				SI32 siChangedGrade = siGradeNow - 1	;
				if( siChangedGrade > 0 )
				{
					siChangedGradevalue	=	pclGradeInfo[ siChangedGrade ].m_GradeValue	;// �ѵ�� �ø���. 
				}
				else	// 0�� ���ų� �����Ƿ� ���̻� ����� ������ ���� �׷��ϱ� ���� ����� �־� �ش�.
				{
					siChangedGradevalue	=	pclGradeInfo[ siGradeNow ].m_GradeValue	;
				}				
			}
		}
		break;
	case PVP_LEAGUE_END_GRADEDOWN :
		{
			if(siDownLose == WinLoseCount)
			{
				SI32 siChangedGradeindex = siGradeNow + 1	;
				if( siChangedGradeindex < m_siLastGradeIndex && siChangedGradeindex != 0  )
				{
					siChangedGradevalue	=	pclGradeInfo[ siChangedGradeindex ].m_GradeValue	;	// �ѵ�� ������.
				}
				else	// 0�� ���ų� �����Ƿ� ���̻� ����� ������ ���� �׷��ϱ� ���� ����� �־� �ش�.
				{
					siChangedGradevalue	=	pclGradeInfo[ m_siLastGradeIndex ].m_GradeValue	;
				}
			}
		}
		break;	
	}
	return siChangedGradevalue	;
}

SI32 CPVP_LeagueMgr::GetMyGradeFromGradeValue( SI32 GradeValue)
{
	SI32 siGradeNow	=	0;
	for ( SI32 siGrade = 0 ; siGrade <MAX_GRADECOUNT ; siGrade++) 
	{
		if( pclGradeInfo[ siGrade ].m_GradeValue == GradeValue )
		{
			siGradeNow = pclGradeInfo[ siGrade ].m_Grade	;	// �̰� �̻���� ���� ����̴�. 1����̸� 1�̷��� ���´�.
		}
	}
	return siGradeNow	;
}