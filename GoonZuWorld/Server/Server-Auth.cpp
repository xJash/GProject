//---------------------------------
// 2003/7/31 김태곤
//---------------------------------

#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"

#include "..\Common\Map\Map.h"

#include "MsgType-System.h"

#include "../../Server/AuthServer/AuthMsg.h"
#include "..\..\DBManager\GameDBManager_World\DBMsg-Person.h"

#include "MsgRval-Define.h"

#include "../GMSystem/GMProtocol.h"
#include "../GMSystem/GMMsg.h"

void cltServer::DoMsg_AUTHMSG_RESPONSE_GAMEAUTH(sPacketHeader* pPacket)
{
//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	sResponse_GameAuth* pclMsg = (sResponse_GameAuth*)pPacket;

	// IDNum을 확보해서  Person List를 요청한다.
	SI32 siIDNum	= pclMsg->uiIDNum;
	SI32 id			= pclMsg->usCharID;
	SI32 sex		= pclMsg->siSex;
	SI32 tempid;

	if(pclCM->IsValidID(id) == false)		return;
				
	// 인증할 수 없다. (부적절한 아이디나 패스워드등.. )
	// 인증받지 못한 캐릭터라면 리턴한다. 
	if(siIDNum == 0)return;
	
	// 기존에 게임에 참여하고 있는 사용자 중에서 같은 IDNum을 사용하는 사람이 있는지 검사한다. 같은 IDNum을 
	//사용한다는 것은 중복 아이디 사용이므로 제한한다. 
	SI32 index = 0;
	while(tempid = pclCM->pclIDManager->GetCharOrder(index))
	{
		index++;
		if(pclCM->CR[tempid]->pclCI->clBI.siIDNum == siIDNum)
		{
			// 로그로 남긴다. 
			pclLog->FilePrint(TEXT("Config\\LoginLog.log"), TEXT("중복접속으로 접속 해제 [%s]"), pclCM->CR[tempid]->GetName());

			// 죽었는데 예를 안하고 버티는건 나쁜 사용자!1!!!!버그를 이용하려나.
			// 강제로 근처 마을로 살려서 이동 시키고 끊어야지.
			if(pclCM->IsAlive(tempid)	== false )	// 살아있나?
			{
				// 살아 있지 않아. 그런데 강제로 접속 했다. 
				// 일단 살린다.
				cltCharServer* pDieCharServer = pclCM->GetCharServer(tempid) ;
				if(pDieCharServer != NULL)
				{
					pclCM->CR[tempid]->Revive()	;
					//그리고 강종 시켜야지....이러면 버그 안나타날라나.
				}
			}


			// 다른 사용자 접속으로 접속이 끊김을 알려준다. 
			//cltGameMsgResponse_Notice clNotice(TEXT("알림"), TEXT("다른 곳에서의 접속으로 인해 현재의 접속을 종료합니다."));
			//cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
			//pclCM->CR[tempid]->SendNetMsg((sPacketHeader*)&clMsg);
			//cltMsg clMsg(GAMEMSG_RESPONSE_ANOTHERAUTH,0,NULL);
			//pclCM->CR[tempid]->SendNetMsg((sPacketHeader*)&clMsg);

			// 신규 사용자의 IP를 확보한다.
			//TCHAR * IP = pclCM->CR[id]->GetSession()->GetIP() ;

			TCHAR IP[64] = TEXT("") ;
			StringCchCopy(IP, 64,pclCM->CR[id]->GetSession()->GetIP());
			if ( !_tcscmp(IP , TEXT("222.107.176.36")) )
			{
				StringCchCopy(IP, 64 ,TEXT("영자강림!!!"));
			}

			// 시간을 확보한다.
			SYSTEMTIME stTime;
			GetLocalTime(&stTime);

			cltCharServer* pcloldchar = (cltCharServer*)(pclCM->CR[tempid]);

			cltGameMsgResponse_AnotherAuth clNotice(IP,stTime, FALSE);
			cltMsg clMsg(	GAMEMSG_RESPONSE_ANOTHERAUTH, sizeof(clNotice), (BYTE*)&clNotice);
			pcloldchar->SendNetMsg((sPacketHeader*)&clMsg);

			// 기존 사용자를 삭제한다.
			pcloldchar->bCloseSocketSwitch		= true;
			pcloldchar->dwCloseSocketTimer		= 5;

			//cyj 신규 사용자의 세션을 바로 끊지 않고 메세지를 보낸후 끊어지도록 수정
			cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[id]);
			cltGameMsgResponse_AnotherAuth clNotice2(IP,stTime, TRUE);
			cltMsg clMsg2(	GAMEMSG_RESPONSE_ANOTHERAUTH, sizeof(clNotice), (BYTE*)&clNotice2);
			pclnewchar->SendNetMsg((sPacketHeader*)&clMsg2);
			pclnewchar->bCloseSocketSwitch = true;
			pclnewchar->dwCloseSocketTimer = 5;
			// 신규 사용자 접속도 끊는다. 
			//pclCM->CR[id]->GetSession()->CloseSocket();

			return ;
		}
	}

	if (pclClient->siServiceArea == ConstServiceArea_Japan)
	{
		//cyj 게임팟 인증이 안된 유저이면
		if (pclCM->CR[id]->siAccountStatus == -1)
		{
			cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[id]);
			cltGameMsgResponse_NotGamePotAuth clNotAuth;
			cltMsg clMsg2(	GAMEMSG_RESPONSE_NOTGAMEPOTAUTH, sizeof(clNotAuth), (BYTE*)&clNotAuth);
			pclnewchar->SendNetMsg((sPacketHeader*)&clMsg2);
			pclnewchar->bCloseSocketSwitch = true;
			pclnewchar->dwCloseSocketTimer = 5;

			return;

		}

	}

	if (pclClient->siServiceArea == ConstServiceArea_Korea)
	{
		// 한게임 나이 체크
		if (pclMsg->siAccountStatus == -1000)
		{
			cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[id]);
			cltGameMsgResponse_CannotLogin_Age clNotAge;
			cltMsg clMsg2(	GAMEMSG_RESPONSE_CANNOTLOGIN_AGE, sizeof(cltGameMsgResponse_CannotLogin_Age), (BYTE*)&clNotAge);
			pclnewchar->SendNetMsg((sPacketHeader*)&clMsg2);
			pclnewchar->bCloseSocketSwitch = true;
			pclnewchar->dwCloseSocketTimer = 10;

			return;
		}
		// 한게임 인증 모듈 오류 반환
		else if(pclMsg->siAccountStatus == -1100)
		{
			cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[id]);
			cltGameMsgResponse_CannotLogin_Error clError;
			cltMsg clMsgError(	GAMEMSG_RESPONSE_CANNOTLOGIN_ERROR, sizeof(cltGameMsgResponse_CannotLogin_Error), (BYTE*)&clError);
			pclnewchar->SendNetMsg((sPacketHeader*)&clMsgError);
			pclnewchar->bCloseSocketSwitch = true;
			pclnewchar->dwCloseSocketTimer = 10;

			return;
		}
	}

	// 캐릭터의 IDNum을 기록한다. 
	pclCM->CR[id]->pclCI->clBI.siIDNum = siIDNum;
	pclCM->CR[id]->siIDNUM = siIDNum;

	// 성별 
	pclCM->CR[id]->pclCI->clBI.uiSex = sex;
				
	// 운영자 권한을 업데이트 한다. 
	pclCM->CR[id]->SetGameMasterLevel(pclMsg->siGameMasterLevel);
	pclCM->CR[id]->SetRareItemRate(0,0,0,0);
	pclCM->CR[id]->SetWennyOldMan(false,false);

	//[기형] 휴면 계정 여부를 저장한다.
	pclCM->CR[id]->pclCI->clDormancyInfo.SetDormancyState(pclMsg->siDormancyState);

	// GameDBManager_World에게 모든 Person정보를 알려줄 것을 요청한다. 
	sDBRequest_PersonListInfoGet clMsg(pclMsg->usCharID, pclMsg->uiIDNum);
	pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);

	if( pclCM->CR[id]->siAccountStatus == -2 )
	{
		// HanGame
		if( pclMsg->siAccountStatus == 4 )
		{
			siHangameCharNum++;
		}

		// Gamania
		else if( pclMsg->siAccountStatus == 2 ) 
		{
			siGamaniaCharNum++;
		}  
		
		// GamePot
		else if( pclMsg->siAccountStatus == 8 )
		{
			siGamePotCharNum++;
		}

		// NDE
		else if( pclMsg->siAccountStatus == 0 )
		{
			siNDECharNum++;
#ifdef _ENGLISH
			siGlobalNum++;
#endif
		}
		// NEXON
		else if( pclMsg->siAccountStatus == 10 )
		{
			siNEXONCharNum++;
		}
#ifdef _ENGLISH
		else if( pclMsg->siAccountStatus == 100 )
		{
			siNHNNum++;
		}
		// NEXON
		else if( pclMsg->siAccountStatus == 200 )
		{
			siGlobalNum++;
		}
#endif

		// Netmarble
		/*if( pclMsg->siAccountStatus == 6 ) 
		{
			//siNetmarbleCharNum++;
		}
		*/
	}

	pclCM->CR[id]->siAccountStatus = pclMsg->siAccountStatus;
	
	cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[id]);

	// 피로방지-
	if( ConstServiceArea_China == siServiceArea )
	{

		if( pclMsg->siPlayingTime >= 0 )
		{
			pclnewchar->bTiredSystem = true;

			if( pclMsg->siPlayingTime > 60 * 60 * 3 && pclMsg->siPlayingTime <= 60 * 60 * 5)
			{
				// 정상 수치의 반만 받는다.
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_LITTLE_TIRED;
			}
			else if( pclMsg->siPlayingTime > 60 * 60 * 5 )
			{
				// 아무것도 받지 못 한다.
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_MUCH_TIRED;
			}
			else
			{
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_NORMAL;
			}
			pclnewchar->dwPlayingTime = pclMsg->siPlayingTime;

			SendServerResponseMsg( 0, SRVAL_TIRED_SYSTEM_CHAR,  0, 0, pclnewchar->GetID() );

		}
		else if( -1 == pclMsg->siPlayingTime )
		{
			pclnewchar->bTiredSystem = false;
			pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_NORMAL;
			pclnewchar->dwPlayingTime = 0;
		}

		cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS , (SI32)pclnewchar->uiTiredState );
		pclnewchar->SendNetMsg((sPacketHeader*)&clMsg);

	}
	else if( ConstServiceArea_NHNChina == siServiceArea )
	{

		if( pclMsg->siPlayingTime >= 0 )
		{
			pclnewchar->bTiredSystem = true;

			//KHY - 0218 - 중국 NHN 피로도 모듈 적용 - 분으로 들어온다. 초로 다시 저장하자.
			pclMsg->siPlayingTime = pclMsg->siPlayingTime * 60;

			if( pclMsg->siPlayingTime > 60 * 60 * 3 && pclMsg->siPlayingTime <= 60 * 60 * 5)
			{
				// 정상 수치의 반만 받는다.
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_LITTLE_TIRED;
			}
			else if( pclMsg->siPlayingTime > 60 * 60 * 5 )
			{
				// 아무것도 받지 못 한다.
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_MUCH_TIRED;
			}
			else
			{
				pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_NORMAL;
			}
			pclnewchar->dwPlayingTime = pclMsg->siPlayingTime;

			// 로그로 남긴다. 
			pclLog->FilePrint(TEXT("Config\\Tired_Server_RESPONSE_GAMEAUTH.log"), TEXT("GetName - %s , siPlayingTime - %d"), pclCM->CR[id]->GetName() ,pclMsg->siPlayingTime );

			SendServerResponseMsg( 0, SRVAL_TIRED_SYSTEM_CHAR,  0, 0, pclnewchar->GetID() );

		}
		else if( -1 == pclMsg->siPlayingTime )
		{
			pclnewchar->bTiredSystem = false;
			pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_NORMAL;
			pclnewchar->dwPlayingTime = 0;
			pclnewchar->siTiredNotice = 0;
		}

		//cltMsg clMsg( GAMEMSG_RESPONSE_TIRED_STATUS , (SI32)pclnewchar->uiTiredState );
		//pclnewchar->SendNetMsg((sPacketHeader*)&clMsg);

	}
	else
	{
		pclnewchar->bTiredSystem = false;
		pclnewchar->uiTiredState = cltCharCommon::TIRED_STATUS_NORMAL;
		pclnewchar->dwPlayingTime = 0;
	}

	// 한게임용 IDNO - by LEEKH 2007.11.11
	pclnewchar->uiIDNo = pclMsg->uiIDNo;

//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_AUTHMSG_RESPONSE_HANAUTH_GAMERUNAUTH(sPacketHeader* pPacket)
{
//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	sResponse_GameRunAuth* pclGameDisconnectMsg = (sResponse_GameRunAuth*)pPacket;

/*	if (pclClient->siServiceArea == ConstServiceArea_Korea)
	{
		// PCK - 2007.09.19 : 한게임 나이체크 (게임도중에도 체크를 함.)
		if (pclGameDisconnectMsg->siResult == 0)
		{
			cltCharServer* pclnewchar = (cltCharServer*)(pclCM->CR[pclGameDisconnectMsg->usCharID]);
			cltGameMsgResponse_GameDisconnect_Age clNotAge;
			cltMsg clMsg2(	GAMEMSG_RESPONSE_GAMEDISCONNECT_AGE, sizeof(cltGameMsgResponse_GameDisconnect_Age), (BYTE*)&clNotAge);
			pclnewchar->SendNetMsg((sPacketHeader*)&clMsg2);
			pclnewchar->bCloseSocketSwitch = true;
			pclnewchar->dwCloseSocketTimer = 10;

			return;
		}
	}*/

//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_AUTHMSG_RESPONSE_GMTOOLAUTH(sPacketHeader* pPacket)
{
//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	sResponse_GMToolAuth* pclInfo = (sResponse_GMToolAuth*)pPacket;
	if(pclInfo->usCharID < 0)		return;

	cGMClient* pclchar = pclGMProtocol->GetGMClient( pclInfo->usCharID );
	if(pclchar == NULL)				return;

	ITZSession* pSession = pclchar->GetSession();
	if(pSession == NULL)			return;

	sGMResponse_Login sendMsg( 0 );		// 기본 실패

	if ( pclInfo->siMasterLevel >= BASIC_GAMEMASTER_LEVEL )
	{
		sendMsg.m_iResult = 1;
		
		pclchar->SetAccount( pclInfo->userid, pclInfo->siMasterLevel );
	}
	
	// 메시지 보냄
	pclGMProtocol->SendPacket( pSession, (sPacketHeader*)&sendMsg );

//----------------------------------------------------------------
// 서버만 컴파일 됨
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------

}
