#ifndef _STRSUBRESIGNCHIEFDLG_H
#define _STRSUBRESIGNCHIEFDLG_H

#include "StrSubBaseDlg.h"

// �ǹ� ��� ���� �� ���̾�α� 
class NStrSubResignChiefDlg : public NStrSubTabDlg
{
public:
	enum {
		BUTTON_RESIGN
	};

	NStrSubResignChiefDlg();
	virtual ~NStrSubResignChiefDlg();

	void InitDlg();

	void NDlgTabProc( UINT nEvent, int nControlID, CControllerObj *pControl );
};


#endif