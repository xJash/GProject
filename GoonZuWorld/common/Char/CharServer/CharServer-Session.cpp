//---------------------------------
// 2004/11/16 김태곤
//---------------------------------

#include "CommonLogic.h"
#include "..\CommonLogic\Msg\MsgType-Friend.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "Server.h"
#include "..\..\Server\Statistics\Statistics.h"
#include "../../Server/GameDBProcess/LogDBProcess.h"

#include "Char-Server.h"
#include "Char\CharManager\CharManager.h"
#include "..\Common\Father\Father.h"
#include "Master\Master.h"
#include "../../../Client/NInterface/NMaster/NMaster.h"

#include "Ask\Ask.h"
#include "..\Common\PartyMgr\PartyMgr.h"

#include "..\Common\PrivateTradeOrderMgr\PrivateTradeOrderMgr.h"
#include "Autohunting\Autohunting.h"

#include "HashTable/HashTable_StringInt.h"
#include "HashTable/HashTable_IntInt.h"


#include "..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest2.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-DailyQuest3.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Summon.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Village.h"
//#include "..\..\DBManager\GameDBManager_World\dbgamelogmsg.h"
#include "../../DBManager/GameDBManager_World/DBLogMsg.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"



#include "ITZSession.h"
#include "ITZSendBuffer.h"

#include "../../Server/AuthServer/AuthMsg.h"

#include "../../../Apex/ApexGoonZu.h"

#include "../../CommonLogic/MsgRval-Define.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PostOffice.h"

extern cltCommonLogic* pclClient;

///----------------------------------
// Session 생성시 호출 함수. 
//-----------------------------------
void cltCharServer::Init()
{
	ITZPerson::Init();

	// 캐릭터 생성 
	// 일반 캐릭터를 설정한다. 
	pclClient->MakeSimpleChar(m_uiCharID, m_uiCharID);

	// 암호화키와 유니크 값을 클라이언트에 보낼 것을 요청한다. 
	// 캐릭터가 생성되고 한번만 이루어지면 된다. 
	bSendSecretNCHarUniqueSwitch = true;

	siAccountStatus = -2;

#ifdef USE_GAME_GUARD_SERVER
	// 게임가드 객체 초기화
	CCSAuthInit();
#endif
}

// 게임을 종료하기 전에 캐릭터가 수행해야 할 일들. 
void cltCharServer::CloseAction(cltServer* pclServer, bool bnormalquitswitch)
{
	//	cltServer* pclserver = (cltServer*)pclClient;

	// PC방 로그아웃
	if( pclCI->clBI.bPCRoom) {

		pclCI->clBI.uiGMMode = false;
		pclServer->siPCRoomCharNum--;
	}
	//---------------------------------------------
	// 예약 되어 있는 아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	ItemUseReserveAction();

	//---------------------------------------------
	// 예약 되어 있는 탄환 아이템사용이 있다면 처리한다. 
	//---------------------------------------------
	BulletUseReserveAction();

	//------------------------------------------
	// 소환수가 있으면 제거한다.
	//------------------------------------------
	// DB에 소환수를 설정한다.
	SendDBSummon(SETSUMMON_REASON_UPDATE, MAX_SUMMON_OWN);

	SI32 siSummonID = GetSummonID();
	if(pclCM->IsValidID(siSummonID))
	{
		// 셀 내에서의 정보를 삭제한다. 
		pclCM->CR[siSummonID]->DeleteInCell();
		pclCM->DeleteChar(siSummonID);
	}

	//------------------------------------------
	// 수호정령이 있으면 삭제한다
	//------------------------------------------
	DeleteSoulGuard( );

	//----------------------------------
	// 스승 신청자 리스트에서 삭제한다. 
	//-----------------------------------
	pclClient->pclFatherManager->DeleteApplyer(pclCI->GetPersonID());

	//----------------------------------
	// 장인 리스트에서 삭제한다. 
	//----------------------------------
	pclClient->pclMasterManager->Delete(GetID());

	//----------------------------------
	// 질문 리스트에서 삭제한다. 
	//----------------------------------
	//	if(pclClient->pclAskManager)
	//{
	//	pclClient->pclAskManager->DelAskPersonID(pclCI->GetPersonID());
	//}

	//[진성] 도우미. 질문삭제. 답변자인 경우는 답변자로 등록한 것 삭제.
	pclClient->pclHelperManager->DelQuestion( this );
	pclClient->pclHelperManager->DelAnswer( this );

	//[진성] 파티홀에서 얻은 아이템 삭제.
	PartyHallItemRemove(siID);

	//-----------------------------------
	// 파티 중이었다면, 파티를 종료 시켜준다.
	//-----------------------------------
	if ( siPartyIndex > 0 )
	{
		SI32 siRet = 0;		
		pclClient->pclPartyMgr->LeaveParty( pclCI->GetPersonID(), siPartyIndex, &siRet );
		siPartyIndex = 0;
	}

	// 파티매칭에 리스트를 등록한 상태였다면 리스트를 지워준다.
	if ( NULL != pclClient->m_pServer_PartyMatchingMgr )
	{
		pclClient->m_pServer_PartyMatchingMgr->Remove_PartyMatching( GetCharUnique() );
	}


	//-----------------------------------
	// 거래창을 사용중이었다면 반환한다.
	//-----------------------------------
	pclClient->pclPrivateTradeOrderMgr->Cancel( pclCI->GetPersonID() );

	//----------------------------------------------------------------
	// 자동 사냥 의뢰중이었다면 삭제한다.
	//-----------------------------------------------------------------
	//pclClient->pclAutoHuntingManager->DeletePerson(pclCI->clBI.GetName());


	//-----------------------------------
	// 접속을 종료 했음을 친구들에게 알림
	//-----------------------------------

	if(pclFriendInfo)
	{
		for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			if ( pclFriendInfo->clFriend[ i ].siPersonID > 0 )
			{
				SI32 ToID = pclClient->pclCM->GetIDFromPersonID( pclFriendInfo->clFriend[ i ].siPersonID );

				if ( pclCM->IsValidID(ToID) )
				{
					cltGameMsgResponse_FriendLogOut clGameMsgResponse_FriendLogOut( pclCI->GetPersonID() );
					cltMsg clMsg( GAMEMSG_RESPONSE_FRIENDLOGOUT, sizeof( clGameMsgResponse_FriendLogOut ), (BYTE*)&clGameMsgResponse_FriendLogOut );
					pclClient->pclCM->CR[ToID]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
	}

	//-----------------------------------
	// DailyQuest 마지막 정보 저장해둠.
	//-----------------------------------
	if ( pclCI->clDailyQuestInfo.siMonsterKind > 0 )
	{
		sDBRequest_DailyQuestChange clMsg( pclCI->GetPersonID(), GetID(), pclCI->clDailyQuestInfo.siKillMonsterNum, pclCI->clDailyQuestInfo.siLeftTime, pclCI->clDailyQuestInfo.siMonsterKind );
		pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	//-----------------------------------
	// DailyQuest2 마지막 정보 저장해둠.
	//-----------------------------------
	if ( pclCI->clDailyQuest2Info.siMonsterKind > 0 )
	{
		sDBRequest_DailyQuest2Change clMsg( pclCI->GetPersonID(), GetID(), pclCI->clDailyQuest2Info.siKillMonsterNum, pclCI->clDailyQuest2Info.siLeftTime, pclCI->clDailyQuest2Info.bHiddenQuest, pclCI->clDailyQuest2Info.siMonsterKind );
		pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	//-----------------------------------
	// DailyQuest3 마지막 정보 저장해둠.
	//-----------------------------------
	if ( pclCI->clDailyQuest3Info.siItemUnique > 0 )
	{
		sDBRequest_DailyQuest3Change clMsg( pclCI->GetPersonID(), GetID(), pclCI->clDailyQuest3Info.siMadeItemNum, pclCI->clDailyQuest3Info.siLeftTime, pclCI->clDailyQuest3Info.bHiddenQuest );
		pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	// 만약 로그 아웃할때 PVP 중이라면
	SI32 siIID	=	GetID()	;
	if(pclCM->IsValidID( siIID ) == true )
	{
		if( pclCM->CR[siIID]->siEnemUnique	>	0 )
		{
			cltServer* pclserver = (cltServer*)pclClient;

			SI32 siWarpChar	=	siIID	;	// 워프한 케릭터 질 케릭터.
			if( pclCM->IsValidID( siWarpChar ) == false )	return	;// 정상 아이디 인지 검사 부터 
			SI32 siWarpChaeParentID = pclCM->CR[siWarpChar]->GetSummonParentID()	;		// 워프탄 케릭터의 부모 케릭터를 구한다.
			if ( siWarpChaeParentID == 0 ) siWarpChaeParentID = siWarpChar	;				// 만약 워프탄 케릭터가 본케면 그냥 아이디를 쓴다.
			cltCharServer* pclWarpChar = pclCM->GetCharServer(siWarpChaeParentID);			if(pclWarpChar == NULL)			return	;

			SI16 siWinnerCharID = pclWarpChar->siEnemUnique	;						// 워프 타서 졌으므로 워프탄 케릭터의 상대방 적은 무조건 이긴 케릭터이다.
			if( pclCM->IsValidID( siWinnerCharID ) == false )	return	;			// 정상 아이디 인지 검사 부터
			cltCharServer* pclWinnerChar = pclCM->GetCharServer(siWinnerCharID);			if(pclWinnerChar == NULL)			return	;

			// 워프 탓으니까 전투는 끝이다.
			pclWarpChar->siEnemUnique	=	0	;		// 각각의 케릭터 들을 초기화 해준다
			pclWinnerChar->siEnemUnique	=	0	;
			if( pclClient->IsCountrySwitch( Switch_ValenTineWar ) )
			{
				//발렌타인데이 전쟁 관련 체크, 커플이나 솔로라고 정했고, 아이템을 받지 않았을 경우에만 준다.
				SI32 siCouple = pclWinnerChar->pclValentineWar->GetCouple()	;// 이긴 사람의 커플 여부
				SI32 siLoser = pclWarpChar->pclValentineWar->GetCouple()	;// 진 사람의 커플 여부
				bool bGetPrize = pclWinnerChar->pclValentineWar->GetPrize()	;	// 이긴사람이 아이템을 받았었는지
				if( abs(pclWarpChar->pclCI->clIP.GetLevel() - pclWarpChar->pclCI->clIP.GetLevel() ) < 11
					&& siCouple != 0 && siLoser != 0
					&& siCouple != siLoser 
					&& bGetPrize == false )
				{
					SI32 siRewardItemUnique	=	ITEMUNIQUE(2781) ;
					if( siRewardItemUnique ) 
					{
						cltItem clItem;
						SI16 brareswitch = 0;
						if ( pclClient->pclItemManager->MakeRandItemUnique( siRewardItemUnique,&clItem,0,0,&brareswitch,0,0,0,0,0) == true ) 
						{
							clItem.siItemNum = 1;
							SI32 rtnvalue = 0;
							if(pclWinnerChar->InputItem(pclClient->pclItemManager, &clItem, INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, &rtnvalue))
							{
								// 아이템을 주고 줬다고 셋팅 해준다.
								sDBRequest_Valantine_Get_Prize clMsg( pclWinnerChar->pclCI->GetPersonID(), true );
								pclServer->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
							}
							else
							{
								if(rtnvalue == CANADDINV_FAIL_FULL)
								{
									sDBRequest_PostOfficeMasterSendItem clMsg( INPUTITEMPERSON_OPTION_VALENTINEWAR_PRIZE, 0, (TCHAR*)pclWinnerChar->GetName(), &clItem,&pclServer->pclTime->clDate );
									pclServer-> pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
									// 아이템을 주고 줬다고 셋팅 해준다.
									sDBRequest_Valantine_Get_Prize clMsg2( pclWinnerChar->pclCI->GetPersonID(), true );
									pclServer->pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
								}
							}
						}		
					}
				}

			}			 
			// 각기 클라이언트로 알려준다.
			{//승리자
				// 개인간 pvp가 끝나면서 각종 중독상태 제거
				pclWinnerChar->DeletePoison();						// 중독 상태를 삭제한다.
				pclWinnerChar->DeletePoisonSetItemEffect();			// 중독 상태를 삭제한다.
				pclWinnerChar->DeleteIce();							// 얼음 상태를 삭제한다.
				pclWinnerChar->DeleteCurseAttack();					// 공격력이 저하 상태를 삭제한다.
				pclWinnerChar->DeleteCurseCritical();				// Critical 확률이 낮아지는 상태를 삭제한다.
				pclWinnerChar->DeleteCurseDefense();				// 방어력이 낮아지는 상태를 삭제한다.
				pclWinnerChar->DeleteCurseMovespeed();				// 이동속도 저하 상태를 삭제한다.
				pclWinnerChar->DeleteMagicFire();					// 불에 타는 상태를 삭제한다.
				pclWinnerChar->DeleteFrozen();						// 보스 얼음 상태를 삭제한다.
			}
			// 승리자
			cltGameMsgResponse_PVP_Request clWinner( END_PVP , WIN_PVP, pclWinnerChar->GetCharUnique(), TEXT("") );	
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
			pclWinnerChar->SendNeighbourMsg(&clMsg, true);

			pclWinnerChar->IncQuestPara( QUEST_CLEAR_COND_PVPWIN, 0, 1 );

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [로그추가 : 손서웅ㅇ 2008. 10. 29] // pvp 비김
				// PCK : 수정 - PersonID로 캐릭터이름을 구해서 좀더 보기 쉽게한다. (09.07.31)
				// para1	:	승리자 personID
				// para2	:	패배자 personID

				TCHAR szCharName[100];
				ZeroMemory(szCharName, sizeof(szCharName));
				StringCchPrintf(szCharName, sizeof(szCharName), TEXT("WinnerChar:%s, LoserChar:%s"), pclWinnerChar->GetName(), pclWarpChar->GetName());

				pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_END_LOGOUT, 
					0, this,NULL, 0, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 
					pclWinnerChar->pclCI->GetPersonID(), 
					pclWarpChar->pclCI->GetPersonID(), 0, 0, 0, szCharName, NULL);
			}
			{
				// 서버에 남긴다.
				TCHAR fileNameBuffer[256];
				//슬롯에 찍을 시간을 텍스트로 완성한다.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime,  sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPEND_LOGOUT \tWINOPERSON : \t[%s]\t \t LOSEPERSON2 : \t[%s]\t Time"),
					pclWinnerChar->GetName(),pclWarpChar->GetName(),szBuffer0 );
			}
		}
	}

	//---------------------------------
	// 진행중인 퀘스트 저장. 
	//---------------------------------
	pclCI->clQuestInfo.SaveGoingQuestToDB(this);

	//---------------------------------
	// 결혼 시스템 : 접속 종료
	//---------------------------------
	if ( pclServer->IsCountrySwitch(Switch_WeddingSystem) )
	{
		// 배우자와 동일 맵상에 있었을 경우 배우자와 주변캐릭터 정보를 갱신한다
		if ( (TRUE == IsMarried()) && (MARRIAGE_MATE_CONNECT_MODE_NONE < pclMarriage->GetConnectMode()) )
		{
			SI32			siMateCharID	= pclServer->pclCM->GetIDFromPersonID( pclMarriage->GetMatePersonID() );
			cltCharServer*	pclMateChar		= pclServer->pclCM->GetCharServer( siMateCharID );
			if ( (pclMateChar) && (pclMateChar->IsMarried()) && (pclMateChar->pclMarriage->GetMatePersonID() == pclCI->GetPersonID()) )
			{
				// 우선 서버내 캐릭터 설정
				pclMateChar->pclMarriage->SetConnectMode( MARRIAGE_MATE_CONNECT_MODE_NONE );

				// 배우자 주변 캐릭터에게 바뀐 정보를 보내고
				cltCharChangeStatusInfo			clChangeInfo( CHANGETYPE_DISPLAYLOVELEVEL, false, 0 );
				cltGameMsgResponse_StatusInfo	clInfo( pclMateChar->GetCharUnique(), &clChangeInfo );

				cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clInfo), (BYTE*)&clInfo );
				pclMateChar->SendNeighbourMsg( &clStatusInfoMsg, false );

				// 배우자에게는 접속 정보와 애정도를 같이 보낸다
				pclServer->SendServerResponseMsg( 0, SRVAL_SET_MARRY_WITHSAMEMAP, MARRIAGE_MATE_CONNECT_MODE_NONE, pclMateChar->pclMarriage->GetLoveLevel(), pclMateChar->GetCharUnique() );

			}
		}
	}
	// 접속 종료 하면서 커넥트 한 사람들에게 자신이 나간걸 셋해준다.
	if ( pclClient->IsCountrySwitch(Switch_We_Are_Family) )
	{
		if(pclFamily != NULL )
		{
			if (  pclFamily->GetParent_1() > 0 )	// 내가 부모케릭터에 대한 정보를 가진 건 가족이 있다는 것이다.
			{
				// 내가 나간다고 다 알려줘야 한다.
				SI32 siMyPersonID = pclCI->GetPersonID()	;
				// 나를 찾는다
				// 내 가족 등급 확인
				SI32 siMyClass = pclFamily->GetMyClass_InFamily()	;

				if( siMyClass == MYCLASS_IN_FAMILY_PARANTS)
				{
					for (  SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM; siSlot++) 
					{
						SI32 siPersonID = pclFamily->GetParent_PersonId( siSlot )	;
						if ( siPersonID == siMyPersonID )	// 나다 .
						{
							pclFamily->ConnectOut(siMyPersonID, MYCLASS_IN_FAMILY_PARANTS)	;//빼고 업데이트
						}

					}
				}
				else if( siMyClass == MYCLASS_IN_FAMILY_CHILDREN)
				{
					for (  SI32 siSlot = 0 ; siSlot <MAX_CHILDREN_NUM; siSlot++) 
					{
						SI32 siPersonID = pclFamily->GetChildPersonID( siSlot )	;
						if ( siPersonID == siMyPersonID )	// 나다 .
						{
							pclFamily->ConnectOut(siMyPersonID, MYCLASS_IN_FAMILY_CHILDREN)	;//빼고 업데이트
						}

					}
				}

				CFamily FamilyData ;
				FamilyData.Init()	;
				FamilyData.Set( pclFamily );

				//갱신한 로그아웃 정보를 날려준다.
				for ( SI32 siSlot = 0 ; siSlot < MAX_PARENT_NUM ; siSlot++ ) 
				{
					SI32 siFamilyPersonID = FamilyData.GetParent_PersonId( siSlot )	;
					SI32 siFamilyId = pclCM->GetIDFromPersonID( siFamilyPersonID )	;
					if ( pclCM->IsValidID( siFamilyId ) == false )	continue ;	//아이디의 유효성 검사.
					cltCharServer* pclChar = pclCM->GetCharServer( siFamilyId )	;
					FamilyData.SetMyClass_InFamily( MYCLASS_IN_FAMILY_PARANTS )	;
					pclChar->pclFamily->Set(&FamilyData)	;
					// 클라이언트로 해당 케릭터의 정보 업데인트
					cltGameResponse_UpdateFamily clInfo( &FamilyData ,pclChar->pclMarriage);
					cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clInfo), (BYTE*)&clInfo );
					pclChar->SendNetMsg( (sPacketHeader*)&clStatusInfoMsg);
				}
				for ( SI32 siSlot = 0 ; siSlot < MAX_CHILDREN_NUM ; siSlot++ ) 
				{
					SI32 siFamilyPersonID = FamilyData.GetChildPersonID( siSlot)	;
					SI32 siFamilyId = pclCM->GetIDFromPersonID( siFamilyPersonID )	;
					if ( pclCM->IsValidID( siFamilyId ) == false )	continue ;	//아이디의 유효성 검사.
					cltCharServer* pclChar = pclCM->GetCharServer( siFamilyId )	;
					FamilyData.SetMyClass_InFamily( MYCLASS_IN_FAMILY_CHILDREN )	;
					pclChar->pclFamily->Set(&FamilyData)	;

					// 클라이언트로 해당 케릭터의 정보 업데인트
					cltGameResponse_UpdateFamily clInfo( &FamilyData ,pclChar->pclMarriage);
					cltMsg clStatusInfoMsg( GAMEMSG_RESPONSE_FAMILY_UPDATE, sizeof(clInfo), (BYTE*)&clInfo );
					pclChar->SendNetMsg( (sPacketHeader*)&clStatusInfoMsg);
				}
			}

		}
	}	
	//---------------------------------
	// 셀 내에서의 정보를 삭제한다. 
	//---------------------------------
	DeleteInCell();


	// 빠져나간 캐릭터의 정보를 DB에 저장한다. 
	SI32 idnum	= pclCI->clBI.siIDNum;


	// 주인공 캐릭터가 아닌 상태에서는 저장하지 않는다. 
	// 주인공 캐릭터가 아닐 수 있다. 맨처음 Person을 만들게 되면 구리댁으로 설정되는데 여기서 
	// 다른 영웅 캐릭터로 재설정하지 않고 게임을 끝내면 계속 구리댁으로 나오게 된다. 
	if(idnum && bReadySwitch)		
	{
		//---------------------------------
		// 전과 정보를 저장 
		//---------------------------------
		sDBRequest_GuiltyInfoRecord clMsg(GetID(), pclCI->GetPersonID(), &pclCI->clGuiltyInfo);
		pclClient->SendDBMsg(DBSELECT_BASE,  (sPacketHeader *)&clMsg );

		//------------------------
		//DB로 건강 정보를 보낸다.
		//-------------------------
		{
			sDBRequest_SetHealth clMsg(pclCI->GetPersonID(), &pclCI->clHealthInfo);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}

		//-------------------------
		// 레벨 정보를 저장한다. 
		//-------------------------
		SendDBLevelInfo(0, 0);

		//------------------------
		// 기술정보를 저장한다.
		//------------------------
		SendDBSkillExp();

		//---------------------------------
		// 내구도 정보 저장.  - 아이템의 내구도는 사용되지 않는다.
		//---------------------------------
		SendDBWasteDurability();
		SendDBSummonWasteDurability();

		//KHY - 0227 - 결정체 (크리스탈) 제조 추가. 
		SendDBCrystalDurability();
		//-------------------------------------
		// 게임 시간을 구한다. 
		//-------------------------------------
		CalcPlayTime();

		//-------------------------------------
		// 가입된 마을이 있다면 시간을 DB로 보낸다
		//-------------------------------------
		if(pclCI->clBI.siHomeVillage > 0 && pclCI->clBI.siHomeVillage <= CUR_VILLAGE_LIMIT)
		{
			sDBRequest_VillageJoinPlayTime clMsg(pclCI->GetPersonID(), pclCI->clBI.clVillageScoreInfo.siPlayTime, pclCI->clBI.siHomeVillage);
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// LEEKH MODIFY 2007.10.24
			//	// [로그추가 : 황진성 2007. 10. 9] // 유저의 마을 가입 후 플레이 시간.
			//	// param1 == 플레이 시간.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_VILLAGE, LOGCOMMAND_INDEX_VILLAGE_JOIN_PLAY_TIME, 
			//									0, this, NULL, 0, 0, 0, NULL, 0, 0, 0, pclCI->clBI.siHomeVillage, 0, 0, 
			//									pclCI->clBI.clVillageScoreInfo.siPlayTime, 0, 0, 0, 0, NULL, NULL);
			//}
		}


		//---------------------------------
		// 체력, 마법력, 위치 정보 저장. 
		//---------------------------------
		{
			SendDB_PosLifeMana();

			// 유효하지 않은 지역이면, 
			if(pclClient->pclMapManager->IsValidArea(pclCI->clBI.clPos.siMapIndex, pclCI->clBI.clPos.GetX(), pclCI->clBI.clPos.GetY()) == false)
			{
				pclClient->pclLog->FilePrint(TEXT("Config\\ErrorLog.log"), TEXT("InvalidArea:Close() map:%d x:%d y:%d life:%d"), 
					pclCI->clBI.clPos.siMapIndex, pclCI->clBI.clPos.GetX(), pclCI->clBI.clPos.GetY(), GetLife());

			}
		}
		//-----------------------------------
		// 종량제 서비스 데이터 저장
		//---------------------------------
		// 종량제에 포함된 시스템의 시간도 같이 저장한다.

		// 종량제 시스템 처리 - by LEEKH 2008.01.04
		cltTimeMeterRateInfo* pclTimeMeterRateInfo = &pclCI->clBI.clTimeMeterRateInfo;

		for( SI32 i=0; i < MAX_TIMEMETERRATE; i++ )
		{
			cltTimeMeterRate*	pclTimeMeterRate = &pclTimeMeterRateInfo->m_clTimeMeterRate[i];
			if( pclTimeMeterRate->IsUse() )
			{
				if( pclTimeMeterRate->siUseTimeSec > 0)
				{
					// DB 로 사용량을 전송한다.
					sDBRequest_TimeMeterRate_UseTime clMsg(GetCharID(), pclCI->GetPersonID(), pclTimeMeterRate->siTimeMeterRateType, pclTimeMeterRate->siUseTimeSec, false );
					pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

					switch( pclTimeMeterRate->siTimeMeterRateType )
					{
					case TIMEMETERRATE_TRANSFORM:
						{
							if( pclTimeMeterRate->siUseTimeSec > 0)
							{
								if( clTransFormInfo.bTransFormMode )
								{
									// DB에 변신 시간을 추가해준다.
									sDBRequest_Transform_AddTime clMsg1(GetCharID(), pclCI->GetPersonID(), clTransFormInfo.uiNowTransFormKind, pclTimeMeterRate->siUseTimeSec );
									pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);
								}
							}
						}
						break;
					}
				}
			}
		}

		//------------------------------------
		// 로그 아웃 기록을 남긴다. 
		//------------------------------------
		// bnormalquitswitch	: 정상 종료했는지 여부, 
		sDBRequest_LogOutRecord cllogout(pclCI->GetPersonID(), GetSession()->GetIP(), bnormalquitswitch );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cllogout);

	}

	//------------------------------------------
	// HASH TABLE에서 제거한다.
	//------------------------------------------
	// HashTable에 PERSON 이름과 정보들을 삭제한다.
	((cltServer*)pclClient)->pclHashTable->Remove((TCHAR *)GetName());

	// HashTable에 PERSON ID와 정보들을 삭제한다.
	((cltServer*)pclClient)->pclPersonHashTable->Remove(pclCI->GetPersonID());
}
void cltCharServer::Close()
{
	cltServer *pclServer = (cltServer *)pclClient;

	// PC방 로그아웃
	if( pclCI->clBI.bPCRoom ) {

		pclCI->clBI.bPCRoom = false;
		pclServer->siPCRoomCharNum--;
	}


	//---------------------------------
	// 정상 종료인가, 비정상 종료인가. 
	//---------------------------------
	bool bnormalquitswitch = true;
	if(bHopeToQuitSwitch || (pclKI->IsAtb(ATB_HERO) == false))
	{
		pclServer->pclStatisticsManager->clDailyStatistics.siNormalQuitUserNumber ++;
		bnormalquitswitch = true;
	}
	else
	{
		pclServer->pclStatisticsManager->clDailyStatistics.siAbnormalQuitUserNumber ++;
		bnormalquitswitch = false;

		// apex-
#ifdef _CHINA
		if( 0 < GetID() )
			NoticeApexProxy_UserLogout( GetID(), (char*)pclCI->clBI.szAccountID );
		bApexLogin = false;
#endif
		// -apex
	}

	// 캐릭터가 현재 죽었는데 종료하면 가까운 마을로 보낸다.
	if( ORDER_DIE ==  GetCurrentOrder() || 
		ORDER_DEAD == GetCurrentOrder() ||
		ORDER_REVIVE == GetCurrentOrder() )
	{
		SI32 villageunique = 0;
		if(siKilledMode == KILLEDMODE_VILLAGEWAR)	{	villageunique = pclCI->clBI.siHomeVillage;		}
		else										{	villageunique = GetCurrentVillageUnique();		}

		if( villageunique <= 0 )
		{
			// 현재 위치한 지도의 부모 지도를 찾는다. 
			SI32 parentmap = pclClient->pclMapManager->GetParentMap( GetMapIndex() );
			if(parentmap == 0)parentmap = GetMapIndex();

			//cyj 죽은위치가 수렵장일 경우 parentmap이 villageunique 임
			if(pclClient->pclMapManager->IsHuntMap( GetMapIndex() ) == true)	{		villageunique = parentmap;		}
			else
			{
				// 부모 마을의 야외지역 좌표를 찾는다. 
				SI32 x, y;
				if( parentmap != 0 &&
					pclClient->pclMapManager->pclGateManager->FindMainFieldPos(parentmap, &x, &y) == true )
				{
				}
				else
				{
					x	= pclCI->clBI.clLastMainMapPos.siX;
					y	= pclCI->clBI.clLastMainMapPos.siY;

				}
				// 가까운 마을을 찾는다.
				villageunique = pclClient->pclVillageManager->FindNearVillage(x, y);
			}
		}

		SI32 centerx = 0;
		SI32 centery = 0;

		if( villageunique <= 0 )
		{
			villageunique = MAPINDEX_PALACE;
			centerx = 27;
			centery = 87;
		}
		else
		{
			SI32 maptypeunique = pclClient->pclMapManager->pclMapArray[ villageunique ]->siMapUnique;
			centerx = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
			centery = pclClient->pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
		}

		pclCI->clBI.SetMapIndex(villageunique);
		SetX(centerx);
		SetY(centerx);

		// 비정상으로 종료됐을때 두번 처리하지 않게 생명력을 채운다(클라이언트로는 보내지 않는다) -KKM-
		if( bDeathPenaltySwitch )
		{
			pclCI->clIP.SetLife( clPB.GetMaxLife() );
			SendDBLevelInfo(0, 0);
		}

		SendDB_PosLifeMana();
	}

	// Special 에선 PC방 정보를 DB Log 로 남긴다
#ifndef _DEBUG	// 디버깅할땐 국가코드 신경안씀
	if( pclClient->siServiceArea == ConstServiceArea_Korea )
#endif

	{
		SI32 playMinute = dwPlayingTime / 60;

		sDBRequest_PCRoom_Log clMsg( pclClient->siServerUnique , "K_GOONZU" , pclCI->clBI.szAccountID , 
			(TCHAR*)pclCI->clBI.GetName() , &sTimeStartTime , &((cltServer*)pclClient)->sTime , GetSession()->GetIP() , pclCI->clBI.szCRMcode ,  siLoginedLevel ,
			pclCI->clIP.GetLevel() , playMinute  ,pclCI->clIP.GetMoney() , pclCI->clBI.sPCroomGrade );

		pclClient->SendDBMsg(DBSELECT_SUB,  (sPacketHeader *)&clMsg );

	}

	// [영훈] 서버 이벤트 인던점수 종료시 저장
	if ( 0 < siServerEvent_IndunScore )
	{
		sDBRequest_Server_Event_Server_Person_Score_Set clScore( 0, pclCI->GetPersonID(), siServerEvent_IndunScore );
		pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clScore );
	}

#ifdef USE_GAME_GUARD_SERVER
	CCSAuthClose();
#endif


	// Auth Server로 유저 로그 아웃 정보를 보낸다 
	if( siIDNUM > 0 && siAccountStatus >= 0 )
	{
#ifdef _CHINA
		sRequest_GameLogout	sendMsg;

		sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GAMELOGOUT;
		sendMsg.packetHeader.usSize = sizeof( sendMsg );

		sendMsg.uiIDNum =  siIDNUM;

		memcpy( sendMsg.szAccountID, pclCI->clBI.szAccountID, 20 );
		sendMsg.szAccountID[ 19 ] = NULL;
		memcpy( sendMsg.userServerID, pclClient->szServerID, 20 );
		sendMsg.userServerID[ 19 ] = NULL;
		memcpy( sendMsg.szPlayingCharNmae, GetName(), 20 );
		sendMsg.szPlayingCharNmae[ 19 ] = NULL;

		sendMsg.siLevel = pclCI->clIP.GetLevel();

		ITZSession *pSession = pclServer->pclFrontAuthProcess->GetAuthSession();

		if( pSession )
		{
			pSession->GetSendBuffer()->Write( (BYTE*)&sendMsg );
		}

		// Gamania
		if( siAccountStatus == 2 )
		{		
			pclServer->siGamaniaCharNum--;
		}
		else if( siAccountStatus == 4 )
		{
			pclServer->siHangameCharNum--;
		}
		else if( siAccountStatus == 8 )
		{
			pclServer->siGamePotCharNum--;
		}
		else if( siAccountStatus == 0 )
		{
			pclServer->siNDECharNum--;
		}
		/*
		else if( siAccountStatus == 6 )
		{
		pclServer->siNetmarbleCharNum--;
		}
		*/
		siAccountStatus = -2;
		siIDNUM = 0;
#else
		sRequest_GameLogout	sendMsg;

		sendMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GAMELOGOUT;
		sendMsg.packetHeader.usSize = sizeof( sendMsg );

		sendMsg.uiIDNum =  siIDNUM;

		memcpy( sendMsg.szAccountID, pclCI->clBI.szAccountID, 20 );
		sendMsg.szAccountID[ 19 ] = NULL;

		ITZSession *pSession = pclServer->pclFrontAuthProcess->GetAuthSession();


		//KHY - 0218 - 중국 NHN 피로도 모듈 적용
		SI32 siplayTimeMinute = dwPlayingTime / 60;

		if(bTiredSystem) //피로도 시스템이 설정되어 있는 경우만 보낸?
		{
			pclClient->pclLog->FilePrint(TEXT("Config\\TiredSystemLog.log"), TEXT(" pclCI->clBI.szAccountIDb: %s - TiredSystem : %d  - siPlayTimeMinute:%d"), 
				pclCI->clBI.szAccountID , bTiredSystem , siplayTimeMinute);

			sendMsg.siPlayTimeMinute = siplayTimeMinute;
		}
		else
			sendMsg.siPlayTimeMinute = -1; // 일단 피로도에서만 쓰게됨으로, 기타 다른 국가에서 쓰게 될때는 이부분			

		if( pSession )
		{
			pSession->GetSendBuffer()->Write( (BYTE*)&sendMsg );
		}

		if( siAccountStatus == 4 ) // 한게임
		{
			pclServer->siHangameCharNum--;
		}
		else if( siAccountStatus == 2 ) // 감마니아
		{		
			pclServer->siGamaniaCharNum--;
		}
		else if( siAccountStatus == 8 ) // 게임팟
		{
			pclServer->siGamePotCharNum--;
		}
		else if( siAccountStatus == 0 ) // NDE
		{
			pclServer->siNDECharNum--;
#ifdef _ENGLISH		
			pclServer->siGlobalNum--;
#endif
		}
		else if( siAccountStatus == 10 ) // NEXON
		{
			pclServer->siNEXONCharNum--;
		}

#ifdef _ENGLISH		
		else if( siAccountStatus == 100 ) // NDE
		{
			pclServer->siNHNNum--;
		}
		else if( siAccountStatus == 200 ) // NEXON
		{
			pclServer->siGlobalNum--;
		}
#endif
		/*
		else if( siAccountStatus == 6 )
		{
		pclServer->siNetmarbleCharNum--;
		}
		*/

		siAccountStatus = -2;
		siIDNUM = 0;
#endif
	}

	CloseAction(pclServer, bnormalquitswitch);
	//------------------------------------------
	// 퇴출된 캐릭터를 삭제한다. 
	//------------------------------------------
	// 삭제될 캐릭터 주변의 이웃 데이터를 정리한다. 
	// 이웃캐릭터의 이웃 목록에서 파괴되는 캐릭터의 정보를 지운다.
	pclCM->DeleteChar(GetID() );

	ITZPerson::Close();
}
