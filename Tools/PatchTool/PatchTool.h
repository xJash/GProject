// PatchTool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CPatchToolApp:
// �� Ŭ������ ������ ���ؼ��� PatchTool.cpp�� �����Ͻʽÿ�.
//

class CPatchToolApp : public CWinApp
{
public:
	CPatchToolApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CPatchToolApp theApp;
