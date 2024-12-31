//---------------------------------
// 2003/11/25 ���°�
//---------------------------------

#include <CommonLogic.h>
#include "Char\CharCommon\Char-Common.h"
#include "..\resource.h"

#include "DevTool.h"


cltDevTool::cltDevTool()
{
	m_hDlg	= NULL;	

	DlgRectInitSwitch	= false;

}

cltDevTool::~cltDevTool()
{
}

// ��ȭ���ڰ� ������ ����� ������ ���ش�. 
bool cltDevTool::Create(HINSTANCE hinst, HWND hwnd, SI32 dlgitem, DLGPROC dlgproc, bool bShow /* = true */ )
{
	// ��ȭ���ڰ� ���� ���¶�� �����. 
	if(!IsWindow(m_hDlg))
	{
		m_hDlg = CreateDialog(hinst, MAKEINTRESOURCE(dlgitem), hwnd, dlgproc);

		if(DlgRectInitSwitch == true)
		{
			MoveWindow(m_hDlg, DlgRect.left, DlgRect.top, DlgRect.right - DlgRect.left, DlgRect.bottom - DlgRect.top, FALSE);
		}

		if( bShow )
			ShowWindow(m_hDlg, SW_SHOW);
		else
			ShowWindow(m_hDlg, SW_HIDE);

		return true;
	}
	else
	{
		DestroyWindow(m_hDlg);
	}

	return false;
	
}

// WM_DESTROY������ ��ġ.
void cltDevTool::ACTION_WM_DESTROY()
{
	// �������� ��ġ�� ����Ѵ�. 
	GetWindowRect(m_hDlg, &DlgRect);
	
	DlgRectInitSwitch = true;

	m_hDlg = NULL;
}

