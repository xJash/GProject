#include "..\Common\CommonHeader.h"
#include "..\Common\Order\Order.h"
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\CommonLogic\Msg\MsgType-Agriculture.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Agriculture.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"

#include "../CommonLogic/Land/Land.h"
#include "../CommonLogic/Mine/Mine.h"

void cltServer::DoMsg_DBMSG_RESPONSE_AGRICULTUREGETPRODUCTS(sPacketHeader* pPacket)
{
	sDBResponse_AgricultureGetProducts *pclMsg = (sDBResponse_AgricultureGetProducts*)pPacket;
	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siResult == 1 )
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ���.
			// param1 == ������ ��ġ 
			// param2 == Agriculture Type. 			
			// 	
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];
			
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PERSONITEM_AGRICULTURE, 
								0, pclchar, NULL, 0, 0, 0, &pclMsg->clGetProductsItem, pclMsg->clLeftItem.siItemNum, 0, pclMsg->siKind, 0, 0, 0, 
								pclMsg->siAddedInvPos, pclMsg->siAgricultureType, 0, 0, 0, 
								NULL, NULL);
		}
	}

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	// ��ȹ���� ȹ���Ѱ� ��迡 �߰�
	if ( pclMsg->clLeftItem.siUnique > 0 )
	{
		//cyj ����ǰ ��� �߰�
		pclItemManager->AddProductionItemNum( pclMsg->clLeftItem.siUnique, pclMsg->siAddedItemNum );

		// ���ο� ��� - ������� ���� ���� ��ǰ�� ��踦 ����.
		NStatistics_Add("Item", pclMsg->clLeftItem.siUnique, "ProductionNum", pclMsg->siAddedItemNum);
		NStatistics_Set("Item", pclMsg->clLeftItem.siUnique, "Name", pclItemManager->GetName(pclMsg->clLeftItem.siUnique));
	}
	
	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// ������ Update
		if ( pclMsg->siAddedInvPos > 0 )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siAddedInvPos ].Set( &pclMsg->clLeftItem );
		}

		cltGameMsgResponse_AgricultureGetProducts clGameMsgResponse_AgricultureGetProducts( pclMsg->siAddedInvPos, pclMsg->siAddedItemNum, &pclMsg->clLeftItem, pclMsg->siCharUnique, pclMsg->siKind, pclMsg->siAgricultureType );
		cltMsg clMsg( GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTS, sizeof( clGameMsgResponse_AgricultureGetProducts ), (BYTE*)&clGameMsgResponse_AgricultureGetProducts );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
		
		cltGameMsgResponse_AgricultureGetProductsNotify clGameMsgResponse_AgricultureGetProductsNotify(
			pclMsg->clLeftItem.siUnique, pclMsg->siAddedItemNum, pclMsg->siCharUnique, pclMsg->siKind, pclMsg->siAgricultureType );
		cltMsg clMsg1( GAMEMSG_RESPONSE_AGRICULTUREGETPRODUCTSNOTIFY, sizeof( clGameMsgResponse_AgricultureGetProductsNotify ), (BYTE*)&clGameMsgResponse_AgricultureGetProductsNotify );
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg( &clMsg1 , true);
	}

	return;
}


void cltServer::DoMsg_DBMSG_RESPONSE_AGRICULTUREPAYMONEYFORRENTLAND(sPacketHeader* pPacket)
{
	sDBResponse_AgriculturePayMoneyForRentLand *pclMsg = (sDBResponse_AgriculturePayMoneyForRentLand*)pPacket;

	SI32 id = pclMsg->siCharID;

	// ������ ����
	if( pclMsg->siVillageUnique <= 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )					return;
	if ( pclMsg->siAgricultureItemUnique < 0 || pclMsg->siAgricultureItemUnique > MAX_ITEM_UNIQUE )		return;

	if ( pclMsg->siResult == 1 )
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� �ӽ÷� ����.
			// param1 == Ÿ��, 
			// param2 == Agriculture Item Unique, 
			// param3 == �ӽ÷� ������ �Ⱓ ����ð�(��)
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_WORKINGPAYMONEYFORRENT, 
								0, pclchar, NULL, 0, pclMsg->siPayMoney, pclMsg->siLeftMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								pclMsg->siStructType, pclMsg->siAgricultureItemUnique, pclMsg->uiLeaseExpire, 0, 0, NULL, NULL);
		}
	}

	if ( pclMsg->siResult != 1 )
	{
		if ( pclMsg->siResult == -1 )
		{
			// ������ ����
		}
		else
		{
			pclLog->FilePrint( TEXT("Agriculture.txt"), TEXT("DoMsg_DBMSG_REQUEST_AGRICULTUREPAYMONEYFORRENTLAND pclMsg->siResult = %d"), pclMsg->siResult );
		}

		return;
	}
	
	//---------------------------------------------------------------------------------------------------
	// �ǹ��� �� ����
	//---------------------------------------------------------------------------------------------------
	SI16 SturctNumber = 0;
	switch ( pclMsg->siStructType )
	{
	case RANKTYPE_LAND:
		{
			SturctNumber = 130;
			if ( pclVillageManager->pclVillageInfo[ pclMsg->siVillageUnique ]->clVillageVary.clStructureInfo.IsDuplicate( SturctNumber ) == FALSE )
			{
				return;
			}

			cltStrInfo* pclinfo = pclLandManager->GetStrInfo( pclMsg->siVillageUnique );
			if ( pclinfo )
			{
				pclinfo->clCommonInfo.clMoney.itMoney += pclMsg->siPayMoney;
			}
		}
		break;
	case RANKTYPE_MINE:
		{
			SturctNumber = 160;
			if ( pclVillageManager->pclVillageInfo[ pclMsg->siVillageUnique ]->clVillageVary.clStructureInfo.IsDuplicate( SturctNumber ) == FALSE )
			{
				return;
			}

			cltStrInfo* pclinfo = pclMineManager->GetStrInfo( pclMsg->siVillageUnique );
			if ( pclinfo )
			{
				pclinfo->clCommonInfo.clMoney.itMoney += pclMsg->siPayMoney;
			}
		}
		break;
	default:
		return;
	}
	//---------------------------------------------------------------------------------------------------

	cltCharServer* pclChar = NULL;
	if( id > 0 && pclCM->IsValidID(id) )	{		pclChar = pclCM->GetCharServer( id );		}
	if( pclChar != NULL )
	{
		if( pclChar->pclCI->GetPersonID() != pclMsg->siPersonID )		pclChar = NULL;
	}

	cltAgriculture* pclAgriculture = NULL;
	if( pclChar )		pclAgriculture = pclChar->m_pclAgriculture;

	//---------------------------------------------------------------------------------------------------
	// ĳ���� ���� ó��
	//---------------------------------------------------------------------------------------------------
	if( pclChar && pclAgriculture )
	{
		// ���� �� ���� �˸�.
		pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siLeftMoney );
		cltGameMsgResponse_AgriculturePayRentFee clinfo( pclMsg->siPayMoney, pclMsg->siLeftMoney, pclMsg->siVillageUnique, pclMsg->siStructType );
		cltMsg clMsg( GAMEMSG_RESPONSE_AGRICULTUREPAYRENTFEE,  sizeof( clinfo ), (BYTE*)&clinfo );
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);

		// ����Ȱ�� ���
		pclAgriculture->AddAgriculture( pclMsg->siVillageUnique, pclMsg->uiLeaseExpire );

		SI32 SkillLevel = 0;
		switch ( pclMsg->siStructType )
		{
		case RANKTYPE_LAND:
			{	
				pclChar->siFarmingItemUnique = pclMsg->siAgricultureItemUnique;
				pclAgriculture->StartAgriculture( pclMsg->siVillageUnique, pclClient->CurrentClock );

				SkillLevel = pclChar->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_FARM, 0, 0, &pclChar->pclCI->clCharItem.clItem[0] );
				SI32 SuccessPercent = pclChar->GetFarmRate( SkillLevel );

				SI32 delaytime = 40000;
				delaytime -= ((pclClient->pclItemManager->clItemStatistic.siItemPriceIndex / 100000 + 1 ) / 2 * 2) * 1000;
				delaytime = max( 20000, delaytime );

				UI32 leftTime = pclAgriculture->GetExpireTime(pclMsg->siVillageUnique) - pclClient->GetMinuteFromsTime( sTime );

				cltGameMsgResponse_AgricultureStart clGameMsgResponse_AgricultureStart( pclMsg->siAgricultureItemUnique, SuccessPercent, RANKTYPE_LAND, delaytime, leftTime );
				cltMsg clMsg1( GAMEMSG_RESPONSE_AGRICULTURESTART, sizeof(clGameMsgResponse_AgricultureStart), (BYTE*)&clGameMsgResponse_AgricultureStart );
				pclChar->SendNetMsg((sPacketHeader*)&clMsg1);
			}
			break;
		case RANKTYPE_MINE:
			{
				pclChar->siMiningItemUnique = pclMsg->siAgricultureItemUnique;
				pclAgriculture->StartAgriculture( pclMsg->siVillageUnique, pclClient->CurrentClock );

				SkillLevel = pclChar->pclCI->clCharSkill.GetTotalSkillLevel( SKILL_MINE, 0, 0, &pclChar->pclCI->clCharItem.clItem[0] );
				SI32 SuccessPercent = pclChar->GetMineRate( SkillLevel );

				SI32 delaytime = 60000;
				delaytime -= ((pclClient->pclItemManager->clItemStatistic.siItemPriceIndex / 100000 + 1 ) / 2 * 2) * 1000;
				delaytime = max( 40000, delaytime );

				UI32 leftTime = pclAgriculture->GetExpireTime(pclMsg->siVillageUnique) - pclClient->GetMinuteFromsTime( sTime );
																							
				cltGameMsgResponse_AgricultureStart clGameMsgResponse_AgricultureStart( pclMsg->siAgricultureItemUnique, SuccessPercent, RANKTYPE_MINE, delaytime, leftTime );
				cltMsg clMsg1( GAMEMSG_RESPONSE_AGRICULTURESTART, sizeof(clGameMsgResponse_AgricultureStart), (BYTE*)&clGameMsgResponse_AgricultureStart );
				pclChar->SendNetMsg((sPacketHeader*)&clMsg1);
			}
			break;
		}
	}
	//---------------------------------------------------------------------------------------------------
	
	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETAGRICULTURELEASEINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetAgricultureLeaseInfo* pclMsg = (sDBResponse_GetAgricultureLeaseInfo*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( pclCM->IsValidID(id) == false )			return;
	if( pclMsg->siResult < 0 )					return;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )						return;

	cltAgriculture* pclAgriculture = pclchar->m_pclAgriculture;
	if( pclAgriculture == NULL )				return;

	//pclAgriculture->AddAgriculture( pclMsg->siVillageUnique, pclMsg->uiExpire );
	for( SI32 i=0; i<MAX_AGRICULTURE_COUNT; i++ )
	{
		if( pclMsg->siVillageUnique[i] > 0 && pclMsg->siVillageUnique[i] <= CUR_VILLAGE_LIMIT )
			pclAgriculture->AddAgriculture( pclMsg->siVillageUnique[i], pclMsg->uiExpire[i] );
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_EXPIREDAGRICULTERLEASE(sPacketHeader* pPacket)
{
	sDBResponse_ExpiredAgricultureLease* pclMsg = (sDBResponse_ExpiredAgricultureLease*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if(pclMsg->siResult == 1)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 4] // ���� ����
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_AGRICULTURE_EXPIRE, 
											0, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											0, 0, 0, 0, 0, NULL, NULL);
		}
	}

	if( pclCM->IsValidID(id) == false )			return;
	if( pclMsg->siResult < 0 )					return;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL )						return;

	cltAgriculture* pclAgriculture = pclchar->m_pclAgriculture;
	if( pclAgriculture == NULL )				return;

	// ����Ȱ��(���, ä��) �������� �ڵ����� ������ ���ش�.
	//OrderForceStop(id, BY_PLAYER);
}
