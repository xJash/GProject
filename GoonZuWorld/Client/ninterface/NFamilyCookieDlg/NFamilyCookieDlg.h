#pragma once

#include "../../InterfaceMgr/DialogController.h"

class CNFamilyCookieDlg : public CDialogController
{
private:
	SI32			m_siMinimizedSlot;

	CImageStatic*	m_pclBackGround;

public:
	CNFamilyCookieDlg( void );
	~CNFamilyCookieDlg( void );

	void Init();
	void Create();

	void Action();

	static void CALLBACK StaticCallBackDialogCNFamilyCookieDlg( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj* pControl );
	void CALLBACK CallBackDialogCNFamilyCookieDlg( UINT nEvent, int nControlID, CControllerObj* pControl );

public:
	SI32 GetMinimizedSlot( void )	{	return m_siMinimizedSlot;	}

};