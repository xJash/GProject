// GoonzuUserlog.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ
#include "LogUnit.h"

// CGoonzuUserlogApp:
// �� Ŭ������ ������ ���ؼ��� GoonzuUserlog.cpp�� �����Ͻʽÿ�.
//

class CGoonzuUserlogApp : public CWinApp
{
public:
	CGoonzuUserlogApp();

// ������
	public:
	virtual BOOL InitInstance();


// ����

	
	DECLARE_MESSAGE_MAP()
};

extern CGoonzuUserlogApp theApp;
