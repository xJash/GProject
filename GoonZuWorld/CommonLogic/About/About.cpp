//---------------------------------
// 2003/5/17 ���°�
//---------------------------------

#include "..\Common\CommonHeader.h"
#include "..\CommonLogic\CommonLogic.h"
#include "../../resource.h"

extern cltCommonLogic* pclClient;

BOOL cltCommonLogic::About()
{

	return DialogBox(GetInstance(), MAKEINTRESOURCE(IDD_ABOUT), GetHwnd(), (DLGPROC)StaticAboutDlgProc);
}

BOOL CALLBACK cltCommonLogic::StaticAboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	return pclClient->AboutDlgProc(hDlg, iMsg, wParam, lParam);
}

BOOL CALLBACK cltCommonLogic::AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch(iMsg)
	{
	case WM_INITDIALOG:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		SetTimer(hDlg, 1, 4000, NULL);

		return TRUE;

	case WM_TIMER:
		EndDialog(hDlg, 0);
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);
		return TRUE;


	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;

		}
		break;
	}

	return FALSE;

}
