
#include "Char\CharManager\CharManager.h"

#include "..\..\CommonLogic\CommonLogic.h"
#include "..\Server.h"

#include "MinisterBase.h"
#include "Minister-Byungzo.h"

#include "..\..\CommonLogic\MsgRval-Define.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\CommonLogic\MsgType-System.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"

extern cltCommonLogic* pclClient;

CMinisterByungzo::CMinisterByungzo() : CMinisterBase()
{

	m_siVillageWarTime = 40;

	m_siPersonID = 0;
	m_siSetTime = 0;
	m_siWarStartTime = 0;
	m_siSetWarCount = 0;
	m_siBlackArmyNum = 600;

}



CMinisterByungzo::~CMinisterByungzo()
{

}


// DB�� ������ ������ ��û�Ѵ�.
void CMinisterByungzo::InitializeDB()
{

	// ������ ������ ��û�Ѵ�.
	sDBRequest_GetByungzoInfo clMsg;
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

// DB���� ������ ������ ������ ���� Class�� �����Ѵ�.
void  CMinisterByungzo::DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket)
{

	sDBResponse_GetByungzoInfo* pclMsg = (sDBResponse_GetByungzoInfo *)pPacket;

	if(pclMsg->siResult)
	{
		StringCchCopy(m_szAccountID, MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szAccountID);
		StringCchCopy(m_szPersonName, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szPersonName);
		StringCchCopy(m_szGreeting, 256, pclMsg->MinisterBase.m_szGreeting);

		m_siVillageWarTime =	pclMsg->siVillageWarTime;

		// �����ð���  40�к��� ������ ���� 60�� ���� Ŭ�� ����.
		if(m_siVillageWarTime<40 || m_siVillageWarTime>60)	m_siVillageWarTime = 40;

		((cltServer *)pclClient)->dwVillageWarTimeMin	= m_siVillageWarTime;
		((cltServer *)pclClient)->dwVillageWarFinishMin	= ((cltServer *)pclClient)->dwVillageWarStartMin + ((cltServer *)pclClient)->dwVillageWarTimeMin;

		m_siPersonID = pclMsg->siPersonID;
		m_siSetTime = pclMsg->siSetTime;
		m_siWarStartTime = pclMsg->siWarStartTime;
		m_siSetWarCount = pclMsg->siSetWarCount;
		m_siBlackArmyNum = pclMsg->siBlackArmyNum;
        		
        if ( m_siBlackArmyNum< 100 || m_siBlackArmyNum > 600 )
			m_siBlackArmyNum = 600 ;

		// ���Ǳ��� ����ð��� üũ�Ͽ� ��ȿ�� �ð��� �ƴϸ�, �����Ѵ�.
		SYSTEMTIME stServerTime;
		memcpy(&stServerTime, &((cltServer *)pclClient)->sTime, sizeof(stServerTime));
		SYSTEMTIME stWarStartTime = pclClient->GetTimeFromsMinute(m_siWarStartTime);

		// ������۽ð��� ���� �ð����� �����̸�,
		if( TimeCompare(&stWarStartTime, &stServerTime) < 0 )
		{
			// ������۽ð� �ʱ�ȭ
			m_siWarStartTime = 0;

			// DB�� ��ȣ�� ����
			SI32 siID = 0;
			sDBRequest_SetByungzoInfo clMsg(siID, m_siPersonID,
											m_szGreeting, m_siVillageWarTime, m_siSetTime, m_siWarStartTime, 
											m_siSetWarCount, m_siBlackArmyNum);
			((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
		}
	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetByungzoInfo"));
}

// Client���� ������ ������ ��û�ϸ� ���� Class�� �ִ� ������ �����Ѵ�.
void CMinisterByungzo::DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID)
{
	CMinisterBase *pMinister = (CMinisterBase* )(this);
	cltGameMsgResponse_GetByungzoInfo clinfo(pMinister, m_siVillageWarTime, 
			m_siSetTime, m_siWarStartTime, m_siSetWarCount, m_siBlackArmyNum);

	cltMsg clMsg(GAMEMSG_RESPONSE_GETBYUNGZOINFO, sizeof(clinfo), (BYTE*)&clinfo);
	((cltServer *)pclClient)->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
}

// Client���� ������ ���� ���� �����ϱ⸦ ���ϸ� ���������� DB�� ���� ������ ��û�Ѵ�.
void CMinisterByungzo::DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID)
{
	cltGameMsgRequest_SetByungzoInfo *pclinfo = (cltGameMsgRequest_SetByungzoInfo*)pclMsg->cData;

	cltServer *pclserver = (cltServer*)pclClient;

	if (m_siSetWarCount >= MAX_SETWARCOUNT)
		return;

	SI32 settime = pclClient->GetMinuteFromsTime( pclserver->sTime );
	
	sDBRequest_SetByungzoInfo clMsg(siID, ((cltServer *)pclClient)->pclCM->CR[siID]->pclCI->GetPersonID(),
		pclinfo->szGreeting, pclinfo->siVillageWarTime , settime, pclinfo->siWarStartTime, 
		pclinfo->siSetWarCount, pclinfo->siBlackArmyNum);

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
}

// DB���� ������ ���Ⱑ �Ϸ�Ǹ� Client���� �ٽ� �����Ͽ��ش�.
void CMinisterByungzo::DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_SetByungzoInfo* pclMsg = (sDBResponse_SetByungzoInfo*)pPacket;

	SI32 id = pclMsg->usCharID;

	if(pclMsg->siResult == 1)
	{

		//û����� ������ ������ ������ warstarttime�� �ʱ�ȭ�ǰ� setwarcount�� �ϳ� �����Ѵ�
		//�׷��� �������� ���� ������ �ٲٴ°��̱� ������ siID���� 0���� ����
		//�׸��Ͽ� �Ʒ��� ID�� �˻��ϴºκ��� �ּ�ó��

		//// �������̶�� 
		//if(((cltServer *)pclClient)->pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
		//{
			StringCchCopy(m_szAccountID, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szAccountID);
			StringCchCopy(m_szPersonName, MAX_PLAYER_NAME,	pclMsg->MinisterBase.m_szPersonName);
			StringCchCopy(m_szGreeting, 256,	pclMsg->MinisterBase.m_szGreeting);
			
			// �����ð��� 20�к��� ������ ���� 60�� ���� Ŭ�� ����.
			if(m_siVillageWarTime<40 || m_siVillageWarTime>60)	m_siVillageWarTime = 40;

			m_siVillageWarTime		= pclMsg->siVillageWarTime;
			((cltServer *)pclClient)->dwVillageWarTimeMin	= m_siVillageWarTime;
			((cltServer *)pclClient)->dwVillageWarFinishMin	= ((cltServer *)pclClient)->dwVillageWarStartMin + ((cltServer *)pclClient)->dwVillageWarTimeMin;

			m_siPersonID = pclMsg->siPersonID;
			m_siSetTime = pclMsg->siSetTime;
			m_siWarStartTime = pclMsg->siWarStartTime;
			m_siSetWarCount = pclMsg->siSetWarCount;
			m_siBlackArmyNum = pclMsg->siBlackArmyNum;
			m_siPersonID = pclMsg->siPersonID;
		//}

		if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog))
		{
			// [�α��߰� : Ȳ���� 2007. 10. 4] // ��������.
			// param1		 == ���Ｓ�� Ƚ��, 
			// param2		 == ���� ���� ��, 
			// param3		 == ����ð�, 
			// pszCharParam1 == ���Ｓ���ð�
			// pszCharParam2 == ������۽ð�
			cltServer * pclserver = (cltServer*)pclClient;
			cltCharServer* pclchar = NULL;
			if(pclClient->pclCM->IsValidID(id))			pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

			_SYSTEMTIME SetTime;
			_SYSTEMTIME WarStartTime;
			SetTime		 = pclClient->GetTimeFromsMinute(pclMsg->siSetTime);
			WarStartTime = pclClient->GetTimeFromsMinute(pclMsg->siWarStartTime);

			TCHAR	pszCharParam1[50] = {'\0', };
			TCHAR	pszCharParam2[50] = {'\0', };
			StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "%d-%d-%d", 
				SetTime.wYear,
				SetTime.wMonth,
				SetTime.wDay	);
			StringCchPrintf(pszCharParam1, sizeof(pszCharParam1), "%d-%d-%d", 
				WarStartTime.wYear,
				WarStartTime.wMonth,
				WarStartTime.wDay	);

			pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_BYUNGZO_SET, 
				0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
				pclMsg->siSetWarCount, pclMsg->siBlackArmyNum, pclMsg->siVillageWarTime, 0, 0,
				pszCharParam1, pszCharParam2);
		}
	}
	else
	{
		if(((cltServer *)pclClient)->pclCM->IsAlive(id) == false)return ;

		// ���� Error
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETBYUNGZOINFO,  0, 0, id);
	}

	if (pclClient->pclCM->IsValidID(id))
	{
		// ������ ��û�������� ���� �����ش�.
		DoMsg_GameMsgRequest_GetMinisterInfo(id);
	}

}
