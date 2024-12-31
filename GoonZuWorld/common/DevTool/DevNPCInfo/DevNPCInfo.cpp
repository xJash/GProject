//---------------------------------
// 2003/11/25 ���°�
//---------------------------------

#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "..\resource.h"

#include "DevNPCInfo.h"

extern cltCommonLogic* pclClient;

cltDevNPCInfo::cltDevNPCInfo(cltCharManager* pclcm) : cltDevTool()
{

}

cltDevNPCInfo::~cltDevNPCInfo()
{

}

BOOL CALLBACK cltDevNPCInfo::DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR buffer[256] = TEXT("");

	switch(iMsg)
	{
	case WM_INITDIALOG:
		{
			// Ÿ�̸Ӹ� �����Ѵ�. 
			SetTimer(hDlg, 1, 1000, NULL);
			
		}
		return TRUE;

	case WM_CHAR:
		return TRUE;

	case WM_TIMER:
		ShowInfo(hDlg);
		return TRUE;

	case WM_DESTROY:
		// Ÿ�̸Ӹ� �����Ѵ�. 
		KillTimer(hDlg, 1);

		// �������� ��ġ�� ����Ѵ�. 
		GetWindowRect(m_hDlg, &DlgRect);

		DlgRectInitSwitch = TRUE;

		m_hDlg = NULL;
		return TRUE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			DestroyWindow(m_hDlg);
			return TRUE;

		case IDCANCEL:
			DestroyWindow(m_hDlg);
			return TRUE;
			
		}
		return TRUE;
	}
	return FALSE;
}

void cltDevNPCInfo::ShowInfo(HWND hDlg)
{
/*	TCHAR buffer[1024];
	HWND hwnd = GetDlgItem(hDlg, IDC_EDIT_CHARINFO);

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		_tcscpy(buffer, TEXT("NO PROPER CHAR\r\n"));
	}
	else
	{

		// ĳ������ ������ �ؽ�Ʈ�� �����ؼ� �޴´�.
		pclCM->CR[id]->GetCharInfoText(buffer);

	}
	
	TCHAR temp[1024];
	sprintf(temp, TEXT("\r\n�ε�Ÿ�Ϲ���Ʈ:[%d]\r\n"), pclClient->pclTileSet->siLoadedTileSetImageSize);
	strcat(buffer, temp);
	sprintf(temp, TEXT("�ε�FieldObj:[%d]\r\n"), pclClient->pclFieldObjectSet->siLoadedSize);
	strcat(buffer, temp);
	

	SetWindowText(hwnd, buffer);
	*/
}