#ifndef _DBGAMELOGMSG_H
#define _DBGAMELOGMSG_H

#include "../../GoonZuWorld/Common/CommonHeader.h"
#include "../../GoonZuWorld/Common/Char/CharCommon/Char-Common.h"
#include "../../GoonZuWorld/Common/Char/ParametaBox/ParametaBox.h"
#include "../../GoonZuWorld/Common/Char/CharCommon/Char-Common.h"

#define MAX_STLOGDATA_PER_PACKET		10
#define MAX_RESPONSING_PERSONAL_LOG		10

#define LOGTYPE_PERSONAL_POSTOFFICE		0	// ���� ���� �ŷ�
#define LOGTYPE_PERSONAL_ITEMMALL		1	// ������ �� �ŷ�
#define LOGTYPE_PERSONAL_ALLITEM		2	// ����� ������ ���� �˻�
#define LOGTYPE_PERSONAL_CHARLOGIN		3	// ĳ���� �α��� �˻�
#define LOGTYPE_PERSONAL_ACCOUNTLOGIN	4	// ���� �α��� �˻�

#define MAX_DBLOG_SIZE_DATE				24 // DBLog szDate �ִ�
#define MAX_DBLOG_SIZE_COMMAND			30 // DBLog szCommand �ִ�
#define MAX_DBLOG_SIZE_LOGTEXT			256 // DBLog szLogTxt �ִ�
#define MAX_DBLOG_SIZE_SERVERNAME		16 // DBLog szServerName

enum {
	DBLOGMSG_REQUEST_PERSONAL_LOG = 1,		// [�ؿ�] ���� �α� ��û
	DBLOGMSG_RESPONSE_PERSONAL_LOG,
};

class stLOGData
{
public:
	char				szDate[MAX_DBLOG_SIZE_DATE];
	char				szCommand[MAX_DBLOG_SIZE_COMMAND];

	char				szPersonName[MAX_PLAYER_NAME];
	char				szDstPersonName[MAX_PLAYER_NAME];
	SI32				siItemUnique;
	char				szLogTxt[MAX_DBLOG_SIZE_LOGTEXT];

	void Init()
	{
		strcpy(szDate,"");
		strcpy(szCommand,"");

		strcpy(szPersonName,"");
		strcpy(szDstPersonName,"");
		siItemUnique = 0 ;
		strcpy(szLogTxt,"");
	}

	void Set(stLOGData * stlogdata)
	{
		memcpy ( this, stlogdata, sizeof( stLOGData ));
	}
};

// ���� �α� ��û
class sDBRequest_Personal_Log
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID; // ����� ĳ������ ID

	SI32				siLogType; // �α��� ����

	char				szServerName[MAX_DBLOG_SIZE_SERVERNAME]; // ���� �̸�
	char				szPersonName[MAX_PLAYER_NAME]; // ã�� ĳ������ �̸�
	
	SI32				siItemUnique; // �˻� ������

	char				szStartDate[MAX_DBLOG_SIZE_DATE]; // �˻������� ��¥ ex:2004-08-10 10:30
	char				szEndDate[MAX_DBLOG_SIZE_DATE]; // �˻� ���� ��¥ ex:2004-08-10 10:31

	sDBRequest_Personal_Log(UI16 charid, SI32 logtype,
		char * server,char * personname,SI32 itemunique,char *startdate,char *enddate)
	{

		packetHeader.usSize = sizeof( sDBRequest_Personal_Log );
		packetHeader.usCmd = DBLOGMSG_REQUEST_PERSONAL_LOG;

		usCharID = charid ;

		siLogType = logtype ;

		memcpy(szServerName,server,MAX_DBLOG_SIZE_SERVERNAME);
		memcpy(szPersonName,personname,MAX_PLAYER_NAME);

		siItemUnique = itemunique ;

		memcpy(szStartDate,startdate,MAX_DBLOG_SIZE_DATE);
		memcpy(szEndDate,enddate,MAX_DBLOG_SIZE_DATE);
	}
};

// ���� �α� ����
class sDBResponse_Personal_Log
{
public:
	sPacketHeader		packetHeader;
	UI16				usCharID;

	SI32				siResult;

	stLOGData			stLogData[MAX_STLOGDATA_PER_PACKET];

	sDBResponse_Personal_Log()
	{
		ZeroMemory( this, sizeof( sDBResponse_Personal_Log ) );
	}
};

#endif