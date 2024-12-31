//---------------------------------
// 2003/6/9 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"
#include "..\Server\Candidate\Candidate.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Cityhall.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"
#include "..\CommonLogic\MsgType-Structure.h"
#include "..\CommonLogic\Msg\MsgType-Village.h"
#include "..\CommonLogic\Msg\MsgType-Rank.h"
#include "MsgRval-Define.h"

#include "..\Server\Minister\MinisterBase.h"
#include "..\Server\Minister\MinisterMgr.h"
#include "..\Server\Minister\Minister-Hozo.h"

#include "../common/Item/ItemCommon/Item-EventStructure.h"
 
//-------------------------------------
// Common
//-------------------------------------0
#include "PersonInfo.h"
#include "..\Common\Event\Hunting\Hunting.h"
#include "Char\CharManager\CharManager.h"
#include "Map\FieldObject\FieldObject.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_INVESTLIST(cltMsg* pclMsg, SI32 id)
{
	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	// ������ ������ ���Ѵ�. 
	cltVillageInvestInfo* pMayorInfo = &pclVillageManager->pclVillageInfo[villageunique]->clVillageVary.clInvestInfo;

	// � ������ ���������� ������Ʈ �Ѵ�. 
	pMayorInfo->siVillageUnique = villageunique;

	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg(GAMEMSG_RESPONSE_INVESTLIST, sizeof(cltVillageInvestInfo), (BYTE*)pMayorInfo);
	
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// �źп� �Ӹ��Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_BECHIEF(cltMsg* pclMsg, SI32 id)
{

	cltRank* pclrank = (cltRank*)pclMsg->cData;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclrank->GetVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;
	
	//-----------------------------------------
	// �ڰ��� �ִ��� Ȯ���Ѵ�. 
	//-----------------------------------------
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ����� �Ӹ��� ��� Person�� ������ �ִ��������� Ȯ���Ѵ�. 
	if(pclrank->clRank.siType == RANKTYPE_CITYHALL)
	{
		// ������� �Ӹ��� �� ����.!!!!!
		return ;
		
		/*if(pclVillageManager->IsMostBeholder(villageunique, personid) == FALSE)
		{
			// �ִ����ְ� �ƴϴ�. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTBESTBEHOLDER,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}*/
	}
	// ��Ÿ �Ӹ��� ��� ����� ���� Ȯ���Ѵ�. 
	else
	{
		cltSimpleRank clrank(RANKTYPE_CITYHALL, villageunique);
		if( pclRankManager->IsRank(personid, &clrank) == FALSE)
		{
			// ������� �ƴϴ�. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTMAYOR,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}

	//-----------------------------------------
	// ���Ӹ����� ������ ���Ѵ�. 
	//-----------------------------------------
	if(pclrank->GetPersonID() == 0)return ;

	// ���Ӹ����� �����͸� ���Ѵ�.
	SI32 candidateindex = -1;
	cltSimplePerson* pclcandidateinfo = pclCityHallManager->pclStruct[villageunique]->GetCandidateInfoFromPersonID(pclrank->GetRankType(), pclrank->GetPersonID(), &candidateindex);
	if(pclcandidateinfo == NULL)
	{
		// �ĺ��� ��ܿ� �ش� ĳ���Ͱ� ����. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_INVALIDCANDIDATE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	
	//DB�Ŵ������� ��û�Ѵ�.
	sDBRequest_BeRank clMsg(id, pclrank->GetPersonID(), candidateindex, &pclrank->clRank);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}


// �ĺ��� ��Ͻ�û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CANDIDATE(cltMsg* pclMsg, SI32 id)
{

	//-----------------------------------------------------
	// ���ĺ��� ������ Ȯ���Ѵ�. 
	//-----------------------------------------------------
	cltSimpleRank* pclrank = (cltSimpleRank*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	SI32 villageunique = pclrank->GetVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;

	// [����] �ʺ��� ���� : �ʺ��� ������ ��常 �ҿ��� ��û �����ϰ� �� �ź��� ��ȣõ�簡 �ƴϸ� �ȵȴ�
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == villageunique )
		{
			if ( (RANKTYPE_GUILD != pclrank->GetRankType()) || (pclCM->CR[id]->pclCI->clBI.uiAngelSwitch == false) )
			{
				return;
			}
		}
	}
		
	//---------------------------------------------------
	// �ĺ� ����� ������ �������� üũ �Ѵ� 
	//---------------------------------------------------

	SI32 needlevel = pclCityHallManager->GetNeedLevelFromRankType( pclrank->GetRankType() );

	if( pclCM->CR[id]->pclCI->clIP.GetLevel() < needlevel ) {

		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAILCANDIDATE_LEVELERROR,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	//---------------------------------------------------
	// �̹� ���� ������ �ĺ��� ����� �Ǿ� �ִٸ� ����. 
	//---------------------------------------------------
	if(pclCityHallManager->pclStruct[villageunique] == NULL)
	{
		return ;
	}

	SI32 index = 0;
	if(pclCityHallManager->pclStruct[villageunique]->GetCandidateInfoFromPersonID(pclrank->GetRankType(), personid, &index) != NULL)
	{
		// �̹� ���� ������ ��ϵǾ� �ִ�. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAILCANDIDATE_ALREADY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------------------------
	// �ش� �ź��� ���ĺ��ڰ� �ִ� ���� �Ѿ�ٸ� ����. 
	//---------------------------------------------------
	if(pclCityHallManager->pclStruct[villageunique]->GetCandidateNum(pclrank->GetRankType()) >= (MAX_CANDIDATE_NUMBER -1))
	{
		// �ִ� ���ĺ� ������ ���� �Ѿ��. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAILCANDIDATE_OVERFLOW,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}


	//---------------------------------------------------
	// �̹� �ź��� �����ϰ� �ִٸ� ����. 
	//---------------------------------------------------
	if(pclCM->CR[id]->pclCI->clCharRank.GetRankType())
	{
		// �̹� �ٸ� ������ �����ϰ� ������ ����.  
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAILCANDIDATE_ALREADYRANK,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------------------------
	// DBManager���� �ĺ� ����� ��û�Ѵ�. 
	//---------------------------------------------------
	sDBRequest_Candidate clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), pclrank);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELCANDIDATE(cltMsg* pclMsg, SI32 id)
{
	// ������ �ſ��� Ȯ���Ѵ�. 
	SI32 villageunique = pclMsg->siData32[0];
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	

	// DBManager���� ��û�Ѵ�. 
	sDBRequest_CancelCandidate clMsg(id, personid);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);


}

// �ź� ���ĺ��� ����� ��û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_CANDIDATELIST(cltMsg* pclMsg, SI32 id)
{
	// ������ �ſ��� Ȯ���Ѵ�. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank* pclrank = (cltSimpleRank*)pclMsg->cData;

	SI32 villageunique = pclrank->GetVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	//---------------------------------------
	// ������ �ڰ��� �ִ��� Ȯ���Ѵ�. 
	//---------------------------------------
	// ����� �Ӹ��̸� �ִ� ���ֿ��� �Ѵ�. 
	if(pclrank->siType == RANKTYPE_CITYHALL)
	{
		if(pclVillageManager->IsMostBeholder(villageunique, personid) == FALSE)
		{
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTBESTBEHOLDER,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}
	// ��� �Ӹ��̸� ��������� �Ѵ�. 
	else
	{
		cltSimpleRank clrank(RANKTYPE_CITYHALL,villageunique);
		if( pclRankManager->IsRank(personid, &clrank) == FALSE)
		{
			// ������� �ƴϴ�. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTMAYOR,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}
	
	
	SI32 i;
	SI32 sendmsgnum = 0;
	cltSimplePerson* pclPerson;
	for(i = 0;i< MAX_CANDIDATE_NUMBER;i++)
	{
		pclPerson = pclCityHallManager->pclStruct[villageunique]->GetCandidateInfoFromRef(pclrank->GetRankType(), i);
		
		if(pclPerson->GetPersonID() <= 0)continue;

		// �ĺ��� ��� ���� ������ �ľ��Ѵ�. 
		sendmsgnum++;
		
		// Ŭ���̾�Ʈ�� cltCandidate�����͸� ������ ���� �����Ѵ�. 
		cltGameMsgResponse_CandidateList clinfo(i, pclrank, pclPerson);
		cltMsg clMsg(GAMEMSG_RESPONSE_CANDIDATELIST, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
	
	// ������ ���� ����� �ϳ��� ���� ���, 
	if(sendmsgnum == 0)
	{
		// �ĺ��ڰ� ������ �˸���. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_NOCANDIDATE,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
	
}


void cltServer::DoMsg_GAMEMSG_REQUEST_DELCANDIDATE(cltMsg* pclMsg, SI32 id)
{

	// ������ �ſ��� Ȯ���Ѵ�. 
	cltSimpleRank* pclrank = (cltSimpleRank*)pclMsg->cData;
	SI32 villageunique = pclrank->GetVillageUnique();
	
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 returnval = 0;
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// �ִ��������� Ȯ���Ѵ�. 
	if(pclrank->siType == RANKTYPE_CITYHALL)
	{
		if(pclVillageManager->IsMostBeholder(villageunique, personid) == FALSE)
		{
			// �ִ����ְ� �ƴϴ�. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTBESTBEHOLDER,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}
	// ��Ÿ �Ӹ��� ��� ����� ���� Ȯ���Ѵ�. 
	else
	{
		cltSimpleRank clrank(RANKTYPE_CITYHALL,villageunique);
		if( pclRankManager->IsRank(personid, &clrank) == FALSE)
		{
			// ������� �ƴϴ�. 
			SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_NOTMAYOR,  0, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}
	}
	
	//DBManager���� �ĺ��� ������ ���� ��û�Ѵ�. 
	sDBRequest_DelCandidate clMsg(id, pclrank);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}


void cltServer::DoMsg_GAMEMSG_REQUEST_RESIGN(cltMsg* pclMsg, SI32 id)
{
	SI32 returnval = 0;

	//-------------------------------
	// ������ �ſ��� Ȯ���Ѵ�. 
	//-------------------------------
	cltSimpleRank* pclrank = (cltSimpleRank*)pclMsg->cData;

	SI32 villageunique = pclrank->GetVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID == 0)return ;

//#if defined(_CITYHALL_BANKRUPTCY)
	cltStrInfo* pclStrInfo = pclCityHallManager->GetStrInfo(villageunique);

	// ������� �����ΰ�
	if( pclStrInfo != NULL && pclrank->siType == 1 )
	{
		// ������ ������ �� ���� ������� ������ �� ����.
		if( pclStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_STABLE )
		{
			// ������ ������ �Դϴ�.. => ����� ���� ���� => �˸�
			cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( villageunique,  pclStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_CITYHALLCHIEF_RESIGN );
			cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			return;
		}
	}
//#endif

	//-------------------------------------
	// ����ڰ� Chief���� Ȯ���Ѵ�. 
	//-------------------------------------
	cltSimpleRank clrank(pclrank->GetRankType(),villageunique);
	if( pclRankManager->IsRank(PersonID, &clrank) == TRUE)
	{

		// Rank�������� ����ڸ� �����Ѵ�. 
		sDBRequest_Resign clMsg(id, PersonID, &clrank);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		
		returnval = SRVAL_SUCCESSRESIGNMAYOR;
	}
	else
	{
		returnval = SRVAL_NOMAYOR;	// ������� �ƴϴ�. 
	}


	// Person���� ������� �����ش�. 
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(pclrank->GetRankType(), returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_APPLYRESIDENT( cltMsg *pclMsg, SI32 id )
{
	SI32 returnval = 0;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID == 0)return ;

	bool bCheckMaxResidentCount = true;

	// �ʺ��� ������ ����� ������ �ִ� �ֹμ��� üũ���� �ʴ´�. - by LEEKH 2008-05-04
	if( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true )
	{
		if( villageunique == Const_Beginner_Village )
		{
			bCheckMaxResidentCount = false;
		}
	}

	if( bCheckMaxResidentCount )
	{
		cltStrInfo *pStrInfo = pclCityHallManager->GetStrInfo( villageunique );

		if( pStrInfo ) 
		{
			CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister( MINISTER_HOZO );
			if( pStrInfo->clCityhallStrInfo.siResidentNum > pclminister->m_siResidentNum )
			{
				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EXCEEDMAXRESIDENT, 0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}
		}
	}

	cltCharServer *pclChar = (cltCharServer*)pclCM->CR[id];
	if ( NULL == pclChar )
	{
		return;
	}

	// �ʺ��� ���� : �ʺ��� ������ ��������Ʈ�ÿ� �ڵ����Եǵ����Ѵ�
	if ( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true )
	{
		SI16 siQuestType, siQuestUnique, siPara1, siPara2;
		SI32 siQuestClearCond	= QUEST_CLEAR_COND_APPLYVILLAGE;

		bool bQuestGoing		= pclChar->pclCI->clQuestInfo.IsQuestGoing(siQuestClearCond, &siQuestType, &siQuestUnique, &siPara1, &siPara2);
		bool bTutorialVillage	= ( Const_Beginner_Village == villageunique );

		SI32 siLevel			= pclCM->CR[id]->pclCI->clIP.GetLevel();


		if( (true == bQuestGoing) && (true == bTutorialVillage) )
		{
			// �̹� �ٸ� ������ ���Ե� �����̰ų� 40���� �̻��̸� ����Ʈ�� Ŭ����
			if ( (0 < pclChar->pclCI->clBI.siHomeVillage) || (Const_BV_Max_Resident_Level <= siLevel) )
			{
				pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_APPLYVILLAGE);

				return;
			}
			// �ʺ��� ������ ������ �� �ִ� �����̶�� ����Ʈ Ŭ���� ���ÿ� �ڵ� ����
			else if ( Const_BV_Max_Resident_Level > siLevel )
			{
				sDBRequest_BeResident clMsg( id, PersonID, villageunique, &pclTime->clDate, true );
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

				pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_APPLYVILLAGE);

				return;
			}
		}	// if( (true == bQuestGoing) && (true == bTutorialVillage) ) ����
	}	// if ( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true ) ����

	sDBRequest_ApplyResident clMsg( id, PersonID, villageunique, &pclTime->clDate );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_APPLYRESIDENT2( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_ApplyResident2* pclmsg = (cltGameMsgRequest_ApplyResident2*)pclMsg->cData;

	SI32 returnval = 0;

	// ĳ���Ͱ� �ʴ���� ������ ���Ѵ�. 
	SI32 villageunique = pclmsg->siVillageUnique;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID == 0)return ;

	bool bCheckMaxResidentCount = true;

	// �ʺ��� ������ ����� ������ �ִ� �ֹμ��� üũ���� �ʴ´�. - by LEEKH 2008-05-04
	if( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true )
	{
		if( villageunique == Const_Beginner_Village )
		{
			bCheckMaxResidentCount = false;
		}
	}

	if( bCheckMaxResidentCount )
	{
		cltStrInfo *pStrInfo = pclCityHallManager->GetStrInfo( villageunique );

		if( pStrInfo ) 
		{
			CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister( MINISTER_HOZO );
			if( pStrInfo->clCityhallStrInfo.siResidentNum > pclminister->m_siResidentNum )
			{
				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EXCEEDMAXRESIDENT, 0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}
		}
	}

	cltCharServer *pclChar = (cltCharServer*)pclCM->CR[id];
	if ( NULL == pclChar )
	{
		return;
	}

	// �ʺ��� ���� : �ʺ��� ������ ��������Ʈ�ÿ� �ڵ����Եǵ����Ѵ�
	if ( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true )
	{
		SI16 siQuestType, siQuestUnique, siPara1, siPara2;
		SI32 siQuestClearCond	= QUEST_CLEAR_COND_APPLYVILLAGE;

		bool bQuestGoing		= pclChar->pclCI->clQuestInfo.IsQuestGoing(siQuestClearCond, &siQuestType, &siQuestUnique, &siPara1, &siPara2);
		bool bTutorialVillage	= ( Const_Beginner_Village == villageunique );

		SI32 siLevel			= pclCM->CR[id]->pclCI->clIP.GetLevel();


		if( (true == bQuestGoing) && (true == bTutorialVillage) )
		{
			// �̹� �ٸ� ������ ���Ե� �����̰ų� 40���� �̻��̸� ����Ʈ�� Ŭ����
			if ( (0 < pclChar->pclCI->clBI.siHomeVillage) || (Const_BV_Max_Resident_Level <= siLevel) )
			{
				pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_APPLYVILLAGE);

				return;
			}
			// �ʺ��� ������ ������ �� �ִ� �����̶�� ����Ʈ Ŭ���� ���ÿ� �ڵ� ����
			else if ( Const_BV_Max_Resident_Level > siLevel )
			{
				sDBRequest_BeResident clMsg( id, PersonID, villageunique, &pclTime->clDate, true );
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

				pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_APPLYVILLAGE);

				return;
			}
		}	// if( (true == bQuestGoing) && (true == bTutorialVillage) ) ����
	}	// if ( pclClient->IsCountrySwitch( Switch_TutorialVillage ) == true ) ����

	// ���ֿ��� ������ ������.
	cltRank* pclRank = pclRankManager->GetRank( RANKTYPE_CITYHALL, villageunique );
	if ( pclRank != NULL )
	{
		cltRank clRank;
		SI32	siPersonID = 0;
		SI32	siCharID   = 0;

		clRank.Set( pclRank );
		siPersonID = clRank.clPerson.GetPersonID();

		if( 0 < siPersonID )
		{
			SI32 siID = pclCM->GetIDFromPersonID( siPersonID );
			if( 0 >= siID )
			{
				cltLetterMsg_Invite_Applyresident clletter( pclmsg->szMentorName, (TCHAR*)pclChar->GetName() );
				sDBRequest_PushLetter clMsg( siPersonID, (cltLetterUnit*)&clletter );
				pclGameDBProcess->SendMsg( DBSELECT_LETTER, (sPacketHeader *)&clMsg );
			}
			else
			{
				cltLetterMsg_Invite_Applyresident clletter( pclmsg->szMentorName, (TCHAR*)pclChar->GetName() );
				SendLetterMsg(  siPersonID , (cltLetterHeader*)&clletter );
			}
		}
	}
	

	sDBRequest_ApplyResident clMsg( id, PersonID, villageunique, &pclTime->clDate, true );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELRESIDENT( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_CancelResident *pclmsg = (cltGameMsgRequest_CancelResident *)pclMsg->cData;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;


	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE && personid != pclmsg->siPersonID )
	{
		return;
	}

	sDBRequest_CancelResident clMsg( id, pclmsg->siPersonID, villageunique, false );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BERESIDENT( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_BeResident *pclmsg = (cltGameMsgRequest_BeResident *)pclMsg->cData;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;
	
	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	cltStrInfo *pStrInfo = pclCityHallManager->GetStrInfo( villageunique );

	if( pStrInfo ) {
		
		CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);

		if( pStrInfo->clCityhallStrInfo.siResidentNum > pclminister->m_siResidentNum ) {

			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EXCEEDMAXRESIDENT, 0, 0, pclCM->CR[id]->GetCharUnique() );

			return;
		}
	}

	if( pclClient->pclVillageManager->IsVillageAtWar(villageunique) == TRUE)
	{

		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_VILLAGEATWAR, 0, 0, pclCM->CR[id]->GetCharUnique() );

		return;
	}


	sDBRequest_BeResident clMsg( id, pclmsg->siPersonID, villageunique, &pclTime->clDate, false );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTAPPLYERLIST( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_GetResidentApplyerList *pclmsg = (cltGameMsgRequest_GetResidentApplyerList *)pclMsg->cData;

	cltGameMsgResponse_GetResidentApplyerList retMsg;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	cltCityHall *pclCityHall = (cltCityHall *)(pclCityHallManager->pclStruct[ villageunique ]);

	int c = 0;
	for( int i = 0; i < MAX_RESIDENT_APPLYER; ++i ) {

		if( pclCityHall->clResidentApplyer[ i ].clApplyer.GetPersonID() ) {

			if( c >= MAX_RESIDENT_APPLYER )		continue;
			retMsg.clResidentApplyer[ c ].Set( &pclCityHall->clResidentApplyer[ i ] );

			c++;
		}

	}

	retMsg.count = c;

	cltMsg clNormalMsg( GAMEMSG_RESPONSE_RESIDENTAPPLYERLIST, retMsg.GetTotalSize(), (BYTE*)&retMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);


}

void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTLIST( cltMsg *pclMsg, SI32 id )
{

	cltGameMsgRequest_GetResidentList *pclmsg = (cltGameMsgRequest_GetResidentList *)pclMsg->cData;


	sDBRequest_GetResidentList clMsg( id, pclmsg->siVillageUnique, pclmsg->siSort );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	


	/*
	cltGameMsgResponse_GetResidentList retMsg;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	cltCityHall *pclCityHall = (cltCityHall *)(pclCityHallManager->pclStruct[ villageunique ]);

	int c = 0;
	for( int i = 0; i < MAX_RESIDENT_NUMBER; ++i ) {

		if( pclCityHall->clResident[ i ].clPerson.GetPersonID() ) {

			retMsg.clResident[ c ].Set( &pclCityHall->clResident[ i ] );

			c++;
		}

	}

	retMsg.count = c;

	cltMsg clNormalMsg( GAMEMSG_RESPONSE_RESIDENTLIST, retMsg.GetTotalSize(), (BYTE*)&retMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
	*/

}

// �ֹ� �� ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTINFO( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_GetResidentInfo *pclInfo = (cltGameMsgRequest_GetResidentInfo *)pclMsg->cData;
	
	
	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageUnique <= 0 || villageUnique >= MAX_VILLAGE_NUMBER)	return ;

	sDBRequest_GetResidentInfo clMsg( id, villageUnique, pclInfo->szPersonName );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}


// �ֹ� ���� �ο�
void cltServer::DoMsg_GAMEMSG_REQUEST_SETRESIDENTSCORE( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_SetResidentScore *pclInfo = (cltGameMsgRequest_SetResidentScore *)pclMsg->cData;

	// ĳ���Ͱ� ��ġ�� ������ ���Ѵ�. 
	SI32 villageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageUnique <= 0 || villageUnique >= MAX_VILLAGE_NUMBER)	return ;


	sDBRequest_SetResidentScore clMsg( villageUnique, pclInfo->siPersonId, pclInfo->siScore );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}


// ���� �ֹ� ��� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HIRENPC( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_HireNPC *pclInfo = (cltGameMsgRequest_HireNPC *)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}
	
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclchar->GetCurrentVillageUnique();
	if (villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)
	{
		return ;
	}
	
	SI32 personid = pclchar->pclCI->GetPersonID();
	// ������ �ִ°� 
	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	UI16 slot = pclInfo->usSlot;
	if( slot < 0 || slot >= MAX_HIRED_NPC_NUM )
	{
		return;
	}

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);

	if( pclinfo == NULL ) return;

	// �ذ��̸�
	if( pclInfo->siNPCKind == 0 ) {

		if( pclinfo->clCityhallStrInfo.clHiredNPC[ slot ].siNPCKind > 0 ) {

			sDBRequest_HireNPC clMsg( id, villageunique, slot, 0, 0, 0, &pclTime->clDate , HIRENPC_HIRENPC );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

			
		}
		return;
	}


	// ����̸�,

	// NPC���� ��ġ�� �ǹ� ���Կ� �ǹ��� ������ �ִٸ� NPC�� ����� �� ���� 

	// slot�� ����ִ��� ���� 
	if( pclVillageManager->pclVillageInfo[ villageunique ]->clVillageVary.clStructureInfo.IsExist( 6 ) ) {
		// slot�� ������� �ʴٸ�,
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_HIRENPC_BUILDSTRUCTURE, 0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	int i;

	for( i = 0; i < MAX_HIRED_NPC_NUM; ++i ) {

		if( pclinfo->clCityhallStrInfo.clHiredNPC[ i ].siNPCKind == pclInfo->siNPCKind ) break;
	}

	// �̹� ���� ���̸� return;
	if( i < MAX_HIRED_NPC_NUM )
	{
		return;
	}
	

//#if defined(_CITYHALL_BANKRUPTCY)
	// ���� ������ �̹Ƿ� npc ����� �����̴�.
	cltStrInfo* pclStrInfo = pclinfo;
	if( pclStrInfo->clCityhallStrInfo.usCurStatus != CITYHALL_BEING_STABLE )
	{
		//// ��� ������ ���� �����ΰ�
		//if( pclinfo->clCityhallStrInfo.siVillageLevel <
		//	pclKindInfoSet->GetHireVillageLevel( pclInfo->siNPCKind ) )
		//{
		//	SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_HIRENPC_VILLAGELEVEL, 0, 0, pclCM->CR[id]->GetCharUnique() );
		//	return;
		//}
	}
//#endif
	
	GMONEY gmPayment = pclKindInfoSet->GetHireBasicMoney( pclInfo->siNPCKind );

	gmPayment = gmPayment * ( pclItemManager->clItemStatistic.siNPCPriceRate / 100. );

	//#if defined(_CITYHALL_BANKRUPTCY)
	// ���� ������ �̹Ƿ� npc ����� �����̴�.
	if( pclStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_STABLE )
	{
		gmPayment = 0;
	}
	//#endif


	// ���� ��ȣ�� NPC�� ������
	if( slot >= 0 && slot < MAX_HIRED_NPC_NUM ) 
	{
		if( pclinfo->clCityhallStrInfo.clHiredNPC[ slot ].siNPCKind == 0 ) 
		{
			sDBRequest_HireNPC clMsg( id, villageunique, slot, pclInfo->siNPCKind, gmPayment, gmPayment, &pclTime->clDate , HIRENPC_HIRENPC );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
				
			return;
		}
	}

	// ������ ���Թ�ȣ�� NPC�� �̹� ���Ǿ� ������ �̰����� �� ������ ã�Ƽ� NPC�� ����Ѵ�
	for( i = 0; i < MAX_HIRED_NPC_NUM; ++i )
	{
		if( pclinfo->clCityhallStrInfo.clHiredNPC[ i ].siNPCKind == 0 ) 
		{
			sDBRequest_HireNPC clMsg( id, villageunique, i, pclInfo->siNPCKind, gmPayment, gmPayment, &pclTime->clDate , HIRENPC_HIRENPC );

			pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
			
			return;			
		}
	}
	
}

// ������ ���� �ֹ� ����Ʈ ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_GETNPCLIST( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_GetNPCList *pclInfo = (cltGameMsgRequest_GetNPCList *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
	if(pclinfo == NULL)return ;

	// ���� ������
	cltGameMsgResponse_GetNPCList rspMsg;

	rspMsg.siVillageUnique = villageunique;

#ifdef _SAFE_MEMORY
	rspMsg.clHiredNPC.MemCpy(pclinfo->clCityhallStrInfo.clHiredNPC);
#else
	memcpy( rspMsg.clHiredNPC, pclinfo->clCityhallStrInfo.clHiredNPC, sizeof( cltHiredNPC ) * MAX_HIRED_NPC_NUM );
#endif

	cltMsg clNormalMsg( GAMEMSG_RESPONSE_GETNPCLIST, sizeof( cltGameMsgResponse_GetNPCList ), (BYTE*)&rspMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
}

// NPC �޿� ���� ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_NPCPAYMENT( cltMsg *pclMsg, SI32 id )
{

	cltGameMsgResponse_NPCPayment rspMsg;
	rspMsg.siCount = 0;

	SI32 kind;

	for( int i = 0; i < MAX_HIREDNPC_KIND_NUM; ++i ) {

		kind = pclHiredNPCPayManager->clHiredNPCPayInfo[ i ].siNPCKind;

		if( kind ) 
		{
			GMONEY gmPayment = pclKindInfoSet->GetHireBasicMoney( kind );
			gmPayment = gmPayment * (pclItemManager->clItemStatistic.siNPCPriceRate / 100.);

			if( rspMsg.siCount >= MAX_HIREDNPC_KIND_NUM )	continue;
			rspMsg.clHiredNPCPayInfo[ rspMsg.siCount ]				= pclHiredNPCPayManager->clHiredNPCPayInfo[ i ];
			rspMsg.clHiredNPCPayInfo[ rspMsg.siCount ].siPayment	= gmPayment;
			++rspMsg.siCount;
		}
	}

	cltMsg clNormalMsg( GAMEMSG_RESPONSE_NPCPAYMENT, sizeof( cltGameMsgResponse_NPCPayment ), (BYTE*)&rspMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);
}

// ���� ���� 
void cltServer::DoMsg_GAMEMSG_REQUEST_DECLAREWAR( cltMsg *pclMsg, SI32 id )
{

	// ������ ������ ������
	

	SI32 returnval = 0;

	if(  true == bForceStopVillageWarProcess	)
	{	
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTNATION;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}

	SI32 targetVillage = pclMsg->siData32[ 0 ];
	if( targetVillage < 0 || targetVillage >= MAX_VILLAGE_NUMBER )		return;

	SI32 villageunique = pclCM->CR[id]->pclCI->clBI.siHomeVillage;
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER )		return;

	// [����] �ʺ��� ���� : �ʺ��� ������ ������ �ߵ� ���ϰ�
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( (Const_Beginner_Village == villageunique) 
			|| (Const_Beginner_Village == targetVillage) 
		)
		{
			return;
		}
	}

	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER )
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTNATION;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );

		return ;
	}
	
	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	if( villageunique == targetVillage ) return;

	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if(pStrInfo == NULL)return ;
	cltStrInfo *pTargetStrInfo = GetStrInfo( targetVillage, RANKTYPE_CITYHALL );
	if(pTargetStrInfo == NULL)return ;

	if( pStrInfo == NULL || pTargetStrInfo == NULL ) return;

	if( bVillageWarSwitch ) {
		// ���� �������̸�,

		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_WARTIME;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	cltRank* pclrank = pclRankManager->GetRank(RANKTYPE_CITYHALL,targetVillage);
	
	SI32 Homevillageunique	= pclCM->CR[id]->pclCI->clBI.siHomeVillage;
	cltStrInfo* pclstrinfo = pclClient->pclCityHallManager->GetStrInfo(Homevillageunique);
	if(pclstrinfo == NULL)return ;
	 SI32 VillageRegNum = pclstrinfo->clCityhallStrInfo.siResidentNum;// ���� �ֹμ�

     
	if(pclrank == NULL || pclrank->clPerson.siPersonID <= 0 ) //����� ������ ������� ���ٸ�
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTMAYOR;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// ���� �� �ֹ��� �ϳ��� ���� 
	if (VillageRegNum == NULL || VillageRegNum <= 0 ) {
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_NOTMAYOR;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// ���� ������ 5�ܰ� �Ѱ� ���̰� ����� ����

	SI32 myVillageRank = pclVillageManager->GetVillageRank(villageunique);
	SI32 TargetVillageRank = pclVillageManager->GetVillageRank(targetVillage);
	
	if( TargetVillageRank - myVillageRank > 5)
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_LOWERRANK;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// ������ �й� �ð� ���� 7���� ������ �ʾҴٸ� ����
	
	NDate CurrentDate;

	CurrentDate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
	
	SI32 CurrentDateVary = CurrentDate.GetDateVary();

	cltStrInfo *pclStrInfo = GetStrInfo(villageunique, RANKTYPE_CITYHALL );
	if(pclStrInfo  == NULL) return;


	NDate LastWarLoseDate;

	LastWarLoseDate.SetDate( pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateYear,
		pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateMonth,
		pclStrInfo->clCityhallStrInfo.uiLastWarLoseDateDay)	;

	SI32 LastWarLoseDateVary = LastWarLoseDate.GetDateVary();
	
	// ��¥���� ����ġ �ʾҴٸ� ��ȿȭ �Ѵ�.
    if( LastWarLoseDate.m_uiYear == 0 ||  LastWarLoseDate.m_uiMonth == 0 || LastWarLoseDate.m_uiDay == 0 )
	{
		LastWarLoseDateVary = 0;
	}
	

	if( (LastWarLoseDateVary > 0 ) && ( LastWarLoseDateVary + 7 >  CurrentDateVary) )
	{
		// �й����� 7���� ������ �������� �����Ҽ� �ִ�.
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_AFTERLOSE;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	cltStrInfo* pclTargetStrInfo = GetStrInfo(targetVillage, RANKTYPE_CITYHALL);

	if(pclTargetStrInfo == NULL) return;

	NDate TargetLastWarLoseDate;

	TargetLastWarLoseDate.SetDate( pclTargetStrInfo->clCityhallStrInfo.uiLastWarLoseDateYear,
		pclTargetStrInfo->clCityhallStrInfo.uiLastWarLoseDateMonth,
		pclTargetStrInfo->clCityhallStrInfo.uiLastWarLoseDateDay );

	LastWarLoseDateVary =  TargetLastWarLoseDate.GetDateVary();  //((cltCityhallStrInfo*)(pclTargetStrInfo))->clLastWarLoseDate.GetDateVary();

	// ��¥���� ����ġ �ʾҴٸ� ��ȿȭ �Ѵ�.
	if( TargetLastWarLoseDate.m_uiYear == 0 ||  TargetLastWarLoseDate.m_uiMonth == 0 || TargetLastWarLoseDate.m_uiDay == 0 )
	{
		LastWarLoseDateVary = 0;
	}


	if( (LastWarLoseDateVary > 0 ) && ( LastWarLoseDateVary + 7 >  CurrentDateVary) )
	{		
			// �й����� 7���� ������ ������ ������� ������ �� �ִ�.
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_TARGET_AFTERLOSE;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}


	if( pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ targetVillage ] ){
		// �̹� ���� ���� �Ǿ� �ִ°�

		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADY;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	} 

	//��� ������ �̹� �������� �ߴ�
	if( pclClient->pclVillageManager->siDeclareWarVillage[targetVillage] > 0 )
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADY;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	
	SI32 i = 0;
	for(  i = 1; i < MAX_VILLAGE_NUMBER; ++i )
	{

		// �̹� ���� ���� �� ������ �ִ�.
		if( pStrInfo->clCityhallStrInfo.bDeclareWarVillage[ i ] == 1 )
		{
			returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADYACT;
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
		// ��� ������ �̹� ������ ������ �޾Ҵ�
		if( pclClient->pclVillageManager->siDeclareWarVillage[i] == targetVillage  )
		{
			returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADY;
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
		// �̹� ���� ������� ������ ������ �� ������ �ִ�.
		if( pclClient->pclVillageManager->siDeclareWarVillage[i] == villageunique )
		{
			returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_ALREADY;
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}


	
	// ���� [������] �������� ���� ��� ����
	/*
	// �������� �ϰų� �������� 15���� �����°�
	{

		SI32 wardate = pStrInfo->clCityhallStrInfo.clDeclareWarDate.GetDateVary();
		SI32 currdate = pclTime->clDate.GetDateVary();

		if( currdate - wardate <= 15 ) {
			returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_DATE;
			SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}*/

/*
	// �ֹμ��ڰ� 50%�̻� ���̰� ����
	{
		SI32 targetResidentNum = pTargetStrInfo->clCityhallStrInfo.siResidentNum;
		if( targetResidentNum < 50 ) targetResidentNum = 50;

		if( pStrInfo->clCityhallStrInfo.siResidentNum / 2 > targetResidentNum ) {
				returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_GAP;
				SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
		}
	}
*/	
//#if defined(_CITYHALL_BANKRUPTCY)
	if( pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_STABLE 
		|| pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT 
		|| pTargetStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_INITIALIZED  )
	{
		// ���� ��� ������ �������Դϴ�.. => �������� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( targetVillage, pTargetStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_DECLARE_WAR );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	// �������� ������ �ٸ� ������ ������ �� ����.
	if( pStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_STABLE )
	{
		// ���� ��� ������ �������Դϴ�.. => �������� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( villageunique, pStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_DECLARE_WAR );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}
//#endif

	// ���� �ֽ��� �� Ǯ�� �������� ������ ���� ����
	if ( pTargetStrInfo->clCityhallStrInfo.siTotalStockAmount <= 0 )
	{
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_NOMASTER;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	NDate clRealDate;
	clRealDate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
	
	sDBRequest_DeclareWar clMsg( id, villageunique, targetVillage, &clRealDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CANCELDECLAREWAR( cltMsg *pclMsg, SI32 id )
{
	SI32 returnval = 0;

	SI32 targetVillage = pclMsg->siData32[ 0 ];
	if(targetVillage < 0 || targetVillage >= MAX_VILLAGE_NUMBER)	return;

	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if( pStrInfo == NULL ) return;


	if( bVillageWarSwitch ) {
		returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_WARTIME;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if( pclCityHallManager->GetStrInfo( villageunique )->clCityhallStrInfo.bDeclareWarVillage[ targetVillage ] != 1 ) {

		returnval = SRVAL_CITYHALL_FAIL_CANCELDECLAREWAR;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
/*
	// �������� �ϰų� �������� 15���� �����°�
	{

		SI32 wardate = pStrInfo->clCityhallStrInfo.clDeclareWarDate.GetDateVary();
		SI32 currdate = pclTime->clDate.GetDateVary();

		if( currdate - wardate <= 15 ) {
			returnval = SRVAL_CITYHALL_FAIL_DECLAREWAR_DATE;
			SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}
*/
	NDate clCurDate;
	clCurDate.SetDate(sTime.wYear,sTime.wMonth,sTime.wDay);
	sDBRequest_CancelDeclareWar clMsg( id, villageunique, targetVillage, &clCurDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

// �������� ��û( �ְ� �θ� ����, �θ� ����, �������� ���� )
void cltServer::DoMsg_GAMEMSG_REQUEST_GETVILLAGEINFO( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgResponse_GetVillageInfo sendMsg;

	cltVillageInfo *pVillageInfo;

	for( int i = 1; i < MAX_VILLAGE_NUMBER; ++i )
	{
		pVillageInfo = pclVillageManager->pclVillageInfo[ i ];

		if( pVillageInfo == NULL ) continue;

		sendMsg.siMasterVillage[ i ] = pVillageInfo->clVillageVary.siMasterVillage;

		sendMsg.siParentVillage[ i ] = pVillageInfo->clVillageVary.siParentVillage;

		sendMsg.siVillageMark[ i ] = pVillageInfo->clVillageVary.siVillageMark;

		sendMsg.siTotalVillageScore[ i ] = pVillageInfo->clVillageVary.siTotalVillageScore;
		
	}
	
#ifdef _SAFE_MEMORY
	memcpy( sendMsg.siDeclareWarVillage, &pclVillageManager->siDeclareWarVillage[0], sizeof( sendMsg.siDeclareWarVillage ) );
	memcpy( sendMsg.clDeclareWarDate, &pclVillageManager->clDeclareWarDate[0], sizeof( sendMsg.clDeclareWarDate ) );
	memcpy( sendMsg.siNowWarVillage, &pclVillageManager->siNowWarVillage[0],sizeof(sendMsg.siNowWarVillage) );
#else
	memcpy( sendMsg.siDeclareWarVillage, pclVillageManager->siDeclareWarVillage, sizeof( sendMsg.siDeclareWarVillage ) );
	memcpy( sendMsg.clDeclareWarDate, pclVillageManager->clDeclareWarDate, sizeof( sendMsg.clDeclareWarDate ) );
	memcpy( sendMsg.siNowWarVillage, pclVillageManager->siNowWarVillage,sizeof(sendMsg.siNowWarVillage) );
#endif

	cltMsg clNormalMsg( GAMEMSG_RESPONSE_GETVILLAGEINFO, sizeof( cltGameMsgResponse_GetVillageInfo ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clNormalMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTSLIST( cltMsg *pclMsg, SI32 id )
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clBI.siHomeVillage < 1 || pclCM->CR[id]->pclCI->clBI.siHomeVillage >= MAX_VILLAGE_NUMBER )
	{
		return;
	}

	cltGameMsgRequest_ResidentsList *pclInfo = (cltGameMsgRequest_ResidentsList*)pclMsg->cData;
	
	if ( pclInfo->siVillageUnique < 1 || pclInfo->siVillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clBI.siHomeVillage != pclInfo->siVillageUnique )
	{
		return;
	}

	cltGameMsgResponse_ResidentsList clResidentsList;
	clResidentsList.Set( pclInfo->siVillageUnique );
	
	SI32 CharID = 0;
	SI32 index = 0;
	while( CharID = pclCM->GetCharOrder( index ))
	{
		index++;

		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[CharID];
		if(IsPC(CharID))
		{
			if(pclchar->pclCI->clBI.siHomeVillage == pclInfo->siVillageUnique )
			{
				// ĳ���� ����, ����, ����
				clResidentsList.Add( &pclchar->pclCI->clBI.clPerson, pclchar->pclCI->clIP.GetLevel(), pclchar->siVillageWarKillScore, &pclchar->pclCI->clCharRank, pclchar->pclCI->clBI.szAccountID );
			}
		}
	}


	if ( clResidentsList.uiCount > 0 )
	{
		cltMsg clMsg( GAMEMSG_RESPONSE_RESIDENTSLIST, clResidentsList.GetTotalSize(), (BYTE*)&clResidentsList );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETSYMBOLSTATUS( cltMsg *pclMsg, SI32 id )
{
	SI32 returnval;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	if( bVillageWarSwitch ) {
		// ���� �������̸�,
		returnval = SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_WARTIME;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	SI32 siGodCharUnique;
	if( pclVillageManager->IsThereVillageGod( villageunique, &siGodCharUnique ) == FALSE ) {
		returnval = SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_NOTEXIST;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	cltGameMsgRequest_SetSymbolStatus *pclInfo = (cltGameMsgRequest_SetSymbolStatus *)pclMsg->cData;

	if( pclInfo->siStatValue < 0 || pclInfo->siStatValue >= MAX_KINDINFO_NUMBER )	return;

	SI32	siMaxLife = pclVillageManager->GetMaxLifeOfGodInVillage( villageunique );
	if( siMaxLife == 0 ) return;
	
	SI32	siStatValue = 0;
	GMONEY	siCost = 0;
	
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if(pStrInfo == NULL)return ;

	// ���� �� ���¿� ���� ���� ��ġ ����
	switch( pclInfo->siStatKind )
	{
	case SYMBOLSTAT_KIND:
		{
			cltKindInfo *pclKindInfo = pclKindInfoSet->pclKI[ pclInfo->siStatValue ];
			if( pclKindInfo == NULL ) return;
			
			// ���� ��Ȳ�� ���º��� ���� �ܰ��� ��Ȳ�����δ� ������ �� ����

			if( pclKindInfoSet->GetSortLevel( pStrInfo->clCityhallStrInfo.siSymbolKind ) >
				pclKindInfoSet->GetSortLevel( pclInfo->siStatValue ) ) {

				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_LOWERLEVEL,  0, 0, pclCM->CR[id]->GetCharUnique() );
				return;
			}



			// ���� �ֹ� �� üũ
			if( pclKindInfo->GetResidentNumForVillageGod() > pStrInfo->clCityhallStrInfo.siResidentNum ) {

				returnval = SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_RESIDENT;
				SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
				return;

			}

			// ����� �� �ִ� �� 
			if( pclKindInfo->CanGodForVillage( villageunique ) == FALSE ) {

				return;
			}


			siCost = pclKindInfo->GetMoneyForVillageGod();
			siStatValue = pclInfo->siStatValue;

			if( siCost == 0 ) return;
		}
		break;

	case SYMBOLSTAT_LIFE:
		{
			SI32 value = 0 ;
			cltKindInfo * pclkind = NULL;
			if( pStrInfo->clCityhallStrInfo.siSymbolKind >= 0 && pStrInfo->clCityhallStrInfo.siSymbolKind < MAX_KINDINFO_NUMBER )
				pclkind = pclKindInfoSet->pclKI[pStrInfo->clCityhallStrInfo.siSymbolKind];

			if ( pclkind )
			{
				if ( pclkind->IsAtb(ATB_GOD) )
					value = 300 ;
				else
					value = 600 ;
			}
			else return;

			siStatValue = SI32(siMaxLife * 0.2);
			if( siStatValue + pStrInfo->clCityhallStrInfo.siSymbolLife > siMaxLife ) {
				siStatValue = siMaxLife - pStrInfo->clCityhallStrInfo.siSymbolLife;
			}

			siCost = siStatValue * value;
			siStatValue += pStrInfo->clCityhallStrInfo.siSymbolLife;
		}
		
		break;

	case SYMBOLSTAT_MANA:
		{

		}
		break;

	case SYMBOLSTAT_CAPA:
		{
			siStatValue = pStrInfo->clCityhallStrInfo.siSymbolCapa + 1;
			if ( siStatValue > 250  )
			{				
				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_MAXLEVEL,  0, 0, pclCM->CR[id]->GetCharUnique() );
				return ;
			}
			siCost = 100000;

			cltKindInfo *pclKindInfo = NULL;
			if( pStrInfo->clCityhallStrInfo.siSymbolKind >= 0 && pStrInfo->clCityhallStrInfo.siSymbolKind < MAX_KINDINFO_NUMBER )
				pclKindInfo = pclKindInfoSet->pclKI[ pStrInfo->clCityhallStrInfo.siSymbolKind ];

			if( pclKindInfo != NULL ) {

				siCost = pclKindInfo->GetUpMoneyForVillageGod();
			}

			if( siCost == 0 ) return;
		}
		break;
 
	}

	// ������ ���� �� 1���� �����°�
	{
		SI32 lastdate = pStrInfo->clCityhallStrInfo.clLastSymbolUpdate.GetDateVary();
		SI32 currdate = pclTime->clDate.GetDateVary();

		if( currdate - lastdate < 30 ) {
			returnval = SRVAL_CITYHALL_FAIL_SYMBOLSTATUS_DATE;
			SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}

	sDBRequest_SetSymbolStatus clMsg( id, villageunique, pclInfo->siStatKind, siStatValue, siCost, &pclTime->clDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETCASTLESTATUS( cltMsg *pclMsg, SI32 id )
{

	SI32 returnval;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	if( bVillageWarSwitch ) {
		// ���� �������̸�,
		returnval = SRVAL_CITYHALL_FAIL_CASTLESTATUS_WARTIME;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	SI32 siCastleCharUnique;
	if( pclVillageManager->IsThereCastle( villageunique, &siCastleCharUnique ) == FALSE ) {
		returnval = SRVAL_CITYHALL_FAIL_CASTLESTATUS_NOTEXIST;
		SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	

	cltGameMsgRequest_SetCastleStatus *pclInfo = (cltGameMsgRequest_SetCastleStatus *)pclMsg->cData;

	SI32	siMaxLife = pclVillageManager->GetMaxLifeOfCastleInVillage( villageunique );
	if( siMaxLife == 0 ) return;
	
	SI32	siStatValue = 0;
	GMONEY	siCost = 0;
	
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if(pStrInfo == NULL)return;

	// ���� �� ���¿� ���� ���� ��ġ ����
	switch( pclInfo->siStatKind )
	{
	case SYMBOLSTAT_KIND:
		{
		}
		break;

	case SYMBOLSTAT_LIFE:
		{
			siStatValue = SI32(siMaxLife * 0.2);
			if( siStatValue + pStrInfo->clCityhallStrInfo.siCastleLife > siMaxLife ) {
				siStatValue = siMaxLife - pStrInfo->clCityhallStrInfo.siCastleLife;
			}

			siCost = siStatValue * 200;
			siStatValue += pStrInfo->clCityhallStrInfo.siCastleLife;
		}
		
		break;

	case SYMBOLSTAT_MANA:
		{
		}
		break;

	case SYMBOLSTAT_CAPA:
		{
			siStatValue = pStrInfo->clCityhallStrInfo.siCastleCapa + 1;
			if ( siStatValue > 250 )
			{
				SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_CASTLESTATUS_MAXLEVEL,  0, 0, pclCM->CR[id]->GetCharUnique() );
				return ;
			}

			siCost = 100000;
/*
			cltKindInfo *pclKindInfo = pclKindInfoSet->pclKI[ pStrInfo->clCityhallStrInfo.siSymbolKind ];

			if( pclKindInfo != NULL ) {

				siCost = pclKindInfo->GetUpMoneyForVillageGod();
			}
*/
		}
		break;

	}


	// ������ ���� �� 1���� �����°�
	{
		SI32 lastdate = pStrInfo->clCityhallStrInfo.clLastCastleUpdate.GetDateVary();
		SI32 currdate = pclTime->clDate.GetDateVary();

		if( currdate - lastdate < 30 ) {

			returnval = SRVAL_CITYHALL_FAIL_CASTLESTATUS_DATE;
			SendServerResponseMsg( RANKTYPE_CITYHALL, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}

	sDBRequest_SetCastleStatus clMsg( id, villageunique, pclInfo->siStatKind, siStatValue, siCost, &pclTime->clDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTSHARE( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_ResidentShare *pclInfo = (cltGameMsgRequest_ResidentShare *)pclMsg->cData;
	// ���� ���ͱ� ���� ��ƾ -1
	if( pclInfo->clTotalShareMoney.itMoney < 1000000 ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	pclCM->FindResidentListInVillage( villageunique );
	
	// ������ �ִ� �ֹ� ���� 30�� �����̸� ��� �� �� ���� 
	if( siParaCharListIndex < 30 ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGCOUNT,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	// ��� ������ �ð��ΰ�( 18:00 ~ 23:00 )

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	if( systime.wHour < 18 || systime.wHour > 23 ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_RESIDENTSHARE_WRONGTIME,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// �ǹ��� ��ü���� �Ѵ��� �����°� 
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if( pStrInfo->clCityhallStrInfo.siLastDestroyStrDate + 30 > pclTime->clDate.GetDateVary() ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_RESIDENTSHARE_DATE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if( pStrInfo->clCityhallStrInfo.clProfitMoney.itMoney < pclInfo->clTotalShareMoney.itMoney ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_RESIDENTSHARE_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	sDBRequest_ResidentShare sendMsg;
	
	sendMsg.packetHeader.usCmd = DBMSG_REQUEST_RESIDENTSHARE;
	sendMsg.packetHeader.usSize = sizeof( sendMsg );

	sendMsg.siCount = siParaCharListIndex;

	if( sendMsg.siCount > 100 ) sendMsg.siCount = 100;

	GMONEY sharemoney = (GMONEY)((REAL64)pclInfo->clTotalShareMoney.itMoney / (REAL64)sendMsg.siCount );

	sendMsg.siVillageUnique = villageunique;
	sendMsg.clTotalShareMoney.Set( sharemoney * sendMsg.siCount );

	for( int i = 0; i < sendMsg.siCount; ++i ) {

		sendMsg.siCharIndex[ i ] = siParaCharList[ i ];
		sendMsg.siPersonID[ i ] = pclCM->CR[ siParaCharList[ i ] ]->pclCI->GetPersonID();
		sendMsg.siShareMoney[ i ] = sharemoney;
	}
	
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETSTRUCTURELIST(cltMsg* pclMsg, SI32 id)
{

}


void cltServer::DoMsg_GAMEMSG_REQUEST_BUILDSTRUCTURE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_BuildStructure *pclInfo = (cltGameMsgRequest_BuildStructure *)pclMsg->cData;	

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER )		return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}


	// slot�� ����ִ��� ���� 
	if( pclVillageManager->pclVillageInfo[ villageunique ]->clVillageVary.clStructureInfo.IsExist( pclInfo->siSlot ) ) {
		// slot�� ������� �ʴٸ�,
		return;
	}

	// �ش� ������ NPC�� ��ġ�� �� �ִ� �����϶� NPC�� �ִ��� ����
	// NPC�� �ִٸ� �ǹ��� ���� �� ����
	if( pclInfo->siSlot == 6 ) {

		cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );

		for( int i = 0; i < MAX_HIRED_NPC_NUM; ++i )
		{
			if( pclStrInfo->clCityhallStrInfo.clHiredNPC[ i ].siNPCKind != 0 ) break;
		}

		if( i < MAX_HIRED_NPC_NUM ) {
			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_CONSTRUCT_NPCZONE,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}

	}

	// ������ ��� 
	if( pclInfo->siStructureUnique == LAND_UNIQUE ) {
		if( pclVillageManager->pclVillageInfo[ villageunique ]->bFarmSwitch == FALSE ) {
			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_CONSTRUCT_NOTFARM,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}

	// ������ ���
	if( pclInfo->siStructureUnique == MINE_UNIQUE ) {
		if( pclVillageManager->pclVillageInfo[ villageunique ]->bIronSwitch == FALSE ) {
			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_CONSTRUCT_NOTMINE,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return;
		}
	}

	//[����] ���ո����� ��� �Ǽ� ������ ���� ������ 20�� �̻�.
	if( NEWMARKET_UNIQUE == pclInfo->siStructureUnique ) 
	{
		if( 20 < pclVillageManager->GetVillageRank(villageunique) ) return;
	}

	// �Ǽ� ������ �ǹ����� ����
	SI32 ref = pclVillageStructureSet->FindRefFromUnique( pclInfo->siStructureUnique );
	if( ref == -1 ) return;
	
	if( pclVillageStructureSet->pclVillageStructureInfo[ ref ]->bDestroyable == FALSE ) {
		// �Ǽ� ������ �ǹ��� �ƴ϶��,
		return;
	}

	// �̹� �Ǽ� �Ǿ� �ִ� �ǹ����� ���� 
	if( true == pclVillageManager->pclVillageInfo[ villageunique ]->clVillageVary.clStructureInfo.IsDuplicate( pclInfo->siStructureUnique ) ) 
	{
		// �̹� �Ǽ� �Ǿ� �ִ� �ǹ��̶��,
		return;
	}

	// ���� �ǹ� ���� ����
	SI32 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;
	SI32 siPenalty = 0;
		 if ( npcRate >= 500 )  siPenalty = 100;
	else if ( npcRate >= 400 )  siPenalty =  90;
	else if ( npcRate >= 300 )  siPenalty =  80;
	else if ( npcRate >= 200 )  siPenalty =  70;
	else						siPenalty =  60;

	GMONEY cost = pclVillageStructureSet->pclVillageStructureInfo[ ref ]->siNeedMoney * siPenalty / 100;

	// �ǹ��� �Ǽ��Ѵ�
	sDBRequest_BuildStructure sendMsg( id, villageunique, pclInfo->siSlot, pclInfo->siStructureUnique, cost, BUILD_BY_PERSON, pclVillageStructureSet->pclVillageStructureInfo[ ref ]->siNeedVillageScore );

	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

// �ǹ��� ��ü �Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_DESTROYSTRUCTURE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_DestroyStructure *pclInfo = (cltGameMsgRequest_DestroyStructure *)pclMsg->cData;	

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER )		return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	//�̰����� ���� �Դµ�!!!
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	// ������ villageunique �ٰŷ� �ǹ��� ������ ���Ѵ�. 
	cltStrInfo* pclinfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
	if(pclinfo == NULL)return ;

	// ���� ��¥�� DateVary�� ���Ѵ�. 
	SI32 datevary = pclTime->clDate.GetDateVary();
	if(datevary < pclinfo->clCityhallStrInfo.siLastDestroyStrDate + 30)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAILDESTROYSTR_NOLAST,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;	// �Ѵ� �̳��� ����. 
	}


	// ������ȸ �߿��� �ǹ��� ��ü�� �� ���� 
	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];
	if( pclCityHall->clGeneralMeetingInfo.siMatterType != 0 ) {
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_DESTROYSTR_MEETING,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}	


	// ��ü ������ �ǹ����� ����
	SI32 siStructureUnique = pclVillageManager->pclVillageInfo[ villageunique ]->clVillageVary.clStructureInfo.Get( pclInfo->siSlot );
	if( siStructureUnique == 0 ) {
		// ���Կ� �ǹ��� ����.
		return;
	}

	SI32 ref = pclVillageStructureSet->FindRefFromUnique( siStructureUnique );
	if( ref == -1 ) return;
    
	SI32 ranktype = 0;
	if ( ref >= 0 && ref < MAX_VILLAGE_STRUCTURE_NUMBER)
		ranktype = pclVillageStructureSet->GetRankTypeFromStructureName( pclVillageStructureSet->pclVillageStructureInfo[ ref ]->szName );
	if( ranktype == 0 ) return;

	sDBRequest_DestroyStructure sendMsg( id, villageunique, pclInfo->siSlot, siStructureUnique, ranktype, datevary);

	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VILLAGENOTICE( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	cltGameMsgRequest_VillageNotice *pclInfo = (cltGameMsgRequest_VillageNotice*)pclMsg->cData;	

	// ������ villageunique �ٰŷ� �ǹ��� ������ ���Ѵ�. 
	cltStrInfo* pclinfo = GetStrInfo( pclInfo->siVillageUnique, RANKTYPE_CITYHALL );
	
	if( pclinfo )
	{
		cltGameMsgResponse_VillageNotice ResPonse_VillageNotice( pclInfo->siVillageUnique, pclinfo->clCommonInfo.strNotice );
		cltMsg clMsg( GAMEMSG_RESPONSE_VILLAGENOTICE, sizeof(ResPonse_VillageNotice), (BYTE*)&ResPonse_VillageNotice );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ALLSTRCHIEFINFO( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 siVillageUnique = pclMsg->siData32[ 0 ];
	if( siVillageUnique < 0 || siVillageUnique >= MAX_VILLAGE_NUMBER)		return;

	cltGameMsgResponse_AllStrChiefInfo sendMsg;

	ZeroMemory( &sendMsg, sizeof( sendMsg ));

	cltRank* pclRank;

	for( int i = 1; i < MAX_RANKTYPE_NUMBER; ++i ) {

		cltVillageInfo *pVillageInfo = pclClient->pclVillageManager->pclVillageInfo[ siVillageUnique ];
		if( pVillageInfo == NULL ) continue;

		if( pVillageInfo->clVillageVary.clStructureInfo.IsThereStructure( i ) == false ) continue;

		pclRank = pclRankManager->GetRank( i, siVillageUnique );

		sendMsg.siRankType[ i ] = i;

		if( pclRank ) {
			
			if( pclRank->GetPersonID() ) {
				memcpy( sendMsg.szChiefPersonName[ i ], pclRank->GetName(), MAX_PLAYER_NAME );
				sendMsg.szChiefPersonName[ i ][ MAX_PLAYER_NAME - 1 ] = NULL;				
			} else {
				TCHAR* pText = GetTxtFromMgr(1561);
				StringCchCopy( sendMsg.szChiefPersonName[ i ], MAX_PLAYER_NAME, pText );
			}
		} else {
			TCHAR* pText = GetTxtFromMgr(1561);
			StringCchCopy( sendMsg.szChiefPersonName[ i ], MAX_PLAYER_NAME, pText );
		}
	}

	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg(GAMEMSG_RESPONSE_ALLSTRCHIEFINFO, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROFITTOCAPITALFUND( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_ProfitToCapitalFund *pclInfo = (cltGameMsgRequest_ProfitToCapitalFund *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	if( pclInfo->siMoney < 0 ) return;

	sDBRequest_ProfitToCapitalFund sendMsg( id, villageunique, pclInfo->siMoney );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_STARTEVENT( cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_StartEvent *pclInfo = (cltGameMsgRequest_StartEvent *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER )	return ;

	// [����] �ʺ��� ���� : �ʺ��� ������ ���� �̺�Ʈ ���� �ȵǰ�
	if ( pclClient->IsCountrySwitch(Switch_TutorialVillage) )
	{
		if ( Const_Beginner_Village == villageunique )
		{
			return;
		}
	}

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	
	cltCityhallEventInfo *pclEvent = pclCityHallManager->clEventManager.GetEventInfoFromEventID( pclInfo->siEventID );

	if( pclEvent == NULL ) return;

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );

	if( pclStrInfo == NULL ) return;
	
	// �����ڱ�(�ں���)�� ����Ѱ�?
	SI32 cost = (SI32)(pclEvent->siEventMoney * (pclItemManager->clItemStatistic.siItemPriceIndex / 10000000.));
	cost = max(cost, 2000000);

	if( pclStrInfo->clCommonInfo.clMoney.itMoney < cost ) {
		// �����ڱ� ����
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EVENT_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// �̺�Ʈ ����
	BOOL bStarted = FALSE;
	switch( pclEvent->eventid ) 
	{
		case 1:
			// �Ұ��縮 ��� �̺�Ʈ 
			{
				if( pclEventHunting->Start( villageunique, cost ) == true ) {
					// ���� 
					bStarted = TRUE;

				}
				else 
				{
					// ���� : �̹� ������..
					SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_EVENT_ALREADYSTARTED,  0, 0, pclCM->CR[id]->GetCharUnique() );
				}
			} 
			break;
		//[����] ���� �̺�Ʈ - ���� ����. 2008-3-26
		case 3:
			{
				// �̺�Ʈ ���̸� �ȵ�.
				if(pclMonsterAttackEvent->IsEvent())
				{
					SendServerResponseMsg( 0, SRVAL_MONSTER_ATTACK_EVENT,  MONSTER_ATTACK_EVENT_ALREADY_RUN, 0, pclCM->CR[id]->GetCharUnique() );
					return;
				}

				pclMonsterAttackEvent->StartEvent(villageunique);
				bStarted = TRUE;
			}
			break;
	}

	if( bStarted ) {

		sDBRequest_ChangeStrMoney sendMsg( CHANGESTRMONEY_EVENTPAY, pclInfo->siEventID, villageunique, RANKTYPE_CITYHALL, -cost );

		pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

	}


}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETVILLAGEMARK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetVillageMark *pclInfo = (cltGameMsgRequest_SetVillageMark *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );

	if( pclStrInfo == NULL ) return;
	
	// �����ڱ�(�ں���)�� ����Ѱ�?
	if( pclStrInfo->clCommonInfo.clMoney.itMoney < 1000000 ) {
		// �����ڱ� ����
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_VILLAGEMARK_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	sDBRequest_SetVillageMark sendMsg( id, villageunique, pclInfo->siVillageMark, &pclTime->clDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SETVILLAGEMAP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SetVillageMap *pclInfo = (cltGameMsgRequest_SetVillageMap *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank;
	clrank.Init();

	cltStrInfo *pclStrInfo = NULL;
	pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );	// ���������� ������ ���� ��� ��û �ڱݿ��� ��ݵ�

	//_LEON_HUNTMAP
	switch(pclInfo->siMapType)
	{
	case cltGameMsgRequest_SetVillageMap::MAPTYPE_CITYHALL:
		clrank.Set( RANKTYPE_CITYHALL, villageunique );
		//pclStrInfo = GetStrInfo( villageunique, RANKTYPE_CITYHALL );
		break;
	case cltGameMsgRequest_SetVillageMap::MAPTYPE_HUNT:
		{
			SI32 i = 0;
			clrank.Set( RANKTYPE_HUNT, villageunique );
			//pclStrInfo = GetStrInfo( villageunique, RANKTYPE_HUNT );
			for( i = 0; i<MAX_HUNT_MAP_NUMBER-1; i++)
			{
				if(villageunique == pclMapManager->GetParentMap(HUNT_MAP_START + i ) )
				{
					villageunique = HUNT_MAP_START + i;
					break;
				}
			}
			if( villageunique == HUNT_MAP_START + MAX_HUNT_MAP_NUMBER-1 )
				return;

			cltMapTypeInfo *pMapTypeInfo = NULL;

			for( i=0; i<MAX_HUNT_MAP_NUMBER-1; i++)
			{
				pMapTypeInfo = NULL;
				pMapTypeInfo = pclMapManager->pclMapTypeManager->pclMapTypeInfo[ i ];

				if( pMapTypeInfo == NULL ) continue;
				if( pMapTypeInfo->siAdaptHuntType != HUNTTYPE_ALL ) continue;
				SI32 mapunique = pMapTypeInfo->siMapUnique;
				if( pclInfo->siVillageMapUnique == mapunique ) break;
			}

			if( i >= MAX_HUNT_MAP_NUMBER-1 ) return;		// �߸��� mapunique...
		}
		break;
	default:
		return;
	}

	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
		return;

	if( pclStrInfo == NULL ) return;
	
	cltMapTypeInfo *pMapTypeInfo = NULL;

	for( int i = 0; i < MAX_MAPTYPE_NUMBER; ++i ) {

		pMapTypeInfo = pclMapManager->pclMapTypeManager->pclMapTypeInfo[ i ];

		if( pMapTypeInfo == NULL ) continue;

		if( pMapTypeInfo->siMapUnique == pclInfo->siVillageMapUnique ) break;
	}

	if( i == MAX_MAPTYPE_NUMBER ) return;

	if( pMapTypeInfo == NULL ) return;

	// �����ڱ�(�ں���)�� ����Ѱ�? ���������� ������ ���� ��� ��û �ڱݿ��� ������.
	if( pclStrInfo->clCommonInfo.clMoney.itMoney < pMapTypeInfo->siAdaptNeedVillageMoney ) {
		// �����ڱ� ����

		switch(pclInfo->siMapType)
		{
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_CITYHALL:
			SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_CITYHALL_FAIL_VILLAGEMAP_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
			break;
		case cltGameMsgRequest_SetVillageMap::MAPTYPE_HUNT:
			SendServerResponseMsg( RANKTYPE_HUNT, SRVAL_HUNT_FAIL_HUNTMAP_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
			break;
		default:
			return;
		}

		return;
	}

	sDBRequest_SetVillageMap sendMsg( id, villageunique, pclInfo->siVillageMapUnique, pMapTypeInfo->siAdaptNeedVillageMoney, pclInfo->siMapType );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_VILLAGELEVELDETAILINFO( cltMsg *pclMsg, SI32 id )
{
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER )		return ;


	cltGameMsgResponse_VillageLevelDetailInfo sendMsg;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	pclCityHall->clLevelInfo.siVillageTotalScore = pclVillageManager->pclVillageInfo[ villageunique ]->clVillageVary.siTotalVillageScore;
	sendMsg.clLevelInfo.Set( &pclCityHall->clLevelInfo );
	
	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg(GAMEMSG_RESPONSE_VILLAGELEVELDETAILINFO, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_INFO(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;



	cltGameMsgResponse_GeneralMeetingInfo sendMsg;

	sendMsg.clGeneralMeetingInfo = pclCityHall->clGeneralMeetingInfo;

	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg(GAMEMSG_RESPONSE_GENERALMEETING_INFO, sizeof( sendMsg ), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_SUGGEST(cltMsg* pclMsg, SI32 id)//������ȸ�����ϱ�.
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_GeneralMeetingSuggest *pclInfo = (cltGameMsgRequest_GeneralMeetingSuggest *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	// [�߰� : Ȳ���� 2008. 2. 20 => ������ȸ�� ���� ���� ��ڰ� ������ ������ȸ�� �ߵ������ϰ� �ؾ� �Ѵ�. ]
	if( true == pclClient->IsCountrySwitch( Switch_GeneralMeetingSuggest ) )
	{
		if( false == pclClient->pclVillageManager->pclVillageInfo[villageunique]->clVillageVary.m_bGeneralMeetingSuggest )
		{
			SendServerResponseMsg(0, SRVAL_GENERAL_MEETING_SUGGEST_OFF_FAIL, 0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	}

	cltStrInfo* pclStrInfo = pclCityHallManager->GetStrInfo(villageunique);
	
	if(	   pclStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_BANKRUPT 
		|| pclStrInfo->clCityhallStrInfo.usCurStatus == CITYHALL_BEING_INITIALIZED  )
	{
		// ������ �Ļ� �����Դϴ�.. => ������ȸ ���� ���� => �˸�
		cltGameMsgResponse_NotifyClientAboutCityHallState clinfo( villageunique,  pclStrInfo->clCityhallStrInfo.usCurStatus, cltGameMsgResponse_NotifyClientAboutCityHallState::ANNOUNCEMENT_TYPE_FAIL_GENERALMEETING_SUGGEST );
		cltMsg clMsg(GAMEMSG_RESPONSE_NOTIFYCLIENTABOUTCITYHALLSTATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��� ���� ������
	cltDate clStartDate;
	clStartDate.Set( &pclTime->clDate );
	SI32 StartDate = clStartDate.GetDateVary();

	cltDate clDate;
	clDate.Set( &pclTime->clDate );
	//KHY - 1115 - ������ȸ �ߵ� ���� ����. - �ĺ��� ���� ���� 1�޸� ��ٸ���.
	//clDate.AddMonth( 1 );  
	//[����] ������ȸ ���� �ð��� ���ӽð� 3�޷� ����. => 2008-7-21
	clDate.AddMonth( 3 );

	sDBRequest_GeneralMeeting_SuggestChief sendMsg( id, villageunique, personid, pclInfo->szCandidateName, StartDate, &clDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_VOTE(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_GeneralMeetingVote *pclInfo = (cltGameMsgRequest_GeneralMeetingVote *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��ǥ�����ΰ�
	if( pclCityHall->clGeneralMeetingInfo.IsVoter( personid ) == FALSE ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_GENERALMEETING_FAIL_VOTE_NOTVOTER,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// �̹� ��ǥ �Ͽ���
	if( pclCityHall->clGeneralMeetingInfo.IsAleadyVote( personid ) ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_GENERALMEETING_FAIL_VOTE_ALREADY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	sDBRequest_GeneralMeeting_Vote sendMsg( id, villageunique, personid, pclInfo->siVoteType );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_VOTE_REFRESH(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_GeneralMeetingVoteRefresh *pclInfo = (cltGameMsgRequest_GeneralMeetingVoteRefresh*)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;

	cltGameMsgResponse_GeneralMeetingInfo sendMsg;

	sendMsg.clGeneralMeetingInfo = pclCityHall->clGeneralMeetingInfo;

	// Ŭ���̾�Ʈ�� ������ ������. 
	if( pclCM->IsValidID(id) ) {	
		cltMsg clMsg(GAMEMSG_RESPONSE_GENERALMEETING_INFO, sizeof( sendMsg ), (BYTE*)&sendMsg );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}


}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_ACCEPTCANDIDATE(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;
	
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	if( pclCityHall->clGeneralMeetingInfo.siMatterType == 0 ||
		pclCityHall->clGeneralMeetingInfo.siAcceptCandidate == 1 ) {
		return;
	}

	if( personid != pclCityHall->clGeneralMeetingInfo.siCandidatePersonID ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_GENERALMEETING_FAIL_ACCEPTCANDIDATE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	//KHY - 1115 - ������ȸ �ߵ� ���� ����. -����� �ĺ��ڰ� ���� ���Ǹ� �ϴ� ���� 2���� ��ǥ�Ⱓ���� �����Ѵ�.
	/*cltDate clStartDate;
	clStartDate.Set( &pclTime->clDate );
	SI32 StartDate = clStartDate.GetDateVary();
	
	cltDate clDate;
	clDate.Set( &pclTime->clDate );
	clDate.AddMonth( 2 );*/

	//[����] ������ȸ ������ ����, ��ǥ �ð��� �̹� �����Ƿ� �״�� ����.( �ߵ��� ���� �ߵ��� 3�ް� ) => 2008-7-21
	SI32	StartDate = pclCityHall->clGeneralMeetingInfo.clStartDate.GetDateVary();
	cltDate clDate	  = pclCityHall->clGeneralMeetingInfo.clCloseDate;

	sDBRequest_GeneralMeeting_AcceptCandidate sendMsg(	id, 
														villageunique, 
														personid, 
														StartDate, 
														&clDate );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_PARTICIPATE(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_GeneralMeetingParticipate *pclInfo = (cltGameMsgRequest_GeneralMeetingParticipate *)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	sDBRequest_GeneralMeeting_SetVoterState sendMsg( pclInfo->siVillageUnique, personid, pclInfo->siParticipate );
	sendMsg.usCharID = id;
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHAT(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id))
		return;

	cltGameMsgRequest_GeneralMeetingChat *pclInfo = (cltGameMsgRequest_GeneralMeetingChat*)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();


	// Ŭ���̾�Ʈ�� ������ ������. 

	cltGameMsgResponse_GeneralMeetingChat sendMsg;

	memcpy( sendMsg.szName, pclCM->CR[id]->GetName(), MAX_PLAYER_NAME );
	sendMsg.szName[ MAX_PLAYER_NAME - 1 ] = NULL;

	memcpy( sendMsg.szText, pclInfo->szText, 128 );
	sendMsg.szText[ 127 ] = NULL;

	sendMsg.textlen = _tcslen( sendMsg.szText );


	cltMsg clMsg(GAMEMSG_RESPONSE_GENERALMEETING_CHAT, MAX_PLAYER_NAME + 16 + sendMsg.textlen, (BYTE*)&sendMsg );
	pclCityHall->clChatMemberManager.SendMsg( (BYTE*)&clMsg );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHATJOIN(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��ǥ�����ΰ�
	if( pclCityHall->clGeneralMeetingInfo.IsVoter( personid ) == FALSE &&
		pclCityHall->clGeneralMeetingInfo.siCandidatePersonID != personid &&
		pclCM->CR[id]->GetGameMasterLevel() < 100 ) {
		SendServerResponseMsg( RANKTYPE_CITYHALL, SRVAL_GENERALMEETING_FAIL_VOTE_NOTVOTER,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	pclCityHall->clChatMemberManager.AddChatMember( id, pclCM->CR[id]->pclCI->GetPersonID() );

	// Ŭ���̾�Ʈ�� ������ ������. 
	cltMsg clMsg(GAMEMSG_RESPONSE_GENERALMEETING_CHATJOIN, 0 );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GENERALMEETING_CHATOUT(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER ) return ;

	cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[ villageunique ];

	if( pclCityHall == NULL ) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	pclCityHall->clChatMemberManager.DelChatMember( pclCM->CR[id]->pclCI->GetPersonID() );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGESTRBASEMONEY( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_ChangeStrBaseMoney *pclInfo = (cltGameMsgRequest_ChangeStrBaseMoney *)pclMsg->cData;

	if( pclInfo == NULL )
		return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}


	cltStrInfo* pStrInfo = pclCityHallManager->GetStrInfo( villageunique );

	if( pclInfo->siMoney > pStrInfo->clCommonInfo.clMoney.itMoney )
		return;

	sDBRequest_ChangeStrBaseMoney sendMsg( id, villageunique, pclInfo->siType, pclInfo->siMoney );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&sendMsg );
}


// �̺�Ʈ NPC ��� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HIREEVENTNPC( cltMsg *pclMsg, SI32 id )
{

	cltGameMsgRequest_HireEventNPC *pclInfo = (cltGameMsgRequest_HireEventNPC *)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclInfo->siVillageUnique ;
	if(villageunique <= 0)return ;

	// ������ �ִ°� 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltSimpleRank clrank( RANKTYPE_CITYHALL, villageunique );
	if( pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return;
	}

	SI32 eventNpcKind = pclInfo->siEventNpcKind;

	cltStrInfo* pclinfo = pclCityHallManager->GetStrInfo(villageunique);
	if( pclinfo == NULL ) return;

	// �Ȱ��� NPC�� �ٽ� ����� �� ����.
	SI32 siNPCKind = 0;
	for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++)
	{
		siNPCKind = pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind;		
		if(siNPCKind == eventNpcKind) 
		{
			return;
		}

		// ũ�������� Ʈ�� 2�ܰ谡�ִٸ�.
		if(siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREE1")))
		{
			// ��ġ�Ϸ��� �������� ������ ���� 1�ܰ� �̸� ��ġ ����.
			if(eventNpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_CHRISTMASTREEBASE")))
			{
				return;
			}
		}

		// ������ ���� 2�ܰ谡 ������.
		if(siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUE")))
		{
			// ��ġ�Ϸ��� �������� ������ ���� 1�ܰ� �̸� ��ġ ����.
			if(eventNpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_ROULETTESTATUEBASE")))
			{
				return;
			}
		}
		// �ҷ��� �д� 2�ܰ谡 ������ //Switch_HalloweenEvent
		if(siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEEN")))
		{
			// ��ġ �Ϸ��� �������� �ҷ��� �д� ���̽��� ����
			if(eventNpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_HALLOWEENBASE")))
			{
				return;
			}
		}
		// �ų��̺�Ʈ �ǹ� 2�ܰ谡 ������
		if(siNPCKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREE")))
		{
			// ��ġ �Ϸ��� �������� �ҷ��� �д� ���̽��� ����
			if(eventNpcKind == pclClient->GetUniqueFromHash(TEXT("KIND_NEWYEARTREEBASE")))
			{
				return;
			}
		}
	}

	SI64 siPayment = 0;
	// �ų� �̺�Ʈ �Ⱓ���� ������ ����� �ֵ���.	

	//---------------------------------------------------------------------------------------------
	// �̺�Ʈ NPC ���� ����
	if( eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_KADOMACH")) ||
		eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_NEWYEARTREE"))	)
	{
		if(true == NewYearEventDay())
		{			
			siPayment = pclClient->GetGlobalValue(TEXT("GV_NewYearValue"));	//�ų� Ʈ�� ����� ���� �о� �´�	
		}
	}
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_RETURNTOWER"))) 
	{
		SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

		if (npcrate < 500) siPayment = 5000000;
		else if (npcrate < 1000) siPayment = 10000000;
		else if (npcrate < 1500) siPayment = 15000000;
		else if (npcrate < 2000) siPayment = 20000000;
		else if (npcrate < 2500) siPayment = 25000000;
		else if (npcrate < 3000) siPayment = 30000000;
		else{
			siPayment = 35000000;
		}
	}
	//[����] ������ ���� ���� => 2008-6-12
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_ROULETTESTATUEBASE"))) 
	{
		SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

		if (npcrate < 100)		 siPayment =   5000000;
		else if (npcrate < 300)  siPayment =  10000000;
		else if (npcrate < 700)  siPayment =  20000000;
		else if (npcrate < 1000) siPayment =  40000000;
		else if (npcrate < 2000) siPayment =  60000000;
		else if (npcrate < 3000) siPayment =  80000000;
		else					 siPayment = 100000000;
	}
	//[����] �ҷ��� �д� //Switch_HalloweenEvent
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_HALLOWEENBASE"))) 
	{
		SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

		if (npcrate < 100)		 siPayment =   1000000;
		else if (npcrate < 300)  siPayment =  2000000;
		else if (npcrate < 700)  siPayment =  8000000;
		else if (npcrate < 1000) siPayment =  10000000;
		else if (npcrate < 2000) siPayment =  15000000;
		else if (npcrate < 3000) siPayment =  20000000;
		else					 siPayment = 50000000;
	}
	//KHY - 1113 - ũ�������� �̺�Ʈ - ���� �������� �о�´�.
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_PINE_TREE")) ||
		eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_CHRISTMASTREEBASE")) ) 
	{
		//siPayment = pclClient->GetGlobalValue(TEXT("GV_Christmasvalue"));	//Ʈ�� ����� ���� �о� �´�
		SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

		if (npcrate < 100)		  siPayment =  5000000;
		else if (npcrate < 300)   siPayment =  10000000;
		else if (npcrate < 700)   siPayment =  20000000;
		else if (npcrate < 1000)  siPayment =  40000000;
		else if (npcrate < 2000)  siPayment =  60000000;
		else if (npcrate < 3000)  siPayment =  80000000;
		else if (npcrate < 4000)  siPayment =  100000000;
		else if (npcrate < 5500)  siPayment =  120000000;
		else if (npcrate < 8500)  siPayment =  160000000;
		else if (npcrate < 14500) siPayment =  280000000;
		else if (npcrate < 25500) siPayment =  500000000;
		else if (npcrate < 33500) siPayment =  650000000;
		else if (npcrate < 35500) siPayment =  800000000;
		else					  siPayment =  800000000;
	}
	// ���� : PCK - ���������� �̺�Ʈ (08.12.16)
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_HINADOLL"))) 
	{
		SI64 npcRate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;//NPCRate�� �о� �´�.

		siPayment = npcRate * 300000;
	}
	// [���] �ų��̺�Ʈ ������ (08.11.24)
	else if(eventNpcKind == pclClient->GetUniqueFromHash( TEXT("KIND_NEWYEARTREEBASE"))) 
	{
		SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

		if (npcrate < 100)		 siPayment =   5000000;
		else if (npcrate < 300)  siPayment =  10000000;
		else if (npcrate < 700)  siPayment =  20000000;
		else if (npcrate < 1000) siPayment =  40000000;
		else if (npcrate < 2000) siPayment =  60000000;
		else if (npcrate < 3000) siPayment =  80000000;
		// KHY - 1021 - NPCRate �� Ȯ��.
		else if (npcrate < 4000) siPayment =  100000000;
		else if (npcrate < 5500) siPayment =  120000000;
		else if (npcrate < 8500) siPayment =  160000000;
		else if (npcrate < 14500) siPayment = 280000000;
		else if (npcrate < 25500) siPayment = 500000000;
		else if (npcrate < 33500) siPayment = 650000000;
		else					  siPayment = 800000000;
	}

	//---------------------------------------------------------------------------------------------
	if( siPayment <= 0 )				return;

	for (SI32 i = 0; i<MAX_HIRED_EVENTNPC_NUM; i++) {

		if( pclinfo->clCityhallStrInfo.clHiredEventNPC[i].siNPCKind == 0 )
		{
			if(pclKindInfoSet->IsValidKind(eventNpcKind) == false) 
				return;

			if(eventNpcKind > 0)
			{
				sDBRequest_HireNPC clMsg( id, villageunique, i , eventNpcKind, siPayment, 0, &pclTime->clDate, HIRENPC_HIREEVENTNPC );
				pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
			}

			return;
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EVENT_INSERTMATERIAL( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_Event_InsertMaterial *pclInfo = (cltGameMsgRequest_Event_InsertMaterial *)pclMsg->cData;

	if( pclCM->IsValidID(id) == false)				return;
	if( pclInfo->m_siVillageUnique < 0 )			return;
	if( pclInfo->m_siConstructType <= 0 )			return;

	cltEventStructureUnit* pEventStruct = pclEventStructure->GetEventStructure(pclInfo->m_siConstructType);
	if( pEventStruct == NULL )						return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if( pclchar == NULL)							return;

	//---------------------------------------------
	// �����ڿ��� ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();


	//---------------------------------------------
	// �����ڿ��� ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	DBStructMaterialInfo clinfo[MAX_MATERIAL_NUMBER];

	int		i, j;
	bool	bFind = false;

	for(i=0; i<MAX_MATERIAL_NUMBER; i++)
	{
		clinfo[i].siItemUnique	= pEventStruct->clMaterial[i].siUnique;
		clinfo[i].siNeedNum		= pEventStruct->clMaterial[i].siNeedNum;
		clinfo[i].siUseItemNum	= 0;
		clinfo[i].siStgPos		= -1;

		bFind = false;
		for(j=0; j<MAX_MATERIAL_NUMBER; j++)
		{
			if( pclInfo->m_siItemUnique[j] == clinfo[i].siItemUnique )
			{
				clinfo[i].siUseItemNum = pclInfo->m_siItemNum[j];
				bFind = true;
			}
		}

		// ���� ���� Unique �� 0���� �����Ѵ�.
		if(bFind == false)
		{
			clinfo[i].siItemUnique	= 0;
			clinfo[i].siNeedNum		= 0;
		}

		if(clinfo[i].siUseItemNum <= 0)
		{
			clinfo[i].siItemUnique	= 0;
			clinfo[i].siNeedNum		= 0;
		}
	}

	// ���޵� ��� ��Ḧ �κ����� ã�´�.
	for( i = 0;i < MAX_MATERIAL_NUMBER; i++)
	{
		SI32 siMaterialUnique	= clinfo[i].siItemUnique;
		SI32 siMaterialNum		= clinfo[i].siUseItemNum;

		if( siMaterialUnique <= 0 )					continue;
		if( siMaterialNum < 0 )						continue;

		// �κ����� �ش� ��Ḧ ã�´�. 
		for( j = PERSONITEM_INV0; j < PERSONITEM_INV0 + MAX_INVITEM_PER_PERSON; j++ )
		{
			cltItem* pclItem = &pclchar->pclCI->clCharItem.clItem[j];
			if(pclItem == NULL)					continue;

			if( pclItem->siUnique == siMaterialUnique && pclItem->siItemNum >= siMaterialNum )
			{
				clinfo[i].siItemUnique	= siMaterialUnique;
				clinfo[i].siStgPos		= j;
				clinfo[i].siUseItemNum	= siMaterialNum;
			
				break;
			}
		}
	}

	sDBRequest_Event_InsertMaterial clMsg( id, pclchar->pclCI->GetPersonID(), pclInfo->m_siVillageUnique , pclInfo->m_siConstructType, clinfo );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALLIST( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_Event_MaterialList *pclInfo = (cltGameMsgRequest_Event_MaterialList *)pclMsg->cData;

	if( pclCM->IsValidID(id) == false)			return;

	if( pclInfo->m_siConstructType <= 0)		return;
	if( pclInfo->m_siVillageUnique < 0)			return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar == NULL)							return;

	sDBRequest_Event_MaterialList clMsg( id, pclchar->pclCI->GetPersonID(), pclInfo->m_siVillageUnique , pclInfo->m_siConstructType );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_EVENT_MATERIALCOMPLETE( cltMsg *pclMsg, SI32 id )
{
	cltGameMsgRequest_Event_MaterialComplete *pclInfo = (cltGameMsgRequest_Event_MaterialComplete *)pclMsg->cData;

	if( pclCM->IsValidID(id) == false)			return;

	if( pclInfo->m_siConstructType <= 0)		return;
	if( pclInfo->m_siVillageUnique < 0)			return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(pclchar == NULL)							return;

	cltEventStructureUnit* pEventStruct = pclEventStructure->GetEventStructure(pclInfo->m_siConstructType);
	if( pEventStruct == NULL )						return;

	SI16	siItemUnique[MAX_MATERIAL_NUMBER];	// �Ǽ� ��� ����
	SI16	siItemNum[MAX_MATERIAL_NUMBER];		// �Ǽ� ��� ����

	// �Ǽ� ��ῡ�� �ʿ䰳���� ã�� ä���.
	for(int i = 0; i < MAX_MATERIAL_NUMBER; i++)
	{
		cltMaterialInfo* pMaterial = &pEventStruct->clMaterial[i];
		if(pMaterial == NULL)					
			continue;

		siItemUnique[i] = pMaterial->siUnique;
		siItemNum[i]    = pMaterial->siNeedNum;
	}

	cltItem	clRewardItem;
	clRewardItem.Init();

	SI16 itempos = 0;
	cltItem cltoitem;
	SI32 rtnvalue = 0;

	cltoitem.Init();

	if( pEventStruct->m_siRewardItemUnique > 0 && pEventStruct->m_siRewardItemNum > 0 )
	{
		SI16 brareswitch = 0;
		SI32 usedate = 0;
		if(pclClient->pclItemManager->MakeRandItemUnique( pEventStruct->m_siRewardItemUnique, &clRewardItem, 0, 0, &brareswitch,0,0,0,0,0,usedate) == false)	return;

		// ������ �����Ѵ�. 
		// ��ø ������ �������� ���ϴ� ������ŭ ���� �� �ִ�. 
		if(clRewardItem.CanPile(pclClient->pclItemManager) == true)		
			clRewardItem.SetItemNum(pEventStruct->m_siRewardItemNum);
		else															
			clRewardItem.SetItemNum(1);

		// �ش�������� �κ��� ���� �� �ִ��� Ȯ���Ѵ�. 
		if(pclchar->CanAddInv(INVMODE_ALL, &clRewardItem, &itempos, &cltoitem, &rtnvalue) == false)
		{
			return;
		}
	}

	sDBRequest_Event_MaterialComplete clMsg( id, pclchar->pclCI->GetPersonID(), pclInfo->m_siVillageUnique , pclInfo->m_siConstructType,
											 siItemUnique, siItemNum, itempos, &clRewardItem, clRewardItem.CanPile(pclItemManager) );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DONATEVILLAGEMONEY( cltMsg *pclMsg, SI32 id )
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_DonateVillageMoney *pclInfo = (cltGameMsgRequest_DonateVillageMoney *)pclMsg->cData;

	// ����� ������ ��ġ�� Ʋ���ٸ� ����
	SI32 villageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageUnique != pclInfo->siVillageUnique )
		return;

	if( villageUnique < 0 || villageUnique > CUR_GLOBAL_VILLAGE_LIMIT )
		return;

	// ����� ���� �� �����ݺ��� ���ٸ� ����
	SI64 donateMoney = pclInfo->siDonateMoney;
	SI64 myMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();
	if( donateMoney > myMoney )
	{
		// ������ ���� ��α��� �� ����.
		SendServerResponseMsg(RANKTYPE_CITYHALL, SRVAL_CITYHALL_DONATE_OVERMONEY,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
	}
	

	if( donateMoney < MIN_DONATE_MONEY )
		return;

	SI32 personID = pclCM->CR[id]->pclCI->GetPersonID();

	cltDate clDonateDate;
	clDonateDate.Set( &pclTime->clDate );
	SI32 donateDate = clDonateDate.GetDateVary();

	sDBRequest_DonateVillageMoney clMsg( id, personID , villageUnique, donateDate, pclInfo->siDonateMoney );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );

	pclDelMoneyStatistics->Add(DELMONEY_DONATE, pclInfo->siDonateMoney);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DONATEMEMBERLIST( cltMsg *pclMsg, SI32 id )
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_DonateMemberList *pclInfo = (cltGameMsgRequest_DonateMemberList *)pclMsg->cData;

	SI32 villageUnique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageUnique < 0 || villageUnique > CUR_GLOBAL_VILLAGE_LIMIT )
		return;

	if( 0 > pclInfo->siRequestPage )
		return;

	sDBRequest_DonateMemberList clMsg( id, villageUnique, pclInfo->siRequestPage );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
}




