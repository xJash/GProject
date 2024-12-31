#ifndef _DBMSG_TRADEMERCHANT_H_
#define  _DBMSG_TRADEMERCHANT_H_

#include "DBMsg.h"
// ��������

// � ���������� �����ҷ��� ���� ����( DB �� ������ Insert, ������ Update )
class sDBRequest_TradeMerchantSet
{
public:
	sPacketHeader		packetHeader;
	
	SI32 siTradeMerchantKind;	// ���� ���� NPC ����
	
	GMONEY siBuyTotalMoney;		// �� ���� ����
	
	SI16 siBuyItemUnique;		// �����ϴ� ������
	GMONEY siBuyItemPrice;		// �����ϴ� ������ ����

	sDBRequest_TradeMerchantSet( SI32 TradeMerchantKind, GMONEY BuyTotalMoney,
		SI16 BuyItemUnique, GMONEY BuyItemPrice )
	{
		packetHeader.usCmd = DBMSG_REQUEST_TRADEMERCHANTSET;
		packetHeader.usSize = sizeof( sDBRequest_TradeMerchantSet );

		siTradeMerchantKind = TradeMerchantKind;
		siBuyTotalMoney = BuyTotalMoney;

		siBuyItemUnique = BuyItemUnique;
		siBuyItemPrice = BuyItemPrice;
	}
};

class sDBResponse_TradeMerchantSet
{
public:
	sPacketHeader		packetHeader;

	SI32 siResult;				// 1 ����
	
	SI32 siTradeMerchantKind;	// ���� ���� NPC ����
	
	GMONEY siBuyTotalMoney;		// �� ���� ����
	
	SI16 siBuyItemUnique;		// �����ϴ� ������
	GMONEY siBuyItemPrice;		// �����ϴ� ������ ����
	
	sDBResponse_TradeMerchantSet()
	{
		memset( this, 0, sizeof( sDBResponse_TradeMerchantSet ) );
	}
};

// ������ ���� ���ο��� ������ �Ǹ��Ѵ�.
class sDBRequest_TradeMerchantBuyItemFromPerson
{
public:
	sPacketHeader		packetHeader;

	SI32 siCharID;
	SI32 siPersonID;
	
	SI32 siTradeMerchantKind;		// ���� ���� NPC ����

	SI16 siItemPos;					// ������ ��ġ
	cltItem clItem;					// ������ 
	
	GMONEY siIncreaseMoney;			// ������ ���� - siBuyTotalMoney ���� �� �׼� ��ŭ �� ��� ��.
	GMONEY siTradeTax;				// �ս��ڱ����� ���� ���� - siBuyTotalMoney���� �� ��� ��.
		
	sDBRequest_TradeMerchantBuyItemFromPerson( SI32 CharID, SI32 PersonID , SI32 TradeMerchantKind, SI16 ItemPos, cltItem *pclItem, GMONEY IncreaseMoney,GMONEY TradeTax )
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeMerchantBuyItemFromPerson );
		packetHeader.usCmd	= DBMSG_REQUEST_TRADEMERCHANTBUYITEMFROMPERSON;

		siCharID = CharID;
		siPersonID = PersonID;

		siTradeMerchantKind = TradeMerchantKind;

		siItemPos = ItemPos;
		clItem.Set( pclItem );

		siIncreaseMoney = IncreaseMoney;
		siTradeTax		= TradeTax ;
	}
};


class sDBResponse_TradeMerchantBuyItemFromPerson
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;					// 1 ����, -2 : NPC �����Ҽ� �ִ� �� ���� ���� ����
	
	SI32 siCharID;
	SI32 siPersonID;

	SI32 siTradeMerchantKind;		// ���� ���� NPC ����

	SI16 siItemPos;					// ������ ��ġ
	cltItem clItem;					// ���� ������ ����

	GMONEY siIncreateMoney;			// �߰��� �� ( ������ �״�� �־��ָ� �� ) - ���� siBuyTotalMoney �� ��Ƴ����� ��.
	GMONEY siTradeTax;				// �ս��ڱ����� ���� ����
	GMONEY siLeftMoney;				// �߰��ϰ� ���� ��

	GMONEY siLeftBuyTotalMoney;		// NPC �� ������ �����Ҽ� �ִ� ���� ���� ����

	sDBResponse_TradeMerchantBuyItemFromPerson()
	{
		memset( this, 0, sizeof( sDBResponse_TradeMerchantBuyItemFromPerson ) );
	}
};


// ������ ���� ����
class sDBRequest_TradeMerchantBuyHorseFromPerson
{
public:
	sPacketHeader		packetHeader;

	SI32 siCharID;
	SI32 siPersonID;
	
	SI32 siTradeMerchantKind;		// ���� NPC ���� ( DB ������ ���� ���� �׳� ���� �ָ� �� )

	SI16 siPersonHorseIndex;		// ������ ���� index

	GMONEY siIncreaseMoney;			// �� ����
		
	sDBRequest_TradeMerchantBuyHorseFromPerson( SI32 CharID, SI32 PersonID,
		SI32 TradeMerchantKind, SI16 PersonHorseIndex,
		GMONEY IncreaseMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeMerchantBuyHorseFromPerson );
		packetHeader.usCmd	= DBMSG_REQUEST_TRADEMERCHANTBUYHORSEFROMPERSON;

		siCharID = CharID;
		siPersonID = PersonID;

		siTradeMerchantKind = TradeMerchantKind;

		siPersonHorseIndex = PersonHorseIndex;

		siIncreaseMoney = IncreaseMoney;
	}
};


class sDBResponse_TradeMerchantBuyHorseFromPerson
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;					// 1 ����, -2 : NPC �����Ҽ� �ִ� �� ���� ���� ����
	
	SI32 siCharID;
	SI32 siPersonID;

	SI32 siTradeMerchantKind;		// ���� NPC ����

	SI16 siPersonHorseIndex;		// �ȸ� ���� index

	GMONEY siIncreaseMoney;			// �߰��� �� ( ������ �״�� �־��ָ� �� )
	GMONEY siLeftMoney;				// �߰��ϰ� ���� ��	

	sDBResponse_TradeMerchantBuyHorseFromPerson()
	{
		memset( this, 0, sizeof( sDBResponse_TradeMerchantBuyHorseFromPerson ) );
	}
};


// ������ �������� ����
class sDBRequest_TradeMerchantBuyItem
{
public:
	sPacketHeader		packetHeader;

	SI32 siCharID;
	SI32 siPersonID;
	
	SI32 siTradeMerchantKind;		// NPC ���� ( DB ������ ���� ���� �׳� ���� �ָ� �� )

	SI16 siItemPos;
	cltItem clItem;					// ������ �����ϴ� �������� ����

	GMONEY siIncreaseMoney;			// �� ����
		
	sDBRequest_TradeMerchantBuyItem( SI32 CharID, SI32 PersonID,
		SI32 TradeMerchantKind,
		SI16 ItemPos, cltItem *pclItem,
		GMONEY IncreaseMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_TradeMerchantBuyItem );
		packetHeader.usCmd	= DBMSG_REQUEST_TRADEMERCHANTBUYITEM;

		siCharID = CharID;
		siPersonID = PersonID;

		siItemPos = ItemPos;
		clItem.Set( pclItem );

		siTradeMerchantKind = TradeMerchantKind;

		siIncreaseMoney = IncreaseMoney;
	}
};


class sDBResponse_TradeMerchantBuyItem
{
public:
	sPacketHeader packetHeader;

	SI32 siResult;					// 1 ����, -2 : NPC �����Ҽ� �ִ� �� ���� ���� ����
	
	SI32 siCharID;
	SI32 siPersonID;

	SI32 siTradeMerchantKind;		// ���� NPC ����
	
	SI16 siItemPos;					// ������ ��ġ
	SI16 siBuyItemUnique;			// ������ ������ �������� Item Unique
	SI16 siBuyItemNum;				// ������ ������ �������� ����
	cltItem clLeftItem;				// ������ �����ϰ� ���� ������ ������ ����

	GMONEY siIncreaseMoney;			// �߰��� �� ( ������ �״�� �־��ָ� �� )
	GMONEY siLeftMoney;				// �߰��ϰ� ���� ��	

	sDBResponse_TradeMerchantBuyItem()
	{
		memset( this, 0, sizeof( sDBResponse_TradeMerchantBuyItem ) );
	}
};

#endif