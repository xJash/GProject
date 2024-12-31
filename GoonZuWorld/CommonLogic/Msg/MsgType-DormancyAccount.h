#pragma once

//#include "../SoulGuardMgr/SoulGuardMgr.h"

// �ڽ����� �޸� ���� ���� ������ ������ ��û
class cltGameMsgRequest_DormancyTakeOutEquipItemInBox
{
public:
	// ���� ����ũ
	SI32	m_siBoxUnique;
	// ���� ������ �κ��丮 ��ġ
	SI16	m_siBoxPos;
	// ���� ��� ������ ����ũ
	SI16	m_siEquipItemUnique;
	// ���� ��� �������� �ڽ������� �ε���
	SI16	m_siEquipItemIndex;
public:
	cltGameMsgRequest_DormancyTakeOutEquipItemInBox( SI32 siBoxUnique,SI16	siBoxPos, SI16 siEquipItemUnique,SI16 siEquipItemIndex )
	{
		m_siBoxUnique	= siBoxUnique;
		m_siBoxPos	= siBoxPos;
		m_siEquipItemUnique	= siEquipItemUnique;
		m_siEquipItemIndex = siEquipItemIndex;
	}
};	// GAMEMSG_REQUEST_DORMANCY_TAKEOUTEQUIPITEMINBOX

// �ڽ����� �޸� ���� ���� ������ ������ ����
class cltGameMsgResponse_DormancyTakeOutEquipItemInBox
{
public:
	cltItem	m_clBoxItem;	// ����ϰ� ���� ���� ������
	SI16	m_siBoxItemPos;	// 

	cltItem	m_clGetItem;	// ���� ������
	SI16	m_siGetItemPos;	//

public:
	cltGameMsgResponse_DormancyTakeOutEquipItemInBox( cltItem* pclBoxItem, SI16 siBoxItemPos, cltItem* pclGetItem, SI16 siGetItemPos )
	{
		if ( pclBoxItem )
		{
			m_clBoxItem.Set( pclBoxItem );
		}
		m_siBoxItemPos = siBoxItemPos;

		if ( pclGetItem )
		{
			m_clGetItem.Set( pclGetItem );
		}
		m_siGetItemPos = siGetItemPos;

	}
};	// GAMEMSG_RESOPONSE_DORMANCY_TAKEOUTEQUIPITEMINBOX

// �������� �ֱ������� Ŭ���̾�Ʈ���� �޸� ����Ʈ ���� ���� ����
class cltGameMsgResponse_DormancyRefreshPointInfo
{
public:
	SI16		m_siPoint;					// �޸� ����Ʈ
	SI16		m_siRemainedTime;			// �޸� ����Ʈ�� ��� ���� �÷��� �ð�
	BOOL		m_bDormancyState;			// �޸� ����
	SI16		m_siStartedYear;			// ���� ��
	SI16		m_siStartedMonth;			// ���� ��
	SI16		m_siStartedDay;			// ���� ��

public:
	cltGameMsgResponse_DormancyRefreshPointInfo( SI16 siPoint, SI16 siRemainedTime, BOOL bDormancyState ,SI16 siStartedYear, SI16 siStartedMonth, SI16 siStartedDay)
	{
		m_siPoint = siPoint;
		m_siRemainedTime = siRemainedTime;
		m_bDormancyState = bDormancyState;

		m_siStartedYear = siStartedYear;
		m_siStartedMonth = siStartedMonth;
		m_siStartedDay = siStartedDay;
	}
};	// GAMEMSG_RESPONSE_DORMANCY_REFRESHPOINTINFO

// �޸� ����Ʈ�� ������ ���� ��û
class cltGameMsgRequest_DormancyBuyPoinItem
{
public:
	// ������ ����ũ
	SI32	m_siItemUnique;
public:
	cltGameMsgRequest_DormancyBuyPoinItem( SI32 siItemUnique)
	{
		m_siItemUnique	= siItemUnique;	
	}
};	// GAMEMSG_REQUEST_DORMANCY_BUYPOINTITEM
