//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "ToolBar.h"
#include "..\..\Resource.h"

#include "..\Interface\ToolBarBaseInfoDlg\ToolBarBaseInfoDlg.h"

#include "../Client/Client.h"

extern cltCommonLogic* pclClient;


// Ŭ���̾�Ʈ�� ����. 
static cltToolBarInfo clToolBarGameInfo[] ={
	{0, ID_TOOLBAR_SMALLMAP,	TBSTYLE_BUTTON,   TEXT("��ü����\r\nALT+W")}, 
	{0, ID_TOOLBAR_SEPERATOR,	TBSTYLE_SEP,      TEXT("")},
	{2, ID_TOOLBAR_CHARSTATUS,	TBSTYLE_BUTTON,   TEXT("��������\r\nALT+A")},
	{3, ID_TOOLBAR_INVENTORY,	TBSTYLE_BUTTON,   TEXT("����ǰ\r\nALT+I")},
	{4, ID_TOOLBAR_SKILL,		TBSTYLE_BUTTON,   TEXT("�������\r\nALT+S")},
	{5, ID_TOOLBAR_PERSONALSHOP,TBSTYLE_DROPDOWN, TEXT("���λ���")},
	{0, ID_TOOLBAR_SEPERATOR,	TBSTYLE_SEP,      TEXT("")},

	{6, ID_TOOLBAR_ITEMINFO,	TBSTYLE_BUTTON, TEXT("��ǰ������")},
	{7, ID_TOOLBAR_MONSTERINFO,	TBSTYLE_BUTTON, TEXT("���ͻ�����")},
	{8, ID_TOOLBAR_HUNTINGINFO,	TBSTYLE_BUTTON, TEXT("����ͻ�����")},
	{9, ID_TOOLBAR_NPCINFO,		TBSTYLE_BUTTON, TEXT("�ֹ�(NPC)������")},	
	{10, ID_TOOLBAR_VILLAGEINFO,TBSTYLE_BUTTON, TEXT("����������")},	
	{0, ID_TOOLBAR_SEPERATOR,	TBSTYLE_SEP,    TEXT("")},

	{11, ID_TOOLBAR_VILLAGERESIDENTINFO,TBSTYLE_BUTTON, TEXT("�����ֹ�����\r\nALT+V")},	
	{12, ID_TOOLBAR_MASTERINFO,	TBSTYLE_BUTTON, TEXT("��������\r\nALT+C")},	
	{13, ID_TOOLBAR_MAGICINFO,	TBSTYLE_BUTTON, TEXT("��������\r\nALT+M")},	
//	{14, ID_TOOLBAR_SCHOOLINFO,	TBSTYLE_BUTTON, TEXT("�б�����")},	
	{15, ID_TOOLBAR_FRIEND,		TBSTYLE_BUTTON, TEXT("ģ�����\r\nALT+F")},
	{16, ID_TOOLBAR_FATHER,		TBSTYLE_BUTTON, TEXT("���´�\r\nALT+T")},
	{0,  ID_TOOLBAR_SEPERATOR,	TBSTYLE_SEP,    TEXT("")},

	
	{17, ID_TOOLBAR_HOMEPAGE,	TBSTYLE_DROPDOWN, TEXT("���� Ȩ������ �̵�")},
	
//	{20, ID_TOOLBAR_ASK,		TBSTYLE_BUTTON, TEXT("������Ϻ���")},  // ���İ˻�"
	{0,  ID_TOOLBAR_SEPERATOR,	TBSTYLE_SEP,    TEXT("")},
	
	{22,ID_TOOLBAR_CONFIG,		TBSTYLE_BUTTON, TEXT("ȯ�漳��\r\nALT+E")},
	{23,ID_TOOLBAR_SCREENSHOT,	TBSTYLE_BUTTON, TEXT("��ũ����\r\nALT+P")},
	
	{24,ID_TOOLBAR_ITEMMALL,	TBSTYLE_BUTTON, TEXT("������ ��")},
	{25,ID_TOOLBAR_HELP,		TBSTYLE_BUTTON, TEXT("����\r\nALT+H")},

};




// �� �����Ϳ� ����. 
static cltToolBarInfo clToolBarMapEditInfo[] ={
	{0, ID_TOOLBAR_NEWMAP,			TBSTYLE_BUTTON, TEXT("������")},
	{1, ID_TOOLBAR_LOAD,			TBSTYLE_BUTTON, TEXT("���� �ҷ�����")},
	{2, ID_TOOLBAR_SAVE,			TBSTYLE_BUTTON, TEXT("���� ����")},
	{0, ID_TOOLBAR_SEPERATOR,		TBSTYLE_SEP, TEXT("")},


	{3, ID_TOOLBAR_TERRAINTOOL,		TBSTYLE_BUTTON,	TEXT("Ÿ��,������Ʈ ��")},
	{4, ID_TOOLBAR_HEADERMANAGER,	TBSTYLE_BUTTON,	TEXT("���������")},
	{5, ID_TOOLBAR_GEOINFO,			TBSTYLE_BUTTON, TEXT("�����ȳ���")},
	{0, ID_TOOLBAR_SEPERATOR,		TBSTYLE_SEP, TEXT("")},

	{6, ID_TOOLBAR_SMALLMAP,		TBSTYLE_BUTTON,	TEXT("�̴ϸ�")}, 
	{7, ID_TOOLBAR_CAPTUREMAP,		TBSTYLE_BUTTON, TEXT("�̴ϸ� ����")},
	{8, ID_TOOLBAR_VILLAGE,			TBSTYLE_CHECK,	TEXT("��������")},
	{0, ID_TOOLBAR_SEPERATOR,		TBSTYLE_SEP, TEXT("")},
	
	{9, ID_TOOLBAR_COLLDRAW,		TBSTYLE_BUTTON,	TEXT("�浹���������ֱ�")},
	{10,ID_TOOLBAR_NEWCOLL,			TBSTYLE_BUTTON, TEXT("�浹�����缳��")},
	{11,ID_TOOLBAR_CUSTOMCOLL,		TBSTYLE_BUTTON, TEXT("�����浹����")},

	{12,ID_TOOLBAR_DELETEUNIQUE,	TBSTYLE_BUTTON, TEXT("����ũ ��� ����")}
};

cltToolBar::cltToolBar(HWND hparent, HINSTANCE parentinstance, SI32 mode)
{
	SI32 i;
	SI32 BitmapImage = 0;
	SI32 BitmapImageNumber = 0;

	hToolBar = NULL;
	hBmpFindShopItem = NULL;
	memset(hBmpInternetHome, 0, sizeof(hBmpInternetHome));
	
	hParent			=	hparent;
	ParentInstance	=	parentinstance;

	if(mode == 0)
	{
		pToolBarInfo = clToolBarGameInfo;
		ToolButtonNumber	= sizeof(clToolBarGameInfo)/sizeof(cltToolBarInfo);

		BitmapImageNumber	= 26;

		BitmapImage			= IDB_TOOLBAR;
	}
	else
	{
		pToolBarInfo = clToolBarMapEditInfo;
		ToolButtonNumber	= sizeof(clToolBarMapEditInfo)/sizeof(cltToolBarInfo);;
		BitmapImageNumber	= 13;
		BitmapImage			= IDB_TOOLBAR_MAPEDIT;
	}

	if(ToolButtonNumber >= MAX_TOOLBAR_BUTTON_NUMBER)
	{
		MessageBox(NULL, TEXT("fd9ndf"), TEXT("vcvd111"), MB_OK|MB_TOPMOST);
	}
	
	for(i = 0; i < ToolButtonNumber ;i++)
	{
		ToolBtn[i].iBitmap		= pToolBarInfo[i].iBimap;
		ToolBtn[i].idCommand	= pToolBarInfo[i].idCommand;
		ToolBtn[i].fsState		= TBSTATE_ENABLED;
		ToolBtn[i].fsStyle		= pToolBarInfo[i].fsStyle;
		ToolBtn[i].dwData		= 0;
		ToolBtn[i].iString		= 0;
	}

	hToolBar  = CreateToolbarEx(hParent, WS_CHILD|WS_VISIBLE|WS_BORDER|TBSTYLE_TOOLTIPS,
		ID_TOOLBAR, 
		BitmapImageNumber,	// �� ��ư ��Ʈ���� ����. 
		ParentInstance,		// �θ��� �ν��Ͻ� 
		BitmapImage,		// ��Ʈ���� �ڵ� 
		ToolBtn,			// ����ư�� ���� ������ ���� TBBUTTON����ü �迭 
		ToolButtonNumber,	// ����ư ����. 
		16, 16,				// ��ư�� ���� ���� ũ��. 		
		20/*GetToolBarXsize()*/,	// ��Ʈ���� ũ��. (X)
		20/*GetToolBarYsize()*/,	// ��Ʈ���� ũ��. (Y)
		sizeof(TBBUTTON));

	if(hToolBar == NULL)
	{
		TCHAR buffer[256];
		TCHAR text[128];
		DWORD errcode = GetLastError();
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errcode, 0, buffer,  128, NULL);
		StringCchPrintf(text, 128, TEXT("ErrorCode=%d Message=%s"), errcode, buffer);
		MessageBox(NULL, text, TEXT("CreateToolBarEx"), MB_OK|MB_TOPMOST);
	}
	else
	{
		//============================
		// ���ӽð��� ���� �ڱ��� ǥ���ϴ� DialogBox ���� 
		//============================
		g_ToolBarBaseInfoDlg.Create( parentinstance, hToolBar );		
		SendMessage(hToolBar, TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_DRAWDDARROWS);

		//============================
		// TrackPopMenu Icons
		//============================
		hBmpFindShopItem    = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_FINDSHOPITEM));

		hBmpInternetHome[0] = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_MYGOMZI));
		hBmpInternetHome[1] = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_NEWS));
		hBmpInternetHome[2] = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_KNOWLEDGE));
		hBmpInternetHome[3] = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_SARANGBANG));
		hBmpInternetHome[4] = NULL;	// ����û ������ ���� 
		hBmpInternetHome[5] = LoadBitmap(parentinstance, MAKEINTRESOURCE(IDB_BITMAP_VILLAGERESIDENT));
		hBmpInternetHome[6] = NULL; // ���� ������ ����
	}
}


cltToolBar::~cltToolBar()
{
	if(hBmpFindShopItem) DeleteObject(hBmpFindShopItem);

	for(int i = 0; i < MAX_INTERNETMENU_ITEM; ++i)
		if(hBmpInternetHome[i]) DeleteObject(hBmpInternetHome[i]);
}


TCHAR* cltToolBar::GetToolTip(SI32 idcommand)
{
	SI32 i;

	for(i = 0; i< ToolButtonNumber;i++)
	{
		if(pToolBarInfo[i].idCommand == idcommand)
		{
			
			return pToolBarInfo[i].szTip;
		}
	}

	return NULL;
}
