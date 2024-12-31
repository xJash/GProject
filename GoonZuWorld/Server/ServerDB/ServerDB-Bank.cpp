//---------------------------------
// 2003/8/5 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\CommonLogic\Bank\Bank-Manager.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "..\..\Common\Map\Map.h"
#include "Char\CharManager\CharManager.h"

#include "..\../../Server/AuthServer/AuthMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Bank.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-Stock.h"

#include "MsgRval-Define.h"
#include "MsgType-Stock.h"


// ���¸� ������ ��. 
void cltServer::DoMsg_DBMSG_RESPONSE_CREATEBANKACCOUNT(sPacketHeader* pPacket)
{
	sDBResponse_CreateBankAccount* pclMsg = (sDBResponse_CreateBankAccount*)pPacket;

	SI32 id	= pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE)return ;

	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		returnval = SRVAL_BANK_FAILCREATEACCOUNT;
		break;
	case 1:
		{
			//------------------------------
			// ���� ���� ������Ʈ. 
			//------------------------------
			// ���� ������ Ȯ���Ѵ�. 
			pclCM->CR[id]->pclCI->clBank.Set(&pclMsg->clBankAccount);
			
			// Ŭ���̾�Ʈ�� ������ ������. 
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

			returnval = SRVAL_BANK_SUCCESSCREATEACCOUNT;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 9. 4] // ���� ���� ����.
				// param1 == ���¹�ȣ.
				cltCharServer* pclchar = NULL;
				if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_CREATEBANKACCOUNT, 
										0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->clBankAccount.clAccountNum.GetVillageUnique(), 0, 0, 
										pclMsg->clBankAccount.clAccountNum.siAccountNum, 0, 0, 0, 0, NULL, NULL);
			}
		}
		break;
	case -1:
		returnval = SRVAL_BANK_FAILCREATEACCOUNT_ALREADY;
		break;
	}
	

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_BANK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// ���¸� ������ ��. 
void cltServer::DoMsg_DBMSG_RESPONSE_CLOSEBANKACCOUNT(sPacketHeader* pPacket)
{
	sDBResponse_CloseBankAccount* pclMsg = (sDBResponse_CloseBankAccount*)pPacket;

	SI32 id	= pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE)return ;

	SI32 returnval = 0;

	switch(pclMsg->siResult)
	{
	case 0:
		returnval = SRVAL_BANK_FAILCLOSEACCOUNT;
		break;
	case 1:
		{
			//------------------------------
			// ���� ���� ������Ʈ. 
			//------------------------------
			// ���� ������ Ȯ���Ѵ�. 
			pclCM->CR[id]->pclCI->clBank.Set(&pclMsg->clBankAccount);
			
			// Ŭ���̾�Ʈ�� ������ ������. 
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);
			
			//-----------------------------
			// ���� ���� ������Ʈ 
			//-----------------------------
			pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->siMoney);
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

			returnval = SRVAL_BANK_SUCCESSCLOSEACCOUNT;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� ���� ����. 
				cltCharServer* pclchar = NULL;
				if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_CLOSEBANKACCOUNT, 
					0, pclchar, NULL, 0, 0, pclMsg->siMoney, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
					0, 0, 0, 0, 0, NULL, NULL);
			}
		}

		break ;
	case -2:
		{
			returnval = SRBAL_BANK_FAILCLOSEACCOUNT_OTHERVILLAGE;
		}
		break;
	case -3:
		{
			returnval = SRBAL_BANK_FAILCLOSEACCOUNT_CHECKMARKET;
		}
		break;
	}
		
		
	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_BANK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}

// ���忡 ���� �Ա��϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_INPUTMONEYTOBANK(sPacketHeader* pPacket)
{
	sDBResponse_InputMoneyToBank* pclMsg = (sDBResponse_InputMoneyToBank*)pPacket;

	SI32 id	= pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE)return ;

	// ����� Ȯ���Ѵ�. 
	
	SI32 returnval = 0;
	switch(pclMsg->siResult)
	{
	case 0:
		return;
	case 1:	// �Ա� ����. 
		{
			if( pclMsg->clBankAccount.GetMoney() == 0 ) break;
			returnval	= SRVAL_BANK_SUCCESSINPUTMONEY;

			//------------------------------
			// ���� ���� ������Ʈ. 
			//------------------------------
			// ���� ������ Ȯ���Ѵ�. 
			pclCM->CR[id]->pclCI->clBank.Set(&pclMsg->clBankAccount);

			// Ŭ���̾�Ʈ�� ������ ������. 
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

			//-------------------------------
			// ���� ���� ������Ʈ 
			//-------------------------------
			// ���� ������ Ȯ���Ѵ�. 
			pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->clMoney.itMoney);

			// Ŭ���̾�Ʈ�� ������ ������. 
			pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

			//-------------------------------
			// ToBank ������Ʈ. 
			//-------------------------------
			SI32 villageunique = pclMsg->clBankAccount.clAccountNum.GetVillageUnique();
			if(villageunique > 0)
			{
				cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
				if(pclinfo)
				{
					pclinfo->clBankStrInfo.clTotalInputMoney.Set(&pclMsg->clTotalInputMoney);
					pclinfo->clCommonInfo.clMoney.Set(&pclMsg->clCurrentLeftMoney);
				}

			}

			//-----------------------------
			// ByBank ������Ʈ 
			//-----------------------------
			villageunique = pclMsg->siByBankVillageUnique;
			if(villageunique > 0)
			{
				cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
				if(pclinfo)
				{
					pclinfo->clBankStrInfo.clTotalInputMoney.Set(&pclMsg->clByBankTotalInputMoney);
					pclinfo->clCommonInfo.clMoney.Set(&pclMsg->clByBankCurrentLeftMoney);
				}
			}

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{ 
				// [�α��߰� : Ȳ���� 2007. 10. 16] // ���� �Ա� ����.
				// param1 == ������.
				// param2 == ���� �ܾ�.
				cltCharServer* pclchar = NULL;
				if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

				SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_INPUTMONEYTOBANK, 
					0, pclchar, NULL, 0, pclMsg->clInputMoney.itMoney, pclMsg->clMoney.itMoney, NULL, 0, 0, 0, pclMsg->siByBankVillageUnique, 0, 0, 
					pclMsg->siFee, pclMsg->clBankAccount.GetMoney(), 0, 0, 0, NULL, NULL);
			}
		}
		break;


	case -1: // ���� ���� �Ա� ����. 
		returnval	= SRVAL_BANK_FAILINPUTMONEY_NOACCOUNT;
		break;	

	default:
		return ;
	}

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_BANK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}
}


// ���忡�� ���� ����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_OUTPUTMONEYFROMBANK(sPacketHeader* pPacket)
{
	sDBResponse_OutputMoneyFromBank* pclMsg = (sDBResponse_OutputMoneyFromBank*)pPacket;

	SI32 id	= pclMsg->usCharID;

	if(pclCM->IsValidID(id) == FALSE)return ;

	// ����� Ȯ���Ѵ�. 
	SI32 returnval = 0;
	switch(pclMsg->siResult)
	{
	case 0:
		return ;
	case 1:	// ��� ����. 
		returnval	= SRVAL_BANK_SUCCESSOUTPUTMONEY;

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 16] // ��� �Ա� ����. 
			// param1 == ������.
			// param2 == ���� �ܾ�.
			cltCharServer* pclchar = NULL;
			if(pclCM->IsValidID(id))		pclchar = (cltCharServer*)pclCM->CR[id];

			SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_OUTPUTMONEYFROMBANK, 
				0, pclchar, NULL, 0, pclMsg->clOutputMoney.itMoney, pclMsg->clMoney.itMoney, NULL, 0, 0, 0, pclMsg->siByBankVillageUnique, 0, 0, 
				pclMsg->siFee, pclMsg->clBankAccount.GetMoney(), 0, 0, 0, NULL, NULL);
		}
		break;
	case -1: // ���°� ����. 
		returnval	= SRVAL_BANK_FAILOUTPUTMONEY_NOACCOUNT;
		break;
	case -2:	// �ܾ� ����. 
		returnval	= SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHMONEYINACCOUNT;
		break;
	case -3:	// ��� ����-���»���. 
		returnval	= SRVAL_BANK_SUCCESSOUTPUTMONEY_DELACCOUNT;
		break;
	case -4:	// ��� ����. - ������ ����. 	
		returnval	= SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHFEE;
		break;
	default:
		MsgBox( TEXT("1fd9jfd"), TEXT("fld9j:%d"), pclMsg->siResult);
		return ;
	}

	//----------------------------------
	// ���� ���� ������Ʈ 
	//----------------------------------
	// ���� ������ Ȯ���Ѵ�. 
	pclCM->CR[id]->pclCI->clBank.Set(&pclMsg->clBankAccount);

	// Ŭ���̾�Ʈ�� ������ ������. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_BANK, true, 0);

	//----------------------------------
	// ���� ���� ������Ʈ 
	//----------------------------------
	// ���� ������ Ȯ���Ѵ�. 
	pclCM->CR[id]->pclCI->clIP.SetMoney(pclMsg->clMoney.itMoney);

	// Ŭ���̾�Ʈ�� ������ ������. 
	pclCM->CR[id]->SetUpdateSwitch(UPDATE_IP, true, 0);

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_BANK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());
	}

	if(pclMsg->bCancelStockOrder)
	{
		// PersonID�� ���Ѵ�. 
		SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

		// �ֹ��� ����϶�� ��û�� DB�� ������.
		sDBRequest_CancelStockOrder clMsg(id, personid);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		cltGameMsgResponse_CancelStockOrder clcancelstockorder;
		cltMsg clMsg2(GAMEMSG_RESPONSE_CANCEL_STOCKORDER, sizeof(clcancelstockorder), (BYTE*)&clcancelstockorder);

		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg2);


	}

	//-------------------------------
	// ToBank ������Ʈ. 
	//-------------------------------
	SI32 villageunique = pclMsg->clBankAccount.clAccountNum.GetVillageUnique();
	if(villageunique > 0)
	{
		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
		if(pclinfo)
		{
			pclinfo->clBankStrInfo.clTotalInputMoney.Set(&pclMsg->clTotalInputMoney);
			pclinfo->clCommonInfo.clMoney.Set(&pclMsg->clCurrentLeftMoney);
		}
	}

	//-----------------------------
	// ByBank ������Ʈ 
	//-----------------------------
	villageunique = pclMsg->siByBankVillageUnique;
	if(villageunique > 0)
	{
		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
		if(pclinfo)
		{
			pclinfo->clBankStrInfo.clTotalInputMoney.Set(&pclMsg->clByBankTotalInputMoney);
			pclinfo->clCommonInfo.clMoney.Set(&pclMsg->clByBankCurrentLeftMoney);
		}
	}
}

// ���� ������ ������ �����϶�� ��û�� ���� ����. 
void cltServer::DoMsg_DBMSG_RESPONSE_SETBANKFEE(sPacketHeader* pPacket)
{
	sDBResponse_SetBankFee* pclMsg = (sDBResponse_SetBankFee*)pPacket;

	// ����� Ȯ���Ѵ�. 
	SI32 returnval = 0;
	switch(pclMsg->siResult)
	{
	case 0:
		return ;
	case 1:	// ������ ���� ����. 
		returnval	= SRVAL_BANK_SUCCESSSETFEE;
		break;
	default:
		MsgBox( TEXT("vc984j"), TEXT("fdd:%d"), pclMsg->siResult);
	}

	// ������ �ش� ������ ������ ������Ʈ �Ѵ�. 
	cltStrInfo* pclinfo = pclBankManager->GetStrInfo(pclMsg->siVillageUnique);
	if(pclinfo == NULL)return ;
	pclinfo->clBankStrInfo.clFee.Set(&pclMsg->clFee);

	SI32 id	= pclMsg->usCharID;
	if(pclCM->IsValidID(id) == FALSE)return ;

	if(returnval)
	{
		// Ŭ���̾�Ʈ�� ������ ���䰪�� ������. 
		SendServerResponseMsg(RANKTYPE_BANK, returnval,  0, 0, pclCM->CR[id]->GetCharUnique());

		// [�α��߰� : Ȳ���� 2007. 10. 22] // ���� ������ ����.
		// param1 == Ÿ�� ����� ������,  
		// param2 == ���� ������, 
		// param3 == �ִ� ������ 
		SendLog_WriteLogToDB(LOGCOMMAND_TYPE_BANK, LOGCOMMAND_INDEX_BANK_SET_FEE, 
							 0, NULL, NULL, 0, 0, 0, NULL, 0, 0, 0, pclMsg->siVillageUnique, 0, 0, 
							 pclMsg->clFee.GetFeeRate(),
							 pclMsg->clFee.GetMinFee(), 
							 pclMsg->clFee.GetMaxFee(), 
							 0, 0, NULL, NULL);
	}
}