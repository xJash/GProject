//---------------------------------
// 2003/11/26 김태곤
//---------------------------------

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"
#include "../Server/HelperManager/HelperManager.h"

#include "../../NLib/NUtil.h"

#include "../Common/Map/Map.h"
#include "../Common/School/School.h"
#include "Skill/Skill-Manager.h"
#include "../Common/Father/Father.h"
#include "Char/CharManager/CharManager.h"
#include "../Common/GameEvent/GameEvent.h"

#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../DBManager/GameDBManager_World/DBMsg-IPGClient.h"
#include "../../DBManager/GameDBManager_World/DBMsg-PVP_League.h"

#include "../../CommonLogic/MagicMgr/MagicMgr.h"
#include "../../CommonLogic/MagicMgr/MagicAttribute/MagicAttribute.h"

#include "../CommonLogic/MsgType-Item.h"

#include "../../common/Family/Marriage.h"

#include "MsgType-Person.h"
#include "MsgType-System.h"
#include "Msg/MsgType-Quest.h"
#include "Msg/MsgType-ItemMall.h"
#include "Msg/MsgType-Web.h"
#include "Msg/MsgType-MofuMofuEvent.h"
#include "Msg/MsgType-HappyBeanQuest.h"

#include "MsgRval-Define.h"


#include "../Common/Order/order.h"
#include "../common/Item/ItemCommon/cltSetItem.h"
#include "../../common/PVP_Leage/PVP_LeageMgr.h"

#include "../lib/MD5/md5.h"
#include "../Common/Bullet/Bullet.h"

//----------------------------------
// Server
//----------------------------------
#include "Statistics\Statistics.h"

#include "../Apex/ApexGoonZu.h"

#include "Util/Util.h"

extern cltCommonLogic* pclClient;

//CString URLEncode(CString sIn);

// IP를 보내줄 것을 요청 
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSON_IP(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id) == false)return ;

	SI32 targetid = pclMsg->siData32[0];
	if(pclCM->IsValidID(targetid) == false)return ;

	cltGameMsgResponse_IP clinfo(targetid, &pclCM->CR[targetid]->pclCI->clIP);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_IP, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// 제자 리스트 요청 
void cltServer::DoMsg_GAMEMSG_REQUEST_UPDATECHILDLIST(cltMsg* pclMsg, SI32 id)
{
	// 메시지가 너무 자주오는 것을 차단한다. 
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}


	cltGameMsgRequest_UpdateChildList* pclinfo = (cltGameMsgRequest_UpdateChildList*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// DB로 리스트를 요청한다. 
	sDBRequest_GetChildList clMsg(id, personid);
	pclGameDBProcess->SendMsg(DBSELECT_LETTER,  (sPacketHeader *)&clMsg);
}

// 스승이 제자를 짜른다.
void cltServer::DoMsg_GAMEMSG_REQUEST_RENOUNCEPUPIL(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID( id ) )
		return;

	cltGameMsgRequest_RenouncePupil* pclinfo = (cltGameMsgRequest_RenouncePupil*)pclMsg->cData;

	sDBRequest_RenouncePupil clMsg( id, pclinfo->GetPupilPersonID() );
	pclGameDBProcess->SendMsg(DBSELECT_LETTER,  (sPacketHeader *)&clMsg);

	
}

// 스승 등록 신청자 명단 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_FATHERAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_FatherApplyerList* pclinfo = (cltGameMsgRequest_FatherApplyerList*)pclMsg->cData;

#ifdef _SAFE_MEMORY
	cltGameMsgResponse_FatherApplyerList clinfo(&pclFatherManager->clApplyerList[0]);
#else
	cltGameMsgResponse_FatherApplyerList clinfo(pclFatherManager->clApplyerList);
#endif

	cltMsg clMsg(GAMEMSG_RESPONSE_FATHERAPPLYERLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

// 스승 등록 신청 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_APPLYFATHER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ApplyFather* pclinfo = (cltGameMsgRequest_ApplyFather*)pclMsg->cData;

	//KHY - 0610 - 스승제자 S 추가수정.
	if ( ConstServiceArea_Japan != pclClient->siServiceArea )
	{
		if( pclClient->siMinimumTeacherLevel > pclCM->CR[id]->pclCI->clIP.GetLevel() )
		{
			return;
		}
	}

	bool bAngel = false ;
	if ( pclCM->CR[id]->pclCI->clBI.uiAngelSwitch > 0 )
		bAngel = true ;

	cltFatherApplyerInfo clinfo(id, pclCM->CR[id]->pclCI->GetPersonID(), 
		(TCHAR*)pclCM->CR[id]->GetName(), pclCM->CR[id]->pclCI->clBI.szAccountID, 
		pclCM->CR[id]->pclCI->clIP.GetLevel(), pclCM->CR[id]->pclCI->clIP.siFameLevel,bAngel );


	// 삭제 
	if(pclinfo->siCharUnique == 0)
	{
		pclFatherManager->DeleteApplyer(pclCM->CR[id]->pclCI->GetPersonID());

		// 클라이언트로 서버의 응답값을 보낸다. 
		SendServerResponseMsg(0, SRVAL_SUCCESSDELFATHERAPPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
	else
	{

		SI32 returnval = 0;
		if(pclFatherManager->AddApplyer(&clinfo, &returnval) == true)
		{
			// 클라이언트로 서버의 응답값을 보낸다. 
			SendServerResponseMsg(0, SRVAL_SUCCESSAPPLYFATHER,  0, 0, pclCM->CR[id]->GetCharUnique());

			// 스승신청에 성공했을때만 로그를 남긴다.
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [로그추가 : 황진성 2007. 9. 7] // 스승 신청 로그쓰기. 
				// param1 == 수호천사 여부.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_APPLYFATHER, 
					0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					bAngel, 0, 0, 0, 0, NULL, NULL);
			}
		}
		else
		{
			if(returnval == ADD_FATHERSUPPLYER_ALREADY)
			{
				// 클라이언트로 서버의 응답값을 보낸다. 
				SendServerResponseMsg(0, SRVAL_FAILAPPLYFATHER_ALREADY,  0, 0, pclCM->CR[id]->GetCharUnique());

			}
			if(returnval == ADD_FATHERSUPPLYER_FULL)
			{

				// 클라이언트로 서버의 응답값을 보낸다. 
				SendServerResponseMsg(0, SRVAL_FAILAPPLYFATHER_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
			}
		}
	}
}

// 개인 상세 정보 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONPRIVATEINFO(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}

	cltGameMsgRequest_PersonPrivateInfo* pclinfo = (cltGameMsgRequest_PersonPrivateInfo*)pclMsg->cData;
	//if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)return ;
	if(pclCM->IsValidID(pclinfo->siCharUnique) == false)			return;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[pclinfo->siCharUnique];
	if(pclCM->IsValidID(pclinfo->siCharUnique)  == false)return ;

	// 클라이언트에게 통보한다. 
	cltSimplePerson clperson;
	clperson.Set(&pclchar->pclCI->clBI.clPerson);
	cltSimplePerson clfather;
	clfather.Set(&pclchar->pclCI->clBI.clFatherInfo.clFather);

	SI32 rank = pclchar->pclCI->clBI.siWealthRank;
	if ( pclchar->pclCI->clIP.GetLevel() < FATHER_LEVEL || rank <= 0 )
		rank = 0 ;

	SI32 out_villageunique	= 0;
	SI32 out_unitslot		= 0;
	SI32 out_memberindex	= 0;
	SI32 in_personid		= pclchar->pclCI->GetPersonID();/*pclCM->CR[id]->pclCI->GetPersonID();*/
	SI32 retvalue			= 0;

	cltGameMsgResponse_PersonPrivateInfo clinfo( pclchar->pclCI->clBI.szAccountID, &clperson, &clfather,
			 									 pclchar->pclCI->clIP.GetLevel(), 
												 pclchar->pclCI->clIP.siFameLevel,
												 pclchar->pclCI->clBI.siCountryID,
												 pclchar->pclCI->clBI.bShowCountry,
												 pclchar->pclCI->clBI.clFatherInfo.siFatherChangeNumber,
												 rank,
												 pclchar->pclCI->clBI.clTotalWealthMoney, 
												 pclchar->pclCI->clBI.szGreeting,
												 pclchar->pclCI->clBI.siPVPWinNumber,
												 pclchar->pclCI->clBI.siPVPLoseNumber,
												 pclchar->pclCI->clBI.szPVPWinHighLevelUserName,
												 pclchar->pclCI->clPersonNaming.m_siSelectedLevel,
												 pclchar->pclCI->clBI.clGuildRank.szGuildName,
												 pclchar->pclCI->clBI.siHomeVillage	
												 );
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONPRIVATEINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONPRIVATEINFOBYPERSONID(cltMsg* pclMsg, SI32 id)
{
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}

	cltGameMsgRequest_PersonPrivateInfoByPersonID* pclinfo = (cltGameMsgRequest_PersonPrivateInfoByPersonID*)pclMsg->cData;

	SI32 CharID = pclCM->GetIDFromPersonID( pclinfo->siPersonID );

	if ( CharID ==  0 )
	{
		return;
	}

	if(pclCM->IsValidID(CharID)  == false)return ;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[CharID];

	// 클라이언트에게 통보한다. 
	cltSimplePerson clperson;
	clperson.Set(&pclchar->pclCI->clBI.clPerson);
	cltSimplePerson clfather;
	clfather.Set(&pclchar->pclCI->clBI.clFatherInfo.clFather);

	SI32 rank = pclchar->pclCI->clBI.siWealthRank;
	if ( pclchar->pclCI->clIP.GetLevel() < FATHER_LEVEL || rank <= 0 )
		rank = 0 ;

	SI32 out_villageunique = 0;
	SI32 out_unitslot = 0;
	SI32 out_memberindex = 0;
	SI32 in_personid = pclCM->CR[id]->pclCI->GetPersonID();
	SI32 retvalue = 0;

	cltGameMsgResponse_PersonPrivateInfo clinfo(pclchar->pclCI->clBI.szAccountID, &clperson, &clfather,
		pclchar->pclCI->clIP.GetLevel(), 
		pclchar->pclCI->clIP.siFameLevel,
		pclchar->pclCI->clBI.siCountryID,
		pclchar->pclCI->clBI.bShowCountry,
		pclchar->pclCI->clBI.clFatherInfo.siFatherChangeNumber,
		rank,
		pclchar->pclCI->clBI.clTotalWealthMoney,
		pclchar->pclCI->clBI.szGreeting,
		pclchar->pclCI->clBI.siPVPWinNumber,
		pclchar->pclCI->clBI.siPVPLoseNumber,
		pclchar->pclCI->clBI.szPVPWinHighLevelUserName,
		pclchar->pclCI->clPersonNaming.m_siSelectedLevel,
		pclchar->pclCI->clBI.clGuildRank.szGuildName,
		pclchar->pclCI->clBI.siHomeVillage	
		);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONPRIVATEINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

// 접속중인 학교 사용자 수요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SCHOOLUSERNUM(cltMsg* pclMsg, SI32 id)
{
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}

	cltGameMsgRequest_SchoolUserNum* pclinfo = (cltGameMsgRequest_SchoolUserNum*)pclMsg->cData;
	if(pclinfo->siSchoolUnique <= 0)return ;

	// 사용자를 검색하여 학교 사용자 수를 파악한다. 
	SI32 usernum = 0;
	SI32 index = 0;
	SI32 userid;
	while(userid = pclCM->GetCharOrder(index))
	{
		index++;

		if(pclCM->IsValidID(userid))
		{
			if(IsPC(userid))
			{
				if(pclCM->CR[userid]->pclCI->clBI.siSchoolUnique == pclinfo->siSchoolUnique)
				{
					usernum ++;
				}
			}
		}
	}


	// 클라이언트에게 통보한다. 
	cltGameMsgResponse_SchoolUserNum clinfo(pclinfo->siSchoolUnique, usernum);
	cltMsg clMsg(GAMEMSG_RESPONSE_SCHOOLUSERNUM, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// 스승 등록  요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETFATHER(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_SetFather* pclinfo = (cltGameMsgRequest_SetFather*)pclMsg->cData;

	// 일본이다
	if( 0 == pclinfo->uiType)
	{
		// 레벨이 적합한지 확인한다. 
		if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
			return ;

		// 스승 등록 신청자 리스트에 있는지 확인한다. 
		if(pclFatherManager->IsExist(pclinfo->siPersonID) == false)
		{
			// 클라이언트로 서버의 응답값을 보낸다. 
			SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}

		// 해당 사용자가 존재하는지 확인한다. 
		SI32 targetid = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
		if(pclCM->IsValidID(targetid))
		{
			sDBRequest_SetFather clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), (TCHAR*)pclCM->CR[targetid]->GetName(), pclCM->CR[id]->pclCI->clIP.GetLevel());
			pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
		}
	}
	else if( 1 == pclinfo->uiType )
	{
		// 제자가 스승에게 스승을 하자고 요청
		if( 0 == pclinfo->uiMode )
		{
			// 레벨이 적합한지 확인한다. 
			//KHY -0629 - 50렙이전이면 스승을 신청할 수 있다.
			if( ConstServiceArea_Japan != siServiceArea)
			{
				if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= pclClient->siMinimumTeacherLevel)
					return ;
			}
			else
				if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
					return ;

			// 스승 등록 신청자 리스트에 있는지 확인한다. 
			if(pclFatherManager->IsExist(pclinfo->siPersonID) == false)
			{
				// 클라이언트로 서버의 응답값을 보낸다. 
				SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[id]->GetCharUnique());
				return ;
			}

			// 해당 사용자가 존재하는지 확인한다. 
			SI32 targetid = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
			if(targetid)
			{
				if( false == pclCM->IsValidID(targetid) )
				{
				}
				else
				{
					cltGameMsgResponse_Request_SetFather clinfo( pclCM->CR[id]->pclCI->GetPersonID(), (TCHAR*)pclCM->CR[id]->GetName() );
					cltMsg clMsg( GAMEMSG_RESPONSE_REQUEST_SETFATHER, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[targetid]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}
		// 스승인 내가 수락해서 제자를 받아주기
		else if( 1 == pclinfo->uiMode )
		{
			// 레벨이 적합한지 확인한다. 
			//KHY -0629 - 50렙이전이면 스승을 신청할 수 있다.
			if( ConstServiceArea_Japan != siServiceArea)
			{
				if( pclClient->siMinimumTeacherLevel > pclCM->CR[id]->pclCI->clIP.GetLevel() )
					return;
			}

			SI32 pupilPersonID = pclinfo->siPersonID;
			SI32 pupilID = pclCM->GetIDFromPersonID( pupilPersonID );

			if( 0 < pupilID  )
			{
				if( false == pclCM->IsValidID( pupilID ) )
				{
				}
				else
				{
					// 레벨이 적합한지 확인한다. 
					if(pclCM->CR[pupilID]->pclCI->clIP.GetLevel() >= pclClient->siMinimumTeacherLevel)
						return ;


					// 스승 등록 신청자 리스트에 있는지 확인한다. 
					if(pclFatherManager->IsExist( pclCM->CR[id]->pclCI->GetPersonID() ) == false)
					{
						// 클라이언트로 서버의 응답값을 보낸다. 
						SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[pupilID]->GetCharUnique());
						return ;
					}

					// 해당 사용자가 존재하는지 확인한다. 
					sDBRequest_SetFather clMsg(pupilID, pupilPersonID, (TCHAR*)pclCM->CR[id]->GetName(), pclCM->CR[pupilID]->pclCI->clIP.GetLevel());
					pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
				}
			}
		}
		// 스승이 수락을 거절했다
		else if( 2 == pclinfo->uiMode )
		{
			SI32 pupilPersonID = pclinfo->siPersonID;
			SI32 pupilID = pclCM->GetIDFromPersonID( pupilPersonID );

			if( 0 < pupilID  )
			{
				if( false == pclCM->IsValidID( pupilID ) )
				{
				}
				else
				{
					SendServerResponseMsg(0, SRVAL_REJECT_SETFATHER,  0, 0, pclCM->CR[pupilID]->GetCharUnique());
				}
			}
		}	
	}
}
/*
// 학교등록  요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETSCHOOL(cltMsg* pclMsg, SI32 id)
{
cltGameMsgRequest_SetSchool* pclinfo = (cltGameMsgRequest_SetSchool*)pclMsg->cData;

if(pclinfo->siSchoolUnique < 0)return ;
if(pclinfo->siSchoolUnique >= MAX_SCHOOL_NUMBER)return ;


// 정보를 업데이트 한다. 
pclCM->CR[id]->pclCI->clBI.siSchoolUnique = pclinfo->siSchoolUnique;

// 클라이언트로 정보를 보낸다. 
cltGameMsgResponse_School clinfo(pclCM->CR[id]->GetCharUnique(), pclCM->CR[id]->pclCI->clBI.siSchoolUnique);
cltMsg clMsg(GAMEMSG_RESPONSE_SCHOOL, sizeof(clinfo), (BYTE*)&clinfo);
((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);


// DB에 저장한다. 
{
sDBRequest_SetSchool clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siSchoolUnique);
pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
}


}
*/
// 게임 플레이 시간 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_PLAYTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PlayTime* pclinfo = (cltGameMsgRequest_PlayTime*)pclMsg->cData;

	if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)return ;

	cltGameMsgResponse_PlayTime clinfo(pclCM->CR[id]->pclCI->clBI.siPlaySecond, 
		pclCM->CR[id]->pclCI->clBI.siPlayEventSecond );

	cltMsg clMsg(GAMEMSG_RESPONSE_PLAYTIME, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// 말 풀어주기. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEFREE(cltMsg* pclMsg, SI32 id)
{

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if(personid <= 0)return ;

	// 말을 보유 하고 있어야 한다. 
	cltHorse* pclhorse  = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if( pclhorse == NULL || pclhorse->siHorseUnique <= 0 )	return; 

	// 그 말을 타고 있는 상태가 아니어야 한다. 
	if(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		return ;
	}

	//---------------------------------------------
	// 예약 되어 있는 아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// 예약 되어 있는 탄환아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// 말 인벤에 물품이 있으면 풀어줄 수 없다. 
	if(pclchar->pclCI->clCharItem.IsHorseHaveItem() )return ;

	// DB에 저장한다. 
	pclchar->UpdateHorseToDB(this, pclchar->pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_FREE);

	// 말을 지운다. 
	pclchar->pclCI->clHorseInfo.Init(pclchar->pclCI->clHorseInfo.siCurrentShowHorse);

	pclStatisticsManager->clDailyStatistics.siReleaseHorse++;

	
	pclchar->SetUpdateSwitch(UPDATE_HORSE, true, 0);

	// 이웃들에게 알린다. 
	cltGameMsgResponse_HorseFree clinfo(pclCM->CR[id]->GetCharUnique());
	cltMsg clMsg(GAMEMSG_RESPONSE_HORSEFREE, sizeof(clinfo), (BYTE*)&clinfo);
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
}

// 말 
void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGEHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ChangeHorse *pclinfo = ( cltGameMsgRequest_ChangeHorse * )pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// 말을 보유 하고 있어야 한다. 
	cltHorse* pclhorse  = pclCM->CR[id]->pclCI->clHorseInfo.GetHorse(pclinfo->siChangeHorseIndex);

	if(pclhorse == NULL || pclhorse->siHorseUnique <= 0)
	{
		((cltCharServer*)pclCM->CR[id])->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE = false;
		//return;	
	}

	cltTimeMeterRate* pclTimeMeterRate = pclchar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(TIMEMETERRATE_MOTORCYCLE);
	if ( NULL == pclTimeMeterRate )
	{
		pclchar->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE = false;
	}
	
	pclchar->pclCI->clHorseInfo.SetCurrentShowHorseIndex(pclinfo->siChangeHorseIndex);
	
	// PCK : 말을 바꾸면 ParametaBoxAction을 수행한다.  
	pclCM->CR[id]->SetParametaBoxAction(true);

	// DB에 저장한다. 
	pclchar->UpdateHorseToDB(this, pclchar->pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

	//pclchar->SetUpdateSwitch(UPDATE_HORSE, true, 0);

	// 주인과 이웃에게 말 정보를 보낸다. 
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyHorseStatus(pclchar->pclCI->clHorseInfo.siCurrentShowHorse);

	if(((cltCharServer*)pclCM->CR[id])->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		//---------------------------------------
		// 이웃들에게 말을 탔음을 알린다. 
		//---------------------------------------
		// 오토바이는 사용이 가능해야 한다(휘발유가 남아있어야 한다)
		if ( HORSEUNIQUE_MOTORCYCLE == pclhorse->siHorseUnique )
		{
			// 기존에 그냥 오토바이를 사용중이었다면 바로 모션을 변경하고
			if ( pclTimeMeterRate->IsUse() )
			{
				((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
			}
			// 지금 처음 타는 것이라면 휘발류 종량제가 시작되어야 모션을 변경하고
			else if ( pclchar->pclCI->clBI.clTimeMeterRateInfo.UseStart(TIMEMETERRATE_MOTORCYCLE) )
			{
				((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
			}
			// 아니면 다시 말에서 내리도록 한다
			else
			{
				SI16 showHorseIndex = pclchar->pclCI->clHorseInfo.GetCurrentShowHorseIndex();

				pclchar->UnrideHorse();

				// 휘발유가 없기 때문에 내리도록 한다
				sDBRequest_SetRideHorse cldbmsg(id, pclchar->pclCI->GetPersonID(), showHorseIndex , false);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);
			}
		}
		else
		{
			// 기존에 오토바이여서 휘발유를 사용중이었다면 사용을 중지 시킨다
			if( pclTimeMeterRate->IsUse() )
			{
				// DB에 사용시간 차감을 보냄
				sDBRequest_TimeMeterRate_UseTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_MOTORCYCLE, pclTimeMeterRate->siUseTimeSec, true );
				SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

				// 사용 종료
				pclchar->pclCI->clBI.clTimeMeterRateInfo.UseEnd( TIMEMETERRATE_MOTORCYCLE );
			}

			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
		}
	}

	// 이웃들에게 알린다. 
	cltGameMsgResponse_ChangeHorse clinfo(pclinfo->siChangeHorseIndex , pclhorse,pclCM->CR[id]->GetCharUnique());
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEHORSE, sizeof(clinfo), (BYTE*)&clinfo);
	//((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, TRUE);
	((cltCharServer*)pclCM->CR[id])->SendNetMsg((sPacketHeader*)&clMsg);
}


// 유저 아이디 요청( 미니 홈페이지 띄우려고... )
void cltServer::DoMsg_GAMEMSG_REQUEST_USERID(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Userid *pclinfo = ( cltGameMsgRequest_Userid * )pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	if(personid <= 0) return;

	SI32 toid = 0;
	SI32 ToPersonID = 0;


	if( pclinfo->siToPersonCharUnique ) {

		toid = pclCM->GetIDFromCharUnique( pclinfo->siToPersonCharUnique );
		if(pclCM->IsValidID(toid) == false) return ;

		ToPersonID = pclCM->CR[toid]->pclCI->GetPersonID();
		if(ToPersonID <= 0) return ;

		sDBRequest_Userid clMsg( pclCM->CR[id]->GetCharUnique(), personid, ToPersonID );
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

	} else {

		sDBRequest_Userid clMsg( pclCM->CR[id]->GetCharUnique(), personid, pclinfo->szToPersonName );
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
	}




	return;
}

// 스킬 점수 복구.
void cltServer::DoMsg_GAMEMSG_REQUEST_DECREASESKILLBONUS(cltMsg* pclMsg, SI32 id)
{
	SI32 i;

	cltGameMsgRequest_DecreaseSkillBonus* pclinfo = (cltGameMsgRequest_DecreaseSkillBonus*)pclMsg->cData;
	if ( NULL == pclinfo )		return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 )		return;

	//----------------------------------
	// 스킬의 종류를 확인한다.
	//----------------------------------
	SI32 skillunique = pclinfo->siSkillUnique;
	if ( (skillunique <= 0) || (MAX_SKILL_NUMBER <= skillunique) )	return;

	//---------------------------------
	// 스킬 점수가 있어야 뺄 수 있다. 
	//---------------------------------
	SI32 skilllevel = pclCM->CR[id]->pclCI->clCharSkill.GetSkillLevel(skillunique);
	if(skilllevel <= 0)			return;

	//---------------------------------
	// 전투 향상술은 스킬포인트가 1이 아닐 수 있다
	//---------------------------------
	bool			bSkillTypeFight	= false;
	cltSkillInfo*	pclGetSkill		= pclSkillManager->pclSkillInfo[skillunique];
	if ( NULL == pclGetSkill )	return;

	SI32 siDecreaseSkillPoint = 0;
	// 기술 전체 초기화 이용권 - 2009.11.24 손성웅
	if ( pclinfo->siInitMode ==INIT_SKILLMODE_TICKET_ALL ) 
	{
		siDecreaseSkillPoint = skilllevel;	// 전체 초기화면 해당 스킬레벨만큼 뺀다 
	}
	else
	{
		siDecreaseSkillPoint = 1;
	}
	
	if ( SKILLTYPE_FIGHT == pclGetSkill->siSkillType )
	{
		if ( (SKILLATB_HIDDENGRADE1 & pclGetSkill->siSkillAtb) || (SKILLATB_HIDDENGRADE2 & pclGetSkill->siSkillAtb) )
		{
			SI32 siParentSkill = pclGetSkill->siParentRef;
			if ( (0 >= siParentSkill) || (MAX_SKILL_NUMBER <= siParentSkill) )
			{
				return;
			}
			pclGetSkill = pclSkillManager->pclSkillInfo[siParentSkill];
			if ( NULL == pclGetSkill )
			{
				return;
			}
		}

		if ( (0 >= skilllevel) || (MAX_WEAPONSKILL_LEVEL < skilllevel) )
		{
			return;
		}
		SI32 siRealIndex = skilllevel - 1;

		if ( NULL == pclGetSkill->pclWeaponSkillInfo[siRealIndex] )
		{
			return;
		}

		bSkillTypeFight			= true;
		if ( pclinfo->siInitMode ==INIT_SKILLMODE_TICKET_ALL ) 
		{
			siDecreaseSkillPoint	= pclGetSkill->pclWeaponSkillInfo[siRealIndex]->siNeedSkillPoint * skilllevel ;
		}
		else
		{
			siDecreaseSkillPoint	= pclGetSkill->pclWeaponSkillInfo[siRealIndex]->siNeedSkillPoint;
		}

	}

	SI32 index = skillunique;

	//---------------------------------
	// 자식 스킬이 있으면 0으로 만들지는 않는다.
	//---------------------------------
	// skillunique를 부모로 둔 기술의 점수가 0이 아니면 실패. 
	UI08 childskilllist[MAX_CHILD_SKILL_NUM];
	SI32 childskillnum = 0;
	for(i = 0;i < MAX_CHILD_SKILL_NUM;i++)
	{
		childskilllist[i] = 0;
	}

	bool bfailswitch = false;
	SI32 childskillunique = 0;
	// 전투 향상술은 선행조건을 검사하지 않는다
	if ( (false == bSkillTypeFight) && (skilllevel == 1) )
	{
		for(i = 0;i < MAX_SKILL_NUMBER;i++)
		{
			if(pclSkillManager->pclSkillInfo[i] == NULL)continue;

			if(pclSkillManager->pclSkillInfo[i]->siParentRef == skillunique)
			{
				if(childskillnum < MAX_CHILD_SKILL_NUM)
				{
					childskilllist[ childskillnum ] = pclSkillManager->pclSkillInfo[i]->siUnique;
					childskillnum++;
				}


				childskillunique = pclSkillManager->pclSkillInfo[i]->siUnique;
				SI32 childskilllevel = pclCM->CR[id]->pclCI->clCharSkill.GetSkillLevel(pclSkillManager->pclSkillInfo[i]->siUnique);
				if(childskilllevel > 0)
				{
					bfailswitch = true;
					continue;
				}
			}
		}
	}

	if ( bfailswitch == true )
	{
		// 클라이언트로 서버의 응답값을 보낸다. 
		SendServerResponseMsg(0, SRVAL_DECSKILL_FAIL_HAVECHILD,  childskillunique, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	if(index < 0 ) return ;

	switch(pclinfo->siInitMode)
	{
	case INIT_SKILLMODE_LEVEL:
		{
			//----------------------------------
			// 레벨이 맞지 않으면 실패. 
			//----------------------------------
			
			if( pclCM->CR[id]->pclCI->clIP.GetLevel() != INIT_LEVEL && pclCM->CR[id]->pclCI->clIP.GetLevel() != INIT_LEVEL_SECOND )
				break;

			// 제조활성화 : 제조 스킬로 올린 스킬보너스 포인트는 다시 복구 되지 않는다. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, 1, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_LEVEL, 0, NULL);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 10. 11] // 캐릭터의 스킬 감소.(확인필요한가)
			//	// param1 == 설정할 스킬 유니크, 
			//	// param2 == 감소시켜야 할 스킬 레벨, 
			//	// param3 == 다시 돌려줘야할 스킬보너스 포인트.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, 1, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
	case INIT_SKILLMODE_TICKET:
		{
			//------------------------------------
			// 아이템이 없으면 실패.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24040) ; // 기술부분초기화이용권
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(1);

			// 통계를 낸다. 
			pclItemManager->AddUseNum(itemunique, 1);

			// 새로운 통계 - 아이템 사용
			//NStatistics_Add("Item", itemunique, "UseNum", 1);

			// 제조활성화 : 제조 스킬로 올린 스킬보너스 포인트는 다시 복구 되지 않는다. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, 1, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_TICKET, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 10. 11] // 캐릭터의 스킬 감소.(확인필요한가)
			//	// param1 == 설정할 스킬 유니크, param2 == 감소시켜야 할 스킬 레벨, param3 == 다시 돌려줘야할 스킬보너스 포인트.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, 1, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
	case INIT_SKILLMODE_WEAPONSKILL:
		{
			//------------------------------------
			// 아이템이 기술레벨만큼 없으면 실패.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24040) ; // 기술부분초기화이용권
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) < skilllevel )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(skilllevel);

			// 통계를 낸다. 
			pclItemManager->AddUseNum(itemunique, skilllevel);

			// 새로운 통계 - 아이템 사용
			//NStatistics_Add("Item", itemunique, "UseNum", skilllevel);
	
			// 제조활성화 : 제조 스킬로 올린 스킬보너스 포인트는 다시 복구 되지 않는다. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, skilllevel, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_WEAPONSKILL, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 10. 11] // 캐릭터의 스킬 감소.(확인필요한가)
			//	// param1 == 설정할 스킬 유니크, param2 == 감소시켜야 할 스킬 레벨, param3 == 다시 돌려줘야할 스킬보너스 포인트.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, skilllevel, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
		// 기술 전체 초기화 이용권 - 2009.11.24 손성웅
	case INIT_SKILLMODE_TICKET_ALL:
		{
			//------------------------------------
			// 아이템이 기술레벨만큼 없으면 실패.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24041) ; // 기술부분초기화이용권
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(1);

			// 통계를 낸다. 
			pclItemManager->AddUseNum(itemunique, 1);

			// 제조활성화 : 제조 스킬로 올린 스킬보너스 포인트는 다시 복구 되지 않는다. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, skilllevel, siDecreaseSkillPoint, childskilllist, INIT_SKILLMODE_TICKET_ALL, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [로그추가 : 황진성 2007. 10. 11] // 캐릭터의 스킬 감소.(확인필요한가)
			//	// param1 == 설정할 스킬 유니크, param2 == 감소시켜야 할 스킬 레벨, param3 == 다시 돌려줘야할 스킬보너스 포인트.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, skilllevel, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
	}
}

// 퀘스트 취소 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELQUEST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_CancelQuest* pclInfo = (cltGameMsgRequest_CancelQuest*)pclMsg->cData;

	//--------------------------------
	// 퀘스트타입을 확인한다. 
	//--------------------------------
	SI32 questtype		= pclInfo->siQuestType;
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(personid <= 0)return ;

	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)return ;

	// 해당 퀘스트 타입에 진행중인 퀘스트가 있는가 ?
	cltPersonQuestUnitInfo* pclquestinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype];

	// 진행중인 퀘스트가 있다면 퀘스트 스텝을 보고 조치한다. 
	if(pclquestinfo->siCurQuestUnique)
	{
		// 완료단계의 퀘스트가 아니라면 취소한다. 
		if(pclquestinfo->siCurQuestStep != QUEST_STEP_CLEAR && pclquestinfo->siCurQuestStep != QUEST_STEP_NEXTQUEST)
		{

			pclquestinfo->siCurQuestUnique	= 0;
			pclquestinfo->siCurQuestStep	= 0;
			pclquestinfo->siQuestCmd		= 0;
			pclquestinfo->siQuestPara1		= 0;
			pclquestinfo->siQuestPara2		= 0;

			if(questtype == QUEST_TYPE_SPECIAL)
			{
				pclchar->pclCI->clQuestInfo.clSpecialQuestInfo.Init();

				// 특수 퀘스트 정보를 저장한다. 
				// DB에 퀘스트이 상태를 저장한다. 
#ifdef _SAFE_MEMORY
				sDBRequest_SetSpecialQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clSpecialQuestInfo, &pclchar->pclCI->clQuestInfo.bWordAssemblySwitch[0]);
#else
				sDBRequest_SetSpecialQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clSpecialQuestInfo, pclchar->pclCI->clQuestInfo.bWordAssemblySwitch);
#endif
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);
			}
			else if(questtype == QUEST_TYPE_NAMING )
			{
				pclchar->pclCI->clQuestInfo.clNamingQuestInfo.Init(); //KHY - 네이밍 퀘스트가 삭제되어야 한다.

				// naming - 네이밍 퀘스트 정보 저장
				sDBRequest_SetNamingQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clNamingQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);

			}
			//KHY - 0822 - 해피빈 퀘스트 추가.
			else if(questtype == QUEST_TYPE_HAPPYBEAN )
			{
				//해피빈 스타트 카운터를 내린다.
				SendLog_SetHappyBeanClearInfo(pclchar, questtype, QUEST_HAPPYBEAN_STEP_NON);

				pclchar->pclCI->clQuestInfo.clHappyBeanQuestInfo.Init();
				// 초기화된 해피빈 정보를 보낸다.
				sDBRequest_SetHappyBeanQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clHappyBeanQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);
			}
			// 미션 삭제 : 취소에 의한 삭제 - by LEEKH 2008-09-17
			else if( questtype == QUEST_TYPE_MISSION1 )
			{
				pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
				sDBRequest_SetMissionQuestInfo	clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);
			}

			// DB에 퀘스트의 상태를 저장한다. 
			sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			// 클라이언트에 퀘스트의 상태를 통보한다. 
			pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
		}
	}
}


// 퀘스트 수행에 대한 요청. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETQUESTGOING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_QuestGoing* pclInfo = (cltGameMsgRequest_QuestGoing*)pclMsg->cData;

	//--------------------------------
	// 퀘스트타입을 확인한다. 
	//--------------------------------
	SI32 questtype		= pclInfo->siQuestType;
	SI32 questunique	= pclInfo->siQuestUnique;
	SI32 queststep		= pclInfo->siQuestStep;
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar == NULL)	return ;
	if(personid <= 0)	return ;

	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)return ;

	// 피로도 시스템이 설정되어 있고,  TIRED_STATUS_MUCH_TIRED 상태라면, 무조건 퀘스트 진행이 안된다. 
	if(pclchar->bTiredSystem) //피로도 시스템이 설정되어 있는 경우만
	{
		if (	pclchar->uiTiredState == cltCharCommon::TIRED_STATUS_MUCH_TIRED 
			||	pclchar->uiTiredState == cltCharCommon::TIRED_STATUS_LITTLE_TIRED	)
			return;		
	}

	// 해당 퀘스트 타입에 진행중인 퀘스트가 있는가 ?
	cltPersonQuestUnitInfo* pclquestinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype];

	// 진행중인 퀘스트가 있다면 퀘스트 스텝을 보고 조치한다. 
	if(pclquestinfo->siCurQuestUnique)
	{
		if(pclquestinfo->siCurQuestStep == QUEST_STEP_MIDDLE)
		{
			// 완료 상태인지 여부를 묻는다. 
			if(queststep == QUEST_STEP_CLEAR)
			{
				cltQuestInfoCommon* pclinfo = NULL;

				// 특수한 퀘스트 처리를 위한 퀘스트 정보 설정
				switch(questtype)
				{
				case QUEST_TYPE_SPECIAL:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo;			break;
				case QUEST_TYPE_NAMING:			pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo;				break;
				case QUEST_TYPE_HAPPYBEAN:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo;			break;
				case QUEST_TYPE_MISSION1:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo;			break;
				default:						pclinfo = pclQuestManager->GetQuestInfo(pclquestinfo->siCurQuestUnique);										break;
				}

				if(pclinfo == NULL)return;

				// 완료 조건을 충족시킨다. 
				if(pclCM->CR[id]->IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
				{
					//-----------------------------------------------------------------------
					// 완료 조건에서 캐릭터의 인벤에서 제거해야 할 아이템 있는 경우 제거한다.
					//-----------------------------------------------------------------------

					// 보상으로 아이템을 주는 경우에는 아이템을 줄 수 있는 상황인지 확인해야 한다. 
					cltQuestRewardInfo* pclreward = &pclinfo->clQuestRewardInfo;
					bool bIsHaveItemReward = false;

					// 보상을 선택해야 하는경우..
					// 선택한 아이템 외에는 보상 데이터 없애준다...;
					//SI32 rewardItemUnique[MAX_QUEST_REWARD_NUMBER] = {0,};

					SI32	siRewardItemUnique[MAX_MATERIAL_NUMBER]	= {0, };
					SI32	siRewardItemNumber[MAX_MATERIAL_NUMBER]	= {0, };
					SI32	siRewardItemUseDate	= 0;
					SI32	siRepeatCounter		= 0;


					ZeroMemory( siRewardItemUnique, (sizeof(SI32) * MAX_MATERIAL_NUMBER) );
					ZeroMemory( siRewardItemNumber, (sizeof(SI32) * MAX_MATERIAL_NUMBER) );
					
					// 아이템의 재료를 주는 스위치가 켜져있다면 재료를 준다
					if ( pclreward->bIsGetMaterial == true )
					{
						siRepeatCounter = MAX_MATERIAL_NUMBER;

						SI32 siRewardItem	= pclreward->siItemUnique[0];
						SI32 siMulNumber	= pclreward->siItemNum[0];
						SI32 siReference	= pclClient->pclItemManager->FindItemRefFromUnique( siRewardItem );
						

						if ( ( siRewardItem > 0 ) && ( siReference > 0 ) )
						{

							cltItemInfo* pclMaterialInfo = (cltItemInfo*)pclClient->pclItemManager->pclItemInfo[ siReference ];
							if ( pclMaterialInfo == NULL )
							{
								return;
							}

							siRewardItemUseDate =  (SI32)pclMaterialInfo->clItem.uiDateUseDay;

							// 해당아이템의 필요한 재료아이템을 구해온다
							for ( SI32 siIndex=0; siIndex<MAX_MATERIAL_NUMBER; siIndex++ )
							{
								SI32 siMaterialUnique	= pclMaterialInfo->clProductionInfo.clMaterial[ siIndex ].siUnique;
								SI32 siMaterialNumber	= pclMaterialInfo->clProductionInfo.clMaterial[ siIndex ].siNeedNum;
				

								if ( (siMaterialUnique <= 0) || (siMaterialNumber <= 0) )
								{
									continue;
								}

								if ( siMulNumber > 0 )
								{
									siMaterialNumber = siMaterialNumber * siMulNumber;
								}

								siRewardItemUnique[ siIndex ] = siMaterialUnique;
								siRewardItemNumber[ siIndex ] = siMaterialNumber;

								if ( siRewardItemUnique[ siIndex ] > 0 )
								{
									bIsHaveItemReward = true;
								}
							}
						} // if ( ( siRewardItem > 0 ) && ( siReference > 0 ) ) 종료
						else
						{
							bIsHaveItemReward = false;
						}
					}
					// 일반적인 아이템 보상 퀘스트
					else
					{
						siRepeatCounter		= MAX_QUEST_REWARD_NUMBER;

						for ( SI32 i = 0 ; i < siRepeatCounter ; i++ )
						{
							if ( pclreward->bSelectItem && pclInfo->siSelectItemIndex != i )
							{
								siRewardItemUnique[i] = 0;							
							}
							else
							{
								siRewardItemUnique[i] = pclreward->siItemUnique[i];
							}
						}

						for( SI32 j = 0 ; j < siRepeatCounter; j++ )
						{
							if( siRewardItemUnique[j] > 0 )
							{
								bIsHaveItemReward = true;
								break;
							}
						}
					}
					
					if( bIsHaveItemReward )
					{
						// 해당 아이템을 랜덤하게 만든다. 
						cltItem	clManyRewardItem[MAX_MATERIAL_NUMBER];
						SI16	brareswitch = 0;

						for ( SI32 siInitCount=0; siInitCount<MAX_MATERIAL_NUMBER; siInitCount++ )
						{
							clManyRewardItem[siInitCount].Init();
						}


						for( SI32 i = 0; i < siRepeatCounter; i++ )
						{
							SI32 siItemUseDate	= 0;
							bool bMakeResult	= false;


							if ( pclreward->bIsGetMaterial == true )
							{
								siItemUseDate = siRewardItemUseDate;
							}
							else
							{	siItemUseDate = pclreward->siItemUseDate[i];
							}

							if(siRewardItemUnique[i] <= 0 ) continue;

							bMakeResult = pclItemManager->MakeRandItemUnique( siRewardItemUnique[i], &clManyRewardItem[i], 0, 0, &brareswitch,
								0,0,0,0,0,siItemUseDate);

							if( bMakeResult == false)
							{
								return ;
							}
						}

						// 해당아이템을 인벤에 넣을 수 있는지 확인한다. 

						SI32 rtnvalue;
						if(pclchar->CanAddInvManyItems(INVMODE_ALL, clManyRewardItem, &rtnvalue) == false)
						{
							// 클라이언트로 서버의 응답값을 보낸다. 
							SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, pclCM->CR[id]->GetCharUnique());

							// db에도 기록해준다
							SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,siRewardItemUnique[0],
								pclreward->siItemNum[0],pclreward->siNCoin,pclreward->siItemUseDate[0],false);
							
							return ;
						}
					}
					if(pclCM->CR[id]->DoClearCondition(&pclinfo->clQuestClearConditionInfo) == false)
					{
						return ;
					}

					//-----------------------------------------------------------------------
					// 보상을 집행한다. 
					//-----------------------------------------------------------------------
					bool rewardswitch = false;

					// 아이템을 준다. 
					for( SI32 i = 0; i < siRepeatCounter; i ++ )
					{
						if(siRewardItemUnique[i])
						{
							SI32 rewardItemNum			= 0;
							SI32 siQuestItemUnique		= 0;
							SI32 siUseDateForLog		= 0;
							
							if ( pclreward->bIsGetMaterial == true )
							{
								siQuestItemUnique	= siRewardItemUnique[ i ];
								rewardItemNum		= siRewardItemNumber[ i ];
								siUseDateForLog		= siRewardItemUseDate;
							}
							else
							{
								siQuestItemUnique	= pclreward->siItemUnique[ i ];
								rewardItemNum		= pclreward->siItemNum[ i ];
								siUseDateForLog		= pclreward->siItemUseDate[ i ];
							}

							// 피로방지 시스템 적용 ( 퀘스트 아이템일 경우 모두 준다.)
							if ( pclItemManager->GetItemType( siQuestItemUnique ) != ITEMTYPE_QUEST )
							{
								rewardItemNum = pclchar->CalcTiredPoint( rewardItemNum );
							}

							// 캐릭터에게 아이템을 주고 필요한 조치를 취한다. 
							if( rewardItemNum > 0 )
							{
								if(  pclchar->GiveItem(siQuestItemUnique, rewardItemNum, INPUTITEMPERSON_OPTION_QUEST, siUseDateForLog) == false )
								{
									// 클라이언트로 서버의 응답값을 보낸다. 
									SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, pclCM->CR[id]->GetCharUnique());

									// db에도 기록해준다
									SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,siQuestItemUnique,
										rewardItemNum,pclreward->siNCoin,siUseDateForLog,false);

									return ;
								}
								else
								{
									rewardswitch = true;

									// 통계를 낸다. 
									pclItemManager->AddQuestItemNum(siQuestItemUnique, rewardItemNum);

									// 새로운 통계 - 퀘스트 공급 물품의 통계를 낸다.
									NStatistics_Add("Item", siQuestItemUnique, "Quest", rewardItemNum);

									// db에도 기록해준다
									SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,siQuestItemUnique,
										rewardItemNum,pclreward->siNCoin,siUseDateForLog,true);
								}
							}
							else
							{
								rewardswitch = true;
							}
						}
					}

					//-----------------------------------------------------------------------
					// 군주 스페셜 이벤트 : 겨울맞이! 군주S의 훈훈한 릴레이 이벤트
					// - by LEEKH 2007.12.21
					//-----------------------------------------------------------------------
/*					if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
					{
						switch(questtype)
						{
						case QUEST_TYPE_BATTLE1:			// 지그프리드
						case QUEST_TYPE_BASIC1:				// 지젤
						case QUEST_TYPE_HUNTINGGROUND01:	// 소피아
						case QUEST_TYPE_HUNTINGGROUND02:	// 스파키
						case QUEST_TYPE_BATTLE2:			// 진
							{
								SI32	maxunique = 0;
								for(int i=0; i<MAX_QUEST_PER_TYPE_NUMBER; i++)
								{
									SI32 tmpunique = pclClient->pclQuestManager->GetUniqueFromBit(questtype, i);
									if (tmpunique > maxunique)
									{
										maxunique = tmpunique;
									}
								}

								// 마지막 퀘스트 라면...
								if( maxunique == questunique)
								{
									SYSTEMTIME	SEvent, EEvent;
									ZeroMemory(&SEvent, sizeof(SEvent));
									ZeroMemory(&EEvent, sizeof(EEvent));

									SEvent.wYear = 2007;	SEvent.wMonth = 12;		SEvent.wDay = 27;
									EEvent.wYear = 2008;	EEvent.wMonth = 1;		EEvent.wDay = 23;	EEvent.wHour = 23;	EEvent.wMinute = 59;	EEvent.wSecond = 59;

									_SYSTEMTIME stCreateTime = pclchar->pclCI->clBI.GetFirstCreatTime(); //최초 계정 생성 시간.

									// 이벤트 기간과 계정생성 시간을 체크 한다.
									if( TimeInBounds(&sTime, &SEvent, &EEvent) &&
										TimeInBounds(&stCreateTime, &SEvent, &EEvent) )
									{
											SendLog_SetEventCouponInfo(pclchar, SUPER_ROOKIE_LEVELUP_EVENT, questtype);
									}
								}								
							}
							break;
						}
					}*/
					//-----------------------------------------------------------------------

					// 돈을 준다. 
					if(pclreward->siMoney)
					{
						// 아이템 보상금액에 NPC Rate가 적용되는 것이라면
						GMONEY rewardMoney = pclreward->siMoney;
						if ( true == pclreward->bApplyNpcRate )
						{
							SI64 siNPCPriceRate = pclItemManager->clItemStatistic.siNPCPriceRate;
							rewardMoney = rewardMoney * siNPCPriceRate / 100;
						}

						// 피로방지 시스템 적용
						rewardMoney = pclchar->CalcTiredPoint( rewardMoney );

						sDBRequest_ChangeMoney clMsg(id, personid, CHANGE_MONEY_REASON_QUESTREWARD, rewardMoney);
						pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

						pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_QUEST, rewardMoney);

						// 통화량을  집계한다. 
						cltMoney clmoney;


						clmoney.Set(rewardMoney);
						clCurrencyInfo.clInputMoney_Quest.Increase(&clmoney);

						rewardswitch = true;
					}

					// 경험치를 준다.
					if(pclreward->siExp)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

						// 피로방지 시스템 적용
						SI32 rewardExp = pclchar->CalcTiredPoint( pclreward->siExp );
						pclchar->IncreaseExp(rewardExp);

						rewardswitch = true;
					}
					//기술 경험치를 준다.		//KHY  - 0219 - 기술경험치를 보상추가한다.
					if(pclreward->siSkillType)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

						// 피로방지 시스템 적용
						SI32 rewardExp = pclchar->CalcTiredPoint( pclreward->siExp );
						pclchar->SetSkillUpdate(pclreward->siSkillType,pclreward->siSkillExp);

						//pclchar->IncreaseExp(rewardExp);

						rewardswitch = true;
					}
					
					// 명성 경험치를 준다. 
					if(pclreward->siFameExp)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
						// 피로방지 시스템 적용
						SI32 rewardFameExp = pclchar->CalcTiredPoint( pclreward->siFameExp );

						pclchar->IncreaseFameExp(rewardFameExp);

						rewardswitch = true;
					}

					// 물품 구매 퀘스트이면, 수락시 돈을 지급한다. 
					if(pclreward->siNCoin)
					{
						if ( PushCash(pclCM->CR[id]->GetCharUnique(), pclCM->CR[id]->pclCI->GetPersonID(), 
							pclCM->CR[id]->pclCI->clBI.szAccountID, pclreward->siNCoin, PUSHCASH_REASON_QUESTEVENT) )
						{
							// db에도 기록해준다
							SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,pclreward->siItemUnique[0],
								pclreward->siItemNum[0],pclreward->siNCoin,pclreward->siItemUseDate[0],true);
						}
					}
					
					if(pclreward->bMoveBuf)
					{
						pclchar->dwIncreaseMovespeedLastClock	= INCREASEMOVESPEED_DELAY;	// 이동속도 증가버프 지연시간. 
						pclchar->dwIncreaseMovespeedStartClock = pclClient->CurrentClock;		// 이동속도 증가버프   시작시간. 

						// 버프 적용되어있지 않을때 스피드 올려줌
						if (pclchar->clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED) == false)
						{
							pclchar->clInnerStatus.SetStatus(INNERSTATUS_INCREASEMOVESPEED);
							pclchar->siIncreaseMovespeedPower		= INCREASEMOVESPEED_POWER;				// 이동속도 증가버프의 강도. 
							SI32 siCurrentSpeed = pclchar->clPB.TotalMoveSpeed;
							if (siCurrentSpeed + pclchar->siIncreaseMovespeedPower > 20)
								pclchar->clPB.GivenMoveSpeed = 20;
							else
								pclchar->clPB.GivenMoveSpeed = max(0, siCurrentSpeed + pclchar->siIncreaseMovespeedPower);


							pclchar->clPB.TotalMoveSpeed = pclchar->clPB.GivenMoveSpeed;
						}

						// 이웃에게 통보 
						cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_INCREASEMOVESPEED, true, pclchar->clPB.GivenMoveSpeed);
						cltGameMsgResponse_StatusInfo clChangeInfo(pclchar->GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						pclchar->SendNeighbourMsg(&clMsg, true);

						// 이동속도 증가 메세지 뿌려줌
						TCHAR* pTitle = GetTxtFromMgr(5614);
						TCHAR *pText = GetTxtFromMgr(6412);
						cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
						cltMsg clMsg2(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
						pclchar->SendNetMsg((sPacketHeader*)&clMsg2);

						// [수정 : 황진성 2007. 10. 11 => 이동속도버프를 주는데 적용이 안됨.] // 보상이 이루어졌다고 표시.
						rewardswitch = true;
					}
					// [지연] : 2010신년이벤트 - 디버프 보상
					if ( true == pclreward->bDeBuff )
					{
						SI16 index0 = -1;
						bool bDeBuff;

						index0 = pclchar->pclCI->clBI.clBufInfo.FindBufSlot( BUF_EVENT_FORTUNE_BAD ); // 보상 내역에 버프id를 포함하면 여기다 하드코딩 안해도 됨. 
						//일단은 디버프 보상을 또 쓸지 안쓸지도 모르니 흉버프만 지우는거로..
						if ( -1 < index0 )
						{
							// 디버프 할 버프가 (현재는 무조건 배드 버프) 있다면 디비에 디버프 메세지 보냄.
							stBuf DelBuf( BUF_EVENT_FORTUNE_BAD, 0, 0);
							sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index0, &DelBuf );
							((cltServer*)pclClient)->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );

							// 클라에 디버프 했다고 신호 보냄 메세지는 따로 만들지 않고 2010신년이벤트용 패킷을 이용 후에 디버프가 보편적인 기능으로 구현되야 한다면 패킷 따로 작성
							// fortunequality가 200이면 디버프 메세지로 약속
							cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclchar->pclCI->GetPersonID(), 200, 0, 0, 0, 0, 0 );
							cltMsg clMsg2( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
							pclchar->SendNetMsg( (sPacketHeader*)&clMsg2 );
						}

						rewardswitch = true;
						bDeBuff = true;
					}

					// 보물찾기 이벤트 마지막일떄 버프 줘야지
					if ( questtype == QUEST_TYPE_FINDTREASURE ) 
					{
						if ( questunique == 31515 ) // 보물찾기 마지막 이벤트 클리어 일떄 보상 준다.
						{
							SI32 siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // 현실시간 48분간.
							SI16 siEmptySlot = pclchar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_FINDTREASURE, false );
							if ( -1 < siEmptySlot )
							{
								stBuf addBuf(BUF_EVENT_FINDTREASURE, 0, siUseItem);
								pclchar->AddBufThroughDB( siEmptySlot, &addBuf , false , 0 ,NULL,0  );
								rewardswitch = true;
							}
						}
					}
					if ( questtype == QUEST_TYPE_NAMING )
					{
						// naming - 유저 네이밍 퀘스트 완료 정보 저장. DB저장으로 바꾸자. 일단 테스트
						sDBRequest_SetPersonNamingInfo clMsg(pclCM->CR[id]->pclCI->GetPersonID(),
							pclreward->siNamingIndex, pclreward->siNamingLevel );
						SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg );

						// 완료 알림
						rewardswitch = true;
					}

					// 보상이 이루어졌다면, 
					if(rewardswitch == true)
					{
						if(questtype == QUEST_TYPE_SPECIAL)		// 특수임무인 경우 초기화한다. 
						{
							bool bClearSpecialWordQuest = false ;
							// 글자 맞추기 단어를 랜덤하게 선택한다. 
							SI32 wordindex = pclQuestManager->GetRandWordAssembly();
							if(wordindex >= 0)
							{

								// 이미 글자 조합이 완성되어 있다면, 
								if(pclCM->CR[id]->pclCI->clQuestInfo.IsWordAssembleCompleted(pclQuestManager) == true)
								{
									pclCM->CR[id]->pclCI->clQuestInfo.InitWordAssemble();

								}

								pclCM->CR[id]->pclCI->clQuestInfo.bWordAssemblySwitch[wordindex] = true;

								// 단어 조합에 성공했음을 조사한다.

								bClearSpecialWordQuest = pclCM->CR[id]->pclCI->clQuestInfo.IsWordAssembleCompleted( pclQuestManager) ;
							}

							// 클라이언트에 보상 내역을 통보한다. 
							cltGameMsgResponse_SpeicalQuestReward clinfo(pclreward, wordindex, ((cltCharServer*)pclCM->CR[id])->uiTiredState );
							cltMsg clMsg1(GAMEMSG_RESPONSE_SPECIALQUESTREWARD, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);


							pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo.Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();

							// 흥부박 퀘스트 깨기 퀘스트 중이면, 
							pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SPECIALQUEST);

							// 요술램프 이벤트 기간에만 이벤트 조합 횟 수 증가.
							bool bLampEventPeriod = false;
							bLampEventPeriod = pclEventTimeManager->InEventTime("MagicLamp_event", &sTime);
							bLampEventPeriod = (bLampEventPeriod && bClearSpecialWordQuest);

							// 퀘스트 정보를 삭제해서 DB에 저장한다. 
							sDBRequest_SetSpecialQuestInfo clMsg(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo,
								&pclCM->CR[id]->pclCI->clQuestInfo.bWordAssemblySwitch[0],
								bClearSpecialWordQuest, bLampEventPeriod);
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg);

							//흥부박 퀘스트 완료건 통계. 
							pclStatisticsManager->clDailyStatistics.siSpecialQuestDoneNum++;

							if ( IsCountrySwitch(Switch_Server_Event) )
							{
								CNServerEvent_Quest* pclSE_Quest = (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
								if ( pclSE_Quest )
								{
									SI32 siQuestAmount = pclchar->siQuestCount;

									if ( 0 >= siQuestAmount )
									{
										siQuestAmount = 1;
									}
									pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_QUESTCLEAR, questtype, siQuestAmount );
								}
							}
						}						
						else if ( questtype == QUEST_TYPE_HAPPYBEAN )	//KHY - 0822 - 해피빈 퀘스트 추가.
						{
							// 클라이언트에 보상 내역을 통보한다. 
							cltGameMsgResponse_HappyBeanQuestReward clinfo(pclreward);
							cltMsg clMsg1(GAMEMSG_RESPONSE_HAPPYBEANQUEST_REWARD, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

							SendLog_SetHappyBeanClearInfo(pclchar, QUEST_TYPE_HAPPYBEAN, QUEST_HAPPYBEAN_STEP_COMPLETE);

							// 초기화후 DB저장
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo.Init();

							// 퀘스트 정보를 삭제해서 DB에 저장한다. 
							sDBRequest_SetHappyBeanQuestInfo clMsg2(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);

						}
						else if ( questtype == QUEST_TYPE_NAMING )
						{
							// naming - 초기화후 DB저장
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo.Init();

							// 퀘스트 정보를 삭제해서 DB에 저장한다. 
							sDBRequest_SetNamingQuestInfo clMsg2(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);
						}
						else if( questtype == QUEST_TYPE_MISSION1 )
						{
							// 군주데이 미션 일땐 클라로 보상 내역 통보
							if ( MISSIONQUEST_UNIQUE_GOONZUDAY == questunique )
							{
								cltGameMsgResponse_GoonzuDayMissionClearReward clinfo( pclCM->CR[id]->pclCI->GetPersonID(), 
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siExp,
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemUnique[0],
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemNum[0] );

								cltMsg clMsg1(GAMEMSG_RESPONSE_GOONZUDAYMISSION_CLEARREWARD, sizeof(clinfo), (BYTE*)&clinfo);
								pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
							}

							// 미션 퀘스트 초기화 - by LEEKH 2008-09-18
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.Init();

							// 퀘스트 정보를 삭제해서 DB에 저장한다. 
							sDBRequest_SetMissionQuestInfo clMissionQuest( pclCM->CR[id]->pclCI->GetPersonID(), &pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuest);
						}
						
						// 퀘스트 클리어 이펙트를 클라이언트로 보낸다.						
						cltGameMsgResponse_QuestEffect	clinfoQuestEff( pclchar->GetCharUnique() ,QUEST_EFFECT_CLEAR);
                        cltMsg clQuestEffMsg(GAMEMSG_RESPONSE_QUESTEFFECT,sizeof(clinfoQuestEff), (BYTE*)&clinfoQuestEff);
						pclchar->SendNeighbourMsg(&clQuestEffMsg,true);

						// 퀘스트의 상태를 변경한다. 
						pclquestinfo->siCurQuestStep	= queststep;

						// DB에 퀘스트의 상태를 저장한다. 
						sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
						SendDBMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

						// 클라이언트에 퀘스트의 상태를 통보한다. 
						pclCM->CR[id]->SetUpdateSwitch(UPDATE_QUEST, true, 0);
					}
				}
			}
		}
		if(pclquestinfo->siCurQuestStep == QUEST_STEP_CLEAR)
		{
			if(queststep == QUEST_STEP_NEXTQUEST)
			{
				SI32 bit = pclQuestManager->GetBitFromUnique(questtype, questunique);
				if(bit >= 0)
				{
					pclquestinfo->SetBit(bit, 1);		// 클리어한 퀘스트. 
				}

				// 퀘스트 정보 초기화. 
				pclquestinfo->siCurQuestUnique	= 0;
				pclquestinfo->siCurQuestStep	= 0;
				pclquestinfo->siQuestCmd		= 0;
				pclquestinfo->siQuestPara1		= 0;
				pclquestinfo->siQuestPara2		= 0;

				// DB에 퀘스트의 상태를 저장한다. 
				sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
				pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg );

				// 클라이언트에 퀘스트의 상태를 통보한다. 
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_QUEST, true, 0);

				// db에 로그를 기록한다.
				SendLog_GetQuest(personid,questtype,questunique,false);

				if ( IsCountrySwitch(Switch_Server_Event) )
				{
					if ( true == pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, questtype ) )
					{
						CNServerEvent_Quest* pclSE_Quest = (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
						if ( pclSE_Quest )
						{

							SI32 siQuestAmount = pclchar->siQuestCount;
							if ( 0 >= siQuestAmount )
							{
								siQuestAmount = 1;
							}

							pclSE_Quest->IncServerEventQuestCondition( SERVEREVENT_TYPE_QUESTCLEAR, questtype, siQuestAmount );
						}
					}
				}
			}
		}

	}
	// 진행중인 퀘스트가 없다면 새로은 퀘스트로의 진입인가 ?
	else
	{
		// questunique가 진행할 적절한 퀘스트가 맞나 ?
		// 완료되지 않은 가장 낮은 퀘스트의 Unique를 구한다. 
		SI32 minbit = pclCM->CR[id]->GetMinBit(questtype);
		// 모든 퀘스트가 완료되었따. 
		if(minbit < 0)
		{
			return ;
		}

		SI32 minquestunique = pclQuestManager->GetQuestUniqueFromBit(questtype, minbit);
		if(minquestunique <= 0)
		{
			return ;
		}

		// 아직 완료되지 않은 가장 낮은 퀘스트와 요청받은 퀘스트가 일치한다면, 
		if(minquestunique != questunique)
		{
			return ;
		}

		//요청받은 퀘스트의 단계가 QUEST_STEP_MIDDLE이 아니라면. 
		if(queststep != QUEST_STEP_MIDDLE)
		{
			return ;
		}

		cltQuestInfo* pclnextquestinfo = pclQuestManager->GetQuestInfo(questunique);
		if(pclnextquestinfo == NULL)return ;

		// 임무 부여 조건 충족 확인.
		
		// 군주 스페셜은 퀘스트 제한조건 없음
		if ( pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) == false )
		{
			// 지크의 6400 번 퀘스트를 받기 위해선 사쿠야의 모든 퀘스트를 클리어 해야 함
			if(pclnextquestinfo->siUnique == QUESTUNIQUE(6400) )
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
				{
					return;
				}								
			}

			//나죄수, 김정호의 퀘를 받기 위해선 사쿠야의 모든 퀘스트를 클리어 해야 함
			if( pclnextquestinfo->siType == QUEST_TYPE_BEGINNER3 
				||  pclnextquestinfo->siType == QUEST_TYPE_BEGINNER4
				)
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
				{
					return;
				}
			}

			// 모든 제조 퀘스트를 받기 위해선 제드의 모든 퀘스트를 클리어 해야 함
			if( pclnextquestinfo->siType == QUEST_TYPE_MAKEHEAL1 
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKESWORD1
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEBOW1 
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEHELMET1 
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKESPEAR1 
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEARMOUR1									
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEAX1 
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEGUN1
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKESTAFF1
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKEBELT1
				||  pclnextquestinfo->siType == QUEST_TYPE_MAKESHOES1 )
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, QUEST_TYPE_MAKEBEGINNER1) == false)
				{
					return;
				}                                   

			}

			// BATTLE1 을 모두 클리어 해야 BATTLE2 퀘스트를 받을 수 있다.
			if( pclnextquestinfo->siType == QUEST_TYPE_BATTLE2 )
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear(pclQuestManager, QUEST_TYPE_BATTLE1) == false)
				{
					return;
				}    
			}
		}	// if ( pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) == false ) 종료

		// 레벨 
		if(pclnextquestinfo->clInitConditionInfo.siLevel)
		{
			if(pclCM->CR[id]->pclCI->clIP.GetLevel() < pclnextquestinfo->clInitConditionInfo.siLevel)
			{
				return ;
			}
		}
		// 스킬. 
		if(pclnextquestinfo->clInitConditionInfo.siSkillUnique)
		{
			if(pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(pclnextquestinfo->clInitConditionInfo.siSkillUnique, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[0]) < pclnextquestinfo->clInitConditionInfo.siSkillLevel)
			{
				return ;
			}
		}

		// 필수 선행 퀘스트 확인.
		SI32 mustclearquestunique = pclnextquestinfo->clInitConditionInfo.siMustClearQuestUnique;
		if( mustclearquestunique > 0 )
		{
			if( pclCM->CR[id]->pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager , mustclearquestunique) == false )
			{
				return ;
			}
		}

		// 퀘스트의 상태를 변경한다. 
		pclquestinfo->siCurQuestUnique	= questunique;
		pclquestinfo->siCurQuestStep	= queststep;

		pclquestinfo->siQuestCmd	= pclnextquestinfo->clQuestClearConditionInfo.siFlag;
		pclquestinfo->siQuestPara1	= pclnextquestinfo->clQuestClearConditionInfo.siPara1;
		pclquestinfo->siQuestPara2	= 0;

		// 퀘스트 수락 이펙트를 클라이언트로 보낸다.
		cltGameMsgResponse_QuestEffect	clinfoQuestEff( pclchar->GetCharUnique() ,QUEST_EFFECT_RECEIVE);
		cltMsg clQuestEffMsg(GAMEMSG_RESPONSE_QUESTEFFECT,sizeof(clinfoQuestEff), (BYTE*)&clinfoQuestEff);
		pclchar->SendNeighbourMsg(&clQuestEffMsg,true);


		// DB에 퀘스트의 상태를 저장한다. 
		sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

		// 클라이언트에 퀘스트의 상태를 통보한다. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_QUEST, true, 0);

		// db에 로그를 기록한다.
		SendLog_GetQuest(personid,questtype,questunique,true);
	}
}

// 퀘스트 상태 통보. 
void cltServer::DoMsg_GAMEMSG_REQUEST_QUESTSTATUS(cltMsg* pclMsg, SI32 id)
{
	
	cltGameMsgRequest_QuestStatus* pclinfo = (cltGameMsgRequest_QuestStatus* )pclMsg->cData;

	switch ( pclinfo->siQuestClearCond ) 
	{
		case QUEST_CLEAR_COND_OPENCHARSTATUS:
		case QUEST_CLEAR_COND_OPENSKILL:
		case QUEST_CLEAR_COND_SELLNPC:
		case QUEST_CLEAR_COND_ITEMINFO:
		case QUEST_CLEAR_COND_NEWS:
		case QUEST_CLEAR_COND_GOMAP:
		case QUEST_CLEAR_COND_LAMPGOMAP:		// 요술램프 마을 순회
		case QUEST_CLEAR_COND_SELLMARKET:
		case QUEST_CLEAR_COND_SCROLL:
		case QUEST_CLEAR_COND_SELLTRADER:
		case QUEST_CLEAR_COND_USEWENNYOLDMAN2:
		case QUEST_CLEAR_COND_STRUCTUREOPEN:
		case QUEST_CLEAR_COND_ITEMINFODLG:
		case QUEST_CLEAR_COND_SELLSWORDNPC:
		case QUEST_CLEAR_COND_OTHERMINIHOME:
		case QUEST_CLEAR_COND_OPENSTOCKMARKET:
		case QUEST_CLEAR_COND_LOOKPANSEO:
		case QUEST_CLEAR_COND_OPENVILLAGEBOARD:
		case QUEST_CLEAR_COND_OPENCITYHALL:
		case QUEST_CLEAR_COND_OPENHUNT:
		case QUEST_CLEAR_COND_SKILLMASTER:
		case QUEST_CLEAR_COND_BROADCAST:
		case QUEST_CLEAR_COND_GONPC:
		case QUEST_CLEAR_COND_CLICKITEMINFO:
		case QUEST_CLEAR_COND_OPENMAKEITEM:
		case QUEST_CLEAR_COND_CLICKMAKEBUTTON:
		case QUEST_CLEAR_COND_OPENENCHANTITEM:
		case QUEST_CLEAR_COND_SETENCHANTITEM:
		case QUEST_CLEAR_COND_SETENCHANTELEMENT:
		case QUEST_CLEAR_COND_WARPTOPALACE:
		case QUEST_CLEAR_COND_HUNTMAPINFODLG:
		case QUEST_CLEAR_COND_SEARCHMONSTERINFO:
		case QUEST_CLEAR_COND_MAGICINFODLG:
		case QUEST_CLEAR_COND_OPENHOUSE:
		case QUEST_CLEAR_COND_OPENREALESTATEMARKET:
		case QUEST_CLEAR_COND_OPENHORSEMARKET:
		case QUEST_CLEAR_COND_OPENHOZODLG:
		case QUEST_CLEAR_COND_OPENBYUNGZODLG:
		case QUEST_CLEAR_COND_OPENGONGZODLG:
		case QUEST_CLEAR_COND_OPENIZODLG:
		case QUEST_CLEAR_COND_OPENGOONZUDLG:
		case QUEST_CLEAR_COND_USEMAGIC:
		case QUEST_CLEAR_COND_VILLAGEDETAILINFO:
		case QUEST_CLEAR_COND_OPENFRIEND:
		case QUEST_CLEAR_COND_OPENMASTER:
		case QUEST_CLEAR_COND_OPENMAKEREQUEST:
		case QUEST_CLEAR_COND_OPENNAMINGQUEST:
		case QUEST_CLEAR_COND_SUMMONATTACK:
		case QUEST_CLEAR_COND_OPENGUILD:
		case QUEST_CLEAR_COND_LOOKPRISON:
		case QUEST_CLEAR_COND_OPENGOONZUDLG_NOTICE:
		case QUEST_CLEAR_COND_CLICKITEMPROPERTY:
		case QUEST_CLEAR_COND_OPENSKILLETC:
		case QUEST_CLEAR_COND_OPENGUILDUSER:
		case QUEST_CLEAR_COND_NPCINFO:
		case QUEST_CLEAR_COND_SEARCHSTOCKINFO:
		case QUEST_CLEAR_COND_CLICKSTOCKOFFER:
		case QUEST_CLEAR_COND_CLICKCITYHALLFUND:
		case QUEST_CLEAR_COND_CLICKGENERALMETTING:
		case QUEST_CLEAR_COND_CLICKPERSONALSHOP:
		case QUEST_CLEAR_COND_OPENITEMMALL:
		case QUEST_CLEAR_COND_ANGELLISTCLICK:
		case QUEST_CLEAR_COND_POLICESETCLICK:
		case QUEST_CLEAR_COND_SEARCHFARM:
		case QUEST_CLEAR_COND_LEASECLICK:
		case QUEST_CLEAR_COND_GETMAGICLAMPQUEST:
		case QUEST_CLEAR_COND_OPENQUESTDIALOG:
		case QUEST_CLEAR_COND_ISLEARNED_MANUFACTURE:
		case QUEST_CLEAR_COND_ISGET_MANUFACTUREQUEST:
		case QUEST_CLEAR_COND_CHATTOBEGGINER:
		case QUEST_CLEAR_COND_CHECKSTATUS:
		case QUEST_CLEAR_COND_ALLWEAPONSKILL:
		case QUEST_CLEAR_COND_MEMOCLICK:
		case QUEST_CLEAR_COND_MOVETOGROUPCLICK:
		case QUEST_CLEAR_COND_EQUIPBAG:
		case QUEST_CLEAR_COND_REQUESTMENTORSUCCESS:
		case QUEST_CLEAR_COND_FULL_ORGAN:
		case QUEST_CLEAR_COND_OPENFATHERDIALOG:
		case QUEST_CLEAR_COND_OPENPOSTOFFICEDIALOG:
		case QUEST_CLEAR_COND_TAKEEQUIPLEVELWEAPON:
		case QUEST_CLEAR_COND_TAKEITEM_MATERIAL:
		case QUEST_CLEAR_COND_TAKEWEAPONHAVESLOT:
		case QUEST_CLEAR_COND_TEACHERSET:
		case QUEST_CLEAR_COND_SWORDSKILLCLICK:
		case QUEST_CLEAR_COND_LEARNWEAPONSKILL:
		case QUEST_CLEAR_COND_PVPLEAGUERESERVE:
		case QUEST_CLEAR_COND_SETMYKEY:
		case QUEST_CLEAR_COND_BUFFCLICK:
		case QUEST_CLEAR_COND_GONPC_INFORMATION:
		case QUEST_CLEAR_COND_MAKESKILLEXPUP:
		case QUEST_CLEAR_COND_SEARCH_TOTALMAP:
		case QUEST_CLEAR_COND_USE_SKILLBOOK:
			{
				// 아무처리도 하지 않음
			}
			break;
		case QUEST_CLEAR_COND_TRANSMONSTERTRICERAMONS:
			{
				SI32 siBufTransformKind = 0;
				if( pclCM->IsValidID(id) == false )												return;
				cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;

				SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
				SI32 index = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_TRANSFORM);

				stBuf* pclBuf = pclchar->pclCI->clBI.clBufInfo.GetBuf( BUF_TRANSFORM );
				if(pclBuf)			siBufTransformKind = pclBuf->siPercent;

				if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM) == true)
				{
					// 팝업으로 해당 메시지를 출력해 준다.
					SendServerResponseMsg(0, SRVAL_RETURN_LOSTWORLDQUEST_COMPLETE,  0, 0, id);
				}

				//if(siBufTransformKind == pclClient->GetUniqueFromHash( TEXT("KIND_TRICERAMONS")))
				{
					// BUF_TRANSFORM 타입으로 변신된 상황이면 무조건 완료 시킨다.
					if(index > -1)
					{
						stBuf DelBuf(pclCM->CR[id]->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, BUF_TRANSFORM);
						sDBRequest_DeleteBuf clMsg( siPersonID, index, &DelBuf );
						pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					}
				}
			}
			break;
		default:
			{
				return;
			}
			break;
	}	// switch ( pclinfo->siQuestClearCond ) 종료


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;
	
	// 현재 퀘스트가 진행중이면, 적절한 조치를 취하여 해결한다.  
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	pclchar->DoQuestCheckAndAction(pclinfo->siQuestClearCond);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RECOMMENDPERSON(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_RecommendPerson * pclinfo = (cltGameMsgRequest_RecommendPerson* )pclMsg->cData;

	

	if(pclCM->IsValidID(id)  == false)
		return;

	SI32 accountidnum = pclCM->CR[id]->pclCI->clBI.siIDNum ;
	if(accountidnum <= 0)return ;
	UI08 uiSlot = pclinfo->uiSlot ;
	if(uiSlot < 0 || uiSlot > 2 ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI32 personid = 0;
	if( pclchar->pclCharListInfo )	personid = pclchar->pclCharListInfo[uiSlot].clBI.clPerson.siPersonID ;

	if ( personid < 0 ) return ;
	
	if ( pclinfo->strUserName == NULL || _tcslen(pclinfo->strUserName ) < 1 )
	{
		sDBRequest_RecommendPerson clMsg( pclinfo->strUserName , accountidnum,uiSlot, personid,id );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
		return;
	}
	else{
		sDBRequest_RecommendPerson clMsg( pclinfo->strUserName,accountidnum,uiSlot, personid,id );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
	}	
	
	return;
}

// 자막 종류 변경
void cltServer::DoMsg_GAMEMSG_REQUEST_CAPTIONKINDCHANGE( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID(id)  == false )
		return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if( personid < 1 )
		return ;

	cltGameMsgRequest_CaptionKindChange * pclinfo = (cltGameMsgRequest_CaptionKindChange* )pclMsg->cData;

	if ( pclinfo->siCaptionKind < CAPTIONKIND_NEWSCHAT || pclinfo->siCaptionKind >= CAPTIONKIND_END )
	{
		return;
	}

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclChar == NULL )
	{
		return;
	}

	pclChar->siCaptionKind = pclinfo->siCaptionKind;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ADDINFO(cltMsg* pclMsg, SI32 id)
{
	SI32 targetid = pclMsg->siData32[0];

	if(pclCM->IsValidID(targetid)  == false)	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[targetid];

	cltGameMsgResponse_AddInfo clInfo(targetid, &pclchar->clAddInfo, pclchar->GetLife(), pclchar->GetMana());
	cltMsg clMsg(GAMEMSG_RESPONSE_ADDINFO, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGEMAGIC(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id)  == false)	return;

	SI32 magickind = pclMsg->siData32[0];
	CMagicAttribute *pMagicAttributePtr = pclMagicManager->GetMagicAttributePtr();
	stMagicAttributeData* psMagicData   = pclMagicManager->GetMagicAttribute( magickind ); 

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];	

	// 현재 장착된 무기의 Type에 따른 설정가능성을 타진한다.
	if(pMagicAttributePtr && pMagicAttributePtr->IsMatchAttackTye(id, magickind, pclchar->GetAttackType()) == true)
	{
		// 해당 Skill이 적용이 가능한지 살펴본다.

		// [진성] 스킬북 획득 마법일 경우 스킬 정보를 얻어준다.
		SI32 SkillType = pMagicAttributePtr->GetMagicSkillType(magickind);
		if( SKILL_SIKLLBOOK == SkillType && IsPC(id) )
		{
			cltSkillBookMagic*	pclSkillBookMagic = pclchar->pclCharSkillBookInfo->GetSkillBookMagic( pclchar->GetAttackType() );	
			if( NULL == pclSkillBookMagic ) return;

			SkillType = pclSkillBookMagic->GetSkillUnique();
		}

		SI32 SkillLevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel( SkillType, 0, 0, &pclchar->pclCI->clCharItem.clItem[0], id);
		if ( SkillLevel >= psMagicData->si16MagicSkillLevel )
		{
			pclchar->SetCurrentMagic(magickind, psMagicData->si08MagicCastType);
			// 요따가

			pclchar->DoQuestCheckAndAction( QUEST_CLEAR_COND_MAGICACTIVE );
		}
	}
	
	// Client에게 알려준다.
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEMAGIC, pclchar->GetCurrentMagic());
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}





void cltServer::DoMsg_GAMEMSG_REQUEST_ALLCHARINFO(cltMsg* pclMsg, SI32 id)
{
	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		{
			pclClient->pclLog->FilePrint(TEXT("EnchantBug.txt"), TEXT(" REQUEST_ALLCHARINFO START	ID = %d	Type = %d	Power = %d "), pclCM->CR[id]->pclCI->GetPersonID()  ,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siType,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siPower );
		}
	}
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		{
			pclClient->pclLog->FilePrint(TEXT("EnchantBug.txt"), TEXT(" REQUEST_ALLCHARINFO START	ID = %d	Type = %d	Power = %d "), pclCM->CR[id]->pclCI->GetPersonID()  ,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siType,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siPower );
		}
	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		{
			pclClient->pclLog->FilePrint(TEXT("EnchantBug.txt"), TEXT(" REQUEST_ALLCHARINFO START	ID = %d	Type = %d	Power = %d "), pclCM->CR[id]->pclCI->GetPersonID()  ,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siType,pclCM->CR[id]->pclCI->clCharItem.clItem[0].Element.siPower );
		}
	}


	cltPersonInfo clpersoninfo;

#if defined(_DEBUG)
	// 파티획득막음
	//	SI32 sizetest = sizeof(cltPersonInfo);
#endif

	clpersoninfo.Set(pclCM->CR[id]->pclCI);

	//----------------------------------------
	// 말 관련 정보인 경우 모든 정보를 보내지 않아야 할 때도 있따. 
	// 기술이 부족하여 말의 요구가 뭔지 모르는 경우, 
	//----------------------------------------
	cltPersonHorseInfo clhorseinfo;
	clhorseinfo.Set(&clpersoninfo.clHorseInfo);

	// 말조련술의 레벨에 따라 요구 사항을 보내지 않을수도 있다. 
	SI32 skilllevel = clpersoninfo.clCharSkill.GetTotalSkillLevel(SKILL_HORSETRAINING, 0, 0, &clpersoninfo.clCharItem.clItem[0]);
	SI32 rate = skilllevel * 10;

	cltHorse* pclHorse = clhorseinfo.GetHorse(clhorseinfo.siCurrentShowHorse);

	if( pclHorse != NULL )
	{
		if(pclHorse->siRate > rate)	
		{
			pclHorse->siPara1		= 0;
			pclHorse->siPara2		= 0;
			pclHorse->siSupply	= 0;
		}
	}

	clpersoninfo.clHorseInfo.Set(&clhorseinfo);
		
	cltPersonInfoOne clPersonInfoOne;

	clPersonInfoOne.clBI.Set(&clpersoninfo.clBI);
	clPersonInfoOne.clIP.Set(&clpersoninfo.clIP);
	clPersonInfoOne.clCharSkill.Set(&clpersoninfo.clCharSkill);
	clPersonInfoOne.clCharRank.Set(&clpersoninfo.clCharRank);
	clPersonInfoOne.clBank.Set(&clpersoninfo.clBank);
	clPersonInfoOne.clStock.Set(&clpersoninfo.clStock);
	clPersonInfoOne.clMarket.Set(&clpersoninfo.clMarket);
	clPersonInfoOne.clRealEstate.Set(&clpersoninfo.clRealEstate);
	clPersonInfoOne.clWorldMoney.Set(&clpersoninfo.clWorldMoney);

	clPersonInfoOne.clHealthInfo.Set(&clpersoninfo.clHealthInfo);
	clPersonInfoOne.clHorseInfo.Set(&clpersoninfo.clHorseInfo);
	clPersonInfoOne.clQuestInfo.Set(&clpersoninfo.clQuestInfo);
	clPersonInfoOne.clGuiltyInfo.Set(&clpersoninfo.clGuiltyInfo);
	clPersonInfoOne.clCharOption.Set(&clpersoninfo.clCharOption);
	clPersonInfoOne.clDailyQuestInfo.Set(&clpersoninfo.clDailyQuestInfo);
	clPersonInfoOne.clDailyQuest2Info.Set(&clpersoninfo.clDailyQuest2Info);
	clPersonInfoOne.clDailyQuest3Info.Set(&clpersoninfo.clDailyQuest3Info);
	
	clPersonInfoOne.clWorldOrder.Set(&clpersoninfo.clWorldOrder);
	clPersonInfoOne.uiGachaCnt = clpersoninfo.uiGachaCnt;
	clPersonInfoOne.clPersonNaming.Set(&clpersoninfo.clPersonNaming);

	clPersonInfoOne.clWorldPassport.Set( &clpersoninfo.clWorldPassport );

	cltPersonInfoTwo clPersonInfoTwo;
	clPersonInfoTwo.clCharItem.Set(&clpersoninfo.clCharItem);
	clPersonInfoTwo.clSummonInfo.Set(&clpersoninfo.clSummonInfo);


	// 정보를 역순으로 보내자 cltPersonInfoOne 클래스에 캐릭정보가 다 있다
	cltGameMsgResponse_AllCharInfoTwo clinfoTwo(&clPersonInfoTwo);
	cltMsg clMsgTwo(GAMEMSG_RESPONSE_ALLCHARINFOTWO, sizeof(clinfoTwo), (BYTE*)&clinfoTwo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsgTwo);

	cltGameMsgResponse_AllCharInfoOne clinfoOne(&clPersonInfoOne, pclCM->CR[id]->m_siSetItemType,  pclCM->CR[id]->m_siSetItemStep,
																  pclCM->CR[id]->m_siSetItemType2, pclCM->CR[id]->m_siSetItemStep2	);
	cltMsg clMsgOne(GAMEMSG_RESPONSE_ALLCHARINFOONE, sizeof(clinfoOne), (BYTE*)&clinfoOne);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsgOne);

	SI32 siSize = sizeof(cltPItemInfo);
/*
		cltGameMsgResponse_AllCharInfo clinfo( &clpersoninfo, pclCM->CR[id]->m_siSetItemType, pclCM->CR[id]->m_siSetItemStep );
		cltMsg clMsg(GAMEMSG_RESPONSE_ALLCHARINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
*/

	//------------------------------------------
	// 현재 시간 정보도 보낸다. 
	//------------------------------------------
	{
		cltMsg clDate(GAMEMSG_RESPONSE_DATE, sizeof(cltDate), (BYTE*)&pclTime->clDate);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clDate);

		//서버실제시간도 보내줌
		cltGameMsgResponse_ServerTime clTime(sTime);
		cltMsg clTimeMsg(GAMEMSG_RESPONSE_SERVERTIME, sizeof(clTime), (BYTE*)&clTime);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clTimeMsg);

	}

	//-----------------------------------------
	// 마을 점령 상태도 보낸다. 
	//-----------------------------------------
	{
		cltGameMsgResponse_EnemyCaptureAll clinfo;

		for(SI32 i = 0;i < MAX_VILLAGE_NUMBER;i ++)
		{
			if(pclVillageManager->pclVillageInfo[i])
			{
				if(pclVillageManager->pclVillageInfo[i]->bEnemyCaptureSwitch)
				{
					clinfo.Set(true, i);
				}
			}
		}

		cltMsg clMsg(GAMEMSG_RESPONSE_ENEMYCAPTUREALL, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}

	//-----------------------------------------
	// 모후모후 이벤트 중이면 알린다.
	//-----------------------------------------
	SI32 siVillageUnique = pclMofuMofuEvent->GetCurrentEventVillage();
	if(siVillageUnique > 0)
	{
		cltGameMsgResponse_MofuMofuEvent_Start clinfo(siVillageUnique);

		cltMsg clMsg(GAMEMSG_RESPONSE_MOFUMOFUEVENT_START, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	//-----------------------------------------
	//[진성] 마을 이벤트 - 몬스터 습격 중이면 알림
	//-----------------------------------------
	if(pclMonsterAttackEvent->IsEvent())
	{
		SI32 VillageUnique = pclMonsterAttackEvent->GetEventVillageUnique();

		cltMsg clMsg(GAMEMSG_RESPONSE_MONSTER_ATTACK_START, sizeof(VillageUnique), (BYTE*)&VillageUnique);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

/*	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		if(clinfo.clInfo.clCharItem.clItem[0].Element.siType > 0 && clinfo.clInfo.clCharItem.clItem[0].Element.siPower <= 0)
		{
			pclClient->pclLog->FilePrint(TEXT("EnchantBug.txt"), TEXT(" REQUEST_ALLCHARINFO END	ID = %d	Type = %d	Power = %d "), pclCM->CR[id]->pclCI->GetPersonID() ,clinfo.clInfo.clCharItem.clItem[0].Element.siType,clinfo.clInfo.clCharItem.clItem[0].Element.siPower );
		}
	}*/


	//------------------------------------------
	// 출근 상황을 점검한다. 
	//------------------------------------------
	//if(pclCM->CR[id]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
	//if(pclCM->CR[id]->IsSBS() == false)
	/*	{
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
	{
	if(pclCM->CR[id]->pclCI->clBI.bTodayFirstAttendanceSwitch && siServiceArea == ConstServiceArea_Korea )
	{
	SI32 money = 0;
	if(pclCM->CR[id]->pclCI->clBI.siAttendanceDays >= 3)
	{
	money = 300;*/ // 출석 이벤트
	// 레벨에 따라 지급되는 돈이 다르다. 
	/*if(pclCM->CR[id]->pclCI->clIP.GetLevel()	  >= 100)			money = 300;
	else if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= 50)			money = 200;
	else if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)	money = 100;												
	else money = 0;
	*/
	/*					if( siServiceArea == ConstServiceArea_Korea ) {
	PushCash(id, pclCM->CR[id]->pclCI->GetPersonID(), pclCM->CR[id]->pclCI->clBI.szAccountID, money,
	PUSHCASH_REASON_ATTENDANCE,3);
	}

	// 말복
	if ( sTime.wMonth == 8 && sTime.wDay == 14 )
	{
	SI32 itemunique = 3355 ; // 삼계탕
	SI32 itemnum	= 30;
	cltItem clItem;
	bool brareswitch = false;
	if(pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, &brareswitch) == true)
	{
	clItem.SetItemNum(itemnum);

	TCHAR buffer[256] = TEXT("") ;
	sprintf(buffer, TEXT("말복 기념으로 [%s] [%d]개를 받았습니다."),clItem.GetShortName(pclItemManager),itemnum);
	SendPostOfficeItemToPerson((TCHAR*)pclCM->CR[id]->GetName(), &clItem, buffer);
	}
	}
	}

	SendServerResponseMsg(0, SRVAL_ATTENDANCE, money, pclCM->CR[id]->pclCI->clBI.siAttendanceDays, id);

	pclCM->CR[id]->pclCI->clBI.bTodayFirstAttendanceSwitch = false ;
	}
	}
	}*/

}

void cltServer::DoMsg_GAMEMSG_REQUEST_USEBONUS(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	if(dwDBLatency > 3000)
	{
		//SendServerResponseMsg(0, SRVAL_MARKET_SELL_FAIL,  100, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	cltGameMsgResponse_UseBonus* pclinfo = (cltGameMsgResponse_UseBonus*)pclMsg->cData;


	// 보너스 수치가 정상적이지 않다면 강퇴시킨다. 
	SI32 data = pclCM->CR[id]->pclCI->clIP.GetBonus() 
		+ pclCM->CR[id]->pclCI->clIP.GetStr()
		+ pclCM->CR[id]->pclCI->clIP.GetDex()
		+ pclCM->CR[id]->pclCI->clIP.GetMag()
		+ pclCM->CR[id]->pclCI->clIP.GetHnd()
		+ pclCM->CR[id]->pclCI->clIP.GetVit()
		+ pclCM->CR[id]->pclCI->clIP.GetLuk()
		+ pclCM->CR[id]->pclCI->clIP.GetWis()
		;

	SI32 siBaseValue = 40;

	if(data != (siBaseValue + (pclCM->CR[id]->pclCI->clIP.GetLevel()-1) * 5) ) 
	{
		// apex-
#ifdef _CHINA
		if( 0 < id )
			NoticeApexProxy_UserLogout( id, (char*)pclCM->CR[id]->pclCI->clBI.szAccountID );

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		pclchar->bApexLogin = false;
#endif
		// -apex

#ifdef USE_GAME_GUARD_SERVER
		((cltCharServer*)pclCM->CR[id])->CCSAuthClose();
#endif	
		pclCM->CR[id]->GetSession()->CloseSocket();
		return ;
	}

	// 보너스를 분배하는 조건이면 보너스가 남아 있어야 쓸 수 있다.
	if(pclinfo->siAmount > 0)
	{
		if(pclCM->CR[id]->pclCI->clIP.GetBonus() < pclinfo->siAmount)return ;

		switch(pclinfo->siPos)
		{
		case 0:
			pclCM->CR[id]->pclCI->clIP.IncreaseStr(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 1:
			pclCM->CR[id]->pclCI->clIP.IncreaseDex(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 2:
			pclCM->CR[id]->pclCI->clIP.IncreaseMag(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 3:
			pclCM->CR[id]->pclCI->clIP.IncreaseVit(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 4:
			//[진성] 손재주 스탯적용 제한사항 제거. => 2008-4-4
			if(false == pclClient->IsCountrySwitch(Switch_CharStatusReform))
			{
				// 손재주는 레벨 * 2 까지만 허용한다.
				if(pclCM->CR[id]->pclCI->clIP.GetHnd() >= pclCM->CR[id]->pclCI->clIP.GetLevel()*2)return ;
				if(pclCM->CR[id]->pclCI->clIP.GetHnd() + pclinfo->siAmount >  pclCM->CR[id]->pclCI->clIP.GetLevel()*2)return;
			}

			pclCM->CR[id]->pclCI->clIP.IncreaseHnd(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 5:
			pclCM->CR[id]->pclCI->clIP.IncreaseLuk(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		case 6:
			pclCM->CR[id]->pclCI->clIP.IncreaseWis(pclinfo->siAmount);
			pclCM->CR[id]->pclCI->clIP.DecreaseBonus(pclinfo->siAmount);
			break;
		default:
			return ;
		}
	}
	else if(pclinfo->siAmount < 0)
	{
		switch(pclinfo->siPos)
		{
		case IDC_BUTTON_STR2:	if(pclCM->CR[id]->pclCI->clIP.GetStr() <= 5)return ;	break;
		case IDC_BUTTON_DEX2:	if(pclCM->CR[id]->pclCI->clIP.GetDex() <= 5)return ;	break;
		case IDC_BUTTON_MAG2:	if(pclCM->CR[id]->pclCI->clIP.GetMag() <= 5)return ;	break;
		case IDC_BUTTON_VIT2:	if(pclCM->CR[id]->pclCI->clIP.GetVit() <= 5)return ;	break;
		case IDC_BUTTON_HND2:	if(pclCM->CR[id]->pclCI->clIP.GetHnd() <= 5)return ;	break;
		case IDC_BUTTON_LUK2:	if(pclCM->CR[id]->pclCI->clIP.GetLuk() <= 5)return ;	break;
		default: return ;
		}

		// 상태부분초기화이용권이 존재하는지 확인한다. 
		//SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(14095);
		SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(ITEMUNIQUE(24035));
		if(itempos <= 0)
		{
			return ;
		}

		// 상태부분초기화이용권을 소모한다. 
		cltItem clItem;
		clItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[itempos]);
		clItem.SetItemNum(1);

		sDBRequest_UseItem clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), itempos, &clItem,USEITEM_REASON_TICKET);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	

		// 스텟을 빼서 보너스로 넣는다. 
		switch(pclinfo->siPos)
		{
		case IDC_BUTTON_STR2:	
			pclCM->CR[id]->pclCI->clIP.DecreaseStr(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		case IDC_BUTTON_DEX2:
			pclCM->CR[id]->pclCI->clIP.DecreaseDex(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		case IDC_BUTTON_MAG2:
			pclCM->CR[id]->pclCI->clIP.DecreaseMag(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		case IDC_BUTTON_VIT2:
			pclCM->CR[id]->pclCI->clIP.DecreaseVit(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		case IDC_BUTTON_HND2:
			pclCM->CR[id]->pclCI->clIP.DecreaseHnd(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		case IDC_BUTTON_LUK2:
			pclCM->CR[id]->pclCI->clIP.DecreaseLuk(1);
			pclCM->CR[id]->pclCI->clIP.IncreaseBonus(1);
			break;

		default: return ;
		}


	}
	else
	{
		return ;
	}

	// 캐릭터의 IP를 클라이언트로 보낼 수 있게 한다. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);


	//변경된 정보를 DB에 저장한다. 
	cltBasicAbility clba;

	clba.Set(	pclCM->CR[id]->pclCI->clIP.siStr, 
				pclCM->CR[id]->pclCI->clIP.siDex, 
				pclCM->CR[id]->pclCI->clIP.siVit, 
				pclCM->CR[id]->pclCI->clIP.siMag,
				pclCM->CR[id]->pclCI->clIP.siHnd, 
				pclCM->CR[id]->pclCI->clIP.siLuk,
				pclCM->CR[id]->pclCI->clIP.siWis);


	sDBRequest_SetBonusInfo clMsg(id, 	pclCM->CR[id]->pclCI->GetPersonID(), 	&clba, pclCM->CR[id]->pclCI->clIP.GetBonus());	
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	pclCM->CR[id]->SetParametaBoxAction(true);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [로그추가 : 황진성 2007. 10. 15] // 캐릭터 보너스 수치 상태 변경.
	//	// param1 == 캐릭터가 얻는 보너스 수치.
	//	cltServer* pclserver = (cltServer*)pclClient;
	//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_INPORTANTPARAMEATA, LOGCOMMAND_INDEX_INPORTANTPARAMEATA_SETBONUSINFO,
	//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//									pclCM->CR[id]->pclCI->clIP.GetBonus(), 0, 0, 0, 0,  NULL, NULL);
	//}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_NAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GetName* pclinfo = (cltGameMsgRequest_GetName*)pclMsg->cData;

	if( pclinfo->siCharUnique < 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER )	return;

	//-------------------------------------------------
	// 이름을 요청받은 대상의 아이디를 확인한다. 
	//-------------------------------------------------
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		cltGameMsgResponse_GetName clinfo(pclinfo->siCharUnique, (TCHAR*)pclCM->CR[charid]->GetName());


		// 클라이언트에게 새로운 사용자의 이름을 통보한다.
		cltMsg clNormalMsg(GAMEMSG_RESPONSE_NAME, 
			sizeof(clinfo), 
			(BYTE*)&clinfo);

		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
	}

}


void cltServer::DoMsg_GAMEMSG_REQUEST_RIGHTMOUSE_USERLIST_NAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GetName* pclinfo = (cltGameMsgRequest_GetName*)pclMsg->cData;

	if( pclinfo->siCharUnique < 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER )	return;

	//-------------------------------------------------
	// 이름을 요청받은 대상의 아이디를 확인한다. 
	//-------------------------------------------------
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		cltGameMsgResponse_GetName clinfo(pclinfo->siCharUnique, (TCHAR*)pclCM->CR[charid]->GetName());


		// 클라이언트에게 새로운 사용자의 이름을 통보한다.
		cltMsg clNormalMsg(GAMEMSG_RESPONSE_RIGHTMOUSE_USERLIST_NAME, 
			sizeof(clinfo), 
			(BYTE*)&clinfo);

		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_USERORDER(cltMsg* pclMsg, SI32 id)
{
	cltOrderData* porder	= (cltOrderData*)pclMsg->cData;
	SI32 hostid	= id;		// 명령을 수행하는 주체 캐릭터. 


	if(porder->ODI.siOrder == ORDER_ATTACK_SUMMON)
	{
		// 공격 명령을 전환한다. 
		porder->ODI.siOrder = ORDER_ATTACK;
		hostid = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(hostid)  == FALSE)
		{
			return ;
		}
	}

	if(porder->ODI.siOrder == ORDER_MAGIC_SUMMON )
	{
		// 마법 공격으로 전환한다.
		porder->ODI.siOrder = ORDER_MAGIC;
		hostid = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(hostid)  == FALSE)
		{
			return ;
		}
		if ( (pclCM->CR[hostid]->GetCurrentMagic() <= 0) || (pclCM->CR[hostid]->GetCurrentMagicCastType() != MAGIC_CASTTYPE_ACTIVE) )
		{
			return ;
		}
	}

	if(porder->ODI.siOrder == ORDER_MOVE_SUMMON)
	{
		// 이동 명령을 전환한다. 
		porder->ODI.siOrder = ORDER_MOVE;
		hostid = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(hostid)  == FALSE)
		{
			return ;
		}
	}

	// 해당 캐릭터에게 명령을 직접 전달한다. 
	LetOrder(porder, hostid);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HIT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Hit* pclinfo = (cltGameMsgRequest_Hit*)pclMsg->cData;

	SI32 charID = pclinfo->GetCharID();

	if( false == pclCM->IsValidID(charID) )
		return;

	if( true == pclCM->CR[charID]->CheckLastMsgClock(200) )
	{
		return;
	}

	if( false == pclCM->IsAlive( pclinfo->clAttackTarget.GetAttackID() ) )
		return;

	cltAttackDamageInfo clAttackDamageInfo( pclCM->CR[charID]->GetAttackType(), pclCM->CR[charID]->GetApower(), 0 );

	SI32 siAddAttackRange = pclCM->CR[charID]->GetAttackRange();
	if ( IsPC(charID) )
	{
		siAddAttackRange += pclCM->CR[charID]->m_clMagicBufMgr.GetIncRange( pclCM->CR[charID] );
	}

	HitOperation( charID, &clAttackDamageInfo, siAddAttackRange, &pclinfo->clAttackTarget, pclCM->CR[charID]->pclMap );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 클라이언트에서 요청한 원거리 공격을 등록한다.
/////////////////////////////////////////////////////////////////////////////////////////////////////
void cltServer::DoMsg_GAMEMSG_REQUEST_SETBULLET(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetBullet* pclinfo = (cltGameMsgRequest_SetBullet*)pclMsg->cData;

	SI32 charID = pclinfo->siCharID;

	if( false == pclCM->IsValidID(charID) )
		return;

	if( true == pclCM->CR[charID]->CheckLastMsgClock(200) )
	{
		return ;
	}

	// 그냥 원거리 공격
	if( pclinfo->siMagicKind == 0 )
	{
		SI32 power = pclCM->CR[charID]->GetApower();
		if( IsPC(charID) )
		{
			// 최소 거리에서 공격 불가능한 캐릭터인 경우에는 
			if( pclClient->pclAttackTypeInfoManager->IsAtb(pclCM->CR[charID]->GetAttackType(), ATTACKTYPE_ATB_MINRANGE) && 
				pclCM->CR[charID]->IsInMinRange( pclinfo->clAttackTarget.GetAttackID(), 1 ) == TRUE )
			{
				power = max( 1, power * 7 / 10 );
			}
		}

		pclClient->pclBulletManager->SetBullet( pclCM->CR[charID]->pclMap, 
			pclinfo->siBulletUnique, 
			0,  
			pclCM->CR[charID]->GetID(), 
			power, 
			&pclinfo->clTileStartPos,
			&pclinfo->clDotStartPos,
			&pclinfo->clAttackTarget,
			&pclinfo->clDotDestPos);
	}
	// 마법공격
	else
	{
		pclClient->pclBulletManager->SetBullet( pclCM->CR[charID]->pclMap, 
			pclinfo->siBulletUnique, 
			pclinfo->siMagicKind,  
			pclCM->CR[charID]->GetID(), 
			pclinfo->siPower, 
			&pclinfo->clTileStartPos,
			&pclinfo->clDotStartPos,
			&pclinfo->clAttackTarget,
			&pclinfo->clDotDestPos);
	}
}

// 캐릭터의 상태 변경 요청을 처리한다. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGESTATUSINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StatusInfo* pclinfo = (cltGameMsgRequest_StatusInfo*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;



	switch(pclinfo->ChangeInfo.siChangeType)
	{
	case CHANGETYPE_AUTOFOOD:
		{
			pclCM->CR[id]->pclCI->clHorseInfo.bAutoFoodSwitch = pclinfo->ChangeInfo.bChangeSwitch;

			// DB로 정보를 저장한다. 
			sDBRequest_SetAutoFood clDBMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->ChangeInfo.bChangeSwitch);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clDBMsg);


			// 클라이언트로 통보한다. 
			cltCharChangeStatusInfo	ChangeInfo(CHANGETYPE_AUTOFOOD, pclinfo->ChangeInfo.bChangeSwitch);
			cltGameMsgResponse_StatusInfo clinfo(id, &ChangeInfo);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		break;
	default:
		return ;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRIZE_GAMEEVENT(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	//if ( !pclCM->CR[id]->pclCI->clBI.bNewAccount ) return ;

	cltGameMsgResponse_Prize_GameEvent clinfo(pclCM->CR[id]->pclCI->clBI.bNewAccount,
		pclCM->CR[id]->pclCI->clBI.bGameEvent,pclCM->CR[id]->pclCI->clBI.bWinPrizeEvent);

	cltMsg clMsg(GAMEMSG_RESPONSE_PRIZE_GAMEEVENT, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GET_WEAPONSKILLCOST(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false ) return ;

	// 메시지가 너무 자주오는 것을 차단한다. 
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	cltGameMsgRequest_Get_WeaponSkillCost* pclinfo = (cltGameMsgRequest_Get_WeaponSkillCost*)pclMsg->cData ;

	if ( pclinfo->siSkillUnique <= 0 || pclinfo->siSkillUnique >= MAX_SKILL_NUMBER ) return ;
	if ( pclinfo->siSkillLevel < 1 || pclinfo->siSkillLevel > 5 ) return ;

	if ( pclSkillManager->pclSkillInfo[pclinfo->siSkillUnique] == NULL ) return ;
	if ( pclSkillManager->pclSkillInfo[pclinfo->siSkillUnique]->pclWeaponSkillInfo == NULL ) return ;
	if ( pclSkillManager->pclSkillInfo[pclinfo->siSkillUnique]->pclWeaponSkillInfo[pclinfo->siSkillLevel-1] == NULL ) return ;

	GMONEY cost = pclSkillManager->pclSkillInfo[pclinfo->siSkillUnique]->pclWeaponSkillInfo[pclinfo->siSkillLevel-1]->siSkillCost ;
	GMONEY money = cost * pclItemManager->clItemStatistic.siNPCPriceRate ; // 일단 1만냥에 무수리

	cltGameMsgResponse_Get_WeaponSkillCost clinfo(pclinfo->siSkillUnique,pclinfo->siSkillLevel,money);
	cltMsg clMsg(GAMEMSG_RESPONSE_GET_WEAPONSKILLCOST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SET_WEAPONSKILL(cltMsg* pclMsg,SI32 id)
{
	// 메시지가 너무 자주오는 것을 차단한다. 
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		pclLog->LogPrint( TEXT("Return MsgClock") );
		return ;
	}

	cltGameMsgRequest_Set_WeaponSkill* pclinfo = (cltGameMsgRequest_Set_WeaponSkill*)pclMsg->cData ;
	if ( NULL == pclinfo )
	{
		pclLog->LogPrint( TEXT("pclinfo is NULL") );
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		pclLog->LogPrint( TEXT("pclchar is NULL") );
		return;
	}

	// 스킬 올리기처리가 되지 않았다면
	if ( true == pclchar->bIsWeaponSkillUp )
	{
		pclLog->LogPrint( TEXT("bIsWeaponSkillUp is TRUE") );
		return;
	}

	SI32 siSkillUnique = pclinfo->siSkillUnique;
	if ( (0 >= siSkillUnique) || (MAX_SKILL_NUMBER <= siSkillUnique) )
	{
		pclLog->LogPrint( TEXT("Wrong SkillUnique Value : %d"), siSkillUnique );
		return;
	}

	SI32 siSkillLevel = pclinfo->siSkillLevel;
	if ( (0 >= siSkillLevel) || (MAX_WEAPONSKILL_LEVEL < siSkillLevel) )
	{
		pclLog->LogPrint( TEXT("Wrong SkillLevel Value : %d"), siSkillLevel );
		return;
	}

	// 히든 스킬이라면 pclGetInfo에 다른 것이 들어갈 수 있음
	cltSkillInfo* pclGetInfo = pclSkillManager->pclSkillInfo[siSkillUnique];
	if ( NULL == pclGetInfo )
	{
		pclLog->LogPrint( TEXT("pclSkillInfo is NULL") );
		return;
	}

	// 배우려는 스킬이 전투향상술이 아니라면
	if ( SKILLTYPE_FIGHT != pclGetInfo->siSkillType )
	{
		pclLog->LogPrint( TEXT("This is not Fight Skill Type [SkillUnique : %d]"), siSkillUnique );
		return;
	}

	// 히든 스킬 이라면 부모 스킬정보를 갖고온다
	bool bHiddenSkill = false;
	if ( (SKILLATB_HIDDENGRADE1 & pclGetInfo->siSkillAtb) || (SKILLATB_HIDDENGRADE2 & pclGetInfo->siSkillAtb) )
	{
		bHiddenSkill = true;

		SI32 siParentSkillUnique = pclGetInfo->siParentRef;
		if ( (0 >= siParentSkillUnique) || (MAX_SKILL_NUMBER <= siParentSkillUnique) )
		{
			pclLog->LogPrint( TEXT("Wrong Parent SkillUnique Value : %d"), siParentSkillUnique );
			return;
		}

		pclGetInfo = pclSkillManager->pclSkillInfo[siParentSkillUnique];
		if ( NULL == pclGetInfo )
		{
			pclLog->LogPrint( TEXT("parent pclSkillInfo is NULL") );
			return;
		}
	}

	if ( NULL == pclGetInfo->pclWeaponSkillInfo )
	{
		pclLog->LogPrint( TEXT("pclWeaponSkillInfo is NULL") );
		return;
	}

	SI32				siRealWeaponSkillInfoIndex	= siSkillLevel - 1;
	cltWeaponSkillInfo*	pclWeaponInfo				= pclGetInfo->pclWeaponSkillInfo[siRealWeaponSkillInfoIndex];
	if ( NULL == pclWeaponInfo )
	{
		pclLog->LogPrint( TEXT("Level pclWeaponSkillInfo is NULL [RealIndex : %d]"), siRealWeaponSkillInfoIndex );
		return;
	}

	SI32 siNeedSkillPoint = 0;	// 이값은 DB로 보내진다
	if ( false == pclSkillManager->GetWeaponSkillNeedSkillPoint(siSkillUnique, siSkillLevel, &siNeedSkillPoint) )
	{
		// 이 함수의 값이 False가 나왔다는 것은 스킬 설정의 문제이다(여기까지왔는데 저 함수에 False가 나오면 문제가 있으므로 꼭 디버깅할것)
		pclLog->LogPrint( TEXT("GetWeaponSkillNeedSkillPoint function return value is FALSE") );
		return;
	}

	// 이값은 1이상이어야 한다(기획의도)
	if ( 0 >= siNeedSkillPoint )
	{
		pclLog->LogPrint( TEXT("siNeedSkillPoint value is Zero") );
		return;
	}
	
	SI32 siSkillBouns = pclchar->pclCI->clIP.GetSkillBonus();
	if ( siNeedSkillPoint > siSkillBouns )
	{
		pclLog->LogPrint( TEXT("Not enought SkillBonus [CharSKillPoint : %d, NeedSkillPoint : %d]"), siSkillBouns, siNeedSkillPoint );
		return;
	}

	cltItem	clNeedItem;				// 이값은 DB로 보내진다 (히든 스킬일때 소모되는 아이템)
	SI32	siNeedItemPos	= -1;	// 이값은 DB로 보내진다 (-1일때는 아이템이 소모되지 않음, 즉 히든 스킬일때 쓰임) 
	GMONEY	gmRealCost		= 0;	// 이값은 DB로 보내진다 (일반 스킬일때 소모되는 돈)

	// 히든 스킬과 일반스킬의 검사 루틴이 다르다
	if ( bHiddenSkill )
	{
		if ( false == pclSkillManager->IsUpgradeHiddenWeaponSkill(siSkillUnique, siSkillLevel, id) )
		{
			pclLog->LogPrint( TEXT("IsUpgradeHiddenWeaponSkill function return value is FALSE") );
			return;
		}
		
		if ( false == pclSkillManager->GetHiddenWeaponSkillItem( siSkillUnique, siSkillLevel, &clNeedItem) )
		{
			// 이 함수가 false가 나오면 안됨 문제 있는것입니다.
			pclLog->LogPrint( TEXT("GetHiddenWeaponSkillItem function return value is FALSE") );
			return;
		}

		siNeedItemPos = pclchar->pclCI->clCharItem.FindItemInv(&clNeedItem, false);
		if ( 0 >= siNeedItemPos )
		{
			pclLog->LogPrint( TEXT("siNeedItemPos value is Zero") );
			return;
		}

		if ( clNeedItem.GetItemNum() > pclchar->pclCI->clCharItem.clItem[ siNeedItemPos ].GetItemNum() )
		{
			pclLog->LogPrint( TEXT("Not Enought NeedItemNum") );
			return;
		}
	}
	else
	{
		if ( false == pclSkillManager->IsUpgradeWeaponSkill(siSkillUnique, siSkillLevel, id) )
		{
			pclLog->LogPrint( TEXT("IsUpgradeWeaponSkill function return value is FALSE") );
			return;
		}

		GMONEY gmCost		= pclWeaponInfo->siSkillCost;
		gmRealCost			= gmCost * pclItemManager->clItemStatistic.siNPCPriceRate;

		GMONEY gmMyMoney	= pclchar->pclCI->clIP.GetMoney();
		if ( gmRealCost > gmMyMoney )
		{
			SendServerResponseMsg( 0, SRVAL_WEAPONSKILL_FAIL_MONEY, (SI16)(gmRealCost/10000) ,0 , pclchar->GetCharUnique() );
			return;
		}
	}
	
	SI32 siPersonID = pclchar->pclCI->GetPersonID();
	if ( 0 >= siPersonID )
	{
		pclLog->LogPrint( TEXT("siPersonID value is Zero") );
		return;
	}
	
	sDBRequest_Set_WeaponSkill clMsg( id, siPersonID, siSkillUnique, siSkillLevel, siNeedSkillPoint, gmRealCost, &clNeedItem, siNeedItemPos );
	pclGameDBProcess->SendMsg(DBSELECT_BASE,  (sPacketHeader *)&clMsg);

	// 이값은 리스폰 받을때 다시 풀어줘야한다
	pclchar->bIsWeaponSkillUp = true;

}
/*
void cltServer::DoMsg_GAMEMSG_REQUEST_COUNTATTACK_INFO(cltMsg* pclMsg , SI32 id)
{
if ( pclCM->IsValidID(id) == false ) return ;
// 메시지가 너무 자주오는 것을 차단한다. 
// 마지막 메시지 보낸 시간을 체크한다. 
if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
{
return ;
}

// 이미 체크중인지 아닌지 검사한다.
if ( ((cltCharServer*)pclCM->CR[id])->bCheckGameEvent == true ) return ;

SI32 itemunique = 8150 ; // 반격의깃발
SI32 itemnum = pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) ;
SI16 itempos = -1 ;

if ( itemnum > 0 )
{
itempos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
}

cltItem clItem;
clItem.Init() ;

if ( itempos > 0 )
{
clItem.siUnique = itemunique ;
clItem.siItemNum = itemnum ;
}
else
{
itempos = 0 ;
}

SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
if(personid <= 0)return ;

sDBRequest_CountAttack_Info clinfo(personid,id,&clItem,itempos) ;
pclGameDBProcess->SendMsg(DBSELECT_BASE,  (sPacketHeader *)&clinfo);

((cltCharServer*)pclCM->CR[id])->bCheckGameEvent = true ;
}*/

void cltServer::DoMsg_GAMEMSG_REQUEST_EVENTNPC(cltMsg* pclMsg , SI32 id)
{
	/*	if ( pclCM->IsValidID(id) == false ) return ;
	// 메시지가 너무 자주오는 것을 차단한다. 


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	SI08 data = 1;

	if ( pclCM->CR[id]->pclCI->clBI.bGameEvent == false )
	{
	cltItem clItem;
	// 반격의 깃발 1개를 준다
	SI32 itemunique = ITEMUNIQUE(8150);
	SI32 ref = pclItemManager->FindItemRefFromUnique(itemunique);
	if(ref > 0)
	{
	clItem.Set(&pclItemManager->pclItemInfo[ref]->clItem);
	clItem.SetItemNum(1);

	cltCharServer* pclmychar = (cltCharServer*)pclCM->CR[id];

	SI32 rtnvalue = 0;
	if(pclmychar->InputItem(pclItemManager, &clItem, INPUTITEMPERSON_OPTION_NONE, &rtnvalue) == false)
	{
	// 인벤에 빈자리가 없어서 추가할 수 없다. 
	if(rtnvalue == CANADDINV_FAIL_FULL)
	{
	SendServerResponseMsg( 0, SRVAL_ADDINV_FAIL_FULL,  clItem.siUnique, 0, pclmychar->GetCharUnique());
	}
	}
	}
	pclCM->CR[id]->pclCI->clBI.bGameEvent = true ;
	sDBRequest_Prize_GameEvent clevent(personid, id, (UI08)sTime.wDay, false);
	SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clevent);
	data = 0;
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_EVENTNPC,1,&data);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);*/
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETGREETING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetGreeting* pclinfo = (cltGameMsgRequest_SetGreeting*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return ;

	sDBRequest_SetGreeting clMsg( id, personid, pclinfo->szGreeting);
	// 글로벌에서 인사말 버그가 발생하여, 최대입력 바이트를 100바이트로 제한한다. - by LEEKH 2009-02-24
	pclinfo->szGreeting[ MAX_GREETING_LENGTH + 1 ] = '\0';
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETGREETING(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_GetGreeting* pclinfo = (cltGameMsgRequest_GetGreeting*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	//if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)
	//	return;

	SI32 targetid = pclCM->GetIDFromPersonID( pclinfo->siPersonID );
	if (pclCM->IsValidID(targetid) == false)
	{
		return;
	}

	TCHAR tempName[MAX_PLAYER_NAME];

	StringCchCopy(tempName, MAX_PLAYER_NAME, pclCM->CR[targetid]->GetName());

	cltGameMsgResponse_GetGreeting clinfo( pclinfo->siParam, tempName, pclCM->CR[targetid]->pclCI->clBI.szGreeting );

	cltMsg clMsg(GAMEMSG_RESPONSE_GETGREETING, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GET_HOMEPAGE_URL(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_GetHomepage_URL* pclinfo = (cltGameMsgRequest_GetHomepage_URL*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return ;

	SI32 targetid = pclCM->GetIDFromPersonID( pclinfo->siPersonID );
	if (pclCM->IsValidID(targetid) == false) return;
	

	TCHAR tempName[MAX_PLAYER_NAME];
	StringCchCopy(tempName, MAX_PLAYER_NAME, pclCM->CR[targetid]->GetName());


	// DB로 홈페이지 URL정보를 요청한다.
 	sDBRequest_Get_HomePageURL clMsg( id, personid, tempName);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SET_HOMEPAGE_URL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetHomepage_URL* pclinfo = (cltGameMsgRequest_SetHomepage_URL*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return ;


	// DB로 폼페이지 URL정보를 셋팅한다.
	sDBRequest_Set_HomePageURL clMsg( id, personid, pclinfo->szHomepageURL);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SITDOWN(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_SitDown* pclinfo = (cltGameMsgRequest_SitDown*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if( pclChar == NULL)
		return;
	if ( pclChar->GetMapIndex() == MAPINDEX_BATTLEROYAL_GRANDMABRIUM || pclChar->GetMapIndex() == MAPINDEX_BATTLEROYAL_MABRIUM)
		return;

	// gmmode 4일때(Berserker) 는 앉을수 없다. 동작이 없으므로
	if ( pclCM->CR[id]->pclCI->clBI.GetKind() == pclClient->GetUniqueFromHash(TEXT("KIND_BERSERKER")) )
	{
		return;
	}

	if ( pclClient->pclCM->CR[id]->pclCI->clBI.uiGMMode == 4 )
	{
		return;
	}

	((cltCharServer*)pclCM->CR[id])->DoQuestCheckAndAction( QUEST_CLEAR_COND_SITDOWN );

	if ( pclinfo->bSitDown )
	{
		switch( pclinfo->siDirection )
		{
		case SOUTH|EAST:			
		case SOUTH:			
		case SOUTH|WEST:			
		case WEST:			
		case WEST|NORTH:			
		case NORTH:			
		case NORTH|EAST:			
		case EAST:
			{
				if( pclinfo->siDirection )
				{
					pclCM->CR[id]->ChangeDirectionNormal( pclinfo->siDirection );
				}
				OrderSitDown( id, pclinfo->siDirection, BY_PLAYER );
			}
			break;
		default:
			return;
		}
	}
	else
	{
		OrderForceStop( id, BY_PLAYER );
	}
}

//cyj 클라이언트로 부터 부활을 요청하는 메세지를 받으면 부활
void cltServer::DoMsg_GAMEMSG_REQUEST_REVIVE(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_Revive * pclinfo = (cltGameMsgRequest_Revive*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)
		return;

	pclCM->CR[id]->Revive();
}
// 보물찾기 이벤트 - 오카라 주고 버프 받기.
void cltServer::DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_USEOKARA(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_TreasureEvent_Use_Okara * pclinfo = (cltGameMsgRequest_TreasureEvent_Use_Okara*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;
	// 사용할 아이템
	// 오카라
	SI32 siUseItem = ITEMUNIQUE( 2017 );
	SI32 siUseItemNum  = 10 ;	// 10개
	cltItem clitem;
	SI32 siref = pclClient->pclItemManager->FindItemRefFromUnique(siUseItem);
	if(siref <= 0) return ;
	// 먼저 인벤토리에서 해당 아이템이 있는지 확인 한다.
	cltCharServer * pclchar = (cltCharServer *)pclCM->CR[id];
	SI32 siHaveitemNum = pclchar->pclCI->clCharItem.GetItemNum( siUseItem ) ;	// 아이템을 몇개 가지고 있는지 확인.

	SI16 siEmptySlot = pclchar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_FINDTREASURE, false );
	if ( siEmptySlot < -1)	return	;	// 버프 걸 자리가 없다.

	if ( siHaveitemNum >= siUseItemNum ) // 충분한 수가 있다면 
	{
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			if(pclchar->pclCI->clCharItem.clItem[i].siUnique == siUseItem)
			{
				if ( siUseItemNum == 0 )	break	;	// 갯수가 0개면 끝낸다
				SI32 invItemNum = pclchar->pclCI->clCharItem.clItem[i].GetItemNum()	;
				if ( invItemNum  >= siUseItemNum )
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = siUseItemNum;
					sDBRequest_UseItem clMsg(id, pclchar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					break	;
				}
				else
				{
					clitem.Set(&pclClient->pclItemManager->pclItemInfo[siref]->clItem);
					clitem.siItemNum = invItemNum	;// 양만큼 넣고 

					//전체 갯수에서 뺴준다
					siUseItemNum =  siUseItemNum - invItemNum	;
					// 사용해라
					sDBRequest_UseItem clMsg(id, pclchar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}
		}
		// 다 소모 했다면 버프를 준다.
		SI32 siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // 현실시간 48분간.
		if ( -1 < siEmptySlot )
		{
			stBuf addBuf(BUF_EVENT_FINDTREASURE, 0, siUseItem);
			pclchar->AddBufThroughDB( siEmptySlot, &addBuf , false , 0 ,NULL,0  );
		}

	}
};

void cltServer::DoMsg_GAMEMSG_REQUEST_RESURRECTION(cltMsg* pclMsg , SI32 id)
{
    cltGameMsgRequest_Resurrection * pclinfo = (cltGameMsgRequest_Resurrection *)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false ) return ;
	
	if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)
		return;

	cltCharServer * pclchar = (cltCharServer *)pclCM->CR[id];

	if(NULL == pclchar)
		return;

	// 인던에서 부활하는 모드가 아니면 한양으로 보낸다. 부활용 아이템을 소모하지 않는다.
	if( pclClient->pclMapManager->IsInstanceMap( pclchar->GetMapIndex() ) == true &&
		pclchar->siKilledMode == 0 )
	{
		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
		pclchar->SetWarpInfo(&clWarpInfo, 56);
		pclchar->Warp();

		return;
	}
	
	// [기형] 배틀로얄 중일 경우 그냥 부활 
	if(pclchar->siKilledMode == KILLEDMODE_BATTLEROYAL)
	{
		pclchar->Revive();
	}
	// 부활용 아이템을 가지고 있다면 즉시 부활. 없다면 가까운 마을 부활 - 다른 아이템보다 보험증서를 먼저 찾아서 확인 한다 
	for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];

		if( pclitem->siUnique <= 0 ) continue;

		if(	pclitem->siUnique == ITEMUNIQUE(2731)	&& pclitem->GetItemNum() > 0 )
		{
			//// 보험증서를 찾았다. 사용 예약시킨후 살린다.
			//while(pclchar->clItemUseReserveInfo.Push(ITEMUNIQUE(2731) , -1 , i) == false)
			//{
			//	pclchar->ItemUseReserveAction();
			//}

			//if(pclitem->siItemNum == 1)
			//{
			//	pclchar->ItemUseReserveAction();
			//}

			//pclitem->Decrease(1);
			//  이미 사용 했기 때문에 업데이트만하고 살린다 

			// 클라이언트로 소모된 아이템 업데이트
			cltGameMsgResponse_PersonItemInfo clinfo( i , PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			// 제자리에서 즉시 부활시킨다.
			((cltCharServer*)pclCM->CR[id])->Resurrection(false);

			return;
		}
	}
	// 부활용 아이템을 가지고 있다면 즉시 부활. 없다면 가까운 마을 부활	//보험증서가 없다 이제 나머지 다른 부활용 아이템들을 찾아서 살린다.
	for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];

		if( pclitem->siUnique <= 0 ) continue;

		SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);

		if( ref <= 0 ) continue;

		if(	pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESURRECTION	&& pclitem->GetItemNum() > 0 )
		{
			// 아이템 위치를 찾았다. 소모를 예약 시키고 부활시킨다.
			while(pclchar->clItemUseReserveInfo.Push(pclitem->siUnique , -1 , i) == false)
			{
				pclchar->ItemUseReserveAction();
			}

			if(pclitem->siItemNum == 1)
			{
				pclchar->ItemUseReserveAction();
			}

			pclitem->Decrease(1);

			// 클라이언트로 소모된 아이템 업데이트
			cltGameMsgResponse_PersonItemInfo clinfo( i , PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			// 제자리에서 즉시 부활시킨다.
			((cltCharServer*)pclCM->CR[id])->Resurrection(false);
						
			return;
		}
	}
	// PVP로 죽은 거라면 그자리에서 부활
	if ( pclinfo->siDieMode == PVP_DIE ) 
	{
		// 제자리에서 즉시 부활시킨다.
		((cltCharServer*)pclCM->CR[id])->Resurrection(true);
		return	;
	}
	// pk 맵변경 이후 pk 맵이라면 엔팰리스로보낸다 .,
	if ( IsCountrySwitch( Switch_PKHuntMap_Change_Info )) 
	{
		if( pclClient->pclMapManager->IsPkMap( pclchar->GetMapIndex() ) == true && 
			pclchar->siKilledMode == 0 )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// 경복궁 안전지대로 워프. 
			pclchar->SetWarpInfo(&clWarpInfo, 56);
			pclchar->Warp();

			return;
		}
	}
	// 못 찾고 빠져나왔다. 그냥 부활시킨다.
	
	pclchar->Revive();

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONNAME_SERIALID(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_GetNameFromItemSerialID *pclInfo = (cltGameMsgRequest_GetNameFromItemSerialID*)pclMsg->cData;

	if (pclCM->IsValidID(id) == false ) return;

	if (pclInfo->siSerialID <= 0 ) return;

	
	cltPersonNameInfo clPersonInfo;
	if( pclNewPersonNameManager->Find( pclInfo->siSerialID, &clPersonInfo ) )
	{
		cltGameMsgResponse_GetNameFromItemSerialID clPersonName(pclInfo->siSerialID, clPersonInfo.szPersonName, clPersonInfo.siServerUnique );
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONNAME_SERIALID, sizeof(clPersonName), (BYTE*)&clPersonName);
			
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	else
	{
		sDBRequest_GetItemMakerNameNew clMsg( id, pclInfo->siSerialID );
		pclClient->SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONNAME_FROMPERSONID(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_GetNameFromPersonID *pclInfo = (cltGameMsgRequest_GetNameFromPersonID*)pclMsg->cData;

	if (pclCM->IsValidID(id) == false ) return;

	if (pclInfo->siPersonID <= 0 ) return;

	TCHAR buf[MAX_PLAYER_NAME];

	if (pclPersonNameManager->Find(pclInfo->siPersonID, buf))
	{
		if (buf)
		{
			cltGameMsgResponse_GetNameFromPersonID clPersonName(pclInfo->siPersonID, buf);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONNAME_FROMPERSONID, sizeof(clPersonName), (BYTE*)&clPersonName);
						
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	else
	{
		sDBRequest_GetItemMakerName clMsg(id, pclInfo->siPersonID);
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg);
	}



}
void cltServer::DoMsg_GAMEMSG_REQUEST_SETCOUNTRYINFO( cltMsg* pclMsg,SI32 id )
{
	if (pclCM->IsValidID(id) == false ) return;

	cltGameMsgRequest_SetCountryInfo *pclinfo = (cltGameMsgRequest_SetCountryInfo*)pclMsg->cData;

	pclClient->pclCM->CR[id]->pclCI->clBI.bShowCountry = pclinfo->bShowCountry;
	pclClient->pclCM->CR[id]->pclCI->clBI.siCountryID = pclinfo->siCountryID;

	if ( pclinfo->siCountryID != -1 )
	{
		SI32 personid = pclClient->pclCM->CR[id]->pclCI->GetPersonID();
		// 국가 정보 DB에 보내기
        sDBRequest_SetCountry clMsg( personid, pclinfo->siCountryID );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );

		// 공개 여부 DB로 보내기
		sDBRequest_SetShowCountry clMsg2( personid, pclinfo->bShowCountry );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg2 );
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_SETSHOWCOUNTRY( cltMsg*pclMsg, SI32 id )
{
	if (pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_SetShowCountry *pclinfo = (cltGameMsgRequest_SetShowCountry*)pclMsg->cData;
	SI32 personid = pclClient->pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_SetShowCountry clMsg( personid, pclinfo->bShowCountry );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETSHOWPUCHIKOMI( cltMsg*pclMsg, SI32 id )
{
	if ( pclCM->IsValidID(id) == false ) return;

	cltGameMsgRequest_SetShowPuchikomi *pclinfo = (cltGameMsgRequest_SetShowPuchikomi*)pclMsg->cData;

	if( pclCM->CR[id]->siAccountStatus == CHANNELINGCODE_HANGAMEJP )
	{
		pclCM->CR[id]->pclCI->clBI.bShowPuchikomi = false;
		return;
	}

	SI32 personid = pclClient->pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_SetShowPuchikomi clMsg( personid, pclinfo->bShowPuchikomi );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );

	
}


void cltServer::DoMsg_GAMEMSG_REQUEST_USERLISTBYCOUNTRY( cltMsg* pclMsg, SI32 id )
{
	if (pclCM->IsValidID(id) == false ) return;

	cltGameMsgRequest_UserListByCounty *pclinfo = (cltGameMsgRequest_UserListByCounty*)pclMsg->cData;
	if ( pclinfo->siCountryID > -1 )
	{
		SI32	personid[MAX_USERLIST_NUM];
		TCHAR	charname[MAX_USERLIST_NUM][MAX_PLAYER_NAME];
		SI32	charlevel[MAX_USERLIST_NUM];
		TCHAR	villagename[MAX_USERLIST_NUM][32];
		// 변수 초기화
		for ( SI32 i = 0; i < MAX_USERLIST_NUM; ++i )
		{
			personid[i] = 0;
			StringCchCopy( charname[i], MAX_PLAYER_NAME, TEXT("") );
			charlevel[i] = 0;
			StringCchCopy( villagename[i], 32, TEXT("") );		}

		SI32 usercount = 0;
		SI32 tempid = 0;
		SI32 index = 0;

		for ( SI32 i = 1; i < MAX_PERSON_NUMBER ; ++i )
		{
			if( i == id )
				continue;

			if ( pclCM->IsValidID(i) == false)
				continue;

			if( pclCM->CR[i]->pclCI->clBI.siCountryID ==  pclinfo->siCountryID &&
				( pclCM->CR[i]->pclCI->clBI.bShowCountry == TRUE || 
				pclCM->CR[id]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL )  )
			{
				personid[usercount] = pclCM->CR[i]->pclCI->GetPersonID();
				StringCchCopy( charname[usercount], MAX_PLAYER_NAME, pclCM->CR[i]->GetName() );
				charlevel[usercount] = pclCM->CR[i]->pclCI->clIP.GetLevel();
				TCHAR* homevillage = pclClient->pclVillageManager->GetName( pclCM->CR[i]->pclCI->clBI.siHomeVillage );
				if ( homevillage == NULL ) 
				{
					StringCchCopy( villagename[usercount], 32,  TEXT("") );	
				}
				else
				{
					StringCchCopy( villagename[usercount], 32,  homevillage );	
				}
				usercount++;
			}

			if ( usercount >= MAX_USERLIST_NUM ) break;
		}

		//while(tempid = pclCM->GetCharOrder(index))
		//{
		//	index++;

		//	if( tempid == id )
		//		continue;

		//	// 사용자인 컴에게만 전달한다. 
		//	if(pclCM->IsValidID(tempid) && pclCM->CR[tempid]->IsValidConnection() == true)
		//	{
		//		if( pclCM->CR[tempid]->pclCI->clBI.siCountryID ==  pclinfo->siCountryID &&
		//			( pclCM->CR[tempid]->pclCI->clBI.bShowCountry == TRUE || 
		//			pclCM->CR[tempid]->pclCI->clBI.siCountryID == pclCM->CR[id]->pclCI->clBI.siCountryID ) )
		//		{
		//			personid[usercount] = pclCM->CR[tempid]->pclCI->GetPersonID();
		//			StringCchCopy( charname[usercount], MAX_PLAYER_NAME, pclCM->CR[tempid]->GetName() );
		//			charlevel[usercount] = pclCM->CR[tempid]->pclCI->clIP.GetLevel();
		//			TCHAR* homevillage = pclClient->pclVillageManager->GetName( pclCM->CR[tempid]->pclCI->clBI.siHomeVillage );
		//			if ( homevillage == NULL ) 
		//			{
		//				StringCchCopy( villagename[usercount], 32,  TEXT("") );	
		//			}
		//			else
		//			{
		//				StringCchCopy( villagename[usercount], 32,  homevillage );	
		//			}
		//			usercount++;
		//		}

		//		if ( usercount >= MAX_USERLIST_NUM ) break;
		//	}

		//}


		
		if ( usercount <= 0 ) return; 

		cltGameMsgResponse_UserListByCounty clinfo( (SI32*)personid, (TCHAR**)charname, (SI32*)charlevel,  (TCHAR**)villagename );

		cltMsg clMsg(GAMEMSG_RESPONSE_USERLISTBYCOUNTRY, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_ADDCHINESEUSER( cltMsg *pclMsg, SI32 id)
{
	if (pclCM->IsValidID(id) == false )	return;

	pclStatisticsManager->clDailyStatistics.siChineseUserCount++;
}

// 20미만 레벨 유저 요청
void cltServer::DoMsg_GAMEMSG_REQUEST_LOWLEVELLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_LowLevelList* pclinfo = (cltGameMsgRequest_LowLevelList*)pclMsg->cData;
	cltChildInfo LowLevel[MAX_LOWLEVEL_LIST_NUMBER-1];
	SI32 userid;
	SI32 index = 0;
	SI32 NumUser = 0;
	//for( NumUser = 0; NumUser < MAX_LOWLEVEL_LIST_NUMBER - 1;  NumUser++)
	//{
	//	if(pclCM->IsValidID(siLowLevelCharUnique[NumUser]))
	//	{
	//		if(IsPC(siLowLevelCharUnique[NumUser]))
	//		{
	//			if( pclCM->CR[id]->GetCharUnique() != pclCM->CR[siLowLevelCharUnique[NumUser]]->GetCharUnique() )
	//			{
	//				LowLevel[NumUser].clPerson = pclCM->CR[siLowLevelCharUnique[NumUser]]->pclCI->clBI.clPerson;
	//				LowLevel[NumUser].siLevel = pclCM->CR[siLowLevelCharUnique[NumUser]]->pclCI->clIP.GetLevel();
	//				strcat(LowLevel[NumUser].szAccountID, pclCM->CR[siLowLevelCharUnique[NumUser]]->pclCI->clBI.szAccountID);
	//			}
	//		}
	//	}
	//}
	while(userid = pclCM->GetCharOrder(index) )
	{
		index++;

		if(pclCM->IsValidID(userid))
		{
			if(IsPC(userid))
			{
				if( pclCM->CR[userid]->pclCI->clIP.GetLevel() < 20 && pclCM->CR[id]->GetCharUnique() != pclCM->CR[userid]->GetCharUnique() )
				{
					for(int i = 0; i < MAX_LOWLEVEL_LIST_NUMBER -1; i++)
					{
						if( siLowLevelCharUnique[i] == pclCM->CR[userid]->GetCharUnique() )
						{
							if( NumUser < MAX_LOWLEVEL_LIST_NUMBER -1)
							{
								LowLevel[NumUser].clPerson = pclCM->CR[userid]->pclCI->clBI.clPerson;
								LowLevel[NumUser].siLevel = pclCM->CR[userid]->pclCI->clIP.GetLevel();
								strcat(LowLevel[NumUser].szAccountID, pclCM->CR[userid]->pclCI->clBI.szAccountID);
								NumUser++;											
							}
						}
					}
				}
			}
		}
	}

	cltGameMsgResponse_LowLevelList clinfo(LowLevel);
	cltMsg clMsg(GAMEMSG_RESPONSE_LOWLEVELLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MYPUCHIKOMIURL(cltMsg* pclMsg, SI32 id)
{
	// 일본에서만 푸치코미 서비스를 한다
	if(siServiceArea != ConstServiceArea_Japan) return;

  	cltGameMsgRequest_MyPuchikomiURL * pclinfo = (cltGameMsgRequest_MyPuchikomiURL*)pclMsg->cData;

	UI08 md5buf[256] = "" ;
	char buffermd5ID[256] = "" ;
	char buffermd5PassWord[256] = "" ;

	char tmp[256] = "" ;
	
	sprintf(tmp,"%s", pclinfo->szAccountID );	

	SI32 tmpsize = strlen(tmp);

	// URLEncode
	CString str ;
	str.SetString(tmp,tmpsize);
	CString unicodeID = URLEncode(str);

	// MD5
	SI32 md5size = unicodeID.GetLength() ;
	memcpy(md5buf,unicodeID.GetBuffer(md5size),md5size);

	md5_string(md5buf, buffermd5ID, md5size);
    
	sprintf(tmp,"%s", pclinfo->szPassWord );

	tmpsize = strlen(tmp);
	
	// URLEncode
	str.SetString(tmp,tmpsize);
	CString unicodePass = URLEncode(str);

	// MD5
	md5size = unicodePass.GetLength() ;
	memcpy(md5buf,unicodePass.GetBuffer(md5size),md5size);

	md5_string(md5buf, buffermd5PassWord,md5size);

	
	TCHAR URLbuf[MAX_PUCHIKOMI_URL] = {'\0',};

	StringCchPrintf(URLbuf,MAX_PUCHIKOMI_URL,TEXT("%s&%s"), buffermd5ID , buffermd5PassWord );

	cltGameMsgResponse_MyPuchikomiURL clinfo(URLbuf);	
	cltMsg clMsg(GAMEMSG_RESPONSE_MYPUCHIKOMIURL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

}


void cltServer::DoMsg_GAMEMSG_REQUEST_USERPUCHIKOMIURL(cltMsg* pclMsg, SI32 id)
{
	// 일본에서만 푸치코미 서비스를 한다
	if(siServiceArea != ConstServiceArea_Japan) return;

	cltGameMsgRequest_UserPuchikomiURL * pclinfo = (cltGameMsgRequest_UserPuchikomiURL *)pclMsg->cData;

	if( pclinfo->siToPersonCharUnique ) 
	{
		SI32 toid = pclCM->GetIDFromCharUnique( pclinfo->siToPersonCharUnique );
		if( pclCM->IsValidID(toid) == false ) return ;
		
		if( pclCM->CR[toid]->pclCI->clBI.bShowPuchikomi == false )
		{
			SendServerResponseMsg( 0 , SRVAL_PUCHIKOMI_FAIL_OP_REJECTION , 0 , 0 , pclCM->CR[id]->GetCharUnique() );
			return;
		}

		UI08 md5buf[256] = "" ;
		char buffermd5ID[256] = "" ;
		char buffermd5PassWord[256] = "" ;

		char tmp[256] = "" ;

		sprintf(tmp,"%s",	pclCM->CR[toid]->pclCI->clBI.szAccountID );	
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
	else
	{
		SI32 toid = pclCM->GetIDFromName( pclinfo->szToPersonName );
		
		

		if( pclCM->IsValidID(toid) == false )
		{
			// 현재 접속중이 아니라면 DB로 조회를 요청한다.
			
			SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
			if( personid <= 0  ) return;

			sDBRequest_Userid clMsg( pclCM->CR[id]->GetCharUnique(), personid, pclinfo->szToPersonName );
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
			
			return ;
		}

		if( pclCM->CR[toid]->pclCI->clBI.bShowPuchikomi == false )
		{
			SendServerResponseMsg( 0 , SRVAL_PUCHIKOMI_FAIL_OP_REJECTION , 0 , 0 , pclCM->CR[id]->GetCharUnique() );
			return;
		}
		

		UI08 md5buf[256] = "" ;
		char buffermd5ID[256] = "" ;
		char buffermd5PassWord[256] = "" ;

		char tmp[256] = "" ;

		sprintf(tmp,"%s", pclCM->CR[toid]->pclCI->clBI.szAccountID );	
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


}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETEMOTICON(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_SetEmoticon* pclinfo = (cltGameMsgRequest_SetEmoticon*)pclMsg->cData;

	cltGameMsgResponse_SetEmoticon clinfo( pclinfo->m_siIndex , pclCM->CR[id]->GetCharUnique() );
	cltMsg clMsg(GAMEMSG_RESPONSE_SETEMOTICON, sizeof( clinfo ) , (BYTE*)&clinfo );

	((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg( &clMsg, true );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GAME_GUARD_AUTH(cltMsg* pclMsg, SI32 id )
{

#ifdef USE_GAME_GUARD_SERVER

	cltGameMsgRequest_GameGuardAuth * pclinfo = (cltGameMsgRequest_GameGuardAuth *)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar == NULL)						return;

	// 인증처리
	pclchar->CCSReceivedAuth(&pclinfo->ggData);

#endif
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ATTEND(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_Attend* pclInfo = (cltGameMsgRequest_Attend*)pclMsg->cData;
	if ( pclInfo == NULL )					return;

	if ( pclCM->IsValidID(id) == false )	return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )					return;

	switch ( pclInfo->siType ) 
	{
		case ATTEND_EVENTTYPE_ATTENDANCE:
			{
				if ( pclchar->pclCI->clBI.bAttendToday[ ATTEND_EVENTTYPE_ATTENDANCE ] == true )
				{
					return;
				}

				// 출석을 할 수 없다면
				if ( pclchar->pclCI->clBI.bIsCanAttend == false )
				{
					SendServerResponseMsg( 0, SRVAL_FAIL_SEASON2_ATTEND_NOTGIVEITEM, 0, 0, id );

 					return;
				}

				if ( pclchar->pclCI->clBI.bIsAttendTime == false )
				{
					return;
				}
			}
			break;
		//-----------------------------------------------------------------------------------------

		default:
			return;
	}

	NDate kAttendDay;
	

	kAttendDay.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );	

	sDBRequest_SetAttend clMsg( pclchar->pclCI->GetPersonID(), pclchar->GetID(), &kAttendDay, pclInfo->siType );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ATTENDREWARDITEM(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_AttendRewardItem* pclInfo = (cltGameMsgRequest_AttendRewardItem*)pclMsg->cData;
	if ( pclInfo == NULL )
	{
		return;
	}

	if ( pclCM->IsValidID(id) == false )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL )
	{
		return;
	}

	switch	( pclInfo->siType ) 
	{
		case ATTEND_EVENTTYPE_SEASON2:
			{
				// 이미 보상을 받을 수 없는 상태라면
				if ( pclchar->pclCI->clBI.bAttendToday[pclInfo->siType] == true )
				{
					return;
				}

				// 보상을 받을 수 있는지 체크해서 안되면 못받는다
				if ( pclchar->pclCI->clBI.bIsCanReward == false )
				{
					return;
				}

				// 출석 보상을 받을 수 있는 날인지만 체크해서 Season2 출석을 한다.
				cltItem clRewardItem;
				if ( GetItemByAttendanceDay( pclchar->pclCI->clBI.siAttendanceDays, &clRewardItem ) )
				{
					NDate kAttendDay;
					kAttendDay.SetDate( sTime.wYear, sTime.wMonth, sTime.wDay );

					sDBRequest_SetAttend clDBSetAttend( pclchar->pclCI->GetPersonID(), pclchar->GetID(), &kAttendDay, pclInfo->siType );
					pclGameDBProcess->SendMsg((sPacketHeader *)&clDBSetAttend);
				}

			}
			break;
		default:
			return;
	}
}

//KHY - 0910 - 클라이언트로 캐릭터형태의 리턴값을 보낸다.
void cltServer::DoMsg_GAMEMSG_REQUEST_CHARSERVERRTN(cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_CharServerRTN* pclinfo = (cltGameMsgRequest_CharServerRTN*)pclMsg->cData;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if(pclinfo->siResult == 1)
	{
		//KHY - 0906 -해당계정의 해당이벤트 타입에 따른 쿠폰을 발급여부를 요청한다.
		SendLog_SetEventCouponInfo(pclchar, GAMEROOM_COUPON_EVENT,0);	
	}
}

//KHY - 1220 - 변신시스템.
void cltServer::DoMsg_GAMEMSG_REQUEST_TRANSFORM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_SetTransForm* pclinfo = (cltGameMsgRequest_SetTransForm*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltItem *pclItemList = pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
	cltPSkillInfo *pclskillinfo = &pclchar->pclCI->clCharSkill;
 
	//---------------------------------------------
	// [기형] 배틀로얄 경기장이라면 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclchar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclchar) )
				return;
		}
	}

	// 데이터 검증
	if( pclinfo->m_siTransFormKind < 0 || pclinfo->m_siTransFormKind >= MAX_KIND_NUMBER )		return;
	if( pclKindInfoSet->pclKI[pclinfo->m_siTransFormKind] == NULL)								return;

	if( pclCM->IsAlive( id ) == false ) //죽으면 변신 할 수 없다.
	{
		//SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}
	//if ( pclchar->siEnemUnique > 0 ) 
	//{
	//	// 전투중에는 변신 불가능 
	//	return	;
	//}

	if( pclchar->clTransFormInfo.bTransFormMode == true ) // 변신 상태면 리턴.
		return;

	if( pclchar->clTransFormInfo.SearchTransFormChar((UI16)pclinfo->m_siTransFormKind) == false ) // 변신 상태면 리턴.
		return;

	if( pclchar->GetAttackType() == ATTACKTYPE_HAND )
	{
		// 무기를 장착하지 않은 경우는 변신할 수 없습니다.
		return;
	}

	if( pclchar->CanTransFormAttackType(pclinfo->m_siTransFormKind) == false)
	{
		// 공격 타입이 달라서 변신할 수 없습니다.
		return;
	}

	// 변신에 필요한 종량제 시스템 확인
	if( pclchar->pclCI->clBI.clTimeMeterRateInfo.GetLeftTime( TIMEMETERRATE_TRANSFORM ) <= 0)
	{
		// 변신에 필요한 시간이 모자랍니다. 시간을 충전해 주십시요.
		return;
	}

	// 변신에 따른 종량제 시간 시작
	if( pclchar->pclCI->clBI.clTimeMeterRateInfo.UseStart( TIMEMETERRATE_TRANSFORM ) == false)
	{
		return;
	}

	// 변신 설정
	pclchar->CharTransform( pclinfo->m_siTransFormKind ,pclchar->ActiveWeapon,pclItemList , pclskillinfo);

	// 타임 제한 설정
	pclchar->m_clCharUpdateTimer[CHAR_UPDATETIMER_TRANSFORM_TIME_LIMIT].SetActive(true, GetTickCount());

	sDBRequest_TransForm_Set clMsg( pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), pclchar->clTransFormInfo.uiNowTransFormKind, false );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRANSFORM_END(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_SetTransForm* pclinfo = (cltGameMsgRequest_SetTransForm*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltItem *pclItemList = pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
	cltPSkillInfo *pclskillinfo = &pclchar->pclCI->clCharSkill;
 
	// 데이터 검증
	if( pclinfo->m_siTransFormKind < 0 || pclinfo->m_siTransFormKind >= MAX_KIND_NUMBER )		return;
	if( pclKindInfoSet->pclKI[pclinfo->m_siTransFormKind] == NULL)								return;

	if( pclCM->IsAlive( id ) == false ) //죽으면 변신 할 수 없다.
	{
		//SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}

	// 변신 중이 아니라면 리턴
	if( pclchar->clTransFormInfo.bTransFormMode == false )				return;

	cltTimeMeterRate* pclTimeMeterRate = pclchar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(TIMEMETERRATE_TRANSFORM);
	if(pclTimeMeterRate == NULL)										return;

	// 타임 제한 체크
	if( pclchar->m_clCharUpdateTimer[CHAR_UPDATETIMER_TRANSFORM_TIME_LIMIT].IsActivated() )
	{
		if( pclchar->m_clCharUpdateTimer[CHAR_UPDATETIMER_TRANSFORM_TIME_LIMIT].IsTimed(GetTickCount(), false) == false )
		{
			cltMsg clMsg( GAMEMSG_RESPONSE_TRANSFORM_LIMIT_TIME, NULL, NULL );
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
			return;
		}
	}

	if( pclTimeMeterRate->IsUse() )
	{
		// DB에 사용시간 차감을 보냄
		sDBRequest_TimeMeterRate_UseTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_TRANSFORM, pclTimeMeterRate->siUseTimeSec, true );
		SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

		// DB에 변신 시간을 추가해준다.
		sDBRequest_Transform_AddTime clMsg1(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), pclchar->clTransFormInfo.uiNowTransFormKind, pclTimeMeterRate->siUseTimeSec );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);

		// 사용 종료
		pclchar->pclCI->clBI.clTimeMeterRateInfo.UseEnd( TIMEMETERRATE_TRANSFORM );
	}

	// 변신 해제	
	pclchar->CharTransform( 0 ,pclchar->ActiveWeapon,pclItemList,pclskillinfo);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRANSFORM_USEITEM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_UseTransFormItem* pclinfo = (cltGameMsgRequest_UseTransFormItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// 데이터 검증
	//if( pclchar->clTransFormInfo.bTransFormMode == true ) // 변신 상태면 리턴. - 문제가 없을까?
	//	return;

	SI32 pos1 = -1;

	if ( pclchar->pclCI->clCharItem.GetItemNum(pclinfo->siItemUnique) <= 0) //해당 아이템이 없다.
	{
		// 클라이언트로 서버의 응답값을 보낸다. 
		SendServerResponseMsg(0, SRVAL_FAIL_NOTRANSFROMITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	
	}

	pos1 = pclchar->pclCI->clCharItem.GetItemPos(pclinfo->siItemUnique); //아이템 위치 선정.
	if( pos1 < 0 )
		return ;

	cltItem clitem;
	clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos1]);
	clitem.SetItemNum(1);

	if( pclinfo->siItemUnique == ITEMUNIQUE(5410) ||
		pclinfo->siItemUnique == ITEMUNIQUE(5411) ||
		pclinfo->siItemUnique == ITEMUNIQUE(5412) ) // 변신 시간 증가 아이템이다. - 종량제.
	{
		SI32 siAddTime = 0;
		
		// [추가 : 황진성 2008. 1. 16 => 국내 군주는 변신 충전시간 변경.]
		if( pclClient->IsWhereServiceArea( ConstServiceArea_Korea | ConstServiceArea_English | ConstServiceArea_Taiwan | ConstServiceArea_USA | ConstServiceArea_NHNChina | ConstServiceArea_EUROPE) ) 
		{
			if( pclinfo->siItemUnique == ITEMUNIQUE(5410) )
			{
				siAddTime = 12 * 60 * 60;		// 12시간
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5411) )
			{
				siAddTime = 48 * 60 * 60;		// 48 시간
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5412) )
			{
				siAddTime = 96 * 60 * 60;		// 96시간
			}
		}
		else
		{
			if( pclinfo->siItemUnique == ITEMUNIQUE(5410) )
			{
				siAddTime = 86400;		// 1 일
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5411) )
			{
				siAddTime = 604800;		// 7 일
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5412) )
			{
				siAddTime = 2592000;	// 30 일
			}
		}
		
		if(siAddTime <= 0)			return;

		// DB에 저장한다. 
		sDBRequest_TimeMeterRate_AddTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_TRANSFORM, siAddTime, &clitem, pos1);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}
	else
	{
		UI16 uTransFormChar = 0;

		uTransFormChar = pclchar->GetCharKindFromItemUnique(pclinfo->siItemUnique);
		if( uTransFormChar <= 0 || uTransFormChar >= MAX_KIND_NUMBER )
			return;

		if( pclClient->pclKindInfoSet->pclKI[uTransFormChar]->IsAtb( ATB_TRANSFORM )  == false )
			return;

		//KHY - 0124 - 가챠레어- 닌자 변신 아이템.
		SI32 AddTime = 0;
		switch(pclinfo->siItemUnique)
		{
			case ITEMUNIQUE(13612):
			case ITEMUNIQUE(13613):
				AddTime = 10800;  // 기본 3시간이다. -  
				break;
			case ITEMUNIQUE(13615):
			case ITEMUNIQUE(13616):
			case ITEMUNIQUE(13623): // 고양이 스피릿 - 원거리
			case ITEMUNIQUE(13624): // 고양이 스피릿 - 근거리
			case ITEMUNIQUE(13626): // [진성] 호박상자. 할로윈 변신  - 근거리
			case ITEMUNIQUE(13627): // [진성] 호박상자. 할로윈 변신  - 원거리
			case ITEMUNIQUE(13633): // 크리스마스 근거리변신
			case ITEMUNIQUE(13632): // 크리스마스 원거리변신
			case ITEMUNIQUE(13641): // 검사스피릿 - 근거리
			case ITEMUNIQUE(13642): // 거너스피릿 - 원거리
			case ITEMUNIQUE(13652): // 요정스피릿(남) - 근거리 ; 유니크 추가되면 변경할 예정.
			case ITEMUNIQUE(13653): // 요정스피릿(여) - 원거리 ; 유니크 추가되면 변경할 예정.
			// 가챠 - 12월 스피릿 상자	눈의 여왕 사스콰치
			case ITEMUNIQUE(13657 ): // 눈의 여왕
			case ITEMUNIQUE(13656 ): // 사스콰치
				AddTime = 864000;   // 기본 10일이다.
				break;
		}

		// 캐릭터 등록여부 확인.
		if(uTransFormChar > 0)
		{
			if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true)
			{
				// 클라이언트로 서버의 응답값을 보낸다. 
				//SendServerResponseMsg(0, SRVAL_FAIL_ALEADYTRANSFROMCHR,  0, 0, pclCM->CR[id]->GetCharUnique());
				//return; //이미등록된 캐릭터다.
				// DB에 저장한다. 

				// 이미 등록된 캐리릭터인 경우 시간만 늘려준다.
				sDBRequest_TimeMeterRate_AddTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_TRANSFORM, AddTime, &clitem, pos1);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				return; //이미등록된 캐릭터다.
			}
		}


		// DB로 알린다. - 캐릭터 셋팅.		
		sDBRequest_Transform_AddChar clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), uTransFormChar, &clitem, pos1, TIMEMETERRATE_TRANSFORM, AddTime);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return ;
}

//KHY - 1111 - 오토바이 추가.
void cltServer::DoMsg_GAMEMSG_REQUEST_OILLING_USEITEM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_UseOillingItem* pclinfo = (cltGameMsgRequest_UseOillingItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 pos1 = -1;

	if ( pclchar->pclCI->clCharItem.GetItemNum(pclinfo->siItemUnique) <= 0) //해당 아이템이 없다.
	{
		// 클라이언트로 서버의 응답값을 보낸다.  - 
		//SendServerResponseMsg(0, SRVAL_FAIL_NOTRANSFROMITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	
	}

	pos1 = pclchar->pclCI->clCharItem.GetItemPos(pclinfo->siItemUnique); //아이템 위치 선정.
	if( pos1 < 0 )
		return ;

	cltItem clitem;
	clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos1]);
	clitem.SetItemNum(1);

	if( pclinfo->siItemUnique == ITEMUNIQUE(13631) ) // 휘발유.
	{
		SI32 siAddTime = 0;
		
		siAddTime = 200 * 60;		// 200 분
		
		if(siAddTime <= 0)			return;

		// DB에 저장한다. 
		sDBRequest_TimeMeterRate_AddTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_MOTORCYCLE, siAddTime, &clitem, pos1);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return ;
}


// [진성] 영웅의 동상 이벤트 버프룰렛 돌릴때 사용하는 패킷. => 2008-6-10
void cltServer::DoMsg_GAMEMSG_REQUEST_BUFF_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_Buff_Roulette* pclInfo = (cltGameMsgRequest_Buff_Roulette*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 CompleteBuffKind = 0;
	// 클라에서 룰렛을 돌리므로 해당 버프를 준다.
	if(false == pclInfo->m_bAction)
	{
		if(pclInfo->m_Money > pclchar->pclCI->clIP.GetMoney())
		{
			return;
		}

		// 전체 버프의 번호 배열.
		SI32 BuffKindArray[BUF_END];		
		ZeroMemory(BuffKindArray, sizeof(BuffKindArray));
		
		// 버프의 번호가 나올 확률 배열.
		SI32 BuffKindArrayRate[BUF_END];	
		ZeroMemory(BuffKindArrayRate, sizeof(BuffKindArrayRate));

		//KHY - 1113 - 크리스마스 이벤트 - 크리스마스용 버프 및 아이템 설정.
		if( pclEventTimeManager->InEventTime("ChristmasEvent", &sTime) )
		{
			BuffKindArray[0]		= BUF_ATTACKUP;					// 전투력 증가
			BuffKindArrayRate[0]	= 780;
			BuffKindArray[1]  		= BUF_DEFENSEUP;				// 방어력 증가.
			BuffKindArrayRate[1]	= 780;
			BuffKindArray[2]  		= BUF_MAKEEXPUP;				// 제조 경험치 증가.
			BuffKindArrayRate[2]	= 380;
			BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// 선공 방지 효과.
			BuffKindArrayRate[3]	= 500;
			BuffKindArray[4]  		= BUF_SUMMONATACUP;				// 소환수 강화. 
			BuffKindArrayRate[4]	= 750;
			BuffKindArray[5]  		= BUF_LOVEPOWER;				// 사랑 버프		
			BuffKindArrayRate[5]	= 150;
			BuffKindArray[6]  		= BUF_FRIENDSHIP;				// 우정 버프
			BuffKindArrayRate[6]	= 150;
			BuffKindArray[7]  		= BUF_HINAMOCHI;				// 레인보우 케익크 효과.
			BuffKindArrayRate[7]	= 80;
			BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// 아이템 제조 100% 성공.
			BuffKindArrayRate[8]	= 620;
			BuffKindArray[9] 		= BUF_FOURLEAF;					// 네잎클로버 - 아이템 드랍률 2배.
			BuffKindArrayRate[9]	= 60;
			BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// 경험치 150% 획득.
			BuffKindArrayRate[10]	= 250;
			BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// 배가 안고프고 내장기관이 - 되지 않는다,
			BuffKindArrayRate[11]	= 500;
			BuffKindArray[12]		= ITEMUNIQUE(13002);		// 크리스마스 양말. - 버프공간이지만 그냥 쓰자. - 버프맥스 안넘어가게 주의 
			BuffKindArrayRate[12]	= 50;			
		}
		else
		{
			BuffKindArray[0]		= BUF_ATTACKUP;					// 전투력 증가
			BuffKindArrayRate[0]	= 860;
			BuffKindArray[1]  		= BUF_DEFENSEUP;				// 방어력 증가.
			BuffKindArrayRate[1]	= 860;
			//BuffKindArray[2]  		= BUF_SPEEDUP;					// 스피드가 증가
			//BuffKindArrayRate[2]	= 900;
			BuffKindArray[2]  		= BUF_MAKEEXPUP;				// 제조 경험치 증가.
			BuffKindArrayRate[2]	= 350;
			BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// 선공 방지 효과.
			BuffKindArrayRate[3]	= 550;
			BuffKindArray[4]  		= BUF_SUMMONATACUP;				// 소환수 강화. 
			BuffKindArrayRate[4]	= 710;
			BuffKindArray[5]  		= BUF_LOVEPOWER;				// 사랑 버프		
			BuffKindArrayRate[5]	= 150;
			BuffKindArray[6]  		= BUF_FRIENDSHIP;				// 우정 버프
			BuffKindArrayRate[6]	= 200;
			BuffKindArray[7]  		= BUF_HINAMOCHI;				// 레인보우 케익크 효과.
			BuffKindArrayRate[7]	= 150;
			BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// 아이템 제조 100% 성공.
			BuffKindArrayRate[8]	= 700;
			BuffKindArray[9] 		= BUF_FOURLEAF;					// 네잎클로버 - 아이템 드랍률 2배.
			BuffKindArrayRate[9]	= 70;
			BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// 경험치 150% 획득.
			BuffKindArrayRate[10]	= 300;
			BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// 배가 안고프고 내장기관이 - 되지 않는다,
			BuffKindArrayRate[11]	= 600;
		}
		
		SI32 TotalRate = 0;

		// 세팅된 버프의 번호 배열.
		SI32 SetBuffKindArray[BUF_END];		
		ZeroMemory(SetBuffKindArray, sizeof(SetBuffKindArray));
		SI32 SetBuffKindArrayRate[BUF_END];		
		ZeroMemory(SetBuffKindArrayRate, sizeof(SetBuffKindArrayRate));
		SI32 SetBuffNum = 0; 
		for(SI32 Count = 0; Count < BUF_END; ++Count)	
		{
			if(0 >= BuffKindArray[Count])
				break;

			// 이미 사용중인 버프는 뺀다.
			if(true == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BuffKindArray[Count]))
				continue;

			SetBuffKindArray[SetBuffNum]	 = BuffKindArray[Count];
			SetBuffKindArrayRate[SetBuffNum] = BuffKindArrayRate[Count];
			SetBuffNum++;
			
			if(BUF_END < SetBuffNum)
				break;

			TotalRate += BuffKindArrayRate[Count];
		}
 
		if( 0 >= SetBuffNum )	return;
		if( 0 >= TotalRate  )	return;
		
		cltUniqueRange SetBuffKind[BUF_END];
		ZeroMemory(SetBuffKind, sizeof(SetBuffKind));
		for(SI32 Count = 0; Count < SetBuffNum; ++Count)	
		{
			SetBuffKind[Count].siUnique  = SetBuffKindArray[Count];
			SetBuffKind[Count].siPercent = (SetBuffKindArrayRate[Count] * 1000 / TotalRate);
		}
				
		CompleteBuffKind = GetUniqueWithRange( SetBuffKind, SetBuffNum, 1000);
		
		if(0 == CompleteBuffKind)
		{
			CompleteBuffKind = SetBuffKind[rand()%SetBuffNum].siUnique;
		}
	}
	
	pclchar->bBuffRouletteSwitch = pclInfo->m_bAction;

	cltGameMsgResponse_Buff_Roulette	Roulette(pclInfo->m_bAction, pclchar->GetCharUnique(), CompleteBuffKind);
	cltMsg clMsg( GAMEMSG_RESPONSE_BUFF_ROULETTE, sizeof(Roulette), (BYTE*)&Roulette );
	pclchar->SendNeighbourMsg(&clMsg, true);  

	// 버프룰렛이 종료되고 버프가 결정되어서 버프를 세팅한다.
	if(false == pclInfo->m_bAction && -1 < pclInfo->m_BuffKind)
	{
		SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		if ( siPersonID <= 0 ) 
			return ;

		// 현재 DB와 버프관련 통신 중이면, 처리하지 않는다.
		if( pclchar->IsNowAddBufThroughDB() == true )			return;

		// 돈이 부족해서 사용할 수 없다.
		if( TABS(pclInfo->m_Money) > pclCM->CR[id]->pclCI->clIP.GetMoney() )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY, 0, 0, pclchar->GetCharUnique() );
			return;
		}

		SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48분간사용
		
		SI16 siPercent = 0; //타입에 따라 설정.

		switch(CompleteBuffKind)
		{
			case BUF_MAKEEXPUP:
				{
					siPercent = 50;
				}
				break;
			case BUF_ATTACKUP:
			case BUF_DEFENSEUP:
			case BUF_SUMMONATACUP:	
				{
					siPercent = 20;
				}
				break;
			case BUF_PREMIUMEXPUP:
			case BUF_NOFIRSTATTACK:						
			case BUF_SUCCESS_MANUFACTURE:
			case BUF_FOURLEAF:
				{
					siPercent = 0;						
				}
				break;
		}
		
		//[진성] 버프룰렛을 사용하여 돈 관련 정보가 있으면 돈을 뺀다.
		sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BUFF_ROULETTE, pclInfo->m_Money);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		// 버프룰렛을 이용하여 지급한 금액의 통계.
		pclDelMoneyStatistics->Add(DELMONEY_BUFF_ROULETTE, pclInfo->m_Money);

		// 이전에 룰렛으로 얻은 버프가 있으면 삭제.
		//KHY - 1113 - 크리스마스 이벤트 - 크리스마스용 버프 및 아이템 설정.
		if( pclEventTimeManager->InEventTime("ChristmasEvent", &sTime) )
		{
			if(CompleteBuffKind ==ITEMUNIQUE(13002)) // 아이템에 당첨 되었다.
			{
				// 아이템 유니크 체크
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( CompleteBuffKind );
				if(ref < 0) return;

				// 아이템 지급
				if(  pclchar->GiveItem(CompleteBuffKind, 1, INPUTITEMPERSON_OPTION_CHRISTMAS_ROULETTE, 0) == false )
				{
					// 클라이언트로 서버의 응답값을 보낸다. 
					SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
					return ;
				}
				
				cltItem clItem;			
				SI16 brareswitch = 0;
				if( pclItemManager->MakeRandItemUnique(CompleteBuffKind, &clItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, 0) )
				{
					/*
					// 명품 알림 공지를 사용하여 아이템 획득을 알린다.
					cltGameMsgResponse_RareItemMade	clinfo((TCHAR*)(pclchar->GetName()), pclchar->pclCI->GetPersonID(), 
															&clItem,
															RARAITEM_NOTICE_SWITCH_CHRISTMASEVENT,
															0);

					if(pclchar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
					{
						cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMMADE, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
					}
					*/
				}

			}
			else  // 버프다.
			{
				SI16 index = -1;
				index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_BUFROULETTE);
				if ( index > -1 )
				{
					stBuf DelBuf(pclCM->CR[id]->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, BUF_GET_TYPE_BUFROULETTE);
					sDBRequest_DeleteBuf clMsg( siPersonID, index, &DelBuf );
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
				else
				{
					// 새로운 버프적용 할 빈 인덱스 얻기.
					index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclInfo->m_BuffKind, false );		
				}

				
				if ( index > -1 )
				{
					// 버프를 준다.
					stBuf addBuf(CompleteBuffKind, siPercent, usetime, BUF_GET_TYPE_BUFROULETTE);
					((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, pclInfo->m_Money);
				}
			}
		}
		else
		{
			SI16 index = -1;
			index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_BUFROULETTE);
			if ( index > -1 )
			{
				stBuf DelBuf(pclCM->CR[id]->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, BUF_GET_TYPE_BUFROULETTE);
				sDBRequest_DeleteBuf clMsg( siPersonID, index, &DelBuf );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
			else
			{
				// 새로운 버프적용 할 빈 인덱스 얻기.
				index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclInfo->m_BuffKind, false );		
			}

			
			if ( index > -1 )
			{
				stBuf addBuf(CompleteBuffKind, siPercent, usetime, BUF_GET_TYPE_BUFROULETTE);
				((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, pclInfo->m_Money);
			}
		}
	}
}


//	[종호_BALANCECURRENCY]
void cltServer::DoMsg_GAMEMSG_REQUEST_BALANCECURRENCY_BUFF(cltMsg* pclMsg,SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_BalanceCurrency_Buff* pclInfo = (cltGameMsgRequest_BalanceCurrency_Buff*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 CompleteBuffKind = 0;
	// 클라에서 룰렛을 돌리므로 해당 버프를 준다.
	if(false == pclInfo->m_bAction)
	{
		if(pclInfo->m_Money > pclchar->pclCI->clIP.GetMoney())
		{
			return;
		}

		// 전체 버프의 번호 배열.
		SI32 BuffKindArray[BUF_END];		
		ZeroMemory(BuffKindArray, sizeof(BuffKindArray));

		// 버프의 번호가 나올 확률 배열.
		SI32 BuffKindArrayRate[BUF_END];	
		ZeroMemory(BuffKindArrayRate, sizeof(BuffKindArrayRate));

		BuffKindArray[0]		= BUF_ATTACKUP;					// 전투력 증가
		BuffKindArrayRate[0]	= 860;
		BuffKindArray[1]  		= BUF_DEFENSEUP;				// 방어력 증가.
		BuffKindArrayRate[1]	= 860;
		//BuffKindArray[2]  		= BUF_SPEEDUP;					// 스피드가 증가
		//BuffKindArrayRate[2]	= 900;
		BuffKindArray[2]  		= BUF_MAKEEXPUP;				// 제조 경험치 증가.
		BuffKindArrayRate[2]	= 350;
		BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// 선공 방지 효과.
		BuffKindArrayRate[3]	= 550;
		BuffKindArray[4]  		= BUF_SUMMONATACUP;				// 소환수 강화. 
		BuffKindArrayRate[4]	= 710;
		BuffKindArray[5]  		= BUF_LOVEPOWER;				// 사랑 버프		
		BuffKindArrayRate[5]	= 150;
		BuffKindArray[6]  		= BUF_FRIENDSHIP;				// 우정 버프
		BuffKindArrayRate[6]	= 200;
		BuffKindArray[7]  		= BUF_HINAMOCHI;				// 레인보우 케익크 효과.
		BuffKindArrayRate[7]	= 150;
		BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// 아이템 제조 100% 성공.
		BuffKindArrayRate[8]	= 700;
		BuffKindArray[9] 		= BUF_FOURLEAF;					// 네잎클로버 - 아이템 드랍률 2배.
		BuffKindArrayRate[9]	= 70;
		BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// 경험치 150% 획득.
		BuffKindArrayRate[10]	= 300;
		BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// 배가 안고프고 내장기관이 - 되지 않는다,
		BuffKindArrayRate[11]	= 600;

		SI32 TotalRate = 0;

		// 세팅된 버프의 번호 배열.
		SI32 SetBuffKindArray[BUF_END];		
		ZeroMemory(SetBuffKindArray, sizeof(SetBuffKindArray));
		SI32 SetBuffKindArrayRate[BUF_END];		
		ZeroMemory(SetBuffKindArrayRate, sizeof(SetBuffKindArrayRate));
		SI32 SetBuffNum = 0; 
		for(SI32 Count = 0; Count < BUF_END; ++Count)	
		{
			if(0 >= BuffKindArray[Count])
				break;

			// 이미 사용중인 버프는 뺀다.
			if(true == pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BuffKindArray[Count]))
				continue;

			SetBuffKindArray[SetBuffNum]	 = BuffKindArray[Count];
			SetBuffKindArrayRate[SetBuffNum] = BuffKindArrayRate[Count];
			SetBuffNum++;

			if(BUF_END < SetBuffNum)
				break;

			TotalRate += BuffKindArrayRate[Count];
		}

		if( 0 >= SetBuffNum )	return;
		if( 0 >= TotalRate  )	return;

		cltUniqueRange SetBuffKind[BUF_END];
		ZeroMemory(SetBuffKind, sizeof(SetBuffKind));
		for(SI32 Count = 0; Count < SetBuffNum; ++Count)	
		{
			SetBuffKind[Count].siUnique  = SetBuffKindArray[Count];
			SetBuffKind[Count].siPercent = (SetBuffKindArrayRate[Count] * 1000 / TotalRate);
		}

		CompleteBuffKind = GetUniqueWithRange( SetBuffKind, SetBuffNum, 1000);

		if(0 == CompleteBuffKind)
		{
			CompleteBuffKind = SetBuffKind[rand()%SetBuffNum].siUnique;
		}
	}

	pclchar->bBuffRouletteSwitch = pclInfo->m_bAction;

	//	[종호_BALANCECURRENCY] Client로부터 요청온 통화량조절NPC 사용전에 사용가능통화량 응답
	cltGameMsgResponse_BalanceCurrency_Buff	Roulette(pclInfo->m_bAction, pclchar->GetCharUnique(), CompleteBuffKind);
	cltMsg clMsg( GAMEMSG_RESPONSE_BALANCECURRENCY_BUFF, sizeof(Roulette), (BYTE*)&Roulette );
	pclchar->SendNeighbourMsg(&clMsg, true);  

	// 버프룰렛이 종료되고 버프가 결정되어서 버프를 세팅한다.
	if(false == pclInfo->m_bAction && -1 < pclInfo->m_BuffKind)
	{
		SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		if ( siPersonID <= 0 ) 
			return ;

		// 현재 DB와 버프관련 통신 중이면, 처리하지 않는다.
		if( pclchar->IsNowAddBufThroughDB() == true )			return;

		// 돈이 부족해서 사용할 수 없다.
		if( TABS(pclInfo->m_Money) > pclCM->CR[id]->pclCI->clIP.GetMoney() )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY, 0, 0, pclchar->GetCharUnique() );
			return;
		}

		SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48분간사용

		SI16 siPercent = 0; //타입에 따라 설정.

		switch(CompleteBuffKind)
		{
		case BUF_MAKEEXPUP:
			{
				siPercent = 50;
			}
			break;
		case BUF_ATTACKUP:
		case BUF_DEFENSEUP:
		case BUF_SUMMONATACUP:	
			{
				siPercent = 20;
			}
			break;
		case BUF_PREMIUMEXPUP:
		case BUF_NOFIRSTATTACK:						
		case BUF_SUCCESS_MANUFACTURE:
		case BUF_FOURLEAF:
			{
				siPercent = 0;						
			}
			break;
		}

		// 버프룰렛을 사용하여 돈 관련 정보가 있으면 돈을 뺀다.
		sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BUFF_ROULETTE, pclInfo->m_Money);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		
		//	통화량흡수 NPC에게 흡수된 Money 로그 남김
		pclDelMoneyStatistics->Add(DELMONEY_BALANCECURRENCY, pclInfo->m_Money);

		SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_BALANCECURRENCY, 
								LOGCOMMAND_INDEX_BALANCECURRENCY, 
								0, 
								(cltCharServer*)pclchar, 
								NULL, 
								0, 
								pclInfo->m_Money, 
								0, 
								NULL, 
								0, 
								0, 
								0, 
								0, 
								0,
								NULL, 
								0, 
								0, 
								0,
								NULL, 
								NULL,
								NULL,
								NULL);



		//[종호] 통화량 조절 - 사용가능 통화량 저장
		GMONEY siMoney = m_pclBalanceCurrencyMgr->GetCanUseMoney() + pclInfo->m_Money;
		sDBRequest_SetBalanceCanUseCurrency clMsg2(siMoney, id);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);

	
		// 버프룰렛을 이용하여 지급한 금액의 통계.
		pclDelMoneyStatistics->Add(DELMONEY_BUFF_ROULETTE, pclInfo->m_Money);



		// 이전에 룰렛으로 얻은 버프가 있으면 삭제.

		SI16 index = -1;
		index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_BUFROULETTE);
		if ( index > -1 )
		{
			stBuf DelBuf(pclCM->CR[id]->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, BUF_GET_TYPE_BUFROULETTE);
			sDBRequest_DeleteBuf clMsg( siPersonID, index, &DelBuf );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		else
		{
			// 새로운 버프적용 할 빈 인덱스 얻기.
			index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclInfo->m_BuffKind, false );		
		}


		if ( index > -1 )
		{
			stBuf addBuf(CompleteBuffKind, siPercent, usetime, BUF_GET_TYPE_BUFROULETTE);
			((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, pclInfo->m_Money);
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_START(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_MissionQuest_Start* pclInfo = (cltGameMsgRequest_MissionQuest_Start*)pclMsg->cData;

	// 캐릭터 확인
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;
	
	//  미션퀘스트가 늘어나면 여기를 죄다 수정 .
	// 캐릭터가 가지고 있는 퀘스트 정보를 확인한다.
	// 캐릭터가 가지고 있는 퀘스트정보가 이상한 경우에는 정보를 삭제한다.
	if( (pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique > 0 || pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique > 0) &&
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique != pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique )
	{
		// 이상정보는 로그로 기록한다.
		pclLog->FilePrint("Config\\QuestError.log", "Name[%s], Mission1QuestUnique[%d, %d]", pclchar->GetName(),
							pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique,
							pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique );

		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();
	}

	// 현재 진행하고 있는 미션을 취소하고 하셔야 합니다.
	if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique > 0)
	{
		if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestStep == QUEST_STEP_MIDDLE )
			return;
	}

	// 미션 퀘스트 생성
	if( pclchar->MakeMissionQuest(pclInfo->m_siMissionUnique) == false )				return;

	cltGameMsgResponse_MissionQuest_Start clMissionQuest_Start( pclInfo->m_siMissionUnique, &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
	cltMsg clMsg(GAMEMSG_RESPONSE_MISSIONQUEST_START, sizeof(cltGameMsgResponse_MissionQuest_Start), (BYTE*)&clMissionQuest_Start );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_MissionQuest_Accept* pclInfo = (cltGameMsgRequest_MissionQuest_Accept*)pclMsg->cData;

	// 캐릭터 확인
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;
    
	// 현재 설정된 미션퀘스트와 요청된 퀘스트가 같은 것인지 확인
	if( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique != pclInfo->m_siMissionUnique )						return;

	switch ( pclInfo->m_siMissionUnique )
	{
	case MISSIONQUEST_UNIQUE_HOLLOWEEN:
		{
			pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique	= MISSIONQUEST_UNIQUE_HOLLOWEEN;
		}
		break;
	case MISSIONQUEST_UNIQUE_REMOVE_UNLUCK:
		{
			pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique	= MISSIONQUEST_UNIQUE_REMOVE_UNLUCK;
		}
		break;
	}

	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestCmd			= pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag;
	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestStep		= QUEST_STEP_MIDDLE;

	// 미션 퀘스트 정보를 DB에 저장한다.
	sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

	// 퀘스트 상태를 DB에 저장한다.
	sDBRequest_SetQuestInfo clQuestInfo(pclchar->pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

	// 클라이언트에 퀘스트의 상태를 통보한다. 
	pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_CANCEL(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_MissionQuest_Cancel* pclInfo = (cltGameMsgRequest_MissionQuest_Cancel*)pclMsg->cData;

	// 캐릭터 확인
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;

	// 현재 설정된 미션퀘스트와 요청된 퀘스트가 같은 것인지 확인
	if( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique != pclInfo->m_siMissionUnique )						return;
	//if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique != pclInfo->m_siMissionUnique )	return;

	// 설정된 퀘스트 초기화
	if ( MISSIONQUEST_UNIQUE_HOLLOWEEN == pclInfo->m_siMissionUnique )
	{
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

		// 미션 퀘스트 정보를 DB에 저장한다.
		sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
		pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

		// 퀘스트 상태를 DB에 저장한다.
		sDBRequest_SetQuestInfo clQuestInfo(pclchar->pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
		pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

		// 클라이언트에 퀘스트의 상태를 통보한다. 
		pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
	}
	// clMissionQuestInfo의 내용을 원래 가지고 있던 미션 정보로 복구 한다.
	else if ( MISSIONQUEST_UNIQUE_REMOVE_UNLUCK == pclInfo->m_siMissionUnique )
	{
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		
		// 퀘스트의 종료 조건을 구한다. 
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique								=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag		=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestCmd;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestPara1;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestPara2;

		// 미션 완료 제한 시간을 설정한다
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 50000 );	// 시간제한 없음 임의로 설정.

		// 보상을 구한다. 
		cltQuestRewardInfo clrewardinfo;
		clrewardinfo.bDeBuff = true;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set( &clrewardinfo );
	}
}

//보물찾기 이벤트 
void cltServer::DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_KILLNPC(cltMsg* pclMsg, SI32 id )
{
	cltServer* pclserver = (cltServer*)pclClient;
	// 이 메세지가 오면 해당 ID의 npc를 죽이고 아이템을 준다.
	// 그리고 다시 새로운 놈 하나를 세운다.
	cltGameMsgRequest_TreasureEvent_Npc_Kill* pclInfo = (cltGameMsgRequest_TreasureEvent_Npc_Kill*)pclMsg->cData;
	SI32 siEventNPC_ID_FromClient = pclInfo->m_siNPC_CharUnique	;
	cltCharServer* pclChar = pclCM->GetCharServer( siEventNPC_ID_FromClient)	;
	if ( pclChar == NULL	 )	return	;
	// 아이템을 준다 해당 유저에게

	SI32 siRewardItem		=	ITEMUNIQUE( 13347)	;
	SI32 siRewardItemNum	=	1	;

	cltCharServer* pCharServer = pclCM->GetCharServer( id );
	if(GIVEITEM_RESULT_SUCCESS == pCharServer->GiveItem(siRewardItem, siRewardItemNum, INPUTITEMPERSON_OPTION_TREASUREEVENTITEM, 0))
	{
		pclClient->pclLog->FilePrint(	TEXT("Config\\TreasureEventGiveItem.log"), 
			"Name = %s, ItemUnique = %d, ItemNum = %d", 
			pCharServer->pclCI->clBI.GetName(), siRewardItemNum,	siRewardItemNum
			);
	}
	// 죽여 버리라고 날린다.
	cltGameMsgResponse_IncLife clInfo(pclChar->GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_TIMEOUT);
	cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNeighbourMsg(&clMsg, true);

	pclChar->SetLife(0);
	pclserver->Write_Kill_NPC_Num(pclChar->GetMapIndex())	;// 사라진걸 기억한다.

}
void cltServer::DoMsg_GAMEMSG_REQUEST_CHAR_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	SI16		siCharKind[31];
	SI16		siPercent[31];
	SI32		siCharRouletteCount = 0;

	cltGameMsgRequest_Char_Roulette* pclInfo = (cltGameMsgRequest_Char_Roulette*)pclMsg->cData;

	// 캐릭터 확인
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;

	switch( pclInfo->m_siBufRoulette )
	{
	case CHAR_ROULETTE_START:
		{
			SI32 siCurKind = 0;
			if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
			{
				stBuf* pclBuf = pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
				if(pclBuf)
				{
					siCurKind = pclBuf->siPercent;
				}
			}

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RACCOON");
			siPercent[siCharRouletteCount] = 500;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RABBIT");
			siPercent[siCharRouletteCount] = 500;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MUSHROOM");
			siPercent[siCharRouletteCount] = 500;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RAT");
			siPercent[siCharRouletteCount] = 500;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MONKEYSON");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RACCOONDOG");
			siPercent[siCharRouletteCount] = 300;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_TURTLE");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_CATFISH");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_LADYBUG");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_BLUEFLY");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GARGOYLE");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MARIONETTE");
			siPercent[siCharRouletteCount] = 300;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_WEREWOLF");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_DEVILOUS");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GANGSI");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_EVILEYE");
			siPercent[siCharRouletteCount] = 300;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_FRUITBROS");
			siPercent[siCharRouletteCount] = 400;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_HARPY");
			siPercent[siCharRouletteCount] = 300;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_WILDCAT");
			siPercent[siCharRouletteCount] = 300;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GOLDBEETLE");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MANDRAGORA");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_FROZENQUEEN");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_OTOHIME");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_CERBERUS");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			// PCK : 변신 몬스터 5종 추가 (09.08.07)
			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_EMPERORPORTER");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GREATWALLSLIME");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GREATWALLSOUL");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_DRAKEFLY");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MANTISRAPTOR");
			siPercent[siCharRouletteCount] = 200;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			// 할로윈 망토 삭제
			// PCK - 망토 획득 확률 1% -> 0.5%으로 수정 (09.08.06)
			siCharKind[siCharRouletteCount] = ITEMUNIQUE(18528);
			siPercent[siCharRouletteCount] = 50;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(18529);
			siPercent[siCharRouletteCount] = 50;
			siCharRouletteCount++;

			SI32 siTotalPercent = 0;
			SI32 i;

			for(i=0; i<siCharRouletteCount; i++)
			{
				siTotalPercent += siPercent[i];
			}

			SI32 siRand = rand() % siTotalPercent;
			SI32 siSelected = -1;
			siTotalPercent = 0;
			for(i=0; i<siCharRouletteCount; i++)
			{
				siTotalPercent += siPercent[i];		
				if( siRand < siTotalPercent )
				{
					siSelected = i;
					break;
				}
			}

			pclchar->siCharRouletteValue = siCharKind[siSelected];

			cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_START, pclchar->siCharRouletteValue, siCharKind, siCharRouletteCount);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
		break;

	case CHAR_ROULETTE_ADDBUF:
		{
			// 지정된 카인드가 아니면 취소된다.
			if( pclInfo->m_siRequestKind != pclchar->siCharRouletteValue )
			{
				cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_END, 0, NULL, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
				pclchar->SendNeighbourMsg(&clMsg, true);

				return;
			}

			// 현재 DB와 버프관련 통신 중이면, 처리하지 않는다.
			if( pclchar->IsNowAddBufThroughDB() == true )			return;

			// 사용금액 계산
			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			GMONEY siPrice = 0;

			// 춘기 : 일본의 경우는 할로윈 룰렛돌리는 금액을 다르게 정한다.
			if(pclClient->IsWhereServiceArea(ConstServiceArea_Japan))
			{
				if		(npcrate < 100)		{		siPrice = -15000;	}
				else if	(npcrate < 300)		{		siPrice = -30000;	}
				else if	(npcrate < 700)		{		siPrice = -50000;	}
				else if	(npcrate < 1000)	{		siPrice = -100000;	}
				else if	(npcrate < 1450)	{		siPrice = -180000;	}
				else if	(npcrate < 1750)	{		siPrice = -290000;	}
				else if	(npcrate < 2050)	{		siPrice = -420000;	}
				else if	(npcrate < 2350)	{		siPrice = -580000;	}
				else if	(npcrate < 3000)	{		siPrice = -780000;	}

				// KHY - 1021 - NPCRate 값 확대.
				else if	(npcrate < 4000)	{		siPrice = -1000000;	}
				else if	(npcrate < 5500)	{		siPrice = -1300000;	}
				else if	(npcrate < 8500)	{		siPrice = -1800000;	}
				else if	(npcrate < 14500)	{		siPrice = -2500000;	}
				else if	(npcrate < 25500)	{		siPrice = -4000000;	}
				else if	(npcrate < 33500)	{		siPrice = -5800000;	}
				else						{		siPrice = -8500000;	}
			}
			else
			{
				if		(npcrate < 100)		{		siPrice = -150000;	}
				else if	(npcrate < 300)		{		siPrice = -300000;	}
				else if	(npcrate < 700)		{		siPrice = -500000;	}
				else if	(npcrate < 1000)	{		siPrice = -1000000;	}
				else if	(npcrate < 1450)	{		siPrice = -1800000;	}
				else if	(npcrate < 1750)	{		siPrice = -2900000;	}
				else if	(npcrate < 2050)	{		siPrice = -4200000;	}
				else if	(npcrate < 2350)	{		siPrice = -5800000;	}
				else if	(npcrate < 3000)	{		siPrice = -7800000;	}

				// KHY - 1021 - NPCRate 값 확대.
				else if	(npcrate < 4000)	{		siPrice = -10000000;	}
				else if	(npcrate < 5500)	{		siPrice = -13000000;	}
				else if	(npcrate < 8500)	{		siPrice = -18000000;	}
				else if	(npcrate < 14500)	{		siPrice = -25000000;	}
				else if	(npcrate < 25500)	{		siPrice = -40000000;	}
				else if	(npcrate < 33500)	{		siPrice = -58000000;	}
				else						{		siPrice = -85000000;	}
			}

			// 아무 마을이나 가입되어 있으면, 정상가격
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				// 룰렛을 돌리고 있는 마을과 가입된 마을이 같다면, 0.7배 가격
				if( pclchar->GetMapIndex() == pclchar->pclCI->clBI.siHomeVillage)
				{
					siPrice *= 0.7;
				}
			}
			else
			{
				// 마을에 가입조차 되어있지 않으면 1.5배 가격
				siPrice *= 1.5;
			}

			// [춘기] 체크조건 다시 수정 - 촛대가 있으면 돈의 유무에 상관없이 촛대를 소모해서 돌린다.
			bool	bHaveTicket = false;

			// 촛대가 있다면
			if(pclInfo->b_bUseTicketItem == true)
			{
				// 실제 촛대가 있는지, 있다면 100개 이상 가지고 있는지 체크

				for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
				{
					if (pclchar->pclCI->clCharItem.clItem[i].siUnique == ITEMUNIQUE(13049)
						 && pclchar->pclCI->clCharItem.clItem[i].siItemNum >= 100)
					{	
						bHaveTicket = true;
						break;
					}					
				}

				if(bHaveTicket == false)	return;		
			}
			// 촛대가 없다면
			else 
			{
				// 조건 수정 : 실제 내가 돈을 가지고 있는지 여부 확인
				// 내가 가지고 있는 금액이 없다면 리턴.
				if(siPrice > pclchar->pclCI->clIP.GetMoney() || (pclchar->pclCI->clIP.GetMoney() + siPrice) < 0 || pclchar->pclCI->clIP.GetMoney() == 0)
				{
					 return;
				}
					
			}

			bool bGiveItem = false;
			if( pclInfo->m_siRequestKind > 10000 )			bGiveItem = true;

			// 데이터 유효성 체크
			if( bGiveItem )
			{
				// 아이템 유니크 체크
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclInfo->m_siRequestKind );
				if(ref < 0)																					return;
			}
			else
			{
				// 변신 캐릭터 카인드 체크
				if( pclClient->pclKindInfoSet->IsValidKind( pclInfo->m_siRequestKind ) == false )			return;
			}

			SI16 index = -1;
			index = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_TRANSFORM);
			if ( index > -1 )
			{
				// 기존에 걸려있는 버프를 삭제한다.
				stBuf DelBuf(pclchar->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0);
				sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index, &DelBuf );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}

			if( bGiveItem )
			{
				// 아이템 지급
				if(  pclchar->GiveItem(pclInfo->m_siRequestKind, 1, INPUTITEMPERSON_OPTION_CHAR_ROULETTE, 7) == false )
				{
					// 클라이언트로 서버의 응답값을 보낸다. 
					SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
					return ;
				}
			}
			else
			{
				if( index < 0 )
				{
					// 새로운 버프 지급
					index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_TRANSFORM, false );		
				}

				if ( index > -1 )
				{
					SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48분간사용

					stBuf addBuf(BUF_TRANSFORM, pclchar->siCharRouletteValue, usetime, 0);
					((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
				}
			}

			// PCK : 촛대 아이템이 있는지 확인하고 있으면 소모시킨다. (소지금액보다 먼저 처리)

			if(pclInfo->b_bUseTicketItem) // 유저에 선택에 따라 다르다.
			{
				for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
				{
					if (pclchar->pclCI->clCharItem.clItem[i].siUnique == ITEMUNIQUE(13049)
						&& pclchar->pclCI->clCharItem.clItem[i].siItemNum >= 100)
					{	
						cltItem	clItem;
						clItem.Set(&pclchar->pclCI->clCharItem.clItem[i]);
						clItem.SetItemNum(100);

						sDBRequest_UseItem clMsg1( id, pclchar->pclCI->GetPersonID(), i, &clItem, USEITEM_REASON_TICKET);
						pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg1);
						break;
					}					
				}
			}
			else
			{
				//[강형] 캐릭터변신룰렛을 사용하여 돈 관련 정보가 있으면 돈을 뺀다.
				sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_CHAR_ROULETTE, siPrice);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				// 버프룰렛을 이용하여 지급한 금액의 통계.
				pclDelMoneyStatistics->Add(DELMONEY_CHAR_ROULETTE, siPrice);
			}

			// 초기화
			pclchar->siCharRouletteValue = 0;

			cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_END, 0, NULL, 0);
			cltMsg clCharRouletteMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
			pclchar->SendNeighbourMsg(&clCharRouletteMsg, true);

			if( bGiveItem )
			{
				cltItem clItem;			
				SI16 bRareSwitch = 0;
				if( pclItemManager->MakeRandItemUnique(pclInfo->m_siRequestKind, &clItem, 0, 0, &bRareSwitch, 0, 0, 0, 0, 0, 7) )
				{
					// 명품 알림 공지를 사용하여 아이템 획득을 알린다.
					cltGameMsgResponse_RareItemMade	clinfo((TCHAR*)(pclchar->GetName()), pclchar->pclCI->GetPersonID(), 
															&clItem,
															RARAITEM_NOTICE_SWITCH_HALLOWEENMANTLE,
															0);

					if(pclchar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
					{
						cltMsg clMsg(GAMEMSG_RESPONSE_RAREITEMMADE, sizeof(clinfo), (BYTE*)&clinfo);
						pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
					}
				}
			}
		}
		break;

	case CHAR_ROULETTE_END:
		{
			// 초기화
			pclchar->siCharRouletteValue = 0;

			cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_END, 0, NULL, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
		break;
	}
}
// NEW PVP - 손성웅 2008.10.08
void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_FILED(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_PVP_Request* pclInfo = (cltGameMsgRequest_PVP_Request*)pclMsg->cData;
	 if ( pclClient->IsCountrySwitch(Switch_IKillU) ==	false )				return	;
	switch( pclInfo->siRequestType)
	{
	case REQUEST_PVP :// PVP를 요청 했다.
		{
			SI32 siMyId		=	id	;					// 내 ID
			SI32 siEnermyId =	pclInfo->siPara1	;	// 공격할 적의 케릭터 유니크
			// 캐릭터 확인
			if( pclCM->IsValidID( siMyId ) == false )			return;
			if( pclCM->IsValidID( siEnermyId ) == false )		return;	//pvp를 할 대상의 ID확인.
			// 살아있음을 확인
			if( pclCM->IsAlive( siMyId ) == false )			return;
			if( pclCM->IsAlive( siEnermyId ) == false )		return;	//pvp를 할 대상의 ID확인.

			cltCharServer* pclmychar = pclCM->GetCharServer(siMyId);			if(pclmychar == NULL)			return;
			cltCharServer* pclEnemychar = pclCM->GetCharServer(siEnermyId);		if(pclEnemychar == NULL)		return;
			//. 엔펠리스에서는 신청 불가능 
			if( pclmychar->GetMapIndex() == MAPINDEX_PALACE || pclEnemychar->GetMapIndex() == MAPINDEX_PALACE )	return	;
			// 라쿤 피하기 이벤트 맵이면 불간,ㅇ 
			if( pclmychar->GetMapIndex() == MAPINDEX_FESTIVAL || pclEnemychar->GetMapIndex() == MAPINDEX_FESTIVAL )	return	;
			// 둘중 하나라도 pk맵이면 신청불가능
			if ( pclMapManager->IsPkMap(pclmychar->GetMapIndex()) == true )										return	;
			if ( pclMapManager->IsPkMap(pclEnemychar->GetMapIndex()) == true )									return	;
			if (pclmychar->bPersonalShopSwitch	==	 true ) return	;;
			if (pclmychar->bPremiumPersonalShop	==	 true ) return	;
			if (pclEnemychar->bPersonalShopSwitch	==	 true ) return	;
			if (pclEnemychar->bPremiumPersonalShop	==	 true ) return	;
			/*if ( pclClient->pclMapManager->IsCanMarketOpenMap( pclmychar->GetMapIndex() ) == true ||
				pclClient->pclMapManager->IsCanMarketOpenMap( pclEnemychar->GetMapIndex() ) == true )			return ;*/
			// 이벤트 맵타일 위라면 신청 불가능
			cltMapCommon* pclMymap		=	pclMapManager->GetMapPointer(	pclmychar->GetMapIndex()	)	;
			cltMapCommon* pclEnemymap	=	pclMapManager->GetMapPointer(	pclEnemychar->GetMapIndex()	)	;
			if ( pclMymap != NULL && pclmychar->GetMapIndex() == MAPINDEX_MAINFIELD ) 
			{
				SI32 siColl = pclMymap->CalcCollInfo( pclmychar->GetX(), pclmychar->GetY())	;
				if( siColl & BLOCK_EVENT4 )								return	;
			}
			if ( pclEnemymap != NULL && pclEnemychar->GetMapIndex() == MAPINDEX_MAINFIELD ) 
			{
				SI32 siColl = pclEnemymap->CalcCollInfo( pclEnemychar->GetX(), pclEnemychar->GetY())	;
				if( siColl & BLOCK_EVENT4 )								return	;
			}
			if ( pclmychar->GetMapIndex() == MAPINDEX_PVPMAP	|| pclEnemychar->GetMapIndex() == MAPINDEX_PVPMAP) 
			{
				// 둘중 하나라도 pvp 맵이라면 신청 불가능 합니다
				return	;
			}
			bool bNowEnermyPVPsetting = pclCM->CR[ siEnermyId ]->pclCI->clCharOption.GetPVPMode() ;

			// 이미 전투대상이 있으면 애초에 대기를 할수 없다.
			if ( pclCM->CR[ siMyId ]->siEnemUnique >0 || pclCM->CR[ siEnermyId ]->siEnemUnique > 0 )		return	;

			if (  bNowEnermyPVPsetting == false )	// PVP를 거절 하지 않는다. 메뉴에는 PVP 모드 거절로 .
			{
				//	상대방에게 ok 할껀지 물어보는 창을 띄운다.
				cltGameMsgResponse_PVP_Request clResponsePvp( REQUEST_PVP , siMyId,0,(TCHAR*)pclCM->CR[id]->GetName() );
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clResponsePvp), (BYTE*)&clResponsePvp );
				pclEnemychar->SendNetMsg((sPacketHeader*)&clMsg);
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [로그추가 : 손서웅ㅇ 2008. 10. 29] // pvp 타겟에 요청
					// 타켓 personID 
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_REQUEST, 
						0, pclmychar,NULL , pclEnemychar->pclCI->GetPersonID(), 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						0, 0, 0, 0, 0, NULL, NULL);
				}
				// 서버에 남긴다.
				TCHAR fileNameBuffer[256];
				//슬롯에 찍을 시간을 텍스트로 완성한다.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPREQUEST \tRequestPerson : \t[%s]\t \tACCEPTPERSON : \t[%s]\t Time"),
					pclmychar->GetName(),pclEnemychar->GetName(),szBuffer0 );
			}
		}
		break;
	case REFUSE_PVP://상대방이 거절 상태 이다.
		{
			SI32 siRequestId			=	pclInfo->siPara1	;		// PVP 요청한 사람 ID
			SI32 siAcceptId				=	id	;						// PVP 요청을 거절 한사람

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// 허락한 사람이 정상적인 ID인가 확인
						
			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)		return;
			cltCharServer* pclRefuseChar = pclCM->GetCharServer(siAcceptId);			if(pclRefuseChar == NULL)		return;
			// 요청한 사람에게 거절 당했다는 메세지를 날려준다.
			cltGameMsgResponse_PVP_Request clAcceptToRequest( REFUSE_PVP ,siAcceptId,0,TEXT(""));
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
			pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg);
			{
				// 서버에 남긴다.
				TCHAR fileNameBuffer[256];
				//슬롯에 찍을 시간을 텍스트로 완성한다.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPREFUSE \tRequestPerson : \t[%s]\t \tACCEPTPERSON : \t[%s]\t Time"),
					pclRequestChar->GetName(),pclRefuseChar->GetName(),szBuffer0 );
			}
			
		}
		break;
	case READY_PVP:// 5초 대기 하기 위해서 대기 메세지를 날린다.
		{
			SI32 siRequestId			=	pclInfo->siPara1	;	// PVP 요청한 사람 ID
			SI32 siAcceptId				=	id	;						// PVP 요청을 받아서 ok 한 사람 ID

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// 허락한 사람이 정상적인 ID인가 확인

			// 살아 있음을 확인
			if( pclCM->IsAlive( siRequestId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsAlive( siAcceptId ) == false )		return;	// 허락한 사람이 정상적인 ID인가 확인

			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)		return	;
			cltCharServer* pclAcceptChar = pclCM->GetCharServer(siAcceptId);			if(pclAcceptChar == NULL)		return	;			
			
			// 이미 누구 하나라도 전투 시작 되면 시작된 사람이 있을시에는 보내지 않는다.
			if( pclRequestChar->siEnemUnique	>0 || pclAcceptChar->siEnemUnique >0 )									return	;
			if( pclRequestChar->GetMapIndex() == MAPINDEX_PALACE || pclAcceptChar->GetMapIndex() == MAPINDEX_PALACE)
			{
				cltGameMsgResponse_PVP_Request cltoAccept( ILLPLACE_PVP ,0,0,TEXT(""))	;
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(cltoAccept), (BYTE*)&cltoAccept )	;
				pclAcceptChar->SendNetMsg((sPacketHeader*)&clMsg)	;
				cltGameMsgResponse_PVP_Request clToRequest( ILLPLACE_PVP ,0,0,TEXT(""))	;
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clToRequest), (BYTE*)&clToRequest )	;
				pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg2)	;
			}
			else
			{
				pclCM->CR[ siRequestId ]->siPVPWaitRequestId	=	pclInfo->siPara1			;// PVP 요청한 사람 ID
				pclCM->CR[ siRequestId ]->siPVPWaitAcceptId		=	id			;// PVP 요청을 받아서 ok 한 사람 ID
				pclCM->CR[ siAcceptId ]->siPVPWaitRequestId	=	pclInfo->siPara1			;// PVP 요청한 사람 ID
				pclCM->CR[ siAcceptId ]->siPVPWaitAcceptId		=	id			;// PVP 요청을 받아서 ok 한 사람 ID

				// 각기 클라이언트로 알려준다.
				// 요청한 사람에게
				cltGameMsgResponse_PVP_Request clAcceptToRequest( READY_PVP ,0,0,TEXT(""));	// 각가 기다리라는 메세지를 날려준다 서버 시간을 날린다.
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
				pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg);
				//	승낙한 사람에게
				cltGameMsgResponse_PVP_Request clclAcceptToAccepeter( READY_PVP ,0,0,TEXT(""));// 기다리라는 메세지를 날려준다 서버시간을 날린다
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclAcceptToAccepeter), (BYTE*)&clclAcceptToAccepeter );
				pclAcceptChar->SendNetMsg((sPacketHeader*)&clMsg2);
			}
		}
		break;
	case START_PVP://pvp를 시작한다.
		{
			SI32 siRequestId			=	pclCM->CR[ id ]->siPVPWaitRequestId	;// PVP 요청한 사람 ID
			SI32 siAcceptId				=	pclCM->CR[ id ]->siPVPWaitAcceptId		;// PVP 요청을 받아서 ok 한 사람 ID			

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// 허락한 사람이 정상적인 ID인가 확인
			// 살아 있음을 확인
			if( pclCM->IsAlive( siRequestId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsAlive( siAcceptId ) == false )			return;	// 허락한 사람이 정상적인 ID인가 확인
			// 정상 아이디라면 현제 해당 케릭터가 PVP 리그의 매칭리스트에 존재 하는지 확인한다.
			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)	return	;
			cltCharServer* pclAcceptChar = pclCM->GetCharServer(siAcceptId);			if(pclAcceptChar == NULL)	return	;

			if ( pclCM->CR[ siRequestId ]->siEnemUnique >0 || pclCM->CR[ siAcceptId ]->siEnemUnique > 0 )			return	;
			// 같은 맵에 있지 않으면 실행되지 않도록 한다
			if( pclRequestChar->GetMapIndex() !=pclAcceptChar->GetMapIndex() )
			{
				{
					// 서버에 남긴다.
					TCHAR fileNameBuffer[256];
					//슬롯에 찍을 시간을 텍스트로 완성한다.
					TCHAR szTime[128];
					TCHAR szBuffer0[128];
					SYSTEMTIME stTimeInfo;
					GetLocalTime(&stTimeInfo);
					StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
					StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
					StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
						, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
					pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
						TEXT(" PVPWARPBEFORESTART \tRequestPerson : \t[%s]\t \tACCEPTPERSON : \t[%s]\t Time"),
						pclRequestChar->GetName(),pclAcceptChar->GetName(),szBuffer0 );
				}
				return	;
			}
			// 신청 한놈이나 신청 받은놈이 엔펠리스에 있으면 전투 불가능 
			if( pclRequestChar->GetMapIndex() == MAPINDEX_PALACE || pclAcceptChar->GetMapIndex() == MAPINDEX_PALACE )
			{
				pclRequestChar->siEnemUnique	=	0	;
				pclAcceptChar->siEnemUnique		=	0	;
				cltGameMsgResponse_PVP_Request cltoAccept( ILLPLACE_PVP ,0,0,TEXT(""))	;
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(cltoAccept), (BYTE*)&cltoAccept )	;
				pclAcceptChar->SendNetMsg((sPacketHeader*)&clMsg)	;
				cltGameMsgResponse_PVP_Request clToRequest( ILLPLACE_PVP ,0,0,TEXT(""))	;
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clToRequest), (BYTE*)&clToRequest )	;
				pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg2)	;
			}
			else
			{
				// PVP를 승낙 하였으므로 서로에게 서로의 ID를 기억해준다
				pclRequestChar->siEnemUnique	=	siAcceptId	;
				pclAcceptChar->siEnemUnique		=	siRequestId	;
				pclRequestChar->ParametaBoxAction()	;			
				pclAcceptChar->ParametaBoxAction();
				pclRequestChar->IncreaseLife( pclRequestChar->clPB.GetMaxLife() )	;
				pclAcceptChar->IncreaseLife( pclAcceptChar->clPB.GetMaxLife() )		;
				// 각기 클라이언트로 알려준다.
				// 요청한 사람에게
				cltGameMsgResponse_PVP_Request clAcceptToRequest( START_PVP , siAcceptId,siRequestId,TEXT("") );	// 요정한 사람에게는 승락한 사람 ID
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
				pclRequestChar->SendNeighbourMsg(&clMsg,true);
				//	승낙한 사람에게
				cltGameMsgResponse_PVP_Request clclAcceptToAccepeter( START_PVP , siRequestId,siAcceptId,TEXT("") );// 승락한 사람에게는 요청한 사람 ID
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclAcceptToAccepeter), (BYTE*)&clclAcceptToAccepeter );
				pclAcceptChar->SendNeighbourMsg(&clMsg2,true);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [로그추가 : 손서웅ㅇ 2008. 10. 29] // pvp 시작 
					// 타켓 personID 
					//pclRequestChar 는 신청한사람
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_START, 
						0, pclRequestChar,NULL, pclAcceptChar->pclCI->GetPersonID() , 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						0, 0, 0, 0, 0, NULL, NULL);
				}

				// 서버에 남긴다.
				TCHAR fileNameBuffer[256];
				//슬롯에 찍을 시간을 텍스트로 완성한다.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPSTART \tRequestPerson : \t[%s]\t \tACCEPTPERSON : \t[%s]\t Time"),
					pclRequestChar->GetName(),pclAcceptChar->GetName(),szBuffer0 );
			}
		}
		break;
	case LOSE_PVP://pvp의 패배 조건을 만족해서 졌다,
		{
			SI32 siWinnerId				=	pclInfo->siPara1	;	// PVP 승자
			SI32 siLoserId				=	id							;	// PVP 패자

			if( pclCM->IsValidID( siWinnerId ) == false )		return;	// 요청한 사람이 정상적인 ID인가 확인
			if( pclCM->IsValidID( siLoserId ) == false )		return;	// 허락한 사람이 정상적인 ID인가 확인

			SI32 siWinnerparent = pclCM->CR[siWinnerId]->GetSummonParentID()	;	// 승리자의 parentid
			SI32 siLoserParent = pclCM->CR[siLoserId]->GetSummonParentID()		;	// 패배자의 parentid

			if( siWinnerparent == 0 ) siWinnerparent = siWinnerId;
			if( siLoserParent == 0 ) siLoserParent = siLoserId;

			cltCharServer* pclWinnerChar = pclCM->GetCharServer(siWinnerparent);			if(pclWinnerChar == NULL)			return;
			cltCharServer* pclLoserChar = pclCM->GetCharServer(siLoserParent);				if(pclLoserChar == NULL)			return;

			// 승리자와 패배자의 상대방의 적 아이디를 초기화.
			pclWinnerChar->siEnemUnique		=	0		;
			pclLoserChar->siEnemUnique		=	-100	;

			// 각기 클라이언트로 알려준다.
			// 승리자
			//>SendNetMsg((sPacketHeader*),>SendNeighbourMsg(
			cltGameMsgResponse_PVP_Request clWinner( END_PVP , WIN_PVP, pclWinnerChar->GetCharUnique(), TEXT(""));	
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
			//pclWinnerChar->SendNetMsg((sPacketHeader*)&clMsg);
			pclWinnerChar->SendNeighbourMsg(&clMsg, true);

			pclWinnerChar->IncQuestPara( QUEST_CLEAR_COND_PVPWIN, 0, 1 );

			// 패배자
			cltGameMsgResponse_PVP_Request clclLoser( END_PVP , LOSE_PVP, pclLoserChar->GetCharUnique(), TEXT("") );
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclLoser), (BYTE*)&clclLoser );
			//pclLoserChar->SendNetMsg((sPacketHeader*)&clMsg2);
			pclLoserChar->SendNeighbourMsg(&clMsg2, true);
		}break;
	case DRAW_PVP:
		{
			if( pclCM->IsValidID( pclInfo->siPara1 ) == false )		return;	
			if( pclCM->IsValidID( id ) == false )		return;	

			SI32 siDrawparent1	=	pclCM->CR[pclInfo->siPara1]->GetSummonParentID()	;	
			SI32 siDrawparent2	=	pclCM->CR[id]->GetSummonParentID()							;	

			if( siDrawparent1 == 0 ) siDrawparent1 = pclInfo->siPara1;
			if( siDrawparent2 == 0 ) siDrawparent2 = id;

			cltCharServer* pclDrawChar1 = pclCM->GetCharServer(siDrawparent1);			if(pclDrawChar1 == NULL)			return;
			cltCharServer* pclDrawChar2 = pclCM->GetCharServer(siDrawparent2);			if(pclDrawChar2 == NULL)			return;

			if ( pclDrawChar1->siEnemUnique		==	0 )			return	;
			if ( pclDrawChar2->siEnemUnique		==	0 )			return	;

			// 비기고 끝났다.
			pclDrawChar1->siEnemUnique		=	0	;
			pclDrawChar2->siEnemUnique		=	0	;
			// 각기 클라이언트로 알려준다.
			{//승리자
				// 개인간 pvp가 끝나면서 각종 중독상태 제거
				pclDrawChar1->DeletePoison();						// 중독 상태를 삭제한다.
				pclDrawChar1->DeletePoisonSetItemEffect();			// 중독 상태를 삭제한다.
				pclDrawChar1->DeleteIce();							// 얼음 상태를 삭제한다.
				pclDrawChar1->DeleteCurseAttack();					// 공격력이 저하 상태를 삭제한다.
				pclDrawChar1->DeleteCurseCritical();				// Critical 확률이 낮아지는 상태를 삭제한다.
				pclDrawChar1->DeleteCurseDefense();					// 방어력이 낮아지는 상태를 삭제한다.
				pclDrawChar1->DeleteCurseMovespeed();				// 이동속도 저하 상태를 삭제한다.
				pclDrawChar1->DeleteMagicFire();					// 불에 타는 상태를 삭제한다.
				pclDrawChar1->DeleteFrozen();						// 보스 얼음 상태를 삭제한다.
				pclDrawChar1->DeleteCurseEffect();
			}
			{	// 패배자
				// 개인간 pvp가 끝나면서 각종 중독상태 제거
				pclDrawChar2->DeletePoison();						// 중독 상태를 삭제한다.
				pclDrawChar2->DeletePoisonSetItemEffect();			// 중독 상태를 삭제한다.
				pclDrawChar2->DeleteIce();							// 얼음 상태를 삭제한다.
				pclDrawChar2->DeleteCurseAttack();					// 공격력이 저하 상태를 삭제한다.
				pclDrawChar2->DeleteCurseCritical();				// Critical 확률이 낮아지는 상태를 삭제한다.
				pclDrawChar2->DeleteCurseDefense();					// 방어력이 낮아지는 상태를 삭제한다.
				pclDrawChar2->DeleteCurseMovespeed();				// 이동속도 저하 상태를 삭제한다.
				pclDrawChar2->DeleteMagicFire();					// 불에 타는 상태를 삭제한다.
				pclDrawChar2->DeleteFrozen();						// 보스 얼음 상태를 삭제한다.
				pclDrawChar2->DeleteCurseEffect();
			}
			cltGameMsgResponse_PVP_Request clDraw1( END_PVP , DRAW_PVP, pclDrawChar1->GetCharUnique() ,TEXT(""));	
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clDraw1), (BYTE*)&clDraw1 );
			pclDrawChar1->SendNeighbourMsg(&clMsg,true);
			// 패배자
			cltGameMsgResponse_PVP_Request clDraw2( END_PVP , DRAW_PVP, pclDrawChar2->GetCharUnique() ,TEXT(""));
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clDraw2), (BYTE*)&clDraw2 );
			pclDrawChar2->SendNeighbourMsg(&clMsg2,true);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [로그추가 : 손서웅ㅇ 2008. 10. 29] // pvp 비김
				// para1, para2 : 싸운 두사람의 personID
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_REQUEST, 
					0, pclDrawChar1 ,NULL , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					pclDrawChar1->pclCI->GetPersonID(), 
					pclDrawChar2->pclCI->GetPersonID(), 0, 0, 0, NULL, NULL);
			}
			{
				// 서버에 남긴다.
				TCHAR fileNameBuffer[256];
				//슬롯에 찍을 시간을 텍스트로 완성한다.
				TCHAR szTime[128];
				TCHAR szBuffer0[128];
				SYSTEMTIME stTimeInfo;
				GetLocalTime(&stTimeInfo);
				StringCchPrintf( szTime, sizeof(szTime) ,TEXT("%d:%d:%d:%d:%d"),stTimeInfo.wMonth,stTimeInfo.wDay,stTimeInfo.wHour,stTimeInfo.wMinute,stTimeInfo.wSecond);
				StringCchPrintf(szBuffer0, sizeof(szBuffer0),"%s",&szTime) ;
				StringCchPrintf( fileNameBuffer , sizeof(fileNameBuffer) , TEXT("Config\\PVPLog_%04d%02d%02d.log") 
					, stTimeInfo.wYear , stTimeInfo.wMonth , stTimeInfo.wDay );
				pclClient->pclLog->FilePrint(TEXT(fileNameBuffer), 
					TEXT(" PVPDRAW \tPerson1 : \t[%s]\t \t PERSON2 : \t[%s]\t Time"),
					pclDrawChar1->GetName(),pclDrawChar2->GetName(),szBuffer0 );
			}
		}
		break;

	}

}

// PVP_League 손성웅 2008.11.7
void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE(cltMsg* pclMsg,SI32 id)
{
}


void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_UI_INFOGET(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siGetPersonID	= pclchar->pclCI->GetPersonID();
	SI16 siGetPLGrade	= pclchar->GetPVP_LeagueGrade();


	//--
	// 디비로 정보를 요청하는 부분
	//-- 
	sDBRequest_PVP_League_UI_InfoGet clMsg( pclchar->pclCI->GetPersonID(), id );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_APPLY(cltMsg* pclMsg, SI32 id)
{
	// PVP 무한대전 경기 시간에만 할 수 있다
	if ( false == pclEventTimeManager->InEventTime( TEXT("PVP_LeagueReserve"), &sTime) )
	{
		return;
	}

	if ( NULL == pclPVP_LeagueMgr )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// 수감되어 있는 상태라면 이동이 안된다.
	if ( pclchar->clInnerStatus.IsStatus(INNERSTATUS_PRISON) )
	{
		return;
	}

	if ( pclchar->pclCI->clIP.GetLevel() < pclClient->GetGlobalValue("GV_PVPLeague_LimitLevel") )
	{
		return;
	}

	//--
	// 이곳에 실제 리스트에 등록하는 것을 넣으면된다
	SI32 siPersonID = pclchar->pclCI->GetPersonID();
	SI16 siGrade	= pclchar->GetPVP_LeagueGrade();
	if ( siGrade == PVP_LEAGUE_GRADE_NONE ) 
	{
		// 등급이 없을때에는 기본 설정 등급으로 변경 시킨다
		siGrade = Const_PVP_League_Default_Grade;

		sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  siPersonID , siGrade , sTime);
		pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	SI32 siResult	= pclPVP_LeagueMgr->AddReserveList( siPersonID, siGrade );
	SI32 siCount	= pclPVP_LeagueMgr->GetRerserveListCount();	// 로직상 현재 등록 인원이라고 봐도 무방하다
	//--

	if ( PVP_LEAGUE_APPLY_RESULT_SUCCESS == siResult )
	{
		pclchar->DoQuestCheckAndAction( QUEST_CLEAR_COND_PVPLEAGUERESERVE );
	}

	//--
	// 이곳은 결과값을 보내주는 부분
	SendServerResponseMsg( 0, SRVAL_PVP_LEAGUE_APPLY_MESSAGE, siResult, siCount, pclchar->GetCharUnique() );
	//--
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_CANCEL(cltMsg* pclMsg, SI32 id)
{
	// PVP 무한대전 경기 시간에만 할 수 있다
	if ( (false == pclEventTimeManager->InEventTime( TEXT("PVP_LeagueReserve"), &sTime))
		&& (false == pclEventTimeManager->InEventTime( TEXT("PVP_LeagueMatch"), &sTime))
		)
	{
		return;
	}

	if ( NULL == pclPVP_LeagueMgr )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	//--
	// 이곳에 실제 리스트에서 삭제하는 것을 넣으면 된다
	SI32 siPersonID = pclchar->pclCI->GetPersonID();

	pclPVP_LeagueMgr->SubReserveList( siPersonID );
	//--

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_AGAIN_RESERVE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PVP_League_Again_Reserve* pclInfo = (cltGameMsgRequest_PVP_League_Again_Reserve*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	// PVP 무한대전 예약 시간에만 할 수 있다
	if ( false == pclEventTimeManager->InEventTime( TEXT("PVP_LeagueReserve"), &sTime) )
	{
		return;
	}

	if ( NULL == pclPVP_LeagueMgr )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siPersonID = pclchar->pclCI->GetPersonID();

	pclPVP_LeagueMgr->AgainReserveList( siPersonID, pclInfo->m_bAnswer );

}


void cltServer::DoMsg_GAMEMSG_REQUEST_VILLAGE_RESIDENT_INVITE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Village_Resident_Invite* pclInfo = (cltGameMsgRequest_Village_Resident_Invite*)pclMsg->cData;

	cltCharServer* pclTeacherChar = pclCM->GetCharServer(id);		
	if(pclTeacherChar == NULL)	return;

	SI32 DisciplePersonID = pclCM->GetPersonIDFromName(pclInfo->m_kCharName);
	if( 0 >= DisciplePersonID)
	{
		SendServerResponseMsg( 0, SRVAL_VILLAGE_RESIDENT_INVITE, 0, 0, pclTeacherChar->GetCharUnique() );
		return;
	}

	SI32 DiscipleCharID			   = pclCM->GetIDFromPersonID(DisciplePersonID);
	cltCharServer* pclDiscipleChar = pclCM->GetCharServer(DiscipleCharID);		
	if(pclDiscipleChar == NULL)
	{
		SendServerResponseMsg( 0, SRVAL_VILLAGE_RESIDENT_INVITE, 0, 0, pclTeacherChar->GetCharUnique() );
		return;
	}

	if(  0 < pclDiscipleChar->pclCI->clBI.siHomeVillage )
	{
		SendServerResponseMsg( 0, SRVAL_VILLAGE_RESIDENT_INVITE, 0, 0, pclTeacherChar->GetCharUnique() );
		return;
	}

	if( 20 > pclDiscipleChar->pclCI->clIP.GetLevel() )
	{
		SendServerResponseMsg( 0, SRVAL_VILLAGE_RESIDENT_INVITE, 0, 0, pclTeacherChar->GetCharUnique() );
		return;
	}

	SendServerResponseMsg( 0, SRVAL_VILLAGE_RESIDENT_INVITE, 1, 0, pclCM->CR[id]->GetCharUnique() );


	cltGameMsgResponse_Village_Resident_Invite VillageResidentInvite( pclTeacherChar->pclCI->clBI.GetName(), pclTeacherChar->pclCI->clBI.siHomeVillage );
	cltMsg clMsg(GAMEMSG_RESPONSE_VILLAGE_RESIDENT_INVITE, sizeof(VillageResidentInvite), (BYTE*)&VillageResidentInvite );
	pclDiscipleChar->SendNetMsg((sPacketHeader*)&clMsg);
}
// 발렌타인데이 전쟁 답변 
void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_REQUEST(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_ValentineWar_Request* pclInfo = (cltGameMsgRequest_ValentineWar_Request*)pclMsg->cData;
	cltCharServer* pclChar = pclCM->GetCharServer( id)	;

	cltValentineWarInfo clvaletineinfo;
	switch( pclInfo->siCouple) 
	{
	case VALENTINEWAR_NONE : // 난 대답하기 싫다
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_NONE )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
			//셋팅 된것을 디비로 날린다.
		}
		break;
	case VALENTINEWAR_COUPLE :	// 난 커플이다	
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_COUPLE )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
		}
		break;
	case VALENTINEWAR_SOLO :	// 난 솔로다.
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_SOLO )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
		}
		break;
	}
	// 일단 막아 두고~바로 디비에서 받은거를 날려야지.
	sDBRequest_Valantine_Request clMsg( pclChar->pclCI->GetPersonID(), clvaletineinfo );
	pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
}
// 케릭터 정보를 받는다.
void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_INFOGET(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineWar_Info_get* pclInfo = (cltGameRequest_ValentineWar_Info_get*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer( id)	;
	// [성웅] 발렌타인 데이 정보 요청
	sDBRequest_Valantine_Info_Get clValantineInfo( pclChar->pclCI->GetPersonID() );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clValantineInfo);

}
void cltServer::DoMsg_GAMEMSG_REQUEST_DIVINATION_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	SI16		siCharKind[50];
	SI16		siPercent[50];
	SI32		siCharRouletteCount = 0;

	cltGameMsgRequest_Divination_Roulette* pclInfo = (cltGameMsgRequest_Divination_Roulette*)pclMsg->cData;

	// 캐릭터 확인
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;

	switch( pclInfo->m_siDivinationRoulette )
	{
	case DIVINATION_ROULETTE_START:
		{
			SI32 siCurKind = 0;

			//if(pclchar->pclCI->clBI.clBufInfo.IsHaveBuf(BUF_TRANSFORM))
			//{
			//	stBuf* pclBuf = pclchar->pclCI->clBI.clBufInfo.GetBuf(BUF_TRANSFORM);
			//	if(pclBuf)
			//	{
			//		siCurKind = pclBuf->siPercent;
			//	}
			//}
			
			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RACCOON");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RABBIT");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MUSHROOM");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RAT");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MONKEYSON");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_RACCOONDOG");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_TURTLE");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_CATFISH");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_LADYBUG");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_BLUEFLY");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GARGOYLE");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MARIONETTE");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_WEREWOLF");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_DEVILOUS");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GANGSI");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_EVILEYE");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_FIRESTAR");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_FRUITBROS");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_HARPY");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_WILDCAT");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_GOLDBEETLE");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_MANDRAGORA");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_FROZENQUEEN");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_OTOHIME");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = pclClient->GetUniqueFromHash("KIND_CERBERUS");
			siPercent[siCharRouletteCount] = 20;
			if(siCharKind[siCharRouletteCount] > 0 && siCurKind != siCharKind[siCharRouletteCount])	siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(5350);
			siPercent[siCharRouletteCount] = 1;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(5365);
			siPercent[siCharRouletteCount] = 1;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(5360);
			siPercent[siCharRouletteCount] = 1;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(5355);
			siPercent[siCharRouletteCount] = 1;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = ITEMUNIQUE(3770);
			siPercent[siCharRouletteCount] = 160;
			siCharRouletteCount++;
			
			// [춘기] - 버프 추가

			siCharKind[siCharRouletteCount] = BUF_PREMIUMEXPUP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;
			
			siCharKind[siCharRouletteCount] = BUF_ATTACKUP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_DEFENSEUP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_MAKEEXPUP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_NOFIRSTATTACK;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_SUCCESS_MANUFACTURE;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_FOURLEAF;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_LOVEPOWER;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_FRIENDSHIP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_HINAMOCHI;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

			siCharKind[siCharRouletteCount] = BUF_SUMMONATACUP;
			siPercent[siCharRouletteCount] = 30;
			siCharRouletteCount++;

//-------------------------------------------------------

			SI32 siTotalPercent = 0;
			SI32 i;

			for(i=0; i<siCharRouletteCount; i++)
			{
				siTotalPercent += siPercent[i];
			}

			SI32 siRand = rand() % siTotalPercent;
			SI32 siSelected = -1;
			siTotalPercent = 0;
			for(i=0; i<siCharRouletteCount; i++)
			{
				siTotalPercent += siPercent[i];		
				if( siRand < siTotalPercent )
				{
					siSelected = i;
					break;
				}
			}

			pclchar->siDivinationValue = siCharKind[siSelected];

			SI32 siBufKind = 0;

			if(siSelected < 25)		siBufKind = BUFKIND_CHAR;
			else if(siSelected < 30)	siBufKind = BUFKIND_ITEM;
			else siBufKind = BUFKIND_BUF;

			cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_START, pclchar->siDivinationValue, siCharKind, siCharRouletteCount, siBufKind);
			cltMsg clMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
		break;

	case DIVINATION_ROULETTE_ADDBUF:
		{
			// 지정된 카인드가 아니면 취소된다.
			if( pclInfo->m_siRequestDivination != pclchar->siDivinationValue )
			{
				cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_END, 0, NULL, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
				pclchar->SendNeighbourMsg(&clMsg, true);

				return;
			}

			// 현재 DB와 버프관련 통신 중이면, 처리하지 않는다.
			if( pclchar->IsNowAddBufThroughDB() == true )			return;

			// 사용금액 계산
			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			SI64 siPrice = 0;

			// 사용요금 계산
			if		(npcrate < 100)		{		siPrice = -500000;	}
			else if	(npcrate < 300)		{		siPrice = -1000000;	}
			else if	(npcrate < 700)		{		siPrice = -1500000;	}
			else if	(npcrate < 1000)	{		siPrice = -2000000;	}
			else if (npcrate < 1450)    {		siPrice = -2500000;	}
			else if (npcrate < 1750)	{		siPrice = -3000000;	}
			else if	(npcrate < 2050)	{		siPrice = -3500000;	}
			else if (npcrate < 2350)	{		siPrice = -4000000;	}
			else if	(npcrate < 3000)	{		siPrice = -4500000;	}

			// KHY - 1021 - NPCRate 값 확대.
			else if	(npcrate < 4000)	{		siPrice = -5000000;	}
			else if	(npcrate < 5500)	{		siPrice = -7500000;	}
			else if	(npcrate < 8500)	{		siPrice = -12000000;	}
			else if	(npcrate < 14500)	{		siPrice = -20000000;	}
			else if	(npcrate < 25500)	{		siPrice = -38000000;	}
			else if	(npcrate < 33500)	{		siPrice = -50000000;	}
			else						{		siPrice = -70000000;	}

			//// 아무 마을이나 가입되어 있으면, 정상가격
			//if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			//{
			//	// 룰렛을 돌리고 있는 마을과 가입된 마을이 같다면, 0.7배 가격
			//	if( pclchar->GetMapIndex() == pclchar->pclCI->clBI.siHomeVillage)
			//	{
			//		siPrice *= 0.7;
			//	}
			//}
			//else
			//{
			//	// 마을에 가입조차 되어있지 않으면 1.5배 가격
			//	siPrice *= 1.5;
			//}

			if(siPrice > pclchar->pclCI->clIP.GetMoney())
			{
				// 돈이 없어서 버프를 받지 못한다.
				return;
			}

			//	춘기 : 버프타입에 따라서 처리한다.

			// 신년운세룰렛 버프가 걸려있으면 삭제를 한다.
			// 단 버프 타입이 아이템 지급이면 삭제하지 않는다.
			SI16 index = -1;			
			index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_NEWYEAREVENT);
			if ( index > -1 && pclInfo->m_siBufKind_Type != BUFKIND_ITEM)
			{
				// 기존에 걸려있는 버프를 삭제한다.
				stBuf DelBuf(pclchar->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0);
				sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index, &DelBuf );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}

			switch(pclInfo->m_siBufKind_Type)
			{
			case BUFKIND_CHAR:
				{
					// 변신 캐릭터 카인드 체크
					if( pclClient->pclKindInfoSet->IsValidKind( pclInfo->m_siRequestDivination ) == false )			return;

					if ( index < 0)
					{
						// 새로운 버프 지급
						index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_TRANSFORM, false );		
					}

					if ( index > -1 )
					{
						SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48분간사용

						stBuf addBuf(BUF_TRANSFORM, pclchar->siDivinationValue, usetime, BUF_GET_TYPE_NEWYEAREVENT);
						((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
					}
				}
				break;
			case BUFKIND_ITEM:
				{
					// 아이템 유니크 체크
					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclInfo->m_siRequestDivination );
					if(ref < 0)																	return;

					// 아이템 지급

					// 떡국의 경우에는 갯수를 1~5개 랜덤하게 준다.
					if(pclInfo->m_siRequestDivination == 3770)
					{
						SI32 siRand = 1+ (rand() % 4);

						if(  pclchar->GiveItem(pclInfo->m_siRequestDivination, siRand, INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE, 0) == false )
						{
							// 클라이언트로 서버의 응답값을 보낸다. 
							SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
							return ;
						}
					}
					else
					{
						if(  pclchar->GiveItem(pclInfo->m_siRequestDivination, 1, INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE, 0) == false )
						{
							// 클라이언트로 서버의 응답값을 보낸다. 
							SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
							return ;
						}
					}
				}
				break;
			case BUFKIND_BUF:
				{
					if ( index < 0)
					{
						// 새로운 버프 지급
						index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclchar->siDivinationValue, false );		
					}

					SI16 siPercent = 0; //타입에 따라 설정.

					switch(pclchar->siDivinationValue)
					{
					case BUF_MAKEEXPUP:
						{
							siPercent = 50;
						}
						break;
					case BUF_ATTACKUP:
					case BUF_DEFENSEUP:
					case BUF_SUMMONATACUP:	
						{
							siPercent = 20;
						}
						break;
					case BUF_PREMIUMEXPUP:
					case BUF_NOFIRSTATTACK:						
					case BUF_SUCCESS_MANUFACTURE:
					case BUF_FOURLEAF:
						{
							siPercent = 0;						
						}
						break;
					}

					if ( index > -1 )
					{
						SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48분간사용

						stBuf addBuf(pclchar->siDivinationValue, siPercent, usetime, BUF_GET_TYPE_NEWYEAREVENT);
						((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
					}
				}
				break;
			}


			// 운세메시지를 던진다.

			if(pclInfo->m_siBufKind_Type != 0)
			{
				SendServerResponseMsg(0, SRVAL_DIVINATION_MSG,  0, 0, pclCM->CR[id]->GetCharUnique());
			}

//-----------------------------------
			//[강형] 캐릭터변신룰렛을 사용하여 돈 관련 정보가 있으면 돈을 뺀다.
			sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_CHAR_ROULETTE, siPrice);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			// 버프룰렛을 이용하여 지급한 금액의 통계.
			pclDelMoneyStatistics->Add(DELMONEY_NEWYEAREVENT_ROULETTE, siPrice);

			// 초기화
			pclchar->siDivinationValue = 0;

			cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_END, 0, NULL, 0);
			cltMsg clDivinationRouletteMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
			pclchar->SendNeighbourMsg(&clDivinationRouletteMsg, true);
		}
		break;

	case DIVINATION_ROULETTE_END:
		{
			// 초기화
			pclchar->siDivinationValue = 0;

			cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_END, 0, NULL, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
		break;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROPOSE_QUESTION( cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_Propose_Question* pclInfo = (cltGameRequest_Propose_Question*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	// 대상 케릭터 이름이 없다면
	if ( 0 == _tcslen(pclInfo->m_szCharName) )
	{
		return;
	}
	
	// 전할 메시지가 없다면
	if ( 0 == _tcslen(pclInfo->m_szMessage) )
	{
		return;
	}

	cltCharServer* pclMyChar = pclCM->GetCharServer( id );
	if ( NULL == pclMyChar )
	{
		return;
	}

	// 이미 결혼을 했다면
	if ( TRUE == pclMyChar->IsMarried() )
	{
		return;
	}

	// 결혼을 할 수 있는 레벨이 아니라면
	if ( Const_Marriage_Min_Level > pclMyChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	// 가족 이용권이 없다면
	if ( 0 >= pclMyChar->pclCI->clCharItem.GetItemNum(Const_Family_Item_Unique) )
	{
		return;
	}

	// 프로포즈 상대자 캐릭터 ID를 가져온다
	SI32 siProposeID = pclCM->GetIDFromName(pclInfo->m_szCharName);

	// 현재 캐릭터가 존재하지 않거나 접속중이 아닐때
	cltCharServer* pclProposeChar = pclCM->GetCharServer( siProposeID );
	if ( NULL == pclProposeChar )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_IS_NOT_VALIDCHAR,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// 상대자가 이미 결혼을 했다면
	if ( TRUE == pclProposeChar->IsMarried() )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_ALREADY_MARRIED,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// 상대자가 결혼 가능 레벨이 아니라면
	if ( Const_Marriage_Min_Level > pclProposeChar->pclCI->clIP.GetLevel() )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_LESSTHAN_MARRY_LEVEL,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// 성별체크는 캐릭터 KIND로 체크한다
	SI32 siMyKind		= pclMyChar->GetKind();
	SI32 siProposeKind	= pclProposeChar->GetKind();

	bool bSexCheck		= false;

	switch ( siMyKind )
	{
	case KIND_HERO3:
	case KIND_HERO4:
		{
			if ( (KIND_HEROINE3 == siProposeKind) || (KIND_HEROINE4 == siProposeKind) )
			{
				bSexCheck = true;
			}
		}
		break;

	case KIND_HEROINE3:
	case KIND_HEROINE4:
		{
			if ( (KIND_HERO3 == siProposeKind) || (KIND_HERO4 == siProposeKind) )
			{
				bSexCheck = true;
			}
		}
		break;
	}

	if ( false == bSexCheck )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_SAME_SEX,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}
	
	// 청혼을 한다
	TCHAR szCharName[MAX_PLAYER_NAME]			= TEXT("");
	TCHAR szMessage[Const_Max_Propose_Message]	= TEXT("");

	StringCchCopy( szCharName,	sizeof(szCharName),	((TCHAR*)pclMyChar->GetName()) );
	StringCchCopy( szMessage,	sizeof(szMessage),	pclInfo->m_szMessage );

	// 전할 메시지에 필터 적용
    m_pCAbuseFilter->CheckAbuse( szMessage );

	// 패킷 보내기~
	cltGameResponse_Propose_Question clinfo( szCharName, szMessage );
	cltMsg clMsg(GAMEMSG_RESPONSE_PROPOSE_QUESTION, sizeof(clinfo), (BYTE*)&clinfo );
	pclProposeChar->SendNetMsg((sPacketHeader*)&clMsg);

	// 상대방에게 프로포즈한 퍼슨 아이디를 설정한다
	pclMyChar->SetProposePersonID( pclProposeChar->pclCI->GetPersonID() );
	pclProposeChar->SetProposePersonID( pclMyChar->pclCI->GetPersonID() );

	if ( IsWhereServiceArea(ConstSwitch_NewLog) ) 
	{
		SendLog_WriteLogToDB( LOGCOMMAND_TYPE_FAMILY , LOGCOMMAND_INDEX_FAMILY_PROPOSE, 
			0, pclMyChar, NULL, pclProposeChar->pclCI->GetPersonID(), 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, NULL, NULL);

	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROPOSE_ANSWER( cltMsg* pclMsg, SI32 id )
{
	cltGameRequest_Propose_Answer* pclInfo = (cltGameRequest_Propose_Answer*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclMyChar = pclCM->GetCharServer( id );
	if ( NULL == pclMyChar )
	{
		return;
	}

	// 청혼자 아이디를 구한다
	SI32 siProposerCharID = pclCM->GetIDFromPersonID( pclMyChar->GetProposePersonID() );

	cltCharServer* pclProposerChar = pclCM->GetCharServer( siProposerCharID );
	if ( NULL == pclProposerChar )
	{
		return;
	}

	// 혹시 모르니 각자 설정되어있는 청혼자 퍼슨 아이디를 비교한다
	if ( pclMyChar->GetProposePersonID() != pclProposerChar->pclCI->GetPersonID() )
	{
		return;
	}

	if ( pclProposerChar->GetProposePersonID() != pclMyChar->pclCI->GetPersonID() )
	{
		return;
	}

	// 프로포즈를 거절하였을 경우 상대방 캐릭터에게만 메시지를 날린다
	if ( false == pclInfo->m_bAccept )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_ANSWER_NO,  0, 0, pclProposerChar->GetCharUnique() );

		if ( IsWhereServiceArea(ConstSwitch_NewLog) ) 
		{
			SendLog_WriteLogToDB( LOGCOMMAND_TYPE_FAMILY , LOGCOMMAND_INDEX_FAMILY_PROPOSE_FAIL, 
				0, pclMyChar, NULL, pclProposerChar->pclCI->GetPersonID(), 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				0, 0, 0, 0, 0, NULL, NULL);

		}

		return;
	}

	// 결혼 체크
	if ( TRUE == pclMyChar->IsMarried() )
	{
		return;
	}

	if ( TRUE == pclProposerChar->IsMarried() )
	{
		return;
	}

	// 레벨 체크
	if ( Const_Marriage_Min_Level > pclMyChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	if ( Const_Marriage_Min_Level > pclProposerChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	// 성별 체크
	SI32 siMyKind		= pclMyChar->GetKind();
	SI32 siProposerKind	= pclProposerChar->GetKind();

	bool bSexCheck		= false;

	switch ( siMyKind )
	{
	case KIND_HERO3:
	case KIND_HERO4:
		{
			if ( (KIND_HEROINE3 == siProposerKind) || (KIND_HEROINE4 == siProposerKind) )
			{
				bSexCheck = true;
			}
		}
		break;

	case KIND_HEROINE3:
	case KIND_HEROINE4:
		{
			if ( (KIND_HERO3 == siProposerKind) || (KIND_HERO4 == siProposerKind) )
			{
				bSexCheck = true;
			}
		}
		break;
	}

	if ( false == bSexCheck )
	{
		return;
	}

	// 아이템 체크
	SI32 siMyItemPos		= pclMyChar->pclCI->clCharItem.FindItemInv( Const_Family_Item_Unique );
	SI32 siProposerItemPos	= pclProposerChar->pclCI->clCharItem.FindItemInv( Const_Family_Item_Unique );

	if ( (-1 >= siMyItemPos) || (-1 >= siProposerItemPos) )
	{
		return;
	}
	
	//=====================================================================
	// 자 결혼에 필요한 모든 조건을 충족했다 이제 결혼이다
	//=====================================================================

	// 결혼시 소모될 아이템
	cltItem clMyItem;
	
	clMyItem.Init();
	clMyItem.siUnique			= Const_Family_Item_Unique;
	clMyItem.siItemNum			= Const_Family_Item_Num;

	cltItem clProposerItem;

	clProposerItem.Init();
	clProposerItem.siUnique		= Const_Family_Item_Unique;
	clProposerItem.siItemNum	= Const_Family_Item_Num;

	// 결혼 기념일설정
	cltDate clWeddingDate;
	clWeddingDate.Set( &pclTime->clDate );

	// 실제 디비로 보낸다
	sDBRequest_Set_Marry clMsg( pclProposerChar->pclCI->GetPersonID(),	&clProposerItem,			siProposerItemPos,	// 청혼한사람
								pclMyChar->pclCI->GetPersonID(),		&clMyItem,					siMyItemPos,		// 청혼받은사람
								MARRIAGE_LOVE_LEVEL_01,					clWeddingDate.GetDateVary()						// 공용설정
								);																			

	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WEDDINGANNIVERSARY_ITEMGET( cltMsg* pclMsg, SI32 id )
{
	cltCharServer* pclMyChar = pclCM->GetCharServer( id ); 
	if ( NULL == pclMyChar )
	{
		return;
	}

	if ( 0 >= pclMyChar->pclCI->GetPersonID() )
	{
		return;
	}

	// 결혼도 안했는데 받기 요청한다면
	if ( FALSE == pclMyChar->IsMarried() )
	{
		return;
	}

	SI32 siNowDateVary = pclTime->clDate.GetDateVary();

	// 결혼 기념일이 아니라면
	if ( FALSE == pclMyChar->pclMarriage->IsWeddingAnniversary(siNowDateVary) )
	{
		return;
	}

	// 이미 결혼 기념일 아이템을 받았다면
	if ( TRUE == pclMyChar->pclMarriage->IsWeddingItemGet(siNowDateVary) )
	{
		return;
	}

	// 우선 DB다녀오기 전에 또 요청이 들어올수있으므로 설정해 주고
	pclMyChar->pclMarriage->SetItemGetDateVary( siNowDateVary );

	// 여기에서 바로 아이템을 지급한다
	pclMyChar->GiveItem( Const_WeddingAnniversary_Unique, Const_WeddingAnniversary_Num, INPUTITEMPERSON_OPTION_WEDDINGANNIVERSARY, 0 );

	// DB로 아이템 받은 정보를 보낸다
	sDBRequest_Marry_ItemGet_Set clMsg( pclMyChar->pclCI->GetPersonID(), siNowDateVary );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SKILLBOOK_BUYITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SkillBook_BuyItem* pclinfo = (cltGameMsgRequest_SkillBook_BuyItem*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL ) return;

	if( 0 >= pclinfo->m_clBuyItem.siUnique  || 0 >= pclinfo->m_clUseItem.siUnique ) return;

	if(		MAX_ITEM_PER_PERSON <= pclinfo->m_siInvenPos 
		||	0					>= pclinfo->m_siInvenPos )
	{
		return;
	}

	cltItem* pclInvenItem = &pclchar->pclCI->clCharItem.clItem[pclinfo->m_siInvenPos];
	if( NULL == pclInvenItem ) return;

	if(    pclinfo->m_clUseItem.siUnique   != pclInvenItem->siUnique  
		|| pclinfo->m_clUseItem.siItemNum  >  pclInvenItem->siItemNum )
	{
		return;
	}

	if( pclinfo->m_siGrade != pclItemManager->pclSkillBookManager->GetSkillBookGradeFromItemUnique( pclInvenItem->siUnique ) )
	{
		return;
	}

	if( pclchar->pclCI->clIP.GetMoney() < pclinfo->m_siUseMoney ) return;

	if( GIVEITEM_RESULT_SUCCESS == pclchar->GiveItem(	pclinfo->m_clBuyItem.siUnique, 
		pclinfo->m_clBuyItem.siItemNum, 
		INPUTITEMPERSON_OPTION_SKILLBOOK_BUY, 
		0 ) )
	{
		sDBRequest_UseItem useitem( id, pclchar->pclCI->GetPersonID(), pclinfo->m_siInvenPos, &pclinfo->m_clUseItem, USEITEM_REASON_DATEOVER );
		pclGameDBProcess->SendMsg( DBSELECT_BASE, (sPacketHeader *)&useitem );

		sDBRequest_ChangeMoney clMsg( id, pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_QUESTREWARD, -pclinfo->m_siUseMoney ); 
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SKILLBOOK_SUBMAGIC_DEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SkillBook_SubMagic_Del* pclinfo = (cltGameMsgRequest_SkillBook_SubMagic_Del*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if( pclchar == NULL ) return;

	if( 0 >= pclinfo->m_clAddSkillBookSubMagic.GetMagicKind() || 0 >= pclinfo->m_clAddSkillBookSubMagic.GetParentMagicKind() ) return;

	sDBRequest_SkillBook_SubMagic_Del	clMsg( pclchar->GetID(), pclchar->pclCI->GetPersonID(), &pclinfo->m_clAddSkillBookSubMagic, false );
	pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);	
}
//-------------------------------------------------------------------------------
//	메크로
//-------------------------------------------------------------------------------
void cltServer::DoMsg_GAMEMSG_RESPONSE_RECORD_ACTION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgResponse_RecordAction*	pclinfo	=	( cltGameMsgResponse_RecordAction* )pclMsg->cData;
	SI32								adminid;	

	if( pclCM->IsAlive( id ) == FALSE )														return;	

	if( ( adminid = pclCM->GetIDFromPersonID( pclinfo->siAdminPersonID ) ) == 0 )			return;

	if( pclCM->IsValidID( adminid ) == FALSE )												return;


	if( pclinfo->bReportedByAdminCommand == TRUE )
	{	
		// 운영자 명령어에 의한 신고이다.

		switch( pclinfo->siResult )
		{
		case 0:

			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_ERROR_UNKNOWN, 0, 0, adminid );

			// 알 수 없는 오류

			break;
		case 1:

			// 성공

			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_SUCCESS, 0, 0, adminid );

			break;

		case 2:

			// 현재 기록중
			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_ALREADY_ORDERED, 0, 0, adminid );

			break;	
		}
	}
	else
	{
		// 게임내 허용된 권한을 가진 캐릭터(군주, 형조판서, 포교)에 의한 신고이다.

		switch( pclinfo->siResult )
		{
		case 1:

			// 성공

			m_pclMacroReportedMgr->OnUserReported( ( ( cltCharServer* )pclCM->CR[ id ] )->pclCI->GetPersonID() );

			//SendServerResponseMsg( 0, SRVAL_REPORTMACRO_SUCCESS, 0, 0, adminid );

			pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "매크로 사용자 신고 [신고자:%s][피신고자:%s] : 성공", pclCM->CR[ adminid ]->GetName(),  ( ( cltCharServer* )pclCM->CR[ id ] )->GetName() );

			break;
		case 2:

			// 현재 기록중
			//SendServerResponseMsg( 0, SRVAL_REPORTMACRO_WORKING, 0, 0, adminid );

			pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "매크로 사용자 신고 [신고자:%s][피신고자:%s] : 현재 기록중", pclCM->CR[ adminid ]->GetName(),  ( ( cltCharServer* )pclCM->CR[ id ] )->GetName() );

			break;
		}	
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RECORD_ACTION_FINISHED( cltMsg* pclMsg, SI32 id )
{ 	
	cltGameMsgRequest_RecordActionFinished	*pclinfo	=	( cltGameMsgRequest_RecordActionFinished* )pclMsg->cData;
	CHAR	szcharname[ MAX_PLAYER_NAME ] = "";



	if( pclCM->IsAlive( id ) == FALSE )														return;

	if( pclCM->IsValidID(id) == FALSE )														return;


	strncpy( szcharname, pclCM->CR[ id ]->GetName(), MAX_PLAYER_NAME );

	if( pclinfo->bReportedByAdminCommand == TRUE )
	{
		SI32 adminid;

		if( ( adminid = pclCM->GetIDFromPersonID( pclinfo->siAdminPersonID ) ) == 0 )			return;

		if( pclCM->IsValidID( adminid ) == FALSE )												return;	


		// 운영자 명령어에 의한 신고이다. 기록 내용은 파일로 존재한다.
		// 운영자에게 직접 수집하도록 전달한다.

		cltGameMsgResponse_RecordActionFinished		clinfo( szcharname, pclinfo->szFilePath );
		cltMsg msg( GAMEMSG_RESPONSE_RECORD_ACTION_FINISHED, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[ adminid ]->SendNetMsg((sPacketHeader*)&msg );
	}
	else
	{
		// 게임내 허용된 권한을 가진 캐릭터(군주, 형조판서, 포교)에 의한 신고이다.
		// 기록 내용은 메모리에 존재한다.
		// 서버에서 수집하도록 한다.

		cltGameMsgGZFTPProtocol::__initialize_data	data;

		data.siyourPersonID		=	0;
		data.siotherPersonID	=	pclCM->CR[ id ]->pclCI->GetPersonID();

		strncpy( data.szSenderName, szcharname, sizeof( data.szSenderName ) - 1 );		

		strncpy( data.szFilePath, pclinfo->szFilePath, sizeof( data.szFilePath ) - 1 );

		data.boption_delete		=	TRUE;

		cltGameMsgGZFTPProtocol	clinfo(	cltGameMsgGZFTPProtocol::GZFTP_INITIALIZE, 
			0,
			pclCM->CR[ id ]->pclCI->GetPersonID(),
			( BYTE* )&data, sizeof( data ) );		

		m_pclGZFtpMgr->DisaptchGZFtpMsg( ( cltCharServer* )pclCM->CR[ id ], &clinfo );

		pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "피신고자 파일 작성 완료 [피신고자:%s] : 파일 수집 요청", data.szSenderName );
	}
}
