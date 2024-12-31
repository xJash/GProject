#ifndef _MSGTYPEPOSTOFFICE_H
#define _MSGTYPEPOSTOFFICE_H

#include "..\PostOffice\PostOffice.h"

// ������ ������
class cltGameMsgRequest_PostOfficeSendItem
{
public:	
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];

	SI16				siItemInventoryIndex;
	SI32				siItemUnique;
	SI16				siItemNum;

	cltGameMsgRequest_PostOfficeSendItem( TCHAR *personName, SI16 itemInvenIndex, SI32 itemUnique, SI16 itemNum )
	{
		memcpy( szReceiverPersonName, personName, MAX_PLAYER_NAME );
		szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

		siItemInventoryIndex = itemInvenIndex;
		siItemUnique = itemUnique;
		siItemNum = itemNum;
	}


};

// �۱��ϱ�
class cltGameMsgRequest_PostOfficeSendMoney
{
public:
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];
	GMONEY				siMoney;

	cltGameMsgRequest_PostOfficeSendMoney( TCHAR *personName, SI64 money )
	{
		memcpy( szReceiverPersonName, personName, MAX_PLAYER_NAME );
		szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

		siMoney = money;
	}
};


// �޽��� ������
class cltGameMsgRequest_PostOfficeSendMsg
{
public:
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];
	SI16				siSendFlag;

	cltGameMsgRequest_PostOfficeSendMsg( TCHAR *personName, TCHAR *msg, SI16 sendflag = 0 )
	{
		memcpy( szReceiverPersonName, personName, MAX_PLAYER_NAME );
		szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

		memcpy( szMsg, msg, MAX_POSTOFFICE_MSG_SIZE );
		szMsg[ MAX_POSTOFFICE_MSG_SIZE - 1 ] = NULL;

		siSendFlag = sendflag;
	}
};

// ���ŵ� ������ ����Ʈ �ޱ� 
class cltGameMsgResponse_PostOfficeRecvItemList
{
public:
	SI32							siVillageUnique;

	UI16							usCount;
	cltPostOfficeRecvItemInfo		clRecvItemInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	cltGameMsgResponse_PostOfficeRecvItemList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PostOfficeRecvItemList ) );
	}

	SI32 GetTotalSize() { return 12 + sizeof( cltPostOfficeRecvItemInfo ) * usCount; };

};

// ���ŵ� ���� ����Ʈ �ޱ� 
class cltGameMsgResponse_PostOfficeRecvMoneyList
{
public:
	SI32							siVillageUnique;

	UI16							usCount;
	cltPostOfficeRecvMoneyInfo		clRecvMoneyInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	cltGameMsgResponse_PostOfficeRecvMoneyList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PostOfficeRecvMoneyList ) );
	}

	SI32 GetTotalSize() { return 12 + sizeof( cltPostOfficeRecvMoneyInfo ) * usCount; };

};

// ���ŵ� �޽��� ����Ʈ �ޱ�
class cltGameMsgResponse_PostOfficeRecvMsgList
{
public:
	SI32							siVillageUnique;

	UI16							usCount;
	cltPostOfficeRecvMsgInfo		clRecvMsgInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	cltGameMsgResponse_PostOfficeRecvMsgList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PostOfficeRecvMsgList ) );
	}

	SI32 GetTotalSize() { return 12 + sizeof( cltPostOfficeRecvMsgInfo ) * usCount; };
};

// ������ �ޱ� ��û
class cltGameMsgRequest_PostOfficeGetItem
{
public:
	SI32							siMsgID;
	cltItem							clItem;

	cltGameMsgRequest_PostOfficeGetItem( SI32 msgid, cltItem *pclItem )
	{
		siMsgID = msgid;
		clItem.Set( pclItem );
	}
};

// ���� ������ ����
class cltGameMsgRequest_PostOfficeSetFee
{
public:
	cltFee				clMoneyFee;					// �۱� ������ 
	cltFee				clItemFee;					// ��ǰ ���� ������ 

	GMONEY				siMsgFee;					// �޽��� ���� ������ (�Ǵ�)
	GMONEY				siRecvFee;					// ������ ���� ������ (ȸ��)

	cltGameMsgRequest_PostOfficeSetFee()
	{
		ZeroMemory( this, sizeof( cltGameMsgRequest_PostOfficeSetFee ) );
	}

	cltGameMsgRequest_PostOfficeSetFee( cltFee* pclMoneyFee, cltFee* pclItemFee, GMONEY msgfee, GMONEY recvfee )
	{
		clMoneyFee.Set( pclMoneyFee );
		clItemFee.Set( pclItemFee );

		siMsgFee = msgfee;
		siRecvFee = recvfee;
	}

};

class cltGameMsgResponse_PostOfficeGetRecord
{
public:
	UI16						usCount;
	cltPostOfficeRecordInfo		recordinfo[ MAX_POSTOFFICE_RECORD_NUMBER ];

	cltGameMsgResponse_PostOfficeGetRecord()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_PostOfficeGetRecord ) );
	}
};

class cltGameMsgRequest_Get_SaveUserItem
{
public:

	SI32				siIndex;			
	cltItem				clItem;

	cltGameMsgRequest_Get_SaveUserItem( SI32 index, cltItem *pclItem )
	{
		siIndex = index;
		clItem.Set( pclItem );
	}
};

//KHY - 1127 - Ŭ��� ��ǰ ���� ����
class cltGameMsgRequest_Get_SaveUserHorse
{
public:

	SI32				siIndex;			
	cltHorse			clHorse;  //����� �������� �����´�.

	cltGameMsgRequest_Get_SaveUserHorse( SI32 index, cltHorse *pclHorse )
	{
		siIndex = index;
		clHorse.Set( pclHorse );
	}
};

class cltGameMsgResponse_Get_SaveUserItem
{
public:
	GMONEY				siUserMoney;

	cltGameMsgResponse_Get_SaveUserItem(GMONEY money)
	{
		siUserMoney = money;
	}
};

class cltGameMsgResponse_Get_SaveUserItemList
{
public:
	SI16				siCharId;
	SI32				siSaveItemPersonID;

	cltSaveUersItemInfo	clSaveUsersItemInfo[MAX_SAVEUSERITEM_LIST];

	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	cltSaveUersHorseInfo	clSaveUsersHorseInfo[MAX_SAVEUSERHORSE_LIST];

	cltGameMsgResponse_Get_SaveUserItemList()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_Get_SaveUserItemList) );
	}
};

class cltGameMsgRequest_MarketConditions
{
public:
	SI32 			siNPCCharUnique;			// NPC����ũ.
	
	SI32				selectWhatShowList; 		// 1 = �Ϲݰ˻�,  2 = ���� ���, 3 = ������ �ü�.
	SI32				siSelectItemTypeIndex;	// ���õ� ǰ��.		
	SI16				siSelectItemIndex;		// ���õ� ǰ��.
	
	cltGameMsgRequest_MarketConditions(SI32 m_siNPCCharUnique ,SI32 WhatShowList, SI32 SelectItemTypeIndex,SI16 SelectItemIndex )
	{
		siNPCCharUnique = m_siNPCCharUnique;
		selectWhatShowList = WhatShowList;
		siSelectItemTypeIndex = SelectItemTypeIndex;
		siSelectItemIndex = SelectItemIndex;		
	}
};

class cltGameMsgResponse_MarketConditions
{
public:

#ifdef _SAFE_MEMORY
	NSafeTArray<cltMarketConditionsInfo, 100>		clMarketConditionsInfo;
	NSafeTArray<_SYSTEMTIME, 8>		sTimeMarketConditionsInfo;
#else
	cltMarketConditionsInfo clMarketConditionsInfo[100];
	_SYSTEMTIME	sTimeMarketConditionsInfo[8]; // 3= ������ �ü��� ����.
#endif

	cltGameMsgResponse_MarketConditions()
	{
		ZeroMemory( this, sizeof( cltGameMsgResponse_MarketConditions) );
	}
};






#define MAX_SEND_USER_NUM	100		//[����] ��ü������ ��ü �޽��� ������ �ִ� ������. => 2008-8-4

//[����] ��ü ������ ������ => 2008-8-4
class cltGameMsgRequest_PostOffice_SendItem_Group
{
public:	
	TCHAR				m_szReceiverPersonNameGroup[MAX_SEND_USER_NUM][MAX_PLAYER_NAME];

	SI16				siItemInventoryIndex;
	SI32				siItemUnique;
	SI16				siItemNum;

	cltGameMsgRequest_PostOffice_SendItem_Group( TCHAR* _pReceiverPersonNameGroup, SI16 itemInvenIndex, SI32 itemUnique, SI16 itemNum )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szReceiverPersonNameGroup, _pReceiverPersonNameGroup, sizeof(m_szReceiverPersonNameGroup) );
		
		siItemInventoryIndex = itemInvenIndex;
		siItemUnique		 = itemUnique;
		siItemNum			 = itemNum;
	}


};

//[����] ��ü �۱��ϱ� => 2008-8-4 
class cltGameMsgRequest_PostOffice_SendMoney_Group
{
public:
	TCHAR				m_szReceiverPersonNameGroup[MAX_SEND_USER_NUM][ MAX_PLAYER_NAME ];
	GMONEY				siMoney;

	cltGameMsgRequest_PostOffice_SendMoney_Group( TCHAR* _pReceiverPersonNameGroup, SI32 money )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szReceiverPersonNameGroup, _pReceiverPersonNameGroup, sizeof(m_szReceiverPersonNameGroup) );
		
		siMoney = money;
	}
};

//[����] ��ü �޽��� ������ => 2008-8-4 
class cltGameMsgRequest_PostOffice_SendMsg_Group
{
public:
	TCHAR				m_szReceiverPersonNameGroup[MAX_SEND_USER_NUM][ MAX_PLAYER_NAME ];
	TCHAR				m_szMsg[ MAX_POSTOFFICE_MSG_SIZE ];
	SI16				m_siSendFlag;

	cltGameMsgRequest_PostOffice_SendMsg_Group( TCHAR* _pReceiverPersonNameGroup, TCHAR *_pMsg, SI16 _Sendflag = 0 )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szReceiverPersonNameGroup, _pReceiverPersonNameGroup, sizeof(m_szReceiverPersonNameGroup) );
		
		memcpy( m_szMsg, _pMsg, MAX_POSTOFFICE_MSG_SIZE );
		m_szMsg[ MAX_POSTOFFICE_MSG_SIZE - 1 ] = NULL;
		
		m_siSendFlag = _Sendflag;
	}
};

class cltGameMsgRequest_PostOffice_User_List_Group
{
public:
	enum{ FRIEND, GUILD, VILLAGE };

	SI16	m_siType;

	cltGameMsgRequest_PostOffice_User_List_Group( SI16	_siType )
	{
		m_siType = _siType;
	}
};

class cltGameMsgResponse_PostOffice_User_List_Group
{
public:
	TCHAR				m_szAddPersonNameGroup[MAX_SEND_USER_NUM][ MAX_PLAYER_NAME ];
	SI16				m_siLevel[MAX_SEND_USER_NUM];
	SI16				m_siVillage[MAX_SEND_USER_NUM];
	bool				m_bConnect[MAX_SEND_USER_NUM];

	cltGameMsgResponse_PostOffice_User_List_Group( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}

	cltGameMsgResponse_PostOffice_User_List_Group( TCHAR* _pReceiverPersonNameGroup )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szAddPersonNameGroup, _pReceiverPersonNameGroup, sizeof(m_szAddPersonNameGroup) );		
	}
};

class cltGameMsgRequest_Char_Name_Check
{
public:
	TCHAR				m_szAddPersonName[MAX_PLAYER_NAME];

	cltGameMsgRequest_Char_Name_Check( TCHAR* _pAddPersonName )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szAddPersonName, _pAddPersonName, sizeof(m_szAddPersonName) );
	}
};

class cltGameMsgResponse_Char_Add_Name_Check
{
public:
	TCHAR				m_szAddPersonName[MAX_PLAYER_NAME];
	SI32				m_siPersonID;
	SI16				m_CheckPersonLevel;					// ����.
	SI16				m_CheckPersonVillage;				// ���� ����.
    
	bool				m_bConnect;							// ���ӿ���.

	cltGameMsgResponse_Char_Add_Name_Check( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}

	cltGameMsgResponse_Char_Add_Name_Check( TCHAR* _pAddPersonName, SI32 _siPersonID, SI16	_CheckPersonLevel, SI16	_CheckPersonVillage, bool _bConnect )
	{
		ZeroMemory( this, sizeof(*this) );

		memcpy( m_szAddPersonName, _pAddPersonName, sizeof(m_szAddPersonName) );

		m_siPersonID			= _siPersonID;
		m_CheckPersonLevel		= _CheckPersonLevel;
		m_CheckPersonVillage	= _CheckPersonVillage;
		m_bConnect				= _bConnect;
	}
};







#endif


