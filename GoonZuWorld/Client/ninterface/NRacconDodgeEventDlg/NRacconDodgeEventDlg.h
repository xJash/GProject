/* ==========================================================================
Ŭ���� :		 

�ۼ��� :		 
�ۼ��� :		 

������� :		 

�����۾� :		
========================================================================*/
 //Switch_10MonthEvent_RacoonDodge
#pragma once

#include "../../Client/client.h"
#include "../../InterfaceMgr/DialogController.h"
#include "MsgType-System.h"

class NRacconDldgeEventDlg : public CDialogController
{
public:

	NRacconDldgeEventDlg();
	~NRacconDldgeEventDlg();

	void Init();

	void Create();
	void Destroy();
	void Action();

	static void CALLBACK StatiNRacconDldgeEventDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
		   void CALLBACK NRacconDldgeEventDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );
	

public:
private:
	InterfaceFactory	m_InterfaceFactory;
};
 