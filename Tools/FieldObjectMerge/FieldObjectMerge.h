// FieldObjectMerge.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CFieldObjectMergeApp:
// �� Ŭ������ ������ ���ؼ��� FieldObjectMerge.cpp�� �����Ͻʽÿ�.
//

class CFieldObjectMergeApp : public CWinApp
{
public:
	CFieldObjectMergeApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CFieldObjectMergeApp theApp;
