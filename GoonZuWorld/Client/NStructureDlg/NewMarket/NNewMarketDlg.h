#ifndef _NNewMarket_H
#define _NNewMarket_H


#include "../../InterfaceMgr/DialogController.h"
#include "../StrBaseDlg/StrBaseDlg.h"

class NStrInventory;
class CComboBox;
class cltItem;

class NNewMarketDlg : public NStrBaseDlg
{

public:
	NNewMarketDlg();
	virtual ~NNewMarketDlg();

	void Create();

	void GreetingMsg();
	
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY  );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );

	void NDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );

};

// ���� ��ǰ �ȱ�
class NNewMarketUserSellDlg : public NStrTabDlg
{
public:
	enum
	{
		 CREATE_BANK_MSGBOX = 1		// ���� ����.
		,SELL_MSGBOX 				// �Ǹ� ���.
		,RECALL_MSGBOX				// �Ǹ� �ֹ� ������ ȸ��.
	};

	enum
	{
		 LISTVIEW_MYINVENTORY
		,LISTVIEW_MARKETSTORAGE
		,EDIT_AMOUNT
		,EDIT_PRICE
		,EDIT_FEERATE
		,EDIT_FEE
		,EDIT_MONEY_UNIT
		,BUTTON_SELL
		,BUTTON_CANCEL_ORDER
		,BUTTON_SEARCHPRICE
		,EDIT_ITEMPRICE1
		,EDIT_ITEMPRICE2
		,EDIT_ITEMPRICE3
		,EDIT_ITEMPRICE4
		,EDIT_BACKGROUND
		,STATIC_TOTALNUM
		,STATIC_MONEYUNIT
	};

	NNewMarketUserSellDlg();
	virtual ~NNewMarketUserSellDlg();

	void 	InitDlg();
	void 	Action();
	void 	NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
	void 	RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

public:
	void	SetMyInventory( void );						// �� �κ� ���� ����.
	void	ShowFeeRate( void );						// ������ ����.
	void	ShowFee( SI32 _ItemNum, GMONEY _Price );	// ������ ������.
	bool	IsSell( bool _bEditBoxClear = false );		// ������ �Ǹ� ���� ����.
	void	SetNewMarketAccount(cltGameMsgResponse_NewMarketAccount* pNewMarketAccount);
	void	RefreshSellInfo( void );
	void	SetStgItemPrice( void );
	void	SetScrollStgItemPrice( void );
	void	CancelOrder( void );
	void	SetStrInventory( void );
		
private:
	NStrInventory*	m_pMyInventory;
	NStrInventory*	m_pStgItem;

	float			m_fFeeRate; 
	SI32			m_siItemNum;
	GMONEY			m_Tax;
	GMONEY			m_Price; 

	cltNewMarketAccount	m_clNewMarketAccount;
	
};



// ���� ��ǰ ���
class NNewMarketUserBuyDlg : public NStrTabDlg
{
public:
	enum 
	{
		 STATIC_PRICECOND
		,CHECK_PRICECOND
		,COMBO_ITEMTYPE
		,COMBO_ITEM
		,BUTTON_REFRESH
		,BUTTON_BUY
		,BUTTON_ITEMMALL
		,EDIT_AMOUNT
		,EDIT_PRICECOND
		,EDIT_ITEMPRICE
		,EDIT_EXPLAIN
		,IMAGESTATIC_ITEMBACK
		,LIST_ORDERLIST
		,EDIT_EXPLAINCHAR 
		,STATIC_ITEMNAME
		,STATIC_ITEMTYPE
		,STATIC_ITEMINFO
		,STATIC_CHARINFO
	};

	NNewMarketUserBuyDlg();
	virtual ~NNewMarketUserBuyDlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
	
public:
	

private:
	

};




// ���� ��� �޴�
class NNewMarketChiefDlg : public NStrTabDlg
{
public:
	enum 
	{
		EDIT_FEERATE,
		BUTTON_SETFEERATE,
		BUTTON_SETFEERATE_DOWN,
		BUTTON_SETFEERATE_UP
	};

	NNewMarketChiefDlg();
	virtual ~NNewMarketChiefDlg();

	void	InitDlg();
	void	Action();

	void	NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	float	m_fFeeRate; 
};


// ���� ��ǰ ���
class NNewMarketUserBuyDlgSub :public CDialogController
{
public:
	
	NNewMarketUserBuyDlgSub();
	virtual ~NNewMarketUserBuyDlgSub();

	void	Create( void );
	void	Action( void );
	void	Init( void );	

	static	void CALLBACK StaticCallBackDialogNNewMarketUserBuyDlgSub( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
			void CALLBACK CallBackDialogNNewMarketUseBuyDlgSub( UINT nEvent, int nControlID, CControllerObj* pControl );


public:
	BOOL 		ShowItemTypeListInCombo( void );															// ������ Ÿ�� ����Ʈ �����.
	BOOL 		ShowItemListInCombo( CComboBox *pCombo, SI32 itemtypeunique );								// ������ Ÿ�Ժ� ������ ����Ʈ �����.
	void 		VDirectDrawToBackScreen( LPDIRECTDRAWSURFACE7 lpBackScreen, SI32 ScreenRX, SI32 ScreenRY );// ������ ����Ʈ�� ���õ� ������ �׸���.
	void 		InputAction( void );																			// ����Ʈ �ڽ��� �ѱ۹��ڸ� ������ �޽����� ���� �ʾƼ� ������ ���� ������ Ȯ���� �޶����� ���� ������ ��������.
	SI32 		GetTextOneSize( void );
	void 		ShowMyCharInfo( SI32 _siItemUnique );
	void 		ShowItemExpalan( SI32 _siItemUnique, SI32 _siServerUnique = 0 );
	void 		RefreshOrder( void );
	void 		SetProductListFromUnique( SI32 _siItemunique );
	void 		RequestNewMarketOrderList( SI32 itemunique );
	void		RequestNewMarketOrderListRefresh( void );
	void 		SetItemList( cltGameMsgResponse_NewMarketItemList* pNewMarketItemList );
	bool 		IsCheckItem( cltItem* _pclItem );
	void 		SetPage( SI32 MaxPage );
	void		RefreshItemExpalan( void );

public:
	InterfaceFactory	m_InterfaceFactory;

	SI32				m_siImageIndex;
	SI32				m_siImageType;

	SI16				m_siRequestItemUnique;
	SI16				m_siRequestPage;
	SI16				m_siMaxPage;

	SI16				m_siSelectOrderIndex;
	bool				m_bActionRequestItemList;
	
	NSafeTArray<cltNewTradeOrder, MAX_NEWMARKET_ITEMLIST> clNewTradeOrder;
	//cltNewTradeOrder	clNewTradeOrder[MAX_NEWMARKET_ITEMLIST]; 
};


#endif