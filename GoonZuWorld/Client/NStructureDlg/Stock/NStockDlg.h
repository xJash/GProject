#ifndef _NSTOCKDLG_H
#define _NSTOCKDLG_H

#include "../StrBaseDlg/StrBaseDlg.h"
#include "../NLib/NUpdateTimer.h"//�ֽİ���� 5�� ���������� ���

class CComboBox;

// ���� �⺻
class NStockDlg : public NStrBaseDlg
{
public:
	NStockDlg();
	virtual ~NStockDlg();

	void Create();

	void GreetingMsg();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

};

// �ֽ� �Ÿ� 
class NStockUserDlg : public NStrTabDlg
{
public:
	enum {
		BUTTON_BUY,
		BUTTON_SELL,
		BUTTON_CANCEL_ORDER,

		COMBO_BUY_KIND,
		COMBO_SELL_KIND,

		EDIT_BUY_AMOUNT,
		EDIT_BUY_PRICE,
		EDIT_SELL_AMOUNT,
		EDIT_SELL_PRICE,

		EDIT_FEERATE,

		LIST_HAVESTOCK,
		LIST_ORDERSTOCK,
		LIST_MOST_ORDER_SELL,
		LIST_MOST_ORDER_BUY,
		
		EDIT_AVERAGE_BUY,
		EDIT_AVERAGE_SELL

	};

	NStockUserDlg();
	virtual ~NStockUserDlg();

	void InitDlg();

	void Action();

	// ���� �ֽ��� ǥ���Ѵ�. 
	void SetHaveStock();

	// �ֹ� ������ ����Ʈ �ڽ��� �߰��Ѵ�. 
	void SetStockOrderList();

	// �ż� ������ �޺� �ڽ��� �߰��Ѵ�.
//	void SetComboBuyKind();

	// �ŵ� ������ �޺� �ڽ��� �߰��Ѵ�. 
	void SetComboSellKind();

	void ShowFeeInfo();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );
};

// ���� 
class NStockUser2Dlg : public NStrTabDlg
{
public:
	enum {
		COMBO_BUYER_TYPE, // ���ְ� ��³� �Ϲ����� �����
		COMBO_VILLAGE,	  // �ֽ��� �� ����

		EDIT_DATE,		  // ���� ���� �ð�
		EDIT_TOTAL_INCREASESTOCK_AMOUNT,
		EDIT_LEFTSTOCK_AMOUNT,
		EDIT_CURRENT_STOCKPRICE,
		EDIT_BUYSTOCK_AMOUNT,
		EDIT_LIMITBUYSTOCK_AMOUNT,
		EDIT_STARTDAY,	// ���� ������!!

		BUTTON_BUYSTOCK,

		LIST_STOCKHOLDER	// ���� ���� ���
	};

	SI32 m_siSelectVillageIndex_;
	/*
	#ifdef _DEBUG // kkm
	enum {
	COMBO_BUYER_TYPE, // ���ְ� ��³� �Ϲ����� �����
	COMBO_VILLAGE,	  // �ֽ��� �� ����

	EDIT_DATE,		  // ���� ���� �ð�
	EDIT_TOTAL_INCREASESTOCK_AMOUNT,
	EDIT_LEFTSTOCK_AMOUNT,
	EDIT_CURRENT_STOCKPRICE,
	EDIT_BUYSTOCK_AMOUNT,

	BUTTON_BUYSTOCK,

	LIST_STOCKHOLDER	// ���� ���� ���
	};
	#else
	enum {
	COMBO_STOCKBID_ITEM,

	EDIT_TOTAL_AMOUNT,
	EDIT_BEGIN_PRICE,

	EDIT_AMOUNT,
	EDIT_PRICE,

	EDIT_DATE,

	BUTTON_BIDSTOCK,
	BUTTON_REFRESH_LIST,

	LIST_STOCKBIDDER
	};
	#endif
	*/	
	NStockUser2Dlg();
	virtual ~NStockUser2Dlg();

	void InitDlg();

	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	// �޺��ڽ� �ؽ�Ʈ�� ���� ����
	void NComboBoxSort(CComboBox* in_pCombo );
};

// ��� �޴� 
class NStockChiefDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_FEERATE,
		BUTTON_SETFEERATE
	};

	NStockChiefDlg();
	virtual ~NStockChiefDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};

// ���� û��
class NStockPublicSubscriptionDlg : public NStrTabDlg
{
public:
	enum {
		COMBO_VILLAGELIST,
		BUTTON_ORDER,
	};

	NUpdateTimer	m_kUpdateTimer_ButtonDisable;

	NStockPublicSubscriptionDlg();
	virtual ~NStockPublicSubscriptionDlg();

	void InitDlg();
	
	void Action();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );

	virtual void Show();
};

#endif