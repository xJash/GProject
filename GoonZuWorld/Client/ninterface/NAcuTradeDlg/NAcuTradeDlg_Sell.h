// [����] ��ť �ŷ�â ������
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"

class CNAcuTradeDlg_Sell : public CDialogController
{
	// ��������
private:
	InterfaceFactory	m_InterfaceFactory;


	// �Լ�����
public:
	CNAcuTradeDlg_Sell();
	~CNAcuTradeDlg_Sell();

	void Create(CControllerMgr* pParent);

	static void CALLBACK StaticAcuTradeDlg_SellProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAcuTradeDlg_SellProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	void Refresh( void );

private:
	void CalcTotal( void );

	void OrderToSell( void );
	void OrderToCancel( void );

};
