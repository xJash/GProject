#ifndef _CHATSTATUSBAR_H_
#define _CHATSTATUSBAR_H_



#include <Directives.h>

#include <Commctrl.h>		// Common Control ����	- Commctrl.h�� include �Ѵ�. 

#include "..\..\..\Resource.h"
#include "ChatStatusBarBaseInfo.h"


#define	CHAT_STATUS_BAR_HEIGHT_SIZE		39
#define CHAT_STATUS_BAR_DIVIDE_NUMBER	3


class CChatStatusBarBuffer;
class CChatRecvDataMgr;
/*
class CChatStatusBar
{
public:
	CChatStatusBar();
	~CChatStatusBar();

	void	Destroy();

	void	Create( HWND hParent, HINSTANCE hInst );

	bool	IsCreate();

	static	LRESULT CALLBACK StaticEditSubProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK EditSubProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	static	BOOL CALLBACK StaticChatStatusBarDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
	BOOL	CALLBACK ChatStatusBarDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	SI32	GetXsize();
	SI32	GetYsize();
	void	ReSize( WPARAM wParam, LPARAM lParam );
	
//	void	SetBroadCastButton(bool bShow); // ��� ��ư

	void	ChatDataSend();
	SI32	CompareKey(char *data, SI32 type);
	//void	ChatDataRecv( TCHAR *strUserID, TCHAR *strChatData );
	//void	ResidentsChatDataRecv( TCHAR *strUserID, TCHAR *strChatData );
	
	bool	Pop( stChatStatusBarData * pChatStatusBarData );		// ������ �������� �Լ�

	void	SetText(TCHAR* str, SI32 part);

	void Show();
	void Hide();

	CChatStatusBarBuffer	*m_pChatStatusBarBuffer;

	HWND	m_hChatEdit;
	
	void	CharacterLogin();

	HWND	GetDlgHwnd()	{ return m_hDlg; };

private:
	HWND	m_hParent;
	HWND	m_hChatStatusBar;
	HWND	m_hDlg;
	
	bool	m_bIsCreate;

	WNDPROC	m_OldEditProc;

	TCHAR	m_strChatData[ MAX_CHAT_DATA_LENGTH ];
	TCHAR	m_strChatRecordData[ MAX_CHAT_DATA_RECORD_NUM ][ MAX_CHAT_DATA_LENGTH + MAX_PLAYER_NAME ];		//MAX_PLAYER_NAME �� ĳ���� ���̵� ǥ�� ������...

	// ��۹�ư
	HBITMAP m_hBroadCastBitmap;
	HBITMAP m_hWinampBitmap;
};
*/

#endif
