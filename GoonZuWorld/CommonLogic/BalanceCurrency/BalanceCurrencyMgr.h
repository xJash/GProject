#pragma once

//////////////////////////////////////////////////////////////////////////
//	Title		: [��ȣ] 2000526 ��ȭ�� ��� ��å
//
//	Description : ���ӳ��� ��ȭ���� �����ϱ� ���� manager �Դϴ�.
//				  ���λ������� �������󿡼� +�� ��ȭ���� ��� �մϴ�.
//////////////////////////////////////////////////////////////////////////

#include <Directives.h>
#include "../../Common/CommonHeader.h"

//	��ȭ�� ���� ����
enum CurrencyUpdateState	
{
	CURRENCY_UPDATE_NONE,
	CURRENCY_UPDATE_TODAY_DONE,					//	DB�κ��� ���� ��ȭ�� ���� �Ϸ�
	CURRENCY_UPDATE_ALL_DONE,					//	DB�κ��� ���� ��ȭ�� ���� �Ϸ�
};


class CBalanceCurrencyMgr
{
private:
	enum NPCCoordinate
	{
		BALANCECURRENCY_X	=	37,
		BALANCECURRENCY_Y	=	36,
	};

	GMONEY	m_siCanUseMoney;						//	����Ҽ� �ִ� ��ȭ��
	GMONEY	m_siTodayCurrency;						//	���� DB�κ��� �޾ƿ� �� ��ȭ��
	GMONEY	m_siYesterdayCurrency;					//	���� DB�κ��� �޾ƿ� �� ��ȭ��

	SI32	m_siUpdateState;						//	��ȭ�� ���� ����

	bool	m_bNeedToCalculateCurrency;				//	��ȭ�� ����� �ʿ��Ѱ�.

private:
	SI32	m_siBalanceCurrencyID;					//	��ȭ�� ���� NPC�� ĳ����ID


public:
	bool	CreateBalanceCurrencyNPC();				//	��ȭ�� ���� NPC ����
	void	Action();
	
	GMONEY	GetBuffCost();					//	npcrate�� ����� ���
	void	CalculateBalanceCurrency();	
	SI32	GetBalanceCurrencyNPC_ID(){return m_siBalanceCurrencyID;}

	void	SetCanUserMoney(){m_siCanUseMoney = m_siTodayCurrency - m_siYesterdayCurrency;}	//	Server���� CanUserMoney()����� ��쿡�� �� �Լ��� ���
	void	SetCanUserMoney(GMONEY siMoney){m_siCanUseMoney = siMoney;}						//	Client�������� Server���� �޾ƿð�쿡�� �� �Լ��� ����ؼ� �ٷ� Money����
	GMONEY	GetCanUseMoney(){return m_siCanUseMoney;}
    

	void	SetTodayCurrency(GMONEY siMoney){m_siTodayCurrency = siMoney;}
	GMONEY	GetTodayCurrency(){return m_siTodayCurrency;}

	void	SetYesterDayCurrency(GMONEY siMoney){m_siYesterdayCurrency = siMoney;}
	GMONEY	GetYesterDayCurrency(){return m_siTodayCurrency;}

	void	SetUpdateState(SI32 siState){m_siUpdateState = siState;}
	SI32	GetUpdateState(){return m_siUpdateState;}	


public:	
	CBalanceCurrencyMgr(void);
	~CBalanceCurrencyMgr(void);
};
