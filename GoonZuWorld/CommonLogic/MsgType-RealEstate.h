#ifndef _MSGTYPEREALESTATE_H
#define _MSGTYPEREALESTATE_H

//-----------------------------------
// �ε��� ��� ���� ��û. 
//-----------------------------------
class cltGameMsgRequest_ExtendContract{
public:
	SI32 siVillageUnique;
	SI32 siRealEstateType;
	SI32 siIndex;

	cltRentContract clContract;

	cltGameMsgRequest_ExtendContract(SI32 villageunique, SI32 type, SI32 index, cltRentContract* pclcontract)
	{
		siVillageUnique		= villageunique;
		siRealEstateType	= type;
		siIndex				= index;
		clContract.Set(pclcontract);
	}
};

#endif

