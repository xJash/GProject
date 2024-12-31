#ifndef _DBMSGSOULGUARD_H
#define _DBMSGSOULGUARD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"

// 
class sDBRequest_SoulGuardCreate
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siPersonID;

	TCHAR				m_szName[MAX_SOULGUARD_NAME];	// ��ȣ���� �̸�

	SI16				m_siStatus;						// ��ȣ���� ����
	SI16				m_siKind;						// ��ȣ���� KIND

	SI32				m_siLimitDateVary;				// �̶����� �������

	SI16				m_siFellowShip;					// ģȭ��

public:
	sDBRequest_SoulGuardCreate( )
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuardCreate) );
	}

	sDBRequest_SoulGuardCreate( SI32 siPersonID, TCHAR* pszName, SI16 siStatus, SI16 siKind, SI32 siLimitDateVary, SI16 siFellowShip )
	{
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuardCreate);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_CREATE;

		m_siPersonID			= siPersonID;

		if ( pszName )
		{
			StringCchCopy( m_szName, sizeof(m_szName), pszName );
		}

		m_siStatus				= siStatus;
		m_siKind				= siKind;

		m_siLimitDateVary		= siLimitDateVary;

		m_siFellowShip			= siFellowShip;
		
	}
};

class sDBResponse_SoulGuardCreate
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;

	SI32				m_siPersonID;

	SI32				m_siSoulGuardID;				// ��ȣ���� ���� ID(PersonID���� ����ũ�� ����)
	SI08				m_siPosType;					// ��� �����Ǿ��ִ��� �˷��� (1 ĳ����, 2 ������)

	TCHAR				m_szName[MAX_SOULGUARD_NAME];	// ��ȣ���� �̸�

	SI16				m_siStatus;						// ��ȣ���� ����
	SI16				m_siKind;						// ��ȣ���� KIND

	SI32				m_siLimitDateVary;				// �̶����� �������

	SI16				m_siFellowShip;					// ģȭ��

public:
	sDBResponse_SoulGuardCreate()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuardCreate) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_CREATE

// ĳ���Ϳ��� �ִ� ��ȣ���� ������ ���� �´�
class sDBRequest_SoulGuardGet
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

public:
	sDBRequest_SoulGuardGet()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuardGet) );
	}

	sDBRequest_SoulGuardGet( SI32 siPersonID )
	{
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuardGet);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_GET;

		m_siPersonID			= siPersonID;
	}
};

class sDBResponse_SoulGuardGet
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;						// �����

	SI32				m_siPersonID;

	SI32				m_siSoulGuardID;				// ��ȣ���� ���� ID(PersonID���� ����ũ�� ����)

	TCHAR				m_szName[MAX_SOULGUARD_NAME];	// ��ȣ���� �̸�

	SI16				m_siStatus;						// ��ȣ���� ����
	SI16				m_siKind;						// ��ȣ���� KIND

	SI32				m_siLimitDateVary;				// �̶����� �������

	SI16				m_siFellowShip;					// ģȭ��

public:
	sDBResponse_SoulGuardGet()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuardGet) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_GET


// ĳ���Ϳ��� �ִ� ��ȣ���� ģȭ�¸� �����Ѵ�
class sDBRequest_SoulGuard_FellowShipSet
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	SI32			m_siSoulGuardID;
	SI16			m_siFellowShip;

public:
	sDBRequest_SoulGuard_FellowShipSet()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuard_FellowShipSet) );
	}

	sDBRequest_SoulGuard_FellowShipSet( SI32 siPersonID, SI32 siSoulGuardID, SI16 siFellowShip )
	{
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuard_FellowShipSet);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_FELLOWSHIP_SET;

		m_siPersonID			= siPersonID;
		m_siSoulGuardID			= siSoulGuardID;

		m_siFellowShip			= siFellowShip;
	}
};

class sDBResponse_SoulGuard_FellowShipSet
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	SI32			m_siPersonID;

	SI32			m_siSoulGuardID;
	SI16			m_siFellowShip;

public:
	sDBResponse_SoulGuard_FellowShipSet()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuard_FellowShipSet) );
	}

};	// DBMSG_RESPONSE_SOULGUARD_FELLOWSHIP_SET

// ĳ���Ϳ� �ִ� ��ȣ������ �̸� ����
class sDBRequest_SoulGuard_Change_Name
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	SI32			m_siSoulGuardID;
	TCHAR			m_szChangeName[MAX_SOULGUARD_NAME];

public:
	sDBRequest_SoulGuard_Change_Name()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuard_Change_Name) );
	}

	sDBRequest_SoulGuard_Change_Name( SI32 siPersonID, SI32 siSoulGuardID, TCHAR* pszChangeName )
	{
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuard_Change_Name);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_CHANGE_NAME;

		m_siPersonID			= siPersonID;
		m_siSoulGuardID			= siSoulGuardID;

		if ( pszChangeName )
		{
			StringCchCopy( m_szChangeName, sizeof(m_szChangeName), pszChangeName );
		}
	}
};

class sDBResponse_SoulGuard_Change_Name
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	SI32			m_siPersonID;

	SI32			m_siSoulGuardID;
	TCHAR			m_szChangeName[MAX_SOULGUARD_NAME];

public:
	sDBResponse_SoulGuard_Change_Name()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuard_Change_Name) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_CHANGE_NAME

enum SOULGUARD_DEAD_MODE
{
	SOULGUARD_DEAD_MODE_FREE = 1,	// ������ Ǯ���ش�
	SOULGUARD_DEAD_MODE_DEAD		// ����� ���ؼ� �׾���(�̰��� Ŭ���̾�Ʈ�� ���� �ü��� ���� ������ �������� ����)
};

// ĳ���Ϳ� �ִ� ��ȣ������ ������ ���ؼ� �״´�
class sDBRequest_SoulGuard_Dead
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	SI32			m_siSoulGuardID;

	SI32			m_siDeadMode;

public:
	sDBRequest_SoulGuard_Dead()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuard_Dead) );
	}

	sDBRequest_SoulGuard_Dead( SI32 siPersonID, SI32 siSoulGuardID, SI32 siDeadMode )
	{
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuard_Dead);
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_DEAD;

		m_siPersonID			= siPersonID;
		m_siSoulGuardID			= siSoulGuardID;
		m_siDeadMode			= siDeadMode;
	}
};

class sDBResponse_SoulGuard_Dead
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;

	SI32			m_siPersonID;

	SI32			m_siDeadMode;

public:
	sDBResponse_SoulGuard_Dead()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuard_Dead) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_DEAD

//--------------------------------------------------------------------------- 
//                          ��ȣ���� ������ ����
//--------------------------------------------------------------------------- 

// ��ȣ���� ������ ������ ���´�
class sDBRequest_SoulGuardHouse_Get
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

public:
	sDBRequest_SoulGuardHouse_Get()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuardHouse_Get) );
	}

	sDBRequest_SoulGuardHouse_Get( SI32 siPersonID )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_HOUSE_GET;
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuardHouse_Get);

		m_siPersonID			= siPersonID;
	}

};

class sDBResponse_SoulGuardHouse_Get
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;				// �����

	SI32			m_siPersonID;			// ��û ID

	SI32			m_siHouseNum;			// ���� ��밡���� ������ ����

	SI32			m_siSoulGuardID[MAX_SOULGUARD_HOUSE_NUM];		// ��ȣ���� ID
	SI16			m_sisoulGuardKind[MAX_SOULGUARD_HOUSE_NUM];	// ��ȣ���� KIND

public:
	sDBResponse_SoulGuardHouse_Get()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuardHouse_Get) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_HOUSE_GET

// ĳ������ ��ȣ���ɰ� �������� ��ȣ������ �±�ȯ �Ѵ�
class sDBRequest_SoulGuardHouse_Change
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	SI32			m_siCharSoulGuardID;	// ĳ���Ͱ� ���� �ִ� ��ȣ���� ID
	SI32			m_siHouseSoulGuardID;	// �����ҿ� �ִ� ��ȣ���� ID

public:
	sDBRequest_SoulGuardHouse_Change()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuardHouse_Change) );
	}

	sDBRequest_SoulGuardHouse_Change( SI32 siPersonID, SI32 siCharSoulGuardID, SI32 siHouseSoulGuardID )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_HOUSE_CHANGE;
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuardHouse_Change);

		m_siPersonID			= siPersonID;

		m_siCharSoulGuardID		= siCharSoulGuardID;
		m_siHouseSoulGuardID	= siHouseSoulGuardID;
	}
};

class sDBResponse_SoulGuardHouse_Change
{
public:
	sPacketHeader		m_packetHeader;

	SI32				m_siResult;						// �����

	SI32				m_siPersonID;
	// �����ҿ� �־��� ��ȣ���� ����
	SI32				m_siSoulGuardID;				// ��ȣ���� ���� ID(PersonID���� ����ũ�� ����)

	TCHAR				m_szName[MAX_SOULGUARD_NAME];	// ��ȣ���� �̸�

	SI16				m_siStatus;						// ��ȣ���� ����
	SI16				m_siKind;						// ��ȣ���� KIND

	SI32				m_siLimitDateVary;				// �̶����� �������

	SI16				m_siFellowShip;					// ģȭ��

public:
	sDBResponse_SoulGuardHouse_Change()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuardHouse_Change) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_HOUSE_CHANGE

// ĳ������ ��ȣ���ɰ� �������� ��ȣ������ �±�ȯ �Ѵ�
class sDBRequest_SoulGuardHouse_Create
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;

	SI32			m_siHouseNum;	// �̰��� �߰��Ǵ� ������ �ƴ϶� �ִ밹���� ������

	SI16			m_siItemPos;	// ���Ǵ� ������ ��ġ
	cltItem			m_clItem;		// ���Ǵ� ������

public:
	sDBRequest_SoulGuardHouse_Create()
	{
		ZeroMemory( this, sizeof(sDBRequest_SoulGuardHouse_Create) );
	}

	sDBRequest_SoulGuardHouse_Create( SI32 siPersonID, SI32 siHouseNum, SI16 siItemPos, cltItem* pclItem )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_SOULGUARD_HOUSE_CREATE;
		m_packetHeader.usSize	= sizeof(sDBRequest_SoulGuardHouse_Create);

		m_siPersonID			= siPersonID;

		m_siHouseNum			= siHouseNum;

		m_siItemPos				= siItemPos;
		if ( pclItem )
		{
			m_clItem.Set( pclItem );
		}
	}
};

class sDBResponse_SoulGuardHouse_Create
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;			// �����

	SI32			m_siPersonID;

	SI32			m_siHouseNum;		// �ִ� ��� ����

	SI16			m_siLeftItemPos;	// ����� ������ ��ġ
	cltItem			m_clLeftItem;		// ����� ������

public:
	sDBResponse_SoulGuardHouse_Create()
	{
		ZeroMemory( this, sizeof(sDBResponse_SoulGuardHouse_Create) );
	}
};	// DBMSG_RESPONSE_SOULGUARD_HOUSE_CREATE

#endif