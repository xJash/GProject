//-------------------------------
// SJY 2005/12/06
//-------------------------------
#include "WorldMoneyMgr.h"

#include "CommonLogic.h"

#include "../../Server/Server.h"

#include "../../../DBManager/GameDBManager_World/DBMsg-WorldMoney.h"

extern cltCommonLogic* pclClient;

#define MAX_VALUE_UP			105
#define MAX_VALUE_DOWN			95
#define MAX_VALUE_PRICE			500

cltDistributionWorldMoney::cltDistributionWorldMoney()
{
	m_bActive = FALSE ; // ���� �������ΰ�

	m_dwStartClock = 0 ; // ���� �ð�
	m_dwEndClock = 0 ; // �������� �ð�

	m_siWorldMoney = 0 ; // ���� �������� ��ť�� ��
	m_siWorldMoneyPrice = 0 ; // ���� �������� ��ť�� ����
	m_siTotalWorldMoney = 0 ; // ���� �������� ��ť�� �Ѿ�

	m_wOldHour = (WORD)-1;
	m_siLimitLowPrice = 0;
	m_siLimitHighPrice = 0;


	for ( SI32 i = 0 ; i < MAX_WORLDMONEY_TRADELIST_NUM ; i ++ )
	{
		clTradeList[i].Set(0,0,0,0);
	}

	siAverageWorldMoneyPrice = 0 ;

	return ;
}

cltDistributionWorldMoney::~cltDistributionWorldMoney()
{
	m_bActive = FALSE ; // ���� �������ΰ�

	m_dwStartClock = 0 ; // ���� �ð�
	m_dwEndClock = 0 ; // �������� �ð�

	m_siWorldMoney = 0 ; // ���� �������� ��ť�� ��
	m_siWorldMoneyPrice = 0 ; // ���� �������� ��ť�� ����
	m_siTotalWorldMoney = 0 ; // ���� �������� ��ť�� �Ѿ�

	m_wOldHour = (WORD)-1;
	m_siLimitLowPrice = 0;
	m_siLimitHighPrice = 0;

	for ( SI32 i = 0 ; i < MAX_WORLDMONEY_TRADELIST_NUM ; i ++ )
	{
		clTradeList[i].Set(0,0,0,0);
	}

	siAverageWorldMoneyPrice = 0 ;
}

BOOL cltDistributionWorldMoney::IsActive()
{
	return m_bActive ;
}

DWORD cltDistributionWorldMoney::GetStartClock()
{
	return m_dwStartClock ;
}

DWORD cltDistributionWorldMoney::GetEndClockTime()
{
	return m_dwEndClock ;
}

BOOL cltDistributionWorldMoney::IsEndDistribution()
{
	if ( !m_bActive )
		return FALSE ;
	else
	{
		if ( m_dwStartClock == 0 || m_dwEndClock == 0 )
		{
			m_bActive = FALSE ;
			return FALSE ;
		}

		if ((DWORD)(TABS(pclClient->CurrentClock - m_dwStartClock)) >=  m_dwEndClock)
		{
			m_bActive = FALSE ;
			m_dwStartClock = 0 ;
			m_dwEndClock = 0 ;
			return FALSE ;
		}
		else
		{
			return TRUE ;
		}
	}

//	return TRUE ;
}

void cltDistributionWorldMoney::Set(BOOL acive,SI64 worldmoney,SI64 price,SI64 total,DWORD start,DWORD end)
{
	m_bActive = acive ;
	m_dwStartClock = start ;
	m_dwEndClock = end ;

	m_siWorldMoney = worldmoney ;
	m_siWorldMoneyPrice = price ;
	m_siTotalWorldMoney = total ;
}

BOOL cltDistributionWorldMoney::IsCorrectDistribution(SI64 worldmoney,SI64 price)
{
	if ( IsEndDistribution() == FALSE )
		return FALSE ;

	if ( m_siWorldMoney != worldmoney )
		return FALSE ;
	if ( m_siWorldMoneyPrice != price )
		return FALSE ;
	if ( m_siTotalWorldMoney < worldmoney )
		return FALSE ;

	m_siTotalWorldMoney -= worldmoney ;

	return TRUE ;
}

// worldmoney�� ������ itemnum�̰� price�� price��
SI64 cltDistributionWorldMoney::SetAverageWorldMoney(SI64 worldmoney,SI64 price)
{
	SI64 averageprice = siAverageWorldMoneyPrice ;

	cltServer *pclserver = (cltServer*)pclClient;

	if (m_wOldHour != pclserver->sTime.wHour)
	{
		m_siLimitLowPrice = averageprice * 80 / 100;
		m_siLimitHighPrice = averageprice * 120 / 100;
		m_wOldHour = pclserver->sTime.wHour;
	}

	if ( worldmoney && price )
	{
		if ( averageprice )
		{
			// �ŷ����� 10��ť ���� �̸� �ü� ������ �ݿ����� ����
			if (worldmoney <= 10)
				return averageprice;

			// �ŷ����� 300��ť �ʰ��̸� �ü� ������ �ݿ����� ����
			if (worldmoney > 300)
				return averageprice;

			//---------------------------------------------------
			// ������ �ü��� MAX_VALUE_UP%�̻��̸� MAX_VALUE_UP%������ �ݿ��Ѵ�. 
			//---------------------------------------------------
			SI64 maxprice = max(1, (averageprice * MAX_VALUE_UP / 100));
			if(maxprice == averageprice)
			{
				maxprice++;
			}

			//---------------------------------------------------
			// ������ �ü����� MAX_VALUE_DOWN%���϶�� MAX_VALUE_DOWN%������ �ݿ��Ѵ�.
			//---------------------------------------------------
			SI64 minprice = max(1, (averageprice * MAX_VALUE_DOWN / 100));
			if(minprice == averageprice )
			{
				minprice = max(1, minprice-1);
			}

			// ��ΰ� �����Ǵ� ���� ���������� �����Ѵ�.
			if(price > maxprice)
			{
				price = maxprice;

				// ������ �ʹ� ���� �͵� �����Ѵ�. 
				if(worldmoney > 10)worldmoney = 10;
			}
			// �ΰ� �����Ǵ� ���� ���������� �ݿ��Ѵ�. 
			else if(price < minprice)
			{
				price = minprice;

				// ������ �ʹ� ���� �͵� �����Ѵ�. 
				if(worldmoney > 1000)worldmoney = 1000;
			}
		}

		if(averageprice == 0)
		{
			// ���� ������ 100�ɿ��� �����Ѵ�. 
			if ( worldmoney > 5000 ) worldmoney = 5000 ;

			averageprice = worldmoney ;
		}
		else
		{
			GMONEY orgworldmoney = min(10000, worldmoney);

			// 1�ð����� �ü���ȭ�� 20%�� ���� �ʵ���
			GMONEY tmpaverageprice = (( averageprice * orgworldmoney ) + ( price * worldmoney ))/(orgworldmoney+worldmoney);
			//averageprice = (( averageprice * orgworldmoney ) + ( price * worldmoney ))/(orgworldmoney+worldmoney);

			if (tmpaverageprice > m_siLimitHighPrice)
			{
				averageprice = m_siLimitHighPrice;
			}
			else if (tmpaverageprice < m_siLimitLowPrice)
			{
				averageprice = m_siLimitLowPrice;
			}
			else
			{
				averageprice = tmpaverageprice;
			}
		}

		// ACU�ü� �������� 100
		averageprice = max(averageprice, 100);
	}

	return averageprice ;
}

void cltDistributionWorldMoney::Action(bool bdaychangedswitch)
{
	cltServer* pclserver = (cltServer*)pclClient;
	if ( pclserver == NULL ) return ;

	// DB �ʱ�ȭ �Ϸ�ɶ����� ��ٸ�
	if( pclserver->bCompleteDBInitAll == FALSE ) return ;

	if ( bdaychangedswitch )
	{
		SI32 curdate = pclserver->pclTime->clDate.GetDateVary() ;

		for ( SI32 i = 0 ; i < MAX_WORLDMONEY_TRADELIST_NUM ; i ++ )
		{
			// 100�� ���Ϸδ� �� ������.
			if ( clTradeList[i].siPrice <= 100 )
				continue;
			if ( clTradeList[i].siPersonID <= 0 )
				continue;

			// 30�Ͽ� �ѹ� ��´�.
			if ( clTradeList[i].siDate + 30 <= curdate )
			{
				SI64 price = ( clTradeList[i].siPrice * 90 ) / 100 ; // 90%�� �����.
				if ( price <= 100 )
					price = 100 ;

				sDBRequest_WorldMoney_ReducePrice clMsg(i,price,curdate,clTradeList[i].siPersonID,clTradeList[i].siWorldMoney);
				pclserver->SendDBMsg(DBSELECT_BASE, (sPacketHeader *)&clMsg);
			}
		}
	}
}