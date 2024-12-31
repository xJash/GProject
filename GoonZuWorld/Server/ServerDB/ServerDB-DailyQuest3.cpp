
#include "Char\CharManager\CharManager.h"


//---------------------------------------
// Server
//---------------------------------------
#include "..\Server\Server.h"
#include "..\Server\Statistics\Statistics.h"

//--------------------------------------
// CommonLogic
//--------------------------------------
#include "..\CommonLogic\Msg\MsgType-DailyQuest3.h"
#include "..\CommonLogic\MsgType-Person.h"

//---------------------------------------
// DBManager
//---------------------------------------
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest3.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Guild.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"


void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUEST3ADD( sPacketHeader* pPacket)
{
	sDBResponse_DailyQuest3Add * pclMsg = (sDBResponse_DailyQuest3Add*)pPacket;

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
			// param5 == ���� ����Ʈ ����.
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST3_ADD, 
								0, pclchar, NULL, 0, pclMsg->siFee, pclMsg->siLeftMoney, NULL, 0, pclMsg->siItemUnique, 0, 0, 0, 0, 
								pclMsg->siItemNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardExp, pclMsg->bHiddenQuest, NULL,NULL);
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

	pclDailyQuest3Mgr->InitQuest3ListData( pclMsg->siQuestListIndex, pclMsg->siItemUnique, 
		pclMsg->siItemNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, 
		pclMsg->siFee, pclMsg->siLeftTime,/* pclMsg->siGuildPoint, */pclMsg->siRewardExp, pclMsg->bHiddenQuest);//, pclMsg->bPCRoomQuest );

	// ����Ʈ ����ڰ� �����ϴ� ��� 
	if ( pclCM->IsValidID(id) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{		
		//pclDailyQuestMgr->Set( pclMsg->siMonsterKind, pclMsg->siMonsterNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum, pclMsg->siRewardExp, pclMsg->siFee, pclMsg->siLeftTime, 0 );
		pclCM->CR[id]->pclCI->clDailyQuest3Info.Set( pclMsg->siItemUnique, pclMsg->siItemNum, pclMsg->siRewardItemUnique, pclMsg->siRewardItemNum,pclMsg->siRewardExp, pclMsg->siFee, pclMsg->siQuestTime, pclMsg->siLeftTime, 0, pclMsg->bMoneySelected, pclMsg->bHiddenQuest );
		pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siLeftMoney );
	
		cltGameMsgResponse_DailyQuest3Select clinfo( &pclCM->CR[id]->pclCI->clDailyQuest3Info, pclMsg->siLeftMoney );
		cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3SELECT, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUEST3DEL( sPacketHeader* pPacket)
{

	sDBResponse_DailyQuest3Del * pclMsg = (sDBResponse_DailyQuest3Del*)pPacket;

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
			//���� ������ ������ ��ų���� ��.
			SI32 ref = pclItemManager->FindItemRefFromUnique(pclMsg->siItemUnique);
			SI32 skillunique = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkill;
			pclChar->SetSkillUpdate(skillunique,pclMsg->siExp);			
			//// ����ġ ������Ʈ
			//pclChar->IncreaseExp( pclMsg->siExp );					
			//��� ����Ʈ ���.
			SI32 addGP = 0;
			SI32 guildUnique = pclChar->pclCI->clBI.clGuildRank.GetGuildUnitIndex();
			// ���� ����Ʈ �ϼ�,.
			if ( pclMsg->bHiddenQuest == true )
			{
				if (guildUnique > 0) 
				{
					addGP = (pclMsg->siExp*25 / 100) * 2;
					if ( addGP > 0 )
					{	//���ڸ� �ְ� ��� ����Ʈ�� ��
						pclChar->GiveItem(ITEMUNIQUE(13321),1, INPUTITEMPERSON_OPTION_QUEST,0);
						sDBRequest_Guild_ChangeGuildPoint clMsg(guildUnique, pclChar->pclCI->GetPersonID(), addGP, TYPE_GUILDPOINT_DAILYQUEST2 );
						pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
					}
					else{
					}
				}
				else
					{
						//��尡 ������ �������Ʈ�� ���� �ʰ� ���ڸ� �ش�
						pclChar->GiveItem(ITEMUNIQUE(13321),1, INPUTITEMPERSON_OPTION_QUEST,0);

					}
			}
			// ���� ����Ʈ�� �ƴ϶�� ��� ����Ʈ�� �ش�.
			// ��� �� ������ �׳� �н�
			else{
				if (guildUnique > 0) {
					addGP = pclMsg->siExp* 25 / 100;
					if ( addGP > 0 )
					{
						sDBRequest_Guild_ChangeGuildPoint clMsg(guildUnique, pclChar->pclCI->GetPersonID(), addGP, TYPE_GUILDPOINT_DAILYQUEST2 );
						pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
					}
				}				
				else
				{

				}

			}
			// ������ ������Ʈ		
			cltGameMsgResponse_DailyQuest3End clinfo1( pclMsg->uiSuccess, pclChar->pclCI->clIP.GetCurExp(), // SI32->SI64 ����ġ �����÷ο춧���� ����
				pclMsg->siInventoryItemIndex, pclMsg->siChangedItemNum, &pclMsg->clInventoryItem, 
				pclMsg->siAddMoney, pclMsg->siExp,addGP,pclMsg->bHiddenQuest); 
			cltMsg clMsg1(GAMEMSG_RESPONSE_DAILYQUEST3END, sizeof(clinfo1), (BYTE*)&clinfo1);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

			pclCM->CR[id]->pclCI->clDailyQuest3Info.Init();//���ϸ� ����Ʈ ������ ���� ������.

			// �𺴰� ����Ʈ Ŭ�������. 
			//pclStatisticsManager->clDailyStatistics.siDailyQuestClearNum++;
		}
		else
		{
			cltItem clItem;
			clItem.Init();
			cltGameMsgResponse_DailyQuest3End clinfo1( pclMsg->uiSuccess, pclCM->CR[id]->pclCI->clIP.GetCurExp(),// SI32->SI64 ����ġ �����÷ο춧���� ����
				0, 0, &clItem, 0,0,0,false );
			cltMsg clMsg1(GAMEMSG_RESPONSE_DAILYQUEST3END, sizeof(clinfo1), (BYTE*)&clinfo1);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
			pclCM->CR[id]->pclCI->clDailyQuest3Info.Init();//���ϸ� ����Ʈ ������ ���� ������.
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
									INPUTITEMPERSON_OPTION_DAILYQUEST3, pclchar, NULL, 0, 0, 0, &pclMsg->clRewardItem, 0, 0, 0, 0, 0, 
									pclMsg->siInventoryItemIndex, 0, 0, 0, 0, 0, NULL, NULL);

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST3_END, 
									0, pclchar, NULL, 0, pclMsg->siAddMoney, pclchar->pclCI->clIP.GetMoney(), NULL, 0, 0, 0, 0, 0, 0, 
									pclMsg->uiSuccess, pclMsg->clRewardItem.siUnique, pclMsg->siExp, 0, 0, NULL, NULL);
			}
		}

		// ����Ʈ�� ����Ǿ����Ƿ�, �ʱ�ȭ �� ��� ��.
		pclCM->CR[id]->pclCI->clDailyQuest3Info.Init();
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_DAILYQUEST3CHANGE( sPacketHeader* pPacket)
{
	sDBResponse_DailyQuest3Change * pclMsg = (sDBResponse_DailyQuest3Change*)pPacket;

	SI32 id = pclMsg->siCharID;

	if ( pclMsg->siResult == 1 )
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 8] // ��(�𺴰�) ����Ʈ ����.
			// param1 == �����ð�. 
			// param2 == ���� ������. 

			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_DAILY_QUEST3_CHANGE, 
								0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								pclMsg->siLeftTime, pclMsg->siMakedItem, 0, 0, 0, NULL, NULL);
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
		pclCM->CR[id]->pclCI->clDailyQuest3Info.siMadeItemNum = pclMsg->siMakedItem;
		pclCM->CR[id]->pclCI->clDailyQuest3Info.siLeftTime =	pclMsg->siLeftTime;
		pclCM->CR[id]->pclCI->clDailyQuest3Info.siLeftTime =	pclMsg->bHiddenQuest;
		
		cltGameMsgResponse_DailyQuest3Change clinfo( pclMsg->siLeftTime, pclMsg->siMakedItem, pclMsg->bHiddenQuest );
		cltMsg clMsg(GAMEMSG_RESPONSE_DAILYQUEST3CHANGE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
	}

	return;
}
