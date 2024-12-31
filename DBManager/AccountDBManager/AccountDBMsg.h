#ifndef _ACCOUNTDBMSG_H
#define _ACCOUNTDBMSG_H

#include "itzbase.h"

enum {
	DBMSG_REQUEST_IDNUMGET = 0,
	DBMSG_RESPONSE_IDNUMGET,

	DBMSG_REQUEST_ADMINLOGIN,
	DBMSG_RESPONSE_ADMINLOGIN,

	DBMSG_REQUEST_JOINGAME,
	DBMSG_RESPONSE_JOINGAME,

	DBMSG_REQUEST_GAMEAUTH,
	DBMSG_RESPONSE_GAMEAUTH,

	DBMSG_REQUEST_IDNUMGET2,
	DBMSG_RESPONSE_IDNUMGET2,

	DBMSG_REQUEST_NEWCHARNUM,
	DBMSG_RESPONSE_NEWCHARNUM,

	DBMSG_REQUEST_NETMARBLELOGIN,
	DBMSG_RESPONSE_NETMARBLELOGIN,

	DBMSG_REQUEST_RECORDUSERNUM,

	DBMSG_REQUEST_RECORDSERVERUSERNUM,

	DBMSG_REQUEST_GMTOOLLOGIN,
	DBMSG_RESPONSE_GMTOOLLOGIN,

	DBMSG_REQUEST_ENGLISH_IDNUMGET,
	DBMSG_RESPONSE_ENGLISH_IDNUMGET,
};


/*-------------------------------------------------------------------
����: idnum��� [��û]
��¥: 2003-07-29
-------------------------------------------------------------------*/
struct sDBRequest_IDNumGet
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 40 ];		// For �븸 by LEEKH - 2007.08.03  // �Ϻ� �ؽ� - +5����Ʈ �߰�.
	char			userpw[ 40 ];		// For �븸 by LEEKH - 2007.08.03

	char			userIP[ 20 ];
	char			jumin[ 20 ];

	// �Ϻ� �ؽ� �� ������.
	char 			requestTime[24];
	char 			mkey1[37];
	char 			mkey2[37];
	char 			key[261];
	
	char			macaddress[ 20 ];

	SI32			accountstatus;

	sDBRequest_IDNumGet() 
	{ 
		ZeroMemory(userid, 40);
		ZeroMemory(userpw, 40);
		ZeroMemory(userIP, 20);
		ZeroMemory(jumin, 20);
		ZeroMemory(requestTime, 24);
		ZeroMemory(mkey1, 37);
		ZeroMemory(mkey2, 37);
		ZeroMemory(key, 261);
		ZeroMemory(macaddress, 20);
		
		accountstatus = 0;
    } 
};

/*-------------------------------------------------------------------
����: idnum��� [��û] - IOVATION ��
��¥: 2009-02-03
-------------------------------------------------------------------*/
struct sDBRequest_English_IDNumGet
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 40 ];		// For �븸 by LEEKH - 2007.08.03  // �Ϻ� �ؽ� - +5����Ʈ �߰�.
	char			userpw[ 40 ];		// For �븸 by LEEKH - 2007.08.03

	char			userIP[ 20 ];
	char			jumin[ 20 ];

	// �Ϻ� �ؽ� �� ������.
	char 		requestTime[24];
	char 		mkey1[37];
	char 		mkey2[37];
	char 		key[261];

	char			macaddress[ 20 ];

	char			Blackbox[ 2048 ];

	SI32	accountstatus;

	sDBRequest_English_IDNumGet() { 

		ZeroMemory(userid, 40);
		ZeroMemory(userpw, 40);
		ZeroMemory(userIP, 20);
		ZeroMemory(jumin, 20);
		ZeroMemory(requestTime, 24);
		ZeroMemory(mkey1, 37);
		ZeroMemory(mkey2, 37);
		ZeroMemory(key, 261);
		ZeroMemory(macaddress, 20);
		ZeroMemory(Blackbox, 2048);

		accountstatus = 0;
	} 
};

/*-------------------------------------------------------------------
����: idnum��� [����]
��¥: 2003-07-29
-------------------------------------------------------------------*/
struct sDBResponse_IDNumGet
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];

	SI32			idnum;						// idnum < 0�̸�, ��������
	SI16			siGameMasterLevel;		    // ��� ����
	SI32			siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32			siBlockYear;
	SI32			siBlockMonth;
	SI32			siBlockDay;
	SI32			siBlockHour;
	SI32			siBlockMin;
	char			szBlockReason[ 30 ];
	bool			bAlreadyMakeCharSwitch;
	char			szServerName[ 20 ];

	SI32			siAccountStatus;
	char			userIP[ 20 ];

	char			macaddress[ 20 ];

	UI08			m_uiRealAge;				// (�ѱ�) ���� �ֹε�ϻ��� ���̸� ����
};

/*-------------------------------------------------------------------
����: idnum��� [��û] (ldap)
��¥: 2004-05-14
-------------------------------------------------------------------*/
struct sDBRequest_IDNumGet2
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];
	char			jumin[ 20 ];
	char			userIP[ 20 ];
	char			macaddress[ 20 ];
};

/*-------------------------------------------------------------------
����: idnum��� [����] (ldap)
��¥: 2004-05-14
-------------------------------------------------------------------*/
struct sDBResponse_IDNumGet2
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;	
	UI16			usFrontCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];

	SI32			idnum;						// idnum < 0�̸�, ��������
	SI16			siGameMasterLevel;		    // ��� ����
};

/*-------------------------------------------------------------------
����: idnum��� [����] - IOVATION ��
��¥: 2009-02-03
-------------------------------------------------------------------*/
struct sDBResponse_English_IDNumGet
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];

	SI32			idnum;						// idnum < 0�̸�, ��������
	SI16			siGameMasterLevel;		    // ��� ����
	SI32			siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32			siBlockYear;
	SI32			siBlockMonth;
	SI32			siBlockDay;
	SI32			siBlockHour;
	SI32			siBlockMin;
	char			szBlockReason[ 30 ];
	bool			bAlreadyMakeCharSwitch;
	char			szServerName[ 20 ];

	SI32			siAccountStatus;
	char			userIP[ 20 ];

	char			macaddress[ 20 ];

	char			Blackbox[ 2048 ];
};

/*-------------------------------------------------------------------
����: Game Server ���� ��û
��¥: 2004-01-27
-------------------------------------------------------------------*/
struct sDBRequest_GameAuth
{
	sPacketHeader	packetHeader;

	UI16			usGameServerID;
	UI16			usCharID;

	SI32			idnum;

	char			userid[ 30 ];		// �븸 �۾��� ���� ���̰� �þ by LEEKH - 2007.08.03
	char			userpw[ 40 ];		// �븸 �۾��� ���� ���̰� �þ by LEEKH - 2007.08.03
	SI32			siPlayingTime;

	UI32			uiIDNo;				// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11
};

/*-------------------------------------------------------------------
����: Game Server ���� ���� 
��¥: 2004-01-27
-------------------------------------------------------------------*/
struct sDBResponse_GameAuth
{
	sPacketHeader	packetHeader;

	UI16			usGameServerID;
	UI16			usCharID;

	SI16			siSex;

	SI32			idnum;						// idnum < 0�̸�, ��������
	SI16			siGameMasterLevel;		    // ��� ����
	SI32			siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32			siBlockYear;
	SI32			siBlockMonth;
	SI32			siBlockDay;
	SI32			siBlockHour;
	SI32			siBlockMin;
	char			szBlockReason[ 30 ];

	SI32			siAccountStatus;
	SI32			siPlayingTime;

	UI32			uiIDNo;				// �Ѱ��ӿ� IDNO - by LEEKH 2007.11.11
	char			userid[ 30 ];		//KHY - 0218 - �߱� NHN �Ƿε� ��� ���� - �ʿ��ϴ�. 

	SI16			siDormancyState;			// �޸� �������� �ƴ���
};



/*-------------------------------------------------------------------
����: ������ ��� �α��� 
��¥: 2003-09-22
-------------------------------------------------------------------*/
struct sDBRequest_AdminLogin
{
	sPacketHeader	packetHeader;
	UI16			usMasterCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];
//	char			userip[ 20 ];		-- IP ���� ���� - ������ �������� ��ɾ� ���� - by LEEKH 2008.01.30
};

/*-------------------------------------------------------------------
����: ������ ��� �α��� 
��¥: 2003-09-22
-------------------------------------------------------------------*/
struct sDBResponse_AdminLogin
{
	sPacketHeader	packetHeader;
	UI16			usMasterCharID;

	UI16			usResult;				    // ��� ���� ( 0: ��ھƴ� or ���̵���� or �н�����Ʋ�� )
	char			userid[ 20 ];
};


/*-------------------------------------------------------------------
����: ���� ���� ��û 
��¥: 2004-01-27
-------------------------------------------------------------------*/
struct sDBRequest_JoinGame
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];
	char			jumin[ 20 ];
	char			cookie[ 20 ];
	char			szIP[ 20 ];
};


/*-------------------------------------------------------------------
����: ���� ���� ����
��¥: 2004-01-27
-------------------------------------------------------------------*/
struct sDBResponse_JoinGame
{
	sPacketHeader	packetHeader;

	UI16			usPacketUnique;
	UI16			usFrontCharID;

	SI32			siResult;
};

struct sDBRequest_NewCharNum
{
	sPacketHeader	packetHeader;

	SI32			siCount;
	char			szServerName[ 50 ][ 32 ];
};


struct sDBResponse_NewCharNum
{
	sPacketHeader	packetHeader;

	SI32			siCount;
	SI32			siNewCharNum[ 50 ];
	SI32			siDelCharNum[ 50 ];
};

/*-------------------------------------------------------------------
����: �ݸ��� �α� ��û
��¥: 2005-07-04
-------------------------------------------------------------------*/
struct sDBRequest_NetmarbleLogin
{
	sPacketHeader	packetHeader;

	UI16			usGameServerID;
	UI16			usCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];
	char			userIP[ 20 ];
	char			jumin[ 20 ];
	char			macaddress[ 20 ];
};

/*-------------------------------------------------------------------
����: �ݸ��� �α� ����
��¥: 2005-07-04
-------------------------------------------------------------------*/
struct sDBResponse_NetmarbleLogin
{
	sPacketHeader	packetHeader;

	UI16			usGameServerID;
	UI16			usCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];

	SI32			idnum;						// idnum < 0�̸�, ��������
	SI16			siGameMasterLevel;		    // ��� ����
	SI32			siBlockMode;				// 0:�Ϲ�, 1:��, 2:������
	SI32			siBlockYear;
	SI32			siBlockMonth;
	SI32			siBlockDay;
	SI32			siBlockHour;
	SI32			siBlockMin;
	char			szBlockReason[ 30 ];
	bool			bAlreadyMakeCharSwitch;
};

struct sDBRequest_RecordUserNum
{
	sPacketHeader	packetHeader;

	SI32			siUserNum;
};

struct sDBRequest_RecordServerUserNum
{
	sPacketHeader	packetHeader;

	TCHAR			szServerName[20];
	TCHAR			szServerIP[16];
	SI32			siUserNum;
};

/*-------------------------------------------------------------------
����: GMTOOL �α��� 
-------------------------------------------------------------------*/
struct sDBRequest_GMTOOLLogin
{
	sPacketHeader	packetHeader;
	UI16			usGameServerID;
	UI16			usCharID;

	char			userid[ 20 ];
	char			userpw[ 20 ];
};

/*-------------------------------------------------------------------
����: GMTOOL �α��� 
-------------------------------------------------------------------*/
struct sDBResponse_GMTOOLLogin
{
	sPacketHeader	packetHeader;
	UI16			usGameServerID;
	UI16			usCharID;

	SI32			siGameMasterLevel;
	char			userid[ 20 ];
};

#endif
