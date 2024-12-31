#ifndef _DBMSGPOSTOFFICE_H
#define _DBMSGPOSTOFFICE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\CommonLogic\PostOffice\PostOffice.h"
#include "..\..\GoonZuWorld\CommonLogic\CityHall\CityHall.h"

class sDBRequest_PostOfficeMasterSendItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siReason;										// ������ ���� ����

	SI32				siReceiverPersonID;								// ������ person id
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];		// ������ name

	cltItem				clItem;											// item			

	cltDate				clDate;											// �۽�����

	sDBRequest_PostOfficeMasterSendItem( SI32 reason, SI32 personid, TCHAR *receiverPersonName, cltItem *pclItem, cltDate *pclDate )
	{

		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_MASTERSENDITEM;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeMasterSendItem );

		siReason = reason;

		siReceiverPersonID = personid;

		if( receiverPersonName ) {		
			memcpy( szReceiverPersonName, receiverPersonName, MAX_PLAYER_NAME );
			szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
		} else {
			szReceiverPersonName[ 0 ] = NULL;
		}

		clItem.Set( pclItem );

		clDate.Set( pclDate );
	}
};

class sDBResponse_PostOfficeMasterSendItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;												// ���

	SI32				siReason;												// ������ ���� ����
	
	SI32				siReceiverPersonID;										// ������ personid

	cltItem				clItem;													// item (�۽���)

	cltDate				clDate;

	sDBResponse_PostOfficeMasterSendItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeMasterSendItem ) );
	}


};


// ��ǰ ������ ��û�Ѵ�
class sDBRequest_PostOfficeSendItem 
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;

	SI32				siSenderPersonID;										// �۽��� personid

	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];				// ������ name

	SI16				siItemInventoryIndex;									// item index
	SI32				siItemUnique;											// item unique
	SI16				siItemNum;												// item num

	cltDate				clDate;													// �۽ų�¥
	GMONEY				siFee;													// ������
	//KHY - 0614 - ���� �������� ���� ������ ĳ���Ϳ� ���Ͽ� �������� �ְ� ���� �� �ִ�. 
	BOOL				bGacha;                                                                             //���� ������ ����.

	sDBRequest_PostOfficeSendItem( UI16 id, SI32 posttype, SI32 villageUnique, SI32 senderpersonid, TCHAR *receiverPersonName,
		SI16 itemInventoryIndex, SI32 itemUnique, SI16 itemNum, cltDate *pclDate, GMONEY fee ,BOOL gacha)
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_SENDITEM;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeSendItem );

		usCharID = id;
		
		siPostType = posttype;
		siVillageUnique = villageUnique;
		siSenderPersonID = senderpersonid;

		memcpy( szReceiverPersonName, receiverPersonName, MAX_PLAYER_NAME );
		szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;

		siItemInventoryIndex = itemInventoryIndex;
		siItemUnique = itemUnique;
		siItemNum = itemNum;

		clDate.Set( pclDate );
		siFee = fee;
		bGacha = gacha;
	}

};

class sDBResponse_PostOfficeSendItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;												// ���

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;										// ��������ũ

	SI32				siSenderPersonID;										// �۽��� personid
	SI32				siReceiverPersonID;										// ������ personid

	SI16				siItemInventoryIndex;									// item index(�۽���)
	SI32				siItemUnique;											// item unique(�۽���)
	SI16				siItemNum;												// item num(�۽���)

	cltMoney			clPostOfficeMoney;										// ���� �����ڱ�
	cltMoney			clPersonMoney;											// �۽��� ������ ����	

	//[�߰� : Ȳ���� 2007. 10. 24 �α׿� �̿�, ������ ������ ����]
	SI16				siSendItemInventoryIndex;									// item index(�۽���)
	SI32				siSendItemUnique;											// item unique(�۽���)
	SI16				siSendItemNum;												// item num(�۽���)

	// PCK : �α׿� ��Ŷ �߰�
	GMONEY				siFee;													// ������.
	sDBResponse_PostOfficeSendItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeSendItem ) );
	}

};

// �۱��� ��û�Ѵ�
class sDBRequest_PostOfficeSendMoney
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;

	SI32				siSenderPersonID;										// �۽��� person id
	
	SI32				siReceiverPersonID;										// ������ person id (0�̸� name���� �˻�)	
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];				// ������ name
	
	GMONEY				siMoney;												// ���� �ݾ� 
	cltDate				clDate;													// ������ �ð� 
	GMONEY				siFee;
	
	sDBRequest_PostOfficeSendMoney( UI16 id, SI32 posttype, SI32 villageUnique, SI32 senderPersonID, SI32 receiverPersonID, TCHAR *receiverPersonName, 
		GMONEY money, cltDate *pclDate, GMONEY fee )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_SENDMONEY;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeSendMoney );

		usCharID = id;

		siPostType = posttype;
		siVillageUnique = villageUnique;
		siSenderPersonID = senderPersonID;

		siReceiverPersonID = receiverPersonID;

		if( receiverPersonName ) {		
			memcpy( szReceiverPersonName, receiverPersonName, MAX_PLAYER_NAME );
			szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
		} else {
			szReceiverPersonName[ 0 ] = NULL;
		}

		siMoney = money;		
		clDate.Set( pclDate );
		siFee = fee;
	}
	
};

class sDBResponse_PostOfficeSendMoney
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;												// ���

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;										// ��������ũ
	
	SI32				siSenderPersonID;										// �۽��� personid
	SI32				siReceiverPersonID;										// ������ personid

	cltMoney			clPostOfficeMoney;										// ���� �����ڱ�
	cltMoney			clPersonMoney;											// �۽��� ������ ����
	
	//[�߰� : Ȳ���� 2007. 10. 25 �α׿� �̿�. �۱ݽ� �۱ݾװ� ������ ����.]
	GMONEY				siMoney;												// ���� �ݾ� 
	GMONEY				siFee;

	sDBResponse_PostOfficeSendMoney()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeSendMoney ) );
	}
};



// �޽��� ������ ��û�Ѵ�
class sDBRequest_PostOfficeSendMsg
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;

	SI32				siSenderPersonID;										// �۽��� person id

	SI32				siReceiverPersonID;										// ������ person id (0�̸� name���� �˻�)
	TCHAR				szReceiverPersonName[ MAX_PLAYER_NAME ];				// ������ name
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽���
	cltDate				clDate;													// ������ �ð� 
	GMONEY				siFee;
	
	sDBRequest_PostOfficeSendMsg( UI16 id, SI32 posttype, SI32 villageUnique, SI32 senderPersonID, 
		SI32 receiverPersonID, TCHAR *receiverPersonName, 
		TCHAR *szmsg, cltDate *pclDate, GMONEY fee )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_SENDMSG;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeSendMsg );

		usCharID = id;

		siPostType = posttype;
		siVillageUnique = villageUnique;
		siSenderPersonID = senderPersonID;

		siReceiverPersonID = receiverPersonID;

		if( receiverPersonName ) {
			memcpy( szReceiverPersonName, receiverPersonName, MAX_PLAYER_NAME );
			szReceiverPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
		} else {
			szReceiverPersonName[ 0 ] = NULL;
		}

		memcpy( szMsg, szmsg, MAX_POSTOFFICE_MSG_SIZE );
		szMsg[ MAX_POSTOFFICE_MSG_SIZE - 1 ] = NULL;
		
		clDate.Set( pclDate );
		siFee = fee;
	}
	
};

class sDBResponse_PostOfficeSendMsg
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;												// ���

	SI32				siPostType;												// 0:�Ϲ�����, 1:���

	SI32				siVillageUnique;										// ��������ũ
	
	SI32				siSenderPersonID;										// �۽��� personid
	SI32				siReceiverPersonID;										// ������ personid

	cltMoney			clPostOfficeMoney;										// ���� �����ڱ�
	cltMoney			clPersonMoney;											// �۽��� ������ ����
	
	// PCK : �α׿� ��Ŷ �߰�
	GMONEY				siFee;													// ������
	TCHAR				szMsg[MAX_POSTOFFICE_MSG_SIZE];							// ������ �޽���

	sDBResponse_PostOfficeSendMsg()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeSendMsg ) );
	}
};

// ���� ������ ����� ��û�Ѵ�
class sDBRequest_PostOfficeRecvItemList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;

	sDBRequest_PostOfficeRecvItemList( UI16 id, SI32 villageunique, SI32 personid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_RECVITEMLIST;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeRecvItemList );

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;
	}
	
};

class sDBResponse_PostOfficeRecvItemList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;

	UI16				usCount;
	cltPostOfficeRecvItemInfo			clRecvItemInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	sDBResponse_PostOfficeRecvItemList()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeRecvItemList ) );
	}

	SI32 GetTotalSize() {
		return sizeof( packetHeader ) + 24 + (sizeof( cltPostOfficeRecvItemInfo ) * usCount );
	}
	
};

// ���� ���� ����� ��û�Ѵ�
class sDBRequest_PostOfficeRecvMoneyList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;

	sDBRequest_PostOfficeRecvMoneyList( UI16 id, SI32 villageunique, SI32 personid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_RECVMONEYLIST;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeRecvMoneyList );

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;
	}
	
};

class sDBResponse_PostOfficeRecvMoneyList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;

	UI16				usCount;
	cltPostOfficeRecvMoneyInfo			clRecvMoneyInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	sDBResponse_PostOfficeRecvMoneyList()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeRecvMoneyList ) );
	}

	SI32 GetTotalSize() {
		return sizeof( packetHeader ) + 24 + (sizeof( cltPostOfficeRecvMoneyInfo ) * usCount );
	}
	
};


// ���� �޽��� ����� ��û�Ѵ�
class sDBRequest_PostOfficeRecvMsgList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siPersonID;

	sDBRequest_PostOfficeRecvMsgList( UI16 id, SI32 villageunique, SI32 personid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_RECVMSGLIST;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeRecvMsgList );

		usCharID = id;

		siVillageUnique = villageunique;
		siPersonID = personid;
	}

};


class sDBResponse_PostOfficeRecvMsgList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siPersonID;

	UI16				usCount;
	cltPostOfficeRecvMsgInfo			clRecvMsgInfo[ MAX_POSTOFFICE_RECV_NUMBER ];

	sDBResponse_PostOfficeRecvMsgList()
	{

	}

	SI32 GetTotalSize() {
		return sizeof( packetHeader ) + 24 + (sizeof( cltPostOfficeRecvMsgInfo ) * usCount );
	}


};


// ���� �������� �� �κ��丮�� �ִ´�
class sDBRequest_PostOfficeGetItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siMsgID;

	SI16				siInventoryIndex;							// �κ��丮 ��ġ
	BOOL				bPile;										// ��ø�ɼ� �ִ°�



	sDBRequest_PostOfficeGetItem( UI16 id, SI32 personid, SI32 msgid, SI16 inventoryindex, BOOL bpile )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_GETITEM;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeGetItem );

		usCharID = id;

		siPersonID = personid;
		siMsgID = msgid;

		siInventoryIndex = inventoryindex;
		bPile = bpile;

	}
};

class sDBResponse_PostOfficeGetItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siResult;

	SI32				siPersonID;
	SI32				siMsgID;

	SI16				siItemInventoryIndex;
	cltItem				clItem;

	SI32				siSenderPersonID;
	TCHAR				szRecverName[ MAX_PLAYER_NAME ];

	SI16				siRecvItemNum;

	sDBResponse_PostOfficeGetItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeGetItem ) );
	}

};

class sDBRequest_PostOfficeGetMoney
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siMsgID;

	sDBRequest_PostOfficeGetMoney( UI16 id, SI32 personid, SI32 msgid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_GETMONEY;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeGetMoney );

		usCharID = id;

		siPersonID = personid;
		siMsgID = msgid;
	}
};

class sDBResponse_PostOfficeGetMoney
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siResult;

	SI32				siPersonID;
	SI32				siMsgID;

	GMONEY				siPersonMoney;			// �������� ������

	SI32				siSenderPersonID;
	TCHAR				szRecverName[ MAX_PLAYER_NAME ];

	sDBResponse_PostOfficeGetMoney()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeGetMoney ) );
	}
};

// ���� �޽����� �����
class sDBRequest_PostOfficeDelMsg
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siMsgID;


	sDBRequest_PostOfficeDelMsg( UI16 id, SI32 personid, SI32 msgid )
	{
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_DELMSG;
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeGetItem );

		usCharID = id;

		siPersonID = personid;
		siMsgID = msgid;
	}
};


 
// ���� ������ ����
class sDBRequest_PostOfficeSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI32				siVillageUnique;			// ������ ��ġ�� ���� VillageUnique

	cltFee				clMoneyFee;					// �۱� ������ 
	cltFee				clItemFee;					// ��ǰ ���� ������ 

	GMONEY				siMsgFee;					// �޽��� ���� ������ (�Ǵ�)
	GMONEY				siRecvFee;					// ������ ���� ������ (ȸ��)


	sDBRequest_PostOfficeSetFee( SI32 id, SI32 personid, SI32 villageunique, 
		cltFee* pclMoneyFee, cltFee* pclItemFee, GMONEY msgfee, GMONEY recvfee )
	{
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeSetFee );
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_SETFEE;

		usCharID		= id;

		siPersonID		= personid;
		siVillageUnique	= villageunique;

		clMoneyFee.Set( pclMoneyFee );
		clItemFee.Set( pclItemFee );

		siMsgFee = msgfee;
		siRecvFee = recvfee;
	}
};


class sDBResponse_PostOfficeSetFee
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siPersonID;
	SI32				siVillageUnique;			// ������ ��ġ�� ������ VillageUnique

	cltFee				clMoneyFee;					// �۱� ������ 
	cltFee				clItemFee;					// ��ǰ ���� ������ 

	GMONEY				siMsgFee;					// �޽��� ���� ������ (�Ǵ�)
	GMONEY				siRecvFee;					// ������ ���� ������ (ȸ��)

	sDBResponse_PostOfficeSetFee()
	{
		ZeroMemory( this, sizeof(sDBResponse_PostOfficeSetFee) );
	}

};

class sDBRequest_PostOfficeGetRecord
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;					// ��û�� personid 

	sDBRequest_PostOfficeGetRecord( SI32 id, SI32 personid )
	{
		packetHeader.usSize = sizeof( sDBRequest_PostOfficeGetRecord );
		packetHeader.usCmd = DBMSG_REQUEST_POSTOFFICE_GETRECORD;

		usCharID		= id;
		siPersonID		= personid;
	}

};

class sDBResponse_PostOfficeGetRecord
{
public:
	sPacketHeader				packetHeader;
	UI16						usCharID;

	SI32						siResult;

	SI32						siPersonID;

	UI16						usCount;
	cltPostOfficeRecordInfo		recordinfo[ MAX_POSTOFFICE_RECORD_NUMBER ];

	sDBResponse_PostOfficeGetRecord()
	{
		ZeroMemory( this, sizeof( sDBResponse_PostOfficeGetRecord ) );
	}

	SI32 GetTotalSize() {
		return sizeof( packetHeader ) + 12 + (sizeof( cltPostOfficeRecordInfo ) * usCount );
	}

};

// ��ڿ��� ������ ������ ��ǰ ����( �ϴ��� ���̱輱���� �����Ѵ� )
class sDBRequest_Get_SaveUserItem
{
public:
	sPacketHeader		packetHeader;
	
	SI16				siCharId;
	SI32				siSaveItemPersonID;		// ������ ���� ���� person id
	SI16				siIndex;				// �޾ƿ� ������ �ε���		
	SI16				siItemPos;				// ������ ��ġ

	bool				bAddItem;				// ������ ���ΰ�?
		
	SI64				siServiceCharge;		// ������

	sDBRequest_Get_SaveUserItem( SI16 charid, SI32 personid, SI16 index, SI16 pos, bool bdd, SI64 servicecharge )
	{

		packetHeader.usCmd = DBMSG_REQUEST_GET_SAVEUSERITEM;
		packetHeader.usSize = sizeof( sDBRequest_Get_SaveUserItem );

		siCharId = charid;
		siSaveItemPersonID = personid;
		siIndex = index;
		siItemPos = pos;

		bAddItem = bdd;
		
		siServiceCharge = servicecharge;

	}
};

class sDBResponse_Get_SaveUserItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI16				siCharId;
	SI32				siSaveItemPersonID;		// ������ ���� ���� person id
	SI16				siIndex;				// ������ �ε���
	SI16				siItemPos;				// ������ ��ġ
	SI64				siUserMoney;
	
	cltItem				clItem;

	sDBResponse_Get_SaveUserItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_Get_SaveUserItem ) );
	}
};

//KHY - 1127 - Ŭ��� ��ǰ ���� ����
class sDBRequest_Get_SaveUserHorse
{
public:
	sPacketHeader		packetHeader;
	
	SI16				siCharId;
	SI32				siSaveItemPersonID;		// ������ ���� ���� person id

	SI16				siIndex;				// �޾ƿ� ��µ�����  �ε���		
	SI32				siEnptyHorseindex;	// �� ��ġ.		
	
	SI64				siServiceCharge;		// ������

	sDBRequest_Get_SaveUserHorse( SI16 charid, SI32 personid, SI16 index, SI32 enptyHorseindex,  SI64 servicecharge )
	{

		packetHeader.usCmd = DBMSG_REQUEST_GET_SAVEUSERHORSE;
		packetHeader.usSize = sizeof( sDBRequest_Get_SaveUserHorse );

		siCharId = charid;
		siSaveItemPersonID = personid;
		siIndex = index;
		siEnptyHorseindex = enptyHorseindex;
		
		siServiceCharge = servicecharge;

	}
};
class sDBResponse_Get_SaveUserHorse
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI16				siCharId;
	SI32				siSaveHorsePersonID;		// ��µ��� ���� ���� person id
	SI16				siIndex;				// ��µ��� �ε���
	SI16				siEnptyHorseindex;				//  ��µ��� ��ġ
	SI64				siUserMoney;
	
	cltHorse			clHorse;

	sDBResponse_Get_SaveUserHorse()
	{
		ZeroMemory( this, sizeof( sDBResponse_Get_SaveUserHorse ) );
	}
};

// ��ڿ��� ������ ������ ��ǰ ����Ʈ ������( �ϴ��� ���̱輱���� �����Ѵ� )
class sDBRequest_Get_SaveUserItemList 
{
public:
	sPacketHeader		packetHeader;

	SI16				siCharId;
	SI32				siSaveItemPersonID;

	sDBRequest_Get_SaveUserItemList(SI16 charid, SI32 personid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_SAVEUSERITEMLIST;
		packetHeader.usSize = sizeof( sDBRequest_Get_SaveUserItemList );

		siCharId = charid;
		siSaveItemPersonID = personid;
	}
};

class sDBResponse_Get_SaveUserItemList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	SI16				siCharId;
	SI32				siSaveItemPersonID;
	
	cltSaveUersItemInfo	clSaveUsersItemInfo[MAX_SAVEUSERITEM_LIST];

	//KHY - 1127 - Ŭ��� ��ǰ ���� ����
	cltSaveUersHorseInfo	clSaveUsersHorseInfo[MAX_SAVEUSERHORSE_LIST];

	sDBResponse_Get_SaveUserItemList() 
	{
		ZeroMemory(this, sizeof(sDBResponse_Get_SaveUserItemList));
	}
};


enum NAME_CHECK_REASON
{ 
	POSTOFFICE_ADD_RECV_USER,						// ��ü������ �޽����� ������ ���� �߰��� ����.
};

class sDBRequest_Char_Name_Check
{
public:
    sPacketHeader		packetHeader;

	SI16				siCharId;
	SI16				siReason;								// �̸��� Ȯ���ϴ� ����.

	TCHAR				m_szCheckPersonName[MAX_PLAYER_NAME];

	sDBRequest_Char_Name_Check( SI16 CharId, SI16 Reason, TCHAR* _pCheckPersonName )
	{
		ZeroMemory(this, sizeof(sDBRequest_Char_Name_Check));

		packetHeader.usCmd  = DBMSG_REQUEST_CHAR_NAME_CHECK;
		packetHeader.usSize = sizeof( sDBRequest_Char_Name_Check );

		siCharId = CharId;
		siReason = Reason;
		memcpy( m_szCheckPersonName, _pCheckPersonName, sizeof(m_szCheckPersonName) );
	}
};

class sDBResponse_Char_Name_Check
{
public:
	sPacketHeader		packetHeader;

	SI16				siCharId;
	SI16				siReason;						// �̸��� Ȯ���ϴ� ����.
	SI16				CheckPersonLevel;				// ����.
	SI16				CheckPersonVillage;				// ���� ����.
	cltSimplePerson		CheckPersonInfo;

	SI32				siResult;						// �����.
	

	sDBResponse_Char_Name_Check() 
	{
		ZeroMemory(this, sizeof(sDBResponse_Char_Name_Check));
	}
};


//----------------------------------------------------------------------------------------------
// �ۼ��� : 2008-8-6
//
// �׷� ����Ʈ ��û. (ģ��, ���, �ֹ� ��..)	
//
// - ���Ӿȵ� ���� ���� ������ ��� ����� DB�� �ʿ��� ���� ��û.
//
//----------------------------------------------------------------------------------------------
// ����Ʈ ��û ����.
enum GROUP_LIST_REQUEST_REASON
{
	POSTOFFICE_GOURP_MESSAGE = 1,			// ��ü���� ��ü �޽����� �̿�.

};

//[����] ���, ģ��, �ֹε��� ����Ʈ�� ��û�Ҷ� ���� ���� ����.
class clCharInfo
{
public:
	SI16	m_siLevel;
	SI16	m_siVillageUnique;
	SI32	m_siPersonID;
	TCHAR	m_PersonName[MAX_PLAYER_NAME];

	clCharInfo()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ģ�� ��� ��û.	=> 2008-8-
class sDBRequest_Friend_Info
{
public:
	sPacketHeader		m_packetHeader;

	SI08				m_siRequestReason;	//��û ����.

	SI16				m_siCharId;
	SI32				m_siPersonID;

	sDBRequest_Friend_Info(SI08	_siRequestReason, SI16	_siCharId, SI32 _siPersonID)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd  = DBMSG_REQUEST_FRIEND_INFO;
		m_packetHeader.usSize = sizeof( sDBRequest_Friend_Info );

		m_siRequestReason =	_siRequestReason;
		m_siCharId		  =	_siCharId;
		m_siPersonID	  =	_siPersonID;
	}
};


class sDBResponse_Friend_Info
{
public:
	sPacketHeader		m_packetHeader;

	SI08				m_siRequestReason;	//��û ����.
	SI16				m_siCharId;
	clCharInfo			m_clCharInfo[MAX_FRIEND_NUMBER];

	sDBResponse_Friend_Info()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ��� ��� ��û.	=> 2008-8-
class sDBRequest_Guild_Info
{
public:
	sPacketHeader		m_packetHeader;

	SI08				m_siRequestReason;	//��û ����.
	SI16				m_siCharId;
	SI32				m_GuildUnique;

	sDBRequest_Guild_Info(SI08	_siRequestReason, SI16	_siCharId, SI32 _GuildUnique)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd  = DBMSG_REQUEST_GUILD_INFO;
		m_packetHeader.usSize = sizeof( sDBRequest_Guild_Info );

		m_siRequestReason =	_siRequestReason;
		m_siCharId		  =	_siCharId;
		m_GuildUnique	  =	_GuildUnique;
	}

};


class sDBResponse_Guild_Info
{
public:	
	sPacketHeader		m_packetHeader;

	SI08				m_siRequestReason;	//��û ����.
	SI16				m_siCharId;
	clCharInfo			m_clCharInfo[MAX_GUILD_MEMBER_NUM];

	sDBResponse_Guild_Info()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

//[����] ���� �ֹ� ��� ��û.	=> 2008-8-
class sDBRequest_Village_Resident_Info
{
public:
	sPacketHeader		m_packetHeader;

    SI08				m_siRequestReason;	//��û ����.
	SI16				m_siCharId;
	SI32				m_VillageUnique;

	sDBRequest_Village_Resident_Info(SI08	_siRequestReason, SI16	_siCharId, SI16 _VillageUnique)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usCmd  = DBMSG_REQUEST_VILLAGE_RESIDENT_INFO;
		m_packetHeader.usSize = sizeof( sDBRequest_Village_Resident_Info );

		m_siRequestReason =	_siRequestReason;
		m_siCharId		  =	_siCharId;
		m_VillageUnique	  =	_VillageUnique;
	}
};


class sDBResponse_Village_Resident_Info
{
public:
	sPacketHeader		m_packetHeader;

	SI08				m_siRequestReason;	//��û ����.
	SI16				m_siCharId;
	clCharInfo			m_clCharInfo[MAX_RESIDENT_NUMBER];

	sDBResponse_Village_Resident_Info()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};



#endif
