#ifndef _DBMSG_WEDDING_H_
#define _DBMSG_WEDDING_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "../../../GoonZuWorld/CommonLogic/Marriage/WeddingManager.h"


// [����] ��ȥ�ý��� : ���� ����Ʈ �ޱ�
class sDBRequest_WeddingReserveListGet
{
public:
	sPacketHeader	m_packetHeader;

	SYSTEMTIME		m_stCurrentTime;	// �� ������ 24�ð� ���ı����� ���� ������ �޾ƿ´�

public:
	sDBRequest_WeddingReserveListGet( SYSTEMTIME& stCurrentTime )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_WEDDING_RESERVE_LIST_GET;
		m_packetHeader.usSize	= sizeof(sDBRequest_WeddingReserveListGet);

		memcpy( &m_stCurrentTime, &stCurrentTime, sizeof(m_stCurrentTime) );
	}
};


class sDBResponse_WeddingReserveListGet
{
public:
	sPacketHeader			m_packetHeader;

	cltWeddingReserveUnit	m_clReserveList[WEDDING_RESERVE_LIST_NUM];

public:
	sDBResponse_WeddingReserveListGet()
	{
		ZeroMemory( this, sizeof(sDBResponse_WeddingReserveListGet) );
	}

};	// DBMSG_RESPONSE_WEDDING_RESERVE_LIST_GET

// [����] ��ȥ �ý��� : ���� ���� �ϱ�
class sDBRequest_WeddingReserve
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;		// ������

	GMONEY			m_gmCost;			// ���� ���

	SYSTEMTIME		m_stReserveTime;	// �����Ϸ��� �ð�

public:
	sDBRequest_WeddingReserve( SI32 siPersonID, GMONEY gmCost, SYSTEMTIME& stReserveTime )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_WEDDING_RESERVE;
		m_packetHeader.usSize	= sizeof(sDBRequest_WeddingReserve);

		m_siPersonID			= siPersonID;

		m_gmCost				= gmCost;

		memcpy( &m_stReserveTime, &stReserveTime, sizeof(m_stReserveTime) );

	}
};

class sDBResponse_WeddingReserve
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;			// �����

	SI32			m_siPersonID;		// ������
	TCHAR			m_szPersonName[MAX_PLAYER_NAME];

	SI32			m_siMatePersonID;	// �������� �����
	TCHAR			m_szMateName[MAX_PLAYER_NAME];

	SI32			m_siReserveNum;		// �����ȣ

	GMONEY			m_gmLeftBankMoney;	// �������� ���� ���൷
	SYSTEMTIME		m_stReserveTime;	// ����ð�


	GMONEY			m_gmReserveMoney;	// �����ڱݾ� : [�߰�] 2009-07-09 �ռ���

public:
	sDBResponse_WeddingReserve()
	{
		ZeroMemory( this, sizeof(sDBResponse_WeddingReserve) );
	}
};	// DBMSG_RESPONSE_WEDDING_RESERVE

// [����] ��ȥ�ý��� : ���� ����ϱ�
class sDBRequest_WeddingReserveCancel
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siPersonID;	// ����ϴ� ���

	SI32			m_siReserveNum;	// ����ϴ� ���� ��ȣ

public:
	sDBRequest_WeddingReserveCancel( SI32 siPersonID, SI32 siReserveNum )
	{
		m_packetHeader.usCmd	= DBMSG_REQUEST_WEDDING_RESERVE_CANCEL;
		m_packetHeader.usSize	= sizeof(sDBRequest_WeddingReserveCancel);

		m_siPersonID			= siPersonID;
		m_siReserveNum			= siReserveNum;
	}
};

class sDBResponse_WeddingReserveCancel
{
public:
	sPacketHeader	m_packetHeader;

	SI32			m_siResult;		// �����

	SI32			m_siPersonID;	// ����ϴ� ���

	SI32			m_siReserveNum;	// ����ϴ� ���� ��ȣ

public:
	sDBResponse_WeddingReserveCancel( )
	{
		ZeroMemory( this, sizeof(sDBResponse_WeddingReserveCancel) );
	}
};	// DBMSG_RESPONSE_WEDDING_RESERVE_CANCEL

#endif
