/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/
 
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "MsgType-System.h"

class NValentineDayNPCDlg : public CDialogController
{
public:

	NValentineDayNPCDlg();
	~NValentineDayNPCDlg();

	void Create();
	void Destroy();
	void Action();

	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	static void CALLBACK StaticNValentineDayNPCDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NValentineDayNPCDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
private:
	InterfaceFactory	m_InterfaceFactory;
};
 