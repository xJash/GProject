#ifndef _WORLDMONEYMGR_H
#define _WORLDMONEYMGR_H

#include <Directives.h>

#include "../../../NLib/NArray.h"
#include <Stdio.h>

#define MAX_WORLDMONEY_TRADELIST_NUM		500
#define MAX_WORLDMONEY_TRADELIST_PER_SEND	50

class cltWorldOrder
{
public:
	SI64 siPrice; // �ֹ��� ����
	SI32 siIndex; // �ֹ��� ������

	SI16 siUnique;
	SI16 siItemNum;

	SI16 siType; // �Ӽ� ����
	SI16 siPower; // �Ӽ��� ��

	SI16 siRank; // �ֹ�ǰ ���

	SI08 siRareType; // �ֹ�ǰ�� ���(��ǰ,ȣǰ ��)

	char szData[24] ;

public:
	cltWorldOrder()
	{
		siPrice = 0 ; // �ֹ��� ����
		siIndex = 0 ; // �ֹ��� ������

		siUnique = 0 ;
		siItemNum = 0 ;

		siType = 0 ; // �Ӽ� ����
		siPower = 0 ; // �Ӽ��� ��

		siRank = 0 ; // �ֹ�ǰ ���

		siRareType = 0 ; // �ֹ�ǰ�� ���(��ǰ,ȣǰ ��)

		ZeroMemory(szData,sizeof(char) * 24);
	}

	void Set(cltWorldOrder* pclinfo)
	{
		siPrice = pclinfo->siPrice ;
		siIndex = pclinfo->siIndex ;

		siUnique = pclinfo->siUnique ;
		siItemNum = pclinfo->siItemNum ;

		siType = pclinfo->siType ;
		siPower = pclinfo->siPower ;

		siRank = pclinfo->siRank ;

		siRareType = pclinfo->siRareType ;

		if ( pclinfo->szData[0] != NULL )
			memcpy(szData,pclinfo->szData,24);
		else ZeroMemory(szData,sizeof(char) * 24);

	}

	//void Set(SI64 price , SI32 index , SI16 unique , SI16 num , SI16 type , SI16 power , SI08 rank , SI08 rare )
	void Set(SI64 price , SI32 index , SI16 unique , SI16 num , SI16 type , SI16 power , SI16 rank , SI08 rare ,char*data)
	{
		siPrice = price ;
		siIndex = index ;

		siUnique = unique ;
		siItemNum = num ;

		siType = type ;
		siPower = power ;

		siRank = rank ;

		siRareType = rare ;

		if ( data )
			memcpy(szData,data,24);
		else ZeroMemory(szData,sizeof(char) * 24);

	}
};

class cltWorldMoneyTradeList
{
public:
	SI64		siWorldMoney;
	SI64		siPrice;
	SI32		siPersonID;

	SI32		siDate; // �ø� �ð�

public:
	void Set(cltWorldMoneyTradeList* pclinfo)
	{
		siWorldMoney = pclinfo->siWorldMoney ;
		siPrice = pclinfo->siPrice ;
		siPersonID = pclinfo->siPersonID ;
		siDate = pclinfo->siDate ;
	}

	//void Set(SI32 worldmoney,SI32 price,SI32 personid)
	void Set(SI64 worldmoney,SI64 price,SI32 personid,SI32 date)
	{
		siWorldMoney = worldmoney ;
		siPrice = price ;
		siPersonID = personid ;
		siDate = date ;
	}
};

class cltWorldMoneyAccount{
public:
	SI64			siWorldMoney;			// �������� ��ť

	SI64			siTradeWorldMoney;		// �ŷ��ҿ� �ø� ��ť
	SI64			siTradeWorldMoneyPrice;	// �ŷ��ҿ� �ø� ��ť�� ����

public:
	void Set(cltWorldMoneyAccount * pclinfo)
	{
		siWorldMoney			= pclinfo->GetWorldMoney() ;

		siTradeWorldMoney		= pclinfo->siTradeWorldMoney ;
		siTradeWorldMoneyPrice	= pclinfo->siTradeWorldMoneyPrice ;
	}

	SI64 GetWorldMoney()
	{
		return siWorldMoney ;
	}
	void SetWorldMoney(SI64 money)
	{
		siWorldMoney = money ;
	}
	void IncreaseWorldMoney(SI64 money)
	{
		siWorldMoney += money ;
	}
	void DecreaseWorldMoney(SI64 money)
	{
		siWorldMoney -= money ;
	}

};

// ��ť ���� Ŭ����
class cltDistributionWorldMoney{
private:
	BOOL			m_bActive; // ���� �������ΰ�

	DWORD			m_dwStartClock; // ���� �ð�
	DWORD			m_dwEndClock; // �������� �ð�

	SI64			m_siWorldMoney; // ���� �������� ��ť�� ��
	SI64			m_siWorldMoneyPrice; // ���� �������� ��ť�� ����
	SI64			m_siTotalWorldMoney; // ���� �������� ��ť�� �Ѿ�

	WORD			m_wOldHour;
	SI64			m_siLimitLowPrice;
	SI64			m_siLimitHighPrice;

public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltWorldMoneyTradeList, MAX_WORLDMONEY_TRADELIST_NUM>	clTradeList;
#else
	cltWorldMoneyTradeList	clTradeList[MAX_WORLDMONEY_TRADELIST_NUM];
#endif
	SI64					siAverageWorldMoneyPrice; // ��ť �ü�

	cltDistributionWorldMoney();
	~cltDistributionWorldMoney();

	//void			Set(cltWorldMoneyTradeList*pclinfo)
	void Set(cltWorldMoneyTradeList*pclinfo)
	{
		for ( SI32 i = 0 ; i < MAX_WORLDMONEY_TRADELIST_NUM ; i ++ )
		{
			clTradeList[i].Set(&pclinfo[i]);
		}
	}

	void Set(SI32 index , SI32 worldmoney,SI32 price,SI32 personid,SI32 date)
	{
		if ( index < 0 || index >= MAX_WORLDMONEY_TRADELIST_NUM )
			return ;

		clTradeList[index].Set(worldmoney,price,personid,date);
	}

	BOOL			IsActive();
	DWORD			GetStartClock();
	DWORD			GetEndClockTime();

	BOOL			IsEndDistribution(); // ���� �����°�?
	void			Set(BOOL acive,SI64 worldmoney,SI64 price,SI64 total,DWORD start,DWORD end); // �����Ѵ�
	BOOL			IsCorrectDistribution(SI64 worldmoney,SI64 price);

	SI64			SetAverageWorldMoney(SI64 worldmoney,SI64 price) ; // �ŷ��� ��ť�� �������� ��ť �ü��� ���Ѵ�.

	void			Action(bool bdaychangedswitch);

};


#endif
