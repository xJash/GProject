#ifndef _STRPAYTAXDLG_H
#define _STRPAYTAXDLG_H

#include "StrBaseDlg.h"

// �ǹ� ���� ���� �� ���̾�α� 
class NStrPayTaxDlg : public NStrTabDlg
{
public:
	enum {
		EDIT_MONEY,
		BUTTON_PAYTAX
	};
	NStrPayTaxDlg();
	virtual ~NStrPayTaxDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};


#endif