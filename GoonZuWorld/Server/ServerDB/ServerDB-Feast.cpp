// server&db-feast
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\Server\Statistics\Statistics.h"
#include "..\Common\Letter\Letter.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Feast.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-item.h"

#include "Msg\MsgType-Feast.h"
#include "MsgRval-Define.h"


#include "PersonInfo.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"

// ���ڽÿ� ��û�ڰ� ������ �Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_RESERVE(sPacketHeader* pPacket)
{
	sDBResponse_FeastReserve* pclMsg = (sDBResponse_FeastReserve*)pPacket;

	SI32 id = pclMsg->usCharID;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_FEAST );

	SI32 returnval = SRVAL_FEAST_FAIL_RESERVE;

	switch( pclMsg->siResult ) {
	case 1:
		{
			returnval = SRVAL_FEAST_SUCCESS_RESERVE;

			pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus = 2;

			cltFeastResvInfo clinfo;
			clinfo.siPersonID = pclMsg->siPersonID;
			memcpy( clinfo.szPersonName, pclMsg->szPersonName, MAX_PLAYER_NAME );
			clinfo.szPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
			clinfo.siYear = pclMsg->siYear;
			clinfo.siMonth = pclMsg->siMonth;
			clinfo.siDay = pclMsg->siDay;
			clinfo.siHour = pclMsg->siHour;
			clinfo.siMinute = pclMsg->siMinute;
			memcpy( clinfo.szReason, pclMsg->szReason, 128 );
			clinfo.szReason[ 127 ] = NULL;

			for( int i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {
				pclStrInfo->clFeastStrInfo.clFeastInfo.siItemGive[ i ] = 0;
			}

			pclStrInfo->clFeastStrInfo.clFeastResvInfo.Set( &clinfo );

			// ���ڽ� �ڱ� ���� 
			pclStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clFeastMoney );

			// ��û�� �����ڱ� ���� 
			if( pclCM->IsValidID(id) ) {

				pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonMoney );
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

				UpdateStrInfoToClient( id, RANKTYPE_FEAST );
			}

			pclStatisticsManager->clDailyStatistics.siFeastUseNumber++;
			pclStatisticsManager->clDailyStatistics.siFeastUseMoney += pclStrInfo->clFeastStrInfo.clFeastInfo.siCost;

			// LEEKH MODIFY 2007.10.25
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
			{
				cltCharServer* pclchar = NULL;
				if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

				// [�α��߰� : Ȳ���� 2007. 10. 18] // ��ȸ ����
				// param2 == ��ȸ�� �����ڱ�
				TCHAR szCharParam1[50] = { '\0', };
				TCHAR szCharParam2[50] = { '\0', };
				StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("%03d-%02d-%02d"), pclMsg->siYear, pclMsg->siMonth, pclMsg->siDay);
				StringCchPrintf(szCharParam2, sizeof(szCharParam2), TEXT("%02d:%02d"), pclMsg->siHour, pclMsg->siMinute);

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_RESERVE, 
					0, pclchar, NULL, 0, pclMsg->siCost, pclMsg->siPersonMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					0, pclMsg->clFeastMoney.itMoney, 0, 0, 0, szCharParam1, szCharParam2);
			}
		}
		break;

	case 2:
		{
			// �̹� ����Ǿ� ����
			returnval = SRVAL_FEAST_FAIL_RESERVE_ALREADY;
		}
		break;

	case 3:
		{
			// ������ ����
			returnval = SRVAL_FEAST_FAIL_RESERVE_NOTENOUGHMONEY;
		}
		break;
	}

	// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
	if( pclCM->IsValidID(id) ) {

		SendServerResponseMsg( RANKTYPE_FEAST, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}
}


// ���ڽ� ����� ���� ����� �߰��Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_ADDPRESENTLIST(sPacketHeader* pPacket)
{
	sDBResponse_FeastAddPresentList* pclMsg = (sDBResponse_FeastAddPresentList*)pPacket;

	SI32 id = pclMsg->usCharID;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_FEAST );
	
	if( pclMsg->siResult == 1 ) 
	{
		pclStrInfo->clFeastStrInfo.clFeastInfo.SetPresentItem(pclMsg->siListIndex, pclMsg->siItemUnique, pclMsg->siItemNum);

		if( pclCM->IsValidID(id) ) {	UpdateStrInfoToClient( id, RANKTYPE_FEAST );	}

		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ ���� �߰�
			// param1 == ���� ��� �ε��� , 
			// Param2 == ������ ����ũ.
			// param3 == ������ ����.
			cltServer* pclserver = (cltServer*)pclClient;
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))			pclchar = (cltCharServer*)pclCM->CR[id];
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_ADDPRESENTLIST, 
				0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,
				pclMsg->siListIndex, pclMsg->siItemUnique, pclMsg->siItemNum, 0, 0, NULL, NULL);
		}
	}
}

// ���ڽ� ����� ���� ��Ͽ��� �����Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_DELPRESENTLIST(sPacketHeader* pPacket)
{
	sDBResponse_FeastDelPresentList* pclMsg = (sDBResponse_FeastDelPresentList*)pPacket;

	SI32 id = pclMsg->usCharID;

	cltStrInfo *pclStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_FEAST );
	
	if( pclMsg->siResult == 1 ) 
	{
		pclStrInfo->clFeastStrInfo.clFeastInfo.SetPresentItem( pclMsg->siListIndex, 0, 0 );

		if( pclCM->IsValidID(id) ) {	UpdateStrInfoToClient( id, RANKTYPE_FEAST );	}

		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ ���� ��Ͽ��� ����.			
			// param1 == ���� ��� �ε���. 
			cltServer* pclserver = (cltServer*)pclClient;
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))			pclchar = (cltCharServer*)pclCM->CR[id];
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_DELPRESENTLIST, 
				0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				pclMsg->siListIndex, 0, 0, 0, 0, NULL, NULL);
		}
	}
}

// ���ڽ� ����� â�� �������� �ִ´� 
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_STGITEMIN(sPacketHeader* pPacket)
{
	sDBResponse_FeastStgItemIn* pclMsg = (sDBResponse_FeastStgItemIn*)pPacket;

	SI32 id = pclMsg->usCharID;

	if( pclCM->IsValidID(id) == false )						return;
	if( pclMsg->siPersonID < 1 || pclMsg->usCharID < 1 )	return;

	if ( pclMsg->siResult == -4 )
	{
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_TOOMANY, 0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	} 

	if ( pclMsg->siResult != 1 ) return;
	

	if ( pclMsg->siVillageUnique < 1 ) return;

	cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL ) return;

	if( pclMsg->siItemInventoryIndex < PERSONITEM_INV0 || 
		pclMsg->siItemInventoryIndex >= MAX_ITEM_PER_PERSON ) return;

	if( pclMsg->siStgItemIndex < 0 ||
		pclMsg->siStgItemIndex >= MAX_FEAST_STG_NUMBER ) return;

	if( pclMsg->siStgItemNum < 1 || 
		pclMsg->siStgItemNum > MAX_ITEM_PILE_NUMBER ) return;

	pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemUnique = pclMsg->siStgItemUnique;
	pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemNum = pclMsg->siStgItemNum;

	if( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if ( pclMsg->siItemNum < 0 || pclMsg->siItemNum > MAX_ITEM_PILE_NUMBER )
		{
			return;
		}

		if ( pclMsg->siItemNum == 0 )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].Init();
		}
		else
		{
	
			if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siUnique != pclMsg->siItemUnique )
			{
				return;
			}
			

			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siUnique = pclMsg->siItemUnique;
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siItemNum = pclMsg->siItemNum;
		}

		pclCM->CR[id]->SetUpdateSwitch( UPDATE_INVENTORY, true , 0);

		UpdateStrInfoToClient( id, RANKTYPE_FEAST );
/*
		cltGameMsgResponse_FeastStgItemIn clinfo(
			pclMsg->siItemInventoryIndex,
			pclMsg->siItemUnique,
			pclMsg->siItemNum,
			pclMsg->siStgItemIndex,
			pclMsg->siStgItemUnique,
			pclMsg->siStgItemNum
			);
		cltMsg clMsg(GAMEMSG_RESPONSE_FEAST_STGITEMIN, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
*/
		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [�α��߰� : Ȳ���� 2007. 10. 18] // ���ڽ� ����� â�� �������� �ִ´� 		
			// param1 == inventory item index, param2 == inventory item unique, param3 == inventory item num
			// pszParam1 == stg ����. 
			TCHAR szCharParam1[50];
			ZeroMemory(szCharParam1, sizeof(szCharParam1));

			StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("STG index : %d, itemunique : %d, itemnum : %d"),	
																		pclMsg->siStgItemIndex, 
																		pclMsg->siStgItemUnique, 
																		pclMsg->siStgItemNum);
			

			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_STGITEMIN, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siItemInventoryIndex, pclMsg->siItemUnique, pclMsg->siItemNum, 0, 0, szCharParam1, NULL);
		}
	}	
	

}

// ���ڽ� ����� â���� �������� ������
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_STGITEMOUT(sPacketHeader* pPacket)
{
	sDBResponse_FeastStgItemOut* pclMsg = (sDBResponse_FeastStgItemOut*)pPacket;

	if ( pclMsg->siResult != 1 ) return;
	
	SI32 id = pclMsg->usCharID;

	if( pclCM->IsValidID(id) == false )						return;
	if ( pclMsg->siPersonID < 1 || pclMsg->usCharID < 1 )	return;

	if ( pclMsg->siVillageUnique < 1 ) return;

	cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL ) return;

	if( pclMsg->siItemInventoryIndex < PERSONITEM_INV0 || 
		pclMsg->siItemInventoryIndex >= MAX_ITEM_PER_PERSON ) return;

	if( pclMsg->siStgItemIndex < 0 ||
		pclMsg->siStgItemIndex >= MAX_FEAST_STG_NUMBER ) return;

	if( pclMsg->siItemNum < 1 || 
		pclMsg->siItemNum > MAX_ITEM_PILE_NUMBER ) return;

	if( pclMsg->siStgItemNum == 0 ) {
		
		pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemUnique = 0;
		pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemNum = 0;

	} else {

		pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemUnique = pclMsg->siStgItemUnique;
		pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgItemIndex ].siItemNum = pclMsg->siStgItemNum;
	}

	if( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].Init();
				
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siUnique = pclMsg->siItemUnique;
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemInventoryIndex ].siItemNum = pclMsg->siItemNum;

		pclCM->CR[id]->SetUpdateSwitch( UPDATE_INVENTORY, true , 0);

		UpdateStrInfoToClient( id, RANKTYPE_FEAST );
/*
		cltGameMsgResponse_FeastStgItemIn clinfo(
			pclMsg->siItemInventoryIndex,
			pclMsg->siItemUnique,
			pclMsg->siItemNum,
			pclMsg->siStgItemIndex,
			pclMsg->siStgItemUnique,
			pclMsg->siStgItemNum
			);

		cltMsg clMsg(GAMEMSG_RESPONSE_FEAST_STGITEMIN, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
*/

		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 9. 27] // ���ڽ� ����� â���� �������� ������.		
			// param1 == inventory item index, param2 == inventory item unique, param3 == inventory item num
			// pszParam1 == stg ����. 
			TCHAR szCharParam1[50];
			ZeroMemory(szCharParam1, sizeof(szCharParam1));

			StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("STG index : %d, itemunique : %d, itemnum : %d"),	
																		pclMsg->siStgItemIndex, 
																		pclMsg->siStgItemUnique, 
																		pclMsg->siStgItemNum);

			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_STGITEMOUT, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siItemInventoryIndex, 
											pclMsg->siItemUnique, 
											pclMsg->siItemNum,
											0, 0, szCharParam1, NULL);
		}
	}

}

// ��ȸ�� ���۵ȴ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_OPEN(sPacketHeader* pPacket)
{
	sDBResponse_FeastOpen* pclMsg = (sDBResponse_FeastOpen*)pPacket;

	if( pclMsg->siResult != 1 ) {
		return;
	}

	cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL ) return;

	for( int i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {
		pclStrInfo->clFeastStrInfo.clFeastInfo.siItemGive[ i ] = 0;
	}

	pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus = 1;

	TCHAR *pTitle = GetTxtFromMgr(6134);
	TCHAR *pText = GetTxtFromMgr(6135);

	cltGameMsgResponse_Notice clNotice( pTitle, pText ,true);
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
	
	pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg, pclMsg->siVillageUnique);


	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ�� �����Ѵ�.
		// 
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_OPEN, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,
										0, 0, 0, 0, 0, NULL, NULL);
	}
}

// ��ȸ�� �����Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_CLOSE(sPacketHeader* pPacket)
{
	sDBResponse_FeastClose* pclMsg = (sDBResponse_FeastClose*)pPacket;

	if( pclMsg->siResult != 1 ) {
		return;
	}

	cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

	if ( pclStrInfo == NULL ) return;

	for( int i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {
		pclStrInfo->clFeastStrInfo.clFeastInfo.siItemGive[ i ] = 0;
	}

	pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus = 0;

	TCHAR *pTitle = GetTxtFromMgr(6134);
	TCHAR *pText = GetTxtFromMgr(6136);

	cltGameMsgResponse_Notice clNotice( pTitle, pText,true );
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
	
	pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg, pclMsg->siVillageUnique);


	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ�� ������.
		// 
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_CLOSE, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,
										0, 0, 0, 0, 0, NULL, NULL);
	}
}


// ���ڽ� ����� ��ȸ����� �����Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_SETCOST(sPacketHeader* pPacket)
{
	sDBResponse_FeastSetCost* pclMsg = (sDBResponse_FeastSetCost*)pPacket;

	SI32 returnval = SRVAL_FEAST_FAIL_SETCOST;

	SI32 id = pclMsg->usCharID;

	if( pclMsg->siResult == 1 ) {

		returnval = SRVAL_FEAST_SUCCESS_SETCOST;

		cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

		if ( pclStrInfo == NULL ) return;

		pclStrInfo->clFeastStrInfo.clFeastInfo.siCost = pclMsg->siCost;
		

		if( pclCM->IsValidID( id ) ) 
		{
			UpdateStrInfoToClient( id, RANKTYPE_FEAST );
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ �ݾ� ����.
			// param1 == ��ȸ�ݾ�.
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID( id ))		pclchar = (cltCharServer*)pclCM->CR[id];
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_SETCOST, 
								0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								pclMsg->siCost, 0, 0, 0, 0, NULL, NULL);
		}
	}
	
	if( pclCM->IsValidID( id ) ) 
	{	
		SendServerResponseMsg( RANKTYPE_FEAST, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}

}

// ��ȸ ��û�ڰ� ��ȸ ��ǰ�� �������� 
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_GIVEITEM(sPacketHeader* pPacket)
{
	sDBResponse_FeastGiveItem* pclMsg = (sDBResponse_FeastGiveItem*)pPacket;

	SI32 returnval = SRVAL_FEAST_FAIL_GIVEITEM;

	SI32 id = pclMsg->usCharID;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER)		return;

	if( pclMsg->siPresentIndex < 0 || pclMsg->siPresentIndex >= MAX_FEAST_PRESENT_NUMBER)	return;
	if( pclMsg->siStgIndex < 0 || pclMsg->siStgIndex >= MAX_FEAST_STG_NUMBER)				return;

	if( pclMsg->siPresentIndex < 0 || pclMsg->siPresentIndex >= MAX_FEAST_PRESENT_NUMBER)	return;
	

	switch( pclMsg->siResult )
	{
	case 0:
		break;
	case 1:
		{
			returnval = SRVAL_FEAST_SUCCESS_GIVEITEM;

			cltStrInfo *pclStrInfo = pclFeastManager->GetStrInfo( pclMsg->siVillageUnique );

			pclStrInfo->clFeastStrInfo.clFeastInfo.siItemGive[ pclMsg->siPresentIndex ] = 1;

			if( pclMsg->siStgItemNum == 0 ) {
				
				pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgIndex ].siItemUnique = 0;
				pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgIndex ].siItemNum = 0;

			} else {

				pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgIndex ].siItemUnique = pclMsg->siStgItemUnique;
				pclStrInfo->clFeastStrInfo.clFeastStg[ pclMsg->siStgIndex ].siItemNum = pclMsg->siStgItemNum;
			}

			if( pclCM->IsValidID( id ) ) {
				UpdateStrInfoToClient( id, RANKTYPE_FEAST );
			}


			cltItem clItem;

			clItem.Init();
			
			clItem.siUnique = pclMsg->siItemUnique;
			clItem.siItemNum = pclMsg->siItemNum;

			pclCM->GiveItemForVillageMember( clItem, pclMsg->siVillageUnique, INPUTITEMPERSON_OPTION_FEAST );

			// LEEKH MODIFY 2007.10.25
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ ��û�ڰ� ��ȸ ��ǰ�� ����
				// param1 == ���� �ε���, param2 == StgIndex, param3 == StgItemUnique, param4 == StgItemNum
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_GIVEITEM, 
									0, NULL, NULL, 0, 0, 0, &clItem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,  
									pclMsg->siPresentIndex, pclMsg->siStgIndex, pclMsg->siStgItemUnique, pclMsg->siStgItemNum, 0, NULL, NULL);
			}

		}
		break;

	case 2:
		{

		}
		break;
	}

	if( pclCM->IsValidID( id ) ) {	
		SendServerResponseMsg( RANKTYPE_FEAST, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}

}

//#if defined(_LEON_FEAST_EFFECT)
void cltServer::DoMsg_DBMSG_RESPONSE_FEAST_USEEFFECT( sPacketHeader *pPacket )
{
	SI32 returnval = 0;

	sDBResponse_FeastUseEffect *pclMsg = (sDBResponse_FeastUseEffect *)pPacket;

	SI32 id = pclMsg->usCharID;
	
	if( pclCM->IsValidID(id) == FALSE )									return;
	if( pclMsg->siPos < 0 || pclMsg->siPos >= MAX_ITEM_PER_PERSON )		return;

	returnval = SRVAL_FEAST_FAIL_USEEFFECT_NOTHAVETICKET;

	switch( pclMsg->siResult ) 
	{
	case 1:	// �����̿�� ��� ����
		{		
			if ( pclMsg->clitem.siItemNum == 0 )
			{
				pclMsg->clitem.Init();
			}
			else
			{
				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siPos ].Set( &pclMsg->clitem );
			}


			cltGameMsgResponse_PersonItemInfo clinfo1( pclMsg->siPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clitem, 0);

			// Ŭ���̾�Ʈ ���� ������ ���� ��û!
			cltMsg clMsg1(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo1), (BYTE*)&clinfo1);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);


			// ������ �ִ� ��� Ŭ���̾�Ʈ�� ���� ������
			cltGameMsgResponse_FeastUseEffect sendMsg( pclMsg->siEffectNum );
			cltMsg clMsg( GAMEMSG_RESPONSE_FEAST_USEEFFECT, sizeof( sendMsg ), (BYTE*)&sendMsg );

			//  pclCM->UseEffectToAllPersonInVillage(...); =>
			SI32 targetid;

			SI32 index = 0;
			while(targetid = pclCM->GetCharOrder(index))
			{
				index++;

				cltCharServer* pclchar = (cltCharServer*)(pclCM->CR[targetid]);
				if(pclchar->GetSession())
				{
					if(pclchar->GetCurrentVillageUnique() == pclMsg->siVillageUnique)
					{
						pclchar->SendNetMsg((sPacketHeader*)&clMsg);
					}
					
				}
			}
			
			returnval = SRVAL_FEAST_SUCCESS_USEEFFECT;

			// LEEKH ��û - ��ȸ�� ���� ���� ������ ���� �߰� �ʿ�
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȸ ����.
				// param1 == �κ��丮 ��ġ.
				// param2 == �κ��� ������ ����ũ.
				// param3 == �κ��� ���� ������ ����.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FEAST, LOGCOMMAND_INDEX_FEAST_USEEFFECT, 
									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUseItem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,
									pclMsg->siPos, pclMsg->clitem.siUnique, pclMsg->clitem.siItemNum, 0, 0, NULL, NULL);
			}
		}
		break;
	}

	if( returnval ) {
		SendServerResponseMsg( RANKTYPE_FEAST, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}
//#endif

void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_RESERVATION(sPacketHeader* pPacket)
{
	sDBResponse_PartyHall_Reservation* pclMsg = (sDBResponse_PartyHall_Reservation*)pPacket;

	if( 0 > pclMsg->m_siResult )
		return;

	SI32 id = pclMsg->m_usCharID;
	if( false == pclCM->IsValidID(id))									
		return; 

  	SI32	siVillageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(pclMsg->m_siVillageUnique != siVillageUnique)
		return;
	

	// ������ ���ֱ�.
	sDBRequest_ChangeStrMoney ChangeStrMoney( CHANGESTRMONEY_NORMAL, 0, pclCM->CR[id]->GetCurrentVillageUnique(), RANKTYPE_FEAST, pclMsg->m_ResvMoney * 0.5);
	pclGameDBProcess->SendMsg((sPacketHeader *)&ChangeStrMoney);

	// ����ݰ� ���ֱ�.
	cltMoney cltTempMoney;
	cltTempMoney.Set(0.f);
	cltMoney cltTexPay;
	cltTexPay.Set(pclMsg->m_ResvMoney * 0.2);
	sDBRequest_AutoPayDividend AutoPayDividend(
												id, 
												pclCM->CR[id]->GetCurrentVillageUnique(),
												&cltTempMoney, 
												&cltTempMoney, 
												&cltTexPay,
												0, 
												0, 
												0, 
												pclTime->clDate.uiYear, 
												&pclTime->clDate 
											);

	pclGameDBProcess->SendMsg( (sPacketHeader *)&AutoPayDividend );


	// ���� �ݾ� ����.
	pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->m_UserChangeMoney );
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);
	
	cltFeastStg*		  pcltFeastStg	= pclFeastManager->GetStrInfo( siVillageUnique )->clFeastStrInfo.clFeastStg;
	if(NULL == pcltFeastStg)
		return;

	PartyHall_Decoration* pclDecoration = pclFeastManager->GetStrInfo( siVillageUnique )->clFeastStrInfo.clDecoration;
	if(NULL == pclDecoration)
		return;


	if(0 <= pclMsg->m_siDecorationSlotNum && MAX_PARTYHALL_DECORATION_ITEM > pclMsg->m_siDecorationSlotNum)
	{
		//��Ĺ��� �ϳ� �����Ѵ�.
		pclDecoration[pclMsg->m_siDecorationSlotNum].m_DacorationNum--;
		if(0 == pclDecoration[pclMsg->m_siDecorationSlotNum].m_DacorationNum)
			pclDecoration[pclMsg->m_siDecorationSlotNum].m_DacorationKind = 0;	
	
	}
		
	//-----------------------------------------------------------------------------------------------------------------
	//����� ��Ĺ� ������ �����ش�.
	cltGameMsgResponse_PartyHall_Decoration_List cltInfo4;
	for(SI32 Count = 0; Count < MAX_FEAST_STG_NUMBER; ++Count) 
	{
		cltInfo4.m_clDecoration[Count].m_siDecorationKind = pclDecoration[Count].m_DacorationKind;
		cltInfo4.m_clDecoration[Count].m_siDecorationNum  = pclDecoration[Count].m_DacorationNum;
		cltInfo4.m_clDecoration[Count].m_siDecorationSlot = Count;
	}

	cltMsg clMsg4(GAMEMSG_RESPONSE_PARTYHALL_DECORATION_LIST, sizeof(cltGameMsgResponse_PartyHall_Decoration_List), (BYTE*)&cltInfo4);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);
	//-----------------------------------------------------------------------------------------------------------------
	
	SI32	Personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	// ������ġ ã�� �ڵ�.
	cltPatyHallResvInfo* pPatyHallResvInfo		= NULL;
	cltPatyHallResvInfo* pPatyHallResvInfoList	= (cltPatyHallResvInfo*)&pclClient->pclFeastManager->clPartyHallResvInfo[pclMsg->m_siPartyHallIndex][0];
	if(NULL == pPatyHallResvInfoList)
		return;
	
	pPatyHallResvInfo = &pPatyHallResvInfoList[pclMsg->m_SystemTime.wHour];
	if(NULL == pPatyHallResvInfo)
		return;
		
	// �������� ����.
	pPatyHallResvInfo->m_siPersonID			=	pclMsg->m_siPersonID;						
	pPatyHallResvInfo->m_SystemTime.wYear	=	pclMsg->m_SystemTime.wYear;									
	pPatyHallResvInfo->m_SystemTime.wMonth	=	pclMsg->m_SystemTime.wMonth;								
	pPatyHallResvInfo->m_SystemTime.wDay	=	pclMsg->m_SystemTime.wDay;									
	pPatyHallResvInfo->m_SystemTime.wHour	=	pclMsg->m_SystemTime.wHour;									
	pPatyHallResvInfo->m_SystemTime.wMinute	=	pclMsg->m_SystemTime.wMinute;								
	pPatyHallResvInfo->m_siEntranceType		=	pclMsg->m_siEntranceType;					
	pPatyHallResvInfo->m_siDecorationKind	=	pclMsg->m_siDecorationKind;					
	pPatyHallResvInfo->m_siValueType		=	pclMsg->m_siValueType;				
	MStrCpy(pPatyHallResvInfo->m_szPersonName,	pclMsg->m_szPersonName,	sizeof(pPatyHallResvInfo->m_szPersonName));
	MStrCpy(pPatyHallResvInfo->m_szReason,		pclMsg->m_szReason,		sizeof(pPatyHallResvInfo->m_szReason));

	// Ŭ�󿡰� ���� ���� ����.
	cltGameMsgResponse_PartyHall_Reservation cltInfo;
	cltInfo.m_siPersonID		  =	pclMsg->m_siPersonID;					
	cltInfo.m_siYear			  =	pclMsg->m_SystemTime.wYear;					
	cltInfo.m_siMonth			  =	pclMsg->m_SystemTime.wMonth;		
	cltInfo.m_siDay				  =	pclMsg->m_SystemTime.wDay;		
	cltInfo.m_siHour			  =	pclMsg->m_SystemTime.wHour;		
	cltInfo.m_siMinute			  =	pclMsg->m_SystemTime.wMinute;	
	cltInfo.m_siDecorationKind	  =	pclMsg->m_siDecorationKind;
	cltInfo.m_siEntranceType	  = pclMsg->m_siEntranceType;
	cltInfo.m_siValueType	 	  =	pclMsg->m_siValueType;	
	cltInfo.m_siPartyHallIndex	  = pclMsg->m_siPartyHallIndex;
	cltInfo.m_siUserMoney		  = pclMsg->m_UserChangeMoney;
	MStrCpy(cltInfo.m_szPersonName,	pclMsg->m_szPersonName, sizeof(cltInfo.m_szPersonName));
	MStrCpy(cltInfo.m_szReason,		pclMsg->m_szReason,		sizeof(cltInfo.m_szReason));

	cltMsg clMsg(GAMEMSG_RESPONSE_PARTYHALL_RESERVATION, sizeof(cltGameMsgResponse_PartyHall_Reservation), (BYTE*)&cltInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
}
void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_CLOSE(sPacketHeader* pPacket)
{


	
}

void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_ADD_PRESENT(sPacketHeader* pPacket)
{
	sDBResponse_PartyHall_Add_Present* pclMsg = (sDBResponse_PartyHall_Add_Present*)pPacket;

	if( 1 > pclMsg->siResult )
		return;

	SI32 id	= pclMsg->usCharID;
	if( pclCM->IsValidID(id) == FALSE )									
		return;

	SI32 Personid    = pclCM->CR[id]->pclCI->GetPersonID(); 
	
    SI32 ResvIndex = pclClient->pclFeastManager->GetReveIndex(pclMsg->m_siPartyHallIndex, Personid);
	
	cltPatyHallResvInfo* pPatyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[pclMsg->m_siPartyHallIndex][ResvIndex];
	if(NULL == pPatyHallResvInfo)
		return;
	
	// �迭 ���� �˻�.
	if(0 > pclMsg->m_siItemListIndex || RESERVATIO_PRESENT_ITEM <= pclMsg->m_siItemListIndex)
		return;

	pPatyHallResvInfo->m_PresentItem[pclMsg->m_siItemListIndex].m_siItemUnique = pclMsg->m_siItemUnique;
	pPatyHallResvInfo->m_PresentItem[pclMsg->m_siItemListIndex].m_siItemNum	   = pclMsg->m_siItemNum;

	// �迭 ���� �˻�.
	if(0 > pclMsg->m_siPresentItemInvenPos || MAX_ITEM_PER_PERSON <= pclMsg->m_siPresentItemInvenPos)
		return;

	// ������ ����.  
	cltItem RemoveItem   = pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->m_siPresentItemInvenPos];
	RemoveItem.siItemNum = pclMsg->m_siItemNum;

	sDBRequest_UseItem useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), pclMsg->m_siPresentItemInvenPos, &RemoveItem, USEITEM_REASON_PARTYHALLGIFT);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

	cltGameMsgResponse_PartyHall_Add_Present cltInfo(Personid, pclMsg->m_siPartyHallIndex, pclMsg->m_siItemUnique,pclMsg->m_siItemNum, 
													 pclMsg->m_siItemListIndex, pclMsg->m_siPresentItemInvenPos);
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTYHALL_ADD_PRESENT, sizeof(cltGameMsgResponse_PartyHall_Add_Present), (BYTE*)&cltInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_ADD_DECORATION(sPacketHeader* pPacket)
{
	sDBResponse_PartyHall_Add_Decoration* pclMsg = (sDBResponse_PartyHall_Add_Decoration *)pPacket;

	if( 0 > pclMsg->m_siResult )
		return;

	SI32 id = pclMsg->m_usCharID;

	// ��ƼȦ â��.
	cltFeastStg*		  pcltFeastStg	= pclFeastManager->GetStrInfo(pclMsg->m_siVillageUnique)->clFeastStrInfo.clFeastStg;
	if(NULL == pcltFeastStg)
		return;

	// â�� ��Ĺ�.
	PartyHall_Decoration* pclDecoration = pclFeastManager->GetStrInfo(pclMsg->m_siVillageUnique)->clFeastStrInfo.clDecoration;
	if(NULL == pclDecoration)
		return;


	memcpy( pcltFeastStg, pclMsg->m_DeleteItem, sizeof(pclMsg->m_DeleteItem));
	
	// �迭 ���� �˻�.
	if(0 > pclMsg->m_siDecorationSlot || MAX_PARTYHALL_DECORATION_ITEM <= pclMsg->m_siDecorationSlot)
		return;

	pclDecoration[pclMsg->m_siDecorationSlot].m_DacorationKind = pclMsg->m_siDecorationKind;
	pclDecoration[pclMsg->m_siDecorationSlot].m_DacorationNum  = pclMsg->m_siDecorationNum;
	

	cltGameMsgResponse_PartyHall_Add_Decoration cltInfo;

	cltInfo.m_siVillageUnique	=	pclMsg->m_siVillageUnique;
	cltInfo.m_siDecorationKind	=	pclMsg->m_siDecorationKind;
	cltInfo.m_siDecorationNum	=	pclMsg->m_siDecorationNum;
	cltInfo.m_siDecorationSlot	=	pclMsg->m_siDecorationSlot;
	
	memcpy( cltInfo.m_DeleteItem, pclMsg->m_DeleteItem, sizeof(cltInfo.m_DeleteItem));
	

	cltMsg clMsg(GAMEMSG_RESPONSE_PARTYHALL_ADD_DECORATION, sizeof(cltGameMsgResponse_PartyHall_Add_Decoration), (BYTE*)&cltInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);  
}

// ���� �ֱ�.
void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_GIVEITEM( sPacketHeader* pPacket )
{
	sDBResponse_PartyHall_GiveItem* pclInfo = (sDBResponse_PartyHall_GiveItem*)pPacket;

	if(0 > pclInfo->m_siResult )
		return;
	
//-----------------------------
// ������ �������� �ִ��� Ȯ��.
//-----------------------------
	cltPatyHallResvInfo* pPartyHallResvList	= &pclClient->pclFeastManager->clPartyHallResvInfo[ pclInfo->m_siPartyHallIndex ][0];
	if(NULL == pPartyHallResvList)
		return;

	cltPatyHallResvInfo* pPartyHallResvInfo = NULL;

	// �������� ������ ��Ƽ���� ������.
	pPartyHallResvInfo = &pPartyHallResvList[sTime.wHour];
	if(NULL == pPartyHallResvInfo)
		return;

	// ���� �������� ������ ���.
	cltPartyHallPresentItemInfo* pPartyItem = &pPartyHallResvInfo->m_PresentItem[0];
	if(NULL == pPartyItem)
		return;

	// ù��° �������� ������ ���� �����۵� �����Ƿ� ����. 
	if( 0 >= pPartyItem->m_siItemUnique || 0 >= pPartyItem->m_siItemNum )
		return;
//-----------------------------
	
	SI32	PersonIDGiveItem[MAX_PERSON_NUMBER];
	ZeroMemory( PersonIDGiveItem, sizeof( PersonIDGiveItem ) );
	
	SI32 MapIndex		= PARTYHALL_START_MAP_INDEX + pclInfo->m_siPartyHallIndex;		// �� �ε���.
	SI32 UserCountNum	= 0;															// ��Ƽ�� ������.

	// ��Ƽ���� �ƴϸ� ����.
	if(PARTYHALL_START_MAP_INDEX > MapIndex || PARTYHALL_START_MAP_INDEX + MAX_PARTYHALL_MAP < MapIndex)
		return;

	for(SI32 IdCount = 1; IdCount < MAX_PERSON_NUMBER; ++IdCount)
	{
		// ���̵� ��� �˻�.
		if( false == pclCM->IsValidID(IdCount) ) 
			continue;

		// ��Ƽ�忡 �ִ� ������ ���̵� ����.
		if( MapIndex == pclCM->CR[IdCount]->GetMapIndex() )
		{
			PersonIDGiveItem[UserCountNum] = IdCount;
			++UserCountNum; 
		}
	}
	
	// ������ ���� ������ ����.
	if( 0 >= UserCountNum )
	{
		// �ش� ���� ������ ���� ����.
		ZeroMemory( pPartyItem, sizeof(cltPartyHallPresentItemInfo) * RESERVATIO_PRESENT_ITEM );
		return;
	}

	SI32 GiveItemNum[RESERVATIO_PRESENT_ITEM];
	ZeroMemory( GiveItemNum, sizeof(GiveItemNum));
	for( SI32 count = 0; count < RESERVATIO_PRESENT_ITEM; ++count )
	{
		if( 0 >= pPartyItem[count].m_siItemNum )
			break;

		GiveItemNum[count] = pPartyItem[count].m_siItemNum / UserCountNum;
		if( 0 >= GiveItemNum[count] )
			GiveItemNum[count] = 1;
	}

	
	SI32			ItemSlot = 0;
	cltCharServer*	pclchar	 = NULL;
	for( SI32 UserCount = 0; UserCount < UserCountNum; ++UserCount )
	{	
		if( false == pclCM->IsValidID(PersonIDGiveItem[UserCount]) ) 
			continue;

		pclchar = (cltCharServer*)pclCM->CR[ PersonIDGiveItem[UserCount] ];
		pclchar->GiveItem( pPartyItem[ItemSlot].m_siItemUnique, GiveItemNum[ItemSlot], INPUTITEMPERSON_OPTION_NONE, 0 );

		// ������ ������ �������� ����.
		pPartyItem[ItemSlot].m_siItemNum -= GiveItemNum[ItemSlot];
		
		// �����Ϸ��� �纸�� ���������� ���ٸ� 1���� ��������.
		if( GiveItemNum[ItemSlot] > pPartyItem[ItemSlot].m_siItemNum )
			GiveItemNum[ItemSlot] = 1;
		
		// ���̻� ������ �������� ������ ���� �������� ��������.
		if( 0 >= pPartyItem[ItemSlot].m_siItemNum )	
			++ItemSlot;

		// ������ �������� �� ���� ������ ��ž.
		if( RESERVATIO_PRESENT_ITEM <= ItemSlot )
			break;

		// ���̻� ���� ������ ������ �������� ������.
		if( 0 >= pPartyItem[ItemSlot].m_siItemNum )
			break;

		// ������ �����ε� ���� �������� �ִٸ� �ٽ� ó�� �������� �������� �ټ��ְ� �Ѵ�.
		if( (UserCount + 1) == UserCountNum ) 
		{
			if( 0 < pPartyItem[ItemSlot].m_siItemNum )
			{
				UserCount = -1;
			}
		}
	}
	
	// �ش� ���� ������ ���� ����.
	ZeroMemory( pPartyItem, sizeof(cltPartyHallPresentItemInfo) * RESERVATIO_PRESENT_ITEM );
}



void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_RESERVELIST(sPacketHeader* pPacket)
{
	sDBResponse_PartyHall_ReserveList* pclMsg = (sDBResponse_PartyHall_ReserveList*)pPacket;  

#ifdef _SAFE_MEMORY
	for(SI32 i=0; i<MAX_PARTYHALL_MAP; i++)
	{
		for(SI32 j=0; j<MAX_PARTYHALL_RESERVATION_INFO_LIST; j++)
		{
			pclClient->pclFeastManager->clPartyHallResvInfo[i][j].Set(&pclMsg->clPartyHallResvInfo[i][j]); 
		}
	}
#else
	memcpy(pclClient->pclFeastManager->clPartyHallResvInfo, pclMsg->clPartyHallResvInfo, sizeof(pclClient->pclFeastManager->clPartyHallResvInfo));
#endif
}

void cltServer::DoMsg_DBMSG_RESPONSE_PARTYHALL_DECORATION_LIST(sPacketHeader* pPacket)
{
	sDBResponse_PartyHall_Decoration_List* pclMsg = (sDBResponse_PartyHall_Decoration_List*)pPacket;

	PartyHall_Decoration*	DecorationList	= NULL;
	cltStrInfo*				pStructInfo		= NULL;		
	
	for( SI32 VillageCount = 1; VillageCount < MAX_VILLAGE_NUMBER; ++VillageCount )
	{
		pStructInfo = pclClient->pclFeastManager->GetStrInfo(VillageCount);
		if(NULL == pStructInfo)
			continue;

		DecorationList = pStructInfo->clFeastStrInfo.clDecoration;
		
		memcpy( DecorationList, pclMsg->clDecoration[VillageCount], sizeof(PartyHall_Decoration) * MAX_PARTYHALL_DECORATION_ITEM);
	}
}