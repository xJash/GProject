#ifndef _DBMSGHUNT_H
#define _DBMSGHUNT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\Hunt\Hunt.h"

//-----------------------------------------------------
// �����忡 ���� ������ �������� �Է��Ѵ�. ( ����Ʈ�� �߰� )
//-----------------------------------------------------
class sDBRequest_HuntMonsterFieldListAdd
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID;

	SI32				siVillageUnique;

	SI16				siAddListIndex;

	SI16				siMonsterKind;
	SI16				siMonsterNum;
	SI16				siMonsterLevel;

	sDBRequest_HuntMonsterFieldListAdd()
	{
		ZeroMemory(this, sizeof(sDBRequest_HuntMonsterFieldListAdd));
	}

	sDBRequest_HuntMonsterFieldListAdd( SI32 PersonID, SI32 CharID, SI32 VillageUnique, SI16 AddListIndex, SI16 MonsterKind, SI16 MonsterNum, SI16 MonsterLevel )
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntMonsterFieldListAdd );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTMONSTERFIELDLISTADD;

		siPersonID = PersonID;
		siCharID = CharID;

		siVillageUnique = VillageUnique;
		siAddListIndex = AddListIndex;

		siMonsterKind = MonsterKind;
		siMonsterNum = MonsterNum;
		siMonsterLevel = MonsterLevel;
	}
};

//-----------------------------------------------------
// ����� ������.
//-----------------------------------------------------
class sDBResponse_HuntMonsterFieldListAdd
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������� PersonID
	SI32				siCharID;			// ������� CharUnique

	SI32				siVillageUnique;

	SI16				siAddListIndex;

	SI16				siMonsterKind;
	SI16				siMonsterNum;
	SI16				siMonsterLevel;

	sDBResponse_HuntMonsterFieldListAdd()
	{
		memset( this, 0, sizeof( sDBResponse_HuntMonsterFieldListAdd ) );
	}
};


//-----------------------------------------------------
// �����忡 �־��� ������ �������� ����Ʈ���� �����Ѵ�. ( ����Ʈ���� ���� )
//-----------------------------------------------------
class sDBRequest_HuntMonsterFieldListDel
{
public:
	sPacketHeader		packetHeader;

	SI32				siPersonID;
	SI32				siCharID;

	SI32				siVillageUnique;

	SI16				siDelListIndex;

	sDBRequest_HuntMonsterFieldListDel()
	{
		ZeroMemory(this, sizeof(sDBRequest_HuntMonsterFieldListAdd));
	}

	sDBRequest_HuntMonsterFieldListDel( SI32 PersonID, SI32 CharID, SI32 VillageUnique, SI16 DelListIndex )
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntMonsterFieldListDel );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTMONSTERFIELDLISTDEL;

		siPersonID = PersonID;
		siCharID = CharID;

		siVillageUnique = VillageUnique;

		siDelListIndex = DelListIndex;	
	}
};

//-----------------------------------------------------
// ����� ������.
//-----------------------------------------------------
class sDBResponse_HuntMonsterFieldListDel
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������� PersonID
	SI32				siCharID;			// ������� CharUnique

	SI32				siVillageUnique;

	SI16				siDelListIndex;

	sDBResponse_HuntMonsterFieldListDel()
	{
		memset( this, 0, sizeof( sDBResponse_HuntMonsterFieldListDel ) );
	}
};

//-----------------------------------------------------
// ������ â�� ������ �ִ´�.
//-----------------------------------------------------
class sDBRequest_HuntStorageMonsterIn
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siPersonID;
	SI32				siCharID;
	
	SI16				siFromPersonInventoryItemIndex;
	SI16				siToHuntStorageInventoryItemIndex;

	SI32				siVillageUnique;
	SI16				siItemUnique;
	SI16				siItemNum;

	sDBRequest_HuntStorageMonsterIn()
	{
		ZeroMemory(this, sizeof(sDBRequest_HuntStorageMonsterIn));
	}

	sDBRequest_HuntStorageMonsterIn( SI32 PersonID, SI32 CharID,
						SI16 FromPersonInventoryItemIndex, SI16 ToHuntStorageInventoryItemIndex,
						SI32 VillageUnique, SI16 ItemUnique, SI16 ItemNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntStorageMonsterIn );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTSTORAGEMONSTERIN;

		siCharID		= CharID;
		siPersonID		= PersonID;

		siToHuntStorageInventoryItemIndex = ToHuntStorageInventoryItemIndex;
		siFromPersonInventoryItemIndex = FromPersonInventoryItemIndex;

		siVillageUnique	= VillageUnique;

		siItemUnique	= ItemUnique;
		siItemNum		= ItemNum;
	}
};


class sDBResponse_HuntStorageMonsterIn
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������� PersonID
	SI32				siCharID;			// ������� CharUnique

	SI32				siVillageUnique;
	
	SI16				siFromPersonInventoryItemIndex;
	SI16				siFromPersonInventoryItemUnique;
	SI16				siFromPersonInventoryItemNum;

	SI16				siToHuntStorageInventoryItemIndex;
	SI16				siToHuntStorageInventoryItemUnique;
	SI16				siToHuntStorageInventoryItemNum;
	
	sDBResponse_HuntStorageMonsterIn()
	{
		ZeroMemory(this, sizeof(sDBResponse_HuntStorageMonsterIn));
	}	
};

//-----------------------------------------------------
// ������ â�� �� �ִ� ������ ������.
//-----------------------------------------------------
class sDBRequest_HuntStorageMonsterOut
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siPersonID;
	SI32				siCharID;
	
	SI16				siFromHuntStorageInventoryItemIndex;
	SI16				siToPersonInventoryItemIndex;
	
	SI32				siVillageUnique;
	SI16				siItemUnique;
	SI16				siItemNum;

	sDBRequest_HuntStorageMonsterOut()
	{
		ZeroMemory(this, sizeof(sDBRequest_HuntStorageMonsterOut));
	}

	sDBRequest_HuntStorageMonsterOut( SI32 PersonID, SI32 CharID,
						SI16 FromHuntStorageInventoryItemIndex, SI16 ToPersonInventoryItemIndex,
						SI32 VillageUnique, SI16 ItemUnique, SI16 ItemNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntStorageMonsterOut );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTSTORAGEMONSTEROUT;

		siPersonID		= PersonID;
		siCharID		= CharID;

		siFromHuntStorageInventoryItemIndex = FromHuntStorageInventoryItemIndex;
		siToPersonInventoryItemIndex = ToPersonInventoryItemIndex;

		siVillageUnique	= VillageUnique;

		siItemUnique	= ItemUnique;
		siItemNum		= ItemNum;
	}
};

class sDBResponse_HuntStorageMonsterOut
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID;			// ������� PersonID
	SI32				siCharID;			// ������� CharUnique

	SI32				siVillageUnique;
		
	SI16				siFromHuntStorageInventoryItemIndex;
	SI16				siFromHuntStorageInventoryItemUnique;
	SI16				siFromHuntStorageInventoryItemNum;

	SI16				siToPersonInventoryItemIndex;
	SI16				siToPersonInventoryItemUnique;
	SI16				siToPersonInventoryItemNum;

	sDBResponse_HuntStorageMonsterOut()
	{
		ZeroMemory(this, sizeof(sDBResponse_HuntStorageMonsterOut));
	}	
};

class sDBRequest_HuntStorageDecreaseDollItemNum
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	SI16				siHuntStorageItemUnique[ MAX_HUNT_LINEUP_NUMBER ];
	SI16				siHuntStorageItemIndex[ MAX_HUNT_LINEUP_NUMBER ];
	SI16				siHuntStorageItemDecreaseNum[ MAX_HUNT_LINEUP_NUMBER ];

	sDBRequest_HuntStorageDecreaseDollItemNum()
	{
		ZeroMemory(this, sizeof(sDBRequest_HuntStorageDecreaseDollItemNum));
	};

	sDBRequest_HuntStorageDecreaseDollItemNum( 
		SI32 VillageUnique, 
		SI16 *pHuntStorageItemUnique,
		SI16 *pHuntStorageItemIndex,
		SI16 *pHuntStorageItemDecreaseNum
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntStorageDecreaseDollItemNum );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTSTORAGEDECREASEDOLLITEMNUM;

		siVillageUnique = VillageUnique;
		
		memcpy( siHuntStorageItemUnique, pHuntStorageItemUnique, sizeof( SI16 ) * MAX_HUNT_LINEUP_NUMBER );
		memcpy( siHuntStorageItemIndex, pHuntStorageItemIndex, sizeof( SI16 ) * MAX_HUNT_LINEUP_NUMBER );
		memcpy( siHuntStorageItemDecreaseNum, pHuntStorageItemDecreaseNum, sizeof( SI16 ) * MAX_HUNT_LINEUP_NUMBER );
	}
};

class sDBResponse_HuntStorageDecreaseDollItemNum
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;

	SI32				siVillageUnique;

	SI16				siHuntStorageItemUnique[ MAX_HUNT_LINEUP_NUMBER ];
	SI16				siHuntStorageItemIndex[ MAX_HUNT_LINEUP_NUMBER ];	
	SI16				siHuntStorageItemNum[ MAX_HUNT_LINEUP_NUMBER ];

	sDBResponse_HuntStorageDecreaseDollItemNum()
	{
		memset( this, 0, sizeof( sDBResponse_HuntStorageDecreaseDollItemNum ) );
	}
};

//-----------------------------------------------------
// �����忡 ���� ���̰� ���� �������� â�� ���������� �ٽ� �־��ش�.
//-----------------------------------------------------
class sDBRequest_HuntLeftMonsterStgIn
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;
	
	SI16				siToHuntStorageInventoryItemIndex;

	SI16				siItemUnique;
	SI16				siItemNum;

	sDBRequest_HuntLeftMonsterStgIn( SI32 VillageUnique, SI16 ToHuntStorageInventoryItemIndex, SI16 ItemUnique, SI16 ItemNum )
	{
		packetHeader.usSize = sizeof( sDBRequest_HuntLeftMonsterStgIn );
		packetHeader.usCmd	= DBMSG_REQUEST_HUNTLEFTMONSTERSTGIN;

		siVillageUnique = VillageUnique;

		siToHuntStorageInventoryItemIndex = ToHuntStorageInventoryItemIndex;

		siItemUnique = ItemUnique;
		siItemNum = ItemNum;
	}
};

class sDBResponse_HuntLeftMonsterStgIn
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;

	SI32				siVillageUnique;

	SI16				siToHuntStorageInventoryItemIndex;
	
	SI16				siItemUnique;
	SI16				siItemNum;

	sDBResponse_HuntLeftMonsterStgIn()
	{
		ZeroMemory( this, sizeof( sDBResponse_HuntLeftMonsterStgIn ) );
	}
};

enum INSTANCEMAPPOINT_TYPE
{
	INSTANCEMAPPOINT_TYPE_GUILD = 1,
};

//�ν��Ͻ� ���� ���� ���� ����Ʈ
//���� ���� ����Ʈ�� ������ �´�.
struct HOFList
{
	// ���ַ� - �⵵
	UI08				uiYear;
	//���� ���� ��� ����ũ
	SI32				siGuildUnique;
	//���� ���� ��� ��ũ �ε���
	SI32				siGuildMarkindex;
	//���� ���� ��� �̸�
	TCHAR				szHOFGuildName[MAX_GUILD_NAME];
	//���� ���� ȹ�� ����
	SI32				siClearPoint;
	//���� ���� Ŭ���� �ð�
	SI32			ClearTime;
	//���� ���� Ŭ���� ��¥
	SYSTEMTIME			ClearDateTime;

	HOFList()
	{
		ZeroMemory(this, sizeof(HOFList));
	}
};

#define MAX_HOF_PAGE 10//�ִ� ������
#define MAX_HOF_RANKCOUNT 10//�ִ� ��ŷ 10������.

class sDBRequest_HOFList
{
public:
	sPacketHeader		packetHeader;
	UI16				uiCharID;

	SI16				siType;					// Ÿ��
	SI32				siRequestPageNum;		// ��û ������ ��ȣ
	SI08				siPageMaxCount;			// ���̴� ����

	sDBRequest_HOFList( UI16 charid, SI16 type, SI32 RequestPage )
	{
		packetHeader.usSize = sizeof( sDBRequest_HOFList );
		packetHeader.usCmd	= DBMSG_REQUEST_HOFLIST;

		uiCharID			= charid;

		siType				= type;
		siRequestPageNum	= RequestPage;
		siPageMaxCount		= MAX_HOF_PAGE;
	}
};
class sDBResponse_HOFList
{
public:
	sPacketHeader		packetHeader;
	UI16				uiCharID;

	SI32				siResult;

	SI16				siType;				// Ÿ��
	
	SI32				siRequestPage;		// ��û�� ������	
	HOFList    HOFrList[MAX_HOF_PAGE];		// ��� ������
	SI32				siMaxPage;

	sDBResponse_HOFList()
	{
		ZeroMemory(this, sizeof(sDBResponse_HOFList));
	}
};

class sDBRequest_YearRanking
{
public:
	sPacketHeader		packetHeader;
	UI16				uiCharID;
	SI16				siType;			// Ÿ�� INSTANCEMAPPOINT_TYPE_GUILD
	UI08				uiYear;			// �ش� �⵵ (���ӽð�)
	bool				bReward;		// ������ �ؾ��ϴ°�? (�������� ����ϴ� ��)
	SI32				sRequest_Page;

	sDBRequest_YearRanking( UI16 charid, SI16 type, UI08 Year, bool reward, SI32 Request_Page)
	{
		packetHeader.usSize = sizeof( sDBRequest_YearRanking );
		packetHeader.usCmd = DBMSG_REQUEST_YEARRANKING;
		uiCharID		= charid;
		siType			= type;
		uiYear			= Year;//���� ���ַ�
		bReward			= reward;
		sRequest_Page	= Request_Page;//��û ������ 
	}
};

class sDBResponse_YearRanking
{
public:
	sPacketHeader		packetHeader;
	UI16				uiCharID;
	SI32				siResult;
	SI16				siType;			// Ÿ�� INSTANCEMAPPOINT_TYPE_GUILD
	UI08				uiYear;			// �ش� �⵵ (���ӽð�)
	// ��� ������
	HOFList    HOFrList[MAX_HOF_RANKCOUNT];

	bool				bReward;		// ������ �ؾ��ϴ°�? (�������� ����ϴ� ��)
	SI32				siRequestPage;	// ��û�� ������	
	SI32				siMaxPage;		// �ִ� ������
	sDBResponse_YearRanking()
	{
		ZeroMemory(this, sizeof(sDBResponse_YearRanking));
	}
};

class sDBRequest_InstanceMapPoint_Insert
{
public:
	sPacketHeader		packetHeader;

	SI16				siType;			// Ÿ�� INSTANCEMAPPOINT_TYPE_GUILD
	SI32				siUnique;		// ����ũ (��� or )
	SI32				siPoint;		// ����
	UI08				uiYear;			// �ش� �⵵ (���ӽð�) 
	SI32				siClearTime;	// ���� Ŭ�����ϴµ� �ɸ��ð� 
	SYSTEMTIME			stClearTime;	// Ŭ������ �ð� (���ǽð�)

	sDBRequest_InstanceMapPoint_Insert( SI16 type, SI32 unique, SI32 point, UI08 year, SI32 cleartime, SYSTEMTIME& Time )
	{
		packetHeader.usSize = sizeof( sDBRequest_InstanceMapPoint_Insert );
		packetHeader.usCmd = DBMSG_REQUEST_INSTANCEMAPPOINT_INSERT;

		siType		= type;
		siUnique	= unique;
		siPoint		= point;
		uiYear		= year;
		siClearTime	= cleartime;
		memcpy(&stClearTime, &Time, sizeof(stClearTime));
	}
};

class sDBResponse_InstanceMapPoint_Insert
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	sDBResponse_InstanceMapPoint_Insert()
	{
		ZeroMemory(this, sizeof(sDBResponse_InstanceMapPoint_Insert));
	}
};

#endif