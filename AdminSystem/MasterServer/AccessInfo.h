#pragma once

#include <iostream>
#include <fstream>
#include "itzbase.h"

using namespace std;

enum E_AcessInfoType
{
	ACCESS_IP_MC = 1
};

const SI32 ConstMCAccessIpCount = 256;
const SI32 ConstIPSize = 16;

class CAccessInfo
{
protected:
	BOOL	SetMCIP(TCHAR* pszIP);

public:
	CAccessInfo(void);
	~CAccessInfo(void);

	BOOL	ReadFromFile();							// ���Ͽ��� ���� ���� ���
	BOOL	ConfirmAccessMC(TCHAR* pszIP);		// ����� Ŭ���̾�Ʈ ���� Ȯ��
public:
	TCHAR	m_szMCIPList[ConstMCAccessIpCount][ConstIPSize];
	SI32	m_siMCIPCount;
};
