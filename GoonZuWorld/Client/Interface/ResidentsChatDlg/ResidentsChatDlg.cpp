#include "ResidentsChatDlg.h"
#include "ResidentsChatDataMgr.h"
#include "..\..\FontManager\FontManager.h"


CResidentsChatDlg	g_ResidentsChatDlg;


CResidentsChatDlg::CResidentsChatDlg()
{	
	m_hDlg = NULL;
	m_hChatViewBrush = NULL;
	m_hChatInputBrush = NULL;
	m_hDlg = NULL;
	m_bShowFlag = false;

	m_hChatDataViewEdit = NULL;
	m_hChatDataInputEdit = NULL;

	m_pChatDataViewMgr = new CResidentsChatDataMgr( true );
	m_pChatDataViewMgr->CreateMaxEmptyObj( MAX_CHAT_DATA_RECORD_NUM );

	m_pChatDataSendMgr = new CResidentsChatDataMgr( false );
	m_pChatDataSendMgr->CreateMaxEmptyObj( MAX_CHAT_DATA_BUFFER_NUM );

	m_strChatViewData = new char[ ( MAX_PLAYER_NAME + MAX_CHAT_DATA_LENGTH + 10 ) * MAX_CHAT_DATA_RECORD_NUM ];
	memset( m_strChatViewData, 0, ( MAX_PLAYER_NAME + MAX_CHAT_DATA_LENGTH + 10 ) * MAX_CHAT_DATA_RECORD_NUM );

	Initialize();
}

CResidentsChatDlg::~CResidentsChatDlg()
{
	Destroy();

	if ( m_hDlg )
	{
		DestroyWindow( m_hDlg );
	}
}

void CResidentsChatDlg::Create( HINSTANCE hInst, HWND hWnd )
{
	m_hDlg = CreateDialog( hInst, MAKEINTRESOURCE( IDD_DIALOG_RESIDENTS_CHAT ), hWnd, StaticResidentsChatDlgProc );
	Hide();
	return;
}

void CResidentsChatDlg::Initialize()
{
	return;
}

void CResidentsChatDlg::Destroy()
{
	if ( m_pChatDataViewMgr )
	{
		delete m_pChatDataViewMgr;
		m_pChatDataViewMgr = NULL;
	}

	if ( m_pChatDataSendMgr )
	{
		delete m_pChatDataSendMgr;
		m_pChatDataSendMgr = NULL;
	}

	if ( m_strChatViewData )
	{
		delete [] m_strChatViewData;
		m_strChatViewData = NULL;
	}

	return;
}

LRESULT CALLBACK CResidentsChatDlg::StaticEditSubProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return g_ResidentsChatDlg.EditSubProc( hWnd, msg, wParam, lParam );
}


LRESULT CALLBACK CResidentsChatDlg::EditSubProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) 
	{
	case WM_CHAR :
		if( wParam == VK_RETURN )
		{
			if ( m_hDlg )
			{
				memset( m_strChatData, 0, MAX_CHAT_DATA_LENGTH );
				GetWindowText( hWnd, m_strChatData, MAX_CHAT_DATA_LENGTH );

				// ��Ʈ���� ���̰� 0���� ū ��츸 ����. 
				// �ߺ��� ä�� �����͵� ���ƾ� ��... ( �峭��� ��� ���� �� �����Ƿ�.. )
				if ( strlen( m_strChatData ) > 0 )
				{
					Push();
					SetWindowText( m_hChatDataInputEdit, "" );
				}
			}
		}
		else if (wParam == VK_ESCAPE )
		{
			SetWindowText( m_hChatDataInputEdit, "" );
		}

		break;
	default :
		break;
    }

    return CallWindowProc( m_OldEditProc, hWnd, msg, wParam, lParam );
}

BOOL CALLBACK CResidentsChatDlg::StaticResidentsChatDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return g_ResidentsChatDlg.ResidentsChatDlgProc( hDlg, iMsg, wParam, lParam );
}

BOOL CALLBACK CResidentsChatDlg::ResidentsChatDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch( iMsg )
	{

	case WM_INITDIALOG:
		{
			m_hDlg = hDlg;
			g_FontManager.SetFont( hDlg, IDC_EDIT_RECV_CHAT_DATA );
			g_FontManager.SetFont( hDlg, IDC_EDIT_CHAT_INPUT );

			m_hChatDataViewEdit = GetDlgItem( hDlg, IDC_EDIT_RECV_CHAT_DATA );
			m_hChatDataInputEdit = GetDlgItem( hDlg, IDC_EDIT_CHAT_INPUT );

			m_hChatViewBrush = CreateSolidBrush( COLOR_DIALOG_WHITE );
			m_hChatInputBrush = CreateSolidBrush( COLOR_DIALOG_WHITE );

			SendMessage( m_hChatDataInputEdit, EM_LIMITTEXT, MAX_CHAT_DATA_LENGTH - 2, 0 );

			m_OldEditProc = (WNDPROC)SetWindowLong( m_hChatDataInputEdit, GWL_WNDPROC, (LONG)StaticEditSubProc);

			return TRUE;
		}
		break;
	
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
			case IDCANCEL:
				{
					Hide();
				}
				break;

			}
		}
		break;
	
	case WM_CTLCOLORSTATIC:				// ����Ʈ �ڽ��� disable �̰ų� read only �� ��� �̸��� ��
		{
			if ( m_hChatDataViewEdit == ( HWND ) lParam )
			{
				
				HDC hdc = ( HDC ) wParam;
				
				//SetBkMode( hdc, TRANSPARENT );			//<---- �̰� ���� ��ũ�� �ÿ� ���ڰ� ��ġ�� �̻��� ���� �߻�. �׷��� �ּ�ó�� ����.
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITE);
				
				return (BOOL)m_hChatViewBrush;
			}
		}
		break;

  
	case WM_CTLCOLOREDIT:
		{
			if ( m_hChatDataInputEdit == ( HWND ) lParam )
			{
				HDC hdc = ( HDC ) wParam;

				SetBkMode( hdc, TRANSPARENT );
				SetTextColor( hdc, COLOR_DIALOG_BLACK );
				SetBkColor( hdc, COLOR_DIALOG_WHITE);

				return (BOOL)m_hChatInputBrush;
			}
		}
		break;
	

	case WM_CLOSE:
		{
			Hide();
		}
		break;

	case WM_DESTROY:
		{
			if ( m_hChatViewBrush )
			{
				DeleteObject( m_hChatViewBrush );
				m_hChatViewBrush = NULL;
			}

			if ( m_hChatInputBrush )
			{
				DeleteObject( m_hChatInputBrush );
				m_hChatInputBrush = NULL;
			}

			SetWindowLong( m_hChatDataInputEdit, GWL_WNDPROC, (LONG) m_OldEditProc );
			Hide();

			m_hDlg = NULL ;
		}
		break;
	}

	return FALSE;
}

void CResidentsChatDlg::LoadData()
{
	m_pChatDataViewMgr->LoadData( m_strChatViewData );

	//SetWindowText( m_hChatDataViewEdit, m_strChatViewData );

	SetWindowText( m_hChatDataViewEdit, "" );
	SendMessage( m_hChatDataViewEdit, EM_SETSEL, (WPARAM)-1, (LPARAM)-1 );
	SendMessage( m_hChatDataViewEdit, EM_REPLACESEL, 0, (LPARAM)m_strChatViewData );


	return;
}

// ���̾�α� ���� �ֱ�	
void CResidentsChatDlg::Show()
{
	if ( m_bShowFlag )
	{
		return;
	}

	m_bShowFlag = true;	
	ShowWindow ( m_hDlg, SW_SHOWNORMAL );

	return;
}

// ���̾�α� �����
void CResidentsChatDlg::Hide()
{
	if ( ! m_bShowFlag )
	{
		return;
	}

	m_bShowFlag = false;	
	ShowWindow( m_hDlg, SW_HIDE );

	return;
}

bool CResidentsChatDlg::IsShow()
{
	return m_bShowFlag;
}

void CResidentsChatDlg::Push()
{
	m_pChatDataSendMgr->Push( RESIDENTS_CHAT_DATA_SEND, m_strChatData );
	
	return;
}

void CResidentsChatDlg::Push( char *strUserID, char *strChatRecvData )
{
	m_pChatDataViewMgr->Push( strUserID, strChatRecvData );
	LoadData();
	return;
}

bool CResidentsChatDlg::Pop( stChatStatusBarData *pChatStatusBarData )
{
	return m_pChatDataSendMgr->Pop( pChatStatusBarData );
}