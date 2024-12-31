//---------------------------------
// 2003/6/26 ���°�
//---------------------------------
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-House.h"

#include "..\Client\Interface\HouseUnit\HouseUnitBaseInfo.h"

#include "MsgRval-Define.h"
#include "..\CommonLogic\MsgType-House.h"
#include "..\CommonLogic\MsgType-Person.h"

#include "../CommonLogic/RealEstate/RealEstate.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Item.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

// â�� �̸� ����
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITNAMECHANGE(cltMsg* pclMsg, SI32 id)
{
	//�޽����� Ȯ���Ѵ�. 
	cltGameMsgRequest_ChangeHouseUnitName* pclData= (cltGameMsgRequest_ChangeHouseUnitName*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer(id);
	if( NULL == pclChar)
		return;
	
	if(m_pCAbuseFilter->CheckAbuseWord(pclData->m_szHouseName))
	{
		return;
	}

	SI32 siVillageunique = pclChar->GetCurrentVillageUnique();
	if(siVillageunique <= 0 || siVillageunique >= MAX_VILLAGE_NUMBER)	return ;

	if( siVillageunique != pclData->m_siVillageUnique)
		return;

	sDBRequest_ChangeHouseUnitName clSendMsg(id, pclChar->pclCI->GetPersonID(), siVillageunique, pclData->m_siHouseIndex, pclData->m_szHouseName);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clSendMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_CHANGEHOUSECONTRACT(cltMsg* pclMsg, SI32 id)
{

	//�޽����� Ȯ���Ѵ�. 
	cltRentContractPacket* pclpacket = (cltRentContractPacket*)pclMsg->cData;
	if(pclpacket->clRentContract.IsValid() == FALSE)return ;

	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;


	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;

	cltSimpleRank clrank(RANKTYPE_HOUSE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ��������� �ƴ϶� ��� ���� ���濡 ����. 
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILSETCONTRACT_NOTCHIEF,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// ��� �Ⱓ�� Ȯ���Ѵ�. 
	if(pclpacket->clRentContract.siRentPeriod <= 0 || pclpacket->clRentContract.siRentPeriod > MAX_RENT_PERIOD_YEAR)return ;

	// �Ӵ�ݾ��� Ȯ���Ѵ�. 
	if(pclpacket->clRentContract.siRentFee < MIN_HOUSE_RENT_FEE || pclpacket->clRentContract.siRentFee > MAX_HOUSE_RENT_FEE)return ;


	cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_HOUSE );

	if( pStrInfo == NULL ) return;

	if( pclpacket->clRentContract.siRentFee < pStrInfo->clHouseStrInfo.clRentContract.siRentFee - 10000 ||
		pclpacket->clRentContract.siRentFee > pStrInfo->clHouseStrInfo.clRentContract.siRentFee + 10000 ) 
	{
			SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILSETCONTRACT_WRONGFEE,  0, 0, pclCM->CR[id]->GetCharUnique());
			return;
	}

	if( pclTime->clDate.GetDateVary() < 
		pStrInfo->clHouseStrInfo.clLastChangeDate.GetDateVary() + 30 ) 
	{
			SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILSETCONTRACT_DATE,  0, 0, pclCM->CR[id]->GetCharUnique());
				return;
	}

	//-----------------------------------
	// ��� �������� ����Ѵ�. 
	//-----------------------------------
	pclpacket->clRentContract.clDate.Set(&pclTime->clDate);
	pclpacket->clRentContract.clDate.AddMonth(pclpacket->clRentContract.siRentPeriod * 12);


	// DB�Ŵ������� ��� ������ �����ϵ��� ��û�Ѵ�. 
	sDBRequest_ChangeHouseContract clMsg(id, pclpacket->siVillageUnique, &pclpacket->clRentContract, &pclTime->clDate );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

// ���� ����Ʈ�� ��û�Ѵ�. (������ ��û�� �� �ִ�. )
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITLIST(cltMsg* pclMsg, SI32 id)
{
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	//------------------------------------------------------------
	// �ش� ������ �������� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	//------------------------------------------------------------
	cltGameMsgRequest_HouseUnitList clInfo(villageunique);
	cltGameMsgResponse_MyHouseUnitList clMyHouseList;

	SI32 siMyHouseIndex = 0;
	const SI32 YEARTOMONTH = 12;

	for(SI32 i = 0;i < MAX_HOUSEUNIT_NUMBER;i++)
	{
		// ������ �Ͽ콺���ֿ� ���� RealEstateMarketManager�� ��ǰ���� ��ϵǾ��ִ� �Ͽ콺�������� Ȯ��
		bool b = pclRealEstateMarketManager->IsExistOrder( PersonID, villageunique, i);

		clInfo.clPerson[i].Set(&pclHouseManager->pclStruct[villageunique]->GetHouseUnit(i)->clPerson);

		clInfo.bSell[i] = b;

		// �ڽ��� ���� ���� ���
		if( PersonID == clInfo.clPerson[i].GetPersonID())
		{
			cltHouseUnit* pclHouseUnit = pclHouseManager->pclStruct[villageunique]->GetHouseUnit(i);
			if( NULL != pclHouseUnit)
			{
				cltMyHouseInfo clMyHouseInfo( i, pclHouseUnit->m_szName , &pclHouseUnit->clContract);

				clMyHouseList.clMyHouseInfo[siMyHouseIndex].Set(&clMyHouseInfo);
				++siMyHouseIndex;
			}
		}
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITLIST, sizeof(clInfo), (BYTE*)&clInfo);	
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	if( IsCountrySwitch(Switch_ChangeHouseList))
	{
		// [����] �ڽ��� ���� ���� �߰� ����
		cltMsg clMsgExtend(GAMEMSG_RESPONSE_MYHOUSEUNITLIST, sizeof(clMyHouseList), (BYTE*)&clMyHouseList);	
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsgExtend);
	}	
}

// ���� �� ���� ����Ʈ�� ��û�Ѵ�. (���� ����� ��û�� �� �ִ�.  )
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITLIST_DETAIL(cltMsg* pclMsg, SI32 id)
{
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;

	//-----------------------------------
	// �ش� ������ ����������� Ȯ���Ѵ�. 
	//-----------------------------------
	cltSimpleRank clrank(RANKTYPE_HOUSE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		return ;
	}

	//------------------------------------------------------------
	// �ش� ������ �������� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	//------------------------------------------------------------
	cltGameMsgRequest_HouseUnitListDetail clInfo(villageunique);

	for(SI32 i = 0;i < MAX_HOUSEUNIT_NUMBER;i++)
	{
		clInfo.clContract[i].Set(&pclHouseManager->pclStruct[villageunique]->GetHouseUnit(i)->clContract);
	}

	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITLIST_DETAIL, sizeof(clInfo), (BYTE*)&clInfo);

	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
}



// ���� ���� ����� ����� �����Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_DELHOUSEAPPLYER(cltMsg* pclMsg, SI32 id)
{
	// PCK : ���� ����ڸ� ��� �����ϴ°��� ����.
	SI32 Slot = (SI32)*pclMsg->cData;

	// ������ ����ũ�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)	return ;

	// PersonID�� Ȯ���Ѵ�. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)		return ;

	//-----------------------------------
	// �ش� ������ ����������� Ȯ���Ѵ�. 
	//-----------------------------------
	cltSimpleRank clrank(RANKTYPE_HOUSE, villageunique);
	if(pclRankManager->IsRank(personid, &clrank) == FALSE)
	{
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILDELHOUSEAPPLYER_NOTCHIEF,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//-----------------------------------
	// DB�� ����� ������ ���� ��û�Ѵ�.
	//-----------------------------------
	sDBRequest_DelHouseApplyer clMsg(id, personid, villageunique, Slot);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}



void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEAPPLYERLIST(cltMsg* pclMsg, SI32 id)
{

	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;


	cltSimpleRank clrank(RANKTYPE_HOUSE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ��������� �ƴ϶� ��� ���� ���濡 ����. 
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILSETCONTRACT_NOTCHIEF,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}


	// �ش� ������ �������� ������ ���ؼ� Ŭ���̾�Ʈ�� ������. 
	for(SI32 i = 0;i < MAX_APPLY_PER_HOUSE;i++)
	{
		cltHouseApplyerPacket sendMsg(i, pclHouseManager->pclStruct[villageunique]->GetHouseApplyer(i) );

		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEAPPLYERLIST, sizeof(cltHouseApplyerPacket), (BYTE*)&sendMsg);		
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}

// ���� �ؾ��� ���� ������� ��û�ؿԴ�
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSECANCELLATIONPENALTYMONEY(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HouseCancellationPenaltyMoney* pclinfo = (cltGameMsgRequest_HouseCancellationPenaltyMoney*)pclMsg->cData;

	GMONEY siPenaltyMoney = 0; // �����
	GMONEY siRentMoney = 0; // ���� �Ӵ��

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0 ) return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER) return ;

	SI32 villageunique = pclinfo->siVillageUnique;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;
	SI32 houseunitslot = pclinfo->siHouseIndex;
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return ;
	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if(pclHouseManager->IsHouseHost(personid, villageunique, houseunitslot) == false)return ;

	// ���� ����ó�� ��


	// ����� ����
	cltHouseUnit* pclhouse = pclHouseManager->GetHouseUnit(villageunique,houseunitslot);
	if( pclhouse == NULL) return;
	cltServer * pclserver = (cltServer*)pclClient;

	siRentMoney = pclhouse->clContract.siRentFee;

	siPenaltyMoney = siRentMoney ;	// ������� 1ȸ�� ��� �Ӵ�� �� �Ѵ�.

	cltGameMsgResponse_HouseCancellationPenaltyMoney sendMsg(siPenaltyMoney);
	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSECANCELLATIONPENALTYMONEY,sizeof(sendMsg), (BYTE*)&sendMsg );
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSECANCELLATION(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HouseCancellation* pclinfo = (cltGameMsgRequest_HouseCancellation*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0 ) return;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER) return ;

	SI32 villageunique = pclinfo->siVillageUnique;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;
	SI32 houseunitslot = pclinfo->siHouseIndex;
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return ;
	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if(pclHouseManager->IsHouseHost(personid, villageunique, houseunitslot) == false)return ;

	// ���� ����ó�� ��
	// ������, ��, ��ȯ���� �����ȿ� �ֳ� Ȯ���Ѵ�.
	cltHouseUnitStorageInfo* pclstg = pclHouseManager->GetStgPointer(villageunique, houseunitslot);
	if(pclstg == NULL)return ;

	if(pclstg->IsItemRemaind() || pclstg->IsHorseRemaind() || pclstg->IsSummonRemaind())
	{
		SendServerResponseMsg( RANKTYPE_HOUSE, SRVAL_HOUSE_FAILREMAINDITEM,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}

	// ����� ��� ����
	// ����� ����
	cltHouseUnit* pclhouse = pclHouseManager->GetHouseUnit(villageunique,houseunitslot);
	if( pclhouse == NULL) return;


	cltServer * pclserver = (cltServer*)pclClient;

	GMONEY siRentMoney = pclhouse->clContract.siRentFee;
	// SI32 siRemainDay =  5; //pclhouse->clContract.clDate.GetDay() + pclhouse->clContract.siRentPeriod - pclserver->pclTime->clDate.uiDay;
	GMONEY siPenaltyMoney = siRentMoney; // * siRemainDay * 0.1f;

	// ������ �������� ������� ���Ͽ� ���� �ִ��� üũ

	if( siPenaltyMoney > pclCM->CR[id]->pclCI->clIP.GetMoney() ) {
		SendServerResponseMsg( RANKTYPE_HOUSE, SRVAL_HOUSE_FAILNOTENOUGHMONEY,  0, 0, pclCM->CR[id]->GetCharUnique() );
		return;
	}	

	// ������ �̸��� �˾ƿ´�.
	const TCHAR* pOwnerName = pclCM->CR[id]->GetName();

	// DB�� ���� �����޶�� ��û ����, ������ ����ݵ� ������ ������ �����ݿ��� �����Ѵ�.
	sDBRequest_RecallHouse clMsg(personid, HOUSERECALL_REASON_CANCELLATION, villageunique, houseunitslot, siPenaltyMoney,pOwnerName);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, siPenaltyMoney);
}

// Ư�� ���������� ���� ��û�� ����Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSERENTAPPLYCANCEL(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgRequest_HouseRentApplyCancel* pclinfo = (cltGameMsgRequest_HouseRentApplyCancel*)pclMsg->cData;

	// personidȮ��. 
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// ���� ����ũ�� Ȯ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return;
	if(villageunique != pclinfo->siVillageUnique)					return;

	// DB�� ��Ҹ� ��û�Ѵ�. 
	sDBRequest_HouseRentApplyCancel clMsg(id, villageunique, personid);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� �Ӵ� ���(����� ��û�ڸ� ��Ͽ��� �������� ��)
	//	// 
	//	cltServer* pclserver = (cltServer*)pclClient;
	//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RENTAPPLYCANCEL,
	//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, villageunique, 0, 0, 
	//									0, 0, 0, 0, 0, NULL, NULL);
	//}
}

// ������ ��û�Ѵ�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSERENTAPPLY(cltMsg* pclMsg, SI32 id)
{
	// Ŭ���̾�Ʈ�� ������ ��� ������ Ȯ���Ѵ�.
	cltRentContractPacket* pclpacket = (cltRentContractPacket*) pclMsg->cData;
	SI32 sivillageunique = pclpacket->siVillageUnique;
	if(sivillageunique <= 0 || sivillageunique >= MAX_VILLAGE_NUMBER)	return ;
	cltRentContract* pclcontract = &pclpacket->clRentContract;

	// �Ӵ�Ⱓ�� �������ϸ� ����. 
	if(pclcontract->siRentPeriod <= 0 || pclcontract->siRentPeriod > MAX_RENT_PERIOD_YEAR)return ;

	// �⺻ ���� ������ ������Ű�� ���ϸ� ����. 
	if(pclCM->CR[id]->pclCI->clIP.GetLevel() < LEVELLIMIT_USE_HOUSE)return ;


	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	// ��¥�� ���´�. 
	pclcontract->clDate.Set(&pclTime->clDate);

	// �ش� ������ ������ǰ� ���Ͽ� �������� ������ ����. 
	if(pclHouseManager->IsSameContract(sivillageunique, pclcontract) == FALSE)
	{
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILAPPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// ���� ���°� �־�� �Ѵ�. 
	cltAccountNum*	pclAccountNum = &pclCM->CR[id]->pclCI->clBank.clAccountNum;
	if(pclAccountNum->GetAccountNum() == 0)
	{
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILAPPLY_NOACCOUNT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// �̹� ��ϵǾ� ������ ����. 
	cltRentApplyer* pclapplyer = pclHouseManager->GetHouseApplyerFromPersonID(sivillageunique, personid);
	if(pclapplyer)
	{
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILAPPLY_ALREADYAPPLY,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	// ��û�ڷ� ����Ѵ�.
	sDBRequest_HouseRentApply clMsg(id, sivillageunique, personid, pclcontract);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSERENT(cltMsg* pclMsg, SI32 id)
{

	// �Ӵ� ��û�� Ȯ���Ѵ�. 
	cltRequestRent* pclrent = (cltRequestRent*)pclMsg->cData;

	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if(PersonID <= 0)return ;


	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)	return ;


	cltSimpleRank clrank(RANKTYPE_HOUSE, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ��������� �ƴ϶� ��� ���� ���濡 ����. 
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILSETCONTRACT_NOTCHIEF,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//----------------------------
	// ������� �ִ��� Ȯ���Ѵ�. 
	//----------------------------
	if(pclHouseManager->IsEmpty(pclrent->siVillageUnique, pclrent->siSlot) == FALSE)
	{
		// �� ������ ��� �Ӵ��� �� ����.
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_NOEMPTYHOUSE,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------
	// ��û�ڰ� ��ȿ���� Ȯ���Ѵ�.
	//---------------------------------
	if(pclrent->siPersonID == 0)
	{
		// ���� ����ڰ� ��ȿ���� �ʴ�. 
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_INVALIDHOUSEAPPLYER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	cltRentApplyer* pclapplyer = pclHouseManager->GetHouseApplyerFromPersonID(pclrent->siVillageUnique, pclrent->siPersonID);
	if(pclapplyer == NULL)
	{
		// ���� ����ڰ� ��ȿ���� �ʴ�. 
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_INVALIDHOUSEAPPLYER,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//---------------------------------
	// �������� ������ ��� ����� �������� Ȯ���Ѵ�. 
	//---------------------------------
	// ��� ������ Ȯ���Ѵ�. 
	cltStrInfo* pclvary = pclHouseManager->GetStrInfo(pclrent->siVillageUnique);
	if(pclvary == NULL)return ;

	// �Ӵ�ᰡ 0������ üũ�Ѵ�.
	if(pclvary->clHouseStrInfo.clRentContract.siRentFee <= 0)
		return;

	cltRentContract clcontract;
	clcontract.Set(&pclvary->clHouseStrInfo.clRentContract);

	if(pclapplyer->clContract.IsSame(&clcontract) == false)
	{
		SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILNOTSAMECONTRACT,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	//--------------------------------
	// �� ������ �������� ����Ѵ�. 
	//--------------------------------
	// ���� ��¥�� ������� �����Ѵ�. 
	clcontract.clDate.Set(&pclTime->clDate);

	// DBManager���� �Ӵ븦 ��û�Ѵ�.
	sDBRequest_HouseRent clMsg(id, pclrent->siVillageUnique, pclrent->siPersonID, pclrent->siSlot, &clcontract, (TCHAR*)pclCM->CR[id]->GetName());
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

// �κ����� â��� �������� �̵�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_MOVEITEMINVTOSTG(cltMsg* pclMsg, SI32 id)
{

	stHouseUnitData* pclinfo = (stHouseUnitData*)pclMsg->cData;


	MOVEITEMINVTOSTG(id, pclinfo->si32VillageUnique, pclinfo->si32HouseUnitSlot, pclinfo->si32lParam1, &pclinfo->clItem);

	//------------------------------------------
	// ���Ⱓ�� Ȯ���Ѵ�.
	//------------------------------------------

}

BOOL cltServer::MOVEITEMINVTOSTG(SI32 siCharId, SI32 siVillageUnique, SI32 siHouseIndex, SI32 siItemPos, cltItem* pclInvenItem, bool bNoMoveNewPos)
{
	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)return FALSE;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[siCharId]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return FALSE;

	//----------------------------------------------
	// â�� �������� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//---------------------------------------------
	SI32 personid		= pclCM->CR[siCharId]->pclCI->GetPersonID();
	if(personid <= 0)return FALSE;


	if( NULL == pclInvenItem)
		return FALSE;

	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[siCharId];

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();


	//----------------------------------------------
	// �κ��� ������ �ش� ��ǰ�� �ִ��� Ȯ���Ѵ�. 
	//----------------------------------------------
	SI32 frompos = siItemPos;
	if(frompos < 0 || frompos >= MAX_ITEM_PER_PERSON)return FALSE;

	cltItem* pclitem = &pclCM->CR[siCharId]->pclCI->clCharItem.clItem[frompos];

	// ���� ���������� ���Ѵ�. 
	cltItem clitem1;
	clitem1.Set(pclInvenItem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(pclitem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)return FALSE;

	// ������ �������� Ȯ���Ѵ�. 
	if(pclInvenItem->GetItemNum() >  pclitem->GetItemNum())return FALSE;

	//------------------------------------------------------
	// ��ƼȦ���� ���� �������� ������ �� ����.
	//------------------------------------------------------
	if( pclitem->clItemCommon.clCommonInfo.uiGetItemReason == cltItemCommonInfo::REASON_GIVE_PARTYHALL_ITEM )	
		return FALSE;

	// �ͼ����� ���λ���
	if( pclchar->clShopData.m_siSelectedSpacialInventoryPos == frompos	)
	{
		// ���� �������� ������ �����ϴ��� üũ 
		if( pclchar->clShopData.m_clSpacialItem.siUnique > 0 )
		{  
			SendServerResponseMsg(0, SRVAL_CANNOTMOVEITEM_PERSONALSHOP, 0, 0, siCharId );
			return FALSE;
		}
	}

	//------------------------------------------------------
	//�޸� ��� �������̶�� â��� �̵� �Ұ�
	//------------------------------------------------------
	if( NULL != this->pclDormancySystem)
	{
		CDormancyEquipItemRewardServer *pclRewardServer = (CDormancyEquipItemRewardServer *) this->pclDormancySystem->GetDormancyEquipItemReward();
		if( NULL != pclRewardServer)
		{
			if( TRUE == pclRewardServer->IsDormancyEquipItem(pclInvenItem->siUnique))
			{
				SendServerResponseMsg(0, SRVAL_FAIL_MOVE_ITEM_INHOUSE, 0, 0, siCharId );
				return FALSE;
			}
		}
	}

	//�Ⱓ�� �������� ��� ���� ���Ⱓ�� �ִ��� Ȯ���Ѵ�.
	SI32 itemunique = pclInvenItem->siUnique ;
	if ( itemunique > 0 )
	{
		if ( pclInvenItem->IsHaveUseDay() )  //[����] ���� ���Ⱓ ���� �˸�
		{
			SI32 useableDay = 0;
			BOOL rVal = GetItemUseAbleDay(pclInvenItem,&useableDay);
			if(rVal == FALSE) return FALSE;

			if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
			{
				//KHY - 0723 - �Ⱓ������ �ı� ����.
				if(pclClient->IsCountrySwitch( Switch_DateOverItemNoDestroy) )
				{
					return FALSE;	
				}
				else
				{
					// �Ⱓ�� ���� ���ǰ�� â�� ���� �� ����. - by LEEKH
					if( pclInvenItem->clItemCommon.clCommonInfo.uiRareInfo == RARELEVEL_5 )
					{
						// �޽��� ���
						return FALSE;
					}
					else
					{
						// ������ �������� �����ش�.
						sDBRequest_UseItem useitem(siCharId,pclCM->CR[siCharId]->pclCI->GetPersonID(),frompos,pclInvenItem,USEITEM_REASON_DATEOVER);
						pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

						cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclInvenItem->siUnique, useableDay);
						cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
						pclCM->CR[siCharId]->SendNetMsg((sPacketHeader*)&clMsg );				
					}
					return FALSE;
				}
			}
		}
	}

	/*	SI32 NotUsingData;
	if ( pclItemManager->GetLimitDateItemValue( clitem1.siUnique, &NotUsingData ) )
	{
	return;
	}*/
	// SJY DEBUG

	/*cyj �̺�Ʈ ����������ũ ����
	if ( clitem1.siUnique == ITEMUNIQUE(8150) ||
	clitem1.siUnique == ITEMUNIQUE(14300) ||
	clitem1.siUnique == ITEMUNIQUE(14400) ||
	clitem1.siUnique == ITEMUNIQUE(14500) ) // �ݰ��Ǳ�� ��
	{
	return ;
	}
	*/
	SI32 PersonID		= pclchar->pclCI->GetPersonID()	;

	// �ش�â�� ������� �������� Ȯ���Ѵ�.
	if(pclHouseManager->IsHouseHost(personid, siVillageUnique, siHouseIndex) == false)return FALSE;

	// ������ �ȷ��� �������� Ȯ��
	for ( SI32 i=0 ; i<MAX_REALESTATEMARKET_ORDER_NUMBER;i++) 
	{
		if ( siVillageUnique > 0 &&  PersonID> 0 ) 
		{
			if( pclRealEstateMarketManager->pclRealEstateOrder[i].siVillageUnique == siVillageUnique )
			{
				if(pclRealEstateMarketManager->pclRealEstateOrder[i].siPersonID ==   PersonID && 
					pclRealEstateMarketManager->pclRealEstateOrder[i].siHouseIndex == siHouseIndex)
				{
					return	FALSE;
				}
			}			
		}
	}

	if(pclRealEstateMarketManager->IsExistOrder(personid, siVillageUnique, siHouseIndex))
	{
		cltItemInfo* pcliteminfo = pclItemManager->FindItemInfo( pclInvenItem->siUnique );
		if (pcliteminfo == NULL) return FALSE;

		if (pcliteminfo->IsItemInfoAtb(ITEMINFOATB_NOTTRADE) ||pclInvenItem->IsBelonging(pclItemManager))
		{
			SendServerResponseMsg(RANKTYPE_HOUSE, SRVAL_HOUSE_FAILINPUT_NOTRADEITEM,  0, 0, pclCM->CR[siCharId]->GetCharUnique());
			return FALSE;
		}
	}

	// �ش� â�� ���ڸ��� �ִ��� Ȯ���Ѵ�. 
	SI32 sitopos;
	if(pclHouseManager->CanAddStg(siVillageUnique, siHouseIndex, pclItemManager, pclInvenItem, &sitopos) == false)
	{
		SendServerResponseMsg( RANKTYPE_HOUSE, SRVAL_HOUSE_FAILINPUT_FULLSTG,  0, 0, pclCM->CR[siCharId]->GetCharUnique() );
		return FALSE;
	}

	if( true == bNoMoveNewPos)
	{
		cltItem *pclItem = pclHouseManager->GetStgItemPointer(siVillageUnique, siHouseIndex, sitopos);
		if(NULL == pclItem)
			return FALSE;
		if( 0 == pclItem->siUnique)
			return FALSE;
	}

	if( true == pclchar->bPersonalShopSwitch ||
		true == pclchar->bPremiumPersonalShop )
	{
		for(SI32 i = 0; i < MAX_SHOP_ITEM_NUMBER; ++i)
		{
			if( pclchar->clShopData.m_clItem[i].siUnique == pclInvenItem->siUnique  )
			{
				SendServerResponseMsg(0, SRVAL_FAIL_PERSONALSHOP_MOVEITEM, 0, 0, siCharId);
				return FALSE;
			}
		}
	}

	//----------------------------------------------
	// �������� �ű⵵�� DBManager���� ��û�Ѵ�. 
	//----------------------------------------------
	sDBRequest_MoveItemInvToStg clMsg(siCharId, personid, frompos, siVillageUnique, siHouseIndex, sitopos, pclInvenItem, pclInvenItem->CanPile(pclItemManager));
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return TRUE;
}

// â���� �κ����� ������ �̵�. 
void cltServer::DoMsg_GAMEMSG_REQUEST_MOVEITEMSTGTOINV(cltMsg* pclMsg, SI32 id)
{
	stHouseUnitData* pclinfo = (stHouseUnitData*)pclMsg->cData;

	//--------------------------------------------
	// ������ ���� ������ �������� ������� �ʴ´�. 
	//--------------------------------------------
	if(dwDBLatency > 3000)return ;


	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return ;


	//------------------------------------------
	// â�� ���� ��ǰ�� �ִ��� Ȯ���Ѵ�.
	//-----------------------------------------
	SI32 personid		= pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;



	cltCharServer* pclchar = (cltCharServer*)pclCM->CR[id];

	//---------------------------------------------
	// ���� �Ǿ� �ִ� ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->ItemUseReserveAction();

	//---------------------------------------------
	// ���� �Ǿ� �ִ� źȯ������ ����� �ִٸ� ó���Ѵ�. 
	//---------------------------------------------
	pclchar->BulletUseReserveAction();

	SI32 villageunique	= pclinfo->si32VillageUnique;
	SI32 houseunitslot	= pclinfo->si32HouseUnitSlot;

	// �ش�â�� ������� �������� Ȯ���Ѵ�.
	if(pclHouseManager->IsHouseHost(personid, villageunique, houseunitslot) == false)return ;	
	// �������� ������ �ִ��� Ȯ���Ѵ�. 
	SI32 frompos = pclinfo->si32lParam1;
	if(frompos < 0 || frompos >= MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER)return ;

	cltItem* pclitem = pclHouseManager->GetStgItemPointer(villageunique, houseunitslot, frompos);
	if(pclitem == NULL)return ;

	// â��� �������� �ʴ´�.
/*	if(pclClient->IsCountrySwitch(Switch_FourLeaf))
	{
		//[����] ����ũ�ι��� ���� ����Ҽ� ���� �Ÿ� ������ ���Ѵ�. => 2008-8-14
		if( ITEMUNIQUE(2755) == pclitem->siUnique || ITEMUNIQUE(2754) == pclitem->siUnique )	
		{	
			if( pclitem->siUnique != siFourLeafUnique )	
			{
				SendServerResponseMsg( 0, SRVAL_RETURN_NOT_USE_FOURLEAF, 0, 0, pclchar->GetID() );
				return;	
			}
		}
	}*/

	// ���� ���������� ���Ѵ�. 
	cltItem clitem1;
	clitem1.Set(&pclinfo->clItem);
	clitem1.SetItemNum(1);

	cltItem clitem2;
	clitem2.Set(pclitem);
	clitem2.SetItemNum(1);

	if(clitem1.IsSame(&clitem2, false) == FALSE)return ;

	// ������ �������� Ȯ���Ѵ�. 
	if(pclinfo->clItem.GetItemNum() >  pclitem->GetItemNum())return ;

	//------------------------------------------
	// �κ��� ��ǰ�� ���� ������ �ִ��� Ȯ���Ѵ�. 
	//------------------------------------------
	SI16 invpos;
	cltItem cltoitem;
	SI32 rtnvalue;
	if(pclchar->CanAddInv(INVMODE_ALL, &pclinfo->clItem, &invpos, &cltoitem, &rtnvalue) == false)return ;

	//------------------------------------------
	// �������� �ű⵵�� DBManager���� ��û�Ѵ�. 
	//------------------------------------------
	sDBRequest_MoveItemStgToInv clMsg(id, villageunique, houseunitslot, frompos, personid, invpos, &pclinfo->clItem, pclinfo->clItem.CanPile(pclItemManager));
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
} 

// â�������� ��û. 
void cltServer::DoMsg_GAMEMSG_REQUEST_STGINFO(cltMsg* pclMsg, SI32 id)
{
	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();
	if(personid <= 0)return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return ;


	GameMsgRequest_HouseUnitStgInfo* pclinfo = (GameMsgRequest_HouseUnitStgInfo*)pclMsg->cData;
	SI32 villageunique = pclinfo->siVillageUnique;
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;
	SI32 houseunitslot = pclinfo->siHouseUnitSlot;
	if(houseunitslot < 0 || houseunitslot >= MAX_HOUSEUNIT_NUMBER)return ;

	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if(pclHouseManager->IsHouseHost(personid, villageunique, houseunitslot) == false)return ;


	//------------------------------------------
	// â���� ������ Client�� ������. 
	//------------------------------------------
	cltHouseUnitStorageInfo* pclstg = pclHouseManager->GetStgPointer(villageunique, houseunitslot);
	if(pclstg == NULL)return ;

	GameMsgResponse_HouseUnitStgInfo clInfo(villageunique, houseunitslot, pclstg);
	cltMsg clMsg(GAMEMSG_RESPONSE_STGINFO, sizeof(clInfo), (BYTE*)&clInfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

}

// ������ �������� ������ �޶�� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITSTABLECREATE(cltMsg* pclMsg, SI32 id)
{
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return ;


	cltGameMsgRequest_HouseUnitStableCreate *pclinfo = (cltGameMsgRequest_HouseUnitStableCreate *)pclMsg->cData;

	SI32 VillageUnique = pclinfo->siVillageUnique;
	if( VillageUnique <= 0 || VillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return ;
	}
	SI32 HouseUnitSlot = pclinfo->siHouseUnitSlot;
	if( HouseUnitSlot < 0 || HouseUnitSlot >= MAX_HOUSEUNIT_NUMBER )
	{
		return ;
	}

	SI32 CreateStableIndex = pclinfo->siCreateStableIndex;
	if ( CreateStableIndex < 0 || CreateStableIndex >= MAX_HOUSEUNIT_HORSENUMBER )
	{
		return;
	}

	//------------------------------------------
	// ���� �������� �����ϴ��� üũ ( �� á�� ����̰ų�, �� ���� ��ȣ�� Ʋ�� ��쿡�� �׳� return (���ʷ� �����Ƿ�... ) )
	//------------------------------------------
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( VillageUnique, HouseUnitSlot );
	if( pclStg == NULL ) return ;

	for ( SI16 i = 0; i < MAX_HOUSEUNIT_HORSENUMBER; ++i )
	{
		if ( pclStg->bCreatedHouseUnitStable[ i ] == false )
		{
			if ( i == pclinfo->siCreateStableIndex )
			{
				break;
			}
		}
	}

	// ������ ���� ������ ���ų�, �� ���� ��ȣ�� Ŭ���̾�Ʈ�� ���� ���̶� Ʋ����
	if ( i == MAX_HOUSEUNIT_HORSENUMBER )
	{
		return;
	}

	/*
	//------------------------------------------
	// �������� ����� ���� ����(MAX_HOUSEUNIT_CREATESTABLEFEE) �̻��� �ݾ��� �����ϰ� �ִ��� Ȯ�� 
	//------------------------------------------
	if ( pclCM->CR[id]->pclCI->clIP.GetMoney() < MAX_HOUSEUNIT_CREATESTABLEFEE )
	{
	return;
	}
	*/

	//------------------------------------------
	// �̿���� �ִ��� üũ
	//------------------------------------------
	//SI16 ItemUnique = ITEMUNIQUE(24025);		// ���������̿��
	//SI32 ItemPos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( ItemUnique );
	//if ( ItemPos < 0 )
	//{
	//	return;
	//}

	//if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ ItemPos ].siItemNum < HOUSEUNIT_CREATESTABLE_USEITEMNUM )
	//{
	//	return;
	//}
	//------------------------------------------
	// �������� �ִ��� üũ
	//------------------------------------------
	GMONEY siNeedMoney = HOUSEUNIT_CREATESTABLE_NEEDMONEY * pclItemManager->clItemStatistic.siNPCPriceRate;

	if ( siNeedMoney == 0 || pclCM->CR[id]->pclCI->clIP.GetMoney() < siNeedMoney )
	{
		return;
	}

	//cltItem clTempItem;
	//clTempItem.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[ ItemPos ] );
	//clTempItem.siItemNum = HOUSEUNIT_CREATESTABLE_USEITEMNUM;


	/*
	// ������ ���µ��� ���� ���� ���� ����
	//------------------------------------------
	// ���� ������ �´��� Ȯ�� ( ���� 1������ ������ 1���� 2������ ������ 2���� ����... )
	//------------------------------------------
	cltStrInfo *pStrInfo = GetStrInfo( VillageUnique, RANKTYPE_CITYHALL );

	if ( pStrInfo == NULL )
	{
	return;
	}

	// ���� ������ 0�ΰ��
	if ( pStrInfo->clCityhallStrInfo.siVillageLevel < 1 )
	{
	SendServerResponseMsg(0, SRVAL_HOUSE_VILLAGELEVELLIMIT, 1, 0, id);
	return;
	}

	// ���� ������ ���Ƽ� ���������� ������ �� ����.
	if ( i >= pStrInfo->clCityhallStrInfo.siVillageLevel )
	{
	SendServerResponseMsg(0, SRVAL_HOUSE_VILLAGELEVELLIMIT, pStrInfo->clCityhallStrInfo.siVillageLevel + 1, 0, id);
	return;
	}
	*/

	//------------------------------------------
	// �������� �����϶�� DB �� ��û
	//------------------------------------------	
	sDBRequest_HouseUnitStableCreate clMsg( id, PersonID, VillageUnique, HouseUnitSlot, siNeedMoney, pclinfo->siCreateStableIndex );	
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_TAX, siNeedMoney);

	return;
}

// ������ ���� �־� �޶�� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITHORSEIN(cltMsg* pclMsg, SI32 id)
{
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill == 0)return ;

	// �� �ֱ�
	cltGameMsgRequest_HouseUnitHorseIn *pclinfo = (cltGameMsgRequest_HouseUnitHorseIn *)pclMsg->cData;

	SI32 VillageUnique = pclinfo->siVillageUnique;
	if( VillageUnique <= 0 || VillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return ;
	}
	SI32 HouseUnitSlot = pclinfo->siHouseUnitSlot;
	if( HouseUnitSlot < 0 || HouseUnitSlot >= MAX_HOUSEUNIT_NUMBER )
	{
		return ;
	}

	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if( pclHouseManager->IsHouseHost( PersonID, VillageUnique, HouseUnitSlot ) == false )
	{
		return;
	}

	//------------------------------------------
	// Person���� ���� �ִ��� Ȯ�� ( ���� �־�� ������ ���� �� �����Ƿ�... )
	// Person���� ���� �ִٸ�, ���� ������ Ȯ�� ( ���� �� ���������� Ȯ�� �ʿ���� ) ���, �� ���� Ȯ�ε� �ʿ����.
	// Person�� ���� Ÿ�� �ִٸ� ���� �ع���
	// �� �κ��丮�� �������� �ִٸ� ���� �ع���
	//------------------------------------------
	// ������ Ÿ�� �����Ƿ�...
	if ( pclCM->CR[id]->pclCI->clHorseInfo.siCurrentHorseRIDEHORSE == true )
	{
		return;
	}

	cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
	if ( pclHorse == NULL)
	{
		return;
	}
	SI32 horseindex	= pclCM->CR[id]->pclCI->clHorseInfo.siCurrentShowHorse;

	// ���� ������ Ʋ��
	if ( pclHorse->siHorseUnique != pclinfo->siHorseUnique )
	{
		return;
	}


	// �� �κ��丮�� �������� �ִ��� Ȯ��
	if ( pclCM->CR[id]->pclCI->clCharItem.IsHorseHaveItem() == true )
	{
		return;
	}
	// ������ �ȷ��� �������� Ȯ��
	for ( SI32 i=0 ; i<MAX_REALESTATEMARKET_ORDER_NUMBER;i++) 
	{
		if ( VillageUnique > 0 && PersonID > 0 ) 
		{
			if( pclRealEstateMarketManager->pclRealEstateOrder[i].siVillageUnique == VillageUnique )
			{
				if(pclRealEstateMarketManager->pclRealEstateOrder[i].siPersonID == PersonID && 
				pclRealEstateMarketManager->pclRealEstateOrder[i].siHouseIndex == HouseUnitSlot)
				{
					return	;
				}
			}			
		}
	}

	//------------------------------------------
	// ������ ���� ���� �� �ִ� ���� ã�´�.
	//------------------------------------------
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( VillageUnique, HouseUnitSlot );
	if( pclStg == NULL ) return ;

	/*
	SI16 HorseAvailableAddPos = -1;
	if ( pclStg->CanAddHorse( &HorseAvailableAddPos ) == false )
	{		
	return;
	}
	*/

	SI16 HorseAvailableAddPos = pclinfo->siStgHorseIndex;
	// ���� ���� �� �ִ��� üũ
	if ( pclStg->CanAddHorse( &HorseAvailableAddPos ) == false )
	{
		// ���� �ִٸ�, �ٲܼ� �����Ƿ�(change) ���� �ִ��� üũ	
		if ( ! pclStg->IsHorseExist( HorseAvailableAddPos ) )
		{
			return;
		}		
	}

	//------------------------------------------
	// ���� �������� �ű�⸦ DB�� ��û
	//------------------------------------------
	sDBRequest_HouseUnitHorseIn clMsg( id, PersonID, VillageUnique, HouseUnitSlot, horseindex, HorseAvailableAddPos );
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	return;
}

// �������� ���� ���� �޶�� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITHORSEOUT(cltMsg* pclMsg, SI32 id)
{
	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return ;


	cltGameMsgRequest_HouseUnitHorseOut *pclinfo = (cltGameMsgRequest_HouseUnitHorseOut *)pclMsg->cData;

	if ( pclinfo->siStgHorseIndex < 0 || pclinfo->siStgHorseIndex >= MAX_HOUSEUNIT_HORSENUMBER )
	{
		return;
	}

	if ( pclinfo->siStgHorseUnique < 1 )
	{
		return;
	}

	SI32 VillageUnique = pclinfo->siVillageUnique;
	if( VillageUnique <= 0 || VillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return ;
	}
	SI32 HouseUnitSlot = pclinfo->siHouseUnitSlot;
	if( HouseUnitSlot < 0 || HouseUnitSlot >= MAX_HOUSEUNIT_NUMBER )
	{
		return ;
	}	

	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if( pclHouseManager->IsHouseHost( PersonID, VillageUnique, HouseUnitSlot ) == false )
	{
		return;
	}

	//------------------------------------------
	// ���� �� ����Ʈ �� ��ġ�� �� ���� �ִ��� Ȯ��
	//------------------------------------------
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( VillageUnique, HouseUnitSlot );
	if( pclStg == NULL ) return ;

	if ( pclStg->clHorse[ pclinfo->siStgHorseIndex ].siHorseUnique < 1 ||
		pclStg->clHorse[ pclinfo->siStgHorseIndex ].siHorseUnique != pclinfo->siStgHorseUnique )
	{
		return;
	}

	/*
	// ������� ���� ������ ������ �� ��ġ�� �ִ� ���� �ٲٱ�� ����. (���� �Ʒ��� ���� �ִ��� �������� Ȯ���� �ʿ䰡 ���� )
	//------------------------------------------
	// Person���� ���� ������ Ȯ�� ( ���� ����� Person ���� ���� �� �� �����Ƿ�... )
	//------------------------------------------
	cltHorse* pclHorse = &pclCM->CR[id]->pclCI->clHorseInfo.clHorse;
	if ( pclHorse == NULL )
	{
	return;
	}
	*/	

	SI32 index = pclCM->CR[id]->pclCI->clHorseInfo.FindEmptyHorseIndex();
	if( index < 0 )
	{
		cltHorse* pclHorse = pclCM->CR[id]->pclCI->clHorseInfo.GetCurrentShowHorse();
		if ( pclHorse == NULL)
		{
			return;
		}

		SI32 horseindex	= pclCM->CR[id]->pclCI->clHorseInfo.siCurrentShowHorse;

		sDBRequest_HouseUnitHorseOut clMsg( id, PersonID, VillageUnique, HouseUnitSlot, pclinfo->siStgHorseIndex, horseindex );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		return;
	}
	else
	{
		//------------------------------------------
		// �������� ���� ������ ������� �־� �ֱ⸦ DB�� ��û�Ѵ�.
		//------------------------------------------
		sDBRequest_HouseUnitHorseOut clMsg( id, PersonID, VillageUnique, HouseUnitSlot, pclinfo->siStgHorseIndex, index );
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	}

	return;
}

// �������� ������ �����϶�� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITUSEDGOODSBUILDINGCREATE(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill <= 0 || curvill >= MAX_VILLAGE_NUMBER)	return ;

	cltGameMsgRequest_HouseUnitUsedGoodsBuildingCreate *pclinfo = (cltGameMsgRequest_HouseUnitUsedGoodsBuildingCreate *)pclMsg->cData;

	SI32 VillageUnique = pclinfo->siVillageUnique;
	if( VillageUnique <= 0 || VillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return ;
	}

	SI32 HouseUnitSlot = pclinfo->siHouseUnitSlot;
	if( HouseUnitSlot < 0 || HouseUnitSlot >= MAX_HOUSEUNIT_NUMBER )
	{
		return ;
	}

	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if( pclHouseManager->IsHouseHost( PersonID, VillageUnique, HouseUnitSlot ) == false )
	{
		return;
	}

	//------------------------------------------
	// ������ �Ǽ��� �� �ִ��� Ȯ��
	//------------------------------------------
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( VillageUnique, HouseUnitSlot );
	if( pclStg == NULL ) return ;


	if ( pclStg->bCreatedHouseUnitUsedGoodsBuilding )
	{
		return;
	}

	//------------------------------------------
	// �̿���� �ִ��� üũ
	//------------------------------------------
	SI16 ItemUnique = ITEMUNIQUE(24025);		// ���������̿��  14080 ->   24025
	SI32 ItemPos = pclCM->CR[id]->pclCI->clCharItem.GetItemPos( ItemUnique );
	if ( ItemPos < 0 )
	{
		return;
	}

	if ( pclCM->CR[id]->pclCI->clCharItem.clItem[ ItemPos ].siItemNum < HOUSEUNIT_CREATEUSEDGOODSBUILDING_USEITEMNUM )
	{
		return;
	}

	cltItem clTempItem;
	clTempItem.Set( &pclCM->CR[id]->pclCI->clCharItem.clItem[ ItemPos ] );
	clTempItem.siItemNum = HOUSEUNIT_CREATEUSEDGOODSBUILDING_USEITEMNUM;

	sDBRequest_HouseUnitUsedGoodsBuildingCreate clMsg( id, PersonID, VillageUnique, HouseUnitSlot, ItemPos, &clTempItem );
	pclGameDBProcess->SendMsg( (sPacketHeader *) &clMsg );

	return;
}

// ������ �������� �̾Ƴ��� ���� ������ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill == 0)return ;

	cltGameMsgRequest_HouseUnitMakeItemFromUsedGoodsInfo *pclinfo = (cltGameMsgRequest_HouseUnitMakeItemFromUsedGoodsInfo*)pclMsg->cData;
	if ( pclinfo->clItem.siUnique < 1 || pclinfo->clItem.siItemNum < 1 )
	{
		return;
	}

	// ������ �Ӽ� Ȯ��
	if ( pclItemManager->GetItemAtb( pclinfo->clItem.siUnique ) & ITEMATB_OBJECT )
	{
	}
	else
	{
		return;
	}

	cltItem clItemList[ MAX_MATERIAL_NUMBER ];
	SI16 i = 0;

	for ( i = 0; i < MAX_MATERIAL_NUMBER; ++i )
	{
		clItemList[i].Init();
	}

	cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclItemManager;
	SI16 MakePercent = 0;
	if( ! pclitemmanager->GetDismantleMaterial( (cltCharServer *)pclCM->CR[id],  pclinfo->clItem, clItemList, &MakePercent ) )
	{
		return;
	}

	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsInfo clinfo( clItemList );
	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	return;
}

// ������ �������� �̾Ƴ���� ��û
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODS(cltMsg* pclMsg, SI32 id)
{
	if ( pclCM->IsValidID( id ) == FALSE )
	{
		return;
	}

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	if( PersonID < 1 )return ;

	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 curvill = pclCM->CR[id]->GetCurrentVillageUnique();
	if(curvill == 0)return ;

	cltGameMsgRequest_HouseUnitMakeItemFromUsedGoods *pclinfo = (cltGameMsgRequest_HouseUnitMakeItemFromUsedGoods*)pclMsg->cData;

	SI32 VillageUnique = pclinfo->siVillageUnique;
	if( VillageUnique <= 0 || VillageUnique >= MAX_VILLAGE_NUMBER )
	{
		return ;
	}

	SI32 HouseUnitSlot = pclinfo->siHouseUnitSlot;
	if( HouseUnitSlot < 0 || HouseUnitSlot >= MAX_HOUSEUNIT_NUMBER )
	{
		return ;
	}

	if ( pclinfo->siItemPos < 0 || pclinfo->siItemPos >= MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER )
	{
		return;
	}

	if ( pclinfo->clItem.siUnique < 1 || pclinfo->clItem.siItemNum < 1 )
	{
		return;
	}

	// ������ �Ӽ� Ȯ��
	if ( pclItemManager->GetItemAtb( pclinfo->clItem.siUnique ) & ITEMATB_OBJECT )
	{

	}
	else
	{
		return;
	}

	//------------------------------------------
	// Person�� �ش� â���� �������� Ȯ���Ѵ�.
	//------------------------------------------
	if( pclHouseManager->IsHouseHost( PersonID, VillageUnique, HouseUnitSlot ) == false )
	{
		return;
	}

	//------------------------------------------
	// ������ �Ǽ��Ǿ� �ִ��� Ȯ��
	//------------------------------------------
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( VillageUnique, HouseUnitSlot );
	if( pclStg == NULL ) return ;


	if ( ! pclStg->bCreatedHouseUnitUsedGoodsBuilding )
	{
		return;
	}

	//------------------------------------------
	// ������ �Ҹ�� �������� �ִ��� Ȯ��
	//------------------------------------------
	cltItem* pclitem = pclHouseManager->GetStgItemPointer( VillageUnique, HouseUnitSlot, pclinfo->siItemPos );
	if(pclitem == NULL)
		return;

	if ( ! pclitem->IsSame( &pclinfo->clItem, true ) )
	{
		return;
	}

	if ( pclCM->CR[id]->GetGameMasterLevel() <= BASIC_GAMEMASTER_LEVEL &&
		pclitem->GetMaxDurability() > DUR_FOR_DISMANTLE )
	{
		return;
	}

	SI16 ItemPosList[ MAX_MATERIAL_NUMBER ];
	cltItem clItemList[ MAX_MATERIAL_NUMBER ];
	SI16 i = 0;

	for ( i = 0; i < MAX_MATERIAL_NUMBER; ++i )
	{
		ItemPosList[i] = -1;
		clItemList[i].Init();
	}

	cltItemManagerServer* pclitemmanager = (cltItemManagerServer*)pclItemManager;
	SI16 MakePercent = 0;
	//if( ! pclitemmanager->GetDismantleMaterial( (cltCharServer *)pclCM->CR[id],  pclinfo->clItem, clItemList, &MakePercent ) )
	//{
	//	return;
	//}

	SI16 Counter = 0;
	SI16 PreCounter = 0;
	bool InputAvailable = false;

	for ( SI16 j = 0; j < MAX_MATERIAL_NUMBER; ++j )
	{
		if ( clItemList[ j ].siUnique > 0 )
		{
			InputAvailable = false;

			for ( i = 0; i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER; ++i )
			{
				if ( pclStg->clItem[ i ].siUnique == clItemList[ j ].siUnique )
				{
					// ������ ��ø ���� �ʰ�
					if ( pclStg->clItem[i].siItemNum + clItemList[ j ].siItemNum >= MAX_ITEM_PILE_NUMBER )
					{
						return;
					}

					ItemPosList[j]  = i;
					InputAvailable = true;
					break;
				}
				else if ( pclStg->clItem[ i ].siUnique == 0 && ItemPosList[j] == -1 )
				{
					if ( PreCounter > 0 )
					{
						--PreCounter;
						continue;
					}

					ItemPosList[j] = i;
					++Counter;
					PreCounter = Counter;
					InputAvailable = true;
				}
			}

			// â�� ���� �� ����.
			if ( ! InputAvailable )
			{
				return;
			}
		}
	}



	sDBRequest_HouseUnitMakeItemFromUsedGoods clMsg( id, PersonID, 
													VillageUnique, HouseUnitSlot, 
													pclinfo->siItemPos, pclinfo->clItem.siUnique,
													ItemPosList, clItemList, MakePercent );
	pclGameDBProcess->SendMsg( (sPacketHeader *) &clMsg );

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
	//	// [�α��߰� : Ȳ���� 2007. 10. 15] // �� �ϴ� ��ǰ MakePercent = 59% (ȸ����)
	//	// param1 == �ε����� ��ȣ, 
	//	// param2 == ������ ��ġ, 
	//	// param3 == ������ ����ũ,
	//	// param4 == Ȯ��, 
	//	cltServer* pclserver = (cltServer*)pclClient;
	//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_SALVAGEFROM,
	//									0, (cltCharServer*)pclCM->CR[id], NULL, PersonID, 0, 0, clItemList, 0, 0, 0, VillageUnique, 0, 0, 
	//									HouseUnitSlot, pclinfo->siItemPos, pclinfo->clItem.siUnique, MakePercent, 0, NULL, NULL);
	//}

	return;
}

void cltServer::RefreshHouseUnit()
{
	for( int i = 1; i < MAX_VILLAGE_NUMBER; ++i ) {

		if(pclVillageManager->pclVillageInfo[i])
		{
			// ���� ������ ������ ��û�Ѵ�. 
			{
				sDBRequest_ManyHouseUnit clMsg(0, i);
				pclGameDBProcess->SendMsg( (sPacketHeader *)&clMsg );
			}
		}
	}
}

// â�� ������ ����
void cltServer::DoMsg_GAMEMSG_REQUEST_HOUSEITEMARRANGEMENT(cltMsg* pclMsg, SI32 id)
{
	cltGameMsgResponse_ArrangeHouseItem* pclinfo = (cltGameMsgResponse_ArrangeHouseItem*)pclMsg->cData;

	cltCharServer* pclChar = pclCM->GetCharServer(id);

	if(NULL == pclChar)
		return;

	BOOL bArrangement = FALSE;

	for(SI32 i = 0; i < MAX_ITEM_PER_PERSON; i++)
	{
		cltItem* pclitem = &pclCM->CR[id]->pclCI->clCharItem.clItem[i];

		if ( TRUE == MOVEITEMINVTOSTG(id , pclinfo->m_siVillageUnique, pclinfo->m_siHouseIndex, i, pclitem, true))
		{
			bArrangement = TRUE;
		}
	}

	if( FALSE == bArrangement)
	{
		SendServerResponseMsg(0, SRVAL_HOUSE_FAILARRANGEITEM,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
	
}

