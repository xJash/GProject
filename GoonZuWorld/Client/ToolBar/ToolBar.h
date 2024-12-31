//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#ifndef _TOOLBAR_H
#define _TOOLBAR_H

#include <directives.h>

#include <Commctrl.h>	// Common Control ����	- Commctrl.h�� include �Ѵ�. 
						//							- WM_CREATE�� InitCommonCtrolsEx()�� ȣ���Ѵ� 
						//							- ComCtl32.lib�� ��ũ���ش�. 				

#define MAX_TOOLBAR_BUTTON_NUMBER 40

class cltToolBarInfo{
public:
	SI32 iBimap;
	SI32 idCommand;
	BYTE fsStyle;
	TCHAR szTip[128];
};

class cltToolBar{
public:
	HWND hToolBar;				// ������ �ڵ� 
	HWND hParent;				// ���� �θ��� �ڵ� 	
	HINSTANCE ParentInstance;	// �θ��� �ν��Ͻ� 

	TBBUTTON ToolBtn[MAX_TOOLBAR_BUTTON_NUMBER];

	cltToolBarInfo* pToolBarInfo;
	SI32 ToolButtonNumber;


	HBITMAP hBmpFindShopItem;
#define MAX_INTERNETMENU_ITEM	10
	HBITMAP hBmpInternetHome[MAX_INTERNETMENU_ITEM];


	cltToolBar(HWND hParent, HINSTANCE parentinstance, SI32 mode);
	~cltToolBar();

	SI32 GetToolBarXsize()
	{
		RECT rect;
		GetClientRect(hToolBar, &rect);
		return rect.right;
	}

	SI32 GetToolBarYsize()
	{
		/*
		RECT rect;
		GetClientRect(hToolBar, &rect);
		return rect.bottom;
		*/
		return 26;
	}
	TCHAR* GetToolTip(SI32 idcommand);
	
};


#endif


