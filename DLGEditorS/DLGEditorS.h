// DLGEditorS.h : DLGEditorS ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CDLGEditorSApp:
// �� Ŭ������ ������ ���ؼ��� DLGEditorS.cpp�� �����Ͻʽÿ�.
//

class CDLGEditorSApp : public CWinApp
{
public:
	CDLGEditorSApp();


// ������
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnDlgProperty();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
};

extern CDLGEditorSApp theApp;
