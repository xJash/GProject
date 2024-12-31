#include "..\Common\CommonHeader.h"
#include "..\..\Client\Client.h"
#include "Char\CharServer\Char-Server.h"

//--------------------------
// Common
//-------------------------
#include "PersonInfo.h"
#include "..\CharManager\CharManager.h"
#include "..\Common\Bullet\Bullet.h"

#include "Util\Util.h"

//------------------------
// CommonLogic 
//------------------------
#include "..\CommonLogic\Msg\MsgType-Summon.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "..\Server\Server.h"

extern cltCommonLogic* pclClient;

// InnerStatus를 이웃과 자기자신에게 통보한다. 
bool cltCharServer::SendInnerStatusToNeighbour()
{
	cltGameMsgResponse_InnerStatus clinfo(GetCharUnique(), &clInnerStatus);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_INNERSTATUS, sizeof(clinfo), (BYTE*)&clinfo);

	SendNeighbourMsg(&clMsg, true);

	return true;
}

BOOL cltCharServer::SendChangedDataToClient()
{

	// 기본 정보를 업데이트 해야 한다. 
	if(clUpdateInfo[UPDATE_BASICINFO].bMode == true)
	{
		bool bmode = false;
		if(clUpdateInfo[UPDATE_BASICINFO].siPara1 == 1)
		{
			bmode = true;
		}
		else
		{
			bmode = false;
		}

		// 피격당한 적의 정보를 업데이트 한다. 
		pclClient->SendCharUpdate(CharUnique, bmode);

		clUpdateInfo[UPDATE_BASICINFO].Init();
		
		
	}
	
	// ImportantParameta 를 업데이트 한다. 
	if(clUpdateInfo[UPDATE_IP].bMode == true)
	{
		clUpdateInfo[UPDATE_IP].Init();

		cltGameMsgResponse_IP clinfo(GetCharUnique(), &pclCI->clIP);
		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_IP, sizeof(clinfo), (BYTE*)&clinfo );
		SendNetMsg((sPacketHeader*)&clResMsg);
		
		//==================================================
		// 소환수의 Udate된 정보는 소유주에게 전달한다.
		//==================================================
		if(clIdentity.siIdentity == IDENTITY_PERSON_SUMMON)
		{
			SI32 siParentID = GetSummonParentID();
			if(	pclCM->IsValidID(siParentID))
			{
				// 자신의 정보를 소유주에게 Update하고 수유주에게 정보를 전달한다.
				// 자신의 Index 정보를 알아야한다.
				cltSummon *pclSummon = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSummon(GetSummonIndex() );
				if(pclSummon)
				{
					pclSummon->clIP.Set(&pclCI->clIP);
					cltGameMsgResponse_Summon clInfo(pclCM->CR[siParentID]->GetCharUnique(), GetSummonIndex(), pclSummon);
					cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
					pclCM->CR[siParentID]->SendNetMsg((sPacketHeader*)&clMsg);					

					cltSimpleSummon *pclSimpleSummon = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSimpleSummonFromSummonID(pclSummon->siSummonID);
					SI32 siSlotIndex = pclCM->CR[siParentID]->pclCI->clSummonInfo.GetSummonBaseIndexFromSummonID(pclSummon->siSummonID);
					if(pclSimpleSummon)
					{
						pclSimpleSummon->siLevel = pclCI->clIP.siLevel;

						cltGameMsgResponse_BaseSummon clInfo(pclCM->CR[siParentID]->GetCharUnique(), siSlotIndex, pclSimpleSummon);
						cltMsg clMsg(GAMEMSG_RESPONSE_BASESUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
						pclCM->CR[siParentID]->SendNetMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}
	}

	// Health 를 업데이트 한다. 
	if(clUpdateInfo[UPDATE_HEALTH].bMode == true)
	{
		clUpdateInfo[UPDATE_HEALTH].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_HEALTH, sizeof(pclCI->clHealthInfo), 
														(BYTE*)&(pclCI->clHealthInfo) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}
	
	if(clUpdateInfo[UPDATE_SKILL].bMode == true)
	{
		clUpdateInfo[UPDATE_SKILL].Init();

		// 요청 받은 캐릭터의 SkillData를 보내준다.
		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_SKILL, 
			sizeof(cltPSkillInfo), (BYTE*)&pclCI->clCharSkill);
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}


	if(clUpdateInfo[UPDATE_INVENTORY].bMode	 == true)
	{
		clUpdateInfo[UPDATE_INVENTORY].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_ALLITEM, sizeof(cltPItemInfo),	(BYTE*)&pclCI->clCharItem);
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}

	if(clUpdateInfo[UPDATE_BANK].bMode	 == true)
	{
		clUpdateInfo[UPDATE_BANK].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_BANK, sizeof(cltBankAccount), 
			(BYTE*)&(pclCI->clBank) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}

	if(clUpdateInfo[UPDATE_STOCK].bMode	 == true)
	{
		clUpdateInfo[UPDATE_STOCK].Init() ;

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_STOCK, sizeof(cltStockAccount), 
			(BYTE*)&(pclCI->clStock.clInfo) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);

	}

	if(clUpdateInfo[UPDATE_STOCKORDER].bMode	 == true)
	{
		clUpdateInfo[UPDATE_STOCKORDER].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_STOCKORDER, sizeof(cltCharOrderInfo), 
			(BYTE*)&(pclCI->clStock.clOrderInfo) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}

	//_LEON_GUILD_STOCK
	if(clUpdateInfo[UPDATE_GUILDSTOCK].bMode == true)
	{
		clUpdateInfo[UPDATE_GUILDSTOCK].Init();

/*		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_GUILDSTOCK, sizeof(cltGuildStockAccount),
			(BYTE*)&(pclCI->clGuildStock.clInfo) );

		SendNetMsg((sPacketHeader*)&clResMsg);*/
	}

	//_LEON_GUILD_STOCK
	if(clUpdateInfo[UPDATE_GUILDSTOCKORDER].bMode == true)
	{
		clUpdateInfo[UPDATE_GUILDSTOCKORDER].Init();

/*		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_GUILDSTOCKORDER, sizeof(cltGuildCharOrderInfo),
			(BYTE*)&(pclCI->clGuildStock.clOrderInfo) );

		SendNetMsg((sPacketHeader*)&clResMsg);*/
	}

	if(clUpdateInfo[UPDATE_WORLDMONEY].bMode == true)
	{
		clUpdateInfo[UPDATE_WORLDMONEY].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_WORLDMONEY, sizeof(cltWorldMoneyAccount),
			(BYTE*)&(pclCI->clWorldMoney) );

		SendNetMsg((sPacketHeader*)&clResMsg);
	}


	if(clUpdateInfo[UPDATE_MARKET].bMode	 == true)
	{
		clUpdateInfo[UPDATE_MARKET].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_MARKET, sizeof(cltMarketAccount), 
			(BYTE*)&(pclCI->clMarket.clInfo) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);

	}

	if(clUpdateInfo[UPDATE_RANK].bMode	 == true)
	{
		clUpdateInfo[UPDATE_RANK].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_RANK, sizeof(cltSimpleRank), 
			(BYTE*)&(pclCI->clCharRank) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);

	}

	if(clUpdateInfo[UPDATE_REALESTATE].bMode	 == true)
	{
		clUpdateInfo[UPDATE_REALESTATE].Init();

		cltMsg clMsg(GAMEMSG_RESPONSE_REALESTATE, sizeof(cltCharRealEstate), 
			(BYTE*)&(pclCI->clRealEstate) );
		
		SendNetMsg((sPacketHeader*)&clMsg);

	}

	if(clUpdateInfo[UPDATE_QUEST].bMode	 == true)
	{
		clUpdateInfo[UPDATE_QUEST].Init();

		cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_QUEST, sizeof(cltPQuestInfo), (BYTE*)&(pclCI->clQuestInfo) );
		SendNetMsg((sPacketHeader*)&clMsg);
	}
	
	if(clUpdateInfo[UPDATE_HORSE].bMode	 == true)
	{
		clUpdateInfo[UPDATE_HORSE].Init();

		cltPersonHorseInfo clhorseinfo;
		clhorseinfo.Set(&pclCI->clHorseInfo);

		cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_HORSE, sizeof(cltPersonHorseInfo), (BYTE*)&clhorseinfo );
		SendNetMsg((sPacketHeader*)&clMsg);
	}

	if(clUpdateInfo[UPDATE_SUMMON].bMode	 == true)
	{
		clUpdateInfo[UPDATE_SUMMON].Init();

		// 나와 있는 소환수의 정보를 Update 시킨다.
		UpdateTakeOutSummon();

		for (SI32 i = 0 ; i < MAX_SUMMON_OWN; i++)
		{
			SI32 summonidex = i;

			cltSummon *pclSummon = pclCI->clSummonInfo.GetSummon(summonidex);
			
			if(pclSummon && _tcscmp(pclSummon->szName, TEXT("")) != 0)
			{
				cltGameMsgResponse_Summon clInfo(GetCharUnique(), summonidex, pclSummon);
				cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
				SendNetMsg((sPacketHeader*)&clMsg);
			}
		}

		//SI32 summonid = GetSummonID();
		//if(summonid)
		//{
		//	SI32 summonidex = pclCM->CR[summonid]->GetSummonIndex();

		//	cltSummon *pclSummon = pclCI->clSummonInfo.GetSummon(summonidex);
		//	if(pclSummon)
		//	{
		//		cltGameMsgResponse_Summon clInfo(GetCharUnique(), pclSummon);
		//		cltMsg clMsg(GAMEMSG_RESPONSE_SUMMONINFO, sizeof(clInfo), (BYTE*)&clInfo);
		//		SendNetMsg((sPacketHeader*)&clMsg);
		//	}

		//}

	}

	if(clUpdateInfo[UPDATE_GUILTY].bMode	 == true)
	{
		clUpdateInfo[UPDATE_GUILTY].Init();

		cltMsg clResMsg(GAMEMSG_RESPONSE_PERSON_GUILTY, sizeof(cltGuiltyInfo), 
			(BYTE*)&(pclCI->clGuiltyInfo) );
		
		SendNetMsg((sPacketHeader*)&clResMsg);
	}
	
	return TRUE;
}