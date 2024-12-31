#ifndef _NTRADESERVERMSG_H
#define _NTRADESERVERMSG_H

#define MAX_TRADESERVER_GET_LIST	50		// �ѹ��� �ܾ�� ����Ʈ�� �ִ��
#define MAX_TRADESERVER_ORDER_LIST	1500	// �ִ� ��� ����
#define MAX_TRADESERVER_ACU_LIST	10		// ��ť �ֽų��� �ִ��

// �ֹ�ǰ �ø� �ð� - �����ð�
class cltTradeDate
{
public:
	UI08		uiYear;
	UI08		uiMonth;
	UI08		uiDay;
	UI08		uiHour;

public:
	cltTradeDate()
	{
		uiYear = 0 ;
		uiMonth = 0 ;
		uiDay = 0 ;
		uiHour = 0 ;
	}

	void Set(UI08 year, UI08 month, UI08 day, UI08 hour, UI08 minute)
	{
		uiYear		= year;
		uiMonth		= month;
		uiDay		= day;
		uiHour		= hour;
	}
	void Set(cltTradeDate*clinfo)
	{
		uiYear		= clinfo->uiYear ;
		uiMonth		= clinfo->uiMonth ;
		uiDay		= clinfo->uiDay ;
		uiHour		= clinfo->uiHour ;
	}

	void Init()
	{
		uiYear = 0 ;
		uiMonth = 0 ;
		uiDay = 0 ;
		uiHour = 0 ;
	}
};

// �ֹ�ǰ �� ����
class cltTradeItem
{
public:
	SI16 siUnique;
	SI16 siItemNum;

	SI16 siType; // �Ӽ� ����
	SI16 siPower; // �Ӽ��� ��

	SI16 siRank; // �ֹ�ǰ ���
	SI64 siPrice; // �ֹ�ǰ ����

	SI08 siRareType; // �ֹ�ǰ�� ���(��ǰ,ȣǰ ��)

	char szItemData[24] ;

	cltTradeDate clDate;

	// ������ ���ʿ� ���� ��ų��(�������������� �߰��ߴ�)
	UI08 uiSkillNumber;
	// �����Ǹ�ġ Ƚ��(�������������� �߰��ߴ�)
	UI08 uiChangeAbilityCount;
	//������� ȸ��(��������,���߿� ȣǰ,��ǰ���� �߰�)
	UI08 uiAbilityUp;

	cltTradeItem()
	{
		siUnique = 0 ;
		siItemNum = 0 ;

		siType = 0;
		siPower = 0;

		siRank = 0 ;
		siPrice = 0 ;

		siRareType = 0 ;

		ZeroMemory(szItemData,sizeof(char) * 24 );

		clDate.Init();

		uiSkillNumber = 0;
		uiChangeAbilityCount = 0;
		uiAbilityUp = 0;
	}

	void Set(cltTradeItem*pcltradeitem)
	{
		siUnique = pcltradeitem->siUnique ;
		siItemNum = pcltradeitem->siItemNum ;

		siType = pcltradeitem->siType;
		siPower = pcltradeitem->siPower ;

		siRank = pcltradeitem->siRank ;
		siPrice = pcltradeitem->siPrice ;

		siRareType = pcltradeitem->siRareType ;

		// �������� �ٲ� �� ������ �ϴ� ���� ���� - 2006/09/18 SJY
//		if ( pcltradeitem->szItemData[0] != NULL && pcltradeitem->szItemData[0] != '\0')
			memcpy(szItemData,pcltradeitem->szItemData,24);
//		else ZeroMemory(szItemData,sizeof(char)*24);


		clDate.Set(&pcltradeitem->clDate);

		uiSkillNumber = pcltradeitem->uiSkillNumber;
		uiChangeAbilityCount = pcltradeitem->uiChangeAbilityCount;
		uiAbilityUp			= pcltradeitem->uiAbilityUp;

	}

	void Init()
	{
		siUnique = 0 ;
		siItemNum = 0 ;

		siType = 0;
		siPower = 0;

		siRank = 0 ;
		siPrice = 0 ;

		siRareType = 0 ;

		ZeroMemory(szItemData,sizeof(char) * 24 );

		clDate.Init();

		uiSkillNumber = 0;
		uiChangeAbilityCount = 0;
		uiAbilityUp	= 0;
	}
};

// �ֹ� �� ����
class cltTradeServerOrder
{
public:
	//char szServerName[20]; // �ֹ� ����
	char szAccountID[20]; // �ֹ��� ����
	char szCharName[20]; // �ֹ��� �̸�

	SI32 siPersonID; // �ֹ��� personid
	SI16 siCharNation; // �ֹ��� ���� ��ȣ

	cltTradeItem clitem;
	SI32 siIndex; // �ֹ��� ������

	char szServerNation[4]; // ���� ���� �ڵ�
	SI16 siServerIndex; // �ֹ� ����

	cltTradeServerOrder()
	{
		//ZeroMemory(szServerName,sizeof(char) * 20);
		ZeroMemory(szAccountID,sizeof(char) * 20);
		ZeroMemory(szCharName,sizeof(char) * 20);

		siCharNation = 0 ;
		siPersonID = 0 ;

		clitem.Init();

		siIndex = 0 ;

		ZeroMemory(szServerNation,sizeof(char)*4);
		siServerIndex = 0 ;
	}

	void Init()
	{
		//ZeroMemory(szServerName,sizeof(char) * 20);
		ZeroMemory(szAccountID,sizeof(char) * 20);
		ZeroMemory(szCharName,sizeof(char) * 20);

		siCharNation = 0 ;
		siPersonID = 0 ;

		clitem.Init();

		siIndex = 0 ;

		ZeroMemory(szServerNation,sizeof(char)*4);
		siServerIndex = 0 ;
	}

	void Set(cltTradeServerOrder* pclOrder)
	{
		//memcpy(szServerName,pclOrder->szServerName,20);
		memcpy(szAccountID,pclOrder->szAccountID,20);
		memcpy(szCharName,pclOrder->szCharName,20);

		siCharNation = pclOrder->siCharNation ;
		siPersonID = pclOrder->siPersonID ;

		clitem.Set(&pclOrder->clitem);

		siIndex = pclOrder->siIndex ;

		memcpy(szServerNation,pclOrder->szServerNation,4);
		siServerIndex = pclOrder->siServerIndex ;
	}

	bool IsSame(cltTradeServerOrder* pclOrder)
	{
		//if ( strcmp(szServerName,pclOrder->szServerName) )
		//	return false ;
		if ( strcmp(szAccountID,pclOrder->szAccountID) )
			return false ;
		if ( strcmp(szCharName,pclOrder->szCharName) )
			return false ;

		if ( siCharNation != pclOrder->siCharNation )
			return false ;
		if ( siPersonID != pclOrder->siPersonID )
			return false ;
		if ( siIndex != pclOrder->siIndex )
			return false ;

		if ( clitem.siItemNum != pclOrder->clitem.siItemNum )
			return false ;
		if ( clitem.siPower != pclOrder->clitem.siPower )
			return false ;
		if ( clitem.siPrice != pclOrder->clitem.siPrice )
			return false ;
		if ( clitem.siRank != pclOrder->clitem.siRank )
			return false ;
		if ( clitem.siRareType != pclOrder->clitem.siRareType )
			return false ;
		if ( clitem.siType != pclOrder->clitem.siType )
			return false ;
		if ( clitem.siUnique != pclOrder->clitem.siUnique )
			return false ;

		if ( strcmp(clitem.szItemData,pclOrder->clitem.szItemData) != 0 )
			return false ;

		if ( strcmp(szServerNation,pclOrder->szServerNation) )
			return false ;
		if ( siServerIndex != pclOrder->siServerIndex )
			return false ;
		return true ;
	}
};

class cltTradeAcuList
{
public:
	SI16			m_siItemUnique;	// �Ǹ��� ������ ����ũ
	SI64			m_siPriceACU;	// �Ǹŵ� ����
	cltTradeDate	m_clDate;		// �Ǹŵ� ��¥


	cltTradeAcuList()
	{
		Init();
	}

	cltTradeAcuList( SI16 siItemUnique, SI64 siPriceACU, cltTradeDate* pclDate )
	{
		Init();

		m_siItemUnique	= siItemUnique;
		m_siPriceACU	= siPriceACU;

		if ( pclDate )
		{
			m_clDate.Set( pclDate );
		}
	}

	cltTradeAcuList( cltTradeAcuList* pclAcuList )
	{
		Init();

		if ( pclAcuList )
		{
			memcpy( this, pclAcuList, sizeof(cltTradeAcuList) );
		}
	}

	void Init( void )
	{
		ZeroMemory( this, sizeof(cltTradeAcuList) );
	}

	bool IsEmpty( void )
	{
		if ( 0 < m_siItemUnique )
		{
			return false;
		}

		if ( 0 < m_siPriceACU )
		{
			return false;
		}

		if ( (0 < m_clDate.uiYear) || (0 < m_clDate.uiMonth) || (0 < m_clDate.uiDay) || (0 < m_clDate.uiHour) )
		{
			return false;
		}

		return true;
	}
};


// Server -> TradeServer
enum {
	NTRADESERVERREQUEST_SET_SELLORDER = 1,		// �ֹ��� �ø���.
	NTRADESERVERRESPONSE_SET_SELLORDER,

	NTRADESERVERREQUEST_CANCEL_SELLORDER,		// �ֹ��� ������.
	NTRADESERVERRESPONSE_CANCEL_SELLORDER,

	NTRADESERVERREQUEST_SET_BUYORDER,			// �ֹ��� ���.
	NTRADESERVERRESPONSE_SET_BUYORDER,

	NTRADESERVERRESPONSE_SET_SELLINFO,			// �ȸ� �ֹ��� ������ �ȸ� ����� �ִ� ������ ������.

	NTRADESERVERREQUEST_DEL_SELLINFO,			// �ȸ� �ֹ��� ������ �����϶� - �������� ó���ߴ�.

	NTRADESERVERREQUEST_GET_LISTINFO,			// ����Ʈ�� ��û�Ѵ�.
	NTRADESERVERRESPONSE_GET_LISTINFO,

	NTRADESERVERREQUEST_DELETE_SELLORDER,		// �ֹ� �ø���� �����ߴµ� �������� ������ ����� ������ ��쿡 ���������� �ö� ���� �����

	//-------------------------------------------------------------------
	// [�����ؿ�] �迵�� 20080918 ����������� �߰� ����
	//-------------------------------------------------------------------
	NTRADESERVERREQUEST_SET_SELLORDER_HOLDACU,	// �ֹ��� �ø���.(�ȸ��ľ�ť�� ���������� ����ȴ�)
												// �������� ������ ���� ����Ѵ�
	// ���������� �ִ� ACU�ޱ�
	NTRADESERVERREQUEST_WITHDRAW_ACU,			// ���������� ����� ��ť ȸ��
	NTRADESERVERRESPONSE_WITHDRAW_ACU,	

	NTRADESERVERREQUEST_WITHDRAW_ACU_SUCCESS,	// ��ť �޾Ҵ�
												// �������� �ʿ����

	NTRADESERVERREQUEST_GET_SAVEDACU_LIST,		// ���������� ����Ǿ��ִ� ACU/��� �ޱ�
	NTRADESERVERRESPONSE_GET_SAVEDACU_LIST,
	//-------------------------------------------------------------------
	// [�����ؿ�] �迵�� 20080918 ����������� �߰� ��
	//-------------------------------------------------------------------

	//-------------------------------------------------------------------
	// [�����ؿ�] �̰��� 20090121 �������� ����
	//-------------------------------------------------------------------
	NTRADESERVERREQUEST_HEARTBEAT,
	NTRADESERVERRESPONSE_HEARTBEAT,

	NTRADESERVERREQUEST_SET_SELLINFO, // �ȸ� �ֹ��� ������ ��û�Ѵ�.

	NTRADESERVERREQUEST_SET_SERVERVERSION, // ������ ������ �����Ѵ�.
	NTRADESERVERRESPONSE_SET_SERVERVERSION, // ������ ������ �����Ѵ�.
	//-------------------------------------------------------------------

	NTRADESERVERMSG_END
};

// TradeServer(GameProtocol) -> TradeServerDB(DBProcess -> DBProtocol)
enum {
	NTRADESERVERDB_REQUEST_SET_SELLORDER = 1,	// �ֹ��� �ø���.
	NTRADESERVERDB_RESPONSE_SET_SELLORDER,

	NTRADESERVERDB_REQUEST_CANCEL_SELLORDER,	// �ֹ��� ������.
	NTRADESERVERDB_RESPONSE_CANCEL_SELLORDER,

	NTRADESERVERDB_REQUEST_SET_BUYORDER,		// �ֹ��� ���.
	NTRADESERVERDB_RESPONSE_SET_BUYORDER,

	NTRADESERVERDB_REQUEST_SET_SELLINFO,
	NTRADESERVERDB_RESPONSE_SET_SELLINFO,		// �ȸ� �ֹ��� ������ �ȸ� ����� �ִ� ������ ������.

	NTRADESERVERDB_REQUEST_DEL_SELLINFO,		// �ȸ� �ֹ��� ������ �����϶� - �������� ó���ߴ�.

	NTRADESERVERDB_REQUEST_GET_LISTINFO,		// ����Ʈ�� ��û�Ѵ�.
	NTRADESERVERDB_RESPONSE_GET_LISTINFO,

	NTRADESERVERDB_REQUEST_REDUCEPRICE,			// ������ ������� ��û�Ѵ�.
	NTRADESERVERDB_RESPONSE_REDUCEPRICE,

	NTRADESERVERDB_REQUEST_DELETE_SELLORDER,	// �ֹ� �ø���� �����ߴµ� �������� ������ ����� ������ ��쿡 ���������� �ö� ���� �����

	//-------------------------------------------------------------------
	// [�����ؿ�] �迵�� 20080918 ����������� �߰� ����
	//-------------------------------------------------------------------
	NTRADESERVERDB_REQUEST_SET_SELLORDER_HOLDACU,// �ֹ��� �ø��� ���ÿ� �̰��� ������ �ȷ��� ��ť�� ���������� �ִ´�

	NTRADESERVERDB_REQUEST_WITHDRAW_ACU,		// ���������� ����� ��ť ȸ��
	NTRADESERVERDB_RESPONSE_WITHDRAW_ACU,

	NTRADESERVERDB_REQUEST_WITHDRAW_ACU_SUCCESS,// ��ť ȸ���� �����Ͽ���
												// �������� ����

	NTRADESERVERDB_REQUEST_SAVEDACU_LIST,		// ���������� ����� ��ť�� �ֱ� �ŷ����� ������ �����´�
	NTRADESERVERDB_RESPONSE_SAVEDACU_LIST,
	//-------------------------------------------------------------------
	// [�����ؿ�] �迵�� 20080918 ����������� �߰� ��
	//-------------------------------------------------------------------

	NTRADESERVERDB_MSG_END
};

//-------------------------------------------------------------
// GameServer <-> TradeServer
//--------------------------------------------------------------

// Ʈ���̵� ������ �ȱ��ֹ��� �ø���.
class NTradeServerRequest_Set_SellOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID; // ĳ���� ID

	SI16				siPos; // �ø� �ֹ��� ��ġ

	cltTradeServerOrder	clOrder; // �ø� �ֹ��� ����

	NTradeServerRequest_Set_SellOrder(SI32 id ,SI16 pos ,cltTradeServerOrder*pclOrder)
	{
		packetHeader.usCmd = NTRADESERVERREQUEST_SET_SELLORDER;
		packetHeader.usSize = sizeof( NTradeServerRequest_Set_SellOrder );

		siCharID = id ;

		siPos = pos ;

		clOrder.Set(pclOrder);
	}
};

class NTradeServerResponse_Set_SellOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID

	SI16				siPos; // �ø� �ֹ��� ��ġ

	cltTradeServerOrder	clOrder; // �ø� �ֹ��� ����

	NTradeServerResponse_Set_SellOrder(SI32 result,SI32 charid,SI16 pos,cltTradeServerOrder*pclOrder)
	{
		packetHeader.usCmd = NTRADESERVERRESPONSE_SET_SELLORDER;
		packetHeader.usSize = sizeof( NTradeServerResponse_Set_SellOrder );

		siResult = result ;

		siCharID = charid ;

		siPos = pos ;

		clOrder.Set(pclOrder);
	}
};
// �ȱ��ֹ��� �Բ� �̰��� �ȷ��� ��ť�� ���� �ʰ� ���������� ����ȴ� 
class NTradeServerRequest_Set_SellOrder_HoldAcu
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;		// ĳ���� ID

	SI16				m_siPos;		// �ø� �ֹ��� ��ġ

	cltTradeServerOrder	m_clOrder;		// �ø� �ֹ��� ����

	bool				m_bHoldAcu;	// ���������� ��ť�� ��������� �����Ѵ�( 1�̻��̸� ���� )

	NTradeServerRequest_Set_SellOrder_HoldAcu( SI32 siCharID, SI16 siPos ,cltTradeServerOrder*pclOrder, bool bHoldAcu )
	{
		m_packetHeader.usCmd	= NTRADESERVERREQUEST_SET_SELLORDER_HOLDACU;
		m_packetHeader.usSize	= sizeof( NTradeServerRequest_Set_SellOrder_HoldAcu );

		m_siCharID				= siCharID;

		m_siPos					= siPos;

		m_clOrder.Set(pclOrder);

		m_bHoldAcu				= bHoldAcu;
	}
};

// Ʈ���̵� ������ �ø� �ֹ��� ����Ѵ�.
class NTradeServerRequest_Cancel_SellOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID; // ĳ���� ID

	cltTradeServerOrder	clOrder; // ����� �ֹ� ����
	SI16				siPos ; // ����� �ֹ��� �� �ڸ�

	//NTradeServerRequest_Cancel_SellOrder(SI32 id,cltTradeServerOrder*pclOrder)
	NTradeServerRequest_Cancel_SellOrder(SI32 id,cltTradeServerOrder*pclOrder,SI16 pos)
	{
		packetHeader.usCmd = NTRADESERVERREQUEST_CANCEL_SELLORDER;
		packetHeader.usSize = sizeof( NTradeServerRequest_Cancel_SellOrder );

		siCharID = id ;

		clOrder.Set(pclOrder);
		siPos = pos ;

	}
};

class NTradeServerResponse_Cancel_SellOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID

	cltTradeServerOrder	clOrder; // ����� �ֹ� ����
	SI16				siPos;

	NTradeServerResponse_Cancel_SellOrder()
	{
		ZeroMemory( this, sizeof( NTradeServerResponse_Cancel_SellOrder ) );
	}
};

// Ʈ���̵� ������ �ö� �ֹ��� ���.
class NTradeServerRequest_Set_BuyOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;			// �� ĳ���� ID
	SI32				siPersonID;			// �� ĳ���� PersonID

	//char				szServerName[20] ;	// �� ĳ���Ͱ� �ִ� ����
	char				szServerNation[4] ;	// �� ĳ���Ͱ� �ִ� ������ ���� �ڵ�
	SI16				siServerIndex;		// �� ĳ������ ���� ��ȣ
	SI16				siCharNation;		// ĳ������ ���� �ڵ�
	char				szCharName[20] ;	// �� ĳ������ �̸�
	char				szAccountID[20] ;	// �� ĳ������ ����

	cltTradeServerOrder	clOrder;			// �ֹ� ����
	SI16				siPos;

	//NTradeServerRequest_Set_BuyOrder(SI32 id,SI32 personid,/*char*server,*/char*name,char*account,
	//	char*servernation,SI16 serverindex,SI16 charnation,
	//	cltTradeServerOrder*pclOrder)
	NTradeServerRequest_Set_BuyOrder(SI32 id,SI32 personid,/*char*server,*/char*name,char*account,
		char*servernation,SI16 serverindex,SI16 charnation,
		cltTradeServerOrder*pclOrder,SI16 pos)
	{
		packetHeader.usCmd = NTRADESERVERREQUEST_SET_BUYORDER;
		packetHeader.usSize = sizeof( NTradeServerRequest_Set_BuyOrder );

		siCharID = id ;
		siPersonID = personid ;

		//memcpy(szServerName,server,20);
		memcpy(szServerNation,servernation,4);
		siServerIndex = serverindex;
		siCharNation = charnation;
		memcpy(szCharName,name,20);
		memcpy(szAccountID,account,20);

		clOrder.Set(pclOrder);
		siPos = pos ;

	}
};

class NTradeServerResponse_Set_BuyOrder
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID
	SI32				siPersonID; // ĳ���� PersonID

	cltTradeServerOrder	clOrder; // �ֹ� ����
	SI16				siPos;


	NTradeServerResponse_Set_BuyOrder()
	{
		ZeroMemory( this, sizeof( NTradeServerResponse_Set_BuyOrder ) );
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20090210 �̰���
//
// �ȸ� �ֹ��� ������ ��û�Ѵ�.
//---------------------------------------------------------------------------
class NTradeServerRequest_Set_SellInfo
{
public:
	sPacketHeader		packetHeader;

	NTradeServerRequest_Set_SellInfo()
	{
		ZeroMemory(this, sizeof(NTradeServerRequest_Set_SellInfo));
		packetHeader.usCmd = NTRADESERVERREQUEST_SET_SELLINFO;
		packetHeader.usSize = sizeof(NTradeServerRequest_Set_SellInfo);
	}
};


// �ȸ� �ֹ��� ������ �ȸ� ����� �ִ� ������ ������.
class NTradeServerResponse_Set_SellInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����

	//char				szBuyerServer[20] ; // �� ����� �ִ� ����
	char				szBuyerServerNation[4] ; // �� ����� ���� ���� �ڵ�
	SI16				siBuyerServerIndex; // �� ����� ���� �ε���
	char				szBuyerName[20] ; // �� ����� �̸�
	char				szBuyerAccountID[20] ; // �� ����� ����
	SI16				siBuyerNation; // �� ����� ���� �ε���

	cltTradeServerOrder	clLeftOrder; // �ȸ��� ���� �ֹ� ����

	NTradeServerResponse_Set_SellInfo()
	{
		ZeroMemory( this, sizeof( NTradeServerResponse_Set_SellInfo ) );
	}
};

// �ȸ� �ֹ��� ����� �޾����� ���� ������� ��û�Ѵ�.
class NTradeServerRequest_Del_SellInfo
{
public:
	sPacketHeader		packetHeader;

	cltTradeServerOrder	clOrder; // �������� �ֹ� ����

	NTradeServerRequest_Del_SellInfo(cltTradeServerOrder*pclorder)
	{
		packetHeader.usCmd = NTRADESERVERREQUEST_DEL_SELLINFO;
		packetHeader.usSize = sizeof( NTradeServerRequest_Del_SellInfo );

		clOrder.Set(pclorder);
	}
};

// �߰� ������ ��ǰ ����Ʈ�� ��û�Ѵ�.
class NTradeServerRequest_Get_ListInfo
{
public:
	sPacketHeader		packetHeader;

	//char				szServerName[20] ; // Server �̸� '����''����'...
	char				szServerNation[4] ; // ���� �ڵ� 'kor','jpn'...
	SI16				siServerIndex;

	NTradeServerRequest_Get_ListInfo(char* servernation,SI16 serverindex)
	{
		packetHeader.usCmd = NTRADESERVERREQUEST_GET_LISTINFO;
		packetHeader.usSize = sizeof( NTradeServerRequest_Get_ListInfo );

		//memcpy(szServerName,server,20);
		memcpy(szServerNation,servernation,4);
		siServerIndex = serverindex ;
	}
};

class NTradeServerResponse_Get_ListInfo
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����
	SI32				siListStartIndex;

	cltTradeServerOrder	clOrder[MAX_TRADESERVER_GET_LIST];

	NTradeServerResponse_Get_ListInfo()
	{
		ZeroMemory( this, sizeof( NTradeServerResponse_Get_ListInfo ) );
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ����� ��ť�� �ֱ� ��ť������ ��û�Ѵ�(������ ������)
//---------------------------------------------------------------------------
class NTradeServerRequest_Get_SavedACU_List
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;
	SI32				m_siPersonID;

	char				m_szServerNation[4]; // ���� �ڵ� 'kor','jpn'...
	SI16				m_siServerIndex;


	NTradeServerRequest_Get_SavedACU_List( SI32 siCharID, SI32 siPersonID, char* szServerNation, SI16 siServerIndex )
	{
		ZeroMemory( this, sizeof(NTradeServerRequest_Get_SavedACU_List) );

		m_packetHeader.usCmd	= NTRADESERVERREQUEST_GET_SAVEDACU_LIST;
		m_packetHeader.usSize	= sizeof( NTradeServerRequest_Get_SavedACU_List );

		m_siCharID				= siCharID;
		m_siPersonID			= siPersonID;

		memcpy( m_szServerNation, szServerNation, 4 );
		m_siServerIndex			= siServerIndex;
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ����� ��ť�� �ֱ� ��ť������ ��û -> ����
//---------------------------------------------------------------------------
class NTradeServerResponse_Get_SavedACU_List
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;

	SI32				m_siCharID;
	SI32				m_siPersonID;

	SI64				m_siSavedACU;							// ����� Acu
	cltTradeAcuList		m_clAcuList[MAX_TRADESERVER_ACU_LIST];	// �ֱ� �ŷ�����


	NTradeServerResponse_Get_SavedACU_List( )
	{
		ZeroMemory( this, sizeof(NTradeServerResponse_Get_SavedACU_List) );
	}
};	// NTRADESERVERRESPONSE_GET_SAVEDACU_LIST

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ���������� ����� ��ť�� �ޱ� ��û
//---------------------------------------------------------------------------
class NTradeServerRequest_Withdraw_Acu
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siCharID;
	SI32				m_siPersonID;

	char				m_szServerNation[4]; // ���� �ڵ� 'kor','jpn'...
	SI16				m_siServerIndex;

	SI64				m_siWithdrawAcu;	// ���� ��ť


	NTradeServerRequest_Withdraw_Acu( SI32 siCharID, SI32 siPersonID, char* szServerNation, SI16 siServerIndex, SI64 siWithdrawAcu )
	{
		ZeroMemory( this, sizeof(NTradeServerRequest_Withdraw_Acu) );

		m_packetHeader.usCmd	= NTRADESERVERREQUEST_WITHDRAW_ACU;
		m_packetHeader.usSize	= sizeof( NTradeServerRequest_Withdraw_Acu );

		m_siCharID				= siCharID;
		m_siPersonID			= siPersonID;

		memcpy( m_szServerNation, szServerNation, 4 );
		m_siServerIndex			= siServerIndex;

		m_siWithdrawAcu			= siWithdrawAcu;
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ���������� ����� ��ť�� �ޱ� ��û -> ����
//---------------------------------------------------------------------------
class NTradeServerResponse_Withdraw_Acu
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;

	SI32				m_siCharID;
	SI32				m_siPersonID;

	SI64				m_siLeftSavedAcu;	// ���������� ����� ��ť
	SI64				m_siWithdrawAcu;	// ���� ��ť

	SI32				m_siReservedNum;	// ���� �޽����� ������ �� ��ȣ�� ��ť�� �����ض�


	NTradeServerResponse_Withdraw_Acu()
	{
		ZeroMemory( this, sizeof(NTradeServerResponse_Withdraw_Acu) );
	}
};	// NTRADESERVERRESPONSE_WITHDRAW_ACU

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ���������� ��ť�� ���������� �޾����� �˷��ش�
//---------------------------------------------------------------------------
class NTradeServerRequest_Withdraw_Acu_Success
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siReservedNum;


	NTradeServerRequest_Withdraw_Acu_Success( SI32 siReservedNum )
	{
		ZeroMemory( this, sizeof(NTradeServerRequest_Withdraw_Acu_Success) );

		m_packetHeader.usCmd	= NTRADESERVERREQUEST_WITHDRAW_ACU_SUCCESS;
		m_packetHeader.usSize	= sizeof( NTradeServerRequest_Withdraw_Acu_Success );

		m_siReservedNum			= siReservedNum;
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20090210 �̰���
//
// HeartBeat ��Ŷ
//---------------------------------------------------------------------------
class NTradeServerRequest_HeartBeat		// ���Ӽ��� -> ��������
{
public:
	sPacketHeader	m_packetHeader;

	NTradeServerRequest_HeartBeat()
	{
		ZeroMemory(this, sizeof(NTradeServerRequest_HeartBeat));
		m_packetHeader.usCmd = NTRADESERVERREQUEST_HEARTBEAT;
		m_packetHeader.usSize = sizeof( NTradeServerRequest_HeartBeat );
	}
};

class NTradeServerResponse_HeartBeat	// �������� -> ���Ӽ���
{
public:
	sPacketHeader		m_packetHeader;

	NTradeServerResponse_HeartBeat()
	{
		ZeroMemory(this, sizeof(NTradeServerResponse_HeartBeat));
		m_packetHeader.usCmd = NTRADESERVERRESPONSE_HEARTBEAT;
		m_packetHeader.usSize = sizeof( NTradeServerResponse_HeartBeat );
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20090210 �̰���
//
// ���� ���� ���� ��Ŷ
//---------------------------------------------------------------------------
class NTradeServerRequest_Set_ServerVersion		// ���Ӽ��� -> ��������
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siVersion;

	NTradeServerRequest_Set_ServerVersion(SI32 siVersion)
	{
		ZeroMemory(this, sizeof(NTradeServerRequest_Set_ServerVersion));
		m_packetHeader.usCmd = NTRADESERVERREQUEST_SET_SERVERVERSION;
		m_packetHeader.usSize = sizeof( NTradeServerRequest_Set_ServerVersion );

		m_siVersion = siVersion;
	}
};

class NTradeServerResponse_Set_ServerVersion	// �������� -> ���Ӽ���
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siVersion;

	NTradeServerResponse_Set_ServerVersion(SI32 siVersion)
	{
		ZeroMemory(this, sizeof(NTradeServerResponse_Set_ServerVersion));
		m_packetHeader.usCmd = NTRADESERVERRESPONSE_SET_SERVERVERSION;
		m_packetHeader.usSize = sizeof( NTradeServerResponse_Set_ServerVersion );

		m_siVersion = siVersion;
	}
};


//-------------------------------------------------------------
// TradeServer <-> TradeServerDB
//--------------------------------------------------------------

// Ʈ���̵� ������ �ȱ��ֹ��� �ø���.
class NTradeServerDB_Request_Set_SellOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siCharID; // ĳ���� ID

	SI16				siPos; // �ø� �ֹ��� ��ġ

	cltTradeServerOrder	clOrder; // �ø� �ֹ��� ����

	NTradeServerDB_Request_Set_SellOrder(UI16 serverid ,SI32 id ,SI16 pos ,cltTradeServerOrder*pclOrder)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_SET_SELLORDER;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_Set_SellOrder );

		uiServerIndex = serverid ;

		siCharID = id ;

		siPos = pos ;

		clOrder.Set(pclOrder);
	}
};

class NTradeServerDB_Response_Set_SellOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID

	SI16				siPos; // �ø� �ֹ��� ��ġ

	cltTradeServerOrder	clOrder; // �ø� �ֹ��� ����

	NTradeServerDB_Response_Set_SellOrder()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_Set_SellOrder ) );
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// �ֹ��� �ø��� ���ÿ� �̰��� �ȷ��� ��ť�� ���������� �׳� ������ �ǹ�
//
// (�������� NTradeServerDB_Response_Set_SellOrder�� ����)
//---------------------------------------------------------------------------
class NTradeServerDB_Request_Set_SellOrder_HoldAcu
{
public:
	sPacketHeader		m_packetHeader;

	UI16				m_uiServerIndex;

	SI32				m_siCharID;			// ĳ���� ID

	SI16				m_siPos;			// �ø� �ֹ��� ��ġ

	cltTradeServerOrder	m_clOrder;			// �ø� �ֹ��� ����

	bool				m_bHodlAcu;			// ���������� ��ť�� ��������� �����Ѵ�( 1�̻��̸� ���� )

	NTradeServerDB_Request_Set_SellOrder_HoldAcu(UI16 siServerID, SI32 siCharID, SI16 siPos, cltTradeServerOrder*pclOrder, bool bHoldAcu)
	{
		m_packetHeader.usCmd	= NTRADESERVERDB_REQUEST_SET_SELLORDER_HOLDACU;
		m_packetHeader.usSize	= sizeof( NTradeServerDB_Request_Set_SellOrder_HoldAcu );

		m_uiServerIndex			= siServerID;

		m_siCharID				= siCharID;

		m_siPos					= siPos;

		m_clOrder.Set(pclOrder);

		m_bHodlAcu				= bHoldAcu;
	}
};

// Ʈ���̵� ������ �ø� �ֹ��� ����Ѵ�.
class NTradeServerDB_Request_Cancel_SellOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siCharID; // ĳ���� ID

	cltTradeServerOrder	clOrder; // ����� �ֹ� ����
	SI16				siPos;

	//NTradeServerDB_Request_Cancel_SellOrder(UI16 serverid ,SI32 id ,cltTradeServerOrder*pclOrder)
	NTradeServerDB_Request_Cancel_SellOrder(UI16 serverid ,SI32 id ,cltTradeServerOrder*pclOrder,SI16 pos)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_CANCEL_SELLORDER;
		packetHeader.usSize = sizeof( NTradeServerRequest_Cancel_SellOrder );

		uiServerIndex = serverid ;

		siCharID = id ;

		clOrder.Set(pclOrder);
		siPos = pos ;

	}
};

class NTradeServerDB_Response_Cancel_SellOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID

	cltTradeServerOrder	clOrder; // ����� �ֹ� ����
	SI16				siPos ;

	NTradeServerDB_Response_Cancel_SellOrder()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_Cancel_SellOrder ) );
	}
};

// Ʈ���̵� ������ �ö� �ֹ��� ���.
class NTradeServerDB_Request_Set_BuyOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siCharID; // �� ĳ���� ID
	SI32				siPersonID; // �� ĳ���� PersonID

	//char				szServerName[20] ; // �� ĳ���Ͱ� �ִ� ����
	char				szServerNation[4] ; // �� ĳ���Ͱ� �ִ� ������ ���� �ڵ�
	SI16				siServerIndex; // �� ĳ������ ���� ��ȣ
	SI16				siCharNation; // ĳ������ ���� �ڵ�
	char				szCharName[20] ; // �� ĳ������ �̸�
	char				szAccountID[20] ; // �� ĳ������ ����

	cltTradeServerOrder	clOrder; // �ֹ� ����
	SI16				siPos;

	//NTradeServerDB_Request_Set_BuyOrder(UI16 serverid ,SI32 id ,SI32 personid,/*char*server,*/char*name,char*account,
	//	char*servernation,SI16 serverindex,SI16 charnation,
	//	cltTradeServerOrder*pclOrder)
	NTradeServerDB_Request_Set_BuyOrder(UI16 serverid ,SI32 id ,SI32 personid,/*char*server,*/char*name,char*account,
		char*servernation,SI16 serverindex,SI16 charnation,
		cltTradeServerOrder*pclOrder,SI16 pos)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_SET_BUYORDER;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_Set_BuyOrder );

		uiServerIndex = serverid ;

		siCharID = id ;
		siPersonID = personid ;

		//memcpy(szServerName,server,20);
		memcpy(szServerNation,servernation,4);
		siServerIndex = serverindex;
		siCharNation = charnation;
		memcpy(szCharName,name,20);
		memcpy(szAccountID,account,20);

		clOrder.Set(pclOrder);
		siPos = pos ;

	}
};

class NTradeServerDB_Response_Set_BuyOrder
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siResult; // 1�ܿ��� ��� ����

	SI32				siCharID; // ĳ���� ID
	SI32				siPersonID; // ĳ���� PersonID

	char				szServerNation[4] ; // �� ĳ���Ͱ� �ִ� ������ ���� �ڵ�
	SI16				siServerIndex; // �� ĳ������ ���� ��ȣ
	char				szCharName[20] ; // �� ĳ������ �̸�

	cltTradeServerOrder	clOrder; // �ֹ� ����
	SI16				siPos;

	NTradeServerDB_Response_Set_BuyOrder()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_Set_BuyOrder ) );
	}
};

class NTradeServerDB_Request_Set_SellInfo // ������ ����Ǿ� �����ϱ� SetSellInfo�� �����϶�
{
public:
	sPacketHeader		packetHeader;

	char				szServerIP[20]; // ����Ǿ� �ִ� ���� IP

	NTradeServerDB_Request_Set_SellInfo(char*ip)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_SET_SELLINFO;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_Set_SellInfo );

		memcpy(szServerIP,ip,20);
	}
};

// �ȸ� �ֹ��� ������ �ȸ� ����� �ִ� ������ ������.
class NTradeServerDB_Response_Set_SellInfo
{
public:
	sPacketHeader		packetHeader;

	char				szServerIP[20]; // �� ����� �ִ� ���� IP

	SI32				siResult; // 1�ܿ��� ��� ����

	//char				szBuyerServer[20] ; // �� ����� �ִ� ����
	char				szBuyerServerNation[4] ; // �� ����� ���� ���� �ڵ�
	SI16				siBuyerServerIndex; // �� ����� ���� �ε���
	char				szBuyerName[20] ; // �� ����� �̸�
	char				szBuyerAccountID[20] ; // �� ����� ����
	SI16				siBuyerNation; // �� ����� ���� �ε���

	cltTradeServerOrder	clLeftOrder; // �� �ֹ��� �� ���� - �Ǹ����� ����(personid,servername��)

	NTradeServerDB_Response_Set_SellInfo()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_Set_SellInfo ) );
	}
};

// �ȸ� �ֹ��� ������ �����϶� - �������� ó���ߴ�.
class NTradeServerDB_Request_Del_SellInfo
{
public:
	sPacketHeader		packetHeader;

	cltTradeServerOrder	clOrder; // ������ �ֹ� ����

	NTradeServerDB_Request_Del_SellInfo(cltTradeServerOrder*pclOrder)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_DEL_SELLINFO;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_Del_SellInfo );

		clOrder.Set(pclOrder);
	}
};

// �߰� ������ ��ǰ ����Ʈ�� ��û�Ѵ�.
class NTradeServerDB_Request_Get_ListInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siListStartIndex; // ����Ʈ ��ŸƮ �ε���

	bool				bDBInit; // ���� ���� ���α׷��� ó���� ��û�ϴ°ų�?

	NTradeServerDB_Request_Get_ListInfo(UI16 serverid ,SI32 index,bool dbinit)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_GET_LISTINFO;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_Get_ListInfo );

		uiServerIndex = serverid ;

		siListStartIndex = index ;

		bDBInit = dbinit;
	}
};

class NTradeServerDB_Response_Get_ListInfo
{
public:
	sPacketHeader		packetHeader;

	UI16				uiServerIndex;

	SI32				siResult; // 1�ܿ��� ��� ����
	SI32				siListStartIndex;

	cltTradeServerOrder	clOrder[MAX_TRADESERVER_GET_LIST];

	bool				bDBInit; // ���� ���� ���α׷��� ó���� ��û�ϴ°ų�?

	NTradeServerDB_Response_Get_ListInfo()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_Get_ListInfo ) );
	}
};

// �߰� ������ ��ǰ�� ������ ������.
class NTradeServerDB_Request_ReducePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siIndex;
	SI64				siPrice;

	cltTradeDate		clDate;
	char				szSellerName[20];
	char				szSellerServerNation[20];
	SI32				siSellerServerIndex;

	SI32				siItemUnique;

	NTradeServerDB_Request_ReducePrice(SI32 index , SI64 price, cltTradeDate*date,char*name,char*server,SI32 serverindex,SI32 itemunique)
	{
		packetHeader.usCmd = NTRADESERVERDB_REQUEST_REDUCEPRICE;
		packetHeader.usSize = sizeof( NTradeServerDB_Request_ReducePrice );

		siIndex = index;
		siPrice = price;

		clDate.Set(date);
		memcpy(szSellerName,name,20);
		memcpy(szSellerServerNation,server,20);
		siSellerServerIndex = serverindex ;

		siItemUnique = itemunique ;
	}
};

class NTradeServerDB_Response_ReducePrice
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult; // 1�ܿ��� ��� ����

	cltTradeServerOrder	clOrder;

	NTradeServerDB_Response_ReducePrice()
	{
		ZeroMemory( this, sizeof( NTradeServerDB_Response_ReducePrice ) );
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ���������� ����� ��ť �ޱ⸦ ��û�Ѵ�
//
// (���� �������� ��ť�� �Ҹ�Ǵ� ���� �ƴϰ� ���߿� Success��Ŷ�� ���޵Ǿ� �Ҹ�ȴ�)
//---------------------------------------------------------------------------
class NTradeServerDB_Request_Withdraw_Acu
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiServerIndex;

	SI32			m_siCharID;
	SI32			m_siPersonID;

	char			m_szServerNation[4];	// �����ڵ�
	SI16			m_siServerIndex;		// ���� �ε���

	SI64			m_siWithdrawAcu;		// ���� ��ť


	NTradeServerDB_Request_Withdraw_Acu( UI16 uiServerIndex, SI32 siCharID, SI32 siPersonID, char* pszServerNation, SI16 siServerIndex, SI64 siWithdrawAcu )
	{
		m_packetHeader.usCmd	= NTRADESERVERDB_REQUEST_WITHDRAW_ACU;
		m_packetHeader.usSize	= sizeof( NTradeServerDB_Request_Withdraw_Acu );

		m_uiServerIndex			= uiServerIndex;

		m_siCharID				= siCharID;
		m_siPersonID			= siPersonID;

		memcpy( m_szServerNation, pszServerNation, 4 );
		m_siServerIndex			= siServerIndex;

		m_siWithdrawAcu			= siWithdrawAcu;
	}
};

class NTradeServerDB_Response_Withdraw_Acu
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiServerIndex;
	SI32			m_siResult;

	SI32			m_siCharID;
	SI32			m_siPersonID;

	SI64			m_siWithdrawAcu;		// ���� ��ť
	SI64			m_siLeftSavedAcu;		// �ް� �� �� ����� ��ť

	SI32			m_siReservedNum;		// �������� �� ��ȣ�� ��ť�� �����ϱ� ���� ����


	NTradeServerDB_Response_Withdraw_Acu()
	{
		ZeroMemory( this, sizeof(NTradeServerDB_Response_Withdraw_Acu) );
	}
};	// NTRADESERVERDB_RESPONSE_WITHDRAW_ACU

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ��ť �ޱ⸦ ���� �˸�
//
// (������ �ޱ� ����� �ִ� ��ť�� �����Ѵ�)
//---------------------------------------------------------------------------
class NTradeServerDB_Request_Withdraw_Acu_Success
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siReservedNum;

	NTradeServerDB_Request_Withdraw_Acu_Success( SI32 siReservedNum )
	{
		m_packetHeader.usCmd	= NTRADESERVERDB_REQUEST_WITHDRAW_ACU_SUCCESS;
		m_packetHeader.usSize	= sizeof( NTradeServerDB_Request_Withdraw_Acu_Success );

		m_siReservedNum			= siReservedNum;
	}
};

//---------------------------------------------------------------------------
// [�����ؿ�] 20080918 �迵��
//
// ���������� ����� ACU�� �ֽ� �ŷ����� ������ ��û�Ѵ�
//---------------------------------------------------------------------------
class NTradeServerDB_Request_SavedAcu_List
{
public:
	sPacketHeader	m_packetHeader;

	UI16			m_uiServerIndex;

	SI32			m_siCharID;
	SI32			m_siPersonID;

	char			m_szServerNation[4];	// �����ڵ�
	SI16			m_siServerIndex;		// ���� �ε���


	NTradeServerDB_Request_SavedAcu_List( UI16 uiServerIndex, SI32 siCharID, SI32 siPersonID, char* pszServerNation, SI16 siServerIndex )
	{
		m_packetHeader.usCmd	= NTRADESERVERDB_REQUEST_SAVEDACU_LIST;
		m_packetHeader.usSize	= sizeof( NTradeServerDB_Request_SavedAcu_List );

		m_uiServerIndex			= uiServerIndex;

		m_siCharID				= siCharID;
		m_siPersonID			= siPersonID;

		memcpy( m_szServerNation, pszServerNation, 4 );
		m_siServerIndex			= siServerIndex;
	}
};

class NTradeServerDB_Response_SavedAcu_List
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;
	UI16			m_uiServerIndex;

	SI32			m_siCharID;
	SI32			m_siPersonID;

	SI64			m_siSavedAcu;
	cltTradeAcuList	m_clAcuList[MAX_TRADESERVER_ACU_LIST];	// �ֱ� �ŷ�����


	NTradeServerDB_Response_SavedAcu_List( )
	{
		ZeroMemory( this, sizeof(NTradeServerDB_Response_SavedAcu_List) );
	}
};	// NTRADESERVERDB_RESPONSE_SAVEDACU_LIST


#endif