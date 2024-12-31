//---------------------------------
// 2004/7/26 ���ؿ�
//---------------------------------
#include "Char\CharManager\CharManager.h"

#include "../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Person.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-ItemMall.h"

#include "../../../NBillServer/NBillMsg.h"

#include "../Common/Order/Order.h"

#include "../common/JWLib/IsCorrectID/IsCorrectID.h"

#include "MsgRval-Define.h"
#include "Msg/MsgType-ItemMall.h"
#include "MsgType-Person.h"

#include "../../Lib/HashTable/HashTable_StringInt.h"

//#include "../Server/gbillweb.h.h"

#ifdef USE_HAN_BAN_CHECK
	#ifdef _SERVER
		// �Ѱ��� ���� ���� ���
		#include "../HanBanCheckForSvr/HanBanCheckForSvr.h"
	#endif		
#endif

void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMALLEXISTENCE( cltMsg* pclMsg, SI32 id )
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	if(personid <= 0)
	{
		return ;
	}

	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL)
	{
		return ;
	}

	sDBRequest_ItemMallExistence clMsg(id,personid);
	pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMALLITEMLIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_ItemMallItemList* pclinfo = (cltGameMsgRequest_ItemMallItemList*)pclMsg->cData;

	if( pclCM->IsAlive( id ) == false )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)
	{
		return ;
	}


	SI32 page = pclinfo->siListPage ;

	if ( page < 0 )
	{
		page = 0 ;
	}

	sDBRequest_ItemMallItemList clMsg(id,personid,MAX_ITEMNUM_PER_ITEMMALL,page);
	pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);

	// Ȥ�� ������ ������ �� ������ ���� �޽��� ���� üũ
	// 
	sDBRequest_PopAccountLetter clMsg2( id ,pclCM->CR[id]->pclCI->clBI.szAccountID );
	pclClient->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg2);

	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMALLGETITEM( cltMsg* pclMsg, SI32 id )
{
	if( pclCM->IsAlive( id ) == false )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CHADEAD,  0, 0, id);
		return;
	}
	

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CONTINUERENEWAL,  0, 0, id);
		return ;
	}

	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}

	cltGameMsgRequest_ItemMallGetItem* pclinfo = (cltGameMsgRequest_ItemMallGetItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;

	cltItem clfromitem;
	clfromitem = pclchar->pclCI->clItemMall.GetItem(pclinfo->siItemPos) ;
	if ( pclinfo->clItem.siItemNum <= 0 || pclinfo->clItem.siUnique <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,1,0,id);
		return ;
	}
	if ( pclinfo->siItemID < 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,2,0,id);
		return ;
	}

	if ( pclinfo->siItemPos < 0 || pclinfo->siItemPos >= MAX_ITEMNUM_PER_ITEMMALL )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,3,0,id);
		return ;
	}

	if ( pclinfo->clItem.siItemNum > clfromitem.siItemNum )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,4,0,id);
		return ;
	}

	if ( pclItemManager->CanPile(pclinfo->clItem.siUnique) == false && pclinfo->clItem.GetItemNum() != 1 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOITEM,5,0,id);
		return ;
	}

	// [��ȣ_NHN->NDOORS] ������������ ���� �������̷� �����ϴ� �κп��� �������̷� �����ϴ·�ƾ���� ����
	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique( pclinfo->clItem.siUnique );
	if(ref < 0)			return;

	// [��ȣ_NHN->NDOORS] ���ɺ� ����
	if( IsWhereServiceArea( ConstServiceArea_Korea ) )
	{
		if ( pclItemManager->pclItemInfo[ref]->clCondition.siGrownUp == 1 )
		{
			
			if(pclCM->CR[id]->pclCI->clBI.m_uiRealAge < 18)
			{
				// ��ü �̿밡 ���������� ������ �� ���� ������ �Դϴ�. 18�� �̻� �������� �������ּ���.
				SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_ONLYGROWNUP, 5 ,0, id);
				return;
			}
		}
	}
	else if( IsWhereServiceArea(ConstServiceArea_English) )
	{
		if( pclClient->IsCountrySwitch(Switch_GlobalItemMall_Limit) )
		{
			//[����] �۷ι����� �ƾ��۸� ������ ���� ����. => 2008-9-22
			//       ĳ������ ������ �˻��Ѵ�.
			if( pclItemManager->pclItemInfo[ref]->clCondition.siGrownUp > pclchar->pclCI->clIP.GetLevel() )
			{
				SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_ONLYGROWNUP, pclItemManager->pclItemInfo[ref]->clCondition.siGrownUp ,0, id);
				return;
			}

			// �⺻���� 30���� �����̴�.
			if( 30 > pclchar->pclCI->clIP.GetLevel() )
			{
				SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_ONLYGROWNUP, 30 ,0, id);
				return;
			}
		}
	}


	////// ���� ���� ���� üũ
/*
	SI32 ref = pclClient->pclItemManager->FindItemRefFromUnique(pclinfo->clItem.siUnique);
 
	if(ref <= 0) return;

	cltItemConition * pclCondition = &pclClient->pclItemManager->pclItemInfo[ref]->clCondition;

	if( pclCondition->bForMan == true && pclCondition->bForWoman == false  )
	{
		SI32 kind = pclClient->pclCM->CR[id]->GetKind();
		if( kind == KIND_HEROINE1 ||  kind == KIND_HEROINE2 || kind == KIND_HEROINE3 || kind == KIND_HEROINE4 )
		{
			SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_EQUIPUNABLE,1,0,id);
			return ;
		}							
	}
	else if( pclCondition->bForMan == false && pclCondition->bForWoman == true )
	{
		SI32 kind = pclClient->pclCM->CR[id]->GetKind();
		if( kind == KIND_HERO1 ||  kind == KIND_HERO2 || kind == KIND_HERO3 || kind == KIND_HERO4 )
		{
			SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_EQUIPUNABLE,2,0,id);
			return ;
		}
	}

	/////////////////////// 
*/
	SI16 sitopos;
	cltItem cltoitem;

	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclinfo->clItem, &sitopos,&cltoitem, &rtnvalue) ==  false)
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOTINV,0,0,id);
		return ;
	}

	cltoitem.Init() ;
	SI16 brareswitch = 0;
	if( pclItemManager->MakeRandItemUnique( pclinfo->clItem.siUnique, &cltoitem, 0, 0,&brareswitch,0,0,0,0,0,
		pclinfo->clItem.uiDateUseDay) == false )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_NOTINV,0,0,id);
		return ;
	}

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ, ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------

	
	((cltCharServer*)pclCM->CR[id])->ItemUseReserveAction();
	
	((cltCharServer*)pclCM->CR[id])->BulletUseReserveAction();



	cltoitem.SetItemNum(pclinfo->clItem.siItemNum);

	// �巹���� ���� �ο�
	if ( pclItemManager->GetItemType( cltoitem.siUnique ) == ITEMTYPE_DRESS 
		 || pclItemManager->GetItemType( cltoitem.siUnique ) == ITEMTYPE_HAT )
	{
		if ( pclinfo->uiStr > 0 || pclinfo->uiDex > 0 || pclinfo->uiMag > 0
					 || pclinfo->uiVit > 0 || pclinfo->uiHnd > 0 || pclinfo->uiLuk > 0)
		{
			cltItemStatusArmour statusdata = cltoitem.clItemStatusArmour;
			statusdata.SetStatus( (UI08)pclinfo->uiStr, (UI08)pclinfo->uiDex, (UI08)pclinfo->uiMag,
									(UI08)pclinfo->uiVit, (UI08)pclinfo->uiHnd, (UI08)pclinfo->uiLuk);

			cltoitem.clItemStatusArmour.Set(&statusdata);
		}
	}

	bool bPossession = true ;


	switch( siServiceArea )
	{
	case ConstServiceArea_China:
		{
			sDBRequest_ItemMallGetItem_China clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_English:
		{
			sDBRequest_ItemMallGetItem_Global clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_Japan:
		{
			sDBRequest_ItemMallGetItem clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_Korea:
		{
			sDBRequest_ItemMallGetItem_Korea clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_Taiwan:
		{
			sDBRequest_ItemMallGetItem_Taiwan clMsg(id, personid, sitopos, pclinfo->siItemID, &cltoitem, bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_USA : //���߿� ���� �������־�� ��. ����� �۷ι� ����.
		{
			sDBRequest_ItemMallGetItem_USA clMsg(id, personid, sitopos, pclinfo->siItemID, &cltoitem, bPossession, cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_NHNChina:
		{
			//KHY - 0304 - �߱� NHNChinaBilling - 
			sDBRequest_ItemMallGetItem_NHNChina clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	case ConstServiceArea_EUROPE:
		{
			sDBRequest_ItemMallGetItem_Germany clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;

	default:
		{		
			sDBRequest_ItemMallGetItem clMsg(id,personid,sitopos,pclinfo->siItemID,&cltoitem,bPossession,cltoitem.IsCreateSID(pclItemManager));
			pclGameDBProcess->SendMsg(DBSELECT_SYSTEM,(sPacketHeader *)&clMsg);
			pclchar->bIsItemMallGetItem = true ;
		}
		break;
	}
	return;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGENAME(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	cltGameMsgRequest_ChangeCharName* pclinfo = (cltGameMsgRequest_ChangeCharName*)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	if ( !_tcscmp(pclChar->GetName(),pclinfo->szName) ) return ;  // ���� �̸��� �����Ѵ�.
	if ( !IsCorrectID(pclinfo->szName) ) return ; // ��Ģ�� ����� �̸��� �����Ѵ�.
	if ( _tcslen(pclinfo->szName) <= 0 || _tcslen(pclinfo->szName) > MAX_PLAYER_NAME ) return ; // ���̿� �� ������ �����Ѵ�.



	cltItem clitem;
	SI32 pos		= 0;
	SI32 siPersonID = 0;


	if(pclinfo->m_bUseItem == true)
	{
		SI32 itemunique = ITEMUNIQUE(24114) ; // �̸������̿��

		if ( pclChar->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
			return ;

		pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
		if(pos < 0)return ;

		clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos]);
		clitem.SetItemNum(1);

		siPersonID = pclChar->pclCI->GetPersonID();
	}
	else
	{
		// �������� ������� �ʰ� ĳ���͸� �����ϴ� ���� ĳ���� ����â������ �α��λ�Ȳ�̹Ƿ� �����ε��� üũ
		
		// �ε��� ��ȿ�� üũ 
		if((pclinfo->m_siSlotIndex < 0) || (pclinfo->m_siSlotIndex >= MAX_CHAR_PER_USER))
			return;

		siPersonID = pclChar->pclCharListInfo[pclinfo->m_siSlotIndex].clBI.clPerson.GetPersonID();
	}
	

	sDBRequest_ChangeName clMsg(siPersonID, pclinfo->szName, pos, &clitem, pclinfo->m_bUseItem);

	if(pclinfo->m_bUseItem == false)
		clMsg.siCharID = id;		

	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGE_CHARKIND(cltMsg* pclMsg,SI32 id)
{
	if( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	//if ( siServiceArea == ConstServiceArea_China )
	//	return ;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	SI16 type = *pclMsg->cData;
	SI32 orikind = pclChar->pclCI->clBI.GetKind() ;
	if ( orikind <= 0 || orikind >= KIND_SYSTEM ) return ;
	if ( type <= 0 || type >= KIND_SYSTEM ) return ;
	if ( orikind == type ) return ;

	cltKindInfo *pclKindInfo = pclKindInfoSet->pclKI[type];
	if ( pclKindInfo == NULL ) return ;
	if ( pclKindInfo->IsAtb(ATB_HERO) == false ) return ;

	// ��� �����Ǿ��ִ��� �˻��Ѵ�.
	for ( SI16 i=0 ; i<PERSONITEM_RESERVED1 ; i++ )
	{
		if ( i == PERSONITEM_BAG || i == PERSONITEM_BAG_SUB )
			continue;

		if ( pclChar->pclCI->clCharItem.clItem[i].siUnique != 0 )
			return;
	}

	//if ( pclChar->pclCI->clCharItem.clItem[PERSONITEM_DRESS].siUnique != 0 ) return ; // �Ǻ� ����� ��
	//if ( pclChar->pclCI->clCharItem.clItem[PERSONITEM_HAT].siUnique != 0 ) return ; // ���� ����� ��

	SI32 itemunique = ITEMUNIQUE(24070) ; // ĳ���ͺ����̿��

	if ( pclChar->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
		return ;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0)return ;

	cltItem clitem;
	clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos]);
	clitem.SetItemNum(1);

	sDBRequest_Change_CharKind clMsg(pclChar->pclCI->GetPersonID(),type, pos, &clitem);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	return ;
}

void cltServer::DoMsg_GAMEMSG_REQUEST_NOLIMITTICKET_WARP(cltMsg* pclMsg,SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	} 

	cltGameMsgRequest_NolimitTicket_Warp * pclinfo = (cltGameMsgRequest_NolimitTicket_Warp *)pclMsg->cData;

	cltCharServer *pclChar = (cltCharServer *)pclCM->CR[id];

	SI32 itemunique = pclinfo->siItemUnique ;
	SI32 adddate = 0 ;

	if( itemunique <= 0 ) return;

	SI32 ticketType = 0;
	switch(itemunique)
	{
	case ITEMUNIQUE(24094):
	case ITEMUNIQUE(24129): // Goonzu Event Item (24094�� ���� ����� �Ѵ�.)
		{
			adddate = 30 ;//�Ϸ�
			ticketType = NOLIMIT_TICKET;
		}
		break;
	case ITEMUNIQUE(24096):
	case ITEMUNIQUE(24126):	//	�����̵������7�� (EVENT)
		{
			adddate = 210 ;//������
			ticketType = NOLIMIT_TICKET;
		}
		break;
	case ITEMUNIQUE(24097):
		{
			adddate = 900 ;//30��
			ticketType = NOLIMIT_TICKET;
		}
		break;
	case ITEMUNIQUE(24098):
		{
			adddate = 900 ;//30��
			ticketType = NOLIMIT_TICKET;
		}
		break;
	case ITEMUNIQUE(24102)://���� ������ ���� Ƽ�� But ���ӳ��� 25�� 12�� 30�� 23�� 59�б��� ���
		{
			cltDate MaxWarpDate;//���� Ƽ�� ���� ���� �Ѥ�;�̷��� ���ϴ� �����������.
			MaxWarpDate.uiYear = 255;
			MaxWarpDate.uiMonth = 12;
			MaxWarpDate.uiDay = 30;
			MaxWarpDate.uiHour = 23;
			MaxWarpDate.uiMinute = 59;
			SI32 MAX_GAME_DATE = MaxWarpDate.GetDateVary();

			adddate =MAX_GAME_DATE;//���� ���� 255���� ���� ���ڴϱ�.  
			ticketType = NOLIMIT_TICKET;
		}
		break;
	case ITEMUNIQUE(24099):
		{
			adddate = 900 ;
			ticketType = MARKET_TICKET;
		}
		break;
	/*case ITEMUNIQUE(24099):	// ���ո��� Ƽ�� ��� �ϸ�... ���� Ƽ�� �������� ���� �����.
		{
			adddate = 900 ;
			ticketType = NewMarket_TICKET;
		}
		break;*/
	case ITEMUNIQUE(24111):
	case ITEMUNIQUE(24131):	//	GE
		{
			adddate		= 30 ;//�Ϸ�
			ticketType	= SPACEBOX_TICKET;//��������
		}
		break;
	case ITEMUNIQUE(24112):
		{
			adddate = 210 ;//������
			ticketType = SPACEBOX_TICKET;//��������
		}
		break;
	case ITEMUNIQUE(24113):
	case ITEMUNIQUE(24127): // ���������̿��30�� (EVENT)
		{
			adddate = 900 ;//30��
			ticketType = SPACEBOX_TICKET;//��������
		}
		break;
	case ITEMUNIQUE(24117):
		{
			if(pclCM->CR[id]->pclCI->clBI.bSummonExtraSlot == false)
			{
				ticketType = SUMMON_SPACE_TICKET;//��ȯ�� ���� Ȯ��
				adddate = 720 ;//	���ַ� 2��
			}
		}
		break;
	default:
		return ;
	}
	if( 0 == ticketType )
		return;

	if( adddate <= 0 ) return;

	if ( pclChar->pclCI->clCharItem.GetItemNum(itemunique) <= 0 )
		return ;

	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);
	if(pos < 0)return ;

	cltItem clitem;
	clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos]);
	clitem.SetItemNum(1);

	SI32 datevary = 0 ;
	//���ѿ���
	if( NOLIMIT_TICKET == ticketType )
	{
		if (itemunique == ITEMUNIQUE(24102)) {
			pclChar->pclCI->clBI.siNoLimitTicketWarpDateVary = adddate ;
			datevary = pclChar->pclCI->clBI.siNoLimitTicketWarpDateVary;
		}
		else if ( pclChar->pclCI->clBI.bUseNoLimitTicketWarp )
		{
			datevary = pclChar->pclCI->clBI.siNoLimitTicketWarpDateVary + adddate ;
		}
		else
		{
			datevary = pclTime->clDate.GetDateVary() + adddate ;
		}
	}
	else if( MARKET_TICKET == ticketType )
	{
		if ( pclChar->pclCI->clBI.bMarKetPremiumService )
		{
			datevary = pclChar->pclCI->clBI.siMarKetPremiumServiceDate + adddate ;
		}
		else
		{
			datevary = pclTime->clDate.GetDateVary() + adddate ;
		}
	}
	else if( NewMarket_TICKET == ticketType )
	{
		if ( pclChar->pclCI->clBI.bNewMarketPremiumService )
		{
			datevary = pclChar->pclCI->clBI.siNewMarketPremiumServiceDate + adddate ;
		}
		else
		{
			datevary = pclTime->clDate.GetDateVary() + adddate ;
		}
	}
	else if( SPACEBOX_TICKET == ticketType )//��������
	{
		if ( pclChar->pclCI->clBI.bSpaceBoxPremiumService  )
		{
			datevary = pclChar->pclCI->clBI.siSpaceBoxPremiumServiceDate+ adddate ; //�̹� ������̸� ���ڸ� ���ϰ�
		}
		else
		{
			datevary = pclTime->clDate.GetDateVary() + adddate ;//�ƴϸ� ���� ��¥�� + ��Ų��,
		}
	}
	else if( SUMMON_SPACE_TICKET == ticketType )//��ȯ�� ���� Ȯ��
	{
		if ( pclChar->pclCI->clBI.bSummonExtraSlot == false ) 
		{
			datevary = pclTime->clDate.GetDateVary() + adddate ;
		}
	}
		
	sDBRequest_NoLimitTicket_Warp clMsg( true ,pclChar->GetID(), pclChar->pclCI->GetPersonID(), pos, &clitem,datevary, ticketType);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	return ;
}



void cltServer::DoMsg_GAMEMSG_REQUEST_GET_SEL_PGLIST(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	/*
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
        
		return ;
	}
	*/

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if( ((cltCharServer*) pclCM->CR[id])->CheckItemMallBadRequest() == false )
	{
		// �������� �ް� �ִ� ���·� ����� ������ ���� ��� ������ ���ܵȴ�.
        pclchar->bIsItemMallGetItem = true;			
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_BADREQUEST,  0, 0, id);
		return;
	}

	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}


	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;

	cltGameMsgRequest_Get_Sel_PGList * pclinfo = (cltGameMsgRequest_Get_Sel_PGList*)pclMsg->cData ;

	if ( pclinfo->szType[0] == NULL )
		return ;
	SI32 main = 0 ;
	SI32 sub = 0 ;

	if ( pclinfo->siPage <= 0 )
		return ;

	if ( !_tcscmp(pclinfo->szType,TEXT("A")) || !_tcscmp(pclinfo->szType,TEXT("E")) ) // ��ü��ȸ( ��з�,�Һз� ���)
	{
		if ( pclinfo->siMainCategory != ITEMALL_CHARACTER_MENU &&
			pclinfo->siMainCategory != ITEMALL_POWER_MENU &&
			pclinfo->siMainCategory != ITEMALL_SUMMONHORSE_MENU &&
			pclinfo->siMainCategory != ITEMALL_MATERIALFOOD_MENU &&
			pclinfo->siMainCategory != ITEMALL_BEGINNER_MENU &&
			pclinfo->siMainCategory != ITEMALL_SILVERCOIN_MENU )
			return ;

		if ( (pclinfo->siSubCategory >= ITEMALL_CHARACTER_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_CHARACTER_SUBJECT5) ||
			(pclinfo->siSubCategory >= ITEMALL_POWER_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_POWER_SUBJECT4) ||
			(pclinfo->siSubCategory >= ITEMALL_SUMMONHORSE_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_SUMMONHORSE_SUBJECT4) ||
			(pclinfo->siSubCategory >= ITEMALL_MATERIALFOOD_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_MATERIALFOOD_SUBJECT4) ||
			(pclinfo->siSubCategory >= ITEMALL_BEGINNER_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_BEGINNER_SUBJECT3) ||
			(pclinfo->siSubCategory >= ITEMALL_SILVERCOIN_SUBJECT1 && pclinfo->siSubCategory <= ITEMALL_SILVERCOIN_SUBJECT1) )
		{
		}
		else return ;

		main = pclinfo->siMainCategory ;
		sub = pclinfo->siSubCategory ;
	}
	// N , P , S ( �ű� , �α� , ����� )
	else if (	!_tcscmp(pclinfo->szType,TEXT("N")) 
			||	!_tcscmp(pclinfo->szType,TEXT("P")) 
			||	!_tcscmp(pclinfo->szType,TEXT("S")) )
	{
		main = 0 ;
		sub = 0 ;
	}
	else return ;


	// [��ȣ_NHN->NDOORS] ���ɺ� ����
	sDBRequest_Get_Sel_PGList clMsg(pclchar->GetCharUnique(),personid,main,sub,pclinfo->szType,pclinfo->siPage);

	if(pclClient->IsWhereServiceArea(ConstServiceArea_Korea))
	{
		if(pclCM->CR[id]->pclCI->clBI.m_uiRealAge >= 18)		
			clMsg.siAllowGrownUpItem = 1;
	}
	SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	pclchar->bIsItemMallGetItem = true ;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GET_ITEMMALL_ITEMINFO(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	if( ((cltCharServer*) pclCM->CR[id])->CheckItemMallBadRequest() == false )
	{
		// �������� �ް� �ִ� ���·� ����� ������ ���� ��� ������ ���ܵȴ�.
		pclchar->bIsItemMallGetItem = true;			
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_BADREQUEST,  0, 0, id);
		return;
	}
/*
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}
*/
	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}

	

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;

	cltGameMsgRequest_Get_ItemMall_ItemInfo* pclinfo = (cltGameMsgRequest_Get_ItemMall_ItemInfo*)pclMsg->cData;

	sDBRequest_Get_ItemMall_ItemInfo clMsg(pclchar->GetCharUnique(),personid,pclinfo->siGroupKey);
	SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	pclchar->bIsItemMallGetItem = true ;
}


void cltServer::DoMsg_GAMEMSG_REQUEST_GET_MYCASH_INFO(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}

	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}

	cltServer *pclServer = (cltServer *)pclClient;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 siAccountNumber = pclchar->pclCI->clBI.siIDNum;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		SDBRequest_Get_MyCash_Info_Global clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_China)
	{
		SDBRequest_Get_MyCash_Info_China clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_Korea)
	{
		// [��ȣ_NHN->NDOORS] �����۸� �ܾ���ȸ
		SDBRequest_Get_MyCash_Info_nDoors_Korea clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

		//SDBRequest_Get_MyCash_Info_Korea clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		//SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);	
	}
	else if (pclClient->siServiceArea == ConstServiceArea_Taiwan) //���߿� ���� �������־�� ��. ����� �۷ι� ����.
	{
		SDBRequest_Get_MyCash_Info_Global clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_USA )
	{
		sDBRequest_Get_MyCash_Info_USA clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID, pclchar->uiIDNo );
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		//KHY - 0304 - �߱� NHNChinaBilling - 
		SDBRequest_Get_MyCash_Info_NHNChina clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID , pclServer->siServerID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)		// [��ȣ] ���� - ĳ�� ������ �����´�.
	{
		SDBRequest_Get_MyCash_Info_Germany clMsg(pclchar->GetCharUnique(), personid, siAccountNumber, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}

	else
	{
		SDBRequest_Get_MyCash_Info clMsg(pclchar->GetCharUnique(), personid, pclchar->pclCI->clBI.szAccountID);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMALL_BUYITEM(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltServer *pclServer = (cltServer *)pclClient;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// 1�ʿ� 5ȸ �̻��� ��û�� ���Դٸ�
	if( ((cltCharServer*) pclCM->CR[id])->CheckItemMallBadRequest() == false )
	{
		//  �������� �ް� �ִ� ���·� ����� ������ ���� ��� ������ ���ܵȴ�.
		pclchar->bIsItemMallGetItem = true;			
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_BADREQUEST,  0, 0, id);
		return;
	}
/*
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}
*/
	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}


	SI32 siAccountNumber = pclchar->pclCI->clBI.siIDNum;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}
	
	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;

	cltGameMsgRequest_ItemMall_Buyitem* pclinfo = (cltGameMsgRequest_ItemMall_Buyitem*)pclMsg->cData;

	if ( pclinfo->siProductKey < 1 ) return ;
	if ( pclinfo->siProductNum < 1 ) return ;
	if (pclClient->siServiceArea != ConstServiceArea_NHNChina)
	{
		if ( pclinfo->siProductPrice < 1 ) return ;
	}

	// �۷ι� ������ �Ϻ������� ���޴������� ó���ϴ� ��ƾ�� Ʋ���Ƿ�
	// �ٸ� �޼����� ���� ����
	// �׷��� �ش� �޼������� ���� �޼����� �������� ó��
	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		sDBRequest_ItemMall_Buyitem_Global clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China	)
	{
		sDBRequest_ItemMall_Buyitem_China clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName, pclinfo->szSecondPassWord );
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		// [��ȣ_NHN->NDOORS] ������ ����
		sDBRequest_ItemMall_Buyitem_nDoors_Korea clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

		//sDBRequest_ItemMall_Buyitem_Korea clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
		//	pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
		//	pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);
		//SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_Taiwan) //���߿� ���� �������־�� ��. ����� �۷ι� ����.
	{
		sDBRequest_ItemMall_Buyitem_Global clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_USA ) //���߿� ���� �������־�� ��. ����� �۷ι� ����.
	{
		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11
		sDBRequest_ItemMall_Buyitem_USA clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey, pclinfo->szItemName,
			pclchar->pclCI->clBI.szAccountID, pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName, pclchar->uiIDNo);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		//KHY - 0304 - �߱� NHNChinaBilling - 
		sDBRequest_ItemMall_Buyitem_NHNChina clMsg(	pclchar->GetCharUnique(),
													personid,
													pclinfo->siProductKey,
													pclchar->pclCI->clBI.szAccountID,
													pclinfo->siProductNum,
													pclinfo->siProductPrice,
													pclinfo->siProductEventPrice,
													pclchar->GetSession()->GetIP(), 
													pclinfo->szItemName,
													(TCHAR*)pclchar->pclCI->clBI.GetName(), //ĳ���� ��
													pclServer->siServerID
													);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		sDBRequest_ItemMall_Buyitem_Germany clMsg(	pclchar->GetCharUnique(),personid, siAccountNumber,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);				//	������ �̸�

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}

	else
	{
		sDBRequest_ItemMall_Buyitem clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->siProductNum,
			pclinfo->siProductPrice,pclchar->GetSession()->GetIP(), pclinfo->szItemName);
		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}


	pclchar->bIsItemMallGetItem = true ;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_ITEMMALL_GIFTITEM(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// 1�ʿ� 5ȸ �̻��� ��û�� ���Դٸ�
	if( ((cltCharServer*) pclCM->CR[id])->CheckItemMallBadRequest() == false )
	{
		//  �������� �ް� �ִ� ���·� ����� ������ ���� ��� ������ ���ܵȴ�.
		pclchar->bIsItemMallGetItem = true;			
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_BADREQUEST,  0, 0, id);
		return;
	}
/*
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}
*/
	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}

	
	SI32 siAccountNumber = pclchar->pclCI->clBI.siIDNum;
	

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;

	cltGameMsgRequest_ItemMall_Giftitem* pclinfo = (cltGameMsgRequest_ItemMall_Giftitem*)pclMsg->cData;

	if ( pclinfo->siProductKey		<	1	)	return; 
	if ( pclinfo->siProductNum		<=	0	)	return;
	if ( pclinfo->siProductPrice	<	1	)	return;
//	if ( pclinfo->szComment[0]		== '\0' )	return; // ���� �Ҷ� �޼����� ��� �ȴ�!!
	if ( pclinfo->szGetAccountID[0] == '\0' )	return;

	cltServer *pclServer = (cltServer *)pclClient;

	// �۷ι� ������ �Ϻ������� ���޴������� ó���ϴ� ��ƾ�� Ʋ���Ƿ�
	// �ٸ� �޼����� ���� ����
	// �׷��� �ش� �޼������� ���� �޼����� �������� ó��
	if (pclClient->siServiceArea == ConstServiceArea_English)
	{
		sDBRequest_ItemMall_Giftitem_Global clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_China)
	{
		sDBRequest_ItemMall_Giftitem_China clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,
			pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont, pclinfo->szSecondPassWord);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);
	}
	else if( pclClient->siServiceArea == ConstServiceArea_Korea )
	{
		// [��ȣ_NHN->NDOORS] �����ϱ�
		sDBRequest_ItemMall_Giftitem_nDoors_Korea clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

		//sDBRequest_ItemMall_Giftitem_Korea clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
		//	pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
		//	pclinfo->siProductNum,pclinfo->siProductPrice,
		//	pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		//SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_Taiwan) //���߿� ���� �������־�� ��. ����� �۷ι� ����.
	{
		sDBRequest_ItemMall_Giftitem_Global clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_NHNChina)
	{
		//KHY - 0304 - �߱� NHNChinaBilling - 
		sDBRequest_ItemMall_Giftitem_NHNChina clMsg(pclchar->GetCharUnique(),
													personid,
													pclinfo->siProductKey,
													pclchar->pclCI->clBI.szAccountID,
													pclinfo->szGetAccountID,
													pclinfo->siProductNum,
													pclinfo->siProductPrice,
													pclinfo->siProductEventPrice,
													pclinfo->szComment,
													pclchar->GetSession()->GetIP(),
													pclinfo->szItemName,
													pclinfo->siGetServerUnique,
													pclinfo->szGetCharName, 
													pclinfo->siItemImageFont,
													(TCHAR*)pclchar->pclCI->clBI.GetName(), //ĳ���� ��
													pclServer->siServerID
													);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_EUROPE)
	{
		sDBRequest_ItemMall_Giftitem_Germany clMsg(	pclchar->GetCharUnique(),personid, siAccountNumber,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else if (pclClient->siServiceArea == ConstServiceArea_USA ) //[����] USA �����ֱ�.
	{
#ifdef USE_HAN_BAN_CHECK
	#ifdef _SERVER
			//[����] ������� �������� Ȯ��. => 2008-8-26
			char szBuffer1[SIZE_OUTBUFF] = "";
			char szBuffer2[SIZE_OUTBUFF] = "";
			//pclinfo->szGetAccountID
			int ret = HanBanCheckReq( pclinfo->szGetAccountID, szBuffer1, sizeof(szBuffer1) );
			if( HAN_BANCHECKSVR_OK != ret )	return;

			// '0' / '1' / '2' <= �������� �Ǿ��ִ�. ���߿� 1�� ���� �Ľ�.
			ret = HanBanCheckParsing( szBuffer1, 1, szBuffer2, sizeof(szBuffer2) );
			if( HAN_BANCHECKSVR_OK != ret )	return;

			// ������ true�̸� ���� ����. false �̸� ������ ���Ͽ����Ƿ� ���� ������~~~ ����
			if( 0 != strcmp("true", szBuffer2) ) return;
	#endif
#endif
	


		// ���� 30 ���ϴ� ���� �Ұ���.
		const SI16 siTradeLevel = 30;
		if( siTradeLevel > pclchar->pclCI->clIP.GetLevel() )	
		{		
			SendServerResponseMsg( 0, SRVAL_ITEMMALL_FAIL_LIMIT_LEVEL, siTradeLevel, 0, id );
			return;	
		}
		// ���� �������� ������ �Ұ����ϰ�.
		if( 0 == _tcsicmp( pclchar->pclCI->clBI.szAccountID, pclinfo->szGetAccountID))
		{
			return;	
		}

		sDBRequest_ItemMall_Giftitem_USA clMsg(	pclchar->GetCharUnique(),
												personid,
												pclinfo->siProductKey, 
												pclinfo->szItemName, 
												pclchar->pclCI->clBI.szAccountID, 
												pclinfo->szGetAccountID,
												pclinfo->siProductNum,
												pclinfo->siProductPrice,
												pclinfo->szComment,
												pclchar->GetSession()->GetIP(),
												pclinfo->szItemName,
												pclinfo->siGetServerUnique,
												pclinfo->szGetCharName, 
												pclinfo->siItemImageFont,
												pclchar->uiIDNo					);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}
	else
	{
		sDBRequest_ItemMall_Giftitem clMsg(pclchar->GetCharUnique(),personid,pclinfo->siProductKey,
			pclchar->pclCI->clBI.szAccountID,pclinfo->szGetAccountID,
			pclinfo->siProductNum,pclinfo->siProductPrice,
			pclinfo->szComment,pclchar->GetSession()->GetIP(),pclinfo->szItemName,pclinfo->siGetServerUnique,pclinfo->szGetCharName, pclinfo->siItemImageFont);

		SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	}

	pclchar->bIsItemMallGetItem = true ;
}
void cltServer::DoMsg_GAMEMSG_REQUEST_CHECK_ACCOUNTID(cltMsg* pclMsg, SI32 id)
{
 	if( pclCM->IsValidID( id ) == false )
	{
		return;
	}
/*
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
		return ;
	}
*/
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	// 1�ʿ� 5ȸ �̻��� ��û�� ���Դٸ�
	if( ((cltCharServer*) pclCM->CR[id])->CheckItemMallBadRequest() == false )
	{
		//  �������� �ް� �ִ� ���·� ����� ������ ���� ��� ������ ���ܵȴ�.
		pclchar->bIsItemMallGetItem = true;			
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_BADREQUEST,  0, 0, id);
		return;
	}

	if ( !bItemMallUseSwitch && pclCM->CR[id]->GetGameMasterLevel() < BASIC_GAMEMASTER_LEVEL )
	{
		SendServerResponseMsg(0, SRVAL_ITEMMALL_FAIL_CANNOT_SERVER,  0, 0, id);
		return ;
	}

	

	SI32 personid = pclchar->pclCI->GetPersonID();
	if(personid <= 0 )
	{
		SendServerResponseMsg(0,SRVAL_ITEMMALL_FAIL_GETITEM_INFOERROR,2,0,id);
		return ;
	}

	// �̹� �ް� �ִٸ� �� �޴´�
	if ( pclchar->bIsItemMallGetItem )
		return ;
  
	cltGameMsgRequest_Check_AccountID* pclinfo = (cltGameMsgRequest_Check_AccountID*)pclMsg->cData;

	if ( pclinfo->szGetCharName[0] == '\0' ) return ;

	sDBRequest_Check_AccountID clMsg(pclchar->GetCharUnique(),personid,pclinfo->siServerUnique,pclinfo->szGetCharName);
	SendDBMsg(DBSELECT_SYSTEM, (sPacketHeader *)&clMsg);

	pclchar->bIsItemMallGetItem = true ;
}


// �Ϻ� �������� ���� �ִ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_BILLPAGE_URL(cltMsg* pclMsg, SI32 id)
{
	// ���� ����ó��
	if( pclCM->IsValidID( id ) == false )	return;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)	return ;
	// ���� ����ó�� ��	

	cltGameMsgRequest_BillPage_URL * pclinfo = (cltGameMsgRequest_BillPage_URL*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 personid = pclchar->pclCI->GetPersonID();
 	if ( personid <= 0 )	return ;

	//KHY - 0617 - �Ϻ� ä�θ� �߰�.
	TCHAR selectURL[MAX_BILL_PAGGE_URL_LENGTH];

	if(SelectBillURL( pclinfo->szAccountID, selectURL ) == false)
		return ;

	cltGameMsgResponse_BillPage_URL	clinfo( selectURL );
	cltMsg clMsg(GAMEMSG_RESPONSE_BILLPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	/*
	NBillRequest_EncryptIDPW clinfo( pclchar->GetCharUnique() , personid , pclinfo->szAccountID , pclinfo->szPassWord );
	pclBillProcess->SendMsg( (sPacketHeader*) &clinfo );
	*/	
	/*
	TCHAR EncryptedURL[MAX_BILL_PAGGE_URL_LENGTH];

	//	EncryptBill( pclinfo->szAccountID,pclinfo->szPassWord, EncryptedURL );

	cltGameMsgResponse_BillPage_URL	clinfo( EncryptedURL );
	cltMsg clMsg(GAMEMSG_RESPONSE_BILLPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);*/



}

void cltServer::DoMsg_GAMEMSG_REQUEST_LOGINPAGE_URL(cltMsg* pclMsg, SI32 id)
{
	// ���� ����ó��
	if( pclCM->IsValidID( id ) == false )	return;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)	return ;
	// ���� ����ó�� ��	

	cltGameMsgRequest_LoginPage_URL * pclinfo = (cltGameMsgRequest_LoginPage_URL*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if ( personid <= 0 )	return ;

#ifdef _DEBUG
	
	NBillRequest_EncryptIDPW_Web clinfo( pclchar->GetCharUnique() , personid , pclinfo->szAccountID , "psz690n5", pclinfo->szUrl );
	pclBillProcess->SendMsg( (sPacketHeader*) &clinfo );

#else

	NBillRequest_EncryptIDPW_Web clinfo( pclchar->GetCharUnique() , personid , pclinfo->szAccountID , pclinfo->szPassWord, pclinfo->szUrl );
	pclBillProcess->SendMsg( (sPacketHeader*) &clinfo );

#endif

	/*
	TCHAR EncryptedURL[MAX_BILL_PAGGE_URL_LENGTH];

	//	EncryptBill( pclinfo->szAccountID,pclinfo->szPassWord, EncryptedURL );

	cltGameMsgResponse_BillPage_URL	clinfo( EncryptedURL );
	cltMsg clMsg(GAMEMSG_RESPONSE_BILLPAGE_URL,sizeof(clinfo),(BYTE*)&clinfo);
	pclCM->CR[1]->SendNetMsg((sPacketHeader*)&clMsg);*/

}




void cltServer::DoMsg_GAMEMSG_REQUEST_GACHAPAGE_URL(cltMsg* pclMsg, SI32 id)
{
	// ���� ����ó��
	if( pclCM->IsValidID( id ) == false )	return;

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)	return ;
	// ���� ����ó�� ��	

	cltGameMsgRequest_GachaPage_URL * pclinfo = (cltGameMsgRequest_GachaPage_URL*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	if ( pclchar == NULL ) return ;

	SI32 personid = pclchar->pclCI->GetPersonID();
	if ( personid <= 0 )	return ;

#ifdef _DEBUG

	NBillRequest_EncryptIDPW_Gacha clinfo( pclchar->GetCharUnique() , personid , pclinfo->szAccountID , "psz690n5");
	pclBillProcess->SendMsg( (sPacketHeader*) &clinfo );

#else

	NBillRequest_EncryptIDPW_Gacha clinfo( pclchar->GetCharUnique() , personid , pclinfo->szAccountID , pclinfo->szPassWord);
	pclBillProcess->SendMsg( (sPacketHeader*) &clinfo );

#endif


}


void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGE_HERO(cltMsg* pclMsg, SI32 id)
{
	/*
	if( pclCM->IsValidID( id ) == false )
	{
	return;
	}

	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)
	{
	return ;
	}

	cltGameMsgRequest_Change_Hero* pclinfo = (cltGameMsgRequest_Change_Hero*)pclMsg->cData;

	if ( pclinfo->bChange )
	{
	switch(pclinfo->siCharKind)
	{
	case KIND_ONDAL:
	{
	if ( pclCM->CR[id]->pclCI->clBI.siChangeHeroCode & 0x1 )
	{
	pclCM->CR[id]->pclCI->clBI.siChangeHeroKind = KIND_ONDAL ;
	}
	else return ;
	}
	break;
	case KIND_PYEONGGANG:
	{
	if ( pclCM->CR[id]->pclCI->clBI.siChangeHeroCode & 0x2 )
	{
	pclCM->CR[id]->pclCI->clBI.siChangeHeroKind = KIND_PYEONGGANG ;
	}
	else return ;
	}
	break;
	default:
	return;
	break;
	}
	}
	else
	{
	pclCM->CR[id]->pclCI->clBI.siChangeHeroKind = 0 ;
	}

	cltWarpInfo clWarpInfo(1, pclCM->CR[id]->GetMapIndex(), false, false, pclCM->CR[id]->GetX(), pclCM->CR[id]->GetY(), -1, -1);
	((cltCharServer*)pclCM->CR[id])->SetWarpInfo(&clWarpInfo, 2100);
	*/
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PRESENT_ANSWER(cltMsg* pclMsg, SI32 id)
{
	if( pclCM->IsValidID( id ) == false )	return;
	if(id && pclCM->CR[id]->CheckLastMsgClock(1000) == true)	return ;
	
	cltGameMsgRequest_Present_Asnwer * pclinfo = (cltGameMsgRequest_Present_Asnwer*)pclMsg->cData;

	cltLetterMsg_PresentAnswer clletter( siServerUnique ,(TCHAR*)pclCM->CR[id]->GetName(),pclinfo->szComment);
	
	if( pclinfo->siToServerUnique == siServerUnique)	// ���� ���� ĳ���Ϳ��� ������ �޽������
	{
		// �̸����� ��������ü üũ�ϰ� �ٷ� �����ְԲ� �޽����� ������.		
		SI32 toid = pclCM->GetIDFromName(pclinfo->szToCharName);

		if( pclCM->IsValidID(toid) == false )
		{
			SendAccountLetterMsg( pclinfo->szToAccountName , (cltLetterHeader*)&clletter);	
		}
		else
		{
			//			((cltServer*)pclCM->CR[toid])->SendAccountLetterMsg( pclMsg->szGetAccountID ,(cltLetterHeader*)&clletter);

			cltAccountLetterUnit clLetterUnit((cltLetterHeader*)&clletter);

			((cltCharServer*)pclCM->CR[toid])->SendAccountLetterMsg(&clLetterUnit);			

		}
	}
	else
	{
		SendAccountLetterMsg( pclinfo->szToAccountName , (cltLetterHeader*)&clletter);		 	    
	}	

}

//KHY - 0617 - �Ϻ� ä�θ� �߰�. - ����.
bool	cltServer::SelectBillURL( TCHAR * AccountID, TCHAR * selectURL )
{
	SI16 idSize = strlen(AccountID);

	TCHAR temPublisher[20] = {'\0',};
	bool	    tempFlage =false;
	SI16    tempNum = 0;

	for(SI16 i =0;i < idSize; i++)
	{
		// "@" ���� ������ ���ڸ��� �����Ѵ�.
		if((tempFlage == false) &&( AccountID[i] == '@'))
		{	
			tempFlage = true;
			continue;
		}

		if(tempFlage == true)
		{
			temPublisher[tempNum] = AccountID[i];
			tempNum++;
		}
	}

	if(strcmp(temPublisher, "HG") == 0) // �Ѱ���.
	{
		strcpy(selectURL , "http://bill.ndoors.jp/channeling/hangame/notice.asp");
	}
	else if(strcmp(temPublisher, "GP") == 0) // ������.
	{
		strcpy(selectURL , "http://bill.ndoors.jp/channeling/gamepot/notice.asp");
	}
	else if(strcmp(temPublisher, "GA") == 0) // �����Ͼ�.
	{
		StringCchPrintf(selectURL ,MAX_BILL_PAGGE_URL_LENGTH,TEXT("%s%s"),
			"https://bill.ndoors.jp/channeling/gamania/term.asp?user_id=",AccountID);
		
	}
	else if(strcmp(temPublisher, "ND") == 0) // NDE
	{
		StringCchPrintf(selectURL ,MAX_BILL_PAGGE_URL_LENGTH,TEXT("%s%s"),
				"https://bill.ndoors.jp/channeling/payment/term.asp?user_id=",AccountID);	
	}
	else if(strcmp(temPublisher, "NX") == 0) // �ؽ� 
	{
		strcpy(selectURL ,"http://bill.ndoors.jp/channeling/nexon/notice.asp");	
	}
	else
	{
		return false;	
	}

	return true;	
}
void cltServer::DoMsg_GAMEMSG_REQUEST_WARP_TARGETWORLD(cltMsg* pclMsg, SI32 id)
{
	// ��ǥ �������� ���󰣴� .
	// �ٸ� �����۵� ����ũ �߰��ؼ� Ƽ�� �߰� �Ҽ� �ֵ��� �ؾ��� 

	cltGameMsgRequest_WarpTargetWorld * pclinfo = (cltGameMsgRequest_WarpTargetWorld *)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer(id)	;	if(pclChar == NULL)	return	;

	if( false == pclChar->CanWarpToChar( id))	return	;

	// ���� ���°� ������ ������ ���� �Ұ��� 
	if(pclChar->clInnerStatus.IsStatus( INNERSTATUS_PRISON ))	return	;
	// ���� ���� ���� ���̸� ���� �Ұ��� 
	if( pclChar->bPersonalShopSwitch == true || pclChar->bPremiumPersonalShop == true  )	return	;


	SI32 itemunique = pclinfo->siItemUnique ;	if( itemunique <= 0 ) return;

	// �ϴ� �ش� �������� �ִ��� Ȯ�� �Ѵ� .
	// �ش� �������� ��� �Ѵ� .
	// �ɸ��͸� ���� ��Ų�� .

	// ���常 ��� �̴ϱ�.
	SI32 pos = pclChar->pclCI->clCharItem.GetItemPos(itemunique);	if(pos < 0)return ;

	cltItem clitem;
	clitem.Set( &pclChar->pclCI->clCharItem.clItem[pos]);
	clitem.SetItemNum(1);

	sDBRequest_Warp_TargetWorld clMsg( pclChar->GetID(), pclChar->pclCI->GetPersonID(), pos, &clitem);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

}

