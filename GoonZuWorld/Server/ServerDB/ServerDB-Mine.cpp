// server&db-land
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\Common\Letter\Letter.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Mine.h"

#include "Msg\MsgType-Mine.h"
#include "MsgRval-Define.h"

#include "PersonInfo.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

// ���� ���� ���� ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYMINEUNIT(sPacketHeader* pPacket)
{
	sDBResponse_ManyMineUnit* pclMsg = (sDBResponse_ManyMineUnit*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if( pclMsg->siResult == 0 ) return;

	SI32 villageunique = pclMsg->siVillageUnique;
	if( villageunique < 0 || villageunique >= MAX_VILLAGE_NUMBER )	return;
	if( pclMineManager->pclStruct[villageunique] == NULL )			return;

	cltMine *pclMine;
	for( int i = 0; i < MAX_MINEUNIT_NUMBER; i++ )
	{
		pclMine = (cltMine *)pclMineManager->pclStruct[ villageunique ];
		pclMine->SetMineUnit( i, &pclMsg->clMineUnit[i] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_ManyMineUnit"));
}

// ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_CHANGECONTRACT(sPacketHeader* pPacket)
{

	sDBResponse_MineChangeContract* pclMsg = (sDBResponse_MineChangeContract*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = 0;
	SI32 id = pclMsg->usCharID;

	if( pclMsg->siResult == 1 ) {

		// �ش��ϴ� ������ ��� ������ �����Ѵ�. 
		cltMine *pclMine = (cltMine *)pclMineManager->pclStruct[pclMsg->siVillageUnique];
		pclMine->SetRentContract( &pclMsg->clContract );
	
		if(pclCM->IsValidID(id)== false)return ;

		// Ŭ���̾�Ʈ�� ����� ��������� ������. 
		if(pclCM->CR[id]->IsValidConnection())	
		{
			cltStrInfo* pclinfo = pclMineManager->GetStrInfo(pclMsg->siVillageUnique);
			if(pclinfo == NULL)return ;

			cltMsg clMsg(GAMEMSG_RESPONSE_STRINFO,  pclinfo->GetTotalSize(), (BYTE*)pclinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			
		}
		returnval = SRVAL_MINE_SUCCESS_SETCONTRACT;

	}

	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_MINE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

// ���� ��û 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_RENTAPPLY(sPacketHeader* pPacket)
{

	sDBResponse_MineRentApply* pclMsg = (sDBResponse_MineRentApply*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = SRVAL_MINE_FAIL_APPLY;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	switch( pclMsg->siResult ) {
	case 1:
		{
			
			// ��û�ڸ� ����Ѵ�.
			if(pclMsg->siVillageUnique)
			{
				cltMine *pclMine = (cltMine *)pclMineManager->pclStruct[pclMsg->siVillageUnique];
				pclMine->AddApplyer( &pclMsg->clApplyer, &pclMsg->clContract );
			}

			returnval = SRVAL_MINE_SUCCESS_APPLY;

			// ���� ��û�� ���� �Ҷ��� �α׸� �����.
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 18] // ���� ���� ��û �α׾���. 
				// param1		 == ����, 
				// param2		 == �Ⱓ, 
				// pszCharParam1 == ��Ͻð� (���ӳ� �ð�)
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
					pclMsg->clContract.clDate.uiYear,
					pclMsg->clContract.clDate.uiMonth,
					pclMsg->clContract.clDate.uiDay,
					pclMsg->clContract.clDate.uiHour,
					pclMsg->clContract.clDate.uiMinute );

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_RENT_APPLY, 
					0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					pclMsg->clContract.siRentFee, pclMsg->clContract.siRentPeriod, 0, 0, 0,
					pszCharParam1, NULL);
			}
		}
		break;
	case 2:
		{
			returnval = SRVAL_MINE_FAIL_APPLY;
		}
		break;
	case 3:
		{
			returnval = SRVAL_MINE_FAIL_APPLY_ALREADYAPPLY;
		}
		break;

	case 4:
		{
			returnval = SRVAL_MINE_FAIL_APPLY;
		}
		break;
	}
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_MINE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// ���� ��û ��� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_CANCELRENTAPPLY(sPacketHeader* pPacket)
{

	sDBResponse_MineCancelRentApply* pclMsg = (sDBResponse_MineCancelRentApply *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = SRVAL_MINE_FAIL_CANCELAPPLY;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if( pclMsg->siResult == 1 ) {

		returnval = SRVAL_MINE_SUCCESS_CANCELAPPLY;
		
		// ��û�ڸ� ����Ѵ�.
		if(pclMsg->siVillageUnique) {

			cltMine *pclMine;
			pclMine = (cltMine *)pclMineManager->pclStruct[pclMsg->siVillageUnique];
			pclMine->DeleteApplyer( pclMsg->siPersonID );
		}

		// ��û��ҿ� �����Ҷ��� �α׸� �����.
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 9] // ���� ��û ��� �α׾���.
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_CANCEL_RENT_APPLY, 
				0, (cltCharServer*)(pclCM->CR[id]), NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				0, 0, 0, 0, 0, NULL, NULL);
		}
	}
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_MINE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}	
}


// ���� ����� ��� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_APPLYERLIST(sPacketHeader* pPacket)
{
	sDBResponse_MineApplyerList* pclMsg = (sDBResponse_MineApplyerList*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if(pclMsg->siResult == 0) return ;

	cltMine *pclMine = NULL;
	for( int i = 0; i < MAX_APPLY_PER_MINE; i++ )
	{
		if(pclMineManager->pclStruct[pclMsg->siVillageUnique])
		{
			pclMine = (cltMine *)pclMineManager->pclStruct[pclMsg->siVillageUnique];
			pclMine->SetRentApplyer( i, &pclMsg->clApplyer[i].clPerson, &pclMsg->clApplyer[i].clContract );
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_MineApplyerList"));
}

// ���� ����� ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_DELAPPLYER(sPacketHeader* pPacket)
{
	sDBResponse_MineDelApplyer* pclMsg = (sDBResponse_MineDelApplyer *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siDelSlotNum < 0 || pclMsg->siDelSlotNum > MAX_APPLY_PER_MINE )				return;

	SI32 returnval = 0;

	if( pclMsg->siResult != 1 ) return;
	
	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	// ������ ��쿡�� ���Ӽ����� ���� ����� ����� �����Ѵ�. 
	cltMine *pclMine	 = (cltMine *)pclMineManager->pclStruct[pclMsg->siVillageUnique];
	
	// [�߰� : Ȳ���� 2007. 11. 2 ���� ����� ��� �� ������ ������ personid.]
	SI32	siDelPerSonID = 0;

	if(pclMsg->siDelSlotNum >=0 && pclMsg->siDelSlotNum < MAX_APPLY_PER_MINE)
	{
		siDelPerSonID = pclMine->clApplyer[pclMsg->siDelSlotNum].clPerson.GetPersonID();
	}

	if(pclCM->IsValidID(pclMsg->usCharID) == TRUE)
	{
		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 4] // �����Ӵ� ����� ����.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_RENT_APPLYER_DELETE, 
											0, (cltCharServer*)pclCM->CR[id], NULL, siDelPerSonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
											0, 0, 0, 0, 0, NULL, NULL);
		}
	}

	// [�߰� : Ȳ���� 2007. 11. 2 ���� ����� ����� ������ �����ϴ� ���� ����.]
	pclMine->DeleteApplyer(siDelPerSonID);

	// Ŭ���̾�Ʈ�� ���� ����� ����� ��� �����϶�� �޽����� ������. 

	if(pclCM->IsValidID(id) == TRUE)
	{
		cltMsg clMsg(GAMEMSG_RESPONSE_MINE_DELAPPLYER, sizeof(SI32), (BYTE*)&pclMsg->siDelSlotNum);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// �Ӵ� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_RENT(sPacketHeader* pPacket)
{
	sDBResponse_MineRent* pclMsg = (sDBResponse_MineRent*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = SRVAL_MINE_FAIL_RENT;

	cltMine *pclMine = (cltMine*)pclMineManager->pclStruct[ pclMsg->siVillageUnique ];
	if( pclMine == NULL ) return;

	// ����� ��ܿ��� Person�� �����Ѵ�. 
	pclMine->DeleteApplyer( pclMsg->clPerson.siPersonID );

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case -1:
		returnval	= SRVAL_MINE_FAIL_NOTSAMECONTRACT;		// ��� ������ �ٸ��� 
		break;

	case -2:
		returnval	= SRVAL_MINE_FAIL_NOMOREREALESTATE;		// �ε��� ������ �ʰ��ؼ� ���� �� ����. 
		break;

	case 1:
		{
			returnval	= SRVAL_MINE_SUCCESS_RENT;				// �����Ӵ뿡 �����ߴ�.
				
			cltMine *pclMine = (cltMine*)pclMineManager->pclStruct[ pclMsg->siVillageUnique ];
			if( pclMine == NULL ) return;

			// ���� ���������� ����Ѵ�. 
			pclMine->SetRent( pclMsg->siIndex, &pclMsg->clPerson, &pclMsg->clRentContract );
			

			// ������ ������. 
			cltLetterMsg_RentMine clletter(pclMsg->siVillageUnique, pclMsg->siIndex);
			SI32 id = SendLetterMsg(pclMsg->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);
			if(pclCM->IsValidID(id))
			{
				// Person�� �ľ��� �ε��� ������ ������Ʈ �Ѵ�. 
				pclCM->CR[id]->pclCI->clRealEstate.Add(REALESTATE_TYPE_MINE, pclMsg->siVillageUnique, pclMsg->siIndex, &pclMsg->clRentContract);
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);

			}	
			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� �Ӵ� �α׾���. 
				// param1		 == ���� ��ȣ. 
				// param2		 == �Ӵ� ������.
				// param3		 == �Ӵ�Ⱓ.
				// pszCharParam1 == �Ӵ뼺���������� ���� �ð� 
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
																			pclMsg->clRentContract.clDate.uiYear,
																			pclMsg->clRentContract.clDate.uiMonth,
																			pclMsg->clRentContract.clDate.uiDay,
																			pclMsg->clRentContract.clDate.uiHour,
																			pclMsg->clRentContract.clDate.uiMinute );

				cltCharServer* pclchar = NULL;
				if(pclCM->IsValidID(pclMsg->usCharID))		pclchar = (cltCharServer*)(pclCM->CR[pclMsg->usCharID]);
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_RENT, 
									 0, pclchar, NULL, pclMsg->clPerson.GetPersonID(), 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
									 pclMsg->siIndex, pclMsg->clRentContract.siRentFee, pclMsg->clRentContract.siRentPeriod, 0, 0, 
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
		SendServerResponseMsg( RANKTYPE_MINE, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}

}

// �Ӵ�� ¡�� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_PAYRENTFEE(sPacketHeader* pPacket)
{

	sDBResponse_MinePayRentFee* pclMsg = (sDBResponse_MinePayRentFee*)pPacket;

	SI32 id = 0;
	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
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
				sDBRequest_MineRecall clMsg(pclMsg->siPersonID, MINERECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siMineIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
			else
			{
				cltLetterMsg_PayMineRentFee clletter(pclMsg->siVillageUnique, pclMsg->siMineIndex, pclMsg->siRentFee, pclMsg->siDelayNum, pclMsg->siDelayMoney);
				// ������ DB�� Ŭ���̾�Ʈ���� ������. 
				SendLetterMsg(pclMsg->siPersonID, (cltLetterHeader*)&clletter);
			}
			

			if(pclCM->IsValidID(id))
			{
				// �������� �����ܰ� ������Ʈ �Ѵ�. 
				pclCM->CR[id]->pclCI->clBank.SetMoney( pclMsg->clBankMoney.itMoney );
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);
			}

			// ������ ���� �ڱ��� ������Ʈ �Ѵ�. 
			cltMoney clmoney;
			clmoney.Set( &pclMsg->clMineMoney );
			pclMineManager->SetMoney(pclMsg->siVillageUnique, &clmoney);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 16] // �����Ӵ� ������ ����.
				// param1 == ���� ������ �ε���, 
				// param3 == ��ü Ƚ��, 
				// param4 == ��ü�� �հ�.
				// param5 == ���� �����ڱ�
				cltServer * pclserver = (cltServer*)pclClient;
				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_RENT_RENT_FREE_PAY, 
					0, NULL, NULL, pclMsg->siPersonID, pclMsg->siRentFee, pclMsg->clBankMoney.itMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					pclMsg->siMineIndex, 0, pclMsg->siDelayNum, pclMsg->siDelayMoney, pclMsg->clMineMoney.itMoney, NULL, NULL);
			}
		}
		break;

	case -1:
		{
			// ��ü Ƚ���� 3ȸ�� �ʰ��ϴ� ��� ������ �ʱ�ȭ�Ѵ�. 
			if( pclMsg->siDelayNum > 3)
			{
				// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
				sDBRequest_MineRecall clMsg(pclMsg->siPersonID, MINERECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siMineIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
		break;

	}
}

// ����  ȸ�� 
void cltServer::DoMsg_DBMSG_RESPONSE_MINE_RECALL(sPacketHeader* pPacket)
{

	sDBResponse_MineRecall* pclMsg = (sDBResponse_MineRecall*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siMineIndex < 0 || pclMsg->siMineIndex >= MAX_MINEUNIT_NUMBER )				return;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 personid		= pclMsg->siPersonID;
	SI32 villageunique	= pclMsg->siVillageUnique;
	SI32 landindex		= pclMsg->siMineIndex;

	cltMine *pclMine = (cltMine*)pclMineManager->pclStruct[ villageunique ];
	if( pclMine == NULL ) return;

	pclMine->clUnit[ landindex ].Init();


	// ������ ������. 
	cltLetterMsg_MineRecall clletter(pclMsg->siRecallReason, pclMsg->siVillageUnique, pclMsg->siMineIndex);
	SI32 letterid = SendLetterMsg(personid, (cltLetterHeader*)&clletter);
	if(pclCM->IsValidID(letterid))
	{
		pclCM->CR[letterid]->pclCI->clRealEstate.Delete(REALESTATE_TYPE_MINE, pclMsg->siVillageUnique, pclMsg->siMineIndex);
		pclCM->CR[letterid]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 9. 3] // ���� �Ӵ��ȯ �α׾���. 
		// param1 ==  �����ȣ.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINE, LOGCOMMAND_INDEX_MINE_RECALL, 
							pclMsg->siRecallReason, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							pclMsg->siMineIndex, 0, 0, 0, 0, NULL, NULL);
	}
}
