// GLogClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CGLogClientApp:
// �� Ŭ������ ������ ���ؼ��� GLogClient.cpp�� �����Ͻʽÿ�.
//

class CGLogClientApp : public CWinApp
{
public:
	CGLogClientApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CGLogClientApp theApp;
