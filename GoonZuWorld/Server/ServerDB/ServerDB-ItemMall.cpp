//---------------------------------
// 2004/07/26 ���ؿ�
//---------------------------------

#include "Char\CharManager\CharManager.h"

#include "../Server/Server.h"

#include "../../Common/Map/Map.h"
#include "../../Common/Order/Order.h"
#include "../../Common/Event/Event.h"

#include "../../../Server/AuthServer/AuthMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"
#include "Skill/Skill-Manager.h"

#include "MsgType-Person.h"
#include "MsgType-Item.h"
#include "MsgRval-Define.h"
#include "Msg/MsgType-ItemMall.h"

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALLEXISTENCE(sPacketHeader* pPacket)
{
	sDBResponse_ItemMallExistence* pclMsg = (sDBResponse_ItemMallExistence*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 )							return ;
	if ( pclCM->IsValidID(id) == false)		return ;
	if ( id != pclMsg->usCharID )			return ;

	if ( pclMsg->siResult == 0 || pclMsg->siPersonID <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_DBFAIL,  0, 0, id);
		return ;
	}
/*
#ifdef _DEBUG
	pclMsg->bExistence = false ;
#endif
*/
	pclCM->CR[id]->pclCI->clItemMall.Init();
	pclCM->CR[id]->pclCI->clItemMall.SetExistence(pclMsg->bExistence);

	// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
	cltGameMsgResponse_ItemMallExistence clinfo(pclMsg->bExistence);
	cltMsg clMsg(GAMEMSG_RESPONSE_ITEMMALLEXISTENCE, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return ;
}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALLITEMLIST(sPacketHeader* pPacket)
{
	sDBResponse_ItemMallItemList* pclMsg = (sDBResponse_ItemMallItemList*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 )							return ;
	if ( pclCM->IsValidID(id) == false )	return ;
	if ( id != pclMsg->usCharID )			return ;

	if ( pclMsg->siPersonID <= 0 )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_DBFAIL,  0, 0, id);
		return ;
	}

	
	cltItem pclitem[MAX_ITEMNUM_PER_ITEMMALL];
	if ( pclMsg->siResult == 0 )
	{
		pclCM->CR[id]->pclCI->clItemMall.Init();
	}
	else
	{
		for ( int i = 0 ; i < MAX_ITEMNUM_PER_ITEMMALL ; i ++ )
		{
			SI16 brareswitch = 0;
			pclitem[i].Init();
			pclitem[i].Set(&pclMsg->clItem[i]);
			if( pclItemManager->MakeRandItemUnique( pclMsg->clItem[i].siUnique, &pclitem[i], 0, 0, &brareswitch) )
			{
				pclitem[i].SetItemNum(pclMsg->clItem[i].siItemNum) ;
				if ( pclMsg->clItem[i].uiDateUseDay > 0 )
					pclitem[i].uiDateUseDay = pclMsg->clItem[i].uiDateUseDay ;// + 1 ;
				pclMsg->clItem[i].Set(&pclitem[i]);
			}
		}

		pclCM->CR[id]->pclCI->clItemMall.SetItem(pclitem);

		pclCM->CR[id]->pclCI->clItemMall.SetItemID(pclMsg->siItemID);

		pclCM->CR[id]->pclCI->clItemMall.SetTotalItemNum(pclMsg->siTotalItemNum);
		pclCM->CR[id]->pclCI->clItemMall.SetListPage(pclMsg->siListPage);
	}

	// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
	cltGameMsgResponse_ItemMallItemList clinfo(pclMsg->clItem,pclMsg->siItemID,pclMsg->siTotalItemNum,pclMsg->siListPage);
	cltMsg clMsg(GAMEMSG_RESPONSE_ITEMMALLITEMLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return ;
}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALLGETITEM(sPacketHeader* pPacket)
{
	sDBResponse_ItemMallGetItem* pclMsg = (sDBResponse_ItemMallGetItem*)pPacket;

	if ( pclMsg->siResult != 1 ) return ;
	if ( pclMsg->siPersonID <= 0 ) return ;	
	if ( pclMsg->siInvPos < 0 || pclMsg->siInvPos > MAX_ITEM_PER_PERSON )	return;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false )	return ;
	if ( id != pclMsg->usCharID ) return ;


	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if( NULL == pclChar)
		return;

	if ( pclMsg->clItem.siUnique <= 0 || pclMsg->clItem.siItemNum <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,0,0,id);
		return ;
	}
	if ( pclChar->pclCI->clCharItem.clItem[pclMsg->siInvPos].siUnique > 0 &&
		 pclItemManager->CanPile(pclMsg->clItem.siUnique) == false )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,1,0,id);
		return ;
	}

	if ( pclItemManager->CanPile(pclMsg->clItem.siUnique) == false && pclMsg->clItem.GetItemNum() != 1 )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,  0, 0, id);
		return ;
	}

	// ������ �޾ƿ� �Ϸ�
	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	SI32 siGetItemNum = pclMsg->clItem.GetItemNum() - pclChar->pclCI->clCharItem.clItem[pclMsg->siInvPos].GetItemNum();

	cltItem clGetItem;
	clGetItem.Set(&pclMsg->clItem);
	clGetItem.SetItemNum(siGetItemNum);

	// ��踦 ����.
	pclItemManager->AddMallItemNum(pclMsg->clItem.siUnique,siGetItemNum);

	// ���ο� ��� - �����۸����� ���� ��ǰ�� ��踦 ����.
	NStatistics_Add("Item", pclMsg->clItem.siUnique, "MallItemNum", pclMsg->clItem.GetItemNum());
	NStatistics_Set("Item", pclMsg->clItem.siUnique, "Name", pclItemManager->GetName(pclMsg->clItem.siUnique));

	// �����۸�  ����Ʈ ���̶��, 
	pclChar->DoQuestCheckAndAction(QUEST_CLEAR_COND_ITEMMALL);

	if ( pclMsg->bPossession )
	{
		pclChar->pclCI->clCharItem.clItem[pclMsg->siInvPos].Set(&pclMsg->clItem);
	}
	else if ( pclMsg->bPossession == false )
	{
		//if ( pclMsg->clItem.siUnique == 8250 ) // ������ ���� ó��
		//{
			//if ( pclChar->UseItem(pclMsg->clItem) == false )
		//		return ;
		//}
	}

	// Ŭ���̾�Ʈ�� �뺸�Ѵ�. 
	cltGameMsgResponse_ItemMallGetItem clinfo(pclMsg->siInvPos,&pclMsg->clItem);
	cltMsg clMsg(GAMEMSG_RESPONSE_ITEMMALLGETITEM, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		//// PCK - ������ ������ ����� �α� �߰���.
		//SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_GET_ITEM,
		//					 INPUTITEMPERSON_OPTION_ITEMMALL, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
		//					 pclMsg->siInvPos, 0, 0, 0, 0, NULL, NULL);

		// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ �� ����.
		// param1 == ������ ���̵�, param2 == ������ ����ũ
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ITEMMALL, LOGCOMMAND_INDEX_ITEMMALL_GET, 
							0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &clGetItem, pclMsg->clItem.GetItemNum(), 0, 0, 0, 0, 0, 
							pclMsg->siItemID, pclMsg->clItem.siUnique, 0, 0, 0, NULL, NULL);	
	}

	sDBRequest_PersonItemInfoGet clMsgToDB( id, pclMsg->siPersonID );
	pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsgToDB);

	/*
	// �����̵����ױ� ���ó��
	if ( pclMsg->clItem.siUnique == ITEMUNIQUE(14170) || pclMsg->clItem.siUnique == ITEMUNIQUE(14180) ||
		 pclMsg->clItem.siUnique == ITEMUNIQUE(14190) || pclMsg->clItem.siUnique == ITEMUNIQUE(14165) ||
		 pclMsg->clItem.siUnique == ITEMUNIQUE(14168) )
	{
		SI32 adddate = 0 ;

		switch(pclMsg->clItem.siUnique)
		{
		case ITEMUNIQUE(14190):
			{
				adddate = 900 ;
			}
			break;
		case ITEMUNIQUE(14180):
			{
				adddate = 420 ;
			}
			break;
		case ITEMUNIQUE(14170):
			{
				adddate = 210 ;
			}
			break;
		case ITEMUNIQUE(14165):
			{
				adddate = 30 ;
			}
			break;
		case ITEMUNIQUE(14168):
			{
				adddate = 90 ;
			}
			break;
		default:
			return ;
		}

		if ( pclChar->pclCI->clCharItem.GetItemNum(pclMsg->clItem.siUnique) <= 0 )
			return ;

		SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(pclMsg->clItem.siUnique);
		if(pos < 0)return ;

		SI32 datevary = 0 ;
		if ( pclChar->pclCI->clBI.bUseNoLimitTicketWarp )
		{
			datevary = pclChar->pclCI->clBI.siNoLimitTicketWarpDateVary + adddate * pclMsg->clItem.siItemNum ;
		}
		else
		{
			datevary = pclTime->clDate.GetDateVary() + adddate * pclMsg->clItem.siItemNum ;
		}

		sDBRequest_NoLimitTicket_Warp clMsg(true ,pclChar->GetID(), pclChar->pclCI->GetPersonID(), pos, &pclMsg->clItem,datevary);
		SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
	}
*/
	return ;
}

// �̸��� �����Ѵ�.
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGENAME(sPacketHeader* pPacket)
{
	sDBResponse_ChangeName* pclinfo = (sDBResponse_ChangeName*)pPacket;

	if(pclinfo->m_bUseItem == false)
	{
		// [��ȣ_NHN->NDOORS] �α��ν� ĳ���͸��� �����ϴ� ���
		//.....

		SI32 siCharID = pclinfo->siCharID;

		if ( pclCM->IsValidID(siCharID) == false )
			return ;

		if ( pclinfo->siResult == 1)
			pclCM->CR[siCharID]->pclCI->clBI.clPerson.SetName(pclinfo->szName);

		sDBRequest_PersonListInfoGet clMsg(siCharID, pclCM->CR[siCharID]->pclCI->clBI.siIDNum);
		pclGameDBProcess->SendMsg( DBSELECT_LOGIN, (sPacketHeader *)&clMsg);

		cltGameMsgResponse_ChangeCharName clinfo2(pclinfo->siResult,pclinfo->szName, pclinfo->m_bUseItem);
		cltMsg clMsg2(GAMEMSG_RESPONSE_CHANGE_CHARNAME, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclCM->CR[siCharID]->SendNetMsg((sPacketHeader*)&clMsg2);

		// [��ȣ_NHN->NDOORS] �̰��α�
		SendLog_WriteLogToDB(	LOGCOMMAND_TYPE_CHARACTOR, 
								LOGCOMMAND_INDEX_CHARACTER_CHANGE_NAME, 
								CHANGENAME_REASON_SPECIALCHAR_CHANGENAME,
								(cltCharServer*)pclCM->CR[siCharID], 
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
								pclinfo->szName, 
								pclinfo->szOldName);

	}
	else
	{
		// �������� ����ؼ� ĳ���͸��� �����ϴ� ���
		//.....	

		SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
		if ( pclCM->IsValidID(id) == false )
			return ;

		if ( pclinfo->siResult == 1)
		{
			pclCM->CR[id]->pclCI->clBI.clPerson.SetName(pclinfo->szName);

			// ��迡 �߰��Ѵ�. 
			SI32 itemunique = ITEMUNIQUE(24114) ; // �̸������̿��
			pclItemManager->AddUseNum( itemunique, 1);

			// ���ο� ���
			//NStatistics_Add("Item", itemunique, "UseNum", 1);
		}

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclinfo->clitem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		cltGameMsgResponse_ChangeCharName clinfo2(pclinfo->siResult,pclinfo->szName, pclinfo->m_bUseItem);
		cltMsg clMsg2(GAMEMSG_RESPONSE_CHANGE_CHARNAME, sizeof(clinfo2), (BYTE*)&clinfo2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// PCK - �����ۻ���� �Ҷ� ������ ��� �α׵� ���� �����ش�.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
				USEITEM_REASON_CHANGENAME, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclinfo->clitem_Log, 0, 
				0, 0, 0, 0, 0, 
				pclinfo->siPos, 0, 0, 0, 0, NULL, NULL);

			// [�α��߰� : Ȳ���� 2007. 10. 9] // �̸� ���� ��볻��.(�����۵� ������?)
			// param2== ������ ����ũ, pszParam1 == �̸�
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_CHANGE_NAME, 
				0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				0, pclinfo->clitem_Log.siUnique, 0, 0, 0, pclinfo->szName, NULL);
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_CHANGE_CHARKIND(sPacketHeader* pPacket)
{
	sDBResponse_Change_CharKind* pclinfo = (sDBResponse_Change_CharKind*)pPacket;

	if( pclinfo->siKind < 0 || pclinfo->siKind >= MAX_KIND_NUMBER )			return;

	SI32 id = pclCM->GetIDFromPersonID(pclinfo->siPersonID);
	if ( pclCM->IsValidID(id) == false )
		return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0)return ;

	if ( pclinfo->siKind <= 0 || pclinfo->siKind >= KIND_SYSTEM ) return ;
	if ( pclKindInfoSet->pclKI[pclinfo->siKind] == NULL ) return ;

	if ( pclinfo->siResult == 1)
	{
		if ( pclchar->pclCI->clBI.GetKind() == pclinfo->siKind ) return ;

		pclchar->pclCI->clBI.SetKind(pclinfo->siKind);

		// ��迡 �߰��Ѵ�. 
		SI32 itemunique = ITEMUNIQUE(24070) ; // ĳ���ͺ����̿��
		pclItemManager->AddUseNum( itemunique, 1);

		//���ο� ���
		//NStatistics_Add("Item", itemunique, "UseNum", 1);
	}
	else return ;

	// ĳ���͸� �ٽ� �ε��ϱ� ���� �溹������ ������.
	OrderStop(id, BY_COMPUTER);

	cltWarpInfo clWarpInfo(1, MAPINDEX_PALACE, false, false, 27, 87, -1, -1);
	pclchar->SetWarpInfo(&clWarpInfo, 1900);

	// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
	cltGameMsgResponse_PersonItemInfo clinfo(pclinfo->siPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclinfo->clitem, 0);
	cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg);

	cltGameMsgResponse_Change_CharKind clinfo2(pclinfo->siResult,pclinfo->siKind);
	cltMsg clMsg2(GAMEMSG_RESPONSE_CHANGE_CHARKIND, sizeof(clinfo2), (BYTE*)&clinfo2);
	pclchar->SendNetMsg((sPacketHeader*)&clMsg2);

	if ( pclinfo->siResult == 1)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			cltServer * pclserver = (cltServer*)pclClient;

			// PCK - �����ۻ���� �Ҷ� ������ ��� �α׵� ���� �����ش�.
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_USE_ITEM,
											USEITEM_REASON_CHANGECHARKIND, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, 
											&pclinfo->clitem_Log, 0, 0, 0, 0, 0, 0, pclinfo->siPos, 0, 0, 0, 0, NULL, NULL);

			// [�α��߰� : Ȳ���� 2007. 10. 5] // ĳ���� ���� ��볻��.
			// param1 == ���
			// param2 == ������ ����ũ
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_CHANGE_KIND, 
											0, (cltCharServer*)pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclinfo->siKind, pclinfo->clitem_Log.siUnique, 0, 0, 0, NULL, NULL);	
		}
	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_NEWSCHATADDMISSION(sPacketHeader* pPacket)
{
	sDBResponse_NewsChatAddmission* pclMsg = (sDBResponse_NewsChatAddmission*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( id != pclMsg->usCharID ) return ;
	if ( pclMsg->siResult != 1 || pclMsg->siPersonID <= 0 )
		return ;
	if ( pclCM->IsValidID(id) == FALSE ) return ;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	if ( pclchar == NULL )
		return;

	if( pclMsg->siInvPos >= 0 && pclMsg->siInvPos < MAX_ITEM_PER_PERSON )
	{
		// ������ ������ ������Ʈ�Ѵ�.
		pclchar->pclCI->clCharItem.clItem[ pclMsg->siInvPos].Set(&pclMsg->clItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siInvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclchar->SendNetMsg((sPacketHeader*)&clMsg);
	}

	TCHAR * pName = (TCHAR*)pclchar->GetName() ;

	SI32 captionKind = CAPTIONKIND_NEWSCHAT;
	SI32 sendKind    = CAPTIONKIND_NEWSCHAT;
    if( pclMsg->bUseColorNews )
	{
		captionKind = CAPTIONKIND_COLORNEWSCHAT;
	}

	PushSpecialNews( pclMsg->szChatText,pName, NULL, captionKind,sendKind);

	if ( IsWhereServiceArea(ConstSwitch_NewLog) ) 
	{
		// szparam1 == �ڸ����� ����1(49byte)
		// szparam2 == �ڸ����� ����2(49byte)
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_CHARACTOR, LOGCOMMAND_INDEX_CHARACTER_USESUBTITLE, 
									0, pclchar, NULL, 0, 0, 0, &pclMsg->clItem, 0, 0, 0, 0, 0, 0, 
									0, 0, 0, 0, 0, pclMsg->szChatText, &pclMsg->szChatText[49]);
	}
	

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_NOLIMITTICKET_WARP(sPacketHeader* pPacket)
{
	sDBResponse_NoLimitTicket_Warp* pclMsg = (sDBResponse_NoLimitTicket_Warp*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( id != pclMsg->usCharID ) return ;
	if ( pclMsg->siResult != 1 || pclMsg->siPersonID <= 0 )
		return ;
	if ( pclCM->IsValidID(id) == FALSE ) return ;

	cltCharServer* pclchar = pclCM->GetCharServer( id );

	// ������ ������� ���� ������ ���� ������Ʈ
	if ( pclMsg->bUsing )
	{
		if( pclMsg->siInvPos >= 0 && pclMsg->siInvPos < MAX_ITEM_PER_PERSON )
		{
			cltItem* pclItem = &pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siInvPos];

			if(NULL == pclItem)
				return;

			if(IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				cltItem clUsedItem;
				clUsedItem.Set(pclItem);
				clUsedItem.SetItemNum(1);

				cltDate clEndDate;
				clEndDate.MakeFullDateFromDateVary(pclMsg->siDateVary);

				TCHAR szEndDate[32] = {0,};	
				StringCchPrintf(szEndDate, 32, GetTxtFromMgr(1644), clEndDate.uiYear, clEndDate.uiMonth, clEndDate.uiDay );

				//param1 == �κ� ��ġ  param2 == ������ Ÿ�� charparam1 == ������ �ð�
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_PERSONITEM, LOGCOMMAND_INDEX_PERSONITEM_PREMIUMITEM_USE, 
					0, pclchar, NULL, 0, 0, 0, &clUsedItem, pclMsg->clItem.GetItemNum(), 0, 0, 0, 0, 0, 
					pclMsg->siInvPos, pclMsg->siType, 0, 0, 0, szEndDate, NULL);
			}

			// ��迡 �߰��Ѵ�. 
			pclItemManager->AddUseNum( pclItem->siUnique, 1);

			// ������ ������ ������Ʈ�Ѵ�.
			pclItem->Set(&pclMsg->clItem);

			// ���ο� ���
			//NStatistics_Add("Item", pclMsg->clItem.siUnique, "UseNum", 1);

			if ( SUMMON_SPACE_TICKET == pclMsg->siType) 
			{

				((cltServer *)pclClient)->SendServerResponseMsg(0, SRVAL_SUMMON_SUCCES_USESTRAGERICKET,  0, 0, id);// ��ȯ�� Ƽ���� ��� �߽��ϴ�.
			}
			

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siInvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}

	//���� ���� 
	if( NOLIMIT_TICKET == pclMsg->siType )
	{
		pclCM->CR[id]->pclCI->clBI.bUseNoLimitTicketWarp = pclMsg->bUsing ;
		pclCM->CR[id]->pclCI->clBI.siNoLimitTicketWarpDateVary = pclMsg->siDateVary ;
	}
	else if( MARKET_TICKET == pclMsg->siType )
	{
		pclCM->CR[id]->pclCI->clBI.bMarKetPremiumService = pclMsg->bUsing ;
		pclCM->CR[id]->pclCI->clBI.siMarKetPremiumServiceDate = pclMsg->siDateVary ;
	}
	else if( NewMarket_TICKET == pclMsg->siType )
	{
		pclCM->CR[id]->pclCI->clBI.bNewMarketPremiumService		= pclMsg->bUsing ;
		pclCM->CR[id]->pclCI->clBI.siNewMarketPremiumServiceDate	= pclMsg->siDateVary ;
	}
	else if( SPACEBOX_TICKET == pclMsg->siType )
	{
		pclCM->CR[id]->pclCI->clBI.bSpaceBoxPremiumService = pclMsg->bUsing ;
		pclCM->CR[id]->pclCI->clBI.siSpaceBoxPremiumServiceDate = pclMsg->siDateVary ;
	}
	//��ȯ�� ���� Ȯ�� 
	else if( SUMMON_SPACE_TICKET == pclMsg->siType)
	{
		pclCM->CR[id]->pclCI->clBI.bSummonExtraSlot = pclMsg->bUsing ;
		pclCM->CR[id]->pclCI->clBI.siSummonExtraSlotDate = pclMsg->siDateVary ;
	}

	cltGameMsgResponse_NoLimitTicket_Warp clmsg( pclMsg->siType, pclMsg->bUsing,pclMsg->siDateVary );
	cltMsg clMsg(GAMEMSG_RESPONSE_NOLIMITTICKET_WARP, sizeof(clmsg), (BYTE*)&clmsg);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return ;
}


void cltServer::DoMsg_DBMSG_RESPONSE_GET_SEL_PGLIST(sPacketHeader* pPacket)
{
	sDBResponse_Get_Sel_PGList * pclMsg = (sDBResponse_Get_Sel_PGList*)pPacket;

	if ( pclMsg->siPersonID <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false)	return;
	if ( id != pclMsg->usCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	if ( pclMsg->siResult != 1 ) return ;

	// ���� ����Ÿ
	cltItemMallData cldata[MAX_ITEMMALL_LIST_NUM];

	for ( SI32 i = 0 ; i < MAX_ITEMMALL_LIST_NUM ; i ++ )
	{
		cldata[i].Init();

		for ( SI32 j = 0 ; j < MAX_ITEMMALL_SET_NUM ; j ++ )
		{
			cldata[i].clItem[j].Init();
			cldata[i].clItem[j].siUnique	= pclMsg->clItemData[i].siUnique[j] ;
			cldata[i].clItem[j].siItemNum	= pclMsg->clItemData[i].siItemNum[j] ;
			cldata[i].siLimitLevel[j]		= pclMsg->clItemData[i].siLimitLevel[j];
		}

		cldata[i].siPrice		= pclMsg->clListData[i].siPrice ;
		cldata[i].siEventPrice	= pclMsg->clListData[i].siEventPrice ;

		cldata[i].siProductKey	= pclMsg->clListData[i].siProductKey ;
		cldata[i].siGroupKey	= pclMsg->clListData[i].siGroupKey ;

		cldata[i].siImageFont	= pclMsg->clListData[i].siSprFont ;

		MStrCpy(cldata[i].szName,		pclMsg->clListData[i].szName,		128);
		MStrCpy(cldata[i].szExplain,	pclMsg->clListData[i].szExplain,	512);

		if(pclClient->IsCountrySwitch(Switch_ItemExplain2))
			MStrCpy(cldata[i].szExplain2,	pclMsg->clListData[i].szExplain2,	512);	//	[��ȣ_szExplain2]

		cldata[i].bGift = pclMsg->clListData[i].bGiftFlag ;
		
		// ������ �߱������� ����
		if( ConstServiceArea_China == pclClient->siServiceArea )
		{
			cldata[i].bOnlyBuySilverCoin = pclMsg->clListData[i].bOnlyBuySilverCoin;
		}
		else
		{
			cldata[i].bOnlyBuySilverCoin = false;
		}

		cldata[i].bAgeLimit = pclMsg->clListData[i].bAgeLimit;	//[����] �ŷ�����. KOR: ����, ENG: ���� => 2008-9-22
	}

	cltGameMsgResponse_Get_Sel_PGList clmsg(pclMsg->siResult,
											pclMsg->siMainCategory,
											pclMsg->siSubCategory,
											pclMsg->szType,
											pclMsg->siPage, 
											pclMsg->siMaxPage, 
											cldata);
	cltMsg clMsg(GAMEMSG_RESPONSE_GET_SEL_PGLIST, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_GET_ITEMMALL_ITEMINFO(sPacketHeader* pPacket)
{
	sDBResponse_Get_ItemMall_ItemInfo* pclMsg = (sDBResponse_Get_ItemMall_ItemInfo*)pPacket;

	if ( pclMsg->siPersonID <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false)	return;
	if ( id != pclMsg->usCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	if ( pclMsg->siResult != 1 ) return ;

	cltItemMallData		clItemData[3];

	for ( SI32 i = 0 ; i < 3 ; i ++ )
	{
		clItemData[i].siPrice = pclMsg->clItemData[i].siPrice ;
		clItemData[i].siProductKey = pclMsg->clItemData[i].siProductKey ;
		MStrCpy(clItemData[i].szName,pclMsg->clItemData[i].szName,128);
	}

	cltGameMsgResponse_Get_ItemMall_ItemInfo clmsg(pclMsg->siResult,clItemData);
	cltMsg clMsg(GAMEMSG_RESPONSE_GET_ITEMMALL_ITEMINFO, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALL_BUYITEM(sPacketHeader* pPacket)
{
	sDBResponse_ItemMall_Buyitem* pclMsg = (sDBResponse_ItemMall_Buyitem*)pPacket;

	if ( pclMsg->siPersonID <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false) return;
	if ( id != pclMsg->usCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	cltServer *pclServer = (cltServer *)pclClient;

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	//	if ( pclMsg->siResult != 1 ) return ;

	cltItemMallData cldata;
	cldata.Init();

	cldata.siProductKey = pclMsg->siProductKey ;
	cldata.siPrice = pclMsg->siProductPrice ;
	strcpy(cldata.szName, pclMsg->szItemName);

	// ��õ���� �ִ��� Ȯ���Ѵ�. 
	SI32 recommenderpersonid = pclChar->pclCI->clBI.clRecommenderInfo.siPersonID;
	if( recommenderpersonid  > 0 ) 
	{
		// ������ ������ ���� �ִ��� Ȯ��
		if( siItemmallRPRate )
		{
#ifdef USE_PROMOTOR_SERVER
			// �߱��� ���θ��Ͱ� �ְ� �ڵ��� ������ �Ǿ߸� �����۰� ����Ʈ�� �ش�.	
			if( /*true == pclChar->bCellularPhoneAuth &&*/ true == pclChar->bIsPromoter )
#endif
			{
				SI32 recommendPoint = pclMsg->siProductPrice * pclMsg->siProductNum / siItemmallRPRate;
				sDBRequest_ChangeRecommendPoint clMsg( pclChar->GetID() , pclChar->pclCI->GetPersonID() , (TCHAR*)pclChar->GetName() , pclChar->pclCI->clIP.GetLevel()  , recommenderpersonid,  recommendPoint, RPGIVE_REASON_ITEMMALL );
				SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}

	cltGameMsgResponse_ItemMall_Buyitem clmsg(pclMsg->siResult,&cldata,pclMsg->siProductNum,pclMsg->siCash, pclMsg->siEventCash, pclMsg->szTxNoCode);
	cltMsg clMsg(GAMEMSG_RESPONSE_ITEMMALL_BUYITEM, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ �� ����.
		// param1 == ��ǰ�� ����, param2 == ��ǰ �ε���, param3 == �̺�Ʈ ĳ��
		// pszParam1 == ��ǰ�� �̸�.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ITEMMALL, LOGCOMMAND_INDEX_ITEMMALL_BUY, 
			0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, pclMsg->siProductPrice, pclMsg->siCash, 0, 0, 0, 0, 0, 0, 0, 
			pclMsg->siProductNum, pclMsg->siProductKey, pclMsg->siEventCash, 0, 0, 
			pclMsg->szItemName, NULL);
	}

	SI32 personid = pclMsg->siPersonID;
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		SDBRequest_Get_MyCash_Info_Global clMsg2(pclChar->GetCharUnique(), personid, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China )
	{
		SDBRequest_Get_MyCash_Info_China clMsg2(pclChar->GetCharUnique(), personid, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		// Do Nothing if Korea

		// EVENT
		/*
		if( pclEventTimeManager->InEventTime("ItemMall_GiveBronzeKey", &sTime) )
		{
			if( pclMsg->siProductPrice >= 800 )		// �ܰ��� 800�� �̻��� �͸� �����Ѵ�.
			{
				sDBRequest_ItemMall_Buyitem_ForXNoti clMsg( -1, -1, pclMsg->szMyAccountID, (TCHAR*)pclChar->GetName(), 1362211099, pclMsg->siProductNum, 0, "", pclClient->siServiceArea);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
		*/
	}
	else if( pclClient->siServiceArea == ConstServiceArea_USA )
	{
		// Do Noting if USA
	}
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		SDBRequest_Get_MyCash_Info_NHNChina clMsg2(pclChar->GetCharUnique(), personid, pclChar->pclCI->clBI.szAccountID, pclServer->siServerID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		SDBRequest_Get_MyCash_Info_Germany clMsg2(pclChar->GetCharUnique(), personid, pclChar->pclCI->clBI.siIDNum, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);

		// Do Nothing if Europe
	}
	else
	{
		SDBRequest_Get_MyCash_Info clMsg2(pclChar->GetCharUnique(), personid, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}

	// �����۸����� ���Ž� ���ʽ� ��ǰ ����
	if ( pclEventTimeManager->InEventTime("ItemMall_GiveItem", &sTime) )
	{
		GMONEY	gmCondMoney		= GetGlobalValue( _T("GV_ItemMall_GiveItem_Money") );
		GMONEY	gmSellMoney		= pclMsg->siProductPrice * pclMsg->siProductNum;

		SI32	siGiveUinque	= GetGlobalValue( _T("GV_ItemMall_GiveItem_ItemUnique") );
		SI32	siGiveNum		= GetGlobalValue( _T("GV_ItemMall_GiveItem_ItemNum") );

		cltItem	clGiveItem;
		SI16	siRareSwitch	= 0;

		if ( (0 < gmCondMoney) && (0 <siGiveUinque) && (0 < siGiveNum) && (gmCondMoney <= gmSellMoney) )
		{
			if ( true == pclItemManager->MakeRandItemUnique(siGiveUinque, &clGiveItem, 0, 0, &siRareSwitch) )
			{
				cltSystemRewardInfo clInfo;	// ������ ���� ���� ����

				// ���� ��¥
				clInfo.m_sGiveTime = sTime;

				// ���� ��¥ - ���޹��� ������ 90�� ���� ������ �� �ִ�.
				TimeAddDate(&clInfo.m_sGiveTime, 90, &clInfo.m_sExpireTime);

				// ������ ������
				clInfo.m_clItem.Set( &clGiveItem );

				// �������� ���� �϶�� ��û
				sDBRequest_GiveSystemReward clMsgReward( GIVEREWARD_CHAR, pclMsg->siPersonID, pclMsg->usCharID, &clInfo );
				SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsgReward );
			}
		}
	}

}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALL_GIFTITEM(sPacketHeader* pPacket)
{
	
	sDBResponse_ItemMall_Giftitem* pclMsg = (sDBResponse_ItemMall_Giftitem*)pPacket;

	if ( pclMsg->siPersonID <= 0 )		return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 )						return ;
	if ( pclCM->IsValidID(id) == false) return;
	if ( id != pclMsg->usCharID )		return ;
	
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	//	if ( pclMsg->siResult != 1 ) return ;

	cltItemMallData cldata;
	cldata.Init();

	cldata.siProductKey = pclMsg->siProductKey ;
	cldata.siPrice		= pclMsg->siProductPrice ;

	cltGameMsgResponse_ItemMall_Giftitem clmsg(	pclMsg->siResult,	
												pclMsg->szGetCharName,
												pclMsg->siProductKey,	
												pclMsg->siProductNum,
												pclMsg->siProductPrice,
												pclMsg->siCash, 
												pclMsg->siEventCash,
												pclMsg->szTxNoCode,
												pclMsg->szItemName,	
												pclMsg->siHanFailReason	);
	cltMsg clMsg(GAMEMSG_RESPONSE_ITEMMALL_GIFTITEM, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 16] // ITEMMALL�̿� �����ϱ�
		// param1 == ��ǰ ����, param2 == ��ǰ �ε���, param3 == �̺�Ʈ ĳ��
		// pszParam1 == ���� ���� ��� �̸�, pszParam2 == ��ǰ�� �̸�
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ITEMMALL, LOGCOMMAND_INDEX_ITEMMALL_GIFT,
										0, pclChar, NULL, 0, pclMsg->siProductPrice, pclMsg->siCash, NULL, 0, 0, 0, 0, 0, 0, 
										pclMsg->siProductNum, pclMsg->siProductKey, pclMsg->siEventCash, 0, 0, 
										pclMsg->szGetCharName, pclMsg->szItemName);
	}
	

	// ������ �� �������� ������ ���������� �˸�
	cltLetterMsg_Present clletter(  pclClient->siServerUnique , 
									(TCHAR*)pclChar->GetName(),
									pclMsg->szComment,
									pclMsg->szItemName,
									pclMsg->siProductNum,
									pclMsg->siItemImageFont, 
									pclChar->pclCI->clBI.szAccountID );
	
//	SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);

	// 
	if( siServiceArea == ConstServiceArea_Korea )
	{
		if(pclMsg->siGetItemPersonID)
		{
			SendLetterMsg(pclMsg->siGetItemPersonID, (cltLetterHeader*)&clletter);
		}
	}

	if ( siServiceArea != ConstServiceArea_Korea )
	{
		if( pclMsg->siGetServerUnique == siServerUnique)	// ���� ���� ĳ���Ϳ��� ������ �޽������
		{
			// �̸����� ��������ü üũ�ϰ� �ٷ� �����ְԲ� �޽����� ������.		
			SI32 toid = pclCM->GetIDFromName(pclMsg->szGetCharName);

			if(toid == 0)
			{
				if( ConstServiceArea_China == pclClient->siServiceArea )
				{
				}
				else if( ConstServiceArea_Japan == pclClient->siServiceArea )
				{
					SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);	
				}
				// [����] �����ϱ�. ���� ���� ������ ���� �����̸� ������ �޾Ҵٴ� �޽����� DB�� ����. => 2008-7-24
				else if( ConstServiceArea_USA == pclClient->siServiceArea )
				{
					SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);	
				}
				else
				{
					if(pclMsg->siGetItemPersonID)
					{
						SendLetterMsg(pclMsg->siGetItemPersonID, (cltLetterHeader*)&clletter);
					}
				}
			}
			else
			{
				cltAccountLetterUnit clLetterUnit((cltLetterHeader*)&clletter);
				if( pclCM->IsValidID(toid) )
					((cltCharServer*)pclCM->CR[toid])->SendAccountLetterMsg(&clLetterUnit);			
			}
		}
		else
		{
			SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);		 	    
		}	
	}
	
	if ( pclClient->siServiceArea == ConstServiceArea_English )
	{
		SDBRequest_Get_MyCash_Info_Global clMsg2(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_China )
	{
		SDBRequest_Get_MyCash_Info_China clMsg2(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_USA )
	{
		sDBRequest_Get_MyCash_Info_USA clMsg(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.szAccountID, pclChar->uiIDNo);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		// Do Nothing if Korea

		// EVENT
		/*
		if( pclEventTimeManager->InEventTime("ItemMall_GiveBronzeKey", &sTime) )
		{
			if( pclMsg->siProductPrice >= 800 )		// �ܰ��� 800�� �̻��� �͸� �����Ѵ�.
			{
				sDBRequest_ItemMall_Buyitem_ForXNoti clMsg( -1, -1, pclMsg->szMyAccountID, (TCHAR*)pclChar->GetName(), 1362211099, pclMsg->siProductNum, 0, "", pclClient->siServiceArea);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
		*/
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_NHNChina )
	{
		/*SDBRequest_Get_MyCash_Info_Global clMsg2(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);*/
	}
	else if ( pclClient->siServiceArea == ConstServiceArea_EUROPE )
	{
		SDBRequest_Get_MyCash_Info_Germany clMsg2(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.siIDNum, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}
	else
	{
		SDBRequest_Get_MyCash_Info clMsg2(pclChar->GetCharUnique(), pclMsg->siPersonID, pclChar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg2);
	}

	// �����۸����� ���Ž� ���ʽ� ��ǰ ����
	if ( pclEventTimeManager->InEventTime("ItemMall_GiveItem", &sTime) )
	{
		GMONEY	gmCondMoney		= GetGlobalValue( _T("GV_ItemMall_GiveItem_Money") );
		GMONEY	gmSellMoney		= pclMsg->siProductPrice * pclMsg->siProductNum;

		SI32	siGiveUinque	= GetGlobalValue( _T("GV_ItemMall_GiveItem_ItemUnique") );
		SI32	siGiveNum		= GetGlobalValue( _T("GV_ItemMall_GiveItem_ItemNum") );

		cltItem	clGiveItem;
		SI16	siRareSwitch	= 0;

		if ( (0 < gmCondMoney) && (0 <siGiveUinque) && (0 < siGiveNum) && (gmCondMoney <= gmSellMoney) )
		{
			if ( true == pclItemManager->MakeRandItemUnique(siGiveUinque, &clGiveItem, 0, 0, &siRareSwitch) )
			{
				cltSystemRewardInfo clInfo;	// ������ ���� ���� ����

				// ���� ��¥
				clInfo.m_sGiveTime = sTime;

				// ���� ��¥ - ���޹��� ������ 90�� ���� ������ �� �ִ�.
				TimeAddDate(&clInfo.m_sGiveTime, 90, &clInfo.m_sExpireTime);

				// ������ ������
				clInfo.m_clItem.Set( &clGiveItem );

				// �������� ���� �϶�� ��û
				sDBRequest_GiveSystemReward clMsgReward( GIVEREWARD_CHAR, pclMsg->siPersonID, pclMsg->usCharID, &clInfo );
				SendDBMsg( DBSELECT_SYSTEM, (sPacketHeader *)&clMsgReward );
			}
		}
	}

	
}

void cltServer::DoMsg_DBMSG_RESPONSE_CHECK_ACCOUNTID(sPacketHeader* pPacket)
{
	

	sDBResponse_Check_AccountID* pclMsg = (sDBResponse_Check_AccountID*)pPacket;

	if ( pclMsg->siPersonID <= 0 )
	{
		return ;	
	}
	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false) return;
	if ( id != pclMsg->usCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bIsItemMallGetItem )
		pclChar->bIsItemMallGetItem = false ;

	//if ( pclMsg->szAccountID[0] == '\0' ) return ;
	//if ( pclMsg->szAccountName[0] == '\0' ) return ;
	if ( pclMsg->szCharName[0] == '\0' ) return ;
 

	cltGameMsgResponse_Check_AccountID clmsg(pclMsg->siResult, pclMsg->siServerUnique ,pclMsg->szCharName ,pclMsg->szAccountID, pclMsg->szAccountName);
	cltMsg clMsg(GAMEMSG_RESPONSE_CHECK_ACCOUNTID, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	
}

void cltServer::DoMsg_DBMSG_RESPONSE_GET_MYCASH_INFO(sPacketHeader* pPacket)
{
	SDBResponse_Get_MyCash_Info* pclMsg = (SDBResponse_Get_MyCash_Info*)pPacket;

	if(pclMsg->siResult != 1)
		return;


	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)
		return ;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	cltGameMsgResponse_Get_MyCash_Info clmsg(pclMsg->siResult, pclMsg->siCash, pclMsg->siEventCash);
	cltMsg clMsg(GAMEMSG_RESPONSE_GET_MYCASH_INFO, sizeof(clmsg), (BYTE*)&clmsg);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_DBMSG_RESPONSE_SET_BAGITEM(sPacketHeader* pPacket)
{

	sDBResponse_Set_Bagitem* pclMsg = (sDBResponse_Set_Bagitem*)pPacket;

	if ( pclMsg->siPersonID <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( pclCM->IsValidID(id) == false) return;
	if ( id != pclMsg->siCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];
	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	if ( pclChar->bUseBagItem )
		pclChar->bUseBagItem = false ;

	if ( pclMsg->siResult != 1 ) return ;


	if( pclMsg->siLeftPos >= 0 && pclMsg->siLeftPos < MAX_ITEM_PER_PERSON )
	{
		pclChar->pclCI->clCharItem.clItem[pclMsg->siLeftPos].Set(&pclMsg->clLeftItem);

		// Ŭ���̾�Ʈ�� �뺸
		cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siLeftPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clLeftItem, 0);
		cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
		pclChar->SendNetMsg((sPacketHeader*)&clMsg);
	}

	for ( SI32 i = 0 ; i < MAX_NUM_PER_BAGITEM ; i ++ )
	{
		if ( pclMsg->siPos[i] != 0 && pclMsg->clItem[i].siUnique != 0 && pclMsg->clItem[i].siItemNum != 0 )
		{
			if( pclMsg->siPos[i] >= 0 && pclMsg->siPos[i] < MAX_ITEM_PER_PERSON )
			{
				pclChar->pclCI->clCharItem.clItem[pclMsg->siPos[i]].Set(&pclMsg->clItem[i]);

				// Ŭ���̾�Ʈ�� �뺸
				cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siPos[i], PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem[i], 0);
				cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
				pclChar->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}	
}

void cltServer::DoMsg_DBMSG_RESPONSE_SET_CHANGEHERO(sPacketHeader* pPacket)
{/*
	sDBResponse_Set_ChangeHero* pclMsg = (sDBResponse_Set_ChangeHero*)pPacket;

	if ( pclMsg->siPersonID <= 0 ) return ;	

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( id != pclMsg->siCharID ) return ;
	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( pclMsg->siPersonID != pclChar->pclCI->GetPersonID() )
		return ;

	pclChar->bUseChangeHeroItem = false ;

	if ( pclMsg->siResult != 1 ) return ;

	pclChar->pclCI->clCharItem.clItem[pclMsg->siPos].Set(&pclMsg->clItem) ;

	pclChar->pclCI->clBI.siChangeHeroCode = pclMsg->siCode ;

	cltGameMsgResponse_Set_ChangeHero clinfo(pclMsg->siPos,&pclMsg->clItem,pclMsg->siCode);
	cltMsg clMsg(GAMEMSG_RESPONSE_SET_CHANGEHERO, sizeof(clinfo), (char*)&clinfo);
	pclChar->SendNetMsg((char*)&clMsg);*/
} 


void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALL_BUYITEM_FORXNOTI(sPacketHeader* pPacket)
{
	sDBResponse_ItemMall_Buyitem_ForXNoti* pclMsg = (sDBResponse_ItemMall_Buyitem_ForXNoti*)pPacket;
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d]"), TEXT("sDBResponse_ItemMall_Buyitem_ForXNoti"), pclMsg->siArrayIndex );

	// FOR EVENT
	if( pclMsg->siArrayIndex < 0 && pclMsg->siIdx < 0 )		return;

#ifdef USE_HANXNOTI

	if(pclMsg->siArrayIndex < 0 || pclMsg->siArrayIndex >= HANXNOTI_MAX_WAITING)		return;

	AddInventoryItemAns*	pkSendMsg = NULL;
	if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
	{
		// �������� �޽��� ó��
		m_pkHanXNoti_AnsMessages[pclMsg->siArrayIndex] = new AddInventoryItemAns;
		pkSendMsg = (AddInventoryItemAns*)m_pkHanXNoti_AnsMessages[pclMsg->siArrayIndex];
	}
	else
	{
		// �޽����� �ʰ� ���������Ƿ� DB�� ��Ҹ� ��û
		sDBRequest_ItemMall_CancelOrder_XNoti clMsg( pclMsg->szTxCode );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Cancel Order:Time Out] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog_Error.log"), TEXT("Msg:[%s] [Cancel Order:Time Out] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
	}

	if(pkSendMsg != NULL)
	{
		pkSendMsg->nIdx = pclMsg->siIdx;

		if(pclMsg->siResult == 1)
		{
			pkSendMsg->result = MRS_ERRORCODE_SUCCESS;
		}
		else
		{
			pkSendMsg->result = MRS_ERRORCODE_ADDINVENTORYITEMREQ_FAILED;
		}

		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [result:%d]"), TEXT("AddInventoryItemAns"), pkSendMsg->result );
	}
	else
	{
		// �޸� ���� ����
		if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
		{
			// ����ó�� �̹Ƿ� DB�� ��Ҹ� ��û
			sDBRequest_ItemMall_CancelOrder_XNoti clMsg( pclMsg->szTxCode );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Cancel Order:Mem Error] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog_Error.log"), TEXT("Msg:[%s] [Cancel Order:Mem Error] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
		}
	}

	// Idx �� ��ġ�� ��쿡�� 
	if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
	{
		// �̺�Ʈ SET !!
		::SetEvent(m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_hWaitingHandle);
	}

#endif
}

void cltServer::DoMsg_DBMSG_RESPONSE_ITEMMALL_GIFTITEM_FORXNOTI(sPacketHeader* pPacket)
{
	sDBResponse_ItemMall_Giftitem_ForXNoti* pclMsg = (sDBResponse_ItemMall_Giftitem_ForXNoti*)pPacket;
	pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [siArrayIndex:%d]"), TEXT("sDBResponse_ItemMall_Giftitem_ForXNoti"), pclMsg->siArrayIndex );

#ifdef USE_HANXNOTI

	if(pclMsg->siArrayIndex < 0 || pclMsg->siArrayIndex >= HANXNOTI_MAX_WAITING)		return;

	AddInventoryItemAns*	pkSendMsg = NULL;
	if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
	{
		m_pkHanXNoti_AnsMessages[pclMsg->siArrayIndex] = new AddInventoryItemAns;
		pkSendMsg = (AddInventoryItemAns*)m_pkHanXNoti_AnsMessages[pclMsg->siArrayIndex];
	}
	else
	{
		if(pclMsg->siResult == 1)
		{
			// �޽����� �ʰ� ���������Ƿ� DB�� ��Ҹ� ��û
			sDBRequest_ItemMall_CancelOrder_XNoti clMsg( pclMsg->szTxCode );
			pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Cancel Order:Time Out] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
			pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog_Error.log"), TEXT("Msg:[%s] [Cancel Order:Time Out] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
		}
	}

	if(pkSendMsg != NULL)
	{
		pkSendMsg->nIdx = pclMsg->siIdx;

		if(pclMsg->siResult == 1)
		{
			pkSendMsg->result = MRS_ERRORCODE_SUCCESS;
		}
		else
		{
			pkSendMsg->result = MRS_ERRORCODE_ADDINVENTORYITEMREQ_FAILED;
		}

		pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [result:%d]"), TEXT("AddInventoryItemAns"), pkSendMsg->result );
	}
	else
	{
		// �޸� ���� ����
		if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
		{
			if(pclMsg->siResult == 1)
			{
				// ����ó�� �̹Ƿ� DB�� ��Ҹ� ��û
				sDBRequest_ItemMall_CancelOrder_XNoti clMsg( pclMsg->szTxCode );
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

				pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog.log"), TEXT("Msg:[%s] [Cancel Order:No Mem] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
				pclClient->pclLog->FilePrint(TEXT("Config\\MRSLog_Error.log"), TEXT("Msg:[%s] [Cancel Order:Time Out] [txcode:%s]"), TEXT("AddInventoryItemAns"), pclMsg->szTxCode );
			}
		}
	}

	// Idx �� ��ġ�� ��쿡�� 
	if( m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_siIdx == pclMsg->siIdx )
	{
		// �̺�Ʈ SET !!
		::SetEvent(m_kHanXNoti_Waitings[pclMsg->siArrayIndex].m_hWaitingHandle);

		//[����] �����ϱ�. ������ �������� �������� ���� �޴� �ѿ��� �˸�. => 2008-7-24
		cltLetterMsg_Present clletter(  0, 
										pclMsg->szSendCharName,
										pclMsg->szComment,
										NULL,
										pclMsg->siProductNum,
										NULL, 
										pclMsg->szMyAccountID );

		SI32 toid = pclClient->pclCM->GetIDFromName( pclMsg->szGetCharName );
		if(toid == 0)
		{
			if( ConstServiceArea_China == pclClient->siServiceArea )
			{
			} 
			else if( ConstServiceArea_Japan == pclClient->siServiceArea )
			{
				SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);	
			}
			// [����] �����ϱ�. ���� ���� ������ ���� �����̸� ������ �޾Ҵٴ� �޽����� DB�� ����. => 2008-7-24
			else if( ConstServiceArea_USA == pclClient->siServiceArea )
			{
				//SendAccountLetterMsg( pclMsg->szGetAccountID , (cltLetterHeader*)&clletter);	
			}
			else
			{
				/*if(pclMsg->siGetItemPersonID)
				{
					SendLetterMsg(pclMsg->siGetItemPersonID, (cltLetterHeader*)&clletter);
				}*/
			}
		}
		else
		{
			cltAccountLetterUnit clLetterUnit((cltLetterHeader*)&clletter);
			if( pclCM->IsValidID(toid) )
				((cltCharServer*)pclCM->CR[toid])->SendAccountLetterMsg(&clLetterUnit);			
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
// [�α��߰� : Ȳ���� 2007. 10. 16] // ������ ITEMMALL�̿� �����ϱ�
			// param1	 == ��ǰ ����, 
			// param2	 == ��ǰ �ε���, 
			// param3	 == �̺�Ʈ ĳ��
			// pszParam1 == ���� ������ ��� �̸�, 
			// pszParam2 == ���� ���� ��� �̸�, 
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_ITEMMALL, LOGCOMMAND_INDEX_ITEMMALL_WEB_GIFT,
											0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
											pclMsg->siProductNum,  pclMsg->siProductKey, pclMsg->siProductPrice, 0, 0, 
											pclMsg->szSendCharName, pclMsg->szGetCharName);
		}
	}

#endif
}

// ��ǥ �������� �̵� �Ѵ�
void cltServer::DoMsg_DBMSG_RESPONSE_WARP_TARGETWORLD(sPacketHeader* pPacket)
{
	sDBResponse_TargetWorld* pclMsg = (sDBResponse_TargetWorld*)pPacket;

	SI32 id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
	if ( id <= 0 ) return ;
	if ( id != pclMsg->usCharID ) return ;
	if ( pclMsg->siResult != 1 || pclMsg->siPersonID <= 0 )
		return ;
	if ( pclCM->IsValidID(id) == FALSE ) return ;

	cltCharServer* pclchar = pclCM->GetCharServer( id );

	// ������ ������� ���� ������ ���� ������Ʈ
	if ( pclMsg->siResult == 1 )
	{
		if( pclMsg->siInvPos >= 0 && pclMsg->siInvPos < MAX_ITEM_PER_PERSON )
		{
			// ������ ������ ������Ʈ�Ѵ�.
			pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siInvPos].Set(&pclMsg->clItem);

			// ��迡 �߰��Ѵ�. 
			pclItemManager->AddUseNum( pclMsg->clItem.siUnique, 1);

			// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siInvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		// �������� ������Ʈ �Ѵ����� ���� ��Ű�� ��

		cltWarpInfo	clWarpInfo(1, MAPINDEX_FESTIVAL, true, false, 133 ,168 , -1,  -1)	;
		switch(pclMsg->clItem.siUnique) 
		{
		case ITEMUNIQUE(24128):	// �ӽ÷� ���̿������ 
			{
				clWarpInfo.uiWarpSwitch = 1 ; 
				clWarpInfo.uiMapIndex = MAPINDEX_FESTIVAL	;
				clWarpInfo.uiForceSwitch = true	;
				clWarpInfo.uiTicketUseSwitch = false	;
				clWarpInfo.uiX = 133	;
				clWarpInfo.uiY = 138	;
				clWarpInfo.siGateX = -1	;
				clWarpInfo.siGateY = -1	;				
				
				pclchar->SetWarpInfo(&clWarpInfo, 3000);
				pclchar->Warp();			
			}
			break;
		}
	}
	else // ������ ��� ���н� 
	{
	}
	/*cltGameMsgResponse_WarpTargetWorld clmsg( pclMsg->clItem.siUnique );
	cltMsg clMsg(GAMEMSG_RESPONSE_WARP_TARGETWORLD, sizeof(clmsg), (BYTE*)&clmsg);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);*/
	return ;
}

