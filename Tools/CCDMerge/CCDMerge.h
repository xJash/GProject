// CCDMerge.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CCCDMergeApp:
// �� Ŭ������ ������ ���ؼ��� CCDMerge.cpp�� �����Ͻʽÿ�.
//

class CCCDMergeApp : public CWinApp
{
public:
	CCCDMergeApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CCCDMergeApp theApp;
