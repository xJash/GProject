// GoonzuUserlogDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CItemManager ��ȭ ����
class CItemManager
{

// ����
public:
	CItemManager();
	~CItemManager();

	bool LoadFile(char* itemUnique);
	void FindUnique(char* FileName,char *itemUnique);
	void Set(char * BinaryData, char* ItemUnique);

};
