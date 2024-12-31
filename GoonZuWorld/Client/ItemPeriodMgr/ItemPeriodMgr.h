#ifndef	__ITEMPERIODMGR_H__
#define __ITEMPERIODMGR_H__

#pragma once

//////////////////////////////////////////////////////////////////////////
//  [7/1/2009 ��ȣ_ITEM_PERIOD] client���� ������ ȿ���� ��������
//								resource�� ���� �����ϱ� ���� class
//////////////////////////////////////////////////////////////////////////

#include <directives.h>
#include "CommonHeader.h"
#include "../../Client/client.h"

#include <vector>

struct sItemPeriodObj;

class CItemPeriodMgr
{
	private:
	vector<sItemPeriodObj> m_SItemPeriodObj;

public:
	bool			Initialize();						//	manager �ʱ�ȭ ����
	
	sItemPeriodObj*	GetBuffData(SI32 siBuffIndex);		//	�����ε��� �� �������� ��������

public:
	CItemPeriodMgr(void);
	~CItemPeriodMgr(void);
};

//	���� ���� �ʿ��� ������
struct sItemPeriodObj
{
	TCHAR	m_szBuffName[MAX_PATH];
	SI32	m_siTabIndex;
	SI32	m_siIconIndex;
	SI32	m_siTextindex;

	sItemPeriodObj()
	{
		ZeroMemory(m_szBuffName, MAX_PATH);
		m_siTabIndex	= 0;
		m_siIconIndex	= 0;
		m_siTextindex	= 0;
	}

	TCHAR* GetBuffName(){return m_szBuffName;}
	SI32 GetTabIndex(){return m_siTabIndex;}
	SI32 GetIconIndex(){return m_siIconIndex;}
	SI32 GetTextIndex(){return m_siTextindex;}
};

#endif