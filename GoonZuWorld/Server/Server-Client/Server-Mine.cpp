// server-mine
#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Mine.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\Msg\\MsgType-Mine.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_CHANGECONTRACT(cltMsg* pclMsg, SI32 id )
{

	//�޽����� Ȯ���Ѵ�. 
	cltGameMsgRequest_MineChangeContract *pclpacket = (cltGameMsgRequest_MineChangeContract *)pclMsg->cData;

	if( pclpacket->clRentContract.IsValid() == FALSE ) return ;

	SI32 returnval	= SRVAL_MINE_FAIL_SETCONTRACT;

	//----------------------------------
	// ��û�ڰ� ������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique == 0 ) return ;

	cltSimpleRank clrank(RANKTYPE_MINE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		return ;
	}

	// ��� �Ⱓ�� Ȯ���Ѵ�. 
	if( pclpacket->clRentContract.siRentPeriod <= 0 || 
		pclpacket->clRentContract.siRentPeriod > MAX_RENT_PERIOD_YEAR ) return;
	
	// �Ӵ�ݾ��� Ȯ���Ѵ�. 
	if( pclpacket->clRentContract.siRentFee < MIN_MINE_RENT_FEE || 
		pclpacket->clRentContract.siRentFee > MAX_MINE_RENT_FEE) return ;

	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_MINE );

	if( pStrInfo == NULL ) return;

	if( pclpacket->clRentContract.siRentFee < pStrInfo->clMineStrInfo.clRentContract.siRentFee - 10000 ||
		pclpacket->clRentContract.siRentFee > pStrInfo->clMineStrInfo.clRentContract.siRentFee + 10000 ) {

		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_SETCONTRACT_WRONGFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	if( pclTime->clDate.GetDateVary() < 
		pStrInfo->clMineStrInfo.clLastChangeDate.GetDateVary() + 30 ) {

		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_SETCONTRACT_DATE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return;
	}

	
	//-----------------------------------
	// ��� �������� ����Ѵ�. 
	//-----------------------------------
	pclpacket->clRentContract.clDate.Set(&pclTime->clDate);
	pclpacket->clRentContract.clDate.AddMonth(pclpacket->clRentContract.siRentPeriod * 12);

	
	// DB�Ŵ������� ��� ������ �����ϵ��� ��û�Ѵ�. 
	sDBRequest_MineChangeContract clMsg(id, pclpacket->siVillageUnique, &pclpacket->clRentContract, &pclTime->clDate );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_UNITLIST(cltMsg* pclMsg, SI32 id )
{

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID <= 0 ) return;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	//------------------------------------------------------------
	// �ش� �����ǿ��� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	//------------------------------------------------------------
	cltGameMsgResponse_MineUnitList clInfo( villageunique );

	cltMine *pclMine;
	pclMine = (cltMine *)pclMineManager->pclStruct[ villageunique ];

	for( SI32 i = 0; i < MAX_MINEUNIT_NUMBER; i++ ) {
		clInfo.clPerson[i].Set( &pclMine->GetMineUnit(i)->clPerson );
	}

	cltMsg clMsg( GAMEMSG_RESPONSE_MINE_UNITLIST, sizeof(clInfo), (BYTE*)&clInfo );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_UNITDETAIL(cltMsg* pclMsg, SI32 id )
{

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	//-----------------------------------
	// �ش� ������ ������� Ȯ���Ѵ�. 
	//-----------------------------------
	cltSimpleRank clrank(RANKTYPE_MINE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		return ;
	}

	//------------------------------------------------------------
	// �ش� ������ ���꿡�� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	//------------------------------------------------------------
	cltGameMsgResponse_MineUnitListDetail clInfo(villageunique);

	cltMine *pclMine = (cltMine *)pclMineManager->pclStruct[villageunique];

	for(SI32 i = 0;i < MAX_MINEUNIT_NUMBER;i++)
	{
		clInfo.clContract[i].Set( &pclMine->GetMineUnit(i)->clContract );
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_MINE_UNITDETAIL, sizeof(clInfo), (BYTE*)&clInfo );	
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}


void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_RENTAPPLY(cltMsg* pclMsg, SI32 id )
{

	// Ŭ���̾�Ʈ�� ������ ��� ������ Ȯ���Ѵ�.
	cltGameMsgRequest_MineRentApply* pclpacket = (cltGameMsgRequest_MineRentApply*) pclMsg->cData;
	
	cltRentContract* pclcontract = &pclpacket->clRentContract;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	// �Ӵ�Ⱓ�� �������ϸ� ����. 
	if( pclcontract->siRentPeriod <= 0 || 
		pclcontract->siRentPeriod > MAX_RENT_PERIOD_YEAR )return ;
	
	// �⺻ ���� ������ ������Ű�� ���ϸ� ����. 
//	if( pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE )return ;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��¥�� ���´�. 
	pclcontract->clDate.Set(&pclTime->clDate);
	

	// �ش� ������ ������ǰ� ���Ͽ� �������� ������ ����. 
	cltMine *pclMine;

	pclMine = (cltMine*)pclMineManager->pclStruct[ villageunique ];

	if( pclMine->IsSameContract( pclcontract ) == FALSE)
	{
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_APPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// ���� ���°� �־�� �Ѵ�. 
	cltAccountNum*	pclAccountNum = &pclCM->CR[id]->pclCI->clBank.clAccountNum;
	if( pclAccountNum->GetAccountNum() == 0 )
	{
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_APPLY_NOACCOUNT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// �̹� ��ϵǾ� ������ ����. 
	cltRentApplyer* pclapplyer = pclMine->GetMineApplyerFromPersonID( personid );
	if( pclapplyer )
	{		
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_APPLY_ALREADYAPPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
			
	// ��û�ڷ� ����Ѵ�.
	sDBRequest_MineRentApply clMsg( id, villageunique, personid, pclcontract );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_CANCELAPPLY(cltMsg* pclMsg, SI32 id )
{

	// personidȮ��. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique == 0 )return ;

	// DB�� ��Ҹ� ��û�Ѵ�. 
	sDBRequest_MineCancelRentApply clMsg(id, villageunique, personid);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_APPLYERLIST(cltMsg* pclMsg, SI32 id )
{

	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0) return;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;
	
	
	cltSimpleRank clrank(RANKTYPE_MINE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE) {
		return;
	}
	
	cltGameMsgResponse_MineApplyerList sendMsg( villageunique );

	cltMine *pclMine;

	// �ش� ������ ���꿡�� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	for( SI32 i = 0; i < MAX_APPLY_PER_MINE; i++ )
	{
		pclMine = (cltMine *)pclMineManager->pclStruct[ villageunique ];

		sendMsg.clMineApplyer[ i ].Set( pclMine->GetRentApplyer( i ) );			
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_MINE_APPLYERLIST, sizeof(sendMsg), (BYTE*)&sendMsg );
	
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_DELAPPLYER(cltMsg* pclMsg, SI32 id )
{
	// [�߰� : Ȳ���� 2007. 11. 2 ���� ����� ����� ������ �����ϴ� ���� ����. ������ ������ ���Թ�ȣ��.]
	SI32 Slot = (SI32)*pclMsg->cData;


	// ������ ����ũ�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	// PersonID�� Ȯ���Ѵ�. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;


	//-----------------------------------
	// �ش� ������ ���� ������� Ȯ���Ѵ�. 
	//-----------------------------------
	cltSimpleRank clrank(RANKTYPE_MINE, villageunique);
	if(pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		return ;
	}
	
	//-----------------------------------
	// DB�� ����� ������ ���� ��û�Ѵ�.
	//-----------------------------------
	sDBRequest_MineDelApplyer clMsg(id, personid, villageunique, Slot);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_MINE_RENT(cltMsg* pclMsg, SI32 id )
{

	// �Ӵ� ��û�� Ȯ���Ѵ�. 
	cltGameMsgRequest_MineRent* pclrent = (cltGameMsgRequest_MineRent *)pclMsg->cData;


	//----------------------------------
	// ��û�ڰ� ������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0) return;
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if( villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	cltSimpleRank clrank( RANKTYPE_MINE, villageunique );
	if( pclRankManager->IsRank( PersonID, &clrank) == FALSE )
	{
		return ;
	}
	
	//----------------------------
	// �󱤻��� �ִ��� Ȯ���Ѵ�. 
	//----------------------------
	cltMine *pclMine;
	pclMine = (cltMine *)pclMineManager->pclStruct[ villageunique ];

	if( pclMine == NULL ) return;

	if( pclMine->IsEmpty( pclrent->siIndex ) == FALSE )
	{
		// �� ������ ��� �Ӵ��� �� ����.
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_RENT_NOTEMPTY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------
	// ��û�ڰ� ��ȿ���� Ȯ���Ѵ�.
	//---------------------------------
	if(pclrent->siPersonID == 0)
	{
		// ���� ����ڰ� ��ȿ���� �ʴ�. 
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_RENT_INVALIDPERSONID,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	
	cltRentApplyer* pclapplyer = pclMine->GetMineApplyerFromPersonID( pclrent->siPersonID );
	if( pclapplyer == NULL )
	{
		// ���� ����ڰ� ��ȿ���� �ʴ�. 
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_RENT_INVALIDPERSONID,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	
	//---------------------------------
	// �������� ������ ��� ����� �������� Ȯ���Ѵ�. 
	//---------------------------------
	// ��� ������ Ȯ���Ѵ�. 
	cltStrInfo* pclStrInfo = GetStrInfo( villageunique, RANKTYPE_MINE );
	if( pclStrInfo == NULL )return ;

	cltRentContract clcontract;
	clcontract.Set( &pclStrInfo->clMineStrInfo.clRentContract );

	if( pclapplyer->clContract.IsSame( &clcontract ) == false)
	{
		SendServerResponseMsg(RANKTYPE_MINE, SRVAL_MINE_FAIL_NOTSAMECONTRACT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//--------------------------------
	// �� ������ �������� ����Ѵ�. 
	//--------------------------------
	// ���� ��¥�� ������� �����Ѵ�. 
	clcontract.clDate.Set(&pclTime->clDate);

	// DBManager���� �Ӵ븦 ��û�Ѵ�.
	sDBRequest_MineRent clMsg( id, villageunique, pclrent->siPersonID, pclrent->siIndex, &clcontract );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);


}

