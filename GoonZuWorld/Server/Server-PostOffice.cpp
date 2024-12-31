#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "Msg\MsgType-List.h"
#include "Msg\MsgType-PostOffice.h"
#include "MsgRval-Define.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-PostOffice.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h "
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Structure.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

#include "gachamanager\GachaManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOfficeSendItem *pclinfo = (cltGameMsgRequest_PostOfficeSendItem *)pclMsg->cData;

	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	//---------------------------------------------
	// 예약 되어 있는 아이템 사용이 있다면 처리한다. (처리하지 않으면 사용한 아이템이 다시 복구될 수 있다.) 
	//---------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// 예약 되어 있는 탄환아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	pclinfo->szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

	// 자기 자신에게는 보낼 수 없다

	TCHAR personname[ MAX_PLAYER_NAME ];	
	int startpos = -1; 
	int endpos = -1;
	
	TCHAR ch;
	int i = 0;

	bool loop = true;
	while( loop ) 
	{
		ch = pclinfo->szReceiverPersonName[ i ];
		if( ch == NULL ) break;

		if( ch != ' ' ) 
		{
			if( startpos == -1 ) startpos = i;
			endpos = i + 1;
		}

		i++;
	}

	personname[ 0 ] = NULL;

	if( startpos != -1 ) 
	{
		TMemCpy( personname, &pclinfo->szReceiverPersonName[ startpos ], endpos - startpos + 1 );
	}

	personname[ MAX_PLAYER_NAME - 1 ] = NULL;


	if( _tcsicmp( personname, pclCM->CR[id]->pclCI->clBI.GetName() ) == 0 ) 
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_SAMEPERSON,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	if ( pclinfo->siItemInventoryIndex < PERSONITEM_INV0 || pclinfo->siItemInventoryIndex >= MAX_ITEM_PER_PERSON )
	{
		return;
	}

	if( pclinfo->siItemUnique < 1 )
	{
		return;
	}


	if ( pclinfo->siItemNum < 1 || pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}
	
	// 아이템 unique 확인
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siUnique != pclinfo->siItemUnique )
	{
		return;
	}

	// 아이템 개수가 적당한지 확인
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siItemNum < pclinfo->siItemNum )
	{
		return;
	}

	bool isGacha = false;
	if ( ( pclItemManager->IsItemInfoAtb(pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].siUnique,ITEMINFOATB_NOTTRADE) ))
	{
		SI32 checkUnique = pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].siUnique;
		// 가챠 아이템이 아니면 못 보낸다
		if( false == pclGachaManager->IsGachaRareItem( checkUnique ) )
		{
			SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return ;
		}
		else
		{
			isGacha = true;
		}
	}

	// cyj 귀속아이템은 역참으로 못보내도록 수정
	// by LEEKH - 2007.10.01 - 가차아이템은 귀속체크를 하지 않는다.
	if (isGacha == false && 
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].IsBelonging(pclItemManager))
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}
	
	// 개인상점 개설중이며 개인상점에 출품된 아이템이라면 팔수 없다.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->siItemInventoryIndex	)
			{
				// 상점 아이템이 실제로 존재하는지 체크 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}

		// 귀속전용 개인상점
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->siItemInventoryIndex	)
		{
			// 상점 아이템이 실제로 존재하는지 체크 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}

	// [영진]기간제 아이템인지 체크 후 기간제 아이템이라면 GetItemUseAbleDay 로 사용일 가능수 체크
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].IsHaveUseDay())
	{	
		SI32 useableDay = 0;
		BOOL rVal = GetItemUseAbleDay(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex], &useableDay);
			
		if( rVal && useableDay < 0 ) 
		{	
			//KHY - 0723 - 기간아이템 파괴 방지.
			if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
			{
				SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_USEDATEOVER,  0, 0, pclCM->CR[id]->GetCharUnique() );				
				return;
			}
			else
			{
				// 사용기간이 지난 고급품은 보낼 수 없다. - by LEEKH
				if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
				{
					// 메시지 출력
					return;
				}
				else
				{
					// 사용기간이 지난 아이템을 보내려 한다. 지우고 실패 메시지 클라이언트로
					// DB 삭제 요청
					sDBRequest_UseItem useitem(	id,pclCM->CR[id]->pclCI->GetPersonID(),pclinfo->siItemInventoryIndex
												,&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex],USEITEM_REASON_DATEOVER);

					pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);


					SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_USEDATEOVER,  0, 0, pclCM->CR[id]->GetCharUnique() );
					return;
				}
			}
		}
	}
	// 수수료
	GMONEY fee = 0;
	cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice( pclinfo->siItemUnique );
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_POSTOFFICE );
	if(pStrInfo == NULL)return ;

	//KHY - 0614 - 가차 아이템은 같은 계정간 캐릭터에 한하여 우편으로 주고 받을 수 있다. 수수료가 다름. 
	//		fee =  pclClient->pclItemManager->clItemStatistic.siNPCPriceRate *1000;

	if(isGacha ==true)
		fee  = 0;
	else
		fee = pStrInfo->clPostOfficeStrInfo.clItemFee.CalcFee( pclprice->siPrice ) * pclinfo->siItemNum;

	if( fee > pclCM->CR[id]->pclCI->clIP.GetMoney() ) 
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	SI32 posttype = 0;
	if( pclCM->CR[id]->GetGameMasterLevel() >= 100 && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		posttype = 1;		
	}

	//KHY - 0614 - 가차 아이템은 같은 계정간 캐릭터에 한하여 우편으로 주고 받을 수 있다. 
	sDBRequest_PostOfficeSendItem	clMsg(  id, posttype, villageunique, personid, personname,
											pclinfo->siItemInventoryIndex, pclinfo->siItemUnique, pclinfo->siItemNum,
											&pclTime->clDate, fee ,isGacha);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOfficeSendMoney *pclinfo = (cltGameMsgRequest_PostOfficeSendMoney *)pclMsg->cData;

	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	pclinfo->szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

	// 자기 자신에게는 보낼 수 없다
	if( _tcsicmp( pclinfo->szReceiverPersonName, pclCM->CR[id]->pclCI->clBI.GetName() ) == 0 ) {
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_SAMEPERSON,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	// 송금 상한 금액
	if( pclinfo->siMoney > pclClient->GetGlobalValue("GV_PostOfficeMoneyLimit") )	return ;

	if( pclinfo->siMoney > pclCM->CR[id]->pclCI->clIP.GetMoney() ) {

		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// 수수료
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_POSTOFFICE );
	if(pStrInfo == NULL)return ;
	GMONEY fee = pStrInfo->clPostOfficeStrInfo.clMoneyFee.CalcFee( pclinfo->siMoney );

	if( pclinfo->siMoney + fee > pclCM->CR[id]->pclCI->clIP.GetMoney() ) {

		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	SI32 posttype = 0;
	if( pclCM->CR[id]->GetGameMasterLevel() >= 100 && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		posttype = 1;		
	}	

	sDBRequest_PostOfficeSendMoney	clMsg( id, posttype, villageunique, personid, 0, pclinfo->szReceiverPersonName,
		pclinfo->siMoney, &pclTime->clDate, fee );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMSG(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOfficeSendMsg *pclinfo = (cltGameMsgRequest_PostOfficeSendMsg *)pclMsg->cData;

	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)
	{
		SendServerResponseMsg( 0, SRVAL_POSTOFFICE_FAIL_SEND_NOTPOSTOFFICE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// 자기 자신에게는 보낼 수 없다
	if( _tcsicmp( pclinfo->szReceiverPersonName, pclCM->CR[id]->pclCI->clBI.GetName() ) == 0 ) {
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_SAMEPERSON,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// 수수료
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_POSTOFFICE );
	if(pStrInfo == NULL)
	{
		SendServerResponseMsg( 0, SRVAL_POSTOFFICE_FAIL_SEND_NOTPOSTOFFICE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}
	GMONEY fee = pStrInfo->clPostOfficeStrInfo.siMsgFee;

	if( fee > pclCM->CR[id]->pclCI->clIP.GetMoney() ) {

		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}
	
	SI32 posttype = 0;
	if( pclCM->CR[id]->GetGameMasterLevel() >= 100 && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		posttype = 1;		
	}

	sDBRequest_PostOfficeSendMsg	clMsg( id, posttype, villageunique, personid, 0, pclinfo->szReceiverPersonName,
		pclinfo->szMsg, &pclTime->clDate, fee );
		
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	

	pclDelMoneyStatistics->Add(DELMONEY_POSTOFFICE, fee);
}

// 아이템, 현금, 메시지 수신함 정보를 요청 
void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVITEMLIST(cltMsg* pclMsg, SI32 id)
{
	// 마지막 메시지 보낸 시간을 체크한다. 
	if(id && pclCM->CR[id]->CheckLastMsgClock(2000) == true)
	{
		return ;
	}

	cltGameMsgResponse_ListDeleteAll		sendMsg( LISTID_POSTOFFICE_RECVITEM );
	cltMsg clMsg(GAMEMSG_RESPONSE_LIST_DELETEALL, sizeof(cltGameMsgResponse_ListDeleteAll), (BYTE*)&sendMsg);
	
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);


	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER) return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// 아이템 
	{
		sDBRequest_PostOfficeRecvItemList	clMsg( id, villageunique, personid );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	// 현금 
	{		
		sDBRequest_PostOfficeRecvMoneyList	clMsg( id, villageunique, personid );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	// 메시지
	{
		sDBRequest_PostOfficeRecvMsgList	clMsg( id, villageunique, personid );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}


}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVMONEYLIST(cltMsg* pclMsg, SI32 id)
{
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_RECVMSGLIST(cltMsg* pclMsg, SI32 id)
{
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOfficeGetItem *pclinfo = (cltGameMsgRequest_PostOfficeGetItem *)pclMsg->cData;
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = pclchar->pclCI->GetPersonID();
	SI16 siInventoryIndex;

	//---------------------------------------------
	// 예약 되어 있는 아이템 사용이 있다면 처리한다. (처리하지 않으면 사용한 아이템이 다시 복구될 수 있다.) 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// 예약 되어 있는 탄환아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	if(pclClient->IsCountrySwitch(Switch_FourLeaf))
	{
		//[진성] 네잎크로버가 현재 사용할수 없는 거면 꺼내지 몬한다. => 2008-8-14
		if( ITEMUNIQUE(2755) == pclinfo->clItem.siUnique || ITEMUNIQUE(2754) == pclinfo->clItem.siUnique )	
		{	
			if( pclinfo->clItem.siUnique != siFourLeafUnique )	
			{
				SendServerResponseMsg( 0, SRVAL_RETURN_NOT_USE_FOURLEAF, 0, 0, 0 );
				return;	
			}
		}
	}

	cltItem cltoitem;
	SI32 rtnvalue;
	if( pclchar->CanAddInv(INVMODE_ALL, &pclinfo->clItem, &siInventoryIndex, &cltoitem, &rtnvalue) ) {

		sDBRequest_PostOfficeGetItem		clMsg( id, personid, pclinfo->siMsgID, siInventoryIndex, pclinfo->clItem.CanPile( pclItemManager ) );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}
	else
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_GETITEM_FULLINVEN,  0, 0, pclCM->CR[id]->GetCharUnique());
	}        
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETMONEY(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_PostOfficeGetMoney		clMsg( id, personid, pclMsg->siData32[ 0 ] );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_DELMSG(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	{		
		sDBRequest_PostOfficeDelMsg			clMsg( id, personid, pclMsg->siData32[ 0 ] );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	{
		LPARAM lParam = MAKELPARAM( pclMsg->siData32[ 0 ], LPARAMHIWORD_MSG );

		cltGameMsgResponse_ListDelItem		sendMsg( LISTID_POSTOFFICE_RECVITEM, lParam );
		cltMsg clMsg(GAMEMSG_RESPONSE_LIST_DELITEM, sizeof(cltGameMsgResponse_ListDelItem), (BYTE*)&sendMsg);
		
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
	
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SETFEE(cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PostOfficeSetFee *pclinfo = (cltGameMsgRequest_PostOfficeSetFee *)pclMsg->cData;

	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)return ;
	
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	if( pclinfo->clMoneyFee.IsValid(1000) == FALSE ||
		pclinfo->clItemFee.IsValid(1000) == FALSE ||
		pclinfo->siMsgFee < 0 || pclinfo->siMsgFee > 10000 ||
		pclinfo->siRecvFee < 0 || pclinfo->siRecvFee > 10000 ) {

		// 수수료 설정 실패
		SendServerResponseMsg(RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SETFEE,  0, 0, pclCM->CR[id]->GetCharUnique());

		return;
		}
		

	sDBRequest_PostOfficeSetFee		clMsg( id, personid, villageunique, 
		&pclinfo->clMoneyFee, &pclinfo->clItemFee, pclinfo->siMsgFee, pclinfo->siRecvFee );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::SendPostOfficeItemToPerson( TCHAR *szPersonName, cltItem *pclItem, TCHAR *szMsg, GMONEY money )
{
	if( szMsg && szMsg[ 0 ] != NULL ) {
		sDBRequest_PostOfficeSendMsg clMsg( 0, 0, 0, 0, 0, szPersonName, szMsg, &pclTime->clDate, 0 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}	

	if( pclItem ) {
		sDBRequest_PostOfficeMasterSendItem clMsg( 0, 0, szPersonName, pclItem, &pclTime->clDate );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	if( money > 0 ) {
		sDBRequest_PostOfficeSendMoney	clMsg( 0, 0, 0, 0, 0, szPersonName, money, &pclTime->clDate, 0 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	

	}
	
}

void cltServer::SendPostOfficeItemToPerson( SI32 personid, cltItem *pclItem, TCHAR *szMsg, GMONEY money )
{
	
	if( szMsg && szMsg[ 0 ] != NULL ) {
		sDBRequest_PostOfficeSendMsg clMsg( 0, 0, 0, 0, personid, NULL, szMsg, &pclTime->clDate, 0 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	if( pclItem && pclItem->GetItemNum() > 0 ) {
		sDBRequest_PostOfficeMasterSendItem clMsg( 0, personid, NULL, pclItem, &pclTime->clDate );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	if( money > 0 ) {
		sDBRequest_PostOfficeSendMoney	clMsg( 0, 0, 0, 0, personid, NULL, money, &pclTime->clDate, 0 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
	}
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_GETRECORD(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_PostOfficeGetRecord	clMsg( id, personid );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERITEM(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Get_SaveUserItem* pclInfo = (cltGameMsgRequest_Get_SaveUserItem*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = pclchar->pclCI->GetPersonID();
	SI16 siInventoryIndex;

	//---------------------------------------------
	// 예약 되어 있는 아이템 사용이 있다면 처리한다. (처리하지 않으면 사용한 아이템이 다시 복구될 수 있다.) 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// 예약 되어 있는 탄환아이템 사용이 있다면 처리한다. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	if(pclInfo->clItem.siUnique <= 0)
		return;

	SI32 ref = pclItemManager->FindItemRefFromUnique(pclInfo->clItem.siUnique) ;
	if ( ref < 0 ) 
		return ;

	cltItem cltoitem;
	SI32 rtnvalue;
	if( pclchar->CanAddInv(INVMODE_ALL, &pclInfo->clItem, &siInventoryIndex, &cltoitem, &rtnvalue) )
	{
		SI32 itemunique = pclInfo->clItem.siUnique;

		cltItemPriceUnit* pclprice = pclItemManager->pclItemPrice->GetPrice(pclItemManager, itemunique);

		SI64 UserMoney = pclCM->CR[id]->pclCI->clIP.GetMoney();

		SI64 tempTax = ((pclprice->siPrice/100)*pclInfo->clItem.GetItemNum());

		// 클라라를 통한 물품 회수 수수료 없음
		if(bNoChargeGetItemFromNPC)				tempTax = 0;

		if( UserMoney < tempTax )
			return;

		sDBRequest_Get_SaveUserItem		clMsg( id, personid, pclInfo->siIndex, siInventoryIndex, pclInfo->clItem.CanPile( pclItemManager ), tempTax );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		pclDelMoneyStatistics->Add(DELMONEY_TAX, tempTax);
	}
}

//KHY - 1127 - 클라라 물품 보관 개선
void cltServer::DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERHORSE(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Get_SaveUserHorse* pclInfo = (cltGameMsgRequest_Get_SaveUserHorse*)pclMsg->cData;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	SI32 personid = pclchar->pclCI->GetPersonID();

	if(pclInfo->clHorse.siHorseUnique<= 0)
		return;


	//말을 저장 할 수 揚獵쩝?검사 해야 한다. - 빈슬롯유무 판단.

	SI32 enptyHorseindex = pclCM->CR[id]->pclCI->clHorseInfo.FindEmptyHorseIndex();

	if( enptyHorseindex >= 0 )
	{
		REAL32	npcrate = (REAL32)pclItemManager->clItemStatistic.siNPCPriceRate;
		npcrate = npcrate / (REAL32)100;

		SI64 serviceCharge = (SI64)((REAL32)20000 * npcrate);

		// 클라라를 통한 물품 회수 수수료 없음
		if(bNoChargeGetItemFromNPC)				serviceCharge = 0;
	
		sDBRequest_Get_SaveUserHorse clMsg( id, personid, pclInfo->siIndex, enptyHorseindex,  serviceCharge );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);			

		pclDelMoneyStatistics->Add(DELMONEY_TAX, serviceCharge);
	}
}
void cltServer::DoMsg_GAMEMSG_REQUEST_GET_SAVEUSERITEMLIST(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	sDBRequest_Get_SaveUserItemList	clMsg( id, personid );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// [희영] 시세확인 2008-07-18
void cltServer::DoMsg_GAMEMSG_REQUEST_MARKETCONDITIONS(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_MarketConditions* pclInfo = (cltGameMsgRequest_MarketConditions*)pclMsg->cData;

	cltCharServer* pclchar = pclCM->GetCharServer(id);
	if ( NULL == pclchar )
	{
		return;
	}

	SI32 personid = pclchar->pclCI->GetPersonID();

	//-- 수수료 계산 -  수수료가 없다면 아무것도 할 필요가 없다.
	SI32 NPCCharUnique = pclInfo->siNPCCharUnique;
	if ( NPCCharUnique <= 0 ) return ;

	SI32 NPCID = pclCM->GetIDFromCharUnique( NPCCharUnique ) ;

	if ( NPCID <= 0 ) return ;

	if ( pclCM->IsValidID( NPCID ) == false ) return ;

	SI32 villageunique = pclCM->CR[NPCID]->GetCurrentVillageUnique();

	if ( villageunique < 0 || villageunique > CUR_VILLAGE_LIMIT ) return ;


	GMONEY serviceCharge = 0;
	
	REAL32	npcrate = (REAL32)pclItemManager->clItemStatistic.siNPCPriceRate;
	//npcrate = npcrate / (REAL32)100;

	if(pclInfo->selectWhatShowList ==1)
	{
		serviceCharge = (SI64)((REAL32)5000 /100 * npcrate);

	}
	else if(pclInfo->selectWhatShowList ==2)
	{
		serviceCharge = 2 *(SI64)((REAL32)5000 /100 * npcrate);
	}
	else if(pclInfo->selectWhatShowList ==3)
	{
		serviceCharge = 3 *(SI64)((REAL32)5000 /100 * npcrate);
	}

	if( pclchar->pclCI->clIP.GetMoney() < serviceCharge)
		return;

	//-----------------------------------------------------------------------------------------

	SI16 x = 0; // 맥스 카운트. - 안전장치.
	SI16 i =0;
	SI32 index  = 0;
	
	// 전달 해야 할 정보.
	cltMarketConditionsInfo rsInfo[100]; 
	_SYSTEMTIME			rsTime[8];

	if(pclInfo->selectWhatShowList ==1 ) // 1 = 일반 검색
	{
		for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
		{
			if(pclItemManager->pclItemInfo[i] == NULL)continue;

			 index = pclItemManager->FindItemRefFromUnique(pclItemManager->pclItemInfo[i]->clItem.siUnique);

			 if(index ==0) continue;

			if((pclItemManager->pclItemInfo[i]->siType) == (pclInfo->siSelectItemTypeIndex))	
			{
				if( x < 100)
				{
					rsInfo[x].siUnique = pclItemManager->pclItemInfo[i]->clItem.siUnique;
					rsInfo[x].siMarketConditionsMoney =  pclItemManager->pclItemPrice->clUnit[index].siPrice; //현재 시세.

					// 차액과 시간은 없다.

					x++;
				}				
			}			
		}
	}
	else if(pclInfo->selectWhatShowList ==2 ) //  2 = 전날 대비.
	{
		for(i = 0;i < MAX_ITEMINFO_NUMBER;i++)
		{
			if(pclItemManager->pclItemInfo[i] == NULL)		continue;

			 index = pclItemManager->FindItemRefFromUnique(pclItemManager->pclItemInfo[i]->clItem.siUnique);
			 if(index <= 0)									continue;

			if((pclItemManager->pclItemInfo[i]->siType) == (pclInfo->siSelectItemTypeIndex))	
			{
				if( x >= 100 )			break;

				rsInfo[x].siUnique					=  pclItemManager->pclItemInfo[i]->clItem.siUnique;
				rsInfo[x].siMarketConditionsMoney	=  pclItemManager->pclItemPrice->clUnit[index].siPrice; //현재 시세.

				SI64 siBeforePrice = 0;
				if( pclItemManager->clMarketConditions[0] != NULL &&
					pclItemManager->clMarketConditions[0]->pclMarketConditionsB[rsInfo[x].siUnique] != NULL)
				{
					siBeforePrice = pclItemManager->clMarketConditions[0]->pclMarketConditionsB[rsInfo[x].siUnique]->siItemMarketConditions;
				}
				
				if( siBeforePrice == 0 )		siBeforePrice = pclItemManager->pclItemPrice->clUnit[index].siPrice;

				rsInfo[x].siDifferenceMoney =  (pclItemManager->pclItemPrice->clUnit[index].siPrice)
												- siBeforePrice; //차액.
				//날짜는 필요없다.					

				x++;
			}			
		}
	}
	else if(pclInfo->selectWhatShowList ==3 ) //  3 = 일주일 시세. - 단일품목에 대한 일주일간의 시세를 넣어  보내준다.
	{
		SI16 p = 0;

		if(pclInfo->siSelectItemIndex ==0) // 3 = 일주일 시세는 품목 정보가 있어야 한다.
			return ;


		for(p = 0;p < 7 ;p++) // 8일치를 돌아야 한다.
		{
			if(pclItemManager->clMarketConditions[p] == NULL)continue;
			if(pclItemManager->clMarketConditions[p+1] == NULL)continue;
			if(pclItemManager->clMarketConditions[p]->pclMarketConditionsB[ pclInfo->siSelectItemIndex] == NULL)continue;
			if(pclItemManager->clMarketConditions[p+1]->pclMarketConditionsB[ pclInfo->siSelectItemIndex] == NULL)continue;

			if((pclItemManager->clMarketConditions[p]->pclMarketConditionsB[pclInfo->siSelectItemIndex]->siItemUnique) == (pclInfo->siSelectItemIndex))	 // 품목이 같아야 한다.
			{
				if( x < 100)
				{
					rsInfo[x].siUnique =  pclInfo->siSelectItemIndex;
					rsInfo[x].siMarketConditionsMoney =  pclItemManager->clMarketConditions[p]->pclMarketConditionsB[ pclInfo->siSelectItemIndex]->siItemMarketConditions; //과거 시세.

					rsInfo[x].siDifferenceMoney =  ( pclItemManager->clMarketConditions[p]->pclMarketConditionsB[ pclInfo->siSelectItemIndex]->siItemMarketConditions)
												 - (pclItemManager->clMarketConditions[p+1]->pclMarketConditionsB[ pclInfo->siSelectItemIndex]->siItemMarketConditions); //계산된 차개

					memcpy(&rsTime[p], &pclItemManager->clMarketConditions[p]->sTimeMarketConditions , sizeof(_SYSTEMTIME));

					x++;
				}				
			}			
		}
	}

	// 만약을 대비하여, 실패 했을 때는 막는다. - 보내줄 데이터가 없음으로 리턴이다.
	if(x == 0) return ;

	// 돈을 줄인다
	GMONEY changmoney = serviceCharge ;

	sDBRequest_ChangeMoney clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), CHANGE_MONEY_REASON_MARKETCONDITIONS, -changmoney);
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_MARKETCONDITIONS, changmoney);

	// 통화량 조절 
	cltMoney clmoney;
	clmoney.Set(changmoney - changmoney/20);
	clCurrencyInfo.clOutputMoney_NPC.Increase(&clmoney);

	// 마을에 이익금을 추가한다.
	if( villageunique > 0 && villageunique < MAX_VILLAGE_NUMBER)
	{
		sDBRequest_ChangeCityhallProfitMoney sendMsg( CHANGESTRMONEY_CITYHALL_PROFIT, 0, villageunique, changmoney/20 );
		pclGameDBProcess->SendMsg((sPacketHeader *)&sendMsg);
	}

	// 퀘스트 관련
	if ( pclInfo->selectWhatShowList == 1 )
	{
		pclchar->IncQuestPara( QUEST_CLEAR_COND_MARKETCONDITION, pclInfo->siSelectItemTypeIndex, 1 );
	}

	cltGameMsgResponse_MarketConditions rspMsg;

#ifdef _SAFE_MEMORY
	rspMsg.clMarketConditionsInfo.MemCpy(rsInfo);
	rspMsg.sTimeMarketConditionsInfo.MemCpy(rsTime);
#else
	memcpy( rspMsg.clMarketConditionsInfo, rsInfo, sizeof( cltMarketConditionsInfo ) * 100 );
	memcpy( rspMsg.sTimeMarketConditionsInfo, rsTime, sizeof( _SYSTEMTIME ) * 8 );
#endif
	cltMsg clMsg2(GAMEMSG_RESPONSE_MARKETCONDITIONS, sizeof(cltGameMsgResponse_MarketConditions), (BYTE*)&rspMsg);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

}

//[진성] 우체국에서 단체 메시지 보내기. => 2008-8-4
void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDITEM_GROUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOffice_SendItem_Group *pclinfo = (cltGameMsgRequest_PostOffice_SendItem_Group *)pclMsg->cData;

	if( false == pclCM->IsValidID(id) )	return;
	
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();	// Person이 위치한 마을의 VillageUnique를 확보한다
	if( villageunique <= 0 )			return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	pclchar->ItemUseReserveAction();		// 예약 되어 있는 아이템 사용이 있다면 처리한다. (처리하지 않으면 사용한 아이템이 다시 복구될 수 있다.) 
	pclchar->BulletUseReserveAction();		// 예약 되어 있는 탄환아이템 사용이 있다면 처리한다. 

	if(	pclinfo->siItemInventoryIndex < PERSONITEM_INV0 ||  pclinfo->siItemInventoryIndex >= MAX_ITEM_PER_PERSON )			  
		return;

	if( pclinfo->siItemNum < 1 || pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER ) 
		return;

	// 아이템 unique 확인
	if( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siUnique != pclinfo->siItemUnique )
		return;
	
	bool isGacha = false;
	if ( ( pclItemManager->IsItemInfoAtb(pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].siUnique,ITEMINFOATB_NOTTRADE) ))
	{
		SI32 checkUnique = pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].siUnique;
		// 가챠 아이템이 아니면 못 보낸다
		if( false == pclGachaManager->IsGachaRareItem( checkUnique ) )
		{
			SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique() );
			return ;
		}
		else
		{
			isGacha = true;
		}
	}

	// cyj 귀속아이템은 역참으로 못보내도록 수정
	// by LEEKH - 2007.10.01 - 가차아이템은 귀속체크를 하지 않는다.
	if (isGacha == false && 
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].IsBelonging(pclItemManager))
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTRADEITEM,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}

	// 개인상점 개설중이며 개인상점에 출품된 아이템이라면 팔수 없다.
	if( pclchar->bPersonalShopSwitch == true && pclchar->clShopData.m_siShopMode ==PSHOP_MODE_SELL)
	{
		for( SI16 i = 0; i < MAX_SHOP_ITEM_NUMBER ; i++)
		{
			if( pclchar->clShopData.m_siSelectedInventoryPos[i] == pclinfo->siItemInventoryIndex	)
			{
				// 상점 아이템이 실제로 존재하는지 체크 
				if( pclchar->clShopData.m_clItem[ i ].siUnique > 0 )
				{
					SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
					return ;
				}
			}
		}

		// 귀속전용 개인상점
		if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == pclinfo->siItemInventoryIndex	)
		{
			// 상점 아이템이 실제로 존재하는지 체크 
			if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
			{
				SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, id );
				return ;
			}
		}
	}

	// [영진]기간제 아이템인지 체크 후 기간제 아이템이라면 GetItemUseAbleDay 로 사용일 가능수 체크
	if(pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].IsHaveUseDay())
	{	
		SI32 useableDay = 0;
		BOOL rVal = GetItemUseAbleDay(&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex], &useableDay);

		if( rVal && useableDay < 0 ) 
		{	
			//KHY - 0723 - 기간아이템 파괴 방지.
			if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
			{
				SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_USEDATEOVER,  0, 0, pclCM->CR[id]->GetCharUnique() );				
				return;
			}
			else
			{
				// 사용기간이 지난 고급품은 보낼 수 없다. - by LEEKH
				if( pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex].clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
				{
					// 메시지 출력
					return;
				}
				else
				{
					// 사용기간이 지난 아이템을 보내려 한다. 지우고 실패 메시지 클라이언트로
					// DB 삭제 요청
					sDBRequest_UseItem useitem(	id,pclCM->CR[id]->pclCI->GetPersonID(),pclinfo->siItemInventoryIndex
						,&pclCM->CR[id]->pclCI->clCharItem.clItem[pclinfo->siItemInventoryIndex],USEITEM_REASON_DATEOVER);

					pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);


					SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_USEDATEOVER,  0, 0, pclCM->CR[id]->GetCharUnique() );
					return;
				}
			}
		}
	}
	
	// 단체로 보내는 유저 수 얻기.
	SI32 UserNum = 0;
	for(UserNum = 0; UserNum < MAX_SEND_USER_NUM; ++UserNum)
	{
		if( 0 >= _tcslen(pclinfo->m_szReceiverPersonNameGroup[UserNum]) )
			break;
	}
	
	// 내가 전체 보내야할 아이템 수보다 보내려는 아이템 수가 많으면 리턴.
	SI16 UseItemTotalNum = UserNum * pclinfo->siItemNum;
	SI16 MyInvenItemNum  = pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siItemNum;
	if( MyInvenItemNum < UseItemTotalNum )
		return;


		// 수수료
	GMONEY fee = 0;
	cltItemPriceUnit* pclprice = pclItemManager->GetCurrentPrice( pclinfo->siItemUnique );
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_POSTOFFICE );
	if(pStrInfo == NULL)return ;
	
	if(isGacha ==true)  
		fee  = 0;
	else
		fee = pStrInfo->clPostOfficeStrInfo.clItemFee.CalcFee( pclprice->siPrice ) * pclinfo->siItemNum;


	if( fee > pclCM->CR[id]->pclCI->clIP.GetMoney() ) 
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	SI32 posttype = 0;
	if( pclCM->CR[id]->GetGameMasterLevel() >= 100 && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		posttype = 1;		
	}

	for(SI32 Count = 0; Count < MAX_SEND_USER_NUM; ++Count)
	{
		if( 0 >= _tcslen(pclinfo->m_szReceiverPersonNameGroup[Count]) )
			break;

		if( 0 == _tcsicmp( pclClient->pclCM->CR[id]->GetName(), pclinfo->m_szReceiverPersonNameGroup[Count] ) )
			continue;
		
		//KHY - 0614 - 가차 아이템은 같은 계정간 캐릭터에 한하여 우편으로 주고 받을 수 있다. 
		sDBRequest_PostOfficeSendItem	clMsg(  id, posttype, villageunique, personid, pclinfo->m_szReceiverPersonNameGroup[Count],
												pclinfo->siItemInventoryIndex, pclinfo->siItemUnique, pclinfo->siItemNum,
												&pclTime->clDate, fee ,isGacha);		

		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	

		pclDelMoneyStatistics->Add(DELMONEY_POSTOFFICE, fee);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMONEY_GROUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOffice_SendMoney_Group *pclinfo = (cltGameMsgRequest_PostOffice_SendMoney_Group *)pclMsg->cData;

	if( false == pclCM->IsValidID(id) )					return;
	if( pclCM->CR[id]->GetCurrentVillageUnique() <= 0 )	return;

}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_SENDMSG_GROUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOffice_SendMsg_Group *pclinfo = (cltGameMsgRequest_PostOffice_SendMsg_Group *)pclMsg->cData;
  
	if( false == pclCM->IsValidID(id) )					return;

	// Person이 위치한 마을의 VillageUnique를 확보한다
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)
	{
		SendServerResponseMsg( 0, SRVAL_POSTOFFICE_FAIL_SEND_NOTPOSTOFFICE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// 수수료
	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_POSTOFFICE );
	if(pStrInfo == NULL)
	{
		SendServerResponseMsg( 0, SRVAL_POSTOFFICE_FAIL_SEND_NOTPOSTOFFICE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return ;
	}
	
	GMONEY fee = 500;

	if( fee > pclCM->CR[id]->pclCI->clIP.GetMoney() ) 
	{
		SendServerResponseMsg( RANKTYPE_POSTOFFICE, SRVAL_POSTOFFICE_FAIL_SEND_NOTENOUGHFEE,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	SI32 posttype = 0;
	if( pclCM->CR[id]->GetGameMasterLevel() >= 100 && pclCM->CR[id]->pclCI->clBI.uiGMMode == GMMODE_ATB_GMSHOW)
	{
		posttype = 1;		
	}

	for(SI32 Count = 0; Count < MAX_SEND_USER_NUM; ++Count)
	{
		if( 0 >= _tcslen(pclinfo->m_szReceiverPersonNameGroup[Count]) )
			break;
		
		sDBRequest_PostOfficeSendMsg	clMsg(  id, 
												posttype, 
												villageunique, 
												personid, 
												0, 
												pclinfo->m_szReceiverPersonNameGroup[Count],
												pclinfo->m_szMsg, 
												&pclTime->clDate, 
												fee );

		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	

		pclDelMoneyStatistics->Add(DELMONEY_POSTOFFICE, fee);
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_POSTOFFICE_USER_LIST_GROUP(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_PostOffice_User_List_Group *pclinfo = (cltGameMsgRequest_PostOffice_User_List_Group *)pclMsg->cData;

	if( false == pclCM->IsValidID(id) )					return;
	if( pclCM->CR[id]->GetCurrentVillageUnique() <= 0 )	return;

    cltGameMsgResponse_PostOffice_User_List_Group	sendMsg;

	switch(pclinfo->m_siType)
	{
		case cltGameMsgRequest_PostOffice_User_List_Group::FRIEND:
			{
				if( pclCM->CR[id]->pclFriendInfo == NULL)				return;
				if( 0 >= pclCM->CR[id]->pclFriendInfo->GetFriendNum() )	return;	// 친구 없어.

				sDBRequest_Friend_Info	clMsg( POSTOFFICE_GOURP_MESSAGE, id, pclCM->CR[id]->pclCI->GetPersonID() );  
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
		
			}
			break;
		case cltGameMsgRequest_PostOffice_User_List_Group::GUILD:
			{
				if( false == pclCM->CR[id]->pclCI->clBI.clGuildRank.IsGuildMember() ) return;

				cltGuildInfo* pGuild = pclClient->pclGuildManager->GetGuildInfo( pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() );
				if(NULL == pGuild)	return;	// 길드 없어.
					
				sDBRequest_Guild_Info	clMsg( POSTOFFICE_GOURP_MESSAGE, id, pclCM->CR[id]->pclCI->clBI.clGuildRank.GetGuildUnitIndex() );  
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
			}
			break;
		case cltGameMsgRequest_PostOffice_User_List_Group::VILLAGE:
			{
				SI32 siHomeVillage = pclCM->CR[id]->pclCI->clBI.siHomeVillage;
				if( siHomeVillage <= 0 || siHomeVillage > MAX_VILLAGE_NUMBER ) return;	// 마을 없어.
				
				sDBRequest_Village_Resident_Info	clMsg( POSTOFFICE_GOURP_MESSAGE, id, pclCM->CR[id]->pclCI->clBI.siHomeVillage );  
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
			}
			break;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHAR_NAME_CHECK(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_Char_Name_Check* pclinfo = (cltGameMsgRequest_Char_Name_Check*)pclMsg->cData;

	if( false == pclCM->IsValidID(id) )														return;
	if( pclCM->CR[id]->GetCurrentVillageUnique() <= 0 )										return;
	if( 0 ==_tcsicmp( pclClient->pclCM->CR[id]->GetName(), pclinfo->m_szAddPersonName) )	return;
	
	
	sDBRequest_Char_Name_Check	clMsg( id, POSTOFFICE_ADD_RECV_USER, pclinfo->m_szAddPersonName );
	SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
}
