//----------------------------
// LeeKH 2007/04/17
//----------------------------
#include "Char\CharManager\CharManager.h"
#include "..\Server\Server.h"

#include "../common/Event/MofuMofu/MofuMofu.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-MofuMofuEvent.h"

#include "MsgRval-Define.h"
#include "Msg\MsgType-MofuMofuEvent.h"

#include "./CityHall/CityHall.h"

// ���ĸ��� �̺�Ʈ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVE(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )			return;

	cltGameMsgRequest_MofuMofuEvent_Reserve* pclinfo = (cltGameMsgRequest_MofuMofuEvent_Reserve*)pclMsg->cData;
	if(pclinfo == NULL)								return;
	
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;
	
	// [����] �ʺ��� ���� : �ʺ��� ������ ���ĸ��� �̺�Ʈ ���� �ȵǰ�
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == villageunique )
		{
			return;
		}
	}
	
	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		// ������� �ƴϴ�. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTMAYOR,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	cltCityhallEventInfo *pclEvent = pclCityHallManager->clEventManager.GetEventInfoFromEventID( CITYHALL_EVENT_MOFUMOFU );
	if( pclEvent == NULL ) return;

	// �����ڱ�(�ں���)�� ����Ѱ�?
	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if( pclStrInfo == NULL ) return;

	SI32 cost = (SI32)(pclEvent->siEventMoney * (pclItemManager->clItemStatistic.siItemPriceIndex / 10000000.));
	cost = max(cost, 2000000);

	if( pclStrInfo->clCommonInfo.clMoney.itMoney < cost ) {
		// �����ڱ� ����
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EVENT_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if(pclMofuMofuEvent->CanReserveRoom(pclinfo->m_siYear, pclinfo->m_siMonth, pclinfo->m_siDay, pclinfo->m_siHour, pclCM->CR[id]->pclCI->clBI.siHomeVillage) == FALSE)
	{
		// �̹� ��û�� �ð��Դϴ�. �ٸ� �ð��� �����Ͽ� �ֽʽÿ�.
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_MOFUMOFUEVENT_FAIL_ALREADY_RESERVE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if(pclMofuMofuEvent->ReserveRoom(pclinfo->m_siYear, pclinfo->m_siMonth, pclinfo->m_siDay, pclinfo->m_siHour, pclCM->CR[id]->pclCI->clBI.siHomeVillage) == FALSE)
	{
		// �̹� ��û�� �ð��Դϴ�. �ٸ� �ð��� �����Ͽ� �ֽʽÿ�.
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_MOFUMOFUEVENT_FAIL_ALREADY_RESERVE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	SYSTEMTIME ReserveHour;
	ZeroMemory(&ReserveHour, sizeof(ReserveHour));

	ReserveHour.wYear	= pclinfo->m_siYear;
	ReserveHour.wMonth	= pclinfo->m_siMonth;
	ReserveHour.wDay	= pclinfo->m_siDay;
	ReserveHour.wHour	= pclinfo->m_siHour;
	
	// DB�� ���������� �����Ѵ�.
	sDBRequest_MofuMofuEvent_Reserve clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), ReserveHour, pclCM->CR[id]->pclCI->clBI.siHomeVillage, cost);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_RESERVELIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_MofuMofuEvent_ReserveList*	pclinfo = (cltGameMsgRequest_MofuMofuEvent_ReserveList*)pclMsg->cData;
	if(pclinfo == NULL)								return;

	cltGameMsgResponse_MofuMofuEvent_ReserveList	clInfo;

	for(SI32 i=0; i<MOFUMOFUEVENT_ROOMNUM; i++)
	{
		cltMofuMofuEventReserveUnit* pclRoom = pclMofuMofuEvent->GetRoom(i);
		if(pclRoom == NULL)				continue;

		clInfo.m_Reserved[i].Set(pclRoom);
	}

	clInfo.m_siCount = MOFUMOFUEVENT_ROOMNUM;

	SI32 siSize = clInfo.GetSize();
	cltMsg clMsg(GAMEMSG_RESPONSE_MOFUMOFUEVENT_RESERVELIST, siSize, (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_ENTERFIELD(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResquest_MofuMofuEvent_EnterField*	pclinfo = (cltGameMsgResquest_MofuMofuEvent_EnterField*)pclMsg->cData;
	if(pclinfo == NULL)								return;

	if(pclinfo->m_siFieldIndex < 0 || pclinfo->m_siFieldIndex >= MOFUMOFUEVENT_MAXFIELD_COUNT)	return;

	SI32 siEventVillage = pclMofuMofuEvent->GetCurrentEventVillage();
	if(pclinfo->m_siInOut == 1 && siEventVillage <= 0)											return;

	if(pclinfo->m_siInOut == 1 && pclCM->CR[id]->pclCI->clBI.siHomeVillage != siEventVillage)
	{
		// �̺�Ʈ�� �����ϴ� ������ �� �� �ֽ��ϴ�.
		return;
	}

	if(pclinfo->m_siInOut == 1 && pclMofuMofuEvent->CanEnterField() == FALSE)
	{
		// �̺�Ʈ�� ���۵ǰ� 5�� �ں��� ������ �� �ֽ��ϴ�.
		return;
	}

	// �׾����� ��� ���� ����.
	if(pclCM->IsAlive(id) == FALSE)					return;

	// �ʵ�� ���� ��Ų��.
	cltWarpInfo clWarpInfo(1, 0, true, false, 0, 0, -1, -1);
	clWarpInfo.uiMapIndex = MAPINDEX_MOFUMOFULAND;

	if(pclinfo->m_siInOut == 1)
	{
		cltMofuMofuField* pclField = pclMofuMofuEvent->GetField(pclinfo->m_siFieldIndex);
		if(pclField != NULL)
		{
			clWarpInfo.uiX = pclField->m_siInPosX;
			clWarpInfo.uiY = pclField->m_siInPosY;
		}
	}
	else
	{
		cltMofuMofuField* pclField = pclMofuMofuEvent->GetField(pclinfo->m_siFieldIndex);
		if(pclField != NULL)
		{
			clWarpInfo.uiX = pclField->m_siOutPosX;
			clWarpInfo.uiY = pclField->m_siOutPosY;
		}
	}

	cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

	pclchar->SetWarpInfo(&clWarpInfo, 3000);
	if ( pclchar->Warp() )
	{
		// ��ȯ���� ���� ���� �Ѵ�.
		SI32 siSummonID = pclchar->GetSummonID();
		if(pclCM->IsAlive(siSummonID) == TRUE)
		{
			if(siSummonID > 0)
			{
				cltCharServer* pclcharSummon = (cltCharServer*)pclClient->pclCM->CR[siSummonID];

				pclcharSummon->SetWarpInfo(&clWarpInfo, 3000);
				pclcharSummon->Warp();
			}
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MOFUMOFUEVENT_WARP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResquest_MofuMofuEvent_Warp*	pclinfo = (cltGameMsgResquest_MofuMofuEvent_Warp*)pclMsg->cData;
	if(pclinfo == NULL)								return;

	cltGate	clGate;
	pclMapManager->pclGateManager->FindGate(MAPINDEX_MOFUMOFULAND, MAPINDEX_MAINFIELD, &clGate);

	if(clGate.siUnique <= 0)						return;
	if(pclCM->IsAlive(id) == FALSE)					return;
	
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// ������ �� �� �ִ°�?
	if( pclchar->CanWarpFrom() == false)			return;

	// ����üũ
	if(pclchar->pclCI->clIP.GetMoney() < 1000)		return;
    
	cltWarpInfo clWarpInfo(1, clGate.DstMapIndex, false, true, clGate.DstX, clGate.DstY, -1, -1);

	pclchar->SetWarpInfo(&clWarpInfo, 3100);
	if ( pclchar->Warp() )
	{
		// ���� �� ���� �����Ѵ�.
		SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
		if(personid)
		{
			sDBRequest_ChangeMoney clMsg(id, personid, CHANGE_MONEY_REASON_MOFUMOFUEVENT_WARP, -1000);
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

            pclDelMoneyStatistics->Add(DELMONEY_WARP, 1000);
		}
	}
}