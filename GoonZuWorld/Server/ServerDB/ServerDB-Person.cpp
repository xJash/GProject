//---------------------------------
// 2003/8/6 김태곤
//---------------------------------
// APEX- 
#include "../../Apex/ApexGoonZu.h"
// -APEX

#include "../../Common/CommonHeader.h"
#include "../../Server/Server.h"

#include "../../../NLib/NUtil.h"
#include "../../../NLib/NTCHARString.h"

#include "../Common/Map/Map.h"
#include "../Common/Father/Father.h"
#include "../Common/VoteMgr/VoteMgr.h"
#include "../Common/Skill/Skill-Manager.h"
#include "Char/CharManager/CharManager.h"
#include "../Common/Order/Order.h"
#include "../common/GameEvent/GameEvent.h"
#include "../common/Item/ItemCommon/cltSetItem.h"

#include "../CommonLogic/Feast/Feast.h"

#include "Guild/Guild.h"

#include "MsgRval-Define.h"
#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "MsgType-Horse.h"
#include "Msg/MsgType-Vote.h"
#include "Msg/MsgType-Friend.h"
#include "Msg/MsgType-Summon.h"
#include "Msg/MsgType-Village.h"
#include "Msg/MsgType-ItemMall.h"
#include "Msg/MsgType-npc.h"
#include "MsgType-Structure.h"
#include "Msg/MsgType-Web.h"
#include "Msg/MsgType-NamingQuest.h"


#include "MsgType-Item.h"
#include "MsgType-Guild.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Family.h"

//-----------------------------------------
// Server
//-----------------------------------------
#include "../Server/Statistics/Statistics.h"
#include "../Server/Minister/Minister-yezo.h"
#include "../Server/Minister/MinisterMgr.h"
#include "../Server/ServerReward/ServerReward.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Stock.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Summon.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Cityhall.h"
#include "../../DBManager/GameDBManager_World/DBMsg-item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PostOffice.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Agriculture.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Friend.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"
#include "../../DBManager/GameDBManager_World/DBMsg-SoulGuard.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "../Notice/Notice.h"
#include "HashTable/HashTable_StringInt.h"
#include "HashTable/HashTable_IntInt.h"

#include "../../Server/AuthServer/AuthMsg.h"

#include "NDate.h"


#include "../../../NLib/NUtil.h"
#include "../../Lib/MD5/md5.h"

#include "../../CommonLogic/Msg/MsgType-HappyBeanQuest.h"

#include "../../common/VoteMgr/VoteBaseInfo.h"


// 스테이터스 초기화 
void cltServer::DoMsg_DBMSG_RESPONSE_INITSTATUS(sPacketHeader* pPacket)
{
	sDBResponse_InitStatus* pclinfo = (sDBResponse_InitStatus*)pPacket;

	if(pclinfo->siResult == 0)
	{
		return ;
	}

	SI32 id = pclinfo->usCharID;
	if(id <= 0)return ;
	if(pclCM->IsValidID(id) == false)		return;

	// 스테이터스를 초기화 한다. 
	pclCM->CR[id]->pclCI->clIP.SetStr(5);
	pclCM->CR[id]->pclCI->clIP.SetDex(5);
	pclCM->CR[id]->pclCI->clIP.SetVit(5);
	pclCM->CR[id]->pclCI->clIP.SetHnd(5);
	pclCM->CR[id]->pclCI->clIP.SetMag(5);
	pclCM->CR[id]->pclCI->clIP.SetLuk(5);
	pclCM->CR[id]->pclCI->clIP.SetWis(5);
	pclCM->CR[id]->pclCI->clIP.SetBonus( pclCM->CR[id]->pclCI->clIP.GetLevel() * 5);

	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

	// 캐릭터를 안정하게 경복궁으로 워프시킨다. 
	OrderStop(id, BY_COMPUTER);

	//if ( siServiceArea == ConstServiceArea_China )
	//{
	//	cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);
	//	pclCM->CR[id]->SetWarpInfo(&clWarpInfo, 1900);
	//}
	//else
	//{
	//	if ( pclCM->CR[id]->pclKI->siDefaultCountry == ConstServiceArea_China )
	//	{
	//		cltWarpInfo clWarpInfo(1, MAPINDEX_CHINABORDER, false, false, 17, 19, -1, -1);
	//		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, 1900);
	//	}
	//	else
	//	{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);
			pclCM->CR[id]->SetWarpInfo(&clWarpInfo, 1900);
		//}
	//}
	
	// 이용권을 이용해서 초기화한 경우, 
	if( pclinfo->siMode == INITSTATUSMODE_TICKET || 
		pclinfo->siMode == INITSTATUSMODE_CHINA_EVENTTICKET )
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemPos].Set(&pclinfo->clItem);

		// 클라이언트로 업데이트 된 정보를 보낸다. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclinfo->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// 통계를 낸다. 
		
		if( INITSTATUSMODE_CHINA_EVENTTICKET == pclinfo->siMode )
			pclItemManager->AddUseNum(ITEMUNIQUE(24031), 1);

			// 새로운 통계
			//NStatistics_Add("Item", ITEMUNIQUE(24031), "UseNum", 1);

		else
			pclItemManager->AddUseNum(ITEMUNIQUE(24030), 1);

			// 새로운 통계
			//NStatistics_Add("Item", ITEMUNIQUE(24030), "UseNum", 1);
	}

	cltServer* pclserver = (cltServer*)pclClient;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// PCK - 아이템사용을 할땐 아이템 사용 로그도 같이 남겨준다.
		SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
										USEITEM_REASON_INITSTATUSMODE_TICKET, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclinfo->clItem_Log, pclinfo->clItem.GetItemNum(), 
										0, 0, 0, 0, 0, 
										pclinfo->siItemPos, 0, 0, 0, 0, NULL, NULL);

		// [로그추가 : 황진성 2007. 10. 15] // 상태 초기화. (능력을 모두 5로 초기화 할때.)
		// parma1 == 아이템 유니크
		SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_INITSTATUS,
								pclinfo->siMode, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								pclinfo->clItem_Log.siUnique, 0, 0, 0, 0, NULL, NULL);
	}

	// 클라이언트에 사실을 알린다. 
	SendServerResponseMsg(0, SRVAL_INITSTATUS,  pclinfo->siMode, 0, pclCM->CR[id]->GetCharUnique());
	
}

// 제자 리스트 통보. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETCHILDLIST(sPacketHeader* pPacket)
{
	sDBResponse_GetChildList* pclinfo = (sDBResponse_GetChildList*)pPacket;

	if(pclinfo->siResult == 0)
	{
		return ;
	}
	
	SI32 id = pclinfo->usCharID;
	if(id <= 0)return ;
	

	// 클라이언트로 통보한다. 
	cltGameMsgResponse_UpdateChildList clinfo(pclinfo->usCharID, pclinfo->clChildInfo);
	cltMsg clMsg(GAMEMSG_RESPONSE_UPDATECHILDLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

// 제자 양성 성공수 증가  통보. 
void cltServer::DoMsg_DBMSG_RESPONSE_INCREASECHILDNUMBER(sPacketHeader* pPacket)
{
	sDBResponse_IncreaseChildNumber* pclinfo = (sDBResponse_IncreaseChildNumber*)pPacket;

	if(pclinfo->siResult == 0)
	{
		return ;
	}

	SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
	if(pclCM->IsValidID(id))
	{
		// 클라이언트로 통보한다. 
		cltGameMsgResponse_ChildInfo clinfo(id, pclinfo->siChildNumber);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHILDINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// Person 간단 정보 요청. 
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONSIMPLEINFO(sPacketHeader* pPacket)
{
	sDBResponse_PersonSimpleInfo* pclinfo = (sDBResponse_PersonSimpleInfo*)pPacket;

	if(pclinfo->siResult == 0)
	{
		return ;
	}

	SI32 id = pclinfo->usCharID;

	if( false == pclCM->IsValidID(id) )
		return;

	// 스승 정보를 얻어온 것이라면, 
	if(pclinfo->siReason == PERSONSIMPLEINFO_REASON_FATHERREWARD)
	{

		//KHY - 0611 - 스승제자 S 추가수정.
		if ( ConstServiceArea_Japan != pclClient->siServiceArea )
		{
			// 향상 시킨 레벨 
			SI32 inclevel = max(0, NEWFATHER_LEVEL - pclCM->CR[id]->pclCI->clBI.clFatherInfo.siMyLevelForFather);
			GMONEY money		= pclinfo->siLevel * min(pclItemManager->clItemStatistic.siNPCPriceRate * 100,	(inclevel * 200));
		
			SI32 teacherID = pclCM->GetIDFromPersonID(pclCM->CR[id]->pclCI->clBI.clFatherInfo.clFather.GetPersonID());
			// 접속해 있을경우 피로방지 시스템 적용
			if ( pclCM->IsValidID( teacherID) )
			{
				money = ((cltCharServer*)pclCM->CR[teacherID])->CalcTiredPoint( money );
			}

			// 쪽지를 DB나 클라이언트에게 보낸다. 
			cltLetterMsg_ChildLevelUp clletter( inclevel, (TCHAR*)pclCM->CR[id]->GetName(), money, 0, cltLetterMsg_ChildLevelUp::FATHERREWARD );
			SendLetterMsg(pclinfo->siPersonID, (cltLetterHeader*)&clletter);

			// 스승에게  포상 지금을 요청. 
			{
				sDBRequest_ChangeMoney clMsg( teacherID, pclinfo->siPersonID, CHANGE_MONEY_REASON_FATHERREWARD, money );
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);


				// 통화량을 집계한다. 
				cltMoney clmoney;
				clmoney.Set(money);
				clCurrencyInfo.clInputMoney_Father.Increase(&clmoney);

				pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_FATHER, money);
			}

			money = ( inclevel * 100 ) * NEWFATHER_LEVEL;

			// 피로방지 시스템 적용
			GMONEY givemoney = ((cltCharServer*)pclCM->CR[id])->CalcTiredPoint(money);

			cltLetterMsg_ChildLevelUp clletter3( inclevel, (TCHAR*)pclCM->CR[id]->GetName(), givemoney, 0, cltLetterMsg_ChildLevelUp::PUPILREWARD );
			SendLetterMsg(pclCM->CR[id]->pclCI->GetPersonID(), (cltLetterHeader*)&clletter3);
			// 제자에게  포상 지금을 요청. 
			{

				sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_PUPILREWARD, givemoney );
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				// 통화량을 집계한다. 
				cltMoney clmoney;
				clmoney.Set(givemoney);
				clCurrencyInfo.clInputMoney_Father.Increase(&clmoney);

				pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_FATHER, givemoney);
			}

			SI32 grandTeacherID = pclCM->GetIDFromPersonID( pclinfo->siGrandPersonID );
			// 스승의 스승은 10%만 받는다.
			givemoney = money / 10;

			// 접속해 있을경우 피로방지 시스템 적용
			if ( pclCM->IsValidID( grandTeacherID) )
			{
				givemoney = ((cltCharServer*)pclCM->CR[grandTeacherID])->CalcTiredPoint( givemoney );
			}
			
			cltLetterMsg_ChildLevelUp clletter2( inclevel, (TCHAR*)pclCM->CR[id]->GetName(), givemoney, 0, cltLetterMsg_ChildLevelUp::GRANDFATHERREWARD );
			SendLetterMsg( pclinfo->siGrandPersonID, (cltLetterHeader*)&clletter2);

			// 스승의 스승에게  포상 지금을 요청. 
			{
				sDBRequest_ChangeMoney clMsg( grandTeacherID, pclinfo->siGrandPersonID, CHANGE_MONEY_REASON_GRANDFATHERREWARD, givemoney );
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				// 통화량을 집계한다. 
				cltMoney clmoney;
				clmoney.Set(givemoney);
				clCurrencyInfo.clInputMoney_Father.Increase(&clmoney);

				pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_FATHER, givemoney);
			}
		}
		else
		{
			// 향상 시킨 레벨 
			SI32 inclevel = max(0, FATHER_LEVEL - pclCM->CR[id]->pclCI->clBI.clFatherInfo.siMyLevelForFather);

			SI32 money		= pclinfo->siLevel * min(2000,	(inclevel * 200));
			//SI32 exp		= pclinfo->siLevel * min(100,	(inclevel * 10));
			SI32 fameexp	= max(5, inclevel * 3);							// 명성 경험치 획득. 

			// 쪽지를 DB나 클라이언트에게 보낸다. 
			cltLetterMsg_ChildLevelUp clletter(inclevel, (TCHAR*)pclCM->CR[id]->GetName(), money, fameexp);
			SendLetterMsg(pclinfo->siPersonID, (cltLetterHeader*)&clletter);

			// 포상 지금을 요청. 
			{
				sDBRequest_ChangeMoney clMsg(id, pclinfo->siPersonID, CHANGE_MONEY_REASON_FATHERREWARD, money);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				// 통화량을 집계한다. 
				cltMoney clmoney;
				clmoney.Set(money);
				clCurrencyInfo.clInputMoney_Father.Increase(&clmoney);

				pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_FATHER, money);

			}

			// 경험치 지급을 요청. 
			// 사용자의 접속 여부와 관계없이 경험치를 준다.
			//pclCM->IncExp(pclinfo->siPersonID, exp, CHANGE_EXP_REASON_FATHER);

			// 명성 경험치를 줄 것을 요청. 
			// 사용자의 접속 여부와 관계없이 경험치를 준다.
			pclCM->IncFameExp(pclinfo->siPersonID, fameexp, GETEXP_REASON_FAMEFATHER, CHANGE_FAMEEXP_REASON_FATHER);

			/*		// 스승 양성 성공을 요청. 
			{
			sDBRequest_IncreaseChildNumber clMsg(pclinfo->siPersonID, 1);
			SendDBMsg((sPacketHeader *)&clMsg);
			}
			*/		
		}
	}
	else if( pclinfo->siReason == PERSONSIMPLEINFO_REASON_PROMOTER_INFO )
	{
		cltCharServer* pclchar = pclCM->GetCharServer( pclinfo->usCharID );
		pclchar->pclCI->clBI.clRecommenderInfo.siPersonID = pclinfo->siPersonID;

		cltGameResponse_Promoter_Info_Get clinfo( pclinfo->siPersonID, pclinfo->siCharKind, pclinfo->siLevel, pclchar->bCellularPhoneAuth, pclinfo->szGetCharInfoName );
		cltMsg clMsg(GAMEMSG_RESPONSE_PROMOTER_INFO_GET, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if( pclinfo->siPersonID )
		{
			bool bResult = true;
			// 기존에 목록에 있는지 체크
			cltSimplePerson* pSimplePersonInfo = NULL;
			for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
			{
				pSimplePersonInfo = &pclchar->pclFriendInfo->clFriend[i];

				if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
				{
					if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclinfo->szGetCharInfoName ) == 0 )
					{
						// 친구 목록에 있으므로 추가할 필요 없음.
						bResult = false;
						break;
					}
				}
			}

			if( bResult )
			{
				sDBRequest_FriendAddList clMsg(	0, pclinfo->siPersonID, pclCM->GetIDFromPersonID(pclinfo->siPersonID), pclinfo->szGetCharInfoName, 
												0, pclchar->pclCI->GetPersonID(), (SI32)pclinfo->usCharID, (TCHAR*)pclchar->GetName() );

				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
	}
	// 추천인이 피추천인에게 인사말.(추천인의 정보를 받아왔다.)
	else if( pclinfo->siReason == PERSONSIMPLEINFO_REASON_RECOMMEND_INTRODUCE )
	{
		bool bConnect = false;
		// 추천인의 ID
		SI32 siID = pclCM->GetIDFromName( pclinfo->szGetCharInfoName );
		cltCharServer* pclRecommendChar = pclCM->GetCharServer( siID );
		if( pclRecommendChar )
		{
			bConnect = true;
		}

		// 피추천인 ID
		siID = pclCM->GetIDFromName( pclinfo->szCharInfoName );
		cltCharServer* pclRecommendeeChar = pclCM->GetCharServer( siID );
		if( pclRecommendeeChar )
		{
			cltGameResponse_Recommend_Introduce clInfo( pclinfo->szGetCharInfoName, pclinfo->siCharKind, bConnect );
			cltMsg clMsg(GAMEMSG_RESPONSE_RECOMMEND_INTRODUCE, sizeof(clInfo), (BYTE*)&clInfo);
			pclRecommendeeChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	// 피추천인이 추천인에게 인사말.(추천인의 정보를 받아왔다.)
	else if( pclinfo->siReason == PERSONSIMPLEINFO_REASON_RECOMMENDEE_INTRODUCE )
	{
		bool bConnect = false;
		// 피추천인의 ID
		SI32 siID = pclCM->GetIDFromName( pclinfo->szGetCharInfoName );
		cltCharServer* pclRecommendeeChar = pclCM->GetCharServer( siID );
		if( pclRecommendeeChar )
		{
			bConnect = true;
		}

		// 추천인 ID
		siID = pclCM->GetIDFromName( pclinfo->szCharInfoName );
		cltCharServer* pclRecommendChar = pclCM->GetCharServer( siID );
		if( pclRecommendChar )
		{
			cltGameResponse_Recommendee_Introduce clInfo( pclinfo->szGetCharInfoName, pclinfo->siCharKind, bConnect );
			cltMsg clMsg(GAMEMSG_RESPONSE_RECOMMENDEE_INTRODUCE, sizeof(clInfo), (BYTE*)&clInfo);
			pclRecommendChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

// 스승 설정/해제 
void cltServer::DoMsg_DBMSG_RESPONSE_SETFATHER(sPacketHeader* pPacket)
{
	sDBResponse_SetFather* pclMsg = (sDBResponse_SetFather*)pPacket;

	SI32 id = pclMsg->usCharID;

	if( false == pclCM->IsValidID(id) )
		return;

	if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)return ;

	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case 1:
		{
			//---------------------------------
			// 스승을 설정한다. 
			//---------------------------------
			SI32 orgfatherid = pclCM->CR[id]->pclCI->clBI.clFatherInfo.clFather.siPersonID;
			SI32 fathercharid = pclCM->GetIDFromPersonID(pclMsg->siFatherPersonID);

			if ( pclCM->IsValidID(fathercharid) )
			{
				pclCM->CR[id]->pclCI->clBI.clFatherInfo.clFather.siPersonID	= pclMsg->siFatherPersonID;
				StringCchCopy(pclCM->CR[id]->pclCI->clBI.clFatherInfo.clFather.szName, MAX_PLAYER_NAME, pclMsg->szFatherName);
				pclCM->CR[id]->pclCI->clBI.clFatherInfo.siMyLevelForFather		= (SI08)pclMsg->siMyLevel;		// 스승 설정 당시의 레벨 
				pclCM->CR[id]->pclCI->clBI.clFatherInfo.siFatherChangeNumber	= (SI08)pclMsg->siChangedFatherNumber;
				StringCchCopy(pclCM->CR[id]->pclCI->clBI.clFatherInfo.szAccountID, MAX_PLAYER_NAME,pclCM->CR[fathercharid]->pclCI->clBI.szAccountID);

				//---------------------------------
				// 클라이언트에 통보한다. 
				//--------------------------------
				cltGameMsgResponse_SetFather clinfo(&pclCM->CR[id]->pclCI->clBI.clFatherInfo.clFather, pclCM->CR[id]->pclCI->clIP.GetLevel(),pclCM->CR[id]->pclCI->clBI.clFatherInfo.szAccountID);
				cltMsg clMsg(GAMEMSG_RESPONSE_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				// 이전스승이 없다면 
				if(!pclMsg->siPrevFatherPersonID)
				{
					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [로그추가 : 황진성 2007. 10. 9] // 스승 등록 로그쓰기. 
						// param1  == 스승 설정 당시의 내 레벨, 
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_SETFATHER, 
											0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->siFatherPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siMyLevel, 0, 0, 0, 0, NULL, NULL);
					}
				}

				//------------------------------------------
				// 이전 스승이 있다면 해임 쪽지를 보낸다. 
				//------------------------------------------
				if(pclMsg->siPrevFatherPersonID)
				{
					cltLetterMsg_Father clletter(false, (TCHAR*)pclCM->CR[id]->GetName());
					// 쪽지를 DB나 클라이언트에게 보낸다. 
					SendLetterMsg(pclMsg->siPrevFatherPersonID, (cltLetterHeader*)&clletter);

					if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
					{
						// [로그추가 : 황진성 2007. 10. 9] // 스승 해지 로그 작성.
						// param1 == 스승이 변경된 횟수
						SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_RENOUNCEFATHER, 
											0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->siPrevFatherPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siChangedFatherNumber, 0, 0, 0, 0, NULL, NULL);
					}
				}

				//-----------------------------------------
				// 임명된 스승에게 임명 쪽지를 보낸다. 
				//-----------------------------------------
				if(orgfatherid != pclCM->CR[pclMsg->usCharID]->pclCI->clBI.clFatherInfo.clFather.siPersonID)
				{
					cltLetterMsg_Father clletter(true, (TCHAR*)pclCM->CR[id]->GetName());
					// 쪽지를 DB나 클라이언트에게 보낸다. 
					SendLetterMsg(pclMsg->siFatherPersonID, (cltLetterHeader*)&clletter);


					SI32 siFatherCharID = pclCM->GetIDFromPersonID( pclMsg->siFatherPersonID );

					if ( pclCM->IsValidID( siFatherCharID ) == true )
					{
						((cltCharServer*)pclCM->CR[siFatherCharID])->DoQuestCheckAndAction(QUEST_CLEAR_COND_TAKEPUPILS);
					}
				}


				// 퀘스트 체크한다.
				((cltCharServer*)pclCM->CR[id])->DoQuestCheckAndAction(QUEST_CLEAR_COND_SETFATHER);

				//KHY - 0611 - 스승제자 S 추가수정.
				if ( ConstServiceArea_Japan != pclClient->siServiceArea )
				{
					// 서로 친구 만들어주기
					sDBRequest_FriendAddList clMsg1( 0, pclMsg->siPersonID, id, (TCHAR*)pclCM->CR[id]->GetName(), 0, pclMsg->siFatherPersonID, fathercharid, pclMsg->szFatherName );
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg1);

					SendServerResponseMsg(0, SRVAL_ACCEPT_SETFATHER,  0, 0, pclCM->CR[id]->GetCharUnique());

					sDBRequest_FriendAddList clMsg2( 0, pclMsg->siFatherPersonID, fathercharid, pclMsg->szFatherName, 0, pclMsg->siPersonID, id, (TCHAR*)pclCM->CR[id]->GetName() );
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg2);
				}
				
				//KHY - 1025 - 나우콤 이벤트 - 기간설정. -경품응모 - 제자달성.
				if (pclClient->IsCountrySwitch(Switch_NowComEvent)) 
				{
					cltServer* pclServer = (cltServer*)pclClient;
					_SYSTEMTIME sStartAEventDay , sEndAEventDay;//이벤트 시작시간과 끝나는 시간로그인 시간.
					cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

					sStartAEventDay.wYear = 2006;
					sStartAEventDay.wMonth = 11;
					sStartAEventDay.wDay = 8;
					sStartAEventDay.wHour = 0;
					sStartAEventDay.wDayOfWeek = 0;
					sStartAEventDay.wMinute = 0;
					sStartAEventDay.wSecond = 0;
					sStartAEventDay.wMilliseconds=0;

					sEndAEventDay.wYear = 2006;
					sEndAEventDay.wMonth = 12;
					sEndAEventDay.wDay = 5;
					sEndAEventDay.wHour = 0;
					sEndAEventDay.wDayOfWeek = 0;
					sEndAEventDay.wMinute = 0;
					sEndAEventDay.wSecond = 0;
					sEndAEventDay.wMilliseconds=0;

					SI32 startAEventdatevary = pclClient->GetMinuteFromsTime(sStartAEventDay);
					SI32 endAEventdatevary = pclClient->GetMinuteFromsTime(sEndAEventDay);
					SI32 LoginTime = pclClient->GetMinuteFromsTime(pclServer->sTime);

					if((LoginTime <= endAEventdatevary)
						&&(LoginTime >= startAEventdatevary))
						//이벤트 기간내에 접속이면 쿠폰발급.
					{
						SendLog_SetEventCouponInfo(pclchar, NOW_COM_EVENT,3); //  -최초 접속.
					}
				}
				
			}
			else returnval = SRVAL_NOFATHERNAME;
		}
		break;
	case -1:	
		returnval = SRVAL_NOFATHERNAME;		
		break;			// 해당하는 스승이 존재하지 않는다. 
	case -2:	
		returnval = SRVAL_SAMEACCOUNT;		
		break;			// 같은 계정끼리는 스승이 될 수 없다. 
	case -4: 
		{
			// 스승 설정 패널티 적용중이다( 하루동안 제자를 받을 수 없다 )
			SI32 fathercharid = pclCM->GetIDFromPersonID(pclMsg->siFatherPersonID);

			if ( pclCM->IsValidID(fathercharid) )
			{
				SendServerResponseMsg(0, SRVAL_PENALTY_SETFATHER_TEACHER,  0, 0, pclCM->CR[fathercharid]->GetCharUnique());
			}
			if( pclCM->IsValidID(id) )
			{
				SendServerResponseMsg(0, SRVAL_PENALTY_SETFATHER_PUPIL,  0, 0, pclCM->CR[id]->GetCharUnique());
			}
		}
		break;
	}

	if(returnval)
	{
		SendServerResponseMsg(0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// 현금을 옮긴다. 
void cltServer::DoMsg_DBMSG_RESPONSE_MOVEMONEY(sPacketHeader* pPacket)
{

	sDBResponse_MoveMoney* pclMsg = (sDBResponse_MoveMoney*)pPacket;

	switch(pclMsg->siResult)
	{
	case -1:		// from의 돈이 부족하다. 
		break;
	case 0:
		break;
	case 1:
		{
			// from의 보유액을 업데이트 한다. 
			if(pclMsg->siFromPersonID)
			{
				SI32 fromid = pclCM->GetIDFromPersonID(pclMsg->siFromPersonID);
				if( pclCM->IsValidID(fromid) )
				{
					pclCM->CR[fromid]->pclCI->clIP.SetMoney(pclMsg->siFromPersonMoney);

					// 클라이언트로 통보한다. 
					if(pclMsg->siMovedMoney)
					{
						SI32 reason = CHANGE_MONEY_REASON_NOTDEFINED;

						cltGameMsgResponse_ChangeMoney clinfo(pclMsg->siFromPersonMoney, -pclMsg->siMovedMoney, reason);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->CR[fromid]->SendNetMsg((sPacketHeader*)&clMsg);
					}

				}
			}

			// to의 보유액을 업데이트 한다. 
			if(pclMsg->siToPersonID)
			{
				SI32 toid = pclCM->GetIDFromPersonID(pclMsg->siToPersonID);
				if( pclCM->IsValidID(toid) )
				{
					pclCM->CR[toid]->pclCI->clIP.SetMoney(pclMsg->siToPersonMoney);

					// 클라이언트로 통보한다. 
					if(pclMsg->siMovedMoney)
					{
						SI32 reason = CHANGE_MONEY_REASON_NOTDEFINED;
						
						cltGameMsgResponse_ChangeMoney clinfo(pclMsg->siToPersonMoney, pclMsg->siMovedMoney, reason);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);
					}

				}

			}

		}
		break;
	}	
}
// 케릭터 게임옵션셋팅
void cltServer::DoMsg_DBMSG_RESPONSE_CHAR_OPTION(sPacketHeader* pPacket)
{
	sDBResponse_Char_Option* pclMsg = (sDBResponse_Char_Option*)pPacket;
	if( pclMsg->siResult == 0 )
	{
		return ;
	}
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return ;
	// 서버에 있는 해당 유저의 채팅 정보를 셋팅 한다.
	pclCM->CR[ id ]->pclCI->clCharOption.Set( &pclMsg->clPCharOptioninfo ) ;

	//if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID) return ;

	cltGameMsgResponse_Char_Option clinfo( pclCM->CR[ id ]->pclCI->clCharOption );
	cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_OPTION, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}
/// 케릭터 게임옵션을 가지고온다
void cltServer::DoMsg_DBMSG_RESPONSE_CHAR_GET_OPTION(sPacketHeader* pPacket)
{
	sDBResponse_Char_Get_Option* pclMsg = ( sDBResponse_Char_Get_Option* )pPacket;

	SI32 id	= pclMsg->siCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	pclCM->CR[id]->pclCI->clCharOption.Set( &pclMsg->clPCharOptioninfo );
	
	// 클라이언트에 정보 전송
	cltGameMsgResponse_Char_Get_Option clinfo;
	clinfo.clCharOptionInfo.Set( &pclCM->CR[id]->pclCI->clCharOption );

	cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_GET_OPTION, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	

}
// 현금액이 변경된다. 
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEMONEY(sPacketHeader* pPacket)
{

	sDBResponse_ChangeMoney* pclMsg = (sDBResponse_ChangeMoney*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return ;

	if(pclCM->CR[id]->pclCI->GetPersonID() != pclMsg->siPersonID)return ;

	// 현금액을 업데이트 한다. 
	pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siMoney);

	// 클라이언트로 통보한다. 
	cltGameMsgResponse_ChangeMoney clinfo(pclMsg->siMoney, pclMsg->siChangedMoney, pclMsg->siReason);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMONEY, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 소지금이 변경되는 내역을 기록(리즌값에따라 다양한 변동)
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_CHANGE_MONEY, 
										pclMsg->siReason, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siTargetPersonID, pclMsg->siChangedMoney, pclMsg->siMoney, NULL, 0, 0, 0, 0, 0, 0, 
										0, 0, 0, 0, 0, NULL, NULL);
	}
}



// 경험치가  변경된다. 
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEEXP(sPacketHeader* pPacket)
{

	sDBResponse_ChangeExp* pclMsg = (sDBResponse_ChangeExp*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 10] // 경험치 변동 내역(직접적인 사냥 이외의 다른 경우에 의한…)
		// param1 == 증감된 경험치
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_EXPCHAMGE,
										pclMsg->siReason, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->siChangedExp, 0, 0, 0, 0, NULL, NULL);
	}
}

// 명성 경험치가  변경된다. 
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEFAMEEXP(sPacketHeader* pPacket)
{

	sDBResponse_ChangeFameExp* pclMsg = (sDBResponse_ChangeFameExp*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 10] // 명성 경험치가  변경.
		// param1 == 증감된 경험치.
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_CHANGEFAMEEXP,
										pclMsg->siReason, 0, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, pclMsg->siFameExp, 
										pclMsg->siChangedFameExp, 0, 0, 0, 0, NULL, NULL);
	}
}

// 퀘스트 저장 결과. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETQUESTINFO(sPacketHeader* pPacket)
{
	// PCK : 로그를 남기위해서 내용추가함.
	// param1 : 퀘스트 타입, param2 : 퀘스트 유니크, param3 : 퀘스트 스텝, param4 : 퀘스트 클리어 조건
	// charparam1 : 퀘스트 클리어여부
	sDBResponse_SetQuestInfo* pclMsg = (sDBResponse_SetQuestInfo*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID) ;
	if ( pclCM->IsValidID(id) == false ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// QuestState를 2진수로 변환
	TCHAR szCharParam1[50] = { '\0', };
	_itoa(pclMsg->clQuestInfo.siQuestState, szCharParam1, 2);
	
	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_INFO_SET,
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
									pclMsg->siQuestType, pclMsg->clQuestInfo.siCurQuestUnique, pclMsg->clQuestInfo.siCurQuestStep, pclMsg->clQuestInfo.siQuestCmd, 0,
									szCharParam1, NULL);
}

// PCK : 스폐셜 퀘스트 저장 결과 - 로그용
void cltServer::DoMsg_DBMSG_RESPONSE_SETSPECIALQUESTCHANGE(sPacketHeader* pPacket)
{
	// 스폐셜 퀘스트를 하나 완료하고 나면 받는 보상과 얻는 단어의 결과를 로그로 남긴다.
	sDBResponse_SetSpecialQuestInfo* pclMsg = (sDBResponse_SetSpecialQuestInfo*)pPacket;
	
	cltServer* pclserver = (cltServer*)pclClient;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID) ;
	if ( pclCM->IsValidID(id) == false ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// 현재 스폐셜 퀘스트는 보상으로 경험치만 주고 있으나, 차후 돈이나 아이템이 추가할것을 대비해서 나머지 부분도 남기도록 한다.
	// param1 == 아이템 유니크, param2 == 보상아이템의 갯수, param3 == 보상받은 금액, param4 == 보상받은 경험치
	// charparam1 == 단어조합 맞춘상황

	TCHAR szCharParam1[50] = { '\0', };
	StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("WordAssembly = %d%d%d%d%d%d%d%d%d%d"),
		pclMsg->bWordAssemblySwitch[0], pclMsg->bWordAssemblySwitch[1],
		pclMsg->bWordAssemblySwitch[2], pclMsg->bWordAssemblySwitch[3],
		pclMsg->bWordAssemblySwitch[4], pclMsg->bWordAssemblySwitch[5],
		pclMsg->bWordAssemblySwitch[6], pclMsg->bWordAssemblySwitch[7],
		pclMsg->bWordAssemblySwitch[8], pclMsg->bWordAssemblySwitch[9]);

	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_SPECIALL_QUEST_CHANGE, 
		0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		pclMsg->clSpecialQuestInfo.clQuestRewardInfo.siItemUnique[0], pclMsg->clSpecialQuestInfo.clQuestRewardInfo.siItemNum[0], 
		pclMsg->clSpecialQuestInfo.clQuestRewardInfo.siMoney, pclMsg->clSpecialQuestInfo.clQuestRewardInfo.siExp, 0,
		szCharParam1, NULL);

}

// 퀘스트 저장 결과. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETSPECIALQUESTINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetSpecialQuestInfo* pclMsg = (sDBResponse_SetSpecialQuestInfo*)pPacket;

	if ( pclMsg->bClearWordSpecialQuest && pclMsg->siClearWordSpecialQuestNum > 0 )
	{
		SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID) ;
		if ( pclCM->IsValidID(id) == false ) return;

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

		// 단어조함 클리어 횟수 - 흥부박(요술램프)
		pclchar->pclCI->clQuestInfo.siClearWordSpecialQuest = pclMsg->siClearWordSpecialQuestNum ;
		//pclchar->pclCI->clQuestInfo.siEventClearWordSpecialQuest = pclMsg->siEventClearWordSpecialQuestNum;
		// 7회 마다 초기화(8회때 1로 보이게..)
		pclchar->pclCI->clQuestInfo.siEventClearWordSpecialQuest = pclMsg->siEventClearWordSpecialQuestNum - (((pclMsg->siEventClearWordSpecialQuestNum - 1) / 7) * 7);


		//퀘스트 수행 횟수를 2으로 나는 몫과 나머지를 이용해 2배수 횟수마다 특별 보상을 한다.
		SI32 siEventReward = (pclchar->pclCI->clQuestInfo.siEventClearWordSpecialQuest) / 2;
		SI32 siCheckValue = (pclchar->pclCI->clQuestInfo.siEventClearWordSpecialQuest) % 2;

		if( pclEventTimeManager->InEventTime("MagicLamp_event", &sTime) )
		{	
			// [지연-090602] 1, 3, 5,7 ... 의 횟수마다 보상을 준다. (나머지 1일때)
			if ( 1 == siCheckValue ) // 나머지 1일때의 몫의 값으로 보상을 준다.
			{
				siEventReward = siEventReward % 4; 
				SI32	itemunique = 0;
				SI16	itemnum = 0;
				SI16	brareswitch = 0;
				cltItem clItem;

				switch ( siEventReward )
				{
				case 0:
					// 1회 수행 : 러브러브초콜렛 - 아이템 5개 생성
					itemunique = ITEMUNIQUE(3890);
					itemnum = 5;
					break;
				case 1:
					// 3회 수행 : 다크카카오
					itemunique = ITEMUNIQUE(2781);
					itemnum = 8;
					break;
				case 2: 
					// 5회 수행 : 레인보우 케이크
					itemunique = ITEMUNIQUE(3897);
					itemnum = 10;
					break;
				case 3:
					// 7회 수행 : 애완동물
					itemunique = ITEMUNIQUE(13646); // 팅키
					itemnum = 1;
					break;;
				}


					if(pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, 0, &brareswitch) == true)
					{
						clItem.SetItemNum(itemnum);

						SI32 rtnvalue = 0;
						if( pclchar->InputItem(pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WORDASSEMBLE, &rtnvalue) == false)
						{
							// 인벤토리에 직접 못넣으면 역참(우체국)으로 보낸다.
							((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclchar->pclCI->GetPersonID(), &clItem , NULL ,0  ); // 수정 필요
							
							//SendLog_InventoryFull( pclchar->pclCI->GetPersonID(),itemunique,itemnum,
							//	INPUTITEMPERSON_OPTION_WORDASSEMBLE);
						}
					}
			}

		}

		// 스페셜 퀘스트 보상 타입을 읽어온다. - 흥부박(요술램프)
		SI64 siGV_SpecialQuestReward = GetGlobalValue(TEXT("GV_SpecialQuestReward"));

		GMONEY givemoney = 0;
		// 기본 보상
		if( siGV_SpecialQuestReward == 0 )
		{
			// 돈을 지급한다.
			SI32 npcRate =  pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			givemoney = pclchar->pclCI->clIP.GetLevel() * npcRate *50;
			sDBRequest_ChangeMoney clMsg(pclchar->GetID(), pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_WORDSPECIALQUEST, givemoney );
			SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg);

			pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_SPECIALQUEST, givemoney);

			// 랜덤하게 대박 아이템을 준다.  - 1%
			if (rand()%100 == 0)
			{
				SI32 bigitemunique = pclItemManager->GetRandBigWarItem();
				cltItem clItem;
				SI16 brareswitch = 0;
				SI16 itemnum = 10;
				if(pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch) == true)
				{
					clItem.SetItemNum(itemnum);

					SI32 rtnvalue = 0;
					if( pclchar->InputItem(pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WORDASSEMBLE, &rtnvalue) == false)
					{
						SendLog_InventoryFull( pclchar->pclCI->GetPersonID(),bigitemunique,itemnum,
							INPUTITEMPERSON_OPTION_WORDASSEMBLE);
					}
				}
			}
		}
		// 할로윈 이벤트 보상 - by LEEKH 2007.10.16
		else if ( siGV_SpecialQuestReward == 1 )
		{
			SI32	bigitemunique = 0;
			cltItem	clItem;
			SI16	brareswitch = 0;
			SI16	itemnum = 10;
			SI32	usedate = 0;

			SI32 siRand = rand() % 100;

			// 랜덤하게 대박 아이템을 준다.  - 40%
			if ( siRand < 10 )
			{
				bigitemunique = ITEMUNIQUE(3899);
				itemnum = 1;
			}
			else if ( siRand < 30 )
			{
				bigitemunique = pclItemManager->GetRandBigWarItem();
				itemnum = 10;
			}
			else if ( siRand < 100 )
			{
				// 할로윈 모자
				bigitemunique = ITEMUNIQUE(23055);
				itemnum = 1;
				usedate = 7;
			}

			if(bigitemunique > 0)
			{
				if(pclItemManager->MakeRandItemUnique( bigitemunique, &clItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate) == true)
				{
					clItem.SetItemNum(itemnum);

					SI32 rtnvalue = 0;
					if( pclchar->InputItem(pclItemManager, &clItem, INPUTITEMPERSON_OPTION_WORDASSEMBLE, &rtnvalue) == false)
					{
						SendLog_InventoryFull( pclchar->pclCI->GetPersonID(), bigitemunique, itemnum, INPUTITEMPERSON_OPTION_WORDASSEMBLE);
					}
				}
			}
		}

		// 클라이언트에 보상 내역을 통보한다.
		cltGameMsgResponse_Clear_SpecialWord clinfo( pclchar->pclCI->clQuestInfo.siClearWordSpecialQuest, givemoney, pclchar->pclCI->clIP.GetMoney(), pclchar->pclCI->clQuestInfo.siEventClearWordSpecialQuest );		// 이벤트용 횟수 체크 변수 추가로 생성 부분 수정.
		cltMsg clMsg1(GAMEMSG_RESPONSE_CLEAR_SPECIALWORD, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg1);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			cltServer * pclServer = (cltServer*)pclClient;

			// [로그추가 : 황진성 2007. 10. 8] // 특수 퀘스트. 
			// param1 : 아이템 유니크
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_SPECIALL_QUEST_END, 
				0, pclchar, NULL, 0, givemoney, pclchar->pclCI->clIP.GetMoney(), NULL, 0, 0, 0, 0, 0, 0, 
				pclMsg->clSpecialQuestInfo.clQuestRewardInfo.siItemUnique[0], 0, 0, 0, 0, NULL, NULL);

		}
	}
}

// PCK : 네이밍 퀘스트 추가 (로그용)
void cltServer::DoMsg_DBMSG_RESPONSE_SETNAMINGQUESTINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetNamingQuestInfo* pclMsg = (sDBResponse_SetNamingQuestInfo*)pPacket;

	cltServer * pclServer = (cltServer*)pclClient;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID) ;
	if ( pclCM->IsValidID(id) == false ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// param1 == 아이템 유니크, param2 == 보상아이템의 갯수, param3 == 보상받은 금액, param4 == 보상받은 경험치
	// charparam1 == 네이밍 인덱스, 레벨

	TCHAR szCharParam1[50] = { '\0', };
	StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("NamingIndex = %d, NamingLevel = %d"), 
					pclMsg->clNamingQuestInfo.clQuestRewardInfo.siNamingIndex, 
					pclMsg->clNamingQuestInfo.clQuestRewardInfo.siNamingLevel);
	
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_QUEST, LOGCOMMAND_INDEX_QUEST_NAMING_INFO_SET, 
		0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		pclMsg->clNamingQuestInfo.clQuestRewardInfo.siItemUnique[0], pclMsg->clNamingQuestInfo.clQuestRewardInfo.siItemNum[0], 
		pclMsg->clNamingQuestInfo.clQuestRewardInfo.siMoney, pclMsg->clNamingQuestInfo.clQuestRewardInfo.siExp, 0, 
		szCharParam1, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETPERSONNAMINGINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetPersonNamingInfo* pclMsg = (sDBResponse_SetPersonNamingInfo*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );
	if(pclCM->IsValidID(id) == FALSE ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if ( pclMsg->siResult > 0 )
	{
		if( pclMsg->siIndex >= 0 && pclMsg->siIndex < MAX_NAMINGQUEST_INDEX )
		{
			pclCM->CR[id]->pclCI->clPersonNaming.m_siLevel[pclMsg->siIndex] = pclMsg->siLevel;

			// naming - TODO : 완료 했다고 메세지 날려주쟈...

			cltGameMsgResponse_SetPersonNamingInfo clinfo( pclMsg->siIndex, pclMsg->siLevel );
			cltMsg clMsg(GAMEMSG_RESPONSE_SETPERSONNAMINGINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_SETPERSONCURRENTNAMING(sPacketHeader* pPacket)
{
	sDBResponse_SetPersonCurrentNaming* pclMsg = (sDBResponse_SetPersonCurrentNaming*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );
	if(pclCM->IsValidID(id) == FALSE ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if ( pclMsg->siResult > 0 )
	{
		pclCM->CR[id]->pclCI->clPersonNaming.m_siSelectedIndex = pclMsg->siSelectedIndex;
		pclCM->CR[id]->pclCI->clPersonNaming.m_siSelectedLevel = pclMsg->siSelectedLevel;

		cltGameMsgResponse_SetPersonCurrentNaming clinfo( pclCM->CR[id]->GetCharUnique(), pclMsg->siSelectedIndex, pclMsg->siSelectedLevel );
		cltMsg clMsg(GAMEMSG_RESPONSE_SETPPERSONCURRENTNAMING, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNeighbourMsg(&clMsg, true);
	}
}

//KHY - 0822 - 해피빈 퀘스트 추가.
void cltServer::DoMsg_DBMSG_RESPONSE_GETHAPPYBEANQUESTINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetHappyBeanClearInfo* pclMsg = (sDBResponse_GetHappyBeanClearInfo*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );
	if(pclCM->IsValidID(id) == FALSE ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 siResult = 0;
	if(pclMsg->siQuestType == QUEST_TYPE_HAPPYBEAN)
	{
		if(pclMsg->siQuest_CompleteCount < MAX_QUEST_ONEDAY_COUNT)
		{
			if((pclMsg->siQuest_CompleteCount  + pclMsg->siQuest_StartCount) <= MAX_QUEST_ONEDAY_COUNT)
				siResult = 1;
		}
	}

	switch(siResult )
	{
		case 0 : //0 = 퀘스트 불허.
			{
				// 퀘스트 상태를 DB에 저장한다. - 벌써 증가한 StartCount값을 낮춘다.
				SendLog_SetHappyBeanClearInfo(pclchar, QUEST_TYPE_HAPPYBEAN, QUEST_HAPPYBEAN_STEP_NON);

				cltGameMsgResponse_HappyBeanQuestStart_NO clinfo( siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_NO, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			break;
		case 1 : // 1= 퀘스트 진행 허가.
			if ( pclchar->MakeHappyBeanQuest( ) == false ) // 퀘스트를 만든다.
			{
				// 퀘스트 상태를 DB에 저장한다. - 벌써 증가한 StartCount값을 낮춘다.
				SendLog_SetHappyBeanClearInfo(pclchar, QUEST_TYPE_HAPPYBEAN, QUEST_HAPPYBEAN_STEP_NON);

				// 퀘스트 진행 허가는 나왔지만, 퀘스트를 만드는데 실패했다. (1)
				cltGameMsgResponse_HappyBeanQuestStart_NO clinfo( siResult );
				cltMsg clMsg(GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_NO, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			else
			{
				// 퀘스트 진행 허가는 나왔고, 퀘스트를 만드는데 성공.
				cltGameMsgResponse_HappyBeanQuestStart_OK clinfo(&pclchar->pclCI->clQuestInfo.clHappyBeanQuestInfo );
				cltMsg clMsg(GAMEMSG_RESPONSE_HAPPYBEANQUEST_START_OK, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);		
			}

			
			break;
		case 2 : // 2= 퀘스트 완료가 성공적으로 저장 되었음.
				// 할게 있나?
			break;
		default :
			return;
			break;
	}
}

//KHY - 0906 - 게임방 이벤트 쿠폰.
void cltServer::DoMsg_DBMSG_RESPONSE_GETEVENTCOUPONINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetEventCouponInfo* pclMsg = (sDBResponse_GetEventCouponInfo*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );
	if(pclCM->IsValidID(id) == FALSE ) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 siResult = pclMsg->siResult;
	if(pclMsg->siEventType == GAMEROOM_COUPON_EVENT)
	{
		switch(siResult )
		{
			case 0 : //한장이라도 발급 받았다
				{
					//할게 없다. 정상 동작.
				}
				break;
			case 1 : // //발급 받은 쿠폰이 없다. -쿠폰발금.
				{
					//쿠폰 발급.
					cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
					cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				}
				break;
			default :
				return;
				break;
		}
	}

	if(pclMsg->siEventType == AUCTION_COUPON_EVENT)
	{
		switch(siResult )
		{
		case 0 : 
			{			}
			break;
		case 1 : // //
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		case 2 : 
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		case 3 : 
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		case 4 : 
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		case 5 :
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		case 6 : 
			{
				//쿠폰 발급.
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			}
			break;
		
		default :
			return;
			break;
		}
	}
	// 고스톱,포커 이벤트 설정
	if (pclMsg->siEventType == GOSTOP_POKER_EVENT)
	{
		switch (siResult)
		{
		case 0 :	// 이미 고스톱 또는 포커머니를 받았을 경우
			{
				// 할게없음. 
			}
			break;
		case 1 :
			{
				// 포커머니 지급
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			break;
		case 2 :
			{
				// 고스톱머니 지급
				cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
				cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			}
			break;

		default :
			return;
			break;
		}
	}

	//KHY - 1024 - 한게임 VIP 이벤트
	if(pclMsg->siEventType == HAN_GAME_VIP_EVENT)
	{
		switch (siResult)
		{
			case 0 :	// 에러. 
				{
					// 할게없음. 
				}
				break;
			case 1 :
				{
					cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
					cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
				break;
			default :
				return;
				break;
		}
	}
	//KHY - 1025 - 나우콤 이벤트
	if(pclMsg->siEventType == NOW_COM_EVENT)
	{
		switch (siResult)
		{
			case 0 :	// 에러. 
				{
					// 할게없음. 
				}
				break;
			case 1 : // 최초 접속. - 쿠폰 발급 성공.
			case 2 : // 10렙달성.
			case 3 :	// 제자 되기 성공.			
				{
					cltGameMsgResponse_EventCoupon clinfo( pclMsg->siEventType ,siResult);
					cltMsg clMsg(GAMEMSG_RESPONSE_EVENTCOUPON, sizeof(clinfo), (BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clMsg);
				}
				break;
			default :
				return;
				break;
		}
	}

	// 겨울맞이! 군주S의 훈훈한 릴레이 이벤트 - by LEEKH 2007.12.21
	if(pclMsg->siEventType == SUPER_ROOKIE_LEVELUP_EVENT)
	{
		cltItem clRewardItem;
		clRewardItem.Init();
		SI16	brareswitch = 0;
		SI32	usedate = 0;
		SI32	ItemUnique = 0;
		SI32	ItemNum = 0;

		switch (siResult)
		{
		case 0 :	
			{
				// 할게없음. 
			}
			break;
		case QUEST_TYPE_BATTLE1:			// 지그프리드
			{
				ItemUnique = ITEMUNIQUE(13612);
				ItemNum = 1;
				usedate = 30;
			}
			break;
		case QUEST_TYPE_BASIC1:				// 지젤
			{
				ItemUnique = ITEMUNIQUE(15900);
				ItemNum = 1;
			}
			break;
		case QUEST_TYPE_HUNTINGGROUND01:	// 소피아
			{
				ItemUnique = ITEMUNIQUE(24096);
				ItemNum = 1;
			}
			break;
		case QUEST_TYPE_HUNTINGGROUND02:	// 스파키
			{
				ItemUnique = ITEMUNIQUE(5400);
				ItemNum = 1;
			}
			break;
		case QUEST_TYPE_BATTLE2:			// 진
			{
				ItemUnique = ITEMUNIQUE(3880);
				ItemNum = 5;
			}
			break;
		}

		if(ItemUnique > 0)
		{
			SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(ItemUnique);
			if (ref <= 0)	return;

			// 설정된 날짜가 없으면, 아이템의 기본값을 사용한다.
			if(usedate <= 0)	usedate = pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

			if( pclClient->pclItemManager->MakeRandItemUnique( ItemUnique, &clRewardItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, usedate ) )
			{
				// -------------------------------------------
				// LEEKH 예외코드 ----------------------------
				clRewardItem.uiDateYear = 0;
				clRewardItem.uiDateMonth = 0;
				clRewardItem.uiDateDay = 0;
				// -------------------------------------------

				// 개수 설정
				clRewardItem.siItemNum = ItemNum;

				cltSystemRewardInfo clInfo;

				clInfo.m_sGiveTime = sTime;

				// 지급한 날부터 30일동안 수령이 가능하다.
				TimeAddDate(&clInfo.m_sGiveTime, 30, &clInfo.m_sExpireTime);

				//NDate ExpireDate;
				//ExpireDate.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );
				//ExpireDate.AddMonths( 2 );

				//_SYSTEMTIME sExpireTime;
				//TimeAddDate(&sTime, 30, &sExpireTime);

				//clInfo.m_sExpireTime = sExpireTime;
				clInfo.m_clItem.Set( &clRewardItem );

				NTCHARString256		kText( GetTxtFromMgr(7230) );
				StringCchCopy(clInfo.m_szReason, sizeof(clInfo.m_szReason), kText);
 
				sDBRequest_GiveSystemReward clMsg( GIVEREWARD_ACCOUNT, pclchar->pclCI->GetPersonID(), pclchar->GetID(), &clInfo );
				SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
			}
		}
	}
}

// 새로운 Person이 만들어졌음을 알려주는 메시지 프로시져.
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOCREATE(sPacketHeader* pPacket)
{
	sDBResponse_PersonTotalInfoCreate* pclMsg = (sDBResponse_PersonTotalInfoCreate*)pPacket;

	SI32 id	= pclMsg->usCharID;
	SI32 id2 = pclMsg->siPersonID;

	if(pclCM->IsValidID(id) == FALSE)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	//---------------------------------------------------
	// 결과값을 확인한다. 
	//---------------------------------------------------
	switch(pclMsg->siResult)
	{
	case 1:	// 성공. 
		{
			// [영훈] 캐릭터 생성시 보상아이템을 지급한다 - 2008.11.19
			if ( true == pclEventTimeManager->InEventTime( TEXT("CreateCharReward"), &sTime) )
			{
				if ( pclRewardMgr )
				{
					pclRewardMgr->GiveCreateCharRewardItem( id2 );
				}
			} 
			
			cltCharListInfo sendMsg;
			sendMsg.clBI.SetName( pclMsg->szName );
			cltMsg clMsg( GAMEMSG_RESPONSE_MAKENEWCHAR, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );

			if( pclPromoterManager )
			{
				// 프로모터 시스템에서 캐릭터 생성시 프로모터와 관계등록을 위해 사용한다.
				clPromoterInfo PromoterInfo( id, clPromoterInfo::SET_PROMOTER_CHAR );
				PromoterInfo.SetName( pclMsg->szName ); 
				PromoterInfo.SetAccountID( pclMsg->szAccountID );
				pclPromoterManager->Push( PromoterInfo );
			}


			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [로그추가 : 황진성 2007. 9. 5] // 캐릭터 생성 로그쓰기.
				// pszCharParam1 == 계정아이디.
				// pszCharParam2 == 캐릭터 이름.
				// 임시용
				cltCharServer clTmpCharServer;
				// 계정 id
				clTmpCharServer.pclCI->clBI.siIDNum = pclchar->pclCI->clBI.siIDNum;
				// 캐릭터 명
				clTmpCharServer.SetName(pclMsg->szName);
				// personid
				clTmpCharServer.pclCI->SetPersonID(pclMsg->siPersonID);

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_MAKECHAR, 
					0, &clTmpCharServer, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					0, 0, 0, 0, 0, pclMsg->szAccountID, pclMsg->szName);
			}
		}
		break;
	case 0:	// 실패 
		return ;
	case -1:	// 중복 아이디. 
		// 클라이언트로 서버의 응답값을 보낸다. 
		SendServerResponseMsg(0, SRVAL_MAKEPERSON_FAIL_DUPNAME,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	// -> 리턴해야 한다. 중복 아이디라 생성이 아예 안된다.
	}

	siNewCharNum++;

	//-------------------------------------------------------------
	// GameDBManager_World에게 모든 Person정보를 알려줄 것을 요청한다. 
	//-------------------------------------------------------------
	sDBRequest_PersonListInfoGet clMsg(pclMsg->usCharID, pclCM->CR[id]->pclCI->clBI.siIDNum);
	pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);

	if(pclMsg->siResult == 1)
	{
		// 로그 작성 - 캐릭터 생성
		//WriteLogToDB()
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_PERSONLISTINFOGET(sPacketHeader* pPacket)//케릭터를 삭제 하고 리스트를 업그레이드 한다.
{
	sDBResponse_PersonListInfoGet* pclMsg  = (sDBResponse_PersonListInfoGet*)pPacket;

	SI32			siGetID	= pclMsg->usCharID;
	cltCharServer*	pclChar	= pclCM->GetCharServer( siGetID );
	if ( NULL == pclChar )
	{
		return;
	}

	cltPBasicInfo	clinfo;
	cltCharListInfo	clCharListInfo;
	bool			bDeleteChar;

	for ( SI32 siIndex=0; siIndex<MAX_TOTAL_CHAR_PER_USER; siIndex++ )
	{
		// 기본 정보 셋팅
		clinfo.Set( &pclMsg->personInfo[siIndex] );
		clinfo.SetIndex( siIndex );	// 현재 인덱스를 기억 하도록 한다

		// 캐릭터 리스트에 대한 셋팅
		clCharListInfo.clBI.Set( &clinfo );
		clCharListInfo.clBI.uiGMMode	= 0;
		clCharListInfo.clIP.siLevel		= pclMsg->siLevel[siIndex];
		clCharListInfo.DelCharTime		= pclMsg->stTime[siIndex];

		/*
		// 아이템에 대한 정보는 앞에 3개의 캐릭터만 갖고 있는다
		if ( MAX_CHAR_PER_USER > siIndex )
		{
			for ( SI32 siCount=0; siCount<MAX_CHAR_PER_USER; siCount++ )
			{
				clCharListInfo.clCharItem[siCount] = pclMsg->personIteminfo[siIndex][siCount];
			}
		}
		else
		{
			for ( SI32 siCount=0; siCount<MAX_CHAR_PER_USER; siCount++ )
			{
				clCharListInfo.clCharItem[siCount].Init();
			}
		}
		*/

        // 캐릭터 리스트에 대한 정보를 설정한다
		if ( pclChar->pclCharListInfo )	
		{
			pclChar->pclCharListInfo[siIndex].Set(&clCharListInfo);
		}

		// 캐릭터 삭제 유해 기간에 따른 처리
		bDeleteChar = false;

		if ( 0 < clCharListInfo.DelCharTime.wYear )
		{
			// 삭제해야 할 캐릭터인지 체크
			SYSTEMTIME st_CheckTime;
			SYSTEMTIME st_CurTime;

			// 삭제가 예정된 시각에 3일을 더한다.
			TimeAddDate(&clCharListInfo.DelCharTime, 3, &st_CheckTime);

			// 현재 시간
			GetLocalTime(&st_CurTime);

			if(TimeCompare(&st_CurTime, &st_CheckTime) > 0)
			{
				bDeleteChar = true;
			}
		}

		// 삭제 유해 기간이 지나서 삭제해야 한다면
		if ( true == bDeleteChar )
		{
			sDBRequest_PersonTotalInfoDelete clMsg( siGetID, pclChar->pclCI->clBI.siIDNum, siIndex, clCharListInfo.clBI.clPerson.siPersonID, TEXT(""), pclChar->GetSession()->GetIP());
			SendDBMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg );
		}
		else
		{
			cltMsg clMsg(GAMEMSG_RESPONSE_CHARLIST, sizeof(cltCharListInfo), (BYTE*)&clCharListInfo);
			pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
		}
	}

}

//cyj 사용자가 아이템 정보 받아오는 함수
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONITEMINFOGET(sPacketHeader* pPacket)
{
	sDBResponse_PersonItemInfoGet* pclMsg = (sDBResponse_PersonItemInfoGet*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	//---------------------------------------------------
	// 결과값을 확인한다. 
	//---------------------------------------------------
	//if(pclMsg->siResult == 0)return ;

	pclCM->CR[id]->pclCI->clCharItem.Set(&pclMsg->ItemInfo);

	// 휴면 계정 아이템이 있을 경우 아이템 업그래이드 ==============================================================================
	CDormancySystem *pclDormancySystem = this->pclDormancySystem;
	if( NULL != pclDormancySystem)
	{
		CDormancyEquipItemRewardServer *pclDormancyServer = (CDormancyEquipItemRewardServer *)pclDormancySystem->GetDormancyEquipItemReward();
		if(NULL != pclDormancyServer)
		{
			pclDormancyServer->UpgradeItemInven(pclCM->CR[id]);
		}
	}
	//==============================================================================================================================

	pclCM->CR[id]->SetUpdateSwitch( UPDATE_INVENTORY, true, 0);


	return;
}

// 최초로그인 시점
// 사용자가 Person을 선택했을때 DB로 Person의 전체 정보를 요청하는데 이때 수령한 전체 정보를 처리하는 함수. 
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOGETBYIDNUM(sPacketHeader* pPacket)
{
	SI32 i = 0 ;

	sDBResponse_PersonTotalInfoGet* pclMsg = (sDBResponse_PersonTotalInfoGet*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	TCHAR*	pszCounteyCode = NULL;
	int		siAccessDeny = IPACCESSDENY_NONE;
	bool	bPass = false;

	if(pclAccessDenyMgr)		siAccessDeny = pclAccessDenyMgr->GetAccessDeny(pclCM->CR[id]->GetSession()->GetIP());
	if(pclIPToCountryMgr)		pszCounteyCode = pclIPToCountryMgr->GetCountryCode(pclCM->CR[id]->GetSession()->GetIP());

	// 운영자 아이디는 무조건 통과 - 20090420 - BASIC_PLAYERMASTER_LEVEL (90) 부터 로그인이 가능하다. 
	if( pclCM->CR[id]->GetGameMasterLevel() >= BASIC_PLAYERMASTER_LEVEL )
		siAccessDeny = IPACCESSDENY_ACCESS;

	switch(siAccessDeny)
	{
	case IPACCESSDENY_ACCESS:	{		bPass = true;		}		break;
	case IPACCESSDENY_DENY:		{		bPass = false;		}		break;
	case IPACCESSDENY_NONE:
		{
			bPass = true;

			if ( pszCounteyCode != NULL)
			{
				// 접속 제한 조건
				if ( pclClient->siServiceArea == ConstServiceArea_English )
				{
					// 글로벌의 경우 
					if( _tcscmp( pszCounteyCode, CONST_COUNTRYCODE_JAPAN ) == 0 ||
						_tcscmp( pszCounteyCode, CONST_COUNTRYCODE_KOREA ) == 0 )
					{
						bPass = false;
					}
				}
				// 접속 제한 조건
				else if ( pclClient->siServiceArea == ConstServiceArea_NHNChina )
				{
					if( _tcscmp( pszCounteyCode, CONST_COUNTRYCODE_JAPAN ) == 0 ||
						_tcscmp( pszCounteyCode, CONST_COUNTRYCODE_KOREA ) == 0 )
					{
						bPass = false;
					}
				}
				else if ( pclClient->siServiceArea == ConstServiceArea_EUROPE )
				{
					if( _tcscmp( pszCounteyCode, CONST_COUNTRYCODE_JAPAN ) == 0 ||
						_tcscmp( pszCounteyCode, CONST_COUNTRYCODE_KOREA ) == 0 )
					{
						bPass = false;
					}
				}
			}
		}
		break;
	}

	if(bPass == false)
	{
		SendServerResponseMsg(0, SRVAL_NOTCORRECTIP,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	//---------------------------------------------------
	// 결과값을 확인한다. 
	//---------------------------------------------------
	if(pclMsg->siResult == 0)return ;

	// 기존 캐릭터가 시스템인 아닌경우, (캐릭터 제 선택인경우.) 
	if(pclCM->CR[id]->GetKind() != KIND_SYSTEM)
	{
		// 같은 캐릭터 선택이라면, 아무런 처리를 하지않아야 한다.
		if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->clInfo.BasicInfo.clPerson.GetPersonID())
		{
			return ;
		}

		// 이전에 플레이 하던 캐릭터는 종료처리를 한다.
		// 캐릭터 종료 처리를 한다. 실제로 캐릭터를 삭제하는 것은 아니고 필요한 초기화 조치만 취한다.
		((cltCharServer*)pclCM->CR[id])->CloseAction(this, true);
	}

	// 서버 정보를 통보한다. (캐릭터가 만들어지기 전에 통보해야 한다.) 
	SendServerInfo(id);

	if( pclMsg->clInfo.BasicInfo.uiKind < 0 || pclMsg->clInfo.BasicInfo.uiKind > MAX_KIND_NUMBER )		return;
	if( pclKindInfoSet->pclKI[pclMsg->clInfo.BasicInfo.uiKind] == NULL )
	{
		MsgBox(TEXT("Fds39fj"), TEXT("idnum:%d index:%d personid:%d kind:%d"), 
			pclMsg->clInfo.BasicInfo.siIDNum, 
			pclMsg->clInfo.BasicInfo.uiIndex,
			pclMsg->clInfo.BasicInfo.clPerson.GetPersonID(),
			pclMsg->clInfo.BasicInfo.uiKind);

		return ;
	}

	//----------------------------------------------------
	// 선택한 캐릭터 정보를 서버에 보관한다.
	//----------------------------------------------------
	// 운영자 권한을 확보한다. 
	SI32 gamemasterlevel = pclCM->CR[id]->GetGameMasterLevel();

	// 기존의 임시 캐릭터를 삭제하고 새로운 캐릭터를 만든다.
	pclCM->DeleteChar(id);

	//----------------------------------------------------
	// 캐릭터 정보를 토대로 필드를 거닐 캐릭터를 만든다. 
	//----------------------------------------------------
	cltPersonInfo			clPersonInfo;
	cltInnerStatusInfo		clInnerStatus;
	clInnerStatus.clEnemyType.Set(ENEMYTYPE_ALLNPC | ENEMYTYPE_VILLAGE | ENEMYTYPE_GUILDWAR , 0);		// 모든 NPC에게 적대적이다. 

	cltIdentity				clIdentity;

	clPersonInfo.clBI.Set(&pclMsg->clInfo.BasicInfo);
	clPersonInfo.clBI.siHomeVillage	= pclMsg->siHomeVillageUnique;
	clPersonInfo.clBI.uiGMMode = 0;

	clPersonInfo.clIP.Set(&pclMsg->clInfo.IPInfo);
	clPersonInfo.clCharSkill.Set(&pclMsg->clInfo.SkillInfo);
	clPersonInfo.clCharItem.Set(&pclMsg->clInfo.ItemInfo);
	clPersonInfo.clCharRank.Set(&pclMsg->clInfo.RankInfo);

	//clPersonInfo.clLimitDateItem.Set(&pclMsg->clInfo.clLimitDateItemInfo);

	clPersonInfo.clBank.Set(&pclMsg->clInfo.clBankInfo);				// 전장 관련 정보. 
	clPersonInfo.clStock.Set(&pclMsg->clInfo.clStockInfo);				// 주식 관련 정보. 
	//_LEON_GUILD_STOCK
//	clPersonInfo.clGuildStock.Set(&pclMsg->clInfo.clGuildStockInfo);	// 길드 주식 관련 정보
	clPersonInfo.clWorldMoney.Set(&pclMsg->clInfo.clWorldMoney);

	//_LEON_GUILD_CHAT
//#if defined(_DEBUG)
	clPersonInfo.clBI.clGuildRank.Set(&pclMsg->clInfo.BasicInfo.clGuildRank);	// 개인 길드 정보
//#endif

	// 버프
	clPersonInfo.clBI.clBufInfo.SetBuf(&pclMsg->clInfo.BasicInfo.clBufInfo);
	
	clPersonInfo.uiGachaCnt = pclMsg->clInfo.uiGachaCnt;
	clPersonInfo.clPersonNaming.Set( &pclMsg->clInfo.clPersonNaming );

	clPersonInfo.clWorldPassport.Set( &pclMsg->clInfo.clWorldPassportForDB );

	// 휴면 계정 정보
	clPersonInfo.clDormancyInfo.Set(&pclMsg->clInfo.m_clDormancyInfo);
	
	// 주총이 진행중인 마을이 있는지 확인한다. 
	for(i =0;i < MAX_STOCK_KIND_IN_ACOUNT;i++)
	{
		SI16 villageunique = clPersonInfo.clStock.clInfo.clUnit[i].siVillageUnique;
		if(villageunique == 0)continue;
		if(pclCityHallManager->IsGeneralMeeting(villageunique))
		{
			cltLetterMsg_GeneralMeeting clletter(villageunique);
			SendLetterMsg(pclMsg->clInfo.BasicInfo.clPerson.GetPersonID(), (cltLetterHeader*)&clletter);

		}

		//#if defined(_CITYHALL_BANKRUPTCY)
		cltStrInfo* pclStrInfo = pclCityHallManager->GetStrInfo(villageunique);

		// 1주라도 가진 마을이 파산이면 공지함
		switch( pclCityHallManager->GetCityHallState( villageunique ) )
		{
		case 	CITYHALL_BEING_NORMAL		:		// 마을 정상 상태 중
			{

				if( pclStrInfo->clCityhallStrInfo.clChiefDate.GetDateVary() == 0 )	// 신규 마을이므로 파산 체크 없다
					break;
				// 대행수가 임명되었는가
				// 배열로 잡혀있기 때문에 NULL을 기대할 수 없다.
				cltRank* pclrank = pclRankManager->GetRank(RANKTYPE_CITYHALL, villageunique);

				if(pclrank != NULL && pclrank->clPerson.siPersonID > 0 ) // 대행수가 있다면 파산으로 안간다.
					break;

				// 날짜가 같은 경우도 해당
				if( pclStrInfo->clCityhallStrInfo.clResignDate.GetDateVary() >= pclStrInfo->clCityhallStrInfo.clChiefDate.GetDateVary() )
				{
					SI32 siMyStockAmount = clPersonInfo.clStock.clInfo.GetStockAmount(villageunique);
					SI32 siTotalStockAmount = pclStrInfo->clCityhallStrInfo.siTotalStockAmount;

					if( siMyStockAmount < 1 || siTotalStockAmount < 1 ) break;

					// 마을 주식 3%이상을 가지고 있어야 파산 경고 공지를 받는다.
					if( siMyStockAmount < siTotalStockAmount * CITYHALL_BANKRUPTCY_NOTIFY_STOCK_AMOUNT_RATE ) break;

					cltDate cldate1, cldate2;
					cldate1.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );
					cldate2.Set( &pclStrInfo->clCityhallStrInfo.clResignDate );

					//#if defined(_DEBUG)
					//					cldate1.uiDay = cldate1.uiDay + CITYHALL_BANKRUPTCY_NOTIFY_AFTER_DAYS;
					//					cldate2.uiDay = cldate2.uiDay + CITYHALL_BANKRUPTCY_AFTER_DAYS;
					//#else
					// AddMonth 함수를 쓸 것
					cldate1.AddMonth( CITYHALL_BANKRUPTCY_NOTIFY_AFTER_MONTHS );
					cldate2.uiYear = cldate2.uiYear + CITYHALL_BANKRUPTCY_AFTER_YEARS;
					//#endif

					// 대행수 해임 후 6개월 이후라면 1년이 되면 파산 함을 1년이 될 때까지만 공지한다.
					if( cldate1.GetDateVary() <= pclTime->clDate.GetDateVary() && 
						cldate2.GetDateVary() > pclTime->clDate.GetDateVary() ) 
					{
						cltLetterMsg_VillageNameAndDate clletter( villageunique, &cldate2, cltLetterMsg_VillageNameAndDate::LETTERTYPE_CITYHALLBANKRUPTCY_ALERT );
						SendLetterMsg(pclMsg->clInfo.BasicInfo.clPerson.GetPersonID(), (cltLetterHeader*)&clletter );
					}
				}
			}
			break;
		}
		//#endif

	}

	clPersonInfo.clMarket.Set(&pclMsg->clInfo.clMarketInfo);			// 객주 관련 정보. 
	clPersonInfo.clRealEstate.Set(&pclMsg->clInfo.clRealEstateInfo);	// 부동산 정보. 
	clPersonInfo.clHealthInfo.Set(&pclMsg->clInfo.clHealthInfo);		// 건강  정보. 
	clPersonInfo.clQuestInfo.Set(&pclMsg->clInfo.clQuestInfo);			// 퀘스트 정보.

	// 말이 없는 상태인데 타고 있다면, 타지 않은 상태로 전환해야 한다. 
	clPersonInfo.clHorseInfo.Set(&pclMsg->clInfo.clHorseInfo);			// 말정보. 

	clPersonInfo.clGuiltyInfo.Set(&pclMsg->clInfo.clGuiltyInfo);		// 전과 정보. 
	clPersonInfo.clDailyQuestInfo.Set(&pclMsg->clInfo.clDailyQuestInfo);// DailyQuest 정보
	clPersonInfo.clDailyQuest2Info.Set(&pclMsg->clInfo.clDailyQuest2Info);
	clPersonInfo.clDailyQuest3Info.Set(&pclMsg->clInfo.clDailyQuest3Info);
	clPersonInfo.clSummonInfo.Set(&pclMsg->clInfo.clSummonInfo);		// 소환수 

	if( pclClient->IsCountrySwitch( Switch_Elixir) )
	{
		// 서버에 캐릭터의 엘릭서 정보 세팅.
		if( pclchar )
		{
			pclchar->pcltElixir->SetEndMinuteVary(  pclMsg->clInfo.m_clElixirInfo.m_siEndMinuteVary	);	
			pclchar->pcltElixir->SetMultiple(  pclMsg->clInfo.m_clElixirInfo.m_uiMultiple );
			pclchar->pcltElixir->SetPoint(  pclMsg->clInfo.m_clElixirInfo.m_siPoint	);		
			pclchar->pcltElixir->SetStr(  pclMsg->clInfo.m_clElixirInfo.m_siStr	);		
			pclchar->pcltElixir->SetDex(  pclMsg->clInfo.m_clElixirInfo.m_siDex	);		
			pclchar->pcltElixir->SetVit(  pclMsg->clInfo.m_clElixirInfo.m_siVit	);		
			pclchar->pcltElixir->SetMag(  pclMsg->clInfo.m_clElixirInfo.m_siMag	);		
			pclchar->pcltElixir->SetHnd(  pclMsg->clInfo.m_clElixirInfo.m_siHnd	);		
			pclchar->pcltElixir->SetWis(  pclMsg->clInfo.m_clElixirInfo.m_siWis	);		

			pclchar->bElixirSwitch = pclchar->pcltElixir->IsElixir();
		}
	}
	

	// 군주 스페셜이라면 ip를 통해 한게임 pc방인지 체크한다
#ifdef USE_HANIPCHECK

	if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		TCHAR szBuffer[256] = {0,};

		SI32 rVal =	HanIPCheckRequest( szBuffer , 256 , pclCM->CR[id]->GetSession()->GetIP() ) ;

		if( 0 == rVal)
		{

			TCHAR szReturn[2] = {0,};

			_tcsncpy( szReturn , szBuffer , 1 );

			if( 0 == _tcscmp(szReturn , "Y"))	// 성공
			{
				clPersonInfo.clBI.bPCRoom = true;
				TCHAR* pszGradeCode = NULL;	// 등급 코드를 마저 읽는다.
				TCHAR* pszCRMcode = NULL;
				pszGradeCode =  strtok(&szBuffer[1], "|");
				pszCRMcode	= strtok(NULL,"|");

				if( pszGradeCode != NULL )
				{
					if( 0 == _tcscmp(pszGradeCode , "G") )
					{
						clPersonInfo.clBI.sPCroomGrade = 'G';
					}
					else if( 0 == _tcscmp(pszGradeCode , "P") )
					{
						clPersonInfo.clBI.sPCroomGrade = 'P';
					}
					else if( 0 == _tcscmp(pszGradeCode , "T") )
					{
						clPersonInfo.clBI.sPCroomGrade = 'T';
					}
				}

				if(pszCRMcode != NULL)
				{
					_tcsncpy(clPersonInfo.clBI.szCRMcode, pszCRMcode ,16);
				}

			}			
			else	// pc방이 아님
			{
				clPersonInfo.clBI.bPCRoom = false;				
			}

		}
		else
		{
			// pc방이 아님
			clPersonInfo.clBI.bPCRoom = false;	

			// 오류코드 체크
			TCHAR * pszError = NULL;
			pszError =	(TCHAR*)HanIPCheckErrorString(rVal);
			if( pszError )
			{
				pclClient->pclLog->FilePrint( "Config\\PCRoomErrorLog.log", pszError );
			}
		}
	}	// if( pclClient->siServiceArea == ConstServiceArea_Korea )
	else if ( IsWhereServiceArea(ConstServiceArea_NHNChina) )
	{
		char szBuffer[256]	= { 0, };
		
		SI32 siReturnValue	= HanIPCheckRequestEx( szBuffer, sizeof(szBuffer), pclCM->CR[id]->GetSession()->GetIP(), "N" );
		if ( HAN_IPCHECK_OK == siReturnValue )
		{
			// 성공코드 Y만 검출하고 기타 플러스/CRM등은 체크하지 않아도 된다
			if ( 'Y' == szBuffer[0] )
			{
				clPersonInfo.clBI.bPCRoom = true;	
			}
			else
			{
				clPersonInfo.clBI.bPCRoom = false;	
			}
		}
		else
		{
			// pc방이 아님
			clPersonInfo.clBI.bPCRoom = false;	

			// 에러 로그
			TCHAR * pszError = (TCHAR*)HanIPCheckErrorString( siReturnValue );
			if( pszError )
			{
				pclClient->pclLog->FilePrint( "Config\\PCRoomErrorLog.log", pszError );
			}
		}
	}	// else if ( IsWhereServiceArea(ConstServiceArea_NHNChina) )
#endif //#ifdef USE_HANIPCHECK

	// 강제 PC방 설정
	if(pclClient->IsCountrySwitch(Switch_PCRoom))
	{
		clPersonInfo.clBI.bPCRoom = true;
	}

	// 마을 주민인 경우에는 마을 주민들에게 로그인 했음을 알려준다.
	if ( clPersonInfo.clBI.siHomeVillage > 0 )
	{
		if ( clPersonInfo.clBI.GetName() != NULL && _tcslen( clPersonInfo.clBI.GetName() ) > 0 )
		{
			cltGameMsgResponse_ResidentLogin clGameMsgResponse_ResidentLogin( clPersonInfo.clBI.siHomeVillage, (TCHAR*)clPersonInfo.clBI.GetName() );
			cltMsg clMsg( GAMEMSG_RESPONSE_RESIDENTLOGIN, sizeof( clGameMsgResponse_ResidentLogin ), (BYTE*)&clGameMsgResponse_ResidentLogin );
			pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg, clPersonInfo.clBI.siHomeVillage );
		}
	}

	//----------------------------------------------------
	// 아이템의 장비가 정상적인지 확인한다. 
	//----------------------------------------------------
	/*	SI16 erroritemunique, errorpos;
	if(pclMsg->clInfo.ItemInfo.IsAllProperEquip(pclItemManager, &erroritemunique, &errorpos) == false)
	{
	pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("Invalid Equip(Person:%d)(item:%d)pos(%d)"), 
	pclMsg->clInfo.BasicInfo.clPerson.siPersonID,
	erroritemunique, errorpos);
	return ;
	}
	*/


	// 장비품의 통계를 낸다. 
	for(i = 0; i < PERSONITEM_INV0;i++)
	{
		if(pclMsg->clInfo.ItemInfo.clItem[i].siUnique)
		{
			pclItemManager->AddEquipItemNum(pclMsg->clInfo.ItemInfo.clItem[i].siUnique, 1);

			// 새로운 통계 - 장비품의 통계를 낸다.
			//NStatistics_Add("Item", pclMsg->clInfo.ItemInfo.clItem[i].siUnique, "EquipNum", 1);

		}
	}

	{
		cltGameMsgResponse_SetVillageUpgrade sendMsg( &siTopLevelVillageUnique[0] );
		cltMsg clMsg( GAMEMSG_RESPONSE_SETVILLAGEUPGRADE, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
	}

	// 유저의 사용중인 무장에 대한 통계를 낸다. (30이상일때만 )
	if(clPersonInfo.clIP.GetLevel() >= 30 )
	{
		if( pclCM->CR[id]->ActiveWeapon >= 0 && pclCM->CR[id]->ActiveWeapon < MAX_ITEM_PER_PERSON )
			pclCM->AddUserWeapon(&clPersonInfo.clCharItem.clItem[pclCM->CR[id]->ActiveWeapon]);
	}

	//---------------------------------------------------
	// 레벨이 10이상인데 초보자 수련장에 있따면 ,, 견이
	//---------------------------------------------------
	if(clPersonInfo.clIP.GetLevel()  >= MAX_LEVEL_FOR_BEGINNERMAP && clPersonInfo.clBI.GetMapIndex() == MAPINDEX_BEGINNER1)
	{
		// 한양으로 이동한다. 

		SI32 villageunique = 1;
		SI32 maptypeunique = pclMapManager->pclMapArray[villageunique]->siMapUnique;
		SI32 x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		SI32 y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		clPersonInfo.clBI.SetMapIndex(villageunique);
		clPersonInfo.clBI.SetX(x);
		clPersonInfo.clBI.SetY(y);
	}

	// 유저 입장 제한이 있는 맵이라면..
	SI32 userLimit = pclClient->pclMapManager->GetUserLimit( clPersonInfo.clBI.GetMapIndex() );
	if ( userLimit > 0 &&
		 pclClient->pclMapManager->IsInstanceMap(clPersonInfo.clBI.GetMapIndex()) == false )
	{
		if ( pclClient->pclMapManager->GetUserCount(clPersonInfo.clBI.GetMapIndex()) >= userLimit )
		{
			// 클론맵이 있는지 확인한다.
			SI32 cloneMapIndex = pclClient->pclMapManager->GetCloneMap( clPersonInfo.clBI.GetMapIndex() );
			if ( cloneMapIndex )
			{
				clPersonInfo.clBI.SetMapIndex(cloneMapIndex);
			}
		}
	}

	//---------------------------------------------------
	// 배틀로얄 맵에 있다면
	//---------------------------------------------------
	if( ( clPersonInfo.clBI.GetMapIndex() ==  MAPINDEX_BATTLEROYAL_MABRIUM )||
		( clPersonInfo.clBI.GetMapIndex() ==  MAPINDEX_BATTLEROYAL_GRANDMABRIUM ) )
	{
		clPersonInfo.clBI.SetMapIndex(MAPINDEX_MAINFIELD);
		clPersonInfo.clBI.SetX(499);
		clPersonInfo.clBI.SetY(258);
	}

	//---------------------------------------------------
	// 축제 기간이 아니라면
	//---------------------------------------------------
	if( !pclEventTimeManager->InEventTime("FestivalEvent", &sTime) &&  MAPINDEX_FESTIVAL == clPersonInfo.clBI.GetMapIndex() )
	{
		clPersonInfo.clBI.SetMapIndex(MAPINDEX_MAINFIELD);
		clPersonInfo.clBI.SetX(288);
		clPersonInfo.clBI.SetY(354);
	}

	//---------------------------------------------------
	// 길드전 필드에 있다면!
	//---------------------------------------------------
	if( IsCountrySwitch( Switch_NewGuildHuntMapWar ) )	// 변경후
	{
		if( IsGuildWarMap_Use_New_GuildWar( clPersonInfo.clBI.GetMapIndex() )  || 
			IsGuildWarMap_NEW( clPersonInfo.clBI.GetMapIndex() ) )
		{
			clPersonInfo.clBI.SetMapIndex(MAPINDEX_PALACE);
			clPersonInfo.clBI.SetX(26);
			clPersonInfo.clBI.SetY(72);
		}
	}
	else	// 변경전 
	{
		if( IsGuildWarMap_Not_Use_New_GuildWar( clPersonInfo.clBI.GetMapIndex() ) )
		{
			clPersonInfo.clBI.SetMapIndex(MAPINDEX_PALACE);
			clPersonInfo.clBI.SetX(26);
			clPersonInfo.clBI.SetY(72);
		}
	}
	if( IsCountrySwitch( Switch_PKHuntMap_Change_Info ) )	// 변경후
	{
		if( pclMapManager->IsPkMap(clPersonInfo.clBI.GetMapIndex()  ))	// pk 맵이면 리스해서 돌아올때 엔펠리스 
		{
			clPersonInfo.clBI.SetMapIndex(MAPINDEX_PALACE);
			clPersonInfo.clBI.SetX(26);
			clPersonInfo.clBI.SetY(72);
		}
	}
#ifdef USE_PROMOTOR_SERVER
	// 프로모터 새내기 유저는 인사말을 전달하기 위해서.
	if( clPersonInfo.clIP.GetLevel() <= 1 )
	{
		clPromoterInfo PromoterInfo( id, clPromoterInfo::PROMOTER_INTRODUCE );
		PromoterInfo.SetName( (TCHAR*)clPersonInfo.clBI.GetName() ); 
		PromoterInfo.SetAccountID( clPersonInfo.clBI.szAccountID );
		pclPromoterManager->Push( PromoterInfo );
	}
#endif
	//---------------------------------------------------
	// 레벨이 10이상인데 초보자 수련장에 있따면 ,, 신이
	//---------------------------------------------------
	//if(clPersonInfo.clIP.GetLevel()  >= MAX_LEVEL_FOR_BEGINNERMAP && clPersonInfo.clBI.GetMapIndex() == MAPINDEX_BEGINNER2)
	//{
	//	// 신의주로 이동한다. 

	//	SI32 villageunique = 69;
	//	SI32 maptypeunique = pclMapManager->pclMapArray[villageunique]->siMapUnique;
	//	SI32 x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
	//	SI32 y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

	//	clPersonInfo.clBI.SetMapIndex(villageunique);
	//	clPersonInfo.clBI.SetX(x);
	//	clPersonInfo.clBI.SetY(y);
	//}

	//---------------------------------------------------
	// 수렵장이면 연결된 마을로 간다. 
	//---------------------------------------------------
	if(pclMapManager->IsHuntMap(clPersonInfo.clBI.GetMapIndex()) == true)
	{
		SI32 villunique = clPersonInfo.clBI.GetMapIndex() - 200;
		if(villunique >= 0 && villunique < MAX_VILLAGE_NUMBER && pclVillageManager->pclVillageInfo[villunique])
		{
			SI32 maptypeunique = pclMapManager->pclMapArray[villunique]->siMapUnique;
			SI32 x = -1;
			SI32 y = -1;
			if( maptypeunique >= 0 && maptypeunique < MAX_MAPTYPE_NUMBER )
			{
				x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
				y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
			}

			if( x > 0 && y > 0)
			{
				// 연결된 마을로 간다.
				clPersonInfo.clBI.SetMapIndex(villunique);
				clPersonInfo.clBI.SetX(x);
				clPersonInfo.clBI.SetY(y);
			}
		}
	}
	//--------------------------------------------
	// 인스턴스 던전이면 경복궁으로 날려버린다.
	//---------------------------------------------
	else if ( pclMapManager->IsInstanceMap(clPersonInfo.clBI.GetMapIndex()) == true )
	{
		SI32 mapindex = 0 ;
		SI32 centerx = 0 ;
		SI32 centery = 0 ;
		//if ( siServiceArea == ConstServiceArea_China )
		//{
		//	// 마을정보를 얻어와 이동시킨다.
		//	mapindex = MAPINDEX_PALACE;		// 경복궁 
		//	centerx  = 26;
		//	centery  = 72;
		//}
		//else
		//{
		//	if ( pclCM->CR[id]->pclKI->siDefaultCountry == ConstServiceArea_China )
		//	{
		//		// 마을정보를 얻어와 이동시킨다.
		//		mapindex = MAPINDEX_CHINABORDER;		// 국경선
		//		centerx  = 17;
		//		centery  = 19;
		//	}
		//	else
		//	{
				// 마을정보를 얻어와 이동시킨다.
				mapindex = MAPINDEX_PALACE;		// 경복궁 
				centerx  = 26;
				centery  = 72;
		//	}
		//}

		clPersonInfo.clBI.SetMapIndex(mapindex);
		clPersonInfo.clBI.SetX(centerx);
		clPersonInfo.clBI.SetY(centery);
	}
	//-------------------------------------------------
	// 감옥에 있는 상태면, 
	//-------------------------------------------------
	if(clPersonInfo.clGuiltyInfo.siLeftPrisonSecond)
	{
		clPersonInfo.clBI.SetMapIndex(PRISON_MAPINDEX);
		clPersonInfo.clBI.SetX(PRISON_X);
		clPersonInfo.clBI.SetY(PRISON_Y);

		clInnerStatus.SetStatus(INNERSTATUS_PRISON);
	}

	//[진성] 파티홀. 파티장에 있으면 엔펠리스로 무조건 뭐프시킨다. => 2008-4-2
	if(IsPC(id))
	{
		for(SI32 MapCount = 0; MapCount < MAX_PARTYHALL_MAP; ++MapCount)
		{
			// 새로 초기화 되는 캐릭터가 파티장에서 나오게 되면 엔펠리스로 워프시킨다.
			if(clPersonInfo.clBI.GetMapIndex() == PARTYHALL_START_MAP_INDEX + MapCount)
			{
				clPersonInfo.clBI.SetMapIndex(MAPINDEX_PALACE);
				clPersonInfo.clBI.SetX(26);
				clPersonInfo.clBI.SetY(72);
			}
		}
	}

	//[진성] 서버 이벤트. 이벤트 보상기간 중이 아닌 상태인데 해당 맵에 있다면 엔펠리스로 이동 시킨다. => 2008-7-1
	if( IsCountrySwitch( Switch_Server_Event ) )
	{
		if( false == pclEventTimeManager->InEventTime("GoonzuDay_Week_Reward", &sTime) )
		{
			if( true == pclServerEventManager->IsEventMap( clPersonInfo.clBI.GetMapIndex() ) )
			{
				clPersonInfo.clBI.SetMapIndex( MAPINDEX_PALACE );
				clPersonInfo.clBI.SetX(26);
				clPersonInfo.clBI.SetY(72);
			}
		}
	}


	// 군주데이 이벤트 중이라면 클라이언트에게 알려줍니다.
	/*if(pclEventTimeManager->InEventTime("GoonzuDay_Week", &sTime) == true)
	{
		cltGameMsgResponse_EventTime_Update sendMsg("GoonzuDay_Week", true);
		cltMsg clMsg(GAMEMSG_REQUEST_EVENTTIME_UPDATE, sizeof(sendMsg), (BYTE*)&sendMsg);

		cltCharServer* pclchar = pclClient->pclCM->GetCharServer(id);
		if(pclchar)
		{
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}*/

	//---------------------------------------------------
	// 해당 지역에 있을때는 무조건 엔펠리스(한양)으로 이동
	//---------------------------------------------------
	switch ( clPersonInfo.clBI.GetMapIndex() )
	{
		case Const_MapIndex_PollMap:		// 투표소 지역
		case MAPINDEX_SERVEREVENT_LOBBY:	// 서버이벤트 던전 로비
		case MAPINDEX_SANTAFACTORY_1:		// 아이의 산타 작업장.
		case MAPINDEX_SANTAFACTORY_2:		// 청년의 산타 작업장.
		case MAPINDEX_SANTAFACTORY_3:		// 어른의 산타 작업장.
		case MAPINDEX_SANTAFACTORY_1_2:		// 아이의 산타 작업장.
		case MAPINDEX_SANTAFACTORY_2_2:		// 청년의 산타 작업장.
		case MAPINDEX_SANTAFACTORY_3_2:		// 어른의 산타 작업장
		case MAPINDEX_WEDDINGHALL:			// 예식장에 있을때
			{
				clPersonInfo.clBI.SetMapIndex(MAPINDEX_PALACE);
				clPersonInfo.clBI.SetX(26);
				clPersonInfo.clBI.SetY(72);
			}
			break;
	}


	//---------------------------------------------------
	// 땅 지역이 아닌 곳에 있다면 가까운 포구로 이동한다. 
	//---------------------------------------------------
	SI32 x = 0, y = 0;
	SI32 mapindex = 0;

	//--------------------------------------------------
	// 정상적인 땅 지역에 있다면, 
	//--------------------------------------------------
	if(pclMapManager->IsLandMap( clPersonInfo.clBI.GetMapIndex() ) == true)
	{
		x	= clPersonInfo.clBI.clPos.siX;
		y	= clPersonInfo.clBI.clPos.siY;
		mapindex	= clPersonInfo.clBI.clPos.siMapIndex;

		bool bGetPos = false;
		if( mapindex >= 0 && mapindex < MAX_MAP_NUMBER )
			bGetPos = pclMapManager->pclMapArray[clPersonInfo.clBI.clPos.siMapIndex]->FindEmptyAreaForCharLocate(clPersonInfo.clBI.uiKind, clPersonInfo.clBI.clPos.siX, clPersonInfo.clBI.clPos.siY, 30, &x, &y, false);

		if( bGetPos == false )
		{
			//------------------------------------
			// 실패시에는 한양에서 나오게 한다. 
			//------------------------------------
			SI32 villageunique = 1;
			SI32 maptypeunique = pclMapManager->pclMapArray[villageunique]->siMapUnique;

			x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
			y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
		}
	}
	else
	{
		pclLog->FilePrint( TEXT("Config\\ErrorLog.log"), TEXT("No Land Area:%d id:%d"),
			clPersonInfo.clBI.GetMapIndex(), id);

	}
	// 캐릭터를 배치하기 적절한 곳인지 확인한다. 
	clPersonInfo.clBI.clPos.siMapIndex	= mapindex;
	clPersonInfo.clBI.clPos.siX			= x;
	clPersonInfo.clBI.clPos.siY			= y;

	SI32 childcharunique	= 0;
	SI32 summonindex		= 0;
	SetChar1(id, pclCM->CR[id]->GetCharUnique(), childcharunique, summonindex, &clIdentity, &clPersonInfo, &clInnerStatus, 0);

	//cltCharServer* pclcchar = (cltCharServer*)pclCM->CR[id];

	// [기형] 선공방지 스프 
	if(clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK))
	{
		pclCM->CR[id]->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum = true;
	}
	else
	{
		pclCM->CR[id]->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum = false;
	}
	
	// 확보해둔 운영자 권한을 설정한다. 
	pclchar->SetGameMasterLevel(gamemasterlevel);
	pclchar->SetRareItemRate(0,0,0,0);
	pclchar->SetWennyOldMan(false,false);

	// 로그인후 10초간 보호한다.
	pclchar->SetInitProtectSwitch();

	//---------------------------------------
	// HashTable에 PERSON 이름과 정보들을 설정한다.
	//---------------------------------------
	if(pclHashTable->Insert((TCHAR *)pclCM->CR[id]->GetName(), pclCM->CR[id]->pclCI->GetPersonID(), id)==false)
	{
		pclLog->FilePrint( TEXT("Config\\ErrorLog.log"), TEXT("pclHashTable->Insert name:%s id:%d"),
			(TCHAR *)pclCM->CR[id]->GetName(), id);
	}
	if(pclPersonHashTable->Insert(pclCM->CR[id]->pclCI->GetPersonID(), id)==false)
	{
		pclLog->FilePrint( TEXT("Config\\ErrorLog.log"), TEXT("pclPersonHashTable->Insert personid:%d id:%d"),
			pclCM->CR[id]->pclCI->GetPersonID(), id);
	}

	if ( (id != pclCM->GetIDFromName((TCHAR *)pclCM->CR[id]->GetName()))
		|| (id != pclCM->GetIDFromPersonID(pclCM->CR[id]->pclCI->GetPersonID()))
		)
	{
		pclchar->bCloseSocketSwitch	= true;
		pclchar->dwCloseSocketTimer	= 5;

		pclLog->FilePrint( TEXT("Config\\BugChar_Login.txt"), TEXT("PersonID:%d"), pclCM->CR[id]->pclCI->GetPersonID() );
	}

	//---------------------------------------
	// 이 Person의 정보를 사용자에게 보낸다. 
	//---------------------------------------
	cltOrderDataInfo clOrder;
	clOrder.Make(ORDER_STOP, BY_PLAYER, 0, 0, 0, 0);


	//------------------------------------------
	// 캐릭터의 아이템 확인.
	//------------------------------------------	
	cltPItemInfo * pclcharitem = &pclCM->CR[id]->pclCI->clCharItem ;
	NDate ndate;
	ndate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
	SI32 todaydatevary = ndate.GetDateVary() ;

	for ( i = 0 ; i < MAX_ITEM_PER_PERSON ; i ++ )
	{
		SI32 itemunique = pclcharitem->clItem[i].siUnique ;
		if ( itemunique > 0 )
		{
			if ( pclcharitem->clItem[i].IsHaveUseDay() )  //[영진] 남은 사용기간 3일미만 알림
			{
				SI32 useableDay = 0;
				BOOL rVal = GetItemUseAbleDay(&pclcharitem->clItem[i],&useableDay);
				
				if(pclcharitem->clItem[i].IsSealingUp(pclItemManager) == true)
					continue;

				if(rVal == FALSE) continue;
							
				if(useableDay >= 3) continue; // 사용가능기간이 3일 이상 넉넉하면 패스 
				else if(useableDay >= 0)		 //  3일 미만이지만 사용가능 기간이 남아있다면 클라이언트로 경고
				{
					cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclcharitem->clItem[i].siUnique, useableDay);
					cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
				}
				else if( useableDay < 0) //사용기간이 지나서 지워준다 그리고 클라이언트에 알림.
				{
					//KHY - 0723 - 기간아이템 파괴 방지.
					if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
					{

					}
					else
					{
						// 고급품은 지워지지 않는다. - by LEEKH
						if( pclcharitem->clItem[i].clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
						{
							sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),i,&pclcharitem->clItem[i],USEITEM_REASON_DATEOVER);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
												
							cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclcharitem->clItem[i].siUnique, useableDay);
							cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				
						}
					}
				}
			}
		}
	}//( i = 0 ; i < MAX_ITEM_PER_PERSON ; i ++ )

	//------------------------------------------	
	// 외부 장비. 
	//--------------------------------------------------
	// 무기사용술 부적 사용 실태를 체크한다. 
	//--------------------------------------------------
	pclchar->CheckWeaponSkillScroll(pclItemManager);

	cltShapeEquipInfo clequip;
	pclchar->GetShapeEquipInfo(&clequip);


	// 현재 나와있는 말의 정보를 구한다. 
	SI32 horseunique = 0;
	cltHorse* pclhorse = clPersonInfo.clHorseInfo.GetCurrentShowHorse();
	SI32 addstatusdate = 0 ;
	SI32 ticketnum = 0 ;

	SI32 PremiumDate_slot1 = 0 ;
	SI32 PremoiumUniuqe_Slot1 = 0 ;
	SI32 PremiumDate_slot2 = 0 ;
	SI32 PremoiumUniuqe_Slot2 = 0 ;
	SI32 PremiumDate_slot3 = 0 ;
	SI32 PremoiumUniuqe_Slot3 = 0 ;
	SI32 PremoiumPartsNum = 0 ;


	if(pclhorse)
	{
		horseunique = pclhorse->siHorseUnique;
		addstatusdate = pclhorse->clAddStatusDate.GetDateVary() ;
		ticketnum = pclhorse->siStatusTicketNum ;

		PremiumDate_slot1 = pclhorse->clPremiumPartsDate_Slot1.GetDateVary() ;
		PremoiumUniuqe_Slot1 = pclhorse->siPremiumUnique_Slot1 ;
		PremiumDate_slot2 = pclhorse->clPremiumPartsDate_Slot2.GetDateVary() ;
		PremoiumUniuqe_Slot2 = pclhorse->siPremiumUnique_Slot2 ;
		PremiumDate_slot3 = pclhorse->clPremiumPartsDate_Slot3.GetDateVary() ;
		PremoiumUniuqe_Slot3 = pclhorse->siPremiumUnique_Slot3 ;

		PremoiumPartsNum = pclhorse->siPremiumPartsNum	;

		// 말에 관한 데이터가 없다면, 타고 있을 수 없다.
		if(horseunique <= 0 )
		{
			clPersonInfo.clHorseInfo.siCurrentHorseRIDEHORSE = false;
		}

		//KHY - 1111 - 오토바이 추가.		
		if((horseunique == HORSEUNIQUE_MOTORCYCLE) && (clPersonInfo.clHorseInfo.siCurrentHorseRIDEHORSE == TRUE))
		{
			// 오토바이에 타기위해 필요한 종량제 시스템 확인
			if( pclchar->pclCI->clBI.clTimeMeterRateInfo.GetLeftTime( TIMEMETERRATE_MOTORCYCLE ) <= 0)
			{
				// 연료가 부족합니다.충전해 주십시요.
				//return;
			}
			else
			{
				// 오토바이에 타면 종량제 시작.
				if( pclchar->pclCI->clBI.clTimeMeterRateInfo.UseStart( TIMEMETERRATE_MOTORCYCLE ) == false)
				{
					//return;
				}
			}

			// 효과가 있다면 여기서 넣어준다.
		}
	}

    if (clPersonInfo.clBI.bPCRoom)	
	{
		((cltServer*)pclClient)->siPCRoomCharNum++;
	}

	if( pclGuildManager->siBeforeYearTopGuildUnique > 0 &&
		clPersonInfo.clBI.clGuildRank.IsGuildMember() &&
		clPersonInfo.clBI.clGuildRank.GetGuildUnitIndex() == pclGuildManager->siBeforeYearTopGuildUnique )
		pclchar->uiBestGuild = 1;

	SI32 siBufTransformKind = 0;
	if( clPersonInfo.clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) )
	{
		stBuf* pclBuf = clPersonInfo.clBI.clBufInfo.GetBuf( BUF_TRANSFORM );
		if(pclBuf)			siBufTransformKind = pclBuf->siPercent;
	}

	//// PCK : 축제 음식 (탈것변신)
	//if( clPersonInfo.clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM_HORSE ) )
	//{
	//	stBuf* pclBuf = clPersonInfo.clBI.clBufInfo.GetBuf( BUF_TRANSFORM_HORSE );
	//	if(pclBuf)			siBufTransformKind = pclBuf->siPercent;
	//}

	// 무기술의 달인 - 엠블렘
	UI08 uiGetEmblem = 0;
	if ( (PERSONITEM_WEAPON1 == pclchar->ActiveWeapon) || (PERSONITEM_WEAPON2 == pclchar->ActiveWeapon) )
	{
		SI32 siItemType		= pclchar->pclCI->clCharItem.GetWeaponType( pclClient->pclItemManager, pclchar->ActiveWeapon );
		SI32 siSkillUnique	= pclSkillManager->m_clMasterManager.GetSkillUseWeaponFromItemType( siItemType );
		if ( (0 < siSkillUnique) && (MAX_SKILL_NUMBER > siSkillUnique) )
		{
			SI32 siSkillLevel = pclchar->pclCI->clCharSkill.GetSkillExpLevel( siSkillUnique );
			
			uiGetEmblem = pclSkillManager->m_clMasterManager.GetEmblemIndex( siItemType, siSkillLevel );
			if ( (SKILLMSTER_WEAPONTYPE_NONE< uiGetEmblem) && (SKILLMSTER_WEAPONTYPE_MAX > uiGetEmblem) )
			{
				pclchar->m_uiWeaponSkillMasterEmblem = uiGetEmblem;
			}
		}
	}

	//KHY - 1001 - 기승동물 5마리 보유 수정.
	cltMakeCharInfo clMakeCharInfo(	clPersonInfo.clBI.GetKind(), 
									pclCM->CR[id]->GetCharUnique(),		
									clPersonInfo.clIP.GetLevel(),		
									clPersonInfo.clIP.GetLife(), 
									clPersonInfo.clBI.GetX(), 
									clPersonInfo.clBI.GetY(), 
									clPersonInfo.clBI.GetMapIndex(),
									childcharunique, 
									summonindex, 
									0,
									0, 
									clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_NOFIRSTATTACK) | clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_HINAMOCHI) | clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_EVENT_EGGMOONCAKE) | clPersonInfo.clBI.clBufInfo.IsHaveBufExecptGetType(BUF_TRANSFORM, BUF_GET_TYPE_NIGHTMARKET),
									0,
									clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_LOVEPOWER) && clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_FRIENDSHIP),
									clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_FOURLEAF) ,clPersonInfo.clBI.clBufInfo.IsHaveBuf(BUF_FARMINGNMININGFOREVER) ,
									0,
									clPersonInfo.clBI.uiSex,
									&clequip,
									clPersonInfo.clHorseInfo.siCurrentShowHorse,
									0,
									0,  gamemasterlevel, pclMapManager->pclMapArray[pclCM->CR[id]->GetMapIndex()]->siMapUnique,
									horseunique,									
									clPersonInfo.clBI.siHomeVillage,
									clPersonInfo.clBI.siSchoolUnique,
									&clPersonInfo.clCharRank,addstatusdate,ticketnum,
									&clOrder,
									&clIdentity, 
									&clInnerStatus,
									0,
									0,
									clPersonInfo.clBI.uiGMMode  ,
									clPersonInfo.clBI.bPCRoom  ,
									0,
									&clPersonInfo.clBI.clGuildRank,
									&clPersonInfo.clPersonNaming,
									clPersonInfo.clHorseInfo.siCurrentHorseRIDEHORSE,
									0,
									false,
									pclchar->uiBestGuild,	// [추가 : 황진성 2008. 1. 14 => 자신의 길드가 최강인가.]
									false,
									false,
									siBufTransformKind,
									0,
									NULL,
									false
									,NULL
									,PremiumDate_slot1
									,PremoiumUniuqe_Slot1
									,PremiumDate_slot2
									,PremoiumUniuqe_Slot2
									,PremiumDate_slot3
									,PremoiumUniuqe_Slot3
									,PremoiumPartsNum
									,uiGetEmblem
									,0	// 이곳에서는 결혼 정보를 받아오지 않기 때문에 나중에 받아올때 설정한다
									,0	// 처음에는 수호정령은 소환된 상태가 아니기 때문에 0으로 해도 무방
									,false
									,&clPersonInfo.clBI.clBufInfo);
	if (pclWarRankManager)
	{
		if (pclWarRankManager->IsRankMVPFromPersonID(pclchar->pclCI->GetPersonID()))
		{
			pclchar->pclCI->clBI.uiGMMode = GMMODE_ATB_WARMVP;
			pclchar->SetUpdateSwitch(UPDATE_BASICINFO, true, 0 );
		}
	}

	if( pclBlackWarManager )
	{
		if( true == pclBlackWarManager->IsMVPPersonID( pclchar->pclCI->GetPersonID() ) )
		{
			pclchar->pclCI->clBI.uiGMMode = GMMODE_ATB_WARMVP;
			pclchar->SetUpdateSwitch(UPDATE_BASICINFO, true, 0 );
		}
	}

	// APEX-
#ifdef _CHINA
	if( false == pclchar->bApexLogin )
	{
		NoticeApexProxy_UserLogin( id, pclchar->pclCI->clBI.szAccountID );
		pclchar->bApexLogin = true;
	}
#endif
	// -APEX

	cltMsg clMsg(GAMEMSG_RESPONSE_LOGIN, sizeof(clMakeCharInfo), (BYTE*)&clMakeCharInfo);

	// 클라이언트에게 새로운 사용자의 정보를 통보한다. 
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// 프로모터 정보 초기화.
	if( pclPromoterManager )
	{
		clPromoterInfo PromoterInfo( id, clPromoterInfo::GET_PROMOTER_INFO );
		pclPromoterManager->Push( PromoterInfo );
	}
	


	// 로그인 로그
	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_LOGIN, LOGCOMMAND_INDEX_LOGIN, 
						 0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
						 NULL, NULL);

	
	//KHY - 0906 - 게임방 쿠폰이벤트. 기간 설정. 
	if (pclClient->IsCountrySwitch(Switch_GameRoomCouponEvent) )
	{		
		_SYSTEMTIME sStartEventDay , sEndEventDay;

		ZeroMemory(&sStartEventDay,sizeof(_SYSTEMTIME));
		ZeroMemory(&sEndEventDay,sizeof(_SYSTEMTIME));

		sStartEventDay.wYear = 2007;
		sStartEventDay.wMonth = 9;
		sStartEventDay.wDay = 13;
		sStartEventDay.wHour = 0;
		sStartEventDay.wMinute = 0;
     

		sEndEventDay.wYear = 2007;
		sEndEventDay.wMonth = 10;
		sEndEventDay.wDay = 4;
		sEndEventDay.wHour = 0;
		sEndEventDay.wMinute = 0;

		SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
		SI32 endEventdatevary = pclClient->GetMinuteFromsTime(sEndEventDay);
		
		_SYSTEMTIME fTimeDatevary = pclMsg->clInfo.BasicInfo.GetFirstCreatTime(); //최초 계정 생성 시간.

		SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

		//KHY - 0906 - 게임방 쿠폰이벤트. 기간 검사. 
		if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary))
		{

			TCHAR FullURL[100] = {'\0', };

#ifdef USE_HANRTA
			if(siServiceType == SERVICE_REAL)
			{
				StringCchPrintf(FullURL, sizeof(FullURL),
					"http://gzs.hangame.com/event/promotion.nhn?m=isPCBangIP&ip=%s", pclchar->GetSession()->GetIP());
			}
			else
			{
				StringCchPrintf(FullURL, sizeof(FullURL),
					"http://alpha-gzs.hangame.com/event/promotion.nhn?m=isPCBangIP&ip=%s", pclchar->GetSession()->GetIP());
			}
#endif // USE_HANRTA

			SendServerResponseCharMsg(0, SRVAL_CHECK_WEBVAL, FullURL, NULL, pclCM->CR[id]->GetCharUnique());

			//KHY - 0906 - 게임방 인지 아닌지.
			//if( ) //게임방인 경우에만. (피카 메니져.)
			//{
				//KHY - 0906 -해당계정의 해당이벤트 타입에 따른 쿠폰을 발급여부를 요청한다.
				//sDBRequest_GetEventCouponInfo clMsg3( pclCM->CR[id]->pclCI->GetPersonID() , GAMEROOM_COUPON_EVENT);
				//SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg3);
				
				//SendLog_SetEventCouponInfo(pclchar, GAMEROOM_COUPON_EVENT);

			//}	
		}	
	}
	if (pclClient->IsCountrySwitch(Switch_AuctionEvent)) //지역코드로 묶음. 옥션이벤트 [2007.09.10 손성웅]
	{
		//옥션이벤트 게임 접속했을때.유저가 이벤트 기간에 최초 접속인지 확인해서최초면 쿠폰발금[2007.09.10 손성웅]
		cltServer* pclServer = (cltServer*)pclClient;
		_SYSTEMTIME sStartAEventDay , sEndAEventDay;//이벤트 시작시간과 끝나는 시간로그인 시간.

		sStartAEventDay.wYear = 2007;
		sStartAEventDay.wMonth = 9;
		sStartAEventDay.wDay = 13;
		sStartAEventDay.wHour = 0;
		sStartAEventDay.wDayOfWeek = 0;
		sStartAEventDay.wMinute = 0;
		sStartAEventDay.wSecond = 0;
		sStartAEventDay.wMilliseconds=0;

		sEndAEventDay.wYear = 2007;
		sEndAEventDay.wMonth = 10;
		sEndAEventDay.wDay = 4;
		sEndAEventDay.wHour = 0;
		sEndAEventDay.wDayOfWeek = 0;
		sEndAEventDay.wMinute = 0;
		sEndAEventDay.wSecond = 0;
		sEndAEventDay.wMilliseconds=0;

		SI32 startAEventdatevary = pclClient->GetMinuteFromsTime(sStartAEventDay);
		SI32 endAEventdatevary = pclClient->GetMinuteFromsTime(sEndAEventDay);
		SI32 LoginTime = pclClient->GetMinuteFromsTime(pclServer->sTime);


		if((LoginTime <= endAEventdatevary)
			&&(LoginTime >= startAEventdatevary))
			//이벤트 기간내에 접속이면 쿠폰발급.
		{
			SendLog_SetEventCouponInfo(pclchar, AUCTION_COUPON_EVENT,0);
		}
	}

	//KHY - 1025 - 나우콤 이벤트 - 기간설정. - 1기가이용권.
	//by LEEKH 2007.10.30 - 기간 변경
	if (pclClient->IsCountrySwitch(Switch_NowComEvent)) 
	{
		cltServer* pclServer = (cltServer*)pclClient;
		_SYSTEMTIME sStartAEventDay , sEndAEventDay;//이벤트 시작시간과 끝나는 시간로그인 시간.

		sStartAEventDay.wYear = 2006;
		sStartAEventDay.wMonth = 11;
		sStartAEventDay.wDay = 8;
		sStartAEventDay.wHour = 0;
		sStartAEventDay.wDayOfWeek = 0;
		sStartAEventDay.wMinute = 0;
		sStartAEventDay.wSecond = 0;
		sStartAEventDay.wMilliseconds=0;

		sEndAEventDay.wYear = 2006;
		sEndAEventDay.wMonth = 12;
		sEndAEventDay.wDay = 5;
		sEndAEventDay.wHour = 0;
		sEndAEventDay.wDayOfWeek = 0;
		sEndAEventDay.wMinute = 0;
		sEndAEventDay.wSecond = 0;
		sEndAEventDay.wMilliseconds=0;

		SI32 startAEventdatevary = pclClient->GetMinuteFromsTime(sStartAEventDay);
		SI32 endAEventdatevary = pclClient->GetMinuteFromsTime(sEndAEventDay);
		SI32 LoginTime = pclClient->GetMinuteFromsTime(pclServer->sTime);


		if((LoginTime <= endAEventdatevary)
			&&(LoginTime >= startAEventdatevary))
			//이벤트 기간내에 접속이면 쿠폰발급.
		{
			SendLog_SetEventCouponInfo(pclchar, NOW_COM_EVENT,1); //  -최초 접속.
		}
	}
	// 임시로 빌려져 있는 광산, 농장을 요청한다.
	sDBRequest_GetAgricultureLeaseInfo clMsg2( pclCM->CR[id]->pclCI->GetPersonID() );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);

	// 친구 정보 요청
	sDBRequest_FriendAllList clFriendAllList(id, pclCM->CR[id]->pclCI->GetPersonID(), 1);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clFriendAllList);

	// 게임옵션정보
	sDBRequest_Char_Get_Option clCharOptiinInfo(id, pclCM->CR[id]->pclCI->GetPersonID(), 1);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clCharOptiinInfo);

	

	//---------------------------------------
	// 수호천사 여부 확인. 
	//---------------------------------------
	CMinisterHozo* pclministerhozo = (CMinisterHozo*)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if(pclministerhozo)
	{
		if(pclministerhozo->IsValidAngelFromPersonID(pclCM->CR[id]->pclCI->GetPersonID()))
		{
			pclCM->CR[id]->pclCI->clBI.uiAngelSwitch = true;
		}
	}

	//---------------------------------------
	// 포교 여부 확인. 
	//---------------------------------------
	CMinisterHyungzo* pclministerHyungzo = (CMinisterHyungzo*)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if(pclministerHyungzo)
	{
		if(pclministerHyungzo->IsValidPoliceFromPersonID(pclCM->CR[id]->pclCI->GetPersonID()))
		{
			pclCM->CR[id]->pclCI->clBI.uiPoliceSwitch = true;
		}
	}


	//------------------------------------------
	// 로그인 공지가 설정되어 있따면 공지를 보내준다. 
	//-------------------------------------------
	if(pclNoticeManager->bLoginNoticeSwitch)
	{
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTICELOGIN, 0);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
/*
	//------------------------------------------
	// 캐릭터의 아이템 확인.
	//------------------------------------------	
	cltPItemInfo * pclcharitem = &pclCM->CR[id]->pclCI->clCharItem ;
	NDate ndate;
	ndate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
	SI32 todaydatevary = ndate.GetDateVary() ;

	
	for ( i = 0 ; i < MAX_ITEM_PER_PERSON ; i ++ )
	{
		SI32 itemunique = pclcharitem->clItem[i].siUnique ;
		if ( itemunique > 0 )
		{
			if ( pclcharitem->clItem[i].IsHaveUseDay() )  //[영진] 남은 사용기간 3일미만 알림
			{
				SI32 useableDay = 0;
				BOOL rVal = GetItemUseAbleDay(&pclcharitem->clItem[i],&useableDay);
				
				if(pclcharitem->clItem[i].IsSealingUp(pclItemManager) == true)
					continue;

				if(rVal == FALSE) continue;
							
				if(useableDay >= 3) continue; // 사용가능기간이 3일 이상 넉넉하면 패스 
				else if(useableDay >= 0)		 //  3일 미만이지만 사용가능 기간이 남아있다면 클라이언트로 경고
				{
					cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclcharitem->clItem[i].siUnique, useableDay);
					cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );
				}
				else if( useableDay < 0) //사용기간이 지나서 지워준다 그리고 클라이언트에 알림.
				{
					//KHY - 0723 - 기간아이템 파괴 방지.
					if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
					{

					}
					else
					{
						// 고급품은 지워지지 않는다. - by LEEKH
						if( pclcharitem->clItem[i].clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
						{
							sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),i,&pclcharitem->clItem[i],USEITEM_REASON_DATEOVER);
							pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);
												
							cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclcharitem->clItem[i].siUnique, useableDay);
							cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				
						}
					}
				}
			}
		}
	}//( i = 0 ; i < MAX_ITEM_PER_PERSON ; i ++ )
	//------------------------------------------	
*/
	
	//[추가 : 황진성 2008. 1. 30 => 캐릭터 만들때 공간 박스 리스트 요청 하기.]
	if( pclClient->IsCountrySwitch( Switch_SpaceBox ) )
	{ 
		sDBRequest_Space_Box_List clSpace_Box_List( id, pclCM->CR[id]->pclCI->GetPersonID() );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clSpace_Box_List);
	} 

	//[진성] 도우미 정보 요청.
	if( pclClient->IsCountrySwitch( Switch_Helper ) )
	{ 
		sDBRequest_Question_Daily_Count_Get clInfo( id, pclCM->CR[id]->pclCI->GetPersonID() );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clInfo);
	}

	// [영훈] PVP 무한대전 정보요청
	sDBRequest_PVP_League_InfoGet clPVPLeagueInfo( pclCM->CR[id]->pclCI->GetPersonID() );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clPVPLeagueInfo);

	if( pclClient->IsCountrySwitch( Switch_ValenTineWar ) )
	{
		if(pclClient->pclEventTimeManager->InEventTime("ValentineEvent", &sTime) )
		{
			// [성웅] 발렌타인 데이 정보 요청
			sDBRequest_Valantine_Info_Get clValantineInfo( pclCM->CR[id]->pclCI->GetPersonID() );
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clValantineInfo);
		}
	}

	// 로그인시 군주데이 퀘스트를 수행했는지 체크 해서 수행하지 않은 캐릭터에게 군주데이 미션 부여함.
	// get 으로 디비에서 데이터 얻어옴.

	//------------------------------------------
	// 장인으로 등록시킨다. (운영자 권한이 있는 캐릭터는 표기하지 않는다. ) 
	//-----------------------------------------
	bool debug = false ;
#ifdef _DEBUG
	// 파티획득막음 //debug = true ;
#endif
	if(pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL && debug == false )
	{
		SI32 topskillunique = 0;
		SI32 maxskilllevel = 0;
		for(i = 0;i < MAX_SKILL_NUMBER;i++)
		{
			SI32 skillunique = i;
			if(skillunique <= 0)continue;
			
#ifdef _SAFE_MEMORY
			SI32 totallevel = pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[0]);
#else
			SI32 totallevel = pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, pclCM->CR[id]->pclCI->clCharItem.clItem);
#endif
			SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
			if(totallevel && totallevel >= pclSkillManager->GetMaxLevel(skillunique))
			{
				cltSkillInfo* pclskillinfo = NULL;
				if(skillunique >= 0 && skillunique < MAX_SKILL_NUMBER)
					pclskillinfo = pclSkillManager->pclSkillInfo[skillunique];
				if(pclskillinfo == NULL)continue;
				if((pclskillinfo->siSkillAtb & SKILLATB_LIST) == 0)continue;

				if(pclMasterManager->Regist(id, skillunique, totallevel, personid) == true)
				{
					// 최고 장인이면, 
					if(totallevel > maxskilllevel && pclMasterManager->IsTopSkill(id, skillunique) == true)
					{
						maxskilllevel = totallevel;
						topskillunique = skillunique;

						// 기존 최고 장인은 효과 등록 취소. 
						SI32 oldtopid = pclMasterManager->GetSecondSkillID(skillunique);
						if(pclCM->IsValidID(oldtopid))
						{
							pclCM->CR[oldtopid]->ChangeTopSkillUnique(0);
						}

					}
				}
			}
		}
		
		if(topskillunique)
		{
			pclCM->CR[id]->ChangeTopSkillUnique(topskillunique);
		}
	}

	//--------------------------------------
	// 로그인 회수 통계 
	//--------------------------------------
	pclStatisticsManager->clDailyStatistics.siLoginNumber ++;
	

	// 물품 정보 변경해야 할 것이 있으면 해준다. (2004/10/20 ~ 2004/10/31)
/*	for(i = 0;i < MAX_ITEM_PER_PERSON;i++)
	{
		cltItem * pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[i];
		if(pclitem->siUnique == 0)continue;

		if(pclitem->siUnique == 9400
		|| pclitem->siUnique == 9410
		|| pclitem->siUnique == 13330
		|| pclitem->siUnique == 13340
		|| pclitem->siUnique == 13350
		|| pclitem->siUnique == 13360)
		{

			if(pclitem->clItemArmour.uiSkillUp < 2)
			{
				pclitem->clItemArmour.uiSkillUp = 2;
				
				// DBManager에게 내구도를 소모할 것을 요청한다. 
				sDBRequest_WasteDurability clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), i, 
					pclitem);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}
*/

	// 시전 연장을 못해서 찾아야 할 아이템이 있다면
	if(pclMsg->bExistentItem)
	{
		cltLetterMsg_Existent_SaveUserItem clletter;
		SendLetterMsg(pclMsg->clInfo.BasicInfo.clPerson.GetPersonID(), (cltLetterHeader*)&clletter );
	}
	


	// 주주총회 개최 중인 마을의 주주 이라면,
	{

		cltGameMsgResponse_GeneralMeetingLetter sendMsg;

		int c = 0;
		for( int i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
		{
		
			SI32 villageunique = pclCM->CR[id]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique;
			if( villageunique == 0 ) continue;

			cltCityHall *pCityHall = ((cltCityHall *)(pclCityHallManager->pclStruct[ villageunique ]));

			if( pCityHall == NULL ) continue;

			if( pCityHall->clGeneralMeetingInfo.siMatterType == 1 &&
				pCityHall->clGeneralMeetingInfo.siAcceptCandidate == 1 ) 
			{
				// 주주총회 중이라면,


				// 참여 의사를 밝히지 않았다면,
				for( int j = 0; j < 100; ++j )
				{
					if( pCityHall->clGeneralMeetingInfo.clVoter[ j ].siPersonID ==
						pclCM->CR[id]->pclCI->GetPersonID() &&
						pCityHall->clGeneralMeetingInfo.clVoter[ j ].siParticipate == 0 )
					{

						if (c >= MAX_STOCK_KIND_IN_ACOUNT)		continue;
						sendMsg.siVillageUnique[ c ] = villageunique;
						c++;				

						break;
					}
				}
			}
		}

		if( c ) {

			cltMsg clMsg( GAMEMSG_RESPONSE_GENERALMEETINGLETTER, sizeof( sendMsg ), (BYTE*)&sendMsg );
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );				
		}

	}

	{
		// 국가 설정 관련

		cltGameMsgResponse_CountryInfo sendMsg;
		sendMsg.siCountryID = clPersonInfo.clBI.siCountryID;
		sendMsg.bShowCountry = clPersonInfo.clBI.bShowCountry;

		cltMsg clMsg( GAMEMSG_RESPONSE_COUNTRYINFO , sizeof(sendMsg), (BYTE*)&sendMsg);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	
	{
		// 푸치코미 공개 / 비공개 설정
		
		cltGameMsgResponse_SetShowPuchikomi sendMsg(clPersonInfo.clBI.bShowPuchikomi);
		cltMsg clMsg( GAMEMSG_RESPONSE_SETSHOWPUCHIKOMI, sizeof(sendMsg), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg);

	}

	// 20미만 레벨 유저 - 위에 선언.
	//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	int k;
	for(k = 0; k < MAX_LOWLEVEL_LIST_NUMBER; k++)
	{
		if( siLowLevelCharUnique[k] == pclchar->GetCharUnique() && pclchar->pclCI->clIP.GetLevel() > 19)
		{
			siLowLevelCharUnique[k] = 0;
		}

	}
	bool Same = false;
	bool Full = false;
	if( pclchar->pclCI->clIP.GetLevel() < 20 )
	{
		for(k = 0; k < MAX_LOWLEVEL_LIST_NUMBER; k++)
		{
			if(siLowLevelCharUnique[k] == pclchar->GetCharUnique())
				Same = true;
		}
		if( !Same )
		{
			for(k = 0; k < MAX_LOWLEVEL_LIST_NUMBER; k++)
			{
				if(siLowLevelCharUnique[k] <= 0)
				{
					siLowLevelCharUnique[k] = pclchar->GetCharUnique();
					Full = false;
					break;
				}
				else
					Full = true;
			}		 
		}
		if(Full)
		{
			if( siLowLevelCount >= 0 && siLowLevelCount < MAX_LOWLEVEL_LIST_NUMBER)
			{
				siLowLevelCharUnique[siLowLevelCount] = pclchar->GetCharUnique();
				siLowLevelCount++;
			}
		}
	}

	// 자신의 로그인할때 레벨을 기록해 둔다
	{
		pclchar->siLoginedLevel = pclchar->pclCI->clIP.GetLevel();
	}


	if(siLowLevelCount >= MAX_LOWLEVEL_LIST_NUMBER)
	{
		siLowLevelCount = 0;
	}

	// 길드가 있다면 - 길드 정보를 보내고
	// 길드가 없어도 - 길드 정보를 보내어 초기화 시켜줘야 한다.
	//if ( pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex > 0 )
	{
		cltGuildInfo* pclGuild = pclGuildManager->GetGuildInfo(pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex);
		if ( pclGuild )
		{
			for( SI32 guildmembernum = 0; guildmembernum < MAX_GUILD_MEMBER_NUM; ++guildmembernum )
			{
				// 길드 신청이 되어 있으면 길드 스테이 터스를 적용 하지 않는다.
				if ( pclGuild->clStandingMember[ guildmembernum ].siPersonID == pclchar->pclCI->GetPersonID() )
				{
					cltGuildInfo pclGuildtemp;
					cltSimpleGuildRank	clGuildtemp;

					pclGuildtemp.Init();
					clGuildtemp.Init();

					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuildtemp.clStatus,&clGuildtemp,pclchar->GetCharUnique());
					cltMsg clInfoMsg( GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS,sizeof(clinfo),(BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clInfoMsg );
				}
				else
				{// 길드가 있을때만 길드 스테이터스를 적용 한다.
					cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuild->clStatus,&pclchar->pclCI->clBI.clGuildRank,pclchar->GetCharUnique());
					cltMsg clInfoMsg( GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS,sizeof(clinfo),(BYTE*)&clinfo);
					pclchar->SendNetMsg((sPacketHeader*)&clInfoMsg );
				}
			}
		}
		else
		{
			cltGuildInfo pclGuildtemp;
			cltSimpleGuildRank	clGuildtemp;

			pclGuildtemp.Init();
			clGuildtemp.Init();

			cltGameMsgResponse_Guild_SetGuildStatus clinfo(&pclGuildtemp.clStatus,&clGuildtemp,pclchar->GetCharUnique());
			cltMsg clInfoMsg( GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS,sizeof(clinfo),(BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clInfoMsg );
		}
	}

	SI32 siCurrentEventNPC = 0;
/*
#ifdef EVENT_GIRLS_DAY
	siCurrentEventNPC = GetUniqueFromHash(TEXT("KIND_HINADOLL"));
#endif
*/
	SI32 siEventNPCKind[MAX_HIRED_EVENTNPC_NUM];

	// 마을이 있는데 이벤트NPC를 지어놨다면
	if( pclchar->pclCI->clBI.siHomeVillage > 0 )
	{
		cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo( pclchar->pclCI->clBI.siHomeVillage );

		if( pclinfo != NULL)
		{
			for (i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
				siEventNPCKind[i] = pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind;
			}
			// 클라이언트에 이벤트NPC 정보 전송
			// 0은 삭제 정보
			if( siEventNPCKind >= 0 )
			{
				cltGameMsgResponse_VillageHaveEventNPC clinfo( siEventNPCKind);
				cltMsg clInfoMsg(GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC, sizeof(clinfo), (BYTE*)&clinfo );
				
				//[수정 : 황진성 2008. 2. 25 => 마을에 이벤트 NPC가 있을때 마을 유저에게만 메시지를 전달하게.]
				pclCM->SendAllPersonHomeMsg( (sPacketHeader*)&clInfoMsg, pclchar->pclCI->clBI.siHomeVillage);
			}
		}	
	}
	//[추가 : 황진성 2008. 2. 25 => 마을이 없는 캐릭터일 경우 0으로 초기화 시킨 데이터를 보낸다.]
	else 
	{
		cltGameMsgResponse_VillageHaveEventNPC clinfo;
		cltMsg clInfoMsg(GAMEMSG_RESPONSE_VILLAGEHAVEEVENTNPC, sizeof(clinfo), (BYTE*)&clinfo );
		
		//[수정 : 황진성 2008. 2. 25 => 마을에 이벤트 NPC가 있을때 마을 유저에게만 메시지를 전달하게.]
		pclchar->SendNetMsg( (sPacketHeader*)&clInfoMsg );
	}


	cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclClient->pclItemManager;
	SI16 setItemType = 0;
	SI16 setItemStep = 0;
	SI16 setItemType2 = 0;
	SI16 setItemStep2 = 0;
	SI16 setItemType3 = 0;
	SI16 setItemStep3 = 0;
	SI16 setItemType4 = 0;
	SI16 setItemStep4 = 0;
	SI16 setItemType5 = 0;
	SI16 setItemStep5 = 0;

#ifdef _SAFE_MEMORY
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		setItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep, USE_SETITEM_1 );
		pclchar->m_siSetItemType = setItemType;

		setItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep2, USE_SETITEM_2 );
		pclchar->m_siSetItemType2 = setItemType2;

		setItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep3, USE_SETITEM_3 );
		pclchar->m_siSetItemType3 = setItemType3;

		setItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep4, USE_SETITEM_4 );
		pclchar->m_siSetItemType4 = setItemType4;

		setItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep5, USE_SETITEM_5 );
	}
	else
	{
		setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( &pclchar->pclCI->clCharItem.clItem[0] );
	}
#else
	if ( pclClient->IsCountrySwitch(Switch_Set_Item_Add) )
	{
		setItemType  = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep, USE_SETITEM_1  );
		pclchar->m_siSetItemType = setItemType;

		setItemType2 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep2, USE_SETITEM_2  );
		pclchar->m_siSetItemType2 = setItemType2;

		setItemType3 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep3, USE_SETITEM_3  );
		pclchar->m_siSetItemType3 = setItemType3;

		setItemType4 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep4, USE_SETITEM_4  );
		pclchar->m_siSetItemType4 = setItemType4;

		setItemType5 = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar, &setItemStep5, USE_SETITEM_5  );
	}
	else
	{
		setItemType = pclitemmanager->pclSetItemManager->FindSetItemType( pclchar->pclCI->clCharItem.clItem );
	}
#endif

	pclchar->m_siSetItemType = setItemType;
	pclchar->m_siSetItemStep = setItemStep;

	pclchar->m_siSetItemType2 = setItemType2;
	pclchar->m_siSetItemStep2 = setItemStep2;

	pclchar->m_siSetItemType3 = setItemType3;
	pclchar->m_siSetItemStep3 = setItemStep3;

	pclchar->m_siSetItemType4 = setItemType4;
	pclchar->m_siSetItemStep4 = setItemStep4;

	pclchar->m_siSetItemType5 = setItemType5;
	pclchar->m_siSetItemStep5 = setItemStep5;

	cltGameMsgResponse_SetItemTypeInfo clinfo3( setItemType, setItemStep, setItemType2, setItemStep2 , setItemType3, setItemStep3, setItemType4, setItemStep4, setItemType5, setItemStep5);
	cltMsg clMsg3(GAMEMSG_RESPONSE_SETITEMTYPEINFO, sizeof(clinfo3), (BYTE*)&clinfo3);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg3);

	// 피로방지-
	if( ConstServiceArea_China == siServiceArea )
	{
		pclchar->bTiredSystem = pclMsg->bTiredSystem;
		pclchar->dwPlayingTime = pclMsg->dwPlayingTime;
	}
	else
	{
		//NHNChina 는 이미 설정하였기에 DB에서 가져오는 값을 설정하지 않는다.  
		if( ConstServiceArea_NHNChina != siServiceArea )
		{
		pclchar->bTiredSystem = false;
		pclchar->dwPlayingTime = 0;
	}
	}

	//KHY - 1220 - 변신시스템.
	pclchar->clTransFormInfo.Set(&pclMsg->clInfo.clTransFormInfo);
	
	cltGameMsgResponse_SetTransForm cltransform( &pclchar->clTransFormInfo );
	cltMsg clMsgTransform(GAMEMSG_RESPONSE_TRANSFORM, sizeof(cltransform), (BYTE*)&cltransform);
	pclchar->SendNetMsg((sPacketHeader*)&clMsgTransform);

	// [영훈] 클라이언트에게 CRC체크 패킷을 보내라는 명령 (인자값 1은 아무 의미 없음)
	cltGameMsgResponse_FileCRCCheck cltFileCRCCheck( 1 );
	cltMsg clMsgFileCRCCheck(GAMEMSG_RESPONSE_FILECRCCHECK, sizeof(cltFileCRCCheck), (BYTE*)&cltFileCRCCheck);
	pclchar->SendNetMsg((sPacketHeader*)&clMsgFileCRCCheck);

	// [영훈] 출석관련
	SI32 siPersonID		= pclchar->pclCI->GetPersonID();
	SI32 siCharID		= pclchar->GetID();

	NDate kAttendDay;

	kAttendDay.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );

	// [영훈] Season출석 이벤트 중이라고 알림
	if ( (kAttendDay.GetDateVary() >= clAttendEventStart.GetDateVary()) &&
		(kAttendDay.GetDateVary() <= clAttendEventEnd.GetDateVary()) 
	)
	{
		// 클라이언트에게 이벤트 중이라고 알림
		SendServerResponseMsg( 0, SRVAL_NOTICE_SEASON2_ATTEND, 0, 0, siCharID );

		// 시즌2 
		sDBRequest_Attend clMsg(siPersonID, siCharID, &clAttendEventStart, &clAttendEventEnd, ATTEND_EVENTTYPE_SEASON2 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}


	// [영훈] PC방 프리미엄 강화 - 네잎클로버 지급
	if ( ( clPersonInfo.clBI.bPCRoom == true ) && (pclMsg->clInfo.BasicInfo.bAttendToday[ ATTEND_EVENTTYPE_PCROOM ] == false) )
	{
		sDBRequest_Attend clMsg(siPersonID, siCharID, &kAttendDay, &kAttendDay, ATTEND_EVENTTYPE_PCROOM );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	//------------------------------------------
	// [기형] 휴면 계정 객체
	//------------------------------------------
	CDormancySystem *pclDormancySystem = this->pclDormancySystem;
	CDormancyEquipItemRewardServer *pclDormancyServer = NULL;
	CDormancyPointRewardServer *pclDormancyPointServer = NULL;
	cltCharServer *pclCharServer = pclCM->GetCharServer(id);
	if(NULL != pclDormancySystem)
	{
		pclDormancyServer = (CDormancyEquipItemRewardServer *)pclDormancySystem->GetDormancyEquipItemReward();
		pclDormancyPointServer = (CDormancyPointRewardServer *)pclDormancySystem->GetDormancyPointReward();
	}
	// 휴면 계정 정보 전송
	if(NULL != pclDormancyPointServer)
	{
		pclDormancyPointServer->SendClientDormancyInfo(pclCharServer);
		pclDormancyPointServer->WaringExpiration(pclCharServer);
	}
	// 휴면 계정 시스템 - 장비 보급 상자 지급 관련
	if(NULL != pclDormancyServer)
	{
		// 보급 상자가 보급 되지 않았다면
		if( clPersonInfo.clDormancyInfo.GetGiveDormancyEquipItem() == FALSE)
			pclDormancyServer->GiveEquipBox(pclCharServer);
	}

	// [ 손성웅] 추천인 시스템 변경
	// [영훈] 임시로 유럽은 뺀다
	if ( clPersonInfo.clBI.clRecommenderInfo.siPersonID == 0 )
	{
		cltGameMsgResponse_RecommendPersonAvailable clinfo( true );
		cltMsg clMsg(GAMEMSG_RESPONSE_RECOMMENDPERSONAVAILABLE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		//KHY - 1024 - 한게임 VIP 이벤트- 기간내 최초 캐릭터.
		//by LEEKH 2007.10.30 - 기간 변경
		if (pclClient->IsCountrySwitch(Switch_HanGameVIPEvent) )
		{					
			_SYSTEMTIME sStartEventDay , sEndEventDay;

			ZeroMemory(&sStartEventDay,	sizeof(_SYSTEMTIME));
			ZeroMemory(&sEndEventDay,	sizeof(_SYSTEMTIME));

			sStartEventDay.wYear    = 2006;
			sStartEventDay.wMonth   = 11;
			sStartEventDay.wDay     = 8;
			sStartEventDay.wHour    = 0;
			sStartEventDay.wMinute  = 0;

			sEndEventDay.wYear		= 2006;
			sEndEventDay.wMonth		= 11;
			sEndEventDay.wDay		= 30;
			sEndEventDay.wHour		= 0;
			sEndEventDay.wMinute	= 0;

			SI32 startEventdatevary = pclClient->GetMinuteFromsTime(sStartEventDay);
			SI32 endEventdatevary   = pclClient->GetMinuteFromsTime(sEndEventDay);

			_SYSTEMTIME fTimeDatevary;  // 현재 시간이 최초이다.  = 최초 계정 생성 시간.
			GetLocalTime( &fTimeDatevary );

			SI32 firstCreatTimedatevary = pclClient->GetMinuteFromsTime(fTimeDatevary);

			if((startEventdatevary <= firstCreatTimedatevary)&&(endEventdatevary >= firstCreatTimedatevary))
			{
				SendLog_SetEventCouponInfo( pclchar->pclCI->clBI.szAccountID, 
											(TCHAR*)pclCM->CR[siPersonID]->pclCI->clBI.GetName()
											,siPersonID, 
											HAN_GAME_VIP_EVENT,
											1	); // 1 = 첫번째로 만들어진 캐릭터임.
			}
		}
	}


	// 투표 진행 상태이고, 후보를 이전에 뽑은 적이 없는 경우 투표 가능
	if ( pclVoteMgr->IsPlayStatus() &&  clPersonInfo.clBI.siVoteKingSelectionIndex == 0 )
	{	
		// 레벨 40 이상만 투표에 참여 가능
		if ( clPersonInfo.clIP.GetLevel() >= Const_CanVote_MinLevel )
		{
			SendServerResponseMsg( 0, SRVAL_NOTICE_WARPTOPOLL_MAP, 0, 0, siCharID );
		}
	}

	// 서버시간을 로그인때 한번 전송한다.
	cltGameMsgResponse_ServerTime clTime(sTime);
	cltMsg clTimeMsg(GAMEMSG_RESPONSE_SERVERTIME, sizeof(clTime), (BYTE*)&clTime);
	pclchar->SendNetMsg((sPacketHeader*)&clTimeMsg);

	// 채팅 블록 시간을 가져온다.
	sDBRequest_GetMuteTime clMsgMute( siCharID, siPersonID );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsgMute);

	//[진성] 엘릭서
	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
	{ 
		sDBRequest_Elixir_Get clInfo( id, pclCM->CR[id]->pclCI->GetPersonID() );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clInfo);
	}

	// [영훈] 결혼 시스템 : 관련 정보를 받아온다
	if ( IsCountrySwitch(Switch_WeddingSystem) )
	{
		sDBRequest_Get_Marry_Info clMarryInfo( siPersonID );
		pclGameDBProcess->SendMsg( (sPacketHeader*)&clMarryInfo );
	}
	// [성웅] 가족 시스템 : 가족 정보를 받아 온다.
	sDBRequest_Get_FamilyInfo clFamilyInfo( siPersonID );
	pclGameDBProcess->SendMsg( (sPacketHeader*)&clFamilyInfo );

	// 수호정령 받아오기
	if ( IsCountrySwitch(Switch_SoulGuard) )
	{
		// 일단 보내기전에 초기화 해주면 계정간 캐릭터 변경시 정보가 남아 있지 않는다
		if ( pclchar->pclSoulGuard )
		{
			pclchar->pclSoulGuard->Init();
		}

		sDBRequest_SoulGuardGet clSoulGuardInfo( siPersonID );
		pclGameDBProcess->SendMsg( (sPacketHeader*)&clSoulGuardInfo );

		sDBRequest_SoulGuardHouse_Get clSoulGuardHouseInfo( siPersonID );
		pclGameDBProcess->SendMsg( (sPacketHeader*)&clSoulGuardHouseInfo );
	}

	// [진성] 스킬북 관련 정보 요청.
	if ( IsCountrySwitch(Switch_SkillBook) )
	{
		if( pclchar->pclCharSkillBookInfo ) pclchar->pclCharSkillBookInfo->Clear();
		
		sDBRequest_SkillBook_MagicInfo_Get clSkillBookMagicInfoGet( id, siPersonID );
		pclGameDBProcess->SendMsg( (sPacketHeader*)&clSkillBookMagicInfoGet );
	}

	// [기형] 발렌타인 데이 버프 데이터 전송
	CValentineEventServerMgr *pclValentineEventServerMgr = (CValentineEventServerMgr *)m_pclValentineEventMgr;

	if ( NULL != pclValentineEventServerMgr)
	{
		if(pclValentineEventServerMgr->IsEventPeriod())
		{
			pclValentineEventServerMgr->SendNewBufInfo(pclCharServer);
			pclValentineEventServerMgr->SendBufInfo(pclCharServer);
		}
	}

	// 1. 군주데이 이벤트 중이라면 클라이언트에게 알려줍니다.
	if( IsCountrySwitch( Switch_Server_Event ) )
	{
		if(pclEventTimeManager->InEventTime(TEXT("GoonzuDay_Week"), &sTime) == true)
		{
			cltGameMsgResponse_EventTime_Update sendMsg(TEXT("GoonzuDay_Week"), true);
			cltMsg clMsg(GAMEMSG_REQUEST_EVENTTIME_UPDATE, sizeof(sendMsg), (BYTE*)&sendMsg);

			cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];
			if(pclchar)
			{
				pclchar->SendNetMsg((sPacketHeader*)&clMsg);

				// [지연] 군주데이미션 : 군주데이 미션을 이미 받았었는지 디비에 질문
				cltEventTime* pParentEventTime = NULL;
				pParentEventTime = pclEventTimeManager->GetEvent( TEXT("GoonzuDay_Week") );
				cltEventTime* pChildEventTime = NULL;
				pChildEventTime = pclEventTimeManager->GetEvent( TEXT("GoonzuDay_GiveMission") );

				if ( NULL != pParentEventTime && NULL != pChildEventTime )
				{
					if ( true == pParentEventTime->m_bEventActivated && true == pChildEventTime->m_bEventShoted )	// 군주데이 이벤트 중이고, 군주데이 이벤트의 차일드 미션인 군주데이미션 이벤트가 이미 수행되서 캐릭터들에게 미션을 부여하고 난 뒤에 로그인 했을 경우에만 미션 수행여부 디비에 물어봄)
					{
						sDBRequest_GoonzuDayMissionInfo_Get clSndInfo( pclchar->GetID(), pclchar->pclCI->GetPersonID() );
						pclClient->SendDBMsg( DBSELECT_BASE,(sPacketHeader*)&clSndInfo );
					}
				}
			}
		}
	}

	pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
}

// Person삭제 요청에 대한 응답. 
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONTOTALINFODELETE(sPacketHeader* pPacket)
{
	sDBResponse_PersonTotalInfoDelete* pclMsg = (sDBResponse_PersonTotalInfoDelete*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	//if(pclMsg->siResult == 1 || siServiceArea == ConstServiceArea_English)
	if(pclMsg->siResult == 1)
	{
		siDelCharNum++;

		//-------------------------------------------------------------
		// GameDBManager_World에게 모든 Person정보를 알려줄 것을 요청한다. 
		//-------------------------------------------------------------
		sDBRequest_PersonListInfoGet clMsg(pclMsg->usCharID, pclCM->CR[id]->pclCI->clBI.siIDNum);//수정필요여기서 리스트를 보냐면서
		//셀렉트 케릭터화면을 바꿀수 있으니 이곳에서 시간을 패킷에 보내도록 하자.
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);

		SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();

		sDBRequest_GeneralMeetingInfo clMsg2( villageunique );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg2);

		// 길드가 있는 캐릭이라면
		if ( pclMsg->clinfo.siUnique > 0 )
		{
			cltGuildInfo* pGuild = pclGuildManager->GetGuildInfo(pclMsg->clinfo.siUnique);
			if ( pGuild )
			{
				// 삭제된 거다
				if ( pGuild->siMasterPersonID <= 0 )
				{
					for ( SI32 i = 0 ; i < MAX_GUILD_MEMBER_NUM ; i ++ )
					{
						SI32 personid = pGuild->clMember[i].siPersonID ;
						SI32 charid = pclCM->GetIDFromPersonID(personid);
						if ( pclCM->IsValidID(charid) )
						{
							pclCM->CR[charid]->pclCI->clBI.clGuildRank.Init();

							cltGuildStatus clStatus;
							ZeroMemory(&clStatus,sizeof(cltGuildStatus));
							cltSimpleGuildRank clRank;
							clRank.Init();

							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&clStatus,&clRank,pclCM->CR[charid]->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);
						}

						personid = pGuild->clStandingMember[i].siPersonID ;
						charid = pclCM->GetIDFromPersonID(personid);
						if ( pclCM->IsValidID(charid) )
						{
							pclCM->CR[charid]->pclCI->clBI.clGuildRank.Init();

							cltGuildStatus clStatus;
							ZeroMemory(&clStatus,sizeof(cltGuildStatus));
							cltSimpleGuildRank clRank;
							clRank.Init();

							cltGameMsgResponse_Guild_SetGuildStatus clinfo(&clStatus,&clRank,pclCM->CR[charid]->GetCharUnique());
							cltMsg clMsg(GAMEMSG_RESPONSE_GUILD_SETGUILDSTATUS, sizeof(clinfo), (BYTE*)&clinfo);
							((cltCharServer*)pclCM->CR[charid])->SendNeighbourMsg(&clMsg,true);
						}
					}

					pGuild->Init();
				}

				pGuild->Set(&pclMsg->clinfo);
			}
		}
		// 객주에 팔자 주문이 있는경우 서버도 없애준다.
		for( SI32 i = 0; i < MAX_MARKET_ORDER_PER_PERSON; ++i )
		{
			SI32 index = pclMsg->clOrder[i].siIndex;
			if( index < 0 || index >= MAX_MARKET_ORDER_NUMBER )
			{
				continue;
			}

			SI32 orderitemunique	= pclMarketManager->pclOrderManager->pclOrderSell[index]->clItemData.siUnique;

			if( 0 < orderitemunique )
			{
				if( true == pclMarketManager->pclOrderManager->SetOrder( ORDERMODE_SELL, &pclMsg->clOrder[i] ) )
				{
					cltTradeOrder clorder;
					clorder.Set(&pclMsg->clOrder[i]);
					clorder.clItemData.siUnique	= orderitemunique;

					pclMarketManager->SetItemTypeOrder(&clorder, 700);
				}
			}
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 9. 5] // 캐릭터 삭제 로그쓰기.
			// pszParam1 == 아이디.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_DELCHAR, 
								0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
								0, 0, 0, 0, 0, pclCM->CR[id]->pclCI->clBI.szAccountID, NULL);
		}
	}
	
	else if(pclMsg->siResult <= 0)
	{
		switch(pclMsg->siResult)
		{
			case 0:  SendServerResponseMsg(0, SRVAL_DELPERSON_FAIL_UNKNOWN,  0, 0, pclCM->CR[id]->GetCharUnique());		break;
			case -1: SendServerResponseMsg(0, SRVAL_DELPERSON_FAIL_IDMATCHERROR,  0, 0, pclCM->CR[id]->GetCharUnique()); break;	// 주민등록번호 뒷자리가 불일치함을 Client에게 알린다.
		}
		return ;
	}

	

}

// Person삭제 요청대기 대한 응답.
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOPREDELETE(sPacketHeader* pPacket)
{
	sDBResponse_PersonTotalInfoPreDelete* pclMsg = (sDBResponse_PersonTotalInfoPreDelete*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	//if(pclMsg->siResult == 1 || siServiceArea == ConstServiceArea_English)
	if(pclMsg->siResult == 1)
	{
		siDelCharNum++;

		//-------------------------------------------------------------
		// GameDBManager_World에게 모든 Person정보를 알려줄 것을 요청한다. 
		//-------------------------------------------------------------
		sDBRequest_PersonListInfoGet clMsg(pclMsg->usCharID, pclCM->CR[id]->pclCI->clBI.siIDNum);//수정필요여기서 리스트를 보냐면서
		//셀렉트 케릭터화면을 바꿀수 있으니 이곳에서 시간을 패킷에 보내도록 하자.
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);
	}

}

// Person 정보 저장요청에 대한 응답. (별다른 조치를 취할 것이 없다.)
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONTOTALINFOSET(sPacketHeader* pPacket)
{
	sDBResponse_PersonTotalInfoSet* pclMsg = (sDBResponse_PersonTotalInfoSet*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

}


// Person의 주식 계좌 정보 요청에 대한 응답. 
void cltServer::DoMsg_DBMSG_RESPONSE_PERSONSTOCKACCOUNTGET(sPacketHeader* pPacket)
{
	sDBResponse_PersonStockAccountGet* pclMsg = (sDBResponse_PersonStockAccountGet*)pPacket;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	// Person의 주식 계좌 정보를 업데이트 한다. 
	pclCM->CR[id]->pclCI->clStock.clInfo.Set(&pclMsg->clStockAccount);
	
	// 클라이언트로 전송하게 한다. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_STOCK, true, 0);

}

// Person의 스킬 레벨을 낮춘다. 
void cltServer::DoMsg_DBMSG_RESPONSE_DECREASESKILL(sPacketHeader* pPacket)
{
	DoMsg_DBMSG_RESPONSE_INCREASESKILL(pPacket);
}


// Person의 스킬 레벨을 높인다. 
void cltServer::DoMsg_DBMSG_RESPONSE_INCREASESKILL(sPacketHeader* pPacket)
{
	sDBResponse_IncreaseSkill* pclMsg = (sDBResponse_IncreaseSkill*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->uiSkillUnique < 0 || pclMsg->uiSkillUnique >= MAX_SKILL_NUMBER)		return;

		// Person의 스킬 정보를 업데이트 한다. 
		SI32 oldskilllevel		= pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiLevel;
		SI32 oldtotalskilllevel	= oldskilllevel + pclCM->CR[id]->pclCI->clCharSkill.GetSkillExpLevel(pclMsg->uiSkillUnique);

		pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiSkillUnique	= pclMsg->uiSkillUnique;
		pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiLevel		= pclMsg->uiSkillLevel;

		// 클라이언트로 전송하게 한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_SKILL, true, 0);

		//Person의 SkillBonus를 업데이트 한다. 
		pclCM->CR[id]->pclCI->clIP.SetSkillBonus(pclMsg->siSkillBonus);

		// 클라이언트로 전송하게 한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);
		
		// 이용권을 소모해서 기술을 뺀 경우, 아이템을 업데이트 한다. 
		if(pclMsg->siMode == DECSKILLMODE_TICKET || pclMsg->siMode == DECSKILLMODE_WEAPONSKILL|| pclMsg->siMode == DECSKILLMODE_ALLSKILLPOINT  )
		{
			if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
			{
				pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemPos].Set(&pclMsg->clItem);

				// 클라이언트로 업데이트 된 정보를 보낸다. 
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				// PCK - 아이템 사용 로그를 남긴다.
				cltServer * pclServer = (cltServer*)pclClient;
				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
					USEITEM_REASON_SKILLRESET_TICKET, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUseItem, 0, 0, 0, 0, 0, 
					pclMsg->siItemPos, 0, 0, 0, 0, 0, NULL, NULL);
			}
		}

		// 경험기술 레벨이 올랐다면, 
		SI32 totalskilllevel = pclMsg->uiSkillLevel + pclCM->CR[id]->pclCI->clCharSkill.GetSkillExpLevel(pclMsg->uiSkillUnique);

		if(oldtotalskilllevel < totalskilllevel)
		{
			SendServerResponseMsg(0, SRVAL_SETSKILL,  pclMsg->uiSkillUnique, totalskilllevel, pclCM->CR[id]->GetCharUnique());

			if ( IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
				if ( pclSE_Quest )
				{
					SI32 siAmount = max( 1, ((cltCharServer*)pclCM->CR[id])->siQuestCount );
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_SKILLUP, totalskilllevel, siAmount );
				}
			}
/*
			TCHAR szName[MAX_PLAYER_NAME];
			MStrCpy( szName, pclCM->CR[id]->GetName(), MAX_PLAYER_NAME );
			
			//KHY - 1205 - 유저레벨업 공지
			if ( pclCM->CR[id]->pclCI->clBI.clGuildRank.IsGuildMember() == true ) //길드.
			{
				cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo(pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex());
				if ( pGuild )
				{
					cltGameMsgResponse_LevelUpNotice clinfo(szName, 0, totalskilllevel , pclMsg->uiSkillUnique , 1);
					cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
					pclClient->pclCM->SendAllGuildMemberMsg((sPacketHeader*)&clMsg,pGuild->siUnique);

				}
			}

			if(pclCM->CR[id]->pclCI->clBI.siHomeVillage > 0 && pclCM->CR[id]->pclCI->clBI.siHomeVillage <= CUR_VILLAGE_LIMIT) //마을 
			{

				//KHY - 1205 - 유저레벨업 공지
				cltGameMsgResponse_LevelUpNotice clinfo(szName, 0, totalskilllevel , pclMsg->uiSkillUnique , 2);
				cltMsg clMsg(GAMEMSG_RESPONSE_LEVELUPNOTICE, sizeof(clinfo), (BYTE*)&clinfo);
				pclClient->pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg,pclCM->CR[id]->pclCI->clBI.siHomeVillage);

			}
*/
		}
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 11] // 캐릭터의 스킬상승과 감소. 수정 - PCK : 08.09.19
		// param1 == 설정된 스킬 유니크.  
		// param2 == 설정된 스킬 레벨, 
		// param3 == 결과로 변경된 스킬보너스 포인트, 
		// param4 == 모드. 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_CHANGE, 
			pclMsg->siReason, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUseItem, 0, 0, 0, 0, 0, 0, 
			pclMsg->uiSkillUnique, pclMsg->uiSkillLevel, pclMsg->siSkillBonus, pclMsg->siMode, 0, 
			NULL, NULL);
	}
}

// Person의 스킬 레벨을 높인다. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETSKILLEXP(sPacketHeader* pPacket)
{
	// PCK : 로그용 추가
	sDBResponse_SetSkillExp*	pclMsg = (sDBResponse_SetSkillExp*)pPacket;

	// PCK : PersonID를 근거로 CharID를 찾음.(PersonID넣지말자!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// param1 == 기술 유니크, 
	// param2 == 기술 경험치.
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_SET_SKILL_EXP, 
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
									pclMsg->uiSkillUnique, pclMsg->siSkillExp, 0, 0, 0, NULL, NULL);
}

// Person의 레벨 정보를 설정한다. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETLEVELINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetLevelInfo* pclMsg = (sDBResponse_SetLevelInfo*)pPacket;

	if ( pclMsg->siResult != 1 )
	{

		SI32 id	= pclMsg->usCharID;
		if(pclCM->IsValidID(id) == FALSE)return ;

		
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

		// PCK : 레벨 정보를 설정하는 부분에 캐릭터 정보가 다들어와서 필요없는 로그라 판단되어 주석처리함. (08.06.20)
		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [로그추가 : 황진성 2007. 10. 15] // 레벨 정보를 설정
		//	// 
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_SETLEVELINFO,
		//									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		//									0, 0, 0, 0, 0,  NULL, NULL);
		//}
	

		if(pclchar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
		{
			// 부적절한 정보가 저장되었으므로 사용자를 내보낸다. 
			pclchar->bCloseSocketSwitch		= true;
			pclchar->dwCloseSocketTimer		= 10;
			
			SendNoticeMsg(-1, 0, id, TEXT("부적절한 데이터로 인해 접속을 종료합니다."));
			
#ifdef _CHINA
			pclLog->FilePrint( TEXT("ErrorSerLevelInfo"), TEXT("SetLevelInfo name:%s"),
				pclchar->GetName());
#else
			pclLog->FilePrint( TEXT("Config\\ErrorLog.log"), TEXT("SetLevelInfo name:%s"),
				pclchar->GetName());
#endif
		}


		return;
	}
}

// 위치, 생명력, 마법력 정보 저장
void cltServer::DoMsg_DBMSG_RESPONSE_SETPOSLIFEMANA(sPacketHeader* pPacket)
{
	// PCK:  로그를 남기기 위해서 작성
	sDBResponse_SetPosLifeMana*	pclMsg = (sDBResponse_SetPosLifeMana*)pPacket;

	// PCK : PersonID를 근거로 CharID를 찾음.(PersonID넣지말자!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( false == pclCM->IsValidID(CharID) )
	{
		return;
	}

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	// param1 = Life, 
	// param2 = Mana, 
	// param3 = Map Index, 
	// param4 = Pos x, 
	// param5 = Pos y
	// charparam1 = "PlaySec = %d, PlayEventSec = %d"
	TCHAR szCharParam[50] = { '\0', };
	StringCchPrintf(szCharParam, sizeof(szCharParam), TEXT("PlaySec = %d, PlayEventSec = %d"), pclMsg->siPlaySecond, pclMsg->siPlayEventSecond);

	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_SETPOSLIFEMANA,
		0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
		pclMsg->siLife, pclMsg->siMana, pclMsg->clPos.GetMapIndex(), pclMsg->clPos.GetX(), pclMsg->clPos.GetY(),
		szCharParam, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_BBB_SET_REWARDMONEY(sPacketHeader* pPacket)
{
	//sDBResponse_BBB_Set_RewardMoney* pclMsg = (sDBResponse_BBB_Set_RewardMoney*) pPacket;

}

void cltServer::DoMsg_DBMSG_RESPONSE_BBB_GET_REWARD_MONEY(sPacketHeader* pPacket)
{ 
	sDBResponse_BBB_Get_RewardMoney* pclMsg = (sDBResponse_BBB_Get_RewardMoney*)pPacket;

	if(m_pServer_BBBMgr)
	{
		m_pServer_BBBMgr->m_siTotalMoney = pclMsg->m_siTotalRewardPriceWithDraw;

	}
}

// [지연] 군주데이미션 : 미션 부여 여부에 대한 디비의 응답
void cltServer::DoMsg_DBMSG_RESPONSE_GOONZUDAYMISSIONINFO_GET(sPacketHeader* pPacket)
{
	// 디비에서 넘어온 군주데이미션 수행 여부에 대한 날짜 정보를 토대로 미션을 부여할지 말지를 결정
	// (저장된 날짜는 최종적으로 미션을 부여 받은 날짜이므로 그게 현재 군주데이 기간에 포함이 되면 미션을 주지 않고 포함이 안되면 미션을 준다)

	if (  false == pclEventTimeManager->InEventTime(TEXT("GoonzuDay_Week"), &sTime) ) return;		// 군주데이 이벤트 기간 아니면 그냥 리턴

	sDBResponse_GoonzuDayMissionInfo_Get* pRcvInfo = (sDBResponse_GoonzuDayMissionInfo_Get*)pPacket;
	if ( NULL == pRcvInfo ) return;

	// 정상적으로 접속중인 유저인가? 아니면 그냥 리턴 맞으면 아래 진행
	SI32 id = 0;
	id = pRcvInfo->m_usCharID;
	if ( false == pclCM->IsValidID(id) ) return;
	if ( false == pclCM->CR[id]->IsValidConnection() ) return;
	cltCharServer* pCharServer = (cltCharServer*)pclCM->CR[id];

	// 디비에 저장되있던 이 캐릭터의 군주데이 미션 수행 시간과 현재 군주데이 이벤트 시간을 비교해서 아직 미션을 수행하지 않았다면 미션을 부여해준다.
	cltEventTime* pGoonzuDayEvent = NULL;
	cltEventTime* pGoonzuDayMissionEvent = NULL;
	SYSTEMTIME stCurrentTime;		// 현재시간
	GetLocalTime( &stCurrentTime );

	pGoonzuDayEvent			= pclEventTimeManager->GetEvent( TEXT("GoonzuDay_Week") );
	pGoonzuDayMissionEvent	= pclEventTimeManager->GetEvent( TEXT("GoonzuDay_GiveMission") );
	if ( NULL == pGoonzuDayEvent || NULL == pGoonzuDayMissionEvent ) return;
	if ( false == pGoonzuDayEvent->m_bEventActivated || false == pGoonzuDayMissionEvent->m_bEventShoted ) return;

	// 군주데이 미션 최종 수행 날짜와 현재의 군주데이 이벤트 기간을 비교해 아직 수행 안했는지 판별

	// 그전에 디비에서 넘어온 날짜 정보가 0 인경우 (한번도 안해서 초기값이 넘어온경우에 대해서 먼저 처리)
	if ( 0 == pRcvInfo->siCount || (0 == pRcvInfo->m_MissionGetTime.wYear && 0 == pRcvInfo->m_MissionGetTime.wMonth && 0 == pRcvInfo->m_MissionGetTime.wDay) )
	{
		pclEventTimeManager->GiveMission( pCharServer );
	}
	else
	{
		// ** 군주데이 이벤트 기간의 EndTime이 값이 세팅이 안되어 있고 65535 맥스값으로 초기화 되어 있기 때문에 끝나는 날짜를 정확히 비교할수가 없다. 그래서 아래 조건식은 뺐고, 현재 날짜와 디비에 저장되어있던 캐릭터의 군주데이미션 최종 부여 날짜만을 가지고 비교를 한다. 
		if ( pRcvInfo->m_MissionGetTime.wYear		!= stCurrentTime.wYear 
			|| pRcvInfo->m_MissionGetTime.wMonth	!= stCurrentTime.wMonth
			|| pRcvInfo->m_MissionGetTime.wDay		!= stCurrentTime.wDay )
		{
			pclEventTimeManager->GiveMission( pCharServer );
		}
	}
}

// 건강 정보 저장.
void cltServer::DoMsg_DBMSG_RESPONSE_SETHEALTH(sPacketHeader* pPacket)
{
	
}

// 유저 아이디 받아옮
void cltServer::DoMsg_DBMSG_RESPONSE_USERID( sPacketHeader* pPacket )
{
	sDBResponse_Userid* pclMsg = (sDBResponse_Userid*)pPacket;

	if ( pclMsg->siResult < 1 )
	{
		return;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return ;

	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		
		if( pclMsg->bShowPuchikomi == false )
		{
			SendServerResponseMsg( 0 , SRVAL_PUCHIKOMI_FAIL_OP_REJECTION , 0 , 0 , pclCM->CR[id]->GetCharUnique() );
		
			return;
		}


		UI08 md5buf[256] = "" ;
		char buffermd5ID[256] = "" ;
		char buffermd5PassWord[256] = "" ;

		char tmp[256] = "" ;

		sprintf(tmp,"%s",  pclMsg->strUserID );	
		SI32 tmpsize = strlen(tmp);

		// URLEncode
		CString str ;
		str.SetString(tmp,tmpsize);
		CString unicodeID = URLEncode(str);

		// MD5
		SI32 md5size = unicodeID.GetLength() ;
		memcpy(md5buf,unicodeID.GetBuffer(md5size),md5size);

		md5_string(md5buf, buffermd5ID, md5size);

		cltGameMsgResponse_UserPuchikomiURL clinfo(buffermd5ID);	
		cltMsg clMsg(GAMEMSG_RESPONSE_USERPUCHIKOMIURL,sizeof(clinfo),(BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_RECOMMENDPERSON( sPacketHeader* pPacket )
{
	sDBResponse_RecommendPerson* pclMsg = (sDBResponse_RecommendPerson*)pPacket;

	SI32 id	= pclMsg->siCharID;

	if(pclCM->IsValidID(id) == FALSE)
		return ;

	//	if( pclMsg->siResult != 1 ) // 그냥 리턴 하도록 되어 있지만 이 리절트 값을 정해서 서버 메세지를 날려주자
	if( _tcslen(pclMsg->strUserName) < 1) // 이름의 길이를 봐서
	{
		SendServerResponseMsg(0, SRVAL_FAIL_RECOMMANDPERSON_CANCEL,  0, 0, id);
		return ;
	}

	else if( pclMsg->siResult != 1 )
	{

		//todo:
		SendServerResponseMsg(0, SRVAL_FAIL_RECOMMANDPERSON,  0, 0, id);

		return ;
	}
	else {
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if( pclchar == NULL ) return ;
		if( pclMsg->uiSlot < 0 || pclMsg->uiSlot >= MAX_CHAR_PER_USER )		return;

		if( pclchar->pclCharListInfo != NULL &&
			pclchar->pclCharListInfo[pclMsg->uiSlot].clBI.clPerson.siPersonID == pclMsg->siPersonID &&
			pclCM->CR[id]->pclCI->clBI.siIDNum == pclMsg->siIDNum )
		{
			if ( pclMsg->strRecommenderUserName != NULL || _tcslen( pclMsg->strRecommenderUserName ) > 0 )
			{
				cltLetterMsg_Recommender clletter( ( TCHAR*) pclMsg->strRecommenderUserName );
				SendLetterMsg(pclMsg->siRecommendPersonID, (cltLetterHeader*)&clletter );
			}

			pclCM->CR[id]->pclCI->clBI.clRecommenderInfo.siPersonID = pclMsg->siRecommendPersonID;

			cltGameMsgResponse_RecommendPerson clinfo( pclMsg->strUserName );
			cltMsg clMsg(GAMEMSG_RESPONSE_RECOMMENDPERSON, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [로그추가 : 황진성 2007. 9. 10] // 추천인 등록(추천인을 등록)
				//pszParam1 == 추천인 이름.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_RECOMMENDER_ADD, 
					0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->siRecommendPersonID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
					0, 0, 0, 0, 0, pclMsg->strRecommenderUserName, NULL);
			}

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 9. 7] // 추천을 받음
			//	//pszParam1 == 피추천인 이름
			//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_RECOMMENDER_RECOMMENDPERSON, 
			//		0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			//		0, 0, 0, 0, 0, pclMsg->strUserName, NULL);
			//}
		}


		return;
	}
}



void cltServer::DoMsg_DBMSG_RESPONSE_SETHORSE(sPacketHeader* pPacket)
{
	sDBResponse_SetHorse *pclMsg = (sDBResponse_SetHorse *)pPacket;
	
	if( pclMsg->siResult != 1 )						return;
	
	SI32 id	= pclMsg->usCharID;

	// PCK : 수정 - 말 설정 로그 수정 (Reason에 있는부분을 로그로 찍게 빼낸것 삭제.)
	if(pclCM->IsValidID(id) == TRUE && pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		TCHAR	szHorseInfo[50] = {'\0', };
		StringCchPrintf(szHorseInfo, sizeof(szHorseInfo), "Life : %d,  Str : %d, Dex : %d, Mag : %d, MoveSpeed : %d",
			pclMsg->cIHorse.siLife, pclMsg->cIHorse.siStr, pclMsg->cIHorse.siDex, pclMsg->cIHorse.siMag, pclMsg->cIHorse.siMoveSpeed);

		cltServer * pclServer = (cltServer*)pclClient;

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 10] // 말 설정.
			// pszParam1 == 말의 정보

			cltServer * pclServer = (cltServer*)pclClient;
			pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSESET, LOGCOMMAND_INDEX_HORSESET_SET,
				pclMsg->siReason, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, szHorseInfo, NULL);
		}
	}
	
	// 말이 죽었을때만 처리한다.
	if(pclMsg->siReason	 != SETHORSE_REASON_DIE)	return;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		//cyj 말 죽을떄 ParametaBox갱신하도록 추가
		pclCM->CR[id]->UnrideHorse();
		pclCM->CR[id]->SetParametaBoxAction(true);	// ParametaBoxAction을 수행한다. 

		((cltCharServer*)pclCM->CR[id])->SendNeighbourMyHorseStatus(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentShowHorse);

		// 클라이언트에 사실을 알린다. 
		SendServerResponseMsg(0, SRVAL_HORSEDIE,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETAUTOFOOD(sPacketHeader* pPacket)
{
	sDBResponse_SetAutoFood *pclMsg = (sDBResponse_SetAutoFood*)pPacket;

	// 특별히 할 일이 없다. 
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETRIDEHORSE(sPacketHeader* pPacket)
{
	sDBResponse_SetRideHorse *pclMsg = (sDBResponse_SetRideHorse *)pPacket;

	if( pclMsg->siResult != 1 )						return;

	SI32 id = pclMsg->usCharID;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if(pclCM->IsValidID(id) == false)				return;
	if(pclchar->pclCI->GetPersonID() != pclMsg->siPersonID)return ;

//	if(pclMsg->siIndex >= 0)
	if(pclMsg->siCurrentHorseRIDEHORSE == true)
	{
		
		// 대상자에게 말을 태운다.
		if( pclCM->CR[id]->RideHorse() == false)return ;

		pclCM->CR[id]->SetParametaBoxAction(true);	// ParametaBoxAction을 수행한다. 

		cltGameMsgResponse_RideOrUnrideHorse clinfo(pclMsg->siIndex);
		cltMsg clMsg(GAMEMSG_RESPONSE_RIDEHORSE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	else
	{
		pclCM->CR[id]->SetParametaBoxAction(true);	// ParametaBoxAction을 수행한다. 

		cltGameMsgResponse_RideOrUnrideHorse clinfo(pclMsg->siIndex);
		cltMsg clMsg(GAMEMSG_RESPONSE_UNRIDEHORSE, sizeof(clinfo), (BYTE*)&clinfo);

		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	
	//---------------------------------------
	// 이웃들에게 말을 탔음을 알린다. 
	//---------------------------------------
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
	
}

// 말 시세 설정
void cltServer::DoMsg_DBMSG_RESPONSE_SETCURRENTHORSEPRICE(sPacketHeader* pPacket)
{
	sDBResponse_SetCurrentHorsePrice *pclMsg = (sDBResponse_SetCurrentHorsePrice *)pPacket;
	
	if ( pclMsg->siResult != 1 )
	{
		pclLog->FilePrint( TEXT("Config/CurrentHorsePrice.log"), TEXT("DoMsg_DBMSG_RESPONSE_SETCURRENTHORSEPRICE pclMsg->siResult = %d"), pclMsg->siResult );
		return;
	}

	if ( pclMsg->siHorseUnique > 0 )
	{
		bHorseCurrentPriceSet = true;
		siHorseTradeCount = 0;
		siHorseCurrentPrice = pclMsg->siHorseCurrentPrice;
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [로그추가 : 황진성 2007. 10. 11] // 말 시세.
		// param1 == 말 종류, param2 == 말 현재 가격.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSEMARKET, LOGCOMMAND_INDEX_HORSEMARKET_PRICESET, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, NULL, 0, 0, 0, 0, 
										pclMsg->siHorseUnique, pclMsg->siHorseCurrentPrice, 0, 0, 0, NULL, NULL);

	}

	return;
}

// 말 시세 얻어옮
void cltServer::DoMsg_DBMSG_RESPONSE_GETCURRENTHORSEPRICE(sPacketHeader* pPacket)
{
	sDBResponse_GetCurrentHorsePrice *pclMsg = (sDBResponse_GetCurrentHorsePrice *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		pclLog->FilePrint( TEXT("Config/CurrentHorsePrice.log"), TEXT("DoMsg_DBMSG_RESPONSE_GETCURRENTHORSEPRICE pclMsg->siResult = %d"), pclMsg->siResult );
		return;
	}

	if ( pclMsg->siHorseUnique > 0 )
	{
		bHorseCurrentPriceSet = true;
		siHorseCurrentPrice = pclMsg->siHorseCurrentPrice;
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HORSENAMECHANGE(sPacketHeader* pPacket)
{
	sDBResponse_HorseNameChange *pclMsg = (sDBResponse_HorseNameChange *)pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if(pclMsg->siHorseIndex < 0 || pclMsg->siHorseIndex >= MAX_HORSE_PER_PERSON)
		return;

	SI32 id	= pclMsg->siCharID;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if ( pclMsg->strHorseName == NULL || _tcslen( pclMsg->strHorseName ) < 1 )
		{
			return;
		}

		cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetHorse(pclMsg->siHorseIndex);
		if(pclHorse != NULL)
		{
			MStrCpy( pclHorse->szName, pclMsg->strHorseName, MAX_HORSE_NAME );
		}

		cltGameMsgResponse_HorseNameChange clinfo( pclMsg->siHorseIndex, pclMsg->strHorseName );
		cltMsg clMsg(GAMEMSG_RESPONSE_HORSENAMECHANGE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// 클라이언트로 전송하게 한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_HORSE, true, 0);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 15] // 말 이름 변경.
			// param1 == 말 번호, pszParam1 == 말 이름.
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSESET, LOGCOMMAND_INDEX_HORSESET_NAMECHANGE, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
											pclMsg->siHorseIndex, 0, 0, 0, 0, pclMsg->strHorseName, NULL);
		}
	}
	
	return;
}

// Person의 스킬 레벨을 높인다. 
void cltServer::DoMsg_DBMSG_RESPONSE_INCREASEMASTERSKILL(sPacketHeader* pPacket)
{
	sDBResponse_IncreaseMasterSkill* pclMsg = (sDBResponse_IncreaseMasterSkill*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 11] // 해당 스킬 레벨로의 경험이 증가. <MASTER>. 
		// param1 == 설정된 스킬 유니크.
		// param2 == 설정된 스킬 레벨.
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_INCREASE_SKILL_MASTER, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->uiSkillUnique, pclMsg->uiSkillLevel, 0, 0, 0, NULL, NULL);
	}
	
	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if( pclMsg->uiSkillUnique < 0 || pclMsg->uiSkillUnique >= MAX_SKILL_NUMBER)		return;

		// Person의 스킬 정보를 업데이트 한다. 
		SI32 oldskilllevel		= pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiLevel;
		SI32 oldtotalskilllevel	= oldskilllevel + pclCM->CR[id]->pclCI->clCharSkill.GetSkillExpLevel(pclMsg->uiSkillUnique);

		pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiSkillUnique	= pclMsg->uiSkillUnique;
		pclCM->CR[id]->pclCI->clCharSkill.clSkill[pclMsg->uiSkillUnique].uiLevel		= pclMsg->uiSkillLevel;

		// 클라이언트로 전송하게 한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_SKILL, true, 0);

		// 클라이언트로 전송하게 한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);
		
		// 경험기술 레벨이 올랐다면, 
		SI32 totalskilllevel = pclMsg->uiSkillLevel + pclCM->CR[id]->pclCI->clCharSkill.GetSkillExpLevel(pclMsg->uiSkillUnique);

		if(oldtotalskilllevel < totalskilllevel)
		{
			SendServerResponseMsg(0, SRVAL_SETSKILL,  pclMsg->uiSkillUnique, totalskilllevel, pclCM->CR[id]->GetCharUnique());

			if ( IsCountrySwitch(Switch_Server_Event) )
			{
				CNServerEvent_Quest* pclSE_Quest =  (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
				if ( pclSE_Quest )
				{
					SI32 siAmount = max( 1, ((cltCharServer*)pclCM->CR[id])->siQuestCount );
					pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_SKILLUP, totalskilllevel, siAmount );
				}
			}
		}

	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_GUILTYINFORECORD(sPacketHeader* pPacket)
{
	sDBResponse_GuiltyInfoRecord *pclMsg = (sDBResponse_GuiltyInfoRecord *)pPacket;

	if ( pclMsg->siResult < 1 )	return;

	SI32 id	= pclMsg->siCharID;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 15] // DB에 범죄 정보를 저장.
			// param1 == 총 수감시간
			// param2 == 남은 수감시간
			// param3 == 총 저지른 범죄횟수
			// pszparam1 == 범죄 이유
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRISON, LOGCOMMAND_INDEX_GUILTY_INFORECORD, 
											0, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
											pclMsg->cIGuiltyInfo.siTotalPrisonSecond, pclMsg->cIGuiltyInfo.siLeftPrisonSecond, pclMsg->cIGuiltyInfo.siTotalPrisonNum, 0, 0, 
											pclMsg->cIGuiltyInfo.szPrisonReason, NULL);
		}
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETMINISTER(sPacketHeader* pPacket)
{
	sDBResponse_SetMinister * pclMsg = ( sDBResponse_SetMinister*)pPacket;

	SI32 userid = 0 ;

	if ( pclMsg->siResult == 1 )
	{
		// 자동이 아닌 수동으로 네잎클로버를 설정한다.
/*		if(pclClient->IsCountrySwitch(Switch_FourLeaf))
		{
			//[진성] 군주 선출되면 현재 사용가능한 네잎크로버를 변경한다.
			if( GRANK_KING == pclMsg->siMinister )
			{
				SI32 siCurFourLeafUnique = 0;
				
					 if( ITEMUNIQUE(2755) == siFourLeafUnique )	siCurFourLeafUnique = ITEMUNIQUE(2754);
				else if( ITEMUNIQUE(2754) == siFourLeafUnique ) siCurFourLeafUnique = ITEMUNIQUE(2755);
				else											siCurFourLeafUnique = ITEMUNIQUE(2754);	// 둘중 아무것도 아니면 하나 세팅.	
				
				sDBRequest_SetFourLeaf clMsg( siCurFourLeafUnique );
				SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
			}
		}*/

		cltSimpleRank pclrank ;
		pclrank.Init();

		if ( pclMsg->siTempPersonId )
		{
			userid = pclCM->GetIDFromPersonID(pclMsg->siTempPersonId);
			if ( pclCM->IsValidID(userid) )
			{
				pclCM->CR[userid]->pclCI->clBI.uiGRank = 0 ;
				SendServerResponseMsg(0, SRVAL_MINISTER_FIRE_MINISTER,  0, 0, pclCM->CR[userid]->GetCharUnique());
			}

			cltLetterMsg_Fire clletter(&pclrank,&pclTime->clDate,pclMsg->siMinister);
			SendLetterMsg(pclMsg->siTempPersonId, (cltLetterHeader*)&clletter);
		}

		if ( pclMsg->siMinisterPersonId )
		{
			userid = pclCM->GetIDFromPersonID(pclMsg->siMinisterPersonId);
			if ( pclCM->IsValidID(userid) )
			{
				pclCM->CR[userid]->pclCI->clBI.uiGRank = pclMsg->siMinister ;
				SendServerResponseMsg(0, SRVAL_MINISTER_APPOINTMENT_SETMINISTER,  pclMsg->siMinister, 0, pclCM->CR[userid]->GetCharUnique());
			}

			cltLetterMsg_BeRank clletter(&pclrank,&pclTime->clDate,pclMsg->siMinister);
			SendLetterMsg(pclMsg->siMinisterPersonId, (cltLetterHeader*)&clletter);

			// [영훈] 초보자 마을 : 공작일 경우 자동적으로 초보자 마을의 영주가 되도록 한다
			if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
			{
				if ( pclMsg->siMinister == GRANK_MINISTER2 )
				{
					BegnnerVillage_SetVillageChief( pclMsg->siMinisterPersonId );
				}
			}
		}

		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
		if ( pclCM->IsValidID(userid) == false ) return ;

		//KHY - 0629 - 해임 성공 통지 추가.
		if ( pclMsg->siTempPersonId )
			SendServerResponseMsg(0, SRVAL_MINISTER_FIRE_SUCCESS_SETMINISTER,  0, 0, pclCM->CR[userid]->GetCharUnique());
		else
			SendServerResponseMsg(0, SRVAL_MINISTER_SUCCESS_SETMINISTER,  0, 0, pclCM->CR[userid]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 10] // 판서 설정.
			// param1 == 직급.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_SET, 
											0, (cltCharServer*)pclCM->CR[userid], NULL, pclMsg->siMinisterPersonId, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siMinister, 0, 0, 0, 0, NULL, NULL);
		}
	}
	else
	{
		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
		if ( pclCM->IsValidID(userid) == false ) return ;

		SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETMINISTER,  0, 0, pclCM->CR[userid]->GetCharUnique());
	}

	if ( pclMinisterMgr )
		pclMinisterMgr->InitializeDB();
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETLIQUIDATION(sPacketHeader* pPacket)
{
	sDBResponse_SetLiquidation * pclMsg = ( sDBResponse_SetLiquidation*)pPacket;

	SI32 userid = 0 ;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

		if (pclCM->IsValidID(userid))
			SendServerResponseMsg(0, SRVAL_MINISTER_SUCCESS_SETLIQUIDATION,  0, 0, pclCM->CR[userid]->GetCharUnique());
	}
	else
	{
		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

		if (pclCM->IsValidID(userid))
			SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETLIQUIDATION,  0, 0, pclCM->CR[userid]->GetCharUnique());
	}

	if ( pclMinisterMgr )
		pclMinisterMgr->InitializeDB();
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETBONUSTIME(sPacketHeader* pPacket)
{
	sDBResponse_Goonzu_SetBonusTime * pclMsg = (sDBResponse_Goonzu_SetBonusTime *)pPacket;

	SI32 userid = 0 ;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

		if (pclCM->IsValidID(userid))
			SendServerResponseMsg(0, SRVAL_MINISTER_SUCCESS_SETBONUS,  0, 0, pclCM->CR[userid]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 16] // 보너스 타임 설정.
			// param1 == 전투 보너스 타임 시작 시간.
			// param2 == 제조 보너스 타임 시작 시간
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_GOONZU_BONUS_SET, 
											0, (cltCharServer*)pclCM->CR[userid], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siBonusTime, pclMsg->siMakeBonusTime, 0, 0, 0, NULL, NULL);
		}

	}
	else
	{
		if ( pclMsg->siPersonID <= 0 ) return ;
		userid = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

		if (pclCM->IsValidID(userid))
			SendServerResponseMsg(0,  SRVAL_MINISTER_FAIL_SETBONUS,  0, 0, pclCM->CR[userid]->GetCharUnique());
	}

	if ( pclMinisterMgr )
		pclMinisterMgr->InitializeDB();

}


void cltServer::DoMsg_DBMSG_RESPONSE_PRIZE_GAMEEVENT(sPacketHeader* pPacket)
{
	sDBResponse_Prize_GameEvent * pclMsg = ( sDBResponse_Prize_GameEvent*)pPacket;

	if ( pclMsg->siResult != 1 ) return;

	SI32 id	= pclMsg->usCharID ;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clBI.bGameEvent = pclMsg->bGameEvent ;
		pclCM->CR[id]->pclCI->clBI.bWinPrizeEvent = pclMsg->bWinPrizeEvent ;

/*		if ( pclCM->CR[id]->pclCI->clBI.bWinPrizeEvent == false ) return ; // 이벤트가 꽝이면 그냥 끝낸다.

		SI32 itemunique , itemnum ;

		pclGameEventManager->GetItemUniqueAndNumRamdomSelect(&itemunique,&itemnum);

		cltItem clItem;
		bool brareswitch = false;
		if(pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, &brareswitch) == true)
		{
			clItem.SetItemNum(itemnum);

			TCHAR buffer[256] = TEXT("") ;
			sprintf(buffer, TEXT("이벤트 당첨으로 [%s] [%d]개를 받았습니다."),clItem.GetShortName(pclItemManager),itemnum);
			SendPostOfficeItemToPerson((TCHAR*)pclCM->CR[id]->GetName(), &clItem, buffer);

			pclLog->FilePrint(TEXT("Config\\BigItem.txt"), TEXT("독도 이벤트 당첨 : [%s] [%s] [%d]개"), 
				pclCM->CR[id]->GetName(), clItem.GetShortName(pclItemManager), clItem.GetItemNum());
		}*/
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SET_WEAPONSKILL(sPacketHeader* pPacket)
{
	sDBResponse_Set_WeaponSkill* pclMsg = (sDBResponse_Set_WeaponSkill*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
    
	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->usCharID );
	if ( NULL == pclchar )
	{
		return;
	}

	if ( pclMsg->siPersonID != pclchar->pclCI->GetPersonID() )
	{
		return;
	}

	if ( 1 > pclMsg->siResult )
	{
		pclchar->bIsWeaponSkillUp = false;	// 이 값은 꼭 풀어줘야됨
		return;
	}
	
	UI08 uiSkillUnique = pclMsg->uiSkillUnique;
	if ( (0 == uiSkillUnique) || (MAX_SKILL_NUMBER <= uiSkillUnique) )
	{
		return;
	}

	//------------------------------- 서버 정보 업데이트 -------------------------------

	// 스킬 정보 업데이트
	pclchar->pclCI->clCharSkill.clSkill[uiSkillUnique].uiSkillUnique	= uiSkillUnique;
	pclchar->pclCI->clCharSkill.clSkill[uiSkillUnique].uiLevel			= pclMsg->uiSkillLevel;
	pclchar->SetUpdateSwitch( UPDATE_SKILL, true, 0 );

	// 스킬 포인트 업데이트
	pclchar->pclCI->clIP.SetSkillBonus( pclMsg->siLeftBonus );
	// 돈정보 업데이트
	pclchar->pclCI->clIP.SetMoney( pclMsg->siLeftMoney );
	pclchar->SetUpdateSwitch( UPDATE_IP, true, 0 );

	// 아이템 정보 업데이트
	SI16 siItemPos = pclMsg->siItemPos;
	if ( (PERSONITEM_INV0 <= siItemPos) && (MAX_ITEM_PER_PERSON > siItemPos) )
	{
		pclchar->pclCI->clCharItem.clItem[siItemPos].Set( &pclMsg->clLeftItem );
	}

	// 이건 꼭 풀어줘야됨
	pclchar->bIsWeaponSkillUp = false;

	//------------------------------- 클라 정보 업데이트 -------------------------------
	cltGameMsgResponse_Set_WeaponSkill clinfo( pclMsg->siResult, uiSkillUnique, pclMsg->uiSkillLevel, &pclMsg->clLeftItem, siItemPos );
	cltMsg clMsg(GAMEMSG_RESPONSE_SET_WEAPONSKILL, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	//------------------------------- 로그 -------------------------------
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 11] // 홍길동으로부터 스킬을 배울 경우 기록됨.
		// param1 == 기술 유니크, 
		// param2 == 기술 레벨, 
		// param3 == 필요 스킬 포인트, 
		// param4 == 남은 스킬 포인트, 
		// param5 == 아이템 인벤 위치

		SendLog_WriteLogToDB( LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_INCREASE_SKILL_WEAPON, 0,
			pclchar, NULL, 0, pclMsg->siMoney, pclMsg->siLeftMoney, &pclMsg->clNeedItem, pclMsg->clLeftItem.GetItemNum(), 
			0, 0, 0, 0, 0, 
			uiSkillUnique, pclMsg->uiSkillLevel, pclMsg->siNeedSkillBonus, pclMsg->siLeftBonus, pclMsg->siItemPos, NULL, NULL
		);
	}
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_COUNTATTACK_INFO(sPacketHeader* pPacket)
{
/*	sDBResponse_CountAttack_Info* pclMsg = (sDBResponse_CountAttack_Info*)pPacket;

	SI32 id = pclMsg->usCharID ;

	SI32 giveitemunique = 0 ;
	SI32 giveitemnum = 0 ;
	cltItem clItem;

	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if ( pclchar == NULL ) return ;

		if ( pclMsg->siResult >= 1 )
		{
			if ( pclMsg->siItemPos )
			{
				pclchar->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clitem);

				if ( pclMsg->siFlagNum >= 50 && pclMsg->siBeforeNum < 50 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("제왕의반지"));
					giveitemnum = 1 ;
				}
				else if ( pclMsg->siFlagNum >= 40 && pclMsg->siBeforeNum < 40 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("금괴"));
					giveitemnum = 100 ;
				}
				else if ( pclMsg->siFlagNum >= 30 && pclMsg->siBeforeNum < 30 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("소환수[진화]이용권"));
					giveitemnum = 1 ;
				}
				else if ( pclMsg->siFlagNum >= 20 && pclMsg->siBeforeNum < 20 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("말능력향상이용권"));
					giveitemnum = 1 ;
				}
				else if ( pclMsg->siFlagNum >= 10 && pclMsg->siBeforeNum < 10 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("순간이동[1일]정액권"));
					giveitemnum = 1 ;
				}
				else if ( pclMsg->siFlagNum >= 1 && pclMsg->siBeforeNum < 1 )
				{
					giveitemunique = pclItemManager->FindUniqueFromName(TEXT("쌍화탕"));
					giveitemnum = 10 ;
				}

				bool brareswitch = false;
				if(pclItemManager->MakeRandItemUnique( giveitemunique, &clItem, 0, &brareswitch) == true)
				{
					clItem.SetItemNum(giveitemnum);

					SI32 rtnvalue = 0;
					if(pclchar->InputItem(pclItemManager, &clItem, INPUTITEMPERSON_OPTION_COUNTATTACK, &rtnvalue) == false)
					{
						SendLog_InventoryFull( pclchar->pclCI->GetPersonID(),giveitemunique,giveitemnum,
							INPUTITEMPERSON_OPTION_COUNTATTACK);
					}
				}
			}

			clItem.Init();
			clItem.siItemNum = giveitemnum ;
			clItem.siUnique = giveitemunique ;

			cltGameMsgResponse_CountAttack_Info clinfo(pclMsg->siFlagNum,&clItem,pclMsg->siItemPos,&pclMsg->clitem);
			cltMsg clMsg(GAMEMSG_RESPONSE_COUNTATTACK_INFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}

		pclchar->bCheckGameEvent = false ;
	}*/
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETGREETING(sPacketHeader* pPacket)
{
	sDBResponse_SetGreeting* pclMsg = (sDBResponse_SetGreeting*)pPacket;

	SI32 id = pclMsg->siCharID;

	if( pclCM->IsAlive(id) == false)
		return;

	if(pclMsg->siResult)
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

		MStrCpy(pclchar->pclCI->clBI.szGreeting, pclMsg->szText,128);

		cltGameMsgResponse_GetGreeting clinfo( 0, TEXT(""), pclMsg->szText );
		cltMsg clMsg(GAMEMSG_RESPONSE_GETGREETING, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SETGREETING);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMAKERNAMENEW(sPacketHeader* pPacket)
{
	sDBResponse_GetItemMakerNameNew* pclMsg = (sDBResponse_GetItemMakerNameNew*)pPacket;

	SI32 id = pclMsg->siCharID;

	if (pclCM->IsValidID(id) == false)		return;

	if ( pclMsg->szName == NULL )			return;

	// 혹시 DB에도 이름이 없다면
	if ( _tcscmp(pclMsg->szName, TEXT("")) == 0 )
	{
		StringCchCopy( pclMsg->szName, sizeof(pclMsg->szName), TEXT("[NONAME]") );

		if ( 0 >= pclMsg->siSerialID )
		{
			pclMsg->siSerialID = pclMsg->siDupSerialID;
		}
	}
	
	cltPersonNameInfo clPersonInfo;
	if( false == pclNewPersonNameManager->Find( pclMsg->siSerialID, &clPersonInfo ) )
	{
		clPersonInfo.siServerUnique = pclMsg->siServerUnique;
		StringCchCopy( clPersonInfo.szPersonName, sizeof(clPersonInfo.szPersonName), pclMsg->szName );

		pclNewPersonNameManager->Insert( pclMsg->siSerialID, &clPersonInfo );
	}

	cltGameMsgResponse_GetNameFromItemSerialID clPersonName( pclMsg->siSerialID, clPersonInfo.szPersonName, clPersonInfo.siServerUnique );
	cltMsg clMsg( GAMEMSG_RESPONSE_PERSONNAME_SERIALID, sizeof(clPersonName), (BYTE*)&clPersonName );

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMAKERNAME(sPacketHeader* pPacket)
{
	sDBResponse_GetItemMakerName* pclMsg = (sDBResponse_GetItemMakerName*)pPacket;

	SI32 id = pclMsg->siCharID;

	if (pclCM->IsValidID(id) == false)
		return;

	if (pclMsg->szName == NULL)
		return;

	TCHAR buf[MAX_PLAYER_NAME];

	if (pclPersonNameManager->Find(pclMsg->siPersonID, buf) == false)
	{
		StringCchCopy(buf, MAX_PLAYER_NAME, pclMsg->szName);

		pclPersonNameManager->Insert(pclMsg->siPersonID, buf);

	}

	cltGameMsgResponse_GetNameFromPersonID clPersonName(pclMsg->siPersonID, buf);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONNAME_FROMPERSONID, sizeof(clPersonName), (BYTE*)&clPersonName);

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DOMSG_DBMSG_RESPONSE_CHANGERECOMMENDPOINT(sPacketHeader* pPacket)
{
	sDBResponse_ChangeRecommendPoint * pclMsg = (sDBResponse_ChangeRecommendPoint*)pPacket;
		
	//리절트 값에 따라 성공 유무 체크후 리턴
	if(pclMsg->siResult != 1) return;	
	
	// 해당 유저에게 쪽지를 보낸다. 
	cltLetterMsg_ChangeRecommendPoint clletter( pclMsg->szCharName,pclMsg->siLevel, pclMsg->siChangedRecommendPoint, pclMsg->siRecommendPoint );
	//SI32 letterid = SendLetterMsg( pclMsg->siRecommendPersonID , (cltLetterHeader*)&clletter);
	
	cltLetterUnit clletterunit((cltLetterHeader*)&clletter);

	SI32 letterid = pclCM->GetIDFromPersonID(pclMsg->siRecommendPersonID);
	// 게임에 접속중이면 클라이언트로 통보한다. 
	if(pclCM->IsValidID(letterid))
	{
		pclCM->CR[letterid]->SendLetterMsg(&clletterunit);
	}
	else 
	{
		if( pclMsg->siLevel > 50 )
		{
			sDBRequest_PushLetter clMsg(pclMsg->siRecommendPersonID, &clletterunit);
			pclGameDBProcess->SendMsg( DBSELECT_LETTER, (sPacketHeader *)&clMsg);
		}
	}

	// 메시지 보낸 사람인지 체크
	if(pclCM->IsValidID(pclMsg->siCharID) == false) return;
	if(pclCM->CR[pclMsg->siCharID]->pclCI->GetPersonID() != pclMsg->siPersonID ) return;

#ifdef USE_PROMOTOR_SERVER
	// 중국은 프로모터와 핸드폰 인증이 되야만 아이템과 포인트를 준다.	
	if( /*true == pclCM->CR[pclMsg->siCharID]->bCellularPhoneAuth &&*/ true == pclCM->CR[pclMsg->siCharID]->bIsPromoter )
#endif
	{
		// 추천인을 등록해 두었다면 추천인에게 아이템 지급, 중국 제외
		if ( true == pclEventTimeManager->InEventTime( TEXT("RecommendReward"), &sTime ) )
		{
			if ( pclRewardMgr )
			{
				pclRewardMgr->GiveRecommendRewardItem( pclMsg->siRecommendPersonID, pclMsg->siLevel, false, (TCHAR*)pclCM->CR[pclMsg->siCharID]->GetName(), pclCM->CR[pclMsg->siCharID]->bCellularPhoneAuth );
			}
		}
		else
		{
			if( IsWhereServiceArea( ConstServiceArea_China ) == false  )
			{
				if((  pclMsg->siLevel == 20 || pclMsg->siLevel == 30  || pclMsg->siLevel == 40 || pclMsg->siLevel == 50 )) 
				{
					SI32 itemunique = 0; //
					SI32 itemnum = 0;
					SI32 RndValue = rand()%4;

					switch(pclMsg->siLevel)
					{
						case 20:	itemunique = ITEMUNIQUE(5350 + RndValue*5 );  //5350 , 5355, 5360, 5365 중 랜덤으로 하나 지급
									itemnum = 3;	
									break;
						case 30:	itemunique = ITEMUNIQUE(5350 + RndValue*5 );  //5350 , 5355, 5360, 5365 중 랜덤으로 하나 지급
									itemnum = 6;	
									break;
						case 40:	itemunique = ITEMUNIQUE(5350 + RndValue*5 );  //5350 , 5355, 5360, 5365 중 랜덤으로 하나 지급	
									itemnum = 9;
									break;
						case 50:	itemunique = ITEMUNIQUE(5370);		
									itemnum = 10; 	
									break;
					}

					SI32 ref = pclItemManager->FindItemRefFromUnique(itemunique);

					if(itemunique > 0 && itemnum > 0 && ref > 0)
					{
						UI16 usedate = pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay;

						//  역참으로 보낸다.
						cltItem clInputItem;
						SI16 bRareSwitch = 0;
						pclItemManager->MakeRandItemUnique(itemunique,&clInputItem,0,0,&bRareSwitch);

						clInputItem.siItemNum = itemnum;

						//((cltServer*)pclClient)->SendPostOfficeItemToPerson( pclCI->GetPersonID(), &clInputItem , NULL ,0  );

						sDBRequest_PostOfficeMasterSendItem clMsg( INPUTITEMPERSON_OPTION_RECOMMEND, pclMsg->siRecommendPersonID , NULL, &clInputItem, &((cltServer*)pclClient)->pclTime->clDate );
						pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

						cltLetterMsg_LevelUpREcommandRewardForRecommender clletter( (TCHAR*)pclCM->CR[pclMsg->siCharID]->GetName()  , pclMsg->siLevel, itemunique , itemnum );
						SendLetterMsg(  pclMsg->siRecommendPersonID , (cltLetterHeader*)&clletter );

					}
				}
			}	// if( IsWhereServiceArea( ConstServiceArea_China ) == false  ) 종료
		}
	}
#ifdef USE_PROMOTOR_SERVER
	// 중국은 프로모터가 있으면서 핸드폰 인증이 되야만 아이템과 포인트를 준다.	
	else if( true == pclCM->CR[pclMsg->siCharID]->bIsPromoter )
	{
		// 핸드폰 인증이 안되서 줄수 있는 아이템이 있는데 못줄때 메시지를 보낸다.
		if( pclRewardMgr->IsGiveRecommendRewardItem( pclCM->CR[pclMsg->siCharID]->pclCI->GetPersonID(), pclCM->CR[pclMsg->siCharID]->pclCI->clIP.GetLevel(), false, NULL ) )
		{
			SI32 recommenderpersonid = pclCM->CR[pclMsg->siCharID]->pclCI->clBI.clRecommenderInfo.siPersonID;
			if( recommenderpersonid > 0 ) 
			{
				SI32 siID = pclCM->GetIDFromPersonID(recommenderpersonid);
				cltCharServer* pRecommendeeChar = pclCM->GetCharServer( siID );
				if( pRecommendeeChar )
				{
					// 중국은 핸드폰 인증이 안되면 해당 메시지를 클라에 준다.
					//SendServerResponseMsg(0, SRVAL_PROMOTER_NOT_CELLULAR_PHONE_AUTH, 1, 0, pRecommendeeChar->GetCharUnique());
					
					SendServerResponseCharMsg2( 0, SRVAL_RECOMMENDEE_GIVE_ITEM_FAIL, (TCHAR*)pclCM->CR[pclMsg->siCharID]->GetName(), NULL, NULL, pclCM->CR[pclMsg->siCharID]->GetCharUnique() );		
				}
			}
		}
	}
#endif


    
	
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 추천인 보상 점수.
		// param1 == 레벨, Param2 == 추가된 추천 점수.
		// PCK (08.06.23) - pszCharParam1 삭제함.
		cltServer * pclserver = (cltServer*)pclClient;
		cltCharServer* pclchar = pclCM->GetCharServer(pclMsg->siCharID);

		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_RECOMMENDER_POINT_SET, 
										pclMsg->siReason, pclchar, NULL, pclMsg->siRecommendPersonID, 0, 0, 0, 0, 0, 0, 0, pclMsg->siRecommendPoint, 0, 
										pclMsg->siLevel, pclMsg->siChangedRecommendPoint, 0, 0, 0, NULL, NULL);	
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETRECOMMANDPOINT(sPacketHeader* pPacket)
{
	sDBResponse_GetRecommendPoint * pclMsg = (sDBResponse_GetRecommendPoint*)pPacket;

	if(pclMsg->siResult != 1) return;

	SI32 id = pclMsg->siCharID;

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	cltGameMsgResponse_GetRecommandPoint clRecommandPoint(pclMsg->siResult,pclMsg->siRecommendPoint);
	cltMsg clMsg( GAMEMSG_RESPONSE_GETRECOMMANDPOINT,sizeof(clRecommandPoint),(BYTE*)&clRecommandPoint);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}
void cltServer::DoMsg_DBMSG_RESPONSE_SETCOUNTRY( sPacketHeader* pPacket )
{
	sDBResponse_SetCountry* pclMsg = (sDBResponse_SetCountry*)pPacket;
	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	if( pclMsg->siResult == -1 )
	{
		// 실패했다는 메세지~
		return;
	}
    
	pclCM->CR[id]->pclCI->clBI.siCountryID = pclMsg->siCountryID;
	
	// 같은 국가 유저에게 알린다.
	for ( SI32 i = 1; i < MAX_PERSON_NUMBER ; ++i )
	{
		if( i == id )
			continue;

		if ( pclCM->IsValidID(i) == false)
			continue;

		if( pclCM->CR[i]->pclCI->clBI.siCountryID ==  pclMsg->siCountryID )
		{
			cltGameMsgResponse_NoticeCountryUserMake clinfo( id, pclMsg->siCountryID );
			cltMsg clMsg(GAMEMSG_RESPONSE_NOTICECOUNTRYUSERMAKE, sizeof(cltGameMsgResponse_NoticeCountryUserMake), (BYTE*)&clinfo );

			pclClient->pclCM->CR[i]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}
void cltServer::DoMsg_DBMSG_RESPONSE_SETSHOWCOUNTRY( sPacketHeader* pPacket )
{
	sDBResponse_SetShowCountry* pclMsg = (sDBResponse_SetShowCountry*)pPacket;
	
	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	if( pclMsg->siResult == -1 )
	{
		// 실패했다는 메세지
		//pclCM->CR[id]->SendNetMsg()
		return;
	}

	pclCM->CR[id]->pclCI->clBI.bShowCountry = pclMsg->bShowCountry;
} 

void cltServer::DoMsg_DBMSG_RESPONSE_SETSHOWPUCHIKOMI( sPacketHeader* pPacket )
{
	sDBResponse_SetShowPuchikomi* pclMsg = (sDBResponse_SetShowPuchikomi*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	if( pclMsg->siResult == -1 )
	{
		// 실패했다는 메세지
		//pclCM->CR[id]->SendNetMsg()
		return;
	}

	pclCM->CR[id]->pclCI->clBI.bShowPuchikomi = pclMsg->bShowPuchikomi;


	cltGameMsgResponse_SetShowPuchikomi clinfo(pclMsg->bShowPuchikomi);
	cltMsg clMsg(GAMEMSG_RESPONSE_SETSHOWPUCHIKOMI,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );
	

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [로그추가 : 황진성 2007. 10. 9] // 자신의 푸치코미 보기.
	//	// param1 == 푸치코미 보니 마니.
	//	cltServer * pclserver = (cltServer*)pclClient;
	//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_PUCHIKIMI_SET, 
	//									0, (cltCharServer *)pclCM->CR[id], NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	//									pclMsg->bShowPuchikomi, 0,  0, 0, 0, NULL, NULL);
	//}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GIVEFP( sPacketHeader* pPacket )
{
	sDBResponse_GiveFP* pclMsg = (sDBResponse_GiveFP*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 추천인 보상 점수 주기.
		// 
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_RECOMMENDER, LOGCOMMAND_INDEX_RECOMMENDER_POINT_SET, 
										pclMsg->siReason, NULL, NULL, pclMsg->siPersonID, 0, 0, 0, 0, 0, 0, 0, pclMsg->siRecommendPoint, 0, 
										0, 0, 0, 0, 0, NULL, NULL);	
	}
}
void cltServer::DoMsg_DBMSG_RESPONSE_ADDBUF( sPacketHeader* pPacket )
{
	sDBResponse_AddBuf* pclMsg = (sDBResponse_AddBuf*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( pclCM->IsValidID(id) == false )
		return;

	// 버프아이템을 다시 사용할수 있도록 한다
	((cltCharServer*)pclCM->CR[id])->bIsNowAddBufThroughDB = false;

	if ( pclMsg->siResult < 0 )
		return;

	pclCM->CR[id]->pclCI->clBI.clBufInfo.AddBuf( pclMsg->siIndex, pclMsg->m_stBuf );
	
	// 클라이언트에게도 통보한다.
	cltGameMsgResponse_AddBuf clinfo( pclCM->CR[id]->GetCharUnique(), pclMsg->siIndex, pclMsg->m_stBuf );
	cltMsg clMsg(GAMEMSG_RESPONSE_ADDBUF, sizeof(cltGameMsgResponse_AddBuf), (BYTE*)&clinfo );
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [로그추가 : 황진성 2007. 10. 5] // 버프 추가. (수정작업 : 버프 구조체 정보 추가 작업.)
		// param1 == 번호, 
		// param2 == 버프받은경로
		// param3 == 버프 타입
		// param4 == 사용제한 시간(게임시간)
		// param5 == 사용된 아이템 유니크
		// charparam1 == 게임시간
		TCHAR szCharParam1[50] = { '\0', };
		StringCchPrintf(szCharParam1, sizeof(szCharParam1), "Y:%03d M:%02d D:%02d H:%02d", pclTime->clDate.uiYear, pclTime->clDate.uiMonth, pclTime->clDate.uiDay, pclTime->clDate.uiHour);

		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_BUF_ADD, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clUsedItem, 0, 0, 0, 0, 0, 0, 
										pclMsg->siIndex, pclMsg->m_stBuf.siGetType, pclMsg->m_stBuf.siBufType, pclMsg->m_stBuf.siOverTime, pclMsg->clUsedItem.siUnique, szCharParam1, NULL);
	}


	// 아이템 사용했을 경우

	if ( pclMsg->bUseItem )
	{
		if( pclMsg->siItemPos >= 0 && pclMsg->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);

			// 클라이언트로 업데이트 된 정보를 보낸다. 
			cltGameMsgResponse_PersonItemInfo clinfo2(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg2(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo2), (BYTE*)&clinfo2);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

			pclItemManager->AddUseNum(pclMsg->clUsedItem.siUnique, pclMsg->clUsedItem.siItemNum);

			//새로운 통계 - 아이템 사용 통계를 낸다.
			//NStatistics_Add("Item", pclMsg->clUsedItem.siUnique, "UseNum", pclMsg->clUsedItem.siItemNum);
			
		}
	}


	// 선공 방지 프리미엄 버프 일 경우에 자신과 주변유저들에게 표시해준다. 
	if(		pclMsg->m_stBuf.siBufType == BUF_NOFIRSTATTACK 
		||	pclMsg->m_stBuf.siBufType == BUF_HINAMOCHI 
		||	pclMsg->m_stBuf.siBufType == BUF_EVENT_EGGMOONCAKE 
		||	(pclMsg->m_stBuf.siBufType == BUF_TRANSFORM && pclMsg->m_stBuf.siGetType != BUF_GET_TYPE_NIGHTMARKET)
	)
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACK, true);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	
	if( pclMsg->m_stBuf.siBufType == BUF_LOVEPOWER || pclMsg->m_stBuf.siBufType == BUF_FRIENDSHIP )
	{
		if( pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) 
			&& pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP ) )
		{
			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_HEARTEFFECT, true);
			cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
		}
	}
	else if( pclMsg->m_stBuf.siBufType == BUF_FOURLEAF )
	{
		if( pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FOURLEAF ) )
		{
			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FOURLEAF, true);
			cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
		}
	}
	else if( pclMsg->m_stBuf.siBufType == BUF_TRANSFORM )
	{
		// 에러처리를 위해 강제로 캐릭터를 세운다
		if( pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM ) )
		{
			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo( CHANGETYPE_TRANSFORMBUF, false, (SI32)pclMsg->m_stBuf.siPercent );
			cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
		}
	}
	else if( pclMsg->m_stBuf.siBufType == BUF_MENTOR )	//[진성] 스승, 제자 버프를 얻으면 얻었다고 메시지를 던지자.
	{
		SendServerResponseMsg( 0, SRVAL_GIVE_MENTOR_BUF, 0, 0, pclCM->CR[id]->GetCharUnique() );
	}
	// PCK : 축제음식 (탈것변신)
	else if( pclMsg->m_stBuf.siBufType == BUF_TRANSFORM_HORSE )
	{
		// 에러처리를 위해 강제로 캐릭터를 세운다
		if( pclCM->CR[id]->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_TRANSFORM_HORSE ) )
		{
			// 이웃에게 통보 
			cltCharChangeStatusInfo	StatusInfo( CHANGETYPE_TRANSFORM_HORSE, false, (SI32)pclMsg->m_stBuf.siPercent );
			cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
			((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
		}
	}

	// [기형] 선공방지 스프 개선 - 프리미엄이기 때문
	if(pclMsg->m_stBuf.siBufType == BUF_NOFIRSTATTACK)
	{
		pclCM->CR[id]->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum = true;

		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACKPREMIUM, true);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}

}
void cltServer::DoMsg_DBMSG_RESPONSE_DELETEBUF( sPacketHeader* pPacket)
{
	sDBResponse_DeleteBuf* pclMsg = (sDBResponse_DeleteBuf*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID( pclMsg->siPersonID );

	if( pclCM->IsValidID(id) == false )
		return;

	if( pclMsg->siResult < 0 )
		return;

	if( pclMsg->siIndex < 0 && pclMsg->siIndex >= MAX_BUF_COUNT )
		return;

	SI32 BufType = pclCM->CR[id]->pclCI->clBI.clBufInfo.m_stBuf[pclMsg->siIndex].siBufType;
	if( BufType  == BUF_NOFIRSTATTACK || BufType == BUF_HINAMOCHI || BufType == BUF_EVENT_EGGMOONCAKE)
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACK, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	else if( BufType  == BUF_LOVEPOWER || BufType  == BUF_FRIENDSHIP )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_HEARTEFFECT, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	else if( BufType == BUF_FOURLEAF )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_FOURLEAF, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	else if( BufType == BUF_HAPPYBEAN )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(BUF_HAPPYBEAN, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	else if( BufType == BUF_THANKSGIVING_DAY )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(BUF_THANKSGIVING_DAY, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);  
	}
	else if( BufType == BUF_FARMINGNMININGFOREVER )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(BUF_FARMINGNMININGFOREVER, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}
	else if( BufType == BUF_TRANSFORM )
	{
		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_TRANSFORMBUF, false, 0);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}	
	// PCK : 축제음식 (탈것이 변신)
	else if( BufType == BUF_TRANSFORM_HORSE )
	{	
		// 탈것 삭제시에 기존의 탈것으로 교체한다.
		SI32 siKind = 0;
		cltHorse* pCurHorse = pclClient->pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
		if( pCurHorse )
			siKind = pCurHorse->siHorseUnique; 

		// 이웃에게 통보 
		cltCharChangeStatusInfo	StatusInfo( CHANGETYPE_TRANSFORM_HORSE, false, siKind );
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
	}	
	pclCM->CR[id]->pclCI->clBI.clBufInfo.DeleteBuf( pclMsg->siIndex );

	cltGameMsgResponse_DeleteBuf clinfo( pclCM->CR[id]->GetCharUnique(), pclMsg->siIndex );
	cltMsg clMsg(GAMEMSG_RESPONSE_DELETEBUF, sizeof(cltGameMsgResponse_DeleteBuf), (BYTE*)&clinfo );
	pclClient->pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	// [기형] 선공방지 스프 개선
	if(pclMsg->m_stBuf.siBufType == BUF_NOFIRSTATTACK)
	{
		pclCM->CR[id]->pclCI->clBI.clBufInfo.m_bNoFirstAttackPreminum = false;

		// 프리미엄 선공 방지 제거
		cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_NOFIRSTATTACKPREMIUM, false);
		cltGameMsgResponse_StatusInfo clChangeInfo(pclCM->CR[id]->GetCharUnique(), &StatusInfo);
		cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// 소환수 선공 방지 제거
		cltCharChangeStatusInfo	StatusInfo2(CHANGETYPE_SUMMONNOFIRSTATTACK, false);
		cltGameMsgResponse_StatusInfo clChangeInfo2(pclCM->CR[id]->GetCharUnique(), &StatusInfo2);
		cltMsg clMsg2(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo2), (BYTE*)&clChangeInfo2);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg2, true);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 버프삭제.
		// param1 == 번호.
		// param2 == 버프타입
		// param3 == 제한 시간(게임시간)
		// charparam1 == 게임시간
		TCHAR szCharParam1[50] = { '\0', };
		StringCchPrintf(szCharParam1, sizeof(szCharParam1), "Y:%03d M:%02d D:%02d H:%02d", pclTime->clDate.uiYear, pclTime->clDate.uiMonth, pclTime->clDate.uiDay, pclTime->clDate.uiHour);

		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_BUF_DELETE, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
										pclMsg->siIndex, pclMsg->m_stBuf.siBufType, pclMsg->m_stBuf.siOverTime, 0, 0, szCharParam1, NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETTEACHERPOINT( sPacketHeader* pPacket)
{
	sDBResponse_SetTeacherPoint* pclMsg = (sDBResponse_SetTeacherPoint*)pPacket;

	if( 1 != pclMsg->siResult )
		return;

	// 현재 스승이 접속중이면 서버 클라 업데이트
	SI32 charID = pclCM->GetIDFromPersonID( pclMsg->siTeacherPersonID );
	if( 0 < charID )
	{
		if( false == pclCM->IsValidID( charID ) )		
			return;	

		// 서버 업데이트
	//	pclCM->CR[charID]->pclCI->clBI.clFatherInfo.SetTeacherPoint( pclMsg->siTotalTeacherPoint );
	
		cltGameMsgResponse_SetTeacherPoint clinfo( pclMsg->siTotalTeacherPoint );
		cltMsg clMsg( GAMEMSG_RESPONSE_SETTEACHERPOINT, sizeof(cltGameMsgResponse_SetTeacherPoint), (BYTE*)&clinfo );
		pclCM->CR[charID]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETITEM_FROM_TEACHERPOINT( sPacketHeader* pPacket)
{
	sDBResponse_GetItem_From_TeacherPoint* pclMsg = (sDBResponse_GetItem_From_TeacherPoint*)pPacket;

}

void cltServer::DoMsg_DBMSG_RESPONSE_RENOUNCEPUPIL( sPacketHeader* pPacket)
{
	sDBResponse_RenouncePupil* pclMsg = (sDBResponse_RenouncePupil*)pPacket;

	SI32 id = pclMsg->siCharID;

	if( 0 >= id )
		return;

	if( 1 != pclMsg->siResult )
	{
		cltGameMsgResponse_RenouncePupil clRenouncePupil( pclMsg->siResult );
		cltMsg clMsg( GAMEMSG_RESPONSE_RENOUNCEPUPIL, sizeof( clRenouncePupil ), (BYTE*)&clRenouncePupil );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		
		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [로그추가 : 황진성 2007. 10. 9] // 스승이 제자를 짜른다.
		//	// param1 == 결과.
		//	cltServer * pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_RENOUNCEPUPIL, 
		//									0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siPupilPersonID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		//									0, 0, 0, 0, 0, NULL, NULL);
		//}
									
		return;
	}

	// 제자에게 스승한테서 짤렸다는 정보를 편지로 보내준다.
	cltLetterMsg_RenouncePupil clletter( (TCHAR*)pclCM->CR[id]->GetName() );
	SendLetterMsg( pclMsg->siPupilPersonID, (cltLetterHeader*)&clletter);

	SI32 pupilID = pclCM->GetIDFromPersonID( pclMsg->siPupilPersonID );
	if( pupilID > 0 )
	{
		if( true == pclCM->IsValidID(pupilID) )
		{
			pclCM->CR[pupilID]->pclCI->clBI.clFatherInfo.Init();

			cltGameMsgResponse_SetFather clinfo(&pclCM->CR[pupilID]->pclCI->clBI.clFatherInfo.clFather, 0, pclCM->CR[pupilID]->pclCI->clBI.clFatherInfo.szAccountID);
			cltMsg clMsg(GAMEMSG_RESPONSE_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[pupilID]->SendNetMsg((sPacketHeader*)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 10. 9] // 스승이 제자를 버려.
			//	// param1	 == 스승레벨, 
			//	// pszParam1 == 스승 이름.
			//	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_RENOUNCEPUPIL, 
			//						0, (cltCharServer*)(pclCM->CR[pupilID]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//						pclCM->CR[pupilID]->pclCI->clIP.GetLevel(), 0, 0, 0, 0, pclCM->CR[pupilID]->pclCI->clBI.clFatherInfo.szAccountID, NULL);
			//}
		}
	}

	cltGameMsgResponse_RenouncePupil clRenouncePupil( pclMsg->siResult );
	cltMsg clMsg( GAMEMSG_RESPONSE_RENOUNCEPUPIL, sizeof( clRenouncePupil ), (BYTE*)&clRenouncePupil );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 스승이 제자를 짜른다.
		// param1 == 결과.
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_RENOUNCEPUPIL, 
										0, (cltCharServer*)pclCM->CR[id], NULL, pclMsg->siPupilPersonID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
										pclMsg->siResult, 0,  0, 0, 0, NULL, NULL);
	}

	sDBRequest_GetChildList clMsg2( id, pclCM->CR[id]->pclCI->GetPersonID() );
	pclGameDBProcess->SendMsg(DBSELECT_LETTER,  (sPacketHeader *)&clMsg2);
}

void cltServer::DoMsg_DBMSG_RESPONSE_OVERTAKETEACHERLEVEL( sPacketHeader* pPacket)
{
	sDBResponse_OverTakeTeacherLevel* pclMsg = (sDBResponse_OverTakeTeacherLevel*)pPacket;

	if( 1 != pclMsg->siResult )
		return;

	SI32 id = pclMsg->siCharID;

	if( 0 >= id )
		return;

	pclCM->CR[id]->pclCI->clBI.clFatherInfo.bOverTake = true;

	// 가방 30일
	cltItem clInputItem1;
	clInputItem1.siUnique = 15900;
	// 피로방지 시스템 적용
	clInputItem1.siItemNum = (SI16)(((cltCharServer*)pclCM->CR[id])->CalcTiredPoint( 1 ));
	clInputItem1.uiDateUseDay = 30;

	if ( clInputItem1.siItemNum )
	{
		SendPostOfficeItemToPerson( pclCM->CR[id]->pclCI->GetPersonID(), &clInputItem1, NULL, 0 );
	}
	if (  siServiceArea == ConstServiceArea_NHNChina )	//중국이라면 
	{
		//청출 어람시 피로도가 적용되었다면 메세지를 보내지 않는다 .(받을게 없을때도 보내지 않는다 )
		cltGameMsgResponse_OverTakeTeacherLevel clinfo( &clInputItem1, (TCHAR*)pclCM->CR[id]->GetName(), pclMsg->szTeacherName );
		cltMsg clMsg( GAMEMSG_RESPONSE_OVERTAKETEACHERLEVEL, sizeof(clinfo), (BYTE*)&clinfo);

		if(clInputItem1.siItemNum > 0 || ((cltCharServer*)pclCM->CR[id])->uiTiredState <= 0 )
		{
			pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [로그추가 : 황진성 2007. 10. 16] // 제자가 스승레벨을 앞질렀다
			// pszParam1 == 제자이름, 
			// pszParam2 == 선생이름.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_OVERTAKE_TEACHER_LEVEL, 
				0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &clinfo.m_clItem, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, clinfo.m_szPupilName, clinfo.m_szTeaCherName);
		}
	}
	else //아니라면 원래대로 
	{
		cltGameMsgResponse_OverTakeTeacherLevel clinfo( &clInputItem1, (TCHAR*)pclCM->CR[id]->GetName(), pclMsg->szTeacherName );
		cltMsg clMsg( GAMEMSG_RESPONSE_OVERTAKETEACHERLEVEL, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [로그추가 : 황진성 2007. 10. 16] // 제자가 스승레벨을 앞질렀다
			// pszParam1 == 제자이름, 
			// pszParam2 == 선생이름.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_OVERTAKE_TEACHER_LEVEL, 
				0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &clinfo.m_clItem, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, clinfo.m_szPupilName, clinfo.m_szTeaCherName);
		}
	}	
}

void cltServer::DoMsg_DBMSG_RESPONSE_PVPRESULT( sPacketHeader* pPacket )
{
	sDBResponse_PVPResult* pclMsg = (sDBResponse_PVPResult*)pPacket;

	if( 1 != pclMsg->siResult )
		return;

	// 이긴 사람 처리
	if( pclCM->IsValidID( pclMsg->siWinCharID ) )		
	{
		pclCM->CR[pclMsg->siWinCharID]->pclCI->clBI.siPVPWinNumber++;
		MStrCpy( pclCM->CR[pclMsg->siWinCharID]->pclCI->clBI.szPVPWinHighLevelUserName, pclMsg->szPVPWinHighLevelUserName, MAX_PLAYER_NAME );

		cltGameMsgResponse_PVPResult clPVPResult( true, pclMsg->szLoseUserName,
												pclCM->CR[pclMsg->siWinCharID]->pclCI->clBI.siPVPWinNumber,
												pclCM->CR[pclMsg->siWinCharID]->pclCI->clBI.siPVPLoseNumber,
												pclCM->CR[pclMsg->siWinCharID]->pclCI->clBI.szPVPWinHighLevelUserName );
		cltMsg clMsg( GAMEMSG_RESPONSE_PVPRESULT, sizeof( clPVPResult ), (BYTE*)&clPVPResult );
		pclCM->CR[pclMsg->siWinCharID]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	// 진 사람 처리
	if( pclCM->IsValidID( pclMsg->siLoseCharID ) )	
	{
		pclCM->CR[pclMsg->siLoseCharID]->pclCI->clBI.siPVPLoseNumber++;

		//[진성] pk시 패배하면 자신이 패했다는 정보를 보내주게 수정. => 2008-5-9
		cltGameMsgResponse_PVPResult clPVPResult( false, pclMsg->szWinUserName,
												pclCM->CR[pclMsg->siLoseCharID]->pclCI->clBI.siPVPWinNumber,
												pclCM->CR[pclMsg->siLoseCharID]->pclCI->clBI.siPVPLoseNumber,
												pclCM->CR[pclMsg->siLoseCharID]->pclCI->clBI.szPVPWinHighLevelUserName );
		cltMsg clMsg( GAMEMSG_RESPONSE_PVPRESULT, sizeof( clPVPResult ), (BYTE*)&clPVPResult );
		pclCM->CR[pclMsg->siLoseCharID]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_ATTEND( sPacketHeader* pPacket )
{
	// [tys]attend - 출석체크.
	sDBResponse_Attend* pclinfo = (sDBResponse_Attend*)pPacket;

	SI32 id = pclinfo->usCharID ;
	if ( pclCM->IsValidID(id) == false )	return;

	SI32 personid = pclinfo->siPersonID ;
	if ( pclCM->CR[id]->pclCI->GetPersonID() != personid ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if ( pclinfo->siResult != 1 )			return;

	switch ( pclinfo->siType ) 
	{
		// 출석 체크이벤트
		case ATTEND_EVENTTYPE_ATTENDANCE :
			{
				pclchar->pclCI->clBI.bAttendToday[ATTEND_EVENTTYPE_ATTENDANCE] = true;
				
				cltGameMsgResponse_Attend clinfo( pclinfo->siAttendanceDay, 0,  pclinfo->siType );
				cltMsg clMsg( GAMEMSG_RESPONSE_ATTEND, sizeof(clinfo), (BYTE*)&clinfo );
				pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
			}
			break;
		// PC방 프리미엄 강화 이벤트 지급
		case ATTEND_EVENTTYPE_PCROOM:
			{
				bool		bMakeResult			= false;	// 아이템 생성결과
				bool		bReferenceCheck		= false;	// 아이템 참조자 찾기 결과

				cltItem		clRewardItem;		// 보상할 아이템
				cltItem		clRewardItem2;		// 중국 PC방용 2번째 지급 아이템 
				SI32		siRewardItemUnique	= ITEMUNIQUE( 2756 );	// 행운의 네잎클로버(네잎클로버2)
				SI32		siRewardItemUnique2	= ITEMUNIQUE( 13351 );	// 중국PC방 상자
				SI32		siReference			= pclClient->pclItemManager->FindItemRefFromUnique( siRewardItemUnique );

				SI16		siUsedate			= 0;
				SI16		siRareswitch		= 0;

				// 0은 PC방 이지만 출석이 안되있는 상태 즉 아이템 지급을 안한상태 그렇기 때문에 0이 아니면 무조건 종료
				if ( pclinfo->siAttendanceDay != 0 )
				{
					return;
				}

				// 요청이 오기는 했지만 혹시 다시한번 검증해서 PC방이 아니라면 리턴
				if ( pclchar->pclCI->clBI.bPCRoom == false )
				{
					return;
				}

				if ( siReference > 0 )
				{
					siUsedate			= pclClient->pclItemManager->pclItemInfo[ siReference ]->clItem.uiDateUseDay;

					bReferenceCheck		= true;
					bMakeResult			= pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique, &clRewardItem, 0, 0, &siRareswitch,0,0,0,0,0,siUsedate );
				}

				// 중국일때는 아이템을 하나 더 지급한다
				if ( IsWhereServiceArea(ConstServiceArea_NHNChina) )
				{
					if ( (bMakeResult == true) && (bReferenceCheck == true) )
					{
						// 2번째 아이템이 만들어 졌는지도 검사해야 하므로 다시 false로 만든다
						bReferenceCheck		= false;
						bMakeResult			= false;

						siReference			= pclItemManager->FindItemRefFromUnique( siRewardItemUnique2 );
						if ( 0 < siReference )
						{
							siUsedate		= pclClient->pclItemManager->pclItemInfo[ siReference ]->clItem.uiDateUseDay;
							bReferenceCheck	= true;
							bMakeResult		= pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique2, &clRewardItem2, 0, 0, &siRareswitch,0,0,0,0,0,siUsedate );
						}
					}
				}

				if ( (bMakeResult == true) && (bReferenceCheck == true) )
				{
					cltSystemRewardInfo		clInfo;			// 아이템 보상에 따른 정보
					TCHAR*					pText			= GetTxtFromMgr( 7979 );	// 지급하는 이유(PC방 프리미엄)

					SI32					siPersonID		= pclchar->pclCI->GetPersonID();
					SI32					siCharID		= pclchar->GetID();

					// 받은 날짜
					clInfo.m_sGiveTime		= sTime;

					// 받은 날로부터 1일동안만 수령할 수 있다.
					TimeAddDate(&clInfo.m_sGiveTime, 1, &clInfo.m_sExpireTime);

					// 지급할 아이템
					clInfo.m_clItem.Set( &clRewardItem );

					// 지급 이유
					if ( pText )
					{
						StringCchCopy( clInfo.m_szReason, 256, pText );
					}

					// 아이템을 지급 하라는 요청
					sDBRequest_GiveSystemReward clMsg( GIVEREWARD_ACCOUNT, siPersonID, siCharID, &clInfo );
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

					// 중국일때는 아이템을 하나 더 지급한다
					if ( IsWhereServiceArea(ConstServiceArea_NHNChina) )
					{
						clInfo.m_clItem.Set( &clRewardItem2 );

						// 아이템을 지급 하라는 요청
						sDBRequest_GiveSystemReward clMsg( GIVEREWARD_ACCOUNT, siPersonID, siCharID, &clInfo );
						pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
					}

					NDate kAttendDay;
					kAttendDay.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );
					
					// 이 날짜로 출석을 하라는 메시지
					sDBRequest_SetAttend clDBSetAttend( siPersonID, siCharID, &kAttendDay, ATTEND_EVENTTYPE_PCROOM );
					pclGameDBProcess->SendMsg((sPacketHeader *)&clDBSetAttend);

					// 유저에게 지급되었다는 메시지를 띄워줌
					SendServerResponseMsg( 0, SRVAL_REWARDITEM_FOR_PCROOM, 0, 0, siCharID );

					pclchar->pclCI->clBI.bAttendToday[ ATTEND_EVENTTYPE_PCROOM ] = true;
				}

			}
			break;

		case ATTEND_EVENTTYPE_SEASON2:
			{
				// 이곳은 보상을 받을 수 있는지 없는지만을 검사한다
				SI32 siAttendanceDay = pclinfo->siAttendanceDay;
				SI32 siModulationDay = siAttendanceDay % Const_Attendance_Modulation_Day;

				if ( (0 > siAttendanceDay) || (0 > siModulationDay) )
				{
					return;
				}

				// 다음 아이템 받을때까지 며칠이 필요한지 검사
				SI32 siNextRewardDays = 0;
				for ( SI32 siNext=siModulationDay; siNext<MAX_ATTENDANCE_COUNT; siNext++ )
				{
					if ( m_pclAttendanceReward[siNext] != NULL )
					{
						if ( m_pclAttendanceReward[siNext]->m_siItemUnique > 0 )
						{
							break;
						}
					}
					siNextRewardDays++;
				}

				if ( siNext == MAX_ATTENDANCE_COUNT )
				{
					siNextRewardDays = 0;
				}


				SI32 siRewardCount = 0;
				SI32 siRewardIndex = 0;
				// 누적 출석일수동안 보상아이템을 몇번 받을수있는지 검사
				for ( SI32 siCount=1; siCount<=siAttendanceDay; siCount++ )
				{
					siRewardIndex = (siCount % Const_Attendance_Modulation_Day);
					if ( m_pclAttendanceReward[siRewardIndex] != NULL )
					{
						if ( m_pclAttendanceReward[siRewardIndex]->m_siItemUnique > 0 )
						{
							siRewardCount++;
						}
					}
				}
				
				// 현재 보상을 받을 필요가 없다면 출석 도장을 찍을 수 있도록 해준다
				if ( pclinfo->siRewardDay >= siRewardCount )
				{
					 pclchar->pclCI->clBI.bIsCanAttend = true;
				}
				else
				{
					pclchar->pclCI->clBI.bIsCanAttend = false;
				}

				// 보상을 받을 수 있는지 여부를 판별
				if ( pclinfo->siRewardDay < siRewardCount )
				{
					pclchar->pclCI->clBI.bIsCanReward = true;
				}
				else
				{
					pclchar->pclCI->clBI.bIsCanReward = false;
				}

				pclchar->pclCI->clBI.siAttendanceDays = siAttendanceDay;

			
				// 클라이언트에게 출석에 관한 정보를 보내준다 패킷 이름은 관계없음
				cltGameMsgResponse_DemandAttend clInfo( (SI16)siAttendanceDay, (SI16)siNextRewardDays, ATTEND_EVENTTYPE_SEASON2, false );
				cltMsg clMsg( GAMEMSG_RESPONSE_DEMANDATTEND, sizeof(clInfo), (BYTE*)&clInfo);
				pclchar->SendNetMsg( (sPacketHeader*)&clMsg );

				// 로그 찍기
				if( pclClient->IsWhereServiceArea(ConstSwitch_NewLog) ) 
				{
					// param1 : 출석일수
					// param2 : 다음 보상 일수
					// param3 : 출석 타입
					SendLog_WriteLogToDB( LOGCOMMAND_TYPE_ATTEND, LOGCOMMAND_INDEX_ATTEND_CHANGE, 0, pclchar, NULL,
										0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										siAttendanceDay, siNextRewardDays, ATTEND_EVENTTYPE_SEASON2, 0, 0, NULL, NULL );
				}
			}
			break;

		default:
			return;
	}

}

// [영훈] 출석체크 : 출석체크하고나서의 결과값
void cltServer::DoMsg_DBMSG_RESPONSE_SETATTEND( sPacketHeader* pPacket )
{
	sDBResponse_SetAttend* pclinfo = (sDBResponse_SetAttend*)pPacket;
	if ( pclinfo == NULL )
	{
		return;
	}

	SI32 siCharID = pclinfo->uiCharID ;
	if ( pclCM->IsValidID(siCharID) == false )
	{
		return;
	}

	SI32 siPersonID = pclinfo->siPersonID ;
	if ( pclCM->CR[siCharID]->pclCI->GetPersonID() != siPersonID )
	{
		//return;
	}

	cltServer *pclServer = (cltServer*)pclClient;
	if ( pclServer == NULL )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siCharID];
	if ( pclchar == NULL )
	{
		return;
	}

	if ( pclinfo->siResult != 1 )
	{
		// 로그 찍기
/*		if( pclClient->IsWhereServiceArea(ConstSwitch_NewLog) ) 
		{
			switch ( pclinfo->siType ) 
			{
				case ATTEND_EVENTTYPE_ATTENDANCE:
				{
					pclServer->SendLog_WriteLogToDB( LOGCOMMAND_TYPE_ATTEND, LOGCOMMAND_INDEX_ATTEND_FAIL, 0, pclchar, NULL,
						0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL );
				}
				break;

				case ATTEND_EVENTTYPE_SEASON2:
				{
					pclServer->SendLog_WriteLogToDB( LOGCOMMAND_TYPE_ATTEND, LOGCOMMAND_INDEX_ATTEND_REWARD_FAIL, 0, pclchar, NULL,
						0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL );
				}
				break;
			}
		}*/
		return;
	}

	switch ( pclinfo->siType ) 
	{
		// 출석 체크이벤트
		case ATTEND_EVENTTYPE_ATTENDANCE:
			{
				// 이벤트 기간동안 얼마만큼 출석하고 얼마만큼 보상을 받았는지 받아오기
				sDBRequest_Attend clMsg( siPersonID, siCharID,	&clAttendEventStart, &clAttendEventEnd, ATTEND_EVENTTYPE_SEASON2 );
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
			break;

		// 한게임 PC방 출석
		case ATTEND_EVENTTYPE_PCROOM:
			{
				
			}
			break;

		// 시즌2 출석 이벤트
		case ATTEND_EVENTTYPE_SEASON2:
			{
				SI32	siAttendanceDays = pclchar->pclCI->clBI.siAttendanceDays;
				cltItem clRewardItem;
				
				if ( GetItemByAttendanceDay( siAttendanceDays, &clRewardItem ) )
				{
					cltSystemRewardInfo clInfo;

					clInfo.m_sGiveTime = sTime;
                    // 지급받은 뒤 30일 동안 수령이 가능하다.
					TimeAddDate(&clInfo.m_sGiveTime, 30, &clInfo.m_sExpireTime);

//					NDate ExpireDate;
//					ExpireDate.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );
//					ExpireDate.AddMonths( 1 );
//
//					_SYSTEMTIME sExpireTime;
//					ZeroMemory( &sExpireTime, sizeof(_SYSTEMTIME) );
//					sExpireTime.wYear		= ExpireDate.m_uiYear;
//					sExpireTime.wMonth		= ExpireDate.m_uiMonth;
//					sExpireTime.wDay		= ExpireDate.m_uiDay;
//
//					clInfo.m_sExpireTime	= sExpireTime;

					clInfo.m_clItem.Set( &clRewardItem );
					TCHAR* pText = GetTxtFromMgr( 10175 );
					StringCchPrintf( clInfo.m_szReason, 256, pText, siAttendanceDays );

					sDBRequest_GiveSystemReward clMsg( GIVEREWARD_ACCOUNT, pclchar->pclCI->GetPersonID(), pclchar->GetID(), &clInfo );
					SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

					pclchar->pclCI->clBI.bAttendToday[ATTEND_EVENTTYPE_SEASON2] = true;

					// 출석이 가능하도록 해준다
					pclchar->pclCI->clBI.bIsCanAttend = true;

					SendServerResponseMsg( 0, SRVAL_SUCCESS_SEASON2_ATTEND_REWARDITEM, 0, 0, pclchar->GetID() );

					// 로그 찍기
					if( pclClient->IsWhereServiceArea(ConstSwitch_NewLog) ) 
					{
						// para1 = 출석일수
						pclServer->SendLog_WriteLogToDB( LOGCOMMAND_TYPE_ATTEND, LOGCOMMAND_INDEX_ATTEND_REWARD_SUCCESS, 0, pclchar, NULL,
							0, 0, 0, &clRewardItem, 0, 0, 0, 0, 0, 0, siAttendanceDays, 0, 0, 0, 0, NULL, NULL );
					}
				}
				else
				{
					SendServerResponseMsg( 0, SRVAL_FAIL_SEASON2_ATTEND_REWARDITEM, 0, 0, pclchar->GetID() );
					// 로그 찍기
					if( pclClient->IsWhereServiceArea(ConstSwitch_NewLog) ) 
					{
						// para1 = 출석일수
						pclServer->SendLog_WriteLogToDB( LOGCOMMAND_TYPE_ATTEND, LOGCOMMAND_INDEX_ATTEND_REWARD_FAIL, 0, pclchar, NULL,
							0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, siAttendanceDays, 0, 0, 0, 0, NULL, NULL );
					}
				}
			}
			break;
		default:
			return;
	}

	pclchar->pclCI->clBI.bAttendToday[pclinfo->siType] = true;
}

//KHY - 1220 - 변신시스템.
void cltServer::DoMsg_DBMSG_RESPONSE_TRANSFORM_ADDCHAR( sPacketHeader* pPacket )
{
	sDBResponse_Transform_AddChar* pclinfo = (sDBResponse_Transform_AddChar*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( NULL == pclChar)
		return;
	if ( pclinfo->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	if(pclinfo->siResult == 1)
	{
		if(IsWhereServiceArea(ConstSwitch_NewLog))
		{
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_SPIRIT_CHARGE, 
				0, pclChar, 
				NULL, 0, 0, 0, &pclinfo->clItem, pclinfo->clLeftItem.GetItemNum(), 0, 0, 0, 0, 0, 
				pclinfo->siItemPos, 0, pclinfo->siAddTime, 0, 0, 
				NULL, NULL);
		}

		if(pclChar->clTransFormInfo.SetTransFormChar(pclinfo->siCharKind) == true)
		{
			// 클라이언트로 알린다.
			cltGameMsgResponse_SetTransForm cltransform( &pclChar->clTransFormInfo );
			cltMsg clMsgTransform(GAMEMSG_RESPONSE_TRANSFORM, sizeof(cltransform), (BYTE*)&cltransform);
			pclChar->SendNetMsg((sPacketHeader*)&clMsgTransform);
		}

		cltTimeMeterRate* pclTimeMeterRate = pclChar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(pclinfo->siTimeMeterRateType);
		if( pclTimeMeterRate )
		{
			pclTimeMeterRate->AddLeftTime(pclinfo->siAddTime);

			// 클라이언트에 정보를 전송한다.
			cltGameResponse_TimeMeterRate_Update	clTimeMeterRate( pclTimeMeterRate );
			cltMsg clMsg1( GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE, sizeof(clTimeMeterRate), (BYTE*)&clTimeMeterRate );
			pclChar->SendNetMsg( (sPacketHeader*)&clMsg1 );
		}

		//--------------------------
		// 인벤을 업데이트 한다. 
		//--------------------------
		if( pclinfo->siItemPos >= 0 && pclinfo->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclChar->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clLeftItem);

			cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siItemPos, PERSONITEMINFO_OPTION_NONE, pclinfo->clLeftItem.siItemNum, 0, &pclinfo->clLeftItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_TIMEMETERRATE_ADDTIME( sPacketHeader* pPacket )
{
	sDBResponse_TimeMeterRate_AddTime* pclinfo = (sDBResponse_TimeMeterRate_AddTime*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclinfo->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	if(pclinfo->siResult == 1)
	{
		if(IsWhereServiceArea(ConstSwitch_NewLog))
		{
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_SPIRIT_CHARGE, 
				0, pclChar, 
				NULL, 0, 0, 0, &pclinfo->clItem, pclinfo->clLeftItem.siItemNum, 0, 0, 0, 0, 0, 
				pclinfo->siItemPos, pclinfo->siLeftTime, pclinfo->siAddTime, 0, 0, 
				NULL, NULL);
		}
		cltTimeMeterRate* pclTimeMeterRate = pclChar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(pclinfo->siTimeMeterRateType);
		if( pclTimeMeterRate )
		{
			pclTimeMeterRate->AddLeftTime(pclinfo->siAddTime);

			// 클라이언트에 정보를 전송한다.
			cltGameResponse_TimeMeterRate_Update	clTimeMeterRate( pclTimeMeterRate );
			cltMsg clMsg( GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE, sizeof(clTimeMeterRate), (BYTE*)&clTimeMeterRate );
			pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
		}
		//--------------------------
		// 인벤을 업데이트 한다. 
		//--------------------------
		if( pclinfo->siItemPos >= 0 && pclinfo->siItemPos < MAX_ITEM_PER_PERSON )
		{
			pclChar->pclCI->clCharItem.clItem[pclinfo->siItemPos].Set(&pclinfo->clLeftItem);

			cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siItemPos, PERSONITEMINFO_OPTION_NONE, pclinfo->clLeftItem.siItemNum, 0, &pclinfo->clLeftItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclChar->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_TIMEMETERRATE_USETIME( sPacketHeader* pPacket )
{
	sDBResponse_TimeMeterRate_UseTime* pclinfo = (sDBResponse_TimeMeterRate_UseTime*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);

	if( pclCM->IsValidID(id) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclinfo->siPersonID != pclChar->pclCI->GetPersonID())
		return ;

	cltItem *pclItemList = pclChar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
	cltPSkillInfo *pclskillinfo = &pclChar->pclCI->clCharSkill;


	if(pclinfo->siResult == 1)
	{
		if( pclinfo->bUpdate )
		{
			cltTimeMeterRate* pclTimeMeterRate = pclChar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(pclinfo->siTimeMeterRateType);
			if( pclTimeMeterRate )
			{
				pclTimeMeterRate->siLeftTimeSec = pclinfo->siLeftTime;

				// 클라이언트에 정보를 전송한다.
				cltGameResponse_TimeMeterRate_Update	clTimeMeterRate( pclTimeMeterRate );
				cltMsg clMsg( GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE, sizeof(clTimeMeterRate), (BYTE*)&clTimeMeterRate );
				pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
			}
		}
	}
	// DB처리에서 오류가 나면, DB정보로 업데이트 한다.
	else
	{
		// 종량제 서비스 강제 종료
		pclChar->pclCI->clBI.clTimeMeterRateInfo.UseEnd(pclinfo->siTimeMeterRateType);

      		 // 종량제 시스템 강제 종료에 따른 컨텐츠 종료		
		switch(pclinfo->siTimeMeterRateType)
		{
			case TIMEMETERRATE_TRANSFORM:
				// 변신시스템 강제 종료
				pclChar->CharTransform( 0 ,pclChar->ActiveWeapon,pclItemList ,pclskillinfo);
				break;
			//KHY - 1111 - 오토바이 추가
			case TIMEMETERRATE_MOTORCYCLE:
				// 오토바이 에서 강제로 내리게 한다.
				pclChar->CharTransform( 0 ,pclChar->ActiveWeapon,pclItemList ,pclskillinfo);
				break;
		}

		cltTimeMeterRate* pclTimeMeterRate = pclChar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(pclinfo->siTimeMeterRateType);
		if( pclTimeMeterRate )
		{
			pclTimeMeterRate->siLeftTimeSec = pclinfo->siLeftTime;

			// 클라이언트에 정보를 전송한다.
			cltGameResponse_TimeMeterRate_Update	clTimeMeterRate( pclTimeMeterRate );
			cltMsg clMsg( GAMEMSG_RESPONSE_TIMEMETERRATE_UPDATE, sizeof(clTimeMeterRate), (BYTE*)&clTimeMeterRate );
			pclChar->SendNetMsg( (sPacketHeader*)&clMsg );
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GET_HOMEPAGE_URL(sPacketHeader* pPacket)
{
	sDBResponse_Get_HomePageURL* pclinfo = (sDBResponse_Get_HomePageURL*)pPacket;

	SI32 id = pclinfo->siCharID;
	
	if ( pclCM->IsValidID(id) == false ) return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return ;

	SI32 targetid = pclCM->GetIDFromPersonID( pclinfo->siPersonID );
	if (pclCM->IsValidID(targetid) == false) return;

	// DB로 홈페이지 URL정보를 요청한다.
	cltGameMsgResponse_GetHomepage_URL GetHomepage_URL( pclinfo->szText );
	cltMsg clMsg( GAMEMSG_RESPONSE_GET_HOMEPAGE_URL, sizeof(GetHomepage_URL), (BYTE*)&GetHomepage_URL );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SET_HOMEPAGE_URL(sPacketHeader* pPacket)
{
	sDBResponse_Set_HomePageURL* pclinfo = (sDBResponse_Set_HomePageURL*)pPacket;

	SI32 id = pclinfo->siCharID;

	if ( pclCM->IsValidID(id) == false) return;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return;


	// DB로 폼페이지 URL정보를 셋팅한다.
	//cltGameMsgResponse_SetHomepage_URL GetHomepage_URL( pclinfo->szText );
	//cltMsg clMsg( GAMEMSG_RESPONSE_SET_HOMEPAGE_URL, sizeof(GetHomepage_URL), (BYTE*)&GetHomepage_URL );
	//SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETBONUSINFO(sPacketHeader* pPacket)
{
	// PCK : 로그를 남기기 위해서 작성
	sDBResponse_SetBonusInfo*	pclMsg = (sDBResponse_SetBonusInfo*)pPacket;

	// PCK : PersonID를 근거로 CharID를 찾음.(PersonID넣지말자!!)
	SI32 CharID = pclCM->GetIDFromPersonID(pclMsg->siPersonID);

	if(FALSE == pclCM->IsValidID(CharID)) {		return;		}

	cltCharServer* pclchar = pclCM->GetCharServer(CharID);

	TCHAR szBA[50];
	ZeroMemory(szBA, sizeof(szBA));
	StringCchPrintf(szBA, sizeof(szBA), TEXT("Str:%d, Dex:%d, Vit:%d, Mag:%d, Hnd:%d, Luk:%d, Wis:%d"),	
		pclMsg->cIBA.GetStr(), pclMsg->cIBA.GetDex(), pclMsg->cIBA.GetMag(), 
		pclMsg->cIBA.GetHnd(), pclMsg->cIBA.GetLuk(), pclMsg->cIBA.GetWis() );

	// param1 == 캐릭터가 얻는 보너스 수치.
	// pszcharparam1 == 캐릭터의 스탯
	cltServer* pclserver = (cltServer*)pclClient;
	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_SETBONUSINFO,
									0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
									pclMsg->siBonus, 0, 0, 0, 0,  szBA, NULL);
}
//발렌타인 전쟁 정보를 받는다,.
void cltServer::DoMsg_DBMSG_RESPONSE_VALENTINEWAR_INFO_GET(sPacketHeader* pPacket)
{
	sDBResponse_Valantine_Info_Get*	pclMsg = (sDBResponse_Valantine_Info_Get*)pPacket;
	SI32 id = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID ) ;
	
	if(FALSE == pclCM->IsValidID(id)) {		return;		}
	cltCharServer* pclchar = pclCM->GetCharServer(id);

	SYSTEMTIME stLastAnswerTime;

	stLastAnswerTime = pclMsg->m_clValantineWarInfo.GetAnswerTime()	;	// 디비로부터 마지막으로 대답해서 저장된 시간을 받는다.
	if( sTime.wDay != stLastAnswerTime.wDay )// 날짜가 다르다면
	{
		// 클라이언트에 커플이냐고 묻는 창을 띄운다.
		cltGameResponse_ValentineWar_OpenDlg clDoenDlg(true);
		cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINE_OPENDLG, sizeof(clDoenDlg), (BYTE*)&clDoenDlg );
		pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
	}
	else // 날짜가 같다
	{
		// 서버에 정보를 셋팅 한
		pclchar->pclValentineWar->Set(&pclMsg->m_clValantineWarInfo)	;
		cltGameResponse_ValentineWar_Info_get clValenTinewar_Info_Get( pclchar->pclValentineWar );
		cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINE_INFO_GET, sizeof(clValenTinewar_Info_Get), (BYTE*)&clValenTinewar_Info_Get );
		pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
	}
}
//발렌타인 전쟁 정보 셋팅을 했다.
void cltServer::DoMsg_DBMSG_RESPONSE_VALENTINEWAR_REQUEST(sPacketHeader* pPacket)
{
	sDBResponse_Valantine_Request*	pclMsg = (sDBResponse_Valantine_Request*)pPacket;
	SI32 siID = pclCM->GetIDFromPersonID(pclMsg->m_siPersonID) ;
	if( FALSE == pclCM->IsValidID(siID ) )	return	;
	cltCharServer* pclchar = pclCM->GetCharServer( siID)	;
	pclchar->pclValentineWar->Set( &pclMsg->clValentineWarInfo)	;
	cltGameMsgResponse_ValentineWar_Request clvalentinewar_Request( pclchar->GetCharUnique(),pclMsg->clValentineWarInfo );
	cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINE_REQUEST, sizeof(clvalentinewar_Request), (BYTE*)&clvalentinewar_Request );
	pclchar->SendNeighbourMsg( &clMsg,true );
}
//발렌타인 전쟁아이템을 받았다.
void cltServer::DoMsg_DBMSG_RESPONSE_VALENTINEWAR_GET_PRIZE(sPacketHeader* pPacket)
{
	sDBResponse_Valantine_Get_Prize*	pclMsg = (sDBResponse_Valantine_Get_Prize*)pPacket;
	SI32 siID = pclCM->GetIDFromPersonID(pclMsg->m_siPersonID) ;
	if( FALSE == pclCM->IsValidID(siID ) )	return	;
	cltCharServer* pclchar = pclCM->GetCharServer( siID)	;
	pclchar->pclValentineWar->SetPrize( pclMsg->bGetPrize );

	cltGameResponse_ValentineWar_PrizeGet clvalentinewar_PrizeGet( pclchar->GetCharUnique(),pclMsg->bGetPrize );
	cltMsg clMsg( GAMEMSG_RESPONSE_VALENTINE_PRIZEGET, sizeof(clvalentinewar_PrizeGet), (BYTE*)&clvalentinewar_PrizeGet );
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
}


void cltServer::DoMsg_DBMSG_RESPONSE_CELLULAR_PHONE_AUTH(sPacketHeader* pPacket)
{
	sDBResponse_Get_Cellular_Phone_Auth* pclMsg = (sDBResponse_Get_Cellular_Phone_Auth*)pPacket;
	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->m_siCharID );
	if( NULL == pclchar ) return;
	
	pclchar->bCellularPhoneAuth = pclMsg->m_bIsCellularPhoneAuth;

	if( 0 < pclMsg->m_siRecommendPersonID )
	{
		// 기존에 목록에 있는지 체크
		cltSimplePerson* pSimplePersonInfo = NULL;
		for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			pSimplePersonInfo = &pclchar->pclFriendInfo->clFriend[i];

			if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
			{
				if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->m_szRecommendPersonName ) == 0 )
				{
					// 친구 목록에 있으므로 추가할 필요 없음.
					return;
				}
			}
		}

		if( pclMsg->m_bFirstCharCreate )
		{
			sDBRequest_FriendAddList clMsg(	0, pclMsg->m_siRecommendPersonID, 0, pclMsg->m_szRecommendPersonName, 
											0, pclchar->pclCI->GetPersonID(), pclMsg->m_siCharID, (TCHAR*)pclchar->GetName() );

			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		}
	}
}

void cltServer::DoMsg_DBMSG_DBMSG_RESPONSE_SET_MARRY( sPacketHeader* pPacket )
{
	sDBResponse_Set_Marry* pclMsg = (sDBResponse_Set_Marry*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	// DB에서 실패 했다면
	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}
	
	// 결혼 기념일
	SI32			siWeddingDate	= pclMsg->m_siWeddingDateVary;
	SI16			siLoveLevle		= pclMsg->m_siLoveLevel;

	// 우선 청혼을 한 사람
	SI32			siSourcePID		= pclMsg->m_siSourcePersonID;
	SI32			siSourceCharID	= pclCM->GetIDFromPersonID( siSourcePID );
	cltCharServer*	pclSourceChar	= pclCM->GetCharServer( siSourceCharID );

	// 청혼 받은 사람
	SI32			siDestPID		= pclMsg->m_siDestPersonID;
	SI32			siDestCharID	= pclCM->GetIDFromPersonID( siDestPID );
	cltCharServer*	pclDestChar		= pclCM->GetCharServer( siDestCharID );

	// 접속/동일 맵상에 있는지 검사
	SI16			siConnectMode	= MARRIAGE_MATE_CONNECT_MODE_NONE;
	
	if ( (pclSourceChar) && (pclDestChar) )
	{
		siConnectMode = MARRIAGE_MATE_CONNECT_MODE_CONNECT;

		if ( pclSourceChar->GetMapIndex() == pclDestChar->GetMapIndex() )	
		{
			siConnectMode = MARRIAGE_MATE_CONNECT_MODE_SAMEMAP;
		}
	}

	// 청혼한 사람
	if ( pclSourceChar )
	{
		// 결혼 관련 정보 셋팅
		if ( pclSourceChar->pclMarriage )
		{
			pclSourceChar->pclMarriage->Set( siDestPID, pclMsg->m_szDestName, siWeddingDate, 0, FALSE, siLoveLevle, 0, 0, siConnectMode );
		}

		// 사용된 아이템 설정
		if ( (PERSONITEM_INV0 <= pclMsg->m_siSourceItemPos) && ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) > pclMsg->m_siSourceItemPos) )
		{
			pclSourceChar->pclCI->clCharItem.clItem[pclMsg->m_siSourceItemPos].Set( &pclMsg->m_clSourceItem );
		}

		// 클라이언트로 정보를 보낸다
		cltGameResponse_Set_Marry clinfo( siDestPID,				pclMsg->m_szDestName,
										siWeddingDate,
										siLoveLevle,				siConnectMode,
										&pclMsg->m_clSourceItem,	pclMsg->m_siSourceItemPos );

		cltMsg clMsg( GAMEMSG_RESPONSE_SET_MARRY, sizeof(clinfo), (BYTE*)&clinfo );
		pclSourceChar->SendNetMsg( (sPacketHeader*)&clMsg );

		if ( IsWhereServiceArea(ConstSwitch_NewLog) ) 
		{
			// param1 = 결혼일
			// param2 = 애정도
			// param3 = 사용된 아이템 위치

			SendLog_WriteLogToDB( LOGCOMMAND_TYPE_FAMILY, LOGCOMMAND_INDEX_FAMILY_MARRY, 
				0, pclSourceChar, NULL, siDestPID, 0, 0, &pclMsg->m_clSourceItem, pclMsg->m_clSourceItem.siItemNum, 0, 0, 0, 0, 0, 
				siWeddingDate, siLoveLevle, pclMsg->m_siSourceItemPos, 0, 0, NULL, NULL);
		}

	}

	// 청혼받은 사람
	if ( pclDestChar )
	{
		// 결혼 관련 정보 셋팅
		if ( pclDestChar->pclMarriage )
		{
			pclDestChar->pclMarriage->Set( siSourcePID, pclMsg->m_szSourceName, siWeddingDate, 0, FALSE, siLoveLevle, 0, 0, siConnectMode );
		}

		// 사용된 아이템 설정
		if ( (PERSONITEM_INV0 <= pclMsg->m_siDestItemPos) && ((PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON) > pclMsg->m_siDestItemPos) )
		{
			pclDestChar->pclCI->clCharItem.clItem[pclMsg->m_siDestItemPos].Set( &pclMsg->m_clDestItem );
		}

		// 클라이언트로 정보를 보낸다
		cltGameResponse_Set_Marry clinfo( siSourcePID,			pclMsg->m_szSourceName,
										siWeddingDate,
										siLoveLevle,			siConnectMode,
										&pclMsg->m_clDestItem,	pclMsg->m_siDestItemPos );

		cltMsg clMsg( GAMEMSG_RESPONSE_SET_MARRY, sizeof(clinfo), (BYTE*)&clinfo );
		pclDestChar->SendNetMsg( (sPacketHeader*)&clMsg );

		if ( IsWhereServiceArea(ConstSwitch_NewLog) ) 
		{
			// param1 = 결혼일
			// param2 = 애정도
			// param3 = 사용된 아이템 위치

			SendLog_WriteLogToDB( LOGCOMMAND_TYPE_FAMILY, LOGCOMMAND_INDEX_FAMILY_MARRY, 
				0, pclDestChar, NULL, siSourcePID, 0, 0, &pclMsg->m_clDestItem, pclMsg->m_clDestItem.siItemNum, 0, 0, 0, 0, 0, 
				siWeddingDate, siLoveLevle, pclMsg->m_siDestItemPos, 0, 0, NULL, NULL);
		}
	}



}

void cltServer::DoMsg_DBMSG_RESPONSE_GET_MARRY_INFO( sPacketHeader* pPacket )
{
	sDBResponse_Get_Marry_Info* pclMsg = (sDBResponse_Get_Marry_Info*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32			siMyCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclMyChar	= pclCM->GetCharServer( siMyCharID );
	if ( NULL == pclMyChar )
	{
		return;
	}

	if ( NULL == pclMyChar->pclMarriage )
	{
		return;
	}

	SI16 siConnectMode = MARRIAGE_MATE_CONNECT_MODE_NONE;

	// 우선 접속을 제외한 모든값들을 셋팅한다 접속관련은 아래에서
	pclMyChar->pclMarriage->Set( pclMsg->m_siMatePersonID,		pclMsg->m_szMateName,
								pclMsg->m_siWeddingDateVary,	pclMsg->m_siItemGetDateVary,	FALSE,
								pclMsg->m_siLoveLevel,			pclMsg->m_siUseDateVary,		pclMsg->m_siLimitDateVary,
								siConnectMode );

	//====================================================================
	// 결혼 했다면 정보를 체크한다
	//====================================================================
	if ( TRUE == pclMyChar->IsMarried() )
	{
		//====================================================================
		// 애정도 체크
		//====================================================================
		SI16 siCalcLoveLevel = pclMyChar->pclMarriage->CalcNowLoveLevel( pclTime->clDate.GetHourVary() );
		// 계산 되어 나온값이 현재 애정도와 다르다면
		if ( siCalcLoveLevel != pclMyChar->pclMarriage->GetLoveLevel() )
		{
			// 일단 이곳에서 설정해 주고(다른곳에서 계산될때도 LoveLevel이 쓰이므로)
			pclMyChar->pclMarriage->SetLoveLevel( siCalcLoveLevel );
			pclMyChar->pclMarriage->SetLimitHourVary( pclMsg->m_siLimitDateVary + 24 );

			// DB로 보낸다
			sDBRequest_Marry_Love_Set clMsg( pclMyChar->pclCI->GetPersonID(), 
											pclMyChar->pclMarriage->GetUseHourVary(), pclMyChar->pclMarriage->GetLimitHourVary(),
											pclMyChar->pclMarriage->GetLoveLevel() );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}

		//====================================================================
		// 배우자 체크
		//====================================================================
		SI32			siMateCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siMatePersonID );
		cltCharServer*	pclMateChar		= pclCM->GetCharServer( siMateCharID );
		if ( (pclMateChar) && (pclMateChar->pclMarriage) )
		{
			// 위에서 계산한 애정도 검사를 배우자 캐릭터도 검사한다
			if ( siCalcLoveLevel != pclMateChar->pclMarriage->GetLoveLevel() )
			{
				// 서버 케릭터에 변경시키고
				pclMateChar->pclMarriage->SetLoveLevel( siCalcLoveLevel );
				pclMateChar->pclMarriage->SetLimitHourVary( pclMsg->m_siLimitDateVary + 24 );

				// DB로 보낸다
				sDBRequest_Marry_Love_Set clMsg( pclMateChar->pclCI->GetPersonID(), 
											pclMateChar->pclMarriage->GetUseHourVary(), pclMateChar->pclMarriage->GetLimitHourVary(),
											pclMateChar->pclMarriage->GetLoveLevel() );
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}

			// 배우자가 접속해 있다고 설정해 준다
			siConnectMode = MARRIAGE_MATE_CONNECT_MODE_CONNECT;

			SI16 siLoveLevel = pclMateChar->pclMarriage->GetLoveLevel();

			// 동일 맵상에 있어야 한다
			if ( pclMyChar->GetMapIndex() == pclMateChar->GetMapIndex() )
			{
				siConnectMode = MARRIAGE_MATE_CONNECT_MODE_SAMEMAP;

				cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_DISPLAYLOVELEVEL, false, siLoveLevel );
				cltGameMsgResponse_StatusInfo	clInfo( pclMateChar->GetCharUnique(), &clChangeInfo );

				cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo );
				pclMateChar->SendNeighbourMsg( &clStatusInfoMsg, false );
			}

			pclMateChar->pclMarriage->SetConnectMode( siConnectMode );

			SendServerResponseMsg( 0, SRVAL_SET_MARRY_WITHSAMEMAP, siConnectMode, siLoveLevel, pclMateChar->GetCharUnique() );
		}
	}

	// 이곳에서 접속 관련 셋팅을 해준다
	pclMyChar->pclMarriage->SetConnectMode( siConnectMode );

	// 클라이언트로 정보를 보낸다
	cltGameResponse_Get_Marry_Info clinfo( pclMsg->m_siMatePersonID,	pclMsg->m_szMateName, 
										pclMsg->m_siWeddingDateVary,	pclMsg->m_siItemGetDateVary,
										pclMsg->m_siLoveLevel,			pclMsg->m_siUseDateVary,		pclMsg->m_siLimitDateVary,
										siConnectMode );

	cltMsg clMsg( GAMEMSG_RESPONSE_GET_MARRY_INFO, sizeof(clinfo), (BYTE*)&clinfo );
	pclMyChar->SendNetMsg( (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_DBMSG_RESPONSE_MARRY_ITEMGET_SET(sPacketHeader* pPacket)
{
	sDBResponse_Marry_ItemGet_Set* pclMsg = (sDBResponse_Marry_ItemGet_Set*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( (0 > pclMsg->m_siPersonID) || (0 > pclMsg->m_siItemGetDateVary) )
	{
		return;
	}

	SI32			siMyCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclMyChar	= pclCM->GetCharServer( siMyCharID );
	if ( NULL == pclMyChar )
	{
		return;
	}

	// 혹시 결혼을 안했다면?
	if ( FALSE == pclMyChar->IsMarried() )
	{
		return;
	}

	// 요청했던것은 풀어주고
	pclMyChar->pclMarriage->SetRequestItemGet( FALSE );

	// 서버케릭터 셋팅해 주고
	pclMyChar->pclMarriage->SetItemGetDateVary( pclMsg->m_siItemGetDateVary );

	// 클라이언트에도 보내준다
	cltGameResponse_Marry_ItemGet_Set clinfo( pclMsg->m_siItemGetDateVary );
	cltMsg clMsg( GAMEMSG_RESPONSE_MARRY_ITEMGET_SET, sizeof(clinfo), (BYTE*)&clinfo );
	pclMyChar->SendNetMsg( (sPacketHeader*)&clMsg );

}

void cltServer::DoMsg_DBMSG_RESPONSE_MARRY_LOVE_SET(sPacketHeader* pPacket)
{
	sDBResponse_Marry_Love_Set* pclMsg = (sDBResponse_Marry_Love_Set*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI16 siLoveLevel		= pclMsg->m_siLoveLevel;
	SI32 siUseHourVary		= pclMsg->m_siUseHourVary;
	SI32 siLimitHourVary	= pclMsg->m_siLimitHourVary;

	// 내 캐릭터
	SI32			siMyCharID	= pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	cltCharServer*	pclMyChar	= pclCM->GetCharServer( siMyCharID );
	if ( NULL == pclMyChar )
	{
		return;
	}

	if ( FALSE == pclMyChar->IsMarried() )
	{
		return;
	}

	pclMyChar->pclMarriage->SetLoveLevel( siLoveLevel );
	pclMyChar->pclMarriage->SetUseHourVary( siUseHourVary );
	pclMyChar->pclMarriage->SetLimitHourVary( siLimitHourVary );

	cltGameResponse_Marry_Love_Set clinfo( siLoveLevel, siUseHourVary, siLimitHourVary );
	cltMsg clMsg( GAMEMSG_RESPONSE_MARRY_LOVE_SET, sizeof(clinfo), (BYTE*)&clinfo );
	pclMyChar->SendNetMsg( (sPacketHeader*)&clMsg );


	// 배우자 캐릭터
	SI32			siMateCharID	= pclCM->GetIDFromPersonID( pclMyChar->pclMarriage->GetMatePersonID() );
	cltCharServer*	pclMateChar		= pclCM->GetCharServer( siMateCharID );
	if ( NULL == pclMateChar )
	{
		return;
	}

	if ( FALSE == pclMateChar->IsMarried() )
	{
		return;
	}

	pclMateChar->pclMarriage->SetLoveLevel( siLoveLevel );
	pclMateChar->pclMarriage->SetLimitHourVary( siLimitHourVary );

	cltGameResponse_Marry_Love_Set clMateInfo( siLoveLevel, pclMateChar->pclMarriage->GetUseHourVary(), siLimitHourVary );
	cltMsg clMateMsg( GAMEMSG_RESPONSE_MARRY_LOVE_SET, sizeof(clMateInfo), (BYTE*)&clMateInfo );
	pclMateChar->SendNetMsg( (sPacketHeader*)&clMateMsg );


	// 두사람이 같은 맵에 있을경우 애정도를 주위사람에게 보내준다
	if ( pclMyChar->GetMapIndex() == pclMateChar->GetMapIndex() )
	{
		cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_DISPLAYLOVELEVEL, false, siLoveLevel );

		cltGameMsgResponse_StatusInfo	clMyInfo( pclMyChar->GetCharUnique(), &clChangeInfo );
		cltMsg clMyStatusInfoMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clMyInfo), (BYTE*)&clMyInfo );
		pclMyChar->SendNeighbourMsg( &clMyStatusInfoMsg, false );

		cltGameMsgResponse_StatusInfo	clMateInfo( pclMateChar->GetCharUnique(), &clChangeInfo );
		cltMsg clMateStatusInfoMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clMateInfo), (BYTE*)&clMateInfo );
		pclMateChar->SendNeighbourMsg( &clMateStatusInfoMsg, false );
	}

}
void cltServer::DoMsg_DBMSG_RESPONSE_GET_FAMILYINFO( sPacketHeader* pPacket )
{
	sDBResponse_Get_FamilyInfo* pclMsg = (sDBResponse_Get_FamilyInfo*)pPacket;
	UpdateFamily(&pclMsg->m_cFamily,pclMsg->m_siPersonID)	;
}
void cltServer::DoMsg_DBMSG_RESPONSE_FAMILY_ADD_CHILDREN( sPacketHeader* pPacket )
{
	sDBResponse_Family_Add_Children* pclMsg = (sDBResponse_Family_Add_Children*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	UpdateFamily(&pclMsg->m_cFamily,0)	;	// 뒤에 퍼슨아이디는 갱신할때 가족없는 친구들을 위해서 넣은거다 다른경우는 필요 없다.
}
void cltServer::DoMsg_DBMSG_RESPONSE_FAMILY_DEL_CHILDREN( sPacketHeader* pPacket )
{
	sDBResponse_Family_Del_Children* pclMsg = (sDBResponse_Family_Del_Children*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	UpdateFamily(&pclMsg->m_cFamily,0)	;	// 델일때는 지운 놈한테는 보낼필요가 없어서 db에서 personid를 안받았다 가족들만 지운놈 업데이트
}
void cltServer::DoMsg_DBMSG_RESPONSE_FAMILY_PLUS_ADD_DATE( sPacketHeader* pPacket )
{
	sDBResponse_Family_Plus_Add_Date* pclMsg = (sDBResponse_Family_Plus_Add_Date*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	UpdateFamily(&pclMsg->m_cFamily,0)	;	// 얘도 싹 다 해주는거라 personId를 안받음
}
void cltServer::DoMsg_DBMSG_RESPONSE_FAMILY__SET_COOKIE_EFFECT( sPacketHeader* pPacket )
{
	// 쿠키는 혼자만 받으면 되네 -0- 이러면 다 받을 필요 없이 그냥 업데이트 하는 방법으로 해야지.
	sDBResponse_Set_My_CookeEffect * pclMsg = (sDBResponse_Set_My_CookeEffect *)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}
	UpdateFamily(&pclMsg->m_cFamily,pclMsg->m_siPersonID)	;
}

void cltServer::DoMsg_DBMSG_RESPONSE_PERSONSLOTNUMCHANGE(sPacketHeader* pPacket)
{
	sDBResponse_PersonSlotNumChange* pclMsg = (sDBResponse_PersonSlotNumChange*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	SI32			siGetID	= pclMsg->m_uiCharID;
	cltCharServer*	pclChar	= pclCM->GetCharServer( siGetID );
	if ( NULL == pclChar )
	{
		return;
	}

	// 리스트를 다시 읽어오도록 한다
	sDBRequest_PersonListInfoGet clMsg( pclMsg->m_uiCharID, pclChar->pclCI->clBI.siIDNum );
	SendDBMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg );


	// [종호_NHN->NDOORS] 캐릭터보관소에서 캐릭터 꺼낼때
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_CHARACTOR, 
								LOGCOMMAND_INDEX_CHARHOUSE_GET, 
								0, 
								pclChar, 
								NULL, 
								0, 
								0, 
								0, 
								NULL, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								0, 
								(TCHAR*)pclChar->pclCI->clBI.GetName(), 
								NULL);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET(sPacketHeader* pPacket)
{
	sDBResponse_SkillBook_MagicInfo_Get* pclMsg = (sDBResponse_SkillBook_MagicInfo_Get*)pPacket;

	if( 0 >= pclMsg->m_siResult ) return;

	cltCharServer*	pclChar	= pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclChar ) return;

	SI32 siCount = 0;
	for( siCount = 0; siCount < SKILLBOOK_MAGIC_NUM; ++siCount )
	{
		if(    0 >= pclMsg->m_clAddSkillBookMagic[siCount].GetMagicKind() 
			|| 0 >= pclMsg->m_clAddSkillBookMagic[siCount].GetSkillUnique() )
		{
			break;	
		} 

		pclChar->pclCharSkillBookInfo->SetSkillBookMagic( pclMsg->m_iIndex[siCount], &pclMsg->m_clAddSkillBookMagic[siCount] );
	}

	for( siCount = 0; siCount < MAX_SKILLBOOK_SUBMAGIC_NUM; ++siCount )
	{
		if(    0 >= pclMsg->m_clAddSkillBookSubMagic[siCount].GetMagicKind() 
			|| 0 >= pclMsg->m_clAddSkillBookSubMagic[siCount].GetParentMagicKind() )
		{
			break;	
		}
		pclChar->pclCharSkillBookInfo->AddSkillBookSubMagic( &pclMsg->m_clAddSkillBookSubMagic[siCount] );
	}

	cltGameMsgResponse_SkillBook_MagicInfo_Get clInfo;
	memcpy( clInfo.m_iIndex,					pclMsg->m_iIndex,					sizeof(clInfo.m_iIndex) );
	memcpy( clInfo.m_clAddSkillBookMagic,		pclMsg->m_clAddSkillBookMagic,		sizeof(clInfo.m_clAddSkillBookMagic) );
	memcpy( clInfo.m_clAddSkillBookSubMagic,	pclMsg->m_clAddSkillBookSubMagic,	sizeof(clInfo.m_clAddSkillBookSubMagic) );
	cltMsg clMsg( GAMEMSG_RESPONSE_SKILLBOOK_MAGICINFO_GET, PACKET(clInfo) );
	pclChar->SendNetMsg((sPacketHeader*)&clMsg );
}


void cltServer::DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGIC_ADD(sPacketHeader* pPacket)
{
	sDBResponse_SkillBook_Magic_Add* pclMsg = (sDBResponse_SkillBook_Magic_Add*)pPacket;

	if( 0 >= pclMsg->m_siResult ) return;

	cltCharServer*	pclChar	= pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->AddSkillBookMagic( pclChar->GetAttackType(), &pclMsg->m_clAddSkillBookMagic );
	
	cltSkillBookMagic*	pclSkillBookMagic = pclChar->pclCharSkillBookInfo->GetSkillBookMagic( pclChar->GetAttackType() );	
	if( NULL == pclSkillBookMagic ) return;

	cltGameMsgResponse_SkillBook_Magic_Add clInfo( pclSkillBookMagic );
	cltMsg clMsg( GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_ADD, PACKET(clInfo) );
	pclChar->SendNetMsg((sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SKILLBOOK_MAGIC_DEL(sPacketHeader* pPacket)
{
	sDBResponse_SkillBook_Magic_Del* pclMsg = (sDBResponse_SkillBook_Magic_Del*)pPacket;

	if( 0 >= pclMsg->m_siResult ) return;

	cltCharServer*	pclChar	= pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclChar ) return;

	cltSkillBookMagic* pclSkillBookMagic = pclChar->pclCharSkillBookInfo->GetSkillBookMagicIndex( pclMsg->m_iIndex );
	if( pclSkillBookMagic )
	{
		cltLetterMsg_SkillBookMagicDel clletter( pclSkillBookMagic->GetMagicKind() );
		SendLetterMsg(pclChar->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );
	}

	pclChar->pclCharSkillBookInfo->DelSkillBookMagic( pclMsg->m_iIndex );

	cltGameMsgResponse_SkillBook_Magic_Del clInfo( pclMsg->m_iIndex );
	cltMsg clMsg( GAMEMSG_RESPONSE_SKILLBOOK_MAGIC_DEL, PACKET(clInfo) );
	pclChar->SendNetMsg((sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD(sPacketHeader* pPacket)
{
	sDBResponse_SkillBook_SubMagic_Add* pclMsg = (sDBResponse_SkillBook_SubMagic_Add*)pPacket;

	if( 0 >= pclMsg->m_siResult ) return;

	cltCharServer*	pclChar	= pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->AddSkillBookSubMagic( &pclMsg->m_clAddSkillBookSubMagic );

	cltGameMsgResponse_SkillBook_SubMagic_Add clInfo( &pclMsg->m_clAddSkillBookSubMagic );
	cltMsg clMsg( GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_ADD, PACKET(clInfo) );
	pclChar->SendNetMsg((sPacketHeader*)&clMsg );
} 

void cltServer::DoMsg_DBMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL(sPacketHeader* pPacket)
{
	sDBResponse_SkillBook_SubMagic_Del* pclMsg = (sDBResponse_SkillBook_SubMagic_Del*)pPacket;

	if( 0 >= pclMsg->m_siResult ) return;

	cltCharServer*	pclChar	= pclCM->GetCharServer( pclMsg->m_usCharID );
	if( NULL == pclChar ) return;

	pclChar->pclCharSkillBookInfo->DelSkillBookSubMagic( &pclMsg->m_clAddSkillBookSubMagic );

	cltGameMsgResponse_SkillBook_SubMagic_Del clInfo( &pclMsg->m_clAddSkillBookSubMagic );
	cltMsg clMsg( GAMEMSG_RESPONSE_SKILLBOOK_SUBMAGIC_DEL, PACKET(clInfo) );
	pclChar->SendNetMsg((sPacketHeader*)&clMsg );

	if( pclMsg->m_bTimeOver )
	{
		cltLetterMsg_SkillBookMagicDel clletter( pclMsg->m_clAddSkillBookSubMagic.GetMagicKind() );
		SendLetterMsg(pclChar->pclCI->GetPersonID(), (cltLetterHeader*)&clletter );
	}
}