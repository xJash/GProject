
#include "Char/CharManager/CharManager.h"
#include "../Server/Server.h"

#include "../../CommonLogic/Marriage/MarriageManager.h"
#include "../../CommonLogic/Marriage/WeddingManager.h"

#include "../../common/Order/order.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Wedding.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-Wedding.h"


void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_RESERVE(cltMsg* pclMsg, SI32 id )
{
	if ( NULL ==  m_pclMarriageMgr )
	{
		return;
	}

	cltGameMsgRequest_WeddingReserve* pclinfo = (cltGameMsgRequest_WeddingReserve*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{	
		return;
	}

	// ��ȥ ���ߴٸ�
	if ( FALSE == pclChar->IsMarried() )
	{
		return;
	}

	SI32 siGetPersonID = pclChar->pclCI->GetPersonID();
	if ( 0 >= siGetPersonID )
	{
		return;
	}

	SI16 siYear				= pclinfo->m_siYear;
	SI16 siMonth			= pclinfo->m_siMonth;
	SI16 siDay				= pclinfo->m_siDay;
	SI16 siHour				= pclinfo->m_siHour;

	SI32 siReserveResult	= m_pclMarriageMgr->m_clWeddingList.CanReserve( siYear, siMonth, siDay, siHour, siGetPersonID );
	if ( WEDDING_RESERVE_RESULT_SUCCESS != siReserveResult )
	{
		return;
	}
 
	// ���� ���
	// ���ذ��ݿ� ���� ���� �̾ƿ´�
	SI32 siNpcRate = pclItemManager->clItemStatistic.siNPCPriceRate;
	siNpcRate = siNpcRate / 500;

	// ������ ����ϰ�
	GMONEY siReserveCost = (WEDDING_RESERVE_BASIC_COST) * ( 2.5 * siNpcRate );
	if ( 0 >= siNpcRate )
	{
		siReserveCost = (WEDDING_RESERVE_BASIC_COST);
	}

	// ���࿡ ���� üũ
	if ( siReserveCost > pclChar->pclCI->clBank.GetMoney() )
	{
		return;
	}

	SYSTEMTIME stReserveTime;
	ZeroMemory( &stReserveTime, sizeof(stReserveTime) );

	stReserveTime.wYear		= siYear;
	stReserveTime.wMonth	= siMonth;
	stReserveTime.wDay		= siDay;
	stReserveTime.wHour		= siHour;

	sDBRequest_WeddingReserve clMsg( siGetPersonID, siReserveCost, stReserveTime );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}
void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_SIMPLELIST_GET(cltMsg* pclMsg, SI32 id )
{
	if ( NULL ==  m_pclMarriageMgr )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{	
		return;
	}

	cltGameMsgResponse_WeddingSimpleListGet	clSimpleList;
	cltWeddingReserveUnit*					pclSimpleUnit = NULL;

	SI16 siCurrentYear		= sTime.wYear;
	SI16 siCurrentMonth		= sTime.wMonth;
	SI16 siCurrentDay		= sTime.wDay;
	SI16 siCurrentHour		= sTime.wHour;

	SI16 siReserveStatus	= WEDDING_RESERVE_STATUS_NONE;

	for ( SI32 siIndex=0; siIndex<WEDDING_RESERVE_LIST_NUM; siIndex++ )
	{
		pclSimpleUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siIndex );
		if ( NULL == pclSimpleUnit )
		{
			continue;
		}

		// ����Ǿ������� �װ��� ���� �ð��̶�� �������̶�� ǥ���Ѵ�
		if ( (0 < pclSimpleUnit->m_siMate1_PersonID) || (0 < pclSimpleUnit->m_siMate2_PersonID) )
		{
			if ( TRUE == pclSimpleUnit->IsSameTime(siCurrentYear, siCurrentMonth, siCurrentDay, siCurrentHour) )
			{
				siReserveStatus = WEDDING_RESERVE_STATUS_PROGRESS;
			}
			else
			{
				siReserveStatus = WEDDING_RESERVE_STATUS_RESERVE;
			}
		}
		else
		{
			siReserveStatus = WEDDING_RESERVE_STATUS_NONE;
		}

		clSimpleList.m_clSimpleUnit[siIndex].Set( pclSimpleUnit->m_stReserveTime, siReserveStatus );
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_WEDDING_SIMPLELIST_GET, sizeof(clSimpleList), (BYTE*)&clSimpleList );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_QUESTION_ANSWER(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_WeddingQuestionAnswer* pclinfo = (cltGameMsgRequest_WeddingQuestionAnswer*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	SI32 siMyPersonID = pclChar->pclCI->GetPersonID();

	cltWeddingReserveUnit* pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtrFromNowTime();
	if ( NULL == pclUnit )
	{
		return;
	}

	if ( FALSE == pclUnit->IsReserved() )
	{
		return;
	}

	// ������ ���� �� ����� ������ �߿� ���ٸ�
	if ( (siMyPersonID != pclUnit->m_siMate1_PersonID) && (siMyPersonID != pclUnit->m_siMate2_PersonID) )
	{
		return;
	}

	// ���� ���¶� �ٸ��ٸ� �� �� �°�!!
	if ( pclinfo->m_siAnswerKind != m_pclMarriageMgr->GetWeddingStatus() )
	{
		return;
	}

	SI32 siChangeStatus = 0;
	switch ( pclinfo->m_siAnswerKind )
	{
	case MARRIAGE_WEDDING_STATUS_MATE1_QUESTION_WAIT:	{	siChangeStatus = MARRIAGE_WEDDING_STATUS_MATE2_QUESTION;	}	break;
	case MARRIAGE_WEDDING_STATUS_MATE2_QUESTION_WAIT:	{	siChangeStatus = MARRIAGE_WEDDING_STATUS_WEDDING_END;		}	break;
	case MARRIAGE_WEDDING_STATUS_GIVEITEM_WAIT:			{	siChangeStatus = MARRIAGE_WEDDING_STATUS_GIVEITEM;			}	break;
	default:
		{
			return;
		}
	}

	if ( 0 >= siChangeStatus )
	{
		return;
	}

	m_pclMarriageMgr->ChangeWeddingStatus( siChangeStatus );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_LIST_GET(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_WeddingListGet* pclinfo = (cltGameMsgRequest_WeddingListGet*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	if ( 0 > pclinfo->m_siRequestPage )
	{
		return;
	}

	SI32 siStartPos = (pclinfo->m_siRequestPage * WEDDING_RESERVE_LIST_PAGE_PER_NUM);
	if ( WEDDING_RESERVE_LIST_NUM <= siStartPos )
	{
		return;
	}

	cltGameMsgResponse_WeddingListGet clList;

	SI32 siCount = 0;

	for ( SI32 siIndex=siStartPos; siIndex<(siStartPos+WEDDING_RESERVE_LIST_PAGE_PER_NUM); siIndex++ )
	{
		if ( WEDDING_RESERVE_LIST_NUM <= siIndex )
		{
			break;
		}

		if ( WEDDING_RESERVE_LIST_PAGE_PER_NUM <= siCount )
		{
			break;
		}

		clList.m_clUnit[siCount].Set( m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr(siIndex) );

		siCount++;
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_WEDDING_LIST_GET, sizeof(clList), (BYTE*)&clList );
	pclChar->SendNetMsg( (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_HALL_ENTER(cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	SI32					siMyPersonID	= pclChar->pclCI->GetPersonID();

	SI16					siCurrentYear	= sTime.wYear;
	SI16					siCurrentMonth	= sTime.wMonth;
	SI16					siCurrentDay	= sTime.wDay;
	SI16					siCurrentHour	= sTime.wHour;
	SI16					siCurrentMinute	= sTime.wMinute;

	cltWeddingReserveUnit*	pclUnit			= NULL;

	// ���� �������� ������ ����
	if ( (0 <= siCurrentMinute) && (30 > siCurrentMinute) )
	{
		pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siCurrentYear, siCurrentMonth, siCurrentDay, siCurrentHour );
	}
	// ���� �����ΰͿ� ������ ����
	else if ( (50 <= siCurrentMinute) && (60 > siCurrentMinute) )
	{
		SYSTEMTIME stAddTime;
		ZeroMemory( &stAddTime, sizeof(stAddTime) );

		stAddTime.wYear		= siCurrentYear;
		stAddTime.wMonth	= siCurrentMonth;
		stAddTime.wDay		= siCurrentDay;
		stAddTime.wHour		= siCurrentHour;

		TimeAddHour( &stAddTime, 1, &stAddTime );

		pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( stAddTime.wYear, stAddTime.wMonth, stAddTime.wDay, stAddTime.wHour );
	}

	if ( NULL == pclUnit )
	{
		return;
	}

	if ( FALSE == pclUnit->IsReserved() )
	{
		return;
	}

	// �������϶�
	if ( (siMyPersonID == pclUnit->m_siMate1_PersonID) || (siMyPersonID == pclUnit->m_siMate2_PersonID) )
	{
		cltWarpInfo clWarpInfo( 1, MAPINDEX_WEDDINGHALL, true, false, MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_X, MARRIAGE_WEDDING_COMEIN_MARRIAGE_PERSON_Y, -1,-1 );

		pclChar->SetWarpInfo( &clWarpInfo, 3102 );
		pclChar->Warp();
	}
	// �ϰ��϶�
	else
	{
		cltWarpInfo clWarpInfo( 1, MAPINDEX_WEDDINGHALL, true, false, MARRIAGE_WEDDING_COMEIN_CONGRATULATOR_X, MARRIAGE_WEDDING_COMEIN_CONGRATULATOR_Y, -1,-1 );

		pclChar->SetWarpInfo( &clWarpInfo, 3103 );
		pclChar->Warp();
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDING_RESERVE_CANCEL(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_WeddingReserveCancel* pclinfo = (cltGameMsgRequest_WeddingReserveCancel*)pclMsg->cData;
	if ( NULL == pclinfo )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// �ʹ� ���� ���� ���ϵ��� �Ѵ�
	if ( true == pclChar->CheckLastMsgClock( 1000 ) )
	{
		return;
	}

	// ��ȥ�� ���ߴµ� ������ ����Ҽ�����
	if ( FALSE == pclChar->IsMarried() )
	{
		return;
	}

	if ( NULL == m_pclMarriageMgr )
	{
		return;
	}

	SI16					siCancelYear	= pclinfo->m_siYear;
	SI16					siCancelMonth	= pclinfo->m_siMonth;
	SI16					siCancelDay		= pclinfo->m_siDay;
	SI16					siCancelHour	= pclinfo->m_siHour;

	cltWeddingReserveUnit*	pclUnit			= NULL;
	pclUnit = m_pclMarriageMgr->m_clWeddingList.GetReserveUnitPtr( siCancelYear, siCancelMonth, siCancelDay, siCancelHour );
	if ( NULL == pclUnit )
	{
		return;
	}

	if ( FALSE == pclUnit->IsReserved() )
	{
		return;
	}

	SI16 siCurrentYear	= sTime.wYear;
	SI16 siCurrentMonth	= sTime.wMonth;
	SI16 siCurrentDay	= sTime.wDay;
	SI16 siCurrentHour	= sTime.wHour;

	// ���� �ð� ������ ��Ұ� �Ұ����ϴ�
	if ( TRUE == pclUnit->IsSameTime(siCurrentYear, siCurrentMonth, siCurrentDay, siCurrentHour) )
	{
		return;
	}

	// ���� �� ������ �ƴϸ� �ȵ�
	SI32 siMyPersonID = pclChar->pclCI->GetPersonID();
	if ( (siMyPersonID != pclUnit->m_siMate1_PersonID) && (siMyPersonID != pclUnit->m_siMate2_PersonID) )
	{
		return;
	}

	sDBRequest_WeddingReserveCancel clMsg( siMyPersonID, pclUnit->m_siReserveNum );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MARRIAGEMATE_WARP(cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pclChar = pclCM->GetCharServer( id );
	if ( NULL == pclChar )
	{
		return;
	}

	// ��ȥ�� ���ߴµ� ���!!
	if ( FALSE == pclChar->IsMarried() )
	{
		return;
	}

	// ����� ĳ���Ͱ� �����ϰ� ������ ������ �׸��� �ȵ�
	SI32			siMateCharID	= pclCM->GetIDFromPersonID( pclChar->pclMarriage->GetMatePersonID() );
	cltCharServer*	pclMateChar		= pclCM->GetCharServer( siMateCharID );
	if ( NULL == pclMateChar )
	{
		return	;
	}

	SI32 siMateMapIndex = pclMateChar->GetMapIndex();
	SI32 siMateXPos		= pclMateChar->GetX();
	SI32 siMateYPos		= pclMateChar->GetY();

	// ��ȿ���� ���� ���̶��!!
	if ( (0 > siMateMapIndex) || (MAX_MAP_NUMBER <= siMateMapIndex) )
	{
		return;
	}

	// �ش� �� ������ ���ٸ�!!!
	if ( NULL == pclMapManager->pclMapArray[siMateMapIndex] )
	{
		return;
	}

	// ��ȿ���� ���� �����̶��!!
	if ( false == pclMapManager->IsValidArea(siMateMapIndex, siMateXPos, siMateYPos) )
	{
		return;
	}

	// ������ �������� üũ
	bool bVillageWarp = false;
	if ( (0 < siMateMapIndex) && (CUR_VILLAGE_LIMIT >= siMateMapIndex) )
	{
		if ( true == pclMapManager->pclVillageManager->IsValidVillage(siMateMapIndex) )
		{
			bVillageWarp = true;
		}
	}

	// ������������ �����Ҽ� ������?
	if ( false == pclChar->CanWarpFrom() )
	{
		return;
	}

	// �ش� �������� �����Ҽ�������?
	if ( false == pclChar->CanWarpTo(siMateMapIndex) )
	{
		return;
	}

	// �� �ɸ��ͷ� ������ �����Ҽ�������?
	if ( false == pclChar->CanWarpToChar(siMateCharID) )
	{
		return;
	}
	SI32 siWarpUnique	= 0;

	// ������ �̵��� ���
	if ( bVillageWarp )
	{
		SI32 siGetMapTypeUnique = pclMapManager->pclMapArray[siMateMapIndex]->siMapUnique;
		if (0 > siGetMapTypeUnique)
		{
			return;
		}

		siWarpUnique = 2300;
	}
	else
	{
		siWarpUnique = 2200;
	}

	if ( id )
	{
		OrderStop( id, BY_COMPUTER );

		// ���� ����Ʈ ǥ��
		cltGameMsgResponse_WarpEffect clinfo( id );
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNeighbourMsg(&clMsg, true);

		// ������ �����ϱ�
		cltWarpInfo clWarpInfo( 1, siMateMapIndex, false, true, siMateXPos, siMateYPos, -1, -1 );
		pclChar->SetWarpInfo( &clWarpInfo, siWarpUnique );
		pclChar->Warp();
	}



	

}