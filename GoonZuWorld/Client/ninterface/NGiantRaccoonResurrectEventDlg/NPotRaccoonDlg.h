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

class NPotRaccoonDlg : public CDialogController
{
public:

	NPotRaccoonDlg();
	~NPotRaccoonDlg();

	void	Create( void );
	void	Init( void );
	void	ClearFocus( void );
	
	static void CALLBACK StaticNPotRaccoonDlgProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl );
	void CALLBACK NPotRaccoonDlgProc( UINT nEvent, int nControlID, CControllerObj* pControl );


private:
	InterfaceFactory	m_InterfaceFactory;
};
