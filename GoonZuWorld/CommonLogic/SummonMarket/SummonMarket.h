#ifndef _SUMMONMARKET_H
#define _SUMMONMARKET_H

#include <Directives.h>

#include "..\StructureClass\StructureClass.h"

//-------------------------------------
// Common
//-------------------------------------
#include "PersonInfo.h"

#define MAX_SUMMONMARKET_ORDER_NUMBER			10000
#define MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER	60
#define MAX_SUMMONMARKET_ORDER_PER_PERSON		3

#define	MAX_SUMMONMARKET_TAB_NUMBER				4

class cltTaxPaymentListDlg;


//-------------------------------------------------
// ��ȯ�� �ֹ� ����
//-------------------------------------------------
class cltSummonOrder
{
public:
	SI32			siIndex;		// �ֹ� ������ �ĺ���(�ε���)
	SI32			siPersonID;		// �ֹ��� �� PersonID
	GMONEY			siPrice;		// �ֹ� ����. 
	cltDate			clDate;			// �ð� ����. 

	cltSummon		clSummon;		// ��ȯ������

	SI32			siSelectPersonID;	// ���� ������ PersonID (0�ϰ�� �����ŷ��ƴ�)


	cltSummonOrder()
	{
		Init();
	}

	void Init()
	{
		siIndex = 0;
		siPersonID = 0;
		siPrice = 0;

		clSummon.Init();

		siSelectPersonID = 0;
	}

	void Set( cltSummonOrder *pclOrder )
	{
		siIndex = pclOrder->siIndex;
		siPersonID = pclOrder->siPersonID;
		siPrice = pclOrder->siPrice;
		clDate.Set( &pclOrder->clDate );

		clSummon.Set( &pclOrder->clSummon );

		siSelectPersonID = pclOrder->siSelectPersonID;
	}

};


//-------------------------------------------------
// �������� ��ȯ���ŷ���
//-------------------------------------------------
class cltSummonMarket : public cltStructureBasic{
private:

public:
	cltSummonMarket(SI32 sivillageunique);
	~cltSummonMarket();

};


//-----------------------------------------------
// ��ȯ���ŷ��� ������. 
//-----------------------------------------------
class cltSummonMarketManager : public cltStructureMngBasic{
public:

	cltSummonMarketManager(cltCharManager* pclCM, SI32 gamemode, SI32 ranktype, TCHAR *strFileName );
	~cltSummonMarketManager();

	void GetTitleText(SI32 villageunique);

	// ���� ȯ�� �λ��ȯ��ǥ�� . 
	void GreetingMsg(HWND hDlg);
	void Do_WM_INITDIALOG(SI32 id);

	// ��ȯ���ŷ��Ҹ� �ż��Ѵ�.
	BOOL CreateSummonMarket(SI32 siunique);

	void DispMsgInfo( HWND hDlg );
	void ShowSummonMarketInfo();

	BOOL ShowFeeRate(HWND hDlg, SI32 rate);
	
	BOOL ShowFee( HWND hDlg );
	BOOL ShowRealFee(HWND hDlg, GMONEY price);

	void AddOrder( cltSummonOrder *pclOrder );
	void DelOrder( SI32 orderIndex );
	void UpdatePrice( int index, cltSummonOrder *pclOrder );	

	// �� �ֹ� ���� ����
	void AddSummonKind( HWND hDlg );


	void AddMyOrder( cltSummonOrder *pclOrder );
	void DelMyOrder( SI32 orderIndex );

	void ShowResponseOrder( HWND hDlg );
	void ShowResponseExplain( HWND hDlg );

	void ShowMySummonInfo( HWND hDlg );
	void ShowMyOrderInfo( HWND hDlg );

	void ShowMySummonList(HWND hDlg);
	void ShowMyOrderList(HWND hDlg);

	void DrawSummonPortrait( HWND hDlg );

	void Action( bool bdaychangedswitch );

public:	
	BOOL						m_bMainExplain;

	cltSummonOrder				*pclSummonOrder;
	SI32						siAddStartIndex;
	SI32						siTotalOrderNumber;

	BOOL						bSelectedSwitch;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSummonOrder, MAX_SUMMONMARKET_ORDER_PER_PERSON>	clMyOrder;
#else
	cltSummonOrder				clMyOrder[ MAX_SUMMONMARKET_ORDER_PER_PERSON ];
#endif
	BOOL						bShowMyOrderSwitch;

#ifdef _SAFE_MEMORY
	NSafeTArray<cltSummonOrder, MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER>	clResponseOrder;
#else
	cltSummonOrder				clResponseOrder[ MAX_SUMMONMARKET_RESPONSE_ORDER_NUMBER ];
#endif

	SI32						siTotalResponseOrderNumber;
	BOOL						bShowResponseOrderSwitch;
	
	SI32						siSelectedIndex;
	SI32						siMySummonSelectedIndex;		// �� ��ȯ�� ����Ʈ
	SI32						siMyOrderSelectedIndex;			// �� �ֹ� ����Ʈ 

	SI32						m_siKind;
	SI32						m_siSelectList;


	HBITMAP						m_hSummonPortraitBitmap;
	SI32						m_siPortraitSummonKind;

	SI32						m_siCurrentPage;				// [����] ���� �������� ����. => 2008-7-19//�ֹ� ����Ʈ ��û�� ���� ��ġ
	SI32						m_siTotalPageNum;				// [����] ��ü ������ ��.	  => 2008-7-19

};

#endif
