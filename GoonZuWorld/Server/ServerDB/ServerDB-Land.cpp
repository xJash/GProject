// server&db-land
#include "Char\CharManager\CharManager.h"

#include "..\Server\Server.h"
#include "..\Common\Letter\Letter.h"

#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Land.h"

#include "Msg\MsgType-Land.h"
#include "MsgRval-Define.h"

#include "PersonInfo.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "../../CommonLogic/CommonLogic.h"

// ���� ���� ���� ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_MANYLANDUNIT(sPacketHeader* pPacket)
{
	sDBResponse_ManyLandUnit* pclMsg = (sDBResponse_ManyLandUnit*)pPacket;

    if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siResult == 0 ) return;


	SI32 villageunique = pclMsg->siVillageUnique;
	if( pclLandManager->pclStruct[villageunique] == NULL ) return ;



	cltLand *pclLand;
	for( int i = 0; i < MAX_LANDUNIT_NUMBER; i++ )
	{
		pclLand = (cltLand *)pclLandManager->pclStruct[ villageunique ];
		pclLand->SetLandUnit( i, &pclMsg->clLandUnit[i] );
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_ManyLandUnit"));
}

// ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_CHANGECONTRACT(sPacketHeader* pPacket)
{
	sDBResponse_LandChangeContract* pclMsg = (sDBResponse_LandChangeContract*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = 0;
	SI32 id = pclMsg->usCharID;

	if( pclMsg->siResult == 1 ) {

		// �ش��ϴ� ������ ��� ������ �����Ѵ�. 
		cltLand *pclLand = (cltLand *)pclLandManager->pclStruct[pclMsg->siVillageUnique];
		pclLand->SetRentContract( &pclMsg->clContract );
	
		if(pclCM->IsValidID(id)== false)return ;

		// Ŭ���̾�Ʈ�� ����� ��������� ������. 
		if(pclCM->CR[id]->IsValidConnection())	
		{
			cltStrInfo* pclinfo = pclLandManager->GetStrInfo(pclMsg->siVillageUnique);
			if(pclinfo == NULL)return ;

			cltMsg clMsg(GAMEMSG_RESPONSE_STRINFO,  pclinfo->GetTotalSize(), (BYTE*)pclinfo);
			pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
			
		}
		returnval = SRVAL_LAND_SUCCESS_SETCONTRACT;

	}

	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_LAND, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

// ���� ��û 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_RENTAPPLY(sPacketHeader* pPacket)
{
	sDBResponse_LandRentApply* pclMsg = (sDBResponse_LandRentApply*)pPacket;
    
	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = SRVAL_LAND_FAIL_APPLY;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	switch( pclMsg->siResult ) {
	case 1:
		{
			
			// ��û�ڸ� ����Ѵ�.
			if(pclMsg->siVillageUnique)
			{
				cltLand *pclLand = (cltLand *)pclLandManager->pclStruct[pclMsg->siVillageUnique];
				pclLand->AddApplyer( &pclMsg->clApplyer, &pclMsg->clContract );
			}

			returnval = SRVAL_LAND_SUCCESS_APPLY;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 18] // ���� ��û �α׾���. (������������.)
				// param1	 == �ε��� 
				// param2	 == �Ӵ� ������
				// param3	 == �Ӵ� �Ⱓ.
				// pszParam1 == �Ӵ��������. 
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
					pclMsg->clContract.clDate.uiYear,
					pclMsg->clContract.clDate.uiMonth,
					pclMsg->clContract.clDate.uiDay,
					pclMsg->clContract.clDate.uiHour,
					pclMsg->clContract.clDate.uiMinute );


				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_RENTAPPLY, 
					0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					pclMsg->siIndex, pclMsg->clContract.siRentFee, pclMsg->clContract.siRentPeriod, 0, 0,
					pszCharParam1, NULL);
			}
		}
		break;
	case 2:
		{
			returnval = SRVAL_LAND_FAIL_APPLY;
		}
		break;
	case 3:
		{
			returnval = SRVAL_LAND_FAIL_APPLY_ALREADYAPPLY;
		}
		break;

	case 4:
		{
			returnval = SRVAL_LAND_FAIL_APPLY;
		}
		break;
	}
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_LAND, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}

// ���� ��û ��� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_CANCELRENTAPPLY(sPacketHeader* pPacket)
{
	sDBResponse_LandCancelRentApply* pclMsg = (sDBResponse_LandCancelRentApply *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	SI32 returnval = SRVAL_LAND_FAIL_CANCELAPPLY;

	if( pclMsg->siResult == 1 ) {

		returnval = SRVAL_LAND_SUCCESS_CANCELAPPLY;
		
		// ��û�ڸ� ����Ѵ�.
		if(pclMsg->siVillageUnique) {

			cltLand *pclLand;
			pclLand = (cltLand *)pclLandManager->pclStruct[pclMsg->siVillageUnique];
			pclLand->DeleteApplyer( pclMsg->siPersonID );
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� ���� ��û��� �α׾���. 
			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_CANCELRENTAPPLY, 
				0, (cltCharServer*)pclCM->CR[id], NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
				0, 0, 0, 0, 0, NULL, NULL);
		}
	}
	
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_LAND, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

}


// ���� ����� ��� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_APPLYERLIST(sPacketHeader* pPacket)
{
	sDBResponse_LandApplyerList* pclMsg = (sDBResponse_LandApplyerList*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	if(pclMsg->siResult == 0) return ;

	cltLand *pclLand = NULL;
	for( int i = 0; i < MAX_APPLY_PER_LAND; i++ )
	{
		if(pclLandManager->pclStruct[pclMsg->siVillageUnique])
		{
			pclLand = (cltLand *)pclLandManager->pclStruct[pclMsg->siVillageUnique];
			pclLand->SetRentApplyer( i, &pclMsg->clApplyer[i].clPerson, &pclMsg->clApplyer[i].clContract );
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_LandApplyerList"));
}

// ���� ����� ��� ���� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_DELAPPLYER(sPacketHeader* pPacket)
{
	sDBResponse_LandDelApplyer* pclMsg = (sDBResponse_LandDelApplyer *)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siDelSlotNum < 0 || pclMsg->siDelSlotNum > MAX_APPLY_PER_LAND )				return;

	SI32 returnval = 0;
	SI32 id	= pclMsg->usCharID;

	if( pclMsg->siResult != 1 ) return;

	// ������ ��쿡�� ���Ӽ����� ���� ����� ����� �����Ѵ�. 
	cltLand *pclLand = (cltLand *)pclLandManager->pclStruct[pclMsg->siVillageUnique];
	
	// PCK : ��������� ����� ������ ������ PersonID
	SI32	siDelPersonID = 0;

	if(pclMsg->siDelSlotNum >=0 && pclMsg->siDelSlotNum < MAX_APPLY_PER_LAND)
	{
		siDelPersonID = pclLand->clApplyer[pclMsg->siDelSlotNum].clPerson.GetPersonID();
	}

	// PCK : ���� ����� ����� ��� �����ϴ°��� ����
	if(siDelPersonID > 0)	pclLand->DeleteApplyer(siDelPersonID);

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� ����� ����� ����. 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_RENTAPPLYDELETE, 
			0, (cltCharServer*)(pclCM->CR[id]), NULL, siDelPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
			0, 0, 0, 0, 0, NULL, NULL);
	}

	// Ŭ���̾�Ʈ�� ���� ����� ����� ��� �����϶�� �޽����� ������. 
	if(pclCM->IsValidID(id) == TRUE)
	{
		cltMsg clMsg(GAMEMSG_RESPONSE_LAND_DELAPPLYER, sizeof(SI32), (BYTE*)&pclMsg->siDelSlotNum);
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
	}
}

// �Ӵ� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_RENT(sPacketHeader* pPacket)
{

	sDBResponse_LandRent* pclMsg = (sDBResponse_LandRent*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;

	SI32 returnval = SRVAL_LAND_FAIL_RENT;

	cltLand *pclLand = (cltLand*)pclLandManager->pclStruct[ pclMsg->siVillageUnique ];
	if( pclLand == NULL ) return;

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	// ����� ��ܿ��� Person�� �����Ѵ�. 
	pclLand->DeleteApplyer( pclMsg->clPerson.siPersonID );

	switch(pclMsg->siResult)
	{
	case 0:
		break;
	case -1:
		returnval	= SRVAL_LAND_FAIL_NOTSAMECONTRACT;		// ��� ������ �ٸ��� 
		break;

	case -2:
		returnval	= SRVAL_LAND_FAIL_NOMOREREALESTATE;		// �ε��� ������ �ʰ��ؼ� ���� �� ����. 
		break;

	case 1:
		{
			returnval	= SRVAL_LAND_SUCCESS_RENT;				// �����Ӵ뿡 �����ߴ�.
				
			cltLand *pclLand = (cltLand*)pclLandManager->pclStruct[ pclMsg->siVillageUnique ];
			if( pclLand == NULL ) return;

			// ���� ���������� ����Ѵ�. 
			pclLand->SetRent( pclMsg->siIndex, &pclMsg->clPerson, &pclMsg->clRentContract );
			

			// ������ ������. 
			cltLetterMsg_RentLand clletter(pclMsg->siVillageUnique, pclMsg->siIndex);
			SI32 id = SendLetterMsg(pclMsg->clPerson.GetPersonID(), (cltLetterHeader*)&clletter);
			if(pclCM->IsValidID(id))
			{
				// Person�� �ľ��� �ε��� ������ ������Ʈ �Ѵ�. 
				pclCM->CR[id]->pclCI->clRealEstate.Add(REALESTATE_TYPE_LAND, pclMsg->siVillageUnique, pclMsg->siIndex, &pclMsg->clRentContract);
				pclCM->CR[id]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);

			}

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // �Ӵ� �α׾���. 
				// param1		 == ���� ������ �ε���, 
				// param2		 == �Ӵ� ������.
				// param3		 == �Ӵ� �Ⱓ.
				// pszCharParam1 == �Ӵ��������.
				TCHAR pszCharParam1[50] = {'\0', };
				StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), TEXT("%d-%d-%d, %d:%d"),	
					pclMsg->clRentContract.clDate.uiYear,
					pclMsg->clRentContract.clDate.uiMonth,
					pclMsg->clRentContract.clDate.uiDay,
					pclMsg->clRentContract.clDate.uiHour,
					pclMsg->clRentContract.clDate.uiMinute );

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_RENT, 
					0, (cltCharServer*)(pclCM->CR[id]), NULL, pclMsg->clPerson.siPersonID, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					pclMsg->siIndex, pclMsg->clRentContract.siRentFee, pclMsg->clRentContract.siRentPeriod, 0, 0, 
					pszCharParam1, NULL);
			}
		}
		break;
	}

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg( RANKTYPE_LAND, returnval,  0, 0, pclCM->CR[id]->GetCharUnique() );
	}

}

// �Ӵ�� ¡�� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_PAYRENTFEE(sPacketHeader* pPacket)
{

	sDBResponse_LandPayRentFee* pclMsg = (sDBResponse_LandPayRentFee*)pPacket;

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
				sDBRequest_LandRecall clMsg(pclMsg->siPersonID, LANDRECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siLandIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
			else
			{
				cltLetterMsg_PayLandRentFee clletter(pclMsg->siVillageUnique, pclMsg->siLandIndex, pclMsg->siRentFee, pclMsg->siDelayNum, pclMsg->siDelayMoney);
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
			clmoney.Set( &pclMsg->clLandMoney );
			pclLandManager->SetMoney(pclMsg->siVillageUnique, &clmoney);

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // ���� �̿�� ����. 
				// param1 == �����ȣ, 
				// param3 == ��ü Ƚ��, 
				// param4 == ��ü��,
				// param5 == ���� �����ڱ�
				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_RENTFEEPAY, 
					0, NULL, NULL, pclMsg->siPersonID, pclMsg->siRentFee, pclMsg->clBankMoney.itMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					pclMsg->siLandIndex, 0, pclMsg->siDelayNum, pclMsg->siDelayMoney, pclMsg->clLandMoney.itMoney, NULL, NULL);
			}
		}
		break;

	case -1:
		{
			// ��ü Ƚ���� 3ȸ�� �ʰ��ϴ� ��� ������ �ʱ�ȭ�Ѵ�. 
			if( pclMsg->siDelayNum > 3)
			{
				// DB�Ŵ������� ������ ȸ���� ���� ��û�Ѵ�. 
				sDBRequest_LandRecall clMsg(pclMsg->siPersonID, LANDRECALL_REASON_FEEDELAY, pclMsg->siVillageUnique, pclMsg->siLandIndex);
				pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
			}
		}
		break;

	}
}

// ����  ȸ�� 
void cltServer::DoMsg_DBMSG_RESPONSE_LAND_RECALL(sPacketHeader* pPacket)
{

	sDBResponse_LandRecall* pclMsg = (sDBResponse_LandRecall*)pPacket;

	if( pclMsg->siVillageUnique < 0 || pclMsg->siVillageUnique >= MAX_VILLAGE_NUMBER )		return;
	if( pclMsg->siLandIndex < 0		|| pclMsg->siLandIndex >= MAX_LANDUNIT_NUMBER )			return;

	if(pclMsg->siResult == 0)
	{
		return ;
	}

	SI32 personid		= pclMsg->siPersonID;
	SI32 villageunique	= pclMsg->siVillageUnique;
	SI32 landindex		= pclMsg->siLandIndex;

	cltLand *pclLand = (cltLand*)pclLandManager->pclStruct[ villageunique ];
	if( pclLand == NULL ) return;

	pclLand->clUnit[ landindex ].Init();


	// ������ ������. 
	cltLetterMsg_LandRecall clletter(pclMsg->siRecallReason, pclMsg->siVillageUnique, pclMsg->siLandIndex);
	SI32 letterid = SendLetterMsg(personid, (cltLetterHeader*)&clletter);
	if(pclCM->IsValidID(letterid))
	{
		pclCM->CR[letterid]->pclCI->clRealEstate.Delete(REALESTATE_TYPE_LAND, pclMsg->siVillageUnique, pclMsg->siLandIndex);
		pclCM->CR[letterid]->SetUpdateSwitch(UPDATE_REALESTATE, true, 0);
	}

	if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
	{
		// [�α��߰� : Ȳ���� 2007. 10. 10] // �Ӵ� �Ϸ�(��)  �α׾���.
		// param1 == ���� �ε���.
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_FARM, LOGCOMMAND_INDEX_FARM_END, 
							pclMsg->siRecallReason, NULL, NULL, pclMsg->siPersonID, 0, 0, NULL, 0, 0, 0, villageunique, 0, 0, 
							landindex, 0, 0, 0, 0, NULL, NULL);
	}
}
