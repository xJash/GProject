#ifndef _DBMSGHOUSE_H
#define _DBMSGHOUSE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\House\House.h"

//-----------------------------------------------------
// ���� â���� Ư�� ��ġ�� ���� ������ ��û�Ѵ�. 
//-----------------------------------------------------
class sDBRequest_GetHouseStgPos
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Person
	SI32				siPersonID;			// ������ ����� ���. 

	// House
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?
	SI16				siStgPos;			// ����� �Ǵ� â�� ��ġ. 

	sDBRequest_GetHouseStgPos()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetHouseStgPos));
	}

	sDBRequest_GetHouseStgPos(SI32 id, SI32 personid, 
						SI32 villageunique, SI32 houseunitslot, SI32 stgpos)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetHouseStgPos );
		packetHeader.usCmd	= DBMSG_REQUEST_GETHOUSESTGPOS;

		usCharID		= id;

		siPersonID		= personid;

		siVillageUnique	= villageunique;
		siHouseUnitSlot	= houseunitslot;
		siStgPos		= stgpos;

	}
};


class sDBResponse_GetHouseStgPos
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// Person
	SI32				siPersonID;			// ������ ����� ���. 

	// House
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?
	SI16				siStgPos;			// ����� �Ǵ� â�� ��ġ. 

	// Output
	cltItem				clItem;				// ����ǰ�� ����. (���� ����. ) 

	sDBResponse_GetHouseStgPos()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetHouseStgPos));
	}
};


//-----------------------------------------------------
// ���� ������� ����� ��� �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_DelHouseApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;			// ������ ����� ���. 

	// where
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique

	// PCK : ���� ����� ����� ������ �����ϴ°��� ������.
	SI32				siDelSlotNum;

	sDBRequest_DelHouseApplyer()
	{
		ZeroMemory(this, sizeof(sDBRequest_DelHouseApplyer));
	}

	sDBRequest_DelHouseApplyer(SI32 id, SI32 personid, SI32 villageunique, SI32 delSlotNum)
	{
		packetHeader.usSize = sizeof( sDBRequest_DelHouseApplyer );
		packetHeader.usCmd	= DBMSG_REQUEST_DELHOUSEAPPLYER;

		usCharID		= id;

		siPersonID		= personid;

		siVillageUnique	= villageunique;
		siDelSlotNum	= delSlotNum;
	}

};


class sDBResponse_DelHouseApplyer
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;			// ������ ����� ���. 

	// where
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique

	// PCK : ���� ����� ����� ������ �����ϴ°��� ������.
	SI32				siDelSlotNum;

	sDBResponse_DelHouseApplyer()
	{
		ZeroMemory(this, sizeof(sDBResponse_DelHouseApplyer));
	}
};


//-----------------------------------------------------
// ������ �Ӵ�Ḧ �����Ѵ�. 
//-----------------------------------------------------
class sDBRequest_PayRentFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who
	SI32				siPersonID;			// �Ӵ�Ḧ �����ϴ� ���.
	GMONEY				siRentFee;			// �����ؾ� �� �Ӵ��. 

	//whom				
	SI32				siVillageUnique;	// �Ӵ�Ḧ �ްԵ� ������ ���� ����ũ. 

	// for what
	SI32				siHouseIndex;		// ����� �Ǵ� ���� ������ �ε���. 

	sDBRequest_PayRentFee()
	{
		ZeroMemory(this, sizeof(sDBRequest_PayRentFee));
	}

	sDBRequest_PayRentFee(SI32 id, SI32 personid, GMONEY rentfee, SI32 villageunique, SI32 houseindex)
	{
		packetHeader.usSize = sizeof( sDBRequest_PayRentFee );
		packetHeader.usCmd	= DBMSG_REQUEST_PAYRENTFEE;

		usCharID		= id;

		siPersonID		= personid;

		siRentFee		= rentfee;

		siVillageUnique	= villageunique;

		siHouseIndex	= houseindex;
	}

};


class sDBResponse_PayRentFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;			// �Ӵ�Ḧ ������ ���. 
	GMONEY				siBankMoney;		// �������� �����ܰ�.
	GMONEY				siRentFee;			// �����߾�� �� �Ӵ��. 
	SI32				siDelayNum;			// ��ü Ƚ��
	GMONEY				siDelayMoney;		// ��ü�� �հ�. 

	// for what
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseIndex;
	GMONEY				siHouseMoney;		// �Ӵ�Ḧ �޾Ƽ� ��� ������ ���� �ڱ�. 

	sDBResponse_PayRentFee()
	{
		ZeroMemory(this, sizeof(sDBResponse_PayRentFee));
	}
};



//-----------------------------------------------------
// ������ ȸ���Ѵ�. 
//-----------------------------------------------------
class sDBRequest_RecallHouse
{
public:
	sPacketHeader		packetHeader;

	// who
	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����(��ü, ��������..) 

	//whom				
	SI32				siVillageUnique;	// ������ ���� ����ũ. 

	// for what
	SI32				siHouseIndex;		// ����� �Ǵ� ���� ������ �ε���. 
	
	GMONEY				siPenaltyMoney;
	
	//cltMoney			clPenaltyMoney;
	TCHAR				szOwnerName[MAX_PLAYER_NAME];


	sDBRequest_RecallHouse()
	{
		ZeroMemory(this, sizeof(sDBRequest_RecallHouse));
	}

	sDBRequest_RecallHouse(SI32 personid, SI32 reason, SI32 villageunique, SI32 houseindex, GMONEY penaltyMoney = 0, const TCHAR* ownerName = NULL)
	{
		packetHeader.usSize = sizeof( sDBRequest_RecallHouse );
		packetHeader.usCmd	= DBMSG_REQUEST_RECALLHOUSE;

		siPersonID		= personid;

		siRecallReason	= reason;

		siVillageUnique	= villageunique;

		siHouseIndex	= houseindex;

		siPenaltyMoney = penaltyMoney;
		
        MStrCpy(szOwnerName, ownerName, MAX_PLAYER_NAME);
	}

};


class sDBResponse_RecallHouse
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	// who
	SI32				siPersonID;			// ������. 

	SI32				siRecallReason;		// ȸ�� ����(��ü, ��������..) 

	//whom				
	SI32				siVillageUnique;	// ������ ���� ����ũ. 

	// for what
	SI32				siHouseIndex;		// ����� �Ǵ� ���� ������ �ε���. 
	
	GMONEY				siPenaltyMoney;		// ������ ������ �����
	GMONEY				siRemainMoney;		// ������ ������
	GMONEY				siHouseMoney;		// �ؾ���� ���� ������ ���� �ڻ�
	
	TCHAR				szOwnerName[MAX_PLAYER_NAME];

//	cltMoney				clPenaltyMoney;
//	cltMoney				clRemainMoney;		
//  cltMoney				clHouseMoney

	sDBResponse_RecallHouse()
	{
		ZeroMemory(this, sizeof(sDBResponse_RecallHouse));
	}
};


//-----------------------------------------
// ������ �Ӵ��Ѵ�. 
//-----------------------------------------
class sDBRequest_HouseRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siPersonID;			// ��û��.
	SI32				siIndex;			// ������ ��ȣ. 
	cltRentContract		clRentContract;		// ��� ����. 
	TCHAR				m_szCharName[MAX_PLAYER_NAME];

	sDBRequest_HouseRent()
	{
		ZeroMemory(this, sizeof(sDBRequest_HouseRent));
	}

	sDBRequest_HouseRent(SI32 id, SI32 villageunique, SI32 personid, SI32 index, cltRentContract* pclcontract , TCHAR* pszCharName)
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseRent );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSERENT;

		usCharID		= id;
		siVillageUnique	= villageunique;
		siPersonID		= personid;
		siIndex			= index;

		clRentContract.Set(pclcontract);

		_tcscpy(m_szCharName, pszCharName);
	}
};


class sDBResponse_HouseRent
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	cltSimplePerson		clPerson;			// ��û��.
	SI32				siIndex;			// ������ ��ȣ. 
	cltRentContract		clRentContract;		// ��� ����. 

	SI32				siApplyerIndex;		// ��û�� ������ ��ġ. 
	cltRentApplyer		clApplyer;			// ��û�� ����. 
	
	TCHAR				m_szName[MAX_PLAYER_NAME];

	sDBResponse_HouseRent()
	{
		ZeroMemory(this, sizeof(sDBResponse_HouseRent));
	}
};



//-------------------------
// �ε��� ����� �����Ѵ�. 
//-------------------------
class sDBRequest_ExtendContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// ��û��.

	SI32				siVillageUnique;	// ����� �Ǵ� �ε����� ��ġ�� ������ Unique
	SI32				siRealEstateType;	// �ε����� ����.(REALESTATE_HOUSE.._)  
	SI32				siIndex;			// �ε����� ��ȣ. 
	cltRentContract		clRentContract;		// ��� ����. 

	sDBRequest_ExtendContract()
	{
		ZeroMemory(this, sizeof(sDBRequest_ExtendContract));
	}

	sDBRequest_ExtendContract(SI32 id, SI32 personid, SI32 villageunique, SI32 realestatetype, SI32 index, cltRentContract* pclcontract)
	{
		packetHeader.usSize = sizeof( sDBRequest_ExtendContract );
		packetHeader.usCmd	= DBMSG_REQUEST_EXTENDCONTRACT;

		usCharID			= id;
	
		siPersonID			= personid;
		siVillageUnique		= villageunique;
		siRealEstateType	= realestatetype;
		siIndex				= index;
		clRentContract.Set(pclcontract);
	}
};


class sDBResponse_ExtendContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	cltSimplePerson		clPerson;			// ��û��.

	SI32				siVillageUnique;	// ����� �Ǵ� �ε����� ��ġ�� ������ Unique
	SI32				siRealEstateType;	// �ε����� ����.(REALESTATE_HOUSE.._)  
	SI32				siIndex;			// �ε����� ��ȣ. 
	cltRentContract		clRentContract;		// ��� ����. 
	GMONEY				siBankMoney;		// ��࿬���� ���� �Ӵ�� �����ϰ� ���� ������ ���� �ܾ�. 

	sDBResponse_ExtendContract()
	{
		ZeroMemory(this, sizeof(sDBResponse_ExtendContract));
	}
};

//-------------------------
// â�� �̸� ���� 
//-------------------------
class sDBRequest_ChangeHouseUnitName
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;			// ��û��.

	SI32				m_siVillageUnique;		// ����� �Ǵ� �ε����� ��ġ�� ������ Unique
	SI32				m_siIndex;				// �ε����� ��ȣ. 
	TCHAR				m_szName[MAX_PLAYER_NAME]; // â�� �̸�				

	sDBRequest_ChangeHouseUnitName()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeHouseUnitName));
	}

	sDBRequest_ChangeHouseUnitName(SI32 id, SI32 personid, SI32 villageunique, SI32 index, TCHAR* pszName)
	{
		m_packetHeader.usSize = sizeof( sDBRequest_ChangeHouseUnitName );
		m_packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITNAMECHANGE;

		m_usCharID			= id;

		m_siPersonID			= personid;
		m_siVillageUnique		= villageunique;
		m_siIndex				= index;
		_tcscpy( m_szName , pszName);
	}
};


class sDBResponse_ChangeHouseUnitName
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;			// �����.

	SI32				m_siPersonID;			// ��û��.

	SI32				m_siVillageUnique;		// ����� �Ǵ� �ε����� ��ġ�� ������ Unique
	SI32				m_siIndex;				// �ε����� ��ȣ. 
	TCHAR				m_szName[MAX_PLAYER_NAME]; // â�� �̸�				

	sDBResponse_ChangeHouseUnitName()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeHouseUnitName));
	}
};

//-----------------------------------------
// ������ ��� ������ �����ϵ��� �Ѵ�. 
//-----------------------------------------
class sDBRequest_ChangeHouseContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;// ����� �Ǵ� ������ ��ġ�� ������ Unique
	cltRentContract		clContract;		// ��� ����.
	cltDate				clDate;			// ��� ������

	sDBRequest_ChangeHouseContract()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeHouseContract));
	}

	sDBRequest_ChangeHouseContract(SI32 id, SI32 villageunique, cltRentContract* pclcontract, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeHouseContract );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGEHOUSECONTRACT;

		usCharID		= id;
		siVillageUnique	= villageunique;

		clContract.Set(pclcontract);
		clDate.Set( pclDate );
	}
};


class sDBResponse_ChangeHouseContract
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;// ����� �Ǵ� ������ ��ġ�� ������ Unique
	cltRentContract		clContract;		// ����� ��� ����.

	cltDate				clDate;			// ��� ������

	sDBResponse_ChangeHouseContract()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeHouseContract));
	}
};

//-----------------------------------------
// ���� ������ ������ ���´�. 
//-----------------------------------------
class sDBRequest_ManyHouseUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique; // ����� �Ǵ� ������ ��ġ�� ������ Unique

	sDBRequest_ManyHouseUnit()
	{
		ZeroMemory(this, sizeof(sDBRequest_ManyHouseUnit));
	}

	sDBRequest_ManyHouseUnit(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_ManyHouseUnit );
		packetHeader.usCmd	= DBMSG_REQUEST_MANYHOUSEUNIT;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};

#define MANYHOUSEUNIT_NUMBER	20
class sDBResponse_ManyHouseUnit
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;								// �����.

	SI32				siVillageUnique;						// ����� �Ǵ� ������ ��ġ�� ������ Unique
	
	SI32				siStartIndex;
	cltHouseUnit		clHouseUnit[MANYHOUSEUNIT_NUMBER];		// �� ������ �ִ� ���� ���� ������ ������ ��´�. 	

	sDBResponse_ManyHouseUnit()
	{
		ZeroMemory(this, sizeof(sDBResponse_ManyHouseUnit));
	}
};


//-----------------------------------------
// ���� ����� ����� ���´�. 
//-----------------------------------------
class sDBRequest_GetHouseApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique; // ����� �Ǵ� ������ ��ġ�� ������ Unique

	sDBRequest_GetHouseApplyerList()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetHouseApplyerList));
	}

	sDBRequest_GetHouseApplyerList(SI32 id, SI32 villageunique)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetHouseApplyerList );
		packetHeader.usCmd	= DBMSG_REQUEST_GETHOUSEAPPLYERLIST;

		usCharID		= id;
		siVillageUnique	= villageunique;
	}
};


class sDBResponse_GetHouseApplyerList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	
	cltRentApplyer		clApply[MAX_APPLY_PER_HOUSE];	// ���� ����� ����� ��´�. 

	sDBResponse_GetHouseApplyerList()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetHouseApplyerList));
	}
};

//-----------------------------------------
// ���� ������ ��û�Ѵ�. 
//-----------------------------------------
class sDBRequest_HouseRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siPersonID;			// ��û��.
	
	cltRentContract		clContract;

	sDBRequest_HouseRentApply()
	{
		ZeroMemory(this, sizeof(sDBRequest_HouseRentApply));
	}

	sDBRequest_HouseRentApply(SI32 id, SI32 villageunique, SI32 personid, cltRentContract* pclcontract)
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseRentApply );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSERENTAPPLY;

		usCharID		= id;
		siVillageUnique	= villageunique;
		siPersonID		= personid;
		clContract.Set(pclcontract);
	}
};


class sDBResponse_HouseRentApply
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	
	SI32				siIndex;			// ���� ������� ������ ��� ��ġ�� ����Ų��.
	cltSimplePerson		clApply;			// ���� ����� ������ ��´�. 

	cltRentContract		clContract;			// ������� ��� ������ ��´�. 
	sDBResponse_HouseRentApply()
	{
		ZeroMemory(this, sizeof(sDBResponse_HouseRentApply));
	}
};


//-----------------------------------------
// ���� ���� ��û�� ����Ѵ�. 
//-----------------------------------------
class sDBRequest_HouseRentApplyCancel
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// who 
	SI32				siPersonID;			// ��û��.

	// where
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique

	sDBRequest_HouseRentApplyCancel()
	{
		ZeroMemory(this, sizeof(sDBRequest_HouseRentApplyCancel));
	}

	sDBRequest_HouseRentApplyCancel(SI32 id, SI32 villageunique, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseRentApplyCancel );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSERENTAPPLYCANCEL;

		usCharID		= id;

		siVillageUnique	= villageunique;
		siPersonID		= personid;
	}
};


class sDBResponse_HouseRentApplyCancel
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	
	SI32				siIndex;			// ���� ������� ������ ��� ��ġ�� ����Ų��.
	cltRentApplyer		clApply;			// ���� ����� ������ ��´�. 

	sDBResponse_HouseRentApplyCancel()
	{
		ZeroMemory(this, sizeof(sDBResponse_HouseRentApplyCancel));
	}
};

//-----------------------------------------
//  �������� �κ��丮���� â��� �ű��. 
//-----------------------------------------
class sDBRequest_MoveItemInvToStg
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// �κ��丮�� ��ġ. 

	// to 
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?
	SI16				siStgPos;			// ���� ���ó� ��ġ. 

	// what
	cltItem				clItem;
	bool				bCanPileSwitch;


	sDBRequest_MoveItemInvToStg()
	{
		ZeroMemory(this, sizeof(sDBRequest_MoveItemInvToStg));
	}

	sDBRequest_MoveItemInvToStg(SI32 id, SI32 personid, SI32 invpos, SI32 villageunique, SI32 houseunitslot, SI32 stgpos, cltItem* pclitem, bool bcanpileswitch)
	{
		packetHeader.usSize = sizeof( sDBRequest_MoveItemInvToStg );
		packetHeader.usCmd	= DBMSG_REQUEST_MOVEITEMINVTOSTG;

		usCharID		= id;

		siPersonID		= personid;
		siInvPos		= invpos;

		siVillageUnique	= villageunique;
		siHouseUnitSlot	= houseunitslot;
		siStgPos		= stgpos;

		clItem.Set(pclitem);
		bCanPileSwitch	= bcanpileswitch;
	}
};


class sDBResponse_MoveItemInvToStg
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// from
	SI32				siPersonID;
	SI16				siInvPos;
	cltItem				clInvItem;

	// to 
	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;
	SI16				siStgPos;
	cltItem				clStgItem;
	
	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� ���. �κ����� â��� �̵��ϴ� ������ ����]
	cltItem				clMoveItem;

	sDBResponse_MoveItemInvToStg()
	{
		ZeroMemory(this, sizeof(sDBResponse_MoveItemInvToStg));
	}
};


//-----------------------------------------
//  �������� â���� �κ��丮�� �ű��. 
//-----------------------------------------
class sDBRequest_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// from 
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?
	SI16				siStgPos;			// ���� ���ó� ��ġ. 

	// to 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;
	bool				bCanPileSwitch;


	sDBRequest_MoveItemStgToInv()
	{
		ZeroMemory(this, sizeof(sDBRequest_MoveItemStgToInv));
	}

	sDBRequest_MoveItemStgToInv(SI32 id, SI32 villageunique, SI32 houseunitslot, SI32 stgpos, SI32 personid, SI32 invpos, cltItem* pclitem, bool bcanpileswitch)
	{
		packetHeader.usSize = sizeof( sDBRequest_MoveItemStgToInv );
		packetHeader.usCmd	= DBMSG_REQUEST_MOVEITEMSTGTOINV;

		usCharID		= id;

		siVillageUnique	= villageunique;
		siHouseUnitSlot	= houseunitslot;
		siStgPos		= stgpos;

		siPersonID		= personid;
		siInvPos		= invpos;

		clItem.Set(pclitem);
		bCanPileSwitch	= bcanpileswitch;
	}
};


class sDBResponse_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// from
	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;
	SI16				siStgPos;
	cltItem				clStgItem;

	// to 
	SI32				siPersonID;
	SI16				siInvPos;
	cltItem				clInvItem;

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� ���. â���� �κ��� �̵��ϴ� ������ ����]
	cltItem				clMoveItem;

	sDBResponse_MoveItemStgToInv()
	{
		ZeroMemory(this, sizeof(sDBResponse_MoveItemStgToInv));
	}
};



class sDBRequest_MakeItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	// Person
	SI32				siPersonID;			// ������ ����� ���. 

	// House
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?

	// Material 
	DBMaterialInfo		clMaterial[MAX_MATERIAL_NUMBER];

	// Output
	SI16				siOutputPos;		// ����ǰ�� ��ġ�� ����. 
	cltItem				clItem;				// ����ǰ�� ����. (���� ����. ) 
	bool				bCanPileSwitch;		// ����ǰ�� ���������Ѱ� ?
	bool				bAlmostFailSwitch;	// ���� ������ ��ǰ�ΰ� ?

	sDBRequest_MakeItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_MakeItem));
	}

	sDBRequest_MakeItem(SI32 id, SI32 personid, 
						SI32 villageunique, SI32 houseunitslot, 
						DBMaterialInfo* pclinfo, 
						SI32 outputpos, cltItem* pclitem, bool bcanpileswitch, bool balmostfailswitch)
	{
		packetHeader.usSize = sizeof( sDBRequest_MakeItem );
		packetHeader.usCmd	= DBMSG_REQUEST_MAKEITEM;

		usCharID		= id;

		siPersonID		= personid;

		siVillageUnique	= villageunique;
		siHouseUnitSlot	= houseunitslot;

		for(SI32 i = 0;i < MAX_MATERIAL_NUMBER;i++)
		{
			clMaterial[i].Set(&pclinfo[i]);
		}

		siOutputPos	= outputpos;
		clItem.Set(pclitem);
		bCanPileSwitch		= bcanpileswitch;
		bAlmostFailSwitch	= balmostfailswitch;
	}
};


class sDBResponse_MakeItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	// Person
	SI32				siPersonID;			// ������ ����� ���. 

	// House
	SI32				siVillageUnique;	// ����� �Ǵ� ������ ��ġ�� ������ Unique
	SI32				siHouseUnitSlot;	// ������ � ���������ΰ� ?

	// Output
	SI16				siOutputPos;		// ����ǰ�� ��ġ�� ����. 
	SI16				siAddedNum;			// �߰��� ������ ����. 
	cltItem				clItem;				// ����ǰ�� ����. (���� ����. ) 
	bool				bAlmostFailSwitch;	// ���� ������ ��ǰ�ΰ� ?

	sDBResponse_MakeItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_MakeItem));
	}
};

class sDBRequest_HouseUnitStableCreate
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	GMONEY				siHouseUnitStableCreateFee;
	//SI16				siItemPos;
	//cltItem			clItem;

	SI16				siStableIndex;

	sDBRequest_HouseUnitStableCreate( SI32 CharID, SI32 PersonID,
		SI32 VillageUnique, SI32 HouseUnitSlot,
		GMONEY HouseUnitStableCreateFee,  SI16 StableIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitStableCreate );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSTABLECREATE;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siHouseUnitStableCreateFee = HouseUnitStableCreateFee;
		//siItemPos = ItemPos;
		//clItem.Set( pclItem );


		siStableIndex = StableIndex;
	}
};

class sDBResponse_HouseUnitStableCreate
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	GMONEY				siHouseUnitStableCreateFee;
	//cltMoney			clLeftHouseUnitMoney;
	//SI32				siPersonLeftMoney;

	//SI16				siItemPos;
	//cltItem			clLeftItem;

	SI16				siStableIndex;

	sDBResponse_HouseUnitStableCreate()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitStableCreate ) );
	}
};

class sDBRequest_HouseUnitHorseIn
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siPersonHorseIndex;
	SI16				siHouseUnitStgHorseIndex;
	
	//SI32				siHouseUnitHorseInFee;
	
	sDBRequest_HouseUnitHorseIn( SI32 CharID, SI32 PersonID,
		SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 PersonHorseIndex, SI16 HouseUnitStgHorseIndex )//, SI32 HouseUnitHorseInFee )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitHorseIn );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITHORSEIN;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siPersonHorseIndex = PersonHorseIndex;
		siHouseUnitStgHorseIndex = HouseUnitStgHorseIndex;

		//siHouseUnitHorseInFee = HouseUnitHorseInFee;
	}
};

class sDBResponse_HouseUnitHorseIn
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siPersonHorseIndex;
	cltHorse			clPersonHorse;

	SI16				siHouseUnitStgHorseIndex;
	cltHorse			clHouseUnitStgHorse;

	sDBResponse_HouseUnitHorseIn()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitHorseIn ) );
	}	
};


class sDBRequest_HouseUnitHorseOut
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siHouseUnitStgHorseIndex;

	SI16				siPersonHorseIndex;	

	sDBRequest_HouseUnitHorseOut( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 HouseUnitStgHorseIndex, SI16 PersonHorseIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitHorseIn );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITHORSEOUT;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siHouseUnitStgHorseIndex = HouseUnitStgHorseIndex;

		siPersonHorseIndex = PersonHorseIndex;		
	}
	
};

class sDBResponse_HouseUnitHorseOut
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siHouseUnitStgHorseIndex;
	cltHorse			clHouseUnitHorse;
	
	SI16				siPersonHorseIndex;
	cltHorse			clPersonHorse;

	sDBResponse_HouseUnitHorseOut()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitHorseOut ) );
	}
};

class sDBRequest_HouseUnitHorseInfoSet
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siHouseUnitHorseIndex;
	cltHorse			clHouseUnitHorseInfo;

	sDBRequest_HouseUnitHorseInfoSet( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 HouseUnitHorseIndex, cltHorse *pclHouseUnitHorseInfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitHorseInfoSet );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITHORSEINFOSET;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siHouseUnitHorseIndex = HouseUnitHorseIndex;
		clHouseUnitHorseInfo.Set( pclHouseUnitHorseInfo );
	}	
};

class sDBResponse_HouseUnitHorseInfoSet
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siHouseUnitHorseIndex;
	cltHorse			clHouseUnitHorseInfo;

	sDBResponse_HouseUnitHorseInfoSet()
	{
		memset ( this, 0, sizeof( sDBResponse_HouseUnitHorseInfoSet ) );
	}
};


class sDBRequest_HouseUnitHorseEatFood
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siHouseUnitItemIndex;
	
	SI16				siHouseUnitHorseEatItemUnique;
	SI16				siHouseUnitHorseEatItemNum;

	sDBRequest_HouseUnitHorseEatFood( SI32 CharID, SI32 PersonID, SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 HouseUnitItemIndex, SI16 HouseUnitHorseEatItemUnique, SI16 HouseUnitHorseEatItemNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitHorseEatFood );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITHORSEEATFOOD;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siHouseUnitItemIndex = HouseUnitItemIndex;
		
		siHouseUnitHorseEatItemUnique = HouseUnitHorseEatItemUnique;
		siHouseUnitHorseEatItemNum = HouseUnitHorseEatItemNum;
	}
};

class sDBResponse_HouseUnitHorseEatFood
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;
	
	SI16				siHouseUnitHorseEatItemUnique;
	SI16				siHouseUnitHorseEatItemNum;

	SI16				siHouseUnitItemIndex;
	cltItem				clHouseUnitItem;

	sDBResponse_HouseUnitHorseEatFood()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitHorseEatFood ) );
	}

};

class sDBRequest_HouseUnitUsedGoodsBuildingCreate
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siItemPos;				// �Һ��� �̿���� ���� �κ� ��ġ
	cltItem				clItem;					// �Һ��� �̿�� ������ ����

	sDBRequest_HouseUnitUsedGoodsBuildingCreate( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 ItemPos, cltItem *pclItem )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitUsedGoodsBuildingCreate );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITUSEDGOODSBUILDINGCREATE;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siItemPos = ItemPos;
		clItem.Set( pclItem );
	}
};

class sDBResponse_HouseUnitUsedGoodsBuildingCreate
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;				// 1 : ����, Others : ����

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siItemPos;				// �Һ�� �̿���� ���� �κ� ��ġ
	cltItem				clLeftItem;				// �Һ��ϰ� ���� ���� �κ� ����

	sDBResponse_HouseUnitUsedGoodsBuildingCreate()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitUsedGoodsBuildingCreate ));
	}
};

class sDBRequest_HouseUnitMakeItemFromUsedGoods
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	// ���� ������
	SI16				siFromHoustUnitStgItemPos;			// �� ������ ��ġ ( ������ ������ ��ġ�� )
	SI16				siFromHouseUnitItemUnique;			// �� ������ Unique
	
	// ���� ������
	SI16				siToHouseUnitStgItemPos[ MAX_MATERIAL_NUMBER ];
	cltItem				clMakeItem[ MAX_MATERIAL_NUMBER ];

	SI16				siMakePercent;

	sDBRequest_HouseUnitMakeItemFromUsedGoods( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 FromHoustUnitStgItemPos, SI16 FromHouseUnitItemUnique,
		SI16 *ToHoustUnitStgItemPos, cltItem *pclMakeItem,
		SI16 MakePercent
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitMakeItemFromUsedGoods );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITMAKEITEMFROMUSEDGOODS;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siFromHoustUnitStgItemPos = FromHoustUnitStgItemPos;
		siFromHouseUnitItemUnique = FromHouseUnitItemUnique;

		memcpy( siToHouseUnitStgItemPos, ToHoustUnitStgItemPos, sizeof( SI16 ) * MAX_MATERIAL_NUMBER );
		memcpy( clMakeItem, pclMakeItem, sizeof( cltItem ) * MAX_MATERIAL_NUMBER );

		siMakePercent = MakePercent;
	}
};

class sDBResponse_HouseUnitMakeItemFromUsedGoods
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siFromItemPos;				// ����� �� �������� ��ġ
	SI16				siFromItemUnique;			// ����� �� ������ Unique

	// ����� ������ ���� ������ ��
	SI16				siToHouseUnitStgItemPos[ MAX_MATERIAL_NUMBER ];		// ������� ���� ������ ��ġ
	cltItem				clMakeLeftItem[ MAX_MATERIAL_NUMBER ];					// ������ ��ġ�� ���� ������

	SI16				siMakePercent;

	sDBResponse_HouseUnitMakeItemFromUsedGoods()
	{
		memset( this, 0, sizeof ( sDBResponse_HouseUnitMakeItemFromUsedGoods ) );

		for( SI16 i = 0; i < MAX_MATERIAL_NUMBER; ++i )
		{
			siToHouseUnitStgItemPos [ i ] = -1;
		}
	}
};


// ��ȯ�� ������ �����.
class sDBRequest_HouseUnitSummonBuildingCreate
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;

	SI16				siItemPos;
	cltItem				clItem;

	sDBRequest_HouseUnitSummonBuildingCreate( SI32 CharID, SI32 PersonID, SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 ItemPos, cltItem *pclItem,
		SI16 SummonBuildingIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitSummonBuildingCreate );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSUMMONBUILDINGCREATE;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siSummonBuildingIndex = SummonBuildingIndex;

		siItemPos = ItemPos;
		clItem.Set( pclItem );
	}
};

class sDBResponse_HouseUnitSummonBuildingCreate
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;

	SI16				siItemPos;
	cltItem				clLeftItem;

	sDBResponse_HouseUnitSummonBuildingCreate()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitSummonBuildingCreate ) );
	}
};


// ��ȯ�� ������ ���׷��̵� ��Ų��.
class sDBRequest_HouseUnitSummonBuildingUpgrade
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;		// ���� ��ȣ
	SI32				siHouseUnitSlot;		// ���� ��ȣ

	SI16				siSummonBuildingIndex;	// ���� index

	SI16				siItemPos;				// ����ؾ� �� ������ ��ġ
	cltItem				clItem;					// ����ؾ� �� ������ Unique, ����

	SI16				siLevel;				// ���� ����

	sDBRequest_HouseUnitSummonBuildingUpgrade( SI32 CharID, SI32 PersonID, SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 SummonBuildingIndex,
		SI16 ItemPos, cltItem *pclItem,
		SI16 Level )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitSummonBuildingUpgrade );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSUMMONBUILDINGUPGRADE;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siSummonBuildingIndex = SummonBuildingIndex;

		siItemPos = ItemPos;
		clItem.Set( pclItem );

		siLevel = Level;
	}
};

class sDBResponse_HouseUnitSummonBuildingUpgrade
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// 1:����, Other:����

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;

	SI16				siItemPos;					// ����ϰ� ���� ������ ����
	cltItem				clLeftItem;
	
	SI16				siLevel;					// ���� ����

	sDBResponse_HouseUnitSummonBuildingUpgrade()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitSummonBuildingUpgrade ) );
	}
};

class sDBRequest_HouseUnitSummonIn
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siPersonSummonIndex;
	SI16				siSummonBuildingIndex;
			
	sDBRequest_HouseUnitSummonIn( SI32 CharID, SI32 PersonID,
		SI32 VillageUnique, SI32 HouseUnitSlot,
		SI16 PersonSummonIndex, SI16 SummonBuildingIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitSummonIn );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSUMMONIN;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siPersonSummonIndex = PersonSummonIndex;
		siSummonBuildingIndex = SummonBuildingIndex;
	}
};

class sDBResponse_HouseUnitSummonIn
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siPersonSummonIndex;

	SI16				siSummonBuildingIndex;
	cltSummon			clHouseUnitStgSummon;

	sDBResponse_HouseUnitSummonIn()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitSummonIn ) );
	}	
};

class sDBRequest_HouseUnitSummonOut
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;

	SI16				siPersonSummonIndex;	

	sDBRequest_HouseUnitSummonOut( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 SummonBuildingIndex, SI16 PersonSummonIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitSummonOut );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSUMMONOUT;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siSummonBuildingIndex = SummonBuildingIndex;

		siPersonSummonIndex = PersonSummonIndex;		
	}
	
};

class sDBResponse_HouseUnitSummonOut
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;
	
	SI16				siPersonSummonIndex;
	cltSummon			clPersonSummon;

	sDBResponse_HouseUnitSummonOut()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitSummonOut ) );
	}
};

class sDBRequest_HouseUnitSummonEat
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;

	SI16				siItemPos;
	cltItem				clItem;

	cltSummon			clSummon;

	sDBRequest_HouseUnitSummonEat( SI32 CharID, SI32 PersonID, 
		SI32 VillageUnique, SI32 HouseUnitSlot, 
		SI16 SummonBuildingIndex,
		SI16 ItemPos, cltItem *pclItem,
		cltSummon *pSummon
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_HouseUnitSummonEat );
		packetHeader.usCmd	= DBMSG_REQUEST_HOUSEUNITSUMMONEAT;

		siCharID = CharID;
		siPersonID = PersonID;

		siVillageUnique = VillageUnique;
		siHouseUnitSlot = HouseUnitSlot;

		siSummonBuildingIndex = SummonBuildingIndex;

		siItemPos = ItemPos;
		clItem.Set( pclItem );

		clSummon.Set( pSummon );
	}
	
};

class sDBResponse_HouseUnitSummonEat
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siVillageUnique;
	SI32				siHouseUnitSlot;

	SI16				siSummonBuildingIndex;
	
	SI16				siItemPos;
	cltItem				clLeftItem;

	cltSummon			clSummon;

	sDBResponse_HouseUnitSummonEat()
	{
		memset( this, 0, sizeof( sDBResponse_HouseUnitSummonEat ) );
	}
};

#endif