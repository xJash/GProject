#pragma once

#include "../../CommonLogic/CommonLogic.h"
#define MAX_SYSTEMREWARD_LIST		20		// �ִ� ������ �ִ� ����Ʈ�� ����(DB�ʿ����� �� �����ΰ��� ������ 20���� ���� # ������������)

enum eSystemRewardInfoType
{
	SystemRewardInfoType_DormancyEquipItem = 1	//	�޸� ���� ��� ���� ����
};

class cltSystemRewardInfo
{
public:
	SI32		m_siIndex;
	_SYSTEMTIME	m_sGiveTime;
	_SYSTEMTIME	m_sExpireTime;
	GMONEY		m_siMoney;
	cltItem		m_clItem;
	TCHAR		m_szReason[256];

	cltSystemRewardInfo();
	cltSystemRewardInfo( cltSystemRewardInfo* pclInfo );
	~cltSystemRewardInfo();

	void Init();
	void Set( cltSystemRewardInfo* pclInfo );
};


// [��ȣ_NHN->NDOORS] ���� ���󸮽�Ʈ ���� ��û
class cltRequestRewardList
{
public:
	SI32 m_siCurPage;

public:
	cltRequestRewardList(SI32 siCurPage)
	{
		ZeroMemory(this, sizeof(cltRequestRewardList));

		m_siCurPage = siCurPage;
	}
};