//---------------------------------
// 2003/9/27 김태곤
//---------------------------------

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "../../Common/Map/Map.h"
#include "../../Common/Order/Order.h"
#include "../../Common/PrivateTradeOrderMgr/PrivateTradeOrderMgr.h"
#include "Char\CharManager\CharManager.h"
#include "GachaManager/GachaManager.h"

#include "../../../Server/AuthServer/AuthMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"

#include "../../CommonLogic/Msg/MsgType-PrivateTrade.h"
#include "../../CommonLogic/MsgType-System.h"


#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-CityHall.h"
#include "../../../DBManager/GameDBManager_World/DBGameLogMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Friend.h"

#include "MsgRval-Define.h"
#include "MsgType-Item.h"
#include "../Minister/MinisterMgr.h"
#include "../Minister/Minister-Goonzu.h"
#include "../Minister/Minister-Byungzo.h"

#include "../Lib/HashTable/HashTable_StringInt.h"

#include "../../NLib/NUtil.h"

#include "../../../AdminSystem/MasterServer/MasterMsg.h"
#include "../../CommonLogic/CityHall/CityHall.h"

extern cltCommonLogic* pclClient;

// 사용자 간단 정보 응답. 
void cltServer::DoMsg_DBMSG_RESPONSE_USERCHARINFO(sPacketHeader* pPacket)
{
	sDBResponse_UserCharInfo* pclMsg = (sDBResponse_UserCharInfo* )pPacket;

	//============================================
	// GMTOOL용 응답이다.
	if(pclMsg->siRequestType == 1)
	{
		/*
		sResponse_GMC_UserCharInfo	clinfo;
		clinfo.m_siCharID = pclMsg->usCharID;

		StringCchCopy(clinfo.m_szAccountID, sizeof(clinfo.m_szAccountID), pclMsg->szAccountID);
		StringCchCopy(clinfo.m_szPassword, sizeof(clinfo.m_szPassword), pclMsg->szPassword);
		clinfo.m_bConnectSwitch		= pclMsg->bConnectSwitch;

		clinfo.m_clTotalMoney		= pclMsg->clTotalMoney.itMoney;
		clinfo.m_clBankMoney		= pclMsg->clBankMoney.itMoney;

		clinfo.m_siWorldTradeMoney	= pclMsg->siWorldTradeMoney;

		clinfo.m_siVillageUnique	= pclMsg->siVillageUnique;
		clinfo.m_uiWarnMode			= pclMsg->uiWarnMode;

		clinfo.m_uiBlockMode		= pclMsg->uiBlockMode;
		StringCchCopy(clinfo.m_szBlockReason, sizeof(clinfo.m_szBlockReason), pclMsg->szBlockReason);
		StringCchCopy(clinfo.m_szBlockStartDate, sizeof(clinfo.m_szBlockStartDate), pclMsg->szBlockStartDate);
		StringCchCopy(clinfo.m_szBlockEndDate, sizeof(clinfo.m_szBlockEndDate), pclMsg->szBlockEndDate);

		clinfo.m_siPersonID			= pclMsg->siPersonID;
		clinfo.m_siLevel			= pclMsg->siLevel;
		clinfo.m_siMoney			= pclMsg->siMoney;

		clinfo.m_siMapIndex			= pclMsg->siMapIndex;
		clinfo.m_siX				= pclMsg->siX;
		clinfo.m_siY				= pclMsg->siY;
		clinfo.m_siGoonzuFriends	= pclMsg->siGoonzuFriends;

		StringCchCopy(clinfo.m_szRecommender, sizeof(clinfo.m_szRecommender), pclMsg->szRecommender);
		StringCchCopy(clinfo.m_szFatherName, sizeof(clinfo.m_szFatherName), pclMsg->szFatherName);
		clinfo.m_siStudentLevel		= pclMsg->siStudentLevel;

		StringCchCopy(clinfo.m_szMakeDate, sizeof(clinfo.m_szMakeDate), pclMsg->szMakeDate);

		for(SI32 i=0; i<110; i++)
		{
			clinfo.m_siItemUnique[i]	= pclMsg->clItem[i].siUnique;
			clinfo.m_siItemCount[i]		= pclMsg->clItem[i].siItemNum;
		}

		if( pclAgentProcess != NULL &&
			pclAgentProcess->GetAgentSession() != NULL &&
			pclAgentProcess->GetAgentSession()->GetSendBuffer() != NULL)
		{
			pclAgentProcess->GetAgentSession()->GetSendBuffer()->Write((BYTE*)&clinfo);
		}
		*/
		return;
	}
	//============================================

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id)	== false)return ;
	if(pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)return ;

	if(pclMsg->siResult == 0)return ;
	
	SI32 mapindex = pclMsg->siMapIndex;
	SI32 x			= pclMsg->siX;
	SI32 y			= pclMsg->siY;

	SI32 siCharUnique = 0;

	bool bconnectswitch = false;
	if(pclMsg->siPersonID)
	{
		// 게임에 접속중이면, 
		SI32 charid = pclCM->GetIDFromPersonID( pclMsg->siPersonID );
		if(charid)
		{
			mapindex	= pclCM->CR[charid]->GetMapIndex();
			x			= pclCM->CR[charid]->GetX();
			y			= pclCM->CR[charid]->GetY();

			bconnectswitch = true;

			siCharUnique = pclCM->CR[charid]->GetCharUnique();
		}
	}

#if defined(_DEBUG)
	// 파티획득막음
//SI32 ReceivedPacketsize = sizeof( sDBResponse_UserCharInfo );

//	SI32 SendPacketsize = sizeof( cltGameMsgResponse_UserCharInfo );
#endif


	cltGameMsgResponse_UserCharInfo clinfo(pclMsg->szAccountID, pclMsg->szPassword, &pclMsg->clTotalMoney,
											&pclMsg->clBankMoney, pclMsg->siWorldTradeMoney, bconnectswitch, pclMsg->siPersonID, siCharUnique, pclMsg->siLevel, pclMsg->siMoney, mapindex, x, y, 
											pclMsg->siGoonzuFriends, pclMsg->szOtherPersonName1, pclMsg->szOtherPersonName2 ,//pclMsg->clItem,
											&(pclMsg->clSummonInfo), pclMsg->siVillageUnique,
											pclMsg->szRecommender,pclMsg->szFatherName,pclMsg->siStudentLevel,pclMsg->szMakeDate,
											pclMsg->m_clBlockLog );
	cltMsg clMsg(GAMEMSG_RESPONSE_USERCHARINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);



	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// TEMP LEEKH -------------------------------------------------------------------
		// [로그추가 : 황진성 2007. 10. 18] // 사용자 캐릭터 정보 요청. (확인필요 : 정보가 부족할듯.)
		// param1	 == 접속여부, 
		// param2	 == 레벨,
		// param3	 == 지도번호, 
		// param4	 == 군주친구,
		// pszParam1 == 추천인, 스승, 
		// pszParam2 == 캐릭터 생성 시기.
		TCHAR str[2][50];
		ZeroMemory(str, sizeof(str));
		StringCchPrintf(str[0], sizeof(str[0]), TEXT("Recommender: %s, FatherName: %s"),	
														pclMsg->szRecommender, 
														pclMsg->szFatherName 	);

		StringCchPrintf(str[1], sizeof(str[1]), TEXT("MakeDate: %s"),	pclMsg->szMakeDate	);

		
		cltServer * pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SYSTEM, LOGCOMMAND_INDEX_SYSTEM_USER_INFO_GET, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, pclMsg->siMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->bConnectSwitch, pclMsg->siLevel, pclMsg->siMapIndex, pclMsg->siGoonzuFriends, 0, 
										str[0], str[1]);
		// TEMP LEEKH -------------------------------------------------------------------
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_USERCHARITEMINFO(sPacketHeader* pPacket)
{
	sDBResponse_UserCharItemInfo* pclMsg = (sDBResponse_UserCharItemInfo*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer(pclMsg->m_usCharID);
	if ( NULL == pclChar )
	{
		return;
	}

	if ( pclChar->pclCI->GetPersonID() != pclMsg->m_siPersonID )
	{
		return;
	}

	if ( pclChar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return;
	}

	cltGameMsgResponse_UserCharItemInfo clInfo( pclMsg->m_clItem );
	cltMsg clMsg(GAMEMSG_RESPONSE_USERCHARITEMINFO, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_USERCHARITEMINFO2(sPacketHeader* pPacket)
{
	sDBResponse_UserCharItemInfo2* pclMsg = (sDBResponse_UserCharItemInfo2*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	cltCharServer* pclChar = pclCM->GetCharServer(pclMsg->m_usCharID);
	if ( NULL == pclChar )
	{
		return;
	}

	if ( pclChar->pclCI->GetPersonID() != pclMsg->m_siPersonID )
	{
		return;
	}

	if ( pclChar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return;
	}

	cltGameMsgResponse_UserCharItemInfo2 clInfo( pclMsg->m_clSpaceBox, pclMsg->m_clTreasureBox );
	cltMsg clMsg(GAMEMSG_RESPONSE_USERCHARITEMINFO2, sizeof(clInfo), (BYTE*)&clInfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_ACCOUNTINFO(sPacketHeader* pPacket)
{
	sDBResponse_AccountInfo* pclMsg = (sDBResponse_AccountInfo* )pPacket;

	//============================================
	// GMTOOL용 응답이다.
	if(pclMsg->siRequestType == 1)
	{
		sResponse_GMC_AccountCharInfo	clinfo;
		clinfo.m_siCharID = pclMsg->usCharID;
		MStrCpy(clinfo.m_szAccountID, pclMsg->szAccountID, sizeof(clinfo.m_szAccountID));
		MStrCpy(clinfo.m_szServerName, szServerName, sizeof(clinfo.m_szServerName));

		MStrCpy(clinfo.m_szCharName1, pclMsg->szPersonName1, sizeof(clinfo.m_szCharName1));
		MStrCpy(clinfo.m_szCharName2, pclMsg->szPersonName2, sizeof(clinfo.m_szCharName2));
		MStrCpy(clinfo.m_szCharName3, pclMsg->szPersonName3, sizeof(clinfo.m_szCharName3));

		if( pclAgentProcess != NULL &&
			pclAgentProcess->GetAgentSession() != NULL &&
			pclAgentProcess->GetAgentSession()->GetSendBuffer() != NULL)
		{
			pclAgentProcess->GetAgentSession()->GetSendBuffer()->Write((BYTE*)&clinfo);
		}
		return;
	}
	//============================================

	SI32 id = pclMsg->usCharID;

	if(pclCM->IsValidID(id)	== false)return ;
	// PCK : account명령어는 GM레벨 90이상부터 동작하도록 수정.
	if(pclCM->CR[id]->GetGameMasterLevel() < BASIC_PLAYERMASTER_LEVEL)return ;

	if(pclMsg->siResult == 0)return ;

	cltGameMsgResponse_AccountInfo clinfo( pclMsg->szAccountID, pclMsg->szPersonName1, pclMsg->szPersonName2, pclMsg->szPersonName3 );
	cltMsg clMsg(GAMEMSG_RESPONSE_ACCOUNTINFO, sizeof(clinfo), (BYTE*)&clinfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_ACCOUNTINFOFORHANXNOTI(sPacketHeader* pPacket)
{
#ifdef USE_HANXNOTI

	sDBResponse_AccountInfoForHanXNoti* pclMsg = (sDBResponse_AccountInfoForHanXNoti* )pPacket;
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [m_siArrayIndex:%d]"), TEXT("sDBResponse_AccountInfoForHanXNoti"), pclMsg->m_siArrayIndex );

	if(pclMsg->m_siArrayIndex < 0 || pclMsg->m_siArrayIndex >= HANXNOTI_MAX_WAITING)		return;

	GameCharacter*			pkChar = NULL;
	GameCharacterListAns*	pkSendMsg = NULL;

	if( m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_siIdx == pclMsg->m_nIdx )
	{
		m_pkHanXNoti_AnsMessages[pclMsg->m_siArrayIndex] = new GameCharacterListAns;
		pkSendMsg = (GameCharacterListAns*)m_pkHanXNoti_AnsMessages[pclMsg->m_siArrayIndex];
	}

	if(pkSendMsg)
	{
		if(pclMsg->siResult == 1)
		{
			pkSendMsg->nIdx = pclMsg->m_nIdx;

			pkChar = new GameCharacter;
			pkChar->nIdx			= 0;
			pkChar->memberid		= pclMsg->szAccountID;
			pkChar->serverid		= pclMsg->szServerID;
			pkChar->characterId		= pclMsg->szPersonName1;
			pkChar->characterType	= "";
			pkChar->level			= 0;
			pkChar->gameMoney		= 0;
			pkSendMsg->listcharacters.push_back(pkChar);

			pkChar = new GameCharacter;
			pkChar->memberid		= pclMsg->szAccountID;
			pkChar->serverid		= pclMsg->szServerID;
			pkChar->characterId		= pclMsg->szPersonName2;
			pkChar->characterType	= "";
			pkChar->level			= 0;
			pkChar->gameMoney		= 0;
			pkSendMsg->listcharacters.push_back(pkChar);

			pkChar = new GameCharacter;
			pkChar->memberid		= pclMsg->szAccountID;
			pkChar->serverid		= pclMsg->szServerID;
			pkChar->characterId		= pclMsg->szPersonName3;
			pkChar->characterType	= "";
			pkChar->level			= 0;
			pkChar->gameMoney		= 0;
			pkSendMsg->listcharacters.push_back(pkChar);

			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [memberid:%s] [serverid:%s] [characterId1:%s] [characterId2:%s] [characterId3:%s]"), TEXT("GameCharacterListAns"), pclMsg->szAccountID, pclMsg->szServerID, pclMsg->szPersonName1, pclMsg->szPersonName2, pclMsg->szPersonName3 );
		}
	}

	// Idx 가 일치할 경우에만 
	if( m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_siIdx == pclMsg->m_nIdx )
	{
		// 이벤트 SET !!
		::SetEvent(m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_hWaitingHandle);
	}

#endif // USE_HANXNOTI
}

void cltServer::DoMsg_DBMSG_RESPONSE_CHARINFOFORHANXNOTI(sPacketHeader* pPacket)
{
#ifdef USE_HANXNOTI

	sDBResponse_CharInfoForHanXNoti* pclMsg = (sDBResponse_CharInfoForHanXNoti* )pPacket;
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [m_siArrayIndex:%d]"), TEXT("sDBResponse_CharInfoForHanXNoti"), pclMsg->m_siArrayIndex );

	// 이상한 테이터를 받았다.
	if(pclMsg->m_siArrayIndex < 0 || pclMsg->m_siArrayIndex >= HANXNOTI_MAX_WAITING)		return;

	GameCharacter*			pkChar = NULL;
	GameCharacterListAns*	pkSendMsg = NULL;

	// Idx 가 일치할 경우에만 
	if( m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_siIdx == pclMsg->m_nIdx )
	{
		m_pkHanXNoti_AnsMessages[pclMsg->m_siArrayIndex] = new GameCharacterListAns;
		pkSendMsg = (GameCharacterListAns*)m_pkHanXNoti_AnsMessages[pclMsg->m_siArrayIndex];
	}

	if(pkSendMsg != NULL)
	{
		pkSendMsg->nIdx = pclMsg->m_nIdx;
		if(pclMsg->siResult == 1)
		{
			pkChar = new GameCharacter;
			pkChar->nIdx			= 0;
			pkChar->memberid		= pclMsg->m_szAccountID;
			pkChar->serverid		= pclMsg->m_szServerID;
			pkChar->characterId		= pclMsg->m_szCharName;
			pkChar->characterType	= "";
			pkChar->level			= 0;
			pkChar->gameMoney		= 0;
			pkSendMsg->listcharacters.push_back(pkChar);

			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [memberid:%s] [serverid:%s] [characterId:%s]"), TEXT("GameCharacterListAns"), pclMsg->m_szAccountID, pclMsg->m_szServerID, pclMsg->m_szCharName );
		}
	}

	// Idx 가 일치할 경우에만 
	if( m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_siIdx == pclMsg->m_nIdx )
	{
		// 이벤트 SET !!
		::SetEvent(m_kHanXNoti_Waitings[pclMsg->m_siArrayIndex].m_hWaitingHandle);



	}

#endif // USE_HANXNOTI
}

void cltServer::DoMsg_DBMSG_RESPONSE_PRIVATETRADE(sPacketHeader* pPacket)
{
	sDBResponse_PrivateTrade *pclMsg = (sDBResponse_PrivateTrade *)pPacket;

	cltRentContract clPerson1RecvHouseUnitContract;
	clPerson1RecvHouseUnitContract.Init();

	cltRentContract clPerson2RecvHouseUnitContract;
	clPerson2RecvHouseUnitContract.Init();


	if ( pclMsg->siResult != 1 )
	{
		// -2 인 경우에는 시전 개수 초과해서 가질려고 할때
		if ( pclMsg->siResult == -2 )
		{
			if(pclCM->IsValidID(pclMsg->usCharID1) )
			{
				if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->GetPersonID() == pclMsg->siPersonID1 )
				{
					cltHorse* pclHorse1 = pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.GetCurrentShowHorse();
					cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult, 0, 0, 0, 0, 0, 0, &clPerson1RecvHouseUnitContract, 0, 0, -1, pclHorse1);
					cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );
					
					pclCM->CR[pclMsg->usCharID1]->SendNetMsg((sPacketHeader*)&clMsg);

					SendServerResponseMsg(0, SRVAL_PRIVATETRADE_HOUSEUNIT_EXCEED_NUMBER_PER_PERSON, 0, 0, pclMsg->usCharID1 );
				}
			}
			if(pclCM->IsValidID(pclMsg->usCharID2)	)
			{
				if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->GetPersonID() == pclMsg->siPersonID2 )
				{
					cltHorse* pclHorse2 = pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.GetCurrentShowHorse();
					cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult, 0, 0, 0, 0, 0, 0, &clPerson2RecvHouseUnitContract, 0, 0, -1, pclHorse2 );
					cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );
					
					pclCM->CR[pclMsg->usCharID2]->SendNetMsg((sPacketHeader*)&clMsg);

					SendServerResponseMsg(0, SRVAL_PRIVATETRADE_HOUSEUNIT_EXCEED_NUMBER_PER_PERSON, 0, 0, pclMsg->usCharID2 );
				}
			}
			
		}
		else
		{
			if(pclCM->IsValidID(pclMsg->usCharID1) )
			{
				if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->GetPersonID() == pclMsg->siPersonID1 )
				{
					cltHorse* pclHorse1 = pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.GetCurrentShowHorse();
					cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult, 0, 0, 0, 0, 0, 0, &clPerson1RecvHouseUnitContract, 0, 0, -1, pclHorse1 );
					cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );
					
					pclCM->CR[pclMsg->usCharID1]->SendNetMsg((sPacketHeader*)&clMsg);

				}
			}
			
			if(pclCM->IsValidID(pclMsg->usCharID2)	)
			{
				if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->GetPersonID() == pclMsg->siPersonID2 )
				{
					cltHorse* pclHorse2 = pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.GetCurrentShowHorse();
					cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult, 0, 0, 0, 0, 0, 0, &clPerson2RecvHouseUnitContract, 0, 0, -1, pclHorse2 );
					cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );
					
					pclCM->CR[pclMsg->usCharID2]->SendNetMsg((sPacketHeader*)&clMsg);
				}
			}
		}

		pclPrivateTradeOrderMgr->Cancel( pclMsg->siPersonID1 );
		pclPrivateTradeOrderMgr->Cancel( pclMsg->siPersonID2 );
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	// 시전 거래( 유저가 존재 하지 않더라도 거래는 되어야 함으로. )	
	if ( pclMsg->siSendHouseVillageUnique1 > 0 && pclMsg->siSendHouseVillageUnique1 <= MAX_VILLAGE_NUMBER )
	{
		cltHouse* pclhouse = (cltHouse*)pclHouseManager->pclStruct[ pclMsg->siSendHouseVillageUnique1 ];

		if( pclhouse != NULL )
		{
			if( pclMsg->siSendHouseUnitSlot1 >= 0 && pclMsg->siSendHouseUnitSlot1 < MAX_HOUSEUNIT_NUMBER )
			{
				pclhouse->clUnit[ pclMsg->siSendHouseUnitSlot1 ].clPerson.Set( pclMsg->siPersonID2, pclMsg->Person2Name );			
				clPerson2RecvHouseUnitContract.Set( &pclhouse->clUnit[ pclMsg->siSendHouseUnitSlot1 ].clContract );
			}
		}
	}
	
	if ( pclMsg->siSendHouseVillageUnique2 > 0 )
	{	
		cltStrInfo *pclStrInfo = pclHouseManager->GetStrInfo( pclMsg->siSendHouseVillageUnique2 );

		cltHouse* pclhouse = (cltHouse*)pclHouseManager->pclStruct[ pclMsg->siSendHouseVillageUnique2 ];

		if( pclhouse != NULL )
		{
			if( pclMsg->siSendHouseUnitSlot2 >= 0 && pclMsg->siSendHouseUnitSlot2 < MAX_HOUSEUNIT_NUMBER )
			{
				pclhouse->clUnit[ pclMsg->siSendHouseUnitSlot2 ].clPerson.Set( pclMsg->siPersonID1, pclMsg->Person1Name );
				clPerson1RecvHouseUnitContract.Set( &pclhouse->clUnit[ pclMsg->siSendHouseUnitSlot2 ].clContract );
			}
			//pclhouse->clUnit[ pclMsg->siSendHouseUnitSlot2 ].clContract;
		}
	}	
	//////////////////////////////////////////////////////////////////////////
	
	
	if(pclCM->IsValidID(pclMsg->usCharID1) )
	{
		if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->GetPersonID() == pclMsg->siPersonID1 )
		{
			// 성공이든 실패든 결과값을 보내서 거래창을 닫게 한다.
			// 물론, 거래 할당된 것도 해제 해야 된다.

			//KHY - 1001 - 기승동물 5마리 보유 수정. - 자신의 말이 안보이는 부분.
			SI16 siHorseIndex1 = pclMsg->siHorse1;
			cltHorse clHorse1;

			clHorse1.Set(&pclMsg->clRecvHorse1 );
			
			if(pclMsg->siHorse1 == -1)
			{
				siHorseIndex1 = pclCM->CR[pclMsg->usCharID1]->pclCI->clHorseInfo.GetCurrentShowHorseIndex();
				clHorse1.Set(pclCM->CR[pclMsg->usCharID1]->pclCI->clHorseInfo.GetCurrentShowHorse());
			}
			cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult,
				pclMsg->siRecvStockVillageUnique1, pclMsg->siRecvStockNum1, 
				pclMsg->siSendStockVillageUnique1, pclMsg->siSendStockNum1,
				pclMsg->siRecvHouseVillageUnique1, pclMsg->siRecvHouseUnitSlot1,
				&clPerson1RecvHouseUnitContract,
				pclMsg->siSendHouseVillageUnique1, pclMsg->siSendHouseUnitSlot1,
				siHorseIndex1, &clHorse1 );
			cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );

			pclCM->CR[pclMsg->usCharID1]->SendNetMsg((sPacketHeader*)&clMsg);

//			pclMsg->siHorse1, &pclMsg->clRecvHorse1 );

			//////////////////////////////////////////////////////////////////////////
			// 주식 거래
			if ( pclMsg->siRecvStockNum1 > 0 && pclMsg->siRecvStockVillageUnique1 > 0 && pclMsg->siRecvStockVillageUnique1 < MAX_VILLAGE_NUMBER )
			{
				SI16 EmptyIndex = -1;
				for ( SI16 i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
				{
					if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == pclMsg->siRecvStockVillageUnique1 )
					{
						pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = pclMsg->siRecvStockNum1;
						break;
					}
					else if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == 0 && EmptyIndex == -1 )
					{
						EmptyIndex = i;
					}
				}

				if ( i == MAX_STOCK_KIND_IN_ACOUNT && EmptyIndex > -1 && EmptyIndex < MAX_STOCK_KIND_IN_ACOUNT )
				{
					pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ EmptyIndex ].siAmount = pclMsg->siRecvStockNum1;
					pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ EmptyIndex ].siVillageUnique = pclMsg->siRecvStockVillageUnique1;
				}
			}			
			
			if ( pclMsg->siSendStockVillageUnique1 > 0 && pclMsg->siSendStockVillageUnique1 < MAX_VILLAGE_NUMBER )
			{
				for ( SI16 i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
				{
					if ( pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == pclMsg->siSendStockVillageUnique1 )
					{
						if ( pclMsg->siSendStockNum1 > 0 )
						{
							pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = pclMsg->siSendStockNum1;
						}
						else
						{
							pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = 0;
							pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique = 0;
						}
						break;		
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////


			//////////////////////////////////////////////////////////////////////////
			// 시전 거래
			if ( pclMsg->siSendHouseVillageUnique1 > 0 && pclMsg->siSendHouseVillageUnique1 < MAX_VILLAGE_NUMBER )
			{
				pclCM->CR[pclMsg->usCharID1]->pclCI->clRealEstate.Delete( REALESTATE_TYPE_HOUSE, pclMsg->siSendHouseVillageUnique1, pclMsg->siSendHouseUnitSlot1 );
			}

			if ( pclMsg->siRecvHouseVillageUnique1 > 0 && pclMsg->siRecvHouseVillageUnique1 < MAX_VILLAGE_NUMBER )
			{
				cltHouse* pclhouse = (cltHouse*)pclHouseManager->pclStruct[ pclMsg->siRecvHouseVillageUnique1 ];

				if( pclhouse != NULL )
				{	
					if( pclMsg->siRecvHouseUnitSlot1 >= 0 && pclMsg->siRecvHouseUnitSlot1 < MAX_HOUSEUNIT_NUMBER )
						pclCM->CR[pclMsg->usCharID1]->pclCI->clRealEstate.Add( REALESTATE_TYPE_HOUSE, pclMsg->siRecvHouseVillageUnique1, pclMsg->siRecvHouseUnitSlot1, &pclhouse->clUnit[ pclMsg->siRecvHouseUnitSlot1 ].clContract );
				}
			}
			//////////////////////////////////////////////////////////////////////////
			

			//////////////////////////////////////////////////////////////////////////
			// 말 거래 ( 말 강제로 내린 후에 거래 )
			if ((pclMsg->siHorse1 != -1) && (pclMsg->siRecvHorse1 != -1)) //서로 말을 주고 받았다.
			{
				pclCM->CR[pclMsg->usCharID1]->UnrideHorse();
				//pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.clHorse.Set( &pclMsg->clRecvHorse1 );
				pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.Init(pclMsg->siHorse1);
				pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siRecvHorse1, &pclMsg->clRecvHorse1 );
				pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.SetCurrentShowHorseIndex(pclMsg->siRecvHorse1);
				
				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 교환, 또는 보냄 )
				//---------------------------------------
				((cltCharServer*)pclCM->CR[pclMsg->usCharID1])->SendNeighbourMyHorseStatus(pclCM->CR[pclMsg->usCharID1]->pclCI->clHorseInfo.siCurrentShowHorse);

			}
			else if ( pclMsg->siHorse1 != -1 ) 
			{
				pclCM->CR[pclMsg->usCharID1]->UnrideHorse();
				pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siHorse1, &pclMsg->clRecvHorse1 );

				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 교환, 또는 보냄 )
				//---------------------------------------
				((cltCharServer*)pclCM->CR[pclMsg->usCharID1])->SendNeighbourMyHorseStatus(pclCM->CR[pclMsg->usCharID1]->pclCI->clHorseInfo.siCurrentShowHorse);

			}
			else if ( pclMsg->siRecvHorse1 != -1 )
			{
				pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siRecvHorse1, &pclMsg->clRecvHorse1 );

				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 생성 )
				//---------------------------------------
				{
					((cltCharServer*)pclCM->CR[pclMsg->usCharID1])->SendNeighbourMyHorseStatus( pclCM->CR[pclMsg->usCharID1]->pclCI->clHorseInfo.siCurrentShowHorse);
				}
			}
			//////////////////////////////////////////////////////////////////////////

			//개인거래 퀘스트가 진행중인지 확인한다. 
			((cltCharServer*)pclCM->CR[pclMsg->usCharID1])->DoQuestCheckAndAction(QUEST_CLEAR_COND_PRIVATETRADE);
		}
	}
	
	if(pclCM->IsValidID(pclMsg->usCharID2)	)
	{
		if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->GetPersonID() == pclMsg->siPersonID2 )
		{
			// 성공이든 실패든 결과값을 보내서 거래창을 닫게 한다.
			// 물론, 거래 할당된 것도 해제 해야 된다.

			//KHY - 1001 - 기승동물 5마리 보유 수정. - 자신의 말이 안보이는 부분.
			SI16 siHorseIndex2 = pclMsg->siHorse2;
			cltHorse clHorse2;

			clHorse2.Set(&pclMsg->clRecvHorse2 );
			if(pclMsg->siHorse2 == -1)
			{
				siHorseIndex2 = pclCM->CR[pclMsg->usCharID2]->pclCI->clHorseInfo.GetCurrentShowHorseIndex();
				clHorse2.Set(pclCM->CR[pclMsg->usCharID2]->pclCI->clHorseInfo.GetCurrentShowHorse());
			}
			cltGameMsgResponse_PrivateTrade_End clPrivateTradeEnd( pclMsg->siResult,
				pclMsg->siRecvStockVillageUnique2, pclMsg->siRecvStockNum2,
				pclMsg->siSendStockVillageUnique2, pclMsg->siSendStockNum2,
				pclMsg->siRecvHouseVillageUnique2, pclMsg->siRecvHouseUnitSlot2,
				&clPerson2RecvHouseUnitContract,
				pclMsg->siSendHouseVillageUnique2, pclMsg->siSendHouseUnitSlot2,
				siHorseIndex2, &clHorse2
				);
			cltMsg clMsg( GAMEMSG_RESPONSE_PRIVATETRADE_END, sizeof( clPrivateTradeEnd ),(BYTE*)&clPrivateTradeEnd );

	//			pclMsg->siHorse2, &pclMsg->clRecvHorse2

			pclCM->CR[pclMsg->usCharID2]->SendNetMsg((sPacketHeader*)&clMsg);

			//////////////////////////////////////////////////////////////////////////
			// 주식 거래
			if ( pclMsg->siRecvStockNum2 > 0 && pclMsg->siRecvStockVillageUnique2 > 0 && pclMsg->siRecvStockVillageUnique2 < MAX_VILLAGE_NUMBER )
			{
				SI16 EmptyIndex = -1;
				for ( SI16 i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
				{
					if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == pclMsg->siRecvStockVillageUnique2 )
					{
						pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = pclMsg->siRecvStockNum2;
						break;
					}
					else if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == 0 && EmptyIndex == -1 )
					{
						EmptyIndex = i;
					}
				}

				if ( i == MAX_STOCK_KIND_IN_ACOUNT && EmptyIndex > -1 && EmptyIndex < MAX_STOCK_KIND_IN_ACOUNT )
				{
					pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ EmptyIndex ].siAmount = pclMsg->siRecvStockNum2;
					pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ EmptyIndex ].siVillageUnique = pclMsg->siRecvStockVillageUnique2;
				}
			}

			if ( pclMsg->siSendStockVillageUnique2 > 0 && pclMsg->siSendStockVillageUnique2 < MAX_VILLAGE_NUMBER )
			{
				for ( SI16 i = 0; i < MAX_STOCK_KIND_IN_ACOUNT; ++i )
				{
					if ( pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique == pclMsg->siSendStockVillageUnique2 )
					{
						if ( pclMsg->siSendStockNum2 > 0 )
						{
							pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = pclMsg->siSendStockNum2;
						}
						else
						{
							pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siAmount = 0;
							pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clStock.clInfo.clUnit[ i ].siVillageUnique = 0;
						}
						break;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////


			//////////////////////////////////////////////////////////////////////////
			// 시전 거래
			if ( pclMsg->siSendHouseVillageUnique2 > 0 && pclMsg->siSendHouseVillageUnique2 < MAX_VILLAGE_NUMBER )
			{
				pclCM->CR[pclMsg->usCharID2]->pclCI->clRealEstate.Delete( REALESTATE_TYPE_HOUSE, pclMsg->siSendHouseVillageUnique2, pclMsg->siSendHouseUnitSlot2 );
			}

			if ( pclMsg->siRecvHouseVillageUnique2 > 0 && pclMsg->siRecvHouseVillageUnique2 < MAX_VILLAGE_NUMBER )
			{
				cltHouse* pclhouse = (cltHouse*)pclHouseManager->pclStruct[ pclMsg->siRecvHouseVillageUnique2 ];

				if( pclhouse != NULL )
				{
					pclCM->CR[pclMsg->usCharID2]->pclCI->clRealEstate.Add( REALESTATE_TYPE_HOUSE, pclMsg->siRecvHouseVillageUnique2, pclMsg->siRecvHouseUnitSlot2, &pclhouse->clUnit[ pclMsg->siRecvHouseVillageUnique2 ].clContract );
				}
			}
			//////////////////////////////////////////////////////////////////////////
			

			//////////////////////////////////////////////////////////////////////////
			// 말 거래 ( 말 강제로 내린 후에 거래 )
			if ((pclMsg->siHorse2 != -1) && (pclMsg->siRecvHorse2 != -1)) //서로 말을 주고 받았다.
			{
				pclCM->CR[pclMsg->usCharID2]->UnrideHorse();
				//pclCM->CR[ pclMsg->usCharID1 ]->pclCI->clHorseInfo.clHorse.Set( &pclMsg->clRecvHorse1 );
				pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.Init(pclMsg->siHorse2);
				pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siRecvHorse2, &pclMsg->clRecvHorse2 );
				pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.SetCurrentShowHorseIndex(pclMsg->siRecvHorse2);

				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 교환, 또는 보냄 )
				//---------------------------------------
				((cltCharServer*)pclCM->CR[pclMsg->usCharID2])->SendNeighbourMyHorseStatus(pclCM->CR[pclMsg->usCharID2]->pclCI->clHorseInfo.siCurrentShowHorse);

			}
			else if ( pclMsg->siHorse2 != -1 )
			{
				pclCM->CR[ pclMsg->usCharID2 ]->UnrideHorse();
				pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siHorse2, &pclMsg->clRecvHorse2 );

				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 교환 또는 보냄 )
				//---------------------------------------
				{
					((cltCharServer*)pclCM->CR[pclMsg->usCharID2])->SendNeighbourMyHorseStatus( pclCM->CR[pclMsg->usCharID2]->pclCI->clHorseInfo.siCurrentShowHorse);
				}
			}
			else if ( pclMsg->siRecvHorse2 != -1 )
			{
				pclCM->CR[ pclMsg->usCharID2 ]->pclCI->clHorseInfo.SetHorse( pclMsg->siRecvHorse2, &pclMsg->clRecvHorse2 );

				//---------------------------------------
				// 이웃들에게 말정보 변경을 알림 ( 말 생성 )
				//---------------------------------------
				{
					((cltCharServer*)pclCM->CR[pclMsg->usCharID2])->SendNeighbourMyHorseStatus( pclCM->CR[pclMsg->usCharID2]->pclCI->clHorseInfo.siCurrentShowHorse);
				}
			}
			//////////////////////////////////////////////////////////////////////////


			//개인거래 퀘스트가 진행중인지 확인한다. 
			((cltCharServer*)pclCM->CR[pclMsg->usCharID2])->DoQuestCheckAndAction(QUEST_CLEAR_COND_PRIVATETRADE);

		}
	}

	pclPrivateTradeOrderMgr->Cancel( pclMsg->siPersonID1 );
	pclPrivateTradeOrderMgr->Cancel( pclMsg->siPersonID2 );

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		if( pclCM->IsValidID(pclMsg->usCharID1) && pclCM->IsValidID(pclMsg->usCharID2) )
		{
			SI32 i;
			// A 사용자에서 B 사용자로 옮겨간 아이템 로그
			for( i=0; i<MAX_PRIVATETRADEORDER_ITEM_NUM; i++ )
			{
				if( pclMsg->LOG_clItem1[i].siUnique > 0 )
				{
					// 아이템 거래 로그
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PRIVATE_TRADE, 
						0, (cltCharServer*)pclCM->GetChar(pclMsg->usCharID1), NULL, pclMsg->siPersonID2, 0, 0, &pclMsg->LOG_clItem1[i], 0, 0, 0, 0, 0, 0, 
						pclMsg->LOG_siItemOriPos1[i], pclMsg->LOG_siItemPos1[i], 0, 0, 0, NULL, NULL);
				}
			}

			// B 사용자에서 A 사용자로 옮겨간 아이템 로그
			for( i=0; i<MAX_PRIVATETRADEORDER_ITEM_NUM; i++ )
			{
				if( pclMsg->LOG_clItem2[i].siUnique > 0 )
				{
					// 아이템 거래 로그
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PRIVATE_TRADE, 
						0, (cltCharServer*)pclCM->GetChar(pclMsg->usCharID2), NULL, pclMsg->siPersonID1, 0, 0, &pclMsg->LOG_clItem2[i], 0, 0, 0, 0, 0, 0, 
						pclMsg->LOG_siItemOriPos2[i], pclMsg->LOG_siItemPos2[i], 0, 0, 0, NULL, NULL);
				}
			}
		}

		if(pclMsg->siRecvStockNum1 > 0)
		{
			// [로그추가 : 박기형 2010. 01. 20] // 주식 개인거래 로그쓰기.
			// param1		 == 기존 주식수 + 받은 주식수
			// param2		 == 받은 주식수
			// param3		 == 주식을 준 사람이 보유한 나머지 주식 수
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_PRIVATETRADE, 
				0, pclCM->GetCharServer(pclMsg->usCharID1), NULL, pclMsg->siPersonID2, 0, 0, 0, 0, 0, 0, pclMsg->siRecvStockVillageUnique1, 0, 0, 
				pclMsg->siRecvStockNum1, pclMsg->siRecvedStockNumToSender1 , pclMsg->siSendStockNum2, 0, 0, 0, 0);		
		}

		if(pclMsg->siRecvStockNum2 > 0)
		{
			// [로그추가 : 박기형 2010. 01. 20] // 주식 개인거래 로그쓰기.
			// param1		 == 기존 주식수 + 받은 주식수
			// param2		 == 받은 주식수
			// param3		 == 주식을 준 사람이 보유한 나머지 주식 수
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_STOCK, LOGCOMMAND_INDEX_STOCK_PRIVATETRADE, 
				0, pclCM->GetCharServer(pclMsg->usCharID2), NULL, pclMsg->siPersonID1, 0, 0, 0, 0, 0, 0, pclMsg->siRecvStockVillageUnique2, 0, 0, 
				pclMsg->siRecvStockNum2, pclMsg->siRecvedStockNumToSender2, pclMsg->siSendStockNum1, 0, 0, 0, 0);		
		}

		if(pclMsg->siRecvHorse1 > -1)
		{
			TCHAR szHorseAbility[50] = {'\0', };
			StringCchPrintf(szHorseAbility, 50, "Str: %d, Dex: %d, Mag: %d, Speed: %d",
				pclMsg->clRecvHorse1.siStr,
				pclMsg->clRecvHorse1.siDex,
				pclMsg->clRecvHorse1.siMag,
				pclMsg->clRecvHorse1.siMoveSpeed );

			// [로그추가 : 박기형 2009. 07. 14] // 탈것 개인거래 로그쓰기.
			// param1		 == 주는사람 말 슬롯번호
			// param2		 == 받는사람 말 슬롯번호.
			// pszCharParam1 == 말 이름.
			// pszCharParam2 == 말 정보.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSESET, LOGCOMMAND_INDEX_HORSESET_PRIVATETRADE, 
				0, (cltCharServer*)pclCM->GetChar(pclMsg->usCharID1), NULL, pclMsg->siPersonID2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
				pclMsg->siHorse2, pclMsg->siRecvHorse1, 0, 0, 0, pclMsg->clRecvHorse1.szName, szHorseAbility);		
		}

		if(pclMsg->siRecvHorse2 > -1)
		{
			TCHAR szHorseAbility[50] = {'\0', };
			StringCchPrintf(szHorseAbility, 50, "Str: %d, Dex: %d, Mag: %d, Speed: %d",
				pclMsg->clRecvHorse2.siStr,
				pclMsg->clRecvHorse2.siDex,
				pclMsg->clRecvHorse2.siMag,
				pclMsg->clRecvHorse2.siMoveSpeed );

			// [로그추가 : 박기형 2009. 07. 14] // 탈것 개인거래 로그쓰기.
			// param1		 == 주는사람 말 슬롯번호
			// param2		 == 받는사람 말 슬롯번호.
			// pszCharParam1 == 말 이름.
			// pszCharParam2 == 말 정보.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HORSESET, LOGCOMMAND_INDEX_HORSESET_PRIVATETRADE, 
				0, (cltCharServer*)pclCM->GetChar(pclMsg->usCharID2), NULL, pclMsg->siPersonID1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
				pclMsg->siHorse1, pclMsg->siRecvHorse2, 0, 0, 0, pclMsg->clRecvHorse2.szName, szHorseAbility);		
		}
	}
	
	// 아이템을 한번 업데이트해준다. 말 거래때문
	{
		sDBRequest_PersonItemInfoGet clMsg1(pclMsg->usCharID1, pclMsg->siPersonID1);
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg1);

		sDBRequest_PersonItemInfoGet clMsg2(pclMsg->usCharID2, pclMsg->siPersonID2);
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg2);
	}


/*	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [로그추가 : 황진성 2007. 10. 11] // 개인 거래. (수정필요 : 정보가 너무 많음.)
		// 
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PRIVATE_TRADE, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										0, 0, 0, 0, 0, NULL, NULL);
	}*/
	return;
}

// 사용자 로그인 허용/제한 응답. 
void cltServer::DoMsg_DBMSG_RESPONSE_BLOCK(sPacketHeader* pPacket)
{
	sDBResponse_Block* pclMsg = (sDBResponse_Block* )pPacket;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id)	== false)return ;
	if(pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)return ;

	SI32 returnval = 0;
	if(pclMsg->siBlockMode == 1)
	{
		returnval = SRVAL_BLOCK_UNBLOCKED;
	}
	else
	{
		returnval = SRVAL_BLOCK_BLOCKED;
	}

	// 클라이언트로 서버의 응답값을 보낸다. 
	SendServerResponseMsg(0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

}

// 특정 사용자 로그인 허용/제한 응답. 
void cltServer::DoMsg_DBMSG_RESPONSE_BLOCKUSER(sPacketHeader* pPacket)
{
	sDBResponse_BlockUser* pclMsg = (sDBResponse_BlockUser* )pPacket;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id)	== false)return ;
	if(pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)return ;

	SI32 returnval = 0;

	switch(pclMsg->siWarnMode)
	{
	case sDBResponse_BlockUser::WARNING_EMPTY:
		{
			if(pclMsg->siBlockMode == 0)
			{
				returnval = SRVAL_BLOCKUSER_UNBLOCKED;

			}
			else
			{
				returnval = SRVAL_BLOCKUSER_BLOCKED;

				//-------------------------------------------
				// 해당 사용자를 강퇴시킨다. 
				//-------------------------------------------
				pclCM->OutByPersonID(pclMsg->siPersonID);

			}

			//// 클라이언트로 서버의 응답값을 보낸다. 
			//SendServerResponseMsg(0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
		}
		break;
	case sDBResponse_BlockUser::WARNING_FIRST:
		{
			TCHAR buffer[512];
			TCHAR* pText = GetTxtFromMgr(5231);
			StringCchPrintf( buffer, 512, pText, pclMsg->szBlockReason );
			SendPostOfficeItemToPerson( pclMsg->siPersonID, NULL, buffer );

			return;	// 경고 메세지를 보냈으므로
		}
		break;
	case sDBResponse_BlockUser::BLOCK_FOR_5_DAYS:	// 5일간 블럭
	case sDBResponse_BlockUser::BLOCK_FOR_10_DAYS:	// 10일간 블럭
	case sDBResponse_BlockUser::BLOCK_FOR_FOREVER:	// 영구히 블럭
		{
			returnval = SRVAL_BLOCKUSER_BLOCKED;

			//-------------------------------------------
			// 해당 사용자를 강퇴시킨다. 
			//-------------------------------------------
			pclCM->OutByPersonID(pclMsg->siPersonID);
		}
		break;
	}

	// 클라이언트로 서버의 응답값을 보낸다. 
	SendServerResponseMsg(0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 9] // 특정 사용자의 접속을 차단/허용.
		// pszParam1 == 차단이유.
		// PCK - Reason 추가.
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_BLOCK_USER, 
										pclMsg->siWarnMode, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										0, 0, 0, 0, 0, pclMsg->szBlockReason, NULL);
	}
}


// 시간을 저장하라는  요청에 대한 응답
void cltServer::DoMsg_DBMSG_RESPONSE_SETTIME(sPacketHeader* pPacket)
{
	sDBResponse_SetTime* pclMsg = (sDBResponse_SetTime*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// DB지연 시간을 구한다. 
	dwDBLatency = TABS(CurrentClock - pclMsg->dwSetTimeClock);
}


// 시간을 얻어오라는 요청에 대한 응답
void cltServer::DoMsg_DBMSG_RESPONSE_GETTIME(sPacketHeader* pPacket)
{
	sDBResponse_GetTime* pclMsg = (sDBResponse_GetTime*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// 게임의 시간을 설정한다. 
	pclTime->clDate.Set(pclMsg->siYear, pclMsg->siMonth, pclMsg->siDay, pclMsg->siHour, pclMsg->siMinute);
	
	// 시간을 얻어왔음을 확인한다. 
	bGetTimeSwitch	= true;

}


// 맵타입 통보. 
void cltServer::DoMsg_DBMSG_RESPONSE_MAPTYPEINFO(sPacketHeader* pPacket)
{

	sDBResponse_MapTypeInfo* pclMsg = (sDBResponse_MapTypeInfo*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}


	for(SI32 i = 0;i < MAX_MAP_NUMBER;i++)
	{
		if(pclMsg->siMapTypeInfo[i] <= 0)continue;

		if(pclMapManager->pclMapArray[i] == NULL)continue;

		// 디폴트 지도와  다른 맵유니크를 갖고 있다면, 
		SI32 mapunique = pclMsg->siMapTypeInfo[i];
		if(pclMapManager->pclMapArray[i]->siMapUnique != mapunique)
		{
			// 기존 지도를 삭제한다. 
			delete pclMapManager->pclMapArray[i];
			pclMapManager->pclMapArray[i] = NULL;

			pclMapManager->LoadMap(this, i, mapunique);
		}

	}

	
	bGetMapTypeInfoSwitch = true;
}


// 마을 이동 허가 통보 
void cltServer::DoMsg_DBMSG_RESPONSE_WARPVILLAGE(sPacketHeader* pPacket)
{

	sDBResponse_WarpVillage* pclMsg = (sDBResponse_WarpVillage*)pPacket;

	// 해당 Item이 없다.
	if(pclMsg->siResult == 0)	return ;
	if(pclMsg->siFromVillageUnique < 0 || pclMsg->siFromVillageUnique >= MAX_MAP_NUMBER )		return;
	if( pclMapManager->pclMapArray[pclMsg->siFromVillageUnique] == NULL ) return ;
	if(pclMsg->siToVillageUnique < 0   || pclMsg->siToVillageUnique   >= MAX_VILLAGE_NUMBER)	return;
	if(pclMapManager->pclMapArray[pclMsg->siToVillageUnique] == NULL)return ;

	if(pclMsg->siItemPos < 0 || pclMsg->siItemPos > MAX_ITEM_PER_PERSON )						return;

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsAlive(id) == false)return ;
	
	// Client의 정보를 인벤토리 Update한다.
	if(pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siItemPos].Set(&pclMsg->clItem);
		
		// 클라이언트로 업데이트 된 정보를 보낸다. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	// 마을에 2000냥을 추가한다.
	if(pclMsg->siFromVillageUnique > 0	&& pclMsg->siFromVillageUnique < MAX_VILLAGE_NUMBER)
	{
		//sDBRequest_ChangeStrMoney sendMsg(CHANGESTRMONEY_SELLNPC, 0, pclMsg->siFromVillageUnique, RANKTYPE_CITYHALL, VILLAGE_PROFIT_FOR_FANPRIEST);
		sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, pclMsg->siFromVillageUnique, VILLAGE_PROFIT_FOR_FANPRIEST );
		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
	}
	// 사용자를 Warp시킨다.
	{
		SI32 ref = pclMsg->siToVillageUnique;
		SI32 mapindex		= pclVillageManager->pclVillageInfo[ref]->siVillageUnique;
		SI32 maptypeunique	= -1;
		if( mapindex >= 0 && mapindex < MAX_MAP_NUMBER )	maptypeunique = pclMapManager->pclMapArray[mapindex]->siMapUnique;
		// WARP를 한다.
		SI32 x	= -1;
		SI32 y	= -1;

		if( maptypeunique >= 0 && maptypeunique < MAX_MAPTYPE_NUMBER )
		{
			x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
			y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
		}
		
		if(id !=0 && pclCM->IsValidID(id)== FALSE)	return;
		if(x > 0 && y > 0)
		{
			id = cltCharServer::CharUniqueInfo[id];
			OrderStop(id, BY_COMPUTER);

			cltWarpInfo clWarpInfo(1, mapindex, false, false, x, y, -1, -1);
			pclCM->CR[pclMsg->usCharID]->SetWarpInfo(&clWarpInfo, 2000);
		}
	}

	
	/*if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 11] // 사용자를 Warp시킨다.
		// param1 == 이동마을 유니크. 
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_WARP_VILLAGE, 
										0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem, pclMsg->clItem.siItemNum, 0, 0, pclMsg->siFromVillageUnique, 0, 0, 
										pclMsg->siToVillageUnique, 0, 0, 0, 0, NULL, NULL);
	}*/
}

// 게임시작에 대한 정보로 공성시간을 얻어온다.
void cltServer::DoMsg_DBMSG_RESPONSE_STARTGAME(sPacketHeader* pPacket)
{

	sDBResponse_StartGame* pclMsg = (sDBResponse_StartGame*)pPacket;

	if(pclMsg->siResult == 0)	return ;

}

void cltServer::DoMsg_DBMSG_RESPONSE_MASTERGIVEITEM(sPacketHeader* pPacket)
{
	sDBResponse_MasterGiveItem* pclMsg = (sDBResponse_MasterGiveItem *)pPacket;

	if( pclMsg->usCount > 1000 )		pclMsg->usCount = 1000;

	for( int i = 0; i < pclMsg->usCount; ++i ) {
		SendPostOfficeItemToPerson( pclMsg->siPersonID[ i ], &pclMsg->clItem, pclMsg->szMsg );
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GIVEITEM(sPacketHeader* pPacket)
{
	// PCK : 로그용으로 추가함.
	sDBResponse_GiveItem*	pclMsg = (sDBResponse_GiveItem*)pPacket;

	SI32 id = pclMsg->usCharID;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	// [로그추가 : 황진성 2007. 10. 18] // 시스템에서 아이템 주기.
	// param1 == 최소레벨, 
	// param2 == 최대레벨,
	// param3 == 아이템 기간,
	// pszParam1 == 메시지
	cltServer * pclServer = (cltServer*)pclClient;
	pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SYSTEM, LOGCOMMAND_INDEX_SYSTEM_GIVE_ITEM, 
		0, pclchar, NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
		pclMsg->minLevelRange, pclMsg->maxLevelRange, pclMsg->clDate.GetDateVary(), 0, 0, pclMsg->szMsg, NULL);
}

void cltServer::DoMsg_DBMSG_RESPONSE_DBSYSTEMINFO(sPacketHeader* pPacket)
{
	sDBResponse_DBSystemInfo *pclMsg = (sDBResponse_DBSystemInfo *)pPacket;

	if( pclMsg->siResult != 1 )						return;
	
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == TRUE && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		switch(pclMsg->siType)
		{
		// 클라이언트에 사실을 알린다. 
		case DBSYSTEMINFO_TODAY_NEWUSERNUM:
			SendServerResponseMsg(0, SRVAL_DBSYSTEMINFO,  DBSYSTEMINFO_TODAY_NEWUSERNUM, pclMsg->siValue, pclCM->CR[id]->GetCharUnique());
			break;

		case DBSYSTEMINFO_CALCULATE_WEALTHRANK:
			SendServerResponseMsg(0, SRVAL_DBSYSTEMINFO,  DBSYSTEMINFO_CALCULATE_WEALTHRANK, 2 , pclCM->CR[id]->GetCharUnique());
			break;
		case DBSYSTEMINFO_CALCULATE_TOTALMONEY:
			SendServerResponseMsg(0, SRVAL_DBSYSTEMINFO,  DBSYSTEMINFO_CALCULATE_TOTALMONEY, 3 , pclCM->CR[id]->GetCharUnique());
			break;
		}
	}

	// 통화량을 얻어왔으므로 서버에 저장한다.
	switch( pclMsg->siType )
	{
	case DBSYSTEMINFO_GET_TOTALMONEY:
		{
			siTotalMoney = pclMsg->siValue;
			m_pclBalanceCurrencyMgr->SetTodayCurrency(pclMsg->siValue);
			m_pclBalanceCurrencyMgr->SetUpdateState(CURRENCY_UPDATE_TODAY_DONE);
		}
		break;

	case DBSYSTEMINFO_GET_TOTALMONEY_YESTERDAY:
		{
			m_pclBalanceCurrencyMgr->SetYesterDayCurrency(pclMsg->siValue);
			m_pclBalanceCurrencyMgr->SetUpdateState(CURRENCY_UPDATE_ALL_DONE);
		}
		break;

		// 등급만 변경 시키는 거라 따로 할일은 없다.
	case DBSYSTEMINFO_CHANGEGRADE:
		{

		}break	;
	}
	return;

}

void cltServer::DoMsg_DBMSG_RESPONSE_DBSTARTINFO(sPacketHeader *pPacket)
{
	sDBResponse_DBStartInfo *pclMsg = (sDBResponse_DBStartInfo *)pPacket;
	
	if( pclMsg->siResult != 1 )						return;
	
	clServerStartInfo.Set( &pclMsg->clServerStartInfo );
	siStartBankruptDateVary = pclMsg->siStartBankruptDateVary;
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_DBStartInfo"));

	siFourLeafUnique = pclMsg->siFourLeafUnique;	//[진성] 현재 사용중인 네잎클로버 유니크 => 2008-8-14

	// 기본 네잎클로버로 설정한다.
	if ( 0 >= siFourLeafUnique )
	{
		// DB에 설정값이 없으면, 기본 네잎클로버로 설정된다.
		//siFourLeafUnique = ITEMUNIQUE(2755);

		sDBRequest_SetFourLeaf clMsg( ITEMUNIQUE(2755) );
		SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETFOURLEAF(sPacketHeader *pPacket)
{
	sDBResponse_SetFourLeaf *pclMsg = (sDBResponse_SetFourLeaf*)pPacket;

	if( 1 != pclMsg->siResult )		return;

	siFourLeafUnique = pclMsg->siFourLeafUnique;	//[진성] 현재 사용중인 네잎클로버 유니크 => 2008-8-14
}


void cltServer::DoMsg_DBMSG_RESPONSE_DBINITCOMPLETE(sPacketHeader *pPacket)
{
	sDBResponse_DBInitComplete *pRecvMsg = (sDBResponse_DBInitComplete *)pPacket;
	if(pRecvMsg->siSelect < 0 || pRecvMsg->siSelect >= DBCONNECTION_NUMBER )		return;

	//bCompleteDBInit[ pRecvMsg->siSelect ] = TRUE;
	siCompleteDBInit[ pRecvMsg->siSelect ] = pRecvMsg->siStep;
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_DBInitComplete"));

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETBYUNGZOINFO(sPacketHeader* pPacket)
{

	// BYUNGZO CLASS에 설정한다.
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_BYUNGZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETBYUNGZOINFO"));

}
void cltServer::DoMsg_DBMSG_RESPONSE_GETGONGZOINFO(sPacketHeader* pPacket)
{
	// GONGZO
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_GONGZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETGONGZOINFO"));

}
void cltServer::DoMsg_DBMSG_RESPONSE_GETHYUNGZOINFO(sPacketHeader* pPacket)
{
	// HYUNGZO
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_HYUNGZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETHYUNGZOINFO"));

}
void cltServer::DoMsg_DBMSG_RESPONSE_GETHOZOINFO(sPacketHeader* pPacket)
{
	// HOZO
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_HOZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETHOZOINFO"));

}
void cltServer::DoMsg_DBMSG_RESPONSE_GETIZOINFO(sPacketHeader* pPacket)
{
	// IZO
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_IZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETIZOINFO"));

}
void cltServer::DoMsg_DBMSG_RESPONSE_GETYEZOINFO(sPacketHeader* pPacket)
{

	// YEZO CLASS에 설정한다.
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_YEZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETYEZOINFO"));
	
}
void cltServer::DoMsg_DBMSG_RESPONSE_GETGOONZUINFO(sPacketHeader* pPacket)
{
	pclMinisterMgr->DoMsg_DBMsgResponse_GetMinisterInfo(MINISTER_GOONZU, pPacket);
	//주기적으로 찍히는 거라 일단 보류
	//pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_GETGOONZUINFO"));
}


/////////////////////

void cltServer::DoMsg_DBMSG_RESPONSE_SETBYUNGZOINFO(sPacketHeader* pPacket)
{
	// BYUNGZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_BYUNGZO, pPacket);
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("DoMsg_DBMSG_RESPONSE_SETBYUNGZOINFO"));
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETBYUNGZOINFO_VILLAGEWARTIME(sPacketHeader* pPacket)
{
	// 전쟁 시간만 설정했다.
	sDBResponse_SetByungzoInfo_VillageWarTime * pclMsg =  (sDBResponse_SetByungzoInfo_VillageWarTime*)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclMsg->siResult == 1)
	{	
		// 공성시간은 40분보다 작을수 없고 60분 보다 클수 없다.
		if(pclMsg->siVillageWarTime < 40 || pclMsg->siVillageWarTime > 60) pclMsg->siVillageWarTime = 40;

		((CMinisterByungzo*)pclMinisterMgr->m_MinisterBase[MINISTER_BYUNGZO])->m_siVillageWarTime = pclMsg->siVillageWarTime;
				
		((CMinisterByungzo*)pclMinisterMgr->m_MinisterBase[MINISTER_BYUNGZO])->m_siPersonID = pclMsg->siPersonID;	
		
		StringCchCopy( ((CMinisterByungzo*)pclMinisterMgr->m_MinisterBase[MINISTER_BYUNGZO])->m_szGreeting ,256, pclMsg->m_szGreeting);


		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 10] // 병조 마을 전쟁.
			// param1 == 공성시간.  
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_BYUNGZO_VILLAGE_WAR_SET, 
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siVillageWarTime, 0, 0, 0, 0, NULL, NULL);
		}
	}
	else
	{
		if(((cltServer *)pclClient)->pclCM->IsAlive(id) == false)return ;

		// 서버 Error
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETBYUNGZOINFO,  0, 0, id);

	}

	if (pclClient->pclCM->IsValidID(id))
	{
		// 정보를 요청했을때와 같이 돌려준다.
		((CMinisterByungzo*)pclMinisterMgr->m_MinisterBase[MINISTER_BYUNGZO])->DoMsg_GameMsgRequest_GetMinisterInfo(id);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETGONGZOINFO(sPacketHeader* pPacket)
{
	// GONGZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_GONGZO, pPacket);

}
void cltServer::DoMsg_DBMSG_RESPONSE_SETHYUNGZOINFO(sPacketHeader* pPacket)
{
	// HYUNGZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_HYUNGZO, pPacket);
}
void cltServer::DoMsg_DBMSG_RESPONSE_SETHOZOINFO(sPacketHeader* pPacket)
{
	// HOZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_HOZO, pPacket);

}
void cltServer::DoMsg_DBMSG_RESPONSE_SETIZOINFO(sPacketHeader* pPacket)
{
	// IZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_IZO, pPacket);

}
void cltServer::DoMsg_DBMSG_RESPONSE_SETYEZOINFO(sPacketHeader* pPacket)
{
	// YEZO
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_YEZO, pPacket);
	
}
void cltServer::DoMsg_DBMSG_RESPONSE_SETGOONZUINFO(sPacketHeader* pPacket)
{
	// GOONZU
	pclMinisterMgr->DoMsg_DBMsgResponse_SetMinisterInfo(MINISTER_GOONZU, pPacket);
}
void cltServer::DoMsg_DBMSG_RESPONSE_SETGOONZUFINANCES(sPacketHeader* pPacket)
{
	// GOONZUFINANCES
	sDBResponse_SetGoonzuFinances* pclMsg = (sDBResponse_SetGoonzuFinances* )pPacket;

	if ( pclMsg->siResult == 0 )
	{
		return ;
	}

	CMinisterGoonzu *pclminister = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclminister == NULL ) return ;

	pclminister->InitializeDB();

	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 10] // 군주 재정.	
		// param1 == 임시 재정, param2 == 총 재정
		cltServer * pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_GOONZU_FINANCES_SET, 
										0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
										pclminister->m_iTempFinances, pclminister->m_iTotalFinances, 0, 0, 0, NULL, NULL);
	}
}
void cltServer::DoMsg_DBMSG_RESPONSE_GETANGELAPPLYERLIST(sPacketHeader* pPacket)
{
	CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_GetAngelApplyerList(pPacket);
}
void cltServer::DoMsg_DBMSG_RESPONSE_GETANGELLIST(sPacketHeader* pPacket)
{
	CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_GetAngelList(pPacket);
}
void cltServer::DoMsg_DBMSG_RESPONSE_SETANGELAPPLYER(sPacketHeader* pPacket)
{
	CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_SetAngelApplyer(pPacket);
}
void cltServer::DoMsg_DBMSG_RESPONSE_SETANGEL(sPacketHeader* pPacket)
{
	CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_SetAngel(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETPOLICELIST(sPacketHeader* pPacket)
{
	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_GetPoliceList(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETPOLICE(sPacketHeader* pPacket)
{
	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_SetPolice(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETCRIMINALLIST(sPacketHeader* pPacket)
{
	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_GetCriminalList(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETCRIMINAL(sPacketHeader* pPacket)
{
	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_SetCriminal(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_PRISONUSER(sPacketHeader* pPacket)
{
	sDBResponse_PrisonUser* pclMsg = (sDBResponse_PrisonUser* )pPacket;

	SI32 id = pclMsg->usCharID;

	if ( pclMsg->siResult != 1 && pclCM->IsValidID(id) == true )
	{
		SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETHYUNGZOPRISON,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// 형조판서 리스트를 다시 불러온다.
	sDBRequest_GetHyungzoInfo clMsg;
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	// 감옥에 가야할 대상자가 접속중이지 확인한다. 
	SI32 prisonid		= 0;
	SI32 prisonpersonid = 0;
	if ( pclHashTable->Find( pclMsg->szPersonName, prisonpersonid, prisonid, 60 ) == true  )
	{
		if( pclCM->IsValidID(prisonid) )
		{
			pclCM->CR[prisonid]->pclCI->clGuiltyInfo.Set(&pclMsg->clGuiltyInfo);
			// 감옥으로 보낸다. 
			((cltCharServer*)pclCM->CR[prisonid])->SendPrison();
		}
	}

	// 클라이언트로 서버의 응답값을 보낸다. 
	if ( pclCM->IsValidID(id) == TRUE )
	{
		SendServerResponseMsg(0, SRVAL_PRISON_SUCCESS,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2007. 10. 10] // 감옥 이동 로그쓰기(수감내역).
		// param1	 == 남은 수감 시간. 
		// param2	 == 총 수감 시간. 
		// pszParam1 == 캐릭터이름, 
		// pszParam2 == 이유.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PRISON, LOGCOMMAND_INDEX_PRISON_IN, 
							0, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
							pclMsg->clGuiltyInfo.siLeftPrisonSecond, pclMsg->clGuiltyInfo.siTotalPrisonSecond, 0, 0, 0, 
							pclMsg->szPersonName, pclMsg->clGuiltyInfo.szPrisonReason);
	}
}

void cltServer::DoMsg_DBLOGMSG_RESPONSE_PERSONAL_LOG(sPacketHeader* pPacket)
{
	/*
	sDBResponse_Personal_Log *pclMsg = (sDBResponse_Personal_Log *)pPacket;

	if ( pclMsg->siResult == 0 ) return ;

	SI32 id = pclMsg->usCharID ;
	if ( id <= 0 ) return ;
	
	stLOGData	stlogdata[MAX_STLOGDATA_PER_PACKET];
	
	for ( SI32 i = 0 ; i < MAX_STLOGDATA_PER_PACKET ; i ++ )
	{
		stlogdata[i].Init();
		if ( !_tcscmp(pclMsg->stLogData[i].szDate,TEXT("")) ) continue ;

		stlogdata[i].Set(&pclMsg->stLogData[i]);
	}

	cltGameMsgResponse_Personal_Log clinfo(pclMsg->siResult,stlogdata);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONAL_LOG, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	*/

	return ;
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETCHANGEDNAME(sPacketHeader* pPacket)
{
	sDBResponse_GetChangedName *pclMsg = (sDBResponse_GetChangedName *)pPacket;

	if ( pclCM->IsValidID(pclMsg->usCharID) == false ) return ;

	if ( pclMsg->siResult == 1 )
	{
		if ( pclCM->GetIDFromPersonID(pclMsg->siPersonID) == pclMsg->usCharID )
		{
			cltGameMsgResponse_GetChangedName clinfo(pclMsg->siResult,pclMsg->siPage,pclMsg->stChangedNameChar);
			cltMsg clMsg(GAMEMSG_RESPONSE_GETCHANGEDNAME, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[pclMsg->usCharID]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETDAILYNEWCHAR(sPacketHeader* pPacket)
{
	CMinisterHozo *pclminister = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclminister == NULL ) return ;

	pclminister->DoMsg_DBMsgResponse_GetDailyNewChar(pPacket);
}

void cltServer::DoMsg_DBMSG_RESPONSE_INITSTATISTICS(sPacketHeader* pPacket)
{
	sDBResponse_InitStatistics *pclMsg = (sDBResponse_InitStatistics *)pPacket;

	memcpy( &clCurrencyInfo, &pclMsg->clCurrencyInfo, sizeof( cltCurrencyInfo ) );
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_InitStatistics"));
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETWARRANKINFO(sPacketHeader* pPacket)
{
	sDBResponse_GetWarRankInfo *pclMsg = (sDBResponse_GetWarRankInfo *)pPacket;

	pclWarRankManager->SetWarRankInfo( &pclMsg->clWarRankInfo );
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetWarRankInfo"));

}

void cltServer::DoMsg_DBMSG_RESPONSE_SETWARRANKINFO(sPacketHeader* pPacket)
{
	sDBResponse_SetWarRankInfo *pclMsg = (sDBResponse_SetWarRankInfo *)pPacket;
	
	pclWarRankManager->SetWarRankInfo( &pclMsg->clWarRankInfo );
}

void cltServer::DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_SAVEINVENTORY(sPacketHeader *pPacket)
{
	sDBResponse_Wennyoldman_SaveInventory *pclMsg = (sDBResponse_Wennyoldman_SaveInventory*)pPacket;

	if (pclCM->IsValidID(pclMsg->usCharID) == false) return;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[pclMsg->usCharID];

	if(pclchar->pclCI->GetPersonID() != pclMsg->siPersonID) return;

	
	if( pclMsg->siResult > 0)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// 분해된 아이템
			// param1 == 분해하는 아이템의 위치 
			// param2 == 분해 정보
			// param3 == 분해 퍼센트
			// param4 == 내구도에 의한 패널티
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_WENNY_OLDMAN_USEITEM, 
								0, (cltCharServer*)pclCM->CR[pclMsg->usCharID], NULL, 0, 0, 0, &pclMsg->clUseItem_Log, pclMsg->clUseItem.siItemNum, 0, 0, 0, 0, 0,
								pclMsg->siDisassembleItemPos, pclMsg->siWennyPercent, pclMsg->siResolutionRate, pclMsg->siDurabilityPenalty, 0,
								NULL, NULL);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			for (SI32 i=0; i<MAX_ITEM_PER_WENNYOLD; i++ )
			{
				if( pclMsg->clItemList[i].siUnique > 0 )
				{
					// [로그추가 : 황진성 2007. 10. 11] // 혹부리(2호식) 인벤토리에 저장 요청
					// param1 == 분해된 아이템 유니크
					// param2 == 분해된 아이템 SID
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_WENNY_OLDMAN_SAVE_INV, 
										0, (cltCharServer*)pclCM->CR[pclMsg->usCharID], NULL, 0, 0, 0, &pclMsg->clItemList[i], pclMsg->clItemList[i].siItemNum, 0, 0, 0, 0, 0, 
										pclMsg->clUseItem_Log.siUnique, pclMsg->clUseItem_Log.siSID, 0, 0, 0, 
										NULL, NULL);
				}
			}
		}

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[pclMsg->usCharID];

		//================================================ 
		// Client의 정보 이호식 창을 Update한다. 
		//================================================ 
		{
			cltGameMsgResponse_ItemDisAssemble clItemDisAssemble(pclMsg->siResult, pclMsg->clItemList, pclMsg->siWennyPercent, pclMsg->siResolutionRate, pclMsg->siDurabilityPenalty);
			cltMsg clMsg(GAMEMSG_RESPONSE_DISASSEMBLEITEM, sizeof(clItemDisAssemble), (BYTE*)&clItemDisAssemble);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		}
		
		//================================================ 
		// Client의 정보 인벤토리 Update한다. 
		//================================================ 
		if( pclMsg->siDisassembleItemPos >= 0 && pclMsg->siDisassembleItemPos < MAX_ITEM_PER_PERSON )
		{
			pclchar->pclCI->clCharItem.clItem[pclMsg->siDisassembleItemPos].Set(&pclMsg->clUseItem);
			
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siDisassembleItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clUseItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}


		if(pclClient->IsCountrySwitch(Switch_WennyOldMan_CityhallProfitMoney))
		{
			// 이호식 분해하였을 경우 국가(마을) 자본금 증가
			SI32 currentVillage = pclchar->GetCurrentVillageUnique();
			if( currentVillage>0 && currentVillage < MAX_VILLAGE_NUMBER)
			{				
				GMONEY siGetVillageMoney = 0;
				SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

				// 가차 아이템
				if( pclGachaManager->IsGachaRareItem(pclMsg->siUsedItemUnique) )
				{
					siGetVillageMoney = npcrate * 25;
				}
				// 아이템 몰 아이템
                else if( pclItemManager->IsItemInfoAtb(pclMsg->siUsedItemUnique, ITEMINFOATB_ITEMMALL) == true)
				{
					siGetVillageMoney = npcrate * 10;
				}
				// 일반 아이템
				else
				{
					SI32 ref = pclItemManager->FindItemRefFromUnique( pclMsg->siUsedItemUnique );
					SI32 TempNPCRate = max(500, npcrate);	
					if(ref > 0 && ref < MAX_ITEMINFO_NUMBER)
					{
                        siGetVillageMoney = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel * TempNPCRate / (SI32)10;
						siGetVillageMoney = siGetVillageMoney * max(1, pclItemManager->pclItemInfo[ref]->clProductionInfo.GetToolCount());
					}
				}

				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, currentVillage, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}
		else
		{
			// 이호식 분해하였을 경우 국가(마을) 자본금 +5000
			SI32 currentVillage = pclchar->GetCurrentVillageUnique();
			if( currentVillage>0 && currentVillage < MAX_VILLAGE_NUMBER)
			{
				GMONEY siGetVillageMoney = 5000;
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, currentVillage, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}
		// 분해 퀘스트 있는경우 업데이트.
		pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_DISASSEMBLEITEM);
	
	}
	else
	{
		SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_FULLINVEN, 0, 0, pclMsg->usCharID);
	}


}

void cltServer::DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_MOVEITEMSTGTOINV(sPacketHeader *pPacket)
{
	sDBResponse_Wennyoldman_MoveItemStgToInv *pclMsg = (sDBResponse_Wennyoldman_MoveItemStgToInv*)pPacket;

	SI32 id = pclMsg->usCharID;

	if (pclCM->IsValidID(id) == false) return;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[id];

	if( pclMsg->siResult > 0 )
	{
		sDBRequest_PersonItemInfoGet clMsg(pclchar->siID, pclchar->pclCI->GetPersonID());
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);

		sDBRequest_Wennyoldman_InventoryList clMsg2(pclchar->siID, pclchar->pclCI->GetPersonID());
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg2);

	
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 11] // 혹부리(2호식) 인벤토리에 사용자 인벤으로 이동
			// param1 == 혹부리(2호식) 인벤토리내 위치, 
			// param2 == 인벤토리 위치, 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_WENNY_OLDMAN_STG_TO_INV, 
								 0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clItem_Log, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
								 pclMsg->siStgPos, pclMsg->siInvPos, 0, 0, 0, 
								 NULL, NULL);
		}
	}
	else
	{
		SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FULLINVEN, 0, 0, id);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_WENNYOLDMAN_INVENTORYLIST(sPacketHeader *pPacket)
{
	sDBResponse_Wennyoldman_InventoryList *pclMsg = (sDBResponse_Wennyoldman_InventoryList*)pPacket;

	if (pclCM->IsValidID(pclMsg->usCharID) == false) return;
    
	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[pclMsg->usCharID];

	cltGameMsgResponse_ItemDisAssemble_List clItemDisAssembleList(pclMsg->siResult, pclMsg->clItemList);
	cltMsg clMsg(GAMEMSG_RESPONSE_DISASSEMBLEITEM_LIST, sizeof(clItemDisAssembleList), (BYTE*)&clItemDisAssembleList);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

}






void cltServer::DoMsg_DBMSG_RESPONSE_VILLAGEBANKRUPTCY(sPacketHeader* pPacket)
{
	sDBResponse_VillageBankruptcy *pclMsg = (sDBResponse_VillageBankruptcy*)pPacket;

	if( 1 != pclMsg->siResult )
		return;

	siStartBankruptDateVary = pclMsg->siDateVary;

	if( siStartBankruptDateVary == 0 )
	{
		SI32 i = 0;
		for( i = 0; i < MAX_VILLAGE_NUMBER; ++i )
		{
			cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[i];
			if( pclCityHall == NULL ) 
				continue;

			pclCityHall->bPrepareBankruptcy = FALSE;

		}
	}
	else
	{
		for( int i = 0; i < 5; ++i )
		{
			if ( pclMsg->siVillageUnique[i] <= 0 || pclMsg->siVillageUnique[i] >= MAX_VILLAGE_NUMBER )
				continue;

			cltCityHall *pclCityHall = (cltCityHall *)pclCityHallManager->pclStruct[pclMsg->siVillageUnique[i]];
			if( pclCityHall == NULL ) 
				continue;

			pclCityHall->bPrepareBankruptcy = TRUE;
		}
	}
}


//***************************************************************************************************************************
//
// 추가 : 황진성 2008. 2. 28 => 아티펙트 DB->S 메시지 처리 구현부분.
//
//[추가 : 황진성 2008. 2. 28 => 아티펙트 아이템 환원 DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_SAVEINVENTORY(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_SaveInventory *pclMsg = (sDBResponse_Artifact_SaveInventory*)pPacket;

	if (pclCM->IsValidID(pclMsg->usCharID) == false) return;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[pclMsg->usCharID];

	if(pclchar->pclCI->GetPersonID() != pclMsg->siPersonID) return;


	if( pclMsg->siResult > 0)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// 분해된 아이템
			// param1 == 분해하는 아이템의 위치 
			// param2 == 분해 정보
			// param3 == 분해 퍼센트
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_ARTIFACT_USEITEM, 
				0, (cltCharServer*)pclCM->CR[pclMsg->usCharID], NULL, 0, 0, 0, &pclMsg->clUseItem_Log, pclMsg->clUseItem.siItemNum, 0, 0, 0, 0, 0,
				pclMsg->siDisassembleItemPos, pclMsg->siWennyPercent, pclMsg->siResolutionRate, 0, 0,
				NULL, NULL);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			for (SI32 i=0; i<MAX_ITEM_ARTIFACT; i++ )
			{
				if( pclMsg->clItemList[i].siUnique > 0 )
				{
					// [로그추가 : 황진성 2007. 10. 11] // 혹부리(2호식) 인벤토리에 저장 요청
					// param1 == 환원한 아이템 유니크
					// param2 == 환원한 아이템 SID
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_ARTIFACT_SAVE_INV, 
						0, (cltCharServer*)pclCM->CR[pclMsg->usCharID], NULL, 0, 0, 0, &pclMsg->clItemList[i], pclMsg->clItemList[i].siItemNum, 0, 0, 0, 0, 0, 
						pclMsg->clUseItem_Log.siUnique, pclMsg->clUseItem_Log.siSID, 0, 0, 0, 
						NULL, NULL);
				}
			}
		}

		// 통계
		NStatistics_Add("Item", pclMsg->clUseItem_Log.siUnique, "ResolveNum", pclMsg->clUseItem_Log.siItemNum);
		NStatistics_Set("Item", pclMsg->clUseItem_Log.siUnique, "Name", pclItemManager->GetName(pclMsg->clUseItem_Log.siUnique));

		for (SI32 i=0; i<MAX_ITEM_ARTIFACT; i++ )
		{
			if( pclMsg->clItemList[i].siUnique > 0 )
			{
				NStatistics_Add("Item", pclMsg->clItemList[i].siUnique, "FromResolve", pclMsg->clItemList[i].siItemNum);
				NStatistics_Set("Item", pclMsg->clItemList[i].siUnique, "Name", pclItemManager->GetName(pclMsg->clItemList[i].siUnique));
			}
		}

		cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[pclMsg->usCharID];

		//================================================ 
		// Client의 정보 이호식 창을 Update한다. 
		//================================================ 
		{
			cltGameMsgResponse_ItemDisAssemble clItemDisAssemble(pclMsg->siResult, pclMsg->clItemList, pclMsg->siWennyPercent , pclMsg->siResolutionRate, 0,  ItemDisAssemble_NPC_KIND::NPC_ATIFACT);
			cltMsg clMsg(GAMEMSG_RESPONSE_DISASSEMBLEITEM, sizeof(clItemDisAssemble), (BYTE*)&clItemDisAssemble);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);

		}

		//================================================ 
		// Client의 정보 인벤토리 Update한다. 
		//================================================ 
		if( pclMsg->siDisassembleItemPos >= 0 && pclMsg->siDisassembleItemPos < MAX_ITEM_PER_PERSON )
		{
			pclchar->pclCI->clCharItem.clItem[pclMsg->siDisassembleItemPos].Set(&pclMsg->clUseItem);

			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siDisassembleItemPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clUseItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}


		if(pclClient->IsCountrySwitch(Switch_WennyOldMan_CityhallProfitMoney))
		{
			// 이호식 분해하였을 경우 국가(마을) 자본금 증가
			SI32 currentVillage = pclchar->GetCurrentVillageUnique();
			if( currentVillage>0 && currentVillage < MAX_VILLAGE_NUMBER)
			{				
				GMONEY siGetVillageMoney = 0;
				SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

				// 가차 아이템
				if( pclGachaManager->IsGachaRareItem(pclMsg->siUsedItemUnique) )
				{
					siGetVillageMoney = npcrate * 25;
				}
				// 아이템 몰 아이템
				else if( pclItemManager->IsItemInfoAtb(pclMsg->siUsedItemUnique, ITEMINFOATB_ITEMMALL) == true)
				{
					siGetVillageMoney = npcrate * 10;
				}
				// 일반 아이템
				else
				{
					SI32 ref = pclItemManager->FindItemRefFromUnique( pclMsg->siUsedItemUnique );
					SI32 TempNPCRate = max(500, npcrate);
					if(ref > 0 && ref < MAX_ITEMINFO_NUMBER)
					{
						siGetVillageMoney = pclItemManager->pclItemInfo[ref]->clSkillInfo.siSkillLevel * TempNPCRate / (SI32)10;
						siGetVillageMoney = siGetVillageMoney * max(1, pclItemManager->pclItemInfo[ref]->clProductionInfo.GetToolCount());
					}
				}

				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, currentVillage, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}
		else
		{
			// 이호식 분해하였을 경우 국가(마을) 자본금 +5000
			SI32 currentVillage = pclchar->GetCurrentVillageUnique();
			if( currentVillage>0 && currentVillage < MAX_VILLAGE_NUMBER)
			{
				GMONEY siGetVillageMoney = 5000;
				sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, currentVillage, siGetVillageMoney );
				pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
			}
		}
		// 분해 퀘스트 있는경우 업데이트.
		pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_DISASSEMBLEITEM);

		// 환원을 통해 원소,속성가루를 획득하는 퀘스트의 경우
		bool bGetElement	= pclchar->pclCI->clQuestInfo.IsQuestGoing( QUEST_CLEAR_COND_GETELEMENT_RESTORE );
		bool bGetPowder		= pclchar->pclCI->clQuestInfo.IsQuestGoing( QUEST_CLEAR_COND_GETPOWDER_RESTORE );

		if ( (true == bGetElement) || (true == bGetPowder) )
		{
			for ( SI32 siIndex=0; siIndex<MAX_ITEM_ARTIFACT; ++siIndex )
			{
				SI32 siItemUnique	= pclMsg->clItemList[siIndex].siUnique;
				SI32 siItemAmount	= pclMsg->clItemList[siIndex].siItemNum;

				switch ( siItemUnique )
				{
				case ITEMUNIQUE(1701):	// 리튬 원소
				case ITEMUNIQUE(1703):	// 아르곤 원소
				case ITEMUNIQUE(1705):	// 셀렌 원소
				case ITEMUNIQUE(1707):	// 루비듐 원소
				case ITEMUNIQUE(1709):	// 스트론튬 원소
				case ITEMUNIQUE(1711):	// 카드뮴 원소
				case ITEMUNIQUE(1713):	// 프라디윰 원소
				case ITEMUNIQUE(1715):	// 루테튬 원소
				case ITEMUNIQUE(1717):	// 레늄 원소
				case ITEMUNIQUE(1719):	// 백금 원소
					{
						pclchar->IncQuestPara( QUEST_CLEAR_COND_GETELEMENT_RESTORE, siItemUnique, siItemAmount );
					}
					break;

				case ITEMUNIQUE(1751):	// 이상한 무속성 가루
				case ITEMUNIQUE(1753):	// 이상한 불속성 가루
				case ITEMUNIQUE(1755):	// 이상한 물속성 가루
				case ITEMUNIQUE(1757):	// 이상한 땅속성 가루
				case ITEMUNIQUE(1759):	// 이상한 바람속성 가루
				case ITEMUNIQUE(1761):	// 신비한 무속성 가루
				case ITEMUNIQUE(1763):	// 신비한 불속성 가루
				case ITEMUNIQUE(1765):	// 신비한 물속성 가루
				case ITEMUNIQUE(1767):	// 신비한 땅속성 가루
				case ITEMUNIQUE(1769):	// 신비한 바람속성 가루
				case ITEMUNIQUE(1771):	// 환상의 무속성 가루
				case ITEMUNIQUE(1773):	// 환상의 불속성 가루
				case ITEMUNIQUE(1775):	// 환상의 물속성 가루
				case ITEMUNIQUE(1777):	// 환상의 땅속성 가루
				case ITEMUNIQUE(1779):	// 환상의 바람속성 가루
					{
						pclchar->IncQuestPara( QUEST_CLEAR_COND_GETPOWDER_RESTORE, siItemUnique, siItemAmount );
					}
					break;
				}	// switch ( siItemUnique ) 종료
			}	// for ( SI32 siIndex=0; siIndex<MAX_ITEM_ARTIFACT; ++siIndex ) 종료
		}	// if ( (true == bGetElement) || (true == bGetPowder) ) 종료

	}
	else
	{
		SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FAILDISASSEMBLE_FULLINVEN, 0, 0, pclMsg->usCharID);
	}


}

//[추가 : 황진성 2008. 2. 28 => 아티펙트 아이템 이동 DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_MOVEITEMSTGTOINV(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_MoveItemStgToInv *pclMsg = (sDBResponse_Artifact_MoveItemStgToInv*)pPacket;

	SI32 id = pclMsg->usCharID;

	if (pclCM->IsValidID(id) == false) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ pclMsg->usCharID ];
	if( NULL == pclchar )
		return;


	if( pclMsg->siResult > 0 )
	{
		sDBRequest_PersonItemInfoGet clMsg(pclchar->siID, pclchar->pclCI->GetPersonID());
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg);

		sDBRequest_Artifact_InventoryList clMsg2(pclchar->siID, pclchar->pclCI->GetPersonID());
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg2);


		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [로그추가 : 황진성 2007. 10. 11] // 혹부리(2호식) 인벤토리에 사용자 인벤으로 이동
			// param1 == 아티펙트 인벤토리내 위치, 
			// param2 == 인벤토리 위치, 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_ARTIFACT_STG_TO_INV, 
				0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clMoveItem, pclMsg->clItem.siItemNum, 0, 0, 0, 0, 0, 
				pclMsg->siStgPos, pclMsg->siInvPos, 0, 0, 0, 
				NULL, NULL);
		}
	}
	else
	{
		SendServerResponseMsg(0, SRVAL_WENNYOLDMAN_FULLINVEN, 0, 0, id);
	}

}

//[추가 : 황진성 2008. 2. 28 => 아티펙트 인벤 리스트  DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_INVENTORYLIST(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_InventoryList *pclMsg = (sDBResponse_Artifact_InventoryList*)pPacket;

	if (pclCM->IsValidID(pclMsg->usCharID) == false) return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ pclMsg->usCharID ];
	if( NULL == pclchar )
		return;


	cltGameMsgResponse_ItemDisAssemble_List clItemDisAssembleList( pclMsg->siResult, pclMsg->clItemList, ItemDisAssemble_NPC_KIND::NPC_ATIFACT );
	cltMsg clMsg(GAMEMSG_RESPONSE_DISASSEMBLEITEM_LIST, sizeof(clItemDisAssembleList), (BYTE*)&clItemDisAssembleList);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

}

//[추가 : 황진성 2008. 2. 28 => 아티펙트 조합 DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_MIXTURE(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_Mixture* pclMsg = (sDBResponse_Artifact_Mixture*)pPacket;

	if ( false == pclCM->IsValidID( pclMsg->m_usCharID ) ) 
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ pclMsg->m_usCharID ];
	if( NULL == pclchar )
		return;

	//if( 0 >= pclMsg->m_siResult )
	//{
	//	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//	{
	//		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
	//		// param1 == 슬롯이 조합된 아이템 위치. 
	//		cltServer* pclServer = (cltServer*)pclClient;
	//		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_MIXTURE, 
	//										0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//										-1, 0, 0, 0, 0, NULL, NULL);
	//	}
	//	return;
	//}
	
	pclchar->pclCI->clCharItem.clItem[pclMsg->m_siEquipItemPos].Set( &pclMsg->m_clEquipItem );
	
	SI32	 ItemPos		  = -1;
	cltItem* pclCreateCrystal = NULL; 
	for( SI32 Count = 0; Count < MAX_CRYSTAL_NUM; ++Count )
	{
		ItemPos			 =  pclMsg->m_siCrystalItemPosList[ Count ];
		if( 0 >= ItemPos )
			continue;

		pclCreateCrystal = &pclMsg->m_clCrystalItemList[ Count ];	
	
		pclchar->pclCI->clCharItem.clItem[ ItemPos ].Set( pclCreateCrystal );
	}


	cltGameMsgResponse_Artifact_Mixture cltInfo( pclMsg->m_siEquipItemPos,		&pclMsg->m_clEquipItem,
												 &pclMsg->m_siCrystalItemPosList[0], &pclMsg->m_clCrystalItemList[0] );
	cltMsg clMsg(GAMEMSG_RESPONSE_ARTIFACT_MIXTURE, sizeof(cltGameMsgResponse_Artifact_Mixture), (BYTE*)&cltInfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	
	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
		// param1 == 슬롯이 조합된 아이템 위치. 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_MIXTURE, 
							0, pclchar, NULL, 0, 0, 0, &pclMsg->m_clEquipItem, pclMsg->m_clEquipItem.GetItemNum(), 0, 0, 0, 0, 0, 
							pclMsg->m_siEquipItemPos, 0, 0, 0, 0, NULL, NULL);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		for( SI32 i=0; i<pclMsg->m_clCrystalItemList_Log.GetSize(); i++ )
		{
			if( pclMsg->m_clCrystalItemList_Log[i].siUnique <= 0 )		continue;

			// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
			// param1 == 슬롯이 조합된 아이템 위치. 
			// param2 == 결과로 생성된 아이템의 유니크
			// param3 == 결과로 생성된 아이템의 SID
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
				USEITEM_REASON_ARTIFACT_MIXTURE, pclchar, NULL, 0, 0, 0, &pclMsg->m_clCrystalItemList_Log[i], pclMsg->m_clCrystalItemList[i].GetItemNum(), 0, 0, 0, 0, 0, 
				pclMsg->m_siEquipItemPos, pclMsg->m_clEquipItem.siUnique, pclMsg->m_clEquipItem.siSID, 0, 0, NULL, NULL);
		}
	}

	// 무기에 결정체 조합해보기 퀘스트를 수행중이라면
	if ( pclMsg->m_clEquipItem.IsWeapon(pclItemManager) )
	{
		pclchar->IncQuestPara( QUEST_CLEAR_COND_ARTIFACTMIXWEAPON, pclMsg->m_clEquipItem.siUnique, 1 );
	}

	// 결정체 조합해보기 퀘스트를 수행중이라면
	pclchar->IncQuestPara( QUEST_CLEAR_COND_ARTIFACTMIX, 0, 1 );
	
}

//[추가 : 황진성 2008. 2. 28 => 아티펙트 제거 DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_REMOVE(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_Remove *pclMsg = (sDBResponse_Artifact_Remove*)pPacket;

	if ( false == pclCM->IsValidID( pclMsg->m_usCharID ) ) 
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ pclMsg->m_usCharID ];
	if( NULL == pclchar )
		return;

	//if( 0 >= pclMsg->m_siResult )
	//{
	//	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//	{
	//		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
	//		// param1 == 슬롯이 조합된 아이템 위치. 
	//		cltServer* pclServer = (cltServer*)pclClient;
	//		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_REMOVE, 
	//										0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//										-1, 0, 0, 0, 0, NULL, NULL);
	//	}
	//	return;
	//}

	SI32	 ItemPos		  = -1;
	cltItem* pclCreateCrystal = NULL; 
	cltItem* pclDeleteCrystal = NULL; 
	for( SI32 Count = 0; Count < MAX_CRYSTAL_NUM; ++Count )
	{
		// 사용된 결정체.(제거 결정체)
		ItemPos			 =  pclMsg->m_siCrystalItemPosList[ Count ];
		pclDeleteCrystal = &pclMsg->m_clCrystalItemList[ Count ];	

		if( 0 < ItemPos && MAX_ITEM_PER_PERSON > ItemPos)
			pclchar->pclCI->clCharItem.clItem[ ItemPos ].Set( pclDeleteCrystal );

		 			
		// 생성된 결정체.(장비에 결합 되있던 결정체)
		ItemPos			 =  pclMsg->m_siCreateCrystalItemPosList[ Count ];
		pclCreateCrystal = &pclMsg->m_clCreateCrystalItemList[ Count ];	
		
		if( 0 < pclCreateCrystal->siUnique )
			pclchar->pclCI->clCharItem.clItem[ ItemPos ].Set( pclCreateCrystal );
	}

	if( 0 < pclMsg->m_clEquipItem.siUnique )
		pclchar->pclCI->clCharItem.clItem[ pclMsg->m_siEquipItemPos ].Set( &pclMsg->m_clEquipItem );

	cltGameMsgResponse_Artifact_Remove cltInfo( pclMsg->m_siEquipItemPos,				&pclMsg->m_clEquipItem,
												pclMsg->m_siCrystalItemPosList,			 pclMsg->m_clCrystalItemList,
												pclMsg->m_siCreateCrystalItemPosList, 	 pclMsg->m_clCreateCrystalItemList	);
	cltMsg clMsg(GAMEMSG_RESPONSE_ARTIFACT_REMOVE, sizeof(cltGameMsgResponse_Artifact_Remove), (BYTE*)&cltInfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
		// param1 == 슬롯이 조합된 아이템 위치. 
		cltServer* pclServer = (cltServer*)pclClient;
		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_REMOVE, 
										0, pclchar, NULL, 0, 0, 0, &pclMsg->m_clEquipItem, 0, 0, 0, 0, 0, 0, 
										pclMsg->m_siEquipItemPos, 0, 0, 0, 0, NULL, NULL);
	}
}

//[추가 : 황진성 2008. 2. 28 => 아티펙트 슬롯 생성 DB->S]
void cltServer::DoMsg_DBMSG_RESPONSE_ARTIFACT_SLOT_CREATE(sPacketHeader *pPacket)
{
	sDBResponse_Artifact_Slot_Create *pclMsg = (sDBResponse_Artifact_Slot_Create*)pPacket;

	if ( false == pclCM->IsValidID( pclMsg->m_usCharID ) ) 
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ pclMsg->m_usCharID ];
	if( NULL == pclchar )
		return;
	
	//if( 0 >= pclMsg->m_siResult )
	//{
	//	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//	{
	//		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
	//		// param1 == 슬롯이 조합된 아이템 위치. 
	//		cltServer* pclServer = (cltServer*)pclClient;
	//		pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_SLOT_CREATE, 
	//										0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//										-1, 0, 0, 0, 0, NULL, NULL);
	//	}
	//	return;
	//}

	

	pclchar->pclCI->clCharItem.clItem[pclMsg->m_siEquipItemPos].Set( &pclMsg->m_clEquipItem );
	pclchar->pclCI->clCharItem.clItem[pclMsg->m_siCrystalItemPos].Set( &pclMsg->m_clCrystalItem);
	

	cltGameMsgResponse_Artifact_Slot_Create cltInfo( pclMsg->m_siEquipItemPos,	 &pclMsg->m_clEquipItem,
													 pclMsg->m_siCrystalItemPos, &pclMsg->m_clCrystalItem );
	cltMsg clMsg(GAMEMSG_RESPONSE_ARTIFACT_SLOT_CREATE, sizeof(cltGameMsgResponse_Artifact_Slot_Create), (BYTE*)&cltInfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
		// param1 == 슬롯이 조합된 아이템 위치. 
		// param2 == 이전 슬롯 개수
		// param3 == 새로 생성된 슬롯 개수
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ARTIFACT, LOGCOMMAND_INDEX_ARTIFACT_SLOT_CREATE, 
							0, pclchar, NULL, 0, 0, 0, &pclMsg->m_clEquipItem, pclMsg->m_clEquipItem.GetItemNum(), 0, 0, 0, 0, 0, 
							pclMsg->m_siEquipItemPos, pclMsg->m_clEquipItem_ForLog.siUseCrystalNum, pclMsg->m_clEquipItem.siUseCrystalNum, 0, 0, NULL, NULL);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [로그추가 : 황진성 2008-4-16 ] // 아티펙트 조합 로그 작성.
		// param1 == 사용되는 슬롯 결정체의 위치
		// param2 == 슬롯이 생성된 아이템의 유니크
		// param3 == 슬롯이 생성된 아이템의 SID
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM, 
			USEITEM_REASON_ARTIFACT_SLOT_CREATE, pclchar, NULL, 0, 0, 0, &pclMsg->m_clCrystalItem_ForLog, pclMsg->m_clCrystalItem.GetItemNum(), 0, 0, 0, 0, 0, 
			pclMsg->m_siCrystalItemPos, pclMsg->m_clEquipItem.siUnique, pclMsg->m_clEquipItem.siSID, 0, 0, NULL, NULL);
	}
}

//****************************************************************************************************************************************************************
//[진성] 서버 이벤트 처리 함수 (DB->S) => 2008-6-20
//****************************************************************************************************************************************************************

void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_RANK_INFO(sPacketHeader *pPacket)
{
	sDBResponse_Server_Event_Rank_Info *pclMsg = (sDBResponse_Server_Event_Rank_Info*)pPacket;

	if(0 > pclMsg->m_siResult)
		return;

	// 내 서버의 점수를 찾는다.
	CNServerDailyRankInfo clTempServerDailyRankInfo;
	ZeroMemory( &clTempServerDailyRankInfo, sizeof(clTempServerDailyRankInfo) );
	for( SI32 siCount = 0; siCount < SERVER_MAX_NUM; ++siCount )
	{
		if( siServerUnique == pclMsg->m_clServerDailyRankInfo[siCount].GetServerUnique() )
		{
			clTempServerDailyRankInfo = pclMsg->m_clServerDailyRankInfo[siCount];

			cltClient* pclclient = (cltClient*) pclClient;
			clTempServerDailyRankInfo.SetServerName(pclclient->GetServerNameFromUnique( clTempServerDailyRankInfo.GetServerUnique() ) );
			break;
		}
	}

	// 목표 점수 세팅.
	CNServerDailyRankInfo clTargetServerDailyRankInfo;
	clTargetServerDailyRankInfo.SetScore( GetGlobalValue("GV_GoonzuDay_Week_Score") );
	clTargetServerDailyRankInfo.SetServerUnique( 0 );
	clTargetServerDailyRankInfo.SetServerName( GetTxtFromMgr(40854) );

	CNServerRankInfo clTargetServerRankInfo;
	clTargetServerRankInfo.SetScore( GetGlobalValue("GV_GoonzuDay_Week_Score") );
	clTargetServerRankInfo.SetServerUnique( 0 );
	clTargetServerRankInfo.SetServerName( GetTxtFromMgr(40854) );

	CNServerRankInfo clTempServerRankInfo;
	clTempServerRankInfo.SetScore( clTempServerDailyRankInfo.GetScore() );
	clTempServerRankInfo.SetServerUnique( clTempServerDailyRankInfo.GetServerUnique() );
	cltClient* pclclient = (cltClient*) pclClient;
	clTempServerRankInfo.SetServerName( pclclient->GetServerNameFromUnique( clTempServerRankInfo.GetServerUnique() ) );
		
	// DB에서 받은 서버 정보를 내 서버 정보와 목표점수로 재 설정.
	ZeroMemory( &pclMsg->m_clServerRankInfo,		sizeof(pclMsg->m_clServerRankInfo) );
	ZeroMemory( &pclMsg->m_clServerDailyRankInfo,	sizeof(pclMsg->m_clServerDailyRankInfo) );
	
	if( clTargetServerDailyRankInfo.GetScore() >= clTempServerDailyRankInfo.GetScore() )
	{
		pclMsg->m_clServerRankInfo[0] = clTargetServerRankInfo;
		pclMsg->m_clServerRankInfo[1] = clTempServerRankInfo;

		pclMsg->m_clServerDailyRankInfo[0] = clTargetServerDailyRankInfo;
		pclMsg->m_clServerDailyRankInfo[1] = clTempServerDailyRankInfo;
	}
	else
	{
		pclMsg->m_clServerRankInfo[1] = clTargetServerRankInfo;
		pclMsg->m_clServerRankInfo[0] = clTempServerRankInfo;

		pclMsg->m_clServerDailyRankInfo[1] = clTargetServerDailyRankInfo;
		pclMsg->m_clServerDailyRankInfo[0] = clTempServerDailyRankInfo;
	}
	
	pclServerEventManager->SetServerRank(pclMsg->m_clServerRankInfo);
	pclServerEventManager->SetServerDailyRank(pclMsg->m_clServerDailyRankInfo);
	pclServerEventManager->SetPersonalRank(pclMsg->m_clPersonalRankInfo);
	pclServerEventManager->SetBonusBufType(pclMsg->m_ServerEventBufKind);
 
	
	switch(pclMsg->m_siReason)
	{
		case SERVER_EVENT_REASON_INSTANCE_MAP_CLEAR: // 인던 클리어(종료).
			{
				//pclServerEventManager->SendDBMsgServerInstanseMapClear();
			}
			break;
		case SERVER_EVENT_REASON_DAILRY:	// 하루 점수 업데이트.
			{
				// 하루가 종료되 모든 정보를 요청하는데 내 서버가 1등이면.
				if(pclServerEventManager->GetBackUpDailyServerUniqueRank(0) == pclClient->siServerUnique)
				{	
					//하루 점수가 1등 서버일때 버프등의 설정 적용.(DB에 기록한다.)
					pclServerEventManager->MyServerDailyRankBestBuf();

					//하루 점수가 1등을하면 얻는 점수.
					SI16 RankPonitScore = 20;
					
					// 하루 점수가 1등이 되었고 버프를 얻음을 알림.
					cltServerResponseValue clreturn(0, SRVAL_SERVER_EVENT_RANK_1, RankPonitScore, 0);
					cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
					pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
				}
				else
				{
					pclServerEventManager->MyServerDailyRankBestBufNo();
				}

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					cltServer * pclServer = (cltServer*)pclClient;

					// [로그추가 : 황진성 2008. 7. 7] 서버 이벤트
					// param1 = 서버 전체 순위.
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_DAILY_BUF, 
													0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
													pclServerEventManager->GetBonusBufType(), 0, 0, 0, 0, NULL, NULL);

					// [로그추가 : 황진성 2008. 7. 7] 서버 이벤트
					// param1 = 서버 전체 순위.
					SI32 Count = 0;
					for(	; Count < SERVER_MAX_NUM;  ++Count)
					{
						if(pclServerEventManager->GetServerUnique(Count) == pclClient->siServerUnique)
							break;
					}
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_TOTAL_RANK, 
													0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
													Count+1, 0, 0, 0, 0, NULL, NULL);

					// [로그추가 : 황진성 2008. 7. 7] 서버 이벤트
					// param1 = 서버 하루 순위.
					Count = 0;
					for(	; Count < SERVER_MAX_NUM;  ++Count)
					{
						if(pclServerEventManager->GetBackUpDailyServerUniqueRank(Count) == pclClient->siServerUnique)
							break;
					}
					pclServer->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_SERVER_EVENT, LOGCOMMAND_INDEX_SERVER_EVENT_DAILY_RANK, 
													0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
													Count+1, 0, 0, 0, 0, NULL, NULL);
				}
				
				// 서버의 버프를 파일로 기록.
				pclClient->pclLog->FilePrint( "config\\ServerEvent.log" , "[Daily Buf Type] BufType = %d", pclServerEventManager->GetBonusBufType()); 
			}
			break;
		case SERVER_EVENT_REASON_INFO_REQUEST://서버 이벤트의 모든 정보 요청.
			{
				
			}
			break;
		case SERVER_EVENT_REASON_END://서버 이벤트 종료.
			{
				// 클라이언트로 1등이 되었음을 알림.
				cltServerResponseValue clreturn(0, SRVAL_SERVER_EVENT_RANK_1, pclServerEventManager->GetServerUnique(0), 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clreturn);
				pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
			break;
	}
	

	cltGameMsgResponse_Server_Event_Rank_Info cltInfo;
	memcpy(cltInfo.m_clServerEvent_Rank_Record.GetServerRankInfo(0),		&pclMsg->m_clServerRankInfo,	  sizeof(CNServerRankInfo) * SERVER_MAX_NUM);
	memcpy(cltInfo.m_clServerEvent_Rank_Record.GetServerDailyRankInfo(0),	&pclMsg->m_clServerDailyRankInfo, sizeof(CNServerDailyRankInfo) * SERVER_MAX_NUM);
	memcpy(cltInfo.m_clServerEvent_Rank_Record.GetPersonalRankInfo(0),		&pclMsg->m_clPersonalRankInfo,	  sizeof(CNPersonalRankInfo) * USER_MAX_NUM);
	cltInfo.m_ServerEventBufKind = pclServerEventManager->GetBonusBufType();


	cltMsg clMsg(GAMEMSG_RESPONSE_SERVER_EVENT_RANK_INFO, sizeof(cltInfo), (BYTE*)&cltInfo);
	pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_SERVER_INFO(sPacketHeader *pPacket)
{
	/*sDBResponse_Server_Event_Server_Info *pclMsg = (sDBResponse_Server_Event_Server_Info*)pPacket;

	if(0 > pclMsg->m_siResult)
		return;

	pclServerEventManager->SetServerRank(pclMsg->m_clServerRankInfo);*/
}
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_DAILY_SERVER_INFO(sPacketHeader *pPacket)
{
	/*sDBResponse_Server_Event_Daily_Server_Info *pclMsg = (sDBResponse_Server_Event_Daily_Server_Info*)pPacket;

	if(0 > pclMsg->m_siResult)
		return;

	pclServerEventManager->SetServerDailyRank(pclMsg->m_clServerRankInfo);*/
}
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_PERSONAL_INFO(sPacketHeader *pPacket)
{
	/*sDBResponse_Server_Event_Personal_Info *pclMsg = (sDBResponse_Server_Event_Personal_Info*)pPacket;

	if(0 > pclMsg->m_siResult)
		return;

	pclServerEventManager->SetPersonalRank(pclMsg->m_clPersonalRankInfo);*/
}

void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_SERVER_BUF_KIND(sPacketHeader *pPacket)
{
	sDBResponse_Server_Event_Server_Buf_Kind *pclMsg = (sDBResponse_Server_Event_Server_Buf_Kind*)pPacket;

	if(0 > pclMsg->m_siResult)
		return;

	pclServerEventManager->SetBonusBufType(pclMsg->m_siServerBufKind);

	// 하루 동안 서버가 사용하는 버프를 알려줌.
	cltServerResponseValue clBufreturn(0, SRVAL_SERVER_EVENT_BUF, pclServerEventManager->GetBonusBufType(), 0);
	cltMsg clBuMsg(GAMEMSG_RESPONSE_SERVERRTN, sizeof(cltServerResponseValue), (BYTE*)&clBufreturn);
	pclCM->SendAllPersonMsg((sPacketHeader*)&clBuMsg);
}



// [영훈] 서버 이벤트 퀘스트 정보 저장 결과
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_SET( sPacketHeader *pPacket )
{
	if ( NULL == pPacket )
	{
		return;
	}
	
	sDBResponse_Server_Event_Server_Quest_Info_Set* pclMsg = (sDBResponse_Server_Event_Server_Quest_Info_Set*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

}

// [영훈] 서버 이벤트 퀘스트 정보 요청 결과
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_GET( sPacketHeader *pPacket )
{
	if ( NULL ==pPacket )
	{
		return;
	}

	sDBResponse_Server_Event_Server_Quest_Info_Get* pclMsg = (sDBResponse_Server_Event_Server_Quest_Info_Get*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	if ( 1 != pclMsg->m_siResult )
	{
		return;
	}

	CNServerEvent_Quest* pclSE_Quest = (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
	if ( NULL == pclSE_Quest )
	{
		return;
	}

	// 서버 유니크에 따른 퀘스트 데이터를 읽는다(현재 서버 UINQUE는 관계없음)
	pclSE_Quest->LoadQuestData( pclClient->siServerUnique );

	// 
	CNServerEvent_QuestData clSE_QuestData;

	clSE_QuestData.SetServerEvent_QuestData( 
		pclMsg->m_siEventType,
		pclMsg->m_siCondition1, 
		pclMsg->m_siCondition2, 
		pclMsg->m_siNeedClearAmount,
		pclMsg->m_siRewardItemUnique, 
		pclMsg->m_siRewardItemAmount, 
		pclMsg->m_siLimitMinute
	);

	pclSE_Quest->GetServerEnent_QuestData()->SetServerEvent_QuestData( &clSE_QuestData );
	pclSE_Quest->SetCharacterIndex(		pclMsg->m_siCharacterIndex );
	pclSE_Quest->SetCharacter(			pclMsg->m_bCharacter );
	pclSE_Quest->SetInFailCharacter(	pclMsg->m_siInFailCharacter );
	pclSE_Quest->SetNowAmount(			pclMsg->m_siNowAmount );
	// 이벤트 시작 시간을 설정한다
	pclSE_Quest->SetServerEventQuestColck( pclClient->CurrentClock );
	// 모든 데이터 설정이 끝났으므로 퀘스트 스타트 상태로 변경
	pclServerEventManager->SetServerEventState( SERVER_EVENT_STATE_START_QUEST );
}

// [영훈] 서버 이벤트 관련 개인 점수 요청 결과
void cltServer::DoMsg_DBMSG_RESPONSE_SERVER_EVENT_PERSON_SCORE_GET( sPacketHeader *pPacket )
{
	if ( NULL ==pPacket )
	{
		return;
	}

	sDBResponse_Server_Event_Server_Person_Score_Get* pclMsg = (sDBResponse_Server_Event_Server_Person_Score_Get*)pPacket;
	if ( NULL == pclMsg )
	{
		return;
	}

	SI32 siID		= pclMsg->m_uiCharID;
	SI32 siPersonID	= pclMsg->m_siPersonID;
	SI64 siScore	= pclMsg->m_siScore;

	// 유효한 아이디 인가?
	if ( false == pclCM->IsValidID(siID) )
	{
		return;
	}
	
	// 캐릭터 가져오기
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ siID ];
	if ( NULL == pclchar )
	{
		return;
	}
	
	// 혹시 Person ID가 다르다면
	if ( siPersonID != pclchar->pclCI->GetPersonID() )
	{
		return;
	}

	// 실제 점수 입력
	pclchar->siServerEvent_IndunScore = siScore;
}
void cltServer::DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_DEL(sPacketHeader* pPacket)
{
	sDBResponse_Question_Daily_Count_Del*	pclMsg = (sDBResponse_Question_Daily_Count_Del*)pPacket;
	
	for( SI32 Count = 0; Count < MAX_PERSON_NUMBER; ++Count )
	{
		cltCharServer* pclchar = pclCM->GetCharServer( Count );
		
		if(pclchar) 
			pclchar->m_uiDailyQuestionCount = 0;
	}	
}

void cltServer::DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_SET( sPacketHeader *pPacket )
{
	sDBResponse_Question_Daily_Count_Set* pclMsg = (sDBResponse_Question_Daily_Count_Set*)pPacket;
	if ( NULL == pclMsg )	return;

	cltCharServer* pclChar = pclCM->GetCharServer( pclMsg->m_siCharID );	
	if( NULL == pclChar ) return;

	pclChar->m_uiDailyQuestionCount = pclMsg->m_DailyCount;
}

void cltServer::DoMsg_DBMSG_RESPONSE_QUESTION_DAILY_COUNT_GET( sPacketHeader *pPacket )
{
	sDBResponse_Question_Daily_Count_Get* pclMsg = (sDBResponse_Question_Daily_Count_Get*)pPacket;
	if ( NULL == pclMsg )	return;

	cltCharServer* pclChar = pclCM->GetCharServer( pclMsg->m_siCharID );	
	if( NULL == pclChar ) return;

	pclChar->m_uiDailyQuestionCount = pclMsg->m_DailyCount;
}

void cltServer::DoMsg_DBMSG_RESPONSE_SETMUTETIME(sPacketHeader* pPacket)
{
	sDBResponse_SetMuteTime* pclMsg = (sDBResponse_SetMuteTime*)pPacket;
	if( NULL == pclMsg )			return;

	if( pclMsg->m_siResult != 1 )	return;

	SI32 siCharID = pclCM->GetIDFromPersonID( pclMsg->m_siTargetPersonID );
	if ( false == pclCM->IsValidID(siCharID) )
	{
		siCharID = 0;
	}

	cltCharServer* pclTargetChar = NULL;
	cltCharServer* pclMasterChar = NULL;

	if( pclCM->IsValidID(siCharID) )			pclTargetChar = pclCM->GetCharServer( siCharID );
	if( pclCM->IsValidID(pclMsg->m_uiCharID) )	pclMasterChar = pclCM->GetCharServer( pclMsg->m_uiCharID );

	// 마스터에게 메시지를 전송한다.
	if( pclMasterChar && pclTargetChar )
	{
		cltGameResponse_SetMute clMsgMuteMaster(pclTargetChar->GetName(), &pclMsg->m_stMuteTime, true);
		cltMsg clMsgMaster(GAMEMSG_RESPONSE_SETMUTE, sizeof(cltGameResponse_SetMute), (BYTE*)&clMsgMuteMaster);
		pclMasterChar->SendNetMsg((sPacketHeader*)&clMsgMaster);
	}

	// 채팅블록이 걸린 유저에게 결과를 알린다.
	if( pclTargetChar )
	{
		memcpy(&pclTargetChar->m_stMuteTime, &pclMsg->m_stMuteTime, sizeof(pclTargetChar->m_stMuteTime));

		cltGameResponse_SetMute clMsgMutePlayer(pclTargetChar->GetName(), &pclMsg->m_stMuteTime, false);
		cltMsg clMsgPlayer(GAMEMSG_RESPONSE_SETMUTE, sizeof(cltGameResponse_SetMute), (BYTE*)&clMsgMutePlayer);
		pclTargetChar->SendNetMsg((sPacketHeader*)&clMsgPlayer);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_GETMUTETIME(sPacketHeader* pPacket)
{
	sDBResponse_GetMuteTime* pclMsg = (sDBResponse_GetMuteTime*)pPacket;
	if( NULL == pclMsg )					return;

	if( pclMsg->m_siResult != 1 )			return;

	// 캐릭터 확인
	SI32 siCharID = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	if ( false == pclCM->IsValidID(siCharID) )
	{
		siCharID = 0;
	}
	if( pclMsg->m_uiCharID != siCharID )	return;

	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	memcpy(&pclchar->m_stMuteTime, &pclMsg->m_stMuteTime, sizeof(pclchar->m_stMuteTime));

	// 9999년도는 초기화된 값이다.
	if( pclchar->m_stMuteTime.wYear == 9999 )	{	ZeroMemory(&pclchar->m_stMuteTime, sizeof(pclchar->m_stMuteTime));	}

	// 채팅 제한 시간이 지나면 채팅 제한은 해제된다.
	if( pclchar->m_stMuteTime.wYear > 0 && TimeCompare(&sTime, &pclchar->m_stMuteTime) > 0 )
	{
		ZeroMemory(&pclchar->m_stMuteTime, sizeof(pclchar->m_stMuteTime));
	}

	if( pclchar->m_stMuteTime.wYear > 0 )
	{
		cltGameResponse_SetMute clMsgMutePlayer(pclchar->GetName(), &pclchar->m_stMuteTime, false);
		cltMsg clMsgPlayer(GAMEMSG_RESPONSE_SETMUTE, sizeof(cltGameResponse_SetMute), (BYTE*)&clMsgMutePlayer);
		pclchar->SendNetMsg((sPacketHeader*)&clMsgPlayer);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_ELIXIR_GET(sPacketHeader* pPacket)
{
	sDBResponse_Elixir_Get* pclMsg = (sDBResponse_Elixir_Get*)pPacket;
	if( NULL == pclMsg )							return;

	// 캐릭터 확인
	SI32 siCharID = pclCM->GetIDFromPersonID( pclMsg->m_siPersonID );
	if ( false == pclCM->IsValidID( siCharID ) )	return;

	if( pclMsg->m_uiCharID != siCharID )			return;

	cltCharServer* pclchar = pclCM->GetCharServer( siCharID );
	if ( NULL == pclchar )							return;

	// 서버에 캐릭터의 엘릭서 정보 세팅.
	pclchar->pcltElixir->SetEndMinuteVary	(  pclMsg->m_clElixirInfo.m_siEndMinuteVary	);	
	pclchar->pcltElixir->SetMultiple		(  pclMsg->m_clElixirInfo.m_uiMultiple		);
	pclchar->pcltElixir->SetPoint			(  pclMsg->m_clElixirInfo.m_siPoint			);		
	pclchar->pcltElixir->SetStr				(  pclMsg->m_clElixirInfo.m_siStr			);		
	pclchar->pcltElixir->SetDex				(  pclMsg->m_clElixirInfo.m_siDex			);		
	pclchar->pcltElixir->SetVit				(  pclMsg->m_clElixirInfo.m_siVit			);		
	pclchar->pcltElixir->SetMag				(  pclMsg->m_clElixirInfo.m_siMag			);		
	pclchar->pcltElixir->SetHnd				(  pclMsg->m_clElixirInfo.m_siHnd			);		
	pclchar->pcltElixir->SetWis				(  pclMsg->m_clElixirInfo.m_siWis			);		

	pclchar->bElixirSwitch = pclchar->pcltElixir->IsElixir();

	pclchar->SetParametaBoxAction( true );

	cltGameMsgResponse_Elixir_Set clInfo( pclchar->GetCharUnique(), &pclMsg->m_clElixirInfo );
	cltMsg clMsg(GAMEMSG_RESPONSE_ELIXIR_SET, sizeof(cltGameMsgResponse_Elixir_Set), (BYTE*)&clInfo);
	pclchar->SendNetMsg( (sPacketHeader*)&clMsg );
}



void cltServer::DoMsg_DBMSG_RESPONSE_ELIXIR_SET(sPacketHeader* pPacket)
{
	sDBResponse_Elixir_Set* pclMsg = (sDBResponse_Elixir_Set*)pPacket;
	if( NULL == pclMsg )							return;

	if( pclMsg->m_siResult != 1 )					return;

	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->m_uiCharID );
	if( NULL == pclchar )										return;
	if( pclchar->pclCI->GetPersonID() != pclMsg->m_siPersonID ) return;

	// 서버에 캐릭터의 엘릭서 정보 세팅.
	pclchar->pcltElixir->SetEndMinuteVary	(  pclMsg->m_clElixirInfo.m_siEndMinuteVary	);	
	pclchar->pcltElixir->SetMultiple		(  pclMsg->m_clElixirInfo.m_uiMultiple		);
	pclchar->pcltElixir->SetPoint			(  pclMsg->m_clElixirInfo.m_siPoint			);		
	pclchar->pcltElixir->SetStr				(  pclMsg->m_clElixirInfo.m_siStr			);		
	pclchar->pcltElixir->SetDex				(  pclMsg->m_clElixirInfo.m_siDex			);		
	pclchar->pcltElixir->SetVit				(  pclMsg->m_clElixirInfo.m_siVit			);		
	pclchar->pcltElixir->SetMag				(  pclMsg->m_clElixirInfo.m_siMag			);		
	pclchar->pcltElixir->SetHnd				(  pclMsg->m_clElixirInfo.m_siHnd			);		
	pclchar->pcltElixir->SetWis				(  pclMsg->m_clElixirInfo.m_siWis			);		

	pclchar->bElixirSwitch = pclchar->pcltElixir->IsElixir();

	pclchar->SetParametaBoxAction( true );

	cltGameMsgResponse_Elixir_Set clInfo( pclchar->GetCharUnique(), &pclMsg->m_clElixirInfo );
	cltMsg clMsg(GAMEMSG_RESPONSE_ELIXIR_SET, sizeof(cltGameMsgResponse_Elixir_Set), (BYTE*)&clInfo);
	pclchar->SendNeighbourMsg( &clMsg, true );

	// 소모하는 아이템이 있으면 소모시킨다.
	if( pclMsg->m_bUseItem )
	{
		if( 0 >= pclMsg->m_siElixirItemUnique )	return;	
		if( 0 >= pclMsg->m_siWaterItemUnique  )	return;	

		// 해당 위치의 아이템 유니크 확인.
		if( pclMsg->m_siElixirItemUnique != pclchar->pclCI->clCharItem.clItem[pclMsg->m_siElixirItemPos].siUnique ) return;
		if( pclMsg->m_siWaterItemUnique  != pclchar->pclCI->clCharItem.clItem[pclMsg->m_siWaterItemPos].siUnique  ) return;

		// 마력의 비약 사용량을 클라와 비교한다.
		SI32 siUseWaterNum = min( 10000, pclMsg->m_clElixirInfo.m_uiMultiple * pclchar->pclCI->clIP.GetLevel() * cltElixir::WATER_MILTIPLE );
		if( pclMsg->m_siWaterItemNum != siUseWaterNum ) return;

		cltItem clUseItem;
		clUseItem.Set( &pclchar->pclCI->clCharItem.clItem[pclMsg->m_siElixirItemPos] );
		clUseItem.siItemNum = 1;

		// 엘릭서 시작시 사용하는 아이템 제거.(엘릭서)
		sDBRequest_UseItem useitem1(	pclMsg->m_uiCharID,
										pclchar->pclCI->GetPersonID(),
										pclMsg->m_siElixirItemPos,
										&clUseItem, 
										USEITEM_REASON_ELIXIR_START_USE_ITEM	);

		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem1);


		// 엘릭서 시작시 사용하는 아이템 제거.(마력의 비약)
		cltItem clUseItem2;
		clUseItem2.Set( &pclchar->pclCI->clCharItem.clItem[pclMsg->m_siWaterItemPos] );
		clUseItem2.siItemNum = pclMsg->m_siWaterItemNum;

		sDBRequest_UseItem useitem2(	pclMsg->m_uiCharID,
										pclchar->pclCI->GetPersonID(),
										pclMsg->m_siWaterItemPos,
										&clUseItem2, 
										USEITEM_REASON_ELIXIR_START_USE_ITEM	);

		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem2);

		pclClient->pclLog->FilePrint( "config\\Elixir.log" , "[Elixir] : %d	[마력의 비약] : %d	[배수] : %d",  
																clUseItem.siItemNum,
																clUseItem2.siItemNum,
																pclMsg->m_clElixirInfo.m_uiMultiple	);
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_PROMOTER_INFO_GET(sPacketHeader* pPacket)
{
	sDBResponse_Promoter_Info_Get* pclMsg = (sDBResponse_Promoter_Info_Get*)pPacket;
	if( NULL == pclMsg )			return;

	if( pclMsg->m_siResult != 1 )	return;

	cltCharServer* pclChar = pclCM->GetCharServer( pclMsg->m_uiCharID );
	pclChar->pclCI->clBI.clRecommenderInfo.siPersonID = pclMsg->m_siPersonID;
		
	cltCharServer* pclchar = pclCM->GetCharServer( pclMsg->m_uiCharID );

	if( pclMsg->m_siPersonID )
	{
		bool bResult = true;
		// 기존에 목록에 있는지 체크
		cltSimplePerson* pSimplePersonInfo = NULL;
		for ( SI16 i = 0; i < MAX_FRIEND_NUMBER; ++i )
		{
			pSimplePersonInfo = &pclchar->pclFriendInfo->clFriend[i];

			if ( pSimplePersonInfo != NULL && pSimplePersonInfo->GetPersonID() > 0 )
			{
				if ( pSimplePersonInfo->GetName() != NULL && _tcscmp( pSimplePersonInfo->GetName(), pclMsg->m_szPromoterName ) == 0 )
				{
					// 친구 목록에 있으므로 추가할 필요 없음.
					bResult = false;
					break;
				}
			}
		}

		if( bResult )
		{
			sDBRequest_FriendAddList clMsg(	0, pclMsg->m_siPersonID, 0, pclMsg->m_szPromoterName, 
				0, pclchar->pclCI->GetPersonID(), (SI32)pclMsg->m_uiCharID, (TCHAR*)pclchar->GetName() );

			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
	}
}



//	여기서 부터 작업
void cltServer::DoMsg_DBMSG_RESPONSE_SETBALANCECANUSECURRENCY(sPacketHeader *pPacket)
{
	sDBResponse_SetBalanceCanUseCurrency *pclMsg = (sDBResponse_SetBalanceCanUseCurrency*)pPacket;
	if(pclMsg == NULL) 
		return;


	m_pclBalanceCurrencyMgr->SetCanUserMoney(pclMsg->m_siMoney);

	if(pclCM->IsValidID(pclMsg->m_siCharID)	== false)return ;
	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[pclMsg->m_siCharID];

	cltGameMsgResponse_BalanceCanUseCurrency cMsgBalanceCanUseCurrency(pclMsg->m_siMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_GETBALANCECANUSECURRENCY, sizeof(cltGameMsgResponse_BalanceCanUseCurrency), (BYTE*)&cMsgBalanceCanUseCurrency);

	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_DBMSG_RESPONSE_GETBALANCECANUSECURRENCY(sPacketHeader *pPacket)
{
	sDBResponse_GetBalanceCanUseCurrency *pclMsg = (sDBResponse_GetBalanceCanUseCurrency*)pPacket;
	
	if(pclMsg == NULL) 
		return;

	if(pclMsg->m_siResult != 1)
		return;

	m_pclBalanceCurrencyMgr->SetCanUserMoney(pclMsg->m_siMoney);

	if(pclMsg->m_siCharID > 0 && pclMsg->m_bCalledGM == true)
	{
		if(pclCM->IsValidID(pclMsg->m_siCharID)	== false)return ;
		if(pclCM->CR[pclMsg->m_siCharID]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)return ;


		//	GM이 현 통화량 조회를 요청했으므로 client에게 알려준다.
		cltGameMsgResponse_BalanceCanUseCurrency cMsgBalanceCanUseCurrency(pclMsg->m_siMoney, true);
		cltMsg clMsg(GAMEMSG_RESPONSE_GETBALANCECANUSECURRENCY, sizeof(cltGameMsgResponse_BalanceCanUseCurrency), (BYTE*)&cMsgBalanceCanUseCurrency);

		pclCM->CR[pclMsg->m_siCharID]->SendNetMsg((sPacketHeader*)&clMsg);

		//pclGameDBProcess->SendMsg((sPacketHeader*)&clMsg);
		
	}
}
// [성웅] 라쿤이벤트 군주 이벤트로 변경
void cltServer::DoMsg_DBMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO(sPacketHeader *pPacket)
{
	sDBResponse_GoonzuRaccoonEvent_SaveInfo *pclMsg = (sDBResponse_GoonzuRaccoonEvent_SaveInfo*)pPacket;

	if(pclMsg == NULL)				return;

	if(pclMsg->m_siResult != 1)		return;
	// 따로 특별한 일은 안한다
}
void cltServer::DoMsg_DBMSG_RESPONSE_GOONZURACCOONEVENT_GETINFO(sPacketHeader *pPacket)
{
	sDBResponse_GoonzuRaccoonEvent_GetInfo *pclMsg = (sDBResponse_GoonzuRaccoonEvent_GetInfo*)pPacket;

	if(pclMsg == NULL)				return;
	// 라쿤이벤트를 셋팅 한다.
	SI32 siSetCount =	0	;
	for (SI32 i = 0 ; i < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; i++ ) 
	{
		if (  i >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT) break;

		SI32 siTime = pclMsg->m_GoonzuRaccoonEventData[i].GetTime()	;
		SI32 siMonsterNum = pclMsg->m_GoonzuRaccoonEventData[i].GetMonsterNum()	;
		if(siTime < 0 || siTime > MAX_HOUR_GOONZURACCOONEVENT )	continue	;
		if(siMonsterNum <= 0 )	continue	;
		pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetTime(siTime)	;
		pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetMakeMonsterNum(siMonsterNum)	;
		siSetCount	=	0	;
		for ( SI32 siFiledIndex = 0 ; siFiledIndex < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ;siFiledIndex++ ) 
		{
			siSetCount++;
			if(siMonsterNum < siSetCount)	continue	;

			SI32 siMapindex = pclMsg->m_GoonzuRaccoonEventData[i].GetRocIndex(siFiledIndex)	;
			if(siMapindex <= 0  )	continue	;
			SI32 siX = pclMsg->m_GoonzuRaccoonEventData[i].GetRocX(siFiledIndex)	;
			SI32 siY = pclMsg->m_GoonzuRaccoonEventData[i].GetRocY(siFiledIndex)	;
			if ( siX < 0 || siY < 0   )
			{
				siX	=	0	;
				siY	=	0	;
			}				
			pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetMapIndex( siFiledIndex,  siMapindex)	;
			pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetMapRocX(siFiledIndex, siX)	;
			pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetMapRocY(siFiledIndex, siY)	;
		}
	}
}