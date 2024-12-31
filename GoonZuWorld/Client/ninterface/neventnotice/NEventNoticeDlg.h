// EventNotice.h: interface for the CNEventNotice class.
//
//////////////////////////////////////////////////////////////////////

/* ==========================================================================
	Ŭ���� :		CNNPCTradeDlg

	�ۼ��� :		2005/04/08
	�ۼ��� :		���¾�

	��  �� :		.
	                

	��  �� :		
	������� :		����

	�����۾� :		cpp �۾� �Ϸ� ��

   ========================================================================*/


#pragma once


#include <Directives.h>
#include <stdio.h>

#include "../../../Resource.h"
#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"


class CStatic;
class CEdit;

class CNEventNoticeDlg : public CDialogController  
{     
public:
	CNEventNoticeDlg();
	 ~CNEventNoticeDlg();


	void                    Create();
	void                    Set(TCHAR * szGift, SI16 txtSize, TCHAR * Txt);
	static void CALLBACK	StatiCNEventNoticeDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK			NEventNoticeDlgProc(UINT nEvent, int nControlID, CControllerObj* pControl);
	
	

private:
	

	BOOL                    m_bRectSwitch;
	RECT                    m_rtDlg;
	CStatic			        *m_pNEventNoticeStatic;
	CEdit					*m_pNEventNoticeEdit;

	

	
};

