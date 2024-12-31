#ifndef _DBMSGSYSTEM_H
#define _DBMSGSYSTEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

#include "..\..\GoonZuWorld\Common\PrivateTradeOrderMgr\PrivateTradeOrderBaseInfo.h"
#include "..\..\GoonZuWorld\CommonLogic\MsgType.h"
#include "..\..\GoonZuWorld\Server\Minister\MinisterBase.h"
#include "..\..\GoonZuWorld\CommonLogic\PostOffice\PostOffice.h"

#include "..\..\GoonZuWorld\Server\Server.h"
#include "..\..\GoonZuWorld\Server\Minister\Minister-Yezo.h"
#include "..\..\GoonZuWorld\Server\Minister\Minister-Hozo.h"
#include "../../Server/Minister/Minister-Hyungzo.h"
#include "..\..\GoonZuWorld\CommonLogic\WarRank\WarRank.h"
#include "../../common/systemnpc/RPMerchantNPC/RPMerchantNPC.h"
#include "../../Server/ServerEvent/ServerEvent_Manager.h"
#include "../../Server/ServerEvent/ServerEvent-Quest.h"

//-----------------------------------------
// ���� WARP ��û. 
//-----------------------------------------
class sDBRequest_WarpVillage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siItemPos;
	SI16				siItemUnique;
	SI16				siFromVillageUnique;
	SI16				siToVillageUnique;

	sDBRequest_WarpVillage()
	{
		ZeroMemory(this, sizeof(sDBRequest_WarpVillage));
	}

	sDBRequest_WarpVillage(UI16 charid, SI32 personid, SI16 itempos, SI16 itemunique, SI16 fromvillage, SI16 tovillage)
	{
		packetHeader.usCmd = DBMSG_REQUEST_WARPVILLAGE;
		packetHeader.usSize = sizeof(sDBRequest_WarpVillage);

		usCharID		= charid;
		siPersonID		= personid;
		siItemPos		= itempos;
		siItemUnique	= itemunique;
		siFromVillageUnique	= fromvillage;
		siToVillageUnique	= tovillage;
	}
};


class sDBResponse_WarpVillage
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;
	SI16				siItemPos;
	cltItem				clItem;
	SI16				siFromVillageUnique;
	SI16				siToVillageUnique;


	sDBResponse_WarpVillage()
	{
		ZeroMemory(this, sizeof(sDBResponse_WarpVillage));
	}
};

//-----------------------------------------
// ���� Ÿ�� ���� ��û. 
//-----------------------------------------
class sDBRequest_MapTypeInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_MapTypeInfo()
	{
		packetHeader.usCmd = DBMSG_REQUEST_MAPTYPEINFO;
		packetHeader.usSize = sizeof(sDBRequest_MapTypeInfo);
	}
};


class sDBResponse_MapTypeInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI16				siMapTypeInfo[MAX_MAP_NUMBER];

	sDBResponse_MapTypeInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_MapTypeInfo));
	}
};

//-----------------------------------------
// ���� ���� �˸�. 
//-----------------------------------------
class sDBRequest_StartGame
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_StartGame()
	{
		packetHeader.usCmd = DBMSG_REQUEST_STARTGAME;
		packetHeader.usSize = sizeof(sDBRequest_StartGame);
	}
};


class sDBResponse_StartGame
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	sDBResponse_StartGame()
	{
		ZeroMemory(this, sizeof(sDBResponse_StartGame));
	}
};

//-----------------------------------------
// ����� ĳ���� ���� ��û 
//-----------------------------------------
class sDBRequest_UserCharInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	TCHAR				szPersonName[MAX_PLAYER_NAME];
	bool				bConnectSwitch;		// ���ӿ� ������ �ִ��� ����.

	SI32				siRequestPersonID;	// ��û�� PersonID

	// ���Ӽ������� ��û�Ȱ��� GMTOOL���� ��û�Ȱ��� �����Ѵ�.
	SI08				siRequestType;			// 0:���Ӽ���, 1:GMTOOL

	sDBRequest_UserCharInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_UserCharInfo));
	}

	sDBRequest_UserCharInfo(UI16 charid, TCHAR* szname, bool connectswitch, SI32 requestpersonid, SI08 requesttype = 0)
	{
		packetHeader.usSize = sizeof( sDBRequest_UserCharInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_USERCHARINFO;

		usCharID	= charid;

		MStrCpy( szPersonName, szname, MAX_PLAYER_NAME );
		szPersonName[MAX_PLAYER_NAME-1] = '\0';

		bConnectSwitch		= connectswitch;

		siRequestPersonID	= requestpersonid;

		siRequestType		= requesttype;
	}
};

class sDBResponse_UserCharInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	TCHAR				szAccountID[30];
	TCHAR				szPassword[30];		
	cltMoney			clTotalMoney;		// ���ڻ�. 	

	bool				bConnectSwitch;		// ���� ����. 

	SI32				siPersonID;
	SI16				siLevel;
	GMONEY				siMoney;

	SI16				siMapIndex;
	SI16				siX;
	SI16				siY;
	SI08				siGoonzuFriends;

	TCHAR				szOtherPersonName1[ MAX_PLAYER_NAME ];				
	TCHAR				szOtherPersonName2[ MAX_PLAYER_NAME ];

	cltMoney			clBankMoney;		// ����ݾ�

	cltSummonInfo		clSummonInfo;		// ��ȯ�� ����
	SI32				siVillageUnique;	// ���� ����

	TCHAR				szRecommender[MAX_PLAYER_NAME]; // ��õ��
	TCHAR				szFatherName[MAX_PLAYER_NAME]; // ����
	SI16				siStudentLevel;					// ���ڰ� �Ǿ��� ���� ����

	TCHAR				szMakeDate[24];	// ĳ���� ������

	SI64				siWorldTradeMoney;

	// ���Ӽ������� ��û�Ȱ��� GMTOOL���� ��û�Ȱ��� �����Ѵ�.
	SI08				siRequestType;			// 0:���Ӽ���, 1:GMTOOL

	cltUserBlockLog		m_clBlockLog[MAX_BLOCKLOG_NUM+1];

	sDBResponse_UserCharInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_UserCharInfo));
	}
};

//------------------------------------------------------------------------
// ���� ������ ���� ���
//------------------------------------------------------------------------
class sDBRequest_UserCharItemInfo
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	TCHAR				m_szPersonName[MAX_PLAYER_NAME];
	SI32				m_siRequestPersonID;				// ��û�� PersonID

	sDBRequest_UserCharItemInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_UserCharItemInfo));
	}

	sDBRequest_UserCharItemInfo(UI16 usCharid, TCHAR* szName, SI32 siRequestPersonID )
	{
		m_packetHeader.usSize	= sizeof( sDBRequest_UserCharItemInfo );
		m_packetHeader.usCmd	= DBMSG_REQUEST_USERCHARITEMINFO;

		m_usCharID				= usCharid;
		m_siRequestPersonID		= siRequestPersonID;

		MStrCpy( m_szPersonName, szName, MAX_PLAYER_NAME );
		m_szPersonName[MAX_PLAYER_NAME-1] = '\0';
	}
};

//==========================================================================
// �뷮������ 2���� �и��ߴ�
//==========================================================================
class sDBResponse_UserCharItemInfo
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;			// �����.
	SI32				m_siPersonID;

	// ĳ���� �κ��丮 ������
	cltItem				m_clItem[MAX_ITEM_PER_PERSON];

	sDBResponse_UserCharItemInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_UserCharItemInfo));
	}
};	// DBMSG_RESPONSE_USERCHARITEMINFO

class sDBResponse_UserCharItemInfo2
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siResult;			// �����.
	SI32				m_siPersonID;

	// �������� ������
	cltItem				m_clSpaceBox[MAX_ITEM_SPACE_BOX];
	// �������� ������
	cltItem				m_clTreasureBox[MAX_ITEM_TREASURE_BOX];

	sDBResponse_UserCharItemInfo2()
	{
		ZeroMemory(this, sizeof(sDBResponse_UserCharItemInfo2));
	}
};	// DBMSG_RESPONSE_USERCHARITEMINFO2



class sDBRequest_AccountInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	TCHAR				szAccountID[ 32 ];

	// ���Ӽ������� ��û�Ȱ��� GMTOOL���� ��û�Ȱ��� �����Ѵ�.
	SI08				siRequestType;			// 0:���Ӽ���, 1:GMTOOL

	sDBRequest_AccountInfo( UI16 id, TCHAR *accountid, SI08 requesttype = 0)
	{
		packetHeader.usSize = sizeof( sDBRequest_AccountInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_ACCOUNTINFO;

		usCharID = id;
		memcpy( szAccountID, accountid, 32 );
		szAccountID[ 31 ] = NULL;

		siRequestType = requesttype;
	}
};

class sDBResponse_AccountInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	TCHAR				szAccountID[ 32 ];

	TCHAR				szPersonName1[ MAX_PLAYER_NAME ];				
	TCHAR				szPersonName2[ MAX_PLAYER_NAME ];				
	TCHAR				szPersonName3[ MAX_PLAYER_NAME ];				

	// ���Ӽ������� ��û�Ȱ��� GMTOOL���� ��û�Ȱ��� �����Ѵ�.
	SI08				siRequestType;			// 0:���Ӽ���, 1:GMTOOL

	sDBResponse_AccountInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_AccountInfo));
	}
};


//=============================================================================
//	CLASS   sDBRequest_AccountInfoForHanXNoti
//! @brief  �������� ĳ���� ������ ��û�Ѵ� - HanXNoti ��
//=============================================================================
class sDBRequest_AccountInfoForHanXNoti
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siArrayIndex;
	SI32				m_nIdx;

	TCHAR				m_szServerID[ 50 ];
	TCHAR				m_szAccountID[ MAX_PLAYER_NAME ];

	sDBRequest_AccountInfoForHanXNoti( SI32 siArrayIndex, SI32 siIdx, TCHAR* pszServerID, TCHAR *pszAccountID)
	{
		m_packetHeader.usSize = sizeof( sDBRequest_AccountInfoForHanXNoti );
		m_packetHeader.usCmd	= DBMSG_REQUEST_ACCOUNTINFOFORHANXNOTI;

		m_siArrayIndex	= siArrayIndex;
		m_nIdx			= siIdx;

        StringCchCopy( m_szServerID, sizeof(pszServerID), m_szServerID );
		StringCchCopy( m_szAccountID, sizeof(m_szAccountID), pszAccountID );
	}
};

class sDBResponse_AccountInfoForHanXNoti
{
public:
	sPacketHeader		packetHeader;
	SI32				m_siArrayIndex;
	SI32				m_nIdx;

	SI32				siResult;

	TCHAR				szServerID[ 50 ];
	TCHAR				szAccountID[ 32 ];

	TCHAR				szPersonName1[ MAX_PLAYER_NAME ];
	TCHAR				szPersonName2[ MAX_PLAYER_NAME ];
	TCHAR				szPersonName3[ MAX_PLAYER_NAME ];

	sDBResponse_AccountInfoForHanXNoti()
	{
		ZeroMemory(this, sizeof(sDBResponse_AccountInfoForHanXNoti));
	}
};


//=============================================================================
//	CLASS   sDBRequest_AccountInfoForHanXNoti
//! @brief  ĳ���� ������ ��û�Ѵ� - HanXNoti ��
//=============================================================================
class sDBRequest_CharInfoForHanXNoti
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siArrayIndex;
	SI32				m_nIdx;

	TCHAR				m_szServerID[ 50 ];
	TCHAR				m_szCharName[ MAX_PLAYER_NAME ];

	sDBRequest_CharInfoForHanXNoti( SI32 siArrayIndex, SI32 siIdx, TCHAR* pszServerID, TCHAR *pszCharName)
	{
		m_packetHeader.usSize = sizeof( sDBRequest_AccountInfoForHanXNoti );
		m_packetHeader.usCmd	= DBMSG_REQUEST_CHARINFOFORHANXNOTI;

		m_siArrayIndex	= siArrayIndex;
		m_nIdx			= siIdx;

		StringCchCopy( m_szServerID, sizeof(m_szServerID), pszServerID );
		StringCchCopy( m_szCharName, sizeof(m_szCharName), pszCharName );
	}
};

class sDBResponse_CharInfoForHanXNoti
{
public:
	sPacketHeader		packetHeader;
	SI32				m_siArrayIndex;
	SI32				m_nIdx;

	SI32				siResult;

	TCHAR				m_szServerID[ 50 ];
	TCHAR				m_szAccountID[ MAX_PLAYER_NAME ];
	TCHAR				m_szCharName[ MAX_PLAYER_NAME ];				

	SI32				siPersonID;
	SI16				siLevel;

	TCHAR				szOtherPersonName1[ MAX_PLAYER_NAME ];				
	TCHAR				szOtherPersonName2[ MAX_PLAYER_NAME ];


	sDBResponse_CharInfoForHanXNoti()
	{
		ZeroMemory(this, sizeof(sDBResponse_CharInfoForHanXNoti));
	}
};

//-----------------------------------------
// ���� �ŷ�
//-----------------------------------------
class sDBRequest_PrivateTrade
{
public:
	sPacketHeader		packetHeader;

	//A ����� ����
	SI32				siPersonID1;		// A ��������� �˸�
	UI16				usCharID1;			// A ������� CharUnique ��
	GMONEY				siMoney1;
	cltItem				clItem1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				siItemOriPos1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				siItemPos1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];	// ���� �κ����� ��ġ.
	bool				bPileSwitch1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];	// ������ �������� �ƴ���.. ( CanPile )

	SI32				siStockVillageUnique1;
	SI32				siStockNum1;

	SI32				siHouseVillageUnique1;
	SI32				siHouseUnitSlot1;
	cltRentContract		clRentContract1;

	//bool				bHorse1;
	SI16				siHorse1;			// ���� ��ġ - �ŷ��� �����ô� -1
	SI16				siRecvHorse1;		// ���� �� ��ġ ( 2������ ���� ��� ) - �ŷ��� �����ô� -1

	//B ����� ����
	SI32				siPersonID2;
	UI16				usCharID2;
	GMONEY				siMoney2;
	cltItem				clItem2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				siItemOriPos2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				siItemPos2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];	// A ������� �κ����� ��ġ.
	bool				bPileSwitch2[ MAX_PRIVATETRADEORDER_ITEM_NUM ]; // ������ �������� �ƴ���.. ( CanPile )

	SI32				siStockVillageUnique2;
	SI32				siStockNum2;

	SI32				siHouseVillageUnique2;
	SI32				siHouseUnitSlot2;
	cltRentContract		clRentContract2;

	//bool				bHorse2;
	SI16				siHorse2;			// �ŷ��� ���� ��ġ - �ŷ��� �����ô� -1
	SI16				siRecvHorse2;		// ���� �� ��ġ ( 1������ ���� ��� ) - �ŷ��� �����ô� -1

	sDBRequest_PrivateTrade()
	{
		ZeroMemory(this, sizeof(sDBRequest_PrivateTrade));
		siHorse1 = -1;
		siHorse2 = -1;
	}

	sDBRequest_PrivateTrade
		( 
		SI32 PersonID1, UI16 CharID1, GMONEY Money1, cltItem *pclItemList1, SI16 *ItemOriPos1, SI16 *ItemListPos1, bool *PileSwitchList1, SI32 StockVillageUnique1, SI32 StockNum1, SI32 HouseVillageUnique1, SI32 HouseUnitSlot1, SI16 Horse1, SI16 RecvHorse1,
		SI32 PersonID2, UI16 CharID2, GMONEY Money2, cltItem *pclItemList2, SI16 *ItemOriPos2, SI16 *ItemListPos2, bool *PileSwitchList2, SI32 StockVillageUnique2, SI32 StockNum2, SI32 HouseVillageUnique2, SI32 HouseUnitSlot2, SI16 Horse2, SI16 RecvHorse2
		)
	{
		packetHeader.usSize = sizeof( sDBRequest_PrivateTrade );
		packetHeader.usCmd	= DBMSG_REQUEST_PRIVATETRADE;

		siPersonID1 = PersonID1;
		usCharID1 = CharID1;
		siMoney1 = Money1;
		memcpy( clItem1, pclItemList1, sizeof( cltItem ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
		memcpy( siItemOriPos1, ItemOriPos1, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );		
		memcpy( siItemPos1, ItemListPos1, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
		memcpy( bPileSwitch1, PileSwitchList1, sizeof( bool ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

		siStockVillageUnique1 = StockVillageUnique1;
		siStockNum1 = StockNum1;

		siHouseVillageUnique1 = HouseVillageUnique1;		// ���� �ŷ�
		siHouseUnitSlot1 = HouseUnitSlot1;

		siHorse1 = Horse1;									// �� �ŷ�
		siRecvHorse1 = RecvHorse1;		

		siPersonID2 = PersonID2;
		usCharID2 = CharID2;
		siMoney2 = Money2;
		memcpy( clItem2, pclItemList2, sizeof( cltItem ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
		memcpy( siItemOriPos2, ItemOriPos2, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
		memcpy( siItemPos2, ItemListPos2, sizeof( SI16 ) * MAX_PRIVATETRADEORDER_ITEM_NUM );
		memcpy( bPileSwitch2, PileSwitchList2, sizeof( bool ) * MAX_PRIVATETRADEORDER_ITEM_NUM );

		siStockVillageUnique2 = StockVillageUnique2;
		siStockNum2 = StockNum2;

		siHouseVillageUnique2 = HouseVillageUnique2;		// ���� �ŷ�
		siHouseUnitSlot2 = HouseUnitSlot2;

		siHorse2 = Horse2;									// �� �ŷ�
		siRecvHorse2 = RecvHorse2;
	}
};

class sDBResponse_PrivateTrade
{
public:
	sPacketHeader		packetHeader;
	SI32				siResult;			// �����.

	SI32				siPersonID1;
	UI16				usCharID1;

	SI32				siPersonID2;
	UI16				usCharID2;

	// FOR LOG - ������ ����
	cltItem				LOG_clItem1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				LOG_siItemOriPos1[ MAX_PRIVATETRADEORDER_ITEM_NUM ]; // A ������� �κ����� ��ġ.
	SI16				LOG_siItemPos1[ MAX_PRIVATETRADEORDER_ITEM_NUM ];	 // B ������� �κ����� ��ġ.

	//B ����� ����
	cltItem				LOG_clItem2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];
	SI16				LOG_siItemOriPos2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];// B ������� �κ����� ��ġ.
	SI16				LOG_siItemPos2[ MAX_PRIVATETRADEORDER_ITEM_NUM ];	// A ������� �κ����� ��ġ.

	SI32				siSendStockVillageUnique1;
	SI32				siSendStockNum1;

	SI32				siRecvStockVillageUnique1;
	SI32				siRecvStockNum1;		   // �ŷ��� �ֽĿ� ���� 1�� ������ �ִ� �� ����
	SI32				siRecvedStockNumToSender1; // 2���� ����  �ֽļ�

	SI32				siSendStockVillageUnique2;
	SI32				siSendStockNum2;

	SI32				siRecvStockVillageUnique2;
	SI32				siRecvStockNum2;		   // �ŷ��� �ֽĿ� ���� 2�� ������ �ִ� �� ����
	SI32				siRecvedStockNumToSender2; // 1���� ����  �ֽļ�

	SI32				siSendHouseVillageUnique1;
	SI32				siSendHouseUnitSlot1;

	SI32				siRecvHouseVillageUnique1;
	SI32				siRecvHouseUnitSlot1;
	TCHAR				Person1Name[ MAX_PLAYER_NAME ];		// ������ �̸��� �ٲ��� �ϹǷ�..

	SI32				siSendHouseVillageUnique2;
	SI32				siSendHouseUnitSlot2;

	SI32				siRecvHouseVillageUnique2;
	SI32				siRecvHouseUnitSlot2;
	TCHAR				Person2Name[ MAX_PLAYER_NAME ];		// ������ �̸��� �ٲ��� �ϹǷ�..

	cltHorse			clRecvHorse1;
	cltHorse			clRecvHorse2;

	SI16				siHorse1;					// �ŷ��� ������ -1
	SI16				siHorse2;					// �ŷ��� ������ -1

	SI16				siRecvHorse1;				// 1�� ����ڰ� ���� ������ ���� ��ġ( �ŷ� ������ -1 )
	SI16				siRecvHorse2;				// 2�� ����ڰ� ���� ������ ���� ��ġ( �ŷ� ������ -1 )


	//bool				bHorse1;
	//bool				bHorse2;

	sDBResponse_PrivateTrade()
	{
		ZeroMemory(this, sizeof(sDBResponse_PrivateTrade));
	}
};

//-----------------------------------------
// Ư�� ������� ������ ����/����Ѵ�.
//-----------------------------------------

class sDBRequest_BlockUser
{
public:
	enum {

		BLOCK_UNTIL_DAYS = 1,
		BLOCK_FOREVER = 2,
		WARNING_TO_BLOCKING = 3
	};

	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siBlockMode;							// 0 :�� ����. 1:�Ϲݺ�, 2:������, 3:���
	TCHAR				szPersonName[MAX_PLAYER_NAME];
	SI32				siDay;									// �� �Ⱓ(��) 
	TCHAR				szBlockReason[MAX_BLOCKREASON_SIZE];	// �� ����.

	sDBRequest_BlockUser()
	{
		ZeroMemory(this, sizeof(sDBRequest_BlockUser));
	}

	sDBRequest_BlockUser(UI16 charid, SI32 blockmode, TCHAR* pname, SI32 day, TCHAR* preason)
	{
		packetHeader.usSize = sizeof( sDBRequest_BlockUser );
		packetHeader.usCmd	= DBMSG_REQUEST_BLOCKUSER;

		usCharID	= charid;
		siBlockMode	= blockmode;

		MStrCpy( szPersonName, pname, MAX_PLAYER_NAME );
		siDay	= day;
		MStrCpy( szBlockReason, preason, MAX_BLOCKREASON_SIZE );
	}
};


class sDBResponse_BlockUser
{
public:
	enum {

		WARNING_EMPTY = 0,
		WARNING_FIRST = 1,
		BLOCK_FOR_5_DAYS = 2,
		BLOCK_FOR_10_DAYS = 3,
		BLOCK_FOR_FOREVER = 4,
	};

	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siBlockMode;		// 0 : ����, 1: ���. 
	UI08				siWarnMode;			// 0 : �����, 1:ù���, 2:5�ϰ� block, 3:10�ϰ� block, 4:������ block
	TCHAR				szPersonName[MAX_PLAYER_NAME];
	SI32				siPersonID;			// ������� PersonID
	SI32				siYear, siMonth, siDay, siHour, siMin;	// �� �Ⱓ(��) 
	TCHAR				szBlockReason[MAX_BLOCKREASON_SIZE];	// �� ����.

	sDBResponse_BlockUser()
	{
		ZeroMemory(this, sizeof(sDBResponse_BlockUser));
	}
};

//-----------------------------------------
// ������� �α����� ����/����Ѵ�.
//-----------------------------------------
class sDBRequest_Block
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siBlockMode;		// 0 : ����, 1: ���. 

	sDBRequest_Block()
	{
		ZeroMemory(this, sizeof(sDBRequest_Block));
	}

	sDBRequest_Block(UI16 charid, SI32 blockmode)
	{
		packetHeader.usSize = sizeof( sDBRequest_Block );
		packetHeader.usCmd	= DBMSG_REQUEST_BLOCK;

		usCharID	= charid;
		siBlockMode	= blockmode;
	}
};

class sDBResponse_Block
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.

	SI32				siBlockMode;		// 0 : ����, 1: ���. 

	sDBResponse_Block()
	{
		ZeroMemory(this, sizeof(sDBResponse_Block));
	}
};


//-----------------------------------------
// ����� ���ڸ� �����Ѵ�. 
//-----------------------------------------
class sDBRequest_SetUserNum
{
public:
	sPacketHeader		packetHeader;

	SI32				siUserNum;
	SI32				siSBSUserNum;

	//KHY - 0708 - �Ϻ� ����͸� Ŭ���̾�Ʈ ����.
	SI32				siHangameUserNum;
	SI32				siGamaniaUserNum;
	SI32				siGamePotUserNum;
	SI32				siNDEUserNum;
	SI32				siNEXONUserNum;

	//SI32				siNetmarbleUserNum;

	sDBRequest_SetUserNum()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetUserNum));
	}

	sDBRequest_SetUserNum(SI32 usernum, SI32 sbsusernum,  SI32 hangameusernum , SI32 GamaniaUserNum, SI32 gamepotusernum, SI32 NDEUserNum ,SI32 NEXONUserNum)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetUserNum );
		packetHeader.usCmd	= DBMSG_REQUEST_SETUSERNUM;

		siUserNum			= usernum;
		siSBSUserNum		= sbsusernum;

		siHangameUserNum	= hangameusernum;
		siGamaniaUserNum	= GamaniaUserNum;
		siGamePotUserNum	= gamepotusernum;
		siNDEUserNum	= NDEUserNum;
		siNEXONUserNum = NEXONUserNum;

		//siNetmarbleUserNum	= netmarbleusernum;

	}
};


//-----------------------------------------
// �ð��� �����ϵ��� �Ѵ�. 
//-----------------------------------------
class sDBRequest_SetTime
{
public:
	sPacketHeader		packetHeader;

	DWORD				dwSetTimeClock;
	SI32				siYesr;
	SI32				siMonth;
	SI32				siDay;
	SI32				siHour;
	SI32				siMinute;

	sDBRequest_SetTime()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetTime));
	}

	sDBRequest_SetTime(DWORD dwsettimeclock, SI32 year, SI32 month, SI32 day, SI32 hour, SI32 minute)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetTime );
		packetHeader.usCmd	= DBMSG_REQUEST_SETTIME;

		dwSetTimeClock	= dwsettimeclock;
		siYesr		= year;
		siMonth		= month;
		siDay		= day;
		siHour		= hour;
		siMinute	= minute;
	}
};

class sDBResponse_SetTime
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	DWORD				dwSetTimeClock;

	sDBResponse_SetTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetTime));
	}
};


//-----------------------------------------
// �ð��� �������� �Ѵ�. 
//-----------------------------------------
class sDBRequest_GetTime
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetTime()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetTime));
		packetHeader.usSize = sizeof( sDBRequest_GetTime );
		packetHeader.usCmd	= DBMSG_REQUEST_GETTIME;

	}
};

class sDBResponse_GetTime
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	SI32				siYear;
	SI32				siMonth;
	SI32				siDay;
	SI32				siHour;
	SI32				siMinute;

	sDBResponse_GetTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetTime));
	}
};

class sDBRequest_Ping
{
public:
	sPacketHeader		packetHeader;

	SI32				siSelect;
	DWORD				dwTick;

	sDBRequest_Ping( SI32 select, DWORD tick ) 
	{
		packetHeader.usCmd = DBMSG_REQUEST_PING;
		packetHeader.usSize = sizeof( sDBRequest_Ping );

		siSelect = select;
		dwTick = tick;
	}
};

class sDBResponse_Ping
{
public:
	sPacketHeader		packetHeader;

	SI32				siSelect;
	DWORD				dwTick;

	sDBResponse_Ping()
	{
		ZeroMemory(this, sizeof(sDBResponse_Ping));
	}
};


//-----------------------------------------
// �����Ǽ� ���� ������ 
//-----------------------------------------
class sDBRequest_GetByungzoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetByungzoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETBYUNGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetByungzoInfo );
	}
};

class sDBResponse_GetByungzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	SI32				siPersonID;

	CMinisterBase		MinisterBase;

	SI32				siSetTime;				// ���Ｓ���ð�
	SI32				siWarStartTime;			// ������۽ð�
	SI16				siSetWarCount;			// ���Ｓ�� Ƚ��
	SI32				siBlackArmyNum;			// ���� ���� ���� ��

	SI32				siVillageWarTime;	// ����ð� 

	sDBResponse_GetByungzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetByungzoInfo));
	}
};

class sDBRequest_GetYezoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetYezoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETYEZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetYezoInfo );
	}
};
class sDBResponse_GetYezoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;
	SI32				siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32				siJapanGunSolNum;	// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32				siJapanCommanderNum;// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32				siJapanPorterNum;	// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32				siWarVillageUnique; // ���ۿֱ��� �ĵ� ���� ����ũ

	sDBResponse_GetYezoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetYezoInfo));
	}
};

class sDBRequest_GetHozoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetHozoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETHOZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetHozoInfo );
	}
};

class sDBResponse_GetHozoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;
	SI32				siResidentNum;		// �ֹμ� 
	SI32				siMaxShop;

	SI32				siTotalCharNum;		// �� �鼺��(ĳ���ͼ�)
	SI32				siCalcTime;			// �� �鼺�� ����� �ð� - ����Ÿ��

	GMONEY				siPrizeMoney;		// ��õ�ο��� ������ �ݾ�
	SI32				siPrizeSetTime;		// �ݾ� ���� �ð�
	GMONEY				siFixationMoney;
	
	SI16				siBankruptcyVillageNumber; // �Ļ�� ���� ����
	SI32				siSetBankruptcyVillageDate; // �Ļ�� ���� ���� ������ �ð�
	GMONEY				siTutorialVillageDivideend;	// ��ī�� �ֽ� ����

	sDBResponse_GetHozoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetHozoInfo));
	}
};

class sDBRequest_GetGoonzuInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetGoonzuInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETGOONZUINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetGoonzuInfo );
	}
};

class sDBResponse_GetGoonzuInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;

	INT64				iTotalFinances; // ���� �� ����

	SI32				siSetMinisterTime[6]; // �Ǽ��� ���� �Ӹ�� �ð�

	SI16				siLiquidationVillageNumber;
	
	SI16				siBonusTime;
	SI16				siMakeBonusTime;


	SI16				siLastChangedBonusTimeYear;
	SI16				siLastChangedBonusTimeMonth;
	SI16				siLastChangedBonusTimeDay;


	sDBResponse_GetGoonzuInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetGoonzuInfo));
	}
};

class sDBRequest_GetIzoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetIzoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETIZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetIzoInfo );
	}
};

class sDBResponse_GetIzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;
	SI32				siPriceValue;
	SI32				siPriceTime;
	GMONEY				siTotalMoney;
	SI32				siCalcTime;
	SI32				siTradeTax;
	GMONEY				siTradeLimitMoney;

	bool				bWorldTradeTax;			// ����_���� ���� ����
	SI32				siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32				siSpecialTaxRate;		// ����_Ư������( 10% ~ 100% )
	SI32				siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI16				siTinTin;				// ƾƾ �߰� ������

		sDBResponse_GetIzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetIzoInfo));
	}
};

class sDBRequest_GetGongzoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetGongzoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETGONGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetGongzoInfo );
	}
};

class sDBResponse_GetGongzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;

	SI32				siPriceTime;
	SI16				siLeftOverValue;
	SI16				siPriceValue[GONGZO_SKILL_TOTAL];
	SI16				siLeftOverValue_Armor;

	GMONEY				siCraftFund;

	sDBResponse_GetGongzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetGongzoInfo));
	}
};

class sDBRequest_GetHyungzoInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetHyungzoInfo() 
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETHYUNGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_GetHyungzoInfo );
	}
};

class sDBResponse_GetHyungzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	CMinisterBase		MinisterBase;

	SI16				siLimitStealNum;
	SI16				siSuspectTime;
	SI16				siPrisonTime;
	SI16				siPrisonerPenalty;

	//	SI32				siDate[MAX_PRISON_LIST_NUM];
	//	TCHAR				szCharName[MAX_PRISON_LIST_NUM][MAX_PLAYER_NAME];
	//	TCHAR				szPrisonReason[MAX_PRISON_LIST_NUM][MAX_PRISON_REASON_SIZE];
	HyungzoMember		stHyungzoMember[MAX_PRISON_LIST_NUM];

	sDBResponse_GetHyungzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetHyungzoInfo));
	}
};

//-----------------------------------------
// �����Ǽ� ���� �����ϱ�
//-----------------------------------------
class sDBRequest_SetByungzoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];

	SI32				siSetTime;				// ���Ｓ���ð�
	SI32				siWarStartTime;			// ������۽ð�
	SI16				siSetWarCount;			// ���Ｓ�� Ƚ��
	SI32				siBlackArmyNum;			// ���� ���� ���� ��

	SI32				siVillageWarTime;	// ����ð� 

	sDBRequest_SetByungzoInfo(UI16 charid, SI32 personid, TCHAR *greeting, SI32 villagewartime, SI32 settime,
		SI32 warstarttime, SI16 setwarcount, UI32 blackarmynum)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETBYUNGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetByungzoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);

		siSetTime = settime;
		siWarStartTime = warstarttime;
		siSetWarCount = setwarcount;
		siBlackArmyNum = blackarmynum;

		siVillageWarTime = villagewartime;

	}

};

class sDBResponse_SetByungzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;

	SI32				siSetTime;				// ���Ｓ���ð�
	SI32				siWarStartTime;			// ������۽ð�
	SI16				siSetWarCount;			// ���Ｓ�� Ƚ��
	SI32				siBlackArmyNum;			// ���� ���� ���� ��

	SI32				siVillageWarTime;	// ����ð� 
	sDBResponse_SetByungzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetByungzoInfo));
	}
};

class sDBRequest_SetByungzoInfo_VillageWarTime
{
public:

	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;	
	
	TCHAR				m_szGreeting[256];					// �λ縻 
	SI32				siVillageWarTime;	// ����ð� 

	sDBRequest_SetByungzoInfo_VillageWarTime(UI16 charid, SI32 personid, TCHAR * greetingMsg , SI32 villagewartime )
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETBYUNGZOINFO_VILLAGEWARTIME;
		packetHeader.usSize = sizeof( sDBRequest_SetByungzoInfo_VillageWarTime );

		usCharID		= charid;
		siPersonID		= personid;
		StringCchCopy(m_szGreeting, 256,greetingMsg);
		siVillageWarTime = villagewartime;
	}
};

class sDBResponse_SetByungzoInfo_VillageWarTime
{
	public:

	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;
	
	TCHAR				m_szGreeting[256];

	SI32				siVillageWarTime;	// ����ð� 
	sDBResponse_SetByungzoInfo_VillageWarTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetByungzoInfo_VillageWarTime));
	}
};

class sDBRequest_SetYezoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;

	TCHAR				szGreeting[256];
	SI32				siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32				siJapanGunSolNum;	// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32				siJapanCommanderNum;// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32				siJapanPorterNum;	// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32				siWarVillageUnique; // ���ۿֱ��� �ĵ� ���� ����ũ

	sDBRequest_SetYezoInfo(UI16 charid, SI32 personid, TCHAR *greeting, SI32 jswordnum, SI32 jgunnum, SI32 jcommandernum,SI32 jporternum,SI32 villageunique)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETYEZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetYezoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);
		siJapanSwordSolNum	= jswordnum;
		siJapanGunSolNum	= jgunnum;
		siJapanCommanderNum	= jcommandernum;
		siJapanPorterNum	= jporternum;

		siWarVillageUnique	= villageunique ;
	}
};

class sDBResponse_SetYezoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;
	SI32				siJapanSwordSolNum;	// �̵��ֱ� ���� ��	KIND_JAPANSWORDSOL
	SI32				siJapanGunSolNum;	// ���ѿֱ� ���� ��	KIND_JAPANGUNSOL
	SI32				siJapanCommanderNum;// �ֱ���� ���� �� KIND_JAPANCOMMANDER
	SI32				siJapanPorterNum;	// ���ۿֱ� ���� �� KIND_JAPANPORTERSOL

	SI32				siWarVillageUnique; // ���ۿֱ��� �ĵ� ���� ����ũ

	sDBResponse_SetYezoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetYezoInfo));
	}
};

class sDBRequest_SetHozoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];

	SI32				siResidentNum;		// �ֹμ� 
	SI32				siMaxShop;

	GMONEY				siPrizeMoney;		// ��õ�ο��� ������ �ݾ�
	SI32				siPrizeSetTime;		// �ݾ� ���� �ð�
	GMONEY				siFixationMoney;
	GMONEY				siTutorialVillageDivideend;	// ��ī�� �ֽ� ����

	sDBRequest_SetHozoInfo(UI16 charid, SI32 personid, TCHAR *greeting, SI32 residentnum,SI32 maxshop,
		GMONEY prizemoney,SI32 prizesettime,GMONEY fixationmoney,
		GMONEY TutorialVillageDivideend)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETHOZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetHozoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);

		siResidentNum	= residentnum;
		siMaxShop = maxshop ;

		siPrizeMoney = prizemoney ;
		siPrizeSetTime = prizesettime ;
		siFixationMoney = fixationmoney ;
		siTutorialVillageDivideend = TutorialVillageDivideend;
	}
};

class sDBResponse_SetHozoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;
	SI32				siResidentNum;		// �ֹμ� 
	SI32				siMaxShop;

	GMONEY				siPrizeMoney;		// ��õ�ο��� ������ �ݾ�
	SI32				siPrizeSetTime;		// �ݾ� ���� �ð�
	GMONEY				siFixationMoney;
	GMONEY				siTutorialVillageDivideend;	// ��ī�� �ֽ� ����

	sDBResponse_SetHozoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetHozoInfo));
	}
};

class sDBRequest_SetGoonzuInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];

	sDBRequest_SetGoonzuInfo(UI16 charid, SI32 personid, TCHAR *greeting)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETGOONZUINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetGoonzuInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);
	}
};

class sDBResponse_SetGoonzuInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;

	sDBResponse_SetGoonzuInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetGoonzuInfo));
	}
};

class sDBRequest_SetGoonzuFinances
{
public:
	sPacketHeader		packetHeader;

	INT64				iTempFinances;

	sDBRequest_SetGoonzuFinances(INT64 finances)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETGOONZUFINANCES;
		packetHeader.usSize = sizeof( sDBRequest_SetGoonzuFinances );

		iTempFinances = finances ;
	}
};

class sDBResponse_SetGoonzuFinances
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	sDBResponse_SetGoonzuFinances()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetGoonzuFinances));
	}
};

class sDBRequest_SetIzoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];
	SI32				siPriceValue;		// ������ 
	SI32				siPriceTime;

	bool				bWorldTradeTax;			// ����_���� ���� ����
	SI32				siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32				siSpecialTaxRate;		// ����_Ư������( 10% ~ 100% )
	SI32				siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI16				siTinTin;				// ƾƾ �߰� ������

	sDBRequest_SetIzoInfo(UI16 charid, SI32 personid, TCHAR *greeting, SI32 pricevalue,SI32 pricetime,
		bool worldtradetax, SI32 specialtaxrange, SI32 specialtaxrate, SI32 marketdownrate, SI16 tintin)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETIZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetIzoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);

		siPriceValue	= pricevalue;
		siPriceTime		= pricetime;

		bWorldTradeTax	= worldtradetax;
		siSpecialTaxRange	= specialtaxrange;
		siSpecialTaxRate	= specialtaxrate;
		siMarketDownRate	= marketdownrate;
		siTinTin			= tintin;
	}
};

class sDBResponse_SetIzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;
	SI32				siPriceValue;		// ������ 
	SI32				siPriceTime;
	SI32				siTradeTax;
	GMONEY				siTradeLimitMoney;

	bool				bWorldTradeTax;			// ����_���� ���� ����
	SI32				siSpecialTaxRange;		// ����_Ư���� �������( 100% ~ 150% )
	SI32				siSpecialTaxRate;		// ����_Ư������( 10% ~ 100% )
	SI32				siMarketDownRate;		//  ���� �ڵ����� �ý��� ������ ( 3% ~ 15% )
	SI16				siTinTin;				// ƾƾ �߰� ������

	sDBResponse_SetIzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetIzoInfo));
	}
};

class sDBRequest_SetGongzoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];

	SI32				siPriceTime;
	SI16				siLeftOverValue;
	SI16				siPriceValue[GONGZO_SKILL_TOTAL];
	SI16				siLeftOverValue_Armor;

	GMONEY				siCraftFund;

	sDBRequest_SetGongzoInfo(UI16 charid, SI32 personid, TCHAR *greeting, SI32 pricetime,SI16 leftovervalue,SI16 *pircevalue, GMONEY craftfund, SI16 leftovervalue_armor)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETGONGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetGongzoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);
		siPriceTime		= pricetime ;
		siLeftOverValue = leftovervalue ;
		siLeftOverValue_Armor = leftovervalue_armor;
		for ( int i = 0 ; i < GONGZO_SKILL_TOTAL ; i ++ )
		{
			siPriceValue[i] = pircevalue[i];
		}

		siCraftFund = craftfund;

	}
};

class sDBResponse_SetGongzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;

	SI32				siPriceTime;
	SI16				siLeftOverValue;
	SI16				siPriceValue[GONGZO_SKILL_TOTAL];
	SI16				siLeftOverValue_Armor;

	GMONEY				siCraftFund;

	sDBResponse_SetGongzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetGongzoInfo));
	}
};

class sDBRequest_SetHyungzoInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	TCHAR				szGreeting[256];

	SI16				siLimitStealNum;
	SI16				siSuspectTime;
	SI16				siPrisonTime;
	SI16				siPrisonerPenalty;

	sDBRequest_SetHyungzoInfo(UI16 charid, SI32 personid, TCHAR *greeting,
		SI16 limitstealnum,SI16 suspecttime,SI16 prisontime,SI16 prisonerpenalty)
	{
		packetHeader.usCmd  = DBMSG_REQUEST_SETHYUNGZOINFO;
		packetHeader.usSize = sizeof( sDBRequest_SetHyungzoInfo );

		usCharID		= charid;
		siPersonID		= personid;

		MStrCpy( szGreeting, greeting, 256);

		siLimitStealNum		= limitstealnum ;
		siSuspectTime		= suspecttime ;
		siPrisonTime		= prisontime ;
		siPrisonerPenalty	= prisonerpenalty;
	}
};

class sDBResponse_SetHyungzoInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;

	CMinisterBase		MinisterBase;

	SI16				siLimitStealNum;
	SI16				siSuspectTime;
	SI16				siPrisonTime;
	SI16				siPrisonerPenalty;

	sDBResponse_SetHyungzoInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetHyungzoInfo));
	}
};

class sDBRequest_MasterGiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				minLevelRange;
	SI32				maxLevelRange;

	cltItem				clItem;													// Item
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽���

	sDBRequest_MasterGiveItem( UI16 id, SI32 minlevel, SI32 maxlevel, cltItem *pclItem, TCHAR *msg )
	{
		packetHeader.usCmd = DBMSG_REQUEST_MASTERGIVEITEM;
		packetHeader.usSize = sizeof( sDBRequest_MasterGiveItem );
		usCharID = id;

		minLevelRange = minlevel;
		maxLevelRange = maxlevel;

		clItem.Set( pclItem );

		memcpy( szMsg, msg, MAX_POSTOFFICE_MSG_SIZE );
		szMsg[ MAX_POSTOFFICE_MSG_SIZE - 1 ] = NULL;
	}

};

class sDBResponse_MasterGiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	cltItem				clItem;
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽���

	UI16				usCount;
	SI32				siPersonID[ 1000 ];

	sDBResponse_MasterGiveItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_MasterGiveItem ) );
	}

};

class sDBRequest_GiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				minLevelRange;
	SI32				maxLevelRange;

	cltItem				clItem;													// Item
	TCHAR				szMsg[ MAX_POSTOFFICE_MSG_SIZE ];						// �޽���

	cltDate				clDate;

	bool				bCreateSID;

	sDBRequest_GiveItem( UI16 id, SI32 minlevel, SI32 maxlevel, cltItem *pclItem, TCHAR *msg, cltDate *pclDate, bool createsid)
	{
		packetHeader.usCmd = DBMSG_REQUEST_MASTERGIVEITEM;
		packetHeader.usSize = sizeof( sDBRequest_MasterGiveItem );
		usCharID = id;

		minLevelRange = minlevel;
		maxLevelRange = maxlevel;

		clItem.Set( pclItem );

		if( msg ) {
			memcpy( szMsg, msg, MAX_POSTOFFICE_MSG_SIZE );
			szMsg[ MAX_POSTOFFICE_MSG_SIZE - 1 ] = NULL;
		} else {
			szMsg[ 0 ] = NULL;
		}

		clDate.Set( pclDate );

		createsid = bCreateSID;
	}

};

class sDBResponse_GiveItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	SI32				siSendNumber;

	// PCK : �α׿� ��Ŷ �߰�
	SI32				minLevelRange;
	SI32				maxLevelRange;

	cltItem				clItem;	

	cltDate				clDate;

	TCHAR				szMsg[MAX_POSTOFFICE_MSG_SIZE];

	sDBResponse_GiveItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_GiveItem ) );
	}

};

#define DBSYSTEMINFO_TODAY_NEWUSERNUM			1		// ���� �ű԰����� ���� 
#define DBSYSTEMINFO_CALCULATE_WEALTHRANK		2		// �������� ����ϵ��� ����Ѵ�.
#define DBSYSTEMINFO_CALCULATE_TOTALMONEY		3		// �� ��ȭ���� ����ϵ��� ����Ѵ�.
#define DBSYSTEMINFO_CALCULATE_TOTALCHARNUM		4		// �� �鼺��(ĳ���ͼ�)�� ����ϵ��� ����Ѵ�.
#define DBSYSTEMINFO_GET_TOTALMONEY				5		// �� ��ȭ���� �����´�.
#define DBSYSTEMINFO_CHANGEGRADE				6		// ���� 12�� ����� ���� ��Ų��.
#define DBSYSTEMINFO_GET_TOTALMONEY_YESTERDAY	7		// ������ �� ��ȭ���� �����´�

class sDBRequest_DBSystemInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siType;		// DB SYSTEM INFO TYPE
	SYSTEMTIME			stTime;		// �� ��Ŷ�� ���� �ð�.

	sDBRequest_DBSystemInfo( UI16 charid, SI32 personid, SI32 type, SYSTEMTIME Time  )
	{

		packetHeader.usCmd  = DBMSG_REQUEST_DBSYSTEMINFO;
		packetHeader.usSize = sizeof( sDBRequest_DBSystemInfo );
		usCharID = charid;

		siPersonID = personid;
		siType = type;

		stTime	=	Time	;
	}

};

class sDBResponse_DBSystemInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.

	UI16				usCharID;
	SI32				siPersonID;
	SI32				siType;
	SI64				siValue;			// DB ��û ����
	SYSTEMTIME			stTime;		// �� ��Ŷ�� ���� �ð�.
	sDBResponse_DBSystemInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_DBSystemInfo )) ;
	}

};

class sDBRequest_DBStartInfo
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_DBStartInfo()
	{
		packetHeader.usCmd  = DBMSG_REQUEST_DBSTARTINFO;
		packetHeader.usSize = sizeof( sDBRequest_DBSystemInfo );		
	}	
};

class sDBResponse_DBStartInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	cltServerStartInfo	clServerStartInfo;				// ���� ������ �ʿ��� �����͵�.
	SI32				siStartBankruptDateVary;		// �ڵ� �Ļ� �������̸� ��ɾ ���۵� �ð�
	SI16				siFourLeafUnique;				// ���� ������� ����Ŭ�ι� ����ũ

	sDBResponse_DBStartInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_DBStartInfo )) ;
	}
};

class sDBRequest_SetFourLeaf
{
public:
	sPacketHeader		packetHeader;

	SI16				siFourLeafUnique;				// ���� ������� ����Ŭ�ι� ����ũ

	sDBRequest_SetFourLeaf( SI16	_siFourLeafUnique )
	{
		ZeroMemory( this, sizeof( *this )) ;

		packetHeader.usCmd  = DBMSG_REQUEST_SETFOURLEAF;
		packetHeader.usSize = sizeof( sDBRequest_SetFourLeaf );		

		siFourLeafUnique = _siFourLeafUnique;
	}	
};

class sDBResponse_SetFourLeaf
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	SI16				siFourLeafUnique;				// ���� ������� ����Ŭ�ι� ����ũ

	sDBResponse_SetFourLeaf()
	{
		ZeroMemory( this, sizeof( *this )) ;
	}	
};


//-----------------------------------------
// Ư�� ����ڸ� �������� ������
//-----------------------------------------
class sDBRequest_PrisonUser
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siDate;
	TCHAR				szPersonName[MAX_PLAYER_NAME];
	SI32				siRequestID;

	cltGuiltyInfo		pclGuiltyInfo;

	sDBRequest_PrisonUser()
	{
		ZeroMemory(this, sizeof(sDBRequest_PrisonUser));
	}

	sDBRequest_PrisonUser(UI16 charid, SI32 date,TCHAR* pname,SI32 requestid,cltGuiltyInfo *clGuiltyInfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_PrisonUser );
		packetHeader.usCmd	= DBMSG_REQUEST_PRISONUSER;

		usCharID	= charid;

		siDate		= date;

		MStrCpy(szPersonName, pname, MAX_PLAYER_NAME );
		siRequestID = requestid ;

		pclGuiltyInfo.Set(clGuiltyInfo);
	}
};


class sDBResponse_PrisonUser
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;						// �����.

	TCHAR				szPersonName[MAX_PLAYER_NAME];
	SI32				siPersonID;						// ������� PersonID

	cltGuiltyInfo		clGuiltyInfo;

	sDBResponse_PrisonUser()
	{
		ZeroMemory(this, sizeof(sDBResponse_PrisonUser));
	}
};

class sDBRequest_GetAngelApplyerList // ��ȣõ�� ��û�� ����Ʈ ��û
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetAngelApplyerList()
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETANGELAPPLYERLIST;
		packetHeader.usSize = sizeof( sDBRequest_GetAngelApplyerList );
	}
};

class sDBResponse_GetAngelApplyerList // ��ȣõ�� ��û�� ����Ʈ ��û ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	HozoAngelList		stHozoAngelApplyerList[MAX_HOZO_ANGELLIST];

	sDBResponse_GetAngelApplyerList()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetAngelApplyerList));
	}
};

class sDBRequest_GetAngelList // ��ȣõ�� ����Ʈ ��û
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetAngelList()
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETANGELLIST;
		packetHeader.usSize = sizeof( sDBRequest_GetAngelList );
	}
};

class sDBResponse_GetAngelList // ��ȣõ�� ����Ʈ ��û ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	HozoAngelList		stHozoAngelList[MAX_HOZO_ANGELLIST];

	sDBResponse_GetAngelList() 
	{
		ZeroMemory(this, sizeof(sDBResponse_GetAngelList));
	}
};

class sDBRequest_SetAngelApplyer // ��ȣõ�� ��� ��û
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	bool				bAdmin ; // true�� ��û , false�� ����

	sDBRequest_SetAngelApplyer(UI16 charid , SI32 personid , bool admin)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetAngelApplyer );
		packetHeader.usCmd	= DBMSG_REQUEST_SETANGELAPPLYER;

		usCharID = charid ;
		siPersonID = personid ;

		bAdmin = admin ;
	}
};

class sDBResponse_SetAngelApplyer // ��ȣõ�� ��� ��û ����
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	SI32				siResult ; // 1�̸� ���� , 0�̸� ����

	SI32				siIndex ; // ������ ĳ���� �ε���
	bool				bAdmin ; // true�� ��û�� ���� ���� , false�� ������ ���� ����

	HozoAngelList		stHozoAngelApplyer ; // ����

	sDBResponse_SetAngelApplyer()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetAngelApplyer));
	}
};

class sDBRequest_SetAngel // ��ȣõ�� ��� ����
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	bool				bAdmin ; // true�� ��� �㰡 , false�� ��� �ź�

	sDBRequest_SetAngel(UI16 charid , SI32 personid ,bool admin)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetAngel );
		packetHeader.usCmd	= DBMSG_REQUEST_SETANGEL;

		usCharID = charid ;
		siPersonID = personid ;

		bAdmin = admin ;
	}
};

class sDBResponse_SetAngel // ��ȣõ�� ��� ���� ����
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	SI32				siResult ; // 1�̸� ���� , 0�̸� ����

	SI32				siIndex ; // ������ ĳ���� �ε���
	bool				bAdmin ; // true�� ��� �㰡 , false�� ��� �ź�

	HozoAngelList		stHozoAngel ; // ����

	sDBResponse_SetAngel()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetAngel));
	}
};

class sDBRequest_GetPoliceList // ���� ����Ʈ ��û
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetPoliceList()
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETPOLICELIST;
		packetHeader.usSize = sizeof( sDBRequest_GetPoliceList );
	}
};

class sDBResponse_GetPoliceList // ���� ����Ʈ ��û ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	HyungzoPoliceList	stHyungzoPoliceList[MAX_HYUNGZO_POLICELIST];

	sDBResponse_GetPoliceList() 
	{
		ZeroMemory(this, sizeof(sDBResponse_GetPoliceList));
	}
};

class sDBRequest_SetPolice // ���� ��� ����
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;	// ���������� ������ ���

	TCHAR				szPoliceName[ MAX_PLAYER_NAME ];
	bool				bAdmin ; // true�� ��� �㰡 , false�� ��� �ź�

	sDBRequest_SetPolice(UI16 charid , TCHAR* pName, bool admin)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetPolice );
		packetHeader.usCmd	= DBMSG_REQUEST_SETPOLICE;

		usCharID = charid ;

		MStrCpy(szPoliceName, pName, MAX_PLAYER_NAME);
		bAdmin = admin ;
	}
};

class sDBResponse_SetPolice // ���� ��� ���� ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ; // 1�̸� ���� , 0�̸� ����

	UI16				usCharID;
	bool				bAdmin ;   // true�� ��� �㰡 , false�� ��� �ź�

	HyungzoPoliceList	stHyungzoPolice; // ����

	sDBResponse_SetPolice()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetPolice));
	}
};

class sDBRequest_GetCriminalList // ���� ����Ʈ ��û
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetCriminalList()
	{
		packetHeader.usCmd  = DBMSG_REQUEST_GETCRIMINALLIST;
		packetHeader.usSize = sizeof( sDBRequest_GetCriminalList );
	}
};

class sDBResponse_GetCriminalList // ���� ����Ʈ ��û ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;						// �����.

	HyungzoCriminalList	stHyungzoCriminalList[MAX_HYUNGZO_CRIMINALLIST];

	sDBResponse_GetCriminalList() 
	{
		ZeroMemory(this, sizeof(sDBResponse_GetCriminalList));
	}
};

class sDBRequest_SetCriminal // ����� ��� ����
{
public:
	sPacketHeader		packetHeader;

	UI16				usCharID;	// ����� ������ ������ ���

	TCHAR				szCriminalName[ MAX_PLAYER_NAME ];
	TCHAR				szCriminalReason[ MAX_PRISON_REASON_SIZE ];
	SI32				siTime;	 // ������ ���� �ð�
	bool				bAdmin ; // true�� ��� �㰡 , false�� ��� �ź�

	sDBRequest_SetCriminal(UI16 charid , TCHAR* pName, TCHAR* pReason, SI32 time, bool admin)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetCriminal );
		packetHeader.usCmd	= DBMSG_REQUEST_SETCRIMINAL;

		usCharID = charid ;

		MStrCpy(szCriminalName, pName, MAX_PLAYER_NAME);
		MStrCpy(szCriminalReason, pReason, MAX_PRISON_REASON_SIZE);
		siTime = time;
		bAdmin = admin ;
	}
};

class sDBResponse_SetCriminal // ����� ��� ����
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult ; // 1�̸� ���� , 0�̸� ����

	UI16				usCharID;
	bool				bAdmin ;   // true�� ��� �㰡 , false�� ��� �ź�

	HyungzoCriminalList	stHyungzoCriminal; // ����

	sDBResponse_SetCriminal()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetCriminal));
	}
};


class sDBRequest_GetChangedName
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	SI32				siPage;
	SI32				siMaxNum;

	sDBRequest_GetChangedName(UI16 charid , SI32 personid ,SI32  page,SI32 maxnum)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetChangedName );
		packetHeader.usCmd	= DBMSG_REQUEST_GETCHANGEDNAME;

		usCharID = charid ;
		siPersonID = personid ;

		siPage = page ;
		siMaxNum = maxnum ;
	}
};

class sDBResponse_GetChangedName // ��ȣõ�� ��� ���� ����
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siPersonID;

	SI32				siResult ; // 1�̸� ���� , 0�̸� ����

	SI32				siPage;

	ChangedNameChar		stChangedNameChar[MAX_HOZO_CHANGEDNAME_LIST];

	sDBResponse_GetChangedName()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetChangedName));
	}
};

class sDBRequest_GetDailyNewChar
{
public:
	sPacketHeader		packetHeader;

	sDBRequest_GetDailyNewChar()
	{
		packetHeader.usSize = sizeof( sDBRequest_GetDailyNewChar );
		packetHeader.usCmd	= DBMSG_REQUEST_GETDAILYNEWCHAR;
	}
};

class sDBResponse_GetDailyNewChar
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siNewCharNum;
	SI32				siDelCharNum;

	sDBResponse_GetDailyNewChar()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetDailyNewChar));
	}
};

class sDBRequest_SetInstanceProfit_Village
{
public:
	sPacketHeader		packetHeader;

	SI32				siVillageUnique;

	bool				bStart;	// true�� ������ �ƴ϶� db ������ ��������

	sDBRequest_SetInstanceProfit_Village(SI32 villageunique,bool start)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetInstanceProfit_Village );
		packetHeader.usCmd	= DBMSG_REQUEST_SETINSTANCEPROFIT_VILLAGE;

		siVillageUnique = villageunique ;

		bStart = start ;
	}
};

class sDBResponse_SetInstanceProfit_Village
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siVillageUnique;

	sDBResponse_SetInstanceProfit_Village()
	{
		ZeroMemory(this,sizeof(sDBResponse_SetInstanceProfit_Village));
	}
};

class sDBRequest_Change_InstanceProfit
{
public:
	sPacketHeader		packetHeader;

	GMONEY				siMoney;	// ������ ��

	bool				bVillage;	// ������ �ֱ� ���ؼ� ��ȭ�ϴ� ���ΰ� �ƴѰ�.. �׳� �����ش�.

	sDBRequest_Change_InstanceProfit(GMONEY money,bool village)
	{
		packetHeader.usSize = sizeof( sDBRequest_Change_InstanceProfit );
		packetHeader.usCmd	= DBMSG_REQUEST_CHANGE_INSTANCEPROFIT;

		siMoney = money ;

		bVillage = village;
	}
};

class sDBResponse_Change_InstanceProfit
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;

	GMONEY				siMoney;	// ������ ��
	GMONEY				siLeftMoney; // �����ϰ� ���� ��

	bool				bVillage; // Request���� �� ���� �����ش�.

	sDBResponse_Change_InstanceProfit()
	{
		ZeroMemory(this,sizeof(sDBResponse_Change_InstanceProfit));
	}
};

class sDBRequest_InitStatistics
{
public:
	sPacketHeader		packetHeader;


	sDBRequest_InitStatistics()
	{
		packetHeader.usSize = sizeof( sDBRequest_InitStatistics );
		packetHeader.usCmd	= DBMSG_REQUEST_INITSTATISTICS;
	}
};

class sDBResponse_InitStatistics
{
public:
	sPacketHeader		packetHeader;

	cltCurrencyInfo		clCurrencyInfo;

	int					UserNum;
	int					NPCNum;
	int					ItemNum;
	int					MarketOrderNum;

	sDBResponse_InitStatistics()
	{
		ZeroMemory( this, sizeof( sDBResponse_InitStatistics ) );
	}
};

class sDBRequest_WriteStatistics
{
public:
	sPacketHeader		packetHeader;

	int					year;
	int					month;
	int					day;
	int					hour;
	int					minute;

	cltCurrencyInfo		clCurrencyInfo;

	int					UserNum;
	int					NPCNum;
	int					ItemNum;
	int					MarketOrderNum;

	sDBRequest_WriteStatistics( cltCurrencyInfo *pCurrencyInfo, int usernum, int npcnum, int itemnum, int marketordernum )
	{
		packetHeader.usSize = sizeof( sDBRequest_WriteStatistics );
		packetHeader.usCmd	= DBMSG_REQUEST_WRITESTATISTICS;

		memcpy( &clCurrencyInfo, pCurrencyInfo, sizeof( cltCurrencyInfo ) );
		UserNum = usernum;
		NPCNum = npcnum;
		ItemNum = itemnum;
		MarketOrderNum = marketordernum;
	}

};


class sDBRequest_GetWarRankInfo
{
public:
	sPacketHeader		packetHeader;

	int					m_warmapindex;

	sDBRequest_GetWarRankInfo( int warmapindex )
	{
		packetHeader.usSize = sizeof( sDBRequest_GetWarRankInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_GETWARRANKINFO;

		m_warmapindex = warmapindex;
	}

};

class sDBResponse_GetWarRankInfo
{
public:
	sPacketHeader		packetHeader;

	cltWarRankInfo		clWarRankInfo;

	SI32				siResult;

	sDBResponse_GetWarRankInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_GetWarRankInfo) );
	}

};

class sDBRequest_SetWarRankInfo
{
public:
	sPacketHeader		packetHeader;

	cltWarRankInfo		clWarRankInfo;

	sDBRequest_SetWarRankInfo( cltWarRankInfo *pWarRankInfo )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetWarRankInfo );
		packetHeader.usCmd	= DBMSG_REQUEST_SETWARRANKINFO;

		memcpy( &clWarRankInfo, pWarRankInfo, sizeof( cltWarRankInfo) );
	}

};

class sDBResponse_SetWarRankInfo
{
public:
	sPacketHeader		packetHeader;

	cltWarRankInfo		clWarRankInfo;

	SI32				siResult;

	sDBResponse_SetWarRankInfo()
	{
		ZeroMemory( this, sizeof(sDBResponse_SetWarRankInfo) );
	}

};

//************************************************************************************************
//
//	[ �߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ DB�� ���� �� ��Ŷ��. ] 
//
//----------------------------------------------------
// ��Ƽ��Ʈ ȯ�� �κ��丮 ������ ���� ���� ��û�ϴ� Ŭ����. 
//----------------------------------------------------
class sDBRequest_Artifact_InventoryList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	

	sDBRequest_Artifact_InventoryList()
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_InventoryList ) );
	}

	sDBRequest_Artifact_InventoryList(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_Artifact_InventoryList );
		packetHeader.usCmd  = DBMSG_REQUEST_ARTIFACT_INVENTORYLIST;
		usCharID			= id;
		siPersonID		    = personid;
	}
};

class sDBResponse_Artifact_InventoryList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	
	SI16				siResult;

	cltItem				clItemList[MAX_ITEM_ARTIFACT];			// Person�� ������ ����. 


	sDBResponse_Artifact_InventoryList()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_InventoryList ) );
		
		packetHeader.usSize = sizeof( sDBResponse_Artifact_InventoryList );
		packetHeader.usCmd  = DBMSG_RESPONSE_ARTIFACT_INVENTORYLIST;
	}
};

//----------------------------------------------------
// ��Ƽ��Ʈ �κ��丮�� ���� ��û�ϴ� Ŭ����.
//----------------------------------------------------
class sDBRequest_Artifact_SaveInventory
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siDisassembleItemPos;

	cltItem				clUseItem;

	cltItem				clItemList[MAX_ITEM_ARTIFACT];		// Person�� ������ ����. 
	bool				bCreateSID[MAX_ITEM_ARTIFACT];		// �����۵��� SID ���� ����

	SI16				siWennyPercent;
	SI32				siResolutionRate;					// ȯ����

	SI16				siUsedItemUnique;					// �����ϴ� �������� ����ũ
	SI16				siUsedItemNum;						// �����ϴ� �������� ����

	sDBRequest_Artifact_SaveInventory()
	{
		ZeroMemory(this, sizeof(sDBRequest_Artifact_SaveInventory));
	}

	sDBRequest_Artifact_SaveInventory(SI32 id, SI32 personid, SI16 disassembleitempos, SI16 wennypercent, SI16 resolutionrate  , cltItem * useItem ,cltItem* itemlist, bool* bcreatesidlist)
	{
		packetHeader.usSize  = sizeof( sDBRequest_Artifact_SaveInventory );
		packetHeader.usCmd	 = DBMSG_REQUEST_ARTIFACT_SAVEINVENTORY;
		usCharID			 = id;
		siPersonID			 = personid;
		siDisassembleItemPos = disassembleitempos;
		siWennyPercent		 = wennypercent;
		siResolutionRate	 = resolutionrate;

		clUseItem.Set(useItem);

		memcpy(clItemList, itemlist, sizeof(clItemList));
		memcpy(bCreateSID, bcreatesidlist, sizeof(bCreateSID));
	}
};

class sDBResponse_Artifact_SaveInventory
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	
	SI16				siDisassembleItemPos;
	SI16				siResult;

	SI16				siWennyPercent;
	SI16				siResolutionRate;

	cltItem				clUseItem;
	cltItem				clItemList[MAX_ITEM_ARTIFACT];		// Person�� ������ ����. 

	SI16				siUsedItemUnique;					// �����ϴ� �������� ����ũ
	SI16				siUsedItemNum;						// �����ϴ� �������� ����

	// log
	cltItem				clUseItem_Log;						// ������ ������

	sDBResponse_Artifact_SaveInventory()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_SaveInventory ) );

		packetHeader.usSize  = sizeof( sDBResponse_Artifact_SaveInventory );
		packetHeader.usCmd	 = DBMSG_RESPONSE_ARTIFACT_SAVEINVENTORY;
	}
};

//----------------------------------------------------
// ��Ƽ��Ʈ �κ��丮�� ����� �κ����� �̵� ��û Ŭ����
//----------------------------------------------------
class sDBRequest_Artifact_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI16				siStgPos;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	// to 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// ����� �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;
	bool				bCanPileSwitch;

	sDBRequest_Artifact_MoveItemStgToInv()
	{
		ZeroMemory(this, sizeof(sDBRequest_Artifact_MoveItemStgToInv));
	}

	sDBRequest_Artifact_MoveItemStgToInv(SI32 id, SI16 stgpos, SI32 personid,  SI16 invpos, cltItem* pclitem, bool canpileswitch)
	{
		packetHeader.usSize = sizeof( sDBRequest_Artifact_MoveItemStgToInv );
		packetHeader.usCmd	= DBMSG_REQUEST_ARTIFACT_MOVEITEMSTGTOINV;
		usCharID			= id;
		siPersonID			= personid;
		siStgPos			= stgpos;
		siInvPos			= invpos;
		clItem.Set(pclitem);
		bCanPileSwitch		= canpileswitch;
	}
};

class sDBResponse_Artifact_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI16				siResult;			// �����.

	SI16				siStgPos;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	// to 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// ����� �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;

	// log
	cltItem				clMoveItem;			// �Ű����� ������

	sDBResponse_Artifact_MoveItemStgToInv()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_MoveItemStgToInv ) );

		packetHeader.usSize = sizeof( sDBResponse_Artifact_MoveItemStgToInv );
		packetHeader.usCmd	= DBMSG_RESPONSE_ARTIFACT_MOVEITEMSTGTOINV;
	}
};

//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� S->DB ��Ŷ. ]
class sDBRequest_Artifact_Mixture
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;	

	SI16				m_siEquipItemPos;										// ����ü�� ������ �������� ��ġ.
	cltItem				m_clEquipItem;											// ����ü�� ������ ������ ����. 

	SI16				m_sCrystalItemPosList[MAX_ITEM_ARTIFACT_MIXTURE];			// ����ü �������� ��ġ.
	cltItem				m_clCrystalItemList[MAX_ITEM_ARTIFACT_MIXTURE];			// ����ü ������ ����. 

	sDBRequest_Artifact_Mixture()
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_Mixture ) );
	}

	sDBRequest_Artifact_Mixture( SI32 id, SI32 personid, SI16  _siEquipItemPos,		 cltItem* _clEquipItem,
														 SI16* _sCrystalItemPosList, cltItem* _clCrystalItemList )
	{	
		m_packetHeader.usSize	= sizeof( sDBRequest_Artifact_Mixture );
		m_packetHeader.usCmd	= DBMSG_REQUEST_ARTIFACT_MIXTURE;
		m_usCharID				= id;
		m_siPersonID		    = personid;

		m_siEquipItemPos	=  _siEquipItemPos;
		memcpy( &m_clEquipItem,			  _clEquipItem,				sizeof( m_clEquipItem ) );
		memcpy( &m_sCrystalItemPosList,   _sCrystalItemPosList,		sizeof( m_sCrystalItemPosList ) );
		memcpy( &m_clCrystalItemList,	  _clCrystalItemList,		sizeof( m_clCrystalItemList ) );
	}
};


//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� DB->S ��Ŷ. ]
class sDBResponse_Artifact_Mixture
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;	
	SI16				m_siResult;

	SI16				m_siEquipItemPos;									// ���յ� �������� ��ġ.
	cltItem				m_clEquipItem;										// ������ ��� ������ ����. 

	NSafeTArray<SI16, MAX_ITEM_ARTIFACT_MIXTURE>		m_siCrystalItemPosList;	// ����ü �������� ��ġ.
	NSafeTArray<cltItem, MAX_ITEM_ARTIFACT_MIXTURE>		m_clCrystalItemList;		// ����ü ������ ����. 

	NSafeTArray<cltItem, MAX_ITEM_ARTIFACT_MIXTURE>		m_clCrystalItemList_Log;	// ����ü ������ ���� - �α׿�

	sDBResponse_Artifact_Mixture()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_Mixture ) );

		m_packetHeader.usSize = sizeof( sDBResponse_Artifact_Mixture );
		m_packetHeader.usCmd  = DBMSG_RESPONSE_ARTIFACT_MIXTURE;
	}
};


//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� S->DB ��Ŷ. ]
class sDBRequest_Artifact_Remove
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_usCharID;
	SI32				m_siPersonID;	

	SI16				m_siEquipItemPos;									// ����ü�� ���ŵǴ� �������� ��ġ.(������ �ǰ���..)
	cltItem				m_clEquipItem;										// ����ü�� ���ŵǴ� ������.

	SI16				m_siCrystalItemPosList[ MAX_CRYSTAL_NUM ];				// ����ü�� ���ſ� ���� �������� ��ġ.(..)
	cltItem				m_clCrystalItemList[ MAX_CRYSTAL_NUM ];					// ����ü�� ���ſ� ���� ������.

	SI16				m_siCreateCrystalItemPosList[ MAX_CRYSTAL_NUM ];	// ����ü�� ���ŵ� ������ �������� ��ġ.()
	cltItem				m_clCreateCrystalItemList[ MAX_CRYSTAL_NUM ];		// ����ü�� ���ŵ� ������ ������.

	sDBRequest_Artifact_Remove()
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_Remove ) );

		m_packetHeader.usSize = sizeof( sDBRequest_Artifact_Remove );
		m_packetHeader.usCmd  = DBMSG_REQUEST_ARTIFACT_REMOVE;
	}
	
	sDBRequest_Artifact_Remove( SI32 id, SI32 personid, SI16   _siEquipItemPos,				cltItem* _clEquipItem,
														SI16*  _siCrystalItemPosList,		cltItem* _clCrystalItemList,
														SI16*  _siCreateCrystalItemPosList,	cltItem* _clCreateCrystalItemList )
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_Remove ) );

		m_packetHeader.usSize = sizeof( sDBRequest_Artifact_Remove );
		m_packetHeader.usCmd  = DBMSG_REQUEST_ARTIFACT_REMOVE;
	
		m_usCharID			= id;
		m_siPersonID		= personid;

		m_siEquipItemPos	= _siEquipItemPos;		
		memcpy( &m_clEquipItem, _clEquipItem, sizeof( m_clEquipItem ) );				

		memcpy( &m_siCrystalItemPosList, _siCrystalItemPosList, sizeof( m_siCrystalItemPosList ) );	
		memcpy( &m_clCrystalItemList,	 _clCrystalItemList,	sizeof( m_clCrystalItemList ) );	

		memcpy( m_siCreateCrystalItemPosList, _siCreateCrystalItemPosList,  sizeof( m_siCreateCrystalItemPosList ) );	
		memcpy( m_clCreateCrystalItemList,	  _clCreateCrystalItemList,		sizeof( m_clCreateCrystalItemList ) );	
	}
};

//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� DB->S ��Ŷ. ]
class sDBResponse_Artifact_Remove
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_usCharID;
	SI32				m_siPersonID;	
	SI16				m_siResult;


	SI16				m_siEquipItemPos;								// ����ü�� ���ŵ� �������� ��ġ.(������ �ǰ���..)
	cltItem				m_clEquipItem;									// ����ü�� ���ŵ� ������.
	
	SI16				m_siCrystalItemPosList[ MAX_CRYSTAL_NUM ];		// ����ü�� ���ſ� ���� �������� ��ġ.
	cltItem				m_clCrystalItemList[ MAX_CRYSTAL_NUM ];			// ����ü�� ���ſ� ���� ������.


	SI16				m_siCreateCrystalItemPosList[ MAX_CRYSTAL_NUM ];	// ����ü�� ���ŵ� ������ �������� ��ġ.()
	cltItem				m_clCreateCrystalItemList[ MAX_CRYSTAL_NUM ];		// ����ü�� ���ŵ� ������ ������.

	sDBResponse_Artifact_Remove()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_Remove ) );

		m_packetHeader.usSize = sizeof( sDBResponse_Artifact_Remove );
		m_packetHeader.usCmd  = DBMSG_RESPONSE_ARTIFACT_REMOVE;
	}
};

//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� ����  S->DB ��Ŷ. ]
class sDBRequest_Artifact_Slot_Create
{
public:
	sPacketHeader		m_packetHeader;
	
	UI16				m_usCharID;
	SI32				m_siPersonID;	

	SI16				m_siEquipItemPos;								// ������ �����Ǵ� �������� ��ġ.(������ �ǰ���..)
	cltItem				m_clEquipItem;									// ������ �����Ǵ� ������.

	SI16				m_siCrystalItemPos;								// ������ ������ ����ϴ� ����ü ��ġ.
	cltItem				m_clCrystalItem;								// ������ ������ ����ϴ� ����ü ������.

	cltItem				m_clEquipItem_ForLog;							// ������ �����Ǳ� ������ ������

	sDBRequest_Artifact_Slot_Create()
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_Slot_Create ) );

		m_packetHeader.usSize = sizeof( sDBRequest_Artifact_Slot_Create );
		m_packetHeader.usCmd	= DBMSG_REQUEST_ARTIFACT_SLOT_CREATE;
	}

	sDBRequest_Artifact_Slot_Create( UI16 id, SI32 personid, SI16  _siEquipItemPos,		cltItem* _clEquipItem,
															 SI16  _siCrystalItemPos,	cltItem* _clCrystalItem,
															 cltItem* pclEquipItem_ForLog )
	{
		ZeroMemory( this, sizeof( sDBRequest_Artifact_Slot_Create ) );

		m_packetHeader.usSize = sizeof( sDBRequest_Artifact_Slot_Create );
		m_packetHeader.usCmd  = DBMSG_REQUEST_ARTIFACT_SLOT_CREATE;

		m_usCharID			= id;
		m_siPersonID		= personid;

		m_siEquipItemPos			= _siEquipItemPos;		
		memcpy( &m_clEquipItem, _clEquipItem, sizeof( m_clEquipItem ) );	

		m_siCrystalItemPos			= _siCrystalItemPos;		
		memcpy( &m_clCrystalItem, _clCrystalItem, sizeof( m_clCrystalItem ) );	

		m_clEquipItem_ForLog.Set(pclEquipItem_ForLog);
	}
};

//[�߰� : Ȳ���� 2008. 2. 28 => ��Ƽ��Ʈ ���� ���� DB->S ��Ŷ. ]
class sDBResponse_Artifact_Slot_Create
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_usCharID;
	SI32				m_siPersonID;
	SI16				m_siResult;


	SI16				m_siEquipItemPos;								// ������ ������ �������� ��ġ.(������ �ǰ���..)
	cltItem				m_clEquipItem;									// ������ ������ ������.

	SI16				m_siCrystalItemPos;								// ������ ������ ���� ��ġ.(����ü ..)
	cltItem				m_clCrystalItem;								// ������ ������ ���� ������.

	cltItem				m_clEquipItem_ForLog;							// ���� ������ �õ��� ������
	cltItem				m_clCrystalItem_ForLog;							// ���� ������ ���� ������

	sDBResponse_Artifact_Slot_Create()
	{
		ZeroMemory( this, sizeof( sDBResponse_Artifact_Slot_Create ) );

		m_packetHeader.usSize = sizeof( sDBResponse_Artifact_Slot_Create );
		m_packetHeader.usCmd	= DBMSG_RESPONSE_ARTIFACT_SLOT_CREATE;
	}
};

//************************************************************************************************



//----------------------------------------------------
// Ȥ�θ�(2ȣ��) �κ��丮 ������ ���� ���� ��û�ϴ� Ŭ����. (ƾƾ)
//----------------------------------------------------
class sDBRequest_Wennyoldman_InventoryList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	

	sDBRequest_Wennyoldman_InventoryList()
	{
		ZeroMemory(this, sizeof(sDBRequest_Wennyoldman_InventoryList));
	}

	sDBRequest_Wennyoldman_InventoryList(SI32 id, SI32 personid)
	{
		packetHeader.usSize = sizeof( sDBRequest_Wennyoldman_InventoryList );
		packetHeader.usCmd = DBMSG_REQUEST_WENNYOLDMAN_INVENTORYLIST;
		usCharID			= id;

		siPersonID	= personid;
	}
};

class sDBResponse_Wennyoldman_InventoryList
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	
	SI32				siResult;

	cltItem				clItemList[MAX_ITEM_PER_WENNYOLD];			// Person�� ������ ����. 


	sDBResponse_Wennyoldman_InventoryList()
	{
		ZeroMemory(this, sizeof(sDBResponse_Wennyoldman_InventoryList));
	}
};

//----------------------------------------------------
// Ȥ�θ�(2ȣ��) �κ��丮�� ���� ��û�ϴ� Ŭ����. (ƾƾ)
//----------------------------------------------------
class sDBRequest_Wennyoldman_SaveInventory
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;
	SI16				siDisassembleItemPos;

	cltItem				clUseItem;

	cltItem				clItemList[MAX_ITEM_PER_WENNYOLD];	// Person�� ������ ����. 
	bool				bCreateSID[MAX_ITEM_PER_WENNYOLD];	// �����۵��� SID ���� ����
        
	SI16				siWennyPercent;
	SI32				siResolutionRate;					// ȯ����

	SI16				siUsedItemUnique;					// �����ϴ� �������� ����ũ
	SI16				siUsedItemNum;						// �����ϴ� �������� ����

	SI16				siDurabilityPenalty;				// �������� ���� �г�Ƽ

	sDBRequest_Wennyoldman_SaveInventory()
	{
		ZeroMemory(this, sizeof(sDBRequest_Wennyoldman_SaveInventory));
	}

	sDBRequest_Wennyoldman_SaveInventory( SI32 id, SI32 personid, SI16 disassembleitempos, SI16 wennypercent, SI16 resolutionrate  , cltItem * useItem ,cltItem* itemlist, bool* bcreatesidlist, SI16 durabilityPenalty )
	{
		packetHeader.usSize		= sizeof( sDBRequest_Wennyoldman_SaveInventory );
		packetHeader.usCmd		= DBMSG_REQUEST_WENNYOLDMAN_SAVEINVENTORY;
		usCharID				= id;
		siPersonID				= personid;
		siDisassembleItemPos	= disassembleitempos;
		siWennyPercent			= wennypercent;
		siResolutionRate		= resolutionrate;
		
		clUseItem.Set(useItem);
        
		memcpy(clItemList, itemlist, sizeof(clItemList));
		memcpy(bCreateSID, bcreatesidlist, sizeof(bCreateSID));

		siDurabilityPenalty		= durabilityPenalty;
	}
};

class sDBResponse_Wennyoldman_SaveInventory
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;	
	SI16				siDisassembleItemPos;
	SI32				siResult;

	SI16				siWennyPercent;
	SI16				siResolutionRate;

	cltItem				clUseItem;
	cltItem				clItemList[MAX_ITEM_PER_WENNYOLD];	// Person�� ������ ����. 

	SI16				siUsedItemUnique;					// �����ϴ� �������� ����ũ
	SI16				siUsedItemNum;						// �����ϴ� �������� ����

	cltItem				clUseItem_Log;						// FOR LOG

	SI16				siDurabilityPenalty;				// �������� ���� �г�Ƽ

	sDBResponse_Wennyoldman_SaveInventory()
	{
		ZeroMemory(this, sizeof(sDBResponse_Wennyoldman_SaveInventory));
	}
};

//----------------------------------------------------
// Ȥ�θ�(2ȣ��) �κ��丮�� ����� �κ����� �̵� ��û Ŭ���� (ƾƾ)
//----------------------------------------------------
class sDBRequest_Wennyoldman_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI16				siStgPos;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	// to 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// ����� �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;
	bool				bCanPileSwitch;

	sDBRequest_Wennyoldman_MoveItemStgToInv()
	{
		ZeroMemory(this, sizeof(sDBRequest_Wennyoldman_MoveItemStgToInv));
	}

	sDBRequest_Wennyoldman_MoveItemStgToInv(SI32 id, SI16 stgpos, SI32 personid,  SI16 invpos, cltItem* pclitem, bool canpileswitch)
	{
		packetHeader.usSize = sizeof( sDBRequest_Wennyoldman_MoveItemStgToInv );
		packetHeader.usCmd = DBMSG_REQUEST_WENNYOLDMAN_MOVEITEMSTGTOINV;
		usCharID			= id;
		siPersonID	= personid;
		siStgPos = stgpos;
		siInvPos = invpos;
		clItem.Set(pclitem);
		bCanPileSwitch = canpileswitch;
	}
};

class sDBResponse_Wennyoldman_MoveItemStgToInv
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	SI32				siResult;			// �����.

	SI16				siStgPos;			// Ȥ�θ�(2ȣ��) �κ��丮�� ��ġ. 

	// to 
	SI32				siPersonID;			// ����� �Ǵ� Person
	SI16				siInvPos;			// ����� �κ��丮�� ��ġ. 

	// what
	cltItem				clItem;

	// what
	cltItem				clItem_Log;			// FOR LOG

	sDBResponse_Wennyoldman_MoveItemStgToInv()
	{
		ZeroMemory(this, sizeof(sDBResponse_Wennyoldman_MoveItemStgToInv));
	}
};


class sDBRequest_RecommendPointList
{
public:

	sPacketHeader		packetHeader;
	UI16				usCharID;		// ��û��
	SI32				siPersonID;
	SI16				siCurrentPage; // ��û ������. ���������� ũ��� MAX_RPLISTDATA_PER_PAGE


	sDBRequest_RecommendPointList(UI16	CharID, SI32 PersonID,	SI16 CurrentPage )
	{
		packetHeader.usSize = sizeof( sDBRequest_RecommendPointList );
		packetHeader.usCmd  = DBMSG_REQUEST_RECOMMENDPOINT_LIST;

		usCharID = CharID;
		siPersonID = PersonID;
		siCurrentPage = CurrentPage;
	}

};

class sDBResponse_RecommendPointList
{
public:
	sPacketHeader		packetHeader;
	UI16				uiCharID;
	SI32				siPersonID;
	SI16				siCurrentPage;
	SI16				siMaxPage;

	stRPListData	sRPListData[MAX_RPLISTDATA_PER_PAGE];

	sDBResponse_RecommendPointList()
	{
		ZeroMemory(this, sizeof(sDBResponse_RecommendPointList));
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_VillageBankruptcy
//
// Last Modified 	: 2007 / 08 / 23
// Created		 	: �豤��
//
// Function			: [��û] �����Ļ��� �����Ѵ�.( ��� ��ɾ� )
//
//***************************************************************************************************
class sDBRequest_VillageBankruptcy
{
public:

	sPacketHeader		packetHeader;

	enum
	{
		BANKRUPTY = 0,
		RECOVERY
	};
	
	SI32	siCharID;		// ��û��
	SI32	siDateVary;		// ������
	SI32	siType;

	sDBRequest_VillageBankruptcy( SI32 CharID,	SI32 DateVary, SI32 Type  )
	{
		packetHeader.usSize = sizeof( sDBRequest_VillageBankruptcy );
		packetHeader.usCmd  = DBMSG_REQUEST_VILLAGEBANKRUPTCY;

		siCharID = CharID;
		siDateVary = DateVary;
		siType = Type;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_VillageBankruptcy
//
// Last Modified 	: 2007 / 08 / 23
// Created		 	: �豤��
//
// Function			: [����] �����Ļ��� �����Ѵ�.( ��� ��ɾ� )
//
//***************************************************************************************************
class sDBResponse_VillageBankruptcy
{
public:

	sPacketHeader		packetHeader;

	SI32				siResult;
	SI32				siCharID;				// ��û��
	SI32				siDateVary;				// ������
	SI32    			siVillageUnique[5];		// ���������� ���� ���� 5�� ����ũ

	sDBResponse_VillageBankruptcy()
	{
		ZeroMemory(this, sizeof(sDBResponse_VillageBankruptcy));
	}
};

enum
{
	SERVER_EVENT_REASON_INFO_REQUEST = 0,		// ���� ��û.
	SERVER_EVENT_REASON_DAILRY,					// �Ϸ� ��� ������Ʈ.
	SERVER_EVENT_REASON_END,					// �̺�Ʈ ����.
	SERVER_EVENT_REASON_INSTANCE_MAP_CLEAR,		// �δ� ����.
	//SERVER_EVENT_REASON_
};

enum
{
	SERVER_EVENT_SCORE_TYPE_DAILY = 0,		// �Ϸ�.
	SERVER_EVENT_SCORE_TYPE_TOTAL,			// ��ü.
};


//[����] ���� �̺�Ʈ�� ���õ� ������ DB�� ��û ��Ŷ. => 2008-6-19
class sDBRequest_Server_Event_Rank_Info
{
public:
	sPacketHeader		m_packetHeader;

	SI16				m_siServerUnique;					// ���� ����ũ.
	SI16				m_siReason;							// �޽����� ���� ���� 
	
	sDBRequest_Server_Event_Rank_Info(SI16 _siServerUnique, SI16 _siReason)
	{
		ZeroMemory(this, sizeof(*this));
		
		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Rank_Info );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_RANK_INFO;

		m_siServerUnique = _siServerUnique;
		m_siReason		 = _siReason;
	}
};


//[����] ���� �̺�Ʈ�� ���õ� ����(��������, ��������)�� ������ ���� ��Ŷ. => 2008-6-19
class sDBResponse_Server_Event_Rank_Info
{
public:
	sPacketHeader				m_packetHeader;
	SI32						m_siResult;
	SI16						m_siReason;									// �޽����� ���� ����
	
	//CNServerEvent_Rank_Record	m_clServerEvent_Rank_Record;
	CNServerRankInfo			m_clServerRankInfo[SERVER_MAX_NUM];			// �̺�Ʈ ����ñ��� �����Ǵ� ��ü ��������.(����Ʈ ����)
	CNServerDailyRankInfo		m_clServerDailyRankInfo[SERVER_MAX_NUM];	// �Ϸ� �����Ǵ� ��ü ��������.(������ ����)
	CNPersonalRankInfo			m_clPersonalRankInfo[USER_MAX_NUM];			// ���δ��� ����.(�� ������ 1~5��)
	SI16						m_ServerEventBufKind;						// �� ������ ���� ����.

	sDBResponse_Server_Event_Rank_Info()
	{
		ZeroMemory(this, sizeof(*this));
		
		// �⺻���� request���� ��û�� ����.
		m_siReason = SERVER_EVENT_REASON_INFO_REQUEST;
	}
};



//[����] ���� �̺�Ʈ�� ������������ ������ ��� DB�� ���� ��Ŷ. => 2008-6-19
class sDBRequest_Server_Event_Server_Info
{
public:
	sPacketHeader		m_packetHeader;
	
	SI16				m_siServerUnique;	
	
	sDBRequest_Server_Event_Server_Info(SI16 _siServerUnique)
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize   = sizeof( sDBRequest_Server_Event_Server_Info );
		m_packetHeader.usCmd    = DBMSG_REQUEST_SERVER_EVENT_SERVER_INFO;

		m_siServerUnique		=	_siServerUnique;
	}
};

//[����] ���� �̺�Ʈ�� ������ŷ ������ ��� ������ ���� ��Ŷ.(���� ���� ��ü�� ��´�) => 2008-6-19
class sDBResponse_Server_Event_Server_Info
{
public:
	sPacketHeader				m_packetHeader;
	SI32						m_siResult;

	CNServerRankInfo			m_clServerRankInfo[SERVER_MAX_NUM];	//������ŷ ����

	sDBResponse_Server_Event_Server_Info(void)
	{
		ZeroMemory(this, sizeof(*this));
	}
};


//[����] ���� �̺�Ʈ�� ���η�ŷ ���� ��û. => 2008-6-19
class sDBRequest_Server_Event_Personal_Info
{
public:
	sPacketHeader		m_packetHeader;
	SI16				m_siServerUnique;	

	sDBRequest_Server_Event_Personal_Info(SI16 _siServerUnique)
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Server_Info );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_PERSONAL_INFO;

		m_siServerUnique = _siServerUnique;
	}
};	// RESPONSE => sDBResponse_Server_Event_Server_Info 



//[����] ���� �̺�Ʈ�� ���õ� ������ DB�� ��û ��Ŷ. => 2008-6-19
class sDBRequest_Server_Event_Server_Score_Add	
{
public:
	sPacketHeader		m_packetHeader;

	SI16				m_siServerUnique;	
	SI16				m_siOpenCount;
	SI64				m_siAddScore;				// �߰��Ǵ� ����.
	

	sDBRequest_Server_Event_Server_Score_Add(SI16 _siServerUnique, SI16	_siOpenCount, SI64 _siAddScore)
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Server_Score_Add );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_SERVER_SCORE_ADD;

		m_siServerUnique = _siServerUnique;
		m_siOpenCount	 = _siOpenCount;
		m_siAddScore     = _siAddScore;
	}
};	// RESPONSE => sDBResponse_Server_Event_Server_Info 

//[����] ���� �̺�Ʈ�� �Ϸ� ������ ������ų ����. => 2008-6-19
class sDBRequest_Server_Event_Server_Daily_Score_Add	
{
public:
	sPacketHeader		m_packetHeader;

	SI16				m_siServerUnique;	
	SI64				m_siAddScore;
	SI16				m_siOpenCount;
	SI16				m_siReason;									// �޽����� ���� ����
	
	sDBRequest_Server_Event_Server_Daily_Score_Add(SI16 _siServerUnique, SI64 _siAddScore, SI16	_siOpenCount, SI16	_siReason)
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Server_Daily_Score_Add );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_SERVER_DAILY_SCORE_ADD;

		m_siServerUnique		  = _siServerUnique;
		m_siAddScore			  = _siAddScore;
		m_siOpenCount			  = _siOpenCount;
		m_siReason				  = _siReason;
	}
};	// RESPONSE => sDBResponse_Server_Event_Server_Info 

class sDBRequest_Server_Event_Clear
{
public:
	sPacketHeader		m_packetHeader;
	SI16				m_siServerUnique;	

	sDBRequest_Server_Event_Clear( SI16 _siServerUnique )
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Clear );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_CLEAR;

		m_siServerUnique		  = _siServerUnique;
	}
};	// RESPONSE => sDBResponse_Server_Event_Server_Info 


//[����] ���� �̺�Ʈ. �Ϸ簡 ������ ���� ��ü�� ����ϴ� ������ ������Ʈ �Ѵ�. => 2008-7-2
class sDBRequest_Server_Event_Server_Buf_Kind
{
public:
	sPacketHeader				m_packetHeader;

	SI16						m_siServerUnique;	
	SI16						m_siServerBufKind;		// ������ ���� ����. 

	sDBRequest_Server_Event_Server_Buf_Kind(SI16 _siServerUnique, SI16 _siServerBufKind)
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBRequest_Server_Event_Server_Buf_Kind );
		m_packetHeader.usCmd  = DBMSG_REQUEST_SERVER_EVENT_SERVER_BUF_KIND;
		
		m_siServerUnique  = _siServerUnique;
		m_siServerBufKind = _siServerBufKind;
	}
};	// RESPONSE => sDBResponse_Server_Event_Server_Buf_Kind 

class sDBResponse_Server_Event_Server_Buf_Kind
{
public:
	sPacketHeader				m_packetHeader;
	SI32						m_siResult;
	
	SI16						m_siServerBufKind;		// ������ ���� ����. 

	sDBResponse_Server_Event_Server_Buf_Kind()
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize = sizeof( sDBResponse_Server_Event_Server_Buf_Kind );
		m_packetHeader.usCmd  = DBMSG_RESPONSE_SERVER_EVENT_SERVER_BUF_KIND;
	}
};	


// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ���� ��û
class sDBRequest_Server_Event_Server_Quest_Info_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siEventType;			// ���� �̺�Ʈ Ÿ��
	SI32			m_siCondition1;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	SI32			m_siCondition2;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2
	SI32			m_siNeedClearAmount;	// Ŭ���� �ϱ� ���� �ʿ��� ����
	SI16			m_siRewardItemUnique;	// Ŭ����� ����Ǵ� ������(����ũ)
	SI16			m_siRewardItemAmount;	// ����Ǵ� ������ ����
	SI32			m_siLimitMinute;		// ���ѽð�

	bool			m_bCharacter[ Const_ServerEvent_Max_QuestCharacter ];
	SI16			m_siInFailCharacter[ Const_ServerEvent_Max_QuestCharacter * Const_ServerEvent_MulNum ];
	SI16			m_siCharacterIndex;
	SI32			m_siNowAmount;


	sDBRequest_Server_Event_Server_Quest_Info_Set( CNServerEvent_QuestData* pclSEQuestData, bool* bCharacter, SI16* siInFailCharacter, SI16 siCharacterIndex, SI32 siNowAmount )
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize	= sizeof( sDBRequest_Server_Event_Server_Quest_Info_Set );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SERVER_EVENT_QUEST_INFO_SET;

		m_siEventType			= pclSEQuestData->GetEventType();
		m_siCondition1			= pclSEQuestData->GetCondition1();
		m_siCondition2			= pclSEQuestData->GetCondition2();
		m_siNeedClearAmount		= pclSEQuestData->GetNeedClearAmount();
		m_siRewardItemUnique	= (SI16)pclSEQuestData->GetRewardItemUnique();
		m_siRewardItemAmount	= (SI16)pclSEQuestData->GetRewardItemAmount();
		m_siLimitMinute			= pclSEQuestData->GetLimitMinute();
		
		memcpy( m_bCharacter, bCharacter, sizeof(m_bCharacter) );
		memcpy( m_siInFailCharacter, siInFailCharacter, sizeof(m_siInFailCharacter) );

		m_siCharacterIndex		= siCharacterIndex;
		m_siNowAmount			= siNowAmount;
	}
};

// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ���� ��û ����
class sDBResponse_Server_Event_Server_Quest_Info_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	sDBResponse_Server_Event_Server_Quest_Info_Set( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

};	// DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_SET

// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ��û
class sDBRequest_Server_Event_Server_Quest_Info_Get
{
public:
	sPacketHeader	m_packetHeader;

	sDBRequest_Server_Event_Server_Quest_Info_Get( void )
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize	= sizeof( sDBRequest_Server_Event_Server_Quest_Info_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SERVER_EVENT_QUEST_INFO_GET;
	}
};

// [����] ���� �̺�Ʈ ����Ʈ ���� ���� ��û ����
class sDBResponse_Server_Event_Server_Quest_Info_Get
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	SI32			m_siEventType;			// ���� �̺�Ʈ Ÿ��
	SI32			m_siCondition1;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 1
	SI32			m_siCondition2;			// Ŭ���� �ϱ� ���� �ʿ��� ���� 2
	SI32			m_siNeedClearAmount;	// Ŭ���� �ϱ� ���� �ʿ��� ����
	SI16			m_siRewardItemUnique;	// Ŭ����� ����Ǵ� ������(����ũ)
	SI16			m_siRewardItemAmount;	// ����Ǵ� ������ ����
	SI32			m_siLimitMinute;		// ���ѽð�

	bool			m_bCharacter[ Const_ServerEvent_Max_QuestCharacter ];
	SI16			m_siInFailCharacter[ Const_ServerEvent_Max_QuestCharacter * Const_ServerEvent_MulNum ];
	SI16			m_siCharacterIndex;
	SI32			m_siNowAmount;


	sDBResponse_Server_Event_Server_Quest_Info_Get( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

};	// DBMSG_RESPONSE_SERVER_EVENT_QUEST_INFO_GET

class sDBRequest_Server_Event_Server_Person_Score_Set
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;

	SI32			m_siPersonID;
	SI64			m_siScore;

	sDBRequest_Server_Event_Server_Person_Score_Set( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

	sDBRequest_Server_Event_Server_Person_Score_Set( UI16 uiCharID, SI32 siPersonID, SI64 siScore )
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize	= sizeof( sDBRequest_Server_Event_Server_Person_Score_Set );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SERVER_EVENT_PERSON_SCORE_SET;

		m_uiCharID				= uiCharID;

		m_siPersonID			= siPersonID;
		m_siScore				= siScore;
		
	}

};

class sDBRequest_Server_Event_Server_Person_Score_Get
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;

	SI32			m_siPersonID;
	
	sDBRequest_Server_Event_Server_Person_Score_Get( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

	sDBRequest_Server_Event_Server_Person_Score_Get( UI16 uiCharID,	SI32 siPersonID )
	{
		ZeroMemory(this, sizeof(*this));

		m_packetHeader.usSize	= sizeof( sDBRequest_Server_Event_Server_Person_Score_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SERVER_EVENT_PERSON_SCORE_GET;

		m_uiCharID				= uiCharID;
		m_siPersonID			= siPersonID;
	}

};

class sDBResponse_Server_Event_Server_Person_Score_Get
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;

	SI32			m_siPersonID;

	SI16			m_siLevel;
	SI64			m_siScore;


	class sDBResponse_Server_Event_Server_Person_Score_Get( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

};	// DBMSG_RESPONSE_SERVER_EVENT_PERSON_SCORE_GET

class sDBRequest_SetMuteTime
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;

	SI32			m_siTargetPersonID;
	SYSTEMTIME		m_stMuteTime;

	sDBRequest_SetMuteTime( UI16 uiCharID, SI32 siPersonID, SYSTEMTIME* pstMuteTime )
	{
		ZeroMemory(this, sizeof(sDBRequest_SetMuteTime));

		m_packetHeader.usSize	= sizeof( sDBRequest_SetMuteTime );
		m_packetHeader.usCmd	= DBMSG_REQUEST_SETMUTETIME;

		m_uiCharID				= uiCharID;

		m_siTargetPersonID		= siPersonID;
		memcpy(&m_stMuteTime, pstMuteTime, sizeof(m_stMuteTime));
	}
};

class sDBResponse_SetMuteTime
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	UI16			m_uiCharID;

	SI32			m_siTargetPersonID;
	SYSTEMTIME		m_stMuteTime;

	sDBResponse_SetMuteTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetMuteTime));
	}
};


class sDBRequest_GetMuteTime
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;
	SI32			m_siPersonID;

	sDBRequest_GetMuteTime( UI16 uiCharID, SI32 siPersonID )
	{
		ZeroMemory(this, sizeof(sDBRequest_GetMuteTime));

		m_packetHeader.usSize	= sizeof( sDBRequest_GetMuteTime );
		m_packetHeader.usCmd	= DBMSG_REQUEST_GETMUTETIME;

		m_uiCharID		= uiCharID;
		m_siPersonID	= siPersonID;
	}
};

class sDBResponse_GetMuteTime
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	UI16			m_uiCharID;

	SI32			m_siPersonID;
	SYSTEMTIME		m_stMuteTime;

	sDBResponse_GetMuteTime()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetMuteTime));
	}
};


class cltElixir_Info
{
public:
	cltElixir_Info() { ZeroMemory( this, sizeof(*this) );	}
	~cltElixir_Info(){										}

public:
	SI16 GetTotalPoint() { return m_siPoint + m_siStr + m_siDex + m_siVit + m_siMag + m_siHnd + m_siWis; }

public:
	SI32	m_siEndMinuteVary;		// ������ ����� ������ �ð�.
	UI08	m_uiMultiple;			// ������ ��� ���. 

	SI16	m_siPoint;				// ����Ʈ.
	SI16	m_siStr;				// �ٷ�	
	SI16	m_siDex;				// ���߷�
	SI16	m_siVit;				// ����� 
	SI16	m_siMag;				// ���� 
	SI16	m_siHnd;				// ������. 
	SI16	m_siWis;				// ���� �߰�.
};

class sDBRequest_Elixir_Get
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;
	SI32			m_siPersonID;

	sDBRequest_Elixir_Get( UI16 uiCharID, SI32 siPersonID )
	{
		ZeroMemory( this, sizeof(sDBRequest_Elixir_Get) );

		m_packetHeader.usSize	= sizeof( sDBRequest_Elixir_Get );
		m_packetHeader.usCmd	= DBMSG_REQUEST_ELIXIR_GET;

		m_uiCharID		= uiCharID;
		m_siPersonID	= siPersonID;
	}
};

class sDBResponse_Elixir_Get
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;
	SI32			m_siPersonID;

	SI32			m_siResult;

	cltElixir_Info  m_clElixirInfo;			// ������ ����.

	sDBResponse_Elixir_Get()
	{
		ZeroMemory( this, sizeof(sDBResponse_Elixir_Get) );
	}
};



class sDBRequest_Elixir_Set
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;
	SI32			m_siPersonID;

	SI32			m_siElixirItemUnique;	// ����ϴ� ������ �������� ����ũ.
	SI32			m_siElixirItemPos;		// ����ϴ� ������ �������� �κ� ��ġ.

	SI32			m_siWaterItemUnique;	// ����ϴ� ������ ��� �������� ����ũ.
	SI32			m_siWaterItemPos;		// ����ϴ� ������ ��� �������� �κ� ��ġ.

	SI32			m_siWaterItemNum;		// ����ϴ� ������ ��� �������� ����.

	cltElixir_Info  m_clElixirInfo;		// ������ ����.

	bool			m_bUseItem;				// �Ҹ��ϴ� �������� �ִ°�.

	sDBRequest_Elixir_Set(  UI16 			 _uiCharID, 
							SI32 			 _siPersonID, 
							cltElixir_Info*  _pclElixir_Info		= NULL,
							SI32 			 _siElixirItemPos		= 0,    
							SI32 			 _siElixirItemUnique	= 0, 
							SI32 			 _siWaterItemPos		= 0,    
							SI32 			 _siWaterItemUnique		= 0,
							SI32 			 _siWaterItemNum		= 0,
							bool			 _bUseItem				= false	)		
	{
		ZeroMemory( this, sizeof(sDBRequest_Elixir_Set) );
		
		m_packetHeader.usSize	= sizeof( sDBRequest_Elixir_Set );
		m_packetHeader.usCmd	= DBMSG_REQUEST_ELIXIR_SET;

		m_uiCharID				= _uiCharID;
		m_siPersonID			= _siPersonID;

		_pclElixir_Info	? memcpy( &m_clElixirInfo, _pclElixir_Info, sizeof(m_clElixirInfo) ) : 0;

		m_siElixirItemPos    	= _siElixirItemPos;   		
		m_siElixirItemUnique 	= _siElixirItemUnique;	

		m_siWaterItemPos     	= _siWaterItemPos;   		
		m_siWaterItemUnique  	= _siWaterItemUnique;	

		m_siWaterItemNum	 	= _siWaterItemNum;

		m_bUseItem				= _bUseItem;
	}
};

class sDBResponse_Elixir_Set
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;
	UI16			m_uiCharID;
	SI32			m_siPersonID;

	SI32			m_siElixirItemUnique;	// ����ϴ� ������ �������� ����ũ.
	SI32			m_siElixirItemPos;		// ����ϴ� ������ �������� �κ� ��ġ.

	SI32			m_siWaterItemUnique;	// ����ϴ� ������ ��� �������� ����ũ.
	SI32			m_siWaterItemPos;		// ����ϴ� ������ ��� �������� �κ� ��ġ.

	SI32			m_siWaterItemNum;		// ����ϴ� ������ ��� �������� ����.

	cltElixir_Info  m_clElixirInfo;			// ������ ����.

	bool			m_bUseItem;				// �Ҹ��ϴ� �������� �ִ°�.

	sDBResponse_Elixir_Set()
	{
		ZeroMemory( this, sizeof(sDBResponse_Elixir_Set) );
	}
};

// [����] ���θ��� ĳ���� ������ ��û.
class sDBReuest_Promoter_Info_Get
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiCharID;

	TCHAR			m_szPromoterName[MAX_PLAYER_NAME];

	sDBReuest_Promoter_Info_Get(TCHAR* _pszPromoterName, UI16 _uiCharID)
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize	= sizeof( *this );
		m_packetHeader.usCmd	= DBMSG_REQUEST_PROMOTER_INFO_GET;

		memcpy( m_szPromoterName, _pszPromoterName, sizeof(m_szPromoterName) );
		m_uiCharID = _uiCharID;
	}
};


class sDBResponse_Promoter_Info_Get
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	UI16			m_uiCharID;

	SI32			m_siPersonID;
	SI16			m_siCharKind;
	SI16			m_siLevel;

	TCHAR			m_szPromoterName[MAX_PLAYER_NAME];

	sDBResponse_Promoter_Info_Get()
	{
		ZeroMemory( this, sizeof(*this) );
	}
};



//	[��ȣ] ��ȭ������ - ��밡�� ��ȭ�� 
class sDBRequest_SetBalanceCanUseCurrency
{
public:
	sPacketHeader		packetHeader;

	bool				m_bType;		
	GMONEY				m_siMoney;
	SI32				m_siResult;
	SI32 				m_siCharID;

	sDBRequest_SetBalanceCanUseCurrency(GMONEY siMoney, SI32 siCharID = 0)
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETBALANCECANUSECURRENCY;
		packetHeader.usSize = sizeof(sDBRequest_SetBalanceCanUseCurrency);
		m_siMoney		=	siMoney;
		m_bType			=	0;			//	Type�� 0�̸� Set
		m_siCharID		=	siCharID;
	}
};

//	[��ȣ] ��ȭ������ - ��밡�� ��ȭ�� 
class sDBResponse_SetBalanceCanUseCurrency
{
public:
	sPacketHeader		packetHeader;

	SI32				m_siResult;
	GMONEY				m_siMoney;
	SI32				m_siCharID;

	sDBResponse_SetBalanceCanUseCurrency()
	{
		m_siCharID = 0;
		packetHeader.usCmd = DBMSG_RESPONSE_SETBALANCECANUSECURRENCY;
		packetHeader.usSize = sizeof(sDBResponse_SetBalanceCanUseCurrency);
	}
};

//	[��ȣ] ��ȭ������ - ��밡�� ��ȭ�� 
class sDBRequest_GetBalanceCanUseCurrency
{
public:
	sPacketHeader		packetHeader;

	bool				m_bType;		

	GMONEY				m_siMoney;
	SI32				m_siResult;

	SI32				m_siCharID;
	bool				m_bCalledGM;		//	GM�� ��ȭ���� �䱸�Ѱ��ΰ�.

	//	�Ϲݻ���ڰ� �䱸
	sDBRequest_GetBalanceCanUseCurrency()	
	{
		packetHeader.usCmd = DBMSG_REQUEST_GETBALANCECANUSECURRENCY;
		packetHeader.usSize = sizeof(sDBRequest_GetBalanceCanUseCurrency);
		m_siMoney = 0;
		m_bType = 1;				//	Type�� 1�̸� Get

		m_bCalledGM = 0;
		m_siCharID  = 0;
	}


	//	GM�� �䱸
	sDBRequest_GetBalanceCanUseCurrency(SI32 siCharID, bool bCalledGM)	
	{
		packetHeader.usCmd = DBMSG_REQUEST_GETBALANCECANUSECURRENCY;
		packetHeader.usSize = sizeof(sDBRequest_GetBalanceCanUseCurrency);
		m_siMoney = 0;
		m_bType = 1;				//	Type�� 1�̸� Get


		m_siCharID  = siCharID;	
		m_bCalledGM = bCalledGM;
	}
};

//	[��ȣ] ��ȭ������ - ��밡�� ��ȭ�� 
class sDBResponse_GetBalanceCanUseCurrency
{
public:
	sPacketHeader		packetHeader;

	SI32				m_siResult;
	GMONEY				m_siMoney;

	SI32				m_siCharID;
	bool				m_bCalledGM;		//	GM�� ��ȭ���� �䱸�Ѱ��ΰ�.


	sDBResponse_GetBalanceCanUseCurrency(bool bCalledGM = false)
	{
		packetHeader.usCmd = DBMSG_RESPONSE_GETBALANCECANUSECURRENCY;
		packetHeader.usSize = sizeof(sDBResponse_GetBalanceCanUseCurrency);

		m_bCalledGM = bCalledGM;
	}
};
//-------------------------------------------------------------------------------------------------------------------
//[����] �����̺�Ʈ ���� �̺�Ʈ�� ����
//-------------------------------------------------------------------------------------------------------------------
class sDBRequest_GoonzuRaccoonEvent_SaveInfo	// ���� �����̺�Ʈ ������ ��� ���� �Ѵ� 
{
public:
	sPacketHeader	m_packetHeader;

	SYSTEMTIME	m_SetTime;

	cGoonzuRaccoonEventData	m_GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT];

	sDBRequest_GoonzuRaccoonEvent_SaveInfo( void )
	{
		ZeroMemory(this, sizeof(*this));
	}

	sDBRequest_GoonzuRaccoonEvent_SaveInfo(SYSTEMTIME SetTime , cGoonzuRaccoonEventData* pGoonzuRaccoonEventData )
	{
		m_packetHeader.usCmd = DBMSG_REQUEST_GOONZURACCOONEVENT_SETINFO;
		m_packetHeader.usSize = sizeof(sDBRequest_GoonzuRaccoonEvent_SaveInfo);

		m_SetTime	=	SetTime	;
		memcpy(&m_GoonzuRaccoonEventData,	pGoonzuRaccoonEventData,	sizeof(m_GoonzuRaccoonEventData));
	}

};

class sDBResponse_GoonzuRaccoonEvent_SaveInfo
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	sDBResponse_GoonzuRaccoonEvent_SaveInfo()	
	{
		m_packetHeader.usCmd = DBMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO;
		m_packetHeader.usSize = sizeof(sDBResponse_GoonzuRaccoonEvent_SaveInfo);
	}

};	// DBMSG_RESPONSE_GOONZURACCOONEVENT_SETINFO
class sDBRequest_GoonzuRaccoonEvent_GetInfo	// ���� �����̺�Ʈ ������ ��񿡼� ������ �´�
{
public:
	sPacketHeader	m_packetHeader;
	// �ش��ɸ��� ����ũ�� �۽� ���̵�� ���� �ϴ� ������ ����
	sDBRequest_GoonzuRaccoonEvent_GetInfo( void )
	{
		ZeroMemory(this, sizeof(*this));
		m_packetHeader.usCmd = DBMSG_REQUEST_GOONZURACCOONEVENT_GETINFO;
		m_packetHeader.usSize = sizeof(sDBRequest_GoonzuRaccoonEvent_GetInfo);
	}
};

class sDBResponse_GoonzuRaccoonEvent_GetInfo
{
public:
	sPacketHeader	m_packetHeader;

	SYSTEMTIME m_stTime	;

	cGoonzuRaccoonEventData	m_GoonzuRaccoonEventData[MAX_SELECTRFIELD_NUM_GOONZURACCOONEVENT];

	sDBResponse_GoonzuRaccoonEvent_GetInfo( void )
	{
		ZeroMemory(this, sizeof(*this));
	}
};	// DBMSG_RESPONSE_GOONZURACCOONEVENT_GETINFO
#endif
