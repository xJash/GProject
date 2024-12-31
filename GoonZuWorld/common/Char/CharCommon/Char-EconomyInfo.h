//---------------------------------
// 2003/6/2 ���°�
//---------------------------------

#ifndef _ECONOMYINFO_H
#define _ECONOMYINFO_H

#include "..\CommonLogic\Stock\Stock.h"
#include "..\CommonLogic\Market\Market.h"
//#include "..\CommonLogic\House\House.h"



#define REALESTATE_TYPE_HOUSE				1
#define REALESTATE_TYPE_LAND				2
#define REALESTATE_TYPE_MINE				3

#define MAX_REAL_ESTATE_NUMBER_PER_PERSON	10

//---------------------------------------------
// Person�� ���� ���� ������ ���ǰ��� ����.
//---------------------------------------------
/*
//_LEON_GUILD_STOCK
class cltPGuildStockInfo{
public:
	cltGuildStockAccount	clInfo;
	//cltCharOrderInfo		clOrderInfo;
	cltGuildCharOrderInfo	clOrderInfo;

	/*cyj
	cltPGuildStockInfo();

	void Init();
	void Set(cltPGuildStockInfo* pinfo);
	*/
/*
	cltPGuildStockInfo()
	{
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltPGuildStockInfo));

		clInfo.Init();
		clOrderInfo.Init();
	}

	void Set(cltPGuildStockInfo* pinfo)
	{
		memcpy(this, pinfo, sizeof(cltPGuildStockInfo));					//ok
	}


};*/


class cltPStockInfo{
public:
	cltStockAccount		clInfo;
	cltCharOrderInfo	clOrderInfo;

	/*cyj
	cltPStockInfo();

	void Init();
	void Set(cltPStockInfo* pinfo);
	*/

	cltPStockInfo()
	{
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltPStockInfo));

		clInfo.Init();
		clOrderInfo.Init();
	}

	void Set(cltPStockInfo* pinfo)
	{
		memcpy(this, pinfo, sizeof(cltPStockInfo));							//ok
	}

	void GetGMSectionData(GMSectionData* pkGMSectionData);
};

//-------------------------------------
// Person�� ���� ���� ����. 
//-------------------------------------
class cltPMarketInfo{
public:
	cltMarketAccount	clInfo;

	/*cyj
	cltPMarketInfo();

	void Init();
	void Set(cltPMarketInfo* pinfo);
	
	
	*/

	cltPMarketInfo()
	{
	}

	void Init()
	{
		ZeroMemory(this, sizeof(cltPMarketInfo));

		clInfo.Init();
	}

	void Set(cltPMarketInfo* pinfo)
	{
		memcpy(this, pinfo, sizeof(cltPMarketInfo));								//ok
	}

	bool IsInMarketOrder(SI32 siunique);		// �̹� �ش� ������ ���ֿ� �÷��� �ִ°� ?

};

//[����] ���ո��Ͽ� ���� �ø� ������.
class cltNewMarketInfo
{
public:
	cltNewMarketAccount		clInfo;

	cltNewMarketInfo()
	{
	}

	void Init()
	{
		ZeroMemory( this, sizeof(*this) );
	}

	void Set(cltNewMarketInfo* pinfo)
	{
		memcpy( this, pinfo, sizeof(*this) );								//ok
	}

	bool IsInNewMarketOrder( SI32 _siUnique );		// �̹� �ش� ������ ���ֿ� �÷��� �ִ°� ?
};


//-----------------------------------
// Person�� ���� ���� ���� 
//-----------------------------------
class cltRealEstateUnit{
public:
	SI32 siType;
	SI32 siVillageUnique;
	SI32 siIndex;

	// �ش� �ε����� ��� ����. 
	cltRentContract clContract;
	
	/*cyj
	cltRealEstateUnit();
	cltRealEstateUnit(SI32 type, SI32 villageunique, SI32 index, cltRentContract* pclinfo);

	void Set(const cltRealEstateUnit* pclinfo);
	void Set(SI32 type, SI32 villageunique, SI32 index, cltRentContract* pclinfo);
	void Init();
	*/

	cltRealEstateUnit()
	{
		siType			= 0;
		siVillageUnique = 0;
		siIndex			= 0;
	}

	cltRealEstateUnit(SI32 type, SI32 villageunique, SI32 index, cltRentContract* pclinfo)
	{
		siType			= type;
		siVillageUnique = villageunique;
		siIndex			= index;

		clContract.Set(pclinfo);
	}

	void Set(const cltRealEstateUnit* pclinfo)
	{
		siType			= pclinfo->siType;
		siVillageUnique = pclinfo->siVillageUnique;
		siIndex			= pclinfo->siIndex;

		clContract.Set(&pclinfo->clContract);
	}

	void Set(SI32 type, SI32 villageunique, SI32 index, cltRentContract* pclinfo)
	{
		siType			= type;
		siVillageUnique = villageunique;
		siIndex			= index;

		clContract.Set(pclinfo);
	}

	void Init()
	{
		siType			= 0;
		siVillageUnique = 0;
		siIndex			= 0;

		clContract.Init();
	}
};

class cltCharRealEstate{
public:
#ifdef _SAFE_MEMORY
	NSafeTArray<cltRealEstateUnit, MAX_REAL_ESTATE_NUMBER_PER_PERSON>	clRealEstate;
#else
	cltRealEstateUnit clRealEstate[MAX_REAL_ESTATE_NUMBER_PER_PERSON];
#endif

	/*cyj
	cltCharRealEstate();

	void Set(cltCharRealEstate* pclinfo);
	SI32 GetRealEstateNum();		// �����ϰ� �ִ� �ε����� ������ �����Ѵ�. 
	*/

	cltCharRealEstate()
	{}

	void Set(cltCharRealEstate* pclinfo)
	{
		SI32 i;
		for(i = 0;i < MAX_REAL_ESTATE_NUMBER_PER_PERSON;i++)
		{
			clRealEstate[i].Set(&pclinfo->clRealEstate[i]);
		}
	}

	SI32 GetRealEstateNum()
	{
		SI32 i;
		SI32 count = 0;
		for(i = 0;i < MAX_REAL_ESTATE_NUMBER_PER_PERSON;i++)
		{
			if(clRealEstate[i].siType)count++;
		}

		return count;

	}

	bool Add(SI32 type, SI32 sivillageunique, SI32 index, cltRentContract*  pclcontract );	// �ε����� �߰��Ѵ�. 
	bool Delete(SI32 type, SI32 sivillageunique, SI32 index);	// �ε����� �����Ѵ�. 

	SI32 FindEmptyIndex();			// �� �ڸ��� ã�´�. 
	cltRealEstateUnit*  Find(SI32 villageunique, SI32 ranktype, SI32 index);	// �����ϰ� �ִ� Ư�� �ε����� ã�Ƴ���.

};



#endif