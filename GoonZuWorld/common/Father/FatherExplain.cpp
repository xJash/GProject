/*
//---------------------------------
// 2004/3/22 ������
//---------------------------------

#include "..\Client\Client.h"
#include "Father.h"
#include "..\resource.h"
#include "..\Server\Rank\Rank.h"
#include "..\..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Msg\MsgType-Horse.h"

extern cltCommonLogic* pclClient;

#define EXPLAIN_FATHER_TYPE		6
char* StatusFather[]=
{
		"���´��� �����Դϱ�?",					"FatherWho.bmp",
		"���ڰ� �ǰ� ��������?",				"Father1.bmp",	
		"���´��� �ٲٰ� ��������?",			"ChangeFather.bmp",
		"���ڰ� �������� ������ ���� ������?",	"EndFather.bmp",
		"������ �ǰ� ��������?",				"Father2.bmp",
		"������ �Ǹ� ������ ��������?",			"FatherWhatCool.bmp",
};

cltFatherExplain::cltFatherExplain()
{
	m_hDlg	= NULL;
	m_DlgRectInitSwitch = FALSE;
	
	m_hHitBitmap = NULL;
}

cltFatherExplain::~cltFatherExplain()
{
	m_hDlg	= NULL;
	m_DlgRectInitSwitch = FALSE;

	m_hHitBitmap = NULL;
}


bool cltFatherExplain::CreateDlg(HINSTANCE hinst, HWND hwnd)
{
	// ��ȭ���ڰ� ���� ���¶�� �����. 
	if(!IsWindow(m_hDlg))
	{
		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG_FATHER_EXPLAIN), hwnd, FatherExplainStaticProc);
		
		if(m_DlgRectInitSwitch == TRUE)
		{
			MoveWindow(m_hDlg, 
				m_DlgRect.left,	 m_DlgRect.top, 
				m_DlgRect.right - m_DlgRect.left, 
				m_DlgRect.bottom - m_DlgRect.top, FALSE);
		}

		ShowWindow(m_hDlg, SW_SHOW);
		
		return TRUE;
	}
	else
	{
		DestroyWindow(m_hDlg);
	}
	
	return FALSE;	
}
BOOL CALLBACK cltFatherExplain::FatherExplainStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;
	return pclclient->pclFatherManager->pclFatherExplain->FatherExplainProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltFatherExplain::FatherExplainProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 i;
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 1000, NULL);
			
			for(i = 0; i < EXPLAIN_FATHER_TYPE; ++i)
			{
				ComboAddString(hDlg, IDC_COMBO_FATHER_TYPE, (LPARAM)StatusFather[i*2]);
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_FATHER_TYPE, CB_SETCURSEL, 0, 0 );

			m_siFatherType= 0;
			ShowFatherHit(hDlg, m_siFatherType);
		}
		return TRUE;
		
		
	case WM_TIMER:
		return TRUE;
		
	case WM_DESTROY:
		// �ʻ�ȭ�� �ڵ��� �����Ѵ�.
		if(m_hHitBitmap)
		{
			DeleteObject(m_hHitBitmap);
			m_hHitBitmap = NULL;
		}
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);
		
		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(m_hDlg, &m_DlgRect);
		m_DlgRectInitSwitch = TRUE;
		m_hDlg = NULL;
		return TRUE;
		
	case WM_NOTIFY:
		return TRUE;
		
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_COMBO_FATHER_TYPE:
				{
					switch(HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						{
							char szFather[128] = "NULL";
							ComboGetString(hDlg, IDC_COMBO_FATHER_TYPE, (LPARAM)szFather);
							
							m_siFatherType = GetFatherType(szFather);
							
							ShowFatherHit(hDlg, m_siFatherType);
						}
						break;
					}
					
				}
				return TRUE;

			case IDCANCEL:
				DestroyWindow(m_hDlg);
				return TRUE;
		}
		return TRUE;
	}
		
	return FALSE;
}


SI32 cltFatherExplain::GetFatherType(char* pFatherType)
{
	SI32 i;
	
	for(i = 0; i < EXPLAIN_FATHER_TYPE; ++i)
	{
		if(strcmp(StatusFather[i*2], pFatherType) == 0)
		{
			return i;
		}
	}
	
	return 0;
}


void cltFatherExplain::ShowFatherHit(HWND hDlg, SI32 siFatherType)
{
	char filename[MAX_PATH];
	sprintf(filename, "FatherHint\\%s", StatusFather[siFatherType*2+1]);

	if(m_hHitBitmap != NULL)
	{
		DeleteObject(m_hHitBitmap);
		m_hHitBitmap = NULL;
	}

	m_hHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		
	if ( m_hHitBitmap != NULL )
	{
		SendDlgItemMessage( hDlg, IDC_STATIC_STATUS_EXPLAIN, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHitBitmap);
	}		
		
}

*/