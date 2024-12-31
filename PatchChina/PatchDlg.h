// PatchDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_PATCHDLG_H__8DEDA850_CC30_4EC3_85A5_DCB17CED762F__INCLUDED_)
#define AFX_PATCHDLG_H__8DEDA850_CC30_4EC3_85A5_DCB17CED762F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPatchDlg dialog
#include <process.h>

class FrontProcess;

#include "../Server/FrontServer/FrontMsg.h"


#pragma comment(lib, "zlibstat.lib")

#include "TypeDefinition.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ProgressST.h"
#include "xSkinButton.h"

#define MAX_DOWNLOAD_NUM				1					// �� ������ �ٿ�ε� ���� �� �ִ� �ִ� ���� ��

#define	MAX_DOWNLOAD_PATCH_FILE_NUM		50					// ��ġ�� ������ ������ ����( �ִ� 30���� �д�... �׷��ٰ� ��ġ�� ���� �ʴ� ���� �ƴϴ�... 30���� �Ѱ� �޾ƾ� �ϴ� ��Ȳ�� �߻��ϸ� ������ ��ü ��ġ ������ �ٿ� ������� �ǰ� �ϱ� �����̴�. �ǰ�� )
#define	DOWNLOAD_PATCH_EXCESS			100					// ��ġ�� 100 �� �̻��� �ʿ��ϴٸ�, ��ġ�� �ȵ�. �� ��� ���� �缳ġ�� �ؾ� ��.

#define WM_DRAWSTATUS					WM_USER+2

#define PROGRESS_WIDTH					259
#define PROGRESS_HEIGHT					18

#define PROGRESS_START_XPOS				10
#define	PROGRESS_START_YPOS				383

const int HOMEPAGE_BUTTON_X		 = 272;
const int HOMEPAGE_BUTTON_Y		 = 32;
const int HOMEPAGE_BUTTON_WIDTH	 = 64;
const int HOMEPAGE_BUTTON_HEIGHT = 19;

const int ACCOUNT_BUTTON_X		= 337;
const int ACCOUNT_BUTTON_Y		= 32;
const int ACCOUNT_BUTTON_WIDTH	= 64;
const int ACCOUNT_BUTTON_HEIGHT = 19;

const int CARD_BUTTON_X		= 402;
const int CARD_BUTTON_Y		= 32;
const int CARD_BUTTON_WIDTH	= 64;
const int CARD_BUTTON_HEIGHT = 19;

const int DOWN_BUTTON_X		= 467;
const int DOWN_BUTTON_Y		= 32;
const int DOWN_BUTTON_WIDTH	= 64;
const int DOWN_BUTTON_HEIGHT = 19;

const int NEXT_BUTTON_X		= 8;
const int NEXT_BUTTON_Y		= 417;
const int NEXT_BUTTON_WIDTH	= 264;
const int NEXT_BUTTON_HEIGHT = 55;

const int EXIT_BUTTON_X		= 594;
const int EXIT_BUTTON_Y		= 4;
const int EXIT_BUTTON_WIDTH	= 64;
const int EXIT_BUTTON_HEIGHT = 19;

const int CNCIDC_BUTTON_X		= 13;
const int CNCIDC_BUTTON_Y		= 44;
const int CNCIDC_BUTTON_WIDTH	= 110;
const int CNCIDC_BUTTON_HEIGHT = 28;

const int CTCIDC_BUTTON_X		= 126;
const int CTCIDC_BUTTON_Y		= 44;
const int CTCIDC_BUTTON_WIDTH	= 110;
const int CTCIDC_BUTTON_HEIGHT = 28;

const int PINGTEST_BUTTON_X		= 151;
const int PINGTEST_BUTTON_Y		= 438;
const int PINGTEST_BUTTON_WIDTH	= 175;
const int PINGTEST_BUTTON_HEIGHT = 36;

const int START_BUTTON_X		= 328;
const int START_BUTTON_Y		= 438;
const int START_BUTTON_WIDTH	= 175;
const int START_BUTTON_HEIGHT = 36;

const int EXIT2_BUTTON_X		= 597;
const int EXIT2_BUTTON_Y		= 2;
const int EXIT2_BUTTON_WIDTH	= 64;
const int EXIT2_BUTTON_HEIGHT = 19;

const int CHECK_BUTTON_X		= 189;
const int CHECK_BUTTON_Y		= 338;
const int CHECK_BUTTON_WIDTH	= 13;
const int CHECK_BUTTON_HEIGHT	= 13;

class CRegistryMgr;
class CHttpMgr;

enum{ DLG_INITIAL_STATUS, DLG_DOWNLOAD_STATUS, DLG_DECOMPRESS_STATUS, DLG_GAMESTART_STATUS, DLG_SOCKET_STATUS };

enum
{ 
	FIRST_PAGE = 0,
	NEXT_PAGE
};

enum
{
	RECT_BUTTON_HOMEPAGE = 0,
	RECT_BUTTON_ACCOUNTREGISTER,
	RECT_BUTTON_CARD,		
	RECT_BUTTON_DOWNLOAD,	
	RECT_BUTTON_NEXT,	
	RECT_BUTTON_CHECK,	// Ǯ��ũ�� üũ
	RECT_BUTTON_EXIT,

	RECT_BUTTON_CNCIDC,
	RECT_BUTTON_CTCIDC,
	RECT_BUTTON_PINGTEST,
	RECT_BUTTON_START,
	RECT_BUTTON_EXIT2,

	RECT_END
};

class CPatchDlg : public CDialog
{
	// Construction
public:
	CPatchDlg(CWnd* pParent = NULL);	// standard constructor

	inline static unsigned __stdcall DownLoadMgrThread(void* lpArg); // DownLoad ���� ������

	bool CheckDupGame(char *name, char* title);

	void EndProcess();

	//bool GetBaseInfo();										// �⺻ Ftp ��θ� ���Ͽ��� ��� �´�.
	bool GetRegistryInfo();									// ������Ʈ������ ������ ���´�.


	bool SetNewDownLoadPathCount( sResponse_PatchInfo * pRecvMsg );				// Count ������ŭ m_stDownLoadPath �� �����Ѵ�. new stDownLoadPath[Count]
	void ParsingVersionData( char * );						// ��ġ ���� ������ ���� �� VersionData ���� Parsing �ϴ� ��.

	void DownLoadThreadStart();								// �ٿ�ε� ����.
	void DownLoadThreadStop();								// �ٿ�ε� ����.
	void DownLoadMgrThreadRun();							// ���� �ٿ�ε� ������ �ϴ� �κ�.

	void Decompress();										// ���� ����.

	int ZipFileDecompress(char* zipfilename);				// ���� ������ �����ϴ� ��
	int GetZipFileLise(char* zipfilename);					// zip ���ϳ��� �ִ� ���ϵ� ����Ʈ�� ���´�.

	void FrontMsgProcess( sPacketHeader *pPacket );

	bool IsCorrectDNS(char* hostname);

	// ���� �ٿ�ε� ���¸� ȭ�鿡 �����ֱ� ���ؼ�..
	void DrawDownLoadStatus(CDC * Destination);								
	void DrawInstallStatus( CDC * Destination );
	void Drawing(CDC * Destination);
	void DrawCustomButton( CDC * Destination, int ButtonIndex, int ButtonMode );
	void DrawAreaButton( CDC * Destination, int ButtonIndex, int ButtonMode );

	// ��ġ �� �ʿ䰡 ���ų�, ��ġ�� �� ���� �ÿ� �� �Լ��� ȣ���Ͽ� ������ ������.
	void GameReady();		

	// ����Ʈ ã��
	void InitFrontServer( FrontProcess* pFrontFrocess, char* pFrontIP );
	// ��ư �̹��� ���
	void AddButtonImage( char* pFileName, CBitmap* pBitmap );

	int GetGameVersionInFile();
	bool SetGameVersionInFile(int siVersion);
	bool GetGameInfo();										// ���� ���������� ������ ���´�.

	UI32			m_uiCurrentVersion;	

	// Dialog Data
	//{{AFX_DATA(CPatchDlg)
	enum { IDD = IDD_PATCH_DIALOG };
	CWebBrowser2	m_WebBrowser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatchDlg)
public:
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	//HANDLE m_hFileRecvThreadHandle;
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CPatchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//afx_msg void OnInitialPatch( WPARAM wParam, LPARAM lParam );
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:	

	//CRITICAL_SECTION	Crit;
	HANDLE			m_hDownLoadMgrThreadHandle;								// �ٿ�ε� �����ϴ� �������� �ڵ�
	bool			m_bDownLoadMgrThreadRun;


	char			m_strGameFolderPath[1024];								// ���� ���� ���
	char			m_strPatchFolderPath[1024];								// ��ġ ���� ���� ���
	char			m_strGameExeFileName[128];								// ���� ���� ���ϸ�
	char			m_strGameFullPath[1536];								// ���� ��ü ���( GameFolderPath + GameFileName )

	CRegistryMgr	*m_pRegistryMgr;										// ������Ʈ�� ���� �޾� ���ų� ������Ʈ���� ���� ���ų� �� �� ���ϰ� ���� ���ؼ� Ŭ����ȭ ����.

	US16			m_usCount;												// DownLoad �ϴ� ������ ����
	UI32			*m_puiVersionList;				

	CHttpMgr		*m_pHttpMgr;

	UC08			m_ucCurrentStatus;										// ���� ����

	bool			m_bButtonClick;

	DWORD			m_dwTotalFileSize;

	FrontProcess	*m_pFront;
	FrontProcess	*m_pCNCFront;
	FrontProcess	*m_pCTCFront;

	HBITMAP			m_hTitleBmp;

	char			m_strParameter[ 2048 ];

	int				m_siServiceArea;

public:
	//	afx_msg void OnBnClickedButtonRun();
	//	afx_msg void OnBnClickedButtonStop();
	afx_msg UINT OnNcHitTest(CPoint point);

	char		m_StatusTextBuffer[256];

	clock_t			m_StartClock;

	char			m_szPatchVersionInfo[16];
	char			m_szState[128];
	char			m_szPingNumber[MAX_IDC][MAX_FRONTSERVER_NUMBER][20];
	char			m_szLastServerName[128];
	CBitmap			m_ProgressBitmap;

	bool			m_bClick[RECT_END];
	bool			m_bHover[RECT_END];

	static	const	RECT CustomControlRect[RECT_END];

	CBitmap			m_CustomButtonBitmapClick[RECT_END];
	CBitmap			m_CustomButtonBitmapDisable[RECT_END];

	CBrush			m_BackGroundBrush[2];
	CBitmap			m_BackGroundBitmap[2];

	char			m_szIDC_IP[MAX_IDC][MAX_FRONTSERVER_NUMBER][64];
	char			m_szIDC_Name[MAX_IDC][MAX_FRONTSERVER_NUMBER][32];

	RECT			AreaControlRect[MAX_FRONTSERVER_NUMBER];
	bool			m_bAreaClick[MAX_FRONTSERVER_NUMBER];
	bool			m_bAreaHover[MAX_FRONTSERVER_NUMBER];

	int				m_siMaxCNCIDC_Number;
	int				m_siMaxCTCIDC_Number;
	int				m_siPrevAreaButtonIdex;
	int				m_siCDNSelect;

	CBitmap*		m_IDCBitmapClick[MAX_IDC];
	CBitmap*		m_IDCBitmapDisable[MAX_IDC];

	int				m_siPage;

	int				m_siSelectIDC;
	int				m_siSelectFrontServerIndex;

	bool			m_bFirstConnect;
	bool			m_bFailPatchInfo;
	int				m_siWhereConnect;
	int				m_siCNCConnectIndex;
	int				m_siCTCConnectIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATCHDLG_H__8DEDA850_CC30_4EC3_85A5_DCB17CED762F__INCLUDED_)
