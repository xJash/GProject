#ifndef _DBMSGLAND_H
#define _DBMSGLAND_H

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Land\Land.h"

#define LANDRECALL_REASON_FEEDELAY			1	// ��ü�� ���� ȸ�� .
#define LANDRECALL_REASON_CONTRACTEND		2	// ��� ����� ���� ȸ��. 

//-----------------------------------------
// ���� ������ ������ ���´�. 
//-----------------------------------------
class sDBRequest_ManyLandUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;

	sDBRequest_ManyLandUnit()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyLandUnit));
	}

	sDBRequest_ManyLandUnit(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_ManyLandUnit );
		packetHeader.usCmd	= DBMSG_REQUEST_MANYLANDUNIT;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};

class sDBResponse_ManyLandUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;								// �����.

	SI32				siVillageUnique;						// ����� �Ǵ� ������ ��ġ�� ������ Unique
	cltLandUnit			clLandUnit[ MAX_LANDUNIT_NUMBER ];		// �� ������ �ִ� ���� ���� ������ ������ ��´�. 	

	sDBResponse_ManyLandUnit()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyLandUnit));
	}
};


//-----------------------------------------
// ������ ��� ������ �����ϵ��� �Ѵ�. 
//-----------------------------------------
class sDBRequest_LandChangeContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	cltRentContract		clContract;				// ��� ����
	
	cltDate				clDate;					// ��� ������

	sDBRequest_LandChangeContract()
	{
		ZeroMemory(this, sizeof(sDBRequest_LandChangeContract));
	}

	sDBRequest_LandChangeContract(SI32 id, SI32 villageunique, cltRentContract* pclcontract, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_LandChangeContract );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_CHANGECONTRACT;

		usCharID		= id;
		siVillageUnique	= villageunique;

		clContract.Set(pclcontract);
		clDate.Set( pclDate );
	}
};


class sDBResponse_LandChangeContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;				// �����.

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	cltRentContract		clContract;				// ����� ��� ����

	cltDate				clDate;					// ��� ������

	sDBResponse_LandChangeContract()
	{
		ZeroMemory(this, sizeof(sDBResponse_LandChangeContract));
	}
};



//-----------------------------------------
// ���� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_LandRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siPersonID;				// ��û��.
	
	cltRentContract		clContract;				// �������

	sDBRequest_LandRentApply()
	{
		ZeroMemory(this, sizeof(sDBRequest_LandRentApply));
	}

	sDBRequest_LandRentApply( SI32 id, SI32 villageunique, SI32 personid, cltRentContract* pclcontract )
	{
		packetHeader.usSize = sizeof( sDBRequest_LandRentApply );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_RENTAPPLY;

		usCharID		= id;
		siVillageUnique	= villageunique;
		siPersonID		= personid;

		clContract.Set(pclcontract);
	}
};


class sDBResponse_LandRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	
	SI32				siIndex;			// ���� ������� ������ ��� ��ġ�� ����Ų��.
	cltSimplePerson		clApplyer;			// ���� ����� ������ ��´�. 

	cltRentContract		clContract;			// ������� ��� ������ ��´�. 

	sDBResponse_LandRentApply()
	{
		ZeroMemory(this, sizeof(sDBResponse_LandRentApply));
	}
};


//-----------------------------------------
// ���� ���� ��û�� ����Ѵ�. 
//-----------------------------------------
class sDBRequest_LandCancelRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ��û��.
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����

	sDBRequest_LandCancelRentApply()
	{
		ZeroMemory( this, sizeof( sDBRequest_LandCancelRentApply ) );
	}

	sDBRequest_LandCancelRentApply( SI32 id, SI32 villageunique, SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_LandCancelRentApply );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_CANCELRENTAPPLY;

		usCharID		= id;

		siVillageUnique	= villageunique;
		siPersonID		= personid;
	}
};


class sDBResponse_LandCancelRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siPersonID;

	sDBResponse_LandCancelRentApply()
	{
		ZeroMemory( this, sizeof(sDBResponse_LandCancelRentApply) );
	}
};


//-----------------------------------------
// ���� ����� ����� ���´�. 
//-----------------------------------------
class sDBRequest_LandApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique; // ����� �Ǵ� ������ ��ġ�� ������ Unique

	sDBRequest_LandApplyerList()
	{
		ZeroMemory(this, sizeof(sDBRequest_LandApplyerList) );
	}

	sDBRequest_LandApplyerList(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_LandApplyerList );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_APPLYERLIST;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};


class sDBResponse_LandApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.

	SI32				siVillageUnique;					// ����� �Ǵ� ������ ��ġ�� ����
	cltRentApplyer		clApplyer[ MAX_APPLY_PER_LAND ];	// ���� ����� ����� ��´�. 

	sDBResponse_LandApplyerList()
	{
		ZeroMemory(this, sizeof(sDBResponse_LandApplyerList) );
	}
};


//-----------------------------------------------------
// ���� ������� ����� ��� �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_LandDelApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;

	// PCK : �α׿� ��Ŷ �߰�. ���� ����� ����� ������ �����ϴ°��� ������.
	SI32				siDelSlotNum;

	sDBRequest_LandDelApplyer()
	{
		ZeroMemory( this, sizeof(sDBRequest_LandDelApplyer) );
	}

	sDBRequest_LandDelApplyer( SI32 id, SI32 personid, SI32 villageunique, SI32 DelSlotNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_LandDelApplyer );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_DELAPPLYER;

		usCharID		= id;
		siPersonID		= personid;
		siVillageUnique	= villageunique;
		siDelSlotNum = DelSlotNum;
	}

};


class sDBResponse_LandDelApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;		

	SI32				siPersonID;			
	SI32				siVillageUnique;

	// PCK : �α׿� ��Ŷ �߰�, ���� ����� ����� ������ �����ϴ°��� ������.
	SI32				siDelSlotNum;

	sDBResponse_LandDelApplyer()
	{
		ZeroMemory(this, sizeof(sDBResponse_LandDelApplyer));
	}
};

//-----------------------------------------
// ������ �Ӵ��Ѵ�. 
//-----------------------------------------
class sDBRequest_LandRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// ��û��.

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siIndex;				// ������ ��ȣ. 
	
	cltRentContract		clRentContract;			// ��� ����. 

	sDBRequest_LandRent()
	{
		ZeroMemory(this, sizeof(sDBRequest_LandRent));
	}

	sDBRequest_LandRent(SI32 id, SI32 villageunique, SI32 personid, SI32 index, cltRentContract* pclcontract)
	{
		packetHeader.usSize = sizeof( sDBRequest_LandRent );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_RENT;

		usCharID		= id;

		siPersonID		= personid;

		siVillageUnique	= villageunique;
		siIndex			= index;

		clRentContract.Set(pclcontract);
	}
};


class sDBResponse_LandRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltSimplePerson		clPerson;			// ��û��.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siIndex;			// ���� ������ �ε��� 

	cltRentContract		clRentContract;		// ��� ����. 

	sDBResponse_LandRent()
	{
		ZeroMemory(this, sizeof(sDBResponse_LandRent));
	}
};



//-----------------------------------------------------
// ������ �Ӵ�Ḧ �����Ѵ�.
//-----------------------------------------------------
class sDBRequest_LandPayRentFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// �Ӵ�Ḧ �����ϴ� ���.

	GMONEY				siRentFee;				// �����ؾ� �� �Ӵ��. 

	SI32				siVillageUnique;		// �Ӵ�Ḧ �ްԵ� ������ ����
	SI32				siLandIndex;			// ����� �Ǵ� ���� ������ �ε���. 



	sDBRequest_LandPayRentFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_LandPayRentFee));
	}

	sDBRequest_LandPayRentFee( SI32 id, SI32 personid, GMONEY rentfee, SI32 villageunique, SI32 landindex)
	{
		packetHeader.usSize = sizeof( sDBRequest_LandPayRentFee );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_PAYRENTFEE;

		usCharID		= id;
		siPersonID		= personid;
		
		siRentFee		= rentfee;

		siVillageUnique	= villageunique;
		siLandIndex	= landindex;
	}

};


class sDBResponse_LandPayRentFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// �Ӵ�Ḧ ������ ���. 
	cltMoney			clBankMoney;		// �������� �����ܰ�.

	GMONEY				siRentFee;			// �����߾�� �� �Ӵ��. 
	SI32				siDelayNum;			// ��ü Ƚ��
	GMONEY				siDelayMoney;		// ��ü�� �հ�. 

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siLandIndex;		// ���� ������ �ε���
	cltMoney			clLandMoney;		// �Ӵ�Ḧ ���� ��� ���� �������� ���� �ڱ�. 

	sDBResponse_LandPayRentFee()
	{
		ZeroMemory( this, sizeof( sDBResponse_LandPayRentFee ) );
	}
};



//-----------------------------------------------------
// ������ ȸ���Ѵ�. 
//-----------------------------------------------------
class sDBRequest_LandRecall
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����(��ü, ��������..)
	
	SI32				siVillageUnique;	// ������ ���� ����ũ
	SI32				siLandIndex;		// ����� �Ǵ� ���� ������ �ε���. 

	sDBRequest_LandRecall()
	{
		ZeroMemory( this, sizeof(sDBRequest_LandRecall) );
	}

	sDBRequest_LandRecall( SI32 personid, SI32 reason, SI32 villageunique, SI32 landindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_LandRecall );
		packetHeader.usCmd	= DBMSG_REQUEST_LAND_RECALL;

		siPersonID		= personid;

		siRecallReason	= reason;

		siVillageUnique	= villageunique;
		siLandIndex	= landindex;
	}

};


class sDBResponse_LandRecall
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����( ��ü, ��� ���� ��..) 
	
	SI32				siVillageUnique;	// ������ ���� ����ũ. 
	SI32				siLandIndex;		// ����� �Ǵ� ���� ������ �ε���. 

	sDBResponse_LandRecall()
	{
		ZeroMemory( this, sizeof(sDBResponse_LandRecall) );
	}
};


#endif