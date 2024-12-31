//---------------------------------
// 2003/111/25 ���°�
//---------------------------------

#ifndef _DEVTOOL_H
#define _DEVTOOL_H

#include <directives.h>

class cltDevTool{
public:
	HWND m_hDlg;	

	bool DlgRectInitSwitch;
	RECT DlgRect;


private:

public:
	cltDevTool();
	virtual ~cltDevTool();

	virtual SI32 GetCharUnique(){return 0;}

	virtual BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) = 0;

	// ��ȭ���ڰ� ������ ����� ������ ���ش�. 
	bool Create(HINSTANCE hinst, HWND hwnd, SI32 dlgitem, DLGPROC dlgproc, bool bShow = true);

	// WM_DESTROY������ ��ġ.
	void ACTION_WM_DESTROY();


};

#endif
