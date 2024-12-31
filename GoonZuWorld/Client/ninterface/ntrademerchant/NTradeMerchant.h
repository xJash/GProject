#pragma once 

#include "../../InterfaceMgr/DialogController.h"

class cltItem;

class CImageStatic;
class CButton;
class CComboBox;
class CListView;
class CEdit;
class CStatic;
class CList;

class CTradeMerchantNPC;

class CNTradeMerchantDlg : public CDialogController
{
public:

	CNTradeMerchantDlg();
	~CNTradeMerchantDlg();

	void Create();

	static void CALLBACK StaticCallBackDialogNTradeMerchantDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogNTradeMerchantDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Action();

	void SetTradeMerChant(SI32 id);

	bool IsInventoryChanged();
	void LoadInventoryData();

	void Set( CTradeMerchantNPC *pTradeMerchantNPC );
	void LoadTradeMerchantNPCBuyData();

	void SellToNPCSuccess();

	CTradeMerchantNPC *m_pTradeMerchantNPC;

private:
	SI32				m_siImageType;	// ������ �̹��� ����
	SI32				m_siImageIndex;	// ������  �̹��� �ε���

	SI32 m_siNPCKind;	
	SI32 m_siSelectedIndex;
	
	cltItem	*m_pclItem;

	CStatic*	m_pStatic[3];		// 0 : ���� ���� ��, 1: ������
	CEdit*		m_pEdit;		

	CListView*	m_pListView;

	CButton*	m_pButtonSellItem;
	CButton*	m_pButtonClose;
};

