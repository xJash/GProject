#ifndef _DBMSGFEAST_H
#define _DBMSGFEAST_H

#include "dbmsg.h"
#include "../../CommonLogic/Feast/Feast.h"
//-----------------------------------------
// ��ȸ ���� ��û�� �Ѵ� 
//-----------------------------------------
class sDBRequest_FeastReserve
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ���� 
	SI32				siPersonID;				// ��û�� personid

	SI16				siYear;					// ��ȸ �ð�(��)
	SI16				siMonth;				// ��ȸ �ð�(��)
	SI16				siDay;					// ��ȸ �ð�(��)

	SI16				siHour;					// ��ȸ �ð�(��)
	SI16				siMinute;				// ��ȸ �ð�(��)

	TCHAR				szReason[ 128 ];		// ��ȸ ���� 

	GMONEY				siCost;					// ����� 

	sDBRequest_FeastReserve( UI16 id, SI32 villageunique, SI32 personid, SI16 year, SI16 month, SI16 day, 
							 SI16 hour, SI16 minute, TCHAR *reason, GMONEY cost )
	{

		packetHeader.usCmd = DBMSG_REQUEST_FEAST_RESERVE;
		packetHeader.usSize = sizeof( sDBRequest_FeastReserve );

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;

		siYear = year;
		siMonth = month;
		siDay = day;

		siHour = hour;
		siMinute = minute;

		memcpy( szReason, reason, 128 );
		szReason[ 127 ] = NULL;

		siCost = cost;
	}

};

class sDBResponse_FeastReserve
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siResult;

	SI32				siVillageUnique;		// ���� 
	SI32				siPersonID;				// ��û�� personid
	TCHAR				szPersonName[ MAX_PLAYER_NAME ];

	SI16				siYear;					// ��ȸ �ð�(��)
	SI16				siMonth;				// ��ȸ �ð�(��)
	SI16				siDay;					// ��ȸ �ð�(��)

	SI16				siHour;					// ��ȸ �ð�(��)
	SI16				siMinute;				// ��ȸ �ð�(��)

	TCHAR				szReason[ 128 ];		// ��ȸ ���� 

	GMONEY				siCost;					// ���ҵ� ��� ��� 
	GMONEY				siPersonMoney;			// ��û�� ������ 
	cltMoney			clFeastMoney;			// ���ڽ� �����ڱ� 

	sDBResponse_FeastReserve()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastReserve ) );
	}
};

class sDBRequest_FeastOpen
{
public:
	sPacketHeader		packetHeader;
	SI32				siVillageUnique;

	sDBRequest_FeastOpen( SI32 villageunique ) 
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_OPEN;
		packetHeader.usSize = sizeof( sDBRequest_FeastOpen );

		siVillageUnique = villageunique;
	}
};

class sDBResponse_FeastOpen
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;
	SI32				siVillageUnique;

	sDBResponse_FeastOpen()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastOpen ) );
	}

};

class sDBRequest_FeastClose
{
public:
	sPacketHeader		packetHeader;
	SI32				siVillageUnique;

	sDBRequest_FeastClose( SI32 villageunique ) 
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_CLOSE;
		packetHeader.usSize = sizeof( sDBRequest_FeastClose );

		siVillageUnique = villageunique;
	}

};

class sDBResponse_FeastClose
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siResult;
	SI32				siVillageUnique;

	sDBResponse_FeastClose()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastClose ) );
	}
};





//-----------------------------------------
// ���ڽ� ����� ���� �׸��� �߰��Ѵ� 
//-----------------------------------------
class sDBRequest_FeastAddPresentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ����
	SI32				siListIndex;			// ���� ��� �ε��� 

	SI16				siItemUnique;			// Item Unique
	SI16				siItemNum;				// Item Num

	sDBRequest_FeastAddPresentList( UI16 id, SI32 villageunique, SI32 listindex, SI16 itemunique, SI16 itemnum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_ADDPRESENTLIST;
		packetHeader.usSize = sizeof( sDBRequest_FeastAddPresentList );

		usCharID = id;

		siVillageUnique = villageunique;
		siListIndex = listindex;

		siItemUnique = itemunique;
		siItemNum = itemnum;

	}

};


class sDBResponse_FeastAddPresentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;		// ����
	SI32				siListIndex;			// ���� ��� �ε��� 

	SI16				siItemUnique;			// Item Unique
	SI16				siItemNum;				// Item Num

	sDBResponse_FeastAddPresentList()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastAddPresentList ) );
	}

};

//-----------------------------------------
// ���ڽ� ����� ���� �׸��� �����Ѵ�
//-----------------------------------------
class sDBRequest_FeastDelPresentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// ���� 
	SI32				siListIndex;			// ���� ��� �ε��� 

	sDBRequest_FeastDelPresentList( UI16 id, SI32 villageunique, SI32 listindex )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_DELPRESENTLIST;
		packetHeader.usSize = sizeof( sDBRequest_FeastDelPresentList );

		usCharID = id;

		siVillageUnique = villageunique;
		siListIndex = listindex;
	}

};

class sDBResponse_FeastDelPresentList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;		// ���� 
	SI32				siListIndex;			// ���� ��� �ε��� 

	sDBResponse_FeastDelPresentList()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastDelPresentList ) );
	}
};


//-----------------------------------------
// ���ڽ� ����� â�� �������� �ִ´� 
//-----------------------------------------
class sDBRequest_FeastStgItemIn
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;									// ��� personid
	SI32				siVillageUnique;							// villageunique;
	
	SI16				siItemInventoryIndex;						// item index
	SI16				siItemUnique;								// item unique
	SI16				siItemNum;									// item num

	sDBRequest_FeastStgItemIn( UI16 id, SI32 personid, SI32 villageunique, 
		                       SI16 inventoryindex, SI16 itemunique, SI16 itemnum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_STGITEMIN;
		packetHeader.usSize = sizeof( sDBRequest_FeastStgItemIn );

		usCharID = id;

		siPersonID = personid;
		siVillageUnique = villageunique;

		siItemInventoryIndex = inventoryindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;
	}

};

class sDBResponse_FeastStgItemIn
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siPersonID;									// ��� personid
	SI32				siVillageUnique;							// villageunique;

	SI16				siItemInventoryIndex;						// inventory item index
	SI16				siItemUnique;								// inventory item unique
	SI16				siItemNum;									// inventory item num

	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	sDBResponse_FeastStgItemIn()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastStgItemIn ) );
	}
};

//-----------------------------------------
// ���ڽ� ����� â���� �������� ������
//-----------------------------------------
class sDBRequest_FeastStgItemOut
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;									// ��� personid
	SI32				siVillageUnique;							// villageunique;
	
	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	SI16				siPersonInvIndex;							// Person item index


	sDBRequest_FeastStgItemOut( UI16 id, SI32 personid, SI32 villageunique, 
		                       SI16 stgindex, SI16 itemunique, SI16 itemnum , SI16 personinvindex )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_STGITEMOUT;
		packetHeader.usSize = sizeof( sDBRequest_FeastStgItemOut );

		usCharID = id;

		siPersonID = personid;
		siVillageUnique = villageunique;

		siStgItemIndex = stgindex;
		siStgItemUnique = itemunique;
		siStgItemNum = itemnum;

		siPersonInvIndex = personinvindex;
	}

};

class sDBResponse_FeastStgItemOut
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siPersonID;									// ��� personid
	SI32				siVillageUnique;							// villageunique;

	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	SI16				siItemInventoryIndex;						// inventory item index
	SI16				siItemUnique;								// inventory item unique
	SI16				siItemNum;									// inventory item num

	sDBResponse_FeastStgItemOut()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastStgItemOut ) );
	}

};

class sDBRequest_FeastGiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPresentIndex;
	SI16				siItemUnique;
	SI16				siItemNum;
	SI32				siStgIndex;
	SI16				siStgItemUnique;
	SI16				siStgItemNum;

	sDBRequest_FeastGiveItem( UI16 id, SI32 villageunique, SI32 presentindex, SI16 itemunique, SI16 itemnum,
		SI32 stgindex, SI16 stgitemunique, SI16 stgitemnum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_GIVEITEM;
		packetHeader.usSize = sizeof( sDBRequest_FeastGiveItem );

		usCharID = id;

		siVillageUnique = villageunique;
		siPresentIndex = presentindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;
		siStgIndex = stgindex;
		siStgItemUnique = stgitemunique;
		siStgItemNum = stgitemnum;
	}
};

class sDBResponse_FeastGiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPresentIndex;
	SI16				siItemUnique;
	SI16				siItemNum;
	SI32				siStgIndex;
	SI16				siStgItemUnique;
	SI16				siStgItemNum;

	sDBResponse_FeastGiveItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastGiveItem ) );
	}
};

class sDBRequest_FeastSetCost
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	GMONEY				siCost;

	sDBRequest_FeastSetCost( UI16 id, SI32 villageunique, GMONEY cost )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_SETCOST;
		packetHeader.usSize = sizeof( sDBRequest_FeastSetCost );

		usCharID = id;
		siVillageUnique = villageunique;
		siCost = cost;
	}
};

class sDBResponse_FeastSetCost
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	GMONEY				siCost;

	sDBResponse_FeastSetCost() 
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastSetCost ) );

	}

};

//#if defined(_LEON_FEAST_EFFECT)
class sDBRequest_FeastUseEffect
{
public:
	enum {
		MAX_EFFECT_NUM_AT_ONCE = 1,
	};

	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;
	SI16				siPos;
	cltItem				clitem;		// <= item���� ���� ����

	SI16				siEffectNum[MAX_EFFECT_NUM_AT_ONCE];

	sDBRequest_FeastUseEffect( SI32 id, SI32 personid, SI32 villageunique, SI16 pos, cltItem *pclItem, SI16* effectnum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_FEAST_USEEFFECT;
		packetHeader.usSize = sizeof( sDBRequest_FeastUseEffect );

		usCharID = id;
		siPersonID = personid;
		siVillageUnique = villageunique;

		siPos = pos;
		clitem.Set( pclItem );

		memcpy(siEffectNum, effectnum, sizeof(SI16) * MAX_EFFECT_NUM_AT_ONCE);
	}
};

class sDBResponse_FeastUseEffect
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;

	SI16				siPos;						// �κ��丮 ��ġ
	cltItem				clitem;						// ������

	SI16				siEffectNum[sDBRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE];

	//[�߰� : Ȳ���� 2007. 11. 1 �α׿� �̿�, ��ȸ�� ������ ����Ҷ� ������ ����]
	cltItem				clUseItem;						

	sDBResponse_FeastUseEffect() 
	{
		ZeroMemory( this, sizeof( sDBResponse_FeastUseEffect ) );
	}

};
//#endif

class sDBRequest_PartyHall_Reservation
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;

	SYSTEMTIME			m_SystemTime;			// �����ð�.

	TCHAR				m_szReason[ 128 ];		// ��ȸ ����. 
	SI16				m_siDecorationKind;		// ��Ĺ� ����.
	SI16				m_siEntranceType;		// ���� Ÿ��.
	SI16				m_siValueType;			// ���� Ÿ�԰��� ����.
	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.			//MAX_PARTYHALL_MAP
	
	GMONEY				m_ResvMoney;			// ������ �����.

	SI16				m_siDecorationSlotNum;	// ��Ĺ��� ���� ��ġ.<��Ĺ� 1���� ����ؼ� �������� 1���� ���� �Ǽ� �ʿ��ϴ�.>
	SI32				m_siVillageUnique;

	sDBRequest_PartyHall_Reservation(  SI32 id,   SI32 personid,
									   SI16 year, SI16 month,  SI16 day, SI16 hour, SI16 minute, 
									   TCHAR *reason, SI16 _siDecorationKind, SI16 _siEntranceType, 
									   SI16 _siValueType, SI16 _siPartyHallIndex, SI32 _ResvMoney, SI16	_siDecorationSlotNum, SI16 _siVillageUnique )
	{
		ZeroMemory( this, sizeof( sDBRequest_PartyHall_Reservation ) );

		m_packetHeader.usCmd	= DBMSG_REQUEST_PARTYHALL_RESERVATION;
		m_packetHeader.usSize	= sizeof( sDBRequest_PartyHall_Reservation );

		m_usCharID			= id;
		m_siPersonID		= personid;

		m_SystemTime.wYear	 = year;
		m_SystemTime.wMonth	 = month;
		m_SystemTime.wDay	 = day;
		m_SystemTime.wHour	 = hour;
		m_SystemTime.wMinute = minute;

		memcpy( m_szReason, reason, 128 );
		m_szReason[ 127 ] = NULL;

		m_siDecorationKind		= _siDecorationKind;	
		m_siEntranceType		= _siEntranceType;	
		m_siValueType			= _siValueType;		
		m_siPartyHallIndex		= _siPartyHallIndex;

		m_ResvMoney				= _ResvMoney;

		m_siDecorationSlotNum   = _siDecorationSlotNum;
		m_siVillageUnique        = _siVillageUnique;
	}
};

class sDBResponse_PartyHall_Reservation
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;

	SI32				m_siResult;

	SYSTEMTIME			m_SystemTime;							// �����ð�.

	TCHAR				m_szPersonName[ MAX_PLAYER_NAME ];		// �̸�. 
	TCHAR				m_szReason[ 128 ];						// ��ȸ ����. 
	SI16				m_siDecorationKind;						// ��Ĺ� ����.
	SI16				m_siEntranceType;						// ���� Ÿ��.
	SI16				m_siValueType;							// ���� Ÿ�԰��� ����.
	SI16				m_siPartyHallIndex;						// ��ƼȦ ��ȣ.				//MAX_PARTYHALL_MAP

	GMONEY				m_UserChangeMoney;						// ������� ���� ����� ������ ������.

	SI16				m_siDecorationSlotNum;					// ��Ĺ��� ���� ��ġ.<��Ĺ� 1���� ����ؼ� �������� 1���� ���� �Ǽ� �ʿ��ϴ�.>
	SI16				m_siVillageUnique;
	
	GMONEY				m_ResvMoney;							// ������ �����.

	sDBResponse_PartyHall_Reservation()
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_Reservation ) );
	}
};

// ���� ��ȸ���� ���� ��Ĺ� �߰�.
class sDBRequest_PartyHall_Add_Decoration
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;
	
	SI32				m_siVillageUnique;		// ���� ����ũ.
	SI16				m_siDecorationKind;		// ��Ĺ� ����.
	SI16				m_siDecorationNum;		// �߰��� ��Ĺ� ����.
	SI16				m_siDecorationSlot;		// ��Ĺ��� ����� ���� ��ȣ.		//MAX_PARTYHALL_DECORATION_ITEM

	cltFeastStg			m_DeleteItem[MAX_FEAST_STG_NUMBER];

public:
	sDBRequest_PartyHall_Add_Decoration( SI32 id, SI32 personid, SI32 _siVillageUnique, SI16 _siDecorationKind, 
																 SI16 _siDecorationNum, SI16 _siDecorationSlot,
																 cltFeastStg* _DeleteItem	)
	{
		ZeroMemory( this, sizeof( sDBRequest_PartyHall_Add_Decoration ) );

		m_packetHeader.usCmd  =	DBMSG_REQUEST_PARTYHALL_ADD_DECORATION;
		m_packetHeader.usSize = sizeof( sDBRequest_PartyHall_Add_Decoration );

		
		m_usCharID			= id;
		m_siPersonID		= personid;
		
		m_siVillageUnique  = _siVillageUnique;
		m_siDecorationKind = _siDecorationKind;
		m_siDecorationNum  = _siDecorationNum;	
		m_siDecorationSlot = _siDecorationSlot;

		memcpy( m_DeleteItem, _DeleteItem, sizeof( m_DeleteItem ) );
	}
};

class sDBResponse_PartyHall_Add_Decoration
{
public:
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;

	SI32				m_siPersonID;

	SI32				m_siVillageUnique;			// ���� ����ũ.
	SI16				m_siDecorationKind;			// ��Ĺ� ����.
	SI16				m_siDecorationNum;			// ���� ��Ĺ� ����.
	SI16				m_siDecorationSlot;			// ��Ĺ��� ����� ���� ��ȣ. //MAX_PARTYHALL_DECORATION_ITEM
	
	cltFeastStg			m_DeleteItem[MAX_FEAST_STG_NUMBER];

public:
	sDBResponse_PartyHall_Add_Decoration( void )
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_Add_Decoration ) );

		m_packetHeader.usCmd  =	DBMSG_RESPONSE_PARTYHALL_ADD_DECORATION;
		m_packetHeader.usSize = sizeof( sDBResponse_PartyHall_Add_Decoration );
	}
};

// ��Ƽ�� �����ڰ� ���� �׸��� �߰�.
class sDBRequest_PartyHall_Add_Present
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.			//MAX_PARTYHALL_MAP
	SYSTEMTIME			m_ResvTime;				// ����� �ð�.
	SI16				m_siItemListIndex;		// �������� �� ���� ��ȣ // RESERVATIO_PRESENT_ITEM

	SI16				m_siPresentItemInvenPos;		// �����ϴ� �� �κ��� ������ ��ġ.
	SI16				m_siItemUnique;			// Item Unique
	SI16				m_siItemNum;			// Item Num

	sDBRequest_PartyHall_Add_Present( UI16 id, SI16 _siPartyHallIndex, 
									  UI08 _siItemListIndex, SI16 _siItemUnique, SI16 _siItemNum, 
									  SYSTEMTIME* _ResvTime, SI16 _siPresentItemInvenPos				)
	{
		m_packetHeader.usCmd  = DBMSG_REQUEST_PARTYHALL_ADD_PRESENT;
		m_packetHeader.usSize = sizeof( sDBRequest_PartyHall_Add_Present );

		m_usCharID = id;

		m_siPartyHallIndex		= _siPartyHallIndex; 
		m_siItemListIndex		= _siItemListIndex;
		m_siItemUnique			= _siItemUnique;
		m_siItemNum				= _siItemNum;	
		m_siPresentItemInvenPos = _siPresentItemInvenPos;

		memcpy( &m_ResvTime, _ResvTime, sizeof( m_ResvTime) );

	}

};


class sDBResponse_PartyHall_Add_Present
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI16				m_siPartyHallIndex;				// ��ƼȦ ��ȣ.			//MAX_PARTYHALL_MAP
	SYSTEMTIME			m_SystemTime;					// ����� �ð�.
	UI08				m_siItemListIndex;				// �������� �� ���� ��ȣ // RESERVATIO_PRESENT_ITEM

	SI16				m_siItemUnique;					// Item Unique
	SI16				m_siItemNum;					// Item Num
	SI16				m_siPresentItemInvenPos;		// �����ϴ� �� �κ��� ������ ��ġ.

	sDBResponse_PartyHall_Add_Present()
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_Add_Present ) );
	}

};


// ���� ��ȸ���� ���� ��Ĺ� �߰�.
class sDBRequest_PartyHall_GiveItem
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;

	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.			//MAX_PARTYHALL_MAP
	SYSTEMTIME			m_SystemTime;			// ����� �ð�.

	sDBRequest_PartyHall_GiveItem()
	{
		ZeroMemory( this, sizeof( sDBRequest_PartyHall_GiveItem ) );

		m_packetHeader.usCmd  = DBMSG_REQUEST_PARTYHALL_GIVEITEM;
		m_packetHeader.usSize = sizeof( sDBRequest_PartyHall_GiveItem );
	}
};

class sDBResponse_PartyHall_GiveItem
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;

	SI32				m_siPersonID;

	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.			//MAX_PARTYHALL_MAP
	SYSTEMTIME			m_SystemTime;			// ����� �ð�.

	sDBResponse_PartyHall_GiveItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_GiveItem ) );
	}
};

class sDBRequest_PartyHall_ReserveList
{
public:
	sPacketHeader		packetHeader;

	SYSTEMTIME			stCurrent;

public:
	sDBRequest_PartyHall_ReserveList(SYSTEMTIME& Cur)
	{
		packetHeader.usSize = sizeof( sDBRequest_PartyHall_ReserveList );
		packetHeader.usCmd	= DBMSG_REQUEST_PARTYHALL_RESERVELIST;

		memcpy(&stCurrent, &Cur, sizeof(stCurrent));
	}
};

class sDBResponse_PartyHall_ReserveList
{
public:
	sPacketHeader				packetHeader;

	cltPatyHallResvInfo			clPartyHallResvInfo[MAX_PARTYHALL_MAP][MAX_PARTYHALL_RESERVATION_INFO_LIST];

public:
	sDBResponse_PartyHall_ReserveList()
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_ReserveList ) );
	}
};


//[����] ��ƼȦ. ��Ĺ� ����Ʈ ��û. => 2008. 3. 12
class sDBRequest_PartyHall_Decoration_List
{
public:
	sPacketHeader		packetHeader;


	sDBRequest_PartyHall_Decoration_List()
	{
		ZeroMemory( this, sizeof( sDBRequest_PartyHall_Decoration_List ) );

		packetHeader.usSize = sizeof( sDBRequest_PartyHall_Decoration_List );
		packetHeader.usCmd	= DBMSG_REQUEST_PARTYHALL_DECORATION_LIST;
	}
};

//[����] ��ƼȦ. ��Ĺ� ����Ʈ ��û. => 2008. 3. 12
class sDBResponse_PartyHall_Decoration_List
{
public:
	sPacketHeader			packetHeader;

	PartyHall_Decoration	clDecoration[MAX_VILLAGE_NUMBER][MAX_PARTYHALL_DECORATION_ITEM];

	sDBResponse_PartyHall_Decoration_List()
	{
		ZeroMemory( this, sizeof( sDBResponse_PartyHall_Decoration_List ) );

		packetHeader.usSize = sizeof( sDBResponse_PartyHall_Decoration_List );
		packetHeader.usCmd	= DBMSG_RESPONSE_PARTYHALL_DECORATION_LIST;
	}
};

#endif