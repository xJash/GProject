//---------------------------------
// 2003/8/18 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"
#include "..\Server\Server.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\Common\Map\Map.h"
#include "../../Common/Skill/Skill-Manager.h"
#include "../Statistics/Statistics.h"
#include "Char\CharManager\CharManager.h"

#include "../../../Server/AuthServer/AuthMsg.h"

//-----------------------------------
// DBManager
//----------------------------------
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-House.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Person.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Item.h"


//-----------------------------------
// CommonLogic 
//----------------------------------
#include "MsgRval-Define.h"
#include "MsgType-House.h"
#include "MsgType-Person.h"

// ������ ȸ���Ѵ� 
void cltServer::DoMsg_DBMSG_RESPONSE_RECALLHOUSE(sPacketHeader* pPacket)
{
	sDBResponse_RecallHouse* pclMsg = (sDBResponse_RecallHouse*)pPacket;

	if(pclMsg->siResult <= 0)
	{
		if(pclMsg->siResult == -9) // ���� ��������
		{

		}
		else if(pclMsg->siResult == -10) // �������� �����ִ�.
		{

		}
		else if(pclMsg->siResult == -11) // ���� �����ִ�.
		{

		}
		return ;
	}

	SI32 personid		= pclMsg->siPersonID;
	SI32 villageunique	= pclMsg->siVillageUnique;
	SI32 houseindex		= pclMsg->siHouseIndex;

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // â�� ȸ��. 
		// param1		 == ����� �Ǵ� ���� ������ �ε���.
		// pszCharParam1 == �̸�.
		cltServer* pclserver = (cltServer*)pclClient;
		pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RECALL,
										pclMsg->siRecallReason, NULL, NULL, personid, 0, 0, NULL, 0, 0, 0, villageunique, 0, 0, 
										houseindex, 0, 0, 0, 0, pclMsg->szOwnerName, NULL);
	}

	//-------------------------------------------
	// �������� ��ǰ�� �������� ������. 
	//-------------------------------------------
	/*	cltHouseUnit* punit =pclHouseManager->pclStruct[villageunique]->GetHouseUnit(houseindex);
	if(punit)
	{
	bool bfirstswitch = false;
	for(SI32 i = 0;i < MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER;i++)
	{
	cltItem* pclitem = &(punit->clStorageInfo.clItem[i]);

	if(pclitem->siUnique)
	{
	if(bfirstswitch == false)
	{
	bfirstswitch = true;
	TCHAR buffer[256];
	TCHAR* pText = GetTxtFromMgr(3792);
	TCHAR index[128]= TEXT(" ") ;

	sprintf(index,TEXT("%d"),houseindex +1);
	Nsprintf(buffer,pText,TEXT("village"), pclVillageManager->GetName(villageunique)   ,TEXT("index"),  index  ,NULL);

	//sprintf(buffer,pText,pclVillageManager->GetName(villageunique), houseindex +1);

	SendPostOfficeItemToPerson((TCHAR*)punit->clPerson.GetName(), pclitem, buffer);
	}
	else
	{
	SendPostOfficeItemToPerson((TCHAR*)punit->clPerson.GetName(), pclitem, NULL);
	}

	}
	}
	}
	*/

	// ������ ȸ���Ѵ�. 
	pclHouseManager->RecallHouse(villageunique, houseindex);


	if(pclMsg->siRecallReason ==  HOUSERECALL_REASON_CANCELLATION)
	{
		// �۽����� ���� �޽����� �����ش�.
		SI32 id = pclCM->GetIDFromPersonID(personid);
		
		if(pclCM->IsValidID(id)== false)return ;

		GMONEY housemoney	= pclMsg->siHouseMoney;
		GMONEY remainmoney = pclMsg->siRemainMoney;
		GMONEY penaltymoney = pclMsg->siPenaltyMoney;

		// ������ �ܵ� ����~!
		pclCM->CR[id]->pclCI->clIP.SetMoney(remainmoney);
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

		// ������ �ܵ� ����~!
		cltStrInfo *pStrInfo = GetStrInfo( villageunique, RANKTYPE_HOUSE );
		if( pStrInfo ) {

			pStrInfo->clCommonInfo.clMoney.Set( housemoney );
		}

		SendServerResponseMsg(RANKTYPE_HOUSE,  SRVAL_HOUSE_SUCCESSCANCELLATION,0,0,pclCM->CR[id]->GetCharUnique());

		// ����������� ������ ������.

		cltRank* pclrank = pclRankManager->GetRank(RANKTYPE_HOUSE,villageunique);
		SI32 housePersonid = pclrank->GetPersonID();	// ���� ����� Persionid

		cltLetterMsg_RecallHouse clletter(pclMsg->siRecallReason, pclMsg->siVillageUnique, pclMsg->siHouseIndex,pclMsg->szOwnerName);
		SI32 letterid = SendLetterMsg(housePersonid, (cltLetterHeader*)&clletter);
		if(pclCM->IsValidID(letterid))	// letterid == 0 �̶�� ������ �ƵǾ��־ DB�� ���Ŵ�.
		{
			pclCM->CR[letterid]->pclCI->clRealEstate.Delete(REALESTATE_TYPE_HOUSE, pclMsg->siVillageUnique, pclMsg->siHouseIndex);
			pclCM->CR[letterid]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);
		}

	}
	else if( pclMsg->siRecallReason == HOUSERECALL_REASON_FEEDELAY || pclMsg->siRecallReason == HOUSERECALL_REASON_CONTRACTEND )
	{	
		// �ش� �������� ������ ������. 
		cltLetterMsg_RecallHouse clletter(pclMsg->siRecallReason, pclMsg->siVillageUnique, pclMsg->siHouseIndex);
		SI32 letterid = SendLetterMsg(personid, (cltLetterHeader*)&clletter);
		if(pclCM->IsValidID(letterid))	// letterid == 0 �̶�� ������ �ƵǾ��־ DB�� ���Ŵ�.
		{
			pclCM->CR[letterid]->pclCI->clRealEstate.Delete(REALESTATE_TYPE_HOUSE, pclMsg->siVillageUnique, pclMsg->siHouseIndex);
			pclCM->CR[letterid]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);
		}

	}
	else
	{
		return; 
	}
	// ȸ���� ���� ������ ��賽��. 
	pclStatisticsManager->clDailyStatistics.siRecallHouseNumber++;

}

// �Ӵ�Ḧ �����Ѵ�. 
void cltServer::DoMsg_DBMSG_RESPONSE_PAYRENTFEE(sPacketHeader* pPacket)
{
	sDBResponse_PayRentFee* pclMsg = (sDBResponse_PayRentFee*)pPacket;

	SI32 id = 0;
	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		{
		}
		break;

	case 1:
		{

			// �����ڰ� ������ Ȯ���Ѵ�.
			if(pclMsg->usCharID)
			{
				id = pclMsg->usCharID;
			}
			else
			{
				id = pclCM->GetIDFromPersonID(pclMsg->siPersonID);
			}

			// ��ü Ƚ���� 3ȸ�� �ʰ��ϴ� ��� ������ �ʱ�ȭ�Ѵ�. 
			if(pclMsg->siDelayNum > 3)
			{
				// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
				sDBRequest_RecallHouse clMsg(pclMsg->siPersonID, HOUSERECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siHouseIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
			else
			{
				cltLetterMsg_PayRentFee clletter(pclMsg->siVillageUnique, pclMsg->siHouseIndex, pclMsg->siRentFee, pclMsg->siDelayNum, pclMsg->siDelayMoney);
				// ������ DB�� Ŭ���̾�Ʈ���� ������. 
				SendLetterMsg(pclMsg->siPersonID, (cltLetterHeader*)&clletter);
			}

			// ������ ���� �ڱ��� ������Ʈ �Ѵ�. 
			cltMoney clmoney;
			clmoney.Set(pclMsg->siHouseMoney);
			pclHouseManager->SetMoney(pclMsg->siVillageUnique, &clmoney);

			if(pclCM->IsValidID(id))
			{
				// �������� �����ܰ� ������Ʈ �Ѵ�. 
				pclCM->CR[id]->pclCI->clBank.SetMoney(pclMsg->siBankMoney);
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 10] // ������ �Ӵ�Ḧ ����.
					// param1 == ����� �Ǵ� ���� ������ �ε���,  
					// param3 == ��ü Ƚ��. 
					// param4 == ��ü��.
					cltServer* pclserver = (cltServer*)pclClient;
					pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RENTFEEPAY,
													0, NULL, NULL, pclMsg->siPersonID, pclMsg->siRentFee, pclMsg->siBankMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
													pclMsg->siHouseIndex, 0, pclMsg->siDelayNum, pclMsg->siDelayMoney, 0, NULL, NULL);
				}
			}

			//returnval	= SRVAL_HOUSE_SUCCESSSETCONTRACT;
		}
		break;

	case -1:
		{
			// ��ü Ƚ���� 3ȸ�� �ʰ��ϴ� ��� ������ �ʱ�ȭ�Ѵ�. 
			if( pclMsg->siDelayNum > 3)
			{
				// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
				sDBRequest_RecallHouse clMsg(pclMsg->siPersonID, HOUSERECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siHouseIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
		break;
	}


}

// ���� ��� ������ ������ �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEHOUSECONTRACT(sPacketHeader* pPacket)
{

	sDBResponse_ChangeHouseContract* pclMsg = (sDBResponse_ChangeHouseContract*)pPacket;

	SI32 returnval = 0;
	SI32 id	= pclMsg->usCharID;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case 1:
		{
			// �ش��ϴ� ������ ��� ������ �����Ѵ�. 
			pclHouseManager->SetRentContract(pclMsg->siVillageUnique, &pclMsg->clContract);

			if(pclCM->IsValidID(id)== false)return ;

			// Ŭ���̾�Ʈ�� ����� ��������� ������. 
			if(pclCM->CR[id]->IsValidConnection())	
			{
				cltStrInfo* pclinfo = pclHouseManager->GetStrInfo(pclMsg->siVillageUnique);
				if(pclinfo == NULL)return ;

				cltMsg clMsg(GAMEMSG_RESPONSE_STRINFO,  pclinfo->GetTotalSize(), (BYTE*)pclinfo);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

			}

			returnval	= SRVAL_HOUSE_SUCCESSSETCONTRACT;
		}
		break;
	}
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// â�� �̸� ����
void cltServer::DoMsg_DBMSG_RESPONSE_CHANGEHOUSEUNITNAME(sPacketHeader* pPacket)
{
	sDBResponse_ChangeHouseUnitName* pclMsg = (sDBResponse_ChangeHouseUnitName*)pPacket;

	SI32 siId	= pclMsg->m_usCharID;

	if( pclMsg->m_siVillageUnique < 0 || pclMsg->m_siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if(pclMsg->m_siResult == 0)
	{
		return ;
	}

	SI32 siVillageunique = pclMsg->m_siVillageUnique;
	SI32 siHouseIndex = pclMsg->m_siIndex;
	if(pclHouseManager->pclStruct[siVillageunique] == NULL)return ;

	cltHouseUnit *pclHouseUnit = pclHouseManager->pclStruct[siVillageunique]->GetHouseUnit(siHouseIndex);
	if( NULL == pclHouseUnit)
		return;

	_tcscpy( pclHouseUnit->m_szName, pclMsg->m_szName);

	cltCharServer* pclChar = pclCM->GetCharServer(siId);
	if( NULL == pclChar)
		return;
	
	// â���� ������ Ŭ���̾�Ʈ���� �����ش�. 
	cltGameMsgResponse_ChangeHouseUnitName clinfo( siVillageunique, siHouseIndex, pclMsg->m_szName);
	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITNAMECHANGE, sizeof(clinfo), (BYTE*)&clinfo);
	pclChar->SendNetMsg((sPacketHeader*)&clMsg);	
}


// ���� ���� ������ ���� ���� ��û�� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYHOUSEUNIT(sPacketHeader* pPacket)
{
	sDBResponse_ManyHouseUnit* pclMsg = (sDBResponse_ManyHouseUnit*)pPacket;
	
	SI32 id	= pclMsg->usCharID;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 villageunique = pclMsg->siVillageUnique;
	if(pclHouseManager->pclStruct[villageunique] == NULL)return ;
	
	SI32 i;

	for(i = 0;i < MANYHOUSEUNIT_NUMBER;i++)
	{
		pclHouseManager->pclStruct[villageunique]->SetHouseUnit(i + pclMsg->siStartIndex, &pclMsg->clHouseUnit[i]);
	}
	//�ʹ� ���� ������ ����
	//pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_ManyHouseUnit"));
}

// ���� ����� ��� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETHOUSEAPPLYERLIST(sPacketHeader* pPacket)
{
	sDBResponse_GetHouseApplyerList* pclMsg = (sDBResponse_GetHouseApplyerList*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_ITEM_PER_PERSON )		return;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 i;
	for(i = 0;i < MAX_APPLY_PER_HOUSE;i++)
	{
		if(pclHouseManager->pclStruct[pclMsg->siVillageUnique])
		{
			pclHouseManager->pclStruct[pclMsg->siVillageUnique]->SetHouseApplyer(i, &pclMsg->clApply[i].clPerson, &pclMsg->clApply[i].clContract);
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetHouseApplyerList"));

}
// ���� ����ڸ� ��� �����Ѵ�. 
void cltServer::DoMsg_DBMSG_RESPONSE_DELHOUSEAPPLYER(sPacketHeader* pPacket)
{
	sDBResponse_DelHouseApplyer* pclMsg = (sDBResponse_DelHouseApplyer*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siDelSlotNum < 0 || pclMsg->siDelSlotNum > MAX_APPLY_PER_HOUSE )			return;

	SI32 returnval = 0;
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)	return ;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case -1:
		returnval	= SRVAL_HOUSE_FAILDELHOUSEAPPLYER_NOTCHIEF;	// ���� ����� �ƴ϶� ����.(�����Ѵٴµ� ����!!) 
		break;
	case 1:
		{
			cltHouse	*pclHouse = (cltHouse*) pclHouseManager->pclStruct[pclMsg->siVillageUnique];

			// PCK : ���� ����� ����� ������ ����� PersonID
			SI32	siDelPersonID = 0;

			if( pclMsg->siDelSlotNum >= 0 && pclMsg->siDelSlotNum < MAX_APPLY_PER_HOUSE )
			{
				siDelPersonID = pclHouse->clApply[pclMsg->siDelSlotNum].clPerson.GetPersonID();
			}

			// PCK : ���� ������� ������ ����� �����Ѵ�.
			if(siDelPersonID > 0)	pclHouse->DeleteApplyer(siDelPersonID);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 29] // ���� ������� ����� ����.
				cltServer* pclserver = (cltServer*)pclClient;
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_DELETEHOUSERENTAPPLYER,
					0, (cltCharServer*)pclCM->CR[id], NULL, siDelPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					0, 0, 0, 0, 0, NULL, NULL);
			}

			// Ŭ���̾�Ʈ�� ���� ����� ����� ��� �����϶�� �޽����� ������. 
			if(pclCM->IsValidID(id) == TRUE)
			{
				cltMsg clMsg(GAMEMSG_RESPONSE_DELHOUSEAPPLYER, sizeof(SI32), (BYTE*)&pclMsg->siDelSlotNum);
				pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			}

			// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
			SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

			returnval	= SRVAL_HOUSE_SUCCESSDELHOUSEAPPLYER;
		}
		break;
	}
}

// ���� ��û ��ҿ� ���� ����.
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSERENTAPPLYCANCEL(sPacketHeader* pPacket)
{
	sDBResponse_HouseRentApplyCancel* pclMsg = (sDBResponse_HouseRentApplyCancel*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_ITEM_PER_PERSON )		return;

	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case 1:
		{

			// ��û�ڸ� ����Ѵ�.
			if(pclMsg->siVillageUnique)
			{
				pclHouseManager->pclStruct[pclMsg->siVillageUnique]->SetHouseApplyer(pclMsg->siIndex, &pclMsg->clApply.clPerson, &pclMsg->clApply.clContract);
			}

			returnval	= SRVAL_HOUSE_SUCCESSAPPLYCANCEL;
		}
		break;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 18] // ���� ��û��� �α׾���. 
			// param1	 == ���� ������� ������ ��� ��ġ.
			// pszParam1 == �Ӵ���� �ð�.
			TCHAR pszCharParam1[50] = {'\0', };
			StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d "),	
																		pclMsg->clApply.clContract.clDate.uiYear,
																		pclMsg->clApply.clContract.clDate.uiMonth,
																		pclMsg->clApply.clContract.clDate.uiDay,
																		pclMsg->clApply.clContract.clDate.uiHour,
																		pclMsg->clApply.clContract.clDate.uiMinute );


			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RENTAPPLYCANCEL, 
								 0, (cltCharServer*)(pclCM->CR[pclMsg->usCharID]), NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								 pclMsg->siIndex, 0, 0, 0, 0, 
								 pszCharParam1, NULL);
		}
	}

}

//�����!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!â��!!!!!!!!!!!!!!!!!
// ���� ��û�� ������ �Ϳ� ���� ����.
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSERENTAPPLY(sPacketHeader* pPacket)
{

	sDBResponse_HouseRentApply* pclMsg = (sDBResponse_HouseRentApply*)pPacket;
	SI32 returnval = 0;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_ITEM_PER_PERSON )		return;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case -1://������ ������û�� �Ҷ� ���� ���� â�� 3�� ������ ������ �ִ�.[2007.07.19 ]
		returnval	= SRVAL_HOUSE_FAILNOMOREREALESTATE;		// �ε��� ������ �ʰ��ؼ� ���� �� ����. 
		break;
	case 1:
		{
			// ��û�ڸ� ����Ѵ�.
			if(pclMsg->siVillageUnique)
			{
				pclHouseManager->pclStruct[pclMsg->siVillageUnique]->SetHouseApplyer(pclMsg->siIndex, &pclMsg->clApply, &pclMsg->clContract);
			}

			returnval	= SRVAL_HOUSE_SUCCESSAPPLY;

			
			SI32 id	= pclMsg->usCharID;
			if(pclCM->IsValidID(id) == FALSE)
			{
				return ;
			}
			else
			{
				if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
				{
					// [�α��߰� : Ȳ���� 2007. 10. 18] // â�� ���� ��û �α׾���. (������������.)
					// param1		 == �Ӵ� ������.
					// param2		 == �Ӵ� �Ⱓ.
					// pszCharParam1 == �Ӵ� ��û �ð�.
					TCHAR pszCharParam1[50] = {'\0', };
					StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d"),	
																				pclMsg->clContract.clDate.uiYear,
																				pclMsg->clContract.clDate.uiMonth,
																				pclMsg->clContract.clDate.uiDay,
																				pclMsg->clContract.clDate.uiHour,
																				pclMsg->clContract.clDate.uiMinute );

					
					SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RENTAPPLY, 
										0, (cltCharServer*)(pclCM->CR[pclMsg->usCharID]), NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
										pclMsg->clContract.siRentFee, pclMsg->clContract.siRentPeriod, 0, 0, 0, 
										pszCharParam1, NULL);
				}
			}
		}
		break;
	}

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}


// �Ӵ� �㰡�� ������ �Ϳ� ���� ����.
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSERENT(sPacketHeader* pPacket)
{
	sDBResponse_HouseRent* pclMsg = (sDBResponse_HouseRent*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_ITEM_PER_PERSON )		return;

	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case -1:
		returnval	= SRVAL_HOUSE_FAILNOMOREREALESTATE;		// �ε��� ������ �ʰ��ؼ� ���� �� ����. 
		break;
	case 1:
		{
			if(pclMsg->siVillageUnique)
			{
				// ���� ���������� ����Ѵ�. 
				pclHouseManager->SetRent(pclMsg->siVillageUnique, pclMsg->siIndex, &pclMsg->clPerson, &pclMsg->clRentContract, pclMsg->m_szName);

				// ����� ��ܿ��� Person�� �����Ѵ�. 
				pclHouseManager->pclStruct[pclMsg->siVillageUnique]->SetHouseApplyer(pclMsg->siApplyerIndex, &pclMsg->clApplyer.clPerson, &pclMsg->clApplyer.clContract);


				// ������ ������. 
				cltLetterMsg_RentHouse clletter(pclMsg->siVillageUnique, pclMsg->siIndex);
				SI32 id = SendLetterMsg(pclMsg->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);
				if(id)
				{
					// Person�� �ľ��� �ε��� ������ ������Ʈ �Ѵ�. 
					pclCM->CR[id]->pclCI->clRealEstate.Add(REALESTATE_TYPE_HOUSE, pclMsg->siVillageUnique, pclMsg->siIndex, &pclMsg->clRentContract);
					pclCM->CR[id]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);

				}


			}

			returnval	= SRVAL_HOUSE_SUCCESSHOUSERENT; // �����Ӵ뿡 �����ߴ�.

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 18] // �����Ӵ�.
				// param1 == �Ӵ��, param2 == �Ӵ�Ⱓ, param3 == ��û�� ������ ��ġ. pszParam1 == �Ӵ�ð�.
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d : %d"),	
																			pclMsg->clRentContract.clDate.uiYear,
																			pclMsg->clRentContract.clDate.uiMonth,
																			pclMsg->clRentContract.clDate.uiDay,
																			pclMsg->clRentContract.clDate.uiHour,
																			pclMsg->clRentContract.clDate.uiMinute  );


				cltServer* pclserver = (cltServer*)pclClient;
				cltCharServer* pclchar = NULL;
				if( pclCM->IsValidID(pclMsg->usCharID) )		pclchar = (cltCharServer*)pclCM->CR[pclMsg->usCharID];
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_RENT, 
												0, pclchar, NULL, pclMsg->clPerson.siPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0,
												pclMsg->clRentContract.siRentFee, pclMsg->clRentContract.siRentPeriod, pclMsg->siIndex, 0, 0, 
												pszCharParam1, NULL);
			}
		}
		break;
	}


	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_HOUSE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

// �������� �κ����� â��� �ű�°Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MOVEITEMINVTOSTG(sPacketHeader* pPacket)
{
	sDBResponse_MoveItemInvToStg* pclMsg = (sDBResponse_MoveItemInvToStg*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->siInvPos < 0 || pclMsg->siInvPos >= MAX_ITEM_PER_PERSON )		return;

	// â�� ������Ʈ �Ѵ�. 
	pclHouseManager->SetItemStg(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, &pclMsg->clStgItem);
	
	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		// Person�� �κ��丮�� ������Ʈ �Ѵ�. 
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siInvPos].Set(&pclMsg->clInvItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		{
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siInvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clInvItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}


		// â���� ������ Ŭ���̾�Ʈ���� �����ش�. 
		{
			cltHouseUnitStgItemInfo clstginfo(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, STGITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clStgItem );
			cltMsg clMsg(GAMEMSG_RESPONSE_STGITEMINFO, sizeof(clstginfo), (BYTE*)&clstginfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}
		
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // â�� ���� �α׾���.
			// param1 == â�� ����, 
			// param2 == �κ���ġ.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_MOVEITEMINVTOSTG, 
								 0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clMoveItem, pclMsg->clInvItem.siItemNum, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								 								 pclMsg->siHouseUnitSlot, pclMsg->siInvPos, pclMsg->clStgItem.siItemNum, 0, 0, NULL, NULL);
		}	
	}
}

// �������� â���� �κ����� �ű�°Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_MOVEITEMSTGTOINV(sPacketHeader* pPacket)
{
	sDBResponse_MoveItemStgToInv* pclMsg = (sDBResponse_MoveItemStgToInv*)pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	if( pclMsg->siInvPos < 0 || pclMsg->siInvPos >= MAX_ITEM_PER_PERSON )		return;

	// â�� ������Ʈ �Ѵ�. 
	pclHouseManager->SetItemStg(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, &pclMsg->clStgItem);

	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		// Person�� �κ��丮�� ������Ʈ �Ѵ�. 
		pclCM->CR[id]->pclCI->clCharItem.clItem[pclMsg->siInvPos].Set(&pclMsg->clInvItem);

		// Ŭ���̾�Ʈ�� ������Ʈ �� ������ ������. 
		{
			cltGameMsgResponse_PersonItemInfo clinfo(pclMsg->siInvPos, PERSONITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clInvItem, 0);
			cltMsg clMsg(GAMEMSG_RESPONSE_PERSONITEMINFO, sizeof(clinfo), (BYTE*)&clinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}


		// â���� ������ Ŭ���̾�Ʈ���� �����ش�. 
		{
			cltHouseUnitStgItemInfo clstginfo(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, STGITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clStgItem);
			cltMsg clMsg(GAMEMSG_RESPONSE_STGITEMINFO, sizeof(clstginfo), (BYTE*)&clstginfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 11] // ������ �������� ����ǰ���� �̵�. 
			// param1 == â����, param2 == �κ��丮 ������ġ

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_MOVEITEMSTGTOINV, 
								0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, &pclMsg->clMoveItem, pclMsg->clInvItem.siItemNum, 0, 0, pclMsg->siVillageUnique, 0, 0, 
																pclMsg->siHouseUnitSlot, pclMsg->siInvPos, pclMsg->clStgItem.siItemNum, 0, 0, NULL, NULL);
		}

		//------------------------------------------
		// ���Ⱓ�� Ȯ���Ѵ�.
		//------------------------------------------
		/*if(CheckItemUseDayOver(&pclMsg->clInvItem))
		{	
		// DB ���� ��û
		sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),pclMsg->siInvPos
		,&pclMsg->clInvItem,USEITEM_REASON_DATEOVER);
		pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

		// �������� �޽���

		}*/

		SI32 itemunique = pclMsg->clInvItem.siUnique ;
		if ( itemunique > 0 )
		{
			if ( pclMsg->clInvItem.IsHaveUseDay() )  //[����] ���� ���Ⱓ ���� �˸�
			{
				SI32 useableDay = 0;
				BOOL rVal = GetItemUseAbleDay(&pclMsg->clInvItem,&useableDay);
				if(rVal == FALSE) return;

				if( useableDay < 0) //���Ⱓ�� ������ �����ش� �׸��� Ŭ���̾�Ʈ�� �˸�.
				{
					// ���ǰ�� �������� �ʴ´�. - by LEEKH
					if( pclMsg->clInvItem.clItemCommon.clCommonInfo.uiRareInfo != RARELEVEL_5 )
					{
						sDBRequest_UseItem useitem(id,pclCM->CR[id]->pclCI->GetPersonID(),pclMsg->siInvPos,&pclMsg->clInvItem,USEITEM_REASON_DATEOVER);
						pclGameDBProcess->SendMsg(DBSELECT_BASE,(sPacketHeader *)&useitem);

						cltGameMsgResponse_NoticeItemUseDayOver sendMsg(pclMsg->clInvItem.siUnique, useableDay);
						cltMsg clMsg( GAMEMSG_RESPONSE_NOTICE_ITEMUSEABLEDAY, sizeof( sendMsg ), (BYTE*)&sendMsg );
						pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg );		
					}

					return;
				}
			}
		}
	}
}


// â���� Ư�� ��ġ�� �ִ� ������ ������ ��û�� �Ϳ� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_GETHOUSESTGPOS(sPacketHeader* pPacket)
{
	sDBResponse_GetHouseStgPos* pclMsg = (sDBResponse_GetHouseStgPos*) pPacket;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	// â�� ������Ʈ �Ѵ�. 
	pclHouseManager->SetItemStg(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, &pclMsg->clItem);


	SI32 id = pclMsg->usCharID;
	if(pclCM->IsValidID(id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
	{
		// â���� ������ Ŭ���̾�Ʈ���� �����ش�. 
		cltHouseUnitStgItemInfo clstginfo(pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStgPos, STGITEMINFO_OPTION_NONE, 0, 0, &pclMsg->clItem);
		cltMsg clMsg(GAMEMSG_RESPONSE_STGITEMINFO, sizeof(clstginfo), (BYTE*)&clstginfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	}
}

void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITSTABLECREATE(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitStableCreate* pclMsg = (sDBResponse_HouseUnitStableCreate*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if( pclMsg->siStableIndex < 0 || pclMsg->siStableIndex >= MAX_HOUSEUNIT_HORSENUMBER )	return;

	//------------------------------------------------------------------------------------------
	// ������ �������� ����.
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}
	pclStg->bCreatedHouseUnitStable[ pclMsg->siStableIndex ] = true;
	//------------------------------------------------------------------------------------------

	// ���� ȭ�� ������Ʈ( � ���ƴ���. )
	// pclItemManager->AddUseNum( ITEMUNIQUE(24025), HOUSEUNIT_CREATESTABLE_USEITEMNUM );

	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		/*
		// ���� ���� ������ ������Ʈ
		pclCM->CR[id]->pclCI->clIP.SetMoney( pclMsg->siPersonLeftMoney );

		// ���� �����ڱ� ������Ʈ 
		cltStrInfo *pStrInfo = GetStrInfo( pclMsg->siVillageUnique, RANKTYPE_HOUSE );
		if( pStrInfo ) 
		{
		pStrInfo->clCommonInfo.clMoney.Set( &pclMsg->clLeftHouseUnitMoney );
		}
		else
		{
		// ������ ���� ������ ���߿� �����... �̷� ����� ��찡 ����� ����...
		pclMsg->clLeftHouseUnitMoney.Set( (__int64)(0) );
		pclLog->FilePrint( TEXT("HouseUnitError.txt"), TEXT("pStrInfo == NULL, VillageUnique = %d"), pclMsg->siVillageUnique );
		}
		*/

		//pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemPos ].Set( &pclMsg->clLeftItem );
		GMONEY siCurrentMoney = pclClient->pclCM->CR[id]->pclCI->clIP.GetMoney();
		pclCM->CR[id]->pclCI->clIP.SetMoney( siCurrentMoney - pclMsg->siHouseUnitStableCreateFee );

		cltGameMsgResponse_HouseUnitStableCreate clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siStableIndex, pclMsg->siHouseUnitStableCreateFee ); 
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITSTABLECREATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // �������� ����.
			// param1 == â�� ���� ��ȣ, 
			// param2 == ������ ��ȣ.  
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSEHORSE, LOGCOMMAND_INDEX_HOUSEHORSE_CREATE_HORSE_STABLE,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, pclMsg->siHouseUnitStableCreateFee, pclCM->CR[id]->pclCI->clIP.GetMoney(), NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siHouseUnitSlot, pclMsg->siStableIndex, 0, 0, 0, NULL, NULL);
		}

	}


	return;
}

// ������ ���� �ִ´�.
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEIN(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitHorseIn* pclMsg = (sDBResponse_HouseUnitHorseIn*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if( pclMsg->siHouseUnitStgHorseIndex < 0 || pclMsg->siHouseUnitStgHorseIndex >= MAX_HOUSEUNIT_HORSENUMBER )	return;

	SI32 id = pclMsg->siCharID;

	//------------------------------------------------------------------------------------------
	// ������ ���� ����. ( ���� �ִ� ��ġ ���� ���� �־��� )
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}
	pclStg->clHorse[ pclMsg->siHouseUnitStgHorseIndex ].Set( &pclMsg->clHouseUnitStgHorse );
	//------------------------------------------------------------------------------------------

	// �������� ���� �־��� ���� �˷���
	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// ����� �����ϹǷ�, ������ ���� �ٲܼ��� �����Ƿ�, ���� ���� ������Ʈ ������		
		pclCM->CR[id]->UnrideHorse();
		pclCM->CR[id]->pclCI->clHorseInfo.SetHorse(pclMsg->siPersonHorseIndex, &pclMsg->clPersonHorse);

		cltGameMsgResponse_HouseUnitHorseIn clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siPersonHorseIndex, &pclMsg->clPersonHorse, pclMsg->siHouseUnitStgHorseIndex, &pclMsg->clHouseUnitStgHorse );
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITHORSEIN, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// ���� ����鿡�� �� ���� ������Ʈ ������
		cltCharServer *pclChar = (cltCharServer*)pclCM->CR[id];		
		pclChar->SendNeighbourMyHorseStatus( pclChar->pclCI->clHorseInfo.siCurrentShowHorse);

		// �� ���� ��ü�� ������Ʈ ��Ų��. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_HORSE, true, 0);



		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 29] // ���������� �� ���� ���.
			// param1 == ������ ����, 
			// param2 == â���� ���� �߿��� ����� �ϴ� Index.  
			// param3 == ���� ������ �ٴϴ� ���� �迭 Index.
			// pszCharParam1 == Unique, Name, Sex, PregnentPeriod, Life, TicketNum
			// pszCharParam2 == Unique, Name, Sex, PregnentPeriod, Life, TicketNum
			TCHAR str[2][50];
			ZeroMemory(str, sizeof(str));
			StringCchPrintf(str[0], sizeof(str[0]), TEXT("OUT:  %d, %s, %d, %d, %d, %d"),	
															pclMsg->clPersonHorse.siHorseUnique, 
															pclMsg->clPersonHorse.szName, 
															pclMsg->clPersonHorse.siSex, 
															pclMsg->clPersonHorse.siPregnentPeriod, 
															pclMsg->clPersonHorse.siLife, 
															pclMsg->clPersonHorse.siStatusTicketNum );

			StringCchPrintf(str[1], sizeof(str[1]), TEXT("IN:  %d, %s, %d, %d, %d, %d"),	
															pclMsg->clHouseUnitStgHorse.siHorseUnique, 
															pclMsg->clHouseUnitStgHorse.szName, 
															pclMsg->clHouseUnitStgHorse.siSex, 
															pclMsg->clHouseUnitStgHorse.siPregnentPeriod, 
															pclMsg->clHouseUnitStgHorse.siLife, 
															pclMsg->clHouseUnitStgHorse.siStatusTicketNum);

			
			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSEHORSE, LOGCOMMAND_INDEX_HOUSEHORSE_HORSEINHOUSE,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitStgHorseIndex, pclMsg->siPersonHorseIndex, 0, 0, str[0], str[1]);
		}
	}

	return;
}

// �������� ���� ����.
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEOUT(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitHorseOut* pclMsg = (sDBResponse_HouseUnitHorseOut*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if( pclMsg->siHouseUnitStgHorseIndex < 0 || pclMsg->siHouseUnitStgHorseIndex >= MAX_HOUSEUNIT_HORSENUMBER )	return;

	//------------------------------------------------------------------------------------------
	// �������� ���� ���� ( ���� �ִ� ��ġ ���� �ʱ�ȭ ��Ŵ )
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}	
	pclStg->clHorse[ pclMsg->siHouseUnitStgHorseIndex ].Set( &pclMsg->clHouseUnitHorse );
	//------------------------------------------------------------------------------------------


	SI32 id = pclMsg->siCharID;

	// �������� ���� ���� ���� �˷���
	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// ����� �����ϹǷ�, ������� �� �߰�
		pclCM->CR[id]->UnrideHorse();		
		//pclCM->CR[id]->pclCI->clHorseInfo.clHorse.Set( &pclMsg->clPersonHorse );
		pclCM->CR[id]->pclCI->clHorseInfo.SetHorse( pclMsg->siPersonHorseIndex, &pclMsg->clPersonHorse );


		// �������� ������Ʈ ������ ( ���� �������� ���ֹ�������, �������� �ٲٴ°͵� �����ϰ� �Ǿ�������. )
		cltGameMsgResponse_HouseUnitHorseOut clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitStgHorseIndex, &pclMsg->clHouseUnitHorse, pclMsg->siPersonHorseIndex, &pclMsg->clPersonHorse );
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITHORSEOUT, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ���������� �� ���� ���.
			// param1 == ������ ����, 
			// param2 == â���� ���� �߿��� ����� �ϴ� Index.  
			// param3 == ���� ������ �ٴϴ� ���� �迭 Index.
			// pszParam1 == Person ������, 
			// pszParam2 == HouseUnit ������
			TCHAR str[2][50];
			ZeroMemory(str, sizeof(str));

			StringCchPrintf(str[0], sizeof(str[0]), TEXT("OUT:  %d, %s, %d, %d, %d, %d"),	
															pclMsg->clPersonHorse.siHorseUnique, 
															pclMsg->clPersonHorse.szName, 
															pclMsg->clPersonHorse.siSex, 
															pclMsg->clPersonHorse.siPregnentPeriod, 
															pclMsg->clPersonHorse.siLife, 
															pclMsg->clPersonHorse.siStatusTicketNum );

			StringCchPrintf(str[1], sizeof(str[1]), TEXT("IN:  %d, %s, %d, %d, %d, %d"),	
															pclMsg->clHouseUnitHorse.siHorseUnique, 
															pclMsg->clHouseUnitHorse.szName, 
															pclMsg->clHouseUnitHorse.siSex, 
															pclMsg->clHouseUnitHorse.siPregnentPeriod, 
															pclMsg->clHouseUnitHorse.siLife, 
															pclMsg->clHouseUnitHorse.siStatusTicketNum);
		

			cltServer* pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSEHORSE, LOGCOMMAND_INDEX_HOUSEHORSE_HORSEOUTHOUSE,
											0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitStgHorseIndex, pclMsg->siPersonHorseIndex, 0, 0, str[0], str[1]);
		}
		
		// �� ���� ��ü�� ������Ʈ ��Ų��. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_HORSE, true, 0);

		// ���� ����鿡�� �� ���� ������Ʈ ������
		cltCharServer *pclChar = (cltCharServer*)pclCM->CR[id];
		pclChar->SendNeighbourMyHorseStatus(pclChar->pclCI->clHorseInfo.siCurrentShowHorse);

	}

	return;
}


void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEINFOSET(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitHorseInfoSet* pclMsg = (sDBResponse_HouseUnitHorseInfoSet*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	if( pclMsg->siHouseUnitHorseIndex < 0 || pclMsg->siHouseUnitHorseIndex >= MAX_HOUSEUNIT_HORSENUMBER )	return;

	//------------------------------------------------------------------------------------------
	// ������ ��� �ִ¸��� ������ ������Ʈ
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}
	pclStg->clHorse[ pclMsg->siHouseUnitHorseIndex ].Set( &pclMsg->clHouseUnitHorseInfo );
	//------------------------------------------------------------------------------------------

	SI32 id = pclMsg->siCharID;
	cltCharServer *pclChar = pclCM->GetCharServer(id);
	// �������� �� ������ ����Ǿ����� �˷���
	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		// �������� �뺸
		cltGameMsgResponse_HouseUnitHorseInfoSet clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitHorseIndex, &pclMsg->clHouseUnitHorseInfo );
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITHORSEINFOSET, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

		// �� ���� ��ü�� ������Ʈ ��Ų��. 
		pclCM->CR[id]->SetUpdateSwitch(UPDATE_HORSE, true, 0);

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 15] // ������ ������ ���� ���°� ����� ������ ���
			// param1	 == ������ ����, 
			// param2	 == ���� ������ �ٴϴ� ���� �迭 Index. 
			// pszParam1 == Unique, Name, Sex, PregnentPeriod, Life, TicketNum

			TCHAR str[50] = {'\0', };
			StringCchPrintf(str, sizeof(str), TEXT("%d, %s, %d, %d, %d, %d"),	
													pclMsg->clHouseUnitHorseInfo.siHorseUnique, 
													pclMsg->clHouseUnitHorseInfo.szName, 
													pclMsg->clHouseUnitHorseInfo.siSex, 
													pclMsg->clHouseUnitHorseInfo.siPregnentPeriod, 
													pclMsg->clHouseUnitHorseInfo.siLife, 
													pclMsg->clHouseUnitHorseInfo.siStatusTicketNum  );

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSEHORSE, LOGCOMMAND_INDEX_HOUSEHORSE_SETHOUSEHORSEINFO,
								 0, pclChar, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
								 pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitHorseIndex, 0, 0, 0, str, NULL);
		}

	}

	return;
}

void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITHORSEEATFOOD(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitHorseEatFood* pclMsg = (sDBResponse_HouseUnitHorseEatFood*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	//------------------------------------------------------------------------------------------
	// ������ ������ ������ ������ ������Ʈ
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}

	if( pclMsg->siHouseUnitItemIndex < 0 || pclMsg->siHouseUnitItemIndex >= MAX_HOUSEUNIT_STORAGE_ITEM_NUMBER )		return;

	pclItemManager->AddUseNum( pclMsg->siHouseUnitHorseEatItemUnique, pclMsg->siHouseUnitHorseEatItemNum );

	// ���ο� ��� - ������ ��� ��踦 ����.
	//NStatistics_Add("Item", pclMsg->siHouseUnitHorseEatItemUnique, "UseNum", pclMsg->siHouseUnitHorseEatItemNum);

	pclStg->clItem[ pclMsg->siHouseUnitItemIndex ].Set( &pclMsg->clHouseUnitItem );
	//------------------------------------------------------------------------------------------

	SI32 id = pclMsg->siCharID;

	// �������� ������ ������ ����Ǿ����� �˷���
	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		cltGameMsgResponse_HouseUnitHorseEatFood clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siHouseUnitItemIndex, &pclMsg->clHouseUnitItem );
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITHORSEEATFOOD, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}

	return;
}


// ������ ���� ����
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE(sPacketHeader* pPacket)
{
	sDBResponse_HouseUnitUsedGoodsBuildingCreate* pclMsg = (sDBResponse_HouseUnitUsedGoodsBuildingCreate*) pPacket;

	if ( pclMsg->siResult != 1 )
	{
		return;
	}

	SI32 id = pclMsg->siCharID;

	if ( id < 1 )
	{
		return;
	}

	if( pclMsg->siItemPos < 0 || pclMsg->siItemPos >= MAX_ITEM_PER_PERSON )			return;

	//------------------------------------------------------------------------------------------
	// ������ ������ ����.
	cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	if ( pclStg == NULL )
	{
		return;
	}
	pclStg->bCreatedHouseUnitUsedGoodsBuilding = true;
	//------------------------------------------------------------------------------------------

	// ���� ȭ�� ������Ʈ( � ���ƴ���. )
	pclItemManager->AddUseNum( ITEMUNIQUE(24025), HOUSEUNIT_CREATEUSEDGOODSBUILDING_USEITEMNUM );

	// ���ο� ��� - ������ ���
	//NStatistics_Add("Item", ITEMUNIQUE(24025), "UseNum", HOUSEUNIT_CREATEUSEDGOODSBUILDING_USEITEMNUM);


	if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	{
		pclCM->CR[id]->pclCI->clCharItem.clItem[ pclMsg->siItemPos ].Set( &pclMsg->clLeftItem );

		cltGameMsgResponse_HouseUnitUsedGoodsBuildingCreate clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siItemPos, &pclMsg->clLeftItem );
		cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITUSEDGOODSBUILDINGCREATE, sizeof(clinfo), (BYTE*)&clinfo);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	
		//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		//{
		//	// [�α��߰� : Ȳ���� 2007. 10. 10] // �������� ���� ����.
		//	// param1 == �ε����� ����. , 
		//	// param2 == ������ ��ġ.
		//	cltServer* pclserver = (cltServer*)pclClient;
		//	pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_CREATE,
		//									0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, &pclMsg->clLeftItem, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
		//									pclMsg->siHouseUnitSlot, pclMsg->siItemPos, 0, 0, 0, NULL, NULL);
		//}
	}

}

// ������ ������ �̾Ƴ�
void cltServer::DoMsg_DBMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS(sPacketHeader* pPacket)
{
	//sDBResponse_HouseUnitMakeItemFromUsedGoods* pclMsg = (sDBResponse_HouseUnitMakeItemFromUsedGoods*) pPacket;

	//if ( pclMsg->siResult != 1 )
	//{
	//	pclLog->FilePrint( TEXT("Config\\HouseUnit.txt"), TEXT("DoMsg_DBMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS pclMsg->siResult = %d"), pclMsg->siResult );
	//	return;
	//}

	//SI32 id = pclMsg->siCharID;

	//if ( id < 1 )
	//{
	//	return;
	//}

	////------------------------------------------------------------------------------------------
	//// ������ ������ ����.
	//cltHouseUnitStorageInfo* pclStg = pclHouseManager->GetStgPointer( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot );
	//if ( pclStg == NULL )
	//{
	//	return;
	//}

	//// pclMsg->siFromItemUnique		// ������ �������� ItemUnique
	//pclStg->clItem[ pclMsg->siFromItemPos ].Init();

	//for( SI16 i = 0; i < MAX_MATERIAL_NUMBER; ++i )
	//{
	//	if ( pclMsg->siToHouseUnitStgItemPos[ i ] >= 0 )
	//	{
	//		pclStg->clItem[ pclMsg->siToHouseUnitStgItemPos[ i ] ].Set( &pclMsg->clMakeLeftItem[ i ] );
	//	}
	//}
	////------------------------------------------------------------------------------------------

	//if( pclCM->IsValidID( id ) && pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID )
	//{
	//	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoods clinfo( pclMsg->siVillageUnique, pclMsg->siHouseUnitSlot, pclMsg->siFromItemPos, pclMsg->siToHouseUnitStgItemPos, pclMsg->clMakeLeftItem );
	//	cltMsg clMsg(GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODS, sizeof(clinfo), (BYTE*)&clinfo);
	//	pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);

	//	cltGameMsgResponse_HouseUnitMakeItemFromUsedGoodsNotify clinfo1( pclCM->CR[id]->GetCharUnique(), pclMsg->siFromItemUnique, pclMsg->siMakePercent );
	//	cltMsg clMsg1(GAMEMSG_RESPONSE_HOUSEUNITMAKEITEMFROMUSEDGOODSNOTIFY, sizeof(clinfo1), (BYTE*)&clinfo1);
	//	((cltCharServer*)pclCM->CR[id])->SendNeighbourMsg( &clMsg1, true);

	//	// ��ó���� ����ġ�� �ο��Ѵ�. 
	//	cltItemPriceUnit* pclprice	= pclItemManager->GetCurrentPrice(pclMsg->siFromItemUnique);
	//	if(pclprice)
	//	{	
	//		cltCharServer* pclchar = (cltCharServer* )pclCM->CR[id];
	//		//--------------------------------------
	//		// ����ġ�� �����ش�. 
	//		//--------------------------------------
	//		SI32 exp	= pclItemManager->GetMakeExpFromItemPrice(pclprice->siPrice , pclchar->pclCI->clIP.GetLevel()) / 2; 
	//		if(exp > 0)
	//		{
	//			pclchar->IncreaseExp(exp, GETEXP_REASON_DISMANTLE);
	//		}

	//		//-------------------------------------
	//		// ���� ����ġ�� �����ش�. 
	//		//-------------------------------------
	//		SI32 skillunique	= SKILL_ALCHEMY; 
	//		SI32 skilllevel = pclchar->pclCI->clCharSkill.GetTotalSkillLevel(skillunique, 0, 0, &pclchar->pclCI->clCharItem.clItem[0]);

	//		SI32 skillexp	= pclItemManager->GetMakeSkillExpFromItemPrice(pclprice->siPrice, skilllevel) / 2; 

	//		// ���� ���ʽ� Ÿ���̸�, 
	//		if(bBonus2TimeSwitch)
	//			skillexp *= 2;
	//		else if(pclchar->pclCI->clBI.bMakeItemService)
	//		{
	//			skillexp = (SI32)(skillexp * 1.2 );
	//		}

	//		pclchar->SetSkillUpdate(skillunique , skillexp);
	//	}
	//}

	//if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	//{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // �� �ϴ� ��ǰ MakePercent = 59% (ȸ����)
	//// param1 == 
	//cltServer* pclserver = (cltServer*)pclClient;
	//pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_HOUSE, LOGCOMMAND_INDEX_HOUSE_SALVAGEFROM,
	//								0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
	//								0, 0, 0, 0, 0, NULL, NULL);
	//}
}