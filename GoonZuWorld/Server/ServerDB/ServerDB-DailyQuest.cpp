
#include "Char\CharManager\CharManager.h"


//---------------------------------------
// Server
//---------------------------------------
#include "..\Server\Server.h"
#include "..\Server\Statistics\Statistics.h"

//--------------------------------------
// CommonLogic
//--------------------------------------
#include "..\CommonLogic\Msg\MsgType-DailyQuest.h"
#include "..\CommonLogic\MsgType-Person.h"

//---------------------------------------
// DBManager
//---------------------------------------
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Guild.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"


void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUESTADD( sPacketHeader* pPacket)
{
	sDBResponse_DailyQuestAdd * pclMsg = (sDBResponse_DailyQuestAdd*)pPacket;

	SI32 id = pclMsg->siCharID;
	
	if ( pclMsg->siResult == 1 )
	{
		// LEEKH MODIFY 2007.10.25
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // ��(�𺴰�) ����.
			// param1 == ���� ��.
			// param2 == ��ǰ ������ ����ũ.
			// param3 == ��ǰ ������ ����.
			// param4 == ��ݾ�
			// param5 == ������ �ִ� ����ġ.
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST_ADD, 
								0, pclchar, NULL, 0, pclMsg->siFee, pclMsg->siLeftMoney, NULL, 0, pclMsg->siMonsterKind, 0, 0, 0, 0, 
								pclMsg->siMonsterNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardMoney, pclMsg->siRewardExp, NULL, NULL);
		}
	}

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclMsg->siVillageUnique > 0 && pclMsg->clStrMoney.itMoney > 0 )
	{
		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, pclMsg->siStrType );
		if( pStrInfo ) 
		{
			// [���� : Ȳ���� 2008. 1. 16 => ���� ������ ���Ǽ� ������ ����Ҷ� ������ �ִ� ���ͱ��� �ں������� ���°� ����]
			//pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clStrMoney );
			pStrInfo->clCityhallStrInfo.clProfitMoney = pclMsg->clStrMoney;
		}
	}

	cltMoney clMoney;
	clMoney.Set( pclMsg->siFee );
	clCurrencyInfo.clOutputMoney_QuestFee.Increase( &clMoney );

//	DB�� ������ ���� ����Ʈ�� �����ϴ� ������ ����
//	pclDailyQuestMgr->InitQuestListData( pclMsg->siQuestListIndex, pclMsg->siMonsterKind, pclMsg->siMonsterNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardMoney, pclMsg->siRewardExp, pclMsg->siFee, pclMsg->siLeftTime);//, pclMsg->bPCRoomQuest );

	// ����Ʈ ����ڰ� �����ϴ� ��� 
	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{		
		//pclDailyQuestMgr->Set( pclMsg->siMonsterKind, pclMsg->siMonsterNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardExp, pclMsg->siFee, pclMsg->siLeftTime, 0 );
		pclCM->CR[id]->pclCI->clDailyQuestInfo.Set( pclMsg->siMonsterKind, pclMsg->siMonsterNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardMoney, pclMsg->siRewardExp, pclMsg->siFee, pclMsg->siQuestTime, pclMsg->siLeftTime, 0, pclMsg->bMoneySelected );
		pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siLeftMoney );
		
		cltGameMsgResponse_DailyQuestSelect clinfo( &pclCM->CR[id]->pclCI->clDailyQuestInfo, pclMsg->siLeftMoney );
		cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTSELECT, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUESTDEL( sPacketHeader* pPacket)
{
	sDBResponse_DailyQuestDel * pclMsg = (sDBResponse_DailyQuestDel*)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}
	
	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	// �������� �������� �˷���� �ϹǷ�...
	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		if ( pclMsg->uiSuccess )
		{
			cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

			if ( pclMsg->siAddMoney  )
			{
				// �� ������Ʈ
				pclChar->pclCI->clIP.IncreaseMoney(pclMsg->siAddMoney);
			}
			else
			{
				if( pclMsg->siInventoryItemIndex >= 0 && pclMsg->siInventoryItemIndex < MAX_ITEM_PER_PERSON )
					pclChar->pclCI->clCharItem.clItem[pclMsg->siInventoryItemIndex].Set(&pclMsg->clInventoryItem);
			}


			
			// ����ġ ������Ʈ
			pclChar->IncreaseExp( pclMsg->siExp );

			// ȹ���� GuildPoint�� ���Ѵ�. - NOTJAPAN[3/21]
			SI32 addGP = 0;
			if ( pclClient->siServiceArea != ConstServiceArea_Japan )
			{
				SI32 guildUnique = pclChar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
				if ( guildUnique > 0)
				{
					addGP = pclMsg->siExp / 100;
					if ( addGP > 0 )
					{
						sDBRequest_Guild_ChangeGuildPoint clMsg(guildUnique, pclChar->pclCI->GetPersonID(), addGP, TYPE_GUILDPOINT_DAILYQUEST );
						pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
					}
				}
			}


			
			// ������ ������Ʈ
			
			/*
			cltGameMsgResponse_PersonItemInfo clinfo( pclMsg->siInventoryItemIndex, PERSONITEMINFO_OPTION_DAILYQUEST, pclMsg->siChangedItemNum, 0, &pclMsg->clInventoryItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			*/
			
			
			cltGameMsgResponse_DailyQuestEnd clinfo1( pclMsg->uiSuccess, pclChar->pclCI->clIP.GetCurExp(), 
				pclMsg->siInventoryItemIndex, pclMsg->siChangedItemNum, 
				&pclMsg->clInventoryItem, pclMsg->siAddMoney, pclMsg->siExp, addGP ); // SI32->SI64 ����ġ �����÷ο춧���� ����
			cltMsg clMsg1(GAMEMSG_RESPONSE_DAILYQUESTEND, sizeof(clinfo1), (BYTE*)&clinfo1);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

			// �𺴰� ����Ʈ Ŭ�������. 
			pclStatisticsManager->clDailyStatistics.siDailyQuestClearNum++;
			
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_DAILYQUEST);


		}
		else
		{
			cltItem clItem;
			clItem.Init();
			cltGameMsgResponse_DailyQuestEnd clinfo1( pclMsg->uiSuccess, pclCM->CR[id]->pclCI->clIP.GetCurExp(), 0, 0, &clItem, 0, 0, 0 );// SI32->SI64 ����ġ �����÷ο춧���� ����
			cltMsg clMsg1(GAMEMSG_RESPONSE_DAILYQUESTEND, sizeof(clinfo1), (BYTE*)&clinfo1);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // �𺴰� ����.
			// param1 == ���� ����.
			// param2 == ������ ����ũ.
			// param3 == ������ �ִ� ����ġ.
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];
			
			if(pclchar)
			{
				// PCK - ������ ������ ����� �α� �߰���.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM,
									INPUTITEMPERSON_OPTION_DAILYQUEST, pclchar, NULL, 0, 0, 0, &pclMsg->clRewardItem, 0, 0, 0, 0, 0, 
									0, pclMsg->siInventoryItemIndex, 0, 0, 0, 0, NULL, NULL);

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST_END, 
									0, pclchar, NULL, 0, pclMsg->siAddMoney, pclchar->pclCI->clIP.GetMoney(), NULL, 0, 0, 0, 0, 0, 0, 
									pclMsg->uiSuccess, pclMsg->clRewardItem.siUnique, pclMsg->siExp, 0, 0, NULL, NULL);
			}
		}

		// ����Ʈ�� ����Ǿ����Ƿ�, �ʱ�ȭ �� ��� ��.
		pclCM->CR[id]->pclCI->clDailyQuestInfo.Init();
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUESTCHANGE( sPacketHeader* pPacket)
{
	sDBResponse_DailyQuestChange * pclMsg = (sDBResponse_DailyQuestChange*)pPacket;

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siResult == 1 )
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // ��(�𺴰�) ����Ʈ ����.
			// param1 == �����ð�. 
			// param2 == ���� ��� �׿���. 
			// param3 == ���� ī�ε�
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST_CHANGE, 
								0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								pclMsg->siLeftTime, pclMsg->siKillMonsterNum, pclMsg->siMonsterKind, 0, 0, NULL, NULL);
		}
	}

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if ( pclMsg->siPersonID < 1 || pclMsg->siCharID < 1 )
	{
		return;
	}

	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		pclCM->CR[id]->pclCI->clDailyQuestInfo.siKillMonsterNum = pclMsg->siKillMonsterNum;
		pclCM->CR[id]->pclCI->clDailyQuestInfo.siLeftTime =	pclMsg->siLeftTime;
		
		cltGameMsgResponse_DailyQuestChange clinfo( pclMsg->siLeftTime, pclMsg->siKillMonsterNum );
		cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUESTCHANGE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}

	return;
}