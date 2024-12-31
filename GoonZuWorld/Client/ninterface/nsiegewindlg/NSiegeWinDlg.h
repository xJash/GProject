
// SiegeWinDlg.h: interface for the CSiegeWinDlg class.
/* ==========================================================================
	Ŭ���� :		CNSiegeWinDlg

	�ۼ��� :		05/03/25
	�ۼ��� :		���¾�

	��  �� :		
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/


#pragma once


#include <Directives.h>
#include <stdio.h>

#include "..\..\..\Resource.h"
#include "../../InterfaceMgr/DialogController.h"

class CStatic;


class CNSiegeWinDlg  : public CDialogController
{
public:
	CNSiegeWinDlg();
	virtual ~CNSiegeWinDlg();

	static void CALLBACK	StatiCNSiegeWinProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NSiegeWinProc( UINT nEvent, int nControlID, CControllerObj* pControl);

	void Create();
	void Set(TCHAR* ptext);

private:
	
	CStatic     	*m_pSiegeWinStatic;

	//HWND m_hSiegeWinDlg;
	//HWND m_hSiegeWinStatic;
};


