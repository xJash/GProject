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

class NValentineDayConfessionQuestionDlg : public CDialogController
{
public:

	NValentineDayConfessionQuestionDlg();
	~NValentineDayConfessionQuestionDlg();

	void Create();
	void Destroy();
	void Action();
	void DrawDialogLast( SI32 ScreenRX, SI32 ScreenRY );

	static void CALLBACK StaticNValentineDayConfessionQuestionDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NValentineDayConfessionQuestionDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	
private:
	InterfaceFactory	m_InterfaceFactory;
};
 