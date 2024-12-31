//---------------------------------
// 2003/6/2 ���°�
//---------------------------------

#ifndef _STRUCTURECLASS_H
#define _STRUCTURECLASS_H

#include <Directives.h>

//
#include "..\..\Common\CommonHeader.h"
#include "..\..\Common\Item\ItemCommon\ItemUnit.h"

#include "..\..\Lib\JYLibFunction.h"


extern CJYLibFunction g_JYLibFunction;

class NStrBaseDlg;

class cltCharManager;
class cltAccountNum;
class cltBankAccount;
class cltFee;
class cltBankVary;
class cltRentContract;
class cltHouseUnit;
class cltHouseUnitStorageInfo;
class cltRentApplyer;
class cltStructureRepairDlg;
class cltTime;

#define	CITYHALL_BEING_NORMAL		0			// ���� ���� ���� ��
#define	CITYHALL_BEING_BANKRUPT		1			// ���� �Ļ� ��	
#define	CITYHALL_BEING_INITIALIZED	2			// ���� �ʱ�ȭ �� �Ⱓ ��
#define	CITYHALL_BEING_STABLE		3			// ���� ������ ��
#define	CITYHALL_BEING_PROCESSING	4			// ���� ���°� ó�� ���̴�..(lock ������)
#define CITYHALL_UNDEFINED_STATE	5			// �˼� ���� ���� ��

#define CITYHALL_BANKRUPTCY_NOTIFY_AFTER_MONTHS			6		// ����� ���� �� ���� �Ļ� ������ ������ �Ⱓ
#define	CITYHALL_BANKRUPTCY_NOTIFY_STOCK_AMOUNT_RATE	0.03f	// ���� �Ļ� ��� �˸� ������ �ֽ� ����
#define CITYHALL_BANKRUPTCY_AFTER_YEARS					1		// ����� ���� �� ���� �Ļ��� �� �Ⱓ

#define CITYHALL_STABLE_YEARS_AFTER_CHIEF_ELECTION		1		// �ʱ�ȭ �� ����� ���� �� ���� ������ ���
#define CITYHALL_STABLE_DAYS_AFTER_CHIEF_ELECTION		360		// �ʱ�ȭ �� ����� ���� �� ���� ������ ��¥��

#define MAX_STRUCTURE_TAB_NUMBER	10
#define MAX_DIVIDEND_RECORD			24			// ��� ���� ���� ���� 

//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�. �ο��� �þ.
#define MAX_DIVIDEND_PERSON			300			// �ִ� ��� ���� ���� 

#define MAX_TAX_RECORD_YEAR			10			// ���� ���� ���� ���� ���� 
#define MAX_INOUTMONEY_RECORD		30			// ��� ����� ���� ���� ����

#define MAX_STR_DATA_SIZE			5120		// �� �ǹ� ������ �ִ� ������ ������. 
#define MAX_HIRED_NPC_NUM			4			// �� �������� �ִ� ����� �� �ִ� �ֹ� ����
#define MAX_HIRED_EVENTNPC_NUM		4			// �� �������� �ִ� ����� �� �ִ� �̺�ƮNPC ����

#define MAX_STR_NOTICE_SIZE			256			// �ǹ� �ȳ��� �ִ���� NULL����


//---------------------------------------
// �������� ����.
//---------------------------------------
#define FEETYPE_STOCK_SELL			200
#define FEETYPE_STOCK_BUY			201

#define FEETYPE_MARKET_SELL			300
#define FEETYPE_NEWMARKET_SELL		301

//---------------------------------------
// ��� ����� ���� �ڵ� 
//---------------------------------------
#define INOUTCODE_DIVIDEND			1		// ��� 
#define INOUTCODE_TAX				2		// ����
#define INOUTCODE_STOCK				4		// ����
#define INOUTCODE_GODSTAT			5		// ��Ȳ�� ���� ����
#define INOUTCODE_CASTLESTAT		6		// ���� ���� ���� 
#define INOUTCODE_TOPARENT			7		// �θ� ���� ���� (����)
#define INOUTCODE_FROMCHILD			8		// �ڽ� ���� ���� (����)
#define INOUTCODE_NPCHIRE			9		// NPC���
#define INOUTCODE_NPCPAY			10		// NPC�޿�
#define INOUTCODE_RESIDENTSHARE		11		// �ֹ� ��� 
#define INOUTCODE_BUILDSTRUCTURE	12		// �ǹ� �Ǽ�
#define INOUTCODE_EVENTPAY			13		// ���� �̺�Ʈ �ǽ�
#define INOUTCODE_VILLAGEMARK		14		// ���� ��ũ ���� 
#define INOUTCODE_VILLAGEMAP		15		// ���� �� ����
#define INOUTCODE_INSTANCEPROFIT	16		// �븶�� ���ͱ�
#define INOUTCODE_DESTROYSTR		17		// �ǹ� ������ �Ҹ�� ����
#define INOUTCODE_NATIONTAX			18		// �ս� �ڱ����� ����
#define INOUTCODE_SETBASEMONEY		19		// ���� �ǹ� �ں������� ������ ��
#define INOUTCODE_VILLAGEWARMONEY	20		// ���� ��,�з� ���� ��,���� ��
#define INOUTCODE_DONATEMONEY		21		// ��α����� ������ ��
#define INOUTCODE_CREATEEMPIRE		22		// ������ ����µ� ����� ��
#define INOUTCODE_SETEMPIREMONEY	23		// �����ں��� �ִµ� ����ߴ�
#define INOUTCODE_BLACK_WAR			24		// ���� �������� ���� �ڱ�.


//---------------------------------------
// ��Ȳ�� 
//---------------------------------------
#define SYMBOLSTAT_KIND				1		
#define SYMBOLSTAT_LIFE				2		
#define SYMBOLSTAT_MANA				3		
#define SYMBOLSTAT_CAPA				4		

//---------------------------------------
// ��� ����� ���� ���� 
//---------------------------------------
class cltCityHallInOutMoneyUnitInfo
{
public:
	SI32							siStrType;								// ����� �ǹ�
	SI32							siInOutCode;							// ����� �ڵ�
	cltDate							clDate;									// ������� 
	cltMoney						clInOutMoney;							// ����ݾ� 
	cltMoney						clCityhallMoney;						// ����ܰ�
};

//---------------------------------------
// ��� ����� ���� ���� 
//---------------------------------------
class cltCityHallInOutMoneyInfo
{
public:
	SI32							siCount;
	cltCityHallInOutMoneyUnitInfo	clInOutMoneyUnitInfo[ MAX_INOUTMONEY_RECORD ];

	void Init()
	{
		siCount = 0;
	}

	SI32 GetCount() { return siCount; };	
	void AddInOutMoneyInfo( SI32 strType, SI32 inoutcode, cltDate *pclDate, cltMoney *pclInOutMoney, cltMoney *pclCityhallMoney );
};

//---------------------------------------
// ��� �ֹ�(NPC)����
//---------------------------------------
class cltHiredNPC
{
public:
	SI32		siNPCKind;					// NPC Kind
	GMONEY		siHirePay;					// �����
	GMONEY		siMonthlyPay;				// ����
	cltDate		clHireDate;					// �����

	void Set(cltHiredNPC* pclHiredNPC)
	{
		if(pclHiredNPC == NULL)			return;

		siNPCKind	= pclHiredNPC->siNPCKind;
		siHirePay	= pclHiredNPC->siHirePay;
		siMonthlyPay = pclHiredNPC->siMonthlyPay;
		clHireDate.Set(&pclHiredNPC->clHireDate);
	}
};

//---------------------------------------
// ��� ���� ����
//---------------------------------------
class cltDividendPerson
{
public:
	SI32		siPersonID;					// personid
	cltMoney	clMoney;					// ���� 
	//KHY - 0730 - ��� ���� ������ ���� �� �ݾ��� ������Ʈ �����ش�.
	cltMoney	clAllMoney;					// ��� ���� person�� ������  �ִ� �ѱݾ�.


	cltDividendPerson()
	{
		siPersonID = 0;
		clMoney.Init();
	}
};

//---------------------------------------
// ��� ����
//---------------------------------------
class cltDividendUnitInfo
{
public:
	cltDate		clDate;						// �����
	
	UI16		usYear;						// ���⵵ 
	SI32		siTotalStock;				// �� ��� �ֽ� ��
	cltMoney	clDividendPrice;			// �� �ִ� ����  

	void Init()
	{
		siTotalStock = 0;
		clDividendPrice.Init();
	}
};

//---------------------------------------
// ��� ����
//---------------------------------------
class cltDividendInfo
{
public:
	SI32					siCount;

	cltDividendUnitInfo		clDividendUnitInfo[ MAX_DIVIDEND_RECORD ];

	void Init()
	{
		siCount = 0;
	}

	void		SetCount( SI32 count ) { siCount = count; };
	SI32		GetCount() { return siCount; };

	SI32		GetTotalSize() { 
		return sizeof( cltDividendInfo ); 
	};

	void		AddDividendInfo( cltDate *pclDate, SI32 siTotalStock, cltMoney *pclMoney );
};


// ��� ���� 
class cltCityhallStrInfo {
public:

	cltCityHallInOutMoneyInfo	clInOutMoneyInfo;								// ��� �ڱ� ����� ���� ���� 
	cltDividendInfo				clDividendInfo;									// ��� ���� ����

	cltHiredNPC		clHiredNPC[ MAX_HIRED_NPC_NUM ];							// �ֹ� ��� ����
	cltHiredNPC		clHiredEventNPC[ MAX_HIRED_EVENTNPC_NUM ];					// �̺�Ʈ�� NPC ��� ����

	SI32			siResidentNum;												// �ֹμ�
	SI32			siTotalStockAmount;											// �� ���� �ֽ� ��
	GMONEY			siStockPrice;												// ���� �ֽ� ���� 
	GMONEY			siBeginningPrice;											// ���� ���� �ֽ� ���� 
	SI32			siVillageLevel;												// ���� ���� 

	SI32			siMasterVillage;											// �ְ� �θ� ����
	SI32			siParentVillage;											// �θ���
	BOOL			bDeclareWarVillage[ MAX_VILLAGE_NUMBER ];					// �������� ���� 	

	UI16		uiDeclareWarDateYear;				// �������� ����
	UI08		uiDeclareWarDateMonth;
	UI08		uiDeclareWarDateDay;
	
	UI16		uiLastWarLoseDateYear;				// ���� ������ �й���(1���ϰ� ��ȣ�ޱ� ���� ���̴� ����)
	UI08		uiLastWarLoseDateMonth;
	UI08		uiLastWarLoseDateDay;
 
	SI16		siVillaeWarRecordWin;				// ���� ������ ���� �¸���
	SI16		siVillaeWarRecordLose;				// ���� ������ ���� �й��

	SI16			siSymbolKind;												// �ɺ�(��ȣ��) ���� 
	SI32			siSymbolLife;												// �ɺ�(��ȣ��) ü��
	SI32			siSymbolMana;												// �ɺ�(��ȣ��) Mana
	SI16			siSymbolCapa;												// �ɺ�(��ȣ��) ����
	SI32			siSymbolMaxLife;											// �ɺ�(��ȣ��) �ִ� ü�� 
	cltDate			clLastSymbolUpdate;											// �ֱ� �ɺ� ���� ������ 
	
	SI16			siCastleKind;												// ĳ�� ���� 
	SI32			siCastleLife;												// ĳ�� ü��
	SI32			siCastleMana;												// ĳ�� Mana
	SI16			siCastleCapa;												// ĳ�� ����
	SI32			siCastleMaxLife;											// ĳ�� �ִ� ü�� 
	cltDate			clLastCastleUpdate;											// �ֱ� ĳ�� ���� ������ 
	
	SI32			siLastDestroyStrDate;										// ���������� �ǹ��� ��ü�� ���� DateVary

	cltMoney		clProfitMoney;												// ���ͱ�
	cltDate			clChiefDate;												// ����� ��������

	SI32			siVisitLevel;												// �湮�� ����

//#if	defined(_CITYHALL_BANKRUPTCY)
	cltDate			clResignDate;												// ����� ������
	UI08			usCurStatus;												// ���� ������ ���� CITYHALL_BEING_BANKRUPT : �Ļ�, CITYHALL_BEING_INITIALIZED : �ʱ�ȭ, 
																				// CITYHALL_BEING_STABLE : ������, CITYHALL_BEING_NORMAL : ����

	SI32			siTotalVillageScore;
	
	void Set(cltCityhallStrInfo* pclinfo)
	{
		SI32 i = 0;

		clInOutMoneyInfo = pclinfo->clInOutMoneyInfo;
		clDividendInfo = pclinfo->clDividendInfo;
		memcpy( &clHiredNPC, &pclinfo->clHiredNPC, sizeof( cltHiredNPC ) * MAX_HIRED_NPC_NUM );
		memcpy( &clHiredEventNPC, &pclinfo->clHiredEventNPC, sizeof( cltHiredNPC ) * MAX_HIRED_EVENTNPC_NUM );
		siResidentNum = pclinfo->siResidentNum;
		siTotalStockAmount = pclinfo->siTotalStockAmount;
		siStockPrice = pclinfo->siStockPrice;
		siBeginningPrice = pclinfo->siBeginningPrice;
		siVillageLevel = pclinfo->siVillageLevel;
	
		// ���� ����
		siMasterVillage = pclinfo->siMasterVillage;
		siParentVillage = pclinfo->siParentVillage;
		memcpy( bDeclareWarVillage, pclinfo->bDeclareWarVillage, sizeof( BOOL ) * MAX_VILLAGE_NUMBER );
//		clDeclareWarDate.Set( &pclinfo->clDeclareWarDate );
//		clLastWarLoseDate.Set( &pclinfo->clLastWarLoseDate );


		uiDeclareWarDateYear = pclinfo->uiDeclareWarDateYear;
		uiDeclareWarDateMonth = pclinfo->uiDeclareWarDateMonth;
		uiDeclareWarDateDay = pclinfo->uiDeclareWarDateDay;

		uiLastWarLoseDateYear = pclinfo->uiLastWarLoseDateYear;
		uiLastWarLoseDateMonth = pclinfo->uiLastWarLoseDateMonth;
		uiLastWarLoseDateDay = pclinfo->uiLastWarLoseDateDay;

		siVillaeWarRecordWin	= pclinfo->siVillaeWarRecordWin;
		siVillaeWarRecordLose	= pclinfo->siVillaeWarRecordLose;

		// �ɺ� 
		siSymbolKind = pclinfo->siSymbolKind;
		siSymbolLife = pclinfo->siSymbolLife;
		siSymbolMana = pclinfo->siSymbolMana;
		siSymbolCapa = pclinfo->siSymbolCapa;
		siSymbolMaxLife = pclinfo->siSymbolMaxLife;
		clLastSymbolUpdate.Set( &pclinfo->clLastSymbolUpdate );		

		// ĳ��
		siCastleKind = pclinfo->siCastleKind;
		siCastleLife = pclinfo->siCastleLife;
		siCastleMana = pclinfo->siCastleMana;
		siCastleCapa = pclinfo->siCastleCapa;
		siCastleMaxLife = pclinfo->siCastleMaxLife;
		clLastCastleUpdate.Set( &pclinfo->clLastCastleUpdate );		

		siLastDestroyStrDate	= pclinfo->siLastDestroyStrDate;

		clProfitMoney.Set( &pclinfo->clProfitMoney );
		clChiefDate.Set( &pclinfo->clChiefDate );

		siVisitLevel = pclinfo->siVillageLevel;

//#if	defined(_CITYHALL_BANKRUPTCY)
		clResignDate.Set( &pclinfo->clResignDate );					// ����� ������
		usCurStatus = pclinfo->usCurStatus;							// ���� ������ ���� CITYHALL_BEING_BANKRUPT : �Ļ�, CITYHALL_BEING_INITIALIZED : �ʱ�ȭ, 
																	// CITYHALL_BEING_STABLE : ������, CITYHALL_BEING_NORMAL : ����

		siTotalVillageScore = pclinfo->siTotalVillageScore;
//#endif
	}

	GMONEY GetTotalDividendMoney( int year ) {

		GMONEY ret = 0;

		for( int i = 0; i < MAX_DIVIDEND_RECORD; ++i ) {
			
			if( (int)(clDividendInfo.clDividendUnitInfo[ i ].clDate.uiYear) == year ) {
				ret += (clDividendInfo.clDividendUnitInfo[ i ].clDividendPrice.itMoney);
			}
		}

		return ret;
	}
	//���� ���Կ� ���� ���Ǿ��� �ִ��� Ȯ��.
	BOOL IHaveEventNpc( SI32 kind){
		for (int i=0; i<MAX_HIRED_EVENTNPC_NUM; i++) {
			if (clHiredEventNPC[i].siNPCKind == kind ) {
				return TRUE;
			}
		}
		return FALSE;
	}

};


// ���� ����
class cltBankStrInfo{
public:
	cltFee	 clFee;					// ������ ����
	cltMoney clMaxMoney;			// ���´� �ִ� �Ա� ���ɾ�
	cltMoney clTotalInputMoney;		// ���Աݾ�

	void Set(cltBankStrInfo* pclinfo)
	{
		clFee.Set(&pclinfo->clFee);
		clMaxMoney.Set(&pclinfo->clMaxMoney);
		clTotalInputMoney.Set(&pclinfo->clTotalInputMoney);
	}
};

// ���� ����
class cltStockStrInfo{
public:
	cltFee clFee;

	void Set(cltStockStrInfo* pclinfo)
	{
		clFee.Set(&pclinfo->clFee);
	}

};


// ���� ���� 
class cltMarketStrInfo
{
public:
	cltFee clFee;

	void Set(cltMarketStrInfo* pclinfo)
	{
		clFee.Set(&pclinfo->clFee);
	}
};

class cltNewMarketStrInfo
{
public:
	cltFee clFee;

	void Set(cltNewMarketStrInfo* pclinfo)
	{
		clFee.Set( &pclinfo->clFee );
	}
};


// ���� ���� 
class cltHouseStrInfo
{
public:
	cltRentContract clRentContract;
	cltDate			clLastChangeDate;	// ��� ���� ���� ������ 

	void Set(cltHouseStrInfo* pclinfo)
	{
		clRentContract.Set( &pclinfo->clRentContract );
		clLastChangeDate.Set( &pclinfo->clLastChangeDate );
	}
};

// ������ ����
#define MAX_HUNT_STG_NUMBER						10			// ���� â�� �뷮. 
#define MAX_HUNT_LINEUP_NUMBER					10			// ������ ��ġ�� ���� ���� ��
#define MAX_HUNT_MONSTER_NUM					60			// ������ ��ġ�� Max ���ͼ�
#define MAX_HUNT_LINEUP_EACH_MONSTER_NUM		30			// ���� �� ������ ��ġ ������ ��

#define MAX_HUNT_MAP_NUMBER						100			// ������ �� ����
#define HUNT_MAP_START							201			// ������ ���� �ε���



enum { HUNT_ENTER_ITEMINSUFFICIENY, HUNT_ENTER_ENABLESTATUS };

class cltHuntStrInfo{
public:
	GMONEY siEnterFee;			// �����. 

	SI16 siHuntStatus;			// ������ ����

	//----------------------------
	// ���� ���� ���ƾ� �� ���� 
	//----------------------------
	SI32 siChiefExp;			// ����� ȹ���ϰ� �Ǵ� ����ġ. 
	GMONEY siTempMoney;			// ������ �ڱ����� �� ���� �ӽ� ������. 
	SI32 siUserNum;				// ������ �̿��� ��. 

	cltHuntStg clHuntStg[MAX_HUNT_STG_NUMBER];			// ���� ��ȯ �������� ���� ����. 
	cltHuntLineUp clHuntLineUp[MAX_HUNT_LINEUP_NUMBER];	// ������ ��ġ�� ���� ����. 

	void Set(cltHuntStrInfo* pclinfo)
	{
		SI32 i;
		
		siEnterFee			= pclinfo->siEnterFee;
		siHuntStatus		= pclinfo->siHuntStatus;
		
		siChiefExp			= pclinfo->siChiefExp;
		siTempMoney			= pclinfo->siTempMoney;
		siUserNum			= pclinfo->siUserNum;


		for(i = 0;i < MAX_HUNT_STG_NUMBER;i++)
		{
			clHuntStg[i].Set(&pclinfo->clHuntStg[i]);
		}

		for(i = 0;i < MAX_HUNT_LINEUP_NUMBER;i++)
		{
			clHuntLineUp[i].Set(&pclinfo->clHuntLineUp[i]);
		}
	}
};



// ��ü�� ����
class cltPostOfficeStrInfo {
public:
	cltFee clMoneyFee;											// �۱� ������ 
	cltFee clItemFee;											// ��ǰ ���� ������

	GMONEY   siMsgFee;											// �޽��� ������ (�Ǵ�)
	GMONEY   siRecvFee;											// ������ ���� ������ (ȸ��)
	
	void Set(cltPostOfficeStrInfo* pclinfo)
	{
		clMoneyFee.Set( &pclinfo->clMoneyFee );
		clItemFee.Set( &pclinfo->clItemFee );

		siMsgFee = pclinfo->siMsgFee;
		siRecvFee = pclinfo->siRecvFee;
	}
};

// �纹�� ����
class cltHorseMarketStrInfo {
public:
	cltFee clFee;

	void Set(cltHorseMarketStrInfo* pclinfo)
	{
		clFee.Set(&pclinfo->clFee);
	}
};


// �Ű� ����
class cltRealEstateMarketStrInfo {
public:
	cltFee clFee;

	void Set(cltRealEstateMarketStrInfo* pclinfo)
	{
		clFee.Set(&pclinfo->clFee);
	}
};

// ��ȯ���ŷ��� ����
class cltSummonMarketStrInfo {
public:
	cltFee clFee;

	void Set(cltSummonMarketStrInfo* pclinfo )
	{
		clFee.Set(&pclinfo->clFee);
	}
};


// �������� 
class cltLandStrInfo{
public:
	cltRentContract	clRentContract;
	cltDate			clLastChangeDate;			// ��� ���� ���� ������ 

	SI32			siLandType;					// ���� ����

	void Set(cltLandStrInfo* pclinfo)
	{
		clRentContract.Set( &pclinfo->clRentContract );
		clLastChangeDate.Set( &pclinfo->clLastChangeDate );

		siLandType = pclinfo->siLandType;
	}

};

// ��ƼȦ ���� Ÿ��.
#define		TYPE_ENTRANCE_PUBLIC			1	// ����.
#define		TYPE_ENTRANCE_VILLAGE			2	// ����.
#define		TYPE_ENTRANCE_GUILD				3	// ���.
#define		TYPE_ENTRANCE_PRIVATE			4	// �����.
#define		RESERVATIO_PRESENT_ITEM			3	// ������..�״ϱ� �����ڰ� ������ ��� �� �� �ִ� ������ �ִ� ��.
#define		ENTRANCE_APPLICATION_LIST		20	// ���� ��û ������ 20�� ����.


//[����] ��Ƽ�忡�� ������ �������� ����� ����ü
class cltPartyHallPresentItemInfo
{
public:
	SI32 m_siItemUnique;
	SI32 m_siItemNum;
	
	cltPartyHallPresentItemInfo()
	{
		ZeroMemory(this, sizeof(cltPartyHallPresentItemInfo));
	}

	void Set(cltPartyHallPresentItemInfo* pclPartyHallPresentItemInfo)
	{
		if(pclPartyHallPresentItemInfo == NULL)			return;

		m_siItemUnique	= pclPartyHallPresentItemInfo->m_siItemUnique;
		m_siItemNum		= pclPartyHallPresentItemInfo->m_siItemNum;
	}
};

//[����] ��Ƽ�忡�� ������ �������� ����� ����ü
class cltPartyHallEntranceApplication
{
public:
	SI32 m_siPersonID;
	SI32 m_siLevel;
	
	cltPartyHallEntranceApplication()
	{
		ZeroMemory(this, sizeof(cltPartyHallEntranceApplication));
	}

	void Set(cltPartyHallEntranceApplication* pclPartyHallEntranceApplication)
	{
		if(pclPartyHallEntranceApplication == NULL)			return;

		m_siPersonID	= pclPartyHallEntranceApplication->m_siPersonID;
		m_siLevel		= pclPartyHallEntranceApplication->m_siLevel;
	}
};

//[����] ��ƼȦ. ���� ����Ʈ ����ü.
class cltPatyHallResvInfo
{
public:
	SI32			m_siPersonID;									// ��û�� person id
	TCHAR			m_szPersonName[ MAX_PLAYER_NAME ];				// ��û�� name 
	SYSTEMTIME		m_SystemTime;
	TCHAR			m_szReason[ 128 ];								// ��ȸ ���� 

	SI16			m_siEntranceType;								//[����] 1: ����,	 2: ����,    3: ���,  4: ����� => 2008. 3. 10
	SI16			m_siDecorationKind;								//[����] ��Ĺ� ����. 
	SI16			m_siValueType;									//[����] ������ȣ, ����ȣ.

#ifdef _SAFE_MEMORY
	NSafeTArray<cltPartyHallPresentItemInfo, RESERVATIO_PRESENT_ITEM>		m_PresentItem;				//[����] ��ƼȦ. �����ڰ� �� ������ ���. => 2008. 3. 13
	NSafeTArray<cltPartyHallEntranceApplication, ENTRANCE_APPLICATION_LIST>	m_clEntranceApplication;	//[����] ��ƼȦ. ���� ��û ������ ����Ʈ. => 2008. 3. 14
#else
	cltPartyHallPresentItemInfo			m_PresentItem[RESERVATIO_PRESENT_ITEM];				//[����] ��ƼȦ. �����ڰ� �� ������ ���. => 2008. 3. 13
	cltPartyHallEntranceApplication		m_clEntranceApplication[ENTRANCE_APPLICATION_LIST]; //[����] ��ƼȦ. ���� ��û ������ ����Ʈ. => 2008. 3. 14
#endif


	void Set( cltPatyHallResvInfo *pclinfo ) 
	{
		ZeroMemory( this, sizeof( cltPatyHallResvInfo ) );
	
		m_siPersonID = pclinfo->m_siPersonID;
		MStrCpy(m_szPersonName, pclinfo->m_szPersonName, sizeof(m_szPersonName));
		m_szPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
		m_SystemTime.wYear   = pclinfo->m_SystemTime.wYear;  
		m_SystemTime.wMonth  = pclinfo->m_SystemTime.wMonth; 
		m_SystemTime.wDay	 = pclinfo->m_SystemTime.wDay;	
		m_SystemTime.wHour	 = pclinfo->m_SystemTime.wHour;
		m_SystemTime.wMinute = pclinfo->m_SystemTime.wMinute;
		MStrCpy( m_szReason, pclinfo->m_szReason, sizeof(m_szReason) );
		m_szReason[ 127 ] = NULL;

		m_siEntranceType	= pclinfo->m_siEntranceType;
		m_siDecorationKind  = pclinfo->m_siDecorationKind;  
		m_siValueType		= pclinfo->m_siValueType;

		SI32 i = 0;
#ifdef _SAFE_MEMORY
		for(i=0; i<RESERVATIO_PRESENT_ITEM; i++)		m_PresentItem[i].Set(&pclinfo->m_PresentItem[i]);
		for(i=0; i<ENTRANCE_APPLICATION_LIST; i++)		m_clEntranceApplication[i].Set(&pclinfo->m_clEntranceApplication[i]);
#else
		memcpy( m_PresentItem, pclinfo->m_PresentItem, sizeof(m_PresentItem) );
		memcpy( m_clEntranceApplication, pclinfo->m_clEntranceApplication, sizeof(m_clEntranceApplication) );
#endif
	}
};

// ���ڽ� ���� ���� 
class cltFeastResvInfo
{
public:
	SI32			siPersonID;										// ��û�� person id
	TCHAR			szPersonName[ MAX_PLAYER_NAME ];				// ��û�� name 
	SI16			siYear;											// ��ȸ �ð�(��)
	SI16			siMonth;										// ��ȸ �ð�(��)
	SI16			siDay;											// ��ȸ �ð�(��)
	SI16			siHour;											// ��ȸ �ð�(��)
	SI16			siMinute;										// ��ȸ �ð�(��)
	TCHAR			szReason[ 128 ];								// ��ȸ ���� 

	void			Set( cltFeastResvInfo *pclinfo ) {

		siPersonID = pclinfo->siPersonID;
		memcpy( szPersonName, pclinfo->szPersonName, MAX_PLAYER_NAME );
		szPersonName[ MAX_PLAYER_NAME - 1 ] = NULL;
		siYear = pclinfo->siYear;
		siMonth = pclinfo->siMonth;
		siDay = pclinfo->siDay;
		siHour = pclinfo->siHour;
		siMinute = pclinfo->siMinute;
		memcpy( szReason, pclinfo->szReason, 128 );
		szReason[ 127 ] = NULL;
	}
};



// ���ڽ� �⺻ ���� 
class cltFeastInfo
{
public:
	GMONEY			siCost;										// ��ȸ ���
	
	SI16			siItemUnique[ MAX_FEAST_PRESENT_NUMBER ];	// ���� item unique
	SI16			siItemNum[ MAX_FEAST_PRESENT_NUMBER ];		// ���� item num
	SI16			siItemGive[ MAX_FEAST_PRESENT_NUMBER ];		// ���� ���� ���� 1:���޵� 0: ���޾ȵ�

	SI32			siStatus;									// 1: ��ȸ��,  2: �����,  0: ��ȸ�� �ƴ� 

	void Set( cltFeastInfo *pclinfo ) 
	{

		siCost = pclinfo->siCost;
		memcpy( siItemUnique, pclinfo->siItemUnique, sizeof( siItemUnique ) );
		memcpy( siItemNum, pclinfo->siItemNum, sizeof( siItemNum ) );
		memcpy( siItemGive, pclinfo->siItemGive, sizeof( siItemGive ) );
		siStatus	   = pclinfo->siStatus;
	}


	SI32 GetEmptyPresentIndex() {

		for( int i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {
			
			if( siItemUnique[ i ] == 0 ) return i;
		}

		return -1;
	}

	void SetPresentItem( SI32 index, SI16 itemunique, SI16 itemnum )
	{
		siItemUnique[ index ] = itemunique;
		siItemNum[ index ] = itemnum;
	}

};

class PartyHall_Decoration
{
public:
	SI16	m_DacorationKind;
	SI16	m_DacorationNum;

	void Set(PartyHall_Decoration* pclPartyHall_Decoration)
	{
		if(pclPartyHall_Decoration == NULL)			return;

		m_DacorationKind = pclPartyHall_Decoration->m_DacorationKind;
		m_DacorationNum = pclPartyHall_Decoration->m_DacorationNum;
	}
};

// ���ڽ� ����
class cltFeastStrInfo{
public:
	cltFeastInfo		clFeastInfo;							// ���ڽ� �⺻���� 
	cltFeastStg			clFeastStg[ MAX_FEAST_STG_NUMBER ];		// ���ڽ� â������
	cltFeastResvInfo	clFeastResvInfo;						// ���ڽ� ��������

	PartyHall_Decoration	clDecoration[MAX_PARTYHALL_DECORATION_ITEM];	// ��Ĺ�.

	void Set( cltFeastStrInfo* pclinfo )
	{
		clFeastInfo.Set( &pclinfo->clFeastInfo );
		memcpy( clFeastStg, pclinfo->clFeastStg, sizeof( cltFeastStg ) * MAX_FEAST_STG_NUMBER );
		clFeastResvInfo.Set( &pclinfo->clFeastResvInfo );
		memcpy( clDecoration, pclinfo->clDecoration, sizeof( clDecoration ));
	}


	BOOL CanResv() 
	{
		int i, j;

		BOOL bRet = FALSE;

		for( i = 0; i < MAX_FEAST_PRESENT_NUMBER; ++i ) {

			if( clFeastInfo.siItemUnique[ i ] == 0 ) continue;

			bRet = TRUE;

			for( j = 0; j < MAX_FEAST_STG_NUMBER; ++j ) {

				if( clFeastInfo.siItemUnique[ i ] == clFeastStg[ j ].siItemUnique ) {
						
						if( clFeastInfo.siItemNum[ i ] > clFeastStg[ j ].siItemNum ) return FALSE;

						break;
					}
			}

			if( j == MAX_FEAST_STG_NUMBER ) return FALSE;
		}

		return bRet;
	}

};

// �񺯻� ����
class cltSummonHeroMarketStrInfo {
public:
	cltFee clFee;

	void Set(cltSummonHeroMarketStrInfo* pclinfo )
	{
		clFee.Set(&pclinfo->clFee);
	}
};

// �������� 
class cltMineStrInfo{
public:
	cltRentContract	clRentContract;
	cltDate			clLastChangeDate;			// ��� ���� ���� ������ 

	SI32			siMineType;					// ���� ����

	void Set(cltMineStrInfo* pclinfo)
	{
		clRentContract.Set( &pclinfo->clRentContract );
		clLastChangeDate.Set( &pclinfo->clLastChangeDate );

		siMineType = pclinfo->siMineType;
	}

};


// ��ܰ����� ����
class cltGuildStrInfo {
public:
	//SI32			siRentMonthPeriod;	// �Ӵ�Ⱓ	- �� ����

	GMONEY			siRentFee;			// �� �Ӵ��. 
	//cltDate			clDate;				// ����Ͻ�. 

	cltFee			clFee;				// ������
	cltDate			clLastChangeDate;	// ��� ���� ���� ������ 

	void Set(cltGuildStrInfo* pclinfo )
	{
		siRentFee = pclinfo->siRentFee;
		//siRentMonthPeriod = pclinfo->siRentMonthPeriod;
		//clDate.Set( &pclinfo->clDate );

		clLastChangeDate.Set( &pclinfo->clLastChangeDate );
		clFee.Set( &pclinfo->clFee );
	}
};



//---------------------------------------
// ���� ����
//---------------------------------------
class cltTaxUnitInfo
{
public:
	cltTaxUnitInfo() {
		usYear = 0;
		clDueTax.Init();
		clPaidTax.Init();
	}

	UI16		usYear;
	cltMoney	clDueTax;
	cltMoney	clPaidTax;
};

//---------------------------------------
// ���� ����
//---------------------------------------
class cltTaxInfo
{
public:
	cltTaxInfo() {
		siCount = 0;
	}
	SI32			siCount;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltTaxUnitInfo, MAX_TAX_RECORD_YEAR>		clTaxUnitInfo;
#else
	cltTaxUnitInfo	clTaxUnitInfo[ MAX_TAX_RECORD_YEAR ];
#endif

	void			SetCount( SI32 count ) { siCount = count; };
	SI32			GetCount() { return siCount; };

	SI32			GetTotalSize() { return sizeof( cltTaxInfo ); };

	void			SetTax( UI16 year, cltMoney *pclTax );
	void			SetPaidTax( UI16 year, cltMoney *pclTax );
};


//---------------------------------------
// �ǹ� �⺻ ���� Ŭ���� 
//---------------------------------------
//class cltStrCommonInfo{
//public:
//	SI32		siStrType;				// �ǹ��� ����.
//	cltMoney	clMoney;
//
//	cltTaxInfo	clTaxInfo;
//	TCHAR		strNotice[ MAX_STR_NOTICE_SIZE ];
//
//	SI32		siStrDura;				// �ǹ� ������
//	
//	SI32		siNeedItemUnique;		// �����ϱ� ���� �ʿ��� ������ ����ũ 
//	SI16		siNeedItemNum;			// �����ϱ� ���� �ʿ��� ������ ���� 
//	SI16		siUseItemNum;			// �����ϱ� ���� ä�� ���� ������ ����
//
//	cltStrCommonInfo()
//	{
//		siStrType	= 0;
//		clMoney.Init();
//		strNotice[ 0 ] = NULL;
//
//		siStrDura = 0;
//		siNeedItemUnique = 0;
//		siNeedItemNum = 0;
//		siUseItemNum = 0;
//	}
//
//	void Set(cltStrCommonInfo* pclinfo)
//	{
//		siStrType	= pclinfo->siStrType;
//		clTaxInfo = pclinfo->clTaxInfo;
//		
//		clMoney.Set(&pclinfo->clMoney);
//
//		memcpy( strNotice, pclinfo->strNotice, MAX_STR_NOTICE_SIZE );
//
//		siStrDura = pclinfo->siStrDura;
//		siNeedItemUnique = pclinfo->siNeedItemUnique;
//		siNeedItemNum = pclinfo->siNeedItemNum;
//		siUseItemNum = pclinfo->siUseItemNum;
//	}
//	
//};

class cltStrCommonInfo{
public:
	SI32		siStrType;				// �ǹ��� ����.
	cltMoney	clMoney;

	cltTaxInfo	clTaxInfo;
	char		strNotice[ MAX_STR_NOTICE_SIZE ];

	SI32		siStrDura;				// �ǹ� ������

	SI32		siNeedItemUnique;		// �����ϱ� ���� �ʿ��� ������ ����ũ 
	SI16		siNeedItemNum;			// �����ϱ� ���� �ʿ��� ������ ���� 
	SI16		siUseItemNum;			// �����ϱ� ���� ä�� ���� ������ ����

	SI32		siRepairStrDura;		// �����ҷ��� ��������(0~1000)

	cltMoney	clBaseMoney;			// �ǹ��� �� �ں���( ������ ���ȴ�.)
	
	cltStrCommonInfo()
	{
		siStrType	= 0;
		clMoney.Init();
		strNotice[ 0 ] = NULL;

		siStrDura = 0;
		siNeedItemUnique = 0;
		siNeedItemNum = 0;
		siUseItemNum = 0;

		siRepairStrDura = 0;

		clBaseMoney.Init();
	}

	void Set(cltStrCommonInfo* pclinfo)
	{
		siStrType	= pclinfo->siStrType;
		clTaxInfo = pclinfo->clTaxInfo;

		clMoney.Set(&pclinfo->clMoney);

		memcpy( strNotice, pclinfo->strNotice, MAX_STR_NOTICE_SIZE );

		siStrDura = pclinfo->siStrDura;
		siNeedItemUnique = pclinfo->siNeedItemUnique;
		siNeedItemNum = pclinfo->siNeedItemNum;
		siUseItemNum = pclinfo->siUseItemNum;

		siRepairStrDura = pclinfo->siRepairStrDura;

		clBaseMoney.Set(&pclinfo->clBaseMoney);
	}

};



//---------------------------------------
// �ǹ��� ����. 
//---------------------------------------
class cltStrInfo{
public:
	cltStrCommonInfo clCommonInfo;

	union{
		UI08 cData[MAX_STR_DATA_SIZE];
		cltBankStrInfo				clBankStrInfo;
		cltStockStrInfo				clStockStrInfo;
		cltMarketStrInfo			clMarketStrInfo;
		cltHouseStrInfo				clHouseStrInfo;
		cltCityhallStrInfo			clCityhallStrInfo;
		cltHuntStrInfo				clHuntStrInfo;
		cltPostOfficeStrInfo		clPostOfficeStrInfo;
		cltHorseMarketStrInfo		clHorseMarketStrInfo;
		cltRealEstateMarketStrInfo	clRealEstateMarketStrInfo;
		cltSummonMarketStrInfo		clSummonMarketStrInfo;
		cltLandStrInfo				clLandStrInfo;
		cltFeastStrInfo				clFeastStrInfo;
		cltSummonHeroMarketStrInfo	clSummonHeroMarketStrInfo;
		cltMineStrInfo				clMineStrInfo;
		cltGuildStrInfo				clGuildStrInfo;
		//cltNewMarketStrInfo		clNewMarketStrInfo;			// [����] ���ո��� 2009-1-5 
		cltNewMarketStrInfo		clNewMarketStrInfo;				// [����] ���ո��� 2009-1-5 
	};


	cltStrInfo()
	{
		ZeroMemory(cData, MAX_STR_DATA_SIZE);
	}

	void Set(cltStrInfo* pclinfo)
	{
		clCommonInfo.Set(&pclinfo->clCommonInfo);

		switch(clCommonInfo.siStrType)
		{
		case RANKTYPE_BANK:				clBankStrInfo.Set(&pclinfo->clBankStrInfo);							break;
		case RANKTYPE_STOCK:			clStockStrInfo.Set(&pclinfo->clStockStrInfo);						break;
		case RANKTYPE_MARKET:			clMarketStrInfo.Set(&pclinfo->clMarketStrInfo);						break;
		case RANKTYPE_HUNT:				clHuntStrInfo.Set(&pclinfo->clHuntStrInfo);							break;
		case RANKTYPE_HOUSE:			clHouseStrInfo.Set(&pclinfo->clHouseStrInfo);						break;
		case RANKTYPE_CITYHALL:			clCityhallStrInfo.Set(&pclinfo->clCityhallStrInfo);					break;
		case RANKTYPE_POSTOFFICE:		clPostOfficeStrInfo.Set(&pclinfo->clPostOfficeStrInfo);				break;
		case RANKTYPE_HORSEMARKET:		clHorseMarketStrInfo.Set(&pclinfo->clHorseMarketStrInfo);			break;
		case RANKTYPE_REALESTATEMARKET: clRealEstateMarketStrInfo.Set(&pclinfo->clRealEstateMarketStrInfo); break;
		case RANKTYPE_SUMMONMARKET:		clSummonMarketStrInfo.Set(&pclinfo->clSummonMarketStrInfo);			break;
		case RANKTYPE_LAND:				clLandStrInfo.Set( &pclinfo->clLandStrInfo );						break;
		case RANKTYPE_FEAST:			clFeastStrInfo.Set( &pclinfo->clFeastStrInfo );						break;
		case RANKTYPE_SUMMONHEROMARKET: clSummonHeroMarketStrInfo.Set(&pclinfo->clSummonHeroMarketStrInfo); break;
		case RANKTYPE_MINE:				clMineStrInfo.Set( &pclinfo->clMineStrInfo );						break;
		case RANKTYPE_GUILD:			clGuildStrInfo.Set( &pclinfo->clGuildStrInfo );						break;		
		case RANKTYPE_NEWMARKET:		clNewMarketStrInfo.Set( &pclinfo->clNewMarketStrInfo);			break;		
			
		default:
			TCHAR buffer[128];
			StringCchPrintf(buffer, 128, TEXT("cltStrInfo"), TEXT("Strtype:%d"), clCommonInfo.siStrType);
			MessageBox(NULL, buffer, TEXT("Err"), MB_OK|MB_TOPMOST);
		}
	}

	SI32 GetTotalSize()
	{
		SI32 size = sizeof(clCommonInfo);

		switch(clCommonInfo.siStrType)
		{
		case RANKTYPE_BANK:				size += sizeof(cltBankStrInfo);				break;
		case RANKTYPE_STOCK:			size += sizeof(cltStockStrInfo);			break;
		case RANKTYPE_MARKET:			size += sizeof(cltMarketStrInfo);			break;
		case RANKTYPE_HUNT:				size += sizeof(cltHuntStrInfo);				break;
		case RANKTYPE_HOUSE:			size += sizeof(cltHouseStrInfo);			break;
		case RANKTYPE_CITYHALL:			size += sizeof(cltCityhallStrInfo);			break;
		case RANKTYPE_POSTOFFICE:		size += sizeof(cltPostOfficeStrInfo);		break;
		case RANKTYPE_HORSEMARKET:		size += sizeof(cltHorseMarketStrInfo);		break;
		case RANKTYPE_REALESTATEMARKET:	size += sizeof(cltRealEstateMarketStrInfo); break;
		case RANKTYPE_SUMMONMARKET:		size += sizeof(cltSummonMarketStrInfo);		break;
		case RANKTYPE_LAND :			size += sizeof(cltLandStrInfo);				break;		
		case RANKTYPE_FEAST :			size += sizeof(cltFeastStrInfo);			break;
		case RANKTYPE_SUMMONHEROMARKET: size += sizeof(cltSummonHeroMarketStrInfo); break;
		case RANKTYPE_MINE :			size += sizeof(cltMineStrInfo );			break;
		case RANKTYPE_GUILD:			size += sizeof(cltGuildStrInfo );			break;
		case RANKTYPE_NEWMARKET:		size += sizeof(cltNewMarketStrInfo);		break;

		default:				size += MAX_STR_DATA_SIZE; break;
		}
		return size;
	}
	
	void IncreaseMoney(cltMoney clmoney)
	{
		clCommonInfo.clMoney.Increase(&clmoney);
	}
};



class cltStructureBasic{
public:
	SI32 siVillageUnique;	// ������ ��ġ�� ������ ����ũ��. 
	cltStrInfo clStrInfo;


	cltStructureBasic(SI32 sivillageunique);
	virtual ~cltStructureBasic();
	

	//----------------------
	// ���� 
	//----------------------
	virtual BOOL GetAcountInfo(cltAccountNum* pclaccountnum, cltBankAccount* pclAcountInfo){return FALSE;}
	virtual BOOL GetAcountInfo(SI32 personid, cltBankAccount* pclaccount){return FALSE;}
	virtual BOOL SetFee(cltFee* pclfee){return FALSE;}
	virtual GMONEY CalcFee(GMONEY money){return 0;}
	virtual bool SetBankVary(cltBankVary* pclvary){return false;}

	//----------------------
	// ��� 
	//----------------------
	virtual BOOL SetCandidate(SI32 index, cltSimpleRank* pclrank, cltSimplePerson* pclcandidate){return FALSE;}
	virtual BOOL DeleteCandidate(SI32 personid){return FALSE;}
	virtual BOOL DeleteCandidate(cltSimpleRank* pclrank){return FALSE;}
	virtual cltSimplePerson* GetCandidateInfoFromPersonID(SI32 ranktype, SI32 personid, SI32* pindex){return NULL;};
	virtual SI32 GetCandidateNum(SI32 ranktype){return 0;};
	virtual cltSimplePerson* GetCandidateInfoFromRef(SI32 ranktype, SI32 ref){return NULL;}
	virtual BOOL DeleteRank(SI32 ranktype){return FALSE;}


	//----------------------------
	// ����. 
	//----------------------------
	virtual BOOL SetRentContract(const cltRentContract* pclcontract){return FALSE;}
	virtual cltHouseUnit* GetHouseUnit(SI32 index){return NULL;}
	virtual void SetHouseUnit(SI32 index, cltHouseUnit* pclunit){}
	virtual void SetHouseApplyer(SI32 index, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract){}
	virtual cltRentApplyer* GetHouseApplyer(SI32 index){return NULL;}
	virtual	BOOL IsSameContract(const cltRentContract* pclcontract){return FALSE;};
	virtual BOOL AddApplyer(const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract ){return FALSE;}
	virtual BOOL DeleteApplyer(SI32 personid){return FALSE;}
	virtual BOOL IsEmpty(SI32 slot){return FALSE;};
	virtual cltRentApplyer* GetHouseApplyerFromPersonID(SI32 personid){return NULL;}
	virtual BOOL SetRent(SI32 slot, const cltSimplePerson* pclapplyer, const cltRentContract* pclcontract){return FALSE;}
	virtual bool IsHouseHost(SI32 personid, SI32 houseunitslot){return false;}
	virtual bool CanAddStg(SI32 houseunitslot, cltItemManagerCommon* pclItemManager, cltItem* pclitem, SI32* pitempos){return false;};
	virtual void SetItemStg(SI32 houseunitslot, SI32 stgpos, cltItem* pclitem){};
	virtual cltItem* GetStgItemPointer(SI32 houseunitslot, SI32 stgpos){return NULL;};
	virtual cltHouseUnitStorageInfo* GetStgPointer(SI32 houseunitslot){return NULL;}
	virtual void InitHouseApplyer(){}


	cltStrInfo* GetStrInfo();
	void SetStrInfo(cltStrInfo* pclinfo);


};

class cltStructureMngBasic{
public:
	cltStructureMngBasic(SI32 sitabctrlnum, cltCharManager* pclcm, 	SI32 ranktype, TCHAR *strFileName );	
	virtual ~cltStructureMngBasic();
	
	SI32 siTabCtrlNum;												// �� ��Ʈ���� � �ִ°� ?

	SI32 siRankType;												// � ������ �ǹ��ΰ�. 
	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltStructureBasic*, MAX_VILLAGE_NUMBER>		pclStruct;
#else
	cltStructureBasic* pclStruct[MAX_VILLAGE_NUMBER];				// ��� ���������� �� �ǹ����� ��ü 
#endif

	// Ŭ���̾�Ʈ
	cltStrInfo	clClientStrInfo;									// Ŭ���̾�Ʈ�� �˰� �־�� �� �ǹ� ����. 

	cltCharManager* pclCM;											// ĳ���� �Ŵ��� ������
	
	SI32 CharUnique;												// ĳ���� ����ũ
	SI32 siVillageUnique;											// �ش� ���� ����ũ 

	BOOL DlgRectInitSwitch;
	RECT DlgRect;

	TCHAR szTitle[128];												// Ÿ��Ʋ 

	SI32 siServerResponseValue;										// ������ ������ �����

	TCHAR m_strFileName[ _MAX_PATH ];								// �ʻ�ȭ ���ϸ�( siPortaitID �� 0 �̶�� strFileName ���� ��ü�ϰ� ����. )

	bool UpdateChiefSwitch;
	bool bDrawPortraitSwitch;

	TCHAR szMainExplain[ 1024 ];
	DWORD dwLastExplainTick;

	cltStructureRepairDlg* pclStructureRepairDlg;

	BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	// �����κ��� ���� �ǹ� ������ ������ Ŭ���̾�Ʈ�� �ǹ���  �����Ѵ�. 
	void SetClientStrInfo(cltStrInfo* pclinfo);

	// �ʻ�ȭ�� �׷��ش�. 
	void DrawPortrait(TCHAR *paccountid);

	// ���� ����â�� �����Ѵ�. 
	BOOL SetMainExplain(HWND hdlg, TCHAR* pstr);

	// ���� ���ϰ� ó�� �Լ�. 
	virtual void ServerRtnValOperate();
	
	virtual void OnTimer() {};

	void DeleteTabDlg();
 
	// ���� ������ �����ش�. 
	BOOL ShowChief(HWND hDlg, SI32 dlgitem, cltSimplePerson* pclperson, TCHAR *paccountid);

	void GetTitleText(SI32 villageunique);

	// ���� ȯ�� �λ縻ǥ�� . 
	virtual void GreetingMsg(HWND hDlg)		= 0;
	virtual void Do_WM_INITDIALOG(SI32 charunique);

	cltStrInfo* GetStrInfo(SI32 villageunique);
	void SetStrInfo(SI32 villageunique, cltStrInfo* pclinfo);

	bool GetHighestLevelVillage(SI32* villageunique,SI32* level);

	// Ư�� �ǹ��� ���� �ڱ��� �����Ѵ�
	void SetMoney(SI32 villageunique, cltMoney* pclmoney);

	// Ư�� �ǹ��� ���� �ں����� �����Ѵ�
	void SetBaseMoney(SI32 villageunique, cltMoney* pclmoney);

	// �ǹ��� Ư�� �⵵�� ������ �����Ѵ� 
	void SetTax( SI32 villageunique, UI16 year, cltMoney* pclTax );

	// �ǹ��� Ư�� �⵵�� ���ε� ������ �����Ѵ�
	void SetPaidTax( SI32 villageunique, UI16 year, cltMoney* pclPaidTax );
	
	void RequestStrInfo( SI32 strType );

	// �ǹ� ���� ���̾�α׸� �����Ѵ� 
	void CreateStructureRepairDlg( HINSTANCE hInst, HWND hParent );

	void CommonAction(cltTime* pcltime);

	DWORD tickTemp;
	BOOL  bSetNeedItem;

	NStrBaseDlg		*pStrBaseDlg;			// Ǯ��ũ�� ����� ��� ���̾�α� ������, â����ϰ��� NULL
};

#endif
 
