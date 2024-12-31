// [����] ��ť �ŷ�â ������
#pragma once

#include "../../InterfaceMgr/DialogController.h"
#include "../../InterfaceMgr/InterfaceFile.h"
#include "../../Server/NTradeServerProcess/TradeServerMsg.h"

struct stACUTRADE_RETMSG_ORDERTOSELL
{
	GMONEY gmSellAcu;
	GMONEY gmSellUnit;
};

enum ACUTRADE_RETMSG
{
	ACUTRADE_RETMSG_ORDERTOSELL = 0,	// Acu �ȱ�
	ACUTRADE_RETMSG_ORDERTOEXTEND		// ���� ����
};

enum ACUTRADE_TAB
{
	ACUTRADE_TAB_SELL		= 0,	// �ȱ�â
	ACUTRADE_TAB_BUY,				// ���â
	ACUTRADE_TAB_WITHDRAW,			// ȸ��â
	ACUTRADE_TAB_PASSPORT,			// ����â

	//----------------------------------------
	// �� ���� �߰��� �ּ���
	//----------------------------------------
	ACUTRADE_TAB_MAX
};

class CNAcuTradeDlg_Parent : public CDialogController
{
	// ��������
private:
	InterfaceFactory	m_InterfaceFactory;
	CDialogController*	m_pTabDialog[ACUTRADE_TAB_MAX];


	// �Լ�����
public:
	CNAcuTradeDlg_Parent();
	~CNAcuTradeDlg_Parent();

	void Create();

	static void CALLBACK StaticAcuTradeDlg_ParentProc(CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NAcuTradeDlg_ParentProc(UINT nEvent, int nControlID, CControllerObj* pControl);

	void Action();

	void Show();
	void Hide();

	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	// -1��(����)�� ���´ٸ� ��ť�ü� ������ ������Ʈ ���Ѵ�
	void Refresh( GMONEY gmExchangeRate = (-1) );

	void SetWithdrawDialogMemberData( GMONEY gmSavedAcu, cltTradeAcuList* pclAcuList=NULL );
	

private:
	void SelectTabDialog( SI32 siControllID );
	void SetTabDialogButton( CButton* pclButton, COLORREF FontColor, SI16 siWeight );
	
	void Request_WorldMoney_TradeList( void );

	// -1��(����)�� ���´ٸ� ��ť�ü� ������ ������Ʈ ���Ѵ�
	void RefreshAcuInfo( GMONEY gmExchangeRate = (-1) );

	void RefreshSell( void );
	void RefreshBuy( void );
	void RefreshWithdraw( void );
	void RefreshPassport( void );

	void SendForRefresh( void );


};
