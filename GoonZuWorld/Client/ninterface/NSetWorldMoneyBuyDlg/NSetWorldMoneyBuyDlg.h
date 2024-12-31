
#pragma once

#include <Directives.h>
#include "../../Client/Client.h"
#include "../../InterfaceMgr/DialogController.h"

class CStatic;
class CEdit;
class Cbutton;

class CNSetWorldMoneyBuyDlg : public CDialogController
{
public:
	enum
	{
		BIG_DISPLAY_MODE_DELTA_X = 16,
		SMALL_DISPLAY_MODE_DELTA_Y = 80,        
		DLG_WIDTH = 0,	// DDF ���Ͽ��� �о ó��
		DLG_HEIGHT = 0,	// DDF ���Ͽ��� �о ó��
		DLG_BIG_POS_X = 1024 - DLG_WIDTH + BIG_DISPLAY_MODE_DELTA_X,
		DLG_BIG_POS_Y = 100,
		DLG_SMALL_POS_X = 800 - DLG_WIDTH + SMALL_DISPLAY_MODE_DELTA_Y,
		DLG_SMALL_POS_Y = 100,
	};

	CNSetWorldMoneyBuyDlg();
	~CNSetWorldMoneyBuyDlg();

	void Initialize();
	void Set( SI64 WorldMoney, SI64 StockPrice,SI64 TotalWorldMoney);

	static	void CALLBACK NSetWorldMoneyBuyStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NSetWorldMoneyBuyProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create();
	void Show();
	void Hide();
	bool IsShow();

	bool m_bShow;

private:

	SI64 m_siAvailableBuyingWorldMoney;
	SI64 m_siWorldMoneyPrice;

	CStatic			*m_pStatic_NONAME1	;
	CButton			*m_pButton_buy	;
	CButton			*m_pButton_reject	;
	CEdit			*m_pEdit_explain	;
	CEdit			*m_pEdit_num	;

};


