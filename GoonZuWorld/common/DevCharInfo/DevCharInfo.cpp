//---------------------------------
// 2003/7/17 ���°�
//---------------------------------

#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "..\resource.h"

#include "DevCharInfo.h"

extern cltCommonLogic* pclClient;

cltDevCharInfo::cltDevCharInfo(cltCharManager* pclcm)
{

	m_hDlg	= NULL;
	
		TabDlg	= NULL;

	DlgRectInitSwitch = FALSE;

	CharUnique = 0;

	pclCM	= pclcm;

}

cltDevCharInfo::~cltDevCharInfo()
{

}

BOOL CALLBACK cltDevCharInfo::DevCharInfoDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	char buffer[128];

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
		ShowCharInfo(hDlg);
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
		case IDC_BUTTON_DEV_CHARUNIQUE:
			GetDlgItemText(hDlg, IDC_EDIT_CHARUNIQUE, buffer, 100);
			CharUnique = atoi(buffer);

			break;

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

void cltDevCharInfo::ShowCharInfo(HWND hDlg)
{
	char buffer[1024];
	HWND hwnd = GetDlgItem(hDlg, IDC_EDIT_CHARINFO);

	SI32 id = cltCharCommon::CharUniqueInfo[CharUnique];
	if(id == 0)
	{
		strcpy(buffer, "NO PROPER CHAR\r\n");
	}
	else
	{

		// ĳ������ ������ �ؽ�Ʈ�� �����ؼ� �޴´�.
		pclCM->CR[id]->GetCharInfoText(buffer);

	}
	
	char temp[1024];
	sprintf(temp, "\r\n�ε�Ÿ�Ϲ���Ʈ:[%d]\r\n", pclClient->pclTileSet->siLoadedTileSetImageSize);
	strcat(buffer, temp);
	sprintf(temp, "�ε�FieldObj:[%d]\r\n", pclClient->pclFieldObjectSet->siLoadedSize);
	strcat(buffer, temp);
	

	SetWindowText(hwnd, buffer);
}