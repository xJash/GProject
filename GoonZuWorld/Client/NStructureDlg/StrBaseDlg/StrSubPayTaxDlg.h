#ifndef _STRSUBPAYTAXDLG_H
#define _STRSUBPAYTAXDLG_H

#include "StrSubBaseDlg.h"

// �ǹ� ���� ���� �� ���̾�α� 
class NStrSubPayTaxDlg : public NStrSubTabDlg
{
public:
	enum {
		EDIT_MONEY,
		BUTTON_PAYTAX
	};
	NStrSubPayTaxDlg();
	virtual ~NStrSubPayTaxDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};


#endif