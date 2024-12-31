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

// - NHN ACM -
#ifdef USE_HANAUTH
	#include "../HanAuth/HanAuthForClient.h"
#endif

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	#include "../Porte/PorteAuthForClient.h"
	using namespace Porte::PorteAuthSystem;
#endif // USE_PORTEAUTH

#ifdef USE_HANREPORT
	#include "../HanAuth/HanReportForClient.h"

	#ifdef _DEBUG
		#pragma comment(lib, "HanReportForClientD.lib") 
	#else
		#pragma comment(lib, "HanReportForClient.lib") 
	#endif // _DEBUG
#endif

#ifdef USE_CNREPORT
	#include "../HanAuth/HanReportForClient.h"

	#ifdef _DEBUG
		#pragma comment(lib, "HanReportForClientD.lib") 
	#else
		#pragma comment(lib, "HanReportForClient.lib") 
	#endif // _DEBUG
#endif

#define HANREPORT_PATCH_STARTPROGRAM			"250"
#define HANREPORT_PATCH_ENDPROGRAM				"251"

#define HANREPORT_PATCH_INITPROGRAM				"253"

#define HANREPORT_PATCH_GAMESTRING_FAILED		"255"

#define HANREPORT_PATCH_FRONTSERVER_CONNECTED	"260"
#define HANREPORT_PATCH_FRONTSERVER_RECVINFO	"261"

#define HANREPORT_PATCH_FRONTSERVER_ADDRFAILED	"265"

#define HANREPORT_PATCH_DOWNLOAD_START			"270"
#define HANREPORT_PATCH_DOWNLOAD_END			"271"
#define HANREPORT_PATCH_UNZIP_START				"275"
#define HANREPORT_PATCH_UNZIP_END				"276"

#define HANREPORT_PATCH_GAMESTART				"280"

//KHY - 0316 - NHNChina Outbound
#ifdef NHNPATCH_HIDEDLG 
#define		PURPLE_OUTBOUND_INFORM					9
#define		PURPLE_OUTBOUND_DOWNLOAD_PROGRESS		18
#define		PURPLE_OUTBOUND_DOWNLOAD_SPEED			27
#define		PURPLE_OUTBOUND_DOWNLOAD_RESTTIME		31
#define		PURPLE_OUTBOUND_FILENAME				36
#define		PURPLE_OUTBOUND_PATCH_PROGRESS			45
#define		PURPLE_OUTBOUND_PATCH_FILE_NUMBER		54
#define		PURPLE_OUTBOUND_ENDING					63


	typedef struct PurpleCDS
	{
		TCHAR szString[160];
		DWORD dwIndex;
	} PurpleCDS;

	/**
	 * 1. �ܺθ�� �⵿�� ��
	 *		���÷��Ĵ� ���� ������ �������ڷ� �����Ѵ�.
	 *		(1) HWND : SendMessage�� ���� ������ �ڵ�. 10������ ǥ�õȴ�.
	 *		(2) argument : ��Ÿ �ܺθ���� �⵿�� �� �ʿ��� ������ �����Ѵ�.
	 *
	 * 2. ���÷���/�ܺθ�� ���� ����
	 *		(1) ���÷��� => �ܺθ��� ����ϴ� ���� ������ (���ʿ� ���ڸ� �����ϱ⸸ �Ѵ�), 
	 *			���Ŀ��� �ܺθ�� => ���÷����� ��Ÿ��� �Ѵ�. 
	 *		(2) ��Ź���� WM_COPYDATA�� ����ϸ� �޽����� ������ ������ ������ ���¸� ���Ѵ�. 
	 *			::SendMessage(HWND, WM_COPYDATA, HWND, PCOPYDATASTRUCT);
	 *				a. HWND : ���÷��� ������ �ڵ��̴�. �� ���� �ܺθ���� ���� �⵿�� �� ���ڷ� ���޵ȴ�.
	 *				b. WM_COPYDATA : ������ �޽���
	 *				c. HWND : �޽����� ���Ϲ��� ������ �ڵ��� �����Ѵ�. (�� ���� �̷��� ���ؼ� �����Ѵ�.)
	 *				d. PCOPYDATASTRUCT : WM_COPYDATA�� �� �� �����ϴ� ����ü�̴�. ������ MSDN ����.
	 *		
	 * 						typedef struct tagCOPYDATASTRUCT {
	 * 							ULONG_PTR dwData;
	 *							DWORD cbData;
	 *							PVOID lpData;
	 *						} COPYDATASTRUCT, *PCOPYDATASTRUCT; 
	 *
	 * 3. �ε���(dwData)�� ���� �ǹ�
	 *		(1) PURPLE_OUTBOUND_INFORM : Inform ����ƽ�� ��Ʈ���� ǥ���Ѵ�.
	 *			- szString : ����ƽ�� ǥ���� ��Ʈ��
	 *			- dwIndex : N/A
	 *		
	 *		(2) PURPLE_OUTBOUND_DOWNLOAD_PROGRESS : �ٿ�ε� ���α׷����� �����Ѵ�.
	 *			- szString : N/A
	 *			- dwIndex : ���α׷��� (0���� 100����)
	 *
	 *		(3) PURPLE_OUTBOUND_DOWNLOAD_SPEED : �ٿ�ε� �ӵ��� ǥ���Ѵ�.
	 *			- szString : N/A
	 *			- dwIndex : �ٿ�ε� ���ǵ� (byte / millisecond)
	 *
	 *		(3.1) PURPLE_OUTBOUND_DOWNLOAD_RESTTIME : �����ð��� ǥ���Ѵ�. 
	 *			- szString : N/A
	 *			- dwIndex : �����ð� (millisecond)
	 *
	 *		(4) PURPLE_OUTBOUND_FILENAME : ���� ó���ϴ� ������ �̸��� ǥ���Ѵ�. 
	 *			- szString : ó������ ���ϸ�Ī
	 *			- dwIndex : N/A
	 *
	 *		(5) PURPLE_OUTBOUND_PATCH_PROGRESS : ��ġ ���α׷����� �����Ѵ�. ��ġ ���α׷����� ��ü��ġ������ ǥ���Ѵ�.
	 *			- szString : N/A
	 *			- dwIndex : ���α׷��� (0���� 100����)
	 *
	 *		(6) PURPLE_OUTBOUND_PATCH_FILE_NUMBER : ��ġ�� ��ü ���� ���� �� ������� ó���� ������ ������ ǥ���Ѵ�.
	 *			- szString : N/A
	 *			- dwIndex : HIWORD => ��ü���ϰ���, LOWORD => ������� ó���� ���� ����
	 *
	 *		(7) PURPLE_OUTBOUND_ENDING : �ܺθ���� ������� �����Ѵ�. 
	 *			- szString : ������Ʈ��
	 *			- dwIndex : �����ڵ�
	 *
	 *			a. �����ڵ� 0 : ��ġ�Ϸ� �� ���������. ���÷��Ĵ� �� �޽����� ������ ���ӽ��� stand by ���°� �ȴ�.
	 *			b. �����ڵ� 1 : �ν��罯�带 �ٽ� �޾ƾ� ���� ���Ѵ�. szString�� �ٿ�޾ƾ� �ϴ� ���� URL�� ����Ѵ�.
	 *			c. ��Ÿ �����ڵ� : �ϳ��� �����Ѵ�. (���� ���, dll �ε忡 �����Ͽ���. ��ġ���� �ٿ�ε忡 �����Ͽ��ٵ�..)
	**/
#endif // NHNPATCH_HIDEDLG 


#define MAX_DOWNLOAD_NUM				1						// �� ������ �ٿ�ε� ���� �� �ִ� �ִ� ���� ��

#ifdef _USA
	#define	MAX_DOWNLOAD_PATCH_FILE_NUM		500					// USA ��ġ�� ������ ������ ����( �ִ� 500���� �д�... �׷��ٰ� ��ġ�� ���� �ʴ� ���� �ƴϴ�... 500���� �Ѱ� �޾ƾ� �ϴ� ��Ȳ�� �߻��ϸ� ������ ��ü ��ġ ������ �ٿ� ������� �ǰ� �ϱ� �����̴�. �ǰ�� )
#else	
	#define	MAX_DOWNLOAD_PATCH_FILE_NUM		50					// ��ġ�� ������ ������ ����( �ִ� 30���� �д�... �׷��ٰ� ��ġ�� ���� �ʴ� ���� �ƴϴ�... 30���� �Ѱ� �޾ƾ� �ϴ� ��Ȳ�� �߻��ϸ� ������ ��ü ��ġ ������ �ٿ� ������� �ǰ� �ϱ� �����̴�. �ǰ�� )
#endif


#define	DOWNLOAD_PATCH_EXCESS			100					// ��ġ�� 100 �� �̻��� �ʿ��ϴٸ�, ��ġ�� �ȵ�. �� ��� ���� �缳ġ�� �ؾ� ��.

#define WM_DRAWSTATUS					WM_USER+2

#define PROGRESS_WIDTH					318
#define PROGRESS_HEIGHT					18

#define PROGRESS_START_XPOS				17
#define	PROGRESS_START_YPOS				272

#define DLG_SOCKET_STATUS_LIFETIME		30					//	[��ȣ] �� ��ġ���°� ���ϻ��� ���� �ð�

class CRegistryMgr;
class CHttpMgr;

enum{ DLG_INITIAL_STATUS, DLG_DOWNLOAD_STATUS, DLG_GAMESTART_STATUS, DLG_SOCKET_STATUS };

void WriteFileLog(TCHAR* pszFileName, TCHAR* pszSource, int nLine, TCHAR* pszLogFormat, ...);

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
	bool GetGameInfo();										// ���� ���������� ������ ���´�.
	

	bool SetNewDownLoadPathCount( sResponse_PatchInfo * pRecvMsg, bool bUseSecondAddr );				// Count ������ŭ m_stDownLoadPath �� �����Ѵ�. new stDownLoadPath[Count]
	void ParsingVersionData( char * );						// ��ġ ���� ������ ���� �� VersionData ���� Parsing �ϴ� ��.
	
	void DownLoadThreadStart();								// �ٿ�ε� ����.
	void DownLoadThreadStop();								// �ٿ�ε� ����.
	void DownLoadMgrThreadRun();							// ���� �ٿ�ε� ������ �ϴ� �κ�.
	

	void DrawDownLoadStatus();								// ���� �ٿ�ε� ���¸� ȭ�鿡 �����ֱ� ���ؼ�..
	void DrawInstallStatus( char *pString );

	void Decompress();										// ���� ����.

	int ZipFileDecompress(char* zipfilename);				// ���� ������ �����ϴ� ��
	int GetZipFileLise(char* zipfilename);					// zip ���ϳ��� �ִ� ���ϵ� ����Ʈ�� ���´�.

	void GameStart();										// ��ġ �� �ʿ䰡 ���ų�, ��ġ�� �� ���� �ÿ� �� �Լ��� ȣ���Ͽ� ������ ������.

	void	CreateGoonZuShourCut( void );
	HRESULT CreateShortCut( char* szSrcFile, char* szLinkFile, char* szArgument, char* szDesc, char* szWorkingDirectory );
	void	GetSpecialFolderPath( OUT char* szGetFolderPath, size_t nSize, int nFolder );

	void FrontMsgProcess( sPacketHeader *pPacket );

	void Drawing();

	bool IsCorrectDNS(char* hostname);

	void HanAuth_Lib_HanReportSendPosLog_Client(TCHAR* pszID, TCHAR* pszValue);
	void HanAuth_Lib_HanReportSendPosLog_Client_NHNCHINA(TCHAR* pszUserID, TCHAR* pszValue);	// ��ġ��ó���� ���� ���̵� ����.

	UI32			m_uiCurrentVersion;	
//KHY - 0316 - NHNChina Outbound
#ifdef NHNPATCH_HIDEDLG 	
	void SendMessageToPurple(int nType, LPCTSTR lpszMsg, DWORD dwValue);
#endif // NHNPATCH_HIDEDLG 

// Dialog Data
	//{{AFX_DATA(CPatchDlg)
	enum { IDD = IDD_PATCH_DIALOG };
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
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//afx_msg void OnInitialPatch( WPARAM wParam, LPARAM lParam );
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
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

	HBITMAP			m_hTitleBmp;
	
	char			m_strParameter[ 4096 ];

	int				m_siServiceArea;
	int				m_siRunMode;
	//CProgressCtrl m_DownProgress;
#ifdef _USA_NEW_AUTH_
	bool									m_bUSAAuth;	
	TCHAR									m_szUSAAuth_String[4096];
#endif
#ifdef USE_NDOORS_KOREA
	bool									m_bUSAAuth;	
	TCHAR									m_szUSAAuth_String[4096];
#endif

#ifdef USE_HANAUTH
	// -HanAuth
	TCHAR									m_szHanAuth_GameString[SIZE_GAMESTRING];
	TCHAR									m_szHanAuth_AuthString[SIZE_AUTHSTRING];
	TCHAR									m_szHanAuth_UserID[20];
	int										m_siHanAuth_ServiceTypeCode;

	// -HanAuth
#endif // USE_HANAUTH

//KHY - 0204 -  �߱� PurpleAuth ���� ���
#ifdef USE_PORTEAUTH
	TCHAR									m_szPorteAuth_GameInfoString[SIZE_GAMEINFOSTRING];
	TCHAR									m_szServerIP[20]; // AG�� ������ �������� ���ӿ� IP
#endif // USE_PORTEAUTH
	//int										m_siPorteAuth_ServiceTypeCode;
	TCHAR									m_szPorteAuth_UserID[13]; // User ID size is 12byte
//KHY - 0316 - NHNChina Outbound
#ifdef NHNPATCH_HIDEDLG 
	HWND 									m_hTarget;  // AG�� ������ exLauncher�� �ڵ鷯.
	TCHAR									m_szServerIP[20]; // AG�� ������ �������� ���ӿ� IP
	TCHAR									m_szPortNum[10]; // AG�� ������ �������� ���ӿ� ��Ʈ ��ȣ.
#endif // NHNPATCH_HIDEDLG 


public:
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonStop();
	CProgressST m_DownLoadProgress2;
	//CStatic m_StaticStatus;
	// PCK : ����ǥ�� ��Ʈ�� �߰�
	/*CStatic	m_StaticVersion;*/

	CxSkinButton m_ButtonStart;

	char		m_StatusTextBuffer[256];
	//CStatic m_StaticImage;

	clock_t			m_StartClock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATCHDLG_H__8DEDA850_CC30_4EC3_85A5_DCB17CED762F__INCLUDED_)
