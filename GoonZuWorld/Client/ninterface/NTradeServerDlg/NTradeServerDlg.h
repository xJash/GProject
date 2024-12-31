#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../../../NLib/NUpdateTimer.h"

class NStrInventory;
class CListView;
class CComboBox;

class CNTradeServerSellDlg;
class CNTradeServerBuyDlg;

// Ʈ���̵� ����â
class CNTradeServerBaseDlg : public CDialogController
{
public:

	InterfaceFactory	m_InterfaceFactory_;

	CNTradeServerSellDlg* m_TradeServerSell;
	CNTradeServerBuyDlg*  m_TradeServerBuy;

	CNTradeServerBaseDlg();
	~CNTradeServerBaseDlg();

	void Create();
	void Action();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void ShowBuyDlg();

	static void CALLBACK StaticCallBackDialogNTradeServerBaseDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNTradeServerBaseDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

};

class CNTradeServerSellDlg : public CDialogController
{
public:

	InterfaceFactory	m_InterfaceFactory_;

	NStrInventory*		m_pMyInventory;
	NStrInventory*		m_pStgItem;

	bool			m_bMyInven;

	CNTradeServerSellDlg();
	~CNTradeServerSellDlg();

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	void Action();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	static void CALLBACK StaticCallBackDialogNTradeServerSellDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNTradeServerSellDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
};

class CNTradeServerBuyDlg : public CDialogController
{
public:

	InterfaceFactory	m_InterfaceFactory_;
	SI32				m_siImageType;	// ǰ�� �ε���
	SI32				m_siImageIndex;	// ǰ�� �ε���

	SI64				siItemPrice; // ��ǰ�� �ü�
	SI64				siWorldMoneyPrice; // ��ť�� �ü�

	bool				m_bWorldTradeTax;			// ���� ���� ����
	SI32				m_siSpecialTaxRange;		// Ư���� ���� ����
	SI32				m_siSpecialTaxRate;		// Ư������

	NUpdateTimer		m_kUpdateTimer_ComboBoxDisable;

	CNTradeServerBuyDlg();
	~CNTradeServerBuyDlg();

	void Create( CControllerMgr *pParent );
	void Show();
	void Hide();
	void Action();

	void RefreshOrder();

	BOOL ShowItemListInCombo( CComboBox *pCombo, SI32 itemtypeunique, bool btradeinterface );

	void ShowItemImage(char* pName);
	void ShowNationFlag(SI32 index) ;

	void StartComboBoxDisable();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
	
	static void CALLBACK StaticCallBackDialogNTradeServerBuyDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNTradeServerBuyDlg( UINT nEvent, int nControlID, CControllerObj* pControl );
};