#ifndef _MSGTYPEFEAST_H
#define _MSGTYPEFEAST_H

#include "../Feast/Feast.h"


class cltGameMsgRequest_FeastReserve
{
public:
	SI16				siYear;					// ��ȸ �ð�(��)
	SI16				siMonth;				// ��ȸ �ð�(��)
	SI16				siDay;					// ��ȸ �ð�(��)

	SI16				siHour;					// ��ȸ �ð�(��)
	SI16				siMinute;				// ��ȸ �ð�(��)

	TCHAR				szReason[ 128 ];		// ��ȸ ���� 

	cltGameMsgRequest_FeastReserve( SI16 year, SI16 month, SI16 day, SI16 hour, SI16 minute, TCHAR *reason )
	{
		siYear = year;
		siMonth = month;
		siDay = day;
		siHour = hour;
		siMinute = minute;

		memcpy( szReason, reason, 128 );
		szReason[ 127 ] = NULL;
	}

};





class cltGameMsgRequest_FeastAddPresentList
{
public:
	SI16				siItemUnique;			// Item Unique
	SI16				siItemNum;				// Item Num

	cltGameMsgRequest_FeastAddPresentList( SI16 itemunique, SI16 itemnum ) 
	{
		siItemUnique = itemunique;
		siItemNum	 = itemnum;
	}
	
};

class cltGameMsgResponse_FeastAddPresentList
{
public:
	SI32				siListIndex;			// ���� ��� �ε��� 
	SI16				siItemUnique;			// Item Unique
	SI16				siItemNum;				// Item Num

	cltGameMsgResponse_FeastAddPresentList( SI32 listindex, SI16 itemunique, SI16 itemnum )
	{
		siListIndex = listindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;	
	}

};

class cltGameMsgRequest_FeastDelPresentList
{
public:
	SI32				siListIndex;			// ���� ��� �ε��� 
	SI16				siItemUnique;
	SI16				siItemNum;			

	cltGameMsgRequest_FeastDelPresentList( SI32 listindex, SI16 itemunique, SI16 itemnum )
	{
		siListIndex = listindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;
	}

};

class cltGameMsgResponse_FeastDelPresentList
{
public:
	SI32				siListIndex;			// ���� ��� �ε��� 

	cltGameMsgResponse_FeastDelPresentList( SI32 listindex )
	{
		siListIndex = listindex;
	}
};

class cltGameMsgRequest_FeastStgItemIn
{
public:
	SI16				siItemInventoryIndex;						// item index
	SI16				siItemUnique;								// item unique
	SI16				siItemNum;									// item num

	cltGameMsgRequest_FeastStgItemIn( SI16 inventoryindex, SI16 itemunique, SI16 itemnum )
	{
		siItemInventoryIndex =inventoryindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;
	}
};

class cltGameMsgResponse_FeastStgItemIn
{
public:
	SI16				siItemInventoryIndex;						// item index
	SI16				siItemUnique;								// item unique
	SI16				siItemNum;									// item num

	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	cltGameMsgResponse_FeastStgItemIn( SI16 inventoryindex, SI16 itemunique, SI16 itemnum,
									   SI16 stgItemIndex, SI16 stgItemUnique, SI16 stgItemNum )
	{
		siItemInventoryIndex = inventoryindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;

		siStgItemIndex = stgItemIndex;
		siStgItemUnique = stgItemUnique;
		siStgItemNum = stgItemNum;
	}


};

class cltGameMsgRequest_FeastStgItemOut
{
public:
	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	cltGameMsgRequest_FeastStgItemOut( SI16 inventoryindex, SI16 itemunique, SI16 itemnum )
	{
		siStgItemIndex =inventoryindex;
		siStgItemUnique = itemunique;
		siStgItemNum = itemnum;
	}
};


class cltGameMsgResponse_FeastStgItemOut
{
public:
	SI16				siItemInventoryIndex;						// item index
	SI16				siItemUnique;								// item unique
	SI16				siItemNum;									// item num

	SI16				siStgItemIndex;								// stg item index
	SI16				siStgItemUnique;							// stg item unique
	SI16				siStgItemNum;								// stg item num

	cltGameMsgResponse_FeastStgItemOut( SI16 inventoryindex, SI16 itemunique, SI16 itemnum,
									   SI16 stgItemIndex, SI16 stgItemUnique, SI16 stgItemNum )
	{
		siItemInventoryIndex = inventoryindex;
		siItemUnique = itemunique;
		siItemNum = itemnum;

		siStgItemIndex = stgItemIndex;
		siStgItemUnique = stgItemUnique;
		siStgItemNum = stgItemNum;
	}


};

class cltGameMsgRequest_FeastSetCost
{
public:
	GMONEY				siCost;

	cltGameMsgRequest_FeastSetCost( GMONEY cost )
	{
		siCost = cost;
	}
};


class cltGameMsgRequest_FeastGiveItem
{
public:
	SI32				siIndex;
	SI32				siItemUnique;
	SI32				siItemNum;

	cltGameMsgRequest_FeastGiveItem( SI32 index, SI32 itemunique, SI32 itemnum )
	{
		siIndex = index;
		siItemUnique = itemunique;
		siItemNum = itemnum;
	}
};

class cltGameMsgRequest_FeastSendChat
{
public:
	SI16				siSize;
	TCHAR				szText[ 128 ];

	cltGameMsgRequest_FeastSendChat( TCHAR *text ) 
	{
		MStrCpy( szText, text, 128 );
		siSize = sizeof( SI16 ) + _tcslen( szText ) + 1;
	}
};

//#if defined(_LEON_FEAST_EFFECT)
class cltGameMsgRequest_FeastUseEffect
{
public:
	enum {
		MAX_EFFECT_NUM_AT_ONCE = 1,
	};

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, MAX_EFFECT_NUM_AT_ONCE>		siEffectNum;
#else
	SI16				siEffectNum[MAX_EFFECT_NUM_AT_ONCE];
#endif

    cltGameMsgRequest_FeastUseEffect( SI16* effectnum, SI16 kindnum = MAX_EFFECT_NUM_AT_ONCE )
	{
		if( effectnum == NULL )
			kindnum = 0;
			
		if( kindnum > MAX_EFFECT_NUM_AT_ONCE )
			kindnum = MAX_EFFECT_NUM_AT_ONCE;

#ifdef _SAFE_MEMORY
		siEffectNum.ZeroMem();
#else
        memset( siEffectNum, 0, sizeof( siEffectNum ));
#endif

		for(SI16 i=0; i< kindnum; i++ )
		{
            siEffectNum[ i ] = effectnum[ i ];
		}
	}    
};

class cltGameMsgResponse_FeastUseEffect
{
public:
	//enum {
	//	MAX_EFFECT_NUM_AT_ONCE = 1,
	//};

#ifdef _SAFE_MEMORY
	NSafeTArray<SI16, cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE>		siEffectNum;
#else
	SI16				siEffectNum[cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE];
#endif

	SI16				siEffectStartPosX;
	SI16				siEffectStartPosY;

	cltGameMsgResponse_FeastUseEffect( 
		SI16* effectnum, 
		SI16 kindnum = cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE, 
		SI16 siStartPosX = 0, 
		SI16 siStartPosY = 0
	)
	{
		if( effectnum == NULL )
			kindnum = 0;
			
		if( kindnum > cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE )
			kindnum = cltGameMsgRequest_FeastUseEffect::MAX_EFFECT_NUM_AT_ONCE;

#ifdef _SAFE_MEMORY
		siEffectNum.ZeroMem();
#else
        memset( siEffectNum, 0, sizeof( siEffectNum ));
#endif

		for(SI16 i=0; i< kindnum; i++ )
		{
            siEffectNum[ i ] = effectnum[ i ];
		}

		siEffectStartPosX = siStartPosX;
		siEffectStartPosY = siStartPosY;
	}    
};
//#endif
class cltGameMsgRequest_PartyHall_Total_Info
{
public:
	SI16						m_PartyHallIndex;

	cltGameMsgRequest_PartyHall_Total_Info(SI16 _PartyHallIndex)
	{
		ZeroMemory(this, sizeof(cltGameMsgRequest_PartyHall_Total_Info));

		m_PartyHallIndex = _PartyHallIndex;
	}
};


//[����] ��ƼȦ. ��ü ���� ���. => 2008. 3. 17
class cltGameMsgResponse_PartyHall_Total_Info
{
public:
	enum{ 
			ONE_PAGE_NUM = 8,  
			PAGE_NUM	 = 3		// 
		};	// ���� ������ ����.
public:
	SI16						m_PartyHallIndex;
	SI16						m_Page;
	cltPatyHallResvInfo			m_clPartyHallResvInfoList[ONE_PAGE_NUM];	

	cltGameMsgResponse_PartyHall_Total_Info(SI16 _PartyHallIndex, SI16 _Page, cltPatyHallResvInfo* _clPartyHallResvInfoList)
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyHall_Total_Info));

		m_PartyHallIndex = _PartyHallIndex;
		m_Page			 = _Page;
		memcpy(	m_clPartyHallResvInfoList, &_clPartyHallResvInfoList[ONE_PAGE_NUM * m_Page], sizeof(m_clPartyHallResvInfoList));
	}
};

//[����] ��ƼȦ. ��Ƽ���� => 2008. 3. 13
class cltGameMsgRequest_PartyHall_Reservation
{
public:
	SI16				m_siYear;				// ��ȸ �ð�(��)
	SI16				m_siMonth;				// ��ȸ �ð�(��)
	SI16				m_siDay;				// ��ȸ �ð�(��)
	SI16				m_siHour;				// ��ȸ �ð�(��)
	SI16				m_siMinute;				// ��ȸ �ð�(��)

	TCHAR				m_szReason[ 128 ];		// ��ȸ ����. 
	SI16				m_siDecorationKind;		// ��Ĺ� ����.
	SI16				m_siEntranceType;		// ���� Ÿ��.
	SI16				m_siValueType;			// ���� Ÿ�԰��� ����.
	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.

	SI32				m_ResvMoney;			// �����.

	SI16				m_siDecorationSlotNum;	// ��Ĺ��� ���� ��ġ.<��Ĺ� 1���� ����ؼ� �������� 1���� ���� �Ǽ� �ʿ��ϴ�.>

	cltGameMsgRequest_PartyHall_Reservation( SI16 year, SI16 month, SI16 day, SI16 hour, SI16 minute, TCHAR *reason,
											 SI16 _siDecorationKind, SI16 _siEntranceType, SI16 _siValueType, SI16 _siPartyHallIndex,
											 SI32 _ResvMoney, SI16 _siDecorationSlotNum)
	{
		m_siYear	= year;
		m_siMonth	= month;
		m_siDay		= day;
		m_siHour	= hour;
		m_siMinute	= minute;

		memcpy( m_szReason, reason, sizeof(m_szReason) );
		m_szReason[ 127 ] = NULL;
		
		m_siDecorationKind	= _siDecorationKind;	
		m_siEntranceType	= _siEntranceType;	
		m_siValueType		= _siValueType;		
		m_siPartyHallIndex  = _siPartyHallIndex;
		m_ResvMoney			= _ResvMoney;

		m_siDecorationSlotNum = _siDecorationSlotNum;
	}
};

class cltGameMsgResponse_PartyHall_Reservation
{
public:
	SI32				m_siPersonID;			
	SI16				m_siYear;				// ��ȸ �ð�(��)
	SI16				m_siMonth;				// ��ȸ �ð�(��)
	SI16				m_siDay;				// ��ȸ �ð�(��)
	SI16				m_siHour;				// ��ȸ �ð�(��)
	SI16				m_siMinute;				// ��ȸ �ð�(��)

	TCHAR				m_szPersonName[ MAX_PLAYER_NAME ];		//  �̸�. 
	TCHAR				m_szReason[ 128 ];		// ��ȸ ����. 
	SI16				m_siDecorationKind;		// ��Ĺ� ����.
	SI16				m_siEntranceType;		// ���� Ÿ��.
	SI16				m_siValueType;			// ���� Ÿ�԰��� ����.
	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.
	
	GMONEY				m_siUserMoney;			// ���� ������ ��.
	
public:
	
	cltGameMsgResponse_PartyHall_Reservation()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_Reservation ) );
	}
};

//[����] ��ƼȦ. ���ǰ �߰�.
class cltGameMsgRequest_PartyHall_Add_Decoration
{
public:
	SI16			m_siViilageUnique;
	SI16			m_siDecorationKind;		// ��Ĺ� ����.
	SI16			m_siDecorationNum;		// ��Ĺ� ����.

	cltFeastStg		m_DeleteItem[MAX_FEAST_STG_NUMBER];

	cltGameMsgRequest_PartyHall_Add_Decoration( SI16 _siViilageUnique, SI16 _siDecorationKind, SI16 _siDecorationNum, cltFeastStg*  _DeleteItem ) 
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_PartyHall_Add_Decoration ) );

		m_siViilageUnique  = _siViilageUnique;
		m_siDecorationKind = _siDecorationKind;
		m_siDecorationNum  = _siDecorationNum;

		memcpy( m_DeleteItem, _DeleteItem, sizeof( m_DeleteItem ) );
	}
};

//[����] ��ƼȦ. ���ǰ �߰�.
class cltGameMsgResponse_PartyHall_Add_Decoration
{
public:
	SI16				m_siVillageUnique;
	SI16				m_siDecorationKind;
	SI16				m_siDecorationNum;
	SI16				m_siDecorationSlot;

	cltFeastStg			m_DeleteItem[MAX_FEAST_STG_NUMBER];

	cltGameMsgResponse_PartyHall_Add_Decoration( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_Add_Decoration ) );
	}

	cltGameMsgResponse_PartyHall_Add_Decoration( SI16 _siVillageUnique, SI16 _siDecorationKind, SI16 _siDecorationNum, 
												 SI16 _siDecorationSlot, cltItem*  _DeleteItem  )
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_Add_Decoration ) );

		m_siVillageUnique  =	_siVillageUnique; 	
		m_siDecorationKind =	_siDecorationKind;
		m_siDecorationNum  =	_siDecorationNum; 	
		m_siDecorationSlot =	_siDecorationSlot;

		memcpy( m_DeleteItem, _DeleteItem, sizeof( m_DeleteItem ) );
	}
};

class PartyHall_Decoration_List_Info
{
public:
	SI16				m_siDecorationKind;
	SI16				m_siDecorationNum;
	SI16				m_siDecorationSlot;
};

class cltGameMsgResponse_PartyHall_Decoration_List
{
public:
	SI16							m_siVillageUnique;
	
	PartyHall_Decoration_List_Info	m_clDecoration[MAX_FEAST_STG_NUMBER];
	
	cltGameMsgResponse_PartyHall_Decoration_List()
	{
		ZeroMemory( this, sizeof(cltGameMsgResponse_PartyHall_Decoration_List) );
	}
};


// [����] ��ƼȦ. ���� ������ ���. => 2008. 3. 13
class cltGameMsgRequest_PartyHall_Add_Present
{
public:
	SI16				m_siItemUnique;			// Item Unique
	SI16				m_siItemNum;			// Item Num

	SI16				m_siPartyHallIndex;	
	SI16				m_siPresentItemInvenPos;		// �����ϴ� �� �κ��� ������ ��ġ.
	SI16				m_siItemSlotIndex;

	cltGameMsgRequest_PartyHall_Add_Present( SI16 itemunique,		 SI16 itemnum,
											 SI16 _siPartyHallIndex, SI16 _siPresentItemInvenPos,
											 SI16 _siItemSlotIndex								) 
	{
		m_siItemUnique			= itemunique;
		m_siItemNum				= itemnum;
		m_siPartyHallIndex		= _siPartyHallIndex;		
		m_siPresentItemInvenPos = _siPresentItemInvenPos;
		m_siItemSlotIndex		= _siItemSlotIndex;
	}

};

// [����] ��ƼȦ. ���� ������ ���. => 2008. 3. 13
class cltGameMsgResponse_PartyHall_Add_Present
{
public:
	SI32				m_siPersonID;			
	SI16				m_siItemUnique;			// Item Unique
	SI16				m_siItemNum;			// Item Num
	SI16				m_siPartyHallIndex;		// ��ƼȦ ��ȣ.
	SI16				m_siItemSlotIndex;
	SI16				m_siPresentItemInvenPos;		// �����ϴ� �� �κ��� ������ ��ġ.
	
	cltGameMsgResponse_PartyHall_Add_Present()
	{
		ZeroMemory(this, sizeof(cltGameMsgResponse_PartyHall_Add_Present));
	};
	cltGameMsgResponse_PartyHall_Add_Present( SI32 _siPersonID,
											  SI16 _siPartyHallIndex,  SI16 _siItemunique,	   SI16 _siItemnum,
											  SI16 _siItemSlotIndex,   SI16 _siPresentItemInvenPos	)	
	{
		m_siPersonID			= _siPersonID;
		m_siPartyHallIndex		= _siPartyHallIndex	;		
		m_siItemUnique 			= _siItemunique;
		m_siItemNum	   			= _siItemnum;	
		m_siItemSlotIndex		= _siItemSlotIndex;
		m_siPresentItemInvenPos = _siPresentItemInvenPos;
	}

};


//[����] ��ƼȦ. ��Ƽ�� ���� ��û�� �޴´�. => 2008. 3. 12
class cltGameMsgRequest_PartyHall_Entrance_Application
{
public:
	SI16    m_siPartyIndex;

	cltGameMsgRequest_PartyHall_Entrance_Application( SI32 _siPersonID, SI16 _siPartyIndex )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_PartyHall_Entrance_Application ) );

		m_siPartyIndex = _siPartyIndex;
	}
};

//[����] ��ƼȦ. ��Ƽ�� ���� ��û�� �޴´�. => 2008. 3. 12
class cltGameMsgResponse_PartyHall_Entrance_Application
{
public:
	SI32	m_siPersonID;
	SI16	m_siLevel;					// ����
	
	cltGameMsgResponse_PartyHall_Entrance_Application()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_Entrance_Application ) );
	}
};

// ��ƼȦ ���� ��û�� ����
class Entrance_Application_Info
{
public:
	TCHAR	m_szID[MAX_PLAYER_NAME];	// id
	SI32	m_siPersonID;				// personid
	SI16	m_siLevel;					// ����
};

//[����] ��ƼȦ. ��Ƽ�� ���� ��û ����Ʈ ��û. => 2008. 3. 12
class cltGameMsgRequest_PartyHall_Entrance_Application_List
{
public:
	

	cltGameMsgRequest_PartyHall_Entrance_Application_List()
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_PartyHall_Entrance_Application_List ) );
	}
};

//[����] ��ƼȦ. ��Ƽ�� ���� ��û ����Ʈ�� �޴´�. => 2008. 3. 12
class cltGameMsgResponse_PartyHall_Entrance_Application_List
{
public:
	Entrance_Application_Info	m_ApplicationArray[MAX_PARTYHALL_APPLICATION_LIST];

	cltGameMsgResponse_PartyHall_Entrance_Application_List()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_Entrance_Application_List ) );
	}
};


//[����] ��ƼȦ. ��Ƽ�� ������ �ֱ�. => 2008. 3. 12
class cltGameMsgRequest_PartyHall_GiveItem
{
public:
	
	cltGameMsgRequest_PartyHall_GiveItem( void )
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_PartyHall_GiveItem ) );
	}
};

//[����] ��ƼȦ. ��Ƽ�� ���� ��û ����Ʈ�� �޴´�. => 2008. 3. 12
class cltGameMsgResponse_PartyHall_GiveItem
{
public:
	

	cltGameMsgResponse_PartyHall_GiveItem()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PartyHall_GiveItem ) );
	}
};


#endif


