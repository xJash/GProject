#ifndef _DBMSGWEB_H
#define _DBMSGWEB_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBMsg.h"
#include "..\..\GoonZuWorld\Common\PrivateTradeOrderMgr\PrivateTradeOrderBaseInfo.h"

//-----------------------------------------
// ���� �Ź� ��� ��û. 
//-----------------------------------------
class sDBRequest_News
{
public:
	sPacketHeader		packetHeader;
	_SYSTEMTIME			sTime;

	sDBRequest_News()
	{
		ZeroMemory(this, sizeof(sDBRequest_News));
	}

	sDBRequest_News(_SYSTEMTIME* ptime)
	{
		packetHeader.usSize = sizeof( sDBRequest_News );
		packetHeader.usCmd	= DBMSG_REQUEST_NEWS;

		memcpy(&sTime, ptime, sizeof(_SYSTEMTIME));
	}

};

#define MAX_NEWS_TITLE_LENGTH		128
#define MAX_NEWSPAPER_NAME_LENGTH	32
class sDBResponse_News
{
public:
	sPacketHeader		packetHeader;

	SI32				siResult;			// �����.
	
	//bool   bBroadcastSwitch;						// ���� ��� ���� ����. 

	TCHAR	szNewsTitle[MAX_NEWS_TITLE_LENGTH];			// ���� �Ӹ����. 
	TCHAR	szNewspaperName[MAX_NEWSPAPER_NAME_LENGTH];	// �Ź��� �̸�. 
	TCHAR	szNewURL[MAX_PATH];							// ���� ��ũ�Ǵ� URL

	sDBResponse_News()
	{
		
		ZeroMemory(this, sizeof(sDBResponse_News));
	}
};




#endif
