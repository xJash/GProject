//---------------------------------
// 2003/9/18 
//---------------------------------���°�

#include "../Common/CommonHeader.h"
#include "../Server/Server.h"

#include "../Common/Map/Map.h"
#include "../Common/Ask/Ask.h"
#include "../Common/PartyMgr/PartyMgr.h"
#include "../Common/PartyMgr/PartyObj.h"
#include "../Common/Char/CharCommon/Char-Common.h"



#include "../Common/Order/Order.h"
#include "../common/AutoHunting/AutoHunting.h"
#include "../common/JWLib/IsCorrectID/IsCorrectID.h"

#include "../CommonLogic/BlackArmy/BlackArmy.h"
#include "../CommonLogic/WarRank/WarRank.h"

#include "Skill\Skill-Manager.h"
#include "Char\CharManager\CharManager.h"

#include "../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../DBManager/GameDBManager_World/DBMsg-System.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Person.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-CityHall.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"

#include "../Client/Interface/NPC1/NPCTradeBaseInfo.h"

#include "../Client/Interface/InvestmentDlg/InvestmentDlg.h"

#include "../Server/Event/GoonzuKingGuri/GoonzuKingGuri.h"



//-----------------------------------------
// Server
//-----------------------------------------
#include "Statistics/Statistics.h"

#include "MsgType-System.h"
#include "MsgType-Person.h"
#include "Msg/MsgType-ItemMall.h"
#include "MsgRval-Define.h"
#include "Msg/msgtype-party.h"

#include "Minister/MinisterBase.h"
#include "Minister/MinisterMgr.h"
#include "Minister/Minister-Hyungzo.h"
#include "Minister/Minister-Goonzu.h"

// APEX-
#include "../Apex/ApexGoonZu.h"
// -APEX

bool cltServer::CheckWarp( SI32 ID, SI32 MapIndex, SI32 DestX, SI32 DestY )
{
	if( pclCM->IsAlive( ID ) == FALSE ) 
		return false;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[ID];	
	if( NULL == pclChar )
		return false;

	if ( MapIndex < 0 || MapIndex >= MAX_MAP_NUMBER )
		return false;

	if ( pclMapManager->pclMapArray[MapIndex] == NULL ) 
		return false;

	// ���������� ���� �Ұ�. 
	if( pclChar->clInnerStatus.IsStatus(INNERSTATUS_PRISON) )
	{
		SendServerResponseMsg( 0, SRVAL_CAN_NOT_WARP_IN_PRISON, 0, 0, ID );
		return false;
	}

	if( pclMapManager->IsBlockWarp( MapIndex ) == true )
	{
		//���� ���� �޽��� : �� ���� ������ �����Ǿ��ֽ��ϴ�
		SendServerResponseMsg( 0,SRVAL_FAIL_WARP_BLOCKWARP,0,0, ID );
		return false;
	}

	// ���ڳ��� ������ �Ұ���
	if ( pclChar->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		 pclChar->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return false;
	}

	bool bVillageWarp = false ;

	if ( MapIndex > 0 && MapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage( MapIndex ) == true )
			bVillageWarp = true ;
		else 
			return false;
	}

	bool bNoLimitWarp = pclChar->pclCI->clBI.bUseNoLimitTicketWarp ;
	if ( pclChar->pclCI->clBI.siNoLimitTicketWarpDateVary < pclTime->clDate.GetDateVary() )
		bNoLimitWarp = false ;

	// �����̸� ������ ��¥
	if ( pclChar->pclCI->clBI.uiPoliceSwitch == 1 )
	{
		if( pclChar->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE(23490) )
		{
			bNoLimitWarp = true;
			//pclChar->DecreaseEquipDur(PERSONITEM_HAT, 5);
		}
	}

	// ��ȣõ���̸� ������ ��¥
	if ( pclChar->pclCI->clBI.uiAngelSwitch == 1 )
	{
		if(pclChar->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique == ITEMUNIQUE(23485))
		{
			bNoLimitWarp = true;
			//pclChar->DecreaseEquipDur(PERSONITEM_HAT, 5);
		}
	}

	// �����̸� ������ ��¥
	if ( pclChar->pclCI->clBI.uiGRank == GRANK_KING )
	{
		if(pclChar->pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23500) ||
			pclChar->pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23505) )
		{
			bNoLimitWarp = true;
		}
	}

	// ����̸� ������ ��¥
	if ( pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER1 ||
		 pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER2 ||
		 pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER3 || 
		 pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER4 ||
		 pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER5 ||
		 pclChar->pclCI->clBI.uiGRank == GRANK_MINISTER6 )
	{				
		if(pclChar->pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique == ITEMUNIQUE(23510) )		
		{
			bNoLimitWarp = true;
		}
	}


	// ��� ������ ���� ������ ���� ��� ������ ��¥
	if( pclChar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_LOVEPOWER ) && pclChar->pclCI->clBI.clBufInfo.IsHaveBuf( BUF_FRIENDSHIP ) )
	{
		bNoLimitWarp = true;
	}

	// pc���̸� ��¥
	if ( pclChar->pclCI->clBI.bPCRoom == true)
	{
		bNoLimitWarp = true;
	}

	// [����] ���ڴ� ���� : ���ڴ��̸� ������ ��¥ (2008. 06 .05)
	if (CONST_JOURNALIST_HAT_ITEMUNIQUE == pclChar->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique )
	{
		bNoLimitWarp = true;
	}

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;

	SI32 warpunique = 0 ;

	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);
	if ( itemNum <= 0 && !bNoLimitWarp )
		return false;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0 && !bNoLimitWarp )
		return false;

	if( true == pclChar->bPersonalShopSwitch ||
		true == pclChar->bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
			{
				if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, ID);
					return false;
				}
			}
		}
	}

	cltWarpInfo clWarpInfo(1, 0, false, true, x, y, -1, -1);

	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		if( pclMapManager->IsEnterLevel( MapIndex, pclChar->pclCI->clIP.GetLevel() ) == false )
			return false;

		const TCHAR * szMapName = pclMapManager->GetMapName( MapIndex );

		if ( MapIndex == MAPINDEX_BEGINNER1 && pclChar->pclCI->clIP.GetLevel() > 10 ) 
			return false;

		if (pclMapManager->pclGateManager->FindMainFieldPos( MapIndex, &x, &y ) == false )
			return false;

		if( siEnablePVP == 0 && pclMapManager->IsPkMap( MapIndex ) )
			return false;

		// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
		if( -1 == DestX && -1 == DestY )
		{
			clWarpInfo.uiMapIndex = 0;
			clWarpInfo.uiX = x+2;
			clWarpInfo.uiY = y+2;
		}
		else
		{
			clWarpInfo.uiMapIndex = MapIndex;
			clWarpInfo.uiX = DestX;
			clWarpInfo.uiY = DestY;
		}
		

		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[MapIndex]->siMapUnique;
		x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		if ( maptypeunique < 0 || x < 0 || y < 0 ) 
			return false;
		if( -1 == DestX && -1 == DestY )
		{
			clWarpInfo.uiMapIndex = MapIndex;
			clWarpInfo.uiX = x;
			clWarpInfo.uiY = y;
		}
		else
		{
			clWarpInfo.uiMapIndex = MapIndex;
			clWarpInfo.uiX = DestX;
			clWarpInfo.uiY = DestY;
		}

		warpunique = 2300 ;
	}
	
	if( bVillageWarp == true )
	{
		if(	pclVillageManager->IsAggressiveVillage( pclChar->pclCI->clBI.siHomeVillage , MapIndex ) ) 

		{
			SendServerResponseMsg(0, SRVAL_CAN_NOT_WARP_IN_VILLAGEWAR, 0, 0, ID);
			return false;
		}
	}

	OrderStop( pclChar->GetID(), BY_COMPUTER );

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
	cltGameMsgResponse_WarpEffect clinfo( pclChar->GetID() );
	cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNeighbourMsg(&clMsg, true);

	// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
	if( MapIndex < MAX_VILLAGE_NUMBER )
	{
		pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
	}
	// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
	else
	{
		pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
	}

	pclChar->SetWarpInfo(&clWarpInfo, warpunique);
	pclChar->Warp();

	if ( !bNoLimitWarp )
	{
		// ��踦 ����. 
		pclItemManager->AddUseNum(itemunique, 1);

		// ���ο� ��� - ������ ���
		//NStatistics_Add("Item", itemunique, "UseNum", 1);

		// �����̵��̿���� �Һ��Ѵ�.
		//////////////////////////////////////////////////////////////////////////
		cltItem clItem;
		clItem.Init();
		clItem.siUnique = itemunique;
		clItem.siItemNum = 1;

		SI32 FromPersonID = pclChar->pclCI->GetPersonID();
		sDBRequest_UseItem clMsg( ID, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//////////////////////////////////////////////////////////////////////////
	}

	return true;

}

// ���� ���/���� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_REGISTMASTER(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_RegistMaster* pclinfo = (cltGameMsgRequest_RegistMaster*)pclMsg->cData;
	
/*	// ����� ��ȿ���� Ȯ���Ѵ�. 
	if(pclinfo->siSkillUnique < 0 || pclinfo->siSkillUnique >= MAX_SKILL_NUMBER)return ;

	// �̹� ��ϵǾ� �ִ��� Ȯ���Ѵ�. 
	if(pclMasterManager->IsRegisterd(id, pclinfo->siSkillUnique) == true)
	{
		pclMasterManager->Unregist(id, pclinfo->siSkillUnique);
	}
	else
	{
		if(pclMasterManager->Regist(id, pclinfo->siSkillUnique) == true)
		{

		}
	}
*/
}

// ���� ��� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_SKILLMASTERLIST(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_SkillMasterList* pclinfo = (cltGameMsgRequest_SkillMasterList*)pclMsg->cData;

	// ����� ��ȿ���� Ȯ���Ѵ�. 
	if(pclinfo->siSkillUnique < 0 || pclinfo->siSkillUnique >= MAX_SKILL_NUMBER)return ;


	cltGameMsgResponse_SkillMasterList clinfo(pclinfo->siSkillUnique);

	for(SI32 i = 0; i < MAX_MASTER_PER_SKILL;i++)
	{
		SI32 charunique = pclMasterManager->clMasterInfo[pclinfo->siSkillUnique].clUnit[i].siCharUnique;

		if(charunique <= 0)continue;

		if(pclCM->IsValidID(charunique) == false)continue;

		if(pclMasterManager->clMasterInfo[pclinfo->siSkillUnique].clUnit[i].siSkillLevel < pclClient->pclSkillManager->GetMaxLevel(pclinfo->siSkillUnique)) continue;
		
		cltMasterUnitInfo clunit(charunique, (TCHAR*)pclCM->CR[charunique]->GetName(), 
			pclCM->CR[charunique]->pclCI->clBI.szAccountID,
			pclCM->CR[charunique]->pclCI->clCharSkill.GetTotalSkillLevel(pclinfo->siSkillUnique, 0, 0, &pclCM->CR[charunique]->pclCI->clCharItem.clItem[0]), 
			pclCM->CR[charunique]->clPB.clTotalBA.GetHnd(),
			pclCM->CR[charunique]->clPB.clTotalBA.GetLuk(),
			pclCM->CR[charunique]->pclCI->clBI.siHomeVillage,
			pclCM->CR[charunique]->pclCI->GetPersonID()
			);

		clinfo.Add(&clunit);
	}

	if(clinfo.siDataNum)
	{
		cltMsg clMsg(GAMEMSG_RESPONSE_SKILLMASTERLIST, clinfo.GetTotalSize(), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	
	// ���� ���� �̿��ڼ��� ������Ų��. 
	pclStatisticsManager->clDailyStatistics.siMasterInfoUseNumber ++;
	
	 

}


// ���� ���� ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_DELASK(cltMsg* pclMsg, SI32 id)
{
/*	cltGameMsgResponse_DelAsk* pclinfo = (cltGameMsgResponse_DelAsk*)pclMsg->cData;

	pclAskManager->DelAskPersonID(pclinfo->siPersonID);
*/


}

// ���� ����Ʈ ��û 
void cltServer::DoMsg_GAMEMSG_REQUEST_ASKLIST(cltMsg* pclMsg, SI32 id)
{
/*	SI32 i;
	cltGameMsgResponse_AskList clinfo;
	SI32 index = 0;

	for(i = 0;i < MAX_ASK_NUMBER;i++)
	{
		if(pclAskManager->clUnit[i].siCharUnique == 0)continue;

		SI32 askid = pclCM->GetIDFromCharUnique(pclAskManager->clUnit[i].siCharUnique);
		if(askid)
		{
			const TCHAR* pname = pclCM->CR[askid]->GetName();
			if(pname)
			{
				cltGameMsgResponse_AskListUnit clunit(pclAskManager->clUnit[i].siCharUnique, pclAskManager->clUnit[i].siPersonID, (TCHAR*)pname, pclAskManager->clUnit[i].szAskText);
				clinfo.clList[index].Set(&clunit);
				index++;
				if(index >= MAX_RESPONSE_ASK_LIST)
				{
					cltMsg clMsg(GAMEMSG_RESPONSE_ASKLIST, sizeof(clinfo), (BYTE*)&clinfo);
					pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
					index	= 0;
					clinfo.Init();
				}
			}
			
		}
	}

	if(index)
	{
		cltMsg clMsg(GAMEMSG_RESPONSE_ASKLIST, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	*/

}

// NPC ��ġ ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_NPCPOS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_NPCPos* pclinfo = (cltGameMsgRequest_NPCPos*)pclMsg->cData;

	SI32 i;
	SI16 mapnumber = 0;
	UI08 mapindexarray[MAX_MAP_NUMBER];

	//--------------------------------
	// kind�� SystemNPC���� Ȯ���Ѵ�. 
	//--------------------------------
	SI32 kind = pclinfo->siKind;
	if(kind <= 0 || kind >= MAX_KIND_NUMBER)return ;

	cltKindInfo* pclki = pclKindInfoSet->pclKI[kind];
	if(pclki == NULL)return ;

	if ( ConstServiceArea_China == pclClient->siServiceArea )
	{
		if(pclki->IsAtb(ATB_HIREABLE) == false)return ;
	}
	//if(pclki->IsAtb(ATB_SYSTEMNPC) == false)return ;

	//----------------------------------------------
	// ��ü ĳ���͸� �˻��Ͽ� �ش� kind�� ã�´�. 
	//----------------------------------------------
	SI32 npcid = 0;
	SI32 index = 0;
	while(npcid = pclCM->pclIDManager->GetCharOrder(index))
	{
		index++;

		if(pclCM->pclIDManager->IsValidID(npcid) )
		{
			if(pclCM->CR[npcid]->GetKind() == kind)
			{
				SI32 mapindex = pclCM->CR[npcid]->GetMapIndex();
				SI32 siSourceMapIndex = pclMapManager->GetSourceMap(mapindex);

				// Ŭ�и��� �߰����� �ʴ´�.
				if(siSourceMapIndex > 0)		continue;

				// �̹� Ȯ���� �ε������� Ȯ���Ѵ�. 
				bool balreadyswitch = false;
				for(i = 0; i < mapnumber;i++)
				{
					if( (i >= 0 && i < MAX_MAP_NUMBER) && mapindexarray[i] == mapindex )
					{
						balreadyswitch = true;
					}					
				}

				if(balreadyswitch == false)
				{
					if ( mapnumber >= 0 && mapnumber < MAX_MAP_NUMBER )
					{
						mapindexarray[mapnumber] = mapindex;
						mapnumber++;
					}
				}

			}
		}
	}
	
	//------------------------------------------
	// Ȯ���� �����͸� Ŭ���̾�Ʈ�� ������. 
	//-------------------------------------------
	//if(mapnumber <= 0)return ;

	cltGameMsgResponse_NPCPos clinfo(kind, mapnumber, mapindexarray);
	cltMsg clMsg(GAMEMSG_RESPONSE_NPCPOS, clinfo.GetTotalSize(), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


}
// Ŭ���̾�Ʈ�� ��Ʈ��Ʈ ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HEARTBEAT(cltMsg* pclMsg, SI32 id)
{
	// Ư���� ��ġ�� ������ ����. 

}

// �Ӹ� ����. (CharUnique)
void cltServer::DoMsg_GAMEMSG_REQUEST_SECRETCHAT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgSecretChat* pclInfo = (cltGameMsgSecretChat*)pclMsg->cData;
	
	TCHAR chatbuffer[ 256 ];

	memcpy( chatbuffer, pclInfo->szChatText, 256 );
	chatbuffer[ MAX_SECRET_CHAT_TEXT_LENGTH - 1 ] = NULL; 

	//-----------------------------------------------
	// ä�� ���ݿ� �����ϴ��� Ȯ�� 
	//-----------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(TABS(CurrentClock - pclchar->dwLastChatInputClock) < CHAT_INPUT_MIN_CLOCK)return ;


	//----------------------------------------------
	// �Ӹ��� ���ؾ� �� ��븦 Ȯ���Ѵ�.
	//----------------------------------------------
	bool bGameMaster = false;

	if (pclCM->CR[id]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
		bGameMaster = true;

	SI32 toid = pclCM->GetIDFromCharUnique(pclInfo->siCharUnique); 
	if( pclCM->IsValidID(toid) == false )
	{
		cltGameMsgResponse_SecretChatResult clResult(SECRETCHAT_FAIL_NOTUSER, TEXT("NULL"), pclInfo->siCharUnique );
		cltMsg clMsg( GAMEMSG_RESPONSE_SECRETCHATRESULT, 	sizeof(clResult), (BYTE*)&clResult);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	// �̸����� �ѹ� �� üũ���ش�.
	SI32 toid1 = pclCM->GetIDFromName( pclInfo->szCharName );
	if( pclCM->IsValidID(toid1) == false )
	{
		cltGameMsgResponse_SecretChatResult clResult( SECRETCHAT_FAIL_NOTUSER, TEXT("NULL"), pclInfo->siCharUnique );
		cltMsg clMsg( GAMEMSG_RESPONSE_SECRETCHATRESULT, 	sizeof(clResult), (BYTE*)&clResult);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	if( !IsPC( toid ) )
	{
		return ;
	}
	else
	{
		cltCharServer *pclChar = (cltCharServer *)pclCM->CR[toid];
		if (bGameMaster == false)	// tys
		{
			if ( pclChar->bWhisperChatReject )  
			{
				SendServerResponseMsg(0, SRVAL_WHISPERCHAT_REJECT,  0, 0, id);
				return;
			}

		}
	}

	//----------------------------------------------
	// �Ӹ��� ���Ѵ�. 
	//----------------------------------------------
	SI32 level = pclCM->CR[id]->pclCI->clIP.GetLevel();

	cltGameMsgResponse_Chat clChat(pclCM->CR[id]->GetCharUnique(), CHATMODE_SECRET, (TCHAR*)pclCM->CR[id]->GetName(), chatbuffer, bGameMaster,level);
	cltMsg clMsg(	GAMEMSG_RESPONSE_CHAT, 	clChat.siDataSize, (BYTE*)&clChat);
	
	if( pclCM->IsValidID(toid) )
		pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

	siChatCount_Private++;
}

// �Ӹ� ���� ��û  (PersonID)
void cltServer::DoMsg_GAMEMSG_REQUEST_MAKESECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_MakeSecretChatChannel* pclInfo = (cltGameMsgRequest_MakeSecretChatChannel*)pclMsg->cData;
	
	//-----------------------------------------------
	// ä�� ���ݿ� �����ϴ��� Ȯ�� 
	//-----------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if(TABS(CurrentClock - pclchar->dwLastChatInputClock) < CHAT_INPUT_MIN_CLOCK)return ;

	//----------------------------------------------
	// �Ӹ��� ���ؾ� �� ��븦 Ȯ���Ѵ�.
	//----------------------------------------------
	//charunique�� �ٰŷ� ������ ����� ã�´�. 
	SI32 toid = pclInfo->siCharUnique;
	if(toid <= 0)
	{
		// charunique�� ã�� ���ϸ� personid�� ã�´�. 
		toid = pclCM->GetIDFromPersonID(pclInfo->siPersonID);
		if ( _tcslen(pclInfo->szCharName) > 0 && pclInfo->szCharName != NULL && toid <= 0 )
			toid = pclCM->GetIDFromName(pclInfo->szCharName);
	}

	bool bGameMaster = false;

	SI32 level = 0 ;
	if(pclCM->IsValidID(toid))
	{
		level = pclCM->CR[toid]->pclCI->clIP.GetLevel() ;
		if ( level <= 0 || level > MAX_CHARACTER_LEVEL )	level = 0 ;

		if (pclCM->CR[toid]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL && pclCM->CR[toid]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
			bGameMaster = true;
	}

	if(pclCM->IsValidID(toid) && level != 0 )
	{
		if ( pclInfo->szChatBuffer )
		{
			 cltGameMsgResponse_MakeSecretChatChannel clinfo(bGameMaster, toid, level,(TCHAR*)pclCM->CR[toid]->GetName(), pclCM->CR[toid]->pclCI->clBI.szAccountID,pclInfo->szChatBuffer);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			cltGameMsgResponse_MakeSecretChatChannel clinfo(bGameMaster, toid, level,(TCHAR*)pclCM->CR[toid]->GetName(), pclCM->CR[toid]->pclCI->clBI.szAccountID, NULL);
			cltMsg clMsg(GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
	else
	{
		cltGameMsgResponse_MakeSecretChatChannel clinfo(false, 0,0, TEXT("NONAME"), TEXT("NONMAE"), NULL);
		cltMsg clMsg(GAMEMSG_RESPONSE_MAKESECRETCHATCHANNEL, 	sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}


}


void cltServer::DoMsg_GAMEMSG_REQUEST_ACCEPTSECRETCHATCHANNEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_AcceptSecretChatChannel* pclInfo = (cltGameMsgRequest_AcceptSecretChatChannel*)pclMsg->cData;

	
	//----------------------------------------------
	// �Ӹ� �¶�, �źθ� ���ؾ� �� ��븦 Ȯ���Ѵ�.
	//----------------------------------------------
	//charunique�� �ٰŷ� ������ ����� ã�´�. 
	
	SI32 toid = pclInfo->siCharUnique;

	if( pclCM->IsValidID(toid) )
	{
		if(pclInfo->bAccept)
		{
			cltGameMsgResponse_AcceptSecretChatChannel clinfo(pclInfo->bAccept,id, (TCHAR*)pclCM->CR[toid]->GetName());
			cltMsg clMsg(GAMEMSG_RESPONSE_ACCEPTSECRETCHATCHANNEL, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		else
		{
			cltGameMsgResponse_AcceptSecretChatChannel clinfo(pclInfo->bAccept,id, (TCHAR*)pclCM->CR[id]->GetName());
			cltMsg clMsg(GAMEMSG_RESPONSE_ACCEPTSECRETCHATCHANNEL, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}
// �Ӹ��� ������ ��û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HEADCHAT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HeadChat* pclinfo = (cltGameMsgRequest_HeadChat*)pclMsg->cData;

	if (pclCM->IsValidID(id) == false)
		return;

	//-----------------------------------------------
	// ä�� ���ݿ� �����ϴ��� Ȯ�� 
	//-----------------------------------------------
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if(TABS(CurrentClock - pclchar->dwLastChatInputClock) < CHAT_INPUT_MIN_CLOCK)return ;
	}

	SI32 chatid = pclCM->GetIDFromCharUnique(pclinfo->siCharUnique);
	if(pclCM->IsValidID(chatid) == false)return ;

	cltCharServer* pclchar = (cltCharServer* )pclCM->CR[chatid];
	if(pclchar->bHeadChatSwitch == false)	return ;
	if(pclchar->bPersonalShopSwitch== true)	return ;	// ���� ���� �߿��� ����â�� ����� ���Ѵ�.

	// �Ӹ��� �����͸� ������. 
	cltGameMsgResponse_HeadChat clinfo(pclinfo->siCharUnique, pclchar->szHeadChatText);
	cltMsg clMsg(GAMEMSG_RESPONSE_HEADCHAT, clinfo.GetTotalSize(), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHAT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Chat* pclinfo = (cltGameMsgRequest_Chat*)pclMsg->cData;

	TCHAR chatbuffer[ 256 ] = {'\0'};
	
	StringCchCopy( chatbuffer, 256, pclinfo->szChatText );

	if( pclCM->IsValidID(id) == false )		return;
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if( pclchar == NULL )					return;

	//---------------------------------------------
	// [����] ��Ʋ�ξ� ������̶�� 
	//---------------------------------------------
	if(NULL != m_pclBattleRoyalMgr)
	{
		CBattleRoyal* pclBattleRoyal = m_pclBattleRoyalMgr->GetBattleRoyal(pclchar);
		if( NULL != pclBattleRoyal)
		{
			if( TRUE == pclBattleRoyal->IsExistStadium(pclchar) )
			{
				switch( pclinfo->siChatMode )
				{
				case CHATMODE_SECRET:
				case CHATMODE_NORMAL:
				case CHATMODE_TOWN:
				case CHATMODE_GUILD:
				case CHATMODE_PARTY:
				case CHATMODE_NEWSITEM:
				case CHATMODE_HEAD:
					return;
				}
			}
		}
	}

//	memcpy( chatbuffer, pclinfo->szChatText, 256 );
//	chatbuffer[ 255 ] = NULL;

	if( chatbuffer[ 0 ] == NULL ) return;

	//KHY - 0108 - ���� �弳 ���͸� �߰�.
	bool bAbuseGameMaster	= false;
	bool bPlayerGM			= false ;

	if (pclCM->CR[id]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL)
		bAbuseGameMaster = true;

	if( pclCM->CR[id]->GetGameMasterLevel() < BASIC_PLAYERMASTER_LEVEL )
		bPlayerGM = true ;

	if(bAbuseGameMaster == true || bPlayerGM == true)
	{
#ifdef _IAF_EXPORT
		if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
		{
			if(!(chatbuffer[0] == '/'))
			{
				TCHAR ResultBuf[1024] = "";
				IAF::Filtering( chatbuffer, ResultBuf, sizeof(ResultBuf) );
				memcpy( chatbuffer, ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
			}
		}
#else
		// ���(PlayerGM����)�̰� "/"�� �����ϴ� �޽����� �弳���͸� ���� �ʴ´�.
		if(!(chatbuffer[0] == '/'))
			m_pCAbuseFilter->CheckAbuse(chatbuffer);
#endif
	}
	else
	{
#ifdef _IAF_EXPORT
		if( pclClient->IsWhereServiceArea(ConstServiceArea_USA) )
		{
			TCHAR ResultBuf[1024] = "";
			IAF::Filtering( chatbuffer, ResultBuf, sizeof(ResultBuf) );
			memcpy( chatbuffer, ResultBuf, strlen(ResultBuf) * sizeof(ResultBuf[0]) + 1 );
		}
#else
		//���޼��� �弳���� ����[����]
		m_pCAbuseFilter->CheckAbuse(chatbuffer);
#endif
	}

	// ��� ���� üũ�� ���� ����
	bool bGameMaster = false;
	
	if (pclCM->CR[id]->GetGameMasterLevel() >= BASIC_GAMEMASTER_LEVEL && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		bGameMaster = true;
	}

	//-----------------------------------------------
	// ä�� ���ݿ� �����ϴ��� Ȯ�� , �����ƿ� �ִ��� Ȯ��
	//-----------------------------------------------
	{
		cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
		if(TABS(CurrentClock - pclchar->dwLastChatInputClock) < CHAT_INPUT_MIN_CLOCK)return ;


		//------------------------------------------------
		//���������� ä�� �� ��Ÿ���� �Ұ�. 
		//------------------------------------------------

		if( pclchar->clInnerStatus.IsStatus(INNERSTATUS_PRISON))
		{
			SendServerResponseMsg(0, SRVAL_CAN_NOT_CHAT_IN_PRISON,  0, 0, id);
			return;
		}
	}
	



	SI32 toid = 0;		// �Ӹ� ����. (����Ʈ�� 0)
	TCHAR code[256];
	TCHAR szname[256] = TEXT("");

	//----------------------------------------
	// ���޵Ǿ� �� ä�� �޽����� Ȯ���Ѵ�. 
	//----------------------------------------
	TCHAR* pChatMsg =	chatbuffer;

	//----------------------------------------
	// ä�ú��
	//---------------------------------------
	if( pclinfo->siChatMode != CHATMODE_SYSTEM && pclchar->m_stMuteTime.wYear > 0)
	{
		cltGameResponse_SetMute clMsgMutePlayer(pclchar->GetName(), &pclchar->m_stMuteTime, false);
		cltMsg clMsgPlayer(GAMEMSG_RESPONSE_SETMUTE, sizeof(cltGameResponse_SetMute), (BYTE*)&clMsgMutePlayer);
		pclchar->SendNetMsg((sPacketHeader*)&clMsgPlayer);
	}

	//-----------------------------------------------------
	// �޽����� ������ '��ڸ��'���� Ȯ���Ͽ� ��ġ�Ѵ�. 
	//-----------------------------------------------------
	if(pChatMsg[0] == TEXT('/') )
	{
		// �Ӹ��̸�, 
		if((pChatMsg[1] == TEXT('t') && pChatMsg[2] == TEXT(' ')) 
			|| (pChatMsg[1] == TEXT('T')  && pChatMsg[2] == TEXT(' ')))
		{
			_stscanf(&pChatMsg[1], TEXT("%s %s"), code, szname);

			szname[ MAX_PLAYER_NAME - 1 ] = NULL;

			toid = pclCM->GetIDFromName(szname);

			if(toid == 0)
			{
				cltGameMsgResponse_SecretChatResult clResult(SECRETCHAT_FAIL_INVALIDNAME, szname);
				cltMsg clMsg(	GAMEMSG_RESPONSE_SECRETCHATRESULT, 	sizeof(clResult), (BYTE*)&clResult);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

				siChatCount_Private++;
				return ;
			}
			else
			{
				cltCharServer *pclChar = NULL;
				if( pclCM->IsValidID(toid) )	pclChar = (cltCharServer *)pclCM->CR[toid];
				// �Ӹ� �ź� ����
				if ( bGameMaster == false )
				{
					if ( pclChar != NULL && pclChar->bWhisperChatReject )
					{
						SendServerResponseMsg(0, SRVAL_WHISPERCHAT_REJECT,  0, 0, id);
						return;
					}
				}
			}
		}
		else if( (pChatMsg[1] == TEXT('p') && pChatMsg[2] == TEXT(' ')) 
			|| (pChatMsg[1] == TEXT('P') && pChatMsg[2] == TEXT(' ')) )
		{
			BOOL bCreateInvite = TRUE; // �⺻�� = ��Ƽ�����ʴ� 
			
			SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
			

			// ��Ƽ �ʴ��ѻ���� ��Ƽ���ε� ��Ƽ���� �ƴ϶�� �����޽����� �Բ� ��ȿ
            if(pclCM->CR[id]->siPartyIndex > 0)
			{
				if(pclPartyMgr->IsPartyLeader(FromPersonID, pclCM->CR[id]->siPartyIndex) == TRUE)
				{
					bCreateInvite = FALSE;
				}
				else
				{
					SendServerResponseMsg(0, SRVAL_PARTYINVITE_NOTLEADER,  0, 0, id);
					return;						
				}				
			}
			else // ��Ƽ �ʴ��� ����� ��Ƽ���� �ƴ϶�� ��Ƽ ���� �ʴ�� ����.
			{
				bCreateInvite = TRUE;
			}

			_stscanf(&pChatMsg[1], TEXT("%s %s"), code, szname);

			szname[ MAX_PLAYER_NAME - 1 ] = NULL;

			SI32 invitedID = pclCM->GetIDFromName(szname);

			if(pclCM->IsValidID(invitedID )== false)
			{
				SendServerResponseMsg(0, SRVAL_PARTYINVITE_NOTFINDNAME,  0, 0, id);
				return ;
			}
			else
			{
				cltCharServer *pclChar = NULL;
				if( pclCM->IsValidID(invitedID) )	pclChar = (cltCharServer *)pclCM->CR[invitedID];
				// ������ ��Ƽ �ź� ����
				if ( pclChar && pclChar->bPartyInviteReject )
				{
					SendServerResponseMsg(0, SRVAL_PARTYINVITE_REJECT,  0, 0, id);
					return;
				}
				// ������ �̹� ��Ƽ ��
				if ( pclCM->IsValidID(invitedID) && pclCM->CR[invitedID]->siPartyIndex > 0 )
				{
					// ������ �̹� ��Ƽ�� �޽��� to client
					SendServerResponseMsg(0, SRVAL_PARTYINVITE_ALREADYPARTY,  0, 0, id);
					return;
				}
				// �ڱ� �ڽ��� �ʴ��� ���̶��
				if( invitedID == id ) 
				{					
					return;
				}
				
				TCHAR * strCharName = (TCHAR*)pclCM->CR[id]->pclCI->clBI.GetName();
				if(strCharName == NULL) return;

				if(bCreateInvite == TRUE)
				{
					cltGameMsgResponse_Party_CreateInvite clGameMsgResponse_Party_CreateInvite( strCharName, FromPersonID);
					cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_CREATEINVITE, sizeof( clGameMsgResponse_Party_CreateInvite), (BYTE*)&clGameMsgResponse_Party_CreateInvite);
					if( pclCM->IsValidID(invitedID) )	pclCM->CR[invitedID]->SendNetMsg((sPacketHeader*)&clMsg);
				}
				else
				{
					cltGameMsgResponse_Party_Invite clGameMsgResponse_Party_Invite( strCharName, FromPersonID,pclCM->CR[id]->siPartyIndex );
					cltMsg clMsg(GAMEMSG_RESPONSE_PARTY_INVITE, sizeof( clGameMsgResponse_Party_Invite), (BYTE*)&clGameMsgResponse_Party_Invite);
					if( pclCM->IsValidID(invitedID) )	pclCM->CR[invitedID]->SendNetMsg((sPacketHeader*)&clMsg);
				}

			}
			return;
		}
		
		// ��� ����̸�, 
		else
		{
			if(OperateGameMasterOrder(pChatMsg, id) == false)
			{
				// ���� ���������� �˷��ش�				
				cltGameMsgResponse_Notice clNotice(TEXT("FAIL"), TEXT("Master Order Error"),true);
				cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
				pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );				
			}
			return ;
		}
		
		
	}

	//cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];


	//--------------------------------------
	// ä�� ������  �̿����� �뺸�Ѵ�.
	//--------------------------------------
	if(pclCM->IsValidID(toid))
	{
		TCHAR* ptext = &pChatMsg[1 + 1+ 1+ (_tcslen(szname) + 1)];

		cltGameMsgResponse_Chat clChat(pclchar->GetCharUnique(), CHATMODE_SECRET, (TCHAR*)pclchar->GetName(), ptext, bGameMaster);
		cltMsg clMsg(	GAMEMSG_RESPONSE_CHAT, 	clChat.siDataSize, (BYTE*)&clChat);

		pclCM->CR[toid]->SendNetMsg((sPacketHeader*)&clMsg);

		// �Ӹ� ä�� ������ �뺸�Ѵ�. 
		{
			cltGameMsgResponse_SecretChatResult clResult(SECRETCHAT_SUCCESS, szname);
			cltMsg clMsg(	GAMEMSG_RESPONSE_SECRETCHATRESULT, 	sizeof(clResult), (BYTE*)&clResult);
			pclchar->SendNetMsg((sPacketHeader*)&clMsg);
		}

		siChatCount_Private++;
	}
	else
	{
		// ���� ���� �����̸�, 
		if(pclinfo->siChatMode == CHATMODE_TOWN)
		{
			// �����ڰ� ������ ��������� �Ѵ�.
			if(pclchar->pclCI->clCharRank.siType != RANKTYPE_CITYHALL)
			{

				return ;
			}

			// �ش� ������ ������ ������. 
			SendNoticeMsg(pclchar->pclCI->clCharRank.siVillageUnique, 0, 0, pChatMsg);

		}
		// �ֹ� ��ο��� ����. 
		else if(pclinfo->siChatMode == CHATMODE_VILLAGER)
		{
			// �����ڰ� ������ ��������� �Ѵ�. 
			if(pclchar->pclCI->clCharRank.siType != RANKTYPE_CITYHALL)
			{
				return ;
			}

			// �ش� ������ ������ ������. 
			SendNoticeMsg(-1, pclchar->pclCI->clCharRank.siVillageUnique, 0, pChatMsg);
		}
		// �Ӹ����̸�, 
		else if(pclinfo->siChatMode == CHATMODE_HEAD)
		{
			// ���λ��� �����߿��� ����â�� ����� ���Ѵ�.
			if(pclchar->bPersonalShopSwitch == false)
			{
				// ĳ������ �Ӹ����� �����Ѵ�. 
				pclchar->SetHeadChat(true, pChatMsg);
				
				// �̿��鿡�� �Ӹ��� �����͸� ������. 
				cltGameMsgResponse_HeadChat clinfo(pclchar->GetCharUnique(), pChatMsg);
				cltMsg clMsg(GAMEMSG_RESPONSE_HEADCHAT, clinfo.GetTotalSize(), (BYTE*)&clinfo);
				pclchar->SendNeighbourMsg(&clMsg, true);
			}
		}
		// �ֹ� ä���̸�, 
		else if(pclinfo->siChatMode == CHATMODE_HOME)
		{
			if(pclchar->pclCI->clBI.siHomeVillage )
			{
				cltGameMsgResponse_Chat clChat(pclCM->CR[id]->GetCharUnique(), pclinfo->siChatMode, (TCHAR*)pclCM->CR[id]->GetName(), pChatMsg, bGameMaster);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, 	clChat.siDataSize, (BYTE*)&clChat);
				
				pclCM->SendAllPersonHomeMsg((sPacketHeader*)&clMsg, pclchar->pclCI->clBI.siHomeVillage);
			}
		}		
		else if ( pclinfo->siChatMode == CHATMODE_PARTY )
		{
			if ( pclCM->CR[id]->siPartyIndex > 0 )
			{
				CPartyObj *pTemp = pclPartyMgr->GetPartyObj( pclCM->CR[id]->siPartyIndex );

				if ( pTemp != NULL )
				{
					pTemp->SendPartyChat( pclCM->CR[id]->GetCharUnique(), (TCHAR*)pclCM->CR[id]->GetName(), pChatMsg );
				}
			}
		}
		else if ( pclinfo->siChatMode == CHATMODE_GUILD )
		{
			if ( pclCM->CR[id]->pclCI->clBI.clGuildRank.siType  > 0 
				&& pclCM->CR[id]->pclCI->clBI.clGuildRank.siType != GUILDRANKTYPE_STANDING 
				&& pclCM->CR[id]->pclCI->clBI.clGuildRank.uiConfirm != GUILDSTATUS_STANDING
				)
			{
				cltGameMsgResponse_Chat clChat(pclCM->CR[id]->GetCharUnique(), pclinfo->siChatMode, (TCHAR*)pclCM->CR[id]->GetName(), pChatMsg, bGameMaster);
				cltMsg clMsg(GAMEMSG_RESPONSE_CHAT, 	clChat.siDataSize, (BYTE*)&clChat);
				
				//KHY - 0131 - ��� ��� �޽��� ���� - �̸����� �˻� - ����ũ��ȣ �˻�����!
				pclCM->SendAllGuildMemberMsg((sPacketHeader*)&clMsg, pclchar->pclCI->clBI.clGuildRank.siGuildUnitIndex,pclchar->pclCI->clBI.clGuildRank.szGuildName);
			}
		}
		else if ( pclinfo->siChatMode == CHATMODE_KING )
		{
			if ( pclCM->CR[id]->pclCI->clBI.uiGRank == GRANK_KING )
			{
				cltGameMsgResponse_Notice clNotice((TCHAR*)pclCM->CR[id]->GetName(), pChatMsg,true);
				cltMsg clMsg(	GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
				pclCM->SendAllPersonMsg((sPacketHeader*)&clMsg);
			}
		}
		else if ( pclinfo->siChatMode == CHATMODE_NEWSITEM ) // �ڸ������
		{
			cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

			SI32 siTicketUnique = ITEMUNIQUE(24045) ; // �ڸ������̿�� 14130-> 24045

			// ����ڸ��̿���� �ִٸ� �켱������ �Ҹ��Ų��

			bool useColorNews = false;

			if( pclChar->pclCI->clCharItem.GetItemNum( ITEMUNIQUE(24047) ) > 0 )
			{	
				siTicketUnique = ITEMUNIQUE(24047);
				useColorNews = true;
			}

			if ( pclChar->pclCI->clCharItem.GetItemNum(siTicketUnique) <= 0 )
				return ;

			SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(siTicketUnique);
			if(pos < 0)return ;

            cltItem clitem;
			clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos]);
			clitem.SetItemNum(1);

			// ��踦 ����. 
			pclItemManager->AddUseNum(siTicketUnique, 1);

			// ���ο� ��� - ������ ���
			//NStatistics_Add("Item", siTicketUnique, "UseNum", 1);

			sDBRequest_NewsChatAddmission clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(),pos, &clitem, useColorNews ,pChatMsg);
			SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		}
		else
		{
			// �Ϲ� ä���̸� �Ӹ����� �����. 
			pclchar->SetHeadChat(false, NULL);

			cltGameMsgResponse_Chat clChat(pclCM->CR[id]->GetCharUnique(),
				pclinfo->siChatMode, (TCHAR*)pclCM->CR[id]->GetName(), pChatMsg,bGameMaster, 0,pclinfo->siSystemTxt);
			cltMsg clMsg(	GAMEMSG_RESPONSE_CHAT, 	clChat.siDataSize, (BYTE*)&clChat);
			
			cltCharServer* pclchar = ((cltCharServer*)pclCM->CR[id]);
			pclchar->SendNeighbourMsg(&clMsg, true);

			SI32 siSummonID = pclchar->GetSummonID();

			if( pclCM->IsValidID(siSummonID) )
			{
				cltSummon* pclSummon = pclchar->pclCI->clSummonInfo.GetSummon(pclCM->CR[siSummonID]->GetSummonIndex());
				if( pclSummon )
				{
					SI16 siAniType = pclKindInfoSet->GetAnitypeFromText(pChatMsg, pclSummon->siKind, pclSummon->clIP.GetLevel() );
					if( siAniType > 0 )
					{
						cltKindInfo* pclKI	= NULL;
						if(pclClient->IsCountrySwitch(Switch_Summon_Separate)) 
						{	pclKI = pclClient->pclKindInfoSet->pclSummonKI[ pclSummon->siKind ];		}
						else
						{	pclKI = pclClient->pclKindInfoSet->pclKI[ pclSummon->siKind ];				}

						SI32 aniref	= pclKI->clCharAniManager.FindRefFromAnitype(siAniType);
						if( aniref >= 0 )
						{
							if( pclCM->CR[siSummonID]->GetCurrentOrder() != ORDER_SPECIAL_ACTION )
							{
								OrderSpecialAction(siSummonID, siAniType, BY_PLAYER);
							}
							else
							{
								int a = 0;
							}
						}
					}
				}
			}

			siChatCount_General++;
		}
	}

	//--------------------------------------
	// ä�� ȸ�� ��� 
	//--------------------------------------
	pclStatisticsManager->clDailyStatistics.siChatNumber++;

}

// ���� ���� ��� �뺸. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HOPETOQUIT(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->IsValidID(id) == false)
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// ������̸� �� ������.
	// pvp ���̸� ������ ����
	if ( pclchar->IsAutoHunting() || pclchar->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP  ) )
	{
		SendServerResponseMsg(0, SRVAL_NO_BATTLEQUIT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	// �ǰ� 0, �׾��ٸ� �� ������.
	if ( pclchar->pclCI->clIP.GetLife() <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_NO_DIEQUIT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

// APEX-
#ifdef _CHINA
	NoticeApexProxy_UserLogout( id, pclchar->pclCI->clBI.szAccountID );
	pclchar->bApexLogin = false;
#endif
	// -APEX

#ifdef USE_GAME_GUARD_SERVER
	pclchar->CCSAuthClose();
#endif	

	pclchar->bHopeToQuitSwitch = true;

	//KHY - 0905 - �α�. �α׾ƿ�.
	SendLog_WriteLogToDB(LOGCOMMAND_TYPE_LOGIN, LOGCOMMAND_INDEX_LOGOUT, 
		0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL);

	cltMsg clMsg(GAMEMSG_RESPONSE_HOPETOQUIT, 0, NULL);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

// ����Ʈ�� �ǵ��ư��� ���
void cltServer::DoMsg_GAMEMSG_REQUEST_HOPETOFRONT(cltMsg* pclMsg,SI32 id)
{
	if(pclCM->IsValidID(id) == false)
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// ������̸� �� ������.
	// pvp ���̸� ����������.
	if ( pclchar->IsAutoHunting() || pclchar->clInnerStatus.clEnemyType.IsType( ENEMYTYPE_PVP  ))
	{
		SendServerResponseMsg(0, SRVAL_NO_BATTLEQUIT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	// �ǰ� 0, �׾��ٸ� �� ������.
	if ( pclchar->pclCI->clIP.GetLife() <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_NO_DIEQUIT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// APEX-
#ifdef _CHINA
	NoticeApexProxy_UserLogout( id, pclchar->pclCI->clBI.szAccountID );
	pclchar->bApexLogin = false;
#endif
	// -APEX


#ifdef USE_GAME_GUARD_SERVER
	pclchar->CCSAuthClose();
#endif	

	pclchar->bHopeToQuitSwitch = true;

	cltMsg clMsg(GAMEMSG_RESPONSE_HOPETOFRONT, 0, NULL);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

// �ش� ������ Warp�� ����� 
void cltServer::DoMsg_GAMEMSG_REQUEST_WARPVILLAGE(cltMsg* pclMsg, SI32 id)
{
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_RESIDENTWARPVILLAGE(cltMsg* pclMsg, SI32 id)
{

	if( pclCM->IsAlive(id) == false )return ;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if( pclchar->CanWarpFrom() == false )		return;

	SI32 villageunique = pclMsg->siData32[0];
	if(villageunique<=0 || villageunique >= MAX_VILLAGE_NUMBER)	return;

	//if( pclchar->CanWarpFrom() == false)						return; // 3�� Ÿ�̸� üũ�� 3�� �޼����� ��� �ؼ� ��µǹǷ� ����.

	// ���� �ֹ�����... ������ ������ �´��� Ȯ��
	if ( pclCM->CR[id]->pclCI->clBI.siHomeVillage < 1 || pclCM->CR[id]->pclCI->clBI.siHomeVillage != villageunique )
	{
		return;
	}

	SI32 ticketunique = 24000;	// �����̵� �̿������ ����ũ ���� kkm 2007 / 09 / 26
	SI32 ticketpos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos(ticketunique);
	if(ticketpos < 0)return;

	pclItemManager->AddUseNum(ticketunique, 1);

	// ���ο� ��� - ������ ���
	//NStatistics_Add("Item", ticketunique, "UseNum", 1);

	// DB�� ��û�Ѵ�. 
	sDBRequest_WarpVillage clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), ticketpos, ticketunique, 1, villageunique);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}


// �����Ǽ� 

void cltServer::DoMsg_GAMEMSG_REQUEST_GETBYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����Ѵ�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_BYUNGZO);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETGONGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����Ѵ�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_GONGZO);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETHYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����Ѵ�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_HYUNGZO);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETHOZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����Ѵ�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_HOZO);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETIZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����Ѵ�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_IZO);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETYEZOINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����ش�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_YEZO);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETGOONZUINFO(cltMsg* pclMsg, SI32 id)
{
	// �ڽ��� ���� �ִ� ������ �����ش�.
	if(pclCM->IsAlive(id) == false)return ;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_GetMinisterInfo(id, MINISTER_GOONZU);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETBYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER4) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_BYUNGZO);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETBYUNGZOINFO_VILLAGEWARINFO(cltMsg* pclMsg, SI32 id)
{
	//DB�� ������ �ð����� �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER4) return;
	if(bVillageWarSwitch == true)	return;

	cltGameMsgRequest_SetByungzoInfoVillageWarTime * pclinfo = (cltGameMsgRequest_SetByungzoInfoVillageWarTime*)pclMsg->cData;

	sDBRequest_SetByungzoInfo_VillageWarTime clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(),
		pclinfo->szGreeting,
		pclinfo->siVillageWarTime );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SETGONGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER6) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_GONGZO);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETHYUNGZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER5) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_HYUNGZO);

}

// �����Ǽ��� �˼��� �����Ѵ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_SETHYUNGZOPRISON(cltMsg* pclMsg , SI32 id)
{
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER5) return;
	if(bVillageWarSwitch == true)	return;

	if ( pclMinisterMgr )
	{
		CMinisterHyungzo *pclHyungzo = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

		if ( pclHyungzo == NULL ) return ;
		pclHyungzo->DoMsg_GameMsgRequest_SetHyungPrison(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETHOZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// ȣ���Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER2) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_HOZO);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETIZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ִ�.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER1) return;
	

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_IZO);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETYEZOINFO(cltMsg* pclMsg, SI32 id)
{
	// DB�� ������ �����Ѵ�.
	// �����Ǽ����� �Ҽ� �ְ� ������ �ð����� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER3) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_YEZO);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETGOONZUINFO(cltMsg* pclMsg, SI32 id)
{
	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_KING) return;
	if(bVillageWarSwitch == true)	return;

	if(pclMinisterMgr)	pclMinisterMgr->DoMsg_GameMsgRequest_SetMinisterInfo(pclMsg, id, MINISTER_GOONZU);
}
// ä��â �޼��� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_CHAR_OPTION(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}
	cltGameMsgRequest_Char_Option* pclinfo = (cltGameMsgRequest_Char_Option *)pclMsg->cData;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	pclCM->CR[id]->pclCI->clCharOption.Set( &pclinfo->clCharOptionInfo/*pclChar->pclCI->clCharOption*/ ) ;//������ �����ϰ�

	sDBRequest_Char_Option clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(),pclinfo->clCharOptionInfo/*pclChar->pclCI->clCharOption*/ );//������.
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	//cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	//pclChar->bChatSetNormal = pclinfo->bChatSetNormal;

	return;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_REJECT(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_WhisperChat_Reject* pclinfo = (cltGameMsgRequest_WhisperChat_Reject *)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	pclChar->bWhisperChatReject = pclinfo->bWhisperChatReject;
	
	return;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_PRIVATETRADE_REJECT(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_PrivateTrade_Reject* pclinfo = (cltGameMsgRequest_PrivateTrade_Reject *)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	pclChar->bPrivateTradeReject = pclinfo->bPrivateTradeReject;
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYINVITE_REJECT( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_PartyInvite_Reject* pclinfo = (cltGameMsgRequest_PartyInvite_Reject *)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	pclChar->bPartyInviteReject = pclinfo->bPartyInviteReject;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDADD_REJECT( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltGameMsgRequest_FriendAdd_Reject* pclinfo = (cltGameMsgRequest_FriendAdd_Reject *)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	pclChar->bFriendAddReject = pclinfo->bFriendAddReject;

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INITSTATUS(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}
	
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	//[����] ĳ���� ���� �ʱ�ȭ �����Ⱓ���� ������ ���. 
	if( pclEventTimeManager->InEventTime("char_ability_init", &sTime) )
	{
		cltItem clitem; 
		clitem.Init();
		
		sDBRequest_InitStatus clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), 0, 0, &clitem);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		{
			// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
			if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
			{
				cltElixir_Info  clElixirInfo;
				clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
				clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
				clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();
				
				if(pclChar->pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}
		return;
	}
	// ����� �̿�� �̿ܿ� ����� ������ 10 �Ǵ� 30�� �Ǹ� �������ͽ� �ʱ�ȭ�� �Ѵ�.
	if (pclCM->CR[id]->pclCI->clIP.GetLevel() == INIT_LEVEL)
	{
		sDBRequest_InitStatus clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID() , INITSTATUSMODE_LEVEL_10 , 0 , NULL );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		{
			// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
			if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
			{
				cltElixir_Info  clElixirInfo;
				clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
				clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
				clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

				if(pclChar->pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}

		return;
	}
	else if (pclCM->CR[id]->pclCI->clIP.GetLevel() == INIT_LEVEL_SECOND)
	{
		sDBRequest_InitStatus clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID() , INITSTATUSMODE_LEVEL_30 , 0 , NULL );
		pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		{
			// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
			if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
			{
				cltElixir_Info  clElixirInfo;
				clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
				clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
				clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

				if(pclChar->pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}

		return;
		//if( ConstServiceArea_China == siServiceArea )
		//{
		//}
		//else
		//{
		//	sDBRequest_InitStatus clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID() , INITSTATUSMODE_LEVEL_30 , 0 , NULL );
		//	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		//	if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		//	{
		//		// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
		//		if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
		//		{
		//			cltElixir_Info  clElixirInfo;
		//			clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
		//			clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
		//			clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

		//			if(pclChar->pclCI->GetPersonID() > 0)
		//			{
		//				sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
		//				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//			}
		//			else
		//				pclClient->pclLog->FilePrint(TEXT("Config\\Elixir_Error.log"), TEXT("cltServer.DoMsg_GAMEMSG_REQUEST_INITSTATUS  - 1633 Line -> [PersonID : 0]"));
		//		}
		//	}

		//	return;
		//}
	}

	SI32 itemunique1		= ITEMUNIQUE(24030);	// �����ʱ�ȭ�̿��
	SI32 itemunique2		= ITEMUNIQUE(24031);	// �߱��̺�Ʈ �����ʱ�ȭ�̿��
	SI32 siEventItemUnique	= ITEMUNIQUE(24125);	// [��ȣ] �����ʱ�ȭ�̿��(�̺�Ʈ) �ѱ��̰��� ����
	SI32 pos1 = -1;

	if( pclClient->IsWhereServiceArea(ConstServiceArea_China | ConstServiceArea_Taiwan) )
	{
		if ( pclChar->pclCI->clCharItem.GetItemNum(itemunique1) <= 0 &&
			pclChar->pclCI->clCharItem.GetItemNum(itemunique2) <= 0 )
			return ;

		pos1 = pclChar->pclCI->clCharItem.GetItemPos(itemunique2);
		if( pos1 < 0 )
		{	
			pos1 = pclChar->pclCI->clCharItem.GetItemPos(itemunique1);
			if( pos1 < 0 )
				return ;
		}
	}
	else
	{
		if ( pclChar->pclCI->clCharItem.GetItemNum(itemunique1) <= 0 && pclChar->pclCI->clCharItem.GetItemNum(siEventItemUnique) <= 0)
			return ;


		pos1 = pclChar->pclCI->clCharItem.GetItemPos(siEventItemUnique);	// �̺�Ʈ�� �ʱ�ȭ�̿�� ���� �˻�
		if( pos1 < 0 )
		{
			pos1 = pclChar->pclCI->clCharItem.GetItemPos(itemunique1);		// �̺�Ʈ�� �ʱ�ȭ�̿���� ���ٸ� �⺻ �ʱ�ȭ�̿�� �˻�
			if( pos1 < 0 )													// �Ѵ� ���ٸ� return
				return ;														
		}
	}

	// ��� �����Ǿ��ִ��� �˻��Ѵ�.
	for ( SI16 i=0 ; i<PERSONITEM_RESERVED1 ; i++ )
	{
		if ( i == PERSONITEM_BAG || i == PERSONITEM_BAG_SUB )
			continue;

		if ( pclChar->pclCI->clCharItem.clItem[i].siUnique != 0 )
		{
			return;
		}
	}

	//------------------------------------
	// �������ͽ��� �ʱ�ȭ�Ѵ�.
	//------------------------------------
	cltItem clitem;
	clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos1]);
	clitem.SetItemNum(1);

	if( ITEMUNIQUE(24031) == pclChar->pclCI->clCharItem.clItem[pos1].siUnique )
	{
		sDBRequest_InitStatus clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), INITSTATUSMODE_CHINA_EVENTTICKET, pos1, &clitem);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		{
			// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
			if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
			{
				cltElixir_Info  clElixirInfo;
				clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
				clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
				clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

				if(pclChar->pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}
	}
	else
	{
		sDBRequest_InitStatus clMsg(pclChar->GetID(), pclChar->pclCI->GetPersonID(), INITSTATUSMODE_TICKET, pos1, &clitem);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		if( pclClient->IsCountrySwitch( Switch_Elixir ) )
		{
			// �������ͽ� �ʱ�ȭ�� �������� ���� �ʱ�ȭ ��Ų��.
			if( pclChar->pcltElixir && pclChar->pcltElixir->IsElixir() ) 
			{
				cltElixir_Info  clElixirInfo;
				clElixirInfo.m_siEndMinuteVary	= pclChar->pcltElixir->GetMinuteVary();
				clElixirInfo.m_uiMultiple 		= pclChar->pcltElixir->GetMultiple();
				clElixirInfo.m_siPoint	  		= pclChar->pcltElixir->GetTotalPoint();

				if(pclChar->pclCI->GetPersonID() > 0)
				{
					sDBRequest_Elixir_Set clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), &clElixirInfo );
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
				}
			}
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_CREATE(cltMsg* pclMsg, SI32 id)
{
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_INVITE(cltMsg* pclMsg, SI32 id)
{
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_USERLIST(cltMsg* pclMsg, SI32 id)
{
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WHISPERCHAT_OUT(cltMsg* pclMsg, SI32 id)
{
	return;
}

// ��ڰ� ������� �α׸� ��û�Ѵ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONAL_LOG(cltMsg* pclMsg, SI32 id)
{
	/*
	cltGameMsgRequest_Personal_Log* pclinfo = (cltGameMsgRequest_Personal_Log*)pclMsg->cData;

	if ( id <= 0 ) return ;
	if ( pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL + 1 ) return ;
	
	if ( pclinfo->siLogType < 0 ) return ;

	if ( _tcslen(pclinfo->szServerName) <= 0 || _tcslen(pclinfo->szServerName) > MAX_DBLOG_SIZE_SERVERNAME )
		return ;
	if ( _tcslen(pclinfo->szPersonName) <= 0 || _tcslen(pclinfo->szPersonName) > MAX_PLAYER_NAME )
		return ;
	if ( _tcslen(pclinfo->szDate) <= 0 || _tcslen(pclinfo->szDate) > MAX_DBLOG_SIZE_DATE )
		return ;
	if ( _tcslen(pclinfo->szStartTime) <= 0 || _tcslen(pclinfo->szStartTime) > MAX_DBLOG_SIZE_DATE )
		return ;
	if ( _tcslen(pclinfo->szEndTime) <= 0 || _tcslen(pclinfo->szEndTime) > MAX_DBLOG_SIZE_DATE )
		return ;

	TCHAR startdate[MAX_DBLOG_SIZE_DATE] = TEXT("");
	TCHAR starttime[MAX_DBLOG_SIZE_DATE] = TEXT("") ;
	TCHAR enddate[MAX_DBLOG_SIZE_DATE] = TEXT("") ;
	TCHAR endtime[MAX_DBLOG_SIZE_DATE] = TEXT("") ;

	StringCchCopy(startdate, MAX_DBLOG_SIZE_DATE,pclinfo->szDate);
	StringCchCopy(enddate, MAX_DBLOG_SIZE_DATE,pclinfo->szDate);

	StringCchCat(startdate, MAX_DBLOG_SIZE_DATE, TEXT(" "));
	StringCchCat(startdate, MAX_DBLOG_SIZE_DATE, pclinfo->szStartTime);

	StringCchCat(enddate, MAX_DBLOG_SIZE_DATE, TEXT(" "));
	StringCchCat(enddate, MAX_DBLOG_SIZE_DATE, pclinfo->szEndTime);

	if ( _tcslen(startdate) > MAX_DBLOG_SIZE_DATE || _tcslen(enddate) > MAX_DBLOG_SIZE_DATE )
		return ;

	sDBRequest_Personal_Log clMsg(id,pclinfo->siLogType,pclinfo->szServerName,pclinfo->szPersonName,pclinfo->siItemUnique,startdate,enddate);
	pclLogDBProcess->SendMsg((sPacketHeader *)&clMsg);
	*/

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INVESTMENTGETINFO(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_InvestmentGetInfo* pclInfo = (cltGameMsgRequest_InvestmentGetInfo*)pclMsg->cData;

	if ( id <= 0 ) return ;

	SI32 NPCCharUnique = pclInfo->siNPCCharUnique;
	if ( NPCCharUnique <= 0 ) return ;

	SI32 NPCID = pclCM->GetIDFromCharUnique( NPCCharUnique ) ;

	if ( NPCID <= 0 ) return ;

	if ( pclCM->IsValidID( NPCID ) == false ) return ;

	SI32 villageunique = pclCM->CR[NPCID]->GetCurrentVillageUnique();

	if ( villageunique < 0 || villageunique > CUR_VILLAGE_LIMIT ) return ;

	GMONEY money = pclCM->CR[id]->pclCI->clIP.GetMoney();

	if ( money < 10000 ) return ;

	// ���� ���δ�
	{
		SI32 changmoney = INVESTMENT_GETINFO_MONEY ;
		sDBRequest_ChangeMoney clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_INVESTMENTINFO, -changmoney);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

		pclDelMoneyStatistics->Add(DELMONEY_TAX, changmoney);

		// ��ȭ�� ���� 
		cltMoney clmoney;
		clmoney.Set(changmoney/2);
		clCurrencyInfo.clOutputMoney_NPC.Increase(&clmoney);
	}
	// ������ 5000���� �߰��Ѵ�.
	if( villageunique > 0 && villageunique < MAX_VILLAGE_NUMBER)
	{
		sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, villageunique, VILLAGE_PROFIT_FOR_INVESTMENT );
		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
	}

#ifdef _SAFE_MEMORY
	cltGameMsgResponse_InvestmentGetInfo clinfo(&pclItemManager->stInvestmentLines[0]);
#else
	cltGameMsgResponse_InvestmentGetInfo clinfo(pclItemManager->stInvestmentLines);
#endif
	cltMsg clMsg(GAMEMSG_RESPONSE_INVESTMENTGETINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HUNTMAPWARP(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_HuntMapWarp* pclInfo = (cltGameMsgRequest_HuntMapWarp*)pclMsg->cData;

	if( pclCM->IsAlive( id ) == false )											return;
	if( pclInfo->siMapIndex <= 0 || pclInfo->siMapIndex >= MAX_MAP_NUMBER )		return;
	if( pclMapManager->pclMapArray[pclInfo->siMapIndex] == NULL )				return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}
	
	// ĳ������ ���¿� ���� ������ �Ұ����ϴ�.
	if( pclChar->CanWarpFrom() == false )						return;
	
	// ���� �ϰ��� �ϴ� �ʿ� ���� ������ �Ұ����ϴ�.
	if( pclChar->CanWarpTo( pclInfo->siMapIndex ) == false )	return;

	// ��¥���� ���� ����
	bool bNoLimitWarp = pclChar->CanFreeWarp( pclInfo->siMapIndex );


	// ������ �����ΰ�?
	bool bVillageWarp = false;
	if ( pclInfo->siMapIndex > 0 && pclInfo->siMapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclInfo->siMapIndex) == true )
			bVillageWarp = true;
		else
			return ;
	}

	if( bVillageWarp == true)
	{
		if( pclVillageManager->IsAggressiveVillage( pclChar->pclCI->clBI.siHomeVillage, pclInfo->siMapIndex ) )
		{
			SendServerResponseMsg(0, SRVAL_CAN_NOT_WARP_IN_VILLAGEWAR, 0, 0, id);
			return;
		}
	}

	SI32 siWarpMode = HUNTMAPWARP_MODE_NONE;
	if( pclInfo->siWMoney == 0 )
	{
		siWarpMode = HUNTMAPWARP_MODE_USEITEM;
	}
	else
	{
		siWarpMode = HUNTMAPWARP_MODE_USEMONEY;
	}

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;
	SI32 warpunique = 0 ;

	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);
	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);

	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
	if(siWarpMode == HUNTMAPWARP_MODE_USEITEM) //����Ƽ������ ��ȯ�̶��.
	{
		// ��¥�̵��� �ƴѵ�, �������� ���ٸ� �̵� �Ұ���
		if( bNoLimitWarp == false )
		{
			if ( itemNum <= 0 || pos < 0 )		return ;
		}

		// ������ �ִ� �������� ����� �� ����.
		if( true == pclChar->bPersonalShopSwitch ||
			true == pclChar->bPremiumPersonalShop )
		{
			for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
			{
				if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
				{
					if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
					{
						SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
						return;
					}
				}
			}
		}
	}
	else if( siWarpMode == HUNTMAPWARP_MODE_USEMONEY )
	{
		GMONEY myMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();
		// �����ݺ��� ���� �ݾ��� ������ ������ �� ����.
		if( myMoney < pclInfo->siWMoney )
			return;
	}
	
	cltWarpInfo clWarpInfo(1, 0, false, true, x, y, -1, -1);
	
	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		const TCHAR * szMapName = pclMapManager->GetMapName(pclInfo->siMapIndex);

		// KHY - 1122 - �����̵� �̿�� ����.		
		if(pclInfo->m_bInMap == true)		// �ش� �� ������ ���� ���
		{
			if (pclMapManager->pclGateManager->FindImportantPos( pclInfo->siMapIndex, &x, &y ) == false )
				return ;

			clWarpInfo.uiMapIndex = pclInfo->siMapIndex;
			// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
			clWarpInfo.uiX = x+2;
			clWarpInfo.uiY = y+2;
		}
		else
		{
			if (pclMapManager->pclGateManager->FindMainFieldPos( pclInfo->siMapIndex, &x, &y ) == false )
				return;

			clWarpInfo.uiMapIndex = 0; //������ ���� �� ���´�.
			// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
			clWarpInfo.uiX = x+2;
			clWarpInfo.uiY = y+2;

		}
		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[pclInfo->siMapIndex]->siMapUnique;
		x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;
		
		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		clWarpInfo.uiMapIndex = pclInfo->siMapIndex;
		clWarpInfo.uiX = x;
		clWarpInfo.uiY = y;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
		cltGameMsgResponse_WarpEffect clinfo(id);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
		if(pclInfo->siMapIndex < MAX_VILLAGE_NUMBER)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
		}
		// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
		else
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
		}

		//���� Ÿ�� pvp ����.

	
		pclChar->SetWarpInfo(&clWarpInfo, warpunique);
		if ( pclChar->Warp() == TRUE )
		{
			//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
			if ( siWarpMode == HUNTMAPWARP_MODE_USEITEM )
			{
				if( bNoLimitWarp == false)
				{
					// ��踦 ����. 
					pclItemManager->AddUseNum(itemunique, 1);

					// ���ο� ��� - ������ ���
					//NStatistics_Add("Item", itemunique, "UseNum", 1);

					// �����̵��̿���� �Һ��Ѵ�.
					//////////////////////////////////////////////////////////////////////////
					cltItem clItem;
					clItem.Init();
					clItem.siUnique = itemunique;
					clItem.siItemNum = 1;

					SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
					sDBRequest_UseItem clMsg( id, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					//////////////////////////////////////////////////////////////////////////
				}
			}
			else if( siWarpMode == HUNTMAPWARP_MODE_USEMONEY )
			{
				SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

				if(personid)
				{
					sDBRequest_ChangeMoney clMsg(id, personid, CHANGE_MONEY_REASON_MONEY_WARP, -(pclInfo->siWMoney));
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

					pclDelMoneyStatistics->Add(DELMONEY_WARP, pclInfo->siWMoney);
				}
			}
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PERSONALSHOPWARP(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_PersonalShopWarp* pclInfo = (cltGameMsgRequest_PersonalShopWarp*)pclMsg->cData;

#ifdef _CHINA
	if( false == CheckWarp( id, pclInfo->siMapIndex, pclInfo->siX, pclInfo->siY ) )
		return;
#else
	if( pclCM->IsAlive( id ) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	SI32 MapIndex	= pclInfo->siMapIndex;
	SI32 XIndex		= pclInfo->siX;
	SI32 YIndex		= pclInfo->siY;

	if ( MapIndex < 0 || MapIndex >= MAX_MAP_NUMBER )		return ;
	if ( pclMapManager->pclMapArray[MapIndex] == NULL )		return ;

	bool bFound = pclMapManager->IsValidArea(MapIndex, XIndex, YIndex);
	if(bFound == false)										return;

	if( pclChar->CanWarpFrom() == false )						return;
	if( pclChar->CanWarpTo(MapIndex) == false )					return;
	bool bNoLimitWarp = pclChar->CanFreeWarp( MapIndex );

	bool bVillageWarp = false ;
	if ( pclInfo->siMapIndex > 0 && pclInfo->siMapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclInfo->siMapIndex) == true )
			bVillageWarp = true;
	}

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;
	SI32 warpunique = 0 ;

	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);
	if ( itemNum <= 0 && !bNoLimitWarp )
		return ;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0 && !bNoLimitWarp ) return ;

	if( true == pclChar->bPersonalShopSwitch ||
		true == pclChar->bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
			{
				if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
					return;
				}
			}
		}
	}
	
	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		x = pclInfo->siX;
		y = pclInfo->siY;

		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[pclInfo->siMapIndex]->siMapUnique;

		x = pclInfo->siX;
		y = pclInfo->siY;
		
		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
		cltGameMsgResponse_WarpEffect clinfo(id);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
		if(pclInfo->siMapIndex < MAX_VILLAGE_NUMBER)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
		}
		// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
		else
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
		}
	
		cltWarpInfo clWarpInfo(1, pclInfo->siMapIndex, false, true, x, y, -1, -1);
		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, warpunique);
		pclCM->CR[id]->Warp();
		
	}

	if (!bNoLimitWarp)
	{
		// ��踦 ����. 
		pclItemManager->AddUseNum(itemunique, 1);

		// ���ο� ��� - ������ ���
		//NStatistics_Add("Item", itemunique, "UseNum", 1);

		// �����̵��̿���� �Һ��Ѵ�.
		//////////////////////////////////////////////////////////////////////////
		cltItem clItem;
		clItem.Init();
		clItem.siUnique = itemunique;
		clItem.siItemNum = 1;

		SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		sDBRequest_UseItem clMsg( id, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//////////////////////////////////////////////////////////////////////////
	}
#endif
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FRIENDWARP(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_FriendWarp* pclInfo = (cltGameMsgRequest_FriendWarp*)pclMsg->cData;

#ifdef _CHINA
	SI32 FriendID = pclCM->GetIDFromPersonID( pclInfo->siPersonID );
	if ( FriendID < 1 || pclCM->IsValidID( FriendID ) == FALSE )
	{
		return;
	}

	// ������ ����� �ʿ� �ִٸ�.
	if ( IsGuildWarMap( pclCM->CR[FriendID]->GetMapIndex() )  )
	{
		BOOL				bInBattle = FALSE;
		cltGuildWarManager*	pclFriendGuildWarManager = NULL;

		// ������ �������� ������� ������ ã�´�.
		if (IsCountrySwitch(Switch_NewGuildHuntMapWar )) // ������
		{
			for(SI32 i=0; i<GUILDWAR_FIELDNUM_OLD; i++)
			{
				if(i >= GUILDWAR_FIELDNUM_OLD) continue	;
				if( pclGuildWarManager[i]->m_siAwayGuildUnique == pclCM->CR[FriendID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
					pclGuildWarManager[i]->m_siHomeGuildUnique == pclCM->CR[FriendID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
				{
					pclFriendGuildWarManager = pclGuildWarManager[i];
				}
			}
		}
		else	// ������
		{
			for(SI32 i=0; i<GUILDWAR_FIELDNUM; i++)
			{
				if(i >= GUILDWAR_FIELDNUM) continue	;
				if( pclGuildWarManager[i]->m_siAwayGuildUnique == pclCM->CR[FriendID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
					pclGuildWarManager[i]->m_siHomeGuildUnique == pclCM->CR[FriendID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
				{
					pclFriendGuildWarManager = pclGuildWarManager[i];
				}
			}
		}
		// ������￡ �츮 ��尡 �������ΰ�?
		if ( pclFriendGuildWarManager != NULL &&
			(pclFriendGuildWarManager->m_siAwayGuildUnique == pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
			pclFriendGuildWarManager->m_siHomeGuildUnique == pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex()) )
		{
			bInBattle = TRUE;
		}

		// ���￡ �������� ������ �ƴϹǷ� ���忡 �� �� ����.
	}
	// ������ ����� �ʿ� �ִٸ�.
	if ( IsGuildWarMap_NEW( pclCM->CR[FriendID]->GetMapIndex() )  )
	{
		if (IsCountrySwitch(Switch_NewGuildHuntMapWar )) // ������
		{
			BOOL				bInBattle = FALSE;

			// ���￡ �������� ������ �ƴϹǷ� ���忡 �� �� ����.
			SI32 siMyGuilindex = pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex()	;
			if(GUILDWAR_HOMEGUILD ==pclGuildHuntMapManager->IsHomeGuildorAwayGuild( siMyGuilindex )	)
			{	
				bInBattle = TRUE;
			}
			else if(GUILDWAR_AWAYGUILD ==pclGuildHuntMapManager->IsHomeGuildorAwayGuild( siMyGuilindex )	)
			{
				bInBattle = TRUE;
			}

		}
	}
	if (bVillageWarSwitch)
	{
		SI32 returnval = SRVAL_FAIL_FORBID_BATTLE;
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if(pclCM->CR[id]->pclFriendInfo)
	{
		// ģ�� ��Ͽ� �ִ��� Ȯ��
		SI16 i = 0;
		for ( ; i < MAX_FRIEND_NUMBER; ++i )
		{
			if ( pclCM->CR[id]->pclFriendInfo->clFriend[ i ].GetPersonID() > 0 &&
				pclCM->CR[id]->pclFriendInfo->clFriend[ i ].GetPersonID() == pclInfo->siPersonID
				)
			{
				break;
			}
		}

		if ( i == MAX_FRIEND_NUMBER )
		{
			return;
		}
	}

	SI32 mapIndex = pclCM->CR[FriendID]->GetMapIndex();
	SI32 posX = pclCM->CR[FriendID]->GetX();
	SI32 posY = pclCM->CR[FriendID]->GetY();

	bool bFound = pclMapManager->IsValidArea( mapIndex, posX, posY );
	if( bFound == false ) 
		return;

	if( false == CheckWarp( id, mapIndex, posX, posY ) )
		return;
#else

	if( pclCM->IsAlive( id ) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	SI32 FriendID = pclCM->GetIDFromPersonID( pclInfo->siPersonID );
	if ( FriendID < 1 || pclCM->IsValidID( FriendID ) == FALSE )
	{
		return;
	}

	// ģ�� ��Ͽ� �ִ��� Ȯ��
	if( pclInfo->siMode == FRIENDWARP_MODE_FRIEND )
	{
		bool bFindFriend = false;
		if(pclCM->CR[id]->pclFriendInfo)
		{
			SI16 i = 0;		
			for ( ; i < MAX_FRIEND_NUMBER; ++i )
			{
				if( pclCM->CR[id]->pclFriendInfo->clFriend[ i ].GetPersonID() > 0 &&
					pclCM->CR[id]->pclFriendInfo->clFriend[ i ].GetPersonID() == pclInfo->siPersonID )
				{
					bFindFriend = true;
					break;
				}
			}

			if ( bFindFriend == false )
			{
				return;
			}
		}
	}

	if( pclInfo->siMode == FRIENDWARP_MODE_GUILD )
	{
		if( pclChar->pclCI->clBI.clGuildRank.IsGuildMember() == false )
			return;
	
		SI32 siFriendID = pclCM->GetIDFromPersonID( pclInfo->siPersonID );
		if( siFriendID <= 0 )			return;
		cltCharServer* pclFriend = (cltCharServer*)pclCM->CR[siFriendID];
		if( pclFriend->pclCI->clBI.clGuildRank.IsGuildMember() == false )
			return;

		if( pclChar->pclCI->clBI.clGuildRank.GetGuildUnitIndex() != pclFriend->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
			return;
	}

	SI32 MapIndex	= pclCM->CR[FriendID]->GetMapIndex();
	SI32 XPos		= pclCM->CR[FriendID]->GetX();
	SI32 YPos		= pclCM->CR[FriendID]->GetY();
	
	if ( MapIndex < 0 || MapIndex >= MAX_MAP_NUMBER ) return ;
	if ( pclMapManager->pclMapArray[MapIndex] == NULL ) return ;

	bool bFound = pclMapManager->IsValidArea( MapIndex, XPos, YPos );
	if( bFound == false )	return;

	bool bVillageWarp = false ;
	if ( MapIndex > 0 && MapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(MapIndex) == true )
			bVillageWarp = true ;
	}

	if( pclChar->CanWarpFrom() == false )				return;
	if( pclChar->CanWarpTo( MapIndex ) == false )		return;
	if( pclChar->CanWarpToChar( FriendID ) == false )	return;
	bool bNoLimitWarp = pclChar->CanFreeWarp( MapIndex );

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;
	SI32 warpunique = 0 ;
	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);

	if ( itemNum <= 0 && !bNoLimitWarp )				return ;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0 && !bNoLimitWarp)return ;

	if( true == pclChar->bPersonalShopSwitch ||
		true == pclChar->bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
			{
				if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
					return;
				}
			}
		}
	}

	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		x = XPos;
		y = YPos;

		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[MapIndex]->siMapUnique;

		x = XPos;
		y = YPos;
		
		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
		cltGameMsgResponse_WarpEffect clinfo(id);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
		if(MapIndex < MAX_VILLAGE_NUMBER)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
		}
		// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
		else
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
		}

		// �����̵��̿���� �̿��� ģ������ �̵��ϱ� ����Ʈ ���̶��,
		pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET3);
	
		cltWarpInfo clWarpInfo(1, MapIndex, false, true, x, y, -1, -1);
		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, warpunique);
		pclCM->CR[id]->Warp();
		
	}


	if ( !bNoLimitWarp )
	{
		// ��踦 ����. 
		pclItemManager->AddUseNum(itemunique, 1);

		// ���ο� ��� - ������ ���
		//NStatistics_Add("Item", itemunique, "UseNum", 1);

		// �����̵��̿���� �Һ��Ѵ�.
		//////////////////////////////////////////////////////////////////////////
		cltItem clItem;
		clItem.Init();
		clItem.siUnique = itemunique;
		clItem.siItemNum = 1;

		SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		sDBRequest_UseItem clMsg( id, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//////////////////////////////////////////////////////////////////////////
	}
#endif
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYWARP(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_PartyWarp* pclInfo = (cltGameMsgRequest_PartyWarp*)pclMsg->cData;

#ifdef _CHINA
	SI32 partyID = pclCM->GetIDFromName( pclInfo->szName );
	if ( partyID < 1 || pclCM->IsValidID( partyID ) == FALSE || partyID == id )
	{
		return;
	}

	// ������ ����� �ʿ� �ִٸ�.
	if ( IsGuildWarMap( pclCM->CR[partyID]->GetMapIndex() )  )
	{
		BOOL				bInBattle = FALSE;
		cltGuildWarManager*	pclPartyGuildWarManager = NULL;

		// ������ �������� ������� ������ ã�´�.
		// ������ 
		if ( IsCountrySwitch( Switch_NewGuildHuntMapWar ))
		{
			for(SI32 i=0; i<GUILDWAR_FIELDNUM_OLD; i++)
			{
				if(i >= GUILDWAR_FIELDNUM_OLD) continue	;
				if( pclGuildWarManager[i]->m_siAwayGuildUnique == pclCM->CR[partyID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
					pclGuildWarManager[i]->m_siHomeGuildUnique == pclCM->CR[partyID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
				{
					pclPartyGuildWarManager = pclGuildWarManager[i];
				}
			}

		}
		else	//������
		{
			for(SI32 i=0; i<GUILDWAR_FIELDNUM; i++)
			{
				if(i >= GUILDWAR_FIELDNUM) continue	;
				if( pclGuildWarManager[i]->m_siAwayGuildUnique == pclCM->CR[partyID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
					pclGuildWarManager[i]->m_siHomeGuildUnique == pclCM->CR[partyID]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() )
				{
					pclPartyGuildWarManager = pclGuildWarManager[i];
				}
			}

		}
		
		// ������￡ �츮 ��尡 �������ΰ�?
		if ( pclPartyGuildWarManager != NULL &&
			(pclPartyGuildWarManager->m_siAwayGuildUnique == pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() ||
			pclPartyGuildWarManager->m_siHomeGuildUnique == pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex()) )
		{
			bInBattle = TRUE;
		}

		// ���￡ �������� ������ �ƴϹǷ� ���忡 �� �� ����.
		if (bInBattle == FALSE)
		{
			return;
		}
	}

	// ������ ����� �ʿ� �ִٸ�.
	if ( IsGuildWarMap_NEW( pclCM->CR[partyID]->GetMapIndex() )  )
	{
		if ( IsCountrySwitch( Switch_NewGuildHuntMapWar ))
		{
			BOOL				bInBattle = FALSE;
			cltGuildWarManager*	pclPartyGuildWarManager = NULL;

			SI32 siMyGuildIndex = pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex()	;
			if( GUILDWAR_HOMEGUILD ==pclGuildHuntMapManager->IsHomeGuildorAwayGuild( siMyGuildIndex) ||
				GUILDWAR_AWAYGUILD ==pclGuildHuntMapManager->IsHomeGuildorAwayGuild( siMyGuildIndex) )
		 {
			 bInBattle = TRUE;
		 }

		 // ���￡ �������� ������ �ƴϹǷ� ���忡 �� �� ����.
		 if (bInBattle == FALSE)
		 {
			 return;
		 }

		}
	}

	SI32 mapIndex = pclCM->CR[partyID]->GetMapIndex();
	SI32 posX = pclCM->CR[partyID]->GetX();
	SI32 posY = pclCM->CR[partyID]->GetY();


	bool bFound = pclMapManager->IsValidArea( mapIndex, posX, posY );
	if(bFound == false) 
		return;

	if( false == CheckWarp( id, mapIndex, posX, posY ) )
		return;
#else
	if( pclCM->IsAlive( id ) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	SI32 partyID = pclCM->GetIDFromName( pclInfo->szName );
	if(pclCM->IsValidID(partyID) == false)				return;

	SI32 XPos = pclCM->CR[partyID]->GetX();
	SI32 YPos = pclCM->CR[partyID]->GetY();

	if ( partyID < 1 || pclCM->IsValidID( partyID ) == FALSE || partyID == id )
	{
		return;
	}

	SI32 MapIndex = pclCM->CR[partyID]->GetMapIndex();
	if ( MapIndex < 0 || MapIndex >= MAX_MAP_NUMBER ) return ;
	if ( pclMapManager->pclMapArray[MapIndex] == NULL ) return ;
	
	
	bool bFound = pclMapManager->IsValidArea( MapIndex, XPos, YPos );
	if(bFound == false) return;

	bool bVillageWarp = false ;
	if ( MapIndex > 0 && MapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(MapIndex) == true )
			bVillageWarp = true ;
	}

	// ���� ���ɼ� üũ �Լ� ȣ��
	if( pclChar->CanWarpFrom() == false )				return;
	if( pclChar->CanWarpTo( MapIndex ) == false )		return;
	if( pclChar->CanWarpToChar( partyID ) == false )	return;

	// ���� �����̵��� �����Ѱ�?
	bool bNoLimitWarp = pclChar->CanFreeWarp( MapIndex );

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;
	SI32 warpunique = 0 ;

	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);
	if ( itemNum <= 0 && !bNoLimitWarp )
		return ;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0 && !bNoLimitWarp)return ;

	if( true == pclChar->bPersonalShopSwitch ||
		true == pclChar->bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
			{
				if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
					return;
				}
			}
		}
	}

	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		if ( (MapIndex == MAPINDEX_BEGINNER1  )
			&& pclChar->pclCI->clIP.GetLevel() > 10 ) return ;

		x = XPos;
		y = YPos;

		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[MapIndex]->siMapUnique;

		x = XPos;
		y = YPos;

		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
		cltGameMsgResponse_WarpEffect clinfo(id);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
		if(MapIndex < MAX_VILLAGE_NUMBER)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
		}
		// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
		else
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
		}

		cltWarpInfo clWarpInfo(1, MapIndex, false, true, x, y, -1, -1);
		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, warpunique);
		pclCM->CR[id]->Warp();


	}

	if ( !bNoLimitWarp )
	{
		// ��踦 ����. 
		pclItemManager->AddUseNum(itemunique, 1);

		// ���ο� ��� - ������ ���
		//NStatistics_Add("Item", itemunique, "UseNum", 1);

		// �����̵��̿���� �Һ��Ѵ�.
		//////////////////////////////////////////////////////////////////////////
		cltItem clItem;
		clItem.Init();
		clItem.siUnique = itemunique;
		clItem.siItemNum = 1;

		SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
		sDBRequest_UseItem clMsg( id, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
		//////////////////////////////////////////////////////////////////////////
	}
#endif
}

void cltServer::DoMsg_GAMEMSG_REQUEST_WARJOIN(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_HuntMapWarp* pclInfo = (cltGameMsgRequest_HuntMapWarp*)pclMsg->cData;

	if( pclCM->IsAlive( id ) == false )
		return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	// 30�̻� �������� �Ұ�
	if( pclChar->pclCI->clIP.GetLevel() > 30 )
		return;

	if ( pclInfo->siMapIndex <= 0 || pclInfo->siMapIndex >= MAX_MAP_NUMBER ) return ;
	if ( pclMapManager->pclMapArray[pclInfo->siMapIndex] == NULL ) return ;



	// ���������� ���� �Ұ�. 
	if( pclChar->clInnerStatus.IsStatus(INNERSTATUS_PRISON)) return ;
	// ������ո��̸� ���� �Ұ�.
	//if ( pclInfo->siMapIndex == MAPINDEX_BATTLESEA ) return ;
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[id]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return ;
	}
	
	//if ( pclInfo->siMapIndex >= MAPINDEX_DAEMADO || pclInfo->siMapIndex == MAPINDEX_DAEMADOGATE ) return ;

	bool bVillageWarp = false ;

	if ( pclInfo->siMapIndex > 0 && pclInfo->siMapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclInfo->siMapIndex) == true )
			bVillageWarp = true ;
		else return ;
	}

	bool bNoLimitWarp = true ;
	
	SI32 x = 0 , y = 0 ;

	SI32 warpunique = 0 ;


	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		//if ( pclMapManager->GetLevelLimit(pclInfo->siMapIndex) > pclChar->pclCI->clIP.GetLevel() )
		if ( pclMapManager->IsEnterLevel(pclInfo->siMapIndex, pclChar->pclCI->clIP.GetLevel()) == false )
			return ;

		const TCHAR * szMapName = pclMapManager->GetMapName(pclInfo->siMapIndex);

		if ( (pclInfo->siMapIndex == MAPINDEX_BEGINNER1 /* || pclInfo->siMapIndex == MAPINDEX_BEGINNER2*/ )
			&& pclChar->pclCI->clIP.GetLevel() > 10 ) return ;

		if ( pclMapManager->pclGateManager->FindImportantPos(pclInfo->siMapIndex,&x,&y) == false )
			return ;

		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[pclInfo->siMapIndex]->siMapUnique;
		x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
	//	cltGameMsgResponse_WarpEffect clinfo(id);
	//	cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
	//	((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		cltWarpInfo clWarpInfo(1, pclInfo->siMapIndex, false, true, x, y, -1, -1);

		pclCM->CR[id]->SetWarpInfo(&clWarpInfo, warpunique);
		pclCM->CR[id]->Warp();

	}
	
	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_AUTOHUNTING(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_AutoHunting* pclinfo = (cltGameMsgRequest_AutoHunting*)pclMsg->cData;

	if ( pclCM->IsValidID( id ) == false )
		return;

	// ������ ������ �Ű� ���Ѵ�.
	if(pclCM->CR[id]->clInnerStatus.IsStatus(INNERSTATUS_PRISON)	== true )
		return ;
	// ���ڳ��� ������ �Ұ���
	if ( pclCM->CR[id]->GetMapIndex() == MAPINDEX_MASTERWORLD &&
		pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		return ;
	}

	// �߸��� �̸��̴�.
	if ( _tcslen(pclinfo->szSuspectName) <= 0 || !_tcscmp(pclinfo->szSuspectName,TEXT("")) )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_NAMEERROR,  0, 0, id);
		return ;
	}

	cltCharServer *pclCharRequest = (cltCharServer *)pclCM->CR[id];
	if ( pclCharRequest == NULL ) return ;

	// ���� ĳ�����̴�.
	SI32 suspectid = pclCM->GetIDFromName(pclinfo->szSuspectName);
	if ( suspectid <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_NAMEERROR,  0, 0, id);
		return ;
	}
	cltCharServer *pclCharSuspect = (cltCharServer *)pclCM->CR[suspectid];
	if ( pclCharSuspect == NULL ) return ;

	TCHAR szName[MAX_PLAYER_NAME] = TEXT("") ;
	StringCchCopy(szName, MAX_PLAYER_NAME, pclCharRequest->GetName());

	// ����� ���� �ʰų� ����Ͱ� �ƴϴ�.
	if ( pclCharSuspect->IsAutoHunting() == false )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_NOTHUNTING,  0, 0, id);
		return ;
	}


	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;
	SI32 TimeLimit	= min(300, max(20, pclminister->m_siSuspectTime)) ;
	SI16 PrisonTime = min(60, max(5, pclminister->m_siPrisonTime)) ;
	SI16 penalty = pclminister->m_siPrisonerPenalty ;

	// ���� ����

	const TCHAR* Txt = pclItemManager->GetRandomItemName();
	if ( Txt == NULL || _tcslen(Txt) <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_SERVERERROR,  0, 0, id);
		return ;
	}

	// �̹� �Ű�� ĳ�����̴�.

	if ( pclAutoHuntingManager->IsRequest(pclinfo->szSuspectName) == true )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_ISREQUEST,  0, 0, id);
		return ;
	}

	// ���� ����
	SI32 slot = 0 ;
	if ( pclAutoHuntingManager->Set(Txt,szName,pclinfo->szSuspectName,
									&slot,pclCharRequest->pclCI->GetPersonID()) == false )
	{
		SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_SERVERERROR,  0, 0, id);
		return ;
	}

	cltGameMsgResponse_AutoHunting clinfo1(TimeLimit,slot,PrisonTime,penalty,Txt);
	cltMsg clMsg1(GAMEMSG_RESPONSE_AUTOHUNTING, 	sizeof(clinfo1), (BYTE*)&clinfo1);
	pclCM->CR[suspectid]->SendNetMsg((sPacketHeader*)&clMsg1);

	cltGameMsgResponse_AutoHunting_TimeUpdate clinfo2(0,TimeLimit);
	cltMsg clMsg2(GAMEMSG_RESPONSE_AUTOHUNTING_TIMEUPDATE, sizeof(clinfo2), (BYTE*)&clinfo2);
	pclCM->CR[suspectid]->SendNetMsg((sPacketHeader*)&clMsg2);

	// �Ƿ� ����
	if ( IsPC(id) )
	{
		SendServerResponseMsg(0,SRVAL_AUTOHUNTING_SUCCESS_REQUEST,0,0,id);

		// TargetID	�ǽɵǴ� ���� personID
		// para1	�Ƿ���
		// para2	�ǽɵǴ� ����

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))  
		{
			SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_PRISON, LOGCOMMAND_INDEX_REQUEST_SUSPECTUSER, 
									0, NULL, NULL, pclCharSuspect->pclCI->GetPersonID(), 0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
									(TCHAR*)pclCharRequest->GetName() , pclinfo->szSuspectName);
		}
	}

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_AUTOHUNTING_ASK(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_AutoHunting_Ask* pclinfo = (cltGameMsgRequest_AutoHunting_Ask*)pclMsg->cData;

	if ( pclCM->IsValidID( id ) == false )
		return;
	
	CMinisterHyungzo *pclminister = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);
	if ( pclminister == NULL ) return ;

	SI16 penalty = pclminister->m_siPrisonerPenalty ;

	const TCHAR * name = pclCM->CR[id]->GetName();

	SI32 siCheckNumber = 0 ;

	if ( pclAutoHuntingManager->CheckAnswer(name,pclinfo->szAnswer,pclinfo->siSlot,&siCheckNumber) == true )
	{
		cltGameMsgResponse_AutoHunting_Ask clinfo(true,0,penalty);
		cltMsg clMsg(GAMEMSG_RESPONSE_AUTOHUNTING_ASK, 	sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		return ;
	}
	else
	{
		if ( siCheckNumber == 0 )
		{
			SendServerResponseMsg(0, SRVAL_AUTOHUNTING_FAIL_SERVERERROR,  0, 0, id);
			return ;
		}
		else
		{
			cltGameMsgResponse_AutoHunting_Ask clinfo(false,siCheckNumber,penalty);
			cltMsg clMsg(GAMEMSG_RESPONSE_AUTOHUNTING_ASK, 	sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			return ;
		}
	}
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_VILLAGESTRUCT(cltMsg* pclMsg, SI32 id)
{
	// ��û ���� ������ ref�� ã�´�. 
	SI32 ref = pclMsg->siData32[0];
	if(ref <= 0 || ref >= MAX_VILLAGE_NUMBER)return ;
	if(pclVillageManager->pclVillageInfo[ref] == NULL)return ;

	// �޽����� �����. 
	cltGameMsgResponse_VillageStruct clinfo(ref, pclVillageManager->pclVillageInfo[ref]->clVillageVary.clStructureInfo.Get());
	cltMsg clMsg(GAMEMSG_RESPONSE_VILLAGESTRUCT, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETANGELAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER2 ) return;
	if(bVillageWarSwitch == true)	return;

	if ( pclMinisterMgr )
	{
		CMinisterHozo *pclHozo = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);

		if ( pclHozo == NULL ) return ;
		pclHozo->DoMsg_GameMsgRequest_GetAngelApplyerList(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETANGELLIST(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHozo *pclHozo = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);

		if ( pclHozo == NULL ) return ;
		pclHozo->DoMsg_GameMsgRequest_GetAngelList(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETANGELAPPLYER(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHozo *pclHozo = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);

		if ( pclHozo == NULL ) return ;
		pclHozo->DoMsg_GameMsgRequest_SetAngelApplyer(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETANGEL(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if(pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER2 && (pclCM->CR[id]->pclCI->clBI.uiAngelSwitch == NULL)) return;
	if(bVillageWarSwitch == true)	return;

	if ( pclMinisterMgr )
	{
		CMinisterHozo *pclHozo = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);

		if ( pclHozo == NULL ) return ;
		pclHozo->DoMsg_GameMsgRequest_SetAngel(pclMsg,id);
	}
}

// ���� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_SETPOLICE(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHyungzo *pclHyungzo = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

		if ( pclHyungzo == NULL ) return ;
		pclHyungzo->DoMsg_GameMsgRequest_SetPolice(pclMsg,id);
	}
}

// ���� ��� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_GETPOLICELIST(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHyungzo *pclHyungzo = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

		if ( pclHyungzo == NULL ) return ;
		pclHyungzo->DoMsg_GameMsgRequest_GetPoliceList(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETCRIMINALLIST(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHyungzo *pclHyungzo = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

		if ( pclHyungzo == NULL ) return ;
		pclHyungzo->DoMsg_GameMsgRequest_GetCriminalList(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETCRIMINAL(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == false )
		return;

	if ( pclMinisterMgr )
	{
		CMinisterHyungzo *pclHyungzo = (CMinisterHyungzo *)pclMinisterMgr->GetMinister(MINISTER_HYUNGZO);

		if ( pclHyungzo == NULL ) return ;
		pclHyungzo->DoMsg_GameMsgRequest_SetCriminal(pclMsg,id);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GETCHANGEDNAME(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_GetChangedName* pclinfo = (cltGameMsgRequest_GetChangedName*)pclMsg->cData;

	if ( pclCM->IsValidID(id) == false) return ;
	if ( pclinfo->siPage < 0 ) return ;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if ( personid <= 0 ) return ;

	sDBRequest_GetChangedName clMsg( id, personid, pclinfo->siPage, MAX_HOZO_CHANGEDNAME_LIST );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETSCHOOLEVENT(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_SetSchoolEvent* pclinfo = (cltGameMsgRequest_SetSchoolEvent*)pclMsg->cData;

	if( pclCM->IsValidID(id) == FALSE )
		return;
	if( pclinfo->siUnique < 1 || pclinfo->siGrade < 1 || pclinfo->siClass < 1)
		return;
	

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GOONZU_SETMINISTER(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Goonzu_SetMinister * pclinfo = (cltGameMsgRequest_Goonzu_SetMinister*)pclMsg->cData ;

	if( pclCM->IsValidID(id) == FALSE )
		return;

	if ( pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_KING )
		return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID() ;
	if ( personid <= 0 ) return ;

	if ( _tcslen(pclinfo->szCharName) <= 0 || pclinfo->szCharName[0] == NULL )
		return ;

	if ( !_tcscmp(pclCM->CR[id]->pclCI->clBI.GetName(),pclinfo->szCharName) )
		return ;


	SI32 grank = 0 ;
	SI32 minister = 0 ;

	if ( pclinfo->siMinisterInx == 1 ){ grank = GRANK_MINISTER1; minister = MINISTER_IZO;}
	else if ( pclinfo->siMinisterInx == 2 ){ grank = GRANK_MINISTER4; minister = MINISTER_BYUNGZO;}
	else if ( pclinfo->siMinisterInx == 3 ){ grank = GRANK_MINISTER2; minister = MINISTER_HOZO;}
	else if ( pclinfo->siMinisterInx == 4 ){ grank = GRANK_MINISTER5; minister = MINISTER_HYUNGZO;}
	else if ( pclinfo->siMinisterInx == 5 ){ grank = GRANK_MINISTER3; minister = MINISTER_YEZO;}
	else if ( pclinfo->siMinisterInx == 6 ){ grank = GRANK_MINISTER6; minister = MINISTER_GONGZO;}
	else return ;

	CMinisterGoonzu *pclministerGoonzu = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclministerGoonzu == NULL ) return ;

	CMinisterBase * pclminister = pclMinisterMgr->GetMinister(minister) ;
	if ( pclminister == NULL ) return ;

	if ( !pclinfo->bLeave )
	{
		//[���� : Ȳ���� 2007. 10. 12  �� ĳ���� 2���̻��� �Ǽ� �ߺ��� �Ұ��� �ϰ�.]
		CMinisterBase* pclSerachMinister;
		for(SI32 i = MINISTER_TYPE_START; i < MINISTER_LAST; ++i)
		{
			pclSerachMinister = pclMinisterMgr->GetMinister(i) ;

			// �̹� ĳ���� ��ϵ��ִٸ� ���.
			if ( 0 == _tcscmp(pclinfo->szCharName, pclSerachMinister->m_szPersonName) )
			{
				SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETMINISTER,  0, 0, pclCM->CR[id]->GetCharUnique());
				return ;
			}
		}

		if ( !_tcscmp(pclinfo->szCharName,pclminister->m_szPersonName) )
			return ;

		SI32 curdate = pclTime->clDate.GetDateVary();
		if( ((grank-2) >= 0 && (grank-2) < 6) && pclministerGoonzu->m_siSetMinisterTime[grank-2] + 180 >  curdate)
		{
			SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETMINISTER_DATE,  6, 0, pclCM->CR[id]->GetCharUnique());
			return ;
		}

		sDBRequest_SetMinister clMsg(grank,personid,pclinfo->szCharName,false,curdate);
		SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else
	{
		if ( _tcscmp(pclinfo->szCharName,pclminister->m_szPersonName) )
			return ;

		TCHAR buffer[MAX_PLAYER_NAME] = TEXT("") ;
		sDBRequest_SetMinister clMsg(grank,personid,buffer,false,0);
		SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GOONZU_SETLIQUIDATION(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_Goonzu_SetLiquidation * pclinfo = (cltGameMsgRequest_Goonzu_SetLiquidation*)pclMsg->cData ;

	if( pclCM->IsValidID(id) == FALSE )
		return;

#ifdef _DEBUG
#else
	if ( pclCM->CR[id]->pclCI->clBI.uiGRank != GRANK_MINISTER2 )
		return;
#endif

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID() ;
	if ( personid <= 0 ) return ;

	CMinisterHozo *pclministerHozo = (CMinisterHozo *)pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclministerHozo == NULL ) 
		return ;

	cltDate clDate;
	clDate.MakeFullDateFromDateVary(pclministerHozo->m_siSetBankruptcyVillageDate);
	clDate.AddMonth(12);

	if( pclTime->clDate.GetDateVary() >= clDate.GetDateVary() )
	{
		SI32 liquidationVillageNumber = pclinfo->siLiquidationVillageNumber;
		if( liquidationVillageNumber < 2 || liquidationVillageNumber > 5 )
			return;

		sDBRequest_SetLiquidation clMsg( personid, liquidationVillageNumber, pclTime->clDate.GetDateVary() );
		SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_GOONZU_GETBONUSTIME(cltMsg* pclMsg,SI32 id)
{
	
	if( pclCM->IsValidID(id) == FALSE )
		return;

	CMinisterGoonzu *pclministerGoonzu = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclministerGoonzu == NULL ) 
		return ;

	bool changeAble = false;

	// ���ֶ�� ���� �ٲܼ� �ְԲ� �������̽��� ���Ѵ�.
	if( pclCM->CR[id]->pclCI->clBI.uiGRank == GRANK_KING )
	{
		changeAble = true;

		// ���� ���� �ٲ���ٸ� ���̻� ���� �ٲܼ� ����.( �Ϸ翡 �ѹ��� ���� �ٲܼ��ִ� )
		if( pclministerGoonzu->m_siLastChangedBonusTimeYear == sTime.wYear
			&& pclministerGoonzu->m_siLastChangedBonusTimeMonth == sTime.wMonth
			&& pclministerGoonzu->m_siLastChangedBonusTimeDay == sTime.wDay )
		{
            changeAble = false;
		}
	}

	cltGameMsgResponse_Goonzu_GetBonusTime clBonus( pclministerGoonzu->m_siBonusTime , pclministerGoonzu->m_siMakeBonusTime , changeAble );		
	cltMsg clMsg( GAMEMSG_RESPONSE_GOONZU_GETBONUSTIME , sizeof( clBonus ) , (BYTE*)&clBonus );
	pclCM->CR[id]->SendNetMsg( (sPacketHeader*)&clMsg );

}


void cltServer::DoMsg_GAMEMSG_REQUEST_GOONZU_SETBONUSTIME(cltMsg* pclMsg,SI32 id)
{

	if( pclCM->IsValidID(id) == FALSE )
		return;

	cltGameMsgRequest_Goonzu_SetBonus * pclinfo = (cltGameMsgRequest_Goonzu_SetBonus *)pclMsg->cData;

	CMinisterGoonzu *pclministerGoonzu = (CMinisterGoonzu *)pclMinisterMgr->GetMinister(MINISTER_GOONZU);
	if ( pclministerGoonzu == NULL ) 
		return ;

	// 0~23 �� ���ڸ� ��ȿ�ϴ�
	if(pclinfo->siBonusTime < 0 || pclinfo->siBonusTime > 23 ) return;
	if(pclinfo->siMakeBonusTime < 0 || pclinfo->siMakeBonusTime > 23 ) return;


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID() ;
	if ( personid <= 0 ) return ;

	bool changeAble = false;

	// ���ֶ�� ���� �ٲܼ� �ִ�.
	if( pclCM->CR[id]->pclCI->clBI.uiGRank == GRANK_KING )
	{
		changeAble = true;

		// ���� ���� �ٲ���ٸ� ���̻� ���� �ٲܼ� ����.( �Ϸ翡 �ѹ��� ���� �ٲܼ��ִ� )
		if( pclministerGoonzu->m_siLastChangedBonusTimeYear == sTime.wYear
			&& pclministerGoonzu->m_siLastChangedBonusTimeMonth == sTime.wMonth
			&& pclministerGoonzu->m_siLastChangedBonusTimeDay == sTime.wDay )
		{
			//changeAble = false;
			SendServerResponseMsg(0,  SRVAL_MINISTER_FAIL_SETBONUS,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	}

	if( changeAble == false )
		return;
	
	sDBRequest_Goonzu_SetBonusTime clMsg( personid , pclinfo->siBonusTime , pclinfo->siMakeBonusTime , sTime.wYear , sTime.wMonth , sTime.wDay );
	SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

}




void cltServer::DoMsg_GAMEMSG_REQUEST_BLACKARMYAPPLY(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_BlackArmy_Apply *pclinfo = (cltGameMsgRequest_BlackArmy_Apply*)pclMsg->cData;

	if( pclCM->IsValidID(id) == FALSE )			return;

	SI32 ApplyUnique = -1;
	SI32 Result = 1;
	
	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[id];

	SI64 UserMoney = pclchar->pclCI->clIP.GetMoney();
	SI64 applyfee = BLACKARMY_APPLY_MONEY;

	//��û�� �� �ִ� �ð��̸�
	if(pclBlackArmyManager->bApplySwitch)
	{
		// ��Ƽ���̸� - ��Ƽ���� ���߿� �� �й��Ҷ� �� �ʿ� �־��ش�.
		//-----------------------------
		if(pclchar->pclCI->clIP.GetLevel() >= 20)
		{
			//if(pclchar->siPartyIndex)
			//{
			//	CPartyObj* pclparty = pclPartyMgr->GetPartyObj(pclchar->siPartyIndex);
			//	if(pclparty)
			//	{
			//		bool bPartyLeader = pclparty->IsPartyLeader(pclchar->pclCI->clBI.clPerson.GetPersonID());

			//		if (UserMoney < applyfee)
			//		{
			//			// ������ ����
			//			Result = -5;
			//		}
			//		else
			//		{
			//			// �������� �����񺸴� ������쿡�� ��û
			//			cltBlackArmyApplyPerson clPerson(pclchar->pclCI->clBI.clPerson, pclchar->siPartyIndex, bPartyLeader);
			//			ApplyUnique = pclBlackArmyManager->ApplyPerson(&clPerson);
			//		}
			//	}
			//	else
			//	{
			//		Result = -1;
			//	}
			//}
			//else
			//{
			if (UserMoney < applyfee)
			{
				//������ ����
				Result = -5;
			}
			else
			{
				cltBlackArmyApplyPerson clPerson(pclchar->pclCI->clBI.clPerson);
				ApplyUnique = pclBlackArmyManager->ApplyPerson(&clPerson);
			}
			//}
		}
		else
		{
			//����20�̸�
			Result = -6;
		}

		if (Result > 0)
		{
			if (ApplyUnique == -1)
			{
				// ��û�ڰ� �� �� ��� ����ó��
				Result = -3;
			} else if (ApplyUnique == -2)
			{
				// �̹� ��û�Ͽ��� ��� ����ó��
				Result = -4;
			}
		}

		// ���������� ��û�� �Ǿ����� ���� ��û�� ����
		if (Result == 1)
		{
			sDBRequest_ChangeMoney clMsg(pclchar->GetID(), pclchar->pclCI->GetPersonID(), CHANGE_MONEY_REASON_BLACKARMYAPPLY, -applyfee );
			pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

			// �� ��迡 ���
			pclDelMoneyStatistics->Add(DELMONEY_ENTEREVENT, applyfee);

			// ���������� ��û�� �Ǿ����� ����Ʈ ���������� üũ
			pclchar->DoQuestCheckAndAction(QUEST_CLEAR_COND_BLACKARMY);

			// �α� ���
			// Param1 = ��û����Ʈ ��ȣ
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BLACKARMY, LOGCOMMAND_INDEX_BLACKARMY_APPLY, 0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0,
								ApplyUnique, 0, 0, 0, 0, NULL, NULL);
		}
	}
	else
	{
		// ��û�ð��� �ƴϸ� ����ó��
		Result = -2;
	}

	// Ŭ���̾�Ʈ�� ��� �뺸
	cltGameMsgResponse_BlackArmy_Apply clApply(Result, ApplyUnique);
	cltMsg clMsg(GAMEMSG_RESPONSE_BLACKARMYAPPLY, sizeof(clApply), (BYTE*)&clApply);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BLACKARMY_RANKINFO(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_BlackArmy_RankInfo *pclInfo = (cltGameMsgRequest_BlackArmy_RankInfo*)pclMsg->cData;

	if( pclCM->IsValidID(id) == FALSE )
		return;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 siPoints[MAX_WARRANK_PERSON_PER_MAP];
	TCHAR szPlayers[MAX_WARRANK_PERSON_PER_MAP][MAX_PLAYER_NAME];

	if (pclWarRankManager)
	{
		for (SI32 i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
		{
			if (pclWarRankManager->clRankInfo[i].m_warmapindex == pclInfo->siWarMapIndex)
			{
				for (SI32 j = 0; j < MAX_WARRANK_PERSON_PER_MAP; j++)
				{
					siPoints[j] = pclWarRankManager->clRankInfo[i].clRankPerson[j].m_score;
					StringCchCopy(szPlayers[j], MAX_PLAYER_NAME, pclWarRankManager->clRankInfo[i].clRankPerson[j].m_szPlayerName);
				}

				break;
				
			}
		}
	}
	else
	{
		return;
	}

	cltGameMsgResponse_BlackArmy_RankInfo clRankMsg(pclInfo->siWarMapIndex, siPoints, (TCHAR**)szPlayers);
	cltMsg clMsg(GAMEMSG_RESPONSE_BLACKARMY_RANKINFO, sizeof(clRankMsg), (BYTE*)&clRankMsg);

	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_BLACKARMY_WARPTOGATE(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_BlackArmy_WarpToGate *pclInfo = (cltGameMsgRequest_BlackArmy_WarpToGate*)pclMsg->cData;

	if( pclCM->IsValidID(id) == FALSE )
		return;

	cltCharServer *pclchar = (cltCharServer*)pclCM->CR[id];

	if (pclBlackArmyManager)
	{
		bool bExistGate = false;

		for (SI32 i = 0; i < MAX_BLACKARMY_MAP_CNT; i++)
		{
			if (pclBlackArmyManager->clWarMap[i].siGateUnique == pclInfo->siGateUnique)
				bExistGate = true;

		}

		if (bExistGate)
		{
			cltGate gate = pclClient->pclMapManager->pclGateManager->clGate[pclInfo->siGateUnique];

			cltWarpInfo clinfo(true, gate.SrcMapIndex, false, false, gate.SrcX, gate.SrcY, -1, -1);
			pclchar->SetWarpInfo(&clinfo,56);
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_RANK_INFO(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltGameMsgRequest_Server_Event_Rank_Info* pclInfo = (cltGameMsgRequest_Server_Event_Rank_Info*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	cltGameMsgResponse_Server_Event_Rank_Info clRankInfo;
	memcpy(&clRankInfo.m_clServerEvent_Rank_Record,  pclServerEventManager->GetServerEventRankRecord(), sizeof(clRankInfo.m_clServerEvent_Rank_Record));

	cltMsg clMsg( GAMEMSG_RESPONSE_SERVER_EVENT_RANK_INFO, sizeof(clRankInfo), (BYTE*)&clRankInfo );
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_BONUS_STAGE(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 siMapIndex = pclServerEventManager->GetBonusMapIndex( pclchar->pclCI->clIP.GetLevel() );
	UI32 x[] = { 65, 42, 61, 83, 63 }; 
	UI32 y[] = { 58, 82, 69, 19, 58 }; 

	cltWarpInfo clWarpPirateShip(1, siMapIndex, false, false, x[siMapIndex-361], y[siMapIndex-361], -1, -1);
	pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
	pclCM->CR[id]->Warp();
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_QUEST_START(cltMsg* pclMsg, SI32 id)
{
	SI32 siID = id;

	// ���� ������ �ɸ����ΰ�?
	if ( false == pclCM->IsValidID(siID) )
	{
		return;
	}

	// �ɸ��� ����Ʈ �ޱ�
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}
	
	// ���� �̺�Ʈ ����Ʈ ������ �ޱ�
	CNServerEvent_Quest*		pclSE_Quest = (CNServerEvent_Quest*)pclServerEventManager->GetServerEvent_Quest();
	if ( NULL == pclSE_Quest )
	{
		return;
	}
	
	// ���� �̺��� ����Ʈ ������ ������ �ޱ�
	CNServerEvent_QuestData*	pclQuestData	= (CNServerEvent_QuestData*)pclSE_Quest->GetServerEnent_QuestData();
	SI16						siMaxChar		= pclSE_Quest->GetCharacterLimit();
	SI32						siNowAmount		= pclSE_Quest->GetNowAmount();
	bool*						pbCharacter		= pclSE_Quest->GetCharacter();
	
	if ( NULL == pclQuestData )
	{
		return;
	}

	if ( NULL == pbCharacter )
	{
		return;
	}

	// �޽��� ������
	cltGameMsgResponse_Server_Event_Quest_Start clQuestStart( pclQuestData, siMaxChar, siNowAmount, pbCharacter );
	cltMsg clMsg( GAMEMSG_RESPONSE_SERVER_EVENT_QUEST_START, sizeof(clQuestStart), (BYTE*)&clQuestStart );

	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_SERVER_EVENT_LOBBY_ENTERFIELD(cltMsg* pclMsg, SI32 id)
{
	SI32 siID = id;
	
	// ���� ������ �ɸ����ΰ�?
	if ( false == pclCM->IsValidID(siID) )
	{
		return;
	}

	// �ɸ��� ����Ʈ �ޱ�
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siPersonID = pclchar->pclCI->GetPersonID();

	// ���� ������ ��
	SI32		siWarpX = 20;
	SI32		siWarpY = 20;
	cltWarpInfo clWarpPollMap(1, MAPINDEX_SERVEREVENT_LOBBY, true, false, siWarpX, siWarpY, -1, -1);

	pclchar->SetWarpInfo( &clWarpPollMap, 905 );
	pclchar->Warp();

	// �ڽ��� ���ʽ� �δ� ������ �޾ƿ�
	sDBRequest_Server_Event_Server_Person_Score_Get clMsg( siID, siPersonID );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );	
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_QUESTION_LIST_GET(cltMsg* pclMsg, SI32 id)
{
	if( false == pclCM->IsValidID(id) )	return;

	pclHelperManager->SendMsgQuestionTileList( id );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHECK_QUESTION(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;
	
	pclHelperManager->CheckQuestion( pclchar );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ADD_QUESTION(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Add_Question* pclInfo = (cltGameMsgRequest_Add_Question*)pclMsg->cData;

	cltQuestionInfo cltQuestionInfo;
	cltQuestionInfo.SetQuestionTile( pclInfo->m_szQuestionTitle );
	cltQuestionInfo.SetQuestionContents( pclInfo-> m_szQuestionContents );
	cltQuestionInfo.SetQuestionPersonID( pclchar->pclCI->GetPersonID() );
	cltQuestionInfo.SetQuestionUnique( id );

	pclHelperManager->AddQuestion( &cltQuestionInfo, id );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_QUESTION_CONTENTS_GET(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Question_Contents_Get* pclInfo = (cltGameMsgRequest_Question_Contents_Get*)pclMsg->cData;

	pclHelperManager->SendMsgQuestionContents( pclInfo->m_siPersonID, pclchar );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ADD_ANSWER(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Add_Answer* pclInfo = (cltGameMsgRequest_Add_Answer*)pclMsg->cData;

	pclHelperManager->AddAnswer( pclchar, pclInfo->m_siQuestionPersonID );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Add_Answer_Complete* pclInfo = (cltGameMsgRequest_Add_Answer_Complete*)pclMsg->cData;

	pclHelperManager->AddAnswerComplete( pclchar, pclInfo->m_siQuestionPersonID, pclInfo->m_szQuestionTitle, pclInfo->m_szQuestionContents );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ADD_ANSWER_COMPLETE_RESULT(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Add_Answer_Complete_Result* pclInfo = (cltGameMsgRequest_Add_Answer_Complete_Result*)pclMsg->cData;

	pclHelperManager->AddAnswerCompleteResult( pclInfo->m_bResult, pclInfo->m_siAnswerCharPersonID, id );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DEL_QUESTION(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	// ������ personID�� ������ �׳��� ���������� ĳ���� ������ �������~
	SI32* psiQuestionPersonID = (SI32*)pclMsg->cData;
	if( NULL != psiQuestionPersonID && 0 < *psiQuestionPersonID )
	{
		pclchar = pclCM->GetCharServer( pclCM->GetIDFromPersonID(*psiQuestionPersonID) );
		if ( NULL == pclchar )	return;
	}

	pclHelperManager->DelQuestion( pclchar, true );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_DEL_ANSWER(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	pclHelperManager->DelAnswer( pclchar );
}


void cltServer::DoMsg_GAMEMSG_REQUEST_ELIXIR_NPC_ITEM_TYPE_LIST_GET(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Elixir_Npc_Item_Type_List_Get* pclInfo = (cltGameMsgRequest_Elixir_Npc_Item_Type_List_Get*)pclMsg->cData;

	
	cltMarketManager*		pMarketManager =  pclMarketManager; 
	if( NULL == pMarketManager ) return;
	cltItemManagerClient*	pclitemmanager = (cltItemManagerClient*)pclItemManager;
	if( NULL == pclitemmanager ) return;

	cltItemInfo* pItemInfo		= NULL;
	SI32		 siItemUnique	= 0;

	//SI32	siNPCPriceRate		= pclItemManager->clItemStatistic.siNPCPriceRate   ? pclItemManager->clItemStatistic.siNPCPriceRate   : 1;
	//SI32	siItemPriceIndex	= pclItemManager->clItemStatistic.siItemPriceIndex ? pclItemManager->clItemStatistic.siItemPriceIndex : 1;

	GMONEY	siChangeItemPrice	= 0;
	GMONEY	siSilverOrePrice	= 0;
	
	SI32	siTotalGiveItemNum	= 0;
	SI16	siEquipLevel		= 0;

	SI32	siListCount = 0;										// ����Ʈ ī��Ʈ.
    cltGameMsgResponse_Elixir_Npc_Item_Type_List_Get	SendMsg;	// Ŭ�� ������ ��Ŷ.
	
	// �޺� �ڽ��� �������� ������ �����Ѵ�. 
	 for( SI32  i = 0; i < MAX_ITEMINFO_NUMBER; i++ )
	{	
		pItemInfo = pclitemmanager->pclItemInfo[i];
		if( NULL == pItemInfo)											continue;
		if( false == pItemInfo->IsItemInfoAtb(ITEMINFOATB_SHOWLIST) )	continue;
		if(pItemInfo->siType != pclInfo->m_siItemType)					continue;

		siItemUnique = pclClient->pclItemManager->FindUniqueFromName( pItemInfo->GetName() );
		if( 0 >= siItemUnique )							continue;
		
		//siEquipLevel = pItemInfo->clItem.GetEquipLevel( pclClient->pclItemManager );
		//siTotalGiveItemNum = m_pclElixirManager->m_MasicalNostrum[siEquipLevel].m_siNum;

		siChangeItemPrice	= pclItemManager->GetCurrentPrice( ITEMUNIQUE(siItemUnique) )->siPrice ? pclItemManager->GetCurrentPrice( ITEMUNIQUE(siItemUnique) )->siPrice : 1;
		siSilverOrePrice	= pclItemManager->GetCurrentPrice( ITEMUNIQUE(5050) )->siPrice ? pclItemManager->GetCurrentPrice( ITEMUNIQUE(5050) )->siPrice : 1;
		siTotalGiveItemNum  = siChangeItemPrice / (siSilverOrePrice * 2);

		
		siTotalGiveItemNum = min( 10000, siTotalGiveItemNum );
		siTotalGiveItemNum = max( 0,	 siTotalGiveItemNum );

		SendMsg.m_siItemUnique[siListCount] = siItemUnique;
		SendMsg.m_siWaterNum[siListCount]   = siTotalGiveItemNum;
												   
		++siListCount;
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_ELIXIR_NPC_ITEM_TYPE_LIST_GET, sizeof(SendMsg), (BYTE*)&SendMsg);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ELIXIR_NPC_CHANGE_ITEM(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )	return;

	// �κ��� ������ �־ ������ ������ �Ұ����� ��� ��ȯ�� ���н���~.
	if( false == pclchar->IsBlankInv( 1, INVMODE_ALL ) ) 
	{
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_GACHA_FAIL_FULLINVEN, 0, 0, pclchar->GetID());
		return;
	}

	cltGameMsgRequest_Elixir_Npc_Change_Item* pclInfo = (cltGameMsgRequest_Elixir_Npc_Change_Item*)pclMsg->cData;

	if( 0 >= pclInfo->m_siItemUnique )	return;	
	if( pclInfo->m_siItemUnique != pclchar->pclCI->clCharItem.clItem[ pclInfo->m_siItemPos ].siUnique ) return;
	
	//SI32	siNPCPriceRate		= pclItemManager->clItemStatistic.siNPCPriceRate   ? pclItemManager->clItemStatistic.siNPCPriceRate   : 1;
	
	/*
	cltItemInfo* pItemInfo		= NULL;
	pItemInfo = pclItemManager->pclItemInfo[pclItemManager->FindItemRefFromUnique(pclInfo->m_siItemUnique)];
	siEquipLevel = pItemInfo->clItem.GetEquipLevel( pclClient->pclItemManager );
	siTotalGiveItemNum = m_pclElixirManager->m_MasicalNostrum[siEquipLevel].m_siNum;
	*/
	
	GMONEY	siChangeItemPrice	= pclItemManager->GetCurrentPrice( ITEMUNIQUE(pclInfo->m_siItemUnique) )->siPrice ? pclItemManager->GetCurrentPrice( ITEMUNIQUE(pclInfo->m_siItemUnique) )->siPrice : 1;
	GMONEY	siSilverOrePrice	= pclItemManager->GetCurrentPrice( ITEMUNIQUE(5050) )->siPrice ? pclItemManager->GetCurrentPrice( ITEMUNIQUE(5050) )->siPrice : 1;

	SI32	siTotalGiveItemNum	= 0;
	SI16	siEquipLevel		= 0;
	siTotalGiveItemNum = siChangeItemPrice / (siSilverOrePrice * 2);
	



	// ��ȯ�ؼ� �������� ���޵Ǵ� �������� 10000���� ���� ���ϰ���~����
	siTotalGiveItemNum = min( 10000, siTotalGiveItemNum );

	if( 0 >= siTotalGiveItemNum )
	{
		SendServerResponseMsg(0, SRVAL_ELIXIR_CHARGE_ITEM_NUM_ZERO_FAIL, 0, 0, pclchar->GetCharUnique());
		return;
	}

	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclInfo->m_siItemUnique );
	if( 0 < ref )  
	{
		if( NULL != pclClient->pclItemManager->pclItemInfo[ref] )
		{
			// ������ ��� �ֱ�.
			pclchar->GiveItem(  ITEMUNIQUE(2789), 
								siTotalGiveItemNum, 
								INPUTITEMPERSON_OPTION_ELIXIR_CHANGE_ITEM, 
								pclClient->pclItemManager->pclItemInfo[ref]->clItem.uiDateUseDay );

			pclItemManager->AddMagicalNostrumNum( pclchar->pclCI->clCharItem.clItem[ pclInfo->m_siItemPos ].siUnique, siTotalGiveItemNum );
		
			
			// ��ȯ�Ǵ� ��� ����.
			sDBRequest_UseItem useitem(	id,
										pclCM->CR[id]->pclCI->GetPersonID(),
										pclInfo->m_siItemPos,
										&pclchar->pclCI->clCharItem.clItem[ pclInfo->m_siItemPos ], 
										USEITEM_REASON_ELIXIR_CHANGE_ITEM								);

			pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

			pclItemManager->AddElixirNum( pclchar->pclCI->clCharItem.clItem[ pclInfo->m_siItemPos ].siUnique, 1 );	
			
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ELIXIR_SET(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer( id );
	if ( NULL == pclchar )	return;

	cltGameMsgRequest_Elixir_Set* pclInfo = (cltGameMsgRequest_Elixir_Set*)pclMsg->cData;

	bool			bUseItem = false;
	cltElixir_Info  clElixirInfo;

	// �������� ó�� ����ϴ� ���̸� �������ͽ� ���� �ܿ� ������ ����� �ʿ��ϰŵ�~ ^^
	if( pclInfo->m_bElixirStart )
	{
		bUseItem = true;	// ó�� �������� ����ϸ� �������� �Ҹ�Ǿ� �������� ���õȴ�.

		// ó�� ����ϴ°ǵ� �������� ���õ� ������ ����.
		//if( 0 < pclchar->pcltElixir->GetMultiple() || 0 < pclchar->pcltElixir->GetPoint() )	return;

		if( 0 >= pclInfo->m_siElixirItemUnique || 0 >= pclInfo->m_siWaterItemUnique )	return;	
		
		// �ش� ��ġ�� ������ ����ũ Ȯ��.
		if( pclInfo->m_siElixirItemUnique != pclchar->pclCI->clCharItem.clItem[pclInfo->m_siElixirItemPos].siUnique ) return;
		if( pclInfo->m_siWaterItemUnique  != pclchar->pclCI->clCharItem.clItem[pclInfo->m_siWaterItemPos].siUnique  ) return;

		if(	   0						 >= pclInfo->m_pcltElixirInfo.m_uiMultiple	 
			|| cltElixir::LIMIT_MULTIPLE <  pclInfo->m_pcltElixirInfo.m_uiMultiple )	return;

		// ������ ��� ��뷮�� Ŭ��� ���Ѵ�.
		SI32 siUseWaterNum = min( 10000, pclInfo->m_pcltElixirInfo.m_uiMultiple * pclchar->pclCI->clIP.GetLevel() * cltElixir::WATER_MILTIPLE );
		if( pclInfo->m_siWaterItemNum != siUseWaterNum )	return;


		// ������ ����� ������ �ð� ���ϱ�.
		cltDate clEndDate;
		clEndDate.Set( &pclTime->clDate );

		switch( pclInfo->m_siElixirItemUnique )
		{
			case ITEMUNIQUE(13634):	clEndDate.AddMonth(12);	break;

			default:	return;	// �ش� �������� �ƴϸ� ����.
		}
		
		clElixirInfo.m_uiMultiple	   = pclInfo->m_pcltElixirInfo.m_uiMultiple;
		clElixirInfo.m_siPoint		   = pclInfo->m_pcltElixirInfo.m_uiMultiple * pclchar->pclCI->clIP.GetLevel();	
		clElixirInfo.m_siEndMinuteVary = clEndDate.GetMinuteVary();
	}
	// ó���� �ƴϸ� �Ŀ��� �������ͽ��� ����.
	else 
	{
		// ���� ��� ������ �ٸ��ٸ� ����.
		//if( pclchar->pcltElixir->GetMultiple() != pclInfo->m_pcltElixirInfo.m_uiMultiple )	return;

		// ��ü ����Ʈ ���� �ٸ��� ����.
		//if( pclInfo->m_pcltElixirInfo.GetTotalPoint() != pclchar->pcltElixir->GetTotalPoint() ) return;

		memcpy( &clElixirInfo, &pclInfo->m_pcltElixirInfo, sizeof(clElixirInfo) );
	}

	
	if(pclchar->pclCI->GetPersonID() > 0)
	{
		sDBRequest_Elixir_Set clMsg(id, 
									pclchar->pclCI->GetPersonID(),
									&clElixirInfo,
									pclInfo->m_siElixirItemPos,	
									pclInfo->m_siElixirItemUnique,
									pclInfo->m_siWaterItemPos,
									pclInfo->m_siWaterItemUnique,
									pclInfo->m_siWaterItemNum,
									bUseItem							);	

		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_BALANCECANUSECURRENCY(cltMsg* pclMsg, SI32 id)
{
	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )	return;

	cltGameMsgResponse_BalanceCanUseCurrency clinfo(m_pclBalanceCurrencyMgr->GetCanUseMoney());
	cltMsg clMsg(GAMEMSG_RESPONSE_BALANCECANUSECURRENCY, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);



	//	[��ȣ_TEST] - ���� ���� ��밡����ȭ �� Ȯ���ϱ�����
	//cltCharServer* pclBalanceCurrencyChar = pclCM->GetCharServer(m_pclBalanceCurrencyMgr->GetBalanceCurrencyNPC_ID());

	//if(pclBalanceCurrencyChar == NULL) 
	//	return;

	//NTCHARString256 strCanUseMoney;
	//g_JYLibFunction.SetNumUnit(m_pclBalanceCurrencyMgr->GetCanUseMoney(),strCanUseMoney, 256);

	//cltGameMsgResponse_Chat clChat( pclBalanceCurrencyChar->GetCharUnique(), CHATMODE_NORMAL, (TCHAR*)pclBalanceCurrencyChar->GetName(), strCanUseMoney);
	//cltMsg clMsg1(GAMEMSG_RESPONSE_CHAT, clChat.siDataSize, (BYTE*)&clChat);

	//// ���� �ʿ� �ִ� ��� ĳ���� �鿡�� �޽����� ������
	//pclCM->SendAllPersonInMapMsg( (sPacketHeader*)&clMsg1, MAPINDEX_PRIVATEMARKETAREA);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PROMOTER_WARP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PromoterWarp* pclInfo = (cltGameMsgRequest_PromoterWarp*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if ( NULL == pclChar )	return;

	SI32 siID = pclCM->GetIDFromName( pclInfo->m_szName );
	cltCharServer* pclTargetChar = pclCM->GetCharServer( siID );
	if( NULL == pclTargetChar ) return;

	// ������ �����ϱ�
	cltWarpInfo clWarpInfo( 1, pclTargetChar->GetMapIndex(), false, false, pclTargetChar->GetX(), pclTargetChar->GetY(), -1, -1 );
	pclChar->SetWarpInfo( &clWarpInfo, 7777 );
	pclChar->Warp();

}

void cltServer::DoMsg_GAMEMSG_REQUEST_FESTIVAL_EVENT_ENTERFIELD_EVENTAREA(cltMsg* pclMsg, SI32 id)
{
	SI32 siID = id;

	if ( false == pclCM->IsValidID(siID) )
	{
		return;
	}

	// �ɸ��� ����Ʈ �ޱ�
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siID];
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 siPersonID = pclchar->pclCI->GetPersonID();

	// ���� ������ ��
	SI32		siWarpX = 70;
	SI32		siWarpY = 60;
   
	cltWarpInfo clWarpPollMap(1, MAPINDEX_FESTIVAL, true, false, siWarpX, siWarpY, -1, -1);

	pclchar->SetWarpInfo( &clWarpPollMap, 905 );
	pclchar->Warp();

}
//-------------------------------------------------------------------------------------------------------------------
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
//-------------------------------------------------------------------------------------------------------------------
//enum
//{
//	GOONZU_KINGGURI_SAMETIME = 0,		// 3Ÿ���� ���� Ÿ���� �ִ�
//	GOONZU_KINGGURI_NOTOVERTIME,		// 24�ð��� ������ ���� ���� �ߴ�
//	GOONZU_KINGGURI_NOTENOUGHDATA,		// 3Ÿ���� ��� ���� ���� �ʾҴ�.
//	GOONZU_KINGGURI_CORRECTDATA,		// ���� ������ 
//};
void cltServer::DoMsg_GAMEMSG_REQUEST_RACCOONEVENT_TOGOONZU(cltMsg* pclMsg, SI32 id)
{
	// �����͸� ���� �Ѵ� .
	cltGameMsgRequest_SetRaccoonEventToGoonzu* pclInfo = (cltGameMsgRequest_SetRaccoonEventToGoonzu*)pclMsg->cData;

	if(pclInfo == NULL)	return	;
	// �ź� üũ
	cltCharServer* pCharServer = pclCM->GetCharServer(id)	;	
	if(pCharServer->pclCI->clBI.uiGRank != GRANK_KING)	return	;	// ���ָ� �Ҽ� �ִ�.

	// 3Ÿ�� ��� ������ �Ǿ� �ִ��� üũ
	// ������ ���� Ÿ������ ���� �Ϸ簡 �������� üũ
	// ���� �ð��� �ִ��� üũ
	// ���� Ÿ���� �ð��� �ֳ�?

	SI32 siReval = pclGoonzuKingGuriEventManager->ChekData(pclInfo->m_GoonzuRaccoonEventData )	;
	switch( siReval ) 
	{
	case CGoonzuKingGuriEvent::GOONZU_KINGGURI_NOTENOUGHDATA:// 3Ÿ���� ��� ���� ���� �ʾҴ�.
		{
			SI32 returnval = SRVAL_FAIL_EVENTSET_NOT_ENOUGH_TIME;	// 3Ÿ���� ��� ���� ���� �ʾҴ�.
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		}
		break;
	case CGoonzuKingGuriEvent::GOONZU_KINGGURI_NOTOVERTIME:// 24�ð��� ������ ���� ���� �ߴ�
		{
			SI32 returnval = SRVAL_FAIL_EVENTSET_NOT_OVER_LIMITTIME;	// 24�ð��� ������ ���� ���� �ߴ�
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		}
		break;
	case CGoonzuKingGuriEvent::GOONZU_KINGGURI_SAMETIME :	
		{
			SI32 returnval = SRVAL_FAIL_EVENTSET_SAMETIME;	// ���� �ð��� �ִ�
			SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
		}
		break;
	}
	if ( siReval == CGoonzuKingGuriEvent::GOONZU_KINGGURI_CORRECTDATA) 
	{
		SI32 siSetCount =	0	;
		for (SI32 i = 0 ; i < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; i++ ) 
		{
			if (  i >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT) break;

			SI32 siTime = pclInfo->m_GoonzuRaccoonEventData[i].GetTime()	;
			SI32 siMonsterNum = pclInfo->m_GoonzuRaccoonEventData[i].GetMonsterNum()	;
			if(siTime < 0 )	continue	;
			if(siMonsterNum <= 0 )	continue	;
			pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetTime(siTime)	;
			pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].SetMakeMonsterNum(siMonsterNum)	;
			siSetCount	=	0	;
			for ( SI32 siFiledIndex = 0 ; siFiledIndex < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ;siFiledIndex++ ) 
			{
				siSetCount++;
				if(siMonsterNum < siSetCount)	continue	;

				SI32 siMapindex = pclInfo->m_GoonzuRaccoonEventData[i].GetRocIndex(siFiledIndex)	;
				if(siMapindex <= 0  )	continue	;
				SI32 siX = pclInfo->m_GoonzuRaccoonEventData[i].GetRocX(siFiledIndex)	;
				SI32 siY = pclInfo->m_GoonzuRaccoonEventData[i].GetRocY(siFiledIndex)	;
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
		// �Ϸ��ߴٴ� �޼����� ������ .
		pclGoonzuKingGuriEventManager->LsatsetTime = sTime	;	// ������ �û��� �����Ѵ� 

		SI32 returnval = SRVAL_SUCCES_SET_GOONZURACCOONEVENT;	// ���������� �����ߴٰ� Ŭ���̾�Ʈ�� �޼����� ������.
		SendServerResponseMsg( 0, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );

		// ��� ���� �ϰ� ���� �޼����� ������ .
		sDBRequest_GoonzuRaccoonEvent_SaveInfo	clMsg( pclGoonzuKingGuriEventManager->LsatsetTime ,pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData );
		pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GOONZURACCOONEVENT_SETINFO(cltMsg* pclMsg, SI32 id)
{
	// ���� ������ �����͸� ������ �´� 
	cltGameMsgRequest_GoonzuRaccoonEventInfo* pclInfo = (cltGameMsgRequest_GoonzuRaccoonEventInfo*)pclMsg->cData;

	if(pclInfo == NULL)	return	;

	cGoonzuRaccoonEventData SendGoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT]		;	// ���� ������

	SI32 siSetCount =	0	;
	for (SI32 i = 0 ; i < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT; i++ ) 
	{
		if (  i >= MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT) break;

		SI32 siTime = pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].GetTime()	;
		SI32 siMonsterNum = pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].GetMonsterNum()	;		
		if(siTime < 0 || siTime > MAX_HOUR_GOONZURACCOONEVENT )	continue	;
		if(siMonsterNum <= 0 || siMonsterNum > MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT )	continue	;
		SendGoonzuRaccoonEventData[i].SetTime(siTime)	;
		SendGoonzuRaccoonEventData[i].SetMakeMonsterNum(siMonsterNum)	;
		siSetCount = 0 ;
		for ( SI32 siFiledIndex = 0 ; siFiledIndex < MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT ;siFiledIndex++ ) 
		{
			siSetCount++;
			if(siMonsterNum < siSetCount)	continue	;
			SI32 SiMapindex = pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].GetRocIndex(siFiledIndex)	;
			if(SiMapindex <	0	)	continue	;
			SI32 siX = pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].GetRocX(siFiledIndex)	;
			SI32 siY =pclGoonzuKingGuriEventManager->GoonzuRaccoonEventData[i].GetRocY(siFiledIndex)	;
			if ( siX < 0 || siY < 0   )
			{
				siX	=	0	;
				siY 	=	0	;
			}
			SendGoonzuRaccoonEventData[i].SetMapIndex(siFiledIndex,  SiMapindex )	;
			SendGoonzuRaccoonEventData[i].SetMapRocX(siFiledIndex, siX)	;
			SendGoonzuRaccoonEventData[i].SetMapRocY(siFiledIndex, siY)	;
		}
	}
	cltGameMsgResponse_GoonzuRaccoonEventInfo clinfo(SendGoonzuRaccoonEventData);
	cltMsg clMsg(GAMEMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GORACCOONWORLD(cltMsg* pclMsg, SI32 id)
{
	if(pclClient->IsCountrySwitch( Switch_Go_RaccoonWorld )	==	false)	return	;
	cltGameMsgRequest_GoRaccoonWorld* pclInfo = (cltGameMsgRequest_GoRaccoonWorld*)pclMsg->cData;

	 cltCharServer* pclCharServer = pclCM->GetCharServer( id )	;	 if(pclCharServer == NULL )	return	;

	 if(pclCM->IsAlive( id ) == false )	return	;

	 if(IsWhereServiceArea( ConstServiceArea_Korea ) )
	 {
		 if(pclCharServer->pclCI->clBI.m_uiRealAge < 18)
		 {
			 // 18���� �ȵǸ� �Ұ�
			 SI32 returnval = SRVAL_FAIL_GORACCOONWORLD_UNDER_18;	// ���� �ð��� �ִ�
			 SendServerResponseMsg( 0, returnval,  0, 0, pclCharServer->GetCharUnique() );
			 return	;
		 }
	 }
	 // ���� ���� ���ϴ� ��Ȳ üũ 
	 if(pclCharServer->CanWarpFrom() == false )		return	;
	 if( pclCharServer->bPersonalShopSwitch == true || pclCharServer->bPremiumPersonalShop == true)	return	;

	 cltWarpInfo	clWarpInfo(1, MAPINDEX_FESTIVAL, true, false, 133 ,168 , -1,  -1)	;
	 pclCharServer->SetWarpInfo(&clWarpInfo, 3000);
	 pclCharServer->Warp();

}
void cltServer::DoMsg_GAMEMSG_REQUEST_PVPMAPWARP(cltMsg* pclMsg,SI32 id)
{
	cltGameMsgRequest_HuntMapWarp* pclInfo = (cltGameMsgRequest_HuntMapWarp*)pclMsg->cData;

	if( pclCM->IsAlive( id ) == false )											return;
	if( pclInfo->siMapIndex <= 0 || pclInfo->siMapIndex >= MAX_MAP_NUMBER )		return;
	if( pclMapManager->pclMapArray[pclInfo->siMapIndex] == NULL )				return;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclChar == NULL )
	{
		return;
	}

	// ĳ������ ���¿� ���� ������ �Ұ����ϴ�.
	if( pclChar->CanWarpFrom() == false )						return;

	//// ���� �ϰ��� �ϴ� �ʿ� ���� ������ �Ұ����ϴ�.
	//if( pclChar->CanWarpTo( pclInfo->siMapIndex ) == false )	return;

	// ��¥���� ���� ����
	bool bNoLimitWarp = pclChar->CanFreeWarp( pclInfo->siMapIndex );


	// ������ �����ΰ�?
	bool bVillageWarp = false;
	if ( pclInfo->siMapIndex > 0 && pclInfo->siMapIndex <= CUR_VILLAGE_LIMIT )
	{
		if ( pclMapManager->pclVillageManager->IsValidVillage(pclInfo->siMapIndex) == true )
			bVillageWarp = true;
		else
			return ;
	}

	if( bVillageWarp == true)
	{
		if( pclVillageManager->IsAggressiveVillage( pclChar->pclCI->clBI.siHomeVillage, pclInfo->siMapIndex ) )
		{
			SendServerResponseMsg(0, SRVAL_CAN_NOT_WARP_IN_VILLAGEWAR, 0, 0, id);
			return;
		}
	}

	SI32 siWarpMode = HUNTMAPWARP_MODE_NONE;
	if( pclInfo->siWMoney == 0 )
	{
		siWarpMode = HUNTMAPWARP_MODE_USEITEM;
	}
	else
	{
		siWarpMode = HUNTMAPWARP_MODE_USEMONEY;
	}

	SI32 itemunique = ITEMUNIQUE(24000) ; // �����̵��̿��
	SI32 x = 0 , y = 0 ;
	SI32 warpunique = 0 ;

	SI32 itemNum = pclChar->pclCI->clCharItem.GetItemNum(itemunique);
	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);

	//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
	if(siWarpMode == HUNTMAPWARP_MODE_USEITEM) //����Ƽ������ ��ȯ�̶��.
	{
		// ��¥�̵��� �ƴѵ�, �������� ���ٸ� �̵� �Ұ���
		if( bNoLimitWarp == false )
		{
			if ( itemNum <= 0 || pos < 0 )		return ;
		}

		// ������ �ִ� �������� ����� �� ����.
		if( true == pclChar->bPersonalShopSwitch ||
			true == pclChar->bPremiumPersonalShop )
		{
			for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
			{
				if( pclChar->clShopData.m_clItem[i].siUnique == itemunique  )
				{
					if( pclChar->clShopData.m_clItem[i].siItemNum >= itemNum )
					{
						SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_USEITEM, 0, 0, id);
						return;
					}
				}
			}
		}
	}
	else if( siWarpMode == HUNTMAPWARP_MODE_USEMONEY )
	{
		GMONEY myMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();
		// �����ݺ��� ���� �ݾ��� ������ ������ �� ����.
		if( myMoney < pclInfo->siWMoney )
			return;
	}

	cltWarpInfo clWarpInfo(1, 0, false, true, x, y, -1, -1);

	if ( !bVillageWarp ) // ����ͷ� �̵�
	{
		const TCHAR * szMapName = pclMapManager->GetMapName(pclInfo->siMapIndex);

		// KHY - 1122 - �����̵� �̿�� ����.		
		if(pclInfo->m_bInMap == true)		// �ش� �� ������ ���� ���
		{
			if(pclInfo->siMapIndex == 300 )
			{
				if (pclMapManager->pclGateManager->FindImportantPos( pclInfo->siMapIndex, &x, &y ) == false )
					return ;

				clWarpInfo.uiMapIndex = pclInfo->siMapIndex;
				// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
				clWarpInfo.uiX = 5+2;
				clWarpInfo.uiY = 97+2;
			}
			else
			{
				if (pclMapManager->pclGateManager->FindImportantPos( pclInfo->siMapIndex, &x, &y ) == false )
					return ;

				clWarpInfo.uiMapIndex = pclInfo->siMapIndex;
				// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
				clWarpInfo.uiX = x+2;
				clWarpInfo.uiY = y+2;
				
			}
		}
		else
		{
			if (pclMapManager->pclGateManager->FindMainFieldPos( pclInfo->siMapIndex, &x, &y ) == false )
				return;

			clWarpInfo.uiMapIndex = 0; //������ ���� �� ���´�.
			// ����Ʈ���� �ణ ������ ������ �̵� - [TYS]
			clWarpInfo.uiX = x+2;
			clWarpInfo.uiY = y+2;

		}
		warpunique = 2200 ;
	}
	else // ������ �̵�
	{
		SI32 maptypeunique	= pclMapManager->pclMapArray[pclInfo->siMapIndex]->siMapUnique;
		x = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterX;
		y = pclMapManager->pclMapTypeManager->pclMapTypeInfo[maptypeunique]->siCenterY;

		if ( maptypeunique < 0 || x < 0 || y < 0 ) return ;

		clWarpInfo.uiMapIndex = pclInfo->siMapIndex;
		clWarpInfo.uiX = x;
		clWarpInfo.uiY = y;

		warpunique = 2300 ;
	}

	if(id)
	{
		OrderStop(id, BY_COMPUTER);

		// ���� ������ ����Ʈ�� ǥ���Ѵ�. 
		cltGameMsgResponse_WarpEffect clinfo(id);
		cltMsg clMsg(GAMEMSG_RESPONSE_WARPEFFECT, sizeof(clinfo), (BYTE*)&clinfo);
		((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg(&clMsg, true);

		// �����̵��̿���� ����Ͽ� ������ �̵��ϱ� ����Ʈ���̶��, 
		if(pclInfo->siMapIndex < MAX_VILLAGE_NUMBER)
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET1);
		}
		// �����̵��̿���� ����Ͽ� ����ͷ� �̵��ϱ� ����Ʈ���̶��, 
		else
		{
			pclCM->CR[id]->DoQuestCheckAndAction(QUEST_CLEAR_COND_USEWARPTICKET2);
		}

		//���� Ÿ�� pvp ����.


		pclChar->SetWarpInfo(&clWarpInfo, warpunique);
		if ( pclChar->Warp() == TRUE )
		{
			//KHY - 0703 - ���� �ӴϷ� ��ȯ�ϱ�.Ŭ���� ����.
			if ( siWarpMode == HUNTMAPWARP_MODE_USEITEM )
			{
				if( bNoLimitWarp == false)
				{
					// ��踦 ����. 
					pclItemManager->AddUseNum(itemunique, 1);

					// ���ο� ��� - ������ ���
					//NStatistics_Add("Item", itemunique, "UseNum", 1);

					// �����̵��̿���� �Һ��Ѵ�.
					//////////////////////////////////////////////////////////////////////////
					cltItem clItem;
					clItem.Init();
					clItem.siUnique = itemunique;
					clItem.siItemNum = 1;

					SI32 FromPersonID = pclCM->CR[id]->pclCI->GetPersonID();
					sDBRequest_UseItem clMsg( id, FromPersonID, pos, &clItem ,USEITEM_REASON_TICKET);
					SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
					//////////////////////////////////////////////////////////////////////////
				}
			}
			else if( siWarpMode == HUNTMAPWARP_MODE_USEMONEY )
			{
				SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

				if(personid)
				{
					sDBRequest_ChangeMoney clMsg(id, personid, CHANGE_MONEY_REASON_MONEY_WARP, -(pclInfo->siWMoney));
					pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

					pclDelMoneyStatistics->Add(DELMONEY_WARP, pclInfo->siWMoney);
				}
			}
		}
	}
}


