#ifndef _STRRESIGNCHIEFDLG_H
#define _STRRESIGNCHIEFDLG_H

#include "StrBaseDlg.h"

// �ǹ� ��� ���� �� ���̾�α� 
class NStrResignChiefDlg : public NStrTabDlg
{
public:
	enum {
		BUTTON_RESIGN
	};

	NStrResignChiefDlg();
	virtual ~NStrResignChiefDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};


#endif