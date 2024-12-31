//---------------------------------
// 2003/6/26 ���°�
//---------------------------------
#include <CommonLogic.h>

#include "Char\CharCommon\Char-Common.h"
#include "Char\CharManager\CharManager.h"
#include "..\..\Common\Util\Control\Control.h"

#include "..\..\Resource.h"

#include "MsgType-Person.h"
#include "MsgType-House.h"

#include "House.h"

#include "../../Client/Client.h"
#include "../Client/NStructureDlg/House/UserInfo/NHouseUserInfoBaseDlg.h"
#include "../Client/Interface/SoundOnOffDlg/SoundOnOffDlg.h"

extern cltCommonLogic* pclClient;

// ��������Ʈ�� �����.
BOOL cltHouseManager::MakeHouseUnitList(HWND hDlg)
{
	// �̹��� ����Ʈ�� ����Ʈ �� ��Ʈ�ѿ� ����Ѵ�. 
	HWND hwnd = GetDlgItem(hDlg, IDC_LIST_HOUSEUNITLIST);
	
	if(hImageList)
	{
		SendMessage(hwnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)hImageList);
	}

	ListView_SetExtendedListViewStyle(hwnd, LVS_EX_FULLROWSELECT);
	

	// �÷��� �߰��Ѵ�. 
	char* pText = GetTxtFromMgr(1695);
	ListViewInsertColumn(hwnd, 60,		pText,		0, 0);
	pText = GetTxtFromMgr(1696);
	ListViewInsertColumn(hwnd, 90,		pText,	1, 0);
	pText = GetTxtFromMgr(1697);
	ListViewInsertColumn(hwnd, 180,		pText,		2, 0);

	return TRUE;
}


// ��������Ʈ�� �����ش�. 
BOOL cltHouseManager::ShowHouseUnitList(HWND hDlg)
{
	SI32 i;
	char buffer[256];

	HWND hwnd = GetDlgItem(hDlg, IDC_LIST_HOUSEUNITLIST);

	// ����Ʈ�並 ��� �����. 
	ListviewDelete(hDlg, IDC_LIST_HOUSEUNITLIST);

	for(i = (MAX_HOUSEUNIT_NUMBER-1);i >= 0 ;i--)
	{
		sprintf(buffer, "%d", i+1);
		ListViewInsertItem(hwnd, 0,		0, 0, buffer, i);

		if(clClientUnit[i].clPerson.GetPersonID())
		{
			ListViewInsertItem(hwnd, -1,	0, 1, (char*)clClientUnit[i].clPerson.GetName(), -1);
			ListViewInsertItem(hwnd, -1,	0, 2, "NOTEXT", -1);
		}
		else
		{
			char* pText = GetTxtFromMgr(1691);

			ListViewInsertItem(hwnd, -1,	0, 1, pText, -1);
		}
	}
	
	return TRUE;
}