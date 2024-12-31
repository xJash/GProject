#ifndef _NREALESTATEMARKETDLG_H
#define _NREALESTATEMARKETDLG_H

#include "../StrBaseDlg/StrBaseDlg.h"
#include "../../../CommonLogic/RealEstate/RealEstate.h"


class NRealEstateMarketDlg : public NStrBaseDlg
{
public:
	NRealEstateMarketDlg();
	virtual ~NRealEstateMarketDlg();

	void Create();

	void GreetingMsg();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

};

// �ε��� ����
class NRealEstateMarketBuyDlg : public NStrTabDlg
{
public:
	enum {
		BUTTON_BUY,
		BUTTON_REFRESH,

		LISTBOX_HOUSE,
		EDITBOX_EXPLAIN,
	};

	NRealEstateMarketBuyDlg();
	virtual ~NRealEstateMarketBuyDlg();

	void InitDlg();
	void Action();

	void ShowResponseOrder();
	void ShowResponseExplain();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

};



// �ε��� �ȱ�
class NRealEstateMarketUserDlg : public NStrTabDlg
{
public:
	enum {
		BUTTON_SELL,
		BUTTON_CANCELORDER,

		EDITBOX_REALFEE,
		EDITBOX_SELLPRICE,
		EDITBOX_SELLPRICECHAR,

		LISTBOX_MYHOUSE,
		LISTBOX_MYORDER,
		EDITBOX_EXPLAIN,

		STATICTEXT_FEERATE,
	};

	NRealEstateMarketUserDlg();
	virtual ~NRealEstateMarketUserDlg();

	void InitDlg();
	void Action();

	void ShowMyRealEstateList();
	void ShowMyOrderList();

	void ShowMyRealEstateInfo();
	void ShowMyOrderInfo();

	BOOL ShowFee();
	BOOL ShowRealFee(GMONEY price);

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

};


// �Ű� ��� 
class NRealEstateMarketChiefDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_FEERATE,
		BUTTON_SETFEERATE
	};
	NRealEstateMarketChiefDlg();
	virtual ~NRealEstateMarketChiefDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};


#endif
