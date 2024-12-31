/*
//---------------------------------
// 2004/3/22 ������
//---------------------------------

#include "..\Client\Client.h"
#include "CharStatus.h"
#include "..\resource.h"
#include "..\Server\Rank\Rank.h"
#include "..\..\Client\Interface\ErrorMsgDlg\ErrorMsgDlg.h"
#include "Msg\MsgType-Horse.h"

extern cltCommonLogic* pclClient;

#define EXPLAIN_SUMMON_BREED_TYPE		7
char* SummonBreed[]=
{
		"��ȯ���� �����Դϱ�?",				"horsewhat.bmp",
		"��ȯ���� Ű��� ������ �����ϱ�?",	"horsewhatgood.bmp",	
		"��ȯ�� ������ ���ϸ�..?",			"horseage.bmp",	
		"��ȯ���� ��� ����ϱ�?",		"horsehow.bmp",	
		"��ȯ�� Ǯ���ֱ�?",					"horsefree.bmp",
		"��ȯ���� �� Ű��� �����?",		"horsehowbreed.bmp",
		"��ȯ�� ��ȭ��Ű��",				"horseitem.bmp",
};

cltSummonBreedExplain::cltSummonBreedExplain()
{
	m_hDlg	= NULL;
	m_DlgRectInitSwitch = FALSE;
	
	m_hHitBitmap = NULL;
}

cltSummonBreedExplain::~cltSummonBreedExplain()
{
	m_hDlg	= NULL;
	m_DlgRectInitSwitch = FALSE;

	m_hHitBitmap = NULL;
}


bool cltSummonBreedExplain::CreateDlg(HINSTANCE hinst, HWND hwnd)
{
	// ��ȭ���ڰ� ���� ���¶�� �����. 
	if(!IsWindow(m_hDlg))
	{
		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(IDD_DIALOG_STATUS_SUMMON_EXPLAIN), hwnd, SummonBreedExplainStaticProc);
		
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
BOOL CALLBACK cltSummonBreedExplain::SummonBreedExplainStaticProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	cltClient* pclclient = (cltClient*)pclClient;
	return pclclient->pclCharStatus->pclSummonBreedExplain->SummonBreedExplainProc(hDlg, iMsg, wParam, lParam);
}


BOOL CALLBACK cltSummonBreedExplain::SummonBreedExplainProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	SI32 i;
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 1000, NULL);
			
			for(i = 0; i < EXPLAIN_SUMMON_BREED_TYPE; ++i)
			{
				ComboAddString(hDlg, IDC_COMBO_BREED_TYPE, (LPARAM)SummonBreed[i*2]);
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_BREED_TYPE, CB_SETCURSEL, 0, 0 );

			m_siBreedType= 0;
			ShowBreedHit(hDlg, m_siBreedType);
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
			case IDC_COMBO_BREED_TYPE:
				{
					switch(HIWORD(wParam))
					{
					case CBN_SELCHANGE:
						{
							char szWeapon[128] = "NULL";
							ComboGetString(hDlg, IDC_COMBO_BREED_TYPE, (LPARAM)szWeapon);
							
							m_siBreedType = GetBreedType(szWeapon);
							
							ShowBreedHit(hDlg, m_siBreedType);
						}
						break;
					}
					
				}
				return TRUE;

			case IDCANCEL:
				DestroyWindow(m_hDlg);
				m_hDlg = NULL;
				return TRUE;
		}
		return TRUE;
	}
		
	return FALSE;
}


SI32 cltSummonBreedExplain::GetBreedType(char* pBreedType)
{
	SI32 i;
	
	for(i = 0; i < EXPLAIN_SUMMON_BREED_TYPE; ++i)
	{
		if(strcmp(SummonBreed[i*2], pBreedType) == 0)
		{
			return i;
		}
	}
	
	return 0;
}


void cltSummonBreedExplain::ShowBreedHit(HWND hDlg, SI32 siBreedType)
{
	char filename[MAX_PATH];
	sprintf(filename, "StatusHint\\%s", SummonBreed[siBreedType*2+1]);

	if(m_hHitBitmap != NULL)
	{
		DeleteObject(m_hHitBitmap);
		m_hHitBitmap = NULL;
	}

	m_hHitBitmap = (HBITMAP)LoadImage( pclClient->GetInstance(), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
		
	if ( m_hHitBitmap != NULL )
	{
		SendDlgItemMessage( hDlg, IDC_STATIC_STATUS_SUMMON_EXPLAIN, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)m_hHitBitmap);
	}		
		
}



*/