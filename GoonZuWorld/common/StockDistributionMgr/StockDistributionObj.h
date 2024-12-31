#ifndef _STOCKDISTRIBUTIONOBJ_H_
#define _STOCKDISTRIBUTIONOBJ_H_

#include "..\SMLib\LibList\Obj.h"
#include "NDataTypes.h"

class CStockDistributionObj : public CObj
{
public:
	CStockDistributionObj( SI32 Index );
	~CStockDistributionObj();

	void Initialize();
	void Destroy();

	SI16 GetCurrentStatus();
	SI32 GetVillageUnique();
	SI32 Set( SI32 VillageUnique, SI32 MaxDistributionStockNum, SI32 DistributionStockUnit, GMONEY DistributionStockPrice, bool VillageWarStockDistribution, SI32 VillageWarWinVillageUnique );
	bool Action();
	SI32 IncreaseDistributionStockNum( SI32 IncreaseDistributionStockNum );
	
	SI32 GetDistributionStockUnit();			// �Ѹ��� �ټ� �ִ� �ִ� �ֽļ�.
	GMONEY GetDistributionStockPrice();			// �� �ֽĴ� ����

	SI32 GetLeftDistributionStockNum();			// ���� �ֽļ�
	SI32 GetMaxDistributionStockNum();			// ��� �ִ� �ֽļ�

	bool IsVillageWarStockDistribution();		// ������ ���� �ֽ� �����̳�??
private:

	SI32 m_siStockDistributionObjIndex;
	SI16 m_siCurrentStatus;
	
	SI32 m_siVillageUnique;						// ����

	SI32 m_siMaxDistributionStockNum;			// �ִ� �����鿡�� �ִ� �ֽļ�
	SI32 m_siDistributionStockUnit;				// �� �����鿡�� �ټ� �ִ� �ִ� �ֽļ�
	GMONEY m_siDistributionStockPrice;			// �� �ֽĴ� ����

	SI32 m_siCurrentDistributionStockNum;		// ���� �й�� �ֽļ�

	SI32 m_siCurrentFrame;

	bool m_bVillageWarStockDistribution;		// ������ ���� �ֽ� �������� ���� ���� ���� ��.
};

#endif