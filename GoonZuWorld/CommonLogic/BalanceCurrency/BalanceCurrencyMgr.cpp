#include "balancecurrencymgr.h"

#include "Char/CharManager/CharManager.h"
#include "../../CommonLogic/CommonLogic.h"
#include "../../CommonLogic/MsgType-System.h"
#include "../../CommonLogic/MsgRval-Define.h"
#include "../../DBManager/GameDBManager_World/DBMsg-Item.h"
#include "../../Lib/dxutil.h"
#include "../../Server/Server.h"

extern cltCommonLogic* pclClient;

CBalanceCurrencyMgr::CBalanceCurrencyMgr(void)
{
	m_siCanUseMoney			=	0;
	m_siTodayCurrency		=	0;
	m_siYesterdayCurrency	=	0;

	m_siBalanceCurrencyID	=	0;

	m_siUpdateState			=	CURRENCY_UPDATE_NONE;

	m_bNeedToCalculateCurrency	=	true;
}


CBalanceCurrencyMgr::~CBalanceCurrencyMgr(void)
{
	m_siCanUseMoney			=	0;
	m_siTodayCurrency		=	0;
	m_siYesterdayCurrency	=	0;
	m_siBalanceCurrencyID	=	0;
}

bool CBalanceCurrencyMgr::CreateBalanceCurrencyNPC()
{
    cltServer* pclServer = (cltServer*)pclClient;

	if (pclServer == NULL)
		return false;


	SI32 siKindOfNPC = pclClient->GetUniqueFromHash("KIND_BALANCECURRENCY");
	if (0 >= siKindOfNPC)
		return false;

	m_siBalanceCurrencyID = pclServer->SetNPCChar(	siKindOfNPC, 
													VILLAGE_NONE, 
													NULL, 
													1, 
													1, 
													BALANCECURRENCY_X, 
													BALANCECURRENCY_Y, 
													MAPINDEX_PRIVATEMARKETAREA, 
													NPCITEMMODE_NONE, 
													NULL );

	if(m_siBalanceCurrencyID != 0)
		return true;
	else
		return false;
}

//	m_siTodayCurrency - m_siYesterdayCurrency + m_siRemainMoney
void CBalanceCurrencyMgr::CalculateBalanceCurrency()
{
	m_siCanUseMoney += GetTodayCurrency() - GetYesterDayCurrency();
}


GMONEY CBalanceCurrencyMgr::GetBuffCost()
{
	SI32 npcrate = pclClient->pclItemManager->clItemStatistic.siNPCPriceRate;

	GMONEY	siPrice = 0;

	if		(npcrate < 100)		siPrice	=	150000;
	else if	(npcrate < 300)		siPrice	=	300000;
	else if	(npcrate < 700)		siPrice	=	500000;
	else if	(npcrate < 1000)	siPrice	=	1000000;
	else if	(npcrate < 1450)	siPrice	=	1800000;
	else if	(npcrate < 1750)	siPrice	=	2900000;
	else if	(npcrate < 2050)	siPrice	=	4200000;
	else if	(npcrate < 2350)	siPrice	=	5800000;
	else if	(npcrate < 3000)	siPrice	=	7800000;
	else if (npcrate < 4000)	siPrice	=	10000000;
	else if (npcrate < 5500)	siPrice	=	13000000;
	else if (npcrate < 8500)	siPrice	=	18000000;
	else if (npcrate < 14500)	siPrice	=	25000000;
	else if (npcrate < 25500)	siPrice	=	40000000;
	else if (npcrate < 35500)	siPrice	=	58000000;
	else						siPrice =	85000000;

	return siPrice;
}

void CBalanceCurrencyMgr::Action()
{
	cltServer* pclServer = (cltServer*)pclClient;

	//	�� �Լ��� ȣ��ȴٸ� �������� NPC �������� ����� �Ϸ�� �����̴� ���⼭ 
	//	CreateBalanceCurrencyNPC �Լ��� �� �ѹ��� ȣ���� �ش�.
	if(m_siBalanceCurrencyID == 0)
	{
		bool bResult = CreateBalanceCurrencyNPC();		//	���⿡ ���´ٸ� ������ �簡�� �Ѵٴ� ���� ����.

		if(bResult == false)
			return;
	}

	//	DB�κ��� ��꿡 �ʿ��� ���ð� ���� ��ȭ���� �޾ƿ� ���¶��
	if(GetUpdateState() == CURRENCY_UPDATE_ALL_DONE)
	{
		//	���� 7�� 20�п� ��ȭ�� ������ �Ѵ�.
		_SYSTEMTIME sTime;
		GetLocalTime(&sTime);

		if(sTime.wHour == 7 && sTime.wMinute == 20)
		{
			if(m_bNeedToCalculateCurrency == true)
			{
				CalculateBalanceCurrency();

				//[��ȣ] ��ȭ�� ���� - ��밡�� ��ȭ�� ����
				sDBRequest_SetBalanceCanUseCurrency clMsg(GetCanUseMoney());	
				pclServer->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);

				m_bNeedToCalculateCurrency = false;
				SetUpdateState(CURRENCY_UPDATE_ALL_DONE);
			}
		}
		else
			m_bNeedToCalculateCurrency = true;
	}
}
