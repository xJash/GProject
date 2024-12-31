#ifndef _DBMSGSOULGUARD_H
#define _DBMSGSOULGUARD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

//------------------------------------------
// �޸� ����Ʈ�� �������� ������ ���� ��û. 
//------------------------------------------
class sDBRequest_BuyDormancyPointItem
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;		// ���  Person
	cltItem				m_clItem;			// ��� ������ ����. 
	bool				m_bPileSwitch;		// ���� ���� ����. 
	SI32				m_siPoint;			// ������ �޸� ����Ʈ(�������� ��� ���� ����Ʈ)
	SI32				m_siItemPoint;		// ������ ����Ʈ 
	SI16				m_siItemPos;		// �������� ���� �κ��� ��ġ.

	sDBRequest_BuyDormancyPointItem()
	{
		ZeroMemory(this, sizeof(sDBRequest_BuyDormancyPointItem));
	}

	sDBRequest_BuyDormancyPointItem(UI16 usCharID, SI32 siPersonID, cltItem* pclItem, bool bPilewitch, SI32 siPoint, SI32 siItemPoint, SI32 siItempos)
	{
		m_sPacketHeader.usSize = sizeof( sDBRequest_BuyDormancyPointItem);
		m_sPacketHeader.usCmd = DBMSG_REQUEST_DORMANCY_POINTITEM_BUY;
		m_usCharID		= usCharID;

		m_siPersonID	= siPersonID;
		m_clItem.Set(pclItem);
		m_bPileSwitch	= bPilewitch;
		m_siPoint		= siPoint;
		m_siItemPoint	= siItemPoint;
		m_siItemPos		= siItempos;
	}
};


class sDBResonse_BuyDormancyPointItem
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siResult;			// �����.
	SI32				m_siPersonID;		
	SI16				m_siItemPos;
	cltItem				m_clItem;			// ���� ������.
	SI32				m_siItemPoint;		// ������ ����Ʈ.
	SI32				m_siPoint;			// ������ �޸� ����Ʈ(�������� ��� ���� ����Ʈ)

	sDBResonse_BuyDormancyPointItem()
	{
		ZeroMemory(this, sizeof(sDBResonse_BuyDormancyPointItem));
	}
};

//------------------------------------------
// �޸� ����Ʈ ���� ���� ���� ��û 
//------------------------------------------
class sDBRequest_SetDormancyPointInfo
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;				// ���  Person
	SI32				m_siPoint;					// ���� �޸� ����Ʈ
	SI32				m_siRemainedPlayTime;		// �÷��� �ð�
	
	sDBRequest_SetDormancyPointInfo()
	{
		ZeroMemory(this, sizeof(sDBRequest_SetDormancyPointInfo));
	}

	sDBRequest_SetDormancyPointInfo(UI16 usCharID, SI32 siPersonID, SI32 siPoint, SI32 siRemainedPlayTime)
	{
		m_sPacketHeader.usSize = sizeof( sDBRequest_SetDormancyPointInfo);
		m_sPacketHeader.usCmd = DBMSG_REQUEST_DORMANCY_POINTINFO_SET;
		m_usCharID			= usCharID;

		m_siPersonID		= siPersonID;
		m_siPoint			= siPoint;
		m_siRemainedPlayTime= siRemainedPlayTime;
	}
};

class sDBResonse_SetDormancyPointInfo
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siResult;				// �����.
	SI32				m_siPersonID;		
	SI32				m_siPoint;				// ���� �޸� ����Ʈ
	SI32				m_siRemainedPlayTime;	// �÷��� �ð�

	sDBResonse_SetDormancyPointInfo()
	{
		ZeroMemory(this, sizeof(sDBResonse_SetDormancyPointInfo));
	}
};

//------------------------------------------
// �޸� ���� ���� ����
//------------------------------------------
class sDBRequest_ChangeDormancyState
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siPersonID;				// ���  Person
	bool				m_bDormancyState;			// �޸� ���� ���� �ƴ���

	sDBRequest_ChangeDormancyState()
	{
		ZeroMemory(this, sizeof(sDBRequest_ChangeDormancyState));
	}

	sDBRequest_ChangeDormancyState(UI16 usCharID, SI32 siPersonID, bool bDormancyState)
	{
		m_sPacketHeader.usSize = sizeof( sDBRequest_ChangeDormancyState);
		m_sPacketHeader.usCmd = DBMSG_REQUEST_DORMANCY_STATE_CHANGE;
		m_usCharID			= usCharID;

		m_siPersonID		= siPersonID;
		m_bDormancyState	= bDormancyState;
	}
};

class sDBResponse_ChangeDormancyState
{
public:
	sPacketHeader		m_sPacketHeader;
	UI16				m_usCharID;

	SI32				m_siResult;				// �����.
	SI32				m_siPersonID;		
	bool				m_bDormancyState;		// �޸� ���� ���� �ƴ���

	sDBResponse_ChangeDormancyState()
	{
		ZeroMemory(this, sizeof(sDBResponse_ChangeDormancyState));
	}
};


#endif