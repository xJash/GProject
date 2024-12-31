
#include "..\..\Common\CommonHeader.h"
#include "..\..\CommonLogic\CommonLogic.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "..\Server.h"

#include "Minister-Hozo.h"

#include "Minister-Goonzu.h"

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

CMinisterGoonzu::CMinisterGoonzu() : CMinisterBase()
{
	m_iTempFinances = 0 ;
	m_iTotalFinances = 0 ;
	
	m_siBonusTime = 0;
	m_siMakeBonusTime = 0;
	m_siLastChangedBonusTimeYear = 0;
	m_siLastChangedBonusTimeMonth = 0;
	m_siLastChangedBonusTimeDay = 0;

	for ( SI32 i = 0 ; i < 6 ; i ++ )
	{
		m_siSetMinisterTime[i] = 0 ;
	}
}

CMinisterGoonzu::~CMinisterGoonzu()
{
}

// DB�� ������ ������ ��û�Ѵ�.
void CMinisterGoonzu::InitializeDB()
{
	// ������ ������ ��û�Ѵ�.
	sDBRequest_GetGoonzuInfo clMsg;
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// DB���� ������ ������ ������ ���� Class�� �����Ѵ�.
void  CMinisterGoonzu::DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_GetGoonzuInfo* pclMsg = (sDBResponse_GetGoonzuInfo *)pPacket;

	if(pclMsg->siResult)
	{
		StringCchCopy(m_szAccountID, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szAccountID);
		StringCchCopy(m_szPersonName, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szPersonName);
		StringCchCopy(m_szGreeting,	 256, pclMsg->MinisterBase.m_szGreeting);

		m_iTotalFinances = pclMsg->iTotalFinances ;
		if ( m_iTotalFinances < 0 ) m_iTotalFinances = 0 ;

		for ( SI32 i = 0 ; i < 6 ; i ++ )
		{
			m_siSetMinisterTime[i] = pclMsg->siSetMinisterTime[i] ;
		}

		m_siLiquidationVillageNumber = pclMsg->siLiquidationVillageNumber;

		m_siBonusTime	= pclMsg->siBonusTime;
		m_siMakeBonusTime = pclMsg->siMakeBonusTime;
		m_siLastChangedBonusTimeYear = pclMsg->siLastChangedBonusTimeYear;
		m_siLastChangedBonusTimeMonth = pclMsg->siLastChangedBonusTimeMonth;
		m_siLastChangedBonusTimeDay = pclMsg->siLastChangedBonusTimeDay;
	}
	//�ֱ������� ������ �Ŷ� ����
	//pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetGoonzuInfo"));
}

// Client���� ������ ������ ��û�ϸ� ���� Class�� �ִ� ������ �����Ѵ�.
void CMinisterGoonzu::DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID)
{
	CMinisterBase *pMinister = (CMinisterBase* )(this);

	cltGameMsgResponse_GetGoonzuInfo clinfo(pMinister,  GetTotalFinances(), GetLiquidationVillageNumber() );
	cltMsg clMsg(GAMEMSG_RESPONSE_GETGOONZUINFO, sizeof(clinfo), (BYTE*)&clinfo);
	((cltServer *)pclClient)->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);
}

// Client���� ������ ���� ���� �����ϱ⸦ ���ϸ� ���������� DB�� ���� ������ ��û�Ѵ�.
void CMinisterGoonzu::DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID)
{
	cltGameMsgRequest_SetGoonzuInfo *pclinfo = (cltGameMsgRequest_SetGoonzuInfo*)pclMsg->cData;
	
	sDBRequest_SetGoonzuInfo clMsg(siID, ((cltServer *)pclClient)->pclCM->CR[siID]->pclCI->GetPersonID(),
		pclinfo->szGreeting);

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// DB���� ������ ���Ⱑ �Ϸ�Ǹ� Client���� �ٽ� �����Ͽ��ش�.
void CMinisterGoonzu::DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_SetGoonzuInfo* pclMsg = (sDBResponse_SetGoonzuInfo*)pPacket;

	SI32 id = pclMsg->usCharID;
	if(((cltServer *)pclClient)->pclCM->IsAlive(id) == false)return ;

	if(pclMsg->siResult == 1)
	{
		// �������̶�� 
		if(((cltServer *)pclClient)->pclCM->CR[id]->pclCI->GetPersonID() == pclMsg->siPersonID)
		{
			StringCchCopy(m_szAccountID, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szAccountID);
			StringCchCopy(m_szPersonName, MAX_PLAYER_NAME, 	pclMsg->MinisterBase.m_szPersonName);
			StringCchCopy(m_szGreeting, 256, 	pclMsg->MinisterBase.m_szGreeting);
		}
	}
	else
	{
		// ���� Error
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETGOONZUINFO,  0, 0, id);
	}
	
	// ������ ��û�������� ���� �����ش�.
	DoMsg_GameMsgRequest_GetMinisterInfo(id);
}

void CMinisterGoonzu::DoMsgDBMsgRequest_SetGoonzuFinances(clock_t currentclock)
{
	static DWORD dwGoonzuFinances = 0 ;

#ifdef _DEBUG
	if ( TABS( currentclock - dwGoonzuFinances ) <= 60000 ) // 1��
		return ;
#else
    if ( TABS( currentclock - dwGoonzuFinances ) <= 600000 ) // 10��
		return ;
#endif

	sDBRequest_SetGoonzuFinances clMsg(GetTempFinances());

	m_iTempFinances = 0 ;

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
	
	dwGoonzuFinances  = currentclock;
}

void CMinisterGoonzu::RemoveFinances(GMONEY money)
{
	if ( money < 0 ) return ;

	sDBRequest_SetGoonzuFinances clMsg(-money);

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

	
}

void CMinisterGoonzu::ActionGameServerInfo(clock_t currentclock)
{
	enum PVP_LEAGUE_test
	{
		PVP_LEAGUE_GRADE_NONE	= 0,	// ����� ����(PVP �������� ���� �ʾ���)

		PVP_LEAGUE_GRADE_9		= 5,
		PVP_LEAGUE_GRADE_8		= 10,
		PVP_LEAGUE_GRADE_7		= 15,
		PVP_LEAGUE_GRADE_6		= 20,
		PVP_LEAGUE_GRADE_5		= 25,
		PVP_LEAGUE_GRADE_4		= 30,
		PVP_LEAGUE_GRADE_3		= 35,
		PVP_LEAGUE_GRADE_2		= 40,
		PVP_LEAGUE_GRADE_1		= 45,
	};

	static DWORD dwActionGameServerInfo = 0 ;

	if ( dwActionGameServerInfo != 0 &&	TABS( currentclock - dwActionGameServerInfo ) <= 600000 ) // 10��
		return ;

	cltServer* pclserver = (cltServer*)pclClient ;

	if ( pclserver == NULL ) return ;
	if ( pclserver->bCompleteDBInitAll == FALSE ) return ;
	if ( pclserver->pclItemManager->clItemStatistic.siNPCPriceRate < 100 ) return ;
	if ( pclserver->pclItemManager->clItemStatistic.siItemPriceIndex <= 0 ) return ;

	StringCchCopy( pclserver->m_gameserverinfo.goonzuname, 20,m_szPersonName );
	StringCchCopy( pclserver->m_gameserverinfo.goonzutext, 256, m_szGreeting );

	CMinisterHozo *pclministerHozo = (CMinisterHozo*)pclserver->pclMinisterMgr->GetMinister(MINISTER_HOZO);
	if ( pclministerHozo == NULL ) return ;

	

	pclserver->m_gameserverinfo.population = pclministerHozo->m_siTotalCharNum ;

	pclserver->m_gameserverinfo.currentPrice = pclserver->pclItemManager->clItemStatistic.siItemPriceIndex ;
	pclserver->m_gameserverinfo.npcrate = pclserver->pclItemManager->clItemStatistic.siNPCPriceRate ;

	pclserver->m_gameserverinfo.fixationmoney = pclministerHozo->m_siFixationMoney * 10 ;

	pclserver->m_bGameserverinfo = TRUE ;

	dwActionGameServerInfo  = currentclock;
}