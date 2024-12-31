
#include "..\..\Common\CommonHeader.h"
#include "..\..\CommonLogic\CommonLogic.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "..\Server.h"

#include "Minister-Hozo.h"

#include "..\..\CommonLogic\MsgRval-Define.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\CommonLogic\MsgType-System.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"
#include "Char\CharManager\CharManager.h"

extern cltCommonLogic* pclClient;

CMinisterHozo::CMinisterHozo() : CMinisterBase()
{
	m_siResidentNum		= 100;
	m_siMaxShop			= 40;

	m_siTotalCharNum	= 0;
	m_siCalcTime		= 0;

	m_siPrizeMoney		= MIN_HOZO_PRIZEMONEY;
	m_siPrizeSetTime	= 0;
	m_siFixationMoney	= MIN_HOZO_FIXATIONMONEY;

	m_siTutorialVillageDivideend		= Const_Min_Hozo_Dividend_Money;

	m_siBankruptcyVillageNumber		= 0;
	m_siSetBankruptcyVillageDate	= 0;

	ZeroMemory(&m_stHozoAngelList, sizeof(m_stHozoAngelList));
	ZeroMemory(&m_stHozoAngelApplyerList, sizeof(m_stHozoAngelApplyerList));
}

CMinisterHozo::~CMinisterHozo()
{
}

// DB�� ȣ���� ������ ��û�Ѵ�.
void CMinisterHozo::InitializeDB()
{
	// ȣ���� ������ ��û�Ѵ�.
	sDBRequest_GetHozoInfo clMsg;
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	sDBRequest_GetDailyNewChar clMsg2;
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg2);

}

// DB���� ȣ���� ������ ������ ���� Class�� �����Ѵ�.
void  CMinisterHozo::DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_GetHozoInfo* pclMsg = (sDBResponse_GetHozoInfo *)pPacket;

	if(pclMsg->siResult)
	{
		StringCchCopy(m_szAccountID,	MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szAccountID);
		StringCchCopy(m_szPersonName,	MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szPersonName);
		StringCchCopy(m_szGreeting,	256, pclMsg->MinisterBase.m_szGreeting);

		m_siResidentNum =	pclMsg->siResidentNum;
		// �ֹμ��ڴ� 100���� ũ�� 150���� �۴�
		if(m_siResidentNum<100 || m_siResidentNum>150)	m_siResidentNum = 100;

		m_siMaxShop =	pclMsg->siMaxShop;
		// ���� ���� 0���� ũ�� 40���� �۴�
		if(m_siMaxShop<0 || m_siMaxShop>40)	m_siMaxShop = 40;

		m_siTotalCharNum = pclMsg->siTotalCharNum;
		if ( m_siTotalCharNum < 0 ) m_siTotalCharNum = 0 ;

		m_siCalcTime = pclMsg->siCalcTime;
		if ( m_siCalcTime < 0 ) m_siCalcTime = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() ;

		m_siPrizeMoney = pclMsg->siPrizeMoney;
		if ( m_siPrizeMoney < MIN_HOZO_PRIZEMONEY || m_siPrizeMoney > MAX_HOZO_FIXATIONMONEY )
			m_siPrizeMoney = MIN_HOZO_PRIZEMONEY ;

		m_siPrizeSetTime = pclMsg->siPrizeSetTime;
		if ( m_siPrizeSetTime < 0 ) m_siPrizeSetTime = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() ;

		m_siFixationMoney = pclMsg->siFixationMoney;
		if ( m_siFixationMoney < MIN_HOZO_FIXATIONMONEY || m_siFixationMoney > MAX_HOZO_FIXATIONMONEY )
			m_siFixationMoney = MIN_HOZO_FIXATIONMONEY ;

		m_siBankruptcyVillageNumber = pclMsg->siBankruptcyVillageNumber;
		m_siSetBankruptcyVillageDate = pclMsg->siSetBankruptcyVillageDate;

		m_siTutorialVillageDivideend = pclMsg->siTutorialVillageDivideend;
		if ( m_siTutorialVillageDivideend < MIN_HOZO_FIXATIONMONEY || m_siTutorialVillageDivideend > MAX_HOZO_FIXATIONMONEY )
			m_siTutorialVillageDivideend = MIN_HOZO_FIXATIONMONEY ;
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetHozoInfo"));
}

void  CMinisterHozo::DoMsg_DBMsgResponse_GetDailyNewChar(sPacketHeader* pPacket)
{
	sDBResponse_GetDailyNewChar* pclMsg = (sDBResponse_GetDailyNewChar *)pPacket;

	if(pclMsg->siResult)
	{
		cltServer* pclserver = (cltServer*)pclClient ;
		if ( pclserver == NULL ) return ;
		if ( pclMsg->siNewCharNum < 0 ) return ;
		if ( pclMsg->siDelCharNum < 0 ) return ;

		if ( pclserver->siNewCharNum != 0 )
		{
			SI32 difference = pclserver->siNewCharNum - pclMsg->siNewCharNum ;

			if ( difference > 0 ) return ;
		}
		
		if ( pclserver->siDelCharNum != 0 )
		{
			SI32 difference = pclserver->siDelCharNum - pclMsg->siDelCharNum ;

			if ( difference > 0 ) return ;
		}

		pclserver->siNewCharNum = pclMsg->siNewCharNum ;
		pclserver->siDelCharNum = pclMsg->siDelCharNum ;
	}
}

// Client���� ȣ���� ������ ��û�ϸ� ���� Class�� �ִ� ������ �����Ѵ�.
void CMinisterHozo::DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID)
{
	CMinisterBase *pMinister = (CMinisterBase* )(this);
	cltServer* pclserver = (cltServer*)pclClient ;
	if ( pclserver == NULL ) return ;

	SI32 newtotalchar = pclserver->siTotalNewCharNum - pclserver->siTotalDelCharNum ;
	SI32 newserverchar = pclserver->siServerNewCharNum - pclserver->siServerDelCharNum ;
	SI32 newcharrate = 0 ;
	if ( newserverchar > 0 && newtotalchar > 0 )
		newcharrate = ( newserverchar * 100 ) / newtotalchar  ;

	cltGameMsgResponse_GetHozoInfo clinfo(pMinister, m_siResidentNum,m_siMaxShop,m_siTotalCharNum,m_siCalcTime,
										  m_siPrizeMoney,m_siPrizeSetTime,m_siFixationMoney,newcharrate,
										  m_siBankruptcyVillageNumber, m_siSetBankruptcyVillageDate,
										  m_siTutorialVillageDivideend );

	cltMsg clMsg(GAMEMSG_RESPONSE_GETHOZOINFO, sizeof(clinfo), (BYTE*)&clinfo);
	pclserver->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);

}

// Client���� ȣ���� ���� ���� �����ϱ⸦ ���ϸ� ���������� DB�� ���� ������ ��û�Ѵ�.
void CMinisterHozo::DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID)
{
	cltGameMsgRequest_SetHozoInfo *pclinfo = (cltGameMsgRequest_SetHozoInfo*)pclMsg->cData;
	
	SI32 curdate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary();
	if(m_siPrizeSetTime + 30 >  curdate)return ;

	if ( TABS(m_siPrizeMoney-pclinfo->siPrizeMoney) > 1 || pclinfo->siPrizeMoney < MIN_HOZO_PRIZEMONEY ) return ;
	if ( pclinfo->siPrizeMoney < MIN_HOZO_PRIZEMONEY || pclinfo->siPrizeMoney > MAX_HOZO_FIXATIONMONEY ) return ;
	if ( pclinfo->siFixationMoney < MIN_HOZO_FIXATIONMONEY || pclinfo->siFixationMoney > MAX_HOZO_FIXATIONMONEY ) return ;

	sDBRequest_SetHozoInfo clMsg(siID, ((cltServer *)pclClient)->pclCM->CR[siID]->pclCI->GetPersonID(),
		pclinfo->szGreeting, pclinfo->siResidentNum,pclinfo->siMaxShop,
		pclinfo->siPrizeMoney,curdate,pclinfo->siFixationMoney,
		pclinfo->siTutorialVillageDivideend);

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// DB���� ������ ���Ⱑ �Ϸ�Ǹ� Client���� �ٽ� �����Ͽ��ش�.
void CMinisterHozo::DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_SetHozoInfo* pclMsg = (sDBResponse_SetHozoInfo*)pPacket;
	SI32 id = pclMsg->usCharID;

	if(((cltServer *)pclClient)->pclCM->IsAlive(id) == false)return ;

	if(pclMsg->siResult == 1)
	{
		// �������̶�� 
		if(((cltServer *)pclClient)->pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
		{
			StringCchCopy(m_szAccountID,	MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szAccountID);
			StringCchCopy(m_szPersonName,	MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szPersonName);
			StringCchCopy(m_szGreeting,	256, pclMsg->MinisterBase.m_szGreeting);
			
			m_siResidentNum		= pclMsg->siResidentNum;
			// �ֹμ��ڴ� 100���� ũ�� 150���� �۴�
			if(m_siResidentNum<100 || m_siResidentNum>150)	m_siResidentNum = 100;

			m_siMaxShop =	pclMsg->siMaxShop;
			// ���� ���� 0���� ũ�� 40���� �۴�
			if(m_siMaxShop<0 || m_siMaxShop>50)	m_siMaxShop = 40;

			m_siPrizeMoney = pclMsg->siPrizeMoney;
			if ( m_siPrizeMoney < MIN_HOZO_PRIZEMONEY || m_siPrizeMoney > MAX_HOZO_FIXATIONMONEY )
				m_siPrizeMoney = MIN_HOZO_PRIZEMONEY ;

			m_siPrizeSetTime = pclMsg->siPrizeSetTime;
			if ( m_siPrizeSetTime < 0 ) m_siPrizeSetTime = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() ;

			m_siFixationMoney = pclMsg->siFixationMoney;
			if ( m_siFixationMoney < MIN_HOZO_FIXATIONMONEY || m_siFixationMoney > MAX_HOZO_FIXATIONMONEY )
				m_siFixationMoney = MIN_HOZO_FIXATIONMONEY ;

			m_siTutorialVillageDivideend = pclMsg->siTutorialVillageDivideend;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 4] // ȣ�� ����
				// param1 == �ֹμ�,	param2 == ���� �ִ� ������, param3 == �����, 
				// param4 == ���� �ð�. param5 == �ű� ���� ���� ������(10�� ���� 1 = 100000 )
				cltServer* pclserver = (cltServer*)pclClient;
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_HOZO_SET, 
					0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					pclMsg->siResidentNum, pclMsg->siMaxShop, pclMsg->siPrizeMoney, pclMsg->siPrizeSetTime, pclMsg->siFixationMoney, 
					pclMsg->MinisterBase.m_szAccountID, pclMsg->MinisterBase.m_szPersonName);
			}
		}
	}
	else
	{
		// ���� Error
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETHOZOINFO,  0, 0, id);
	}
	
	// ������ ��û�������� ���� �����ش�.
	DoMsg_GameMsgRequest_GetMinisterInfo(id);

}

// ��ȣõ�� ������ ��� ��û ���� - DB�� �о�� ��
void CMinisterHozo::DoMsg_DBMsgResponse_GetAngelApplyerList(sPacketHeader* pPacket)
{
	sDBResponse_GetAngelApplyerList* pclMsg = (sDBResponse_GetAngelApplyerList *)pPacket;

	if(pclMsg->siResult)
	{
		for ( int i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
		{
			memcpy(m_stHozoAngelApplyerList[i].szAccountID,pclMsg->stHozoAngelApplyerList[i].szAccountID,32);
			memcpy(m_stHozoAngelApplyerList[i].szName,pclMsg->stHozoAngelApplyerList[i].szName,MAX_PLAYER_NAME);

			m_stHozoAngelApplyerList[i].siLevel = pclMsg->stHozoAngelApplyerList[i].siLevel ;
			m_stHozoAngelApplyerList[i].siFameLevel = pclMsg->stHozoAngelApplyerList[i].siFameLevel ;

			m_stHozoAngelApplyerList[i].siPersonID = pclMsg->stHozoAngelApplyerList[i].siPersonID ;
		}
	}
}

// ��ȣõ�� ��� ��û ���� - DB�� �о�� ��
void CMinisterHozo::DoMsg_DBMsgResponse_GetAngelList(sPacketHeader* pPacket)
{
	sDBResponse_GetAngelList* pclMsg = (sDBResponse_GetAngelList*)pPacket;

	if(pclMsg->siResult)
	{
		for ( int i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
		{
			memcpy(m_stHozoAngelList[i].szAccountID,pclMsg->stHozoAngelList[i].szAccountID,32);
			memcpy(m_stHozoAngelList[i].szName,pclMsg->stHozoAngelList[i].szName,MAX_PLAYER_NAME);

			m_stHozoAngelList[i].siLevel = pclMsg->stHozoAngelList[i].siLevel ;
			m_stHozoAngelList[i].siFameLevel = pclMsg->stHozoAngelList[i].siFameLevel ;

			m_stHozoAngelList[i].siPersonID = pclMsg->stHozoAngelList[i].siPersonID ;
		}
	}
}

// Server&Client
// ��ȣõ�� ������ ��� ��û - ������ ������ �����ش�.
void CMinisterHozo::DoMsg_GameMsgRequest_GetAngelApplyerList(cltMsg* pclMsg, SI32 siID)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	cltGameMsgResponse_GetAngelApplyerList clinfo(1, &m_stHozoAngelApplyerList[0]);
	cltMsg clMsg(GAMEMSG_RESPONSE_GETANGELAPPLYERLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclServer->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
}

// ��ȣõ�� ��� ��û - ������ ������ �����ش�.
void CMinisterHozo::DoMsg_GameMsgRequest_GetAngelList(cltMsg* pclMsg, SI32 siID)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	cltGameMsgResponse_GetAngelList clinfo(1, &m_stHozoAngelList[0]);
	cltMsg clMsg(GAMEMSG_RESPONSE_GETANGELLIST, sizeof(clinfo), (BYTE*)&clinfo);
	pclServer->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
}

// ��ȣõ�� ��Ͻ�û �� ��û�� ����
void CMinisterHozo::DoMsg_GameMsgRequest_SetAngelApplyer(cltMsg* pclMsg, SI32 siID)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	cltGameMsgRequest_SetAngelApplyer * pclinfo = (cltGameMsgRequest_SetAngelApplyer*)pclMsg->cData ;

	SI32 personid = 0 ;

	if ( pclinfo->bAdmin == false && pclinfo->siIndex != -1 ) // �����Ǽ��� ����
	{
		if ( pclinfo->siIndex < 0 || pclinfo->siIndex > MAX_HOZO_ANGELLIST ) return ;
		if ( pclServer->pclCM->CR[siID]->pclCI->clBI.uiGRank != GRANK_MINISTER2 ) return ;

		personid = m_stHozoAngelApplyerList[pclinfo->siIndex].siPersonID ;
	}
	else // ��û�̳� ������ Ż��
	{
		personid = pclServer->pclCM->CR[siID]->pclCI->GetPersonID() ;

		if ( pclinfo->bAdmin == false ) // ������ Ż���
		{
			if ( IsValidApplyerFromPersonID(personid) == false ) // ��û�ڰ� �³� �� �³�
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_FAIL_SETANGELAPPLYER_FALSE, 0, 0, siID );
				return ;
			}
		}
		else // ��û��
		{
			if ( IsValidApplyerFromPersonID(personid) == true ) // �̹� ��û�ߴ��� �� �ߴ���
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_FAIL_SETANGELAPPLYER, 0, 0, siID );
				return ;
			}
		}
	}

	if ( personid <= 0 ) return ;

	sDBRequest_SetAngelApplyer clMsg(siID,personid,pclinfo->bAdmin) ;
	pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
	return ;
}

//��ȣõ�� �Ӹ� �� ����
void CMinisterHozo::DoMsg_GameMsgRequest_SetAngel(cltMsg* pclMsg, SI32 siID)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	cltGameMsgRequest_SetAngel * pclinfo = (cltGameMsgRequest_SetAngel*)pclMsg->cData ;

	SI32 personid = 0 ;
	if ( pclinfo->bAdmin )
	{
		if ( pclServer->pclCM->CR[siID]->pclCI->clBI.uiGRank != GRANK_MINISTER2 ) return ;
		if ( pclinfo->siIndex < 0 || pclinfo->siIndex > MAX_HOZO_ANGELLIST ) return ;
		if ( !_tcscmp(m_stHozoAngelApplyerList[pclinfo->siIndex].szName, TEXT("")) ) return ;
		if ( m_stHozoAngelApplyerList[pclinfo->siIndex].siLevel <= 0 ) return ;

		personid = m_stHozoAngelApplyerList[pclinfo->siIndex].siPersonID ;
	}
	else
	{
		if ( pclServer->pclCM->CR[siID]->pclCI->clBI.uiGRank == GRANK_MINISTER2 )
		{
			if ( pclinfo->siIndex < 0 || pclinfo->siIndex > MAX_HOZO_ANGELLIST ) return ;
			if ( !_tcscmp(m_stHozoAngelList[pclinfo->siIndex].szName, TEXT("")) ) return ;
			if ( m_stHozoAngelList[pclinfo->siIndex].siLevel <= 0 ) return ;

			personid = m_stHozoAngelList[pclinfo->siIndex].siPersonID ;
		}
		else if ( pclServer->pclCM->CR[siID]->pclCI->clBI.uiAngelSwitch && pclinfo->siIndex == -1 )
		{
			personid = pclServer->pclCM->CR[siID]->pclCI->GetPersonID();
		}
	}

	if ( personid <= 0 ) return ;

	sDBRequest_SetAngel clMsg(siID,personid,pclinfo->bAdmin) ;
	pclServer->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
	return ;
}

// Server&DB
// ��ȣõ�� ���� ����
void CMinisterHozo::DoMsg_DBMsgResponse_SetAngelApplyer(sPacketHeader* pPacket)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	sDBResponse_SetAngelApplyer* pclMsg = (sDBResponse_SetAngelApplyer *)pPacket;

	if(pclMsg->siResult == 1)
	{
		if ( pclMsg->bAdmin ) // ���
		{
			SI32 index = pclMsg->siIndex ;

			m_stHozoAngelApplyerList[index].siPersonID = pclMsg->stHozoAngelApplyer.siPersonID ;
			m_stHozoAngelApplyerList[index].siFameLevel = pclMsg->stHozoAngelApplyer.siFameLevel ;
			m_stHozoAngelApplyerList[index].siLevel = pclMsg->stHozoAngelApplyer.siLevel ;
			StringCchCopy(m_stHozoAngelApplyerList[index].szAccountID, 32,pclMsg->stHozoAngelApplyer.szAccountID);
			StringCchCopy(m_stHozoAngelApplyerList[index].szName, MAX_PLAYER_NAME, pclMsg->stHozoAngelApplyer.szName);

			if ( pclServer->pclCM->GetIDFromPersonID(pclMsg->siPersonID) == pclMsg->usCharID &&
				pclServer->pclCM->IsValidID(pclMsg->usCharID) == true )
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_SUCCESS_SETANGELAPPLYER, 0, 0, pclMsg->usCharID );
			}
		}
		else // ����
		{
			SI32 index = pclMsg->siIndex ;

			SI32 deletepersonid = m_stHozoAngelApplyerList[index].siPersonID ;

			m_stHozoAngelApplyerList[index].siPersonID = 0 ;
			m_stHozoAngelApplyerList[index].siFameLevel = 0 ;
			m_stHozoAngelApplyerList[index].siLevel = 0 ;
			StringCchCopy(m_stHozoAngelApplyerList[index].szAccountID, 32, TEXT(""));
			StringCchCopy(m_stHozoAngelApplyerList[index].szName, MAX_PLAYER_NAME, TEXT(""));

			if ( pclServer->pclCM->CR[pclMsg->usCharID]->pclCI->clBI.uiGRank == GRANK_MINISTER2 &&
				pclServer->pclCM->IsValidID(pclMsg->usCharID) )
			{
				cltGameMsgResponse_SetAngelApplyer clinfo(pclMsg->bAdmin,pclMsg->bAdmin,index);
				cltMsg clMsg(GAMEMSG_RESPONSE_SETANGELAPPLYER, sizeof(clinfo), (BYTE*)&clinfo);
				pclServer->pclCM->CR[pclMsg->usCharID]->SendNetMsg((sPacketHeader*)&clMsg);

				if ( deletepersonid )
				{
					cltLetterMsg_HozoAngel clletter(3, &pclServer->pclTime->clDate);
					pclServer->SendLetterMsg(deletepersonid, (cltLetterHeader*)&clletter);
				}
			}
			else if ( pclServer->pclCM->GetIDFromPersonID(pclMsg->siPersonID) == pclMsg->usCharID &&
				pclServer->pclCM->IsValidID(pclMsg->usCharID) )
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_SUCCESS_SETANGELAPPLYER_FALSE, 0, 0, pclMsg->usCharID );
			}
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȣõ���û
			// param1 == ���/����, param2 == �ε���, param3 == ����, param4 == �� ����
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_ANGEL_APPLY_SET, 
				0, (cltCharServer*)pclClient->pclCM->CR[pclMsg->usCharID], NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclMsg->bAdmin, pclMsg->siIndex, pclMsg->stHozoAngelApplyer.siLevel, pclMsg->stHozoAngelApplyer.siFameLevel, 0, 
				NULL, NULL);
		}
	}
	else if ( pclServer->pclCM->IsValidID(pclMsg->usCharID) )
	{
		pclServer->SendServerResponseMsg(0, SRVAL_HOZO_FAIL_SETANGELAPPLYER, 0, 0, pclMsg->usCharID );
	}
}

// ��ȣõ�� �Ӹ� ����
void CMinisterHozo::DoMsg_DBMsgResponse_SetAngel(sPacketHeader* pPacket)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return ;

	sDBResponse_SetAngel* pclMsg = (sDBResponse_SetAngel *)pPacket;

	SI32 index = -1 ;

	if(pclMsg->siResult == 1)
	{
		if ( pclMsg->bAdmin ) // �Ӹ�
		{
			index = pclMsg->siIndex ;

			m_stHozoAngelList[index].siPersonID = pclMsg->stHozoAngel.siPersonID ;
			m_stHozoAngelList[index].siFameLevel = pclMsg->stHozoAngel.siFameLevel ;
			m_stHozoAngelList[index].siLevel = pclMsg->stHozoAngel.siLevel ;
			StringCchCopy(m_stHozoAngelList[index].szAccountID, 32, pclMsg->stHozoAngel.szAccountID);
			StringCchCopy(m_stHozoAngelList[index].szName, MAX_PLAYER_NAME, pclMsg->stHozoAngel.szName);

			for ( int i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
			{
				if ( m_stHozoAngelApplyerList[i].siPersonID == pclMsg->stHozoAngel.siPersonID )
				{
					m_stHozoAngelApplyerList[i].siPersonID = 0 ;
					m_stHozoAngelApplyerList[i].siFameLevel = 0 ;
					m_stHozoAngelApplyerList[i].siLevel = 0 ;
					StringCchCopy(m_stHozoAngelApplyerList[i].szAccountID, 32, TEXT(""));
					StringCchCopy(m_stHozoAngelApplyerList[i].szName, MAX_PLAYER_NAME, TEXT(""));
					break;
				}
			}

			if ( pclServer->pclCM->GetIDFromPersonID(pclMsg->siPersonID) == pclMsg->usCharID )
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_SUCCESS_SETANGEL, 0, 0, pclMsg->usCharID );
			}

			if ( m_stHozoAngelList[index].siPersonID )
			{
				cltLetterMsg_HozoAngel clletter(1, &pclServer->pclTime->clDate);
				pclServer->SendLetterMsg(m_stHozoAngelList[index].siPersonID, (cltLetterHeader*)&clletter);

				SI32 toid = pclServer->pclCM->GetIDFromPersonID(m_stHozoAngelList[index].siPersonID) ;
				if ( IsPC(toid) )
				{
					pclServer->pclCM->CR[toid]->SetAngel(true);
				}
			}
		}
		else // �����̳� Ż��
		{
			index = pclMsg->siIndex ;

			if ( m_stHozoAngelList[index].siPersonID &&
				m_stHozoAngelList[index].siPersonID != pclMsg->siPersonID )
			{
				cltLetterMsg_HozoAngel clletter(2, &pclServer->pclTime->clDate);
				pclServer->SendLetterMsg(m_stHozoAngelList[index].siPersonID, (cltLetterHeader*)&clletter);

				SI32 toid = pclServer->pclCM->GetIDFromPersonID(m_stHozoAngelList[index].siPersonID) ;
				if ( IsPC(toid) )
				{
					pclServer->pclCM->CR[toid]->SetAngel(false);
				}
			}
			else if ( m_stHozoAngelList[index].siPersonID &&
				m_stHozoAngelList[index].siPersonID == pclMsg->siPersonID )
			{
				SI32 toid = pclServer->pclCM->GetIDFromPersonID(m_stHozoAngelList[index].siPersonID) ;
				if ( IsPC(toid) )
				{
					pclServer->pclCM->CR[toid]->SetAngel(false);
					pclServer->SendServerResponseMsg(0, SRVAL_HOZO_SUCCESS_SETANGEL_FALSE_SELF, 0, 0, toid );
				}
			}
			if ( pclServer->pclCM->GetIDFromPersonID(pclMsg->siPersonID) == pclMsg->usCharID &&
				pclServer->pclCM->CR[pclMsg->usCharID]->pclCI->clBI.uiGRank == GRANK_MINISTER2 )
			{
				pclServer->SendServerResponseMsg(0, SRVAL_HOZO_SUCCESS_SETANGELADMIN_FALSE, 0, 0, pclMsg->usCharID );
			}

			m_stHozoAngelList[index].siPersonID = 0 ;
			m_stHozoAngelList[index].siFameLevel = 0 ;
			m_stHozoAngelList[index].siLevel = 0 ;
			StringCchCopy(m_stHozoAngelList[index].szAccountID, 32, TEXT(""));
			StringCchCopy(m_stHozoAngelList[index].szName, MAX_PLAYER_NAME, TEXT(""));
		}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
		{
			// [�α��߰� : Ȳ���� 2007. 10. 10] // ��ȣõ�� �Ӹ�� ����.
			// param1	 == ������ ĳ���� �ε���, 
			// param2	 == ����,	
			// param3	 == ������, 
			// pszParam1 == ����,				  pszParam2 == �̸�.
			cltServer * pclserver = (cltServer*)pclClient;
			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_ANGEL_SET, 
				0, (cltCharServer*)pclClient->pclCM->CR[pclMsg->usCharID], NULL, pclMsg->stHozoAngel.siPersonID, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclMsg->bAdmin, pclMsg->siIndex, pclMsg->stHozoAngel.siLevel, pclMsg->stHozoAngel.siFameLevel, 0, 
				pclMsg->stHozoAngel.szAccountID, pclMsg->stHozoAngel.szName);
		}
	}

	if ( pclServer->pclCM->IsValidID(pclMsg->usCharID) == false ) return ;

	cltGameMsgResponse_SetAngel clinfo(pclMsg->bAdmin,index,pclMsg->bAdmin);
	cltMsg clMsg(GAMEMSG_RESPONSE_SETANGEL, sizeof(clinfo), (BYTE*)&clinfo);
	pclServer->pclCM->CR[pclMsg->usCharID]->SendNetMsg((sPacketHeader*)&clMsg);
}

bool CMinisterHozo::IsValidAngelFromPersonID(SI32 personid)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( personid <= 0 ) return false ;

	for ( SI32 i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
	{
		if ( m_stHozoAngelList[i].siPersonID == personid )
			return true ;
	}

	return false  ;
}

bool CMinisterHozo::IsValidAngelFromCharID(SI32 charid)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( pclServer->pclCM->GetIDFromCharUnique(charid) != charid ) return false ;
	if ( IsPC(pclServer->pclCM->CR[charid]->GetCharUnique()) == false ) return false ;

	SI32 personid = pclServer->pclCM->CR[charid]->pclCI->GetPersonID() ;

	if ( personid <= 0 ) return false ;

	return IsValidAngelFromPersonID(personid) ;
}

bool CMinisterHozo::IsValidAngelFromCharName(const TCHAR * name)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( !_tcscmp(TEXT(""),name) || name == NULL ) return false ;

	for ( SI32 i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
	{
		if ( !_tcscmp(m_stHozoAngelList[i].szName,name) )
		{
			return true ;
		}
	}

	return false ;
}

bool CMinisterHozo::IsValidApplyerFromPersonID(SI32 personid)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( personid <= 0 ) return false ;

	for ( SI32 i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
	{
		if ( m_stHozoAngelApplyerList[i].siPersonID == personid )
			return true ;
	}

	return false  ;
}

bool CMinisterHozo::IsValidApplyerFromFromCharID(SI32 charid)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( pclServer->pclCM->GetIDFromCharUnique(charid) != charid ) return false ;
	if ( IsPC(pclServer->pclCM->CR[charid]->GetCharUnique()) == false ) return false ;

	SI32 personid = pclServer->pclCM->CR[charid]->pclCI->GetPersonID() ;

	if ( personid <= 0 ) return false ;

	return IsValidApplyerFromPersonID(personid) ;
}

bool CMinisterHozo::IsValidApplyerFromFromCharName(const TCHAR * name)
{
	cltServer* pclServer = ((cltServer *)pclClient) ;
	if ( pclServer == NULL ) return false ;
	if ( !_tcscmp(TEXT(""),name) || name == NULL ) return false ;

	for ( SI32 i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
	{
		if ( !_tcscmp(m_stHozoAngelApplyerList[i].szName,name) )
		{
			return true ;
		}
	}

	return false ;
}

SI32 CMinisterHozo::GetAngelNumber()
{
	SI32 count = 0 ;
	for ( SI32 i = 0 ; i < MAX_HOZO_ANGELLIST ; i ++ )
	{
		if ( m_stHozoAngelApplyerList[i].siPersonID > 0 )
		{
			count ++ ;
		}
	}

	return count ;
}
