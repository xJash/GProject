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
#include "../NContributionEvent_CommonDlg/NContributionEvent_CommonDlg.h"


class NGiantRaccoonResurrectEventDlg : public NContributionEvent_CommonDlg
{
public:

	NGiantRaccoonResurrectEventDlg();
	~NGiantRaccoonResurrectEventDlg();

	void	Create( void );
	void	Init( void );
	
	static void CALLBACK StaticNGiantRaccoonResurrectEventDlgProc( CControllerMgr *pControllerMgr, UINT nEvent );
	void CALLBACK NGiantRaccoonResurrectEventDlgProc( UINT nEvent );


private:
	InterfaceFactory	m_InterfaceFactory;
};
