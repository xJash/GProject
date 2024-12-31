//---------------------------------
// 2003/9/2 ���°�
//---------------------------------

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"

#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "../../Common/Map/Map.h"
#include "Char/CharManager/CharManager.h"

#include "../Server/Candidate/Candidate.h"

#include "../../../Server/AuthServer/AuthMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "MsgRval-Define.h"
#include "Msg/MsgType-Village.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Village.h"


#include "../../CommonLogic/Cityhall/Cityhall.h"
#include "../Common/StockDistributionMgr/StockDistributionMgr.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Stock.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"


// ���� �ǹ� ���� ��û. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETSTRUCTUREINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetStructureInfo* pclMsg = (sDBResponse_GetStructureInfo*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// ���� �ǹ� ������ ������Ʈ �Ѵ�.
	SI32 villageunique = pclMsg->siVillageUnique;
	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER )		return;

	SI32 i;
	for(i = 0;i < MAX_CONSTRUCTION_NUM;i++)
	{
		pclVillageManager->pclVillageInfo[villageunique]->clVillageVary.clStructureInfo.Set(pclMsg->siVillageStructureInfo[i], i);
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetStructureInfo"));
		pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("pclVillageManager->pclVillageInfo[villageunique]->clVillageVary.clStructureInfo.Set(pclMsg->siVillageStructureInfo[i], i);"));

	}
	
	//---------------------------
	// ������ ������ ������Ʈ �Ѵ�. 
	//---------------------------
	SI32 mapindex = pclMapManager->GetMapIndexFromVillageUnique(villageunique);
	if(mapindex >= 0)
	{
		pclMapManager->MakeLastMap(mapindex);
	}
	

}

// ���� ���� ����
void cltServer::DoMsg_DBMSG_RESPONSE_GETVILLAGEINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetVillageInfo* pclMsg = (sDBResponse_GetVillageInfo *)pPacket;
	
	//if( pclMsg->siVillageUnique == 0 ) return;
	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	cltVillageVary *pVillVary = &(pclVillageManager->pclVillageInfo[ pclMsg->siVillageUnique ]->clVillageVary);

	pVillVary->siMasterVillage = pclMsg->siMasterVillage;
	pVillVary->siParentVillage = pclMsg->siParentVillage;
	pVillVary->siVillageMark = pclMsg->siVillageMark;

	pVillVary->siTotalVillageScore = pclMsg->siTotalVillageScore;
	pVillVary->siNewYearEventScore = pclMsg->siNewYearEventScore;
	
	//[�߰� : Ȳ���� 2008. 2. 21 => ������ȸ �ߵ� �÷��� �ʱ�ȭ]
	pVillVary->m_bGeneralMeetingSuggest = pclMsg->m_bGeneralMeetingSuggest;

	cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

	pStrInfo->clCityhallStrInfo.siMasterVillage = pclMsg->siMasterVillage;
	pStrInfo->clCityhallStrInfo.siParentVillage = pclMsg->siParentVillage;
	pStrInfo->clCityhallStrInfo.siTotalVillageScore = pclMsg->siTotalVillageScore;
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetVillageInfo"));

}

// �������� 
void cltServer::DoMsg_DBMSG_RESPONSE_DECLAREWAR( sPacketHeader* pPacket )
{
	SI32 returnval = 0;

	sDBResponse_DeclareWar* pclMsg = (sDBResponse_DeclareWar *)pPacket;
	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siTargetVillage < 0 || pclMsg->siTargetVillage >= MAX_VILLAGE_NUMBER )		return;
	
	if( pclMsg->siResult == 1 ) {

		cltStrInfo *pStrInfo;

		pStrInfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

		if( pStrInfo ) {
			pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ pclMsg->siTargetVillage ] = 1;
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateYear = pclMsg->clDate.m_uiYear ;
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateMonth = pclMsg->clDate.m_uiMonth ;
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateDay = pclMsg->clDate.m_uiDay ;
			
			pclVillageManager->clDeclareWarDate[pclMsg->siVillageUnique].Set(&pclMsg->clDate);
		}

		pStrInfo = pclCityHallManager->GetStrInfo( pclMsg->siTargetVillage );
		
		if( pStrInfo ) pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ pclMsg->siVillageUnique ] = 2;
		
		pclVillageManager->siDeclareWarVillage[ pclMsg->siVillageUnique ] = pclMsg->siTargetVillage;

		returnval = SRVAL_CITYHALL_SUCCESS_DECLAREWAR;
		
		// ������ ��� Ŭ���̾�Ʈ���� �˸���
		cltGameMsgResponse_DeclareWar sendMsg;
		
		sendMsg.siVillageUnique = pclMsg->siVillageUnique;
		sendMsg.siTargetVillage = pclMsg->siTargetVillage;
		sendMsg.clDate.Set( &pclMsg->clDate);

		cltMsg clMsg( GAMEMSG_RESPONSE_DECLAREWAR, sizeof( cltGameMsgResponse_DeclareWar ), (BYTE*)&sendMsg );
		pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg );

		SI32 id	= pclMsg->usCharID;
		if(pclCM->IsValidID(id) == FALSE)
		{
			return ;
		}
		else
		{
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// TEMP LEEKH -------------------------------------------------------------------
				// [�α��߰� : Ȳ���� 2007. 10. 18] // ���� ���� ����.
				// param1		 == ���� ���ϴ� ����, 
				// pszCharParam1 == �ð�. 
				TCHAR str[50];
				ZeroMemory(str, sizeof(str));
				StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d"),	
														pclMsg->clDate.m_uiYear,
														pclMsg->clDate.m_uiMonth,
														pclMsg->clDate.m_uiDay);


				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_DECLARE_WAR, 
									 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									 pclMsg->siTargetVillage, 0, 0, 0, 0, str, NULL);
				// TEMP LEEKH -------------------------------------------------------------------
			}
		}
			
	} 
	else if(pclMsg->siResult == -1 ) 
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_MADEPROTECT_TARGET;

	}
	else if(pclMsg->siResult == -2 ) 
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_MADEPROTECT_SELF;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}


}

// �������� ��� 
void cltServer::DoMsg_DBMSG_RESPONSE_CANCELDECLAREWAR( sPacketHeader* pPacket )
{
	SI32 returnval = 0;

	sDBResponse_CancelDeclareWar *pclMsg = (sDBResponse_CancelDeclareWar *)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siTargetVillage < 0 || pclMsg->siTargetVillage >= MAX_VILLAGE_NUMBER )		return;

	if( pclMsg->siResult == 1 ) {
		
		cltStrInfo *pStrInfo;

		pStrInfo = pclCityHallManager->GetStrInfo( pclMsg->siVillageUnique );

		if( pStrInfo ) {
			pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ pclMsg->siTargetVillage ] = 0;
			//pStrInfo->clCityhallStrInfo.clDeclareWarDate.Set( &pclMsg->clDate );
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateYear = pclMsg->clDate.m_uiYear;
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateMonth = pclMsg->clDate.m_uiMonth;
			pStrInfo->clCityhallStrInfo.uiDeclareWarDateDay = pclMsg->clDate.m_uiDay;
		}

		pStrInfo = pclCityHallManager->GetStrInfo( pclMsg->siTargetVillage );
		
		if( pStrInfo ) pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ pclMsg->siVillageUnique ] = 0;

		pclVillageManager->siDeclareWarVillage[ pclMsg->siVillageUnique ] = 0;
		pclVillageManager->siNowWarVillage[ pclMsg->siVillageUnique ] = 0;

		returnval = SRVAL_CITYHALL_SUCCESS_CANCELDECLAREWAR;

		// ������ ��� Ŭ���̾�Ʈ���� �˸���
		cltGameMsgResponse_CancelDeclareWar sendMsg;
		
		sendMsg.siVillageUnique = pclMsg->siVillageUnique;
		sendMsg.siTargetVillage = pclMsg->siTargetVillage;

		cltMsg clMsg( GAMEMSG_RESPONSE_CANCELDECLAREWAR, sizeof( cltGameMsgResponse_CancelDeclareWar ), (BYTE*)&sendMsg );
		pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg );

		SI32 id	= pclMsg->usCharID;
		if(pclCM->IsValidID(id) == FALSE)
		{
			return ;
		}
		else
		{
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� ���� ���� ���.
				// param1 == ���� ��� ���ϴ� ����, 
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_DECLARE_WAR_CANCEL, 
												0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
												pclMsg->siTargetVillage, 0, 0, 0, 0, 
												NULL, NULL);
			}
		}

	} else {
		returnval = SRVAL_CITYHALL_FAIL_CANCELDECLAREWAR;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SETPARENTVILLAGE( sPacketHeader* pPacket )
{
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETSYMBOLSTATUS( sPacketHeader* pPacket )
{
	SI32 returnval = 0;
		
	sDBResponse_SetSymbolStatus *pclMsg = (sDBResponse_SetSymbolStatus *)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if( pclMsg->siResult == 1 ) 
	{
		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

		switch( pclMsg->siStatKind )
		{
		case SYMBOLSTAT_KIND:
			pStrInfo->clCityhallStrInfo.siSymbolKind = pclMsg->siStatValue;
			pclVillageManager->ChangeVillageGod( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;

		case SYMBOLSTAT_LIFE:
			pStrInfo->clCityhallStrInfo.siSymbolLife = pclMsg->siStatValue;
			pclVillageManager->SetLifeOfGodInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;

		case SYMBOLSTAT_MANA:
			pStrInfo->clCityhallStrInfo.siSymbolMana = pclMsg->siStatValue;
			pclVillageManager->SetManaOfGodInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;

		case SYMBOLSTAT_CAPA:
			pStrInfo->clCityhallStrInfo.siSymbolCapa = pclMsg->siStatValue;
			pclVillageManager->SetCapaOfGodInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;
		}
		
		SI32 siVillageGodCharUnique;
		if( pclVillageManager->IsThereVillageGod(pclMsg->siVillageUnique, &siVillageGodCharUnique ) == TRUE )
		{
			if( pclCM->IsValidID(siVillageGodCharUnique))
				pclCM->CR[ siVillageGodCharUnique ]->ParametaBoxAction();
		}

		// ��� �ڱ� ����
		pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );
		
		// ��� �ֱ� ������ ���� 
		pStrInfo->clCityhallStrInfo.clLastSymbolUpdate.Set( &pclMsg->clDate );

		// ��� ����� ������ �߰��Ѵ�			
		{
			cltMoney clMoney;
			clMoney.Set( -pclMsg->siCost );

			pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
				INOUTCODE_GODSTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
				INOUTCODE_GODSTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		
			// ���ӿ��� ���� ������ ���� 
			clMoney.Set( -clMoney.itMoney );
			clCurrencyInfo.clOutputMoney_clVillageWar.Increase( &clMoney );
		}		

		// ��������� �뺸
		
		cltGameMsgResponse_SetSymbolStatus sendMsg;

		sendMsg.siVillageUnique = pclMsg->siVillageUnique;
		sendMsg.siCost = pclMsg->siCost;
		sendMsg.siStatKind = pclMsg->siStatKind;
		sendMsg.siStatValue = pclMsg->siStatValue;

		SI32 id	= pclMsg->usCharID;
		if(pclCM->IsValidID(id) == FALSE)return;

		cltMsg clNormalMsg( GAMEMSG_RESPONSE_SETSYMBOLSTATUS, sizeof( cltGameMsgResponse_SetSymbolStatus ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
		
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 17] // ��Ȳ�� ����.
			// param1 == ���� ����, 
			// param2 == ���� ��ġ,
			// param3 == ���� ���.
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_SYMBOL_STATUS_SET, 
				0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				pclMsg->siStatKind, pclMsg->siStatValue, pclMsg->siCost, 0, 0, NULL, NULL);
		}

//		SI32 id	= pclMsg->usCharID;
//		if(pclCM->IsValidID(id) == FALSE)return;

//		UpdateStrInfoToClient( id, RANKTYPE_CITYHALL );

	} else if( pclMsg->siResult == 2) {
		// �����ڱ� ���� 
		returnval = SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_MONEY;
	}

	
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}	


void cltServer::DoMsg_DBMSG_RESPONSE_SETCASTLESTATUS( sPacketHeader* pPacket )
{
	SI32 returnval = 0;
		
	sDBResponse_SetCastleStatus *pclMsg = (sDBResponse_SetCastleStatus *)pPacket;

	if( pclMsg->siResult == 1 ) {

		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

		switch( pclMsg->siStatKind )
		{
		case SYMBOLSTAT_KIND:
			/*
			pStrInfo->clCityhallStrInfo.siCastleKind = pclMsg->siStatValue;
			pclVillageManager->ChangeVillageGod( pclMsg->siVillageUnique, pclMsg->siStatValue );
			*/
			break;

		case SYMBOLSTAT_LIFE:
			pStrInfo->clCityhallStrInfo.siCastleLife = pclMsg->siStatValue;
			pclVillageManager->SetLifeOfCastleInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;

		case SYMBOLSTAT_MANA:
			pStrInfo->clCityhallStrInfo.siCastleMana = pclMsg->siStatValue;
			pclVillageManager->SetManaOfCastleInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;

		case SYMBOLSTAT_CAPA:
			pStrInfo->clCityhallStrInfo.siCastleCapa = pclMsg->siStatValue;
			pclVillageManager->SetCapaOfCastleInVillage( pclMsg->siVillageUnique, pclMsg->siStatValue );
			break;
		}
		
		
		SI32 siVillageCastleCharUnique;
		if( pclVillageManager->IsThereCastle(pclMsg->siVillageUnique, &siVillageCastleCharUnique ) == TRUE ) {
			
			if(pclCM->IsValidID(siVillageCastleCharUnique))
				pclCM->CR[ siVillageCastleCharUnique ]->ParametaBoxAction();
		}
		
		

		// ��� �ڱ� ����
		pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clCityhallMoney );
		
		// ��� �ֱ� ������ ���� 
		pStrInfo->clCityhallStrInfo.clLastCastleUpdate.Set( &pclMsg->clDate );

		// ��� ����� ������ �߰��Ѵ�			
		{
			cltMoney clMoney;
			clMoney.Set( -pclMsg->siCost );

			pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
				INOUTCODE_CASTLESTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
				INOUTCODE_CASTLESTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
			
			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// TEMP LEEKH -------------------------------------------------------------------
			//	// [�α��߰� : Ȳ���� 2007. 10. 18] // ��û �����ڱ� ����� ����.				
			//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
			//	TCHAR pszCharParam1[50] = {'\0', };
			//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
			//																pclTime->clDate.uiYear,
			//																pclTime->clDate.uiMonth,
			//																pclTime->clDate.uiDay,
			//																pclTime->clDate.uiHour,
			//																pclTime->clDate.uiMinute);

			//	cltServer* pclserver = (cltServer*)pclClient;
			//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
			//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
			//									clMoney.itMoney, pclMsg->clCityhallMoney.itMoney, 0, 0, 0, 
			//									pszCharParam1, NULL);
			//	// TEMP LEEKH -------------------------------------------------------------------
			//}
			

			// ���ӿ��� ���� ������ ���� 
			clMoney.Set( -clMoney.itMoney );
			clCurrencyInfo.clOutputMoney_clVillageWar.Increase( &clMoney );
		}		



		

		// ��������� �뺸

		cltGameMsgResponse_SetCastleStatus sendMsg;

		sendMsg.siVillageUnique = pclMsg->siVillageUnique;
		sendMsg.siCost = pclMsg->siCost;
		sendMsg.siStatKind = pclMsg->siStatKind;
		sendMsg.siStatValue = pclMsg->siStatValue;

		SI32 id	= pclMsg->usCharID;
		if(pclCM->IsValidID(id) == FALSE)return;

		cltMsg clNormalMsg( GAMEMSG_RESPONSE_SETCASTLESTATUS, sizeof( cltGameMsgResponse_SetCastleStatus ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);


		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� ���׷��̵�� ��û �ǹ��� ����Ǿ� ����Ǵ� ���� ����.
			// param1 == ���� ���, 
			// param2 == ���� ����, 
			// param3 == ���� ��ġ. 
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_CASTLE_STATUS_SET, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siCost, pclMsg->siStatKind, pclMsg->siStatValue, 0, 0, NULL, NULL);
		}

//		SI32 id	= pclMsg->usCharID;
//		if(pclCM->IsValidID(id) == FALSE)return;

//		UpdateStrInfoToClient( id, RANKTYPE_CITYHALL );

	} else if( pclMsg->siResult == 2) {
		// �����ڱ� ���� 
		returnval = SRVAL_CITYHALL_FAIL_CASTLESTATUS_MONEY;
	}

	
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}	

void cltServer::DoMsg_DBMSG_RESPONSE_SETVILLAGEWARLOSS( sPacketHeader* pPacket )
{
	int i;

	sDBResponse_SetVillageWarLoss *pclMsg = (sDBResponse_SetVillageWarLoss *)pPacket;

	if( pclMsg->siResult == 1 ) {

		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

		// ���� �� �ֽ� ���� ����
		pStrInfo->clCityhallStrInfo.siTotalStockAmount = pclMsg->siTotalVillageStockAmount;

		// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
		if( pclMsg->usCount > 30 )		pclMsg->usCount = 30;
		for( i = 0; i < pclMsg->usCount; ++i ) {

			// ������ ������

			// pclMsg->siStockHolderPersonID[ i ]				// PersonID
			// pclMsg->siStockAmount[ i ]						// �Ұ� �� ���� �ֽ� ����
			// pclMsg->siLossPersent							// �Ұ� ����
			// pclMsg->siWinVillage								// �¸� ���� 
			
			cltLetterMsg_StockLoss clletter( pclMsg->siVillageUnique, pclMsg->siWinVillage, 
				pclMsg->siLossPersent, pclMsg->siStockAmount[ i ] );
			SendLetterMsg( pclMsg->siStockHolderPersonID[ i ], (cltLetterHeader*)&clletter );
		
			//�ֽ��� �Ұ��ɶ� ������ ���￡ �� ������.�Ұ��ȴ�.
			//�ֽ� �Ұ��� �α� ���� [2007.09.03 �ռ���]
			SI32 tatallossstockamount = pclMsg->siTotalLossStockAmount;			//�Ұ��ֽ� �ѷ�
			SI32 villageuniaue		  = pclMsg->siVillageUnique;				//�Ұ��Ǵ� ���� ����ũ
			// param1 == �Ұ��ֽ� �ѷ�, param2 == �Ұ��� ���� �ֽ� �ѷ�, param3 == �ֽ� �Ұ� ����, param4 == �Ұ� �ֽ� ���� ����
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCKLOSS, 0, NULL,
								 NULL, villageuniaue, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
								 tatallossstockamount, pclMsg->siTotalVillageStockAmount, pclMsg->siLossPersent, pclMsg->usCount, 0, 
								 NULL, NULL);
		}

		if( pclMsg->usCount > 0 && pclMsg->siTotalLossStockAmount > 0 ) {
			// ���� ����
			cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siWinVillage, RANKTYPE_CITYHALL );

			if ( pStrInfo == NULL )
			{
				return;
			}

			if ( pStrInfo->clCityhallStrInfo.siResidentNum < 1 )
			{
				return;
			}

			SI32 unitStock = (SI32)( pclMsg->siTotalLossStockAmount / pStrInfo->clCityhallStrInfo.siResidentNum );
			if( unitStock == 0)
				unitStock = 1;
			
			sDBRequest_MaxStockDistributionNum clMsg( pclMsg->siVillageUnique, pclMsg->siTotalLossStockAmount, unitStock, 5000, true, 0, pclMsg->siWinVillage );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}

	}
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETVILLAGELEVEL( sPacketHeader *pPacket )
{
	sDBResponse_SetVillageLevel *pclMsg = (sDBResponse_SetVillageLevel *)pPacket;

	if( pclMsg->siResult == 1 ) {

		cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_CITYHALL );

		if( pclStrInfo ) {
	
			pclStrInfo->clCityhallStrInfo.siVillageLevel = pclMsg->siLevel;
		}

	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ����.
		// param1 ==  ����, param2 == siSlaveVillageNum, param3 == siResidentLevel, param4 == siVisitLevel.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_LEVEL_SET, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->siLevel, pclMsg->siSlaveVillageNum, pclMsg->siResidentLevel, pclMsg->siVisitLevel, 0, NULL, NULL);
	}
}


void cltServer::DoMsg_DBMSG_RESPONSE_SETVILLAGEMARK( sPacketHeader* pPacket )
{
	sDBResponse_SetVillageMark* pclMsg = (sDBResponse_SetVillageMark *)pPacket;

	// �迭�ε��� ���� �߰� - by LEEKH 2008.02.13
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if( pclMsg->siResult == 1 ) {


		if( pclMsg->siVillageUnique == 0 ) return;

		cltVillageInfo *pclVillageInfo = pclVillageManager->pclVillageInfo[ pclMsg->siVillageUnique ];

		if( pclVillageInfo == NULL ) return;

		pclVillageInfo->clVillageVary.siVillageMark = pclMsg->siVillageMark;


		cltGameMsgResponse_SetVillageMark sendMsg( pclMsg->siVillageUnique, pclMsg->siVillageMark );


		cltMsg clMsg( GAMEMSG_RESPONSE_SETVILLAGEMARK, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg );

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��ũ ����.
			// param1 == ��ũ, 
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_MARK_SET, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siVillageMark, 0, 0, 0, 0, NULL, NULL);
		}


		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_SUCCESS_VILLAGEMARK,  0, 0, pclCM->CR[id]->GetCharUnique());

		// �����ڱ� ���� 
		{
			sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_VILLAGEMARK, 0, pclMsg->siVillageUnique, RANKTYPE_CITYHALL, -1000000 );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
		}


	} else if( pclMsg->siResult == 2 ) {
	
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_VILLAGEMARK_ALREADYUSED,  0, 0, pclCM->CR[id]->GetCharUnique());

	} else if( pclMsg->siResult == 3 ) {

		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_VILLAGEMARK_DATE,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETVILLAGEMAP( sPacketHeader* pPacket )
{
	sDBResponse_SetVillageMap* pclMsg = (sDBResponse_SetVillageMap *)pPacket;

	SI32 id	= pclMsg->usCharID;

	if( pclCM->IsValidID(id) == FALSE )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	if( pclMsg->siResult == 1 ) {

		//_LEON_HUNTMAP
        switch(pclMsg->siMapType)
		{
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_CITYHALL:
			{
				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_SUCCESS_VILLAGEMAP,  0, 0, pclCM->CR[id]->GetCharUnique());

				// �����ڱ� ���� 
				sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_VILLAGEMAP, 0, pclMsg->siVillageUnique, RANKTYPE_CITYHALL, -pclMsg->siNeedMoney );
				pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
			}
			break;
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_HUNT:
			{
				SendServerResponseMsg( RANKTYPE_HUNT, SRVAL_HUNT_SUCCESS_HUNTMAP,  0, 0, pclCM->CR[id]->GetCharUnique());

				// �����ڱ� ���� => ������ ���� ���� �ڱ��� ���� ��û �ڱݿ��� ��ݵȴ�.
				// pclMsg->siVillageUnique�� ���ε��� ��ȣ�̹Ƿ� �������, ��õ(5��)�� 205���̹Ƿ�
				// ĳ���Ͱ� ���� �ִ� ���� ����ũ�� ����
				sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_VILLAGEMAP, 0, villageunique, RANKTYPE_CITYHALL, -pclMsg->siNeedMoney );
				//sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_VILLAGEMAP, 0, pclMsg->siVillageUnique, RANKTYPE_HUNT, -pclMsg->siNeedMoney );
				pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
			}
		default:
			return;
		}
			
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 17] // ���� ���� ����.
			// param1 == ���� ���� ��ȣ, 
			// param2 == ��, 
			// param3 == ���� Ÿ��.
			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_MAP_CHANGE, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siVillageMapIndex, -pclMsg->siNeedMoney, pclMsg->siMapType, 0, 0, NULL, NULL);
		}

	} else {
		switch(pclMsg->siMapType)
		{
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_CITYHALL:
			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_SUCCESS_VILLAGEMAP,  0, 0, pclCM->CR[id]->GetCharUnique());
			break;
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_HUNT:
			SendServerResponseMsg( RANKTYPE_HUNT, SRVAL_HUNT_SUCCESS_HUNTMAP,  0, 0, pclCM->CR[id]->GetCharUnique());
			break;
		default:
			return;
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETINSTANCEPROFIT_VILLAGE(sPacketHeader* pPacket )
{
	sDBResponse_SetInstanceProfit_Village* pclMsg = (sDBResponse_SetInstanceProfit_Village*)pPacket ;

	if ( pclMsg->siResult == 1 )
	{
		pclVillageManager->siInstanceProfitVillageunique = pclMsg->siVillageUnique ;
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_CHANGE_INSTANCEPROFIT(sPacketHeader* pPacket )
{
	sDBResponse_Change_InstanceProfit* pclMsg = (sDBResponse_Change_InstanceProfit*)pPacket ;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclMsg->bVillage )
		{
			SI32 villageunique = pclVillageManager->siInstanceProfitVillageunique ;
			GMONEY money = pclMsg->siLeftMoney ;

			if ( villageunique && pclVillageManager->IsValidVillage(villageunique) && money )
			{
				{
					sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_INSTANCEPROFIT, 0, villageunique,  money);
					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}

				{
					sDBRequest_Change_InstanceProfit sendMsg(-money,false);
					pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
				}
			}

			pclVillageManager->siInstanceProfitVillageunique = 0 ;
		}
		else
		{
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_VILLAGERESIDENTSVISITORSINFO( sPacketHeader *pPacket )
{
	sDBResponse_VillageResidentsVisitorsInfo *pclMsg = (sDBResponse_VillageResidentsVisitorsInfo *)pPacket;

	if( pclMsg->siResult != 1 )
		return;

	for( SI16 i = 1;i < MAX_VILLAGE_NUMBER;i++)
	{
		if(pclVillageManager->pclVillageInfo[i])
		{
			// ��� ������ �θ���, �������� ���� ���� �� ������ũ������ ��û�Ѵ� 
			{
				sDBRequest_GetVillageInfo clMsg2( i );
				pclGameDBProcess->SendMsg( i % DBCONNECTION_NUMBER, (sPacketHeader *)&clMsg2);

			}
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETVILLAGEWAR_RESULT(sPacketHeader *pPacket)
{
	sDBResponse_SetVillageWarResult * pclMsg = (sDBResponse_SetVillageWarResult *)pPacket;

	if( pclMsg->siResult != 1)
	{

		return;
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// TEMP LEEKH -------------------------------------------------------------------
		// [�α��߰� : Ȳ���� 2007. 10. 18] // ���� ������ ���� ���.
		// param1	 == �¸��� ����, 
		// param2	 == ���� ����, 
		// param3	 == �̱� ���� �ڱ�, 
		// param4	 == ���� ���� �ڱ�, 
		// param5	 == +,- �ݾ�, 
		// pszParam1 == �ð�.
		TCHAR str[50] = {'\0', };
		StringCchPrintf(str, sizeof(str), TEXT("%d-%d-%d, %d : %d"),	
												pclTime->clDate.uiYear,
												pclTime->clDate.uiMonth,
												pclTime->clDate.uiDay,
												pclTime->clDate.uiHour,
												pclTime->clDate.uiMinute	);

		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_RESULT, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->m_siwinVillageUnique, pclMsg->m_siloseVillageUnique, pclMsg->m_siwinnerVillageMoney, 
										pclMsg->m_siloserVillageMoney, pclMsg->m_siwinnerGetVillageMoney, 
										str, NULL);
	}

	// ��, ������ ��û �ڱ� ����

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->m_siwinVillageUnique, RANKTYPE_CITYHALL );

	if( pclStrInfo != NULL )
	{
		pclStrInfo->clCommonInfo.clMoney.itMoney  = pclMsg->m_siwinnerVillageMoney;


		cltMoney clMoney;
		clMoney.Set( pclMsg->m_siwinnerGetVillageMoney );
		
		cltMoney clCityHallMoney;
		clCityHallMoney.Set( pclMsg->m_siwinnerVillageMoney );

		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_VILLAGEWARMONEY, &pclTime->clDate, &clMoney, &clCityHallMoney);

		sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->m_siwinVillageUnique , RANKTYPE_CITYHALL, 
			INOUTCODE_VILLAGEWARMONEY, &pclTime->clDate, &clMoney, &clCityHallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// TEMP LEEKH -------------------------------------------------------------------
		//	// [�α��߰� : Ȳ���� 2007. 10. 18] // ��û �����ڱ� ����� ����.				
		//	// param1 == ����� �ݾ�, param2 == ��ܺ����ڱ�, pszParam1 == �ð�.
		//	TCHAR pszCharParam1[50] = {'\0', };
		//	StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
		//																pclTime->clDate.uiYear,
		//																pclTime->clDate.uiMonth,
		//																pclTime->clDate.uiDay,
		//																pclTime->clDate.uiHour,
		//																pclTime->clDate.uiMinute);

		//	
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CITYHALL, LOGCOMMAND_INDEX_CITYHALL_INOUTMONEY, 
		//									0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->m_siwinVillageUnique, 0, 0, 
		//									clMoney.itMoney, clCityHallMoney.itMoney, 0, 0, 0, 
		//									pszCharParam1, NULL);
		//}

		pclStrInfo->clCityhallStrInfo.siVillaeWarRecordWin++;

	}
		
	pclStrInfo = GetStrInfo( pclMsg->m_siloseVillageUnique, RANKTYPE_CITYHALL );
	
	if( pclStrInfo != NULL )
	{
		pclStrInfo->clCommonInfo.clMoney.itMoney  = pclMsg->m_siloserVillageMoney;

		cltMoney clMoney;
		clMoney.Set( -(pclMsg->m_siwinnerGetVillageMoney) );

		cltMoney clCityHallMoney;
		clCityHallMoney.Set( pclMsg->m_siloserVillageMoney );

		pclStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_VILLAGEWARMONEY, &pclTime->clDate, &clMoney, &clCityHallMoney);

		sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->m_siloseVillageUnique , RANKTYPE_CITYHALL, 
			INOUTCODE_VILLAGEWARMONEY, &pclTime->clDate, &clMoney, &clCityHallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

		pclStrInfo->clCityhallStrInfo.siVillaeWarRecordLose++;

		// �й� ������ �й� ��¥ ����
        pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateYear = pclMsg->m_clDateLoser.m_uiYear;
		pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateMonth = pclMsg->m_clDateLoser.m_uiMonth;
		pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateDay = pclMsg->m_clDateLoser.m_uiDay;
		//((cltCityhallStrInfo*)(pclStrInfo))->clLastWarLoseDate.Set( &pclMsg->m_clDateLoser );
		
	}
	//// ���� ������ ����� ������ ����Ʈ ���� ����.
	//// 2009-03-11 [ ���� ]
	//SI32 siWinner = pclMsg->m_siloseVillageUnique	;	// �¸� ����
	//SI32 siLosser = pclMsg->m_siwinVillageUnique	;	// �й� ���� 
	//
	//pclVillageManager->siDeclareWarVillage[siWinner]	=	0	;
	//pclVillageManager->siDeclareWarVillage[siLosser]	=	0	;
	/*
	// ��� ����� ������ �߰��Ѵ�			
	{
		cltMoney clMoney;
		clMoney.Set( -pclMsg->siCost );

		pStrInfo->clCityhallStrInfo.clInOutMoneyInfo.AddInOutMoneyInfo( RANKTYPE_CITYHALL,
			INOUTCODE_GODSTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		sDBRequest_CityHallSetInOutMoney sendMsg( pclMsg->siVillageUnique, RANKTYPE_CITYHALL, 
			INOUTCODE_GODSTAT, &pclTime->clDate, &clMoney, &pclMsg->clCityhallMoney );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );


		// ���ӿ��� ���� ������ ���� 
		clMoney.Set( -clMoney.itMoney );
		clCurrencyInfo.clOutputMoney_clVillageWar.Increase( &clMoney );
	}
*/
	

}

void cltServer::DoMsg_DBMSG_RESPONSE_ADD_VILLAGE_SCORE(sPacketHeader* pPacket)
{
	sDBResponse_Add_Village_Score* pclMsg = (sDBResponse_Add_Village_Score*)pPacket;	

	pclVillageManager->pclVillageInfo[pclMsg->m_siVillageUnique]->clVillageVary.siVillageScore		  = pclMsg->m_siVillageScore;
	pclVillageManager->pclVillageInfo[pclMsg->m_siVillageUnique]->clVillageVary.siTotalVillageScore  += pclMsg->m_siAddVillageScore;
}

void cltServer::DoMsg_DBMSG_RESPONSE_VILLAGEJOINPLAYTIME(sPacketHeader* pPacket)
{
	// PCK : �α׸� ����� ���� ��Ŷ�߰�
	sDBReponse_VillageJoinPlayTime* pclMsg = (sDBReponse_VillageJoinPlayTime*)pPacket;

	// PCK : PersonID�� �ٰŷ� CharID�� ã��.(PersonID��������!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// LEEKH MODIFY 2007.10.24
	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ ���� ���� �� �÷��� �ð�.
	// param1 == �÷��� �ð�.
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_PLAY_TIME, 
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									pclMsg->siVillageJoinPlayTime, 0, 0, 0, 0, NULL, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_VILLAGEJOINLEVELUP(sPacketHeader* pPacket)
{
	// PCK : �α׸� ����� ���� ��Ŷ �߰�
	sDBResponse_VillageJoinLevelUp*	pclMsg = (sDBResponse_VillageJoinLevelUp*)pPacket;

	// PCK : PersonID�� �ٰŷ� CharID�� ã��.(PersonID��������!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// [�α��߰� : Ȳ���� 2007. 10. 9] // ������ �ִ°�� ������ ����.
	// Param1 == ������ Ƚ��
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_LEVEL_UP, 
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									pclMsg->siLevelCount, 0, 0, 0, 0, NULL, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_VILLAGEJOINMAKEITEM(sPacketHeader* pPacket)
{
	// PCK : �α׸� ����� ���� ��Ŷ �߰�
	sDBResponse_VillageJoinMakeItem* pclMsg = (sDBResponse_VillageJoinMakeItem*)pPacket;

	// PCK : PersonID�� �ٰŷ� CharID�� ã��.(PersonID��������!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ �ִ°�� ������ ���� ��ų ����.
	// param1 == ��ų ����ġ.
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_MAKE_ITEM_SKILL_EXP, 
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									pclMsg->siItemSkillExp, 0, 0, 0, 0, NULL, NULL);
}