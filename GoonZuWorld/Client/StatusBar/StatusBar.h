//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _STATUSBAR_H
#define _STATUSBAR_H

#include <windows.h>
#include <directives.h>

#include <Commctrl.h>		// Common Control ����	- Commctrl.h�� include �Ѵ�. 

#define STATUS_BAR_DIVIDE_NUMBER	5

class cltStatusBar{
public:

	HWND hParent;
	HWND hStatusBar;

	RECT Rect;

	cltStatusBar(HWND hparent);
	~cltStatusBar();

	SI32 GetYsize();
	void SetText(char* str, SI32 part);
	// ������ �缳���Ѵ�. 
	void ReSize(WPARAM wParam, LPARAM lParam);


};

#endif