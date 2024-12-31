#ifndef _DBMSGSTRUCTURE_H
#define _DBMSGSTRUCTURE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\GoonZuWorld\CommonLogic\Cityhall\Cityhall.h"
#include "..\..\GoonZuWorld\CommonLogic\House\House.h"
#include "..\..\GoonZuWorld\CommonLogic\Bank\Bank.h"
#include "DBMsg.h"

#include "../../GoonZuWorld/Server/Event/ContributionEvent_Common/ContributionEvent_Common.h"


#define CHANGESTRMONEY_NORMAL					0
#define CHANGESTRMONEY_CITYHALL_PROFIT			1
#define CHANGESTRMONEY_NPCPAY					2	// NPC �� �޿��� �����Ѵ�.
#define CHANGESTRMONEY_EVENTPAY					3	// ���� �̺�Ʈ ���
#define CHANGESTRMONEY_HUNT						4	// ������ �̿뿡 ���� ��� ����. 
#define CHANGESTRMONEY_VILLAGEMARK				5   // VillageMark����
#define CHANGESTRMONEY_VILLAGEMAP				6	// VillageMap����
#define CHANGESTRMONEY_INSTANCEPROFIT			7	// �ν��Ͻ� ���� ���ͱ�
#define CHANGESTRMONEY_DESTORYSTR				8	// �ǹ� ������ �Ҹ�� ����
#define CHANGESTRMONEY_VILLAGEWAR				9	// ���� ������ �¸� Ȥ�� �й�� ���� ����
#define CHANGESTRMONEY_DONATEMONEY				10	// ��α����� ���� ���ͱ��� ���Ѵ�

//---------------------------------------------
// �ǹ��� ���� �ڱ��� ���� ��Ű�ų� ���� ��Ų��
//---------------------------------------------
class sDBRequest_ChangeStrMoney
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siReason;					// DB�Ŵ��������� �̰��� �޾Ƽ� Response�� �״�� �������ָ� �ȴ� 
	LPARAM				lParam;						// DB�Ŵ��������� �̰��� �޾Ƽ� Response�� �״�� �������ָ� �ȴ� 

	SI32				siVillageUnique;			// ���� 

	SI32				siStrType;					// �ǹ� ����
	GMONEY				siMoney;					// �ǹ� �����ڱݿ��� �� �ϰų� �� �ݾ� 

	sDBRequest_ChangeStrMoney()
	{
		Init();
	}

	sDBRequest_ChangeStrMoney( SI32 reason, LPARAM lparam, SI32 villageUnique, SI32 strType, GMONEY money ) {

		Set( reason, lparam, villageUnique, strType, money );
	}

	void				Init()
	{
		ZeroMemory( this, sizeof( sDBRequest_ChangeStrMoney ) );
	}

	void				Set( SI32 reason, LPARAM lparam, SI32 villageUnique, SI32 strType, GMONEY money ) 
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeStrMoney );
		packetHeader.usCmd = DBMSG_REQUEST_CHANGESTRMONEY;

		siReason = reason;
		lParam = lparam;
		siVillageUnique = villageUnique;
		siStrType = strType;
		siMoney = money;
	}

};

class sDBResponse_ChangeStrMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// ����:1, ����:0, �����ڱݺ���:2

	SI32				siReason;
	LPARAM				lParam;

	SI32				siVillageUnique;

	SI32				siStrType;					// �ǹ� ����
	cltMoney			clMoney;					// �ǹ� �����ڱ� 
	
	GMONEY				siChangeMoney;				// ���� �ݾ�

	sDBResponse_ChangeStrMoney() {
		ZeroMemory( this, sizeof( sDBResponse_ChangeStrMoney ) );
	}
};

//---------------------------------------------
// ��� �ǹ��� ���ͱ��� ���� ��Ű�ų� ���� ��Ų��
//---------------------------------------------
class sDBRequest_ChangeCityhallProfitMoney
{
public:
	sPacketHeader		packetHeader;
	
	SI32				siReason;					// DB�Ŵ��������� �̰��� �޾Ƽ� Response�� �״�� �������ָ� �ȴ� 
	LPARAM				lParam;						// DB�Ŵ��������� �̰��� �޾Ƽ� Response�� �״�� �������ָ� �ȴ� 

	SI32				siVillageUnique;			// ���� 
	GMONEY				siMoney;					// ��� ���ͱݿ��� �� �ϰų� �� �ݾ� 

	sDBRequest_ChangeCityhallProfitMoney()
	{
		ZeroMemory( this, sizeof( sDBRequest_ChangeCityhallProfitMoney ) );
	}

	sDBRequest_ChangeCityhallProfitMoney( SI32 reason, LPARAM lparam, SI32 villageunique, GMONEY money )
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeCityhallProfitMoney );
		packetHeader.usCmd = DBMSG_REQUEST_CHANGECITYHALLPROFITMONEY;

		siReason = reason;
		lParam = lparam;
		siVillageUnique = villageunique;
		siMoney = money;
	}

};

class sDBResponse_ChangeCityhallProfitMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// ����:1, ����:0, �����ڱݺ���:2

	SI32				siReason;
	LPARAM				lParam;

	SI32				siVillageUnique;
	cltMoney			clMoney;					// ��� ���ͱ�
	
	GMONEY				siChangeMoney;				// ���� �ݾ�

	sDBResponse_ChangeCityhallProfitMoney() {
		ZeroMemory( this, sizeof( sDBResponse_ChangeCityhallProfitMoney ) );
	}
};


//------------------------------------------
// �ǹ� ������ ������ ���� ��û
//------------------------------------------
class sDBRequest_SetStrInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;	// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;			// �ǹ��� ����.

	//----------------------------
	// �� �������� ������ �Ѵ�. ����� �������̹Ƿ�. 
	//----------------------------
	cltStrInfo			clStrInfo;			// �����ؾ� �� �ǹ��� ����. 

	sDBRequest_SetStrInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetStrInfo));
	}

	sDBRequest_SetStrInfo(SI32 id, SI32 villageunique, SI32 strtype, cltStrInfo* pclinfo)
	{
		packetHeader.usSize = sizeof( sDBRequest_SetStrInfo );
		packetHeader.usCmd = DBMSG_REQUEST_SETSTRINFO;
		usCharID		= id;

		siVillageUnique	= villageunique;
		siStrType		= strtype;

		clStrInfo.Set(pclinfo);
	}
};


class sDBResponse_SetStrInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siVillageUnique;	// �ǹ��� ��ġ�� ������ VillageUnique

	//----------------------------
	// �� �������� ������ �Ѵ�. ����� �������̹Ƿ�. 
	//----------------------------
	cltStrInfo			clStrInfo;			// ������ �� �ǹ��� ����. 

	sDBResponse_SetStrInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetStrInfo));
	}
	// �� �޽����� ��ȿ�� ����� ���Ѵ�. 
	SI32 GetTotalSize()
	{
		return sizeof(sDBResponse_SetStrInfo) - sizeof(cltStrInfo) + clStrInfo.GetTotalSize();
	}
	
};


//------------------------------------------
// �ǹ� ������ ������ ���� ��û
//------------------------------------------
class sDBRequest_GetStrInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	sDBRequest_GetStrInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_GetStrInfo));
	}

	sDBRequest_GetStrInfo(SI32 id, SI32 villageunique, SI32 strtype)
	{
		packetHeader.usSize = sizeof( sDBRequest_GetStrInfo );
		packetHeader.usCmd = DBMSG_REQUEST_GETSTRINFO;
		usCharID		= id;

		siVillageUnique	= villageunique;
		siStrType		= strtype;
	}
};


class sDBResponse_GetStrInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;			// �����.
	SI32				siVillageUnique;	// �ǹ��� ��ġ�� ������ VillageUnique

	//----------------------------
	// �� �������� ������ �Ѵ�. ����� �������̹Ƿ�. 
	//----------------------------
	cltStrInfo			clStrInfo;			// �ǹ��� ����. 

	sDBResponse_GetStrInfo()
	{
		ZeroMemory(this, sizeof(sDBResponse_GetStrInfo));
	}
	// �� �޽����� ��ȿ�� ����� ���Ѵ�. 
	SI32 GetTotalSize()
	{
		return sizeof(sDBResponse_GetStrInfo) - sizeof(cltStrInfo) + clStrInfo.GetTotalSize();
	}
};

//------------------------------------------
// ���� ���� ��û 
//------------------------------------------
class sDBRequest_SetTax
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	UI16				usYear;
	cltMoney			clDueTax;

	sDBRequest_SetTax()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetTax));
	}

	sDBRequest_SetTax(SI32 id, SI32 villageunique, SI32 strtype, UI16 year, cltMoney *pclMoney )
	{
		packetHeader.usSize = sizeof( sDBRequest_SetTax );
		packetHeader.usCmd = DBMSG_REQUEST_SETTAX;
		usCharID		= id;

		siVillageUnique	= villageunique;
		siStrType		= strtype;

		usYear = year;
		clDueTax.Set( pclMoney );
	}
};

//------------------------------------------
// ���� ���� ����
//------------------------------------------
class sDBResponse_SetTax
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	
	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	UI16				usYear;
	cltMoney			clDueTax;
	
	sDBResponse_SetTax()
	{
		ZeroMemory(this, sizeof(sDBResponse_SetTax));
	}

};

//------------------------------------------
// ���� ���� ��û 
//------------------------------------------
class sDBRequest_PayTax
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	cltMoney			clPayTax;					// ���� ���ݾ�
	GMONEY				siChiefPay;					// ��� �޿�

	UI16				usYear;						// ���� ���� �⵵
	cltDate				clDate;						// �ֱ� ���� ������

	sDBRequest_PayTax()
	{
		ZeroMemory(this, sizeof(sDBRequest_PayTax));
	}

	sDBRequest_PayTax( SI32 id, SI32 villageunique, SI32 strtype, cltMoney *pclMoney, GMONEY sichiefpay, UI16 year, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_PayTax );
		packetHeader.usCmd = DBMSG_REQUEST_PAYTAX;
		usCharID		= id;

		siVillageUnique	= villageunique;
		siStrType		= strtype;

		clPayTax.Set( pclMoney );		
		siChiefPay = sichiefpay;

		usYear			= year;
		clDate.Set( pclDate );
	}

};

//------------------------------------------
// ���� ���� ����
//------------------------------------------
class sDBResponse_PayTax
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;			// �ǹ��� ��ġ�� ���� VillageUnique
	SI32				siStrType;					// �ǹ��� Ÿ��. 

	cltMoney			clPaidTax;					// ���� ���ݾ�
	GMONEY				siChiefPay;					// ��� �޿� 

	UI16				usYear;						// ���� �⵵
	cltDate				clDate;						// �ֱ� ���� ������
	
	cltMoney			clStructureMoney;			// ���� �� �ǹ��� �����ڱ�
	cltMoney			clCityhallMoney;			// ���� �� ����� �����ڱ�(���ͱ�)
	GMONEY				siPersonMoney;				// ���� �� ��� ������

	sDBResponse_PayTax()
	{
		ZeroMemory(this, sizeof(sDBResponse_PayTax));
	}
	
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_AutoPayDividend
//
// Last Modified 	: 2006 / 02 / 16
// Created		 	: �豤��
//
// Function			: [��û]�ڵ�����ϱ�
//
//***************************************************************************************************
class sDBRequest_AutoPayDividend
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	SI32				siVillageUnique;			// VillageUnique

	cltMoney			clStockDividend;			// ���ֵ鿡�� ���Ǵ� �ݾ�
	cltMoney			clResidentDividend;			// �ֹε鿡�� ���Ǵ� �ݾ�
	cltMoney			clTaxlDividend;				// �������� �ս� �ڱ����� ���� �ݾ�
	GMONEY				siChiefPay;					// ����� �޿� 
	GMONEY				siKingPay;					// ����(��) �޿�
	SI32				siKingPayPersent;			// ����(��) �޿� ���� 

	UI16				usYear;						// ���⵵
	cltDate				clDate;						// �ֱ� �����

	sDBRequest_AutoPayDividend( SI32 id, SI32 villageUnique, cltMoney *pStockDividend, cltMoney *pResidentDividend,
		cltMoney *pTaxlDividend, GMONEY sichiefpay, GMONEY kingPay, SI32 kingPayPersent,
		UI16 year, cltDate *pclDate )
	{
		packetHeader.usSize = sizeof( sDBRequest_AutoPayDividend );
		packetHeader.usCmd = DBMSG_REQUEST_AUTOPAYDIVIDEND;
		usCharID		= id;

		siVillageUnique	= villageUnique;

		clStockDividend.Set( pStockDividend );
		clResidentDividend.Set( pResidentDividend );
		clTaxlDividend.Set( pTaxlDividend );
		siChiefPay = sichiefpay;
		siKingPay = kingPay;
		siKingPayPersent = kingPayPersent;

		usYear = year;
		clDate.Set( pclDate );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_AutoPayDividend
//
// Last Modified 	: 2006 / 02 / 16
// Created		 	: �豤��
//
// Function			: [����]�ڵ�����ϱ�
//
//***************************************************************************************************
class sDBResponse_AutoPayDividend
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;									// ���: 1���� 0����  -1�����ڱ� ���� 

	SI32				siVillageUnique;							// ��� ����

	SI32				siTotalStock;								// �� ��� �ֽļ� 
	cltMoney			clStockDividendPrice;						// ���ִ� ���� 
	cltMoney			clResidentDividendPrice;					// �ֹ� �Ѹ�� ������ �ݾ� 
	cltMoney			clTaxDividendPrice;							// �ս� �������� ������ �ݾ�

	GMONEY				siChiefPay;									// ����� �޿�

	SI32				siKingPersonID;								// ����(��) Person ID
	GMONEY				siKingPay;									// ����(��) �޿� 
	SI32				siKingPayPersent;							// ����(��) �޿� ����

	UI16				usYear;										// ���⵵ 
	cltDate				clDate;										// �ֱ� ����� 

	cltMoney			clCityhallMoney;							// ����� ��ܺ��� ���ͱ� 
	GMONEY				siPersonMoney;								// ����� ����� ������

	UI16				usStockPersonCount;										// �ֽ� ���޴� ���� ��
	cltDividendPerson	clStockDividendPerson[ MAX_DIVIDEND_PERSON ];		// �ֽ� ���޴� ���� ���� 

	UI16				usResidentPersonCount;										// �ֹ� ���޴� ���� ��
	cltDividendPerson	clResidentDividendPerson[ MAX_DIVIDEND_PERSON ];	// �ֹ� ���޴� ���� ���� 

	//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
	GMONEY			clKingAllMoney;					// ������ ������ ������ �� ����ݾ�.


	sDBResponse_AutoPayDividend()
	{
		usCharID = 0;

		siResult = 0;
		siVillageUnique = 0;

		siTotalStock = 0;
		clStockDividendPrice.Init();
		clResidentDividendPrice.Init();
		clTaxDividendPrice.Init();

		siChiefPay = 0;

		siKingPersonID = 0;
		siKingPay = 0;
		siKingPayPersent = 0;

		usYear = 0;

		clCityhallMoney.Init();
		siPersonMoney = 0;

		usStockPersonCount = 0;
		usResidentPersonCount = 0;

	}

};


//------------------------------------------
// ����� ��û�Ѵ� 
//------------------------------------------
class sDBRequest_PayDividend
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;	

	SI32				siVillageUnique;			// VillageUnique
	
	cltMoney			clTotalDividend;			// �� ���ݾ�
	GMONEY				siChiefPay;					// ����� �޿� 

	UI16				usYear;						// ���⵵
	cltDate				clDate;						// �ֱ� �����
	
	SI32				siParentVillage;			// �θ���
	GMONEY				siParentPay;				// �θ����� ���� ���� 
	
	GMONEY				siKingPay;					// ����(��) �޿�
	SI32				siKingPayPersent;			// ����(��) �޿� ���� 

	sDBRequest_PayDividend( SI32 id, SI32 villageUnique, cltMoney *pclMoney, GMONEY sichiefpay, UI16 year, cltDate *pclDate,
		SI32 parentVillage, GMONEY parentPay, GMONEY kingPay, SI32 kingPayPersent )
	{

		packetHeader.usSize = sizeof( sDBRequest_PayDividend );
		packetHeader.usCmd = DBMSG_REQUEST_PAYDIVIDEND;
		usCharID		= id;

		siVillageUnique	= villageUnique;

		clTotalDividend.Set( pclMoney );
		siChiefPay = sichiefpay;

		usYear = year;
		clDate.Set( pclDate );

		siParentVillage = parentVillage;
		siParentPay = parentPay;

		siKingPay = kingPay;
		siKingPayPersent = kingPayPersent;
	}

};


//------------------------------------------
// ��� ��û�� �����Ѵ�
//------------------------------------------
class sDBResponse_PayDividend
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;									// ���: 1���� 0����  -1�����ڱ� ���� 

	SI32				siVillageUnique;							// ��� ����

	SI32				siTotalStock;								// �� ��� �ֽļ� 
	cltMoney			clDividendPrice;							// ���ִ� ���� 

	GMONEY				siChiefPay;									// ����� �޿�
	
	SI32				siKingPersonID;								// ����(��) Person ID
	GMONEY				siKingPay;									// ����(��) �޿� 
	SI32				siKingPayPersent;							// ����(��) �޿� ����

	SI32				siParentVillage;							// �θ� ����
	GMONEY				siParentPay;								// �θ� �������� ���� ����

	cltMoney			clParentCityhallMoney;						// �θ��� ��� �����ڱ�


	UI16				usYear;										// ���⵵ 
	cltDate				clDate;										// �ֱ� ����� 
	
	cltMoney			clCityhallMoney;							// ����� ��ܺ����ڱ� 
	GMONEY				siPersonMoney;								// ����� ����� ������
	
	UI16				usPersonCount;								// ���޴� ���� ��
	cltDividendPerson	clDividendPerson[ MAX_DIVIDEND_PERSON ];	// ���޴� ���� ���� 

	sDBResponse_PayDividend()
	{
		ZeroMemory(this, sizeof(sDBResponse_PayDividend));
	}

};

class sDBRequest_SetStructureMessage
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;
	SI32				siStrType;

	TCHAR				szMessage[ 256 ];

	sDBRequest_SetStructureMessage( SI32 villageUnique, SI32 strType, TCHAR *msg )
	{

		packetHeader.usSize = sizeof( sDBRequest_SetStructureMessage );
		packetHeader.usCmd = DBMSG_REQUEST_SETSTRUCTUREMESSAGE;

		siVillageUnique = villageUnique;
		siStrType = strType;

		memcpy( szMessage, msg, 256 );
		szMessage[ 255 ] = NULL;
	}

};

#define BUILD_BY_PERSON 0
#define BUILD_BY_MASTER 1

class sDBRequest_BuildStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;					// ���� 
	SI32				siSlot;								// ����
	SI32				siStructure;						// �Ǽ� �ǹ� unique
	GMONEY				siCost;								// �Ǽ� ���
	SI32				siType;
	SI32				siNeedVillageScore;					// �ʿ��� ���� ����.

	sDBRequest_BuildStructure( UI16 id, SI32 villageUnique, SI32 slot, SI32 structure, GMONEY cost, SI32 Type, SI32		NeedVillageScore )
	{
		packetHeader.usCmd = DBMSG_REQUEST_BUILDSTRUCTURE;
		packetHeader.usSize = sizeof( sDBRequest_BuildStructure );

		usCharID = id;
		siVillageUnique = villageUnique;
		siSlot = slot;
		siStructure = structure;
		siCost = cost;
		siType = Type;
		siNeedVillageScore = NeedVillageScore;
	}

};

class sDBResponse_BuildStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;
	SI32				siSlot;
	SI32				siStructure;
	GMONEY				siCost;

	cltMoney			clCityhallMoney;
	SI32				siType;
	SI32				siNeedVillageScore;					// �ʿ��� ���� ����.


	sDBResponse_BuildStructure()
	{
		ZeroMemory( this, sizeof( sDBResponse_BuildStructure ) );
	}

};

class sDBRequest_DestroyStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;					// ���� 
	SI32				siSlot;								// ����
	SI32				siStructure;						// �ǹ� unique
	SI32				siRankType;							// ��� Ÿ��
	
	SI32				siLastDestroyDateVary;				// �ǹ��� ��ü�� ������ �ð�. 
	

	sDBRequest_DestroyStructure( UI16 id, SI32 villageUnique, SI32 slot, SI32 structure, SI32 ranktype, SI32 destroydate )
	{
		packetHeader.usCmd = DBMSG_REQUEST_DESTROYSTRUCTURE;
		packetHeader.usSize = sizeof( sDBRequest_DestroyStructure );

		usCharID = id;
		siVillageUnique = villageUnique;
		siSlot = slot;
		siStructure = structure;
		siRankType = ranktype;

		siLastDestroyDateVary	= destroydate;
	}


};

class sDBResponse_DestroyStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;
	
	SI32				siResult;

	SI32				siVillageUnique;					// ����
	SI32				siSlot;								// ����
	SI32				siStructure;						// �ǹ� unique
	SI32				siRankType;							// ��� Ÿ��

	SI32				siChiefPersonID;					// �ǹ� ��� person id

	SI32				siLastDestroyDateVary;				// �ǹ��� ��ü�� ������ �ð�. 

	sDBResponse_DestroyStructure()
	{
		ZeroMemory( this, sizeof( sDBResponse_DestroyStructure ) );
	}

};


//-----------------------------------------
// 
//-----------------------------------------
class sDBRequest_ChiefInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siPersonID;			// �ǹ� ��� person id

	cltSimpleRank		SimpleRank;

	sDBRequest_ChiefInfo( UI16 id, SI32 personid, cltSimpleRank* pRank )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CHIEFINFO;
		packetHeader.usSize = sizeof( sDBRequest_ChiefInfo );

		usCharID = id;
		siPersonID = personid;

		SimpleRank.Set(pRank);
	}


};

class sDBResponse_ChiefInfo
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;
	
	SI32				siPersonID;			// �ǹ� ��� person id
	cltRank				Rank;
	
	TCHAR				AccountID[MAX_PLAYER_NAME];

	sDBResponse_ChiefInfo()
	{
		ZeroMemory( this, sizeof( sDBResponse_ChiefInfo ) );
	}


};

/*
class sDBRequest_RepairStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siPersonID;												// personid

	SI16				siItemInventoryIndex;									// item index
	SI32				siItemUnique;											// item unique
	SI16				siItemNum;												// item num

	sDBRequest_RepairStructure( UI16 id, SI32 villageUnique, SI32 ranktype, SI32 personid,
		SI16 itemInventoryIndex, SI32 itemUnique, SI16 itemNum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_REPAIRSTRUCTURE;
		packetHeader.usSize = sizeof( sDBRequest_RepairStructure );
		usCharID = id;

		siVillageUnique = villageUnique;
		siRankType = ranktype;

		siPersonID = personid;

		siItemInventoryIndex = itemInventoryIndex;
		siItemUnique = itemUnique;
		siItemNum = itemNum;
	}

};

class sDBResponse_RepairStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI16				siUseItemNum;											// ����� ������ ���� 

	SI32				siPersonID;

	SI16				siItemInventoryIndex;									// item index
	SI32				siItemUnique;											// item unique
	SI16				siItemNum;												// item num


	sDBResponse_RepairStructure()
	{
		ZeroMemory( this, sizeof( sDBResponse_RepairStructure ) );
	}

};
*/

class sDBRequest_SetStrRepairItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siItemUnique;
	SI16				siItemNum;

	sDBRequest_SetStrRepairItem( SI32 villageunique, SI32 ranktype, SI32 itemUnique, SI16 itemNum )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETSTRREPAIRITEM;
		packetHeader.usSize = sizeof( sDBRequest_SetStrRepairItem );

		siVillageUnique = villageunique;
		siRankType = ranktype;
		siItemUnique = itemUnique;
		siItemNum = itemNum;
	}


};

class sDBResponse_SetStrRepairItem
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siItemUnique;
	SI16				siItemNum;

	sDBResponse_SetStrRepairItem()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetStrRepairItem ) );
	}

};

class sDBRequest_SetStrDura
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siStrDura;

	sDBRequest_SetStrDura( SI32 villageunique, SI32 ranktype, SI32 strdura )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETSTRDURA;
		packetHeader.usSize = sizeof( sDBRequest_SetStrDura );

		siVillageUnique = villageunique;
		siRankType = ranktype;
		siStrDura = strdura;
	}

};

class sDBResponse_SetStrDura
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siStrDura;

	sDBResponse_SetStrDura()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetStrDura ) );
	}

};

class sDBRequest_ChangeStrDura
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siChangeDura;

	sDBRequest_ChangeStrDura( SI32 villageunique, SI32 ranktype, SI32 changedura )
	{
		packetHeader.usCmd = DBMSG_REQUEST_CHANGESTRDURA;
		packetHeader.usSize = sizeof( sDBRequest_ChangeStrDura );

		siVillageUnique = villageunique;
		siRankType = ranktype;
		siChangeDura = changedura;
	}

};

class sDBResponse_ChangeStrDura
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	SI32				siStrDura;

	sDBResponse_ChangeStrDura()
	{
		ZeroMemory( this, sizeof( sDBResponse_ChangeStrDura ) );
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_ChangeStrBaseMoney
//
// Last Modified 	: 2006 / 02 / 21
// Created		 	: �豤��
//
// Function			: [��û] �ǹ��� �ں���(������ �ʿ��� ��)�� ��ȭ�Ѵ�.
//
//***************************************************************************************************
class sDBRequest_ChangeStrBaseMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siCharID;
	SI32				siVillageUnique;			// ���� 

	SI32				siStrType;					// �ǹ� ����
	GMONEY				siMoney;					// �ǹ� �����ڱݿ��� �� �ϰų� �� �ݾ� 

	sDBRequest_ChangeStrBaseMoney()
	{
		Init();
	}

	sDBRequest_ChangeStrBaseMoney( SI32 CharId, SI32 VillageUnique, SI32 StrType, GMONEY Money )
	{
		Set( CharId, VillageUnique, StrType, Money );
	}

	void Init()
	{
		ZeroMemory( this, sizeof( sDBRequest_ChangeStrBaseMoney ) );
	}

	void Set( SI32 CharId, SI32 villageUnique, SI32 strType, GMONEY money ) 
	{
		packetHeader.usSize = sizeof( sDBRequest_ChangeStrBaseMoney );
		packetHeader.usCmd = DBMSG_REQUEST_CHANGESTRBASEMONEY;

		siCharID = CharId;
		siVillageUnique = villageUnique;
		siStrType = strType;
		siMoney = money;
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_ChangeStrBaseMoney
//
// Last Modified 	: 2006 / 02 / 21
// Created		 	: �豤��
//
// Function			: [����] �ǹ��� �ں���(������ �ʿ��� ��)�� ��ȭ�Ѵ�.
//
//***************************************************************************************************
class sDBResponse_ChangeStrBaseMoney
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;					// ����:1, ����:0, �����ڱݺ���:2
	SI32				siCharID;					// ��û�� ����� ���ӳ� ���̵�
	SI32				siVillageUnique;
	SI32				siStrType;					// �ǹ� ����
	cltMoney			clBaseMoney;				// �ǹ� �����ڱ� 

	GMONEY				siChangeMoney;				// ���� �ݾ�

	cltMoney			clCityhallMoney;			// �����ǰ� ���Ŀ� ��û �ں���

	sDBResponse_ChangeStrBaseMoney()
	{
		ZeroMemory( this, sizeof( sDBResponse_ChangeStrBaseMoney ) );
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_SetStrRepairAmount
//
// Last Modified 	: 2006 / 02 / 23
// Created		 	: �豤��
//
// Function			: [��û] �ǹ��� �������� ��û�Ѵ�(���� �ʱ�ȭ)
//
//***************************************************************************************************
class sDBRequest_SetStrRepairAmount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	sDBRequest_SetStrRepairAmount( SI32 VillageUnique, SI32 RankType )
	{
		packetHeader.usCmd = DBMSG_REQUEST_SETSTRREPAIRAMOUNT;
		packetHeader.usSize = sizeof( sDBRequest_SetStrRepairItem );

		siVillageUnique = VillageUnique;
		siRankType = RankType;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_SetStrRepairAmount
//
// Last Modified 	: 2006 / 02 / 23
// Created		 	: �豤��
//
// Function			: [����] �ǹ��� �������� ��û�Ѵ�(���� �ʱ�ȭ)
//
//***************************************************************************************************
class sDBResponse_SetStrRepairAmount
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;										// villageunique
	SI32				siRankType;												// �ǹ� 

	sDBResponse_SetStrRepairAmount()
	{
		ZeroMemory( this, sizeof( sDBResponse_SetStrRepairAmount ) );
	}

};

//***************************************************************************************************
//
// Class Name 		: sDBRequest_RepairStructure
//
// Last Modified 	: 2006 / 02 / 23
// Created		 	: �豤��
//
// Function			: [��û] �ǹ��� �����Ѵ�
//
//***************************************************************************************************
class sDBRequest_RepairStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siVillageUnique;		// villageunique
	SI32				siRankType;				// �ǹ� 

	SI32				siPersonID;				// personid

	SI32				siStrRepairAmount;		// �����ҷ��� ��û�ϴ� ��
	GMONEY				siRepairMoney;

	//KHY - 1102 - ���� ������ ������.
	SI16 			siItemUnique; //���� ��Ʈ ����ũ - �ʿ�ټ���  siStrRepairAmount�� ����.

	sDBRequest_RepairStructure( UI16 Id, SI32 VillageUnique, SI32 RankType, SI32 PersonId, 
		SI32 StrRepairAmount, GMONEY RepairMoney ,SI16 itemunique )
	{
		packetHeader.usCmd = DBMSG_REQUEST_REPAIRSTRUCTURE;
		packetHeader.usSize = sizeof( sDBRequest_RepairStructure );
		usCharID = Id;

		siVillageUnique = VillageUnique;
		siRankType = RankType;

		siPersonID = PersonId;
		siStrRepairAmount = StrRepairAmount;
		siRepairMoney = RepairMoney;
		siItemUnique = itemunique;
	}
};

//***************************************************************************************************
//
// Class Name 		: sDBResponse_RepairStructure
//
// Last Modified 	: 2006 / 02 / 23
// Created		 	: �豤��
//
// Function			: [����] �ǹ��� �����Ѵ�
//
//***************************************************************************************************
class sDBResponse_RepairStructure
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	SI32				siVillageUnique;			// villageunique
	SI32				siRankType;					// �ǹ� 

	SI32				siPersonID;

	SI32				siStrRepairAmount;			// ����� ������û�� ��
	GMONEY				siLeftBaseMoney;			// �����ϰ� �� �ڿ� �ǹ� �ں���
	SI32				siUpdateStrRepairAmount;	// �����а� �� �ڿ� ������(������ �ְ� 1000)

	SI16 				siItemUnique;				// �����ϴµ� ����� ������

	SI16				siItemPos;					// �����ϴµ� ����� ������ ��ġ
	cltItem				clItem;						// �����ϴµ� ����ϰ� ���� ������ ����

	sDBResponse_RepairStructure()
	{
		ZeroMemory( this, sizeof( sDBResponse_RepairStructure ) );
	}

};

class sDBRequest_Contribution_Item_List_Input
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;
	SI32 				m_siInputItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 				m_siInputItemNum[CONTRIBUTION_ITEM_NUM];
	SI32				m_siInputItemIvenPos[CONTRIBUTION_ITEM_NUM];
	
	sDBRequest_Contribution_Item_List_Input( UI16 _usID, SI32 _siPersonID, SI32 _siVillageUnique, SI32 _siNPCKind, SI32* _psiInputItemUnique,  SI16* _psiInputItemNum, SI32* _psiInputItemIvenPos )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize = sizeof( sDBRequest_Contribution_Item_List_Input );
		m_packetHeader.usCmd = DBMSG_REQUEST_CONTRIBUTION_ITEM_LIST_INPUT;
		m_usCharID			= _usID;
		m_siPersonID		= _siPersonID;

		m_siVillageUnique	= _siVillageUnique;
		m_siNPCKind			= _siNPCKind;
		memcpy( m_siInputItemUnique,	_psiInputItemUnique,	sizeof(m_siInputItemUnique) );
		memcpy( m_siInputItemNum,		_psiInputItemNum,		sizeof(m_siInputItemNum) );
		memcpy( m_siInputItemIvenPos,	_psiInputItemIvenPos,	sizeof(m_siInputItemIvenPos) );
	}
};

class sDBResponse_Contribution_Item_List_Input
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;
	SI32 				m_siItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 				m_siItemNum[CONTRIBUTION_ITEM_NUM];
	
	SI16 				m_siInputItemNum[CONTRIBUTION_ITEM_NUM];
	SI32				m_siInputItemIvenPos[CONTRIBUTION_ITEM_NUM];

	sDBResponse_Contribution_Item_List_Input( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

class sDBRequest_Contribution_Make_NPC
{
public:
	sPacketHeader		m_packetHeader;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;
	SI32 				m_siItemUnique[CONTRIBUTION_ITEM_NUM];
	SI16 				m_siItemNum[CONTRIBUTION_ITEM_NUM];

	sDBRequest_Contribution_Make_NPC( UI16 _usID, SI32 _siPersonID, SI32 _siVillageUnique, SI32 _siNPCKind, SI32* _psiItemUnique,  SI16* _psiItemNum )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize = sizeof( sDBRequest_Contribution_Make_NPC );
		m_packetHeader.usCmd = DBMSG_REQUEST_CONTRIBUTION_MAKE_NPC;
		m_usCharID			= _usID;
		m_siPersonID		= _siPersonID;

		m_siVillageUnique	= _siVillageUnique;
		m_siNPCKind			= _siNPCKind;
		memcpy( m_siItemUnique,		_psiItemUnique,		sizeof(m_siItemUnique) );
		memcpy( m_siItemNum,		_psiItemNum,		sizeof(m_siItemNum) );
	}

};

class sDBResponse_Contribution_Make_NPC
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;
	UI16				m_usCharID;
	SI32				m_siPersonID;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;

	sDBResponse_Contribution_Make_NPC( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

class sDBRequest_Contribution_Item_List_Delete
{
public:
	sPacketHeader		m_packetHeader;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;

	sDBRequest_Contribution_Item_List_Delete( SI32 _siVillageUnique, SI32 _siNPCKind )
	{
		ZeroMemory( this, sizeof(*this) );

		m_packetHeader.usSize = sizeof( sDBRequest_Contribution_Item_List_Delete );
		m_packetHeader.usCmd = DBMSG_REQUEST_CONTRIBUTION_ITEM_LIST_DELETE;

		m_siVillageUnique	= _siVillageUnique;
		m_siNPCKind			= _siNPCKind;
	}
};

class sDBRsponse_Contribution_Item_List_Delete
{
public:
	sPacketHeader		m_packetHeader;
	SI32				m_siResult;

	SI32 				m_siVillageUnique;
	SI32 				m_siNPCKind;

	sDBRsponse_Contribution_Item_List_Delete( void )
	{
		ZeroMemory( this, sizeof(*this) );
	}
};

#endif
