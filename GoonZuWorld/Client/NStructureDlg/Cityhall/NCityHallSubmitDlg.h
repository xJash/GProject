/* ==========================================================================
	Ŭ���� :		NCityHallSubmitDlg

	�ۼ��� :		05/05/11
	�ۼ��� :		���뷡
	
	������� :		����

	�����۾� :		

   ========================================================================*/
#pragma once

#include "CommonHeader.h"
#include "StructureClass/StructureClass.h"

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"

class cltStructureMngBasic;

class CStatic;
class CEdit;
class CButton;

class NCityHallSubmitDlg : public CDialogController
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

	NCityHallSubmitDlg();
	~NCityHallSubmitDlg(); 

	static	void CALLBACK NCityHallSubmitStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NCityHallSubmitProc( UINT nEvent, int nControlID, CControllerObj* pControl );

	void Create();
	void Show();
	void Hide();
	bool IsShow();
	void RetMsgBox( bool RetValue, SI16 MsgIndex, BYTE *pData, SI16 DataLen );

	bool m_bShow;

public:

	cltStructureMngBasic		*m_pclStructureManager;

	CStatic			*m_pStatic_chief	;
	CStatic			*m_pStatic_cityhall_candidate	;
	CStatic			*m_pStatic_confirm	;
	CButton			*m_pButton_suggest	;
	CEdit			*m_pEdit_explain	;
	CEdit			*m_pEdit_candidature	;


};

//class cltGM_AppointmentChiefDlg
//{
//public:
//	cltGM_AppointmentChiefDlg();
//	~cltGM_AppointmentChiefDlg();
//
//public:
//	static BOOL CALLBACK	StaticDlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam );	
//	BOOL CALLBACK	DlgProc( HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam ); 
//
//public:
//
//};
