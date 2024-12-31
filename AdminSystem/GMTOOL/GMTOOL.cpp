// GMTOOL.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "GMTOOL.h"
#include "MainFrm.h"

#include "Log/LogFrame.h"
#include "NewLog/NewLogFrame.h"
#include "Id/IdFrame.h"
#include "Guild/GuildFrame.h"
#include "Char/CharFrame.h"
#include "Item/ItemFrame.h"
#include "Block/BlockFrame.h"
#include "GMClient/GMClientFrame.h"
//#include "StaticCenterFrame.h"
//#include "InformationChangeFrame.h"
//#include "CharactorRecoveryFrame.h"
#include "Notice/NoticeFrame.h"
#include "TradeLog/TradeLogFrame.h"
#include "SelledLog/SelledLogFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGMTOOLApp

BEGIN_MESSAGE_MAP(CGMTOOLApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_MENU_LOG, OnMenuLog)
	ON_COMMAND(ID_MENU_GUILD, OnMenuGuild)
	ON_COMMAND(ID_MENU_ID, OnMenuId)
	ON_COMMAND(ID_MENU_CHAR, OnMenuChar)
	//ON_COMMAND(ID_MENU_ITEM, OnMenuItem)
	//ON_COMMAND(ID_MENU_BLOCK, OnMenuBlock)
	//ON_COMMAND(ID_MENU_STATICS, OnMenuStatics)
	//ON_COMMAND(ID_MENU_INFOR, OnMenuInfor)
	//ON_COMMAND(ID_MENU_RECOVER, OnMenuRecover)
	ON_COMMAND(ID_MENU_NOTICE, OnMenuNotice)
	ON_COMMAND(ID_MENU_BLOCKCHAR, OnMenuBlockchar)
	//ON_COMMAND(ID_MENU_ITEM, OnMenuItem)
	ON_COMMAND(ID_MENU_ITEM, OnMenuItem)
	ON_COMMAND(32806, OnMenuNewLog)
	ON_COMMAND(ID_MENU_GMCLIENT, OnMenuGmclient)
	ON_COMMAND(ID_MENU_TRADELOG, OnMenuTradeLog)
	ON_COMMAND(ID_MENU_SELLEDLOG, OnMenuSelledLog)
END_MESSAGE_MAP()


// CGMTOOLApp ����

CGMTOOLApp::CGMTOOLApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CGMTOOLApp ��ü�Դϴ�.

CGMTOOLApp theApp;

// CGMTOOLApp �ʱ�ȭ

BOOL CGMTOOLApp::InitInstance()//�ʱ�ȭ �Լ��κ�.
{
//	_CrtSetBreakAlloc(406);

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControls()�� �ʿ��մϴ�. 
	// InitCommonControls()�� ������� ������ â�� ���� �� �����ϴ�.
	InitCommonControls();

	CWinApp::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// ���� ���̺귯�� �ʱ�ȭ
	AfxSocketInit();

	
	char	szPath[MAX_PATH];
	char	szExecuteFile[MAX_PATH];
	::GetModuleFileName(NULL, szExecuteFile, MAX_PATH);
	char*	pFind = strrchr(szExecuteFile, '\\');
	szExecuteFile[pFind - szExecuteFile] = '\0';
	strcpy(szPath, szExecuteFile);

	//strcpy(szIniPath, szPath);
	TCHAR	szIniPath[MAX_PATH] = { '\0', };
	strcpy(szIniPath, "LogData\\Setting.ini");

	DWORD	dwLen;
	TCHAR	szRegistryKey[MAX_PATH] = { '\0', };
	TCHAR	szServiceArea[64] = { '\0', };
	TCHAR	szLanguage[32] = { '\0', };

	if (SERVICEAREA == ConstServiceArea_Korea)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuS"));
		StringCchCopy(szLanguage, 32 , TEXT("KOREAN"));
	}
	else if (SERVICEAREA == ConstServiceArea_Taiwan)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuTaiwan"));
		StringCchCopy(szLanguage, 32 , TEXT("TAIWAN"));
	}
	else if (SERVICEAREA == ConstServiceArea_Japan)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\GamePot\\Kunshu Online"));
		StringCchCopy(szLanguage, 32 , TEXT("JAPAN"));
	}
	else if (SERVICEAREA == ConstServiceArea_English)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuEng"));
		StringCchCopy(szLanguage, 32 , TEXT("ENGLISH"));
	}
	else if (SERVICEAREA == ConstServiceArea_EUROPE)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuEurope"));
		StringCchCopy(szLanguage, 32 , TEXT("EUROPE"));
	}
	else if (SERVICEAREA == ConstServiceArea_NHNChina)
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuC"));
		StringCchCopy(szLanguage, 32 , TEXT("CHINA"));
	}
	else
	{
		StringCchCopy(szRegistryKey, MAX_PATH , TEXT("Software\\NDOORS\\GoonZuS"));
		StringCchCopy(szLanguage, 32 , TEXT("KOREAN"));
	}

	HKEY	hKey;
	TCHAR	szGamePath[MAX_PATH] = { '\0', };

	//KHY - 0112 - �߱��� ������Ʈ���� ���� �ʰ�, ���������Ѵ�.
	if(SERVICEAREA == ConstServiceArea_NHNChina)
	{
		strcpy(szGamePath, szRegistryKey);
	}
	else
	{
		RegCreateKey(HKEY_CURRENT_USER, szRegistryKey, &hKey);
		if(hKey != NULL)
		{
			DWORD ldwSize = MAX_PATH;
			RegQueryValueEx( hKey, "PATH", 0, NULL, (LPBYTE)szGamePath, &ldwSize );
			RegCloseKey( hKey );
			hKey = NULL;
		}
	}

	m_kDataManager.m_siServiceArea = ConstServiceArea_USA;
	m_kDataManager.Init( szLanguage);

	TCHAR	szCurrentDir[MAX_PATH];

	if( szGamePath != NULL && _tcslen(szGamePath) > 0 )
	{
		GetCurrentDirectory(MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szGamePath);
	}

	m_kDataManager.InitGameData( SERVICEAREA);

	m_clItemManagerClient.InIt(m_kDataManager);
	m_clItemManagerClient.SetItemData(SERVICEAREA);

	if( szGamePath != NULL && _tcslen(szGamePath) > 0 )
	{
		SetCurrentDirectory(szCurrentDir);
	}

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	// �� â�� ����� ���� �� �ڵ忡���� �� ������ â ��ü��
	// ���� ���� �̸� ���� ���α׷��� �� â ��ü�� �����մϴ�.
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// �� MDI ������ â�� ����ϴ�.
	if (!pFrame->LoadFrame(IDR_MAINFRAME1))
		return FALSE;
	// ���� MDI �޴� �� �׼��������� Ű ���̺��� �ε带 �õ��մϴ�.
	//TODO: �߰� ��� ������ �߰��ϰ� ���� ���α׷��� �ʿ��� �߰� �޴� ���Ŀ� ����
	//	 ȣ���� �ε��մϴ�.
	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_GMTOOLTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_GMTOOLTYPE));
	// �� â�� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();

	//OnMenuLog();

	return TRUE;
}


// CGMTOOLApp �޽��� ó����

int CGMTOOLApp::ExitInstance() 
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

void CGMTOOLApp::OnMenuLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// �� MDI �ڽ� â�� ����ϴ�.
	pFrame->CreateNewChild(RUNTIME_CLASS(CLogFrame), IDR_GMTOOL_LOG, m_hMDIMenu, m_hMDIAccel);
}


void CGMTOOLApp::OnMenuId()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame,m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CIdFrame), IDR_GMTOOL_ID, m_hMDIMenu, m_hMDIAccel);

}

void CGMTOOLApp::OnMenuGuild()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CGuildFrame),IDR_GMTOOL_GUILD, m_hMDIMenu, m_hMDIAccel );
}




// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

	// ����
protected:
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnMenuGuild();
	//	afx_msg void OnMenuItem();
	afx_msg void OnMenuChar();
	//	afx_msg void OnMenuInfor();
	afx_msg void OnMenuNotice();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CGMTOOLApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CGMTOOLApp �޽��� ó����






void CGMTOOLApp::OnMenuChar()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
	CMDIChildWnd* pkMDIChild = pFrame->GetChild(CHILD_CHAR);
	if(pkMDIChild == NULL || pkMDIChild->m_hWnd == NULL)
	{
		CMDIChildWnd* pkNewChild = pFrame->CreateNewChild(RUNTIME_CLASS(CCharFrame),IDR_GMTOOL_CHAR, m_hMDIMenu, m_hMDIAccel );
		pFrame->SetChild(CHILD_CHAR, pkNewChild);
	}
	else
	{
		CMDIChildWnd* pkMDIChild = pFrame->GetChild(CHILD_CHAR);
		pFrame->MDIActivate(pkMDIChild);
	}
}


//void CGMTOOLApp::OnMenuItem()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
//
//	pFrame->CreateNewChild(RUNTIME_CLASS(CItemFrame),IDR_GMTOOL_ITEM, m_hMDIMenu, m_hMDIAccel );
//}
//


//void CGMTOOLApp::OnMenuStatics()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
//
//	pFrame->CreateNewChild(RUNTIME_CLASS(CStaticCenterFrame),IDR_GMTOOL_STATICS, m_hMDIMenu, m_hMDIAccel );
//
//}


//void CGMTOOLApp::OnMenuInfor()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
//
//	pFrame->CreateNewChild(RUNTIME_CLASS(CInformationChangeFrame),IDR_GMTOOL_CHANGEINFOR, m_hMDIMenu, m_hMDIAccel );
//
//}



//void CGMTOOLApp::OnMenuRecover()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//
//	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
//
//	pFrame->CreateNewChild(RUNTIME_CLASS(CCharactorRecoveryFrame),IDR_GMTOOL_RECOVER, m_hMDIMenu, m_hMDIAccel );
//}


void CGMTOOLApp::OnMenuNotice()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CNoticeFrame),IDR_GMTOOL_NOTICE, m_hMDIMenu, m_hMDIAccel );


}

void CGMTOOLApp::OnMenuBlockchar()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CBlockFrame),IDR_GMTOOL_BLOCKCHAR, m_hMDIMenu, m_hMDIAccel );
}

void CGMTOOLApp::OnMenuTradeLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CTradeLogFrame),IDR_GMTOOL_TRADELOG, m_hMDIMenu, m_hMDIAccel );
}

void CGMTOOLApp::OnMenuSelledLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CSelledLogFrame),IDR_GMTOOL_SELLEDLOG, m_hMDIMenu, m_hMDIAccel );
}

//void CGMTOOLApp::OnMenuItem()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);
//	pFrame->CreateNewChild(RUNTIME_CLASS(CItemFrame),IDR_GMTOOL_ITEM, m_hMDIMenu, m_hMDIAccel );
//}

void CGMTOOLApp::OnMenuItem()
{
	return;

	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	pFrame->CreateNewChild(RUNTIME_CLASS(CItemFrame),IDR_GMTOOL_ITEM, m_hMDIMenu, m_hMDIAccel );
}

CNewLogFrame* CGMTOOLApp::CreatNewLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// �� MDI �ڽ� â�� ����ϴ�.
	CNewLogFrame* pNewLogFrame = (CNewLogFrame*)pFrame->CreateNewChild(RUNTIME_CLASS(CNewLogFrame), IDR_GMTOOL_NEWLOG, m_hMDIMenu, m_hMDIAccel);
	pNewLogFrame->m_pclItemManagerClient = &m_clItemManagerClient;

	pNewLogFrame->ActivateFrame( SW_NORMAL);

	return pNewLogFrame;
}

void CGMTOOLApp::OnMenuNewLog()
{
	CreatNewLog();
}

void CGMTOOLApp::OnMenuGmclient()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// �� MDI �ڽ� â�� ����ϴ�.
	pFrame->CreateNewChild(RUNTIME_CLASS(CGMClientFrame), IDR_GMTOOL_GMCLIENT, m_hMDIMenu, m_hMDIAccel);
}
