#ifndef _HORSEMARKET_H
#define _HORSEMARKET_H

#include <Directives.h>

#include "..\StructureClass\StructureClass.h"

//#include <Stdio.h>

//#include "..\..\Common\Item\ItemCommon\cltitem.h"

#define MAX_HORSEMARKET_ORDER_NUMBER			10000
#define MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER	80

#define	MAX_HORSEMARKET_TAB_NUMBER				4

class cltTaxPaymentListDlg;



//-------------------------------------------------
// �� �ֹ� ����
//-------------------------------------------------
class cltHorseOrder
{
public:
	SI32			siIndex;		// �ֹ� ������ �ĺ���(�ε���)
	SI32			siPersonID;		// �ֹ��� �� PersonID
	GMONEY			siPrice;		// �ֹ� ����. 
	cltDate			clDate;			// �ð� ����. 
	cltHorse		clHorse;		// �� ����

	cltHorseOrder()
	{
		Init();
	}

	void Init()
	{
		siIndex = 0;
		siPersonID = 0;
		siPrice = 0;
		
		clHorse.Init();
	}

	void Set( cltHorseOrder *pclOrder )
	{
		siIndex = pclOrder->siIndex;
		siPersonID = pclOrder->siPersonID;
		siPrice = pclOrder->siPrice;
		clDate.Set( &pclOrder->clDate );
		clHorse.Set( &pclOrder->clHorse );
	}

};


//-------------------------------------------------
// �������� �纹��
//-------------------------------------------------
class cltHorseMarket : public cltStructureBasic{
private:

public:
	cltHorseMarket(SI32 sivillageunique);
	~cltHorseMarket();

};

//-----------------------------------------------
// �纹�� ������. 
//-----------------------------------------------
class cltHorseMarketManager : public cltStructureMngBasic{
public:

	cltHorseMarketManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltHorseMarketManager();

	void GetTitleText(SI32 villageunique);

	// ���� ȯ�� �λ縻ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// �纹�ø� �ż��Ѵ�.
	BOOL CreateHorseMarket(SI32 siunique);

	void DispMsgInfo( HWND hDlg );
	void ShowHorseMarketInfo();

	void ShowMyHorseInfo( HWND hDlg );
	void ShowMyAccountInfo( HWND hDlg );

	void ShowResponseOrder( HWND hDlg );

	BOOL ShowFeeRate(HWND hDlg, SI32 rate);
	
	BOOL ShowFee( HWND hDlg );
	BOOL ShowRealFee(HWND hDlg, GMONEY price);

	void AddOrder( cltHorseOrder *pclOrder );
	void DelOrder( SI32 orderIndex );
	void UpdatePrice( int index, cltHorseOrder *pclOrder );
	
	void Action( bool bdaychangedswitch );

public:	
	BOOL						m_bMainExplain;

	cltHorseOrder				clMyAccount;
	
	cltHorseOrder				*pclHorseOrder;
	SI32						siAddStartIndex;
	SI32						siTotalOrderNumber;

	BOOL						bSelectedSwitch;
	SI32						siHorseUnique;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltHorseOrder, MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER>		clResponseOrder;
#else
	cltHorseOrder				clResponseOrder[ MAX_HORSEMARKET_RESPONSE_ORDER_NUMBER ];
#endif
	SI32						siTotalResponseOrderNumber;
	BOOL						bShowResponseOrderSwitch;
	
	SI32						siSelectedIndex;
	SI32						siHorsePriceType;
};

#endif
