// �ֽ�
#pragma once

#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"


class CEachPersonTradeOrderInfo;
class CNPrivateTradeDlg;
class CLibListMgr;
class CListView;
class CComboBox;
class CButton;
class CStatic;
class CEdit;




class CNTradeChild2 : public CDialogController
{
	
public:
	CNTradeChild2();
	~CNTradeChild2();
	


	
	static void CALLBACK StaticNTradeChild2Proc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NTradeChild2Proc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Create(CControllerMgr *pParent);
	void LoadStockList();
	bool IsStockListChanged();
	void Show();
	void Hide();
	CEdit               *m_pNPTrade2Edit;
	CNPrivateTradeDlg*   m_pParent;
	SI32                 m_siSelectedVillageIndex;
	CComboBox           *m_pNPTrade2Combo;

private:
	//UI32	        	m_uiLastAcceptFrame;	// �ŷ��� �־����� ����
	SI32	        	m_SILastAcceptTime;		// �ŷ��� �־����� ����	-> �����ӿ��� Ŀ��Ʈ Ÿ���� �����ϵ��� ���� 
	CButton             *m_pNPTrade2Button1;
	CButton             *m_pNPTrade2Button2;
	
	
	CStatic             *m_pNPTrade2Static1;
	CStatic             *m_pNPTrade2Static2;
	//SI32				m_siStockKindList[MAX_STOCK_KIND_IN_ACOUNT];	// �ֽ� ����Ʈ ( ���� )
	//SI32				m_siStockNumList[MAX_STOCK_KIND_IN_ACOUNT];		// �ֽ� ����Ʈ ( ���� )




};