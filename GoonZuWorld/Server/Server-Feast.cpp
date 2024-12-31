// server-land
#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Feast.h"
#include "NDate.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\Msg\\MsgType-Feast.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"
#include "../../../DBManager/GameDBManager_World/DBMsg-Structure.h"
//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_RESERVE( cltMsg* pclMsg, SI32 id )
{

	cltGameMsgRequest_FeastReserve* pclinfo = (cltGameMsgRequest_FeastReserve*)pclMsg->cData;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	// �̹� �����ڰ� ������
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus == 2 ) {

		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_RESERVE_ALREADY, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// ��ȸ ���� ���̶��,
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_RESERVE_OPEN, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// ��ȸ ��¥�� �����Ѱ�

	SYSTEMTIME systime;
	GetLocalTime( &systime );
	
	NDate date, resvdate;
	date.SetDate( systime.wYear, systime.wMonth, systime.wDay );
	resvdate.SetDate( pclinfo->siYear, pclinfo->siMonth, pclinfo->siDay );
	
	SI32 gday1 = date.GetDateVary();
	SI32 gday2 = resvdate.GetDateVary();

	if( gday1 > gday2 || gday1 + 1 < gday2 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_RESERVE_DATE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( gday1 == gday2 ) {
		if( pclinfo->siHour * 60 + pclinfo->siMinute <
			systime.wHour * 60 + systime.wMinute ) {

				SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_RESERVE_DATE, 0, 0, pclCM->CR[id]->GetCharUnique());	
				return;

			}
	}

	// ��ǰ�� �غ� �Ǿ��°�
	if( pclStrInfo->clFeastStrInfo.CanResv() == FALSE ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_RESERVE_ITEM, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}


	GMONEY cost = pclStrInfo->clFeastStrInfo.clFeastInfo.siCost;

	// ���� ��û�� �Ѵ�
	sDBRequest_FeastReserve clMsg( id, villageunique, personid, 
		pclinfo->siYear, pclinfo->siMonth, pclinfo->siDay, pclinfo->siHour, pclinfo->siMinute,
		pclinfo->szReason, cost );

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, cost);

    pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_ADDPRESENTLIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastAddPresentList* pclinfo = (cltGameMsgRequest_FeastAddPresentList*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)
		return ;
		
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	if( pclinfo->siItemNum == 0 ) return;

	// ��ȸ���̰ų� �����ڰ� ������쿡�� �������� ���Ѵ�.
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_NOCHANGE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// �̹� ��ϵ� �������̸� 

	for( int i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {

		if( pclStrInfo->clFeastStrInfo.clFeastInfo.siItemUnique[ i ] == pclinfo->siItemUnique ) {

			SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_ALREADY, 0, 0, pclCM->CR[id]->GetCharUnique());	
			return;
		}
	}


	if( pclItemManager->CanPile( pclinfo->siItemUnique ) == FALSE ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_WRONG, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_TOOMANY, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// ����Ʈ���� �� index�� ���Ѵ� 
	SI32 index = pclStrInfo->clFeastStrInfo.clFeastInfo.GetEmptyPresentIndex();


	sDBRequest_FeastAddPresentList clMsg( id, villageunique, index, pclinfo->siItemUnique, pclinfo->siItemNum );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_DELPRESENTLIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastDelPresentList* pclinfo = (cltGameMsgRequest_FeastDelPresentList*)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	// ��ȸ���̰ų� �����ڰ� ������쿡�� �������� ���Ѵ�.
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_NOCHANGE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( pclinfo->siListIndex < 0 || pclinfo->siListIndex >= MAX_FEAST_PRESENT_NUMBER )				return;

	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siItemUnique[ pclinfo->siListIndex ] != pclinfo->siItemUnique ) return;
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siItemNum[ pclinfo->siListIndex ] != pclinfo->siItemNum ) return;

	sDBRequest_FeastDelPresentList clMsg( id, villageunique, pclinfo->siListIndex );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}


void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_STGITEMIN( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastStgItemIn* pclinfo = (cltGameMsgRequest_FeastStgItemIn*)pclMsg->cData;
	

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��ȸ���̰ų� �����ڰ� ������쿡�� �������� ���Ѵ�.
	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_NOCHANGE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( pclItemManager->CanPile( pclinfo->siItemUnique ) == FALSE ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_WRONG, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( pclItemManager->IsItemInfoAtb( pclinfo->siItemUnique, ITEMINFOATB_NOTTRADE ) )
	{
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_WRONG, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if ( pclinfo->siItemInventoryIndex < PERSONITEM_INV0 || pclinfo->siItemInventoryIndex > MAX_ITEM_PER_PERSON )
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

	SI32 pos = -1;
	for (SI32 i = 0; i < MAX_FEAST_STG_NUMBER; i++)
	{
		if (pclStrInfo->clFeastStrInfo.clFeastStg[i].siItemUnique == pclinfo->siItemUnique)
		{
			pos = i;
		}
	}
	if (pos > 0 && pos < MAX_FEAST_STG_NUMBER)
	{
		if (pclStrInfo->clFeastStrInfo.clFeastStg[pos].siItemNum + pclinfo->siItemNum > MAX_ITEM_PILE_NUMBER)
		{
			SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_ITEM_TOOMANY, 0, 0, pclCM->CR[id]->GetCharUnique());	
			return;
		}
	}
	
	// ������ unique Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siUnique != pclinfo->siItemUnique )
	{
		return;
	}

	// ������ ������ �������� Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ pclinfo->siItemInventoryIndex ].siItemNum < pclinfo->siItemNum )
	{
		return;
	}

	
	sDBRequest_FeastStgItemIn	clMsg( id, personid, villageunique, 
		pclinfo->siItemInventoryIndex, pclinfo->siItemUnique, pclinfo->siItemNum );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_STGITEMOUT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastStgItemOut* pclinfo = (cltGameMsgRequest_FeastStgItemOut*)pclMsg->cData;
	

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��ȸ���̰ų� �����ڰ� ������쿡�� �������� ���Ѵ�.
	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_NOCHANGE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if ( pclinfo->siStgItemIndex < 0 || pclinfo->siStgItemIndex >= MAX_FEAST_STG_NUMBER )
	{
		return;
	}

	if( pclinfo->siStgItemUnique < 1 )
	{
		return;
	}


	if ( pclinfo->siStgItemNum < 1 || pclinfo->siStgItemNum > MAX_ITEM_PILE_NUMBER )
	{
		return;
	}


	// ������ unique Ȯ��

	if ( pclStrInfo->clFeastStrInfo.clFeastStg[ pclinfo->siStgItemIndex ].siItemUnique != pclinfo->siStgItemUnique )
	{
		return;
	}

	// ������ ������ �������� Ȯ��
	if ( pclStrInfo->clFeastStrInfo.clFeastStg[ pclinfo->siStgItemIndex ].siItemNum < pclinfo->siStgItemNum )
	{
		return;
	}

	//------------------------------------------
	// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//------------------------------------------
	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];
	SI16 invpos;
	cltItem cltoitem;
	cltItem clfromitem;
	clfromitem.siItemNum = pclinfo->siStgItemNum;
	clfromitem.siUnique = pclinfo->siStgItemUnique;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_PERSON, &clfromitem, &invpos, &cltoitem, &rtnvalue) == false)return ;

	sDBRequest_FeastStgItemOut	clMsg( id, personid, villageunique, 
		pclinfo->siStgItemIndex, pclinfo->siStgItemUnique, pclinfo->siStgItemNum , invpos );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_SETCOST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastSetCost* pclinfo = (cltGameMsgRequest_FeastSetCost*)pclMsg->cData;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	// ��ȸ���̰ų� �����ڰ� ������쿡�� �������� ���Ѵ�.
	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 0 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_NOCHANGE, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	sDBRequest_FeastSetCost	clMsg( id, villageunique, pclinfo->siCost );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_GIVEITEM( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastGiveItem* pclinfo = (cltGameMsgRequest_FeastGiveItem*)pclMsg->cData;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	// ��ȸ ���ΰ�
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 1 ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_GIVEITEM_NOTOPEN, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// ��ȸ �����ڰ� �´°�
	if( pclStrInfo->clFeastStrInfo.clFeastResvInfo.siPersonID != personid ) {
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_GIVEITEM_WRONGPERSON, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	if( pclinfo->siIndex < 0 || pclinfo->siIndex >= MAX_FEAST_PRESENT_NUMBER )		return;

	// ��ǰ�� �ùٸ� ���ΰ�
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siItemUnique[ pclinfo->siIndex ] != pclinfo->siItemUnique || 
		pclStrInfo->clFeastStrInfo.clFeastInfo.siItemNum[ pclinfo->siIndex ] < pclinfo->siItemNum ) {
			SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_GIVEITEM, 0, 0, pclCM->CR[id]->GetCharUnique());	
			return;
	}

	// �̹� ������ ��ǰ�� �ƴѰ�
	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siItemGive[ pclinfo->siIndex ] == 1 ) 
	{
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_GIVEITEM_ALREADY, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;			
	}

	SI32 stgindex = 0;
	SI16 stgitemunique = 0, stgitemnum = 0;

	for( int i = 0; i < MAX_FEAST_STG_NUMBER; ++i ) {
		if( pclStrInfo->clFeastStrInfo.clFeastStg[ i ].siItemUnique == pclinfo->siItemUnique ) {
			stgindex = i;
			stgitemunique = pclinfo->siItemUnique;
			stgitemnum = pclStrInfo->clFeastStrInfo.clFeastStg[ i ].siItemNum;
			break;
		} 
	}

	if( i == MAX_FEAST_STG_NUMBER ) 
	{
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_GIVEITEM, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	sDBRequest_FeastGiveItem clMsg( id, villageunique, pclinfo->siIndex, pclinfo->siItemUnique, pclinfo->siItemNum,
		stgindex, stgitemunique, stgitemnum );

	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);	
}


void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_SENDCHAT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastSendChat* pclinfo = (cltGameMsgRequest_FeastSendChat*)pclMsg->cData;

	TCHAR *pTitle = GetTxtFromMgr(6134);

	cltGameMsgResponse_Notice clNotice( pTitle, pclinfo->szText ,true);
	cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE, clNotice.siDataSize, (BYTE*)&clNotice);
	
	if( pclClient->IsCountrySwitch( Switch_PartyHall ) )
	{
		SI32 SendUserMapIndex = pclCM->CR[id]->GetMapIndex();
		for(SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount)
		{
			if(false == pclCM->IsValidID(UserCount))
				continue;

			if(pclCM->CR[UserCount]->GetMapIndex() == SendUserMapIndex)
			{
				pclCM->CR[UserCount]->SendNetMsg((sPacketHeader*)&clMsg);
			}
		}
	}
	else
	{
		// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
		SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
		if(villageunique == 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

		cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

		if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 1 ) return;

		SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

		if( pclStrInfo->clFeastStrInfo.clFeastResvInfo.siPersonID != personid ) return;

		pclCM->SendAllPersonInVillageMsg((sPacketHeader*)&clMsg, villageunique);
	}
}

//#if defined(_LEON_FEAST_EFFECT)
void cltServer::DoMsg_GAMEMSG_REQUEST_FEAST_USEEFFECT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastUseEffect* pclinfo = (cltGameMsgRequest_FeastUseEffect*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)
		return ;

	// ��ȸ������ üũ
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 ) return;

	cltStrInfo *pclStrInfo = GetStrInfo( villageunique, RANKTYPE_FEAST );

	if( pclStrInfo->clFeastStrInfo.clFeastInfo.siStatus != 1 ) return;

	// ��ȸ������ ���� üũ
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	if( pclStrInfo->clFeastStrInfo.clFeastResvInfo.siPersonID != personid ) return;

	// �����̿�� üũ
	// �����̿�� ��ȣ ���� ��
	SI16 itemunique = ITEMUNIQUE(24060); // ���ڽ������̿��  14200 -> 24060

	SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( itemunique );
	if( pos < 0 )
	{
		// ���ڽ������̿�� ����
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_USEEFFECT_NOTHAVETICKET, 0, 0, pclCM->CR[id]->GetCharUnique());	
	}

	// ��踦 ����. 
	pclItemManager->AddUseNum(itemunique, 1);

	// ���ο� ���
	//NStatistics_Add("Item", itemunique, "UseNum", 1);

	cltItem clitem;
	clitem.Init();

    clitem.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ] );
	clitem.SetItemNum( 1 );

#ifdef _SAFE_MEMORY
	sDBRequest_FeastUseEffect sendMsg( id, personid, villageunique, pos, &clitem, &pclinfo->siEffectNum[0] );
#else
	sDBRequest_FeastUseEffect sendMsg( id, personid, villageunique, pos, &clitem, pclinfo->siEffectNum );
#endif
	pclGameDBProcess->SendMsg( (sPacketHeader*) &sendMsg );
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_EXIT( cltMsg* pclMsg, SI32 id )
{
	if(pclCM->IsValidID(id) == false)
		return ;

	SI32		siWarpX = 12 + (rand() % 5);   
	SI32		siWarpY = 12 + (rand() % 5);
	cltWarpInfo clWarpPirateShip(1, 158, false, false, siWarpX, siWarpY, -1, -1);

	pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
	pclCM->CR[id]->Warp();

}


void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_GET_COSTUME( cltMsg* pclMsg, SI32 id )
{
	if(pclCM->IsValidID(id) == false)
		return ;

	SI32* pInfo = (SI32*)pclMsg->cData;
	
	SI32 ItemUnique = *pInfo;

	if( 0 >= ItemUnique )
		return;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[ id ];
    
	// ��ƼȦ �Ǻ��� ���������� ������ �ִ�.
	SI32 siHaveCount = 0;
	siHaveCount += pclchar->pclCI->clCharItem.GetItemNum(ItemUnique);
	siHaveCount += pclchar->pclCI->clCharItem.GetItemNumInEquip(ItemUnique);

	// ���� 1�������� ������ �� �ִ�.
	if( siHaveCount >= 1 )
	{
		return;
	}
	
	pclchar->GiveItem(ItemUnique, 1, INPUTITEMPERSON_OPTION_PARTYHALL_ITEM, 0);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_TOTAL_INFO( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Total_Info* pclinfo = (cltGameMsgRequest_PartyHall_Total_Info*)pclMsg->cData;
	
	for(SI32 Count = 0; Count < MAX_PARTYHALL_MAP; ++Count)
	{
		cltGameMsgResponse_PartyHall_Total_Info cltInfo1( Count, 0, &pclVillageManager->pclFeastManager->clPartyHallResvInfo[Count][0] );
		cltGameMsgResponse_PartyHall_Total_Info cltInfo2( Count, 1, &pclVillageManager->pclFeastManager->clPartyHallResvInfo[Count][0] );
		cltGameMsgResponse_PartyHall_Total_Info cltInfo3( Count, 2, &pclVillageManager->pclFeastManager->clPartyHallResvInfo[Count][0] );

		cltMsg clMsg1(GAMEMSG_RESPONSE_PARTYHALL_TOTAL_INFO, sizeof(cltGameMsgResponse_PartyHall_Total_Info), (BYTE*)&cltInfo1);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg1);

		cltMsg clMsg2(GAMEMSG_RESPONSE_PARTYHALL_TOTAL_INFO, sizeof(cltGameMsgResponse_PartyHall_Total_Info), (BYTE*)&cltInfo2);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);

		cltMsg clMsg3(GAMEMSG_RESPONSE_PARTYHALL_TOTAL_INFO, sizeof(cltGameMsgResponse_PartyHall_Total_Info), (BYTE*)&cltInfo3);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg3);
	}

	SI32 VillageUnique = pclClient->pclCM->CR[id]->GetCurrentVillageUnique();
	if(0 == VillageUnique)
		return;
	
	cltStrInfo*			  pStructInfo = pclClient->pclFeastManager->GetStrInfo(VillageUnique);
	if(NULL == pStructInfo)
		return;
	
	PartyHall_Decoration*	DecorationList = pStructInfo->clFeastStrInfo.clDecoration;
	if(NULL == DecorationList)
		return;

	
	cltGameMsgResponse_PartyHall_Decoration_List cltInfo4;
	for(SI32 Count = 0; Count < MAX_FEAST_STG_NUMBER; ++Count)
	{
		cltInfo4.m_clDecoration[Count].m_siDecorationKind = DecorationList[Count].m_DacorationKind;
		cltInfo4.m_clDecoration[Count].m_siDecorationNum  = DecorationList[Count].m_DacorationNum;
		cltInfo4.m_clDecoration[Count].m_siDecorationSlot = Count;
	}

	cltMsg clMsg4(GAMEMSG_RESPONSE_PARTYHALL_DECORATION_LIST, sizeof(cltGameMsgResponse_PartyHall_Decoration_List), (BYTE*)&cltInfo4);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg4);
	
}

void cltServer::DoMsg_GAMEMSG_REQUEST_GAMEMSG_REQUEST_PARTYHALL_RESERVATION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Reservation* pclinfo = (cltGameMsgRequest_PartyHall_Reservation*)pclMsg->cData;

	//  ����Ʈ ��û�ϴ� �ڵ� �߰�.	
	if(pclCM->IsValidID(id) == false)
		return ;
	
    SI32		Personid    = pclCM->CR[id]->pclCI->GetPersonID();

	switch( pclinfo->m_siEntranceType )
	{
		case TYPE_ENTRANCE_VILLAGE:	
			 {
				if(0 >= pclCM->CR[id]->pclCI->clBI.siHomeVillage)
					return;
			 }
			 break;
		case TYPE_ENTRANCE_GUILD:	
			 {
				 if(0 >= pclCM->CR[id]->pclCI->clBI.clGuildRank.siGuildUnitIndex)
					 return;
			 }
			 break;		
	}

	cltPatyHallResvInfo* pPatyHallResvInfo = NULL;
	
	for(SI32 MapCount = 0; MapCount < MAX_PARTYHALL_MAP; ++MapCount)
	{
		pPatyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[MapCount][0];
		if(NULL == pPatyHallResvInfo)
			continue;
		
		for(SI32 ResvCount = 0; ResvCount < MAX_PARTYHALL_RESERVATION_INFO_LIST; ++ResvCount)
		{
			// �̹� ����
			if( Personid == pPatyHallResvInfo[ResvCount].m_siPersonID)
			{
				SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ALREADY_USER, 0, pclCM->CR[id]->GetCharUnique());		
				return;
			}

			// �̹� ������ ���ִ� �ð��̴�.
			if( pclinfo->m_siPartyHallIndex ==	MapCount										&&
				pclinfo->m_siHour			==	pPatyHallResvInfo[ResvCount].m_SystemTime.wHour	&&
				0							<	pPatyHallResvInfo[ResvCount].m_siPersonID			)
			{
				SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ALREADY_USER, 0, pclCM->CR[id]->GetCharUnique());		
				return;  
			}
		}
	}
	
	

	sDBRequest_PartyHall_Reservation sendMsg( 
											  id, 
											  Personid, 
											  pclinfo->m_siYear,	
											  pclinfo->m_siMonth,
											  pclinfo->m_siDay,	
											  pclinfo->m_siHour,
											  pclinfo->m_siMinute,
											  pclinfo->m_szReason,
											  pclinfo->m_siDecorationKind,
											  pclinfo->m_siEntranceType,
											  pclinfo->m_siValueType,
											  pclinfo->m_siPartyHallIndex,
											  pclinfo->m_ResvMoney,
											  pclinfo->m_siDecorationSlotNum,
											  pclCM->CR[id]->GetCurrentVillageUnique()
											); 
	pclGameDBProcess->SendMsg( (sPacketHeader*) &sendMsg );		

}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_ADD_PRESENT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Add_Present* pclinfo = (cltGameMsgRequest_PartyHall_Add_Present*)pclMsg->cData;

	//  ����Ʈ ��û�ϴ� �ڵ� �߰�.	  
	if(pclCM->IsValidID(id) == false)
		return ;

	SI32	Personid = pclCM->CR[id]->pclCI->GetPersonID(); 
	
	SI32 ResvIndex = pclClient->pclFeastManager->GetReveIndex(pclinfo->m_siPartyHallIndex, Personid);
	if(0 > ResvIndex)
		return;
	
	cltPatyHallResvInfo* pPatyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[pclinfo->m_siPartyHallIndex][ResvIndex];
	if(NULL == pPatyHallResvInfo)
		return;
		
	sDBRequest_PartyHall_Add_Present sendMsg(
												id, 
												pclinfo->m_siPartyHallIndex, 
												pclinfo->m_siItemSlotIndex,
												pclinfo->m_siItemUnique,
												pclinfo->m_siItemNum,
												&pPatyHallResvInfo->m_SystemTime,
												pclinfo->m_siPresentItemInvenPos
											);
				
	pclGameDBProcess->SendMsg((sPacketHeader*) &sendMsg);		
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Entrance_Application* pclinfo = (cltGameMsgRequest_PartyHall_Entrance_Application*)pclMsg->cData;

	//  ����Ʈ ��û�ϴ� �ڵ� �߰�.	
	if(pclCM->IsValidID(id) == false)
		return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	SI32 ReservationListIndex = sTime.wHour;
	
	// ����� ��Ƽ�� ��ȣ�� ������ ����Ʈ�� �����ͷ� ����.
	cltPatyHallResvInfo* pPatyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[pclinfo->m_siPartyIndex][ReservationListIndex];
	if( 0 >= pPatyHallResvInfo->m_siPersonID )
		return;
	
	// ����� ���� ���� ���.(����, ����, ���, �����)
	SI16 EntranceType = pPatyHallResvInfo->m_siEntranceType;  

	// ������ ��Ƽ���� ��ġ.
	POINT* pPartyHallUserPos = &pclClient->pclFeastManager->m_PartyHallUserPos[0];	
	if(NULL == pPartyHallUserPos)
		return;
	 
	// ��Ƽ���� ������ ������ ��� �̵�. 
	if( personid == pPatyHallResvInfo->m_siPersonID )
	{
		cltWarpInfo clWarpPirateShip(	1, 
										PARTYHALL_START_MAP_INDEX + pclinfo->m_siPartyIndex, 
										false, 
										false, 
										pPartyHallUserPos[pclinfo->m_siPartyIndex].x, 
										pPartyHallUserPos[pclinfo->m_siPartyIndex].y, 
										-1, 
										-1	);

		pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
		pclCM->CR[id]->Warp();
		return;
	}

	switch( EntranceType )
	{
		case TYPE_ENTRANCE_PUBLIC:	
			{
				// �׳� ����.
				cltWarpInfo clWarpPirateShip(	1, 
												PARTYHALL_START_MAP_INDEX + pclinfo->m_siPartyIndex, 
												false, 
												false, 
												pPartyHallUserPos[pclinfo->m_siPartyIndex].x, 
												pPartyHallUserPos[pclinfo->m_siPartyIndex].y, 
												-1, 
												-1	);

				pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
				pclCM->CR[id]->Warp();
			}
			break;
		case TYPE_ENTRANCE_VILLAGE:	
			{
				if( pPatyHallResvInfo->m_siValueType == pclClient->pclCM->CR[id]->pclCI->clBI.siHomeVillage )
				{
					cltWarpInfo clWarpPirateShip(	1, 
													PARTYHALL_START_MAP_INDEX + pclinfo->m_siPartyIndex, 
													false, 
													false, 
													pPartyHallUserPos[pclinfo->m_siPartyIndex].x, 
													pPartyHallUserPos[pclinfo->m_siPartyIndex].y, 
													-1, 
													-1	);

					pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
					pclCM->CR[id]->Warp();
				}
				else
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ETRANCE_RESERVATION_FAIL, 0, pclCM->CR[id]->GetCharUnique());		
					return;
				}
			}
			break;
		case TYPE_ENTRANCE_GUILD:	
			{
				if( pPatyHallResvInfo->m_siValueType == pclClient->pclCM->CR[id]->pclCI->clBI.clGuildRank.siGuildUnitIndex )
				{
					// ��尡 �����Ƿ� ��Ƽ������.
					cltWarpInfo clWarpPirateShip(	1, 
													PARTYHALL_START_MAP_INDEX + pclinfo->m_siPartyIndex, 
													false, 
													false, 
													pPartyHallUserPos[pclinfo->m_siPartyIndex].x, 
													pPartyHallUserPos[pclinfo->m_siPartyIndex].y, 
													-1, 
													-1	);


					pclCM->CR[id]->SetWarpInfo( &clWarpPirateShip, 1024 );
					pclCM->CR[id]->Warp();
				}
				else
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ETRANCE_RESERVATION_FAIL, 0, pclCM->CR[id]->GetCharUnique());		
					return;
				}
			}
			break;
		case TYPE_ENTRANCE_PRIVATE:	
			{
				SI32 EntranceApplicationIndex = -1;
			
				// ��û�� ���ִ��� �׸��� �ȵ��ִٸ� ����ִ� ó�� ����Ʈ�� �ε����� ��´�.
				for(SI32 ApplyCount = 0; ApplyCount < ENTRANCE_APPLICATION_LIST; ++ApplyCount)
				{
					//�̹� ��û�� �ߴ� 
					if(personid == pPatyHallResvInfo->m_clEntranceApplication[ApplyCount].m_siPersonID)
					{
						SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ETRANCE_RESERVATION, 0, pclCM->CR[id]->GetCharUnique());		
						return;
					}

					// ����ִ� ���� ��û ����Ʈ�� ���� ���Թ�ȣ�� ã�´�.
					if(  0 == pPatyHallResvInfo->m_clEntranceApplication[ApplyCount].m_siPersonID &&
						-1 == EntranceApplicationIndex												)
					{
						EntranceApplicationIndex = ApplyCount;		
					}
				}
				// -1�̸� ������ ������ ���̻� ���� ���� ��û�� �Ұ��� ��. 
				if( -1 == EntranceApplicationIndex )
				{
					SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ETRANCE_RESERVATION_FAIL, 0, pclCM->CR[id]->GetCharUnique());		
					return;
				}
				
				// �ش� ���Կ� ��û�ڸ� �ִ´�.
				pPatyHallResvInfo->m_clEntranceApplication[EntranceApplicationIndex].m_siPersonID = personid;
				pPatyHallResvInfo->m_clEntranceApplication[EntranceApplicationIndex].m_siLevel	  = pclCM->CR[id]->pclCI->clIP.GetLevel();

				// ���� ���� �ϷḦ Ŭ�󿡰� ������.
				SendServerResponseMsg(0, SRVAL_FAIL_PARTYHALL,  PARTYHALL_ETRANCE_RESERVATION, 0, pclCM->CR[id]->GetCharUnique());		
			}
			break;
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_ENTRANCE_APPLICATION_LIST( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Entrance_Application_List* pclInfo = (cltGameMsgRequest_PartyHall_Entrance_Application_List*)pclMsg->cData;

	//  ����Ʈ ��û�ϴ� �ڵ� �߰�.	
	if(pclCM->IsValidID(id) == false)
		return;
	
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltPatyHallResvInfo* pPartyHallResvInfo = NULL;
	cltPatyHallResvInfo* pPartyHallInfoList = (cltPatyHallResvInfo*)&pclClient->pclFeastManager->clPartyHallResvInfo[0];
	if(NULL == pPartyHallInfoList)
		return;

	SI32 ResvIndex = sTime.wHour;	// �ð��� ��Ƽ�� ���� ���Թ�ȣ�� ����.
	SI32 ResvId	   = 0;				// ������ ���̵�.
	
	// Ŭ�� ���� �޽����� ����~
	cltGameMsgResponse_PartyHall_Entrance_Application_List cltInfo;

	// ���� Ŭ�󿡰� ���� ����ü�� ���� ��û�� ����Ʈ�� ������.
	Entrance_Application_Info*	pSendInfo = cltInfo.m_ApplicationArray;
	if(NULL == pSendInfo)
		return;

	cltPartyHallEntranceApplication*	pServerInfo = NULL;
	
	for(SI32 PartyHalCount = 0; PartyHalCount < MAX_PARTYHALL_MAP; ++PartyHalCount)
	{
		pPartyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[PartyHalCount][0];
		if(NULL == pPartyHallResvInfo)
			continue;
			
		pServerInfo	= &pPartyHallResvInfo[ResvIndex].m_clEntranceApplication[0];
		if(NULL == pServerInfo)
			continue;
		
		// ��Ƽ �������� ��� ���� ��û�� ����Ʈ�� �ش�.
		if(personid == pPartyHallResvInfo[ResvIndex].m_siPersonID)
		{
			for(SI32 ArrayCount = 0; ArrayCount < MAX_PARTYHALL_APPLICATION_LIST; ArrayCount++, pSendInfo++, pServerInfo++)
			{
				ResvId = pclCM->GetIDFromPersonID(pServerInfo->m_siPersonID);
				// id�� 0 �̸� �����ڿ��� ����.
				if(0 == ResvId)
				{
					pServerInfo->m_siPersonID = 0;
					pServerInfo->m_siLevel    = 0;
					continue;
				}
				//  ������ ������ ������ ����Ʈ���� ����.
				if(false == pclCM->IsValidID(ResvId))
				{
					pServerInfo->m_siPersonID = 0;
					pServerInfo->m_siLevel    = 0;
					continue;
				}
				
				// ���������� ����ϸ� ����Ʈ�� ��´�.
				pSendInfo->m_siPersonID = pServerInfo->m_siPersonID;
				pSendInfo->m_siLevel	= pServerInfo->m_siLevel;
				MStrCpy(pSendInfo->m_szID, pclCM->CR[ResvId]->GetName(), sizeof(pSendInfo->m_szID));
			}
						
			// Ŭ�� �����ֱ�.			
			cltMsg clMsg(GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION_LIST, sizeof(cltGameMsgResponse_PartyHall_Entrance_Application_List), (BYTE*)&cltInfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			break;
		}
	}
}

void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_ADD_DECORATION( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_Add_Decoration* pclInfo = (cltGameMsgRequest_PartyHall_Add_Decoration*)pclMsg->cData;

	// ���ǰ �߰�.
	if(pclCM->IsValidID(id) == false)
		return ;
	
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	
	// ��Ĺ� ������ ���.
	PartyHall_Decoration* pDecorationList = pclClient->pclFeastManager->pclStruct[pclInfo->m_siViilageUnique]->clStrInfo.clFeastStrInfo.clDecoration;
	if(NULL == pDecorationList)
		return;

	// ���� ��Ĺ��� �ִ��� Ȯ��.
	bool DecorationSame	   = false;	
	SI32 DecorationAddSlot = -1;	
	for( SI32 DecorationCount = 0; DecorationCount < MAX_PARTYHALL_DECORATION_ITEM; ++DecorationCount )
	{
		if( pclInfo->m_siDecorationKind == pDecorationList[DecorationCount].m_DacorationKind )
		{
			DecorationAddSlot = DecorationCount;
			DecorationSame    = true;
			break;
		}
	}
		
	// ���� ��Ĺ��� ������ ��Ĺ��� ���� �� ��ġ�� ã��.
	if(false == DecorationSame)	
	{
		for( SI32 DecorationCount = 0; DecorationCount < MAX_PARTYHALL_DECORATION_ITEM; ++DecorationCount )
		{
			if( 0 >= pDecorationList[DecorationCount].m_DacorationKind )
			{
				DecorationAddSlot = DecorationCount;
				break;
			}
		}
	}

	sDBRequest_PartyHall_Add_Decoration sendMsg( id, personid, pclInfo->m_siViilageUnique, pclInfo->m_siDecorationKind,
															   pclInfo->m_siDecorationNum, DecorationAddSlot, pclInfo->m_DeleteItem );
	pclGameDBProcess->SendMsg( (sPacketHeader*) &sendMsg );
}

// ���� �ֱ�.
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_GIVEITEM( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_PartyHall_GiveItem* pclInfo = (cltGameMsgRequest_PartyHall_GiveItem*)pclMsg->cData;
	
	if(pclCM->IsValidID(id) == false)
		return;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	cltPatyHallResvInfo* pPartyHallResvInfoList	= NULL;
	cltPatyHallResvInfo* pPartyHallInfoList		= (cltPatyHallResvInfo*)&pclClient->pclFeastManager->clPartyHallResvInfo[0];
	if(NULL == pPartyHallInfoList)
		return;

	for(SI32 PartyHalCount = 0; PartyHalCount < MAX_PARTYHALL_MAP; ++PartyHalCount)
	{
		pPartyHallResvInfoList = &pclClient->pclFeastManager->clPartyHallResvInfo[ PartyHalCount ][ 0 ];
		if(NULL == pPartyHallResvInfoList)
			continue;

		for(SI32 ResvCount = 0; ResvCount < MAX_PARTYHALL_RESERVATION_INFO_LIST; ++ResvCount )
		{
			if( personid == pPartyHallResvInfoList[ResvCount].m_siPersonID )
			{
				// �ش� ��Ƽ���� ��ϵ� ������ DB�� ���� ��û.
				sDBRequest_PartyHall_GiveItem sendMsg;
				sendMsg.m_siPartyHallIndex  = PartyHalCount;
				sendMsg.m_siPersonID		= personid;
				memcpy(&sendMsg.m_SystemTime, &sTime, sizeof(sendMsg.m_SystemTime));

				//[����] ��Ƽ�忡 ������ �����ٶ� ��, ��, ��, �ø� �����ϰ� �������� 0���� ä���. => 2008-9-12
				//		 ����� ������ ��� �������� ���ֱ� ������.
				sendMsg.m_SystemTime.wDayOfWeek		= 0;
				sendMsg.m_SystemTime.wMinute		= 0;
				sendMsg.m_SystemTime.wSecond		= 0;
				sendMsg.m_SystemTime.wMilliseconds	= 0;

				pclGameDBProcess->SendMsg( (sPacketHeader*) &sendMsg );
				return;
			}
		}
	}
}


void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_INVITATION( cltMsg* pclMsg, SI32 id )
{
	SI32* pclInfo = (SI32*)pclMsg->cData;

	SI32 PersonID = *pclInfo;

	SI32 ResvID = pclCM->GetIDFromPersonID(PersonID);	// �������� ���̵�.

	cltPatyHallResvInfo*				pPartyHallResvInfo   = NULL;
	Entrance_Application_Info*			pSendInfo			 = NULL;
	cltPartyHallEntranceApplication*	pApplication		 = NULL;


	// Ŭ�� ���� ���ŵ� ��û�ڸ���Ʈ ������ ���� ����ü.
	cltGameMsgResponse_PartyHall_Entrance_Application_List cltInfo;

	SI32 ResvIndex = sTime.wHour;							// ���� �ð��� �ٷ� ������ �迭�� �ε���.
	SI32 personid  = pclCM->CR[id]->pclCI->GetPersonID();	// ��û�㰡�� ���ִ� �� ���̵�.
	
	for(SI32 PartyHalCount = 0; PartyHalCount < MAX_PARTYHALL_MAP; ++PartyHalCount)
	{
		pPartyHallResvInfo = &pclClient->pclFeastManager->clPartyHallResvInfo[ PartyHalCount ][ 0 ];
		if(NULL == pPartyHallResvInfo)
			continue;

		pSendInfo = cltInfo.m_ApplicationArray;
		if(NULL == pSendInfo)
			continue;

		pApplication = &pPartyHallResvInfo[ ResvIndex ].m_clEntranceApplication[0];
		if(NULL == pApplication)
			continue;
		
		if(personid == pPartyHallResvInfo[ ResvIndex ].m_siPersonID)
		{
			for(SI32 ArrayCount = 0; ArrayCount < MAX_PARTYHALL_APPLICATION_LIST; ArrayCount++, pApplication++)
			{
				// ������ ����� ������ �����Ѵ�.
				if(false == pclCM->IsValidID(pclCM->GetIDFromPersonID(pApplication->m_siPersonID)))
				{
					pApplication->m_siPersonID = 0;
					pApplication->m_siLevel    = 0;
					continue;
				}
				
				// ��û�ڸ� �̽�Ʈ���� �����Ѵ�. �ؿ��� ResvID�� ��û�ڸ� ������Ų��.
				if(PersonID == pApplication->m_siPersonID)
				{	
					pApplication->m_siPersonID = 0;
					pApplication->m_siLevel    = 0;
					continue;
				}		
				
				// �������� ��û�ڸ� ��û�� ����Ʈ�� ��´�.
				pSendInfo->m_siPersonID = pApplication->m_siPersonID;
				pSendInfo->m_siLevel	= pApplication->m_siLevel;
				MStrCpy( pSendInfo->m_szID, pclCM->CR[pclCM->GetIDFromPersonID(pApplication->m_siPersonID)]->GetName(), sizeof(pSendInfo->m_szID) );
				pSendInfo++; 
			}
			break; // �̹� ��Ƽ���� ã�� ��û�ڸ� Ȯ���Ͽ� ����Ʈ�� ��������Ƿ� �ݺ��� ����.
		}
	}
	
	// ���� �ٲ� ���� ��û�� ����Ʈ�� �����ش�.
	cltMsg clMsg(GAMEMSG_RESPONSE_PARTYHALL_ENTRANCE_APPLICATION_LIST, sizeof(cltGameMsgResponse_PartyHall_Entrance_Application_List), (BYTE*)&cltInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
	// ��û���� ���� ���θ� Ȯ���Ѵ�.
	if(pclCM->IsValidID(ResvID) == false)
		return;

	// ��Ƽ�忡 ������ų ��ġ ����Ʈ.
	POINT* pPartyHallUserPos = &pclClient->pclFeastManager->m_PartyHallUserPos[0];
	if(NULL == pPartyHallUserPos)
		return;
	
	// ��Ƽ���� �ƴϸ� ����.
	if( pclCM->CR[id]->GetMapIndex() < PARTYHALL_START_MAP_INDEX )
		return;

	// ��Ƽ�� ��ȣ�� ������ų ��ġ�� ������ؼ�...
	SI32 PosIndex = pclCM->CR[id]->GetMapIndex() - PARTYHALL_START_MAP_INDEX;

	cltWarpInfo clWarpPirateShip(1, pclCM->CR[id]->GetMapIndex(), false, false, 
									pPartyHallUserPos[PosIndex].x, pPartyHallUserPos[PosIndex].y, -1, -1);

	pclCM->CR[ResvID]->SetWarpInfo( &clWarpPirateShip, 1024 );
	pclCM->CR[ResvID]->Warp();
}

// ��Ƽ�� ����.		
void cltServer::DoMsg_GAMEMSG_REQUEST_PARTYHALL_USEEFFECT( cltMsg* pclMsg, SI32 id )
{
	cltGameMsgRequest_FeastUseEffect* pclinfo = (cltGameMsgRequest_FeastUseEffect*)pclMsg->cData;

	if(pclCM->IsValidID(id) == false)
		return;

	// �����̿�� üũ
	// �����̿�� ��ȣ ���� ��
	SI16 itemunique = ITEMUNIQUE(24060); // ���ڽ������̿��  14200 -> 24060

	SI32 pos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( itemunique );
	if( pos < 0 )
	{
		// ���ڽ������̿�� ����
		SendServerResponseMsg( RANKTYPE_FEAST, SRVAL_FEAST_FAIL_USEEFFECT_NOTHAVETICKET, 0, 0, pclCM->CR[id]->GetCharUnique());	
		return;
	}

	// ��踦 ����. 
	pclItemManager->AddUseNum(itemunique, 1);

	cltItem clitem;
	clitem.Init();

	clitem.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[ pos ] );
	clitem.SetItemNum( 1 );

	// ���� ������ ���.
	sDBRequest_UseItem useitem(id, pclCM->CR[id]->pclCI->GetPersonID(), pos, &clitem, USEITEM_REASON_NONE);
	pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);	

	
	SI16 siStartPosX = (SI16)pclCM->CR[id]->GetX();
	SI16 siStartPosY = (SI16)pclCM->CR[id]->GetY();

	// ���߻��.
	cltGameMsgResponse_FeastUseEffect sendMsg( &pclinfo->siEffectNum[0], cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE, siStartPosX, siStartPosY);
	cltMsg clMsg( GAMEMSG_RESPONSE_FEAST_USEEFFECT, sizeof( sendMsg ), (BYTE*)&sendMsg );
	
	// �ش� �ʿ� �ִ� ������ ��� ������ �����ش�.
	SI32 SendUserMapIndex = pclCM->CR[id]->GetMapIndex();
	for(SI32 UserCount = 1; UserCount < MAX_PERSON_NUMBER; ++UserCount)
	{
		if(false == pclCM->IsValidID(UserCount))
			continue;

		if(pclCM->CR[UserCount]->GetMapIndex() == SendUserMapIndex)
		{
			pclCM->CR[UserCount]->SendNetMsg((sPacketHeader*)&clMsg);
		}
	}
}



//#endif