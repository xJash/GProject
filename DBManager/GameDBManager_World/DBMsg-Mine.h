#ifndef _DBMSGMINE_H
#define _DBMSGMINE_H

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Mine\Mine.h"

#define MINERECALL_REASON_FEEDELAY			1	// ��ü�� ���� ȸ�� .
#define MINERECALL_REASON_CONTRACTEND		2	// ��� ����� ���� ȸ��. 

//-----------------------------------------
// ���� ������ ������ ���´�. 
//-----------------------------------------
class sDBRequest_ManyMineUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;

	sDBRequest_ManyMineUnit()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyMineUnit));
	}

	sDBRequest_ManyMineUnit(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_ManyMineUnit );
		packetHeader.usCmd	= DBMSG_REQUEST_MANYMINEUNIT;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};

class sDBResponse_ManyMineUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;								// �����.

	SI32				siVillageUnique;						// ����� �Ǵ� ������ ��ġ�� ������ Unique
	cltMineUnit			clMineUnit[ MAX_MINEUNIT_NUMBER ];		// �� ������ �ִ� ���� ���� ������ ������ ��´�. 	

	sDBResponse_ManyMineUnit()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyMineUnit));
	}
};


//-----------------------------------------
// ������ ��� ������ �����ϵ��� �Ѵ�. 
//-----------------------------------------
class sDBRequest_MineChangeContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	cltRentContract		clContract;				// ��� ����
	
	cltDate				clDate;					// ��� ������

	sDBRequest_MineChangeContract()
	{
		ZeroMemory(this, sizeof(sDBRequest_MineChangeContract));
	}

	sDBRequest_MineChangeContract(SI32 id, SI32 villageunique, cltRentContract* pclcontract, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_MineChangeContract );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_CHANGECONTRACT;

		usCharID		= id;
		siVillageUnique	= villageunique;

		clContract.Set(pclcontract);
		clDate.Set( pclDate );
	}
};


class sDBResponse_MineChangeContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;				// �����.

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	cltRentContract		clContract;				// ����� ��� ����

	cltDate				clDate;					// ��� ������

	sDBResponse_MineChangeContract()
	{
		ZeroMemory(this, sizeof(sDBResponse_MineChangeContract));
	}
};



//-----------------------------------------
// ���� ���� ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_MineRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siPersonID;				// ��û��.
	
	cltRentContract		clContract;				// �������

	sDBRequest_MineRentApply()
	{
		ZeroMemory(this, sizeof(sDBRequest_MineRentApply));
	}

	sDBRequest_MineRentApply( SI32 id, SI32 villageunique, SI32 personid, cltRentContract* pclcontract )
	{
		packetHeader.usSize = sizeof( sDBRequest_MineRentApply );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_RENTAPPLY;

		usCharID		= id;
		siVillageUnique	= villageunique;
		siPersonID		= personid;

		clContract.Set(pclcontract);
	}
};


class sDBResponse_MineRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	
	SI32				siIndex;			// ���� ������� ������ ��� ��ġ�� ����Ų��.
	cltSimplePerson		clApplyer;			// ���� ����� ������ ��´�. 

	cltRentContract		clContract;			// ������� ��� ������ ��´�. 

	sDBResponse_MineRentApply()
	{
		ZeroMemory(this, sizeof(sDBResponse_MineRentApply));
	}
};


//-----------------------------------------
// ���� ���� ��û�� ����Ѵ�. 
//-----------------------------------------
class sDBRequest_MineCancelRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ��û��.
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����

	sDBRequest_MineCancelRentApply()
	{
		ZeroMemory( this, sizeof( sDBRequest_MineCancelRentApply ) );
	}

	sDBRequest_MineCancelRentApply( SI32 id, SI32 villageunique, SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_MineCancelRentApply );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_CANCELRENTAPPLY;

		usCharID		= id;

		siVillageUnique	= villageunique;
		siPersonID		= personid;
	}
};


class sDBResponse_MineCancelRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siPersonID;

	sDBResponse_MineCancelRentApply()
	{
		ZeroMemory( this, sizeof(sDBResponse_MineCancelRentApply) );
	}
};


//-----------------------------------------
// ���� ����� ����� ���´�. 
//-----------------------------------------
class sDBRequest_MineApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique; // ����� �Ǵ� ������ ��ġ�� ������ Unique

	sDBRequest_MineApplyerList()
	{
		ZeroMemory(this, sizeof(sDBRequest_MineApplyerList) );
	}

	sDBRequest_MineApplyerList(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_MineApplyerList );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_APPLYERLIST;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};


class sDBResponse_MineApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;							// �����.

	SI32				siVillageUnique;					// ����� �Ǵ� ������ ��ġ�� ����
	cltRentApplyer		clApplyer[ MAX_APPLY_PER_MINE ];	// ���� ����� ����� ��´�. 

	sDBResponse_MineApplyerList()
	{
		ZeroMemory(this, sizeof(sDBResponse_MineApplyerList) );
	}
};


//-----------------------------------------------------
// ���� ������� ����� ��� �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_MineDelApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;

	// [�߰� : Ȳ���� 2007. 11. 2 �α׿� �̿�. ���� ����� ����� ������ �����ϴ� ���� ����.]
	SI32				siDelSlotNum;

	sDBRequest_MineDelApplyer()
	{
		ZeroMemory( this, sizeof(sDBRequest_MineDelApplyer) );
	}

	// [�߰� : Ȳ���� 2007. 11. 2 �α׿� �̿�. ���� ����� ����� ������ �����ϴ� ���� ����.]
	sDBRequest_MineDelApplyer( SI32 id, SI32 personid, SI32 villageunique, SI32 DelSlotNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_MineDelApplyer );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_DELAPPLYER;

		usCharID		= id;
		siPersonID		= personid;
		siVillageUnique	= villageunique;
		
		// [�߰� : Ȳ���� 2007. 11. 2 �α׿� �̿�. ���� ����� ����� ������ �����ϴ� ���� ����.]
		siDelSlotNum    = DelSlotNum;
	}

};


class sDBResponse_MineDelApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;		

	SI32				siPersonID;			
	SI32				siVillageUnique;

	// [�߰� : Ȳ���� 2007. 11. 2 �α׿� �̿�. ���� ����� ����� ������ �����ϴ� ���� ����.]
	SI32				siDelSlotNum;

	sDBResponse_MineDelApplyer()
	{
		ZeroMemory(this, sizeof(sDBResponse_MineDelApplyer));
	}
};

//-----------------------------------------
// ������ �Ӵ��Ѵ�. 
//-----------------------------------------
class sDBRequest_MineRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// ��û��.

	SI32				siVillageUnique;		// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siIndex;				// ������ ��ȣ. 
	
	cltRentContract		clRentContract;			// ��� ����. 

	sDBRequest_MineRent()
	{
		ZeroMemory(this, sizeof(sDBRequest_MineRent));
	}

	sDBRequest_MineRent(SI32 id, SI32 villageunique, SI32 personid, SI32 index, cltRentContract* pclcontract)
	{
		packetHeader.usSize = sizeof( sDBRequest_MineRent );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_RENT;

		usCharID		= id;

		siPersonID		= personid;

		siVillageUnique	= villageunique;
		siIndex			= index;

		clRentContract.Set(pclcontract);
	}
};


class sDBResponse_MineRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltSimplePerson		clPerson;			// ��û��.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ����
	SI32				siIndex;			// ���� ������ �ε��� 

	cltRentContract		clRentContract;		// ��� ����. 

	sDBResponse_MineRent()
	{
		ZeroMemory(this, sizeof(sDBResponse_MineRent));
	}
};



//-----------------------------------------------------
// ������ �Ӵ�Ḧ �����Ѵ�.
//-----------------------------------------------------
class sDBRequest_MinePayRentFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;				// �Ӵ�Ḧ �����ϴ� ���.

	GMONEY				siRentFee;				// �����ؾ� �� �Ӵ��. 

	SI32				siVillageUnique;		// �Ӵ�Ḧ �ްԵ� ������ ����
	SI32				siMineIndex;			// ����� �Ǵ� ���� ������ �ε���. 



	sDBRequest_MinePayRentFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_MinePayRentFee));
	}

	sDBRequest_MinePayRentFee( SI32 id, SI32 personid, GMONEY rentfee, SI32 villageunique, SI32 Mineindex)
	{
		packetHeader.usSize = sizeof( sDBRequest_MinePayRentFee );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_PAYRENTFEE;

		usCharID		= id;
		siPersonID		= personid;
		
		siRentFee		= rentfee;

		siVillageUnique	= villageunique;
		siMineIndex	= Mineindex;
	}

};


class sDBResponse_MinePayRentFee
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
	SI32				siMineIndex;		// ���� ������ �ε���
	cltMoney			clMineMoney;		// �Ӵ�Ḧ ���� ��� ���� �������� ���� �ڱ�. 

	sDBResponse_MinePayRentFee()
	{
		ZeroMemory( this, sizeof( sDBResponse_MinePayRentFee ) );
	}
};



//-----------------------------------------------------
// ������ ȸ���Ѵ�. 
//-----------------------------------------------------
class sDBRequest_MineRecall
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����(��ü, ��������..)
	
	SI32				siVillageUnique;	// ������ ���� ����ũ
	SI32				siMineIndex;		// ����� �Ǵ� ���� ������ �ε���. 

	sDBRequest_MineRecall()
	{
		ZeroMemory( this, sizeof(sDBRequest_MineRecall) );
	}

	sDBRequest_MineRecall( SI32 personid, SI32 reason, SI32 villageunique, SI32 Mineindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_MineRecall );
		packetHeader.usCmd	= DBMSG_REQUEST_MINE_RECALL;

		siPersonID		= personid;

		siRecallReason	= reason;

		siVillageUnique	= villageunique;
		siMineIndex	= Mineindex;
	}

};


class sDBResponse_MineRecall
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����( ��ü, ��� ���� ��..) 
	
	SI32				siVillageUnique;	// ������ ���� ����ũ. 
	SI32				siMineIndex;		// ����� �Ǵ� ���� ������ �ε���. 

	sDBResponse_MineRecall()
	{
		ZeroMemory( this, sizeof(sDBResponse_MineRecall) );
	}
};

#endif