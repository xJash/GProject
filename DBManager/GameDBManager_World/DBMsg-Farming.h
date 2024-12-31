#ifndef _DBMSG_FARMING_H_
#define _DBMSG_FARMING_H_

#include "DBMsg.h"
#include "../../BeTheRich/Common/Farming/FarmingMgr.h"

class sDBRequest_FarmingPayMoneyForRentLand
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siCharID;

	SI16 siVillageUnique;				// ���� index
	SI16 siStructType;					// �ǹ��� ��ȣ ( �� ���� ������ ������ ) - RANKTYPE_LAND

	GMONEY siPayMoney;					// ���� �ݾ�
	
	SI16 siFarmingItemUnique;			// ��Ȯ�ҷ��� ��ǰ

	sDBRequest_FarmingPayMoneyForRentLand
		(
		SI32 PersonID, SI32 CharID,
		SI16 VillageUnique, SI16 StructType,
		GMONEY PayMoney,
		SI16 FarmingItemUnique
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_FarmingPayMoneyForRentLand );
		packetHeader.usCmd	= DBMSG_REQUEST_FARMINGPAYMONEYFORRENTLAND;

		siPersonID = PersonID;
		siCharID = CharID;
		
		siVillageUnique = VillageUnique;
		siStructType = StructType;

		siPayMoney = PayMoney;

		siFarmingItemUnique = FarmingItemUnique;
	}
};

class sDBResponse_FarmingPayMoneyForRentLand
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

	SI16 siFarmingItemUnique;			// �������� ������ �״�� �����ֱ�

	sDBResponse_FarmingPayMoneyForRentLand()
	{
		memset( this, 0, sizeof( sDBResponse_FarmingPayMoneyForRentLand ) );
	}	
};

#endif