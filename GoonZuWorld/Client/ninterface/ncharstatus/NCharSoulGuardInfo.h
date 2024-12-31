#pragma once

#include <directives.h>

#include "CommonHeader.h"
#include "../../InterfaceMgr/DialogController.h"

class CButton;
class CEdit;
class CStatic;

// ĳ���� �λ縻 ���� â
class CNCharSoulGuardInfo : public CDialogController
{
public:
	CNCharSoulGuardInfo();
	~CNCharSoulGuardInfo();

	void Create();

	static void CALLBACK NCharSoulGuardInfoStaticProc( CControllerMgr *pControllerMgr, UINT nEvent, int nControlID, CControllerObj *pControl);
	void CALLBACK NCharSoulGuardInfoProc( UINT nEvent, int nControlID, CControllerObj* pControl );

private:
	CEdit*		m_pclEdit_Info;
	CStatic*	m_pclStatic_Noname1;
	CButton*	m_pclButton_Close;


};