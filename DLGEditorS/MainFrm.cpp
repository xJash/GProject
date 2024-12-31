// MainFrm.cpp : CMainFrame Ŭ������ ����
//

#include "stdafx.h"
#include "DLGEditorS.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#include "./MyDefine/MyDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_StartPath;	// ���� path
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_MOVE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,           // ���� �� ǥ�ñ�
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/�Ҹ�

CMainFrame::CMainFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
	m_pSplitterWnd = NULL;
	m_pSplitterWnd2 = NULL;
}

CMainFrame::~CMainFrame()
{
	if(m_pSplitterWnd != NULL) delete m_pSplitterWnd;
	if(m_pSplitterWnd2 != NULL) delete m_pSplitterWnd2;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("���� ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("���� ǥ������ ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	m_wndStatusBar.SetPaneInfo( 0, ID_SEPARATOR, SBPS_NORMAL, 20);
	m_wndStatusBar.SetPaneInfo( 1, ID_SEPARATOR, SBPS_NORMAL, 300);
	m_wndStatusBar.SetPaneInfo( 2, ID_SEPARATOR, SBPS_NORMAL, 300);

	//if (!m_wndDialogBar.Create(this, IDD_DLGPROPERTYDLG/*IDD_DLGBAR_BASE*/, CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_GRIPPER | CBRS_SIZE_DYNAMIC, 
	//	IDD_DLGPROPERTYDLG/*IDD_DLGBAR_BASE*/))
	//{
	//	TRACE0("���̾�α׹ٸ� ������ ���߽��ϴ�.\n");
	//	return -1;
	//}

	char curPath[512];
	char fullPath[1024];
	memset(curPath, 0, 512);
	memset(fullPath, 0, 512);
	DWORD length = GetCurrentDirectory(512, curPath);
	// patchinfo
	_snprintf(fullPath, 1024, "%s\\DLGSetting.txt", curPath);

	g_StartPath = fullPath;

	//m_wndDialogBar.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndDialogBar);
	// TODO: ���� ������ ��ŷ�� �� ���� �Ϸ��� �� �� ���� �����Ͻʽÿ�.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	// Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.x = WIN_STARTX;
	cs.y = WIN_STARTY;
	cs.cx = WIN_WIDTH;
	cs.cy = WIN_HEIGHT;

	SetTitle(WIN_TITLE);

	return true;
}


// CMainFrame ����

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame �޽��� ó����


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	// //SplitterWnd ������..
	//// Base SplitterWnd ����!!
	//m_pSplitterWnd = new CSplitterWnd_Base();

	//m_pSplitterWnd->Create( this, RUNTIME_CLASS(CSplitterWndViewToolBar), RUNTIME_CLASS(CSplitterWndView), pContext, true );
	//
	//m_nViewNo[0] = m_pSplitterWnd->AddView(RIGHT_SIDE, RUNTIME_CLASS(CSplitterWndView), pContext);
	////m_nViewNo[1] = m_pSplitterWnd->AddView(RIGHT_SIDE, RUNTIME_CLASS(CSplitterWndView), pContext);

	//// empty function
	//m_pSplitterWnd->SetInitialStatus();
	//
	//return true;
	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnMove(int x, int y)
{
	CFrameWnd::OnMove(x, y);

	if ( g_bMagnetMode == FALSE ) return;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CString strDialogName[] = {"��ư ��Ʈ�� �Ӽ�"
		, "���̾�α� �Ӽ�â"
		, "�޺��ڽ� ��Ʈ�� �Ӽ�"
		, "����Ʈ�ڽ� ��Ʈ�� �Ӽ�"
		, "���� �ؽ�Ʈ �Ӽ�"
		, "����Ʈ�ڽ� ��Ʈ�� �Ӽ�"
		, "���� �̹��� ��Ʈ�� �Ӽ�"
		, "����Ʈ�� ��Ʈ�� �Ӽ�"
		, "üũ�ڽ� ��Ʈ�� �Ӽ�"
		, "������ư ��Ʈ�� �Ӽ�"
		, "�ܰ��� �׸��� �Ӽ�"
		, "ä�� ����Ʈ �Ӽ�"
	};


	CWnd* pwProperty = NULL;

	

	for (int i=0; i<12; i++)
	{
		pwProperty = FindWindow( NULL, strDialogName[i] );
		
		if ( pwProperty )
		{
			if ( !pwProperty->IsWindowVisible() ) continue;

			CRect rectParent, rectChile;
		
			this->GetWindowRect( rectParent );
			pwProperty->GetWindowRect( rectChile );

			rectChile.MoveToXY( (rectParent.right), rectParent.top );
			pwProperty->MoveWindow( rectChile );
			
			break;
		}
		pwProperty = NULL;
	}

}