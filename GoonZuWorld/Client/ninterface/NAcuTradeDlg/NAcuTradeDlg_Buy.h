// [����] ��ť �ŷ�â ������
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"

class cltWorldMoneyTradeList;

class CNAcuTradeDlg_Buy : public CDialogController
{
	// ��������
private:
	InterfaceFactory	m_InterfaceFactory;
	SI32				m_siSelectedIndex[ MAX_WORLDMONEY_TRADELIST_NUM ];


	// �Լ�����
public:
	CNAcuTradeDlg_Buy();
	~CNAcuTradeDlg_Buy();

	void Create(CControllerMgr* pParent);

	static void CALLBACK StaticAcuTradeDlg_BuyProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAcuTradeDlg_BuyProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void Refresh( void );

private:
	void OrderToBuy( void );
	bool IsEmptyTradeList( cltWorldMoneyTradeList* pclList );
	void SwapTradeList( cltWorldMoneyTradeList* pclLParam, cltWorldMoneyTradeList* pclRParam );
	void SwapTradeIndex( SI32* psiLParam, SI32* psiRParam );
	void SortTradeList( cltWorldMoneyTradeList* pclTradeList );
	void SetTradeListBox( cltWorldMoneyTradeList* pclTradeList );
};
