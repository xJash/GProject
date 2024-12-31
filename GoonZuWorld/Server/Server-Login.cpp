//---------------------------------
// 2003/6/21 김태곤
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

//-------------------------------------
// CommonLogic
//-------------------------------------
#include "msgType-Person.h"
#include "MsgType-System.h"

#include "../../Server/AuthServer/AuthMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

#include "JwLib\IsCorrectID\IsCorrectID.h"

#include "MsgRval-Define.h"

//케릭터 삭제예정을위해 시스템 시간관련 추가.
#include "../NLib/NUtil.h"


void cltServer::DoMsg_GAMEMSG_REQUEST_LOGIN(cltMsg* pclMsg, SI32 id)
{
	if( ConstServiceArea_China == siServiceArea )
	{
		if( false == pclCM->IsValidID(id) )
		{
			SendServerResponseMsg(0, SRVAL_LOGINFAIL_LIMITMAXUSER,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}

		if( 0 == pclCM->CR[id]->GetGameMasterLevel() )
		{
			if( siCurUserNum >= siLimitMaxUserNumber )
			{
				SendServerResponseMsg(0, SRVAL_LOGINFAIL_LIMITMAXUSER,  0, 0, pclCM->CR[id]->GetCharUnique());
				return;
			}
		}
	}
	//-----------------------------------------------------
	// 사용자로부터 들어온 정보를 얻어와서 인증한다. 
	//-----------------------------------------------------
	cltLogInInfo* pcllogininfo = (cltLogInInfo* )pclMsg->cData;

	switch( pcllogininfo->uiGameMode )
	{
	case 0:	
		siWndInterfaceNum++;				// 현재 서버의 재시작 후 윈도우창 + 윈도우 인터페이스 사용자 누적수
		break;
	case 1:
		siWnd_NewInterfaceNum++;			// 현재 서버의 재시작 후 윈도우창 + 새인터페이스 사용자 누적수
		break;
	case 2:
		siFullWnd_NewInterfaceNum++;		// 현재 서버의 재시작 후 전체화면 + 새인터페이스 사용자 누적수
		break;
	}
	
	// 인증서버로 인증을 요청한다. 
	sRequest_GameAuth clMsg;
	clMsg.packetHeader.usSize = sizeof( clMsg );
	clMsg.packetHeader.usCmd = AUTHMSG_REQUEST_GAMEAUTH;
	
	clMsg.usCharID	= id;
	clMsg.siAuthKey	= pcllogininfo->siAuthKey;
	MStrCpy(clMsg.userid,	pcllogininfo->szID,			MAX_PLAYER_NAME );
	MStrCpy(clMsg.userpw,	pcllogininfo->szPassword,	MAX_PLAYER_NAME );
	MStrCpy(clMsg.userServerID,   szServerID, MAX_PLAYER_NAME );
	MStrCpy(clMsg.userIP,   pclCM->CR[id]->GetSession()->GetIP(), MAX_PLAYER_NAME );
	
	pclFrontAuthProcess->SendMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HANAUTH_LOGIN(cltMsg* pclMsg, SI32 id)
{
	//-----------------------------------------------------
	// 사용자로부터 들어온 정보를 얻어와서 인증한다. 
	//-----------------------------------------------------
	cltLogIn_HanAuthInfo* pcllogininfo = (cltLogIn_HanAuthInfo* )pclMsg->cData;

	switch( pcllogininfo->uiGameMode )
	{
	case 0:	
		siWndInterfaceNum++;				// 현재 서버의 재시작 후 윈도우창 + 윈도우 인터페이스 사용자 누적수
		break;
	case 1:
		siWnd_NewInterfaceNum++;			// 현재 서버의 재시작 후 윈도우창 + 새인터페이스 사용자 누적수
		break;
	case 2:
		siFullWnd_NewInterfaceNum++;		// 현재 서버의 재시작 후 전체화면 + 새인터페이스 사용자 누적수
		break;
	}

	// 인증서버로 인증을 요청한다. 
	sRequest_HanAuth_GameAuth clMsg;
	clMsg.packetHeader.usSize = sizeof( clMsg );
	clMsg.packetHeader.usCmd = AUTHMSG_REQUEST_HANAUTH_GAMEAUTH;
	clMsg.usServerAge = siServiceAge;

	clMsg.usCharID	= id;
	clMsg.siAuthKey	= pcllogininfo->siAuthKey;
	MStrCpy(clMsg.authstring,	pcllogininfo->szAuthString,	2048 );
	MStrCpy(clMsg.userid,		pcllogininfo->szID,				MAX_PLAYER_NAME );

	pclFrontAuthProcess->SendMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_HANAUTH_GAMERUNAUTH(cltMsg* pclMsg, SI32 id)
{
	//-----------------------------------------------------
	// 사용자로부터 들어온 정보를 얻어와서 인증한다. 
	//-----------------------------------------------------
	cltHanAuth_GameRunAuth* pclgamerunauth = (cltHanAuth_GameRunAuth* )pclMsg->cData;

	// 인증서버로 인증을 요청한다. 
/*	sRequest_HanAuth_GameRunAuth clMsg;
	clMsg.packetHeader.usSize = sizeof( clMsg );
	clMsg.packetHeader.usCmd = AUTHMSG_REQUEST_HANAUTH_GAMERUNAUTH;
	clMsg.usServerAge = siServiceAge;

	clMsg.usCharID	= id;
	MStrCpy(clMsg.authstring,	pclgamerunauth->authstring,	2048 );
	MStrCpy(clMsg.userid,		pclgamerunauth->userid,		MAX_PLAYER_NAME );

	pclFrontAuthProcess->SendMsg((sPacketHeader*)&clMsg);
	*/
}

void cltServer::DoMsg_GAMEMSG_REQUEST_TAIWAN_LOGIN(cltMsg* pclMsg, SI32 id)
{
	//-----------------------------------------------------
	// 사용자로부터 들어온 정보를 얻어와서 인증한다. 
	//-----------------------------------------------------
	cltLogIn_TaiwanInfo* pcllogininfo = (cltLogIn_TaiwanInfo* )pclMsg->cData;

	switch( pcllogininfo->uiGameMode )
	{
	case 0:	
		siWndInterfaceNum++;				// 현재 서버의 재시작 후 윈도우창 + 윈도우 인터페이스 사용자 누적수
		break;
	case 1:
		siWnd_NewInterfaceNum++;			// 현재 서버의 재시작 후 윈도우창 + 새인터페이스 사용자 누적수
		break;
	case 2:
		siFullWnd_NewInterfaceNum++;		// 현재 서버의 재시작 후 전체화면 + 새인터페이스 사용자 누적수
		break;
	}

	// 인증서버로 인증을 요청한다. 
	sRequest_Taiwan_GameAuth clMsg;
	clMsg.packetHeader.usSize = sizeof( clMsg );
	clMsg.packetHeader.usCmd = AUTHMSG_REQUEST_TAIWAN_GAMEAUTH;

	clMsg.usCharID	= id;
	clMsg.siAuthKey	= pcllogininfo->siAuthKey;

	TCHAR* pFind = _tcsstr(pcllogininfo->szGameAccount, "_");
	if(pFind)		{		*pFind = '\0';		}

	MStrCpy(clMsg.gameaccount,		pcllogininfo->szGameAccount,		sizeof(clMsg.gameaccount) );
	MStrCpy(clMsg.onetinepassword,	pcllogininfo->szOneTimePassword,	sizeof(clMsg.onetinepassword) );

	pclFrontAuthProcess->SendMsg((sPacketHeader*)&clMsg);
}



void cltServer::DoMsg_GAMEMSG_REQUEST_SELECTCHAR(cltMsg* pclMsg, SI32 id)
{
	SI32 index	= pclMsg->siData32[0];
	if(index < 0 || index >= 3)return ;
	
	SI32 idnum	= pclCM->CR[id]->pclCI->clBI.siIDNum;
	if(idnum <= 0)return;

	//---------------------------------------------------
	// 선택한 Person의 전체 정보를 DB에 요청한다. 
	//---------------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	
    // 이미 선택된 캐릭터이고 인덱스가 이전의 것과 같다면 중복 로그인을 요청하는 것이다. 
	if(pclchar->GetKind() != KIND_SYSTEM &&  pclchar->pclCI->clBI.uiIndex == index)
	{
		//------------------------------------------------------------------------------------	
		// [수정 : 황진성 2007. 11. 9 캐릭터를 선택할때 중복된 캐릭터를 선택시 아이템몰이 사라지는 문제 해결을 위해 
		//								중복되는 캐릭터도 다시 초기화 시킨다.]
		
		//return;

		//------------------------------------------------------------------------------------
	}
	


	// 피가 없거나 전투중이면 바꿀 수없다.
	// pvp 중이면 나갈수 바꿀수 없다.
	if ( pclchar->IsAutoHunting()  || pclchar->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP  ) )
	{
		SendServerResponseMsg(0, SRVAL_NO_BATTLEQUIT,  0, 0, pclchar->GetCharUnique());
		return ;
	}
	if ( pclchar->pclCI->clIP.GetLife() <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_NO_DIEQUIT,  0, 0, pclchar->GetCharUnique());
		return ;
	}

	TCHAR* pip = pclchar->GetSession()->GetIP();
	if(pip)
	{
		sDBRequest_PersonTotalInfoGetByIDNum clMsg( id, idnum, index, pclchar->GetSession()->GetIP(),(bool)pclchar->pclCI->clDormancyInfo.GetDormancyState(), pclchar->bTiredSystem, pclchar->dwPlayingTime );
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);
	}
}



void cltServer::DoMsg_GAMEMSG_REQUEST_MAKENEWCHAR(cltMsg* pclMsg, SI32 id)
{
	cltCharListInfo* pclCharlistInfo = (cltCharListInfo*)pclMsg->cData;

	TCHAR buf[128];
	StringCchPrintf(buf, 128, pclCharlistInfo->clBI.GetName() );
#ifdef _IAF_EXPORT
	if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
	{
		TCHAR ResultBuf[1024] = "";
		IAF::Filtering( buf, ResultBuf, sizeof(ResultBuf), IAF::FILTER_CHARACTER );
		memcpy( buf, ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
	}
#else
    m_pCAbuseFilter->CheckAbuse(buf);
#endif

	if ( IsCorrectID( buf ) == FALSE )
		return;

	//----------------------------------------------------------
	// 기본 능력치를 설정한다. 
	//----------------------------------------------------------
	SI32 kind = pclCharlistInfo->clBI.uiKind;
	pclCharlistInfo->clIP.Init();

	//KHY - 0331 - 초기 셋팅이 바뀐다. - 체력 마나가 바뀌면 여기도 수정해야 한다.
	if(pclClient->IsCountrySwitch(Switch_HealthAddChange))
	{				
		pclCharlistInfo->clIP.SetHnd(5);
		pclCharlistInfo->clIP.SetWis(5);
		pclCharlistInfo->clIP.SetLuk(5);

		SI16 basicLife = 0;
		SI16 basicMana = 0;
		
		basicLife = (pclCharlistInfo->clIP.GetVit() * (8000 + (pclCharlistInfo->clIP.GetLevel()*5)))/1000 ;	
		basicMana = (pclCharlistInfo->clIP.GetMag() * (4000 + (pclCharlistInfo->clIP.GetLevel() *5)))/1000 ;	

		pclCharlistInfo->clIP.SetLife(basicLife);
		pclCharlistInfo->clIP.SetMana(basicMana);					
	}

	pclCharlistInfo->clBI.uiKind	= kind;

	cltPersonInfo	clPersonInfo;
	clPersonInfo.clBI	= pclCharlistInfo->clBI;
	clPersonInfo.clIP	= pclCharlistInfo->clIP;
	
	//----------------------------------------------------------
	// 캐릭터 이름을 재확인한다.
	//----------------------------------------------------------
	clPersonInfo.clBI.clPerson.szName[MAX_PLAYER_NAME - 1] ='\0';

	// 영문, 한글, 숫자만 가능하다. 
	//cyj 서버쪽 캐릭명 체크 부분 임시로 주석
	//if(IsCorrectID( clPersonInfo.clBI.clPerson.szName ) == FALSE)return ;


	//----------------------------------------------------------
	//임시로 새로 만들어진 캐릭터에게 아이템을 준다. 
	//----------------------------------------------------------
	SI32 itemunique[] = {
		-1
	};
	
	
	SI32 index = 0;
	while(itemunique[index*2] > 0)
	{
		cltItem clItem;
		SI16 brareswitch = 0;
		if(pclItemManager->MakeRandItemUnique( itemunique[index*2], &clItem, 0, 0, &brareswitch ) == true)
		{
			if(clItem.siUnique)
			{
				clItem.siItemNum	= itemunique[index*2 + 1];
				clPersonInfo.clCharItem.AddInv(pclItemManager, &clItem);
			}
		}
		index++;

	}


	// 클라이언트에서 요청된 새로운 캐릭터의 정보를 검색하여 문제가 없는지 확인한다. 

	// 문제가 없다면 새로운 캐릭터를 생성한다. 

	SI32 idnum	= pclCM->CR[id]->pclCI->clBI.siIDNum;
	SI16 sex	= pclCM->CR[id]->pclCI->clBI.uiSex;
	if(idnum)
	{
		// Basic정보 
		cltPBasicInfo	clbasicinfo;

		// IDNum을 넣어준다. 클라이언트에서 받은 IDNum은 무시해야 한다. (해킹의 위험.)
		clPersonInfo.clBI.siIDNum	= idnum;
		clPersonInfo.clBI.uiSex		= sex;		// 성별 입력. 
		
		clbasicinfo.Set(&clPersonInfo.clBI);

		//if ( siServiceArea == ConstServiceArea_China )
		//{
		//	// 캐릭터가 생성되야 할 위치를 설정한다. 
		//	clbasicinfo.clPos.SetMapIndex(MAPINDEX_PALACE);	// 경복궁. 
		//	clbasicinfo.clPos.SetX(27);
		//	clbasicinfo.clPos.SetY(87);
		//}
		//else
		//{
		//	if ( pclKindInfoSet->pclKI[kind]->siDefaultCountry == ConstServiceArea_China )
		//	{
		//		// 캐릭터가 생성되야 할 위치를 설정한다. 
		//		clbasicinfo.clPos.SetMapIndex(MAPINDEX_CHINABORDER);	// 국경선 
		//		clbasicinfo.clPos.SetX(17);
		//		clbasicinfo.clPos.SetY(19);
		//	}
		//	else
		//	{
//				// 캐릭터가 생성되야 할 위치를 설정한다. 
//				clbasicinfo.clPos.SetMapIndex(MAPINDEX_PALACE);	// 경복궁. 
//				clbasicinfo.clPos.SetX(27);
//				clbasicinfo.clPos.SetY(87);
		//	}
		//}


		// 캐릭터가 생성되야 할 위치를 설정한다. 
		clbasicinfo.clPos.SetMapIndex(MAPINDEX_PALACE);	// 경복궁. 

		SI32 RandXPos = rand()%7 + 24;
		SI32 RandYPos = rand()%23 + 68;

		clbasicinfo.clPos.SetX(RandXPos);
		clbasicinfo.clPos.SetY(RandYPos);


		// ImportantParameta정보 
		cltPIPInfo clipinfo;
		clipinfo.Set(&clPersonInfo.clIP);

		// 신분 정보. 
		cltSimpleRank	clrankinfo;
		clrankinfo.Set(&clPersonInfo.clCharRank);

		// 기술 정보.
		cltPSkillInfo clskillinfo;
		clskillinfo.Set(&clPersonInfo.clCharSkill);

		// 장비 정보. 
		cltPItemInfo clitem;
		clitem.Set(&clPersonInfo.clCharItem);


		// 전장정보. 
		cltBankAccount clBankInfo;

		// 주식 정보 
		cltPStockInfo clStockInfo;

		// 객주 정보. 
		cltPMarketInfo	clMarketInfo;

		// 건강 정보 
		cltHealthInfo clHealthInfo;
		
		// 퀘스트 정보.
		cltPQuestInfo clQuestInfo;
		
		// 말 정보. 
		cltPersonHorseInfo clHorseInfo;
		
		// 전과 기록. 
		cltGuiltyInfo clGuiltyInfo;
	
		//--------------------------
		// DailyQuest 정보. 
		//--------------------------
		cltPDailyQuestInfo clDailyQuestInfo;
		//--------------------------
		// DailyQuest2 정보. 
		//--------------------------
		cltPDailyQuest2Info clDailyQuest2Info;
		//--------------------------
		// DailyQuest3 정보. 
		//--------------------------
		cltPDailyQuest3Info clDailyQuest3Info;
		// 소환수 정보 
		cltSummonInfo	clSummonInfo;

//		cltPGuildStockInfo	clGuildStockInfo;


		// Person정보를 종합한다. 
		sDBPersonTotalInfo clinfo;

		clinfo.siGameMasterLevel = 0;
		clinfo.BasicInfo.Set(&clbasicinfo);
		clinfo.IPInfo.Set(&clipinfo);
		clinfo.RankInfo.Set(&clrankinfo);
		clinfo.SkillInfo.Set(&clskillinfo);
		clinfo.ItemInfo.Set(&clitem);
		clinfo.clBankInfo.Set(&clBankInfo);
		clinfo.clStockInfo.Set(&clStockInfo);
		clinfo.clMarketInfo.Set(&clMarketInfo);
		clinfo.clHealthInfo.Set(&clHealthInfo);
		clinfo.clQuestInfo.Set(&clQuestInfo);
		clinfo.clHorseInfo.Set(&clHorseInfo);
		clinfo.clGuiltyInfo.Set(&clGuiltyInfo);
		clinfo.clDailyQuestInfo.Set(&clDailyQuestInfo);
		clinfo.clDailyQuest2Info.Set(&clDailyQuest2Info);
		clinfo.clDailyQuest3Info.Set(&clDailyQuest3Info);
		clinfo.clSummonInfo.Set(&clSummonInfo);	

		// 새로운 Person을 만들도록 요구한다. 
		sDBRequest_PersonTotalInfoCreate clMsg(id, &clinfo);
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);

	}
	else
	{
		if (pclClient->GameMode != GAMEMODE_SERVER)
			MessageBox(NULL, TEXT("fd927434"), TEXT("f2-994"), MB_OK|MB_TOPMOST);
		return ;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DELUSERCHAR(cltMsg* pclMsg, SI32 id)
{

	cltGameMsgRequest_DelUserChar* pclDelUserChar = (cltGameMsgRequest_DelUserChar*)pclMsg->cData;

	SI32 slot		= pclDelUserChar->siCharSlot;
	TCHAR idennum[12];
	StringCchCopy( idennum, 12, pclDelUserChar->szIdentification );

	if(slot < 0 || slot >= MAX_TOTAL_CHAR_PER_USER)return ;

	//----------------------------------------------------
	// 캐릭터 정보를 삭제한다. 
	//----------------------------------------------------
	SI32 idnum	= pclCM->CR[id]->pclCI->clBI.siIDNum;
	if(idnum <=0)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = 0;
	if(pclchar->pclCharListInfo != NULL)	personid = pclchar->pclCharListInfo[slot].clBI.clPerson.siPersonID;
	//SI32 personid = pclchar->clCharListInfo[slot].clBI.clPerson.siPersonID;
	
	if(personid)
	{
		sDBRequest_PersonTotalInfoDelete clMsg(id, idnum, slot,	personid, idennum, ((ITZPerson *)pclCM->CR[id])->GetSession()->GetIP());
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);
	}

}
void cltServer::DoMsg_GAMEMSG_REQUEST_PREDELUSERCHAR(cltMsg* pclMsg, SI32 id)//케릭터 삭제유예기간
{
	cltGameMsgRequest_PreDelUserChar* pclPreDelUserChar = (cltGameMsgRequest_PreDelUserChar*)pclMsg->cData;

	SI32 slot		= pclPreDelUserChar->siCharSlot;
	TCHAR idennum[12];
	StringCchCopy( idennum, 12, pclPreDelUserChar->szIdentification );

	if(slot < 0 || slot >= MAX_CHAR_PER_USER)return ;
	cltServer* pclserver = (cltServer*)pclClient;

	SYSTEMTIME stTime;//현 시스템시간
	//SYSTEMTIME stDelTime;//결과적으로 케릭터를 지울시간
	//SI32 AddDate = 3;// 결과 시간이 되기위해 현시스템 시간에 더해줘야 하는 시간 or 날짜.
	GetLocalTime(&stTime);//현제 서버 시간 설정.
	//TimeAddDate(&stTime,AddDate,&stDelTime);

	SI32 idnum	= pclCM->CR[id]->pclCI->clBI.siIDNum;
	if(idnum <=0)return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = 0;
	if( pclchar->pclCharListInfo )	personid = pclchar->pclCharListInfo[slot].clBI.clPerson.siPersonID;
	SI16 deltype = pclPreDelUserChar->predeltype;

	if (personid) {
		sDBRequest_PersonTotalInfoPreDelete clMsg(id, idnum, slot,	personid, idennum, stTime, ((ITZPerson *)pclCM->CR[id])->GetSession()->GetIP(),deltype);
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);
	}

}

// 클라이언트가 준비되었다. 
void cltServer::DoMsg_GAMEMSG_REQUEST_READY(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pChar = (cltCharServer*)pclCM->CR[id];

	// 캐릭터가 준비되었음을 확인한다. 
	pChar->bReadySwitch	= true;
}

// [영훈] CRC 체크
void cltServer::DoMsg_GAMEMSG_REQUEST_FILECRCCHECK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_FileCRCCheck* pclCRC = (cltGameMsgRequest_FileCRCCheck*)pclMsg->cData;
	if ( pclCRC == NULL )							return;

	// 서버에서 체크할 목록이 없으면 체크하지 않아도 된다.
	if ( pclCRCFileCheckManager->m_siCount <= 0 )	return;

	bool bCheckResult = false;
	

	if ( pclCRC->siCount == pclCRCFileCheckManager->m_siCount )
	{
		for ( SI32 siIndex=0; siIndex<pclCRC->siCount; siIndex++ )
		{
			NCRCFileCheck* pCRCFile = &pclCRC->CheckFileList[siIndex];
			if ( pCRCFile == NULL ) continue;

			bCheckResult = pclCRCFileCheckManager->CheckFile( pCRCFile );

			if ( bCheckResult == false )
			{
				break;
			}
		}
	}

	if ( bCheckResult == false )
	{
		if ( pclCM->IsValidID( id ) == false )		return;

		SendServerResponseMsg( 0, SRVAL_FAIL_FILECRCCHECK, 0, 0, id );
			
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if ( pclchar == NULL )						return;

		pclchar->bCloseSocketSwitch = true;
		pclchar->dwCloseSocketTimer = 5;
	}
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHECKPROCESS(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_CheckProcess* pclInfo = (cltGameMsgRequest_CheckProcess*)pclMsg->cData;
	if ( NULL == pclInfo )
	{
		return;
	}

	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )
	{
		return;
	}

	pclCheckProcessManager->AddPersonInfo( id, pclInfo->m_siProcessCount, pclInfo->m_szMacAddress );

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONSLOTNUMCHANGE(cltMsg* pclMsg, SI32 id)
{
	if ( false == IsCountrySwitch(Switch_CharHouse) )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if ( NULL == pclChar )
	{
		return;
	}

	SI32 siFromIndex = pclMsg->siData32[0];
	if ( (MAX_CHAR_PER_USER > siFromIndex) || (MAX_TOTAL_CHAR_PER_USER <= siFromIndex) )
	{
		return;
	}

	SI32 siToIndex	= -1; // 인덱스가 0부터 시작이므로
	for ( SI32 siIndex=0; siIndex<MAX_CHAR_PER_USER; siIndex++ )
	{
		if ( 0 >= pclChar->pclCharListInfo[siIndex].clBI.clPerson.GetPersonID() )
		{
			siToIndex = siIndex;
			break;
		}
	}

	if ( (0 > siToIndex) || (MAX_CHAR_PER_USER <= siToIndex) )
	{
		return;
	}

	SI32 siGetPersonID = pclChar->pclCharListInfo[siFromIndex].clBI.clPerson.GetPersonID();
	if ( 0 >= siGetPersonID )
	{
		return;
	}

	sDBRequest_PersonSlotNumChange clMsg( id, siFromIndex, siToIndex, siGetPersonID );
	SendDBMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg );
	
}
