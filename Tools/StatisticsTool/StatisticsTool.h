// StatisticsTool.h : StatisticsTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CStatisticsToolApp:
// �� Ŭ������ ������ ���ؼ��� StatisticsTool.cpp�� �����Ͻʽÿ�.
//

class CStatisticsToolApp : public CWinApp
{
public:
	CStatisticsToolApp();


// ������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern CStatisticsToolApp theApp;
