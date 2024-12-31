// GMTOOL.h : GMTOOL ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ

#include "../../NGameDataManager/NGameDataManager.h"
#include "./ItemManagerClient.h"
#include "./NewLog/NewLogFrame.h"

// CGMTOOLApp:
// �� Ŭ������ ������ ���ؼ��� GMTOOL.cpp�� �����Ͻʽÿ�.
//

#if defined(KOREA)
	#define SERVICEAREA ConstServiceArea_Korea
#elif defined(ENGLISH)
	#define SERVICEAREA ConstServiceArea_English
#elif defined(JAPAN)
	#define SERVICEAREA ConstServiceArea_Japan
#elif defined(EUROPE)
	#define SERVICEAREA ConstServiceArea_EUROPE
#elif defined(NHNCHINA)
	#define SERVICEAREA ConstServiceArea_NHNChina
#elif defined(TAIWAN)
	#define SERVICEAREA ConstServiceArea_Taiwan
#else
	#define SERVICEAREA ConstServiceArea_Korea
#endif


class CGMTOOLApp : public CWinApp
{
public:
	CGMTOOLApp();


// ������
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ����
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	NGameDataManager	m_kDataManager;
	cltItemManagerClient m_clItemManagerClient;

	CNewLogFrame* CreatNewLog();
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuLog();
	afx_msg void OnMenuGuild();
	afx_msg void OnMenuId();

	afx_msg void OnMenuChar();
//	afx_msg void OnMenuItem();
	
//	afx_msg void OnMenuStatics();
//	afx_msg void OnMenuInfor();
//	afx_msg void OnMenuRecover();
	afx_msg void OnMenuNotice();
	afx_msg void OnMenuBlockchar();
//	afx_msg void OnMenuItem();
	afx_msg void OnMenuItem();
	afx_msg void OnMenuNewLog();
	afx_msg void OnMenuGmclient();
	afx_msg void OnMenuTradeLog();
	afx_msg void OnMenuSelledLog();
};

extern CGMTOOLApp theApp;
