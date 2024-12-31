#ifndef _MSGTYPEMINE_H
#define _MSGTYPEMINE_H

#include "../Mine/Mine.h"

//------------------------------------
// ���� ��� ���� ����
//------------------------------------
class cltGameMsgRequest_MineChangeContract {
public:
	SI32 siVillageUnique;
	cltRentContract clRentContract;

	cltGameMsgRequest_MineChangeContract( SI32 villageunique, const cltRentContract* pclcontract )
	{
		siVillageUnique = villageunique;
		clRentContract.Set(pclcontract);
	}
};


//------------------------------------
// ���� ����Ʈ ����Ʈ ����. 
//------------------------------------
class cltGameMsgResponse_MineUnitList{
public:
	SI32 siVillageUnique;
	cltSimplePerson clPerson[ MAX_MINEUNIT_NUMBER ];			// ������. 

	cltGameMsgResponse_MineUnitList( SI32 villageunique )
	{
		siVillageUnique	= villageunique;
	}
};


//------------------------------------
// ���� ��û 
//------------------------------------
class cltGameMsgRequest_MineRentApply
{
public:
	cltRentContract clRentContract;

	cltGameMsgRequest_MineRentApply( cltRentContract* pclcontract )
	{
		clRentContract.Set(pclcontract);
	}
};


//------------------------------------
// ���� ����� ���� 
//------------------------------------
class cltGameMsgResponse_MineApplyerList
{
public:
	SI32				siVillageUnique;
	cltRentApplyer		clMineApplyer[ MAX_APPLY_PER_MINE ];

	cltGameMsgResponse_MineApplyerList( int villageunique ) 
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_MineApplyerList ) );

		siVillageUnique = villageunique;
	}



};


//------------------------------------
// ���� ����Ʈ �� ���� ����Ʈ ����. 
//------------------------------------
class cltGameMsgResponse_MineUnitListDetail{
public:
	SI32 siVillageUnique;
	cltRentContract	clContract[ MAX_MINEUNIT_NUMBER ];			// ��� ����. 

	cltGameMsgResponse_MineUnitListDetail(SI32 villageunique)
	{
		siVillageUnique	= villageunique;
	}
};


//----------------------------------------
// �Ӵ��㰡 
//----------------------------------------
class cltGameMsgRequest_MineRent{
public:
	SI32 siPersonID;		// �Ӵ� ������� PersonID
	SI32 siVillageUnique;	// ������ ��ġ�� ������ VillageUnique
	SI32 siIndex;			// �Ӵ��� �� ������ ����. 

	cltGameMsgRequest_MineRent( SI32 personid, SI32 villageunique, SI32 index )
	{
		siPersonID		= personid;
		siVillageUnique	= villageunique;
		siIndex			= index;
	}

};


#endif