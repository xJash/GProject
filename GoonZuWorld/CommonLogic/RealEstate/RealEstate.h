#ifndef _REALESTATEMARKET_H
#define _REALESTATEMARKET_H

#include <Directives.h>

#include "..\common\Char\CharCommon\Char-EconomyInfo.h"

#include "..\StructureClass\StructureClass.h"

#define MAX_REALESTATEMARKET_ORDER_NUMBER			4000
#define MAX_REALESTATEMARKET_RESPONSE_ORDER_NUMBER	100

#define	MAX_REALESTATEMARKET_TAB_NUMBER				4

class cltTaxPaymentListDlg;

class cltRealEstateDetailInfo
{
public:
	cltRealEstateDetailInfo() { ZeroMemory( this, sizeof( cltRealEstateDetailInfo ) ); };
	~cltRealEstateDetailInfo() {};
	
	SI32				siVillageUnique;
	SI32				siHouseIndex;

	GMONEY				siCurrentRentFee;
	GMONEY				siRentFee;
	SI32				siRentPeriod;
	cltDate				clContractDate;

	SI32				siItemNum;
	SI32				siStableNum;
	SI32				siHorseNum;

};

//-------------------------------------------------
// �ε��� �ֹ� ����
//-------------------------------------------------
class cltRealEstateOrder
{
public:
	SI32			siIndex;			// �ֹ� ������ �ĺ���(�ε���)
	SI32			siPersonID;			// �ֹ��� �� PersonID
	GMONEY			siPrice;			// �ֹ� ����. 
	cltDate			clDate;				// �ð� ����. 

	SI32			siVillageUnique;	// ���� �ε��� �ҼӸ��� 
	SI32			siHouseIndex;		// ���� ��ȣ

	cltRealEstateOrder()
	{
		Init();
	}

	void Init()
	{
		siIndex = 0;
		siPersonID = 0;
		siPrice = 0;
		siVillageUnique = 0;
		siHouseIndex = 0;
	}

	void Set( SI32 orderindex, SI32 personid, GMONEY price, cltDate *pclDate, SI32 villageunique, SI32 houseindex )
	{
		siIndex = orderindex;
		siPersonID = personid;
		siPrice = price;
		clDate.Set( pclDate );
		siVillageUnique = villageunique;
		siHouseIndex = houseindex;
	}

	void Set( cltRealEstateOrder *pclOrder )
	{
		siIndex = pclOrder->siIndex;
		siPersonID = pclOrder->siPersonID;
		siPrice = pclOrder->siPrice;
		clDate.Set( &pclOrder->clDate );
		siVillageUnique = pclOrder->siVillageUnique;
		siHouseIndex = pclOrder->siHouseIndex;
	}

};

//-------------------------------------------------
// �������� �Ű�
//-------------------------------------------------
class cltRealEstateMarket : public cltStructureBasic{
private:

public:
	cltRealEstateMarket(SI32 sivillageunique);
	~cltRealEstateMarket();

};

//-----------------------------------------------
// �Ű� ������. 
//-----------------------------------------------
class cltRealEstateMarketManager : public cltStructureMngBasic{
public:

	cltRealEstateMarketManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltRealEstateMarketManager();

	void GetTitleText(SI32 villageunique);

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// �Ű��� �ż��Ѵ�.
	BOOL CreateRealEstateMarket(SI32 siunique);

	//void DispMsgInfo( HWND hDlg );
	//void ShowRealEstateMarketInfo();

	//void ShowMyHorseInfo( HWND hDlg );
	//void ShowMyAccountInfo( HWND hDlg );

	void ShowResponseOrder( HWND hDlg );

	BOOL ShowFeeRate(HWND hDlg, SI32 rate);
	
	BOOL ShowFee( HWND hDlg );
	BOOL ShowRealFee(HWND hDlg, GMONEY price);

	void AddOrder( cltRealEstateOrder *pclOrder );
	void DelOrder( SI32 orderIndex );
	void UpdatePrice( int index, cltRealEstateOrder *pclOrder );

	bool IsExistOrder( SI32 personid, SI32 villageunique, SI32 houseindex);

	// �� �ֹ� ���� ����
	void AddMyOrder( cltRealEstateOrder *pclOrder );
	void DelMyOrder( SI32 orderIndex );

	void SetMyRealEstateList();

	void ShowMyRealEstateList(HWND hDlg);
	void ShowMyOrderList(HWND hDlg);

	void ShowDetailInfo( HWND hDlg );
	
	void Action( bool bdaychangedswitch );

public:	
	BOOL						m_bMainExplain;
	
	cltRealEstateOrder			*pclRealEstateOrder;
	SI32						siAddStartIndex;
	SI32						siTotalOrderNumber;

	BOOL						bSelectedSwitch;


#ifdef _SAFE_MEMORY
	NSafeTArray<cltRealEstateUnit, MAX_REAL_ESTATE_NUMBER_PER_PERSON>		clMyRealEstate;
	NSafeTArray<cltRealEstateOrder, MAX_REAL_ESTATE_NUMBER_PER_PERSON>		clMyOrder;
#else
	cltRealEstateUnit			clMyRealEstate[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];
	cltRealEstateOrder			clMyOrder[ MAX_REAL_ESTATE_NUMBER_PER_PERSON ];
#endif
	BOOL						bShowMyOrderSwitch;

	
#ifdef _SAFE_MEMORY
	NSafeTArray<cltRealEstateOrder, MAX_REALESTATEMARKET_RESPONSE_ORDER_NUMBER>	clResponseOrder;
#else
	cltRealEstateOrder			clResponseOrder[ MAX_REALESTATEMARKET_RESPONSE_ORDER_NUMBER ];
#endif
	SI32						siTotalResponseOrderNumber;

	BOOL						bShowResponseOrderSwitch;

	cltRealEstateDetailInfo		clDetailInfo;
	BOOL						bRequestDetailInfo;
	BOOL						bUpdateDetailInfo;

	
	SI32						siSelectedIndex;					// ���� �ֹ� ����Ʈ
	SI32						siMyRealEstateSelectedIndex;		// �� �ε��� ����Ʈ
	SI32						siMyOrderSelectedIndex;				// �� �ֹ� ����Ʈ 

};

#endif
