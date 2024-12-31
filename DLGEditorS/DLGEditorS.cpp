// DLGEditorS.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "DLGEditorS.h"
#include "MainFrm.h"

#include "DLGEditorSDoc.h"
#include "DLGEditorSView.h"
#include ".\dlgeditors.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int sDLGUniqueNum;
extern int sBTNUniqueNum;
extern int sCBXUniqueNum;
extern int sETBUniqueNum;
extern int sSTATTUniqueNum;
extern int sIMGSTTUniqueNum;
extern int sLSTBUniqueNum;
extern int sLSTVUniqueNum;
extern int sOUTLNEUniqueNum;
extern int sCHTETBUniqueNum;

// CDLGEditorSApp

BEGIN_MESSAGE_MAP(CDLGEditorSApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
//	ON_COMMAND(ID_DLG_PROPERTY, OnDlgProperty)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()


// CDLGEditorSApp ����

CDLGEditorSApp::CDLGEditorSApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CDLGEditorSApp ��ü�Դϴ�.

CDLGEditorSApp theApp;

// CDLGEditorSApp �ʱ�ȭ

BOOL CDLGEditorSApp::InitInstance()
{
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
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.
	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	// ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDLGEditorSDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CDLGEditorSView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ����ٿ� ������ ����� ����ġ�մϴ�. ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

    m_pMainWnd->DragAcceptFiles();
	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	// SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	return true;
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
void CDLGEditorSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CDLGEditorSApp �޽��� ó����


//void CDLGEditorSApp::OnDlgProperty()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
//}

void CDLGEditorSApp::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	char szFilter [] = "Dialog Design ( *.ddf ) |*.ddf;|All Files(*.*) | *.*||";

	CFileDialog dlg(TRUE, DIALOG_DESIGN_FORMAT_EXT, NULL, OFN_HIDEREADONLY, szFilter );

	if(dlg.DoModal() == IDOK)
	{
		for(POSITION pos = dlg.GetStartPosition(); pos != NULL; )
			OpenDocumentFile(dlg.GetNextPathName(pos));
	}
}

void CDLGEditorSApp::OnFileNew()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	sDLGUniqueNum = 1;
	sBTNUniqueNum = 1;
	sCBXUniqueNum = 1;
	sSTATTUniqueNum = 1;
	sIMGSTTUniqueNum = 1;
	sLSTBUniqueNum = 1;
	sLSTVUniqueNum = 1;
	sOUTLNEUniqueNum = 1;
	sCHTETBUniqueNum = 1;


	CWinApp::OnFileNew();
}
