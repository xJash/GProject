// GoonzuUserlogDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CVillageManager ��ȭ ����
class CVillageManager
{

// ����
public:
	CVillageManager();
	~CVillageManager();

	char village_name[64];
	void FindVillage(char *itemUnique);
	bool IsNumber(LPCTSTR pszText);
	char* Set(char *VillageUnique);

};
