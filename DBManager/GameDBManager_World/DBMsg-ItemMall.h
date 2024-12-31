#ifndef _DBMSGITEMALL_H
#define _DBMSGITEMALL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

#define MAX_ITEMMALL_LIST_NUM		6		// ����Ʈ �ϳ��� �ִ� ��ǰ ��
#define MAX_ITEMMALL_SET_NUM		10		// ��Ʈ ��ǰ�� �� �� �ִ� �ִ� ������ ��

// ������ ������ ����Ʈ �ҷ��� ���� ����Ÿ
class cltItemMallListData{
public:
	SI32	siProductKey;		// ��ǰ �ڵ�
	SI32	siGroupKey;			// �׷� �ڵ�

	bool	bGiftFlag;			// �������� �ڵ�

	TCHAR	szName[128];		// ��ǰ �̸�

	SI32	siPrice;			// ��ǰ ����
	SI32	siEventPrice;		// ��ǰ �̺�Ʈ ����

	SI32	siSprFont;			// ��ǰ�� �̹��� ��Ʈ
	TCHAR	szExplain[256];		// ���ν��������� title
	TCHAR	szExplain2[256];	//	[��ȣ] ��ǰ�� ���� ����2

	bool	bOnlyBuySilverCoin;	// �������θ� ���Ű� �����ϴ�
	
	bool	bAgeLimit;			//[����] �ŷ�����. KOR: ����, ENG: ���� 
};

// ������ ������ ��Ʈ ��ǰ�� ������ ����Ÿ - ����ũ�� ������ ������ ��
class cltItemMallSetData{
public:
	SI32 siUnique[MAX_ITEMMALL_SET_NUM];
	SI32 siItemNum[MAX_ITEMMALL_SET_NUM];
	SI16 siLimitLevel[MAX_ITEMMALL_SET_NUM];
};

// ������ ������ �׷� ������(�Ⱓ�� �����۵�)�� �׷� �� ������
class cltItemMallDateItemInfo{
public:
	SI32		siProductKey; // ��ǰ Ű��
	TCHAR		szName[128]; // ��ǰ �̸�
	SI32		siPrice; // ��ǰ�� ����
};

class sDBRequest_ItemMallExistence
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	sDBRequest_ItemMallExistence(UI16 charid, SI32 personid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLEXISTENCE;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallExistence );

		usCharID		= charid;
		siPersonID		= personid;
	}
};

class sDBResponse_ItemMallExistence
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	bool				bExistence;

	sDBResponse_ItemMallExistence()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMallExistence));
	}
};

class sDBRequest_ItemMallItemList
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siMaxListItemNum;
	SI32				siListPage;

	sDBRequest_ItemMallItemList(UI16 charid, SI32 personid,SI32 listitemnum,SI32 page)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLITEMLIST;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallItemList );

		usCharID			= charid;
		siPersonID			= personid;

		siMaxListItemNum	= listitemnum;
		siListPage			= page;
	}
};

class sDBResponse_ItemMallItemList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siListPage;
	SI32				siTotalItemNum;

	SI32				siItemID[MAX_ITEMNUM_PER_ITEMMALL]; // ������ ��ȣ
	cltItem				clItem[MAX_ITEMNUM_PER_ITEMMALL];

	sDBResponse_ItemMallItemList()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMallItemList));
	}
};

class sDBRequest_ItemMallGetItem
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem( UI16 charid, SI32 personid,
		SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBRequest_ItemMallGetItem_Global
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_Global( UI16 charid, SI32 personid,
		SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_GLOBAL;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_Global );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBRequest_ItemMallGetItem_China
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_China( UI16 charid, SI32 personid,
		SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_CHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_China );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};


class sDBRequest_ItemMallGetItem_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_Korea( UI16 charid, SI32 personid,
									SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_KOREA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_Korea );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBRequest_ItemMallGetItem_NHNChina
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_NHNChina( UI16 charid, SI32 personid,
									SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_NHNCHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_NHNChina );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBRequest_ItemMallGetItem_USA
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_USA( UI16 charid, SI32 personid,
									SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_USA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_USA );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBRequest_ItemMallGetItem_Taiwan
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_Taiwan(	UI16 charid, SI32 personid,
		SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_TAIWAN;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_Taiwan );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};

class sDBResponse_ItemMallGetItem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �κ��丮 ��ġ

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// ������ ����

	bool				bPossession;

	sDBResponse_ItemMallGetItem()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMallGetItem));
	}
};

class sDBRequest_NewsChatAddmission // �ڸ����� ���� ��û
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �ִ� �κ��丮
	cltItem				clItem;			// ���������� ������ ����
	
	bool				bUseColorNews;

	TCHAR				szChatText[256];// ä�� ����Ÿ

	sDBRequest_NewsChatAddmission( UI16 charid, SI32 personid,
		SI16 pos,cltItem *pclitem, bool busecolornews ,TCHAR* chattext)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_NEWSCHATADDMISSION;
		packetHeader.usSize = sizeof( sDBRequest_NewsChatAddmission );

		usCharID		= charid;
		siPersonID		= personid;

		siInvPos		= pos;
		clItem.Set(pclitem);

		bUseColorNews = busecolornews;

		memcpy( szChatText, chattext, 256 );
		szChatText[ 255 ] = NULL;
	}
};

class sDBResponse_NewsChatAddmission
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �κ��丮 ��ġ
	cltItem				clItem;			// ���� ������ ����
	
	bool				bUseColorNews;

	TCHAR				szChatText[256];// ä�� ����Ÿ

	sDBResponse_NewsChatAddmission()
	{
		ZeroMemory(this, sizeof(sDBResponse_NewsChatAddmission));
	}
};

#define NOLIMIT_SET_TICKET_30			0
#define NOLIMIT_SET_TICKET_90			1
#define NOLIMIT_SET_TICKET_210			2
#define NOLIMIT_SET_TICKET_420			3
#define NOLIMIT_SET_TICKET_900			4
#define NOLIMIT_SET_TICKET_DELETE		5
#define NOLIMIT_SET_TICKET_PREMIUM1		6	// �����̾� 30��
#define NOLIMIT_SET_TICKET_PREMIUM2		7	// �����̾� 900��
#define MARKET_SET_TICKET_900			8	// �����̾� 900��
#define SPACEBOX_1						9	// �������� 1��
#define SPACEBOX_7						10	// �������� 7��
#define SPACEBOX_30						11	// �������� 30��


#define NOLIMIT_TICKET			1
#define MARKET_TICKET			2
#define SPACEBOX_TICKET			3		// Ƽ��Ÿ�� ��������Ÿ��
#define SUMMON_SPACE_TICKET		4		// Ƽ��Ÿ�� ��ȯ�� ����Ȯ��
#define NewMarket_TICKET		5		// [����] ���ո���.

//***************************************************************************************************
//
// Class Name 		: sDBRequest_NoLimitTicket_Warp
//
// Last Modified 	: 2007 / 08 / 09
// Created		 	: �豤��
//
// Function			: Ƽ���� �̿��� �����̾� ���� ����( �����̵�, ���� �̿��)
//
//***************************************************************************************************
class sDBRequest_NoLimitTicket_Warp
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	bool				bUsing;			// ����ߴ°� �ƴϸ� �����°�

	SI16				siInvPos;		// �������� �ִ� �κ��丮
	cltItem				clItem;			// ���������� ������ ����

	SI32				siDateVary;		// ������ �ð�

	SI32				siType;			// ���� ����

	sDBRequest_NoLimitTicket_Warp( bool use , UI16 charid, SI32 personid, SI16 pos,cltItem *pclitem , SI32 datevary, SI32 Type )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_NOLIMITTICKET_WARP;
		packetHeader.usSize = sizeof( sDBRequest_NoLimitTicket_Warp );

		usCharID		= charid ;
		siPersonID		= personid ;

		bUsing			= use ;

		siInvPos		= pos ;
		clItem.Set(pclitem);

		siDateVary		= datevary ;

		siType = Type;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_NoLimitTicket_Warp
//
// Last Modified 	: 2007 / 08 / 09
// Created		 	: �豤��
//
// Function			: Ƽ���� �̿��� �����̾� ���� ����( �����̵�, ���� �̿��)
//
//***************************************************************************************************
class sDBResponse_NoLimitTicket_Warp
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	bool				bUsing;			// ����ߴ°� �ƴϸ� �����°�

	SI16				siInvPos;		// �������� �ִ� �κ��丮
	cltItem				clItem;			// ���������� ������ ����

	SI32				siDateVary;		// ������ �ð�

	SI32				siType;

	sDBResponse_NoLimitTicket_Warp()
	{
		ZeroMemory(this, sizeof(sDBResponse_NoLimitTicket_Warp));
	}	
};


// �����۸����� ��з��� �Һз��� �������� ��ǰ ����Ʈ�� ��û�Ѵ�.
class sDBRequest_Get_Sel_PGList
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siMainCategory; // ��з�
	SI32				siSubCategory; // �Һз�

	TCHAR				szType[4] ; // ��ǰ ����

	SI32				siPage ; // �ҷ��� ������
	SI08				siAllowGrownUpItem;

	sDBRequest_Get_Sel_PGList(UI16 id ,SI32 personid,SI32 main,SI32 sub,TCHAR* type,SI32 page, SI08 AllowGrownUpItem = 0 )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_SEL_PGLIST;
		packetHeader.usSize = sizeof( sDBRequest_Get_Sel_PGList );

		usCharID = id ;
		siPersonID = personid;

		siMainCategory = main ;
		siSubCategory = sub ;

		MStrCpy(szType,type,4) ;

		siPage = page ;

		siAllowGrownUpItem = AllowGrownUpItem;
	}
};

class sDBResponse_Get_Sel_PGList
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siMainCategory; // ��з�
	SI32				siSubCategory; // �Һз�

	TCHAR				szType[4] ; // ��ǰ ����

	SI32				siPage ; // �ҷ��� ������
	SI32				siMaxPage;

	cltItemMallListData clListData[MAX_ITEMMALL_LIST_NUM];
	cltItemMallSetData clItemData[MAX_ITEMMALL_LIST_NUM];
	
	sDBResponse_Get_Sel_PGList()
	{
		ZeroMemory(this, sizeof(sDBResponse_Get_Sel_PGList));
	}
};

// ������ �������� �� ���� �� �׷� ������ ������ �ҷ��´�.
class sDBRequest_Get_ItemMall_ItemInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siGroupKey; // �׷�Ű��

	sDBRequest_Get_ItemMall_ItemInfo(UI16 id ,SI32 personid,SI32 key)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_ITEMMALL_ITEMINFO;
		packetHeader.usSize = sizeof( sDBRequest_Get_ItemMall_ItemInfo );

		usCharID = id ;
		siPersonID = personid;

		siGroupKey = key;
	}
};

class sDBResponse_Get_ItemMall_ItemInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	cltItemMallDateItemInfo clItemData[3]; // ����( �Ⱓ���� �����۵� �����̴�. )

	sDBResponse_Get_ItemMall_ItemInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_Get_ItemMall_ItemInfo));
	}
};

// �� ĳ�� ������ �����´�.
class SDBRequest_Get_MyCash_Info
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ĳ��

	SDBRequest_Get_MyCash_Info(UI16 charid , SI32 personid, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}
};

class SDBResponse_Get_MyCash_Info
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;

	SI32				siCash;			// �� ĳ�� ����
	SI32				siEventCash;	// �̺�Ʈ ����

	SDBResponse_Get_MyCash_Info()
	{
		ZeroMemory(this, sizeof(SDBResponse_Get_MyCash_Info));
	}
};

// ������ ���
class sDBRequest_ItemMall_Buyitem
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	sDBRequest_ItemMall_Buyitem(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
	}
};

class sDBResponse_ItemMall_Buyitem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;						// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ;					// ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum;					// ���� ����
	SI32				siProductPrice;					// �ֹ� �ݾ�
	SI32				siProductEventPrice;			// �ֹ� �ݾ�

	SI32				siCash;							// �� ĳ�� ����
	SI32				siEventCash;					// �̺�Ʈ ����

	TCHAR				szTxNoCode[50] ;				// ���� ���� ��ȣ
	TCHAR				szItemName[50];

	sDBResponse_ItemMall_Buyitem()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMall_Buyitem));
	}
};

class sDBResponse_ItemMall_Buyitem_ForXNoti
{
public:
	sPacketHeader		packetHeader;

	SI32				siArrayIndex;
	SI32				siResult ;		// 1�ܿ��� ����

	SI32				siIdx;
	TCHAR				szTxCode[50];

	sDBResponse_ItemMall_Buyitem_ForXNoti()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMall_Buyitem_ForXNoti));
	}
};

// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	
	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	sDBRequest_ItemMall_Giftitem(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;
		
		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;
	}
};

class sDBResponse_ItemMall_Giftitem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	SI32				siCash;			// �� ĳ�� ����
	SI32				siEventCash;	// �̺�Ʈ ����

	TCHAR				szTxNoCode[50] ; // ���� ���� ��ȣ
	TCHAR				szItemName[50];
	

	TCHAR				szComment[200] ; // ���� �޽���
	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	SI32				siGetItemPersonID;	// ���� ���� ����� PersonID

	SI32				siHanFailReason;	// [����] hangame �����ֱ⿡ ������ ����. => 2008-7-24


	sDBResponse_ItemMall_Giftitem()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMall_Giftitem));
	}
};

class sDBResponse_ItemMall_Giftitem_ForXNoti
{
public:
	sPacketHeader		packetHeader;

	SI32				siArrayIndex;
	SI32				siResult ;		// 1�ܿ��� ����

	SI32				siIdx;
	TCHAR				szTxCode[50];

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���

	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	TCHAR				szSendCharName[MAX_PLAYER_NAME];	//[����] ������ �ִ� ���� ĳ���� �̸�. => 2008-7-24
	
	sDBResponse_ItemMall_Giftitem_ForXNoti()
	{
		ZeroMemory(this, sizeof(sDBResponse_ItemMall_Giftitem_ForXNoti));
	}
};


class sDBRequest_ItemMall_CancelOrder_XNoti
{
public:
	sPacketHeader		packetHeader;

	TCHAR				szTxCode[50];

	sDBRequest_ItemMall_CancelOrder_XNoti(TCHAR* pszTxCode)
	{
		packetHeader.usCmd = DBMSG_REQUEST_ITEMMALL_CANCELORDER_XNOTI;
		packetHeader.usSize = sizeof(sDBRequest_ItemMall_CancelOrder_XNoti);

		ZeroMemory(szTxCode, sizeof(szTxCode));
		if(pszTxCode)	StringCchCopy(szTxCode, sizeof(szTxCode), pszTxCode);
	}
};

//-----------------------------------------------------------
// �۷ι��� ����, ���� �޼���
//-----------------------------------------------------------
// ������ ���
class sDBRequest_ItemMall_Buyitem_Global
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	sDBRequest_ItemMall_Buyitem_Global(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_GLOBAL;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_Global );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
	}
};

// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem_Global
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	sDBRequest_ItemMall_Giftitem_Global(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_GLOBAL;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_Global );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;
	}
};


class sDBRequest_ItemMall_Buyitem_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	sDBRequest_ItemMall_Buyitem_Korea(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_KOREA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_Korea );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
	}
};

// [��ȣ_NHN->NDOORS] �����۸� �ܾ���ȸ
class SDBRequest_Get_MyCash_Info_nDoors_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ĳ��

	SDBRequest_Get_MyCash_Info_nDoors_Korea(UI16 charid , SI32 personid, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_NDOORS_KOREA;
		packetHeader.usSize = sizeof(SDBRequest_Get_MyCash_Info_nDoors_Korea);

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}
};

// [��ȣ_NHN->NDOORS] �����۸� �ܾ���ȸ
class sDBRequest_ItemMall_Buyitem_nDoors_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	sDBRequest_ItemMall_Buyitem_nDoors_Korea(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_NDOORS_KOREA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_nDoors_Korea );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
	}
};

// [��ȣ_NHN->NDOORS] �����۸� �����ϱ�
class sDBRequest_ItemMall_Giftitem_nDoors_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	sDBRequest_ItemMall_Giftitem_nDoors_Korea(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_NDOORS_KOREA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_nDoors_Korea );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;
	}
};

class sDBRequest_ItemMall_Buyitem_USA
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szProductName[50];
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	UI32				uiIDNo;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

	sDBRequest_ItemMall_Buyitem_USA(UI16 charid , SI32 personid ,SI32 key, TCHAR* name, TCHAR* account, SI32 num, SI32 price, TCHAR* ip, TCHAR* itemname, UI32 idno)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_USA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_USA );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID, account, MAX_PLAYER_NAME) ;
		MStrCpy(szProductName, name, sizeof(szProductName)) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);

		uiIDNo			= idno;
	}
};

// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	sDBRequest_ItemMall_Giftitem_Korea(UI16 charid , SI32 personid ,SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_KOREA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_Korea );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;
	}
};

//KHY - 0304 - �߱� NHNChinaBilling - 
// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem_NHNChina
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ;						// ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME];		// ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ;	// ���� ���� ��� AccountID
	SI32				siProductNum;						// ���� ����
	SI32				siProductPrice;						// �ֹ� �ݾ�
	SI32				siProductEventPrice;				// �ֹ� �ݾ�

	TCHAR				szComment[200] ;					// ���� �޽���
	TCHAR				szIP[64];							// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	TCHAR				szName[MAX_PLAYER_NAME];
	SI32				siServerID;

	sDBRequest_ItemMall_Giftitem_NHNChina(	UI16	charid, 
											SI32	personid, 
											SI32	key,
											TCHAR*	account,
											TCHAR*	getaccount,
											SI32	num,	 
											SI32	price,	
											SI32	Eventprice,	
											TCHAR*	comment,
											TCHAR*	ip,
											TCHAR*	itemname,
											SI16	GetServerUnique, 
											TCHAR*	GetCharName, 
											SI32	ItemImageFont,
											TCHAR*	Name, 
											SI32	ServerID)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_NHNCHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_NHNChina );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum		= num ;
		siProductPrice		= price ;
		siProductEventPrice = Eventprice;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;

		MStrCpy(szName,Name,MAX_PLAYER_NAME) ;
		siServerID	= ServerID ;
	}
};

// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem_USA
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szProductName[50] ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID 
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];		// ������ ���� ĳ������ �̸�.
	SI32				siItemImageFont;

	UI32				uiIDNo;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11
	
	sDBRequest_ItemMall_Giftitem_USA(UI16 charid , SI32 personid ,SI32 key, TCHAR* productname, TCHAR* account, TCHAR* getaccount,
									SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont, UI32 idno )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_USA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_USA );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;		
		MStrCpy(szProductName,productname,sizeof(szProductName)) ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName, GetCharName, MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;	
		uiIDNo			= idno;	
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ItemMall_Buyitem_ForXNoti
//
// Last Modified 	: 2007 / 08 / 14
// Created		 	: �̰���
//
// Function			: �� �������� ������ �������� DB�� �߰��Ѵ�.
//
//***************************************************************************************************
class sDBRequest_ItemMall_Buyitem_ForXNoti
{
public:
	sPacketHeader		packetHeader;

	SI32				siArrayIndex;
	SI32				siIdx;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	TCHAR				szCharName[MAX_PLAYER_NAME];	// ���� ĳ���� �̸�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szTxCode[50];

	SI32				siServiceArea;				// ���� ���� - by LEEKH 2007.11.11

	sDBRequest_ItemMall_Buyitem_ForXNoti(SI32 arrayindex, SI32 idx, TCHAR* paccountid, TCHAR* pcharname, SI32 key, SI32 num, SI32 price, TCHAR* ptxcode, SI32 servicearea)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_FORXNOTI;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_ForXNoti );

		siArrayIndex	= arrayindex;
		siIdx			= idx;

		siProductKey	= key ;
		MStrCpy(szMyAccountID, paccountid, MAX_PLAYER_NAME) ;
		MStrCpy(szCharName, pcharname, MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szTxCode, ptxcode, 50);
		siServiceArea	= servicearea;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ItemMall_Giftitem_ForXNoti
//
// Last Modified 	: 2007 / 08 / 14
// Created		 	: �̰���
//
// Function			: �� �������� ������ �������� DB�� �߰��Ѵ�. �����ϱ�
//
//***************************************************************************************************
class sDBRequest_ItemMall_Giftitem_ForXNoti
{
public:
	sPacketHeader		packetHeader;

	SI32				siArrayIndex;
	SI32				siIdx;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szTxCode[50];

	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	TCHAR				szSendCharName[MAX_PLAYER_NAME];	//[����] ������ �ִ� ���� ĳ���� �̸�. => 2008-7-24

	sDBRequest_ItemMall_Giftitem_ForXNoti(SI32 arrayindex, SI32 idx, SI32 key,TCHAR* account, TCHAR* getaccount,
		SI32 num, SI32 price, TCHAR* comment, TCHAR* txCode, TCHAR* GetCharName, TCHAR* SendCharName )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_FORXNOTI;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_ForXNoti );

		siArrayIndex	= arrayindex;
		siIdx			= idx ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID, account, MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID, getaccount, MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment, comment, 200) ;
		MStrCpy(szTxCode, txCode, 50) ;

		MStrCpy(szGetCharName,  GetCharName,  MAX_PLAYER_NAME) ;
		MStrCpy(szSendCharName, SendCharName, MAX_PLAYER_NAME) ;
	}
};


//***************************************************************************************************
//
// Class Name 		: sDBRequest_ItemMall_Buyitem_China
//
// Last Modified 	: 2007 / 06 / 08
// Created		 	: �豤��
//
// Function			: �����۸����� ������ �����Ҷ� ����Ѵ�(�߱�������)
//
//***************************************************************************************************
class sDBRequest_ItemMall_Buyitem_China
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�
	SI32				siEventPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	TCHAR				szSecondPassWord[9];

	sDBRequest_ItemMall_Buyitem_China( SI32 charid , SI32 personid ,SI32 key, TCHAR*account,
		                               SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname, TCHAR* SecondPassWord )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_CHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_China );

		siCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
		MStrCpy(szSecondPassWord, SecondPassWord, 9);
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ItemMall_Giftitem_China
//
// Last Modified 	: 2007 / 06 / 08
// Created		 	: �豤��
//
// Function			: �����۸����� ������ �����Ҷ� ����Ѵ�(�߱�������)
//
//***************************************************************************************************
class sDBRequest_ItemMall_Giftitem_China
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	TCHAR				szSecondPassWord[9];


	sDBRequest_ItemMall_Giftitem_China( UI16 charid , SI32 personid ,SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, 
		SI32 ItemImageFont, TCHAR* SecondPassWord )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_CHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_China );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;

		MStrCpy(szSecondPassWord, SecondPassWord, 9);

	}
};

// �� ĳ�� ������ �����´�.
class SDBRequest_Get_MyCash_Info_Global
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ĳ��

	SDBRequest_Get_MyCash_Info_Global(UI16 charid , SI32 personid, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_GLOBAL;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info_Global );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}
};

//***************************************************************************************************
//
// Class Name 		: SDBRequest_Get_MyCash_Info_China
//
// Last Modified 	: 2007 / 06 / 08
// Created		 	: �豤��
//
// Function			: �� ĳ�������� �˾ƿ´�(�߱���)
//
//***************************************************************************************************
class SDBRequest_Get_MyCash_Info_China
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; 

	SDBRequest_Get_MyCash_Info_China(UI16 charid , SI32 personid, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_CHINA;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info_China );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}
};

//-----------------------------------------------------------

class SDBRequest_Get_MyCash_Info_Korea
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ĳ��

	SDBRequest_Get_MyCash_Info_Korea(UI16 charid , SI32 personid, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_KOREA;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info_Korea );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}

};

//KHY - 0304 - �߱� NHNChinaBilling - �� �ܾ��� �˾ƿ´�.
class SDBRequest_Get_MyCash_Info_NHNChina
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; 
	SI32 				siServerID;

	SDBRequest_Get_MyCash_Info_NHNChina(UI16 charid , SI32 personid, TCHAR* accountid ,SI32 	ServerID)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_NHNCHINA;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info_NHNChina );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
		siServerID = ServerID;
	}
};

//KHY - 0304 - �߱� NHNChinaBilling - 
class sDBRequest_ItemMall_Buyitem_NHNChina
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siProductKey ;					// ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum;					// ���� ����
	SI32				siProductPrice;					// �ֹ� �ݾ�
	SI32				siProductEventPrice;			//[����] �߱� �����۸� �̺�Ʈ �ֹ� �ݾ�

	TCHAR				szIP[64];						// IP
	TCHAR				szItemName[50];
	TCHAR				szName[MAX_PLAYER_NAME];
	SI32				siServerID;

	sDBRequest_ItemMall_Buyitem_NHNChina( UI16 charid , 
										  SI32 personid ,
										  SI32 key,
										  TCHAR*account,
										  SI32 num,
										  SI32 price,	
										  SI32 Eventprice,	
										  TCHAR*ip, 
										  TCHAR* itemname , 
										  TCHAR* Name ,
										  SI32 ServerID  )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_NHNCHINA;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_NHNChina );

		usCharID		= charid ;
		siPersonID		= personid ;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum		= num ;
		siProductPrice		= price ;
		siProductEventPrice	= Eventprice ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
		MStrCpy(szName, Name, MAX_PLAYER_NAME);
		siServerID = ServerID;
	}
};


class sDBRequest_Get_MyCash_Info_USA
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // 

	UI32				uiIDNo;		// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11

	sDBRequest_Get_MyCash_Info_USA(UI16 charid , SI32 personid, TCHAR* accountid, UI32 idno)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_USA;
		packetHeader.usSize = sizeof( sDBRequest_Get_MyCash_Info_USA );

		usCharID		= charid ;
		siPersonID		= personid ;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);

		uiIDNo			= idno;
	}

};

// ���̵� �˻��ϱ�
class sDBRequest_Check_AccountID
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siServerUnique;
	TCHAR				szCharName[MAX_PLAYER_NAME] ; // ���� ���� ������ ĳ���� �̸�

	sDBRequest_Check_AccountID(UI16 charid , SI32 personid , SI16 ServerUnique, TCHAR* CharName)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_CHECK_ACCOUNTID;
		packetHeader.usSize = sizeof( sDBRequest_Check_AccountID );
        
		usCharID		= charid ;
		siPersonID = personid;
		siServerUnique = ServerUnique;
		MStrCpy(szCharName,CharName,MAX_PLAYER_NAME);
	}
};

class sDBResponse_Check_AccountID
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�̸� ���̵� ����, �������� ���̵� �������� ����

	UI16				usCharID;
	SI32				siPersonID;

	SI16				siServerUnique;
	TCHAR				szCharName[MAX_PLAYER_NAME] ;		// ���� ���� ������ ĳ���� �̸�

	TCHAR				szAccountID[MAX_PLAYER_NAME] ;		// ���� ���� ��� ID
	TCHAR				szAccountName[MAX_PLAYER_NAME] ;	// ���� ���� ��� �̸�


	sDBResponse_Check_AccountID()
	{
		ZeroMemory(this, sizeof(sDBResponse_Check_AccountID));
	}
};

#define MAX_NUM_PER_BAGITEM			10

// ���ָӴ� ������ �����ϱ�
class sDBRequest_Set_Bagitem
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siFromPos; // ����� ������ ��ġ
	cltItem				clFromItem; // ����� ������

	SI16				siPos[MAX_NUM_PER_BAGITEM]; // ������ ��ġ
	cltItem				clItem[MAX_NUM_PER_BAGITEM]; // ������ ������

	sDBRequest_Set_Bagitem(SI32 charid,SI32 personid,SI16 frompos,cltItem*fromitem,SI16*pos,cltItem*pclitem)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SET_BAGITEM;
		packetHeader.usSize = sizeof( sDBRequest_Set_Bagitem );

		siCharID = charid ;
		siPersonID = personid ;

		siFromPos = frompos ;
		clFromItem.Set(fromitem);

		for ( SI32 i = 0 ; i < MAX_NUM_PER_BAGITEM ; i ++ )
		{
			siPos[i] = pos[i] ;
			clItem[i].Set(&pclitem[i]);
		}
	}
};

class sDBResponse_Set_Bagitem
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ��� ����

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siLeftPos; // ����� ������ ��ġ
	cltItem				clLeftItem; // ����� ������

	SI16				siPos[MAX_NUM_PER_BAGITEM]; // �� ��ġ
	cltItem				clItem[MAX_NUM_PER_BAGITEM]; // �� ������

	sDBResponse_Set_Bagitem()
	{
		ZeroMemory(this, sizeof(sDBResponse_Set_Bagitem));
	}
};

//-------------------------------------
// �������� �����ϰ� �����.
//--------------------------------------
class sDBRequest_Set_ChangeHero
{
public:
	sPacketHeader	packetHeader;

	SI32			siCharID;
	SI32			siPersonID;

	SI16			siPos;
	cltItem			clitem;

	SI32			siCode;

	sDBRequest_Set_ChangeHero(SI32 charid,SI32 personid,SI16 pos,cltItem*pclitem,SI32 code)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SET_CHANGEHERO;
		packetHeader.usSize = sizeof( sDBRequest_Set_ChangeHero );

		siCharID = charid;
		siPersonID = personid;

		siPos = pos;
		clitem.Set(pclitem);

		siCode = code;
	}
};

class sDBResponse_Set_ChangeHero
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ��� ����

	SI32				siCharID;
	SI32				siPersonID;

	SI16				siPos; // ����� ������ ��ġ
	cltItem				clItem; // ����� ������

	SI32				siCode;

	sDBResponse_Set_ChangeHero()
	{
		ZeroMemory(this, sizeof(sDBResponse_Set_ChangeHero));
	}

};

/*
// �������� �������� ���̵� �ٰŷ� ��ǰ ������ ��û�Ѵ�.
class sDBRequest_Get_Present_ItemData
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	
	SI32				siItemID;

	sDBRequest_Get_Present_ItemData(UI16 id ,SI32 personid,SI32 siItemID)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_PRESENT_ITEMDATA;
		packetHeader.usSize = sizeof( sDBRequest_Get_Present_ItemData );

		usCharID = id ;
		siPersonID = personid;
		
		siItemID = siItemID;
	}
};


class sDBResponse_Get_Present_ItemData
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ;		// 1�ܿ��� ����

	UI16				usCharID;
	SI32				siPersonID;

	cltItem				clItemData;


	sDBResponse_Get_Present_ItemData()
	{
		ZeroMemory(this, sizeof(sDBResponse_Get_Present_ItemData));
	}
};
*/


// [��ȣ] �� ĳ�� ������ �����´�.
class SDBRequest_Get_MyCash_Info_Germany
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;								//	Character UniqueID
	SI32				siPersonID;								//	PersonID
	SI32				siIDNumber;								//	����Billing�� �ʿ��� AccountID Number
	TCHAR				szMyAccountID[MAX_PLAYER_NAME];			//	����Billing�� �ʿ��� AccountID String

	SDBRequest_Get_MyCash_Info_Germany(UI16 charid , SI32 personid, SI32 IDNumber, TCHAR* accountid)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GET_MYCASH_INFO_GERMANY;
		packetHeader.usSize = sizeof( SDBRequest_Get_MyCash_Info_Germany );

		usCharID		=	charid ;
		siPersonID		=	personid ;
		siIDNumber		=	IDNumber;

		MStrCpy(szMyAccountID, accountid, MAX_PLAYER_NAME);
	}
};


//	[��ȣ] ������ ����
class sDBRequest_ItemMall_Buyitem_Germany
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siIDNumber;	

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szIP[64];	// IP
	TCHAR				szItemName[50];

	sDBRequest_ItemMall_Buyitem_Germany(UI16 charid , SI32 personid , SI32 IDNumber, SI32 key,TCHAR*account,SI32 num,SI32 price,	TCHAR*ip, TCHAR* itemname)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_BUYITEM_GERMANY;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Buyitem_Germany );

		usCharID		= charid ;
		siPersonID		= personid ;
		siIDNumber		= IDNumber;

		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName, itemname, 50);
	}
};


// ������ �����ϱ�
class sDBRequest_ItemMall_Giftitem_Germany
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siIDNumber;	

	SI32				siProductKey ; // ��ǰ �ε���
	TCHAR				szMyAccountID[MAX_PLAYER_NAME]; // ���� ���̵�

	TCHAR				szGetAccountID[MAX_PLAYER_NAME] ; // ���� ���� ��� AccountID
	SI32				siProductNum; // ���� ����
	SI32				siProductPrice; // �ֹ� �ݾ�

	TCHAR				szComment[200] ; // ���� �޽���
	TCHAR				szIP[64];		// IP
	TCHAR				szItemName[50];

	SI16				siGetServerUnique;
	TCHAR				szGetCharName[MAX_PLAYER_NAME];
	SI32				siItemImageFont;

	sDBRequest_ItemMall_Giftitem_Germany(UI16 charid , SI32 personid , SI32 IDNumber, SI32 key,TCHAR*account,TCHAR*getaccount,
		SI32 num,SI32 price,TCHAR* comment,TCHAR*ip,TCHAR* itemname,SI16 GetServerUnique, TCHAR* GetCharName, SI32 ItemImageFont )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALL_GIFTITEM_GERMANY;
		packetHeader.usSize = sizeof( sDBRequest_ItemMall_Giftitem_Germany );

		usCharID		= charid ;
		siPersonID		= personid ;
		siIDNumber		= IDNumber;	
	
		siProductKey	= key ;
		MStrCpy(szMyAccountID,account,MAX_PLAYER_NAME) ;
		MStrCpy(szGetAccountID,getaccount,MAX_PLAYER_NAME) ;
		siProductNum	= num ;
		siProductPrice	= price ;

		MStrCpy(szComment,comment,200) ;
		MStrCpy(szIP,ip,64) ;
		MStrCpy(szItemName,itemname,50) ;

		siGetServerUnique = GetServerUnique;
		MStrCpy(szGetCharName,GetCharName,MAX_PLAYER_NAME) ;

		siItemImageFont = ItemImageFont;
	}
};

class sDBRequest_ItemMallGetItem_Germany
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siIDNumber;	

	SI16				siInvPos;		// �������� �־�� �� ��ġ.

	SI32				siItemID;		// ������ ��ȣ
	cltItem				clItem;			// Person�� ���� ������.

	bool				bPossession;	// ������ ���ִ� �ų� �ƴϳ�
	bool				bCreateSID;		// SID ���� ����

	sDBRequest_ItemMallGetItem_Germany( UI16 charid, SI32 personid, SI16 pos,SI32 itemid,cltItem *pclitem,bool possession,bool createsid )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_ITEMMALLGETITEM_GERMANY;
		packetHeader.usSize = sizeof( sDBRequest_ItemMallGetItem_Germany );

		usCharID		= charid;
		siPersonID		= personid;
		siInvPos		= pos;

		siItemID		= itemid;		
		clItem.Set(pclitem);

		bPossession		= possession ;
		bCreateSID		= createsid;
	}
};
//***************************************************************************************************
//
// Class Name 		: sDBRequest_Warp_TargetWorld
//
// Last Modified 	: 2009 / 11 / 18
// Created		 	: �ռ�
//
// Function			: Ÿ�� Ƽ���� �̿��ؼ� �ش� �������� �̵� �Ѵ� 
//
//***************************************************************************************************
class sDBRequest_Warp_TargetWorld
{
public:
	sPacketHeader		packetHeader;
	
	UI16				usCharID;
	SI32				siPersonID;

	SI16				siInvPos;		// �������� �ִ� �κ��丮
	cltItem				clItem;			// ���������� ������ ����


	sDBRequest_Warp_TargetWorld(UI16 charid, SI32 personid, SI16 pos,cltItem *pclitem )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_WARP_TARGETWORLD;
		packetHeader.usSize = sizeof( sDBRequest_NoLimitTicket_Warp );

		usCharID		= charid ;
		siPersonID		= personid ;
		siInvPos		= pos ;
		clItem.Set(pclitem);
	}
};
class sDBResponse_TargetWorld
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	SI32				siResult ;		// 1�ܿ��� ����

	SI16				siInvPos;		// �������� �ִ� �κ��丮
	cltItem				clItem;			// ���������� ������ ����


	sDBResponse_TargetWorld()
	{
		ZeroMemory(this, sizeof(sDBResponse_TargetWorld));
	}	
};

#endif
