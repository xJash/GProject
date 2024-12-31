#ifndef _DBMSG_FISHING_H_
#define _DBMSG_FISHING_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\Common\Fishing\FishingBaseInfo.h"

// ���� ������ ������ �Ҹ�
class sDBRequest_FishingDecreaseToolDurability
{
public:
	sPacketHeader packetHeader;

	SI32 siPersonID;
	SI32 siCharID;

	// Tool - ������ ���
	DBToolInfo clFishingTool[MAX_FISHING_TOOL_NUMBER];

	sDBRequest_FishingDecreaseToolDurability
		(
		SI32 PersonID,
		SI32 CharID,
		DBToolInfo* pclFishingTool
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_FishingDecreaseToolDurability );
		packetHeader.usCmd	= DBMSG_REQUEST_FISHINGDECREASETOOLDURABILITY;

		siPersonID = PersonID;
		siCharID = CharID;

		for( SI32 i = 0; i < MAX_FISHING_TOOL_NUMBER; ++i )
		{
			if ( pclFishingTool[i].clItem.siUnique > 0 )
			{
				clFishingTool[i].Set(&pclFishingTool[i]);
			}
		}
	}
};

class sDBResponse_FishingDecreaseToolDurability
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;

	SI32 siPersonID;
	SI32 siCharID;

	// Tool - ������ ���
	DBToolInfo clFishingTool[MAX_FISHING_TOOL_NUMBER];

	sDBResponse_FishingDecreaseToolDurability()
	{
		memset( this, 0, sizeof( sDBResponse_FishingDecreaseToolDurability ) );
	}
};

class sDBRequest_FishingGetMarineProducts
{
public:
	sPacketHeader packetHeader;	

	SI32 siPersonID;
	SI32 siCharID;
	
	// Output
	SI16 siAcquireMarineInvPos;					// ȹ���� ���깰�� ���� �κ��丮 ��ġ
	cltItem clAcquireMarineProductItem;			// ȹ���� ���깰
	bool bCreateSID;							// ȹ���� ���깰�� SID ���뿩��

	SI16 siSkillUnique;							// ����ġ�� ȹ���� ��ų�� ����ũ
	SI16 siIncFishingSkillExp;					// ȹ���� ����ġ
	
	SI32 siCharUnique;							// ���� ��� �Ǵ� ��ȯ���� CharUnique
	SI32 siKind;								// ���� ���Ҵ���... �����̳�? ��ȯ����?
			
	sDBRequest_FishingGetMarineProducts( SI32 PersonID,	SI32 CharID,
		SI16 AcquireMarineInvPos, cltItem *pclAcquireMarineProductItem, bool bcreatesid,
		SI16 SkillUnique, SI16 IncFishingSkillExp,
		SI32 CharUnique, SI32 Kind
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_FishingGetMarineProducts );
		packetHeader.usCmd	= DBMSG_REQUEST_FISHINGGETMARINEPRODUCTS;
		
		siPersonID = PersonID;
		siCharID = CharID;
		
		siAcquireMarineInvPos = AcquireMarineInvPos;
		clAcquireMarineProductItem.Set( pclAcquireMarineProductItem );
		bCreateSID = bcreatesid;

		siSkillUnique = SkillUnique;
		siIncFishingSkillExp = IncFishingSkillExp;

		siCharUnique = CharUnique;
		siKind = Kind;

	}
};

class sDBResponse_FishingGetMarineProducts
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;

	SI32 siPersonID;
	SI32 siCharID;

	cltItem clAcquireMarineProductItem;			// ȹ���� ���깰	- For LOG

	SI16 siAcquireMarineInvPos;			// ���깰�� �� ��ġ
	SI16 siAddedItemNum;				// �߰��� �������� ����
	cltItem clLeftItem;					// ���� ������ ����

	SI16 siIncSkillUnique;				// ��� ����ġ ���� Skill Unique
	SI32 siSkillTotalExp;				// ��� ����ġ ����...

	SI32 siCharUnique;					// �������� ������ �״�� �����ָ� ��
	SI32 siKind;						// �������� ������ �״�� �����ָ� ��
	
	sDBResponse_FishingGetMarineProducts()
	{
		memset( this, 0, sizeof( sDBResponse_FishingGetMarineProducts ) );
	}
};


#endif