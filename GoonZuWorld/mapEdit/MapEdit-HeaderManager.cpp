//---------------------------------
// 2003/8/4 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\Client\Client.h"


#include <Mouse.h>

#include "mapedit.h"

#include "..\resource.h"

extern cltCommonLogic* pclClient;

// �� ��� ������ ��ȭ ��ȭ�� �����ش�.
BOOL cltMapEdit::OpenMapEditHeaderManager()
{
	return DialogBox(GetInstance(), MAKEINTRESOURCE(IDD_DIALOG_MAPEDIT_MAPHEADER), GetHwnd(), 
		(DLGPROC)StaticHeaderManagerDlgProc);
}

BOOL CALLBACK cltMapEdit::StaticHeaderManagerDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return ((cltMapEdit*)pclClient)->HeaderManagerDlgProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltMapEdit::HeaderManagerDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	TCHAR buffer[256];
	
	switch(iMsg)
	{
	case WM_INITDIALOG:
		// Ÿ�� ��Ʈ�� �ʱⰪ�� �����Ѵ�.
		StringCchPrintf(buffer, 256, TEXT("%d"), pclMapManager->pclCurrentMap->MH.TileSet1);
		SetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET, buffer);

		StringCchPrintf(buffer, 256, TEXT("%d"), pclMapManager->pclCurrentMap->MH.TileSet2);
		SetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET2, buffer);


		// ���� ������ �����Ѵ�. 
		if(pclMapManager->pclCurrentMap->MH.bWeatherSwitch)
		{
			SendMessage(GetDlgItem(hDlg, IDC_CHECK_MAPEDIT_WEATHER), BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendMessage(GetDlgItem(hDlg, IDC_CHECK_MAPEDIT_WEATHER), BM_SETCHECK, BST_UNCHECKED, 0);
		}

		return TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			{
				// Ÿ�� ��Ʈ�� ���´�. 
				// Ÿ�� ��Ʈ�� �ʱⰪ�� �����Ѵ�.
				GetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET, buffer, 60);
				SI32 tileset1 = _tstoi(buffer);

				GetDlgItemText(hDlg, IDC_EDIT_MAPEDIT_TILESET2, buffer, 60);
				SI32 tileset2 = _tstoi(buffer);

				pclMapManager->pclCurrentMap->MH.TileSet1	= tileset1;
				pclMapManager->pclCurrentMap->MH.TileSet2	= tileset2;


				// ���� ������ ���´�. 
				SI32 weatherswitch = SendMessage(GetDlgItem(hDlg, IDC_CHECK_MAPEDIT_WEATHER), BM_GETCHECK, 0, 0);
				if(weatherswitch)
				{
					pclMapManager->pclCurrentMap->MH.bWeatherSwitch = true;
				}
				else
				{
					pclMapManager->pclCurrentMap->MH.bWeatherSwitch = false;
				}

				EndDialog(hDlg, 1);
			}
			return TRUE;

		case IDCANCEL:

			// ������ �����Ѵ�. 
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}




