//---------------------------------
// 2003/11/11 ���°�
//---------------------------------
#ifndef _QUITCONFIRM_H
#define _QUITCONFIRM_H

#include <WIndows.h>
#include <Directives.h>

// ���� Ȯ����. 
class cltQuitMenu{
public:
	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	BOOL DlgRectInitSwitch;
	
	cltQuitMenu();
	~cltQuitMenu();
	
	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);

	static BOOL CALLBACK StaticQuitMenuDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK QuitMenuDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

// ���� Ȯ����. 
class cltQuitConfirm{
public:
	HWND m_hDlg;					// ������ ����. 

	RECT DlgRect;
	BOOL DlgRectInitSwitch;

	cltQuitConfirm();
	~cltQuitConfirm();
	
	BOOL CreateDlg(HINSTANCE hinst, HWND hwnd);

	static BOOL CALLBACK StaticQuitConfirmDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK QuitConfirmDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
};


#endif
