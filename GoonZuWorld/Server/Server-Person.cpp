//---------------------------------
// 2003/11/26 ���°�
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

// IP�� ������ ���� ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSON_IP(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id) == false)return ;

	SI32 targetid = pclMsg->siData32[0];
	if(pclCM->IsValidID(targetid) == false)return ;

	cltGameMsgResponse_IP clinfo(targetid, &pclCM->CR[targetid]->pclCI->clIP);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSON_IP, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���� ����Ʈ ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_UPDATECHILDLIST(cltMsg* pclMsg, SI32 id)
{
	// �޽����� �ʹ� ���ֿ��� ���� �����Ѵ�. 
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}


	cltGameMsgRequest_UpdateChildList* pclinfo = (cltGameMsgRequest_UpdateChildList*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// DB�� ����Ʈ�� ��û�Ѵ�. 
	sDBRequest_GetChildList clMsg(id, personid);
	pclGameDBProcess->SendMsg(DBSELECT_LETTER,  (sPacketHeader *)&clMsg);
}

// ������ ���ڸ� ¥����.
void cltServer::DoMsg_GAMEMSG_REQUEST_RENOUNCEPUPIL(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID( id ) )
		return;

	cltGameMsgRequest_RenouncePupil* pclinfo = (cltGameMsgRequest_RenouncePupil*)pclMsg->cData;

	sDBRequest_RenouncePupil clMsg( id, pclinfo->GetPupilPersonID() );
	pclGameDBProcess->SendMsg(DBSELECT_LETTER,  (sPacketHeader *)&clMsg);

	
}

// ���� ��� ��û�� ��� ��û. 
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

// ���� ��� ��û ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_APPLYFATHER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ApplyFather* pclinfo = (cltGameMsgRequest_ApplyFather*)pclMsg->cData;

	//KHY - 0610 - �������� S �߰�����.
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


	// ���� 
	if(pclinfo->siCharUnique == 0)
	{
		pclFatherManager->DeleteApplyer(pclCM->CR[id]->pclCI->GetPersonID());

		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(0, SRVAL_SUCCESSDELFATHERAPPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
	else
	{

		SI32 returnval = 0;
		if(pclFatherManager->AddApplyer(&clinfo, &returnval) == true)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, SRVAL_SUCCESSAPPLYFATHER,  0, 0, pclCM->CR[id]->GetCharUnique());

			// ���½�û�� ������������ �α׸� �����.
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 9. 7] // ���� ��û �α׾���. 
				// param1 == ��ȣõ�� ����.
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FATHER, LOGCOMMAND_INDEX_FATHER_APPLYFATHER, 
					0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					bAngel, 0, 0, 0, 0, NULL, NULL);
			}
		}
		else
		{
			if(returnval == ADD_FATHERSUPPLYER_ALREADY)
			{
				// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
				SendServerResponseMsg(0, SRVAL_FAILAPPLYFATHER_ALREADY,  0, 0, pclCM->CR[id]->GetCharUnique());

			}
			if(returnval == ADD_FATHERSUPPLYER_FULL)
			{

				// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
				SendServerResponseMsg(0, SRVAL_FAILAPPLYFATHER_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
			}
		}
	}
}

// ���� �� ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONPRIVATEINFO(cltMsg* pclMsg, SI32 id)
{
	cltClient* pclclient = (cltClient*)pclClient;

	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}

	cltGameMsgRequest_PersonPrivateInfo* pclinfo = (cltGameMsgRequest_PersonPrivateInfo*)pclMsg->cData;
	//if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)return ;
	if(pclCM->IsValidID(pclinfo->siCharUnique) == false)			return;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[pclinfo->siCharUnique];
	if(pclCM->IsValidID(pclinfo->siCharUnique)  == false)return ;

	// Ŭ���̾�Ʈ���� �뺸�Ѵ�. 
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
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
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

	// Ŭ���̾�Ʈ���� �뺸�Ѵ�. 
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

// �������� �б� ����� ����û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SCHOOLUSERNUM(cltMsg* pclMsg, SI32 id)
{
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(500) == true)
	{
		return ;
	}

	cltGameMsgRequest_SchoolUserNum* pclinfo = (cltGameMsgRequest_SchoolUserNum*)pclMsg->cData;
	if(pclinfo->siSchoolUnique <= 0)return ;

	// ����ڸ� �˻��Ͽ� �б� ����� ���� �ľ��Ѵ�. 
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


	// Ŭ���̾�Ʈ���� �뺸�Ѵ�. 
	cltGameMsgResponse_SchoolUserNum clinfo(pclinfo->siSchoolUnique, usernum);
	cltMsg clMsg(GAMEMSG_RESPONSE_SCHOOLUSERNUM, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ���� ���  ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETFATHER(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_SetFather* pclinfo = (cltGameMsgRequest_SetFather*)pclMsg->cData;

	// �Ϻ��̴�
	if( 0 == pclinfo->uiType)
	{
		// ������ �������� Ȯ���Ѵ�. 
		if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
			return ;

		// ���� ��� ��û�� ����Ʈ�� �ִ��� Ȯ���Ѵ�. 
		if(pclFatherManager->IsExist(pclinfo->siPersonID) == false)
		{
			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}

		// �ش� ����ڰ� �����ϴ��� Ȯ���Ѵ�. 
		SI32 targetid = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
		if(pclCM->IsValidID(targetid))
		{
			sDBRequest_SetFather clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), (TCHAR*)pclCM->CR[targetid]->GetName(), pclCM->CR[id]->pclCI->clIP.GetLevel());
			pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
		}
	}
	else if( 1 == pclinfo->uiType )
	{
		// ���ڰ� ���¿��� ������ ���ڰ� ��û
		if( 0 == pclinfo->uiMode )
		{
			// ������ �������� Ȯ���Ѵ�. 
			//KHY -0629 - 50�������̸� ������ ��û�� �� �ִ�.
			if( ConstServiceArea_Japan != siServiceArea)
			{
				if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= pclClient->siMinimumTeacherLevel)
					return ;
			}
			else
				if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)
					return ;

			// ���� ��� ��û�� ����Ʈ�� �ִ��� Ȯ���Ѵ�. 
			if(pclFatherManager->IsExist(pclinfo->siPersonID) == false)
			{
				// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
				SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[id]->GetCharUnique());
				return ;
			}

			// �ش� ����ڰ� �����ϴ��� Ȯ���Ѵ�. 
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
		// ������ ���� �����ؼ� ���ڸ� �޾��ֱ�
		else if( 1 == pclinfo->uiMode )
		{
			// ������ �������� Ȯ���Ѵ�. 
			//KHY -0629 - 50�������̸� ������ ��û�� �� �ִ�.
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
					// ������ �������� Ȯ���Ѵ�. 
					if(pclCM->CR[pupilID]->pclCI->clIP.GetLevel() >= pclClient->siMinimumTeacherLevel)
						return ;


					// ���� ��� ��û�� ����Ʈ�� �ִ��� Ȯ���Ѵ�. 
					if(pclFatherManager->IsExist( pclCM->CR[id]->pclCI->GetPersonID() ) == false)
					{
						// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
						SendServerResponseMsg(0, SRVAL_NOFATHERNAME,  0, 0, pclCM->CR[pupilID]->GetCharUnique());
						return ;
					}

					// �ش� ����ڰ� �����ϴ��� Ȯ���Ѵ�. 
					sDBRequest_SetFather clMsg(pupilID, pupilPersonID, (TCHAR*)pclCM->CR[id]->GetName(), pclCM->CR[pupilID]->pclCI->clIP.GetLevel());
					pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
				}
			}
		}
		// ������ ������ �����ߴ�
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
// �б����  ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETSCHOOL(cltMsg* pclMsg, SI32 id)
{
cltGameMsgRequest_SetSchool* pclinfo = (cltGameMsgRequest_SetSchool*)pclMsg->cData;

if(pclinfo->siSchoolUnique < 0)return ;
if(pclinfo->siSchoolUnique >= MAX_SCHOOL_NUMBER)return ;


// ������ ������Ʈ �Ѵ�. 
pclCM->CR[id]->pclCI->clBI.siSchoolUnique = pclinfo->siSchoolUnique;

// Ŭ���̾�Ʈ�� ������ ������. 
cltGameMsgResponse_School clinfo(pclCM->CR[id]->GetCharUnique(), pclCM->CR[id]->pclCI->clBI.siSchoolUnique);
cltMsg clMsg(GAMEMSG_RESPONSE_SCHOOL, sizeof(clinfo), (BYTE*)&clinfo);
((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);


// DB�� �����Ѵ�. 
{
sDBRequest_SetSchool clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->siSchoolUnique);
pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);
}


}
*/
// ���� �÷��� �ð� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_PLAYTIME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PlayTime* pclinfo = (cltGameMsgRequest_PlayTime*)pclMsg->cData;

	if(pclinfo->siCharUnique <= 0 || pclinfo->siCharUnique >= MAX_CHAR_NUMBER)return ;

	cltGameMsgResponse_PlayTime clinfo(pclCM->CR[id]->pclCI->clBI.siPlaySecond, 
		pclCM->CR[id]->pclCI->clBI.siPlayEventSecond );

	cltMsg clMsg(GAMEMSG_RESPONSE_PLAYTIME, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// �� Ǯ���ֱ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HORSEFREE(cltMsg* pclMsg, SI32 id)
{

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if(personid <= 0)return ;

	// ���� ���� �ϰ� �־�� �Ѵ�. 
	cltHorse* pclhorse  = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if( pclhorse == NULL || pclhorse->siHorseUnique <= 0 )	return; 

	// �� ���� Ÿ�� �ִ� ���°� �ƴϾ�� �Ѵ�. 
	if(pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		return ;
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	// �� �κ��� ��ǰ�� ������ Ǯ���� �� ����. 
	if(pclchar->pclCI->clCharItem.IsHorseHaveItem() )return ;

	// DB�� �����Ѵ�. 
	pclchar->UpdateHorseToDB(this, pclchar->pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_FREE);

	// ���� �����. 
	pclchar->pclCI->clHorseInfo.Init(pclchar->pclCI->clHorseInfo.siCurrentShowHorse);

	pclStatisticsManager->clDailyStatistics.siReleaseHorse++;

	
	pclchar->SetUpdateSwitch(UPDATE_HORSE, true, 0);

	// �̿��鿡�� �˸���. 
	cltGameMsgResponse_HorseFree clinfo(pclCM->CR[id]->GetCharUnique());
	cltMsg clMsg(GAMEMSG_RESPONSE_HORSEFREE, sizeof(clinfo), (BYTE*)&clinfo);
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);
}

// �� 
void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGEHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_ChangeHorse *pclinfo = ( cltGameMsgRequest_ChangeHorse * )pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// ���� ���� �ϰ� �־�� �Ѵ�. 
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
	
	// PCK : ���� �ٲٸ� ParametaBoxAction�� �����Ѵ�.  
	pclCM->CR[id]->SetParametaBoxAction(true);

	// DB�� �����Ѵ�. 
	pclchar->UpdateHorseToDB(this, pclchar->pclCI->clHorseInfo.siCurrentShowHorse, pclhorse, SETHORSE_REASON_UPDATE);

	//pclchar->SetUpdateSwitch(UPDATE_HORSE, true, 0);

	// ���ΰ� �̿����� �� ������ ������. 
	((cltCharServer*)pclCM->CR[id])->SendNeighbourMyHorseStatus(pclchar->pclCI->clHorseInfo.siCurrentShowHorse);

	if(((cltCharServer*)pclCM->CR[id])->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true)
	{
		//---------------------------------------
		// �̿��鿡�� ���� ������ �˸���. 
		//---------------------------------------
		// ������̴� ����� �����ؾ� �Ѵ�(�ֹ����� �����־�� �Ѵ�)
		if ( HORSEUNIQUE_MOTORCYCLE == pclhorse->siHorseUnique )
		{
			// ������ �׳� ������̸� ������̾��ٸ� �ٷ� ����� �����ϰ�
			if ( pclTimeMeterRate->IsUse() )
			{
				((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
			}
			// ���� ó�� Ÿ�� ���̶�� �ֹ߷� �������� ���۵Ǿ�� ����� �����ϰ�
			else if ( pclchar->pclCI->clBI.clTimeMeterRateInfo.UseStart(TIMEMETERRATE_MOTORCYCLE) )
			{
				((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
			}
			// �ƴϸ� �ٽ� ������ �������� �Ѵ�
			else
			{
				SI16 showHorseIndex = pclchar->pclCI->clHorseInfo.GetCurrentShowHorseIndex();

				pclchar->UnrideHorse();

				// �ֹ����� ���� ������ �������� �Ѵ�
				sDBRequest_SetRideHorse cldbmsg(id, pclchar->pclCI->GetPersonID(), showHorseIndex , false);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&cldbmsg);
			}
		}
		else
		{
			// ������ ������̿��� �ֹ����� ������̾��ٸ� ����� ���� ��Ų��
			if( pclTimeMeterRate->IsUse() )
			{
				// DB�� ���ð� ������ ����
				sDBRequest_TimeMeterRate_UseTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_MOTORCYCLE, pclTimeMeterRate->siUseTimeSec, true );
				SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

				// ��� ����
				pclchar->pclCI->clBI.clTimeMeterRateInfo.UseEnd( TIMEMETERRATE_MOTORCYCLE );
			}

			((cltCharServer*)pclCM->CR[id])->SendNeighbourMyShapeStatus();
		}
	}

	// �̿��鿡�� �˸���. 
	cltGameMsgResponse_ChangeHorse clinfo(pclinfo->siChangeHorseIndex , pclhorse,pclCM->CR[id]->GetCharUnique());
	cltMsg clMsg(GAMEMSG_RESPONSE_CHANGEHORSE, sizeof(clinfo), (BYTE*)&clinfo);
	//((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, TRUE);
	((cltCharServer*)pclCM->CR[id])->SendNetMsg((sPacketHeader*)&clMsg);
}


// ���� ���̵� ��û( �̴� Ȩ������ ������... )
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

// ��ų ���� ����.
void cltServer::DoMsg_GAMEMSG_REQUEST_DECREASESKILLBONUS(cltMsg* pclMsg, SI32 id)
{
	SI32 i;

	cltGameMsgRequest_DecreaseSkillBonus* pclinfo = (cltGameMsgRequest_DecreaseSkillBonus*)pclMsg->cData;
	if ( NULL == pclinfo )		return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 )		return;

	//----------------------------------
	// ��ų�� ������ Ȯ���Ѵ�.
	//----------------------------------
	SI32 skillunique = pclinfo->siSkillUnique;
	if ( (skillunique <= 0) || (MAX_SKILL_NUMBER <= skillunique) )	return;

	//---------------------------------
	// ��ų ������ �־�� �� �� �ִ�. 
	//---------------------------------
	SI32 skilllevel = pclCM->CR[id]->pclCI->clCharSkill.GetSkillLevel(skillunique);
	if(skilllevel <= 0)			return;

	//---------------------------------
	// ���� ������ ��ų����Ʈ�� 1�� �ƴ� �� �ִ�
	//---------------------------------
	bool			bSkillTypeFight	= false;
	cltSkillInfo*	pclGetSkill		= pclSkillManager->pclSkillInfo[skillunique];
	if ( NULL == pclGetSkill )	return;

	SI32 siDecreaseSkillPoint = 0;
	// ��� ��ü �ʱ�ȭ �̿�� - 2009.11.24 �ռ���
	if ( pclinfo->siInitMode ==INIT_SKILLMODE_TICKET_ALL ) 
	{
		siDecreaseSkillPoint = skilllevel;	// ��ü �ʱ�ȭ�� �ش� ��ų������ŭ ���� 
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
	// �ڽ� ��ų�� ������ 0���� �������� �ʴ´�.
	//---------------------------------
	// skillunique�� �θ�� �� ����� ������ 0�� �ƴϸ� ����. 
	UI08 childskilllist[MAX_CHILD_SKILL_NUM];
	SI32 childskillnum = 0;
	for(i = 0;i < MAX_CHILD_SKILL_NUM;i++)
	{
		childskilllist[i] = 0;
	}

	bool bfailswitch = false;
	SI32 childskillunique = 0;
	// ���� ������ ���������� �˻����� �ʴ´�
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
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(0, SRVAL_DECSKILL_FAIL_HAVECHILD,  childskillunique, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}
	if(index < 0 ) return ;

	switch(pclinfo->siInitMode)
	{
	case INIT_SKILLMODE_LEVEL:
		{
			//----------------------------------
			// ������ ���� ������ ����. 
			//----------------------------------
			
			if( pclCM->CR[id]->pclCI->clIP.GetLevel() != INIT_LEVEL && pclCM->CR[id]->pclCI->clIP.GetLevel() != INIT_LEVEL_SECOND )
				break;

			// ����Ȱ��ȭ : ���� ��ų�� �ø� ��ų���ʽ� ����Ʈ�� �ٽ� ���� ���� �ʴ´�. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, 1, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_LEVEL, 0, NULL);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ĳ������ ��ų ����.(Ȯ���ʿ��Ѱ�)
			//	// param1 == ������ ��ų ����ũ, 
			//	// param2 == ���ҽ��Ѿ� �� ��ų ����, 
			//	// param3 == �ٽ� ��������� ��ų���ʽ� ����Ʈ.
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
			// �������� ������ ����.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24040) ; // ����κ��ʱ�ȭ�̿��
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(1);

			// ��踦 ����. 
			pclItemManager->AddUseNum(itemunique, 1);

			// ���ο� ��� - ������ ���
			//NStatistics_Add("Item", itemunique, "UseNum", 1);

			// ����Ȱ��ȭ : ���� ��ų�� �ø� ��ų���ʽ� ����Ʈ�� �ٽ� ���� ���� �ʴ´�. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, 1, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_TICKET, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ĳ������ ��ų ����.(Ȯ���ʿ��Ѱ�)
			//	// param1 == ������ ��ų ����ũ, param2 == ���ҽ��Ѿ� �� ��ų ����, param3 == �ٽ� ��������� ��ų���ʽ� ����Ʈ.
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
			// �������� ���������ŭ ������ ����.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24040) ; // ����κ��ʱ�ȭ�̿��
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) < skilllevel )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(skilllevel);

			// ��踦 ����. 
			pclItemManager->AddUseNum(itemunique, skilllevel);

			// ���ο� ��� - ������ ���
			//NStatistics_Add("Item", itemunique, "UseNum", skilllevel);
	
			// ����Ȱ��ȭ : ���� ��ų�� �ø� ��ų���ʽ� ����Ʈ�� �ٽ� ���� ���� �ʴ´�. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, skilllevel, siDecreaseSkillPoint, childskilllist, DECSKILLMODE_WEAPONSKILL, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ĳ������ ��ų ����.(Ȯ���ʿ��Ѱ�)
			//	// param1 == ������ ��ų ����ũ, param2 == ���ҽ��Ѿ� �� ��ų ����, param3 == �ٽ� ��������� ��ų���ʽ� ����Ʈ.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, skilllevel, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
		// ��� ��ü �ʱ�ȭ �̿�� - 2009.11.24 �ռ���
	case INIT_SKILLMODE_TICKET_ALL:
		{
			//------------------------------------
			// �������� ���������ŭ ������ ����.
			//-----------------------------------
			SI32 itemunique = ITEMUNIQUE(24041) ; // ����κ��ʱ�ȭ�̿��
			if ( pclCM->CR[id]->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
				break;

			SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(itemunique);
			if(pos <= 0)break;

			cltItem clitem;
			clitem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(1);

			// ��踦 ����. 
			pclItemManager->AddUseNum(itemunique, 1);

			// ����Ȱ��ȭ : ���� ��ų�� �ø� ��ų���ʽ� ����Ʈ�� �ٽ� ���� ���� �ʴ´�. by PCK - 2007.08.08
			if(	pclClient->IsCountrySwitch(Switch_ManufactureRevitalize) && 
				pclClient->pclSkillManager->IsManufactureSkill(skillunique))
			{
				siDecreaseSkillPoint = 0;
			}

			sDBRequest_DecreaseSkill clMsg(id, personid, index, skillunique, skilllevel, siDecreaseSkillPoint, childskilllist, INIT_SKILLMODE_TICKET_ALL, pos, &clitem);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			//{
			//	// [�α��߰� : Ȳ���� 2007. 10. 11] // ĳ������ ��ų ����.(Ȯ���ʿ��Ѱ�)
			//	// param1 == ������ ��ų ����ũ, param2 == ���ҽ��Ѿ� �� ��ų ����, param3 == �ٽ� ��������� ��ų���ʽ� ����Ʈ.
			//	cltServer * pclServer = (cltServer*)pclClient;
			//	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SKILL, LOGCOMMAND_INDEX_SKILL_DECREASE, 
			//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
			//									skillunique, skilllevel, siDecreaseSkillPoint, 0, 0, NULL, NULL);
			//}
		}
		break;
	}
}

// ����Ʈ ��� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELQUEST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_CancelQuest* pclInfo = (cltGameMsgRequest_CancelQuest*)pclMsg->cData;

	//--------------------------------
	// ����ƮŸ���� Ȯ���Ѵ�. 
	//--------------------------------
	SI32 questtype		= pclInfo->siQuestType;
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(personid <= 0)return ;

	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)return ;

	// �ش� ����Ʈ Ÿ�Կ� �������� ����Ʈ�� �ִ°� ?
	cltPersonQuestUnitInfo* pclquestinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype];

	// �������� ����Ʈ�� �ִٸ� ����Ʈ ������ ���� ��ġ�Ѵ�. 
	if(pclquestinfo->siCurQuestUnique)
	{
		// �Ϸ�ܰ��� ����Ʈ�� �ƴ϶�� ����Ѵ�. 
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

				// Ư�� ����Ʈ ������ �����Ѵ�. 
				// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
#ifdef _SAFE_MEMORY
				sDBRequest_SetSpecialQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clSpecialQuestInfo, &pclchar->pclCI->clQuestInfo.bWordAssemblySwitch[0]);
#else
				sDBRequest_SetSpecialQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clSpecialQuestInfo, pclchar->pclCI->clQuestInfo.bWordAssemblySwitch);
#endif
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);
			}
			else if(questtype == QUEST_TYPE_NAMING )
			{
				pclchar->pclCI->clQuestInfo.clNamingQuestInfo.Init(); //KHY - ���̹� ����Ʈ�� �����Ǿ�� �Ѵ�.

				// naming - ���̹� ����Ʈ ���� ����
				sDBRequest_SetNamingQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clNamingQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);

			}
			//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
			else if(questtype == QUEST_TYPE_HAPPYBEAN )
			{
				//���Ǻ� ��ŸƮ ī���͸� ������.
				SendLog_SetHappyBeanClearInfo(pclchar, questtype, QUEST_HAPPYBEAN_STEP_NON);

				pclchar->pclCI->clQuestInfo.clHappyBeanQuestInfo.Init();
				// �ʱ�ȭ�� ���Ǻ� ������ ������.
				sDBRequest_SetHappyBeanQuestInfo clMsg1(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clHappyBeanQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg1);
			}
			// �̼� ���� : ��ҿ� ���� ���� - by LEEKH 2008-09-17
			else if( questtype == QUEST_TYPE_MISSION1 )
			{
				pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
				sDBRequest_SetMissionQuestInfo	clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
				SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);
			}

			// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
			sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
			pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

			// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
			pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
		}
	}
}


// ����Ʈ ���࿡ ���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SETQUESTGOING(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_QuestGoing* pclInfo = (cltGameMsgRequest_QuestGoing*)pclMsg->cData;

	//--------------------------------
	// ����ƮŸ���� Ȯ���Ѵ�. 
	//--------------------------------
	SI32 questtype		= pclInfo->siQuestType;
	SI32 questunique	= pclInfo->siQuestUnique;
	SI32 queststep		= pclInfo->siQuestStep;
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar == NULL)	return ;
	if(personid <= 0)	return ;

	if(questtype < 0 || questtype >= MAX_QUEST_TYPE)return ;

	// �Ƿε� �ý����� �����Ǿ� �ְ�,  TIRED_STATUS_MUCH_TIRED ���¶��, ������ ����Ʈ ������ �ȵȴ�. 
	if(pclchar->bTiredSystem) //�Ƿε� �ý����� �����Ǿ� �ִ� ��츸
	{
		if (	pclchar->uiTiredState == cltCharCommon::TIRED_STATUS_MUCH_TIRED 
			||	pclchar->uiTiredState == cltCharCommon::TIRED_STATUS_LITTLE_TIRED	)
			return;		
	}

	// �ش� ����Ʈ Ÿ�Կ� �������� ����Ʈ�� �ִ°� ?
	cltPersonQuestUnitInfo* pclquestinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype];

	// �������� ����Ʈ�� �ִٸ� ����Ʈ ������ ���� ��ġ�Ѵ�. 
	if(pclquestinfo->siCurQuestUnique)
	{
		if(pclquestinfo->siCurQuestStep == QUEST_STEP_MIDDLE)
		{
			// �Ϸ� �������� ���θ� ���´�. 
			if(queststep == QUEST_STEP_CLEAR)
			{
				cltQuestInfoCommon* pclinfo = NULL;

				// Ư���� ����Ʈ ó���� ���� ����Ʈ ���� ����
				switch(questtype)
				{
				case QUEST_TYPE_SPECIAL:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo;			break;
				case QUEST_TYPE_NAMING:			pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo;				break;
				case QUEST_TYPE_HAPPYBEAN:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo;			break;
				case QUEST_TYPE_MISSION1:		pclinfo = &pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo;			break;
				default:						pclinfo = pclQuestManager->GetQuestInfo(pclquestinfo->siCurQuestUnique);										break;
				}

				if(pclinfo == NULL)return;

				// �Ϸ� ������ ������Ų��. 
				if(pclCM->CR[id]->IsClearCondition(questtype, &pclinfo->clQuestClearConditionInfo) == true)
				{
					//-----------------------------------------------------------------------
					// �Ϸ� ���ǿ��� ĳ������ �κ����� �����ؾ� �� ������ �ִ� ��� �����Ѵ�.
					//-----------------------------------------------------------------------

					// �������� �������� �ִ� ��쿡�� �������� �� �� �ִ� ��Ȳ���� Ȯ���ؾ� �Ѵ�. 
					cltQuestRewardInfo* pclreward = &pclinfo->clQuestRewardInfo;
					bool bIsHaveItemReward = false;

					// ������ �����ؾ� �ϴ°��..
					// ������ ������ �ܿ��� ���� ������ �����ش�...;
					//SI32 rewardItemUnique[MAX_QUEST_REWARD_NUMBER] = {0,};

					SI32	siRewardItemUnique[MAX_MATERIAL_NUMBER]	= {0, };
					SI32	siRewardItemNumber[MAX_MATERIAL_NUMBER]	= {0, };
					SI32	siRewardItemUseDate	= 0;
					SI32	siRepeatCounter		= 0;


					ZeroMemory( siRewardItemUnique, (sizeof(SI32) * MAX_MATERIAL_NUMBER) );
					ZeroMemory( siRewardItemNumber, (sizeof(SI32) * MAX_MATERIAL_NUMBER) );
					
					// �������� ��Ḧ �ִ� ����ġ�� �����ִٸ� ��Ḧ �ش�
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

							// �ش�������� �ʿ��� ���������� ���ؿ´�
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
						} // if ( ( siRewardItem > 0 ) && ( siReference > 0 ) ) ����
						else
						{
							bIsHaveItemReward = false;
						}
					}
					// �Ϲ����� ������ ���� ����Ʈ
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
						// �ش� �������� �����ϰ� �����. 
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

						// �ش�������� �κ��� ���� �� �ִ��� Ȯ���Ѵ�. 

						SI32 rtnvalue;
						if(pclchar->CanAddInvManyItems(INVMODE_ALL, clManyRewardItem, &rtnvalue) == false)
						{
							// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
							SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, pclCM->CR[id]->GetCharUnique());

							// db���� ������ش�
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
					// ������ �����Ѵ�. 
					//-----------------------------------------------------------------------
					bool rewardswitch = false;

					// �������� �ش�. 
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

							// �Ƿι��� �ý��� ���� ( ����Ʈ �������� ��� ��� �ش�.)
							if ( pclItemManager->GetItemType( siQuestItemUnique ) != ITEMTYPE_QUEST )
							{
								rewardItemNum = pclchar->CalcTiredPoint( rewardItemNum );
							}

							// ĳ���Ϳ��� �������� �ְ� �ʿ��� ��ġ�� ���Ѵ�. 
							if( rewardItemNum > 0 )
							{
								if(  pclchar->GiveItem(siQuestItemUnique, rewardItemNum, INPUTITEMPERSON_OPTION_QUEST, siUseDateForLog) == false )
								{
									// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
									SendServerResponseMsg(0, SRVAL_QUEST_FAIL_FULLINV,  0, 0, pclCM->CR[id]->GetCharUnique());

									// db���� ������ش�
									SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,siQuestItemUnique,
										rewardItemNum,pclreward->siNCoin,siUseDateForLog,false);

									return ;
								}
								else
								{
									rewardswitch = true;

									// ��踦 ����. 
									pclItemManager->AddQuestItemNum(siQuestItemUnique, rewardItemNum);

									// ���ο� ��� - ����Ʈ ���� ��ǰ�� ��踦 ����.
									NStatistics_Add("Item", siQuestItemUnique, "Quest", rewardItemNum);

									// db���� ������ش�
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
					// ���� ����� �̺�Ʈ : �ܿ����! ����S�� ������ ������ �̺�Ʈ
					// - by LEEKH 2007.12.21
					//-----------------------------------------------------------------------
/*					if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
					{
						switch(questtype)
						{
						case QUEST_TYPE_BATTLE1:			// ����������
						case QUEST_TYPE_BASIC1:				// ����
						case QUEST_TYPE_HUNTINGGROUND01:	// ���Ǿ�
						case QUEST_TYPE_HUNTINGGROUND02:	// ����Ű
						case QUEST_TYPE_BATTLE2:			// ��
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

								// ������ ����Ʈ ���...
								if( maxunique == questunique)
								{
									SYSTEMTIME	SEvent, EEvent;
									ZeroMemory(&SEvent, sizeof(SEvent));
									ZeroMemory(&EEvent, sizeof(EEvent));

									SEvent.wYear = 2007;	SEvent.wMonth = 12;		SEvent.wDay = 27;
									EEvent.wYear = 2008;	EEvent.wMonth = 1;		EEvent.wDay = 23;	EEvent.wHour = 23;	EEvent.wMinute = 59;	EEvent.wSecond = 59;

									_SYSTEMTIME stCreateTime = pclchar->pclCI->clBI.GetFirstCreatTime(); //���� ���� ���� �ð�.

									// �̺�Ʈ �Ⱓ�� �������� �ð��� üũ �Ѵ�.
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

					// ���� �ش�. 
					if(pclreward->siMoney)
					{
						// ������ ����ݾ׿� NPC Rate�� ����Ǵ� ���̶��
						GMONEY rewardMoney = pclreward->siMoney;
						if ( true == pclreward->bApplyNpcRate )
						{
							SI64 siNPCPriceRate = pclItemManager->clItemStatistic.siNPCPriceRate;
							rewardMoney = rewardMoney * siNPCPriceRate / 100;
						}

						// �Ƿι��� �ý��� ����
						rewardMoney = pclchar->CalcTiredPoint( rewardMoney );

						sDBRequest_ChangeMoney clMsg(id, personid, CHANGE_MONEY_REASON_QUESTREWARD, rewardMoney);
						pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

						pclAddMoneyStatistics->Add(ADDMONEY_STATISTIC_QUEST, rewardMoney);

						// ��ȭ����  �����Ѵ�. 
						cltMoney clmoney;


						clmoney.Set(rewardMoney);
						clCurrencyInfo.clInputMoney_Quest.Increase(&clmoney);

						rewardswitch = true;
					}

					// ����ġ�� �ش�.
					if(pclreward->siExp)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

						// �Ƿι��� �ý��� ����
						SI32 rewardExp = pclchar->CalcTiredPoint( pclreward->siExp );
						pclchar->IncreaseExp(rewardExp);

						rewardswitch = true;
					}
					//��� ����ġ�� �ش�.		//KHY  - 0219 - �������ġ�� �����߰��Ѵ�.
					if(pclreward->siSkillType)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

						// �Ƿι��� �ý��� ����
						SI32 rewardExp = pclchar->CalcTiredPoint( pclreward->siExp );
						pclchar->SetSkillUpdate(pclreward->siSkillType,pclreward->siSkillExp);

						//pclchar->IncreaseExp(rewardExp);

						rewardswitch = true;
					}
					
					// �� ����ġ�� �ش�. 
					if(pclreward->siFameExp)
					{
						//cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
						// �Ƿι��� �ý��� ����
						SI32 rewardFameExp = pclchar->CalcTiredPoint( pclreward->siFameExp );

						pclchar->IncreaseFameExp(rewardFameExp);

						rewardswitch = true;
					}

					// ��ǰ ���� ����Ʈ�̸�, ������ ���� �����Ѵ�. 
					if(pclreward->siNCoin)
					{
						if ( PushCash(pclCM->CR[id]->GetCharUnique(), pclCM->CR[id]->pclCI->GetPersonID(), 
							pclCM->CR[id]->pclCI->clBI.szAccountID, pclreward->siNCoin, PUSHCASH_REASON_QUESTEVENT) )
						{
							// db���� ������ش�
							SendLog_GiveQuestItem(pclCM->CR[id]->pclCI->GetPersonID(),questtype,questunique,pclreward->siItemUnique[0],
								pclreward->siItemNum[0],pclreward->siNCoin,pclreward->siItemUseDate[0],true);
						}
					}
					
					if(pclreward->bMoveBuf)
					{
						pclchar->dwIncreaseMovespeedLastClock	= INCREASEMOVESPEED_DELAY;	// �̵��ӵ� �������� �����ð�. 
						pclchar->dwIncreaseMovespeedStartClock = pclClient->CurrentClock;		// �̵��ӵ� ��������   ���۽ð�. 

						// ���� ����Ǿ����� ������ ���ǵ� �÷���
						if (pclchar->clInnerStatus.IsStatus(INNERSTATUS_INCREASEMOVESPEED) == false)
						{
							pclchar->clInnerStatus.SetStatus(INNERSTATUS_INCREASEMOVESPEED);
							pclchar->siIncreaseMovespeedPower		= INCREASEMOVESPEED_POWER;				// �̵��ӵ� ���������� ����. 
							SI32 siCurrentSpeed = pclchar->clPB.TotalMoveSpeed;
							if (siCurrentSpeed + pclchar->siIncreaseMovespeedPower > 20)
								pclchar->clPB.GivenMoveSpeed = 20;
							else
								pclchar->clPB.GivenMoveSpeed = max(0, siCurrentSpeed + pclchar->siIncreaseMovespeedPower);


							pclchar->clPB.TotalMoveSpeed = pclchar->clPB.GivenMoveSpeed;
						}

						// �̿����� �뺸 
						cltCharChangeStatusInfo	StatusInfo(CHANGETYPE_INCREASEMOVESPEED, true, pclchar->clPB.GivenMoveSpeed);
						cltGameMsgResponse_StatusInfo clChangeInfo(pclchar->GetCharUnique(), &StatusInfo);
						cltMsg clMsg(GAMEMSG_RESPONSE_CHANGESTATUSINFO, sizeof(clChangeInfo), (BYTE*)&clChangeInfo);
						pclchar->SendNeighbourMsg(&clMsg, true);

						// �̵��ӵ� ���� �޼��� �ѷ���
						TCHAR* pTitle = GetTxtFromMgr(5614);
						TCHAR *pText = GetTxtFromMgr(6412);
						cltGameMsgResponse_Notice clNotice(pTitle, pText,true);
						cltMsg clMsg2(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
						pclchar->SendNetMsg((sPacketHeader*)&clMsg2);

						// [���� : Ȳ���� 2007. 10. 11 => �̵��ӵ������� �ִµ� ������ �ȵ�.] // ������ �̷�����ٰ� ǥ��.
						rewardswitch = true;
					}
					// [����] : 2010�ų��̺�Ʈ - ����� ����
					if ( true == pclreward->bDeBuff )
					{
						SI16 index0 = -1;
						bool bDeBuff;

						index0 = pclchar->pclCI->clBI.clBufInfo.FindBufSlot( BUF_EVENT_FORTUNE_BAD ); // ���� ������ ����id�� �����ϸ� ����� �ϵ��ڵ� ���ص� ��. 
						//�ϴ��� ����� ������ �� ���� �Ⱦ����� �𸣴� ������� ����°ŷ�..
						if ( -1 < index0 )
						{
							// ����� �� ������ (����� ������ ��� ����) �ִٸ� ��� ����� �޼��� ����.
							stBuf DelBuf( BUF_EVENT_FORTUNE_BAD, 0, 0);
							sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index0, &DelBuf );
							((cltServer*)pclClient)->SendDBMsg( DBSELECT_BASE, (sPacketHeader *)&clMsg );

							// Ŭ�� ����� �ߴٰ� ��ȣ ���� �޼����� ���� ������ �ʰ� 2010�ų��̺�Ʈ�� ��Ŷ�� �̿� �Ŀ� ������� �������� ������� �����Ǿ� �Ѵٸ� ��Ŷ ���� �ۼ�
							// fortunequality�� 200�̸� ����� �޼����� ���
							cltGameMsgResponse_2010NewYear_FortuneResult clinfo( pclchar->pclCI->GetPersonID(), 200, 0, 0, 0, 0, 0 );
							cltMsg clMsg2( GAMEMSG_RESPONSE_FORTUNERESULT, sizeof(clinfo), (BYTE*)&clinfo );
							pclchar->SendNetMsg( (sPacketHeader*)&clMsg2 );
						}

						rewardswitch = true;
						bDeBuff = true;
					}

					// ����ã�� �̺�Ʈ �������ϋ� ���� �����
					if ( questtype == QUEST_TYPE_FINDTREASURE ) 
					{
						if ( questunique == 31515 ) // ����ã�� ������ �̺�Ʈ Ŭ���� �ϋ� ���� �ش�.
						{
							SI32 siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // ���ǽð� 48�а�.
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
						// naming - ���� ���̹� ����Ʈ �Ϸ� ���� ����. DB�������� �ٲ���. �ϴ� �׽�Ʈ
						sDBRequest_SetPersonNamingInfo clMsg(pclCM->CR[id]->pclCI->GetPersonID(),
							pclreward->siNamingIndex, pclreward->siNamingLevel );
						SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg );

						// �Ϸ� �˸�
						rewardswitch = true;
					}

					// ������ �̷�����ٸ�, 
					if(rewardswitch == true)
					{
						if(questtype == QUEST_TYPE_SPECIAL)		// Ư���ӹ��� ��� �ʱ�ȭ�Ѵ�. 
						{
							bool bClearSpecialWordQuest = false ;
							// ���� ���߱� �ܾ �����ϰ� �����Ѵ�. 
							SI32 wordindex = pclQuestManager->GetRandWordAssembly();
							if(wordindex >= 0)
							{

								// �̹� ���� ������ �ϼ��Ǿ� �ִٸ�, 
								if(pclCM->CR[id]->pclCI->clQuestInfo.IsWordAssembleCompleted(pclQuestManager) == true)
								{
									pclCM->CR[id]->pclCI->clQuestInfo.InitWordAssemble();

								}

								pclCM->CR[id]->pclCI->clQuestInfo.bWordAssemblySwitch[wordindex] = true;

								// �ܾ� ���տ� ���������� �����Ѵ�.

								bClearSpecialWordQuest = pclCM->CR[id]->pclCI->clQuestInfo.IsWordAssembleCompleted( pclQuestManager) ;
							}

							// Ŭ���̾�Ʈ�� ���� ������ �뺸�Ѵ�. 
							cltGameMsgResponse_SpeicalQuestReward clinfo(pclreward, wordindex, ((cltCharServer*)pclCM->CR[id])->uiTiredState );
							cltMsg clMsg1(GAMEMSG_RESPONSE_SPECIALQUESTREWARD, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);


							pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo.Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();

							// ��ι� ����Ʈ ���� ����Ʈ ���̸�, 
							pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_SPECIALQUEST);

							// ������� �̺�Ʈ �Ⱓ���� �̺�Ʈ ���� Ƚ �� ����.
							bool bLampEventPeriod = false;
							bLampEventPeriod = pclEventTimeManager->InEventTime("MagicLamp_event", &sTime);
							bLampEventPeriod = (bLampEventPeriod && bClearSpecialWordQuest);

							// ����Ʈ ������ �����ؼ� DB�� �����Ѵ�. 
							sDBRequest_SetSpecialQuestInfo clMsg(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clSpecialQuestInfo,
								&pclCM->CR[id]->pclCI->clQuestInfo.bWordAssemblySwitch[0],
								bClearSpecialWordQuest, bLampEventPeriod);
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg);

							//��ι� ����Ʈ �Ϸ�� ���. 
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
						else if ( questtype == QUEST_TYPE_HAPPYBEAN )	//KHY - 0822 - ���Ǻ� ����Ʈ �߰�.
						{
							// Ŭ���̾�Ʈ�� ���� ������ �뺸�Ѵ�. 
							cltGameMsgResponse_HappyBeanQuestReward clinfo(pclreward);
							cltMsg clMsg1(GAMEMSG_RESPONSE_HAPPYBEANQUEST_REWARD, sizeof(clinfo), (BYTE*)&clinfo);
							pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

							SendLog_SetHappyBeanClearInfo(pclchar, QUEST_TYPE_HAPPYBEAN, QUEST_HAPPYBEAN_STEP_COMPLETE);

							// �ʱ�ȭ�� DB����
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo.Init();

							// ����Ʈ ������ �����ؼ� DB�� �����Ѵ�. 
							sDBRequest_SetHappyBeanQuestInfo clMsg2(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clHappyBeanQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);

						}
						else if ( questtype == QUEST_TYPE_NAMING )
						{
							// naming - �ʱ�ȭ�� DB����
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo.Init();

							// ����Ʈ ������ �����ؼ� DB�� �����Ѵ�. 
							sDBRequest_SetNamingQuestInfo clMsg2(pclCM->CR[id]->pclCI->GetPersonID(),
								&pclCM->CR[id]->pclCI->clQuestInfo.clNamingQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMsg2);
						}
						else if( questtype == QUEST_TYPE_MISSION1 )
						{
							// ���ֵ��� �̼� �϶� Ŭ��� ���� ���� �뺸
							if ( MISSIONQUEST_UNIQUE_GOONZUDAY == questunique )
							{
								cltGameMsgResponse_GoonzuDayMissionClearReward clinfo( pclCM->CR[id]->pclCI->GetPersonID(), 
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siExp,
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemUnique[0],
									pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.siItemNum[0] );

								cltMsg clMsg1(GAMEMSG_RESPONSE_GOONZUDAYMISSION_CLEARREWARD, sizeof(clinfo), (BYTE*)&clinfo);
								pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);
							}

							// �̼� ����Ʈ �ʱ�ȭ - by LEEKH 2008-09-18
							pclCM->CR[id]->pclCI->clQuestInfo.clUnit[questtype].Init();
							pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo.Init();

							// ����Ʈ ������ �����ؼ� DB�� �����Ѵ�. 
							sDBRequest_SetMissionQuestInfo clMissionQuest( pclCM->CR[id]->pclCI->GetPersonID(), &pclCM->CR[id]->pclCI->clQuestInfo.clMissionQuestInfo );
							SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuest);
						}
						
						// ����Ʈ Ŭ���� ����Ʈ�� Ŭ���̾�Ʈ�� ������.						
						cltGameMsgResponse_QuestEffect	clinfoQuestEff( pclchar->GetCharUnique() ,QUEST_EFFECT_CLEAR);
                        cltMsg clQuestEffMsg(GAMEMSG_RESPONSE_QUESTEFFECT,sizeof(clinfoQuestEff), (BYTE*)&clinfoQuestEff);
						pclchar->SendNeighbourMsg(&clQuestEffMsg,true);

						// ����Ʈ�� ���¸� �����Ѵ�. 
						pclquestinfo->siCurQuestStep	= queststep;

						// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
						sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
						SendDBMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

						// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
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
					pclquestinfo->SetBit(bit, 1);		// Ŭ������ ����Ʈ. 
				}

				// ����Ʈ ���� �ʱ�ȭ. 
				pclquestinfo->siCurQuestUnique	= 0;
				pclquestinfo->siCurQuestStep	= 0;
				pclquestinfo->siQuestCmd		= 0;
				pclquestinfo->siQuestPara1		= 0;
				pclquestinfo->siQuestPara2		= 0;

				// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
				sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
				pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg );

				// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_QUEST, true, 0);

				// db�� �α׸� ����Ѵ�.
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
	// �������� ����Ʈ�� ���ٸ� ������ ����Ʈ���� �����ΰ� ?
	else
	{
		// questunique�� ������ ������ ����Ʈ�� �³� ?
		// �Ϸ���� ���� ���� ���� ����Ʈ�� Unique�� ���Ѵ�. 
		SI32 minbit = pclCM->CR[id]->GetMinBit(questtype);
		// ��� ����Ʈ�� �Ϸ�Ǿ���. 
		if(minbit < 0)
		{
			return ;
		}

		SI32 minquestunique = pclQuestManager->GetQuestUniqueFromBit(questtype, minbit);
		if(minquestunique <= 0)
		{
			return ;
		}

		// ���� �Ϸ���� ���� ���� ���� ����Ʈ�� ��û���� ����Ʈ�� ��ġ�Ѵٸ�, 
		if(minquestunique != questunique)
		{
			return ;
		}

		//��û���� ����Ʈ�� �ܰ谡 QUEST_STEP_MIDDLE�� �ƴ϶��. 
		if(queststep != QUEST_STEP_MIDDLE)
		{
			return ;
		}

		cltQuestInfo* pclnextquestinfo = pclQuestManager->GetQuestInfo(questunique);
		if(pclnextquestinfo == NULL)return ;

		// �ӹ� �ο� ���� ���� Ȯ��.
		
		// ���� ������� ����Ʈ �������� ����
		if ( pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) == false )
		{
			// ��ũ�� 6400 �� ����Ʈ�� �ޱ� ���ؼ� ������� ��� ����Ʈ�� Ŭ���� �ؾ� ��
			if(pclnextquestinfo->siUnique == QUESTUNIQUE(6400) )
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
				{
					return;
				}								
			}

			//���˼�, ����ȣ�� ���� �ޱ� ���ؼ� ������� ��� ����Ʈ�� Ŭ���� �ؾ� ��
			if( pclnextquestinfo->siType == QUEST_TYPE_BEGINNER3 
				||  pclnextquestinfo->siType == QUEST_TYPE_BEGINNER4
				)
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear( pclQuestManager, QUEST_TYPE_BEGINNER2) == false)
				{
					return;
				}
			}

			// ��� ���� ����Ʈ�� �ޱ� ���ؼ� ������ ��� ����Ʈ�� Ŭ���� �ؾ� ��
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

			// BATTLE1 �� ��� Ŭ���� �ؾ� BATTLE2 ����Ʈ�� ���� �� �ִ�.
			if( pclnextquestinfo->siType == QUEST_TYPE_BATTLE2 )
			{
				if(pclCM->CR[id]->pclCI->clQuestInfo.IsAllClear(pclQuestManager, QUEST_TYPE_BATTLE1) == false)
				{
					return;
				}    
			}
		}	// if ( pclClient->IsWhereServiceArea( ConstServiceArea_Korea ) == false ) ����

		// ���� 
		if(pclnextquestinfo->clInitConditionInfo.siLevel)
		{
			if(pclCM->CR[id]->pclCI->clIP.GetLevel() < pclnextquestinfo->clInitConditionInfo.siLevel)
			{
				return ;
			}
		}
		// ��ų. 
		if(pclnextquestinfo->clInitConditionInfo.siSkillUnique)
		{
			if(pclCM->CR[id]->pclCI->clCharSkill.GetTotalSkillLevel(pclnextquestinfo->clInitConditionInfo.siSkillUnique, 0, 0, &pclCM->CR[id]->pclCI->clCharItem.clItem[0]) < pclnextquestinfo->clInitConditionInfo.siSkillLevel)
			{
				return ;
			}
		}

		// �ʼ� ���� ����Ʈ Ȯ��.
		SI32 mustclearquestunique = pclnextquestinfo->clInitConditionInfo.siMustClearQuestUnique;
		if( mustclearquestunique > 0 )
		{
			if( pclCM->CR[id]->pclCI->clQuestInfo.IsClear(pclClient->pclQuestManager , mustclearquestunique) == false )
			{
				return ;
			}
		}

		// ����Ʈ�� ���¸� �����Ѵ�. 
		pclquestinfo->siCurQuestUnique	= questunique;
		pclquestinfo->siCurQuestStep	= queststep;

		pclquestinfo->siQuestCmd	= pclnextquestinfo->clQuestClearConditionInfo.siFlag;
		pclquestinfo->siQuestPara1	= pclnextquestinfo->clQuestClearConditionInfo.siPara1;
		pclquestinfo->siQuestPara2	= 0;

		// ����Ʈ ���� ����Ʈ�� Ŭ���̾�Ʈ�� ������.
		cltGameMsgResponse_QuestEffect	clinfoQuestEff( pclchar->GetCharUnique() ,QUEST_EFFECT_RECEIVE);
		cltMsg clQuestEffMsg(GAMEMSG_RESPONSE_QUESTEFFECT,sizeof(clinfoQuestEff), (BYTE*)&clinfoQuestEff);
		pclchar->SendNeighbourMsg(&clQuestEffMsg,true);


		// DB�� ����Ʈ�� ���¸� �����Ѵ�. 
		sDBRequest_SetQuestInfo clMsg(personid, questtype, pclquestinfo);
		pclGameDBProcess->SendMsg( DBSELECT_SUB, (sPacketHeader *)&clMsg);

		// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_QUEST, true, 0);

		// db�� �α׸� ����Ѵ�.
		SendLog_GetQuest(personid,questtype,questunique,true);
	}
}

// ����Ʈ ���� �뺸. 
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
		case QUEST_CLEAR_COND_LAMPGOMAP:		// ������� ���� ��ȸ
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
				// �ƹ�ó���� ���� ����
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
					// �˾����� �ش� �޽����� ����� �ش�.
					SendServerResponseMsg(0, SRVAL_RETURN_LOSTWORLDQUEST_COMPLETE,  0, 0, id);
				}

				//if(siBufTransformKind == pclClient->GetUniqueFromHash( TEXT("KIND_TRICERAMONS")))
				{
					// BUF_TRANSFORM Ÿ������ ���ŵ� ��Ȳ�̸� ������ �Ϸ� ��Ų��.
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
	}	// switch ( pclinfo->siQuestClearCond ) ����


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;
	
	// ���� ����Ʈ�� �������̸�, ������ ��ġ�� ���Ͽ� �ذ��Ѵ�.  
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

// �ڸ� ���� ����
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

	// ���� ������ ������ Type�� ���� �������ɼ��� Ÿ���Ѵ�.
	if(pMagicAttributePtr && pMagicAttributePtr->IsMatchAttackTye(id, magickind, pclchar->GetAttackType()) == true)
	{
		// �ش� Skill�� ������ �������� ���캻��.

		// [����] ��ų�� ȹ�� ������ ��� ��ų ������ ����ش�.
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
			// �����

			pclchar->DoQuestCheckAndAction( QUEST_CLEAR_COND_MAGICACTIVE );
		}
	}
	
	// Client���� �˷��ش�.
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
	// ��Ƽȹ�渷��
	//	SI32 sizetest = sizeof(cltPersonInfo);
#endif

	clpersoninfo.Set(pclCM->CR[id]->pclCI);

	//----------------------------------------
	// �� ���� ������ ��� ��� ������ ������ �ʾƾ� �� ���� �ֵ�. 
	// ����� �����Ͽ� ���� �䱸�� ���� �𸣴� ���, 
	//----------------------------------------
	cltPersonHorseInfo clhorseinfo;
	clhorseinfo.Set(&clpersoninfo.clHorseInfo);

	// �����ü��� ������ ���� �䱸 ������ ������ �������� �ִ�. 
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


	// ������ �������� ������ cltPersonInfoOne Ŭ������ ĳ�������� �� �ִ�
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
	// ���� �ð� ������ ������. 
	//------------------------------------------
	{
		cltMsg clDate(GAMEMSG_RESPONSE_DATE, sizeof(cltDate), (BYTE*)&pclTime->clDate);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clDate);

		//���������ð��� ������
		cltGameMsgResponse_ServerTime clTime(sTime);
		cltMsg clTimeMsg(GAMEMSG_RESPONSE_SERVERTIME, sizeof(clTime), (BYTE*)&clTime);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clTimeMsg);

	}

	//-----------------------------------------
	// ���� ���� ���µ� ������. 
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
	// ���ĸ��� �̺�Ʈ ���̸� �˸���.
	//-----------------------------------------
	SI32 siVillageUnique = pclMofuMofuEvent->GetCurrentEventVillage();
	if(siVillageUnique > 0)
	{
		cltGameMsgResponse_MofuMofuEvent_Start clinfo(siVillageUnique);

		cltMsg clMsg(GAMEMSG_RESPONSE_MOFUMOFUEVENT_START, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	//-----------------------------------------
	//[����] ���� �̺�Ʈ - ���� ���� ���̸� �˸�
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
	// ��� ��Ȳ�� �����Ѵ�. 
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
	money = 300;*/ // �⼮ �̺�Ʈ
	// ������ ���� ���޵Ǵ� ���� �ٸ���. 
	/*if(pclCM->CR[id]->pclCI->clIP.GetLevel()	  >= 100)			money = 300;
	else if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= 50)			money = 200;
	else if(pclCM->CR[id]->pclCI->clIP.GetLevel() >= FATHER_LEVEL)	money = 100;												
	else money = 0;
	*/
	/*					if( siServiceArea == ConstServiceArea_Korea ) {
	PushCash(id, pclCM->CR[id]->pclCI->GetPersonID(), pclCM->CR[id]->pclCI->clBI.szAccountID, money,
	PUSHCASH_REASON_ATTENDANCE,3);
	}

	// ����
	if ( sTime.wMonth == 8 && sTime.wDay == 14 )
	{
	SI32 itemunique = 3355 ; // �����
	SI32 itemnum	= 30;
	cltItem clItem;
	bool brareswitch = false;
	if(pclItemManager->MakeRandItemUnique( itemunique, &clItem, 0, &brareswitch) == true)
	{
	clItem.SetItemNum(itemnum);

	TCHAR buffer[256] = TEXT("") ;
	sprintf(buffer, TEXT("���� ������� [%s] [%d]���� �޾ҽ��ϴ�."),clItem.GetShortName(pclItemManager),itemnum);
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


	// ���ʽ� ��ġ�� ���������� �ʴٸ� �����Ų��. 
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

	// ���ʽ��� �й��ϴ� �����̸� ���ʽ��� ���� �־�� �� �� �ִ�.
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
			//[����] ������ �������� ���ѻ��� ����. => 2008-4-4
			if(false == pclClient->IsCountrySwitch(Switch_CharStatusReform))
			{
				// �����ִ� ���� * 2 ������ ����Ѵ�.
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

		// ���ºκ��ʱ�ȭ�̿���� �����ϴ��� Ȯ���Ѵ�. 
		//SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(14095);
		SI32 itempos = pclCM->CR[id]->pclCI->clCharItem.FindItemInv(ITEMUNIQUE(24035));
		if(itempos <= 0)
		{
			return ;
		}

		// ���ºκ��ʱ�ȭ�̿���� �Ҹ��Ѵ�. 
		cltItem clItem;
		clItem.Set(&pclCM->CR[id]->pclCI->clCharItem.clItem[itempos]);
		clItem.SetItemNum(1);

		sDBRequest_UseItem clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), itempos, &clItem,USEITEM_REASON_TICKET);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	

		// ������ ���� ���ʽ��� �ִ´�. 
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

	// ĳ������ IP�� Ŭ���̾�Ʈ�� ���� �� �ְ� �Ѵ�. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);


	//����� ������ DB�� �����Ѵ�. 
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
	//	// [�α��߰� : Ȳ���� 2007. 10. 15] // ĳ���� ���ʽ� ��ġ ���� ����.
	//	// param1 == ĳ���Ͱ� ��� ���ʽ� ��ġ.
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
	// �̸��� ��û���� ����� ���̵� Ȯ���Ѵ�. 
	//-------------------------------------------------
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		cltGameMsgResponse_GetName clinfo(pclinfo->siCharUnique, (TCHAR*)pclCM->CR[charid]->GetName());


		// Ŭ���̾�Ʈ���� ���ο� ������� �̸��� �뺸�Ѵ�.
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
	// �̸��� ��û���� ����� ���̵� Ȯ���Ѵ�. 
	//-------------------------------------------------
	SI32 charid = cltCharCommon::CharUniqueInfo[pclinfo->siCharUnique];
	if(pclCM->IsValidID(charid))
	{
		cltGameMsgResponse_GetName clinfo(pclinfo->siCharUnique, (TCHAR*)pclCM->CR[charid]->GetName());


		// Ŭ���̾�Ʈ���� ���ο� ������� �̸��� �뺸�Ѵ�.
		cltMsg clNormalMsg(GAMEMSG_RESPONSE_RIGHTMOUSE_USERLIST_NAME, 
			sizeof(clinfo), 
			(BYTE*)&clinfo);

		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
	}

}

void cltServer::DoMsg_GAMEMSG_REQUEST_USERORDER(cltMsg* pclMsg, SI32 id)
{
	cltOrderData* porder	= (cltOrderData*)pclMsg->cData;
	SI32 hostid	= id;		// ����� �����ϴ� ��ü ĳ����. 


	if(porder->ODI.siOrder == ORDER_ATTACK_SUMMON)
	{
		// ���� ����� ��ȯ�Ѵ�. 
		porder->ODI.siOrder = ORDER_ATTACK;
		hostid = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(hostid)  == FALSE)
		{
			return ;
		}
	}

	if(porder->ODI.siOrder == ORDER_MAGIC_SUMMON )
	{
		// ���� �������� ��ȯ�Ѵ�.
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
		// �̵� ����� ��ȯ�Ѵ�. 
		porder->ODI.siOrder = ORDER_MOVE;
		hostid = pclCM->CR[id]->GetSummonID();
		if(pclCM->IsValidID(hostid)  == FALSE)
		{
			return ;
		}
	}

	// �ش� ĳ���Ϳ��� ����� ���� �����Ѵ�. 
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
// Ŭ���̾�Ʈ���� ��û�� ���Ÿ� ������ ����Ѵ�.
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

	// �׳� ���Ÿ� ����
	if( pclinfo->siMagicKind == 0 )
	{
		SI32 power = pclCM->CR[charID]->GetApower();
		if( IsPC(charID) )
		{
			// �ּ� �Ÿ����� ���� �Ұ����� ĳ������ ��쿡�� 
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
	// ��������
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

// ĳ������ ���� ���� ��û�� ó���Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGESTATUSINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_StatusInfo* pclinfo = (cltGameMsgRequest_StatusInfo*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)return ;



	switch(pclinfo->ChangeInfo.siChangeType)
	{
	case CHANGETYPE_AUTOFOOD:
		{
			pclCM->CR[id]->pclCI->clHorseInfo.bAutoFoodSwitch = pclinfo->ChangeInfo.bChangeSwitch;

			// DB�� ������ �����Ѵ�. 
			sDBRequest_SetAutoFood clDBMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclinfo->ChangeInfo.bChangeSwitch);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clDBMsg);


			// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
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

	// �޽����� �ʹ� ���ֿ��� ���� �����Ѵ�. 
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
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
	GMONEY money = cost * pclItemManager->clItemStatistic.siNPCPriceRate ; // �ϴ� 1���ɿ� ������

	cltGameMsgResponse_Get_WeaponSkillCost clinfo(pclinfo->siSkillUnique,pclinfo->siSkillLevel,money);
	cltMsg clMsg(GAMEMSG_RESPONSE_GET_WEAPONSKILLCOST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SET_WEAPONSKILL(cltMsg* pclMsg,SI32 id)
{
	// �޽����� �ʹ� ���ֿ��� ���� �����Ѵ�. 
	// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
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

	// ��ų �ø���ó���� ���� �ʾҴٸ�
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

	// ���� ��ų�̶�� pclGetInfo�� �ٸ� ���� �� �� ����
	cltSkillInfo* pclGetInfo = pclSkillManager->pclSkillInfo[siSkillUnique];
	if ( NULL == pclGetInfo )
	{
		pclLog->LogPrint( TEXT("pclSkillInfo is NULL") );
		return;
	}

	// ������ ��ų�� ���������� �ƴ϶��
	if ( SKILLTYPE_FIGHT != pclGetInfo->siSkillType )
	{
		pclLog->LogPrint( TEXT("This is not Fight Skill Type [SkillUnique : %d]"), siSkillUnique );
		return;
	}

	// ���� ��ų �̶�� �θ� ��ų������ ����´�
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

	SI32 siNeedSkillPoint = 0;	// �̰��� DB�� ��������
	if ( false == pclSkillManager->GetWeaponSkillNeedSkillPoint(siSkillUnique, siSkillLevel, &siNeedSkillPoint) )
	{
		// �� �Լ��� ���� False�� ���Դٴ� ���� ��ų ������ �����̴�(��������Դµ� �� �Լ��� False�� ������ ������ �����Ƿ� �� ������Ұ�)
		pclLog->LogPrint( TEXT("GetWeaponSkillNeedSkillPoint function return value is FALSE") );
		return;
	}

	// �̰��� 1�̻��̾�� �Ѵ�(��ȹ�ǵ�)
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

	cltItem	clNeedItem;				// �̰��� DB�� �������� (���� ��ų�϶� �Ҹ�Ǵ� ������)
	SI32	siNeedItemPos	= -1;	// �̰��� DB�� �������� (-1�϶��� �������� �Ҹ���� ����, �� ���� ��ų�϶� ����) 
	GMONEY	gmRealCost		= 0;	// �̰��� DB�� �������� (�Ϲ� ��ų�϶� �Ҹ�Ǵ� ��)

	// ���� ��ų�� �Ϲݽ�ų�� �˻� ��ƾ�� �ٸ���
	if ( bHiddenSkill )
	{
		if ( false == pclSkillManager->IsUpgradeHiddenWeaponSkill(siSkillUnique, siSkillLevel, id) )
		{
			pclLog->LogPrint( TEXT("IsUpgradeHiddenWeaponSkill function return value is FALSE") );
			return;
		}
		
		if ( false == pclSkillManager->GetHiddenWeaponSkillItem( siSkillUnique, siSkillLevel, &clNeedItem) )
		{
			// �� �Լ��� false�� ������ �ȵ� ���� �ִ°��Դϴ�.
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

	// �̰��� ������ ������ �ٽ� Ǯ������Ѵ�
	pclchar->bIsWeaponSkillUp = true;

}
/*
void cltServer::DoMsg_GAMEMSG_REQUEST_COUNTATTACK_INFO(cltMsg* pclMsg , SI32 id)
{
if ( pclCM->IsValidID(id) == false ) return ;
// �޽����� �ʹ� ���ֿ��� ���� �����Ѵ�. 
// ������ �޽��� ���� �ð��� üũ�Ѵ�. 
if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
{
return ;
}

// �̹� üũ������ �ƴ��� �˻��Ѵ�.
if ( ((cltCharServer*)pclCM->CR[id])->bCheckGameEvent == true ) return ;

SI32 itemunique = 8150 ; // �ݰ��Ǳ��
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
	// �޽����� �ʹ� ���ֿ��� ���� �����Ѵ�. 


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	SI08 data = 1;

	if ( pclCM->CR[id]->pclCI->clBI.bGameEvent == false )
	{
	cltItem clItem;
	// �ݰ��� ��� 1���� �ش�
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
	// �κ��� ���ڸ��� ��� �߰��� �� ����. 
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
	// �۷ι����� �λ縻 ���װ� �߻��Ͽ�, �ִ��Է� ����Ʈ�� 100����Ʈ�� �����Ѵ�. - by LEEKH 2009-02-24
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


	// DB�� Ȩ������ URL������ ��û�Ѵ�.
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


	// DB�� �������� URL������ �����Ѵ�.
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

	// gmmode 4�϶�(Berserker) �� ������ ����. ������ �����Ƿ�
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

//cyj Ŭ���̾�Ʈ�� ���� ��Ȱ�� ��û�ϴ� �޼����� ������ ��Ȱ
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
// ����ã�� �̺�Ʈ - ��ī�� �ְ� ���� �ޱ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_USEOKARA(cltMsg* pclMsg , SI32 id)
{
	cltGameMsgRequest_TreasureEvent_Use_Okara * pclinfo = (cltGameMsgRequest_TreasureEvent_Use_Okara*)pclMsg->cData;
	if ( pclCM->IsValidID(id) == false ) return ;
	// ����� ������
	// ��ī��
	SI32 siUseItem = ITEMUNIQUE( 2017 );
	SI32 siUseItemNum  = 10 ;	// 10��
	cltItem clitem;
	SI32 siref = pclClient->pclItemManager->FindItemRefFromUnique(siUseItem);
	if(siref <= 0) return ;
	// ���� �κ��丮���� �ش� �������� �ִ��� Ȯ�� �Ѵ�.
	cltCharServer * pclchar = (cltCharServer *)pclCM->CR[id];
	SI32 siHaveitemNum = pclchar->pclCI->clCharItem.GetItemNum( siUseItem ) ;	// �������� � ������ �ִ��� Ȯ��.

	SI16 siEmptySlot = pclchar->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_EVENT_FINDTREASURE, false );
	if ( siEmptySlot < -1)	return	;	// ���� �� �ڸ��� ����.

	if ( siHaveitemNum >= siUseItemNum ) // ����� ���� �ִٸ� 
	{
		for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
		{
			if(pclchar->pclCI->clCharItem.clItem[i].siUnique == siUseItem)
			{
				if ( siUseItemNum == 0 )	break	;	// ������ 0���� ������
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
					clitem.siItemNum = invItemNum	;// �縸ŭ �ְ� 

					//��ü �������� ���ش�
					siUseItemNum =  siUseItemNum - invItemNum	;
					// ����ض�
					sDBRequest_UseItem clMsg(id, pclchar->pclCI->GetPersonID(), i, &clitem, USEITEM_REASON_NONE);
					pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				}
			}
		}
		// �� �Ҹ� �ߴٸ� ������ �ش�.
		SI32 siUseItem = ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24 ; // ���ǽð� 48�а�.
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

	// �δ����� ��Ȱ�ϴ� ��尡 �ƴϸ� �Ѿ����� ������. ��Ȱ�� �������� �Ҹ����� �ʴ´�.
	if( pclClient->pclMapManager->IsInstanceMap( pclchar->GetMapIndex() ) == true &&
		pclchar->siKilledMode == 0 )
	{
		cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// �溹�� ��������� ����. 
		pclchar->SetWarpInfo(&clWarpInfo, 56);
		pclchar->Warp();

		return;
	}
	
	// [����] ��Ʋ�ξ� ���� ��� �׳� ��Ȱ 
	if(pclchar->siKilledMode == KILLEDMODE_BATTLEROYAL)
	{
		pclchar->Revive();
	}
	// ��Ȱ�� �������� ������ �ִٸ� ��� ��Ȱ. ���ٸ� ����� ���� ��Ȱ - �ٸ� �����ۺ��� ���������� ���� ã�Ƽ� Ȯ�� �Ѵ� 
	for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];

		if( pclitem->siUnique <= 0 ) continue;

		if(	pclitem->siUnique == ITEMUNIQUE(2731)	&& pclitem->GetItemNum() > 0 )
		{
			//// ���������� ã�Ҵ�. ��� �����Ų�� �츰��.
			//while(pclchar->clItemUseReserveInfo.Push(ITEMUNIQUE(2731) , -1 , i) == false)
			//{
			//	pclchar->ItemUseReserveAction();
			//}

			//if(pclitem->siItemNum == 1)
			//{
			//	pclchar->ItemUseReserveAction();
			//}

			//pclitem->Decrease(1);
			//  �̹� ��� �߱� ������ ������Ʈ���ϰ� �츰�� 

			// Ŭ���̾�Ʈ�� �Ҹ�� ������ ������Ʈ
			cltGameMsgResponse_PersonItemInfo clinfo( i , PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			// ���ڸ����� ��� ��Ȱ��Ų��.
			((cltCharServer*)pclCM->CR[id])->Resurrection(false);

			return;
		}
	}
	// ��Ȱ�� �������� ������ �ִٸ� ��� ��Ȱ. ���ٸ� ����� ���� ��Ȱ	//���������� ���� ���� ������ �ٸ� ��Ȱ�� �����۵��� ã�Ƽ� �츰��.
	for(SI32 i = PERSONITEM_INV0;i < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON;i++)
	{
		cltItem * pclitem = &pclchar->pclCI->clCharItem.clItem[i];

		if( pclitem->siUnique <= 0 ) continue;

		SI32 ref = pclItemManager->FindItemRefFromUnique(pclitem->siUnique);

		if( ref <= 0 ) continue;

		if(	pclItemManager->pclItemInfo[ref]->siHealEft == HEALEFT_RESURRECTION	&& pclitem->GetItemNum() > 0 )
		{
			// ������ ��ġ�� ã�Ҵ�. �Ҹ� ���� ��Ű�� ��Ȱ��Ų��.
			while(pclchar->clItemUseReserveInfo.Push(pclitem->siUnique , -1 , i) == false)
			{
				pclchar->ItemUseReserveAction();
			}

			if(pclitem->siItemNum == 1)
			{
				pclchar->ItemUseReserveAction();
			}

			pclitem->Decrease(1);

			// Ŭ���̾�Ʈ�� �Ҹ�� ������ ������Ʈ
			cltGameMsgResponse_PersonItemInfo clinfo( i , PERSONITEMINFO_OPTION_NONE, 0, 0, pclitem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

			// ���ڸ����� ��� ��Ȱ��Ų��.
			((cltCharServer*)pclCM->CR[id])->Resurrection(false);
						
			return;
		}
	}
	// PVP�� ���� �Ŷ�� ���ڸ����� ��Ȱ
	if ( pclinfo->siDieMode == PVP_DIE ) 
	{
		// ���ڸ����� ��� ��Ȱ��Ų��.
		((cltCharServer*)pclCM->CR[id])->Resurrection(true);
		return	;
	}
	// pk �ʺ��� ���� pk ���̶�� ���Ӹ����κ����� .,
	if ( IsCountrySwitch( Switch_PKHuntMap_Change_Info )) 
	{
		if( pclClient->pclMapManager->IsPkMap( pclchar->GetMapIndex() ) == true && 
			pclchar->siKilledMode == 0 )
		{
			cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);	// �溹�� ��������� ����. 
			pclchar->SetWarpInfo(&clWarpInfo, 56);
			pclchar->Warp();

			return;
		}
	}
	// �� ã�� �������Դ�. �׳� ��Ȱ��Ų��.
	
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
		// ���� ���� DB�� ������
        sDBRequest_SetCountry clMsg( personid, pclinfo->siCountryID );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader*)&clMsg );

		// ���� ���� DB�� ������
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
		// ���� �ʱ�ȭ
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

		//	// ������� �Ŀ��Ը� �����Ѵ�. 
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

// 20�̸� ���� ���� ��û
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
	// �Ϻ������� Ǫġ�ڹ� ���񽺸� �Ѵ�
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
	// �Ϻ������� Ǫġ�ڹ� ���񽺸� �Ѵ�
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
			// ���� �������� �ƴ϶�� DB�� ��ȸ�� ��û�Ѵ�.
			
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

	// ����ó��
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

				// �⼮�� �� �� ���ٸ�
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
				// �̹� ������ ���� �� ���� ���¶��
				if ( pclchar->pclCI->clBI.bAttendToday[pclInfo->siType] == true )
				{
					return;
				}

				// ������ ���� �� �ִ��� üũ�ؼ� �ȵǸ� ���޴´�
				if ( pclchar->pclCI->clBI.bIsCanReward == false )
				{
					return;
				}

				// �⼮ ������ ���� �� �ִ� �������� üũ�ؼ� Season2 �⼮�� �Ѵ�.
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

//KHY - 0910 - Ŭ���̾�Ʈ�� ĳ���������� ���ϰ��� ������.
void cltServer::DoMsg_GAMEMSG_REQUEST_CHARSERVERRTN(cltMsg* pclMsg, SI32 id )
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_CharServerRTN* pclinfo = (cltGameMsgRequest_CharServerRTN*)pclMsg->cData;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if(pclinfo->siResult == 1)
	{
		//KHY - 0906 -�ش������ �ش��̺�Ʈ Ÿ�Կ� ���� ������ �߱޿��θ� ��û�Ѵ�.
		SendLog_SetEventCouponInfo(pclchar, GAMEROOM_COUPON_EVENT,0);	
	}
}

//KHY - 1220 - ���Žý���.
void cltServer::DoMsg_GAMEMSG_REQUEST_TRANSFORM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_SetTransForm* pclinfo = (cltGameMsgRequest_SetTransForm*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltItem *pclItemList = pclchar->pclCI->clCharItem.GetEquipSet(EQUIPSET_PERSON);
	cltPSkillInfo *pclskillinfo = &pclchar->pclCI->clCharSkill;
 
	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
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

	// ������ ����
	if( pclinfo->m_siTransFormKind < 0 || pclinfo->m_siTransFormKind >= MAX_KIND_NUMBER )		return;
	if( pclKindInfoSet->pclKI[pclinfo->m_siTransFormKind] == NULL)								return;

	if( pclCM->IsAlive( id ) == false ) //������ ���� �� �� ����.
	{
		//SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}
	//if ( pclchar->siEnemUnique > 0 ) 
	//{
	//	// �����߿��� ���� �Ұ��� 
	//	return	;
	//}

	if( pclchar->clTransFormInfo.bTransFormMode == true ) // ���� ���¸� ����.
		return;

	if( pclchar->clTransFormInfo.SearchTransFormChar((UI16)pclinfo->m_siTransFormKind) == false ) // ���� ���¸� ����.
		return;

	if( pclchar->GetAttackType() == ATTACKTYPE_HAND )
	{
		// ���⸦ �������� ���� ���� ������ �� �����ϴ�.
		return;
	}

	if( pclchar->CanTransFormAttackType(pclinfo->m_siTransFormKind) == false)
	{
		// ���� Ÿ���� �޶� ������ �� �����ϴ�.
		return;
	}

	// ���ſ� �ʿ��� ������ �ý��� Ȯ��
	if( pclchar->pclCI->clBI.clTimeMeterRateInfo.GetLeftTime( TIMEMETERRATE_TRANSFORM ) <= 0)
	{
		// ���ſ� �ʿ��� �ð��� ���ڶ��ϴ�. �ð��� ������ �ֽʽÿ�.
		return;
	}

	// ���ſ� ���� ������ �ð� ����
	if( pclchar->pclCI->clBI.clTimeMeterRateInfo.UseStart( TIMEMETERRATE_TRANSFORM ) == false)
	{
		return;
	}

	// ���� ����
	pclchar->CharTransform( pclinfo->m_siTransFormKind ,pclchar->ActiveWeapon,pclItemList , pclskillinfo);

	// Ÿ�� ���� ����
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
 
	// ������ ����
	if( pclinfo->m_siTransFormKind < 0 || pclinfo->m_siTransFormKind >= MAX_KIND_NUMBER )		return;
	if( pclKindInfoSet->pclKI[pclinfo->m_siTransFormKind] == NULL)								return;

	if( pclCM->IsAlive( id ) == false ) //������ ���� �� �� ����.
	{
		//SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}

	// ���� ���� �ƴ϶�� ����
	if( pclchar->clTransFormInfo.bTransFormMode == false )				return;

	cltTimeMeterRate* pclTimeMeterRate = pclchar->pclCI->clBI.clTimeMeterRateInfo.GetTimeMeterRate(TIMEMETERRATE_TRANSFORM);
	if(pclTimeMeterRate == NULL)										return;

	// Ÿ�� ���� üũ
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
		// DB�� ���ð� ������ ����
		sDBRequest_TimeMeterRate_UseTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_TRANSFORM, pclTimeMeterRate->siUseTimeSec, true );
		SendDBMsg( DBSELECT_BASE, (sPacketHeader*)&clMsg );

		// DB�� ���� �ð��� �߰����ش�.
		sDBRequest_Transform_AddTime clMsg1(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), pclchar->clTransFormInfo.uiNowTransFormKind, pclTimeMeterRate->siUseTimeSec );
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg1);

		// ��� ����
		pclchar->pclCI->clBI.clTimeMeterRateInfo.UseEnd( TIMEMETERRATE_TRANSFORM );
	}

	// ���� ����	
	pclchar->CharTransform( 0 ,pclchar->ActiveWeapon,pclItemList,pclskillinfo);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TRANSFORM_USEITEM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_UseTransFormItem* pclinfo = (cltGameMsgRequest_UseTransFormItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// ������ ����
	//if( pclchar->clTransFormInfo.bTransFormMode == true ) // ���� ���¸� ����. - ������ ������?
	//	return;

	SI32 pos1 = -1;

	if ( pclchar->pclCI->clCharItem.GetItemNum(pclinfo->siItemUnique) <= 0) //�ش� �������� ����.
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(0, SRVAL_FAIL_NOTRANSFROMITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	
	}

	pos1 = pclchar->pclCI->clCharItem.GetItemPos(pclinfo->siItemUnique); //������ ��ġ ����.
	if( pos1 < 0 )
		return ;

	cltItem clitem;
	clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos1]);
	clitem.SetItemNum(1);

	if( pclinfo->siItemUnique == ITEMUNIQUE(5410) ||
		pclinfo->siItemUnique == ITEMUNIQUE(5411) ||
		pclinfo->siItemUnique == ITEMUNIQUE(5412) ) // ���� �ð� ���� �������̴�. - ������.
	{
		SI32 siAddTime = 0;
		
		// [�߰� : Ȳ���� 2008. 1. 16 => ���� ���ִ� ���� �����ð� ����.]
		if( pclClient->IsWhereServiceArea( ConstServiceArea_Korea | ConstServiceArea_English | ConstServiceArea_Taiwan | ConstServiceArea_USA | ConstServiceArea_NHNChina | ConstServiceArea_EUROPE) ) 
		{
			if( pclinfo->siItemUnique == ITEMUNIQUE(5410) )
			{
				siAddTime = 12 * 60 * 60;		// 12�ð�
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5411) )
			{
				siAddTime = 48 * 60 * 60;		// 48 �ð�
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5412) )
			{
				siAddTime = 96 * 60 * 60;		// 96�ð�
			}
		}
		else
		{
			if( pclinfo->siItemUnique == ITEMUNIQUE(5410) )
			{
				siAddTime = 86400;		// 1 ��
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5411) )
			{
				siAddTime = 604800;		// 7 ��
			}
			else if( pclinfo->siItemUnique == ITEMUNIQUE(5412) )
			{
				siAddTime = 2592000;	// 30 ��
			}
		}
		
		if(siAddTime <= 0)			return;

		// DB�� �����Ѵ�. 
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

		//KHY - 0124 - ��í����- ���� ���� ������.
		SI32 AddTime = 0;
		switch(pclinfo->siItemUnique)
		{
			case ITEMUNIQUE(13612):
			case ITEMUNIQUE(13613):
				AddTime = 10800;  // �⺻ 3�ð��̴�. -  
				break;
			case ITEMUNIQUE(13615):
			case ITEMUNIQUE(13616):
			case ITEMUNIQUE(13623): // ����� ���Ǹ� - ���Ÿ�
			case ITEMUNIQUE(13624): // ����� ���Ǹ� - �ٰŸ�
			case ITEMUNIQUE(13626): // [����] ȣ�ڻ���. �ҷ��� ����  - �ٰŸ�
			case ITEMUNIQUE(13627): // [����] ȣ�ڻ���. �ҷ��� ����  - ���Ÿ�
			case ITEMUNIQUE(13633): // ũ�������� �ٰŸ�����
			case ITEMUNIQUE(13632): // ũ�������� ���Ÿ�����
			case ITEMUNIQUE(13641): // �˻罺�Ǹ� - �ٰŸ�
			case ITEMUNIQUE(13642): // �ųʽ��Ǹ� - ���Ÿ�
			case ITEMUNIQUE(13652): // �������Ǹ�(��) - �ٰŸ� ; ����ũ �߰��Ǹ� ������ ����.
			case ITEMUNIQUE(13653): // �������Ǹ�(��) - ���Ÿ� ; ����ũ �߰��Ǹ� ������ ����.
			// ��í - 12�� ���Ǹ� ����	���� ���� �罺��ġ
			case ITEMUNIQUE(13657 ): // ���� ����
			case ITEMUNIQUE(13656 ): // �罺��ġ
				AddTime = 864000;   // �⺻ 10���̴�.
				break;
		}

		// ĳ���� ��Ͽ��� Ȯ��.
		if(uTransFormChar > 0)
		{
			if(pclchar->clTransFormInfo.SearchTransFormChar(uTransFormChar) == true)
			{
				// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
				//SendServerResponseMsg(0, SRVAL_FAIL_ALEADYTRANSFROMCHR,  0, 0, pclCM->CR[id]->GetCharUnique());
				//return; //�̵̹�ϵ� ĳ���ʹ�.
				// DB�� �����Ѵ�. 

				// �̹� ��ϵ� ĳ�������� ��� �ð��� �÷��ش�.
				sDBRequest_TimeMeterRate_AddTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_TRANSFORM, AddTime, &clitem, pos1);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				return; //�̵̹�ϵ� ĳ���ʹ�.
			}
		}


		// DB�� �˸���. - ĳ���� ����.		
		sDBRequest_Transform_AddChar clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), uTransFormChar, &clitem, pos1, TIMEMETERRATE_TRANSFORM, AddTime);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return ;
}

//KHY - 1111 - ������� �߰�.
void cltServer::DoMsg_GAMEMSG_REQUEST_OILLING_USEITEM(cltMsg* pclMsg,SI32 id)
{
	if ( pclCM->IsValidID(id) == false )	return;

	cltGameMsgRequest_UseOillingItem* pclinfo = (cltGameMsgRequest_UseOillingItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 pos1 = -1;

	if ( pclchar->pclCI->clCharItem.GetItemNum(pclinfo->siItemUnique) <= 0) //�ش� �������� ����.
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������.  - 
		//SendServerResponseMsg(0, SRVAL_FAIL_NOTRANSFROMITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	
	}

	pos1 = pclchar->pclCI->clCharItem.GetItemPos(pclinfo->siItemUnique); //������ ��ġ ����.
	if( pos1 < 0 )
		return ;

	cltItem clitem;
	clitem.Set( &pclchar->pclCI->clCharItem.clItem[pos1]);
	clitem.SetItemNum(1);

	if( pclinfo->siItemUnique == ITEMUNIQUE(13631) ) // �ֹ���.
	{
		SI32 siAddTime = 0;
		
		siAddTime = 200 * 60;		// 200 ��
		
		if(siAddTime <= 0)			return;

		// DB�� �����Ѵ�. 
		sDBRequest_TimeMeterRate_AddTime clMsg(pclchar->GetCharID(), pclchar->pclCI->GetPersonID(), TIMEMETERRATE_MOTORCYCLE, siAddTime, &clitem, pos1);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}

	return ;
}


// [����] ������ ���� �̺�Ʈ �����귿 ������ ����ϴ� ��Ŷ. => 2008-6-10
void cltServer::DoMsg_GAMEMSG_REQUEST_BUFF_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_Buff_Roulette* pclInfo = (cltGameMsgRequest_Buff_Roulette*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 CompleteBuffKind = 0;
	// Ŭ�󿡼� �귿�� �����Ƿ� �ش� ������ �ش�.
	if(false == pclInfo->m_bAction)
	{
		if(pclInfo->m_Money > pclchar->pclCI->clIP.GetMoney())
		{
			return;
		}

		// ��ü ������ ��ȣ �迭.
		SI32 BuffKindArray[BUF_END];		
		ZeroMemory(BuffKindArray, sizeof(BuffKindArray));
		
		// ������ ��ȣ�� ���� Ȯ�� �迭.
		SI32 BuffKindArrayRate[BUF_END];	
		ZeroMemory(BuffKindArrayRate, sizeof(BuffKindArrayRate));

		//KHY - 1113 - ũ�������� �̺�Ʈ - ũ���������� ���� �� ������ ����.
		if( pclEventTimeManager->InEventTime("ChristmasEvent", &sTime) )
		{
			BuffKindArray[0]		= BUF_ATTACKUP;					// ������ ����
			BuffKindArrayRate[0]	= 780;
			BuffKindArray[1]  		= BUF_DEFENSEUP;				// ���� ����.
			BuffKindArrayRate[1]	= 780;
			BuffKindArray[2]  		= BUF_MAKEEXPUP;				// ���� ����ġ ����.
			BuffKindArrayRate[2]	= 380;
			BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// ���� ���� ȿ��.
			BuffKindArrayRate[3]	= 500;
			BuffKindArray[4]  		= BUF_SUMMONATACUP;				// ��ȯ�� ��ȭ. 
			BuffKindArrayRate[4]	= 750;
			BuffKindArray[5]  		= BUF_LOVEPOWER;				// ��� ����		
			BuffKindArrayRate[5]	= 150;
			BuffKindArray[6]  		= BUF_FRIENDSHIP;				// ���� ����
			BuffKindArrayRate[6]	= 150;
			BuffKindArray[7]  		= BUF_HINAMOCHI;				// ���κ��� ����ũ ȿ��.
			BuffKindArrayRate[7]	= 80;
			BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// ������ ���� 100% ����.
			BuffKindArrayRate[8]	= 620;
			BuffKindArray[9] 		= BUF_FOURLEAF;					// ����Ŭ�ι� - ������ ����� 2��.
			BuffKindArrayRate[9]	= 60;
			BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// ����ġ 150% ȹ��.
			BuffKindArrayRate[10]	= 250;
			BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// �谡 �Ȱ����� �������� - ���� �ʴ´�,
			BuffKindArrayRate[11]	= 500;
			BuffKindArray[12]		= ITEMUNIQUE(13002);		// ũ�������� �縻. - �������������� �׳� ����. - �����ƽ� �ȳѾ�� ���� 
			BuffKindArrayRate[12]	= 50;			
		}
		else
		{
			BuffKindArray[0]		= BUF_ATTACKUP;					// ������ ����
			BuffKindArrayRate[0]	= 860;
			BuffKindArray[1]  		= BUF_DEFENSEUP;				// ���� ����.
			BuffKindArrayRate[1]	= 860;
			//BuffKindArray[2]  		= BUF_SPEEDUP;					// ���ǵ尡 ����
			//BuffKindArrayRate[2]	= 900;
			BuffKindArray[2]  		= BUF_MAKEEXPUP;				// ���� ����ġ ����.
			BuffKindArrayRate[2]	= 350;
			BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// ���� ���� ȿ��.
			BuffKindArrayRate[3]	= 550;
			BuffKindArray[4]  		= BUF_SUMMONATACUP;				// ��ȯ�� ��ȭ. 
			BuffKindArrayRate[4]	= 710;
			BuffKindArray[5]  		= BUF_LOVEPOWER;				// ��� ����		
			BuffKindArrayRate[5]	= 150;
			BuffKindArray[6]  		= BUF_FRIENDSHIP;				// ���� ����
			BuffKindArrayRate[6]	= 200;
			BuffKindArray[7]  		= BUF_HINAMOCHI;				// ���κ��� ����ũ ȿ��.
			BuffKindArrayRate[7]	= 150;
			BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// ������ ���� 100% ����.
			BuffKindArrayRate[8]	= 700;
			BuffKindArray[9] 		= BUF_FOURLEAF;					// ����Ŭ�ι� - ������ ����� 2��.
			BuffKindArrayRate[9]	= 70;
			BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// ����ġ 150% ȹ��.
			BuffKindArrayRate[10]	= 300;
			BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// �谡 �Ȱ����� �������� - ���� �ʴ´�,
			BuffKindArrayRate[11]	= 600;
		}
		
		SI32 TotalRate = 0;

		// ���õ� ������ ��ȣ �迭.
		SI32 SetBuffKindArray[BUF_END];		
		ZeroMemory(SetBuffKindArray, sizeof(SetBuffKindArray));
		SI32 SetBuffKindArrayRate[BUF_END];		
		ZeroMemory(SetBuffKindArrayRate, sizeof(SetBuffKindArrayRate));
		SI32 SetBuffNum = 0; 
		for(SI32 Count = 0; Count < BUF_END; ++Count)	
		{
			if(0 >= BuffKindArray[Count])
				break;

			// �̹� ������� ������ ����.
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

	// �����귿�� ����ǰ� ������ �����Ǿ ������ �����Ѵ�.
	if(false == pclInfo->m_bAction && -1 < pclInfo->m_BuffKind)
	{
		SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		if ( siPersonID <= 0 ) 
			return ;

		// ���� DB�� �������� ��� ���̸�, ó������ �ʴ´�.
		if( pclchar->IsNowAddBufThroughDB() == true )			return;

		// ���� �����ؼ� ����� �� ����.
		if( TABS(pclInfo->m_Money) > pclCM->CR[id]->pclCI->clIP.GetMoney() )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY, 0, 0, pclchar->GetCharUnique() );
			return;
		}

		SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48�а����
		
		SI16 siPercent = 0; //Ÿ�Կ� ���� ����.

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
		
		//[����] �����귿�� ����Ͽ� �� ���� ������ ������ ���� ����.
		sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BUFF_ROULETTE, pclInfo->m_Money);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		// �����귿�� �̿��Ͽ� ������ �ݾ��� ���.
		pclDelMoneyStatistics->Add(DELMONEY_BUFF_ROULETTE, pclInfo->m_Money);

		// ������ �귿���� ���� ������ ������ ����.
		//KHY - 1113 - ũ�������� �̺�Ʈ - ũ���������� ���� �� ������ ����.
		if( pclEventTimeManager->InEventTime("ChristmasEvent", &sTime) )
		{
			if(CompleteBuffKind ==ITEMUNIQUE(13002)) // �����ۿ� ��÷ �Ǿ���.
			{
				// ������ ����ũ üũ
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( CompleteBuffKind );
				if(ref < 0) return;

				// ������ ����
				if(  pclchar->GiveItem(CompleteBuffKind, 1, INPUTITEMPERSON_OPTION_CHRISTMAS_ROULETTE, 0) == false )
				{
					// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
					SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
					return ;
				}
				
				cltItem clItem;			
				SI16 brareswitch = 0;
				if( pclItemManager->MakeRandItemUnique(CompleteBuffKind, &clItem, 0, 0, &brareswitch, 0, 0, 0, 0, 0, 0) )
				{
					/*
					// ��ǰ �˸� ������ ����Ͽ� ������ ȹ���� �˸���.
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
			else  // ������.
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
					// ���ο� �������� �� �� �ε��� ���.
					index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclInfo->m_BuffKind, false );		
				}

				
				if ( index > -1 )
				{
					// ������ �ش�.
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
				// ���ο� �������� �� �� �ε��� ���.
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


//	[��ȣ_BALANCECURRENCY]
void cltServer::DoMsg_GAMEMSG_REQUEST_BALANCECURRENCY_BUFF(cltMsg* pclMsg,SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_BalanceCurrency_Buff* pclInfo = (cltGameMsgRequest_BalanceCurrency_Buff*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 CompleteBuffKind = 0;
	// Ŭ�󿡼� �귿�� �����Ƿ� �ش� ������ �ش�.
	if(false == pclInfo->m_bAction)
	{
		if(pclInfo->m_Money > pclchar->pclCI->clIP.GetMoney())
		{
			return;
		}

		// ��ü ������ ��ȣ �迭.
		SI32 BuffKindArray[BUF_END];		
		ZeroMemory(BuffKindArray, sizeof(BuffKindArray));

		// ������ ��ȣ�� ���� Ȯ�� �迭.
		SI32 BuffKindArrayRate[BUF_END];	
		ZeroMemory(BuffKindArrayRate, sizeof(BuffKindArrayRate));

		BuffKindArray[0]		= BUF_ATTACKUP;					// ������ ����
		BuffKindArrayRate[0]	= 860;
		BuffKindArray[1]  		= BUF_DEFENSEUP;				// ���� ����.
		BuffKindArrayRate[1]	= 860;
		//BuffKindArray[2]  		= BUF_SPEEDUP;					// ���ǵ尡 ����
		//BuffKindArrayRate[2]	= 900;
		BuffKindArray[2]  		= BUF_MAKEEXPUP;				// ���� ����ġ ����.
		BuffKindArrayRate[2]	= 350;
		BuffKindArray[3]  		= BUF_NOFIRSTATTACK;			// ���� ���� ȿ��.
		BuffKindArrayRate[3]	= 550;
		BuffKindArray[4]  		= BUF_SUMMONATACUP;				// ��ȯ�� ��ȭ. 
		BuffKindArrayRate[4]	= 710;
		BuffKindArray[5]  		= BUF_LOVEPOWER;				// ��� ����		
		BuffKindArrayRate[5]	= 150;
		BuffKindArray[6]  		= BUF_FRIENDSHIP;				// ���� ����
		BuffKindArrayRate[6]	= 200;
		BuffKindArray[7]  		= BUF_HINAMOCHI;				// ���κ��� ����ũ ȿ��.
		BuffKindArrayRate[7]	= 150;
		BuffKindArray[8]  		= BUF_SUCCESS_MANUFACTURE;		// ������ ���� 100% ����.
		BuffKindArrayRate[8]	= 700;
		BuffKindArray[9] 		= BUF_FOURLEAF;					// ����Ŭ�ι� - ������ ����� 2��.
		BuffKindArrayRate[9]	= 70;
		BuffKindArray[10] 		= BUF_PREMIUMEXPUP;				// ����ġ 150% ȹ��.
		BuffKindArrayRate[10]	= 300;
		BuffKindArray[11]		= BUF_FARMINGNMININGFOREVER;	// �谡 �Ȱ����� �������� - ���� �ʴ´�,
		BuffKindArrayRate[11]	= 600;

		SI32 TotalRate = 0;

		// ���õ� ������ ��ȣ �迭.
		SI32 SetBuffKindArray[BUF_END];		
		ZeroMemory(SetBuffKindArray, sizeof(SetBuffKindArray));
		SI32 SetBuffKindArrayRate[BUF_END];		
		ZeroMemory(SetBuffKindArrayRate, sizeof(SetBuffKindArrayRate));
		SI32 SetBuffNum = 0; 
		for(SI32 Count = 0; Count < BUF_END; ++Count)	
		{
			if(0 >= BuffKindArray[Count])
				break;

			// �̹� ������� ������ ����.
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

	//	[��ȣ_BALANCECURRENCY] Client�κ��� ��û�� ��ȭ������NPC ������� ��밡����ȭ�� ����
	cltGameMsgResponse_BalanceCurrency_Buff	Roulette(pclInfo->m_bAction, pclchar->GetCharUnique(), CompleteBuffKind);
	cltMsg clMsg( GAMEMSG_RESPONSE_BALANCECURRENCY_BUFF, sizeof(Roulette), (BYTE*)&Roulette );
	pclchar->SendNeighbourMsg(&clMsg, true);  

	// �����귿�� ����ǰ� ������ �����Ǿ ������ �����Ѵ�.
	if(false == pclInfo->m_bAction && -1 < pclInfo->m_BuffKind)
	{
		SI32 siPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		if ( siPersonID <= 0 ) 
			return ;

		// ���� DB�� �������� ��� ���̸�, ó������ �ʴ´�.
		if( pclchar->IsNowAddBufThroughDB() == true )			return;

		// ���� �����ؼ� ����� �� ����.
		if( TABS(pclInfo->m_Money) > pclCM->CR[id]->pclCI->clIP.GetMoney() )
		{
			SendServerResponseMsg( 0, SRVAL_FAIL_WORLDMONEY_BUYORDER_NOMONEY, 0, 0, pclchar->GetCharUnique() );
			return;
		}

		SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48�а����

		SI16 siPercent = 0; //Ÿ�Կ� ���� ����.

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

		// �����귿�� ����Ͽ� �� ���� ������ ������ ���� ����.
		sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BUFF_ROULETTE, pclInfo->m_Money);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		
		//	��ȭ����� NPC���� ����� Money �α� ����
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



		//[��ȣ] ��ȭ�� ���� - ��밡�� ��ȭ�� ����
		GMONEY siMoney = m_pclBalanceCurrencyMgr->GetCanUseMoney() + pclInfo->m_Money;
		sDBRequest_SetBalanceCanUseCurrency clMsg2(siMoney, id);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);

	
		// �����귿�� �̿��Ͽ� ������ �ݾ��� ���.
		pclDelMoneyStatistics->Add(DELMONEY_BUFF_ROULETTE, pclInfo->m_Money);



		// ������ �귿���� ���� ������ ������ ����.

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
			// ���ο� �������� �� �� �ε��� ���.
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

	// ĳ���� Ȯ��
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;
	
	//  �̼�����Ʈ�� �þ�� ���⸦ �˴� ���� .
	// ĳ���Ͱ� ������ �ִ� ����Ʈ ������ Ȯ���Ѵ�.
	// ĳ���Ͱ� ������ �ִ� ����Ʈ������ �̻��� ��쿡�� ������ �����Ѵ�.
	if( (pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique > 0 || pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique > 0) &&
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique != pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique )
	{
		// �̻������� �α׷� ����Ѵ�.
		pclLog->FilePrint("Config\\QuestError.log", "Name[%s], Mission1QuestUnique[%d, %d]", pclchar->GetName(),
							pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique,
							pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique );

		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();
	}

	// ���� �����ϰ� �ִ� �̼��� ����ϰ� �ϼž� �մϴ�.
	if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique > 0)
	{
		if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestStep == QUEST_STEP_MIDDLE )
			return;
	}

	// �̼� ����Ʈ ����
	if( pclchar->MakeMissionQuest(pclInfo->m_siMissionUnique) == false )				return;

	cltGameMsgResponse_MissionQuest_Start clMissionQuest_Start( pclInfo->m_siMissionUnique, &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
	cltMsg clMsg(GAMEMSG_RESPONSE_MISSIONQUEST_START, sizeof(cltGameMsgResponse_MissionQuest_Start), (BYTE*)&clMissionQuest_Start );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_ACCEPT(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_MissionQuest_Accept* pclInfo = (cltGameMsgRequest_MissionQuest_Accept*)pclMsg->cData;

	// ĳ���� Ȯ��
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;
    
	// ���� ������ �̼�����Ʈ�� ��û�� ����Ʈ�� ���� ������ Ȯ��
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

	// �̼� ����Ʈ ������ DB�� �����Ѵ�.
	sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

	// ����Ʈ ���¸� DB�� �����Ѵ�.
	sDBRequest_SetQuestInfo clQuestInfo(pclchar->pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
	pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

	// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
	pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MISSIONQUEST_CANCEL(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_MissionQuest_Cancel* pclInfo = (cltGameMsgRequest_MissionQuest_Cancel*)pclMsg->cData;

	// ĳ���� Ȯ��
	if( pclCM->IsValidID(id) == false )												return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);		if(pclchar == NULL)		return;

	// ���� ������ �̼�����Ʈ�� ��û�� ����Ʈ�� ���� ������ Ȯ��
	if( pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique != pclInfo->m_siMissionUnique )						return;
	//if( pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique != pclInfo->m_siMissionUnique )	return;

	// ������ ����Ʈ �ʱ�ȭ
	if ( MISSIONQUEST_UNIQUE_HOLLOWEEN == pclInfo->m_siMissionUnique )
	{
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].Init();

		// �̼� ����Ʈ ������ DB�� �����Ѵ�.
		sDBRequest_SetMissionQuestInfo clMissionQuestInfo(pclchar->pclCI->GetPersonID(), &pclchar->pclCI->clQuestInfo.clMissionQuestInfo );
		pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clMissionQuestInfo);

		// ����Ʈ ���¸� DB�� �����Ѵ�.
		sDBRequest_SetQuestInfo clQuestInfo(pclchar->pclCI->GetPersonID(), QUEST_TYPE_MISSION1, &pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1]);
		pclClient->SendDBMsg(DBSELECT_SUB, (sPacketHeader*)&clQuestInfo);

		// Ŭ���̾�Ʈ�� ����Ʈ�� ���¸� �뺸�Ѵ�. 
		pclchar->SetUpdateSwitch(UPDATE_QUEST, true, 0);
	}
	// clMissionQuestInfo�� ������ ���� ������ �ִ� �̼� ������ ���� �Ѵ�.
	else if ( MISSIONQUEST_UNIQUE_REMOVE_UNLUCK == pclInfo->m_siMissionUnique )
	{
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.Init();
		
		// ����Ʈ�� ���� ������ ���Ѵ�. 
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.siUnique								=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siCurQuestUnique;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siFlag		=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestCmd;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara1	=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestPara1;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestClearConditionInfo.siPara2	=	pclchar->pclCI->clQuestInfo.clUnit[QUEST_TYPE_MISSION1].siQuestPara2;

		// �̼� �Ϸ� ���� �ð��� �����Ѵ�
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.SetLeftTime( 50000 );	// �ð����� ���� ���Ƿ� ����.

		// ������ ���Ѵ�. 
		cltQuestRewardInfo clrewardinfo;
		clrewardinfo.bDeBuff = true;
		pclchar->pclCI->clQuestInfo.clMissionQuestInfo.clQuestRewardInfo.Set( &clrewardinfo );
	}
}

//����ã�� �̺�Ʈ 
void cltServer::DoMsg_GAMEMSG_REQUEST_TREASUREEVENT_KILLNPC(cltMsg* pclMsg, SI32 id )
{
	cltServer* pclserver = (cltServer*)pclClient;
	// �� �޼����� ���� �ش� ID�� npc�� ���̰� �������� �ش�.
	// �׸��� �ٽ� ���ο� �� �ϳ��� �����.
	cltGameMsgRequest_TreasureEvent_Npc_Kill* pclInfo = (cltGameMsgRequest_TreasureEvent_Npc_Kill*)pclMsg->cData;
	SI32 siEventNPC_ID_FromClient = pclInfo->m_siNPC_CharUnique	;
	cltCharServer* pclChar = pclCM->GetCharServer( siEventNPC_ID_FromClient)	;
	if ( pclChar == NULL	 )	return	;
	// �������� �ش� �ش� ��������

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
	// �׿� ������� ������.
	cltGameMsgResponse_IncLife clInfo(pclChar->GetCharUnique(), 0, 0, 0, 0, INCLIFE_REASON_TIMEOUT);
	cltMsg clMsg(GAMEMSG_RESPONSE_INCLIFE, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNeighbourMsg(&clMsg, true);

	pclChar->SetLife(0);
	pclserver->Write_Kill_NPC_Num(pclChar->GetMapIndex())	;// ������� ����Ѵ�.

}
void cltServer::DoMsg_GAMEMSG_REQUEST_CHAR_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	SI16		siCharKind[31];
	SI16		siPercent[31];
	SI32		siCharRouletteCount = 0;

	cltGameMsgRequest_Char_Roulette* pclInfo = (cltGameMsgRequest_Char_Roulette*)pclMsg->cData;

	// ĳ���� Ȯ��
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

			// PCK : ���� ���� 5�� �߰� (09.08.07)
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

			// �ҷ��� ���� ����
			// PCK - ���� ȹ�� Ȯ�� 1% -> 0.5%���� ���� (09.08.06)
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
			// ������ ī�ε尡 �ƴϸ� ��ҵȴ�.
			if( pclInfo->m_siRequestKind != pclchar->siCharRouletteValue )
			{
				cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_END, 0, NULL, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
				pclchar->SendNeighbourMsg(&clMsg, true);

				return;
			}

			// ���� DB�� �������� ��� ���̸�, ó������ �ʴ´�.
			if( pclchar->IsNowAddBufThroughDB() == true )			return;

			// ���ݾ� ���
			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			GMONEY siPrice = 0;

			// ��� : �Ϻ��� ���� �ҷ��� �귿������ �ݾ��� �ٸ��� ���Ѵ�.
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

				// KHY - 1021 - NPCRate �� Ȯ��.
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

				// KHY - 1021 - NPCRate �� Ȯ��.
				else if	(npcrate < 4000)	{		siPrice = -10000000;	}
				else if	(npcrate < 5500)	{		siPrice = -13000000;	}
				else if	(npcrate < 8500)	{		siPrice = -18000000;	}
				else if	(npcrate < 14500)	{		siPrice = -25000000;	}
				else if	(npcrate < 25500)	{		siPrice = -40000000;	}
				else if	(npcrate < 33500)	{		siPrice = -58000000;	}
				else						{		siPrice = -85000000;	}
			}

			// �ƹ� �����̳� ���ԵǾ� ������, ���󰡰�
			if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			{
				// �귿�� ������ �ִ� ������ ���Ե� ������ ���ٸ�, 0.7�� ����
				if( pclchar->GetMapIndex() == pclchar->pclCI->clBI.siHomeVillage)
				{
					siPrice *= 0.7;
				}
			}
			else
			{
				// ������ �������� �Ǿ����� ������ 1.5�� ����
				siPrice *= 1.5;
			}

			// [���] üũ���� �ٽ� ���� - �д밡 ������ ���� ������ ������� �д븦 �Ҹ��ؼ� ������.
			bool	bHaveTicket = false;

			// �д밡 �ִٸ�
			if(pclInfo->b_bUseTicketItem == true)
			{
				// ���� �д밡 �ִ���, �ִٸ� 100�� �̻� ������ �ִ��� üũ

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
			// �д밡 ���ٸ�
			else 
			{
				// ���� ���� : ���� ���� ���� ������ �ִ��� ���� Ȯ��
				// ���� ������ �ִ� �ݾ��� ���ٸ� ����.
				if(siPrice > pclchar->pclCI->clIP.GetMoney() || (pclchar->pclCI->clIP.GetMoney() + siPrice) < 0 || pclchar->pclCI->clIP.GetMoney() == 0)
				{
					 return;
				}
					
			}

			bool bGiveItem = false;
			if( pclInfo->m_siRequestKind > 10000 )			bGiveItem = true;

			// ������ ��ȿ�� üũ
			if( bGiveItem )
			{
				// ������ ����ũ üũ
				SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclInfo->m_siRequestKind );
				if(ref < 0)																					return;
			}
			else
			{
				// ���� ĳ���� ī�ε� üũ
				if( pclClient->pclKindInfoSet->IsValidKind( pclInfo->m_siRequestKind ) == false )			return;
			}

			SI16 index = -1;
			index = pclchar->pclCI->clBI.clBufInfo.FindBufSlot(BUF_TRANSFORM);
			if ( index > -1 )
			{
				// ������ �ɷ��ִ� ������ �����Ѵ�.
				stBuf DelBuf(pclchar->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0);
				sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index, &DelBuf );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}

			if( bGiveItem )
			{
				// ������ ����
				if(  pclchar->GiveItem(pclInfo->m_siRequestKind, 1, INPUTITEMPERSON_OPTION_CHAR_ROULETTE, 7) == false )
				{
					// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
					SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
					return ;
				}
			}
			else
			{
				if( index < 0 )
				{
					// ���ο� ���� ����
					index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_TRANSFORM, false );		
				}

				if ( index > -1 )
				{
					SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48�а����

					stBuf addBuf(BUF_TRANSFORM, pclchar->siCharRouletteValue, usetime, 0);
					((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
				}
			}

			// PCK : �д� �������� �ִ��� Ȯ���ϰ� ������ �Ҹ��Ų��. (�����ݾ׺��� ���� ó��)

			if(pclInfo->b_bUseTicketItem) // ������ ���ÿ� ���� �ٸ���.
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
				//[����] ĳ���ͺ��ŷ귿�� ����Ͽ� �� ���� ������ ������ ���� ����.
				sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_CHAR_ROULETTE, siPrice);
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				// �����귿�� �̿��Ͽ� ������ �ݾ��� ���.
				pclDelMoneyStatistics->Add(DELMONEY_CHAR_ROULETTE, siPrice);
			}

			// �ʱ�ȭ
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
					// ��ǰ �˸� ������ ����Ͽ� ������ ȹ���� �˸���.
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
			// �ʱ�ȭ
			pclchar->siCharRouletteValue = 0;

			cltGameMsgResponse_Char_Roulette clCharRoulette(pclchar->GetCharUnique(), CHAR_ROULETTE_END, 0, NULL, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_CHAR_ROULETTE, sizeof(clCharRoulette), (BYTE*)&clCharRoulette );
			pclchar->SendNeighbourMsg(&clMsg, true);
		}
		break;
	}
}
// NEW PVP - �ռ��� 2008.10.08
void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_FILED(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_PVP_Request* pclInfo = (cltGameMsgRequest_PVP_Request*)pclMsg->cData;
	 if ( pclClient->IsCountrySwitch(Switch_IKillU) ==	false )				return	;
	switch( pclInfo->siRequestType)
	{
	case REQUEST_PVP :// PVP�� ��û �ߴ�.
		{
			SI32 siMyId		=	id	;					// �� ID
			SI32 siEnermyId =	pclInfo->siPara1	;	// ������ ���� �ɸ��� ����ũ
			// ĳ���� Ȯ��
			if( pclCM->IsValidID( siMyId ) == false )			return;
			if( pclCM->IsValidID( siEnermyId ) == false )		return;	//pvp�� �� ����� IDȮ��.
			// ��������� Ȯ��
			if( pclCM->IsAlive( siMyId ) == false )			return;
			if( pclCM->IsAlive( siEnermyId ) == false )		return;	//pvp�� �� ����� IDȮ��.

			cltCharServer* pclmychar = pclCM->GetCharServer(siMyId);			if(pclmychar == NULL)			return;
			cltCharServer* pclEnemychar = pclCM->GetCharServer(siEnermyId);		if(pclEnemychar == NULL)		return;
			//. ���縮�������� ��û �Ұ��� 
			if( pclmychar->GetMapIndex() == MAPINDEX_PALACE || pclEnemychar->GetMapIndex() == MAPINDEX_PALACE )	return	;
			// ���� ���ϱ� �̺�Ʈ ���̸� �Ұ�,�� 
			if( pclmychar->GetMapIndex() == MAPINDEX_FESTIVAL || pclEnemychar->GetMapIndex() == MAPINDEX_FESTIVAL )	return	;
			// ���� �ϳ��� pk���̸� ��û�Ұ���
			if ( pclMapManager->IsPkMap(pclmychar->GetMapIndex()) == true )										return	;
			if ( pclMapManager->IsPkMap(pclEnemychar->GetMapIndex()) == true )									return	;
			if (pclmychar->bPersonalShopSwitch	==	 true ) return	;;
			if (pclmychar->bPremiumPersonalShop	==	 true ) return	;
			if (pclEnemychar->bPersonalShopSwitch	==	 true ) return	;
			if (pclEnemychar->bPremiumPersonalShop	==	 true ) return	;
			/*if ( pclClient->pclMapManager->IsCanMarketOpenMap( pclmychar->GetMapIndex() ) == true ||
				pclClient->pclMapManager->IsCanMarketOpenMap( pclEnemychar->GetMapIndex() ) == true )			return ;*/
			// �̺�Ʈ ��Ÿ�� ����� ��û �Ұ���
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
				// ���� �ϳ��� pvp ���̶�� ��û �Ұ��� �մϴ�
				return	;
			}
			bool bNowEnermyPVPsetting = pclCM->CR[ siEnermyId ]->pclCI->clCharOption.GetPVPMode() ;

			// �̹� ��������� ������ ���ʿ� ��⸦ �Ҽ� ����.
			if ( pclCM->CR[ siMyId ]->siEnemUnique >0 || pclCM->CR[ siEnermyId ]->siEnemUnique > 0 )		return	;

			if (  bNowEnermyPVPsetting == false )	// PVP�� ���� ���� �ʴ´�. �޴����� PVP ��� ������ .
			{
				//	���濡�� ok �Ҳ��� ����� â�� ����.
				cltGameMsgResponse_PVP_Request clResponsePvp( REQUEST_PVP , siMyId,0,(TCHAR*)pclCM->CR[id]->GetName() );
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clResponsePvp), (BYTE*)&clResponsePvp );
				pclEnemychar->SendNetMsg((sPacketHeader*)&clMsg);
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : �ռ����� 2008. 10. 29] // pvp Ÿ�ٿ� ��û
					// Ÿ�� personID 
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_REQUEST, 
						0, pclmychar,NULL , pclEnemychar->pclCI->GetPersonID(), 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						0, 0, 0, 0, 0, NULL, NULL);
				}
				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
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
	case REFUSE_PVP://������ ���� ���� �̴�.
		{
			SI32 siRequestId			=	pclInfo->siPara1	;		// PVP ��û�� ��� ID
			SI32 siAcceptId				=	id	;						// PVP ��û�� ���� �ѻ��

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// ����� ����� �������� ID�ΰ� Ȯ��
						
			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)		return;
			cltCharServer* pclRefuseChar = pclCM->GetCharServer(siAcceptId);			if(pclRefuseChar == NULL)		return;
			// ��û�� ������� ���� ���ߴٴ� �޼����� �����ش�.
			cltGameMsgResponse_PVP_Request clAcceptToRequest( REFUSE_PVP ,siAcceptId,0,TEXT(""));
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
			pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg);
			{
				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
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
	case READY_PVP:// 5�� ��� �ϱ� ���ؼ� ��� �޼����� ������.
		{
			SI32 siRequestId			=	pclInfo->siPara1	;	// PVP ��û�� ��� ID
			SI32 siAcceptId				=	id	;						// PVP ��û�� �޾Ƽ� ok �� ��� ID

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// ����� ����� �������� ID�ΰ� Ȯ��

			// ��� ������ Ȯ��
			if( pclCM->IsAlive( siRequestId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsAlive( siAcceptId ) == false )		return;	// ����� ����� �������� ID�ΰ� Ȯ��

			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)		return	;
			cltCharServer* pclAcceptChar = pclCM->GetCharServer(siAcceptId);			if(pclAcceptChar == NULL)		return	;			
			
			// �̹� ���� �ϳ��� ���� ���� �Ǹ� ���۵� ����� �����ÿ��� ������ �ʴ´�.
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
				pclCM->CR[ siRequestId ]->siPVPWaitRequestId	=	pclInfo->siPara1			;// PVP ��û�� ��� ID
				pclCM->CR[ siRequestId ]->siPVPWaitAcceptId		=	id			;// PVP ��û�� �޾Ƽ� ok �� ��� ID
				pclCM->CR[ siAcceptId ]->siPVPWaitRequestId	=	pclInfo->siPara1			;// PVP ��û�� ��� ID
				pclCM->CR[ siAcceptId ]->siPVPWaitAcceptId		=	id			;// PVP ��û�� �޾Ƽ� ok �� ��� ID

				// ���� Ŭ���̾�Ʈ�� �˷��ش�.
				// ��û�� �������
				cltGameMsgResponse_PVP_Request clAcceptToRequest( READY_PVP ,0,0,TEXT(""));	// ���� ��ٸ���� �޼����� �����ش� ���� �ð��� ������.
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
				pclRequestChar->SendNetMsg((sPacketHeader*)&clMsg);
				//	�³��� �������
				cltGameMsgResponse_PVP_Request clclAcceptToAccepeter( READY_PVP ,0,0,TEXT(""));// ��ٸ���� �޼����� �����ش� �����ð��� ������
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclAcceptToAccepeter), (BYTE*)&clclAcceptToAccepeter );
				pclAcceptChar->SendNetMsg((sPacketHeader*)&clMsg2);
			}
		}
		break;
	case START_PVP://pvp�� �����Ѵ�.
		{
			SI32 siRequestId			=	pclCM->CR[ id ]->siPVPWaitRequestId	;// PVP ��û�� ��� ID
			SI32 siAcceptId				=	pclCM->CR[ id ]->siPVPWaitAcceptId		;// PVP ��û�� �޾Ƽ� ok �� ��� ID			

			if( pclCM->IsValidID( siRequestId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsValidID( siAcceptId ) == false )		return;	// ����� ����� �������� ID�ΰ� Ȯ��
			// ��� ������ Ȯ��
			if( pclCM->IsAlive( siRequestId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsAlive( siAcceptId ) == false )			return;	// ����� ����� �������� ID�ΰ� Ȯ��
			// ���� ���̵��� ���� �ش� �ɸ��Ͱ� PVP ������ ��Ī����Ʈ�� ���� �ϴ��� Ȯ���Ѵ�.
			cltCharServer* pclRequestChar = pclCM->GetCharServer(siRequestId);			if(pclRequestChar == NULL)	return	;
			cltCharServer* pclAcceptChar = pclCM->GetCharServer(siAcceptId);			if(pclAcceptChar == NULL)	return	;

			if ( pclCM->CR[ siRequestId ]->siEnemUnique >0 || pclCM->CR[ siAcceptId ]->siEnemUnique > 0 )			return	;
			// ���� �ʿ� ���� ������ ������� �ʵ��� �Ѵ�
			if( pclRequestChar->GetMapIndex() !=pclAcceptChar->GetMapIndex() )
			{
				{
					// ������ �����.
					TCHAR fileNameBuffer[256];
					//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
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
			// ��û �ѳ��̳� ��û �������� ���縮���� ������ ���� �Ұ��� 
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
				// PVP�� �³� �Ͽ����Ƿ� ���ο��� ������ ID�� ������ش�
				pclRequestChar->siEnemUnique	=	siAcceptId	;
				pclAcceptChar->siEnemUnique		=	siRequestId	;
				pclRequestChar->ParametaBoxAction()	;			
				pclAcceptChar->ParametaBoxAction();
				pclRequestChar->IncreaseLife( pclRequestChar->clPB.GetMaxLife() )	;
				pclAcceptChar->IncreaseLife( pclAcceptChar->clPB.GetMaxLife() )		;
				// ���� Ŭ���̾�Ʈ�� �˷��ش�.
				// ��û�� �������
				cltGameMsgResponse_PVP_Request clAcceptToRequest( START_PVP , siAcceptId,siRequestId,TEXT("") );	// ������ ������Դ� �¶��� ��� ID
				cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clAcceptToRequest), (BYTE*)&clAcceptToRequest );
				pclRequestChar->SendNeighbourMsg(&clMsg,true);
				//	�³��� �������
				cltGameMsgResponse_PVP_Request clclAcceptToAccepeter( START_PVP , siRequestId,siAcceptId,TEXT("") );// �¶��� ������Դ� ��û�� ��� ID
				cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clclAcceptToAccepeter), (BYTE*)&clclAcceptToAccepeter );
				pclAcceptChar->SendNeighbourMsg(&clMsg2,true);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : �ռ����� 2008. 10. 29] // pvp ���� 
					// Ÿ�� personID 
					//pclRequestChar �� ��û�ѻ��
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_START, 
						0, pclRequestChar,NULL, pclAcceptChar->pclCI->GetPersonID() , 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
						0, 0, 0, 0, 0, NULL, NULL);
				}

				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
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
	case LOSE_PVP://pvp�� �й� ������ �����ؼ� ����,
		{
			SI32 siWinnerId				=	pclInfo->siPara1	;	// PVP ����
			SI32 siLoserId				=	id							;	// PVP ����

			if( pclCM->IsValidID( siWinnerId ) == false )		return;	// ��û�� ����� �������� ID�ΰ� Ȯ��
			if( pclCM->IsValidID( siLoserId ) == false )		return;	// ����� ����� �������� ID�ΰ� Ȯ��

			SI32 siWinnerparent = pclCM->CR[siWinnerId]->GetSummonParentID()	;	// �¸����� parentid
			SI32 siLoserParent = pclCM->CR[siLoserId]->GetSummonParentID()		;	// �й����� parentid

			if( siWinnerparent == 0 ) siWinnerparent = siWinnerId;
			if( siLoserParent == 0 ) siLoserParent = siLoserId;

			cltCharServer* pclWinnerChar = pclCM->GetCharServer(siWinnerparent);			if(pclWinnerChar == NULL)			return;
			cltCharServer* pclLoserChar = pclCM->GetCharServer(siLoserParent);				if(pclLoserChar == NULL)			return;

			// �¸��ڿ� �й����� ������ �� ���̵� �ʱ�ȭ.
			pclWinnerChar->siEnemUnique		=	0		;
			pclLoserChar->siEnemUnique		=	-100	;

			// ���� Ŭ���̾�Ʈ�� �˷��ش�.
			// �¸���
			//>SendNetMsg((sPacketHeader*),>SendNeighbourMsg(
			cltGameMsgResponse_PVP_Request clWinner( END_PVP , WIN_PVP, pclWinnerChar->GetCharUnique(), TEXT(""));	
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clWinner), (BYTE*)&clWinner );
			//pclWinnerChar->SendNetMsg((sPacketHeader*)&clMsg);
			pclWinnerChar->SendNeighbourMsg(&clMsg, true);

			pclWinnerChar->IncQuestPara( QUEST_CLEAR_COND_PVPWIN, 0, 1 );

			// �й���
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

			// ���� ������.
			pclDrawChar1->siEnemUnique		=	0	;
			pclDrawChar2->siEnemUnique		=	0	;
			// ���� Ŭ���̾�Ʈ�� �˷��ش�.
			{//�¸���
				// ���ΰ� pvp�� �����鼭 ���� �ߵ����� ����
				pclDrawChar1->DeletePoison();						// �ߵ� ���¸� �����Ѵ�.
				pclDrawChar1->DeletePoisonSetItemEffect();			// �ߵ� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteIce();							// ���� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteCurseAttack();					// ���ݷ��� ���� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteCurseCritical();				// Critical Ȯ���� �������� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteCurseDefense();					// ������ �������� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteCurseMovespeed();				// �̵��ӵ� ���� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteMagicFire();					// �ҿ� Ÿ�� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteFrozen();						// ���� ���� ���¸� �����Ѵ�.
				pclDrawChar1->DeleteCurseEffect();
			}
			{	// �й���
				// ���ΰ� pvp�� �����鼭 ���� �ߵ����� ����
				pclDrawChar2->DeletePoison();						// �ߵ� ���¸� �����Ѵ�.
				pclDrawChar2->DeletePoisonSetItemEffect();			// �ߵ� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteIce();							// ���� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteCurseAttack();					// ���ݷ��� ���� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteCurseCritical();				// Critical Ȯ���� �������� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteCurseDefense();					// ������ �������� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteCurseMovespeed();				// �̵��ӵ� ���� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteMagicFire();					// �ҿ� Ÿ�� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteFrozen();						// ���� ���� ���¸� �����Ѵ�.
				pclDrawChar2->DeleteCurseEffect();
			}
			cltGameMsgResponse_PVP_Request clDraw1( END_PVP , DRAW_PVP, pclDrawChar1->GetCharUnique() ,TEXT(""));	
			cltMsg clMsg( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clDraw1), (BYTE*)&clDraw1 );
			pclDrawChar1->SendNeighbourMsg(&clMsg,true);
			// �й���
			cltGameMsgResponse_PVP_Request clDraw2( END_PVP , DRAW_PVP, pclDrawChar2->GetCharUnique() ,TEXT(""));
			cltMsg clMsg2( GAMEMSG_RESPONSE_PVP_FILED, sizeof(clDraw2), (BYTE*)&clDraw2 );
			pclDrawChar2->SendNeighbourMsg(&clMsg2,true);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : �ռ����� 2008. 10. 29] // pvp ���
				// para1, para2 : �ο� �λ���� personID
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONALPVP, LOGCOMMAND_INDEX_PERSONALPVP_REQUEST, 
					0, pclDrawChar1 ,NULL , 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					pclDrawChar1->pclCI->GetPersonID(), 
					pclDrawChar2->pclCI->GetPersonID(), 0, 0, 0, NULL, NULL);
			}
			{
				// ������ �����.
				TCHAR fileNameBuffer[256];
				//���Կ� ���� �ð��� �ؽ�Ʈ�� �ϼ��Ѵ�.
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

// PVP_League �ռ��� 2008.11.7
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
	// ���� ������ ��û�ϴ� �κ�
	//-- 
	sDBRequest_PVP_League_UI_InfoGet clMsg( pclchar->pclCI->GetPersonID(), id );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_APPLY(cltMsg* pclMsg, SI32 id)
{
	// PVP ���Ѵ��� ��� �ð����� �� �� �ִ�
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

	// �����Ǿ� �ִ� ���¶�� �̵��� �ȵȴ�.
	if ( pclchar->clInnerStatus.IsStatus(INNERSTATUS_PRISON) )
	{
		return;
	}

	if ( pclchar->pclCI->clIP.GetLevel() < pclClient->GetGlobalValue("GV_PVPLeague_LimitLevel") )
	{
		return;
	}

	//--
	// �̰��� ���� ����Ʈ�� ����ϴ� ���� ������ȴ�
	SI32 siPersonID = pclchar->pclCI->GetPersonID();
	SI16 siGrade	= pclchar->GetPVP_LeagueGrade();
	if ( siGrade == PVP_LEAGUE_GRADE_NONE ) 
	{
		// ����� ���������� �⺻ ���� ������� ���� ��Ų��
		siGrade = Const_PVP_League_Default_Grade;

		sDBRequest_PVP_League_Battle_ChangeGrade clMsg(  siPersonID , siGrade , sTime);
		pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	SI32 siResult	= pclPVP_LeagueMgr->AddReserveList( siPersonID, siGrade );
	SI32 siCount	= pclPVP_LeagueMgr->GetRerserveListCount();	// ������ ���� ��� �ο��̶�� ���� �����ϴ�
	//--

	if ( PVP_LEAGUE_APPLY_RESULT_SUCCESS == siResult )
	{
		pclchar->DoQuestCheckAndAction( QUEST_CLEAR_COND_PVPLEAGUERESERVE );
	}

	//--
	// �̰��� ������� �����ִ� �κ�
	SendServerResponseMsg( 0, SRVAL_PVP_LEAGUE_APPLY_MESSAGE, siResult, siCount, pclchar->GetCharUnique() );
	//--
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PVP_LEAGUE_CANCEL(cltMsg* pclMsg, SI32 id)
{
	// PVP ���Ѵ��� ��� �ð����� �� �� �ִ�
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
	// �̰��� ���� ����Ʈ���� �����ϴ� ���� ������ �ȴ�
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

	// PVP ���Ѵ��� ���� �ð����� �� �� �ִ�
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
// �߷�Ÿ�ε��� ���� �亯 
void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_REQUEST(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_ValentineWar_Request* pclInfo = (cltGameMsgRequest_ValentineWar_Request*)pclMsg->cData;
	cltCharServer* pclChar = pclCM->GetCharServer( id)	;

	cltValentineWarInfo clvaletineinfo;
	switch( pclInfo->siCouple) 
	{
	case VALENTINEWAR_NONE : // �� ����ϱ� �ȴ�
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_NONE )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
			//���� �Ȱ��� ���� ������.
		}
		break;
	case VALENTINEWAR_COUPLE :	// �� Ŀ���̴�	
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_COUPLE )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
		}
		break;
	case VALENTINEWAR_SOLO :	// �� �ַδ�.
		{
			clvaletineinfo.SetCouple( VALENTINEWAR_SOLO )	;
			clvaletineinfo.SetAnswerTime( sTime)	;
			clvaletineinfo.SetPrize(false);
		}
		break;
	}
	// �ϴ� ���� �ΰ�~�ٷ� ��񿡼� �����Ÿ� ��������.
	sDBRequest_Valantine_Request clMsg( pclChar->pclCI->GetPersonID(), clvaletineinfo );
	pclGameDBProcess->SendMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
}
// �ɸ��� ������ �޴´�.
void cltServer::DoMsg_GAMEMSG_REQUEST_VALENTINEWAR_INFOGET(cltMsg* pclMsg,SI32 id)
{
	cltGameRequest_ValentineWar_Info_get* pclInfo = (cltGameRequest_ValentineWar_Info_get*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer( id)	;
	// [����] �߷�Ÿ�� ���� ���� ��û
	sDBRequest_Valantine_Info_Get clValantineInfo( pclChar->pclCI->GetPersonID() );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clValantineInfo);

}
void cltServer::DoMsg_GAMEMSG_REQUEST_DIVINATION_ROULETTE(cltMsg* pclMsg,SI32 id)
{
	SI16		siCharKind[50];
	SI16		siPercent[50];
	SI32		siCharRouletteCount = 0;

	cltGameMsgRequest_Divination_Roulette* pclInfo = (cltGameMsgRequest_Divination_Roulette*)pclMsg->cData;

	// ĳ���� Ȯ��
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
			
			// [���] - ���� �߰�

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
			// ������ ī�ε尡 �ƴϸ� ��ҵȴ�.
			if( pclInfo->m_siRequestDivination != pclchar->siDivinationValue )
			{
				cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_END, 0, NULL, 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
				pclchar->SendNeighbourMsg(&clMsg, true);

				return;
			}

			// ���� DB�� �������� ��� ���̸�, ó������ �ʴ´�.
			if( pclchar->IsNowAddBufThroughDB() == true )			return;

			// ���ݾ� ���
			SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
			SI64 siPrice = 0;

			// ����� ���
			if		(npcrate < 100)		{		siPrice = -500000;	}
			else if	(npcrate < 300)		{		siPrice = -1000000;	}
			else if	(npcrate < 700)		{		siPrice = -1500000;	}
			else if	(npcrate < 1000)	{		siPrice = -2000000;	}
			else if (npcrate < 1450)    {		siPrice = -2500000;	}
			else if (npcrate < 1750)	{		siPrice = -3000000;	}
			else if	(npcrate < 2050)	{		siPrice = -3500000;	}
			else if (npcrate < 2350)	{		siPrice = -4000000;	}
			else if	(npcrate < 3000)	{		siPrice = -4500000;	}

			// KHY - 1021 - NPCRate �� Ȯ��.
			else if	(npcrate < 4000)	{		siPrice = -5000000;	}
			else if	(npcrate < 5500)	{		siPrice = -7500000;	}
			else if	(npcrate < 8500)	{		siPrice = -12000000;	}
			else if	(npcrate < 14500)	{		siPrice = -20000000;	}
			else if	(npcrate < 25500)	{		siPrice = -38000000;	}
			else if	(npcrate < 33500)	{		siPrice = -50000000;	}
			else						{		siPrice = -70000000;	}

			//// �ƹ� �����̳� ���ԵǾ� ������, ���󰡰�
			//if( pclchar->pclCI->clBI.siHomeVillage > 0 )
			//{
			//	// �귿�� ������ �ִ� ������ ���Ե� ������ ���ٸ�, 0.7�� ����
			//	if( pclchar->GetMapIndex() == pclchar->pclCI->clBI.siHomeVillage)
			//	{
			//		siPrice *= 0.7;
			//	}
			//}
			//else
			//{
			//	// ������ �������� �Ǿ����� ������ 1.5�� ����
			//	siPrice *= 1.5;
			//}

			if(siPrice > pclchar->pclCI->clIP.GetMoney())
			{
				// ���� ��� ������ ���� ���Ѵ�.
				return;
			}

			//	��� : ����Ÿ�Կ� ���� ó���Ѵ�.

			// �ų��귿 ������ �ɷ������� ������ �Ѵ�.
			// �� ���� Ÿ���� ������ �����̸� �������� �ʴ´�.
			SI16 index = -1;			
			index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindBufGetTypeSlot(BUF_GET_TYPE_NEWYEAREVENT);
			if ( index > -1 && pclInfo->m_siBufKind_Type != BUFKIND_ITEM)
			{
				// ������ �ɷ��ִ� ������ �����Ѵ�.
				stBuf DelBuf(pclchar->pclCI->clBI.clBufInfo.m_stBuf[index].siBufType, 0, 0, 0);
				sDBRequest_DeleteBuf clMsg( pclchar->pclCI->GetPersonID(), index, &DelBuf );
				pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}

			switch(pclInfo->m_siBufKind_Type)
			{
			case BUFKIND_CHAR:
				{
					// ���� ĳ���� ī�ε� üũ
					if( pclClient->pclKindInfoSet->IsValidKind( pclInfo->m_siRequestDivination ) == false )			return;

					if ( index < 0)
					{
						// ���ο� ���� ����
						index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( BUF_TRANSFORM, false );		
					}

					if ( index > -1 )
					{
						SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48�а����

						stBuf addBuf(BUF_TRANSFORM, pclchar->siDivinationValue, usetime, BUF_GET_TYPE_NEWYEAREVENT);
						((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
					}
				}
				break;
			case BUFKIND_ITEM:
				{
					// ������ ����ũ üũ
					SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclInfo->m_siRequestDivination );
					if(ref < 0)																	return;

					// ������ ����

					// ������ ��쿡�� ������ 1~5�� �����ϰ� �ش�.
					if(pclInfo->m_siRequestDivination == 3770)
					{
						SI32 siRand = 1+ (rand() % 4);

						if(  pclchar->GiveItem(pclInfo->m_siRequestDivination, siRand, INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE, 0) == false )
						{
							// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
							SendServerResponseMsg(0, SRVAL_ADDINV_FAIL_FULL,  0, 0, pclCM->CR[id]->GetCharUnique());
							return ;
						}
					}
					else
					{
						if(  pclchar->GiveItem(pclInfo->m_siRequestDivination, 1, INPUTITEMPERSON_OPTION_NEWYEAREVENT_ROULETTE, 0) == false )
						{
							// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
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
						// ���ο� ���� ����
						index = pclCM->CR[id]->pclCI->clBI.clBufInfo.FindEmptySlot( pclchar->siDivinationValue, false );		
					}

					SI16 siPercent = 0; //Ÿ�Կ� ���� ����.

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
						SI32 usetime	= ((cltServer*)pclClient)->pclTime->clDate.GetHourVary() + 24; // 48�а����

						stBuf addBuf(pclchar->siDivinationValue, siPercent, usetime, BUF_GET_TYPE_NEWYEAREVENT);
						((cltCharServer*)pclCM->CR[id])->AddBufThroughDB( index, &addBuf , false, 0, NULL, 0);
					}
				}
				break;
			}


			// ��޽����� ������.

			if(pclInfo->m_siBufKind_Type != 0)
			{
				SendServerResponseMsg(0, SRVAL_DIVINATION_MSG,  0, 0, pclCM->CR[id]->GetCharUnique());
			}

//-----------------------------------
			//[����] ĳ���ͺ��ŷ귿�� ����Ͽ� �� ���� ������ ������ ���� ����.
			sDBRequest_ChangeMoney clMsg( id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_CHAR_ROULETTE, siPrice);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			// �����귿�� �̿��Ͽ� ������ �ݾ��� ���.
			pclDelMoneyStatistics->Add(DELMONEY_NEWYEAREVENT_ROULETTE, siPrice);

			// �ʱ�ȭ
			pclchar->siDivinationValue = 0;

			cltGameMsgResponse_Divination_Roulette clDivinationRoulette(pclchar->GetCharUnique(), DIVINATION_ROULETTE_END, 0, NULL, 0);
			cltMsg clDivinationRouletteMsg(GAMEMSG_RESPONSE_DIVINATION_ROULETTE, sizeof(clDivinationRoulette), (BYTE*)&clDivinationRoulette );
			pclchar->SendNeighbourMsg(&clDivinationRouletteMsg, true);
		}
		break;

	case DIVINATION_ROULETTE_END:
		{
			// �ʱ�ȭ
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

	// ��� �ɸ��� �̸��� ���ٸ�
	if ( 0 == _tcslen(pclInfo->m_szCharName) )
	{
		return;
	}
	
	// ���� �޽����� ���ٸ�
	if ( 0 == _tcslen(pclInfo->m_szMessage) )
	{
		return;
	}

	cltCharServer* pclMyChar = pclCM->GetCharServer( id );
	if ( NULL == pclMyChar )
	{
		return;
	}

	// �̹� ��ȥ�� �ߴٸ�
	if ( TRUE == pclMyChar->IsMarried() )
	{
		return;
	}

	// ��ȥ�� �� �� �ִ� ������ �ƴ϶��
	if ( Const_Marriage_Min_Level > pclMyChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	// ���� �̿���� ���ٸ�
	if ( 0 >= pclMyChar->pclCI->clCharItem.GetItemNum(Const_Family_Item_Unique) )
	{
		return;
	}

	// �������� ����� ĳ���� ID�� �����´�
	SI32 siProposeID = pclCM->GetIDFromName(pclInfo->m_szCharName);

	// ���� ĳ���Ͱ� �������� �ʰų� �������� �ƴҶ�
	cltCharServer* pclProposeChar = pclCM->GetCharServer( siProposeID );
	if ( NULL == pclProposeChar )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_IS_NOT_VALIDCHAR,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// ����ڰ� �̹� ��ȥ�� �ߴٸ�
	if ( TRUE == pclProposeChar->IsMarried() )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_ALREADY_MARRIED,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// ����ڰ� ��ȥ ���� ������ �ƴ϶��
	if ( Const_Marriage_Min_Level > pclProposeChar->pclCI->clIP.GetLevel() )
	{
		SendServerResponseMsg( 0, SRVAL_FAIL_PROPOSE_LESSTHAN_MARRY_LEVEL,  0, 0, pclMyChar->GetCharUnique() );
		return;
	}

	// ����üũ�� ĳ���� KIND�� üũ�Ѵ�
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
	
	// ûȥ�� �Ѵ�
	TCHAR szCharName[MAX_PLAYER_NAME]			= TEXT("");
	TCHAR szMessage[Const_Max_Propose_Message]	= TEXT("");

	StringCchCopy( szCharName,	sizeof(szCharName),	((TCHAR*)pclMyChar->GetName()) );
	StringCchCopy( szMessage,	sizeof(szMessage),	pclInfo->m_szMessage );

	// ���� �޽����� ���� ����
    m_pCAbuseFilter->CheckAbuse( szMessage );

	// ��Ŷ ������~
	cltGameResponse_Propose_Question clinfo( szCharName, szMessage );
	cltMsg clMsg(GAMEMSG_RESPONSE_PROPOSE_QUESTION, sizeof(clinfo), (BYTE*)&clinfo );
	pclProposeChar->SendNetMsg((sPacketHeader*)&clMsg);

	// ���濡�� ���������� �۽� ���̵� �����Ѵ�
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

	// ûȥ�� ���̵� ���Ѵ�
	SI32 siProposerCharID = pclCM->GetIDFromPersonID( pclMyChar->GetProposePersonID() );

	cltCharServer* pclProposerChar = pclCM->GetCharServer( siProposerCharID );
	if ( NULL == pclProposerChar )
	{
		return;
	}

	// Ȥ�� �𸣴� ���� �����Ǿ��ִ� ûȥ�� �۽� ���̵� ���Ѵ�
	if ( pclMyChar->GetProposePersonID() != pclProposerChar->pclCI->GetPersonID() )
	{
		return;
	}

	if ( pclProposerChar->GetProposePersonID() != pclMyChar->pclCI->GetPersonID() )
	{
		return;
	}

	// ������� �����Ͽ��� ��� ���� ĳ���Ϳ��Ը� �޽����� ������
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

	// ��ȥ üũ
	if ( TRUE == pclMyChar->IsMarried() )
	{
		return;
	}

	if ( TRUE == pclProposerChar->IsMarried() )
	{
		return;
	}

	// ���� üũ
	if ( Const_Marriage_Min_Level > pclMyChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	if ( Const_Marriage_Min_Level > pclProposerChar->pclCI->clIP.GetLevel() )
	{
		return;
	}

	// ���� üũ
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

	// ������ üũ
	SI32 siMyItemPos		= pclMyChar->pclCI->clCharItem.FindItemInv( Const_Family_Item_Unique );
	SI32 siProposerItemPos	= pclProposerChar->pclCI->clCharItem.FindItemInv( Const_Family_Item_Unique );

	if ( (-1 >= siMyItemPos) || (-1 >= siProposerItemPos) )
	{
		return;
	}
	
	//=====================================================================
	// �� ��ȥ�� �ʿ��� ��� ������ �����ߴ� ���� ��ȥ�̴�
	//=====================================================================

	// ��ȥ�� �Ҹ�� ������
	cltItem clMyItem;
	
	clMyItem.Init();
	clMyItem.siUnique			= Const_Family_Item_Unique;
	clMyItem.siItemNum			= Const_Family_Item_Num;

	cltItem clProposerItem;

	clProposerItem.Init();
	clProposerItem.siUnique		= Const_Family_Item_Unique;
	clProposerItem.siItemNum	= Const_Family_Item_Num;

	// ��ȥ ����ϼ���
	cltDate clWeddingDate;
	clWeddingDate.Set( &pclTime->clDate );

	// ���� ���� ������
	sDBRequest_Set_Marry clMsg( pclProposerChar->pclCI->GetPersonID(),	&clProposerItem,			siProposerItemPos,	// ûȥ�ѻ��
								pclMyChar->pclCI->GetPersonID(),		&clMyItem,					siMyItemPos,		// ûȥ�������
								MARRIAGE_LOVE_LEVEL_01,					clWeddingDate.GetDateVary()						// ���뼳��
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

	// ��ȥ�� ���ߴµ� �ޱ� ��û�Ѵٸ�
	if ( FALSE == pclMyChar->IsMarried() )
	{
		return;
	}

	SI32 siNowDateVary = pclTime->clDate.GetDateVary();

	// ��ȥ ������� �ƴ϶��
	if ( FALSE == pclMyChar->pclMarriage->IsWeddingAnniversary(siNowDateVary) )
	{
		return;
	}

	// �̹� ��ȥ ����� �������� �޾Ҵٸ�
	if ( TRUE == pclMyChar->pclMarriage->IsWeddingItemGet(siNowDateVary) )
	{
		return;
	}

	// �켱 DB�ٳ���� ���� �� ��û�� ���ü������Ƿ� ������ �ְ�
	pclMyChar->pclMarriage->SetItemGetDateVary( siNowDateVary );

	// ���⿡�� �ٷ� �������� �����Ѵ�
	pclMyChar->GiveItem( Const_WeddingAnniversary_Unique, Const_WeddingAnniversary_Num, INPUTITEMPERSON_OPTION_WEDDINGANNIVERSARY, 0 );

	// DB�� ������ ���� ������ ������
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
//	��ũ��
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
		// ��� ��ɾ ���� �Ű��̴�.

		switch( pclinfo->siResult )
		{
		case 0:

			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_ERROR_UNKNOWN, 0, 0, adminid );

			// �� �� ���� ����

			break;
		case 1:

			// ����

			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_SUCCESS, 0, 0, adminid );

			break;

		case 2:

			// ���� �����
			//SendServerResponseMsg( 0, SRVAL_RECACTION_ORDER_ALREADY_ORDERED, 0, 0, adminid );

			break;	
		}
	}
	else
	{
		// ���ӳ� ���� ������ ���� ĳ����(����, �����Ǽ�, ����)�� ���� �Ű��̴�.

		switch( pclinfo->siResult )
		{
		case 1:

			// ����

			m_pclMacroReportedMgr->OnUserReported( ( ( cltCharServer* )pclCM->CR[ id ] )->pclCI->GetPersonID() );

			//SendServerResponseMsg( 0, SRVAL_REPORTMACRO_SUCCESS, 0, 0, adminid );

			pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "��ũ�� ����� �Ű� [�Ű���:%s][�ǽŰ���:%s] : ����", pclCM->CR[ adminid ]->GetName(),  ( ( cltCharServer* )pclCM->CR[ id ] )->GetName() );

			break;
		case 2:

			// ���� �����
			//SendServerResponseMsg( 0, SRVAL_REPORTMACRO_WORKING, 0, 0, adminid );

			pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "��ũ�� ����� �Ű� [�Ű���:%s][�ǽŰ���:%s] : ���� �����", pclCM->CR[ adminid ]->GetName(),  ( ( cltCharServer* )pclCM->CR[ id ] )->GetName() );

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


		// ��� ��ɾ ���� �Ű��̴�. ��� ������ ���Ϸ� �����Ѵ�.
		// ��ڿ��� ���� �����ϵ��� �����Ѵ�.

		cltGameMsgResponse_RecordActionFinished		clinfo( szcharname, pclinfo->szFilePath );
		cltMsg msg( GAMEMSG_RESPONSE_RECORD_ACTION_FINISHED, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[ adminid ]->SendNetMsg((sPacketHeader*)&msg );
	}
	else
	{
		// ���ӳ� ���� ������ ���� ĳ����(����, �����Ǽ�, ����)�� ���� �Ű��̴�.
		// ��� ������ �޸𸮿� �����Ѵ�.
		// �������� �����ϵ��� �Ѵ�.

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

		pclLog->FilePrint( "Config\\ReportingMacroLog.txt", "�ǽŰ��� ���� �ۼ� �Ϸ� [�ǽŰ���:%s] : ���� ���� ��û", data.szSenderName );
	}
}
