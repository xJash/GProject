#ifndef _DBMSG_AGRICULTURE_H_
#define _DBMSG_AGRICULTURE_H_

#include "DBMsg.h"
#include "../../GoonZuWorld/Common/Agriculture/Agriculture.h"

class sDBRequest_AgricultureGetProducts
{
public:
	sPacketHeader packetHeader;	

	SI32 siPersonID;
	SI32 siCharID;
	
	// Output
	SI16 siGetProductsInvPos;					// ȹ���� ��ǰ�� ���� �κ��丮 ��ġ
	cltItem clGetProductsItem;					// ȹ���� ��ǰ
	bool bCreateSID;							// ȹ���� ��ǰ�� SID ���� ����
	
	SI32 siCharUnique;							// ȹ���� ĳ�� Unique( �������, ��ȯ������ ���� )
	SI32 siKind;								// ���� ����̳�, ��ȯ����.
	
	SI16 siAgricultureType;						// ��� �з�( Type )
			
	sDBRequest_AgricultureGetProducts( SI32 PersonID,	SI32 CharID,
		SI16 GetProductsInvPos, cltItem *pGetProductsItem, bool bcreatesid,
		SI32 CharUnique, SI32 Kind,
		SI16 AgricultureType
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_AgricultureGetProducts );
		packetHeader.usCmd	= DBMSG_REQUEST_AGRICULTUREGETPRODUCTS;
		
		siPersonID = PersonID;
		siCharID = CharID;
		
		siGetProductsInvPos = GetProductsInvPos;
		clGetProductsItem.Set( pGetProductsItem );
		bCreateSID = bcreatesid;

		siCharUnique = CharUnique;
		siKind = Kind;

		siAgricultureType = AgricultureType;
	}
};

class sDBResponse_AgricultureGetProducts
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;

	SI32 siPersonID;
	SI32 siCharID;

	SI16 siAddedInvPos;					// �� ��ġ
	SI16 siAddedItemNum;				// �߰��� �������� ����
	cltItem clLeftItem;					// ���� ������ ����


	SI32 siCharUnique;					// �������� ������ �״�� �����ָ� ��
	SI32 siKind;						// �������� ������ �״�� �����ָ� ��

	SI16 siAgricultureType;				// �������� ������ �״�� �����ָ� ��

	cltItem clGetProductsItem;			// ȹ���� ��ǰ for LOG
	
	sDBResponse_AgricultureGetProducts()
	{
		memset( this, 0, sizeof( sDBResponse_AgricultureGetProducts ) );
	}
};

class sDBRequest_AgriculturePayMoneyForRentLand
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siCharID;

	SI16 siVillageUnique;					// ���� index
	SI16 siStructType;						// �ǹ��� ��ȣ

	GMONEY siPayMoney;						// ���� �ݾ�

	SI16 siAgricultureItemUnique;			// �����ҷ��� ��ǰ

	UI32 uiLeaseExpire;						// �ӽ÷� ������ �Ⱓ ����ð�(��)

	sDBRequest_AgriculturePayMoneyForRentLand
		(
		SI32 PersonID, SI32 CharID,
		SI16 VillageUnique, SI16 StructType,
		GMONEY PayMoney,
		SI16 AgricultureItemUnique,
		UI32 LeaseExpire
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_AgriculturePayMoneyForRentLand );
		packetHeader.usCmd	= DBMSG_REQUEST_AGRICULTUREPAYMONEYFORRENTLAND;

		siPersonID = PersonID;
		siCharID = CharID;

		siVillageUnique = VillageUnique;
		siStructType = StructType;

		siPayMoney = PayMoney;

		siAgricultureItemUnique = AgricultureItemUnique;

		uiLeaseExpire = LeaseExpire;
	}
};

class sDBResponse_AgriculturePayMoneyForRentLand
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;						// ��� : 1 ����, Other : ����

	SI32 siPersonID;
	SI32 siCharID;

	SI16 siVillageUnique;				// �������� ������ �״�� �����ָ� ��
	SI16 siStructType;					// �������� ������ �״�� �����ָ� ��

	GMONEY siPayMoney;					// ���� �ݾ�
	GMONEY siLeftMoney;					// �����ϰ� ���� �ݾ�

	SI16 siAgricultureItemUnique;		// �������� ������ �״�� �����ֱ�

	UI32 uiLeaseExpire;						// �ӽ÷� ������ �Ⱓ ����ð�(��)

	sDBResponse_AgriculturePayMoneyForRentLand()
	{
		memset( this, 0, sizeof( sDBResponse_AgriculturePayMoneyForRentLand ) );
	}	
};

class sDBRequest_GetAgricultureLeaseInfo
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;

	sDBRequest_GetAgricultureLeaseInfo( SI32 personid )
	{
		packetHeader.usSize = sizeof(sDBRequest_GetAgricultureLeaseInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETAGRICULTURELEASEINFO;

		siPersonID = personid;
	}
};

class sDBResponse_GetAgricultureLeaseInfo
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;
	
	SI32 siPersonID;
	SI16 siVillageUnique[MAX_AGRICULTURE_COUNT];
	UI32 uiExpire[MAX_AGRICULTURE_COUNT];

	sDBResponse_GetAgricultureLeaseInfo()
	{
		memset( this, 0 , sizeof(sDBResponse_GetAgricultureLeaseInfo ) ) ;
	}
};

class sDBRequest_ExpiredAgricultureLease
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siVillageUnique;
	UI32 uiExpireTime;

	sDBRequest_ExpiredAgricultureLease( SI32 personid, SI32 villageunique, UI32 expiretime)
	{
		packetHeader.usSize = sizeof(sDBRequest_ExpiredAgricultureLease);
		packetHeader.usCmd = DBMSG_REQUEST_EXPIREDAGRICULTERLEASE;

		siPersonID = personid;
		siVillageUnique = villageunique;
		uiExpireTime = expiretime;
	}
};

class sDBResponse_ExpiredAgricultureLease
{
public:
	sPacketHeader packetHeader;

	SI32	siResult;
	SI32	siPersonID;
	SI32	siVillageUnique;
	UI32	uiExpireTime;

	sDBResponse_ExpiredAgricultureLease()
	{
		memset( this, 0, sizeof(sDBResponse_ExpiredAgricultureLease) );
	}
};
#endif