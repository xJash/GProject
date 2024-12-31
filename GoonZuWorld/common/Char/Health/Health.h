//---------------------------------
// 2003/9/27 ���°�
//---------------------------------

#ifndef _HEALTH_H
#define _HEALTH_H

#include "../../CommonHeader.h"

#include "..\Disease\Disease.h"

#define HEALTH_ACTION_DELAY		60000	// 60�ʿ� �ѹ����� Action�� ���Ѵ�.



#define HEALTH_STATUS_HUNGRY_1		0x1
#define HEALTH_STATUS_HUNGRY_2		0x2
#define HEALTH_STATUS_HUNGRY_3		0x4
#define HEALTH_STATUS_HUNGRY_4		0x8
#define HEALTH_STATUS_HUNGRY_5		0x10	// ���� �߰� ����. 
#define HEALTH_STATUS_HUNGRY_6		0x20
#define HEALTH_STATUS_HUNGRY_7		0x40
#define HEALTH_STATUS_HUNGRY_8		0x80
#define HEALTH_STATUS_HUNGRY_9		0x100
#define HEALTH_STATUS_HUNGRY_NORMAL	0x200	// ���� �߰� ����. 


#define HEALTH_STATUS_ORG1_SERIOUS		0x1000
#define HEALTH_STATUS_ORG1_BAD			0x2000
#define HEALTH_STATUS_ORG1_NORMAL		0x4000
#define HEALTH_STATUS_ORG1_GOOD			0x8000

#define HEALTH_STATUS_ORG2_SERIOUS		0x10000
#define HEALTH_STATUS_ORG2_BAD			0x20000
#define HEALTH_STATUS_ORG2_NORMAL		0x40000
#define HEALTH_STATUS_ORG2_GOOD			0x80000

#define HEALTH_STATUS_ORG3_SERIOUS		0x100000
#define HEALTH_STATUS_ORG3_BAD			0x200000
#define HEALTH_STATUS_ORG3_NORMAL		0x400000
#define HEALTH_STATUS_ORG3_GOOD			0x800000

#define HEALTH_STATUS_ORG4_SERIOUS		0x1000000
#define HEALTH_STATUS_ORG4_BAD			0x2000000
#define HEALTH_STATUS_ORG4_NORMAL		0x4000000
#define HEALTH_STATUS_ORG4_GOOD			0x8000000


#define MAXORG(level)	(25 + (level) / 2)			// ������ ���� ����� �ִ� ��� ����. 

//----------------------------------
// ���� ������ �ִ� ������ ����. 
//----------------------------------
class cltCurDisease{
public:
	SI16 siOrg1Unique;
	SI16 siOrg2Unique;
	SI16 siOrg3Unique;
	SI16 siOrg4Unique;

	cltCurDisease()
	{
		siOrg1Unique	= 0;
		siOrg2Unique	= 0;
		siOrg3Unique	= 0;
		siOrg4Unique	= 0;
	}

	// �־��� ������ ������ �ִ°� ?
	bool IsIn(SI32 diseaseunique)
	{
		if(siOrg1Unique == diseaseunique)return true;
		if(siOrg2Unique == diseaseunique)return true;
		if(siOrg3Unique == diseaseunique)return true;
		if(siOrg4Unique == diseaseunique)return true;

		return true;
	}
};


//-----------------------------------
// �ǰ� Ŭ����. 
//-----------------------------------
class cltHealth
{
public:
	cltHealthInfo* pclInfo;
	DWORD ActionClock;			// Action�� ���� �ð�. 
	
	cltHealth();

	bool Action(SI32 level, DWORD CurrentClock);

	// �ǰ� ���¸� �м��ؼ� �� ����� �����ش�. 
	SI32 AnalyzeHealth(SI32 level);

	// ������ �ǰ� ���¿� ���� Text�� ���Ѵ�.
	bool GetHealthText(SI32 level, TCHAR* text, SI16 txtSize);

	// �踦 ä���.
	void IncreaseHungry(UI32 amount)
	{
		SI32 hungry = pclInfo->siHungry + amount;
		if(hungry > 300)
		{
			hungry = 300;
		}

		pclInfo->siHungry = hungry;

	}	

	// ������� ������Ų��. 
	void DecreaseHungry(SI32 amount)
	{
		pclInfo->siHungry -= amount;

		if(pclInfo->siHungry < -300)
		{
			pclInfo->siHungry = -300;
		}
	}
	
	// ���� ������ �ִ� ���ǰ ��ġ�� ������.
	SI16 GetHungry()
	{
		return pclInfo->siHungry;
	}

	// ���� ������ �ִ� ������ ������ �˷��ش�. 
	bool GetCurDisease(cltCurDisease* pclcurdisease);

	// ������ ġ���Ѵ�. 
	bool CureDisease(SI32 diseaseunique);
	// ���� ������ �̸��� ���Ѵ�. 
	bool GetCurDiseaseName(TCHAR* pname, SI16 txtSize);

	

	// ����� ����� ã�´�. 
	SI32 GetHungryStatus(SI32 level);
	SI32 GetHungryMaxLimit(SI32 level);
	SI32 GetBasic(SI32 level);


};



#endif
