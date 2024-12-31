//---------------------------------
// 2003/5/29 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Server\Server.h"

#include "..\..\DBManager\GameDBManager_World\DBMsg-Bank.h"
#include "..\CommonLogic\MsgType-Bank.h"
#include "MsgRval-Define.h"

#include "..\CommonLogic\Bank\Bank-Manager.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

// ���¸� �����϶�� ��û.
void cltServer::DoMsg_GAMEMSG_REQUEST_CREATEBANKACCOUNT(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	cltGameMsgRequest_CreateBankAccount* pclInfo = (cltGameMsgRequest_CreateBankAccount*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;

	// [�߰� : Ȳ���� 2008. 1. 7 => �������� 0 �϶� ���� ���� �Ұ�.]
	cltStrInfo* pStrInfo = pclBankManager->GetStrInfo(villageunique);
	if( pStrInfo == NULL )
	{
		return;
	}
	if( 0 == pStrInfo->clCommonInfo.siStrDura ) 
	{
		// [�߰� : Ȳ���� 2008. 1. 9 => �������� 0 �϶� ���� ���� �Ұ�.]
		cltMsg clMsg( GAMEMSG_RESPONSE_CREATEBANKACCOUNT_CANCEL, NULL, NULL );
		pclCM->CR[id]->SendNetMsg((sPacketHeader*)&clMsg);
		return;
	}

	//-----------------------------------
	// DB�� ���¸� ������ ���� ��û�Ѵ�. 
	//-----------------------------------
	sDBRequest_CreateBankAccount clMsg(id, personid, villageunique);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

// ���¸� �����϶�� ��û.
void cltServer::DoMsg_GAMEMSG_REQUEST_CLOSEBANKACCOUNT(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	cltGameMsgRequest_CloseBankAccount* pclInfo = (cltGameMsgRequest_CloseBankAccount*)pclMsg->cData;

	SI32 personid = pclCM->CR[id]->pclCI->GetPersonID();

	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0 || villageunique >= MAX_VILLAGE_NUMBER)return ;

	//---------------------------------
	// DB�� ���¸� ������ ���� ��û�Ѵ�. 
	//----------------------------------
	sDBRequest_CloseBankAccount clMsg(id, personid, villageunique);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}


void cltServer::DoMsg_GAMEMSG_REQUEST_INPUTTOBANK(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	GMONEY fee = 0;

	SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
	{
		return ;
	}

	cltGameMsgRequest_GMoney* pclmoney = (cltGameMsgRequest_GMoney*)pclMsg->cData;
			
	// �Ա��ϵ��� �䱸�Ǵ� �ݾ��� �մ����� Ȯ���Ѵ�. 
	GMONEY money = pclmoney->m_money;
	if(money  <= 0)
	{

		cltMoney clmoney;
		clmoney.Init();
		sDBRequest_InputMoneyToBank clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &clmoney, fee);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

		pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);

		return ;
	}
	if(pclCM->CR[id]->pclCI->clIP.GetMoney() < money)
	{
		SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILINPUTMONEY_OUTOFMONEY, 0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	
	//------------------------------------------
	// �����Ḧ �����Ѵ�. 
	//------------------------------------------		
	if( pclCM->CR[id]->GetCurrentVillageUnique() 
		!= pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique() ) {	


		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
		if(pclinfo == NULL)return ;
		fee = pclinfo->clBankStrInfo.clFee.CalcFee(money);


		if( pclCM->CR[id]->pclCI->clIP.GetMoney() <= money + fee ) {
			SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILINPUTMONEY_NOTENOUGHFEE, 0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	}
	

	//-------------------------------------
	//DB�� �Ա��϶�� �޽����� ������. 
	//-------------------------------------
	cltMoney clmoney;
	clmoney.Set(money);
	sDBRequest_InputMoneyToBank clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &clmoney, fee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);
	
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_GAMEMSG_REQUEST_INPUTTOBANKALLMONEY(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	GMONEY money;

		
	money = pclCM->CR[id]->pclCI->clIP.GetMoney();

	if( money == 0 ) return;

	SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0) return ;

	//------------------------------------------
	// �����Ḧ �����Ѵ�. 
	//------------------------------------------
	GMONEY fee = 0;

	if( pclCM->CR[id]->GetCurrentVillageUnique() 
		!= pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique() ) {	
		
		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
		if(pclinfo == NULL)return ;
		fee = pclinfo->clBankStrInfo.clFee.CalcFee(money);

		money -= fee;

		if( money <= 0 ) {
			SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILINPUTMONEY_NOTENOUGHFEE, 0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	}

	//-------------------------------------
	//DB�� �Ա��϶�� �޽����� ������. 
	//-------------------------------------
	cltMoney clmoney;
	clmoney.Set(money);
	sDBRequest_InputMoneyToBank clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &clmoney, fee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	pclDelMoneyStatistics->Add(DELMONEY_SERVICECHARGE, fee);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_GAMEMSG_REQUEST_OUTPUTFROMBANK(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	SI32 returnval = 0;

	cltGameMsgRequest_GMoney* pclmoney = (cltGameMsgRequest_GMoney*)pclMsg->cData;

	//----------------------------------------------------
	// ����ϵ���  �䱸�Ǵ� �ݾ��� �մ����� Ȯ���Ѵ�. 
	//----------------------------------------------------
	GMONEY money = pclmoney->m_money;
	if(money  <= 0)
	{
		return ;
	}
	// Person�� �ľ��ϰ� �ִ� �ܾ׺��� ū �ݾ��� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBank.GetMoney() < money)
	{
		SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHMONEYINACCOUNT, 0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
	{
		return ;
	}

	//------------------------------------------
	// �����Ḧ �����Ѵ�. 
	//------------------------------------------
	GMONEY fee = 0;


	if( pclCM->CR[id]->GetCurrentVillageUnique() 
		!= pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique() ) {	

		cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
		if(pclinfo == NULL)return ;

		fee = pclinfo->clBankStrInfo.clFee.CalcFee(money);

		if( pclCM->CR[id]->pclCI->clBank.GetMoney() < money + fee ) {
			SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHFEE, 0, 0, pclCM->CR[id]->GetCharUnique());
			return;
		}
	}

	//------------------------------------
	//DB�� ����϶�� �޽����� ������. 
	//------------------------------------
	cltMoney clmoney;
	clmoney.Set(money);
	sDBRequest_OutputMoneyFromBank clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &clmoney, fee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_GAMEMSG_REQUEST_OUTPUTFROMBANKALLMONEY(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	SI32 returnval = 0;

	//----------------------------------------------------
	// ����ϵ���  �䱸�Ǵ� �ݾ��� �մ����� Ȯ���Ѵ�. 
	//----------------------------------------------------

	cltGameMsgRequest_GMoney* pclmoney = (cltGameMsgRequest_GMoney*)pclMsg->cData;

	GMONEY money = pclmoney->m_money;
	if(money  <= 0)
	{
		return ;
	}
	// Person�� �ľ��ϰ� �ִ� �ܾ׺��� ū �ݾ��� ������ �� ����.
	if(pclCM->CR[id]->pclCI->clBank.GetMoney() < money)
	{
		SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHMONEYINACCOUNT, 0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}

	SI32 villageunique  = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique <= 0)
	{
		return ;
	}

	//------------------------------------------
	// �����Ḧ �����Ѵ�. 
	//------------------------------------------
	GMONEY fee = 0;


	if( pclCM->CR[id]->GetCurrentVillageUnique() 
		!= pclCM->CR[id]->pclCI->clBank.clAccountNum.GetVillageUnique() ) {	

			cltStrInfo* pclinfo = pclBankManager->GetStrInfo(villageunique);
			if(pclinfo == NULL)return ;

			fee = pclinfo->clBankStrInfo.clFee.CalcFee(money);

			if( pclCM->CR[id]->pclCI->clBank.GetMoney() < money ) {
				SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILOUTPUTMONEY_NOTENOUGHFEE, 0, 0, pclCM->CR[id]->GetCharUnique());
				return;
			}
		}

		GMONEY requsetMoney = money - fee;
		//------------------------------------
		//DB�� ����϶�� �޽����� ������. 
		//------------------------------------
		cltMoney clmoney;
		clmoney.Set(requsetMoney);
		sDBRequest_OutputMoneyFromBank clMsg(id, pclCM->CR[id]->pclCI->GetPersonID(), villageunique, &clmoney, fee);
		pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

void cltServer::DoMsg_GAMEMSG_REQUEST_SETBANKFEE(cltMsg* pclMsg, SI32 id)
{
//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#ifdef _SERVER
//----------------------------------------------------------------

	SI32 returnval = 0;

	SI32 PersonID = pclCM->CR[id]->pclCI->GetPersonID();
	
	// Person�� ��ġ�� ������ Unique�� ���Ѵ�. 
	SI32 villageunique = pclCM->CR[id]->GetCurrentVillageUnique();
	if(villageunique == 0)return ;
	
	// ������ ������ Ȯ���Ѵ�. 
	cltFee* pclfee = (cltFee*)pclMsg->cData;
	// �����ᰡ �������� Ȯ���Ѵ�. 
	if(pclfee->IsValid(1000) == FALSE)return;
	
	//----------------------------------
	// ��û�ڰ� ����������� Ȯ���Ѵ�. 
	//----------------------------------
	cltSimpleRank clrank(RANKTYPE_BANK, villageunique);
	if(pclRankManager->IsRank(PersonID, &clrank) == FALSE)
	{
		// ��������� �ƴ϶� ������ ������ ����. 
		SendServerResponseMsg(RANKTYPE_BANK, SRVAL_BANK_FAILSETFEE_NOTCHIEF,  0, 0, pclCM->CR[id]->GetCharUnique());
		return ;
	}
	//-----------------------------------
	// DB�� ���� ������ ������. 
	//-----------------------------------
	// DB �� ������.

	sDBRequest_SetBankFee clMsg(id, PersonID, villageunique, pclfee);
	pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

//----------------------------------------------------------------
// ������ ������ ��
//----------------------------------------------------------------
#endif //_SERVER
//----------------------------------------------------------------
}

