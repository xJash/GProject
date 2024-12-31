#ifndef _MSGTYPELAND_H
#define _MSGTYPELAND_H

#include "../Land/Land.h"

//------------------------------------
// ���� ��� ���� ����
//------------------------------------
class cltGameMsgRequest_LandChangeContract {
public:
	SI32 siVillageUnique;
	cltRentContract clRentContract;

	cltGameMsgRequest_LandChangeContract( SI32 villageunique, const cltRentContract* pclcontract )
	{
		siVillageUnique = villageunique;
		clRentContract.Set(pclcontract);
	}
};


//------------------------------------
// ���� ����Ʈ ����Ʈ ����. 
//------------------------------------
class cltGameMsgResponse_LandUnitList{
public:
	SI32 siVillageUnique;
	cltSimplePerson clPerson[ MAX_LANDUNIT_NUMBER ];			// ������. 

	cltGameMsgResponse_LandUnitList( SI32 villageunique )
	{
		siVillageUnique	= villageunique;
	}
};


//------------------------------------
// ���� ��û 
//------------------------------------
class cltGameMsgRequest_LandRentApply
{
public:
	cltRentContract clRentContract;

	cltGameMsgRequest_LandRentApply( cltRentContract* pclcontract )
	{
		clRentContract.Set(pclcontract);
	}
};


//------------------------------------
// ���� ����� ���� 
//------------------------------------
class cltGameMsgResponse_LandApplyerList
{
public:
	SI32				siVillageUnique;
	cltRentApplyer		clLandApplyer[ MAX_APPLY_PER_LAND ];

	cltGameMsgResponse_LandApplyerList( int villageunique ) 
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_LandApplyerList ) );

		siVillageUnique = villageunique;
	}



};


//------------------------------------
// ���� ����Ʈ �� ���� ����Ʈ ����. 
//------------------------------------
class cltGameMsgResponse_LandUnitListDetail{
public:
	SI32 siVillageUnique;
	cltRentContract	clContract[ MAX_LANDUNIT_NUMBER ];			// ��� ����. 

	cltGameMsgResponse_LandUnitListDetail(SI32 villageunique)
	{
		siVillageUnique	= villageunique;
	}
};


//----------------------------------------
// �Ӵ��㰡 
//----------------------------------------
class cltGameMsgRequest_LandRent{
public:
	SI32 siPersonID;		// �Ӵ� ������� PersonID
	SI32 siVillageUnique;	// ������ ��ġ�� ������ VillageUnique
	SI32 siIndex;			// �Ӵ��� �� ������ ����. 

	cltGameMsgRequest_LandRent( SI32 personid, SI32 villageunique, SI32 index )
	{
		siPersonID		= personid;
		siVillageUnique	= villageunique;
		siIndex			= index;
	}

};


#endif