// MapTileDiv.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CMapTileDivApp:
// �� Ŭ������ ������ ���ؼ��� MapTileDiv.cpp�� �����Ͻʽÿ�.
//

class CMapTileDivApp : public CWinApp
{
public:
	CMapTileDivApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CMapTileDivApp theApp;
