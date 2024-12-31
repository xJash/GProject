#if !defined(AFX_GAMESERVERLISTDLG_H__52EE614C_4F85_43DD_B1CB_1754673B3A3C__INCLUDED_)
#define AFX_GAMESERVERLISTDLG_H__52EE614C_4F85_43DD_B1CB_1754673B3A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PATCH_ROOTDIRECTORY	"c:\\Patch"
#define PATCH_INFODIR		"c:\\Patch\\PatchDir.txt"
#define PATCH_INFOFILE		"c:\\Patch\\PatchInfo.txt"

// GameServerListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGameServerListDlg dialog

class servercheck
{
public:
	DWORD		last_tick_fps;
	DWORD		last_tick_dblatency;

};


class CGameServerListDlg : public CDialog
{
public:
	BOOL					m_bInitView;
	int 					m_ServerViewIndex;

	unsigned int			m_uiLastFrame[ 100 ];

	BOOL					m_bMacroOn;
	unsigned int			m_bOldFrame;

	void					GameServerDisp();
	void					DBManagerDisp();

	BOOL					CheckServer( int index );
	void                    FindFileRecursive( TCHAR* pPath, HANDLE sendFileHandle, HANDLE sendDirectoryHandle  );

	servercheck				check[ 100 ];

// Construction
public:
	CGameServerListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGameServerListDlg)
	enum { IDD = IDD_DIALOG_GAMESERVERLIST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameServerListDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGameServerListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonAlarmon();
	afx_msg void OnButtonAlarmoff();
	afx_msg void OnButtonMacroon();
	afx_msg void OnButtonMacrooff();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonCmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButtonServerOn();
	afx_msg void OnBnClickedButtonGameserverOff();
	afx_msg void OnBnClickedButtonDbmanagerOn();
	afx_msg void OnBnClickedButtonDbmanagerOff();
	afx_msg void OnBnClickedButtonAllServerOn();
	afx_msg void OnBnClickedButtonAllDbmanagerOff();
	afx_msg void OnBnClickedButtonAllServerOff();
	afx_msg void OnBnClickedButtonAllDbmanagerOn();
	afx_msg void OnBnClickedSendData();
	afx_msg void OnBnClickedAllSendData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESERVERLISTDLG_H__52EE614C_4F85_43DD_B1CB_1754673B3A3C__INCLUDED_)
