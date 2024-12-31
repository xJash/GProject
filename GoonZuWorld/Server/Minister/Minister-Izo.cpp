
#include "Char\CharManager\CharManager.h"
#include "..\..\CommonLogic\CommonLogic.h"
#include "DevTool/DevServerInfo/DevServerInfo.h"
#include "..\Server.h"

#include "MinisterBase.h"
#include "Minister-Izo.h"

#include "..\..\CommonLogic\MsgRval-Define.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg.h"
#include "..\..\..\DBManager\GameDBManager_World\DBMsg-System.h"
#include "..\CommonLogic\MsgType-System.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"

extern cltCommonLogic* pclClient;

CMinisterIzo::CMinisterIzo() : CMinisterBase()
{
	m_siPriceValue = 70;
	m_siPriceTime = 0 ;
	m_siTotalMoney = 0 ;
	m_siCalcTime = 0 ;
	m_siTradeTax = 5 ;
	m_siTradeLimitMoney = 10000000 ;

	m_bWorldTradeTax = true;
	m_siSpecialTaxRange = Const_SpecialTaxRange_Min;
	m_siSpecialTaxRate = Const_SpecialTaxRate_Min;

	m_siMarketDownRate = Const_MarketDownRate_Min;
}

CMinisterIzo::~CMinisterIzo()
{
}

// DB�� ������ ������ ��û�Ѵ�.
void CMinisterIzo::InitializeDB()
{
	// ������ ������ ��û�Ѵ�.
	sDBRequest_GetIzoInfo clMsg;
	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);

}

// DB���� ������ ������ ������ ���� Class�� �����Ѵ�.
void  CMinisterIzo::DoMsg_DBMsgResponse_GetMinisterInfo(sPacketHeader* pPacket)
{

	sDBResponse_GetIzoInfo* pclMsg = (sDBResponse_GetIzoInfo *)pPacket;

	if(pclMsg->siResult)
	{
		StringCchCopy(m_szAccountID, MAX_PLAYER_NAME,	pclMsg->MinisterBase.m_szAccountID);
		StringCchCopy(m_szPersonName,	MAX_PLAYER_NAME, pclMsg->MinisterBase.m_szPersonName);
		StringCchCopy(m_szGreeting,	256, pclMsg->MinisterBase.m_szGreeting);

		// �������� 50���� ũ�� 75���� �۴�
		m_siPriceValue =	pclMsg->siPriceValue;
		if(m_siPriceValue<50 || m_siPriceValue>75)	m_siPriceValue = 70;

		m_siPriceTime =		pclMsg->siPriceTime;
		if(m_siPriceTime <= 0 ) m_siPriceTime = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() - 30 ;

		m_siTotalMoney =	pclMsg->siTotalMoney;
		if ( m_siTotalMoney < 0 ) m_siTotalMoney = 0 ;
		
		m_siCalcTime =		pclMsg->siCalcTime;
		if ( m_siCalcTime <= 0 ) m_siCalcTime = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary() ;
		
		// ������ 5���� 20�����̴�.
		m_siTradeTax = pclMsg->siTradeTax ;
		if(m_siTradeTax < 5 || m_siTradeTax > 20 ) m_siTradeTax = 5 ;

		// �ּҸ��԰��� 100���ɿ��� 1000�����̴�.
		m_siTradeLimitMoney = pclMsg->siTradeLimitMoney ;
		if( m_siTradeLimitMoney < 1000000 || m_siTradeLimitMoney > 10000000 ) m_siTradeLimitMoney = 10000000 ;

		m_bWorldTradeTax = pclMsg->bWorldTradeTax;			// ����_���� ���� ����

		m_siSpecialTaxRange = pclMsg->siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
		if(m_siSpecialTaxRange < Const_SpecialTaxRange_Min || m_siSpecialTaxRange > Const_SpecialTaxRange_Max )
			m_siSpecialTaxRange = Const_SpecialTaxRange_Min;

		m_siSpecialTaxRate = pclMsg->siSpecialTaxRate;			// ����_Ư������( 10% ~ 100% )
		if(m_siSpecialTaxRate < Const_SpecialTaxRate_Min || m_siSpecialTaxRate > Const_SpecialTaxRate_Max )
			m_siSpecialTaxRate = Const_SpecialTaxRate_Min;

		m_siMarketDownRate = pclMsg->siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
		if(m_siMarketDownRate < Const_MarketDownRate_Min || m_siMarketDownRate > Const_MarketDownRate_Max )
			m_siMarketDownRate = Const_MarketDownRate_Min;

		m_siTinTin = pclMsg->siTinTin;

	}
	pclClient->pclserverinfoDlg->OnServerInfoDialog(TEXT("sDBResponse_GetIzoInfo"));
}

// Client���� ������ ������ ��û�ϸ� ���� Class�� �ִ� ������ �����Ѵ�.
void CMinisterIzo::DoMsg_GameMsgRequest_GetMinisterInfo(SI32 siID)
{
	CMinisterBase *pMinister = (CMinisterBase* )(this);
	cltGameMsgResponse_GetIzoInfo clinfo(pMinister,
		((cltServer *)pclClient)->pclItemManager->clItemStatistic.siItemPriceIndex,
		m_siPriceValue,m_siPriceTime,m_siTotalMoney,m_siCalcTime, m_siTradeTax, m_siTradeLimitMoney
		,m_bWorldTradeTax, m_siSpecialTaxRange, m_siSpecialTaxRate, m_siMarketDownRate, m_siTinTin );

	cltMsg clMsg(GAMEMSG_RESPONSE_GETIZOINFO, sizeof(clinfo), (BYTE*)&clinfo);
	((cltServer *)pclClient)->pclCM->CR[siID]->SendNetMsg((sPacketHeader*)&clMsg);

}

// Client���� ������ ���� ���� �����ϱ⸦ ���ϸ� ���������� DB�� ���� ������ ��û�Ѵ�.
void CMinisterIzo::DoMsg_GameMsgRequest_SetMinisterInfo(cltMsg* pclMsg, SI32 siID)
{
	cltGameMsgRequest_SetIzoInfo *pclinfo = (cltGameMsgRequest_SetIzoInfo*)pclMsg->cData;
	
	// �Ѵ� �̳����� ��ó������ �ʴ´�. 
	SI32 curdate = ((cltServer*)pclClient)->pclTime->clDate.GetDateVary();
	if(m_siPriceTime + 30 >  curdate)return ;

	sDBRequest_SetIzoInfo clMsg(siID, ((cltServer *)pclClient)->pclCM->CR[siID]->pclCI->GetPersonID(),
		pclinfo->szGreeting, pclinfo->siPriceValue, curdate, pclinfo->bWorldTradeTax,
		pclinfo->siSpecialTaxRange, pclinfo->siSpecialTaxRate, pclinfo->siMarketDownRate,
		pclinfo->siTinTin);

	((cltServer *)pclClient)->pclGameDBProcess->SendMsg((sPacketHeader *)&clMsg);
}

// DB���� ������ ���Ⱑ �Ϸ�Ǹ� Client���� �ٽ� �����Ͽ��ش�.
void CMinisterIzo::DoMsg_DBMsgResponse_SetMinisterInfo(sPacketHeader* pPacket)
{
	sDBResponse_SetIzoInfo* pclMsg = (sDBResponse_SetIzoInfo*)pPacket;
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

			// �������� 50���� ũ�� 75���� �۴�
			m_siPriceValue		= pclMsg->siPriceValue;
			if(m_siPriceValue<50 || m_siPriceValue>75)	m_siPriceValue = 70;
			m_siPriceTime		= pclMsg->siPriceTime;

			// ������ 5���� ũ�� 20���� �۴�
			m_siTradeTax		= pclMsg->siTradeTax;
			if(m_siTradeTax< 5 || m_siTradeTax > 20 ) m_siTradeTax = 5 ;

			// �ּҸ��԰��� 100���ɿ��� 1000�����̴�.
			m_siTradeLimitMoney = pclMsg->siTradeLimitMoney ;
			if( m_siTradeLimitMoney < 1000000 || m_siTradeLimitMoney > 10000000 ) m_siTradeLimitMoney = 10000000 ;

			m_bWorldTradeTax = pclMsg->bWorldTradeTax;				// ����_���� ���� ����

			m_siSpecialTaxRange = pclMsg->siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
			if(m_siSpecialTaxRange < Const_SpecialTaxRange_Min || m_siSpecialTaxRange > Const_SpecialTaxRange_Max )
				m_siSpecialTaxRange = Const_SpecialTaxRange_Min;

			m_siSpecialTaxRate = pclMsg->siSpecialTaxRate;			// ����_Ư������( 10% ~ 100% )
			if(m_siSpecialTaxRate < Const_SpecialTaxRate_Min || m_siSpecialTaxRate > Const_SpecialTaxRate_Max )
				m_siSpecialTaxRate = Const_SpecialTaxRate_Min;

			m_siMarketDownRate = pclMsg->siMarketDownRate;			//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
			if(m_siMarketDownRate < Const_MarketDownRate_Min || m_siMarketDownRate > Const_MarketDownRate_Max )
				m_siMarketDownRate = Const_MarketDownRate_Min;

			m_siTinTin = pclMsg->siTinTin;

			if(pclClient->IsWhereServiceArea(ConstSwitch_NewLog)) 
			{
				// [�α��߰� : Ȳ���� 2007. 10. 10] // ��������.
				// param1    == ������, param2    == PriceTime, param3 == ������, param4 == ���� ���� �ݾ�, 
				// pszParam1 == ����,   pszParam2 == �̸�.
				cltServer * pclserver = (cltServer*)pclClient;
				cltCharServer* pclchar = (cltCharServer*)pclClient->pclCM->CR[id];

				TCHAR szCharParam1[50] = { '\0', };
				TCHAR szCharParam2[50] = { '\0', };

				StringCchPrintf(szCharParam1, sizeof(szCharParam1), TEXT("ID:%s, NAME:%s"), pclMsg->MinisterBase.m_szAccountID, pclMsg->MinisterBase.m_szPersonName );
				StringCchPrintf(szCharParam2, sizeof(szCharParam2), TEXT("TRADE [ %d - Range:%d, TaxRate:%d ], MARKET [ DownRate:%d ]"), pclMsg->bWorldTradeTax, pclMsg->siSpecialTaxRange, pclMsg->siSpecialTaxRate, pclMsg->siMarketDownRate );

				pclserver->SendLog_WriteLogToDB(LOGCOMMAND_TYPE_MINISTER, LOGCOMMAND_INDEX_MINISTER_IZO_SET, 
					0, pclchar, NULL, 0, 0, 0, NULL, 0, 0, 0, 0, 0, 0, 
					pclMsg->siPriceValue, pclMsg->siPriceTime, 
					pclMsg->siTradeTax, pclMsg->siTradeLimitMoney, 0, 
					szCharParam1, szCharParam2 );
			}
		}
	}
	else
	{
		// ���� Error
		((cltServer*)pclClient)->SendServerResponseMsg(0, SRVAL_MINISTER_FAIL_SETIZOINFO,  0, 0, id);
	}
	
	// ������ ��û�������� ���� �����ش�.
	DoMsg_GameMsgRequest_GetMinisterInfo(id);

}
